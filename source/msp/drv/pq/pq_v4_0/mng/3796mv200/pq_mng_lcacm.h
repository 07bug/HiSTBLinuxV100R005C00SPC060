/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_lcacm.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/07/18
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_LCACM_H__
#define __PQ_MNG_LCACM_H__

#include "drv_pq_table.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct hiALG_LCACM_S
{
    HI_BOOL         bInit;
    HI_BOOL         bEnable;
    HI_U32          u32Strength;
    HI_BOOL         bDemoEnable;
    HI_BOOL         bHdrProcessEn;
    PQ_DEMO_MODE_E   eDemoMode;

    HI_PQ_FLESHTONE_E        enLCACMFleshtone;
    HI_PQ_SIX_BASE_COLOR_S   stLCACMSixbaseColor;
    HI_PQ_COLOR_SPEC_MODE_E  enLCACMColorSpecMode;
} ALG_LCACM_S;

HI_S32 PQ_MNG_RegisterLCACM(PQ_REG_TYPE_E enType);
HI_S32 PQ_MNG_UnRegisterLCACM(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


