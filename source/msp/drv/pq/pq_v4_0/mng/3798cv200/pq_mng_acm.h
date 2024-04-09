/******************************************************************************
*
* Copyright (C) 2014 -2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_acm.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2014/4/22
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_ACM_H__
#define __PQ_MNG_ACM_H__

#include "hi_type.h"
#include "drv_pq_define.h"
#include "pq_hal_acm.h"
#include "drv_pq_table.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/* ��ɫ�������� */
typedef enum hiFLESHTONE_LEVEL_E
{
    FLE_GAIN_OFF = 0 ,
    FLE_GAIN_LOW     ,
    FLE_GAIN_MID     ,
    FLE_GAIN_HIGH    ,

    FLE_GAIN_BUTT
} FLESHTONE_LEVEL_E;

/* Color Gain Level */
typedef enum hiCOLOR_GAIN_LEVEL_E
{
    COLOR_GAIN_OFF = 0,
    COLOR_GAIN_LOW    ,
    COLOR_GAIN_MID    ,
    COLOR_GAIN_HIGH   ,

    COLOR_GAIN_BUTT
} COLOR_GAIN_LEVEL_E;

/* PQ Source Mode */
typedef enum hiPQ_ACM_EHANCE_GAIN_E
{
    ACM_EH_GAIN_LUMA = 0,
    ACM_EH_GAIN_HUE     ,
    ACM_EH_GAIN_SAT     ,

    ACM_EH_GAIN_BUTT
} PQ_ACM_EHANCE_GAIN_E;

/* ����ɫƫ��ֵ */
typedef struct hiSIX_BASE_COLOR_OFFSET_S
{
    HI_U32  u32RedOffset;
    HI_U32  u32GreenOffset;
    HI_U32  u32BlueOffset;
    HI_U32  u32CyanOffset;
    HI_U32  u32MagentaOffset;
    HI_U32  u32YellowOffset;

} SIX_BASE_COLOR_OFFSET_S;

/* ��ɫ��ǿ���� */
typedef enum hiCOLOR_SPEC_MODE_E
{
    COLOR_MODE_RECOMMEND = 0  , /* �Ƽ�����ɫ��ǿģʽ   */
    COLOR_MODE_BLUE           , /* �̶�����ɫ��ǿģʽ   */
    COLOR_MODE_GREEN          , /* �̶�����ɫ��ǿģʽ   */
    COLOR_MODE_BG             , /* �̶�������ɫ��ǿģʽ */
    COLOR_MODE_ORIGINAL       , /* ԭʼ��ɫģʽ */

    COLOR_MODE_BUTT
} COLOR_SPEC_MODE_E;

/*ACM ��ǿ����*/
typedef enum hiACM_ENHANCE_E
{
    ACM_ENHANCE_FLESHTONE = 0,    /* ��ɫ��ǿ */
    ACM_ENHANCE_SIX_BASE,         /* ����ɫ��ǿ,�Զ�����ɫ����ǿ */
    ACM_ENHANCE_SPEC_COLOR_MODE,  /* �̶�ģʽ����ɫ��ǿģʽ */
    ACM_ENHANCE_BUTT
} ACM_ENHANCE_E;


/* ACM GAIN ��Ϣ�ṹ */
typedef struct hiCOLOR_GAIN_S
{
    HI_U32 u32GainMode;   /* 0:SD;1:HD;2:UHD */
    HI_U32 u32Gainluma;   /* ��ʾ��Hue������, ��Χ0-1023 */
    HI_U32 u32Gainhue;    /* ��ʾ��Hue������, ��Χ0-1023 */
    HI_U32 u32Gainsat;    /* ��ʾ��Luma������ */

} COLOR_GAIN_S;



HI_S32 PQ_MNG_GetACMLumaTbl(HI_PQ_COLOR_LUT_S *pstColorData);
HI_S32 PQ_MNG_GetACMHueTbl(HI_PQ_COLOR_LUT_S *pstColorData);
HI_S32 PQ_MNG_GetACMSatTbl(HI_PQ_COLOR_LUT_S *pstColorData);
HI_S32 PQ_MNG_SetAcmLuma(HI_PQ_ACM_LUT_S *pstAttr);
HI_S32 PQ_MNG_SetAcmHue(HI_PQ_ACM_LUT_S *pstAttr);
HI_S32 PQ_MNG_SetAcmSat(HI_PQ_ACM_LUT_S *pstAttr);

HI_S32 PQ_MNG_RegisterACM(PQ_REG_TYPE_E  enType);

HI_S32 PQ_MNG_UnRegisterACM(HI_VOID);






#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
