
#include "drv_cgms.h"
#include "drv_mcvn.h"
#include "vdp_hal_comm.h"
#include "vdp_software_selfdefine.h"
//#include "hal_reg_cfg_manager.h"

S_VDP_COM_REGS_TYPE *pVdpComReg = HI_NULL;


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifndef __DISP_PLATFORM_BOOT__

static const  DISP_CGMS_FMT_CFG_s   s_aCgmsCfgTable[] =
{
    {
        HI_DRV_DISP_FMT_1080i_50,
        {0x88003, 0x28083, 0xd8043, 0x780c3}
    },

    {
        HI_DRV_DISP_FMT_1080i_60,
        { 0x88003, 0x28083, 0xd8043, 0x780c3}
    },

    {
        HI_DRV_DISP_FMT_720P_50,
        {0x88003, 0x28083, 0xd8043, 0x780c3}
    },

    {
        HI_DRV_DISP_FMT_720P_60,
        { 0x88003, 0x28083, 0xd8043, 0x780c3}
    },

    {
        HI_DRV_DISP_FMT_480P_60,
        {0x88003, 0x28083,  0xd8043, 0x780c3}
    },

    {
        HI_DRV_DISP_FMT_576P_50,
        {0x0008, 0x2008, 0x1008, 0x3008}
    },

    {
        HI_DRV_DISP_FMT_NTSC,
        {0x88003, 0x28083, 0xd8043, 0x780c3}
    },

    {
        HI_DRV_DISP_FMT_NTSC_J,
        {0x88003,  0x28083, 0xd8043, 0x780c3}
    },

    {
        HI_DRV_DISP_FMT_PAL,
        {0x0008,  0x2008,  0x1008,  0x3008}
    },

    {
        HI_DRV_DISP_FMT_PAL_N,
        { 0x0008, 0x2008, 0x1008, 0x3008}
    },

    {
        HI_DRV_DISP_FMT_PAL_Nc,
        {0x0008, 0x2008, 0x1008, 0x3008}
    }

};

HI_S32 DRV_CGMS_Init(HI_DRV_DISPLAY_E enDisp, HI_DRV_DISP_FMT_E enFmt, DISP_CGMS_INFO_S* pstCgms)
{
    CgmsCheckNullPointer(pstCgms);

    pstCgms->bEnable = HI_FALSE;

    pstCgms->enAttachedDisp = enDisp;

    pstCgms->enType = HI_DRV_DISP_CGMSA_A;

    pstCgms->enMode = HI_DRV_DISP_CGMSA_COPY_FREELY;

    pstCgms->enCurFormat = enFmt;

    return HI_SUCCESS;
}

HI_S32 DRV_CGMS_DeInit(DISP_CGMS_INFO_S *pstCgms)
{
    return HI_SUCCESS;
}

HI_S32 DISP_CGMS_SetEnable(HI_DRV_DISP_FMT_E enFormat, const HI_DRV_DISP_CGMSA_CFG_S *pstCgmsCfg)
{
    /* Type A of Sdate with PAL format depend on WSS setting */
    if (HI_DRV_DISP_CGMSA_A == pstCgmsCfg->enType)
    {
        if (enFormat == HI_DRV_DISP_FMT_PAL
            || enFormat == HI_DRV_DISP_FMT_PAL_N
            || enFormat == HI_DRV_DISP_FMT_PAL_Nc)
        {
            SDATE_HDATE_VBI_SetWssEn(DISP_VENC_SDATE0, pstCgmsCfg->bEnable);
        }
        else
        {
            SDATE_HDATE_VBI_SetWssEn(DISP_VENC_SDATE0, HI_FALSE);
            SDATE_HDATE_VBI_SetCgmsTypeAEn(DISP_VENC_HDATE0, pstCgmsCfg->bEnable);
            SDATE_HDATE_VBI_SetCgmsTypeAEn(DISP_VENC_SDATE0, pstCgmsCfg->bEnable);
        }
    }
    else if (HI_DRV_DISP_CGMSA_B == pstCgmsCfg->enType)
    {
        VDP_VBI_SetCgmsTypeBEn(DISP_VENC_HDATE0, pstCgmsCfg->bEnable);
    }
    else
    {
        HI_ERR_DISP("DISP does not support the macrovision type:%d!\n", pstCgmsCfg->enType);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 DISP_CGMS_SetTypeA(DISP_VENC_E enChannel, HI_DRV_DISP_FMT_E enFormat, const HI_DRV_DISP_CGMSA_CFG_S *pstCgmsCfg)
{
    HI_U32 u32Data = 0;
    HI_U32 index = 0;
    HI_BOOL bFindFmtFlag = HI_FALSE;

    for (; index < sizeof(s_aCgmsCfgTable) / sizeof(DISP_CGMS_FMT_CFG_s); index++)
    {
        if (s_aCgmsCfgTable[index].enFmt == enFormat)
        {
            bFindFmtFlag = HI_TRUE;
            u32Data = s_aCgmsCfgTable[index].au32CfgData[pstCgmsCfg->enMode ];
            break;
        }
    }

    if (HI_TRUE != bFindFmtFlag)
    {
        return HI_ERR_DISP_INVALID_PARA;
    }

    if (enFormat == HI_DRV_DISP_FMT_PAL_N
        || enFormat == HI_DRV_DISP_FMT_PAL_Nc
        || enFormat == HI_DRV_DISP_FMT_PAL)
    {
        SDATE_HDATE_VBI_SetWssData(enChannel, u32Data);
    }
    else
    {
        SDATE_HDATE_VBI_SetCgmsTypeA(enChannel, u32Data);
    }

    return HI_SUCCESS;

}

HI_S32 DISP_CGMS_SetTypeB(DISP_CGMS_INFO_S *pstCgms,HI_DRV_DISP_FMT_E enFormat,HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg)
{
    HI_ERR_DISP("CGMS_B is unsupported\n",enFormat);

    return HI_ERR_DISP_INVALID_OPT;
}

static HI_VOID DISP_SetCgmsCfgToComReg(const HI_DRV_DISP_CGMSA_CFG_S *pstCgmsCfg)
{
    U_ANALOG_CTRL ANALOG_CTRL;

    ANALOG_CTRL.u32 = VDP_RegRead((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32));
    ANALOG_CTRL.bits.cgms_en    = pstCgmsCfg->bEnable;
    ANALOG_CTRL.bits.cgms_type  = pstCgmsCfg->enType;
    ANALOG_CTRL.bits.cgms_mode  = pstCgmsCfg->enMode;
    VDP_RegWrite(((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32)), ANALOG_CTRL.u32);

    return;
}

static HI_VOID DISP_GetCgmsCfgFromComReg(HI_DRV_DISP_CGMSA_CFG_S *pstCgmsCfg)
{
    U_ANALOG_CTRL ANALOG_CTRL;

    ANALOG_CTRL.u32 = VDP_RegRead((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32));
    pstCgmsCfg->bEnable = ANALOG_CTRL.bits.cgms_en;
    pstCgmsCfg->enType  = ANALOG_CTRL.bits.cgms_type;
    pstCgmsCfg->enMode  = ANALOG_CTRL.bits.cgms_mode;

    return;
}

HI_S32 DRV_CGMS_Set(HI_DRV_DISP_FMT_E enSdateFmt, HI_DRV_DISP_FMT_E enHdateFmt, const HI_DRV_DISP_CGMSA_CFG_S *pstCgmsCfg)
{
    if (enSdateFmt >= HI_DRV_DISP_FMT_BUTT)
    {
        HI_ERR_DISP("Invalid format %d\n", enSdateFmt);
        return HI_ERR_DISP_INVALID_PARA;
    }

    if (enHdateFmt >= HI_DRV_DISP_FMT_BUTT)
    {
        HI_ERR_DISP("Invalid format %d\n", enHdateFmt);
        return HI_ERR_DISP_INVALID_PARA;
    }

    if (pstCgmsCfg->enType >= HI_DRV_DISP_CGMSA_TYPE_BUTT)
    {
        HI_ERR_DISP("Invalid Type %d\n", pstCgmsCfg->enType);
        return HI_ERR_DISP_INVALID_PARA;
    }

    if (pstCgmsCfg->enMode >= HI_DRV_DISP_CGMSA_MODE_BUTT)
    {
        HI_ERR_DISP("Invalid Mode %d\n", pstCgmsCfg->enMode);
        return HI_ERR_DISP_INVALID_PARA;
    }

    DISP_CGMS_SetEnable(enSdateFmt, pstCgmsCfg);

    DISP_SetCgmsCfgToComReg(pstCgmsCfg);

    if (pstCgmsCfg->bEnable == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    if (pstCgmsCfg->enType == HI_DRV_DISP_CGMSA_A)
    {
        (HI_VOID)DISP_CGMS_SetTypeA(DISP_VENC_SDATE0, enSdateFmt, pstCgmsCfg);
        (HI_VOID)DISP_CGMS_SetTypeA(DISP_VENC_HDATE0, enHdateFmt, pstCgmsCfg);
    }
    else
    {
        HI_ERR_DISP("Type %d can't be supported\n", pstCgmsCfg->enType);

        return HI_ERR_DISP_INVALID_OPT;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_CGMS_Get(DISP_CGMS_STATE_S *pstCurState)
{
    HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg = {0};

    DISP_GetCgmsCfgFromComReg(&stCgmsCfg);

    if (stCgmsCfg.enMode >= HI_DRV_DISP_CGMSA_MODE_BUTT
        || stCgmsCfg.enType >= HI_DRV_DISP_CGMSA_TYPE_BUTT)
    {
        HI_ERR_DISP("Mode=%d or Type=%d is out of range !\n", stCgmsCfg.enMode, stCgmsCfg.enType);
        return HI_FAILURE;
    }

    pstCurState->bEnable = stCgmsCfg.bEnable;
    pstCurState->enMode  = stCgmsCfg.enMode;
    pstCurState->enType  = stCgmsCfg.enType;

    return HI_SUCCESS;
}


#else
HI_S32 DRV_CGMS_Init(HI_DRV_DISPLAY_E enDisp,HI_DRV_DISP_FMT_E enFmt,DISP_CGMS_INFO_S *pstCgms)
{
    return HI_SUCCESS;
}

HI_S32 DRV_CGMS_DeInit(DISP_CGMS_INFO_S *pstCgms)
{
    return HI_SUCCESS;
}

HI_S32 DRV_CGMS_Set(HI_DRV_DISP_FMT_E enSdateFmt, HI_DRV_DISP_FMT_E enHdateFmt, HI_DRV_DISP_CGMSA_CFG_S stCgmsCfg)
{
    return HI_SUCCESS;
}

HI_S32 DRV_CGMS_Get(DISP_CGMS_STATE_S *pstCurState)
{
    return HI_SUCCESS;
}
#endif

HI_VOID DRV_SetDateAttachToComReg(DISP_VENC_E enDate, HI_DRV_DISPLAY_E enDisp)
{
    U_ANALOG_CTRL ANALOG_CTRL;
    unsigned int date_attach;

    ANALOG_CTRL.u32 = VDP_RegRead((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32));

    /* Accroding to common register define: 0-no_attaching, 0x1-DISP0, 0x2-DISP1 */
    switch (enDisp)
    {
        case HI_DRV_DISPLAY_0 :
            date_attach = 0x1;
            break;
        case HI_DRV_DISPLAY_1 :
            date_attach = 0x2;
            break;
        case HI_DRV_DISPLAY_BUTT :
            date_attach = 0x0;
            break;
        default:
            return;
    }

    if (DISP_VENC_SDATE0 == enDate)
    {
        ANALOG_CTRL.bits.sdate_attach = date_attach;
        VDP_RegWrite(((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32)), ANALOG_CTRL.u32);
    }
    else if (DISP_VENC_HDATE0 == enDate)
    {
        ANALOG_CTRL.bits.hdate_attach = date_attach;
        VDP_RegWrite(((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32)), ANALOG_CTRL.u32);
    }
    else
    {
        return;
    }

    return;
}

HI_VOID DRV_SetDispFmtToComReg(HI_DRV_DISPLAY_E enDisp, HI_DRV_DISP_FMT_E enFmt)
{
    U_ANALOG_CTRL ANALOG_CTRL;

    ANALOG_CTRL.u32 = VDP_RegRead((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32));

    if (HI_DRV_DISPLAY_0 == enDisp)
    {
        ANALOG_CTRL.bits.disp0_fmt = enFmt;
        VDP_RegWrite(((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32)), ANALOG_CTRL.u32);
    }
    else if (HI_DRV_DISPLAY_1 == enDisp)
    {
        ANALOG_CTRL.bits.disp1_fmt = enFmt;
        VDP_RegWrite(((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32)), ANALOG_CTRL.u32);
    }
    else
    {
        HI_INFO_DISP("DISP enum out of range : DISP=%d.", enDisp);
    }

    return;
}

HI_VOID DRV_InitComReg(HI_VOID)
{
    U_ANALOG_CTRL ANALOG_CTRL;

    ANALOG_CTRL.u32 = 0x0;
    VDP_RegWrite(((HI_ULONG) & (pVdpComReg->ANALOG_CTRL.u32)), ANALOG_CTRL.u32);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
