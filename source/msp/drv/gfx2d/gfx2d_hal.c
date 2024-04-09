/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name        : gfx2d_hal.c
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
#include <linux/fs.h>

#include "hi_gfx2d_type.h"
#include "gfx2d_hal.h"
#include "gfx2d_hal_hwc.h"

/***************************** Macro Definition **************************************************/

/*************************** Structure Definition ************************************************/


/********************** Global Variable declaration **********************************************/

/******************************* API forward declarations ****************************************/

/******************************* API realization *************************************************/
HI_S32 GFX2D_HAL_Init(HI_VOID)
{
    return GFX2D_HAL_HWC_Init();
}

HI_VOID GFX2D_HAL_Deinit(HI_VOID)
{
    GFX2D_HAL_HWC_Deinit();
}

HI_S32 GFX2D_HAL_Open(HI_VOID)
{
    return GFX2D_HAL_HWC_Open();
}

HI_VOID GFX2D_HAL_Close(HI_VOID)
{
    GFX2D_HAL_HWC_Close();
}

HI_S32 GFX2D_HAL_Compose(const HI_GFX2D_DEV_ID_E enDevId,
                         const HI_GFX2D_COMPOSE_LIST_S *pstComposeList,
                         const HI_GFX2D_SURFACE_S *pstDstSurface,
                         HI_VOID **ppNode,
                         GFX2D_HAL_DEV_TYPE_E *penNodeType)
{
    return GFX2D_HAL_HWC_Compose(enDevId, pstComposeList, pstDstSurface, ppNode, penNodeType);
}

HI_VOID GFX2D_HAL_GetNodeOps(const GFX2D_HAL_DEV_TYPE_E enDevType,
                             GFX2D_HAL_NODE_OPS_S **ppstNodeOps)
{
    if (enDevType == GFX2D_HAL_DEV_TYPE_HWC)
    {
        GFX2D_HAL_HWC_GetNodeOps(ppstNodeOps);
    }

    return;
}

HI_S32 GFX2D_HAL_GetIntStatus(const GFX2D_HAL_DEV_TYPE_E enDevType)
{
    return GFX2D_HAL_HWC_GetIntStatus();
}

HI_U32 GFX2D_HAL_GetIsrNum(const HI_GFX2D_DEV_ID_E enDevId, const GFX2D_HAL_DEV_TYPE_E enDevType)
{
    return GFX2D_HAL_HWC_GetIsrNum();
}

HI_U32 GFX2D_HAL_GetBaseAddr(const HI_GFX2D_DEV_ID_E enDevId, const GFX2D_HAL_DEV_TYPE_E enDevType)
{
    return GFX2D_HAL_HWC_GetBaseAddr();
}

#ifdef GFX2D_ALPHADETECT_SUPPORT
HI_VOID GFX2D_HAL_GetTransparent(HI_GFX2D_EXTINFO_S *ExtInfo)
{
    return GFX2D_HAL_HWC_GetTransparent(ExtInfo);
}
#endif

#ifndef GFX2D_PROC_UNSUPPORT
HI_VOID GFX2D_HAL_ReadProc(struct seq_file *p, HI_VOID *v)
{
    GFX2D_HAL_HWC_ReadProc(p, v);
    return;
}

HI_VOID GFX2D_HAL_WriteProc(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    HI_UNUSED(file);
    HI_UNUSED(buf);
    HI_UNUSED(count);
    HI_UNUSED(ppos);
    return;
}
#endif
