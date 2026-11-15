#!/bin/sh
# Entfernt DIET wieder vollstaendig und stellt den Original-Start von RAIDiator her.
PATH=/bin:/sbin:/usr/bin:/usr/sbin
LOG=/var/log/diet-install.log
exec >> $LOG 2>&1
HERE=$(pwd)
cleanup() { cd /; case "$HERE" in /tmp/addons/*) rm -rf "$HERE";; esac; }
# Sprache der Meldungen: die von DIET (bei Update), sonst die von RAIDiator (LANGUAGE in /etc/default/services), sonst Englisch
L=$(cat /diet/etc/diet-lang 2>/dev/null)
[ -n "$L" ] || L=$(sed -n 's/^LANGUAGE=\([a-z][a-z]\).*/\1/p' /etc/default/services 2>/dev/null | head -n 1)
case "$L" in fr|de) ;; *) L=en ;; esac
tx() { case $L in fr) printf '%s' "$1" ;; de) printf '%s' "$2" ;; *) printf '%s' "$3" ;; esac; }
echo "==== $(date) $(tx "Suppression de DIET" "DIET entfernen" "Removing DIET") ===="
fail() { echo "$(tx "ERREUR" "FEHLER" "ERROR"): $*"; rm -f /.update_success; echo "{DIET_ERR} $(tx "DIET non supprimé" "DIET nicht entfernt" "DIET not removed"): $*" > /.update_fail; cleanup; exit 1; }
if grep -q "Weichensteller" /sbin/init 2>/dev/null; then
  [ -x /sbin/init.real ] || fail "$(tx "/sbin/init.real absent, /sbin/init reste inchangé" "/sbin/init.real fehlt, /sbin/init bleibt unveraendert" "/sbin/init.real missing, /sbin/init left unchanged")"
  mv /sbin/init.real /sbin/init || fail "$(tx "impossible de restaurer /sbin/init" "kann /sbin/init nicht zuruecksetzen" "cannot restore /sbin/init")"
  echo "$(tx "/sbin/init d’origine restauré" "Original /sbin/init wiederhergestellt" "Original /sbin/init restored")"
fi
rm -f /.diet_pending /.raidiator_once /.diet_once
rm -rf /diet /diet.old /diet.new
sync
echo "$(tx "OK : DIET supprimé" "OK: DIET entfernt" "OK: DIET removed")"
cleanup
exit 0
