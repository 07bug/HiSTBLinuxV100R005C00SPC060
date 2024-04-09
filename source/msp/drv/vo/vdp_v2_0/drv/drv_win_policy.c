
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

#define _SR_OPEN_


#ifndef _VDP_CHIP_ALG_DEAL_CONSISTENCE
static int caculate_sr_size(HI_RECT_S *pstFrameRect,
               HI_RECT_S *pstOutRect,
               HI_RECT_S *pstSrRect,
               HI_U32    u32WinNum,
               HI_BOOL *pbHorSrEnable,
               HI_BOOL *pbVerSrEnable,
               HI_RECT_S *pstFmtResolution,
               HI_BOOL bExistScaleDown,
               HI_DRV_DISP_STEREO_E enStereo)
{
    HI_CHIP_TYPE_E   enChipType;
    HI_CHIP_VERSION_E enChipVersion;

#ifndef _SR_OPEN_
    return HI_FALSE;
#endif

    /*no matter 98m or 98c, when winnum >2, sr should not opened.*/
    if ((bExistScaleDown) || (enStereo != DISP_STEREO_NONE))
    {
        return HI_FALSE;
    }

#ifndef FPGA_HIFONEB02
    /*currently,only 4k support sr.*/
    if (!((pstFmtResolution->s32Width == 3840)
           &&(pstFmtResolution->s32Height == 2160))
       )
    {
        return HI_FALSE;
    }
#endif

    if ((pstFrameRect->s32Width*2) <= pstOutRect->s32Width)
    {
        *pbHorSrEnable = HI_TRUE;
        pstSrRect->s32Width =  pstOutRect->s32Width/2;
    }

	if ((pstFrameRect->s32Height*2) <= pstOutRect->s32Height)
	{
		*pbVerSrEnable = HI_TRUE;
		pstSrRect->s32Height =  pstOutRect->s32Height/2;
	}
	else
	{
		if (pstFrameRect->s32Height == 1088 && pstOutRect->s32Height == 2160)	
		{
			*pbVerSrEnable = HI_TRUE;	
			pstSrRect->s32Height = pstOutRect->s32Height/2;
		}
	}

    /*the limit of sr is: max input size is 2k*2k,
     * if larger than this, and make a zme even in vertical direction, error happens.
     * so we should turn sr off, the recover the value.
     */
    if ((*pbVerSrEnable) || (*pbHorSrEnable))
    {
        if ((pstSrRect->s32Width > 1920)
            || (pstSrRect->s32Height > 2160)
            || !(*pbVerSrEnable && *pbHorSrEnable)
           )
        {
            *pbHorSrEnable = HI_FALSE;
            *pbVerSrEnable = HI_FALSE;
            pstSrRect->s32Width =  pstOutRect->s32Width;
            pstSrRect->s32Height =  pstOutRect->s32Height;
        }
    }

    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipVersion);

    /*when 3798m added, this branch should be opened.*/
    if (0)
    {
        if ((pstFrameRect->s32Width  > 1920) && (pstOutRect->s32Width > 1920))
        {
            *pbHorSrEnable = HI_TRUE;
            pstSrRect->s32Width =  pstOutRect->s32Width/2;
        }
    }

    return HI_SUCCESS;
}
#else

#endif

static  HI_VOID generate_FrameRect(WINDOW_S *pstWin,
                                   HI_RECT_S *pstSourceFrameRect,
                                   HI_BOOL *pbExistScaleDown)
{
    HI_DRV_VIDEO_FRAME_S *pstDispFrame = HI_NULL;
    HI_DRV_VIDEO_PRIVATE_S *pstPrivInfo = HI_NULL;

    *pbExistScaleDown = HI_FALSE;

    if (!pstWin->stBuffer.stWinBP.pstDisplay)
        goto __error;

    pstDispFrame = (HI_DRV_VIDEO_FRAME_S *)pstWin->stBuffer.stWinBP.pstDisplay->u32Data;
    if (!pstDispFrame)
        goto __error;

    pstPrivInfo = (HI_DRV_VIDEO_PRIVATE_S *)(pstDispFrame->u32Priv);
    if (!pstPrivInfo)
        goto __error;

    pstSourceFrameRect->s32X = 0;
    pstSourceFrameRect->s32Y= 0;
    if (pstDispFrame)
    {
        pstSourceFrameRect->s32Width  = pstPrivInfo->stVideoOriginalInfo.u32Width;
        pstSourceFrameRect->s32Height = pstPrivInfo->stVideoOriginalInfo.u32Height;
    }

#if 0
    if ((pstDispFrame->stLbxInfo.s32Width  < pstSourceFrameRect->s32Width)
        || (pstDispFrame->stLbxInfo.s32Height  < pstSourceFrameRect->s32Height))
    {
        *pbExistScaleDown = HI_TRUE;
    }
#endif

    pstWin->stWinInfoForDeveloper.stOringinFrameSize = *pstSourceFrameRect;
    pstWin->stWinInfoForDeveloper.bExistScaleDown_WhenRatioRevise = *pbExistScaleDown;

    return;
__error:

    pstSourceFrameRect->s32Width  = 4096;
    pstSourceFrameRect->s32Height = 2160;
    return;
}


static int pre_ScalerDistribute(HI_RECT_S *pstVpssZmeSize,
                                 HI_RECT_S *pstFinalZmeSize,
                                 HI_U32  u32WinNum,
                                 HI_BOOL *pbHorSrEnable,
                                 HI_BOOL *pbVerSrEnable,
                                 HI_BOOL  bZmeCapability,
                                 HI_BOOL  bSrCapability,
                                 HI_U32   u32LayerMAXWidth,
                                 HI_U32   u32LayerMAXHeight,
                                 HI_RECT_S *pstSourceFrameRect,
                                 HI_RECT_S *pstFmtResolution,
                                 HI_BOOL bExistScaleDown,
                                 HI_DRV_DISP_STEREO_E enStereo)
{
    HI_RECT_S stVpssZmeSize;
    HI_BOOL bHorSrEnable = HI_FALSE;
    HI_BOOL bVerSrEnable = HI_FALSE;


    stVpssZmeSize = *pstFinalZmeSize;

    /*if no zme exist, the size must be limited to the video capability.*/
    if (!bZmeCapability)
    {
        if (pstFinalZmeSize->s32Width > u32LayerMAXWidth)
        {
            pstVpssZmeSize->s32Width  = u32LayerMAXWidth;
        }

        if (pstFinalZmeSize->s32Height > u32LayerMAXHeight)
        {
            pstVpssZmeSize->s32Height = u32LayerMAXHeight;
        }

    }
    else
    {
        if (!bSrCapability)
        {
            /*if no sr, such as cv200,  should consider the video capability,
             * and  the aspect ratio should be kept.
             */
            if((pstFinalZmeSize->s32Width > u32LayerMAXWidth)||(pstFinalZmeSize->s32Height > u32LayerMAXHeight))
            {
                if (0 == pstFinalZmeSize->s32Height || 0 == pstFinalZmeSize->s32Width)
                {
                    WIN_ERROR("Denominator may be zero !\n");
                    return HI_FAILURE; 
                }
                if(u32LayerMAXWidth * pstFinalZmeSize->s32Height > u32LayerMAXHeight * pstFinalZmeSize->s32Width)
                {
                    pstVpssZmeSize->s32Width = (pstFinalZmeSize->s32Width*u32LayerMAXHeight/pstFinalZmeSize->s32Height)&HI_WIN_OUT_RECT_WIDTH_ALIGN;
                    pstVpssZmeSize->s32Height = u32LayerMAXHeight;
                }
                else
                {
                    pstVpssZmeSize->s32Height = (pstFinalZmeSize->s32Height*u32LayerMAXWidth/pstFinalZmeSize->s32Width)&HI_WIN_OUT_RECT_HEIGHT_ALIGN;
                    pstVpssZmeSize->s32Width = u32LayerMAXWidth;
                }
            }
        }
        else
        {
            /* if SR supported, to judge to  open SR or not.
             * if SR enabled, the size should be divided  into  2 parts bettween VPSS and vdp.
             */
            caculate_sr_size(pstSourceFrameRect,
                            pstFinalZmeSize,
                            &stVpssZmeSize,
                            u32WinNum,
                            &bHorSrEnable,
                            &bVerSrEnable,
                            pstFmtResolution,
                            bExistScaleDown,
                            enStereo);

            /*when sr enable ,but the 1/2 size is larger than video layer cap, do a scale down.*/
            if((stVpssZmeSize.s32Width > u32LayerMAXWidth)||(stVpssZmeSize.s32Height > u32LayerMAXHeight))
            {
                if (0 == pstFinalZmeSize->s32Height || 0 == pstFinalZmeSize->s32Width)
                {
                    WIN_ERROR("Denominator may be zero !\n");
                    return HI_FAILURE; 
                }
                /*when sr enable,but 1/2 size  larger than max, the vpss zme size should be calculated again.*/
                if(u32LayerMAXWidth * pstFinalZmeSize->s32Height > u32LayerMAXHeight * pstFinalZmeSize->s32Width)
                {
                    pstVpssZmeSize->s32Width = (pstFinalZmeSize->s32Width*u32LayerMAXHeight/pstFinalZmeSize->s32Height)&HI_WIN_OUT_RECT_WIDTH_ALIGN;
                    pstVpssZmeSize->s32Height = u32LayerMAXHeight;
                }
                else
                {
                    pstVpssZmeSize->s32Height = (pstFinalZmeSize->s32Height*u32LayerMAXWidth/pstFinalZmeSize->s32Width)&HI_WIN_OUT_RECT_HEIGHT_ALIGN;
                    pstVpssZmeSize->s32Width = u32LayerMAXWidth;
                }

                /*no matter how, sr should be disabled.*/
                bHorSrEnable = HI_FALSE;
                bVerSrEnable = HI_FALSE;
            }
            else
            {
                pstVpssZmeSize->s32Width = stVpssZmeSize.s32Width;
                pstVpssZmeSize->s32Height = stVpssZmeSize.s32Height;
            }
        }
    }

    if ((!pstVpssZmeSize->s32Height) || (!pstVpssZmeSize->s32Width))
    {
        pstVpssZmeSize->s32Width =   VIDEO_LAYER_SUPPORT_MIN_WIDTH;
        pstVpssZmeSize->s32Height =  VIDEO_LAYER_SUPPORT_MIN_HEIGHT;
    }

    pstVpssZmeSize->s32Width  &=  HI_WIN_OUT_RECT_WIDTH_ALIGN;
    pstVpssZmeSize->s32Height &=  HI_WIN_OUT_RECT_HEIGHT_ALIGN;

    *pbHorSrEnable  = bHorSrEnable;
    *pbVerSrEnable  = bVerSrEnable;

    return HI_SUCCESS;
}

/*principly, we only use vpss to zme out or in.  but video layer
 * only support a limit input size.  so in large scale zme, we should
 * do a 2-class zme: vpss and vdp both do scaler.
 */
int Win_Pre_ScalerDistribute(WINDOW_S *pstWin,
                             HI_RECT_S *pstVpssZmeSize,
                             HI_RECT_S *pstFinalZmeSize,
                             HI_U32 u32WinNum,
                             HI_BOOL *pbHorSrEnable,
                             HI_BOOL *pbVerSrEnable,
                             HI_RECT_S *pstFmtResolution,
                             HI_DRV_DISP_STEREO_E enStereo)
{
    unsigned int u32LayerSupportWidthMax = 0, u32LayerSupportHeightMax = 0;
    VIDEO_LAYER_CAPABILITY_S  stVideoLayerCap;
    HI_RECT_S stVpssZmeSize;
    HI_RECT_S stSourceFrameRect;

    HI_BOOL bZmeCapability = HI_FALSE;
    HI_BOOL bSrCapability  = HI_FALSE;
    HI_S32 ret = 0;
    HI_BOOL bExistScaleDown = HI_FALSE;

    if ((ret = pstWin->stVLayerFunc.PF_GetCapability(pstWin->u32VideoLayer,&stVideoLayerCap)))
    {
        return ret;
    }

    memset((void*)&stSourceFrameRect, 0, sizeof(HI_RECT_S));
    generate_FrameRect(pstWin, &stSourceFrameRect, &bExistScaleDown);

    bZmeCapability = stVideoLayerCap.bZme;
    bSrCapability = stVideoLayerCap.bSR;

    u32LayerSupportWidthMax = stVideoLayerCap.u32LayerWidthMax;
    u32LayerSupportHeightMax = stVideoLayerCap.u32LayerHeightMax;
    stVpssZmeSize = *pstFinalZmeSize;

    pre_ScalerDistribute(pstVpssZmeSize,
                        pstFinalZmeSize,
                        u32WinNum,
                        pbHorSrEnable,
                        pbVerSrEnable,
                        bZmeCapability,
                        bSrCapability,
                        u32LayerSupportWidthMax,
                        u32LayerSupportHeightMax,
                        &stSourceFrameRect,
                        pstFmtResolution,
                        bExistScaleDown,
                        enStereo);

    return HI_SUCCESS;
}


/*if  outrect/inrect > 2, the primary condition of sr's openning is satified.
 *but vpss does not give a size vdp want, so vdp should give a second scaler.
 */
HI_S32 post_ScalerProcess(HI_RECT_S *pstFinalDisPosition,
                        HI_RECT_S *pstV0DisPosition,
                        HI_BOOL   *pbHorSrEnable,
                        HI_BOOL   *pbVerSrEnable,
                        HI_U32    u32WinNum,
                        HI_RECT_S *pstSourceFrameRect,
                        HI_CHIP_TYPE_E   enChipType,
                        HI_BOOL bSrCapability,
                        const HI_RECT_S *pstFmtResolution,
                        HI_DRV_DISP_STEREO_E enStereo)
{

    *pbHorSrEnable = HI_FALSE;
    *pbVerSrEnable = HI_FALSE;

    if ((u32WinNum  < 2) && (enStereo == DISP_STEREO_NONE))
    {
        if ((pstSourceFrameRect->s32Width > 1920) || (pstSourceFrameRect->s32Height > 2160))
        {
            *pbHorSrEnable = HI_FALSE;
            *pbVerSrEnable = HI_FALSE;
        }
#ifndef FPGA_HIFONEB02
        else if (!((pstFmtResolution->s32Width == 3840)
           &&(pstFmtResolution->s32Height == 2160))
                )
        {
            *pbHorSrEnable = HI_FALSE;
            *pbVerSrEnable = HI_FALSE;
        }
#endif
        else
        {
            if (((pstSourceFrameRect->s32Width*2) <= pstFinalDisPosition->s32Width)
                && (bSrCapability))
            {
                *pbHorSrEnable = HI_TRUE;
            }

            if (((pstSourceFrameRect->s32Height*2) <= pstFinalDisPosition->s32Height)
                 && (bSrCapability))
            {
                *pbVerSrEnable = HI_TRUE;
            }
        }

        /*both h and vertical meets sr, then open sr, else close it.*/
        if (!(*pbHorSrEnable && *pbVerSrEnable))
        {
            *pbHorSrEnable = HI_FALSE;
            *pbVerSrEnable = HI_FALSE;
        }
    }

#ifndef _SR_OPEN_
    *pbHorSrEnable = HI_FALSE;
    *pbVerSrEnable = HI_FALSE;
#endif


    /*zme has no x/y,it's just a size , but position has x/y,
     *so we should not put them together.when SR in Vp and enabled, the position which V0 care
     *should  be relocated.
     */
    if ((HI_CHIP_TYPE_HI3798C == enChipType) || (HI_CHIP_TYPE_HI3796C == enChipType))
    {
        *pstV0DisPosition = *pstFinalDisPosition;

        if (*pbHorSrEnable)
        {
            pstV0DisPosition->s32X = pstFinalDisPosition->s32X / 2;
            pstV0DisPosition->s32Width = pstFinalDisPosition->s32Width / 2;
        }

        if (*pbVerSrEnable)
        {
            pstV0DisPosition->s32Y = pstFinalDisPosition->s32Y / 2;
            pstV0DisPosition->s32Height = pstFinalDisPosition->s32Height / 2;
        }
    }
    else
    {
        /*because SR in v0 or no SR, so  v0 positon == final position.*/
        /*98m sr is in v0, so v0 output position remain the same with cv200.*/
        *pstV0DisPosition = *pstFinalDisPosition;
    }

    pstV0DisPosition->s32X &=  HI_WIN_OUT_RECT_X_ALIGN;
    pstV0DisPosition->s32Y &=  HI_WIN_OUT_RECT_Y_ALIGN;
    pstV0DisPosition->s32Width &=  HI_WIN_OUT_RECT_WIDTH_ALIGN;
    pstV0DisPosition->s32Height &=  HI_WIN_OUT_RECT_HEIGHT_ALIGN;

    return HI_SUCCESS;
}

int Win_Post_ScalerProcess( WINDOW_S  *pstWin,
                            HI_RECT_S *pstFinalDisPosition,
                            HI_RECT_S *pstV0DisPosition,
                            HI_BOOL   *pbHorSrEnable,
                            HI_BOOL   *pbVerSrEnable,
                            HI_U32 u32WinNum,
                            HI_RECT_S *pstSourceFrameRect,
                            const HI_RECT_S *pstFmtResolution,
                            HI_DRV_DISP_STEREO_E enStereo)
{
    HI_CHIP_TYPE_E   enChipType;
    HI_CHIP_VERSION_E enChipVersion;
    VIDEO_LAYER_CAPABILITY_S  stVideoLayerCap;
    HI_BOOL bSrCapability  = HI_FALSE;
    HI_S32 ret = 0;

    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipVersion);

    if ((ret = pstWin->stVLayerFunc.PF_GetCapability(pstWin->u32VideoLayer,&stVideoLayerCap)))
    {
        return ret;
    }

    bSrCapability = stVideoLayerCap.bSR;
    post_ScalerProcess(pstFinalDisPosition,
                       pstV0DisPosition,
                       pbHorSrEnable,
                       pbVerSrEnable,
                       u32WinNum,
                       pstSourceFrameRect,
                       enChipType,
                       bSrCapability,
                       pstFmtResolution,
                       enStereo);

    return HI_SUCCESS;
}

static HI_VOID updateDci(WINDOW_S *pstWin,
                      HI_BOOL bDciEnable,
                      HI_PQ_DCI_WIN_S *pstActualDciArea)
{
    if (pstWin->enDisp == HI_DRV_DISPLAY_1)
    {
        /*this flag is not a control of dci,
         *just if dci is open ,then make a choice.
         */
        DRV_PQ_UpdateDCIWin(pstActualDciArea, bDciEnable);
    }

    /*save the value for next judgement.*/
    pstWin->stMiscInfor.stWinDciLastConfig = *pstActualDciArea;
    pstWin->stMiscInfor.bWinDciEnableLastConfig = bDciEnable;

    return;
}

HI_S32 dci_enable_policy(HI_RECT_S *pstOriginDciArea,/*vpss's effective area.*/
                         HI_RECT_S *pstV0DisPosition,/*secondary coordinate*/
                         HI_RECT_S *pstVpssGive,/*the original rect give by vpss.*/
                         HI_U32    u32WinNum,
                         HI_BOOL  *pbDciEnable,
                         HI_PQ_DCI_WIN_S *pstActualDciArea)
{
    HI_U32 u32OriginDCI_Width = 0;
    HI_U32 u32OriginDCI_Height = 0;

    HI_U32 u32SecondCoord_DCI_X_Start = 0;
    HI_U32 u32SecondCoord_DCI_X_End = 0;

    HI_U32 u32SecondCoord_DCI_Y_Start = 0;
    HI_U32 u32SecondCoord_DCI_Y_End = 0;

    *pbDciEnable = HI_FALSE;

    /*when win >=2, we only cover the window on V0, 2014-0910,
     *discussed by zk and zlling.*/
#if 0
    if (u32WinNum >= 2)
    {
        memset((void*)pstActualDciArea, 0, sizeof(HI_PQ_DCI_WIN_S));
        return HI_SUCCESS;
    }
#endif

    u32OriginDCI_Width = pstOriginDciArea->s32Width;
    u32OriginDCI_Height = pstOriginDciArea->s32Height;


    /*although 98m different with 98c, but we both use pstV0DisPosition, not final.
     * the final and v0's calculation is done in Win_Post_ScalerProcess*/
    /*secondly, caculate the new dci coordinate in the secondary coordinate.*/
    if (0 == pstVpssGive->s32Width || 0 == pstVpssGive->s32Height) 
    {
        WIN_ERROR("Denominator may be zero !\n");
        return HI_FAILURE;
    }
    u32SecondCoord_DCI_X_Start = (pstOriginDciArea->s32X * pstV0DisPosition->s32Width) / pstVpssGive->s32Width;
    u32SecondCoord_DCI_Y_Start = (pstOriginDciArea->s32Y * pstV0DisPosition->s32Height) / pstVpssGive->s32Height;

    u32SecondCoord_DCI_X_End = u32SecondCoord_DCI_X_Start  +
                (u32OriginDCI_Width *  pstV0DisPosition->s32Width) / pstVpssGive->s32Width;

    u32SecondCoord_DCI_Y_End = u32SecondCoord_DCI_Y_Start  +
         (u32OriginDCI_Height *  pstV0DisPosition->s32Height) / pstVpssGive->s32Height;

    /*3rdly, calculate the final dci in middle coordinate system.*/
    u32SecondCoord_DCI_X_Start += pstV0DisPosition->s32X;
    u32SecondCoord_DCI_X_End   += pstV0DisPosition->s32X;

    u32SecondCoord_DCI_Y_Start  += pstV0DisPosition->s32Y;
    u32SecondCoord_DCI_Y_End  += pstV0DisPosition->s32Y;

    pstActualDciArea->u16HStar = u32SecondCoord_DCI_X_Start;
    pstActualDciArea->u16HEnd = u32SecondCoord_DCI_X_End;
    pstActualDciArea->u16VStar = u32SecondCoord_DCI_Y_Start;
    pstActualDciArea->u16VEnd = u32SecondCoord_DCI_Y_End;

    *pbDciEnable = HI_TRUE;
    return HI_SUCCESS;
}

HI_VOID Win_DciEnable_Policy(WINDOW_S *pstWin,
                         HI_RECT_S *pstOriginDciArea,/*vpss's effective area.*/
                         HI_RECT_S *pstV0DisPosition,/*secondary coordinate*/
                         HI_RECT_S *pstVpssGive,/*the original rect give by vpss.*/
                         HI_U32    u32WinNum)
{
    HI_BOOL   bDciEnable = HI_FALSE;
    HI_BOOL   bDciCapability = HI_FALSE;
    HI_PQ_DCI_WIN_S stActualDciArea;
    HI_RECT_S stActualDciAreaRect;
    VIDEO_LAYER_CAPABILITY_S  stVideoLayerCap;
    HI_S32 ret = 0;

    if ((ret = pstWin->stVLayerFunc.PF_GetCapability(pstWin->u32VideoLayer,&stVideoLayerCap)))
    {
        return ;
    }

    bDciCapability = stVideoLayerCap.bDci;
    if (bDciCapability)
    {
        dci_enable_policy(pstOriginDciArea,/*vpss's effective area.*/
                            pstV0DisPosition,/*secondary coordinate*/
                            pstVpssGive,/*the original rect give by vpss.*/
                            u32WinNum,
                            &bDciEnable,
                            &stActualDciArea);

        updateDci(pstWin, bDciEnable, &stActualDciArea);

        stActualDciAreaRect.s32X = stActualDciArea.u16HStar;
        stActualDciAreaRect.s32Y = stActualDciArea.u16VStar;

        stActualDciAreaRect.s32Width = stActualDciArea.u16HEnd - stActualDciArea.u16HStar;
        stActualDciAreaRect.s32Height =stActualDciArea.u16VEnd - stActualDciArea.u16VStar;

        pstWin->stWinInfoForDeveloper.stOriginDCIPositionInFrame = *pstOriginDciArea;
        pstWin->stWinInfoForDeveloper.stDciFrameSize             = *pstVpssGive;
        pstWin->stWinInfoForDeveloper.bDciOpen                   = bDciEnable;
        pstWin->stWinInfoForDeveloper.stWinFinalPosition         = stActualDciAreaRect;
    }

    return ;
}
#if defined (CHIP_HIFONEB02)
HI_BOOL Win_DcmpShouldOpen(HI_BOOL bDcmp, HI_BOOL bMutimode)
{
    /*1. without dcmp capability,return false. */
    if (bDcmp == HI_FALSE)
    {
        return HI_FALSE;
    }

    /*3. dcmp does not fit the scene,return false. */
    if (bMutimode == HI_TRUE)
    {
        return HI_FALSE;
    }

    return HI_TRUE;
}

HI_U32 Win_SupportedBitWidth(HI_U32 u32SupportMaxbitWidth, HI_BOOL bMultimode)
{
    HI_U32 u32BitWidthForScene = 0;

    /*if in multimode, the layer only support 8bit.*/
    if (HI_TRUE ==  bMultimode)
    {
        u32BitWidthForScene =  8;
    }
    else
    {
        u32BitWidthForScene =  10;
    }

    /*1. to calculate the bitwidth support in current scene.*/
    return (u32SupportMaxbitWidth > u32BitWidthForScene)? u32BitWidthForScene: u32SupportMaxbitWidth;
}


/*this func is used to judge whether should mute the layer or not.
 *HI_TRUE means should mute the layer, hi_false means should open the layer.
 */
HI_BOOL Win_MuteLayer_Policy(HI_RECT_S *pstExpectRect,
                             HI_RECT_S *pstActualRect,
                             HI_BOOL   bZmeCapbility,
                             HI_DRV_PIX_FORMAT_E  eActualPixFormat,
                             HI_BOOL   bDcmpShouldOpen,
                             HI_DRV_PIXEL_BITWIDTH_E  enActualBitWidth,
                             HI_U32 u32CurrentMaxBitWidth)
{
    HI_U32 u32ActualBitWidth = 0;

     /*in some */
    if ((pstExpectRect->s32Width != pstActualRect->s32Width)
            || (pstExpectRect->s32Height != pstActualRect->s32Height))
    {
        if (HI_FALSE == bZmeCapbility)
        {
            /*we must confirm that v1, should not configure the zme,
              but the ifir is needed ,so we have to configure it or not? */
            return HI_TRUE;
        }
    }

    if (((eActualPixFormat == HI_DRV_PIX_FMT_NV12_CMP)
             || (eActualPixFormat == HI_DRV_PIX_FMT_NV21_CMP))
         && (bDcmpShouldOpen == HI_FALSE))
    {
        /*frame is compressed but the layer has no capability*/
        return HI_TRUE;
    }

    if (enActualBitWidth == HI_DRV_PIXEL_BITWIDTH_8BIT)
    {
        u32ActualBitWidth  = 8;
    }
    else if (enActualBitWidth == HI_DRV_PIXEL_BITWIDTH_10BIT)
    {
        u32ActualBitWidth  = 10;
    }
    else if (enActualBitWidth == HI_DRV_PIXEL_BITWIDTH_12BIT)
    {
        u32ActualBitWidth  = 12;
    }

    if (u32CurrentMaxBitWidth < u32ActualBitWidth)
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}
#endif
/*since we support out of window, so when out of window, the content and size of
 * the window  should be  cropped.
 */
HI_S32 Win_Revise_OutOfScreenWin_OutRect(HI_RECT_S *pstInRect,
                        HI_RECT_S *pstOutRect,
                        HI_RECT_S stScreen,
                        HI_DRV_DISP_OFFSET_S stOffsetRect,
                        WIN_HAL_PARA_S *pstLayerPara)
{
    HI_RECT_S stInRect = *pstInRect;
    HI_RECT_S stOutRect = *pstOutRect;
    HI_S32 s32VaildWidth,s32VaildHeight;
    HI_S32 ix = 0, iy = 0, iw = 0, ih = 0;
    HI_S32 ox =0, oy = 0, ow = 0, oh = 0;
    HI_BOOL bDispFlag = HI_FALSE;
    HI_CHIP_TYPE_E   enChipType;
    HI_CHIP_VERSION_E enChipVersion;

    HI_DRV_SYS_GetChipVersion(&enChipType, &enChipVersion);

    if (pstLayerPara->bSecondHorZmeEnable && pstLayerPara->bSecondVerZmeEnable)
    {
        /*when sr enable ,in 98c ,because v0 output size is half of final.
         * so fmt should be 1/2 size.
         */
        if ((HI_CHIP_TYPE_HI3798C == enChipType) || (HI_CHIP_TYPE_HI3796C == enChipType))
        {
            stScreen.s32Width  >>= 1;
            stScreen.s32Height >>= 1;
        }
    }

    stScreen.s32X = 0;
    stScreen.s32Y = 0;

    stScreen.s32Width -= stOffsetRect.u32Left + stOffsetRect.u32Right;
    stScreen.s32Height -= stOffsetRect.u32Top + stOffsetRect.u32Bottom;
    if (0 == stOutRect.s32Width || 0 == stOutRect.s32Height)
    {
        WIN_ERROR("Denominator may be zero !\n");
        return HI_FAILURE; 
    }
    /*stOutRect considered the offset already, so no need to - left.*/
    stOutRect.s32X  -= stOffsetRect.u32Left;
    stOutRect.s32Y  -= stOffsetRect.u32Top;

    if(stOutRect.s32X < 0)
    {
        s32VaildWidth = stOutRect.s32Width  + stOutRect.s32X;

        if(s32VaildWidth < WIN_INRECT_MIN_WIDTH)
        {
            ow = WIN_INRECT_MIN_WIDTH;
            ox = 0;
            iw = stInRect.s32Width * ow/stOutRect.s32Width;
            ix = stInRect.s32Width - iw;

            bDispFlag = HI_TRUE;
        }
        else
        {   // >screen size
            ow = stScreen.s32Width;
            if(s32VaildWidth < ow) // no full screan
            {
                 ow = s32VaildWidth;
            }

            ox = 0;
            iw = stInRect.s32Width * ow/stOutRect.s32Width;
            ix = stInRect.s32Width - stInRect.s32Width * s32VaildWidth/stOutRect.s32Width;
        }
    }
    else if (stOutRect.s32X < (stScreen.s32Width - WIN_INRECT_MIN_WIDTH))
    {
        s32VaildWidth = stOutRect.s32Width;

        if(s32VaildWidth < WIN_INRECT_MIN_WIDTH)
        {
            ow = WIN_INRECT_MIN_WIDTH;
            ox = stOutRect.s32X;
            iw = stInRect.s32Width;
            ix = 0;
            bDispFlag = HI_TRUE;
        }
        else
        {
            ox = stOutRect.s32X;
            ix = 0;

            if((s32VaildWidth + ox) > stScreen.s32Width)
            {
                ow = stScreen.s32Width - stOutRect.s32X;
                iw = stInRect.s32Width*ow/stOutRect.s32Width;
            }
            else
            {
               ow = stOutRect.s32Width;
               iw = stInRect.s32Width;
            }
        }
    }
    else
    {
        ow = WIN_INRECT_MIN_WIDTH;
        ox = stScreen.s32Width  - ow;
        iw = stInRect.s32Width*ow/stOutRect.s32Width;
        ix = 0;
        bDispFlag = HI_TRUE;
    }


    if(stOutRect.s32Y < 0)
    {
        s32VaildHeight = stOutRect.s32Height + stOutRect.s32Y;
        if(s32VaildHeight < WIN_INRECT_MIN_HEIGHT)
        {
            oy = 0;
            oh = WIN_INRECT_MIN_HEIGHT;
            ih = stInRect.s32Height*oh/stOutRect.s32Height;
            iy = stInRect.s32Height - ih;
            bDispFlag = HI_TRUE;
        }
        else
        {
            oy = 0;
            oh = stScreen.s32Height;
            if(s32VaildHeight < oh)
            {
                oh = s32VaildHeight;
            }

            ih = stInRect.s32Height*oh/stOutRect.s32Height;
            iy = stInRect.s32Height - stInRect.s32Height*s32VaildHeight/stOutRect.s32Height;
        }
    }
    else if (stOutRect.s32Y < (stScreen.s32Height - WIN_INRECT_MIN_HEIGHT))
    {
        s32VaildHeight = stOutRect.s32Height;

        if(s32VaildHeight < WIN_INRECT_MIN_HEIGHT)
        {
            oy = stOutRect.s32Y;
            oh = WIN_INRECT_MIN_HEIGHT;
            ih = stInRect.s32Height;
            iy = 0;
            bDispFlag = HI_TRUE;
        }
        else
        {
            oy = stOutRect.s32Y;
            iy = 0;
            if((s32VaildHeight + oy) > stScreen.s32Height)
            {
                oh = stScreen.s32Height - stOutRect.s32Y;
                ih = stInRect.s32Height * oh/stOutRect.s32Height;
            }
            else
            {
                oh = stOutRect.s32Height;
                ih = stInRect.s32Height;
            }
         }
    }
    else
    {
        oh = WIN_INRECT_MIN_HEIGHT;
        oy = stScreen.s32Height - oh;
        ih = stInRect.s32Height * oh/stOutRect.s32Height;
        iy = 0;
        bDispFlag = HI_TRUE;
    }

    ox  += stOffsetRect.u32Left;
    oy  += stOffsetRect.u32Top;

    /*DTS2013100801678, pstInRect in fact is the output of vpss(zme,dei,crop dnr)
     * it does not confirm to  the align limit of inrect.
     * If we give a wrong use, and make a wrong align,
     * there will be no consistency bettween GFX and VIDEO, and the backgroud color will appears.
     */
    pstInRect->s32X = ix & HI_WIN_OUT_RECT_X_ALIGN;
    pstInRect->s32Y = iy & HI_WIN_OUT_RECT_Y_ALIGN;
    pstInRect->s32Width = iw & HI_WIN_OUT_RECT_WIDTH_ALIGN;
    pstInRect->s32Height = ih & HI_WIN_OUT_RECT_HEIGHT_ALIGN;

    pstOutRect->s32X = ox & HI_WIN_OUT_RECT_X_ALIGN;
    pstOutRect->s32Y = oy & HI_WIN_OUT_RECT_Y_ALIGN;
    pstOutRect->s32Width = ow & HI_WIN_OUT_RECT_WIDTH_ALIGN;
    pstOutRect->s32Height = oh & HI_WIN_OUT_RECT_HEIGHT_ALIGN;

    return bDispFlag;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */




