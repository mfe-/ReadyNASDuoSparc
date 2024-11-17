#ifndef _SPARC_CACHEFLUSH_H
#define _SPARC_CACHEFLUSH_H

#include <linux/config.h>
#include <linux/mm.h>		/* Common for other includes */
#include <asm/padre0.h>
#include <asm/io.h>

// flag for ASIC bug fix
extern int padre_cachefix;

/*
 * Fine grained cache flushing.
 */

extern unsigned long icmu_ctrl,dcmu_ctrl;

#define flush_cache_all()					do { } while(0) 
#define flush_cache_mm(mm) 					do { } while(0)
#define flush_cache_range(mm,start,end)     do { } while(0)
//#define flush_cache_page(vma,page)          do { } while(0)
#define flush_cache_page(vma,addr,pfn)      do { } while(0)
#define flush_dcache_page(page)             do { } while(0)


extern void clean_dcache_range(unsigned long start, unsigned long end);
extern void flushn_dcache_range(unsigned long start, unsigned long end);
extern void flush_icache_range(unsigned long start, unsigned long end);
extern void flush_icache_page(struct vm_area_struct *vma, struct page *page);

#define flush_icache_user_range(vma,pg,adr,len)	flush_icache_range(adr,adr+len)

#ifdef CONFIG_PADRE
#define copy_to_user_page(vma, page, vaddr, dst, src, len) \
        do {                                                    \
                memcpy(dst, src, len);                          \
        } while (0)
#define copy_from_user_page(vma, page, vaddr, dst, src, len) \
        do {                                                    \
                memcpy(dst, src, len);                          \
        } while (0)
#else
#define copy_to_user_page(vma, page, vaddr, dst, src, len) \
        do {                                                    \
                flush_cache_page(vma, vaddr, page_to_pfn(page));\
                memcpy(dst, src, len);                          \
        } while (0)
#define copy_from_user_page(vma, page, vaddr, dst, src, len) \
        do {                                                    \
                flush_cache_page(vma, vaddr, page_to_pfn(page));\
                memcpy(dst, src, len);                          \
        } while (0)
#endif

extern void flush_sig_insns(struct mm_struct *mm, unsigned long insn_addr);

#define flush_dcache_mmap_lock(mapping)		do { } while (0)
#define flush_dcache_mmap_unlock(mapping)	do { } while (0)

#define flush_cache_vmap(start, end)		flush_cache_all()
#define flush_cache_vunmap(start, end)		flush_cache_all()

extern void flush_cache_dma(int direction);

#ifdef CONFIG_DEBUG_PAGEALLOC
/* internal debugging function */
void kernel_map_pages(struct page *page, int numpages, int enable);
#endif

#endif /* _SPARC_CACHEFLUSH_H */
