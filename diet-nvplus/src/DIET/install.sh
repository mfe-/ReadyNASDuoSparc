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
# Sprache der Meldungen: die von DIET (bei Update), sonst die von RAIDiator (LANGUAGE in /etc/default/services), sonst Englisch
L=$(cat /diet/etc/diet-lang 2>/dev/null)
[ -n "$L" ] || L=$(sed -n 's/^LANGUAGE=\([a-z][a-z]\).*/\1/p' /etc/default/services 2>/dev/null | head -n 1)
case "$L" in fr|de) ;; *) L=en ;; esac
tx() { case $L in fr) printf '%s' "$1" ;; de) printf '%s' "$2" ;; *) printf '%s' "$3" ;; esac; }
echo "==== $(date) $(tx "Installation de DIET $VER (depuis $SRC)" "DIET $VER Installation (aus $SRC)" "DIET $VER installation (from $SRC)") ===="

lcd() { [ -e /proc/sys/dev/lcd/cmd ] || return 0; echo 192 > /proc/sys/dev/lcd/cmd; printf "%-16s" "$1" > /dev/lcd; } 2>/dev/null
fail() {
  echo "$(tx "ERREUR" "FEHLER" "ERROR"): $*"
  lcd "$(tx "DIET: erreur" "DIET: Fehler" "DIET: error")"
  rm -rf /diet.new
  rm -f /.update_success
  echo "{DIET_ERR} $(tx "DIET non installé : $* (détails dans $LOG)" "DIET nicht installiert: $* (Details in $LOG)" "DIET not installed: $* (details in $LOG)")" > /.update_fail
  cleanup
  exit 1
}

# --- Pruefungen ---
grep -Eq "^model:.*(NV\+|ReadyNAS Duo)" /proc/sys/dev/boot/info 2>/dev/null || fail "$(tx "uniquement pour ReadyNAS NV+ v1 et Duo v1" "nur fuer ReadyNAS NV+ v1 und Duo v1" "only for ReadyNAS NV+ v1 and Duo v1")"
PCB=$(sed -n 's/^pcbid:[ \t]*//p' /proc/sys/dev/boot/info)
[ -n "$PCB" ] && [ "$PCB" -lt 128 ] 2>/dev/null || fail "$(tx "carte inconnue (pcbid $PCB)" "unbekanntes Board (pcbid $PCB)" "unknown board (pcbid $PCB)")"
case "$(uname -r)" in 2.6.17*) ;; *) fail "$(tx "noyau $(uname -r) non pris en charge" "Kernel $(uname -r) wird nicht unterstuetzt" "kernel $(uname -r) not supported")";; esac
[ -f "$SRC/diet.tgz" ] || fail "$(tx "paquet incomplet" "Paket unvollstaendig" "package incomplete")"
FREE=$(df -k / | awk 'NR==2 {print $4}')
[ "${FREE:-0}" -gt 60000 ] || fail "$(tx "pas assez de place sur le volume système (${FREE} ko libres)" "zu wenig Platz auf dem Systemlaufwerk (${FREE} kB frei)" "not enough space on the system volume (${FREE} kB free)")"
lcd "$(tx "DIET installe" "DIET installiert" "DIET installing")"

# --- Auspacken ---
rm -rf /diet.new
mkdir /diet.new || fail "$(tx "impossible de créer /diet.new" "kann /diet.new nicht anlegen" "cannot create /diet.new")"
tar xzf "$SRC/diet.tgz" -C /diet.new || fail "$(tx "échec de l’extraction" "Entpacken fehlgeschlagen" "extraction failed")"
[ -x /diet.new/bin/busybox ] && [ -x /diet.new/sbin/init-weiche ] || fail "$(tx "paquet incomplet" "Paket unvollstaendig" "package incomplete")"
N=/diet.new

if [ -f /diet/etc/hostname ]; then
  # --- Update: Konfiguration des bestehenden DIET uebernehmen ---
  echo "$(tx "Mise à jour : reprise de la configuration de /diet" "Update: uebernehme Konfiguration aus /diet" "Update: keeping the configuration from /diet")"
  for f in etc/hostname etc/TZ etc/diet-net.conf etc/httpd.conf etc/rsyncd.conf etc/passwd etc/group \
           etc/samba/smb.conf etc/samba/shares.conf etc/samba/smbpasswd etc/samba/private etc/dropbear root/.ssh etc/exports etc/diet-notify.conf etc/diet-lang; do
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
  echo "$(tx "Nouvelle installation : reprise des réglages de RAIDiator" "Neuinstallation: uebernehme Einstellungen aus RAIDiator" "New installation: taking over the RAIDiator settings")"
  FRESH=1
  echo "$L" > $N/etc/diet-lang
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
  echo "$(tx "Fuseau horaire : $Z -> $TZS" "Zeitzone: $Z -> $TZS" "Time zone: $Z -> $TZS")"

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
    *) echo "$(tx "Aucun mot de passe admin MD5 trouvé : interface web active seulement après 'diet-webpass'" "Kein MD5-Admin-Passwort gefunden: Web-Oberflaeche erst nach 'diet-webpass' aktiv" "No MD5 admin password found: web interface only after 'diet-webpass'")" ;;
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
  echo "$(tx "Réseau : $(tr '\n' ' ' < $N/etc/diet-net.conf)" "Netz: $(tr '\n' ' ' < $N/etc/diet-net.conf)" "Network: $(tr '\n' ' ' < $N/etc/diet-net.conf)")"
fi

# NFS: Freigaben aus RAIDiator uebernehmen (nur Neuinstallation und nur, wenn NFS dort aktiv war).
# RAIDiator exportiert "/Name" fuer alle (*); DIET exportiert /c/Name nur ins lokale Netz.
if [ "$FRESH" = 1 ] && grep -q '^NFS=1' /etc/default/services 2>/dev/null && grep -q '^"*/' /etc/exports 2>/dev/null; then
  CUR=$(ifconfig eth0 | sed -n 's/.*inet addr:\([0-9.]*\).*/\1/p')
  MASK=$(ifconfig eth0 | sed -n 's/.*Mask:\([0-9.]*\).*/\1/p')
  NETWORK=""; PREFIX=""
  eval `$N/bin/busybox ipcalc -n -p "$CUR" "${MASK:-255.255.255.0}" 2>/dev/null`
  if [ -n "$NETWORK" ] && [ -n "$PREFIX" ]; then
    sed -n "s|^\"*/\([^\" ]*\)\"*[ \t]*\*(\(.*\))|/c/\1 $NETWORK/$PREFIX(\2,no_subtree_check)|p" /etc/exports > $N/etc/exports
    echo "$(tx "Partages NFS repris : $(grep -c '^/' $N/etc/exports) ($NETWORK/$PREFIX)" "NFS-Freigaben uebernommen: $(grep -c '^/' $N/etc/exports) ($NETWORK/$PREFIX)" "NFS shares taken over: $(grep -c '^/' $N/etc/exports) ($NETWORK/$PREFIX)")"
    [ -s $N/etc/exports ] || rm -f $N/etc/exports
  fi
fi

# Systemlaufwerk merken: /dev/md0 (Flex-RAID) oder z.B. /dev/hde1 (X-RAID, Duo v1)
RD=$(awk '$2=="/" && $1 ~ /^\/dev\// {d=$1} END {print d}' /proc/mounts)
[ -b "$RD" ] || RD=/dev/md0
echo "$RD" > $N/etc/diet-rootdev
echo "$(tx "Volume système : $RD" "Systemlaufwerk: $RD" "System volume: $RD")"

# Kein Board-Temperatursensor (Duo v1: temp_0 ist immer 0): Luefter-Grundstufe nicht unter den
# Wert legen, mit dem RAIDiator gerade laeuft (sonst cftpwm/minpwm aus den Boot-Infos, sonst 130).
if [ "$FRESH" = 1 ] && [ "$(cut -d. -f1 /proc/sys/dev/hwmon/temp_0 2>/dev/null)" = "0" ]; then
  binfo() { sed -n "s/^$1:[ \t]*//p" /proc/sys/dev/boot/info; }
  F=$(cat /proc/sys/dev/hwmon/fan0_speed_control 2>/dev/null | tr -cd '0-9')
  MINP=$(binfo minpwm | tr -cd '0-9'); CFT=$(binfo cftpwm | tr -cd '0-9')
  [ -n "$F" ] && [ "$F" -ge 20 ] && [ "$F" -le 255 ] || F=${CFT:-130}
  [ -n "$MINP" ] && [ "$F" -lt "$MINP" ] && F=$MINP
  [ "$F" -ge 20 ] && [ "$F" -le 255 ] || F=130
  sed "s/^FAN_PWM_MIN=[0-9]*/FAN_PWM_MIN=$F/" $N/etc/diet.conf > /tmp/diet.conf.fan && cat /tmp/diet.conf.fan > $N/etc/diet.conf
  rm -f /tmp/diet.conf.fan
  echo "$(tx "Pas de sonde sur la carte : niveau minimal du ventilateur FAN_PWM_MIN=$F, régulation selon la température des disques" "Kein Board-Sensor: Luefter-Grundstufe FAN_PWM_MIN=$F, Regelung nach Plattentemperatur" "No board sensor: fan minimum FAN_PWM_MIN=$F, controlled by disk temperature")"
fi

# --- Umschalten: alte Version als /diet.old behalten ---
rm -rf /diet.old
[ -d /diet ] && { mv /diet /diet.old || fail "$(tx "impossible de déplacer l’ancien /diet" "kann altes /diet nicht verschieben" "cannot move the old /diet")"; }
mv /diet.new /diet || fail "$(tx "impossible de créer /diet" "kann /diet nicht anlegen" "cannot create /diet")"

# --- Weichensteller: /sbin/init muss jederzeit existieren (sonst setzt linuxrc das System zurueck) ---
cp /diet/sbin/init-weiche /sbin/init.neu && chmod 755 /sbin/init.neu || fail "$(tx "impossible de copier l’aiguillage de démarrage" "kann Weichensteller nicht kopieren" "cannot copy the boot switch")"
sh -n /sbin/init.neu || fail "$(tx "aiguillage de démarrage invalide" "Weichensteller fehlerhaft" "boot switch is invalid")"
if ! grep -q "Weichensteller" /sbin/init 2>/dev/null; then
  # Original-init sichern (harter Link, /sbin/init bleibt bestehen)
  rm -f /sbin/init.real
  ln /sbin/init /sbin/init.real 2>/dev/null || cp -p /sbin/init /sbin/init.real || fail "$(tx "impossible de sauvegarder /sbin/init" "kann /sbin/init nicht sichern" "cannot back up /sbin/init")"
fi
[ -x /sbin/init.real ] || fail "$(tx "/sbin/init.real absent" "/sbin/init.real fehlt" "/sbin/init.real missing")"
mv /sbin/init.neu /sbin/init || fail "$(tx "impossible d’installer l’aiguillage de démarrage" "kann Weichensteller nicht setzen" "cannot install the boot switch")"
rm -f /.diet_pending /.raidiator_once
rm -rf /diet-test-alt /sbin/init.alt   # Reste frueherer Testversionen
sync

echo "$(tx "OK : DIET $VER installé. DIET démarrera au prochain redémarrage." "OK: DIET $VER installiert. Beim naechsten Neustart startet DIET." "OK: DIET $VER installed. DIET starts at the next boot.")"
# Beim Systemstart installiert (rc3, nach Update ueber Frontview): nach 2 Minuten automatisch in DIET neu starten
if [ -n "$RUNLEVEL" ]; then
  echo "$(tx "Installation au démarrage : redémarrage automatique dans 2 minutes" "Installation beim Start: automatischer Neustart in 2 Minuten" "Installed at boot: automatic restart in 2 minutes")"
  ( sleep 120; /sbin/reboot ) </dev/null >/dev/null 2>&1 &
fi
lcd "$(tx "DIET: redemarre" "DIET: Neustart!" "DIET: restart!")"
cleanup
exit 0
