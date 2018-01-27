# Copyright (C) 2011-2017 Simon Josefsson

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

AC_INIT([libidn2], [2.0.4], [help-libidn@gnu.org],,
  [https://www.gnu.org/software/libidn/#libidn2])

# Library code modified:                              REVISION++
# Interfaces changed/added/removed:   CURRENT++       REVISION=0
# Interfaces added:                             AGE++
# Interfaces removed:                           AGE=0
AC_SUBST(LT_CURRENT, 3)
AC_SUBST(LT_REVISION, 3)
AC_SUBST(LT_AGE, 3)

#
# Generate version defines for the include file
#
AC_SUBST([IDN2_VERSION_MAJOR], [`echo $PACKAGE_VERSION|cut -d'.' -f1`])
AC_SUBST([IDN2_VERSION_MINOR], [`echo $PACKAGE_VERSION|cut -d'.' -f2`])
AC_SUBST([IDN2_VERSION_PATCH], [`echo $PACKAGE_VERSION|cut -d'.' -f3`])
AC_SUBST([IDN2_VERSION_NUMBER], [`printf '0x%02x%02x%04x' $IDN2_VERSION_MAJOR $IDN2_VERSION_MINOR $IDN2_VERSION_PATCH`])

AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror subdir-objects])
AC_CANONICAL_HOST

AC_PROG_CC
AM_CONDITIONAL(cross_compiling,[test "$cross_compiling" = yes])
AX_PROG_CC_FOR_BUILD
gl_EARLY
unistring_EARLY
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
LT_INIT([win32-dll])
gl_INIT
unistring_INIT
GTK_DOC_CHECK([1.14],[--flavour no-tmpl])

AM_GNU_GETTEXT(external)
AM_GNU_GETTEXT_VERSION(0.19.3)

AX_CODE_COVERAGE

# Non-verbose make
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_ARG_ENABLE([gcc-warnings],
  [AS_HELP_STRING([--enable-gcc-warnings],
		  [turn on lots of GCC warnings (for developers)])],
  [case $enableval in
     yes|no) ;;
     *)      AC_MSG_ERROR([bad value $enableval for gcc-warnings option]) ;;
   esac
   gl_gcc_warnings=$enableval],
  [gl_gcc_warnings=yes]
)

if test "$gl_gcc_warnings" = yes; then
  gl_MANYWARN_ALL_GCC([warnings])
  nw=
  nw="$nw -Wsystem-headers"       # Don't let system headers trigger warnings
  nw="$nw -Wundef"                # All compiler preprocessors support #if UNDEF
  nw="$nw -Wtraditional"          # All compilers nowadays support ANSI C
  nw="$nw -Wconversion"           # These warnings usually don't point to mistakes.
  nw="$nw -Wpadded"               # Padding internal structs doesn't help.
  nw="$nw -Wc++-compat"           # Compile using a C compiler.
  nw="$nw -Wtraditional-conversion" # Too many complaints for now.
  nw="$nw -Wunreachable-code"     # gcc bug 40412
  nw="$nw -Wswitch-default"       # Nothing wrong with default-less switch?

  gl_MANYWARN_COMPLEMENT([warnings], [$warnings], [$nw])
  for w in $warnings; do
    gl_WARN_ADD([$w])
  done

  gl_WARN_ADD([-fdiagnostics-show-option])
  gl_WARN_ADD([-fdiagnostics-color=always]) # colors even when using ccache
fi

AC_ARG_ENABLE(doc,
  AS_HELP_STRING([--disable-doc], [don't generate any documentation]),
    enable_doc=$enableval, enable_doc=yes)
AM_CONDITIONAL(ENABLE_DOC, test "$enable_doc" != "no")

if test "$ac_cv_libunistring" = "yes";then
	AC_SEARCH_LIBS(uc_joining_type, unistring, [], [ac_cv_libunistring=no])
fi

AM_CONDITIONAL(HAVE_LIBUNISTRING, test "$ac_cv_libunistring" = "yes")

AC_CONFIG_FILES([
  Makefile
  doc/Makefile
  doc/reference/Makefile
  doc/reference/version.xml
  examples/Makefile
  lib/idn2.h
  lib/Makefile
  unistring/Makefile
  gl/Makefile
  libidn2.pc
  po/Makefile.in
  src/Makefile
  tests/Makefile
  fuzz/Makefile
])
AC_OUTPUT

AC_MSG_NOTICE([Summary of build options:

  Version:           ${PACKAGE_VERSION}
  Host OS:           ${host_os}
  Install prefix:    ${prefix}
  Compiler:          ${CC}
  Warning flags:     ${WARN_CFLAGS}
  CFLAGS:            ${CFLAGS} ${CPPFLAGS}
  LDFlags:           ${LDFLAGS}
  Documentation:     ${enable_doc}
  Library types:     Shared=${enable_shared}, Static=${enable_static}
  Libiconv:          $am_cv_func_iconv $LTLIBICONV
  Libunistring:      $ac_cv_libunistring $LIBUNISTRING_VERSION $LTLIBUNISTRING
  Valgrind:          ${VALGRIND}
  Version script:    $have_ld_version_script
])
