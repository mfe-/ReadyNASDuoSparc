/* $Id: page.h,v 1.7 2007-04-20 00:52:12 bzhang Exp $
 * page.h:  Various defines and such for MMU operations on the Sparc for
 *          the Linux kernel.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef _SPARC_PAGE_H
#define _SPARC_PAGE_H

#include <linux/config.h>

#ifdef CONFIG_PADRE_16K_PAGE
#define PAGE_SHIFT	14
#else
#ifdef CONFIG_PADRE_8K_PAGE
#define PAGE_SHIFT	13
#else
#define PAGE_SHIFT   	12
#endif
#endif

#ifndef __ASSEMBLY__
/* I have my suspicions... -DaveM */
#define PAGE_SIZE    (1UL << PAGE_SHIFT)
#else
#define PAGE_SIZE    (1 << PAGE_SHIFT)
#endif
#define PAGE_MASK    (~(PAGE_SIZE-1))

#ifdef __KERNEL__

#ifndef __ASSEMBLY__

extern unsigned long PAGE_NONCACHE_MARK;
#define clear_page(page)	 memset((void *)(page), 0, PAGE_SIZE)
#define copy_page(to,from) 	memcpy((void *)(to), (void *)(from), PAGE_SIZE)
#define clear_user_page(addr, vaddr, page)	clear_page(addr)
#define copy_user_page(to, from, vaddr, page)	copy_page(to, from)

/*
 * .. while these make it easier on the compiler
 */

#ifdef CONFIG_PADRE_16K_PAGE
typedef struct { unsigned long pte1,pte2,pte3,pte4; } pte_t;
typedef unsigned long pmd_t;
typedef unsigned long pgd_t;
typedef unsigned long pgprot_t;
#define pte_val(x)  ((x).pte2 | ((unsigned long long)(x).pte1 << 32))
#define pte_low_val(x)	((x).pte1)
#else
#ifdef CONFIG_PADRE_8K_PAGE
typedef struct { unsigned long pte_low, pte_high; } pte_t;
typedef unsigned long pmd_t;
typedef unsigned long pgd_t;
typedef unsigned long pgprot_t;
#define pte_val(x)  ((x).pte_high | ((unsigned long long)(x).pte_low << 32))
#define pte_low_val(x)	((x).pte_low)
#else
typedef unsigned long pte_t;
typedef unsigned long pmd_t;
typedef unsigned long pgd_t;
typedef unsigned long pgprot_t;
#define pte_val(x)	(x)
#define pte_low_val(x)	(x)
#endif
#endif

#define pmd_val(x)      ((x))
#define pgd_val(x)	(x)
#define pgprot_val(x)	(x)

#define __pte(x)	(x)
#define __pmd(x)    	(x) 
#define __pgd(x)	(x)
#define __pgprot(x)	(x)

#define PTE_MASK    PAGE_MASK
#define TASK_UNMAPPED_BASE  0x20000000

#include <asm-generic/memory_model.h>
#include <asm-generic/page.h>

#else /* !(__ASSEMBLY__) */

#define __pgprot(x)	(x)

#endif /* !(__ASSEMBLY__) */

/* to align the pointer to the (next) page boundary */
#define PAGE_ALIGN(addr)  (((addr)+PAGE_SIZE-1)&PAGE_MASK)

#define PAGE_OFFSET	0x80000000UL
#define __pa(x)			((unsigned long)(x) - PAGE_OFFSET)
#define __va(x)			((void *)((unsigned long) (x) + PAGE_OFFSET))

#define virt_to_phys            __pa
#define phys_to_virt            __va

#define virt_to_page(kaddr)	(mem_map + ((((unsigned long)(kaddr)-PAGE_OFFSET)>>PAGE_SHIFT)))

#define pfn_valid(pfn)		((pfn) < max_mapnr)
#define virt_addr_valid(kaddr)	((((unsigned long)(kaddr)-PAGE_OFFSET)>>PAGE_SHIFT) < max_mapnr)

#define VM_DATA_DEFAULT_FLAGS	(VM_READ | VM_WRITE | VM_EXEC | \
				 VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC)

#endif /* __KERNEL__ */

#endif /* _SPARC_PAGE_H */
