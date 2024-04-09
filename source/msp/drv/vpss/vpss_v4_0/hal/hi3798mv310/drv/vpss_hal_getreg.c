#if 0

#include "vpss_hal_getreg.h"
#include "xdp_env_common.h"

#define XDP_RMOD_PROGRESIVE 1
#define XDP_RMOD_INTER_TOP  2
#define XDP_RMOD_INTER_BOT  3
#define XDP_RMOD_PROGR_TOP  4
#define XDP_RMDO_PROGR_BOT  5


HI_BOOL VPSS_HAL_GetbMeEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return 0;//(HI_BOOL) pstVPSSReg->SCAN_CTRL.bits.me_en;
}

HI_BOOL VPSS_HAL_GetbScdEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return 0;//(HI_BOOL) pstVPSSReg->VPSS_CTRL.bits.scd_en;
}

HI_BOOL VPSS_HAL_GetbDeiEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return (HI_BOOL) pstVPSSReg->VPSS_CTRL.bits.dei_en;
}

HI_BOOL VPSS_HAL_Getb3DrsEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return 0;//(HI_BOOL) pstVPSSReg->VPSS_CTRL.bits.vpss_3drs_en;
}

HI_BOOL VPSS_HAL_GetbRttEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return 0;//(HI_BOOL) pstVPSSReg->VPSS_CTRL.bits.rotate_en;
}


HI_U32 VPSS_HAL_GetMeVersion(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return 0;//pstVPSSReg->VPSS_CTRL.bits.me_version;
}

HI_U32 VPSS_HAL_GetImgProMode(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return pstVPSSReg->VPSS_CF_CTRL.bits.cf_lm_rmode;
}


HI_U32 VPSS_HAL_Get3DrsVersion(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return 0;//pstVPSSReg->VPSS_CTRL.bits.ma_mac_sel;
}

HI_BOOL VPSS_HAL_GetbCcclEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return 0;//(HI_BOOL) pstVPSSReg->VPSS_CTRL.bits.cccl_en;
}

HI_BOOL VPSS_HAL_GetbCcclRfrEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return 0;//(HI_BOOL) pstVPSSReg->VPSS_CC_RFR_CTRL.bits.cc_rfr_en;
}

HI_BOOL VPSS_HAL_GetbRgmeEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return (HI_BOOL) pstVPSSReg->VPSS_CTRL.bits.rgme_en;
}

HI_BOOL VPSS_HAL_GetbMcnrEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return (HI_BOOL) pstVPSSReg->VPSS_CTRL.bits.mcnr_en;
}

HI_BOOL VPSS_HAL_GetbRotateEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return (HI_BOOL) pstVPSSReg->VPSS_CHN_CFG_CTRL.bits.rotate_en;
}

HI_U32 VPSS_HAL_GetImgProcMode(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return pstVPSSReg->VPSS_CHN_CFG_CTRL.bits.img_pro_mode;
}

HI_BOOL VPSS_HAL_GetbMmuGlbBypass(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return (HI_BOOL) pstVPSSReg->VPSS0_SMMU_SCR.bits.glb_bypass;
    //return HI_TRUE;
}

HI_BOOL VPSS_HAL_GetbMmuImgBypass(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_CTRL         VPSS_CF_CTRL;

    VPSS_CF_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_CTRL.u32)) + u32Offset);

    return (HI_BOOL) VPSS_CF_CTRL.bits.cf_d_bypass;
}

HI_BOOL VPSS_HAL_GetbMmuSoloBypass(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_RMAD_CTRL         VPSS_NR_RMAD_CTRL;

    VPSS_NR_RMAD_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_RMAD_CTRL.u32)) + u32Offset);

    return (HI_BOOL) VPSS_NR_RMAD_CTRL.bits.nr_rmad_d_bypass;
}

HI_BOOL VPSS_HAL_GetbSnrMadEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
#if 0
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CTRL.u32) + u32Offset));

    return (HI_BOOL) VPSS_CTRL.bits.snr_mad_disable;
#endif
    return 0;
}


HI_BOOL VPSS_HAL_GetbMmuOutImgBypass(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_OUT0_CTRL        VPSS_OUT0_CTRL;

    VPSS_OUT0_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_OUT0_CTRL.u32)) + u32Offset);

    return (HI_BOOL) VPSS_OUT0_CTRL.bits.out0_d_bypass;
}

HI_BOOL VPSS_HAL_GetbMmuOutSoloBypass(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_WMAD_CTRL        VPSS_NR_WMAD_CTRL;

    VPSS_NR_WMAD_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_WMAD_CTRL.u32)) + u32Offset);

    return (HI_BOOL) VPSS_NR_WMAD_CTRL.bits.nr_wmad_d_bypass;
}

HI_BOOL VPSS_HAL_GetbOut0En(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return (HI_BOOL) pstVPSSReg->VPSS_OUT0_CTRL.bits.out0_en;
}


HI_BOOL VPSS_HAL_GetbSecEn(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    //return (HI_BOOL) pstVPSSReg->VPSS_CTRL.bits.prot;
    return HI_FALSE;
}

HI_BOOL VPSS_HAL_GetbTile(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return (HI_BOOL) (pstVPSSReg->VPSS_CF_CTRL.bits.cf_type == 1);
}

HI_BOOL VPSS_HAL_GetbSegDcmp(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return (HI_BOOL) (pstVPSSReg->VPSS_CF_CTRL.bits.cf_dcmp_mode == 1);
}


HI_U32 VPSS_HAl_GetMeVersion(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    return 0;//pstVPSSReg->VPSS_CTRL.bits.me_version;
}

HI_BOOL VPSS_HAL_GetbField(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_CTRL VPSS_CF_CTRL;

    VPSS_CF_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_CTRL.u32)) + u32Offset);

    return ((VPSS_CF_CTRL.bits.cf_lm_rmode == XDP_RMOD_INTER_TOP
             || VPSS_CF_CTRL.bits.cf_lm_rmode == XDP_RMOD_INTER_BOT ) ? HI_TRUE : HI_FALSE);
}


HI_BOOL VPSS_HAL_GetbCurBottom(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_CTRL VPSS_CF_CTRL;

    VPSS_CF_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_CTRL.u32)) + u32Offset);

    return ((VPSS_CF_CTRL.bits.cf_lm_rmode == XDP_RMOD_INTER_BOT
             || VPSS_CF_CTRL.bits.cf_lm_rmode == XDP_RMDO_PROGR_BOT) ? HI_TRUE : HI_FALSE);
}


HI_U32 VPSS_HAL_GetImgMode(S_VPSS_REGS_TYPE *pstVPSSReg)
{
    //return (HI_U32) pstVPSSReg->VPSS_CTRL.bits.bfield_first;
    return 0;
}

HI_U32 VPSS_HAL_GetGetRawIntStatus(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    return pstVpssRegs->VPSS_RAWINT.u32;
}

HI_U32 VPSS_HAL_GetGetIntStatus(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    return pstVpssRegs->VPSS_INTSTATE.u32;
}


HI_U32 VPSS_DRV_GetPfCnt(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    return pstVpssRegs->VPSS_PFCNT.u32;
}

#if 0
HI_U32 VPSS_DRV_GetEofCnt(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    U_VPSS_EOFCNT VPSS_EOFCNT;

    VPSS_EOFCNT.u32 = VPSS_RegRead((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_EOFCNT.u32)));

    return VPSS_EOFCNT.u32;
    return HI_SUCCESS;
}
#endif

HI_U32 VPSS_DRV_GetNodeId(S_VPSS_REGS_TYPE *pstVpssRegs)
{
#if 0
    U_VPSS_NODEID VPSS_NODEID;

    VPSS_NODEID.u32 = VPSS_RegRead((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_NODEID.u32)));

    return VPSS_NODEID.u32;
#endif
    return HI_SUCCESS;
}

HI_BOOL VPSS_DRV_GetbChkSumEn(S_VPSS_REGS_TYPE *pstVpssRegs)
{
#if 0
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((volatile HI_U32 *)((unsigned long) & (pstVpssRegs->VPSS_CTRL.u32)));

    return (HI_BOOL) VPSS_CTRL.bits.chk_sum_en;
#endif

    return HI_FALSE;
}

HI_S32 VPSS_DRV_Get_SMMU_INTSTAT_S(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 *pu32SecureState, HI_U32 *pu32NoSecureState)
{
#if 1
    U_VPSS0_SMMU_INTSTAT_S VPSS0_SMMU_INTSTAT_S;
    U_VPSS0_SMMU_INTSTAT_NS VPSS0_SMMU_INTSTAT_NS;

    VPSS0_SMMU_INTSTAT_S.u32 = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_INTRAW_S.u32));

    *pu32SecureState = VPSS0_SMMU_INTSTAT_S.u32;

    VPSS0_SMMU_INTSTAT_NS.u32 = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_INTRAW_NS.u32));

    *pu32NoSecureState = VPSS0_SMMU_INTSTAT_NS.u32;

    if (0 != VPSS0_SMMU_INTSTAT_NS.u32)
    {
        HI_U32 SMMU_FAULT_ADDR_PTW_NS, SMMU_FAULT_ID_PTW_NS, SMMU_FAULT_PTW_NUM;
        HI_U32 SMMU_FAULT_ADDR_RD_NS, SMMU_FAULT_TLB_RD_NS, SMMU_FAULT_ID_RD_NS;
        HI_U32 SMMU_FAULT_ADDR_WR_NS, SMMU_FAULT_TLB_WR_NS, SMMU_FAULT_ID_WR_NS;

        XDP_PRINT_ERR("Error! SMMU, S-int:%u, NS-int:%u\n", VPSS0_SMMU_INTSTAT_S.u32, VPSS0_SMMU_INTSTAT_NS.u32);

        SMMU_FAULT_ADDR_PTW_NS  = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_PTW_NS.u32));
        SMMU_FAULT_ID_PTW_NS    = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ID_PTW_NS.u32));
        SMMU_FAULT_PTW_NUM      = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_PTW_NUM.u32));
        SMMU_FAULT_ADDR_RD_NS   = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_RD_NS.u32));
        SMMU_FAULT_TLB_RD_NS    = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_TLB_RD_NS.u32));
        SMMU_FAULT_ID_RD_NS     = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ID_RD_NS.u32));

        XDP_PRINT_ERR("SMMU_FAULT_ADDR_PTW_NS:%x (%u) \nSMMU_FAULT_ID_PTW_NS:%u \nSMMU_FAULT_PTW_NUM:%u\n",
                      SMMU_FAULT_ADDR_PTW_NS, SMMU_FAULT_ADDR_PTW_NS, SMMU_FAULT_ID_PTW_NS, SMMU_FAULT_PTW_NUM);
        XDP_PRINT_ERR("SMMU_FAULT_ADDR_RD_NS:%x (%u) \nSMMU_FAULT_TLB_RD_NS:%u \nSMMU_FAULT_ID_RD_NS:%u\n",
                      SMMU_FAULT_ADDR_RD_NS, SMMU_FAULT_ADDR_RD_NS, SMMU_FAULT_TLB_RD_NS, SMMU_FAULT_ID_RD_NS);
        SMMU_FAULT_ADDR_WR_NS = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_WR_NS.u32));
        SMMU_FAULT_TLB_WR_NS = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_TLB_WR_NS.u32));
        SMMU_FAULT_ID_WR_NS = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ID_WR_NS.u32));
        XDP_PRINT_ERR("SMMU_FAULT_ADDR_WR_NS:%x (%u)\nSMMU_FAULT_TLB_WR_NS:%u\nSMMU_FAULT_ID_WR_NS:%u\n",
                      SMMU_FAULT_ADDR_WR_NS, SMMU_FAULT_ADDR_WR_NS,
                      SMMU_FAULT_TLB_WR_NS,
                      SMMU_FAULT_ID_WR_NS);
    }

    if (0 != VPSS0_SMMU_INTSTAT_S.u32)
    {
        HI_U32 SMMU_FAULT_ADDR_PTW_S, SMMU_FAULT_ID_PTW_S, SMMU_FAULT_PTW_NUM;
        HI_U32 SMMU_FAULT_ADDR_RD_S, SMMU_FAULT_TLB_RD_S, SMMU_FAULT_ID_RD_S;
        HI_U32 SMMU_FAULT_ADDR_WR_S, SMMU_FAULT_TLB_WR_S,   SMMU_FAULT_ID_WR_S;
        HI_U32 SMMU_SCB_TTBR;

        XDP_PRINT_ERR("Error! SMMU, S-int:%u, NS-int:%u\n", VPSS0_SMMU_INTSTAT_S.u32, VPSS0_SMMU_INTSTAT_NS.u32);

        SMMU_FAULT_ADDR_PTW_S   = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_PTW_S.u32));
        SMMU_FAULT_ID_PTW_S     = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ID_PTW_S.u32));
        SMMU_FAULT_PTW_NUM      = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_PTW_NUM.u32));
        SMMU_FAULT_ADDR_RD_S    = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_RD_S.u32));
        SMMU_FAULT_TLB_RD_S     = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_TLB_RD_S.u32));
        SMMU_FAULT_ID_RD_S      = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ID_RD_S.u32));
        SMMU_SCB_TTBR           = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_SCB_TTBR.u32));


        XDP_PRINT_ERR("SMMU_FAULT_ADDR_PTW_S:%x (%u) \nSMMU_FAULT_ID_PTW_S:%u \nSMMU_FAULT_PTW_NUM:%u\n",
                      SMMU_FAULT_ADDR_PTW_S, SMMU_FAULT_ADDR_PTW_S, SMMU_FAULT_ID_PTW_S, SMMU_FAULT_PTW_NUM);
        XDP_PRINT_ERR("SMMU_FAULT_ADDR_RD_S:%x (%u) \nSMMU_FAULT_TLB_RD_S:%u \nSMMU_FAULT_ID_RD_S:%u\n",
                      SMMU_FAULT_ADDR_RD_S, SMMU_FAULT_ADDR_RD_S, SMMU_FAULT_TLB_RD_S, SMMU_FAULT_ID_RD_S);
        SMMU_FAULT_ADDR_WR_S = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_WR_S.u32));
        SMMU_FAULT_TLB_WR_S = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_TLB_WR_S.u32));
        SMMU_FAULT_ID_WR_S = VPSS_RegRead((HI_ULONG) & (pstVpssRegs->VPSS0_SMMU_FAULT_ID_WR_S.u32));
        XDP_PRINT_ERR("SMMU_FAULT_ADDR_WR_S:%x (%u)\nSMMU_FAULT_TLB_WR_S:%u\nSMMU_FAULT_ID_WR_S:%u\nSMMU_SCB_TTBR:%x\n",
                      SMMU_FAULT_ADDR_WR_S, SMMU_FAULT_ADDR_WR_S,
                      SMMU_FAULT_TLB_WR_S,
                      SMMU_FAULT_ID_WR_S,
                      SMMU_SCB_TTBR);
    }
#endif

    return HI_SUCCESS;
}

//##########################GET IMG RCH###################
HI_BOOL VPSS_HAL_GetbImgRChnEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_CTRL VPSS_CF_CTRL;

    VPSS_CF_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_CTRL.u32)) + u32Offset);

    return (HI_BOOL) VPSS_CF_CTRL.bits.cf_en;
}


HI_U32 VPSS_HAL_GetImgRChnFormat(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    XDP_LAYER_IFMT_E   enLayerFmt = XDP_LAYER_IFMT_SP_420;
    HI_U32 u32Format = 0;
    HI_U32 u32Type = 0;
    U_VPSS_CF_CTRL VPSS_CF_CTRL;

    VPSS_CF_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_CTRL.u32)) + u32Offset);

    u32Format = VPSS_CF_CTRL.bits.cf_format;
    u32Type   = VPSS_CF_CTRL.bits.cf_type;

    if (u32Type == 0) //sp
    {
        if (u32Format == 0)
        {
            enLayerFmt = XDP_LAYER_IFMT_SP_420;
        }
        else if (u32Format == 1)
        {
            enLayerFmt = XDP_LAYER_IFMT_SP_422;
        }
        else if (u32Format == 2)
        {
            enLayerFmt = XDP_LAYER_IFMT_SP_444;
        }
        else if (u32Format == 3)
        {
            enLayerFmt = XDP_LAYER_IFMT_SP_400;
        }
    }
    else if (u32Type == 1) //tile
    {
        if (u32Format == 0)
        {
            enLayerFmt = XDP_LAYER_IFMT_TILE_420;
        }
        else if (u32Format == 3)
        {
            enLayerFmt = XDP_LAYER_IFMT_TILE_400;
        }
    }

    return enLayerFmt;
}

HI_U32 VPSS_HAL_GetImgRChnHorOffset(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_OFFSET VPSS_CF_OFFSET;

    VPSS_CF_OFFSET.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_OFFSET.u32)) + u32Offset);

    return (HI_U32) VPSS_CF_OFFSET.bits.cf_hor_offset;
}

HI_U32 VPSS_HAL_GetImgRChnVerOffset(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_OFFSET VPSS_CF_OFFSET;

    VPSS_CF_OFFSET.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_OFFSET.u32)) + u32Offset);

    return (HI_U32) VPSS_CF_OFFSET.bits.cf_ver_offset;
}

HI_U32 VPSS_HAL_GetImgRChnWidth(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_SIZE VPSS_CF_SIZE;

    VPSS_CF_SIZE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_SIZE.u32)) + u32Offset);

    return (HI_U32) VPSS_CF_SIZE.bits.cf_width + 1;
}

HI_U32 VPSS_HAL_GetImgRChnHeight(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_SIZE VPSS_CF_SIZE;

    VPSS_CF_SIZE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_SIZE.u32)) + u32Offset);

    return (HI_U32) VPSS_CF_SIZE.bits.cf_height + 1;
}

HI_U32 VPSS_HAL_GetImgRChnYStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_STRIDE VPSS_CF_STRIDE;

    VPSS_CF_STRIDE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_STRIDE.u32)) + u32Offset);

    return (HI_U32) VPSS_CF_STRIDE.bits.cfy_stride;
}

HI_U32 VPSS_HAL_GetImgRChnCStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_STRIDE VPSS_CF_STRIDE;

    VPSS_CF_STRIDE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_STRIDE.u32)) + u32Offset);

    return (HI_U32) VPSS_CF_STRIDE.bits.cfc_stride;
}

HI_U32 VPSS_HAL_GetImgRChnPixBtW(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_CF_CTRL VPSS_CF_CTRL;

    VPSS_CF_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_CF_CTRL.u32)) + u32Offset);

    return (HI_U32) VPSS_CF_CTRL.bits.cf_bitw;
}

//##########################GET IMG WCH###################
HI_BOOL VPSS_HAL_GetbImgWChnEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_OUT0_CTRL VPSS_OUT0_CTRL;

    VPSS_OUT0_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_OUT0_CTRL.u32)) + u32Offset);

    return (HI_BOOL) VPSS_OUT0_CTRL.bits.out0_en;
}

HI_BOOL VPSS_HAL_GetbFrmCmp(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_OUT0_CTRL VPSS_OUT0_CTRL;

    VPSS_OUT0_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_OUT0_CTRL.u32)) + u32Offset);

    return 0;//(HI_BOOL) (VPSS_OUT0_CTRL.bits.out0_cmp_mode==3);
}


HI_U32 VPSS_HAL_GetImgWChnFormat(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    XDP_LAYER_IFMT_E   enLayerFmt = XDP_LAYER_IFMT_SP_420;
    HI_U32 u32Format = 0;
    U_VPSS_OUT0_CTRL VPSS_OUT0_CTRL;

    VPSS_OUT0_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_OUT0_CTRL.u32)) + u32Offset);
    u32Format = VPSS_OUT0_CTRL.bits.reserved_0; //format

    if (u32Format == 0)
    {
        enLayerFmt = XDP_LAYER_IFMT_SP_420;
    }
    else if (u32Format == 1)
    {
        enLayerFmt = XDP_LAYER_IFMT_SP_422;
    }
    else if (u32Format == 2)
    {
        enLayerFmt = XDP_LAYER_IFMT_SP_444;
    }
    else if (u32Format == 3)
    {
        enLayerFmt = XDP_LAYER_IFMT_SP_400;
    }

    return enLayerFmt;
}

HI_U32 VPSS_HAL_GetImgWChnWidth(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_OUT0_SIZE VPSS_OUT0_SIZE;

    VPSS_OUT0_SIZE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_OUT0_SIZE.u32)) + u32Offset);

    return (HI_U32) VPSS_OUT0_SIZE.bits.out0_width + 1;
}

HI_U32 VPSS_HAL_GetImgWChnHeight(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_OUT0_SIZE VPSS_OUT0_SIZE;

    VPSS_OUT0_SIZE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_OUT0_SIZE.u32)) + u32Offset);

    return (HI_U32) VPSS_OUT0_SIZE.bits.out0_height + 1;
}

HI_U32 VPSS_HAL_GetImgWChnYStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_OUT0_STRIDE VPSS_OUT0_STRIDE;

    VPSS_OUT0_STRIDE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_OUT0_STRIDE.u32)) + u32Offset);

    return (HI_U32) VPSS_OUT0_STRIDE.bits.out0y_stride;
}

HI_U32 VPSS_HAL_GetImgWChnCStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_OUT0_STRIDE VPSS_OUT0_STRIDE;

    VPSS_OUT0_STRIDE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_OUT0_STRIDE.u32)) + u32Offset);

    return (HI_U32) VPSS_OUT0_STRIDE.bits.out0c_stride;
}

HI_U32 VPSS_HAL_GetImgWChnPixBtW(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_OUT0_CTRL VPSS_OUT0_CTRL;

    VPSS_OUT0_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_OUT0_CTRL.u32)) + u32Offset);

    return (HI_U32) VPSS_OUT0_CTRL.bits.out0_bitw;
}
//##########################GET SOLO RCH###################
HI_BOOL VPSS_HAL_GetbSoloRChnEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_RMAD_CTRL VPSS_NR_RMAD_CTRL;

    VPSS_NR_RMAD_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_RMAD_CTRL.u32)) + u32Offset);

    return (HI_BOOL) VPSS_NR_RMAD_CTRL.bits.nr_rmad_en;
}

HI_U32 VPSS_HAL_GetSoloRChnWidth(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_RMAD_SIZE VPSS_NR_RMAD_SIZE;

    VPSS_NR_RMAD_SIZE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_RMAD_SIZE.u32)) + u32Offset);

    return (HI_U32) VPSS_NR_RMAD_SIZE.bits.nr_rmad_width + 1;
}

HI_U32 VPSS_HAL_GetSoloRChnHeight(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_RMAD_SIZE VPSS_NR_RMAD_SIZE;

    VPSS_NR_RMAD_SIZE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_RMAD_SIZE.u32)) + u32Offset);

    return (HI_U32) VPSS_NR_RMAD_SIZE.bits.nr_rmad_height + 1;
}

HI_U32 VPSS_HAL_GetSoloRChnStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_RMAD_STRIDE VPSS_NR_RMAD_STRIDE;

    VPSS_NR_RMAD_STRIDE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_RMAD_STRIDE.u32)) + u32Offset);

    return (HI_U32) VPSS_NR_RMAD_STRIDE.bits.nr_rmad_stride;
}

//##########################GET SOLO WCH###################
HI_BOOL VPSS_HAL_GetbSoloWChnEn(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_WMAD_CTRL VPSS_NR_WMAD_CTRL;

    VPSS_NR_WMAD_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_WMAD_CTRL.u32)) + u32Offset);

    return (HI_BOOL) VPSS_NR_WMAD_CTRL.bits.nr_wmad_en;
}

HI_U32 VPSS_HAL_GetSoloWChnWidth(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_WMAD_SIZE VPSS_NR_WMAD_SIZE;

    VPSS_NR_WMAD_SIZE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_WMAD_SIZE.u32)) + u32Offset);

    return (HI_U32) VPSS_NR_WMAD_SIZE.bits.nr_wmad_width + 1;
}

HI_U32 VPSS_HAL_GetSoloWChnHeight(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_WMAD_SIZE VPSS_NR_WMAD_SIZE;

    VPSS_NR_WMAD_SIZE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_WMAD_SIZE.u32)) + u32Offset);

    return (HI_U32) VPSS_NR_WMAD_SIZE.bits.nr_wmad_height + 1;
}

HI_U32 VPSS_HAL_GetSoloWChnStride(S_VPSS_REGS_TYPE *pstVPSSReg, HI_U32 u32Offset)
{
    U_VPSS_NR_WMAD_STRIDE VPSS_NR_WMAD_STRIDE;

    VPSS_NR_WMAD_STRIDE.u32 = VPSS_RegRead((HI_ULONG)(&(pstVPSSReg->VPSS_NR_WMAD_STRIDE.u32)) + u32Offset);

    return (HI_U32) VPSS_NR_WMAD_STRIDE.bits.nr_wmad_stride;
}

HI_BOOL VPSS_HAL_GetCfCConvert(S_VPSS_REGS_TYPE *pVdpReg)
{
#if 0
    U_VPSS_CHN_CFG_CTRL VPSS_CHN_CFG_CTRL;

    VPSS_CHN_CFG_CTRL.u32 = VPSS_RegRead((HI_ULONG)(&(pVdpReg->VPSS_CHN_CFG_CTRL.u32)));

    return (HI_BOOL)VPSS_CHN_CFG_CTRL.bits.cf_c_convert;
#endif
    return 0;
}

#endif
