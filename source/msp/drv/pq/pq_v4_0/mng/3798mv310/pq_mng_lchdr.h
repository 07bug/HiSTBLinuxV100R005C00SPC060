/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_mng_lchdr.h
  Version       : Initial Draft
  Author        : sdk
  Created      : 2016/03/19
  Description  :

******************************************************************************/


#ifndef __PQ_MNG_LCHDR_H__
#define __PQ_MNG_LCHDR_H__

#include "drv_pq_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct hiALG_LCHDR_S
{
    HI_BOOL     bInit;
    HI_BOOL     bEnable;
    HI_BOOL     bDemoEnable;
    PQ_DEMO_MODE_E eDemoMode;
} ALG_LCHDR_S;

HI_S32 PQ_MNG_RegisterLCHDR(PQ_REG_TYPE_E  enType);

HI_S32 PQ_MNG_UnRegisterLCHDR(HI_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


