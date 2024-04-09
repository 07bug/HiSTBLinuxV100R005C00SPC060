/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name        : gfx2d_hal_hwc_adp.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :


History          :
Date                  Author                Modification
2018/01/01            sdk                   Created file
**************************************************************************************************/

/*********************************add include here************************************************/
#include "gfx2d_hal_hwc_adp.h"
#include "hi_gfx_sys_k.h"

/***************************** Macro Definition **************************************************/

/*************************** Structure Definition ************************************************/


/********************** Global Variable declaration **********************************************/
static HWC_CAPABILITY_S gs_stCapability =
{
    HWC_MAX_LAYERS,
    6,
    1,
    {0x00c043d0, 0xfe7efc},
    {0x0c040c0, 0x200},
    1,
    0xffff,
    16,
    1,
#if HWC_VERSION == 0x400   /* hi3798cv200 */
    4096,
#elif HWC_VERSION == 0x300 /*hi3798cv100 hi3796cv100*/
    3840,
#else
    2560,
#endif
    1,
#if HWC_VERSION == 0x400
    2160,
#elif HWC_VERSION == 0x300
    2160,
#else
    1600,
#endif
    32,
    32,
    16,
    16,
    2,
    {0x400000, 0x0},
#if HWC_VERSION == 0x400
    HI_TRUE,
    HI_TRUE,
    2,
    1,
#else
    HI_FALSE,
    HI_FALSE,
    1,
    2,
#endif
};


/******************************* API forward declarations ****************************************/

/******************************* API realization *************************************************/
HI_VOID HWC_ADP_GetCapability(HWC_CAPABILITY_S *pstCapability)
{
    if (NULL != pstCapability)
    {
       HI_GFX_Memcpy(pstCapability, &gs_stCapability, sizeof(HWC_CAPABILITY_S));
    }

    return;
}
