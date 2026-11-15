#!/bin/sh
# Vérifie les réglages système et l'envoi Telegram de l'API, hors du NAS, avec de faux wget et httpd. Nécessite busybox.
cd "$(dirname "$0")" || exit 1
R=$(pwd)/../../src/rootfs; API=$R/www/cgi-bin/api
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
mkdir -p "$T/bin" "$T/etc/samba"
printf '#!/bin/sh\nexec busybox httpd "$@"\n' > "$T/bin/httpd"
# faux wget : journalise ses arguments, répond comme Telegram selon le jeton
cat > "$T/bin/wget" <<EOS
#!/bin/sh
echo "\$*" >> "$T/wget.log"
case "\$*" in *bot111:bon/*) echo '{"ok":true,"result":{}}' ;; *) echo 'wget: server returned error: HTTP/1.1 401 Unauthorized' >&2 ;; esac
EOS
chmod +x "$T/bin/httpd" "$T/bin/wget"
echo nas-test > "$T/etc/hostname"; echo 'PST8PDT,M3.2.0,M11.1.0' > "$T/etc/TZ"
printf 'NET=dhcp\nFALLBACK_IP=192.168.1.10\nNETMASK=255.255.255.0\n' > "$T/etc/diet-net.conf"
printf '[global]\n    workgroup = VOLUME\n    netbios name = NAS-TEST\n    security = user\n' > "$T/etc/samba/smb.conf"
fails=0
E="env PATH=$T/bin:$PATH DIET_ETC=$T/etc DIET_PASSWD=$T/etc/passwd DIET_NOTIFY=$R/sbin/diet-notify DIET_WGET=$T/bin/wget"
get()  { $E REQUEST_METHOD=GET QUERY_STRING="a=sys&l=fr" busybox ash $API | tr -d '\r' | tail -1; }
post() { printf %s "$2" | $E REQUEST_METHOD=POST HTTP_X_DIET=1 CONTENT_LENGTH=${#2} QUERY_STRING="a=$1&l=fr" busybox ash $API | tr -d '\r'; }
ok()   { echo "ok   $1"; }
ko()   { echo "FAIL $1 :: $2" | cut -c1-300; fails=$((fails + 1)); }
check() { if echo "$out" | grep -qE -- "$2"; then ok "$1"; else ko "$1" "$out"; fi; }
TZP='CET-1CEST%2CM3.5.0%2CM10.5.0%2F3'
BASE="host=nas-test&tz=$TZP&net=dhcp&ip=&mask=&gw=&dns=&tgtoken=&tgchat="

out=$(get); check "lecture des réglages" '"host":"nas-test","tz":"PST8PDT,M3.2.0,M11.1.0","net":"dhcp"'
echo "$out" | python3 -I -c 'import json,sys; json.load(sys.stdin)' 2>/dev/null && ok "lecture : JSON valide" || ko "JSON" "$out"
            check "lecture : le jeton n'est jamais renvoyé" '"tgset":0,"tgchat":""'
out=$(post sys_set "$BASE");                         check "enregistrement du fuseau" 'Enregistré'
[ "$(cat "$T/etc/TZ")" = 'CET-1CEST,M3.5.0,M10.5.0/3' ] && ok "fuseau écrit" || ko "TZ" "$(cat "$T/etc/TZ")"
grep -q '^NET=dhcp$' "$T/etc/diet-net.conf" && grep -q '^FALLBACK_IP=192.168.1.10$' "$T/etc/diet-net.conf" && ok "DHCP : adresse de secours conservée" || ko "net" "$(cat "$T/etc/diet-net.conf")"
out=$(post sys_set "host=mon-nas&tz=$TZP&net=static&ip=192.168.1.50&mask=255.255.255.0&gw=192.168.1.1&dns=1.1.1.1%209.9.9.9&tgtoken=&tgchat=")
                                                     check "adresse fixe et nouveau nom" 'Enregistré'
[ "$(cat "$T/etc/diet-net.conf")" = "$(printf 'NET=static\nIPADDR=192.168.1.50\nNETMASK=255.255.255.0\nGATEWAY=192.168.1.1\nDNS="1.1.1.1 9.9.9.9"')" ] && ok "réseau fixe écrit" || ko "net" "$(cat "$T/etc/diet-net.conf")"
[ "$(cat "$T/etc/hostname")" = mon-nas ] && grep -q '^    netbios name = MON-NAS$' "$T/etc/samba/smb.conf" && ok "nom écrit, y compris dans Samba" || ko "nom" "$(cat "$T/etc/samba/smb.conf")"
( NET=; . "$T/etc/diet-net.conf"; [ "$DNS" = "1.1.1.1 9.9.9.9" ] ) && ok "le fichier réseau se relit comme au démarrage" || ko "source" "-"
for bad in 'ip=999.1.1.1' 'ip=1.2.3' 'ip=1.2.3.4%3Breboot' 'mask=abc' 'gw=1.2.3.4.5' 'dns=1.1.1.1%20x'; do
  b="host=mon-nas&tz=$TZP&net=static&ip=192.168.1.50&mask=255.255.255.0&gw=&dns="; b=$(echo "$b" | sed "s/${bad%%=*}=[^&]*/$bad/")
  out=$(post sys_set "$b&tgtoken=&tgchat="); check "refus de $bad" '^HTTP/1.1 400'
done
out=$(post sys_set "host=Mon%20NAS&tz=$TZP&net=dhcp&tgchat=");      check "nom invalide refusé" '^HTTP/1.1 400'
out=$(post sys_set "host=x&tz=CET%3Breboot&net=dhcp&tgchat=");     check "fuseau avec injection refusé" '^HTTP/1.1 400'
out=$(post sys_set "host=x&tz=$TZP&net=wifi&tgchat=");             check "mode réseau inconnu refusé" '^HTTP/1.1 400'
[ "$(cat "$T/etc/hostname")" = mon-nas ] && ok "rien n'est écrit après un refus" || ko "hostname" "$(cat "$T/etc/hostname")"
out=$(post notify_test "");                                        check "test sans configuration refusé" '^HTTP/1.1 400'
out=$(post sys_set "host=mon-nas&tz=$TZP&net=dhcp&tgtoken=&tgchat=42");        check "discussion sans jeton refusée" 'Jeton Telegram manquant'
out=$(post sys_set "host=mon-nas&tz=$TZP&net=dhcp&tgtoken=abc&tgchat=42");     check "jeton mal formé refusé" '^HTTP/1.1 400'
out=$(post sys_set "host=mon-nas&tz=$TZP&net=dhcp&tgtoken=111%3Abon&tgchat=42%3Bx"); check "identifiant mal formé refusé" '^HTTP/1.1 400'
out=$(post sys_set "host=mon-nas&tz=$TZP&net=dhcp&tgtoken=111%3Abon&tgchat=-1001234"); check "Telegram enregistré" 'Enregistré'
[ "$(cat "$T/etc/diet-notify.conf")" = "$(printf 'TG_TOKEN=111:bon\nTG_CHAT=-1001234')" ] && ok "fichier Telegram écrit" || ko "notify.conf" "$(cat "$T/etc/diet-notify.conf")"
[ "$(stat -c %a "$T/etc/diet-notify.conf")" = 600 ] && ok "fichier Telegram lisible par root seulement" || ko "droits" "$(stat -c %a "$T/etc/diet-notify.conf")"
out=$(get);                                                        check "lecture : jeton masqué, identifiant visible" '"tgset":1,"tgchat":"-1001234"'
echo "$out" | grep -q '111:bon' && ko "jeton renvoyé" "$out" || ok "le jeton n'apparaît pas dans la réponse"
out=$(post sys_set "host=mon-nas&tz=$TZP&net=dhcp&tgtoken=&tgchat=77");        check "jeton vide = jeton conservé" 'Enregistré'
grep -q '^TG_TOKEN=111:bon$' "$T/etc/diet-notify.conf" && grep -q '^TG_CHAT=77$' "$T/etc/diet-notify.conf" && ok "jeton conservé, identifiant changé" || ko "notify.conf" "$(cat "$T/etc/diet-notify.conf")"
out=$(post notify_test "");                                        check "notification de test envoyée" 'Notification envoyée'
grep -q -- '--post-data chat_id=77&text=%[0-9a-f%]* https://api.telegram.org/bot111:bon/sendMessage$' "$T/wget.log" && ok "requête Telegram bien formée (texte encodé)" || ko "wget" "$(tail -1 "$T/wget.log")"
printf 'TG_TOKEN=222:faux\nTG_CHAT=77\n' > "$T/etc/diet-notify.conf"
out=$(post notify_test "");                                        check "échec d'envoi signalé avec la raison" '^HTTP/1.1 502'
                                                                   check "raison lisible" '401 Unauthorized'
out=$(post sys_set "host=mon-nas&tz=$TZP&net=dhcp&tgtoken=&tgchat=");          check "désactivation" 'Enregistré'
[ ! -e "$T/etc/diet-notify.conf" ] && ok "identifiant vide = notifications désactivées" || ko "conf restante" "-"
[ "$fails" = 0 ] && echo "Tout passe." || { echo "$fails échec(s)"; exit 1; }
