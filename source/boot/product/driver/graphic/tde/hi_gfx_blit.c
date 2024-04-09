/**********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***********************************************************************************************
File Name          : hi_gfx_blit.c
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : display through gfx layer or vo
                     CNcomment: 2D加速CNend\n
Function List      :
History            :
Date                          Author                     Modification
2018/01/01                    sdk                        Created file
***********************************************************************************************/



/*********************************add include here*********************************************/
#include "hi_gfx_mem.h"
#include "hi_gfx_comm.h"

#include "hi_gfx_show.h"
#include "hi_gfx_surface.h"
#include "hi_gfx_sys.h"

#include "hi_gfx_blit.h"
#include "hi_tde_type.h"
#include "hi_tde_api.h"
/***************************** Macro Definition ***********************************************/

#define RGB32TO1555(c) \
    (((c & 0x80000000) >> 16) | ((c & 0xf80000) >> 9) | ((c & 0xf800) >> 6) | ((c & 0xf8) >> 3))

#define RGB32TO565(c) \
    (((c & 0xf80000) >> 8) | ((c & 0xfc00) >> 5) | ((c & 0xf8) >> 3))

/*************************** Structure Definition *********************************************/
struct
{
    HI_GFX_PF_E  HiGfxFmt;
    TDE2_COLOR_FMT_E  enTdeFmt;
}gs_HiGfx_To_Tde_MapTable[] = {
        {HI_GFX_PF_565,   TDE2_COLOR_FMT_RGB565},
        {HI_GFX_PF_1555,  TDE2_COLOR_FMT_ARGB1555},
        {HI_GFX_PF_8888,  TDE2_COLOR_FMT_ARGB8888},
        {HI_GFX_PF_AYCbCr8888,  TDE2_COLOR_FMT_ARGB8888},
    };

struct
{
    HI_GFX_PF_E HiGfxFmt;
    TDE2_MB_COLOR_FMT_E   enTdeFmt;
}gs_HiGfx_To_MBTde_MapTable[] = {
        {HI_GFX_PF_YUV400,      TDE2_MB_COLOR_FMT_JPG_YCbCr400MBP},
        {HI_GFX_PF_YUV420,      TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP},
        {HI_GFX_PF_YUV422_12,   TDE2_MB_COLOR_FMT_JPG_YCbCr422MBVP},
        {HI_GFX_PF_YUV422_21,   TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP},
        {HI_GFX_PF_YUV444,      TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP}
    };

/********************** Global Variable declaration *******************************************/

static HI_S32 GFX_ADP_ConvertFormat(HI_GFX_PF_E enPixelFormat, TDE2_COLOR_FMT_E *pTdeFmt);
static inline HI_S32 GFX_ADP_ColorExpand(HI_GFX_PF_E enPixelFormat, HI_U32 u32Color, HI_U32 *pFillData);

/************************** Api declaration ***************************************************/

/**********************       API realization       *******************************************/


/*****************************************************************************
* func         : GFX_ADP_ConvertMBFormat
* description  : surface像素格式转成tde需要的像素格式
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
static HI_S32 GFX_ADP_ConvertMBFormat(HI_GFX_PF_E enPixelFormat, TDE2_MB_COLOR_FMT_E *pTdeFmt)
{
    HI_S32 Cnt  = 0;
    HI_S32 Size = 0;
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL(pTdeFmt);

    Size = (HI_S32)(sizeof(gs_HiGfx_To_MBTde_MapTable) / sizeof(gs_HiGfx_To_MBTde_MapTable[0]));

    for (Cnt = 0; Cnt < Size; Cnt++)
    {
        if (gs_HiGfx_To_MBTde_MapTable[Cnt].HiGfxFmt == enPixelFormat)
        {
            *pTdeFmt = gs_HiGfx_To_MBTde_MapTable[Cnt].enTdeFmt;
            HI_GFX_LOG_FuncExit();
            return HI_SUCCESS;
        }
    }

    HI_GFX_LOG_PrintErrCode(HI_FAILURE);
    return HI_FAILURE;
}


/*****************************************************************************
* func         : GFX_ADP_YCbCrToRgb
* description  : yuv转rgb
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
static HI_S32 GFX_ADP_YCbCrToRgb(HI_LOGO_SURFACE_S* pSrcSurface, TDE2_RECT_S *pSrcRect, HI_LOGO_SURFACE_S* pDstSurface, TDE2_RECT_S *pDstRect, HI_BOOL bScale)
{
    HI_S32 Ret = HI_SUCCESS;
    TDE_HANDLE s32Handle = HI_ERR_TDE_INVALID_HANDLE;
    TDE2_MB_S stSrcSurface;
    TDE2_SURFACE_S stDstSurface;
    TDE2_MBOPT_S stMbOpt;
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL(pSrcSurface);
    CHECK_POINT_NULL(pSrcRect);
    CHECK_POINT_NULL(pDstSurface);
    CHECK_POINT_NULL(pDstRect);

    HI_GFX_Memset(&stSrcSurface,0,sizeof(stSrcSurface));
    HI_GFX_Memset(&stDstSurface,0,sizeof(stDstSurface));
    HI_GFX_Memset(&stMbOpt,0,sizeof(stMbOpt));

    Ret = GFX_ADP_ConvertMBFormat(pSrcSurface->enPixelFormat, &(stSrcSurface.enMbFmt));
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_DBG_PrintUInt(pSrcSurface->enPixelFormat);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (HI_SUCCESS != GFX_ADP_ConvertFormat(pDstSurface->enPixelFormat, &(stDstSurface.enColorFmt)))
    {
        HI_GFX_DBG_PrintUInt(pDstSurface->enPixelFormat);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    stSrcSurface.u32YPhyAddr    = (HI_U32)pSrcSurface->pPhyAddr[0];
    stSrcSurface.u32CbCrPhyAddr = (HI_U32)pSrcSurface->pPhyAddr[1];
    stSrcSurface.u32YStride     = pSrcSurface->u32Stride[0];
    stSrcSurface.u32CbCrStride  = pSrcSurface->u32Stride[1];
    stSrcSurface.u32YWidth      = pSrcSurface->u32Width[0];
    stSrcSurface.u32YHeight     = pSrcSurface->u32Height[0];

    CHECK_PARA_ZERO(stSrcSurface.u32YPhyAddr);

    /**output src information
     **打印输入源信息
     **/
    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintXInt(stSrcSurface.u32YPhyAddr);
    HI_GFX_DBG_PrintXInt(stSrcSurface.u32CbCrPhyAddr);
    HI_GFX_DBG_PrintUInt(stSrcSurface.u32YStride);
    HI_GFX_DBG_PrintUInt(stSrcSurface.u32YWidth);
    HI_GFX_DBG_PrintUInt(stSrcSurface.u32YHeight);
    HI_GFX_DBG_PrintUInt(stSrcSurface.enMbFmt);
    HI_GFX_DBG_PrintInfo("============================================================================");

    stDstSurface.u32PhyAddr     = (HI_U32)pDstSurface->pPhyAddr[0];
#ifdef CONFIG_GFX_DOUBLE_BUFFER_SUPPORT
    if ((HI_TRUE == pDstSurface->bUseLayerSurface) && (pDstSurface->InUsingDispIndex < CONFIG_GFX_PIXELDATA_NUM))
    {
        stDstSurface.u32PhyAddr = (HI_U32)pDstSurface->pPhyAddr[pDstSurface->InUsingDispIndex];
    }
#endif
    stDstSurface.u32Height      = pDstSurface->u32Height[0];
    stDstSurface.u32Width       = pDstSurface->u32Width[0];
    stDstSurface.u32Stride      = pDstSurface->u32Stride[0];
    stDstSurface.pu8ClutPhyAddr = NULL;
    stDstSurface.bYCbCrClut     = HI_FALSE;
    stDstSurface.bAlphaMax255   = HI_TRUE;
    stDstSurface.bAlphaExt1555  = HI_TRUE;
    stDstSurface.u8Alpha0       = 0;
    stDstSurface.u8Alpha1       = 255;

    CHECK_PARA_ZERO(stDstSurface.u32PhyAddr);

    if (HI_TRUE == bScale)
    {
        stMbOpt.enResize = TDE2_MBRESIZE_QUALITY_LOW;
    }

    /**output dst information
     **打印输出源信息
     **/
    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintXInt(stDstSurface.u32PhyAddr);
    HI_GFX_DBG_PrintXInt(stDstSurface.u32Height);
    HI_GFX_DBG_PrintUInt(stDstSurface.u32Width);
    HI_GFX_DBG_PrintUInt(stDstSurface.u32Stride);
    HI_GFX_DBG_PrintUInt(stDstSurface.enColorFmt);
    HI_GFX_DBG_PrintUInt(stMbOpt.enResize);
    HI_GFX_DBG_PrintInfo("============================================================================");

    s32Handle = HI_TDE2_BeginJob();
    if (s32Handle == HI_ERR_TDE_INVALID_HANDLE)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    /**output src dst rect
     **打印输入输出矩形
     **/
    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintInt(pSrcRect->s32Xpos);
    HI_GFX_DBG_PrintInt(pSrcRect->s32Ypos);
    HI_GFX_DBG_PrintUInt(pSrcRect->u32Width);
    HI_GFX_DBG_PrintUInt(pSrcRect->u32Height);
    HI_GFX_DBG_PrintInt(pDstRect->s32Xpos);
    HI_GFX_DBG_PrintInt(pDstRect->s32Ypos);
    HI_GFX_DBG_PrintUInt(pDstRect->u32Width);
    HI_GFX_DBG_PrintUInt(pDstRect->u32Height);
    HI_GFX_DBG_PrintInfo("============================================================================");

    Ret = HI_TDE2_MbBlit(s32Handle, &stSrcSurface,pSrcRect, &stDstSurface, pDstRect, &stMbOpt);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        (HI_VOID)HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 100);
        return HI_FAILURE;
    }

    Ret |= HI_TDE2_EndJob(s32Handle, HI_FALSE, HI_TRUE, 100);
    if ((HI_SUCCESS != Ret) && (HI_ERR_TDE_JOB_TIMEOUT != Ret))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    HI_GFX_Memcmp((HI_CHAR*)stDstSurface.u32PhyAddr, stDstSurface.u32Stride * stDstSurface.u32Height);

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}


/*****************************************************************************
* func         : GFX_ADP_RgbToRgb
* description  : rgb转rgb
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
static HI_S32 GFX_ADP_RgbToRgb(HI_LOGO_SURFACE_S* pSrcSurface, TDE2_RECT_S *pSrcRect, HI_LOGO_SURFACE_S* pDstSurface, TDE2_RECT_S *pDstRect,HI_BOOL bScale)
{
    HI_S32 Ret = HI_SUCCESS;
    TDE_HANDLE s32Handle = HI_ERR_TDE_INVALID_HANDLE;
    TDE2_SURFACE_S stSrcSurface;
    TDE2_SURFACE_S stDstSurface;
    TDE2_OPT_S stOpt;
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL(pSrcSurface);
    CHECK_POINT_NULL(pSrcRect);
    CHECK_POINT_NULL(pDstSurface);
    CHECK_POINT_NULL(pDstRect);

    HI_GFX_Memset(&stSrcSurface,0,sizeof(stSrcSurface));
    HI_GFX_Memset(&stDstSurface,0,sizeof(stDstSurface));
    HI_GFX_Memset(&stOpt,0,sizeof(stOpt));

    if (HI_SUCCESS != GFX_ADP_ConvertFormat(pSrcSurface->enPixelFormat, &(stSrcSurface.enColorFmt)))
    {
        HI_GFX_DBG_PrintUInt(pSrcSurface->enPixelFormat);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (HI_SUCCESS != GFX_ADP_ConvertFormat(pDstSurface->enPixelFormat, &(stDstSurface.enColorFmt)))
    {
        HI_GFX_DBG_PrintUInt(pDstSurface->enPixelFormat);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    stSrcSurface.u32PhyAddr     = (HI_U32)pSrcSurface->pPhyAddr[0];
    stSrcSurface.u32Height      = pSrcSurface->u32Height[0];
    stSrcSurface.u32Width       = pSrcSurface->u32Width[0];
    stSrcSurface.u32Stride      = pSrcSurface->u32Stride[0];
    stSrcSurface.pu8ClutPhyAddr = NULL;
    stSrcSurface.bYCbCrClut     = HI_FALSE;
    stSrcSurface.bAlphaMax255   = HI_TRUE;
    stSrcSurface.bAlphaExt1555  = HI_TRUE;
    stSrcSurface.u8Alpha0       = 0;
    stSrcSurface.u8Alpha1       = 255;

    CHECK_PARA_ZERO(stSrcSurface.u32PhyAddr);

    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintXInt(stSrcSurface.u32PhyAddr);
    HI_GFX_DBG_PrintUInt(stSrcSurface.u32Stride);
    HI_GFX_DBG_PrintUInt(stSrcSurface.u32Width);
    HI_GFX_DBG_PrintUInt(stSrcSurface.u32Height);
    HI_GFX_DBG_PrintUInt(stSrcSurface.enColorFmt);
    HI_GFX_DBG_PrintInfo("============================================================================");

    stDstSurface.u32PhyAddr     = (HI_U32)pDstSurface->pPhyAddr[0];
#ifdef CONFIG_GFX_DOUBLE_BUFFER_SUPPORT
    if ((HI_TRUE == pDstSurface->bUseLayerSurface) && (pDstSurface->InUsingDispIndex < CONFIG_GFX_PIXELDATA_NUM))
    {
        stDstSurface.u32PhyAddr = (HI_U32)pDstSurface->pPhyAddr[pDstSurface->InUsingDispIndex];
    }
#endif
    stDstSurface.u32Height      = pDstSurface->u32Height[0];
    stDstSurface.u32Width       = pDstSurface->u32Width[0];
    stDstSurface.u32Stride      = pDstSurface->u32Stride[0];
    stDstSurface.pu8ClutPhyAddr = NULL;
    stDstSurface.bYCbCrClut     = HI_FALSE;
    stDstSurface.bAlphaMax255   = HI_TRUE;
    stDstSurface.bAlphaExt1555  = HI_TRUE;
    stDstSurface.u8Alpha0       = 0;
    stDstSurface.u8Alpha1       = 255;

    CHECK_PARA_ZERO(stDstSurface.u32PhyAddr);

    stOpt.enColorKeyMode = TDE2_COLORKEY_MODE_NONE;
    stOpt.enOutAlphaFrom = TDE2_OUTALPHA_FROM_NORM;
    stOpt.enAluCmd       = TDE2_ALUCMD_NONE;
    stOpt.u8GlobalAlpha  = 0xff;
    if (HI_TRUE == bScale)
    {
        stOpt.bResize      = HI_TRUE;
        stOpt.enFilterMode = TDE2_FILTER_MODE_COLOR;
    }

    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintXInt(stDstSurface.u32PhyAddr);
    HI_GFX_DBG_PrintUInt(stDstSurface.u32Stride);
    HI_GFX_DBG_PrintUInt(stDstSurface.u32Width);
    HI_GFX_DBG_PrintUInt(stDstSurface.u32Height);
    HI_GFX_DBG_PrintUInt(stDstSurface.enColorFmt);
    HI_GFX_DBG_PrintUInt(stOpt.enColorKeyMode);
    HI_GFX_DBG_PrintUInt(stOpt.enOutAlphaFrom);
    HI_GFX_DBG_PrintUInt(stOpt.enAluCmd);
    HI_GFX_DBG_PrintUInt(stOpt.u8GlobalAlpha);
    HI_GFX_DBG_PrintUInt(stOpt.bResize);
    HI_GFX_DBG_PrintUInt(stOpt.enFilterMode);
    HI_GFX_DBG_PrintInfo("============================================================================");

    s32Handle = HI_TDE2_BeginJob();
    if (s32Handle == HI_ERR_TDE_INVALID_HANDLE)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    Ret = HI_TDE2_Bitblit(s32Handle,&stDstSurface,pDstRect,&stSrcSurface,pSrcRect,&stDstSurface,pDstRect,&stOpt);
    if (Ret != HI_SUCCESS)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        (HI_VOID)HI_TDE2_EndJob(s32Handle,HI_FALSE,HI_TRUE,100);
        return HI_FAILURE;
    }

    Ret |= HI_TDE2_EndJob(s32Handle,HI_FALSE,HI_TRUE,100);
    if ((HI_SUCCESS != Ret) && (HI_ERR_TDE_JOB_TIMEOUT != Ret))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    HI_GFX_Memcmp((HI_CHAR*)stDstSurface.u32PhyAddr, stDstSurface.u32Stride * stDstSurface.u32Height);

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : HI_GFX_Blit
* description   : blit src surface to dst surface
                  CNcomment: 将源surface数据搬移到目标surface上CNend\n
* param[in]     : hSrcSurface        CNcomment:源surface    CNend\n
* param[in]     : pSrcRect           CNcomment:源矩形大小   CNend\n
* param[in]     : hDstSurface        CNcomment:目标surface  CNend\n
* param[in]     : pDstRect           CNcomment:目标矩形大小 CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_Blit(HI_HANDLE hSrcSurface, HI_RECT* pSrcRect, HI_HANDLE hDstSurface, HI_RECT* pDstRect, const HI_GFX_BLTOPT_S* pBlitOpt)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_BOOL bEnableScale = HI_FALSE;
    HI_LOGO_SURFACE_S *pstSrcSurface = (HI_LOGO_SURFACE_S *)hSrcSurface;
    HI_LOGO_SURFACE_S *pstDstSurface = (HI_LOGO_SURFACE_S *)hDstSurface;
    TDE2_RECT_S stSrcRect = {0};
    TDE2_RECT_S stDstRect = {0};
    HI_GFX_UNF_FuncEnter();

    CHECK_POINT_NULL(pstSrcSurface);
    CHECK_POINT_NULL(pstDstSurface);
    CHECK_POINT_NULL(pBlitOpt);

    if (NULL == pSrcRect)
    {
        stSrcRect.u32Width  = pstSrcSurface->u32Width[0];
        stSrcRect.u32Height = pstSrcSurface->u32Height[0];
    }
    else
    {
        stSrcRect.s32Xpos   = pSrcRect->x;
        stSrcRect.s32Ypos   = pSrcRect->y;
        stSrcRect.u32Width  = pSrcRect->w;
        stSrcRect.u32Height = pSrcRect->h;
    }

    if (NULL == pDstRect)
    {
        stDstRect.u32Width  = pstDstSurface->u32Width[0];
        stDstRect.u32Height = pstDstSurface->u32Height[0];
    }
    else
    {
        stDstRect.s32Xpos   = pDstRect->x;
        stDstRect.s32Ypos   = pDstRect->y;
        stDstRect.u32Width  = pDstRect->w;
        stDstRect.u32Height = pDstRect->h;
    }

    bEnableScale = pBlitOpt->EnableScale;
    if (pstSrcSurface->enPixelFormat >= HI_GFX_PF_YUV400 && pstSrcSurface->enPixelFormat <= HI_GFX_PF_YUV422_21)
    {
        Ret = GFX_ADP_YCbCrToRgb(pstSrcSurface, &stSrcRect, pstDstSurface, &stDstRect,bEnableScale);
    }
    else
    {
        Ret = GFX_ADP_RgbToRgb(pstSrcSurface, &stSrcRect, pstDstSurface, &stDstRect,bEnableScale);
    }
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        goto ERROR_EXIT;
    }

    HI_GFX_UNF_FuncExit();
    return HI_SUCCESS;

ERROR_EXIT:
    return HI_FAILURE;
}

/*****************************************************************************
* func         : HI_BOOT_GFX2D_Init
* description  : 2d加速初始化
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_S32 HI_BOOT_GFX2D_Init(HI_VOID)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_GFX_LOG_FuncEnter();

    Ret = HI_TDE2_Open();
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    Ret = HI_TDE2_SetAlphaThresholdState(HI_TRUE);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    Ret = HI_TDE2_SetAlphaThresholdValue(0x80);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}

/*****************************************************************************
* func         : HI_GFX_FillRect
* description  : 填充矩形
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_S32 HI_GFX_FillRect(HI_HANDLE hSurface, const HI_RECT* pstRect, HI_U32 u32Color, HI_GFX_COMPOPT_E eComPopt)
{
    HI_S32 Ret = HI_SUCCESS;
    TDE_HANDLE s32Handle = HI_ERR_TDE_INVALID_HANDLE;
    TDE2_RECT_S stRect = {0};
    HI_U32 u32FillData = 0;
    TDE2_SURFACE_S stSurface;
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S *)hSurface;
    HI_GFX_UNF_FuncEnter();

    CHECK_POINT_NULL(pstSurface);

    if (NULL == pstRect)
    {
        stRect.u32Width  = pstSurface->u32Width[0];
        stRect.u32Height = pstSurface->u32Height[0];
    }
    else
    {
        stRect.s32Xpos   = pstRect->x;
        stRect.s32Ypos   = pstRect->y;
        stRect.u32Width  = pstRect->w;
        stRect.u32Height = pstRect->h;
    }

    HI_GFX_Memset(&stSurface,0,sizeof(stSurface));

    Ret = GFX_ADP_ConvertFormat(pstSurface->enPixelFormat, &(stSurface.enColorFmt));
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_DBG_PrintUInt(pstSurface->enPixelFormat);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    Ret = GFX_ADP_ColorExpand(pstSurface->enPixelFormat,u32Color,&u32FillData);
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_DBG_PrintUInt(pstSurface->enPixelFormat);
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    stSurface.u32PhyAddr     = (HI_U32)pstSurface->pPhyAddr[0];
    stSurface.u32Height      = pstSurface->u32Height[0];
#ifdef CONFIG_GFX_DOUBLE_BUFFER_SUPPORT
    if (HI_TRUE == pstSurface->bUseLayerSurface)
    {
        stSurface.u32Height = pstSurface->u32Height[0] * CONFIG_GFX_LAYER_BUF_NUM;
    }
#endif
    stSurface.u32Width       = pstSurface->u32Width[0];
    stSurface.u32Stride      = pstSurface->u32Stride[0];
    stSurface.pu8ClutPhyAddr = NULL;
    stSurface.bYCbCrClut     = HI_FALSE;
    stSurface.bAlphaMax255   = HI_TRUE;
    stSurface.bAlphaExt1555  = HI_TRUE;
    stSurface.u8Alpha0       = 0;
    stSurface.u8Alpha1       = 255;

    CHECK_PARA_ZERO(stSurface.u32PhyAddr);

    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintXInt(stSurface.u32PhyAddr);
    HI_GFX_DBG_PrintUInt(stSurface.u32Stride);
    HI_GFX_DBG_PrintUInt(stSurface.u32Width);
    HI_GFX_DBG_PrintUInt(stSurface.u32Height);
    HI_GFX_DBG_PrintUInt(stSurface.enColorFmt);
    HI_GFX_DBG_PrintXInt(u32FillData);
    HI_GFX_DBG_PrintInfo("============================================================================");

    s32Handle = HI_TDE2_BeginJob();
    if (s32Handle == HI_ERR_TDE_INVALID_HANDLE)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        goto ERROR_EXIT;
    }

    Ret = HI_TDE2_QuickFill(s32Handle, &stSurface, &stRect, u32FillData);
    if (Ret != HI_SUCCESS)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        (HI_VOID)HI_TDE2_EndJob(s32Handle,HI_FALSE,HI_TRUE,100);
        goto ERROR_EXIT;
    }

    Ret |= HI_TDE2_EndJob(s32Handle,HI_FALSE,HI_TRUE,100);
    if ((HI_SUCCESS != Ret) && (HI_ERR_TDE_JOB_TIMEOUT != Ret))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        goto ERROR_EXIT;
    }

    HI_GFX_Memcmp((HI_CHAR*)stSurface.u32PhyAddr, pstSurface->u32Stride[0] * pstSurface->u32Height[0]);

    HI_GFX_UNF_FuncExit();
    return HI_SUCCESS;

ERROR_EXIT:
    return HI_FAILURE;
}

static HI_S32 GFX_ADP_ConvertFormat(HI_GFX_PF_E enPixelFormat, TDE2_COLOR_FMT_E *pTdeFmt)
{
    HI_S32 Cnt  = 0;
    HI_S32 Size = 0;
    HI_GFX_LOG_FuncEnter();

    CHECK_PARA_ZERO(pTdeFmt);

    Size = (HI_S32)(sizeof(gs_HiGfx_To_Tde_MapTable) / sizeof(gs_HiGfx_To_Tde_MapTable[0]));

    for (Cnt = 0; Cnt < Size; Cnt++)
    {
        if (gs_HiGfx_To_Tde_MapTable[Cnt].HiGfxFmt == enPixelFormat)
        {
            *pTdeFmt = gs_HiGfx_To_Tde_MapTable[Cnt].enTdeFmt;
            return HI_SUCCESS;
        }
    }

    HI_GFX_LOG_PrintErrCode(HI_FAILURE);

    HI_GFX_LOG_FuncExit();
    return HI_FAILURE;
}


static inline HI_S32 GFX_ADP_ColorExpand(HI_GFX_PF_E enPixelFormat, HI_U32 u32Color, HI_U32 *pFillData)
{
    HI_GFX_LOG_FuncEnter();
    switch (enPixelFormat)
    {
        case HI_GFX_PF_1555:
            *pFillData = (HI_U32)RGB32TO1555(u32Color);
            break;

        case HI_GFX_PF_8888:
        case HI_GFX_PF_AYCbCr8888:
            *pFillData = (HI_U32)u32Color;
            break;

        case HI_GFX_PF_565:
            *pFillData = RGB32TO565(u32Color);
            break;

        default:
            HI_GFX_LOG_PrintErrCode(HI_FAILURE);
            return HI_FAILURE;
    }
    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}
