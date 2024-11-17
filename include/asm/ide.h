
#ifdef __KERNEL__
#ifndef _PADRE_IDE_H
#define _PADRE_IDE_H

#include <linux/config.h>
#include <linux/delay.h>
#include <asm/pgtable.h>
#include <asm/io.h>
#include <asm/psr.h>

#ifdef CONFIG_PADRE
#define MAX_HWIFS	8
#include <asm/padre_hw_io.h>
#define PADRE_IO_PIO 	0
#define PADRE_IO_LP 	1
#define PADRE_IO_DMA 	2
#define PADRE_UDMA	0
#define PADRE_MDMA	1

#ifndef ide_ioreg_t
typedef unsigned int ide_ioreg_t;
#endif

#define IN_BYTE(p)			padre_NSPIO.read(p)
#define OUT_BYTE(b,p)			padre_NSPIO.write((b),(p))

#define IN_WORD(p)			IN_BYTE(p)
#define OUT_WORD(b,p)			OUT_BYTE(b,p)

#define insl(port, buf, wcount)		insw(port, buf, ((wcount)<<1))
#define outsl(port, buf, wcount)	outsw(port, buf,((wcount)<<1))
#define insw(port, buf, nr)		padre_NSPIO.mport_proc(padre_3_i,(void *)port,(void *)buf,(void *)nr)
#define outsw(port, buf, nr)		padre_NSPIO.mport_proc(padre_3_o,(void *)port,(void *)buf,(void *)nr)

#define __ide_mm_insw   insw
#define __ide_mm_insl   insl
#define __ide_mm_outsw  outsw
#define __ide_mm_outsl  outsl

#endif //CONFIG_PADRE

#define HAVE_ARCH_IN_BYTE
#define HAVE_ARCH_OUT_BYTE


#ifdef OLD_CODE
typedef union {
	unsigned int		all	: 8;	/* all of the bits together */
	struct {
		unsigned int	bit7	: 1;
		unsigned int	lba	: 1;
		unsigned int	bit5	: 1;
		unsigned int	unit	: 1;
		unsigned int	head	: 4;
	} b;
} select_t;
#endif //OLD_CODE

typedef union {
	unsigned int all		: 8;	/* all of the bits together */
	struct {
		unsigned int HOB	: 1;	/* 48-bit address ordering */
		unsigned int reserved456: 3;
		unsigned bit3		: 1;	/* ATA-2 thingy */
		unsigned int SRST	: 1;	/* host soft reset bit */
		unsigned int nIEN	: 1;	/* device INTRQ to host */
		unsigned int bit0	: 1;
	} b;
} control_t;

static __inline__ int ide_request_irq(unsigned int irq,
				      irqreturn_t (*handler)(int, void *, struct pt_regs *),
				      unsigned long flags, const char *name, void *devid)
{
	return request_irq(irq, handler, flags, name, devid);
}

static __inline__ void ide_free_irq(unsigned int irq, void *dev_id)
{
	free_irq(irq, dev_id);
}

#ifdef OLD_CODE
static __inline__ int ide_check_region(ide_ioreg_t base, unsigned int size)
{
	return 0;
}

static __inline__ void ide_request_region(ide_ioreg_t base, unsigned int size,
					  const char *name)
{
}

static __inline__ void ide_release_region(ide_ioreg_t base, unsigned int size)
{
}
#endif //OLD_CODE


#undef  SUPPORT_SLOW_DATA_PORTS
#define SUPPORT_SLOW_DATA_PORTS 0

#undef  SUPPORT_VLB_SYNC
#define SUPPORT_VLB_SYNC 0

#undef  HD_DATA
#define HD_DATA ((ide_ioreg_t)0)

#define	ide__sti()	__sti()
#define ide_ack_intr(hwif)		(1)

#ifdef OLD_CODE
#define ide_release_lock(lock)		do {} while (0)
#define ide_get_lock(lock, hdlr, data)	do {} while (0)
static __inline__ void ide_fix_driveid(struct hd_driveid *id)
{
	int i;
	u16 *stringcast;

	id->config         = __le16_to_cpu(id->config);
	id->cyls           = __le16_to_cpu(id->cyls);
	id->reserved2      = __le16_to_cpu(id->reserved2);
	id->heads          = __le16_to_cpu(id->heads);
	id->track_bytes    = __le16_to_cpu(id->track_bytes);
	id->sector_bytes   = __le16_to_cpu(id->sector_bytes);
	id->sectors        = __le16_to_cpu(id->sectors);
	id->vendor0        = __le16_to_cpu(id->vendor0);
	id->vendor1        = __le16_to_cpu(id->vendor1);
	id->vendor2        = __le16_to_cpu(id->vendor2);
	stringcast = (u16 *)&id->serial_no[0];
	for (i = 0; i < (20/2); i++)
	        stringcast[i] = __le16_to_cpu(stringcast[i]);
	id->buf_type       = __le16_to_cpu(id->buf_type);
	id->buf_size       = __le16_to_cpu(id->buf_size);
	id->ecc_bytes      = __le16_to_cpu(id->ecc_bytes);
	stringcast = (u16 *)&id->fw_rev[0];
	for (i = 0; i < (8/2); i++)
	        stringcast[i] = __le16_to_cpu(stringcast[i]);
	stringcast = (u16 *)&id->model[0];
	for (i = 0; i < (40/2); i++)
	        stringcast[i] = __le16_to_cpu(stringcast[i]);
	id->dword_io       = __le16_to_cpu(id->dword_io);
	id->reserved50     = __le16_to_cpu(id->reserved50);
	id->field_valid    = __le16_to_cpu(id->field_valid);
	id->cur_cyls       = __le16_to_cpu(id->cur_cyls);
	id->cur_heads      = __le16_to_cpu(id->cur_heads);
	id->cur_sectors    = __le16_to_cpu(id->cur_sectors);
	id->cur_capacity0  = __le16_to_cpu(id->cur_capacity0);
	id->cur_capacity1  = __le16_to_cpu(id->cur_capacity1);
	id->lba_capacity   = __le32_to_cpu(id->lba_capacity);
	id->dma_1word      = __le16_to_cpu(id->dma_1word);
	id->dma_mword      = __le16_to_cpu(id->dma_mword);
	id->eide_pio_modes = __le16_to_cpu(id->eide_pio_modes);
	id->eide_dma_min   = __le16_to_cpu(id->eide_dma_min);
	id->eide_dma_time  = __le16_to_cpu(id->eide_dma_time);
	id->eide_pio       = __le16_to_cpu(id->eide_pio);
	id->eide_pio_iordy = __le16_to_cpu(id->eide_pio_iordy);
	for (i = 0; i < 2; i++)
		id->words69_70[i] = __le16_to_cpu(id->words69_70[i]);
        for (i = 0; i < 4; i++)
                id->words71_74[i] = __le16_to_cpu(id->words71_74[i]);
	id->queue_depth	   = __le16_to_cpu(id->queue_depth);
	for (i = 0; i < 4; i++)
		id->words76_79[i] = __le16_to_cpu(id->words76_79[i]);
	id->major_rev_num  = __le16_to_cpu(id->major_rev_num);
	id->minor_rev_num  = __le16_to_cpu(id->minor_rev_num);
	id->command_set_1  = __le16_to_cpu(id->command_set_1);
	id->command_set_2  = __le16_to_cpu(id->command_set_2);
	id->cfsse          = __le16_to_cpu(id->cfsse);
	id->cfs_enable_1   = __le16_to_cpu(id->cfs_enable_1);
	id->cfs_enable_2   = __le16_to_cpu(id->cfs_enable_2);
	id->csf_default    = __le16_to_cpu(id->csf_default);
	id->dma_ultra      = __le16_to_cpu(id->dma_ultra);
	id->word89         = __le16_to_cpu(id->word89);
	id->word90         = __le16_to_cpu(id->word90);
	id->CurAPMvalues   = __le16_to_cpu(id->CurAPMvalues);
	id->word92         = __le16_to_cpu(id->word92);
	id->hw_config      = __le16_to_cpu(id->hw_config);
	id->acoustic       = __le16_to_cpu(id->acoustic);
	for (i = 0; i < 5; i++)
		id->words95_99[i]  = __le16_to_cpu(id->words95_99[i]);
	id->lba_capacity_2 = __le64_to_cpu(id->lba_capacity_2);
	for (i = 0; i < 22; i++)
		id->words104_125[i]   = __le16_to_cpu(id->words104_125[i]);
	id->last_lun       = __le16_to_cpu(id->last_lun);
	id->word127        = __le16_to_cpu(id->word127);
	id->dlf            = __le16_to_cpu(id->dlf);
	id->csfo           = __le16_to_cpu(id->csfo);
	for (i = 0; i < 26; i++)
		id->words130_155[i] = __le16_to_cpu(id->words130_155[i]);
	id->word156        = __le16_to_cpu(id->word156);
	for (i = 0; i < 3; i++)
		id->words157_159[i] = __le16_to_cpu(id->words157_159[i]);
	id->cfa_power      = __le16_to_cpu(id->cfa_power);
	for (i = 0; i < 14; i++)
		id->words161_175[i] = __le16_to_cpu(id->words161_175[i]);
	for (i = 0; i < 31; i++)
		id->words176_205[i] = __le16_to_cpu(id->words176_205[i]);
	for (i = 0; i < 48; i++)
		id->words206_254[i] = __le16_to_cpu(id->words206_254[i]);
	id->integrity_word  = __le16_to_cpu(id->integrity_word);
}
#endif //OLD_CODE
#endif /* _PADRE_IDE_H */
#endif /* __KERNEL__ */

