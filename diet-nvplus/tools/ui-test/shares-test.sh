#!/bin/sh
# Vérifie la gestion des partages de l'API sur une copie de configuration, hors du NAS. Nécessite busybox.
cd "$(dirname "$0")" || exit 1
API=../../src/rootfs/www/cgi-bin/api
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
mkdir -p "$T/c/backup" "$T/c/media"
cat > "$T/shares.conf" <<EOC
[backup]
  path = $T/c/backup
  comment = "Backup Share"
  writeable = 1
  guest ok = 1

[media]
  path = $T/c/media
  admin users = "admin","Administrator"
  writeable = 1
  guest ok = 1

[twonkymedia]
  path = $T/c/twonkymedia
  writeable = 1
EOC
fails=0
get()  { env DIET_SHARES="$T/shares.conf" DIET_DATA="$T/c" REQUEST_METHOD=GET QUERY_STRING="a=shares" busybox ash $API | tr -d '\r' | tail -1; }
post() { printf %s "$2" | env DIET_SHARES="$T/shares.conf" DIET_DATA="$T/c" REQUEST_METHOD=POST HTTP_X_DIET=1 CONTENT_LENGTH=${#2} QUERY_STRING="a=$1" busybox ash $API | tr -d '\r'; }
check() { if echo "$out" | grep -qE -- "$2"; then echo "ok   $1"; else echo "FAIL $1 :: $out" | cut -c1-300; fails=$((fails + 1)); fi; }
nocheck() { if echo "$out" | grep -qE -- "$2"; then echo "FAIL $1 :: $out" | cut -c1-300; fails=$((fails + 1)); else echo "ok   $1"; fi; }

out=$(get);                                   check "liste : 3 partages lus" '"name":"backup".*"name":"media".*"name":"twonkymedia"'
                                              check "liste : droits et invité lus" '"name":"backup","path":"[^"]*","ro":0,"guest":1,"exists":1'
                                              check "liste : dossier absent et pas d invité par défaut" '"name":"twonkymedia","path":"[^"]*","ro":0,"guest":0,"exists":0'
echo "$out" | python3 -I -c 'import json,sys; json.load(sys.stdin)' 2>/dev/null && echo "ok   liste : JSON valide" || { echo "FAIL JSON invalide"; fails=$((fails + 1)); }
out=$(post share_add 'name=photos');          check "création" 'Partage photos créé'
[ -d "$T/c/photos" ] && echo "ok   création : dossier créé" || { echo "FAIL dossier non créé"; fails=$((fails + 1)); }
out=$(get);                                   check "création : visible dans la liste" '"name":"photos","path":"[^"]*/c/photos","ro":0,"guest":1,"exists":1'
out=$(post share_add 'name=Photos');          check "doublon refusé (insensible à la casse)" '^HTTP/1.1 409'
out=$(post share_add 'name=global');          check "nom réservé refusé" '^HTTP/1.1 400'
out=$(post share_add 'name=a%2F..%2Fetc');    check "nom avec chemin refusé" '^HTTP/1.1 400'
out=$(post share_add 'name=x;reboot');        check "injection refusée" '^HTTP/1.1 400'
[ "$(ls "$T/c" | wc -l)" = 3 ] && echo "ok   aucun dossier parasite créé" || { echo "FAIL dossiers: $(ls "$T/c")"; fails=$((fails + 1)); }
out=$(post share_set 'name=media&ro=1&guest=0'); check "réglage" 'Partage media mis à jour'
out=$(get);                                   check "réglage : lecture seule sans invité" '"name":"media","path":"[^"]*","ro":1,"guest":0'
                                              check "réglage : les autres partages sont intacts" '"name":"backup","path":"[^"]*","ro":0,"guest":1'
grep -q 'admin users = "admin","Administrator"' "$T/shares.conf" && echo "ok   réglage : autres options du partage conservées" || { echo "FAIL options perdues"; fails=$((fails + 1)); }
[ "$(grep -c 'writeable' "$T/shares.conf")" = 4 ] && echo "ok   réglage : pas de ligne en double" || { echo "FAIL doublons"; fails=$((fails + 1)); }
out=$(post share_set 'name=media&ro=2&guest=0'); check "réglage invalide refusé" '^HTTP/1.1 400'
out=$(post share_del 'name=twonkymedia');     check "retrait" 'Partage twonkymedia retiré'
out=$(get);                                   nocheck "retrait : absent de la liste" 'twonkymedia'
                                              check "retrait : les autres restent" '"name":"backup".*"name":"media".*"name":"photos"'
out=$(post share_del 'name=media'); [ -d "$T/c/media" ] && echo "ok   retrait : le dossier est conservé" || { echo "FAIL dossier supprimé"; fails=$((fails + 1)); }
out=$(post share_del 'name=inconnu');         check "retrait d un partage inconnu refusé" '^HTTP/1.1 404'
[ -f "$T/shares.conf.bak" ] && echo "ok   sauvegarde .bak présente" || { echo "FAIL pas de sauvegarde"; fails=$((fails + 1)); }
[ "$fails" = 0 ] && echo "Tout passe." || { echo "$fails échec(s)"; exit 1; }
