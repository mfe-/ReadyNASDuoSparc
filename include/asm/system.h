/* $Id: system.h,v 1.3 2007-12-04 20:11:30 wgao Exp $ */
#include <linux/config.h>

#ifndef __SPARC_SYSTEM_H
#define __SPARC_SYSTEM_H

#include <linux/config.h>
#include <linux/kernel.h>
#include <linux/threads.h>	/* NR_CPUS */
#include <linux/thread_info.h>

#include <asm/segment.h>
#include <asm/page.h>
#include <asm/psr.h>
#include <asm/ptrace.h>

#ifndef __ASSEMBLY__

/* Really, userland should not be looking at any of this... */
#ifdef __KERNEL__

extern struct thread_info *current_set[NR_CPUS];

extern unsigned long empty_bad_page;
extern unsigned long empty_bad_page_table;
extern unsigned long empty_zero_page;

extern int serial_console;
extern int stop_a_enabled;

static __inline__ int con_is_present(void)
{
	return serial_console ? 0 : 1;
}

/* When a context switch happens we must flush all user windows so that
 * the windows of the current process are flushed onto its stack. This
 * way the windows are all clean for the next process and the stack
 * frames are up to date.
 */
extern void flush_user_windows(void);
extern void kill_user_windows(void);
extern void synchronize_user_stack(void);
extern void fpsave(unsigned long *fpregs, unsigned long *fsr,
		   void *fpqueue, unsigned long *fpqdepth);

#ifdef CONFIG_SMP
#define SWITCH_ENTER(prv) \
	do {			\
	if (test_tsk_thread_flag(prv, TIF_USEDFPU)) { \
		put_psr(get_psr() | PSR_EF); \
		fpsave(&(prv)->thread.float_regs[0], &(prv)->thread.fsr, \
		       &(prv)->thread.fpqueue[0], &(prv)->thread.fpqdepth); \
		clear_tsk_thread_flag(prv, TIF_USEDFPU); \
		(prv)->thread.kregs->psr &= ~PSR_EF; \
	} \
	} while(0)

#define SWITCH_DO_LAZY_FPU(next)	/* */
#else
#define SWITCH_ENTER(prv)		/* */
#define SWITCH_DO_LAZY_FPU(nxt)	\
	do {			\
	if (last_task_used_math != (nxt))		\
		(nxt)->thread.kregs->psr&=~PSR_EF;	\
	} while(0)
#endif

/*
 * Flush windows so that the VM switch which follows
 * would not pull the stack from under us.
 *
 * SWITCH_ENTER and SWITH_DO_LAZY_FPU do not work yet (e.g. SMP does not work)
 * XXX WTF is the above comment? Found in late teen 2.4.x.
 */
#define prepare_arch_switch(next) do { \
	__asm__ __volatile__( \
	".globl\tflush_patch_switch\nflush_patch_switch:\n\t" \
	"save %sp, -0x40, %sp; save %sp, -0x40, %sp; save %sp, -0x40, %sp\n\t" \
	"save %sp, -0x40, %sp; save %sp, -0x40, %sp; save %sp, -0x40, %sp\n\t" \
	"save %sp, -0x40, %sp\n\t" \
	"restore; restore; restore; restore; restore; restore; restore"); \
} while(0)
//#define finish_arch_switch(rq, next)	spin_unlock_irq(&(rq)->lock)
//#define task_running(rq, p)		((rq)->curr == (p))

	/* Much care has gone into this code, do not touch it.
	 *
	 * We need to loadup regs l0/l1 for the newly forked child
	 * case because the trap return path relies on those registers
	 * holding certain values, gcc is told that they are clobbered.
	 * Gcc needs registers for 3 values in and 1 value out, so we
	 * clobber every non-fixed-usage register besides l2/l3/o4/o5.  -DaveM
	 *
	 * Hey Dave, that do not touch sign is too much of an incentive
	 * - Anton & Pete
	 */
#define switch_to(prev, next, last) do {						\
	SWITCH_ENTER(prev);								\
	SWITCH_DO_LAZY_FPU(next);							\
        cpu_set(smp_processor_id(), next->active_mm->cpu_vm_mask);                      \
	__asm__ __volatile__(								\
	"sethi	%%hi(here - 0x8), %%o7\n\t"						\
	"mov	%%g6, %%g3\n\t"								\
	"or	%%o7, %%lo(here - 0x8), %%o7\n\t"					\
	"rd	%%psr, %%g4\n\t"							\
	"std	%%sp, [%%g6 + %4]\n\t"							\
	"rd	%%wim, %%g5\n\t"							\
	"wr	%%g4, 0x20, %%psr\n\t"							\
	"nop\n\t"									\
	"std	%%g4, [%%g6 + %3]\n\t"							\
	"ldd	[%2 + %3], %%g4\n\t"							\
	"mov	%2, %%g6\n\t"								\
	".globl	patchme_store_new_current\n"						\
"patchme_store_new_current:\n\t"							\
	"st	%2, [%1]\n\t"								\
	"wr	%%g4, 0x20, %%psr\n\t"							\
	"nop\n\t"									\
	"nop\n\t"									\
	"nop\n\t"	/* LEON needs all 3 nops: load to %sp depends on CWP. */		\
	"ldd	[%%g6 + %4], %%sp\n\t"							\
	"wr	%%g5, 0x0, %%wim\n\t"							\
	"ldd	[%%sp + 0x00], %%l0\n\t"						\
	"ldd	[%%sp + 0x38], %%i6\n\t"						\
	"wr	%%g4, 0x0, %%psr\n\t"							\
	"nop\n\t"									\
	"nop\n\t"									\
	"jmpl	%%o7 + 0x8, %%g0\n\t"							\
	" ld	[%%g3 + %5], %0\n\t"							\
	"here:\n"									\
        : "=&r" (last)									\
        : "r" (&(current_set[hard_smp_processor_id()])),	\
	  "r" ((next)->thread_info),				\
	  "i" (TI_KPSR),					\
	  "i" (TI_KSP),						\
	  "i" (TI_TASK)						\
	:       "g1", "g2", "g3", "g4", "g5",       "g7",	\
	  "l0", "l1",       "l3", "l4", "l5", "l6", "l7",	\
	  "i0", "i1", "i2", "i3", "i4", "i5",			\
	  "o0", "o1", "o2", "o3",                   "o7");	\
	} while(0)

/*
 * Changing the IRQ level on the Sparc.
 */
extern void local_irq_restore(unsigned long);
extern unsigned long __local_irq_save(void);
extern void local_irq_enable(void);
static inline unsigned long getipl(void)
{
        unsigned long retval;

        __asm__ __volatile__("rd        %%psr, %0" : "=r" (retval));
        return retval;
}

#define local_save_flags(flags) ((flags) = getipl())
#define local_irq_save(flags)   ((flags) = __local_irq_save())
#define local_irq_disable()     ((void) __local_irq_save())
#define irqs_disabled()         ((getipl() & PSR_PIL) != 0)


/* XXX Change this if we ever use a PSO mode kernel. */
#define mb()	__asm__ __volatile__ ("" : : : "memory")
#define rmb()	mb()
#define wmb()	mb()
#define read_barrier_depends()	do { } while(0)
#define set_mb(__var, __value)  do { __var = __value; mb(); } while(0)
#define set_wmb(__var, __value) set_mb(__var, __value)
#define smp_mb()	__asm__ __volatile__("":::"memory")
#define smp_rmb()	__asm__ __volatile__("":::"memory")
#define smp_wmb()	__asm__ __volatile__("":::"memory")
#define smp_read_barrier_depends()	do { } while(0)

#define nop() __asm__ __volatile__ ("nop")

/* This has special calling conventions */
extern void ___xchg32(void);

extern __inline__ unsigned long xchg_u32(__volatile__ unsigned long *m, unsigned long val)
{
#ifdef CONFIG_SMP
	__asm__ __volatile__("swap [%2], %0"
			     : "=&r" (val)
			     : "0" (val), "r" (m)
			     : "memory");
	return val;
#else
	register unsigned long *ptr asm("g1");
	register unsigned long ret asm("g2");

	ptr = (unsigned long *) m;
	ret = val;

	/* Note: this is magic and the nop there is
	   really needed. */
	__asm__ __volatile__(
	"mov	%%o7, %%g4\n\t"
	"call	___xchg32\n\t"
	" nop\n\t"
	: "=&r" (ret)
	: "0" (ret), "r" (ptr)
	: "g3", "g4", "g7", "memory", "cc");

	return ret;
#endif
}

#define xchg(ptr,x) ((__typeof__(*(ptr)))__xchg((unsigned long)(x),(ptr),sizeof(*(ptr))))
#define tas(ptr) (xchg((ptr),1))

extern void __xchg_called_with_bad_pointer(void);

static __inline__ unsigned long __xchg(unsigned long x, __volatile__ void * ptr, int size)
{
	switch (size) {
	case 4:
		return xchg_u32(ptr, x);
	};
	__xchg_called_with_bad_pointer();
	return x;
}

extern void die_if_kernel(char *str, struct pt_regs *regs) __attribute__ ((noreturn));
#define PADRE_VENDOR_SIZE   32
#define PADRE_MODEL_SIZE    32
#define PADRE_SERIAL_SIZE   16

#define PADRE_IO_7SATA_1PATA  0x20
#define PADRE_IO_4SATA_1PATA  0x21
#define PADRE_IO_4SATA_0PATA  0x41
#define PADRE_IO_2SATA_0PATA  0x42
#define PADRE_IO_1SATA_0PATA  0x43
#define PADRE_IO_8SATA_0PATA  0x80

#define PADRE_BOARD_IT73107     0x00
#define PADRE_BOARD_IT73435     0x01
#define PADRE_BOARD_IT71004     0x80
#define PADRE_BOARD_IT71008     0x81

#define PADRE_BOARD_TEMPERATURE 0x3
 #define PADRE_BOARD_TEMPERATURE_THERMISTOR 0x1
 #define PADRE_BOARD_TEMPERATURE_PII    0x2
 #define PADRE_BOARD_TEMPERATURE_2N3904 0x3

#define PADRE_BOOT_REGULAR              0
#define PADRE_BOOT_FACTORY              1
#define PADRE_BOOT_BOOTP                2
#define PADRE_BOOT_WATCHDOG             3
#define PADRE_BOOT_SOFTFAULT            4
#define PADRE_BOOT_FACTORY_DIAG         5
#define PADRE_BOOT_FACTORY_DIAG_1       6
#define PADRE_BOOT_OS_REINSTALL         7
#define PADRE_BOOT_ECC                  8
#define PADRE_BOOT_TFTP                 9
#define PADRE_BOOT_CONF                 10
#define PADRE_BOOT_RTC                  11
#define PADRE_BOOT_USB                  12
#define PADRE_BOOT_KDEBUG               13
#define PADRE_BOOT_UDEBUG               14

struct boot_param {
    unsigned long mem_size;
    unsigned long cpu_type;
    unsigned char mac[6];
    unsigned char bond_option;
    unsigned char boot_reason;
    unsigned char boot_version[128];
    unsigned char vendor[PADRE_VENDOR_SIZE];
    unsigned char model[PADRE_MODEL_SIZE];
    unsigned char serial[PADRE_SERIAL_SIZE];
    unsigned long product_features;

    // 384-511
    unsigned char vpd_extend[128];
};

extern struct boot_param padre_boot_param;
extern void padre_boot_init(struct boot_param *param);
extern void p0_boot_init(struct boot_param *param);

struct usb_ecounter {
        unsigned long usb_ecount_timeout[4][5];
        unsigned long usb_ecount_ioerr[4][5];
        unsigned long usb_ecount_other[4][5];
        unsigned long scsi_ioerr[8];
};

#endif /* __KERNEL__ */

#endif /* __ASSEMBLY__ */

#define arch_align_stack(x) (x)

#endif /* !(__SPARC_SYSTEM_H) */
