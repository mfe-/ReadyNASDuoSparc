#idn2(1) -- Libidn2 Internationalized Domain Names conversion tool

## SYNOPSIS

`idn2` [OPTION]... [STRINGS]...

## DESCRIPTION

idn2 tool converts DNS domains from UTF-8 to ASCII compatibile encoding
(ACE) form, as used in the DNS protocol. The encoding format is the
Internationalized Domain Name (IDNA2008/TR46) format.

All input strings are expected to be encoded in the locale charset.

To process a string that starts with ```-```, for example ```-foo```,
use ```--``` to signal the end of parameters, as in ```idn2 --quiet --
-foo```.

Mandatory arguments to long options are mandatory for short options too.

  * ```-h, --help```:
    Prints help and exits.

  * ```-V, --version```:
    Prints version and exits.

  * ```-d, --decode```:
    Decode an ACE name according to IDNA2008.

  * ```-l, --lookup```:
    Encode to ACE according to IDNA2008 (the default).

  * ```-r, --register```:
    Registers a label.

  * ```-T, --tr46t```:
    Enable TR#46 transitional processing.

  * ```-N, --tr46nt```:
    Enable TR#46 non-transitional processing (default).

  * ```--no-tr46```:
    Disable TR#46 processing.

  * ```--usestd3asciirules```:
    Enable STD3 ASCII rules.

  * ```--debug```:
    Prints debugging information.

  * ```--quiet```:
    Silent operation.

## Author

Written by Simon Josefsson.

## Reporting bugs

Report bugs to [the gitlab issue tracker of the project](https://gitlab.com/libidn/libidn2/issues).
