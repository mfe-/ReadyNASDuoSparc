/* $Id: cache.h,v 1.1.1.1 2006-08-28 17:51:47 bzhang Exp $
 * cache.h:  Cache specific code for the Sparc.  These include flushing
 *           and direct tag/data line access.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef _SPARC_CACHE_H
#define _SPARC_CACHE_H

#include <linux/config.h>

#define L1_CACHE_SHIFT 5
#define L1_CACHE_BYTES 32
#define L1_CACHE_ALIGN(x) ((((x)+(L1_CACHE_BYTES-1))&~(L1_CACHE_BYTES-1)))
#define L1_CACHE_SHIFT_MAX 5	/* largest L1 which this arch supports */

#define __ic3call  __attribute__ ((__section__ (".ic3.init")))
#define __IC3CALL       .section        ".ic3.init","ax"

#define __dc3data  __attribute__ ((__section__ (".dc3.init")))
#define __DC3DATA   .section    ".dc3.init","aw"

#ifndef __ASSEMBLY__
extern unsigned long icmu_ctrl,dcmu_ctrl;
#endif

#endif /* !(_SPARC_CACHE_H) */
