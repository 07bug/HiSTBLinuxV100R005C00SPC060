/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : hi_gfx_layer.c
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : show
                     CNcomment:显示处理CNend\n
Function List      :
History            :
Date                           Author                     Modification
2018/01/01                     sdk                         Created file
************************************************************************************************/


/************************** add include here****************************************************/
#include "hi_gfx_show.h"
#include "hi_gfx_layer.h"
#include "hi_gfx_surface.h"
#include "hi_gfx_comm.h"
#include "hi_gfx_blit.h"
#include "hi_gfx_decode.h"
#include "hi_gfx_mem.h"
#include "hi_gfx_sys.h"

#ifdef CONFIG_GFX_SUPPORT_VO_4K
#include "drv_com_logo.h"
#endif

#include "drv_hifb_adp.h"
#include "drv_hifb_wbc.h"

#include "hi_drv_disp.h"
#include "drv_disp_ext.h"
/************************** Macro Definition     ***********************************************/

#define WBC_TC_WIDTH      720

/************************** Structure Definition ***********************************************/

typedef enum hiFB_COLOR_FMT_E
{
    HI_FB_FMT_RGB565 = 0,
    HI_FB_FMT_RGB888,        /**<  RGB888 24bpp */

    HI_FB_FMT_KRGB444,       /**<  RGB444 16bpp */
    HI_FB_FMT_KRGB555,       /**<  RGB555 16bpp */
    HI_FB_FMT_KRGB888,       /**<  RGB888 32bpp */

    HI_FB_FMT_ARGB4444,      /**< ARGB4444      */
    HI_FB_FMT_ARGB1555,      /**< ARGB1555      */
    HI_FB_FMT_ARGB8888,      /**< ARGB8888      */
    HI_FB_FMT_ARGB8565,      /**< ARGB8565      */

    HI_FB_FMT_RGBA4444,      /**< ARGB4444      */
    HI_FB_FMT_RGBA5551,      /**< RGBA5551      */
    HI_FB_FMT_RGBA5658,      /**< RGBA5658      */
    HI_FB_FMT_RGBA8888,      /**< RGBA8888      */

    HI_FB_FMT_BGR565,        /**< BGR565        */
    HI_FB_FMT_BGR888,        /**< BGR888        */
    HI_FB_FMT_ABGR4444,      /**< ABGR4444      */
    HI_FB_FMT_ABGR1555,      /**< ABGR1555      */
    HI_FB_FMT_ABGR8888,      /**< ABGR8888      */
    HI_FB_FMT_ABGR8565,      /**< ABGR8565      */
    HI_FB_FMT_KBGR444,       /**< BGR444 16bpp  */
    HI_FB_FMT_KBGR555,       /**< BGR555 16bpp  */
    HI_FB_FMT_KBGR888,       /**< BGR888 32bpp  */

    HI_FB_FMT_1BPP,          /**<  clut1        */
    HI_FB_FMT_2BPP,          /**<  clut2        */
    HI_FB_FMT_4BPP,          /**<  clut4        */
    HI_FB_FMT_8BPP,          /**< clut8         */
    HI_FB_FMT_ACLUT44,       /**< AClUT44       */
    HI_FB_FMT_ACLUT88,       /**< ACLUT88       */
    HI_FB_FMT_PUYVY,         /**< UYVY          */
    HI_FB_FMT_PYUYV,         /**< YUYV          */
    HI_FB_FMT_PYVYU,         /**< YVYU          */
    HI_FB_FMT_YUV888,        /**< YUV888        */
    HI_FB_FMT_AYUV8888,      /**< AYUV8888      */
    HI_FB_FMT_YUVA8888,      /**< YUVA8888      */
    HI_FB_FMT_BUTT
}HI_FB_COLOR_FMT_E;


/************************** Global Variable declaration ****************************************/
HI_HANDLE gs_LayerSurface = HI_GFX_INVALID_HANDLE;
static HI_GFX_DISPLAY_INFO_S gs_stDisplayInfo[HI_GFX_LAYER_MAXCOUNT];

/************************** Api declaration ****************************************************/
#ifdef CONFIG_GFX_SUPPORT_VO_4K
static HI_S32 BOOT_GFX_DisplayLogoWithVo(HI_BOOL bDispSd, HI_HANDLE DecSurface);
#endif

static HI_S32 BOOT_GFX_DisplayLogoWithLayer(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo, HI_U32 LayerId, HI_HANDLE DecSurface);


static HI_S32 GFX_CreateLayer(HI_GFX_LAYER_ID_E enLayerID, HI_BOOL Support4KLogo, HI_GFX_PF_E enPixelFormat, HI_HANDLE *pLayerSurface);
static HI_S32 GfxOpenLayer(HI_LOGO_SURFACE_S *pstGfxSurface, HI_BOOL Support4KLogo);
static HI_S32 GfxLayerIdToGfxId(HI_GFX_LAYER_ID_E eLayerID);
static HI_S32 GfxLayerIdToGpId(HI_GFX_LAYER_ID_E eLayerID);
static HI_S32 GfxGetDisplayInfo(HI_LOGO_SURFACE_S *pstSurface,HI_GFX_DISPLAY_INFO_S *pDisplayInfo, HI_BOOL Support4KLogo);
static HI_U32 GfxParaAlign(HI_U32 x, HI_U32 a);
static inline HI_VOID GfxLayerToHifbFmt(HI_GFX_PF_E SrcFmt,HI_FB_COLOR_FMT_E *DstFmt);

static inline HI_VOID GfxGetLayerInfo(HI_LOGO_SURFACE_S *pstGfxSurface);
static HI_S32 GFX_DestroyLayer(HI_HANDLE hLayerSurface);
static HI_S32 GFX_RefreshLayer(HI_HANDLE hLayerSurface, HI_BOOL Support4KLogo);


HI_VOID GfxWinReviseOutRect(const HI_RECT_S *tmp_virtscreen,             \
                            const HI_DRV_DISP_OFFSET_S *stOffsetInfo,    \
                            const HI_RECT_S *stFmtResolution,            \
                            const HI_RECT_S *stPixelFmtResolution,       \
                            HI_RECT_S *stToBeRevisedRect,                \
                            HI_RECT_S *stRevisedRect);

/************************** API realization ****************************************************/

extern HI_S32 HI_BOOT_GFX2D_Init(HI_VOID);
extern HI_VOID HI_BOOT_GFX_IsSupport4KLOGO(HI_HANDLE DecSurface, HI_BOOL *pSupport4k);

/*****************************************************************************
* func	       :  HI_BOOT_GFX_DisplayWithLayerOrVo
* description  :  CNcomment: 使用图形层或者视频层显示CNend\n
*para[in]      : pInputBaseLogoInfo
*para[in]      : DecSurface
* retval	   : HI_SUCCESS
                 HI_FAILURE
* others:	   : NA
*****************************************************************************/
HI_S32 HI_BOOT_GFX_DisplayWithLayerOrVo(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo, HI_HANDLE DecSurface)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 LayerId = 0;
#ifdef CONFIG_GFX_SUPPORT_VO_4K
    HI_LOGO_SURFACE_S *pstSrcSurface = (HI_LOGO_SURFACE_S *)DecSurface;
#endif
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL(pInputBaseLogoInfo);

#ifdef CONFIG_GFX_SUPPORT_VO_4K
    CHECK_POINT_NULL(pstSrcSurface);
    if (HI_TRUE == pstSrcSurface->bVoDispSupport)
    {
        Ret = BOOT_GFX_DisplayLogoWithVo(pInputBaseLogoInfo->DispToSD, DecSurface);
        HI_GFX_LOG_FuncExit();
        return Ret;
    }
#endif

    LayerId = HI_GFX_LAYER_HD_0;
    Ret = BOOT_GFX_DisplayLogoWithLayer(pInputBaseLogoInfo, LayerId, DecSurface);
    if (HI_SUCCESS != Ret)
    {
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       return HI_FAILURE;
    }

    if (HI_TRUE != pInputBaseLogoInfo->DispToSD)
    {
        HI_GFX_LOG_FuncExit();
        return HI_SUCCESS;
    }

    LayerId = HI_GFX_LAYER_SD_0;
    Ret = BOOT_GFX_DisplayLogoWithLayer(pInputBaseLogoInfo, LayerId, DecSurface);

    HI_GFX_LOG_FuncExit();
    return Ret;
}


#ifdef CONFIG_GFX_SUPPORT_VO_4K
static HI_S32 BOOT_GFX_DisplayLogoWithVo(HI_BOOL bDispSd, HI_HANDLE DecSurface)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_VIDEO_LOGO_INFO LocalLogoInfo;
     HI_LOGO_SURFACE_S *pstSrcSurface = (HI_LOGO_SURFACE_S *)DecSurface;
     CHECK_POINT_NULL(pstSrcSurface);
     HI_GFX_LOG_FuncEnter();

     HI_GFX_Memset(&LocalLogoInfo,0x0,sizeof(LocalLogoInfo));
     LocalLogoInfo.eDispChannelId  = HI_UNF_DISPLAY1;
     LocalLogoInfo.bWbcIso         = (HI_TRUE == bDispSd) ? (HI_FALSE) : (HI_TRUE);
     LocalLogoInfo.ePixelFmt       = HI_DRV_PIX_FMT_NV21;

     LocalLogoInfo.u32LogoWidth    = pstSrcSurface->u32Width[0];
     LocalLogoInfo.u32LogoHeight   = pstSrcSurface->u32Height[0];

     LocalLogoInfo.u32LogoYStride  = pstSrcSurface->u32Stride[0];
     LocalLogoInfo.u32LogoCbStride = pstSrcSurface->u32Stride[1];
     LocalLogoInfo.u32LogoCrStride = pstSrcSurface->u32Stride[2];

     LocalLogoInfo.u32LogoYAddr    = (HI_U32)pstSrcSurface->pPhyAddr[0];
     LocalLogoInfo.u32LogoCbAddr   = (HI_U32)pstSrcSurface->pPhyAddr[1];
     LocalLogoInfo.u32LogoCrAddr   = (HI_U32)pstSrcSurface->pPhyAddr[2];

     Ret = HI_UBOOT_LOGO_CreateLayer(&LocalLogoInfo);
     if (HI_SUCCESS != Ret)
     {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
     }

     HI_GFX_DBG_PrintInfo("============================================================================");
     switch (pstSrcSurface->enPixelFormat)
     {
         case HI_GFX_PF_YUV400:
            HI_GFX_DBG_PrintInfo("output jpeg pix format is yuv400");
            break;
         case HI_GFX_PF_YUV420:
            HI_GFX_DBG_PrintInfo("output jpeg pix format is yuv420");
            break;
         case HI_GFX_PF_YUV422_12:
            HI_GFX_DBG_PrintInfo("output jpeg pix format is yuv422_12");
            break;
         case HI_GFX_PF_YUV422_21:
            HI_GFX_DBG_PrintInfo("output jpeg pix format is yuv422_21");
            break;
         default:
            HI_GFX_DBG_PrintInfo("output jpeg pix format is yuv444");
            break;
     }
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.eDispChannelId);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.bWbcIso);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.ePixelFmt);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.u32LogoWidth);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.u32LogoHeight);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.u32LogoYStride);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.u32LogoCbStride);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.u32LogoCrStride);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.u32LogoYAddr);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.u32LogoCbAddr);
     HI_GFX_DBG_PrintUInt(LocalLogoInfo.u32LogoCrAddr);
     HI_GFX_DBG_PrintInfo("============================================================================");

     HI_GFX_LOG_FuncExit();
     return HI_SUCCESS;
}
#endif

static HI_S32 BOOT_GFX_DisplayLogoWithLayer(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo, HI_U32 LayerId, HI_HANDLE DecSurface)
{
     HI_S32 Ret = HI_SUCCESS;
     HI_U32 DispChanel = 0;
     HI_BOOL GfxSupport4k = HI_FALSE;
     HI_HANDLE LayerSurface = HI_GFX_INVALID_HANDLE;
     HI_GFX_BLTOPT_S stBltOpt;
     HI_GFX_LOG_FuncEnter();

     CHECK_POINT_NULL(pInputBaseLogoInfo);

     if (HI_GFX_LAYER_HD_0 == LayerId)
     {
         DispChanel = CONFIG_GFX_DISP_LOGO_HD;
     }
     else
     {
         DispChanel = CONFIG_GFX_DISP_LOGO_SD;
     }

     HI_BOOT_GFX_IsSupport4KLOGO(DecSurface, &GfxSupport4k);

     Ret = GFX_CreateLayer(LayerId, GfxSupport4k, pInputBaseLogoInfo->DispColorFmt[DispChanel], &LayerSurface);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_LOG_PrintErrCode(HI_FAILURE);
         return HI_FAILURE;
     }

     Ret = HI_BOOT_GFX2D_Init();
     if (HI_SUCCESS != Ret)
     {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        goto ERR_EXIT_ONE;
     }

     Ret = HI_GFX_FillRect(LayerSurface, NULL, 0xffaabbcc, HI_GFX_COMPOPT_NONE);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_LOG_PrintErrCode(HI_FAILURE);
         goto ERR_EXIT_ONE;
     }

     HI_GFX_Memset(&stBltOpt, 0, sizeof(HI_GFX_BLTOPT_S));
     stBltOpt.EnableScale = HI_TRUE;
     Ret = HI_GFX_Blit(DecSurface, NULL, LayerSurface, NULL, &stBltOpt);
     if (HI_SUCCESS != Ret)
     {
         HI_GFX_LOG_PrintErrCode(HI_FAILURE);
         goto ERR_EXIT_ONE;
     }

     Ret = GFX_RefreshLayer(LayerSurface, GfxSupport4k);
     if (HI_SUCCESS != Ret){
         HI_GFX_LOG_PrintErrCode(HI_FAILURE);
         goto ERR_EXIT_ONE;
     }

     if (HI_GFX_INVALID_HANDLE != LayerSurface)
     {/** anition should need, gs_LayerSurface need, kernel can free this mem **/
        //HI_GFX_Free((HI_CHAR*)LayerSurface);
     }

     gs_LayerSurface = LayerSurface;

     HI_GFX_LOG_FuncExit();
     return HI_SUCCESS;

ERR_EXIT_ONE:

     if (HI_GFX_INVALID_HANDLE != LayerSurface)
     {
        GFX_DestroyLayer(LayerSurface);
        HI_GFX_Free((HI_CHAR*)LayerSurface);
     }

     HI_GFX_LOG_PrintErrCode(HI_FAILURE);

     return HI_FAILURE;
}

static HI_S32 GFX_CreateLayer(HI_GFX_LAYER_ID_E enLayerID, HI_BOOL Support4KLogo, HI_GFX_PF_E enPixelFormat, HI_HANDLE *pLayerSurface)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_HANDLE hSurface = 0;
    HI_LOGO_SURFACE_S *pstSurface = NULL;
    CHECK_POINT_NULL(pLayerSurface);
    HI_GFX_LOG_FuncEnter();

    if (HI_GFX_LAYER_HD_0 == enLayerID)
    {
        hSurface = (HI_HANDLE)HI_GFX_Malloc(sizeof(HI_LOGO_SURFACE_S),"hd-surface-handle");
    }
    else
    {
        hSurface = (HI_HANDLE)HI_GFX_Malloc(sizeof(HI_LOGO_SURFACE_S),"sd-surface-handle");
    }

    if (0 == hSurface)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }
    HI_GFX_Memset((HI_VOID*)hSurface,0x0,sizeof(HI_LOGO_SURFACE_S));

    *pLayerSurface = hSurface;

    pstSurface = (HI_LOGO_SURFACE_S*)hSurface;
    pstSurface->enLayerID = enLayerID;
    pstSurface->enPixelFormat = enPixelFormat;

    if (HI_GFX_LAYER_HD_0 == enLayerID)
    {
         Ret = GfxOpenLayer(pstSurface,Support4KLogo);
    }
    else
    {
         GfxGetLayerInfo(pstSurface);
    }

    if (HI_SUCCESS != Ret)
    {
         HI_GFX_Free((HI_CHAR*)pstSurface);
         return HI_FAILURE;
    }

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}


static HI_S32 GfxOpenLayer(HI_LOGO_SURFACE_S *pstGfxSurface, HI_BOOL Support4KLogo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_S32 s32DataId = 0;
    HI_S32 s32GPId   = 0;
    HI_FB_COLOR_FMT_E enLayerFmt;
    HI_DISP_DISPLAY_INFO_S stInfo = {0};
    HI_GFX_DISPLAY_INFO_S *pDisplayInfo = NULL;
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL(pstGfxSurface);

    s32DataId = GfxLayerIdToGfxId(pstGfxSurface->enLayerID);
    if (HI_FAILURE == s32DataId)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    s32GPId  = GfxLayerIdToGpId(pstGfxSurface->enLayerID);
    if (HI_FAILURE == s32GPId)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (s32DataId >= HI_GFX_LAYER_MAXCOUNT)
    {
       HI_GFX_DBG_PrintInt(s32DataId);
       HI_GFX_LOG_PrintErrCode(HI_FAILURE);
       return HI_FAILURE;
    }
    pDisplayInfo = gs_stDisplayInfo + s32DataId;

    Ret = GfxGetDisplayInfo(pstGfxSurface,pDisplayInfo, Support4KLogo);
    if (Ret != HI_SUCCESS)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    GfxLayerToHifbFmt(pstGfxSurface->enPixelFormat, &enLayerFmt);

    OPTM_GfxInit            ();
    OPTM_GfxOpenLayer       (s32DataId);
    OPTM_GfxSetLayerDataFmt (s32DataId,  (enLayerFmt));
    OPTM_GfxSetLayerStride  (s32DataId,  (pDisplayInfo->u32Stride));
    OPTM_GfxSetLayerAddr    (s32DataId,  (pDisplayInfo->u32ScreenAddr));
    OPTM_GfxSetLayerAlpha   (s32DataId,  (HIFB_ALPHA_S*)(&(pDisplayInfo->stAlpha)));
    OPTM_GfxSetLayerRect    (s32DataId,  (const HIFB_RECT*)(&(pDisplayInfo->stInRect)));
    OPTM_GfxSetGpRect       (s32GPId,    (const HIFB_RECT*)(&(pDisplayInfo->stInRect)));
    OPTM_GfxSetDispFMTSize  (s32GPId,    (const HI_RECT_S*)(&(pDisplayInfo->stOutRect)));
    OPTM_GpInitFromDisp     (s32GPId, Support4KLogo);

    if (HI_FALSE == HIFB_ADP_GetIsGfxWorkAtWbc())
    {
       HI_GFX_LOG_FuncExit();
       return HI_SUCCESS;
    }

    HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &stInfo);
    if (stInfo.stFmtResolution.s32Width > WBC_TC_WIDTH)
    {
        OPTM_GFX_SetTCFlag(HI_TRUE);
    }
    HIFB_WBC_InitLayer     (HI_GFX_LAYER_SD_0);
    OPTM_GpInitFromDisp    (OPTM_GFX_GP_1, Support4KLogo);

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 GfxLayerIdToGfxId(HI_GFX_LAYER_ID_E eLayerID)
{
    HI_GFX_LOG_FuncEnter();
    if (HI_GFX_LAYER_HD_0 == eLayerID)
    {
        HI_GFX_LOG_FuncExit();
        return 0;
    }
    else if(HI_GFX_LAYER_HD_1 == eLayerID)
    {
        HI_GFX_LOG_FuncExit();
        return 1;
    }
    else if(HI_GFX_LAYER_HD_2 == eLayerID)
    {
        HI_GFX_LOG_FuncExit();
        return 2;
    }
    else if(HI_GFX_LAYER_HD_3 == eLayerID)
    {
        HI_GFX_LOG_FuncExit();
        return 3;
    }
    else if(HI_GFX_LAYER_SD_0 == eLayerID)
    {
        HI_GFX_LOG_FuncExit();
        return 4;
    }
    else if(HI_GFX_LAYER_SD_1 == eLayerID)
    {
        HI_GFX_LOG_FuncExit();
        return 5;
    }
    else
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }
}


static HI_S32 GfxLayerIdToGpId(HI_GFX_LAYER_ID_E eLayerID)
{
    HI_GFX_LOG_FuncEnter();
    if (eLayerID <= HI_GFX_LAYER_HD_3)
    {
        HI_GFX_LOG_FuncExit();
        return 0;
    }
    else if (eLayerID <= HI_GFX_LAYER_SD_1)
    {
        HI_GFX_LOG_FuncExit();
        return 1;
    }
    else
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }
}

static HI_S32 GfxGetDisplayInfo(HI_LOGO_SURFACE_S *pstSurface,HI_GFX_DISPLAY_INFO_S *pDisplayInfo, HI_BOOL Support4KLogo)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_U32 u32BufferSize = 0;
    HI_DISP_DISPLAY_INFO_S pstInfo = {0};
    HI_RECT stOutRect = {0};
    HI_GFX_LOG_FuncEnter();
    CHECK_POINT_NULL(pstSurface);
    CHECK_POINT_NULL(pDisplayInfo);

    if (pstSurface->enLayerID <= HI_GFX_LAYER_HD_3)
    {
        HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_1, &pstInfo);
    }
    else
    {
        HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &pstInfo);
    }

    GfxWinReviseOutRect(&pstInfo.stVirtaulScreen,      \
                        &pstInfo.stOffsetInfo,         \
                        &pstInfo.stFmtResolution,      \
                        &pstInfo.stPixelFmtResolution, \
                        &pstInfo.stVirtaulScreen,      \
                        (HI_RECT_S*)(&stOutRect));

    HI_GFX_Memset(pDisplayInfo, 0, sizeof(HI_GFX_DISPLAY_INFO_S));

    pDisplayInfo->stAlpha.bAlphaEnable  = HI_TRUE;
    pDisplayInfo->stAlpha.bAlphaChannel = HI_FALSE;
    pDisplayInfo->stAlpha.u8Alpha0      = 0x00;
    pDisplayInfo->stAlpha.u8Alpha1      = 0xff;
    pDisplayInfo->stAlpha.u8GlobalAlpha = 0xff;

    pDisplayInfo->stInRect.x  = pstInfo.stVirtaulScreen.s32X;
    pDisplayInfo->stInRect.y  = pstInfo.stVirtaulScreen.s32Y;
    pDisplayInfo->stInRect.w  = pstInfo.stVirtaulScreen.s32Width;
    pDisplayInfo->stInRect.h  = pstInfo.stVirtaulScreen.s32Height;
    pDisplayInfo->stOutRect.x  = stOutRect.x;
    pDisplayInfo->stOutRect.y  = stOutRect.y;
    pDisplayInfo->stOutRect.w  = stOutRect.w;
    pDisplayInfo->stOutRect.h  = stOutRect.h;
    pstSurface->stRect.x  = pDisplayInfo->stInRect.x;
    pstSurface->stRect.y  = pDisplayInfo->stInRect.y;
    pstSurface->stRect.w  = pDisplayInfo->stInRect.w;
    pstSurface->stRect.h  = pDisplayInfo->stInRect.h;

    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintInt(pDisplayInfo->stInRect.x);
    HI_GFX_DBG_PrintInt(pDisplayInfo->stInRect.y);
    HI_GFX_DBG_PrintInt(pDisplayInfo->stInRect.w);
    HI_GFX_DBG_PrintInt(pDisplayInfo->stInRect.h);
    HI_GFX_DBG_PrintInt(pDisplayInfo->stOutRect.x);
    HI_GFX_DBG_PrintInt(pDisplayInfo->stOutRect.y);
    HI_GFX_DBG_PrintInt(pDisplayInfo->stOutRect.w);
    HI_GFX_DBG_PrintInt(pDisplayInfo->stOutRect.h);
    HI_GFX_DBG_PrintInfo("this outrect should equal to logo to app's src rect");
    HI_GFX_DBG_PrintInfo("logo virtual screen and offset should equal to app's");
    HI_GFX_DBG_PrintInfo("============================================================================");

    if (HI_TRUE == Support4KLogo)
    {
        pDisplayInfo->stInRect.x  = 0;
        pDisplayInfo->stInRect.y  = 0;
        pDisplayInfo->stInRect.w  = pstInfo.stFmtResolution.s32Width;
        pDisplayInfo->stInRect.h  = pstInfo.stFmtResolution.s32Height;
        pDisplayInfo->stOutRect.x = pDisplayInfo->stInRect.x;
        pDisplayInfo->stOutRect.y = pDisplayInfo->stInRect.y;
        pDisplayInfo->stOutRect.w = pDisplayInfo->stInRect.w;
        pDisplayInfo->stOutRect.h = pDisplayInfo->stInRect.h;
        pstSurface->stRect.x  = stOutRect.x;
        pstSurface->stRect.y  = stOutRect.y;
        pstSurface->stRect.w  = stOutRect.w;
        pstSurface->stRect.h  = stOutRect.h;

        HI_GFX_DBG_PrintInt(pDisplayInfo->stInRect.x);
        HI_GFX_DBG_PrintInt(pDisplayInfo->stInRect.y);
        HI_GFX_DBG_PrintInt(pDisplayInfo->stInRect.w);
        HI_GFX_DBG_PrintInt(pDisplayInfo->stInRect.h);
        HI_GFX_DBG_PrintInt(pDisplayInfo->stOutRect.x);
        HI_GFX_DBG_PrintInt(pDisplayInfo->stOutRect.y);
        HI_GFX_DBG_PrintInt(pDisplayInfo->stOutRect.w);
        HI_GFX_DBG_PrintInt(pDisplayInfo->stOutRect.h);
    }

    if ((pDisplayInfo->stInRect.w < CONFIG_GFX_MINWIDTH) || (pDisplayInfo->stInRect.w > CONFIG_GFX_MAXWIDTH))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if ((pDisplayInfo->stInRect.h < CONFIG_GFX_MINHEIGHT) || (pDisplayInfo->stInRect.h > CONFIG_GFX_MAXHEIGHT))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    pstSurface->u32Width[0]     = pDisplayInfo->stInRect.w;
    pstSurface->u32Height[0]    = pDisplayInfo->stInRect.h;
    switch (pstSurface->enPixelFormat)
    {
        case HI_GFX_PF_8888:
             pstSurface->u32Stride[0] = (pDisplayInfo->stInRect.w * 4 + 0xf) & 0xfffffff0;
             break;
        case HI_GFX_PF_0888:
             pstSurface->u32Stride[0] = (pDisplayInfo->stInRect.w * 3 + 0xf) & 0xfffffff0;
             break;
        case HI_GFX_PF_565:
        case HI_GFX_PF_1555:
             pstSurface->u32Stride[0] = (pDisplayInfo->stInRect.w * 2 + 0xf) & 0xfffffff0;
             break;
        default:
             break;
    }

#ifdef CONFIG_GFX_DOUBLE_BUFFER_SUPPORT
    u32BufferSize = pstSurface->u32Stride[0] * pDisplayInfo->stInRect.h * CONFIG_GFX_LAYER_BUF_NUM;
#else
    u32BufferSize = pstSurface->u32Stride[0] * pDisplayInfo->stInRect.h;
#endif
    if (pstSurface->enLayerID <= HI_GFX_LAYER_HD_3)
    {
        pstSurface->pPhyAddr[0] = (HI_CHAR*)HI_GFX_RESERVE_Malloc(u32BufferSize,DISPLAY_BUFFER_HD);
    }
    else
    {
        pstSurface->pPhyAddr[0] = (HI_CHAR*)HI_GFX_RESERVE_Malloc(u32BufferSize,DISPLAY_BUFFER_SD);
    }

    pstSurface->InUsingDispIndex = 0;
    pstSurface->bUseLayerSurface = HI_TRUE;
#ifdef CONFIG_GFX_DOUBLE_BUFFER_SUPPORT
    pstSurface->pPhyAddr[1] = (HI_CHAR*)(pstSurface->pPhyAddr[0] + u32BufferSize / CONFIG_GFX_LAYER_BUF_NUM);
#endif
    if (HI_SUCCESS != Ret)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    pDisplayInfo->u32Stride     = pstSurface->u32Stride[0];
    pDisplayInfo->u32ScreenAddr = (HI_U32)pstSurface->pPhyAddr[0];

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_VOID GfxWinReviseOutRect(const HI_RECT_S *tmp_virtscreen,          \
                            const HI_DRV_DISP_OFFSET_S *stOffsetInfo, \
                            const HI_RECT_S *stFmtResolution,         \
                            const HI_RECT_S *stPixelFmtResolution,    \
                            HI_RECT_S *stToBeRevisedRect,             \
                            HI_RECT_S *stRevisedRect)
{
    HI_U32 width_ratio   = 0;
    HI_U32 height_ratio  = 0;
    HI_U32 zmeDestWidth  = 0;
    HI_U32 zmeDestHeight = 0;
    HI_DRV_DISP_OFFSET_S tmp_offsetInfo;
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL_UNRETURN(tmp_virtscreen);
    CHECK_POINT_NULL_UNRETURN(stOffsetInfo);
    CHECK_POINT_NULL_UNRETURN(stFmtResolution);
    CHECK_POINT_NULL_UNRETURN(stPixelFmtResolution);
    CHECK_POINT_NULL_UNRETURN(stToBeRevisedRect);
    CHECK_POINT_NULL_UNRETURN(stRevisedRect);

    tmp_offsetInfo = *stOffsetInfo;

    if ( (stFmtResolution->s32Width * 2) == stPixelFmtResolution->s32Width)
    {
        tmp_offsetInfo.u32Left  *= 2;
        tmp_offsetInfo.u32Right *= 2;
    }

    zmeDestWidth =  (stPixelFmtResolution->s32Width  - tmp_offsetInfo.u32Left - tmp_offsetInfo.u32Right);
    zmeDestHeight = (stPixelFmtResolution->s32Height - tmp_offsetInfo.u32Top  - tmp_offsetInfo.u32Bottom);

    if ((0 == tmp_virtscreen->s32Width) || (0 == tmp_virtscreen->s32Height))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return;
    }
    width_ratio  = zmeDestWidth  * 100 /(tmp_virtscreen->s32Width);
    height_ratio = zmeDestHeight * 100 /(tmp_virtscreen->s32Height);

    if (tmp_virtscreen->s32Width != stToBeRevisedRect->s32Width)
    {
        stRevisedRect->s32Width = (stToBeRevisedRect->s32Width * width_ratio) / 100;
    }
    else
    {
        stRevisedRect->s32Width = zmeDestWidth;
    }

    if (tmp_virtscreen->s32Height != stToBeRevisedRect->s32Height)
    {
        stRevisedRect->s32Height = (stToBeRevisedRect->s32Height * height_ratio) / 100;
    }
    else
    {
        stRevisedRect->s32Height = zmeDestHeight;
    }

    stRevisedRect->s32X = (stToBeRevisedRect->s32X * width_ratio) / 100  + tmp_offsetInfo.u32Left;
    stRevisedRect->s32Y = (stToBeRevisedRect->s32Y  * height_ratio) / 100 + tmp_offsetInfo.u32Top;

    stRevisedRect->s32X      = GfxParaAlign(stRevisedRect->s32X, 2);
    stRevisedRect->s32Y      = GfxParaAlign(stRevisedRect->s32Y , 2);
    stRevisedRect->s32Width  = GfxParaAlign(stRevisedRect->s32Width, 2);
    stRevisedRect->s32Height = GfxParaAlign(stRevisedRect->s32Height, 2);

    HI_GFX_LOG_FuncExit();
    return;
}

static HI_U32 GfxParaAlign(HI_U32 x, HI_U32 a)
{
    HI_GFX_LOG_FuncEnter();
    if (!a)
    {
        HI_GFX_LOG_FuncExit();
        return x;
    }
    else
    {
        HI_GFX_LOG_FuncExit();
        return ( (( x + (a-1) ) / a ) * a);
    }
}

static inline HI_VOID GfxLayerToHifbFmt(HI_GFX_PF_E SrcFmt,HI_FB_COLOR_FMT_E *DstFmt)
{
    HI_GFX_LOG_FuncEnter();
    switch(SrcFmt)
    {
        case HI_GFX_PF_1555:
            *DstFmt = HI_FB_FMT_ARGB1555;
            break;
        case HI_GFX_PF_565:
            *DstFmt = HI_FB_FMT_RGB565;
            break;
        case HI_GFX_PF_8888:
            *DstFmt = HI_FB_FMT_ARGB8888;
            break;
        case HI_GFX_PF_0888:
            *DstFmt = HI_FB_FMT_RGB888;
            break;
        default:
            *DstFmt = HI_FB_FMT_ARGB8888;
            break;
    }
    HI_GFX_LOG_FuncExit();
    return;
}

static inline HI_VOID GfxGetLayerInfo(HI_LOGO_SURFACE_S *pstGfxSurface)
{
    HIFB_WBC_DATA_S stWbcInfo;
    HI_DISP_DISPLAY_INFO_S pstInfo;
    HI_RECT stOutRect = {0};
    HI_GFX_LOG_FuncEnter();

    HI_GFX_Memset(&stWbcInfo, 0x0, sizeof(stWbcInfo));
    HI_GFX_Memset(&pstInfo, 0x0, sizeof(pstInfo));

    HIFB_WBC_BOOT_GetWbcInfo(&stWbcInfo);

    HI_DISP_GetDisplayInfo(HI_DRV_DISPLAY_0, &pstInfo);
    GfxWinReviseOutRect(&pstInfo.stVirtaulScreen,      \
                        &pstInfo.stOffsetInfo,         \
                        &pstInfo.stFmtResolution,      \
                        &pstInfo.stPixelFmtResolution, \
                        &pstInfo.stVirtaulScreen,      \
                        (HI_RECT_S*)(&stOutRect));

    pstGfxSurface->stRect.x     = 0;
    pstGfxSurface->stRect.y     = 0;
    pstGfxSurface->stRect.w     = stOutRect.w;
    pstGfxSurface->stRect.h     = stOutRect.h;
    pstGfxSurface->u32Width[0]  = stOutRect.w;
    pstGfxSurface->u32Height[0] = stOutRect.h;

    pstGfxSurface->u32Stride[0] = stWbcInfo.u32Stride;
    pstGfxSurface->pPhyAddr[0]  = (HI_CHAR*)stWbcInfo.u32ReadBufAddr;

    pstGfxSurface->InUsingDispIndex = 0;
    pstGfxSurface->bUseLayerSurface = HI_TRUE;
#ifdef CONFIG_GFX_DOUBLE_BUFFER_SUPPORT
    pstGfxSurface->pPhyAddr[1] = (HI_CHAR*)stWbcInfo.u32ReadBufAddr;
#endif

    HI_GFX_DBG_PrintInfo("============================================================================");
    HI_GFX_DBG_PrintInt(pstGfxSurface->stRect.x);
    HI_GFX_DBG_PrintInt(pstGfxSurface->stRect.y);
    HI_GFX_DBG_PrintInt(pstGfxSurface->stRect.w);
    HI_GFX_DBG_PrintInt(pstGfxSurface->stRect.h);
    HI_GFX_DBG_PrintUInt(pstGfxSurface->u32Width[0]);
    HI_GFX_DBG_PrintUInt(pstGfxSurface->u32Height[0]);
    HI_GFX_DBG_PrintUInt(pstGfxSurface->u32Stride[0]);
    HI_GFX_DBG_PrintUInt(stWbcInfo.u32ReadBufAddr);
    HI_GFX_DBG_PrintInfo("this outrect should equal to logo to app's src rect");
    HI_GFX_DBG_PrintInfo("logo virtual screen and offset should equal to app's");
    HI_GFX_DBG_PrintInfo("============================================================================");

    HI_GFX_LOG_FuncExit();
    return;
}

static HI_S32 GFX_DestroyLayer(HI_HANDLE hLayerSurface)
{
    HI_S32 DataId = 0;
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hLayerSurface;
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL(pstSurface);

    DataId = GfxLayerIdToGfxId(pstSurface->enLayerID);
    if (HI_FAILURE == DataId)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    OPTM_GfxCloseLayer(DataId);

    if (0 != pstSurface->pPhyAddr[0])
    {/** not release just ok **/
        //HI_DRV_PDM_ReleaseReserveMem((HI_U32)pstSurface->pPhyAddr[0]);
    }

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 GFX_RefreshLayer(HI_HANDLE hLayerSurface, HI_BOOL Support4KLogo)
{
    HI_S32 DataId = 0;
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)hLayerSurface;
    HI_GFX_LOG_FuncEnter();

    CHECK_POINT_NULL(pstSurface);

    DataId = GfxLayerIdToGfxId(pstSurface->enLayerID);
    if (HI_FAILURE == DataId)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (pstSurface->InUsingDispIndex < CONFIG_GFX_PIXELDATA_NUM)
    {
        OPTM_GfxSetLayerAddr(DataId, (HI_U32)pstSurface->pPhyAddr[pstSurface->InUsingDispIndex]);
        HI_GFX_DBG_PrintInfo("============================================================================");
        HI_GFX_DBG_PrintInfo("display address");
        HI_GFX_DBG_PrintUInt(pstSurface->InUsingDispIndex);
        HI_GFX_DBG_PrintVoid(pstSurface->pPhyAddr[pstSurface->InUsingDispIndex]);
        HI_GFX_DBG_PrintInfo("============================================================================");
    }

    OPTM_GfxSetEnable   (DataId, HI_TRUE);
    OPTM_GfxUpLayerReg  (DataId);

    if (HI_FALSE == HIFB_ADP_GetIsGfxWorkAtWbc())
    {
       HI_GFX_LOG_FuncExit();
       return HI_SUCCESS;
    }

    HIFB_WBC_BOOT_ReFresh   (Support4KLogo);
    OPTM_GfxUpLayerReg      (HI_GFX_LAYER_SD_0);

    HI_GFX_LOG_FuncExit();
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : HI_GFX_GetLayerSurface
* description   : get layer surface
                  CNcomment:获取layer surface, 要是有帧切换就要重新获取一次 CNend\n
* param[in]     : pSurface        CNcomment: layer surface CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_GetLayerSurface(HI_HANDLE *pSurface)
{
    HI_LOGO_SURFACE_S *pstSurface = (HI_LOGO_SURFACE_S*)gs_LayerSurface;
    HI_GFX_UNF_FuncEnter();

    if ((NULL == pSurface) || (NULL == pstSurface))
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

    if (HI_GFX_INVALID_HANDLE == gs_LayerSurface)
    {
        HI_GFX_LOG_PrintErrCode(HI_FAILURE);
        return HI_FAILURE;
    }

#ifdef CONFIG_GFX_DOUBLE_BUFFER_SUPPORT
    if (1 == pstSurface->InUsingDispIndex)
    {
        pstSurface->InUsingDispIndex = 0;
    }
    else
    {
        pstSurface->InUsingDispIndex++;
    }
#endif

    *pSurface = gs_LayerSurface;

    HI_GFX_UNF_FuncExit();
    return HI_SUCCESS;
}

/***************************************************************************************
* func          : HI_GFX_RefreshLayer
* description   : refresh layer
                  CNcomment: 刷新显示 CNend\n
* param[in]     : hSurface        CNcomment: layer surface CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_RefreshLayer(HI_HANDLE hSurface)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_GFX_UNF_FuncEnter();
    Ret = GFX_RefreshLayer(hSurface, HI_FALSE);
    HI_GFX_UNF_FuncExit();
    return Ret;
}
