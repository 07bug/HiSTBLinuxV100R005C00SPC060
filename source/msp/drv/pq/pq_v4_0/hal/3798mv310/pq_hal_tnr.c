/******************************************************************************
*
* Copyright (C) 2015-2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

 File Name    : pq_hal_tnr.c
 Version        : Initial Draft
 Author         : sdk
 Created       : 2016/05/25
 Description   :
******************************************************************************/

#include "hi_type.h"
#include "pq_hal_tnr.h"
#include "pq_hal_comm.h"

static HI_S32 sg_s32TMTYMotionGain = 15;
static HI_S32 sg_s32TMTCMotionGain = 15;

const static HI_U8 sg_YBlendingAlphaLut[32] = { 7,  7,  7,  8,  8, 9, 11, 13, 16, 19, 22, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31};
const static HI_U8 sg_CBlendingAlphaLut[32] = { 7,  7,  7,  8,  8, 9, 11, 13, 16, 19, 22, 25, 27, 28, 29, 30, 30, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31};

HI_S32 PQ_HAL_EnableTNR(HI_U32 u32HandleNo, HI_BOOL bTNROnOff)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssReg);

    pstVpssReg->VPSS_TNR_CONTRL.bits.nren  = bTNROnOff;
    pstVpssReg->VPSS_TNR_CONTRL.bits.cnren = bTNROnOff;
    pstVpssReg->VPSS_TNR_CONTRL.bits.ynren = bTNROnOff;

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_EnableTNRDemo(HI_U32 u32HandleNo, HI_BOOL bTNRDemoEn)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssReg);

    pstVpssReg->VPSS_TNR_CONTRL.bits.marketmodeen = bTNRDemoEn;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetTNRDemoMode(HI_U32 u32HandleNo, TNR_DEMO_MODE_E enMode)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssReg);

    pstVpssReg->VPSS_TNR_CONTRL.bits.marketmode = (HI_U32)enMode;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetTnrMidStr(HI_U32 u32HandleNo)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssReg);

    sg_s32TMTYMotionGain = pstVpssReg->VPSS_TNR_MAMC_MAP.bits.ymotiongain;
    sg_s32TMTCMotionGain = pstVpssReg->VPSS_TNR_MAMC_MAP.bits.cmotiongain;

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_SetTnrStr(HI_U32 u32HandleNo, HI_U32 u32TnrStr)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;
    HI_U32 u32YMotionGain = ((100 - u32TnrStr) * sg_s32TMTYMotionGain + 25) / 50;
    HI_U32 u32CMotionGain = ((100 - u32TnrStr) * sg_s32TMTCMotionGain + 25) / 50;

    pstVpssReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssReg);

    if (u32YMotionGain > 31)
    {
        u32YMotionGain = 31;
    }

    if (u32CMotionGain > 31)
    {
        u32CMotionGain = 31;
    }

    pstVpssReg->VPSS_TNR_MAMC_MAP.bits.ymotiongain = u32YMotionGain;
    pstVpssReg->VPSS_TNR_MAMC_MAP.bits.cmotiongain = u32CMotionGain;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetTnrDemoModeCoor(HI_U32 u32HandleNo, HI_U32 u32XPos)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssReg);

    pstVpssReg->VPSS_TNR_CONTRL.bits.marketcoor = u32XPos;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetTNRBlendingAlphaLut(HI_U32 u32HandleNo)
{
    S_CAS_REGS_TYPE *pstVpssReg = HI_NULL;

    pstVpssReg = PQ_HAL_GetVpssReg(u32HandleNo);
    PQ_CHECK_NULL_PTR_RE_FAIL(pstVpssReg);

    pstVpssReg->VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut0    = sg_CBlendingAlphaLut[0];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut1    = sg_CBlendingAlphaLut[1];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut2    = sg_CBlendingAlphaLut[2];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut3    = sg_CBlendingAlphaLut[3];

    pstVpssReg->VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut4    = sg_CBlendingAlphaLut[4];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut5    = sg_CBlendingAlphaLut[5];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut6    = sg_CBlendingAlphaLut[6];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut7    = sg_CBlendingAlphaLut[7];

    pstVpssReg->VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut8    = sg_CBlendingAlphaLut[8];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut9    = sg_CBlendingAlphaLut[9];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut10   = sg_CBlendingAlphaLut[10];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut11   = sg_CBlendingAlphaLut[11];

    pstVpssReg->VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut12   = sg_CBlendingAlphaLut[12];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut13   = sg_CBlendingAlphaLut[13];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut14   = sg_CBlendingAlphaLut[14];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut15   = sg_CBlendingAlphaLut[15];

    pstVpssReg->VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut16   = sg_CBlendingAlphaLut[16];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut17   = sg_CBlendingAlphaLut[17];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut18   = sg_CBlendingAlphaLut[18];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut19   = sg_CBlendingAlphaLut[19];

    pstVpssReg->VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut20   = sg_CBlendingAlphaLut[20];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut21   = sg_CBlendingAlphaLut[21];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut22   = sg_CBlendingAlphaLut[22];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut23   = sg_CBlendingAlphaLut[23];

    pstVpssReg->VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut24   = sg_CBlendingAlphaLut[24];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut25   = sg_CBlendingAlphaLut[25];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut26   = sg_CBlendingAlphaLut[26];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut27   = sg_CBlendingAlphaLut[27];

    pstVpssReg->VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut28   = sg_CBlendingAlphaLut[28];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut29   = sg_CBlendingAlphaLut[29];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut30   = sg_CBlendingAlphaLut[30];
    pstVpssReg->VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut31   = sg_CBlendingAlphaLut[31];

    pstVpssReg->VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut0    = sg_YBlendingAlphaLut[0];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut1    = sg_YBlendingAlphaLut[1];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut2    = sg_YBlendingAlphaLut[2];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut3    = sg_YBlendingAlphaLut[3];

    pstVpssReg->VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut4    = sg_YBlendingAlphaLut[4];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut5    = sg_YBlendingAlphaLut[5];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut6    = sg_YBlendingAlphaLut[6];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut7    = sg_YBlendingAlphaLut[7];

    pstVpssReg->VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut8    = sg_YBlendingAlphaLut[8];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut9    = sg_YBlendingAlphaLut[9];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut10   = sg_YBlendingAlphaLut[10];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut11   = sg_YBlendingAlphaLut[11];

    pstVpssReg->VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut12   = sg_YBlendingAlphaLut[12];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut13   = sg_YBlendingAlphaLut[13];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut14   = sg_YBlendingAlphaLut[14];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut15   = sg_YBlendingAlphaLut[15];

    pstVpssReg->VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut16   = sg_YBlendingAlphaLut[16];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut17   = sg_YBlendingAlphaLut[17];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut18   = sg_YBlendingAlphaLut[18];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut19   = sg_YBlendingAlphaLut[19];

    pstVpssReg->VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut20   = sg_YBlendingAlphaLut[20];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut21   = sg_YBlendingAlphaLut[21];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut22   = sg_YBlendingAlphaLut[22];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut23   = sg_YBlendingAlphaLut[23];

    pstVpssReg->VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut24   = sg_YBlendingAlphaLut[24];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut25   = sg_YBlendingAlphaLut[25];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut26   = sg_YBlendingAlphaLut[26];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut27   = sg_YBlendingAlphaLut[27];

    pstVpssReg->VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut28   = sg_YBlendingAlphaLut[28];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut29   = sg_YBlendingAlphaLut[29];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut30   = sg_YBlendingAlphaLut[30];
    pstVpssReg->VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut31   = sg_YBlendingAlphaLut[31];

    return HI_SUCCESS;
}


