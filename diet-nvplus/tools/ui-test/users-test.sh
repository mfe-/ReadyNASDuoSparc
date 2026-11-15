#!/bin/sh
# Vérifie la gestion des utilisateurs de l'API avec un faux smbpasswd, hors du NAS. Nécessite busybox.
cd "$(dirname "$0")" || exit 1
API=$(pwd)/../../src/rootfs/www/cgi-bin/api
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
mkdir "$T/bin"
printf '#!/bin/sh\nexec busybox httpd "$@"\n' > "$T/bin/httpd"
# faux smbpasswd : journalise ses arguments et ce qu'il reçoit sur l'entrée standard ; échoue pour "refuse"
cat > "$T/bin/smbpasswd" <<EOS
#!/bin/sh
for a; do last=\$a; done
[ "\$last" = refuse ] && exit 1
{ echo "ARGS \$*"; cat; } >> "$T/smb.log"
EOS
chmod +x "$T/bin/httpd" "$T/bin/smbpasswd"
printf 'root:x:0:0:root:/root:/bin/sh\nnobody:x:65534:65534:nobody:/:/bin/false\nadmin:x:98:98::/c/home/admin:/bin/false\nalice:x:1002:100::/c/home/alice:/bin/false\nUSB_HDD_1:x:1004:65534::/c/home/USB_HDD_1:/bin/false\n' > "$T/passwd"
printf 'root:x:0:\nusers:x:100:\n' > "$T/group"
printf '#\n# SMB password file.\n#\nadmin:98:X:Y:[U ]:LCT-1:\nalice:1002:X:Y:[U ]:LCT-1:\n' > "$T/smbpasswd"
fails=0
E="env PATH=$T/bin:$PATH DIET_PASSWD=$T/passwd DIET_SMBPW=$T/smbpasswd DIET_SMBPASSWD=$T/bin/smbpasswd DIET_DATA=/c"
get()  { $E REQUEST_METHOD=GET QUERY_STRING="a=users&l=fr" busybox ash $API | tr -d '\r' | tail -1; }
post() { printf %s "$2" | $E REQUEST_METHOD=POST HTTP_X_DIET=1 CONTENT_LENGTH=${#2} QUERY_STRING="a=$1&l=fr" busybox ash $API | tr -d '\r'; }
ok()   { echo "ok   $1"; }
ko()   { echo "FAIL $1 :: $2" | cut -c1-300; fails=$((fails + 1)); }
check() { if echo "$out" | grep -qE -- "$2"; then ok "$1"; else ko "$1" "$out"; fi; }

out=$(get); check "liste : comptes utilisateurs seulement" '^\[\{"name":"admin","uid":98,"smb":1\},\{"name":"alice","uid":1002,"smb":1\},\{"name":"USB_HDD_1","uid":1004,"smb":0\}\]$'
out=$(post user_set 'name=lea&pw=s%C3%A9same%20%26%2A%27%22%24x');  check "création" 'Utilisateur lea créé'
grep -q '^lea:x:1005:100::/c/home/lea:/bin/false$' "$T/passwd" && ok "création : compte ajouté avec l'uid suivant et le groupe users" || ko "passwd" "$(cat "$T/passwd")"
grep -q '^ARGS -s -a lea$' "$T/smb.log" && [ "$(grep -c "^sésame &\*'\"\$x$" "$T/smb.log")" = 2 ] && ok "création : mot de passe transmis tel quel, deux fois, sur l'entrée standard" || ko "smbpasswd" "$(cat "$T/smb.log")"
: > "$T/smb.log"
out=$(post user_set 'name=alice&pw=nouveau123');  check "changement de mot de passe d'un compte existant" 'Mot de passe de alice modifié'
[ "$(grep -c '^alice:' "$T/passwd")" = 1 ] && ok "changement : pas de compte en double" || ko "doublon" "$(cat "$T/passwd")"
out=$(post user_set 'name=admin&pw=nouveau123');   check "le compte admin peut changer de mot de passe" 'Mot de passe de admin modifié'
out=$(post user_set 'name=root&pw=nouveau123');    check "compte système refusé" '^HTTP/1.1 403'
out=$(post user_set 'name=lea&pw=court');          check "mot de passe trop court refusé" '^HTTP/1.1 400'
out=$(post user_set 'name=Bob&pw=nouveau123');     check "nouveau nom avec majuscule refusé" '^HTTP/1.1 400'
out=$(post user_set 'name=a;reboot&pw=nouveau123'); check "injection dans le nom refusée" '^HTTP/1.1 400'
out=$(post user_set 'name=x%3A0%3A0&pw=nouveau123'); check "deux-points dans le nom refusés" '^HTTP/1.1 400'
out=$(post user_set 'name=refuse&pw=nouveau123');  check "échec de smbpasswd signalé" '^HTTP/1.1 500'
grep -q '^refuse:' "$T/passwd" && ko "compte laissé après échec" "$(cat "$T/passwd")" || ok "échec : le compte n'est pas laissé à moitié créé"
out=$(post user_del 'name=lea');                   check "suppression" 'Utilisateur lea supprimé'
grep -q '^lea:' "$T/passwd" && ko "suppression" "$(cat "$T/passwd")" || ok "suppression : compte retiré"
grep -q '^ARGS -x lea$' "$T/smb.log" && ok "suppression : mot de passe Samba retiré" || ko "smbpasswd -x" "$(cat "$T/smb.log")"
out=$(post user_del 'name=admin');                 check "suppression du compte admin refusée" '^HTTP/1.1 403'
out=$(post user_del 'name=root');                  check "suppression de root refusée" '^HTTP/1.1 403'
out=$(post user_del 'name=inconnu');               check "suppression d'un inconnu refusée" '^HTTP/1.1 404'
[ "$(grep -c . "$T/passwd")" = 5 ] && grep -q '^root:x:0:0:' "$T/passwd" && ok "fichier des comptes intact à la fin" || ko "passwd final" "$(cat "$T/passwd")"
[ "$fails" = 0 ] && echo "Tout passe." || { echo "$fails échec(s)"; exit 1; }
