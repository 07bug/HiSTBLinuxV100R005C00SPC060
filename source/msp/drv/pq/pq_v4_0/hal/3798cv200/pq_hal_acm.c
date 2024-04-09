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

#define ACM_BUFFER    sizeof(ACM_CONVERT_TABLE) /* Mmz Buffer Size */
#define ACM_LUT_SIZE  sizeof(COLOR_ACM_LUT_S)   /* Lut Size */

static HI_BOOL sg_bHalAcmInitEn = HI_FALSE;
static HI_BOOL sg_bACMEn = HI_FALSE;
static COLOR_ACM_LUT_S *sg_pstAcmLut = HI_NULL;
static PQ_MMZ_BUF_S     sg_stACMBuffer;

/* DeInit ACM */
HI_S32 PQ_HAL_DeInitACM(HI_VOID)
{
    if (HI_FALSE == sg_bHalAcmInitEn)
    {
        return HI_SUCCESS;
    }

    PQ_KFREE_SAFE(sg_pstAcmLut);

    if (HI_NULL != sg_stACMBuffer.pu8StartVirAddr)
    {
        PQ_HAL_MMZ_UnmapAndRelease(&sg_stACMBuffer);
        sg_stACMBuffer.pu8StartVirAddr = HI_NULL;
    }

    sg_bHalAcmInitEn = HI_FALSE;

    return HI_SUCCESS;
}

/* Init ACM */
HI_S32 PQ_HAL_InitACM(HI_VOID)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (HI_TRUE == sg_bHalAcmInitEn)
    {
        return HI_SUCCESS;
    }

    /* MMZ buffer */
    PQ_SAFE_MEMSET(&sg_stACMBuffer, 0, sizeof(PQ_MMZ_BUF_S));

    s32Ret = PQ_HAL_MMZ_AllocAndMap("PQ_ACM", HI_NULL, ACM_BUFFER, 0, &sg_stACMBuffer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ_ACM memory allocated failed!\n");
        sg_bHalAcmInitEn = HI_FALSE;

        return HI_FAILURE;
    }
    PQ_SAFE_MEMSET((HI_U8 *)sg_stACMBuffer.pu8StartVirAddr, 0, ACM_BUFFER);

    /* resource alloc */
    sg_pstAcmLut = (void *)PQ_KMALLOC(ACM_LUT_SIZE, GFP_KERNEL);
    if (HI_NULL == sg_pstAcmLut)
    {
        HI_ERR_PQ("sg_pstAcmLut can not malloc!\n");
        PQ_HAL_MMZ_UnmapAndRelease(&sg_stACMBuffer);
        sg_stACMBuffer.pu8StartVirAddr = HI_NULL;

        sg_bHalAcmInitEn = HI_FALSE;

        return HI_FAILURE;
    }

    PQ_SAFE_MEMSET(sg_pstAcmLut, 0, ACM_LUT_SIZE);

    sg_bACMEn = HI_TRUE;

    sg_bHalAcmInitEn = HI_TRUE;

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
    VP0_ACM_CAD.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CAD.u32)) + u32ChId * PQ_VP_OFFSET));
    VP0_ACM_CAD.bits.coef_addr = u32CoefAddr;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CAD.u32)) + u32ChId * PQ_VP_OFFSET), VP0_ACM_CAD.u32);

    return;
}

static HI_S32 PQ_HAL_Split_Table(HI_S16 ps16OriLUT[9][13][29], ACM_SPLIT_TABLE *pSplitTbl)
{
    HI_S32 *apLUT[8];
    HI_U32 i, j, k;
    HI_U32 u32TblIndex;

    if (HI_NULL == pSplitTbl)
    {
        HI_ERR_PQ("pSplitTbl is NULL pointer!\n");
        return HI_FAILURE;
    }

    apLUT[0] = pSplitTbl->LUT0;
    apLUT[1] = pSplitTbl->LUT1;
    apLUT[2] = pSplitTbl->LUT2;
    apLUT[3] = pSplitTbl->LUT3;
    apLUT[4] = pSplitTbl->LUT4;
    apLUT[5] = pSplitTbl->LUT5;
    apLUT[6] = pSplitTbl->LUT6;
    apLUT[7] = pSplitTbl->LUT7;

    for (k = 0; k < 29; k++)
    {
        for (j = 0; j < 13; j++)
        {
            for (i = 0; i < 9; i++)
            {
                u32TblIndex = (i & 1) + ((j & 1) << 1) + ((k & 1) << 2);
                *apLUT[u32TblIndex] = ps16OriLUT[i][j][k];
                apLUT[u32TblIndex]++;
            }
        }
    }

    return HI_SUCCESS;
}

/* �ı������ݴ洢�Ͷ�ȡ�ķ�ʽ ��ǰ��999977 999977ʣ��28bit��128bit����, ����Ϊ�˽�ʡmemory, ����Ϊ:
   Y:  0~ 8 bit;
   S: 12~20 bit;
   H: 24~30 bit;
   ÿ32bitһ��ѭ��
   */
static HI_VOID Put_H_S_Y_in32Bit(const HI_S32 Hue, const HI_S32 Sat, const HI_S32 Luma, HI_U32 *pu32Bit)
{
    *pu32Bit = ((HI_U32)(Luma & 0x1FF)) + (((HI_U32)(Sat & 0x1FF)) << 12) + (((HI_U32)(Hue & 0x7F)) << 24);
}

static HI_S32 PQ_HAL_AcmCoefConvert(ACM_SPLIT_TABLE *pstTab_Y, ACM_SPLIT_TABLE *pstTab_S,
                                    ACM_SPLIT_TABLE *pstTab_H, ACM_CONVERT_TABLE *pstConverTab)
{
    HI_U32 i   = 0;
    HI_U32 tmp = 0;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstTab_Y);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTab_S);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstTab_H);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstConverTab);

    PQ_SAFE_MEMSET(pstConverTab, 0x00, sizeof(ACM_CONVERT_TABLE));

    for (i = 0; i < 264; ++i)
    {
        Put_H_S_Y_in32Bit(pstTab_H->LUT0[2 * i], pstTab_S->LUT0[2 * i], pstTab_Y->LUT0[2 * i], &tmp);
        pstConverTab->LUT4_LUT0_CONF[i].u32Data[0] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT0[2 * i + 1], pstTab_S->LUT0[2 * i + 1], pstTab_Y->LUT0[2 * i + 1], &tmp);
        pstConverTab->LUT4_LUT0_CONF[i].u32Data[1] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT4[2 * i], pstTab_S->LUT4[2 * i], pstTab_Y->LUT4[2 * i], &tmp);
        pstConverTab->LUT4_LUT0_CONF[i].u32Data[2] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT4[2 * i + 1], pstTab_S->LUT4[2 * i + 1], pstTab_Y->LUT4[2 * i + 1], &tmp);
        pstConverTab->LUT4_LUT0_CONF[i].u32Data[3] = tmp;
    }
    for (i = 0; i < 212; ++i)
    {
        Put_H_S_Y_in32Bit(pstTab_H->LUT1[2 * i], pstTab_S->LUT1[2 * i], pstTab_Y->LUT1[2 * i], &tmp);
        pstConverTab->LUT5_LUT1_CONF[i].u32Data[0] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT1[2 * i + 1], pstTab_S->LUT1[2 * i + 1], pstTab_Y->LUT1[2 * i + 1], &tmp);
        pstConverTab->LUT5_LUT1_CONF[i].u32Data[1] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT5[2 * i], pstTab_S->LUT5[2 * i], pstTab_Y->LUT5[2 * i], &tmp);
        pstConverTab->LUT5_LUT1_CONF[i].u32Data[2] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT5[2 * i + 1], pstTab_S->LUT5[2 * i + 1], pstTab_Y->LUT5[2 * i + 1], &tmp);
        pstConverTab->LUT5_LUT1_CONF[i].u32Data[3] = tmp;
    }
    for (i = 0; i < 228; ++i)
    {
        Put_H_S_Y_in32Bit(pstTab_H->LUT2[2 * i], pstTab_S->LUT2[2 * i], pstTab_Y->LUT2[2 * i], &tmp);
        pstConverTab->LUT6_LUT2_CONF[i].u32Data[0] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT2[2 * i + 1], pstTab_S->LUT2[2 * i + 1], pstTab_Y->LUT2[2 * i + 1], &tmp);
        pstConverTab->LUT6_LUT2_CONF[i].u32Data[1] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT6[2 * i], pstTab_S->LUT6[2 * i], pstTab_Y->LUT6[2 * i], &tmp);
        pstConverTab->LUT6_LUT2_CONF[i].u32Data[2] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT6[2 * i + 1], pstTab_S->LUT6[2 * i + 1], pstTab_Y->LUT6[2 * i + 1], &tmp);
        pstConverTab->LUT6_LUT2_CONF[i].u32Data[3] = tmp;
    }
    for (i = 0; i < 180; ++i)
    {
        Put_H_S_Y_in32Bit(pstTab_H->LUT3[2 * i], pstTab_S->LUT3[2 * i], pstTab_Y->LUT3[2 * i], &tmp);
        pstConverTab->LUT7_LUT3_CONF[i].u32Data[0] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT3[2 * i + 1], pstTab_S->LUT3[2 * i + 1], pstTab_Y->LUT3[2 * i + 1], &tmp);
        pstConverTab->LUT7_LUT3_CONF[i].u32Data[1] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT7[2 * i], pstTab_S->LUT7[2 * i], pstTab_Y->LUT7[2 * i], &tmp);
        pstConverTab->LUT7_LUT3_CONF[i].u32Data[2] = tmp;
        Put_H_S_Y_in32Bit(pstTab_H->LUT7[2 * i + 1], pstTab_S->LUT7[2 * i + 1], pstTab_Y->LUT7[2 * i + 1], &tmp);
        pstConverTab->LUT7_LUT3_CONF[i].u32Data[3] = tmp;
    }

    return HI_SUCCESS;
}


/* ����ACM���� */
HI_S32 PQ_HAL_SetACMParam(COLOR_ACM_LUT_S *pstColorData)
{
    ACM_SPLIT_TABLE   *pstSplitTable_Y = HI_NULL;
    ACM_SPLIT_TABLE   *pstSplitTable_H = HI_NULL;
    ACM_SPLIT_TABLE   *pstSplitTable_S = HI_NULL;
    ACM_CONVERT_TABLE *pstConvertTable = HI_NULL;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstColorData);

    pstConvertTable = (void *)PQ_KMALLOC(sizeof(ACM_CONVERT_TABLE), GFP_ATOMIC);
    if (HI_NULL == pstConvertTable)
    {
        HI_ERR_PQ("pstConvertTable is invaild!\n");
        return HI_FAILURE;
    }

    pstSplitTable_Y = (void *)PQ_KMALLOC(sizeof(ACM_SPLIT_TABLE), GFP_ATOMIC);
    pstSplitTable_H = (void *)PQ_KMALLOC(sizeof(ACM_SPLIT_TABLE), GFP_ATOMIC);
    pstSplitTable_S = (void *)PQ_KMALLOC(sizeof(ACM_SPLIT_TABLE), GFP_ATOMIC);

    if (!(pstSplitTable_Y && pstSplitTable_H && pstSplitTable_S))
    {
        PQ_KFREE_SAFE(pstSplitTable_Y);
        PQ_KFREE_SAFE(pstSplitTable_H);
        PQ_KFREE_SAFE(pstSplitTable_S);

        PQ_KFREE_SAFE(pstConvertTable);

        HI_ERR_PQ("SplitTable is invaild!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(sg_pstAcmLut->as16Luma, pstColorData->as16Luma, sizeof(COLOR_LUT_S));
    PQ_SAFE_MEMCPY(sg_pstAcmLut->as16Hue, pstColorData->as16Hue, sizeof(COLOR_LUT_S));
    PQ_SAFE_MEMCPY(sg_pstAcmLut->as16Sat, pstColorData->as16Sat, sizeof(COLOR_LUT_S));
    /* Debug Start: For Print ACM LUT CURVE */
    /* Debug End: For Print ACM LUT CURVE */

    PQ_SAFE_MEMSET(pstConvertTable, 0x0, sizeof(ACM_CONVERT_TABLE));
    PQ_SAFE_MEMSET(pstSplitTable_Y, 0x0, sizeof(ACM_SPLIT_TABLE));
    PQ_SAFE_MEMSET(pstSplitTable_H, 0x0, sizeof(ACM_SPLIT_TABLE));
    PQ_SAFE_MEMSET(pstSplitTable_S, 0x0, sizeof(ACM_SPLIT_TABLE));
    /* split table */
    PQ_HAL_Split_Table(pstColorData->as16Luma, pstSplitTable_Y);
    PQ_HAL_Split_Table(pstColorData->as16Sat, pstSplitTable_S);
    PQ_HAL_Split_Table(pstColorData->as16Hue, pstSplitTable_H);
    /* convert */
    PQ_HAL_AcmCoefConvert(pstSplitTable_Y, pstSplitTable_S, pstSplitTable_H, pstConvertTable);

    PQ_SAFE_MEMCPY(sg_stACMBuffer.pu8StartVirAddr, pstConvertTable, sizeof(ACM_CONVERT_TABLE));

    PQ_HAL_SetACMAddr(VDP_LAYER_VP0, sg_stACMBuffer.u32StartPhyAddr);
    PQ_HAL_UpdatACMCoef(VDP_LAYER_VP0);

    PQ_KFREE_SAFE(pstConvertTable);
    PQ_KFREE_SAFE(pstSplitTable_Y);
    PQ_KFREE_SAFE(pstSplitTable_H);
    PQ_KFREE_SAFE(pstSplitTable_S);

    return HI_SUCCESS;
}

/* Set ACM Enable */
HI_VOID PQ_HAL_SetACMEn(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET));
    VP0_ACM_CTRL.bits.acm_en = bOnOff;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET), VP0_ACM_CTRL.u32);

    sg_bACMEn = bOnOff;

    return;
}

/* ��ȡACM���ر�־ */
HI_S32 PQ_HAL_GetACMEn(HI_BOOL *bOnOff)
{
    *bOnOff = sg_bACMEn;

    return HI_SUCCESS;
}

/* ����ģʽѡ�� */
HI_VOID PQ_HAL_SetACMDemoMode(PQ_HAL_LAYER_VP_E u32ChId, ACM_DEMO_MODE_E enMode)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET));
    VP0_ACM_CTRL.bits.acm_dbg_mode = enMode;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET), VP0_ACM_CTRL.u32);

    return;
}

/* Enable Acm Demo */
HI_VOID PQ_HAL_SetACMDemoEn(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff)
{
    S_VDP_REGS_TYPE *pstVDPReg = HI_NULL;
    U_VP0_ACM_CTRL  VP0_ACM_CTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("Error,Select Wrong CHANNEL ID\n");
        return;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET));
    VP0_ACM_CTRL.bits.acm_dbg_en = bOnOff;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET), VP0_ACM_CTRL.u32);

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
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET));
    VP0_ACM_CTRL.bits.acm_cbcrthr = u32Data;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET), VP0_ACM_CTRL.u32);

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
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET));
    VP0_ACM_CTRL.bits.acm_stretch = u32Data;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET), VP0_ACM_CTRL.u32);

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
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET));
    VP0_ACM_CTRL.bits.acm_cliprange = u32Data;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET), VP0_ACM_CTRL.u32);

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
    VP0_ACM_ADJ.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_ADJ.u32)) + u32ChId * PQ_VP_OFFSET));
    VP0_ACM_ADJ.bits.acm_gain0 = u32Luma;
    VP0_ACM_ADJ.bits.acm_gain1 = u32Hue;
    VP0_ACM_ADJ.bits.acm_gain2 = u32Sat;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_ADJ.u32)) + u32ChId * PQ_VP_OFFSET), VP0_ACM_ADJ.u32);

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
    VP0_ACM_ADJ.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_ACM_ADJ.u32)) + u32ChId * PQ_VP_OFFSET));
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
    VP0_PARAUP.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_PARAUP.u32)) + u32ChId * PQ_VP_OFFSET));
    VP0_PARAUP.bits.vp0_acmcoef_upd = 1;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVDPReg->VP0_PARAUP.u32)) + u32ChId * PQ_VP_OFFSET), VP0_PARAUP.u32);

    return;
}

HI_S32 PQ_HAL_GetACMLumaTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(pstColorData, sg_pstAcmLut->as16Luma, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetACMHueTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(pstColorData, sg_pstAcmLut->as16Hue, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetACMSatTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(pstColorData, sg_pstAcmLut->as16Sat, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetACMLumaTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(sg_pstAcmLut->as16Luma, pstColorData, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetACMHueTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(sg_pstAcmLut->as16Hue, pstColorData, sizeof(COLOR_LUT_S));
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetACMSatTbl(COLOR_LUT_S *pstColorData)
{
    if (HI_NULL == pstColorData)
    {
        HI_ERR_PQ("pstColorData is NULL!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(sg_pstAcmLut->as16Sat, pstColorData, sizeof(COLOR_LUT_S));
    return PQ_HAL_SetACMParam(sg_pstAcmLut);
}

HI_S32 PQ_HAL_GetACMDemoPos(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 *pu32XPos)
{
    S_VDP_REGS_TYPE *pstVdpReg = NULL;
    U_VP0_ACM_CTRL   VP0_ACM_CTRL;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32XPos);

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("select wrong VP layer id\n");
        return HI_FAILURE;
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVdpReg->VP0_ACM_CTRL.u32)) + u32ChId * PQ_VP_OFFSET));
    *pu32XPos = VP0_ACM_CTRL.bits.acm_dbg_pos;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetACMDemoPos(PQ_HAL_LAYER_VID_E u32VId, HI_U32 u32XPos)
{
    S_VDP_REGS_TYPE *pstVdpReg = NULL;
    U_VP0_ACM_CTRL   VP0_ACM_CTRL;

    if (u32VId >= VID_MAX)
    {
        HI_ERR_PQ("select wrong V layer id\n");
        return HI_FAILURE;
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_ACM_CTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pstVdpReg->VP0_ACM_CTRL.u32)) + u32VId * PQ_VID_OFFSET));
    VP0_ACM_CTRL.bits.acm_dbg_pos = u32XPos;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pstVdpReg->VP0_ACM_CTRL.u32)) + u32VId * PQ_VID_OFFSET), VP0_ACM_CTRL.u32);

    return HI_SUCCESS;
}



