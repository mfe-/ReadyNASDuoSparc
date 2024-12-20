#ifndef _ASM_SPARC_DMA_MAPPING_H
#define _ASM_SPARC_DMA_MAPPING_H

#include <linux/config.h>
//#include <linux/device.h>

#ifdef CONFIG_PCI
#include <asm-generic/dma-mapping.h>
#else

static inline void *dma_alloc_coherent(struct device *dev, size_t size,
			 dma_addr_t *dma_handle, int flag)
{
	BUG();
	return NULL;
}

static inline void dma_free_coherent(struct device *dev, size_t size,
		       void *vaddr, dma_addr_t dma_handle)
{
	BUG();
}

#endif /* PCI */

#endif /* _ASM_SPARC_DMA_MAPPING_H */
