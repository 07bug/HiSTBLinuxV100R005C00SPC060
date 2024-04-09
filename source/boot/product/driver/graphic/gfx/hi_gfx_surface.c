/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name          : hi_gfx_surface.c
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : CNcomment:surface管理CNend\n
Function List      :
History            :
Date                           Author                       Modification
2018/01/01                     sdk                          Created file
*************************************************************************************************/


/*********************************add include here***********************************************/
#include "hi_gfx_surface.h"
#include "hi_gfx_mem.h"
#include "hi_gfx_comm.h"
#include "hi_gfx_sys.h"

/************************** Macro Definition     ************************************************/

/************************** Structure Definition ************************************************/

/************************** Global Variable declaration *****************************************/
extern HI_HANDLE gs_LayerSurface;

/************************** Api declaration *****************************************************/

/************************** API realization *****************************************************/
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
HI_S32 HI_GFX_CreateSurface(HI_U32 Width, HI_U32 Height, HI_GFX_PF_E PixelFormat,HI_HANDLE *pSurface)
{
    HI_HANDLE hSurface = 0;
    HI_U32 Stride = 0;
    HI_LOGO_SURFACE_S *pstSurface = NULL;
    CHECK_POINT_NULL(pSurface);
    HI_GFX_UNF_FuncEnter();

    if ((Width < CONFIG_GFX_MINWIDTH) || (Width > CONFIG_GFX_MAXWIDTH))
    {
        HI_GFX_DBG_PrintUInt(Width);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MINWIDTH);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MAXWIDTH);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if ((Height < CONFIG_GFX_MINHEIGHT) || (Height > CONFIG_GFX_MAXHEIGHT))
    {
        HI_GFX_DBG_PrintUInt(Height);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MINHEIGHT);
        HI_GFX_DBG_PrintUInt(CONFIG_GFX_MAXHEIGHT);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    hSurface = (HI_HANDLE)HI_GFX_Malloc(sizeof(HI_LOGO_SURFACE_S),"memory-surface-handle");
    if (0 == hSurface)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    HI_GFX_Memset((HI_VOID*)hSurface,0x0,sizeof(HI_LOGO_SURFACE_S));
    *pSurface = hSurface;

    switch (PixelFormat)
    {
        case HI_GFX_PF_8888:
            Stride = (Width * 4 + 16 - 1) & (~(16 - 1));
            break;
        case HI_GFX_PF_0888:
            Stride = (Width * 3 + 16 - 1) & (~(16 - 1));
            break;
        case HI_GFX_PF_1555:
        case HI_GFX_PF_565:
            Stride = (Width * 2 + 16 - 1) & (~(16 - 1));
            break;
        default:
            HI_GFX_LOG_PrintErrCode(HI_FAILURE);
            HI_GFX_Free((HI_CHAR*)hSurface);
            return HI_FAILURE;
    }

    pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    pstSurface->enPixelFormat = PixelFormat;
    pstSurface->u32Width[0]   = Width;
    pstSurface->u32Height[0]  = Height;
    pstSurface->u32Stride[0]  = Stride;
    pstSurface->u32Size[0]    = Stride * Height;

    if (0 == pstSurface->u32Size[0])
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        HI_GFX_Free((HI_CHAR*)hSurface);
        return HI_FAILURE;
    }

    pstSurface->pPhyAddr[0] = (HI_CHAR*)HI_GFX_MMZ_Malloc(pstSurface->u32Size[0],"surface-buf");
    if (NULL == pstSurface->pPhyAddr[0])
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        HI_GFX_Free((HI_CHAR*)hSurface);
        return HI_FAILURE;
    }
    pstSurface->pVirAddr[0] = pstSurface->pPhyAddr[0];

    HI_GFX_UNF_FuncExit();
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : HI_GFX_FreeSurface
* description   : free surface
                  CNcomment: 释放surface CNend\n
* param[in]     : hSurface        CNcomment: 创建过的surface CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_FreeSurface(HI_HANDLE hSurface)
{
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    CHECK_POINT_NULL(pstSurface);
    HI_GFX_UNF_FuncEnter();

    if ((NULL != pstSurface->pPhyAddr[0]) && (HI_FALSE == pstSurface->bUseLayerSurface))
    {
        HI_GFX_MMZ_Free(pstSurface->pPhyAddr[0]);
        pstSurface->pPhyAddr[0] = NULL;
        pstSurface->pPhyAddr[1] = NULL;
        pstSurface->pPhyAddr[2] = NULL;
        pstSurface->pVirAddr[0] = NULL;
        pstSurface->pVirAddr[1] = NULL;
        pstSurface->pVirAddr[2] = NULL;
    }

    if (HI_TRUE == pstSurface->bUseLayerSurface)
    {
        gs_LayerSurface = HI_GFX_INVALID_HANDLE;
    }

    HI_GFX_Free((HI_CHAR*)pstSurface);

    HI_GFX_UNF_FuncExit();

    return HI_SUCCESS;
}

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
HI_S32 HI_GFX_GetSurfaceSize(HI_HANDLE hSurface, HI_U32* pWidth, HI_U32* pHeight)
{
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    CHECK_POINT_NULL(pstSurface);
    HI_GFX_UNF_FuncEnter();

    if (NULL != pWidth)
    {
        *pWidth = pstSurface->u32Width[0];
    }

    if (NULL != pHeight)
    {
        *pHeight = pstSurface->u32Height[0];
    }

    HI_GFX_UNF_FuncExit();
    return HI_SUCCESS;
}

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
HI_S32 HI_GFX_LockSurface(HI_HANDLE hSurface, HI_PIXELDATA pData, HI_BOOL bSync)
{
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    HI_UNUSED(bSync);
    HI_GFX_UNF_FuncEnter();

    CHECK_POINT_NULL(pstSurface);

    pData[0].Pitch    = pstSurface->u32Stride[0];
    pData[0].pPhyData = pstSurface->pPhyAddr[0];

    switch (pstSurface->enPixelFormat)
    {
        case HI_GFX_PF_8888:
            pData[0].Bpp = 4;
            break;
        case HI_GFX_PF_0888:
            pData[0].Bpp = 3;
            break;
        case HI_GFX_PF_1555:
        case HI_GFX_PF_565:
            pData[0].Bpp = 2;
            break;
        default:
            pData[0].Bpp = 4;
            break;
    }

    HI_GFX_UNF_FuncExit();
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : HI_GFX_UnLockSurface
* description   : UnLock surface
                  CNcomment: Unlock surface CNend\n
* param[in]     : hSurface        CNcomment: 创建过的surface CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_UnLockSurface(HI_HANDLE hSurface)
{
    HI_GFX_UNF_FuncEnter();
    HI_UNUSED(hSurface);
    HI_GFX_UNF_FuncExit();
    return HI_SUCCESS;
}
