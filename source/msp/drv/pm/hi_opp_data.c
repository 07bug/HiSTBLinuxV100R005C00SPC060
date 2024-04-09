/*
 * HI OPP table definitions.
 *
 * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
 */
#include <linux/module.h>
#include "hi_opp_data.h"
#include "hi_drv_pmoc.h"
#include "hi_reg_common.h"
#include "hipm.h"
#include "opp.h"
#include "hi_drv_sys.h"

/*
 * Structures containing HI voltage supported and various
 * voltage dependent data for each VDD.
 */
static struct hi_opp_def __initdata hi_opp_def_list[] = {

#if   (!defined(CHIP_TYPE_hi3798mv100)) \
   && (!defined(CHIP_TYPE_hi3796mv100))
    OPP_INITIALIZER(true,  400000, HI_VDD_MPU_OPP1_UV),
#endif
    OPP_INITIALIZER(true,  600000, HI_VDD_MPU_OPP2_UV),
#if    defined(CHIP_TYPE_hi3716mv410)    \
    || defined(CHIP_TYPE_hi3716mv420)    \
    || defined(CHIP_TYPE_hi3798cv200)    \
    || defined(CHIP_TYPE_hi3798mv200)    \
    || defined(CHIP_TYPE_hi3798mv300)    \
    || defined(CHIP_TYPE_hi3798mv310)    \
    || defined(CHIP_TYPE_hi3796mv200)    \
    || defined(CHIP_TYPE_hi3716mv450)
    OPP_INITIALIZER(true,  800000, HI_VDD_MPU_OPP3_UV),
#endif
#if    (!defined(CHIP_TYPE_hi3798cv200))  \
    && (!defined(CHIP_TYPE_hi3798mv200))  \
    && (!defined(CHIP_TYPE_hi3798mv300))  \
    && (!defined(CHIP_TYPE_hi3798mv310))  \
    && (!defined(CHIP_TYPE_hi3796mv200))  \
    && (!defined(CHIP_TYPE_hi3716mv450))
    OPP_INITIALIZER(true, 1000000, HI_VDD_MPU_OPP4_UV),
#endif
#if !defined(CHIP_TYPE_hi3716mv410)
    OPP_INITIALIZER(true, 1200000, HI_VDD_MPU_OPP5_UV),
#endif
#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    OPP_INITIALIZER(true, 1450000, HI_VDD_MPU_OPP6_UV),
#endif
#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3796mv200)   \
    || defined(CHIP_TYPE_hi3716mv450)
    OPP_INITIALIZER(true, 1500000, HI_VDD_MPU_OPP6_UV),
#endif
#if    defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)   \
    || defined(CHIP_TYPE_hi3798mv310)   \
    || defined(CHIP_TYPE_hi3796mv200)   \
    || defined(CHIP_TYPE_hi3716mv450)
    OPP_INITIALIZER(true, 1600000, HI_VDD_MPU_OPP7_UV),
#endif
#ifdef ANDROID
#if    defined(CHIP_TYPE_hi3798mv300)   \
    || defined(CHIP_TYPE_hi3798mv310)
    OPP_INITIALIZER(true, 2000000, HI_VDD_MPU_OPP7_UV),
#endif
#endif
};

/**
 * hi_opp_init() - initialize hi opp table
 */
int __init hi_opp_init(void)
{
    int r = -ENODEV;
#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    HI_CHIP_PACKAGE_TYPE_E packageType = HI_CHIP_PACKAGE_TYPE_BUTT;
    int ret = 0;
#endif

    HI_INFO_PM("enter %s\n", __FUNCTION__);

    r = hi_init_opp_table(hi_opp_def_list, ARRAY_SIZE(hi_opp_def_list));

#if defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    ret = HI_DRV_SYS_GetChipPackageType(&packageType);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_PM("get chip package type failed\n");
    }

    if (HI_CHIP_PACKAGE_TYPE_BGA_15_15 == packageType)
    {
        /* 15*15 package disable 1.45G*/
        opp_disable(&mpu_dev, 1450000);
    }
#endif

    return r;
}

#if 0
#ifndef MODULE
device_initcall(hi_opp_init);
#endif
#endif
