/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : drv_pq.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2014/04/01
******************************************************************************/
#include "drv_pq.h"
#include "drv_pdm_ext.h"
#include "drv_pq_ext.h"
#include "hi_drv_dev.h"
#include "drv_pq_comm.h"

PQ_PARAM_S          *g_pstPqParam = HI_NULL;
PQ_MMZ_BUF_S        g_stPqBinBuf;
HI_BOOL             g_bLoadPqBin;
HI_PQ_ALGIP_SEL_E   g_enAlgIPSel = HI_PQ_ALGIP_SEL_VPSS;
HI_BOOL             g_bProcAlgTimeCntEn = HI_FALSE; /* each alg delay count */

HI_U32 g_u32ImageWidth  = 1280;
HI_U32 g_u32ImageHeight = 720;
HI_U32 g_u32OutWidth    = 1280;
HI_U32 g_u32OutHeight   = 720;

HI_DRV_PQ_PARAM_S stPqParam;
PQ_STATUS_S g_stPqStatus = {0};

static HI_U32  sg_u32DemoCoordinate = 50; /*range: 0~100*/
static HI_BOOL sg_bFastBoot         = HI_FALSE;
static HI_BOOL sg_bDefaultParam     = HI_FALSE; /* rwzb flag */
static HI_DRV_PQ_MCDI_SPLIT_MODE_E sg_enMcdiSplitMode[VPSS_HANDLE_NUM] = {HI_DRV_PQ_MCDI_SPLIT_MODE_0}; /* vpss mcid split mode */

HI_DRV_PQ_VP_MODE_E sg_enVPMode[HI_DRV_PQ_VP_TYPE_BUTT] =
{
    HI_DRV_PQ_VIDEOPHONE_MODE_RECOMMEND,
    HI_DRV_PQ_VIDEOPHONE_MODE_RECOMMEND,
    HI_DRV_PQ_VIDEOPHONE_MODE_RECOMMEND,
};

/* handle num limit value , pq module can both be the limit value */
HI_ULONG sg_ulProcAlgTimeCnt[VPSS_HANDLE_NUM+1][HI_PQ_MODULE_ALL+1]   = {{0, 0}};
HI_ULONG sg_ulProcAlgStartTime[VPSS_HANDLE_NUM+1][HI_PQ_MODULE_ALL+1] = {{0, 0}};
HI_ULONG sg_ulProcAlgEndTime[VPSS_HANDLE_NUM+1][HI_PQ_MODULE_ALL+1]   = {{0, 0}};

static HI_S32 DRV_PQ_GetFlashPqBin(PQ_PARAM_S *pstPqParam);
static HI_S32 DRV_PQ_GetPicSetting(HI_VOID);

PQ_EXPORT_FUNC_S   g_PqExportFuncs =
{
    .pfnPqSuspend                 = DRV_PQ_Suspend,
    .pfnPqResume                  = DRV_PQ_Resume,
    .pfnPQ_UpdateVpssPQ           = DRV_PQ_UpdateVpssPQ,
    .pfnPQ_UpdateVdpPQ            = DRV_PQ_UpdateVdpPQ,
    .pfnPQ_UpdateVdpCSC           = DRV_PQ_UpdateVdpCSC,
    .pfnPQ_UpdateDCIWin           = DRV_PQ_UpdateDCIWin,
    .pfnPQ_GetACCHistGram         = DRV_PQ_GetACCHistGram,
    .pfnPQ_UpdateACCHistGram      = DRV_PQ_UpdateACCHistGram,
    .pfnPQ_SetZme                 = DRV_PQ_SetZme,
    .pfnPQ_SetVpssZme             = DRV_PQ_SetVpssZme,
    .pfnPQ_SetVpssLCHDR           = DRV_PQ_SetVpssLCHDR,
    .pfnPQ_GetCSCCoef             = DRV_PQ_GetCSCCoef,
    .pfnPQ_Get8BitCSCCoef         = DRV_PQ_Get8BitCSCCoef,
    .pfnPQ_GetWbcInfo             = DRV_PQ_GetWbcInfo,
    .pfnPQ_SetAlgCalcCfg          = DRV_PQ_SetAlgCalcCfg,
    .pfnPQ_SetVdpAlgCalcCfg       = DRV_PQ_SetVdpAlgCalcCfg,
    .pfnPQ_GetHDPictureSetting    = DRV_PQ_GetHDPictureSetting,
    .pfnPQ_GetSDPictureSetting    = DRV_PQ_GetSDPictureSetting,
    .pfnPQ_SetHDPictureSetting    = DRV_PQ_SetHDPictureSetting,
    .pfnPQ_SetSDPictureSetting    = DRV_PQ_SetSDPictureSetting,
    .pfnPQ_GetHDVideoSetting      = DRV_PQ_GetHDVideoSetting,
    .pfnPQ_GetSDVideoSetting      = DRV_PQ_GetSDVideoSetting,
    .pfnPQ_SetHDVideoSetting      = DRV_PQ_SetHDVideoSetting,
    .pfnPQ_SetSDVideoSetting      = DRV_PQ_SetSDVideoSetting,
    .pfnPQ_GetVdpZmeCoef          = DRV_PQ_GetVdpZmeCoef,
    .pfnPQ_GetVdpZmeStrategy      = DRV_PQ_GetVdpZmeStrategy,
    .pfnPQ_SetGfxZme              = DRV_PQ_SetGfxZme,
    .pfnPQ_SetGfxCscCoef          = DRV_PQ_SetGfxCscCoef,
    .pfnPQ_GetGfxHdrCfg           = DRV_PQ_GetGfxHdrCfg,
    .pfnPQ_GetHdrCfg              = DRV_PQ_GetHdrCfg,
    .pfnPQ_GetMcdiSplitMode       = DRV_PQ_GetMcdiSplitMode,
};

HI_S32 HI_DRV_PQ_DeInit(HI_VOID)
{
    HI_U32 i;

    HI_DRV_MODULE_UnRegister(HI_ID_PQ);
    if (HI_NULL != g_stPqBinBuf.pu8StartVirAddr)
    {
        PQ_HAL_UnmapAndRelease(&g_stPqBinBuf);
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;
    }

    PQ_TABLE_DeInitPQTable();
    PQ_HAL_Deinit();

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        if (PQ_FUNC_CALL(i, DeInit))
        {
            GET_ALG_FUN(i)->DeInit();
        }
    }

#ifdef PQ_ALG_ZME
    PQ_MNG_UnRegisterZme();
#endif

#ifdef PQ_ALG_CSC
    PQ_MNG_UnRegisterCSC();
#endif

#ifdef PQ_ALG_DEI
    PQ_MNG_UnRegisterDEI();
#endif

#ifdef PQ_ALG_DB
    PQ_MNG_UnRegisterDB();
#endif

#ifdef PQ_ALG_DM
    PQ_MNG_UnRegisterDM();
#endif

#ifdef PQ_ALG_DERING
    PQ_MNG_UnRegisterDR();
#endif

#ifdef PQ_ALG_DESHOOT
    PQ_MNG_UnRegisterDS();
#endif

#ifdef PQ_ALG_ARTDS
    PQ_MNG_UnRegisterArtDS();
#endif

#ifdef PQ_ALG_TNR
    PQ_MNG_UnRegisterTNR();
#endif

#ifdef PQ_ALG_SNR
    PQ_MNG_UnRegisterSNR();
#endif

#ifdef PQ_ALG_GFXCSC
    PQ_MNG_UnRegisterGfxCSC();
#endif

#ifdef PQ_ALG_GFXZME
    PQ_MNG_UnRegisterGfxZme();
#endif

#ifdef PQ_ALG_GFXHDR
    PQ_MNG_UnRegisterGfxHdr();
#endif

#ifdef PQ_ALG_SHARPEN
    PQ_MNG_UnRegisterSharp();
#endif

#ifdef PQ_ALG_ACM
    PQ_MNG_UnRegisterACM();
#endif

#ifdef PQ_ALG_LCACM
    PQ_MNG_UnRegisterLCACM();
#endif

#ifdef PQ_ALG_DCI
    PQ_MNG_UnRegisterDCI();
#endif

#ifdef PQ_ALG_ACC
    PQ_MNG_UnRegisterACC();
#endif

#ifdef PQ_ALG_FMD
    PQ_MNG_UnRegisterFMD();
#endif

#ifdef PQ_ALG_HDR
    PQ_MNG_UnRegisterHDR();
#endif

#ifdef PQ_ALG_VPSSCSC
    PQ_MNG_UnRegisterVPSSCSC();
#endif

#ifdef PQ_ALG_VPSSGAMMA
    PQ_MNG_UnRegisterVPSSGAMMA();
#endif

#ifdef PQ_ALG_VDP4KSNR
    PQ_MNG_UnRegisterVDP4KSNR();
#endif
#ifdef PQ_ALG_LCHDR
    PQ_MNG_UnRegisterLCHDR();
#endif

    return HI_SUCCESS;
}


HI_S32 HI_DRV_PQ_Init(HI_CHAR *pszPath)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i = 0;
    g_bLoadPqBin = HI_FALSE;
    g_pstPqParam = HI_NULL;

    s32Ret = HI_DRV_MODULE_Register(HI_ID_PQ, PQ_NAME, (HI_VOID *)&g_PqExportFuncs);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_PQ("ERR: HI_DRV_MODULE_Register!\n");
        return s32Ret;
    }

    s32Ret = PQ_HAL_AllocAndMap("PQ_FLASH_BIN", HI_NULL, sizeof(PQ_PARAM_S), 0, &g_stPqBinBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_PQ("ERR: Pqdriver mmz memory failed!\n");
        g_bLoadPqBin = HI_FALSE;
        return s32Ret;
    }

    g_pstPqParam = (PQ_PARAM_S *)g_stPqBinBuf.pu8StartVirAddr;
    HI_INFO_PQ("\n g_stPqBinBuf.u32StartPhyAddr = 0x%x,g_stPqBinBuf.pu8StartVirAddr = 0x%x\n", g_stPqBinBuf.u32StartPhyAddr, g_stPqBinBuf.pu8StartVirAddr);

    s32Ret = DRV_PQ_GetFlashPqBin(g_pstPqParam);
    if (HI_SUCCESS != s32Ret)
    {
        //HI_ERR_PQ("Load PQBin failed!\n");
        g_bLoadPqBin = HI_FALSE;
    }
    else
    {
        g_bLoadPqBin = HI_TRUE;
    }

    s32Ret = DRV_PQ_GetPicSetting();
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PQ("ERR: DRV_PQ_GetPicSetting failed!\n");
        stPqParam.stSDPictureSetting.u16Brightness = 50;
        stPqParam.stSDPictureSetting.u16Contrast   = 50;
        stPqParam.stSDPictureSetting.u16Hue        = 50;
        stPqParam.stSDPictureSetting.u16Saturation = 50;
        stPqParam.stHDPictureSetting.u16Brightness = 50;
        stPqParam.stHDPictureSetting.u16Contrast   = 50;
        stPqParam.stHDPictureSetting.u16Hue        = 50;
        stPqParam.stHDPictureSetting.u16Saturation = 50;
        stPqParam.stSDVideoSetting.u16Brightness   = 128;
        stPqParam.stSDVideoSetting.u16Contrast     = 128;
        stPqParam.stSDVideoSetting.u16Hue          = 128;
        stPqParam.stSDVideoSetting.u16Saturation   = 128;
        stPqParam.stHDVideoSetting.u16Brightness   = 128;
        stPqParam.stHDVideoSetting.u16Contrast     = 128;
        stPqParam.stHDVideoSetting.u16Hue          = 128;
        stPqParam.stHDVideoSetting.u16Saturation   = 128;
    }

    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Brightness = 128;
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Contrast   = 128;
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Hue        = 128;
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Saturation = 128;

    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Brightness  = 128;
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Contrast    = 128;
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Hue         = 128;
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Saturation  = 128;


#ifdef PQ_ALG_ZME
    PQ_MNG_RegisterZme(REG_TYPE_ALL);
#endif

#ifdef PQ_ALG_CSC
    PQ_MNG_RegisterCSC(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_DEI
    PQ_MNG_RegisterDEI(REG_TYPE_VPSS);
#endif

#ifdef PQ_ALG_TNR
    PQ_MNG_RegisterTNR(REG_TYPE_VPSS);
#endif

#ifdef PQ_ALG_SNR
    PQ_MNG_RegisterSNR(REG_TYPE_VPSS);
#endif

#ifdef PQ_ALG_DB
    PQ_MNG_RegisterDB(REG_TYPE_VPSS);
#endif

#ifdef PQ_ALG_DM
    PQ_MNG_RegisterDM(REG_TYPE_VPSS);
#endif

#ifdef PQ_ALG_DERING
    PQ_MNG_RegisterDR(REG_TYPE_VPSS);
#endif
#ifdef PQ_ALG_DESHOOT
    PQ_MNG_RegisterDS(REG_TYPE_VPSS);
#endif

#ifdef PQ_ALG_ARTDS
    PQ_MNG_RegisterArtDS(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_GFXCSC
    PQ_MNG_RegisterGfxCSC();
#endif

#ifdef PQ_ALG_GFXZME
    PQ_MNG_RegisterGfxZme();
#endif

#ifdef PQ_ALG_GFXHDR
    PQ_MNG_RegisterGfxHdr(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_SHARPEN
    PQ_MNG_RegisterSharp(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_ACM
    PQ_MNG_RegisterACM(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_LCACM
    PQ_MNG_RegisterLCACM(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_DCI
    PQ_MNG_RegisterDCI(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_ACC
    PQ_MNG_RegisterACC(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_FMD
    PQ_MNG_RegisterFMD(REG_TYPE_VPSS);
#endif

#ifdef PQ_ALG_HDR
    PQ_MNG_RegisterHDR(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_VPSSCSC
    PQ_MNG_RegisterVPSSCSC(REG_TYPE_VPSS);
#endif

#ifdef PQ_ALG_VPSSGAMMA
    PQ_MNG_RegisterVPSSGAMMA(REG_TYPE_VPSS);
#endif

#ifdef PQ_ALG_VDP4KSNR
    PQ_MNG_RegisterVDP4KSNR(REG_TYPE_VDP);
#endif

#ifdef PQ_ALG_LCHDR
    PQ_MNG_RegisterLCHDR(REG_TYPE_VPSS);
#endif

    s32Ret = PQ_HAL_Init();
    if (HI_SUCCESS != s32Ret)
    {
        PQ_HAL_UnmapAndRelease(&g_stPqBinBuf);
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init PQ device error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_TABLE_InitPQTable(g_pstPqParam, !g_bLoadPqBin);
    if (HI_SUCCESS != s32Ret)
    {
        PQ_HAL_UnmapAndRelease(&g_stPqBinBuf);
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        PQ_HAL_Deinit();

        HI_ERR_PQ("Init PQ table failure!\n");
        return HI_FAILURE;
    }

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        if (HI_NULL == GET_ALG(i))
        {
            continue;
        }

        if (GET_ALG_FUN(i)->Init)
        {
            GET_ALG_FUN(i)->Init(g_pstPqParam, !g_bLoadPqBin);
        }

        stPqParam.bDemoOnOff[i]   = HI_FALSE;
        stPqParam.bModuleOnOff[i] = HI_TRUE;
        stPqParam.u32Strength[i]  = 50;
    }

    stPqParam.stColorEnhance.enColorEnhanceType      = HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
    stPqParam.stColorEnhance.unColorGain.enColorMode = HI_PQ_COLOR_MODE_RECOMMEND;
    stPqParam.enDemoMode                             = HI_PQ_DEMO_MODE_FIXED_L;  /*default left enable */
    g_stPqStatus.enTunMode                           = PQ_TUN_NORMAL;
    g_stPqStatus.enImageMode                         = PQ_IMAGE_MODE_NORMAL;

    /*set gfx  brightness/contrast/hue/saturation*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, (HI_PQ_PICTURE_SETTING_S *)&stPqParam.stSDPictureSetting);
        GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, (HI_PQ_PICTURE_SETTING_S *)&stPqParam.stHDPictureSetting);
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    if (PM_EVENT_FREEZE == state.event)
    {
        sg_bFastBoot = HI_TRUE;
    }
    else
    {
        sg_bFastBoot = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_Resume(PM_BASEDEV_S *pdev)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_TRUE == sg_bFastBoot)
    {
        s32Ret = DRV_PQ_GetPicSetting();
        if (HI_SUCCESS != s32Ret)
        {
            HI_WARN_PQ("ERR: DRV_PQ_GetPicSetting failed!\n");
        }
    }

    /*set gfx  brightness/contrast/hue/saturation*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, (HI_PQ_PICTURE_SETTING_S *)&stPqParam.stSDPictureSetting);
        GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, (HI_PQ_PICTURE_SETTING_S *)&stPqParam.stHDPictureSetting);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXZME, SetResume))
    {
        GET_ALG_FUN(HI_PQ_MODULE_GFXZME)->SetResume(!g_bLoadPqBin);
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetSDBrightness(HI_U32 *pu32Brightness)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Brightness);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);
            pqprint(PQ_PRN_CSC, "Get SD Brightness: %d\n", *pu32Brightness);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetSDBrightness(HI_U32 u32Brightness)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Brightness, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
    }

    stPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        stPqParam.stSDVideoSetting.u16Brightness = LEVEL2NUM(u32Brightness);
    }

    /*gfx*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, GetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->GetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
    }

    stPictureSetting.u16Brightness = u32Brightness;
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        stPqParam.stSDPictureSetting.u16Brightness = u32Brightness;
    }

    pqprint(PQ_PRN_CSC, "Set SD Brightness: %d\n", u32Brightness);
    return s32Ret;
}

HI_S32 DRV_PQ_GetSDContrast(HI_U32 *pu32Contrast)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Contrast);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Contrast = NUM2LEVEL(stPictureSetting.u16Contrast);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    pqprint(PQ_PRN_CSC, "Get SD Contrast: %d\n", *pu32Contrast);

    return s32Ret;
}

HI_S32 DRV_PQ_SetSDContrast(HI_U32 u32Contrast)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Contrast, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
    }

    stPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        stPqParam.stSDVideoSetting.u16Contrast   = LEVEL2NUM(u32Contrast);
    }

    /*gfx*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, GetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->GetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
    }

    stPictureSetting.u16Contrast = u32Contrast;
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        stPqParam.stSDPictureSetting.u16Contrast = u32Contrast;
    }

    pqprint(PQ_PRN_CSC, "Set SD Contrast: %d\n", u32Contrast);
    return s32Ret;
}

HI_S32 DRV_PQ_GetSDHue(HI_U32 *pu32Hue)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Hue);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Hue = NUM2LEVEL(stPictureSetting.u16Hue);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    pqprint(PQ_PRN_CSC, "Get SD Hue: %d\n", *pu32Hue);
    return s32Ret;
}

HI_S32 DRV_PQ_SetSDHue(HI_U32 u32Hue)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Hue, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
    }

    stPictureSetting.u16Hue = LEVEL2NUM(u32Hue);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        stPqParam.stSDVideoSetting.u16Hue   = LEVEL2NUM(u32Hue);
    }

    /*gfx*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, GetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->GetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
    }

    stPictureSetting.u16Hue = u32Hue;
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        stPqParam.stSDPictureSetting.u16Hue = u32Hue;
    }

    pqprint(PQ_PRN_CSC, "Set SD Hue: %d\n", u32Hue);
    return s32Ret;
}

HI_S32 DRV_PQ_GetSDSaturation(HI_U32 *pu32Saturation)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    pqprint(PQ_PRN_CSC, "Get SD Saturation: %d\n", *pu32Saturation);
    return s32Ret;
}

HI_S32 DRV_PQ_SetSDSaturation(HI_U32 u32Saturation)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Saturation, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
    }

    stPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        stPqParam.stSDVideoSetting.u16Saturation   = LEVEL2NUM(u32Saturation);
    }

    /*gfx*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, GetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->GetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
    }

    stPictureSetting.u16Saturation = u32Saturation;
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, &stPictureSetting);
        stPqParam.stSDPictureSetting.u16Saturation = u32Saturation;
    }

    pqprint(PQ_PRN_CSC, "Set SD Saturation: %d\n", u32Saturation);
    return s32Ret;
}

HI_S32 DRV_PQ_GetHDBrightness(HI_U32 *pu32Brightness)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Brightness);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    pqprint(PQ_PRN_CSC, "Get HD Brightness: %d\n", *pu32Brightness);
    return s32Ret;
}

HI_S32 DRV_PQ_SetHDBrightness(HI_U32 u32Brightness)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Brightness, 100);

    /*video*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
    }

    stPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        stPqParam.stHDVideoSetting.u16Brightness   = LEVEL2NUM(u32Brightness);
    }

    /* HDR CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrCSCVideoSetting(&stPictureSetting);
    }

    /*gfx*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, GetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->GetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
    }

    stPictureSetting.u16Brightness = u32Brightness;
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        stPqParam.stHDPictureSetting.u16Brightness = u32Brightness;
    }

    /* GfxHdr CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXHDR, SetHdrCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_GFXHDR)->SetHdrCSCVideoSetting(&stPictureSetting);
    }

    pqprint(PQ_PRN_CSC, "Set HD Brightness: %d\n", u32Brightness);

    return s32Ret;
}


HI_S32 DRV_PQ_GetHDContrast(HI_U32 *pu32Contrast)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Contrast);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Contrast = NUM2LEVEL(stPictureSetting.u16Contrast);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    pqprint(PQ_PRN_CSC, "Get HD Contrast: %d\n", *pu32Contrast);
    return s32Ret;
}

HI_S32 DRV_PQ_SetHDContrast(HI_U32 u32Contrast)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Contrast, 100);

    /*video*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
    }

    stPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        stPqParam.stHDVideoSetting.u16Contrast = LEVEL2NUM(u32Contrast);
    }

    /* HDR CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrCSCVideoSetting(&stPictureSetting);
    }

    /*gfx*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, GetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->GetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
    }

    stPictureSetting.u16Contrast = u32Contrast;
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        stPqParam.stHDPictureSetting.u16Contrast = u32Contrast;
    }

    /* GfxHdr CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXHDR, SetHdrCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_GFXHDR)->SetHdrCSCVideoSetting(&stPictureSetting);
    }

    pqprint(PQ_PRN_CSC, "Set HD Contrast: %d\n", u32Contrast);
    return s32Ret;
}

HI_S32 DRV_PQ_GetHDHue(HI_U32 *pu32Hue)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Hue);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Hue = NUM2LEVEL(stPictureSetting.u16Hue);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    pqprint(PQ_PRN_CSC, "Get HD Hue: %d\n", *pu32Hue);
    return s32Ret;
}

HI_S32 DRV_PQ_SetHDHue(HI_U32 u32Hue)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Hue, 100);

    /* Video CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
    }

    stPictureSetting.u16Hue = LEVEL2NUM(u32Hue);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        stPqParam.stHDVideoSetting.u16Hue   = LEVEL2NUM(u32Hue);
    }

    /* HDR CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrCSCVideoSetting(&stPictureSetting);
    }

    /*gfx*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, GetGfxCSCPictureSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->GetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
    }

    stPictureSetting.u16Hue = u32Hue;
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        stPqParam.stHDPictureSetting.u16Hue = u32Hue;
    }

    /* GfxHdr CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXHDR, SetHdrCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_GFXHDR)->SetHdrCSCVideoSetting(&stPictureSetting);
    }

    pqprint(PQ_PRN_CSC, "Set HD Hue: %d\n", u32Hue);
    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetHDSaturation(HI_U32 *pu32Saturation)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    pqprint(PQ_PRN_CSC, "Get HD Saturation: %d\n", *pu32Saturation);
    return s32Ret;
}


HI_S32 DRV_PQ_SetHDSaturation(HI_U32 u32Saturation)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Saturation, 100);

    /* Video CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
    }

    stPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        stPqParam.stHDVideoSetting.u16Saturation   = LEVEL2NUM(u32Saturation);
    }

    /* HDR CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrCSCVideoSetting(&stPictureSetting);
    }

    /*gfx*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, GetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->GetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
    }

    stPictureSetting.u16Saturation = u32Saturation;
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, &stPictureSetting);
        stPqParam.stHDPictureSetting.u16Saturation = u32Saturation;
    }

    /* GfxHdr CSC */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXHDR, SetHdrCSCVideoSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_GFXHDR)->SetHdrCSCVideoSetting(&stPictureSetting);
    }

    pqprint(PQ_PRN_CSC, "Set HD Saturation: %d\n", u32Saturation);

    return s32Ret;
}

//vpss csc
HI_S32 DRV_PQ_GetVPPreviewBrightness(HI_U32 *pu32Brightness)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Brightness);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);
        }
        else
        {
            HI_ERR_PQ("get vpsscsc brightness error\n");
        }
    }

    pqprint(PQ_PRN_VPSSCSC, "Get VPSS Brightness: %d\n", *pu32Brightness);
    return s32Ret;
}

HI_S32 DRV_PQ_SetVPPreviewBrightness(HI_U32 u32Brightness)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Brightness, 100);

    /*video*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
    }

    stPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
        stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Brightness   = LEVEL2NUM(u32Brightness);
    }

    pqprint(PQ_PRN_VPSSCSC, "Set VPSS Brightness: %d\n", u32Brightness);

    return s32Ret;
}


HI_S32 DRV_PQ_GetVPPreviewContrast(HI_U32 *pu32Contrast)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Contrast);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Contrast = NUM2LEVEL(stPictureSetting.u16Contrast);
        }
        else
        {
            HI_ERR_PQ("get vpsscsc contrast error\n");
        }
    }

    pqprint(PQ_PRN_VPSSCSC, "Get VPSS Contrast: %d\n", *pu32Contrast);
    return s32Ret;
}

HI_S32 DRV_PQ_SetVPPreviewContrast(HI_U32 u32Contrast)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Contrast, 100);

    /*video*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
    }

    stPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
        stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Contrast = LEVEL2NUM(u32Contrast);
    }

    pqprint(PQ_PRN_VPSSCSC, "Set VPSS Contrast: %d\n", u32Contrast);
    return s32Ret;
}

HI_S32 DRV_PQ_GetVPPreviewHue(HI_U32 *pu32Hue)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Hue);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Hue = NUM2LEVEL(stPictureSetting.u16Hue);
        }
        else
        {
            HI_ERR_PQ("get vpsscsc hue error\n");
        }
    }

    pqprint(PQ_PRN_VPSSCSC, "Get VPSS Hue: %d\n", *pu32Hue);
    return s32Ret;
}

HI_S32 DRV_PQ_SetVPPreviewHue(HI_U32 u32Hue)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Hue, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
    }

    stPictureSetting.u16Hue = LEVEL2NUM(u32Hue);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
        stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Hue   = LEVEL2NUM(u32Hue);
    }

    pqprint(PQ_PRN_VPSSCSC, "Set VPSS Hue: %d\n", u32Hue);
    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetVPPreviewSaturation(HI_U32 *pu32Saturation)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);
        }
        else
        {
            HI_ERR_PQ("get vpsscsc saturation error\n");
        }
    }

    pqprint(PQ_PRN_VPSSCSC, "Get VPSS Saturation: %d\n", *pu32Saturation);
    return s32Ret;
}


HI_S32 DRV_PQ_SetVPPreviewSaturation(HI_U32 u32Saturation)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Saturation, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
    }

    stPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stPictureSetting);
        stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Saturation   = LEVEL2NUM(u32Saturation);
    }

    pqprint(PQ_PRN_VPSSCSC, "Set VPSS Saturation: %d\n", u32Saturation);

    return s32Ret;
}

//vpss csc
HI_S32 DRV_PQ_GetVPRemoteBrightness(HI_U32 *pu32Brightness)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Brightness);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);
        }
        else
        {
            HI_ERR_PQ("get vpsscsc brightness error\n");
        }
    }

    pqprint(PQ_PRN_VPSSCSC, "Get VPSS Brightness: %d\n", *pu32Brightness);
    return s32Ret;
}

HI_S32 DRV_PQ_SetVPRemoteBrightness(HI_U32 u32Brightness)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Brightness, 100);

    /*video*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
    }

    stPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
        stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Brightness   = LEVEL2NUM(u32Brightness);
    }

    pqprint(PQ_PRN_VPSSCSC, "Set VPSS Brightness: %d\n", u32Brightness);

    return s32Ret;
}


HI_S32 DRV_PQ_GetVPRemoteContrast(HI_U32 *pu32Contrast)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Contrast);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Contrast = NUM2LEVEL(stPictureSetting.u16Contrast);
        }
        else
        {
            HI_ERR_PQ("get vpsscsc contrast error\n");
        }
    }

    pqprint(PQ_PRN_VPSSCSC, "Get VPSS Contrast: %d\n", *pu32Contrast);
    return s32Ret;
}

HI_S32 DRV_PQ_SetVPRemoteContrast(HI_U32 u32Contrast)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Contrast, 100);

    /*video*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
    }

    stPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
        stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Contrast = LEVEL2NUM(u32Contrast);
    }

    pqprint(PQ_PRN_VPSSCSC, "Set VPSS Contrast: %d\n", u32Contrast);
    return s32Ret;
}

HI_S32 DRV_PQ_GetVPRemoteHue(HI_U32 *pu32Hue)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Hue);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Hue = NUM2LEVEL(stPictureSetting.u16Hue);
        }
        else
        {
            HI_ERR_PQ("get vpsscsc hue error\n");
        }
    }

    pqprint(PQ_PRN_VPSSCSC, "Get VPSS Hue: %d\n", *pu32Hue);
    return s32Ret;
}

HI_S32 DRV_PQ_SetVPRemoteHue(HI_U32 u32Hue)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Hue, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
    }

    stPictureSetting.u16Hue = LEVEL2NUM(u32Hue);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
        stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Hue   = LEVEL2NUM(u32Hue);
    }

    pqprint(PQ_PRN_VPSSCSC, "Set VPSS Hue: %d\n", u32Hue);
    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetVPRemoteSaturation(HI_U32 *pu32Saturation)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
        if (HI_SUCCESS == s32Ret)
        {
            *pu32Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);
        }
        else
        {
            HI_ERR_PQ("get vpsscsc saturation error\n");
        }
    }

    pqprint(PQ_PRN_VPSSCSC, "Get VPSS Saturation: %d\n", *pu32Saturation);
    return s32Ret;
}


HI_S32 DRV_PQ_SetVPRemoteSaturation(HI_U32 u32Saturation)
{
    HI_PQ_PICTURE_SETTING_S stPictureSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Saturation, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
    }

    stPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stPictureSetting);
        stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Saturation   = LEVEL2NUM(u32Saturation);
    }

    pqprint(PQ_PRN_VPSSCSC, "Set VPSS Saturation: %d\n", u32Saturation);

    return s32Ret;
}

/* get brightness, contrast, hue, saturation  of HD Video*/
HI_S32 DRV_PQ_GetHDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_PQ_PICTURE_SETTING_S stSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_1, &stSetting);
        if (HI_SUCCESS == s32Ret)
        {
            pstSetting->u16Brightness = NUM2LEVEL(stSetting.u16Brightness);
            pstSetting->u16Contrast   = NUM2LEVEL(stSetting.u16Contrast);
            pstSetting->u16Hue        = NUM2LEVEL(stSetting.u16Hue);
            pstSetting->u16Saturation = NUM2LEVEL(stSetting.u16Saturation);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    return HI_SUCCESS;
}


/* set brightness, contrast, hue, saturation  of HD Video*/
HI_S32 DRV_PQ_SetHDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_PQ_PICTURE_SETTING_S stSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Hue, 100);

    pqprint(PQ_PRN_CSC, "Set Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n",
            pstSetting->u16Brightness, pstSetting->u16Contrast, pstSetting->u16Hue, pstSetting->u16Saturation);

    /* 0~100 to 0~255 */
    stSetting.u16Brightness = LEVEL2NUM(pstSetting->u16Brightness);
    stSetting.u16Contrast   = LEVEL2NUM(pstSetting->u16Contrast);
    stSetting.u16Hue        = LEVEL2NUM(pstSetting->u16Hue);
    stSetting.u16Saturation = LEVEL2NUM(pstSetting->u16Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_1, &stSetting);
    }

    /* up drv layer; we use 0~100 level value */
    stPqParam.stHDVideoSetting.u16Brightness = LEVEL2NUM(pstSetting->u16Brightness);
    stPqParam.stHDVideoSetting.u16Contrast   = LEVEL2NUM(pstSetting->u16Contrast);
    stPqParam.stHDVideoSetting.u16Hue        = LEVEL2NUM(pstSetting->u16Hue);
    stPqParam.stHDVideoSetting.u16Saturation = LEVEL2NUM(pstSetting->u16Saturation);

    return s32Ret;
}


//vpss csc
/* get VPSS vpss vidiophone brightness, contrast, hue, saturation  of HD Video*/
HI_S32 DRV_PQ_GetVPPreviewVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_PQ_PICTURE_SETTING_S stSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stSetting);
        if (HI_SUCCESS == s32Ret)
        {
            pstSetting->u16Brightness = NUM2LEVEL(stSetting.u16Brightness);
            pstSetting->u16Contrast   = NUM2LEVEL(stSetting.u16Contrast);
            pstSetting->u16Hue        = NUM2LEVEL(stSetting.u16Hue);
            pstSetting->u16Saturation = NUM2LEVEL(stSetting.u16Saturation);
        }
        else
        {
            HI_ERR_PQ("get vpss csc error\n");
        }
    }

    return HI_SUCCESS;
}

/* set VPSS brightness, contrast, hue, saturation  of HD Video*/
HI_S32 DRV_PQ_SetVPPreviewVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_PQ_PICTURE_SETTING_S stSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Hue, 100);

    pqprint(PQ_PRN_VPSSCSC, "Set vpss Preview Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n",
            pstSetting->u16Brightness, pstSetting->u16Contrast, pstSetting->u16Hue, pstSetting->u16Saturation);

    /* 0~100 to 0~255 */
    stSetting.u16Brightness = LEVEL2NUM(pstSetting->u16Brightness);
    stSetting.u16Contrast   = LEVEL2NUM(pstSetting->u16Contrast);
    stSetting.u16Hue        = LEVEL2NUM(pstSetting->u16Hue);
    stSetting.u16Saturation = LEVEL2NUM(pstSetting->u16Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_PREVIEW, &stSetting);
    }

    /* up drv layer; we use 0~100 level value */
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Brightness = LEVEL2NUM(pstSetting->u16Brightness);
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Contrast   = LEVEL2NUM(pstSetting->u16Contrast);
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Hue        = LEVEL2NUM(pstSetting->u16Hue);
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Saturation = LEVEL2NUM(pstSetting->u16Saturation);

    return s32Ret;
}

/* get VPSS vpss vidiophone brightness, contrast, hue, saturation  of HD Video*/
HI_S32 DRV_PQ_GetVPRemoteVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_PQ_PICTURE_SETTING_S stSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, GetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->GetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stSetting);
        if (HI_SUCCESS == s32Ret)
        {
            pstSetting->u16Brightness = NUM2LEVEL(stSetting.u16Brightness);
            pstSetting->u16Contrast   = NUM2LEVEL(stSetting.u16Contrast);
            pstSetting->u16Hue        = NUM2LEVEL(stSetting.u16Hue);
            pstSetting->u16Saturation = NUM2LEVEL(stSetting.u16Saturation);
        }
        else
        {
            HI_ERR_PQ("get vpss csc error\n");
        }
    }

    return HI_SUCCESS;
}


/* set VPSS brightness, contrast, hue, saturation  of HD Video*/
HI_S32 DRV_PQ_SetVPRemoteVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_PQ_PICTURE_SETTING_S stSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Hue, 100);

    pqprint(PQ_PRN_VPSSCSC, "Set vpss Remote Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n",
            pstSetting->u16Brightness, pstSetting->u16Contrast, pstSetting->u16Hue, pstSetting->u16Saturation);

    /* 0~100 to 0~255 */
    stSetting.u16Brightness = LEVEL2NUM(pstSetting->u16Brightness);
    stSetting.u16Contrast   = LEVEL2NUM(pstSetting->u16Contrast);
    stSetting.u16Hue        = LEVEL2NUM(pstSetting->u16Hue);
    stSetting.u16Saturation = LEVEL2NUM(pstSetting->u16Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPCscSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPCscSetting(HI_DRV_PQ_VP_TYPE_REMOTE, &stSetting);
    }

    /* up drv layer; we use 0~100 level value */
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Brightness = LEVEL2NUM(pstSetting->u16Brightness);
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Contrast   = LEVEL2NUM(pstSetting->u16Contrast);
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Hue        = LEVEL2NUM(pstSetting->u16Hue);
    stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Saturation = LEVEL2NUM(pstSetting->u16Saturation);

    return s32Ret;
}

/* get brightness, contrast, hue, saturation  of SD Video*/
HI_S32 DRV_PQ_GetSDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_PQ_PICTURE_SETTING_S stSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCVideoSetting(HI_PQ_DISPLAY_0, &stSetting);
        if (HI_SUCCESS == s32Ret)
        {
            pstSetting->u16Brightness = NUM2LEVEL(stSetting.u16Brightness);
            pstSetting->u16Contrast   = NUM2LEVEL(stSetting.u16Contrast);
            pstSetting->u16Hue        = NUM2LEVEL(stSetting.u16Hue);
            pstSetting->u16Saturation = NUM2LEVEL(stSetting.u16Saturation);
        }
        else
        {
            HI_ERR_PQ("get csc error\n");
        }
    }

    return s32Ret;
}

/* set brightness, contrast, hue, saturation  of SD Video*/
HI_S32 DRV_PQ_SetSDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_PQ_PICTURE_SETTING_S stSetting;
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Hue, 100);

    pqprint(PQ_PRN_CSC, "Set Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n",
            pstSetting->u16Brightness, pstSetting->u16Contrast, pstSetting->u16Hue, pstSetting->u16Saturation);

    stSetting.u16Brightness = LEVEL2NUM(pstSetting->u16Brightness);
    stSetting.u16Contrast   = LEVEL2NUM(pstSetting->u16Contrast);
    stSetting.u16Hue        = LEVEL2NUM(pstSetting->u16Hue);
    stSetting.u16Saturation = LEVEL2NUM(pstSetting->u16Saturation);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_0, &stSetting);
    }

    stPqParam.stSDVideoSetting.u16Brightness = LEVEL2NUM(pstSetting->u16Brightness);
    stPqParam.stSDVideoSetting.u16Contrast   = LEVEL2NUM(pstSetting->u16Contrast);
    stPqParam.stSDVideoSetting.u16Hue        = LEVEL2NUM(pstSetting->u16Hue);
    stPqParam.stSDVideoSetting.u16Saturation = LEVEL2NUM(pstSetting->u16Saturation);

    return s32Ret;
}


/* get brightness, contrast, hue, saturation  of HD gfx*/
HI_S32 DRV_PQ_GetHDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    pstSetting->u16Brightness  = stPqParam.stHDPictureSetting.u16Brightness;
    pstSetting->u16Contrast    = stPqParam.stHDPictureSetting.u16Contrast;
    pstSetting->u16Hue         = stPqParam.stHDPictureSetting.u16Hue;
    pstSetting->u16Saturation  = stPqParam.stHDPictureSetting.u16Saturation;

    return HI_SUCCESS;
}


/* get brightness, contrast, hue, saturation  of SD gfx*/
HI_S32 DRV_PQ_GetSDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    pstSetting->u16Brightness  = stPqParam.stSDPictureSetting.u16Brightness;
    pstSetting->u16Contrast    = stPqParam.stSDPictureSetting.u16Contrast;
    pstSetting->u16Hue         = stPqParam.stSDPictureSetting.u16Hue;
    pstSetting->u16Saturation  = stPqParam.stSDPictureSetting.u16Saturation;

    return HI_SUCCESS;
}


/* set brightness, contrast, hue, saturation  of HD gfx*/
HI_S32 DRV_PQ_SetHDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Hue, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, pstSetting);
    }

    stPqParam.stHDPictureSetting.u16Brightness = pstSetting->u16Brightness;
    stPqParam.stHDPictureSetting.u16Contrast   = pstSetting->u16Contrast;
    stPqParam.stHDPictureSetting.u16Hue        = pstSetting->u16Hue;
    stPqParam.stHDPictureSetting.u16Saturation = pstSetting->u16Saturation;

    HI_DEBUG_PQ("SetHDPicture Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n", \
                pstSetting->u16Brightness, pstSetting->u16Contrast, pstSetting->u16Hue, pstSetting->u16Saturation);

    return s32Ret;
}

HI_S32 DRV_PQ_GetSRMode(HI_PQ_SR_DEMO_E *penSRMode)
{
    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetSRMode(HI_PQ_SR_DEMO_E enSRMode)
{
    return HI_SUCCESS;
}



HI_S32 DRV_PQ_SetHdrOffsetPara(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrOffsetPara);

    PQ_CHECK_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->enHdrProcessScene, HI_PQ_HDR_MODE_BUTT);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32HdrMode, 1);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32Bright, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32Satu, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32Hue, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32R, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32G, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32B, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32darkCv, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32brightCv, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32ACCdark, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32ACCbrigt, 100);

    pstHdrOffsetPara->u32Bright   = LEVEL2NUM(pstHdrOffsetPara->u32Bright);
    pstHdrOffsetPara->u32Contrast = LEVEL2NUM(pstHdrOffsetPara->u32Contrast);
    pstHdrOffsetPara->u32Satu     = LEVEL2NUM(pstHdrOffsetPara->u32Satu);
    pstHdrOffsetPara->u32Hue      = LEVEL2NUM(pstHdrOffsetPara->u32Hue);

    pstHdrOffsetPara->u32R   = LEVEL2NUM(pstHdrOffsetPara->u32R);
    pstHdrOffsetPara->u32G   = LEVEL2NUM(pstHdrOffsetPara->u32G);
    pstHdrOffsetPara->u32B   = LEVEL2NUM(pstHdrOffsetPara->u32B);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrOffset))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrOffset(pstHdrOffsetPara);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrTMCurve))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrTMCurve(pstHdrOffsetPara);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetGfxHdrOffsetPara(HI_PQ_SETHDROFFSET_S *pstHdrOffsetPara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstHdrOffsetPara);

    PQ_CHECK_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->enHdrProcessScene, HI_PQ_HDR_MODE_BUTT);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32HdrMode, 1);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32Bright, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32Satu, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32Hue, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32R, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32G, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32B, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32darkCv, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32brightCv, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32ACCdark, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstHdrOffsetPara->u32ACCbrigt, 100);

    pstHdrOffsetPara->u32Bright   = LEVEL2NUM(pstHdrOffsetPara->u32Bright);
    pstHdrOffsetPara->u32Contrast = LEVEL2NUM(pstHdrOffsetPara->u32Contrast);
    pstHdrOffsetPara->u32Satu     = LEVEL2NUM(pstHdrOffsetPara->u32Satu);
    pstHdrOffsetPara->u32Hue      = LEVEL2NUM(pstHdrOffsetPara->u32Hue);

    pstHdrOffsetPara->u32R   = LEVEL2NUM(pstHdrOffsetPara->u32R);
    pstHdrOffsetPara->u32G   = LEVEL2NUM(pstHdrOffsetPara->u32G);
    pstHdrOffsetPara->u32B   = LEVEL2NUM(pstHdrOffsetPara->u32B);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXHDR, SetHdrOffset))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXHDR)->SetHdrOffset(pstHdrOffsetPara);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXHDR, SetHdrTMCurve))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXHDR)->SetHdrTMCurve(pstHdrOffsetPara);
    }

    return s32Ret;
}

/* get brightness, contrast, hue, saturation  of SD gfx*/
HI_S32 DRV_PQ_SetSDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstSetting)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstSetting->u16Hue, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, pstSetting);
    }

    stPqParam.stSDPictureSetting.u16Brightness = pstSetting->u16Brightness;
    stPqParam.stSDPictureSetting.u16Contrast   = pstSetting->u16Contrast;
    stPqParam.stSDPictureSetting.u16Hue        = pstSetting->u16Hue;
    stPqParam.stSDPictureSetting.u16Saturation = pstSetting->u16Saturation;

    return s32Ret;
}

HI_S32 DRV_PQ_SetSDTemperature(HI_PQ_COLORTEMPERATURE_S *pstTemperature)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstTemperature);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstTemperature->u32Red, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstTemperature->u32Green, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstTemperature->u32Blue, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetColorTemp))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetColorTemp(pstTemperature);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetSDTemperature(HI_PQ_COLORTEMPERATURE_S *pstTemperature)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstTemperature);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetColorTemp))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetColorTemp(pstTemperature);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetHDTemperature(HI_PQ_COLORTEMPERATURE_S *pstTemperature)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstTemperature);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstTemperature->u32Red, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstTemperature->u32Green, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstTemperature->u32Blue, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetColorTemp))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetColorTemp(pstTemperature);
    }

    return s32Ret;
}


HI_S32 DRV_PQ_GetHDTemperature(HI_PQ_COLORTEMPERATURE_S *pstTemperature)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstTemperature);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetColorTemp))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetColorTemp(pstTemperature);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetSharpness(HI_U32 *pu32Sharpness)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Sharpness);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_SHARPNESS, GetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_SHARPNESS)->GetStrength(pu32Sharpness);
        pqprint(PQ_PRN_SHARPEN, "Get sharpen Level: %d\n", *pu32Sharpness);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetSharpness(HI_U32 u32Sharpness)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Sharpness, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_SHARPNESS, SetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_SHARPNESS)->SetStrength(u32Sharpness);
        stPqParam.u32Strength[HI_PQ_MODULE_SHARPNESS] = u32Sharpness;
        pqprint(PQ_PRN_SHARPEN, "Set sharpen level: %d\n", u32Sharpness);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetColorEhance(HI_U32 *pu32ColorGainLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32ColorGainLevel);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, GetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_COLOR)->GetStrength(pu32ColorGainLevel);
        pqprint(PQ_PRN_ACM, "Get ColorGainLevel: %d\n", *pu32ColorGainLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetColorEhance(HI_U32 u32ColorGainLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32ColorGainLevel, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, SetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_COLOR)->SetStrength(u32ColorGainLevel);
        stPqParam.u32Strength[HI_PQ_MODULE_COLOR] = u32ColorGainLevel;
        pqprint(PQ_PRN_ACM, "Set ColorGainLevel: %d\n", u32ColorGainLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetFleshToneLevel(HI_U32 *pu32FleshToneLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32FleshToneLevel);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, GetFleshToneLevel))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_COLOR)->GetFleshToneLevel(pu32FleshToneLevel);
        pqprint(PQ_PRN_ACM, "Get FleshToneLevel: %d\n", *pu32FleshToneLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetFleshToneLevel(HI_PQ_FLESHTONE_E enFleshToneLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enFleshToneLevel, HI_PQ_FLESHTONE_GAIN_BUTT);

    stPqParam.stColorEnhance.enColorEnhanceType      = HI_PQ_COLOR_ENHANCE_FLESHTONE;
    stPqParam.stColorEnhance.unColorGain.enFleshtone = enFleshToneLevel;

    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, SetFleshToneLevel))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_COLOR)->SetFleshToneLevel(enFleshToneLevel);
        pqprint(PQ_PRN_ACM, "Set FleshToneLevel: %d\n", enFleshToneLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetSixBaseColorLevel(HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColorOffset)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSixBaseColorOffset);

    stPqParam.stColorEnhance.enColorEnhanceType    = HI_PQ_COLOR_ENHANCE_SIX_BASE;
    stPqParam.stColorEnhance.unColorGain.stSixBase = *pstSixBaseColorOffset;

    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, SetSixBaseColorLevel))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_COLOR)->SetSixBaseColorLevel(pstSixBaseColorOffset);
        pqprint(PQ_PRN_ACM, "Set SixBaseColor Red:%d, Green: %d, Blue: %d, Cyan: %d, Magenta: %d, Yellow: %d\n",
                pstSixBaseColorOffset->u32Red, pstSixBaseColorOffset->u32Green,
                pstSixBaseColorOffset->u32Blue, pstSixBaseColorOffset->u32Cyan,
                pstSixBaseColorOffset->u32Magenta, pstSixBaseColorOffset->u32Yellow);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetSixBaseColorLevel(HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColorOffset)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstSixBaseColorOffset);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, GetSixBaseColorLevel))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_COLOR)->GetSixBaseColorLevel(pstSixBaseColorOffset);
        pqprint(PQ_PRN_ACM, "Get SixBaseColor Red:%d, Green: %d, Blue: %d, Cyan: %d, Magenta: %d, Yellow: %d\n",
                pstSixBaseColorOffset->u32Red, pstSixBaseColorOffset->u32Green,
                pstSixBaseColorOffset->u32Blue, pstSixBaseColorOffset->u32Cyan,
                pstSixBaseColorOffset->u32Magenta, pstSixBaseColorOffset->u32Yellow);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetColorEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enColorSpecMode, HI_PQ_COLOR_MODE_BUTT);

    stPqParam.stColorEnhance.enColorEnhanceType      = HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
    stPqParam.stColorEnhance.unColorGain.enColorMode = enColorSpecMode;

    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, SetColorEnhanceMode))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_COLOR)->SetColorEnhanceMode(enColorSpecMode);
        pqprint(PQ_PRN_ACM, "Set ColorEnhanceMode: %d\n", enColorSpecMode);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetColorEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E *penColorSpecMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(penColorSpecMode);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, GetColorEnhanceMode))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_COLOR)->GetColorEnhanceMode(penColorSpecMode);
        pqprint(PQ_PRN_ACM, "Get ColorEnhanceMode: %d\n", *penColorSpecMode);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetDCILevel(HI_U32 u32DCILevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32DCILevel, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, SetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DCI)->SetStrength(u32DCILevel);
        stPqParam.u32Strength[HI_PQ_MODULE_DCI] = u32DCILevel;
        pqprint(PQ_PRN_DCI, "Set DCILevelGain: %d\n", u32DCILevel);
    }

    return s32Ret;
}


HI_S32 DRV_PQ_GetDCILevel(HI_U32 *pu32DCILevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32DCILevel);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, GetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DCI)->GetStrength(pu32DCILevel);
        pqprint(PQ_PRN_DCI, "Get DCI Level: %d\n", *pu32DCILevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetTnrLevel(HI_U32 *pu32TnrLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32TnrLevel);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_TNR, GetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_TNR)->GetStrength(pu32TnrLevel);
        pqprint(PQ_PRN_TNR, "Get TNR Level: %d\n", *pu32TnrLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetTnrLevel(HI_U32 u32TnrLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32TnrLevel, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_TNR, SetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_TNR)->SetStrength(u32TnrLevel);
        stPqParam.u32Strength[HI_PQ_MODULE_TNR] = u32TnrLevel;
        pqprint(PQ_PRN_TNR, "Set TNR Level: %d\n", u32TnrLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetSnrLevel(HI_U32 *pu32SnrLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bVdp4KSnrEn = HI_FALSE;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32SnrLevel);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_SNR, GetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_SNR)->GetStrength(pu32SnrLevel);
        pqprint(PQ_PRN_SNR, "Get SNR Level: %d\n", *pu32SnrLevel);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VDP4KSNR, GetStrength))
    {
        GET_ALG_FUN(HI_PQ_MODULE_VDP4KSNR)->GetEnable(&bVdp4KSnrEn);

        if (HI_TRUE == bVdp4KSnrEn)
        {
            s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VDP4KSNR)->GetStrength(pu32SnrLevel);
            pqprint(PQ_PRN_VDP4KSNR, "Get VDP4KSNR Level: %d\n", *pu32SnrLevel);
        }
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetSnrLevel(HI_U32 u32SnrLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_BOOL bVdp4KSnrEn = HI_FALSE;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32SnrLevel, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_SNR, SetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_SNR)->SetStrength(u32SnrLevel);
        stPqParam.u32Strength[HI_PQ_MODULE_SNR] = u32SnrLevel;
        pqprint(PQ_PRN_SNR, "Set SNR Level: %d\n", u32SnrLevel);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VDP4KSNR, SetStrength))
    {
        GET_ALG_FUN(HI_PQ_MODULE_VDP4KSNR)->GetEnable(&bVdp4KSnrEn);

        if (HI_TRUE == bVdp4KSnrEn)
        {
            s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VDP4KSNR)->SetStrength(u32SnrLevel);
            stPqParam.u32Strength[HI_PQ_MODULE_VDP4KSNR] = u32SnrLevel;
            pqprint(PQ_PRN_VDP4KSNR, "Set VDP4KSNR Level: %d\n", u32SnrLevel);
        }
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetDbLevel(HI_U32 *pu32DbLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32DbLevel);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DB, GetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DB)->GetStrength(pu32DbLevel);
        pqprint(PQ_PRN_DB_READ, "Get DB Level: %d\n", *pu32DbLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetDbLevel(HI_U32 u32DbLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32DbLevel, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DB, SetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DB)->SetStrength(u32DbLevel);
        stPqParam.u32Strength[HI_PQ_MODULE_DB] = u32DbLevel;
        pqprint(PQ_PRN_DB_READ, "Set DB Level: %d\n", u32DbLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetDmLevel(HI_U32 *pu32DmLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32DmLevel);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DM, GetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DM)->GetStrength(pu32DmLevel);
        pqprint(PQ_PRN_DM, "Get DM Level: %d\n", *pu32DmLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetDmLevel(HI_U32 u32DmLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32DmLevel, 100);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DM, SetStrength))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DM)->SetStrength(u32DmLevel);
        stPqParam.u32Strength[HI_PQ_MODULE_DM] = u32DmLevel;
        pqprint(PQ_PRN_DM, "Set DM Level: %d\n", u32DmLevel);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetPQModule(HI_PQ_MODULE_E enModule, HI_U32 *pu32OnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32OnOff);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enModule, HI_PQ_MODULE_BUTT);

    if (HI_PQ_MODULE_ALL == enModule)
    {
        *pu32OnOff = stPqParam.bModuleOnOff[HI_PQ_MODULE_ALL];
        s32Ret = HI_SUCCESS;
    }
    else if (PQ_FUNC_CALL(enModule, GetEnable))
    {
        s32Ret = GET_ALG_FUN(enModule)->GetEnable(pu32OnOff);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetPQModule(HI_PQ_MODULE_E enModule, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enModule, HI_PQ_MODULE_BUTT);

    if (HI_PQ_MODULE_ALL == enModule)
    {
        stPqParam.bModuleOnOff[HI_PQ_MODULE_ALL] = u32OnOff;

        for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
        {
            if (PQ_FUNC_CALL(i, SetEnable))
            {
                s32Ret = GET_ALG_FUN(i)->SetEnable(u32OnOff);
                stPqParam.bModuleOnOff[i] = u32OnOff;
            }
        }
    }
    else if (PQ_FUNC_CALL(enModule, SetEnable))
    {
        s32Ret = GET_ALG_FUN(enModule)->SetEnable(u32OnOff);
        stPqParam.bModuleOnOff[enModule] = u32OnOff;
    }

    return s32Ret;
}


/* Vpss CSC Port must Every frame  */
HI_S32 drv_pq_GetVpssCscCoef(HI_U32 u32HandleNo, HI_DRV_PQ_VP_MODE_E enDrvPqVPImageMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enDrvPqVPImageMode, HI_DRV_PQ_VIDEOPHONE_MODE_BUTT);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, UpdateVpssCsc))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->UpdateVpssCsc(u32HandleNo, enDrvPqVPImageMode);
    }

    return s32Ret;
}

/* Vpss CSC Port must Every frame  */
HI_S32 drv_pq_GetVpssGammaCoef(HI_U32 u32HandleNo, HI_DRV_PQ_VP_MODE_E enDrvPqVPImageMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enDrvPqVPImageMode, HI_DRV_PQ_VIDEOPHONE_MODE_BUTT);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSGAMMA, UpdateVpssGammaCoef))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_VPSSGAMMA)->UpdateVpssGammaCoef(u32HandleNo, enDrvPqVPImageMode);
    }

    return s32Ret;
}


HI_S32 DRV_PQ_SetDemoMode(HI_PQ_MODULE_E enModule, HI_BOOL bOnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enModule, HI_PQ_MODULE_BUTT);

    if (HI_PQ_MODULE_ALL == enModule)
    {
        stPqParam.bDemoOnOff[HI_PQ_MODULE_ALL] = bOnOff;

        for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
        {
            if (PQ_FUNC_CALL(i, SetDemo))
            {
                s32Ret = GET_ALG_FUN(i)->SetDemo(bOnOff);
                stPqParam.bDemoOnOff[i] = bOnOff;
            }
        }
    }
    else if (PQ_FUNC_CALL(enModule, SetDemo))
    {
        s32Ret = GET_ALG_FUN(enModule)->SetDemo(bOnOff);
        stPqParam.bDemoOnOff[enModule] = bOnOff;
    }

    return s32Ret;
}

/* set demo display mode */
HI_S32 DRV_PQ_SetDemoDispMode(PQ_REG_TYPE_E enType, HI_PQ_DEMO_MODE_E enDemoMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i = 0;
    PQ_DEMO_MODE_E enSetMode = PQ_DEMO_ENABLE_L;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enType, REG_TYPE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enDemoMode, HI_PQ_DEMO_MODE_BUTT);

    if ((HI_PQ_DEMO_MODE_FIXED_R == enDemoMode) || (HI_PQ_DEMO_MODE_SCROLL_R == enDemoMode))
    {
        enSetMode = PQ_DEMO_ENABLE_R;
    }
    else if ((HI_PQ_DEMO_MODE_FIXED_L == enDemoMode) || (HI_PQ_DEMO_MODE_SCROLL_L == enDemoMode))
    {
        enSetMode = PQ_DEMO_ENABLE_L;
    }

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        if (PQ_FUNC_CALL(i, SetDemoMode))
        {
            if (enType != PQ_COMM_GetAlgTypeID(i))
            {
                continue;
            }

            s32Ret = GET_ALG_FUN(i)->SetDemoMode(enSetMode);
        }
    }

    stPqParam.enDemoMode = enDemoMode;
    return s32Ret;
}

HI_S32 DRV_PQ_GetDemoDispMode(HI_PQ_DEMO_MODE_E *penDemoMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(penDemoMode);

    *penDemoMode = stPqParam.enDemoMode;

    return HI_SUCCESS;
}

static HI_VOID DRV_PQ_RefreshMktCoordinate(PQ_REG_TYPE_E enType)
{
    /* DEMO */
    HI_U32 i = 0;
    HI_U32 u32Step = 1;
    static HI_U32 s_u32Pos = 0;

    PQ_CHECK_OVER_RANGE_RE_NULL(enType, REG_TYPE_BUTT);

    if ((HI_PQ_DEMO_MODE_FIXED_R == stPqParam.enDemoMode) || (HI_PQ_DEMO_MODE_FIXED_L == stPqParam.enDemoMode))
    {
        DRV_PQ_SetDemoCoordinate(enType, sg_u32DemoCoordinate);
        return;
    }

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        if (HI_NULL == PQ_FUNC_CALL(i, SetDemoModeCoor))
        {
            continue;
        }

        if (enType != PQ_COMM_GetAlgTypeID(i))
        {
            continue;
        }

        /* set demo display mode*/
        if ((HI_PQ_DEMO_MODE_SCROLL_R == stPqParam.enDemoMode) || (HI_PQ_DEMO_MODE_SCROLL_L == stPqParam.enDemoMode))
        {
            if (0 == g_u32ImageWidth)
            {
                return;
            }

            if (REG_TYPE_VPSS == enType)
            {
                GET_ALG_FUN(i)->SetDemoModeCoor(s_u32Pos);
            }
            else if (REG_TYPE_VDP == enType)
            {
                GET_ALG_FUN(i)->SetDemoModeCoor(s_u32Pos * g_u32OutWidth / g_u32ImageWidth);
            }
        }
    }

    s_u32Pos = s_u32Pos + u32Step;
    if (g_u32ImageWidth < s_u32Pos)
    {
        s_u32Pos = 0;
    }

    return;
}

HI_S32 DRV_PQ_SetDemoCoordinate(PQ_REG_TYPE_E enType, HI_U32 u32X)
{
    HI_U32 i;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enType, REG_TYPE_BUTT);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32X, 100);

    sg_u32DemoCoordinate = u32X;

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        if (HI_NULL == PQ_FUNC_CALL(i, SetDemoModeCoor))
        {
            continue;
        }

        if (enType != PQ_COMM_GetAlgTypeID(i))
        {
            continue;
        }

        /* set demo display mode*/
        if (REG_TYPE_VPSS == enType)
        {
            GET_ALG_FUN(i)->SetDemoModeCoor(g_u32ImageWidth * u32X / 100);
        }
        else if (REG_TYPE_VDP == enType)
        {
            GET_ALG_FUN(i)->SetDemoModeCoor(g_u32OutWidth * u32X / 100);
        }
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetDemoCoordinate(HI_U32 *pu32X)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32X);

    *pu32X = sg_u32DemoCoordinate;

    return HI_SUCCESS;
}

static HI_VOID DRV_PQ_RefreshVdpCfg(HI_VOID)
{
    DRV_PQ_RefreshMktCoordinate(REG_TYPE_VDP);

    PQ_TABLE_InitSoftTable(HI_FALSE);

    return;
}

static HI_S32 drv_pq_SetModuleEn(HI_PQ_MODULE_E enMode, HI_BOOL bModuleOnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enMode, HI_PQ_MODULE_BUTT);

    if (HI_NULL == PQ_FUNC_CALL(enMode, SetEnable))
    {
        return s32Ret;
    }

    s32Ret = GET_ALG_FUN(enMode)->SetEnable(bModuleOnOff);

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Alg ID:%d, SetEnable error!\n", enMode);
    }

    return s32Ret;
}

static HI_S32 DRV_PQ_ResetPqStatusParam(PQ_REG_TYPE_E enType)
{
    HI_S32  s32Ret = HI_SUCCESS;
    HI_U32  i = 0;
    HI_BOOL bModuleOn = HI_FALSE;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enType, REG_TYPE_BUTT);

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        if (HI_NULL == GET_ALG(i))
        {
            continue;
        }

        if (enType != PQ_COMM_GetAlgTypeID(i))
        {
            continue;
        }

        if (GET_ALG_FUN(i)->SetEnable)
        {
            bModuleOn = (HI_TRUE == sg_bDefaultParam) ? HI_FALSE : stPqParam.bModuleOnOff[i];

            s32Ret = GET_ALG_FUN(i)->SetEnable(bModuleOn);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_PQ("Alg ID:%d, SetEnable error!\n", i);
            }
        }

        if (GET_ALG_FUN(i)->SetDemo)
        {
            s32Ret = GET_ALG_FUN(i)->SetDemo(stPqParam.bDemoOnOff[i]);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_PQ("Alg ID:%d, SetDemo error!\n", i);
            }
        }

        if (GET_ALG_FUN(i)->SetStrength)
        {
            s32Ret = GET_ALG_FUN(i)->SetStrength(stPqParam.u32Strength[i]);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_PQ("Alg ID:%d, SetStrength error!\n", i);
            }
        }
    }

    return s32Ret;
}

static HI_S32 drv_pq_SetSceneMode(HI_PQ_VPSS_MODULE_S *pstPQModule)
{
    PQ_STATUS_S stPqStatus = {0};

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPQModule);

    PQ_COMM_GetPqStatus(&stPqStatus);

    if (PQ_IMAGE_MODE_NORMAL == stPqStatus.enImageMode)
    {
        PQ_COMM_SetOutputMode(PQ_OUTPUT_MODE_NO);
        return HI_SUCCESS;
    }

    if (HI_PQ_SCENE_MODE_PREVIEW == pstPQModule->enSceneMode)
    {
        PQ_COMM_SetOutputMode(OUTPUT_MODE_PREVIEW);
    }
    else if (HI_PQ_SCENE_MODE_REMOTE == pstPQModule->enSceneMode)
    {
        PQ_COMM_SetOutputMode(OUTPUT_MODE_REMOTE);
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetVPPreviewMode(HI_DRV_PQ_VP_MODE_E enVPSceneMode)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(enVPSceneMode, HI_DRV_PQ_VIDEOPHONE_MODE_BUTT);

    sg_enVPMode[HI_DRV_PQ_VP_TYPE_PREVIEW] = enVPSceneMode ;

    return HI_SUCCESS;
}

/* Get VP Preview Mode */
HI_S32 DRV_PQ_GetVPPreviewMode(HI_DRV_PQ_VP_MODE_E *penVPSceneMode)
{
    HI_DRV_PQ_VP_MODE_E enVPSceneMode;
    PQ_CHECK_NULL_PTR_RE_FAIL(penVPSceneMode);

    enVPSceneMode = sg_enVPMode[HI_DRV_PQ_VP_TYPE_PREVIEW];

    *penVPSceneMode = enVPSceneMode;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetVPRemoteMode(HI_DRV_PQ_VP_MODE_E enVPSceneMode)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(enVPSceneMode, HI_DRV_PQ_VIDEOPHONE_MODE_BUTT);

    sg_enVPMode[HI_DRV_PQ_VP_TYPE_REMOTE] = enVPSceneMode ;

    return HI_SUCCESS;
}

/* Get VP Remote Mode */
HI_S32 DRV_PQ_GetVPRemoteMode(HI_DRV_PQ_VP_MODE_E *penVPSceneMode)
{
    HI_DRV_PQ_VP_MODE_E enVPSceneMode;
    PQ_CHECK_NULL_PTR_RE_FAIL(penVPSceneMode);

    enVPSceneMode = sg_enVPMode[HI_DRV_PQ_VP_TYPE_REMOTE];

    *penVPSceneMode = enVPSceneMode;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetImageMode(HI_PQ_IMAGE_MODE_E enImageMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PQ_STATUS_S stPqStatus;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enImageMode, HI_PQ_IMAGE_MODE_BUTT);

    PQ_COMM_GetPqStatus(&stPqStatus);
    stPqStatus.enImageMode = (PQ_COMM_IMAGE_MODE_E)enImageMode;

    s32Ret = PQ_COMM_SetPqStatus(&stPqStatus);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_COMM_SetPqStatus Failed \n");
        return HI_FAILURE;
    }

    DRV_PQ_SetSharpness(stPqParam.u32Strength[HI_PQ_MODULE_SHARPNESS]);
    drv_pq_SetModuleEn(HI_PQ_MODULE_DCI, stPqParam.bModuleOnOff[HI_PQ_MODULE_DCI]);

    return s32Ret;
}

HI_S32 DRV_PQ_GetImageMode(HI_PQ_IMAGE_MODE_E *penImageMode)
{
    PQ_STATUS_S stPqStatus = {0};

    PQ_CHECK_NULL_PTR_RE_FAIL(penImageMode);

    PQ_COMM_GetPqStatus(&stPqStatus);
    *penImageMode = (HI_PQ_IMAGE_MODE_E)stPqStatus.enImageMode;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetMcdiSplitMode(HI_U32 u32SplitMode)
{
    HI_U32 u32HandleNo = 0;
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32SplitMode, 5);

    if ((2 == u32SplitMode) || (3 == u32SplitMode) || (4 == u32SplitMode))
    {
        HI_ERR_PQ("DRV_PQ_SetMcdiSplitMode set splitmode num error !\n");
    }

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        sg_enMcdiSplitMode[u32HandleNo] = (HI_DRV_PQ_MCDI_SPLIT_MODE_E)u32SplitMode ;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetMcdiSplitMode(HI_U32 u32HandleNo, HI_DRV_PQ_MCDI_SPLIT_MODE_E *penSplitMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM - 1);
    PQ_CHECK_NULL_PTR_RE_FAIL(penSplitMode);

#if defined(PQ_YDJC_MCDI_SPLIT_DEFAULT)
    *penSplitMode = HI_DRV_PQ_MCDI_SPLIT_MODE_5;
#else
    *penSplitMode = sg_enMcdiSplitMode[u32HandleNo];
#endif

    return s32Ret;
}

HI_S32 DRV_PQ_UpdateVpssPQ(HI_U32 u32HandleNo, HI_VPSS_PQ_INFO_S *pstTimingInfo, PQ_VPSS_CFG_REG_S *pstVPSSReg, PQ_VPSS_WBC_REG_S *pstWbcReg, HI_PQ_VPSS_MODULE_S *pstPQModule)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PQ_SOURCE_MODE_E enSourceMode = PQ_SOURCE_MODE_HD;
    PQ_OUTPUT_MODE_E enOutputMode = PQ_OUTPUT_MODE_HD;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);

    PQ_HAL_UpdateVpssReg(u32HandleNo, pstVPSSReg, pstWbcReg);

    /* VPSS Deinit send Null to clear reg para */
    if ((pstVPSSReg == HI_NULL) || ( pstTimingInfo == HI_NULL))
    {
        return HI_SUCCESS;
    }

    pqprint(PQ_PRN_VPSS, "[%s]: HandleNo:%d, Width:%d, Height:%d, FrameRate:%d, Interlace:%d\n",
            __FUNCTION__, u32HandleNo, pstTimingInfo->u32Width, pstTimingInfo->u32Height,
            pstTimingInfo->u32FrameRate, pstTimingInfo->bInterlace);

    g_u32ImageWidth  = pstTimingInfo->u32Width;
    g_u32ImageHeight = pstTimingInfo->u32Height;

    if (pstTimingInfo->u32Width == 0 || pstTimingInfo->u32Height == 0)
    {
        HI_ERR_PQ("VPSS Timing W | H is Zero !\n");
        return HI_SUCCESS;
    }

    enSourceMode  = PQ_COMM_CheckSourceMode(pstTimingInfo->u32Width);
    PQ_COMM_SetSourceMode(enSourceMode);

    drv_pq_SetSceneMode(pstPQModule);
    enOutputMode = PQ_COMM_GetOutputMode();
    /* Load VPSS Physical Register */
    s32Ret = PQ_TABLE_LoadPhyList(REG_TYPE_VPSS, enSourceMode, enOutputMode, u32HandleNo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_TABLE_LoadPhyList VPSS failed!\n");
        return s32Ret;
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_TNR, SetTNRBlendingAlphaLut))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_TNR)->SetTNRBlendingAlphaLut(u32HandleNo);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("TNRLut CfgRefresh failed!\n");
            return s32Ret;
        }
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DS, SetDeShootThr))
    {
        sg_ulProcAlgStartTime[u32HandleNo][HI_PQ_MODULE_DS] = PQ_GetTimeUs();
        /* Refresh DS API CFG */
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DS)->SetDeShootThr(u32HandleNo, pstTimingInfo->u32Width);
        if (HI_SUCCESS != s32Ret)
        {
            sg_ulProcAlgEndTime[u32HandleNo][HI_PQ_MODULE_DS] = PQ_GetTimeUs();
            HI_ERR_PQ("DS CfgRefresh failed!\n");
            return s32Ret;
        }
        sg_ulProcAlgEndTime[u32HandleNo][HI_PQ_MODULE_DS] = PQ_GetTimeUs();
    }

    /* Ifmd Para cfg Init again; consumer problem: when scene change, the convergence time of field mode detection too long, need init again */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_FMD, SofeParaInitByHandle))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_FMD)->SofeParaInitByHandle(u32HandleNo);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("SofeParaInitByHandle failed!\n");
            return s32Ret;
        }
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DB, DBCfgRefresh))
    {
        /* Refresh DB API CFG */
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DB)->DBCfgRefresh(u32HandleNo, pstTimingInfo->u32Height, pstTimingInfo->u32Width, pstTimingInfo->u32FrameRate);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("DB DBCfgRefresh failed!\n");
            return s32Ret;
        }

        if (PQ_FUNC_CALL(HI_PQ_MODULE_DM, DMCfgRefresh))
        {
            /* Refresh DM API CFG */
            s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DM)->DMCfgRefresh(u32HandleNo, pstTimingInfo->u32Height, pstTimingInfo->u32Width, pstTimingInfo->u32FrameRate);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_PQ("DM DMCfgRefresh failed!\n");
                return s32Ret;
            }
        }
    }

    /* reset vpss customer pq setting */
    s32Ret = DRV_PQ_ResetPqStatusParam(REG_TYPE_VPSS);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("ResetPqStatusParam VPSS failed!\n");
    }

    /* set demo mode*/
    DRV_PQ_SetDemoDispMode(REG_TYPE_VPSS, stPqParam.enDemoMode);
    DRV_PQ_SetDemoCoordinate(REG_TYPE_VPSS, sg_u32DemoCoordinate);

    return s32Ret;
}

static HI_S32 drv_pq_UpdatePartlyVdpPQ(PQ_SOURCE_MODE_E enSourceMode, PQ_OUTPUT_MODE_E enOutputMode)
{
    HI_S32  s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enSourceMode, PQ_SOURCE_MODE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enOutputMode, PQ_OUTPUT_MODE_BUTT);

    s32Ret = PQ_TABLE_LoadMultiList(REG_TYPE_VDP, enSourceMode, enOutputMode);

    return s32Ret;
}

static HI_S32 drv_pq_UpdatefullVdpPQ(PQ_SOURCE_MODE_E enSourceMode, PQ_OUTPUT_MODE_E enOutputMode)
{
    HI_S32  s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enSourceMode, PQ_SOURCE_MODE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enOutputMode, PQ_OUTPUT_MODE_BUTT);

    s32Ret = PQ_TABLE_LoadPhyList(REG_TYPE_VDP, enSourceMode, enOutputMode, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_TABLE_LoadPhyList VDP failed!\n");
        return s32Ret;
    }

    /*Set Picture Setting*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_0, (HI_PQ_PICTURE_SETTING_S *)&stPqParam.stSDVideoSetting);
        GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_1, (HI_PQ_PICTURE_SETTING_S *)&stPqParam.stHDVideoSetting);
    }

    /* Set Color Enhance */
    if (HI_PQ_COLOR_ENHANCE_FLESHTONE == stPqParam.stColorEnhance.enColorEnhanceType)
    {
        DRV_PQ_SetFleshToneLevel(stPqParam.stColorEnhance.unColorGain.enFleshtone);
    }
    else if (HI_PQ_COLOR_ENHANCE_SIX_BASE == stPqParam.stColorEnhance.enColorEnhanceType)
    {
        HI_PQ_SIX_BASE_COLOR_S *pstPQSixBase = &(stPqParam.stColorEnhance.unColorGain.stSixBase);
        DRV_PQ_SetSixBaseColorLevel(pstPQSixBase);
    }
    else if (HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE == stPqParam.stColorEnhance.enColorEnhanceType)
    {
        DRV_PQ_SetColorEnhanceMode(stPqParam.stColorEnhance.unColorGain.enColorMode);
    }

    /* Update Coef */
    if ((PQ_FUNC_CALL(HI_PQ_MODULE_DCI, SetResume)) && (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, UpdatDCICoef)))
    {
        if (GET_ALG_FUN(HI_PQ_MODULE_DCI)->SetResume)
        {
            GET_ALG_FUN(HI_PQ_MODULE_DCI)->SetResume(!g_bLoadPqBin);
        }

        if (GET_ALG_FUN(HI_PQ_MODULE_DCI)->UpdatDCICoef)
        {
            GET_ALG_FUN(HI_PQ_MODULE_DCI)->UpdatDCICoef(PQ_VDP_LAYER_VID0);
        }
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, UpdatACMCoef))
    {
        GET_ALG_FUN(HI_PQ_MODULE_COLOR)->UpdatACMCoef(PQ_VDP_LAYER_VP0);
    }

    return s32Ret;
}


HI_S32 DRV_PQ_UpdateVdpPQ(HI_PQ_DISPLAY_E enDisplayId, HI_VDP_PQ_INFO_S *pstTimingInfo, S_VDP_REGS_TYPE *pstVDPReg)
{
    HI_S32      s32Ret;
    HI_BOOL     bTimingChange = HI_FALSE;
    HI_PQ_DCI_WIN_S stDciWin;
    PQ_SOURCE_MODE_E enSourceMode = PQ_SOURCE_MODE_HD;
    PQ_OUTPUT_MODE_E enOutputMode = PQ_OUTPUT_MODE_HD;
    static HI_VDP_PQ_INFO_S stTimingInfo[HI_PQ_DISPLAY_BUTT] = {{0}};

    PQ_CHECK_OVER_RANGE_RE_FAIL(enDisplayId, HI_PQ_DISPLAY_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVDPReg);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTimingInfo);

    if ((pstTimingInfo != HI_NULL) && (PQ_VDP_LAYER_VID1 == pstTimingInfo->enLayerId))
    {
        return HI_SUCCESS;
    }

    if (pstTimingInfo->u32Width == 0 || pstTimingInfo->u32Height == 0)
    {
        HI_ERR_PQ("VDP Timing W | H is Zero !\n");
        return HI_SUCCESS;
    }

    /* Update VDP Register point */
    PQ_HAL_UpdateVdpReg(pstVDPReg);
    /* Update VDP confignure every interrupt */
    DRV_PQ_RefreshVdpCfg();

    /*DCI scene change software alg*/
    if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, CalDCIScd))
    {
        GET_ALG_FUN(HI_PQ_MODULE_DCI)->CalDCIScd();
    }

    pqprint(PQ_PRN_VDP, "[%s]: DisplayId:%d, enLayerId:%d, Width:%d, Height:%d, OutWidth:%d, OutHeight:%d, bSRState:%d, b3dType:%d\n",
            __FUNCTION__, enDisplayId, pstTimingInfo->enLayerId, pstTimingInfo->u32Width, pstTimingInfo->u32Height,
            pstTimingInfo->stVideo.s32Width, pstTimingInfo->stVideo.s32Height, pstTimingInfo->bSRState, pstTimingInfo->b3dType);
    pqprint(PQ_PRN_VDP, "bProgressive:%d, Width:%d, Height:%d,  s32X:%d, s32Y:%d, u32RefreshRate:%d\n",
            pstTimingInfo->stChannelTiming[enDisplayId].bProgressive, pstTimingInfo->stChannelTiming[enDisplayId].stFmtRect.s32Width,
            pstTimingInfo->stChannelTiming[enDisplayId].stFmtRect.s32Height, pstTimingInfo->stChannelTiming[enDisplayId].stFmtRect.s32X,
            pstTimingInfo->stChannelTiming[enDisplayId].stFmtRect.s32Y,
            pstTimingInfo->stChannelTiming[enDisplayId].u32RefreshRate);

    bTimingChange  =  (stTimingInfo[enDisplayId].u32Width != pstTimingInfo->u32Width)
                      || (stTimingInfo[enDisplayId].u32Height != pstTimingInfo->u32Height)
                      || (stTimingInfo[enDisplayId].stVideo.s32Width != pstTimingInfo->stVideo.s32Width)
                      || (stTimingInfo[enDisplayId].stVideo.s32Height != pstTimingInfo->stVideo.s32Height)
                      || (stTimingInfo[enDisplayId].bSRState != pstTimingInfo->bSRState)
                      || (stTimingInfo[enDisplayId].b3dType != pstTimingInfo->b3dType)
                      || (stTimingInfo[enDisplayId].bHdrMode != pstTimingInfo->bHdrMode)
                      || (0 != memcmp((HI_VOID *)&g_stPqStatus.stTimingInfo[enDisplayId], &pstTimingInfo->stChannelTiming[enDisplayId], sizeof(HI_VDP_CHANNEL_TIMING_S)));

    if ((HI_TRUE == pstTimingInfo->bPartUpdate) && (HI_FALSE == bTimingChange))
    {
        return HI_SUCCESS;
    }

    memcpy(&stTimingInfo[enDisplayId], pstTimingInfo, sizeof(HI_VDP_PQ_INFO_S));
    memcpy(&(g_stPqStatus.stTimingInfo[enDisplayId]), &(pstTimingInfo->stChannelTiming[enDisplayId]), sizeof(HI_VDP_CHANNEL_TIMING_S));

    /*ignored sd*/
    if (HI_PQ_DISPLAY_0 == enDisplayId)
    {
        return HI_SUCCESS;
    }

    g_stPqStatus.bIsogenyMode = pstTimingInfo->bIsogenyMode;
    g_stPqStatus.b3dType      = pstTimingInfo->b3dType;
    g_u32ImageWidth  = pstTimingInfo->u32Width;
    g_u32ImageHeight = pstTimingInfo->u32Height;
    enSourceMode     = PQ_COMM_CheckSourceMode(pstTimingInfo->u32Width);
    PQ_COMM_SetSourceMode(enSourceMode);
    enOutputMode = PQ_COMM_GetOutputMode();
    if ((OUTPUT_MODE_PREVIEW != enOutputMode) && (OUTPUT_MODE_REMOTE != enOutputMode))
    {
        enOutputMode     = PQ_COMM_CheckOutputMode(pstTimingInfo->stChannelTiming[enDisplayId].stFmtRect.s32Width);
        PQ_COMM_SetOutputMode(enOutputMode);
    }

    if ((HI_PQ_DISPLAY_1 == enDisplayId) && (PQ_VDP_LAYER_VID0 ==  pstTimingInfo->enLayerId))
    {
        g_u32OutWidth   = pstTimingInfo->stVideo.s32Width;
        g_u32OutHeight  = pstTimingInfo->stVideo.s32Height;

        stDciWin.u16HStar = 0;
        stDciWin.u16HEnd  = g_u32OutWidth;
        stDciWin.u16VStar = 0;
        stDciWin.u16VEnd  = g_u32OutHeight;

        DRV_PQ_UpdateDCIWin(&stDciWin, HI_TRUE);
    }

    /* Load VDP Physical Register */
    if (HI_TRUE == pstTimingInfo->bPartUpdate)
    {
        /*Set Partly update*/
        drv_pq_UpdatePartlyVdpPQ(enSourceMode, enOutputMode);
    }
    else
    {
        /*Set FULL update*/
        s32Ret = drv_pq_UpdatefullVdpPQ(enSourceMode, enOutputMode);

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("UpdatefullVdpPQ VDP failed!\n");
            return s32Ret;
        }
    }

    /* set isogeny mode */

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetIsogenyMode))
    {
        GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetIsogenyMode(pstTimingInfo->bIsogenyMode);
    }

    /*************************************************************************
     *   reset VDP customer pq setting
     *************************************************************************/

    s32Ret = DRV_PQ_ResetPqStatusParam(REG_TYPE_VDP);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("ResetPqStatusParam VDP failed!\n");
    }

    if (HI_TRUE == pstTimingInfo->bHdrMode)
    {
        stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS] = HI_FALSE;
        drv_pq_SetModuleEn(HI_PQ_MODULE_SHARPNESS, stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS]);
    }

    /* set demo mode*/
    DRV_PQ_SetDemoDispMode(REG_TYPE_VDP, stPqParam.enDemoMode);
    DRV_PQ_SetDemoCoordinate(REG_TYPE_VDP, sg_u32DemoCoordinate);

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_UpdateVdpCSC(HI_PQ_CSC_TYPE_E enCscTypeId, HI_PQ_VDP_CSC_S *pstCscMode)
{
    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetACCHistGram(HI_PQ_ACC_HISTGRAM_S *pstACCHistGram)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstACCHistGram);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, GetACCHistGram))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DCI)->GetACCHistGram(pstACCHistGram);
    }
    return s32Ret;
}

HI_S32 DRV_PQ_UpdateACCHistGram(HI_PQ_ACC_HISTGRAM_S *pstACCHistGram)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ACCOutWidth  = 3840;
    HI_U32 u32ACCOutHeight = 2160;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstACCHistGram);

    u32ACCOutWidth  = g_u32OutWidth;
    u32ACCOutHeight = g_u32OutHeight;

    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrACCHistGram))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrACCHistGram(u32ACCOutWidth, u32ACCOutHeight, pstACCHistGram);
        pqprint(PQ_PRN_DCI, "[%s]: Intf width : %d, Hight : %d -- 0 :%d, %d, %d,--1 : %d, %d, %d, %d, %d, %d, %d, %d\n",
                __FUNCTION__,
                u32ACCOutWidth, u32ACCOutHeight,
                pstACCHistGram->u32HistGram0[0], pstACCHistGram->u32HistGram0[1], pstACCHistGram->u32HistGram0[2],
                pstACCHistGram->u32HistGram1[0], pstACCHistGram->u32HistGram1[1],
                pstACCHistGram->u32HistGram1[2], pstACCHistGram->u32HistGram1[3],
                pstACCHistGram->u32HistGram1[4], pstACCHistGram->u32HistGram1[5],
                pstACCHistGram->u32HistGram1[6], pstACCHistGram->u32HistGram1[7]);
    }
    return s32Ret;
}

HI_S32 DRV_PQ_UpdateDCIWin(HI_PQ_DCI_WIN_S *pstWin, HI_BOOL bDciEnable)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstWin);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, UpdateDCIWin))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DCI)->UpdateDCIWin(pstWin);
        pqprint(PQ_PRN_DCI, "[%s]: HStar:%d, HEnd: %d, VStar: %d, VEnd:%d, bDciEnable:%d\n",
                __FUNCTION__, pstWin->u16HStar, pstWin->u16HEnd, pstWin->u16VStar,
                pstWin->u16VEnd, bDciEnable);
    }

    return s32Ret;
}

/* Vedio CSC Port must Every frame  */
HI_S32 DRV_PQ_GetCSCCoef(HI_PQ_CSC_CRTL_S *pstCscCtrl, HI_PQ_CSC_MODE_E enCscMode, HI_PQ_CSC_COEF_S *pstCscCoef, HI_PQ_CSC_DCCOEF_S *pstCscDcCoef)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstCscCtrl);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enCscMode, HI_PQ_CSC_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstCscCoef);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstCscDcCoef);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, GetCSCCoef))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCCoef(pstCscCtrl, enCscMode, pstCscCoef, pstCscDcCoef);
    }

    return s32Ret;
}

/* Gfx CSC Port must Every frame  */
HI_S32 DRV_PQ_SetGfxCscCoef(HI_PQ_GFX_LAYER_E enGfxCscLayer, HI_PQ_GFX_CSC_PARA_S *pstGfxCscPara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enGfxCscLayer, PQ_GFX_LAYER_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstGfxCscPara);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCscCoef))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCscCoef(enGfxCscLayer, pstGfxCscPara);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_Get8BitCSCCoef(HI_PQ_CSC_MODE_E  enCSCMode, HI_PQ_CSC_COEF_S *pstCSCCoef, HI_PQ_CSC_DCCOEF_S *pstCSCDCCoef)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enCSCMode, HI_PQ_CSC_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstCSCCoef);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstCSCDCCoef);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, Get8BitCSCCoef))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_CSC)->Get8BitCSCCoef(enCSCMode, pstCSCCoef, pstCSCDCCoef);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetZme(HI_PQ_ZME_LAYER_E enLayerId, HI_PQ_ZME_PARA_IN_S *pstZmeDrvPara, HI_BOOL  bFirEnable)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enLayerId, HI_PQ_DISP_LAYER_ZME_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmeDrvPara);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_ZME, SetVdpZme))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetVdpZme(enLayerId, pstZmeDrvPara, bFirEnable);
    }

    return s32Ret;
}

HI_S32 drv_pq_SwitchSceneMode(HI_PQ_SCENEMODE_E enSceneMode, HI_DRV_PQ_VP_TYPE_E *pEnDrvPqVPType)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(enSceneMode, HI_PQ_SCENE_MODE_BUTT);

    switch (enSceneMode)
    {
        case HI_PQ_SCENE_MODE_NORMAL:
        {
            *pEnDrvPqVPType = HI_DRV_PQ_VP_TYPE_NORMAL;;
        }
        break;
        case HI_PQ_SCENE_MODE_PREVIEW:
        {
            *pEnDrvPqVPType = HI_DRV_PQ_VP_TYPE_PREVIEW;
        }
        break;
        case HI_PQ_SCENE_MODE_REMOTE:
        {
            *pEnDrvPqVPType = HI_DRV_PQ_VP_TYPE_REMOTE;;
        }
        break;
        default:
        {
            *pEnDrvPqVPType = HI_DRV_PQ_VP_TYPE_NORMAL;
        }
        break;
    }

    return HI_SUCCESS;
}


HI_S32 DRV_PQ_SetVpssZme(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_ZME_PARA_IN_S *pstZmePara, HI_BOOL  bFirEnable)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_DRV_PQ_VP_TYPE_E enDrvPqVPType = HI_DRV_PQ_VP_TYPE_BUTT;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enLayerId, HI_PQ_VPSS_LAYER_ZME_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstReg);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmePara);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_ZME, SetVpssZme))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetVpssZme(enLayerId, pstReg, pstZmePara, bFirEnable);
    }

    /* switch vp type from vpss to pq type*/
    drv_pq_SwitchSceneMode(pstZmePara->enSceneMode, &enDrvPqVPType);

    /* vpss zme contain videophone scene mode,add for videophone */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSCSC, SetVPType))
    {
        GET_ALG_FUN(HI_PQ_MODULE_VPSSCSC)->SetVPType(enDrvPqVPType);
    }

    /* vpss zme contain videophone scene mode,add for videophone */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_VPSSGAMMA, SetVPType))
    {
        GET_ALG_FUN(HI_PQ_MODULE_VPSSGAMMA)->SetVPType(enDrvPqVPType);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_SetVpssLCHDR(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enLayerId, HI_PQ_VPSS_LAYER_ZME_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstReg);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstXdrFrameInfo);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_LCHDR, GetLCHdrCfg))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_LCHDR)->GetLCHdrCfg(enLayerId, pstReg, pstXdrFrameInfo);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetVdpZmeCoef(HI_PQ_ZME_COEF_RATIO_E enCoefRatio, HI_PQ_ZME_COEF_TYPE_E enCoefType, HI_PQ_ZME_TAP_E enZmeTap, HI_S16 *ps16Coef)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enCoefRatio, HI_PQ_ZME_COEF_RATIO_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enCoefType, HI_PQ_ZME_COEF_TYPE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enZmeTap, HI_PQ_ZME_TAP_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(ps16Coef);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_ZME, GetZmeCoef))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetZmeCoef(enCoefRatio, enCoefType, enZmeTap, ps16Coef);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetVdpZmeStrategy (HI_PQ_ZME_LAYER_E enLayerId, HI_PQ_ZME_STRATEGY_IN_U *pstZmeIn, HI_PQ_ZME_STRATEGY_OUT_U *pstZmeOut)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enLayerId, HI_PQ_DISP_LAYER_ZME_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmeIn);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmeOut);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_ZME, GetVdpZmeStrategy))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetVdpZmeStrategy(enLayerId, pstZmeIn, pstZmeOut);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetWbcInfo(HI_PQ_WBC_INFO_S *pstVpssWbcInfo)
{
    HI_S32 s32Ret                   = HI_SUCCESS;
    HI_BOOL bMCDIMode               = HI_TRUE;
    static HI_BOOL s_bPreMCDIMode   = HI_TRUE;

    HI_UNUSED(s32Ret);
    HI_UNUSED(bMCDIMode);
    HI_UNUSED(s_bPreMCDIMode);

    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssWbcInfo);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstVpssWbcInfo->u32HandleNo, VPSS_HANDLE_NUM);

#if (defined(TNR_NOTEE_SUPPORT) || defined(TNR_TEE_SUPPORT))
    if (PQ_FUNC_CALL(HI_PQ_MODULE_TNR, UpdateMCNRCfg))
    {
        sg_ulProcAlgStartTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_TNR] = PQ_GetTimeUs();
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_TNR)->UpdateMCNRCfg(pstVpssWbcInfo);
        sg_ulProcAlgEndTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_TNR] = PQ_GetTimeUs();
    }

    if (HI_TRUE == pstVpssWbcInfo->bProgressive) /* interace */
    {
        return s32Ret;
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DEI, SetDeiParam))
    {
        sg_ulProcAlgStartTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_DEI] = PQ_GetTimeUs();
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DEI)->SetDeiParam(pstVpssWbcInfo);
        sg_ulProcAlgEndTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_DEI] = PQ_GetTimeUs();
    }

    if (PQ_SOURCE_MODE_SD != PQ_COMM_GetSourceMode())
    {
        return s32Ret;
    }

    /*Add MCDI mode selection strategy.
       MCDI's onoff is up to UNF(or echo command) and FMD.
       if UNF and FMD both turn on MCDI, MCDI is on, or MCDI is replaced by MADI
    */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_FMD, GetMCDIMode))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_FMD)->GetMCDIMode(pstVpssWbcInfo->u32HandleNo, &bMCDIMode);

        if (bMCDIMode != s_bPreMCDIMode)
        {
            HI_BOOL bOnOff = stPqParam.bModuleOnOff[HI_PQ_MODULE_DEI] & bMCDIMode;
            s_bPreMCDIMode = bMCDIMode;

            if (PQ_FUNC_CALL(HI_PQ_MODULE_DEI, SetEnable))
            {
                s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DEI)->SetEnable(bOnOff);
            }
        }
    }
#endif

    return s32Ret;
}

static HI_S32 DRV_PQ_SetAlgIPSel(HI_PQ_ALGIP_SEL_E  enAlgIPSel)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PQ_REG_TYPE_E enPqRegType = REG_TYPE_VPSS;
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();
    PQ_OUTPUT_MODE_E enOutputMode = PQ_COMM_GetOutputMode();

    PQ_CHECK_OVER_RANGE_RE_FAIL(enAlgIPSel, HI_PQ_ALGIP_SEL_BUTT);

    if (HI_PQ_ALGIP_SEL_VDP == enAlgIPSel)
    {
        enPqRegType = REG_TYPE_VDP;
    }
    else if (HI_PQ_ALGIP_SEL_VPSS == enAlgIPSel)
    {
        enPqRegType = REG_TYPE_VPSS;
    }

#ifdef PQ_ALG_TNR
    PQ_MNG_RegisterTNR(enPqRegType);
#endif
#ifdef PQ_ALG_SNR
    PQ_MNG_RegisterSNR(enPqRegType);
#endif
#ifdef PQ_ALG_DB
    PQ_MNG_RegisterDB(enPqRegType);
#endif
#ifdef PQ_ALG_DM
    PQ_MNG_RegisterDM(enPqRegType);
#endif

    HI_INFO_PQ("Set Alg IPSel to %s\n", !enPqRegType ? "vpss" : "vdp");

    if (GET_ALG(HI_PQ_MODULE_TNR)
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_TNR))
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_TNR, PQ_SOURCE_MODE_UHD) == HI_TRUE)
        && GET_ALG_FUN(HI_PQ_MODULE_TNR)->InitVdpTnr)
    {
        GET_ALG_FUN(HI_PQ_MODULE_TNR)->InitVdpTnr();
    }

    if (GET_ALG(HI_PQ_MODULE_SNR)
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_SNR))
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_SNR, PQ_SOURCE_MODE_UHD) == HI_TRUE)
        && GET_ALG_FUN(HI_PQ_MODULE_SNR)->InitVdpSnr)
    {
        GET_ALG_FUN(HI_PQ_MODULE_SNR)->InitVdpSnr();
    }

    if (GET_ALG(HI_PQ_MODULE_DB)
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_DB))
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_DB, PQ_SOURCE_MODE_UHD) == HI_TRUE)
        && GET_ALG_FUN(HI_PQ_MODULE_DB)->InitVdpDbm)
    {
        GET_ALG_FUN(HI_PQ_MODULE_DB)->InitVdpDbm();
    }

    if (GET_ALG(HI_PQ_MODULE_DB)
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_DB))
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_DB, PQ_SOURCE_MODE_UHD) == HI_TRUE)
        && GET_ALG_FUN(HI_PQ_MODULE_DB)->DBCfgRefresh)
    {
        /* Refresh DB API CFG */
        GET_ALG_FUN(HI_PQ_MODULE_DB)->DBCfgRefresh(0, g_u32OutHeight, g_u32OutWidth, 0);
    }

    if (GET_ALG(HI_PQ_MODULE_SNR)
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_SNR))
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_SNR, PQ_SOURCE_MODE_UHD) == HI_TRUE))
    {
        if (GET_ALG_FUN(HI_PQ_MODULE_SNR)->SetSNRMotionEdgeLut)
        {
            GET_ALG_FUN(HI_PQ_MODULE_SNR)->SetSNRMotionEdgeLut(1920);
        }
        if (GET_ALG_FUN(HI_PQ_MODULE_SNR)->SetSNRCbCrLut)
        {
            GET_ALG_FUN(HI_PQ_MODULE_SNR)->SetSNRCbCrLut();
        }
        PQ_TABLE_LoadPhyListOfAlg(HI_PQ_MODULE_SNR, enSourceMode, enOutputMode);
    }

    if (GET_ALG(HI_PQ_MODULE_DM)
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_DM))
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_DM, PQ_SOURCE_MODE_UHD) == HI_TRUE))
    {
        PQ_TABLE_LoadPhyListOfAlg(HI_PQ_MODULE_DM, enSourceMode, enOutputMode);
    }

    s32Ret = DRV_PQ_ResetPqStatusParam(enPqRegType);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("ResetPqStatusParam PqRegType[%d] failed!\n", enPqRegType);
    }

    return s32Ret;
}


/* �����㷨������֮��ļĴ��� */
HI_S32 DRV_PQ_SetAlgCalcCfg(HI_PQ_WBC_INFO_S *pstVpssWbcInfo, HI_PQ_CFG_INFO_S *pstVpssCfgInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    /* IFMD */
    HI_PQ_IFMD_CALC_S      stIfmdCalcInfo;
    HI_PQ_IFMD_PLAYBACK_S  stIfmdCalcResult = {0};

    /* DB */
    HI_PQ_DB_CALC_INFO_S  stDbCalcInfo = {0};
    /* Stream Id */
    HI_U32 u32StreamId = 0;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssWbcInfo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssCfgInfo);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstVpssWbcInfo->u32HandleNo, VPSS_HANDLE_NUM);

    DRV_PQ_RefreshMktCoordinate(REG_TYPE_VPSS);

    /********
     * IFMD  interace
     ********/
    if ((HI_FALSE == pstVpssWbcInfo->bProgressive) && (PQ_FUNC_CALL(HI_PQ_MODULE_FMD, IfmdDect)))
    {
        sg_ulProcAlgStartTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_FMD] = PQ_GetTimeUs();
        /* IFMD Calc Info transfer */
        stIfmdCalcInfo.u32HandleNo       = pstVpssWbcInfo->u32HandleNo;
        stIfmdCalcInfo.u32WidthY         = pstVpssWbcInfo->u32Width;
        stIfmdCalcInfo.u32HeightY        = pstVpssWbcInfo->u32Height;
        stIfmdCalcInfo.s32FieldOrder     = pstVpssWbcInfo->s32FieldOrder;
        stIfmdCalcInfo.s32FieldMode      = pstVpssWbcInfo->s32FieldMode;
        stIfmdCalcInfo.u32FrameRate      = pstVpssWbcInfo->u32FrameRate;
        stIfmdCalcInfo.bPreInfo          = pstVpssWbcInfo->bPreInfo;
        stIfmdCalcInfo.enSplitMode       = pstVpssWbcInfo->enSplitMode;
        stIfmdCalcInfo.pstIfmdHardOutReg = pstVpssWbcInfo->pstVPSSWbcReg;
        memcpy(&(stIfmdCalcInfo.stVdecInfo), &(pstVpssWbcInfo->stVdecInfo), sizeof(PQ_VDEC_INFO_S));

        /* FMD After Calc Set CFG Reg to Reg */
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_FMD)->IfmdDect(&stIfmdCalcInfo, &stIfmdCalcResult);

        /* fmdCalcResult Tran to Vpss CFG */
        pstVpssCfgInfo->die_reset        = stIfmdCalcResult.die_reset;
        pstVpssCfgInfo->die_stop         = stIfmdCalcResult.die_stop;
        pstVpssCfgInfo->dir_mch          = stIfmdCalcResult.dir_mch;
        pstVpssCfgInfo->die_out_sel      = stIfmdCalcResult.die_out_sel;
        pstVpssCfgInfo->s32FieldOrder    = stIfmdCalcResult.s32FieldOrder;
        pstVpssCfgInfo->s32SceneChanged  = stIfmdCalcResult.s32SceneChanged;
        pstVpssCfgInfo->s32FilmType      = stIfmdCalcResult.s32FilmType;
        pstVpssCfgInfo->u32KeyValue      = stIfmdCalcResult.u32KeyValue;
        sg_ulProcAlgEndTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_FMD] = PQ_GetTimeUs();
    }

    /********
     * DB DM
     ********/

    /* DEBUG: CLOSE DB SOFTWARE ALG */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_DB, DBCalcConfigCfg) && (HI_PQ_ALGIP_SEL_VPSS == g_enAlgIPSel))
    {
        HI_S32 s32OriX,  s32OriY,  s32OriWidth,  s32OriHeight;
        HI_S32 s32CropX, s32CropY, s32CropWidth, s32CropHeight;
        sg_ulProcAlgStartTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_DB] = PQ_GetTimeUs();
        /* In practical using, In Vpss Db process before crop,and in vdp Db process after scaler */
        if (HI_TRUE == pstVpssWbcInfo->bCropBeforeDB)
        {
            s32OriX       = pstVpssWbcInfo->stOriCoordinate.s32X;
            s32OriY       = pstVpssWbcInfo->stOriCoordinate.s32Y;
            s32OriWidth   = pstVpssWbcInfo->stOriCoordinate.s32Width;
            s32OriHeight  = pstVpssWbcInfo->stOriCoordinate.s32Height;
            s32CropX      = pstVpssWbcInfo->stCropCoordinate.s32X;
            s32CropY      = pstVpssWbcInfo->stCropCoordinate.s32Y;
            s32CropWidth  = pstVpssWbcInfo->stCropCoordinate.s32Width;
            s32CropHeight = pstVpssWbcInfo->stCropCoordinate.s32Height;

            stDbCalcInfo.u32LeftOffset   = s32OriX - s32CropX;
            stDbCalcInfo.u32TopOffset    = s32OriY - s32CropY;
            stDbCalcInfo.u32RightOffset  = s32OriWidth  - s32CropWidth;
            stDbCalcInfo.u32BottomOffset = s32OriHeight - s32CropHeight;
        }
        else
        {
            stDbCalcInfo.u32LeftOffset   = 0;
            stDbCalcInfo.u32TopOffset    = 0;
            stDbCalcInfo.u32RightOffset  = 0;
            stDbCalcInfo.u32BottomOffset = 0;
        }

        /* DB Clac Info transfer */
        stDbCalcInfo.u32HandleNo       = pstVpssWbcInfo->u32HandleNo;
        stDbCalcInfo.u32BitDepth       = pstVpssWbcInfo->u32BitDepth;
        stDbCalcInfo.u32Width          = pstVpssWbcInfo->u32Width;
        stDbCalcInfo.u32Height         = pstVpssWbcInfo->u32Height;

        stDbCalcInfo.u32SingleModeFlag = pstVpssWbcInfo->u32SingleModeFlag;
        stDbCalcInfo.u32DBDeiEnFlag    = pstVpssWbcInfo->u32DeiEnFlag;
        stDbCalcInfo.u32FlagLine       = pstVpssWbcInfo->s32FieldMode;
        stDbCalcInfo.u32Protocol       = pstVpssWbcInfo->u32Protocol;
        stDbCalcInfo.u32ImageAvgQP     = pstVpssWbcInfo->u32ImageAvgQP;
        stDbCalcInfo.u32VdhInfoAddr    = pstVpssWbcInfo->u32VdhInfoAddr;
        stDbCalcInfo.u32VdhInfoStride  = pstVpssWbcInfo->u32VdhInfoStride;
        stDbCalcInfo.u32ImageStruct    = pstVpssWbcInfo->u32ImageStruct;
        stDbCalcInfo.pstVPSSWbcReg     = pstVpssWbcInfo->pstVPSSWbcReg;

        stDbCalcInfo.bDbBlkPosModeEn   = HI_FALSE;
        stDbCalcInfo.bDbFltDetModeEn   = HI_TRUE;
        /* Filter Control Enable; need judgement condition or not */
        stDbCalcInfo.bDBLumHorEn       = HI_TRUE;
        stDbCalcInfo.bDBLumVerEn       = HI_TRUE;
        /* add split mode */
        stDbCalcInfo.enSplitMode       = pstVpssWbcInfo->enSplitMode;

        /* DB After Calc Set CFG Reg to Reg */
        s32Ret  = GET_ALG_FUN(HI_PQ_MODULE_DB)->DBCalcConfigCfg(&stDbCalcInfo);
        sg_ulProcAlgEndTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_DB] = PQ_GetTimeUs();

        sg_ulProcAlgStartTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_DM] = PQ_GetTimeUs();
        if (PQ_FUNC_CALL(HI_PQ_MODULE_DM, DMCalcConfigCfg))
        {
            s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_DM)->DMCalcConfigCfg(&stDbCalcInfo);
        }
        sg_ulProcAlgEndTime[pstVpssWbcInfo->u32HandleNo][HI_PQ_MODULE_DM] = PQ_GetTimeUs();

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("DB DM CalcConfigCfg failed!\n");
            return s32Ret;
        }

        pqprint(PQ_PRN_FMD_READ, "[%s]: W:%d, H:%d, FldOrder:%d, FldMode:%d, FrmRate:%d, PreInfo:%d,PFrm:%d, PSeq:%d, RealFrmRate:%d\n",
                __FUNCTION__,
                pstVpssWbcInfo->u32Width,
                pstVpssWbcInfo->u32Height,
                pstVpssWbcInfo->s32FieldOrder,
                pstVpssWbcInfo->s32FieldMode,
                pstVpssWbcInfo->u32FrameRate,
                pstVpssWbcInfo->bPreInfo,
                pstVpssWbcInfo->stVdecInfo.IsProgressiveFrm,
                pstVpssWbcInfo->stVdecInfo.IsProgressiveSeq,
                pstVpssWbcInfo->stVdecInfo.RealFrmRate);
        pqprint(PQ_PRN_FMD_CALC, "[%s]: reset:%d, stop:%d, mch:%d, outsel:%d, FldOrder:%d, SceneChang:%d, FilmType:%d, KeyValue:%d\n",
                __FUNCTION__,
                pstVpssCfgInfo->die_reset,
                pstVpssCfgInfo->die_stop,
                pstVpssCfgInfo->dir_mch,
                pstVpssCfgInfo->die_out_sel,
                pstVpssCfgInfo->s32FieldOrder,
                pstVpssCfgInfo->s32SceneChanged,
                pstVpssCfgInfo->s32FilmType,
                pstVpssCfgInfo->u32KeyValue);
        pqprint(PQ_PRN_DB_READ, "[%s]: W:%d, H:%d\n",
                __FUNCTION__,
                pstVpssWbcInfo->u32Width,
                pstVpssWbcInfo->u32Height);
    }

    /* stream Id to set special para*/
    u32StreamId = pstVpssWbcInfo->u32StreamId;

    if (PQ_FUNC_CALL(HI_PQ_MODULE_SHARPNESS, SetStreamId))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_SHARPNESS)->SetStreamId(u32StreamId);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, SetStreamId))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DCI)->SetStreamId(u32StreamId);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DEI, SetStreamId))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DEI)->SetStreamId(u32StreamId);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DM, SetStreamId))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DM)->SetStreamId(u32StreamId);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_ZME, SetStreamId))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetStreamId(u32StreamId);
    }

    if (0 == pstVpssWbcInfo->u32HandleNo)
    {
        drv_pq_GetVpssCscCoef(pstVpssWbcInfo->u32HandleNo, sg_enVPMode[HI_DRV_PQ_VP_TYPE_PREVIEW]);
        drv_pq_GetVpssGammaCoef(pstVpssWbcInfo->u32HandleNo, sg_enVPMode[HI_DRV_PQ_VP_TYPE_PREVIEW]);
    }

    if (1 == pstVpssWbcInfo->u32HandleNo)
    {
        drv_pq_GetVpssCscCoef(pstVpssWbcInfo->u32HandleNo, sg_enVPMode[HI_DRV_PQ_VP_TYPE_REMOTE]);
        drv_pq_GetVpssGammaCoef(pstVpssWbcInfo->u32HandleNo, sg_enVPMode[HI_DRV_PQ_VP_TYPE_REMOTE]);
    }

    return HI_SUCCESS;
}


/* �����㷨������֮��ļĴ��� */
HI_S32 DRV_PQ_SetVdpAlgCalcCfg(HI_PQ_VDP_WBC_INFO_S *pstVdpWbcInfo)
{
    HI_U32 u32VId = PQ_VDP_LAYER_VID0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_DB_CALC_INFO_S  stDbCalcInfo = {0};  /* DB */

    PQ_CHECK_NULL_PTR_RE_FAIL(pstVdpWbcInfo);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstVdpWbcInfo->enLayerId, PQ_VDP_LAYER_VID_BUTT);

    if (g_enAlgIPSel != pstVdpWbcInfo->enAlgIPSel)
    {
        g_enAlgIPSel = pstVdpWbcInfo->enAlgIPSel;
        s32Ret = DRV_PQ_SetAlgIPSel(g_enAlgIPSel);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("SetAlgIPSel failed!\n");
        }
    }

    if (GET_ALG(HI_PQ_MODULE_TNR)
        && GET_ALG_FUN(HI_PQ_MODULE_TNR)->SetVdpTnrParaUpd
        && GET_ALG_FUN(HI_PQ_MODULE_TNR)->SetVdpTnrLutUpd
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_TNR))
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_TNR, PQ_SOURCE_MODE_UHD) == HI_TRUE))
    {
        GET_ALG_FUN(HI_PQ_MODULE_TNR)->SetVdpTnrParaUpd(u32VId);
        GET_ALG_FUN(HI_PQ_MODULE_TNR)->SetVdpTnrLutUpd(u32VId);
    }

    if (GET_ALG(HI_PQ_MODULE_SNR)
        && GET_ALG_FUN(HI_PQ_MODULE_SNR)->SetVdpSnrParaUpd
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_SNR))
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_SNR, PQ_SOURCE_MODE_UHD) == HI_TRUE))
    {
        GET_ALG_FUN(HI_PQ_MODULE_SNR)->SetVdpSnrParaUpd(u32VId);
    }

    if (GET_ALG(HI_PQ_MODULE_DB)
        && GET_ALG_FUN(HI_PQ_MODULE_DB)->SetVdpDbmParaUpd
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_DB))
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_DB, PQ_SOURCE_MODE_UHD) == HI_TRUE))
    {
        if (GET_ALG_FUN(HI_PQ_MODULE_DB)->SetVdpDbmInfo)
        {
            GET_ALG_FUN(HI_PQ_MODULE_DB)->SetVdpDbmInfo(pstVdpWbcInfo);
        }

        if (GET_ALG_FUN(HI_PQ_MODULE_DB)->SetVdpDbmParaUpd)
        {
            GET_ALG_FUN(HI_PQ_MODULE_DB)->SetVdpDbmParaUpd(u32VId);
        }
    }

    /********
     * DB DM
     ********/

    if (GET_ALG(HI_PQ_MODULE_DB)
        && GET_ALG_FUN(HI_PQ_MODULE_DB)->DBCalcConfigCfg
        && (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(HI_PQ_MODULE_DB))
        && (PQ_VDP_LAYER_VID0 == pstVdpWbcInfo->enLayerId)
        && (PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_DB, PQ_SOURCE_MODE_UHD) == HI_TRUE))
    {
        HI_S32 s32OriX,  s32OriY,  s32OriWidth,  s32OriHeight;
        HI_S32 s32CropX, s32CropY, s32CropWidth, s32CropHeight;

        /* In practical using, In Vpss Db process before crop,and in vdp Db process after scaler */
        if (HI_TRUE == pstVdpWbcInfo->bCropBeforeDB)
        {
            s32OriX       = pstVdpWbcInfo->stOriCoordinate.s32X;
            s32OriY       = pstVdpWbcInfo->stOriCoordinate.s32Y;
            s32OriWidth   = pstVdpWbcInfo->stOriCoordinate.s32Width;
            s32OriHeight  = pstVdpWbcInfo->stOriCoordinate.s32Height;
            s32CropX      = pstVdpWbcInfo->stCropCoordinate.s32X;
            s32CropY      = pstVdpWbcInfo->stCropCoordinate.s32Y;
            s32CropWidth  = pstVdpWbcInfo->stCropCoordinate.s32Width;
            s32CropHeight = pstVdpWbcInfo->stCropCoordinate.s32Height;

            stDbCalcInfo.u32LeftOffset   = s32OriX - s32CropX;
            stDbCalcInfo.u32TopOffset    = s32OriY - s32CropY;
            stDbCalcInfo.u32RightOffset  = s32OriWidth  - s32CropWidth;
            stDbCalcInfo.u32BottomOffset = s32OriHeight - s32CropHeight;
        }
        else
        {
            stDbCalcInfo.u32LeftOffset   = 0;
            stDbCalcInfo.u32TopOffset    = 0;
            stDbCalcInfo.u32RightOffset  = 0;
            stDbCalcInfo.u32BottomOffset = 0;
        }

        /* DB Clac Info transfer */
        stDbCalcInfo.u32HandleNo       = 0;
        stDbCalcInfo.u32BitDepth       = pstVdpWbcInfo->u32BitDepth;
        /* del width and height from vdp; because DB real width and Height is the W and H after Crop*/
        stDbCalcInfo.u32Width          = g_u32OutWidth;
        stDbCalcInfo.u32Height         = g_u32OutHeight;

        stDbCalcInfo.u32SingleModeFlag = pstVdpWbcInfo->u32SingleModeFlag;
        /* must be after dei in vpss; s32FieldMode and u32DeiEnFlag are useless in vdp; */
        stDbCalcInfo.u32DBDeiEnFlag    = 0;
        stDbCalcInfo.u32FlagLine       = 0;
        stDbCalcInfo.u32Protocol       = pstVdpWbcInfo->enVdecProtocol;
        stDbCalcInfo.u32ImageAvgQP     = pstVdpWbcInfo->u32ImageAvgQP;
        stDbCalcInfo.u32VdhInfoAddr    = pstVdpWbcInfo->u32VdhInfoAddr;
        stDbCalcInfo.u32VdhInfoStride  = pstVdpWbcInfo->u32VdhInfoStride;
        stDbCalcInfo.u32ImageStruct    = pstVdpWbcInfo->u32ImageStruct;
        stDbCalcInfo.pstVPSSWbcReg     = pstVdpWbcInfo->pstVdpWbcReg;

        stDbCalcInfo.bDbBlkPosModeEn   = HI_FALSE;
        stDbCalcInfo.bDbFltDetModeEn   = HI_TRUE;
        /* Filter Control Enable; need judgement condition or not */
        stDbCalcInfo.bDBLumHorEn       = HI_TRUE;
        stDbCalcInfo.bDBLumVerEn       = HI_TRUE;

        /* DB After Calc Set CFG Reg to Reg */
        s32Ret  = GET_ALG_FUN(HI_PQ_MODULE_DB)->DBCalcConfigCfg(&stDbCalcInfo);

        if (PQ_FUNC_CALL(HI_PQ_MODULE_DM, DMCalcConfigCfg))
        {
            s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_DM)->DMCalcConfigCfg(&stDbCalcInfo);
        }

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("DB DM CalcConfigCfg failed!\n");
            return s32Ret;
        }

        pqprint(PQ_PRN_DB_READ, "[%s]: W:%d, H:%d\n",
                __FUNCTION__,
                stDbCalcInfo.u32Width,
                stDbCalcInfo.u32Height);
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_PQ_GetFlashPqBin(PQ_PARAM_S *pstPqParam)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PQ_FILE_HEADER_S *pstPqFileHead = HI_NULL;
    HI_U32 u32CheckSize = 0;
    HI_U32 u32CheckPos  = 0;
    HI_U32 u32CheckSum  = 0;
    HI_U32 u32PqLen     = 0;
    HI_U8  *pu8PqAddr   = HI_NULL;
    PDM_EXPORT_FUNC_S   *pstPdmFuncs = HI_NULL;
    PQ_PARAM_S *pstPqBinParam = HI_NULL;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqParam);

    memset((HI_VOID *)pstPqParam, 0x0, sizeof(PQ_PARAM_S));

    /* get pq bin from pdm */
    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_PDM, (HI_VOID **)&pstPdmFuncs);

    if (s32Ret != HI_SUCCESS)
    {
        HI_FATAL_PQ("HI_DRV_MODULE_GetFunction failed!\n");
        return HI_FAILURE;
    }

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPdmFuncs);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPdmFuncs->pfnPDM_GetData);

    s32Ret = pstPdmFuncs->pfnPDM_GetData(PQ_DEF_NAME, &pu8PqAddr, &u32PqLen);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PQ("pstPdmFuncs->pfnPDM_GetData fail, PQ bin param may not burned\r\n");
        return HI_FAILURE;
    }

    if (HI_NULL == pu8PqAddr)
    {
        HI_WARN_PQ("pstPdmFuncs->pfnPDM_GetData get addr is null, PQ bin param may not burned\r\n");
        return HI_FAILURE;
    }

    pstPqBinParam = (PQ_PARAM_S *)pu8PqAddr;
    pstPqFileHead = &(pstPqBinParam->stPQFileHeader);

    u32CheckPos = (HI_U8 *) & (pstPqBinParam->stPQCoef) - (HI_U8 *)pstPqBinParam;
    u32CheckSize = pstPqFileHead->u32ParamSize;

    if (u32CheckSize != sizeof(PQ_PARAM_S))
    {
        HI_INFO_PQ( "check PQbin size error, Param Size = %d,sizeof(PQ_PARAM_S) = %d\n", u32CheckSize, sizeof(PQ_PARAM_S));
        return HI_FAILURE;
    }

    if (0 != HI_OSAL_Strncmp(pstPqFileHead->u8Version, PQ_VERSION, strlen(PQ_VERSION)))
    {
        HI_ERR_PQ( "check PQbin Version[%s] error\n", PQ_VERSION);
        return HI_FAILURE;
    }

    if (HI_SUCCESS != PQ_COMM_CheckChipName(pstPqFileHead->u8ChipName))
    {
        HI_ERR_PQ( "check PQbin ChipName[%s] error\n", pstPqFileHead->u8ChipName);
        return HI_FAILURE;
    }

    while (u32CheckPos < u32CheckSize)
    {
        u32CheckSum += *(HI_U8 *)(((HI_U8 *)pstPqBinParam) + u32CheckPos);
        u32CheckPos++;
    }

    if (u32CheckSum != pstPqFileHead->u32FileCheckSum)
    {
        HI_ERR_PQ( "PQbin checksum error,declare checksum = %d,calcsum = %d\r\n", pstPqFileHead->u32FileCheckSum, u32CheckSum);
        //pstPdmFuncs->pfnPDM_ReleaseReserveMem(PQ_DEF_NAME);
        return HI_FAILURE;
    }

    memcpy((HI_VOID *)(pstPqParam), (HI_VOID *)pstPqBinParam, sizeof(PQ_PARAM_S));

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetBinPhyAddr(HI_U32 *pu32Addr)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Addr);

    *pu32Addr = g_stPqBinBuf.u32StartPhyAddr;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetPicSetting(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_DISP_PARAM_S stSDDispParam;
    HI_DISP_PARAM_S stHDDispParam;
    PDM_EXPORT_FUNC_S *pstPdmFuncs = HI_NULL;

    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_PDM, (HI_VOID **)&pstPdmFuncs);
    if (s32Ret != HI_SUCCESS)
    {
        HI_WARN_PQ("HI_DRV_MODULE_GetFunction failed!\n");
        return HI_FAILURE;
    }

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPdmFuncs);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPdmFuncs->pfnPDM_GetDispParam);

    s32Ret = pstPdmFuncs->pfnPDM_GetDispParam(HI_UNF_DISPLAY0, &stSDDispParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PQ("baseparam may not burned\r\n");
        return HI_FAILURE;
    }

    stPqParam.stSDPictureSetting.u16Brightness = stSDDispParam.u32Brightness;
    stPqParam.stSDPictureSetting.u16Contrast   = stSDDispParam.u32Contrast;
    stPqParam.stSDPictureSetting.u16Hue        = stSDDispParam.u32HuePlus;
    stPqParam.stSDPictureSetting.u16Saturation = stSDDispParam.u32Saturation;

    stPqParam.stSDVideoSetting.u16Brightness = LEVEL2NUM(stSDDispParam.u32Brightness);
    stPqParam.stSDVideoSetting.u16Contrast   = LEVEL2NUM(stSDDispParam.u32Contrast);
    stPqParam.stSDVideoSetting.u16Hue        = LEVEL2NUM(stSDDispParam.u32HuePlus);
    stPqParam.stSDVideoSetting.u16Saturation = LEVEL2NUM(stSDDispParam.u32Saturation);

    s32Ret = pstPdmFuncs->pfnPDM_GetDispParam(HI_UNF_DISPLAY1, &stHDDispParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PQ("baseparam may not burned\r\n");
        return HI_FAILURE;
    }

    stPqParam.stHDPictureSetting.u16Brightness = stHDDispParam.u32Brightness;
    stPqParam.stHDPictureSetting.u16Contrast   = stHDDispParam.u32Contrast;
    stPqParam.stHDPictureSetting.u16Hue        = stHDDispParam.u32HuePlus;
    stPqParam.stHDPictureSetting.u16Saturation = stHDDispParam.u32Saturation;

    stPqParam.stHDVideoSetting.u16Brightness = LEVEL2NUM(stHDDispParam.u32Brightness);
    stPqParam.stHDVideoSetting.u16Contrast   = LEVEL2NUM(stHDDispParam.u32Contrast);
    stPqParam.stHDVideoSetting.u16Hue        = LEVEL2NUM(stHDDispParam.u32HuePlus);
    stPqParam.stHDVideoSetting.u16Saturation = LEVEL2NUM(stHDDispParam.u32Saturation);

    return HI_SUCCESS;
}

static HI_VOID drv_pq_SetDefaultZmeParam(HI_BOOL bDefault)
{
    if (PQ_FUNC_CALL(HI_PQ_MODULE_ZME, SetZmeDefault))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetZmeDefault(bDefault);
    }

    return;
}

static HI_VOID drv_pq_SetDefaultCSCParam(HI_BOOL bDefault)
{
    HI_PQ_PICTURE_SETTING_S stSDPictureSetting = {50, 50, 50, 50};
    HI_PQ_PICTURE_SETTING_S stHDPictureSetting = {50, 50, 50, 50};
    HI_PQ_PICTURE_SETTING_S stSDVideoSetting   = {128, 128, 128, 128};
    HI_PQ_PICTURE_SETTING_S stHDVideoSetting   = {128, 128, 128, 128};

    if (HI_TRUE == bDefault)
    {
        stSDPictureSetting.u16Brightness = 50;
        stSDPictureSetting.u16Contrast   = 50;
        stSDPictureSetting.u16Hue        = 50;
        stSDPictureSetting.u16Saturation = 50;
        stHDPictureSetting.u16Brightness = 50;
        stHDPictureSetting.u16Contrast   = 50;
        stHDPictureSetting.u16Hue        = 50;
        stHDPictureSetting.u16Saturation = 50;

        stSDVideoSetting.u16Brightness   = 128;
        stSDVideoSetting.u16Contrast     = 128;
        stSDVideoSetting.u16Hue          = 128;
        stSDVideoSetting.u16Saturation   = 128;
        stHDVideoSetting.u16Brightness   = 128;
        stHDVideoSetting.u16Contrast     = 128;
        stHDVideoSetting.u16Hue          = 128;
        stHDVideoSetting.u16Saturation   = 128;
    }
    else
    {
        stSDPictureSetting.u16Brightness = stPqParam.stSDPictureSetting.u16Brightness;
        stSDPictureSetting.u16Contrast   = stPqParam.stSDPictureSetting.u16Contrast;
        stSDPictureSetting.u16Hue        = stPqParam.stSDPictureSetting.u16Hue;
        stSDPictureSetting.u16Saturation = stPqParam.stSDPictureSetting.u16Saturation;
        stHDPictureSetting.u16Brightness = stPqParam.stHDPictureSetting.u16Brightness;
        stHDPictureSetting.u16Contrast   = stPqParam.stHDPictureSetting.u16Contrast;
        stHDPictureSetting.u16Hue        = stPqParam.stHDPictureSetting.u16Hue;
        stHDPictureSetting.u16Saturation = stPqParam.stHDPictureSetting.u16Saturation;

        stSDVideoSetting.u16Brightness   = stPqParam.stSDVideoSetting.u16Brightness;
        stSDVideoSetting.u16Contrast     = stPqParam.stSDVideoSetting.u16Contrast;
        stSDVideoSetting.u16Hue          = stPqParam.stSDVideoSetting.u16Hue;
        stSDVideoSetting.u16Saturation   = stPqParam.stSDVideoSetting.u16Saturation;
        stHDVideoSetting.u16Brightness   = stPqParam.stHDVideoSetting.u16Brightness;
        stHDVideoSetting.u16Contrast     = stPqParam.stHDVideoSetting.u16Contrast;
        stHDVideoSetting.u16Hue          = stPqParam.stHDVideoSetting.u16Hue;
        stHDVideoSetting.u16Saturation   = stPqParam.stHDVideoSetting.u16Saturation ;
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetCSCVideoSetting))
    {
        GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_0, &stSDVideoSetting);
        GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetCSCVideoSetting(HI_PQ_DISPLAY_1, &stHDVideoSetting);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXCSC, SetGfxCSCPictureSetting))
    {
        GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_0, &stSDPictureSetting);
        GET_ALG_FUN(HI_PQ_MODULE_GFXCSC)->SetGfxCSCPictureSetting(HI_PQ_DISPLAY_1, &stHDPictureSetting);
    }

    return;
}

static HI_VOID drv_pq_SetDefaultAlgParam(HI_BOOL bDefault)
{
    HI_U32  u32Alg      = 0;
    HI_BOOL bModuleOn   = HI_FALSE;

    for (u32Alg = 0; u32Alg < HI_PQ_MODULE_BUTT; u32Alg++)
    {
        bModuleOn = (HI_TRUE == bDefault) ? HI_FALSE : stPqParam.bModuleOnOff[u32Alg];
        drv_pq_SetModuleEn(u32Alg, bModuleOn);
    }

    return;
}

HI_S32 DRV_PQ_SetDefaultParam(HI_BOOL bDefault)
{
    drv_pq_SetDefaultZmeParam(bDefault);

    if (sg_bDefaultParam == bDefault)
    {
        return HI_SUCCESS;
    }

    drv_pq_SetDefaultCSCParam(bDefault);
    drv_pq_SetDefaultAlgParam(bDefault);

    sg_bDefaultParam = bDefault;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetDefaultParam(HI_BOOL *pbDefault)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbDefault);

    *pbDefault = sg_bDefaultParam;

    return HI_SUCCESS;
}


HI_S32 DRV_PQ_SetProcAlgTimeCntEn(HI_BOOL bEnable)
{
    g_bProcAlgTimeCntEn = bEnable;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetProcAlgTimeCntEn(HI_BOOL *pbEnable)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbEnable);

    *pbEnable = g_bProcAlgTimeCntEn;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetVpssProcAlgTimeCnt(HI_U32 u32Handle, HI_PQ_MODULE_E enPqModule, HI_ULONG *pulVpssAlgTimeCnt)
{
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Handle, VPSS_HANDLE_NUM);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(enPqModule, HI_PQ_MODULE_ALL);
    PQ_CHECK_NULL_PTR_RE_FAIL(pulVpssAlgTimeCnt);

    sg_ulProcAlgTimeCnt[u32Handle][enPqModule] = abs(sg_ulProcAlgEndTime[u32Handle][enPqModule] - sg_ulProcAlgStartTime[u32Handle][enPqModule]);

    *pulVpssAlgTimeCnt = sg_ulProcAlgTimeCnt[u32Handle][enPqModule];

    return HI_SUCCESS;
}


HI_S32 DRV_PQ_SetGfxZme(HI_PQ_GFX_LAYER_E enGfxZmeLayer, HI_PQ_GFX_ZME_PARA_S *pstGfxZmePara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enGfxZmeLayer, PQ_GFX_LAYER_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstGfxZmePara);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXZME, SetGfxZme))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXZME)->SetGfxZme(enGfxZmeLayer, pstGfxZmePara);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetHdrCfg(HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo, HI_PQ_HDR_CFG *pstPqHdrCfg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstXdrFrameInfo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqHdrCfg);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, GetHdrCfg))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_HDR)->GetHdrCfg(pstXdrFrameInfo, pstPqHdrCfg);
    }

    /* Hdr Process ACM use  */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_COLOR, GetHdrCfg))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_COLOR)->GetHdrCfg(pstXdrFrameInfo, pstPqHdrCfg);
    }

    /* Hdr Process ACC use checksum */
    if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, GetHdrCfg))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_DCI)->GetHdrCfg(pstXdrFrameInfo, pstPqHdrCfg);
    }

    return s32Ret;
}

HI_S32 DRV_PQ_GetGfxHdrCfg(HI_PQ_GFXHDR_HDR_INFO *pstGfxHdrInfo, HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstGfxHdrInfo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqGfxHdrCfg);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXHDR, GetGfxHdrCfg))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_GFXHDR)->GetGfxHdrCfg(pstGfxHdrInfo, pstPqGfxHdrCfg);
    }

    return s32Ret;
}

MODULE_LICENSE("GPL");

EXPORT_SYMBOL(DRV_PQ_UpdateVpssPQ);
EXPORT_SYMBOL(DRV_PQ_UpdateVdpPQ);
EXPORT_SYMBOL(DRV_PQ_UpdateVdpCSC);
EXPORT_SYMBOL(DRV_PQ_GetACCHistGram);
EXPORT_SYMBOL(DRV_PQ_UpdateACCHistGram);
EXPORT_SYMBOL(DRV_PQ_UpdateDCIWin);
EXPORT_SYMBOL(DRV_PQ_GetWbcInfo);
EXPORT_SYMBOL(DRV_PQ_SetAlgCalcCfg);
EXPORT_SYMBOL(DRV_PQ_SetVdpAlgCalcCfg);
EXPORT_SYMBOL(DRV_PQ_GetCSCCoef);
EXPORT_SYMBOL(DRV_PQ_Get8BitCSCCoef);
EXPORT_SYMBOL(DRV_PQ_SetZme);
EXPORT_SYMBOL(DRV_PQ_SetVpssZme);
EXPORT_SYMBOL(DRV_PQ_SetVpssLCHDR);
EXPORT_SYMBOL(DRV_PQ_GetHDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_GetSDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_SetHDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_SetSDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_GetHDVideoSetting);
EXPORT_SYMBOL(DRV_PQ_GetSDVideoSetting);
EXPORT_SYMBOL(DRV_PQ_SetHDVideoSetting);
EXPORT_SYMBOL(DRV_PQ_SetSDVideoSetting);
EXPORT_SYMBOL(DRV_PQ_GetVdpZmeCoef);
EXPORT_SYMBOL(DRV_PQ_GetVdpZmeStrategy);
EXPORT_SYMBOL(DRV_PQ_SetGfxZme);
EXPORT_SYMBOL(DRV_PQ_SetGfxCscCoef);
EXPORT_SYMBOL(DRV_PQ_GetHdrCfg);
EXPORT_SYMBOL(DRV_PQ_GetGfxHdrCfg);
EXPORT_SYMBOL(DRV_PQ_SetDefaultParam);
EXPORT_SYMBOL(DRV_PQ_GetMcdiSplitMode);


