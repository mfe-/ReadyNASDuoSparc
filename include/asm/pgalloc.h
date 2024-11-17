/* $Id: pgalloc.h,v 1.2 2007-12-05 23:32:55 bzhang Exp $ */
#ifndef _SPARC_PGALLOC_H
#define _SPARC_PGALLOC_H

#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/mm.h>

#include <asm/head.h>
#include <asm/page.h>
#include <asm/io.h>

extern struct pgtable_cache_struct {
	unsigned long *pgd_cache;
	unsigned long *pte_cache;
	unsigned long pgtable_cache_sz;
	unsigned long pgd_cache_sz;
} pgt_quicklists;
#define pgd_quicklist           (pgt_quicklists.pgd_cache)
#define pmd_quicklist           ((unsigned long *)0)
#define pte_quicklist           (pgt_quicklists.pte_cache)
#define pgtable_cache_size      (pgt_quicklists.pgtable_cache_sz)
#define pgd_cache_size			(pgt_quicklists.pgd_cache_sz)

#ifdef CONFIG_PADRE_RESERVE_DMA
extern unsigned long padre_pgd_cache[];
extern unsigned long padre_pgd_cache_count;
extern unsigned long padre_pte_cache[];
extern unsigned long padre_pte_cache_count;

static __inline__ pgd_t *get_pgd_fast(void)
{
	pgd_t *pgd=NULL;
	if(padre_pgd_cache_count>0) {
		padre_pgd_cache_count--;
		pgd = (pgd_t*)padre_pgd_cache[padre_pgd_cache_count];
                memset(pgd, 0, USER_PTRS_PER_PGD * sizeof(pgd_t));
                memcpy(pgd+VMALLOC_PTRS_PER_PGD,init_mm.pgd+VMALLOC_PTRS_PER_PGD,
                           (PTRS_PER_PGD-VMALLOC_PTRS_PER_PGD)*sizeof(pgd_t));
	}
	return pgd;
}

static __inline__ void free_pgd_fast(pgd_t *pgd)
{
	padre_pgd_cache[padre_pgd_cache_count] = (unsigned long)pgd;
	padre_pgd_cache_count++;
}

static inline pte_t *
pte_alloc_one_kernel(struct mm_struct *mm, unsigned long addr)
{
	pte_t *pte=NULL;
	if(padre_pte_cache_count>0) {
		padre_pte_cache_count--;
		pte = (pte_t*)padre_pte_cache[padre_pte_cache_count];
		memset(pte,0,4096);
	}
	return pte;
		
}

static inline void pte_free_kernel(pte_t *pte)
{
	padre_pte_cache[padre_pte_cache_count] = (unsigned long)pte;
	padre_pte_cache_count++;
}

#define pte_alloc_one(mm,addr) pte_alloc_one_kernel(mm,addr)
#define pte_free(pte)	pte_free_kernel(pte)

#else
static __inline__ pgd_t *get_pgd_slow(void)
{
	pgd_t *pgd = (pgd_t *)__get_free_page(GFP_KERNEL | GFP_DMA);
		 
	if (pgd) {
		memset(pgd, 0, USER_PTRS_PER_PGD * sizeof(pgd_t));
		memcpy(pgd+VMALLOC_PTRS_PER_PGD,init_mm.pgd+VMALLOC_PTRS_PER_PGD,
			   (PTRS_PER_PGD-VMALLOC_PTRS_PER_PGD)*sizeof(pgd_t));	
	}
	return pgd;
}

static __inline__ pgd_t *get_pgd_fast(void)
{
	unsigned long *ret;
		 
	if ((ret = pgd_quicklist) != NULL) {
		pgd_quicklist = (unsigned long *)(*ret);
		ret[0] = ret[1];
		pgtable_cache_size--;
	} else
		ret = (unsigned long *)get_pgd_slow();
	return (pgd_t *)ret;
}

static __inline__ void free_pgd_fast(pgd_t *pgd)
{
	*(unsigned long *)pgd = (unsigned long) pgd_quicklist;
	pgd_quicklist = (unsigned long *) pgd;
	pgtable_cache_size++;
}

static __inline__ void free_pgd_slow(pgd_t *pgd)
{
	free_page((unsigned long)pgd);
}


static inline pte_t *
pte_alloc_one_kernel(struct mm_struct *mm, unsigned long addr)
{
        pte_t *pte;

        pte = (pte_t *)__get_free_page(GFP_KERNEL|__GFP_REPEAT|GFP_DMA);
        if (pte) 
                clear_page(pte);

        return pte;
}

static inline struct page *
pte_alloc_one(struct mm_struct *mm, unsigned long addr)
{
        struct page *pte;

        pte = alloc_pages(GFP_KERNEL|__GFP_REPEAT|GFP_DMA, 0);
        if (pte) {
                void *page = page_address(pte);
                clear_page(page);
        }

        return pte;
}

static inline void pte_free_kernel(pte_t *pte)
{
        if (pte) 
                free_page((unsigned long)pte);
}

static inline void pte_free(struct page *pte)
{
        __free_page(pte);
}

#endif

#ifdef CONFIG_PADRE_RESERVE_DMA
#define __pte_free_tlb(tlb,pte)	        pte_free(pte)
#else
#define __pte_free_tlb(tlb,pte)	        tlb_remove_page((tlb),(pte))
#endif

#define __pmd_free_tlb(tlb,x)           do { } while (0)

#define pgd_free(pgd)	free_pgd_fast(pgd)
#define pgd_alloc(mm)	get_pgd_fast()

#define pmd_alloc_one(mm,addr)          ({ BUG(); ((pmd_t *)2); })
#define pmd_free(pmd)                   do { } while (0)
#define pgd_populate(mm,pmd,pte)        BUG()

#ifdef CONFIG_PADRE_RESERVE_DMA
static inline void
pmd_populate(struct mm_struct *mm, pmd_t *pmdp, pte_t *ptep)
{
        unsigned long pte_ptr = (unsigned long)ptep - 0x40000000;

        BUG_ON(mm == &init_mm);

	set_pmd(pmdp, _PAGE_TABLE + pte_ptr);
}

#else
static inline void
pmd_populate(struct mm_struct *mm, pmd_t *pmdp, struct page *ptep)
{
        unsigned long pmdval;

        BUG_ON(mm == &init_mm);

        pmdval = ((page_to_pfn(ptep) << PAGE_SHIFT) | _PAGE_TABLE) + 
		 0x40000000;
	set_pmd(pmdp, pmdval);
}
#endif

static inline void
pmd_populate_kernel(struct mm_struct *mm, pmd_t *pmdp, pte_t *ptep)
{
        unsigned long pte_ptr = (unsigned long)ptep - 0x40000000;

        BUG_ON(mm != &init_mm);

	set_pmd(pmdp, _PAGE_TABLE + pte_ptr);
}


extern void check_pgt_cache(void);

#endif /* _SPARC_PGALLOC_H */
