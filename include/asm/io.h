/*
 * $Id: io.h,v 1.2 2006-09-15 21:42:19 jason Exp $
 */
#ifndef __SPARC_IO_H
#define __SPARC_IO_H

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/ioport.h>  /* struct resource */

#include <asm/page.h>      /* IO address mapping routines need this */
#include <asm/system.h>

#define PADRE_DMA_BIDIRECTIONAL   0
#define PADRE_DMA_TODEVICE        1
#define PADRE_DMA_FROMDEVICE      2
#define PADRE_DMA_NONE            3

#define PHYS_BASE   0x40000000UL
#define virt_to_bus(addr)   ((unsigned long)(addr) - PHYS_BASE)
#define bus_to_virt(addr)   ((unsigned long)(addr) + PHYS_BASE)
#define page_to_phys(page)     ((((page) - mem_map) << PAGE_SHIFT)+PHYS_BASE)
			
static inline u32 flip_dword (u32 l)
{
        return ((l&0xff)<<24) | (((l>>8)&0xff)<<16) | (((l>>16)&0xff)<<8)| ((l>>24)&0xff);
}

static inline u16 flip_word (u16 w)
{
        return ((w&0xff) << 8) | ((w>>8)&0xff);
}

#define mmiowb()

/*
 * Memory mapped I/O to PCI
 *
 * Observe that ioremap returns void* cookie, but accessors, such
 * as readb, take unsigned long as address, by API. This mismatch
 * happened historically. The ioremap is much older than accessors,
 * so at one time ioremap's cookie was used as address (*a = val).
 * When accessors came about, they were designed to be compatible across
 * buses, so that drivers can select proper ones like sunhme.c did.
 * To make that easier, they use same aruments (ulong) for sbus, pci, isa.
 * The offshot is, we must cast readb et. al. arguments with a #define.
 */

#ifdef CONFIG_PADRE

static inline u8 __raw_readb(const volatile void __iomem *addr)
{
        return *(__force volatile u8 *)addr;
}

static inline u16 __raw_readw(const volatile void __iomem *addr)
{
        return *(__force volatile u16 *)addr;
}

static inline u32 __raw_readl(const volatile void __iomem *addr)
{
        return *(__force volatile u32 *)addr;
}

static inline void __raw_writeb(u8 b, volatile void __iomem *addr)
{
        *(__force volatile u8 *)addr = b;
}

static inline void __raw_writew(u16 w, volatile void __iomem *addr)
{
        *(__force volatile u16 *)addr = w;
}

static inline void __raw_writel(u32 l, volatile void __iomem *addr)
{
        *(__force volatile u32 *)addr = l;
}

#else

static inline u8 __raw_readb(unsigned long addr)
{
	return *(volatile u8 *)addr;
}

static inline u16 __raw_readw(unsigned long addr)
{
	return *(volatile u16 *)addr;
}

static inline u32 __raw_readl(unsigned long addr)
{
	return *(volatile u32 *)addr;
}

static inline void __raw_writeb(u8 b, unsigned long addr)
{
	*(volatile u8 *)addr = b;
}

static inline void __raw_writew(u16 w, unsigned long addr)
{
	*(volatile u16 *)addr = w;
}

static inline void __raw_writel(u32 l, unsigned long addr)
{
	*(volatile u32 *)addr = l;
}

#endif

#ifdef CONFIG_PADRE
static inline u8 __readb(const volatile void __iomem *addr)
{
        return *(__force volatile u8 *)addr;
}

static inline u16 __readw(const volatile void __iomem *addr)
{
        return *(__force volatile u16 *)addr;
}

static inline u32 __readl(const volatile void __iomem *addr)
{
        return *(__force volatile u32 *)addr;
}

static inline void __writeb(u8 b, volatile void __iomem *addr)
{
        *(__force volatile u8 *)addr = b;
}

static inline void __writew(u16 w, volatile void __iomem *addr)
{
        *(__force volatile u16 *)addr = w;
}

static inline void __writel(u32 l, volatile void __iomem *addr)
{
        *(__force volatile u32 *)addr = l;
}
#else
static inline u8 __readb(unsigned long addr)
{
	return *(volatile u8 *)addr;
}

static inline u16 __readw(unsigned long addr)
{
	return *(volatile u16 *)addr;
}

static inline u32 __readl(unsigned long addr)
{
	return *(volatile u32 *)addr;
}

static inline void __writeb(u8 b, unsigned long addr)
{
	*(volatile u8 *)addr = b;
}

static inline void __writew(u16 w, unsigned long addr)
{
	*(volatile u16 *)addr = w;
}

static inline void __writel(u32 l, unsigned long addr)
{
	*(volatile u32 *)addr = l;
}
#endif

#ifdef CONFIG_PADRE
#define readb(__addr)           __readb((void __iomem *)(unsigned long)__addr)
#define readw(__addr)           __readw((void __iomem *)(unsigned long)__addr)
#define readl(__addr)           __readl((void __iomem *)(unsigned long)__addr)
#define readb_relaxed(__addr)   readb(__addr)
#define readw_relaxed(__addr)   readw(__addr)
#define readl_relaxed(__addr)   readl(__addr)

#define writeb(__b, __addr)     __writeb((__b),(void __iomem *)(unsigned long)(__addr))
#define writew(__w, __addr)     __writew((__w),(void __iomem *)(unsigned long)(__addr))
#define writel(__l, __addr)     __writel((__l),(void __iomem *)(unsigned long)(__addr))

#else

#define readb(__addr)		__readb((unsigned long)(__addr))
#define readw(__addr)		__readw((unsigned long)(__addr))
#define readl(__addr)		__readl((unsigned long)(__addr))
#define readb_relaxed(__addr)	readb(__addr)
#define readw_relaxed(__addr)	readw(__addr)
#define readl_relaxed(__addr)	readl(__addr)

#define writeb(__b, __addr)	__writeb((__b),(unsigned long)(__addr))
#define writew(__w, __addr)	__writew((__w),(unsigned long)(__addr))
#define writel(__l, __addr)	__writel((__l),(unsigned long)(__addr))
#endif

/*
 * I/O space operations
 *
 * Arrangement on a Sun is somewhat complicated.
 *
 * First of all, we want to use standard Linux drivers
 * for keyboard, PC serial, etc. These drivers think
 * they access I/O space and use inb/outb.
 * On the other hand, EBus bridge accepts PCI *memory*
 * cycles and converts them into ISA *I/O* cycles.
 * Ergo, we want inb & outb to generate PCI memory cycles.
 *
 * If we want to issue PCI *I/O* cycles, we do this
 * with a low 64K fixed window in PCIC. This window gets
 * mapped somewhere into virtual kernel space and we
 * can use inb/outb again.
 */
#ifdef CONFIG_PADRE

#define inb_local(__addr)       __readb((void __iomem *)(unsigned long)(__addr))
#define inb(__addr)             __readb((void __iomem *)(unsigned long)(__addr))
#define inw(__addr)             __readw((void __iomem *)(unsigned long)(__addr))
#define inl(__addr)             __readl((void __iomem *)(unsigned long)(__addr))

#define outb_local(__b, __addr) __writeb(__b, (void __iomem *)(unsigned long)(__addr))
#define outb(__b, __addr)       __writeb(__b, (void __iomem *)(unsigned long)(__addr))
#define outw(__w, __addr)       __writew(__w, (void __iomem *)(unsigned long)(__addr))
#define outl(__l, __addr)       __writel(__l, (void __iomem *)(unsigned long)(__addr))

#else

#define inb_local(__addr)	__readb((unsigned long)(__addr))
#define inb(__addr)		__readb((unsigned long)(__addr))
#define inw(__addr)		__readw((unsigned long)(__addr))
#define inl(__addr)		__readl((unsigned long)(__addr))

#define outb_local(__b, __addr)	__writeb(__b, (unsigned long)(__addr))
#define outb(__b, __addr)	__writeb(__b, (unsigned long)(__addr))
#define outw(__w, __addr)	__writew(__w, (unsigned long)(__addr))
#define outl(__l, __addr)	__writel(__l, (unsigned long)(__addr))

#endif

#define inb_p(__addr)		inb(__addr)
#define outb_p(__b, __addr)	outb(__b, __addr)
#define inw_p(__addr)		inw(__addr)
#define outw_p(__w, __addr)	outw(__w, __addr)
#define inl_p(__addr)		inl(__addr)
#define outl_p(__l, __addr)	outl(__l, __addr)

extern void outsb(unsigned long addr, const void *src, unsigned long cnt);
extern void outsw(unsigned long addr, const void *src, unsigned long cnt);
extern void outsl(unsigned long addr, const void *src, unsigned long cnt);
extern void insb(unsigned long addr, void *dst, unsigned long count);
extern void insw(unsigned long addr, void *dst, unsigned long count);
extern void insl(unsigned long addr, void *dst, unsigned long count);

struct led_ctrl_func {
        void    (* do_power_led_ctrl)(int);
        void    (* do_misc_led_ctrl)(int led, int status);
        void    (* do_mount_led_ctrl)(int dev, int status);
        void    (* do_ata_led_wait)(int, int);
        void    (* do_ata_led)(int, int, int, int);
        void    (* do_ata_led_correct)(void);
};
extern struct led_ctrl_func padre_led_handler;

#ifdef CONFIG_PADRE_I2C
extern int i2c_device_exist(u8 dev_id);

extern void i2c_writeb(u8 dev_id,u8 data);
extern u8 i2c_readb(u8 dev_id);
extern void i2c_writew(u8 dev_id, u16 data);
extern u16 i2c_readw(u8 dev_id);

extern void i2c_writeb_idx(u8 dev_id, u8 idx, u8 data);
extern u8 i2c_readb_idx(u8 dev_id, u8 idx);
extern void i2c_writew_idx(u8 dev_id, u8 idx, u16 data);
extern u16 i2c_readw_idx(u8 dev_id, u8 idx);
extern u32 i2c_readl_idx(u8 dev_id, u8 idx);

extern void padre_ata_led(int ch, int on, int count, int type);
extern void padre_ate_led_correct(void);
#else
//#define padre_ata_led(ch,on,count,type)
#endif

#define CONFIG_PADRE_AHBARB     7
#define IO_SPACE_LIMIT 0xffffffff

#define PADRE_HWMON_MINOR       64
#define PADRE_HWMAPPING_MINOR 	65
#define PADRE_CPU2DEV_MINOR     66
#define PADRE_CPU2INITRD_MINOR  67
#define PADRE_HWCP_MINOR        68

#ifdef __KERNEL__

#define memcpy_fromio		    memcpy
#define memcpy_toio		    memcpy
#define ioremap(__offset,__size)    ((void *)(__offset))
#define ioremap_nocache(X,Y)        ioremap((X),(Y))
#define iounmap(__addr)             do { } while(0)

/*
 * At the moment, we do not use CMOS_READ anywhere outside of rtc.c,
 * so rtc_port is static in it. This should not change unless a new
 * hardware pops up.
 */
#define RTC_PORT(x)   (rtc_port + (x))
#define RTC_ALWAYS_BCD  0

/* Nothing to do */
/* P3: Only IDE DMA may need these. XXX Verify that it still does... */

#define dma_cache_inv(_start,_size)		do { } while (0)
#define dma_cache_wback(_start,_size)		do { } while (0)
#define dma_cache_wback_inv(_start,_size)	do { } while (0)

#endif

#define __ARCH_HAS_NO_PAGE_ZERO_MAPPED          1

/*
 * Convert a physical pointer to a virtual kernel pointer for /dev/mem
 * access
 */
#define xlate_dev_mem_ptr(p)    __va(p)

/*
 * Convert a virtual cached pointer to an uncached pointer
 */
#define xlate_dev_kmem_ptr(p)   p

#define ioread8		readb
#define ioread16	readw
#define ioread32	readl
#define iowrite8	writeb
#define iowrite16	writew
#define iowrite32	writel


#endif /* !(__SPARC_IO_H) */
