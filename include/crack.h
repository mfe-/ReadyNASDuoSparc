#ifndef _CRACK_H
#define _CRACK_H

/*
  copyright:
    Copyright (C) 1998, 1999 Jean Pierre LeJacq <jplejacq@quoininc.com>

    Distributed under the GNU GENERAL PUBLIC LICENSE.

  description:
    cracklib - a pro-active password sanity library.
*/


static const char CRACKLIB_DICTPATH[] = "/var/cache/cracklib/cracklib_dict";
/*
  Directory and prefix of the password dictionary database used by
  several of the utilities provided with the cracklib package.  None
  of the functions in libcrack.a actually use this.  If you want to
  use the same database as these utilities, use this constant as the
  second argument to FascistCheck().
*/


extern char const* FascistCheck(char const password[], char const dictpath[]);
/*
  inputs:
    password is the user chosen potential password.

    dictpath is the full path name + filename prefix of the cracklib
    dictionary database, which is hardcoded to CRACKLIB_DICTPATH in
    several of the utility programs that come with cracklib.
  return:
    The NULL pointer for a good password, or a pointer to a diagnostic
    string if it is a bad password.
*/


#endif
