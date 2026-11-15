#!/bin/sh
# Vérifie le rendu de la page web sur deux états d'un Duo v1 (sain, RAID dégradé simulé). Nécessite node.
cd "$(dirname "$0")" || exit 1
T=$(mktemp) && trap 'rm -f "$T"' EXIT
sed -n '/<script>/,/<\/script>/p' ../../src/rootfs/www/index.html | sed '1d;$d' > "$T"
node render-test.js "$T" duo-ok.json duo-fake-degraded.json
