#ifndef _SPARC_TLBFLUSH_H
#define _SPARC_TLBFLUSH_H

#include <linux/config.h>
#include <linux/mm.h>
// #include <asm/processor.h>


#define flush_tlb_pgtables(mm, start, end)	do{ }while(0)

#define flush_tlb_all() 											\
	do {                                                            \
		unsigned int flush_cmd =(PADRE_MMU_CONTROL_FL |		        \
							 	 PADRE_MMU_CONTROL_DE |     	    \
	                              PADRE_MMU_CONTROL_IE);            \
		__asm__ __volatile__(                                       \
			"sta %0, [%1]%2\t\t"                                    \
            :                                                       \
            :"r"(flush_cmd),"r"(PADRE_MMU_CONTROL),"i"(ASI_MMU));   \
    } while(0)

#define flush_tlb_mm(mm)											\
	do {															\
		 if( mm == current->active_mm)								\
			 flush_tlb_all();										\
	} while(0)

static inline void flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
		            unsigned long end)
{
	flush_tlb_mm(vma->vm_mm);
}

static inline void flush_tlb_page(struct vm_area_struct *vma,unsigned long addr)
{
    if( vma->vm_mm == current->active_mm) {
        pgd_t *pgd;
        pmd_t *pmd;
        pte_t *pte,ptev;
        unsigned long flags;

#ifdef CONFIG_PADRE_8K_PAGE
	addr = (addr >> PAGE_SHIFT) << PAGE_SHIFT;
#endif
#ifdef CONFIG_PADRE_16K_PAGE
	addr = (addr >> PAGE_SHIFT) << PAGE_SHIFT;
#endif
	local_irq_save(flags);
	pgd = pgd_offset(vma->vm_mm,addr);
	pmd = pmd_offset(pgd,addr);
	pte = pte_offset(pmd,addr);
	ptev = *pte;
       	__asm__ __volatile__(
            "sta %%g0, [%0]%1\t\n"
#ifdef CONFIG_PADRE_8K_PAGE
	    "sta %%g0, [%2]%1\t\n"
#endif
#ifdef CONFIG_PADRE_16K_PAGE
	    "sta %%g0, [%2]%1\t\n"
	    "sta %%g0, [%3]%1\t\n"
	    "sta %%g0, [%4]%1\t\n"
#endif
            :
            :"r"(addr),"i"(ASI_TLBPROBE)
#ifdef CONFIG_PADRE_8K_PAGE
	     ,"r"(addr+0x1000)
#endif
#ifdef CONFIG_PADRE_16K_PAGE
	     ,"r"(addr+0x1000)
	     ,"r"(addr+0x2000)
	     ,"r"(addr+0x3000)
#endif
            );

#ifdef CONFIG_PADRE_16K_PAGE
        writel(ptev.pte1,(unsigned long)pte);
        writel(ptev.pte2,(unsigned long)pte+4);
        writel(ptev.pte3,(unsigned long)pte+8);
        writel(ptev.pte4,(unsigned long)pte+12);
#else
#ifdef CONFIG_PADRE_8K_PAGE
        writel(ptev.pte_low,(unsigned long)pte);
        writel(ptev.pte_high,(unsigned long)pte+4);
#else
        writel(ptev,(unsigned long)pte);
#endif
#endif
        local_irq_restore(flags);
    }
}


/*
 * This is a kludge, until I know better. --zaitcev XXX
 */
#define flush_tlb_kernel_range(start, end) flush_tlb_all()

#endif /* _SPARC_TLBFLUSH_H */
