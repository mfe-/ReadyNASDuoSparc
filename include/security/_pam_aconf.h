/* _pam_aconf.h.  Generated automatically by configure.  */
/*
 * $Id: _pam_aconf.h.in,v 1.3 2002/09/22 19:53:07 hartmans Exp $
 *
 * 
 */

#ifndef PAM_ACONF_H
#define PAM_ACONF_H

/* lots of stuff gets written to /tmp/pam-debug.log */
/* #undef DEBUG */

/* build libraries with different names (suffixed with 'd') */
/* #undef WITH_LIBDEBUG */

/* provide a global locking facility within libpam */
/* #undef PAM_LOCKING */
#define HAVE_TERMIOS_H 1
#define HAVE_NET_IF_H 1

/* GNU systems as a class, all have the feature.h file */
#define HAVE_FEATURES_H 1
#ifdef HAVE_FEATURES_H
# define _SVID_SOURCE
# define _BSD_SOURCE
# define __USE_BSD
# define __USE_SVID
# define __USE_MISC
# define _GNU_SOURCE
# include <features.h>
#endif /* HAVE_FEATURES_H */

/* we have libcrack available */
#define HAVE_LIBCRACK 1

/* we have libcrypt - its not part of libc (do we need both definitions?) */
#define HAVE_LIBCRYPT 1
#define HAVE_CRYPT_H 1

/* we have libndbm and/or libdb */
#define HAVE_DB_H 1
/* #undef HAVE_NDBM_H */

/* have libfl (Flex) */
#define HAVE_LIBFL 1

/* have libnsl - instead of libc support */
#define HAVE_LIBNSL 1

/* have libpwdb - don't expect this to be important for much longer */
/* #undef HAVE_LIBPWDB */

/* have gethostname() declared */
#define HAVE_GETHOSTNAME 1

#define HAVE_GETTIMEOFDAY 1
#define HAVE_MKDIR 1
#define HAVE_SELECT 1
#define HAVE_STRCSPN 1
#define HAVE_STRDUP 1
#define HAVE_STRERROR 1
#define HAVE_STRSPN 1
#define HAVE_STRSTR 1
#define HAVE_STRTOL 1
#define HAVE_UNAME 1

/* Define if reentrant declarations of standard nss functions are available */
#define HAVE_GETPWNAM_R 1
#define HAVE_GETGRNAM_R 1

/* ugly hack to partially support old pam_strerror syntax */
/* #undef UGLY_HACK_FOR_PRIOR_BEHAVIOR_SUPPORT */

/* read both confs - read /etc/pam.d and /etc/pam.conf in serial */
/* #undef PAM_READ_BOTH_CONFS */

#define HAVE_SYS_CAPABILITY_H 1

#define HAVE_PATHS_H 1
#ifdef HAVE_PATHS_H
#include <paths.h>
#endif
/* location of the mail spool directory */
#define PAM_PATH_MAILDIR "/var/mail"


/* where should we include setfsuid's prototype from? If this is not
   defined, we get it from unistd.h */
#define HAVE_SYS_FSUID_H 1

/* track all memory allocations and liberations */
/* #undef MEMORY_DEBUG */
#ifdef MEMORY_DEBUG
/*
 * this is basically a hack - we need to include a semiarbitrary
 * number of headers to ensure that we don't get silly prototype/macro
 * confusion.
 */
# include <string.h>
# include <stdlib.h>
# include <security/pam_malloc.h>
#endif /* MEMORY_DEBUG */

#endif /* PAM_ACONF_H */
