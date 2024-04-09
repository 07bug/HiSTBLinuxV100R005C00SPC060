/******************************************************************************
  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_xdr_policy.c
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2017/06/12
Last Modified :
Description   : this file use to adapt hal's structures.
Function List :
History       :
******************************************************************************/

#include "hal_xdr_policy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifndef __DISP_PLATFORM_BOOT__
static DRV_DISP_XDR_HARDWARE_CAP_S g_stXdrHardwareCap = {HI_TRUE, HI_TRUE, HI_TRUE, HI_TRUE, HI_FALSE};

static HI_DRV_DISP_XDR_ENGINE_E g_enXdrEngineList[HI_DRV_VIDEO_FRAME_TYPE_BUTT][HI_DRV_DISP_TYPE_BUTT][XDR_ENGINE_NUM] =
{
    /* SDR frame type : HI_DRV_VIDEO_FRAME_TYPE_SDR*/
    {
        /* SDR output type : HI_DRV_DISP_TYPE_NORMAL */
        {DRV_XDR_ENGINE_SDR, DRV_XDR_ENGINE_HDR10, DRV_XDR_ENGINE_HLG, DRV_XDR_ENGINE_SLF, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* SDR_Cert output type : HI_DRV_DISP_TYPE_SDR_CERT*/
        {DRV_XDR_ENGINE_SDR, DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Auto output type : HI_DRV_DISP_TYPE_AUTO*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Dolby output type : HI_DRV_DISP_TYPE_DOLBY */
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10 output type : HI_DRV_DISP_TYPE_HDR10 */
        {DRV_XDR_ENGINE_HDR10, DRV_XDR_ENGINE_HLG, DRV_XDR_ENGINE_SLF, DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10_Cert output type : HI_DRV_DISP_TYPE_HDR10_CERT*/
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HLG output type : HI_DRV_DISP_TYPE_HLG*/
        {DRV_XDR_ENGINE_HLG, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Technicolor output type : HI_DRV_DISP_TYPE_TECHNICOLOR , Unsupport currently.*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Follow first frame : HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME .*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},
    },

    /* Dolby BL frame type : HI_DRV_VIDEO_FRAME_TYPE_DOLBY_BL*/
    {
        /* SDR output type : HI_DRV_DISP_TYPE_NORMAL */
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_SDR, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* SDR_Cert output type : HI_DRV_DISP_TYPE_SDR_CERT*/
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_SDR, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Auto output type : HI_DRV_DISP_TYPE_AUTO*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Dolby output type : HI_DRV_DISP_TYPE_DOLBY */
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10 output type : HI_DRV_DISP_TYPE_HDR10 */
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10_Cert output type : HI_DRV_DISP_TYPE_HDR10_CERT*/
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HLG output type : HI_DRV_DISP_TYPE_HLG*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Technicolor output type : HI_DRV_DISP_TYPE_TECHNICOLOR , Unsupport currently.*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Follow first frame : HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME .*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},
    },

    /* Dolby EL frame type : HI_DRV_VIDEO_FRAME_TYPE_DOLBY_EL, EL always follow BL*/
    {
        /* SDR output type : HI_DRV_DISP_TYPE_NORMAL */
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_SDR, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* SDR_Cert output type : HI_DRV_DISP_TYPE_SDR_CERT*/
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_SDR, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Auto output type : HI_DRV_DISP_TYPE_AUTO*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Dolby output type : HI_DRV_DISP_TYPE_DOLBY */
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10 output type : HI_DRV_DISP_TYPE_HDR10 */
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10_Cert output type : HI_DRV_DISP_TYPE_HDR10_CERT*/
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HLG output type : HI_DRV_DISP_TYPE_HLG*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Technicolor output type : HI_DRV_DISP_TYPE_TECHNICOLOR , Unsupport currently.*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Follow first frame : HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME .*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},
    },

    /* HDR10 frame type : HI_DRV_VIDEO_FRAME_TYPE_HDR10*/
    {
        /* SDR output type : HI_DRV_DISP_TYPE_NORMAL */
        {DRV_XDR_ENGINE_HDR10, DRV_XDR_ENGINE_HLG, DRV_XDR_ENGINE_SLF, DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* SDR_Cert output type : HI_DRV_DISP_TYPE_SDR_CERT*/
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Auto output type : HI_DRV_DISP_TYPE_AUTO*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Dolby output type : HI_DRV_DISP_TYPE_DOLBY */
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10 output type : HI_DRV_DISP_TYPE_HDR10 */
        {DRV_XDR_ENGINE_HDR10, DRV_XDR_ENGINE_HLG, DRV_XDR_ENGINE_SLF, DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10_Cert output type : HI_DRV_DISP_TYPE_HDR10_CERT*/
        {DRV_XDR_ENGINE_DOLBY, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HLG output type : HI_DRV_DISP_TYPE_HLG*/
        {DRV_XDR_ENGINE_HLG, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Technicolor output type : HI_DRV_DISP_TYPE_TECHNICOLOR , Unsupport currently.*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Follow first frame : HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME .*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},
    },

    /* HLG frame type : HI_DRV_VIDEO_FRAME_TYPE_HLG*/
    {
        /* SDR output type : HI_DRV_DISP_TYPE_NORMAL */
        {DRV_XDR_ENGINE_HLG, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* SDR_Cert output type : HI_DRV_DISP_TYPE_SDR_CERT*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Auto output type : HI_DRV_DISP_TYPE_AUTO*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Dolby output type : HI_DRV_DISP_TYPE_DOLBY */
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10 output type : HI_DRV_DISP_TYPE_HDR10 */
        {DRV_XDR_ENGINE_HLG, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10_Cert output type : HI_DRV_DISP_TYPE_HDR10_CERT*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HLG output type : HI_DRV_DISP_TYPE_HLG*/
        {DRV_XDR_ENGINE_HLG, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Technicolor output type : HI_DRV_DISP_TYPE_TECHNICOLOR , Unsupport currently.*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Follow first frame : HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME .*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},
    },

    /* SLF frame type : HI_DRV_VIDEO_FRAME_TYPE_SLF*/
    {
        /* SDR output type : HI_DRV_DISP_TYPE_NORMAL */
        {DRV_XDR_ENGINE_SLF, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* SDR_Cert output type : HI_DRV_DISP_TYPE_SDR_CERT*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Auto output type : HI_DRV_DISP_TYPE_AUTO*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Dolby output type : HI_DRV_DISP_TYPE_DOLBY */
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10 output type : HI_DRV_DISP_TYPE_HDR10 */
        {DRV_XDR_ENGINE_SLF, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10_Cert output type : HI_DRV_DISP_TYPE_HDR10_CERT*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HLG output type : HI_DRV_DISP_TYPE_HLG*/
        {DRV_XDR_ENGINE_SLF, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Technicolor output type : HI_DRV_DISP_TYPE_TECHNICOLOR , Unsupport currently.*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Follow first frame : HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME .*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},
    },

    /* JTP frame type : HI_DRV_VIDEO_FRAME_TYPE_TECHNICOLOR*/
    {
        /* SDR output type : HI_DRV_DISP_TYPE_NORMAL */
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* SDR_Cert output type : HI_DRV_DISP_TYPE_SDR_CERT*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Auto output type : HI_DRV_DISP_TYPE_AUTO*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Dolby output type : HI_DRV_DISP_TYPE_DOLBY */
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10 output type : HI_DRV_DISP_TYPE_HDR10 */
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HDR10_Cert output type : HI_DRV_DISP_TYPE_HDR10_CERT*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* HLG output type : HI_DRV_DISP_TYPE_HLG*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Technicolor output type : HI_DRV_DISP_TYPE_TECHNICOLOR , Unsupport currently.*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},

        /* Follow first frame : HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME .*/
        {DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT, DRV_XDR_ENGINE_BUTT},
    }
};

HI_S32 XDR_SPECIFIC_GetXdrEngineList(HI_DRV_VIDEO_FRAME_TYPE_E enFrmType,
                                     HI_DRV_DISP_OUT_TYPE_E enOutType,
                                     HI_DRV_DISP_XDR_ENGINE_E *penXdrEngineList)
{
    HI_U32 u32Index = 0;

    if ((HI_DRV_VIDEO_FRAME_TYPE_BUTT <= enFrmType)
        || (HI_DRV_DISP_TYPE_BUTT <= enOutType))
    {
        return HI_ERR_DISP_INVALID_PARA;
    }

    if (HI_NULL == penXdrEngineList)
    {
        return HI_ERR_DISP_NULL_PTR;
    }

    for (u32Index = 0; u32Index < XDR_ENGINE_NUM; u32Index++)
    {
        penXdrEngineList[u32Index] = g_enXdrEngineList[enFrmType][enOutType][u32Index];
    }

    return HI_SUCCESS;
}

HI_S32 XDR_SPECIFIC_GetChipXdrCap(DRV_DISP_XDR_HARDWARE_CAP_S *pstXdrHardwareCap)
{
    if (HI_NULL == pstXdrHardwareCap)
    {
        return HI_ERR_DISP_NULL_PTR;
    }

    *pstXdrHardwareCap = g_stXdrHardwareCap;

    return HI_SUCCESS;
}

#endif

HI_BOOL XDR_SPECIFIC_CheckUserSetColorSpaceValid(HI_DRV_DISP_COLOR_SPACE_E enUserSetColorSpace)
{
    if (HI_DRV_DISP_COLOR_SPACE_BUTT <= enUserSetColorSpace)
    {
        HI_ERR_DISP("enUserSetColorSpace is invalid.\n");
        return HI_FALSE;
    }

    /* support BT709/BT2020/Auto. */
    return HI_TRUE;
}


#ifndef __DISP_PLATFORM_BOOT__
static HI_BOOL XDR_SPECIFIC_CheckVdmProcessConflic(HI_U32 u32MaxWinIndex, HI_BOOL *pbVdmConArray)
{
    HI_U32 u32Index = 0, u32Count = 0;

    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        if ((pbVdmConArray[u32Index])
            && (u32Index != u32MaxWinIndex))
        {
            u32Count++;
        }
    }

    /* conflic when v0(max win) need vdm process and v1(other wins) also need vdm process. */
    if (pbVdmConArray[u32MaxWinIndex])
    {
        if (u32Count)
        {
            return HI_TRUE;
        }
        else
        {
            return HI_FALSE;
        }
    }

    return HI_FALSE;

}

static HI_VOID XDR_SPECIFIC_ResetVdmArray(HI_BOOL *pbVdmArray)
{
    HI_U32 u32Index = 0;

    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        pbVdmArray[u32Index] = HI_FALSE;
    }

    return;
}

static HI_VOID XDR_SPECIFIC_MaskWinWhenConflictColorSpace(WIN_INFO_S *pstWinInfo,
                                       HI_DRV_COLOR_SPACE_E    enFmtOutColorCsc)
{
    if ((HI_DRV_CS_BT709_RGB_FULL == enFmtOutColorCsc)
        || (HI_DRV_CS_BT709_RGB_FULL == pstWinInfo->enOutCsc))
    {
        if (enFmtOutColorCsc != pstWinInfo->enOutCsc)
        {
            pstWinInfo->bRegionMute = HI_TRUE;
            pstWinInfo->bRegionEnable = HI_FALSE;
            pstWinInfo->enOutCsc = (HI_DRV_CS_BT709_RGB_FULL == enFmtOutColorCsc) ? HI_DRV_CS_BT709_RGB_FULL : HI_DRV_CS_BT709_YUV_LIMITED;
        }
    }

    return;
}


HI_VOID XDR_SPECIFIC_AdjustConfig(WIN_SHARE_INFO_S  *pstWinShareInfo,
                                  HI_U32             u32MaxWinIndex,
                                  HI_BOOL            *pbVdmProcess,
                                  HI_DRV_DISP_PROCESS_MODE_E  enLastDispProcessMode,
                                  HI_DRV_DISP_PROCESS_MODE_E  *penDispProcessMode,
                                  DISP_XDR_PLAY_INFO_S    *pstXdrFinalPlayInfo,
                                  DISP_XDR_PLAY_INFO_S    *pstXdrPrePlayInfo,
                                  HI_DRV_COLOR_SPACE_E    enFmtOutColorCsc)
{
    HI_U32 u32Index = 0;
    WIN_INFO_S *pstWinInfo = HI_NULL;
    HI_DRV_DISP_PROCESS_MODE_E enDispMode = enLastDispProcessMode;
    HI_BOOL  bHdrProcess = HI_FALSE;

    if (enDispMode >= HI_DRV_DISP_MODE_BUTT || u32MaxWinIndex >= WINDOW_MAX_NUMBER)
    {
        DISP_ERROR("enDispMode(%d) or u32MaxWinIndex(%d) outof range.\n", enDispMode, u32MaxWinIndex);
        return;
    }
    if (HI_NULL == pbVdmProcess)
    {
        DISP_ERROR("pbVdmProcess is null.\n");
        return;
    }

    //if conflict, choose max win's vdm process.
    if (XDR_SPECIFIC_CheckVdmProcessConflic(u32MaxWinIndex, pbVdmProcess))
    {
        XDR_SPECIFIC_ResetVdmArray(pbVdmProcess);
        pbVdmProcess[u32MaxWinIndex] = HI_TRUE;
    }

    //more than one win are not sdr in sdr out, it should go through hdr path.
    for (u32Index = 0; u32Index < WINDOW_MAX_NUMBER; u32Index++)
    {
        pstWinInfo = &pstWinShareInfo->stWinInfo[u32Index];

        if (HI_NULL != pstWinInfo->pCurrentFrame)
        {
            //if close hdr function. Force to set hdr frame as sdr, output type as sdr.inCs as BT.709.
            if (pstWinInfo->bCloseHdr)
            {
                pstWinInfo->pCurrentFrame->enSrcFrameType = HI_DRV_VIDEO_FRAME_TYPE_SDR;
                pstWinInfo->enOutType = HI_DRV_DISP_TYPE_NORMAL;
                pstWinInfo->enInCsc   = HI_DRV_CS_BT709_YUV_LIMITED;
                enDispMode = HI_DRV_DISP_PROCESS_MODE_SDR;
                pbVdmProcess[u32Index] = HI_FALSE;
            }

            if ((HI_DRV_VIDEO_FRAME_TYPE_SDR != pstWinInfo->pCurrentFrame->enSrcFrameType)
                || (HI_DRV_DISP_TYPE_NORMAL != pstWinInfo->enOutType))
            {
                bHdrProcess = HI_TRUE;
            }
        }

        XDR_SPECIFIC_MaskWinWhenConflictColorSpace(pstWinInfo, enFmtOutColorCsc);
    }

    if (HI_NULL == pstWinShareInfo->stWinInfo[u32MaxWinIndex].pCurrentFrame)
    {
        if ((HI_DRV_CS_BT709_RGB_FULL == enFmtOutColorCsc)
            || (HI_DRV_CS_BT709_RGB_FULL == pstXdrPrePlayInfo->enColorSpace))
        {
            pstWinShareInfo->stWinInfo[u32MaxWinIndex].enOutCsc =  enFmtOutColorCsc;
            pstXdrFinalPlayInfo->enColorSpace = enFmtOutColorCsc;
        }
        else
        {
            pstWinShareInfo->stWinInfo[u32MaxWinIndex].enOutCsc =  pstXdrPrePlayInfo->enColorSpace;
            pstXdrFinalPlayInfo->enColorSpace = pstXdrPrePlayInfo->enColorSpace;
        }

        pstWinShareInfo->stWinInfo[u32MaxWinIndex].enOutType = pstXdrPrePlayInfo->enOutType;
        pstXdrFinalPlayInfo->enOutType = pstXdrPrePlayInfo->enOutType;

        *penDispProcessMode = enDispMode;
    }
    else
    {
        pstXdrFinalPlayInfo->enColorSpace = pstWinShareInfo->stWinInfo[u32MaxWinIndex].enOutCsc;
        pstXdrFinalPlayInfo->enOutType = pstWinShareInfo->stWinInfo[u32MaxWinIndex].enOutType;
        *penDispProcessMode = (HI_TRUE == bHdrProcess) ? HI_DRV_DISP_PROCESS_MODE_HDR : HI_DRV_DISP_PROCESS_MODE_SDR;
    }

    return;
}

HI_BOOL XDR_SPECIFIC_CheckOutputSignalValid(HI_DRV_DISP_OUT_TYPE_E enDispType)
{
    HI_BOOL bValid = HI_FALSE;
    switch (enDispType)
    {
        case HI_DRV_DISP_TYPE_NORMAL:
        case HI_DRV_DISP_TYPE_HDR10:
        case HI_DRV_DISP_TYPE_HLG:
        case HI_DRV_DISP_TYPE_DOLBY:
        case HI_DRV_DISP_TYPE_SDR_CERT:
        case HI_DRV_DISP_TYPE_HDR10_CERT:
        case HI_DRV_DISP_TYPE_AUTO:
        case HI_DRV_DISP_TYPE_AUTO_FOLLOW_FIRSTFRAME:
            bValid = HI_TRUE;
            break;

            /* unsupport belowed output type currently.*/
        case HI_DRV_DISP_TYPE_TECHNICOLOR:
            bValid = HI_FALSE;
            break;
        default:
            bValid = HI_FALSE;
            break;
    }

    return bValid;

}

HI_VOID VDP_DRV_MaskAndBackupGfx(HI_U32 u32GfxLayerId, HI_U32 *pu32Alpha, HI_U32 *pu32MuteState)
{
    return;
}
HI_VOID VDP_DRV_UnmaskGfx(HI_U32 u32GfxLayerId, HI_U32 u32Alpha, HI_U32 u32MuteState)
{
    return;
}
HI_VOID VDP_DRV_SetGfxMixvBypassState(HI_U32 u32GfxLayerId, HI_BOOL bEnable)
{
    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

