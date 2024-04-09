/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-02-27
 *
******************************************************************************/

#ifndef PLATFORM_COMMONH
#define PLATFORM_COMMONH
/******************************************************************************/
#define _HI3798M_V100                 (0x0137980100LL)
#define _HI3796M_V100                 (0x0037980100LL)
#define _HI3798M_V100_MASK            (0xF1FFFFFF0FLL)

#define _HI3716M_V410                 (0x0137160410LL)
#define _HI3716M_V420                 (0x0037160410LL)
#define _HI3716M_V420N                (0x0037160460LL)
#define _HI3716M_V410N                (0x0137160460LL)
#define _HI3716M_V410_MASK            (0xFFFFFFFFFFLL)

#define _HI3798C_V200                 (0x0037980200LL) //(0x0020981000LL)
#define _HI3798C_V200_MASK            (0xFFFFFFFFFFLL)

#define _HI3798M_V200                 (0x0037986200LL) //(0x0020981000LL)
#define _HI3798M_V300                 (0x0037980210LL)
#define _HI3798M_V200_MASK            (0xFFFFFFFFFFLL)

#define _HI3798M_V310                 (0x0037980300LL)
#define _HI3798M_V300_H               (0x0137980300LL)
#define _HI3798M_V310_MASK            (0xFFFFFFFFFFLL)

#define _HI3796M_V200_21X21           (0x0037960200LL)
#define _HI3796M_V200_15X15           (0x0137960200LL)
#define _HI3716M_V450_21X21           (0x1037960200LL)
#define _HI3796A_V200_21X21           (0x1837960200LL)
#define _HI3796M_V200_MASK            (0xFFFFFFFFFFLL)


/* The support device every chip platform */
#define DEV_HINFC_AUTO     0x01
#define DEV_HINFC301       0x02
#define DEV_HINFC504       0x03
#define DEV_HINFC610       0x04
#define DEV_HIFMC100       0x05
#define DEV_HINFC_MASK     0x0F

#define DEV_EMMC_AUTO      0x10
#define DEV_EMMCV100       0x20
#define DEV_EMMCV200       0x20
#define DEV_EMMC_MASK      0xF0

#define DEV_HISFC_AUTO     0x100
#define DEV_HISFC300       0x200
#define DEV_HISFC350       0x300
#define DEV_HISFC400       0x400
#define DEV_NOR_HIFMC100   0x500
#define DEV_HISFC_MASK     0xF00

/* bootstrap type */
#define SELF_BOOT_TYPE_NONE           (0)  /* boot type: NONE SELF BOOT */
#define SELF_BOOT_TYPE_UART           (1)  /* boot type: UART */
#define SELF_BOOT_TYPE_USBDEV         (2)  /* boot type: USBDEV */
#define SELF_BOOT_TYPE_USBHOST        (3)  /* boot type: USBHOST */

/* chipset ca type */
#define CHIPSET_CATYPE_INVALID        (-1) /* chipset catype: invalid type */
#define CHIPSET_CATYPE_NORMAL         (0)  /* chipset catype: NORMAL */
#define CHIPSET_CATYPE_CA             (1)  /* chipset catype: CA */

/* board type */
/* for hi3798cv2x board type. */
#define BOARD_TYPE_0            0x1
#define BOARD_TYPE_1            0x2
#define BOARD_TYPE_2            0x3
#define BOARD_TYPE_RESERVED     0x10
#define BOARD_TYPE_INVALID      0x11
/******************************************************************************/
#endif /* PLATFORM_COMMONH */
