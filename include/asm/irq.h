/* $Id: irq.h,v 1.1.1.1 2006-08-28 17:51:47 bzhang Exp $
 * irq.h: IRQ registers on the Sparc.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef _SPARC_IRQ_H
#define _SPARC_IRQ_H

#include <linux/config.h>
#include <linux/linkage.h>
#include <linux/threads.h>     /* For NR_CPUS */
#include <linux/interrupt.h>

#include <asm/system.h>     /* For SUN4M_NCPUS */

#define NR_IRQS    48

#define irq_canonicalize(irq)	(irq)

static inline char *__irq_itoa(unsigned int irq)
{
    static char buff[8];

    sprintf(buff, "%d", irq);
    return buff;
}

struct irqaction;
extern void disable_irq(unsigned int);
extern void disable_irq_nosync(unsigned int);
extern void enable_irq(unsigned int);
extern int setup_irq(unsigned int, struct irqaction *);
extern unsigned long lp_ch_ipend0, lp_ch_ipend1;

#endif
