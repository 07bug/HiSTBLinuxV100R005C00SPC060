#ifndef __VFMW_SYSCONFIG_HEADER__
#define __VFMW_SYSCONFIG_HEADER__

#define MAX_VDH_NUM                 (1)
#define MAX_SCD_NUM                 (MAX_VDH_NUM)
#define MAX_DSP_NUM                 (MAX_VDH_NUM)

#define  MAX_CHIP_SUPPORT_WIDTH     (4096)
#define  MAX_CHIP_SUPPORT_HEIGHT    (2304)

#define  CHIP_SUPPORT_HD_WIDTH     (1920)
#define  CHIP_SUPPORT_HD_HEIGHT    (1088)

#define LOWDLY_DSP_ID               (0)
#define AVS_DSP_ID                  (1)

#define VDM_REG_PHY_ADDR       0xf8c30000
#define SCD_REG_PHY_ADDR       0xf8c3c000
#define BPD_REG_PHY_ADDR       0xf8c3d000

#define SYSTEM_REG_PHY_ADDR    0xf8a22000

#define SYSTEM_REG_RANGE       (1024 * 1024)

#ifdef ENV_SOS_KERNEL
#define VDM_INT_NUM            (105 + 32)
#define SCD_INT_NUM            (106 + 32)
#define MMU_VDH_NUM            (148 + 32)

#define VDH_IRQ_NAME_INDEX     (1)
#define SCD_IRQ_NAME_INDEX     (5)
#define MMU_IRQ_NAME_INDEX     (14)
#else
#define VDM_INT_NUM            (95 + 32)
#define SCD_INT_NUM            (104 + 32)
#define MMU_VDH_NUM            (149 + 32)

#define VDH_IRQ_NAME_INDEX     (0)
#define SCD_IRQ_NAME_INDEX     (4)
#define MMU_IRQ_NAME_INDEX     (13)
#endif

#ifdef ENV_SOS_KERNEL
#define BOARD_MEM_BASE_ADDR    (0x3B000000)
#define BOARD_MEM_TOTAL_SIZE   (72 * 1024 * 1024)
#else
#define BOARD_MEM_BASE_ADDR         (0x08000000)
#define BOARD_MEM_TOTAL_SIZE        (72 * 1024 * 1024)
#endif
#endif
