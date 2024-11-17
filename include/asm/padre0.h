/*=========================================================================
 * FILENAME	: include/asm-sparc/padre0.h
 * DESCRIPTION	: Header file for IT1004/IT1008/IT3107/IT3102
 * Version	: $Revision: 1.2 $
 * Last Update	: $Date: 2007-02-08 23:31:34 $
 *=========================================================================
 * Infrant Technologies, Inc. Proprietary and Confidential
 *	      Copyright (c) 2003-, INFRANT
 *		 All Rights Reserved
 *=========================================================================
 *
 * $Id: padre0.h,v 1.2 2007-02-08 23:31:34 jason Exp $
 *
 *
 * (C) Copryright Infrant Technologies, Inc.  2003-
 */

#ifndef __PADRE0_H
#define __PADRE0_H

#define PADRE

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 *$$$$$$$   NEON PROCESSOR CONSTANT  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 *$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
/* ASI codes */
#define ASI_U_I		0x08
#define ASI_S_I		0x09
#define ASI_U_D		0x0a
#define ASI_S_D		0x0b
#define ASI_MMU		0x10
#define ASI_TLBPROBE	0x11
#define ASI_ICMU	0x14
#define ASI_DCMU	0x15

/* PSR register */
#define PADRE_NEON_PSR_IMPL	(0xf << 28)
#define PADRE_NEON_PSR_VER	(0xf << 24)
#define PADRE_NEON_PSR_ICC	(0xf << 20)
#define PADRE_NEON_PSR_ICC_N	(1 << 23)
#define PADRE_NEON_PSR_ICC_Z	(1 << 22)
#define PADRE_NEON_PSR_ICC_V	(1 << 21)
#define PADRE_NEON_PSR_ICC_C	(1 << 20)
#define PADRE_NEON_PSR_IM	(1 << 8)
#define PADRE_NEON_PSR_S	(1 << 7)
#define PADRE_NEON_PSR_PS	(1 << 6)
#define PADRE_NEON_PSR_ET	(1 << 5)
#define PADRE_NEON_PSR_CWP	(0x1f << 0)

/* WIM register */
#define PADRE_NEON_WIM_WIM	(0xff << 0)

/* TBR register */
#define PADRE_NEON_TBR_TBA	(0xfffff << 12)
#define PADRE_NEON_TBR_TT	(0xff << 4)

/* -- TT Field Definition -- */
#define TT_instruction_access_MMU_miss		0x3c
#define TT_instruction_access_error		0x21
#define TT_instruction_access_exception		0x01
#define TT_privileged_instruction		0x03
#define TT_illegal_instruction			0x02
#define TT_fp_disabled				0x04
#define TT_cp_disabled				0x24
#define	TT_trap_instruction_base		0x80
#define	TT_trap_instruction(n)			(TT_Trap_instruction_base+(n))
#define TT_window_overflow			0x05
#define TT_window_underflow			0x06
#define TT_mem_address_not_aligned		0x07
#define TT_data_access_error			0x29
#define TT_tag_overflow				0x0a
#define TT_division_by_zero			0x2a
#define TT_data_access_MMU_miss			0x2c
#define TT_data_access_exception		0x09
#define TT_interrupt_base			0x10
#define TT_interrupt(n)				(TT_interrupt_base+(n))

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *@@@@@@@@   ASI=00 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/*********************************************************************************
 * AHB PERIPHERAL SPACE BASE DEFINITION
 *   note: address on the AHB bus, that is physical address.
 *********************************************************************************/
#define PADRE_TLB_ENABLE   1
#define PADRE_ROM_SPACE (0x00000000+0x40000000*PADRE_TLB_ENABLE)
#define PADRE_PCI_SPACE (0x10000000+0x40000000*PADRE_TLB_ENABLE)
#define PADRE_APB_SPACE (0x20000000+0x40000000*PADRE_TLB_ENABLE)
#define PADRE_S3_SPACE  (0x30000000+0x40000000*PADRE_TLB_ENABLE)
#define PADRE_DDR_SPACE (0x40000000+0x40000000*PADRE_TLB_ENABLE)


/*..............................................................................*
 * PCI IO DEFINITION
 *..............................................................................*/
#define PADRE_PCI_CONFIG_ADDRESS	(PADRE_PCI_SPACE + 0x0cf8)
#define	  PADRE_PCI_CONFIG_ADDRESS_EN		0x80000000
#define	  PADRE_PCI_CONFIG_ADDRESS_BUS		0x00ff0000
#define	  PADRE_PCI_CONFIG_ADDRESS_DEV		0x0000f800
#define	  PADRE_PCI_CONFIG_ADDRESS_FUNC		0x00000700
#define	  PADRE_PCI_CONFIG_ADDRESS_REG		0x000000fc
#define PADRE_PCI_CONFIG_DATA		(PADRE_PCI_SPACE + 0x0cfc)

/*..............................................................................*
 * S3 DEFINITION
 *..............................................................................*/
#define PADRE_S3_RAMTOP			(PADRE_S3_SPACE + 0x00000000)
#define PADRE_S3_LOCK(n32)		(PADRE_S3_SPACE + 0x01000000 + ((n32)<<4))
#define PADRE_S3_UNLOCK(n32)		(PADRE_S3_SPACE + 0x01000004 + ((n32)<<4))
#define PADRE_S3_RAMTOP_CACHEABLE	(PADRE_S3_SPACE + 0x04000000)


/*********************************************************************************
 * APB PERIPHERAL BASE DEFINITION
 *********************************************************************************/
/* PADRE IO ON APB */
#define PADRE_INTC0_BASE	(PADRE_APB_SPACE + 0x0000000)
#define PADRE_INTC1_BASE	(PADRE_APB_SPACE + 0x0000020)
#define PADRE_TM_BASE		(PADRE_APB_SPACE + 0x0000040)
#define PADRE_UART0_BASE	(PADRE_APB_SPACE + 0x0000060)
#define PADRE_UART1_BASE	(PADRE_APB_SPACE + 0x0000070)
#define PADRE_SYS_BASE		(PADRE_APB_SPACE + 0x0000080) /* SYS/MBIST/PLL */
#define PADRE_GPIO_BASE		(PADRE_APB_SPACE + 0x00000c0)
#define PADRE_PCI_BASE		(PADRE_APB_SPACE + 0x0000100)

#define PADRE_IDE0_BASE		(PADRE_APB_SPACE + 0x0000200)
#define PADRE_IDE1_BASE		(PADRE_APB_SPACE + 0x0000280)
#define PADRE_IDE2_BASE		(PADRE_APB_SPACE + 0x0000300)
#define PADRE_IDE3_BASE		(PADRE_APB_SPACE + 0x0000380)
#define PADRE_IDE4_BASE		(PADRE_APB_SPACE + 0x0000400)
#define PADRE_IDE5_BASE		(PADRE_APB_SPACE + 0x0000480)
#define PADRE_IDE6_BASE		(PADRE_APB_SPACE + 0x0000500)
#define PADRE_IDE7_BASE		(PADRE_APB_SPACE + 0x0000580)

#define PADRE_AU_BASE		(PADRE_APB_SPACE + 0x0000600)
#define PADRE_M4_BASE		(PADRE_APB_SPACE + 0x0000700)
#define PADRE_ASIO_BASE		(PADRE_APB_SPACE + 0x0000800)
#define PADRE_LP_BASE		(PADRE_APB_SPACE + 0x0001000)
#define PADRE_MC_BASE		(PADRE_APB_SPACE + 0x0002000)
#define PADRE_CP0_BASE		(PADRE_APB_SPACE + 0x0003000)
#define PADRE_CP1_BASE		(PADRE_APB_SPACE + 0x0004000)

#define PADRE_DJ_BASE		(PADRE_APB_SPACE + 0x0005000)
#define PADRE_RXA_BASE		(PADRE_APB_SPACE + 0x0006000)
#define PADRE_SATA0_BASE	(PADRE_APB_SPACE + 0x0007000)
#define PADRE_SATA1_BASE	(PADRE_APB_SPACE + 0x0007100)
#define PADRE_SATA2_BASE	(PADRE_APB_SPACE + 0x0007200)
#define PADRE_SATA3_BASE	(PADRE_APB_SPACE + 0x0007300)
#define PADRE_SATA4_BASE	(PADRE_APB_SPACE + 0x0007400)
#define PADRE_SATA5_BASE	(PADRE_APB_SPACE + 0x0007500)
#define PADRE_SATA6_BASE	(PADRE_APB_SPACE + 0x0007600)
#define PADRE_SATA7_BASE	(PADRE_APB_SPACE + 0x0007700)
#define PADRE_GM0_BASE		(PADRE_APB_SPACE + 0x0010000)
#define PADRE_GM1_BASE		(PADRE_APB_SPACE + 0x0020000)

/*..............................................................................*
 * APB REGISTER DEFINITION
 *..............................................................................*/


/*****************************************************************************/
/* INTC0 */
#define PADRE_INTC0_MASK_H			(PADRE_INTC0_BASE + 0x00)
#define PADRE_INTC0_MASK_L			(PADRE_INTC0_BASE + 0x04)
#define PADRE_INTC0_IFORCE_H			(PADRE_INTC0_BASE + 0x10)
#define PADRE_INTC0_IFORCE_L			(PADRE_INTC0_BASE + 0x14)
#define PADRE_INTC0_ICAUSE_H			(PADRE_INTC0_BASE + 0x18)
#define PADRE_INTC0_ICLR_H			(PADRE_INTC0_BASE + 0x18)
#define PADRE_INTC0_ICAUSE_L			(PADRE_INTC0_BASE + 0x1c)
#define PADRE_INTC0_ICLR_L			(PADRE_INTC0_BASE + 0x1C)

/* INTC1 */
#define PADRE_INTC1_IFORCE_H			(PADRE_INTC1_BASE + 0x10)
#define PADRE_INTC1_IFORCE_L			(PADRE_INTC1_BASE + 0x14)

/*****************************************************************************/
/* TM */
#define PADRE_TM_CTRL				(PADRE_TM_BASE + 0x00)
#define	  PADRE_TM_CTRL_STP				0x00001000
#define PADRE_TM_PS				(PADRE_TM_BASE + 0x04)
#define PADRE_TM_CNTDIAG			(PADRE_TM_BASE + 0x0c)
#define PADRE_TM_TIMER0                         (PADRE_TM_BASE + 0x10)
#define PADRE_TM_TIMER1				(PADRE_TM_BASE + 0x14)
#define PADRE_TM_TIMER2				(PADRE_TM_BASE + 0x18)

/* UART0 */
#define PADRE_UART0_DATA			(PADRE_UART0_BASE + 0x00)
#define PADRE_UART0_STAT			(PADRE_UART0_BASE + 0x04)
#define	  PADRE_UART0_STAT_FE				0x00000040
#define	  PADRE_UART0_STAT_PE				0x00000020
#define	  PADRE_UART0_STAT_OV				0x00000010
#define	  PADRE_UART0_STAT_BR				0x00000008
#define	  PADRE_UART0_STAT_TH				0x00000004
#define	  PADRE_UART0_STAT_DR				0x00000001
#define PADRE_UART0_CTRL			(PADRE_UART0_BASE + 0x08)
#define   PADRE_UART0_CTRL_TF				0x00000200
#define   PADRE_UART0_CTRL_RF				0x00000100
#define	  PADRE_UART0_CTRL_TI				0x00000008
#define	  PADRE_UART0_CTRL_RI				0x00000004
#define	  PADRE_UART0_CTRL_TE				0x00000002
#define	  PADRE_UART0_CTRL_RE				0x00000001

/* UART1 */
#define PADRE_UART1_DATA			(PADRE_UART1_BASE + 0x00)
#define PADRE_UART1_STAT			(PADRE_UART1_BASE + 0x04)
#define	  PADRE_UART1_STAT_FE				0x00000040
#define	  PADRE_UART1_STAT_PE				0x00000020
#define	  PADRE_UART1_STAT_OV				0x00000010
#define	  PADRE_UART1_STAT_BR				0x00000008
#define	  PADRE_UART1_STAT_TH				0x00000004
#define	  PADRE_UART1_STAT_DR				0x00000001
#define PADRE_UART1_CTRL			(PADRE_UART1_BASE + 0x08)
#define	  PADRE_UART1_CTRL_TI				0x00000008
#define	  PADRE_UART1_CTRL_RI				0x00000004
#define PADRE_UART1_SCAL			(PADRE_UART1_BASE + 0x0c)

/* SYS/MBIST/PLL */
#define PADRE_MBIST_MODE			(PADRE_SYS_BASE + 0x00)
#define	  PADRE_MBIST_MODE_EN				(1<<0)
#define	    PADRE_MBIST_MODE_ALGORITHM__W			(0)
#define	  PADRE_MBIST_MODE_DONE				(1<<9)
#define PADRE_MBIST_ADDR			(PADRE_SYS_BASE + 0x08)
#define PADRE_MBIST_DATA			(PADRE_SYS_BASE + 0x0c)
#define PADRE_SYS_ID				(PADRE_SYS_BASE + 0x10)
#define PADRE_SYS_CTRL				(PADRE_SYS_BASE + 0x14)
#define PADRE_SYS_STRAP				(PADRE_SYS_BASE + 0x18)
#define PADRE_SYS_TRACE				(PADRE_SYS_BASE + 0x1c)
#define   PADRE_SYS_TRACE_MODE				0x00000007
#define     PADRE_SYS_TRACE_MODE__RESET				(7)

/* GPIO */
#define PADRE_GPIO_DATA				(PADRE_GPIO_BASE + 0x00)
#define PADRE_GPIO_DIR				(PADRE_GPIO_BASE + 0x04)

#define PADRE_ATA_LED_USE                       2       /* each ata use 2 led */
#define PADRE_ATA_LED_IO                        0

/*****************************************************************************/
/* MC */

#define PADRE_MC_DMA_FFCTRL(n20)		(PADRE_MC_BASE + 0x800 + ((n20)<<4))
#define	  PADRE_DMA_FFCTRL_EN				0x00008000
#define	  PADRE_DMA_FFCTRL_ACT				0x00004000
#define	    PADRE_DMA_FFCTRL_LFFS__256				(8)
#define	    PADRE_DMA_FFCTRL_LFFS__512				(9)
#define	    PADRE_DMA_FFCTRL_LFFS__1K				(10)
#define PADRE_MC_DMA_BASE(n20)			(PADRE_MC_BASE + 0x804 + ((n20)<<4))
#define PADRE_MC_DMA_ADDR(n20)			(PADRE_MC_BASE + 0x808 + ((n20)<<4))
#define PADRE_MC_DMA_LEN(n20)			(PADRE_MC_BASE + 0x80c + ((n20)<<4))
#define	  PADRE_DMA_LEN_WRT				0x01000000
#define	  PADRE_DMA_LEN_EOP				0x02000000

/*****************************************************************************/
/* PCI */
#define PADRE_PCI_SWAP				(PADRE_PCI_BASE + 0x04)
#define PADRE_PCI_FLASH				(PADRE_PCI_BASE + 0x08)
#define	  PADRE_PCI_FLASH_OE_MRPn			(1<<5)
#define	  PADRE_PCI_FLASH_OE_MVPEN			(1<<4)
#define	  PADRE_PCI_FLASH_DAT_MRPn			(1<<1)
#define	  PADRE_PCI_FLASH_DAT_MVPEN			(1<<0)
#define PADRE_PCI_FEATURE			(PADRE_PCI_BASE + 0x0c)
#define	  PADRE_PCI_FEATURE_PCION			(1<<2)

/*****************************************************************************/
/* LP */
#define PADRE_LP_CH_ENABLE			(PADRE_LP_BASE + 0x004)
#define PADRE_LP_CH_TRIG			(PADRE_LP_BASE + 0x00c)
#define PADRE_LP_VERSION			(PADRE_LP_BASE + 0x028)
#define	  PADRE_LP_VERSION_HWVER			0xf000
#define	  PADRE_LP_VERSION_FWVER			0x0fff
#define PADRE_LP_CONTROL			(PADRE_LP_BASE + 0x02c)

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *@@@@@@@@   DMA CHANNEL ASSIGNMENT  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#define PADRE_DMA_CH_GMAC0RX				0
#define PADRE_DMA_CH_GMAC0TX				1
#define PADRE_DMA_CH_GMAC1RX                            2
#define PADRE_DMA_CH_GMAC1TX                            3
#define PADRE_DMA_CH_IDE0				4
#define PADRE_DMA_CH_IDE3				7
#define PADRE_DMA_CH_IDE7				11
#define PADRE_DMA_CH_CP0IN				12
#define PADRE_DMA_CH_CP0OUT				13
#define PADRE_DMA_CH_RXAIN				16
#define PADRE_DMA_CH_RXAOUT				17
#define PADRE_DMA_CH_AUIN				18
#define PADRE_DMA_CH_AUOUT				19

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *@@@@@@@@   ASI!=0 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

/* MMU (ASI_MMU) */
#define	PADRE_MMU_CONTROL			0x00000004
#define	  PADRE_MMU_CONTROL_FL				0x00000020
#define	  PADRE_MMU_CONTROL_NF				0x00000004
#define	  PADRE_MMU_CONTROL_DE				0x00000002
#define	  PADRE_MMU_CONTROL_IE				0x00000001
#define	PADRE_MMU_TLBL				0x00000008
#define PADRE_MMU_TLBH				0x0000000c
#define PADRE_MMU_DFSR				0x00000010
#define	  PADRE_MMU_DFSR_V				0x00000001
#define PADRE_MMU_IFSR				0x00000014
#define PADRE_MMU_DFADDR			0x00000018
#define PADRE_MMU_CACHEABLE			0x0000001c
#define	  PADRE_MMU_CACHEABLE_TH			0x7f000000
#define PADRE_MMU_PGT				0x00000024
#define	  PADRE_MMU_PGT_CACHE				0x00000004
#define	  PADRE_MMU_PGT_FL				0x00000002
#define	  PADRE_MMU_PGT_EN				0x00000001

/* TLB (ASI_TLBPROBE) */


/* ICMU (ASI_ICMU) */
#define	PADRE_ICMU_ITAG				0x00010000
#define	PADRE_ICMU_IRD				0x00020000
#define	PADRE_ICMU_CTRL				0x00030000
#define	  PADRE_ICMU_CTRL_IC3TAG			0xfffff800
#define	  PADRE_ICMU_CTRL_IC3				0x00000004
#define	  PADRE_ICMU_CTRL_TM				0x00000002
#define	  PADRE_ICMU_CTRL_EN				0x00000001

/* DCMU (ASI_DCMU) */
#define	PADRE_DCMU_DCD				0x00000000
#define	PADRE_DCMU_DTAG				0x00010000
#define	  PADRE_DCMU_DTAG_V				0x00000001
#define	PADRE_DCMU_DRD				0x00020000
#define	PADRE_DCMU_CTRL				0x00030000
#define	  PADRE_DCMU_CTRL_DC3TAG			0xfffff800
#define	  PADRE_DCMU_CTRL_FORCE				0x00000040
#define	    PADRE_DCMU_CTRL_PROBE__INV				(1)
#define	    PADRE_DCMU_CTRL_PROBE__CLEAN			(2)
#define	    PADRE_DCMU_CTRL_PROBE__INVCLN			(3)
#define	  PADRE_DCMU_CTRL_WT				0x00000008
#define	  PADRE_DCMU_CTRL_DC3				0x00000004
#define	  PADRE_DCMU_CTRL_TM				0x00000002
#define	  PADRE_DCMU_CTRL_EN				0x00000001

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *@@@@@@@@   PGT/PTE  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#define _PAGE_PTE_PTR	0xfffff000
#define _PAGE_BIGPPN	0xfff00000
#define _PAGE_PPN	0xfffff000
#define _PAGE_U		0x200
#define _PAGE_R		0x100
#define _PAGE_W		0x080
#define _PAGE_X		0x040
#define _PAGE_C		0x020
#define _PAGE_T		0x010
#define _PAGE_A		0x008
#define _PAGE_D		0x004
#define _PAGE_Z		0x002
#define _PAGE_V		0x001

#define _PAGE_BIT_U	9
#define _PAGE_BIT_R	8
#define _PAGE_BIT_W	7
#define _PAGE_BIT_X	6
#define _PAGE_BIT_C	5
#define _PAGE_BIT_T	4
#define _PAGE_BIT_A	3
#define _PAGE_BIT_D	2
#define _PAGE_BIT_Z	1
#define _PAGE_BIT_V	0

/****** some definition for C *******/
#ifndef __ASSEMBLER__
#define LSB_OF(X)	(((X)&0x00000001)?0: \
			 ((X)&0x00000002)?1: \
			 ((X)&0x00000004)?2: \
			 ((X)&0x00000008)?3: \
			 ((X)&0x00000010)?4: \
			 ((X)&0x00000020)?5: \
			 ((X)&0x00000040)?6: \
			 ((X)&0x00000080)?7: \
			 ((X)&0x00000100)?8: \
			 ((X)&0x00000200)?9: \
			 ((X)&0x00000400)?10: \
			 ((X)&0x00000800)?11: \
			 ((X)&0x00001000)?12: \
			 ((X)&0x00002000)?13: \
			 ((X)&0x00004000)?14: \
			 ((X)&0x00008000)?15: \
			 ((X)&0x00010000)?16: \
			 ((X)&0x00020000)?17: \
			 ((X)&0x00040000)?18: \
			 ((X)&0x00080000)?19: \
			 ((X)&0x00100000)?20: \
			 ((X)&0x00200000)?21: \
			 ((X)&0x00400000)?22: \
			 ((X)&0x00800000)?23: \
			 ((X)&0x01000000)?24: \
			 ((X)&0x02000000)?25: \
			 ((X)&0x04000000)?26: \
			 ((X)&0x08000000)?27: \
			 ((X)&0x10000000)?28: \
			 ((X)&0x20000000)?29: \
			 ((X)&0x40000000)?30:31)
#define BIT_INS(X,B)	(((X)<<LSB_OF(B))&(B))
#endif /* __ASSEMBLER__ */

#define SYSTEM_TYPE_PADRE	0
#define SYSTEM_TYPE_PZERO	1

#endif /* __PADRE0_H */
