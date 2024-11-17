/**************************************************************************
 * Filename : include/asm/ds1337.h
 * Version  : 1.0
 * Last Update  : $Date: 2006-08-28 17:51:47 $
 * Infrant Technologies, Inc. Proprietary and Confidential
 *        Copyright (c) 2001, INFRANT
 *       All Rights Reserved*
 **************************************************************************/

#ifndef _ASM_DS1337_h
#define _ASM_DS1337_h
extern spinlock_t rtc_lock;     /* serialize CMOS RAM access */

/**********************************************************************
 * register summary
 **********************************************************************/
#define RTC_SECONDS 		0x0
#define RTC_MINUTES 		0x1
#define RTC_HOURS 			0x2
#define RTC_WEEKDAY 		0x3
#define RTC_DAY_OF_MONTH 	0x4
#define RTC_MONTH 			0x5
#define RTC_YEAR 			0x6
#define	RTC_SECONDS_ALARM1	0x7
#define RTC_MINUTES_ALARM1	0x8
#define RTC_HOURS_ALARM1	0x9
#define RTC_DAY_DATE_ALARM1	0xa
#define RTC_MINUTES_ALARM2	0xb
#define RTC_HOURS_ALARM2	0xc
#define RTC_DAY_DATE_ALARM2	0xd
#define RTC_CONTROL 		0xe
#define RTC_STATUS 			0xf



#define RTC_HOURS_12_24		(1<<6)
#define RTC_HOURS_AM_PM		(1<<5)

#define RTC_MONTH_CENTURY	(1<<7)

#define RTC_CONTROL_EOSC	(0x0<<7)
#define RTC_STATUS_OSF		(0x1<<7)

/* Padre use Alarm 1 as Alarm, and use it to do schedule power on */
/* RTC_INTCN must be 1 so that alarm1/2 are independent */
#define RTC_AIE                 (1<<0)
#define RTC_INTCN               (1<<2)
#define RTC_AIF                 (1<<0)

/*
 * Conversion between binary and BCD.
 */
#ifndef BCD_TO_BIN
#define BCD_TO_BIN(val) ((val)=((val)&15) + ((val)>>4)*10)
#endif

#ifndef BIN_TO_BCD
#define BIN_TO_BCD(val) ((val)=(((val)/10)<<4) + (val)%10)
#endif

extern unsigned int CMOS_READ(unsigned int reg);
extern void CMOS_WRITE(unsigned int val, unsigned int reg);
#endif /* _ASM_DS1337_h */
