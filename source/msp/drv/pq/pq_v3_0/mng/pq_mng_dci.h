/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_mng_dci.h
  Version       : Initial Draft
  Author        :
  Created       : 2013/10/15
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_DCI_H__
#define __PQ_MNG_DCI_H__

#include "hi_type.h"
#include "drv_pq_define.h"
#include "pq_hal_dci.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* DCI�ļ��ṹ */
typedef struct  hiDCI_INFO_HEADER_S
{
    HI_U8             au8MagicNumber[8];
    HI_U16            u16DCITblNum;
    HI_U16            u16DCITblSize;
    HI_U32            u32CRC;

} DCI_INFO_HEADER_S;

typedef struct  hiDCI_TABLE_DATA_S
{
    HI_CHAR    cIndexName[8];
    DCI_WGT_S  stDCITable;

} DCI_TABLE_DATA_S;

typedef struct  hiDCI_INFO
{
    DCI_INFO_HEADER_S stDCIHeader;
    HI_U8            *pstDCIData;

} DCI_INFO_S;

/* DCI �������� */
typedef enum hiDCI_LEVEL_E
{
    DCI_LEVEL_LOW = 0,
    DCI_LEVEL_MID    ,
    DCI_LEVEL_HIGH   ,

    DCI_LEVEL_BUTT
} DCI_LEVEL_E;

/* DCI Global Gain */
typedef enum hiPQ_DCI_GLOBAL_GAIN_E
{
    DCI_GLOBAL_GAIN_0 = 0,
    DCI_GLOBAL_GAIN_1,
    DCI_GLOBAL_GAIN_2,
    DCI_GLOBAL_GAIN_BUTT,
} PQ_DCI_GLOBAL_GAIN_E;

/* DCIͳ�ƴ��� */
typedef struct  hiDCI_WIN_S
{
    HI_U16      u16HStar;
    HI_U16      u16HEnd;
    HI_U16      u16VStar;
    HI_U16      u16VEnd;

} DCI_WIN_S;

/* DCI ����ṹ�� */
typedef struct hiDCI_LEVEL_S
{
    HI_U8 u8Gain0;
    HI_U8 u8Gain1;
    HI_U8 u8Gain2;
} DCI_LEVEL_S;


/* ��ʼ��DCIģ�� */
HI_S32 PQ_MNG_InitDCI(PQ_PARAM_S *pstPqParam, HI_BOOL bDefault);
/* ȥ��ʼ��DCIģ�� */
HI_S32 PQ_MNG_DeinitDCI(HI_VOID);
/* ��ȡDCIģ�鿪��״̬ */
HI_S32 PQ_MNG_GetDCIEnable(HI_U32 *pu32OnOff);
/* ʹ��DCIģ�� */
HI_S32 PQ_MNG_EnableDCI(HI_BOOL bOnOff);
/* ����DCIǿ������ȼ� */
HI_S32 PQ_MNG_SetDCILevelGain(HI_U32 u32DCILevelGain, HI_U32 u32SourceMode);
/* ����DCIǿ������ȼ� */
HI_S32 PQ_MNG_GetDCILevelGain(HI_U32 *pu32DCILevelGain);
/* DCI��������ģʽ */
HI_S32 PQ_MNG_EnableDCIDemo(HI_BOOL bOnOff);
HI_S32 PQ_MNG_SetDCIDemoMode(DCI_DEMO_MODE_E enMode);
HI_S32 PQ_MNG_GetDCIDemoMode(DCI_DEMO_MODE_E *enMode);
/* ����DCIֱ��ͼͳ�ƴ���*/
HI_S32 PQ_MNG_UpdateDCIWin(DCI_WIN_S *pstWin);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
