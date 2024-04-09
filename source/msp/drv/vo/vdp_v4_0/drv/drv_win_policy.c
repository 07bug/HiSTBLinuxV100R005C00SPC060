/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_disp_bufcore.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2014/04/30
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "drv_win_policy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define AUTO_OUTPUT_NUM  4

HI_S32 WinParamAlignUp(HI_S32 s32X, HI_U32 u32A)
{
    if (0 == u32A)
    {
        return s32X;
    }
    else
    {
        return ( (( s32X + (u32A - 1) ) / u32A ) * u32A);
    }
}

HI_S32 WinParamAlignDown(HI_S32 s32X, HI_U32 u32A)
{
    if (0 == u32A)
    {
        return s32X;
    }
    else
    {
        return (( s32X / u32A ) * u32A);
    }
}

static HI_S32 WinMultiWinOutRectPolicy(HI_RECT_S *pstRevisedRect, HI_OUT_ALIGN_S *pstOutAlign)
{
    HI_S32 s32YEndPos   = 0;
    HI_S32 s32YStartPos = 0;
    HI_S32 s32XEndPos   = 0;
    HI_S32 s32XStartPos = 0;

    HI_S32 s32UpValue   = 0;

    if (NULL == pstRevisedRect || NULL == pstOutAlign)
    {
        return HI_FAILURE;
    }

    s32XStartPos = pstRevisedRect->s32X;
    s32YStartPos = pstRevisedRect->s32Y;

    s32UpValue   = WinParamAlignUp(pstRevisedRect->s32X, pstOutAlign->u16WinOutRectXAlign);
    pstRevisedRect->s32X = s32UpValue;

    s32UpValue   = WinParamAlignUp(pstRevisedRect->s32Y, pstOutAlign->u16WinOutRectYAlign);
    pstRevisedRect->s32Y = s32UpValue;

    s32XEndPos   = s32XStartPos + pstRevisedRect->s32Width;
    pstRevisedRect->s32Width = WinParamAlignDown((s32XEndPos - pstRevisedRect->s32X), pstOutAlign->u16WinOutRectWAlign);

    s32YEndPos   = s32YStartPos + pstRevisedRect->s32Height;
    pstRevisedRect->s32Height = WinParamAlignDown((s32YEndPos - pstRevisedRect->s32Y), pstOutAlign->u16WinOutRectHAlign);

    return HI_SUCCESS;
}


HI_VOID WinOutRectAlign(HI_RECT_S *pstRectAlign)
{
    HI_BOOL b3Dmode = HI_FALSE;
    HI_BOOL bSDFmt = HI_FALSE;
    HI_BOOL bHDInterlace = HI_FALSE;
    HI_OUT_ALIGN_S stOutAlign = {0};

    WinGetHDDispInfo(HI_DRV_DISPLAY_1, &b3Dmode, &bSDFmt, &bHDInterlace);

    if (WinGetHDWinNum() <= 1)
    {
        if (bSDFmt)
        {
            pstRectAlign->s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_OUT_RECT_X_SD_ALIGN);
            pstRectAlign->s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_OUT_RECT_Y_SD_ALIGN);
            pstRectAlign->s32Width  = WinParamAlignUp(pstRectAlign->s32Width, HI_WIN_OUT_RECT_WIDTH_SD_ALIGN);
            pstRectAlign->s32Height = WinParamAlignUp(pstRectAlign->s32Height, HI_WIN_OUT_RECT_HEIGHT_SD_ALIGN);
        }
        else
        {
            if (b3Dmode)
            {
                pstRectAlign->s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_OUT_RECT_X_3D_ALIGN);
                pstRectAlign->s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_OUT_RECT_Y_3D_ALIGN);
                pstRectAlign->s32Width  = WinParamAlignUp(pstRectAlign->s32Width, HI_WIN_OUT_RECT_WIDTH_3D_ALIGN);
                pstRectAlign->s32Height = WinParamAlignUp(pstRectAlign->s32Height, HI_WIN_OUT_RECT_HEIGHT_3D_ALIGN);
            }
            else
            {
                HI_RECT_S stOutRectTemp = {0};

                if (bHDInterlace)
                {
                    stOutRectTemp.s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_OUT_RECT_I_X_ALIGN);
                    stOutRectTemp.s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_OUT_RECT_I_Y_ALIGN);
                    stOutRectTemp.s32Width  = WinParamAlignUp(pstRectAlign->s32Width + pstRectAlign->s32X - stOutRectTemp.s32X, HI_WIN_OUT_RECT_I_WIDTH_ALIGN);
                    stOutRectTemp.s32Height = WinParamAlignUp(pstRectAlign->s32Height + pstRectAlign->s32Y - stOutRectTemp.s32Y, HI_WIN_OUT_RECT_I_HEIGHT_ALIGN);
                }
                else
                {
                    stOutRectTemp.s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_OUT_RECT_X_ALIGN);
                    stOutRectTemp.s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_OUT_RECT_Y_ALIGN);
                    stOutRectTemp.s32Width  = WinParamAlignUp(pstRectAlign->s32Width + pstRectAlign->s32X - stOutRectTemp.s32X, HI_WIN_OUT_RECT_WIDTH_ALIGN);
                    stOutRectTemp.s32Height = WinParamAlignUp(pstRectAlign->s32Height + pstRectAlign->s32Y - stOutRectTemp.s32Y, HI_WIN_OUT_RECT_HEIGHT_ALIGN);
                }

                *pstRectAlign = stOutRectTemp;
            }
        }
    }
    else
    {
        if (bSDFmt)
        {
            stOutAlign.u16WinOutRectXAlign = HI_WIN_OUT_RECT_X_SD_ALIGN;
            stOutAlign.u16WinOutRectYAlign = HI_WIN_OUT_RECT_Y_SD_ALIGN;
            stOutAlign.u16WinOutRectWAlign = HI_WIN_OUT_RECT_WIDTH_SD_ALIGN;
            stOutAlign.u16WinOutRectHAlign = HI_WIN_OUT_RECT_HEIGHT_SD_ALIGN;
        }
        else
        {
            if (b3Dmode)
            {
                stOutAlign.u16WinOutRectXAlign = HI_WIN_OUT_RECT_X_3D_ALIGN;
                stOutAlign.u16WinOutRectYAlign = HI_WIN_OUT_RECT_Y_3D_ALIGN;
                stOutAlign.u16WinOutRectWAlign = HI_WIN_OUT_RECT_WIDTH_3D_ALIGN;
                stOutAlign.u16WinOutRectHAlign = HI_WIN_OUT_RECT_HEIGHT_3D_ALIGN;
            }
            else
            {
                if (bHDInterlace)
                {
                    stOutAlign.u16WinOutRectXAlign = HI_WIN_OUT_RECT_I_X_ALIGN;
                    stOutAlign.u16WinOutRectYAlign = HI_WIN_OUT_RECT_I_Y_ALIGN;
                    stOutAlign.u16WinOutRectWAlign = HI_WIN_OUT_RECT_I_WIDTH_ALIGN;
                    stOutAlign.u16WinOutRectHAlign = HI_WIN_OUT_RECT_I_HEIGHT_ALIGN;
                }
                else
                {
                    stOutAlign.u16WinOutRectXAlign = HI_WIN_OUT_RECT_X_ALIGN;
                    stOutAlign.u16WinOutRectYAlign = HI_WIN_OUT_RECT_Y_ALIGN;
                    stOutAlign.u16WinOutRectWAlign = HI_WIN_OUT_RECT_WIDTH_ALIGN;
                    stOutAlign.u16WinOutRectHAlign = HI_WIN_OUT_RECT_HEIGHT_ALIGN;
                }
            }
        }

        WinMultiWinOutRectPolicy(pstRectAlign, &stOutAlign);
    }

    return ;
}

HI_VOID WinInRectAlign(HI_RECT_S *pstRectAlign  , HI_U32 u32LayerNO)
{
    HI_BOOL b3Dmode = HI_FALSE;
    HI_BOOL bSDFmt = HI_FALSE;
    HI_BOOL bHDInterlace = HI_FALSE;

    WinGetHDDispInfo(HI_DRV_DISPLAY_1, &b3Dmode, &bSDFmt, &bHDInterlace);

    if (b3Dmode || ( VDP_LAYER_VID0 == u32LayerNO))
    {
        pstRectAlign->s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_IN_RECT_X_3D_ALIGN);
        pstRectAlign->s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_IN_RECT_Y_3D_ALIGN);
        pstRectAlign->s32Width  = WinParamAlignDown(pstRectAlign->s32Width, HI_WIN_IN_RECT_WIDTH_3D_ALIGN);
        pstRectAlign->s32Height = WinParamAlignDown(pstRectAlign->s32Height, HI_WIN_IN_RECT_HEIGHT_3D_ALIGN);
    }
    else
    {
        pstRectAlign->s32X = WinParamAlignDown(pstRectAlign->s32X, HI_WIN_IN_RECT_X_ALIGN);
        pstRectAlign->s32Y = WinParamAlignDown(pstRectAlign->s32Y, HI_WIN_IN_RECT_Y_ALIGN);
        pstRectAlign->s32Width  = WinParamAlignDown(pstRectAlign->s32Width, HI_WIN_IN_RECT_WIDTH_ALIGN);
        pstRectAlign->s32Height = WinParamAlignDown(pstRectAlign->s32Height, HI_WIN_IN_RECT_HEIGHT_ALIGN);
    }

    return ;
}

HI_BOOL  Win_CheckTnrLocateOnVdp(WINDOW_S *pstWin,
                                 HI_RECT_S *pstFrameSize)
{
    VIDEO_LAYER_CAPABILITY_S  stVideoLayerCap;
    HI_S32 ret = 0;

    if ((ret = pstWin->stVLayerFunc.PF_GetCapability(pstWin->u32VideoLayer, &stVideoLayerCap)))
    {
        return  HI_FALSE;
    }

    if (stVideoLayerCap.bTnrSnrDbDMDrDs)
    {
        if ((pstFrameSize->s32Width > 1920)
            && (pstFrameSize->s32Height > 1080))
        {
            return  HI_TRUE;
        }
    }

    return  HI_FALSE;

}

HI_VOID WinAdjustVideoOutRect(HI_RECT_S *pstDispRect, HI_RECT_S *pstVideoOutRect)
{
    WinOutRectAlign(pstVideoOutRect);

    if (pstDispRect->s32X > pstVideoOutRect->s32X)
    {
        pstDispRect->s32X = pstVideoOutRect->s32X;
    }

    if (pstDispRect->s32Y > pstVideoOutRect->s32Y)
    {
        pstDispRect->s32Y = pstVideoOutRect->s32Y;
    }

    if (pstDispRect->s32Width < pstVideoOutRect->s32Width)
    {
        pstDispRect->s32Width = pstVideoOutRect->s32Width;
    }

    if (pstDispRect->s32Height < pstVideoOutRect->s32Height)
    {
        pstDispRect->s32Height = pstVideoOutRect->s32Height;
    }

    return;
}

/*since we support out of window, so when out of window, the content and size of
 * the window  should be  cropped.
 */
HI_S32 Win_Revise_OutOfScreenWin_OutRect(HI_RECT_S *pstInRect,
        HI_RECT_S *pstVideoRect, HI_RECT_S *pstDispRect,
        HI_RECT_S *pstScreen,
        HI_DRV_DISP_OFFSET_S *pstOffsetRect,
        WIN_HAL_PARA_S *pstLayerPara)
{
    HI_RECT_S stInRect = *pstInRect;
    HI_RECT_S stVideoRect = *pstVideoRect;
    HI_RECT_S stDispRect = *pstDispRect;
    HI_RECT_S stOutRect = {0};
    HI_RECT_S stVideoRectOffset ;
    HI_S32 s32VaildWidth, s32VaildHeight;
    HI_S32 ix = 0, iy = 0, iw = 0, ih = 0;
    HI_S32 ox = 0, oy = 0, ow = 0, oh = 0;
    HI_BOOL bDispFlag = HI_FALSE;
    HI_RECT_S stActualResolution ;

    if (0 == stVideoRect.s32Width || 0 == stVideoRect.s32Height)
    {
        WIN_ERROR("Denominator may be zero !\n");
        return HI_FAILURE;
    }

    memset(&stActualResolution, 0x00, sizeof(stActualResolution));

    stVideoRectOffset.s32X = stDispRect.s32X - stVideoRect.s32X ;
    stVideoRectOffset.s32Y = stDispRect.s32Y - stVideoRect.s32Y;
    stVideoRectOffset.s32Width = stDispRect.s32Width - stVideoRect.s32Width;
    stVideoRectOffset.s32Height = stDispRect.s32Height - stVideoRect.s32Height;

    ix = pstInRect->s32X;
    iy = pstInRect->s32Y;
    iw = pstInRect->s32Width;
    ih = pstInRect->s32Height;

    stActualResolution.s32X = 0;
    stActualResolution.s32Y = 0;

    stActualResolution.s32Width = pstScreen->s32Width - pstOffsetRect->u32Left - pstOffsetRect->u32Right;
    stActualResolution.s32Height = pstScreen->s32Height - pstOffsetRect->u32Top - pstOffsetRect->u32Bottom;

    if (stActualResolution.s32Width < 64)
    {
        stActualResolution.s32Width = 64;
    }

    if (stActualResolution.s32Height < 64)
    {
        stActualResolution.s32Height = 64;
    }


    /*stOutRect considered the offset already, so no need to - left.*/
    stVideoRect.s32X  -= pstOffsetRect->u32Left;
    stVideoRect.s32Y  -= pstOffsetRect->u32Top;

    if (stVideoRect.s32X < 0)
    {
        s32VaildWidth = stVideoRect.s32Width  + stVideoRect.s32X;

        if (s32VaildWidth < WIN_INRECT_MIN_WIDTH)
        {
            ow = WIN_INRECT_MIN_WIDTH;
            ox = 0;
            iw = stInRect.s32Width * ow / stVideoRect.s32Width;
            ix += stInRect.s32Width - iw;

            bDispFlag = HI_TRUE;
        }
        else
        {
            // >screen size
            ow = stActualResolution.s32Width;
            if (s32VaildWidth < ow) // no full screan
            {
                ow = s32VaildWidth;
            }

            ox = 0;
            iw = stInRect.s32Width * ow / stVideoRect.s32Width;
            ix += stInRect.s32Width - stInRect.s32Width * s32VaildWidth / stVideoRect.s32Width;
        }
    }
    else if (stVideoRect.s32X < (stActualResolution.s32Width - WIN_INRECT_MIN_WIDTH))
    {
        s32VaildWidth = stVideoRect.s32Width;

        if (s32VaildWidth < WIN_INRECT_MIN_WIDTH)
        {
            ow = WIN_INRECT_MIN_WIDTH;
            ox = stVideoRect.s32X;
            iw = stInRect.s32Width;
            ix += 0;
            bDispFlag = HI_TRUE;
        }
        else
        {
            ox = stVideoRect.s32X;
            ix += 0;

            if ((s32VaildWidth + ox) > stActualResolution.s32Width)
            {
                ow = stActualResolution.s32Width - stVideoRect.s32X;
                iw = stInRect.s32Width * ow / stVideoRect.s32Width;
            }
            else
            {
                ow = stVideoRect.s32Width;
                iw = stInRect.s32Width;
            }
        }
    }
    else
    {
        ow = WIN_INRECT_MIN_WIDTH;
        ox = stActualResolution.s32Width  - ow;
        iw = stInRect.s32Width * ow / stVideoRect.s32Width;
        ix += 0;
        bDispFlag = HI_TRUE;
    }


    if (stVideoRect.s32Y < 0)
    {
        s32VaildHeight = stVideoRect.s32Height + stVideoRect.s32Y;
        if (s32VaildHeight < WIN_INRECT_MIN_HEIGHT)
        {
            oy = 0;
            oh = WIN_INRECT_MIN_HEIGHT;
            ih = stInRect.s32Height * oh / stVideoRect.s32Height;
            iy += stInRect.s32Height - ih;
            bDispFlag = HI_TRUE;
        }
        else
        {
            oy = 0;
            oh = stActualResolution.s32Height;
            if (s32VaildHeight < oh)
            {
                oh = s32VaildHeight;
            }

            ih = stInRect.s32Height * oh / stVideoRect.s32Height;
            iy += stInRect.s32Height - stInRect.s32Height * s32VaildHeight / stVideoRect.s32Height;
        }
    }
    else if (stVideoRect.s32Y < (stActualResolution.s32Height - WIN_INRECT_MIN_HEIGHT))
    {
        s32VaildHeight = stVideoRect.s32Height;

        if (s32VaildHeight < WIN_INRECT_MIN_HEIGHT)
        {
            oy = stVideoRect.s32Y;
            oh = WIN_INRECT_MIN_HEIGHT;
            ih = stInRect.s32Height;
            iy += 0;
            bDispFlag = HI_TRUE;
        }
        else
        {
            oy = stVideoRect.s32Y;
            iy += 0;
            if ((s32VaildHeight + oy) > stActualResolution.s32Height)
            {
                oh = stActualResolution.s32Height - stVideoRect.s32Y;
                ih = stInRect.s32Height * oh / stVideoRect.s32Height;
            }
            else
            {
                oh = stVideoRect.s32Height;
                ih = stInRect.s32Height;
            }
        }
    }
    else
    {
        oh = WIN_INRECT_MIN_HEIGHT;
        oy = stActualResolution.s32Height - oh;
        ih = stInRect.s32Height * oh / stVideoRect.s32Height;
        iy += 0;
        bDispFlag = HI_TRUE;
    }

    ox  += pstOffsetRect->u32Left;
    oy  += pstOffsetRect->u32Top;

    /* pstInRect in fact is the output of vpss(zme,dei,crop dnr)
     * it does not confirm to  the align limit of inrect.
     * If we give a wrong use, and make a wrong align,
     * there will be no consistency bettween GFX and VIDEO, and the backgroud color will appears.
     */

    pstDispRect->s32X = ox + stVideoRectOffset.s32X;
    pstDispRect->s32Y = oy + stVideoRectOffset.s32Y;
    if (pstDispRect->s32X < 0)
    {
        pstDispRect->s32X = 0;
    }
    if (pstDispRect->s32Y < 0)
    {
        pstDispRect->s32Y = 0;
    }

    pstDispRect->s32Width = ow + stVideoRectOffset.s32Width;
    pstDispRect->s32Height = oh + stVideoRectOffset.s32Height;

    pstInRect->s32X = ix ;
    pstInRect->s32Y = iy ;
    pstInRect->s32Width = iw ;
    pstInRect->s32Height = ih ;

    WinInRectAlign(pstInRect, pstLayerPara->u32LayerNO);

    stOutRect.s32X = ox;
    stOutRect.s32Y = oy;
    stOutRect.s32Width  = ow;
    stOutRect.s32Height = oh;
    WinAdjustVideoOutRect(pstDispRect, &stOutRect);

    *pstVideoRect = stOutRect;

    return bDispFlag;
}


HI_VOID Win_Policy_GetPQDegradingConfigFromTEE(HI_BOOL bTEEMode,
        HI_RECT_S *pstInRect,
        HI_RECT_S *pstOutRect,
        HI_U32    u32VideoLayer,
        HI_RECT_S *pstFrameIntermediateRect,
        HI_BOOL   *pbHdcpDegradePQ,
        HI_RECT_S *pstHdcpIntermediateRect)
{
    if ((VDP_LAYER_VID0 != u32VideoLayer)
        || (HI_FALSE == bTEEMode)
        || ((pstFrameIntermediateRect->s32X == pstInRect->s32X)
            && (pstFrameIntermediateRect->s32Y == pstInRect->s32Y)
            && (pstFrameIntermediateRect->s32Width == pstInRect->s32Width)
            && (pstFrameIntermediateRect->s32Height == pstInRect->s32Height))
        || ((INVALID_INTERMEDIARect == pstFrameIntermediateRect->s32Width)
            || (INVALID_INTERMEDIARect == pstFrameIntermediateRect->s32Height))
            || ((MUTE_INTERMEDIARect == pstFrameIntermediateRect->s32Width)
            || (MUTE_INTERMEDIARect == pstFrameIntermediateRect->s32Height))
        || (0 == pstFrameIntermediateRect->s32Width)
        || (0 == pstFrameIntermediateRect->s32Height)
       )
    {

        pstHdcpIntermediateRect->s32X      = 0;
        pstHdcpIntermediateRect->s32Y      = 0;
        pstHdcpIntermediateRect->s32Width  = 0;
        pstHdcpIntermediateRect->s32Height = 0;

        *pbHdcpDegradePQ = HI_FALSE;
    }
    else
    {
        *pstHdcpIntermediateRect = *pstFrameIntermediateRect;
        *pbHdcpDegradePQ = HI_TRUE;
    }

    return;
}

#ifdef CFG_HI3798CV200
/* currently unsupport hlg output type. */
static HI_DRV_DISP_OUT_TYPE_E g_enOptimalOutputList[][AUTO_OUTPUT_NUM] =
{
    /* SDR source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT},

    /* Dolby BL source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_DOLBY, HI_DRV_DISP_TYPE_HDR10, HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT},

    /* Dolby EL source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_DOLBY, HI_DRV_DISP_TYPE_HDR10, HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT},

    /* HDR10 source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_HDR10, HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT},

    /* HLG source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_HLG,HI_DRV_DISP_TYPE_HDR10,HI_DRV_DISP_TYPE_NORMAL,HI_DRV_DISP_TYPE_BUTT},

    /* SLF source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_HDR10, HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT},

    /* JTP source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT}
};
#else
static HI_DRV_DISP_OUT_TYPE_E g_enOptimalOutputList[][AUTO_OUTPUT_NUM] =
{
    /* SDR source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT},

    /* Dolby BL source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_DOLBY, HI_DRV_DISP_TYPE_HDR10, HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT},

    /* Dolby EL source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_DOLBY, HI_DRV_DISP_TYPE_HDR10, HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT},

    /* HDR10 source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_HDR10, HI_DRV_DISP_TYPE_HLG, HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT},

    /* HLG source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_HLG, HI_DRV_DISP_TYPE_HDR10, HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT},

    /* SLF source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_HDR10, HI_DRV_DISP_TYPE_HLG, HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT},

    /* JTP source optimize output type list for choose. */
    {HI_DRV_DISP_TYPE_NORMAL, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT, HI_DRV_DISP_TYPE_BUTT}
};
#endif

static HI_DRV_DISP_XDR_ENGINE_E g_enAutoFollowFirstFrameEngine[HI_DRV_VIDEO_FRAME_TYPE_BUTT] =
{
    /* SDR frame .*/
    DRV_XDR_ENGINE_SDR,

    /* Dolby BL frame , NOT support this mode currently.*/
    DRV_XDR_ENGINE_BUTT,

    /* Dolby EL frame , NOT support this mode currently.*/
    DRV_XDR_ENGINE_BUTT,

    /* HDR10 frame .*/
    DRV_XDR_ENGINE_HDR10,

    /* HLG frame .*/
    DRV_XDR_ENGINE_HLG,

    /* SLF frame .*/
    DRV_XDR_ENGINE_SLF,

    /* JTP frame .*/
    DRV_XDR_ENGINE_BUTT,
};

static HI_BOOL WinOutputTypeAndSinkCapMatch(HI_DRV_DISP_OUT_TYPE_E enOutput,
        HI_DRV_DISP_SINK_CAPABILITY_S  *pstSinkCap)
{
    HI_BOOL bMatch = HI_FALSE;

    switch (enOutput)
    {
        case HI_DRV_DISP_TYPE_NORMAL:
            bMatch = HI_TRUE;
            break;
        case HI_DRV_DISP_TYPE_DOLBY:
            if (pstSinkCap->bDolbySupport)
            {
                bMatch = HI_TRUE;
            }
            break;
        case HI_DRV_DISP_TYPE_HDR10:
            if (pstSinkCap->bHdr10Support)
            {
                bMatch = HI_TRUE;
            }
            break;
        case HI_DRV_DISP_TYPE_HLG:
            if (pstSinkCap->bHlgSupport)
            {
                bMatch = HI_TRUE;
            }
            break;
        default:
            HI_ERR_WIN("Unsupport output type under Auto mode!outType->[%d]\n", enOutput);
            break;
    }

    return bMatch;
}

static HI_VOID WinAdjustXdrEngine(HI_DRV_DISP_XDR_ENGINE_E *penXdrEngine,
                                  DRV_DISP_XDR_HARDWARE_CAP_S *pstHardwareCap,
                                  WIN_SHARE_XDR_LIB_STATUS_S  *pstXdrLibStatus)
{
    HI_U32 u32WinNum = 0;

    u32WinNum = WinGetHDWinNum();
    if (DRV_XDR_ENGINE_BUTT <= *penXdrEngine)
    {
        *penXdrEngine = DRV_XDR_ENGINE_BUTT;
        return;
    }

    switch (*penXdrEngine)
    {
        case DRV_XDR_ENGINE_SDR:
            break;
        case DRV_XDR_ENGINE_HDR10:
            if ((!pstHardwareCap->bSupportHdr10)
                || (!pstXdrLibStatus->bExistHdr10Lib))
            {
                HI_INFO_WIN("Unsupport HDR10\n");
                *penXdrEngine = DRV_XDR_ENGINE_BUTT;
            }
            break;
        case DRV_XDR_ENGINE_HLG:
            if ((!pstHardwareCap->bSupportHlg)
                || (!pstXdrLibStatus->bExistHlgLib))
            {
                HI_INFO_WIN("Unsupport HLG\n");
                *penXdrEngine = DRV_XDR_ENGINE_BUTT;
            }
            break;
        case DRV_XDR_ENGINE_SLF:
            if ((!pstHardwareCap->bSupportSlf)
                || (!pstXdrLibStatus->bExistSlfLib))
            {
                HI_INFO_WIN("Unsupport SLF\n");
                *penXdrEngine = DRV_XDR_ENGINE_BUTT;
            }
            break;
        case DRV_XDR_ENGINE_DOLBY:
            if ((!pstHardwareCap->bSupportDolby)
                || (!pstXdrLibStatus->bExistDolbyLib)
                || (u32WinNum >= 2))
            {
                HI_INFO_WIN("Unsupport DolbyVision, bHardware->%d,bDolbylib->%d,u32WinNum->%d.\n",
                    pstHardwareCap->bSupportDolby,pstXdrLibStatus->bExistDolbyLib,u32WinNum);
                *penXdrEngine = DRV_XDR_ENGINE_BUTT;
            }
            else
            {
#ifndef VDP_DOLBY_HDR_SUPPORT
                HI_INFO_WIN("VDP_DOLBY_HDR_SUPPORT NOT Defined!.\n");
                *penXdrEngine = DRV_XDR_ENGINE_BUTT;
#endif
            }
            break;
        case DRV_XDR_ENGINE_JTP:
            if ((!pstHardwareCap->bSupportJTP)
                || (!pstXdrLibStatus->bExistJTPLib))
            {
                HI_INFO_WIN("Unsupport JTP\n");
                *penXdrEngine = DRV_XDR_ENGINE_BUTT;
            }
            break;
        default:
            break;

    }

    return;
}

static HI_S32 WinAquireEngineList(HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
                                  HI_DRV_DISP_OUT_TYPE_E    enOutType,
                                  HI_DRV_DISP_XDR_ENGINE_E    *penXdrEngineList)
{
    return DISP_GetXdrEngineList(enFrmType, enOutType, penXdrEngineList);
}

static HI_S32 WinFilterEngineList(HI_DRV_DISP_XDR_ENGINE_E *penXdrEngineList)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;
    DRV_DISP_XDR_HARDWARE_CAP_S stXdrHardwareCap = {0};
    WIN_SHARE_XDR_LIB_STATUS_S  stXdrLibStatus = {0};

    /* get hardware ability(chip type and mark). */
    s32Ret = DISP_GetXdrHardwareAbility(&stXdrHardwareCap);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("Get xdr hardware ability failed.\n");
        return s32Ret;
    }

    /* get software libs status. */
    s32Ret = WIN_SHARE_GetXdrLibStatus(&stXdrLibStatus);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("Get xdr lib status failed.\n");
        return s32Ret;
    }

    /* filter Engine(i). */
    for (u32Index = 0; u32Index < XDR_ENGINE_NUM; u32Index++)
    {
        WinAdjustXdrEngine(&penXdrEngineList[u32Index], &stXdrHardwareCap, &stXdrLibStatus);
    }

    /* return the valid engine list. */
    return HI_SUCCESS;
}

static HI_VOID WinGetXdrEngineFromList(HI_DRV_DISP_XDR_ENGINE_E *penXdrEngineList,
                                       HI_DRV_DISP_XDR_ENGINE_E enUserSetForceEngine,
                                       HI_DRV_DISP_XDR_ENGINE_E *penXdrEngine)
{
    HI_U32 u32Index = 0;

    /* get the best engine from list. */
    *penXdrEngine = penXdrEngineList[0];
    for (u32Index = 0; u32Index < XDR_ENGINE_NUM; u32Index++)
    {
        /*find the best engine. */
        if (DRV_XDR_ENGINE_BUTT != penXdrEngineList[u32Index])
        {
            *penXdrEngine = penXdrEngineList[u32Index];
            break;
        }
    }

    /* user has set force xdr engine type, need to adjust the xdr engine. */
    if (DRV_XDR_ENGINE_AUTO != enUserSetForceEngine)
    {
        for (u32Index = 0; u32Index < XDR_ENGINE_NUM; u32Index++)
        {
            /*match. */
            if (enUserSetForceEngine == penXdrEngineList[u32Index])
            {
                *penXdrEngine = penXdrEngineList[u32Index];
                break;
            }
        }

        /* enUserSetForceEngine isn't in xdr engine list, just keep the best one in list. */
        if (XDR_ENGINE_NUM == u32Index)
        {
            HI_ERR_WIN("Can not find [enUserSetForceEngine->%d] in xdr engine list,choose [XdrEngine->%d]\n", enUserSetForceEngine, *penXdrEngine);
        }
    }

    return ;
}


static HI_S32 WinPolicyChooseXdrEngine(HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
                                       HI_DRV_DISP_OUT_TYPE_E enOutType,
                                       HI_DRV_DISP_XDR_ENGINE_E *penXdrEngine)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Index = 0;

    HI_DRV_DISP_XDR_ENGINE_E enXdrEngineList[XDR_ENGINE_NUM];
    HI_DRV_DISP_XDR_ENGINE_E enUserSetForceEngine = DRV_XDR_ENGINE_BUTT;

    /* outType has been chosen as before, and cannot be auto type. */
    if ((HI_DRV_VIDEO_FRAME_TYPE_BUTT <= enFrmType)
        || (HI_DRV_DISP_TYPE_BUTT <= enOutType)
        || (HI_DRV_DISP_TYPE_AUTO == enOutType))
    {
        HI_ERR_WIN("Invalid para, FrmType->%d,OutType->%d\n", enFrmType, enOutType);
        return HI_ERR_VO_INVALID_PARA;
    }

    if (HI_NULL == penXdrEngine)
    {
        return HI_ERR_VO_NULL_PTR;
    }

    /* initial xdr engine list. */
    for (u32Index = 0; u32Index < XDR_ENGINE_NUM; u32Index++)
    {
        enXdrEngineList[u32Index] = DRV_XDR_ENGINE_BUTT;
    }

    /* aquire xdr engine list. */
    s32Ret = WinAquireEngineList(enFrmType, enOutType, &enXdrEngineList[0]);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    /* filter the xdr engine list, pick out the valid engines. */
    s32Ret = WinFilterEngineList(&enXdrEngineList[0]);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    /* get user set force engine type. */
    s32Ret = DISP_GetXdrEngineType(HI_DRV_DISPLAY_1, &enUserSetForceEngine);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    WinGetXdrEngineFromList(&enXdrEngineList[0], enUserSetForceEngine, penXdrEngine);

    return HI_SUCCESS;
}

static HI_S32 WinPolicyAutoChooseOutTypeAndXdrEngine(HI_HANDLE hWin,
                                        HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
                                        HI_DRV_DISP_OUT_TYPE_E   *penOutputType,
                                        HI_DRV_DISP_XDR_ENGINE_E *penXdrEngine)
{
    HI_U32 u32Index = 0;
    HI_HANDLE  hMaxWinHandle = HI_INVALID_HANDLE;
    HI_DRV_DISP_OUT_TYPE_E *penOptimalOutputList = HI_NULL;
    HI_DRV_DISP_SINK_CAPABILITY_S stSinkCap = {0};
    HI_DRV_DISP_XDR_ENGINE_E enTempXdrEngine = DRV_XDR_ENGINE_BUTT;

    if ((HI_NULL == penOutputType)
        || (HI_NULL == penXdrEngine))
    {
        return HI_ERR_VO_NULL_PTR;
    }

    memset((HI_VOID *)&stSinkCap, 0x0, sizeof(stSinkCap));

    /* needn't to make any policy when this is NOT the max win.  */
    WIN_SHARE_GetMaxWinHandle(&hMaxWinHandle);
    if ((HI_INVALID_HANDLE != hMaxWinHandle)
        && (hMaxWinHandle != hWin))
    {
        WIN_SHARE_GetMaxWinOutType(penOutputType);
        WinPolicyChooseXdrEngine(enFrmType,
                                 *penOutputType,
                                 penXdrEngine);
        return HI_SUCCESS;
    }

    (HI_VOID)DISP_GetSinkCapability(HI_DRV_DISPLAY_1, &stSinkCap);

    penOptimalOutputList = &g_enOptimalOutputList[enFrmType][0];

    for (u32Index = 0; u32Index < AUTO_OUTPUT_NUM; u32Index++)
    {
        /* choose the optimal output type according to sink capability and xdr engine support! */
        if (WinOutputTypeAndSinkCapMatch(penOptimalOutputList[u32Index], &stSinkCap))
        {
            (HI_VOID)WinPolicyChooseXdrEngine(enFrmType,
                                              penOptimalOutputList[u32Index],
                                              &enTempXdrEngine);
            /* find the valid xdr engine ,record both output type and engine. */
            if (DRV_XDR_ENGINE_BUTT != enTempXdrEngine)
            {
                *penOutputType = penOptimalOutputList[u32Index];
                *penXdrEngine = enTempXdrEngine;
                break;
            }
        }
    }

    if (AUTO_OUTPUT_NUM == u32Index)
    {
        /* cannot find the valid engine. */
        *penOutputType = HI_DRV_DISP_TYPE_NORMAL;
        *penXdrEngine = DRV_XDR_ENGINE_BUTT;
    }

    return HI_SUCCESS;
}

static HI_S32 WinPolicyGetAutoFollowFirstFrameEngine(HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
        HI_DRV_DISP_XDR_ENGINE_E *penXdrEngine)
{
    *penXdrEngine = g_enAutoFollowFirstFrameEngine[enFrmType];
    return HI_SUCCESS;
}

static HI_S32 WinGetXdrEngine(HI_HANDLE                 hWin,
                              HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
                              HI_DRV_DISP_OUT_TYPE_E enTempOutputType,
                              HI_DRV_DISP_OUT_TYPE_E *penOutputType,
                              HI_DRV_DISP_XDR_ENGINE_E *penXdrEngine)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if ((HI_NULL == penOutputType)
        || (HI_NULL == penXdrEngine))
    {
        return HI_ERR_VO_NULL_PTR;
    }

    if (HI_DRV_DISP_TYPE_BUTT <= enTempOutputType)
    {
        *penXdrEngine = DRV_XDR_ENGINE_BUTT;
        return HI_ERR_VO_INVALID_PARA;
    }

    *penOutputType = enTempOutputType;

    if (HI_DRV_DISP_TYPE_AUTO == enTempOutputType)
    {
        /* auto strategy. */
        return WinPolicyAutoChooseOutTypeAndXdrEngine(hWin, enFrmType, penOutputType, penXdrEngine);
    }

    if (HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME == enTempOutputType)
    {
        /* auto follow first frame strategy, aim to seamless play mix-stream. */
        return WinPolicyGetAutoFollowFirstFrameEngine(enFrmType, penXdrEngine);
    }

    /* process forced output type. */
    s32Ret = WinPolicyChooseXdrEngine(enFrmType, enTempOutputType, penXdrEngine);

    return s32Ret;
}

HI_S32 WIN_POLICY_GetOutputTypeAndEngine(HI_HANDLE hWin,
                                        HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
                                        HI_DRV_DISP_OUT_TYPE_E    *penOutputType,
                                        HI_DRV_DISP_XDR_ENGINE_E  *penXdrEngine)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_DRV_DISP_OUT_TYPE_E enTempOutType = HI_DRV_DISP_TYPE_BUTT;

    if ((HI_NULL == penOutputType)
        || (HI_NULL == penXdrEngine))
    {
        return HI_ERR_VO_NULL_PTR;
    }

    if (HI_DRV_VIDEO_FRAME_TYPE_BUTT <= enFrmType)
    {
        return HI_ERR_VO_INVALID_PARA;
    }

    s32Ret = DISP_GetDispOutput(HI_DRV_DISPLAY_1, &enTempOutType);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (HI_DRV_DISP_TYPE_BUTT <= enTempOutType)
    {
        HI_ERR_DISP("enDispOutType is invalid, forced to sdr out.\n");
        enTempOutType = HI_DRV_DISP_TYPE_NORMAL;
    }

    s32Ret = WinGetXdrEngine(hWin, enFrmType, enTempOutType, penOutputType, penXdrEngine);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_DISP("Fail to choose valid xdr engine.\n");
        *penOutputType = HI_DRV_DISP_TYPE_NORMAL;
        *penXdrEngine = DRV_XDR_ENGINE_SDR;
        return s32Ret;
    }

    /* cannot find a valid xdr engine, set sdr output and sdr engine. */
    if ((DRV_XDR_ENGINE_BUTT <= *penXdrEngine)
        || (DRV_XDR_ENGINE_AUTO >= *penXdrEngine))
    {
        HI_WARN_DISP("Cannot find a valid xdr engine.\n");
        *penOutputType = HI_DRV_DISP_TYPE_NORMAL;
        *penXdrEngine = DRV_XDR_ENGINE_SDR;
    }

    return HI_SUCCESS;
}


static HI_VOID WinOutputTypeFollowSourceType(HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
        HI_DRV_DISP_OUT_TYPE_E    *penOutputType)
{
    HI_DRV_DISP_SINK_CAPABILITY_S stSinkCap = {0};

    memset(&stSinkCap, 0x0, sizeof(stSinkCap));

    /* get sink's capbility. */
    (HI_VOID)DISP_GetSinkCapability(HI_DRV_DISPLAY_1, &stSinkCap);

    /* not support dolby/slf/jtp frame type currently. */
    switch (enFrmType)
    {
        case HI_DRV_VIDEO_FRAME_TYPE_SDR:
            *penOutputType = HI_DRV_DISP_TYPE_NORMAL;
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_HDR10:
            if (stSinkCap.bHdr10Support)
            {
                *penOutputType = HI_DRV_DISP_TYPE_HDR10;
            }
            else if (stSinkCap.bHlgSupport)
            {
                *penOutputType = HI_DRV_DISP_TYPE_HLG;
            }
            else
            {
                *penOutputType = HI_DRV_DISP_TYPE_NORMAL;
            }
            break;
        case HI_DRV_VIDEO_FRAME_TYPE_HLG:
            if (stSinkCap.bHlgSupport)
            {
                *penOutputType = HI_DRV_DISP_TYPE_HLG;
            }
            else if (stSinkCap.bHdr10Support)
            {
                *penOutputType = HI_DRV_DISP_TYPE_HDR10;
            }
            else
            {
                *penOutputType = HI_DRV_DISP_TYPE_NORMAL;
            }
            break;
        default:
            HI_ERR_WIN("Cannot support frame type->%d under 1st frame mode.\n", enFrmType);
            *penOutputType = HI_DRV_DISP_TYPE_NORMAL;
            break;
    }

    return;
}

static HI_VOID WinFixAutoFollowFirstFrmOutStatus(HI_DRV_DISP_OUT_TYPE_E *penOutType, HI_DRV_COLOR_SPACE_E *penOutColorSpace)
{
    HI_DRV_COLOR_SPACE_E   enTempOutColorSpace = HI_DRV_CS_UNKNOWN;
    HI_DRV_DISP_SINK_CAPABILITY_S stSinkCap = {0};

    /* get sink's capbility. */
    (HI_VOID)DISP_GetSinkCapability(HI_DRV_DISPLAY_1, &stSinkCap);
    switch(*penOutType)
    {
        case HI_DRV_DISP_TYPE_NORMAL:
            break;
        case HI_DRV_DISP_TYPE_HDR10:
            if (HI_FALSE == stSinkCap.bHdr10Support)
            {
                *penOutType = HI_DRV_DISP_TYPE_NORMAL;
            }
            break;
        case HI_DRV_DISP_TYPE_HLG:
            if (HI_FALSE == stSinkCap.bHlgSupport)
            {
                *penOutType = HI_DRV_DISP_TYPE_NORMAL;
            }
            break;
         default:
            HI_WARN_WIN("Invalid outType->%d under AUTO_FOLLOW_FIRST_FRM MODE!\n",*penOutType);
            break;
    }

    /* get disp status. */
    (HI_VOID)DISP_GetDisplayColorSpaceWithoutVideo(HI_DRV_DISPLAY_1, &enTempOutColorSpace);
    if (enTempOutColorSpace != *penOutColorSpace)
    {
        if ((HI_DRV_CS_BT601_YUV_LIMITED == enTempOutColorSpace)
            || (HI_DRV_CS_BT709_RGB_FULL == enTempOutColorSpace))
        {
            *penOutColorSpace = enTempOutColorSpace;
        }

        if (HI_DRV_CS_BT2020_YUV_LIMITED == *penOutColorSpace)
        {
            if (HI_FALSE == stSinkCap.bBT2020Support)
            {
                *penOutColorSpace = enTempOutColorSpace;
            }
        }
    }

    return;
}

HI_S32 WIN_POLICY_MixStreamProcess(WIN_XDR_FRAME_S *pstXdrFrame,
                                             HI_DRV_COLOR_SPACE_E enInColorSpace,
                                             HI_DRV_COLOR_SPACE_E *penOutColorSpace)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_HANDLE  hMaxWinHandle = HI_INVALID_HANDLE;
    WIN_FIRST_FRAME_STATUS_S stFirstFrmStatus;

    memset(&stFirstFrmStatus, 0x0, sizeof(stFirstFrmStatus));

    if ((HI_NULL == pstXdrFrame)
        || (HI_NULL == penOutColorSpace))
    {
        return HI_ERR_VO_NULL_PTR;
    }

    if (HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME != pstXdrFrame->enDispOutType)
    {
        return HI_SUCCESS;
    }

    s32Ret = WinGetFirstFrmOutStatus(pstXdrFrame->hWindow, &stFirstFrmStatus);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    /* follow the max win's outType and outColorSpace. */
    WIN_SHARE_GetMaxWinHandle(&hMaxWinHandle);
    if ((HI_INVALID_HANDLE != hMaxWinHandle)
        && (hMaxWinHandle != pstXdrFrame->hWindow))
    {
        WIN_SHARE_GetMaxWinOutType(&pstXdrFrame->enDispOutType);
        WIN_SHARE_GetMaxWinOutColorSpace(penOutColorSpace);

        /* need to regenerate outType  and outColorSpace when become the max win. */
        stFirstFrmStatus.bSenceChange = HI_FALSE;

        return HI_SUCCESS;
    }

    if (HI_TRUE == stFirstFrmStatus.bSenceChange)
    {
        /* adjust the output type and output colorspace when receive frame after 1st frame. */
        pstXdrFrame->enDispOutType = stFirstFrmStatus.enDispOutType;
        *penOutColorSpace = stFirstFrmStatus.enOutColorSpace;

        /* fix outType and outColorSpace when scene has changed. */
        WinFixAutoFollowFirstFrmOutStatus(&pstXdrFrame->enDispOutType, penOutColorSpace);
    }
    else
    {
        /* receive the 1st frame, record win's xdr_mix_stream attributes. */
        stFirstFrmStatus.bSenceChange = HI_TRUE;
        WinOutputTypeFollowSourceType(pstXdrFrame->stBaseFrm.enSrcFrameType,
                                      &stFirstFrmStatus.enDispOutType);

        s32Ret = DISP_GenerateFrameOutColorSpace(HI_DRV_DISPLAY_1,
                                    pstXdrFrame->stBaseFrm.enSrcFrameType,
                                    stFirstFrmStatus.enDispOutType,
                                    enInColorSpace,
                                    penOutColorSpace);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_WIN("DISP_GenerateFrameOutColorSpace Err\n");
            return s32Ret;
        }

        pstXdrFrame->enDispOutType = stFirstFrmStatus.enDispOutType;
        stFirstFrmStatus.enOutColorSpace = *penOutColorSpace;

        s32Ret = WinSetFirstFrmOutStatus(pstXdrFrame->hWindow, &stFirstFrmStatus);
    }

    return s32Ret;
}

HI_VOID WIN_POLICY_ReviseFrameHdrType(HI_DRV_VIDEO_FRAME_S *pu8TempMem)
{
#if defined(CHIP_TYPE_hi3798cv200)
    if(HI_DRV_VIDEO_FRAME_TYPE_SDR != pu8TempMem->enSrcFrameType)
    {
        pu8TempMem->enSrcFrameType = HI_DRV_VIDEO_FRAME_TYPE_SDR;
    }
#endif
    return;

}

#define PAT_M480I_NTSC_YD   0x66
#define PAT_M480I_NTSC_YD1  0x67
#define PAT_M480I_NTSC_YD2  0x68
#define PAT_M480I_NTSC_YD3  0x69

HI_VOID WIN_POLICY_RwzbProcess(HI_U32 u32Fidelity, HI_BOOL *bRWZB)
{
    if ((u32Fidelity > 0) && (u32Fidelity !=  PAT_M480I_NTSC_YD) && (u32Fidelity !=  PAT_M480I_NTSC_YD1) && (u32Fidelity !=  PAT_M480I_NTSC_YD2) && (u32Fidelity !=  PAT_M480I_NTSC_YD3))

    {
        *bRWZB = HI_TRUE;
    }
    else
    {
        *bRWZB = HI_FALSE;
    }
}
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
