/* $Id: dma.h,v 1.1.1.1 2006-08-28 17:51:47 bzhang Exp $
 * include/asm-sparc/dma.h
 *
 * Copyright 1995 (C) David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef _ASM_SPARC_DMA_H
#define _ASM_SPARC_DMA_H

#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/types.h>

#include <asm/delay.h>
#include <asm/system.h>
#include <asm/io.h>
#include <linux/spinlock.h>

extern spinlock_t  dma_spin_lock;

static __inline__ unsigned long claim_dma_lock(void)
{
	unsigned long flags;
	spin_lock_irqsave(&dma_spin_lock, flags);
	return flags;
}

static __inline__ void release_dma_lock(unsigned long flags)
{
	spin_unlock_irqrestore(&dma_spin_lock, flags);
}

/* These are irrelevant for Sparc DMA, but we leave it in so that
 * things can compile.
 */
#define MAX_DMA_CHANNELS 8
#define MAX_DMA_ADDRESS  (~0UL)
#define DMA_MODE_READ    1
#define DMA_MODE_WRITE   2

/* Useful constants */
#define SIZE_16MB      (16*1024*1024)
#define SIZE_64K       (64*1024)

#define for_each_dvma(dma) \
        for((dma) = dma_chain; (dma); (dma) = (dma)->next)

extern int get_dma_list(char *);
extern int request_dma(unsigned int, __const__ char *);
extern void free_dma(unsigned int);

/* From PCI */

#ifdef CONFIG_PCI
extern int isa_dma_bridge_buggy;
#else
#define isa_dma_bridge_buggy	(0)
#endif

#endif /* !(_ASM_SPARC_DMA_H) */
