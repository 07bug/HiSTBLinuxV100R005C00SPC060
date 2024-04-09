/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_gfxzme.c
  Version       : Initial Draft
  Author        : sdk sdk
  Created       : 2015/10/15
  Description   :

******************************************************************************/

#ifndef HI_BUILD_IN_BOOT
#include "pq_mng_gfxzme.h"
#else
#include "drv_pq_ext.h"
#ifndef HI_MINIBOOT_SUPPORT
#include <linux/string.h>
#else
#include "string.h"
#endif
#include "hi_type.h"
#include "uboot.h"
#endif

#include "pq_mng_gfxzme_coef.h"
#include "pq_hal_gfxzme.h"

/***************************** Macro Definition ******************************/
#define VOU_BIT_VALUE(a)    (a)
#define SHARPEN_MAX_WIDTH   3840
#define MAX_GP_NUM          3
#define GZME_MMZ_SIZE       ((128 + 256) * 7)

static HI_BOOL        g_bGfxZmeInitFlag      = HI_FALSE;
static HI_BOOL        gs_bResume[MAX_GP_NUM] = {HI_FALSE, HI_FALSE, HI_FALSE};
static PQ_GZME_MEM_S  gs_stGPZme;  /** ZME Coef buffer **/

static HI_S32 PQ_MNG_GZmeHTransCoefAlign(const HI_S16 *ps16Coef, HI_S16 s16CoefNumber, HI_S16 *pBitCoef)
{
    HI_U32 i;

    /* depend on logic how to place */
    for (i = 0; i < s16CoefNumber; i++)
    {
        *pBitCoef++ = *(ps16Coef + (i / 8 + 1) * 8 - (i % 8) - 1);
    }

    return (s16CoefNumber * 2);
}

static HI_S32 PQ_MNG_GZmeVTransCoefAlign(const HI_S16 *ps16Coef, HI_S16 s16CoefNumber, HI_S16 *pBitCoef)
{
    HI_U32 i;

    /* depend on logic how to place */
    for (i = 0; i < s16CoefNumber; i++)
    {
        *pBitCoef++ = *(ps16Coef + (i / 8 + 1) * 8 - (i % 8) - 1);
    }

    return (s16CoefNumber * 2);
}

/***************************************************************************************
* func          : PQ_MNG_GZmeLoadCoefH
* description   : CNcomment: 水平ZME系数 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 PQ_MNG_GZmeLoadCoefH(PQ_GZME_COEF_RATIO_E enCoefRatio, HI_U8 *pu8Addr)
{
    HI_S16 s16TableTmp[8 * 8];
    HI_U32 u32TableTmpSize;

    memset(s16TableTmp, 0, sizeof(s16TableTmp));

    u32TableTmpSize = PQ_MNG_GZmeHTransCoefAlign(g_pPQGfxZmeReduceCoef[enCoefRatio][PQ_GZME_COEF_8T8P_LH], (HI_S16)(8 * 8), s16TableTmp);

    PQ_CHECK_NULL_PTR_RE_FAIL(pu8Addr);
    PQ_CHECK_NULL_PTR_RE_FAIL(pu8Addr + u32TableTmpSize);

    memcpy(pu8Addr, s16TableTmp, u32TableTmpSize);

    return HI_SUCCESS;
}
/***************************************************************************************
* func          : PQ_MNG_GZmeLoadCoefV
* description   : CNcomment: 垂直ZME系数 CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_S32 PQ_MNG_GZmeLoadCoefV(PQ_GZME_COEF_RATIO_E enCoefRatio, HI_U8 *pu8Addr)
{
    HI_S16 s16TableTmp[16 * 8];
    HI_U32 u32TableTmpSize;

    memset(s16TableTmp, 0, sizeof(s16TableTmp));

    u32TableTmpSize = PQ_MNG_GZmeVTransCoefAlign(g_pPQGfxZmeReduceCoef[enCoefRatio][PQ_GZME_COEF_4T16P_LV], (HI_S16)(16 * 8), s16TableTmp);

    PQ_CHECK_NULL_PTR_RE_FAIL(pu8Addr);
    PQ_CHECK_NULL_PTR_RE_FAIL(pu8Addr + u32TableTmpSize);

    memcpy(pu8Addr, s16TableTmp, u32TableTmpSize);

    return HI_SUCCESS;
}

/***************************************************************************************
* func          : PQ_MNG_GZmeLoadCoefHV
* description   : CNcomment: load zme coef CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
static HI_VOID PQ_MNG_GZmeLoadCoefHV(PQ_GZME_MEM_S *pstGZmeCoefMem)
{
    HI_U8 *pu8CurAddr  = 0;
    HI_U32 u32NumSize  = 0;
    HI_U32 u32PhyAddr  = 0;
    PQ_GZME_COEF_ADDR_S *pstAddrTmp = NULL;
    pu8CurAddr = pstGZmeCoefMem->stMBuf.pu8StartVirAddr;
    u32PhyAddr = pstGZmeCoefMem->stMBuf.u32StartPhyAddr;

    pstAddrTmp = &(pstGZmeCoefMem->stZmeCoefAddr);

    /* ----------gfx zme : H + V-------------- */
    PQ_MNG_GZmeLoadCoefH(PQ_GZME_COEF_1, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL_1 = u32PhyAddr;
    u32NumSize = 128 ;
    u32PhyAddr  += u32NumSize;
    pu8CurAddr  += u32NumSize;

    PQ_MNG_GZmeLoadCoefV(PQ_GZME_COEF_1,  pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL_1 = u32PhyAddr;
    u32NumSize = 256 ;
    u32PhyAddr   += u32NumSize;
    pu8CurAddr   += u32NumSize;

    /* ------------------------ */
    PQ_MNG_GZmeLoadCoefH(PQ_GZME_COEF_E1, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL_E1 = u32PhyAddr;
    u32NumSize = 128 ;
    u32PhyAddr  += u32NumSize;
    pu8CurAddr  += u32NumSize;

    PQ_MNG_GZmeLoadCoefV(PQ_GZME_COEF_E1,  pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL_E1 = u32PhyAddr;
    u32NumSize = 256 ;
    u32PhyAddr   += u32NumSize;
    pu8CurAddr   += u32NumSize;

    /* ------------------------ */
    PQ_MNG_GZmeLoadCoefH(PQ_GZME_COEF_075, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL_075 = u32PhyAddr;
    u32NumSize = 128 ;
    u32PhyAddr  += u32NumSize;
    pu8CurAddr  += u32NumSize;

    PQ_MNG_GZmeLoadCoefV(PQ_GZME_COEF_075,  pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL_075 = u32PhyAddr;
    u32NumSize = 256 ;
    u32PhyAddr   += u32NumSize;
    pu8CurAddr   += u32NumSize;

    /* ------------------------ */
    PQ_MNG_GZmeLoadCoefH(PQ_GZME_COEF_05, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL_05 = u32PhyAddr;
    u32NumSize = 128 ;
    u32PhyAddr  += u32NumSize;
    pu8CurAddr  += u32NumSize;

    PQ_MNG_GZmeLoadCoefV(PQ_GZME_COEF_05,  pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL_05 = u32PhyAddr;
    u32NumSize = 256 ;
    u32PhyAddr   += u32NumSize;
    pu8CurAddr   += u32NumSize;

    /* ------------------------ */
    PQ_MNG_GZmeLoadCoefH(PQ_GZME_COEF_033, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL_033 = u32PhyAddr;
    u32NumSize = 128 ;
    u32PhyAddr  += u32NumSize;
    pu8CurAddr  += u32NumSize;

    PQ_MNG_GZmeLoadCoefV(PQ_GZME_COEF_033,  pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL_033 = u32PhyAddr;
    u32NumSize = 256 ;
    u32PhyAddr   += u32NumSize;
    pu8CurAddr   += u32NumSize;

    /* ------------------------ */
    PQ_MNG_GZmeLoadCoefH(PQ_GZME_COEF_025, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL_025 = u32PhyAddr;
    u32NumSize = 128 ;
    u32PhyAddr  += u32NumSize;
    pu8CurAddr  += u32NumSize;

    PQ_MNG_GZmeLoadCoefV(PQ_GZME_COEF_025,  pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL_025 = u32PhyAddr;
    u32NumSize = 256 ;
    u32PhyAddr   += u32NumSize;
    pu8CurAddr   += u32NumSize;

    /* ------------------------ */
    PQ_MNG_GZmeLoadCoefH(PQ_GZME_COEF_0, pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrHL_0 = u32PhyAddr;
    u32NumSize = 128 ;
    u32PhyAddr  += u32NumSize;
    pu8CurAddr  += u32NumSize;

    PQ_MNG_GZmeLoadCoefV(PQ_GZME_COEF_0,  pu8CurAddr);
    pstAddrTmp->u32ZmeCoefAddrVL_0 = u32PhyAddr;
    u32NumSize = 256 ;
    u32PhyAddr   += u32NumSize;
    pu8CurAddr   += u32NumSize;
}

static PQ_GZME_ORDER_E pq_mng_GetGZmeOrder(HI_U32 u32ZmeFrmWOut, HI_U32 u32ZmeFrmWIn)
{
    PQ_GZME_ORDER_E enGZmeOrder = PQ_GZME_ORDER_VH; /* Ver First */

    /**
       * Default is V First, Ver Filter uses four line buffer, Hor first can save same calculations,
       * But in HiFoneB2, Because Line Buffer is 8bits, So default is Ver first
       **/
    if ((u32ZmeFrmWOut > 1920) && (u32ZmeFrmWIn <= 1920))
    {
        enGZmeOrder = PQ_GZME_ORDER_VH; /* Ver First */
    }
    else if ((u32ZmeFrmWOut <= 1920) && (u32ZmeFrmWIn > 1920))
    {
        enGZmeOrder = PQ_GZME_ORDER_HV; /* Hor First */
    }

    return enGZmeOrder;
}

static PQ_GZME_VER_TAP_E pq_mng_GetGZmeTapV(HI_U32 u32ZmeFrmWOut, HI_U32 u32ZmeFrmWIn)
{
    PQ_GZME_VER_TAP_E enVerTap = PQ_GZME_VER_TAP_4; /* Ver 4Tap */


    if (u32ZmeFrmWOut == u32ZmeFrmWIn)
    {
        enVerTap  = PQ_GZME_VER_TAP_4; /* Ver 4Tap */
    }
    else
    {
        if (u32ZmeFrmWIn <= 1920)
        {
            enVerTap  = PQ_GZME_VER_TAP_4; /* Ver 4Tap */
        }
        else
        {
            enVerTap  = PQ_GZME_VER_TAP_2; /* Ver 2Tap */
        }
    }

    return enVerTap;
}

static HI_VOID PQ_MNG_GZmeComnSet(HI_PQ_GFX_ZME_PARA_S *pstZmeDrvPara, PQ_GZME_RTL_PARA_S *pstZmeRtlPara)
{
    HI_U32 u32VZmeRealRatio;
    PQ_GZME_ORDER_E enOrder = PQ_GZME_ORDER_HV;
    PQ_GZME_VER_TAP_E enTap = PQ_GZME_VER_TAP_4;

    /* config zme enable */
    pstZmeRtlPara->bZmeEnH = (pstZmeDrvPara->u32ZmeFrmWIn == pstZmeDrvPara->u32ZmeFrmWOut) ? HI_FALSE : HI_TRUE;

    if ( (pstZmeDrvPara->u32ZmeFrmHIn == pstZmeDrvPara->u32ZmeFrmHOut)
         && (pstZmeDrvPara->bZmeFrmFmtIn == pstZmeDrvPara->bZmeFrmFmtOut))
    {
        pstZmeRtlPara->bZmeEnV = HI_FALSE;
    }
    else
    {
        pstZmeRtlPara->bZmeEnV = HI_TRUE;
    }

    /* modified by sdk for opening sharp module 2013/6/22 Himedia problem
       modified by sdk for closing sharp module 2013/12/10 TC problem
       */
    if (pstZmeRtlPara->bZmeEnH == HI_TRUE || pstZmeRtlPara->bZmeEnV == HI_TRUE)
    {
        pstZmeRtlPara->bZmeEnH = HI_TRUE;
        pstZmeRtlPara->bZmeEnV = HI_TRUE;
    }

    /* config vertical chroma zme tap and zme order */
    pstZmeRtlPara->bZmeTapVC = 0;

    enOrder = pq_mng_GetGZmeOrder(pstZmeDrvPara->u32ZmeFrmWOut,
                                  pstZmeDrvPara->u32ZmeFrmWIn);
    if (PQ_GZME_ORDER_HV == enOrder)
    {
        pstZmeRtlPara->bZmeOrder = HI_FALSE;
    }
    else
    {
        pstZmeRtlPara->bZmeOrder = HI_TRUE;
    }

    enTap = pq_mng_GetGZmeTapV(pstZmeDrvPara->u32ZmeFrmWOut,
                               pstZmeDrvPara->u32ZmeFrmWIn);
    if (PQ_GZME_VER_TAP_4 == enTap)
    {
        pstZmeRtlPara->bZmeTapV = HI_FALSE;
    }
    else
    {
        pstZmeRtlPara->bZmeTapV = HI_TRUE;
    }

    /* config zme ratio, pay attention: this vertical ratio may not be the real ratio
       logic would calculate the real ratio according to the input and output frame format.
       */
    PQ_CHECK_ZERO_RE_NULL(pstZmeDrvPara->u32ZmeFrmWOut);

    if (pstZmeDrvPara->u32ZmeFrmWIn >= 4096) /* [4096,8192) */
    {
        pstZmeRtlPara->u32ZmeRatioHL = (pstZmeDrvPara->u32ZmeFrmWIn / 2 * PQ_G_HZME_PRECISION) / pstZmeDrvPara->u32ZmeFrmWOut * 2;
    }
    else
    {
        pstZmeRtlPara->u32ZmeRatioHL = pstZmeDrvPara->u32ZmeFrmWIn * PQ_G_HZME_PRECISION / pstZmeDrvPara->u32ZmeFrmWOut;
    }

    PQ_CHECK_ZERO_RE_NULL(pstZmeDrvPara->u32ZmeFrmHOut);

    pstZmeRtlPara->u32ZmeRatioVL = pstZmeDrvPara->u32ZmeFrmHIn * PQ_G_VZME_PRECISION / pstZmeDrvPara->u32ZmeFrmHOut;
    pstZmeRtlPara->u32ZmeRatioHC = pstZmeRtlPara->u32ZmeRatioHL;
    pstZmeRtlPara->u32ZmeRatioVC = pstZmeRtlPara->u32ZmeRatioVL;

    /* calculate luma real zme resolution of input and output */
    if ( (pstZmeDrvPara->bZmeFrmFmtIn == 1) && (pstZmeDrvPara->bZmeFrmFmtOut == 0) )
    {
        u32VZmeRealRatio = pstZmeRtlPara->u32ZmeRatioVL * 2;
    }
    else
    {
        u32VZmeRealRatio = pstZmeRtlPara->u32ZmeRatioVL;
    }

    /* calculate horizontal zme offset */
    pstZmeRtlPara->s32ZmeOffsetHL = 0;
    pstZmeRtlPara->s32ZmeOffsetHC = 0;

    /* calculate vertical zme offset: offset is the real offset! */
    pstZmeRtlPara->s32ZmeOffsetVTop = 0;
    if ( (pstZmeDrvPara->bZmeFrmFmtIn == 0) && (pstZmeDrvPara->bZmeFrmFmtOut == 0) )
    {
        pstZmeRtlPara->s32ZmeOffsetVBtm = ( (HI_S32)u32VZmeRealRatio - PQ_G_VZME_PRECISION ) / 2;
    }
    else if ( (pstZmeDrvPara->bZmeFrmFmtIn == 1) && (pstZmeDrvPara->bZmeFrmFmtOut == 0) )
    {
        pstZmeRtlPara->s32ZmeOffsetVBtm = (HI_S32)u32VZmeRealRatio / 2;
    }
    else
    {
        pstZmeRtlPara->s32ZmeOffsetVBtm = 0;
    }

    /* config zme mode */
    if ( pstZmeRtlPara->u32ZmeRatioHL == PQ_G_HZME_PRECISION ) /* when 1:1 horizontal scaler, directly copy */
    {
        pstZmeRtlPara->bZmeMdHA  = 0;
        pstZmeRtlPara->bZmeMdHLC = 0;
    }
    else
    {
        pstZmeRtlPara->bZmeMdHA  = 1;
        pstZmeRtlPara->bZmeMdHLC = 1;
    }

    /* modified by sdk for opening sharp module 2013/6/22 Himedia problem */
    pstZmeRtlPara->bZmeMdHA  = 1;
    pstZmeRtlPara->bZmeMdHLC = 1;

    /* considering anti-flicker for SD, the situation of 1:1 vertical scaler also need low-pass filter */
    pstZmeRtlPara->bZmeMdVA  = 1;
    pstZmeRtlPara->bZmeMdVLC = 1;

    /* config zme median filter enable: if filter tap > 2 and upscaler, median filter enable */
    if (pstZmeRtlPara->u32ZmeRatioHL < PQ_G_HZME_PRECISION)
    {
        pstZmeRtlPara->bZmeMedHA = 1;
        pstZmeRtlPara->bZmeMedHL = 1;
        pstZmeRtlPara->bZmeMedHC = 1;
    }
    else
    {
        pstZmeRtlPara->bZmeMedHA = 0;
        pstZmeRtlPara->bZmeMedHL = 0;
        pstZmeRtlPara->bZmeMedHC = 0;
    }

    if (pstZmeRtlPara->u32ZmeRatioVL < PQ_G_VZME_PRECISION && pstZmeRtlPara->bZmeTapVC == 0)
    {
        pstZmeRtlPara->bZmeMedVA = 1;
        pstZmeRtlPara->bZmeMedVL = 1;
        pstZmeRtlPara->bZmeMedVC = 1;
    }
    else
    {
        pstZmeRtlPara->bZmeMedVA = 0;
        pstZmeRtlPara->bZmeMedVL = 0;
        pstZmeRtlPara->bZmeMedVC = 0;
    }
    return;
}

static HI_S32 PQ_MNG_GetGfxHLfirCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if      (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHL_1;
    }
    //else if (u32TmpRatio == 4096) { u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHL_E1;}
    else if (u32TmpRatio >= 3482)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHL_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHL_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHL_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHL_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHL_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHL_0;
    }

    return u32CoefAddr;
}

static HI_S32 PQ_MNG_GetGfxHCfirCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if     (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHC_1;
    }
    else if (u32TmpRatio >= 3482)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHC_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHC_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHC_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHC_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHC_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrHC_0;
    }

    return u32CoefAddr;
}

static HI_S32 PQ_MNG_GetGfxVLfirCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if     (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVL_1;
    }
    //else if(u32TmpRatio == 4096) { u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVL_E1; }
    else if (u32TmpRatio >= 3482)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVL_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVL_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVL_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVL_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVL_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVL_0;
    }

    return u32CoefAddr;
}

static HI_S32 PQ_MNG_GetGfxVCfirCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if     (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVC_1;
    }
    else if (u32TmpRatio >= 3482)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVC_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVC_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVC_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVC_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVC_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVC_0;
    }

    return u32CoefAddr;
}

/* add from HiFoneB2 for 4K tiny zme */
static HI_S32 PQ_MNG_GetGfxTinyZMEVLfirCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if     (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVL_1;
    }
    //else if(u32TmpRatio == 4096) { u32CoefAddr = pstZmeCoefAddr->u32ZmeCoefAddrVL_E1;      }
    else if (u32TmpRatio >= 3264)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVL_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVL_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVL_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVL_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVL_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVL_0;
    }

    return u32CoefAddr;
}

/* add from HiFoneB2 for 4K tiny zme */
static HI_S32 PQ_MNG_GetGfxTinyZMEVCfirCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if     (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVC_1;
    }
    else if (u32TmpRatio == 4096)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVC_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVC_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVC_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVC_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVC_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32Zme2T16PCoefAddrVC_0;
    }

    return u32CoefAddr;
}

static HI_S32 PQ_MNG_GetGfxHLfirSDCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if      (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHL_1;
    }
    else if (u32TmpRatio == 4096)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHL_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHL_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHL_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHL_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHL_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHL_0;
    }

    return u32CoefAddr;
}

static HI_S32 PQ_MNG_GetGfxVLfirSDCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if     (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVL_1;
    }
    else if (u32TmpRatio == 4096)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVL_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVL_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVL_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVL_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVL_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVL_0;
    }

    return u32CoefAddr;
}


static HI_S32 PQ_MNG_GetGfxVCfirSDCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if     (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVC_1;
    }
    else if (u32TmpRatio == 4096)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVC_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVC_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVC_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVC_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVC_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrVC_0;
    }

    return u32CoefAddr;
}

static HI_S32 PQ_MNG_GetGfxHCfirSDCoef(PQ_GZME_COEF_ADDR_S *pstZmeCoefAddr, HI_U32 u32Ratio)
{
    HI_U32 u32CoefAddr;
    HI_U32 u32TmpRatio;

    PQ_CHECK_ZERO_RE_FAIL(u32Ratio);

    u32TmpRatio = 4096 * 4096 / u32Ratio;

    if      (u32TmpRatio > 4096 )
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHC_1;
    }
    else if (u32TmpRatio == 4096)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHC_E1;
    }
    else if (u32TmpRatio >= 3072)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHC_075;
    }
    else if (u32TmpRatio >= 2048)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHC_05;
    }
    else if (u32TmpRatio >= 1365)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHC_033;
    }
    else if (u32TmpRatio >= 1024)
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHC_025;
    }
    else
    {
        u32CoefAddr = pstZmeCoefAddr->u32ZmeSDCoefAddrHC_0;
    }

    return u32CoefAddr;
}

static HI_VOID PQ_MNG_GZmeHDSet(HI_PQ_GFX_ZME_PARA_S *pstZmeDrvPara, PQ_GZME_RTL_PARA_S *pstZmeRtlPara)
{
    if (0 == pstZmeRtlPara->bZmeTapV)
    {
        pstZmeRtlPara->u32ZmeCoefAddrHL = PQ_MNG_GetGfxHLfirCoef( &(gs_stGPZme.stZmeCoefAddr), (pstZmeRtlPara->u32ZmeRatioHL) >> PQ_PRECISION_GZMERATIONH_12BITOFFSET);
        pstZmeRtlPara->u32ZmeCoefAddrHC = PQ_MNG_GetGfxHCfirCoef( &(gs_stGPZme.stZmeCoefAddr), (pstZmeRtlPara->u32ZmeRatioHC) >> PQ_PRECISION_GZMERATIONH_12BITOFFSET);
        pstZmeRtlPara->u32ZmeCoefAddrVL = PQ_MNG_GetGfxVLfirCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioVL);
        pstZmeRtlPara->u32ZmeCoefAddrVC = PQ_MNG_GetGfxVCfirCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioVC);
    }
    else
    {
        /** GZME_VER_TAP_2 **/
        pstZmeRtlPara->u32ZmeCoefAddrHL = PQ_MNG_GetGfxHLfirCoef( &(gs_stGPZme.stZmeCoefAddr), (pstZmeRtlPara->u32ZmeRatioHL) >> PQ_PRECISION_GZMERATIONH_12BITOFFSET);
        pstZmeRtlPara->u32ZmeCoefAddrHC = PQ_MNG_GetGfxHCfirCoef( &(gs_stGPZme.stZmeCoefAddr), (pstZmeRtlPara->u32ZmeRatioHC) >> PQ_PRECISION_GZMERATIONH_12BITOFFSET);
        pstZmeRtlPara->u32ZmeCoefAddrVL = PQ_MNG_GetGfxTinyZMEVLfirCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioVL);
        pstZmeRtlPara->u32ZmeCoefAddrVC = PQ_MNG_GetGfxTinyZMEVCfirCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioVC);
    }

    return;
}


static HI_VOID PQ_MNG_GZmeSDSet(HI_PQ_GFX_ZME_PARA_S *pstZmeDrvPara, PQ_GZME_RTL_PARA_S *pstZmeRtlPara)
{
    if (HI_TRUE == pstZmeDrvPara->bDeFlicker)
    {
        pstZmeRtlPara->u32ZmeCoefAddrHL = PQ_MNG_GetGfxHLfirSDCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioHL);
        pstZmeRtlPara->u32ZmeCoefAddrHC = PQ_MNG_GetGfxHCfirSDCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioHC);
        pstZmeRtlPara->u32ZmeCoefAddrVL = PQ_MNG_GetGfxVLfirSDCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioVL);
        pstZmeRtlPara->u32ZmeCoefAddrVC = PQ_MNG_GetGfxVCfirSDCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioVC);
    }
    else
    {
        pstZmeRtlPara->u32ZmeCoefAddrHL = PQ_MNG_GetGfxHLfirCoef( &(gs_stGPZme.stZmeCoefAddr), (pstZmeRtlPara->u32ZmeRatioHL) >> PQ_PRECISION_GZMERATIONH_12BITOFFSET);
        pstZmeRtlPara->u32ZmeCoefAddrHC = PQ_MNG_GetGfxHCfirCoef( &(gs_stGPZme.stZmeCoefAddr), (pstZmeRtlPara->u32ZmeRatioHC) >> PQ_PRECISION_GZMERATIONH_12BITOFFSET);
        pstZmeRtlPara->u32ZmeCoefAddrVL = PQ_MNG_GetGfxVLfirCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioVL);
        pstZmeRtlPara->u32ZmeCoefAddrVC = PQ_MNG_GetGfxVCfirCoef( &(gs_stGPZme.stZmeCoefAddr), pstZmeRtlPara->u32ZmeRatioVC);
    }
    return;
}

static HI_S32 PQ_MNG_SetGfxZmeRegCfg(HI_PQ_GFX_LAYER_E enGfxZmeLayer, HI_BOOL bSlvGp, PQ_GZME_RTL_PARA_S *pstZmeRtlPara)
{
    /* zme enable horizontal */
    if (enGfxZmeLayer != PQ_GFX_GP0)
    {
        return HI_FAILURE;
    }

    PQ_HAL_SetGZmeEnable(enGfxZmeLayer, PQ_GZME_MODE_HOR, pstZmeRtlPara->bZmeEnH);
    PQ_HAL_SetGZmeEnable(enGfxZmeLayer, PQ_GZME_MODE_VER, pstZmeRtlPara->bZmeEnV);

    PQ_HAL_SetGZmeTabV(enGfxZmeLayer, pstZmeRtlPara->bZmeTapV);

    if (pstZmeRtlPara->bZmeEnH || pstZmeRtlPara->bZmeEnV)
    {
        /**
         ** 设置GP CTRL，包括WBC_GP0是否绑定到GP1 ZME上以及LBOX使能等
         **/
        PQ_HAL_SetGZmeHfirOrder       (enGfxZmeLayer, PQ_GZME_ORDER_HV);

        /*set zme mode of horizontal luma and chroma*/
        PQ_HAL_SetGZmeFirEnable       (enGfxZmeLayer, PQ_GZME_MODE_HOR, pstZmeRtlPara->bZmeMdHLC);
        PQ_HAL_SetGZmeFirEnable       (enGfxZmeLayer, PQ_GZME_MODE_ALPHA, pstZmeRtlPara->bZmeMdHLC);
        /*set zme mode of horizontal alpha*/
        PQ_HAL_SetGZmeMidEnable       (enGfxZmeLayer, PQ_GZME_MODE_ALPHA, pstZmeRtlPara->bZmeMedHA);
        PQ_HAL_SetGZmeMidEnable       (enGfxZmeLayer, PQ_GZME_MODE_HORL, pstZmeRtlPara->bZmeMedHL);
        PQ_HAL_SetGZmeMidEnable       (enGfxZmeLayer, PQ_GZME_MODE_HORC, pstZmeRtlPara->bZmeMedHC);
        PQ_HAL_SetGZmePhase           (enGfxZmeLayer, PQ_GZME_MODE_HORL, pstZmeRtlPara->s32ZmeOffsetHL);
        PQ_HAL_SetGZmePhase           (enGfxZmeLayer, PQ_GZME_MODE_HORC, pstZmeRtlPara->s32ZmeOffsetHC);
        PQ_HAL_SetGZmeHorRatio        (enGfxZmeLayer, pstZmeRtlPara->u32ZmeRatioHL);

        /*set zme mode of horizontal luma and chroma*/
        PQ_HAL_SetGZmeFirEnable       (enGfxZmeLayer, PQ_GZME_MODE_VER, pstZmeRtlPara->bZmeMdVLC);
        PQ_HAL_SetGZmeFirEnable       (enGfxZmeLayer, PQ_GZME_MODE_ALPHAV, pstZmeRtlPara->bZmeMdVLC);
        /*set zme mode of horizontal alpha*/
        PQ_HAL_SetGZmeMidEnable       (enGfxZmeLayer, PQ_GZME_MODE_ALPHAV, pstZmeRtlPara->bZmeMedVA);
        PQ_HAL_SetGZmeMidEnable       (enGfxZmeLayer, PQ_GZME_MODE_VERL, pstZmeRtlPara->bZmeMedVL);
        PQ_HAL_SetGZmeMidEnable       (enGfxZmeLayer, PQ_GZME_MODE_VERC, pstZmeRtlPara->bZmeMedVC);
        PQ_HAL_SetGZmePhase           (enGfxZmeLayer, PQ_GZME_MODE_VERL, pstZmeRtlPara->s32ZmeOffsetVBtm);
        PQ_HAL_SetGZmePhase           (enGfxZmeLayer, PQ_GZME_MODE_VERC, pstZmeRtlPara->s32ZmeOffsetVTop);
        PQ_HAL_SetGZmeVerRatio        (enGfxZmeLayer, pstZmeRtlPara->u32ZmeRatioVL);

        PQ_HAL_SetGZmeHfirOrder(enGfxZmeLayer, pstZmeRtlPara->bZmeOrder);

        PQ_HAL_SetGZmeCoefAddr        (enGfxZmeLayer, PQ_GP_PARA_ZME_HOR, pstZmeRtlPara->u32ZmeCoefAddrHL);
        PQ_HAL_SetGZmeParaUpd         (enGfxZmeLayer, PQ_GP_PARA_ZME_HOR);
    }

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_SetGfxResume(HI_BOOL bDefault)
{
    gs_bResume[PQ_GFX_GP0] = HI_TRUE;
    gs_bResume[PQ_GFX_GP1] = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetGfxZme(HI_PQ_GFX_LAYER_E enGfxZmeLayer, HI_PQ_GFX_ZME_PARA_S *pstGfxZmePara)
{
    HI_S32  s32Ret;
    HI_BOOL bChange = HI_FALSE;
    PQ_GZME_RTL_PARA_S stZmeRtlPara = {0};
    static HI_PQ_GFX_ZME_PARA_S stZmePara[PQ_GFX_LAYER_BUTT] = {{0}};

    PQ_CHECK_OVER_RANGE_RE_FAIL(enGfxZmeLayer, PQ_GFX_LAYER_BUTT);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstGfxZmePara);

    if (PQ_GFX_GP0 != enGfxZmeLayer)
    {
        return HI_SUCCESS;
    }

    if (HI_FALSE == pstGfxZmePara->bZmeFrmFmtOut)
    {
        PQ_HAL_SetGZmeEnable(enGfxZmeLayer, PQ_GZME_MODE_VER, HI_TRUE);
    }

    bChange  =  (stZmePara[enGfxZmeLayer].u32ZmeFrmWIn != pstGfxZmePara->u32ZmeFrmWIn)
                || (stZmePara[enGfxZmeLayer].u32ZmeFrmHIn != pstGfxZmePara->u32ZmeFrmHIn)
                || (stZmePara[enGfxZmeLayer].u32ZmeFrmWOut != pstGfxZmePara->u32ZmeFrmWOut)
                || (stZmePara[enGfxZmeLayer].u32ZmeFrmHOut != pstGfxZmePara->u32ZmeFrmHOut)
                || (stZmePara[enGfxZmeLayer].bZmeFrmFmtIn != pstGfxZmePara->bZmeFrmFmtIn)
                || (stZmePara[enGfxZmeLayer].bZmeFrmFmtOut != pstGfxZmePara->bZmeFrmFmtOut)
                || (stZmePara[enGfxZmeLayer].bDeFlicker != pstGfxZmePara->bDeFlicker);

    if ( (HI_FALSE == bChange) && (HI_FALSE == gs_bResume[PQ_GFX_GP0]) && (HI_FALSE == gs_bResume[PQ_GFX_GP1]))
    {
        return HI_SUCCESS;
    }
    gs_bResume[enGfxZmeLayer] = HI_FALSE;

    PQ_MNG_GZmeComnSet(pstGfxZmePara, &stZmeRtlPara);

    if (PQ_GFX_GP0 == enGfxZmeLayer)
    {
        PQ_MNG_GZmeHDSet(pstGfxZmePara, &stZmeRtlPara);
    }
    else if (PQ_GFX_GP1 == enGfxZmeLayer)
    {
        PQ_MNG_GZmeSDSet(pstGfxZmePara, &stZmeRtlPara);
    }

    if (pstGfxZmePara->u32ZmeFrmWIn > SHARPEN_MAX_WIDTH)
    {
        stZmeRtlPara.bZmeEnH = HI_FALSE;
        stZmeRtlPara.bZmeEnV = HI_FALSE;
    }

    memcpy(&stZmePara[enGfxZmeLayer], pstGfxZmePara, sizeof(HI_PQ_GFX_ZME_PARA_S));

    s32Ret = PQ_MNG_SetGfxZmeRegCfg(enGfxZmeLayer, pstGfxZmePara->bSlvGp, &stZmeRtlPara);

    return s32Ret;
}

#ifndef HI_BUILD_IN_BOOT
HI_S32 PQ_MNG_InitGfxZme(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault)
#else
HI_S32 PQ_MNG_InitGfxZme(HI_VOID)
#endif
{
    HI_S32 s32Ret = HI_SUCCESS;
    PQ_MMZ_BUF_S stMMZ = {0};

    if (g_bGfxZmeInitFlag)
    {
        return HI_SUCCESS;
    }

    s32Ret = PQ_HAL_MMZ_AllocAndMap("PQ_GfxZmeCoef", HI_NULL, GZME_MMZ_SIZE, 16, &stMMZ);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_MNG_MMZ_AllocAndMap failed\n");
        g_bGfxZmeInitFlag = HI_FALSE;

        return HI_FAILURE;
    }

    gs_stGPZme.stMBuf.u32StartPhyAddr = stMMZ.u32StartPhyAddr;
    gs_stGPZme.stMBuf.pu8StartVirAddr = stMMZ.pu8StartVirAddr;
    gs_stGPZme.stMBuf.u32Size         = stMMZ.u32Size;

    /**
     ** load zme coefficient into the memory
     **/
    PQ_MNG_GZmeLoadCoefHV(&gs_stGPZme);

    g_bGfxZmeInitFlag = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_DeInitGfxZme(HI_VOID)
{
    if (HI_FALSE == g_bGfxZmeInitFlag)
    {
        return HI_SUCCESS;
    }

    /* release zme coefficient memory */
    if (gs_stGPZme.stMBuf.pu8StartVirAddr != HI_NULL)
    {
        //HI_DRV_MMZ_UnmapAndRelease(&(gs_stGPZme.stMBuf));
        PQ_HAL_MMZ_UnmapAndRelease((PQ_MMZ_BUF_S *) & (gs_stGPZme.stMBuf));
        gs_stGPZme.stMBuf.pu8StartVirAddr = HI_NULL;
        gs_stGPZme.stMBuf.u32StartPhyAddr = 0;
    }

    g_bGfxZmeInitFlag = HI_FALSE;

    return HI_SUCCESS;
}
#ifdef HI_BUILD_IN_BOOT
HI_S32 DRV_PQ_SetGfxZme(HI_PQ_GFX_LAYER_E enGfxZmeLayer, HI_PQ_GFX_ZME_PARA_S *pstGfxZmePara)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_MNG_SetGfxZme(enGfxZmeLayer, pstGfxZmePara);

    return s32Ret;
}
HI_S32 DRV_PQ_InitGfxZme()
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_MNG_InitGfxZme();

    return s32Ret;
}
#else

static stPQAlgFuncs stGfxZMEFuncs =
{
    .Init               = PQ_MNG_InitGfxZme,
    .DeInit             = PQ_MNG_DeInitGfxZme,
    .SetGfxZme          = PQ_MNG_SetGfxZme,
    .SetResume          = PQ_MNG_SetGfxResume,
};

HI_S32 PQ_MNG_RegisterGfxZme(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_GFXZME, REG_TYPE_ALL, PQ_BIN_ADAPT_SINGLE, "gfx zme", HI_NULL, &stGfxZMEFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterGfxZme()
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_GFXZME);

    return s32Ret;
}
#endif

