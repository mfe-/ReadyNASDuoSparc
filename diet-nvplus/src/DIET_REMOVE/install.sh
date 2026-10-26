#!/bin/sh
# Entfernt DIET wieder vollstaendig und stellt den Original-Start von RAIDiator her.
PATH=/bin:/sbin:/usr/bin:/usr/sbin
LOG=/var/log/diet-install.log
exec >> $LOG 2>&1
HERE=$(pwd)
cleanup() { cd /; case "$HERE" in /tmp/addons/*) rm -rf "$HERE";; esac; }
echo "==== $(date) DIET entfernen ===="
fail() { echo "FEHLER: $*"; rm -f /.update_success; echo "{DIET_ERR} DIET nicht entfernt: $*" > /.update_fail; cleanup; exit 1; }
if grep -q "Weichensteller" /sbin/init 2>/dev/null; then
  [ -x /sbin/init.real ] || fail "/sbin/init.real fehlt, /sbin/init bleibt unveraendert"
  mv /sbin/init.real /sbin/init || fail "kann /sbin/init nicht zuruecksetzen"
  echo "Original /sbin/init wiederhergestellt"
fi
rm -f /.diet_pending /.raidiator_once /.diet_once
rm -rf /diet /diet.old /diet.new
sync
echo "OK: DIET entfernt"
cleanup
exit 0
