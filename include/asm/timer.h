/* $Id: timer.h,v 1.2 2006-09-06 21:15:13 bzhang Exp $
 * timer.h:  Definitions for the timer chips on the Sparc.
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#include <linux/config.h>

#ifndef _SPARC_TIMER_H
#define _SPARC_TIMER_H

#include <asm/system.h>  

#define PADRE_TM_CTRL_SEL_BIT(x)    ((x) << 13)
#define PADRE_TM_CTRL_LOAD_BIT(x)   (0x100 << (x))
#define PADRE_TM_CTRL_AUTO_BIT(x)   (0x10 << (x))
#define PADRE_TM_CTRL_INTEN_BIT(x)  (0x1 << (x))

#define PADRE_PRESCALE_VALUE    24

#define PADRE_IRQ_TIMER0		47
#define PADRE_IRQ_TIMER1		46
#define PADRE_IRQ_TIMER2		45
#define PADRE_TM_TIMER  PADRE_TM_TIMER1
#define PADRE_TIMER_COUNT               (50000/CONFIG_HZ-1)
#endif /* !(_SPARC_TIMER_H) */
