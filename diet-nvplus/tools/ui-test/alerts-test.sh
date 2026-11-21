#!/bin/sh
# Vérifie le résumé des alertes (diet-alerts) et la langue du système, hors du NAS. Nécessite busybox.
cd "$(dirname "$0")" || exit 1
A=$(pwd)/../../src/rootfs/sbin/diet-alerts
T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
cp ../../src/rootfs/etc/diet-lang.sh "$T/"
printf 'LOGICAL_DRIVE:0:begin=1,status=redundant,dmap=3\nLOGICAL_DRIVE:1:begin=2,status=degraded,dmap=3\nPHYSICAL_DRIVE:0:number=0,device=hdc,major=22,state=online,present=1\nPHYSICAL_DRIVE:1:number=1,device=hde,major=33,state=failed,present=1\n' > "$T/x"
echo 'health=PASSED realloc=0 pending=2 uncorr=0 hours=5' > "$T/smart.hdc"
fails=0
run() { echo "$1" > "$T/diet-lang"; DIET_ETC=$T DIET_XRAID=$T/x DIET_MDSTAT=/dev/null DIET_RUN=$T busybox ash "$A"; }
check() { if [ "$2" = "$3" ]; then echo "ok   $1"; else echo "FAIL $1 :: [$2]"; fails=$((fails + 1)); fi; }
check "français" "$(run fr)" "RAID dégradé (volume 1=degraded) ; disque hors du RAID (hde=failed) ; hdc : 2 secteurs en attente"
check "allemand" "$(run de)" "RAID beeinträchtigt (Volume 1=degraded) ; Platte nicht im RAID (hde=failed) ; hdc: 2 Sektoren ausstehend"
check "anglais"  "$(run en)" "RAID degraded (volume 1=degraded) ; disk out of the RAID (hde=failed) ; hdc: 2 pending sectors"
check "anglais si la langue est inconnue" "$(run xx)" "$(run en)"
sed -i 's/degraded/redundant/; s/failed/online/' "$T/x"; rm "$T/smart.hdc"
check "rien quand tout va bien" "$(run fr)" ""
[ "$fails" = 0 ] && echo "Tout passe." || { echo "$fails échec(s)"; exit 1; }
