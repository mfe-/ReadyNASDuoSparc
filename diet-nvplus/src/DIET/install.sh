#!/bin/sh
# DIET fuer ReadyNAS NV+ v1 - Installation als RAIDiator-Add-on
# Laeuft in RAIDiator (Frontview entpackt das Add-on nach /tmp/addons/DIET und startet "sh install.sh").
# - installiert/aktualisiert das DIET-System nach /diet (Konfiguration bleibt bei Updates erhalten)
# - uebernimmt bei Neuinstallation Name, Netz, Zeitzone, Benutzer, Passwoerter und Freigaben aus RAIDiator
# - setzt den Weichensteller als /sbin/init (Original bleibt als /sbin/init.real, RAIDiator ist Rueckfall)
# Das Flash wird nicht beschrieben.
PATH=/bin:/sbin:/usr/bin:/usr/sbin
VER=$(cat ./diet-version 2>/dev/null)
SRC=$(pwd)
LOG=/var/log/diet-install.log
exec >> $LOG 2>&1
HERE=$(pwd)
cleanup() { cd /; case "$HERE" in /tmp/addons/*) rm -rf "$HERE";; esac; }
echo "==== $(date) DIET $VER Installation (aus $SRC) ===="

lcd() { [ -e /proc/sys/dev/lcd/cmd ] || return 0; echo 192 > /proc/sys/dev/lcd/cmd; printf "%-16s" "$1" > /dev/lcd; } 2>/dev/null
fail() {
  echo "FEHLER: $*"
  lcd "DIET: Fehler"
  rm -rf /diet.new
  rm -f /.update_success
  echo "{DIET_ERR} DIET nicht installiert: $* (Details in $LOG)" > /.update_fail
  cleanup
  exit 1
}

# --- Pruefungen ---
grep -q "^model:.*NV+" /proc/sys/dev/boot/info 2>/dev/null || fail "nur fuer ReadyNAS NV+ v1"
PCB=$(sed -n 's/^pcbid:[ \t]*//p' /proc/sys/dev/boot/info)
[ -n "$PCB" ] && [ "$PCB" -lt 128 ] 2>/dev/null || fail "unbekanntes Board (pcbid $PCB)"
case "$(uname -r)" in 2.6.17*) ;; *) fail "Kernel $(uname -r) wird nicht unterstuetzt";; esac
[ -f "$SRC/diet.tgz" ] || fail "Paket unvollstaendig"
FREE=$(df -k / | awk 'NR==2 {print $4}')
[ "${FREE:-0}" -gt 60000 ] || fail "zu wenig Platz auf dem Systemlaufwerk (${FREE} kB frei)"
lcd "DIET installiert"

# --- Auspacken ---
rm -rf /diet.new
mkdir /diet.new || fail "kann /diet.new nicht anlegen"
tar xzf "$SRC/diet.tgz" -C /diet.new || fail "Entpacken fehlgeschlagen"
[ -x /diet.new/bin/busybox ] && [ -x /diet.new/sbin/init-weiche ] || fail "Paket unvollstaendig"
N=/diet.new

if [ -f /diet/etc/hostname ]; then
  # --- Update: Konfiguration des bestehenden DIET uebernehmen ---
  echo "Update: uebernehme Konfiguration aus /diet"
  for f in etc/hostname etc/TZ etc/diet-net.conf etc/httpd.conf etc/rsyncd.conf etc/passwd etc/group \
           etc/samba/smb.conf etc/samba/shares.conf etc/samba/smbpasswd etc/samba/private etc/dropbear root/.ssh; do
    if [ -e /diet/$f ]; then rm -rf $N/$f; mkdir -p $N/$(dirname $f); cp -a /diet/$f $N/$f; fi
  done
  # diet.conf: alte Werte behalten, neue Schluessel ergaenzen
  if [ -f /diet/etc/diet.conf ]; then
    cp $N/etc/diet.conf /tmp/diet.conf.neu
    cp /diet/etc/diet.conf $N/etc/diet.conf
    while IFS= read -r line; do
      k=${line%%=*}
      case "$line" in [A-Z]*=*) grep -q "^$k=" $N/etc/diet.conf || echo "$line" >> $N/etc/diet.conf;; esac
    done < /tmp/diet.conf.neu
    rm -f /tmp/diet.conf.neu
  fi
else
  # --- Neuinstallation: Einstellungen aus RAIDiator uebernehmen ---
  echo "Neuinstallation: uebernehme Einstellungen aus RAIDiator"
  H=$(hostname | tr 'A-Z' 'a-z' | tr -cd 'a-z0-9-' | cut -c1-15); [ -n "$H" ] || H=readynas
  echo "$H" > $N/etc/hostname

  # Zeitzone: RAIDiator nutzt /etc/localtime -> zoneinfo, busybox braucht eine POSIX-Zeichenkette
  Z=$(ls -l /etc/localtime 2>/dev/null | sed -n 's|.*zoneinfo/||p')
  case "$Z" in
    Europe/London|Europe/Dublin|Europe/Lisbon|GB|Eire|Portugal) TZS="GMT0BST,M3.5.0/1,M10.5.0" ;;
    Europe/Helsinki|Europe/Kiev|Europe/Kyiv|Europe/Riga|Europe/Tallinn|Europe/Vilnius|Europe/Sofia|Europe/Athens|Europe/Bucharest) TZS="EET-2EEST,M3.5.0/3,M10.5.0/4" ;;
    Europe/Moscow) TZS="MSK-3" ;;
    Europe/*|CET|MET) TZS="CET-1CEST,M3.5.0,M10.5.0/3" ;;
    US/Eastern|America/New_York|America/Detroit|America/Toronto) TZS="EST5EDT,M3.2.0,M11.1.0" ;;
    US/Central|America/Chicago|America/Winnipeg) TZS="CST6CDT,M3.2.0,M11.1.0" ;;
    US/Mountain|America/Denver|America/Edmonton) TZS="MST7MDT,M3.2.0,M11.1.0" ;;
    US/Arizona|America/Phoenix) TZS="MST7" ;;
    US/Pacific|America/Los_Angeles|America/Vancouver) TZS="PST8PDT,M3.2.0,M11.1.0" ;;
    Australia/Sydney|Australia/Melbourne|Australia/Canberra) TZS="AEST-10AEDT,M10.1.0,M4.1.0/3" ;;
    Asia/Tokyo|Japan) TZS="JST-9" ;;
    *) TZS="UTC0" ;;
  esac
  echo "$TZS" > $N/etc/TZ
  echo "Zeitzone: $Z -> $TZS"

  # Benutzer: root-Passwort (= Admin-Passwort von RAIDiator) und die RAIDiator-Benutzer
  RH=$(awk -F: '$1=="root"{print $2}' /etc/passwd)
  if [ "$RH" = "x" ] && [ -f /etc/shadow ]; then RH=$(awk -F: '$1=="root"{print $2}' /etc/shadow); fi
  [ -n "$RH" ] || RH='!'
  {
    echo "root:$RH:0:0:root:/root:/bin/sh"
    echo "nobody:x:65534:65534:nobody:/:/bin/false"
    awk -F: '($3==98 || ($3>=1000 && $3<65534)) {print $1":x:"$3":"$4"::/c/home/"$1":/bin/false"}' /etc/passwd
  } > $N/etc/passwd
  {
    echo "root:x:0:"; echo "nogroup:x:65534:"
    awk -F: '($3==98 || ($3>=100 && $3<65534)) {print $1":x:"$3":"$4}' /etc/group
  } > $N/etc/group

  # Samba: Passwoerter (smbpasswd-Datei) und Freigaben direkt aus RAIDiator
  mkdir -p $N/etc/samba/private
  if [ -f /etc/samba/smbpasswd ]; then cp /etc/samba/smbpasswd $N/etc/samba/smbpasswd; chmod 600 $N/etc/samba/smbpasswd; fi
  if [ -f /etc/frontview/samba/Shares.conf ]; then cp /etc/frontview/samba/Shares.conf $N/etc/samba/shares.conf; else : > $N/etc/samba/shares.conf; fi
  WG=$(sed -n 's/^[ \t]*workgroup[ \t]*=[ \t]*//p' /etc/samba/smb.conf | head -1); [ -n "$WG" ] || WG=WORKGROUP
  NB=$(echo "$H" | tr 'a-z' 'A-Z' | cut -c1-15)
  sed -e "s/@WORKGROUP@/$WG/" -e "s/@NETBIOS@/$NB/" $N/etc/samba/smb.conf.template > $N/etc/samba/smb.conf

  # Web-Oberflaeche: Benutzer admin mit dem Admin-Passwort von RAIDiator (MD5-Hash wird direkt verwendet)
  case "$RH" in
    '$1$'*) sed "s|@USER@:@HASH@|admin:$RH|" $N/etc/httpd.conf.template > $N/etc/httpd.conf; chmod 600 $N/etc/httpd.conf ;;
    *) echo "Kein MD5-Admin-Passwort gefunden: Web-Oberflaeche erst nach 'diet-webpass' aktiv" ;;
  esac

  # SSH-Schluessel von root uebernehmen
  if [ -f /root/.ssh/authorized_keys ]; then mkdir -p $N/root/.ssh; cp /root/.ssh/authorized_keys $N/root/.ssh/; chmod 700 $N/root/.ssh; chmod 600 $N/root/.ssh/authorized_keys; fi
fi

# Netz: statische Adresse aus RAIDiator uebernehmen, sonst DHCP mit der aktuellen Adresse als Notnagel
if [ ! -f $N/etc/diet-net.conf ]; then
  CUR=$(ifconfig eth0 | sed -n 's/.*inet addr:\([0-9.]*\).*/\1/p')
  MASK=$(ifconfig eth0 | sed -n 's/.*Mask:\([0-9.]*\).*/\1/p')
  A=$(awk '/^iface eth0/{f=1;next} /^iface/{f=0} f && $1=="address"{print $2}' /etc/network/interfaces 2>/dev/null)
  if [ -n "$A" ]; then
    M=$(awk '/^iface eth0/{f=1;next} /^iface/{f=0} f && $1=="netmask"{print $2}' /etc/network/interfaces)
    G=$(awk '/^iface eth0/{f=1;next} /^iface/{f=0} f && $1=="gateway"{print $2}' /etc/network/interfaces)
    D=$(awk '$1=="nameserver"{printf "%s ", $2}' /etc/resolv.conf)
    printf 'NET=static\nIPADDR=%s\nNETMASK=%s\nGATEWAY=%s\nDNS="%s"\n' "$A" "${M:-$MASK}" "$G" "$D" > $N/etc/diet-net.conf
  else
    printf 'NET=dhcp\nFALLBACK_IP=%s\nNETMASK=%s\n' "$CUR" "${MASK:-255.255.255.0}" > $N/etc/diet-net.conf
  fi
  echo "Netz: $(tr '\n' ' ' < $N/etc/diet-net.conf)"
fi

# --- Umschalten: alte Version als /diet.old behalten ---
rm -rf /diet.old
[ -d /diet ] && { mv /diet /diet.old || fail "kann altes /diet nicht verschieben"; }
mv /diet.new /diet || fail "kann /diet nicht anlegen"

# --- Weichensteller: /sbin/init muss jederzeit existieren (sonst setzt linuxrc das System zurueck) ---
cp /diet/sbin/init-weiche /sbin/init.neu && chmod 755 /sbin/init.neu || fail "kann Weichensteller nicht kopieren"
sh -n /sbin/init.neu || fail "Weichensteller fehlerhaft"
if ! grep -q "Weichensteller" /sbin/init 2>/dev/null; then
  # Original-init sichern (harter Link, /sbin/init bleibt bestehen)
  rm -f /sbin/init.real
  ln /sbin/init /sbin/init.real 2>/dev/null || cp -p /sbin/init /sbin/init.real || fail "kann /sbin/init nicht sichern"
fi
[ -x /sbin/init.real ] || fail "/sbin/init.real fehlt"
mv /sbin/init.neu /sbin/init || fail "kann Weichensteller nicht setzen"
rm -f /.diet_pending /.raidiator_once
sync

echo "OK: DIET $VER installiert. Beim naechsten Neustart startet DIET."
# Beim Systemstart installiert (rc3, nach Update ueber Frontview): nach 2 Minuten automatisch in DIET neu starten
if [ -n "$RUNLEVEL" ]; then
  echo "Installation beim Start: automatischer Neustart in 2 Minuten"
  ( sleep 120; /sbin/reboot ) </dev/null >/dev/null 2>&1 &
fi
lcd "DIET: Neustart!"
cleanup
exit 0
