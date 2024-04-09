/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : gfx2d_list.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                  Modification
2018/01/01            sdk                    Created file
************************************************************************************************/
#ifndef _GFX2D_LIST_H_
#define _GFX2D_LIST_H_

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
typedef struct tagGFX2D_LIST_NODE_S
{
    HI_GFX2D_DEV_ID_E enDevId;
    HI_VOID *pNode;
    GFX2D_HAL_DEV_TYPE_E enNodeType;
    HI_BOOL bSync;
    HI_U32 u32Timeout;
    HI_S32 s32ReleaseFenceFd;
} GFX2D_LIST_NODE_S;

/***************************  The enum of Jpeg image format  **********************************/


/********************** Global Variable declaration *******************************************/


/******************************* API declaration **********************************************/
HI_S32 GFX2D_LIST_Init(HI_VOID);

HI_VOID GFX2D_LIST_Deinit(HI_VOID);

HI_S32 GFX2D_LIST_Open(HI_VOID);

HI_VOID GFX2D_LIST_Close(HI_VOID);

HI_S32 GFX2D_LIST_SubNode(GFX2D_LIST_NODE_S *pstNode, HI_GFX2D_EXTINFO_S *ExtInfo);

HI_S32 GFX2D_LIST_WaitAllDone(const HI_GFX2D_DEV_ID_E enDevId, const HI_U32 u32Timeout);

#ifndef GFX2D_PROC_UNSUPPORT
HI_VOID GFX2D_LIST_ReadProc(struct seq_file *p, HI_VOID *v);

HI_VOID GFX2D_LIST_WriteProc(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
#endif

HI_S32 GFX2D_LIST_Resume(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif  /*_GFX2D_LIST_H_*/
