/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_lcacm.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2016/07/18
  Description   :

******************************************************************************/
#include <linux/string.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_drv_mmz.h"
#include "hi_drv_mem.h"

#include "pq_hal_comm.h"
#include "pq_hal_lcacm.h"

static HI_PQ_HDR_MODE_E sg_enHDRMode = HI_PQ_HDR_MODE_HDR10_TO_SDR;
static PQ_PARAM_S *sg_pstBinPara  = HI_NULL;
static PQ_BIN_HDR_ACM_REGCFG_S sg_stAcmRegBinOrCode;

static HI_U32 sg_u32ToolHdrAcmMode = 0;//ѡ��HDR����ģʽ��0:�̶�������1:���ߵ��Բ���
static PQ_HAL_ACM_PARA_S g_stToolHdrAcmPara = {0}; //tool para
static PQ_HAL_ACM_PARA_S g_stAcmParaTmp = {0}; //code tmp para
static HI_S32 g_as32HdrAcmRegCfgDefault[PQ_TOOL_HDR_BUTT][PQ_HDR_ACM_REGCFG_SIZE] =
{
    //HDR2SDR ACM Para
    {
        8,  8,  -2,  -2,  -2,  -2,  -8, -4, -4, -8,
        7,  9,  -11,  -11,  -4,  -4,  0, 0, 0, 0,
        8,  6,  1,  1,  3,  3,  -2, -1, -1, -2,
        11,  5,  -12,  -12,  -12,  -12,  0, 0, 0, 0,
    },
    //SDR2HDR ACM Para
    {
        0,  0,  0,  0,  0,  0,  0, 0, 0, 0,
        0,  0,  0,  0,  0,  0,  0, 0, 0, 0,
        0,  0,  0,  0,  0,  0,  0, 0, 0, 0,
        0,  0,  0,  0,  0,  0,  0, 0, 0, 0,
    }
};

typedef HI_S32 (*PF_PQ_Hal_GetHdrLcAcmCfg) (HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS);

static HI_PQ_HDR_MODE_E aenPqHalHdrLcAcmMode[HI_DRV_VIDEO_FRAME_TYPE_BUTT][HI_PQ_DISP_TYPE_BUTT] =
{
    {HI_PQ_HDR_MODE_SDR_TO_SDR,     HI_PQ_HDR_MODE_SDR_TO_HDR10,    HI_PQ_HDR_MODE_SDR_TO_HLG       },   /* sdr */
    {HI_PQ_HDR_MODE_HDR10_TO_HDR10, HI_PQ_HDR_MODE_HDR10_TO_HDR10,  HI_PQ_HDR_MODE_HDR10_TO_HDR10   },   /* bl */
    {HI_PQ_HDR_MODE_HDR10_TO_HDR10, HI_PQ_HDR_MODE_HDR10_TO_HDR10,  HI_PQ_HDR_MODE_HDR10_TO_HDR10   },   /* el */
    {HI_PQ_HDR_MODE_HDR10_TO_SDR,   HI_PQ_HDR_MODE_HDR10_TO_HDR10,  HI_PQ_HDR_MODE_HDR10_TO_HLG     },   /* hdr10 */
    {HI_PQ_HDR_MODE_HLG_TO_SDR,     HI_PQ_HDR_MODE_HLG_TO_HDR10,    HI_PQ_HDR_MODE_HLG_TO_HLG       },   /* hlg */
    {HI_PQ_HDR_MODE_SLF_TO_SDR,     HI_PQ_HDR_MODE_SLF_TO_HDR10,    HI_PQ_HDR_MODE_SLF_TO_HLG       },   /* slf */
    {HI_PQ_HDR_MODE_HDR10_TO_HDR10, HI_PQ_HDR_MODE_HDR10_TO_HDR10,  HI_PQ_HDR_MODE_HDR10_TO_HDR10   },   /* tech */
};

HI_VOID PQ_HAL_SetAcm3En(HI_U32 u32Data, HI_U32 acm3_en)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcm3En Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm3_en = acm3_en;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcm2En(HI_U32 u32Data, HI_U32 acm2_en)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcm2En Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm2_en = acm2_en;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcm1En(HI_U32 u32Data, HI_U32 acm1_en)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcm1En Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm1_en = acm1_en;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcm0En(HI_U32 u32Data, HI_U32 acm0_en)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcm0En Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm0_en = acm0_en;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmSecBlk0(HI_U32 u32Data, HI_U32 acm_sec_blk)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmSecBlk0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm_sec_blk = acm_sec_blk;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmFirBlk0(HI_U32 u32Data, HI_U32 acm_fir_blk)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmFirBlk0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm_fir_blk = acm_fir_blk;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmDUOff0(HI_U32 u32Data, HI_U32 acm_d_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmDUOff0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm_d_u_off = acm_d_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmCUOff0(HI_U32 u32Data, HI_U32 acm_c_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmCUOff0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm_c_u_off = acm_c_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmBUOff0(HI_U32 u32Data, HI_U32 acm_b_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmBUOff0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm_b_u_off = acm_b_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmAUOff0(HI_U32 u32Data, HI_U32 acm_a_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM0 VHDACM0;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmAUOff0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM0.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM0.bits.acm_a_u_off = acm_a_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM0.u32)) + u32Data * PQ_VP_OFFSET), VHDACM0.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmTestEn(HI_U32 u32Data, HI_U32 acm_test_en)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM1 VHDACM1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmTestEn Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM1.bits.acm_test_en = acm_test_en;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET), VHDACM1.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmDbgMode(HI_U32 u32Data, HI_U32 acm_dbg_mode)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM1 VHDACM1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmTestEn Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM1.bits.acm_dbg_mode = acm_dbg_mode;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET), VHDACM1.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmProtMode(HI_U32 u32Data, HI_U32 bw_pro_mode)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM1 VHDACM1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmTestEn Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM1.bits.bw_pro_mode = bw_pro_mode;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET), VHDACM1.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmDVOff0(HI_U32 u32Data, HI_U32 acm_d_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM1 VHDACM1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmDVOff0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM1.bits.acm_d_v_off = acm_d_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET), VHDACM1.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmCVOff0(HI_U32 u32Data, HI_U32 acm_c_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM1 VHDACM1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmCVOff0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM1.bits.acm_c_v_off = acm_c_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET), VHDACM1.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmBVOff0(HI_U32 u32Data, HI_U32 acm_b_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM1 VHDACM1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmBVOff0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM1.bits.acm_b_v_off = acm_b_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET), VHDACM1.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmAVOff0(HI_U32 u32Data, HI_U32 acm_a_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM1 VHDACM1;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmAVOff0 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM1.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM1.bits.acm_a_v_off = acm_a_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM1.u32)) + u32Data * PQ_VP_OFFSET), VHDACM1.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmSecBlk1(HI_U32 u32Data, HI_U32 acm_sec_blk)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM2 VHDACM2;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmSecBlk1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM2.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM2.bits.acm_sec_blk = acm_sec_blk;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET), VHDACM2.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmFirBlk1(HI_U32 u32Data, HI_U32 acm_fir_blk)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM2 VHDACM2;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmFirBlk1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM2.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM2.bits.acm_fir_blk = acm_fir_blk;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET), VHDACM2.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmDUOff1(HI_U32 u32Data, HI_U32 acm_d_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM2 VHDACM2;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmDUOff1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM2.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM2.bits.acm_d_u_off = acm_d_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET), VHDACM2.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmCUOff1(HI_U32 u32Data, HI_U32 acm_c_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM2 VHDACM2;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmCUOff1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM2.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM2.bits.acm_c_u_off = acm_c_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET), VHDACM2.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmBUOff1(HI_U32 u32Data, HI_U32 acm_b_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM2 VHDACM2;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmBUOff1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM2.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM2.bits.acm_b_u_off = acm_b_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET), VHDACM2.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmAUOff1(HI_U32 u32Data, HI_U32 acm_a_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM2 VHDACM2;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmAUOff1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM2.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM2.bits.acm_a_u_off = acm_a_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM2.u32)) + u32Data * PQ_VP_OFFSET), VHDACM2.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmDVOff1(HI_U32 u32Data, HI_U32 acm_d_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM3 VHDACM3;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmDVOff1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM3.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM3.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM3.bits.acm_d_v_off = acm_d_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM3.u32)) + u32Data * PQ_VP_OFFSET), VHDACM3.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmCVOff1(HI_U32 u32Data, HI_U32 acm_c_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM3 VHDACM3;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmCVOff1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM3.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM3.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM3.bits.acm_c_v_off = acm_c_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM3.u32)) + u32Data * PQ_VP_OFFSET), VHDACM3.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmBVOff1(HI_U32 u32Data, HI_U32 acm_b_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM3 VHDACM3;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmBVOff1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM3.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM3.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM3.bits.acm_b_v_off = acm_b_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM3.u32)) + u32Data * PQ_VP_OFFSET), VHDACM3.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmAVOff1(HI_U32 u32Data, HI_U32 acm_a_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM3 VHDACM3;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmAVOff1 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM3.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM3.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM3.bits.acm_a_v_off = acm_a_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM3.u32)) + u32Data * PQ_VP_OFFSET), VHDACM3.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmSecBlk2(HI_U32 u32Data, HI_U32 acm_sec_blk)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM4 VHDACM4;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmSecBlk2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM4.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM4.bits.acm_sec_blk = acm_sec_blk;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET), VHDACM4.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmFirBlk2(HI_U32 u32Data, HI_U32 acm_fir_blk)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM4 VHDACM4;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmFirBlk2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM4.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM4.bits.acm_fir_blk = acm_fir_blk;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET), VHDACM4.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmDUOff2(HI_U32 u32Data, HI_U32 acm_d_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM4 VHDACM4;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmDUOff2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM4.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM4.bits.acm_d_u_off = acm_d_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET), VHDACM4.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmCUOff2(HI_U32 u32Data, HI_U32 acm_c_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM4 VHDACM4;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmCUOff2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM4.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM4.bits.acm_c_u_off = acm_c_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET), VHDACM4.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmBUOff2(HI_U32 u32Data, HI_U32 acm_b_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM4 VHDACM4;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmBUOff2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM4.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM4.bits.acm_b_u_off = acm_b_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET), VHDACM4.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmAUOff2(HI_U32 u32Data, HI_U32 acm_a_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM4 VHDACM4;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmAUOff2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM4.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM4.bits.acm_a_u_off = acm_a_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM4.u32)) + u32Data * PQ_VP_OFFSET), VHDACM4.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmDVOff2(HI_U32 u32Data, HI_U32 acm_d_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM5 VHDACM5;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmDVOff2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM5.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM5.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM5.bits.acm_d_v_off = acm_d_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM5.u32)) + u32Data * PQ_VP_OFFSET), VHDACM5.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmCVOff2(HI_U32 u32Data, HI_U32 acm_c_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM5 VHDACM5;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmCVOff2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM5.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM5.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM5.bits.acm_c_v_off = acm_c_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM5.u32)) + u32Data * PQ_VP_OFFSET), VHDACM5.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmBVOff2(HI_U32 u32Data, HI_U32 acm_b_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM5 VHDACM5;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmBVOff2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM5.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM5.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM5.bits.acm_b_v_off = acm_b_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM5.u32)) + u32Data * PQ_VP_OFFSET), VHDACM5.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmAVOff2(HI_U32 u32Data, HI_U32 acm_a_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM5 VHDACM5;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmAVOff2 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM5.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM5.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM5.bits.acm_a_v_off = acm_a_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM5.u32)) + u32Data * PQ_VP_OFFSET), VHDACM5.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmSecBlk3(HI_U32 u32Data, HI_U32 acm_sec_blk)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM6 VHDACM6;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmSecBlk3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM6.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM6.bits.acm_sec_blk = acm_sec_blk;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET), VHDACM6.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmFirBlk3(HI_U32 u32Data, HI_U32 acm_fir_blk)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM6 VHDACM6;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmFirBlk3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM6.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM6.bits.acm_fir_blk = acm_fir_blk;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET), VHDACM6.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmDUOff3(HI_U32 u32Data, HI_U32 acm_d_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM6 VHDACM6;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmDUOff3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM6.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM6.bits.acm_d_u_off = acm_d_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET), VHDACM6.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmCUOff3(HI_U32 u32Data, HI_U32 acm_c_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM6 VHDACM6;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmCUOff3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM6.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM6.bits.acm_c_u_off = acm_c_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET), VHDACM6.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmBUOff3(HI_U32 u32Data, HI_U32 acm_b_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM6 VHDACM6;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmBUOff3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM6.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM6.bits.acm_b_u_off = acm_b_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET), VHDACM6.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmAUOff3(HI_U32 u32Data, HI_U32 acm_a_u_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM6 VHDACM6;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmAUOff3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM6.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM6.bits.acm_a_u_off = acm_a_u_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM6.u32)) + u32Data * PQ_VP_OFFSET), VHDACM6.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmDVOff3(HI_U32 u32Data, HI_U32 acm_d_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM7 VHDACM7;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmDVOff3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM7.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM7.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM7.bits.acm_d_v_off = acm_d_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM7.u32)) + u32Data * PQ_VP_OFFSET), VHDACM7.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmCVOff3(HI_U32 u32Data, HI_U32 acm_c_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM7 VHDACM7;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmCVOff3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM7.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM7.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM7.bits.acm_c_v_off = acm_c_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM7.u32)) + u32Data * PQ_VP_OFFSET), VHDACM7.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmBVOff3(HI_U32 u32Data, HI_U32 acm_b_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM7 VHDACM7;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmBVOff3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM7.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM7.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM7.bits.acm_b_v_off = acm_b_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM7.u32)) + u32Data * PQ_VP_OFFSET), VHDACM7.u32);

    return;
}

HI_VOID PQ_HAL_SetAcmAVOff3(HI_U32 u32Data, HI_U32 acm_a_v_off)
{
    S_VDP_REGS_TYPE *pstVdpReg = HI_NULL;
    U_VHDACM7 VHDACM7;

    if (u32Data >= VID_MAX)
    {
        HI_ERR_PQ("Error, SetAcmAVOff3 Select Wrong Layer ID\n");
    }

    pstVdpReg = PQ_HAL_GetVdpReg();
    VHDACM7.u32 = PQ_HAL_RegRead((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM7.u32)) + u32Data * PQ_VP_OFFSET));
    VHDACM7.bits.acm_a_v_off = acm_a_v_off;
    PQ_HAL_RegWrite((HI_U32 *)((HI_ULONG)(&(pstVdpReg->VHDACM7.u32)) + u32Data * PQ_VP_OFFSET), VHDACM7.u32);

    return;
}

HI_VOID PQ_HAL_SetACMEn(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff)
{
    PQ_HAL_SetAcm0En(VDP_LAYER_VP0, bOnOff);
    PQ_HAL_SetAcm1En(VDP_LAYER_VP0, bOnOff);
    PQ_HAL_SetAcm2En(VDP_LAYER_VP0, bOnOff);
    PQ_HAL_SetAcm3En(VDP_LAYER_VP0, bOnOff);

    return;
}

HI_VOID PQ_HAL_SetACMDemoEn(PQ_HAL_LAYER_VP_E u32ChId, HI_BOOL bOnOff)
{
    PQ_HAL_SetAcmTestEn(u32ChId, bOnOff);

    return;
}

HI_VOID PQ_HAL_SetACMDemoMode(PQ_HAL_LAYER_VP_E u32ChId, HAL_ACM_DEMO_MODE_E enACMDemoMode)
{
    PQ_HAL_SetAcmDbgMode(u32ChId, enACMDemoMode);

    return;
}

HI_VOID PQ_HAL_SetLCACMPara(HI_U32 enLayer, PQ_HAL_ACM_PARA_S *pstAcmPara)
{
    PQ_HAL_SetAcmSecBlk0 ( enLayer, pstAcmPara->acm0_sec_blk);
    PQ_HAL_SetAcmFirBlk0 ( enLayer, pstAcmPara->acm0_fir_blk);

    PQ_HAL_SetAcmDUOff0  ( enLayer, pstAcmPara->acm0_d_u_off);
    PQ_HAL_SetAcmCUOff0  ( enLayer, pstAcmPara->acm0_c_u_off);
    PQ_HAL_SetAcmBUOff0  ( enLayer, pstAcmPara->acm0_b_u_off);
    PQ_HAL_SetAcmAUOff0  ( enLayer, pstAcmPara->acm0_a_u_off);

    PQ_HAL_SetAcmDVOff0  ( enLayer, pstAcmPara->acm0_d_v_off);
    PQ_HAL_SetAcmCVOff0  ( enLayer, pstAcmPara->acm0_c_v_off);
    PQ_HAL_SetAcmBVOff0  ( enLayer, pstAcmPara->acm0_b_v_off);
    PQ_HAL_SetAcmAVOff0  ( enLayer, pstAcmPara->acm0_a_v_off);

    PQ_HAL_SetAcmSecBlk1 ( enLayer, pstAcmPara->acm1_sec_blk);
    PQ_HAL_SetAcmFirBlk1 ( enLayer, pstAcmPara->acm1_fir_blk);

    PQ_HAL_SetAcmDUOff1  ( enLayer, pstAcmPara->acm1_d_u_off);
    PQ_HAL_SetAcmCUOff1  ( enLayer, pstAcmPara->acm1_c_u_off);
    PQ_HAL_SetAcmBUOff1  ( enLayer, pstAcmPara->acm1_b_u_off);
    PQ_HAL_SetAcmAUOff1  ( enLayer, pstAcmPara->acm1_a_u_off);

    PQ_HAL_SetAcmDVOff1  ( enLayer, pstAcmPara->acm1_d_v_off);
    PQ_HAL_SetAcmCVOff1  ( enLayer, pstAcmPara->acm1_c_v_off);
    PQ_HAL_SetAcmBVOff1  ( enLayer, pstAcmPara->acm1_b_v_off);
    PQ_HAL_SetAcmAVOff1  ( enLayer, pstAcmPara->acm1_a_v_off);

    PQ_HAL_SetAcmSecBlk2 ( enLayer, pstAcmPara->acm2_sec_blk);
    PQ_HAL_SetAcmFirBlk2 ( enLayer, pstAcmPara->acm2_fir_blk);

    PQ_HAL_SetAcmDUOff2  ( enLayer, pstAcmPara->acm2_d_u_off);
    PQ_HAL_SetAcmCUOff2  ( enLayer, pstAcmPara->acm2_c_u_off);
    PQ_HAL_SetAcmBUOff2  ( enLayer, pstAcmPara->acm2_b_u_off);
    PQ_HAL_SetAcmAUOff2  ( enLayer, pstAcmPara->acm2_a_u_off);

    PQ_HAL_SetAcmDVOff2  ( enLayer, pstAcmPara->acm2_d_v_off);
    PQ_HAL_SetAcmCVOff2  ( enLayer, pstAcmPara->acm2_c_v_off);
    PQ_HAL_SetAcmBVOff2  ( enLayer, pstAcmPara->acm2_b_v_off);
    PQ_HAL_SetAcmAVOff2  ( enLayer, pstAcmPara->acm2_a_v_off);

    PQ_HAL_SetAcmSecBlk3 ( enLayer, pstAcmPara->acm3_sec_blk);
    PQ_HAL_SetAcmFirBlk3 ( enLayer, pstAcmPara->acm3_fir_blk);

    PQ_HAL_SetAcmDUOff3  ( enLayer, pstAcmPara->acm3_d_u_off);
    PQ_HAL_SetAcmCUOff3  ( enLayer, pstAcmPara->acm3_c_u_off);
    PQ_HAL_SetAcmBUOff3  ( enLayer, pstAcmPara->acm3_b_u_off);
    PQ_HAL_SetAcmAUOff3  ( enLayer, pstAcmPara->acm3_a_u_off);

    PQ_HAL_SetAcmDVOff3  ( enLayer, pstAcmPara->acm3_d_v_off);
    PQ_HAL_SetAcmCVOff3  ( enLayer, pstAcmPara->acm3_c_v_off);
    PQ_HAL_SetAcmBVOff3  ( enLayer, pstAcmPara->acm3_b_v_off);
    PQ_HAL_SetAcmAVOff3  ( enLayer, pstAcmPara->acm3_a_v_off);

    return;
}

HI_S32 PQ_HAL_SetNormLcacmFleshToneCfg(HI_PQ_FLESHTONE_E enGainLevel)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};

    stAcmPara.acm0_sec_blk = 9;
    stAcmPara.acm0_fir_blk = 7;

    stAcmPara.acm0_d_u_off = 0;
    stAcmPara.acm0_c_u_off = 0;
    stAcmPara.acm0_b_u_off = -2;
    stAcmPara.acm0_a_u_off = -2;
    stAcmPara.acm0_d_v_off = 0;
    stAcmPara.acm0_c_v_off = 2;
    stAcmPara.acm0_b_v_off = 3;
    stAcmPara.acm0_a_v_off = 4;

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    return HI_SUCCESS;
}


HI_S32 PQ_HAL_SetNormLcacmCfg(HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};

    if (HI_PQ_COLOR_MODE_BLUE == enColorSpecMode)
    {
        stAcmPara.acm0_sec_blk = 7;
        stAcmPara.acm0_fir_blk = 9;

        stAcmPara.acm0_d_u_off = 5;
        stAcmPara.acm0_c_u_off = 2;
        stAcmPara.acm0_b_u_off = 0;
        stAcmPara.acm0_a_u_off = 3;
        stAcmPara.acm0_d_v_off = -5;
        stAcmPara.acm0_c_v_off = 0;
        stAcmPara.acm0_b_v_off = 0;
        stAcmPara.acm0_a_v_off = -3;
    }
    else if (HI_PQ_COLOR_MODE_GREEN == enColorSpecMode)
    {
        stAcmPara.acm0_sec_blk = 7;
        stAcmPara.acm0_fir_blk = 6;

        stAcmPara.acm0_d_u_off = -1;
        stAcmPara.acm0_c_u_off = -2;
        stAcmPara.acm0_b_u_off = -4;
        stAcmPara.acm0_a_u_off = -4;
        stAcmPara.acm0_d_v_off = -1;
        stAcmPara.acm0_c_v_off = -5;
        stAcmPara.acm0_b_v_off = -6;
        stAcmPara.acm0_a_v_off = -8;
    }
    else if (HI_PQ_COLOR_MODE_BG == enColorSpecMode)
    {
        stAcmPara.acm0_sec_blk = 7;
        stAcmPara.acm0_fir_blk = 9;

        stAcmPara.acm0_d_u_off = 5;
        stAcmPara.acm0_c_u_off = 2;
        stAcmPara.acm0_b_u_off = 0;
        stAcmPara.acm0_a_u_off = 3;
        stAcmPara.acm0_d_v_off = -5;
        stAcmPara.acm0_c_v_off = 0;
        stAcmPara.acm0_b_v_off = 0;
        stAcmPara.acm0_a_v_off = -3;

        stAcmPara.acm1_sec_blk = 7;
        stAcmPara.acm1_fir_blk = 6;

        stAcmPara.acm1_d_u_off = -1;
        stAcmPara.acm1_c_u_off = -2;
        stAcmPara.acm1_b_u_off = -4;
        stAcmPara.acm1_a_u_off = -4;
        stAcmPara.acm1_d_v_off = -1;
        stAcmPara.acm1_c_v_off = -5;
        stAcmPara.acm1_b_v_off = -6;
        stAcmPara.acm1_a_v_off = -8;

        stAcmPara.acm2_sec_blk = 0;
        stAcmPara.acm2_fir_blk = 0;
    }

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetAcmHDR2HDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    PQ_HAL_ACM_CFG_S  stAcmCfg = {0};

    memset(&stAcmPara, 0, sizeof(PQ_HAL_ACM_PARA_S));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    stAcmCfg.bw_pro_mode  = 0;
    stAcmCfg.acm_dbg_mode = 0;
    stAcmCfg.acm_test_en  = 0;

    PQ_HAL_SetAcmProtMode(VDP_LAYER_VP0, stAcmCfg.bw_pro_mode);
    PQ_HAL_SetAcmDbgMode(VDP_LAYER_VP0, stAcmCfg.acm_dbg_mode);
    PQ_HAL_SetAcmTestEn(VDP_LAYER_VP0, stAcmCfg.acm_test_en);

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetAcmHDR2SDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    PQ_HAL_ACM_CFG_S  stAcmCfg = {0};

    if (HI_DRV_CS_BT2020_YUV_LIMITED == enOutCS)
    {
        memset(&g_stAcmParaTmp, 0, sizeof(PQ_HAL_ACM_PARA_S));
    }
    else
    {
        memcpy(&g_stAcmParaTmp, sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_HDR2SDR], sizeof(PQ_HAL_ACM_PARA_S));

        if (0 == sg_u32ToolHdrAcmMode)
        {
            memcpy(&g_stToolHdrAcmPara, &g_stAcmParaTmp, sizeof(PQ_HAL_ACM_PARA_S));
        }
        else if (1 == sg_u32ToolHdrAcmMode)
        {
            memcpy(&g_stAcmParaTmp, &g_stToolHdrAcmPara, sizeof(PQ_HAL_ACM_PARA_S));
        }
    }

    memcpy(&stAcmPara, &g_stAcmParaTmp, sizeof(PQ_HAL_ACM_PARA_S));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    stAcmCfg.bw_pro_mode  = 0;
    stAcmCfg.acm_dbg_mode = 0;
    stAcmCfg.acm_test_en  = 0;

    PQ_HAL_SetAcmProtMode(VDP_LAYER_VP0, stAcmCfg.bw_pro_mode);
    PQ_HAL_SetAcmDbgMode(VDP_LAYER_VP0, stAcmCfg.acm_dbg_mode);
    PQ_HAL_SetAcmTestEn(VDP_LAYER_VP0, stAcmCfg.acm_test_en);

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetAcmHDR2HLGCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    PQ_HAL_ACM_CFG_S  stAcmCfg = {0};

    memset(&stAcmPara, 0, sizeof(PQ_HAL_ACM_PARA_S));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    stAcmCfg.bw_pro_mode  = 0;
    stAcmCfg.acm_dbg_mode = 0;
    stAcmCfg.acm_test_en  = 0;

    PQ_HAL_SetAcmProtMode(VDP_LAYER_VP0, stAcmCfg.bw_pro_mode);
    PQ_HAL_SetAcmDbgMode(VDP_LAYER_VP0, stAcmCfg.acm_dbg_mode);
    PQ_HAL_SetAcmTestEn(VDP_LAYER_VP0, stAcmCfg.acm_test_en);

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetAcmHLG2SDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    PQ_HAL_ACM_CFG_S  stAcmCfg = {0};

    memset(&stAcmPara, 0, sizeof(PQ_HAL_ACM_PARA_S));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    stAcmCfg.bw_pro_mode  = 0;
    stAcmCfg.acm_dbg_mode = 0;
    stAcmCfg.acm_test_en  = 0;

    PQ_HAL_SetAcmProtMode(VDP_LAYER_VP0, stAcmCfg.bw_pro_mode);
    PQ_HAL_SetAcmDbgMode(VDP_LAYER_VP0, stAcmCfg.acm_dbg_mode);
    PQ_HAL_SetAcmTestEn(VDP_LAYER_VP0, stAcmCfg.acm_test_en);

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetAcmHLG2HDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    PQ_HAL_ACM_CFG_S  stAcmCfg = {0};

    memset(&stAcmPara, 0, sizeof(PQ_HAL_ACM_PARA_S));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    stAcmCfg.bw_pro_mode  = 0;
    stAcmCfg.acm_dbg_mode = 0;
    stAcmCfg.acm_test_en  = 0;

    PQ_HAL_SetAcmProtMode(VDP_LAYER_VP0, stAcmCfg.bw_pro_mode);
    PQ_HAL_SetAcmDbgMode(VDP_LAYER_VP0, stAcmCfg.acm_dbg_mode);
    PQ_HAL_SetAcmTestEn(VDP_LAYER_VP0, stAcmCfg.acm_test_en);

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetAcmHLG2HLGCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    PQ_HAL_ACM_CFG_S  stAcmCfg = {0};

    memset(&stAcmPara, 0, sizeof(PQ_HAL_ACM_PARA_S));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    stAcmCfg.bw_pro_mode  = 0;
    stAcmCfg.acm_dbg_mode = 0;
    stAcmCfg.acm_test_en  = 0;

    PQ_HAL_SetAcmProtMode(VDP_LAYER_VP0, stAcmCfg.bw_pro_mode);
    PQ_HAL_SetAcmDbgMode(VDP_LAYER_VP0, stAcmCfg.acm_dbg_mode);
    PQ_HAL_SetAcmTestEn(VDP_LAYER_VP0, stAcmCfg.acm_test_en);

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetAcmSLF2SDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    HI_UNUSED(enInCS);
    HI_UNUSED(enOutCS);

    return HI_FAILURE;
}

static HI_S32 pq_hal_GetAcmSLF2HLGCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    HI_UNUSED(enInCS);
    HI_UNUSED(enOutCS);

    return HI_FAILURE;
}

static HI_S32 pq_hal_GetAcmSLF2HDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    HI_UNUSED(enInCS);
    HI_UNUSED(enOutCS);

    return HI_FAILURE;
}

static HI_S32 pq_hal_GetAcmSDR2HDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    PQ_HAL_ACM_CFG_S  stAcmCfg = {0};

    if (HI_DRV_CS_BT2020_YUV_LIMITED == enOutCS)
    {
        memset(&g_stAcmParaTmp, 0, sizeof(PQ_HAL_ACM_PARA_S));
    }
    else
    {
        memcpy(&g_stAcmParaTmp, sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_SDR2HDR], sizeof(PQ_HAL_ACM_PARA_S));

        if (0 == sg_u32ToolHdrAcmMode)
        {
            memcpy(&g_stToolHdrAcmPara, &g_stAcmParaTmp, sizeof(PQ_HAL_ACM_PARA_S));
        }
        else if (1 == sg_u32ToolHdrAcmMode)
        {
            memcpy(&g_stAcmParaTmp, &g_stToolHdrAcmPara, sizeof(PQ_HAL_ACM_PARA_S));
        }
    }

    memcpy(&stAcmPara, &g_stAcmParaTmp, sizeof(PQ_HAL_ACM_PARA_S));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    stAcmCfg.bw_pro_mode  = 0;
    stAcmCfg.acm_dbg_mode = 0;
    stAcmCfg.acm_test_en  = 0;

    PQ_HAL_SetAcmProtMode(VDP_LAYER_VP0, stAcmCfg.bw_pro_mode);
    PQ_HAL_SetAcmDbgMode(VDP_LAYER_VP0, stAcmCfg.acm_dbg_mode);
    PQ_HAL_SetAcmTestEn(VDP_LAYER_VP0, stAcmCfg.acm_test_en);

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetAcmSDR2SDRCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    PQ_HAL_ACM_CFG_S  stAcmCfg = {0};

    memset(&stAcmPara, 0, sizeof(PQ_HAL_ACM_PARA_S));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    stAcmCfg.bw_pro_mode  = 0;
    stAcmCfg.acm_dbg_mode = 0;
    stAcmCfg.acm_test_en  = 0;

    PQ_HAL_SetAcmProtMode(VDP_LAYER_VP0, stAcmCfg.bw_pro_mode);
    PQ_HAL_SetAcmDbgMode(VDP_LAYER_VP0, stAcmCfg.acm_dbg_mode);
    PQ_HAL_SetAcmTestEn(VDP_LAYER_VP0, stAcmCfg.acm_test_en);

    return HI_SUCCESS;
}

static HI_S32 pq_hal_GetAcmSDR2HLGCfg(HI_DRV_COLOR_SPACE_E enInCS, HI_DRV_COLOR_SPACE_E enOutCS)
{
    PQ_HAL_ACM_PARA_S stAcmPara = {0};
    PQ_HAL_ACM_CFG_S  stAcmCfg = {0};

    memset(&stAcmPara, 0, sizeof(PQ_HAL_ACM_PARA_S));

    PQ_HAL_SetLCACMPara(VDP_LAYER_VP0, &stAcmPara);

    stAcmCfg.bw_pro_mode  = 0;
    stAcmCfg.acm_dbg_mode = 0;
    stAcmCfg.acm_test_en  = 0;

    PQ_HAL_SetAcmProtMode(VDP_LAYER_VP0, stAcmCfg.bw_pro_mode);
    PQ_HAL_SetAcmDbgMode(VDP_LAYER_VP0, stAcmCfg.acm_dbg_mode);
    PQ_HAL_SetAcmTestEn(VDP_LAYER_VP0, stAcmCfg.acm_test_en);

    return HI_SUCCESS;
}

PF_PQ_Hal_GetHdrLcAcmCfg pfPqHalGetHdrLcAcmCfg[HI_PQ_HDR_MODE_BUTT] =
{
    pq_hal_GetAcmHDR2SDRCfg,
    pq_hal_GetAcmHDR2HDRCfg,
    pq_hal_GetAcmHDR2HLGCfg,

    pq_hal_GetAcmHLG2SDRCfg,
    pq_hal_GetAcmHLG2HDRCfg,
    pq_hal_GetAcmHLG2HLGCfg,

    pq_hal_GetAcmSLF2SDRCfg,
    pq_hal_GetAcmSLF2HDRCfg,
    pq_hal_GetAcmSLF2HLGCfg,

    pq_hal_GetAcmSDR2SDRCfg,
    pq_hal_GetAcmSDR2HDRCfg,
    pq_hal_GetAcmSDR2HLGCfg,
};

HI_S32 PQ_HAL_GetHdrLcacmCfg(HI_PQ_XDR_FRAME_INFO *pstXdrFrameInfo)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enSrcFrameType, HI_DRV_VIDEO_FRAME_TYPE_BUTT);
    PQ_CHECK_OVER_RANGE_RE_FAIL(pstXdrFrameInfo->enDispType, HI_PQ_DISP_TYPE_BUTT);

    sg_enHDRMode = aenPqHalHdrLcAcmMode[pstXdrFrameInfo->enSrcFrameType][pstXdrFrameInfo->enDispType];

    PQ_CHECK_OVER_RANGE_RE_FAIL(sg_enHDRMode, HI_PQ_HDR_MODE_BUTT);

    s32Ret  = pfPqHalGetHdrLcAcmCfg[sg_enHDRMode](pstXdrFrameInfo->enInCS, pstXdrFrameInfo->enOutCS);

    return s32Ret;
}

HI_S32 PQ_HAL_Tool_SetHdrAcmMode(HI_PQ_HDR_ACM_MODE_S *pstMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstMode);

    sg_u32ToolHdrAcmMode = pstMode->u32ParaModeUse;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_Tool_GetHdrAcmMode(HI_PQ_HDR_ACM_MODE_S *pstMode)
{
    PQ_CHECK_NULL_PTR_RE_FAIL(pstMode);

    pstMode->u32ParaModeUse = sg_u32ToolHdrAcmMode;

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_Tool_SetHdrAcmRegCfg(HI_PQ_HDR_ACM_REGCFG_S *pstCfg)
{
    HI_U32 tmp0 = sizeof(PQ_HAL_ACM_PARA_S);
    HI_U32 tmp1 = sizeof(HI_PQ_HDR_ACM_REGCFG_S);
    if (tmp0 != tmp1)
    {
        HI_ERR_PQ("%d,%d\n", tmp0, tmp1);
        return HI_FAILURE;
    }

    /* Tool Tmp Acm Para */
    memcpy(&g_stToolHdrAcmPara, pstCfg, sizeof(PQ_HAL_ACM_PARA_S));

    /* Save Acm Para into BinPara */
    switch (sg_enHDRMode)
    {
        case HI_PQ_HDR_MODE_HDR10_TO_SDR:
            memcpy(sg_pstBinPara->stPQCoef.stBinHdrAcmRegCfg.as32Regcfg[PQ_TOOL_HDR2SDR], pstCfg, \
                   sizeof(sg_pstBinPara->stPQCoef.stBinHdrAcmRegCfg.as32Regcfg[PQ_TOOL_HDR2SDR]));
            break;
        case HI_PQ_HDR_MODE_SDR_TO_HDR10:
            memcpy(sg_pstBinPara->stPQCoef.stBinHdrAcmRegCfg.as32Regcfg[PQ_TOOL_SDR2HDR], pstCfg, \
                   sizeof(sg_pstBinPara->stPQCoef.stBinHdrAcmRegCfg.as32Regcfg[PQ_TOOL_SDR2HDR]));
            break;
        default:
            HI_ERR_PQ("PQ Tool Only Support Hdr2Sdr & Sdr2Hdr Now \n");
            break;
    }

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_Tool_GetHdrAcmRegCfg(HI_PQ_HDR_ACM_REGCFG_S *pstCfg)
{
    HI_U32 tmp0 = sizeof(PQ_HAL_ACM_PARA_S);
    HI_U32 tmp1 = sizeof(HI_PQ_HDR_ACM_REGCFG_S);
    if (tmp0 != tmp1)
    {
        HI_ERR_PQ("%d,%d\n", tmp0, tmp1);
    }
    else
    {
        memcpy(pstCfg , &g_stToolHdrAcmPara, sizeof(PQ_HAL_ACM_PARA_S));
    }

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_InitLcacm(PQ_PARAM_S *pstPqParam, HI_BOOL bParaUseTableDefault)
{
    HI_S32 s32RegAllZero0 = 0;
    HI_S32 s32RegAllZero1 = 0;
    HI_U32 i = 0;

    sg_pstBinPara = pstPqParam;

    PQ_CHECK_NULL_PTR_RE_FAIL(sg_pstBinPara);

    /* step 1 : check pq bin data : all zero means no effective para from bin */
    for (i = 0; i < PQ_HDR_ACM_REGCFG_SIZE; i++)
    {
        if (0 != sg_pstBinPara->stPQCoef.stBinHdrAcmRegCfg.as32Regcfg[PQ_TOOL_HDR2SDR][i])
        {
            s32RegAllZero0++;
            break;
        }
    }

    for (i = 0; i < PQ_HDR_ACM_REGCFG_SIZE; i++)
    {
        if (0 != sg_pstBinPara->stPQCoef.stBinHdrAcmRegCfg.as32Regcfg[PQ_TOOL_SDR2HDR][i])
        {
            s32RegAllZero1++;
            break;
        }
    }

    /* step 2 : para use from bin or code */
    /*
        1.use bin para : if bin para not all zero
        2.use code para : if bin para all zero or no bin exist
    */
    if ((HI_TRUE != bParaUseTableDefault) && (s32RegAllZero0 != 0))
    {
        /* HDR2SDR : use bin para && bin para not all 0 */
        memcpy(sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_HDR2SDR], sg_pstBinPara->stPQCoef.stBinHdrAcmRegCfg.as32Regcfg[PQ_TOOL_HDR2SDR], \
               sizeof(sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_HDR2SDR]));
    }
    else
    {
        memcpy(sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_HDR2SDR], g_as32HdrAcmRegCfgDefault[PQ_TOOL_HDR2SDR], \
               sizeof(sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_HDR2SDR]));
    }


    if ((HI_TRUE != bParaUseTableDefault) && (s32RegAllZero1 != 0))
    {
        /* SDR2HDR : use bin para && bin para not all 0 */
        memcpy(sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_SDR2HDR], sg_pstBinPara->stPQCoef.stBinHdrAcmRegCfg.as32Regcfg[PQ_TOOL_SDR2HDR], \
               sizeof(sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_SDR2HDR]));
    }
    else
    {
        memcpy(sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_SDR2HDR], g_as32HdrAcmRegCfgDefault[PQ_TOOL_SDR2HDR], \
               sizeof(sg_stAcmRegBinOrCode.as32Regcfg[PQ_TOOL_SDR2HDR]));
    }

    return HI_SUCCESS;
}
