/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : gfx2d_config.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                  Modification
2018/01/01            sdk                    Created file
************************************************************************************************/

#ifndef _GFX2D_CONFIG_H_
#define _GFX2D_CONFIG_H_

/*********************************add include here*********************************************/
#include <linux/fs.h>
#include "hi_type.h"

/**********************************************************************************************/


/**********************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/***************************** Macro Definition ***********************************************/
#ifdef CONFIG_GFX_PROC_UNSUPPORT
#define GFX2D_PROC_UNSUPPORT
#endif

typedef HI_VOID (*GFX2D_FUNC_CB)(HI_VOID *param);


/*************************** Structure Definition *********************************************/


/***************************  The enum of Jpeg image format  **********************************/

/********************** Global Variable declaration *******************************************/


/******************************* API declaration **********************************************/
HI_S32 GFX2D_CONFIG_SetMemSize(HI_U32 u32MemSize);

HI_U32 GFX2D_CONFIG_GetMemSize(HI_VOID);

HI_U32 GFX2D_CONFIG_GetNodeNum(HI_VOID);

#ifndef GFX2D_PROC_UNSUPPORT
HI_VOID GFX2D_CONFIG_StartTime(HI_VOID);

HI_U32 GFX2D_CONFIG_EndTime(HI_VOID);

HI_S32 GFX2D_CONFIG_WriteProc(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif/*_GFX2D_CONFIG_H_ */
