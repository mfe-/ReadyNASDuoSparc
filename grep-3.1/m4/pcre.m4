# pcre.m4 - check for libpcre support

# Copyright (C) 2010-2017 Free Software Foundation, Inc.
# This file is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

AC_DEFUN([gl_FUNC_PCRE],
[
  AC_ARG_ENABLE([perl-regexp],
    AC_HELP_STRING([--disable-perl-regexp],
                   [disable perl-regexp (pcre) support]),
    [case $enableval in
       yes|no) test_pcre=$enableval;;
       *) AC_MSG_ERROR([invalid value $enableval for --disable-perl-regexp]);;
     esac],
    [test_pcre=maybe])

  AC_SUBST([PCRE_CFLAGS])
  AC_SUBST([PCRE_LIBS])
  use_pcre=no

  if test $test_pcre != no; then
    PKG_CHECK_MODULES([PCRE], [libpcre], [], [: ${PCRE_LIBS=-lpcre}])

    AC_CACHE_CHECK([for pcre_compile], [pcre_cv_have_pcre_compile],
      [pcre_saved_CFLAGS=$CFLAGS
       pcre_saved_LIBS=$LIBS
       CFLAGS="$CFLAGS $PCRE_CFLAGS"
       LIBS="$PCRE_LIBS $LIBS"
       AC_LINK_IFELSE(
         [AC_LANG_PROGRAM([[#include <pcre.h>
                          ]],
            [[pcre *p = pcre_compile (0, 0, 0, 0, 0);
              return !p;]])],
         [pcre_cv_have_pcre_compile=yes],
         [pcre_cv_have_pcre_compile=no])
       CFLAGS=$pcre_saved_CFLAGS
       LIBS=$pcre_saved_LIBS])

    if test "$pcre_cv_have_pcre_compile" = yes; then
      use_pcre=yes
    elif test $test_pcre = maybe; then
      AC_MSG_WARN([AC_PACKAGE_NAME will be built without pcre support.])
    else
      AC_MSG_ERROR([pcre support not available])
    fi
  fi

  if test $use_pcre = yes; then
    AC_DEFINE([HAVE_LIBPCRE], [1],
      [Define to 1 if you have the Perl Compatible Regular Expressions
       library (-lpcre).])
  else
    PCRE_CFLAGS=
    PCRE_LIBS=
  fi
])
