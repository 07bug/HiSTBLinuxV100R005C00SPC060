/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : gfx2d_mem.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                  Modification
2018/01/01            sdk                    Created file
************************************************************************************************/
#ifndef _GFX2D_MEM_H_
#define _GFX2D_MEM_H_

/*********************************add include here*********************************************/

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

HI_S32 GFX2D_MEM_Init(const HI_U32 u32Size);

HI_VOID GFX2D_MEM_Deinit(HI_VOID);

HI_S32 GFX2D_MEM_Open(HI_VOID);

HI_VOID GFX2D_MEM_Close(HI_VOID);

HI_S32 GFX2D_MEM_Register(const HI_U32 u32BlockSize, const HI_U32 u32BlockNum);

HI_VOID GFX2D_Mem_UnRegister(const HI_U32 u32BlockSize);

HI_VOID *GFX2D_MEM_Alloc(const HI_U32 u32Size);

HI_S32 GFX2D_MEM_Free(HI_VOID *pBuf);

HI_U32 GFX2D_MEM_GetPhyaddr(HI_VOID *pBuf);

#ifndef GFX2D_PROC_UNSUPPORT

HI_VOID GFX2D_MEM_ReadProc(struct seq_file *p, HI_VOID *v);

HI_VOID GFX2D_MEM_WriteProc(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif  /*_GFX2D_MEM_H_*/
