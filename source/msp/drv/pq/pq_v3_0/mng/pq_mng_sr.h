/******************************************************************************
 Copyright (C), 2001-2012, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : pq_mng_sr.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2014/01/16
Last Modified :
Description   : PQ MNG��SRģ������ݽṹ�ͽӿں���
Function List :
History       :
******************************************************************************/

#ifndef __PQ_MNG_SR_H__
#define __PQ_MNG_SR_H__

#include "hi_type.h"
#include "pq_hal_sr.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum
{
    SR_DISABLE  = 0, /* ��SR,ֻZME */
    SR_ENABLE_R,     /* �ұ�SR     */
    SR_ENABLE_L,     /* ���SR     */
    SR_ENABLE_A,     /* ȫ��       */

    SR_DEMO_BUTT
} SR_DEMO_E;


/* ��ʼ��SRģ�� */
HI_S32 PQ_MNG_InitSR(HI_VOID);
/* ȥ��ʼ��SRģ�� */
HI_S32 PQ_MNG_DeinitSR(HI_VOID);
/* ����SRģ�� */
HI_S32 PQ_MNG_EnableSR(HI_BOOL bOnOff);
/* ����SRģ�� */
HI_S32 PQ_MNG_GetSREnableFlag(HI_BOOL *bOnOff);
/* ��ȡSRģ��DEMOģʽ */
HI_S32 PQ_MNG_GetSRDemo(HI_U32 *pu32Type);
/* ����SRģ��DEMOģʽ */
HI_S32 PQ_MNG_SetSRDemo(SR_DEMO_E enDemoCtrl);
HI_S32 PQ_MNG_EnableSRDemo(HI_BOOL bOnOff);
/* SRģ���е�Sharpen��ģ����ǿ��ϸ����ǿ */
HI_S32 PQ_MNG_UpdateSRSpMode(HI_U32 u32Width, HI_U32 u32Hight);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


