/******************************************************************************
*
* Copyright (C) 2015 -2016  Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_mcmatnr.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/05/25
  Description   :

******************************************************************************/
#include "hi_math.h"
#include "drv_pq_table.h"
#include "pq_mng_tnr.h"
#include "pq_hal_comm.h"
#include "pq_hal_tnr.h"
#ifdef PQ_ALG_MCNR
#include "pq_mng_mcnr.h"
#endif

static ALG_TNR_S sg_stPQTNRInfo;

static HI_S32 PQ_MNG_SetTNRBlendingAlphaLut(HI_U32 u32HandleNo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_HAL_SetTNRBlendingAlphaLut(u32HandleNo);

    return s32Ret;
}

HI_S32 PQ_MNG_InitTnr(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault)
{
    HI_U32 u32HandleNo = 0;

    if (HI_TRUE == sg_stPQTNRInfo.bInit)
    {
        return HI_SUCCESS;
    }

    sg_stPQTNRInfo.bEnable      = HI_FALSE;
    sg_stPQTNRInfo.u32Strength  = 50;
    sg_stPQTNRInfo.bDemoEnable  = HI_FALSE;
    sg_stPQTNRInfo.eDemoMode    = PQ_DEMO_ENABLE_R;

    PQ_TABLE_InitPhyList(u32HandleNo, HI_PQ_MODULE_TNR, PQ_SOURCE_MODE_SD, PQ_OUTPUT_MODE_NO);

    PQ_MNG_SetTNRBlendingAlphaLut(u32HandleNo);

    PQ_HAL_SetTnrMidStr(u32HandleNo);

    sg_stPQTNRInfo.bInit = HI_TRUE;

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_DeInitTnr(HI_VOID)
{
    if (HI_FALSE == sg_stPQTNRInfo.bInit)
    {
        return HI_SUCCESS;
    }

    sg_stPQTNRInfo.bInit = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetTnrEn(HI_BOOL bOnOff)
{
    HI_U32 u32HandleNo;
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();

    sg_stPQTNRInfo.bEnable = bOnOff;

    if ((enSourceMode < PQ_SOURCE_MODE_BUTT)
        && (HI_FALSE == PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_TNR, enSourceMode)))
    {
        sg_stPQTNRInfo.bEnable = HI_FALSE;
    }

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_SUCCESS == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            PQ_HAL_EnableTNR(u32HandleNo, sg_stPQTNRInfo.bEnable);
        }
    }

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetTnrEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbOnOff);

    *pbOnOff = sg_stPQTNRInfo.bEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetTnrDemoEn(HI_BOOL bOnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32HandleNo;

    sg_stPQTNRInfo.bDemoEnable = bOnOff;

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_SUCCESS == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            s32Ret = PQ_HAL_EnableTNRDemo(u32HandleNo, bOnOff);
        }
    }

    return s32Ret;
}

HI_S32 PQ_MNG_GetTnrDemoEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbOnOff);

    *pbOnOff = sg_stPQTNRInfo.bDemoEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetTnrDemoMode(PQ_DEMO_MODE_E enMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32HandleNo;

    sg_stPQTNRInfo.eDemoMode = enMode;

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_SUCCESS == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            s32Ret = PQ_HAL_SetTNRDemoMode(u32HandleNo, (TNR_DEMO_MODE_E)enMode);
        }
    }

    return s32Ret;
}

HI_S32 PQ_MNG_GetTnrDemoMode(PQ_DEMO_MODE_E *penMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(penMode);

    *penMode = sg_stPQTNRInfo.eDemoMode;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetTnrStrength(HI_U32 u32TnrStr)
{
    HI_U32 u32HandleNo;
    HI_S32 s32Ret = HI_SUCCESS;

    if (u32TnrStr > 100)
    {
        HI_ERR_PQ("the value[%d] of setting NR strength is out of range!\n", u32TnrStr);
        return HI_FAILURE;
    }

    sg_stPQTNRInfo.u32Strength = u32TnrStr;

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_SUCCESS == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            s32Ret = PQ_HAL_SetTnrStr(u32HandleNo, u32TnrStr);
        }
    }

    return s32Ret;
}

HI_S32 PQ_MNG_GetTnrStrength(HI_U32 *pu32TnrStr)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pu32TnrStr);

    *pu32TnrStr = sg_stPQTNRInfo.u32Strength;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetTnrDemoModeCoor (HI_U32 u32XPos)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32HandleNo;

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_SUCCESS == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            s32Ret = PQ_HAL_SetTnrDemoModeCoor(u32HandleNo, u32XPos);
        }
    }

    return s32Ret;
}

static stPQAlgFuncs stTNRFuncs =
{
    .Init               = PQ_MNG_InitTnr,
    .DeInit             = PQ_MNG_DeInitTnr,
    .SetEnable          = PQ_MNG_SetTnrEn,
    .GetEnable          = PQ_MNG_GetTnrEn,
    .SetDemo            = PQ_MNG_SetTnrDemoEn,
    .GetDemo            = PQ_MNG_GetTnrDemoEn,
    .SetDemoMode        = PQ_MNG_SetTnrDemoMode,
    .GetDemoMode        = PQ_MNG_GetTnrDemoMode,
    .SetStrength        = PQ_MNG_SetTnrStrength,
    .GetStrength        = PQ_MNG_GetTnrStrength,
    .SetDemoModeCoor    = PQ_MNG_SetTnrDemoModeCoor,
    .SetTNRBlendingAlphaLut = PQ_MNG_SetTNRBlendingAlphaLut,
#ifdef PQ_ALG_MCNR
    .UpdateMCNRCfg      = PQ_MNG_UpdateMCNRCfg,
    .EnableMCNR         = PQ_MNG_SetMCNREn,
    .GetMCNREnable      = PQ_MNG_GetMCNREn,
#endif
};

HI_S32 PQ_MNG_RegisterTNR(PQ_REG_TYPE_E  enType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_TNR, enType, PQ_BIN_ADAPT_MULTIPLE, "tnr", HI_NULL, &stTNRFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterTNR()
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_TNR);

    return s32Ret;
}

