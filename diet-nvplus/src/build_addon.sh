#!/bin/sh
# Baut RAIDiator-4.1-Add-ons (SPARC) fuer DIET.
# Format (aus Frontview ermittelt): 512 Byte Kopf + unkomprimiertes tar.
#   Kopf:  "addon::name=..,version=..,time=..,size=<Bytes>,md5sum=<md5 der Nutzdaten>,unencrypted=1\n", Nullen bis 512 Byte
#   Bytes 384..511 waeren die Netgear-Signatur -> leer, RAIDiator warnt "nicht signiert" und installiert trotzdem.
#   Ablauf (System > Update > Lokal): Frontview prueft "dd if=X skip=1 bs=512 | md5sum", schreibt /tmp/update_file
#   nach /.new_addons und startet neu. linuxrc packt beim Start nach /tmp/addons/<name> aus
#   (ohne "unencrypted=1" wird vorher mit hwcp/3DES entschluesselt!), danach fuehrt rc3 "sh install.sh" aus.
set -e
cd "$(dirname "$0")"
OUT=${OUT:-out}
VER=$(cat tree/etc/diet-version)
mkdir -p $OUT

mkbin() {  # mkbin <name> <version> <descr> <verzeichnis> <ausgabe>
  name=$1; ver=$2; descr=$3; dir=$4; out=$5
  tmp=$(mktemp -d)
  tar --format=gnu --owner=0 --group=0 --numeric-owner -C "$dir" -cf $tmp/payload.tar .
  size=$(stat -c %s $tmp/payload.tar)
  md5=$(md5sum < $tmp/payload.tar | cut -d' ' -f1)
  hdr="addon::name=$name,version=$ver,time=$(date +%s),size=$size,md5sum=$md5,unencrypted=1"
  [ ${#hdr} -lt 380 ] || { echo "Kopf zu lang"; exit 1; }
  { printf '%s\n' "$hdr"; head -c $((512 - ${#hdr} - 1)) /dev/zero; cat $tmp/payload.tar; } > "$out"
  rm -rf $tmp
  # Selbsttest wie Frontview
  [ "$(dd if="$out" skip=1 bs=512 2>/dev/null | md5sum | cut -d' ' -f1)" = "$md5" ]
  echo "$out: $(stat -c %s "$out") Bytes, md5 $md5"
}

# Systempaket
rm -f DIET/diet.tgz
tar --owner=0 --group=0 --numeric-owner -C tree -czf DIET/diet.tgz .
cp tree/etc/diet-version DIET/diet-version
chmod 755 DIET/install.sh DIET_REMOVE/install.sh

mkbin DIET "$VER" "DIET $VER - schlankes System fuer ReadyNAS NV+ v1 (RAIDiator bleibt als Rueckfall)" DIET "$OUT/DIET_$VER.bin"
mkbin DIET_REMOVE "$VER" "Entfernt DIET und stellt den normalen RAIDiator-Start wieder her" DIET_REMOVE "$OUT/DIET_remove_$VER.bin"
