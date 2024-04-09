/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : gfx2d_hal.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                  Modification
2018/01/01            sdk                    Created file
************************************************************************************************/

#ifndef _GFX2D_HAL_H_
#define _GFX2D_HAL_H_

/*********************************add include here*********************************************/
#include <linux/fs.h>

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
typedef enum tagGFX2D_HAL_DEV_TYPE_E
{
    GFX2D_HAL_DEV_TYPE_HWC = 0x0,
} GFX2D_HAL_DEV_TYPE_E;

/***************************  The enum of Jpeg image format  **********************************/

/*向硬件提交节点*/
typedef HI_S32 (*GFX2D_HAL_SubNode_FN_PTR)(HI_GFX2D_DEV_ID_E enDevId, HI_VOID *pNode);

/*将两个节点按照硬件要求链接成链表*/
typedef HI_S32 (*GFX2D_HAL_LinkNode_FN_PTR)(HI_VOID *pCurNode, HI_VOID *pNextNode);

/*设置节点ID*/
typedef HI_VOID (*GFX2D_HAL_SetNodeID_FN_PTR)(HI_VOID *pNode, HI_U32 u32NodeId);

/*释放节点*/
typedef HI_VOID (*GFX2D_HAL_FreeNode_FN_PTR)(HI_VOID *pNode);

/*中断处理*/
typedef HI_VOID (*GFX2D_HAL_NodeIsr_FN_PTR)(HI_VOID *pNode);

/*中断处理*/
typedef HI_VOID (*GFX2D_HAL_AllNodeIsr_FN_PTR)(HI_VOID);

/*硬件节点操作函数集*/
typedef struct tagGFX2D_HAL_NODE_OPS_S
{
    GFX2D_HAL_SubNode_FN_PTR     pfnSubNode;
    GFX2D_HAL_LinkNode_FN_PTR    pfnLinkNode;
    GFX2D_HAL_SetNodeID_FN_PTR   pfnSetNodeID;
    GFX2D_HAL_FreeNode_FN_PTR    pfnFreeNode;
    GFX2D_HAL_NodeIsr_FN_PTR     pfnNodeIsr;
    GFX2D_HAL_AllNodeIsr_FN_PTR  pfnAllNodeIsr;
} GFX2D_HAL_NODE_OPS_S;

/********************** Global Variable declaration *******************************************/


/******************************* API declaration **********************************************/

HI_S32 GFX2D_HAL_Init(HI_VOID);

HI_VOID GFX2D_HAL_Deinit(HI_VOID);

HI_S32 GFX2D_HAL_Open(HI_VOID);

HI_VOID GFX2D_HAL_Close(HI_VOID);

HI_S32 GFX2D_HAL_Compose(const HI_GFX2D_DEV_ID_E enDevId,
                         const HI_GFX2D_COMPOSE_LIST_S *pstComposeList,
                         const HI_GFX2D_SURFACE_S *pstDstSurface,
                         HI_VOID **ppNode,
                         GFX2D_HAL_DEV_TYPE_E *penNodeType);

#ifndef GFX2D_PROC_UNSUPPORT

HI_VOID GFX2D_HAL_ReadProc(struct seq_file *p, HI_VOID *v);

HI_VOID GFX2D_HAL_WriteProc(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
#endif

HI_VOID GFX2D_HAL_GetNodeOps(const GFX2D_HAL_DEV_TYPE_E enDevType, GFX2D_HAL_NODE_OPS_S **ppstNodeOps);

HI_S32 GFX2D_HAL_GetIntStatus(const GFX2D_HAL_DEV_TYPE_E enDevType);

HI_U32 GFX2D_HAL_GetIsrNum(const HI_GFX2D_DEV_ID_E enDevId, const GFX2D_HAL_DEV_TYPE_E enDevType);

HI_U32 GFX2D_HAL_GetBaseAddr(const HI_GFX2D_DEV_ID_E enDevId, const GFX2D_HAL_DEV_TYPE_E enDevType);

#ifdef GFX2D_ALPHADETECT_SUPPORT
HI_VOID GFX2D_HAL_GetTransparent(HI_GFX2D_EXTINFO_S *ExtInfo);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif  /*_GFX2D_HAL_H_*/
