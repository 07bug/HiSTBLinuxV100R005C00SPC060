/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_sharpen.c
  Version       : Initial Draft
  Author        :
  Created       : 2013/11/2
  Description   : Hisilicon multimedia software group
******************************************************************************/
#include "hi_type.h"
#include "hi_debug.h"
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"

#include "pq_hal_sharpen.h"


HI_S32 PQ_HAL_EnableSharp(HI_BOOL bOnOff)
{
    S_VDP_REGS_TYPE *pVDPReg = HI_NULL;
    U_SPCTRL  SPCTRL;

    pVDPReg = PQ_HAL_GetVdpReg();
    SPCTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVDPReg->SPCTRL.u32))));
    SPCTRL.bits.sharpen_en = bOnOff;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVDPReg->SPCTRL.u32))), SPCTRL.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetSharpStrReg(HI_U32 u32Data, HI_U32 u32PeakGain, HI_U32 u32EdgeGain)
{
    S_VDP_REGS_TYPE *pVdpReg = HI_NULL;
    U_SPGAIN   SPGAIN;

    pVdpReg = PQ_HAL_GetVdpReg();
    SPGAIN.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPGAIN.u32))));
    SPGAIN.bits.peak_gain = u32PeakGain;
    SPGAIN.bits.edge_gain = u32EdgeGain;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPGAIN.u32))), SPGAIN.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetSharpPeakGain(HI_U32 u32Data, HI_U32 u32PeakGain)
{
    S_VDP_REGS_TYPE *pVdpReg = HI_NULL;
    U_SPGAIN   SPGAIN;

    pVdpReg = PQ_HAL_GetVdpReg();
    SPGAIN.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPGAIN.u32)) + u32Data * PQ_VID_OFFSET));
    SPGAIN.bits.peak_gain = u32PeakGain;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPGAIN.u32)) + u32Data * PQ_VID_OFFSET), SPGAIN.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetSharpDetecEn(HI_U32 u32Data, HI_BOOL bOnOff)
{
    S_VDP_REGS_TYPE *pVdpReg = HI_NULL;
    U_SPCTRL   SPCTRL;

    pVdpReg = PQ_HAL_GetVdpReg();
    SPCTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32)) + u32Data * PQ_VID_OFFSET));
    SPCTRL.bits.detec_en = bOnOff;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32)) + u32Data * PQ_VID_OFFSET), SPCTRL.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_EnableSharpDemo(HI_U32 u32Data, HI_BOOL bOnOff)
{
    S_VDP_REGS_TYPE *pVdpReg = HI_NULL;
    U_SPCTRL         SPCTRL;

    pVdpReg = PQ_HAL_GetVdpReg();
    SPCTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32))));
    SPCTRL.bits.demo_en = bOnOff;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32))), SPCTRL.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetSharpDemoMode(HI_U32 u32Data, SHARP_DEMO_MODE_E enMode)
{
    S_VDP_REGS_TYPE *pVdpReg = HI_NULL;
    U_SPCTRL         SPCTRL;

    pVdpReg = PQ_HAL_GetVdpReg();
    SPCTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32))));
    SPCTRL.bits.demo_mode = enMode;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32))), SPCTRL.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetSharpDemoPos(HI_U32 u32Data, HI_U32 u32Pos)
{
    S_VDP_REGS_TYPE *pVdpReg = HI_NULL;
    U_SPCTRL         SPCTRL;

    pVdpReg = PQ_HAL_GetVdpReg();
    SPCTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32))));
    SPCTRL.bits.demo_pos = u32Pos;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32))), SPCTRL.u32);

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetSharpDemoPos(HI_U32 u32Data, HI_U32 *pu32XPos)
{
    S_VDP_REGS_TYPE *pVdpReg = HI_NULL;
    U_SPCTRL         SPCTRL;

    PQ_CHECK_NULL_PTR_RE_FAIL(pu32XPos);

    pVdpReg = PQ_HAL_GetVdpReg();
    SPCTRL.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32))));
    *pu32XPos = SPCTRL.bits.demo_pos;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_PARA_SetParaAddrVhdChn04( HI_U32 para_addr_vhd_chn04)
{
    S_VDP_REGS_TYPE *pVdpReg = HI_NULL;
    U_PARA_ADDR_VHD_CHN04 PARA_ADDR_VHD_CHN04;

    pVdpReg = PQ_HAL_GetVdpReg();

    PARA_ADDR_VHD_CHN04.bits.para_addr_vhd_chn04 = para_addr_vhd_chn04;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->PARA_ADDR_VHD_CHN04.u32))), PARA_ADDR_VHD_CHN04.u32);

    return HI_SUCCESS;
}

HI_VOID PQ_HAL_PARA_SetShpParaUp(HI_VOID)
{
    S_VDP_REGS_TYPE *pVdpReg = HI_NULL;
    U_PARA_UP_VHD PARA_UP_VHD;

    pVdpReg = PQ_HAL_GetVdpReg();

    PARA_UP_VHD.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pVdpReg->PARA_UP_VHD.u32))));
    PARA_UP_VHD.bits.para_up_vhd_chn04 = 0x1;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pVdpReg->SPCTRL.u32))), PARA_UP_VHD.u32);

    return;
}

