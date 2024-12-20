/* $Id: elf.h,v 1.3 2007-04-20 00:52:12 bzhang Exp $ */
#ifndef __ASMSPARC_ELF_H
#define __ASMSPARC_ELF_H

/*
 * ELF register definitions..
 */

#include <linux/config.h>
#include <asm/ptrace.h>

#ifdef __KERNEL__
#include <asm/uaccess.h>
#endif

/*
 * Sparc section types
 */
#define STT_REGISTER		13

/*
 * Sparc ELF relocation types
 */
#define	R_SPARC_NONE		0
#define	R_SPARC_8		1
#define	R_SPARC_16		2
#define	R_SPARC_32		3
#define	R_SPARC_DISP8		4
#define	R_SPARC_DISP16		5
#define	R_SPARC_DISP32		6
#define	R_SPARC_WDISP30		7
#define	R_SPARC_WDISP22		8
#define	R_SPARC_HI22		9
#define	R_SPARC_22		10
#define	R_SPARC_13		11
#define	R_SPARC_LO10		12
#define	R_SPARC_GOT10		13
#define	R_SPARC_GOT13		14
#define	R_SPARC_GOT22		15
#define	R_SPARC_PC10		16
#define	R_SPARC_PC22		17
#define	R_SPARC_WPLT30		18
#define	R_SPARC_COPY		19
#define	R_SPARC_GLOB_DAT	20
#define	R_SPARC_JMP_SLOT	21
#define	R_SPARC_RELATIVE	22
#define	R_SPARC_UA32		23
#define R_SPARC_PLT32		24
#define R_SPARC_HIPLT22		25
#define R_SPARC_LOPLT10		26
#define R_SPARC_PCPLT32		27
#define R_SPARC_PCPLT22		28
#define R_SPARC_PCPLT10		29
#define R_SPARC_10		30
#define R_SPARC_11		31
#define R_SPARC_64		32
#define R_SPARC_OLO10		33
#define R_SPARC_WDISP16		40
#define R_SPARC_WDISP19		41
#define R_SPARC_7		43
#define R_SPARC_5		44
#define R_SPARC_6		45

/* Bits present in AT_HWCAP, primarily for Sparc32.  */

#define HWCAP_SPARC_FLUSH       1    /* CPU supports flush instruction. */
#define HWCAP_SPARC_STBAR       2
#define HWCAP_SPARC_SWAP        4
#define HWCAP_SPARC_MULDIV      8
#define HWCAP_SPARC_V9		16
#define HWCAP_SPARC_ULTRA3	32

/* For the most part we present code dumps in the format
 * Solaris does.
 */
typedef unsigned long elf_greg_t;
#define ELF_NGREG 38
typedef elf_greg_t elf_gregset_t[ELF_NGREG];

/* Format is:
 * 	G0 --> G7
 *	O0 --> O7
 *	L0 --> L7
 *	I0 --> I7
 *	PSR, PC, nPC, Y, WIM, TBR
 */
#define ELF_CORE_COPY_REGS(__elf_regs, __pt_regs)	\
do {	unsigned long *dest = &(__elf_regs[0]);		\
	struct pt_regs *src = (__pt_regs);		\
	unsigned long __user *sp;				\
	memcpy(&dest[0], &src->u_regs[0],		\
	       sizeof(unsigned long) * 16);		\
	/* Don't try this at home kids... */		\
	sp = (unsigned long __user *) src->u_regs[14];		\
	copy_from_user(&dest[16], sp,			\
		       sizeof(unsigned long) * 16);	\
	dest[32] = src->psr;				\
	dest[33] = src->pc;				\
	dest[34] = src->npc;				\
	dest[35] = src->y;				\
	dest[36] = dest[37] = 0; /* XXX */		\
} while(0); /* Janitors: Don't touch this colon. */

typedef struct {
	union {
		unsigned long	pr_regs[32];
		double		pr_dregs[16];
	} pr_fr;
	unsigned long __unused;
	unsigned long	pr_fsr;
	unsigned char	pr_qcnt;
	unsigned char	pr_q_entrysize;
	unsigned char	pr_en;
	unsigned int	pr_q[64];
} elf_fpregset_t;

#define ELF_CORE_COPY_TASK_REGS(__tsk, __elf_regs)	\
	({ ELF_CORE_COPY_REGS((*(__elf_regs)), (__tsk)->thread.kregs); 1; })

/*
 * This is used to ensure we don't load something for the wrong architecture.
 */
#define elf_check_arch(x) ((x)->e_machine == EM_SPARC)

/*
 * These are used to set parameters in the core dumps.
 */
#define ELF_ARCH	EM_SPARC
#define ELF_CLASS	ELFCLASS32
#define ELF_DATA	ELFDATA2MSB

#define USE_ELF_CORE_DUMP
#ifdef CONFIG_PADRE_16K_PAGE
#define ELF_EXEC_PAGESIZE	16384
#else
#ifdef CONFIG_PADRE_8K_PAGE
#define ELF_EXEC_PAGESIZE	8192
#else
#define ELF_EXEC_PAGESIZE	4096
#endif
#endif


/* This is the location that an ET_DYN program is loaded if exec'ed.  Typical
   use of this is to invoke "./ld.so someprog" to test out a new version of
   the loader.  We need to make sure that it is out of the way of the program
   that it will "exec", and that there is sufficient room for the brk.  */

#define ELF_ET_DYN_BASE         (0x08000000)
//#define ELF_ET_DYN_BASE         (TASK_UNMAPPED_BASE) //???

/* This yields a mask that user programs can use to figure out what
   instruction set this cpu supports.  This can NOT be done in userspace
   on Sparc.  */

#define ELF_HWCAP   HWCAP_SPARC_FLUSH
	
/* This yields a string that ld.so will use to load implementation
   specific libraries for optimization.  This is more specific in
   intent than poking at uname or /proc/cpuinfo. */

#define ELF_PLATFORM	(NULL)

#ifdef __KERNEL__
#define SET_PERSONALITY(ex, ibcs2) set_personality((ibcs2)?PER_SVR4:PER_LINUX)
#endif

#endif /* !(__ASMSPARC_ELF_H) */
