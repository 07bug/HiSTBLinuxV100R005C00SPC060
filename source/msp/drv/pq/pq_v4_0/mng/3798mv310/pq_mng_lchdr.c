/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name    : pq_mng_lchdr.c
  Version       : Initial Draft
  Author        : sdk
  Created      : 2018/01/12
  Description  :

******************************************************************************/
#include <linux/string.h>

#include "pq_mng_lchdr.h"
#include "pq_hal_comm.h"
#include "pq_hal_lchdr.h"
#include "drv_pq_table.h"

static ALG_LCHDR_S sg_stPQLCHDRInfo;

HI_S32 PQ_MNG_InitLCHDR(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault)
{
    /*HI_S32 s32Ret = HI_SUCCESS;*/
    /*HI_U32 u32HandleNo = 0;*/
    if (HI_TRUE == sg_stPQLCHDRInfo.bInit)
    {
        return HI_SUCCESS;
    }

    PQ_CHECK_NULL_PTR_RE_FAIL(pstPqParam);

    /*s32Ret = PQ_TABLE_InitPhyList(u32HandleNo, HI_PQ_MODULE_LCHDR, PQ_SOURCE_MODE_NO, PQ_OUTPUT_MODE_NO);
    if (HI_SUCCESS != s32Ret)
    {
        sg_stPQLCHDRInfo.bInit = HI_FALSE;
        return s32Ret;
    }*/

    /* LCHDR en control by vpss */
    sg_stPQLCHDRInfo.bEnable     = HI_FALSE;
    sg_stPQLCHDRInfo.bDemoEnable = HI_FALSE;
    sg_stPQLCHDRInfo.eDemoMode   = PQ_DEMO_ENABLE_L;
    sg_stPQLCHDRInfo.bInit       = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_DeInitLCHDR(HI_VOID)
{
    if (HI_FALSE == sg_stPQLCHDRInfo.bInit)
    {
        return HI_SUCCESS;
    }

    sg_stPQLCHDRInfo.bInit   = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCHDRCfg(HI_PQ_VPSS_ZME_LAYER_E enLayerId, S_CAS_REGS_TYPE *pstReg, HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_NULL_PTR_RE_FAIL(pstReg);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstXdrFrameInfo);

    s32Ret = PQ_HAL_GetLCHDRCfg(enLayerId, pstReg, pstXdrFrameInfo);

    return s32Ret;
}

HI_S32 PQ_MNG_SetLCHDREn(HI_BOOL bOnOff)
{
    HI_U32 u32HandleNo;
    PQ_SOURCE_MODE_E enSourceMode = PQ_COMM_GetSourceMode();

    if ((enSourceMode > PQ_SOURCE_MODE_UHD)
        || (HI_FALSE == PQ_COMM_GetMoudleCtrl(HI_PQ_MODULE_LCHDR, enSourceMode)))
    {
        bOnOff = HI_FALSE;
    }

    sg_stPQLCHDRInfo.bEnable = bOnOff;

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_SUCCESS == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            PQ_HAL_SetLCHDREn(u32HandleNo, bOnOff);
        }
    }

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCHDREn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbOnOff);

    PQ_HAL_GetLCHDREn(pbOnOff);

    //*pbOnOff = sg_stPQLCHDRInfo.bEnable;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_SetLCHDRDemoEn(HI_BOOL bOnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32HandleNo;

    sg_stPQLCHDRInfo.bDemoEnable = bOnOff;

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_SUCCESS == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            s32Ret = PQ_HAL_SetLCHDRDemoEn(u32HandleNo, bOnOff);
        }
    }

    return s32Ret;
}


HI_S32 PQ_MNG_GetLCHDRDemoEn(HI_BOOL *pbOnOff)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pbOnOff);

    *pbOnOff = sg_stPQLCHDRInfo.bDemoEnable;

    return HI_SUCCESS;
}


HI_S32 PQ_MNG_SetLCHDRDemoMode(PQ_DEMO_MODE_E enMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32HandleNo;

    sg_stPQLCHDRInfo.eDemoMode = enMode;

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_SUCCESS == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            s32Ret = PQ_HAL_SetLCHDRDemoMode(u32HandleNo, enMode);
        }
    }

    return s32Ret;
}


HI_S32 PQ_MNG_GetLCHDRDemoMode(PQ_DEMO_MODE_E *penMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(penMode);

    *penMode = sg_stPQLCHDRInfo.eDemoMode;

    return HI_SUCCESS;
}

HI_S32 PQ_MNG_GetLCHDRDemoPos (HI_U32 u32XPos)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32HandleNo;

    for (u32HandleNo = 0; u32HandleNo < VPSS_HANDLE_NUM; u32HandleNo++)
    {
        if (HI_SUCCESS == PQ_HAL_CheckVpssValid(u32HandleNo))
        {
            s32Ret = PQ_HAL_SetLCHDRDemoPos(u32HandleNo, u32XPos);
        }
    }

    return s32Ret;
}

static stPQAlgFuncs stLCHDRFuncs =
{
    .Init                = PQ_MNG_InitLCHDR,
    .DeInit              = PQ_MNG_DeInitLCHDR,
    .SetEnable           = PQ_MNG_SetLCHDREn,
    .GetEnable           = PQ_MNG_GetLCHDREn,
    .SetDemo             = PQ_MNG_SetLCHDRDemoEn,
    .GetDemo             = PQ_MNG_GetLCHDRDemoEn,
    .SetDemoMode         = PQ_MNG_SetLCHDRDemoMode,
    .GetDemoMode         = PQ_MNG_GetLCHDRDemoMode,
    .SetDemoModeCoor     = PQ_MNG_GetLCHDRDemoPos,
    .GetLCHdrCfg         = PQ_MNG_GetLCHDRCfg,
};

HI_S32 PQ_MNG_RegisterLCHDR(PQ_REG_TYPE_E  enType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgRegister(HI_PQ_MODULE_LCHDR, enType, PQ_BIN_ADAPT_SINGLE, "LCHDR", HI_NULL, &stLCHDRFuncs);

    return s32Ret;
}

HI_S32 PQ_MNG_UnRegisterLCHDR(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = PQ_COMM_AlgUnRegister(HI_PQ_MODULE_LCHDR);

    return s32Ret;
}

