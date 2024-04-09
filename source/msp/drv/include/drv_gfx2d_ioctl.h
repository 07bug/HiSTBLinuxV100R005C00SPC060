/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name      : drv_gfx2d_ioctl.h
Version        : Initial Draft
Author         :
Created        : 2018/01/01
Description    :
Function List  :


History        :
Date                 Author                  Modification
2018/01/01            sdk                    Created file
************************************************************************************************/
#ifndef _DRV_GFX2D_IOCTL_H_
#define _DRV_GFX2D_IOCTL_H_


/*********************************add include here*********************************************/
#include <linux/ioctl.h>


/**********************************************************************************************/


/**********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ***********************************************/
#define GFX2D_IOC_MAGIC        'G'


/*************************** Structure Definition *********************************************/
typedef struct tagGFX2D_COMPOSE_LIST_S
{
    HI_U64   u64Compose;        /**<CNcomment:.叠加层链表,按照由下到上的顺序排列*/
    HI_U32   u32ComposeCnt;     /**<CNcomment:.叠加层数量*/
    HI_U32   u32BgColor;        /**<CNcomment:叠加背景色.*/
}GFX2D_COMPOSE_LIST_S;

typedef struct
{
    HI_GFX2D_DEV_ID_E       enDevId;
    HI_GFX2D_COMPOSE_LIST_S stComposeList;
    HI_GFX2D_SURFACE_S      *pstDst;
    HI_BOOL bSync;
    HI_U32 u32Timeout;
}GFX2D_COMPOSE_CMD_HAL_S;

typedef struct
{
    HI_GFX2D_DEV_ID_E       enDevId;
    GFX2D_COMPOSE_LIST_S    stComposeList;
    HI_GFX2D_SURFACE_S      stDst;
    HI_BOOL bSync;
    HI_U32 u32Timeout;
}GFX2D_COMPOSE_CMD_S;

typedef struct
{
    HI_GFX2D_DEV_ID_E enDevId;
    HI_U32 u32Timeout;
}GFX2D_WAITALLDONE_CMD_S;

/***************************  The enum of Jpeg image format  **********************************/

/********************** Global Variable declaration *******************************************/

/******************************* API declaration **********************************************/
#define GFX2D_COMPOSE          _IOW(GFX2D_IOC_MAGIC, 1, GFX2D_COMPOSE_CMD_S)
#define GFX2D_WAITALLDONE      _IOW(GFX2D_IOC_MAGIC, 2, GFX2D_WAITALLDONE_CMD_S)


#ifdef __cplusplus
#if __cplusplus
 }
#endif
#endif /* __cplusplus */

#endif /*_DRV_GFX2D_IOCTL_H_ */
