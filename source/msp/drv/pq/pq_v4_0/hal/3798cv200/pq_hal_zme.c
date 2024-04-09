/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_zme.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2014/04/01
  Author        : sdk
******************************************************************************/
#include <linux/fs.h>

#include "pq_hal_zme.h"
#include "pq_mng_zme_coef.h"

#define V0_SCALER1_ENABLE_THD       2
#define V0_READ_FMT_ZME_THD         3
#define V0_PREZME_ENABLE_2_THD      6
#define V0_PREZME_ENABLE_4_THD      12
#define V0_PREZME_ENABLE_8_THD      24
#define WBC_HSCALER_THD             4
#define DHD0_OUT_RESOLUTION_W_THD   3840
#define DHD0_OUT_RESOLUTION_H_THD   2160

static S_VDP_REGS_TYPE *pVdpReg;

static HI_BOOL sg_bV0ReadFmtIn = HI_TRUE;
static HI_PQ_PREZME_HOR_MUL_E    sg_enV0PreHScaler   = HI_PQ_PREZME_HOR_DISABLE;
static HI_PQ_PREZME_VER_MUL_E    sg_enV0PreVScaler   = HI_PQ_PREZME_VER_DISABLE;
static HI_PQ_FROST_LEVEL_E       sg_enProcFrostLevel  = HI_PQ_FROST_LEVEL_CLOSE;
static HI_PQ_WBC_VP_POINT_SEL_E  sg_enWbcVpPointSel  = HI_PQ_WBC_VP_POINT_V0;

static HI_BOOL g_bHalVdpZmeFirEn  = HI_TRUE;
static HI_BOOL g_bHalVdpZmeMedEn  = HI_FALSE;
static HI_BOOL sg_bVpssZmeDefault = HI_FALSE;
static HI_BOOL sg_bVdpZmeDefault  = HI_FALSE;

static HI_PQ_PROC_VDPZME_STRATEGY_S sg_stSetPqProcVdpZmeStrategy = {0};
static HI_PQ_PROC_VDPZME_STRATEGY_S sg_stGetPqProcVdpZmeStrategy = {0};
static HI_PQ_PROC_VDPZME_RESO_S     sg_stProcVdpZmeReso          = {{0}};
static HI_PQ_PROC_WBC_STRATEGY_S    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_BUTT] = {{0}};

static HI_U32 sg_u32StreamId = 0;

/****************************Load VDP ZME COEF START*****************************************/
static HI_S32 VdpZmeTransCoefAlign(const HI_S16 *ps16Coef, VZME_TAP_E enTap, ZME_COEF_BITARRAY_S *pBitCoef)
{
    HI_U32 i, u32Cnt, u32Tap, u32Tmp;

    switch (enTap)
    {
        case VZME_TAP_8T32P:
            u32Tap = 8;
            break;
        case VZME_TAP_6T32P:
            u32Tap = 6;
            break;
        case VZME_TAP_4T32P:
            u32Tap = 4;
            break;
        default:
            u32Tap = 4;
            break;
    }

    /* Tran ZME coef to 128 bits order */
    u32Cnt = 18 * u32Tap / 12;
    for (i = 0; i < u32Cnt; i++)
    {
        pBitCoef->stBit[i].bits_0 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_1 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_2 = VouBitValue(*ps16Coef++);

        u32Tmp = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_32 = u32Tmp;
        pBitCoef->stBit[i].bits_38 = (u32Tmp >> 2);

        pBitCoef->stBit[i].bits_4 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_5 = VouBitValue(*ps16Coef++);

        u32Tmp = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_64 = u32Tmp;
        pBitCoef->stBit[i].bits_66 = u32Tmp >> 4;

        pBitCoef->stBit[i].bits_7 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_8 = VouBitValue(*ps16Coef++);

        u32Tmp = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_96 = u32Tmp;
        pBitCoef->stBit[i].bits_94 = u32Tmp >> 6;

        pBitCoef->stBit[i].bits_10 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_11 = VouBitValue(*ps16Coef++);
        pBitCoef->stBit[i].bits_12 = 0;
    }

    pBitCoef->u32Size = u32Cnt * sizeof(ZME_COEF_BIT_S);

    return HI_SUCCESS;
}

/* load hor coef */
static HI_S32 VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_RATIO_E enCoefRatio, VZME_COEF_TYPE_E enCoefType, VZME_TAP_E enZmeTap, HI_U8 *pu8Addr)
{
    ZME_COEF_BITARRAY_S stArray;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu8Addr);

    /* load horizontal zoom coef */
    VdpZmeTransCoefAlign(g_pVZmeCoef[enCoefRatio][enCoefType], enZmeTap, &stArray);

    PQ_CHECK_NULL_PTR_RE_FAIL(pu8Addr + stArray.u32Size);

    PQ_SAFE_MEMCPY(pu8Addr, stArray.stBit, stArray.u32Size);

    return HI_SUCCESS;
}

/* load vert coef */
static HI_S32 VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_RATIO_E enCoefRatio, VZME_COEF_TYPE_E enCoefType, VZME_TAP_E enZmeTap, HI_U8 *pu8Addr)
{
    ZME_COEF_BITARRAY_S stArray;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu8Addr);

    /* load vertical zoom coef */
    VdpZmeTransCoefAlign(g_pVZmeCoef[enCoefRatio][enCoefType], enZmeTap, &stArray);

    PQ_CHECK_NULL_PTR_RE_FAIL(pu8Addr + stArray.u32Size);

    PQ_SAFE_MEMCPY(pu8Addr, stArray.stBit, stArray.u32Size);

    return HI_SUCCESS;
}

HI_VOID PQ_HAL_VdpLoadCoef(ALG_VZME_MEM_S *pstVZmeCoefMem)
{
    HI_U8 *pu8CurAddr;
    HI_U32 u32PhyAddr;
    HI_U32 u32NumSizeLuma, u32NumSizeChro;
    ALG_VZME_COEF_ADDR_S *pstAddrTmp;

    pu8CurAddr = pstVZmeCoefMem->stMBuf.pu8StartVirAddr;
    u32PhyAddr = pstVZmeCoefMem->stMBuf.u32StartPhyAddr;
    pstAddrTmp = &(pstVZmeCoefMem->stZmeCoefAddr);

    /* H_L8C4:Luma-Hor-8T32P Chroma-Hor-4T32P */
    u32NumSizeLuma = 192; /* (8x18) / 12 * 16 = 192 */
    u32NumSizeChro = 96;  /* (4x18) / 12 * 16 = 96 */
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_1, VZME_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_1 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrHL8C4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_1, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_E1, VZME_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_E1 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrHL8C4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_E1, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_075, VZME_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_075 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrHL8C4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_075, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_05, VZME_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_05 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrHL8C4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_05, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_033, VZME_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_033 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrHL8C4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_033, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_025, VZME_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_025 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrHL8C4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_025, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_0, VZME_COEF_8T32P_LH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_0 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrHL8C4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_0, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    /* V_L6C4:Luma-Vert-6T32P Chroma-Vert-4T32P */
    u32NumSizeLuma = 144;  /* (6x18) / 12 * 16 = 144 */
    u32NumSizeChro = 96;   /* (4x18) / 12 * 16 = 96 */
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_1, VZME_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_1 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL6C4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_1, VZME_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_E1, VZME_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_E1 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL6C4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_E1, VZME_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_075, VZME_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_075 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL6C4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_075, VZME_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_05, VZME_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_05 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL6C4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_05, VZME_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, VZME_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_033 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL6C4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, VZME_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_025, VZME_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_025 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL6C4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, VZME_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_0, VZME_COEF_6T32P_LV, VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL6_0 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL6C4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_0, VZME_COEF_4T32P_CV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    /* V_L4C4:Luma-Vert-4T32P Chroma-Vert-4T32P */
    u32NumSizeLuma = 96; /*(4x18) / 12 * 16 */
    u32NumSizeChro = 96; /*(4x18) / 12 * 16 */
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_1, VZME_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_1 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL4C4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_1, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_E1, VZME_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_E1 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL4C4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_E1, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_075, VZME_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_075 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL4C4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_075, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_05, VZME_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_05 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL4C4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_05, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, VZME_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_033 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL4C4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_033, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_025, VZME_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_025 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL4C4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_025, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_0, VZME_COEF_4T32P_LV,  VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_0 = u32PhyAddr;
    pstAddrTmp->u32ZmeCoefAddrVL4C4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeLuma;
    pu8CurAddr  += u32NumSizeLuma;
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_0, VZME_COEF_4T32P_CH, VZME_TAP_4T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    /* Chroma-Hor-8T32P */
    u32NumSizeChro = 192; /* (8x18) / 12 * 16 = 192 */
    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_1, VZME_COEF_8T32P_CH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC8_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_E1, VZME_COEF_8T32P_CH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC8_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_075, VZME_COEF_8T32P_CH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC8_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_05, VZME_COEF_8T32P_CH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC8_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_033, VZME_COEF_8T32P_CH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC8_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_025, VZME_COEF_8T32P_CH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC8_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefH(PQ_HAL_ZME_COEF_0, VZME_COEF_8T32P_CH, VZME_TAP_8T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC8_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    /* Chroma-Vert-6T32P */
    u32NumSizeChro = 144; /* (6x18) / 12 * 16 = 144 */
    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_1, VZME_COEF_6T32P_CV,  VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC6_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_E1, VZME_COEF_6T32P_CV,  VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC6_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_075, VZME_COEF_6T32P_CV,  VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC6_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_05, VZME_COEF_6T32P_CV,  VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC6_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_033, VZME_COEF_6T32P_CV,  VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC6_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_025, VZME_COEF_6T32P_CV,  VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC6_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSizeChro;
    pu8CurAddr  += u32NumSizeChro;

    VdpZmeLoadCoefV(PQ_HAL_ZME_COEF_0, VZME_COEF_6T32P_CV,  VZME_TAP_6T32P, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC6_0 = u32PhyAddr;

    return;
}
/*****************************Load VDP ZME COEF END*****************************************/


/*******************************WBC ZME START***************************************/
static HI_VOID PQ_HAL_WBC_SetZmePhaseH(VDP_LAYER_WBC_E enLayer, HI_S32 s32PhaseL, HI_S32 s32PhaseC)
{
    U_WBC_DHD0_ZME_HLOFFSET WBC_DHD0_ZME_HLOFFSET;
    U_WBC_DHD0_ZME_HCOFFSET WBC_DHD0_ZME_HCOFFSET;

    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 )
    {
        /* VHD layer zoom enable */
        WBC_DHD0_ZME_HLOFFSET.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32)));
        WBC_DHD0_ZME_HLOFFSET.bits.hor_loffset = s32PhaseL;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32))), WBC_DHD0_ZME_HLOFFSET.u32);

        WBC_DHD0_ZME_HCOFFSET.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32)));
        WBC_DHD0_ZME_HCOFFSET.bits.hor_coffset = s32PhaseC;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32))), WBC_DHD0_ZME_HCOFFSET.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {}

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmePhaseV(VDP_LAYER_WBC_E enLayer, HI_S32 s32PhaseL, HI_S32 s32PhaseC)
{
    U_WBC_DHD0_ZME_VOFFSET WBC_DHD0_ZME_VOFFSET;
    pVdpReg = PQ_HAL_GetVdpReg();

    if (enLayer == VDP_LAYER_WBC_HD0 )
    {
        /* VHD layer zoom enable */
        WBC_DHD0_ZME_VOFFSET.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&pVdpReg->WBC_DHD0_ZME_VOFFSET.u32)));
        WBC_DHD0_ZME_VOFFSET.bits.vluma_offset = s32PhaseL;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32))), WBC_DHD0_ZME_VOFFSET.u32);

        WBC_DHD0_ZME_VOFFSET.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&pVdpReg->WBC_DHD0_ZME_VOFFSET.u32)));
        WBC_DHD0_ZME_VOFFSET.bits.vchroma_offset = s32PhaseC;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32))), WBC_DHD0_ZME_VOFFSET.u32);
    }
    else if (enLayer == VDP_LAYER_WBC_GP0)
    {}

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeHorRatio(VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;

    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
        WBC_DHD0_ZME_HSP.bits.hratio = u32Ratio;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeVerRatio(VDP_LAYER_WBC_E enLayer, HI_U32 u32Ratio)
{
    U_WBC_DHD0_ZME_VSR WBC_DHD0_ZME_VSR;

    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSR.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSR.u32)) + enLayer * PQ_WBC_OFFSET));
        WBC_DHD0_ZME_VSR.bits.vratio = u32Ratio;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSR.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSR.u32);
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeEnable(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable, HI_U32 u32firMode)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;

    pVdpReg = PQ_HAL_GetVdpReg();
    /* WBC zoom enable */
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlmsc_en = u32bEnable;
            WBC_DHD0_ZME_HSP.bits.hlfir_en = u32firMode;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchmsc_en = u32bEnable;
            WBC_DHD0_ZME_HSP.bits.hchfir_en = u32firMode;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlmsc_en = u32bEnable;
            WBC_DHD0_ZME_VSP.bits.vlfir_en = u32firMode;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchmsc_en = u32bEnable;
            WBC_DHD0_ZME_VSP.bits.vchfir_en = u32firMode;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 bEnable)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        if ((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hlmid_en = bEnable;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_HSP.bits.hchmid_en = bEnable;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERL) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vlmid_en = bEnable;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }

        if ((enMode == VDP_ZME_MODE_VERC) || (enMode == VDP_ZME_MODE_VER) || (enMode == VDP_ZME_MODE_ALL))
        {
            WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
            WBC_DHD0_ZME_VSP.bits.vchmid_en = bEnable;
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
        }
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeHfirOrder(VDP_LAYER_WBC_E enLayer, HI_U32 u32HfirOrder)
{
    U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
    pVdpReg = PQ_HAL_GetVdpReg();
    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_HSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET));
        WBC_DHD0_ZME_HSP.bits.hfir_order = u32HfirOrder;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_HSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_HSP.u32);
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeVerTap(VDP_LAYER_WBC_E enLayer, VDP_ZME_MODE_E enMode, HI_U32 u32VerTap)
{
    /* vsc_luma_tap does not exist in 3798m_a and 3798m */
    /* vsc_chroma_tap does not exist in 3798m_a and 3798m */
    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeCoefAddr(VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E u32Mode, HI_U32 u32Addr, HI_U32 u32CAddr)
{
    pVdpReg = PQ_HAL_GetVdpReg();

    if ( enLayer == VDP_LAYER_WBC_HD0 ||  enLayer == VDP_LAYER_WBC_ME  )
    {
        if (u32Mode == VDP_WBC_PARA_ZME_HOR)
        {
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_HLCOEFAD.u32)) + enLayer * PQ_WBC_OFFSET), u32Addr);
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_HCCOEFAD.u32)) + enLayer * PQ_WBC_OFFSET), u32CAddr);
        }
        else if (u32Mode == VDP_WBC_PARA_ZME_VER)
        {
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_VLCOEFAD.u32)) + enLayer * PQ_WBC_OFFSET), u32Addr);
            PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_VCCOEFAD.u32)) + enLayer * PQ_WBC_OFFSET), u32CAddr);
        }
        else
        {
            HI_ERR_PQ("Error,PQ_HAL_WBC_SetZmeCoefAddr() Select a Wrong Mode!\n");
        }
    }

    return;
}

static HI_VOID PQ_HAL_WBC_SetParaUpd (VDP_LAYER_WBC_E enLayer, VDP_WBC_PARA_E enMode)
{
    U_WBC_DHD0_PARAUP WBC_DHD0_PARAUP;
    /* WBC_ME exist in 98cv100, using for MEMC, does not exist in 98mv100_a and 98m */

    pVdpReg = PQ_HAL_GetVdpReg();

    if ( enLayer == VDP_LAYER_WBC_HD0 )
    {
        WBC_DHD0_PARAUP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_PARAUP.u32))));
        if (enMode == VDP_WBC_PARA_ZME_HOR)
        {
            WBC_DHD0_PARAUP.bits.wbc_hlcoef_upd = 0x1;
            WBC_DHD0_PARAUP.bits.wbc_hccoef_upd = 0x1;
        }
        else if (enMode == VDP_WBC_PARA_ZME_VER)
        {
            WBC_DHD0_PARAUP.bits.wbc_vlcoef_upd = 0x1;
            WBC_DHD0_PARAUP.bits.wbc_vccoef_upd = 0x1;
        }
        else
        {
            HI_ERR_PQ("error,VDP_WBC_DHD0_SetParaUpd() select wrong mode!\n");
        }
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_PARAUP.u32))), WBC_DHD0_PARAUP.u32);
    }
    else
    {}

    return;
}

static HI_VOID PQ_HAL_WBC_SetZmeInFmt(VDP_LAYER_WBC_E enLayer, VDP_PROC_FMT_E u32Fmt)
{
    U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
    pVdpReg = PQ_HAL_GetVdpReg();

    if (enLayer == VDP_LAYER_WBC_HD0 || enLayer == VDP_LAYER_WBC_ME)
    {
        WBC_DHD0_ZME_VSP.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET));
        WBC_DHD0_ZME_VSP.bits.zme_in_fmt = u32Fmt;
        PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->WBC_DHD0_ZME_VSP.u32)) + enLayer * PQ_WBC_OFFSET), WBC_DHD0_ZME_VSP.u32);
    }
    else
    {}

    return;
}

/* Vdp WBC Cfg Set to reg*/
/* explanation: In WBC We just pay atention to WBC_HD0 */
HI_VOID PQ_HAL_WbcZmeRegCfg(HI_U32 u32LayerId, ALG_VZME_RTL_PARA_S *pstZmeRtlPara, HI_BOOL bFirEnable)
{
    if (u32LayerId >= VDP_ZME_LAYER_WBC0)
    {
        u32LayerId = u32LayerId - VDP_ZME_LAYER_WBC0;
    }

    PQ_HAL_WBC_SetZmeHorRatio(u32LayerId, pstZmeRtlPara->u32ZmeRatioHL);
    PQ_HAL_WBC_SetZmeVerRatio(u32LayerId, pstZmeRtlPara->u32ZmeRatioVL);

    PQ_HAL_WBC_SetZmePhaseH(u32LayerId, pstZmeRtlPara->s32ZmeOffsetHL, pstZmeRtlPara->s32ZmeOffsetHC);
    PQ_HAL_WBC_SetZmePhaseV(u32LayerId, pstZmeRtlPara->s32ZmeOffsetVL, pstZmeRtlPara->s32ZmeOffsetVC);


    /* zme enable and fir enable should not fix to a value. */
    PQ_HAL_WBC_SetZmeEnable(u32LayerId, VDP_ZME_MODE_HORL, pstZmeRtlPara->bZmeEnHL, pstZmeRtlPara->bZmeMdHL);
    PQ_HAL_WBC_SetZmeEnable(u32LayerId, VDP_ZME_MODE_HORC, pstZmeRtlPara->bZmeEnHC, pstZmeRtlPara->bZmeMdHC);
    PQ_HAL_WBC_SetZmeEnable(u32LayerId, VDP_ZME_MODE_VERL, pstZmeRtlPara->bZmeEnVL, pstZmeRtlPara->bZmeMdVL);
    PQ_HAL_WBC_SetZmeEnable(u32LayerId, VDP_ZME_MODE_VERC, pstZmeRtlPara->bZmeEnVC, pstZmeRtlPara->bZmeMdVC);

    /* set media fir. */
    PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_HORL, pstZmeRtlPara->bZmeMedHL);
    PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_HORC, pstZmeRtlPara->bZmeMedHC);
    PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_VERL, pstZmeRtlPara->bZmeMedVL);
    PQ_HAL_WBC_SetMidEnable(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_VERC, pstZmeRtlPara->bZmeMedVC);

    /* set zme order, h first or v first */
    PQ_HAL_WBC_SetZmeHfirOrder(VDP_LAYER_WBC_HD0, pstZmeRtlPara->bZmeOrder);

    /* It does not exist in 98m_a and 98m */
    /* set v chroma zme tap */
    PQ_HAL_WBC_SetZmeVerTap(VDP_LAYER_WBC_HD0, VDP_ZME_MODE_VERC, pstZmeRtlPara->bZmeTapVC);

    /* set hor fir coef addr, and set updata flag */
    if (pstZmeRtlPara->u32ZmeRatioHL)
    {
        PQ_HAL_WBC_SetZmeCoefAddr(VDP_LAYER_WBC_HD0, VDP_WBC_PARA_ZME_HOR, pstZmeRtlPara->u32ZmeCoefAddrHL, pstZmeRtlPara->u32ZmeCoefAddrHC);
        PQ_HAL_WBC_SetParaUpd(VDP_LAYER_WBC_HD0, VDP_WBC_PARA_ZME_HOR);
    }

    /* set ver fir coef addr, and set updata flag */
    if (pstZmeRtlPara->u32ZmeRatioVL)
    {
        PQ_HAL_WBC_SetZmeCoefAddr(VDP_LAYER_WBC_HD0, VDP_WBC_PARA_ZME_VER, pstZmeRtlPara->u32ZmeCoefAddrVL, pstZmeRtlPara->u32ZmeCoefAddrVC);
        PQ_HAL_WBC_SetParaUpd(VDP_LAYER_WBC_HD0, VDP_WBC_PARA_ZME_VER);
    }

    PQ_HAL_WBC_SetZmeInFmt(VDP_LAYER_WBC_HD0, VDP_PROC_FMT_SP_422);

    return;
}

/*******************************WBC ZME END***************************************/


/*********************************SR ZME******************************************/


/**************************************SR ZME END******************************************/

/*******************************Load VPSS ZME COEF START***********************************/
static HI_S32 VpssZmeTransCoefAlign(const HI_S16 *ps16Coef, VZME_TAP_E enTap, ZME_COEF_BITARRAY_S *pBitCoef)
{
    HI_U32 i, j, u32Tap, k;
    HI_S32 s32CoefTmp1, s32CoefTmp2, s32CoefTmp3;

    switch (enTap)
    {
        case VZME_TAP_8T32P:
            u32Tap = 8;
            break;
        case VZME_TAP_6T32P:
            u32Tap = 6;
            break;
        case VZME_TAP_4T32P:
            u32Tap = 4;
            break;
        default:
            u32Tap = 4;
            break;
    }

    j = 0;
    /* when tap == 8, there are 8 number in one group */
    if (u32Tap == 8)
    {
        /* 4 Bytes��32bits is the unit��every filter number is 10bits,
           There are 8 numbers in one group�� take place at one group include 3*4 Bytes,
           Array s32CoefAttr[51] add 1��The last 4 Bytes  only contain two numbers
           */
        for (i = 0; i < 17; i++)
        {
            s32CoefTmp1 = (HI_S32) * ps16Coef++;
            s32CoefTmp2 = (HI_S32) * ps16Coef++;
            s32CoefTmp3 = (HI_S32) * ps16Coef++;
            pBitCoef->s32CoefAttr[j++] = (s32CoefTmp1 & 0x3ff) + ((s32CoefTmp2 << 10) & 0xffc00) + (s32CoefTmp3 << 20);

            s32CoefTmp1 = (HI_S32) * ps16Coef++;
            s32CoefTmp2 = (HI_S32) * ps16Coef++;
            s32CoefTmp3 = (HI_S32) * ps16Coef++;
            pBitCoef->s32CoefAttr[j++] = (s32CoefTmp1 & 0x3ff) + ((s32CoefTmp2 << 10) & 0xffc00) + (s32CoefTmp3 << 20);

            s32CoefTmp1 = (HI_S32) * ps16Coef++;
            s32CoefTmp2 = (HI_S32) * ps16Coef++;
            pBitCoef->s32CoefAttr[j++] = (s32CoefTmp1 & 0x3ff) + ((s32CoefTmp2 << 10) & 0xffc00);
        }

        pBitCoef->u32Size = 17 * 3 * 4; /* size unit is Byte */
    }
    else
    {
        for (i = 0; i < 17; i++)
        {
            for (k = 1; k <= (u32Tap / 2); k++)
            {
                s32CoefTmp1 = (HI_S32) * ps16Coef++;
                s32CoefTmp2 = (HI_S32) * ps16Coef++;
                pBitCoef->s32CoefAttr[j++] = (s32CoefTmp1 & 0xffff) + (s32CoefTmp2 << 16);
            }
        }
        pBitCoef->u32Size = 17 * (u32Tap / 2) * 4;
    }

    return HI_SUCCESS;
}

/* load hor and vert coef */
static HI_S32 VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_RATIO_E enCoefRatio, VZME_VPSS_COEF_TYPE_E enCoefType, VZME_TAP_E enZmeTap, HI_U32 *pu32Addr)
{
    ZME_COEF_BITARRAY_S stArray;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Addr);

    //load chroma horizontal zoom coef
    VpssZmeTransCoefAlign(g_pVZmeVpssCoef[enCoefRatio][enCoefType], enZmeTap, &stArray);

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32Addr + stArray.u32Size);

    PQ_SAFE_MEMCPY(pu32Addr, stArray.s32CoefAttr, stArray.u32Size);

    return HI_SUCCESS;
}

/* Vpss in 3716mv410 is LH8��CH4��LV4��CV4 */
HI_VOID PQ_HAL_VpssLoadCoef(HI_U32 *pu32CurAddr, HI_U32 u32PhyAddr, ALG_VZME_COEF_ADDR_S *pstAddrTmp)
{
    HI_U32 u32NumSize;

    /* HL8 */
    u32NumSize = 256;
    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_1, VZME_VPSS_COEF_8T32P_LH, VZME_TAP_8T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_E1, VZME_VPSS_COEF_8T32P_LH, VZME_TAP_8T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_075, VZME_VPSS_COEF_8T32P_LH, VZME_TAP_8T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_05, VZME_VPSS_COEF_8T32P_LH, VZME_TAP_8T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_033, VZME_VPSS_COEF_8T32P_LH, VZME_TAP_8T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_025, VZME_VPSS_COEF_8T32P_LH, VZME_TAP_8T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_0, VZME_VPSS_COEF_8T32P_LH, VZME_TAP_8T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL8_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    /* HC4 */
    u32NumSize = 256;
    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_1, VZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_E1, VZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_075, VZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_05, VZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_033, VZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_025, VZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_0, VZME_VPSS_COEF_4T32P_CH, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHC4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    /* VL4 */
    u32NumSize = 256;
    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_1, VZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_E1, VZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_075, VZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_05, VZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_033, VZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_025, VZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_0, VZME_VPSS_COEF_4T32P_LV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL4_0 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    /* VC4 */
    u32NumSize = 256;
    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_1, VZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_E1, VZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_E1 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_075, VZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_075 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_05, VZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_05 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_033, VZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_033 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_025, VZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_025 = u32PhyAddr;
    u32PhyAddr  += u32NumSize;
    pu32CurAddr += u32NumSize / 4;

    VZmeLoadVpssCoef(PQ_HAL_ZME_COEF_0, VZME_VPSS_COEF_4T32P_CV, VZME_TAP_4T32P, pu32CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVC4_0 = u32PhyAddr;

    return;
}

/***********************************Load VPSS ZME COEF END*******************************************/

/***************************************VPSS ZME START*******************************************/

static HI_S32 PQ_HAL_VPSS_SetZmeEnable(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_BOOL bEnable)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if ((eMode ==  REG_ZME_MODE_HORL ) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hlmsc_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_HORC) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hchmsc_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERL) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vlmsc_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERC) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vchmsc_en = bEnable;
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeEnable error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeInSize(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_U32 u32Height, HI_U32 u32Width)
{
    switch (ePort)
    {
        case VPSS_REG_HD:

            break;
        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeInSize error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeOutSize(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_U32 u32Height, HI_U32 u32Width)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            pstReg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_oh = u32Height - 1;
            pstReg->VPSS_VHD0_ZMEORESO.bits.vhd0_zme_ow = u32Width  - 1;
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeOutSize error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeFirEnable(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_BOOL bEnable)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if ((eMode ==  REG_ZME_MODE_HORL ) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hlfir_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_HORC) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hchfir_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERL) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vlfir_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERC) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vchfir_en = bEnable;
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeFirEnable error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeMidEnable(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_BOOL bEnable)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if ((eMode == REG_ZME_MODE_HORL) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hlmid_en = bEnable;
            }
            if ((eMode ==  REG_ZME_MODE_HORC) || (eMode == REG_ZME_MODE_HOR) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_HSP.bits.hchmid_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERL) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vlmid_en = bEnable;
            }
            if ((eMode == REG_ZME_MODE_VERC) || (eMode == REG_ZME_MODE_VER) || (eMode == REG_ZME_MODE_ALL))
            {
                pstReg->VPSS_VHD0_VSP.bits.vchmid_en = bEnable;
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeMidEnable error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmePhase(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_S32 s32Phase)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if (eMode == REG_ZME_MODE_HORC)
            {
                pstReg->VPSS_VHD0_HCOFFSET.bits.hor_coffset = s32Phase;
            }
            else if (eMode == REG_ZME_MODE_HORL)
            {
                pstReg->VPSS_VHD0_HLOFFSET.bits.hor_loffset = s32Phase;
            }
            else if (eMode == REG_ZME_MODE_VERC)
            {
                pstReg->VPSS_VHD0_VOFFSET.bits.vchroma_offset = s32Phase;
            }
            else if (eMode == REG_ZME_MODE_VERL)
            {
                pstReg->VPSS_VHD0_VOFFSET.bits.vluma_offset = s32Phase;
            }
            else
            {
                HI_ERR_PQ("Error,VPSS_REG_SetZmePhase error\n");
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmePhase error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeRatio(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_U32 u32Ratio)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if (eMode == REG_ZME_MODE_HOR)
            {
                pstReg->VPSS_VHD0_HSP.bits.hratio = u32Ratio;
            }
            else
            {
                pstReg->VPSS_VHD0_VSR.bits.vratio = u32Ratio;
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeRatio error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeHfirOrder(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_BOOL bVfirst)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            //pstReg->VPSS_VHD_HSP.bits.hfir_order = bVfirst;
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeHfirOrder error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeInFmt(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_DRV_PIX_FORMAT_E eFormat)
{
    HI_U32 u32Format;

    switch (eFormat)
    {
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV12_TILE:
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV61:
        case HI_DRV_PIX_FMT_NV16:
        case HI_DRV_PIX_FMT_YUV400:
        case HI_DRV_PIX_FMT_YUV422_1X2:
        case HI_DRV_PIX_FMT_YUV420p:
        case HI_DRV_PIX_FMT_YUV410p:
            u32Format = 0x1;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_YUV_444:
        case HI_DRV_PIX_FMT_YUV422_2X1:
        case HI_DRV_PIX_FMT_YUV411:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:
            u32Format = 0x0;
            break;
        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeInFmt error\n");
            return HI_FAILURE;
    }

    switch (ePort)
    {
        case VPSS_REG_HD:
            pstReg->VPSS_VHD0_VSP.bits.zme_in_fmt = u32Format;
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeInFmt error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeOutFmt(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, HI_DRV_PIX_FORMAT_E eFormat)
{
    HI_U32 u32Format;

    switch (eFormat)
    {
        case HI_DRV_PIX_FMT_NV21:
        case HI_DRV_PIX_FMT_NV12:
        case HI_DRV_PIX_FMT_NV21_CMP:
        case HI_DRV_PIX_FMT_NV12_CMP:
        case HI_DRV_PIX_FMT_NV12_TILE:
        case HI_DRV_PIX_FMT_NV21_TILE:
        case HI_DRV_PIX_FMT_NV12_TILE_CMP:
        case HI_DRV_PIX_FMT_NV21_TILE_CMP:
            u32Format = 0x1;
            break;
        case HI_DRV_PIX_FMT_NV61_2X1:
        case HI_DRV_PIX_FMT_NV16_2X1:
        case HI_DRV_PIX_FMT_NV61_2X1_CMP:
        case HI_DRV_PIX_FMT_NV16_2X1_CMP:
        case HI_DRV_PIX_FMT_YUYV:
        case HI_DRV_PIX_FMT_YVYU:
        case HI_DRV_PIX_FMT_UYVY:
        case HI_DRV_PIX_FMT_ARGB8888:   /* sp420->sp422->csc->rgb */
        case HI_DRV_PIX_FMT_ABGR8888:
            //case HI_DRV_PIX_FMT_KBGR8888:
            u32Format = 0x0;
            break;
        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeOutFmt error\n");
            return HI_FAILURE;
    }

    switch (ePort)
    {
        case VPSS_REG_HD:
            pstReg->VPSS_VHD0_VSP.bits.zme_out_fmt = u32Format;
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeOutFmt error\n");
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_VPSS_SetZmeCoefAddr(HI_U32 u32HandleNo, VPSS_REG_PORT_E ePort, S_CAS_REGS_TYPE *pstReg, REG_ZME_MODE_E eMode, HI_U32 u32Addr)
{
    switch (ePort)
    {
        case VPSS_REG_HD:
            if (eMode == REG_ZME_MODE_HORC)
            {
                pstReg->VPSS_VHD0_ZME_CHADDR = u32Addr;
            }
            else if (eMode == REG_ZME_MODE_HORL)
            {
                pstReg->VPSS_VHD0_ZME_LHADDR = u32Addr;
            }
            else if (eMode == REG_ZME_MODE_VERC)
            {
                pstReg->VPSS_VHD0_ZME_CVADDR = u32Addr;
            }
            else if (eMode == REG_ZME_MODE_VERL)
            {
                pstReg->VPSS_VHD0_ZME_LVADDR = u32Addr;
            }
            else
            {
                HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeCoefAddr error\n");
            }
            break;

        default:
            HI_ERR_PQ("Error,PQ_HAL_VPSS_SetZmeCoefAddr error\n");
            break;
    }

    return HI_SUCCESS;
}

/* Vpss Cfg Set to reg */
HI_VOID PQ_HAL_VpssZmeRegCfg(HI_U32 u32LayerId, S_CAS_REGS_TYPE *pstReg, ALG_VZME_RTL_PARA_S *pstZmeRtlPara, HI_BOOL bFirEnable)
{
    HI_U32 ih;
    HI_U32 iw;
    HI_U32 oh;
    HI_U32 ow;
    HI_U32 u32HandleNo = 0;

    ih = pstZmeRtlPara->u32ZmeHIn;
    iw = pstZmeRtlPara->u32ZmeWIn;
    oh = pstZmeRtlPara->u32ZmeHOut;
    ow = pstZmeRtlPara->u32ZmeWOut;

    if (ih == oh && iw == ow && iw > 1920 && ih > 1200)
    {
        PQ_HAL_VPSS_SetZmeEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_ALL, HI_FALSE);
    }
    else
    {
        PQ_HAL_VPSS_SetZmeEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_ALL, HI_TRUE);
    }

    /* debug start sdk 2012-1-30; debug config for SDK debug: fixed to copy mode that don't need zme coefficient */
    /*
    pstZmeRtlPara->bZmeMdHL = 0;
    pstZmeRtlPara->bZmeMdHC = 0;
    pstZmeRtlPara->bZmeMdVL = 0;
    pstZmeRtlPara->bZmeMdVC = 0;
    */
    /* debug end sdk 2012-1-30 */

    if (!bFirEnable)
    {
        /* for fidelity output */
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORL, pstZmeRtlPara->bZmeMdHL);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORC, pstZmeRtlPara->bZmeMdHC);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, HI_FALSE);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, HI_FALSE);
    }
    else
    {
        /* for normal output */
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORL, pstZmeRtlPara->bZmeMdHL);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORC, pstZmeRtlPara->bZmeMdHC);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, pstZmeRtlPara->bZmeMdVL);
        PQ_HAL_VPSS_SetZmeFirEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, pstZmeRtlPara->bZmeMdVC);
    }

    PQ_HAL_VPSS_SetZmeMidEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORL, pstZmeRtlPara->bZmeMedHL);
    PQ_HAL_VPSS_SetZmeMidEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORC, pstZmeRtlPara->bZmeMedHC);
    PQ_HAL_VPSS_SetZmeMidEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, pstZmeRtlPara->bZmeMedVL);
    PQ_HAL_VPSS_SetZmeMidEnable(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, pstZmeRtlPara->bZmeMedVC);

    PQ_HAL_VPSS_SetZmePhase(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, pstZmeRtlPara->s32ZmeOffsetVL);
    PQ_HAL_VPSS_SetZmePhase(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, pstZmeRtlPara->s32ZmeOffsetVC);

    PQ_HAL_VPSS_SetZmeRatio(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HOR, pstZmeRtlPara->u32ZmeRatioHL);
    PQ_HAL_VPSS_SetZmeRatio(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VER, pstZmeRtlPara->u32ZmeRatioVL);

    if (u32LayerId == VPSS_REG_SD)
    {
        PQ_HAL_VPSS_SetZmeHfirOrder(u32HandleNo, u32LayerId, pstReg, pstZmeRtlPara->bZmeOrder);
    }

    if (pstZmeRtlPara->u8ZmeYCFmtIn == PQ_ALG_ZME_PIX_FORMAT_SP420)
    {
        PQ_HAL_VPSS_SetZmeInFmt(u32HandleNo, u32LayerId, pstReg, HI_DRV_PIX_FMT_NV21);
    }
    else
    {
        PQ_HAL_VPSS_SetZmeInFmt(u32HandleNo, u32LayerId, pstReg, HI_DRV_PIX_FMT_NV61_2X1);
    }

    if (pstZmeRtlPara->u8ZmeYCFmtOut == PQ_ALG_ZME_PIX_FORMAT_SP420)
    {
        PQ_HAL_VPSS_SetZmeOutFmt(u32HandleNo, u32LayerId, pstReg, HI_DRV_PIX_FMT_NV21);
    }
    else
    {
        PQ_HAL_VPSS_SetZmeOutFmt(u32HandleNo, u32LayerId, pstReg, HI_DRV_PIX_FMT_NV61_2X1);
    }

    PQ_HAL_VPSS_SetZmeInSize(u32HandleNo, u32LayerId, pstReg, ih, iw);
    PQ_HAL_VPSS_SetZmeOutSize(u32HandleNo, u32LayerId, pstReg, oh, ow);

    PQ_HAL_VPSS_SetZmeCoefAddr(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORL, pstZmeRtlPara->u32ZmeCoefAddrHL);
    PQ_HAL_VPSS_SetZmeCoefAddr(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_HORC, pstZmeRtlPara->u32ZmeCoefAddrHC);
    PQ_HAL_VPSS_SetZmeCoefAddr(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERL, pstZmeRtlPara->u32ZmeCoefAddrVL);
    PQ_HAL_VPSS_SetZmeCoefAddr(u32HandleNo, u32LayerId, pstReg, REG_ZME_MODE_VERC, pstZmeRtlPara->u32ZmeCoefAddrVC);

    return;
}

/*******************************VPSS ZME END*********************************/

static HI_VOID PQ_HAL_ColorSpaceTrans(PQ_HAL_DHD_COLORSPACE_E *penHDOutColorSpace, PQ_HAL_DHD_COLORSPACE_E *penSDOutColorSpace)
{
    HI_DRV_COLOR_SPACE_E enColorSpace_Dhd_HD, enColorSpace_Dhd_SD;

    if ((penHDOutColorSpace == HI_NULL) || (penSDOutColorSpace == HI_NULL))
    {
        return;
    }

    enColorSpace_Dhd_HD = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].enOutColorSpace;
    enColorSpace_Dhd_SD = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_0].enOutColorSpace;

    /* SD */
    if ((HI_DRV_CS_BT601_RGB_LIMITED == enColorSpace_Dhd_SD) || (HI_DRV_CS_BT601_RGB_FULL == enColorSpace_Dhd_SD)
        || (HI_DRV_CS_BT709_RGB_LIMITED == enColorSpace_Dhd_SD) || (HI_DRV_CS_BT709_RGB_FULL == enColorSpace_Dhd_SD)
        || (HI_DRV_CS_BT2020_RGB_LIMITED == enColorSpace_Dhd_SD) || (HI_DRV_CS_BT2020_RGB_FULL == enColorSpace_Dhd_SD))
    {
        *penSDOutColorSpace = PQ_HAL_DHD_OUT_RGB;
    }
    else
    {
        *penSDOutColorSpace = PQ_HAL_DHD_OUT_YUV;
    }

    /* HD */
    if ((HI_DRV_CS_BT601_RGB_LIMITED == enColorSpace_Dhd_HD) || (HI_DRV_CS_BT601_RGB_FULL == enColorSpace_Dhd_HD)
        || (HI_DRV_CS_BT709_RGB_LIMITED == enColorSpace_Dhd_HD) || (HI_DRV_CS_BT709_RGB_FULL == enColorSpace_Dhd_HD)
        || (HI_DRV_CS_BT2020_RGB_LIMITED == enColorSpace_Dhd_HD) || (HI_DRV_CS_BT2020_RGB_FULL == enColorSpace_Dhd_HD))
    {
        *penHDOutColorSpace = PQ_HAL_DHD_OUT_RGB;
    }
    else
    {
        *penHDOutColorSpace = PQ_HAL_DHD_OUT_YUV;
    }

    return;
}

static HI_S32 pq_hal_GetZmeCoefType(PQ_HAL_ZME_COEF_TYPE_E enCoefType,
                                    PQ_HAL_ZME_TAP_E enZmeTap,
                                    VZME_COEF_TYPE_E *penZmeCoefType,
                                    HI_U32 *pu32CoefSize)

{
    HI_U32 u32CoefSize = 0;
    VZME_COEF_TYPE_E enZmeCoefType = VZME_COEF_8T32P_LH;

    switch (enZmeTap)
    {
        case PQ_HAL_ZME_TAP_8T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_LH == enCoefType)
            {
                enZmeCoefType = VZME_COEF_8T32P_LH;
            }
            else if (PQ_HAL_ZME_COEF_TYPE_CH == enCoefType)
            {
                enZmeCoefType = VZME_COEF_8T32P_CH;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }
            u32CoefSize = sizeof(HI_S16) * 8 * 18;
            break;
        }

        case PQ_HAL_ZME_TAP_6T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_LV == enCoefType)
            {
                enZmeCoefType = VZME_COEF_6T32P_LV;
            }
            else if (PQ_HAL_ZME_COEF_TYPE_CV == enCoefType)
            {
                enZmeCoefType = VZME_COEF_6T32P_CV;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }
            u32CoefSize = sizeof(HI_S16) * 6 * 18;

            break;
        }

        case PQ_HAL_ZME_TAP_4T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_LV == enCoefType)
            {
                enZmeCoefType = VZME_COEF_4T32P_LV;
            }
            else if (PQ_HAL_ZME_COEF_TYPE_CH == enCoefType)
            {
                enZmeCoefType = VZME_COEF_4T32P_CH;
            }
            else if (PQ_HAL_ZME_COEF_TYPE_CV == enCoefType)
            {
                enZmeCoefType = VZME_COEF_4T32P_CV;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }
            u32CoefSize = sizeof(HI_S16) * 4 * 18;

            break;
        }

        case PQ_HAL_ZME_TAP_5T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_LV == enCoefType)
            {
                enZmeCoefType = VZME_COEF_5T32P_LV;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }
            u32CoefSize = sizeof(HI_S16) * 5 * 18;

            break;
        }

        case PQ_HAL_ZME_TAP_3T32P:
        {
            if (PQ_HAL_ZME_COEF_TYPE_CV == enCoefType)
            {
                enZmeCoefType = VZME_COEF_3T32P_CV;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }

            u32CoefSize = sizeof(HI_S16) * 3 * 18;

            break;
        }

        case PQ_HAL_ZME_TAP_8T2P:
        {
            if ((PQ_HAL_ZME_COEF_TYPE_LH == enCoefType) || (PQ_HAL_ZME_COEF_TYPE_CH == enCoefType))
            {
                enZmeCoefType = VZME_COEF_8T2P_HOR;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }
            u32CoefSize = sizeof(HI_S16) * 8 * 2;

            break;
        }

        case PQ_HAL_ZME_TAP_6T2P:
        {
            if ((PQ_HAL_ZME_COEF_TYPE_LV == enCoefType) || (PQ_HAL_ZME_COEF_TYPE_CV == enCoefType))
            {
                enZmeCoefType = VZME_COEF_6T2P_VER;
            }
            else
            {
                HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
                return HI_FAILURE;
            }
            u32CoefSize = sizeof(HI_S16) * 6 * 2;

            break;
        }

        default:
        {
            HI_ERR_PQ("enZmeTap:%d, enCoefType:%d,unsupport zme coef type!\n", enZmeTap, enCoefType);
            *penZmeCoefType = VZME_COEF_8T32P_LH;
            *pu32CoefSize = 0;
            return HI_FAILURE;
        }
    }

    *penZmeCoefType = enZmeCoefType;
    *pu32CoefSize = u32CoefSize;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetZmeCoef(PQ_HAL_ZME_COEF_RATIO_E enCoefRatio,
                         PQ_HAL_ZME_COEF_TYPE_E enCoefType,
                         PQ_HAL_ZME_TAP_E enZmeTap,
                         HI_S16 *ps16Coef)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32CoefSize = 0;
    VZME_COEF_TYPE_E enZmeCoefType = VZME_COEF_8T32P_LH;

    s32Ret =  pq_hal_GetZmeCoefType(enCoefType, enZmeTap, &enZmeCoefType, &u32CoefSize);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (0 != u32CoefSize)
    {
        PQ_CHECK_OVER_RANGE_RE_FAIL(enCoefRatio, PQ_HAL_ZME_COEF_RATIO_BUTT);
        PQ_CHECK_OVER_RANGE_RE_FAIL(enZmeCoefType, VZME_COEF_TYPE_BUTT);
        PQ_SAFE_MEMCPY((HI_VOID *)ps16Coef, (HI_VOID *)g_pVZmeCoef[enCoefRatio][enZmeCoefType], u32CoefSize);
    }
    else
    {
        HI_FATAL_PQ("Wrong Coef Size\n");
    }

    return s32Ret;
}

HI_S32 PQ_HAL_SetZmeDefault(HI_BOOL bOnOff)
{
    sg_bVpssZmeDefault = bOnOff;
    sg_bVdpZmeDefault  = bOnOff;

    return HI_SUCCESS;
}

static HI_VOID PQ_HAL_AdjustZmeFirEnCfg(HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    if (HI_TRUE == sg_bVdpZmeDefault)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC   = HI_FALSE;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL   = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC   = HI_FALSE;

        pstZmeOut->bZmeDefault = HI_TRUE;  /* 1: rwzb */
    }
    else
    {
        pstZmeOut->bZmeDefault = HI_FALSE; /* 0: no rwzb */
    }
    return;
}

static HI_VOID PQ_HAL_WbcVpZmeDefaultConfig(HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    if (HI_TRUE == sg_bVdpZmeDefault)
    {
        pstZmeOut->stZmeFmt.bZmeFirHL   = HI_FALSE;
        pstZmeOut->stZmeFmt.bZmeFirHC   = HI_FALSE;
        pstZmeOut->stZmeFmt.bZmeFirVL   = HI_FALSE;
        pstZmeOut->stZmeFmt.bZmeFirVC   = HI_FALSE;
        pstZmeOut->bZmeDefault = HI_TRUE;  /* 1: rwzb */
    }
    else
    {
        pstZmeOut->bZmeDefault = HI_FALSE; /* 0: no rwzb */
    }
    return;
}

static HI_BOOL PQ_HAL_GetDHD0P2IEnableFlag(HI_BOOL bSupportP2IOpen)
{
    if ((HI_TRUE == bSupportP2IOpen) && (HI_FALSE == g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].bProgressive))
    {
        /* Modify 20160509 -- HDR Interlace Issue; 98CV200 Interlace Output(1080i, 480i, 576i) ����ͨ��P2I */
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_VOID PQ_HAL_VO_SetVsacleModeByProc(HI_PQ_PREZME_VER_MUL_E *penVScalerMode)
{
    /* proc set zme height draw */
    switch (sg_stSetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode)
    {
        case HI_PQ_PROC_PREZME_VER_1X:
            *penVScalerMode = HI_PQ_PREZME_VER_DISABLE;
            break;
        case HI_PQ_PROC_PREZME_VER_2X:
            *penVScalerMode = HI_PQ_PREZME_VER_2X;
            break;
        case HI_PQ_PROC_PREZME_VER_4X:
            *penVScalerMode = HI_PQ_PREZME_VER_4X;
            break;
        case HI_PQ_PROC_PREZME_VER_8X:
            *penVScalerMode = HI_PQ_PREZME_VER_8X;
            break;
        default:
            break;
    }

    /* proc get zme width draw */
    if (HI_PQ_PROC_PREZME_VER_ORI != sg_stSetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode)
    {
        sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = sg_stSetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode;

    }
    else
    {
        switch (*penVScalerMode)
        {
            case HI_PQ_PREZME_VER_DISABLE:
                sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_1X;
                break;
            case HI_PQ_PREZME_VER_2X:
                sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_2X;
                break;
            case HI_PQ_PREZME_VER_4X:
                sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_4X;
                break;
            case HI_PQ_PREZME_VER_8X:
                sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_8X;
                break;
            default:
                sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_ORI;
                break;
        }
    }

    return;
}

static HI_VOID PQ_HAL_V0PreZmeConfig(HI_PQ_LAYER_STRATEGY_IN_S stZmeIn, HI_BOOL *pbReadFrame,
                                     HI_PQ_PREZME_HOR_MUL_E *penHScalerMode, HI_PQ_PREZME_VER_MUL_E *penVScalerMode, HI_BOOL *pbOpenP2I)
{
    /***
        Progressive Output List:
                 in        out          mode  multiple               scheme                zme tap
          1) 3840x2160  1920x1080         1      2       read frame and Ver prescaler  1     8644
          2) 1920x1080  1280x 720        1/4     6       read frame and Ver prescaler 1/2    8543
          3) 3840x2160  1280x 720        1/4     12      read frame and Ver prescaler 1/4    8543
          4) 4096x2304  1280x 720        1/4    12.8     read frame and Ver prescaler 1/8    8644

        Interlace Output List:
                 in        out          mode   multiple              scheme                 zme tap
          1) 720 x 576  720 x 576(288)    1       2      read field and Ver prescaler  1     8644
          2) 1920x1080  1920x1080(540)    1       2      read field and Ver prescaler  1     8644
          3) 720 x 576  720 x 480(240)    1      2.4     read frame and Ver prescaler  1     8644  ---zme������
          4) 1920x1080  720 x 576(288)    1      3.75    read frame and Ver prescaler 1/2    8644
          5) 1920x1080  720 x 480(240)   1/4      18     read frame and Ver prescaler 1/8    8644  ---1080PԴ�ļ��޳���, ����Ҫ����
          6) 3840x2160  1920x1080(540)   1/4      16     read frame and Ver prescaler 1/8    8644
          7) 3840x2160  720 x 576(288)   1/3     22.5    read frame and Ver prescaler 1/8    8543  ---��Ҫzme����, 8644 -> 8543�ĳ���, cbb����
          8) 3840x2160  720 x 480(240)   1/4      36     read frame and Ver prescaler 1/8    8543
          9) 4096x2304  720 x 480(240)   1/4     38.4    read frame and Ver prescaler 1/8    8543  ---���޳���, 4KԴ�ܷ����?

        ***/

    *pbOpenP2I      = PQ_HAL_GetDHD0P2IEnableFlag(HI_TRUE);
    *pbReadFrame    = HI_TRUE; /* Modify 20160509 -- HDR Interlace Issue; ���ӿ�ʱ������׳� 0-field; 1-frame */
    *penHScalerMode = HI_PQ_PREZME_HOR_DISABLE; /* there is not hor prescaler in logic */

    if (stZmeIn.u32FrmHIn <= V0_READ_FMT_ZME_THD * stZmeIn.u32FrmHOut) /* (in <= out) or (> 1 ~ <= 3); read frame and close prescaler*/
    {
        *penVScalerMode = HI_PQ_PREZME_VER_DISABLE;
    }
    else if ((stZmeIn.u32FrmHIn > V0_READ_FMT_ZME_THD * stZmeIn.u32FrmHOut)
             && (stZmeIn.u32FrmHIn <= V0_PREZME_ENABLE_2_THD * stZmeIn.u32FrmHOut)) /* > 3 ~ <= 6; read frame and 1/2 prescaler*/
    {
        *penVScalerMode = HI_PQ_PREZME_VER_2X;
    }
    else if ((stZmeIn.u32FrmHIn > V0_PREZME_ENABLE_2_THD * stZmeIn.u32FrmHOut)
             && (stZmeIn.u32FrmHIn <= V0_PREZME_ENABLE_4_THD * stZmeIn.u32FrmHOut)) /* > 6 ~ <= 12; read frame and 1/4 prescaler */
    {
        *penVScalerMode = HI_PQ_PREZME_VER_4X;
    }
    else if ((stZmeIn.u32FrmHIn > V0_PREZME_ENABLE_4_THD * stZmeIn.u32FrmHOut)
             && (stZmeIn.u32FrmHIn <= V0_PREZME_ENABLE_8_THD * stZmeIn.u32FrmHOut)) /* > 12 ~ <= 24; read frame and 1/8 prescaler */
    {
        *penVScalerMode = HI_PQ_PREZME_VER_8X;
    }
    else if (stZmeIn.u32FrmHIn > V0_PREZME_ENABLE_8_THD * stZmeIn.u32FrmHOut)       /* > 24; read field and 1/8 prescaler */
    {
        /* �ñ���ֻ��4KԴ(Vpss ByPass)ʱ�Ż����, ��4Kû�г��ĸ���, ������ֻ�ܶ�֡; read field����Ϊ�Ƕ�������, ż���� */
        *pbReadFrame    = HI_FALSE;
        *penVScalerMode = HI_PQ_PREZME_VER_8X;
    }

    sg_stGetPqProcVdpZmeStrategy.enProcVdpWidthDrawMode  = HI_PQ_PROC_PREZME_HOR_ORI;

    PQ_HAL_VO_SetVsacleModeByProc(penVScalerMode);

    return;
}

static HI_VOID PQ_HAL_V0PreZmeFrostConfig(HI_PQ_LAYER_STRATEGY_IN_S stZmeIn, HI_BOOL *pbReadFrame,
        HI_PQ_PREZME_HOR_MUL_E *penHScalerMode, HI_PQ_PREZME_VER_MUL_E *penVScalerMode, HI_BOOL *pbOpenP2I)
{
    *pbOpenP2I      = HI_FALSE;
    *pbReadFrame    = HI_TRUE;
    *penHScalerMode = HI_PQ_PREZME_HOR_DISABLE;

    /* vo set frost */
    switch (stZmeIn.eFrostLevel)
    {
        case HI_PQ_FROST_LEVEL_LOW:
            *penVScalerMode = HI_PQ_PREZME_VER_2X;
            break;
        case HI_PQ_FROST_LEVEL_MIDDLE:
            *penVScalerMode = HI_PQ_PREZME_VER_4X;
            break;
        case HI_PQ_FROST_LEVEL_HIGH:
            *penVScalerMode = HI_PQ_PREZME_VER_8X;
            break;
        default:
            *penVScalerMode = HI_PQ_PREZME_VER_DISABLE;
            break;
    }

    /* proc set frost */
    switch (sg_enProcFrostLevel)
    {
        case HI_PQ_FROST_LEVEL_LOW:
            *penVScalerMode = HI_PQ_PREZME_VER_2X;
            break;
        case HI_PQ_FROST_LEVEL_MIDDLE:
            *penVScalerMode = HI_PQ_PREZME_VER_4X;
            break;
        case HI_PQ_FROST_LEVEL_HIGH:
            *penVScalerMode = HI_PQ_PREZME_VER_8X;
            break;
        default:
            *penVScalerMode = HI_PQ_PREZME_VER_DISABLE;
            break;
    }

    /* proc get v drawmode */
    switch (*penVScalerMode)
    {
        case HI_PQ_PREZME_VER_DISABLE:
            sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_1X;
            break;
        case HI_PQ_PREZME_VER_2X:
            sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_2X;
            break;
        case HI_PQ_PREZME_VER_4X:
            sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_4X;
            break;
        case HI_PQ_PREZME_VER_8X:
            sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_8X;
            break;
        default:
            sg_stGetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode = HI_PQ_PROC_PREZME_VER_ORI;
            break;
    }

    return;
}

static HI_VOID PQ_HAL_V0AllZmeResolutionRatioCalc(HI_PQ_LAYER_STRATEGY_IN_S stZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    /***
       There is two Scaler in V0 of 98CV200, Scaler1 + sharpen = SR.
       Logic Limit: Only 4K output, �����8�ı���(������4�ı���) �ҷŴ�����������(��֧��ˮƽ����ֱ�̶��Ŵ�����), ����Scaler1;
                    e.g.: 480->1080 open Scaler0, but close Scaler1;
                          nvr scene: resolution at 1920 ~ 3840/4096 do not open Scaler1
      ***/
    if (((stZmeIn.u32FrmWOut >= DHD0_OUT_RESOLUTION_W_THD) && (0 == stZmeIn.u32FrmWOut % 8))
        && ((stZmeIn.u32FrmHOut >= DHD0_OUT_RESOLUTION_H_THD) && (0 == stZmeIn.u32FrmHOut % 8))
        && (stZmeIn.u32FrmHOut > stZmeIn.u32FrmHIn * V0_SCALER1_ENABLE_THD))
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = stZmeIn.u32FrmHIn;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = stZmeIn.u32FrmWIn;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = stZmeIn.u32FrmHOut / V0_SCALER1_ENABLE_THD;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = stZmeIn.u32FrmWOut / V0_SCALER1_ENABLE_THD;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = stZmeIn.u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = stZmeIn.u32FrmWOut;

        pstZmeOut->u32ZmeNum = 2; /* zme number */
    }
    else
    {
        /* prescaler will change Height, cbb does not use the height of cbb calc; but we clac it in pq for strategy
           Absolutely condition: when open scaler1, prescaler must be closed */
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = stZmeIn.u32FrmHIn / (1 << pstZmeOut->eVScalerMode);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = stZmeIn.u32FrmWIn / (1 << pstZmeOut->eHScalerMode);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = stZmeIn.u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = stZmeIn.u32FrmWOut;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = stZmeIn.u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = stZmeIn.u32FrmWOut;

        pstZmeOut->u32ZmeNum = 1;
    }

    if (stZmeIn.u32FrmWIn >= 2048)
    {
        /*Logic Limit: when inwith >= 2048, close  Scaler1*/
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight  = stZmeIn.u32FrmHIn / (1 << pstZmeOut->eVScalerMode);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth   = stZmeIn.u32FrmWIn / (1 << pstZmeOut->eHScalerMode);
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight = stZmeIn.u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth  = stZmeIn.u32FrmWOut;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight  = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth   = pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight = stZmeIn.u32FrmHOut;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth  = stZmeIn.u32FrmWOut;

        pstZmeOut->u32ZmeNum = 1;
    }

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixInFmt  = stZmeIn.u32FmtIn;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32PixOutFmt = 0; /* zme output: 0-422; 1-420; 2-444 */
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt  = 0; /* zme input:  0-422; 1-420; 2-444 */
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt = 0; /* zme output: 0-422; 1-420; 2-444 */

    sg_stProcVdpZmeReso.stVdpZme1Inreso.s32Width   = (HI_S32)pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInWidth;
    sg_stProcVdpZmeReso.stVdpZme1Inreso.s32Height  = (HI_S32)pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmInHeight;
    sg_stProcVdpZmeReso.stVdpZme1Outreso.s32Width  = (HI_S32)pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutWidth;
    sg_stProcVdpZmeReso.stVdpZme1Outreso.s32Height = (HI_S32)pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].u32FrmOutHeight;

    sg_stProcVdpZmeReso.stVdpZme2Inreso.s32Width   = (HI_S32)pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth;
    sg_stProcVdpZmeReso.stVdpZme2Inreso.s32Height  = (HI_S32)pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight;
    sg_stProcVdpZmeReso.stVdpZme2Outreso.s32Width  = (HI_S32)pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth;
    sg_stProcVdpZmeReso.stVdpZme2Outreso.s32Height = (HI_S32)pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight;

    return;
}



HI_VOID PQ_HAL_SetVdpZmeFirEn(HI_BOOL bZmeFirEn)
{
    g_bHalVdpZmeFirEn = bZmeFirEn;

    return;
}

HI_VOID PQ_HAL_SetVdpZmeMedEn(HI_BOOL bZmeModEn)
{
    g_bHalVdpZmeMedEn = bZmeModEn;

    return;
}

static HI_VOID PQ_HAL_SetV0OneZmeFirEnable(HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeHorEnable = HI_TRUE;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeVerEnable = HI_TRUE;

    if (HI_TRUE == g_bHalVdpZmeFirEn)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC = HI_TRUE ;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC = HI_FALSE ;
    }

    if (HI_TRUE == g_bHalVdpZmeMedEn)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH  = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV  = HI_TRUE ;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH  = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV  = HI_FALSE ;
    }

    return;
}

static HI_VOID PQ_HAL_SetV0TwoZmeFirEnable(HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    /* zme2 */
    if ((pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutWidth != pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInWidth) ||
        (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmOutHeight != pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32FrmInHeight) ||
        (pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixOutFmt != pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].u32PixInFmt))
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable = HI_TRUE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable = HI_TRUE;

        if (HI_TRUE == g_bHalVdpZmeFirEn)
        {
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL = HI_TRUE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL = HI_TRUE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC = HI_TRUE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC = HI_TRUE;
        }
        else
        {
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL = HI_FALSE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL = HI_FALSE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC = HI_FALSE;
            pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC = HI_FALSE;
        }
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeHorEnable = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeVerEnable = HI_FALSE;

        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHL = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVL = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirHC = HI_FALSE;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeFirVC = HI_FALSE;
    }

    if (HI_TRUE == g_bHalVdpZmeMedEn)
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedH  = HI_TRUE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedV  = HI_TRUE ;
    }
    else
    {
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedH  = HI_FALSE ;
        pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME2].bZmeMedV  = HI_FALSE ;
    }

    return;
}

static HI_VOID PQ_HAL_V0AllZmeModeConfig(HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    if (1 == pstZmeOut->u32ZmeNum)
    {
        PQ_HAL_SetV0OneZmeFirEnable(pstZmeOut);
    }
    else if (2 == pstZmeOut->u32ZmeNum)
    {
        PQ_HAL_SetV0OneZmeFirEnable(pstZmeOut);
        PQ_HAL_SetV0TwoZmeFirEnable(pstZmeOut);
    }

    return;
}

static HI_PQ_WBC_VP_POINT_SEL_E PQ_HAL_WbcVpWriteBackPointConfig(HI_PQ_WBC_STRATEGY_IN_S stZmeIn)
{
    HI_PQ_WBC_VP_POINT_SEL_E   enVpPoint         = HI_PQ_WBC_VP_POINT_V0;

    PQ_HAL_DHD_COLORSPACE_E enHDOutColorSpace = PQ_HAL_DHD_OUT_YUV;
    PQ_HAL_DHD_COLORSPACE_E enSDOutColorSpace = PQ_HAL_DHD_OUT_YUV;

    PQ_HAL_ColorSpaceTrans(&enHDOutColorSpace, &enSDOutColorSpace);

    /***
    ��д��ѡ�����:
    (1) ��ָ�곡��: ��д����V0;
    (2) �ര�����: ѡ��VP��CSC֮��Ļ�д��;
    (3) ˮӡ����:   ѡ��VP��CSC֮��Ļ�д��;
    (4) ë��������: ѡ��VP��CSC֮��Ļ�д��;
    (5) �������С���:
        ��(Դ->SD��ʾ����С����������С10��)> (Դ->HD��ʾ����С����������С6��), ��ѡ��VP��CSC֮��Ļ�д��;
          (SD�����������С, ��������SD�����С��ͼ������) -- �ȼ��ڸ���ͨ·����С����;
    (6) VESA timming ���ʱ�������⴦��
    (7) Else, ѡ��V0 Scaler0֮ǰ�Ļ�д��;
    ***/
    if (HI_TRUE == sg_bVdpZmeDefault) /* rwzb */
    {
        enVpPoint = HI_PQ_WBC_VP_POINT_V0;
    }
    else if (HI_TRUE == stZmeIn.bForceWbcPoint2Vp) /* (1)multi-window, (2)watermark, (3)forstglass; force to vp0 */
    {
        enVpPoint = HI_PQ_WBC_VP_POINT_VP;
    }
    else if ((stZmeIn.stLayerInfo[0].u32FrmWIn == stZmeIn.stLayerInfo[1].u32FrmWOut)
             && (stZmeIn.stLayerInfo[0].u32FrmHIn == stZmeIn.stLayerInfo[1].u32FrmHOut)) /* Interlace output and source resolution == out resolution */
    {
        /* Add 20160325 sdk ��ָ�곡��, ����Դ��CVBS�ķֱ���һ��ҲҪ��V0��д
           e.g.: 576i --> 576p --> 576i(Hdmi), 576i(Cvbs); ��д����V0;
                 480i --> 480p --> 480i(Hdmi), 480i(Cvbs); ��д����V0; */
        enVpPoint = HI_PQ_WBC_VP_POINT_V0;
    }
    else if ((stZmeIn.stLayerInfo[0].u32FrmHOut < stZmeIn.stLayerInfo[0].u32FrmHIn)
             && (stZmeIn.stLayerInfo[0].u32FrmHOut > stZmeIn.stLayerInfo[1].u32FrmHOut))
    {
        /* example: 720x576-->640x480(HD) ��Ҫ��V0��д;
           Judgement condition is height of V0, not the height of VP */
        enVpPoint = HI_PQ_WBC_VP_POINT_VP;
    }
    else
    {
        enVpPoint = HI_PQ_WBC_VP_POINT_V0;
    }

    return enVpPoint;
}

static HI_BOOL PQ_HAL_WbcVpZmeOutFrameOrField(HI_PQ_WBC_STRATEGY_IN_S stZmeIn)
{
    HI_BOOL bOutFmt = 0;
    /***
      WBC_VP��д���ݵĸ�ʽ���������Ǹ���HD�ӿں�SD�ӿ�֮���Ƿ���Ҫ֡��ת����������д��ʽ��
      (1) ���HD֡��<SD֡��(��: HD���1080P24��SD���NTSC��ʽ), ��WBC_VP��д֡����;
          (�Ա�֤SD���ͼ�񲻻���ֻ��˻����¶���)
      (2) Else, WBC_VP��д������. ���������Ҫע��, HD���60hz, ��SD���NTSC(59.94hz)�����,
          HDÿ��16s��SD���ſ�һ��, SD��������ʱҪ��֤һ�ζ�������, �������ּ��Է�ת������Ӷ�����ͼ�����¶���;

      ע��: HD-4KP30, SD-NTSC; HD-4KP25, SD-PAL; HD-1080P24, SD-NTSC; ��ҪV3��֡������, Vdp�������ظ�����ӿ����;
      ***/
    if (HI_TRUE == stZmeIn.bForceWbcFieldMode) /* ǿ�ƻ�д�� */
    {
        bOutFmt = 0; /* Frame format for zme output: 0-field; 1-frame */
    }
    else if (g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].u32RefreshRate != g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_0].u32RefreshRate)
    {
        bOutFmt = 1;
    }
    else
    {
        bOutFmt = 0;
    }

    return bOutFmt;
}

static HI_PQ_ZME_BIND_POSITION_E PQ_HAL_WbcVpZmePosition(HI_VOID)
{
    if (HI_FALSE == g_stPqStatus.bIsogenyMode) /* ��ͬԴ */
    {
        return HI_PQ_ZME_BIND_V3;
    }

    return HI_PQ_ZME_BIND_WBC;
}

static HI_PQ_PREZME_HOR_MUL_E PQ_HAL_WbcVpHScalerConfig(HI_U32 u32InWidth)
{
    /* 98CV200 WBC HScaler�Ŀ������������ܵ�����, ��������ڵ���4Kʱ��; ����оƬ�޷���֤�ж�Hscaler������������һ����;
       �����в��漰Hscaler��ʵ��; PQ��Hsacaler + Scaler(WBC)����һ��������Scaler;
       Hsacler�Ĳ����ɵײ�cbb�Լ���, ����ratio���zme�Ŀ��, ͬ����cbb����;
       */
    if (u32InWidth >= DHD0_OUT_RESOLUTION_W_THD)
    {
        return HI_PQ_PREZME_HOR_2X; /* �̶�2��1 */
    }

    return HI_PQ_PREZME_HOR_DISABLE;
}

static HI_BOOL PQ_HAL_WbcVpZmeP2IConfig(HI_BOOL bWbcAPointProgressive, HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    HI_U32  u32InWidth    = 0;
    HI_U32  u32InHeight   = 0;
    HI_U32  u32OutWidth   = 0;
    HI_U32  u32OutHeight  = 0;
    HI_BOOL bWbcOutFormat = HI_FALSE; /* HI_FALSE: Interlace */
    HI_BOOL bOpenP2I      = HI_FALSE;

    u32InHeight   = pstZmeOut->stZmeFmt.u32FrmInHeight;
    u32InWidth    = pstZmeOut->stZmeFmt.u32FrmInWidth;
    u32OutWidth   = pstZmeOut->stZmeFmt.u32FrmOutWidth;
    u32OutHeight  = pstZmeOut->stZmeFmt.u32FrmOutHeight;
    bWbcOutFormat = pstZmeOut->stZmeFmt.bOutFmt;

    /***
       WBC_VP P2I�Ŀ�������: (�ο�3798cv200 �㷨����ͼ)
       (1) ���B�����Progressive, ��P2I�ر�;
       (2) ���B�����Interlace, ����������;
           A) ���A������Interlace, ��P2I�ر�;
           B) ���A������Progressive, ���ַ��������:
              a) ���Դresolution==Ŀ��resolution, ��P2I��������Ҫƥ�䳡����;
              b) �����ֱ���ű�<THD'(��1/4, ����ֵ��Ҫ���Ժ���ȷ��), ��P2I����(�൱��������С��Ϊ�������������С��ͼ��Ч��);
              c) Else, P2I�ر�
      ***/
    /* ��ͬԴģʽ: ZME����V3��, do not care B Point is Progressive or not */
    if (HI_FALSE == g_stPqStatus.bIsogenyMode)
    {
        return HI_FALSE;
    }
    /* ����ͬԴģʽ: ZME����WBC��, ��Ϊ�������������Interlace, ��B�����Ϊ Interlace */
    if (HI_TRUE == bWbcOutFormat) /* WBC�����Progressive, ��B��Progressive */
    {
        bOpenP2I = HI_FALSE;
    }
    else if (HI_FALSE == bWbcAPointProgressive) /* B�����Interlace, A������Interlace */
    {
        bOpenP2I = HI_FALSE;
    }
    else if (HI_TRUE == bWbcAPointProgressive)  /* B�����Interlace, A������Progressive */
    {
        /* 1. ��������: ��ֻ��4K��Hscalerʱ, �ŻῪ��,��˲���Ҫ�����µ��ж������г���Hscaler.
           2. cvbs������̶���pal��ntsc, ��������������ֻ��: 576p --> 576i; 480p --> 480i;    */
        if ((u32OutWidth == u32InWidth) && (u32OutHeight == u32InHeight))
        {
            /* e.g.: 576i --> 576p --> 576i(Hdmi), 576i(Cvbs); ��д����V0��, V0����, ��A��ΪInterlace;   ������������;
                     576i --> 576p --> 720p(Hdmi), 576i(Cvbs); ��д����V0��, V0��֡, ��A��ΪProgressive; ����������;  */
            bOpenP2I = HI_TRUE;
        }
        else if (u32InHeight > WBC_HSCALER_THD * u32OutHeight)
        {
            bOpenP2I = HI_TRUE;
        }
        else
        {
            bOpenP2I = HI_FALSE;
        }
    }
    return bOpenP2I;
}

static HI_BOOL PQ_HAL_WbcVpZmeIsWriteBackPointIsProgressive(HI_VOID)
{
    HI_BOOL bWbcAPointProgressive = HI_TRUE;

    if (HI_PQ_WBC_VP_POINT_V0 == sg_enWbcVpPointSel)
    {
        bWbcAPointProgressive = sg_bV0ReadFmtIn; /* V0 �������ݸ����� */
    }
    else if (HI_PQ_WBC_VP_POINT_VP == sg_enWbcVpPointSel)
    {
        /* Modify 20160509 -- HDR Interlace Issue; P2I��֮��, VP�ϻ�д, ��д���ݿ϶������� */
        bWbcAPointProgressive = HI_TRUE;
    }

    return bWbcAPointProgressive;
}

static HI_VOID PQ_HAL_WbcVpZmeResolutionRatioCalc(HI_PQ_WBC_STRATEGY_IN_S stZmeIn, HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    HI_U32  bWbcAPointPixFmt = 0; /* A point video format: 0-422; 1-420; 2-444 */
    HI_U32  u32InWidth       = 0;
    HI_U32  u32InHeight      = 0;
    HI_U32  u32OutWidth      = 0;
    HI_U32  u32OutHeight     = 0;

    if (HI_PQ_WBC_VP_POINT_V0 == sg_enWbcVpPointSel)
    {
        u32InWidth   = stZmeIn.stLayerInfo[0].u32FrmWIn / (1 << (HI_U32)sg_enV0PreHScaler);
        u32InHeight  = stZmeIn.stLayerInfo[0].u32FrmHIn / (1 << (HI_U32)sg_enV0PreVScaler);
        u32OutWidth  = stZmeIn.stLayerInfo[1].u32FrmWOut; /* V3 FrmWOut */
        u32OutHeight = stZmeIn.stLayerInfo[1].u32FrmHOut; /* V3 FrmHOut */

        if (2 == stZmeIn.stLayerInfo[0].u32FmtIn) /* pix format: 0-422; 1-420; 2-444 */
        {
            bWbcAPointPixFmt = 0; /* pix format: 0-422; 1-420; 2-444 */
        }
        else
        {
            bWbcAPointPixFmt = stZmeIn.stLayerInfo[0].u32FmtIn; /* V0 �������ݸ�ʽ */
        }
    }
    else if (HI_PQ_WBC_VP_POINT_VP == sg_enWbcVpPointSel)
    {
        /* ������VP��, ������ŵĿ��Ӧ���ǽӿڵĿ��, ���ǲ�Ŀ��; ����PIP��Ԥ���޷���дȫ��;
           Remark: ���ڿ�ߵ���V0��ʵ�ʿ��, ��ʽ��ߵ���VP�ϵĿ�� */
        u32InWidth       = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].stFmtRect.s32Width;
        u32InHeight      = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_1].stFmtRect.s32Height;
        u32OutWidth      = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_0].stFmtRect.s32Width;
        u32OutHeight     = g_stPqStatus.stTimingInfo[HI_PQ_DISPLAY_0].stFmtRect.s32Height;
        bWbcAPointPixFmt = 0; /* pix format: 0-422; 1-420; 2-444 */
    }

    /* Scaler Info Calc */
    pstZmeOut->stZmeFmt.u32FrmInHeight  = u32InHeight;
    pstZmeOut->stZmeFmt.u32FrmInWidth   = u32InWidth; /* can not divide 2 */
    pstZmeOut->stZmeFmt.u32FrmOutWidth  = u32OutWidth;
    pstZmeOut->stZmeFmt.u32FrmOutHeight = u32OutHeight;

    pstZmeOut->stZmeFmt.u32PixInFmt     = bWbcAPointPixFmt;
    pstZmeOut->stZmeFmt.u32PixOutFmt    = 0; /* 0-422; 1-420; 2-444; write back must be 422 */

    return;
}


static HI_VOID PQ_HAL_WbcVpZmeModeConfig(HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    /* config zme mode; when frame resolution does not have change, can not open fir mode; e.g: (480i-->480i) or (576i --> 576i); other must open fir mode; */
    pstZmeOut->stZmeFmt.bZmeFirHL = (pstZmeOut->stZmeFmt.u32FrmOutWidth  == pstZmeOut->stZmeFmt.u32FrmInWidth)  ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt.bZmeFirVL = (pstZmeOut->stZmeFmt.u32FrmOutHeight == pstZmeOut->stZmeFmt.u32FrmInHeight) ? HI_FALSE : HI_TRUE;
    /* in format may be 420(write back from v0) or must be 422(write back from vp0), out format must be 422; when 420 -> 422; vertical need up-sampling, but horizontal does not need */
    pstZmeOut->stZmeFmt.bZmeFirHC = (HI_FALSE == pstZmeOut->stZmeFmt.bZmeFirHL) ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt.bZmeFirVC = (HI_FALSE == pstZmeOut->stZmeFmt.bZmeFirVL) ? ((pstZmeOut->stZmeFmt.u32PixOutFmt == pstZmeOut->stZmeFmt.u32PixInFmt) ? HI_FALSE : HI_TRUE) : HI_TRUE;

    pstZmeOut->stZmeFmt.bZmeMedH  = HI_FALSE; /* zme Median filter enable of horizontal: 0-off; 1-on*/
    pstZmeOut->stZmeFmt.bZmeMedV  = HI_FALSE;

    return;
}

static HI_S32 PQ_HAL_GetV0ZmeStrategy (HI_PQ_LAYER_STRATEGY_IN_S stZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmeOut);

    sg_stProcVdpZmeReso.stVdpInReso.s32Width   = (HI_S32)stZmeIn.u32FrmWIn;
    sg_stProcVdpZmeReso.stVdpInReso.s32Height  = (HI_S32)stZmeIn.u32FrmHIn;
    sg_stProcVdpZmeReso.stVdpOutreso.s32Width  = (HI_S32)stZmeIn.u32FrmWOut;
    sg_stProcVdpZmeReso.stVdpOutreso.s32Height = (HI_S32)stZmeIn.u32FrmHOut;

    /* ���������С���㡢P2I ���� */
    if ((HI_PQ_FROST_LEVEL_CLOSE != stZmeIn.eFrostLevel) || (HI_PQ_FROST_LEVEL_CLOSE != sg_enProcFrostLevel))
    {
        PQ_HAL_V0PreZmeFrostConfig(stZmeIn, &(pstZmeOut->bReadFmtIn), &(pstZmeOut->eHScalerMode), &(pstZmeOut->eVScalerMode), &(pstZmeOut->bOpenP2I));
    }
    else
    {
        PQ_HAL_V0PreZmeConfig(stZmeIn, &(pstZmeOut->bReadFmtIn), &(pstZmeOut->eHScalerMode), &(pstZmeOut->eVScalerMode), &(pstZmeOut->bOpenP2I));
    }
    sg_bV0ReadFmtIn   = pstZmeOut->bReadFmtIn;
    sg_enV0PreHScaler = pstZmeOut->eHScalerMode;
    sg_enV0PreVScaler = pstZmeOut->eVScalerMode;

    PQ_HAL_V0AllZmeResolutionRatioCalc(stZmeIn, pstZmeOut);

    PQ_HAL_V0AllZmeModeConfig(pstZmeOut);

    PQ_HAL_AdjustZmeFirEnCfg(pstZmeOut);

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_GetV1ZmeStrategy (HI_PQ_LAYER_STRATEGY_IN_S stZmeIn, HI_PQ_LAYER_STRATEGY_OUT_S *pstZmeOut)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmeOut);

    pstZmeOut->u32ZmeNum    = 1; /* chroma up-sampling */
    pstZmeOut->eHScalerMode = HI_PQ_PREZME_HOR_DISABLE;
    pstZmeOut->eVScalerMode = HI_PQ_PREZME_VER_DISABLE;

    pstZmeOut->bReadFmtIn   = HI_TRUE; /* read frame */
    pstZmeOut->bOpenP2I     = PQ_HAL_GetDHD0P2IEnableFlag(HI_TRUE);

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL = (stZmeIn.u32FrmWOut == stZmeIn.u32FrmWIn) ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL = (stZmeIn.u32FrmHOut == stZmeIn.u32FrmHIn) ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHC = (HI_FALSE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirHL) ? HI_FALSE : HI_TRUE;
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVC = (HI_FALSE == pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeFirVL) ? ((stZmeIn.u32FmtIn == 0) ? HI_FALSE : HI_TRUE) : HI_TRUE;

    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedH  = HI_FALSE; /* zme Median filter enable of horizontal luma: 0-off; 1-on*/
    pstZmeOut->stZmeFmt[HI_PQ_V0_ZME_NODE_ZME1].bZmeMedV  = HI_FALSE;

    PQ_HAL_AdjustZmeFirEnCfg(pstZmeOut);

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_GetProcWbcVpStrategy (HI_PQ_WBC_STRATEGY_IN_S stZmeIn, HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].u32PointSel = (HI_PQ_WBC_VP_POINT_VP == pstZmeOut->enVpPoint) ? 0 : 1;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].bP2iEn      = pstZmeOut->bOpenP2I;

    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme1Inreso.s32Width   = (HI_S32)pstZmeOut->stZmeFmt.u32FrmInWidth;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme1Inreso.s32Height  = (HI_S32)pstZmeOut->stZmeFmt.u32FrmInHeight;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme1Outreso.s32Width  = (HI_PQ_PREZME_HOR_2X == pstZmeOut->eHScalerMode) ?
            (HI_S32)pstZmeOut->stZmeFmt.u32FrmInWidth / 2 : (HI_S32)pstZmeOut->stZmeFmt.u32FrmInWidth;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme1Outreso.s32Height = (HI_S32)pstZmeOut->stZmeFmt.u32FrmInHeight;

    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme2Inreso.s32Width   = sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme1Outreso.s32Width;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme2Inreso.s32Height  = sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme1Outreso.s32Height;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme2Outreso.s32Width  = (HI_S32)pstZmeOut->stZmeFmt.u32FrmOutWidth;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_VP].stZme2Outreso.s32Height = (HI_S32)pstZmeOut->stZmeFmt.u32FrmOutHeight;

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_GetWbcVpZmeStrategy (HI_PQ_WBC_STRATEGY_IN_S stZmeIn, HI_PQ_WBC_VP_STRATEGY_OUT_S *pstZmeOut)
{
    HI_BOOL bWbcAPointProgressive = HI_TRUE; /* Wbc A point frame format: 0-field; 1-frame */

    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmeOut);

    pstZmeOut->enVpPoint = PQ_HAL_WbcVpWriteBackPointConfig(stZmeIn);
    sg_enWbcVpPointSel     = pstZmeOut->enVpPoint;

    /* ����WBC�������������ߡ�֡/�� */
    PQ_HAL_WbcVpZmeResolutionRatioCalc(stZmeIn, pstZmeOut);

    bWbcAPointProgressive    = PQ_HAL_WbcVpZmeIsWriteBackPointIsProgressive();
    pstZmeOut->bReadFmtIn    = bWbcAPointProgressive; /* Frame format for zme Intput: 0-field; 1-frame */
    pstZmeOut->stZmeFmt.bOutFmt = PQ_HAL_WbcVpZmeOutFrameOrField(stZmeIn);
    pstZmeOut->eZmePosition  = PQ_HAL_WbcVpZmePosition();

    pstZmeOut->bOpenP2I      = PQ_HAL_WbcVpZmeP2IConfig(bWbcAPointProgressive, pstZmeOut);
    pstZmeOut->eHScalerMode  = PQ_HAL_WbcVpHScalerConfig(pstZmeOut->stZmeFmt.u32FrmInWidth);

    /* e.g.: 576i -> 576p -> 576i(Hdmi), 576i(Cvbs); Write back from V0, V0 read field, A point is interlace */
    pstZmeOut->stZmeFmt.bInFmt  = (HI_TRUE == pstZmeOut->bOpenP2I) ? 0 : bWbcAPointProgressive;

    PQ_HAL_WbcVpZmeModeConfig(pstZmeOut);
    PQ_HAL_WbcVpZmeDefaultConfig(pstZmeOut);

    PQ_HAL_GetProcWbcVpStrategy(stZmeIn, pstZmeOut);

    pqprint(PQ_PRN_ZME, "V0 WIn:%d, HIn:%d, WOut:%d, HOut:%d\t", stZmeIn.stLayerInfo[0].u32FrmWIn, stZmeIn.stLayerInfo[0].u32FrmHIn,
            stZmeIn.stLayerInfo[0].u32FrmWOut, stZmeIn.stLayerInfo[0].u32FrmHOut);
    pqprint(PQ_PRN_ZME, "V3 WIn:%d, HIn:%d, WOut:%d, HOut:%d\n", stZmeIn.stLayerInfo[1].u32FrmWIn, stZmeIn.stLayerInfo[1].u32FrmHIn,
            stZmeIn.stLayerInfo[1].u32FrmWOut, stZmeIn.stLayerInfo[1].u32FrmHOut);
    pqprint(PQ_PRN_ZME, "OUT WIn:%d, HIn:%d, WOut:%d, HOut:%d\n", pstZmeOut->stZmeFmt.u32FrmInWidth, pstZmeOut->stZmeFmt.u32FrmInHeight,
            pstZmeOut->stZmeFmt.u32FrmOutWidth, pstZmeOut->stZmeFmt.u32FrmOutHeight);

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_GetProcWbcDHDStrategy (HI_PQ_LAYER_STRATEGY_IN_S stZmeIn, HI_PQ_WBC_DHD0_STRATEGY_OUT_S *pstZmeOut)
{
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].u32PointSel = 0;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].bP2iEn      = 0;

    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme1Inreso.s32Width   = (HI_S32)pstZmeOut->stZmeFmt.u32FrmInWidth;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme1Inreso.s32Height  = (HI_S32)pstZmeOut->stZmeFmt.u32FrmInHeight;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme1Outreso.s32Width  = (HI_PQ_PREZME_HOR_2X == pstZmeOut->eHScalerMode) ?
            (HI_S32)pstZmeOut->stZmeFmt.u32FrmInWidth / 2 : (HI_S32)pstZmeOut->stZmeFmt.u32FrmInWidth;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme1Outreso.s32Height = (HI_S32)pstZmeOut->stZmeFmt.u32FrmInHeight;

    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme2Inreso.s32Width   = sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme1Outreso.s32Width;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme2Inreso.s32Height  = sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme1Outreso.s32Height;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme2Outreso.s32Width  = (HI_S32)pstZmeOut->stZmeFmt.u32FrmOutWidth;
    sg_stGetProcWbcStrategy[HI_PQ_PROC_WBC_LAYER_DHD].stZme2Outreso.s32Height = (HI_S32)pstZmeOut->stZmeFmt.u32FrmOutHeight;

    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_GetWbcDhdZmeStrategy (HI_PQ_LAYER_STRATEGY_IN_S stZmeIn, HI_PQ_WBC_DHD0_STRATEGY_OUT_S *pstZmeOut)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstZmeOut);

    /* �����߼����ܵ�����, Hscaler�̶�����1/2 */
    pstZmeOut->eHScalerMode   = HI_PQ_PREZME_HOR_2X;
    pstZmeOut->bInWbcVpZmeFmt = HI_TRUE; /* Modify 20160509 -- HDR Interlace Issue; P2I ��, ��DHD��д�Ķ������� */

    pstZmeOut->stZmeFmt.u32FrmInHeight  = stZmeIn.u32FrmHIn;
    pstZmeOut->stZmeFmt.u32FrmInWidth   = stZmeIn.u32FrmWIn; /* can not divide 2 */
    pstZmeOut->stZmeFmt.u32FrmOutWidth  = stZmeIn.u32FrmWOut;
    pstZmeOut->stZmeFmt.u32FrmOutHeight = stZmeIn.u32FrmHOut;
    /* Layer strategry: input 444, output 420 */
    pstZmeOut->stZmeFmt.u32PixInFmt     = 2; /* 0-422; 1-420; 2-444 */
    pstZmeOut->stZmeFmt.u32PixOutFmt    = 1; /* 0-422; 1-420; 2-444 */

    pstZmeOut->stZmeFmt.bZmeFirHL = HI_TRUE; /* 0-copy mode; 1-FIR filter mode*/
    pstZmeOut->stZmeFmt.bZmeFirVL = HI_TRUE;
    pstZmeOut->stZmeFmt.bZmeFirHC = HI_TRUE;
    pstZmeOut->stZmeFmt.bZmeFirVC = HI_TRUE;

    pstZmeOut->stZmeFmt.bZmeMedH  = HI_FALSE; /* zme Median filter enable of horizontal luma: 0-off; 1-on*/
    pstZmeOut->stZmeFmt.bZmeMedV  = HI_FALSE;

    PQ_HAL_GetProcWbcDHDStrategy(stZmeIn, pstZmeOut);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetVdpZmeStrategy (VDP_ZME_LAYER_E enLayerId, HI_PQ_ZME_STRATEGY_IN_U *pstZmeIn, HI_PQ_ZME_STRATEGY_OUT_U *pstZmeOut)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (VDP_ZME_LAYER_V0 == enLayerId)
    {
        s32Ret = PQ_HAL_GetV0ZmeStrategy(pstZmeIn->stLayerStrategy, &(pstZmeOut->stStrategyLayerId));
    }
    else if (VDP_ZME_LAYER_V1 == enLayerId)
    {
        s32Ret = PQ_HAL_GetV1ZmeStrategy(pstZmeIn->stLayerStrategy, &(pstZmeOut->stStrategyLayerId));
    }
    else if (VDP_ZME_LAYER_WBC0 == enLayerId)
    {
        /*��ͬԴ����VDP��Ҫ����V3���ԣ�������WBC���� */
        s32Ret = PQ_HAL_GetWbcVpZmeStrategy(pstZmeIn->stWbcStrategy, &(pstZmeOut->stStrategyWbcVp));
    }
    else if (VDP_ZME_LAYER_WBC_DHD == enLayerId)
    {
        s32Ret = PQ_HAL_GetWbcDhdZmeStrategy(pstZmeIn->stLayerStrategy, &(pstZmeOut->stStrategyWbcDhd));
    }
    else
    {
        HI_ERR_PQ("LayerId:%d, unsupport zme strategy!\n", enLayerId);
    }

    return s32Ret;
}

HI_S32 PQ_HAL_SetProcFrostLevel(HI_PQ_FROST_LEVEL_E enFrostLevel)
{
    sg_enProcFrostLevel = enFrostLevel;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetHDCPEn(HI_BOOL bOnOff)
{
    HI_UNUSED(bOnOff);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetProcVdpZmeStrategy(HI_PQ_PROC_VDPZME_STRATEGY_S stProcVdpZmeStrategy)
{
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(stProcVdpZmeStrategy.enProcVdpZmeNum, HI_PQ_PROC_ZME_NUM_BUTT);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(stProcVdpZmeStrategy.enProcVdpWidthDrawMode, HI_PQ_PROC_PREZME_HOR_BUTT);
    PQ_CHECK_NUM_OVER_RANGE_RE_FAIL(stProcVdpZmeStrategy.enProcVdpHeightDrawMode, HI_PQ_PROC_PREZME_VER_BUTT);

    /* hpzme do not support set by proc */
    sg_stSetPqProcVdpZmeStrategy.enProcVdpZmeNum          = stProcVdpZmeStrategy.enProcVdpZmeNum;
    sg_stSetPqProcVdpZmeStrategy.enProcVdpWidthDrawMode   = stProcVdpZmeStrategy.enProcVdpWidthDrawMode;
    sg_stSetPqProcVdpZmeStrategy.enProcVdpHeightDrawMode  = stProcVdpZmeStrategy.enProcVdpHeightDrawMode;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetProcVdpZmeStrategy(HI_PQ_PROC_VDPZME_STRATEGY_S *pstProcVdpZmeStrategy)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstProcVdpZmeStrategy);

    PQ_SAFE_MEMCPY(pstProcVdpZmeStrategy, &sg_stGetPqProcVdpZmeStrategy, sizeof(sg_stGetPqProcVdpZmeStrategy));

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetProcVdpZmeReso(HI_PQ_PROC_VDPZME_RESO_S *pstProcVdpZmeReso)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstProcVdpZmeReso);

    PQ_SAFE_MEMCPY(pstProcVdpZmeReso, &sg_stProcVdpZmeReso, sizeof(sg_stProcVdpZmeReso));

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetProcWbcStrategy(HI_PQ_PROC_WBC_LAYER_E enProcWbcLayer, HI_PQ_PROC_WBC_STRATEGY_S *pstProcWbcStrategy)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstProcWbcStrategy);

    PQ_SAFE_MEMCPY(pstProcWbcStrategy, &sg_stGetProcWbcStrategy[enProcWbcLayer], sizeof(HI_PQ_PROC_WBC_STRATEGY_S));

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetZmeStreamId(HI_U32 u32StreamId)
{
    sg_u32StreamId = u32StreamId;

    return HI_SUCCESS;
}

