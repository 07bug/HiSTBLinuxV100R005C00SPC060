/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : gfx2d_fence.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                  Modification
2018/01/01            sdk                    Created file
************************************************************************************************/
#ifndef _GFX2D_FENCE_H_
#define _GFX2D_FENCE_H_

/*********************************add include here*********************************************/

#include "hi_type.h"

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
#ifdef GFX2D_FENCE_SUPPORT
HI_S32 GFX2D_FENCE_Open(HI_VOID);
HI_VOID GFX2D_FENCE_Close(HI_VOID);
HI_S32 GFX2D_FENCE_Create(const HI_CHAR *name);
HI_VOID GFX2D_FENCE_Destroy(HI_S32 fd);
HI_S32 GFX2D_FENCE_Wait(HI_S32 fd);
HI_S32 GFX2D_FENCE_WakeUp(HI_VOID);
HI_VOID GFX2D_FENCE_ReadProc(struct seq_file *p, HI_VOID *v);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /**_GFX2D_FENCE_H_**/
