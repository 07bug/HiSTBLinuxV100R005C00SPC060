#include "hi_type.h"
#include "hi_debug.h"
#include "hi_drv_mem.h"
#include "hi_drv_file.h"
#include "hi_drv_pq.h"

#include "pq_hal_comm.h"
#include "pq_hal_lcacm.h"
#include "pq_mng_lcacm.h"

static ALG_LCACM_S sg_stPQLCACMInfo = {0};

/* Init Color */
static HI_S32 PQ_MNG_LCACMParaInit(HI_VOID)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};

    memset(&stAcmPara, 0x0, sizeof(stAcmPara));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLCACMEn(HI_BOOL bOnOff)
{
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();
    HI_BOOL bAcmEn1 = HI_TRUE;
    HI_BOOL bAcmEn2 = HI_TRUE;

    if ((enSourceMode < PQ_SOURCE_MODE_BUTT)
        && (HI_FALSE == PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_COLOR, enSourceMode)))
    {
        bAcmEn1 = HI_FALSE;
    }

    if (HI_TRUE == sg_stPQLCACMInfo.bHdrProcessEn)
    {
        bAcmEn2 = HI_TRUE;
    }

    sg_stPQLCACMInfo.bEnable = bOnOff & bAcmEn1 & bAcmEn2;

    PQ_HAL_SetACMEn(VDP_LAYER_VP0, sg_stPQLCACMInfo.bEnable);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCACMEn(HI_U32 *pu32OnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32OnOff);

    *pu32OnOff = sg_stPQLCACMInfo.bEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_InitLCACM(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (sg_stPQLCACMInfo.bInit == HI_TRUE)
    {
        return HI_SUCCESS;
    }

    sg_stPQLCACMInfo.bEnable              = HI_FALSE;
    sg_stPQLCACMInfo.u32Strength          = 50;
    sg_stPQLCACMInfo.bDemoEnable          = HI_FALSE;
    sg_stPQLCACMInfo.eDemoMode            = PQ_DEMO_ENABLE_R;
    sg_stPQLCACMInfo.bHdrProcessEn        = HI_FALSE;

    sg_stPQLCACMInfo.enLCACMFleshtone     = HI_PQ_FLESHTONE_GAIN_MID;
    sg_stPQLCACMInfo.enLCACMColorSpecMode = HI_PQ_COLOR_MODE_ORIGINAL;

    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Red       = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Green     = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Blue      = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Cyan      = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Magenta   = 50;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Yellow    = 50;

    s32Ret = PQ_MNG_SetLCACMEn(HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("LCACM ACM Enable Init failure\n");
        sg_stPQLCACMInfo.bInit = HI_FALSE;

        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_LCACMParaInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("LCACM ACM Para Init failure\n");
        sg_stPQLCACMInfo.bInit = HI_FALSE;

        return HI_FAILURE;
    }

    s32Ret = PQ_TABLE_InitPhyList(PQ_VDP_LAYER_VID0, HI_PQ_MODULE_COLOR, PQ_SOURCE_MODE_NO, PQ_SOURCE_MODE_NO);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Low Cost ACM InitPhyList error\n");
        sg_stPQLCACMInfo.bInit = HI_FALSE;

        return HI_FAILURE;
    }

    sg_stPQLCACMInfo.bInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_DeInitLCACM(HI_VOID)
{
    if (sg_stPQLCACMInfo.bInit == HI_FALSE)
    {
        return HI_SUCCESS;
    }

    sg_stPQLCACMInfo.bInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLCACMDemoEn(HI_BOOL bOnOff)
{
    /* lcacm demo off for only support 50% pos */
    PQ_HAL_SetACMDemoEn(VDP_LAYER_VP0, HI_FALSE);

    sg_stPQLCACMInfo.bDemoEnable = bOnOff;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCACMDemoEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbOnOff);

    *pbOnOff = sg_stPQLCACMInfo.bDemoEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLCACMDemoMode(PQ_DEMO_MODE_E enMode)
{
    PQ_HAL_LAYER_VP_E   u32ChId   = VDP_LAYER_VP0;
    HAL_ACM_DEMO_MODE_E enAcmMode = HAL_ACM_DEMO_ENABLE_L;

    sg_stPQLCACMInfo.eDemoMode = enMode;

    if (enMode == PQ_DEMO_ENABLE_L)
    {
        enAcmMode = HAL_ACM_DEMO_ENABLE_L;
    }
    else if (enMode == PQ_DEMO_ENABLE_R)
    {
        enAcmMode = HAL_ACM_DEMO_ENABLE_R;
    }

    PQ_HAL_SetACMDemoMode(u32ChId, enAcmMode);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCACMDemoMode(PQ_DEMO_MODE_E *penMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(penMode);

    *penMode = sg_stPQLCACMInfo.eDemoMode;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCACMFleshToneLevel(HI_U32 *pu32FleshToneLevel)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32FleshToneLevel);

    *pu32FleshToneLevel = sg_stPQLCACMInfo.enLCACMFleshtone;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLCACMFleshToneLevel(HI_PQ_FLESHTONE_E enGainLevel)
{
    if (HI_PQ_FLESHTONE_GAIN_BUTT <= enGainLevel)
    {
        HI_ERR_PQ("[%d]Switch : Color enGainLevel Mode Set error!\n", enGainLevel);
        return HI_FAILURE;
    }

    sg_stPQLCACMInfo.enLCACMFleshtone = enGainLevel;

    if (HI_TRUE == sg_stPQLCACMInfo.bHdrProcessEn)
    {
        return HI_SUCCESS;
    }

    PQ_HAL_SetNormLcacmFleshToneCfg(enGainLevel);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCACMColorEnhanceMode(HI_U32 *pu32ColorEnhanceMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32ColorEnhanceMode);

    *pu32ColorEnhanceMode = sg_stPQLCACMInfo.enLCACMColorSpecMode;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLCACMColorEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode)
{
    sg_stPQLCACMInfo.enLCACMColorSpecMode = enColorSpecMode;

    if (HI_TRUE == sg_stPQLCACMInfo.bHdrProcessEn)
    {
        return HI_SUCCESS;
    }

    PQ_HAL_SetNormLcacmCfg(enColorSpecMode);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLCACMGainLevel(HI_U32 u32GainLevel)
{
    if (u32GainLevel > 100)
    {
        HI_ERR_PQ("%d:PQ_MNG_SetLCACMGainLevel is over range!\n", u32GainLevel);
        return HI_FAILURE;
    }

    sg_stPQLCACMInfo.u32Strength = u32GainLevel;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCACMGainLevel(HI_U32 *pu32ColorLevel)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32ColorLevel);

    *pu32ColorLevel = sg_stPQLCACMInfo.u32Strength;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLCACMSixBaseColorLevel(HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColorOffset)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstSixBaseColorOffset);

    if ((pstSixBaseColorOffset->u32Red > 100)
        || (pstSixBaseColorOffset->u32Green > 100)
        || (pstSixBaseColorOffset->u32Blue > 100)
        || (pstSixBaseColorOffset->u32Cyan > 100)
        || (pstSixBaseColorOffset->u32Magenta > 100)
        || (pstSixBaseColorOffset->u32Yellow > 100))
    {
        HI_ERR_PQ("out of range\n");
        return HI_FAILURE;
    }

    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Red     = pstSixBaseColorOffset->u32Red;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Green   = pstSixBaseColorOffset->u32Green;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Blue    = pstSixBaseColorOffset->u32Blue;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Cyan    = pstSixBaseColorOffset->u32Cyan;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Magenta = pstSixBaseColorOffset->u32Magenta;
    sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Yellow  = pstSixBaseColorOffset->u32Yellow;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCACMSixBaseColorLevel(HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColorOffset)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstSixBaseColorOffset);

    pstSixBaseColorOffset->u32Red     = sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Red;
    pstSixBaseColorOffset->u32Green   = sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Green;
    pstSixBaseColorOffset->u32Blue    = sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Blue;
    pstSixBaseColorOffset->u32Cyan    = sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Cyan;
    pstSixBaseColorOffset->u32Magenta = sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Magenta;
    pstSixBaseColorOffset->u32Yellow  = sg_stPQLCACMInfo.stLCACMSixbaseColor.u32Yellow;

    return HI_SUCCESS;
}

static HI_S32 PQ_MNG_GetHdrLcacmCfg(HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo, HI_PQ_HDR_CFG *pstPqHdrCfg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstXdrFrameInfo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqHdrCfg);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enSrcFrameType, HI_DRV_VIDEO_FRAME_TYPE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enDispType, HI_PQ_DISP_TYPE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enInCS, HI_DRV_CS_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enOutCS, HI_DRV_CS_BUTT);

    /* sdr->sdr : use hdr adjust para */
    if ((HI_DRV_VIDEO_FRAME_TYPE_SDR == pstXdrFrameInfo->enSrcFrameType)
        && (HI_PQ_DISP_TYPE_NORMAL == pstXdrFrameInfo->enDispType))
    {
        sg_stPQLCACMInfo.bHdrProcessEn = HI_FALSE;
        return HI_SUCCESS;
    }
    else
    {
        sg_stPQLCACMInfo.bHdrProcessEn = HI_TRUE;
    }

    s32Ret = PQ_HAL_GetHdrLcacmCfg(pstXdrFrameInfo);

    return s32Ret;
}


static stPQAlgFuncs stLCACMFuncs =
{
    .Init                 = PQ_MNG_InitLCACM,
    .DeInit               = PQ_MNG_DeInitLCACM,
    .SetEnable            = PQ_MNG_SetLCACMEn,
    .GetEnable            = PQ_MNG_GetLCACMEn,
    .SetDemo              = PQ_MNG_SetLCACMDemoEn,
    .GetDemo              = PQ_MNG_GetLCACMDemoEn,
    .SetDemoMode          = PQ_MNG_SetLCACMDemoMode,
    .GetDemoMode          = PQ_MNG_GetLCACMDemoMode,
    .SetStrength          = PQ_MNG_SetLCACMGainLevel,
    .GetStrength          = PQ_MNG_GetLCACMGainLevel,
    .SetFleshToneLevel    = PQ_MNG_SetLCACMFleshToneLevel,
    .GetFleshToneLevel    = PQ_MNG_GetLCACMFleshToneLevel,
    .SetSixBaseColorLevel = PQ_MNG_SetLCACMSixBaseColorLevel,
    .GetSixBaseColorLevel = PQ_MNG_GetLCACMSixBaseColorLevel,
    .SetColorEnhanceMode  = PQ_MNG_SetLCACMColorEnhanceMode,
    .GetColorEnhanceMode  = PQ_MNG_GetLCACMColorEnhanceMode,
    .GetHdrCfg            = PQ_MNG_GetHdrLcacmCfg,
};

HI_S32 PQ_MNG_RegisterLCACM(PQ_REG_TYPE_E enType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_COLOR, enType, PQ_BIN_ADAPT_SINGLE, "acm", HI_NULL, &stLCACMFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterLCACM(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_COLOR);

    return s32Ret;
}

