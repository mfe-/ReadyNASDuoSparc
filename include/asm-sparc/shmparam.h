/* $Id: shmparam.h,v 1.1.1.1 2006-08-28 17:51:50 bzhang Exp $ */
#ifndef _ASMSPARC_SHMPARAM_H
#define _ASMSPARC_SHMPARAM_H

#define __ARCH_FORCE_SHMLBA 	1

extern int vac_cache_size;
#define SHMLBA (vac_cache_size ? vac_cache_size : \
		(sparc_cpu_model == sun4c ? (64 * 1024) : \
		 (sparc_cpu_model == sun4 ? (128 * 1024) : PAGE_SIZE)))

#endif /* _ASMSPARC_SHMPARAM_H */
