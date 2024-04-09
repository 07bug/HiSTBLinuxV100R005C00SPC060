/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : gfx2d_hal_hwc.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                  Modification
2018/01/01            sdk                    Created file
************************************************************************************************/

#ifndef _GFX2D_HAL_HWC_H_
#define _GFX2D_HAL_HWC_H_

/*********************************add include here*********************************************/

#include "hi_gfx2d_type.h"
#include "gfx2d_config.h"

/**********************************************************************************************/


/**********************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/***************************** Macro Definition ***********************************************/

/*************************** Structure Definition *********************************************/


/***************************  The enum of Jpeg image format  **********************************/


/********************** Global Variable declaration *******************************************/


/******************************* API declaration **********************************************/

HI_S32 GFX2D_HAL_HWC_Init(HI_VOID);

HI_VOID GFX2D_HAL_HWC_Deinit(HI_VOID);

HI_S32 GFX2D_HAL_HWC_Open(HI_VOID);

HI_VOID GFX2D_HAL_HWC_Close(HI_VOID);

HI_S32 GFX2D_HAL_HWC_Compose(const HI_GFX2D_DEV_ID_E enDevId,
                             const HI_GFX2D_COMPOSE_LIST_S *pstComposeList,
                             const HI_GFX2D_SURFACE_S *pstDstSurface,
                             HI_VOID **ppNode, GFX2D_HAL_DEV_TYPE_E *penNodeType);

#ifndef GFX2D_PROC_UNSUPPORT
HI_S32 GFX2D_HAL_HWC_ReadProc(struct seq_file *p, HI_VOID *v);

HI_S32 GFX2D_HAL_HWC_WriteProc(struct seq_file *p, HI_VOID *v);
#endif

HI_VOID GFX2D_HAL_HWC_GetNodeOps(GFX2D_HAL_NODE_OPS_S **ppstNodeOps);

HI_U32 GFX2D_HAL_HWC_GetIntStatus(HI_VOID);

HI_U32 GFX2D_HAL_HWC_GetIsrNum(HI_VOID);

HI_U32 GFX2D_HAL_HWC_GetBaseAddr(HI_VOID);

#ifdef GFX2D_ALPHADETECT_SUPPORT
HI_VOID GFX2D_HAL_HWC_GetTransparent(HI_GFX2D_EXTINFO_S *ExtInfo);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif  /*_GFX2D_HAL_HWC_H_*/
