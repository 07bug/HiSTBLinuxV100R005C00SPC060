/**
 * ddr_training_internal_config.h
 *
 * Copyright (c) 2009-2014, HiSilicon Technologies Co., Ltd.
 * All rights reserved.
 */

/****** include ddrc,phy,dmc define files *******************/
#if defined(DDR_DDRC_V500_CONFIG)
#include "ddr_ddrc_v500.h"
#elif defined(DDR_DDRC_V510_CONFIG)
#include "ddr_ddrc_v510.h"
#else
# error Unknown DDRC Type
#endif

#if defined(DDR_PHY_S40_CONFIG)
#include "ddr_phy_s40.h"
#elif defined(DDR_PHY_T28_CONFIG)
#include "ddr_phy_t28.h"
#else
# error Unknown DDR PHY Type
#endif

#if defined(DDR_DDRT_S40_CONFIG)
#include "ddr_ddrt_s40.h"
#elif defined(DDR_DDRT_T28_CONFIG)
#include "ddr_ddrt_t28.h"
#else
# error Unknown DDR PHY Type
#endif


/****** training item define *******************/
/* enable all config by default */
#define DDR_WL_TRAINING_CONFIG
#define DDR_GATE_TRAINING_CONFIG
#define DDR_DATAEYE_TRAINING_CONFIG
#define DDR_HW_TRAINING_CONFIG
#define DDR_TRAINING_ADJUST_CONFIG
#define DDR_TRAINING_LOG_CONFIG
#define DDR_TRAINING_UART_CONFIG
#define DDR_TRAINING_STAT_CONFIG

/* defined in ddr_training_custom.h to disable this item */
#ifdef DDR_VREF_TRAINING_DISABLE
#undef DDR_VREF_TRAINING_CONFIG
#endif

#ifdef DDR_WL_TRAINING_DISABLE
#undef DDR_WL_TRAINING_CONFIG
#endif

#ifdef DDR_GATE_TRAINING_DISABLE
#undef DDR_GATE_TRAINING_CONFIG
#endif

#ifdef DDR_DATAEYE_TRAINING_DISABLE
#undef DDR_DATAEYE_TRAINING_CONFIG
#endif

#ifdef DDR_HW_TRAINING_DISABLE
#undef DDR_HW_TRAINING_CONFIG
#endif

#ifdef DDR_MPR_TRAINING_DISABLE
#undef DDR_MPR_TRAINING_CONFIG
#endif

#ifdef DDR_TRAINING_ADJUST_DISABLE
#undef DDR_TRAINING_ADJUST_CONFIG
#endif

#ifdef DDR_TRAINING_LOG_DISABLE
#undef DDR_TRAINING_LOG_CONFIG
#endif

#ifdef DDR_TRAINING_UART_DISABLE
#undef DDR_TRAINING_UART_CONFIG
#endif

#ifdef DDR_TRAINING_STAT_DISABLE
#undef DDR_TRAINING_STAT_CONFIG
#endif

/* for training cmd */
#ifdef DDR_TRAINING_CMD
	/* defined in ddr_training_custom.h to disable this item */
    #ifdef DDR_VREF_TRAINING_CMD_DISABLE
    #undef DDR_VREF_TRAINING_CONFIG
    #endif

    #ifdef DDR_WL_TRAINING_CMD_DISABLE
    #undef DDR_WL_TRAINING_CONFIG
    #endif

    #ifdef DDR_GATE_TRAINING_CMD_DISABLE
    #undef DDR_GATE_TRAINING_CONFIG
    #endif

	#ifdef DDR_DATAEYE_TRAINING_CMD_DISABLE
    #undef DDR_DATAEYE_TRAINING_CONFIG
    #endif

	#ifdef DDR_HW_TRAINING_CMD_DISABLE
    #undef DDR_HW_TRAINING_CONFIG
    #endif

	#ifdef DDR_MPR_TRAINING_CMD_DISABLE
    #undef DDR_MPR_TRAINING_CONFIG
    #endif

    #ifdef DDR_TRAINING_ADJUST_CMD_DISABLE
    #undef DDR_TRAINING_ADJUST_CONFIG
    #endif

	#ifdef DDR_TRAINING_LOG_CMD_DISABLE
    #undef DDR_TRAINING_LOG_CONFIG
    #endif
#endif /* DDR_TRAINING_CMD */

/* check config */
#if defined(DDR_TRAINING_ADJUST_DISABLE) && defined(DDR_HW_TRAINING_CONFIG) \
	&& !defined(DDR_HW_READ_ADJ_CONFIG)
#error when defined DDR_TRAINING_ADJUST_DISABLE, \
	MUST define DDR_HW_READ_ADJ_CONFIG.
#endif

#if (defined(DDR_HW_TRAINING_CONFIG) || defined(DDR_MPR_TRAINING_CONFIG) \
	|| defined(DDR_VREF_TRAINING_CONFIG) \
	|| defined(DDR_TRAINING_ADJUST_CONFIG)) \
	&& !defined(DDR_DATAEYE_TRAINING_CONFIG)
#error when enable HW/GATE/VREF training or dataeye adjust, \
	MUST define DDR_DATAEYE_TRAINING_CONFIG.
#endif

/* reserve config */
/* DDR_WL_DATAEYE_ADJUST_CONFIG: Adjust WDQ phase/bdl after WL training. */
/* DDR_VREF_TRAINING_CONFIG    : DDR Vref training. */
/* DDR_MPR_TRAINING_CONFIG     : DDR MPR training. */
/* DDR_AC_TRAINING_CONFIG      : DDR AC training. */
/* DDR_DDRT_SPECIAL_CONFIG     : DDRT read and write special operate. */
/* DDR_DDR4_CONFIG             : DDR4 special operate. */
/* DDR_TRAINING_CUT_CODE_CONFIG: Cut code for small SRAM. */
/* DDR_TRAINING_MINI_LOG_CONFIG: Less code to log */
/* DDR_HW_READ_ADJ_CONFIG      : Adjust read dataeye after hw read training */
/* DDR_VREF_WITHOUT_BDL_CONFIG : Vref not modify DQ bdl */
/* DDR_DATAEYE_NORMAL_NOT_ADJ_CONFIG : Do not adjust window on normal case */
