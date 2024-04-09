/******************************************************************************
  *
  * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
  *
  * This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
  *  and may not be copied, reproduced, modified, disclosed to others, published or used, in
  * whole or in part, without the express prior written permission of Hisilicon.
  *
******************************************************************************
  File Name     : pq_hal_dci.c
  Version       : Initial Draft
  Author        :
  Created       : 2013/10/20
  Description   :
  History       :
******************************************************************************/
#include <linux/string.h>
#include <linux/fcntl.h>
#include <linux/fs.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"

#include "pq_hal_comm.h"
#include "pq_hal_dci.h"


#define S7TOS8(x) ((x>63)?(x-128):(x))

/* �����ϵ���Ĵ���: 0xff120400 in 98C; 0xf8cc0400 in 98M
   VDP�����е�ϵ�����ӸüĴ����ж���,ͨ��PARARD��ʹ�ܼĴ������־����ϵ��
   */
#define COEF_DATA   0xf8cc0400
#define DCI_BUFFER  sizeof(HI_U32) * 80 /* Mmz Buffer Size */


/* DCI Lookup Table buffer */
static MMZ_BUFFER_S sg_stDciBuf;
static DCI_LUT_S    sg_stDciLut;
/* DCI Init Flag */
static HI_BOOL sg_bDciInitFlag = HI_FALSE;
static DCI_WINDOW_S sg_stDciWindow = {0};

static HI_VOID PQ_HAL_SetDCICoefAddr(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32CoefAddr)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VP0_DCI_CAD VP0_DCI_CAD;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("select wrong VP layer id\n");
        return;
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_DCI_CAD.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_DCI_CAD.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_DCI_CAD.bits.coef_addr = u32CoefAddr;
    PQ_HAL_RegWrite(((HI_U32) & (pstVdpReg->VP0_DCI_CAD.u32) + u32ChId * VDP_VP_OFFSET), VP0_DCI_CAD.u32);
    return;
}

HI_VOID PQ_HAL_UpdateDCICoef(PQ_HAL_LAYER_VP_E u32ChId)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VP0_PARAUP   VP0_PARAUP;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("select wrong VP layer id\n");
        return;
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_PARAUP.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_PARAUP.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_PARAUP.bits.vp0_acccoef_upd = 1;
    PQ_HAL_RegWrite(((HI_U32) & (pstVdpReg->VP0_PARAUP.u32) + u32ChId * VDP_VP_OFFSET), VP0_PARAUP.u32);
    return;
}

/* ��ʼ��DCIģ�� */
HI_S32 PQ_HAL_DCIInit(HI_VOID)
{
    HI_S32 s32Ret;

    if (HI_TRUE == sg_bDciInitFlag)
    {
        return HI_SUCCESS;
    }

    PQ_SAFE_MEMSET(&sg_stDciBuf, 0, sizeof(MMZ_BUFFER_S));

    s32Ret = HI_DRV_MMZ_AllocAndMap("PQ_DCI", HI_NULL, DCI_BUFFER, 0, &sg_stDciBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("dci memory allocated failed!\n");

        sg_bDciInitFlag = HI_FALSE;

        return HI_FAILURE;
    }

    PQ_SAFE_MEMSET(sg_stDciBuf.pu8StartVirAddr, 0, DCI_BUFFER);

    sg_bDciInitFlag = HI_TRUE;

    return HI_SUCCESS;
}

/* ȥ��ʼ��DCIģ�� */
HI_S32 PQ_HAL_DCIDeinit(HI_VOID)
{
    if (HI_FALSE == sg_bDciInitFlag)
    {
        return HI_SUCCESS;
    }

    if (HI_NULL != sg_stDciBuf.pu8StartVirAddr)
    {
        HI_DRV_MMZ_UnmapAndRelease(&sg_stDciBuf);
        sg_stDciBuf.pu8StartVirAddr = HI_NULL;
    }

    sg_bDciInitFlag = HI_FALSE;
    return HI_SUCCESS;
}

HI_VOID PQ_HAL_SetDCIDemoMode(PQ_HAL_LAYER_VP_E u32ChId, DCI_DEMO_MODE_E enMode)
{
    return;
}

/* ��������ģʽ */
HI_VOID PQ_HAL_EnableDCIDemo(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff)
{
    S_VDP_REGS_TYPE *pstVdpReg = NULL;
    U_VP0_DCICTRL VP0_DCICTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("select wrong VP layer id\n");
        return;
    }

    pstVdpReg = PQ_HAL_GetVdpReg();

    VP0_DCICTRL.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_DCICTRL.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_DCICTRL.bits.dci_dbg_en = bOnOff;
    PQ_HAL_RegWrite(((HI_U32) & (pstVdpReg->VP0_DCICTRL.u32) + u32ChId * VDP_VP_OFFSET), VP0_DCICTRL.u32);

    return;
}

/* ����DCIģ�� */
HI_VOID PQ_HAL_EnableDCI(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff)
{
    S_VDP_REGS_TYPE *pstVdpReg = NULL;
    U_VP0_DCICTRL VP0_DCICTRL;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("select wrong VP layer id\n");
        return;
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_DCICTRL.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_DCICTRL.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_DCICTRL.bits.dci_en = bOnOff  ;
    PQ_HAL_RegWrite(((HI_U32) & (pstVdpReg->VP0_DCICTRL.u32) + u32ChId * VDP_VP_OFFSET), VP0_DCICTRL.u32);

    return;
}

/* ��ȡDCIǿ�� */
HI_VOID PQ_HAL_GetDCIlevel(PQ_HAL_LAYER_VP_E u32ChId, HI_U16 *pu16Gain0, HI_U16 *pu16Gain1, HI_U16 *pu16Gain2)
{
    S_VDP_REGS_TYPE *pstVdpReg = NULL;
    U_VP0_DCIGLBGAIN VP0_DCIGLBGAIN;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("select wrong VP layer id\n");
        return;
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_DCIGLBGAIN.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_DCIGLBGAIN.u32) + u32ChId * VDP_VP_OFFSET);
    *pu16Gain0 = VP0_DCIGLBGAIN.bits.dci_glb_gain0;
    *pu16Gain1 = VP0_DCIGLBGAIN.bits.dci_glb_gain1;
    *pu16Gain2 = VP0_DCIGLBGAIN.bits.dci_glb_gain2;

    return;
}

/* ����DCIǿ�� */
HI_VOID PQ_HAL_SetDCIlevel(PQ_HAL_LAYER_VP_E u32ChId, HI_U16 u16Gain0, HI_U16 u16Gain1, HI_U16 u16Gain2)
{
    S_VDP_REGS_TYPE *pstVdpReg = NULL;
    U_VP0_DCIGLBGAIN VP0_DCIGLBGAIN;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("select wrong VP layer id\n");
        return;
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_DCIGLBGAIN.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_DCIGLBGAIN.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_DCIGLBGAIN.bits.dci_glb_gain0 = u16Gain0;
    VP0_DCIGLBGAIN.bits.dci_glb_gain1 = u16Gain1;
    VP0_DCIGLBGAIN.bits.dci_glb_gain2 = u16Gain2;
    PQ_HAL_RegWrite(((HI_U32) & (pstVdpReg->VP0_DCIGLBGAIN.u32) + u32ChId * VDP_VP_OFFSET), VP0_DCIGLBGAIN.u32);

    return;
}

/* ����DCIͳ�ƴ��� */
HI_VOID PQ_HAL_SetDCIWindow(PQ_HAL_LAYER_VP_E u32ChId, HI_U16 u16HStar, HI_U16 u16HEnd, HI_U16 u16VStar, HI_U16 u16VEnd)
{
    S_VDP_REGS_TYPE *pstVdpReg = NULL;
    U_VP0_DCIHPOS VP0_DCIHPOS;
    U_VP0_DCIVPOS VP0_DCIVPOS;

    if (u32ChId >= VDP_VP_MAX)
    {
        HI_ERR_PQ("select wrong VP layer id\n");
        return;
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_DCIHPOS.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_DCIHPOS.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_DCIHPOS.bits.dci_hstart = u16HStar;
    VP0_DCIHPOS.bits.dci_hend   = u16HEnd;
    PQ_HAL_RegWrite(((HI_U32) & (pstVdpReg->VP0_DCIHPOS.u32) + u32ChId * VDP_VP_OFFSET), VP0_DCIHPOS.u32);

    VP0_DCIVPOS.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_DCIVPOS.u32) + u32ChId * VDP_VP_OFFSET);
    VP0_DCIVPOS.bits.dci_vstart = u16VStar;
    VP0_DCIVPOS.bits.dci_vend   = u16VEnd;
    PQ_HAL_RegWrite(((HI_U32) & (pstVdpReg->VP0_DCIVPOS.u32) + u32ChId * VDP_VP_OFFSET), VP0_DCIVPOS.u32);

    sg_stDciWindow.u16Hstart = u16HStar;
    sg_stDciWindow.u16Hend   = u16HEnd;
    sg_stDciWindow.u16Vstart = u16VStar;
    sg_stDciWindow.u16Vend   = u16VEnd;
    return;
}

/* ��ȡDCI���ô��� */
HI_VOID PQ_HAL_GetDCIWindow(HI_U16 *u16HStar, HI_U16 *u16HEnd, HI_U16 *u16VStar, HI_U16 *u16VEnd)
{
    *u16HStar = sg_stDciWindow.u16Hstart;
    *u16HEnd  = sg_stDciWindow.u16Hend;
    *u16VStar = sg_stDciWindow.u16Vstart;
    *u16VEnd  = sg_stDciWindow.u16Vend;

    return;
}

/* ����DCI�������� */
HI_S32 PQ_HAL_SetDCIWgtLut(DCI_WGT_S *pstDciCoef)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstDciCoef);

    PQ_SAFE_MEMCPY(sg_stDciLut.s16WgtCoef0, pstDciCoef->s16WgtCoef0, sizeof(sg_stDciLut.s16WgtCoef0));
    PQ_SAFE_MEMCPY(sg_stDciLut.s16WgtCoef1, pstDciCoef->s16WgtCoef1, sizeof(sg_stDciLut.s16WgtCoef1));
    PQ_SAFE_MEMCPY(sg_stDciLut.s16WgtCoef2, pstDciCoef->s16WgtCoef2, sizeof(sg_stDciLut.s16WgtCoef2));
    PQ_HAL_SetDCILut(&sg_stDciLut);

    return HI_SUCCESS;
}

/* ��ȡDCI�������� */
HI_S32 PQ_HAL_GetDCIWgtLut(DCI_WGT_S *pstDciCoef)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstDciCoef);

    PQ_SAFE_MEMCPY(pstDciCoef->s16WgtCoef0, sg_stDciLut.s16WgtCoef0, sizeof(pstDciCoef->s16WgtCoef0));
    PQ_SAFE_MEMCPY(pstDciCoef->s16WgtCoef1, sg_stDciLut.s16WgtCoef1, sizeof(pstDciCoef->s16WgtCoef1));
    PQ_SAFE_MEMCPY(pstDciCoef->s16WgtCoef2, sg_stDciLut.s16WgtCoef2, sizeof(pstDciCoef->s16WgtCoef2));
    PQ_HAL_GetDCIlevel(VDP_LAYER_VP0, &pstDciCoef->u16Gain0, &pstDciCoef->u16Gain1, &pstDciCoef->u16Gain2);

    return HI_SUCCESS;
}

/* Convert DCI LUT */
static HI_S32 PQ_HAL_DCILutConvert(DCI_LUT_S *pstDciLut, HI_U32 *pu32ConvertTbl)
{
    HI_S32 i = 0;
    /* �߼��Ĵ洢������: 128=4*32,128bit����,ÿ������ռ5bit; s16HistCoef0��������������,һ��10bit,
       ����ÿ128bit�������ż����,ÿ��ѭ��ʣ��128-5*24=8bit,���8bit��0;
       s16HistCoef0~2 ֱ��ͼ��Ȩϵ��; ��s16HistCoef0����,ÿ��ѭ������8����,����ѭ��4�δ���
       */
    for (i = 0; i < 4; i++)
    {
        /* 128bit���е�32bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 0], 0, &pu32ConvertTbl[i * 4], 0, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 1], 0, &pu32ConvertTbl[i * 4], 5, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef1[i * 8 + 0], 0, &pu32ConvertTbl[i * 4], 10, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef1[i * 8 + 1], 0, &pu32ConvertTbl[i * 4], 15, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef2[i * 8 + 0], 0, &pu32ConvertTbl[i * 4], 20, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef2[i * 8 + 1], 0, &pu32ConvertTbl[i * 4], 25, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 2], 0, &pu32ConvertTbl[i * 4], 30, 2);
        /* 128bit���е�32bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 2], 2, &pu32ConvertTbl[i * 4 + 1], 0, 3);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 3], 0, &pu32ConvertTbl[i * 4 + 1], 3, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef1[i * 8 + 2], 0, &pu32ConvertTbl[i * 4 + 1], 8, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef1[i * 8 + 3], 0, &pu32ConvertTbl[i * 4 + 1], 13, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef2[i * 8 + 2], 0, &pu32ConvertTbl[i * 4 + 1], 18, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef2[i * 8 + 3], 0, &pu32ConvertTbl[i * 4 + 1], 23, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 4], 0, &pu32ConvertTbl[i * 4 + 1], 28, 4);
        /* 128bit���е�32bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 4], 4, &pu32ConvertTbl[i * 4 + 2], 0, 1);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 5], 0, &pu32ConvertTbl[i * 4 + 2], 1, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef1[i * 8 + 4], 0, &pu32ConvertTbl[i * 4 + 2], 6, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef1[i * 8 + 5], 0, &pu32ConvertTbl[i * 4 + 2], 11, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef2[i * 8 + 4], 0, &pu32ConvertTbl[i * 4 + 2], 16, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef2[i * 8 + 5], 0, &pu32ConvertTbl[i * 4 + 2], 21, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 6], 0, &pu32ConvertTbl[i * 4 + 2], 26, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 7], 0, &pu32ConvertTbl[i * 4 + 2], 31, 1);
        /* 128bit���е�24bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef0[i * 8 + 7], 1, &pu32ConvertTbl[i * 4 + 3], 0, 4);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef1[i * 8 + 6], 0, &pu32ConvertTbl[i * 4 + 3], 4, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef1[i * 8 + 7], 0, &pu32ConvertTbl[i * 4 + 3], 9, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef2[i * 8 + 6], 0, &pu32ConvertTbl[i * 4 + 3], 14, 5);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16HistCoef2[i * 8 + 7], 0, &pu32ConvertTbl[i * 4 + 3], 19, 5);
        /* ����32bit��24bit��ʼ��31bit */
        PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[i * 4 + 3], 24, 8);
    }/* ת����֮���Table:3*4+3=15,��������ݴ�16��ʼ */

    /* s16YDivCoef ������
       128=4*32,128bit����,ÿ������ռ12bit,ÿ��ѭ��ʣ��128-12*10=8bit,���8bit��0;
       ��s16YDivCoef����,ÿ�δ�ѭ������10����,����ѭ��6���ټ���4������
       */
    for (i = 0; i < 6; i++)
    {
        /* 128bit���е�32bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 0], 0, &pu32ConvertTbl[16 + i * 4 + 0], 0, 12);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 1], 0, &pu32ConvertTbl[16 + i * 4 + 0], 12, 12);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 2], 0, &pu32ConvertTbl[16 + i * 4 + 0], 24, 8);
        /* 128bit���е�32bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 2], 8, &pu32ConvertTbl[16 + i * 4 + 1], 0, 4);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 3], 0, &pu32ConvertTbl[16 + i * 4 + 1], 4, 12);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 4], 0, &pu32ConvertTbl[16 + i * 4 + 1], 16, 12);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 5], 0, &pu32ConvertTbl[16 + i * 4 + 1], 28, 4);
        /* 128bit���е�32bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 5], 4, &pu32ConvertTbl[16 + i * 4 + 2], 0, 8);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 6], 0, &pu32ConvertTbl[16 + i * 4 + 2], 8, 12);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 7], 0, &pu32ConvertTbl[16 + i * 4 + 2], 20, 12);
        /* 128bit���е�24bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 8], 0, &pu32ConvertTbl[16 + i * 4 + 3], 0, 12);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[i * 10 + 9], 0, &pu32ConvertTbl[16 + i * 4 + 3], 12, 12);
        /* ����32bit��24bit��ʼ��31bit */
        PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[16 + i * 4 + 3], 24, 8);
    }/* ת����֮���Table:16+5*4+3=39,���������40��41�޷�д��ѭ�� */
    PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[60], 0, &pu32ConvertTbl[40], 0, 12);
    PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[61], 0, &pu32ConvertTbl[40], 12, 12);
    PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[62], 0, &pu32ConvertTbl[40], 24, 8);
    PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[62], 8, &pu32ConvertTbl[41], 0, 4);
    PQ_HAL_CopyU32ByBit(pstDciLut->s16YDivCoef[63], 0, &pu32ConvertTbl[41], 4, 12);
    /* �м��41��43��ȫ����Ϊ0 */
    PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[41], 16, 16);
    PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[42], 0, 32);
    PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[43], 0, 32);

    /* s16WgtCoef0~2 DCI weight LUT
       128=4*32,128bit����,ÿ����ռ10bit
       128bit����,����32bit����,��������ݴ�44��ʼ,д�����д��76,ÿ��ѭ��ʣ��128-10*12=8bit,���8bit��0;
       ��s16WgtCoef0����,ÿ��ѭ������4����,����ѭ��8���ټ���1������
       */
    for (i = 0; i < 8; i++)
    {
        /* 128bit���е�32bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef0[i * 4 + 0], 0, &pu32ConvertTbl[44 + i * 4 + 0], 0, 10);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef1[i * 4 + 0], 0, &pu32ConvertTbl[44 + i * 4 + 0], 10, 10);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef2[i * 4 + 0], 0, &pu32ConvertTbl[44 + i * 4 + 0], 20, 10);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef0[i * 4 + 1], 0, &pu32ConvertTbl[44 + i * 4 + 0], 30, 2);
        /* 128bit���е�32bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef0[i * 4 + 1], 2, &pu32ConvertTbl[44 + i * 4 + 1], 0, 8);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef1[i * 4 + 1], 0, &pu32ConvertTbl[44 + i * 4 + 1], 8, 10);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef2[i * 4 + 1], 0, &pu32ConvertTbl[44 + i * 4 + 1], 18, 10);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef0[i * 4 + 2], 0, &pu32ConvertTbl[44 + i * 4 + 1], 28, 4);
        /* 128bit���е�32bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef0[i * 4 + 2], 4, &pu32ConvertTbl[44 + i * 4 + 2], 0, 6);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef1[i * 4 + 2], 0, &pu32ConvertTbl[44 + i * 4 + 2], 6, 10);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef2[i * 4 + 2], 0, &pu32ConvertTbl[44 + i * 4 + 2], 16, 10);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef0[i * 4 + 3], 0, &pu32ConvertTbl[44 + i * 4 + 2], 26, 6);
        /* 128bit���е�24bit */
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef0[i * 4 + 3], 6, &pu32ConvertTbl[44 + i * 4 + 3], 0, 4);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef1[i * 4 + 3], 0, &pu32ConvertTbl[44 + i * 4 + 3], 4, 10);
        PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef2[i * 4 + 3], 0, &pu32ConvertTbl[44 + i * 4 + 3], 14, 10);
        /* ����32bit��24bit��ʼ��31bit */
        PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[44 + i * 4 + 3], 24, 8);
    }
    PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef0[32], 0, &pu32ConvertTbl[76], 0, 10);
    PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef1[32], 0, &pu32ConvertTbl[76], 10, 10);
    PQ_HAL_CopyU32ByBit(pstDciLut->s16WgtCoef2[32], 0, &pu32ConvertTbl[76], 20, 10);
    /* 80�������飬ʣ���ȫ����0 */
    PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[76], 30, 2);
    PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[77], 0, 32);
    PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[78], 0, 32);
    PQ_HAL_CopyU32ByBit(0, 0, &pu32ConvertTbl[79], 0, 32);

    return HI_SUCCESS;
}

/* ����DCI��LUT */
HI_S32 PQ_HAL_SetDCILut(DCI_LUT_S *pstDciLut)
{
    HI_S32 s32Ret;
    HI_U32 au32DCIConvertTbl[80] = { 0 };

    if (pstDciLut == NULL)
    {
        HI_ERR_PQ("pstDciLut is null point!\n");
        return HI_FAILURE;
    }

    PQ_SAFE_MEMCPY(&sg_stDciLut, pstDciLut, sizeof(sg_stDciLut));
    s32Ret = PQ_HAL_DCILutConvert(&sg_stDciLut, au32DCIConvertTbl);

    PQ_SAFE_MEMCPY(sg_stDciBuf.pu8StartVirAddr, au32DCIConvertTbl, sizeof(au32DCIConvertTbl));
    PQ_HAL_SetDCICoefAddr(VDP_LAYER_VP0, sg_stDciBuf.u32StartPhyAddr);

    PQ_HAL_UpdateDCICoef(VDP_LAYER_VP0);
    HI_DEBUG_PQ("update reg DCI LUT!\n");

    return HI_SUCCESS;
}

/* ��ȡDCI�������� */
HI_S32 PQ_HAL_GetDCIHistgram(DCI_HISTGRAM_S *pstDciHist)
{
    S_VDP_REGS_TYPE *pstVdpReg = NULL;
    U_VP0_PARARD VP0_PARARD;
    HI_S32 i;
    HI_U32 u32TempValue = 0;
    HI_U32 u32WinSize   = 0;

    if (pstDciHist == NULL)
    {
        HI_ERR_PQ("pstDciHist is null point!\n");
        return HI_FAILURE;
    }

    /* ֱ��ͼ��ʹ�ܴ� */
    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_PARARD.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_PARARD.u32));
    VP0_PARARD.bits.vp0_dcihbw_rd = 1;
    PQ_HAL_RegWrite(((HI_U32) & (pstVdpReg->VP0_PARARD.u32)), VP0_PARARD.u32);

    u32WinSize = (sg_stDciWindow.u16Hend - sg_stDciWindow.u16Hstart) * (sg_stDciWindow.u16Vend - sg_stDciWindow.u16Vstart);
    if (u32WinSize == 0)
    {
        HI_ERR_PQ("DCI window is wrong settingt!\n");
        return HI_FAILURE;
    }

    for (i = 0; i < 32; i++)
    {
        (HI_VOID)PQ_HAL_ReadRegister(0, COEF_DATA, &u32TempValue);
        pstDciHist->s32HistGram[i] = (u32TempValue * 256) / u32WinSize;
        HI_INFO_PQ("HistGram[%d]=%d\n", i, pstDciHist->s32HistGram[i]);
    }

    /* ֱ��ͼ��ʹ�ܹر� */
    pstVdpReg = PQ_HAL_GetVdpReg();
    VP0_PARARD.u32 = PQ_HAL_RegRead((HI_U32) & (pstVdpReg->VP0_PARARD.u32));
    VP0_PARARD.bits.vp0_dcihbw_rd = 0;
    PQ_HAL_RegWrite(((HI_U32) & (pstVdpReg->VP0_PARARD.u32)), VP0_PARARD.u32);

    return HI_SUCCESS;
}

HI_VOID PQ_HAL_SetDCIDemoPos(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 u32Pos)
{
    return;
}

HI_VOID PQ_HAL_GetDCIDemoPos(PQ_HAL_LAYER_VP_E u32ChId, HI_U32 *u32Pos)
{
    return;
}


