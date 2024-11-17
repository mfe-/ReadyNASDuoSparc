/* $Id: pgtable.h,v 1.8 2007-12-05 23:32:55 bzhang Exp $ */
#ifndef _SPARC_PGTABLE_H
#define _SPARC_PGTABLE_H

/*  asm-sparc/pgtable.h:  Defines and functions used to work
 *                        with Sparc page tables.
 *
 *  Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 *  Copyright (C) 1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 */
#include <asm-generic/4level-fixup.h>
#include <linux/config.h>
#include <linux/spinlock.h>
#include <linux/swap.h>
#include <asm/types.h>
#include <asm/system.h>
#include <asm/padre0.h>
#include <asm/page.h>

#ifndef __ASSEMBLY__

struct vm_area_struct;
struct page;

#define pte_ERROR(e)   __builtin_trap()
#define pmd_ERROR(e)   __builtin_trap()
#define pgd_ERROR(e)   __builtin_trap()

#define PMD_SHIFT		22
#define PMD_SIZE        	(1UL << PMD_SHIFT)
#define PMD_MASK        	(~(PMD_SIZE-1))
#define PMD_ALIGN(__addr) 	(((__addr) + ~PMD_MASK) & PMD_MASK)
#define PGDIR_SHIFT     	22
#define PGDIR_SIZE      	(1UL << PGDIR_SHIFT)
#define PGDIR_MASK      	(~(PGDIR_SIZE-1))
#ifdef CONFIG_PADRE_16K_PAGE
#define PTRS_PER_PTE    	256
#else

#ifdef CONFIG_PADRE_8K_PAGE
#define PTRS_PER_PTE    	512
#else
#define PTRS_PER_PTE    	1024
#endif
#endif

#define PTRS_PER_PMD    	1
#define PTRS_PER_PGD    	1024
#define USER_PTRS_PER_PGD	(TASK_SIZE/PGDIR_SIZE)
#define FIRST_USER_PGD_NR	0
#define FIRST_USER_ADDRESS      0

#define _PAGE_CHG_MASK  (PAGE_MASK | _PAGE_D)

#define _PAGE_P         (_PAGE_V | _PAGE_C)
#define _PAGE_FILE		0x2

#ifdef CONFIG_PADRE_DCACHE_WT
#undef  _PAGE_P
#define _PAGE_P         (_PAGE_V | _PAGE_C | _PAGE_T)
#endif

#define _PAGE_USER              (_PAGE_U | _PAGE_R | _PAGE_X)

#define PAGE_NONE      __pgprot(0)
#define PAGE_SHARED    __pgprot(_PAGE_W | _PAGE_U | _PAGE_R | _PAGE_X | _PAGE_P)
#define PAGE_COPY      __pgprot(_PAGE_U | _PAGE_R | _PAGE_X | _PAGE_P)
#define PAGE_READONLY  __pgprot(_PAGE_U | _PAGE_R | _PAGE_X | _PAGE_P)
#define PAGE_KERNEL    __pgprot(_PAGE_W |  _PAGE_R | _PAGE_X | _PAGE_D | _PAGE_A | _PAGE_P)

#define _PAGE_TABLE    __pgprot(_PAGE_W | _PAGE_D | _PAGE_R | _PAGE_X | _PAGE_P | _PAGE_U)
#define _KERNPG_TABLE  __pgprot(_PAGE_W | _PAGE_D | _PAGE_R | _PAGE_X | _PAGE_P )

/* Top-level page directory */
#define swapper_pg_dir ((pgd_t *) 0)

#define __P000  PAGE_NONE
#define __P001  PAGE_READONLY
#define __P010  PAGE_COPY
#define __P011  PAGE_COPY
#define __P100  PAGE_READONLY
#define __P101  PAGE_READONLY
#define __P110  PAGE_COPY
#define __P111  PAGE_COPY

#define __S000  PAGE_NONE
#define __S001  PAGE_READONLY
#define __S010  PAGE_SHARED
#define __S011  PAGE_SHARED
#define __S100  PAGE_READONLY
#define __S101  PAGE_READONLY
#define __S110  PAGE_SHARED
#define __S111  PAGE_SHARED

/*
 * ZERO_PAGE is a global shared page that is always zero: used
 * for zero-mapped memory areas etc..
 */
extern unsigned long empty_zero_page;

#define ZERO_PAGE(vaddr) (virt_to_page(&empty_zero_page))

static inline void  set_pte(pte_t *pteptr, pte_t pteval)
{
#ifdef CONFIG_PADRE_16K_PAGE
	if(pteval.pte1 >= PAGE_NONCACHE_MARK) {
		pteval.pte1 &= ~_PAGE_C;
		pteval.pte2 &= ~_PAGE_C;
		pteval.pte3 &= ~_PAGE_C;
		pteval.pte4 &= ~_PAGE_C;
	}

#else
#ifdef CONFIG_PADRE_8K_PAGE
	if(pteval.pte_low >= PAGE_NONCACHE_MARK) {
		pteval.pte_low &= ~_PAGE_C;
		pteval.pte_high &= ~_PAGE_C;
	}
#else
	if(pteval >= PAGE_NONCACHE_MARK)
		pteval &= ~_PAGE_C;
#endif
#endif
	(*(pteptr) = (pteval));
}

extern u32 current_pgd;
static inline void set_pmd(pmd_t *pmdptr, pmd_t pmdval)
{
    unsigned long pgd = (current_pgd - 0x40000000UL) | PADRE_MMU_PGT_EN
#ifdef CONFIG_PADRE_PGTCACHE
        | PADRE_MMU_PGT_CACHE
#endif
     ;
    *pmdptr = pmdval;
    __asm__ __volatile__(
        "sta %0, [%1]%2"
        :
        :"r"(pgd),"r"(PADRE_MMU_PGT),"i"(ASI_MMU));
}

#define pmd_page(pmd) 	(pfn_to_page((pmd_val(pmd)-0x40000000UL) >> PAGE_SHIFT))

#define pte_none(x)     (!pte_low_val(x))
#define pte_present(x)  (pte_low_val(x) & _PAGE_V)
static inline void pte_clear(struct mm_struct *mm, unsigned long addr, pte_t *ptep)
{
#ifdef CONFIG_PADRE_16K_PAGE
	ptep->pte1 = 0;
	ptep->pte2 = 0;
	ptep->pte3 = 0;
	ptep->pte4 = 0;
#else
#ifdef CONFIG_PADRE_8K_PAGE
	ptep->pte_low = 0;
	ptep->pte_high = 0;
#else
	*ptep = 0;
#endif
#endif
}
#define set_pte_at(mm,addr,ptep,pteval) set_pte(ptep,pteval)

#define pmd_none(x)     (!pmd_val(x))

#ifdef CONFIG_PADRE_RESERVE_DMA
#define pmd_bad(x)      ((pmd_val(x) & (0xfff & ~_PAGE_U)) != _KERNPG_TABLE)
#else
#define pmd_bad(x)      ((pmd_val(x) & (~PAGE_MASK & ~_PAGE_U)) != _KERNPG_TABLE)
#endif

#define pmd_present(x)  (pmd_val(x) & _PAGE_V)
#define pmd_clear(xp)   do { set_pmd(xp, __pmd(0)); } while(0)

#define pgd_none(pgd) 		0
#define pgd_bad(pgd) 		0
#define pgd_present(pgd) 	1
#define pgd_clear(pgd) 		do { }  while(0)

#define pte_file(x)     	( pte_low_val(x) & _PAGE_FILE ) 
#define __pte_offset(x) 	(((x) >> PAGE_SHIFT) & (PTRS_PER_PTE - 1))

#ifdef CONFIG_PADRE_RESERVE_DMA
#define pmd_addr(x)     	((pmd_val(x) & 0xfffff000)+0x40000000UL)
#else
#define pmd_addr(x)     	((pmd_val(x) & PAGE_MASK)+0x40000000UL)
#endif

#define pte_offset(xp,x) 	((pte_t*)pmd_addr(*(xp)) + __pte_offset(x))
#define pte_write(x)    	(pte_low_val(x) & _PAGE_W)
#define pte_read(x)     	(pte_low_val(x) & _PAGE_USER)
#define pte_exec(x)     	(pte_low_val(x) & _PAGE_USER)

#ifdef CONFIG_PADRE_16K_PAGE
static inline int pte_dirty(pte_t pte)
{
	return (pte.pte1&_PAGE_D)||(pte.pte2&_PAGE_D)||(pte.pte3&_PAGE_D)||(pte.pte4&_PAGE_D);
}
static inline int pte_young(pte_t pte)
{
	return (pte.pte1&_PAGE_A)||(pte.pte2&_PAGE_A)||(pte.pte3&_PAGE_A)||(pte.pte4&_PAGE_A);
}
#else
#ifdef CONFIG_PADRE_8K_PAGE
static inline int pte_dirty(pte_t pte)
{
	return (pte.pte_low&_PAGE_D)||(pte.pte_high&_PAGE_D);
}
static inline int pte_young(pte_t pte)
{
	return (pte.pte_low&_PAGE_A)||(pte.pte_high&_PAGE_A);
}
#else
#define pte_dirty(x)    	(pte_low_val(x) & _PAGE_D)
#define pte_young(x)    	(pte_low_val(x) & _PAGE_A)
#endif
#endif


#ifdef CONFIG_PADRE_16K_PAGE

static inline pte_t pte_rdprotect(pte_t pte)    
{ 
	pte.pte1 &= ~_PAGE_USER; 
	pte.pte2 &= ~_PAGE_USER; 
	pte.pte3 &= ~_PAGE_USER; 
	pte.pte4 &= ~_PAGE_USER; 
	return pte; 
}
static inline pte_t pte_exprotect(pte_t pte)    
{ 
	pte.pte1 &= ~_PAGE_USER; 
	pte.pte2 &= ~_PAGE_USER; 
	pte.pte3 &= ~_PAGE_USER; 
	pte.pte4 &= ~_PAGE_USER; 
	return pte; 
}
static inline pte_t pte_mkclean(pte_t pte)      
{ 
	pte.pte1 &= ~_PAGE_D; 
	pte.pte2 &= ~_PAGE_D; 
	pte.pte3 &= ~_PAGE_D; 
	pte.pte4 &= ~_PAGE_D; 
	return pte; 
}
static inline pte_t pte_mkold(pte_t pte)        
{ 
	pte.pte1 &= ~_PAGE_A; 
	pte.pte2 &= ~_PAGE_A; 
	pte.pte3 &= ~_PAGE_A; 
	pte.pte4 &= ~_PAGE_A; 
	return pte; 
}
static inline pte_t pte_wrprotect(pte_t pte)    
{ 
	pte.pte1 &= ~_PAGE_W; 
	pte.pte2 &= ~_PAGE_W; 
	pte.pte3 &= ~_PAGE_W; 
	pte.pte4 &= ~_PAGE_W; 
	return pte; 
}
static inline pte_t pte_mkread(pte_t pte)       
{ 
	pte.pte1 |= _PAGE_USER; 
	pte.pte2 |= _PAGE_USER; 
	pte.pte3 |= _PAGE_USER; 
	pte.pte4 |= _PAGE_USER; 
	return pte; 
}
static inline pte_t pte_mkexec(pte_t pte)       
{ 
	pte.pte1 |= _PAGE_USER; 
	pte.pte2 |= _PAGE_USER; 
	pte.pte3 |= _PAGE_USER; 
	pte.pte4 |= _PAGE_USER; 
	return pte; 
}
static inline pte_t pte_mkdirty(pte_t pte)      
{ 
	pte.pte1 |= _PAGE_D; 
	pte.pte2 |= _PAGE_D; 
	pte.pte3 |= _PAGE_D; 
	pte.pte4 |= _PAGE_D; 
	return pte; 
}
static inline pte_t pte_mkyoung(pte_t pte)      
{ 
	pte.pte1 |= _PAGE_A; 
	pte.pte2 |= _PAGE_A; 
	pte.pte3 |= _PAGE_A; 
	pte.pte4 |= _PAGE_A; 
	return pte; 
}
static inline pte_t pte_mkwrite(pte_t pte)      
{ 
	pte.pte1 |= _PAGE_W; 
	pte.pte2 |= _PAGE_W; 
	pte.pte3 |= _PAGE_W; 
	pte.pte4 |= _PAGE_W; 
	return pte; 
}
#else
#ifdef CONFIG_PADRE_8K_PAGE
static inline pte_t pte_rdprotect(pte_t pte)    
{ 
	pte.pte_low &= ~_PAGE_USER; 
	pte.pte_high &= ~_PAGE_USER; 
	return pte; 
}
static inline pte_t pte_exprotect(pte_t pte)    
{ 
	pte.pte_low &= ~_PAGE_USER; 
	pte.pte_high &= ~_PAGE_USER; 
	return pte; 
}
static inline pte_t pte_mkclean(pte_t pte)      
{ 
	pte.pte_low &= ~_PAGE_D; 
	pte.pte_high &= ~_PAGE_D; 
	return pte; 
}
static inline pte_t pte_mkold(pte_t pte)        
{ 
	pte.pte_low &= ~_PAGE_A; 
	pte.pte_high &= ~_PAGE_A; 
	return pte; 
}
static inline pte_t pte_wrprotect(pte_t pte)    
{ 
	pte.pte_low &= ~_PAGE_W; 
	pte.pte_high &= ~_PAGE_W; 
	return pte; 
}
static inline pte_t pte_mkread(pte_t pte)       
{ 
	pte.pte_low |= _PAGE_USER; 
	pte.pte_high |= _PAGE_USER; 
	return pte; 
}
static inline pte_t pte_mkexec(pte_t pte)       
{ 
	pte.pte_low |= _PAGE_USER; 
	pte.pte_high |= _PAGE_USER; 
	return pte; 
}
static inline pte_t pte_mkdirty(pte_t pte)      
{ 
	pte.pte_low |= _PAGE_D; 
	pte.pte_high |= _PAGE_D; 
	return pte; 
}
static inline pte_t pte_mkyoung(pte_t pte)      
{ 
	pte.pte_low |= _PAGE_A; 
	pte.pte_high |= _PAGE_A; 
	return pte; 
}
static inline pte_t pte_mkwrite(pte_t pte)      
{ 
	pte.pte_low |= _PAGE_W; 
	pte.pte_high |= _PAGE_W; 
	return pte; 
}
#else
#define pte_wrprotect(x)    	(pte_low_val(x) & ~_PAGE_W)
#define pte_rdprotect(x)    	(pte_low_val(x) & ~_PAGE_USER)
#define pte_exprotect(x)    	(pte_low_val(x) & ~_PAGE_USER)
#define pte_mkread(x)   	(pte_low_val(x) | _PAGE_USER)
#define pte_mkwrite(x)  	(pte_low_val(x) | _PAGE_W)
#define pte_mkexec(x)   	(pte_low_val(x) | _PAGE_USER)
#define pte_mkdirty(x)  	(pte_low_val(x) | _PAGE_D)
#define pte_mkclean(x)  	(pte_low_val(x) & ~_PAGE_D)
#define pte_mkyoung(x)  	(pte_low_val(x) | _PAGE_A)
#define pte_mkold(x)    	(pte_low_val(x) & ~_PAGE_A)
#endif
#endif

static inline pte_t pfn_pte(unsigned long page_nr, pgprot_t pgprot)
{
	pte_t pte;
#ifdef CONFIG_PADRE_16K_PAGE
	pte.pte1 = ((page_nr << PAGE_SHIFT) | pgprot_val(pgprot)) + 0x40000000UL;
	pte.pte2 = pte.pte1 + 0x1000;
	pte.pte3 = pte.pte2 + 0x1000;
	pte.pte4 = pte.pte3 + 0x1000;
#else
#ifdef CONFIG_PADRE_8K_PAGE
	pte.pte_low = ((page_nr << PAGE_SHIFT) | pgprot_val(pgprot)) + 0x40000000UL;
	pte.pte_high = pte.pte_low + 0x1000;
#else
	pte = ((page_nr << PAGE_SHIFT) | pgprot_val(pgprot)) + 0x40000000UL;
#endif
#endif
	return pte;
}
#define mk_pte(page, pgprot)    pfn_pte(page_to_pfn(page), (pgprot))
#define pte_pfn(pte) 	((unsigned long)((pte_low_val(pte)-0x40000000UL) >> PAGE_SHIFT))
#define pte_page(pte)	pfn_to_page(pte_pfn(pte))

#define VMALLOC_OFFSET  0
#define VMALLOC_START   0xf8000000
#define VMALLOC_END     0xffff0000
#define VMALLOC_PER_PGD
#define VMALLOC_PTRS_PER_PGD   (VMALLOC_START/PGDIR_SIZE)

static __inline__ pte_t pte_modify(pte_t pte, pgprot_t newprot)
{
#ifdef CONFIG_PADRE_16K_PAGE
	pte.pte1 = (pte.pte1 & _PAGE_CHG_MASK) | pgprot_val(newprot);
	pte.pte2 = (pte.pte2 & _PAGE_CHG_MASK) | pgprot_val(newprot);
	pte.pte3 = (pte.pte3 & _PAGE_CHG_MASK) | pgprot_val(newprot);
	pte.pte4 = (pte.pte4 & _PAGE_CHG_MASK) | pgprot_val(newprot);
#else
#ifdef CONFIG_PADRE_8K_PAGE
	pte.pte_low = (pte.pte_low & _PAGE_CHG_MASK) | pgprot_val(newprot);
	pte.pte_high = (pte.pte_high & _PAGE_CHG_MASK) | pgprot_val(newprot);
#else
	pte = (pte & _PAGE_CHG_MASK) | pgprot_val(newprot);
#endif
#endif
	return pte;
}
	
#define pgd_index(address) ((address) >> PGDIR_SHIFT)

/* to find an entry in a page-table-directory */
#define pgd_offset(mm, address) ((mm)->pgd + pgd_index(address))

/* to find an entry in a kernel page-table-directory */
#define pgd_offset_k(address) pgd_offset(&init_mm, address)

/* Find an entry in the second-level page table.. */
#define pmd_offset(dir,addr) ((pmd_t*)(dir))

/* Find an entry in the third-level page table.. */ 
#define pte_offset_kernel(dir,addr) pte_offset(dir,addr)

/*
 * This shortcut works on sun4m (and sun4d) because the nocache area is static,
 * and sun4c is guaranteed to have no highmem anyway.
 */
#define pte_offset_map(d, a)		pte_offset_kernel(d,a)
#define pte_offset_map_nested(d, a)	pte_offset_kernel(d,a)

#define pte_unmap(pte)		do{}while(0)
#define pte_unmap_nested(pte)	do{}while(0)


#define update_mmu_cache(vma,addr,pte) 

#define __swp_type(x)			(((x).val >> 2) & 0x7f)
#define __swp_offset(x)			(((x).val >> 9) & 0x3ffff)
#define __swp_entry(type,off)		((swp_entry_t) {(((type) & 0x7f) << 2) | (((off) & 0x3ffff) << 9)})

#define __pte_to_swp_entry(pte)     ((swp_entry_t) { pte_low_val(pte) })

#ifdef CONFIG_PADRE_16K_PAGE
#define __swp_entry_to_pte(x)       ((pte_t) {(x).val,0,0,0} )
#else
#ifdef CONFIG_PADRE_8K_PAGE
#define __swp_entry_to_pte(x)       ((pte_t) {(x).val,0} )
#else
#define __swp_entry_to_pte(x)       ((pte_t) ( (x).val ))
#endif
#endif

/*
 * Bits 0,1,2 and 10 are taken, split up the 28 bits of offset 
 * into this range:
 */
#define PTE_FILE_MAX_BITS 28

#define pte_to_pgoff(pte) \
	(((pte_low_val(pte)>>3) & 0x7f) + ((pte_low_val(pte)>>11)<<7))
#ifdef CONFIG_PADRE_16K_PAGE
#define pgoff_to_pte(off) \
	((pte_t){(((off & 0x7f) << 3) + ((off >> 7) << 11) + _PAGE_FILE),0,0,0})
#else
#ifdef CONFIG_PADRE_8K_PAGE
#define pgoff_to_pte(off) \
	((pte_t){(((off & 0x7f) << 3) + ((off >> 7) << 11) + _PAGE_FILE),0})
#else
#define pgoff_to_pte(off) \
	((pte_t)(((off & 0x7f) << 3) + ((off >> 7) << 11) + _PAGE_FILE))
#endif
#endif

/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
#define kern_addr_valid(addr) 1
#define io_remap_page_range   remap_page_range

#ifndef CONFIG_PADRE

/* Needs to be defined here and not in linux/mm.h, as it is arch dependent */
#define kern_addr_valid(addr) \
        (test_bit(__pa((unsigned long)(addr))>>20, sparc_valid_addr_bitmap))

extern int io_remap_page_range(struct vm_area_struct *vma,
                               unsigned long from, unsigned long to,
                               unsigned long size, pgprot_t prot, int space);
extern int io_remap_pfn_range(struct vm_area_struct *vma,
                              unsigned long from, unsigned long pfn,
                              unsigned long size, pgprot_t prot);

/*
 * For sparc32&64, the pfn in io_remap_pfn_range() carries <iospace> in
 * its high 4 bits.  These macros/functions put it there or get it from there.
 */
#define MK_IOSPACE_PFN(space, pfn)      (pfn | (space << (BITS_PER_LONG - 4)))
#define GET_IOSPACE(pfn)                (pfn >> (BITS_PER_LONG - 4))
#define GET_PFN(pfn)                    (pfn & 0x0fffffffUL)

#endif //CONFIG_PADRE

#include <asm-generic/pgtable.h>

#endif /* !(__ASSEMBLY__) */

/*
 * No page table caches to initialise
 */
#define pgtable_cache_init()	do { } while (0)

#endif /* !(_SPARC_PGTABLE_H) */
