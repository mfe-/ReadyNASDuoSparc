# Libidn2 CONTRIBUTING -- Information for developers
Copyright (C) 2011-2017 Simon Josefsson
See the end for copying conditions.

This file contains instructions for developers and advanced users.
See README for the additional tools you need to have installed.

## Obtaining sources

Download the version controlled sources:
```
$ git clone https://gitlab.com/libidn/libidn2.git
$ cd libidn2
```

## Building the project

Prepare building with
```
$ ./bootstrap
$ ./configure --enable-gtk-doc --enable-gtk-doc-pdf --enable-gcc-warnings --enable-valgrind-tests
```

You may want to use --gnulib-srcdir=/foo/bar/gnulib to avoid having to
checkout gnulib every time.  Make sure the gnulib directory you point
to is up to date.

Then build the project normally:
```
$ make
$ make check
```

## Test suite:

New functionality should be accompanied by a test case which verifies
the correctness of the new functionality as well as under failure.
The libidn2 test suite is run on "make check".

When submitting patches it is recommended to open a new merge request
[on the gitlab site](https://gitlab.com/libidn/libidn2), to force the
changes to pass the automated test suite.

## Release process

The release process consists of:

 * Make sure version number is updated in configure.ac.
 * Make sure library version is updated in configure.ac.
 * Prepare NEWS.
 * Do 'make release'

Happy hacking!

----------------------------------------------------------------------
This file is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

This file is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this file.  If not, see <https://www.gnu.org/licenses/>.
