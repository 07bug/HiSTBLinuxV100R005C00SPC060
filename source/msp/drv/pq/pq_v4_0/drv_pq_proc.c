/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : drv_pq_proc.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2015/09/22
  Author        : sdk
******************************************************************************/
#include "hi_math.h"
#include "drv_pq.h"

#define  PQ_MODIFY_TIME     "(20180626v2)"

extern HI_BOOL     g_bLoadPqBin;
extern PQ_PARAM_S *g_pstPqParam;
extern HI_DRV_PQ_PARAM_S stPqParam;
extern HI_U32   g_u32ImageWidth;
extern HI_U32   g_u32ImageHeight;
extern HI_DRV_PQ_VP_MODE_E sg_enVPMode[HI_DRV_PQ_VP_TYPE_BUTT];

static PQ_PROC_PRINT_LEVEL_E sg_enPqProcPrintLevel = PQ_PROC_PRINT_LEVEL_ORI;

static HI_S32 drv_pq_ProcSetBrightness(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetContrast(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetHue(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetSaturation(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetDemoMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetTunMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcColorMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetFleshTone(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetFrost(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetDeiMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetFodMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetPrintBin(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetPrintAlgBin(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetBin(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetHDRCfg(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetPrintType(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetSceneChange(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetCfgDefault(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetMcnr(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetHdcp(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetImageMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetColorTemp(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetHdrOffset(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetGfxHdrOffset(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetHdrTM(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetGfxHdrTM(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetZmeMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetAlgCtrl(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetVPMode(HI_DRV_PQ_VP_TYPE_E enVPType, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetVPTypeMode(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetProcLevelCtrl(HI_CHAR *pArg1, HI_CHAR *pArg2);

static HI_S32 drv_pq_ProcSetVdpZmeStrategy(HI_CHAR *pArg1, HI_CHAR *pArg2);
static HI_S32 drv_pq_ProcSetParaCtrl(HI_CHAR *pArg1, HI_CHAR *pArg2);


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
    {"demomode",     drv_pq_ProcSetDemoMode},
    {"mode",         drv_pq_ProcSetTunMode},
    {"colormode",    drv_pq_ProcColorMode},
    {"fleshtone",    drv_pq_ProcSetFleshTone},
    {"frost",        drv_pq_ProcSetFrost},
    {"deimode",      drv_pq_ProcSetDeiMode},
    {"fodmode",      drv_pq_ProcSetFodMode},
    {"printbin",     drv_pq_ProcSetPrintBin},
    {"printalgbin",  drv_pq_ProcSetPrintAlgBin},
    {"setbin",       drv_pq_ProcSetBin},
    {"sethdrcfg",    drv_pq_ProcSetHDRCfg},
    {"printtype",    drv_pq_ProcSetPrintType},
    {"scenechange",  drv_pq_ProcSetSceneChange},
    {"scd",          drv_pq_ProcSetSceneChange},
    {"cfgdefault",   drv_pq_ProcSetCfgDefault},
    {"mcnr",         drv_pq_ProcSetMcnr},
    {"hdcp",         drv_pq_ProcSetHdcp},
    {"imagemode",    drv_pq_ProcSetImageMode},
    {"preview",      drv_pq_ProcSetVPTypeMode},
    {"remote",       drv_pq_ProcSetVPTypeMode},
    {"colortemp",    drv_pq_ProcSetColorTemp},
    {"hdroffset",    drv_pq_ProcSetHdrOffset},
    {"gfxhdroffset", drv_pq_ProcSetGfxHdrOffset},
    {"hdrtm",        drv_pq_ProcSetHdrTM},
    {"gfxhdrtm",     drv_pq_ProcSetGfxHdrTM},
    {"zme",          drv_pq_ProcSetZmeMode},
    {"fmd",          drv_pq_ProcSetAlgCtrl},
    {"tnr",          drv_pq_ProcSetAlgCtrl},
    {"snr",          drv_pq_ProcSetAlgCtrl},
    {"db",           drv_pq_ProcSetAlgCtrl},
    {"vdp4ksnr",     drv_pq_ProcSetAlgCtrl},
    {"lchdr",        drv_pq_ProcSetAlgCtrl},
    {"dr",           drv_pq_ProcSetAlgCtrl},
    {"dm",           drv_pq_ProcSetAlgCtrl},
    {"sharp",        drv_pq_ProcSetAlgCtrl},
    {"dci",          drv_pq_ProcSetAlgCtrl},
    {"acm",          drv_pq_ProcSetAlgCtrl},
    {"csc",          drv_pq_ProcSetAlgCtrl},
    {"dei",          drv_pq_ProcSetAlgCtrl},
    {"ds",           drv_pq_ProcSetAlgCtrl},
    {"artds",        drv_pq_ProcSetAlgCtrl},
    {"gfxcsc",       drv_pq_ProcSetAlgCtrl},
    {"gfxzme",       drv_pq_ProcSetAlgCtrl},
    {"all",          drv_pq_ProcSetAlgCtrl},
    {"proc",         drv_pq_ProcSetProcLevelCtrl},
    {"para",       drv_pq_ProcSetParaCtrl},

    {"vdpzmestrategy", drv_pq_ProcSetVdpZmeStrategy},
};


typedef enum hiPQ_PRN_TABLE_TYPE_E
{
    PRN_TABLE_ALL           = 0,
    PRN_TABLE_MULTI         = 1,
    PRN_TABLE_SINGLE        = 2,
    PRN_TABLE_ALG           = 3,
    PRN_TABLE_SET_DEFAULT   = 4,

    PRN_TABLE_BUTT,
} PQ_PRN_TABLE_TYPE_E;

static HI_S32 DRV_PQ_SetTunMode(PQ_TUN_MODE_E enTunMode)
{
    HI_U32 i;

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        if (PQ_FUNC_CALL(i, SetTunMode))
        {
            GET_ALG_FUN(i)->SetTunMode(enTunMode);
        }
    }

    return HI_SUCCESS;
}

#ifdef PQ_PROC_CTRL_SUPPORT
static HI_S32 drv_pq_ProcReadACM(struct seq_file *s)
{
#ifdef PQ_ALG_ACM
    HI_PQ_COLOR_SPEC_MODE_E enProcColorSpecMode = HI_PQ_COLOR_MODE_RECOMMEND;
    HI_U32  u32FleshStr  = 0;

    HI_U8  *au8ProcEnhanceMode[HI_PQ_COLOR_MODE_BUTT] =
    {
        "optimal",
        "blue",
        "green",
        "bg",
        "original"
    };

    HI_U8  *au8ProcFleshTone[FLE_GAIN_BUTT] =
    {
        "off",
        "low",
        "middle",
        "high"
    };

    DRV_PQ_GetColorEnhanceMode(&enProcColorSpecMode);
    DRV_PQ_GetFleshToneLevel(&u32FleshStr);

    PQ_CHECK_OVER_RANGE_RE_FAIL(enProcColorSpecMode, HI_PQ_COLOR_MODE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(u32FleshStr, FLE_GAIN_BUTT);

    PROC_PRINT(s, "%-20s: %-20s", "enhance mode",       au8ProcEnhanceMode[enProcColorSpecMode]);
    PROC_PRINT(s, "%-20s: %s\n",  "flesh tone level",   au8ProcFleshTone[u32FleshStr]);

#endif

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcReadCSC(struct seq_file *s)
{
#ifdef PQ_ALG_CSC
    HI_PQ_VDP_CSC_S stCSC[HI_PQ_CSC_TYPE_BUUT];
    HI_U8  *au8ProcCSC[HI_PQ_CSC_BUTT + 1] =
    {
        "ProcPQ_CSC_YUV2RGB_601           ",
        "ProcPQ_CSC_YUV2RGB_709           ",
        "ProcPQ_CSC_RGB2YUV_601           ",
        "ProcPQ_CSC_RGB2YUV_709           ",
        "ProcPQ_CSC_YUV2YUV_709_601       ",
        "ProcPQ_CSC_YUV2YUV_601_709       ",
        "ProcPQ_CSC_YUV2YUV               ",

        "ProcPQ_CSC_RGB2RGB_709_2020      ",
        "ProcPQ_CSC_RGB2YUV_2020_2020_L   ",
        "ProcPQ_CSC_RGB2RGB_2020_709      ",
        "ProcPQ_CSC_RGB2YUV_2020_709_L    ",

        "ProcPQ_CSC_RGB2RGB_601_2020      ",
        "ProcPQ_CSC_RGB2RGB_2020_601      ",
        "ProcPQ_CSC_RGB2YUV_2020_601_L    ",

        "ProcPQ_CSC_YUV2YUV_709_2020_L_L  ",
        "ProcPQ_CSC_YUV2RGB_709_2020_L    ",

        "ProcPQ_CSC_YUV2YUV_601_2020_L_L  ",
        "ProcPQ_CSC_YUV2RGB_601_2020_L    ",

        "ProcPQ_CSC_YUV2YUV_2020_2020_L_L ",
        "ProcPQ_CSC_YUV2YUV_2020_709_L_L  ",
        "ProcPQ_CSC_YUV2YUV_2020_601_L_L  ",
        "ProcPQ_CSC_YUV2RGB_2020_2020_L   ",
        "ProcPQ_CSC_YUV2RGB_2020_709_L    ",
        "ProcPQ_CSC_YUV2RGB_2020_601_L    ",

        "ProcPQ_CSC_YUV2RGB_601_FULL      ",
        "ProcPQ_CSC_YUV2RGB_709_FULL      ",
        "ProcPQ_CSC_RGB2YUV_601_FULL      ",
        "ProcPQ_CSC_RGB2YUV_709_FULL      ",
        "ProcPQ_CSC_RGB2RGB               ",

        "NULL",
    };

    if (GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCMode == HI_NULL)
    {
        return HI_FAILURE;
    }

    GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCMode(HI_PQ_CSC_TUNING_V0, &stCSC[HI_PQ_CSC_TUNING_V0]);
    GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCMode(HI_PQ_CSC_TUNING_V1, &stCSC[HI_PQ_CSC_TUNING_V1]);
    GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCMode(HI_PQ_CSC_TUNING_V3, &stCSC[HI_PQ_CSC_TUNING_V3]);
    GET_ALG_FUN(HI_PQ_MODULE_CSC)->GetCSCMode(HI_PQ_CSC_TUNING_V4, &stCSC[HI_PQ_CSC_TUNING_V4]);

    PROC_PRINT(s, "%-10s: %-20s",   "V0 enable", stCSC[HI_PQ_CSC_TUNING_V0].bCSCEn ? "on" : "off");
    PQ_CHECK_OVER_RANGE_RE_FAIL(stCSC[HI_PQ_CSC_TUNING_V0].enCscMode, HI_PQ_CSC_BUTT + 1);
    PROC_PRINT(s, "%-10s: %-40s\n", "CSC mode", au8ProcCSC[stCSC[HI_PQ_CSC_TUNING_V0].enCscMode]);

    PROC_PRINT(s, "%-10s: %-20s",   "V1 enable", stCSC[HI_PQ_CSC_TUNING_V1].bCSCEn  ? "on" : "off");
    PQ_CHECK_OVER_RANGE_RE_FAIL(stCSC[HI_PQ_CSC_TUNING_V1].enCscMode, HI_PQ_CSC_BUTT + 1);
    PROC_PRINT(s, "%-10s: %-40s\n", "CSC mode", au8ProcCSC[stCSC[HI_PQ_CSC_TUNING_V1].enCscMode]);

    PROC_PRINT(s, "%-10s: %-20s",   "V3 enable", stCSC[HI_PQ_CSC_TUNING_V3].bCSCEn  ? "on" : "off");
    PQ_CHECK_OVER_RANGE_RE_FAIL(stCSC[HI_PQ_CSC_TUNING_V3].enCscMode, HI_PQ_CSC_BUTT + 1);
    PROC_PRINT(s, "%-10s: %-40s\n", "CSC mode", au8ProcCSC[stCSC[HI_PQ_CSC_TUNING_V3].enCscMode]);

    PROC_PRINT(s, "%-10s: %-20s",   "V4 Enable", stCSC[HI_PQ_CSC_TUNING_V4].bCSCEn  ? "on" : "off");
    PQ_CHECK_OVER_RANGE_RE_FAIL(stCSC[HI_PQ_CSC_TUNING_V4].enCscMode, HI_PQ_CSC_BUTT + 1);
    PROC_PRINT(s, "%-10s: %-40s\n", "CSC mode", au8ProcCSC[stCSC[HI_PQ_CSC_TUNING_V4].enCscMode]);

#endif

    return HI_SUCCESS;
}




static HI_S32 drv_pq_ProcReadZME(struct seq_file *s)
{
#ifdef PQ_ALG_ZME
    HI_BOOL bVpssZmeFirEn  = HI_FALSE;
    HI_BOOL bVpssZmeMedEn  = HI_FALSE;
    HI_BOOL bVdpZmeFirEn   = HI_FALSE;
    HI_BOOL bVdpZmeMedEn   = HI_FALSE;

    HI_PQ_PROC_VDPZME_RESO_S stProcVdpZmeReso = {{0}};
    HI_PQ_PROC_VDPZME_STRATEGY_S stProcVdpZmeStrategy = {0};
    HI_PQ_PROC_WBC_STRATEGY_S stProcWbcStrategy = {0};

    if (GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetZmeEnMode == HI_NULL)
    {
        return HI_FAILURE;
    }

    memset(&stProcVdpZmeReso, 0, sizeof(stProcVdpZmeReso));
    memset(&stProcVdpZmeStrategy, 0, sizeof(stProcVdpZmeStrategy));

    GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetZmeEnMode(PQ_ZME_MODE_VPSS_FIR, &bVpssZmeFirEn);
    GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetZmeEnMode(PQ_ZME_MODE_VPSS_MED, &bVpssZmeMedEn);
    GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetZmeEnMode(PQ_ZME_MODE_VDP_FIR,  &bVdpZmeFirEn);
    GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetZmeEnMode(PQ_ZME_MODE_VDP_MED,  &bVdpZmeMedEn);

    PROC_PRINT(s, "%-20s: %-20s",   "vpss fir/copy mode",   bVpssZmeFirEn   ? "fir" : "copy");
    PROC_PRINT(s, "%-20s: %-20s\n", "vpss med enable",      bVpssZmeMedEn   ? "on"  : "off");
    PROC_PRINT(s, "%-20s: %-20s",   "vdp  fir/copy mode",   bVdpZmeFirEn    ? "fir" : "copy");
    PROC_PRINT(s, "%-20s: %-20s\n", "vdp  med enable",      bVdpZmeMedEn    ? "on"  : "off");

    if (PQ_PROC_PRINT_LEVEL3 == sg_enPqProcPrintLevel)
    {
        PROC_PRINT(s, "------------------------------------ %s ------------------------------------\n", "vdp v0 zme reso");
        if (GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetProcVdpZmeReso)
        {
            GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetProcVdpZmeReso(&stProcVdpZmeReso);

            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  in       : width, height", stProcVdpZmeReso.stVdpInReso.s32Width, stProcVdpZmeReso.stVdpInReso.s32Height);
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  out      : width, height", stProcVdpZmeReso.stVdpOutreso.s32Width, stProcVdpZmeReso.stVdpOutreso.s32Height);
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme1 in  : width, height", stProcVdpZmeReso.stVdpZme1Inreso.s32Width, stProcVdpZmeReso.stVdpZme1Inreso.s32Height);
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme1 out : width, height", stProcVdpZmeReso.stVdpZme1Outreso.s32Width, stProcVdpZmeReso.stVdpZme1Outreso.s32Height);

            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme2 in  : width, height", stProcVdpZmeReso.stVdpZme2Inreso.s32Width, stProcVdpZmeReso.stVdpZme2Inreso.s32Height);
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme2 out : width, height", stProcVdpZmeReso.stVdpZme2Outreso.s32Width, stProcVdpZmeReso.stVdpZme2Outreso.s32Height);
        }

        if (GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetProcVdpZmeStrategy)
        {
            GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetProcVdpZmeStrategy(&stProcVdpZmeStrategy);

            PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(stProcVdpZmeStrategy.enProcVdpWidthDrawMode, 10);
            PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(stProcVdpZmeStrategy.enProcVdpHeightDrawMode, 10);
            PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(stProcVdpZmeStrategy.bProcVdpHpzmeEn, 2);

            PROC_PRINT(s, "%-20s | %-20s \n",  "vdp  horizontal prezme enable", stProcVdpZmeStrategy.bProcVdpHpzmeEn ? "on" : "off");
            PROC_PRINT(s, "%-20s | %-8d \n",   "vdp  horizontal draw mode", stProcVdpZmeStrategy.enProcVdpWidthDrawMode);
            PROC_PRINT(s, "%-20s | %-8d \n",   "vdp  vertical   draw mode", stProcVdpZmeStrategy.enProcVdpHeightDrawMode);
        }

        if (GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetProcWbcStrategy)
        {
            PROC_PRINT(s, "------------------------------------ %s ------------------------------------\n", "vdp wbc dhd zme reso");
            GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetProcWbcStrategy(HI_PQ_PROC_WBC_LAYER_DHD, &stProcWbcStrategy);

            PROC_PRINT(s, "%-20s | %-6s | %-8s | %-5s\n", "wbc dhd point sel", stProcWbcStrategy.u32PointSel ? "GP" : "CBM", "p2i", stProcWbcStrategy.bP2iEn ? "on" : "off");
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme1 in  : width, height", stProcWbcStrategy.stZme1Inreso.s32Width, stProcWbcStrategy.stZme1Inreso.s32Height);
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme1 out : width, height", stProcWbcStrategy.stZme1Outreso.s32Width, stProcWbcStrategy.stZme1Outreso.s32Height);

            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme2 in  : width, height", stProcWbcStrategy.stZme2Inreso.s32Width, stProcWbcStrategy.stZme2Inreso.s32Height);
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme2 out : width, height", stProcWbcStrategy.stZme2Outreso.s32Width, stProcWbcStrategy.stZme2Outreso.s32Height);

            PROC_PRINT(s, "------------------------------------ %s ------------------------------------\n", "vdp wbc vp zme reso");
            GET_ALG_FUN(HI_PQ_MODULE_ZME)->GetProcWbcStrategy(HI_PQ_PROC_WBC_LAYER_VP, &stProcWbcStrategy);

            PROC_PRINT(s, "%-20s : %-6s | %-8s : %-5s\n", "wbc vp point sel", stProcWbcStrategy.u32PointSel ? "V0" : "VP", "p2i", stProcWbcStrategy.bP2iEn ? "on" : "off");
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme1 in  : width, height", stProcWbcStrategy.stZme1Inreso.s32Width, stProcWbcStrategy.stZme1Inreso.s32Height);
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme1 out : width, height", stProcWbcStrategy.stZme1Outreso.s32Width, stProcWbcStrategy.stZme1Outreso.s32Height);

            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme2 in  : width, height", stProcWbcStrategy.stZme2Inreso.s32Width, stProcWbcStrategy.stZme2Inreso.s32Height);
            PROC_PRINT(s, "%-20s | %-8d: %-8d \n",  "vdp  zme2 out : width, height", stProcWbcStrategy.stZme2Outreso.s32Width, stProcWbcStrategy.stZme2Outreso.s32Height);
        }
    }
#endif

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcReadFMD(struct seq_file *s)
{
#ifdef PQ_ALG_FMD
    HI_S32 s32DeiMdLum = 0;
    HI_PQ_IFMD_PLAYBACK_S stIfmdPlayBack = {0};
    HI_U8 *au8ProcFldMode[ALG_DEI_MODE_BUTT] = { "5Field", "4Field", "3Field"};

    if (GET_ALG_FUN(HI_PQ_MODULE_FMD)->GetIfmdDectInfo)
    {
        GET_ALG_FUN(HI_PQ_MODULE_FMD)->GetIfmdDectInfo(&stIfmdPlayBack);
        PROC_PRINT(s, "%-20s: %-20s",   "fir/copy mode",    stIfmdPlayBack.die_out_sel ? "copy" : "fir");
        PROC_PRINT(s, "%-20s: %-20d\n", "dir mch",          stIfmdPlayBack.dir_mch);
        PROC_PRINT(s, "%-20s: %-20s",   "field order",      stIfmdPlayBack.s32FieldOrder ? "bottom first" : "top first");
        PROC_PRINT(s, "%-20s: %-20s\n", "edge smooth",      stIfmdPlayBack.u32EdgeSmoothEn ? "enable" : "disable");
    }

    if (GET_ALG_FUN(HI_PQ_MODULE_FMD)->GetDeiMdLum)
    {
        s32DeiMdLum = GET_ALG_FUN(HI_PQ_MODULE_FMD)->GetDeiMdLum();

        PQ_CHECK_OVER_RANGE_RE_FAIL(s32DeiMdLum, ALG_DEI_MODE_BUTT);

        PROC_PRINT(s, "%-20s: %-20s\n", "field mode", au8ProcFldMode[(ALG_DEI_MODE_E)s32DeiMdLum]);
    }

#endif

    return HI_SUCCESS;
}

#endif

static HI_S32 drv_pq_ProcSetFrostLevel(HI_PQ_FROST_LEVEL_E enFrostLevel)
{
    if (PQ_FUNC_CALL(HI_PQ_MODULE_ZME, SetFrostLevel))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetFrostLevel(enFrostLevel);
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

static HI_S32 drv_pq_ProcSetHDCPEn(HI_BOOL bOnOff)
{
    if (PQ_FUNC_CALL(HI_PQ_MODULE_ZME, SetHDCPEn))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetHDCPEn(bOnOff);
        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

static HI_VOID drv_pq_ProcPrintTable(PQ_PRN_TABLE_TYPE_E enType, HI_U32 u32PriAddr)
{
#ifdef PQ_PROC_CTRL_SUPPORT
    HI_U32 i;
    HI_U32 u32Addr, u32Value, u32Module;
    HI_U8  u8Lsb, u8Msb, u8SourceMode, u8OutputMode;
    HI_U32 u32PhyListNum = PQ_TABLE_GetPhyListNum();
    PQ_PHY_REG_S *pstPhyReg  = PQ_TABLE_GetPhyReg();

    PQ_CHECK_OVER_RANGE_RE_NULL(enType, PRN_TABLE_BUTT);
    PQ_CHECK_NULL_PTR_RE_NULL(pstPhyReg);

    if (PRN_TABLE_SET_DEFAULT == enType)
    {
        PQ_TABLE_SetTableRegDefault();
        HI_DRV_PROC_EchoHelper("set pqbin default from code success!\n");
        return;
    }

    HI_DRV_PROC_EchoHelper("\n");
    HI_DRV_PROC_EchoHelper("List\t");
    HI_DRV_PROC_EchoHelper("Addr\t");
    HI_DRV_PROC_EchoHelper("Lsb\t");
    HI_DRV_PROC_EchoHelper("Msb\t");
    HI_DRV_PROC_EchoHelper("SourceMode\t");
    HI_DRV_PROC_EchoHelper("OutputMode\t");
    HI_DRV_PROC_EchoHelper("Module\t");
    HI_DRV_PROC_EchoHelper("Value\t");

    for (i = 0; i < u32PhyListNum; i++)
    {
        u32Addr       = pstPhyReg[i].u32RegAddr;
        u32Value      = pstPhyReg[i].u32Value;
        u32Module     = pstPhyReg[i].u32Module;
        u8Lsb         = pstPhyReg[i].u8Lsb;
        u8Msb         = pstPhyReg[i].u8Msb;
        u8SourceMode  = pstPhyReg[i].u8SourceMode;
        u8OutputMode  = pstPhyReg[i].u8OutputMode;

        if ((PRN_TABLE_SINGLE == enType) && (u32PriAddr != u32Addr))
        {
            continue;
        }
        else if ((PRN_TABLE_MULTI == enType) && (PQ_BIN_ADAPT_MULTIPLE != PQ_COMM_GetAlgAdapeType(u32Module)))
        {
            continue;
        }
        else if ((PRN_TABLE_ALG == enType) && (u32PriAddr != u32Module))
        {
            continue;
        }

        HI_DRV_PROC_EchoHelper("\n");
        HI_DRV_PROC_EchoHelper("[%d]\t", i);
        HI_DRV_PROC_EchoHelper("0x%x\t", u32Addr);
        HI_DRV_PROC_EchoHelper("%d\t", u8Lsb);
        HI_DRV_PROC_EchoHelper("%d\t", u8Msb);
        HI_DRV_PROC_EchoHelper("%d\t\t", u8SourceMode);
        HI_DRV_PROC_EchoHelper("%d\t\t", u8OutputMode);
        HI_DRV_PROC_EchoHelper("0x%x\t", u32Module);
        HI_DRV_PROC_EchoHelper("%d\t", u32Value);

    }

    HI_DRV_PROC_EchoHelper("\n\n");

#endif
}

HI_VOID drv_pq_ProcSetTable(HI_U32 u32List, HI_U32 u32Value)
{
#ifdef PQ_PROC_CTRL_SUPPORT
    HI_U32 u32Addr, u32OldValue, u32Module;
    HI_U8  u8Lsb, u8Msb, u8SourceMode, u8OutputMode;
    PQ_PHY_REG_S *pstPhyReg  = PQ_TABLE_GetPhyReg();

    if (HI_NULL == pstPhyReg)
    {
        return;
    }

    if (u32List > PQ_TABLE_GetPhyListNum())
    {
        return;
    }

    HI_DRV_PROC_EchoHelper("\n");
    HI_DRV_PROC_EchoHelper("List\t");
    HI_DRV_PROC_EchoHelper("Addr\t");
    HI_DRV_PROC_EchoHelper("Lsb\t");
    HI_DRV_PROC_EchoHelper("Msb\t");
    HI_DRV_PROC_EchoHelper("SourceMode\t");
    HI_DRV_PROC_EchoHelper("OutputMode\t");
    HI_DRV_PROC_EchoHelper("Module\t");
    HI_DRV_PROC_EchoHelper("Value\t");

    u32Addr       = pstPhyReg[u32List].u32RegAddr;
    u32OldValue   = pstPhyReg[u32List].u32Value;
    u32Module     = pstPhyReg[u32List].u32Module;
    u8Lsb         = pstPhyReg[u32List].u8Lsb;
    u8Msb         = pstPhyReg[u32List].u8Msb;
    u8SourceMode  = pstPhyReg[u32List].u8SourceMode;
    u8OutputMode  = pstPhyReg[u32List].u8OutputMode;

    HI_DRV_PROC_EchoHelper("\n");
    HI_DRV_PROC_EchoHelper("[%d]\t", u32List);
    HI_DRV_PROC_EchoHelper("0x%x\t", u32Addr);
    HI_DRV_PROC_EchoHelper("%d\t", u8Lsb);
    HI_DRV_PROC_EchoHelper("%d\t", u8Msb);
    HI_DRV_PROC_EchoHelper("%d\t\t", u8SourceMode);
    HI_DRV_PROC_EchoHelper("%d\t\t", u8OutputMode);
    HI_DRV_PROC_EchoHelper("0x%x\t", u32Module);
    HI_DRV_PROC_EchoHelper("%d to %d\n", u32OldValue, u32Value);

    pstPhyReg[u32List].u32Value = u32Value;
#endif

    return;
}

HI_S32 DRV_PQ_ProcRead(struct seq_file *s, HI_VOID *data)
{
#ifdef PQ_PROC_CTRL_SUPPORT
    HI_BOOL bEableEn    = HI_FALSE;
    HI_BOOL bDemoEn     = HI_FALSE;
    HI_BOOL bDefault    = HI_FALSE;
    HI_BOOL u32Strength = 0;
    PQ_DEMO_MODE_E enDemoMode = PQ_DEMO_ENABLE_L;
    HI_U32 u32SizeOfPqParam = sizeof(PQ_PARAM_S);
    HI_U32 AlgModule = 0;
    HI_VDP_CHANNEL_TIMING_S  stHDTimingInfo = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1];
    HI_VDP_CHANNEL_TIMING_S  stSDTimingInfo = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_0];
    HI_U32 u32HandleNo = 0;
    HI_BOOL bProcPrintTimeCntEn = HI_FALSE;

    HI_U8 *au8ProcSourceType[PQ_SOURCE_MODE_BUTT] =
    {
        "Unknown",
        "SD",
        "HD",
        "UHD"
    };

    HI_U8 *au8ProcVPMode[HI_DRV_PQ_VIDEOPHONE_MODE_BUTT] =
    {
        "HI_DRV_PQ_VIDEOPHONE_MODE_RECOMMEND",
        "HI_DRV_PQ_VIDEOPHONE_MODE_BLACK",
        "HI_DRV_PQ_VIDEOPHONE_MODE_COLORFUL",
        "HI_DRV_PQ_VIDEOPHONE_MODE_BRIGHT",
        "HI_DRV_PQ_VIDEOPHONE_MODE_WARM",
        "HI_DRV_PQ_VIDEOPHONE_MODE_COOL",
        "HI_DRV_PQ_VIDEOPHONE_MODE_OLD",
        "HI_DRV_PQ_VIDEOPHONE_MODE_USER"
    };

    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();
    PQ_OUTPUT_MODE_E enOutputMode = PQ_COMM_GetOutputMode();
    HI_U8 *aOutputMode[PQ_OUTPUT_MODE_BUTT] =
    {
        "NULL",
        "SD",
        "HD",
        "UHD"
    };

    DRV_PQ_GetDefaultParam(&bDefault);

    PROC_PRINT(s, "================================ PQ Bin Information =================================\n");
    PROC_PRINT(s, "%-20s: %s %s\n", "Driver version", "PQ_V4_0"PQ_MODIFY_TIME, "[Build Time:"__DATE__", "__TIME__"]");
    PROC_PRINT(s, "%-20s: %s\n", "PQ Bin version", PQ_VERSION);
    PROC_PRINT(s, "%-20s: %d\n", "PQ Bin size", u32SizeOfPqParam);

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
    PROC_PRINT(s, "%-20s: %-20d",   "HD brightness",    NUM2LEVEL(stPqParam.stHDVideoSetting.u16Brightness));
    PROC_PRINT(s, "%-20s: %-20d\n", "SD brightness",    NUM2LEVEL(stPqParam.stSDVideoSetting.u16Brightness));
    PROC_PRINT(s, "%-20s: %-20d",   "HD contrast",      NUM2LEVEL(stPqParam.stHDVideoSetting.u16Contrast));
    PROC_PRINT(s, "%-20s: %-20d\n", "SD contrast",      NUM2LEVEL(stPqParam.stSDVideoSetting.u16Contrast));
    PROC_PRINT(s, "%-20s: %-20d",   "HD hue",           NUM2LEVEL(stPqParam.stHDVideoSetting.u16Hue));
    PROC_PRINT(s, "%-20s: %-20d\n", "SD hue",           NUM2LEVEL(stPqParam.stSDVideoSetting.u16Hue));
    PROC_PRINT(s, "%-20s: %-20d",   "HD saturation",    NUM2LEVEL(stPqParam.stHDVideoSetting.u16Saturation));
    PROC_PRINT(s, "%-20s: %-20d\n", "SD saturation",    NUM2LEVEL(stPqParam.stSDVideoSetting.u16Saturation));
    PROC_PRINT(s, "%-20s: %-20s\n", "Default param",    bDefault ? "yes" : "no");
    PROC_PRINT(s, "%-20s: %-20s\n", "3D type",          g_stPqStatus.b3dType ? "yes" : "no");
    PROC_PRINT(s, "%-20s: %-20s",   "Out mode",         aOutputMode[enOutputMode]);
    PROC_PRINT(s, "%-20s: %s(%4d*%4d)\n", "Source",     au8ProcSourceType[enSourceMode], g_u32ImageWidth, g_u32ImageHeight);
    PROC_PRINT(s, "%-20s: %4d*%4d, progressive:%d, refresh rate:%d\n", "HD output", stHDTimingInfo.stFmtRect.s32Width,
               stHDTimingInfo.stFmtRect.s32Height, stHDTimingInfo.bProgressive, stHDTimingInfo.u32RefreshRate / 100);
    PROC_PRINT(s, "%-20s: %4d*%4d, progressive:%d, refresh rate:%d\n", "SD output", stSDTimingInfo.stFmtRect.s32Width,
               stSDTimingInfo.stFmtRect.s32Height, stSDTimingInfo.bProgressive, stSDTimingInfo.u32RefreshRate / 100);

    PROC_PRINT(s, "=============================== VideoPhone Information ==============================\n");

    if (PQ_IMAGE_MODE_VIDEOPHONE == g_stPqStatus.enImageMode)
    {
        PROC_PRINT(s, "%-20s\n", "Video phone mode : yes");
    }
    else if (PQ_IMAGE_MODE_GALLERY == g_stPqStatus.enImageMode)
    {
        PROC_PRINT(s, "%-20s\n", "Gallery mode : yes");
    }
    else
    {
        PROC_PRINT(s, "%-20s\n", "Normal mode : yes");
    }

    if (PQ_IMAGE_MODE_VIDEOPHONE == g_stPqStatus.enImageMode)
    {
        PROC_PRINT(s, "%-20s: %-20s\n", "Video phone Preview Mode", au8ProcVPMode[sg_enVPMode[HI_DRV_PQ_VP_TYPE_PREVIEW]]);
        PROC_PRINT(s, "%-20s: %-20s\n", "Video phone Remote  Mode", au8ProcVPMode[sg_enVPMode[HI_DRV_PQ_VP_TYPE_REMOTE]]);
        PROC_PRINT(s, "============== VideoPhone Picture Information ==============\n");
        PROC_PRINT(s, "%-20s: %-20d",   "Preview brightness",       NUM2LEVEL(stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Brightness));
        PROC_PRINT(s, "%-20s: %-20d\n", "Remote brightness",        NUM2LEVEL(stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Brightness));
        PROC_PRINT(s, "%-20s: %-20d",   "Preview contrast",         NUM2LEVEL(stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Contrast));
        PROC_PRINT(s, "%-20s: %-20d\n", "Remote contrast",          NUM2LEVEL(stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Contrast));
        PROC_PRINT(s, "%-20s: %-20d",   "Preview hue",              NUM2LEVEL(stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Hue));
        PROC_PRINT(s, "%-20s: %-20d\n", "Remote hue",               NUM2LEVEL(stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Hue));
        PROC_PRINT(s, "%-20s: %-20d",   "Preview saturation",       NUM2LEVEL(stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_PREVIEW].u16Saturation));
        PROC_PRINT(s, "%-20s: %-20d\n", "Remote saturation",        NUM2LEVEL(stPqParam.stVpssVideoSetting[HI_DRV_PQ_VP_TYPE_REMOTE].u16Saturation));
    }

    PROC_PRINT(s, "================================ Algorithm Information ==============================\n");

    for (AlgModule = 0; AlgModule < HI_PQ_MODULE_BUTT; AlgModule++)
    {
        if (HI_NULL == GET_ALG(AlgModule))
        {
            continue;
        }

        PROC_PRINT(s, "------------------------------------ %s ------------------------------------\n", PQ_COMM_GetAlgName(AlgModule));
        if (REG_TYPE_VPSS == PQ_COMM_GetAlgTypeID(AlgModule))
        {
            PROC_PRINT(s, "%-20s: %-20s", "bind to", "vpss");
        }
        else if (REG_TYPE_VDP == PQ_COMM_GetAlgTypeID(AlgModule))
        {
            PROC_PRINT(s, "%-20s: %-20s", "bind to", "vdp");
        }

        if (GET_ALG_FUN(AlgModule)->GetEnable)
        {
            GET_ALG_FUN(AlgModule)->GetEnable(&bEableEn);
            PROC_PRINT(s, "%-20s: %-20s\n", "module", bEableEn ? "on" : "off");
        }

        if (GET_ALG_FUN(AlgModule)->GetStrength)
        {
            GET_ALG_FUN(AlgModule)->GetStrength(&u32Strength);
            PROC_PRINT(s, "%-20s: %-20d", "strength", u32Strength);
        }

        if (GET_ALG_FUN(AlgModule)->GetDemo)
        {
            GET_ALG_FUN(AlgModule)->GetDemo(&bDemoEn);
            PROC_PRINT(s, "%-20s: %-20s\n", "demo", bDemoEn ? "on" : "off");
            if (bDemoEn && GET_ALG_FUN(AlgModule)->GetDemoMode)
            {
                GET_ALG_FUN(AlgModule)->GetDemoMode(&enDemoMode);
                PROC_PRINT(s, "%-20s: %-20s\n", "demo mode", enDemoMode ? "enable right" : "enable left");
            }
        }
        else if (REG_TYPE_ALL != PQ_COMM_GetAlgTypeID(AlgModule)
                 || GET_ALG_FUN(AlgModule)->GetEnable
                 || GET_ALG_FUN(AlgModule)->GetStrength)
        {
            PROC_PRINT(s, "\n");
        }

        switch (AlgModule)
        {
            case HI_PQ_MODULE_COLOR:
                drv_pq_ProcReadACM(s);
                break;
            case HI_PQ_MODULE_CSC:
                drv_pq_ProcReadCSC(s);
                break;
            case HI_PQ_MODULE_ZME:
                drv_pq_ProcReadZME(s);
                break;
            case HI_PQ_MODULE_FMD:
                drv_pq_ProcReadFMD(s);
                break;
            default:
                break;
        }
    }

    /* print each vpss alg time delay */
    DRV_PQ_GetProcAlgTimeCntEn(&bProcPrintTimeCntEn);

    if (bProcPrintTimeCntEn)
    {
        HI_PQ_MODULE_E enProcModule = HI_PQ_MODULE_FMD;

        PROC_PRINT(s, "------------------------------------ %s ------------------------------------\n", "alg time cost");
        for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
        {
            HI_ULONG ulPqAlgTimeCost = 0;
            for (enProcModule = HI_PQ_MODULE_FMD; enProcModule < HI_PQ_MODULE_ALL; enProcModule++)
            {
                DRV_PQ_GetVpssProcAlgTimeCnt(u32HandleNo, enProcModule, &ulPqAlgTimeCost);

                if (ulPqAlgTimeCost > 0)
                {
                    PROC_PRINT(s, "HandleNo : %-5d / Module :  %-12s / TimeDelay : %-20lu (us)\n", \
                               u32HandleNo, PQ_COMM_GetAlgName(enProcModule), ulPqAlgTimeCost);
                }
            }
        }
    }

    PROC_PRINT(s, "================================================================================\n");

#endif
    return HI_SUCCESS;
}

static HI_VOID DRV_PQ_ProcPrintHelp(HI_VOID)
{
#ifdef PQ_PROC_CTRL_SUPPORT

    HI_DRV_PROC_EchoHelper("\n");
    HI_DRV_PROC_EchoHelper("help message:\n");
    HI_DRV_PROC_EchoHelper("echo help                        > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo bright          <0~100>     > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo contrast        <0~100>     > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo hue             <0~100>     > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo satu            <0~100>     > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo mode            debug/normal     > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo scd/scenechange on/off           > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo cfgdefault      on/off           > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo mcnr            on/off           > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo hdcp            on/off           > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo printbin        <hex>/all/multi  > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo printalgbin     <0~20>           > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo printhdrtm      0(ori)/1(b100)/2(b0)/3(d100)/4(d0)/5(BP)/6(DP) > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo printtype       <hex>            > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo printalgbin     <0~20>           > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo setbin          default          > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo setbin<list>    value            > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo sethdrcfg       default/debug    > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo imagemode       normal/videophone/gallery    > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo preview/remote  recommed/black/color/bt/warm/cool/old/user > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo colortemp       rrggbb           > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo hdroffset       HdrScene(00:Hdr2Sdr,10:Sdr2Hdr)bbccsshhrrggbb   > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo hdrtm           HdrScene(00:Hdr2Sdr,10:Sdr2Hdr)M(0-1)DD(AccD:0-99)BB(AccB:0-99)dd(0-99)bb(0-99) > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo gfxhdroffset    GfxHdrScene(10:Sdr2Hdr,11:Sdr2Hlg)bbccsshhrrggbb   > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo gfxhdrtm        GfxHdrScene(10:Sdr2Hdr,11:Sdr2Hlg)M(0-1)dd(0-99)bb(0-99) > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo fleshtone       off/low/mid/high           > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo frost           off/low/mid/high           > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo colormode       blue/green/bg/optimal/off  > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo deimode         auto/fir/copy              > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo fodmode         auto/top1st/bottom1st      > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo deshoot         flat/medfir                > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo demomode        fixr/fixl/scrollr/scrolll  > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo zme             vdpfir/vdpcopy/vdpmedon/vdpmedoff          > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo zme             vpssfir/vpsscopy/vpssmedon/vpssmedoff      > /proc/msp/pq\n");
    if (PQ_PROC_PRINT_LEVEL3 == sg_enPqProcPrintLevel)
    {
        HI_DRV_PROC_EchoHelper("echo vdpzmestrategy  ZmeNum(0:no set,1:just use zme1)WDraw(Width Draw,0:no set,1/2/4/8:Draw)HDraw(Height Draw,0:no set,1/2/4/8:Draw) > /proc/msp/pq\n");
    }

    HI_DRV_PROC_EchoHelper("echo sharp/dci/acm/tnr/snr/db/dm/vdp4ksnr/all            <0~100>         > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo sharp/dci/acm/tnr/snr/dei/db/dm/dr/ds/vdp4ksnr/all  enable/disable  > /proc/msp/pq\n");
    HI_DRV_PROC_EchoHelper("echo sharp/dci/acm/tnr/snr/dei/db/vpscene/vdp4ksnr/lchdr/all   demoon/demooff  > /proc/msp/pq\n");
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

static HI_S32 DRV_PQ_ProcCmdProcess(HI_CHAR *pArg1, HI_CHAR *pArg2)
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

HI_S32 DRV_PQ_ProcWrite(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    HI_S32 s32Ret = HI_SUCCESS;
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
    if (  (s32Ret != HI_SUCCESS)
          || (0 == HI_OSAL_Strncmp(pArg1, "help", strlen("help")))
          || (pArg2 == HI_NULL) )
    {
        DRV_PQ_ProcPrintHelp();
        return count;
    }

    s32Ret = DRV_PQ_ProcCmdProcess(pArg1, pArg2);
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

static HI_S32 drv_pq_ProcSetDemoMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_PQ_DEMO_MODE_E enDemoMode = HI_PQ_DEMO_MODE_BUTT;

    if (0 == HI_OSAL_Strncmp(pArg2, "fixr", strlen("fixr")))
    {
        enDemoMode = HI_PQ_DEMO_MODE_FIXED_R;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "fixl", strlen("fixl")))
    {
        enDemoMode = HI_PQ_DEMO_MODE_FIXED_L;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "scrollr", strlen("scrollr")))
    {
        enDemoMode = HI_PQ_DEMO_MODE_SCROLL_R;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "scrolll", strlen("scrolll")))
    {
        enDemoMode = HI_PQ_DEMO_MODE_SCROLL_L;
    }
    else if ((0 <= simple_strtol(pArg2, NULL, 10)) && (simple_strtol(pArg2, NULL, 10) <= 100))
    {
        DRV_PQ_SetDemoCoordinate(REG_TYPE_VPSS, simple_strtol(pArg2, NULL, 10));
        DRV_PQ_SetDemoCoordinate(REG_TYPE_VDP, simple_strtol(pArg2, NULL, 10));

        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }

    DRV_PQ_SetDemoDispMode(REG_TYPE_VPSS, enDemoMode);
    DRV_PQ_SetDemoDispMode(REG_TYPE_VDP, enDemoMode);

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetTunMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "debug", strlen("debug")))
    {
        DRV_PQ_SetTunMode(PQ_TUN_DEBUG);
        g_stPqStatus.enTunMode = PQ_TUN_DEBUG;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "normal", strlen("normal")))
    {
        DRV_PQ_SetTunMode(PQ_TUN_NORMAL);
        g_stPqStatus.enTunMode = PQ_TUN_NORMAL;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcColorMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
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
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        enColorSpecMode = HI_PQ_COLOR_MODE_ORIGINAL;
    }
    else
    {
        return HI_FAILURE;
    }

    return DRV_PQ_SetColorEnhanceMode(enColorSpecMode);
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

static HI_S32 drv_pq_ProcSetVdpZmeStrategy(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_CHAR achList[8] = "\0";
    HI_PQ_PROC_VDPZME_STRATEGY_S stProcVdpZmeStrategy = {0};
    HI_U32 u32ProcZmeNum = 0;
    HI_U32 u32ProcWDraw = 0;
    HI_U32 u32ProcHDraw = 0;

    if (strlen(pArg2) > 4)
    {
        return HI_FAILURE;
    }

    memset(achList, 0, sizeof(achList));

    /* set vdp zme num :    1 : just use zme1;    0 :  use normal zme number*/
    memcpy(achList, pArg2 , 1);
    u32ProcZmeNum = (HI_U32)simple_strtol(achList, NULL, 10);

    /* set vdp hor draw mode : 0/1/2/4/8;  0:not support proc setting;  */
    memcpy(achList, pArg2 + 1 , 1);
    u32ProcWDraw = (HI_U32)simple_strtol(achList, NULL, 10);

    /* set vdp ver draw mode : 0/1/2/4/8;  0:not support proc setting;  */
    memcpy(achList, pArg2 + 2 , 1);
    u32ProcHDraw = (HI_U32)simple_strtol(achList, NULL, 10);

    if (((HI_PQ_PROC_ZME_NUM_ORI == u32ProcZmeNum) || (HI_PQ_PROC_ZME_NUM_ONLY_ZME1 == u32ProcZmeNum))
        && ((HI_PQ_PROC_PREZME_HOR_ORI == u32ProcWDraw) || (HI_PQ_PROC_PREZME_HOR_1X == u32ProcWDraw)
            || (HI_PQ_PROC_PREZME_HOR_2X == u32ProcWDraw) || (HI_PQ_PROC_PREZME_HOR_4X == u32ProcWDraw)
            || (HI_PQ_PROC_PREZME_HOR_8X == u32ProcWDraw))
        && ((HI_PQ_PROC_PREZME_VER_ORI == u32ProcHDraw) || (HI_PQ_PROC_PREZME_VER_1X == u32ProcHDraw)
            || (HI_PQ_PROC_PREZME_VER_2X == u32ProcHDraw)  || (HI_PQ_PROC_PREZME_VER_4X == u32ProcHDraw)
            || (HI_PQ_PROC_PREZME_VER_8X == u32ProcHDraw)))
    {

        stProcVdpZmeStrategy.enProcVdpZmeNum        = (HI_PQ_PROC_ZME_NUM_E)u32ProcZmeNum;
        stProcVdpZmeStrategy.enProcVdpWidthDrawMode  = (HI_PQ_PROC_PREZME_HOR_MUL_E)u32ProcWDraw;
        stProcVdpZmeStrategy.enProcVdpHeightDrawMode = (HI_PQ_PROC_PREZME_VER_MUL_E)u32ProcHDraw;

        if (PQ_FUNC_CALL(HI_PQ_MODULE_ZME, SetProcVdpZmeStrategy))
        {
            GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetProcVdpZmeStrategy(stProcVdpZmeStrategy);
        }

        return HI_SUCCESS;
    }
    else
    {
#ifdef PQ_PROC_CTRL_SUPPORT
        HI_DRV_PROC_EchoHelper("vdp zme strategy: zme num=%d, WidthDraw=%d, HeightDraw=%d\n", u32ProcZmeNum, u32ProcWDraw, u32ProcHDraw);
#endif
        return HI_FAILURE;
    }
}

static HI_S32 drv_pq_ProcSetFrost(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_PQ_FROST_LEVEL_E enFrostLevel;
    if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        enFrostLevel = HI_PQ_FROST_LEVEL_CLOSE;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "low", strlen("low")))
    {
        enFrostLevel = HI_PQ_FROST_LEVEL_LOW;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "mid", strlen("mid")))
    {
        enFrostLevel = HI_PQ_FROST_LEVEL_MIDDLE;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "high", strlen("high")))
    {
        enFrostLevel = HI_PQ_FROST_LEVEL_HIGH;
    }
    else
    {
        return HI_FAILURE;
    }

    return drv_pq_ProcSetFrostLevel(enFrostLevel);
}

static HI_S32 drv_pq_ProcSetDeiMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_MODULE_E   enModule = HI_PQ_MODULE_FMD;

    if (HI_NULL == PQ_FUNC_CALL(enModule, SetDeiOutMode))
    {
        return HI_FAILURE;
    }

    if (0 == HI_OSAL_Strncmp(pArg2, "auto", strlen("auto")))
    {
        s32Ret = GET_ALG_FUN(enModule)->SetDeiOutMode(PQ_DIE_OUT_MODE_AUTO);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "fir", strlen("fir")))
    {
        s32Ret = GET_ALG_FUN(enModule)->SetDeiOutMode(PQ_DIE_OUT_MODE_FIR);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "copy", strlen("copy")))
    {
        s32Ret = GET_ALG_FUN(enModule)->SetDeiOutMode(PQ_DIE_OUT_MODE_COPY);
    }

    return s32Ret;
}

static HI_S32 drv_pq_ProcSetFodMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_MODULE_E   enModule = HI_PQ_MODULE_FMD;

    if (HI_NULL == PQ_FUNC_CALL(enModule, SetFodMode))
    {
        return HI_FAILURE;
    }

    if (0 == HI_OSAL_Strncmp(pArg2, "auto", strlen("auto")))
    {
        s32Ret = GET_ALG_FUN(enModule)->SetFodMode(PQ_FOD_ENABLE_AUTO);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "top1st", strlen("top1st")))
    {
        s32Ret = GET_ALG_FUN(enModule)->SetFodMode(PQ_FOD_TOP_FIRST);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "bottom1st", strlen("bottom1st")))
    {
        s32Ret = GET_ALG_FUN(enModule)->SetFodMode(PQ_FOD_BOTTOM_FIRST);
    }

    return s32Ret;
}

static HI_S32 drv_pq_ProcSetPrintBin(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = 0;

    if (0 == HI_OSAL_Strncmp(pArg2, "all", strlen("all")))
    {
        drv_pq_ProcPrintTable(PRN_TABLE_ALL, u32Data);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "multi", strlen("multi")))
    {
        drv_pq_ProcPrintTable(PRN_TABLE_MULTI, u32Data);
    }
    else
    {
        u32Data = (HI_U32)simple_strtol(pArg2, NULL, 16);
        drv_pq_ProcPrintTable(PRN_TABLE_SINGLE, u32Data);
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetPrintAlgBin(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = (HI_U32)simple_strtol(pArg2, NULL, 10);

    drv_pq_ProcPrintTable(PRN_TABLE_ALG, u32Data);

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetBin(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (strlen(pArg1) > strlen("setbin"))
    {
        HI_CHAR achList[8] = "\0";
        HI_U8  u8MinLen = MIN2((sizeof(achList) - 1), (strlen(pArg1) - strlen("setbin")));
        HI_U32 u32List  = 0;
        HI_U32 u32Value = 0;

        memcpy(achList, pArg1 + strlen("setbin") , u8MinLen);
        u32List  = (HI_U32)simple_strtol(achList, NULL, 10);
        u32Value = (HI_U32)simple_strtol(pArg2, NULL, 10);

        drv_pq_ProcSetTable(u32List, u32Value);

        return HI_SUCCESS;
    }

    if (0 == HI_OSAL_Strncmp(pArg2, "default", strlen("default")))
    {
        drv_pq_ProcPrintTable(PRN_TABLE_SET_DEFAULT, 0);

        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

static HI_S32 drv_pq_ProcSetHDRCfg(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "default", strlen("default")))
    {
        if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrDefaultCfg))
        {
            GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrDefaultCfg(HI_TRUE);
        }

        return HI_SUCCESS;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "debug", strlen("debug")))
    {
        if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrDefaultCfg))
        {
            GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrDefaultCfg(HI_FALSE);
        }

        return HI_SUCCESS;
    }

    return HI_FAILURE;
}

static HI_S32 drv_pq_ProcSetPrintType(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_U32 u32Data = (HI_U32)simple_strtol(pArg2, NULL, 16);

    PQ_HAL_SetPrintType(u32Data);

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetSceneChange(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
        if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, SetDciScd))
        {
            GET_ALG_FUN(HI_PQ_MODULE_DCI)->SetDciScd(HI_TRUE);
        }
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, SetDciScd))
        {
            GET_ALG_FUN(HI_PQ_MODULE_DCI)->SetDciScd(HI_FALSE);
        }
    }
    else
    {
        return HI_FAILURE;
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

static HI_S32 drv_pq_ProcSetMcnr(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_BOOL bEnableMCNR = HI_TRUE;

    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
        bEnableMCNR = HI_TRUE;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        bEnableMCNR = HI_FALSE;
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_TNR, EnableMCNR))
    {
        GET_ALG_FUN(HI_PQ_MODULE_TNR)->EnableMCNR(bEnableMCNR);
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetHdcp(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_BOOL bHDCPEn = HI_FALSE;

    if (0 == HI_OSAL_Strncmp(pArg2, "on", strlen("on")))
    {
        bHDCPEn = HI_TRUE;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "off", strlen("off")))
    {
        bHDCPEn = HI_FALSE;
    }

    return drv_pq_ProcSetHDCPEn(bHDCPEn);
}

static HI_S32 drv_pq_ProcSetImageMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (0 == HI_OSAL_Strncmp(pArg1, "imagemode", PQ_PROC_CMD_NAMELENGTH))
    {
        if (0 == HI_OSAL_Strncmp(pArg2, "normal", strlen("normal")))
        {
            DRV_PQ_SetImageMode(HI_PQ_IMAGE_MODE_NORMAL);
        }
        else if (0 == HI_OSAL_Strncmp(pArg2, "videophone", strlen("videophone")))
        {
            DRV_PQ_SetImageMode(HI_PQ_IMAGE_MODE_VIDEOPHONE);
        }
        else if (0 == HI_OSAL_Strncmp(pArg2, "gallery", strlen("gallery")))
        {
            DRV_PQ_SetImageMode(HI_PQ_IMAGE_MODE_GALLERY);
        }
    }
    else
    {
        return HI_FAILURE;
    }


    return HI_SUCCESS;
}
static HI_S32 drv_pq_ProcSetColorTemp(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_CHAR achList[8] = "\0";
    HI_U32 u32DateR, u32DateG, u32DateB;
    HI_PQ_COLORTEMPERATURE_S stTemperature = {0};

    if (strlen(pArg2) != 7)
    {
        return HI_FAILURE;
    }

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 , 2);
    u32DateR = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 2 , 2);
    u32DateG = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 4 , 2);
    u32DateB = (HI_U32)simple_strtol(achList, NULL, 10);

#ifdef PQ_PROC_CTRL_SUPPORT
    HI_DRV_PROC_EchoHelper("color temp: R=%d, G=%d, B=%d\n", u32DateR, u32DateG, u32DateB);
#endif
    stTemperature.u32Red   = u32DateR;
    stTemperature.u32Green = u32DateG;
    stTemperature.u32Blue  = u32DateB;

    if (PQ_FUNC_CALL(HI_PQ_MODULE_CSC, SetColorTemp))
    {
        GET_ALG_FUN(HI_PQ_MODULE_CSC)->SetColorTemp(&stTemperature);
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetHdrOffset(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_CHAR achList[8] = "\0";
    HI_PQ_SETHDROFFSET_S stHdrOffset;
    HI_U32 u32Date = 0;

    if (strlen(pArg2) != 17)
    {
        return HI_FAILURE;
    }

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 , 2);
    u32Date = simple_strtol(achList, NULL, 10);
    PQ_CHECK_OVER_RANGE_RE_FAIL(u32Date, HI_PQ_HDR_MODE_BUTT);
    stHdrOffset.enHdrProcessScene = (HI_PQ_HDR_MODE_E)u32Date;

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 2 , 2);
    stHdrOffset.u32Bright = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 4 , 2);
    stHdrOffset.u32Contrast = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 6 , 2);
    stHdrOffset.u32Satu = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 8 , 2);
    stHdrOffset.u32Hue = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 10 , 2);
    stHdrOffset.u32R = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 12 , 2);
    stHdrOffset.u32G = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 14 , 2);
    stHdrOffset.u32B = (HI_U32)simple_strtol(achList, NULL, 10);

    stHdrOffset.u32Bright   = LEVEL2NUM(stHdrOffset.u32Bright);
    stHdrOffset.u32Contrast = LEVEL2NUM(stHdrOffset.u32Contrast);
    stHdrOffset.u32Satu     = LEVEL2NUM(stHdrOffset.u32Satu);
    stHdrOffset.u32Hue      = LEVEL2NUM(stHdrOffset.u32Hue);

    stHdrOffset.u32R   = LEVEL2NUM(stHdrOffset.u32R);
    stHdrOffset.u32G   = LEVEL2NUM(stHdrOffset.u32G);
    stHdrOffset.u32B   = LEVEL2NUM(stHdrOffset.u32B);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrOffset))
    {
        GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrOffset(&stHdrOffset);
    }
    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetGfxHdrOffset(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_CHAR achList[8] = "\0";
    HI_PQ_SETHDROFFSET_S stHdrOffset;
    HI_U32 u32Date = 0;

    if (strlen(pArg2) != 17)
    {
        return HI_FAILURE;
    }

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 , 2);
    u32Date = simple_strtol(achList, NULL, 10);
    PQ_CHECK_OVER_RANGE_RE_FAIL(u32Date, HI_PQ_HDR_MODE_BUTT);
    stHdrOffset.enHdrProcessScene = (HI_PQ_HDR_MODE_E)u32Date;

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 2 , 2);
    stHdrOffset.u32Bright = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 4 , 2);
    stHdrOffset.u32Contrast = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 6 , 2);
    stHdrOffset.u32Satu = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 8 , 2);
    stHdrOffset.u32Hue = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 10 , 2);
    stHdrOffset.u32R = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 12 , 2);
    stHdrOffset.u32G = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 14 , 2);
    stHdrOffset.u32B = (HI_U32)simple_strtol(achList, NULL, 10);

    stHdrOffset.u32Bright   = LEVEL2NUM(stHdrOffset.u32Bright);
    stHdrOffset.u32Contrast = LEVEL2NUM(stHdrOffset.u32Contrast);
    stHdrOffset.u32Satu     = LEVEL2NUM(stHdrOffset.u32Satu);
    stHdrOffset.u32Hue      = LEVEL2NUM(stHdrOffset.u32Hue);

    stHdrOffset.u32R   = LEVEL2NUM(stHdrOffset.u32R);
    stHdrOffset.u32G   = LEVEL2NUM(stHdrOffset.u32G);
    stHdrOffset.u32B   = LEVEL2NUM(stHdrOffset.u32B);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXHDR, SetHdrOffset))
    {
        GET_ALG_FUN(HI_PQ_MODULE_GFXHDR)->SetHdrOffset(&stHdrOffset);
    }
    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetHdrTM(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_CHAR achList[8] = "\0";
    HI_PQ_SETHDROFFSET_S stHdrOffset;
    HI_U32 u32Date = 0;

    if (strlen(pArg2) != 12)
    {
        return HI_FAILURE;
    }

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 , 2);
    u32Date = simple_strtol(achList, NULL, 10);
    PQ_CHECK_OVER_RANGE_RE_FAIL(u32Date, HI_PQ_HDR_MODE_BUTT);
    stHdrOffset.enHdrProcessScene = (HI_PQ_HDR_MODE_E)u32Date;

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 2 , 1);
    stHdrOffset.u32HdrMode = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 3 , 2);
    stHdrOffset.u32ACCdark = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 5 , 2);
    stHdrOffset.u32ACCbrigt = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 7 , 2);
    stHdrOffset.u32darkCv = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 9 , 2);
    stHdrOffset.u32brightCv = (HI_U32)simple_strtol(achList, NULL, 10);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_HDR, SetHdrTMCurve))
    {
        GET_ALG_FUN(HI_PQ_MODULE_HDR)->SetHdrTMCurve(&stHdrOffset);
    }
    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetGfxHdrTM(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_CHAR achList[8] = "\0";
    HI_PQ_SETHDROFFSET_S stHdrOffset;
    HI_U32 u32Date = 0;

    if (strlen(pArg2) != 8)
    {
        return HI_FAILURE;
    }

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 , 2);
    u32Date = simple_strtol(achList, NULL, 10);
    PQ_CHECK_OVER_RANGE_RE_FAIL(u32Date, HI_PQ_HDR_MODE_BUTT);
    stHdrOffset.enHdrProcessScene = (HI_PQ_HDR_MODE_E)u32Date;

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 2 , 1);
    stHdrOffset.u32HdrMode = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 3 , 2);
    stHdrOffset.u32darkCv = (HI_U32)simple_strtol(achList, NULL, 10);

    memset(achList, 0, sizeof(achList));
    memcpy(achList, pArg2 + 5 , 2);
    stHdrOffset.u32brightCv = (HI_U32)simple_strtol(achList, NULL, 10);

    if (PQ_FUNC_CALL(HI_PQ_MODULE_GFXHDR, SetHdrTMCurve))
    {
        GET_ALG_FUN(HI_PQ_MODULE_GFXHDR)->SetHdrTMCurve(&stHdrOffset);
    }
    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetZmeMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    if (HI_NULL == PQ_FUNC_CALL(HI_PQ_MODULE_ZME, SetZmeEnMode))
    {
        return HI_FAILURE;
    }

    if (0 == HI_OSAL_Strncmp(pArg2, "vdpfir", strlen("vdpfir")))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetZmeEnMode(PQ_ZME_MODE_VDP_FIR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "vdpcopy", strlen("vdpcopy")))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetZmeEnMode(PQ_ZME_MODE_VDP_FIR, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "vdpmedon", strlen("vdpmedon")))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetZmeEnMode(PQ_ZME_MODE_VDP_MED, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "vdpmedoff", strlen("vdpmedoff")))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetZmeEnMode(PQ_ZME_MODE_VDP_MED, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "vpssfir", strlen("vpssfir")))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetZmeEnMode(PQ_ZME_MODE_VPSS_FIR, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "vpsscopy", strlen("vercopy")))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetZmeEnMode(PQ_ZME_MODE_VPSS_FIR, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "vpssmedon", strlen("vpssmedon")))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetZmeEnMode(PQ_ZME_MODE_VPSS_MED, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "vpssmedoff", strlen("vpssmedoff")))
    {
        GET_ALG_FUN(HI_PQ_MODULE_ZME)->SetZmeEnMode(PQ_ZME_MODE_VPSS_MED, HI_FALSE);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetAlgCtrlArg1(HI_CHAR *pArg1, HI_PQ_MODULE_E *penModule)
{
    HI_PQ_MODULE_E   enModule = HI_PQ_MODULE_BUTT;

    if (0 == HI_OSAL_Strncmp(pArg1, "fmd", strlen("fmd")))
    {
        enModule = HI_PQ_MODULE_FMD;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "tnr", strlen("tnr")))
    {
        enModule = HI_PQ_MODULE_TNR;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "snr", strlen("snr")))
    {
        enModule = HI_PQ_MODULE_SNR;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "db", strlen("db")))
    {
        enModule = HI_PQ_MODULE_DB;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "dr", strlen("dr")))
    {
        enModule = HI_PQ_MODULE_DR;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "dm", strlen("dm")))
    {
        enModule = HI_PQ_MODULE_DM;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "sharp", strlen("sharp")))
    {
        enModule = HI_PQ_MODULE_SHARPNESS;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "dci", strlen("dci")))
    {
        enModule = HI_PQ_MODULE_DCI;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "acm", strlen("acm")))
    {
        enModule = HI_PQ_MODULE_COLOR;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "csc", strlen("csc")))
    {
        enModule = HI_PQ_MODULE_CSC;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "dei", strlen("dei")))
    {
        enModule = HI_PQ_MODULE_DEI;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "ds", strlen("ds")))
    {
        enModule = HI_PQ_MODULE_DS;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "artds", strlen("artds")))
    {
        enModule = HI_PQ_MODULE_ARTDS;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "gfxcsc", strlen("gfxcsc")))
    {
        enModule = HI_PQ_MODULE_GFXCSC;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "gfxzme", strlen("gfxzme")))
    {
        enModule = HI_PQ_MODULE_GFXZME;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "vpscene", strlen("vpscene")))
    {
        enModule = HI_PQ_MODULE_VPSSCSC;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "vdp4ksnr", strlen("vdp4ksnr")))
    {
        enModule = HI_PQ_MODULE_VDP4KSNR;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "lchdr", strlen("lchdr")))
    {
        enModule = HI_PQ_MODULE_LCHDR;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "all", strlen("all")))
    {
        enModule = HI_PQ_MODULE_ALL;
    }

    *penModule = enModule;

    return HI_SUCCESS;
}


static HI_S32 drv_pq_ProcSetAlgCtrlArg2(HI_PQ_MODULE_E enModule, HI_CHAR *pArg2)
{
    HI_U32 u32Strength = 0;

    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        DRV_PQ_SetPQModule(enModule, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        DRV_PQ_SetPQModule(enModule, HI_FALSE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demoon", strlen("demoon")))
    {
        DRV_PQ_SetDemoMode(enModule, HI_TRUE);
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "demooff", strlen("demooff")))
    {
        DRV_PQ_SetDemoMode(enModule, HI_FALSE);
    }
    else
    {
        u32Strength = simple_strtol(pArg2, NULL, 10);
        if (u32Strength > 100)
        {
            return HI_FAILURE;
        }

        if (PQ_FUNC_CALL(enModule, SetStrength))
        {
            stPqParam.u32Strength[enModule] = u32Strength;
            GET_ALG_FUN(enModule)->SetStrength(u32Strength);
        }
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetVPType(HI_CHAR *pArg1, HI_DRV_PQ_VP_TYPE_E *pEnVPType)
{
    if (0 == HI_OSAL_Strncmp(pArg1, "preview", strlen("preview")))
    {
        *pEnVPType = HI_DRV_PQ_VP_TYPE_PREVIEW;
    }
    else if (0 == HI_OSAL_Strncmp(pArg1, "remote", strlen("remote")))
    {
        *pEnVPType = HI_DRV_PQ_VP_TYPE_REMOTE;
    }
    else
    {
        HI_ERR_PQ("drv_pq_ProcSetVPType type not match!\n");

        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetVPMode(HI_DRV_PQ_VP_TYPE_E enVPType, HI_CHAR *pArg2)
{
    HI_DRV_PQ_VP_MODE_E   enVPSceneMode     = HI_DRV_PQ_VIDEOPHONE_MODE_BUTT;

    if (0 == HI_OSAL_Strncmp(pArg2, "recommed", strlen("recommed")))
    {
        enVPSceneMode = HI_DRV_PQ_VIDEOPHONE_MODE_RECOMMEND;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "black", strlen("black")))
    {
        enVPSceneMode = HI_DRV_PQ_VIDEOPHONE_MODE_BLACK;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "color", strlen("color")))
    {
        enVPSceneMode = HI_DRV_PQ_VIDEOPHONE_MODE_COLORFUL;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "bt", strlen("bt")))
    {
        enVPSceneMode = HI_DRV_PQ_VIDEOPHONE_MODE_BRIGHT;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "warm", strlen("warm")))
    {
        enVPSceneMode = HI_DRV_PQ_VIDEOPHONE_MODE_WARM;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "cool", strlen("cool")))
    {
        enVPSceneMode = HI_DRV_PQ_VIDEOPHONE_MODE_COOL;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "old", strlen("old")))
    {
        enVPSceneMode = HI_DRV_PQ_VIDEOPHONE_MODE_OLD;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "user", strlen("user")))
    {
        enVPSceneMode = HI_DRV_PQ_VIDEOPHONE_MODE_USER;
    }
    else
    {
        enVPSceneMode = HI_DRV_PQ_VIDEOPHONE_MODE_BUTT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enVPType)
    {
        DRV_PQ_SetVPPreviewMode(enVPSceneMode);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enVPType)
    {
        DRV_PQ_SetVPRemoteMode(enVPSceneMode);
    }
    /*else if (HI_DRV_PQ_VP_TYPE_ALL == enVPType)
    {
        DRV_PQ_SetVPPreviewMode(enVPSceneMode);
        DRV_PQ_SetVPRemoteMode(enVPSceneMode);
    }*/
    /*printk("__LINE__ == %d\n", __LINE__);*/
    return HI_SUCCESS;
}

static HI_S32 drv_pq_ProcSetAlgCtrl(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_PQ_MODULE_E   enModule = HI_PQ_MODULE_BUTT;

    drv_pq_ProcSetAlgCtrlArg1(pArg1, &enModule);
    if (enModule == HI_PQ_MODULE_BUTT)
    {
        return HI_FAILURE;
    }

    return drv_pq_ProcSetAlgCtrlArg2(enModule, pArg2);
}

static HI_S32 drv_pq_ProcSetParaCtrl(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_S32  s32Ret = HI_SUCCESS;
    HI_U32  u32StreamIdSetMode = HI_TRUE;

    if (0 != HI_OSAL_Strncmp(pArg1, "para", strlen("para")))
    {
        return HI_FAILURE;
    }

    if (0 == HI_OSAL_Strncmp(pArg2, "enable", strlen("enable")))
    {
        u32StreamIdSetMode = HI_TRUE;
    }
    else if (0 == HI_OSAL_Strncmp(pArg2, "disable", strlen("disable")))
    {
        u32StreamIdSetMode = HI_FALSE;
    }
    else
    {
        return HI_FAILURE;
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_SHARPNESS, SetStreamSetON))
    {
        s32Ret = GET_ALG_FUN(HI_PQ_MODULE_SHARPNESS)->SetStreamSetON(u32StreamIdSetMode);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DCI, SetStreamSetON))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_DCI)->SetStreamSetON(u32StreamIdSetMode);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DM, SetStreamSetON))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_DM)->SetStreamSetON(u32StreamIdSetMode);
    }

    if (PQ_FUNC_CALL(HI_PQ_MODULE_DEI, SetStreamSetON))
    {
        s32Ret |= GET_ALG_FUN(HI_PQ_MODULE_DEI)->SetStreamSetON(u32StreamIdSetMode);
    }

    return s32Ret;
}

static HI_S32 drv_pq_ProcSetProcLevelCtrl(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_S32  s32Ret              = HI_FAILURE;
    HI_U32  u32PqProcPrintLevel = 0;
    HI_BOOL bProcPrintLevelEn   = HI_FALSE;

    if (0 == HI_OSAL_Strncmp(pArg1, "proc", PQ_PROC_CMD_NAMELENGTH))
    {
        u32PqProcPrintLevel = (HI_U32)simple_strtol(pArg2, NULL, 10);

        PQ_CHECK_OVER_RANGE_RE_FAIL(u32PqProcPrintLevel, PPQ_ROC_PRINT_BUTT);

        sg_enPqProcPrintLevel = (PQ_PROC_PRINT_LEVEL_E)u32PqProcPrintLevel;
    }

    if (PQ_PROC_PRINT_LEVEL3 == sg_enPqProcPrintLevel)
    {
        bProcPrintLevelEn = HI_TRUE;
    }

    s32Ret = DRV_PQ_SetProcAlgTimeCntEn(bProcPrintLevelEn);

    return s32Ret;
}

static HI_S32 drv_pq_ProcSetVPTypeMode(HI_CHAR *pArg1, HI_CHAR *pArg2)
{
    HI_DRV_PQ_VP_TYPE_E enVPType = HI_DRV_PQ_VP_TYPE_BUTT;

    drv_pq_ProcSetVPType(pArg1, &enVPType);

    return drv_pq_ProcSetVPMode(enVPType, pArg2);
}

