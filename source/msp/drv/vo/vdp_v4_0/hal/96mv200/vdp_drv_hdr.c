#include "hi_type.h"
#include "vdp_define.h"
#include "vdp_drv_pq_hdr.h"
#include "vdp_drv_hdr.h"
#include "vdp_hal_hdr.h"
#include "vdp_hal_vid.h"
#include "vdp_hal_gfx.h"
#include "vdp_hal_chn.h"
#include "vdp_hal_mmu.h"

#include "vdp_drv_comm.h"
#include "vdp_drv_pq_zme.h"
#include "vdp_drv_vid.h"

#include "vdp_hal_ip_vdm.h"
#include "vdp_hal_ip_gdm.h"

extern  VDP_COEF_ADDR_S gstVdpCoefBufAddr;

HI_S32 VDP_DRV_SetHdrInit(XDP_HDR_CTRL_S *pstXdpHdrCtrl)
{
    //enable
    pstXdpHdrCtrl->bHdrEn            = 1;
    pstXdpHdrCtrl->bBlEn             = 1;
    pstXdpHdrCtrl->bElEn             = 1;
    pstXdpHdrCtrl->bComposerEn       = 1;
    pstXdpHdrCtrl->bEdrEn            = 0;
    pstXdpHdrCtrl->bEdrMdEn          = 0;
    pstXdpHdrCtrl->bEdrDsEn          = 0;

    //vdm
    pstXdpHdrCtrl->bVdmYuv2RgbEn     = 1;
    pstXdpHdrCtrl->bVdmV0Yuv2RgbEn   = 1;
    pstXdpHdrCtrl->bVdmV1Yuv2RgbEn   = 1;
    pstXdpHdrCtrl->bVdmNormEn        = 1;
    pstXdpHdrCtrl->bVdmDegmmEn       = 1;
    pstXdpHdrCtrl->bVdmRgb2LmsEn     = 1;
    pstXdpHdrCtrl->bVdmGmmEn         = 1;
    pstXdpHdrCtrl->bVdmV0GmmEn       = 1;
    pstXdpHdrCtrl->bVdmV1GmmEn       = 1;
    pstXdpHdrCtrl->bCvm1Lms2IptEn    = 1;
    pstXdpHdrCtrl->bVdmIptInEn       = 1;
    pstXdpHdrCtrl->bVcvmEn           = 1;
    pstXdpHdrCtrl->bVdmS2UEn         = 1;

    //gdm
    pstXdpHdrCtrl->bGdmEn            = 0;
    pstXdpHdrCtrl->bGdmRgb2LmsEn     = 0;
    pstXdpHdrCtrl->bGdmDegmmEn       = 0;
    pstXdpHdrCtrl->bGdmGmmEn         = 0;
    pstXdpHdrCtrl->bCvm2Lms2IptEn    = 0;
    pstXdpHdrCtrl->GcvmEn            = 1;
    pstXdpHdrCtrl->bGdmS2UEn         = 1;

    //output mapping
    pstXdpHdrCtrl->bOmapIptOutEn       = 0;
    pstXdpHdrCtrl->bOmapIpt2LmsEn      = 1;
    pstXdpHdrCtrl->bOmapLms2RgbEn      = 1;
    pstXdpHdrCtrl->bOmapRgb2YuvEn      = 1;
    pstXdpHdrCtrl->bOmapDenormEn       = 1;
    pstXdpHdrCtrl->bOmapDegmmEn        = 1;
    pstXdpHdrCtrl->bOmapGmmEn          = 1;
    pstXdpHdrCtrl->bOmapU2SEn          = 1;

    pstXdpHdrCtrl->bOmapSel = 0; //0: in DHD; 1:in VP0

    //mixg bypass
    pstXdpHdrCtrl->bMixvBypassEn      = 0;
    pstXdpHdrCtrl->bMixvBypassMode    = 0;
    pstXdpHdrCtrl->bMixvPremultEn     = 0;
    pstXdpHdrCtrl->bMixvDePremultEn   = 1;
    pstXdpHdrCtrl->bGfxPreMultEn = 0;

    pstXdpHdrCtrl->s32Cvm2Lms2IptOutDc[0] = 0;
    pstXdpHdrCtrl->s32Cvm2Lms2IptOutDc[1] = 0;
    pstXdpHdrCtrl->s32Cvm2Lms2IptOutDc[2] = 0;

    return HI_SUCCESS;

}

HI_S32 XDP_DRV_GetDolbySceneMode(XDP_LAYER_VID_INFO_S *pstInfoOut, XDP_DOLBY_CFG_MODE_E *penSceneMode)
{

    XDP_VIDEO_FRAME_TYPE_E enFrmType   = pstInfoOut->stXdpSrcCfg.enXdpViDeoFrameType;
    XDP_DISP_OUT_TYPE_E  enDisPlayMode = pstInfoOut->stXdpDispCfg.enDisPlayMode;

    switch (enDisPlayMode)
    {
        case XDP_DISP_TYPE_NORMAL:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_DOLBY_BL:
                case XDP_VIDEO_FRAME_TYPE_DOLBY_EL:
                    if (pstInfoOut->stXdpSrcCfg.bCompatibleSource == HI_TRUE)
                    {
                        *penSceneMode = XDP_DOVI_BC_IN_SDR_OUT;
                    }
                    else
                    {
                        *penSceneMode = XDP_DOVI_NBC_IN_SDR_OUT;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    *penSceneMode = XDP_HDR10_IN_SDR_OUT;
                    break;
                default:
                    VDP_PRINT("Not  frame.\n");
                    break;
            }
            break;
        case XDP_DISP_TYPE_SDR_CERT:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_DOLBY_BL:
                case XDP_VIDEO_FRAME_TYPE_DOLBY_EL:
                    if (pstInfoOut->stXdpSrcCfg.bCompatibleSource == HI_TRUE)
                    {
                        *penSceneMode = XDP_DOVI_BC_IN_SDR_OUT_CERT;
                    }
                    else
                    {
                        *penSceneMode = XDP_DOVI_NBC_IN_SDR_OUT_CERT;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    *penSceneMode = XDP_HDR10_IN_SDR_OUT_CERT;
                    break;
                default:
                    VDP_PRINT("Not  frame.\n");
                    break;
            }
            break;
        case XDP_DISP_TYPE_HDR10:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_DOLBY_BL:
                case XDP_VIDEO_FRAME_TYPE_DOLBY_EL:
                    if (pstInfoOut->stXdpSrcCfg.bCompatibleSource == HI_TRUE)
                    {
                        *penSceneMode = XDP_DOVI_BC_IN_HDR10_OUT;
                    }
                    else
                    {
                        *penSceneMode = XDP_DOVI_NBC_IN_HDR10_OUT;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    *penSceneMode = XDP_HDR10_IN_HDR10_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_SDR:
                    *penSceneMode = XDP_SDR_IN_HDR10_OUT;
                    break;
                default:
                    VDP_PRINT("Not  frame.\n");
                    break;
            }
            break;
        case XDP_DISP_TYPE_HDR10_CERT:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_DOLBY_BL:
                case XDP_VIDEO_FRAME_TYPE_DOLBY_EL:
                    if (pstInfoOut->stXdpSrcCfg.bCompatibleSource == HI_TRUE)
                    {
                        *penSceneMode = XDP_DOVI_BC_IN_HDR10_OUT_CERT;
                    }
                    else
                    {
                        *penSceneMode = XDP_DOVI_NBC_IN_HDR10_OUT_CERT;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    *penSceneMode = XDP_HDR10_IN_HDR10_OUT_CERT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_SDR:
                    *penSceneMode = XDP_SDR_IN_HDR10_OUT_CERT;
                    break;
                default:
                    VDP_PRINT("Not  frame.\n");
                    break;
            }
            break;
        case XDP_DISP_TYPE_DOLBY:
            switch (enFrmType)
            {
                case XDP_VIDEO_FRAME_TYPE_DOLBY_BL:
                case XDP_VIDEO_FRAME_TYPE_DOLBY_EL:
                    if (pstInfoOut->stXdpSrcCfg.bCompatibleSource == HI_TRUE)
                    {
                        *penSceneMode = XDP_DOVI_BC_IN_DOVI_IPT_OUT;
                    }
                    else
                    {
                        *penSceneMode = XDP_DOVI_NBC_IN_DOVI_IPT_OUT;
                    }
                    break;

                case XDP_VIDEO_FRAME_TYPE_HDR10:
                    *penSceneMode = XDP_HDR10_IN_DOLBY_OUT;
                    break;

                case XDP_VIDEO_FRAME_TYPE_SDR:
                    *penSceneMode = XDP_SDR_IN_DOLBY_OUT;
                    break;
                default:
                    VDP_PRINT("Not  frame.\n");
                    break;
            }
            break;
        default:
            *penSceneMode = HIHDR_BYPASS_MODE;
            break;
    }

    if (*penSceneMode >= XDP_HDR_CFG_MODE_BUTT)
    {
        VDP_PRINT("*penSceneMode arange Error !!! \n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_S32 VDP_DRV_GetHdrCfg(XDP_DOLBY_CFG_MODE_E  enSceneMode, VDP_FIXPT_MAIN_CFG_S *pstCompCfg, DmKsFxp_t *pstDmKs, XDP_HDR_CTRL_S *pstXdpHdrCtrl)
{

    //----------------------------------------------------------------------
    //IPT OUTPUT
    //----------------------------------------------------------------------
    if (enSceneMode == XDP_DOVI_BC_IPT_IN_DOVI_IPT_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 1;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 1;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    //----------------------------------------------------------------------
    //IPT OUTPUT
    //----------------------------------------------------------------------
    else if (enSceneMode == XDP_DOVI_BC_IN_DOVI_IPT_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 1;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 1;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;
        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_DOVI_NBC_IN_DOVI_IPT_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 1;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }

    //----------------------------------------------------------------------
    //HDR10 OUTPUT for certificate
    //----------------------------------------------------------------------
    else if (enSceneMode == XDP_DOVI_BC_IN_HDR10_OUT_CERT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 1;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;


        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_DOVI_NBC_IN_HDR10_OUT_CERT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 1;


        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_HDR10_IN_HDR10_OUT_CERT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 0;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 0;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;
        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    //----------------------------------------------------------------------
    //HDR10 OUTPUT for STB HDMI
    //----------------------------------------------------------------------
    else if (enSceneMode == XDP_DOVI_BC_IN_HDR10_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 1;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_DOVI_NBC_IN_HDR10_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;


        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_HDR10_IN_HDR10_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 0;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 0;
        pstXdpHdrCtrl->bEdrEn             = 1;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;

        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        pstXdpHdrCtrl->bOmapIptOutEn   = 0;
        pstXdpHdrCtrl->bMixvBypassMode    = 1;
        pstXdpHdrCtrl->bMixvBypassEn          = 0;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    //----------------------------------------------------------------------
    //SDR OUTPUT for certificate: IPT OUTPUT
    //----------------------------------------------------------------------
    else if (enSceneMode == XDP_DOVI_BC_IN_SDR_OUT_CERT)
    {
        //the same as VDP_HDR_DOVI_BC_IN_DOVI_IPT_OUT
        //printk("I am in XDP_DOVI_BC_IN_SDR_OUT_CERT\n");
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 1;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;
        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_DOVI_NBC_IN_SDR_OUT_CERT)
    {
        ///the same as VDP_HDR_DOVI_NBC_IN_DOVI_IPT_OUT)

        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 1;


        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_HDR10_IN_SDR_OUT_CERT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 0;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 0;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }

    else if (enSceneMode == XDP_SDR_IN_HDR10_OUT_CERT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 0;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 0;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_SDR_IN_HDR10_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 0;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 0;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;

        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;


        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }

    else if (enSceneMode == XDP_SDR_IN_DOLBY_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 0;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 0;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 1;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }

    else if (enSceneMode == XDP_HDR10_IN_DOLBY_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 0;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 0;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 1;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }

    //----------------------------------------------------------------------
    //SDR OUTPUT: YUV OUTPUT
    //----------------------------------------------------------------------
    else if (enSceneMode == XDP_DOVI_BC_IN_SDR_OUT)
    {
        //the same as VDP_HDR_DOVI_BC_IN_DOVI_IPT_OUT
        //printk("I am in XDP_DOVI_BC_IN_SDR_OUT_CERT\n");
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 1;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;
        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_DOVI_NBC_IN_SDR_OUT)
    {

        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;


        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_HDR10_IN_SDR_OUT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 0;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 0;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;

        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 1;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }

    //----------------------------------------------------------------------
    //SDR OUTPUT in HISI data path
    //to do....refer to above
    //----------------------------------------------------------------------
    else if (enSceneMode == XDP_DOVI_BC_IN_SDR_OUT_HISI)
    {
        pstXdpHdrCtrl->enOmapPosition         = 1;

        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 1;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 0;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 1;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_DOVI_NBC_IN_SDR_OUT_HISI)
    {
        pstXdpHdrCtrl->enOmapPosition         = 1;
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;

        //vdm
        pstXdpHdrCtrl->bVdmYuv2RgbEn      = 0;
        pstXdpHdrCtrl->bVdmV0Yuv2RgbEn = 0;
        pstXdpHdrCtrl->bVdmV1Yuv2RgbEn = 0;
        pstXdpHdrCtrl->bVdmNormEn     = 0;
        pstXdpHdrCtrl->bVdmDegmmEn    = 0;
        pstXdpHdrCtrl->bVdmRgb2LmsEn      = 0;
        pstXdpHdrCtrl->bVdmGmmEn          = 0;
        pstXdpHdrCtrl->bVdmV0GmmEn    = 0;
        pstXdpHdrCtrl->bVdmV1GmmEn    = 0;
        pstXdpHdrCtrl->bCvm1Lms2IptEn   = 0;
        pstXdpHdrCtrl->bVdmIptInEn    = 1;

        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 1;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 1;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }
    else if (enSceneMode == XDP_HDR10_IN_SDR_OUT_HISI)
    {
        pstXdpHdrCtrl->enOmapPosition         = 1;

        //enable
        pstXdpHdrCtrl->bBlEn              = 0;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 0;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 0;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 1;
        pstXdpHdrCtrl->bMixvBypassEn          = 0;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 1;
        pstXdpHdrCtrl->bGfxPreMultEn      = 1;
    }
    else  if (enSceneMode == XDP_DOVI_BC_IN_SDR_YUV_OUT_CERT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 1;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 1;

        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;

        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;
        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;




    }
    else if (enSceneMode == XDP_DOVI_NBC_IN_SDR_YUV_OUT_CERT)
    {
        //enable
        pstXdpHdrCtrl->bBlEn              = 1;
        pstXdpHdrCtrl->bElEn              = 0;
        pstXdpHdrCtrl->bComposerEn    = 1;
        pstXdpHdrCtrl->bEdrEn             = 0;
        pstXdpHdrCtrl->bEdrMdEn       = 0;
        pstXdpHdrCtrl->bEdrDsEn       = 1;


        //vdm
        pstXdpHdrCtrl->bVdmIptInEn    = 0;
        //output mapping
        pstXdpHdrCtrl->bOmapIptOutEn   = 0;

        pstXdpHdrCtrl->bMixvBypassMode    = 0;
        pstXdpHdrCtrl->bMixvBypassEn          = 1;
        pstXdpHdrCtrl->bMixvPremultEn   = 0;
        pstXdpHdrCtrl->bMixvDePremultEn   = 0;
        pstXdpHdrCtrl->bGfxPreMultEn      = 0;
    }

    pstXdpHdrCtrl->bElEn   = (pstCompCfg->disable_residual_flag == 1) ? 0 : 1;
    pstXdpHdrCtrl->bVcvmEn = (pstDmKs->ksTMap.tcLutDir == 2) ? 0 : 1;

    //  if ((pstXdpHdrCfgOut->bGfxEn == 1) || (pstXdpHdrCfgOut->bGfx1En == 1))
    {
        pstXdpHdrCtrl->bGcvmEn = HI_TRUE;
        //gdm
        if (pstXdpHdrCtrl->enOmapPosition == 0)
        {
            pstXdpHdrCtrl->bGdmEn = 1;
            pstXdpHdrCtrl->bGdmRgb2LmsEn = 1;
            pstXdpHdrCtrl->bGdmDegmmEn = 1;
            pstXdpHdrCtrl->bGdmGmmEn  = 1;
            pstXdpHdrCtrl->bCvm2Lms2IptEn   = 1;
            pstXdpHdrCtrl->bGcvmEn = (pstDmKs->ksTMapG.tcLutDir == 2) ? 0 : 1;
            pstXdpHdrCtrl->bGdmS2UEn = 1;
        }
        else
        {
            pstXdpHdrCtrl->bGdmEn           = HI_FALSE;
            pstXdpHdrCtrl->bGdmRgb2LmsEn    = HI_FALSE;
            pstXdpHdrCtrl->bGdmDegmmEn      = HI_FALSE;
            pstXdpHdrCtrl->bGdmGmmEn        = HI_FALSE;
            pstXdpHdrCtrl->bCvm2Lms2IptEn   = HI_FALSE;
            pstXdpHdrCtrl->bGcvmEn          = HI_FALSE;
            pstXdpHdrCtrl->bGdmS2UEn        = HI_TRUE;
        }


    }

    if (enSceneMode == XDP_HDR10_IN_HDR10_OUT_CERT
        || enSceneMode == XDP_HDR10_IN_HDR10_OUT
        || enSceneMode == XDP_HDR10_IN_SDR_OUT_CERT
        || enSceneMode == XDP_HDR10_IN_SDR_OUT
        || enSceneMode == XDP_HDR10_IN_SDR_OUT_HISI
        || enSceneMode == XDP_SDR_IN_HDR10_OUT
        || enSceneMode == XDP_SDR_IN_HDR10_OUT_CERT
        || enSceneMode == XDP_SDR_IN_DOLBY_OUT
        || enSceneMode == XDP_HDR10_IN_DOLBY_OUT
       )

    {
        pstDmKs->ksIMap.eotfParam.bdp        = 14;
        pstDmKs->ksIMap.eotfParam.range  = 16383;//(g_pKs.ksIMap.eotfParam.range)*16;
        pstDmKs->ksUs.minUs               = 0  ;
        pstDmKs->ksUs.maxUs               = 16383;
        pstDmKs->ksIMap.v3Yuv2RgbOffInRgb[0] *= 4;
        pstDmKs->ksIMap.v3Yuv2RgbOffInRgb[1] *= 4;
        pstDmKs->ksIMap.v3Yuv2RgbOffInRgb[2] *= 4;

    }


    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetGfxHdr(DmKsFxp_t *pstDmKs, XDP_HDR_CTRL_S *pstXdpHdrCtrl)
{
    VDP_HDR_SetGCvmLms2iptEnable          ( 1                        ) ;
    VDP_HDR_SetGCvmImapLms2ipt            ( pstDmKs->ksIMapG.m33Lms2Ipt         ) ;
    VDP_HDR_SetGCvmImapLms2iptscale2p     ( pstDmKs->ksIMapG.m33Lms2IptScale2P  + 1   ) ;
    VDP_HDR_SetGCvmImapLms2iptOutDc       ( pstXdpHdrCtrl->s32Cvm2Lms2IptOutDc      ) ;
    VDP_HDR_SetGDmImapLms2iptmin        (   0 - ((1 << 15) - 1)                  );
    VDP_HDR_SetGDmImapLms2iptmax        (     ((1 << 15) - 1)                  );

    VDP_HDR_SetGDmRgb2lmsEn           ( 1             ) ;
    VDP_HDR_SetGDmImapRgb2lms         ( pstDmKs->ksIMapG.m33Rgb2Lms  ) ;
    VDP_HDR_SetGDmImapRgb2lmsscale2p  ( pstDmKs->ksIMapG.m33Rgb2LmsScale2P    ) ;
    VDP_HDR_SetGDmImapRgb2lmsmin      ( 0            ) ;
    VDP_HDR_SetGDmImapRgb2lmsmax      ( ((1 << 25)  - 1)       ) ;
    VDP_HDR_SetGDmImapRgb2lmsOutDc    ( pstXdpHdrCtrl->s32Cvm2Lms2IptOutDc) ;

    //VDP_GFX_SetPreMultEnable          (VDP_LAYER_GFX0, pstXdpHdrCtrl->bGfxPreMultEn);
    //VDP_GP_SetDePreMultEnable         (VDP_LAYER_GP0, pstXdpHdrCtrl->bMixvDePremultEn);
    //VDP_GFX_MixvBypassEn              (pstXdpHdrCtrl->bMixvBypassEn);
    //VDP_GFX_MixvPremultEn             (pstXdpHdrCtrl->bMixvPremultEn);
    //VDP_GFX_MixvBypassMode            (pstXdpHdrCtrl->bMixvBypassMode);

    return HI_SUCCESS;

}



HI_S32 XDP_DRV_SetHdrCtrlInfo(XDP_HDR_CTRL_S *pstXdpHdrCtrl)
{
    //----------------------------------------------------------------------
    //enable setting
    //----------------------------------------------------------------------
    //VDM(V2020)
    VDP_HDR_SetVDmEn               (1);
    VDP_HDR_SetVDmYuv2rgbEn        (pstXdpHdrCtrl->bVdmYuv2RgbEn);
    VDP_HDR_SetVDmYuv2rgbV0En      (pstXdpHdrCtrl->bVdmV0Yuv2RgbEn);
    VDP_HDR_SetVDmYuv2rgbV1En      (pstXdpHdrCtrl->bVdmV1Yuv2RgbEn);

    VDP_HDR_SetVDmNormEn           (pstXdpHdrCtrl->bVdmNormEn);
    VDP_HDR_SetVDmDegammaEn        (pstXdpHdrCtrl->bVdmDegmmEn);
    VDP_HDR_SetVDmRgb2lmsEn        (pstXdpHdrCtrl->bVdmRgb2LmsEn);
    VDP_HDR_SetVDmGammaEn          (pstXdpHdrCtrl->bVdmGmmEn);
    VDP_HDR_SetVDmGammaV0En        (pstXdpHdrCtrl->bVdmV0GmmEn);
    VDP_HDR_SetVDmGammaV1En        (pstXdpHdrCtrl->bVdmV1GmmEn);

    //VCVM1
    VDP_HDR_SetVCvmEn              (pstXdpHdrCtrl->bVcvmEn ) ;
    VDP_HDR_SetGCvmEn              (pstXdpHdrCtrl->bGcvmEn ) ;
    VDP_HDR_SetVCvmLms2iptEn       (pstXdpHdrCtrl->bCvm1Lms2IptEn );
    VDP_HDR_SetVDmIptInSel         (pstXdpHdrCtrl->bVdmIptInEn );

    VDP_HDR_SetVCvmIpt2lmsEn       (pstXdpHdrCtrl->bOmapIpt2LmsEn );
    VDP_HDR_SetVCvmLms2rgbEn       (pstXdpHdrCtrl->bOmapLms2RgbEn );
    VDP_HDR_SetVCvmRgb2yuvEn       (pstXdpHdrCtrl->bOmapRgb2YuvEn );
    VDP_HDR_SetVCvmDenormEn        (pstXdpHdrCtrl->bOmapRgb2YuvEn   );
    VDP_HDR_SetIptOutSel           (pstXdpHdrCtrl->bOmapIptOutEn );

    VDP_HDR_SetVCvmDegammaEn       (pstXdpHdrCtrl->bOmapDegmmEn  ) ;
    VDP_HDR_SetVCvmMGammaEn        (pstXdpHdrCtrl->bOmapGmmEn    ) ;
    VDP_HDR_SetVCvmS2uEn           (pstXdpHdrCtrl->bVdmS2UEn);
    VDP_HDR_SetGCvmS2uEn           (pstXdpHdrCtrl->bGdmS2UEn);
    VDP_HDR_SetCvm1U2sEn           (pstXdpHdrCtrl->bOmapU2SEn);

    //GDM
    VDP_HDR_SetGDmEn               (pstXdpHdrCtrl->bGdmEn);
    VDP_HDR_SetGDmDegammaEn        (pstXdpHdrCtrl->bGdmDegmmEn);
    VDP_HDR_SetGDmRgb2lmsEn        (pstXdpHdrCtrl->bGdmRgb2LmsEn) ;
    VDP_HDR_SetGDmGammaEn          (pstXdpHdrCtrl->bGdmGmmEn);
    VDP_HDR_SetAuthEn              (1);

    //EDR
    VDP_HDR_SetDmEdrEn             (pstXdpHdrCtrl->bEdrEn);
    VDP_HDR_SetDmHdrMdEn           (pstXdpHdrCtrl->bEdrMdEn);
    VDP_HDR_SetDmHdrDsEn           (pstXdpHdrCtrl->bEdrDsEn);

    VDP_DISP_SetNxgDataSwapEnable (VDP_CHN_DHD0, pstXdpHdrCtrl->bEdrMdEn);

    //----------------------------------------------------------------------
    //data path setting
    //----------------------------------------------------------------------
    VDP_HDR_SetHdrEnable           (pstXdpHdrCtrl->bHdrEn);
    VDP_VID_SetComposerBlEn        (pstXdpHdrCtrl->bBlEn) ;
    VDP_VID_SetComposerElEn        (pstXdpHdrCtrl->bElEn) ;
    VDP_VP_SetIpt2YuvSel           (pstXdpHdrCtrl->enOmapPosition);
    VDP_GP_SetHdrSel               (1 );
    VDP_VP_SetHdrSel               (1 );

    VDP_DISP_SetHdmiMode       (VDP_CHN_DHD0, pstXdpHdrCtrl->bEdrDsEn);//1: no swap

    return HI_SUCCESS;

}


HI_S32 VDP_DRV_SetHdrCoef(DmKsFxp_t *pstDmKs)
{
    VDP_DRV_SetDmDegammaCoef(pstDmKs);
    VDP_DRV_SetDmgammaCoef(pstDmKs);
    VDP_DRV_SetDmCvmCoef(pstDmKs->ksTMap.tmLutI, pstDmKs->ksTMap.tmLutS, pstDmKs->ksTMap.smLutI, pstDmKs->ksTMap.smLutS);
    VDP_DRV_SetDmGCvmCoef(pstDmKs->ksTMapG.tmLutI, pstDmKs->ksTMapG.tmLutS, pstDmKs->ksTMapG.smLutI, pstDmKs->ksTMapG.smLutS);

    VDP_HDR_SetGdmParaUpd(VDP_LAYER_GP0, VDP_GP_PARA_HDR_DEGMM);
    VDP_HDR_SetGdmParaUpd(VDP_LAYER_GP0, VDP_GP_PARA_HDR_GMM);
    VDP_HDR_SetDmInputDegmmParaup  ();
    VDP_HDR_SetDmInputGammaParaup  ();
    VDP_HDR_SetDmCvmParaup         ();
    VDP_HDR_SetDmOutputDegmmParaup ();
    VDP_HDR_SetDmOutputGammaParaup ();
    VDP_HDR_SetGcvmCoefParaup();

    return HI_SUCCESS;

}


HI_S32 VDP_DRV_SetXdpRegUp(HI_VOID)
{
    VDP_VID_SetRegUp(VDP_LAYER_VID0);
    VDP_VID_SetRegUp(VDP_LAYER_VID1);

    VDP_GP_SetRegUp(VDP_LAYER_GFX0);
    VDP_VP_SetRegUp(VDP_LAYER_VP0);
    VDP_HDR_SetRegUp();
    VDP_DISP_SetRegUp (VDP_CHN_DHD0);
    return HI_SUCCESS;
}
HI_S32 VDP_DRV_CleanVidPQModule(HI_VOID)
{
    //----------------------------------------------------------------------
    //do not support the function in HDR mode
    //----------------------------------------------------------------------

    VDP_DISP_SetDispMode               (VDP_CHN_DHD0, VDP_DISP_MODE_2D);
    //----------------------------------------------------------------------
    //disable all PQ
    //----------------------------------------------------------------------

    VDP_VP_SetAcmEnable                (VDP_LAYER_VP0, HI_FALSE);
    VDP_VP_SetDciEnable                (VDP_LAYER_VP0, HI_FALSE);

    return HI_SUCCESS;

}

HI_S32 XDP_DRV_SetVid1LayerFdr(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    HI_U32 u32LeftEye  =  pstInfoOut->stXdpSysCfg.u32RegionNO;

    VDP_VID_SetLayerEnable (u32LayerId, HI_TRUE);

    VDP_VID_SetInDataFmt               (u32LayerId, pstInfoOut->stXdpSrcCfg.enElInFmt);

    VDP_VID_SetReadMode                (u32LayerId, VDP_RMODE_INTERFACE, VDP_RMODE_INTERFACE);

    VDP_VID_Set16RegionSmmuLumBypass   (u32LayerId, u32LeftEye, !pstInfoOut->stXdpSrcCfg.bSmmuEn);
    VDP_VID_Set16RegionSmmuChromBypass (u32LayerId, u32LeftEye, !pstInfoOut->stXdpSrcCfg.bSmmuEn);

    VDP_VID_SetDataWidth               (u32LayerId, pstInfoOut->stXdpSrcCfg.enElDataWidth);
    VDP_VID_SetNoSecFlag               (u32LayerId, !pstInfoOut->stXdpSysCfg.bSecureEn);

    VDP_VID_SetInReso                  (u32LayerId, pstInfoOut->stXdpSrcCfg.stElSrcRect);


    return HI_SUCCESS;



}


HI_S32 VDP_DRV_SetHdrFdr(XDP_LAYER_VID_INFO_S  *stXdpHdrCfg, XDP_HDR_CTRL_S *pstXdpHdrCtrl)
{
    XDP_DRV_SetVidLayerFdr(VDP_LAYER_VID0, stXdpHdrCfg);

    if (pstXdpHdrCtrl->bElEn)
    {
        XDP_DRV_SetVid1LayerFdr(VDP_LAYER_VID1, stXdpHdrCfg);
    }

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetHdrAddr(XDP_LAYER_VID_INFO_S  *stXdpHdrCfg, XDP_HDR_CTRL_S *pstXdpHdrCtrl)
{
    XDP_DRV_SetVidAddr(VDP_LAYER_VID0, stXdpHdrCfg);

    if (pstXdpHdrCtrl->bElEn)
    {
        stXdpHdrCfg->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumAddr = stXdpHdrCfg->stXdpSrcCfg.stAddr[VDP_ADDR_EL].u32LumAddr;
        stXdpHdrCfg->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmAddr = stXdpHdrCfg->stXdpSrcCfg.stAddr[VDP_ADDR_EL].u32ChmAddr;
        stXdpHdrCfg->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32LumStr  = stXdpHdrCfg->stXdpSrcCfg.stAddr[VDP_ADDR_EL].u32LumStr;
        stXdpHdrCfg->stXdpSrcCfg.stAddr[VDP_ADDR_DATA].u32ChmStr  = stXdpHdrCfg->stXdpSrcCfg.stAddr[VDP_ADDR_EL].u32ChmStr;

        XDP_DRV_SetVidAddr(VDP_LAYER_VID1, stXdpHdrCfg);
    }

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_GetHdrZmeCfg(XDP_LAYER_VID_INFO_S  *stXdpHdrCfgIn, XDP_LAYER_VID_INFO_S  *stXdpHdrCfgOut, XDP_HDR_CTRL_S *pstXdpHdrCtrl)
{

    XDP_DRV_GetVidZmeCfg(VDP_LAYER_VID0, stXdpHdrCfgIn, stXdpHdrCfgOut);

    if (pstXdpHdrCtrl->bElEn)
    {
        XDP_DRV_GetVidZmeCfg(VDP_LAYER_VID1, stXdpHdrCfgIn, stXdpHdrCfgOut);
    }

    stXdpHdrCfgOut->stXdpZmeCfg.stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = VDP_PROC_FMT_SP_420;

    return HI_SUCCESS;
}


HI_S32 VDP_DRV_SetVid1Zme(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    HI_BOOL bHdrElEn = HI_FALSE;
    /* if el.Reso == outReso, needn't to zme. */
    if ((pstInfoOut->stXdpSrcCfg.stElSrcRect.u32Wth == pstInfoOut->stXdpPositionCfg.stVideoRect.u32Wth)
        && (pstInfoOut->stXdpSrcCfg.stElSrcRect.u32Hgt == pstInfoOut->stXdpPositionCfg.stVideoRect.u32Hgt))
    {
        VDP_VID_SetHdrElZme            (VDP_LAYER_VID1, HI_FALSE);
        VDP_VID_SetZmeEnable           (VDP_LAYER_VID1, VDP_ZME_MODE_HOR, HI_FALSE);
        VDP_VID_SetZmeEnable           (VDP_LAYER_VID1, VDP_ZME_MODE_VER, HI_FALSE);
    }
    else
    {
        if ((pstInfoOut->stXdpSrcCfg.stElSrcRect.u32Wth == pstInfoOut->stXdpPositionCfg.stVideoRect.u32Wth / 2)
        && (pstInfoOut->stXdpSrcCfg.stElSrcRect.u32Hgt == pstInfoOut->stXdpPositionCfg.stVideoRect.u32Hgt / 2))
        {
            /* use dolby cert zme. */
            bHdrElEn = HI_TRUE;
        }
        else
        {
            bHdrElEn = HI_FALSE;
        }
        VDP_VID_SetHdrElZme            (VDP_LAYER_VID1, bHdrElEn);

        VDP_VID_SetZmeEnable           (VDP_LAYER_VID1, VDP_ZME_MODE_HOR, HI_TRUE);
        VDP_VID_SetZmeEnable           (VDP_LAYER_VID1, VDP_ZME_MODE_VER, HI_TRUE);

        VDP_VID_SetZmeInFmt            (VDP_LAYER_VID1, VDP_PROC_FMT_SP_420);
        VDP_VID_SetZmeOutFmt           (VDP_LAYER_VID1, VDP_PROC_FMT_SP_420);

        VDP_VID_SetZmePhase            (VDP_LAYER_VID1, VDP_ZME_MODE_HOR, 0);
        VDP_VID_SetZmePhase            (VDP_LAYER_VID1, VDP_ZME_MODE_VER, 0);

        VDP_VID_SetZmeFirEnable        (VDP_LAYER_VID1, VDP_ZME_MODE_HOR, HI_TRUE);
        VDP_VID_SetZmeFirEnable        (VDP_LAYER_VID1, VDP_ZME_MODE_VER, HI_TRUE);
        if ((0 == pstInfoOut->stXdpPositionCfg.stVideoRect.u32Wth)
            || (0 == pstInfoOut->stXdpPositionCfg.stVideoRect.u32Hgt))
        {
            VDP_PRINT("Denominator Is Zero !!!!\n");
            return HI_FAILURE;
        }

        VDP_VID_SetZmeHorRatio         (VDP_LAYER_VID1, (pstInfoOut->stXdpSrcCfg.stElSrcRect.u32Wth / 2 * ZME_HPREC) / pstInfoOut->stXdpPositionCfg.stVideoRect.u32Wth * 2);
        VDP_VID_SetZmeVerRatio         (VDP_LAYER_VID1, (pstInfoOut->stXdpSrcCfg.stElSrcRect.u32Hgt / 2 * ZME_VPREC) / pstInfoOut->stXdpPositionCfg.stVideoRect.u32Hgt * 2);

        if(HI_FALSE == bHdrElEn)
        {
            if (HI_NULL == gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_H]
                || HI_NULL == gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_V]
                || HI_NULL == gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP])
            {
                VDP_PRINT("V1 ZME  PTR Is NUll Please check it !!! \n");
                return HI_FAILURE;
            }

            VDP_GetVdpZmeCoef(HI_PQ_ZME_COEF_E1, HI_PQ_ZME_COEF_TYPE_LH, HI_PQ_ZME_TAP_8T32P, (HI_S16 *)gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]);
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_8LH, HI_PQ_ZME_COEF_TYPE_LH, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_H]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

            VDP_GetVdpZmeCoef(HI_PQ_ZME_COEF_E1, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_H] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

            VDP_GetVdpZmeCoef(HI_PQ_ZME_COEF_E1, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_V]), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

            VDP_GetVdpZmeCoef(HI_PQ_ZME_COEF_E1, HI_PQ_ZME_COEF_TYPE_CV, HI_PQ_ZME_TAP_4T32P, (HI_S16 *)(gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));
            DRV_PQ_SetVdpZmeCoef(VDP_ZOOM_TAP_4CH, HI_PQ_ZME_COEF_TYPE_CV, (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_V1_V] + 256), (gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_ZME_TMP]));

            VDP_VID_SetZmeCoefAddr(u32LayerId, VDP_VID_PARA_ZME_HOR , (gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_ZME_V1_H]));
            VDP_VID_SetZmeCoefAddr(u32LayerId, VDP_VID_PARA_ZME_VER , (gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_ZME_V1_V]));
            VDP_VID_SetParaUpd(u32LayerId, VDP_VID_PARA_ZME_HOR);
            VDP_VID_SetParaUpd(u32LayerId, VDP_VID_PARA_ZME_VER);
        }
    }

    return HI_SUCCESS;

}


HI_S32 VDP_DRV_SetHdrZmeCfg(XDP_LAYER_VID_INFO_S  *stXdpHdrCfgOut, XDP_HDR_CTRL_S *pstXdpHdrCtrl)
{
    XDP_DRV_SetVidZme (VDP_LAYER_VID0, stXdpHdrCfgOut);

    if (HI_TRUE == pstXdpHdrCtrl->bElEn)
    {
        VDP_DRV_SetVid1Zme(VDP_LAYER_VID1, stXdpHdrCfgOut);
    }

    return HI_SUCCESS;
}
HI_S32 XDP_DRV_SetVidElReso(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{

    VDP_VID_SetInReso                  (u32LayerId, pstInfoOut->stXdpSrcCfg.stElSrcRect);
    VDP_VID_SetOutReso(u32LayerId, pstInfoOut->stXdpPositionCfg.stVideoRect);
    VDP_VID_SetSrOutReso (u32LayerId, pstInfoOut->stXdpPositionCfg.stVideoRect);
    VDP_VID_SetVideoPos                (u32LayerId, pstInfoOut->stXdpPositionCfg.stVideoRect);
    VDP_VID_SetDispPos                 (u32LayerId, pstInfoOut->stXdpPositionCfg.stVideoRect);


    return HI_SUCCESS;

}

HI_S32 VDP_DRV_SetHdrVidReso(XDP_LAYER_VID_INFO_S  *stXdpHdrCfgOut, XDP_HDR_CTRL_S *pstXdpHdrCtrl)
{

    XDP_DRV_SetVidReso(VDP_LAYER_VID0, stXdpHdrCfgOut);

    if (pstXdpHdrCtrl->bElEn)
    {
        XDP_DRV_SetVidElReso(VDP_LAYER_VID1, stXdpHdrCfgOut);
    }

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetHdrHdmiMetadata(HI_U8 *pu8HeadData, HI_U32 u32MdLen, HI_U8 *pu8MdBuf)
{

    HI_U32 no_md     = pu8HeadData[0] & 0x1;
    HI_U32 md_ver    = (pu8HeadData[0] >> 1) & 0x7;
    HI_U32 md_type   = (pu8HeadData[0] >> 4) & 0x3;
    HI_U32 md_id     = pu8HeadData[1];
    HI_U32 md_eos    = pu8HeadData[2] & 0x1;

    VDP_HDR_SetDmHdrNoMd           ( no_md   );
    VDP_HDR_SetDmHdrMdVer          ( md_ver  );
    VDP_HDR_SetDmHdrMdType         ( md_type );
    VDP_HDR_SetDmHdrMdId           ( md_id   );
    VDP_HDR_SetDmHdrMdEos          ( md_eos  );

    memcpy((HI_VOID *)gstVdpCoefBufAddr.pu8CoefVirAddr[VDP_COEF_BUF_HDR_METADATA], (HI_VOID *)pu8MdBuf, u32MdLen);

    VDP_HDR_SetDmHdrMdLen          ( u32MdLen );
    VDP_HDR_SetDmMetadataCoefAddr  ( gstVdpCoefBufAddr.u32CoefPhyAddr[VDP_COEF_BUF_HDR_METADATA]);
    VDP_HDR_SetDmMdParaup          ();

    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetComposer(VDP_FIXPT_MAIN_CFG_S *pstCompCfg)
{
    HI_U32 ii = 0, jj = 0, kk = 0;

    HI_S32 poly_coef[3][8][3];
    HI_S32 mmr_coef[2][22];
    HI_S64 mmr_coef_tmp;
    HI_S32 nlq_coef[3][3];
    HI_U32 pivot_value[3][9];
    HI_U32 poly_order[3][8];

    //----------------------------------------------------------------------
    // calc the config
    //----------------------------------------------------------------------
    for (kk = 0; kk < 3; kk++)
    {
        for (ii = 0; ii < 8; ii++)
        {
            for (jj = 0; jj < 3; jj++)
            {
                poly_coef[kk][ii][jj] = pstCompCfg->poly_coef_int[kk][ii][jj] << 23 | pstCompCfg->poly_coef[kk][ii][jj] << (23 - pstCompCfg ->coefficient_log2_denom);
            }
        }
    }

    for (ii = 0; ii < 2; ii++)
    {
        for (jj = 0; jj < 22; jj++)
        {
            if (pstCompCfg ->coefficient_log2_denom <= 14)
            {
                mmr_coef[ii][jj] = pstCompCfg->MMR_coef_int[ii][jj] << 14 | pstCompCfg->MMR_coef[ii][jj] << (14 - pstCompCfg ->coefficient_log2_denom);
            }
            else
            {
                mmr_coef_tmp = ((((HI_S64)pstCompCfg->MMR_coef_int[ii][jj]) << pstCompCfg ->coefficient_log2_denom) | pstCompCfg->MMR_coef[ii][jj]) ;
                mmr_coef_tmp = mmr_coef_tmp >> (pstCompCfg ->coefficient_log2_denom - 14) ;
                mmr_coef[ii][jj] = (HI_S32)mmr_coef_tmp ;
            }
        }
    }

    for (ii = 0; ii < 3; ii++)
    {
        for (jj = 0; jj < 3; jj++)
        {
            nlq_coef[ii][jj] = pstCompCfg->NLQ_coeff_int[ii][jj] << 23 | pstCompCfg->NLQ_coeff[ii][jj] << (23 - pstCompCfg ->coefficient_log2_denom) ;

        }
    }

    for (ii = 0; ii < 3; ii++)
    {
        for (jj = 0; jj < 9; jj++)
        {
            if (pstCompCfg ->rpu_BL_bit_depth == 8)
            {
                pivot_value[ii][jj] = pstCompCfg->pivot_value[ii][jj] << 2;
            }
            else
            {
                pivot_value[ii][jj] = pstCompCfg->pivot_value[ii][jj];
            }
        }
    }

    for (ii = 0; ii < 3; ii++)
    {
        for (jj = 0; jj < 8; jj++)
        {
            poly_order[ii][jj] = pstCompCfg->poly_order[ii][jj] - 1;
        }
    }
#if 0
    //info print
    printk("pstCompCfg ->rpu_VDR_bit_depth      == %d\n", pstCompCfg->rpu_VDR_bit_depth     );
    printk("pstCompCfg ->rpu_BL_bit_depth       == %d\n", pstCompCfg->rpu_BL_bit_depth       );
    printk("pstCompCfg ->rpu_EL_bit_depth       == %d\n", pstCompCfg->rpu_EL_bit_depth       );
    printk("pstCompCfg ->coefficient_log2_denom  == %d\n", pstCompCfg->coefficient_log2_denom    );
    printk("pstCompCfg ->num_pivots[0]          == %d\n", pstCompCfg->num_pivots[0]        );
    printk("pstCompCfg ->num_pivots[1]          == %d\n", pstCompCfg->num_pivots[1]        );
    printk("pstCompCfg ->num_pivots[2]          == %d\n", pstCompCfg->num_pivots[2]        );
    printk("pstCompCfg ->mapping_idc[0]         == %d\n", pstCompCfg->mapping_idc[0]      );
    printk("pstCompCfg ->mapping_idc[1]         == %d\n", pstCompCfg->mapping_idc[1]      );
    printk("pstCompCfg ->mapping_idc[2]         == %d\n", pstCompCfg->mapping_idc[2]      );
    printk("pstCompCfg ->MMR_order[0]           == %d\n", pstCompCfg->MMR_order[0]          );
    printk("pstCompCfg ->MMR_order[1]           == %d\n", pstCompCfg->MMR_order[1]          );
    printk("pstCompCfg ->NLQ_method_idc         == %d\n", pstCompCfg->NLQ_method_idc      );
    printk("pstCompCfg ->disable_residual_flag   == %d\n", pstCompCfg->disable_residual_flag );
    printk("pstCompCfg ->NLQ_offset[0]          == %d\n", pstCompCfg->NLQ_offset[0]        );
    printk("pstCompCfg ->NLQ_offset[1]          == %d\n", pstCompCfg->NLQ_offset[1]        );
    printk("pstCompCfg ->NLQ_offset[2]          == %d\n", pstCompCfg->NLQ_offset[2]        );
    printk("pstCompCfg->pivot_value[0][0]       == %d\n", pstCompCfg->pivot_value[0][0]          );
    printk("pstCompCfg->pivot_value[0][1]       == %d\n", pstCompCfg->pivot_value[0][1]          );
    printk("pstCompCfg->pivot_value[0][2]       == %d\n", pstCompCfg->pivot_value[0][2]          );
    printk("pstCompCfg->pivot_value[0][3]       == %d\n", pstCompCfg->pivot_value[0][3]          );
    printk("pstCompCfg->pivot_value[0][4]       == %d\n", pstCompCfg->pivot_value[0][4]          );
    printk("pstCompCfg->pivot_value[0][5]       == %d\n", pstCompCfg->pivot_value[0][5]          );
    printk("pstCompCfg->pivot_value[0][6]       == %d\n", pstCompCfg->pivot_value[0][6]          );
    printk("pstCompCfg->pivot_value[0][7]       == %d\n", pstCompCfg->pivot_value[0][7]          );
    printk("pstCompCfg->pivot_value[0][8]       == %d\n", pstCompCfg->pivot_value[0][8]          );
    printk("pstCompCfg->pivot_value[1][0]       == %d\n", pstCompCfg->pivot_value[1][0]          );
    printk("pstCompCfg->pivot_value[1][1]       == %d\n", pstCompCfg->pivot_value[1][1]          );
    printk("pstCompCfg->pivot_value[1][2]       == %d\n", pstCompCfg->pivot_value[1][2]          );
    printk("pstCompCfg->pivot_value[1][3]       == %d\n", pstCompCfg->pivot_value[1][3]          );
    printk("pstCompCfg->pivot_value[1][4]       == %d\n", pstCompCfg->pivot_value[1][4]          );
    printk("pstCompCfg->pivot_value[2][0]       == %d\n", pstCompCfg->pivot_value[2][0]          );
    printk("pstCompCfg->pivot_value[2][1]       == %d\n", pstCompCfg->pivot_value[2][1]          );
    printk("pstCompCfg->pivot_value[2][2]       == %d\n", pstCompCfg->pivot_value[2][2]          );
    printk("pstCompCfg->pivot_value[2][3]       == %d\n", pstCompCfg->pivot_value[2][3]          );
    printk("pstCompCfg->pivot_value[2][4]       == %d\n", pstCompCfg->pivot_value[2][4]          );


    for (ii = 0; ii < 3; ii++)
    {
        for (jj = 0; jj < 8; jj++)
        {
            printk("pstCompCfg ->poly_order[%d][%d] = %d\n", ii, jj, pstCompCfg->poly_order[ii][jj]);
        }
    }

    for (kk = 0; kk < 3; kk++)
    {
        for (ii = 0; ii < 8; ii++)
        {
            for (jj = 0; jj < 3; jj++)
            {

                printk("pstCompCfg ->poly_coef_int[%d][%d][%d] = %08x\n", kk, ii, jj, pstCompCfg->poly_coef_int[kk][ii][jj]);
                printk("pstCompCfg ->poly_coef[%d][%d][%d] = %08x\n", kk, ii, jj, pstCompCfg->poly_coef[kk][ii][jj]);
                printk("poly_coef[%d][%d][%d] = %08x\n", kk, ii, jj, poly_coef[kk][ii][jj]);

            }
        }
    }

    for (ii = 0; ii < 2; ii++)
    {
        for (jj = 0; jj < 22; jj++)
        {
            printk("pstCompCfg ->MMR_coef_int[%d][%d] = %08x\n", ii, jj, pstCompCfg->MMR_coef_int[ii][jj]);
            printk("pstCompCfg ->MMR_coef[%d][%d] = %08x\n", ii, jj, pstCompCfg->MMR_coef[ii][jj]);
            printk("mmr_coef[%d][%d] = %08x\n", ii, jj, mmr_coef[ii][jj]);
        }
    }

    for (ii = 0; ii < 3; ii++)
    {
        for (jj = 0; jj < 3; jj++)
        {
            printk("pstCompCfg->NLQ_coeff[%d][%d] = %08x\n", ii, jj, pstCompCfg->NLQ_coeff[ii][jj]);
            printk("nlq_coef[%d][%d] = %08x\n", ii, jj, nlq_coef[ii][jj]);
        }
    }


#endif

    VDP_VID_SetComposerElUpsampleEn      ( pstCompCfg->el_spatial_resampling_filter_flag ) ;
    VDP_VID_SetComposerBlBitDepth        ( (pstCompCfg->rpu_BL_bit_depth - 8) / 2 ) ;
    VDP_VID_SetComposerElBitDepth        ( (pstCompCfg->rpu_EL_bit_depth - 8) / 2 ) ;
    VDP_VID_SetComposerVdrBitDepth       ( (pstCompCfg->rpu_VDR_bit_depth - 12) / 2 ) ;
    VDP_VID_SetComposerBlNumPivotsY      ( pstCompCfg->num_pivots[0] - 2 ) ;
    VDP_VID_SetComposerBlNumPivotsU      ( pstCompCfg->num_pivots[1] - 2 ) ;
    VDP_VID_SetComposerBlNumPivotsV      ( pstCompCfg->num_pivots[2] - 2 ) ;
    VDP_VID_SetComposerBlPolyPivotValueY ( pivot_value[0]) ;
    VDP_VID_SetComposerBlPolyPivotValueU ( pivot_value[1]) ;
    VDP_VID_SetComposerBlPolyPivotValueV ( pivot_value[2]) ;
    VDP_VID_SetComposerBlPolyOrderY      ( poly_order[0] ) ;
    VDP_VID_SetComposerBlPolyOrderU      ( poly_order[1] ) ;
    VDP_VID_SetComposerBlPolyOrderV      ( poly_order[2] ) ;
    VDP_VID_SetComposerBlPolyCoefY       ( poly_coef[0] ) ;
    VDP_VID_SetComposerBlPolyCoefU       ( poly_coef[1] ) ;
    VDP_VID_SetComposerBlPolyCoefV       ( poly_coef[2] ) ;
    VDP_VID_SetComposerMappingIdcU       ( pstCompCfg->mapping_idc[1] ) ;
    VDP_VID_SetComposerMappingIdcV       ( pstCompCfg->mapping_idc[2] ) ;
    VDP_VID_SetComposerBlMmrOrderU       ( pstCompCfg->MMR_order[0] - 1 ) ;
    VDP_VID_SetComposerBlMmrOrderV       ( pstCompCfg->MMR_order[1] - 1 ) ;
    VDP_VID_SetComposerBlMmrCoefU        ( mmr_coef[0] ) ;
    VDP_VID_SetComposerBlMmrCoefV        ( mmr_coef[1] ) ;
    VDP_VID_SetComposerElEn              ( !pstCompCfg->disable_residual_flag ) ;
    VDP_VID_SetComposerElNldqOffsetY     ( pstCompCfg->NLQ_offset[0] ) ;
    VDP_VID_SetComposerElNldqOffsetU     ( pstCompCfg->NLQ_offset[1] ) ;
    VDP_VID_SetComposerElNldqOffsetV     ( pstCompCfg->NLQ_offset[2] ) ;
    VDP_VID_SetComposerElNldqCoefY       ( nlq_coef[0] ) ;
    VDP_VID_SetComposerElNldqCoefU       ( nlq_coef[1] ) ;
    VDP_VID_SetComposerElNldqCoefV       ( nlq_coef[2] ) ;

    VDP_VID_SetComposerBlEn              ( 1 );

    if (pstCompCfg->el_spatial_resampling_filter_flag == 1)
    {
        VDP_VID_SetHdrElZme(VDP_LAYER_VID1, HI_TRUE);
    }
    else
    {
        VDP_VID_SetHdrElZme(VDP_LAYER_VID1, HI_FALSE);
    }

    return HI_SUCCESS;
}



HI_S32 VDP_DRV_SetVdm(DmKsFxp_t *pstDmKs)
{
    HI_U32 u32InBdp;
    HI_U32 u32OutBdp;
    HI_U32 u32InClr;
    HI_U32 u32OutClr;

#if 0
    //#if HDR_DEBUG

    printk("(HI_S32)pstDmKs->ksTMap.tcLutDir                    == %d\n", (HI_S32)pstDmKs->ksTMap.tcLutDir);
    printk("(HI_S32)pstDmKs->rowPitchNum                    == %d\n", (HI_S32)pstDmKs->rowPitchNum                 );
    printk("(HI_U32)pstDmKs->rowPitchNum                    == %d\n", (HI_U32)pstDmKs->rowPitchNum                 );
    printk("(HI_U32)pstDmKs->rowPitchNum                    == %d\n", (HI_U32)pstDmKs->rowPitchNum                 );
    printk("(HI_U32)pstDmKs->rowPitchNum                    == %d\n", (HI_U32)pstDmKs->rowPitchNum                 );

    printk("(HI_S32)pstDmKs->ksUs.chrmIn                == %d\n", (HI_S32)pstDmKs->ksUs.chrmIn              );
    printk("(HI_S32)pstDmKs->ksUs.minUs                 == %d\n", (HI_S32)pstDmKs->ksUs.minUs                   );
    printk("(HI_S32)pstDmKs->ksUs.maxUs                 == %d\n", (HI_S32)pstDmKs->ksUs.maxUs                   );

    printk("(HI_S32)pstDmKs->ksDs.maxDs                 == %d\n", (HI_S32)pstDmKs->ksDs.maxDs);
    printk("(HI_S32)pstDmKs->ksDs.maxDs                 == %d\n", (HI_S32)pstDmKs->ksDs.minDs);
    printk("(HI_S32)pstDmKs->ksDs.maxDs                 == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDsRadius);
    printk("(HI_S32)pstDmKs->ksDs.maxDs                 == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDsScale2P);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[0]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[1]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[2]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[3]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[4]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[5]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[6]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[7]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[8]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[9]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[10]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[11]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[12]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[13]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[14]);
    printk("(HI_S32)pstDmKs->ksDs.filterUvColDs_m[0] == %d\n", (HI_S32)pstDmKs->ksDs.filterUvColDs_m[15]);

#if 0
    printk("(HI_S32)pstDmKs->ksUds.chrmIn               == %d\n", (HI_S32)pstDmKs->ksUds.chrmIn            );
    printk("(HI_S32)pstDmKs->ksUds.chrmOut              == %d\n", (HI_S32)pstDmKs->ksUds.chrmOut          );
    printk("(HI_S32)pstDmKs->ksUds.minUs                    == %d\n", (HI_S32)pstDmKs->ksUds.minUs                 );
    printk("(HI_S32)pstDmKs->ksUds.maxUs                    == %d\n", (HI_S32)pstDmKs->ksUds.maxUs                 );
    printk("(HI_S32)pstDmKs->ksUds.minDs                    == %d\n", (HI_S32)pstDmKs->ksUds.minDs                 );
    printk("(HI_S32)pstDmKs->ksUds.maxDs                    == %d\n", (HI_S32)pstDmKs->ksUds.maxDs                 );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUsHalfSize  == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUsHalfSize );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUsScale2P   == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUsScale2P  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[0]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[0]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[1]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[1]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[2]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[2]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[3]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[3]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[4]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[4]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[5]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[5]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[6]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[6]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[7]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs0_m[7]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[0]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[0]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[1]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[1]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[2]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[2]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[3]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[3]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[4]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[4]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[5]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[5]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[6]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[6]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[7]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvRowUs1_m[7]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUsHalfSize  == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUsHalfSize );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUsScale2P   == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUsScale2P  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUs_m[0]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUs_m[0]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUs_m[1]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUs_m[1]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUs_m[2]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUs_m[2]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUs_m[3]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUs_m[3]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUs_m[4]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUs_m[4]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUs_m[5]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUs_m[5]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUs_m[6]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUs_m[6]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColUs_m[7]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColUs_m[7]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDsRadius    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDsRadius    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDsScale2P   == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDsScale2P  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[0]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[0]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[1]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[1]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[2]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[2]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[3]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[3]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[4]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[4]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[5]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[5]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[6]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[6]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[7]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[7]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[8]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[8]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[9]     == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[9]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[10]    == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[10]    );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[11]   == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[11]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[12]   == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[12]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[13]   == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[13]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[14]   == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[14]  );
    printk("(HI_S32)pstDmKs->ksUds.filterUvColDs_m[15]   == %d\n", (HI_S32)pstDmKs->ksUds.filterUvColDs_m[15]  );
#endif
    printk("(HI_S32)pstDmKs->ksDmCtrl.mainIn               == %d\n", (HI_S32)pstDmKs->ksDmCtrl.mainIn           );
    printk("(HI_S32)pstDmKs->ksDmCtrl.prf              == %d\n", (HI_S32)pstDmKs->ksDmCtrl.prf             );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.rowNum          == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.rowNum          );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.colNum          == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.colNum          );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.dtp             == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.dtp           );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.weav            == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.weav         );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.loc             == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.loc           );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.bdp             == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.bdp           );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.chrm            == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.chrm         );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.clr             == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.clr           );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.rowPitch        == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.rowPitch      );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.colPitch        == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.colPitch      );
    printk("(HI_S32)pstDmKs->ksFrmFmtI.rowPitchC           == %d\n", (HI_S32)pstDmKs->ksFrmFmtI.rowPitchC        );
    printk("(HI_S32)pstDmKs->ksIMap.clr                == %d\n", (HI_S32)pstDmKs->ksIMap.clr            );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2RgbScale2P    == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2RgbScale2P   );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[0][0]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[0][0]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[0][1]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[0][1]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[0][2]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[0][2]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[1][0]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[1][0]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[1][1]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[1][1]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[1][2]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[1][2]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[2][0]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[2][0]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[2][1]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[2][1]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[2][2]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Yuv2Rgb[2][2]     );
    printk("(HI_S32)pstDmKs->ksIMap.v3Yuv2RgbOffInRgb[0] == %d\n", (HI_S32)pstDmKs->ksIMap.v3Yuv2RgbOffInRgb[0]);
    printk("(HI_S32)pstDmKs->ksIMap.v3Yuv2RgbOffInRgb[1] == %d\n", (HI_S32)pstDmKs->ksIMap.v3Yuv2RgbOffInRgb[1]);
    printk("(HI_S32)pstDmKs->ksIMap.v3Yuv2RgbOffInRgb[2] == %d\n", (HI_S32)pstDmKs->ksIMap.v3Yuv2RgbOffInRgb[2]);
    printk("(HI_U32)pstDmKs->ksIMap.eotfParam.rangeMin   == %d\n", (HI_U32)pstDmKs->ksIMap.eotfParam.rangeMin  );
    printk("(HI_U32)pstDmKs->ksIMap.eotfParam.range    == %d\n", (HI_U32)pstDmKs->ksIMap.eotfParam.range   );
    printk("(HI_U32)pstDmKs->ksIMap.eotfParam.rangeInv   == %d\n", (HI_U32)pstDmKs->ksIMap.eotfParam.rangeInv  );
    printk("(HI_U32)pstDmKs->ksIMap.eotfParam.bdp      == %d\n", (HI_U32)pstDmKs->ksIMap.eotfParam.bdp   );
    printk("(HI_U32)pstDmKs->ksIMap.eotfParam.eotf     == %d\n", (HI_U32)pstDmKs->ksIMap.eotfParam.eotf     );
#if 0
    printk("(HI_U32)pstDmKs->ksIMap.eotfParam.gamma    == %d\n", (HI_U32)pstDmKs->ksIMap.eotfParam.gamma   );
    printk("(HI_U32)pstDmKs->ksIMap.eotfParam.a        == %d\n", (HI_U32)pstDmKs->ksIMap.eotfParam.a      );
    printk("(HI_U32)pstDmKs->ksIMap.eotfParam.b        == %d\n", (HI_U32)pstDmKs->ksIMap.eotfParam.b      );
    printk("(HI_U32)pstDmKs->ksIMap.eotfParam.g        == %d\n", (HI_U32)pstDmKs->ksIMap.eotfParam.g      );
#endif
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2LmsScale2P    == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2LmsScale2P   );
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[0][0]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[0][0]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[0][1]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[0][1]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[0][2]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[0][2]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[1][0]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[1][0]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[1][1]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[1][1]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[1][2]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[1][2]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[2][0]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[2][0]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[2][1]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[2][1]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[2][2]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Rgb2Lms[2][2]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2IptScale2P    == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2IptScale2P   );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[0][0]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[0][0]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[0][1]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[0][1]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[0][2]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[0][2]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[1][0]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[1][0]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[1][1]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[1][1]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[1][2]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[1][2]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[2][0]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[2][0]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[2][1]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[2][1]     );
    printk("(HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[2][2]       == %d\n", (HI_S32)pstDmKs->ksIMap.m33Lms2Ipt[2][2]     );
    printk("(HI_S32)pstDmKs->ksIMap.iptScale               == %d\n", (HI_S32)pstDmKs->ksIMap.iptScale           );
    printk("(HI_S32)pstDmKs->ksIMap.v3IptOff[0]        == %d\n", (HI_S32)pstDmKs->ksIMap.v3IptOff[0]      );
    printk("(HI_S32)pstDmKs->ksIMap.v3IptOff[1]        == %d\n", (HI_S32)pstDmKs->ksIMap.v3IptOff[1]      );
    printk("(HI_S32)pstDmKs->ksIMap.v3IptOff[2]        == %d\n", (HI_S32)pstDmKs->ksIMap.v3IptOff[2]      );
    printk("(HI_S32)pstDmKs->ksTMap.tmLutISizeM1           == %d\n", (HI_S32)pstDmKs->ksTMap.tmLutISizeM1        );
    printk("(HI_S32)pstDmKs->ksTMap.tmLutSSizeM1           == %d\n", (HI_S32)pstDmKs->ksTMap.tmLutSSizeM1        );
    printk("(HI_S32)pstDmKs->ksTMap.smLutISizeM1           == %d\n", (HI_S32)pstDmKs->ksTMap.smLutISizeM1        );
    printk("(HI_S32)pstDmKs->ksTMap.smLutSSizeM1           == %d\n", (HI_S32)pstDmKs->ksTMap.smLutSSizeM1        );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.rowNum             == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.rowNum             );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.colNum             == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.colNum             );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.dtp                == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.dtp              );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.weav               == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.weav                );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.loc                == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.loc              );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.bdp                == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.bdp              );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.chrm               == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.chrm                );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.clr                == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.clr              );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.rowPitch           == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.rowPitch             );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.colPitch           == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.colPitch             );
    printk("(HI_S32)pstDmKs->ksFrmFmtG.rowPitchC              == %d\n", (HI_S32)pstDmKs->ksFrmFmtG.rowPitchC       );
    printk("(HI_S32)pstDmKs->ksIMapG.clr                  == %d\n", (HI_S32)pstDmKs->ksIMapG.clr                  );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2RgbScale2P    == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2RgbScale2P     );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[0][0]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[0][0]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[0][1]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[0][1]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[0][2]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[0][2]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[1][0]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[1][0]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[1][1]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[1][1]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[1][2]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[1][2]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[2][0]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[2][0]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[2][1]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[2][1]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[2][2]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Yuv2Rgb[2][2]   );
    printk("(HI_S32)pstDmKs->ksIMapG.v3Yuv2RgbOffInRgb[0]  == %d\n", (HI_S32)pstDmKs->ksIMapG.v3Yuv2RgbOffInRgb[0] );
    printk("(HI_S32)pstDmKs->ksIMapG.v3Yuv2RgbOffInRgb[1]  == %d\n", (HI_S32)pstDmKs->ksIMapG.v3Yuv2RgbOffInRgb[1] );
    printk("(HI_S32)pstDmKs->ksIMapG.v3Yuv2RgbOffInRgb[2]  == %d\n", (HI_S32)pstDmKs->ksIMapG.v3Yuv2RgbOffInRgb[2] );
    printk("(HI_U32)pstDmKs->ksIMapG.eotfParam.rangeMin   == %d\n", (HI_U32)pstDmKs->ksIMapG.eotfParam.rangeMin   );
    printk("(HI_U32)pstDmKs->ksIMapG.eotfParam.range      == %d\n", (HI_U32)pstDmKs->ksIMapG.eotfParam.range     );
    printk("(HI_U32)pstDmKs->ksIMapG.eotfParam.rangeInv   == %d\n", (HI_U32)pstDmKs->ksIMapG.eotfParam.rangeInv   );
    printk("(HI_U32)pstDmKs->ksIMapG.eotfParam.bdp        == %d\n", (HI_U32)pstDmKs->ksIMapG.eotfParam.bdp        );
    printk("(HI_U32)pstDmKs->ksIMapG.eotfParam.eotf       == %d\n", (HI_U32)pstDmKs->ksIMapG.eotfParam.eotf      );

#if 0
    printk("(HI_U32)pstDmKs->ksIMapG.eotfParam.gamma      == %d\n", (HI_U32)pstDmKs->ksIMapG.eotfParam.gamma     );
    printk("(HI_U32)pstDmKs->ksIMapG.eotfParam.a          == %d\n", (HI_U32)pstDmKs->ksIMapG.eotfParam.a        );
    printk("(HI_U32)pstDmKs->ksIMapG.eotfParam.b          == %d\n", (HI_U32)pstDmKs->ksIMapG.eotfParam.b        );
    printk("(HI_U32)pstDmKs->ksIMapG.eotfParam.g          == %d\n", (HI_U32)pstDmKs->ksIMapG.eotfParam.g        );
#endif
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2LmsScale2P    == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2LmsScale2P     );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[0][0]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[0][0]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[0][1]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[0][1]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[0][2]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[0][2]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[1][0]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[1][0]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[1][1]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[1][1]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[1][2]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[1][2]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[2][0]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[2][0]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[2][1]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[2][1]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[2][2]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Rgb2Lms[2][2]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2IptScale2P    == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2IptScale2P     );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[0][0]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[0][0]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[0][1]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[0][1]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[0][2]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[0][2]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[1][0]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[1][0]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[1][1]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[1][1]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[1][2]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[1][2]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[2][0]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[2][0]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[2][1]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[2][1]   );
    printk("(HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[2][2]     == %d\n", (HI_S32)pstDmKs->ksIMapG.m33Lms2Ipt[2][2]   );
    printk("(HI_S32)pstDmKs->ksIMapG.iptScale             == %d\n", (HI_S32)pstDmKs->ksIMapG.iptScale             );
    printk("(HI_S32)pstDmKs->ksIMapG.v3IptOff[0]          == %d\n", (HI_S32)pstDmKs->ksIMapG.v3IptOff[0]        );
    printk("(HI_S32)pstDmKs->ksIMapG.v3IptOff[1]          == %d\n", (HI_S32)pstDmKs->ksIMapG.v3IptOff[1]        );
    printk("(HI_S32)pstDmKs->ksIMapG.v3IptOff[2]          == %d\n", (HI_S32)pstDmKs->ksIMapG.v3IptOff[2]        );
    printk("(HI_S32)pstDmKs->ksTMapG.tmLutISizeM1         == %d\n", (HI_S32)pstDmKs->ksTMapG.tmLutISizeM1      );
    printk("(HI_S32)pstDmKs->ksTMapG.tmLutSSizeM1         == %d\n", (HI_S32)pstDmKs->ksTMapG.tmLutSSizeM1      );
    printk("(HI_S32)pstDmKs->ksTMapG.smLutISizeM1         == %d\n", (HI_S32)pstDmKs->ksTMapG.smLutISizeM1      );
    printk("(HI_S32)pstDmKs->ksTMapG.smLutSSizeM1         == %d\n", (HI_S32)pstDmKs->ksTMapG.smLutSSizeM1      );
    printk("(HI_S32)pstDmKs->ksTMapG.tcLutDir                   == %d\n", (HI_S32)pstDmKs->ksTMapG.tcLutDir);
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2LmsScale2P    == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2LmsScale2P   );
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[0][0]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[0][0]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[0][1]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[0][1]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[0][2]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[0][2]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[1][0]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[1][0]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[1][1]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[1][1]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[1][2]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[1][2]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[2][0]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[2][0]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[2][1]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[2][1]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[2][2]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Ipt2Lms[2][2]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2RgbScale2P    == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2RgbScale2P   );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[0][0]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[0][0]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[0][1]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[0][1]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[0][2]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[0][2]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[1][0]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[1][0]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[1][1]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[1][1]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[1][2]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[1][2]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[2][0]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[2][0]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[2][1]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[2][1]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[2][2]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Lms2Rgb[2][2]     );
    printk("(HI_S32)pstDmKs->ksOMap.oetfParam.oetf     == %d\n", (HI_S32)pstDmKs->ksOMap.oetfParam.oetf     );
    printk("(HI_S32)pstDmKs->ksOMap.oetfParam.min      == %d\n", (HI_S32)pstDmKs->ksOMap.oetfParam.min   );
    printk("(HI_S32)pstDmKs->ksOMap.oetfParam.max      == %d\n", (HI_S32)pstDmKs->ksOMap.oetfParam.max   );
    printk("(HI_S32)pstDmKs->ksOMap.oetfParam.bdp      == %d\n", (HI_S32)pstDmKs->ksOMap.oetfParam.bdp   );

    printk("(HI_S32)pstDmKs->ksOMap.oetfParam.rangeMin      == %d\n", (HI_S32)pstDmKs->ksOMap.oetfParam.rangeMin     );
    printk("(HI_S32)pstDmKs->ksOMap.oetfParam.range      == %d\n", (HI_S32)pstDmKs->ksOMap.oetfParam.range     );
    printk("(HI_S32)pstDmKs->ksOMap.oetfParam.rangeOverOne      == %d\n", (HI_S32)pstDmKs->ksOMap.oetfParam.rangeOverOne     );



    printk("(HI_S32)pstDmKs->ksOMap.clr                == %d\n", (HI_S32)pstDmKs->ksOMap.clr            );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2YuvScale2P    == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2YuvScale2P   );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[0][0]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[0][0]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[0][1]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[0][1]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[0][2]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[0][2]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[1][0]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[1][0]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[1][1]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[1][1]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[1][2]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[1][2]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[2][0]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[2][0]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[2][1]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[2][1]     );
    printk("(HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[2][2]       == %d\n", (HI_S32)pstDmKs->ksOMap.m33Rgb2Yuv[2][2]     );
    printk("(HI_S32)pstDmKs->ksOMap.v3Rgb2YuvOff[0]    == %d\n", (HI_S32)pstDmKs->ksOMap.v3Rgb2YuvOff[0]   );
    printk("(HI_S32)pstDmKs->ksOMap.v3Rgb2YuvOff[1]    == %d\n", (HI_S32)pstDmKs->ksOMap.v3Rgb2YuvOff[1]   );
    printk("(HI_S32)pstDmKs->ksOMap.v3Rgb2YuvOff[2]    == %d\n", (HI_S32)pstDmKs->ksOMap.v3Rgb2YuvOff[2]   );
    printk("(HI_S32)pstDmKs->ksOMap.iptScale               == %d\n", (HI_S32)pstDmKs->ksOMap.iptScale           );
    printk("(HI_S32)pstDmKs->ksOMap.v3IptOff[0]        == %d\n", (HI_S32)pstDmKs->ksOMap.v3IptOff[0]      );
    printk("(HI_S32)pstDmKs->ksOMap.v3IptOff[1]        == %d\n", (HI_S32)pstDmKs->ksOMap.v3IptOff[1]      );
    printk("(HI_S32)pstDmKs->ksOMap.v3IptOff[2]        == %d\n", (HI_S32)pstDmKs->ksOMap.v3IptOff[2]      );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.rowNum          == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.rowNum          );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.colNum          == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.colNum          );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.dtp             == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.dtp           );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.weav            == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.weav         );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.loc             == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.loc           );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.bdp             == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.bdp           );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.chrm            == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.chrm         );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.clr             == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.clr           );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.rowPitch        == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.rowPitch      );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.colPitch        == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.colPitch      );
    printk("(HI_S32)pstDmKs->ksFrmFmtO.rowPitchC           == %d\n", (HI_S32)pstDmKs->ksFrmFmtO.rowPitchC        );
    printk("(HI_S32)pstDmKs->bypassShift                   == %d\n", (HI_S32)pstDmKs->bypassShift                  );
#endif

    //composer up sample
    VDP_VID_SetComposeElUpsampleMax    (pstDmKs->ksUs.maxUs);
    VDP_VID_SetComposeElUpsampleMin    (pstDmKs->ksUs.minUs);


    //vdm_yuv2rgb
    VDP_HDR_SetVDmYuv2rgbEn            ( 1 );
    VDP_HDR_SetVDmYuv2rgbV0En          ( 1 );
    VDP_HDR_SetVDmYuv2rgbV1En          ( 0 );
    VDP_HDR_SetVDmImap0Yuv2rgb         (pstDmKs->ksIMap.m33Yuv2Rgb);
    VDP_HDR_SetVDmImapYuv2rgbscale2p   (pstDmKs->ksIMap.m33Yuv2RgbScale2P);
    VDP_HDR_SetVDmImapYuv2rgbOutDc0    (pstDmKs->ksIMap.v3Yuv2RgbOffInRgb);

    u32InBdp = (pstDmKs->ksIMap.eotfParam.bdp == 12) ? 0 : 1;
    VDP_HDR_SetVDmInBits               ( u32InBdp );

    //vdm_rgb2lms
    VDP_HDR_SetVDmRgb2lmsEn            ( 1 );
    VDP_HDR_SetVDmImapRgb2lms          ( pstDmKs->ksIMap.m33Rgb2Lms       );
    VDP_HDR_SetVDmImapRgb2lmsscale2p   ( pstDmKs->ksIMap.m33Rgb2LmsScale2P);
    VDP_HDR_SetVDmImapRgb2lmsmin       ( 0 );
    //VDP_HDR_SetVDmImapRgb2lmsmax       ( (HI_U32)((HI_U64)10000*(1<<18))  );
    VDP_HDR_SetVDmImapRgb2lmsmax        ( 0x9c400000  );//(10000LL*(1<<18))

    //cvm1_lms2ipt
    VDP_HDR_SetVCvmLms2iptEn           ( 1 );
    VDP_HDR_SetVDmImapLms2iptmin       ( 0 - ((1 << 15) - 1) );
    VDP_HDR_SetVDmImapLms2iptmax       ( ((1 << 15) - 1) );
    VDP_HDR_SetVCvmImapLms2ipt         ( pstDmKs->ksIMap.m33Lms2Ipt           );
    VDP_HDR_SetVCvmImapLms2iptscale2p  ( pstDmKs->ksIMap.m33Lms2IptScale2P + 1 );

    //cvm1_ipt2lms
    VDP_HDR_SetVCvmIpt2lmsEn           ( 1 );
    VDP_HDR_SetVCvmOmapIpt2lms         ( pstDmKs->ksOMap.m33Ipt2Lms       );
    VDP_HDR_SetVCvmOmapIpt2lmsscale2p  ( pstDmKs->ksOMap.m33Ipt2LmsScale2P);
    VDP_HDR_SetVDmOmapIpt2lmsmin       ( 0 );
    VDP_HDR_SetVDmOmapIpt2lmsmax       ( (1 << 16) - 1 );

    //cvm1_lms2rgb
    VDP_HDR_SetVCvmLms2rgbEn           ( 1 );
    VDP_HDR_SetVCvmOmapLms2rgb         ( pstDmKs->ksOMap.m33Lms2Rgb       );
    VDP_HDR_SetVCvmOmapLms2rgbscale2p  ( pstDmKs->ksOMap.m33Lms2RgbScale2P);
    VDP_HDR_SetVDmOmapLms2rgbmin       ( pstDmKs->ksOMap.oetfParam.min    );
    VDP_HDR_SetVDmOmapLms2rgbmax       ( pstDmKs->ksOMap.oetfParam.max    );

    //cvm1_rgb2yuv
    VDP_HDR_SetVCvmRgb2yuvEn           ( 1 );
    VDP_HDR_SetVCvmOmapRgb2yuv         ( pstDmKs->ksOMap.m33Rgb2Yuv       );
    VDP_HDR_SetVCvmOmapRgb2yuvscale2p  ( pstDmKs->ksOMap.m33Rgb2YuvScale2P);
    VDP_HDR_SetVCvmOmapRgb2yuvOutDc    ( pstDmKs->ksOMap.v3Rgb2YuvOff     );

    //VDM_PQ2L
    VDP_HDR_SetVDmInEotf               ( pstDmKs->ksIMap.eotfParam.eotf   ) ;
    VDP_HDR_SetVDmDegammaEn            ( 1 );
    VDP_HDR_SetVCvmEn                  ( 1 );
    VDP_HDR_SetVCvmDegammaEn           ( 1 );
    VDP_HDR_SetVCvmMGammaEn            ( 1 );
    VDP_HDR_SetVDmGammaEn              ( 1 );
    VDP_HDR_SetVDmNormEn               ( 1 );
    VDP_HDR_SetVDmImapRangeMin         ( pstDmKs->ksIMap.eotfParam.rangeMin     );
    VDP_HDR_SetVDmImapRange            ( pstDmKs->ksIMap.eotfParam.range        );
    VDP_HDR_SetVDmImapRangeInv         ( pstDmKs->ksIMap.eotfParam.rangeInv     );
    VDP_HDR_SetVCvmOmapRangeMin        ( pstDmKs->ksOMap.oetfParam.rangeMin     );
    VDP_HDR_SetVCvmOmapRangeOver       ( pstDmKs->ksOMap.oetfParam.rangeOverOne );

    u32OutBdp = (pstDmKs->ksOMap.oetfParam.bdp == 12) ? 2 : ((pstDmKs->ksOMap.oetfParam.bdp == 10) ? 1 : 0 );
    VDP_HDR_SetCvmOutBits              ( u32OutBdp );
    VDP_HDR_SetVCvmDenormEn            ( 1 );
    VDP_HDR_SetVDmImapIptoff           ( pstDmKs->ksIMap.v3IptOff               );
    VDP_HDR_SetVDmImapIptScale         ( pstDmKs->ksIMap.iptScale               );

    u32InClr = (pstDmKs->ksIMap.clr == 3) ? 0 : 1;
    VDP_HDR_SetVDmInColor              ( u32InClr );

    u32OutClr = (pstDmKs->ksOMap.clr == 3) ? 0 : 1;
    VDP_HDR_SetCvmOutColor             ( u32OutClr );

    VDP_HDR_SetVCvmOmapIptoff          ( pstDmKs->ksOMap.v3IptOff );
    VDP_HDR_SetVCvmOmapIptScale        ( pstDmKs->ksOMap.iptScale );

    //downsample
    VDP_HDR_SetDmHdrDsMax              ( pstDmKs->ksDs.maxDs );
    VDP_HDR_SetDmHdrDsMin              ( pstDmKs->ksDs.minDs );

    return HI_SUCCESS;
}

HI_S32 XDP_DRV_SetHdrMute(XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    VDP_VP_MUTE_BK_S stVpMuteBkg = {0};

    stVpMuteBkg.u32VpMuteBkgA = 0x3ff;
    stVpMuteBkg.u32VpMuteBkgY = 0x40;
    stVpMuteBkg.u32VpMuteBkgU = 0x200;
    stVpMuteBkg.u32VpMuteBkgV = 0x200;

    VDP_VP_SetMuteEnable     (VDP_LAYER_VP0, pstInfoOut->stXdpSysCfg.bMuteEn);

    VDP_VP_SetMuteBkg        (VDP_LAYER_VP0, stVpMuteBkg);

    if (HI_TRUE == pstInfoOut->stXdpSysCfg.bMuteEn)
    {
        VDP_DRV_SetXdpRegUp();

        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
}

HI_S32 XDP_DRV_SetDolbyVP0Reso(HI_U32 u32LayerId, XDP_LAYER_VID_INFO_S *pstInfoOut)
{
    VDP_RECT_S stVidRect = {0};

    if (u32LayerId != VDP_LAYER_VID3)
    {
        stVidRect.u32Wth = pstInfoOut->stXdpPositionCfg.stVideoRect.u32Wth;
        stVidRect.u32Hgt = pstInfoOut->stXdpPositionCfg.stVideoRect.u32Hgt;

        /* inner rect should be the same with outer rect in dolby path. */
        VDP_VID_SetVideoPos                (VDP_LAYER_VID0, stVidRect);
        VDP_VID_SetDispPos                 (VDP_LAYER_VID0, stVidRect);

        VDP_VP_SetVideoPos             (VDP_LAYER_VP0, pstInfoOut->stXdpPositionCfg.stVideoRect);
        VDP_VP_SetDispPos              (VDP_LAYER_VP0, pstInfoOut->stXdpPositionCfg.stVideoRect);
        VDP_VP_SetInReso               (VDP_LAYER_VP0, pstInfoOut->stXdpPositionCfg.stVideoRect);
        VDP_VP_SetLayerGalpha          (VDP_LAYER_VP0, pstInfoOut->stXdpSysCfg.u32AllAlpha);
    }

    return HI_SUCCESS;
}

XDP_LAYER_VID_INFO_S stXdpHdrCfgTmp;

HI_S32 VDP_DRV_ClearOtherModeCfg(XDP_LAYER_VID_INFO_S  *stXdpHdrCfgIn)
{
    VDP_VID_SetMultiModeEnable(VDP_LAYER_VID1, HI_FALSE);
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetHdrMode(XDP_LAYER_VID_INFO_S  *stXdpHdrCfgIn, VDP_FIXPT_MAIN_CFG_S *pstCompCfg, DmKsFxp_t *pstDmKs)
{

    XDP_HDR_CTRL_S stXdpHdrCtrl = {0};
    XDP_DOLBY_CFG_MODE_E enSceneMode = XDP_DOVI_BC_IN_DOVI_IPT_OUT;

    XDP_LAYER_VID_INFO_S *stXdpHdrCfgOut = HI_NULL;
    if (HI_NULL == stXdpHdrCfgIn || HI_NULL == pstCompCfg || HI_NULL == pstDmKs)
    {
        VDP_PRINT("VDP_DRV_SetHdrMode is NULL !!!\n");
        return HI_FAILURE;
    }
    memset(&stXdpHdrCtrl, 0x0, sizeof(XDP_HDR_CTRL_S));
    memset((HI_VOID *)&stXdpHdrCfgTmp, 0, sizeof(XDP_LAYER_VID_INFO_S));
    memcpy((HI_VOID *)&stXdpHdrCfgTmp, stXdpHdrCfgIn, sizeof(XDP_LAYER_VID_INFO_S));
    stXdpHdrCfgOut = &stXdpHdrCfgTmp;
    if (HI_NULL == stXdpHdrCfgOut)
    {
        VDP_PRINT("stXdpHdrCfgOut is NULL !!!\n");
        return HI_FAILURE;
    }

    if (HI_SUCCESS == XDP_DRV_JudgeVidLayerEnable(VDP_LAYER_VID0, stXdpHdrCfgIn)
        || HI_SUCCESS == XDP_DRV_SetHdrMute(stXdpHdrCfgIn))
    {
        return HI_SUCCESS;
    }

    VDP_DRV_ClearOtherModeCfg(stXdpHdrCfgIn);

    VDP_SetCheckSumEnable(HI_TRUE);//enable check sum.

    VDP_DRV_SetHdrInit(&stXdpHdrCtrl);

    XDP_DRV_GetDolbySceneMode(stXdpHdrCfgOut, &enSceneMode);

    VDP_DRV_GetHdrCfg(enSceneMode, pstCompCfg, pstDmKs, &stXdpHdrCtrl);

    VDP_DRV_SetComposer            (pstCompCfg);

    VDP_DRV_SetVdm                 (pstDmKs);

    XDP_DRV_SetHdrCtrlInfo         (&stXdpHdrCtrl);

    VDP_DRV_SetHdrCoef             (pstDmKs);

    XDP_DRV_GetVidLayerFdr(VDP_LAYER_VID0, stXdpHdrCfgIn, stXdpHdrCfgOut);

    VDP_DRV_SetHdrFdr(stXdpHdrCfgIn, &stXdpHdrCtrl);

    VDP_DRV_SetHdrAddr(stXdpHdrCfgIn, &stXdpHdrCtrl);

    VDP_DRV_GetHdrZmeCfg(stXdpHdrCfgIn, stXdpHdrCfgOut, &stXdpHdrCtrl);

    VDP_DRV_SetHdrZmeCfg (stXdpHdrCfgOut, &stXdpHdrCtrl);

    VDP_DRV_SetHdrVidReso(stXdpHdrCfgOut, &stXdpHdrCtrl);

    XDP_DRV_SetDolbyVP0Reso(VDP_LAYER_VID0, stXdpHdrCfgOut);

    VDP_DRV_CleanVidPQModule();

    VDP_DRV_SetGfxHdr(pstDmKs, &stXdpHdrCtrl);

    //XDP_DRV_SetHdrCbmBkg(stXdpHdrCfgOut);

    VDP_DRV_SetXdpRegUp();

    return HI_SUCCESS;


}


HI_VOID VDP_DRV_HdrRegClean(HI_VOID)
{
    VDP_HIHDR_SetVdmGmmEn(HI_FALSE);
    VDP_HIHDR_SetVdmTmapEn( HI_FALSE);
    VDP_HIHDR_SetVdmDegmmEn(HI_FALSE);
    VDP_HIHDR_SetVdmDitherEn( HI_FALSE);
    VDP_HIHDR_SetVdmCadjEn(HI_FALSE);
    VDP_HIHDR_SetVdmRgb2yuvEn(HI_FALSE);
    VDP_HIHDR_SetVdmCscEn(HI_FALSE);
    VDP_HIHDR_SetVdmV0GammaEn( HI_FALSE);
    VDP_HIHDR_SetVdmV1GammaEn( HI_FALSE);
    VDP_VP_SetMuteEnable(VDP_LAYER_VP0, HI_FALSE);

    VDP_GP_SetGdmGdmGmmEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmTmapEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmDegmmEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetGdmGdmEn(VDP_LAYER_GP0, HI_FALSE);
    VDP_GP_SetHdrSel               (0 );

    VDP_HDR_SetVDmEn               (0);
    VDP_HDR_SetVDmYuv2rgbEn        (0);
    VDP_HDR_SetVDmYuv2rgbV0En      (0);
    VDP_HDR_SetVDmYuv2rgbV1En      (0);

    VDP_HDR_SetVDmNormEn           (0);
    VDP_HDR_SetVDmDegammaEn        (0);
    VDP_HDR_SetVDmRgb2lmsEn        (0);
    VDP_HDR_SetVDmGammaEn          (0);
    VDP_HDR_SetVDmGammaV0En        (0);
    VDP_HDR_SetVDmGammaV1En        (0);

    //VCVM1
    VDP_HDR_SetVCvmEn              (0) ;
    VDP_HDR_SetGCvmEn              (0) ;
    VDP_HDR_SetVCvmLms2iptEn       (0);

    VDP_HDR_SetVCvmIpt2lmsEn       (0);
    VDP_HDR_SetVCvmLms2rgbEn       (0);
    VDP_HDR_SetVCvmRgb2yuvEn       (0);
    VDP_HDR_SetVCvmDenormEn        (0);

    VDP_HDR_SetVCvmDegammaEn       (0) ;
    VDP_HDR_SetVCvmMGammaEn        (0) ;
    VDP_HDR_SetVCvmS2uEn           (0);
    VDP_HDR_SetGCvmS2uEn           (0);
    VDP_HDR_SetCvm1U2sEn           (0);

    //GDM
    VDP_HDR_SetGDmEn               (0);
    VDP_HDR_SetGDmDegammaEn        (0);
    VDP_HDR_SetGDmRgb2lmsEn        (0) ;
    VDP_HDR_SetGDmGammaEn          (0);
    VDP_HDR_SetAuthEn              (0);

    //EDR
    VDP_HDR_SetDmEdrEn             (0);
    VDP_HDR_SetDmHdrMdEn           (0);
    VDP_HDR_SetDmHdrDsEn           (0);

    VDP_DISP_SetNxgDataSwapEnable (VDP_CHN_DHD0, 0);
    VDP_DISP_SetHdmiMode          (VDP_CHN_DHD0, 0);
    VDP_VID_SetHdrElZme           (VDP_LAYER_VID1, 0);
    //----------------------------------------------------------------------
    //data path setting
    //----------------------------------------------------------------------
    VDP_HDR_SetHdrEnable           (0);
    VDP_VID_SetComposerBlEn        (0) ;
    VDP_VID_SetComposerElEn        (0) ;

    VDP_DRV_SetXdpRegUp();

    return;
}

