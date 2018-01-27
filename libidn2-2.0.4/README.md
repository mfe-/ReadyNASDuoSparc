[![build status](https://gitlab.com/libidn/libidn2/badges/master/build.svg)](https://gitlab.com/libidn/libidn2/pipelines)
[![coverage status](https://gitlab.com/libidn/libidn2/badges/master/coverage.svg)](https://libidn.gitlab.io/libidn2/coverage)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/12080/badge.svg)](https://scan.coverity.com/projects/libidn2)


# Libidn2 README -- Introduction information

Libidn2 is a free software implementation of IDNA2008, Punycode and TR46.
Its purpose is to encode and decode internationalized domain names.

 * [RFC 5890](https://tools.ietf.org/html/rfc5890)
 * [RFC 5891](https://tools.ietf.org/html/rfc5891)
 * [RFC 5892](https://tools.ietf.org/html/rfc5892)
 * [RFC 5893](https://tools.ietf.org/html/rfc5893)
 * [TR46](http://www.unicode.org/reports/tr46/)

The library contains functionality to convert internationalized domain names
to and from ASCII Compatible Encoding (ACE), following the IDNA2008 and TR46
standards.

The API consists of two main functions, ```idn2_to_ascii_8z``` for
converting data from UTF-8 to ASCII Compatible Encoding (ACE), and
```idn2_to_unicode_8z8z``` to convert ACE names into UTF-8
format. There are several variations of these main functions, which
accept UTF-32, or input in the local system encoding. All functions
assume zero-terminated strings.

This library is backwards (API) compatible with the [libidn
library](https://www.gnu.org/software/libidn/).  Replacing the
```idna.h``` header with ```idn2.h``` into a program is sufficient to
switch the application from IDNA2003 to IDNA2008 as supported by this
library.

Libidn2 is believed to be a complete IDNA2008 and TR46 implementation,
it contains an extensive test-suite, and is included in the continuous
fuzzing project [OSS-Fuzz](https://bugs.chromium.org/p/oss-fuzz/issues/list?q=libidn2).


# License

The installed C library libidn2 is dual-licensed under LGPLv3+|GPLv2+,
while the rest of the package is GPLv3+.  See the file
[COPYING](COPYING) for detailed information.


# Online docs

[API reference](https://libidn.gitlab.io/libidn2/reference/api-index-full.html)

[Manual](https://libidn.gitlab.io/libidn2/manual/libidn2.html)


# Obtaining the source

The homepage of libidn2: https://www.gnu.org/software/libidn/#libidn2

Software releases of libidn2 can be downloaded from
https://ftp.gnu.org/gnu/libidn/ and ftp://ftp.gnu.org/gnu/libidn/

Development of libidn2 is organized [through GitLab website](https://gitlab.com/libidn/libidn2),
and there is [an issue tracker for reporting bugs](https://gitlab.com/libidn/libidn2/issues).


# Dependencies

To build Libidn2 you will need a POSIX shell to run ./configure and
the Unix make tool.

 * [Bash](https://www.gnu.org/software/bash/)
 * [Make](https://www.gnu.org/software/make/)

The shared libidn2 library uses GNU libunistring for Unicode
processing and GNU libiconv for character set conversion.  You should
install them before building and installing libidn2.  See the
following links for more information on these packages:

 * [Unistring](https://www.gnu.org/software/libunistring/)
 * [iconv](https://www.gnu.org/software/libiconv/)

Note that the iconv dependency is optional -- it is required for the
functions involving locale to UTF conversions -- but is recommended.

If you wish to build the project from version controlled sources,
rebuild all generated files (e.g., run autoreconf), or modify some
source code files, you will need to have additional tools installed.
None of the following tools are necessary if you build Libidn2 in the
usual way (i.e., ./configure && make).

 * [Automake](https://www.gnu.org/software/automake/)
 * [Autoconf](https://www.gnu.org/software/autoconf/)
 * [Libtool](https://www.gnu.org/software/libtool/)
 * [Gettext](https://www.gnu.org/software/gettext/)
 * [Texinfo](https://www.gnu.org/software/texinfo/)
 * [Gperf](https://www.gnu.org/software/gperf/)
 * [Gengetopt](https://www.gnu.org/software/gengetopt/)
 * [Tar](https://www.gnu.org/software/tar/)
 * [Gzip](https://www.gnu.org/software/gzip/)
 * [Texlive & epsf](https://www.tug.org/texlive/) (for PDF manual)
 * [GTK-DOC](https://www.gtk.org/gtk-doc/) (for API manual)
 * [Git](https://git-scm.com/)
 * [Perl](https://www.cpan.org/) (HTTPS: www.cpan.org uses an invalid security certificate)
 * [Valgrind](http://valgrind.org/) (optional) (No HTTPS at all)
 * [abi-compliance-checker]
 * [ronn](https://rtomayko.github.io/ronn/)

The software is typically distributed with your operating system, and
the instructions for installing them differ.  Here are some hints.

gNewSense/Debian/Ubuntu:
```
apt-get install git autoconf automake libtool texinfo gperf git2cl
apt-get install libunistring-dev gtk-doc-tools valgrind gengetopt
apt-get install abi-compliance-checker ruby-ronn
```


# Contributing

See [the contributing document](CONTRIBUTING.md).


# Estimating code coverage

Dependencies:
 * [lcov](https://linux-test-project.github.io/) (for code coverage)

To test the code coverage of the test suite use the following:
```
$ ./configure --enable-code-coverage
$ make && make check && make code-coverage-capture
```

The current coverage report can be found [here](https://libidn.gitlab.io/libidn2/coverage/).


# Cross-compiling

It is possible to cross-compile libidn2.  It is expected your cross
compiler toolchain to have a specific prefix to the target host.  For
example compiling for Windows with mingw64 (with prefix
```i686-w64-mingw32```) can be done the following way:

```
./configure --host=i686-w64-mingw32 && make
```

After `./bootstrap`ing you find the `INSTALL` file in the main project
directory including generic instructions about cross-compilation.
