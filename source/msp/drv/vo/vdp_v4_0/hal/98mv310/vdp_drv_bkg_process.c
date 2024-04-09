#include "vdp_drv_bkg_process.h"
#include "vdp_hal_comm.h"
#include "vdp_drv_pq_csc.h"
#include "vdp_func_pq_csc.h"
#include "vdp_hal_ip_hihdr_v.h"
#include "vdp_hal_vid.h"

#ifndef __DISP_PLATFORM_BOOT__
#include "vdp_drv_pq_ext.h"

HI_S32 VDP_DRV_GetCsc0Mode(VDP_CLR_SPACE_E enInClr, VDP_CLR_SPACE_E enOutClr, VDP_CSC_MODE_E *enCscMode, HI_PQ_CSC_MODE_E *enPqCscMode)
{
    VDP_CSC_MODE_E enCsc2Mode = {0};
    static HI_PQ_HDR_CFG  pstPqHdrCfg;

    memset((void *)&pstPqHdrCfg, 0, sizeof(pstPqHdrCfg));


    if (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020_L)
    {
        *enCscMode = VDP_CSC_YUV2RGB_709;//VDP_CSC_YUV2RGB_2020_2020_L           ; /* YCbCr L      -> YCbCr L */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709; /* YCbCr L      -> YCbCr L */
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_2020 && enOutClr == VDP_CLR_SPACE_RGB_2020_L)
    {
        *enCscMode = VDP_CSC_YUV2RGB_709;//VDP_CSC_YUV2RGB_2020_2020_L           ; /* YCbCr L      -> YCbCr L */
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709; /* YCbCr L      -> YCbCr L */
    }

    else if (enInClr == VDP_CLR_SPACE_YUV_2020 && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709 ;
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_2020_L && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_709 ;
        enCsc2Mode  = VDP_CSC_RGB2RGB;
    }
    else if (enInClr == VDP_CLR_SPACE_YUV_601_L && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = HI_PQ_CSC_YUV2RGB_601 ;
    }

    else if (enInClr == VDP_CLR_SPACE_YUV_709_L && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode  = VDP_CSC_YUV2RGB_709;
        *enPqCscMode = VDP_CSC_YUV2RGB_709 ;
    }
    else
    {
        VDP_PRINT("VDP Err csc0 mode in %d out %d!\n", enInClr, enOutClr);
    }

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_GetCsc1Mode(VDP_CLR_SPACE_E enInClr, VDP_CLR_SPACE_E enOutClr, VDP_CSC_MODE_E *enCscMode, HI_PQ_CSC_MODE_E *enPqCscMode)
{
    static HI_PQ_HDR_CFG  pstPqHdrCfg;

    memset((void *)&pstPqHdrCfg, 0, sizeof(pstPqHdrCfg));


   if ((enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020)
      || (enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020_L))
   {
        *enCscMode = VDP_CSC_RGB2RGB             ; /* RGB          -> RGB */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB             ; /* RGB          -> RGB */
   }
    else if ((enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_YUV_2020_L)
        ||(enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_YUV_2020))
    {
        *enCscMode = VDP_CSC_RGB2YUV_709     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_709    ; /* RGB          -> YCbCr_709 F */
    }
    else if ((enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_YUV_601_L)
            ||  (enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_YUV_601))
    {
        *enCscMode = VDP_CSC_RGB2YUV_601         ; /* RGB          -> YCbCr_709 L */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_709         ; /* RGB          -> YCbCr_709 L */
    }
    else if ((enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_YUV_709_L)
            || (enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_YUV_709))
    {
        *enCscMode = VDP_CSC_RGB2YUV_709     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2YUV_709     ; /* RGB          -> YCbCr_709 F */
    }

    else if (enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_RGB_709_L)
    {
        *enCscMode = VDP_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
    }
    else if (enInClr == VDP_CLR_SPACE_RGB_709_L && enOutClr == VDP_CLR_SPACE_RGB_709)
    {
        *enCscMode = VDP_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
    }

    else if (enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020_L)
    {
        *enCscMode = VDP_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
    }

    else if (enInClr == VDP_CLR_SPACE_RGB_2020_L && enOutClr == VDP_CLR_SPACE_RGB_2020)
    {
        *enCscMode = VDP_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
        *enPqCscMode = HI_PQ_CSC_RGB2RGB     ; /* RGB          -> YCbCr_709 F */
    }
    else
    {
        VDP_PRINT("VDP Err csc1 mode in %d out %d!\n", enInClr, enOutClr);
    }
    return HI_SUCCESS;

}

HI_S32 VDP_DRV_SetYuv2RgbCfg(HI_U32 u32LayerId, HI_S16  S16Yuv2Rgb[3][3],
                                       HI_S32 S32Yuv2RgbOutDc[3], HI_S32 S32Yuv2RgbInDc[3])
{
    VDP_HIHDR_V_SetHihdrY2rV1Scale2p( 13);
    VDP_HIHDR_V_SetHihdrY2rV0Scale2p( 13);

    VDP_HIHDR_V_SetHihdrY2rV1ClipMin( 0);
    VDP_HIHDR_V_SetHihdrY2rV0ClipMin( 0);
    VDP_HIHDR_V_SetHihdrY2rV1ClipMax( 1023);
    VDP_HIHDR_V_SetHihdrY2rV0ClipMax( 1023);

    VDP_HIHDR_V_SetVhdrDitherEn( 0);

    if (u32LayerId == VDP_LAYER_VID0)
    {
        VDP_HIHDR_V_SetHihdrV0Y2rEn( 1);
        VDP_HIHDR_V_SetHihdrY2rEn( 1);
        VDP_HIHDR_V_SetHihdrY2rCoef00( S16Yuv2Rgb[0][0]);
        VDP_HIHDR_V_SetHihdrY2rCoef01( S16Yuv2Rgb[0][1]);
        VDP_HIHDR_V_SetHihdrY2rCoef02( S16Yuv2Rgb[0][2]);
        VDP_HIHDR_V_SetHihdrY2rCoef03( S16Yuv2Rgb[1][0]);
        VDP_HIHDR_V_SetHihdrY2rCoef04( S16Yuv2Rgb[1][1]);
        VDP_HIHDR_V_SetHihdrY2rCoef05( S16Yuv2Rgb[1][2]);
        VDP_HIHDR_V_SetHihdrY2rCoef06( S16Yuv2Rgb[2][0]);
        VDP_HIHDR_V_SetHihdrY2rCoef07( S16Yuv2Rgb[2][1]);
        VDP_HIHDR_V_SetHihdrY2rCoef08( S16Yuv2Rgb[2][2]);
        VDP_HIHDR_V_SetHihdrY2rIdc00( S32Yuv2RgbInDc[0] );
        VDP_HIHDR_V_SetHihdrY2rIdc01( S32Yuv2RgbInDc[1] );
        VDP_HIHDR_V_SetHihdrY2rIdc02( S32Yuv2RgbInDc[2] );
        VDP_HIHDR_V_SetHihdrY2rOdc00( S32Yuv2RgbOutDc[0]);
        VDP_HIHDR_V_SetHihdrY2rOdc01( S32Yuv2RgbOutDc[1]);
        VDP_HIHDR_V_SetHihdrY2rOdc02( S32Yuv2RgbOutDc[2]);


    }
    else if (u32LayerId == VDP_LAYER_VID1)
    {
        VDP_HIHDR_V_SetHihdrV1Y2rEn( 1);
        VDP_HIHDR_V_SetHihdrY2rEn( 1);
        VDP_HIHDR_V_SetHihdrY2rCoef00( S16Yuv2Rgb[0][0]);
        VDP_HIHDR_V_SetHihdrY2rCoef01( S16Yuv2Rgb[0][1]);
        VDP_HIHDR_V_SetHihdrY2rCoef02( S16Yuv2Rgb[0][2]);
        VDP_HIHDR_V_SetHihdrY2rCoef03( S16Yuv2Rgb[1][0]);
        VDP_HIHDR_V_SetHihdrY2rCoef04( S16Yuv2Rgb[1][1]);
        VDP_HIHDR_V_SetHihdrY2rCoef05( S16Yuv2Rgb[1][2]);
        VDP_HIHDR_V_SetHihdrY2rCoef06( S16Yuv2Rgb[2][0]);
        VDP_HIHDR_V_SetHihdrY2rCoef07( S16Yuv2Rgb[2][1]);
        VDP_HIHDR_V_SetHihdrY2rCoef08( S16Yuv2Rgb[2][2]);
        VDP_HIHDR_V_SetHihdrY2rIdc00( S32Yuv2RgbInDc[0] );
        VDP_HIHDR_V_SetHihdrY2rIdc01( S32Yuv2RgbInDc[1] );
        VDP_HIHDR_V_SetHihdrY2rIdc02( S32Yuv2RgbInDc[2] );
        VDP_HIHDR_V_SetHihdrY2rOdc00( S32Yuv2RgbOutDc[0]);
        VDP_HIHDR_V_SetHihdrY2rOdc01( S32Yuv2RgbOutDc[1]);
        VDP_HIHDR_V_SetHihdrY2rOdc02( S32Yuv2RgbOutDc[2]);
    }
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetRgb2YuvCfg(HI_U32 u32LayerId, HI_S16  S16Rgb2Yuv[3][3],
                             HI_S32 S32Rgb2YuvOutDc[3], HI_S32 S32Rgb2YuvInDc[3])
{
	VDP_HIHDR_V_SetVhdrR2yEn( 1);
	VDP_HIHDR_V_SetVhdrR2yCoef00( S16Rgb2Yuv[0][0]);
	VDP_HIHDR_V_SetVhdrR2yCoef01( S16Rgb2Yuv[0][1]);
	VDP_HIHDR_V_SetVhdrR2yCoef02( S16Rgb2Yuv[0][2]);
	VDP_HIHDR_V_SetVhdrR2yCoef10( S16Rgb2Yuv[1][0]);
	VDP_HIHDR_V_SetVhdrR2yCoef11( S16Rgb2Yuv[1][1]);
	VDP_HIHDR_V_SetVhdrR2yCoef12( S16Rgb2Yuv[1][2]);
	VDP_HIHDR_V_SetVhdrR2yCoef20( S16Rgb2Yuv[2][0]);
	VDP_HIHDR_V_SetVhdrR2yCoef21( S16Rgb2Yuv[2][1]);
	VDP_HIHDR_V_SetVhdrR2yCoef22( S16Rgb2Yuv[2][2]);
	VDP_HIHDR_V_SetVhdrR2yScale2p( 14);
	VDP_HIHDR_V_SetVhdrR2yIdc0( S32Rgb2YuvInDc[0]);
	VDP_HIHDR_V_SetVhdrR2yIdc1( S32Rgb2YuvInDc[1]);
	VDP_HIHDR_V_SetVhdrR2yIdc2( S32Rgb2YuvInDc[2]);
	VDP_HIHDR_V_SetVhdrR2yOdc0( S32Rgb2YuvOutDc[0]);
	VDP_HIHDR_V_SetVhdrR2yOdc1( S32Rgb2YuvOutDc[1]);
	VDP_HIHDR_V_SetVhdrR2yOdc2( S32Rgb2YuvOutDc[2]);
	VDP_HIHDR_V_SetVhdrR2yClipCMin( 0);
	VDP_HIHDR_V_SetVhdrR2yClipYMin( 0);
	VDP_HIHDR_V_SetVhdrR2yClipCMax( 1023);
	VDP_HIHDR_V_SetVhdrR2yClipYMax( 1023);

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetVdpBkg(HI_U32 u32LayerId, VDP_COLOR_SPACE_INFO_S  *pstColorSpaceInfo)
{
#if 0
    HI_PQ_CSC_CRTL_S stCscCtrl = {0};
    VDP_CSC_MODE_E enCscMode = {0};

    HI_PQ_CSC_MODE_E enPqCscMode = {0};

    VDP_CSC_COEF_S     stCscCoef = {0};
    VDP_CSC_DC_COEF_S  stCscDc = {0};
    HI_PQ_CSC_COEF_S   stPqCscCoef = {0};
    HI_PQ_CSC_DCCOEF_S stPqCscDc = {0};
    HI_S16             S16Yuv2Rgb[3][3] = {{0}, {0}, {0}};
    HI_S32             S32Yuv2RgbOutDc[3] = {0};
    HI_S32             S32Yuv2RgbInDc[3] = {0};
    VDP_CLR_SPACE_E enInClr;
    VDP_CLR_SPACE_E enOutClr;

    enInClr = pstColorSpaceInfo->enInClrSpace;
    enOutClr = pstColorSpaceInfo->enOutClrSpace;

    if (pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020_L
        || pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_YUV_2020
        || pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_RGB_2020_L
        || pstColorSpaceInfo->enInClrSpace == VDP_CLR_SPACE_RGB_2020
       )
    {
        enInClr  = VDP_CLR_SPACE_YUV_709_L;
        enOutClr = VDP_CLR_SPACE_RGB_709_L;
    }
    else
    {
        enOutClr = VDP_CLR_SPACE_RGB_709_L;
    }
    VDP_PRINT(">>>>>>enInClr = %d  enOutClr = %d<<<<<<<<<<\n",enInClr,enOutClr);
    //--------------------csc0 begin--------------------------------------//
    VDP_DRV_GetCsc0Mode(enInClr, enOutClr, &enCscMode, &enPqCscMode);

    stCscCtrl.bCSCEn    = HI_TRUE;
    stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V0;

    VDP_PQ_GetCSCCoefPtr(&stCscCtrl, enCscMode, enPqCscMode, &stPqCscCoef, &stPqCscDc);

    memcpy(&stCscCoef, &stPqCscCoef, sizeof(VDP_CSC_COEF_S));
    memcpy(&stCscDc, &stPqCscDc, sizeof(VDP_CSC_DC_COEF_S));

    S32Yuv2RgbOutDc[0] =  stPqCscDc.csc_out_dc0;
    S32Yuv2RgbOutDc[1] =  stPqCscDc.csc_out_dc1;
    S32Yuv2RgbOutDc[2] =  stPqCscDc.csc_out_dc2;

    S32Yuv2RgbInDc[0] =  stPqCscDc.csc_in_dc0;
    S32Yuv2RgbInDc[1] =  stPqCscDc.csc_in_dc1;
    S32Yuv2RgbInDc[2] =  stPqCscDc.csc_in_dc2;

    S16Yuv2Rgb[0][0]  = (HI_S16)stPqCscCoef.csc_coef00 * 8;
    S16Yuv2Rgb[0][1]  = (HI_S16)stPqCscCoef.csc_coef01 * 8;
    S16Yuv2Rgb[0][2]  = (HI_S16)stPqCscCoef.csc_coef02 * 8;
    S16Yuv2Rgb[1][0]  = (HI_S16)stPqCscCoef.csc_coef10 * 8;
    S16Yuv2Rgb[1][1]  = (HI_S16)stPqCscCoef.csc_coef11 * 8;
    S16Yuv2Rgb[1][2]  = (HI_S16)stPqCscCoef.csc_coef12 * 8;
    S16Yuv2Rgb[2][0]  = (HI_S16)stPqCscCoef.csc_coef20 * 8;
    S16Yuv2Rgb[2][1]  = (HI_S16)stPqCscCoef.csc_coef21 * 8;
    S16Yuv2Rgb[2][2]  = (HI_S16)stPqCscCoef.csc_coef22 * 8;

    VDP_DRV_SetYuv2RgbCfg(u32LayerId, S16Yuv2Rgb, S32Yuv2RgbOutDc, S32Yuv2RgbInDc);
    //--------------------csc0 end--------------------------------------//


    //--------------------csc1 begin--------------------------------------//
    enInClr  = enOutClr;

    if (pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020_L
        || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_YUV_2020
       )
    {
        enOutClr = VDP_CLR_SPACE_YUV_709_L;
    }
    else if (pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020_L
             || pstColorSpaceInfo->enOutClrSpace == VDP_CLR_SPACE_RGB_2020
            )
    {
        enOutClr = VDP_CLR_SPACE_RGB_709_L;
    }
    else
    {
        enOutClr = pstColorSpaceInfo->enOutClrSpace;
    }

    VDP_DRV_GetCsc1Mode(enInClr, enOutClr, &enCscMode, &enPqCscMode);

    stCscCtrl.bCSCEn    = HI_TRUE;
    stCscCtrl.enCscType = HI_PQ_CSC_TUNING_V0;

    VDP_PQ_GetCSCCoefPtr(&stCscCtrl, enCscMode, enPqCscMode, &stPqCscCoef, &stPqCscDc);


    memcpy(&stCscCoef, &stPqCscCoef, sizeof(VDP_CSC_COEF_S));
    memcpy(&stCscDc, &stPqCscDc, sizeof(VDP_CSC_DC_COEF_S));

    S32Yuv2RgbOutDc[0] =  stPqCscDc.csc_out_dc0;
    S32Yuv2RgbOutDc[1] =  stPqCscDc.csc_out_dc1;
    S32Yuv2RgbOutDc[2] =  stPqCscDc.csc_out_dc2;

    S32Yuv2RgbInDc[0] =  stPqCscDc.csc_in_dc0;
    S32Yuv2RgbInDc[1] =  stPqCscDc.csc_in_dc1;
    S32Yuv2RgbInDc[2] =  stPqCscDc.csc_in_dc2;

    S16Yuv2Rgb[0][0]  = (HI_S16)stPqCscCoef.csc_coef00 * 16;
    S16Yuv2Rgb[0][1]  = (HI_S16)stPqCscCoef.csc_coef01 * 16;
    S16Yuv2Rgb[0][2]  = (HI_S16)stPqCscCoef.csc_coef02 * 16;
    S16Yuv2Rgb[1][0]  = (HI_S16)stPqCscCoef.csc_coef10 * 16;
    S16Yuv2Rgb[1][1]  = (HI_S16)stPqCscCoef.csc_coef11 * 16;
    S16Yuv2Rgb[1][2]  = (HI_S16)stPqCscCoef.csc_coef12 * 16;
    S16Yuv2Rgb[2][0]  = (HI_S16)stPqCscCoef.csc_coef20 * 16;
    S16Yuv2Rgb[2][1]  = (HI_S16)stPqCscCoef.csc_coef21 * 16;
    S16Yuv2Rgb[2][2]  = (HI_S16)stPqCscCoef.csc_coef22 * 16;

    VDP_DRV_SetRgb2YuvCfg(u32LayerId, S16Yuv2Rgb, S32Yuv2RgbOutDc, S32Yuv2RgbInDc);
    //--------------------csc1 end--------------------------------------//
#endif
    return HI_SUCCESS;
}

HI_VOID XDP_DRV_JudgeRgbColorSpace(VDP_CLR_SPACE_E enClrSpace,HI_BOOL *pbRgbColorSpace)
{
    if (enClrSpace == VDP_CLR_SPACE_RGB_601
        || enClrSpace == VDP_CLR_SPACE_RGB_709
        || enClrSpace == VDP_CLR_SPACE_RGB_2020
        || enClrSpace == VDP_CLR_SPACE_RGB_601_L
        || enClrSpace == VDP_CLR_SPACE_RGB_709_L
        || enClrSpace == VDP_CLR_SPACE_RGB_2020_L
       )
    {
        *pbRgbColorSpace = HI_TRUE;
    }
    else
    {
        *pbRgbColorSpace = HI_FALSE;
    }

    return;
}


HI_VOID VDP_DRV_SetLayerLetterboxBkg(HI_BOOL bRgbColorSpace)
{
    VDP_BKG_S  stLetterBoxColor = {0};

    stLetterBoxColor.u32BkgA = 0xff;

    if (HI_TRUE ==bRgbColorSpace)
    {
        stLetterBoxColor.u32BkgY = 0x0;
        stLetterBoxColor.u32BkgU = 0x0;
        stLetterBoxColor.u32BkgV = 0x0;
    }
    else
    {
        stLetterBoxColor.u32BkgY = 0x0;
        stLetterBoxColor.u32BkgU = 0x200;
        stLetterBoxColor.u32BkgV = 0x200;
    }

    VDP_VID_SetLayerBkg(VDP_LAYER_VID0, stLetterBoxColor);

    return;
}

HI_VOID XDP_DRV_AdjustColor(VDP_BKG_S *pstOutColor,VDP_BKG_S pstInColor, HI_BOOL bRgbColorSpace)
{
    HI_S32 s32Red   = 0;
    HI_S32 s32Green = 0;
    HI_S32 s32Blue  = 0;
    HI_S32 s32Y = 0;
    HI_S32 s32U = 0;
    HI_S32 s32V = 0;

    s32Red   = (HI_S32)pstInColor.u32BkgY;
    s32Green = (HI_S32)pstInColor.u32BkgU;
    s32Blue  = (HI_S32)pstInColor.u32BkgV;

    if (bRgbColorSpace)
    {
        //8bit -> 10bit.
        pstOutColor->u32BkgY = (HI_U32)s32Red << 2;
        pstOutColor->u32BkgU = (HI_U32)s32Green << 2;
        pstOutColor->u32BkgV = (HI_U32)s32Blue << 2;
    }
    else
    {
        //change rgb to yuv.
        s32Y = (183 * s32Red + 614 * s32Green + 62 * s32Blue )/ 1000 + 16;
        s32U = (-101* s32Red - 338 * s32Green + 439* s32Blue )/ 1000 + 128;
        s32V = (439 * s32Red - 399 * s32Green - 40 * s32Blue )/ 1000 + 128;

        s32Y = (s32Y < 16)  ? 16  : s32Y;
        s32Y = (s32Y > 235) ? 235 : s32Y;
        s32U = (s32U < 16)  ? 16  : s32U;
        s32U = (s32U > 240) ? 240 : s32U;
        s32V = (s32V < 16)  ? 16  : s32V;
        s32V = (s32V > 240) ? 240 : s32V;

        //8bit -> 10bit.
        pstOutColor->u32BkgY = (HI_U32)s32Y << 2;
        pstOutColor->u32BkgU = (HI_U32)s32U << 2;
        pstOutColor->u32BkgV = (HI_U32)s32V << 2;
    }
    return ;
}


#endif
