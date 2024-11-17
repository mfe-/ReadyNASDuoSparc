#ifndef __SPARC_MMU_CONTEXT_H
#define __SPARC_MMU_CONTEXT_H

#ifndef __ASSEMBLY__

static inline void enter_lazy_tlb(struct mm_struct *mm, struct task_struct *tsk)
{
}

/*
 * Initialize a new mmu context.  This is invoked when a new
 * address space instance (unique or shared) is instantiated.
 */
#define init_new_context(tsk, mm)	0 

#define destroy_context(mm) do { } while(0)

/* Switch the current MM context. */
extern u32 current_pgd;
static inline void switch_mm(struct mm_struct *prev, struct mm_struct *next,
                             struct task_struct *tsk)
{
    if( prev != next) {
        register u32 pgd;
	unsigned long flags;

	local_irq_save(flags);
        current_pgd = (u32)next->pgd;
        pgd = ((u32)(next->pgd) - 0x40000000) | PADRE_MMU_PGT_EN |
            PADRE_MMU_PGT_FL
#ifdef CONFIG_PADRE_PGTCACHE
            | PADRE_MMU_PGT_CACHE
#endif
        ;

        __asm__ __volatile__(
            "sta %0, [%1]%2\n\t"
            :
            :"r"(pgd),"r"(PADRE_MMU_PGT),"i"(ASI_MMU)
	);

	local_irq_restore(flags);
	
    }
}



#define deactivate_mm(tsk,mm)	do { } while (0)

/* Activate a new MM instance for the current task. */
#define activate_mm(active_mm, mm) switch_mm((active_mm), (mm), NULL)

#endif /* !(__ASSEMBLY__) */

#endif /* !(__SPARC_MMU_CONTEXT_H) */
