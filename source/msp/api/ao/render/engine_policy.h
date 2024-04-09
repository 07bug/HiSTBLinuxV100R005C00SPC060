/******************************************************************************

  Copyright (C), 2011-2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : engine_policy.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/08/23
  Description  :
  History       :
  1.Date        : 2017/08/23
    Author      :
    Modification: Created file

*******************************************************************************/
#ifndef  __ENGINE_POLICY_H__
#define  __ENGINE_POLICY_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum
{
    POLICY_NONE = 0,
    POLICY_DEC_M,
    POLICY_DEC_A,
    POLICY_DEC_DUAL,
    POLICY_DROP_M,
    POLICY_DROP_A,
    POLICY_DEC_BUTT,
} ENGINE_POLICY_E;

typedef struct
{
    HI_BOOL  bDecoding;
    HI_BOOL  bPtsInvert;
    HI_BOOL  bDropStream;
    HI_BOOL  bMainPtsInvert;
    HI_BOOL  bAssocPtsInvert;
    HI_BOOL  bAssocWaiting;

    HI_U32   u32CurPts[2];
    HI_U32   u32PrePts[2];
    HI_U32   u32FirstTimeMs[2];
    HI_U32   u32AllEmptyTimeMs;
    ENGINE_POLICY_E enStatus;
    ENGINE_POLICY_E enLastStatus;
} ENGINE_POLICY_S;

ENGINE_POLICY_E Policy_Process(ENGINE_POLICY_S* pstPolicy, HI_U32 u32MSize, HI_U32 u32ASize);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
#endif
