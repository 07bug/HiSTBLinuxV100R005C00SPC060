/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name          : hi_gfx_surface.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        :
                     CNcomment:surface管理CNend\n
Function List      :
History            :
Date                           Author                     Modification
2018/01/01                     sdk                         Created file
**************************************************************************************************/

#ifndef  __HI_GFX_SURFACE_H__
#define  __HI_GFX_SURFACE_H__


/*********************************add include here*************************************************/

#include "hi_gfx_show.h"
#include "hi_gfx_comm.h"

/***************************** Macro Definition ***************************************************/

#define  CONFIG_GFX_PIXELDATA_NUM         3

/*************************** Structure Definition *************************************************/

typedef struct hiLOGOSURFACE_S
{
    HI_BOOL bUseLayerSurface;
    HI_BOOL bVoDispSupport;
    HI_U32  InUsingDispIndex;
    HI_U32  u32Width[CONFIG_GFX_PIXELDATA_NUM];
    HI_U32  u32Height[CONFIG_GFX_PIXELDATA_NUM];
    HI_U32  u32Stride[CONFIG_GFX_PIXELDATA_NUM];
    HI_U32  u32Size[CONFIG_GFX_PIXELDATA_NUM];
    HI_CHAR* pPhyAddr[CONFIG_GFX_PIXELDATA_NUM];
    HI_CHAR* pVirAddr[CONFIG_GFX_PIXELDATA_NUM];
    HI_GFX_RECT_S stRect;
    HI_GFX_LAYER_ID_E enLayerID;
    HI_GFX_PF_E  enPixelFormat;
}HI_LOGO_SURFACE_S;

typedef struct hiGFX_PIXELDATA_S
{
    HI_VOID* pPhyData;
    HI_U32   Pitch;
    HI_U32 Bpp;
}HI_GFX_PIXELDATA_S;

/********************** Global Variable declaration ***********************************************/
typedef HI_GFX_PIXELDATA_S  HI_PIXELDATA[CONFIG_GFX_PIXELDATA_NUM];

/******************************* API declaration **************************************************/

/***************************************************************************************
* func          : HI_GFX_CreateSurface
* description   : create surface
                  CNcomment: 创建普通surface CNend\n
* param[in]     : Width        CNcomment: surface宽       CNend\n
* param[in]     : Height       CNcomment: surface高       CNend\n
* param[in]     : PixelFormat  CNcomment: surface像素格式 CNend\n
* param[out]    : pSurface     CNcomment: 输出解码surface，使用完之后需要调用HI_GFX_FreeSurface释放内存 CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_CreateSurface(HI_U32 Width, HI_U32 Height, HI_GFX_PF_E PixelFormat,HI_HANDLE *pSurface);

/***************************************************************************************
* func          : HI_GFX_FreeSurface
* description   : free surface
                  CNcomment: 释放surface CNend\n
* param[in]     : hSurface        CNcomment: 创建过的surface CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_FreeSurface(HI_HANDLE hSurface);

/***************************************************************************************
* func          : HI_GFX_GetSurfaceSize
* description   : get surface size
                  CNcomment: 获取surface 打小 CNend\n
* param[in]     : hSurface        CNcomment: 创建过的surface CNend\n
* param[ou]     : pWidth          CNcomment: 宽 CNend\n
* param[ou]     : pHeight         CNcomment: 高 CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_GetSurfaceSize(HI_HANDLE hSurface, HI_U32* pWidth, HI_U32* pHeight);

/***************************************************************************************
* func          : HI_GFX_LockSurface
* description   : Lock surface
                  CNcomment: 获取surface信息 CNend\n
* param[in]     : hSurface        CNcomment: 创建过的surface CNend\n
* param[in]     : pData           CNcomment: surface信息     CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_LockSurface(HI_HANDLE hSurface, HI_PIXELDATA pData, HI_BOOL bSync);

/***************************************************************************************
* func          : HI_GFX_UnLockSurface
* description   : UnLock surface
                  CNcomment: Unlock surface CNend\n
* param[in]     : hSurface        CNcomment: 创建过的surface CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_UnLockSurface(HI_HANDLE hSurface);

#endif /*__HI_GFX_SURFACE_H__ */
