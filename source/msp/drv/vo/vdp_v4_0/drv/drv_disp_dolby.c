/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : drv_disp_dolby.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017-06-08
  Description   : Dolby HDR processing functions.
  History       :
  1.Date        : 2017-06-08
    Author      : sdk
    Modification: Created file
*******************************************************************************/
#include "hi_drv_hdmi.h"
#include "hi_drv_module.h"
#include "drv_disp_priv.h"
#include "drv_disp_bufcore.h"
#include "drv_disp_dolby.h"
#include "drv_window.h"
#include "vdp_dm_typefxp.h"
#include "vdp_hal_chn.h"
#include "hi_drv_disp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

//******************************extern function***********************************
extern HI_VOID XDR_InfoFrame_SetColorimetry(HI_DRV_COLOR_SPACE_E enOutCs,
                                                   HI_DRV_HDMI_HDR_ATTR_S *pstHdmiHdrAttr);


static HI_BOOL IsLengthValid(DISP_HDR_META_INFO_S *pstHdrInfo)
{
    /**Judge whether the length is valid.**/
    if (DISP_BUF_METADATA_SIZE < (pstHdrInfo->u32CompLen + \
                              pstHdrInfo->u32DmCfgLen + \
                              pstHdrInfo->u32DmRegLen + \
                              pstHdrInfo->u32Hdr10InfoFrmLen + \
                              pstHdrInfo->u32UpMdLen))
    {
        DISP_ERROR("Invalid metadata length.\n");
        return HI_FALSE;
    }

    if (pstHdrInfo->u32CompLen != sizeof(VDP_FIXPT_MAIN_CFG_S))
    {
        DISP_ERROR("Invalid u32CompLen.\n");
        return HI_FALSE;
    }

    if (pstHdrInfo->u32DmCfgLen != sizeof(VDP_METADATA_S))
    {
        DISP_ERROR("Invalid u32DmCfgLen.\n");
        return HI_FALSE;
    }

    if (pstHdrInfo->u32DmRegLen != sizeof(DmKsFxp_t))
    {
        DISP_ERROR("Invalid u32DmRegLen.\n");
        return HI_FALSE;
    }

    if (pstHdrInfo->u32Hdr10InfoFrmLen != sizeof(VDP_HDR10_FRMINFO_S))
    {
        DISP_ERROR("Invalid u32Hdr10InfoFrmLen.\n");
        return HI_FALSE;
    }

    return HI_TRUE;
}

//*******************************NEW STUCTURE CODE****************************
HI_VOID XDR_DOLBY_GetCoeffByFrm(HI_DRV_VIDEO_FRAME_S      *pstFrm,
                                          DRV_DISP_DOLBY_PLAY_INFO_S *pstDolbyInfo)
{
    DISP_BUF_NODE_S *pstDispBufNode = HI_NULL;
    DRV_DISP_DOLBY_COEFF_S *pstDolbyCoeff = HI_NULL;
    HI_U32           u32CompLen  = 0;
    HI_U32           u32DmCfgLen = 0;
    HI_U32           u32KsDmLen  = 0;
    HI_U32           u32Hdr10InfoFrmLen = 0;

    pstDispBufNode = container_of((HI_U32 *)pstFrm,DISP_BUF_NODE_S,u32Data[0]);//use container_of method to get the node.

    u32CompLen  = pstDispBufNode->stHdrInfo.u32CompLen;
    u32DmCfgLen = pstDispBufNode->stHdrInfo.u32DmCfgLen;
    u32KsDmLen  = pstDispBufNode->stHdrInfo.u32DmRegLen;
    u32Hdr10InfoFrmLen= pstDispBufNode->stHdrInfo.u32Hdr10InfoFrmLen;
    pstDolbyInfo->stDolbyCoeff.u32UpMdLen = pstDispBufNode->stHdrInfo.u32UpMdLen;

    pstDolbyInfo->bELVaild = pstDispBufNode->bValidData2;
    pstDolbyCoeff = &pstDolbyInfo->stDolbyCoeff;

    if (HI_FALSE == IsLengthValid(&pstDispBufNode->stHdrInfo))
    {
        return;
    }

    //get composer cfg and dm reg metadata from buffer Node.
    memcpy(&pstDolbyCoeff->stCompCfg,pstDispBufNode->u8Metadata,u32CompLen);
    memcpy(&pstDolbyCoeff->stDmCfg,pstDispBufNode->u8Metadata + u32CompLen,u32DmCfgLen);
    memcpy(&pstDolbyCoeff->stDmKs,pstDispBufNode->u8Metadata \
           + u32CompLen + u32DmCfgLen,u32KsDmLen);
    memcpy(&pstDolbyCoeff->stHdr10InfoFrm,pstDispBufNode->u8Metadata \
           + u32CompLen + u32DmCfgLen + u32KsDmLen,u32Hdr10InfoFrmLen);
    memcpy(&pstDolbyCoeff->u8MdBuf,pstDispBufNode->u8Metadata + u32CompLen \
           + u32DmCfgLen + u32KsDmLen + u32Hdr10InfoFrmLen,\
           pstDolbyInfo->stDolbyCoeff.u32UpMdLen);

    if(pstDolbyInfo->bELVaild)
    {
        pstDolbyCoeff->stCompCfg.disable_residual_flag = HI_FALSE;
    }
    else
    {
        pstDolbyCoeff->stCompCfg.disable_residual_flag = HI_TRUE;
    }

    return;
}

HI_VOID XDR_DOLBY_GetHdr10InfoFrm(VDP_HDR10_FRMINFO_S *pstHdr10InfoFrm,
                                            const HI_DRV_DISP_OUT_TYPE_E enDispOutType,
                                            HI_DRV_HDMI_HDR_ATTR_S   *pstHdmiHdrAttr)
{
    if(HI_DRV_DISP_TYPE_HDR10_CERT == enDispOutType)
    {
        pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_CEA_861_3_AUTHEN;
    }
    else
    {
        pstHdmiHdrAttr->enHdrMode = HI_DRV_HDMI_HDR_MODE_CEA_861_3;
    }

    pstHdmiHdrAttr->enEotfType = HI_DRV_HDMI_EOTF_SMPTE_ST_2084;
    pstHdmiHdrAttr->enMetadataId = HI_DRV_HDMI_HDR_METADATA_ID_0;

    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries0_X = (pstHdr10InfoFrm->display_primaries_x_0_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_x_0_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries0_Y = (pstHdr10InfoFrm->display_primaries_y_0_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_y_0_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries1_X = (pstHdr10InfoFrm->display_primaries_x_1_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_x_1_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries1_Y = (pstHdr10InfoFrm->display_primaries_y_1_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_y_1_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries2_X = (pstHdr10InfoFrm->display_primaries_x_2_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_x_2_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16Primaries2_Y = (pstHdr10InfoFrm->display_primaries_y_2_MSB << 8) |
                                                           (pstHdr10InfoFrm->display_primaries_y_2_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16WhitePoint_X = (pstHdr10InfoFrm->white_point_x_MSB << 8) |
                                                           (pstHdr10InfoFrm->white_point_x_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16WhitePoint_Y = (pstHdr10InfoFrm->white_point_y_MSB << 8) |
                                                           (pstHdr10InfoFrm->white_point_y_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16MaxLuminance = (pstHdr10InfoFrm->max_display_mastering_luminance_MSB << 8) |
                                                           (pstHdr10InfoFrm->max_display_mastering_luminance_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16MinLuminance = (pstHdr10InfoFrm->min_display_mastering_luminance_MSB << 8) |
                                                           (pstHdr10InfoFrm->min_display_mastering_luminance_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16MaxLightLevel= (pstHdr10InfoFrm->max_content_light_level_MSB << 8) |
                                                           (pstHdr10InfoFrm->max_content_light_level_LSB);
    pstHdmiHdrAttr->unDescriptor.stType1.u16AverageLightLevel= (pstHdr10InfoFrm->max_frame_average_light_level_MSB << 8) |
                                                           (pstHdr10InfoFrm->max_frame_average_light_level_LSB);
    /* !NOTICE! here should use no-const luminous,otherwise may cause display problem on
    * some TVs which not support const luminous. */
    pstHdmiHdrAttr->enColorimetry = HI_DRV_HDMI_COLORIMETRY_2020_NON_CONST_LUMINOUS;
    return ;
}


static DRV_DISP_DOLBY_PLAY_INFO_S g_stDolbyInfo = {0};

HI_VOID XDR_DOLBY_Process(DISP_S                *pstDisp,
                                  WIN_INFO_S            *pstWinInfo,
                                  DISP_XDR_PLAY_INFO_S   *pstXdrPlayInfo)
{
    if (HI_NULL == pstDisp
       || HI_NULL == pstWinInfo
       || HI_NULL == pstXdrPlayInfo)
    {
        HI_ERR_DISP("Pointer is null !");
        return;
    }

    if (HI_NULL == pstWinInfo->pCurrentFrame)
    {
        pstXdrPlayInfo->enColorSpace = pstDisp->stXdrPrePlayInfo.enColorSpace;
        pstXdrPlayInfo->enOutType = pstDisp->stXdrPrePlayInfo.enOutType;
        pstXdrPlayInfo->stXdrHdmiHdrAttr = pstDisp->stXdrPrePlayInfo.stXdrHdmiHdrAttr;
        g_stDolbyInfo = pstDisp->stDolbyInfo;
    }
    else
    {
        XDR_DOLBY_GetCoeffByFrm(pstWinInfo->pCurrentFrame, &g_stDolbyInfo);

        switch(pstWinInfo->enOutType)
        {
            case HI_DRV_DISP_TYPE_HDR10:
            case HI_DRV_DISP_TYPE_HDR10_CERT:
                XDR_DOLBY_GetHdr10InfoFrm(&g_stDolbyInfo.stDolbyCoeff.stHdr10InfoFrm,
                                          pstWinInfo->enOutType,
                                          &pstXdrPlayInfo->stXdrHdmiHdrAttr);
                pstXdrPlayInfo->enColorSpace = HI_DRV_CS_BT2020_YUV_LIMITED;
                pstXdrPlayInfo->enOutType = HI_DRV_DISP_TYPE_HDR10;
                break;
            case HI_DRV_DISP_TYPE_NORMAL:
            case HI_DRV_DISP_TYPE_SDR_CERT:
                pstXdrPlayInfo->stXdrHdmiHdrAttr.enHdrMode = HI_DRV_HDMI_HDR_MODE_DISABLE;
                pstXdrPlayInfo->enColorSpace = HI_DRV_CS_BT709_YUV_LIMITED;
                pstXdrPlayInfo->enOutType = HI_DRV_DISP_TYPE_NORMAL;
                break;
            case HI_DRV_DISP_TYPE_DOLBY:
                pstXdrPlayInfo->stXdrHdmiHdrAttr.enHdrMode = HI_DRV_HDMI_HDR_MODE_DOLBY_TUNNELING;
                pstXdrPlayInfo->enColorSpace = HI_DRV_CS_BT709_YUV_LIMITED;
                pstXdrPlayInfo->enOutType = HI_DRV_DISP_TYPE_DOLBY;
                break;
            default:
                DISP_ERROR("Invalid Output Type in Dolby process.\n");
                pstXdrPlayInfo->stXdrHdmiHdrAttr.enHdrMode = HI_DRV_HDMI_HDR_MODE_DISABLE;
                pstXdrPlayInfo->enColorSpace = HI_DRV_CS_BT709_YUV_LIMITED;
                pstXdrPlayInfo->enOutType = HI_DRV_DISP_TYPE_NORMAL;
                break;

        }

    }

    XDR_InfoFrame_SetColorimetry(pstXdrPlayInfo->enColorSpace, &pstXdrPlayInfo->stXdrHdmiHdrAttr);

    //config dolby path.
    pstDisp->pstIntfOpt->PF_ConfigDolbyPath(pstWinInfo,&g_stDolbyInfo);

    //record dolby coeff.
    pstDisp->stDolbyInfo = g_stDolbyInfo;

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
