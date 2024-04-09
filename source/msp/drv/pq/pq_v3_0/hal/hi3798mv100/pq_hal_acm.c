/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************/

/*-----------------------------------------------------------------------------*/
/* Include Header Files                                                        */
/*-----------------------------------------------------------------------------*/
#include <linux/string.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"

#include "pq_hal_comm.h"
#include "pq_hal_acm.h"


#define VouBitValue(a) (a)
#define ACM_BUFFER    COEFACMCNT * sizeof(ACM_COEF_BIT_S) /* Mmz Buffer Size */
#define ACM_LUT_SIZE  sizeof(COLOR_ACM_LUT_S)             /* Lut Size */

static HI_BOOL sg_bHalAcmInit    = HI_FALSE;
static HI_BOOL sg_bHalAcmEn     = HI_TRUE;
static COLOR_ACM_LUT_S *sg_pstHalAcmLut = HI_NULL;
static MMZ_BUFFER_S     sg_stHalAcmBuffer;

static ACM_SPLIT_TABLE     *sg_pstSplitTable_Y = HI_NULL;
static ACM_SPLIT_TABLE     *sg_pstSplitTable_H = HI_NULL;
static ACM_SPLIT_TABLE     *sg_pstSplitTable_S = HI_NULL;
static ACM_COEF_BITARRAY_S *sg_pstAcmBitArray    = HI_NULL;

/* DeInit ACM */
HI_S32 PQ_HAL_DeInitACM(HI_VOID)
{
    if (HI_FALSE == sg_bHalAcmInit)
    {
        return HI_SUCCESS;
    }

    PQ_KFREE_SAFE(sg_pstHalAcmLut);
    PQ_KFREE_SAFE(sg_pstSplitTable_Y);
    PQ_KFREE_SAFE(sg_pstSplitTable_H);
    PQ_KFREE_SAFE(sg_pstSplitTable_S);
    PQ_KFREE_SAFE(sg_pstAcmBitArray);

    if (HI_NULL != sg_stHalAcmBuffer.pu8StartVirAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&sg_stHalAcmBuffer);
        sg_stHalAcmBuffer.pu8StartVirAddr = HI_NULL;
    }

    sg_bHalAcmInit = HI_FALSE;

    return HI_SUCCESS;
}

/* Init ACM */
HI_S32 PQ_HAL_InitACM(HI_VOID)
{
    HI_S32 s32Ret;
    if (HI_TRUE == sg_bHalAcmInit)
    {
        return HI_SUCCESS;
    }

    /* MMZ buffer */
    PQ_SAFE_MEMSET(&sg_stHalAcmBuffer, 0, sizeof(MMZ_BUFFER_S));

    s32Ret = HI_DRV_MMZ_AllocAndMap("PQ_ACM", HI_NULL, ACM_BUFFER, 0, &sg_stHalAcmBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_ACM memory allocated failed!\n");
        sg_bHalAcmInit = HI_FALSE;

        return HI_FAILURE;
    }
    PQ_SAFE_MEMSET((HI_U8 *)sg_stHalAcmBuffer.pu8StartVirAddr, 0, ACM_BUFFER);

    /* resource alloc */
    sg_pstHalAcmLut    = (void *)PQ_KMALLOC(ACM_LUT_SIZE, GFP_ATOMIC);
    sg_pstAcmBitArray  = (void *)PQ_KMALLOC(sizeof(ACM_COEF_BITARRAY_S), GFP_ATOMIC);
    sg_pstSplitTable_Y = (void *)PQ_KMALLOC(sizeof(ACM_SPLIT_TABLE), GFP_ATOMIC);
    sg_pstSplitTable_H = (void *)PQ_KMALLOC(sizeof(ACM_SPLIT_TABLE), GFP_ATOMIC);
    sg_pstSplitTable_S = (void *)PQ_KMALLOC(sizeof(ACM_SPLIT_TABLE), GFP_ATOMIC);

    if (!(sg_pstHalAcmLut && sg_pstAcmBitArray && sg_pstSplitTable_Y && sg_pstSplitTable_H && sg_pstSplitTable_S))
    {
        HI_DRV_MMZ_UnmapAndRelease(&sg_stHalAcmBuffer);
        sg_stHalAcmBuffer.pu8StartVirAddr = HI_NULL;

        PQ_KFREE_SAFE(sg_pstHalAcmLut);
        PQ_KFREE_SAFE(sg_pstSplitTable_Y);
        PQ_KFREE_SAFE(sg_pstSplitTable_H);
        PQ_KFREE_SAFE(sg_pstSplitTable_S);
        PQ_KFREE_SAFE(sg_pstAcmBitArray);

        HI_ERR_PQ("PQ_HAL_InitACM malloc fail !\n");

        sg_bHalAcmInit = HI_FALSE;
        return HI_FAILURE;
    }

    PQ_SAFE_MEMSET(sg_pstHalAcmLut, 0, ACM_LUT_SIZE);
    PQ_SAFE_MEMSET(sg_pstAcmBitArray, 0, sizeof(ACM_COEF_BITARRAY_S));
    PQ_SAFE_MEMSET(sg_pstSplitTable_Y, 0, sizeof(ACM_SPLIT_TABLE));
    PQ_SAFE_MEMSET(sg_pstSplitTable_H, 0, sizeof(ACM_SPLIT_TABLE));
    PQ_SAFE_MEMSET(sg_pstSplitTable_S, 0, sizeof(ACM_SPLIT_TABLE));

    sg_bHalAcmEn = HI_TRUE;

    sg_bHalAcmInit = HI_TRUE;

    return HI_SUCCESS;
}

HI_VOID PQ_HAL_SetACMAddr(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32CoefAddr)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CAD VP0_ACM_CAD;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CAD.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_ACM_CAD.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_ACM_CAD.bits.coef_addr = u32CoefAddr;
    PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_ACM_CAD.u32) + u32ChId * VDP_VP_OFFSET), VP0_ACM_CAD.u32);

    return;
}

static HI_S32 PQ_HAL_Split_Table(HI_S16 ps16OriLUT[5][7][29], ACM_SPLIT_TABLE *pSplitTbl)
{
    HI_S32 i, j, k;
    HI_S32 *pLUT0, *pLUT1, *pLUT2, *pLUT3, *pLUT4, *pLUT5, *pLUT6, *pLUT7;
    if (HI_NULL == pSplitTbl)
    {
        HI_ERR_PQ("pSplitTbl is NULL pointer!\n");
        return HI_FAILURE;
    }

    pLUT0 = pSplitTbl->LUT0; /* 指针 数组 */
    pLUT1 = pSplitTbl->LUT1;
    pLUT2 = pSplitTbl->LUT2;
    pLUT3 = pSplitTbl->LUT3;
    pLUT4 = pSplitTbl->LUT4;
    pLUT5 = pSplitTbl->LUT5;
    pLUT6 = pSplitTbl->LUT6;
    pLUT7 = pSplitTbl->LUT7;
    for (k = 0; k < 29; k++)
    {
        for (j = 0; j < 7; j++)
        {
            for (i = 0; i < 5; i++)
            {
                switch ((i & 1) + ((j & 1) << 1) + ((k & 1) << 2)) /* 按这种划分方式，逐一的给数组赋值 */
                {
                    case 0:
                        *pLUT0 = ps16OriLUT[i][j][k];
                        pLUT0++;
                        break;
                    case 1:
                        *pLUT1 = ps16OriLUT[i][j][k];
                        pLUT1++;
                        break;
                    case 2:
                        *pLUT2 = ps16OriLUT[i][j][k];
                        pLUT2++;
                        break;
                    case 3:
                        *pLUT3 = ps16OriLUT[i][j][k];
                        pLUT3++;
                        break;
                    case 4:
                        *pLUT4 = ps16OriLUT[i][j][k];
                        pLUT4++;
                        break;
                    case 5:
                        *pLUT5 = ps16OriLUT[i][j][k];
                        pLUT5++;
                        break;
                    case 6:
                        *pLUT6 = ps16OriLUT[i][j][k];
                        pLUT6++;
                        break;
                    case 7:
                        *pLUT7 = ps16OriLUT[i][j][k];
                        pLUT7++;
                        break;
                    default:
                        HI_ERR_PQ("ACM Split_Table ERROR!\n");
                        break;
                }
            }
        }
    }
    return HI_SUCCESS;
}

static HI_S32 PQ_HAL_AcmCoefConvert(ACM_SPLIT_TABLE *pstTab_Y, ACM_SPLIT_TABLE *pstTab_S,
                                    ACM_SPLIT_TABLE *pstTab_H, ACM_COEF_BITARRAY_S *pBitCoef)
{
    HI_S32 i, s32Tmp;
    ACM_PSCoef stACM_PSCoef;
    ACM_PSCoef *pACM_PSCoef = &stACM_PSCoef;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstTab_Y);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTab_S);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTab_H);
    PQ_CHECK_NULL_PTR_RE_FAIL(pBitCoef);

    pACM_PSCoef->ps16Luma = &(pstTab_Y->LUT0[0]);
    pACM_PSCoef->ps16Sat  = &(pstTab_S->LUT0[0]);
    pACM_PSCoef->ps16Hue  = &(pstTab_H->LUT0[0]);

    for (i = 0; i < 45; i++) /* 180/4 */
    {
        pBitCoef->stBit[i].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++); /* repeat luma */
        pBitCoef->stBit[i].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++); /* repeat saturation */
        pBitCoef->stBit[i].bits_35 = s32Tmp;
        pBitCoef->stBit[i].bits_34 = (s32Tmp >> 5); /* handle it as bit move to the right 5 bit */
        pBitCoef->stBit[i].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i].bits_6 = VouBitValue(*pACM_PSCoef->ps16Luma++); /* repeat */
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i].bits_75 = s32Tmp;
        pBitCoef->stBit[i].bits_74 = s32Tmp >> 5;
        pBitCoef->stBit[i].bits_8 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i].bits_9 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i].bits_10 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i].bits_113 = s32Tmp;
        pBitCoef->stBit[i].bits_114 = s32Tmp >> 3;
        pBitCoef->stBit[i].bits_12 = 0; /* apply last 28bit to 0 */
    }
    pACM_PSCoef->ps16Luma = &(pstTab_Y->LUT1[0]);
    pACM_PSCoef->ps16Sat  = &(pstTab_S->LUT1[0]);
    pACM_PSCoef->ps16Hue  = &(pstTab_H->LUT1[0]);

    for (i = 0; i < 30; i++) /* 120/4 */
    {
        pBitCoef->stBit[i + 45].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 45].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 45].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 45].bits_35 = s32Tmp;
        pBitCoef->stBit[i + 45].bits_34 = (s32Tmp >> 5);
        pBitCoef->stBit[i + 45].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 45].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 45].bits_6 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 45].bits_75 = s32Tmp;
        pBitCoef->stBit[i + 45].bits_74 = s32Tmp >> 5;
        pBitCoef->stBit[i + 45].bits_8 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 45].bits_9 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 45].bits_10 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 45].bits_113 = s32Tmp;
        pBitCoef->stBit[i + 45].bits_114 = s32Tmp >> 3;
        pBitCoef->stBit[i + 45].bits_12 = 0;
    }
    pACM_PSCoef->ps16Luma = &(pstTab_Y->LUT2[0]);
    pACM_PSCoef->ps16Sat  = &(pstTab_S->LUT2[0]);
    pACM_PSCoef->ps16Hue  = &(pstTab_H->LUT2[0]);

    for (i = 0; i < 34; i++) /* 135/4=33.75 */
    {
        if (i == 33) /* 0.75 is different from other data */
        {
            pBitCoef->stBit[i + 75].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 75].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 75].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 75].bits_35 = s32Tmp;
            pBitCoef->stBit[i + 75].bits_34 = (s32Tmp >> 5);
            pBitCoef->stBit[i + 75].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 75].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 75].bits_6 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            s32Tmp = 0;
            pBitCoef->stBit[i + 75].bits_75 = s32Tmp;
            pBitCoef->stBit[i + 75].bits_74 = s32Tmp >> 5;
            pBitCoef->stBit[i + 75].bits_8 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 75].bits_9 = 0;
            pBitCoef->stBit[i + 75].bits_10 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            s32Tmp = 0;
            pBitCoef->stBit[i + 75].bits_113 = s32Tmp;
            pBitCoef->stBit[i + 75].bits_114 = s32Tmp >> 3;
        }
        else
        {
            pBitCoef->stBit[i + 75].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 75].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 75].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 75].bits_35 = s32Tmp;
            pBitCoef->stBit[i + 75].bits_34 = (s32Tmp >> 5);
            pBitCoef->stBit[i + 75].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 75].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 75].bits_6 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 75].bits_75 = s32Tmp;
            pBitCoef->stBit[i + 75].bits_74 = s32Tmp >> 5;
            pBitCoef->stBit[i + 75].bits_8 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 75].bits_9 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 75].bits_10 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 75].bits_113 = s32Tmp;
            pBitCoef->stBit[i + 75].bits_114 = s32Tmp >> 3;
        }
        pBitCoef->stBit[i + 75].bits_12 = 0;
    }
    pACM_PSCoef->ps16Luma = &(pstTab_Y->LUT3[0]);
    pACM_PSCoef->ps16Sat  = &(pstTab_S->LUT3[0]);
    pACM_PSCoef->ps16Hue  = &(pstTab_H->LUT3[0]);

    for (i = 0; i < 23; i++) /* 90/4=22.5 */
    {
        if (i == 22)
        {
            pBitCoef->stBit[i + 109].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 109].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 109].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 109].bits_35 = s32Tmp;
            pBitCoef->stBit[i + 109].bits_34 = (s32Tmp >> 5);
            pBitCoef->stBit[i + 109].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 109].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        }
        else
        {
            pBitCoef->stBit[i + 109].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 109].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 109].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 109].bits_35 = s32Tmp;
            pBitCoef->stBit[i + 109].bits_34 = (s32Tmp >> 5);
            pBitCoef->stBit[i + 109].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 109].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 109].bits_6 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 109].bits_75 = s32Tmp;
            pBitCoef->stBit[i + 109].bits_74 = s32Tmp >> 5;
            pBitCoef->stBit[i + 109].bits_8 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 109].bits_9 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 109].bits_10 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 109].bits_113 = s32Tmp;
            pBitCoef->stBit[i + 109].bits_114 = s32Tmp >> 3;
        }
        pBitCoef->stBit[i + 109].bits_12 = 0;
    }
    pACM_PSCoef->ps16Luma = &(pstTab_Y->LUT4[0]);
    pACM_PSCoef->ps16Sat  = &(pstTab_S->LUT4[0]);
    pACM_PSCoef->ps16Hue  = &(pstTab_H->LUT4[0]);
    for (i = 0; i < 42; i++) /* 168/4=42 */
    {
        pBitCoef->stBit[i + 132].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 132].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 132].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 132].bits_35 = s32Tmp;
        pBitCoef->stBit[i + 132].bits_34 = (s32Tmp >> 5);
        pBitCoef->stBit[i + 132].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 132].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 132].bits_6 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 132].bits_75 = s32Tmp;
        pBitCoef->stBit[i + 132].bits_74 = s32Tmp >> 5;
        pBitCoef->stBit[i + 132].bits_8 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 132].bits_9 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 132].bits_10 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 132].bits_113 = s32Tmp;
        pBitCoef->stBit[i + 132].bits_114 = s32Tmp >> 3;
        pBitCoef->stBit[i + 132].bits_12 = 0;
    }
    pACM_PSCoef->ps16Luma = &(pstTab_Y->LUT5[0]);
    pACM_PSCoef->ps16Sat  = &(pstTab_S->LUT5[0]);
    pACM_PSCoef->ps16Hue  = &(pstTab_H->LUT5[0]);
    for (i = 0; i < 28; i++) /* 112/4=28 */
    {
        pBitCoef->stBit[i + 174].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 174].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 174].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 174].bits_35 = s32Tmp;
        pBitCoef->stBit[i + 174].bits_34 = (s32Tmp >> 5);
        pBitCoef->stBit[i + 174].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 174].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 174].bits_6 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 174].bits_75 = s32Tmp;
        pBitCoef->stBit[i + 174].bits_74 = s32Tmp >> 5;
        pBitCoef->stBit[i + 174].bits_8 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 174].bits_9 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 174].bits_10 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 174].bits_113 = s32Tmp;
        pBitCoef->stBit[i + 174].bits_114 = s32Tmp >> 3;
        pBitCoef->stBit[i + 174].bits_12 = 0;
    }
    pACM_PSCoef->ps16Luma = &(pstTab_Y->LUT6[0]);
    pACM_PSCoef->ps16Sat  = &(pstTab_S->LUT6[0]);
    pACM_PSCoef->ps16Hue  = &(pstTab_H->LUT6[0]);
    for (i = 0; i < 32; i++) /* 126/4=31.5 */
    {
        if (i == 31)
        {
            pBitCoef->stBit[i + 202].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 202].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 202].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 202].bits_35 = s32Tmp;
            pBitCoef->stBit[i + 202].bits_34 = (s32Tmp >> 5);
            pBitCoef->stBit[i + 202].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 202].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        }
        else
        {
            pBitCoef->stBit[i + 202].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 202].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 202].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 202].bits_35 = s32Tmp;
            pBitCoef->stBit[i + 202].bits_34 = (s32Tmp >> 5);
            pBitCoef->stBit[i + 202].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 202].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 202].bits_6 = VouBitValue(*pACM_PSCoef->ps16Luma++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Luma++);
            pBitCoef->stBit[i + 202].bits_75 = s32Tmp;
            pBitCoef->stBit[i + 202].bits_74 = s32Tmp >> 5;
            pBitCoef->stBit[i + 202].bits_8 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 202].bits_9 = VouBitValue(*pACM_PSCoef->ps16Sat++);
            pBitCoef->stBit[i + 202].bits_10 = VouBitValue(*pACM_PSCoef->ps16Hue++);
            s32Tmp = VouBitValue(*pACM_PSCoef->ps16Hue++);
            pBitCoef->stBit[i + 202].bits_113 = s32Tmp;
            pBitCoef->stBit[i + 202].bits_114 = s32Tmp >> 3;
        }
        pBitCoef->stBit[i + 202].bits_12 = 0;
    }
    pACM_PSCoef->ps16Luma = &(pstTab_Y->LUT7[0]);
    pACM_PSCoef->ps16Sat  = &(pstTab_S->LUT7[0]);
    pACM_PSCoef->ps16Hue  = &(pstTab_H->LUT7[0]);
    for (i = 0; i < 21; i++) /* 84/4=21 */
    {
        pBitCoef->stBit[i + 234].bits_0 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 234].bits_1 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 234].bits_2 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 234].bits_35 = s32Tmp;
        pBitCoef->stBit[i + 234].bits_34 = (s32Tmp >> 5);
        pBitCoef->stBit[i + 234].bits_4 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 234].bits_5 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 234].bits_6 = VouBitValue(*pACM_PSCoef->ps16Luma++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Luma++);
        pBitCoef->stBit[i + 234].bits_75 = s32Tmp;
        pBitCoef->stBit[i + 234].bits_74 = s32Tmp >> 5;
        pBitCoef->stBit[i + 234].bits_8 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 234].bits_9 = VouBitValue(*pACM_PSCoef->ps16Sat++);
        pBitCoef->stBit[i + 234].bits_10 = VouBitValue(*pACM_PSCoef->ps16Hue++);
        s32Tmp = VouBitValue(*pACM_PSCoef->ps16Hue++);
        pBitCoef->stBit[i + 234].bits_113 = s32Tmp;
        pBitCoef->stBit[i + 234].bits_114 = s32Tmp >> 3;
        pBitCoef->stBit[i + 234].bits_12 = 0;
    }
    pBitCoef->u32Size = COEFACMCNT * sizeof(ACM_COEF_BIT_S); /* 所有的数加起来刚好是255 */

    return HI_SUCCESS;
}

/* 设置ACM参数 */
HI_S32 PQ_HAL_SetACMParam(COLOR_ACM_LUT_S *pstColorData)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstColorData);

    PQ_SAFE_MEMCPY(sg_pstHalAcmLut->as16Luma, pstColorData->as16Luma, sizeof(COLOR_LUT_S));
    PQ_SAFE_MEMCPY(sg_pstHalAcmLut->as16Hue, pstColorData->as16Hue, sizeof(COLOR_LUT_S));
    PQ_SAFE_MEMCPY(sg_pstHalAcmLut->as16Sat, pstColorData->as16Sat, sizeof(COLOR_LUT_S));
    /* Debug Start: For Print ACM LUT CURVE */
    /* Debug End: For Print ACM LUT CURVE */
    /* split table */
    PQ_HAL_Split_Table(pstColorData->as16Luma, sg_pstSplitTable_Y);
    PQ_HAL_Split_Table(pstColorData->as16Hue,  sg_pstSplitTable_H);
    PQ_HAL_Split_Table(pstColorData->as16Sat,  sg_pstSplitTable_S);
    /* convert */
    PQ_HAL_AcmCoefConvert(sg_pstSplitTable_Y, sg_pstSplitTable_S, sg_pstSplitTable_H, sg_pstAcmBitArray);

    PQ_SAFE_MEMCPY(sg_stHalAcmBuffer.pu8StartVirAddr, sg_pstAcmBitArray->stBit, sg_pstAcmBitArray->u32Size);

    PQ_HAL_SetACMAddr(VDP_LAYER_VP0, sg_stHalAcmBuffer.u32StartPhyAddr);
    PQ_HAL_UpdatACMCoef(VDP_LAYER_VP0);

    return HI_SUCCESS;
}

/* Set ACM Enable */
HI_VOID PQ_HAL_EnableACM(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_ACM_CTRL.bits.acm_en = bOnOff;
    PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET), VP0_ACM_CTRL.u32);

    sg_bHalAcmEn = bOnOff;

    return;
}

/* 获取ACM开关标志 */
HI_S32 PQ_HAL_GetACMEnableFlag(HI_BOOL *bOnOff)
{
    *bOnOff = sg_bHalAcmEn;

    return HI_SUCCESS;
}

/* 卖场模式选择 */
HI_VOID PQ_HAL_SetACMDemoMode(PQ_HAL_LAYER_VP_E u32ChId, ACM_DEMO_MODE_E enMode)
{
    return;
}

/* 开关卖场模式 */
HI_VOID PQ_HAL_EnableACMDemo(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_ACM_CTRL.bits.acm_dbg_en = bOnOff;
    PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET), VP0_ACM_CTRL.u32);

    return;
}

HI_VOID PQ_HAL_SetACMCbcrThd(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Data)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_ACM_CTRL.bits.acm_cbcrthr = u32Data;
    PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET), VP0_ACM_CTRL.u32);

    return;
}

HI_VOID PQ_HAL_SetACMStretch(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Data)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_ACM_CTRL.bits.acm_stretch = u32Data;
    PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET), VP0_ACM_CTRL.u32);

    return;
}

HI_VOID PQ_HAL_SetACMClipRange(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Data)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_ACM_CTRL.bits.acm_cliprange = u32Data;
    PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET), VP0_ACM_CTRL.u32);

    return;
}

HI_VOID PQ_HAL_SetACMGain(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Luma, HI_U32 u32Hue, HI_U32 u32Sat)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_ADJ  VP0_ACM_ADJ;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_ADJ.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_ACM_ADJ.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_ACM_ADJ.bits.acm_gain0 = u32Luma;
    VP0_ACM_ADJ.bits.acm_gain1 = u32Hue;
    VP0_ACM_ADJ.bits.acm_gain2 = u32Sat;
    PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_ACM_ADJ.u32) + u32ChId * VDP_VP_OFFSET), VP0_ACM_ADJ.u32);

    return;
}

HI_VOID PQ_HAL_GetACMGain(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 *pu32Luma, HI_U32 *pu32Hue, HI_U32 *pu32Sat)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_ADJ  VP0_ACM_ADJ;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_ADJ.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_ACM_ADJ.u32) + u32ChId * VDP_VP_OFFSET);
    *pu32Luma = VP0_ACM_ADJ.bits.acm_gain0;
    *pu32Hue  = VP0_ACM_ADJ.bits.acm_gain1;
    *pu32Sat  = VP0_ACM_ADJ.bits.acm_gain2;

    return;
}

HI_VOID PQ_HAL_UpdatACMCoef(PQ_HAL_LAYER_VP_E u32ChId)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_PARAUP   VP0_PARAUP;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_PARAUP.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_PARAUP.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_PARAUP.bits.vp0_acmcoef_upd = 1;
    PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_PARAUP.u32) + u32ChId * VDP_VP_OFFSET), VP0_PARAUP.u32);

    return;
}

HI_S32 PQ_HAL_GetACMLumaTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(pstColorData, sg_pstHalAcmLut->as16Luma, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetACMHueTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(pstColorData, sg_pstHalAcmLut->as16Hue, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetACMSatTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(pstColorData, sg_pstHalAcmLut->as16Sat, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetACMLumaTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(sg_pstHalAcmLut->as16Luma, pstColorData, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetACMHueTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(sg_pstHalAcmLut->as16Hue, pstColorData, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetACMSatTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(sg_pstHalAcmLut->as16Sat, pstColorData, sizeof(COLOR_LUT_S));
    return PQ_HAL_SetACMParam(sg_pstHalAcmLut);
}

HI_VOID PQ_HAL_SetACMDemoPos(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Pos)
{
    return;
}

HI_VOID PQ_HAL_GetACMDemoPos(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 *u32Pos)
{
    return;
}

#if 0
/* 获取ACM参数 */
static HI_S32 PQ_HAL_GetACMParam(COLOR_ACM_LUT_S *pstColorTable)
{
    if (HI_NULL == sg_pstHalAcmLut)
    {
        HI_ERR_PQ("sg_pstHalAcmLut is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(pstColorTable, sg_pstHalAcmLut, sizeof(COLOR_ACM_LUT_S));

    return HI_SUCCESS;
}

static HI_VOID PQ_HAL_SetACMCliporWrap(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Data)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_ACM_CTRL.bits.acm_cliporwrap = u32Data;
    PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_ACM_CTRL.u32) + u32ChId * VDP_VP_OFFSET), VP0_ACM_CTRL.u32);

    return;
}
#endif


