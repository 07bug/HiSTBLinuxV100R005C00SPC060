/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_gfxcsc.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2015/10/10
  Description   :

******************************************************************************/
#include "pq_hal_comm.h"
#include "pq_hal_gfxcsc.h"

#ifndef HI_BUILD_IN_BOOT
#include <linux/kernel.h>
#include <linux/string.h>
#else
#include "hi_type.h"
#include "uboot.h"
#endif

static S_VDP_REGS_TYPE *pVdpReg;

static HI_VOID PQ_HAL_SetGdmRgb2yuvCoef00(HI_U32 hihdr_r2y_coef00)
{
    U_HIHDR_G_RGB2YUV_COEF0 HIHDR_G_RGB2YUV_COEF0;

    pVdpReg = PQ_HAL_GetVdpReg();
    HIHDR_G_RGB2YUV_COEF0.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF0.u32))));
    HIHDR_G_RGB2YUV_COEF0.bits.hihdr_r2y_coef00 = hihdr_r2y_coef00;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF0.u32))), HIHDR_G_RGB2YUV_COEF0.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvCoef01(HI_U32 hihdr_r2y_coef01)
{
    U_HIHDR_G_RGB2YUV_COEF1 HIHDR_G_RGB2YUV_COEF1;

    pVdpReg = PQ_HAL_GetVdpReg();
    HIHDR_G_RGB2YUV_COEF1.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF1.u32))));
    HIHDR_G_RGB2YUV_COEF1.bits.hihdr_r2y_coef01 = hihdr_r2y_coef01;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF1.u32))), HIHDR_G_RGB2YUV_COEF1.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvCoef02(HI_U32 hihdr_r2y_coef02)
{
    U_HIHDR_G_RGB2YUV_COEF2 HIHDR_G_RGB2YUV_COEF2;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_COEF2.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF2.u32))));
    HIHDR_G_RGB2YUV_COEF2.bits.hihdr_r2y_coef02 = hihdr_r2y_coef02;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF2.u32))), HIHDR_G_RGB2YUV_COEF2.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvCoef10(HI_U32 hihdr_r2y_coef10)
{
    U_HIHDR_G_RGB2YUV_COEF3 HIHDR_G_RGB2YUV_COEF3;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_COEF3.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF3.u32))));
    HIHDR_G_RGB2YUV_COEF3.bits.hihdr_r2y_coef10 = hihdr_r2y_coef10;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF3.u32))), HIHDR_G_RGB2YUV_COEF3.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvCoef11(HI_U32 hihdr_r2y_coef11)
{
    U_HIHDR_G_RGB2YUV_COEF4 HIHDR_G_RGB2YUV_COEF4;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_COEF4.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF4.u32))));
    HIHDR_G_RGB2YUV_COEF4.bits.hihdr_r2y_coef11 = hihdr_r2y_coef11;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF4.u32))), HIHDR_G_RGB2YUV_COEF4.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvCoef12(HI_U32 hihdr_r2y_coef12)
{
    U_HIHDR_G_RGB2YUV_COEF5 HIHDR_G_RGB2YUV_COEF5;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_COEF5.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF5.u32))));
    HIHDR_G_RGB2YUV_COEF5.bits.hihdr_r2y_coef12 = hihdr_r2y_coef12;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF5.u32))), HIHDR_G_RGB2YUV_COEF5.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvCoef20(HI_U32 hihdr_r2y_coef20)
{
    U_HIHDR_G_RGB2YUV_COEF6 HIHDR_G_RGB2YUV_COEF6;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_COEF6.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF6.u32))));
    HIHDR_G_RGB2YUV_COEF6.bits.hihdr_r2y_coef20 = hihdr_r2y_coef20;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF6.u32))), HIHDR_G_RGB2YUV_COEF6.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvCoef21(HI_U32 hihdr_r2y_coef21)
{
    U_HIHDR_G_RGB2YUV_COEF7 HIHDR_G_RGB2YUV_COEF7;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_COEF7.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF7.u32))));
    HIHDR_G_RGB2YUV_COEF7.bits.hihdr_r2y_coef21 = hihdr_r2y_coef21;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF7.u32))), HIHDR_G_RGB2YUV_COEF7.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvCoef22(HI_U32 hihdr_r2y_coef22)
{
    U_HIHDR_G_RGB2YUV_COEF8 HIHDR_G_RGB2YUV_COEF8;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_COEF8.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF8.u32))));
    HIHDR_G_RGB2YUV_COEF8.bits.hihdr_r2y_coef22 = hihdr_r2y_coef22;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_COEF8.u32))), HIHDR_G_RGB2YUV_COEF8.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvDcIn0(HI_U32 hihdr_r2y_idc0)
{
    U_HIHDR_G_RGB2YUV_IDC0 HIHDR_G_RGB2YUV_IDC0;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_IDC0.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_IDC0.u32))));
    HIHDR_G_RGB2YUV_IDC0.bits.hihdr_r2y_idc0 = hihdr_r2y_idc0;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_IDC0.u32))), HIHDR_G_RGB2YUV_IDC0.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvDcIn1(HI_U32 hihdr_r2y_idc1)
{
    U_HIHDR_G_RGB2YUV_IDC1 HIHDR_G_RGB2YUV_IDC1;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_IDC1.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_IDC1.u32))));
    HIHDR_G_RGB2YUV_IDC1.bits.hihdr_r2y_idc1 = hihdr_r2y_idc1;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_IDC1.u32))), HIHDR_G_RGB2YUV_IDC1.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvDcIn2(HI_U32 hihdr_r2y_idc2)
{
    U_HIHDR_G_RGB2YUV_IDC2 HIHDR_G_RGB2YUV_IDC2;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_IDC2.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_IDC2.u32))));
    HIHDR_G_RGB2YUV_IDC2.bits.hihdr_r2y_idc2 = hihdr_r2y_idc2;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_IDC2.u32))), HIHDR_G_RGB2YUV_IDC2.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvDcOut0(HI_U32 hihdr_r2y_odc0)
{
    U_HIHDR_G_RGB2YUV_ODC0 HIHDR_G_RGB2YUV_ODC0;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_ODC0.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_ODC0.u32))));
    HIHDR_G_RGB2YUV_ODC0.bits.hihdr_r2y_odc0 = hihdr_r2y_odc0;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_ODC0.u32))), HIHDR_G_RGB2YUV_ODC0.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvDcOut1(HI_U32 hihdr_r2y_odc1)
{
    U_HIHDR_G_RGB2YUV_ODC1 HIHDR_G_RGB2YUV_ODC1;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_ODC1.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_ODC1.u32))));
    HIHDR_G_RGB2YUV_ODC1.bits.hihdr_r2y_odc1 = hihdr_r2y_odc1;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_ODC1.u32))), HIHDR_G_RGB2YUV_ODC1.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvDcOut2(HI_U32 hihdr_r2y_odc2)
{
    U_HIHDR_G_RGB2YUV_ODC2 HIHDR_G_RGB2YUV_ODC2;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_ODC2.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_ODC2.u32))));
    HIHDR_G_RGB2YUV_ODC2.bits.hihdr_r2y_odc2 = hihdr_r2y_odc2;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_ODC2.u32))), HIHDR_G_RGB2YUV_ODC2.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvS2P(HI_U32 hihdr_r2y_scale2p)
{
    U_HIHDR_G_RGB2YUV_SCALE2P HIHDR_G_RGB2YUV_SCALE2P;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_SCALE2P.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_SCALE2P.u32))));
    HIHDR_G_RGB2YUV_SCALE2P.bits.hihdr_r2y_scale2p = hihdr_r2y_scale2p;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_SCALE2P.u32))), HIHDR_G_RGB2YUV_SCALE2P.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvClipMin(HI_U32 hihdr_r2y_clip_min)
{
    U_HIHDR_G_RGB2YUV_MIN HIHDR_G_RGB2YUV_MIN;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_MIN.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_MIN.u32))));
    HIHDR_G_RGB2YUV_MIN.bits.hihdr_r2y_clip_min = hihdr_r2y_clip_min;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_MIN.u32))), HIHDR_G_RGB2YUV_MIN.u32);

    return ;
}

static HI_VOID PQ_HAL_SetGdmRgb2yuvClipMax(HI_U32 hihdr_r2y_clip_max)
{
    U_HIHDR_G_RGB2YUV_MAX HIHDR_G_RGB2YUV_MAX;
    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_MAX.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_MAX.u32))));
    HIHDR_G_RGB2YUV_MAX.bits.hihdr_r2y_clip_max = hihdr_r2y_clip_max;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_MAX.u32))), HIHDR_G_RGB2YUV_MAX.u32);

    return ;
}

HI_VOID PQ_HAL_SetGdmRgb2yuvEn(HI_U32 hihdr_r2y_en)
{
    U_HIHDR_G_RGB2YUV_CTRL HIHDR_G_RGB2YUV_CTRL;

    pVdpReg = PQ_HAL_GetVdpReg();

    HIHDR_G_RGB2YUV_CTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_CTRL.u32))));
    HIHDR_G_RGB2YUV_CTRL.bits.hihdr_r2y_en = hihdr_r2y_en;
    PQ_HAL_RegWrite((HI_U32 *)((unsigned long)(&(pVdpReg->HIHDR_G_RGB2YUV_CTRL.u32))), HIHDR_G_RGB2YUV_CTRL.u32);

    return ;
}

HI_VOID PQ_HAL_SetGdmRgb2yuvCoef( PQ_GFX_CSC_COEF_S *pstCscCoef)
{
    PQ_HAL_SetGdmRgb2yuvCoef00(pstCscCoef->csc_coef00);
    PQ_HAL_SetGdmRgb2yuvCoef01(pstCscCoef->csc_coef01);
    PQ_HAL_SetGdmRgb2yuvCoef02(pstCscCoef->csc_coef02);

    PQ_HAL_SetGdmRgb2yuvCoef10(pstCscCoef->csc_coef10);
    PQ_HAL_SetGdmRgb2yuvCoef11(pstCscCoef->csc_coef11);
    PQ_HAL_SetGdmRgb2yuvCoef12(pstCscCoef->csc_coef12);

    PQ_HAL_SetGdmRgb2yuvCoef20(pstCscCoef->csc_coef20);
    PQ_HAL_SetGdmRgb2yuvCoef21(pstCscCoef->csc_coef21);
    PQ_HAL_SetGdmRgb2yuvCoef22(pstCscCoef->csc_coef22);
}

HI_VOID PQ_HAL_SetGdmRgb2yuvDcCoef( PQ_GFX_CSC_DCCOEF_S *pstCscDcCoef)
{
    PQ_HAL_SetGdmRgb2yuvDcIn0 (pstCscDcCoef->csc_in_dc0);
    PQ_HAL_SetGdmRgb2yuvDcIn1 (pstCscDcCoef->csc_in_dc1);
    PQ_HAL_SetGdmRgb2yuvDcIn2 (pstCscDcCoef->csc_in_dc2);

    PQ_HAL_SetGdmRgb2yuvDcOut0(pstCscDcCoef->csc_out_dc0);
    PQ_HAL_SetGdmRgb2yuvDcOut1(pstCscDcCoef->csc_out_dc1);
    PQ_HAL_SetGdmRgb2yuvDcOut2(pstCscDcCoef->csc_out_dc2);

    return;
}

HI_VOID PQ_HAL_TransGfxCscPrecision(PQ_GFX_CSC_PRE_S *pstCscPre, PQ_GFX_CSC_COEF_S *pstCscOriCoef, PQ_GFX_CSC_DCCOEF_S *pstCscOriDcCoef,
                                    PQ_GFX_CSC_COEF_S *pstCscTrueCoef, PQ_GFX_CSC_DCCOEF_S *pstCscTrueDcCoef)
{
    HI_U32 CscCoefPre;      /* Csc 系数精度 */
    HI_U32 CscInDcCoefPre;  /* Csc 直流分量精度 */
    HI_U32 CscOutDcCoefPre; /* Csc 直流分量精度 */

    if (pstCscPre->CscCoefPre > 10)
    {
        CscCoefPre = 1 << (pstCscPre->CscCoefPre - 10);
    }
    else
    {
        CscCoefPre = 1;
    }

    if (pstCscPre->CscInDcCoefPre > 10)
    {
        CscInDcCoefPre = 1 << (pstCscPre->CscInDcCoefPre - 10);
    }
    else
    {
        CscInDcCoefPre = 1;
    }

    if (pstCscPre->CscOutDcCoefPre > 10)
    {
        CscOutDcCoefPre = 1 << (pstCscPre->CscOutDcCoefPre - 10);
    }
    else
    {
        CscOutDcCoefPre = 1;
    }

    pstCscTrueCoef->csc_coef00    = (HI_S32)(pstCscOriCoef->csc_coef00 * CscCoefPre);
    pstCscTrueCoef->csc_coef01    = (HI_S32)(pstCscOriCoef->csc_coef01 * CscCoefPre);
    pstCscTrueCoef->csc_coef02    = (HI_S32)(pstCscOriCoef->csc_coef02 * CscCoefPre);
    pstCscTrueCoef->csc_coef10    = (HI_S32)(pstCscOriCoef->csc_coef10 * CscCoefPre);
    pstCscTrueCoef->csc_coef11    = (HI_S32)(pstCscOriCoef->csc_coef11 * CscCoefPre);
    pstCscTrueCoef->csc_coef12    = (HI_S32)(pstCscOriCoef->csc_coef12 * CscCoefPre);
    pstCscTrueCoef->csc_coef20    = (HI_S32)(pstCscOriCoef->csc_coef20 * CscCoefPre);
    pstCscTrueCoef->csc_coef21    = (HI_S32)(pstCscOriCoef->csc_coef21 * CscCoefPre);
    pstCscTrueCoef->csc_coef22    = (HI_S32)(pstCscOriCoef->csc_coef22 * CscCoefPre);

    pstCscTrueDcCoef->csc_in_dc0  = (HI_S32)(pstCscOriDcCoef->csc_in_dc0  * CscInDcCoefPre);
    pstCscTrueDcCoef->csc_in_dc1  = (HI_S32)(pstCscOriDcCoef->csc_in_dc1  * CscInDcCoefPre);
    pstCscTrueDcCoef->csc_in_dc2  = (HI_S32)(pstCscOriDcCoef->csc_in_dc2  * CscInDcCoefPre);
    pstCscTrueDcCoef->csc_out_dc0 = (HI_S32)(pstCscOriDcCoef->csc_out_dc0 * CscOutDcCoefPre);
    pstCscTrueDcCoef->csc_out_dc1 = (HI_S32)(pstCscOriDcCoef->csc_out_dc1 * CscOutDcCoefPre);
    pstCscTrueDcCoef->csc_out_dc2 = (HI_S32)(pstCscOriDcCoef->csc_out_dc2 * CscOutDcCoefPre);

    return;
}

HI_S32 PQ_HAL_SetGfxCsc(HI_U32 enLayer, HI_BOOL bCSCEn, PQ_GFX_CSC_COEF_S *pstCscCoef, PQ_GFX_CSC_DCCOEF_S *pstCscDcCoef)
{
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetGfxGdmCsc(HI_U32 enLayer, HI_BOOL bCSCEn, PQ_GFX_CSC_COEF_S *pstCscCoef, PQ_GFX_CSC_DCCOEF_S *pstCscDcCoef)
{
    HI_U16 gdm_rgb2yuvscale2p   = 0;
    HI_U16 gdm_rgb2yuv_clip_min = 0;
    HI_U16 gdm_rgb2yuv_clip_max = 0;
    PQ_GFX_CSC_PRE_S    stCscPre;
    PQ_GFX_CSC_COEF_S   stCscTrueCoef;
    PQ_GFX_CSC_DCCOEF_S stCscTrueDcCoef;

    gdm_rgb2yuvscale2p   = 14;
    gdm_rgb2yuv_clip_min = 0;
    gdm_rgb2yuv_clip_max = 1023;

    stCscPre.CscCoefPre      = 14;
    stCscPre.CscInDcCoefPre  = 10;
    stCscPre.CscOutDcCoefPre = 10;

    PQ_HAL_TransGfxCscPrecision(&stCscPre, pstCscCoef, pstCscDcCoef, &stCscTrueCoef, &stCscTrueDcCoef);

    PQ_HAL_SetGdmRgb2yuvEn(bCSCEn);
    PQ_HAL_SetGdmRgb2yuvCoef     (&stCscTrueCoef);
    PQ_HAL_SetGdmRgb2yuvDcCoef       (&stCscTrueDcCoef);

    PQ_HAL_SetGdmRgb2yuvS2P(gdm_rgb2yuvscale2p);
    PQ_HAL_SetGdmRgb2yuvClipMin(gdm_rgb2yuv_clip_min);
    PQ_HAL_SetGdmRgb2yuvClipMax(gdm_rgb2yuv_clip_max);

    return HI_SUCCESS;
}
