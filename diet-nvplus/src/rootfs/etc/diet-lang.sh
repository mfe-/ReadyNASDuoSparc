# Systemsprache fuer Meldungen (Protokolle, diet-status, Telegram): /etc/diet-lang = fr | de | en, Standard en.
# Einbinden mit: . /etc/diet-lang.sh   Benutzung: tx "francais" "deutsch" "english"
L=$(cat ${DIET_ETC:-/etc}/diet-lang 2>/dev/null)
case "$L" in fr|de|en) ;; *) L=en ;; esac
tx() { case $L in fr) printf '%s' "$1" ;; de) printf '%s' "$2" ;; *) printf '%s' "$3" ;; esac; }
