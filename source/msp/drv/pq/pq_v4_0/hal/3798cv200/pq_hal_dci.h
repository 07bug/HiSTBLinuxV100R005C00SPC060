/******************************************************************************
  *
  * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
  *
  * This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
  *  and may not be copied, reproduced, modified, disclosed to others, published or used, in
  * whole or in part, without the express prior written permission of Hisilicon.
  *
******************************************************************************
  File Name     : pq_hal_dci.h
  Version       : Initial Draft
  Author        :
  Created       : 2013/04/20
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_DCI_H__
#define __PQ_HAL_DCI_H__

#include "hi_type.h"
#include "pq_hal_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define DCI_GAIN_ADDR      0xf8cc612c
#define DCI_GAIN0_LSB      26
#define DCI_GAIN0_MSB      31
#define DCI_GAIN1_LSB      20
#define DCI_GAIN1_MSB      25
#define DCI_GAIN2_LSB      14
#define DCI_GAIN2_MSB      19


/*DCI LUT��ṹ*/
typedef struct hiDCI_LUT_S
{
    HI_S16 s16HistCoef0[32];  /* ֱ��ͼ��Ȩϵ��0 */
    HI_S16 s16HistCoef1[32];  /* ֱ��ͼ��Ȩϵ��1 */
    HI_S16 s16HistCoef2[32];  /* ֱ��ͼ��Ȩϵ��2 */
    HI_S16 s16YDivCoef[64];   /* ������ */
    HI_S16 s16WgtCoef0[33];   /* DCI weight LUT0 */
    HI_S16 s16WgtCoef1[33];   /* DCI weight LUT1 */
    HI_S16 s16WgtCoef2[33];   /* DCI weight LUT2 */
    HI_U32 s32DciCfgReg[28];
} DCI_LUT_S;

/*DCI�������ñ�*/
typedef struct hiDCI_WGT_S
{
    HI_S16 s16WgtCoef0[33];
    HI_S16 s16WgtCoef1[33];
    HI_S16 s16WgtCoef2[33];
    HI_U16 u16Gain0;
    HI_U16 u16Gain1;
    HI_U16 u16Gain2;
} DCI_WGT_S;

/*DCI Black Stretch*/
typedef struct hiDCI_BS_LUT_S
{
    HI_S16 s16BSDelta[320];    /*����������б��Ϊ1�����ߵĶ�Ӧ���ֵ*/
    HI_S16 s16VertOffset[160]; /*����չ���ߴ�ֱƫ��*/
} DCI_BS_LUT_S;


/*DCIֱ��ͼ�ṹ*/
typedef struct hiDCI_HISTGRAM_S
{
    HI_S32 s32HistGram[32];
} DCI_HISTGRAM_S;

/*DCI��������*/
typedef struct hiDCI_WINDOW_S
{
    HI_U16 u16Hstart;
    HI_U16 u16Hend;
    HI_U16 u16Vstart;
    HI_U16 u16Vend;
} DCI_WINDOW_S;

/* DCI Demo Mode */
typedef enum hiDCI_DEMO_MODE_E
{
    DCI_DEMO_ENABLE_R = 0,
    DCI_DEMO_ENABLE_L    ,

    DCI_DEMO_ENABLE_BUTT
} DCI_DEMO_MODE_E;


/* ��ʼ��DCIģ��*/
HI_S32  PQ_HAL_DCIInit(HI_VOID);
/* ȥ��ʼ��DCIģ�� */
HI_S32  PQ_HAL_DCIDeinit(HI_VOID);
/* ��������ģʽ */
HI_VOID PQ_HAL_EnableDCIDemo(PQ_HAL_LAYER_VID_E u32ChId, HI_BOOL bOnOff);
HI_VOID PQ_HAL_SetDCIDemoMode(PQ_HAL_LAYER_VID_E u32ChId, DCI_DEMO_MODE_E enMode);
/* ����DCIģ�� */
HI_VOID PQ_HAL_EnableDCI(PQ_HAL_LAYER_VID_E u32ChId, HI_BOOL bOnOff);
/*����DCI BSģ��*/
HI_VOID PQ_HAL_EnableDciBS(PQ_HAL_LAYER_VID_E u32ChId, HI_BOOL bOnOff);

/* ��ȡDCIǿ�� */
HI_VOID PQ_HAL_GetDCIlevel(PQ_HAL_LAYER_VID_E u32ChId, HI_U16 *pu16Gain0, HI_U16 *pu16Gain1, HI_U16 *pu16Gain2);
/* ����DCIǿ�� */
HI_VOID PQ_HAL_SetDCIlevel(PQ_HAL_LAYER_VID_E u32ChId, HI_U16 u16Gain0, HI_U16 u16Gain1, HI_U16 u16Gain2);
/* ����DCIͳ�ƴ��� */
HI_VOID PQ_HAL_SetDCIWindow(PQ_HAL_LAYER_VID_E u32ChId, HI_U16 u16HStar, HI_U16 u16HEnd, HI_U16 u16VStar, HI_U16 u16VEnd);
/* ��ȡDCI���ô��� */
HI_VOID PQ_HAL_GetDCIWindow(HI_U16 *u16HStar, HI_U16 *u16HEnd, HI_U16 *u16VStar, HI_U16 *u16VEnd);
/* ����DCI�������� */
HI_S32  PQ_HAL_SetDCIWgtLut(DCI_WGT_S *pstDciCoef);
/* ��ȡDCI�������� */
HI_S32  PQ_HAL_GetDCIWgtLut(DCI_WGT_S *pstDciCoef);
/* ����DCI��LUT */
HI_S32  PQ_HAL_SetDciLut(DCI_LUT_S *pstDciLut);
/* ��ȡDCIֱ��ͼ */
HI_S32  PQ_HAL_GetDCIHistgram(DCI_HISTGRAM_S *pstDciHist);

HI_S32  PQ_HAL_SetDciBSLut(DCI_BS_LUT_S *pstDciBSLut);

/* ����DCI BS�������� */
HI_S32  PQ_HAL_SetDciBSCoef(DCI_BS_LUT_S *pstDciCoef);
/* ��ȡDCI BS �������� */
HI_S32  PQ_HAL_GetDciBSCoef(DCI_BS_LUT_S *pstDciCoef);

HI_VOID PQ_HAL_UpdateDCICoef(PQ_HAL_LAYER_VID_E u32ChId);

HI_S32 PQ_HAL_SetDCIDemoPos(PQ_HAL_LAYER_VID_E u32ChId, HI_U32 u32Pos);

HI_S32 PQ_HAL_GetDCIDemoPos(PQ_HAL_LAYER_VID_E u32ChId, HI_U32 *u32Pos);

HI_VOID PQ_HAL_UpdataDCIScd(PQ_HAL_LAYER_VID_E u32ChId, HI_BOOL EnSceneChange);

HI_S32 PQ_HAL_SetDciAlphaBlend(PQ_HAL_LAYER_VID_E u32VId, HI_U32 u32AlphaBlend);

HI_S32 PQ_HAL_SetDciClipLimit(PQ_HAL_LAYER_VID_E u32VId, HI_U32 u32ClipLimitR, HI_U32 u32ClipLimitL);

HI_S32 PQ_HAL_SetDciManAlgBlendEn(PQ_HAL_LAYER_VID_E u32VId, HI_BOOL bEn);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
