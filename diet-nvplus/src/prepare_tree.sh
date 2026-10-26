#!/bin/sh
# Creates src/tree (the complete DIET root) for build_addon.sh:
#   binaries and libraries from an existing DIET_<version>.bin, scripts/config from src/rootfs.
# Usage: sh prepare_tree.sh ../DIET_2.8.bin
set -e
cd "$(dirname "$0")"
BIN=${1:?usage: prepare_tree.sh DIET_x.y.bin}
rm -rf tree tmp.payload && mkdir tree tmp.payload
dd if="$BIN" bs=512 skip=1 2>/dev/null | tar -x -C tmp.payload
tar -xzf tmp.payload/diet.tgz -C tree
rm -rf tmp.payload
cp -a rootfs/. tree/
echo "tree/ ready: $(cat tree/etc/diet-version)"
