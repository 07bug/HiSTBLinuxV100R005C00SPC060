/*
 * (C) Copyright 2009, HISILICON
 * Configuation settings for the godbox board.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <asm/arch/platform.h>

#ifndef __CONFIG_HI3716MV410_H__
#define __CONFIG_HI3716MV410_H__
#define CONFIG_ARCH_HI3716MV410

/* Arm configuration*/
#define CONFIG_L2_OFF
#define CONFIG_SYS_DCACHE_OFF
#define CONFIG_SYS_CACHELINE_SIZE             32
#ifndef CONFIG_SYS_DCACHE_OFF
#  define CONFIG_CMD_CACHE
#endif

#ifndef CONFIG_SDKVERSION
#  define CONFIG_SDKVERSION               "0.1.0.1 - Hi3716cV200"
#endif

#define CONFIG_SYS_MALLOC_LEN      (0x600000)
#define CONFIG_SYS_GBL_DATA_SIZE   128  /* size in bytes reserved for initial data */

#include "hi3716mv410_config.h"

#if CFG_HI3716MV410_FPGA
#  define CONFIG_HI3716MV410_FPGA
#else
#  undef CONFIG_HI3716MV410_FPGA
#endif
/*-----------------------------------------------------------------------
 * for timer configuration (udelay)
*  enable timer
 -----------------------------------------------------------------------*/
#define CFG_TIMERBASE           REG_BASE_TIMER01
#define CFG_TIMER_CTRL          0xCA
#define READ_TIMER              \
	(*(volatile unsigned long *)(CFG_TIMERBASE + REG_TIMER_VALUE))
/*-----------------------------------------------------------------------
 * environment && bd_info  && global_data  configure
*     used in file
-----------------------------------------------------------------------*/

#ifndef CFG_ENV_SIZE
#  define CFG_ENV_SIZE                  0x2000
#endif

#ifndef CFG_ENV_ADDR
#  define CFG_ENV_ADDR                  0x80000
#endif

#ifndef CFG_ENV_RANGE
#  define CFG_ENV_RANGE                 CFG_ENV_SIZE
#endif

#ifdef CONFIG_ENV_BACKUP
#  define CONFIG_ENV_BACKUP_ADDR        CFG_ENV_BACKUP_ADDR
#endif

#define CONFIG_ENV_OFFSET               CFG_ENV_ADDR/* environment starts here  */
#define CONFIG_ENV_NAND_ADDR            CFG_ENV_ADDR
#define CONFIG_ENV_SPI_ADDR             CFG_ENV_ADDR
#define CONFIG_ENV_ADDR                 CFG_ENV_ADDR
#define CONFIG_ENV_RANGE                CFG_ENV_RANGE
#define CONFIG_CMD_SAVEENV
#define CONFIG_ENV_OVERWRITE
#define CONFIG_ENV_SIZE                 CFG_ENV_SIZE/*include ENV_HEADER_SIZE */
#define CONFIG_ENV_SECT_SIZE            CONFIG_ENV_SIZE
#define CONFIG_NR_DRAM_BANKS            1/* we have 1 bank of DRAM */
#define CFG_BOOT_PARAMS                 (MEM_BASE_DDR + 0x0100)
#define CONFIG_BOOT_PARAMS_MAX_SIZE     (0x10000)

/*-----------------------------------------------------------------------
 *  Environment   Configuration
 ------------------------------------------------------------------------*/
#define CONFIG_BOOTDELAY    1
#define CONFIG_BOOTARGS     \
	"mem=256M console=ttyAMA0,115200 console=ttyMTD,blackbox"
#define CONFIG_NETMASK      255.255.255.0 /* talk on MY local net */
#define CONFIG_IPADDR       192.168.1.10 /* static IP I currently own */
#define CONFIG_SERVERIP     192.168.1.1 /* current IP of tftp server ip */
#define CONFIG_ETHADDR      00:00:00:00:00:00
#define CONFIG_BOOTFILE     "uImage" /* file to load */
#define CONFIG_BAUDRATE     115200

#define CONFIG_BOOTARGS_MERGE
#define CONFIG_BOOTARGS_512M    "mem=512M mmz=ddr,0,0,256M"
#define CONFIG_BOOTARGS_1G      "mem=1G mmz=ddr,0,0,380M"
#define CONFIG_BOOTARGS_2G      "mem=2G mmz=ddr,0,0,600M"

#ifdef CONFIG_HI3716MV410_FPGA
#define CONFIG_EXTRA_ENV_SETTINGS       "phyintf=mii,rgmii\0" \
					"phymdio=0,1\0"       \
					"phyaddr=2,1\0"       \
					"phygpio=none,none\0" \
					"gmac_debug=0\0"
#endif
/*-----------------------------------------------------------------------
 * for bootm linux
 *
 -----------------------------------------------------------------------*/

#define CONFIG_BOOTM_LINUX 1    //for bootm
#define CONFIG_SYS_LOAD_ADDR (CFG_DDR_PHYS_OFFSET + 0x08000)   /* default load address 0x80008000*/
#define CONFIG_ZERO_BOOTDELAY_CHECK 1   /*use ^c to interrupt*/

/*-----------------------------------------------------------------------
 * for  commond configure
 -----------------------------------------------------------------------*/
//tftp comm
#define CONFIG_SYS_MAX_FLASH_BANKS    1 /* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT     256

//do_printenv  do_setenv common/cmd_nvedit.c
#define CONFIG_SYS_BAUDRATE_TABLE { 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_SYS_MAXARGS 16          /* max number of command args   */

#define CONFIG_SYS_CONSOLE_INFO_QUIET         1

/*-----------------------------------------------------------------------
 * Flash Memory Configuration v100
 *----------------------------------------------------------------------*/

#  ifdef CONFIG_SPIFLASH_SUPPORT
#    define CONFIG_HIFMC100_SPI_NOR_SUPPORT
#  endif
#  ifdef CONFIG_NAND_SUPPORT
#    define CONFIG_HIFMC100_NAND_SUPPORT
#  endif
#  ifdef CONFIG_SPI_NAND_SUPPORT
#    define CONFIG_HIFMC100_SPI_NAND_SUPPORT
#  endif

#ifdef CONFIG_HIFMC100_SPI_NOR_SUPPORT
#  define CONFIG_GENERIC_SF
#  define CONFIG_HIFMC100_SPI_NOR_CHIP_NUM           2
#endif

#if defined(CONFIG_HIFMC100_SPI_NAND_SUPPORT) || defined(CONFIG_HIFMC100_NAND_SUPPORT)
#  define CONFIG_GENERIC_NAND

#  undef CONFIG_HIFMC100_HARDWARE_PAGESIZE_ECC
#  undef CONFIG_HIFMC100_PAGESIZE_AUTO_ECC_NONE
#  define CONFIG_HIFMC100_AUTO_PAGESIZE_ECC

#ifdef CONFIG_HIFMC100_SPI_NAND_SUPPORT
  #define CONFIG_SYS_SPI_NAND_MAX_CHIPS	       1
#endif

#ifdef CONFIG_HIFMC100_NAND_SUPPORT
  #define CONFIG_SYS_NAND_MAX_CHIPS            1
#endif
#endif /* CONFIG_HIFMC_SPI_NAND_SUPPORT */

#if (defined CONFIG_HIFMC100_NAND_SUPPORT) || (defined CONFIG_HIFMC100_SPI_NAND_SUPPORT) || (defined CONFIG_HIFMC100_SPI_NOR_SUPPORT)
#define CONFIG_HIFMC100_SUPPORT
#endif

#ifdef CONFIG_HIFMC100_SUPPORT
#  define CONFIG_HIFMC100_REG_BASE_ADDRESS           REG_BASE_FMC
#  define CONFIG_HIFMC100_BUFFER_BASE_ADDRESS        MEM_BASE_FMC
#  define CONFIG_HIFMC100_BUFFER_SIZE                0x1000
#endif /* CONFIG_HIFMC100_SUPPORT */

#ifdef CONFIG_GENERIC_NAND
/* env in flash instead of CFG_ENV_IS_NOWHERE */
#  define CONFIG_ENV_IS_IN_NAND                1

#  define CONFIG_CMD_NAND
#  define CONFIG_SYS_NAND_BASE                 REG_BASE_FMC

#  define CONFIG_SYS_MAX_NAND_DEVICE           1
#  define NAND_RR_PARAM_OFFSET                 0x80000ULL
#undef CONFIG_NANDID_TAG
//#define CONFIG_NANDPTN_TAG                      1
//#define CONFIG_NANDPTN_TAG_VAL                  0x48694E70

#endif /* CONFIG_GENERIC_NAND */

#ifdef CONFIG_GENERIC_SF

/* env in flash instead of CFG_ENV_IS_NOWHERE */
#  define CONFIG_ENV_IS_IN_SPI_FLASH               1

#  define CONFIG_CMD_SF
#endif /* CONFIG_GENERIC_SF */

/*****************************************************************************
 * UBI/UBIFS Filesystem Configuration
******************************************************************************/

#if 0 /* Define ubi/ubifs supports */
/* UBI/UBIFS need much more malloc memory. */
#  warning adjust malloc macro CONFIG_SYS_MALLOC_LEN for ubi/ubifs.
#  undef CONFIG_SYS_MALLOC_LEN
#  define CONFIG_SYS_MALLOC_LEN      (CONFIG_ENV_SIZE + 128*1024 + (512 << 11))
#  define CONFIG_CMD_UBI              /* UBI Support      */
#  define CONFIG_CMD_UBIFS            /* UBIFS Support    */
#  define CONFIG_MTD_PARTITIONS
#  define CONFIG_MTD_DEVICE
#  define CONFIG_RBTREE
#  define CONFIG_LZO
#  define CONFIG_CMD_MTDPARTS
#endif
/*****************************************************************************/
#if 0 /* Define net-console supports */
#  define CONFIG_NETCONSOLE              1
#endif
/*****************************************************************************/
/*****************************************************************************/
#define CFG_DDR_PHYS_OFFSET             MEM_BASE_DDR
#define CFG_DDR_SIZE                    0x10000000

#define CONFIG_SYS_MEMTEST_START       \
	(CFG_DDR_PHYS_OFFSET + sizeof(unsigned long))
#define CONFIG_SYS_MEMTEST_END         (CFG_DDR_PHYS_OFFSET + CFG_DDR_SIZE)
#define CONFIG_SYS_MEMTEST_SCRATCH     CFG_DDR_PHYS_OFFSET

/*****************************************************************************/
/* Reserve memory config

High|		|
Addr|		|
	--------- <-- CONFIG_RESERVE_MEM_SIZE_MAX
	|   	|
	|Reserve|
	|  mem	|
	|   	|
	|   	|
	--------- <--
	|  		|
	|  Gap	| CONFIG_RESERVE_MEM_GAP
	|   	|
	--------- <--
	|   	|
	|U-boot |
Low	|   	|
Addr

*/
/* The gap between the free memory starting addr and the reserve mem bound addr */
#define CONFIG_RESERVE_MEM_GAP         128*1024*1024
//#define CONFIG_RESERVE_MEM_SIZE_MAX    512*1024*1024

/*****************************************************************************/

#define CONFIG_CMDLINE_TAG            1   /* enable passing of ATAGs  */
#define CONFIG_INITRD_TAG             1   /* support initrd */
#define CONFIG_SETUP_MEMORY_TAGS      1
#define CONFIG_MISC_INIT_R            1   /* call misc_init_r during start up */

#define CONFIG_SDKVERSION_TAG         1
#ifdef  CONFIG_SDKVERSION_TAG
#  define CONFIG_SDKVERSION_TAG_VAL   0x726d6d75
#endif

#undef CONFIG_BOOTREG_TAG
#ifdef  CONFIG_BOOTREG_TAG
#  define CONFIG_BOOTREG_TAG_VAL   0x53000001
#endif

#define CONFIG_ETHADDR_TAG            1
#ifdef  CONFIG_ETHADDR_TAG
#define CONFIG_ETHADDR_TAG_VAL        0x726d6d73
#define CONFIG_PHYADDR_TAG_VAL        (CONFIG_ETHADDR_TAG_VAL + 1)
#define CONFIG_PHYINTF_TAG_VAL        0x726d6d80
#define CONFIG_PHYGPIO_TAG_VAL        (CONFIG_PHYINTF_TAG_VAL + 1)
#endif

#define HISFV_DEFAULT_PHY_U                 1
#define HISFV_DEFAULT_PHY_D                 3

#define CONFIG_SYS_NO_FLASH
#define CONFIG_PL011_SERIAL           1

#ifdef CONFIG_HI3716MV410_FPGA
#  define CONFIG_PL011_CLOCK            54000000
#  define CONFIG_CONS_INDEX             0
#  define CONFIG_CUR_UART_BASE          REG_BASE_UART2
#else
#  define CONFIG_PL011_CLOCK            83300000
#  define CONFIG_CONS_INDEX             0
#  define CONFIG_CUR_UART_BASE          REG_BASE_UART0
#endif
#ifndef CONFIG_PL011_CLOCK
#  define CONFIG_PL011_CLOCK            83300000
#  define CONFIG_CONS_INDEX             0
#  define CONFIG_CUR_UART_BASE          REG_BASE_UART0
#endif

#ifdef CONFIG_HI3716MV410_FPGA
#  define CONFIG_PL01x_PORTS            \
	{(void *)REG_BASE_UART2, (void *)REG_BASE_UART1}
#else
#  define CONFIG_PL01x_PORTS            \
	{(void *)REG_BASE_UART0, (void *)REG_BASE_UART1}
#endif

#define CONFIG_PRODUCTNAME            "hi3716mv410"

/*****************************************************************************/
/* DDR training Configuration */
/******************************************************************************/
//#define CONFIG_DDR_TRAINING
#define CONFIG_DDR_TRAINING_V2

/*****************************************************************************/
/* eMMC Flash Configuration */
/******************************************************************************/
#ifdef CONFIG_EMMC_SUPPORT
#  define CONFIG_HIMCI_V200                   1
#endif

#ifdef CONFIG_HIMCI_V200
#  define CONFIG_MMC_BOOT_ADDR                0
#  define CONFIG_MMC_POWER_OFF_TIMEOUT        50
#  define CONFIG_MMC_POWER_ON_TIMEROUT        50
#  define CONFIG_MMC_RESET_LOW_TIMEOUT        10
#  define CONFIG_MMC_RESET_HIGH_TIMEROUT      300
#  define CONFIG_GENERIC_MMC
#endif /* CONFIG_HIMCI_V200 */

#ifdef CONFIG_GENERIC_MMC
/* env in flash instead of CFG_ENV_IS_NOWHERE */
#  define CONFIG_ENV_IS_IN_EMMC               1
#  define CONFIG_CMD_MMC
#  define CONFIG_EXT4
#  define CONFIG_EXT4_SPARSE
#endif /* CONFIG_GENERIC_MMC */

/******************************************************************************/
/*  USB Flash Configuration */
/******************************************************************************/
#define CONFIG_USB_BOOTSTRAP

#  ifdef CONFIG_USB_DEVICE
#    define CONFIG_USB_DEVICE_DMA
#    define CONFIG_USBDEV_REV_2_93a               0x4F54293A
#    define CONFIG_USBDEV_REV_2_94a               0x4F54294A
#    define CONFIG_USBDEV_REV_3_00a               0x4F54300A
#    undef CONFIG_USB_DEVICE_DBG
#  endif

#ifdef CONFIG_USB_SUPPORT
#  define CONFIG_CMD_USB
#endif

#ifdef CONFIG_CMD_USB
/*
 * ehci and ohci only choose one
 * only ohci can support keyboard
 */
//#  define CONFIG_USB_OHCI_NEW
#  define CONFIG_USB_EHCI
#  define CONFIG_USB_HOST_BOOTSTRAP
#  define CONFIG_FILE_BOOTARGS_NAME         "bootargs.bin"
#  define CONFIG_FILE_RECOVERY_NAME         "recovery.img"
#  define CONFIG_FILE_READ_ADDR             0x1000000
#  define CONFIG_FILE_MAX_SIZE              0x1000000

#  define CONFIG_SYS_USB_OHCI_SLOT_NAME     "hiusb"
#  define CONFIG_SYS_USB_OHCI_MAX_ROOT_PORTS    3
#  define CONFIG_SYS_USB_OHCI_CPU_INIT
#  define CONFIG_USB_KEYBOARD
#  define CONFIG_USB_STORAGE
#  define CONFIG_SYS_USB_EVENT_POLL
#  define CONFIG_SYS_USB_EHCI_MAX_ROOT_PORTS    3

/*-----------------------------------------------------------------------
* Fat File System Configuration
 -----------------------------------------------------------------------*/
#  ifdef CONFIG_USB_STORAGE
#    define CONFIG_CMD_FAT
#  endif

#  ifdef  CONFIG_CMD_FAT
#    define CONFIG_USB_VFAT_INF
#    define CONFIG_SUPPORT_VFAT
#    define CONFIG_DOS_PARTITION
#    define CONFIG_SYS_DEVICE_DEREGISTER
#    define LITTLEENDIAN
#  endif

#endif


#define CONFIG_MEM_BASE_FREE_START  0X1000000
/******************************************************************************
 * The follow ONLY used in not CA mode.
******************************************************************************/
#if !(defined(CONFIG_SUPPORT_CA_DEBUG) || defined(CONFIG_SUPPORT_CA_RELEASE))

/******************************************************************************/
/*  lib  Uncompress/compress Configuration */
/******************************************************************************/
#define CONFIG_GZIP     1
#define CONFIG_ZLIB     1
#ifdef CONFIG_GZIP
#  define CONFIG_CMD_UNZIP
#endif

#define CONFIG_HIBERNATE
#ifdef CONFIG_HIBERNATE
#define CONFIG_HIBERNATE_HIBDRV_SIZE     0x300000
#define CONFIG_HIBERNATE_USERAPI_SIZE    0x200000
#endif
#undef CONFIG_SHOW_MEMORY_LAYOUT
#define CONFIG_SHOW_REG_INFO
#define CONFIG_SHOW_RESERVE_MEM_LAYOUT

#define CONFIG_BOOTHEAD_GAP           0

/*-----------------------------------------------------------------------
 * console display  Configuration
 ------------------------------------------------------------------------*/

#define CONFIG_VERSION_VARIABLE      1 /*used in common/main.c*/
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_PROMPT            "fastboot# " /* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE            1024  /* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE            \
	(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)

#define CFG_LONGHELP
#define CFG_BARGSIZE            CFG_CBSIZE /* Boot Argument Buffer Size */
#undef  CFG_CLKS_IN_HZ                  /* everything, incl board info, in Hz */
#define CFG_LOAD_ADDR           \
	(CFG_DDR_PHYS_OFFSET + 0x08000)     /* default load address */
#define CONFIG_AUTO_COMPLETE    1
#define CFG_CMDLINE_HISTORYS    8
#define CONFIG_CMDLINE_EDITING

#if 1 /* Enable Ctrl+C to stop autoboot.*/
#  define CONFIG_AUTOBOOT_KEYED      1
#  define CONFIG_AUTOBOOT_PROMPT     "Press Ctrl+C to stop autoboot\n"
#  define CONFIG_AUTOBOOT_DELAY_STR  "hisilicon #"
#  define CONFIG_AUTOBOOT_STOP_STR   "\x03"
#endif

// cp.b
#define CONFIG_CMD_MEMORY  /*md mw cp etc.*/
#define CONFIG_CMD_LOADB  /* loadb   common/cmd_load.c*/

/*-----------------------------------------------------------------------
 * SATA  Configuration
 -----------------------------------------------------------------------*/
#ifdef CONFIG_SATA_SUPPORT
#  define CONFIG_SATA_HI3716MV410
#  define CONFIG_CMD_SATA
#  define CONFIG_HISATA
#  define CONFIG_LBA48
#  define CONFIG_LIBATA
#  define CONFIG_SYS_SATA_MAX_DEVICE          1
#  define CFG_HZ                              93750
#endif
/*-----------------------------------------------------------------------
 * HIETH driver
 -----------------------------------------------------------------------*/
#ifdef CONFIG_NET_SUPPORT
#  define CONFIG_NET_HISFV300                   1
#endif
/* default is hieth-switch-fabric */
#ifdef CONFIG_NET_HISFV300
#  define CONFIG_NET_MULTI                    1
#  define CONFIG_NET_HISFV300_HI3716MV410     1
#  define HISFV_MII_MODE                      0
#  define HISFV_RMII_MODE                     1
#  define HIETH_MII_RMII_MODE_U               HISFV_MII_MODE /* XXX only for hi3719 FPGA. */
#  define HIETH_MII_RMII_MODE_D               HISFV_RMII_MODE /* XXX only for hi3719 FPGA. */
#endif /* CONFIG_NET_HISFV300 */

/*-----------------------------------------------------------------------
 * STMMAC driver
 -----------------------------------------------------------------------*/
#undef CONFIG_NET_STMMAC
#ifdef CONFIG_NET_STMMAC
#  define STMMAC_IOADDR             (0x60140000)
#  define STMMAC_IOSIZE             (0x10000)
#  define STMMAC_FRQDIV             (0)
#  define STMMAC_PHYADDR            (3)
#  define STMMAC_PHYNAME            "0:03"
#  define CONFIG_PHY_GIGE
#endif /* CONFIG_NET_STMMAC */

/*-----------------------------------------------------------------------
 * network config
 -----------------------------------------------------------------------*/
#ifdef CONFIG_NET_SUPPORT
#  define CONFIG_ARP_TIMEOUT                50000UL
#  define CONFIG_NET_RETRY_COUNT            50
#  define CONFIG_CMD_NET
#  define CONFIG_CMD_PING
#  define CONFIG_CMD_MII
#  define CONFIG_SYS_FAULT_ECHO_LINK_DOWN    1
#endif
/******************************************************************************/

/******************************************************************************/
#else /* !(defined(CONFIG_SUPPORT_CA_DEBUG) || defined(CONFIG_SUPPORT_CA_RELEASE)) */
/* The follow ONLY define in CA mode */
/******************************************************************************/

//#undef  CONFIG_DDR_TRAINING

/******************************************************************************/
/*  lib  Uncompress/compress Configuration */
/******************************************************************************/
#if defined(CONFIG_SUPPORT_CA_DEBUG)
#define CONFIG_GZIP     1
#define CONFIG_ZLIB     1
#ifdef CONFIG_GZIP
#  define CONFIG_CMD_UNZIP
#endif
#endif

#define CONFIG_SYS_PROMPT            "fastboot# " /* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE            1024         /* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE            \
(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)

#ifdef CONFIG_SUPPORT_CA_DEBUG     /*----------------------------CONFIG_SUPPORT_CA_DEBUG------------------------------*/
#define CONFIG_CMD_MEMORY  /*md mw cp etc.*/
//#define CONFIG_CMD_LOADB  /* loadb   common/cmd_load.c*/
#define CFG_LOAD_ADDR           \
(CFG_DDR_PHYS_OFFSET + 0x08000)     /* default load address */
/*-----------------------------------------------------------------------
* HIETH driver
-----------------------------------------------------------------------*/
#ifndef CONFIG_NET_SUPPORT
#define CONFIG_NET_SUPPORT
#endif /* CONFIG_NET_SUPPORT */

#define CONFIG_NET_MULTI                    1
#define CONFIG_NET_HISFV300                   1
#define CONFIG_NET_HISFV300_HI3716MV410     1
#define HISFV_MII_MODE                      0
#define HISFV_RMII_MODE                     1
#define HIETH_MII_RMII_MODE_U               HISFV_MII_MODE /* XXX only for hi3719 FPGA. */
#define HIETH_MII_RMII_MODE_D               HISFV_RMII_MODE /* XXX only for hi3719 FPGA. */


/*-----------------------------------------------------------------------
* network config
-----------------------------------------------------------------------*/
#define CONFIG_ARP_TIMEOUT                50000UL
#define CONFIG_NET_RETRY_COUNT            50
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_MII
#define CONFIG_SYS_FAULT_ECHO_LINK_DOWN    1


#endif  /*----------------------------#ifdef CONFIG_SUPPORT_CA_DEBUG------------------------------*/

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define CONFIG_SERIAL_NO_DISPLAY
#endif

#if defined(CONFIG_SUPPORT_CA_NAGRA)
#define CONFIG_GZIP     1
#define CONFIG_ZLIB     1
#endif

#define CONFIG_BOOTHEAD_GAP          ((TEXT_BASE & 0x000FFFFF) + 0x1000)

#endif /* !(defined(CONFIG_SUPPORT_CA_DEBUG) || defined(CONFIG_SUPPORT_CA_RELEASE)) */

#ifdef CONFIG_DDR_TRAINING
#  undef CONFIG_DDR_TRAINING_STARTUP
#  define CONFIG_DDR_DATAEYE_TRAINING_STARTUP
#  define CONFIG_DDR_TRAINING_HI3716MV410
#endif /* CONFIG_DDR_TRAINING */

#define CONFIG_BOOTROM_SUPPORT

#if (defined(CONFIG_BOOTROM_SUPPORT)) \
	&& (!defined(REG_START_FLAG) || !defined(CONFIG_START_MAGIC))
#  error Please define CONFIG_START_MAGIC and CONFIG_START_MAGIC first
#endif

#endif /* __CONFIG_H */
