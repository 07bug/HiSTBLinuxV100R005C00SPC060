/******************************************************************************
 Copyright (C), 2014-2016, Hisilicon Tech. Co. Ltd.
******************************************************************************
File Name     : pq_mng_sharpen.c
Version       : Initial Draft
Author        : sdk
Created       : 2014/06/19
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <linux/slab.h>      /* kmalloc() */
#include <linux/string.h>
#include <linux/fcntl.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "drv_pq_define.h"

#include "pq_hal_comm.h"
#include "pq_mng_sharpen.h"
#include "drv_pq_table.h"

#define S10TOS16(x) ((x>511)?(x-1024):(x))

static ALG_SHARPEN_S sg_stPQSharpenInfo;

/* if table has set para or the scene, then use table para; else use these para */
static HI_U32 sg_u32PeakGain[PQ_SOURCE_MODE_BUTT][PQ_OUTPUT_MODE_BUTT] =
{
    {256, 256, 256, 256, 400, 400}, /* PQ_SOURCE_MODE_NO  */
    {256, 256, 352, 512, 400, 400}, /* PQ_SOURCE_MODE_SD  */
    {256, 256, 256, 256, 400, 400}, /* PQ_SOURCE_MODE_HD  */
    {80,  80,   80,  80, 80, 80}, /* PQ_SOURCE_MODE_UHD */
};

static HI_U32 sg_u32EdgeGain[PQ_SOURCE_MODE_BUTT][PQ_OUTPUT_MODE_BUTT] =
{
    {128, 128, 128, 128, 256, 256}, /* PQ_SOURCE_MODE_NO  */
    {128, 128, 176, 256, 256, 256}, /* PQ_SOURCE_MODE_SD  */
    {128, 128, 128, 128, 256, 256}, /* PQ_SOURCE_MODE_HD  */
    { 40,  40,  40,  40, 40,  40}, /* PQ_SOURCE_MODE_UHD */
};

static HI_S32 PQ_MNG_FindSharpenGainRatio(HI_U32 ppu32Gain[][PQ_OUTPUT_MODE_BUTT], HI_U32 u32RegAddr, HI_U8 u8GainLsb, HI_U8 u8GainMsb)
{
    HI_U32 u32Addr, u32Value;
    PQ_PHY_REG_S *sg_pstPhyReg   = HI_NULL;
    HI_U32 i;
    HI_U8  u8Lsb, u8Msb, u8SourceMode, u8OutputMode;
    HI_U32 u32StartPos = 0;
    HI_U32 u32EndPos   = 0;

    PQ_CHECK_NULL_PTR_RE_FAIL(sg_stPQSharpenInfo.pstParam);
    sg_pstPhyReg = sg_stPQSharpenInfo.pstParam->stPQPhyReg;

    PQ_TABLE_FindBinPos(HI_PQ_MODULE_SHARPNESS, &u32StartPos, &u32EndPos);

    for (i = u32StartPos; i <= u32EndPos; i++)
    {
        u32Addr       = sg_pstPhyReg[i].u32RegAddr;
        u32Value      = sg_pstPhyReg[i].u32Value;
        u8Lsb         = sg_pstPhyReg[i].u8Lsb;
        u8Msb         = sg_pstPhyReg[i].u8Msb;
        u8SourceMode  = sg_pstPhyReg[i].u8SourceMode;
        u8OutputMode  = sg_pstPhyReg[i].u8OutputMode;

        if (u32Addr != SHARP_PEAK_GAIN_ADDR)
        {
            continue;
        }
        if (u8Lsb != SHARP_PEAK_GAIN_LSB)
        {
            continue;
        }
        if (u8Msb != SHARP_PEAK_GAIN_MSB)
        {
            continue;
        }

        if ((PQ_SOURCE_MODE_BUTT <= u8SourceMode) || (PQ_OUTPUT_MODE_BUTT <= u8OutputMode))
        {
            continue;
        }

        sg_stPQSharpenInfo.pPeakGain[u8SourceMode][u8OutputMode] = u32Value;
        pqprint(PQ_PRN_SHARPEN, "GetPeakGainRatio:%d, SourceMode:%d, OutputMode:%d\n", u32Value, u8SourceMode, u8OutputMode);
    }

    for (i = u32StartPos; i <= u32EndPos; i++)
    {
        u32Addr       = sg_pstPhyReg[i].u32RegAddr;
        u32Value      = sg_pstPhyReg[i].u32Value;
        u8Lsb         = sg_pstPhyReg[i].u8Lsb;
        u8Msb         = sg_pstPhyReg[i].u8Msb;
        u8SourceMode  = sg_pstPhyReg[i].u8SourceMode;
        u8OutputMode  = sg_pstPhyReg[i].u8OutputMode;

        if (u32Addr != SHARP_EDGE_GAIN_ADDR)
        {
            continue;
        }
        if (u8Lsb != SHARP_EDGE_GAIN_LSB)
        {
            continue;
        }
        if (u8Msb != SHARP_EDGE_GAIN_MSB)
        {
            continue;
        }

        if ((PQ_SOURCE_MODE_BUTT <= u8SourceMode) || (PQ_OUTPUT_MODE_BUTT <= u8OutputMode))
        {
            continue;
        }
        sg_stPQSharpenInfo.pEdgeGain[u8SourceMode][u8OutputMode] = u32Value;
        pqprint(PQ_PRN_SHARPEN, "GetEdgeGainRatio:%d, SourceMode:%d, OutputMode:%d\n", u32Value, u8SourceMode, u8OutputMode);
    }
    return HI_SUCCESS;
}

static HI_S32 PQ_MNG_FindSharpGain(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret  = PQ_MNG_FindSharpenGainRatio(sg_stPQSharpenInfo.pPeakGain, SHARP_PEAK_GAIN_ADDR, SHARP_PEAK_GAIN_LSB, SHARP_PEAK_GAIN_MSB);
    s32Ret |= PQ_MNG_FindSharpenGainRatio(sg_stPQSharpenInfo.pEdgeGain, SHARP_EDGE_GAIN_ADDR, SHARP_EDGE_GAIN_LSB, SHARP_EDGE_GAIN_MSB);

    return s32Ret;
}

/* Deinit Sharp Moudle */
HI_S32 PQ_MNG_DeInitSharpen(HI_VOID)
{
    if (HI_FALSE == sg_stPQSharpenInfo.bInit)
    {
        return HI_SUCCESS;
    }

    sg_stPQSharpenInfo.bInit = HI_FALSE;

    return HI_SUCCESS;
}

/* Deinit Sharp Moudle (Include Sharpen and HSharpen) */
HI_S32 PQ_MNG_InitSharpen(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Data = 0;

    if (HI_TRUE == sg_stPQSharpenInfo.bInit)
    {
        return HI_SUCCESS;
    }

    sg_stPQSharpenInfo.bEnable      = HI_TRUE;
    sg_stPQSharpenInfo.u32Strength  = 50;
    sg_stPQSharpenInfo.bDemoEnable  = HI_FALSE;
    sg_stPQSharpenInfo.eDemoMode    = PQ_DEMO_ENABLE_L;
    sg_stPQSharpenInfo.pstParam     = pstPqParam;
    sg_stPQSharpenInfo.pPeakGain    = sg_u32PeakGain;
    sg_stPQSharpenInfo.pEdgeGain    = sg_u32EdgeGain;
    sg_stPQSharpenInfo.u32StreamId  = 0; //no special para
    sg_stPQSharpenInfo.u32StreamIdSetMode  = HI_TRUE; //Default Para On

    memset(&(sg_stPQSharpenInfo.stSharpReso), 0, sizeof(sg_stPQSharpenInfo.stSharpReso));

    s32Ret = PQ_TABLE_InitPhyList(u32Data, HI_PQ_MODULE_SHARPNESS, PQ_SOURCE_MODE_HD, PQ_OUTPUT_MODE_NO);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Sharpen InitPhyList error\n");
        sg_stPQSharpenInfo.bInit = HI_FALSE;

        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_FindSharpGain();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("FindSharpGain error\n");
        sg_stPQSharpenInfo.bInit = HI_FALSE;

        return s32Ret;
    }

    sg_stPQSharpenInfo.bInit = HI_TRUE;

    return s32Ret;
}

/* Set Sharpen Strength, Range: 0~100;
   说明: UI菜单设置直接调用，根据当前的源和输出信息将设置的s32ShpStr(0-100)值混合Bin文件的Gain值设置Sharpen强度
   */
HI_S32 PQ_MNG_SetSharpenStr(HI_U32 u32ShpStr)
{
    HI_U32 u32ShpStrTmp;
    HI_U32 u32PeakGain, u32EdgeGain;
    HI_BOOL bDetecEn = HI_TRUE;
    PQ_SHARP_GAIN_S stSharpGain;
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();
    PQ_OUTPUT_MODE_E enOutMode = PQ_COMM_GetOutputMode();

    if (100 < u32ShpStr)
    {
        HI_ERR_PQ("the value of setting sharpen strength [%d] is out of range!\n", u32ShpStr);
        return HI_FAILURE;
    }

    sg_stPQSharpenInfo.u32Strength = u32ShpStr;
    u32ShpStrTmp = LEVEL2NUM(u32ShpStr);

    PQ_CHECK_OVER_RANGE_RE_FAIL(enSourceMode, PQ_SOURCE_MODE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(enOutMode, PQ_OUTPUT_MODE_BUTT);

    stSharpGain.u32PeakGain = sg_stPQSharpenInfo.pPeakGain[enSourceMode][enOutMode];
    stSharpGain.u32EdgeGain = sg_stPQSharpenInfo.pEdgeGain[enSourceMode][enOutMode];

    u32PeakGain = (stSharpGain.u32PeakGain * u32ShpStrTmp + 64) / 128;
    u32EdgeGain = (stSharpGain.u32EdgeGain * u32ShpStrTmp + 64) / 128;

    if (HI_TRUE == sg_stPQSharpenInfo.u32StreamIdSetMode)
    {
        /* stream Id : 1 */
        if (0x67 == sg_stPQSharpenInfo.u32StreamId)
        {
            u32PeakGain = 1000;

            bDetecEn = HI_FALSE;
        }
        /* stream Id : 2 */
        if (0x68 == sg_stPQSharpenInfo.u32StreamId)
        {
            u32PeakGain = 700;
            u32EdgeGain = 600;

            bDetecEn = HI_TRUE;
        }
    }

    PQ_HAL_SetSharpDetecEn(PQ_VDP_LAYER_VID0, bDetecEn);

    PQ_HAL_SetSharpStrReg(PQ_VDP_LAYER_VID0, u32PeakGain, u32EdgeGain);

    return HI_SUCCESS;
}

/* Get Sharpen Strength, Range: 0~100 */
HI_S32 PQ_MNG_GetSharpenStr(HI_U32 *pu32ShpStr)
{
    *pu32ShpStr = sg_stPQSharpenInfo.u32Strength;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetSharpDisableByReso(HI_VOID)
{
#if defined(SHARPEN_FHD_SUPPORT)
    /*
    1 : src = 4K, close sharp
    2 : 1080P < SRC < 4K : close sharp
    3 : if(src <= 1080P)
            if (intf >= 2160P)
                if (zme2 out != zme2 in)
                    if (zme2 out >= zme2 in * 1.6) //both w and h
                        not close sharp
                    else
                        close sharp
                else if ((zme1 out w > 1920) ||(zme1 out h > 1080)
                    close sharp
                else
                    not close sharp
                ===============
                if (zme2 out <= 0.75*intf)
                  close sharp
                else
                  not close sharp
            else
                not close sharp
    */
    if ((sg_stPQSharpenInfo.stSharpReso.stSrcReso.s32Width > SHARP_DHD1_OUT_1080P_W_THD)
        || (sg_stPQSharpenInfo.stSharpReso.stSrcReso.s32Height > SHARP_DHD1_OUT_1080P_H_THD))
    {
        sg_stPQSharpenInfo.bEnable = HI_FALSE;
    }
    else if (sg_stPQSharpenInfo.stSharpReso.stIntfReso.s32Height >= SHARP_DHD1_OUT_4K_H_THD)
    {
        if ((sg_stPQSharpenInfo.stSharpReso.stZme2OutReso.s32Width != sg_stPQSharpenInfo.stSharpReso.stZme2InReso.s32Width)
            && (sg_stPQSharpenInfo.stSharpReso.stZme2OutReso.s32Height != sg_stPQSharpenInfo.stSharpReso.stZme2InReso.s32Height))
        {
            if ((sg_stPQSharpenInfo.stSharpReso.stZme2OutReso.s32Width * 5 >= sg_stPQSharpenInfo.stSharpReso.stZme2InReso.s32Width * 8)
                && (sg_stPQSharpenInfo.stSharpReso.stZme2OutReso.s32Height * 5 >= sg_stPQSharpenInfo.stSharpReso.stZme2InReso.s32Height * 8))
            {
                //do nothing
            }
            else
            {
                sg_stPQSharpenInfo.bEnable = HI_FALSE;
            }
        }
        else if ((sg_stPQSharpenInfo.stSharpReso.stZme1OutReso.s32Width > SHARP_SUPPORT_MAX_W)
                 || (sg_stPQSharpenInfo.stSharpReso.stZme1OutReso.s32Height > SHARP_SUPPORT_MAX_H))
        {
            sg_stPQSharpenInfo.bEnable = HI_FALSE;
        }
        if (sg_stPQSharpenInfo.stSharpReso.stZme2OutReso.s32Width * 4 <= sg_stPQSharpenInfo.stSharpReso.stIntfReso.s32Width * 3
            || sg_stPQSharpenInfo.stSharpReso.stZme2OutReso.s32Height * 4 <= sg_stPQSharpenInfo.stSharpReso.stIntfReso.s32Height * 3)
        {
            sg_stPQSharpenInfo.bEnable = HI_FALSE;

        }
    }
#endif

    return HI_SUCCESS;
}

/* Enable Sharpen Moudle(Sharpen and HSharpen) */
HI_S32 PQ_MNG_SetSharpenEn(HI_BOOL bOnOff)
{
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();
    PQ_OUTPUT_MODE_E enOutputMode = PQ_COMM_GetOutputMode();

    HI_UNUSED(enOutputMode);

    sg_stPQSharpenInfo.bEnable = bOnOff;

    if ((enSourceMode < PQ_SOURCE_MODE_BUTT)
        && (HI_FALSE == PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_SHARPNESS, enSourceMode)))
    {
        sg_stPQSharpenInfo.bEnable = HI_FALSE;
    }
    // PQ_MNG_SetSharpDisableByReso();

    PQ_HAL_EnableSharp(sg_stPQSharpenInfo.bEnable);
#if defined(SHARPEN_CFG_STYLE_COEF)
    PQ_HAL_PARA_SetParaAddrVhdChn04(g_stSharpCfgBuff.u32StartPhyAddr);
#endif

    return HI_SUCCESS;
}

/* Get Sharpen Enable(Sharpen and HSharpen) */
HI_S32 PQ_MNG_GetSharpenEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbOnOff);

    *pbOnOff = sg_stPQSharpenInfo.bEnable;

    return HI_SUCCESS;
}

/* Enable Sharpen Demo(Sharpen and HSharpen) */
HI_S32 PQ_MNG_SetSharpenDemoEn(HI_BOOL bOnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;

#if defined(SHARPEN_FHD_SUPPORT)
    sg_stPQSharpenInfo.bDemoEnable = HI_FALSE;
#else
    sg_stPQSharpenInfo.bDemoEnable = bOnOff;
#endif

    s32Ret = PQ_HAL_EnableSharpDemo(PQ_VDP_LAYER_VID0, sg_stPQSharpenInfo.bDemoEnable);

    return s32Ret;
}

HI_S32 PQ_MNG_GetSharpenDemoEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbOnOff);

    *pbOnOff = sg_stPQSharpenInfo.bDemoEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetSharpDemoMode(PQ_DEMO_MODE_E enMode)
{
    SHARP_DEMO_MODE_E enSharpMode = SHARP_DEMO_ENABLE_L;

    sg_stPQSharpenInfo.eDemoMode = enMode;

    if (enMode == PQ_DEMO_ENABLE_L)
    {
        enSharpMode = SHARP_DEMO_ENABLE_L;
    }
    else if (enMode == PQ_DEMO_ENABLE_R)
    {
        enSharpMode = SHARP_DEMO_ENABLE_R;
    }

    PQ_HAL_SetSharpDemoMode(PQ_VDP_LAYER_VID0, enSharpMode);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetSharpDemoMode(PQ_DEMO_MODE_E *penMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(penMode);

    *penMode = sg_stPQSharpenInfo.eDemoMode;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetSharpDemoModeCoor(HI_U32 u32XPos)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_HAL_SetSharpDemoPos(PQ_VDP_LAYER_VID0, u32XPos);

    return s32Ret;
}

HI_S32 PQ_MNG_SetSharpResoInfo(HI_PQ_SHARP_RESO_S *pstSharpReso)
{
    memcpy(&(sg_stPQSharpenInfo.stSharpReso), pstSharpReso, sizeof(sg_stPQSharpenInfo.stSharpReso));

    PQ_MNG_SetSharpDisableByReso();

    PQ_HAL_EnableSharp(sg_stPQSharpenInfo.bEnable);

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetSharpStreamId(HI_U32 u32StreamId)
{
    HI_U32 u32PeakGain, u32EdgeGain;
    HI_BOOL bDetecEn = HI_TRUE; // Default True

    sg_stPQSharpenInfo.u32StreamId  = u32StreamId; //special para
    if (HI_TRUE == sg_stPQSharpenInfo.u32StreamIdSetMode)
    {
        /* stream Id : 1 */
        if (0x67 == sg_stPQSharpenInfo.u32StreamId)
        {
            u32PeakGain = 1000;
            PQ_HAL_SetSharpPeakGain(PQ_VDP_LAYER_VID0, u32PeakGain);

            bDetecEn = HI_FALSE;
        }
        /* stream Id : 2 */
        if (0x68 == sg_stPQSharpenInfo.u32StreamId)
        {
            u32PeakGain = 700;
            u32EdgeGain = 600;
            //u32PeakGain = 1000;
            //u32EdgeGain = 900;
            PQ_HAL_SetSharpStrReg(PQ_VDP_LAYER_VID0, u32PeakGain, u32EdgeGain);

            bDetecEn = HI_TRUE;
        }

        PQ_HAL_SetSharpDetecEn(PQ_VDP_LAYER_VID0, bDetecEn);
    }
    else
    {
        PQ_MNG_SetSharpenStr(sg_stPQSharpenInfo.u32Strength);
    }

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_SetSharpStreamIdSetEnable(HI_U32 u32StreamIdSetMode)
{
    sg_stPQSharpenInfo.u32StreamIdSetMode = u32StreamIdSetMode;


    return HI_SUCCESS;
}

static stPQAlgFuncs stSharpFuncs =
{
    .Init            = PQ_MNG_InitSharpen,
    .DeInit          = PQ_MNG_DeInitSharpen,
    .SetEnable       = PQ_MNG_SetSharpenEn,
    .GetEnable       = PQ_MNG_GetSharpenEn,
    .SetDemo         = PQ_MNG_SetSharpenDemoEn,
    .GetDemo         = PQ_MNG_GetSharpenDemoEn,
    .SetDemoMode     = PQ_MNG_SetSharpDemoMode,
    .GetDemoMode     = PQ_MNG_GetSharpDemoMode,
    .SetDemoModeCoor = PQ_MNG_SetSharpDemoModeCoor,
    .SetStrength     = PQ_MNG_SetSharpenStr,
    .GetStrength     = PQ_MNG_GetSharpenStr,
    .SetSharpResoInfo = PQ_MNG_SetSharpResoInfo,
    .SetStreamId      = PQ_MNG_SetSharpStreamId,
    .SetStreamSetON   = PQ_MNG_SetSharpStreamIdSetEnable,
};

HI_S32 PQ_MNG_RegisterSharp(PQ_REG_TYPE_E  enType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_SHARPNESS, enType, PQ_BIN_ADAPT_MULTIPLE, "sharp", HI_NULL, &stSharpFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterSharp(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_SHARPNESS);

    return s32Ret;
}

