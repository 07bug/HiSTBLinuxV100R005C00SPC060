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
  Author        : sdk
******************************************************************************/
#include "drv_pq.h"
#include "drv_pdm_ext.h"
#include "drv_pq_ext.h"
#include "hi_drv_dev.h"

#define  PQ_MODIFY_TIME     "(20170819)"

PQ_PARAM_S     *g_pstPqParam = HI_NULL; /*PQ BIN */
MMZ_BUFFER_S    g_stPqBinBuf;
HI_BOOL         g_bLoadPqBin;

static HI_DRV_PQ_PARAM_S stPqParam;
static HI_U32  sg_u32SourceMode = PQ_SOURCE_MODE_NO;
static HI_U32  sg_u32OutputMode = PQ_OUTPUT_MODE_NO;
static HI_BOOL sg_bFastBoot     = HI_FALSE;

static HI_U32 sg_u32ImageWidth  = 1280;
static HI_U32 sg_u32ImageHeight = 720;
static HI_U32 sg_u32OutWidth    = 1280;
static HI_U32 sg_u32OutHeight   = 720;
static HI_BOOL sg_bRWZBDefaultEnable     = HI_FALSE; /* rwzb flag */

static HI_S32 DRV_PQ_CheckChipName(HI_CHAR *pchChipName);
static HI_S32 DRV_PQ_GetFlashPqBin(PQ_PARAM_S *pstPqParam);
static HI_S32 DRV_PQ_GetPicSetting(HI_VOID);
static HI_S32 DRV_PQ_SetVdpMktCoordinate(HI_U32 u32MktCoordinate);

PQ_EXPORT_FUNC_S   g_PqExportFuncs =
{
    .pfnPQ_UpdateVpssPQ           = DRV_PQ_UpdateVpssPQ,
    .pfnPQ_UpdateVdpPQ            = DRV_PQ_UpdateVdpPQ,
    .pfnPQ_UpdateVdpCSC           = DRV_PQ_UpdateVdpCSC,
    .pfnPQ_UpdateDCIWin           = DRV_PQ_UpdateDCIWin,
    .pfnPQ_SetZme                 = DRV_PQ_SetZme,
    .pfnPQ_SetVpssZme             = DRV_PQ_SetVpssZme,
    .pfnPQ_GetCSCCoef             = DRV_PQ_GetCSCCoef,
    .pfnPQ_Get8BitCSCCoef         = DRV_PQ_Get8BitCSCCoef,
    .pfnPQ_GetWbcInfo             = DRV_PQ_GetWbcInfo,
    .pfnPQ_SetAlgCalcCfg          = DRV_PQ_SetAlgCalcCfg,
    .pfnPQ_PfmdDetect             = DRV_PQ_PfmdDetect,
    .pfnPQ_GetDciHistgram         = DRV_PQ_GetDciHistgram,
    .pfnPQ_GetHDPictureSetting    = DRV_PQ_GetHDPictureSetting,
    .pfnPQ_GetSDPictureSetting    = DRV_PQ_GetSDPictureSetting,
    .pfnPQ_SetHDPictureSetting    = DRV_PQ_SetHDPictureSetting,
    .pfnPQ_SetSDPictureSetting    = DRV_PQ_SetSDPictureSetting,
    .pfnPQ_GetHDVideoSetting      = DRV_PQ_GetHDVideoSetting,
    .pfnPQ_GetSDVideoSetting      = DRV_PQ_GetSDVideoSetting,
    .pfnPQ_SetHDVideoSetting      = DRV_PQ_SetHDVideoSetting,
    .pfnPQ_SetSDVideoSetting      = DRV_PQ_SetSDVideoSetting
};

static HI_S32 drv_pq_ProcSetBrightness(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetContrast(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetHue(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetSaturation(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetDB(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetDM(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetFleshTone(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetColorMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetSharp(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetDCI(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetACM(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetSR(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetTNR(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetVPSS(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetVDP(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetAll(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetDeiMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetVpssZme(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetVdpZme(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetFodMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetPrintBin(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetPrintType(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetTunMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetCfgDefault(HI_CHAR *pArg1, HI_CHAR *pArg2);


typedef HI_S32 (*pFunProc) (HI_CHAR *pArg1, HI_CHAR *pArg2);

typedef struct hiPQ_PROC_FUN_S
{
    HI_CHAR *pFuncName;
    pFunProc pfnProc;
} PQ_PROC_FUN_S;

static PQ_PROC_FUN_S g_stPQProcInfo[] =
{
    {"bright",       drv_pq_ProcSetBrightness},
    {"contrast",     drv_pq_ProcSetContrast},
    {"hue",          drv_pq_ProcSetHue},
    {"satu",         drv_pq_ProcSetSaturation},
    {"db",           drv_pq_ProcSetDB},
    {"dm",           drv_pq_ProcSetDM},
    {"fleshtone",    drv_pq_ProcSetFleshTone},
    {"colormode",    drv_pq_ProcSetColorMode},
    {"sharp",        drv_pq_ProcSetSharp},
    {"dci",          drv_pq_ProcSetDCI},
    {"acm",          drv_pq_ProcSetACM},
    {"sr",           drv_pq_ProcSetSR},
    {"tnr",          drv_pq_ProcSetTNR},
    {"vpss",         drv_pq_ProcSetVPSS},
    {"vdp",          drv_pq_ProcSetVDP},
    {"all",          drv_pq_ProcSetAll},
    {"deimode",      drv_pq_ProcSetDeiMode},
    {"vpsszme",      drv_pq_ProcSetVpssZme},
    {"vdpzme",       drv_pq_ProcSetVdpZme},
    {"fodmode",      drv_pq_ProcSetFodMode},
    {"printbin",     drv_pq_ProcSetPrintBin},
    {"printtype",    drv_pq_ProcSetPrintType},
    {"tunmode",      drv_pq_ProcSetTunMode},
    {"rwzbdefault",  drv_pq_ProcSetCfgDefault},
};

#ifdef PQ_PROC_CTRL_SUPPORT
HI_U8 *g_pPQProcSourceType[PQ_SOURCE_MODE_BUTT] =
{
    "Unknown",
    "SD",
    "HD",
    "UHD",
};

HI_U8 *g_pPQProcFleshTone[FLE_GAIN_BUTT] =
{
    "off",
    "low",
    "middle",
    "high",
};

HI_U8 *g_pPQProcFldMode[ALG_DEI_MODE_BUTT] =
{
    "5Field",
    "4Field",
    "3Field",
};

HI_U8 *g_pPQProcCSC[HAL_CSC_BUTT + 1] =
{
    "ProcPQ_CSC_YUV2RGB_601      ",
    "ProcPQ_CSC_YUV2RGB_709      ",
    "ProcPQ_CSC_RGB2YUV_601      ",
    "ProcPQ_CSC_RGB2YUV_709      ",
    "ProcPQ_CSC_YUV2YUV_709_601  ",
    "ProcPQ_CSC_YUV2YUV_601_709  ",
    "ProcPQ_CSC_YUV2YUV          ",
    "ProcPQ_CSC_YUV2RGB_601_FULL ",
    "ProcPQ_CSC_YUV2RGB_709_FULL ",
    "ProcPQ_CSC_RGB2YUV_601_FULL ",
    "ProcPQ_CSC_RGB2YUV_709_FULL ",
    "ProcPQ_CSC_RGB2RGB          ",
    "NULL",

};

HI_U8 *g_pPQProcEnhanceMode[COLOR_MODE_BUTT] =
{
    "optimal",
    "blue",
    "green",
    "bg",
    "original",
};

HI_U8 *g_pPQProcSRDemoMode[SR_DEMO_BUTT] =
{
    "all off",
    "left off,right on",
    "left on,right off",
    "all on",
};
#endif

HI_S32 HI_DRV_PQ_DeInit(HI_VOID)
{
    HI_S32 s32Ret;

    HI_DRV_MODULE_UnRegister(HI_ID_PQ);
    if (HI_NULL != g_stPqBinBuf.pu8StartVirAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;
    }

    s32Ret = PQ_MNG_DeinitSharpen();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit SHARPEN error!\n");
        return HI_FAILURE;
    }
    s32Ret = PQ_MNG_DeInitDei();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit DEI error!\n");
        return HI_FAILURE;
    }
    s32Ret = PQ_MNG_DeinitDNR();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit DNR error!\n");
        return HI_FAILURE;
    }

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    s32Ret = PQ_MNG_DeInitTnr();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init Tnr error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeInitDeshoot();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit Deshoot error!\n");
        return HI_FAILURE;
    }
#endif

    s32Ret = PQ_MNG_DeinitSR();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit SR error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeInitIfmd();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit Ifmd error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeInitZme();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit ZME error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeinitDCI();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit DCI error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeInitColor();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit Color error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeInitPQTable();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit PQ table error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_HAL_Deinit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit PQ device error!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_S32 HI_DRV_PQ_Init(HI_CHAR *pszPath)
{
    HI_S32 s32Ret;
    HI_S32 i;
    g_bLoadPqBin = HI_FALSE;
    g_pstPqParam = HI_NULL;

    s32Ret = HI_DRV_MODULE_Register(HI_ID_PQ, PQ_NAME, (HI_VOID *)&g_PqExportFuncs);

    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_PQ("ERR: HI_DRV_MODULE_Register!\n");
        return s32Ret;
    }

    s32Ret = HI_DRV_MMZ_AllocAndMap("PQ_FLASH_BIN", HI_NULL, sizeof(PQ_PARAM_S), 0, (MMZ_BUFFER_S *)(&g_stPqBinBuf));
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_PQ("ERR: Pqdriver mmz memory failed!\n");
        g_bLoadPqBin = HI_FALSE;
        return s32Ret;
    }

    g_pstPqParam = (PQ_PARAM_S *)g_stPqBinBuf.pu8StartVirAddr;
    HI_INFO_PQ("\ng_stPqBinBuf.u32StartVirAddr = 0x%x,g_stPqBinBuf.u32StartVirAddr = 0x%x\n", g_stPqBinBuf.u32StartPhyAddr, g_stPqBinBuf.pu8StartVirAddr);

    s32Ret = DRV_PQ_GetFlashPqBin(g_pstPqParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Load PQBin failed!\n");
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
        stPqParam.stSDPictureSetting.u16Brightness = 128;
        stPqParam.stSDPictureSetting.u16Contrast   = 128;
        stPqParam.stSDPictureSetting.u16Hue        = 128;
        stPqParam.stSDPictureSetting.u16Saturation = 128;
        stPqParam.stHDPictureSetting.u16Brightness = 128;
        stPqParam.stHDPictureSetting.u16Contrast   = 128;
        stPqParam.stHDPictureSetting.u16Hue        = 128;
        stPqParam.stHDPictureSetting.u16Saturation = 128;
        stPqParam.stSDVideoSetting.u16Brightness   = 128;
        stPqParam.stSDVideoSetting.u16Contrast     = 128;
        stPqParam.stSDVideoSetting.u16Hue          = 128;
        stPqParam.stSDVideoSetting.u16Saturation   = 128;
        stPqParam.stHDVideoSetting.u16Brightness   = 128;
        stPqParam.stHDVideoSetting.u16Contrast     = 128;
        stPqParam.stHDVideoSetting.u16Hue          = 128;
        stPqParam.stHDVideoSetting.u16Saturation   = 128;
    }

    s32Ret = PQ_HAL_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init PQ device error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitPQTable(g_pstPqParam, !g_bLoadPqBin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init PQ table failure!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitDei();
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init DEI error!\n");
        return HI_FAILURE;
    }
    s32Ret = PQ_MNG_InitSharpen(g_pstPqParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init SHARPEN error!\n");
        return HI_FAILURE;
    }
    /* SD DR add from HiFoneB2, But there is not SD DR in 3716mv410 */
    s32Ret = PQ_MNG_InitDNR(g_pstPqParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init DNR error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitIfmd(g_pstPqParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init Ifmd error!\n");
        return HI_FAILURE;
    }
#if defined(CHIP_TYPE_hi3716mv410)|| defined(CHIP_TYPE_hi3716mv420)
    s32Ret = PQ_MNG_InitTnr();
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init Tnr error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitDeshoot();
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init Deshoot failure!\n");
        return HI_FAILURE;
    }
#endif

    s32Ret = PQ_MNG_InitSR();
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init SR failure!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitZme();
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init ZME failure!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitDCI(g_pstPqParam, !g_bLoadPqBin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init DCI failure!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitColor(g_pstPqParam, !g_bLoadPqBin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S *)(&g_stPqBinBuf));
        g_stPqBinBuf.pu8StartVirAddr = HI_NULL;

        HI_ERR_PQ("Init Color failure!\n");
        return HI_FAILURE;
    }

    /*Init Customer PQ setting*/
    stPqParam.stColorTemp.s16RedGain     = 128;
    stPqParam.stColorTemp.s16GreenGain   = 128;
    stPqParam.stColorTemp.s16BlueGain    = 128;
    stPqParam.stColorTemp.s16RedOffset   = 128;
    stPqParam.stColorTemp.s16GreenOffset = 128;
    stPqParam.stColorTemp.s16BlueOffset  = 128;

    stPqParam.stDciWin.u16HStar = 0;
    stPqParam.stDciWin.u16HEnd  = 0;
    stPqParam.stDciWin.u16VStar = 0;
    stPqParam.stDciWin.u16VEnd  = 0;

    stPqParam.u32TNRLevel       = 50;
    stPqParam.u32Sharpness      = 128;
    stPqParam.u32DBLevel        = 128;
    stPqParam.u32DRLevel        = 128;
    stPqParam.u32ColorGainLevel = 128;
    stPqParam.u32NrAuto         = HI_FALSE;
    stPqParam.u32DCILevelGain   = 50;
    stPqParam.stColorEnhance.enColorEnhanceType      = HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
    stPqParam.stColorEnhance.unColorGain.enColorMode = HI_PQ_COLOR_MODE_RECOMMEND;
    stPqParam.enDemoMode                             = HI_PQ_DEMO_MODE_FIXED_R;

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        stPqParam.bDemoOnOff[i] = HI_FALSE;
    }

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        stPqParam.bModuleOnOff[i] = HI_FALSE;
    }

    stPqParam.bModuleOnOff[HI_PQ_MODULE_SR]        = HI_TRUE;

    /* In Mv410 Open dci and sharpen enable default setting, same as mv310 */
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    stPqParam.bModuleOnOff[HI_PQ_MODULE_TNR]       = HI_TRUE;
    stPqParam.bModuleOnOff[HI_PQ_MODULE_DB]        = HI_TRUE;
    stPqParam.bModuleOnOff[HI_PQ_MODULE_DM]        = HI_TRUE;
    stPqParam.bModuleOnOff[HI_PQ_MODULE_DCI]       = HI_TRUE;
    stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS] = HI_TRUE;
#endif

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
    HI_S32 s32Ret;

    if (HI_TRUE == sg_bFastBoot)
    {
        s32Ret = DRV_PQ_GetPicSetting();
        if (HI_SUCCESS != s32Ret)
        {
            HI_WARN_PQ("ERR: DRV_PQ_GetPicSetting failed!\n");
        }
    }

    return HI_SUCCESS;
}

/**
 \brief ��ȡ��������
 \attention \n
��

 \param[out] pu32Brightness ����ֵ,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSDBrightness(HI_U32 *pu32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Brightness);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);

    pqprint(PQ_PRN_CSC, "Get SD Brightness: %d\n", *pu32Brightness);
    return HI_SUCCESS;
}

/**
 \brief ���ñ�������
 \attention \n
��

 \param[in] u32Brightness, ����ֵ,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDBrightness(HI_U32 u32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Brightness, 100);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPqParam.stSDPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);
    stPqParam.stSDVideoSetting.u16Brightness   = LEVEL2NUM(u32Brightness);

    pqprint(PQ_PRN_CSC, "Set SD Brightness: %d\n", u32Brightness);
    return HI_SUCCESS;
}

/**
 \brief ��ȡ����Աȶ�
 \attention \n
��

 \param[out] pu32Contrast �Աȶ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSDContrast(HI_U32 *pu32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Contrast);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Contrast = NUM2LEVEL(stPictureSetting.u16Contrast);

    pqprint(PQ_PRN_CSC, "Get SD Contrast: %d\n", *pu32Contrast);
    return HI_SUCCESS;
}

/**
 \brief ���ñ���Աȶ�
 \attention \n
��

 \param[in] u32Contrast, �Աȶ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDContrast(HI_U32 u32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Contrast, 100);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPqParam.stSDPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);
    stPqParam.stSDVideoSetting.u16Contrast   = LEVEL2NUM(u32Contrast);

    pqprint(PQ_PRN_CSC, "Set SD Contrast: %d\n", u32Contrast);
    return HI_SUCCESS;
}

/**
 \brief ��ȡ����ɫ��
 \attention \n
��

 \param[out] pu32Hue  ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSDHue(HI_U32 *pu32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Hue);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Hue = NUM2LEVEL(stPictureSetting.u16Hue);

    pqprint(PQ_PRN_CSC, "Get SD Hue: %d\n", *pu32Hue);
    return HI_SUCCESS;
}

/**
 \brief ���ñ���ɫ��
 \attention \n
��

 \param[in] u32Hue   ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDHue(HI_U32 u32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Hue, 100);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Hue = LEVEL2NUM(u32Hue);

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPqParam.stSDPictureSetting.u16Hue = LEVEL2NUM(u32Hue);
    stPqParam.stSDVideoSetting.u16Hue   = LEVEL2NUM(u32Hue);

    pqprint(PQ_PRN_CSC, "Set SD Hue: %d\n", u32Hue);
    return HI_SUCCESS;
}

/**
 \brief ��ȡ���履�Ͷ�
 \attention \n
��

 \param[out] pu32Saturation  ���Ͷ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSDSaturation(HI_U32 *pu32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Saturation);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);

    pqprint(PQ_PRN_CSC, "Get SD Saturation: %d\n", *pu32Saturation);
    return HI_SUCCESS;
}

/**
 \brief ���ñ��履�Ͷ�
 \attention \n
��

 \param[in] u32Saturation ���Ͷ�,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDSaturation(HI_U32 u32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Saturation, 100);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPqParam.stSDPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);
    stPqParam.stSDVideoSetting.u16Saturation   = LEVEL2NUM(u32Saturation);

    pqprint(PQ_PRN_CSC, "Set SD Saturation: %d\n", u32Saturation);
    return HI_SUCCESS;
}

/**
 \brief ��ȡ��������
 \attention \n
��

 \param[out] pu32Brightness ����ֵ,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDBrightness(HI_U32 *pu32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Brightness);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);

    pqprint(PQ_PRN_CSC, "Get HD Brightness: %d\n", *pu32Brightness);
    return HI_SUCCESS;
}

/**
 \brief ���ø�������
 \attention \n
��

 \param[in] u32Brightness, ����ֵ,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDBrightness(HI_U32 u32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Brightness, 100);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPqParam.stHDPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);
    stPqParam.stHDVideoSetting.u16Brightness   = LEVEL2NUM(u32Brightness);

    pqprint(PQ_PRN_CSC, "Set HD Brightness: %d\n", u32Brightness);
    return HI_SUCCESS;
}

/**
 \brief ��ȡ����Աȶ�
 \attention \n
��

 \param[out] pu32Contrast �Աȶ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDContrast(HI_U32 *pu32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Contrast);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Contrast = NUM2LEVEL(stPictureSetting.u16Contrast);

    pqprint(PQ_PRN_CSC, "Get HD Contrast: %d\n", *pu32Contrast);
    return HI_SUCCESS;
}

/**
 \brief ���ø���Աȶ�
 \attention \n
��

 \param[in] u32Contrast, �Աȶ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDContrast(HI_U32 u32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Contrast, 100);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPqParam.stHDPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);
    stPqParam.stHDVideoSetting.u16Contrast   = LEVEL2NUM(u32Contrast);

    pqprint(PQ_PRN_CSC, "Set HD Contrast: %d\n", u32Contrast);
    return HI_SUCCESS;
}


/**
 \brief ��ȡ����ɫ��
 \attention \n
��

 \param[out] pu32Hue  ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDHue(HI_U32 *pu32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Hue);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Hue = NUM2LEVEL(stPictureSetting.u16Hue);

    pqprint(PQ_PRN_CSC, "Get HD Hue: %d\n", *pu32Hue);
    return HI_SUCCESS;
}


/**
 \brief ���ø���ɫ��
 \attention \n
��

 \param[in] u32Hue   ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDHue(HI_U32 u32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Hue, 100);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Hue = LEVEL2NUM(u32Hue);

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPqParam.stHDPictureSetting.u16Hue = LEVEL2NUM(u32Hue);
    stPqParam.stHDVideoSetting.u16Hue   = LEVEL2NUM(u32Hue);

    pqprint(PQ_PRN_CSC, "Set HD Hue: %d\n", u32Hue);
    return HI_SUCCESS;
}


/**
 \brief ��ȡ���履�Ͷ�
 \attention \n
��

 \param[out] pu32Saturation  ���Ͷ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDSaturation(HI_U32 *pu32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Saturation);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);

    pqprint(PQ_PRN_CSC, "Get HD Saturation: %d\n", *pu32Saturation);
    return HI_SUCCESS;
}


/**
 \brief ���ø��履�Ͷ�
 \attention \n
��

 \param[in] u32Saturation ���Ͷ�,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDSaturation(HI_U32 u32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Saturation, 100);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPqParam.stHDPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);
    stPqParam.stHDVideoSetting.u16Saturation   = LEVEL2NUM(u32Saturation);

    pqprint(PQ_PRN_CSC, "Set HD Saturation: %d\n", u32Saturation);
    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetSDTemperature(HI_PQ_COLORTEMPERATURE_S *pstTemperature)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTemperature);

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetSDTemperature(HI_PQ_COLORTEMPERATURE_S *pstTemperature)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTemperature);

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetHDTemperature(HI_PQ_COLORTEMPERATURE_S *pstTemperature)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTemperature);

    return HI_SUCCESS;
}


HI_S32 DRV_PQ_GetHDTemperature(HI_PQ_COLORTEMPERATURE_S *pstTemperature)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTemperature);

    return HI_SUCCESS;
}


/**
 \brief ��ȡ��Ƶ��������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPictureSetting);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    pstPictureSetting->u16Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);
    pstPictureSetting->u16Contrast   = NUM2LEVEL(stPictureSetting.u16Contrast);
    pstPictureSetting->u16Hue        = NUM2LEVEL(stPictureSetting.u16Hue);
    pstPictureSetting->u16Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);

    return HI_SUCCESS;
}


/**
 \brief ��ȡ��Ƶ��������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPictureSetting);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    pstPictureSetting->u16Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);
    pstPictureSetting->u16Contrast   = NUM2LEVEL(stPictureSetting.u16Contrast);
    pstPictureSetting->u16Hue        = NUM2LEVEL(stPictureSetting.u16Hue);
    pstPictureSetting->u16Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);

    return HI_SUCCESS;
}


/**
 \brief ������Ƶ��������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp = {0};

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPictureSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Hue, 100);

    pqprint(PQ_PRN_CSC, "Set Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n",
            pstPictureSetting->u16Brightness,
            pstPictureSetting->u16Contrast,
            pstPictureSetting->u16Hue,
            pstPictureSetting->u16Saturation);

    stPictureSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPictureSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPictureSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPictureSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);

    stPqParam.stHDVideoSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPqParam.stHDVideoSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPqParam.stHDVideoSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPqParam.stHDVideoSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);

    return HI_SUCCESS;
}


/**
 \brief ������Ƶ��������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDVideoSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp = {0};

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPictureSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Hue, 100);

    pqprint(PQ_PRN_CSC, "Set Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n",
            pstPictureSetting->u16Brightness,
            pstPictureSetting->u16Contrast,
            pstPictureSetting->u16Hue,
            pstPictureSetting->u16Saturation);

    stPictureSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPictureSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPictureSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPictureSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);

    stPqParam.stSDVideoSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPqParam.stSDVideoSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPqParam.stSDVideoSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPqParam.stSDVideoSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);

    return HI_SUCCESS;
}


/**
 \brief ��ȡͼ�θ�������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPictureSetting);

    pstPictureSetting->u16Brightness  = NUM2LEVEL(stPqParam.stHDPictureSetting.u16Brightness);
    pstPictureSetting->u16Contrast    = NUM2LEVEL(stPqParam.stHDPictureSetting.u16Contrast);
    pstPictureSetting->u16Hue         = NUM2LEVEL(stPqParam.stHDPictureSetting.u16Hue);
    pstPictureSetting->u16Saturation  = NUM2LEVEL(stPqParam.stHDPictureSetting.u16Saturation);

    return HI_SUCCESS;
}


/**
 \brief ��ȡͼ�α�������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPictureSetting);

    pstPictureSetting->u16Brightness  = NUM2LEVEL(stPqParam.stSDPictureSetting.u16Brightness);
    pstPictureSetting->u16Contrast    = NUM2LEVEL(stPqParam.stSDPictureSetting.u16Contrast);
    pstPictureSetting->u16Hue         = NUM2LEVEL(stPqParam.stSDPictureSetting.u16Hue);
    pstPictureSetting->u16Saturation  = NUM2LEVEL(stPqParam.stSDPictureSetting.u16Saturation);

    return HI_SUCCESS;
}


/**
 \brief ����ͼ�θ�������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPictureSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Hue, 100);

    HI_DEBUG_PQ("SetHDPicture Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n", \
                pstPictureSetting->u16Brightness, \
                pstPictureSetting->u16Contrast, \
                pstPictureSetting->u16Hue, \
                pstPictureSetting->u16Saturation);

    stPqParam.stHDPictureSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPqParam.stHDPictureSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPqParam.stHDPictureSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPqParam.stHDPictureSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);
    return HI_SUCCESS;
}


/**
 \brief ����ͼ�α�������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDPictureSetting(HI_PQ_PICTURE_SETTING_S *pstPictureSetting)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstPictureSetting);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Brightness, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Contrast, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Saturation, 100);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(pstPictureSetting->u16Hue, 100);

    stPqParam.stSDPictureSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPqParam.stSDPictureSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPqParam.stSDPictureSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPqParam.stSDPictureSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);
    return HI_SUCCESS;
}

/**
 \brief ��ȡ������
 \attention \n
��

 \param[out] pu32Sharpness  ������, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSharpness(HI_U32 *pu32Sharpness)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Sharpness);

    *pu32Sharpness = NUM2LEVEL(stPqParam.u32Sharpness);

    pqprint(PQ_PRN_SHARPEN, "Get sharpen: %d\n", *pu32Sharpness);
    return HI_SUCCESS;
}

/**
 \brief ����������
 \attention \n
��

 \param[in] u32Sharpness, ������, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSharpness(HI_U32 u32Sharpness)
{
    HI_S32 s32Ret;
    HI_U32 u32Num = LEVEL2NUM(u32Sharpness);/* 0~100 trans to 0~255 */

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32Sharpness, 100);

    s32Ret = PQ_MNG_SetSharpenStr(u32Num, sg_u32SourceMode, sg_u32OutputMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("error in setting sharpness strength\n");
        return s32Ret;
    }

    stPqParam.u32Sharpness = u32Num;
    pqprint(PQ_PRN_SHARPEN, "Set sharpen: %d\n", u32Sharpness);

    return HI_SUCCESS;
}

/**
 \brief ��ȡ��ɫ��ǿ
 \attention \n
��

 \param[out] pu32ColorGainLevel

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetColorEhance(HI_U32 *pu32ColorGainLevel)
{
    HI_S32 s32Ret;
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32ColorGainLevel);

    s32Ret = PQ_MNG_GetColorGainLevel(pu32ColorGainLevel);
    *pu32ColorGainLevel = NUM2LEVEL(*pu32ColorGainLevel);

    pqprint(PQ_PRN_ACM, "Get ColorGainLevel: %d\n", *pu32ColorGainLevel);
    return s32Ret;
}


/**
 \brief ������ɫ��ǿ
 \attention \n
��

 \param[in] u32ColorGainLevel

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetColorEhance(HI_U32 u32ColorGainLevel)
{
    HI_U32 u32Num = LEVEL2NUM(u32ColorGainLevel);

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32ColorGainLevel, 100);

    stPqParam.u32ColorGainLevel = u32Num;
    pqprint(PQ_PRN_ACM, "Set ColorGainLevel: %d\n", u32ColorGainLevel);
    return PQ_MNG_SetColorGainLevel(u32Num);
}

/**
 \brief ��ȡ��ɫ��ǿ
 \attention \n
  ��

 \param[out] pu32FleshToneLevel

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetFleshToneLevel(HI_U32 *pu32FleshToneLevel)
{
    HI_S32 s32Ret;
    HI_U32 u32Level = 0;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32FleshToneLevel);
    s32Ret = PQ_MNG_GetFleshToneLevel(&u32Level);
    *pu32FleshToneLevel = u32Level;

    pqprint(PQ_PRN_ACM, "Get FleshTone: %d\n", *pu32FleshToneLevel);

    return s32Ret;
}

/**
 \brief ���÷�ɫ��ǿ
 \attention \n
  ��

 \param[in] enFleshToneLevel

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetFleshToneLevel(HI_PQ_FLESHTONE_E enFleshToneLevel)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(enFleshToneLevel, HI_PQ_FLESHTONE_GAIN_BUTT);

    stPqParam.stColorEnhance.enColorEnhanceType      = HI_PQ_COLOR_ENHANCE_FLESHTONE;
    stPqParam.stColorEnhance.unColorGain.enFleshtone = enFleshToneLevel;

    pqprint(PQ_PRN_ACM, "Set FleshTone: %d\n", enFleshToneLevel);
    return PQ_MNG_SetFleshToneLevel(enFleshToneLevel, sg_u32SourceMode);
}

/**
 \brief ����ɫ��������
 \attention \n
  ��

 \param[in] enSixColorType;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSixBaseColorLevel(HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColorOffset)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstSixBaseColorOffset);

    pqprint(PQ_PRN_ACM, "Set SixBaseColor Red:%d, Green: %d, Blue: %d, Cyan: %d, Magenta: %d, Yellow: %d\n",
            pstSixBaseColorOffset->u32Red, pstSixBaseColorOffset->u32Green,
            pstSixBaseColorOffset->u32Blue, pstSixBaseColorOffset->u32Cyan,
            pstSixBaseColorOffset->u32Magenta, pstSixBaseColorOffset->u32Yellow);

    stPqParam.stColorEnhance.enColorEnhanceType    = HI_PQ_COLOR_ENHANCE_SIX_BASE;
    stPqParam.stColorEnhance.unColorGain.stSixBase = *pstSixBaseColorOffset;

    return PQ_MNG_SetSixBaseColorLevel((SIX_BASE_COLOR_OFFSET_S *)pstSixBaseColorOffset, sg_u32SourceMode);
}

/**
 \brief ��ɫ��ǿģʽ����
 \attention \n
  ��

 \param[in] enColorSpecMode 0-RECOMMEND;1-BLUE;2-GREEN;3-BG;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetColorEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(enColorSpecMode, HI_PQ_COLOR_MODE_BUTT);

    stPqParam.stColorEnhance.enColorEnhanceType      = HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
    stPqParam.stColorEnhance.unColorGain.enColorMode = enColorSpecMode;

    pqprint(PQ_PRN_ACM, "Set ColorEnhanceMode: %d\n", enColorSpecMode);
    return PQ_MNG_SetColorEnhanceMode(enColorSpecMode, sg_u32SourceMode);
}


/**
 \brief ����DCIǿ������ȼ�
 \attention \n
��

 \param[in] u32DCILevelGain;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDCILevelGain(HI_U32 u32DCILevelGain)
{
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32DCILevelGain, 100);

    stPqParam.u32DCILevelGain = u32DCILevelGain;
    pqprint(PQ_PRN_DCI, "Set DCILevelGain: %d\n", u32DCILevelGain);
    return PQ_MNG_SetDCILevelGain(u32DCILevelGain, sg_u32SourceMode);
}


/**
 \brief ����DCI��������
 \attention \n
��

 \param[in] pstDciCoef;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetDCIWgtLut(DCI_WGT_S *pstDciCoef)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstDciCoef);

    g_pstPqParam->stPQCoef.stDciCoef.stPqDciLut = *(PQ_DCI_LUT_S *)pstDciCoef;

    return PQ_HAL_SetDCIWgtLut(pstDciCoef);
}

/**
 \brief ��ȡ����ǿ��
 \attention \n
��

 \param[out] pu32NRLevel: ����ȼ�, ��Ч��Χ: 0~255


 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetTnrLevel(HI_U32 *pu32TnrLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32Strength = 0;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32TnrLevel);

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    s32Ret = PQ_MNG_GetTnrStrength(&s32Strength);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("error in getting TNR strength\n");
        return HI_FAILURE;
    }
#endif

    *pu32TnrLevel = s32Strength;

    return s32Ret;
}

/**
 \brief ���ý���ǿ��
 \attention \n
��

 \param[in] u32tNRLevel: ����ȼ�, ��Ч��Χ: 0~255

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetTnrLevel(HI_U32 u32TnrLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32TnrLevel, 100);

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    s32Ret = PQ_MNG_SetTnrStrength(u32TnrLevel);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("error in setting TNR strength\n");
        return HI_FAILURE;
    }
    HI_DEBUG_PQ("Set TNR level %d\n", u32TnrLevel);
    stPqParam.u32TNRLevel = u32TnrLevel;
#endif

    return s32Ret;
}

/**
 \brief ��������ģʽ����
 \attention \n
��

 \param[in] enFlags
 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetDemoMode(HI_PQ_MODULE_E enFlags, HI_BOOL bOnOff)
{
    HI_U32 i;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enFlags, HI_PQ_MODULE_BUTT);

    if (enFlags == HI_PQ_MODULE_DB)
    {
        PQ_MNG_EnableDBDemo(bOnOff);/* can set DB Demo in HiFone, MV410, it does not exist DB in 98M */
        HI_DEBUG_PQ("DB demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DR)
    {
        PQ_MNG_EnableDRDemo(bOnOff); /* can set DR Demo in 98M and HiFone, it does not exist DR in MV410 */
    }
    else if (enFlags == HI_PQ_MODULE_DM)
    {
        PQ_MNG_EnableDMDemo(bOnOff); /* can set DM Demo in HiFone and MV410, it does not exist DM in 98M */
    }
    else if (enFlags == HI_PQ_MODULE_DBM)
    {
        PQ_MNG_EnableDBDemo(bOnOff);
        PQ_MNG_EnableDMDemo(bOnOff);
        HI_DEBUG_PQ("DBM demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_COLOR)
    {
        PQ_MNG_EnableACMDemo(bOnOff);
        pqprint(PQ_PRN_ACM, "COLOR demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_TNR)
    {
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
        PQ_MNG_EnableTnrDemo(bOnOff);
        HI_DEBUG_PQ("TNR demo %s\n", bOnOff ? "on" : "off");
#endif
    }
    else if (enFlags == HI_PQ_MODULE_SHARPNESS)
    {
        PQ_MNG_EnableSharpenDemo(bOnOff);
        pqprint(PQ_PRN_SHARPEN, "Sharpeness demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DCI)
    {
        PQ_MNG_EnableDCIDemo(bOnOff);
        pqprint(PQ_PRN_DCI, "DCI demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_SR)
    {
        PQ_MNG_EnableSRDemo(bOnOff);
        pqprint(PQ_PRN_SR, "SR demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DEI)
    {
        PQ_MNG_EnableDeiDemo(bOnOff);
        HI_DEBUG_PQ("DEI demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_ALL)
    {
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
        PQ_MNG_EnableTnrDemo(bOnOff);
#endif
        PQ_MNG_EnableDBDemo(bOnOff);
        PQ_MNG_EnableDMDemo(bOnOff);
        PQ_MNG_EnableDRDemo(bOnOff);
        PQ_MNG_EnableSRDemo(bOnOff);
        PQ_MNG_EnableACMDemo(bOnOff);
        PQ_MNG_EnableSharpenDemo(bOnOff);
        PQ_MNG_EnableDCIDemo(bOnOff);
        PQ_MNG_EnableDeiDemo(bOnOff);
        //PQ_MNG_EnableNrDemo(bOnOff);

        for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
        {
            stPqParam.bDemoOnOff[i] = bOnOff;
        }

        pqprint(PQ_PRN_DBG, "ALL demo %s\n", bOnOff ? "on" : "off");
    }
    stPqParam.bDemoOnOff[enFlags] = bOnOff;
    return HI_SUCCESS;
}

/**
 \brief set demo display mode
 \attention \n
  ��

 \param[in] enDemoMode;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetDemoDispMode(HI_PQ_DEMO_MODE_E enDemoMode, HI_PQ_MOUDULE_FLAG_E enFlag)
{
    HI_S32 s32Ret = HI_FAILURE;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enFlag, HI_PQ_MOUDULE_FLAG_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enDemoMode, HI_PQ_DEMO_MODE_BUTT);

    if ((HI_PQ_DEMO_MODE_FIXED_R == enDemoMode) || (HI_PQ_DEMO_MODE_SCROLL_R == enDemoMode))
    {
        if (HI_PQ_MOUDULE_FLAG_VPSS == enFlag)
        {
            /* Vpss */
            s32Ret =  PQ_MNG_SetDeiDemoMode(DEI_DEMO_ENABLE_R);
            /* Can Set Dbm Demo Mode At MV410 and HiFone; Other Chip does not support */
            s32Ret |= PQ_MNG_SetDbmDemoMode(DBM_DEMO_ENABLE_R);
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
            s32Ret |= PQ_MNG_SetTnrDemoMode(TNR_DEMO_ENABLE_R);
#endif
        }
        else if (HI_PQ_MOUDULE_FLAG_VDP == enFlag)
        {
            /* Vdp */
            s32Ret =  PQ_MNG_SetACMDemoMode(ACM_DEMO_ENABLE_R);
            s32Ret |= PQ_MNG_SetDCIDemoMode(DCI_DEMO_ENABLE_R);
            s32Ret |= PQ_MNG_SetSharpDemoMode(SHARP_DEMO_ENABLE_R);
        }
    }
    else if ((HI_PQ_DEMO_MODE_FIXED_L == enDemoMode) || (HI_PQ_DEMO_MODE_SCROLL_L == enDemoMode))
    {
        if (HI_PQ_MOUDULE_FLAG_VPSS == enFlag)
        {
            /* Vpss */
            s32Ret =  PQ_MNG_SetDeiDemoMode(DEI_DEMO_ENABLE_L);
            s32Ret |= PQ_MNG_SetDbmDemoMode(DBM_DEMO_ENABLE_L);
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
            s32Ret |= PQ_MNG_SetTnrDemoMode(TNR_DEMO_ENABLE_L);
#endif
        }
        else if (HI_PQ_MOUDULE_FLAG_VDP == enFlag)
        {
            /* Vdp */
            s32Ret = PQ_MNG_SetACMDemoMode(ACM_DEMO_ENABLE_L);
            s32Ret |= PQ_MNG_SetDCIDemoMode(DCI_DEMO_ENABLE_L);
            s32Ret |= PQ_MNG_SetSharpDemoMode(SHARP_DEMO_ENABLE_L);
        }
    }

    stPqParam.enDemoMode = enDemoMode;
    return s32Ret;
}

/**
 \brief get demo display mode
 \attention \n
  ��

 \param[in] penDemoMode ;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetDemoDispMode(HI_PQ_DEMO_MODE_E *penDemoMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(penDemoMode);

    *penDemoMode = stPqParam.enDemoMode;

    return HI_SUCCESS;
}

/**
 \brief ��ȡPQģ�鿪��״̬
 \attention \n
  ��

 \param[in] enFlags
 \param[out] *pu32OnOff

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetPQModule(HI_PQ_MODULE_E enFlags, HI_U32 *pu32OnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32OnOff);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enFlags, HI_PQ_MODULE_BUTT);

    if (enFlags == HI_PQ_MODULE_DCI)
    {
        PQ_MNG_GetDCIEnable(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_COLOR)
    {
        PQ_HAL_GetACMEnableFlag(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_TNR)
    {
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
        PQ_MNG_GetTnrEnableFlag(pu32OnOff);
#endif
    }
    else if (enFlags == HI_PQ_MODULE_SNR)
    {
    }
    else if (enFlags == HI_PQ_MODULE_DB)
    {
        PQ_MNG_GetDBEnableFlag(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_DM)
    {
        PQ_MNG_GetDMEnableFlag(pu32OnOff);/* There is DM in HiFoneB2 and MV410, It does not DR in 98M */
    }
    else if (enFlags == HI_PQ_MODULE_DR)
    {
        PQ_MNG_GetDREnableFlag(pu32OnOff);/* There is DR in HiFoneB2 and 98M, It does not DR in MV410 */
    }
    else if (enFlags == HI_PQ_MODULE_DBM)
    {
        PQ_MNG_GetDBEnableFlag(pu32OnOff);/* only get DB */
    }
    else if (enFlags == HI_PQ_MODULE_SHARPNESS)
    {
        PQ_MNG_GetSharpenEnable(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_SR)
    {
        PQ_MNG_GetSREnableFlag(pu32OnOff);
    }

    return HI_SUCCESS;
}


/**
 \brief ����PQģ�鿪��
 \attention \n
  ��

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetPQModule(HI_PQ_MODULE_E enFlags, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(enFlags, HI_PQ_MODULE_BUTT);

    if (enFlags == HI_PQ_MODULE_DCI)
    {
        s32Ret = PQ_MNG_EnableDCI(u32OnOff);
        pqprint(PQ_PRN_DCI, "Set DCI  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_COLOR)
    {
        s32Ret = PQ_MNG_EnableColorEnhance(u32OnOff);
        pqprint(PQ_PRN_ACM, "Set COLOR  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_TNR)
    {
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
        s32Ret = PQ_MNG_EnableTnr(u32OnOff);
        pqprint(PQ_PRN_TNR, "Set TNR  %s\n", u32OnOff ? "on" : "off");
#endif
    }
    else if (enFlags == HI_PQ_MODULE_SNR)
    {
        //HI_DEBUG_PQ("Set SNR  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DB)
    {
        /* In does not Exist DB in 98M, It is Control by Vpss in HiFoneB2 and MV410 *//* merge it Using software method */
        s32Ret = PQ_MNG_EnableDB(u32OnOff);
        pqprint(PQ_PRN_DB_READ, "Set DB  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DR)
    {
        /* In does not Exist DR in MV410, And There is not effect in HiFoneB2 and 98M */
        s32Ret = PQ_MNG_EnableDR(u32OnOff);
        pqprint(PQ_PRN_DNR, "Set DR  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DM)
    {
        /* In does not Exist DM in 98M, It is Control by Vpss in HiFoneB2 and MV410 *//* merge it Using software method */
        s32Ret = PQ_MNG_EnableDM(u32OnOff);
        pqprint(PQ_PRN_DM, "Set DM  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DBM)
    {
        s32Ret  = PQ_MNG_EnableDB(u32OnOff);
        s32Ret |= PQ_MNG_EnableDM(u32OnOff);
        pqprint(PQ_PRN_DB_READ, "Set DBM  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_SHARPNESS)
    {
        /* include Sharpen and HSharpen in VPSS *//* MV410 Sharpen in Vdp */
        s32Ret = PQ_MNG_EnableSharpen(u32OnOff);
        pqprint(PQ_PRN_SHARPEN, "Set SHARPEN  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_SR)
    {
        /* VDP CTRL SR */ /* We Control it Using software method */
        s32Ret = PQ_MNG_EnableSR(u32OnOff);
        pqprint(PQ_PRN_SR, "Set SR  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_ALL)
    {
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
        PQ_MNG_EnableTnr(u32OnOff);
#endif
        PQ_MNG_EnableSR(u32OnOff);
        PQ_MNG_EnableDCI(u32OnOff);
        PQ_MNG_EnableColorEnhance(u32OnOff);
        PQ_MNG_EnableDB(u32OnOff);
        PQ_MNG_EnableDM(u32OnOff);
        PQ_MNG_EnableDR(u32OnOff);
        PQ_MNG_EnableSharpen(u32OnOff);
    }

    if (HI_FALSE == sg_bRWZBDefaultEnable)
    {
        stPqParam.bModuleOnOff[enFlags] = u32OnOff;
    }

    return s32Ret;
}

static HI_VOID DRV_PQ_RefreshVpssCfg(HI_VOID)
{
#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200_b) || defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    HI_BOOL bModuleOn = HI_FALSE;
    /* HSharpen or Sharpen */
    static HI_U32 s_u32InMode  = PQ_SOURCE_MODE_NO;
    static HI_U32 s_u32OutMode = PQ_OUTPUT_MODE_NO;

    /* HSharpen or Sharpen */
    if ((s_u32InMode != sg_u32OutputMode) || (s_u32OutMode != sg_u32SourceMode))
    {
        PQ_MNG_InitPhyList(0, REG_TYPE_VPSS, sg_u32SourceMode, sg_u32OutputMode, PQ_BIN_MODULE_SHARPEN);

        s_u32InMode  = sg_u32OutputMode;
        s_u32OutMode = sg_u32SourceMode;

        bModuleOn = (HI_TRUE == sg_bRWZBDefaultEnable) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS];
        PQ_MNG_EnableSharpen(bModuleOn);
        PQ_MNG_EnableSharpenDemo(stPqParam.bDemoOnOff[HI_PQ_MODULE_SHARPNESS]);
        (HI_VOID)DRV_PQ_SetSharpness(NUM2LEVEL(stPqParam.u32Sharpness));
    }
#endif

    return;
}

static HI_VOID DRV_PQ_RefreshMktCoordinate(HI_VOID)
{
    /* DEMO */
    HI_U32 u32Step = 1;
    static HI_U32 s_u32Pos = 0;

    /* set demo display mode*/
    if ((HI_PQ_DEMO_MODE_FIXED_R == stPqParam.enDemoMode) || (HI_PQ_DEMO_MODE_FIXED_L == stPqParam.enDemoMode))
    {
        (HI_VOID)PQ_MNG_SetVpssMktCoordinate(sg_u32ImageWidth / 2);
        (HI_VOID)DRV_PQ_SetVdpMktCoordinate(sg_u32OutWidth / 2);
    }
    else if ((HI_PQ_DEMO_MODE_SCROLL_R == stPqParam.enDemoMode) || (HI_PQ_DEMO_MODE_SCROLL_L == stPqParam.enDemoMode))
    {
        if (0 == sg_u32ImageWidth)
        {
            return;
        }

        (HI_VOID)PQ_MNG_SetVpssMktCoordinate(s_u32Pos);
        (HI_VOID)DRV_PQ_SetVdpMktCoordinate(s_u32Pos * sg_u32OutWidth / sg_u32ImageWidth);

        s_u32Pos = s_u32Pos + u32Step;
        if (sg_u32ImageWidth < s_u32Pos)
        {
            s_u32Pos = 0;
        }
    }

    return;
}

/**
 \brief Timming�仯�����VPSS PQ��������
 \attention \n
��

 \param[in]  *u32HandleNo:   VPSSͨ����
 \param[in]  *pstTimingInfo: Timming Info
 \param[in]  *pstVPSSReg:    VPSS ����Ĵ�����ַ
 \param[out] *pstPQModule:   PQ���������Ŀ��ز���

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateVpssPQ(HI_U32 u32HandleNo, HI_VPSS_PQ_INFO_S *pstTimingInfo, PQ_VPSS_CFG_REG_S *pstVPSSReg, PQ_VPSS_WBC_REG_S *pstWbcReg, HI_PQ_VPSS_MODULE_S *pstPQModule)
{
    HI_S32 s32Ret;
    HI_BOOL bModuleOn = HI_FALSE;

    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(u32HandleNo, VPSS_HANDLE_NUM);

    PQ_HAL_UpdateVpssReg(u32HandleNo, pstVPSSReg, pstWbcReg);

    if (pstVPSSReg != HI_NULL && pstTimingInfo != HI_NULL)
    {
        pqprint(PQ_PRN_VPSS, "[%s]: HandleNo:%d, Width:%d, Height:%d, FrameRate:%d, Interlace:%d\n",
                __FUNCTION__, u32HandleNo, pstTimingInfo->u32Width, pstTimingInfo->u32Height,
                pstTimingInfo->u32FrameRate, pstTimingInfo->bInterlace);

        sg_u32ImageWidth  = pstTimingInfo->u32Width;
        sg_u32ImageHeight = pstTimingInfo->u32Height;
        sg_u32SourceMode  = PQ_MNG_CheckSourceMode(pstTimingInfo->u32Width, pstTimingInfo->u32Height);

        /* Load VPSS Physical Register */
        s32Ret = PQ_MNG_LoadPhyList(REG_TYPE_VPSS, sg_u32SourceMode, sg_u32OutputMode, PQ_BIN_MODULE_ALL);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("PQ_MNG_LoadPhyList VDP failed!\n");
            return s32Ret;
        }
        /* Ifmd Para Init */
        s32Ret = PQ_MNG_IFMD_SofewareParaInitByHandleNo(u32HandleNo);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("SofewareParaInitByHandleNo failed\n");
            return HI_FAILURE;
        }

        //PQ_MNG_UpdataVpssPQ(u32HandleNo, pstTimingInfo);

        /*************************************************************************
         *   reset vpss customer pq setting
         *************************************************************************/

        /* Set DBM; Enable DB and DB Demo Using Users Data When Timming Change */
        /* Can Control DB Enable Using Software method in MV410; It is useless In HiFone and 98M */
        bModuleOn = (HI_TRUE == sg_bRWZBDefaultEnable) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_DB];
        PQ_MNG_EnableDB(bModuleOn);
        /* Can Control DB Demo Enable To reg in MV410 and Hifone; It is useless In 98M */
        PQ_MNG_EnableDBDemo(stPqParam.bDemoOnOff[HI_PQ_MODULE_DBM]);
        PQ_MNG_EnableDMDemo(stPqParam.bDemoOnOff[HI_PQ_MODULE_DBM]);
        PQ_MNG_EnableDeiDemo(stPqParam.bDemoOnOff[HI_PQ_MODULE_DEI]);

        /* Refresh DB API CFG *//* Take effect in HiFone and Mv410; But no practical meaning in 98M*/
        s32Ret = PQ_MNG_DBCfgRefresh(u32HandleNo, pstTimingInfo->u32Height, pstTimingInfo->u32Width, pstTimingInfo->u32FrameRate);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("PQ_MNG_DBCfgRefresh failed!\n");
            return s32Ret;
        }

#if defined(CHIP_TYPE_hi3798cv200_a) || defined(CHIP_TYPE_hi3798cv200_b) || defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)

        /* Set Sharp include HSharpen and Sharpen; 98M and hiFone Sharpen in Vpss*/
        bModuleOn = (HI_TRUE == sg_bRWZBDefaultEnable) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS];
        PQ_MNG_EnableSharpen(bModuleOn);
        PQ_MNG_EnableSharpenDemo(stPqParam.bDemoOnOff[HI_PQ_MODULE_SHARPNESS]);
        s32Ret = DRV_PQ_SetSharpness(NUM2LEVEL(stPqParam.u32Sharpness));
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("DRV_PQ_SetSharpness failed!\n");
            return s32Ret;
        }
#endif
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
        /* Set TNR*/
        bModuleOn = (HI_TRUE == sg_bRWZBDefaultEnable) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_TNR];
        PQ_MNG_EnableTnr(bModuleOn);
        PQ_MNG_EnableTnrDemo(stPqParam.bDemoOnOff[HI_PQ_MODULE_TNR]);
        s32Ret = DRV_PQ_SetTnrLevel(stPqParam.u32TNRLevel);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("DRV_PQ_SetTnrLevel failed!\n");
            return s32Ret;
        }

        /* set demo display mode*/
        DRV_PQ_SetDemoDispMode(stPqParam.enDemoMode, HI_PQ_MOUDULE_FLAG_VPSS);
#endif
    }

    return HI_SUCCESS;
}

/**
 \brief Timming�仯�����VDP PQ��������
 \attention \n
��

 \param[in] pstTimingInfo: Timming Info
 \param[in] *pstVDPReg:VDP ����Ĵ�����ַ

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateVdpPQ(HI_PQ_DISPLAY_E enDisplayId, HI_VDP_PQ_INFO_S *pstTimingInfo, S_VDP_REGS_TYPE *pstVDPReg)
{
    HI_S32 s32Ret;
    HI_U32 u32TmpOutputMode;
    HI_BOOL bTimingChange = HI_FALSE;
    HI_BOOL bModuleOn = HI_FALSE;
    static HI_VDP_PQ_INFO_S stTimingInfo[HI_PQ_DISPLAY_BUTT] = {{0}};

    PQ_CHECK_OVER_RANGE_RE_FAIL(enDisplayId, HI_PQ_DISPLAY_BUTT);

    /* Update VDP Register point */
    PQ_HAL_UpdateVdpReg(pstVDPReg);
    DRV_PQ_RefreshMktCoordinate();

    if (pstVDPReg != HI_NULL && pstTimingInfo != HI_NULL)
    {
        pqprint(PQ_PRN_VDP, "[%s]: DisplayId:%d, Width: %d, Height: %d, OutWidth:%d, OutHeight:%d, bSRState: %d\n",
                __FUNCTION__, enDisplayId, pstTimingInfo->u32Width, pstTimingInfo->u32Height,
                pstTimingInfo->u32OutWidth, pstTimingInfo->u32OutHeight, pstTimingInfo->bSRState);


        bTimingChange  =  (stTimingInfo[enDisplayId].u32Width != pstTimingInfo->u32Width)
                          || (stTimingInfo[enDisplayId].u32Height != pstTimingInfo->u32Height)
                          || (stTimingInfo[enDisplayId].u32OutWidth != pstTimingInfo->u32OutWidth)
                          || (stTimingInfo[enDisplayId].u32OutHeight != pstTimingInfo->u32OutHeight)
                          || (stTimingInfo[enDisplayId].bSRState != pstTimingInfo->bSRState);

        if ((HI_TRUE == pstTimingInfo->bPartUpdate) && (HI_FALSE == bTimingChange))
        {
            return HI_SUCCESS;
        }

        memcpy(&stTimingInfo[enDisplayId], pstTimingInfo, sizeof(HI_VDP_PQ_INFO_S));

        sg_u32SourceMode = PQ_MNG_CheckSourceMode(pstTimingInfo->u32Width, pstTimingInfo->u32Height);
        u32TmpOutputMode = PQ_MNG_CheckOutputMode(pstTimingInfo->bSRState);

        if ((HI_PQ_DISPLAY_1 == enDisplayId) || (HI_PQ_DISPLAY_2 == enDisplayId))
        {
            sg_u32OutWidth   = pstTimingInfo->u32OutWidth;
            sg_u32OutHeight  = pstTimingInfo->u32OutHeight;
            sg_u32OutputMode = u32TmpOutputMode;
        }

        /* Load VDP Physical Register */
        if (HI_TRUE == pstTimingInfo->bPartUpdate)
        {
            /*Set Partly update*/

            s32Ret = PQ_MNG_LoadMultiList(REG_TYPE_VDP, sg_u32SourceMode, u32TmpOutputMode, PQ_BIN_MODULE_ALL);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_PQ("PQ_MNG_LoadMultiList VDP failed!\n");
                return s32Ret;
            }

            /* Set Color Enhance */
            s32Ret = PQ_MNG_SetACMGain(sg_u32SourceMode);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_PQ("Set ACMGain failed!\n");
                return s32Ret;
            }
        }
        else
        {
            /*Set FULL update*/

            s32Ret = PQ_MNG_LoadPhyList(REG_TYPE_VDP, sg_u32SourceMode, u32TmpOutputMode, PQ_BIN_MODULE_ALL);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_PQ("PQ_MNG_LoadPhyList VDP failed!\n");
                return s32Ret;
            }

            /*Set Picture Setting*/
            s32Ret  = PQ_MNG_SetSDPictureSetting(&stPqParam.stSDVideoSetting, &stPqParam.stColorTemp);
            s32Ret |= PQ_MNG_SetHDPictureSetting(&stPqParam.stHDVideoSetting, &stPqParam.stColorTemp);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_PQ("set VDP customer pq setting error!\n");
            }

            /* Set Color Enhance */
            if (HI_PQ_COLOR_ENHANCE_FLESHTONE == stPqParam.stColorEnhance.enColorEnhanceType)
            {
                s32Ret = PQ_MNG_SetFleshToneLevel(stPqParam.stColorEnhance.unColorGain.enFleshtone, sg_u32SourceMode);
            }
            else if (HI_PQ_COLOR_ENHANCE_SIX_BASE == stPqParam.stColorEnhance.enColorEnhanceType)
            {
                HI_PQ_SIX_BASE_COLOR_S *pstPQSixBase = &(stPqParam.stColorEnhance.unColorGain.stSixBase);
                s32Ret = PQ_MNG_SetSixBaseColorLevel((SIX_BASE_COLOR_OFFSET_S *)pstPQSixBase, sg_u32SourceMode);
            }
            else if (HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE == stPqParam.stColorEnhance.enColorEnhanceType)
            {
                s32Ret = PQ_MNG_SetColorEnhanceMode(stPqParam.stColorEnhance.unColorGain.enColorMode, sg_u32SourceMode);
            }

            /* Update Coef */
            PQ_HAL_UpdateDCICoef(VDP_LAYER_VP0);
            PQ_HAL_UpdatACMCoef(VDP_LAYER_VP0);
        }

        /* set isogeny mode */
        PQ_MNG_SetIsogenyMode(pstTimingInfo->bIsogenyMode);


        /*************************************************************************
         *   reset VDP customer pq setting
         *************************************************************************/


        /* Set Module */
        bModuleOn = (HI_TRUE == sg_bRWZBDefaultEnable) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_SR];
        DRV_PQ_SetPQModule(HI_PQ_MODULE_SR, bModuleOn);
        bModuleOn = (HI_TRUE == sg_bRWZBDefaultEnable) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_DCI];
        PQ_MNG_EnableDCI(bModuleOn);
        bModuleOn = (HI_TRUE == sg_bRWZBDefaultEnable) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_COLOR];
        PQ_MNG_EnableColorEnhance(bModuleOn);

        /* Set Demo */
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_SR, stPqParam.bDemoOnOff[HI_PQ_MODULE_SR]);
        PQ_MNG_EnableDCIDemo(stPqParam.bDemoOnOff[HI_PQ_MODULE_DCI]);
        PQ_MNG_EnableACMDemo(stPqParam.bDemoOnOff[HI_PQ_MODULE_COLOR]);

        /* Set DCI Level */
        s32Ret = PQ_MNG_SetDCILevelGain(stPqParam.u32DCILevelGain, sg_u32SourceMode);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("PQ_MNG_SetDCILevelGain failed!\n");
            return s32Ret;
        }

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
        /* Mv410 Sharpen in Vdp*/
        bModuleOn = (HI_TRUE == sg_bRWZBDefaultEnable) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS];
        PQ_MNG_EnableSharpen(bModuleOn);
        PQ_MNG_EnableSharpenDemo(stPqParam.bDemoOnOff[HI_PQ_MODULE_SHARPNESS]);
        (HI_VOID)DRV_PQ_SetSharpness(NUM2LEVEL(stPqParam.u32Sharpness));

        /* set demo display mode*/
        DRV_PQ_SetDemoDispMode(stPqParam.enDemoMode, HI_PQ_MOUDULE_FLAG_VDP);
#endif
    }

    return HI_SUCCESS;
}


/**
 \brief ���ø�ͨ����CSC
 \attention \n
��

 \param[in] enDisplayId:
 \param[in] pstCscMode: ɫ�ʿռ�

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateVdpCSC(HI_PQ_CSC_ID_E enDisplayId, HI_PQ_VDP_CSC_S *pstCscMode)
{
    CSC_MODE_S stCscMode = {HI_FALSE, HAL_CSC_BUTT};

    PQ_CHECK_OVER_RANGE_RE_FAIL(enDisplayId, HI_PQ_VDP_CSC_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstCscMode);

    pqprint(PQ_PRN_CSC, "[%s]: enDisplayId:%d, bCSCEn: %d, enCSC: %d\n",
            __FUNCTION__, enDisplayId, pstCscMode->bCSCEn, pstCscMode->enCSC);

    PQ_MNG_GetCSCMode(enDisplayId, &stCscMode);
    if ((stCscMode.bCSCEn == pstCscMode->bCSCEn)
        && ((HI_PQ_CSC_MODE_E)stCscMode.enCSC == pstCscMode->enCSC))
    {
        return HI_SUCCESS;
    }
    return PQ_MNG_SetCSCMode(enDisplayId, (CSC_MODE_S *)pstCscMode);
}

/**
 \brief ����DCIֱ��ͼͳ�ƴ���
 \attention \n
��

 \param[in] *pstWin;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateDCIWin(HI_PQ_DCI_WIN_S *pstWin, HI_BOOL bDciEnable)
{
    HI_S32 s32Ret  = HI_FAILURE;
#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    HI_BOOL bOnOff = HI_FALSE;
#endif

    PQ_CHECK_NULL_PTR_RE_FAIL(pstWin);

    pqprint(PQ_PRN_DCI, "[%s]: HStar:%d, HEnd: %d, VStar: %d, VEnd:%d, bDciEnable:%d\n",
            __FUNCTION__, pstWin->u16HStar, pstWin->u16HEnd, pstWin->u16VStar,
            pstWin->u16VEnd, bDciEnable);

    memcpy(&(stPqParam.stDciWin), pstWin, sizeof(HI_PQ_DCI_WIN_S));

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    PQ_MNG_GetDCIEnable(&bOnOff);
    s32Ret = PQ_MNG_EnableDCI(bDciEnable && bOnOff);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_MNG_EnableDCI is error!.\n");
        return HI_FAILURE;
    }
#endif
    s32Ret = PQ_MNG_UpdateDCIWin((DCI_WIN_S *)pstWin);

    return s32Ret;
}

/**
 \brief ��ȡCSCϵ��
 \attention \n
��

 \param[in] enCSCMode:
 \param[out] pstCSCCoef:
 \param[out] pstCSCDCCoef:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetCSCCoef(HI_PQ_CSC_MODE_E  enCSCMode, HI_PQ_CSC_COEF_S *pstCSCCoef, HI_PQ_CSC_DCCOEF_S *pstCSCDCCoef)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(enCSCMode, HI_PQ_CSC_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstCSCCoef);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstCSCDCCoef);

    return PQ_MNG_GetCscCoef(enCSCMode, (CSC_COEF_S *)pstCSCCoef, (CSC_DCCOEF_S *)pstCSCDCCoef);
}

/**
 \brief ��ȡ8bit CSCϵ��
 \attention \n
��

 \param[in] enCSCMode:
 \param[out] pstCSCCoef:
 \param[out] pstCSCDCCoef:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_Get8BitCSCCoef(HI_PQ_CSC_MODE_E  enCSCMode, HI_PQ_CSC_COEF_S *pstCSCCoef, HI_PQ_CSC_DCCOEF_S *pstCSCDCCoef)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(enCSCMode, HI_PQ_CSC_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstCSCCoef);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstCSCDCCoef);

    return PQ_MNG_Get8BitCscCoef(enCSCMode, (CSC_COEF_S *)pstCSCCoef, (CSC_DCCOEF_S *)pstCSCDCCoef);
}

HI_S32 DRV_PQ_SetZme(HI_PQ_ZME_LAYER_E enLayerId, HI_PQ_ZME_PARA_IN_S *pstZmePara, HI_BOOL  bFirEnable)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(enLayerId, HI_PQ_DISP_LAYER_ZME_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmePara);

    PQ_MNG_SetVdpZme(enLayerId, (ALG_VZME_DRV_PARA_S *)pstZmePara, bFirEnable);
    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetVpssZme(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_ZME_PARA_IN_S *pstZmePara, HI_BOOL  bFirEnable)
{
    PQ_CHECK_OVER_RANGE_RE_FAIL(enLayerId, HI_PQ_VPSS_LAYER_ZME_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmePara);

    PQ_MNG_SetVpssZme(enLayerId, pstReg, (ALG_VZME_DRV_PARA_S *)pstZmePara, bFirEnable);
    return HI_SUCCESS;
}

/**
 \brief ��ȡSR��ʾģʽ����
 \attention \n
��

 \param[in] ps32Type

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSRMode(HI_S32 *ps32Type)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(ps32Type);

    return PQ_MNG_GetSRDemo(ps32Type);
}

/**
 \brief ����SR��ʾģʽ����
 \attention \n
��

 \param[in] eSRMode: SR��ʾģʽ0-ֻZME;1-�ұ�SR��2-���SR��3-SR��

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSRMode(HI_PQ_SR_DEMO_E eSRMode)
{
    HI_S32 s32Ret;

    PQ_CHECK_OVER_RANGE_RE_FAIL(eSRMode, HI_PQ_SR_DEMO_BUTT);

    s32Ret = PQ_MNG_SetSRDemo(eSRMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("error in setting sr mode!\n");
        return HI_FAILURE;
    }
    pqprint(PQ_PRN_SR, "Set SR mode: %d\n", eSRMode);

    return HI_SUCCESS;
}


/**
 \brief ��ȡWbcInfo��Ϣ
 \attention \n
��

 \param[in]  HI_PQ_WBC_INFO_S* pstWbcInfo

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetWbcInfo(HI_PQ_WBC_INFO_S *pstVpssWbcInfo)
{
    /* Glboal motion */
    MOTION_INPUT_S stMotionInput;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssWbcInfo);

    /* Glboal motion Calc ���ݽ���*/
    stMotionInput.u32HandleNo  = pstVpssWbcInfo->u32HandleNo;
    stMotionInput.u32Height    = pstVpssWbcInfo->u32Height;
    stMotionInput.u32Width     = pstVpssWbcInfo->u32Width;
    stMotionInput.pstMotionReg = pstVpssWbcInfo->pstVPSSWbcReg;
    /* Global Motion After Calc Set AdjustGain to Reg */
    PQ_MNG_GetGlobalMotion(&stMotionInput);

    return HI_SUCCESS;
}




/**
 \brief �����㷨������֮��ļĴ���
 \attention \n
��

 \param[in]  *pstWbcInfo
 \param[out] *pstVpssCfgInfo
 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetAlgCalcCfg(HI_PQ_WBC_INFO_S *pstVpssWbcInfo, HI_PQ_CFG_INFO_S *pstVpssCfgInfo)
{
    /* IFMD */
    PQ_IFMD_CALC_S        stIfmdCalcInfo;
    REG_PLAYBACK_CONFIG_S stIfmdCalcResult = {0};
    /* DB */
    HI_PQ_DB_CALC_INFO_S  stDbCalcInfo = {0};

    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssWbcInfo);
    /********
     * IFMD
     ********/
    if (0 == pstVpssWbcInfo->bProgressive) /* Progressive */
    {
        /* IFMD Calc Info transfer */
        stIfmdCalcInfo.u32HandleNo       = pstVpssWbcInfo->u32HandleNo;
        stIfmdCalcInfo.u32WidthY         = pstVpssWbcInfo->u32Width;
        stIfmdCalcInfo.u32HeightY        = pstVpssWbcInfo->u32Height;
        stIfmdCalcInfo.s32FieldOrder     = pstVpssWbcInfo->s32FieldOrder;
        stIfmdCalcInfo.s32FieldMode      = pstVpssWbcInfo->s32FieldMode;
        stIfmdCalcInfo.u32FrameRate      = pstVpssWbcInfo->u32FrameRate;
        stIfmdCalcInfo.bPreInfo          = pstVpssWbcInfo->bPreInfo;
        stIfmdCalcInfo.pstIfmdHardOutReg = pstVpssWbcInfo->pstVPSSWbcReg;
        memcpy(&(stIfmdCalcInfo.stVdecTranInfo), &(pstVpssWbcInfo->stVdecInfo), sizeof(PQ_VDEC_INFO_S));

        /* FMD After Calc Set CFG Reg to Reg */
        PQ_MNG_IfmdDect(&stIfmdCalcInfo, &stIfmdCalcResult);

        /* fmdCalcResult Tran to Vpss CFG */
        pstVpssCfgInfo->die_reset        = stIfmdCalcResult.die_reset;
        pstVpssCfgInfo->die_stop         = stIfmdCalcResult.die_stop;
        pstVpssCfgInfo->dir_mch          = stIfmdCalcResult.dir_mch;
        pstVpssCfgInfo->die_out_sel      = stIfmdCalcResult.die_out_sel;
        pstVpssCfgInfo->s32FieldOrder    = stIfmdCalcResult.s32FieldOrder;
        pstVpssCfgInfo->s32SceneChanged  = stIfmdCalcResult.s32SceneChanged;
        pstVpssCfgInfo->s32FilmType      = stIfmdCalcResult.s32FilmType;
        pstVpssCfgInfo->u32KeyValue      = stIfmdCalcResult.u32KeyValue;

    }
    /********
     * DBDM
     ********/
    /* DB Clac Info transfer */
    stDbCalcInfo.u32HandleNo     = pstVpssWbcInfo->u32HandleNo;
    stDbCalcInfo.u32Width        = pstVpssWbcInfo->u32Width;
    stDbCalcInfo.u32Height       = pstVpssWbcInfo->u32Height;
    stDbCalcInfo.pstDbCalcWbcReg = pstVpssWbcInfo->pstVPSSWbcReg;

    /* After Calc Tran to Vpss CFG */
    /* DB After Calc Set CFG Reg to Reg; Take effect in Mv410 and HiFone; no practical meaning in 98M*/
    PQ_MNG_DBCalcConfigCfg((DB_CALC_INFO_S *)(&stDbCalcInfo));
    /*  Take effect in Mv410; it does not exist DM Software Alg In HiFone And 98M */
    PQ_MNG_DMCalcConfigCfg((DB_CALC_INFO_S *)(&stDbCalcInfo));

    DRV_PQ_RefreshVpssCfg();

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

    return HI_SUCCESS;
}


/**
 \brief ����FMDģʽ���
 \attention \n
��

 \param[in] pstVPSSReg: VPSS����Ĵ�����ַ

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_PfmdDetect(HI_PQ_PFMD_CALC_S *pstPfmdCalc, HI_PQ_PFMD_PLAYBACK_S *pstPfmdResult)
{
    return HI_SUCCESS;
}


/**
 \brief ��ȡDCIֱ��ͼ
 \attention \n
��

 \param[in] *pstDciHist:0-255

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetDciHistgram(HI_PQ_HISTGRAM_S *pstDciHist)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstDciHist);

    return PQ_HAL_GetDCIHistgram((DCI_HISTGRAM_S *)pstDciHist);
}

static HI_S32 DRV_PQ_GetFlashPqBin(PQ_PARAM_S *pstPqParam)
{
    HI_S32 s32Ret;
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

    //get pq bin from pdm
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
        HI_ERR_PQ( "check PQbin size error, Param Size = %d,sizeof(PQ_PARAM_S) = %d\n", u32CheckSize, sizeof(PQ_PARAM_S));
        return HI_FAILURE;
    }

    if (0 != strncmp(pstPqFileHead->u8Version, PQ_VERSION, strlen(PQ_VERSION)))
    {
        HI_ERR_PQ( "check PQbin Version[%s] error\n", PQ_VERSION);
        return HI_FAILURE;
    }

    if (HI_SUCCESS != DRV_PQ_CheckChipName(pstPqFileHead->u8ChipName))
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
    HI_S32 s32Ret;
    HI_DISP_PARAM_S stSDDispParam;
    HI_DISP_PARAM_S stHDDispParam;
    PDM_EXPORT_FUNC_S *pstPdmFuncs = HI_NULL;

    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_PDM, (HI_VOID **)&pstPdmFuncs);
    if (s32Ret != HI_SUCCESS)
    {
        HI_FATAL_PQ("HI_DRV_MODULE_GetFunction failed!\n");
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

    stPqParam.stSDPictureSetting.u16Brightness = LEVEL2NUM(stSDDispParam.u32Brightness);
    stPqParam.stSDPictureSetting.u16Contrast   = LEVEL2NUM(stSDDispParam.u32Contrast);
    stPqParam.stSDPictureSetting.u16Hue        = LEVEL2NUM(stSDDispParam.u32HuePlus);
    stPqParam.stSDPictureSetting.u16Saturation = LEVEL2NUM(stSDDispParam.u32Saturation);

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

    stPqParam.stHDPictureSetting.u16Brightness = LEVEL2NUM(stHDDispParam.u32Brightness);
    stPqParam.stHDPictureSetting.u16Contrast   = LEVEL2NUM(stHDDispParam.u32Contrast);
    stPqParam.stHDPictureSetting.u16Hue        = LEVEL2NUM(stHDDispParam.u32HuePlus);
    stPqParam.stHDPictureSetting.u16Saturation = LEVEL2NUM(stHDDispParam.u32Saturation);

    stPqParam.stHDVideoSetting.u16Brightness = LEVEL2NUM(stHDDispParam.u32Brightness);
    stPqParam.stHDVideoSetting.u16Contrast   = LEVEL2NUM(stHDDispParam.u32Contrast);
    stPqParam.stHDVideoSetting.u16Hue        = LEVEL2NUM(stHDDispParam.u32HuePlus);
    stPqParam.stHDVideoSetting.u16Saturation = LEVEL2NUM(stHDDispParam.u32Saturation);

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetAcmLuma(HI_PQ_ACM_LUT_S *pstAttr)
{
    HI_S32 s32Ret;
    HI_U32 u32RegCmd;
    PQ_ACM_MODE_S *pstModeLut;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstAttr);
    PQ_CHECK_NULL_PTR_RE_FAIL(g_pstPqParam);

    u32RegCmd = pstAttr->u32LutType;
    pstModeLut = &(g_pstPqParam->stPQCoef.stAcmCoef.stModeLut);

    switch (u32RegCmd)
    {
        case PQ_CMD_VIRTUAL_ACM_RECMD_LUT:
            memcpy(pstModeLut->stModeRecmd.as16Y, pstAttr->as16Lut, sizeof(pstModeLut->stModeRecmd.as16Y));
            break;
        case PQ_CMD_VIRTUAL_ACM_BLUE_LUT:
            memcpy(pstModeLut->stModeBlue.as16Y, pstAttr->as16Lut, sizeof(pstModeLut->stModeBlue.as16Y));
            break;
        case PQ_CMD_VIRTUAL_ACM_GREEN_LUT:
            memcpy(pstModeLut->stModeGreen.as16Y, pstAttr->as16Lut, sizeof(pstModeLut->stModeGreen.as16Y));
            break;
        case PQ_CMD_VIRTUAL_ACM_BG_LUT:
            memcpy(pstModeLut->stModeBG.as16Y, pstAttr->as16Lut, sizeof(pstModeLut->stModeBG.as16Y));
            break;
        case PQ_CMD_VIRTUAL_ACM_FLESH_LUT:
            memcpy(pstModeLut->stModeFleshtone.as16Y, pstAttr->as16Lut, sizeof(pstModeLut->stModeFleshtone.as16Y));
            break;
        case PQ_CMD_VIRTUAL_ACM_6BCOLOR_LUT:
            memcpy(pstModeLut->stMode6BColor.as16Y, pstAttr->as16Lut, sizeof(pstModeLut->stMode6BColor.as16Y));
            break;
        default:
            HI_ERR_PQ("%s:u32RegCmd[0x%x] is error!\n", __FUNCTION__, u32RegCmd);
            break;
    }

    s32Ret = PQ_HAL_SetACMLumaTbl((COLOR_LUT_S *)pstAttr->as16Lut);

    return s32Ret;
}

HI_S32 DRV_PQ_SetAcmHue(HI_PQ_ACM_LUT_S *pstAttr)
{
    HI_S32 s32Ret;
    HI_U32 u32RegCmd;
    PQ_ACM_MODE_S *pstModeLut;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstAttr);
    PQ_CHECK_NULL_PTR_RE_FAIL(g_pstPqParam);

    u32RegCmd = pstAttr->u32LutType;
    pstModeLut = &(g_pstPqParam->stPQCoef.stAcmCoef.stModeLut);

    switch (u32RegCmd)
    {
        case PQ_CMD_VIRTUAL_ACM_RECMD_LUT:
            memcpy(pstModeLut->stModeRecmd.as16H, pstAttr->as16Lut, sizeof(pstModeLut->stModeRecmd.as16H));
            break;
        case PQ_CMD_VIRTUAL_ACM_BLUE_LUT:
            memcpy(pstModeLut->stModeBlue.as16H, pstAttr->as16Lut, sizeof(pstModeLut->stModeBlue.as16H));
            break;
        case PQ_CMD_VIRTUAL_ACM_GREEN_LUT:
            memcpy(pstModeLut->stModeGreen.as16H, pstAttr->as16Lut, sizeof(pstModeLut->stModeGreen.as16H));
            break;
        case PQ_CMD_VIRTUAL_ACM_BG_LUT:
            memcpy(pstModeLut->stModeBG.as16H, pstAttr->as16Lut, sizeof(pstModeLut->stModeBG.as16H));
            break;
        case PQ_CMD_VIRTUAL_ACM_FLESH_LUT:
            memcpy(pstModeLut->stModeFleshtone.as16H, pstAttr->as16Lut, sizeof(pstModeLut->stModeFleshtone.as16H));
            break;
        case PQ_CMD_VIRTUAL_ACM_6BCOLOR_LUT:
            memcpy(pstModeLut->stMode6BColor.as16H, pstAttr->as16Lut, sizeof(pstModeLut->stMode6BColor.as16H));
            break;
        default:
            HI_ERR_PQ("%s:u32RegCmd[0x%x] is error!\n", __FUNCTION__, u32RegCmd);
            break;
    }

    s32Ret = PQ_HAL_SetACMHueTbl((COLOR_LUT_S *)pstAttr->as16Lut);

    return s32Ret;
}

HI_S32 DRV_PQ_SetAcmSat(HI_PQ_ACM_LUT_S *pstAttr)
{
    HI_S32 s32Ret;
    HI_U32 u32RegCmd;
    PQ_ACM_MODE_S *pstModeLut;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstAttr);
    PQ_CHECK_NULL_PTR_RE_FAIL(g_pstPqParam);

    u32RegCmd = pstAttr->u32LutType;
    pstModeLut = &(g_pstPqParam->stPQCoef.stAcmCoef.stModeLut);

    switch (u32RegCmd)
    {
        case PQ_CMD_VIRTUAL_ACM_RECMD_LUT:
            memcpy(pstModeLut->stModeRecmd.as16S, pstAttr->as16Lut, sizeof(pstModeLut->stModeRecmd.as16S));
            break;
        case PQ_CMD_VIRTUAL_ACM_BLUE_LUT:
            memcpy(pstModeLut->stModeBlue.as16S, pstAttr->as16Lut, sizeof(pstModeLut->stModeBlue.as16S));
            break;
        case PQ_CMD_VIRTUAL_ACM_GREEN_LUT:
            memcpy(pstModeLut->stModeGreen.as16S, pstAttr->as16Lut, sizeof(pstModeLut->stModeGreen.as16S));
            break;
        case PQ_CMD_VIRTUAL_ACM_BG_LUT:
            memcpy(pstModeLut->stModeBG.as16S, pstAttr->as16Lut, sizeof(pstModeLut->stModeBG.as16S));
            break;
        case PQ_CMD_VIRTUAL_ACM_FLESH_LUT:
            memcpy(pstModeLut->stModeFleshtone.as16S, pstAttr->as16Lut, sizeof(pstModeLut->stModeFleshtone.as16S));
            break;
        case PQ_CMD_VIRTUAL_ACM_6BCOLOR_LUT:
            memcpy(pstModeLut->stMode6BColor.as16S, pstAttr->as16Lut, sizeof(pstModeLut->stMode6BColor.as16S));
            break;
        default:
            HI_ERR_PQ("%s:u32RegCmd[0x%x] is error!\n", __FUNCTION__, u32RegCmd);
            break;
    }

    s32Ret = PQ_HAL_SetACMSatTbl((COLOR_LUT_S *)pstAttr->as16Lut);

    return s32Ret;
}


HI_S32 DRV_PQ_SetReg(HI_PQ_REGISTER_S *pstAttr)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstAttr);

    return PQ_MNG_SetReg(pstAttr, sg_u32SourceMode, sg_u32OutputMode);
}


HI_S32 DRV_PQ_GetReg(HI_PQ_REGISTER_S *pstAttr)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstAttr);

    return PQ_MNG_GetReg(pstAttr);
}

static HI_S32 DRV_PQ_CheckChipName(HI_CHAR *pchChipName)
{
    HI_S32 s32Ret = HI_FAILURE;
    PQ_CHECK_NULL_PTR_RE_FAIL(pchChipName);

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3716M", strlen("HI_CHIP_TYPE_HI3716M"));
#elif defined(CHIP_TYPE_hi3798mv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3798M", strlen("HI_CHIP_TYPE_HI3798M"));
#elif defined(CHIP_TYPE_hi3796mv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3796M", strlen("HI_CHIP_TYPE_HI3796M"));
#else
    HI_ERR_PQ("unknown Chip Type \r\n");
    return HI_FAILURE;
#endif

    if (0 != s32Ret)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/* You Can Set Demo Pos At MV410; Other Chip is not support */
static HI_S32 DRV_PQ_SetVdpMktCoordinate(HI_U32 u32MktCoordinate)
{
    HI_U32 u32VLayerId  = 0;
    HI_U32 u32VpLayerId = 0;
    PQ_HAL_SetDCIDemoPos(u32VpLayerId, u32MktCoordinate);  /* VP0 */
    PQ_HAL_SetACMDemoPos(u32VpLayerId, u32MktCoordinate);  /* VP0 */
    PQ_HAL_SetSharpDemoPos(u32VLayerId, u32MktCoordinate); /* V0  */

    return HI_SUCCESS;
}

static HI_VOID drv_pq_SetDefaultCSCParam(HI_BOOL bDefault)
{
    HI_PQ_PICTURE_SETTING_S stSDPictureSetting = {50, 50, 50, 50};
    HI_PQ_PICTURE_SETTING_S stHDPictureSetting = {50, 50, 50, 50};
    HI_PQ_PICTURE_SETTING_S stSDVideoSetting   = {50, 50, 50, 50};
    HI_PQ_PICTURE_SETTING_S stHDVideoSetting   = {50, 50, 50, 50};

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
        stSDVideoSetting.u16Brightness   = 50;
        stSDVideoSetting.u16Contrast     = 50;
        stSDVideoSetting.u16Hue          = 50;
        stSDVideoSetting.u16Saturation   = 50;
        stHDVideoSetting.u16Brightness   = 50;
        stHDVideoSetting.u16Contrast     = 50;
        stHDVideoSetting.u16Hue          = 50;
        stHDVideoSetting.u16Saturation   = 50;
    }
    else
    {
        stSDPictureSetting.u16Brightness = NUM2LEVEL(stPqParam.stSDPictureSetting.u16Brightness);
        stSDPictureSetting.u16Contrast   = NUM2LEVEL(stPqParam.stSDPictureSetting.u16Contrast);
        stSDPictureSetting.u16Hue        = NUM2LEVEL(stPqParam.stSDPictureSetting.u16Hue);
        stSDPictureSetting.u16Saturation = NUM2LEVEL(stPqParam.stSDPictureSetting.u16Saturation);
        stHDPictureSetting.u16Brightness = NUM2LEVEL(stPqParam.stHDPictureSetting.u16Brightness);
        stHDPictureSetting.u16Contrast   = NUM2LEVEL(stPqParam.stHDPictureSetting.u16Contrast);
        stHDPictureSetting.u16Hue        = NUM2LEVEL(stPqParam.stHDPictureSetting.u16Hue);
        stHDPictureSetting.u16Saturation = NUM2LEVEL(stPqParam.stHDPictureSetting.u16Saturation);

        stSDVideoSetting.u16Brightness   = NUM2LEVEL(stPqParam.stSDVideoSetting.u16Brightness);
        stSDVideoSetting.u16Contrast     = NUM2LEVEL(stPqParam.stSDVideoSetting.u16Contrast);
        stSDVideoSetting.u16Hue          = NUM2LEVEL(stPqParam.stSDVideoSetting.u16Hue);
        stSDVideoSetting.u16Saturation   = NUM2LEVEL(stPqParam.stSDVideoSetting.u16Saturation);
        stHDVideoSetting.u16Brightness   = NUM2LEVEL(stPqParam.stHDVideoSetting.u16Brightness);
        stHDVideoSetting.u16Contrast     = NUM2LEVEL(stPqParam.stHDVideoSetting.u16Contrast);
        stHDVideoSetting.u16Hue          = NUM2LEVEL(stPqParam.stHDVideoSetting.u16Hue);
        stHDVideoSetting.u16Saturation   = NUM2LEVEL(stPqParam.stHDVideoSetting.u16Saturation );
    }
    DRV_PQ_SetSDBrightness    (stSDPictureSetting.u16Brightness);
    DRV_PQ_SetSDContrast      (stSDPictureSetting.u16Contrast);
    DRV_PQ_SetSDHue           (stSDPictureSetting.u16Hue);
    DRV_PQ_SetSDSaturation    (stSDPictureSetting.u16Saturation);
    DRV_PQ_SetHDBrightness    (stHDPictureSetting.u16Brightness);
    DRV_PQ_SetHDContrast      (stHDPictureSetting.u16Contrast);
    DRV_PQ_SetHDHue           (stHDPictureSetting.u16Hue);
    DRV_PQ_SetHDSaturation    (stHDPictureSetting.u16Saturation);

    return;
}

static HI_VOID drv_pq_SetDefaultAlgParam(HI_BOOL bDefault)
{
    HI_BOOL bModuleOn = HI_FALSE;
    bModuleOn = (HI_TRUE == bDefault) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS];
    DRV_PQ_SetPQModule(HI_PQ_MODULE_SHARPNESS, bModuleOn);
    bModuleOn = (HI_TRUE == bDefault) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_DCI];
    DRV_PQ_SetPQModule(HI_PQ_MODULE_DCI,       bModuleOn);
    bModuleOn = (HI_TRUE == bDefault) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_COLOR];
    DRV_PQ_SetPQModule(HI_PQ_MODULE_COLOR,     bModuleOn);

#if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    bModuleOn = (HI_TRUE == bDefault) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_TNR];
    DRV_PQ_SetPQModule(HI_PQ_MODULE_TNR,       bModuleOn);
    bModuleOn = (HI_TRUE == bDefault) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_DB];
    DRV_PQ_SetPQModule(HI_PQ_MODULE_DB,        bModuleOn);
    bModuleOn = (HI_TRUE == bDefault) ? HI_FALSE : stPqParam.bModuleOnOff[HI_PQ_MODULE_DM];
    DRV_PQ_SetPQModule(HI_PQ_MODULE_DM,        bModuleOn);
#endif

    return;
}

static HI_VOID drv_pq_SetDefaultZmeParam(HI_BOOL bDefault)
{

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)  
    DRV_PQ_SetPQModule(HI_PQ_MODULE_SR,  bDefault);
#elif defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    PQ_MNG_SetZmeDefault(bDefault);
#endif

    return;
}

HI_S32 DRV_PQ_SetDefaultParam(HI_BOOL bDefault)
{
    sg_bRWZBDefaultEnable = bDefault;
    drv_pq_SetDefaultCSCParam(bDefault);
    drv_pq_SetDefaultAlgParam(bDefault);
    drv_pq_SetDefaultZmeParam(bDefault);
    //DRV_PQ_SetDemoMode(HI_PQ_MODULE_ALL, HI_FALSE);

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetDefaultParam(HI_BOOL *pbDefault)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbDefault);

    *pbDefault = sg_bRWZBDefaultEnable;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_ProcRead(struct seq_file *s, HI_VOID *data)
{
#ifdef PQ_PROC_CTRL_SUPPORT
    PQ_PROC_INFO_S stProcInfo;
    HI_PQ_IFMD_PLAYBACK_S stIfmdInfo;
    HI_BOOL bDefault    = HI_FALSE;
    HI_U32 u32ProcDeiMDLum = 0;

    memset(&stProcInfo, 0, sizeof(stProcInfo));
    memset(&stIfmdInfo, 0, sizeof(stIfmdInfo));

    /* DEI And Fmd */
    PQ_HAL_GetDeiEn(0, &(stProcInfo.bDeiEn));
    PQ_MNG_GetGlobMotiGain(&(stProcInfo.u32DeiGloblGain));
    PQ_MNG_GetIfmdDectInfo((REG_PLAYBACK_CONFIG_S *)(&stIfmdInfo));
    stProcInfo.u32DeiOutSel     = stIfmdInfo.die_out_sel;
    stProcInfo.s32DeiDirMch     = stIfmdInfo.dir_mch;
    stProcInfo.s32DeiFieldOrder = stIfmdInfo.s32FieldOrder;
    stProcInfo.u32DeiEdgeSmEn   = stIfmdInfo.u32EdgeSmoothEn;
    /* Zme */
    PQ_MNG_GetVdpZmeFirEn(&(stProcInfo.bVdpZmeFirEn));
    PQ_MNG_GetVdpZmeMedEn(&(stProcInfo.bVdpZmeMedEn));
    PQ_MNG_GetVpssZmeFirEn(&(stProcInfo.bVpssZmeFirEn));
    PQ_MNG_GetVpssZmeMedEn(&(stProcInfo.bVdpZmeMedEn));

    /* Dci */
    PQ_HAL_GetDCIWindow(&(stProcInfo.u16DciHStart), &(stProcInfo.u16DciHEnd), &(stProcInfo.u16DciVStart), &(stProcInfo.u16DciVEnd));
    PQ_HAL_GetDCIlevel(VDP_LAYER_VP0, &(stProcInfo.u16DciGain0), &(stProcInfo.u16DciGain1), &(stProcInfo.u16DciGain2));
    PQ_MNG_GetDCILevelGain(&stProcInfo.u32DciLevelGain);

    /* Acm */
    PQ_HAL_GetACMGain(VDP_LAYER_VP0, &(stProcInfo.u32AcmLumaGain), &(stProcInfo.u32AcmHueGain), &(stProcInfo.u32AcmSatGain));
    PQ_MNG_GetColorEnhanceMode(&(stProcInfo.u32ColorMode));/* prinrk Word, Not Number(Use enum) */
    PQ_MNG_GetFleshToneLevel(&(stProcInfo.u32FleshStr));

    /* DBDM/DBDR */
    DRV_PQ_GetPQModule(HI_PQ_MODULE_DB, &(stProcInfo.bDbEn));
    DRV_PQ_GetPQModule(HI_PQ_MODULE_DM, &(stProcInfo.bDmEn));

    /* SR */
    DRV_PQ_GetPQModule(HI_PQ_MODULE_SR, &(stProcInfo.bSrEn));
    PQ_HAL_GetSRSharpStr(VDP_LAYER_VID0, &(stProcInfo.u32SrSharpStr));
    DRV_PQ_GetSRMode(&(stProcInfo.u32SrMode));/* prinrk Word, Not Number(Use enum) */

    /* Dither */
    PQ_HAL_GetVpssDitherEn(0, &(stProcInfo.bVpssDithEn));
    PQ_HAL_GetDnrDitherEn(0, &(stProcInfo.bDnrDithEn));
    PQ_HAL_GetVdpDitherEn(&(stProcInfo.bVdpDithEn));

    /* CSC */
    PQ_MNG_GetCSCMode(HAL_DISP_LAYER_V0, &stProcInfo.stCSC[HAL_DISP_LAYER_V0]);
    PQ_MNG_GetCSCMode(HAL_DISP_LAYER_V1, &stProcInfo.stCSC[HAL_DISP_LAYER_V1]);
    PQ_MNG_GetCSCMode(HAL_DISP_LAYER_V2, &stProcInfo.stCSC[HAL_DISP_LAYER_V2]);
    PQ_MNG_GetCSCMode(HAL_DISP_LAYER_V3, &stProcInfo.stCSC[HAL_DISP_LAYER_V3]);
    PQ_MNG_GetCSCMode(HAL_DISP_LAYER_V4, &stProcInfo.stCSC[HAL_DISP_LAYER_V4]);

    DRV_PQ_GetDefaultParam(&bDefault);

    u32ProcDeiMDLum = PQ_MNG_GetDeiMdLum();

    PROC_PRINT(s, "================================ PQ Bin Information =================================\n");
    PROC_PRINT(s, "%-20s: %s %s\n", "Driver version", "PQ_V3_0"PQ_MODIFY_TIME, "[Build Time:"__DATE__", "__TIME__"]");
    PROC_PRINT(s, "%-20s: %s\n", "PQ Bin version", PQ_VERSION);
    PROC_PRINT(s, "%-20s: %d\n", "PQ Bin size", sizeof(PQ_PARAM_S));

    if (HI_FALSE == g_bLoadPqBin)
    {
        PROC_PRINT(s, "%-20s: failure\n", "PQ Bin Load");
    }
    else
    {
        PROC_PRINT(s, "%-20s: success\n", "PQ Bin Load");
        PROC_PRINT(s, "%-20s: %s\n", "PQ Bin version", g_pstPqParam->stPQFileHeader.u8Version);
        PROC_PRINT(s, "%-20s: %s\n", "PQ Bin chipname", g_pstPqParam->stPQFileHeader.u8ChipName);
        PROC_PRINT(s, "%-20s: %s\n", "PQ Bin SDK version", g_pstPqParam->stPQFileHeader.u8SDKVersion);
        PROC_PRINT(s, "%-20s: %s\n", "PQ Bin author", g_pstPqParam->stPQFileHeader.u8Author);
        PROC_PRINT(s, "%-20s: %s\n", "PQ Bin describe", g_pstPqParam->stPQFileHeader.u8Desc);
        PROC_PRINT(s, "%-20s: %s\n", "PQ Bin time", g_pstPqParam->stPQFileHeader.u8Time);
    }

    PROC_PRINT(s, "================================ Picture Information ================================\n");
    PROC_PRINT(s, "%-20s: %-20d",   "HD brightness",    NUM2LEVEL(stPqParam.stHDPictureSetting.u16Brightness));
    PROC_PRINT(s, "%-20s: %-20d\n", "SD brightness",    NUM2LEVEL(stPqParam.stSDPictureSetting.u16Brightness));
    PROC_PRINT(s, "%-20s: %-20d",   "HD contrast",      NUM2LEVEL(stPqParam.stHDPictureSetting.u16Contrast));
    PROC_PRINT(s, "%-20s: %-20d\n", "SD contrast",      NUM2LEVEL(stPqParam.stSDPictureSetting.u16Contrast));
    PROC_PRINT(s, "%-20s: %-20d",   "HD hue",           NUM2LEVEL(stPqParam.stHDPictureSetting.u16Hue));
    PROC_PRINT(s, "%-20s: %-20d\n", "SD hue",           NUM2LEVEL(stPqParam.stSDPictureSetting.u16Hue));
    PROC_PRINT(s, "%-20s: %-20d",   "HD saturation",    NUM2LEVEL(stPqParam.stHDPictureSetting.u16Saturation));
    PROC_PRINT(s, "%-20s: %-20d\n", "SD saturation",    NUM2LEVEL(stPqParam.stSDPictureSetting.u16Saturation));

    PROC_PRINT(s, "%-20s: %d\n", "sharpness", NUM2LEVEL(stPqParam.u32Sharpness));
    PROC_PRINT(s, "%-20s: %d\n", "DCI gain",  stProcInfo.u32DciLevelGain);

    PQ_CHECK_OVER_RANGE_RE_FAIL(stProcInfo.u32FleshStr, FLE_GAIN_BUTT);
    PROC_PRINT(s, "%-20s: %s\n", "flesh tone level", g_pPQProcFleshTone[stProcInfo.u32FleshStr]);
    PROC_PRINT(s, "%-20s: %s (%d*%d)\n", "source",   g_pPQProcSourceType[sg_u32SourceMode], sg_u32ImageWidth, sg_u32ImageHeight);
    PROC_PRINT(s, "%-20s: %s (%d*%d)\n", "output",   g_pPQProcSourceType[sg_u32OutputMode], sg_u32OutWidth, sg_u32OutHeight);
    PROC_PRINT(s, "%-20s: %-20s\n", "RWZB Default", bDefault ? "on" : "off");

    PROC_PRINT(s, "================================ Algorithm Information ==============================\n");
    PROC_PRINT(s, "-------------------------------------- DEI/FMD ------------------------------------\n");
    PROC_PRINT(s, "%-20s: %-20s",   "module",           stProcInfo.bDeiEn ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s\n", "demo",             stPqParam.bDemoOnOff[HI_PQ_MODULE_DEI] ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s",   "fir/copy mode",    stProcInfo.u32DeiOutSel ? "copy" : "fir");
    PROC_PRINT(s, "%-20s: %-20d\n", "global motion gain", stProcInfo.u32DeiGloblGain);
    PROC_PRINT(s, "%-20s: %-20d",   "dir mch",          stProcInfo.s32DeiDirMch);
    PROC_PRINT(s, "%-20s: %-20s\n", "field order",      stProcInfo.s32DeiFieldOrder ? "bottom first" : "top first");
    PROC_PRINT(s, "%-20s: %-20s",   "edge smooth",      stProcInfo.u32DeiEdgeSmEn   ? "enable"       : "disable");

    PQ_CHECK_OVER_RANGE_RE_FAIL(u32ProcDeiMDLum, ALG_DEI_MODE_BUTT);
    PROC_PRINT(s, "%-20s: %-20s\n", "field mode", g_pPQProcFldMode[(ALG_DEI_MODE_E)u32ProcDeiMDLum]);

    PROC_PRINT(s, "--------------------------------------- ZME ---------------------------------------\n");
    PROC_PRINT(s, "%-20s: %-20s",   "vpss fir/copy mode",   stProcInfo.bVpssZmeFirEn ? "fir" : "copy");
    PROC_PRINT(s, "%-20s: %-20s\n", "vpss med enable",      stProcInfo.bVpssZmeMedEn ? "on"  : "off");
    PROC_PRINT(s, "%-20s: %-20s",   "vdp  fir/copy mode",   stProcInfo.bVdpZmeFirEn  ? "fir" : "copy");
    PROC_PRINT(s, "%-20s: %-20s\n", "vdp  med enable",      stProcInfo.bVdpZmeMedEn  ? "on"  : "off");

    PROC_PRINT(s, "--------------------------------------- DCI ---------------------------------------\n");
    PROC_PRINT(s, "%-20s: %-20s",   "module",   stPqParam.bModuleOnOff[HI_PQ_MODULE_DCI] ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s\n", "demo",     stPqParam.bDemoOnOff[HI_PQ_MODULE_DCI]   ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20d",   "h start",  stProcInfo.u16DciHStart);
    PROC_PRINT(s, "%-20s: %-20d\n", "h end",    stProcInfo.u16DciHEnd);
    PROC_PRINT(s, "%-20s: %-20d",   "v start",  stProcInfo.u16DciVStart);
    PROC_PRINT(s, "%-20s: %-20d\n", "v end",    stProcInfo.u16DciVEnd);
    PROC_PRINT(s, "%-20s: %-20d",   "gain 0",   stProcInfo.u16DciGain0);
    PROC_PRINT(s, "%-20s: %-20d\n", "gain 1",   stProcInfo.u16DciGain1);
    PROC_PRINT(s, "%-20s: %-20d",   "gain 2",   stProcInfo.u16DciGain2);
    PROC_PRINT(s, "%-40s\n", "");

    PROC_PRINT(s, "-------------------------------------- DBDM ---------------------------------------\n");
    PROC_PRINT(s, "%-20s: %-20s",   "DB module",    stPqParam.bModuleOnOff[HI_PQ_MODULE_DB] ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s\n", "demo",         stPqParam.bDemoOnOff[HI_PQ_MODULE_DB]   ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s",   "DM module",    stPqParam.bModuleOnOff[HI_PQ_MODULE_DM] ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s\n", "demo",         stPqParam.bDemoOnOff[HI_PQ_MODULE_DM]   ? "on" : "off");

    PROC_PRINT(s, "--------------------------------------- ACM ---------------------------------------\n");
    PROC_PRINT(s, "%-20s: %-20s",   "module",       stPqParam.bModuleOnOff[HI_PQ_MODULE_COLOR] ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s\n", "demo",         stPqParam.bDemoOnOff[HI_PQ_MODULE_COLOR]   ? "on" : "off");

    PQ_CHECK_OVER_RANGE_RE_FAIL(stProcInfo.u32ColorMode, COLOR_MODE_BUTT);
    PROC_PRINT(s, "%-20s: %-20s",   "enhance mode", g_pPQProcEnhanceMode[stProcInfo.u32ColorMode]);
    PROC_PRINT(s, "%-20s: %-20d\n", "luma gain",    stProcInfo.u32AcmLumaGain);
    PROC_PRINT(s, "%-20s: %-20d",   "hue gain",     stProcInfo.u32AcmHueGain);
    PROC_PRINT(s, "%-20s: %-20d\n", "sat gain",     stProcInfo.u32AcmSatGain);

    PROC_PRINT(s, "--------------------------------------- SR ----------------------------------------\n");
    PROC_PRINT(s, "%-20s: %-20s",   "module",   stPqParam.bModuleOnOff[HI_PQ_MODULE_SR] ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s\n", "demo",     stPqParam.bDemoOnOff[HI_PQ_MODULE_SR] ? "on" : "off");

    PQ_CHECK_OVER_RANGE_RE_FAIL(stProcInfo.u32SrMode, SR_DEMO_BUTT);
    PROC_PRINT(s, "%-20s: %-20s",   "SR demo mode",     g_pPQProcSRDemoMode[stProcInfo.u32SrMode]);
    PROC_PRINT(s, "%-20s: %-20d\n", "sharp strength",   stProcInfo.u32SrSharpStr);

    PROC_PRINT(s, "-------------------------------------- Sharpn -------------------------------------\n");
    PROC_PRINT(s, "%-20s: %-20s",   "module", stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS] ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s\n", "demo", stPqParam.bDemoOnOff[HI_PQ_MODULE_SHARPNESS] ? "on" : "off");

    PROC_PRINT(s, "--------------------------------------- CSC ---------------------------------------\n");
    PROC_PRINT(s, "%-10s: %-20s",   "V0 enable", stProcInfo.stCSC[HAL_DISP_LAYER_V0].bCSCEn  ? "on" : "off");

    PQ_CHECK_OVER_RANGE_RE_FAIL(stProcInfo.stCSC[HAL_DISP_LAYER_V0].enCSC, HAL_CSC_BUTT + 1);
    PROC_PRINT(s, "%-10s: %-40s\n", "CSC mode",  g_pPQProcCSC[stProcInfo.stCSC[HAL_DISP_LAYER_V0].enCSC]);

    PROC_PRINT(s, "%-10s: %-20s",   "V1 enable", stProcInfo.stCSC[HAL_DISP_LAYER_V1].bCSCEn  ? "on" : "off");
    PQ_CHECK_OVER_RANGE_RE_FAIL(stProcInfo.stCSC[HAL_DISP_LAYER_V1].enCSC, HAL_CSC_BUTT + 1);
    PROC_PRINT(s, "%-10s: %-40s\n", "CSC mode",  g_pPQProcCSC[stProcInfo.stCSC[HAL_DISP_LAYER_V1].enCSC]);

    PROC_PRINT(s, "%-10s: %-20s",   "V2 enable", stProcInfo.stCSC[HAL_DISP_LAYER_V2].bCSCEn  ? "on" : "off");
    PQ_CHECK_OVER_RANGE_RE_FAIL(stProcInfo.stCSC[HAL_DISP_LAYER_V2].enCSC, HAL_CSC_BUTT + 1);
    PROC_PRINT(s, "%-10s: %-40s\n", "CSC mode",  g_pPQProcCSC[stProcInfo.stCSC[HAL_DISP_LAYER_V2].enCSC]);

    PROC_PRINT(s, "%-10s: %-20s",   "V3 enable", stProcInfo.stCSC[HAL_DISP_LAYER_V3].bCSCEn  ? "on" : "off");
    PQ_CHECK_OVER_RANGE_RE_FAIL(stProcInfo.stCSC[HAL_DISP_LAYER_V3].enCSC, HAL_CSC_BUTT + 1);
    PROC_PRINT(s, "%-10s: %-40s\n", "CSC mode",  g_pPQProcCSC[stProcInfo.stCSC[HAL_DISP_LAYER_V3].enCSC]);

    PROC_PRINT(s, "%-10s: %-20s",   "V4 Enable", stProcInfo.stCSC[HAL_DISP_LAYER_V4].bCSCEn  ? "on" : "off");
    PQ_CHECK_OVER_RANGE_RE_FAIL(stProcInfo.stCSC[HAL_DISP_LAYER_V4].enCSC, HAL_CSC_BUTT + 1);
    PROC_PRINT(s, "%-10s: %-40s\n", "CSC mode",  g_pPQProcCSC[stProcInfo.stCSC[HAL_DISP_LAYER_V4].enCSC]);

    PROC_PRINT(s, "--------------------------------------- TNR ---------------------------------------\n");
    PROC_PRINT(s, "%-20s: %-20s",   "module",    stPqParam.bModuleOnOff[HI_PQ_MODULE_TNR] ? "on" : "off");
    PROC_PRINT(s, "%-20s: %-20s\n", "demo",      stPqParam.bDemoOnOff[HI_PQ_MODULE_TNR] ? "on" : "off");

    PROC_PRINT(s, "-------------------------------------- Dither -------------------------------------\n");
    PROC_PRINT(s, "%-20s: %-20s",   "DNR dither",  stProcInfo.bDnrDithEn   ? "enable" : "disable");
    PROC_PRINT(s, "%-20s: %-20s\n", "vpss dither", stProcInfo.bVpssDithEn  ? "enable" : "disable");
    PROC_PRINT(s, "%-20s: %-20s",   "vdp dither",  stProcInfo.bVdpDithEn   ? "enable" : "disable");
    PROC_PRINT(s, "%-40s\n", "");

    PROC_PRINT(s, "=====================================================================================\n");

#endif
    return HI_SUCCESS;
}

static HI_VOID DRV_PQ_ProcPrintHelp(HI_VOID)
{
#ifdef PQ_PROC_CTRL_SUPPORT

    HI_DRV_PROC_EchoHelper("\n");
    HI_DRV_PROC_EchoHelper("help message:\n");
    HI_DRV_PROC_EchoHelper("echo help                               > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo tunmode    normal/debug            > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo rwzbdefault on/off                 > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo printbin   <hex>/all/multi         > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo printtype  <hex>                   > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo bright     <0~100>                 > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo contrast   <0~100>                 > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo hue        <0~100>                 > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo satu       <0~100>                 > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo sharp      <0~100>                 > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo dci        <0~63>                  > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo color      <0~1023>                > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo fleshtone  off/low/mid/high             > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo colormode  blue/green/bg/optimal        > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo deimode    auto/fir/copy                > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo fodmode    auto/top1st/bottom1st        > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo ds         flat/medfir                  > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo vpsszme/vdpzme  fir/copy/medon/medoff   > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo sharp/dci/acm/sr/tnr/db/dm/vpss/vdp/all    enable/disable   > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo sharp/dci/acm/sr/tnr/db/dm/dei/all         demoon/demooff   > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("\n");

#endif
}

static HI_S32 DRV_PQ_ProcParsePara(HI_CHAR *pProcPara, HI_CHAR **ppArg1, HI_CHAR **ppArg2)
{
    HI_CHAR *pChar = HI_NULL;

    if (strlen(pProcPara) == 0)
    {
        /* not fined arg1 and arg2, return failed */
        *ppArg1  = HI_NULL;
        *ppArg2  = HI_NULL;
        return HI_FAILURE;
    }

    /* find arg1 */
    pChar = pProcPara;
    while ( (*pChar == ' ') && (*pChar != '\0') )
    {
        pChar++;
    }

    if (*pChar != '\0')
    {
        *ppArg1 = pChar;
    }
    else
    {
        *ppArg1  = HI_NULL;

        return HI_FAILURE;
    }

    /* ignor arg1 */
    while ( (*pChar != ' ') && (*pChar != '\0') )
    {
        pChar++;
    }

    /* Not find arg2, return */
    if (*pChar == '\0')
    {
        *ppArg2 = HI_NULL;

        return HI_SUCCESS;
    }

    /* add '\0' for arg1 */
    *pChar = '\0';

    /* start to find arg2 */
    pChar = pChar + 1;
    while ( (*pChar == ' ') && (*pChar != '\0') )
    {
        pChar++;
    }

    if (*pChar != '\0')
    {
        *ppArg2 = pChar;
    }
    else
    {
        *ppArg2 = HI_NULL;
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_PQ_ProcCmdProcee(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Index = 0;
    HI_U32 u32MaxFuncIndex = sizeof(g_stPQProcInfo) / sizeof(PQ_PROC_FUN_S);

    if ((pArg1 == HI_NULL) || (pArg2 == HI_NULL) )
    {
        return HI_FAILURE;
    }

    for (u32Index = 0; u32Index < u32MaxFuncIndex; u32Index++)
    {
        if (0 == HI_OSAL_Strncmp(pArg1, g_stPQProcInfo[u32Index].pFuncName, strlen("g_stPQProcInfo[u32Index].pFuncName")))
        {
            return g_stPQProcInfo[u32Index].pfnProc(pArg1, pArg2);
        }
    }

    return HI_FAILURE;
}

HI_S32 DRV_PQ_ProcWrite(struct file *file,
                        const char __user *buf, size_t count, loff_t *ppos)
{
    HI_S32 s32Ret;
    HI_CHAR u8PQProcBuffer[256];
    HI_CHAR *pArg1, *pArg2;

    if (count >= sizeof(u8PQProcBuffer))
    {
        HI_ERR_PQ("your parameter string is too long!\n");
        return HI_FAILURE;
    }

    PQ_CHECK_NULL_PTR_RE_FAIL(buf);

    memset(u8PQProcBuffer, 0, sizeof(u8PQProcBuffer));
    if (copy_from_user(u8PQProcBuffer, buf, count))
    {
        HI_ERR_PQ("MMZ: copy_from_user failed!\n");
        return HI_FAILURE;
    }
    u8PQProcBuffer[count] = 0;

    s32Ret = DRV_PQ_ProcParsePara(u8PQProcBuffer, &pArg1, &pArg2);

    if (0 == HI_OSAL_Strncmp(pArg1, "help", strlen("help")))
    {
        DRV_PQ_ProcPrintHelp();
        return count;
    }

    if ((s32Ret != HI_SUCCESS) || (pArg2 == HI_NULL))
    {
        DRV_PQ_ProcPrintHelp();
        HI_ERR_PQ("proc cmd procee failed!\n");

        return count;
    }

    s32Ret = DRV_PQ_ProcCmdProcee(pArg1, pArg2);
    if (s32Ret != HI_SUCCESS)
    {
        DRV_PQ_ProcPrintHelp();
        HI_ERR_PQ("proc cmd procee failed!\n");
    }

    return count;
}

static HI_S32 drv_pq_ProcSetBrightness(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = (HI_U32)simple_strtol(pArg2, NULL, 10);

    DRV_PQ_SetSDBrightness(u32Data);
    DRV_PQ_SetHDBrightness(u32Data);

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetContrast(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = (HI_U32)simple_strtol(pArg2, NULL, 10);

    DRV_PQ_SetSDContrast(u32Data);
    DRV_PQ_SetHDContrast(u32Data);

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetHue(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = (HI_U32)simple_strtol(pArg2, NULL, 10);

    DRV_PQ_SetSDHue(u32Data);
    DRV_PQ_SetHDHue(u32Data);

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetSaturation(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = (HI_U32)simple_strtol(pArg2, NULL, 10);

    DRV_PQ_SetSDSaturation(u32Data);
    DRV_PQ_SetHDSaturation(u32Data);

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetDB(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DB, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DB, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demoon", strlen("demoon")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_DB, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demooff", strlen("demooff")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_DB, HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetDM(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DM, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DM, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demoon", strlen("demoon")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_DM, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demooff", strlen("demooff")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_DM, HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetFleshTone(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_PQ_FLESHTONE_E enFleshToneLevel;

    if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        enFleshToneLevel = HI_PQ_FLESHTONE_GAIN_OFF;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "low", strlen("low")))
    {
        enFleshToneLevel = HI_PQ_FLESHTONE_GAIN_LOW;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "mid", strlen("mid")))
    {
        enFleshToneLevel = HI_PQ_FLESHTONE_GAIN_MID;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "high", strlen("high")))
    {
        enFleshToneLevel = HI_PQ_FLESHTONE_GAIN_HIGH;
    }
    else
    {
        return HI_FAILURE;
    }

    return DRV_PQ_SetFleshToneLevel(enFleshToneLevel);
}

static HI_S32 drv_pq_ProcSetColorMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode;

    if (0 == HI_OSAL_Strncmp(pArg2, "blue", strlen("blue")))
    {
        enColorSpecMode = HI_PQ_COLOR_MODE_BLUE;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "green", strlen("green")))
    {
        enColorSpecMode = HI_PQ_COLOR_MODE_GREEN;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "bg", strlen("bg")))
    {
        enColorSpecMode = HI_PQ_COLOR_MODE_BG;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "optimal", strlen("optimal")))
    {
        enColorSpecMode = HI_PQ_COLOR_MODE_RECOMMEND;
    }
    else
    {
        return HI_FAILURE;
    }

    return DRV_PQ_SetColorEnhanceMode(enColorSpecMode);
}

static HI_S32 drv_pq_ProcSetSharp(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        s32Ret = DRV_PQ_SetPQModule(HI_PQ_MODULE_SHARPNESS, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        s32Ret = DRV_PQ_SetPQModule(HI_PQ_MODULE_SHARPNESS, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demoon", strlen("demoon")))
    {
        s32Ret = DRV_PQ_SetDemoMode(HI_PQ_MODULE_SHARPNESS, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demooff", strlen("demooff")))
    {
        s32Ret = DRV_PQ_SetDemoMode(HI_PQ_MODULE_SHARPNESS, HI_FALSE);
    }
    else
    {
        u32Data = (HI_U32)simple_strtol(pArg2, NULL, 10);
        s32Ret = DRV_PQ_SetSharpness(u32Data);
    }

    return s32Ret;
}

static HI_S32 drv_pq_ProcSetDCI(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        s32Ret = DRV_PQ_SetPQModule(HI_PQ_MODULE_DCI, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        s32Ret = DRV_PQ_SetPQModule(HI_PQ_MODULE_DCI, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demoon", strlen("demoon")))
    {
        s32Ret = DRV_PQ_SetDemoMode(HI_PQ_MODULE_DCI, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demooff", strlen("demooff")))
    {
        s32Ret = DRV_PQ_SetDemoMode(HI_PQ_MODULE_DCI, HI_FALSE);
    }
    else
    {
        u32Data = (HI_U32)simple_strtol(pArg2, NULL, 10);
        PQ_HAL_SetDCIlevel(VDP_LAYER_VP0, u32Data, u32Data, u32Data);

        return HI_SUCCESS;
    }

    return s32Ret;
}

static HI_S32 drv_pq_ProcSetACM(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        s32Ret = DRV_PQ_SetPQModule(HI_PQ_MODULE_COLOR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        s32Ret = DRV_PQ_SetPQModule(HI_PQ_MODULE_COLOR, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demoon", strlen("demoon")))
    {
        s32Ret = DRV_PQ_SetDemoMode(HI_PQ_MODULE_COLOR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demooff", strlen("demooff")))
    {
        s32Ret = DRV_PQ_SetDemoMode(HI_PQ_MODULE_COLOR, HI_FALSE);
    }
    else
    {
        u32Data = (HI_U32)simple_strtol(pArg2, NULL, 10);
        PQ_HAL_SetACMGain(VDP_LAYER_VP0, u32Data, u32Data, u32Data);

        return HI_SUCCESS;
    }

    return s32Ret;
}

static HI_S32 drv_pq_ProcSetSR(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_SR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_SR, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demoon", strlen("demoon")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_SR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demooff", strlen("demooff")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_SR, HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetTNR(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_TNR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_TNR, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demoon", strlen("demoon")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_TNR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demooff", strlen("demooff")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_TNR, HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetVPSS(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DB,  HI_TRUE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DM,  HI_TRUE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_TNR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DB,  HI_FALSE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DM,  HI_FALSE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_TNR, HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetAll(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_SHARPNESS, HI_TRUE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DCI, HI_TRUE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_COLOR, HI_TRUE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_SR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_SHARPNESS, HI_FALSE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_DCI, HI_FALSE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_COLOR, HI_FALSE);
        DRV_PQ_SetPQModule(HI_PQ_MODULE_SR, HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetVDP(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_ALL, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        DRV_PQ_SetPQModule(HI_PQ_MODULE_ALL, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demoon", strlen("demoon")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_ALL, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demooff", strlen("demooff")))
    {
        DRV_PQ_SetDemoMode(HI_PQ_MODULE_ALL, HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetDeiMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "auto", strlen("auto")))
    {
        PQ_MNG_SetDieOutMode(DIE_OUT_MODE_AUTO);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "fir", strlen("fir")))
    {
        PQ_MNG_SetDieOutMode(DIE_OUT_MODE_FIR);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "copy", strlen("copy")))
    {
        PQ_MNG_SetDieOutMode(DIE_OUT_MODE_COPY);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetVpssZme(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "fir", strlen("fir")))
    {
        PQ_MNG_SetVpssZmeFirEn(HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "copy", strlen("copy")))
    {
        PQ_MNG_SetVpssZmeFirEn(HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "medon", strlen("medon")))
    {
        PQ_MNG_SetVpssZmeMedEn(HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "medoff", strlen("medoff")))
    {
        PQ_MNG_SetVpssZmeMedEn(HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetVdpZme(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "fir", strlen("fir")))
    {
        PQ_MNG_SetVdpZmeFirEn(HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "copy", strlen("copy")))
    {
        PQ_MNG_SetVdpZmeFirEn(HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "medon", strlen("medon")))
    {
        PQ_MNG_SetVdpZmeMedEn(HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "medoff", strlen("medoff")))
    {
        PQ_MNG_SetVdpZmeMedEn(HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetFodMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "auto", strlen("auto")))
    {
        PQ_MNG_SetFodMode(PQ_FOD_ENABLE_AUTO);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "top1st", strlen("top1st")))
    {
        PQ_MNG_SetFodMode(PQ_FOD_TOP_FIRST);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "bottom1st", strlen("bottom1st")))
    {
        PQ_MNG_SetFodMode(PQ_FOD_BOTTOM_FIRST);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetPrintBin(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = 0;

    if (0 == HI_OSAL_Strncmp(pArg2, "all", strlen("all")))
    {
        PQ_MNG_PrintTable(PRN_TABLE_ALL, u32Data);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "multi", strlen("all")))
    {
        PQ_MNG_PrintTable(PRN_TABLE_MULTI, u32Data);
    }
    else
    {
        u32Data = (HI_U32)simple_strtol(pArg2, NULL, 16);
        PQ_MNG_PrintTable(PRN_TABLE_SINGLE, u32Data);
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetPrintType(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = (HI_U32)simple_strtol(pArg2, NULL, 16);

    return PQ_HAL_SetPrintType(u32Data);
}

static HI_S32 drv_pq_ProcSetTunMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "debug", strlen("debug")))
    {
        PQ_MNG_SetDbTunMode(DB_TUN_DEBUG);
        PQ_MNG_SetIfmdTunMode(IFMD_TUN_DEBUG);
        PQ_MNG_SetZmeTunMode(ZME_TUN_DEBUG);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "normal", strlen("normal")))
    {
        PQ_MNG_SetDbTunMode(DB_TUN_NORMAL);
        PQ_MNG_SetIfmdTunMode(IFMD_TUN_NORMAL);
        PQ_MNG_SetZmeTunMode(ZME_TUN_NORMAL);
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetCfgDefault(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
        DRV_PQ_SetDefaultParam(HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        DRV_PQ_SetDefaultParam(HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

MODULE_LICENSE("GPL");

EXPORT_SYMBOL(DRV_PQ_UpdateVpssPQ);
EXPORT_SYMBOL(DRV_PQ_UpdateVdpPQ);
EXPORT_SYMBOL(DRV_PQ_UpdateVdpCSC);
EXPORT_SYMBOL(DRV_PQ_UpdateDCIWin);
EXPORT_SYMBOL(DRV_PQ_GetWbcInfo);
EXPORT_SYMBOL(DRV_PQ_SetAlgCalcCfg);
EXPORT_SYMBOL(DRV_PQ_GetCSCCoef);
EXPORT_SYMBOL(DRV_PQ_Get8BitCSCCoef);
EXPORT_SYMBOL(DRV_PQ_PfmdDetect);
EXPORT_SYMBOL(DRV_PQ_GetDciHistgram);
EXPORT_SYMBOL(DRV_PQ_SetZme);
EXPORT_SYMBOL(DRV_PQ_SetVpssZme);
EXPORT_SYMBOL(DRV_PQ_GetHDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_GetSDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_SetHDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_SetSDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_GetHDVideoSetting);
EXPORT_SYMBOL(DRV_PQ_GetSDVideoSetting);
EXPORT_SYMBOL(DRV_PQ_SetHDVideoSetting);
EXPORT_SYMBOL(DRV_PQ_SetSDVideoSetting);
EXPORT_SYMBOL(DRV_PQ_SetDefaultParam);




