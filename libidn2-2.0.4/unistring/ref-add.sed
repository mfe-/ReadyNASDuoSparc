/^# Packages using this file: / {
  s/# Packages using this file://
  ta
  :a
  s/ libidn2 / libidn2 /
  tb
  s/ $/ libidn2 /
  :b
  s/^/# Packages using this file:/
}
