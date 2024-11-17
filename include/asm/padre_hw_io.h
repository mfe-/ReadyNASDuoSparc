
#ifndef __PADRE_HW_IO_H
#define __PADRE_HW_IO_H

#include <linux/proc_fs.h>
#define PADRE_HWIO_MODULE_NAME_LEN	64
#define USER_CMD_SIZE   		4096

typedef enum {
  padre_0_scan, 
  padre_0_default, 
  padre_1_sir,
  padre_1_sdr,
  padre_1_mdr,
  padre_1_scb,
  padre_1_tdo,
  padre_1_scbw,
  padre_1_dioc,
  padre_1_drp,
  padre_1_dp,
  padre_1_ds,
  padre_1_xs,
  padre_1_xm,
  padre_1_ul,
  padre_1_RTE,
  padre_2_pd,
  padre_2_gddi,
  padre_2_di,
  padre_3_i,
  padre_3_o,
  padre_3_md,
  padre_3_sd,
  padre_3_mde,
  padre_4_sip,
  padre_4_al,
  padre_5_rc,
  padre_5_ts,
  padre_5_dc,
  padre_6_rrp,
} padre_hwio_datatype_t;

typedef unsigned short (padre_IO_read_t)(unsigned long);
typedef void (padre_IO_write_t)(unsigned char, unsigned long);
typedef void (padre_IO_plug_t)(void*);
typedef void (padre_IO_rescan_t)(void*,char*);
typedef unsigned int (padre_IO_err_t)(void*,void*,unsigned char);
typedef int  (padre_IO_intr_t)(int, void *data);
typedef int  (padre_IO_flush_t)(int,int);
typedef int  (padre_IO_scan_t)(int,int,int,int);
typedef int  (padre_IO_re_id_t)(void*,int);
typedef int  (padre_IO_MC_IRQ_t)(unsigned long);



typedef void (padre_PIO_proc_t)(void*,void*, unsigned int);

typedef unsigned long (padre_chip_startstop0_t)(unsigned long*);

typedef int (padre_chip_scan_t)(int);
typedef int (padre_chip_startstop1_t)(int,void*);
typedef int (padre_IO_proc_t)(int,void*, void*);
typedef int (padre_IO_MPORT_proc_t)(int,void*,void*,void*);
typedef int (padre_IO_MRXAN_proc_t)(int,void*,void*,void*,void*);
typedef int (padre_IO_MDJNM_proc_t)(int,void*,void*,
					void*,void*,void*);
typedef int (padre_IO_MLPNM_proc_t)(int,void*,void*,
					void*,void*,void*,void*);
typedef void (padre_LCD_display)(unsigned char *);

typedef struct padre_hwio_module_s {

	int				state;
	int				ssl;
	int				load_level;

	char				name[PADRE_HWIO_MODULE_NAME_LEN];
	char				*user_cmd;
	unsigned long			version;	

	unsigned int			*level1;
	unsigned int			*level2;

	int				*ssl_opt;
	int				*ssl_dma;
	int				*ssl_cnt;
	int				*ssl_dbg;
	int				*ssl_n_s;
	int				*ssl_old;
	int				*ssl_add;

	void				*hwifs;

	padre_chip_scan_t		*scan;
	padre_chip_startstop0_t		*init_c;
	padre_chip_startstop1_t		*init;

	padre_IO_proc_t			*setback;
	padre_IO_proc_t			*proc;
	padre_IO_read_t			*read;
	padre_IO_write_t		*write;
	padre_IO_plug_t			*plug;
	padre_IO_rescan_t		*chn_rescan;
	padre_IO_err_t			*error;
	padre_IO_intr_t			*intr;
	padre_IO_intr_t			*gintr;
	padre_IO_flush_t		*flush;
	padre_IO_scan_t			*chn_scan;
	padre_IO_re_id_t		*chn_re_id;

	padre_PIO_proc_t		*diskin;
	padre_PIO_proc_t		*diskout;

	padre_IO_MC_IRQ_t		*mc_map;
	padre_IO_MC_IRQ_t		*irq_map;

	padre_IO_MPORT_proc_t		*mport_proc;
	padre_IO_MRXAN_proc_t		*mrxan_proc;
	padre_IO_MDJNM_proc_t		*mdjnm_proc;
	padre_IO_MLPNM_proc_t		*mlpnm_proc;

	padre_LCD_display		*LCD_display;

	read_proc_t			*read_proc;
	read_proc_t			*read_user_cmd;
	write_proc_t			*write_user_cmd;
} padre_hwio_module_t;

extern padre_hwio_module_t padre_NSPIO;
#ifdef __init
#undef __init
#define __init
#endif
#ifdef md__init
#undef md__init
#define md__init
#endif
#endif //__PADRE_HW_IO_H
