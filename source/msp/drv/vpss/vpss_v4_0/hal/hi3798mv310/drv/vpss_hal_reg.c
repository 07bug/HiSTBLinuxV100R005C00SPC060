
//vpss_hal_ip_sys.cpp begin

#include "vpss_hal_reg.h"
#include "vpss_hal_comm.h"
#include "vpss_cbb_reg.h"


HI_U32 VPSS_HAL_GetGetRawIntStatus(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    return pstVpssRegs->VPSS_RAWINT.u32;
}

HI_U32 VPSS_HAL_GetGetIntStatus(S_VPSS_REGS_TYPE *pstVpssRegs)
{
    return pstVpssRegs->VPSS_INTSTATE.u32;
}


HI_S32 VPSS_DRV_Get_SMMU_INTSTAT_S(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 *pu32SecureState, HI_U32 *pu32NoSecureState)
{
#if 1
    U_VPSS0_SMMU_INTSTAT_S VPSS0_SMMU_INTSTAT_S;
    U_VPSS0_SMMU_INTSTAT_NS VPSS0_SMMU_INTSTAT_NS;

    VPSS0_SMMU_INTSTAT_S.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_INTRAW_S.u32));

    *pu32SecureState = VPSS0_SMMU_INTSTAT_S.u32;

    VPSS0_SMMU_INTSTAT_NS.u32 = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_INTRAW_NS.u32));

    *pu32NoSecureState = VPSS0_SMMU_INTSTAT_NS.u32;

    if (0 != VPSS0_SMMU_INTSTAT_NS.u32)
    {
        HI_U32 SMMU_FAULT_ADDR_PTW_NS, SMMU_FAULT_ID_PTW_NS, SMMU_FAULT_PTW_NUM;
        HI_U32 SMMU_FAULT_ADDR_RD_NS, SMMU_FAULT_TLB_RD_NS, SMMU_FAULT_ID_RD_NS;
        HI_U32 SMMU_FAULT_ADDR_WR_NS, SMMU_FAULT_TLB_WR_NS, SMMU_FAULT_ID_WR_NS;

        VPSS_FATAL("Error! SMMU, S-int:%u, NS-int:%u\n", VPSS0_SMMU_INTSTAT_S.u32, VPSS0_SMMU_INTSTAT_NS.u32);

        SMMU_FAULT_ADDR_PTW_NS  = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_PTW_NS.u32));
        SMMU_FAULT_ID_PTW_NS    = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ID_PTW_NS.u32));
        SMMU_FAULT_PTW_NUM      = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_PTW_NUM.u32));
        SMMU_FAULT_ADDR_RD_NS   = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_RD_NS.u32));
        SMMU_FAULT_TLB_RD_NS    = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_TLB_RD_NS.u32));
        SMMU_FAULT_ID_RD_NS     = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ID_RD_NS.u32));

        VPSS_FATAL("SMMU_FAULT_ADDR_PTW_NS:%x (%u) \nSMMU_FAULT_ID_PTW_NS:%u \nSMMU_FAULT_PTW_NUM:%u\n",
                   SMMU_FAULT_ADDR_PTW_NS, SMMU_FAULT_ADDR_PTW_NS, SMMU_FAULT_ID_PTW_NS, SMMU_FAULT_PTW_NUM);
        VPSS_FATAL("SMMU_FAULT_ADDR_RD_NS:%x (%u) \nSMMU_FAULT_TLB_RD_NS:%u \nSMMU_FAULT_ID_RD_NS:%u\n",
                   SMMU_FAULT_ADDR_RD_NS, SMMU_FAULT_ADDR_RD_NS, SMMU_FAULT_TLB_RD_NS, SMMU_FAULT_ID_RD_NS);
        SMMU_FAULT_ADDR_WR_NS = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_WR_NS.u32));
        SMMU_FAULT_TLB_WR_NS = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_TLB_WR_NS.u32));
        SMMU_FAULT_ID_WR_NS = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ID_WR_NS.u32));
        VPSS_FATAL("SMMU_FAULT_ADDR_WR_NS:%x (%u)\nSMMU_FAULT_TLB_WR_NS:%u\nSMMU_FAULT_ID_WR_NS:%u\n",
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

        VPSS_FATAL("Error! SMMU, S-int:%u, NS-int:%u\n", VPSS0_SMMU_INTSTAT_S.u32, VPSS0_SMMU_INTSTAT_NS.u32);

        SMMU_FAULT_ADDR_PTW_S   = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_PTW_S.u32));
        SMMU_FAULT_ID_PTW_S     = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ID_PTW_S.u32));
        SMMU_FAULT_PTW_NUM      = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_PTW_NUM.u32));
        SMMU_FAULT_ADDR_RD_S    = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_RD_S.u32));
        SMMU_FAULT_TLB_RD_S     = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_TLB_RD_S.u32));
        SMMU_FAULT_ID_RD_S      = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ID_RD_S.u32));
        SMMU_SCB_TTBR           = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_SCB_TTBR.u32));


        VPSS_FATAL("SMMU_FAULT_ADDR_PTW_S:%x (%u) \nSMMU_FAULT_ID_PTW_S:%u \nSMMU_FAULT_PTW_NUM:%u\n",
                   SMMU_FAULT_ADDR_PTW_S, SMMU_FAULT_ADDR_PTW_S, SMMU_FAULT_ID_PTW_S, SMMU_FAULT_PTW_NUM);
        VPSS_FATAL("SMMU_FAULT_ADDR_RD_S:%x (%u) \nSMMU_FAULT_TLB_RD_S:%u \nSMMU_FAULT_ID_RD_S:%u\n",
                   SMMU_FAULT_ADDR_RD_S, SMMU_FAULT_ADDR_RD_S, SMMU_FAULT_TLB_RD_S, SMMU_FAULT_ID_RD_S);
        SMMU_FAULT_ADDR_WR_S = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ADDR_WR_S.u32));
        SMMU_FAULT_TLB_WR_S = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_TLB_WR_S.u32));
        SMMU_FAULT_ID_WR_S = VPSS_RegRead(&(pstVpssRegs->VPSS0_SMMU_FAULT_ID_WR_S.u32));
        VPSS_FATAL("SMMU_FAULT_ADDR_WR_S:%x (%u)\nSMMU_FAULT_TLB_WR_S:%u\nSMMU_FAULT_ID_WR_S:%u\nSMMU_SCB_TTBR:%x\n",
                   SMMU_FAULT_ADDR_WR_S, SMMU_FAULT_ADDR_WR_S,
                   SMMU_FAULT_TLB_WR_S,
                   SMMU_FAULT_ID_WR_S,
                   SMMU_SCB_TTBR);
    }
#endif

    return HI_SUCCESS;
}

HI_U32 VPSS_Sys_GetPfcnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset)
{
    HI_U32 u32GetData = 0;
    U_VPSS_PFCNT VPSS_PFCNT;
    VPSS_PFCNT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PFCNT.u32) + u32AddrOffset));
    u32GetData = VPSS_PFCNT.u32;
    return u32GetData;
}

HI_U32 VPSS_DRV_GetEofCnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset)
{
    HI_U32 u32GetData = 0;
    u32GetData = VPSS_RegRead((&(pstVpssRegs->VPSS_EOFCNT.u32) + u32AddrOffset));
    return u32GetData;
}

HI_VOID VPSS_Sys_SetIntMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32Mask)
{
    U_VPSS_INTMASK         VPSS_INTMASK                      ; /* 0x324 */
    VPSS_INTMASK.u32 = u32Mask;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset), VPSS_INTMASK.u32);
    return ;
}

HI_U32 VPSS_Sys_GetIntState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset)
{
    HI_U32 u32GetData = 0;
    U_VPSS_INTSTATE        VPSS_INTSTATE                     ; /* 0x304 */
    VPSS_INTSTATE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset));
    u32GetData = VPSS_INTSTATE.u32;
    return u32GetData;
}

HI_VOID VPSS_Sys_SetIntClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32Data1)
{
    U_VPSS_INTCLR          VPSS_INTCLR                       ; /* 0x308 */
    VPSS_INTCLR.u32 = u32Data1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset), VPSS_INTCLR.u32);
    return ;
}


HI_VOID VPSS_Sys_SetBfieldFirst(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bfield_first)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.bfield_first = bfield_first;

    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}



HI_VOID VPSS_Sys_SetIgbmEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 igbm_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.igbm_en = igbm_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIfmdEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ifmd_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.ifmd_en = ifmd_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHdrIn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hdr_in)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.hdr_in = hdr_in;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFourPixEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 four_pix_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.four_pix_en = four_pix_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetTnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 tnr_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.tnr_en = tnr_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetSnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 snr_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.snr_en = snr_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}



HI_VOID VPSS_Sys_SetBlkDetEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 blk_det_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.blk_det_en = blk_det_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}

HI_VOID VPSS_Sys_SetNrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 nr_en)
{
    U_VPSS_DB_CTRL VPSS_DB_CTRL;

    VPSS_DB_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset));
    VPSS_DB_CTRL.bits.nr_en = nr_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset), VPSS_DB_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_en)
{
    U_VPSS_DB_CTRL VPSS_DB_CTRL;

    VPSS_DB_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset));
    VPSS_DB_CTRL.bits.dm_en = dm_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset), VPSS_DB_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_en)
{
    U_VPSS_DB_CTRL VPSS_DB_CTRL;

    VPSS_DB_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset));
    VPSS_DB_CTRL.bits.db_en = db_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset), VPSS_DB_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBit10BypassEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bit10_bypass_en)
{
    U_VPSS_CTRL VPSS_CTRL;
    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.bit10_bypass_en = bit10_bypass_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);
    return ;
}

HI_VOID VPSS_Sys_SetRgmeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rgme_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.rgme_en = rgme_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}

HI_VOID VPSS_Sys_SetVc1En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vc1_en)
{
    U_VPSS_CTRL VPSS_CTRL;
    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.vc1_en = vc1_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);
    return ;
}


HI_VOID VPSS_Sys_SetMcdiEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcdi_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.mcdi_en = mcdi_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDeiEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dei_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.dei_en = dei_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);
    return ;
}
HI_VOID VPSS_Sys_SetOutProEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 out_pro_en)
{
    U_VPSS_CTRL VPSS_CTRL;
    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.out_pro_en = out_pro_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMadVfirEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mad_vfir_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.mad_vfir_en = mad_vfir_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.vhd0_en = vhd0_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcnr_en)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.mcnr_en = mcnr_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetTnrMadMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 tnr_mad_mode)
{
    U_VPSS_CTRL VPSS_CTRL;

    VPSS_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset));
    VPSS_CTRL.bits.tnr_mad_mode = tnr_mad_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL.u32) + u32AddrOffset), VPSS_CTRL.u32);

    return ;
}





HI_VOID VPSS_Sys_SetVhd0LbaEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_lba_en)
{
    U_VPSS_CTRL3 VPSS_CTRL3;

    VPSS_CTRL3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL3.u32) + u32AddrOffset));
    VPSS_CTRL3.bits.vhd0_lba_en = vhd0_lba_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL3.u32) + u32AddrOffset), VPSS_CTRL3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0CropEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_crop_en)
{
    U_VPSS_CTRL3 VPSS_CTRL3;

    VPSS_CTRL3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL3.u32) + u32AddrOffset));
    VPSS_CTRL3.bits.vhd0_crop_en = vhd0_crop_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL3.u32) + u32AddrOffset), VPSS_CTRL3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0PreVfirEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_pre_vfir_en)
{
    U_VPSS_CTRL3 VPSS_CTRL3;

    VPSS_CTRL3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL3.u32) + u32AddrOffset));
    VPSS_CTRL3.bits.vhd0_pre_vfir_en = vhd0_pre_vfir_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL3.u32) + u32AddrOffset), VPSS_CTRL3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetZmeVhd0En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 zme_vhd0_en)
{
    U_VPSS_CTRL3 VPSS_CTRL3;

    VPSS_CTRL3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CTRL3.u32) + u32AddrOffset));
    VPSS_CTRL3.bits.zme_vhd0_en = zme_vhd0_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CTRL3.u32) + u32AddrOffset), VPSS_CTRL3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCmdCntRdChn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmd_cnt_rd_chn)
{
    U_VPSS_CMD_CNT_CHN VPSS_CMD_CNT_CHN;

    VPSS_CMD_CNT_CHN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CMD_CNT_CHN.u32) + u32AddrOffset));
    VPSS_CMD_CNT_CHN.bits.cmd_cnt_rd_chn = cmd_cnt_rd_chn;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CMD_CNT_CHN.u32) + u32AddrOffset), VPSS_CMD_CNT_CHN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCmdlenCntRdChn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmdlen_cnt_rd_chn)
{
    U_VPSS_CMD_CNT_CHN VPSS_CMD_CNT_CHN;

    VPSS_CMD_CNT_CHN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CMD_CNT_CHN.u32) + u32AddrOffset));
    VPSS_CMD_CNT_CHN.bits.cmdlen_cnt_rd_chn = cmdlen_cnt_rd_chn;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CMD_CNT_CHN.u32) + u32AddrOffset), VPSS_CMD_CNT_CHN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCmdCntWrChn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmd_cnt_wr_chn)
{
    U_VPSS_CMD_CNT_CHN VPSS_CMD_CNT_CHN;

    VPSS_CMD_CNT_CHN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CMD_CNT_CHN.u32) + u32AddrOffset));
    VPSS_CMD_CNT_CHN.bits.cmd_cnt_wr_chn = cmd_cnt_wr_chn;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CMD_CNT_CHN.u32) + u32AddrOffset), VPSS_CMD_CNT_CHN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCmdlenCntWrChn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmdlen_cnt_wr_chn)
{
    U_VPSS_CMD_CNT_CHN VPSS_CMD_CNT_CHN;

    VPSS_CMD_CNT_CHN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_CMD_CNT_CHN.u32) + u32AddrOffset));
    VPSS_CMD_CNT_CHN.bits.cmdlen_cnt_wr_chn = cmdlen_cnt_wr_chn;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_CMD_CNT_CHN.u32) + u32AddrOffset), VPSS_CMD_CNT_CHN.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRchTransrBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_transr_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_transr_bypass = rch_transr_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchNx2cTile2bitBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_nx2c_tile_2bit_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_nx2c_tile_2bit_bypass = rch_nx2c_tile_2bit_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchNx2yTile2bitBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_nx2y_tile_2bit_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_nx2y_tile_2bit_bypass = rch_nx2y_tile_2bit_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchNx2cHeadBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_nx2c_head_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_nx2c_head_bypass = rch_nx2c_head_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchNx2yHeadBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_nx2y_head_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_nx2y_head_bypass = rch_nx2y_head_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchTunlBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_tunl_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_tunl_bypass = rch_tunl_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchReecBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_reec_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_reec_bypass = rch_reec_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchReeyBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_reey_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_reey_bypass = rch_reey_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchRgmvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_rgmv_cur_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_rgmv_cur_bypass = rch_rgmv_cur_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchRgmvNx1Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_rgmv_nx1_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_rgmv_nx1_bypass = rch_rgmv_nx1_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchPrjvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_prjv_cur_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_prjv_cur_bypass = rch_prjv_cur_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchBlkmvRefBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_blkmv_ref_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_blkmv_ref_bypass = rch_blkmv_ref_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchBlkmvCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_blkmv_cur_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_blkmv_cur_bypass = rch_blkmv_cur_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchBlkmvNx1Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_blkmv_nx1_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_blkmv_nx1_bypass = rch_blkmv_nx1_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchPrjhCurBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_prjh_cur_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_prjh_cur_bypass = rch_prjh_cur_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchRstBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_rst_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_rst_bypass = rch_rst_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchSrmdBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_srmd_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_srmd_bypass = rch_srmd_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchTrmdBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_trmd_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_trmd_bypass = rch_trmd_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchNx2cBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_nx2c_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_nx2c_bypass = rch_nx2c_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchNx2yBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_nx2y_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_nx2y_bypass = rch_nx2y_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchNx1cBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_nx1c_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_nx1c_bypass = rch_nx1c_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchNx1yBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_nx1y_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_nx1y_bypass = rch_nx1y_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchRefcBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_refc_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_refc_bypass = rch_refc_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchRefyBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_refy_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_refy_bypass = rch_refy_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchCurcBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_curc_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_curc_bypass = rch_curc_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRchCuryBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rch_cury_bypass)
{
    U_VPSS_RCH_BYPASS VPSS_RCH_BYPASS;

    VPSS_RCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset));
    VPSS_RCH_BYPASS.bits.rch_cury_bypass = rch_cury_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RCH_BYPASS.u32) + u32AddrOffset), VPSS_RCH_BYPASS.u32);

    return ;
}



HI_VOID VPSS_Sys_SetWchTunlBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_tunl_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_tunl_bypass = wch_tunl_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchTranswBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_transw_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_transw_bypass = wch_transw_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchCuecBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_cuec_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_cuec_bypass = wch_cuec_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchCueyBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_cuey_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_cuey_bypass = wch_cuey_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchRgmvnx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_rgmvnx2_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_rgmvnx2_bypass = wch_rgmvnx2_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchPrjvnx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_prjvnx2_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_prjvnx2_bypass = wch_prjvnx2_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchBlkmvnx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_blkmvnx2_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_blkmvnx2_bypass = wch_blkmvnx2_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchPrjhnx2Bypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_prjhnx2_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_prjhnx2_bypass = wch_prjhnx2_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchSttBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_stt_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_stt_bypass = wch_stt_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchTwmdBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_twmd_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_twmd_bypass = wch_twmd_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchWstBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_wst_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_wst_bypass = wch_wst_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchRfrcBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_rfrc_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_rfrc_bypass = wch_rfrc_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchRfryBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_rfry_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_rfry_bypass = wch_rfry_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchVhd0cBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_vhd0c_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_vhd0c_bypass = wch_vhd0c_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetWchVhd0yBypass(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 wch_vhd0y_bypass)
{
    U_VPSS_WCH_BYPASS VPSS_WCH_BYPASS;

    VPSS_WCH_BYPASS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset));
    VPSS_WCH_BYPASS.bits.wch_vhd0y_bypass = wch_vhd0y_bypass;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_WCH_BYPASS.u32) + u32AddrOffset), VPSS_WCH_BYPASS.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0ZmeOh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_zme_oh)
{
    U_VPSS_VHD0_ZMEORESO VPSS_VHD0_ZMEORESO;

    VPSS_VHD0_ZMEORESO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_ZMEORESO.u32) + u32AddrOffset));
    VPSS_VHD0_ZMEORESO.bits.vhd0_zme_oh = vhd0_zme_oh;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_ZMEORESO.u32) + u32AddrOffset), VPSS_VHD0_ZMEORESO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0ZmeOw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_zme_ow)
{
    U_VPSS_VHD0_ZMEORESO VPSS_VHD0_ZMEORESO;

    VPSS_VHD0_ZMEORESO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_ZMEORESO.u32) + u32AddrOffset));
    VPSS_VHD0_ZMEORESO.bits.vhd0_zme_ow = vhd0_zme_ow;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_ZMEORESO.u32) + u32AddrOffset), VPSS_VHD0_ZMEORESO.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0SclLh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_scl_lh)
{
    U_VPSS_VHD0_ZME_LHADDR VPSS_VHD0_ZME_LHADDR;

    VPSS_VHD0_ZME_LHADDR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_ZME_LHADDR.u32) + u32AddrOffset));
    VPSS_VHD0_ZME_LHADDR.bits.vhd0_scl_lh = vhd0_scl_lh;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_ZME_LHADDR.u32) + u32AddrOffset), VPSS_VHD0_ZME_LHADDR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0SclLv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_scl_lv)
{
    U_VPSS_VHD0_ZME_LVADDR VPSS_VHD0_ZME_LVADDR;

    VPSS_VHD0_ZME_LVADDR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_ZME_LVADDR.u32) + u32AddrOffset));
    VPSS_VHD0_ZME_LVADDR.bits.vhd0_scl_lv = vhd0_scl_lv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_ZME_LVADDR.u32) + u32AddrOffset), VPSS_VHD0_ZME_LVADDR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0SclCh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_scl_ch)
{
    U_VPSS_VHD0_ZME_CHADDR VPSS_VHD0_ZME_CHADDR;

    VPSS_VHD0_ZME_CHADDR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_ZME_CHADDR.u32) + u32AddrOffset));
    VPSS_VHD0_ZME_CHADDR.bits.vhd0_scl_ch = vhd0_scl_ch;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_ZME_CHADDR.u32) + u32AddrOffset), VPSS_VHD0_ZME_CHADDR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0SclCv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_scl_cv)
{
    U_VPSS_VHD0_ZME_CVADDR VPSS_VHD0_ZME_CVADDR;

    VPSS_VHD0_ZME_CVADDR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_ZME_CVADDR.u32) + u32AddrOffset));
    VPSS_VHD0_ZME_CVADDR.bits.vhd0_scl_cv = vhd0_scl_cv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_ZME_CVADDR.u32) + u32AddrOffset), VPSS_VHD0_ZME_CVADDR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetTnrCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 tnr_cfg_addr)
{
    U_VPSS_TNR_ADDR VPSS_TNR_ADDR;

    VPSS_TNR_ADDR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_ADDR.u32) + u32AddrOffset));
    VPSS_TNR_ADDR.bits.tnr_cfg_addr = tnr_cfg_addr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_ADDR.u32) + u32AddrOffset), VPSS_TNR_ADDR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetSnrCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 snr_cfg_addr)
{
    U_VPSS_SNR_ADDR VPSS_SNR_ADDR;

    VPSS_SNR_ADDR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_ADDR.u32) + u32AddrOffset));
    VPSS_SNR_ADDR.bits.snr_cfg_addr = snr_cfg_addr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_ADDR.u32) + u32AddrOffset), VPSS_SNR_ADDR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetZmeCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 zme_cfg_addr)
{
    U_VPSS_ZME_ADDR VPSS_ZME_ADDR;

    VPSS_ZME_ADDR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_ZME_ADDR.u32) + u32AddrOffset));
    VPSS_ZME_ADDR.bits.zme_cfg_addr = zme_cfg_addr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_ZME_ADDR.u32) + u32AddrOffset), VPSS_ZME_ADDR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDeiCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dei_cfg_addr)
{
    U_VPSS_DEI_ADDR VPSS_DEI_ADDR;

    VPSS_DEI_ADDR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEI_ADDR.u32) + u32AddrOffset));
    VPSS_DEI_ADDR.bits.dei_cfg_addr = dei_cfg_addr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEI_ADDR.u32) + u32AddrOffset), VPSS_DEI_ADDR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetHdrCfgAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hdr_cfg_addr)
{
    U_VPSS_HDR_ADDR VPSS_HDR_ADDR;

    VPSS_HDR_ADDR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_HDR_ADDR.u32) + u32AddrOffset));
    VPSS_HDR_ADDR.bits.hdr_cfg_addr = hdr_cfg_addr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_HDR_ADDR.u32) + u32AddrOffset), VPSS_HDR_ADDR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetNodeid(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 nodeid)
{
    U_VPSS_NODEID VPSS_NODEID;

    VPSS_NODEID.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_NODEID.u32) + u32AddrOffset));
    VPSS_NODEID.bits.nodeid = nodeid;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_NODEID.u32) + u32AddrOffset), VPSS_NODEID.u32);

    return ;
}



HI_VOID VPSS_Sys_SetPNext(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 p_next)
{
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PNEXT.u32) + u32AddrOffset), p_next);

    return ;
}



HI_VOID VPSS_Sys_SetStart(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 start)
{
    U_VPSS_START VPSS_START;

    VPSS_START.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_START.u32) + u32AddrOffset));
    VPSS_START.bits.start = start;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_START.u32) + u32AddrOffset), VPSS_START.u32);

    return ;
}



HI_VOID VPSS_Sys_SetBusRErrState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bus_r_err_state)
{
    U_VPSS_INTSTATE VPSS_INTSTATE;

    VPSS_INTSTATE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset));
    VPSS_INTSTATE.bits.bus_r_err_state = bus_r_err_state;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset), VPSS_INTSTATE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDcmpErrState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dcmp_err_state)
{
    U_VPSS_INTSTATE VPSS_INTSTATE;

    VPSS_INTSTATE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset));
    VPSS_INTSTATE.bits.dcmp_err_state = dcmp_err_state;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset), VPSS_INTSTATE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0TunlState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_tunl_state)
{
    U_VPSS_INTSTATE VPSS_INTSTATE;

    VPSS_INTSTATE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset));
    VPSS_INTSTATE.bits.vhd0_tunl_state = vhd0_tunl_state;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset), VPSS_INTSTATE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEofEndState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 eof_end_state)
{
    U_VPSS_INTSTATE VPSS_INTSTATE;

    VPSS_INTSTATE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset));
    VPSS_INTSTATE.bits.eof_end_state = eof_end_state;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset), VPSS_INTSTATE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBusWErrState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bus_w_err_state)
{
    U_VPSS_INTSTATE VPSS_INTSTATE;

    VPSS_INTSTATE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset));
    VPSS_INTSTATE.bits.bus_w_err_state = bus_w_err_state;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset), VPSS_INTSTATE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetTimeoutState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 timeout_state)
{
    U_VPSS_INTSTATE VPSS_INTSTATE;

    VPSS_INTSTATE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset));
    VPSS_INTSTATE.bits.timeout_state = timeout_state;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset), VPSS_INTSTATE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEofState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 eof_state)
{
    U_VPSS_INTSTATE VPSS_INTSTATE;

    VPSS_INTSTATE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset));
    VPSS_INTSTATE.bits.eof_state = eof_state;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTSTATE.u32) + u32AddrOffset), VPSS_INTSTATE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetBusRErrClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bus_r_err_clr)
{
    U_VPSS_INTCLR VPSS_INTCLR;

    VPSS_INTCLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset));
    VPSS_INTCLR.bits.bus_r_err_clr = bus_r_err_clr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset), VPSS_INTCLR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDcmpErrClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dcmp_err_clr)
{
    U_VPSS_INTCLR VPSS_INTCLR;

    VPSS_INTCLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset));
    VPSS_INTCLR.bits.dcmp_err_clr = dcmp_err_clr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset), VPSS_INTCLR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0TunlClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_tunl_clr)
{
    U_VPSS_INTCLR VPSS_INTCLR;

    VPSS_INTCLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset));
    VPSS_INTCLR.bits.vhd0_tunl_clr = vhd0_tunl_clr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset), VPSS_INTCLR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEofEndClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 eof_end_clr)
{
    U_VPSS_INTCLR VPSS_INTCLR;

    VPSS_INTCLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset));
    VPSS_INTCLR.bits.eof_end_clr = eof_end_clr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset), VPSS_INTCLR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBusWErrClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bus_w_err_clr)
{
    U_VPSS_INTCLR VPSS_INTCLR;

    VPSS_INTCLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset));
    VPSS_INTCLR.bits.bus_w_err_clr = bus_w_err_clr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset), VPSS_INTCLR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetTimeoutClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 timeout_clr)
{
    U_VPSS_INTCLR VPSS_INTCLR;

    VPSS_INTCLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset));
    VPSS_INTCLR.bits.timeout_clr = timeout_clr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset), VPSS_INTCLR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEofClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 eof_clr)
{
    U_VPSS_INTCLR VPSS_INTCLR;

    VPSS_INTCLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset));
    VPSS_INTCLR.bits.eof_clr = eof_clr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTCLR.u32) + u32AddrOffset), VPSS_INTCLR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRawBusRErr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 raw_bus_r_err)
{
    U_VPSS_RAWINT VPSS_RAWINT;

    VPSS_RAWINT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset));
    VPSS_RAWINT.bits.raw_bus_r_err = raw_bus_r_err;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset), VPSS_RAWINT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRawDcmpErr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 raw_dcmp_err)
{
    U_VPSS_RAWINT VPSS_RAWINT;

    VPSS_RAWINT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset));
    VPSS_RAWINT.bits.raw_dcmp_err = raw_dcmp_err;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset), VPSS_RAWINT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRawVhd0Tunl(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 raw_vhd0_tunl)
{
    U_VPSS_RAWINT VPSS_RAWINT;

    VPSS_RAWINT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset));
    VPSS_RAWINT.bits.raw_vhd0_tunl = raw_vhd0_tunl;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset), VPSS_RAWINT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRawEofEnd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 raw_eof_end)
{
    U_VPSS_RAWINT VPSS_RAWINT;

    VPSS_RAWINT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset));
    VPSS_RAWINT.bits.raw_eof_end = raw_eof_end;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset), VPSS_RAWINT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRawBusWErr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 raw_bus_w_err)
{
    U_VPSS_RAWINT VPSS_RAWINT;

    VPSS_RAWINT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset));
    VPSS_RAWINT.bits.raw_bus_w_err = raw_bus_w_err;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset), VPSS_RAWINT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRawTimeout(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 raw_timeout)
{
    U_VPSS_RAWINT VPSS_RAWINT;

    VPSS_RAWINT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset));
    VPSS_RAWINT.bits.raw_timeout = raw_timeout;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset), VPSS_RAWINT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRawEof(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 raw_eof)
{
    U_VPSS_RAWINT VPSS_RAWINT;

    VPSS_RAWINT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset));
    VPSS_RAWINT.bits.raw_eof = raw_eof;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RAWINT.u32) + u32AddrOffset), VPSS_RAWINT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetPfcnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 pfcnt)
{
    U_VPSS_PFCNT VPSS_PFCNT;

    VPSS_PFCNT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PFCNT.u32) + u32AddrOffset));
    VPSS_PFCNT.bits.pfcnt = pfcnt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PFCNT.u32) + u32AddrOffset), VPSS_PFCNT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetTimeout(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 timeout)
{
    U_VPSS_TIMEOUT VPSS_TIMEOUT;

    VPSS_TIMEOUT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TIMEOUT.u32) + u32AddrOffset));
    VPSS_TIMEOUT.bits.timeout = timeout;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TIMEOUT.u32) + u32AddrOffset), VPSS_TIMEOUT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetNodeRstEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 node_rst_en)
{
    U_VPSS_FTCONFIG VPSS_FTCONFIG;

    VPSS_FTCONFIG.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_FTCONFIG.u32) + u32AddrOffset));
    VPSS_FTCONFIG.bits.node_rst_en = node_rst_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_FTCONFIG.u32) + u32AddrOffset), VPSS_FTCONFIG.u32);

    return ;
}



HI_VOID VPSS_Sys_SetBusRErrMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bus_r_err_mask)
{
    U_VPSS_INTMASK VPSS_INTMASK;

    VPSS_INTMASK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset));
    VPSS_INTMASK.bits.bus_r_err_mask = bus_r_err_mask;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset), VPSS_INTMASK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDcmpErrMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dcmp_err_mask)
{
    U_VPSS_INTMASK VPSS_INTMASK;

    VPSS_INTMASK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset));
    VPSS_INTMASK.bits.dcmp_err_mask = dcmp_err_mask;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset), VPSS_INTMASK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0TunlMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_tunl_mask)
{
    U_VPSS_INTMASK VPSS_INTMASK;

    VPSS_INTMASK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset));
    VPSS_INTMASK.bits.vhd0_tunl_mask = vhd0_tunl_mask;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset), VPSS_INTMASK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEofEndMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 eof_end_mask)
{
    U_VPSS_INTMASK VPSS_INTMASK;

    VPSS_INTMASK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset));
    VPSS_INTMASK.bits.eof_end_mask = eof_end_mask;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset), VPSS_INTMASK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBusWErrMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bus_w_err_mask)
{
    U_VPSS_INTMASK VPSS_INTMASK;

    VPSS_INTMASK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset));
    VPSS_INTMASK.bits.bus_w_err_mask = bus_w_err_mask;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset), VPSS_INTMASK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetTimeoutMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 timeout_mask)
{
    U_VPSS_INTMASK VPSS_INTMASK;

    VPSS_INTMASK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset));
    VPSS_INTMASK.bits.timeout_mask = timeout_mask;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset), VPSS_INTMASK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEofMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 eof_mask)
{
    U_VPSS_INTMASK VPSS_INTMASK;

    VPSS_INTMASK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset));
    VPSS_INTMASK.bits.eof_mask = eof_mask;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_INTMASK.u32) + u32AddrOffset), VPSS_INTMASK.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEofCnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 eof_cnt)
{
    U_VPSS_EOFCNT VPSS_EOFCNT;

    VPSS_EOFCNT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_EOFCNT.u32) + u32AddrOffset));
    VPSS_EOFCNT.bits.eof_cnt = eof_cnt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_EOFCNT.u32) + u32AddrOffset), VPSS_EOFCNT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVersion(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 version)
{
    U_VPSS_VERSION VPSS_VERSION;

    VPSS_VERSION.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VERSION.u32) + u32AddrOffset));
    VPSS_VERSION.bits.version = version;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VERSION.u32) + u32AddrOffset), VPSS_VERSION.u32);

    return ;
}

HI_VOID VPSS_Sys_SetCkGtEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ck_gt_en)
{
    U_VPSS_LOWPOWER_CTRL VPSS_LOWPOWER_CTRL;
    VPSS_LOWPOWER_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_LOWPOWER_CTRL.u32) + u32AddrOffset));
    VPSS_LOWPOWER_CTRL.bits.ck_gt_en = ck_gt_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_LOWPOWER_CTRL.u32) + u32AddrOffset), VPSS_LOWPOWER_CTRL.u32);
    return ;
}

HI_VOID VPSS_Sys_SetHardCkGtEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hard_gate_clk_ppc_en, HI_U32 hard_gate_clk_axi_en)
{
    U_VPSS_HARDGATE_CTRL VPSS_HARDGATE_CTRL;
    VPSS_HARDGATE_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_HARDGATE_CTRL.u32) + u32AddrOffset));
    VPSS_HARDGATE_CTRL.bits.hard_gate_clk_ppc_en = hard_gate_clk_ppc_en;
    VPSS_HARDGATE_CTRL.bits.hard_gate_clk_axi_en = hard_gate_clk_axi_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_HARDGATE_CTRL.u32) + u32AddrOffset), VPSS_HARDGATE_CTRL.u32);
    return ;
}

#if 0
HI_VOID VPSS_Sys_SetVhd0PreVfirMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_pre_vfir_mode)
{
    U_VPSS_VPZME_CFG0 VPSS_VPZME_CFG0;

    VPSS_VPZME_CFG0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VPZME_CFG0.u32) + u32AddrOffset));
    VPSS_VPZME_CFG0.bits.vhd0_pre_vfir_mode = vhd0_pre_vfir_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VPZME_CFG0.u32) + u32AddrOffset), VPSS_VPZME_CFG0.u32);

    return ;
}

HI_VOID VPSS_Sys_SetRotateAngle(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rotate_angle)
{
    U_VPSS_RTT_CFG VPSS_RTT_CFG;

    VPSS_RTT_CFG.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_RTT_CFG.u32) + u32AddrOffset));
    VPSS_RTT_CFG.bits.rotate_angle = rotate_angle;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_RTT_CFG.u32) + u32AddrOffset), VPSS_RTT_CFG.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0CropHeight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_crop_height)
{
    U_VPSS_VHD0CROP_SIZE VPSS_VHD0CROP_SIZE;

    VPSS_VHD0CROP_SIZE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0CROP_SIZE.u32) + u32AddrOffset));
    VPSS_VHD0CROP_SIZE.bits.vhd0_crop_height = vhd0_crop_height;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0CROP_SIZE.u32) + u32AddrOffset), VPSS_VHD0CROP_SIZE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0CropWidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_crop_width)
{
    U_VPSS_VHD0CROP_SIZE VPSS_VHD0CROP_SIZE;

    VPSS_VHD0CROP_SIZE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0CROP_SIZE.u32) + u32AddrOffset));
    VPSS_VHD0CROP_SIZE.bits.vhd0_crop_width = vhd0_crop_width;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0CROP_SIZE.u32) + u32AddrOffset), VPSS_VHD0CROP_SIZE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0CropY(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_crop_y)
{
    U_VPSS_VHD0CROP_POS VPSS_VHD0CROP_POS;

    VPSS_VHD0CROP_POS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0CROP_POS.u32) + u32AddrOffset));
    VPSS_VHD0CROP_POS.bits.vhd0_crop_y = vhd0_crop_y;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0CROP_POS.u32) + u32AddrOffset), VPSS_VHD0CROP_POS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0CropX(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_crop_x)
{
    U_VPSS_VHD0CROP_POS VPSS_VHD0CROP_POS;

    VPSS_VHD0CROP_POS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0CROP_POS.u32) + u32AddrOffset));
    VPSS_VHD0CROP_POS.bits.vhd0_crop_x = vhd0_crop_x;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0CROP_POS.u32) + u32AddrOffset), VPSS_VHD0CROP_POS.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0LbaHeight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_lba_height)
{
    U_VPSS_VHD0LBA_DSIZE VPSS_VHD0LBA_DSIZE;

    VPSS_VHD0LBA_DSIZE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0LBA_DSIZE.u32) + u32AddrOffset));
    VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_height = vhd0_lba_height;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0LBA_DSIZE.u32) + u32AddrOffset), VPSS_VHD0LBA_DSIZE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0LbaWidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_lba_width)
{
    U_VPSS_VHD0LBA_DSIZE VPSS_VHD0LBA_DSIZE;

    VPSS_VHD0LBA_DSIZE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0LBA_DSIZE.u32) + u32AddrOffset));
    VPSS_VHD0LBA_DSIZE.bits.vhd0_lba_width = vhd0_lba_width;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0LBA_DSIZE.u32) + u32AddrOffset), VPSS_VHD0LBA_DSIZE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0LbaYfpos(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_lba_yfpos)
{
    U_VPSS_VHD0LBA_VFPOS VPSS_VHD0LBA_VFPOS;

    VPSS_VHD0LBA_VFPOS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0LBA_VFPOS.u32) + u32AddrOffset));
    VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_yfpos = vhd0_lba_yfpos;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0LBA_VFPOS.u32) + u32AddrOffset), VPSS_VHD0LBA_VFPOS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0LbaXfpos(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_lba_xfpos)
{
    U_VPSS_VHD0LBA_VFPOS VPSS_VHD0LBA_VFPOS;

    VPSS_VHD0LBA_VFPOS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0LBA_VFPOS.u32) + u32AddrOffset));
    VPSS_VHD0LBA_VFPOS.bits.vhd0_lba_xfpos = vhd0_lba_xfpos;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0LBA_VFPOS.u32) + u32AddrOffset), VPSS_VHD0LBA_VFPOS.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVhd0VbkCr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_vbk_cr)
{
    U_VPSS_VHD0LBA_BK VPSS_VHD0LBA_BK;

    VPSS_VHD0LBA_BK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0LBA_BK.u32) + u32AddrOffset));
    VPSS_VHD0LBA_BK.bits.vhd0_vbk_cr = vhd0_vbk_cr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0LBA_BK.u32) + u32AddrOffset), VPSS_VHD0LBA_BK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0VbkCb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_vbk_cb)
{
    U_VPSS_VHD0LBA_BK VPSS_VHD0LBA_BK;

    VPSS_VHD0LBA_BK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0LBA_BK.u32) + u32AddrOffset));
    VPSS_VHD0LBA_BK.bits.vhd0_vbk_cb = vhd0_vbk_cb;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0LBA_BK.u32) + u32AddrOffset), VPSS_VHD0LBA_BK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVhd0VbkY(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vhd0_vbk_y)
{
    U_VPSS_VHD0LBA_BK VPSS_VHD0LBA_BK;

    VPSS_VHD0LBA_BK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0LBA_BK.u32) + u32AddrOffset));
    VPSS_VHD0LBA_BK.bits.vhd0_vbk_y = vhd0_vbk_y;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0LBA_BK.u32) + u32AddrOffset), VPSS_VHD0LBA_BK.u32);

    return ;
}

HI_VOID VPSS_Sys_SetDieOutSelL(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 die_out_sel_l)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.die_out_sel_l = die_out_sel_l;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDieOutSelC(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 die_out_sel_c)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.die_out_sel_c = die_out_sel_c;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDieLMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 die_l_mode)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.die_l_mode = die_l_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDieCMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 die_c_mode)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.die_c_mode = die_c_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetTwoFourPxlShare(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 two_four_pxl_share)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.two_four_pxl_share = two_four_pxl_share;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcOnly(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_only)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.mc_only = mc_only;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMaOnly(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ma_only)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.ma_only = ma_only;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeSmoothEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_smooth_en)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.edge_smooth_en = edge_smooth_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMchdirL(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mchdir_l)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.mchdir_l = mchdir_l;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMchdirC(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mchdir_c)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.mchdir_c = mchdir_c;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDieRst(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 die_rst)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.die_rst = die_rst;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStinfoStop(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 stinfo_stop)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.stinfo_stop = stinfo_stop;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeSmoothRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_smooth_ratio)
{
    U_VPSS_DIECTRL VPSS_DIECTRL;

    VPSS_DIECTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset));
    VPSS_DIECTRL.bits.edge_smooth_ratio = edge_smooth_ratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECTRL.u32) + u32AddrOffset), VPSS_DIECTRL.u32);

    return ;
}



HI_VOID VPSS_Sys_SetChromaMfOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 chroma_mf_offset)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset));
    VPSS_DIELMA2.bits.chroma_mf_offset = chroma_mf_offset;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDeiStRstValue(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dei_st_rst_value)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset));
    VPSS_DIELMA2.bits.dei_st_rst_value = dei_st_rst_value;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRecModeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rec_mode_en)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset));
    VPSS_DIELMA2.bits.rec_mode_en = rec_mode_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetChromaMfMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 chroma_mf_max)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset));
    VPSS_DIELMA2.bits.chroma_mf_max = chroma_mf_max;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLumaMfMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 luma_mf_max)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset));
    VPSS_DIELMA2.bits.luma_mf_max = luma_mf_max;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionIirEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_en)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset));
    VPSS_DIELMA2.bits.motion_iir_en = motion_iir_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLumaScesdfMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 luma_scesdf_max)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset));
    VPSS_DIELMA2.bits.luma_scesdf_max = luma_scesdf_max;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_en)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset));
    VPSS_DIELMA2.bits.frame_motion_smooth_en = frame_motion_smooth_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset), VPSS_DIELMA2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRecmodeFrmfldBlendMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 recmode_frmfld_blend_mode)
{
    U_VPSS_DIELMA2 VPSS_DIELMA2;

    VPSS_DIELMA2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset));
    VPSS_DIELMA2.bits.recmode_frmfld_blend_mode = recmode_frmfld_blend_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIELMA2.u32) + u32AddrOffset), VPSS_DIELMA2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMinNorthStrength(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 min_north_strength)
{
    U_VPSS_DIEINTEN VPSS_DIEINTEN;

    VPSS_DIEINTEN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTEN.u32) + u32AddrOffset));
    VPSS_DIEINTEN.bits.min_north_strength = min_north_strength;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTEN.u32) + u32AddrOffset), VPSS_DIEINTEN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDirRatioNorth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir_ratio_north)
{
    U_VPSS_DIEINTEN VPSS_DIEINTEN;

    VPSS_DIEINTEN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTEN.u32) + u32AddrOffset));
    VPSS_DIEINTEN.bits.dir_ratio_north = dir_ratio_north;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTEN.u32) + u32AddrOffset), VPSS_DIEINTEN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRecModeOutputMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rec_mode_output_mode)
{
    U_VPSS_DIEINTEN VPSS_DIEINTEN;

    VPSS_DIEINTEN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTEN.u32) + u32AddrOffset));
    VPSS_DIEINTEN.bits.rec_mode_output_mode = rec_mode_output_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTEN.u32) + u32AddrOffset), VPSS_DIEINTEN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRecModeSetPreInfoMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rec_mode_set_pre_info_mode)
{
    U_VPSS_DIEINTEN VPSS_DIEINTEN;

    VPSS_DIEINTEN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTEN.u32) + u32AddrOffset));
    VPSS_DIEINTEN.bits.rec_mode_set_pre_info_mode = rec_mode_set_pre_info_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTEN.u32) + u32AddrOffset), VPSS_DIEINTEN.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRangeScale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 range_scale)
{
    U_VPSS_DIESCALE VPSS_DIESCALE;

    VPSS_DIESCALE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIESCALE.u32) + u32AddrOffset));
    VPSS_DIESCALE.bits.range_scale = range_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIESCALE.u32) + u32AddrOffset), VPSS_DIESCALE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetBc1Gain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bc1_gain)
{
    U_VPSS_DIECHECK1 VPSS_DIECHECK1;

    VPSS_DIECHECK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECHECK1.u32) + u32AddrOffset));
    VPSS_DIECHECK1.bits.bc1_gain = bc1_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECHECK1.u32) + u32AddrOffset), VPSS_DIECHECK1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBc1AutodzGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bc1_autodz_gain)
{
    U_VPSS_DIECHECK1 VPSS_DIECHECK1;

    VPSS_DIECHECK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECHECK1.u32) + u32AddrOffset));
    VPSS_DIECHECK1.bits.bc1_autodz_gain = bc1_autodz_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECHECK1.u32) + u32AddrOffset), VPSS_DIECHECK1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBc1MaxDz(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bc1_max_dz)
{
    U_VPSS_DIECHECK1 VPSS_DIECHECK1;

    VPSS_DIECHECK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECHECK1.u32) + u32AddrOffset));
    VPSS_DIECHECK1.bits.bc1_max_dz = bc1_max_dz;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECHECK1.u32) + u32AddrOffset), VPSS_DIECHECK1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetBc2Gain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bc2_gain)
{
    U_VPSS_DIECHECK2 VPSS_DIECHECK2;

    VPSS_DIECHECK2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECHECK2.u32) + u32AddrOffset));
    VPSS_DIECHECK2.bits.bc2_gain = bc2_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECHECK2.u32) + u32AddrOffset), VPSS_DIECHECK2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBc2AutodzGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bc2_autodz_gain)
{
    U_VPSS_DIECHECK2 VPSS_DIECHECK2;

    VPSS_DIECHECK2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECHECK2.u32) + u32AddrOffset));
    VPSS_DIECHECK2.bits.bc2_autodz_gain = bc2_autodz_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECHECK2.u32) + u32AddrOffset), VPSS_DIECHECK2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBc2MaxDz(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bc2_max_dz)
{
    U_VPSS_DIECHECK2 VPSS_DIECHECK2;

    VPSS_DIECHECK2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECHECK2.u32) + u32AddrOffset));
    VPSS_DIECHECK2.bits.bc2_max_dz = bc2_max_dz;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECHECK2.u32) + u32AddrOffset), VPSS_DIECHECK2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDir3Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir3_scale)
{
    U_VPSS_DIEDIR0_3 VPSS_DIEDIR0_3;

    VPSS_DIEDIR0_3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR0_3.u32) + u32AddrOffset));
    VPSS_DIEDIR0_3.bits.dir3_scale = dir3_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR0_3.u32) + u32AddrOffset), VPSS_DIEDIR0_3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir2Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir2_scale)
{
    U_VPSS_DIEDIR0_3 VPSS_DIEDIR0_3;

    VPSS_DIEDIR0_3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR0_3.u32) + u32AddrOffset));
    VPSS_DIEDIR0_3.bits.dir2_scale = dir2_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR0_3.u32) + u32AddrOffset), VPSS_DIEDIR0_3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir1Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir1_scale)
{
    U_VPSS_DIEDIR0_3 VPSS_DIEDIR0_3;

    VPSS_DIEDIR0_3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR0_3.u32) + u32AddrOffset));
    VPSS_DIEDIR0_3.bits.dir1_scale = dir1_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR0_3.u32) + u32AddrOffset), VPSS_DIEDIR0_3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir0Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir0_scale)
{
    U_VPSS_DIEDIR0_3 VPSS_DIEDIR0_3;

    VPSS_DIEDIR0_3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR0_3.u32) + u32AddrOffset));
    VPSS_DIEDIR0_3.bits.dir0_scale = dir0_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR0_3.u32) + u32AddrOffset), VPSS_DIEDIR0_3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDir7Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir7_scale)
{
    U_VPSS_DIEDIR4_7 VPSS_DIEDIR4_7;

    VPSS_DIEDIR4_7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR4_7.u32) + u32AddrOffset));
    VPSS_DIEDIR4_7.bits.dir7_scale = dir7_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR4_7.u32) + u32AddrOffset), VPSS_DIEDIR4_7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir6Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir6_scale)
{
    U_VPSS_DIEDIR4_7 VPSS_DIEDIR4_7;

    VPSS_DIEDIR4_7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR4_7.u32) + u32AddrOffset));
    VPSS_DIEDIR4_7.bits.dir6_scale = dir6_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR4_7.u32) + u32AddrOffset), VPSS_DIEDIR4_7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir5Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir5_scale)
{
    U_VPSS_DIEDIR4_7 VPSS_DIEDIR4_7;

    VPSS_DIEDIR4_7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR4_7.u32) + u32AddrOffset));
    VPSS_DIEDIR4_7.bits.dir5_scale = dir5_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR4_7.u32) + u32AddrOffset), VPSS_DIEDIR4_7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir4Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir4_scale)
{
    U_VPSS_DIEDIR4_7 VPSS_DIEDIR4_7;

    VPSS_DIEDIR4_7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR4_7.u32) + u32AddrOffset));
    VPSS_DIEDIR4_7.bits.dir4_scale = dir4_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR4_7.u32) + u32AddrOffset), VPSS_DIEDIR4_7.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDir11Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir11_scale)
{
    U_VPSS_DIEDIR8_11 VPSS_DIEDIR8_11;

    VPSS_DIEDIR8_11.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR8_11.u32) + u32AddrOffset));
    VPSS_DIEDIR8_11.bits.dir11_scale = dir11_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR8_11.u32) + u32AddrOffset), VPSS_DIEDIR8_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir10Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir10_scale)
{
    U_VPSS_DIEDIR8_11 VPSS_DIEDIR8_11;

    VPSS_DIEDIR8_11.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR8_11.u32) + u32AddrOffset));
    VPSS_DIEDIR8_11.bits.dir10_scale = dir10_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR8_11.u32) + u32AddrOffset), VPSS_DIEDIR8_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir9Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir9_scale)
{
    U_VPSS_DIEDIR8_11 VPSS_DIEDIR8_11;

    VPSS_DIEDIR8_11.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR8_11.u32) + u32AddrOffset));
    VPSS_DIEDIR8_11.bits.dir9_scale = dir9_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR8_11.u32) + u32AddrOffset), VPSS_DIEDIR8_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir8Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir8_scale)
{
    U_VPSS_DIEDIR8_11 VPSS_DIEDIR8_11;

    VPSS_DIEDIR8_11.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR8_11.u32) + u32AddrOffset));
    VPSS_DIEDIR8_11.bits.dir8_scale = dir8_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR8_11.u32) + u32AddrOffset), VPSS_DIEDIR8_11.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDir14Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir14_scale)
{
    U_VPSS_DIEDIR12_14 VPSS_DIEDIR12_14;

    VPSS_DIEDIR12_14.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR12_14.u32) + u32AddrOffset));
    VPSS_DIEDIR12_14.bits.dir14_scale = dir14_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR12_14.u32) + u32AddrOffset), VPSS_DIEDIR12_14.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir13Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir13_scale)
{
    U_VPSS_DIEDIR12_14 VPSS_DIEDIR12_14;

    VPSS_DIEDIR12_14.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR12_14.u32) + u32AddrOffset));
    VPSS_DIEDIR12_14.bits.dir13_scale = dir13_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR12_14.u32) + u32AddrOffset), VPSS_DIEDIR12_14.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDir12Scale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir12_scale)
{
    U_VPSS_DIEDIR12_14 VPSS_DIEDIR12_14;

    VPSS_DIEDIR12_14.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIR12_14.u32) + u32AddrOffset));
    VPSS_DIEDIR12_14.bits.dir12_scale = dir12_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIR12_14.u32) + u32AddrOffset), VPSS_DIEDIR12_14.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCHeightCnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 c_height_cnt)
{
    U_VPSS_DIESTA VPSS_DIESTA;

    VPSS_DIESTA.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIESTA.u32) + u32AddrOffset));
    VPSS_DIESTA.bits.c_height_cnt = c_height_cnt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIESTA.u32) + u32AddrOffset), VPSS_DIESTA.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLHeightCnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 l_height_cnt)
{
    U_VPSS_DIESTA VPSS_DIESTA;

    VPSS_DIESTA.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIESTA.u32) + u32AddrOffset));
    VPSS_DIESTA.bits.l_height_cnt = l_height_cnt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIESTA.u32) + u32AddrOffset), VPSS_DIESTA.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCurCstate(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cur_cstate)
{
    U_VPSS_DIESTA VPSS_DIESTA;

    VPSS_DIESTA.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIESTA.u32) + u32AddrOffset));
    VPSS_DIESTA.bits.cur_cstate = cur_cstate;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIESTA.u32) + u32AddrOffset), VPSS_DIESTA.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCurState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cur_state)
{
    U_VPSS_DIESTA VPSS_DIESTA;

    VPSS_DIESTA.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIESTA.u32) + u32AddrOffset));
    VPSS_DIESTA.bits.cur_state = cur_state;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIESTA.u32) + u32AddrOffset), VPSS_DIESTA.u32);

    return ;
}



HI_VOID VPSS_Sys_SetIntpScaleRatio8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_8)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_8 = intp_scale_ratio_8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_7)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_7 = intp_scale_ratio_7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_6)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_6 = intp_scale_ratio_6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_5)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_5 = intp_scale_ratio_5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_4)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_4 = intp_scale_ratio_4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_3)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_3 = intp_scale_ratio_3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_2)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_2 = intp_scale_ratio_2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset), VPSS_DIEINTPSCL0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_1)
{
    U_VPSS_DIEINTPSCL0 VPSS_DIEINTPSCL0;

    VPSS_DIEINTPSCL0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL0.bits.intp_scale_ratio_1 = intp_scale_ratio_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL0.u32) + u32AddrOffset), VPSS_DIEINTPSCL0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetIntpScaleRatio15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_15)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_15 = intp_scale_ratio_15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_14)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_14 = intp_scale_ratio_14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_13)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_13 = intp_scale_ratio_13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_12)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_12 = intp_scale_ratio_12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_11)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_11 = intp_scale_ratio_11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_10)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_10 = intp_scale_ratio_10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset), VPSS_DIEINTPSCL1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetIntpScaleRatio9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 intp_scale_ratio_9)
{
    U_VPSS_DIEINTPSCL1 VPSS_DIEINTPSCL1;

    VPSS_DIEINTPSCL1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset));
    VPSS_DIEINTPSCL1.bits.intp_scale_ratio_9 = intp_scale_ratio_9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEINTPSCL1.u32) + u32AddrOffset), VPSS_DIEINTPSCL1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetStrengthThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 strength_thd)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset));
    VPSS_DIEDIRTHD.bits.strength_thd = strength_thd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset), VPSS_DIEDIRTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHorEdgeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hor_edge_en)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset));
    VPSS_DIEDIRTHD.bits.hor_edge_en = hor_edge_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset), VPSS_DIEDIRTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_mode)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset));
    VPSS_DIEDIRTHD.bits.edge_mode = edge_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset), VPSS_DIEDIRTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDirThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir_thd)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset));
    VPSS_DIEDIRTHD.bits.dir_thd = dir_thd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset), VPSS_DIEDIRTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBcGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bc_gain)
{
    U_VPSS_DIEDIRTHD VPSS_DIEDIRTHD;

    VPSS_DIEDIRTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset));
    VPSS_DIEDIRTHD.bits.bc_gain = bc_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEDIRTHD.u32) + u32AddrOffset), VPSS_DIEDIRTHD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFldMotionCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 fld_motion_coring)
{
    U_VPSS_DIEJITMTN VPSS_DIEJITMTN;

    VPSS_DIEJITMTN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEJITMTN.u32) + u32AddrOffset));
    VPSS_DIEJITMTN.bits.fld_motion_coring = fld_motion_coring;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEJITMTN.u32) + u32AddrOffset), VPSS_DIEJITMTN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetJitterCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 jitter_coring)
{
    U_VPSS_DIEJITMTN VPSS_DIEJITMTN;

    VPSS_DIEJITMTN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEJITMTN.u32) + u32AddrOffset));
    VPSS_DIEJITMTN.bits.jitter_coring = jitter_coring;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEJITMTN.u32) + u32AddrOffset), VPSS_DIEJITMTN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetJitterGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 jitter_gain)
{
    U_VPSS_DIEJITMTN VPSS_DIEJITMTN;

    VPSS_DIEJITMTN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEJITMTN.u32) + u32AddrOffset));
    VPSS_DIEJITMTN.bits.jitter_gain = jitter_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEJITMTN.u32) + u32AddrOffset), VPSS_DIEJITMTN.u32);

    return ;
}



HI_VOID VPSS_Sys_SetLongMotionShf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 long_motion_shf)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset));
    VPSS_DIEFLDMTN.bits.long_motion_shf = long_motion_shf;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFldMotionWndMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 fld_motion_wnd_mode)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset));
    VPSS_DIEFLDMTN.bits.fld_motion_wnd_mode = fld_motion_wnd_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFldMotionGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 fld_motion_gain)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset));
    VPSS_DIEFLDMTN.bits.fld_motion_gain = fld_motion_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFldMotionCurveSlope(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 fld_motion_curve_slope)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset));
    VPSS_DIEFLDMTN.bits.fld_motion_curve_slope = fld_motion_curve_slope;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFldMotionThdHigh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 fld_motion_thd_high)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset));
    VPSS_DIEFLDMTN.bits.fld_motion_thd_high = fld_motion_thd_high;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset), VPSS_DIEFLDMTN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFldMotionThdLow(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 fld_motion_thd_low)
{
    U_VPSS_DIEFLDMTN VPSS_DIEFLDMTN;

    VPSS_DIEFLDMTN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset));
    VPSS_DIEFLDMTN.bits.fld_motion_thd_low = fld_motion_thd_low;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFLDMTN.u32) + u32AddrOffset), VPSS_DIEFLDMTN.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionDiffThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_diff_thd_3)
{
    U_VPSS_DIEMTNDIFFTHD0 VPSS_DIEMTNDIFFTHD0;

    VPSS_DIEMTNDIFFTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32) + u32AddrOffset));
    VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_3 = motion_diff_thd_3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32) + u32AddrOffset), VPSS_DIEMTNDIFFTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionDiffThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_diff_thd_2)
{
    U_VPSS_DIEMTNDIFFTHD0 VPSS_DIEMTNDIFFTHD0;

    VPSS_DIEMTNDIFFTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32) + u32AddrOffset));
    VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_2 = motion_diff_thd_2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32) + u32AddrOffset), VPSS_DIEMTNDIFFTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionDiffThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_diff_thd_1)
{
    U_VPSS_DIEMTNDIFFTHD0 VPSS_DIEMTNDIFFTHD0;

    VPSS_DIEMTNDIFFTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32) + u32AddrOffset));
    VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_1 = motion_diff_thd_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32) + u32AddrOffset), VPSS_DIEMTNDIFFTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionDiffThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_diff_thd_0)
{
    U_VPSS_DIEMTNDIFFTHD0 VPSS_DIEMTNDIFFTHD0;

    VPSS_DIEMTNDIFFTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32) + u32AddrOffset));
    VPSS_DIEMTNDIFFTHD0.bits.motion_diff_thd_0 = motion_diff_thd_0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD0.u32) + u32AddrOffset), VPSS_DIEMTNDIFFTHD0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMaxMotionIirRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 max_motion_iir_ratio)
{
    U_VPSS_DIEMTNDIFFTHD1 VPSS_DIEMTNDIFFTHD1;

    VPSS_DIEMTNDIFFTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32) + u32AddrOffset));
    VPSS_DIEMTNDIFFTHD1.bits.max_motion_iir_ratio = max_motion_iir_ratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32) + u32AddrOffset), VPSS_DIEMTNDIFFTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMinMotionIirRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 min_motion_iir_ratio)
{
    U_VPSS_DIEMTNDIFFTHD1 VPSS_DIEMTNDIFFTHD1;

    VPSS_DIEMTNDIFFTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32) + u32AddrOffset));
    VPSS_DIEMTNDIFFTHD1.bits.min_motion_iir_ratio = min_motion_iir_ratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32) + u32AddrOffset), VPSS_DIEMTNDIFFTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionDiffThd5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_diff_thd_5)
{
    U_VPSS_DIEMTNDIFFTHD1 VPSS_DIEMTNDIFFTHD1;

    VPSS_DIEMTNDIFFTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32) + u32AddrOffset));
    VPSS_DIEMTNDIFFTHD1.bits.motion_diff_thd_5 = motion_diff_thd_5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32) + u32AddrOffset), VPSS_DIEMTNDIFFTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionDiffThd4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_diff_thd_4)
{
    U_VPSS_DIEMTNDIFFTHD1 VPSS_DIEMTNDIFFTHD1;

    VPSS_DIEMTNDIFFTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32) + u32AddrOffset));
    VPSS_DIEMTNDIFFTHD1.bits.motion_diff_thd_4 = motion_diff_thd_4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNDIFFTHD1.u32) + u32AddrOffset), VPSS_DIEMTNDIFFTHD1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionIirCurveRatio0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_curve_ratio_0)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_ratio_0 = motion_iir_curve_ratio_0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset), VPSS_DIEMTNIIRSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionIirCurveSlope3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_curve_slope_3)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_3 = motion_iir_curve_slope_3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset), VPSS_DIEMTNIIRSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionIirCurveSlope2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_curve_slope_2)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_2 = motion_iir_curve_slope_2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset), VPSS_DIEMTNIIRSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionIirCurveSlope1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_curve_slope_1)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_1 = motion_iir_curve_slope_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset), VPSS_DIEMTNIIRSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionIirCurveSlope0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_curve_slope_0)
{
    U_VPSS_DIEMTNIIRSLP VPSS_DIEMTNIIRSLP;

    VPSS_DIEMTNIIRSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset));
    VPSS_DIEMTNIIRSLP.bits.motion_iir_curve_slope_0 = motion_iir_curve_slope_0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNIIRSLP.u32) + u32AddrOffset), VPSS_DIEMTNIIRSLP.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionIirCurveRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_curve_ratio_4)
{
    U_VPSS_DIEMTNIIRRAT VPSS_DIEMTNIIRRAT;

    VPSS_DIEMTNIIRRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32) + u32AddrOffset));
    VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_4 = motion_iir_curve_ratio_4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32) + u32AddrOffset), VPSS_DIEMTNIIRRAT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionIirCurveRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_curve_ratio_3)
{
    U_VPSS_DIEMTNIIRRAT VPSS_DIEMTNIIRRAT;

    VPSS_DIEMTNIIRRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32) + u32AddrOffset));
    VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_3 = motion_iir_curve_ratio_3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32) + u32AddrOffset), VPSS_DIEMTNIIRRAT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionIirCurveRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_curve_ratio_2)
{
    U_VPSS_DIEMTNIIRRAT VPSS_DIEMTNIIRRAT;

    VPSS_DIEMTNIIRRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32) + u32AddrOffset));
    VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_2 = motion_iir_curve_ratio_2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32) + u32AddrOffset), VPSS_DIEMTNIIRRAT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionIirCurveRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_iir_curve_ratio_1)
{
    U_VPSS_DIEMTNIIRRAT VPSS_DIEMTNIIRRAT;

    VPSS_DIEMTNIIRRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32) + u32AddrOffset));
    VPSS_DIEMTNIIRRAT.bits.motion_iir_curve_ratio_1 = motion_iir_curve_ratio_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNIIRRAT.u32) + u32AddrOffset), VPSS_DIEMTNIIRRAT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetHisMotionInfoWriteMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 his_motion_info_write_mode)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.his_motion_info_write_mode = his_motion_info_write_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHisMotionWriteMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 his_motion_write_mode)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.his_motion_write_mode = his_motion_write_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHisMotionUsingMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 his_motion_using_mode)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.his_motion_using_mode = his_motion_using_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHisMotionEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 his_motion_en)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.his_motion_en = his_motion_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetPreInfoEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 pre_info_en)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.pre_info_en = pre_info_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetPpreInfoEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ppre_info_en)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.ppre_info_en = ppre_info_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRecModeFrmMotionStep1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rec_mode_frm_motion_step_1)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.rec_mode_frm_motion_step_1 = rec_mode_frm_motion_step_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRecModeFrmMotionStep0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rec_mode_frm_motion_step_0)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.rec_mode_frm_motion_step_0 = rec_mode_frm_motion_step_0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRecModeFldMotionStep1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rec_mode_fld_motion_step_1)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.rec_mode_fld_motion_step_1 = rec_mode_fld_motion_step_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRecModeFldMotionStep0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rec_mode_fld_motion_step_0)
{
    U_VPSS_DIEHISMODE VPSS_DIEHISMODE;

    VPSS_DIEHISMODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset));
    VPSS_DIEHISMODE.bits.rec_mode_fld_motion_step_0 = rec_mode_fld_motion_step_0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEHISMODE.u32) + u32AddrOffset), VPSS_DIEHISMODE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMedBlendEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 med_blend_en)
{
    U_VPSS_DIEMORFLT VPSS_DIEMORFLT;

    VPSS_DIEMORFLT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMORFLT.u32) + u32AddrOffset));
    VPSS_DIEMORFLT.bits.med_blend_en = med_blend_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMORFLT.u32) + u32AddrOffset), VPSS_DIEMORFLT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMorFltEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mor_flt_en)
{
    U_VPSS_DIEMORFLT VPSS_DIEMORFLT;

    VPSS_DIEMORFLT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMORFLT.u32) + u32AddrOffset));
    VPSS_DIEMORFLT.bits.mor_flt_en = mor_flt_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMORFLT.u32) + u32AddrOffset), VPSS_DIEMORFLT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMorFltSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mor_flt_size)
{
    U_VPSS_DIEMORFLT VPSS_DIEMORFLT;

    VPSS_DIEMORFLT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMORFLT.u32) + u32AddrOffset));
    VPSS_DIEMORFLT.bits.mor_flt_size = mor_flt_size;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMORFLT.u32) + u32AddrOffset), VPSS_DIEMORFLT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMorFltThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mor_flt_thd)
{
    U_VPSS_DIEMORFLT VPSS_DIEMORFLT;

    VPSS_DIEMORFLT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMORFLT.u32) + u32AddrOffset));
    VPSS_DIEMORFLT.bits.mor_flt_thd = mor_flt_thd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMORFLT.u32) + u32AddrOffset), VPSS_DIEMORFLT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCombChkUpperLimit(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 comb_chk_upper_limit)
{
    U_VPSS_DIECOMBCHK0 VPSS_DIECOMBCHK0;

    VPSS_DIECOMBCHK0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECOMBCHK0.u32) + u32AddrOffset));
    VPSS_DIECOMBCHK0.bits.comb_chk_upper_limit = comb_chk_upper_limit;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECOMBCHK0.u32) + u32AddrOffset), VPSS_DIECOMBCHK0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCombChkLowerLimit(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 comb_chk_lower_limit)
{
    U_VPSS_DIECOMBCHK0 VPSS_DIECOMBCHK0;

    VPSS_DIECOMBCHK0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECOMBCHK0.u32) + u32AddrOffset));
    VPSS_DIECOMBCHK0.bits.comb_chk_lower_limit = comb_chk_lower_limit;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECOMBCHK0.u32) + u32AddrOffset), VPSS_DIECOMBCHK0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCombChkMinVthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 comb_chk_min_vthd)
{
    U_VPSS_DIECOMBCHK0 VPSS_DIECOMBCHK0;

    VPSS_DIECOMBCHK0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECOMBCHK0.u32) + u32AddrOffset));
    VPSS_DIECOMBCHK0.bits.comb_chk_min_vthd = comb_chk_min_vthd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECOMBCHK0.u32) + u32AddrOffset), VPSS_DIECOMBCHK0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCombChkMinHthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 comb_chk_min_hthd)
{
    U_VPSS_DIECOMBCHK0 VPSS_DIECOMBCHK0;

    VPSS_DIECOMBCHK0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECOMBCHK0.u32) + u32AddrOffset));
    VPSS_DIECOMBCHK0.bits.comb_chk_min_hthd = comb_chk_min_hthd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECOMBCHK0.u32) + u32AddrOffset), VPSS_DIECOMBCHK0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCombChkEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 comb_chk_en)
{
    U_VPSS_DIECOMBCHK1 VPSS_DIECOMBCHK1;

    VPSS_DIECOMBCHK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECOMBCHK1.u32) + u32AddrOffset));
    VPSS_DIECOMBCHK1.bits.comb_chk_en = comb_chk_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECOMBCHK1.u32) + u32AddrOffset), VPSS_DIECOMBCHK1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCombChkMdThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 comb_chk_md_thd)
{
    U_VPSS_DIECOMBCHK1 VPSS_DIECOMBCHK1;

    VPSS_DIECOMBCHK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECOMBCHK1.u32) + u32AddrOffset));
    VPSS_DIECOMBCHK1.bits.comb_chk_md_thd = comb_chk_md_thd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECOMBCHK1.u32) + u32AddrOffset), VPSS_DIECOMBCHK1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCombChkEdgeThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 comb_chk_edge_thd)
{
    U_VPSS_DIECOMBCHK1 VPSS_DIECOMBCHK1;

    VPSS_DIECOMBCHK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIECOMBCHK1.u32) + u32AddrOffset));
    VPSS_DIECOMBCHK1.bits.comb_chk_edge_thd = comb_chk_edge_thd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIECOMBCHK1.u32) + u32AddrOffset), VPSS_DIECOMBCHK1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFrameMotionSmoothThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_thd3)
{
    U_VPSS_DIEFRMMTNSMTHTHD0 VPSS_DIEFRMMTNSMTHTHD0;

    VPSS_DIEFRMMTNSMTHTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd3 = frame_motion_smooth_thd3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_thd2)
{
    U_VPSS_DIEFRMMTNSMTHTHD0 VPSS_DIEFRMMTNSMTHTHD0;

    VPSS_DIEFRMMTNSMTHTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd2 = frame_motion_smooth_thd2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_thd1)
{
    U_VPSS_DIEFRMMTNSMTHTHD0 VPSS_DIEFRMMTNSMTHTHD0;

    VPSS_DIEFRMMTNSMTHTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd1 = frame_motion_smooth_thd1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_thd0)
{
    U_VPSS_DIEFRMMTNSMTHTHD0 VPSS_DIEFRMMTNSMTHTHD0;

    VPSS_DIEFRMMTNSMTHTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHTHD0.bits.frame_motion_smooth_thd0 = frame_motion_smooth_thd0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD0.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHTHD0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFrameMotionSmoothRatioMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_ratio_max)
{
    U_VPSS_DIEFRMMTNSMTHTHD1 VPSS_DIEFRMMTNSMTHTHD1;

    VPSS_DIEFRMMTNSMTHTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_ratio_max = frame_motion_smooth_ratio_max;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothRatioMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_ratio_min)
{
    U_VPSS_DIEFRMMTNSMTHTHD1 VPSS_DIEFRMMTNSMTHTHD1;

    VPSS_DIEFRMMTNSMTHTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_ratio_min = frame_motion_smooth_ratio_min;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothThd5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_thd5)
{
    U_VPSS_DIEFRMMTNSMTHTHD1 VPSS_DIEFRMMTNSMTHTHD1;

    VPSS_DIEFRMMTNSMTHTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_thd5 = frame_motion_smooth_thd5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothThd4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_thd4)
{
    U_VPSS_DIEFRMMTNSMTHTHD1 VPSS_DIEFRMMTNSMTHTHD1;

    VPSS_DIEFRMMTNSMTHTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHTHD1.bits.frame_motion_smooth_thd4 = frame_motion_smooth_thd4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHTHD1.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHTHD1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFrameMotionSmoothRatio0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_ratio0)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_ratio0 = frame_motion_smooth_ratio0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothSlope3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_slope3)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope3 = frame_motion_smooth_slope3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothSlope2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_slope2)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope2 = frame_motion_smooth_slope2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothSlope1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_slope1)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope1 = frame_motion_smooth_slope1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothSlope0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_slope0)
{
    U_VPSS_DIEFRMMTNSMTHSLP VPSS_DIEFRMMTNSMTHSLP;

    VPSS_DIEFRMMTNSMTHSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHSLP.bits.frame_motion_smooth_slope0 = frame_motion_smooth_slope0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHSLP.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHSLP.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFrameMotionSmoothRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_ratio4)
{
    U_VPSS_DIEFRMMTNSMTHRAT VPSS_DIEFRMMTNSMTHRAT;

    VPSS_DIEFRMMTNSMTHRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio4 = frame_motion_smooth_ratio4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHRAT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_ratio3)
{
    U_VPSS_DIEFRMMTNSMTHRAT VPSS_DIEFRMMTNSMTHRAT;

    VPSS_DIEFRMMTNSMTHRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio3 = frame_motion_smooth_ratio3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHRAT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_ratio2)
{
    U_VPSS_DIEFRMMTNSMTHRAT VPSS_DIEFRMMTNSMTHRAT;

    VPSS_DIEFRMMTNSMTHRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio2 = frame_motion_smooth_ratio2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHRAT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMotionSmoothRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_motion_smooth_ratio1)
{
    U_VPSS_DIEFRMMTNSMTHRAT VPSS_DIEFRMMTNSMTHRAT;

    VPSS_DIEFRMMTNSMTHRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32) + u32AddrOffset));
    VPSS_DIEFRMMTNSMTHRAT.bits.frame_motion_smooth_ratio1 = frame_motion_smooth_ratio1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMMTNSMTHRAT.u32) + u32AddrOffset), VPSS_DIEFRMMTNSMTHRAT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFrameFieldBlendThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_thd3)
{
    U_VPSS_DIEFRMFLDBLENDTHD0 VPSS_DIEFRMFLDBLENDTHD0;

    VPSS_DIEFRMFLDBLENDTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd3 = frame_field_blend_thd3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_thd2)
{
    U_VPSS_DIEFRMFLDBLENDTHD0 VPSS_DIEFRMFLDBLENDTHD0;

    VPSS_DIEFRMFLDBLENDTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd2 = frame_field_blend_thd2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_thd1)
{
    U_VPSS_DIEFRMFLDBLENDTHD0 VPSS_DIEFRMFLDBLENDTHD0;

    VPSS_DIEFRMFLDBLENDTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd1 = frame_field_blend_thd1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_thd0)
{
    U_VPSS_DIEFRMFLDBLENDTHD0 VPSS_DIEFRMFLDBLENDTHD0;

    VPSS_DIEFRMFLDBLENDTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDTHD0.bits.frame_field_blend_thd0 = frame_field_blend_thd0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD0.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDTHD0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFrameFieldBlendRatioMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_ratio_max)
{
    U_VPSS_DIEFRMFLDBLENDTHD1 VPSS_DIEFRMFLDBLENDTHD1;

    VPSS_DIEFRMFLDBLENDTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_ratio_max = frame_field_blend_ratio_max;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendRatioMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_ratio_min)
{
    U_VPSS_DIEFRMFLDBLENDTHD1 VPSS_DIEFRMFLDBLENDTHD1;

    VPSS_DIEFRMFLDBLENDTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_ratio_min = frame_field_blend_ratio_min;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendThd5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_thd5)
{
    U_VPSS_DIEFRMFLDBLENDTHD1 VPSS_DIEFRMFLDBLENDTHD1;

    VPSS_DIEFRMFLDBLENDTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_thd5 = frame_field_blend_thd5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendThd4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_thd4)
{
    U_VPSS_DIEFRMFLDBLENDTHD1 VPSS_DIEFRMFLDBLENDTHD1;

    VPSS_DIEFRMFLDBLENDTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDTHD1.bits.frame_field_blend_thd4 = frame_field_blend_thd4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDTHD1.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDTHD1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFrameFieldBlendRatio0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_ratio0)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_ratio0 = frame_field_blend_ratio0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendSlope3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_slope3)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope3 = frame_field_blend_slope3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendSlope2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_slope2)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope2 = frame_field_blend_slope2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendSlope1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_slope1)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope1 = frame_field_blend_slope1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendSlope0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_slope0)
{
    U_VPSS_DIEFRMFLDBLENDSLP VPSS_DIEFRMFLDBLENDSLP;

    VPSS_DIEFRMFLDBLENDSLP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDSLP.bits.frame_field_blend_slope0 = frame_field_blend_slope0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDSLP.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDSLP.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFrameFieldBlendRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_ratio4)
{
    U_VPSS_DIEFRMFLDBLENDRAT VPSS_DIEFRMFLDBLENDRAT;

    VPSS_DIEFRMFLDBLENDRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio4 = frame_field_blend_ratio4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDRAT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_ratio3)
{
    U_VPSS_DIEFRMFLDBLENDRAT VPSS_DIEFRMFLDBLENDRAT;

    VPSS_DIEFRMFLDBLENDRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio3 = frame_field_blend_ratio3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDRAT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_ratio2)
{
    U_VPSS_DIEFRMFLDBLENDRAT VPSS_DIEFRMFLDBLENDRAT;

    VPSS_DIEFRMFLDBLENDRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio2 = frame_field_blend_ratio2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDRAT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameFieldBlendRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_field_blend_ratio1)
{
    U_VPSS_DIEFRMFLDBLENDRAT VPSS_DIEFRMFLDBLENDRAT;

    VPSS_DIEFRMFLDBLENDRAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32) + u32AddrOffset));
    VPSS_DIEFRMFLDBLENDRAT.bits.frame_field_blend_ratio1 = frame_field_blend_ratio1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFRMFLDBLENDRAT.u32) + u32AddrOffset), VPSS_DIEFRMFLDBLENDRAT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionAdjustGainChr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_adjust_gain_chr)
{
    U_VPSS_DIEMTNADJ VPSS_DIEMTNADJ;

    VPSS_DIEMTNADJ.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNADJ.u32) + u32AddrOffset));
    VPSS_DIEMTNADJ.bits.motion_adjust_gain_chr = motion_adjust_gain_chr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNADJ.u32) + u32AddrOffset), VPSS_DIEMTNADJ.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionAdjustCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_adjust_coring)
{
    U_VPSS_DIEMTNADJ VPSS_DIEMTNADJ;

    VPSS_DIEMTNADJ.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNADJ.u32) + u32AddrOffset));
    VPSS_DIEMTNADJ.bits.motion_adjust_coring = motion_adjust_coring;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNADJ.u32) + u32AddrOffset), VPSS_DIEMTNADJ.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionAdjustGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_adjust_gain)
{
    U_VPSS_DIEMTNADJ VPSS_DIEMTNADJ;

    VPSS_DIEMTNADJ.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMTNADJ.u32) + u32AddrOffset));
    VPSS_DIEMTNADJ.bits.motion_adjust_gain = motion_adjust_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMTNADJ.u32) + u32AddrOffset), VPSS_DIEMTNADJ.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgeNorm1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_1)
{
    U_VPSS_DIEEDGENORM0 VPSS_DIEEDGENORM0;

    VPSS_DIEEDGENORM0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM0.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM0.bits.edge_norm_1 = edge_norm_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM0.u32) + u32AddrOffset), VPSS_DIEEDGENORM0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_0)
{
    U_VPSS_DIEEDGENORM0 VPSS_DIEEDGENORM0;

    VPSS_DIEEDGENORM0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM0.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM0.bits.edge_norm_0 = edge_norm_0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM0.u32) + u32AddrOffset), VPSS_DIEEDGENORM0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgeNorm3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_3)
{
    U_VPSS_DIEEDGENORM1 VPSS_DIEEDGENORM1;

    VPSS_DIEEDGENORM1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM1.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM1.bits.edge_norm_3 = edge_norm_3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM1.u32) + u32AddrOffset), VPSS_DIEEDGENORM1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_2)
{
    U_VPSS_DIEEDGENORM1 VPSS_DIEEDGENORM1;

    VPSS_DIEEDGENORM1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM1.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM1.bits.edge_norm_2 = edge_norm_2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM1.u32) + u32AddrOffset), VPSS_DIEEDGENORM1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMcStrengthK3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_k3)
{
    U_VPSS_DIEEDGENORM2 VPSS_DIEEDGENORM2;

    VPSS_DIEEDGENORM2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM2.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM2.bits.mc_strength_k3 = mc_strength_k3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM2.u32) + u32AddrOffset), VPSS_DIEEDGENORM2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_5)
{
    U_VPSS_DIEEDGENORM2 VPSS_DIEEDGENORM2;

    VPSS_DIEEDGENORM2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM2.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM2.bits.edge_norm_5 = edge_norm_5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM2.u32) + u32AddrOffset), VPSS_DIEEDGENORM2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_4)
{
    U_VPSS_DIEEDGENORM2 VPSS_DIEEDGENORM2;

    VPSS_DIEEDGENORM2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM2.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM2.bits.edge_norm_4 = edge_norm_4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM2.u32) + u32AddrOffset), VPSS_DIEEDGENORM2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMcStrengthG3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_g3)
{
    U_VPSS_DIEEDGENORM3 VPSS_DIEEDGENORM3;

    VPSS_DIEEDGENORM3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM3.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM3.bits.mc_strength_g3 = mc_strength_g3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM3.u32) + u32AddrOffset), VPSS_DIEEDGENORM3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_7)
{
    U_VPSS_DIEEDGENORM3 VPSS_DIEEDGENORM3;

    VPSS_DIEEDGENORM3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM3.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM3.bits.edge_norm_7 = edge_norm_7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM3.u32) + u32AddrOffset), VPSS_DIEEDGENORM3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_6)
{
    U_VPSS_DIEEDGENORM3 VPSS_DIEEDGENORM3;

    VPSS_DIEEDGENORM3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM3.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM3.bits.edge_norm_6 = edge_norm_6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM3.u32) + u32AddrOffset), VPSS_DIEEDGENORM3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetInterDiffThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 inter_diff_thd0)
{
    U_VPSS_DIEEDGENORM4 VPSS_DIEEDGENORM4;

    VPSS_DIEEDGENORM4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM4.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM4.bits.inter_diff_thd0 = inter_diff_thd0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM4.u32) + u32AddrOffset), VPSS_DIEEDGENORM4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_9)
{
    U_VPSS_DIEEDGENORM4 VPSS_DIEEDGENORM4;

    VPSS_DIEEDGENORM4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM4.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM4.bits.edge_norm_9 = edge_norm_9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM4.u32) + u32AddrOffset), VPSS_DIEEDGENORM4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_8)
{
    U_VPSS_DIEEDGENORM4 VPSS_DIEEDGENORM4;

    VPSS_DIEEDGENORM4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM4.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM4.bits.edge_norm_8 = edge_norm_8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM4.u32) + u32AddrOffset), VPSS_DIEEDGENORM4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetInterDiffThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 inter_diff_thd1)
{
    U_VPSS_DIEEDGENORM5 VPSS_DIEEDGENORM5;

    VPSS_DIEEDGENORM5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM5.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM5.bits.inter_diff_thd1 = inter_diff_thd1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM5.u32) + u32AddrOffset), VPSS_DIEEDGENORM5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_11)
{
    U_VPSS_DIEEDGENORM5 VPSS_DIEEDGENORM5;

    VPSS_DIEEDGENORM5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM5.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM5.bits.edge_norm_11 = edge_norm_11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM5.u32) + u32AddrOffset), VPSS_DIEEDGENORM5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeNorm10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_norm_10)
{
    U_VPSS_DIEEDGENORM5 VPSS_DIEEDGENORM5;

    VPSS_DIEEDGENORM5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGENORM5.u32) + u32AddrOffset));
    VPSS_DIEEDGENORM5.bits.edge_norm_10 = edge_norm_10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGENORM5.u32) + u32AddrOffset), VPSS_DIEEDGENORM5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetInterDiffThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 inter_diff_thd2)
{
    U_VPSS_DIEEDGEFORMC VPSS_DIEEDGEFORMC;

    VPSS_DIEEDGEFORMC.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32) + u32AddrOffset));
    VPSS_DIEEDGEFORMC.bits.inter_diff_thd2 = inter_diff_thd2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32) + u32AddrOffset), VPSS_DIEEDGEFORMC.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeScale(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_scale)
{
    U_VPSS_DIEEDGEFORMC VPSS_DIEEDGEFORMC;

    VPSS_DIEEDGEFORMC.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32) + u32AddrOffset));
    VPSS_DIEEDGEFORMC.bits.edge_scale = edge_scale;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32) + u32AddrOffset), VPSS_DIEEDGEFORMC.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_coring)
{
    U_VPSS_DIEEDGEFORMC VPSS_DIEEDGEFORMC;

    VPSS_DIEEDGEFORMC.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32) + u32AddrOffset));
    VPSS_DIEEDGEFORMC.bits.edge_coring = edge_coring;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEEDGEFORMC.u32) + u32AddrOffset), VPSS_DIEEDGEFORMC.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMcStrengthG0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_g0)
{
    U_VPSS_DIEMCSTRENGTH0 VPSS_DIEMCSTRENGTH0;

    VPSS_DIEMCSTRENGTH0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32) + u32AddrOffset));
    VPSS_DIEMCSTRENGTH0.bits.mc_strength_g0 = mc_strength_g0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32) + u32AddrOffset), VPSS_DIEMCSTRENGTH0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcStrengthK2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_k2)
{
    U_VPSS_DIEMCSTRENGTH0 VPSS_DIEMCSTRENGTH0;

    VPSS_DIEMCSTRENGTH0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32) + u32AddrOffset));
    VPSS_DIEMCSTRENGTH0.bits.mc_strength_k2 = mc_strength_k2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32) + u32AddrOffset), VPSS_DIEMCSTRENGTH0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcStrengthK1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_k1)
{
    U_VPSS_DIEMCSTRENGTH0 VPSS_DIEMCSTRENGTH0;

    VPSS_DIEMCSTRENGTH0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32) + u32AddrOffset));
    VPSS_DIEMCSTRENGTH0.bits.mc_strength_k1 = mc_strength_k1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32) + u32AddrOffset), VPSS_DIEMCSTRENGTH0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcStrengthK0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_k0)
{
    U_VPSS_DIEMCSTRENGTH0 VPSS_DIEMCSTRENGTH0;

    VPSS_DIEMCSTRENGTH0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32) + u32AddrOffset));
    VPSS_DIEMCSTRENGTH0.bits.mc_strength_k0 = mc_strength_k0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCSTRENGTH0.u32) + u32AddrOffset), VPSS_DIEMCSTRENGTH0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMcStrengthMaxg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_maxg)
{
    U_VPSS_DIEMCSTRENGTH1 VPSS_DIEMCSTRENGTH1;

    VPSS_DIEMCSTRENGTH1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32) + u32AddrOffset));
    VPSS_DIEMCSTRENGTH1.bits.mc_strength_maxg = mc_strength_maxg;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32) + u32AddrOffset), VPSS_DIEMCSTRENGTH1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcStrengthMing(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_ming)
{
    U_VPSS_DIEMCSTRENGTH1 VPSS_DIEMCSTRENGTH1;

    VPSS_DIEMCSTRENGTH1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32) + u32AddrOffset));
    VPSS_DIEMCSTRENGTH1.bits.mc_strength_ming = mc_strength_ming;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32) + u32AddrOffset), VPSS_DIEMCSTRENGTH1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcStrengthG2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_g2)
{
    U_VPSS_DIEMCSTRENGTH1 VPSS_DIEMCSTRENGTH1;

    VPSS_DIEMCSTRENGTH1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32) + u32AddrOffset));
    VPSS_DIEMCSTRENGTH1.bits.mc_strength_g2 = mc_strength_g2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32) + u32AddrOffset), VPSS_DIEMCSTRENGTH1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcStrengthG1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_strength_g1)
{
    U_VPSS_DIEMCSTRENGTH1 VPSS_DIEMCSTRENGTH1;

    VPSS_DIEMCSTRENGTH1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32) + u32AddrOffset));
    VPSS_DIEMCSTRENGTH1.bits.mc_strength_g1 = mc_strength_g1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCSTRENGTH1.u32) + u32AddrOffset), VPSS_DIEMCSTRENGTH1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKCMcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_c_mcbld)
{
    U_VPSS_DIEFUSION0 VPSS_DIEFUSION0;

    VPSS_DIEFUSION0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION0.u32) + u32AddrOffset));
    VPSS_DIEFUSION0.bits.k_c_mcbld = k_c_mcbld;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION0.u32) + u32AddrOffset), VPSS_DIEFUSION0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKCMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_c_mcw)
{
    U_VPSS_DIEFUSION0 VPSS_DIEFUSION0;

    VPSS_DIEFUSION0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION0.u32) + u32AddrOffset));
    VPSS_DIEFUSION0.bits.k_c_mcw = k_c_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION0.u32) + u32AddrOffset), VPSS_DIEFUSION0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKYMcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_y_mcbld)
{
    U_VPSS_DIEFUSION0 VPSS_DIEFUSION0;

    VPSS_DIEFUSION0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION0.u32) + u32AddrOffset));
    VPSS_DIEFUSION0.bits.k_y_mcbld = k_y_mcbld;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION0.u32) + u32AddrOffset), VPSS_DIEFUSION0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKYMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_y_mcw)
{
    U_VPSS_DIEFUSION0 VPSS_DIEFUSION0;

    VPSS_DIEFUSION0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION0.u32) + u32AddrOffset));
    VPSS_DIEFUSION0.bits.k_y_mcw = k_y_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION0.u32) + u32AddrOffset), VPSS_DIEFUSION0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetG0McwAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_mcw_adj)
{
    U_VPSS_DIEFUSION1 VPSS_DIEFUSION1;

    VPSS_DIEFUSION1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION1.u32) + u32AddrOffset));
    VPSS_DIEFUSION1.bits.g0_mcw_adj = g0_mcw_adj;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION1.u32) + u32AddrOffset), VPSS_DIEFUSION1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0McwAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_mcw_adj)
{
    U_VPSS_DIEFUSION1 VPSS_DIEFUSION1;

    VPSS_DIEFUSION1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION1.u32) + u32AddrOffset));
    VPSS_DIEFUSION1.bits.k0_mcw_adj = k0_mcw_adj;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION1.u32) + u32AddrOffset), VPSS_DIEFUSION1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0McwAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_mcw_adj)
{
    U_VPSS_DIEFUSION1 VPSS_DIEFUSION1;

    VPSS_DIEFUSION1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION1.u32) + u32AddrOffset));
    VPSS_DIEFUSION1.bits.x0_mcw_adj = x0_mcw_adj;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION1.u32) + u32AddrOffset), VPSS_DIEFUSION1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetK1Mcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_mcbld)
{
    U_VPSS_DIEFUSION2 VPSS_DIEFUSION2;

    VPSS_DIEFUSION2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION2.u32) + u32AddrOffset));
    VPSS_DIEFUSION2.bits.k1_mcbld = k1_mcbld;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION2.u32) + u32AddrOffset), VPSS_DIEFUSION2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0Mcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_mcbld)
{
    U_VPSS_DIEFUSION2 VPSS_DIEFUSION2;

    VPSS_DIEFUSION2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION2.u32) + u32AddrOffset));
    VPSS_DIEFUSION2.bits.k0_mcbld = k0_mcbld;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION2.u32) + u32AddrOffset), VPSS_DIEFUSION2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0Mcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_mcbld)
{
    U_VPSS_DIEFUSION2 VPSS_DIEFUSION2;

    VPSS_DIEFUSION2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION2.u32) + u32AddrOffset));
    VPSS_DIEFUSION2.bits.x0_mcbld = x0_mcbld;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION2.u32) + u32AddrOffset), VPSS_DIEFUSION2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK1McwAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_mcw_adj)
{
    U_VPSS_DIEFUSION2 VPSS_DIEFUSION2;

    VPSS_DIEFUSION2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION2.u32) + u32AddrOffset));
    VPSS_DIEFUSION2.bits.k1_mcw_adj = k1_mcw_adj;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION2.u32) + u32AddrOffset), VPSS_DIEFUSION2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMcLaiBldmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_lai_bldmode)
{
    U_VPSS_DIEFUSION3 VPSS_DIEFUSION3;

    VPSS_DIEFUSION3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION3.u32) + u32AddrOffset));
    VPSS_DIEFUSION3.bits.mc_lai_bldmode = mc_lai_bldmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION3.u32) + u32AddrOffset), VPSS_DIEFUSION3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKCurwMcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_curw_mcbld)
{
    U_VPSS_DIEFUSION3 VPSS_DIEFUSION3;

    VPSS_DIEFUSION3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION3.u32) + u32AddrOffset));
    VPSS_DIEFUSION3.bits.k_curw_mcbld = k_curw_mcbld;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION3.u32) + u32AddrOffset), VPSS_DIEFUSION3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG0Mcbld(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_mcbld)
{
    U_VPSS_DIEFUSION3 VPSS_DIEFUSION3;

    VPSS_DIEFUSION3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEFUSION3.u32) + u32AddrOffset));
    VPSS_DIEFUSION3.bits.g0_mcbld = g0_mcbld;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEFUSION3.u32) + u32AddrOffset), VPSS_DIEFUSION3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMaGbmThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ma_gbm_thd0)
{
    U_VPSS_DIEMAGBMTHD0 VPSS_DIEMAGBMTHD0;

    VPSS_DIEMAGBMTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMAGBMTHD0.u32) + u32AddrOffset));
    VPSS_DIEMAGBMTHD0.bits.ma_gbm_thd0 = ma_gbm_thd0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMAGBMTHD0.u32) + u32AddrOffset), VPSS_DIEMAGBMTHD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMaGbmThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ma_gbm_thd1)
{
    U_VPSS_DIEMAGBMTHD0 VPSS_DIEMAGBMTHD0;

    VPSS_DIEMAGBMTHD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMAGBMTHD0.u32) + u32AddrOffset));
    VPSS_DIEMAGBMTHD0.bits.ma_gbm_thd1 = ma_gbm_thd1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMAGBMTHD0.u32) + u32AddrOffset), VPSS_DIEMAGBMTHD0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMaGbmThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ma_gbm_thd2)
{
    U_VPSS_DIEMAGBMTHD1 VPSS_DIEMAGBMTHD1;

    VPSS_DIEMAGBMTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMAGBMTHD1.u32) + u32AddrOffset));
    VPSS_DIEMAGBMTHD1.bits.ma_gbm_thd2 = ma_gbm_thd2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMAGBMTHD1.u32) + u32AddrOffset), VPSS_DIEMAGBMTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMaGbmThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ma_gbm_thd3)
{
    U_VPSS_DIEMAGBMTHD1 VPSS_DIEMAGBMTHD1;

    VPSS_DIEMAGBMTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMAGBMTHD1.u32) + u32AddrOffset));
    VPSS_DIEMAGBMTHD1.bits.ma_gbm_thd3 = ma_gbm_thd3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMAGBMTHD1.u32) + u32AddrOffset), VPSS_DIEMAGBMTHD1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMtfiltenGmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mtfilten_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset));
    VPSS_DIEMCGBMCOEF0.bits.mtfilten_gmd = mtfilten_gmd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMtth3Gmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mtth3_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset));
    VPSS_DIEMCGBMCOEF0.bits.mtth3_gmd = mtth3_gmd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMtth2Gmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mtth2_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset));
    VPSS_DIEMCGBMCOEF0.bits.mtth2_gmd = mtth2_gmd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMtth1Gmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mtth1_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset));
    VPSS_DIEMCGBMCOEF0.bits.mtth1_gmd = mtth1_gmd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMtth0Gmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mtth0_gmd)
{
    U_VPSS_DIEMCGBMCOEF0 VPSS_DIEMCGBMCOEF0;

    VPSS_DIEMCGBMCOEF0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset));
    VPSS_DIEMCGBMCOEF0.bits.mtth0_gmd = mtth0_gmd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCGBMCOEF0.u32) + u32AddrOffset), VPSS_DIEMCGBMCOEF0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKMagGmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_mag_gmd)
{
    U_VPSS_DIEMCGBMCOEF1 VPSS_DIEMCGBMCOEF1;

    VPSS_DIEMCGBMCOEF1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32) + u32AddrOffset));
    VPSS_DIEMCGBMCOEF1.bits.k_mag_gmd = k_mag_gmd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32) + u32AddrOffset), VPSS_DIEMCGBMCOEF1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKDifhGmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_difh_gmd)
{
    U_VPSS_DIEMCGBMCOEF1 VPSS_DIEMCGBMCOEF1;

    VPSS_DIEMCGBMCOEF1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32) + u32AddrOffset));
    VPSS_DIEMCGBMCOEF1.bits.k_difh_gmd = k_difh_gmd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32) + u32AddrOffset), VPSS_DIEMCGBMCOEF1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKMaxmagGmd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_maxmag_gmd)
{
    U_VPSS_DIEMCGBMCOEF1 VPSS_DIEMCGBMCOEF1;

    VPSS_DIEMCGBMCOEF1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32) + u32AddrOffset));
    VPSS_DIEMCGBMCOEF1.bits.k_maxmag_gmd = k_maxmag_gmd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEMCGBMCOEF1.u32) + u32AddrOffset), VPSS_DIEMCGBMCOEF1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKhoredge(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 khoredge)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset));
    VPSS_DIEKMAG1.bits.khoredge = khoredge;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset), VPSS_DIEKMAG1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKmagv2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 kmagv_2)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset));
    VPSS_DIEKMAG1.bits.kmagv_2 = kmagv_2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset), VPSS_DIEKMAG1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKmagv1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 kmagv_1)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset));
    VPSS_DIEKMAG1.bits.kmagv_1 = kmagv_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset), VPSS_DIEKMAG1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKmagh2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 kmagh_2)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset));
    VPSS_DIEKMAG1.bits.kmagh_2 = kmagh_2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset), VPSS_DIEKMAG1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKmagh1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 kmagh_1)
{
    U_VPSS_DIEKMAG1 VPSS_DIEKMAG1;

    VPSS_DIEKMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset));
    VPSS_DIEKMAG1.bits.kmagh_1 = kmagh_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG1.u32) + u32AddrOffset), VPSS_DIEKMAG1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetScalerFramemotion(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scaler_framemotion)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset));
    VPSS_DIEKMAG2.bits.scaler_framemotion = scaler_framemotion;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset), VPSS_DIEKMAG2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionLimt2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_limt_2)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset));
    VPSS_DIEKMAG2.bits.motion_limt_2 = motion_limt_2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset), VPSS_DIEKMAG2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionLimt1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_limt_1)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset));
    VPSS_DIEKMAG2.bits.motion_limt_1 = motion_limt_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset), VPSS_DIEKMAG2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFrameMagEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 frame_mag_en)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset));
    VPSS_DIEKMAG2.bits.frame_mag_en = frame_mag_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset), VPSS_DIEKMAG2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetScalerHoredge(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scaler_horedge)
{
    U_VPSS_DIEKMAG2 VPSS_DIEKMAG2;

    VPSS_DIEKMAG2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset));
    VPSS_DIEKMAG2.bits.scaler_horedge = scaler_horedge;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIEKMAG2.u32) + u32AddrOffset), VPSS_DIEKMAG2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgeStrCoringC(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge_str_coring_c)
{
    U_VPSS_DIE_S3ADD VPSS_DIE_S3ADD;

    VPSS_DIE_S3ADD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIE_S3ADD.u32) + u32AddrOffset));
    VPSS_DIE_S3ADD.bits.edge_str_coring_c = edge_str_coring_c;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIE_S3ADD.u32) + u32AddrOffset), VPSS_DIE_S3ADD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDirRatioC(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dir_ratio_c)
{
    U_VPSS_DIE_S3ADD VPSS_DIE_S3ADD;

    VPSS_DIE_S3ADD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DIE_S3ADD.u32) + u32AddrOffset));
    VPSS_DIE_S3ADD.bits.dir_ratio_c = dir_ratio_c;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DIE_S3ADD.u32) + u32AddrOffset), VPSS_DIE_S3ADD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetHistThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hist_thd3)
{
    U_VPSS_PDPHISTTHD1 VPSS_PDPHISTTHD1;

    VPSS_PDPHISTTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPHISTTHD1.u32) + u32AddrOffset));
    VPSS_PDPHISTTHD1.bits.hist_thd3 = hist_thd3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPHISTTHD1.u32) + u32AddrOffset), VPSS_PDPHISTTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHistThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hist_thd2)
{
    U_VPSS_PDPHISTTHD1 VPSS_PDPHISTTHD1;

    VPSS_PDPHISTTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPHISTTHD1.u32) + u32AddrOffset));
    VPSS_PDPHISTTHD1.bits.hist_thd2 = hist_thd2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPHISTTHD1.u32) + u32AddrOffset), VPSS_PDPHISTTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHistThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hist_thd1)
{
    U_VPSS_PDPHISTTHD1 VPSS_PDPHISTTHD1;

    VPSS_PDPHISTTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPHISTTHD1.u32) + u32AddrOffset));
    VPSS_PDPHISTTHD1.bits.hist_thd1 = hist_thd1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPHISTTHD1.u32) + u32AddrOffset), VPSS_PDPHISTTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHistThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hist_thd0)
{
    U_VPSS_PDPHISTTHD1 VPSS_PDPHISTTHD1;

    VPSS_PDPHISTTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPHISTTHD1.u32) + u32AddrOffset));
    VPSS_PDPHISTTHD1.bits.hist_thd0 = hist_thd0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPHISTTHD1.u32) + u32AddrOffset), VPSS_PDPHISTTHD1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMovCoringNorm(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mov_coring_norm)
{
    U_VPSS_PDPCCMOV VPSS_PDPCCMOV;

    VPSS_PDPCCMOV.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCMOV.u32) + u32AddrOffset));
    VPSS_PDPCCMOV.bits.mov_coring_norm = mov_coring_norm;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCMOV.u32) + u32AddrOffset), VPSS_PDPCCMOV.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMovCoringTkr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mov_coring_tkr)
{
    U_VPSS_PDPCCMOV VPSS_PDPCCMOV;

    VPSS_PDPCCMOV.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCMOV.u32) + u32AddrOffset));
    VPSS_PDPCCMOV.bits.mov_coring_tkr = mov_coring_tkr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCMOV.u32) + u32AddrOffset), VPSS_PDPCCMOV.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMovCoringBlk(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mov_coring_blk)
{
    U_VPSS_PDPCCMOV VPSS_PDPCCMOV;

    VPSS_PDPCCMOV.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCMOV.u32) + u32AddrOffset));
    VPSS_PDPCCMOV.bits.mov_coring_blk = mov_coring_blk;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCMOV.u32) + u32AddrOffset), VPSS_PDPCCMOV.u32);

    return ;
}



HI_VOID VPSS_Sys_SetLasiMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_mode)
{
    U_VPSS_PDCTRL VPSS_PDCTRL;

    VPSS_PDCTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDCTRL.u32) + u32AddrOffset));
    VPSS_PDCTRL.bits.lasi_mode = lasi_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDCTRL.u32) + u32AddrOffset), VPSS_PDCTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBitsmov2r(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bitsmov2r)
{
    U_VPSS_PDCTRL VPSS_PDCTRL;

    VPSS_PDCTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDCTRL.u32) + u32AddrOffset));
    VPSS_PDCTRL.bits.bitsmov2r = bitsmov2r;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDCTRL.u32) + u32AddrOffset), VPSS_PDCTRL.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDiffMovblkThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 diff_movblk_thd)
{
    U_VPSS_PDBLKTHD VPSS_PDBLKTHD;

    VPSS_PDBLKTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDBLKTHD.u32) + u32AddrOffset));
    VPSS_PDBLKTHD.bits.diff_movblk_thd = diff_movblk_thd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDBLKTHD.u32) + u32AddrOffset), VPSS_PDBLKTHD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetUmThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 um_thd2)
{
    U_VPSS_PDUMTHD VPSS_PDUMTHD;

    VPSS_PDUMTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDUMTHD.u32) + u32AddrOffset));
    VPSS_PDUMTHD.bits.um_thd2 = um_thd2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDUMTHD.u32) + u32AddrOffset), VPSS_PDUMTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetUmThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 um_thd1)
{
    U_VPSS_PDUMTHD VPSS_PDUMTHD;

    VPSS_PDUMTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDUMTHD.u32) + u32AddrOffset));
    VPSS_PDUMTHD.bits.um_thd1 = um_thd1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDUMTHD.u32) + u32AddrOffset), VPSS_PDUMTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetUmThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 um_thd0)
{
    U_VPSS_PDUMTHD VPSS_PDUMTHD;

    VPSS_PDUMTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDUMTHD.u32) + u32AddrOffset));
    VPSS_PDUMTHD.bits.um_thd0 = um_thd0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDUMTHD.u32) + u32AddrOffset), VPSS_PDUMTHD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCoringBlk(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 coring_blk)
{
    U_VPSS_PDPCCCORING VPSS_PDPCCCORING;

    VPSS_PDPCCCORING.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCCORING.u32) + u32AddrOffset));
    VPSS_PDPCCCORING.bits.coring_blk = coring_blk;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCCORING.u32) + u32AddrOffset), VPSS_PDPCCCORING.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoringNorm(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 coring_norm)
{
    U_VPSS_PDPCCCORING VPSS_PDPCCCORING;

    VPSS_PDPCCCORING.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCCORING.u32) + u32AddrOffset));
    VPSS_PDPCCCORING.bits.coring_norm = coring_norm;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCCORING.u32) + u32AddrOffset), VPSS_PDPCCCORING.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoringTkr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 coring_tkr)
{
    U_VPSS_PDPCCCORING VPSS_PDPCCCORING;

    VPSS_PDPCCCORING.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCCORING.u32) + u32AddrOffset));
    VPSS_PDPCCCORING.bits.coring_tkr = coring_tkr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCCORING.u32) + u32AddrOffset), VPSS_PDPCCCORING.u32);

    return ;
}



HI_VOID VPSS_Sys_SetPccHthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 pcc_hthd)
{
    U_VPSS_PDPCCHTHD VPSS_PDPCCHTHD;

    VPSS_PDPCCHTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCHTHD.u32) + u32AddrOffset));
    VPSS_PDPCCHTHD.bits.pcc_hthd = pcc_hthd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCHTHD.u32) + u32AddrOffset), VPSS_PDPCCHTHD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetPccVthd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 pcc_vthd3)
{
    U_VPSS_PDPCCVTHD VPSS_PDPCCVTHD;

    VPSS_PDPCCVTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCVTHD.u32) + u32AddrOffset));
    VPSS_PDPCCVTHD.bits.pcc_vthd3 = pcc_vthd3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCVTHD.u32) + u32AddrOffset), VPSS_PDPCCVTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetPccVthd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 pcc_vthd2)
{
    U_VPSS_PDPCCVTHD VPSS_PDPCCVTHD;

    VPSS_PDPCCVTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCVTHD.u32) + u32AddrOffset));
    VPSS_PDPCCVTHD.bits.pcc_vthd2 = pcc_vthd2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCVTHD.u32) + u32AddrOffset), VPSS_PDPCCVTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetPccVthd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 pcc_vthd1)
{
    U_VPSS_PDPCCVTHD VPSS_PDPCCVTHD;

    VPSS_PDPCCVTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCVTHD.u32) + u32AddrOffset));
    VPSS_PDPCCVTHD.bits.pcc_vthd1 = pcc_vthd1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCVTHD.u32) + u32AddrOffset), VPSS_PDPCCVTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetPccVthd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 pcc_vthd0)
{
    U_VPSS_PDPCCVTHD VPSS_PDPCCVTHD;

    VPSS_PDPCCVTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDPCCVTHD.u32) + u32AddrOffset));
    VPSS_PDPCCVTHD.bits.pcc_vthd0 = pcc_vthd0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDPCCVTHD.u32) + u32AddrOffset), VPSS_PDPCCVTHD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetItdiffVthd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 itdiff_vthd3)
{
    U_VPSS_PDITDIFFVTHD VPSS_PDITDIFFVTHD;

    VPSS_PDITDIFFVTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32) + u32AddrOffset));
    VPSS_PDITDIFFVTHD.bits.itdiff_vthd3 = itdiff_vthd3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32) + u32AddrOffset), VPSS_PDITDIFFVTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetItdiffVthd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 itdiff_vthd2)
{
    U_VPSS_PDITDIFFVTHD VPSS_PDITDIFFVTHD;

    VPSS_PDITDIFFVTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32) + u32AddrOffset));
    VPSS_PDITDIFFVTHD.bits.itdiff_vthd2 = itdiff_vthd2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32) + u32AddrOffset), VPSS_PDITDIFFVTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetItdiffVthd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 itdiff_vthd1)
{
    U_VPSS_PDITDIFFVTHD VPSS_PDITDIFFVTHD;

    VPSS_PDITDIFFVTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32) + u32AddrOffset));
    VPSS_PDITDIFFVTHD.bits.itdiff_vthd1 = itdiff_vthd1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32) + u32AddrOffset), VPSS_PDITDIFFVTHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetItdiffVthd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 itdiff_vthd0)
{
    U_VPSS_PDITDIFFVTHD VPSS_PDITDIFFVTHD;

    VPSS_PDITDIFFVTHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32) + u32AddrOffset));
    VPSS_PDITDIFFVTHD.bits.itdiff_vthd0 = itdiff_vthd0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDITDIFFVTHD.u32) + u32AddrOffset), VPSS_PDITDIFFVTHD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetLasiMovThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_mov_thd)
{
    U_VPSS_PDLASITHD VPSS_PDLASITHD;

    VPSS_PDLASITHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDLASITHD.u32) + u32AddrOffset));
    VPSS_PDLASITHD.bits.lasi_mov_thd = lasi_mov_thd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDLASITHD.u32) + u32AddrOffset), VPSS_PDLASITHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLasiEdgeThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_edge_thd)
{
    U_VPSS_PDLASITHD VPSS_PDLASITHD;

    VPSS_PDLASITHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDLASITHD.u32) + u32AddrOffset));
    VPSS_PDLASITHD.bits.lasi_edge_thd = lasi_edge_thd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDLASITHD.u32) + u32AddrOffset), VPSS_PDLASITHD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLasiCoringThd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_coring_thd)
{
    U_VPSS_PDLASITHD VPSS_PDLASITHD;

    VPSS_PDLASITHD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDLASITHD.u32) + u32AddrOffset));
    VPSS_PDLASITHD.bits.lasi_coring_thd = lasi_coring_thd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDLASITHD.u32) + u32AddrOffset), VPSS_PDLASITHD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetLasiTxtCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_txt_coring)
{
    U_VPSS_PDLASIMODE0COEF VPSS_PDLASIMODE0COEF;

    VPSS_PDLASIMODE0COEF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDLASIMODE0COEF.u32) + u32AddrOffset));
    VPSS_PDLASIMODE0COEF.bits.lasi_txt_coring = lasi_txt_coring;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDLASIMODE0COEF.u32) + u32AddrOffset), VPSS_PDLASIMODE0COEF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLasiTxtAlpha(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_txt_alpha)
{
    U_VPSS_PDLASIMODE0COEF VPSS_PDLASIMODE0COEF;

    VPSS_PDLASIMODE0COEF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDLASIMODE0COEF.u32) + u32AddrOffset));
    VPSS_PDLASIMODE0COEF.bits.lasi_txt_alpha = lasi_txt_alpha;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDLASIMODE0COEF.u32) + u32AddrOffset), VPSS_PDLASIMODE0COEF.u32);

    return ;
}



HI_VOID VPSS_Sys_SetLasiTxtThd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_txt_thd3)
{
    U_VPSS_PDLASIMODE1COEF VPSS_PDLASIMODE1COEF;

    VPSS_PDLASIMODE1COEF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32) + u32AddrOffset));
    VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd3 = lasi_txt_thd3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32) + u32AddrOffset), VPSS_PDLASIMODE1COEF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLasiTxtThd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_txt_thd2)
{
    U_VPSS_PDLASIMODE1COEF VPSS_PDLASIMODE1COEF;

    VPSS_PDLASIMODE1COEF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32) + u32AddrOffset));
    VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd2 = lasi_txt_thd2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32) + u32AddrOffset), VPSS_PDLASIMODE1COEF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLasiTxtThd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_txt_thd1)
{
    U_VPSS_PDLASIMODE1COEF VPSS_PDLASIMODE1COEF;

    VPSS_PDLASIMODE1COEF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32) + u32AddrOffset));
    VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd1 = lasi_txt_thd1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32) + u32AddrOffset), VPSS_PDLASIMODE1COEF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLasiTxtThd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lasi_txt_thd0)
{
    U_VPSS_PDLASIMODE1COEF VPSS_PDLASIMODE1COEF;

    VPSS_PDLASIMODE1COEF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32) + u32AddrOffset));
    VPSS_PDLASIMODE1COEF.bits.lasi_txt_thd0 = lasi_txt_thd0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDLASIMODE1COEF.u32) + u32AddrOffset), VPSS_PDLASIMODE1COEF.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRegion1YStt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 region1_y_stt)
{
    U_VPSS_PDREGION VPSS_PDREGION;

    VPSS_PDREGION.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDREGION.u32) + u32AddrOffset));
    VPSS_PDREGION.bits.region1_y_stt = region1_y_stt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDREGION.u32) + u32AddrOffset), VPSS_PDREGION.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRegion1YEnd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 region1_y_end)
{
    U_VPSS_PDREGION VPSS_PDREGION;

    VPSS_PDREGION.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_PDREGION.u32) + u32AddrOffset));
    VPSS_PDREGION.bits.region1_y_end = region1_y_end;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_PDREGION.u32) + u32AddrOffset), VPSS_PDREGION.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKRgdifycore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_rgdifycore)
{
    U_VPSS_MCDI_RGDIFY VPSS_MCDI_RGDIFY;

    VPSS_MCDI_RGDIFY.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32) + u32AddrOffset));
    VPSS_MCDI_RGDIFY.bits.k_rgdifycore = k_rgdifycore;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32) + u32AddrOffset), VPSS_MCDI_RGDIFY.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGRgdifycore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g_rgdifycore)
{
    U_VPSS_MCDI_RGDIFY VPSS_MCDI_RGDIFY;

    VPSS_MCDI_RGDIFY.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32) + u32AddrOffset));
    VPSS_MCDI_RGDIFY.bits.g_rgdifycore = g_rgdifycore;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32) + u32AddrOffset), VPSS_MCDI_RGDIFY.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreRgdify(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_rgdify)
{
    U_VPSS_MCDI_RGDIFY VPSS_MCDI_RGDIFY;

    VPSS_MCDI_RGDIFY.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32) + u32AddrOffset));
    VPSS_MCDI_RGDIFY.bits.core_rgdify = core_rgdify;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32) + u32AddrOffset), VPSS_MCDI_RGDIFY.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLmtRgdify(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lmt_rgdify)
{
    U_VPSS_MCDI_RGDIFY VPSS_MCDI_RGDIFY;

    VPSS_MCDI_RGDIFY.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32) + u32AddrOffset));
    VPSS_MCDI_RGDIFY.bits.lmt_rgdify = lmt_rgdify;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGDIFY.u32) + u32AddrOffset), VPSS_MCDI_RGDIFY.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCoefSadlpf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 coef_sadlpf)
{
    U_VPSS_MCDI_RGSAD VPSS_MCDI_RGSAD;

    VPSS_MCDI_RGSAD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGSAD.u32) + u32AddrOffset));
    VPSS_MCDI_RGSAD.bits.coef_sadlpf = coef_sadlpf;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGSAD.u32) + u32AddrOffset), VPSS_MCDI_RGSAD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKmvRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 kmv_rgsad)
{
    U_VPSS_MCDI_RGSAD VPSS_MCDI_RGSAD;

    VPSS_MCDI_RGSAD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGSAD.u32) + u32AddrOffset));
    VPSS_MCDI_RGSAD.bits.kmv_rgsad = kmv_rgsad;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGSAD.u32) + u32AddrOffset), VPSS_MCDI_RGSAD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKTpdifRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_tpdif_rgsad)
{
    U_VPSS_MCDI_RGSAD VPSS_MCDI_RGSAD;

    VPSS_MCDI_RGSAD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGSAD.u32) + u32AddrOffset));
    VPSS_MCDI_RGSAD.bits.k_tpdif_rgsad = k_tpdif_rgsad;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGSAD.u32) + u32AddrOffset), VPSS_MCDI_RGSAD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGTpdifRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g_tpdif_rgsad)
{
    U_VPSS_MCDI_RGSAD VPSS_MCDI_RGSAD;

    VPSS_MCDI_RGSAD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGSAD.u32) + u32AddrOffset));
    VPSS_MCDI_RGSAD.bits.g_tpdif_rgsad = g_tpdif_rgsad;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGSAD.u32) + u32AddrOffset), VPSS_MCDI_RGSAD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetThmagRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 thmag_rgmv)
{
    U_VPSS_MCDI_RGMV VPSS_MCDI_RGMV;

    VPSS_MCDI_RGMV.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMV.u32) + u32AddrOffset));
    VPSS_MCDI_RGMV.bits.thmag_rgmv = thmag_rgmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMV.u32) + u32AddrOffset), VPSS_MCDI_RGMV.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThSaddifRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_saddif_rgmv)
{
    U_VPSS_MCDI_RGMV VPSS_MCDI_RGMV;

    VPSS_MCDI_RGMV.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMV.u32) + u32AddrOffset));
    VPSS_MCDI_RGMV.bits.th_saddif_rgmv = th_saddif_rgmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMV.u32) + u32AddrOffset), VPSS_MCDI_RGMV.u32);

    return ;
}


HI_VOID VPSS_Sys_SetTh0mvsadRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_0mvsad_rgmv)
{
    U_VPSS_MCDI_RGMV VPSS_MCDI_RGMV;

    VPSS_MCDI_RGMV.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMV.u32) + u32AddrOffset));
    VPSS_MCDI_RGMV.bits.th_0mvsad_rgmv = th_0mvsad_rgmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMV.u32) + u32AddrOffset), VPSS_MCDI_RGMV.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCoreMagRg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_mag_rg)
{
    U_VPSS_MCDI_RGMAG0 VPSS_MCDI_RGMAG0;

    VPSS_MCDI_RGMAG0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMAG0.u32) + u32AddrOffset));
    VPSS_MCDI_RGMAG0.bits.core_mag_rg = core_mag_rg;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMAG0.u32) + u32AddrOffset), VPSS_MCDI_RGMAG0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetLmtMagRg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lmt_mag_rg)
{
    U_VPSS_MCDI_RGMAG0 VPSS_MCDI_RGMAG0;

    VPSS_MCDI_RGMAG0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMAG0.u32) + u32AddrOffset));
    VPSS_MCDI_RGMAG0.bits.lmt_mag_rg = lmt_mag_rg;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMAG0.u32) + u32AddrOffset), VPSS_MCDI_RGMAG0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCoreMvRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_mv_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMAG1.bits.core_mv_rgmvls = core_mv_rgmvls;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKMvRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_mv_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMAG1.bits.k_mv_rgmvls = k_mv_rgmvls;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreMagRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_mag_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMAG1.bits.core_mag_rgmvls = core_mag_rgmvls;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKMagRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_mag_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMAG1.bits.k_mag_rgmvls = k_mag_rgmvls;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThMvadjRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_mvadj_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMAG1.bits.th_mvadj_rgmvls = th_mvadj_rgmvls;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset), VPSS_MCDI_RGMAG1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEnMvadjRgmvls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 en_mvadj_rgmvls)
{
    U_VPSS_MCDI_RGMAG1 VPSS_MCDI_RGMAG1;

    VPSS_MCDI_RGMAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMAG1.bits.en_mvadj_rgmvls = en_mvadj_rgmvls;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMAG1.u32) + u32AddrOffset), VPSS_MCDI_RGMAG1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKSadRgls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_sad_rgls)
{
    U_VPSS_MCDI_RGLS VPSS_MCDI_RGLS;

    VPSS_MCDI_RGLS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGLS.u32) + u32AddrOffset));
    VPSS_MCDI_RGLS.bits.k_sad_rgls = k_sad_rgls;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGLS.u32) + u32AddrOffset), VPSS_MCDI_RGLS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThMagRgls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_mag_rgls)
{
    U_VPSS_MCDI_RGLS VPSS_MCDI_RGLS;

    VPSS_MCDI_RGLS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGLS.u32) + u32AddrOffset));
    VPSS_MCDI_RGLS.bits.th_mag_rgls = th_mag_rgls;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGLS.u32) + u32AddrOffset), VPSS_MCDI_RGLS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThSadRgls(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_sad_rgls)
{
    U_VPSS_MCDI_RGLS VPSS_MCDI_RGLS;

    VPSS_MCDI_RGLS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGLS.u32) + u32AddrOffset));
    VPSS_MCDI_RGLS.bits.th_sad_rgls = th_sad_rgls;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGLS.u32) + u32AddrOffset), VPSS_MCDI_RGLS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKSadcoreRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_sadcore_rgmv)
{
    U_VPSS_MCDI_RGLS VPSS_MCDI_RGLS;

    VPSS_MCDI_RGLS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGLS.u32) + u32AddrOffset));
    VPSS_MCDI_RGLS.bits.k_sadcore_rgmv = k_sadcore_rgmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGLS.u32) + u32AddrOffset), VPSS_MCDI_RGLS.u32);

    return ;
}



HI_VOID VPSS_Sys_SetForceMven(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 force_mven)
{
    U_VPSS_MCDI_SEL VPSS_MCDI_SEL;

    VPSS_MCDI_SEL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_SEL.u32) + u32AddrOffset));
    VPSS_MCDI_SEL.bits.force_mven = force_mven;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_SEL.u32) + u32AddrOffset), VPSS_MCDI_SEL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetForceMvx(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 force_mvx)
{
    U_VPSS_MCDI_SEL VPSS_MCDI_SEL;

    VPSS_MCDI_SEL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_SEL.u32) + u32AddrOffset));
    VPSS_MCDI_SEL.bits.force_mvx = force_mvx;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_SEL.u32) + u32AddrOffset), VPSS_MCDI_SEL.u32);

    return ;
}



HI_VOID VPSS_Sys_SetThBlkmvxMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_blkmvx_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset));
    VPSS_MCDI_DLT0.bits.th_blkmvx_mvdlt = th_blkmvx_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset), VPSS_MCDI_DLT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThRgmvxMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_rgmvx_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset));
    VPSS_MCDI_DLT0.bits.th_rgmvx_mvdlt = th_rgmvx_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset), VPSS_MCDI_DLT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThLsMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_ls_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset));
    VPSS_MCDI_DLT0.bits.th_ls_mvdlt = th_ls_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset), VPSS_MCDI_DLT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThVblkdistMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_vblkdist_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset));
    VPSS_MCDI_DLT0.bits.th_vblkdist_mvdlt = th_vblkdist_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset), VPSS_MCDI_DLT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThHblkdistMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_hblkdist_mvdlt)
{
    U_VPSS_MCDI_DLT0 VPSS_MCDI_DLT0;

    VPSS_MCDI_DLT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset));
    VPSS_MCDI_DLT0.bits.th_hblkdist_mvdlt = th_hblkdist_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT0.u32) + u32AddrOffset), VPSS_MCDI_DLT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKSadcoreMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_sadcore_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset));
    VPSS_MCDI_DLT1.bits.k_sadcore_mvdlt = k_sadcore_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset), VPSS_MCDI_DLT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThMagMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_mag_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset));
    VPSS_MCDI_DLT1.bits.th_mag_mvdlt = th_mag_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset), VPSS_MCDI_DLT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGMagMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g_mag_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset));
    VPSS_MCDI_DLT1.bits.g_mag_mvdlt = g_mag_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset), VPSS_MCDI_DLT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThlSadMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 thl_sad_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset));
    VPSS_MCDI_DLT1.bits.thl_sad_mvdlt = thl_sad_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset), VPSS_MCDI_DLT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThhSadMvdlt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 thh_sad_mvdlt)
{
    U_VPSS_MCDI_DLT1 VPSS_MCDI_DLT1;

    VPSS_MCDI_DLT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset));
    VPSS_MCDI_DLT1.bits.thh_sad_mvdlt = thh_sad_mvdlt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DLT1.u32) + u32AddrOffset), VPSS_MCDI_DLT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKRglsw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_rglsw)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW0.bits.k_rglsw = k_rglsw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset), VPSS_MCDI_RGMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKSimimvw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_simimvw)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW0.bits.k_simimvw = k_simimvw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset), VPSS_MCDI_RGMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGhCoreSimimv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 gh_core_simimv)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW0.bits.gh_core_simimv = gh_core_simimv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset), VPSS_MCDI_RGMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGlCoreSimimv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 gl_core_simimv)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW0.bits.gl_core_simimv = gl_core_simimv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset), VPSS_MCDI_RGMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKCoreSimimv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_core_simimv)
{
    U_VPSS_MCDI_RGMCW0 VPSS_MCDI_RGMCW0;

    VPSS_MCDI_RGMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW0.bits.k_core_simimv = k_core_simimv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW0.u32) + u32AddrOffset), VPSS_MCDI_RGMCW0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKCoreVsaddif(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_core_vsaddif)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW1.bits.k_core_vsaddif = k_core_vsaddif;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKRgsadadjMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_rgsadadj_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW1.bits.k_rgsadadj_mcw = k_rgsadadj_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreRgsadadjMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_rgsadadj_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW1.bits.core_rgsadadj_mcw = core_rgsadadj_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKMvyMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_mvy_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW1.bits.k_mvy_mcw = k_mvy_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreMvyMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_mvy_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW1.bits.core_mvy_mcw = core_mvy_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset), VPSS_MCDI_RGMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRgtbEnMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rgtb_en_mcw)
{
    U_VPSS_MCDI_RGMCW1 VPSS_MCDI_RGMCW1;

    VPSS_MCDI_RGMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW1.bits.rgtb_en_mcw = rgtb_en_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW1.u32) + u32AddrOffset), VPSS_MCDI_RGMCW1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCoreRgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW2.bits.core_rgmag_mcw = core_rgmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset), VPSS_MCDI_RGMCW2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetModeRgysadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mode_rgysad_mcw)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW2.bits.mode_rgysad_mcw = mode_rgysad_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset), VPSS_MCDI_RGMCW2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKVsaddifw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_vsaddifw)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW2.bits.k_vsaddifw = k_vsaddifw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset), VPSS_MCDI_RGMCW2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGhCoreVsadDif(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 gh_core_vsad_dif)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW2.bits.gh_core_vsad_dif = gh_core_vsad_dif;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset), VPSS_MCDI_RGMCW2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGlCoreVsaddif(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 gl_core_vsaddif)
{
    U_VPSS_MCDI_RGMCW2 VPSS_MCDI_RGMCW2;

    VPSS_MCDI_RGMCW2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW2.bits.gl_core_vsaddif = gl_core_vsaddif;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW2.u32) + u32AddrOffset), VPSS_MCDI_RGMCW2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetG0RgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW3 VPSS_MCDI_RGMCW3;

    VPSS_MCDI_RGMCW3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW3.bits.g0_rgmag_mcw = g0_rgmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32) + u32AddrOffset), VPSS_MCDI_RGMCW3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0RgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW3 VPSS_MCDI_RGMCW3;

    VPSS_MCDI_RGMCW3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW3.bits.k0_rgmag_mcw = k0_rgmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32) + u32AddrOffset), VPSS_MCDI_RGMCW3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0RgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW3 VPSS_MCDI_RGMCW3;

    VPSS_MCDI_RGMCW3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW3.bits.x0_rgmag_mcw = x0_rgmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW3.u32) + u32AddrOffset), VPSS_MCDI_RGMCW3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetX0RgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW4 VPSS_MCDI_RGMCW4;

    VPSS_MCDI_RGMCW4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW4.bits.x0_rgsad_mcw = x0_rgsad_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32) + u32AddrOffset), VPSS_MCDI_RGMCW4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreRgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW4 VPSS_MCDI_RGMCW4;

    VPSS_MCDI_RGMCW4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW4.bits.core_rgsad_mcw = core_rgsad_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32) + u32AddrOffset), VPSS_MCDI_RGMCW4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK1RgmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_rgmag_mcw)
{
    U_VPSS_MCDI_RGMCW4 VPSS_MCDI_RGMCW4;

    VPSS_MCDI_RGMCW4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW4.bits.k1_rgmag_mcw = k1_rgmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW4.u32) + u32AddrOffset), VPSS_MCDI_RGMCW4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetK1RgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW5 VPSS_MCDI_RGMCW5;

    VPSS_MCDI_RGMCW5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW5.bits.k1_rgsad_mcw = k1_rgsad_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32) + u32AddrOffset), VPSS_MCDI_RGMCW5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG0RgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW5 VPSS_MCDI_RGMCW5;

    VPSS_MCDI_RGMCW5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW5.bits.g0_rgsad_mcw = g0_rgsad_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32) + u32AddrOffset), VPSS_MCDI_RGMCW5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0RgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW5 VPSS_MCDI_RGMCW5;

    VPSS_MCDI_RGMCW5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW5.bits.k0_rgsad_mcw = k0_rgsad_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW5.u32) + u32AddrOffset), VPSS_MCDI_RGMCW5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKRgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW6 VPSS_MCDI_RGMCW6;

    VPSS_MCDI_RGMCW6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW6.bits.k_rgsad_mcw = k_rgsad_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32) + u32AddrOffset), VPSS_MCDI_RGMCW6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetXRgsadMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x_rgsad_mcw)
{
    U_VPSS_MCDI_RGMCW6 VPSS_MCDI_RGMCW6;

    VPSS_MCDI_RGMCW6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW6.bits.x_rgsad_mcw = x_rgsad_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32) + u32AddrOffset), VPSS_MCDI_RGMCW6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0SmrgMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_smrg_mcw)
{
    U_VPSS_MCDI_RGMCW6 VPSS_MCDI_RGMCW6;

    VPSS_MCDI_RGMCW6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW6.bits.k0_smrg_mcw = k0_smrg_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32) + u32AddrOffset), VPSS_MCDI_RGMCW6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0SmrgMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_smrg_mcw)
{
    U_VPSS_MCDI_RGMCW6 VPSS_MCDI_RGMCW6;

    VPSS_MCDI_RGMCW6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32) + u32AddrOffset));
    VPSS_MCDI_RGMCW6.bits.x0_smrg_mcw = x0_smrg_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_RGMCW6.u32) + u32AddrOffset), VPSS_MCDI_RGMCW6.u32);

    return ;
}



HI_VOID VPSS_Sys_SetK1TpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW0 VPSS_MCDI_TPMCW0;

    VPSS_MCDI_TPMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_TPMCW0.bits.k1_tpmvdist_mcw = k1_tpmvdist_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32) + u32AddrOffset), VPSS_MCDI_TPMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG0TpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW0 VPSS_MCDI_TPMCW0;

    VPSS_MCDI_TPMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_TPMCW0.bits.g0_tpmvdist_mcw = g0_tpmvdist_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32) + u32AddrOffset), VPSS_MCDI_TPMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0TpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW0 VPSS_MCDI_TPMCW0;

    VPSS_MCDI_TPMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_TPMCW0.bits.k0_tpmvdist_mcw = k0_tpmvdist_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32) + u32AddrOffset), VPSS_MCDI_TPMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0TpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW0 VPSS_MCDI_TPMCW0;

    VPSS_MCDI_TPMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_TPMCW0.bits.x0_tpmvdist_mcw = x0_tpmvdist_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_TPMCW0.u32) + u32AddrOffset), VPSS_MCDI_TPMCW0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKCoreTpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_core_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW1 VPSS_MCDI_TPMCW1;

    VPSS_MCDI_TPMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_TPMCW1.bits.k_core_tpmvdist_mcw = k_core_tpmvdist_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32) + u32AddrOffset), VPSS_MCDI_TPMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBCoreTpmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 b_core_tpmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW1 VPSS_MCDI_TPMCW1;

    VPSS_MCDI_TPMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_TPMCW1.bits.b_core_tpmvdist_mcw = b_core_tpmvdist_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32) + u32AddrOffset), VPSS_MCDI_TPMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKAvgmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_avgmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW1 VPSS_MCDI_TPMCW1;

    VPSS_MCDI_TPMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_TPMCW1.bits.k_avgmvdist_mcw = k_avgmvdist_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32) + u32AddrOffset), VPSS_MCDI_TPMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKMinmvdistMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_minmvdist_mcw)
{
    U_VPSS_MCDI_TPMCW1 VPSS_MCDI_TPMCW1;

    VPSS_MCDI_TPMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_TPMCW1.bits.k_minmvdist_mcw = k_minmvdist_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_TPMCW1.u32) + u32AddrOffset), VPSS_MCDI_TPMCW1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKTbdifMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_tbdif_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW0.bits.k_tbdif_mcw = k_tbdif_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0MaxMagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_max_mag_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW0.bits.k0_max_mag_mcw = k0_max_mag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK1MaxMagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_max_mag_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW0.bits.k1_max_mag_mcw = k1_max_mag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKMaxDifMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_max_dif_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW0.bits.k_max_dif_mcw = k_max_dif_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKMaxCoreMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_max_core_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW0.bits.k_max_core_mcw = k_max_core_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKDifvcoreMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_difvcore_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW0.bits.k_difvcore_mcw = k_difvcore_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKDifhcoreMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_difhcore_mcw)
{
    U_VPSS_MCDI_WNDMCW0 VPSS_MCDI_WNDMCW0;

    VPSS_MCDI_WNDMCW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW0.bits.k_difhcore_mcw = k_difhcore_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW0.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetK1MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW1.bits.k1_mag_wnd_mcw = k1_mag_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG0MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW1.bits.g0_mag_wnd_mcw = g0_mag_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW1.bits.k0_mag_wnd_mcw = k0_mag_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW1.bits.x0_mag_wnd_mcw = x0_mag_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKTbmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_tbmag_mcw)
{
    U_VPSS_MCDI_WNDMCW1 VPSS_MCDI_WNDMCW1;

    VPSS_MCDI_WNDMCW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW1.bits.k_tbmag_mcw = k_tbmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW1.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetG0SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW2 VPSS_MCDI_WNDMCW2;

    VPSS_MCDI_WNDMCW2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW2.bits.g0_sad_wnd_mcw = g0_sad_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW2 VPSS_MCDI_WNDMCW2;

    VPSS_MCDI_WNDMCW2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW2.bits.k0_sad_wnd_mcw = k0_sad_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW2 VPSS_MCDI_WNDMCW2;

    VPSS_MCDI_WNDMCW2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW2.bits.x0_sad_wnd_mcw = x0_sad_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG1MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g1_mag_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW2 VPSS_MCDI_WNDMCW2;

    VPSS_MCDI_WNDMCW2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW2.bits.g1_mag_wnd_mcw = g1_mag_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW2.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetG1SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g1_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW3 VPSS_MCDI_WNDMCW3;

    VPSS_MCDI_WNDMCW3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW3.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW3.bits.g1_sad_wnd_mcw = g1_sad_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW3.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK1SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_sad_wnd_mcw)
{
    U_VPSS_MCDI_WNDMCW3 VPSS_MCDI_WNDMCW3;

    VPSS_MCDI_WNDMCW3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_WNDMCW3.u32) + u32AddrOffset));
    VPSS_MCDI_WNDMCW3.bits.k1_sad_wnd_mcw = k1_sad_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_WNDMCW3.u32) + u32AddrOffset), VPSS_MCDI_WNDMCW3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetBHvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 b_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT0.bits.b_hvdif_dw = b_hvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBBhvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 b_bhvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT0.bits.b_bhvdif_dw = b_bhvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKBhvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_bhvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT0.bits.k_bhvdif_dw = k_bhvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreBhvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_bhvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT0.bits.core_bhvdif_dw = core_bhvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGainLpfDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 gain_lpf_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT0.bits.gain_lpf_dw = gain_lpf_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKMaxHvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_max_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT0 VPSS_MCDI_VERTWEIGHT0;

    VPSS_MCDI_VERTWEIGHT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT0.bits.k_max_hvdif_dw = k_max_hvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT0.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetBMvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 b_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT1 VPSS_MCDI_VERTWEIGHT1;

    VPSS_MCDI_VERTWEIGHT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT1.bits.b_mv_dw = b_mv_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreMvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT1 VPSS_MCDI_VERTWEIGHT1;

    VPSS_MCDI_VERTWEIGHT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT1.bits.core_mv_dw = core_mv_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKDifvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_difv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT1 VPSS_MCDI_VERTWEIGHT1;

    VPSS_MCDI_VERTWEIGHT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT1.bits.k_difv_dw = k_difv_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreHvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT1 VPSS_MCDI_VERTWEIGHT1;

    VPSS_MCDI_VERTWEIGHT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT1.bits.core_hvdif_dw = core_hvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT1.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetK1HvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT2 VPSS_MCDI_VERTWEIGHT2;

    VPSS_MCDI_VERTWEIGHT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT2.bits.k1_hvdif_dw = k1_hvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG0HvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT2 VPSS_MCDI_VERTWEIGHT2;

    VPSS_MCDI_VERTWEIGHT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT2.bits.g0_hvdif_dw = g0_hvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0HvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT2 VPSS_MCDI_VERTWEIGHT2;

    VPSS_MCDI_VERTWEIGHT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT2.bits.k0_hvdif_dw = k0_hvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0HvdifDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_hvdif_dw)
{
    U_VPSS_MCDI_VERTWEIGHT2 VPSS_MCDI_VERTWEIGHT2;

    VPSS_MCDI_VERTWEIGHT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT2.bits.x0_hvdif_dw = x0_hvdif_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT2.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetK1MvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT3 VPSS_MCDI_VERTWEIGHT3;

    VPSS_MCDI_VERTWEIGHT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT3.bits.k1_mv_dw = k1_mv_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG0MvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT3 VPSS_MCDI_VERTWEIGHT3;

    VPSS_MCDI_VERTWEIGHT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT3.bits.g0_mv_dw = g0_mv_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0MvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT3 VPSS_MCDI_VERTWEIGHT3;

    VPSS_MCDI_VERTWEIGHT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT3.bits.k0_mv_dw = k0_mv_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0MvDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_mv_dw)
{
    U_VPSS_MCDI_VERTWEIGHT3 VPSS_MCDI_VERTWEIGHT3;

    VPSS_MCDI_VERTWEIGHT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT3.bits.x0_mv_dw = x0_mv_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT3.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetK1MtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT4 VPSS_MCDI_VERTWEIGHT4;

    VPSS_MCDI_VERTWEIGHT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT4.bits.k1_mt_dw = k1_mt_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG0MtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT4 VPSS_MCDI_VERTWEIGHT4;

    VPSS_MCDI_VERTWEIGHT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT4.bits.g0_mt_dw = g0_mt_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0MtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT4 VPSS_MCDI_VERTWEIGHT4;

    VPSS_MCDI_VERTWEIGHT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT4.bits.k0_mt_dw = k0_mt_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0MtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT4 VPSS_MCDI_VERTWEIGHT4;

    VPSS_MCDI_VERTWEIGHT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT4.bits.x0_mt_dw = x0_mt_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT4.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetBMtDw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 b_mt_dw)
{
    U_VPSS_MCDI_VERTWEIGHT5 VPSS_MCDI_VERTWEIGHT5;

    VPSS_MCDI_VERTWEIGHT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT5.bits.b_mt_dw = b_mt_dw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK1MvMt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_mv_mt)
{
    U_VPSS_MCDI_VERTWEIGHT5 VPSS_MCDI_VERTWEIGHT5;

    VPSS_MCDI_VERTWEIGHT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT5.bits.k1_mv_mt = k1_mv_mt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0MvMt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_mv_mt)
{
    U_VPSS_MCDI_VERTWEIGHT5 VPSS_MCDI_VERTWEIGHT5;

    VPSS_MCDI_VERTWEIGHT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT5.bits.x0_mv_mt = x0_mv_mt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG0MvMt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_mv_mt)
{
    U_VPSS_MCDI_VERTWEIGHT5 VPSS_MCDI_VERTWEIGHT5;

    VPSS_MCDI_VERTWEIGHT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32) + u32AddrOffset));
    VPSS_MCDI_VERTWEIGHT5.bits.g0_mv_mt = g0_mv_mt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_VERTWEIGHT5.u32) + u32AddrOffset), VPSS_MCDI_VERTWEIGHT5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMclpfMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mclpf_mode)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset));
    VPSS_MCDI_MC0.bits.mclpf_mode = mclpf_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKPxlmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_pxlmag_mcw)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset));
    VPSS_MCDI_MC0.bits.k_pxlmag_mcw = k_pxlmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetXPxlmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x_pxlmag_mcw)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset));
    VPSS_MCDI_MC0.bits.x_pxlmag_mcw = x_pxlmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRsPxlmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rs_pxlmag_mcw)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset));
    VPSS_MCDI_MC0.bits.rs_pxlmag_mcw = rs_pxlmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGainMclpfh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 gain_mclpfh)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset));
    VPSS_MCDI_MC0.bits.gain_mclpfh = gain_mclpfh;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGainDnMclpfv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 gain_dn_mclpfv)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset));
    VPSS_MCDI_MC0.bits.gain_dn_mclpfv = gain_dn_mclpfv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset), VPSS_MCDI_MC0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGainUpMclpfv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 gain_up_mclpfv)
{
    U_VPSS_MCDI_MC0 VPSS_MCDI_MC0;

    VPSS_MCDI_MC0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset));
    VPSS_MCDI_MC0.bits.gain_up_mclpfv = gain_up_mclpfv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC0.u32) + u32AddrOffset), VPSS_MCDI_MC0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetGPxlmagMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g_pxlmag_mcw)
{
    U_VPSS_MCDI_MC1 VPSS_MCDI_MC1;

    VPSS_MCDI_MC1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC1.u32) + u32AddrOffset));
    VPSS_MCDI_MC1.bits.g_pxlmag_mcw = g_pxlmag_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC1.u32) + u32AddrOffset), VPSS_MCDI_MC1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKCVertw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_c_vertw)
{
    U_VPSS_MCDI_MC2 VPSS_MCDI_MC2;

    VPSS_MCDI_MC2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC2.u32) + u32AddrOffset));
    VPSS_MCDI_MC2.bits.k_c_vertw = k_c_vertw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC2.u32) + u32AddrOffset), VPSS_MCDI_MC2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKYVertw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_y_vertw)
{
    U_VPSS_MCDI_MC2 VPSS_MCDI_MC2;

    VPSS_MCDI_MC2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC2.u32) + u32AddrOffset));
    VPSS_MCDI_MC2.bits.k_y_vertw = k_y_vertw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC2.u32) + u32AddrOffset), VPSS_MCDI_MC2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKFstmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_fstmt_mc)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset));
    VPSS_MCDI_MC3.bits.k_fstmt_mc = k_fstmt_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetXFstmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x_fstmt_mc)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset));
    VPSS_MCDI_MC3.bits.x_fstmt_mc = x_fstmt_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK1MvMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_mv_mc)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset));
    VPSS_MCDI_MC3.bits.k1_mv_mc = k1_mv_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0MvMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_mv_mc)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset));
    VPSS_MCDI_MC3.bits.x0_mv_mc = x0_mv_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBdvMcpos(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bdv_mcpos)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset));
    VPSS_MCDI_MC3.bits.bdv_mcpos = bdv_mcpos;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBdhMcpos(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bdh_mcpos)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset));
    VPSS_MCDI_MC3.bits.bdh_mcpos = bdh_mcpos;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset), VPSS_MCDI_MC3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKDelta(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_delta)
{
    U_VPSS_MCDI_MC3 VPSS_MCDI_MC3;

    VPSS_MCDI_MC3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset));
    VPSS_MCDI_MC3.bits.k_delta = k_delta;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC3.u32) + u32AddrOffset), VPSS_MCDI_MC3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKHfcoreMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_hfcore_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset));
    VPSS_MCDI_MC4.bits.k_hfcore_mc = k_hfcore_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetXHfcoreMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x_hfcore_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset));
    VPSS_MCDI_MC4.bits.x_hfcore_mc = x_hfcore_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGSlmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g_slmt_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset));
    VPSS_MCDI_MC4.bits.g_slmt_mc = g_slmt_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKSlmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_slmt_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset));
    VPSS_MCDI_MC4.bits.k_slmt_mc = k_slmt_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetXSlmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x_slmt_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset));
    VPSS_MCDI_MC4.bits.x_slmt_mc = x_slmt_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset), VPSS_MCDI_MC4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGFstmtMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g_fstmt_mc)
{
    U_VPSS_MCDI_MC4 VPSS_MCDI_MC4;

    VPSS_MCDI_MC4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset));
    VPSS_MCDI_MC4.bits.g_fstmt_mc = g_fstmt_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC4.u32) + u32AddrOffset), VPSS_MCDI_MC4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetR0Mc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 r0_mc)
{
    U_VPSS_MCDI_MC5 VPSS_MCDI_MC5;

    VPSS_MCDI_MC5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC5.u32) + u32AddrOffset));
    VPSS_MCDI_MC5.bits.r0_mc = r0_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC5.u32) + u32AddrOffset), VPSS_MCDI_MC5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetC0Mc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 c0_mc)
{
    U_VPSS_MCDI_MC5 VPSS_MCDI_MC5;

    VPSS_MCDI_MC5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC5.u32) + u32AddrOffset));
    VPSS_MCDI_MC5.bits.c0_mc = c0_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC5.u32) + u32AddrOffset), VPSS_MCDI_MC5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGHfcoreMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g_hfcore_mc)
{
    U_VPSS_MCDI_MC5 VPSS_MCDI_MC5;

    VPSS_MCDI_MC5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC5.u32) + u32AddrOffset));
    VPSS_MCDI_MC5.bits.g_hfcore_mc = g_hfcore_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC5.u32) + u32AddrOffset), VPSS_MCDI_MC5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMcmvrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcmvrange)
{
    U_VPSS_MCDI_MC6 VPSS_MCDI_MC6;

    VPSS_MCDI_MC6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC6.u32) + u32AddrOffset));
    VPSS_MCDI_MC6.bits.mcmvrange = mcmvrange;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC6.u32) + u32AddrOffset), VPSS_MCDI_MC6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetR1Mc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 r1_mc)
{
    U_VPSS_MCDI_MC6 VPSS_MCDI_MC6;

    VPSS_MCDI_MC6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC6.u32) + u32AddrOffset));
    VPSS_MCDI_MC6.bits.r1_mc = r1_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC6.u32) + u32AddrOffset), VPSS_MCDI_MC6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetC1Mc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 c1_mc)
{
    U_VPSS_MCDI_MC6 VPSS_MCDI_MC6;

    VPSS_MCDI_MC6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC6.u32) + u32AddrOffset));
    VPSS_MCDI_MC6.bits.c1_mc = c1_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC6.u32) + u32AddrOffset), VPSS_MCDI_MC6.u32);

    return ;
}



HI_VOID VPSS_Sys_SetKFrcountMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_frcount_mc)
{
    U_VPSS_MCDI_MC7 VPSS_MCDI_MC7;

    VPSS_MCDI_MC7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC7.u32) + u32AddrOffset));
    VPSS_MCDI_MC7.bits.k_frcount_mc = k_frcount_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC7.u32) + u32AddrOffset), VPSS_MCDI_MC7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetXFrcountMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x_frcount_mc)
{
    U_VPSS_MCDI_MC7 VPSS_MCDI_MC7;

    VPSS_MCDI_MC7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC7.u32) + u32AddrOffset));
    VPSS_MCDI_MC7.bits.x_frcount_mc = x_frcount_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC7.u32) + u32AddrOffset), VPSS_MCDI_MC7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetScenechangeMc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechange_mc)
{
    U_VPSS_MCDI_MC7 VPSS_MCDI_MC7;

    VPSS_MCDI_MC7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_MC7.u32) + u32AddrOffset));
    VPSS_MCDI_MC7.bits.scenechange_mc = scenechange_mc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_MC7.u32) + u32AddrOffset), VPSS_MCDI_MC7.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMcendc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcendc)
{
    U_VPSS_MCDI_LCDINEW0 VPSS_MCDI_LCDINEW0;

    VPSS_MCDI_LCDINEW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32) + u32AddrOffset));
    VPSS_MCDI_LCDINEW0.bits.mcendc = mcendc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32) + u32AddrOffset), VPSS_MCDI_LCDINEW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcendr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcendr)
{
    U_VPSS_MCDI_LCDINEW0 VPSS_MCDI_LCDINEW0;

    VPSS_MCDI_LCDINEW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32) + u32AddrOffset));
    VPSS_MCDI_LCDINEW0.bits.mcendr = mcendr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32) + u32AddrOffset), VPSS_MCDI_LCDINEW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcstartc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcstartc)
{
    U_VPSS_MCDI_LCDINEW0 VPSS_MCDI_LCDINEW0;

    VPSS_MCDI_LCDINEW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32) + u32AddrOffset));
    VPSS_MCDI_LCDINEW0.bits.mcstartc = mcstartc;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32) + u32AddrOffset), VPSS_MCDI_LCDINEW0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcstartr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcstartr)
{
    U_VPSS_MCDI_LCDINEW0 VPSS_MCDI_LCDINEW0;

    VPSS_MCDI_LCDINEW0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32) + u32AddrOffset));
    VPSS_MCDI_LCDINEW0.bits.mcstartr = mcstartr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_LCDINEW0.u32) + u32AddrOffset), VPSS_MCDI_LCDINEW0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMovegain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 movegain)
{
    U_VPSS_MCDI_LCDINEW1 VPSS_MCDI_LCDINEW1;

    VPSS_MCDI_LCDINEW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32) + u32AddrOffset));
    VPSS_MCDI_LCDINEW1.bits.movegain = movegain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32) + u32AddrOffset), VPSS_MCDI_LCDINEW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMovecorig(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 movecorig)
{
    U_VPSS_MCDI_LCDINEW1 VPSS_MCDI_LCDINEW1;

    VPSS_MCDI_LCDINEW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32) + u32AddrOffset));
    VPSS_MCDI_LCDINEW1.bits.movecorig = movecorig;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32) + u32AddrOffset), VPSS_MCDI_LCDINEW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMovethdl(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 movethdl)
{
    U_VPSS_MCDI_LCDINEW1 VPSS_MCDI_LCDINEW1;

    VPSS_MCDI_LCDINEW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32) + u32AddrOffset));
    VPSS_MCDI_LCDINEW1.bits.movethdl = movethdl;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32) + u32AddrOffset), VPSS_MCDI_LCDINEW1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMovethdh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 movethdh)
{
    U_VPSS_MCDI_LCDINEW1 VPSS_MCDI_LCDINEW1;

    VPSS_MCDI_LCDINEW1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32) + u32AddrOffset));
    VPSS_MCDI_LCDINEW1.bits.movethdh = movethdh;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_LCDINEW1.u32) + u32AddrOffset), VPSS_MCDI_LCDINEW1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMcNumtBlden(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_numt_blden)
{
    U_VPSS_MCDI_NUMT VPSS_MCDI_NUMT;

    VPSS_MCDI_NUMT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_NUMT.u32) + u32AddrOffset));
    VPSS_MCDI_NUMT.bits.mc_numt_blden = mc_numt_blden;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_NUMT.u32) + u32AddrOffset), VPSS_MCDI_NUMT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetNumtGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 numt_gain)
{
    U_VPSS_MCDI_NUMT VPSS_MCDI_NUMT;

    VPSS_MCDI_NUMT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_NUMT.u32) + u32AddrOffset));
    VPSS_MCDI_NUMT.bits.numt_gain = numt_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_NUMT.u32) + u32AddrOffset), VPSS_MCDI_NUMT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetNumtCoring(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 numt_coring)
{
    U_VPSS_MCDI_NUMT VPSS_MCDI_NUMT;

    VPSS_MCDI_NUMT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_NUMT.u32) + u32AddrOffset));
    VPSS_MCDI_NUMT.bits.numt_coring = numt_coring;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_NUMT.u32) + u32AddrOffset), VPSS_MCDI_NUMT.u32);

    return ;
}


HI_VOID VPSS_Sys_SetNumtLpfEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 numt_lpf_en)
{
    U_VPSS_MCDI_NUMT VPSS_MCDI_NUMT;

    VPSS_MCDI_NUMT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_NUMT.u32) + u32AddrOffset));
    VPSS_MCDI_NUMT.bits.numt_lpf_en = numt_lpf_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_NUMT.u32) + u32AddrOffset), VPSS_MCDI_NUMT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetK1Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_hw)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD0.bits.k1_hw = k1_hw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_hw)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD0.bits.k0_hw = k0_hw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreHfvline(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_hfvline)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD0.bits.core_hfvline = core_hfvline;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK1Hfvline(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_hfvline)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD0.bits.k1_hfvline = k1_hfvline;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0Hfvline(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_hfvline)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD0.bits.k0_hfvline = k0_hfvline;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset), VPSS_MCDI_S3ADD0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCoreRglsw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core_rglsw)
{
    U_VPSS_MCDI_S3ADD0 VPSS_MCDI_S3ADD0;

    VPSS_MCDI_S3ADD0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD0.bits.core_rglsw = core_rglsw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD0.u32) + u32AddrOffset), VPSS_MCDI_S3ADD0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetGDifcoreMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g_difcore_mcw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD1.bits.g_difcore_mcw = g_difcore_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetSubpixMcEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 subpix_mc_en)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD1.bits.subpix_mc_en = subpix_mc_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCore1Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 core1_hw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD1.bits.core1_hw = core1_hw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKCore0Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_core0_hw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD1.bits.k_core0_hw = k_core0_hw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBCore0Hw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 b_core0_hw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD1.bits.b_core0_hw = b_core0_hw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset), VPSS_MCDI_S3ADD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGHw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g_hw)
{
    U_VPSS_MCDI_S3ADD1 VPSS_MCDI_S3ADD1;

    VPSS_MCDI_S3ADD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD1.bits.g_hw = g_hw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD1.u32) + u32AddrOffset), VPSS_MCDI_S3ADD1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetG0SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g0_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD2.bits.g0_sadr_wnd_mcw = g0_sadr_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset), VPSS_MCDI_S3ADD2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK0SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k0_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD2.bits.k0_sadr_wnd_mcw = k0_sadr_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset), VPSS_MCDI_S3ADD2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetX0SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 x0_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD2.bits.x0_sadr_wnd_mcw = x0_sadr_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset), VPSS_MCDI_S3ADD2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRpK1SadWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_k1_sad_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD2.bits.rp_k1_sad_wnd_mcw = rp_k1_sad_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset), VPSS_MCDI_S3ADD2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRpK1MagWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_k1_mag_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD2 VPSS_MCDI_S3ADD2;

    VPSS_MCDI_S3ADD2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD2.bits.rp_k1_mag_wnd_mcw = rp_k1_mag_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD2.u32) + u32AddrOffset), VPSS_MCDI_S3ADD2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetThCurBlksad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_cur_blksad)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD3.bits.th_cur_blksad = th_cur_blksad;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset), VPSS_MCDI_S3ADD3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKMcdifvMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_mcdifv_mcw)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD3.bits.k_mcdifv_mcw = k_mcdifv_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset), VPSS_MCDI_S3ADD3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKP1cfdifhMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_p1cfdifh_mcw)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD3.bits.k_p1cfdifh_mcw = k_p1cfdifh_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset), VPSS_MCDI_S3ADD3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetG1SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 g1_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD3.bits.g1_sadr_wnd_mcw = g1_sadr_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset), VPSS_MCDI_S3ADD3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK1SadrWndMcw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_sadr_wnd_mcw)
{
    U_VPSS_MCDI_S3ADD3 VPSS_MCDI_S3ADD3;

    VPSS_MCDI_S3ADD3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD3.bits.k1_sadr_wnd_mcw = k1_sadr_wnd_mcw;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD3.u32) + u32AddrOffset), VPSS_MCDI_S3ADD3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetThCurBlkmotion(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_cur_blkmotion)
{
    U_VPSS_MCDI_S3ADD4 VPSS_MCDI_S3ADD4;

    VPSS_MCDI_S3ADD4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD4.bits.th_cur_blkmotion = th_cur_blkmotion;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32) + u32AddrOffset), VPSS_MCDI_S3ADD4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThlNeighBlksad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 thl_neigh_blksad)
{
    U_VPSS_MCDI_S3ADD4 VPSS_MCDI_S3ADD4;

    VPSS_MCDI_S3ADD4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD4.bits.thl_neigh_blksad = thl_neigh_blksad;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32) + u32AddrOffset), VPSS_MCDI_S3ADD4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThhNeighBlksad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 thh_neigh_blksad)
{
    U_VPSS_MCDI_S3ADD4 VPSS_MCDI_S3ADD4;

    VPSS_MCDI_S3ADD4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD4.bits.thh_neigh_blksad = thh_neigh_blksad;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD4.u32) + u32AddrOffset), VPSS_MCDI_S3ADD4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRpDifmvxthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_difmvxth_rgmv)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD5.bits.rp_difmvxth_rgmv = rp_difmvxth_rgmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRpMvxthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_mvxth_rgmv)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD5.bits.rp_mvxth_rgmv = rp_mvxth_rgmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRpcounterth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rpcounterth)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD5.bits.rpcounterth = rpcounterth;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetKRpcounter(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k_rpcounter)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD5.bits.k_rpcounter = k_rpcounter;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBlkmvUpdateEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 blkmv_update_en)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD5.bits.blkmv_update_en = blkmv_update_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset), VPSS_MCDI_S3ADD5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetThRgmvMag(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 th_rgmv_mag)
{
    U_VPSS_MCDI_S3ADD5 VPSS_MCDI_S3ADD5;

    VPSS_MCDI_S3ADD5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD5.bits.th_rgmv_mag = th_rgmv_mag;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD5.u32) + u32AddrOffset), VPSS_MCDI_S3ADD5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRpMagthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_magth_rgmv)
{
    U_VPSS_MCDI_S3ADD6 VPSS_MCDI_S3ADD6;

    VPSS_MCDI_S3ADD6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD6.bits.rp_magth_rgmv = rp_magth_rgmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32) + u32AddrOffset), VPSS_MCDI_S3ADD6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRpSadthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_sadth_rgmv)
{
    U_VPSS_MCDI_S3ADD6 VPSS_MCDI_S3ADD6;

    VPSS_MCDI_S3ADD6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD6.bits.rp_sadth_rgmv = rp_sadth_rgmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32) + u32AddrOffset), VPSS_MCDI_S3ADD6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRpDifsadthRgmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_difsadth_rgmv)
{
    U_VPSS_MCDI_S3ADD6 VPSS_MCDI_S3ADD6;

    VPSS_MCDI_S3ADD6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD6.bits.rp_difsadth_rgmv = rp_difsadth_rgmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD6.u32) + u32AddrOffset), VPSS_MCDI_S3ADD6.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDifvtMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 difvt_mode)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD7.bits.difvt_mode = difvt_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset), VPSS_MCDI_S3ADD7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRpEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_en)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD7.bits.rp_en = rp_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset), VPSS_MCDI_S3ADD7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetSubmvSadchkEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 submv_sadchk_en)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD7.bits.submv_sadchk_en = submv_sadchk_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset), VPSS_MCDI_S3ADD7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetK1TpdifRgsad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 k1_tpdif_rgsad)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD7.bits.k1_tpdif_rgsad = k1_tpdif_rgsad;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset), VPSS_MCDI_S3ADD7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRpDifsadthTb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_difsadth_tb)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD7.bits.rp_difsadth_tb = rp_difsadth_tb;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset), VPSS_MCDI_S3ADD7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRpDifmvxthSp(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rp_difmvxth_sp)
{
    U_VPSS_MCDI_S3ADD7 VPSS_MCDI_S3ADD7;

    VPSS_MCDI_S3ADD7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset));
    VPSS_MCDI_S3ADD7.bits.rp_difmvxth_sp = rp_difmvxth_sp;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_S3ADD7.u32) + u32AddrOffset), VPSS_MCDI_S3ADD7.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCntlut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cntlut_5)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT0.bits.cntlut_5 = cntlut_5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCntlut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cntlut_4)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT0.bits.cntlut_4 = cntlut_4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCntlut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cntlut_3)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT0.bits.cntlut_3 = cntlut_3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCntlut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cntlut_2)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT0.bits.cntlut_2 = cntlut_2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCntlut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cntlut_1)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT0.bits.cntlut_1 = cntlut_1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCntlut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cntlut_0)
{
    U_VPSS_MCDI_STILLCNT0 VPSS_MCDI_STILLCNT0;

    VPSS_MCDI_STILLCNT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT0.bits.cntlut_0 = cntlut_0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT0.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMcwScntGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcw_scnt_gain)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT1.bits.mcw_scnt_gain = mcw_scnt_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcwScntEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcw_scnt_en)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT1.bits.mcw_scnt_en = mcw_scnt_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMcMtshift(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mc_mtshift)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT1.bits.mc_mtshift = mc_mtshift;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCntlut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cntlut_8)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT1.bits.cntlut_8 = cntlut_8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCntlut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cntlut_7)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT1.bits.cntlut_7 = cntlut_7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCntlut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cntlut_6)
{
    U_VPSS_MCDI_STILLCNT1 VPSS_MCDI_STILLCNT1;

    VPSS_MCDI_STILLCNT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset));
    VPSS_MCDI_STILLCNT1.bits.cntlut_6 = cntlut_6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_STILLCNT1.u32) + u32AddrOffset), VPSS_MCDI_STILLCNT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDemoBorder(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 demo_border)
{
    U_VPSS_MCDI_DEMO VPSS_MCDI_DEMO;

    VPSS_MCDI_DEMO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DEMO.u32) + u32AddrOffset));
    VPSS_MCDI_DEMO.bits.demo_border = demo_border;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DEMO.u32) + u32AddrOffset), VPSS_MCDI_DEMO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDemoModeR(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 demo_mode_r)
{
    U_VPSS_MCDI_DEMO VPSS_MCDI_DEMO;

    VPSS_MCDI_DEMO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DEMO.u32) + u32AddrOffset));
    VPSS_MCDI_DEMO.bits.demo_mode_r = demo_mode_r;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DEMO.u32) + u32AddrOffset), VPSS_MCDI_DEMO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDemoModeL(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 demo_mode_l)
{
    U_VPSS_MCDI_DEMO VPSS_MCDI_DEMO;

    VPSS_MCDI_DEMO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DEMO.u32) + u32AddrOffset));
    VPSS_MCDI_DEMO.bits.demo_mode_l = demo_mode_l;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DEMO.u32) + u32AddrOffset), VPSS_MCDI_DEMO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDemoEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 demo_en)
{
    U_VPSS_MCDI_DEMO VPSS_MCDI_DEMO;

    VPSS_MCDI_DEMO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_MCDI_DEMO.u32) + u32AddrOffset));
    VPSS_MCDI_DEMO.bits.demo_en = demo_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_MCDI_DEMO.u32) + u32AddrOffset), VPSS_MCDI_DEMO.u32);

    return ;
}



HI_VOID VPSS_Sys_SetHlmscEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hlmsc_en)
{
    U_VPSS_VHD0_HSP VPSS_VHD0_HSP;

    VPSS_VHD0_HSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset));
    VPSS_VHD0_HSP.bits.hlmsc_en = hlmsc_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset), VPSS_VHD0_HSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHchmscEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hchmsc_en)
{
    U_VPSS_VHD0_HSP VPSS_VHD0_HSP;

    VPSS_VHD0_HSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset));
    VPSS_VHD0_HSP.bits.hchmsc_en = hchmsc_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset), VPSS_VHD0_HSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHlmidEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hlmid_en)
{
    U_VPSS_VHD0_HSP VPSS_VHD0_HSP;

    VPSS_VHD0_HSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset));
    VPSS_VHD0_HSP.bits.hlmid_en = hlmid_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset), VPSS_VHD0_HSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHchmidEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hchmid_en)
{
    U_VPSS_VHD0_HSP VPSS_VHD0_HSP;

    VPSS_VHD0_HSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset));
    VPSS_VHD0_HSP.bits.hchmid_en = hchmid_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset), VPSS_VHD0_HSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHlfirEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hlfir_en)
{
    U_VPSS_VHD0_HSP VPSS_VHD0_HSP;

    VPSS_VHD0_HSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset));
    VPSS_VHD0_HSP.bits.hlfir_en = hlfir_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset), VPSS_VHD0_HSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHchfirEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hchfir_en)
{
    U_VPSS_VHD0_HSP VPSS_VHD0_HSP;

    VPSS_VHD0_HSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset));
    VPSS_VHD0_HSP.bits.hchfir_en = hchfir_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset), VPSS_VHD0_HSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHfirOrder(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hfir_order)
{
    U_VPSS_VHD0_HSP VPSS_VHD0_HSP;

    VPSS_VHD0_HSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset));
    VPSS_VHD0_HSP.bits.hfir_order = hfir_order;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset), VPSS_VHD0_HSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetHratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hratio)
{
    U_VPSS_VHD0_HSP VPSS_VHD0_HSP;

    VPSS_VHD0_HSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset));
    VPSS_VHD0_HSP.bits.hratio = hratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HSP.u32) + u32AddrOffset), VPSS_VHD0_HSP.u32);

    return ;
}



HI_VOID VPSS_Sys_SetHorLoffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hor_loffset)
{
    U_VPSS_VHD0_HLOFFSET VPSS_VHD0_HLOFFSET;

    VPSS_VHD0_HLOFFSET.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HLOFFSET.u32) + u32AddrOffset));
    VPSS_VHD0_HLOFFSET.bits.hor_loffset = hor_loffset;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HLOFFSET.u32) + u32AddrOffset), VPSS_VHD0_HLOFFSET.u32);

    return ;
}



HI_VOID VPSS_Sys_SetHorCoffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hor_coffset)
{
    U_VPSS_VHD0_HCOFFSET VPSS_VHD0_HCOFFSET;

    VPSS_VHD0_HCOFFSET.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_HCOFFSET.u32) + u32AddrOffset));
    VPSS_VHD0_HCOFFSET.bits.hor_coffset = hor_coffset;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_HCOFFSET.u32) + u32AddrOffset), VPSS_VHD0_HCOFFSET.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVlmscEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vlmsc_en)
{
    U_VPSS_VHD0_VSP VPSS_VHD0_VSP;

    VPSS_VHD0_VSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset));
    VPSS_VHD0_VSP.bits.vlmsc_en = vlmsc_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset), VPSS_VHD0_VSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVchmscEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vchmsc_en)
{
    U_VPSS_VHD0_VSP VPSS_VHD0_VSP;

    VPSS_VHD0_VSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset));
    VPSS_VHD0_VSP.bits.vchmsc_en = vchmsc_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset), VPSS_VHD0_VSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVlmidEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vlmid_en)
{
    U_VPSS_VHD0_VSP VPSS_VHD0_VSP;

    VPSS_VHD0_VSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset));
    VPSS_VHD0_VSP.bits.vlmid_en = vlmid_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset), VPSS_VHD0_VSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVchmidEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vchmid_en)
{
    U_VPSS_VHD0_VSP VPSS_VHD0_VSP;

    VPSS_VHD0_VSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset));
    VPSS_VHD0_VSP.bits.vchmid_en = vchmid_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset), VPSS_VHD0_VSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVlfirEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vlfir_en)
{
    U_VPSS_VHD0_VSP VPSS_VHD0_VSP;

    VPSS_VHD0_VSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset));
    VPSS_VHD0_VSP.bits.vlfir_en = vlfir_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset), VPSS_VHD0_VSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVchfirEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vchfir_en)
{
    U_VPSS_VHD0_VSP VPSS_VHD0_VSP;

    VPSS_VHD0_VSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset));
    VPSS_VHD0_VSP.bits.vchfir_en = vchfir_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset), VPSS_VHD0_VSP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetZmeOutFmt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 zme_out_fmt)
{
    U_VPSS_VHD0_VSP VPSS_VHD0_VSP;

    VPSS_VHD0_VSP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset));
    VPSS_VHD0_VSP.bits.zme_out_fmt = zme_out_fmt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VSP.u32) + u32AddrOffset), VPSS_VHD0_VSP.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vratio)
{
    U_VPSS_VHD0_VSR VPSS_VHD0_VSR;

    VPSS_VHD0_VSR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VSR.u32) + u32AddrOffset));
    VPSS_VHD0_VSR.bits.vratio = vratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VSR.u32) + u32AddrOffset), VPSS_VHD0_VSR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetVlumaOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vluma_offset)
{
    U_VPSS_VHD0_VOFFSET VPSS_VHD0_VOFFSET;

    VPSS_VHD0_VOFFSET.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VOFFSET.u32) + u32AddrOffset));
    VPSS_VHD0_VOFFSET.bits.vluma_offset = vluma_offset;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VOFFSET.u32) + u32AddrOffset), VPSS_VHD0_VOFFSET.u32);

    return ;
}


HI_VOID VPSS_Sys_SetVchromaOffset(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vchroma_offset)
{
    U_VPSS_VHD0_VOFFSET VPSS_VHD0_VOFFSET;

    VPSS_VHD0_VOFFSET.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_VHD0_VOFFSET.u32) + u32AddrOffset));
    VPSS_VHD0_VOFFSET.bits.vchroma_offset = vchroma_offset;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_VHD0_VOFFSET.u32) + u32AddrOffset), VPSS_VHD0_VOFFSET.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbmOutMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbm_out_mode)
{
    U_VPSS_DB_CTRL VPSS_DB_CTRL;

    VPSS_DB_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset));
    VPSS_DB_CTRL.bits.dbm_out_mode = dbm_out_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset), VPSS_DB_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDetHyEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 det_hy_en)
{
    U_VPSS_DB_CTRL VPSS_DB_CTRL;

    VPSS_DB_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset));
    VPSS_DB_CTRL.bits.det_hy_en = det_hy_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset), VPSS_DB_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbmDemoMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbm_demo_mode)
{
    U_VPSS_DB_CTRL VPSS_DB_CTRL;

    VPSS_DB_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset));
    VPSS_DB_CTRL.bits.dbm_demo_mode = dbm_demo_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset), VPSS_DB_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbmDemoEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbm_demo_en)
{
    U_VPSS_DB_CTRL VPSS_DB_CTRL;

    VPSS_DB_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset));
    VPSS_DB_CTRL.bits.dbm_demo_en = dbm_demo_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset), VPSS_DB_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_en)
{
    U_VPSS_DB_CTRL VPSS_DB_CTRL;

    VPSS_DB_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset));
    VPSS_DB_CTRL.bits.db_lum_hor_en = db_lum_hor_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRL.u32) + u32AddrOffset), VPSS_DB_CTRL.u32);

    return ;
}

HI_VOID VPSS_Sys_SetDbmDemoPosX(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbm_demo_pos_x)
{
    U_VPSS_DBM_DEMO VPSS_DBM_DEMO;

    VPSS_DBM_DEMO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBM_DEMO.u32) + u32AddrOffset));
    VPSS_DBM_DEMO.bits.dbm_demo_pos_x = dbm_demo_pos_x;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBM_DEMO.u32) + u32AddrOffset), VPSS_DBM_DEMO.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbCtrstThresh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_ctrst_thresh)
{
    U_VPSS_DB_DIR VPSS_DB_DIR;

    VPSS_DB_DIR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_DIR.u32) + u32AddrOffset));
    VPSS_DB_DIR.bits.db_ctrst_thresh = db_ctrst_thresh;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_DIR.u32) + u32AddrOffset), VPSS_DB_DIR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbGradSubRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_grad_sub_ratio)
{
    U_VPSS_DB_DIR VPSS_DB_DIR;

    VPSS_DB_DIR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_DIR.u32) + u32AddrOffset));
    VPSS_DB_DIR.bits.db_grad_sub_ratio = db_grad_sub_ratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_DIR.u32) + u32AddrOffset), VPSS_DB_DIR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbLumHBlkSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_blk_size)
{
    U_VPSS_DB_BLK VPSS_DB_BLK;

    VPSS_DB_BLK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BLK.u32) + u32AddrOffset));
    VPSS_DB_BLK.bits.db_lum_h_blk_size = db_lum_h_blk_size;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BLK.u32) + u32AddrOffset), VPSS_DB_BLK.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbLumHorTxtWinSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_txt_win_size)
{
    U_VPSS_DB_RATIO VPSS_DB_RATIO;

    VPSS_DB_RATIO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_RATIO.u32) + u32AddrOffset));
    VPSS_DB_RATIO.bits.db_lum_hor_txt_win_size = db_lum_hor_txt_win_size;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_RATIO.u32) + u32AddrOffset), VPSS_DB_RATIO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbGlobalDbStrenthLum(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_global_db_strenth_lum)
{
    U_VPSS_DB_RATIO VPSS_DB_RATIO;

    VPSS_DB_RATIO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_RATIO.u32) + u32AddrOffset));
    VPSS_DB_RATIO.bits.db_global_db_strenth_lum = db_global_db_strenth_lum;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_RATIO.u32) + u32AddrOffset), VPSS_DB_RATIO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorFilterSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_filter_sel)
{
    U_VPSS_DB_RATIO VPSS_DB_RATIO;

    VPSS_DB_RATIO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_RATIO.u32) + u32AddrOffset));
    VPSS_DB_RATIO.bits.db_lum_hor_filter_sel = db_lum_hor_filter_sel;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_RATIO.u32) + u32AddrOffset), VPSS_DB_RATIO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorScaleRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_scale_ratio)
{
    U_VPSS_DB_RATIO VPSS_DB_RATIO;

    VPSS_DB_RATIO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_RATIO.u32) + u32AddrOffset));
    VPSS_DB_RATIO.bits.db_lum_hor_scale_ratio = db_lum_hor_scale_ratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_RATIO.u32) + u32AddrOffset), VPSS_DB_RATIO.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbLumHorHfVarGain2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_hf_var_gain2)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_var_gain2 = db_lum_hor_hf_var_gain2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorHfVarGain1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_hf_var_gain1)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_var_gain1 = db_lum_hor_hf_var_gain1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorHfVarCore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_hf_var_core)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_var_core = db_lum_hor_hf_var_core;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorHfDiffGain2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_hf_diff_gain2)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_diff_gain2 = db_lum_hor_hf_diff_gain2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorHfDiffGain1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_hf_diff_gain1)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_diff_gain1 = db_lum_hor_hf_diff_gain1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset), VPSS_DB_LHHF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorHfDiffCore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_hf_diff_core)
{
    U_VPSS_DB_LHHF VPSS_DB_LHHF;

    VPSS_DB_LHHF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset));
    VPSS_DB_LHHF.bits.db_lum_hor_hf_diff_core = db_lum_hor_hf_diff_core;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LHHF.u32) + u32AddrOffset), VPSS_DB_LHHF.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbLumHorBordAdjGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_bord_adj_gain)
{
    U_VPSS_DB_LVHF VPSS_DB_LVHF;

    VPSS_DB_LVHF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LVHF.u32) + u32AddrOffset));
    VPSS_DB_LVHF.bits.db_lum_hor_bord_adj_gain = db_lum_hor_bord_adj_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LVHF.u32) + u32AddrOffset), VPSS_DB_LVHF.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorAdjGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_adj_gain)
{
    U_VPSS_DB_LVHF VPSS_DB_LVHF;

    VPSS_DB_LVHF.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LVHF.u32) + u32AddrOffset));
    VPSS_DB_LVHF.bits.db_lum_hor_adj_gain = db_lum_hor_adj_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LVHF.u32) + u32AddrOffset), VPSS_DB_LVHF.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbMaxLumHorDbDist(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_max_lum_hor_db_dist)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset));
    VPSS_DB_CTRS.bits.db_max_lum_hor_db_dist = db_max_lum_hor_db_dist;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset), VPSS_DB_CTRS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbCtrstAdjGain2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_ctrst_adj_gain2)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset));
    VPSS_DB_CTRS.bits.db_ctrst_adj_gain2 = db_ctrst_adj_gain2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset), VPSS_DB_CTRS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbCtrstAdjGain1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_ctrst_adj_gain1)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset));
    VPSS_DB_CTRS.bits.db_ctrst_adj_gain1 = db_ctrst_adj_gain1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset), VPSS_DB_CTRS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirSmoothMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_smooth_mode)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset));
    VPSS_DB_CTRS.bits.db_dir_smooth_mode = db_dir_smooth_mode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset), VPSS_DB_CTRS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbCtrstAdjCore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_ctrst_adj_core)
{
    U_VPSS_DB_CTRS VPSS_DB_CTRS;

    VPSS_DB_CTRS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset));
    VPSS_DB_CTRS.bits.db_ctrst_adj_core = db_ctrst_adj_core;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_CTRS.u32) + u32AddrOffset), VPSS_DB_CTRS.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p7)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p7 = db_lum_hor_delta_lut_p7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p6)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p6 = db_lum_hor_delta_lut_p6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p5)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p5 = db_lum_hor_delta_lut_p5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p4)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p4 = db_lum_hor_delta_lut_p4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p3)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p3 = db_lum_hor_delta_lut_p3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p2)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p2 = db_lum_hor_delta_lut_p2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p1)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p1 = db_lum_hor_delta_lut_p1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset), VPSS_DB_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p0)
{
    U_VPSS_DB_LUT0 VPSS_DB_LUT0;

    VPSS_DB_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset));
    VPSS_DB_LUT0.bits.db_lum_hor_delta_lut_p0 = db_lum_hor_delta_lut_p0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT0.u32) + u32AddrOffset), VPSS_DB_LUT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p15)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p15 = db_lum_hor_delta_lut_p15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p14)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p14 = db_lum_hor_delta_lut_p14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p13)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p13 = db_lum_hor_delta_lut_p13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p12)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p12 = db_lum_hor_delta_lut_p12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p11)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p11 = db_lum_hor_delta_lut_p11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p10)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p10 = db_lum_hor_delta_lut_p10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p9)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p9 = db_lum_hor_delta_lut_p9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset), VPSS_DB_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHorDeltaLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_hor_delta_lut_p8)
{
    U_VPSS_DB_LUT1 VPSS_DB_LUT1;

    VPSS_DB_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset));
    VPSS_DB_LUT1.bits.db_lum_hor_delta_lut_p8 = db_lum_hor_delta_lut_p8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT1.u32) + u32AddrOffset), VPSS_DB_LUT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p9)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p9 = db_lum_h_str_fade_lut_p9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p8)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p8 = db_lum_h_str_fade_lut_p8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p7)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p7 = db_lum_h_str_fade_lut_p7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p6)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p6 = db_lum_h_str_fade_lut_p6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p5)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p5 = db_lum_h_str_fade_lut_p5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p4)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p4 = db_lum_h_str_fade_lut_p4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p3)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p3 = db_lum_h_str_fade_lut_p3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p2)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p2 = db_lum_h_str_fade_lut_p2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p1)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p1 = db_lum_h_str_fade_lut_p1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p0)
{
    U_VPSS_DB_LUT2 VPSS_DB_LUT2;

    VPSS_DB_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset));
    VPSS_DB_LUT2.bits.db_lum_h_str_fade_lut_p0 = db_lum_h_str_fade_lut_p0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT2.u32) + u32AddrOffset), VPSS_DB_LUT2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p11)
{
    U_VPSS_DB_LUT3 VPSS_DB_LUT3;

    VPSS_DB_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT3.u32) + u32AddrOffset));
    VPSS_DB_LUT3.bits.db_lum_h_str_fade_lut_p11 = db_lum_h_str_fade_lut_p11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT3.u32) + u32AddrOffset), VPSS_DB_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbLumHStrFadeLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_lum_h_str_fade_lut_p10)
{
    U_VPSS_DB_LUT3 VPSS_DB_LUT3;

    VPSS_DB_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT3.u32) + u32AddrOffset));
    VPSS_DB_LUT3.bits.db_lum_h_str_fade_lut_p10 = db_lum_h_str_fade_lut_p10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT3.u32) + u32AddrOffset), VPSS_DB_LUT3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbDirStrGainLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_gain_lut_p7)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p7 = db_dir_str_gain_lut_p7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrGainLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_gain_lut_p6)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p6 = db_dir_str_gain_lut_p6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrGainLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_gain_lut_p5)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p5 = db_dir_str_gain_lut_p5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrGainLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_gain_lut_p4)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p4 = db_dir_str_gain_lut_p4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrGainLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_gain_lut_p3)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p3 = db_dir_str_gain_lut_p3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrGainLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_gain_lut_p2)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p2 = db_dir_str_gain_lut_p2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrGainLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_gain_lut_p1)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p1 = db_dir_str_gain_lut_p1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset), VPSS_DB_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrGainLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_gain_lut_p0)
{
    U_VPSS_DB_LUT4 VPSS_DB_LUT4;

    VPSS_DB_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset));
    VPSS_DB_LUT4.bits.db_dir_str_gain_lut_p0 = db_dir_str_gain_lut_p0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT4.u32) + u32AddrOffset), VPSS_DB_LUT4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbDirStrLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p7)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p7 = db_dir_str_lut_p7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p6)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p6 = db_dir_str_lut_p6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p5)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p5 = db_dir_str_lut_p5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p4)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p4 = db_dir_str_lut_p4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p3)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p3 = db_dir_str_lut_p3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p2)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p2 = db_dir_str_lut_p2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p1)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p1 = db_dir_str_lut_p1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset), VPSS_DB_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p0)
{
    U_VPSS_DB_LUT5 VPSS_DB_LUT5;

    VPSS_DB_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset));
    VPSS_DB_LUT5.bits.db_dir_str_lut_p0 = db_dir_str_lut_p0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT5.u32) + u32AddrOffset), VPSS_DB_LUT5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbDirStrLutP15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p15)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p15 = db_dir_str_lut_p15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p14)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p14 = db_dir_str_lut_p14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p13)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p13 = db_dir_str_lut_p13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p12)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p12 = db_dir_str_lut_p12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p11)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p11 = db_dir_str_lut_p11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p10)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p10 = db_dir_str_lut_p10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p9)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p9 = db_dir_str_lut_p9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset), VPSS_DB_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbDirStrLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 db_dir_str_lut_p8)
{
    U_VPSS_DB_LUT6 VPSS_DB_LUT6;

    VPSS_DB_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset));
    VPSS_DB_LUT6.bits.db_dir_str_lut_p8 = db_dir_str_lut_p8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_LUT6.u32) + u32AddrOffset), VPSS_DB_LUT6.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdHyThdEdge(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_thd_edge)
{
    U_VPSS_DBD_THDEDGE VPSS_DBD_THDEDGE;

    VPSS_DBD_THDEDGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_THDEDGE.u32) + u32AddrOffset));
    VPSS_DBD_THDEDGE.bits.dbd_hy_thd_edge = dbd_hy_thd_edge;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_THDEDGE.u32) + u32AddrOffset), VPSS_DBD_THDEDGE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdHyThdTxt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_thd_txt)
{
    U_VPSS_DBD_THDTXT VPSS_DBD_THDTXT;

    VPSS_DBD_THDTXT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_THDTXT.u32) + u32AddrOffset));
    VPSS_DBD_THDTXT.bits.dbd_hy_thd_txt = dbd_hy_thd_txt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_THDTXT.u32) + u32AddrOffset), VPSS_DBD_THDTXT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdDetLutWgt7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt7)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt7 = dbd_det_lut_wgt7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt6)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt6 = dbd_det_lut_wgt6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt5)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt5 = dbd_det_lut_wgt5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt4)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt4 = dbd_det_lut_wgt4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt3)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt3 = dbd_det_lut_wgt3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt2)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt2 = dbd_det_lut_wgt2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt1)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt1 = dbd_det_lut_wgt1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset), VPSS_DBD_LUTWGT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt0)
{
    U_VPSS_DBD_LUTWGT0 VPSS_DBD_LUTWGT0;

    VPSS_DBD_LUTWGT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT0.bits.dbd_det_lut_wgt0 = dbd_det_lut_wgt0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT0.u32) + u32AddrOffset), VPSS_DBD_LUTWGT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdDetLutWgt15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt15)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt15 = dbd_det_lut_wgt15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt14)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt14 = dbd_det_lut_wgt14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt13)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt13 = dbd_det_lut_wgt13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt12)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt12 = dbd_det_lut_wgt12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt11)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt11 = dbd_det_lut_wgt11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt10)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt10 = dbd_det_lut_wgt10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt9)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt9 = dbd_det_lut_wgt9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset), VPSS_DBD_LUTWGT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdDetLutWgt8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_det_lut_wgt8)
{
    U_VPSS_DBD_LUTWGT1 VPSS_DBD_LUTWGT1;

    VPSS_DBD_LUTWGT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset));
    VPSS_DBD_LUTWGT1.bits.dbd_det_lut_wgt8 = dbd_det_lut_wgt8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_LUTWGT1.u32) + u32AddrOffset), VPSS_DBD_LUTWGT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdHyRtnBdTxt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_rtn_bd_txt)
{
    U_VPSS_DBD_RTNBDTXT VPSS_DBD_RTNBDTXT;

    VPSS_DBD_RTNBDTXT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_RTNBDTXT.u32) + u32AddrOffset));
    VPSS_DBD_RTNBDTXT.bits.dbd_hy_rtn_bd_txt = dbd_hy_rtn_bd_txt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_RTNBDTXT.u32) + u32AddrOffset), VPSS_DBD_RTNBDTXT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdHyTstBlkNum(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_tst_blk_num)
{
    U_VPSS_DBD_TSTBLKNUM VPSS_DBD_TSTBLKNUM;

    VPSS_DBD_TSTBLKNUM.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_TSTBLKNUM.u32) + u32AddrOffset));
    VPSS_DBD_TSTBLKNUM.bits.dbd_hy_tst_blk_num = dbd_hy_tst_blk_num;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_TSTBLKNUM.u32) + u32AddrOffset), VPSS_DBD_TSTBLKNUM.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdHyRdx8binLut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_rdx8bin_lut1)
{
    U_VPSS_DBD_HYRDX8BINLUT0 VPSS_DBD_HYRDX8BINLUT0;

    VPSS_DBD_HYRDX8BINLUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT0.u32) + u32AddrOffset));
    VPSS_DBD_HYRDX8BINLUT0.bits.dbd_hy_rdx8bin_lut1 = dbd_hy_rdx8bin_lut1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT0.u32) + u32AddrOffset), VPSS_DBD_HYRDX8BINLUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdHyRdx8binLut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_rdx8bin_lut0)
{
    U_VPSS_DBD_HYRDX8BINLUT0 VPSS_DBD_HYRDX8BINLUT0;

    VPSS_DBD_HYRDX8BINLUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT0.u32) + u32AddrOffset));
    VPSS_DBD_HYRDX8BINLUT0.bits.dbd_hy_rdx8bin_lut0 = dbd_hy_rdx8bin_lut0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT0.u32) + u32AddrOffset), VPSS_DBD_HYRDX8BINLUT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdHyRdx8binLut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_rdx8bin_lut3)
{
    U_VPSS_DBD_HYRDX8BINLUT1 VPSS_DBD_HYRDX8BINLUT1;

    VPSS_DBD_HYRDX8BINLUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT1.u32) + u32AddrOffset));
    VPSS_DBD_HYRDX8BINLUT1.bits.dbd_hy_rdx8bin_lut3 = dbd_hy_rdx8bin_lut3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT1.u32) + u32AddrOffset), VPSS_DBD_HYRDX8BINLUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdHyRdx8binLut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_rdx8bin_lut2)
{
    U_VPSS_DBD_HYRDX8BINLUT1 VPSS_DBD_HYRDX8BINLUT1;

    VPSS_DBD_HYRDX8BINLUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT1.u32) + u32AddrOffset));
    VPSS_DBD_HYRDX8BINLUT1.bits.dbd_hy_rdx8bin_lut2 = dbd_hy_rdx8bin_lut2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT1.u32) + u32AddrOffset), VPSS_DBD_HYRDX8BINLUT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdHyRdx8binLut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_rdx8bin_lut5)
{
    U_VPSS_DBD_HYRDX8BINLUT2 VPSS_DBD_HYRDX8BINLUT2;

    VPSS_DBD_HYRDX8BINLUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT2.u32) + u32AddrOffset));
    VPSS_DBD_HYRDX8BINLUT2.bits.dbd_hy_rdx8bin_lut5 = dbd_hy_rdx8bin_lut5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT2.u32) + u32AddrOffset), VPSS_DBD_HYRDX8BINLUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdHyRdx8binLut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_rdx8bin_lut4)
{
    U_VPSS_DBD_HYRDX8BINLUT2 VPSS_DBD_HYRDX8BINLUT2;

    VPSS_DBD_HYRDX8BINLUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT2.u32) + u32AddrOffset));
    VPSS_DBD_HYRDX8BINLUT2.bits.dbd_hy_rdx8bin_lut4 = dbd_hy_rdx8bin_lut4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT2.u32) + u32AddrOffset), VPSS_DBD_HYRDX8BINLUT2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdHyRdx8binLut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_rdx8bin_lut6)
{
    U_VPSS_DBD_HYRDX8BINLUT3 VPSS_DBD_HYRDX8BINLUT3;

    VPSS_DBD_HYRDX8BINLUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT3.u32) + u32AddrOffset));
    VPSS_DBD_HYRDX8BINLUT3.bits.dbd_hy_rdx8bin_lut6 = dbd_hy_rdx8bin_lut6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_HYRDX8BINLUT3.u32) + u32AddrOffset), VPSS_DBD_HYRDX8BINLUT3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdHyMaxBlkSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_hy_max_blk_size)
{
    U_VPSS_DBD_BLKSIZE VPSS_DBD_BLKSIZE;

    VPSS_DBD_BLKSIZE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_BLKSIZE.u32) + u32AddrOffset));
    VPSS_DBD_BLKSIZE.bits.dbd_hy_max_blk_size = dbd_hy_max_blk_size;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_BLKSIZE.u32) + u32AddrOffset), VPSS_DBD_BLKSIZE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDbdMinBlkSize(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_min_blk_size)
{
    U_VPSS_DBD_BLKSIZE VPSS_DBD_BLKSIZE;

    VPSS_DBD_BLKSIZE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_BLKSIZE.u32) + u32AddrOffset));
    VPSS_DBD_BLKSIZE.bits.dbd_min_blk_size = dbd_min_blk_size;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_BLKSIZE.u32) + u32AddrOffset), VPSS_DBD_BLKSIZE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDbdThrFlat(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dbd_thr_flat)
{
    U_VPSS_DBD_FLAT VPSS_DBD_FLAT;

    VPSS_DBD_FLAT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DBD_FLAT.u32) + u32AddrOffset));
    VPSS_DBD_FLAT.bits.dbd_thr_flat = dbd_thr_flat;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DBD_FLAT.u32) + u32AddrOffset), VPSS_DBD_FLAT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmOppAngCtrstDiv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_opp_ang_ctrst_div)
{
    U_VPSS_DM_DIR VPSS_DM_DIR;

    VPSS_DM_DIR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_DIR.u32) + u32AddrOffset));
    VPSS_DM_DIR.bits.dm_opp_ang_ctrst_div = dm_opp_ang_ctrst_div;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_DIR.u32) + u32AddrOffset), VPSS_DM_DIR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmOppAngCtrstT(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_opp_ang_ctrst_t)
{
    U_VPSS_DM_DIR VPSS_DM_DIR;

    VPSS_DM_DIR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_DIR.u32) + u32AddrOffset));
    VPSS_DM_DIR.bits.dm_opp_ang_ctrst_t = dm_opp_ang_ctrst_t;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_DIR.u32) + u32AddrOffset), VPSS_DM_DIR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmCtrstThresh(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_ctrst_thresh)
{
    U_VPSS_DM_DIR VPSS_DM_DIR;

    VPSS_DM_DIR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_DIR.u32) + u32AddrOffset));
    VPSS_DM_DIR.bits.dm_ctrst_thresh = dm_ctrst_thresh;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_DIR.u32) + u32AddrOffset), VPSS_DM_DIR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmGradSubRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_grad_sub_ratio)
{
    U_VPSS_DM_DIR VPSS_DM_DIR;

    VPSS_DM_DIR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_DIR.u32) + u32AddrOffset));
    VPSS_DM_DIR.bits.dm_grad_sub_ratio = dm_grad_sub_ratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_DIR.u32) + u32AddrOffset), VPSS_DM_DIR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmGlobalStr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_global_str)
{
    U_VPSS_DM_EDGE VPSS_DM_EDGE;

    VPSS_DM_EDGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_EDGE.u32) + u32AddrOffset));
    VPSS_DM_EDGE.bits.dm_global_str = dm_global_str;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_EDGE.u32) + u32AddrOffset), VPSS_DM_EDGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmInitValStep(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_init_val_step)
{
    U_VPSS_DM_EDGE VPSS_DM_EDGE;

    VPSS_DM_EDGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_EDGE.u32) + u32AddrOffset));
    VPSS_DM_EDGE.bits.dm_init_val_step = dm_init_val_step;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_EDGE.u32) + u32AddrOffset), VPSS_DM_EDGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmMmfSet(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_mmf_set)
{
    U_VPSS_DM_EDGE VPSS_DM_EDGE;

    VPSS_DM_EDGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_EDGE.u32) + u32AddrOffset));
    VPSS_DM_EDGE.bits.dm_mmf_set = dm_mmf_set;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_EDGE.u32) + u32AddrOffset), VPSS_DM_EDGE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmSwWhtLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_sw_wht_lut_p3)
{
    U_VPSS_DM_LUT0 VPSS_DM_LUT0;

    VPSS_DM_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT0.u32) + u32AddrOffset));
    VPSS_DM_LUT0.bits.dm_sw_wht_lut_p3 = dm_sw_wht_lut_p3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT0.u32) + u32AddrOffset), VPSS_DM_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmSwWhtLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_sw_wht_lut_p2)
{
    U_VPSS_DM_LUT0 VPSS_DM_LUT0;

    VPSS_DM_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT0.u32) + u32AddrOffset));
    VPSS_DM_LUT0.bits.dm_sw_wht_lut_p2 = dm_sw_wht_lut_p2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT0.u32) + u32AddrOffset), VPSS_DM_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmSwWhtLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_sw_wht_lut_p1)
{
    U_VPSS_DM_LUT0 VPSS_DM_LUT0;

    VPSS_DM_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT0.u32) + u32AddrOffset));
    VPSS_DM_LUT0.bits.dm_sw_wht_lut_p1 = dm_sw_wht_lut_p1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT0.u32) + u32AddrOffset), VPSS_DM_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmSwWhtLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_sw_wht_lut_p0)
{
    U_VPSS_DM_LUT0 VPSS_DM_LUT0;

    VPSS_DM_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT0.u32) + u32AddrOffset));
    VPSS_DM_LUT0.bits.dm_sw_wht_lut_p0 = dm_sw_wht_lut_p0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT0.u32) + u32AddrOffset), VPSS_DM_LUT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmLimitT10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_limit_t_10)
{
    U_VPSS_DM_LUT1 VPSS_DM_LUT1;

    VPSS_DM_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT1.u32) + u32AddrOffset));
    VPSS_DM_LUT1.bits.dm_limit_t_10 = dm_limit_t_10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT1.u32) + u32AddrOffset), VPSS_DM_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmLimitT(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_limit_t)
{
    U_VPSS_DM_LUT1 VPSS_DM_LUT1;

    VPSS_DM_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT1.u32) + u32AddrOffset));
    VPSS_DM_LUT1.bits.dm_limit_t = dm_limit_t;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT1.u32) + u32AddrOffset), VPSS_DM_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmSwWhtLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_sw_wht_lut_p4)
{
    U_VPSS_DM_LUT1 VPSS_DM_LUT1;

    VPSS_DM_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT1.u32) + u32AddrOffset));
    VPSS_DM_LUT1.bits.dm_sw_wht_lut_p4 = dm_sw_wht_lut_p4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT1.u32) + u32AddrOffset), VPSS_DM_LUT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmDirStrGainLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_gain_lut_p7)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p7 = dm_dir_str_gain_lut_p7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrGainLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_gain_lut_p6)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p6 = dm_dir_str_gain_lut_p6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrGainLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_gain_lut_p5)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p5 = dm_dir_str_gain_lut_p5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrGainLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_gain_lut_p4)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p4 = dm_dir_str_gain_lut_p4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrGainLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_gain_lut_p3)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p3 = dm_dir_str_gain_lut_p3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrGainLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_gain_lut_p2)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p2 = dm_dir_str_gain_lut_p2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrGainLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_gain_lut_p1)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p1 = dm_dir_str_gain_lut_p1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset), VPSS_DM_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrGainLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_gain_lut_p0)
{
    U_VPSS_DM_LUT2 VPSS_DM_LUT2;

    VPSS_DM_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset));
    VPSS_DM_LUT2.bits.dm_dir_str_gain_lut_p0 = dm_dir_str_gain_lut_p0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT2.u32) + u32AddrOffset), VPSS_DM_LUT2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmDirStrLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p7)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p7 = dm_dir_str_lut_p7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p6)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p6 = dm_dir_str_lut_p6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p5)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p5 = dm_dir_str_lut_p5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p4)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p4 = dm_dir_str_lut_p4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p3)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p3 = dm_dir_str_lut_p3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p2)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p2 = dm_dir_str_lut_p2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p1)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p1 = dm_dir_str_lut_p1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset), VPSS_DM_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p0)
{
    U_VPSS_DM_LUT3 VPSS_DM_LUT3;

    VPSS_DM_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset));
    VPSS_DM_LUT3.bits.dm_dir_str_lut_p0 = dm_dir_str_lut_p0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT3.u32) + u32AddrOffset), VPSS_DM_LUT3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmDirStrLutP15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p15)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p15 = dm_dir_str_lut_p15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p14)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p14 = dm_dir_str_lut_p14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p13)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p13 = dm_dir_str_lut_p13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p12)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p12 = dm_dir_str_lut_p12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p11)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p11 = dm_dir_str_lut_p11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p10)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p10 = dm_dir_str_lut_p10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p9)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p9 = dm_dir_str_lut_p9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset), VPSS_DM_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmDirStrLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_str_lut_p8)
{
    U_VPSS_DM_LUT4 VPSS_DM_LUT4;

    VPSS_DM_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset));
    VPSS_DM_LUT4.bits.dm_dir_str_lut_p8 = dm_dir_str_lut_p8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT4.u32) + u32AddrOffset), VPSS_DM_LUT4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmMmfLimitEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_mmf_limit_en)
{
    U_VPSS_DM_DIRC VPSS_DM_DIRC;

    VPSS_DM_DIRC.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_DIRC.u32) + u32AddrOffset));
    VPSS_DM_DIRC.bits.dm_mmf_limit_en = dm_mmf_limit_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_DIRC.u32) + u32AddrOffset), VPSS_DM_DIRC.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmMndirOppCtrstT(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_mndir_opp_ctrst_t)
{
    U_VPSS_DM_DIRC VPSS_DM_DIRC;

    VPSS_DM_DIRC.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_DIRC.u32) + u32AddrOffset));
    VPSS_DM_DIRC.bits.dm_mndir_opp_ctrst_t = dm_mndir_opp_ctrst_t;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_DIRC.u32) + u32AddrOffset), VPSS_DM_DIRC.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmCswTrsntSt10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_csw_trsnt_st_10)
{
    U_VPSS_DM_DIRO VPSS_DM_DIRO;

    VPSS_DM_DIRO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_DIRO.u32) + u32AddrOffset));
    VPSS_DM_DIRO.bits.dm_csw_trsnt_st_10 = dm_csw_trsnt_st_10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_DIRO.u32) + u32AddrOffset), VPSS_DM_DIRO.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmLswRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_lsw_ratio)
{
    U_VPSS_DM_LSW VPSS_DM_LSW;

    VPSS_DM_LSW.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LSW.u32) + u32AddrOffset));
    VPSS_DM_LSW.bits.dm_lsw_ratio = dm_lsw_ratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LSW.u32) + u32AddrOffset), VPSS_DM_LSW.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmCswTrsntSt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_csw_trsnt_st)
{
    U_VPSS_DM_LSW VPSS_DM_LSW;

    VPSS_DM_LSW.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LSW.u32) + u32AddrOffset));
    VPSS_DM_LSW.bits.dm_csw_trsnt_st = dm_csw_trsnt_st;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LSW.u32) + u32AddrOffset), VPSS_DM_LSW.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmLwCtrstT10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_lw_ctrst_t_10)
{
    U_VPSS_DM_LSW VPSS_DM_LSW;

    VPSS_DM_LSW.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LSW.u32) + u32AddrOffset));
    VPSS_DM_LSW.bits.dm_lw_ctrst_t_10 = dm_lw_ctrst_t_10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LSW.u32) + u32AddrOffset), VPSS_DM_LSW.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmLwCtrstT(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_lw_ctrst_t)
{
    U_VPSS_DM_LSW VPSS_DM_LSW;

    VPSS_DM_LSW.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LSW.u32) + u32AddrOffset));
    VPSS_DM_LSW.bits.dm_lw_ctrst_t = dm_lw_ctrst_t;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LSW.u32) + u32AddrOffset), VPSS_DM_LSW.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmCswTrsntLt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_csw_trsnt_lt)
{
    U_VPSS_DM_MMFLR VPSS_DM_MMFLR;

    VPSS_DM_MMFLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_MMFLR.u32) + u32AddrOffset));
    VPSS_DM_MMFLR.bits.dm_csw_trsnt_lt = dm_csw_trsnt_lt;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_MMFLR.u32) + u32AddrOffset), VPSS_DM_MMFLR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmMmfLr10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_mmf_lr_10)
{
    U_VPSS_DM_MMFLR VPSS_DM_MMFLR;

    VPSS_DM_MMFLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_MMFLR.u32) + u32AddrOffset));
    VPSS_DM_MMFLR.bits.dm_mmf_lr_10 = dm_mmf_lr_10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_MMFLR.u32) + u32AddrOffset), VPSS_DM_MMFLR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmMmfLr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_mmf_lr)
{
    U_VPSS_DM_MMFLR VPSS_DM_MMFLR;

    VPSS_DM_MMFLR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_MMFLR.u32) + u32AddrOffset));
    VPSS_DM_MMFLR.bits.dm_mmf_lr = dm_mmf_lr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_MMFLR.u32) + u32AddrOffset), VPSS_DM_MMFLR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmCswTrsntLt10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_csw_trsnt_lt_10)
{
    U_VPSS_DM_MMFSR VPSS_DM_MMFSR;

    VPSS_DM_MMFSR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_MMFSR.u32) + u32AddrOffset));
    VPSS_DM_MMFSR.bits.dm_csw_trsnt_lt_10 = dm_csw_trsnt_lt_10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_MMFSR.u32) + u32AddrOffset), VPSS_DM_MMFSR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmMmfSr10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_mmf_sr_10)
{
    U_VPSS_DM_MMFSR VPSS_DM_MMFSR;

    VPSS_DM_MMFSR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_MMFSR.u32) + u32AddrOffset));
    VPSS_DM_MMFSR.bits.dm_mmf_sr_10 = dm_mmf_sr_10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_MMFSR.u32) + u32AddrOffset), VPSS_DM_MMFSR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmMmfSr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_mmf_sr)
{
    U_VPSS_DM_MMFSR VPSS_DM_MMFSR;

    VPSS_DM_MMFSR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_MMFSR.u32) + u32AddrOffset));
    VPSS_DM_MMFSR.bits.dm_mmf_sr = dm_mmf_sr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_MMFSR.u32) + u32AddrOffset), VPSS_DM_MMFSR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmDirBlendStr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_dir_blend_str)
{
    U_VPSS_DM_THR0 VPSS_DM_THR0;

    VPSS_DM_THR0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_THR0.u32) + u32AddrOffset));
    VPSS_DM_THR0.bits.dm_dir_blend_str = dm_dir_blend_str;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_THR0.u32) + u32AddrOffset), VPSS_DM_THR0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmLimResBlendStr2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_lim_res_blend_str2)
{
    U_VPSS_DM_THR0 VPSS_DM_THR0;

    VPSS_DM_THR0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_THR0.u32) + u32AddrOffset));
    VPSS_DM_THR0.bits.dm_lim_res_blend_str2 = dm_lim_res_blend_str2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_THR0.u32) + u32AddrOffset), VPSS_DM_THR0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmLimResBlendStr1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_lim_res_blend_str1)
{
    U_VPSS_DM_THR0 VPSS_DM_THR0;

    VPSS_DM_THR0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_THR0.u32) + u32AddrOffset));
    VPSS_DM_THR0.bits.dm_lim_res_blend_str1 = dm_lim_res_blend_str1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_THR0.u32) + u32AddrOffset), VPSS_DM_THR0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmLimitLswRatio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_limit_lsw_ratio)
{
    U_VPSS_DM_THR0 VPSS_DM_THR0;

    VPSS_DM_THR0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_THR0.u32) + u32AddrOffset));
    VPSS_DM_THR0.bits.dm_limit_lsw_ratio = dm_limit_lsw_ratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_THR0.u32) + u32AddrOffset), VPSS_DM_THR0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmTransBandLutP4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p4)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p4 = dm_trans_band_lut_p4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset), VPSS_DM_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p3)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p3 = dm_trans_band_lut_p3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset), VPSS_DM_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p2)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p2 = dm_trans_band_lut_p2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset), VPSS_DM_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p1)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p1 = dm_trans_band_lut_p1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset), VPSS_DM_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p0)
{
    U_VPSS_DM_LUT5 VPSS_DM_LUT5;

    VPSS_DM_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset));
    VPSS_DM_LUT5.bits.dm_trans_band_lut_p0 = dm_trans_band_lut_p0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT5.u32) + u32AddrOffset), VPSS_DM_LUT5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmTransBandLutP9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p9)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p9 = dm_trans_band_lut_p9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset), VPSS_DM_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p8)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p8 = dm_trans_band_lut_p8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset), VPSS_DM_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p7)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p7 = dm_trans_band_lut_p7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset), VPSS_DM_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p6)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p6 = dm_trans_band_lut_p6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset), VPSS_DM_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p5)
{
    U_VPSS_DM_LUT6 VPSS_DM_LUT6;

    VPSS_DM_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset));
    VPSS_DM_LUT6.bits.dm_trans_band_lut_p5 = dm_trans_band_lut_p5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT6.u32) + u32AddrOffset), VPSS_DM_LUT6.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmTransBandLutP14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p14)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p14 = dm_trans_band_lut_p14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset), VPSS_DM_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p13)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p13 = dm_trans_band_lut_p13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset), VPSS_DM_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p12)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p12 = dm_trans_band_lut_p12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset), VPSS_DM_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p11)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p11 = dm_trans_band_lut_p11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset), VPSS_DM_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p10)
{
    U_VPSS_DM_LUT7 VPSS_DM_LUT7;

    VPSS_DM_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset));
    VPSS_DM_LUT7.bits.dm_trans_band_lut_p10 = dm_trans_band_lut_p10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT7.u32) + u32AddrOffset), VPSS_DM_LUT7.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmTransBandLutP19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p19)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p19 = dm_trans_band_lut_p19;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset), VPSS_DM_LUT8.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p18)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p18 = dm_trans_band_lut_p18;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset), VPSS_DM_LUT8.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p17)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p17 = dm_trans_band_lut_p17;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset), VPSS_DM_LUT8.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p16)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p16 = dm_trans_band_lut_p16;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset), VPSS_DM_LUT8.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p15)
{
    U_VPSS_DM_LUT8 VPSS_DM_LUT8;

    VPSS_DM_LUT8.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset));
    VPSS_DM_LUT8.bits.dm_trans_band_lut_p15 = dm_trans_band_lut_p15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT8.u32) + u32AddrOffset), VPSS_DM_LUT8.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmTransBandLutP24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p24)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p24 = dm_trans_band_lut_p24;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset), VPSS_DM_LUT9.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p23)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p23 = dm_trans_band_lut_p23;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset), VPSS_DM_LUT9.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p22)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p22 = dm_trans_band_lut_p22;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset), VPSS_DM_LUT9.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p21)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p21 = dm_trans_band_lut_p21;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset), VPSS_DM_LUT9.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p20)
{
    U_VPSS_DM_LUT9 VPSS_DM_LUT9;

    VPSS_DM_LUT9.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset));
    VPSS_DM_LUT9.bits.dm_trans_band_lut_p20 = dm_trans_band_lut_p20;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT9.u32) + u32AddrOffset), VPSS_DM_LUT9.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmTransBandLutP29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p29)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p29 = dm_trans_band_lut_p29;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset), VPSS_DM_LUT10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p28)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p28 = dm_trans_band_lut_p28;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset), VPSS_DM_LUT10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p27)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p27 = dm_trans_band_lut_p27;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset), VPSS_DM_LUT10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p26)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p26 = dm_trans_band_lut_p26;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset), VPSS_DM_LUT10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDmTransBandLutP25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p25)
{
    U_VPSS_DM_LUT10 VPSS_DM_LUT10;

    VPSS_DM_LUT10.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset));
    VPSS_DM_LUT10.bits.dm_trans_band_lut_p25 = dm_trans_band_lut_p25;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT10.u32) + u32AddrOffset), VPSS_DM_LUT10.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDmTransBandLutP30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dm_trans_band_lut_p30)
{
    U_VPSS_DM_LUT11 VPSS_DM_LUT11;

    VPSS_DM_LUT11.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DM_LUT11.u32) + u32AddrOffset));
    VPSS_DM_LUT11.bits.dm_trans_band_lut_p30 = dm_trans_band_lut_p30;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DM_LUT11.u32) + u32AddrOffset), VPSS_DM_LUT11.u32);

    return ;
}



//HI_VOID VPSS_Sys_SetVpssDbBordFlag0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_0)
//{
//  U_VPSS_DB_BORD_FLAG0 VPSS_DB_BORD_FLAG0;
//
//  VPSS_DB_BORD_FLAG0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG0.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG0.bits.vpss_db_bord_flag_0 = vpss_db_bord_flag_0;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG0.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG0.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_1)
//{
//  U_VPSS_DB_BORD_FLAG1 VPSS_DB_BORD_FLAG1;
//
//  VPSS_DB_BORD_FLAG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG1.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG1.bits.vpss_db_bord_flag_1 = vpss_db_bord_flag_1;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG1.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG1.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_2)
//{
//  U_VPSS_DB_BORD_FLAG2 VPSS_DB_BORD_FLAG2;
//
//  VPSS_DB_BORD_FLAG2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG2.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG2.bits.vpss_db_bord_flag_2 = vpss_db_bord_flag_2;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG2.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG2.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_3)
//{
//  U_VPSS_DB_BORD_FLAG3 VPSS_DB_BORD_FLAG3;
//
//  VPSS_DB_BORD_FLAG3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG3.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG3.bits.vpss_db_bord_flag_3 = vpss_db_bord_flag_3;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG3.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG3.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_4)
//{
//  U_VPSS_DB_BORD_FLAG4 VPSS_DB_BORD_FLAG4;
//
//  VPSS_DB_BORD_FLAG4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG4.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG4.bits.vpss_db_bord_flag_4 = vpss_db_bord_flag_4;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG4.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG4.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_5)
//{
//  U_VPSS_DB_BORD_FLAG5 VPSS_DB_BORD_FLAG5;
//
//  VPSS_DB_BORD_FLAG5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG5.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG5.bits.vpss_db_bord_flag_5 = vpss_db_bord_flag_5;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG5.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG5.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_6)
//{
//  U_VPSS_DB_BORD_FLAG6 VPSS_DB_BORD_FLAG6;
//
//  VPSS_DB_BORD_FLAG6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG6.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG6.bits.vpss_db_bord_flag_6 = vpss_db_bord_flag_6;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG6.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG6.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_7)
//{
//  U_VPSS_DB_BORD_FLAG7 VPSS_DB_BORD_FLAG7;
//
//  VPSS_DB_BORD_FLAG7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG7.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG7.bits.vpss_db_bord_flag_7 = vpss_db_bord_flag_7;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG7.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG7.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_8)
//{
//  U_VPSS_DB_BORD_FLAG8 VPSS_DB_BORD_FLAG8;
//
//  VPSS_DB_BORD_FLAG8.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG8.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG8.bits.vpss_db_bord_flag_8 = vpss_db_bord_flag_8;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG8.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG8.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_9)
//{
//  U_VPSS_DB_BORD_FLAG9 VPSS_DB_BORD_FLAG9;
//
//  VPSS_DB_BORD_FLAG9.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG9.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG9.bits.vpss_db_bord_flag_9 = vpss_db_bord_flag_9;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG9.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG9.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_10)
//{
//  U_VPSS_DB_BORD_FLAG10 VPSS_DB_BORD_FLAG10;
//
//  VPSS_DB_BORD_FLAG10.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG10.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG10.bits.vpss_db_bord_flag_10 = vpss_db_bord_flag_10;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG10.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG10.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_11)
//{
//  U_VPSS_DB_BORD_FLAG11 VPSS_DB_BORD_FLAG11;
//
//  VPSS_DB_BORD_FLAG11.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG11.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG11.bits.vpss_db_bord_flag_11 = vpss_db_bord_flag_11;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG11.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG11.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_12)
//{
//  U_VPSS_DB_BORD_FLAG12 VPSS_DB_BORD_FLAG12;
//
//  VPSS_DB_BORD_FLAG12.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG12.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG12.bits.vpss_db_bord_flag_12 = vpss_db_bord_flag_12;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG12.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG12.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_13)
//{
//  U_VPSS_DB_BORD_FLAG13 VPSS_DB_BORD_FLAG13;
//
//  VPSS_DB_BORD_FLAG13.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG13.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG13.bits.vpss_db_bord_flag_13 = vpss_db_bord_flag_13;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG13.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG13.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_14)
//{
//  U_VPSS_DB_BORD_FLAG14 VPSS_DB_BORD_FLAG14;
//
//  VPSS_DB_BORD_FLAG14.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG14.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG14.bits.vpss_db_bord_flag_14 = vpss_db_bord_flag_14;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG14.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG14.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_15)
//{
//  U_VPSS_DB_BORD_FLAG15 VPSS_DB_BORD_FLAG15;
//
//  VPSS_DB_BORD_FLAG15.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG15.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG15.bits.vpss_db_bord_flag_15 = vpss_db_bord_flag_15;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG15.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG15.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_16)
//{
//  U_VPSS_DB_BORD_FLAG16 VPSS_DB_BORD_FLAG16;
//
//  VPSS_DB_BORD_FLAG16.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG16.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG16.bits.vpss_db_bord_flag_16 = vpss_db_bord_flag_16;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG16.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG16.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_17)
//{
//  U_VPSS_DB_BORD_FLAG17 VPSS_DB_BORD_FLAG17;
//
//  VPSS_DB_BORD_FLAG17.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG17.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG17.bits.vpss_db_bord_flag_17 = vpss_db_bord_flag_17;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG17.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG17.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_18)
//{
//  U_VPSS_DB_BORD_FLAG18 VPSS_DB_BORD_FLAG18;
//
//  VPSS_DB_BORD_FLAG18.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG18.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG18.bits.vpss_db_bord_flag_18 = vpss_db_bord_flag_18;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG18.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG18.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_19)
//{
//  U_VPSS_DB_BORD_FLAG19 VPSS_DB_BORD_FLAG19;
//
//  VPSS_DB_BORD_FLAG19.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG19.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG19.bits.vpss_db_bord_flag_19 = vpss_db_bord_flag_19;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG19.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG19.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_20)
//{
//  U_VPSS_DB_BORD_FLAG20 VPSS_DB_BORD_FLAG20;
//
//  VPSS_DB_BORD_FLAG20.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG20.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG20.bits.vpss_db_bord_flag_20 = vpss_db_bord_flag_20;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG20.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG20.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_21)
//{
//  U_VPSS_DB_BORD_FLAG21 VPSS_DB_BORD_FLAG21;
//
//  VPSS_DB_BORD_FLAG21.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG21.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG21.bits.vpss_db_bord_flag_21 = vpss_db_bord_flag_21;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG21.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG21.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_22)
//{
//  U_VPSS_DB_BORD_FLAG22 VPSS_DB_BORD_FLAG22;
//
//  VPSS_DB_BORD_FLAG22.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG22.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG22.bits.vpss_db_bord_flag_22 = vpss_db_bord_flag_22;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG22.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG22.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_23)
//{
//  U_VPSS_DB_BORD_FLAG23 VPSS_DB_BORD_FLAG23;
//
//  VPSS_DB_BORD_FLAG23.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG23.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG23.bits.vpss_db_bord_flag_23 = vpss_db_bord_flag_23;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG23.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG23.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_24)
//{
//  U_VPSS_DB_BORD_FLAG24 VPSS_DB_BORD_FLAG24;
//
//  VPSS_DB_BORD_FLAG24.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG24.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG24.bits.vpss_db_bord_flag_24 = vpss_db_bord_flag_24;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG24.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG24.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_25)
//{
//  U_VPSS_DB_BORD_FLAG25 VPSS_DB_BORD_FLAG25;
//
//  VPSS_DB_BORD_FLAG25.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG25.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG25.bits.vpss_db_bord_flag_25 = vpss_db_bord_flag_25;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG25.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG25.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_26)
//{
//  U_VPSS_DB_BORD_FLAG26 VPSS_DB_BORD_FLAG26;
//
//  VPSS_DB_BORD_FLAG26.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG26.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG26.bits.vpss_db_bord_flag_26 = vpss_db_bord_flag_26;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG26.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG26.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_27)
//{
//  U_VPSS_DB_BORD_FLAG27 VPSS_DB_BORD_FLAG27;
//
//  VPSS_DB_BORD_FLAG27.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG27.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG27.bits.vpss_db_bord_flag_27 = vpss_db_bord_flag_27;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG27.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG27.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_28)
//{
//  U_VPSS_DB_BORD_FLAG28 VPSS_DB_BORD_FLAG28;
//
//  VPSS_DB_BORD_FLAG28.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG28.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG28.bits.vpss_db_bord_flag_28 = vpss_db_bord_flag_28;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG28.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG28.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_29)
//{
//  U_VPSS_DB_BORD_FLAG29 VPSS_DB_BORD_FLAG29;
//
//  VPSS_DB_BORD_FLAG29.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG29.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG29.bits.vpss_db_bord_flag_29 = vpss_db_bord_flag_29;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG29.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG29.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_30)
//{
//  U_VPSS_DB_BORD_FLAG30 VPSS_DB_BORD_FLAG30;
//
//  VPSS_DB_BORD_FLAG30.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG30.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG30.bits.vpss_db_bord_flag_30 = vpss_db_bord_flag_30;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG30.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG30.u32);
//
//  return ;
//}
//
//
//
//HI_VOID VPSS_Sys_SetVpssDbBordFlag31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_db_bord_flag_31)
//{
//  U_VPSS_DB_BORD_FLAG31 VPSS_DB_BORD_FLAG31;
//
//  VPSS_DB_BORD_FLAG31.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DB_BORD_FLAG31.u32) + u32AddrOffset));
//  VPSS_DB_BORD_FLAG31.bits.vpss_db_bord_flag_31 = vpss_db_bord_flag_31;
//  VPSS_RegWrite((&(pstVpssRegs->VPSS_DB_BORD_FLAG31.u32) + u32AddrOffset),VPSS_DB_BORD_FLAG31.u32);
//
//  return ;
//}



HI_VOID VPSS_Sys_SetTestEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 test_en)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset));
    VPSS_SNR_ENABLE.bits.test_en = test_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeprefilteren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgeprefilteren)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset));
    VPSS_SNR_ENABLE.bits.edgeprefilteren = edgeprefilteren;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetColorweighten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 colorweighten)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset));
    VPSS_SNR_ENABLE.bits.colorweighten = colorweighten;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionedgeweighten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motionedgeweighten)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset));
    VPSS_SNR_ENABLE.bits.motionedgeweighten = motionedgeweighten;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCnr2den(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cnr2den)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset));
    VPSS_SNR_ENABLE.bits.cnr2den = cnr2den;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset), VPSS_SNR_ENABLE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYnr2den(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ynr2den)
{
    U_VPSS_SNR_ENABLE VPSS_SNR_ENABLE;

    VPSS_SNR_ENABLE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset));
    VPSS_SNR_ENABLE.bits.ynr2den = ynr2den;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_ENABLE.u32) + u32AddrOffset), VPSS_SNR_ENABLE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgeoriratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgeoriratio)
{
    U_VPSS_SNR_EDGE_RATIORANGE VPSS_SNR_EDGE_RATIORANGE;

    VPSS_SNR_EDGE_RATIORANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIORANGE.bits.edgeoriratio = edgeoriratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIORANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeminratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgeminratio)
{
    U_VPSS_SNR_EDGE_RATIORANGE VPSS_SNR_EDGE_RATIORANGE;

    VPSS_SNR_EDGE_RATIORANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIORANGE.bits.edgeminratio = edgeminratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIORANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemaxratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemaxratio)
{
    U_VPSS_SNR_EDGE_RATIORANGE VPSS_SNR_EDGE_RATIORANGE;

    VPSS_SNR_EDGE_RATIORANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIORANGE.bits.edgemaxratio = edgemaxratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIORANGE.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIORANGE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgeoristrength(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgeoristrength)
{
    U_VPSS_SNR_EDGE_STRRANGE VPSS_SNR_EDGE_STRRANGE;

    VPSS_SNR_EDGE_STRRANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STRRANGE.bits.edgeoristrength = edgeoristrength;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32) + u32AddrOffset), VPSS_SNR_EDGE_STRRANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgeminstrength(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgeminstrength)
{
    U_VPSS_SNR_EDGE_STRRANGE VPSS_SNR_EDGE_STRRANGE;

    VPSS_SNR_EDGE_STRRANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STRRANGE.bits.edgeminstrength = edgeminstrength;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32) + u32AddrOffset), VPSS_SNR_EDGE_STRRANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemaxstrength(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemaxstrength)
{
    U_VPSS_SNR_EDGE_STRRANGE VPSS_SNR_EDGE_STRRANGE;

    VPSS_SNR_EDGE_STRRANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STRRANGE.bits.edgemaxstrength = edgemaxstrength;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STRRANGE.u32) + u32AddrOffset), VPSS_SNR_EDGE_STRRANGE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgestrth3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgestrth3)
{
    U_VPSS_SNR_EDGE_STRTH VPSS_SNR_EDGE_STRTH;

    VPSS_SNR_EDGE_STRTH.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STRTH.bits.edgestrth3 = edgestrth3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32) + u32AddrOffset), VPSS_SNR_EDGE_STRTH.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgestrth2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgestrth2)
{
    U_VPSS_SNR_EDGE_STRTH VPSS_SNR_EDGE_STRTH;

    VPSS_SNR_EDGE_STRTH.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STRTH.bits.edgestrth2 = edgestrth2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32) + u32AddrOffset), VPSS_SNR_EDGE_STRTH.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgestrth1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgestrth1)
{
    U_VPSS_SNR_EDGE_STRTH VPSS_SNR_EDGE_STRTH;

    VPSS_SNR_EDGE_STRTH.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STRTH.bits.edgestrth1 = edgestrth1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STRTH.u32) + u32AddrOffset), VPSS_SNR_EDGE_STRTH.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgestrk3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgestrk3)
{
    U_VPSS_SNR_EDGE_STRK VPSS_SNR_EDGE_STRK;

    VPSS_SNR_EDGE_STRK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STRK.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STRK.bits.edgestrk3 = edgestrk3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STRK.u32) + u32AddrOffset), VPSS_SNR_EDGE_STRK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgestrk2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgestrk2)
{
    U_VPSS_SNR_EDGE_STRK VPSS_SNR_EDGE_STRK;

    VPSS_SNR_EDGE_STRK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STRK.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STRK.bits.edgestrk2 = edgestrk2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STRK.u32) + u32AddrOffset), VPSS_SNR_EDGE_STRK.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgestrk1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgestrk1)
{
    U_VPSS_SNR_EDGE_STRK VPSS_SNR_EDGE_STRK;

    VPSS_SNR_EDGE_STRK.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STRK.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STRK.bits.edgestrk1 = edgestrk1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STRK.u32) + u32AddrOffset), VPSS_SNR_EDGE_STRK.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgemeanth3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeanth3)
{
    U_VPSS_SNR_EDGE_MEANTH1 VPSS_SNR_EDGE_MEANTH1;

    VPSS_SNR_EDGE_MEANTH1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANTH1.bits.edgemeanth3 = edgemeanth3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANTH1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeanth2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeanth2)
{
    U_VPSS_SNR_EDGE_MEANTH1 VPSS_SNR_EDGE_MEANTH1;

    VPSS_SNR_EDGE_MEANTH1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANTH1.bits.edgemeanth2 = edgemeanth2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANTH1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeanth1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeanth1)
{
    U_VPSS_SNR_EDGE_MEANTH1 VPSS_SNR_EDGE_MEANTH1;

    VPSS_SNR_EDGE_MEANTH1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANTH1.bits.edgemeanth1 = edgemeanth1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH1.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANTH1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgemeanth6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeanth6)
{
    U_VPSS_SNR_EDGE_MEANTH2 VPSS_SNR_EDGE_MEANTH2;

    VPSS_SNR_EDGE_MEANTH2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANTH2.bits.edgemeanth6 = edgemeanth6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANTH2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeanth5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeanth5)
{
    U_VPSS_SNR_EDGE_MEANTH2 VPSS_SNR_EDGE_MEANTH2;

    VPSS_SNR_EDGE_MEANTH2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANTH2.bits.edgemeanth5 = edgemeanth5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANTH2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeanth4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeanth4)
{
    U_VPSS_SNR_EDGE_MEANTH2 VPSS_SNR_EDGE_MEANTH2;

    VPSS_SNR_EDGE_MEANTH2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANTH2.bits.edgemeanth4 = edgemeanth4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH2.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANTH2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgemeanth8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeanth8)
{
    U_VPSS_SNR_EDGE_MEANTH3 VPSS_SNR_EDGE_MEANTH3;

    VPSS_SNR_EDGE_MEANTH3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH3.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANTH3.bits.edgemeanth8 = edgemeanth8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH3.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANTH3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeanth7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeanth7)
{
    U_VPSS_SNR_EDGE_MEANTH3 VPSS_SNR_EDGE_MEANTH3;

    VPSS_SNR_EDGE_MEANTH3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH3.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANTH3.bits.edgemeanth7 = edgemeanth7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANTH3.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANTH3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgemeank4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeank4)
{
    U_VPSS_SNR_EDGE_MEANK1 VPSS_SNR_EDGE_MEANK1;

    VPSS_SNR_EDGE_MEANK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANK1.bits.edgemeank4 = edgemeank4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANK1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeank3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeank3)
{
    U_VPSS_SNR_EDGE_MEANK1 VPSS_SNR_EDGE_MEANK1;

    VPSS_SNR_EDGE_MEANK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANK1.bits.edgemeank3 = edgemeank3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANK1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeank2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeank2)
{
    U_VPSS_SNR_EDGE_MEANK1 VPSS_SNR_EDGE_MEANK1;

    VPSS_SNR_EDGE_MEANK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANK1.bits.edgemeank2 = edgemeank2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANK1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeank1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeank1)
{
    U_VPSS_SNR_EDGE_MEANK1 VPSS_SNR_EDGE_MEANK1;

    VPSS_SNR_EDGE_MEANK1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANK1.bits.edgemeank1 = edgemeank1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK1.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANK1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdgemeank8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeank8)
{
    U_VPSS_SNR_EDGE_MEANK2 VPSS_SNR_EDGE_MEANK2;

    VPSS_SNR_EDGE_MEANK2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANK2.bits.edgemeank8 = edgemeank8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANK2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeank7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeank7)
{
    U_VPSS_SNR_EDGE_MEANK2 VPSS_SNR_EDGE_MEANK2;

    VPSS_SNR_EDGE_MEANK2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANK2.bits.edgemeank7 = edgemeank7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANK2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeank6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeank6)
{
    U_VPSS_SNR_EDGE_MEANK2 VPSS_SNR_EDGE_MEANK2;

    VPSS_SNR_EDGE_MEANK2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANK2.bits.edgemeank6 = edgemeank6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANK2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdgemeank5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edgemeank5)
{
    U_VPSS_SNR_EDGE_MEANK2 VPSS_SNR_EDGE_MEANK2;

    VPSS_SNR_EDGE_MEANK2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_MEANK2.bits.edgemeank5 = edgemeank5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_MEANK2.u32) + u32AddrOffset), VPSS_SNR_EDGE_MEANK2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetC2dwinheight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 c2dwinheight)
{
    U_VPSS_SNR_WIN VPSS_SNR_WIN;

    VPSS_SNR_WIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_WIN.u32) + u32AddrOffset));
    VPSS_SNR_WIN.bits.c2dwinheight = c2dwinheight;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_WIN.u32) + u32AddrOffset), VPSS_SNR_WIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetC2dwinwidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 c2dwinwidth)
{
    U_VPSS_SNR_WIN VPSS_SNR_WIN;

    VPSS_SNR_WIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_WIN.u32) + u32AddrOffset));
    VPSS_SNR_WIN.bits.c2dwinwidth = c2dwinwidth;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_WIN.u32) + u32AddrOffset), VPSS_SNR_WIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetY2dwinheight(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 y2dwinheight)
{
    U_VPSS_SNR_WIN VPSS_SNR_WIN;

    VPSS_SNR_WIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_WIN.u32) + u32AddrOffset));
    VPSS_SNR_WIN.bits.y2dwinheight = y2dwinheight;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_WIN.u32) + u32AddrOffset), VPSS_SNR_WIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetY2dwinwidth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 y2dwinwidth)
{
    U_VPSS_SNR_WIN VPSS_SNR_WIN;

    VPSS_SNR_WIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_WIN.u32) + u32AddrOffset));
    VPSS_SNR_WIN.bits.y2dwinwidth = y2dwinwidth;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_WIN.u32) + u32AddrOffset), VPSS_SNR_WIN.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCsnrstr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 csnrstr)
{
    U_VPSS_SNR_STR VPSS_SNR_STR;

    VPSS_SNR_STR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_STR.u32) + u32AddrOffset));
    VPSS_SNR_STR.bits.csnrstr = csnrstr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_STR.u32) + u32AddrOffset), VPSS_SNR_STR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYsnrstr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ysnrstr)
{
    U_VPSS_SNR_STR VPSS_SNR_STR;

    VPSS_SNR_STR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_STR.u32) + u32AddrOffset));
    VPSS_SNR_STR.bits.ysnrstr = ysnrstr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_STR.u32) + u32AddrOffset), VPSS_SNR_STR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetStroffset3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 stroffset3)
{
    U_VPSS_SNR_STR_OFFSET VPSS_SNR_STR_OFFSET;

    VPSS_SNR_STR_OFFSET.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_STR_OFFSET.u32) + u32AddrOffset));
    VPSS_SNR_STR_OFFSET.bits.stroffset3 = stroffset3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_STR_OFFSET.u32) + u32AddrOffset), VPSS_SNR_STR_OFFSET.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStroffset2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 stroffset2)
{
    U_VPSS_SNR_STR_OFFSET VPSS_SNR_STR_OFFSET;

    VPSS_SNR_STR_OFFSET.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_STR_OFFSET.u32) + u32AddrOffset));
    VPSS_SNR_STR_OFFSET.bits.stroffset2 = stroffset2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_STR_OFFSET.u32) + u32AddrOffset), VPSS_SNR_STR_OFFSET.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStroffset1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 stroffset1)
{
    U_VPSS_SNR_STR_OFFSET VPSS_SNR_STR_OFFSET;

    VPSS_SNR_STR_OFFSET.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_STR_OFFSET.u32) + u32AddrOffset));
    VPSS_SNR_STR_OFFSET.bits.stroffset1 = stroffset1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_STR_OFFSET.u32) + u32AddrOffset), VPSS_SNR_STR_OFFSET.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStroffset0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 stroffset0)
{
    U_VPSS_SNR_STR_OFFSET VPSS_SNR_STR_OFFSET;

    VPSS_SNR_STR_OFFSET.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_STR_OFFSET.u32) + u32AddrOffset));
    VPSS_SNR_STR_OFFSET.bits.stroffset0 = stroffset0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_STR_OFFSET.u32) + u32AddrOffset), VPSS_SNR_STR_OFFSET.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCstradjust(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cstradjust)
{
    U_VPSS_SNR_STR_ADJUST VPSS_SNR_STR_ADJUST;

    VPSS_SNR_STR_ADJUST.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_STR_ADJUST.u32) + u32AddrOffset));
    VPSS_SNR_STR_ADJUST.bits.cstradjust = cstradjust;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_STR_ADJUST.u32) + u32AddrOffset), VPSS_SNR_STR_ADJUST.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYstradjust(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ystradjust)
{
    U_VPSS_SNR_STR_ADJUST VPSS_SNR_STR_ADJUST;

    VPSS_SNR_STR_ADJUST.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_STR_ADJUST.u32) + u32AddrOffset));
    VPSS_SNR_STR_ADJUST.bits.ystradjust = ystradjust;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_STR_ADJUST.u32) + u32AddrOffset), VPSS_SNR_STR_ADJUST.u32);

    return ;
}



HI_VOID VPSS_Sys_SetScenechangeth(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechangeth)
{
    U_VPSS_SNR_SCHANGE_TH VPSS_SNR_SCHANGE_TH;

    VPSS_SNR_SCHANGE_TH.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_SCHANGE_TH.u32) + u32AddrOffset));
    VPSS_SNR_SCHANGE_TH.bits.scenechangeth = scenechangeth;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_SCHANGE_TH.u32) + u32AddrOffset), VPSS_SNR_SCHANGE_TH.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ratio3)
{
    U_VPSS_SNR_EDGE_RATIO_1 VPSS_SNR_EDGE_RATIO_1;

    VPSS_SNR_EDGE_RATIO_1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIO_1.bits.ratio3 = ratio3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIO_1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ratio2)
{
    U_VPSS_SNR_EDGE_RATIO_1 VPSS_SNR_EDGE_RATIO_1;

    VPSS_SNR_EDGE_RATIO_1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIO_1.bits.ratio2 = ratio2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIO_1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ratio1)
{
    U_VPSS_SNR_EDGE_RATIO_1 VPSS_SNR_EDGE_RATIO_1;

    VPSS_SNR_EDGE_RATIO_1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIO_1.bits.ratio1 = ratio1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_1.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIO_1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRatio6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ratio6)
{
    U_VPSS_SNR_EDGE_RATIO_2 VPSS_SNR_EDGE_RATIO_2;

    VPSS_SNR_EDGE_RATIO_2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIO_2.bits.ratio6 = ratio6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIO_2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRatio5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ratio5)
{
    U_VPSS_SNR_EDGE_RATIO_2 VPSS_SNR_EDGE_RATIO_2;

    VPSS_SNR_EDGE_RATIO_2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIO_2.bits.ratio5 = ratio5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIO_2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ratio4)
{
    U_VPSS_SNR_EDGE_RATIO_2 VPSS_SNR_EDGE_RATIO_2;

    VPSS_SNR_EDGE_RATIO_2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIO_2.bits.ratio4 = ratio4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_2.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIO_2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRatio8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ratio8)
{
    U_VPSS_SNR_EDGE_RATIO_3 VPSS_SNR_EDGE_RATIO_3;

    VPSS_SNR_EDGE_RATIO_3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_3.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIO_3.bits.ratio8 = ratio8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_3.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIO_3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetRatio7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ratio7)
{
    U_VPSS_SNR_EDGE_RATIO_3 VPSS_SNR_EDGE_RATIO_3;

    VPSS_SNR_EDGE_RATIO_3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_3.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_RATIO_3.bits.ratio7 = ratio7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_RATIO_3.u32) + u32AddrOffset), VPSS_SNR_EDGE_RATIO_3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetEdge3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge3)
{
    U_VPSS_SNR_EDGE_STR VPSS_SNR_EDGE_STR;

    VPSS_SNR_EDGE_STR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STR.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STR.bits.edge3 = edge3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STR.u32) + u32AddrOffset), VPSS_SNR_EDGE_STR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdge2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge2)
{
    U_VPSS_SNR_EDGE_STR VPSS_SNR_EDGE_STR;

    VPSS_SNR_EDGE_STR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STR.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STR.bits.edge2 = edge2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STR.u32) + u32AddrOffset), VPSS_SNR_EDGE_STR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetEdge1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 edge1)
{
    U_VPSS_SNR_EDGE_STR VPSS_SNR_EDGE_STR;

    VPSS_SNR_EDGE_STR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_EDGE_STR.u32) + u32AddrOffset));
    VPSS_SNR_EDGE_STR.bits.edge1 = edge1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_EDGE_STR.u32) + u32AddrOffset), VPSS_SNR_EDGE_STR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetTestColorCr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 test_color_cr)
{
    U_VPSS_SNR_TEST_COLOR VPSS_SNR_TEST_COLOR;

    VPSS_SNR_TEST_COLOR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_TEST_COLOR.u32) + u32AddrOffset));
    VPSS_SNR_TEST_COLOR.bits.test_color_cr = test_color_cr;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_TEST_COLOR.u32) + u32AddrOffset), VPSS_SNR_TEST_COLOR.u32);

    return ;
}


HI_VOID VPSS_Sys_SetTestColorCb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 test_color_cb)
{
    U_VPSS_SNR_TEST_COLOR VPSS_SNR_TEST_COLOR;

    VPSS_SNR_TEST_COLOR.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_TEST_COLOR.u32) + u32AddrOffset));
    VPSS_SNR_TEST_COLOR.bits.test_color_cb = test_color_cb;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_TEST_COLOR.u32) + u32AddrOffset), VPSS_SNR_TEST_COLOR.u32);

    return ;
}



HI_VOID VPSS_Sys_SetScenechangeMode2En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechange_mode2_en)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset));
    VPSS_SNR_SCHANGE.bits.scenechange_mode2_en = scenechange_mode2_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetScenechangeBldcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechange_bldcore)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset));
    VPSS_SNR_SCHANGE.bits.scenechange_bldcore = scenechange_bldcore;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetScenechangeBldk(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechange_bldk)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset));
    VPSS_SNR_SCHANGE.bits.scenechange_bldk = scenechange_bldk;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetScenechangeMode1En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechange_mode1_en)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset));
    VPSS_SNR_SCHANGE.bits.scenechange_mode1_en = scenechange_mode1_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetScenechangeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechange_en)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset));
    VPSS_SNR_SCHANGE.bits.scenechange_en = scenechange_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset), VPSS_SNR_SCHANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetScenechangeInfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechange_info)
{
    U_VPSS_SNR_SCHANGE VPSS_SNR_SCHANGE;

    VPSS_SNR_SCHANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset));
    VPSS_SNR_SCHANGE.bits.scenechange_info = scenechange_info;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_SCHANGE.u32) + u32AddrOffset), VPSS_SNR_SCHANGE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionalpha(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motionalpha)
{
    U_VPSS_SNR_MT VPSS_SNR_MT;

    VPSS_SNR_MT.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_MT.u32) + u32AddrOffset));
    VPSS_SNR_MT.bits.motionalpha = motionalpha;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_MT.u32) + u32AddrOffset), VPSS_SNR_MT.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCbcrWeight1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cbcr_weight1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W1.bits.cbcr_weight1 = cbcr_weight1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset), VPSS_SNR_CBCR_W1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCrEnd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cr_end1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W1.bits.cr_end1 = cr_end1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset), VPSS_SNR_CBCR_W1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbEnd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cb_end1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W1.bits.cb_end1 = cb_end1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset), VPSS_SNR_CBCR_W1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCrBegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cr_begin1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W1.bits.cr_begin1 = cr_begin1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset), VPSS_SNR_CBCR_W1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbBegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cb_begin1)
{
    U_VPSS_SNR_CBCR_W1 VPSS_SNR_CBCR_W1;

    VPSS_SNR_CBCR_W1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W1.bits.cb_begin1 = cb_begin1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W1.u32) + u32AddrOffset), VPSS_SNR_CBCR_W1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCbcrWeight2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cbcr_weight2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W2.bits.cbcr_weight2 = cbcr_weight2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset), VPSS_SNR_CBCR_W2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCrEnd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cr_end2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W2.bits.cr_end2 = cr_end2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset), VPSS_SNR_CBCR_W2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbEnd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cb_end2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W2.bits.cb_end2 = cb_end2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset), VPSS_SNR_CBCR_W2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCrBegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cr_begin2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W2.bits.cr_begin2 = cr_begin2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset), VPSS_SNR_CBCR_W2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbBegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cb_begin2)
{
    U_VPSS_SNR_CBCR_W2 VPSS_SNR_CBCR_W2;

    VPSS_SNR_CBCR_W2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset));
    VPSS_SNR_CBCR_W2.bits.cb_begin2 = cb_begin2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_SNR_CBCR_W2.u32) + u32AddrOffset), VPSS_SNR_CBCR_W2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut07(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut07)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut07 = motion_edge_lut07;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut06(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut06)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut06 = motion_edge_lut06;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut05(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut05)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut05 = motion_edge_lut05;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut04(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut04)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut04 = motion_edge_lut04;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut03(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut03)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut03 = motion_edge_lut03;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut02(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut02)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut02 = motion_edge_lut02;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut01(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut01)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut01 = motion_edge_lut01;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset), MOTION_EDGE_LUT_01.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut00(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut00)
{
    U_MOTION_EDGE_LUT_01 MOTION_EDGE_LUT_01;

    MOTION_EDGE_LUT_01.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_01.bits.motion_edge_lut00 = motion_edge_lut00;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_01.u32) + u32AddrOffset), MOTION_EDGE_LUT_01.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut0f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut0f)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0f = motion_edge_lut0f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut0e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut0e)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0e = motion_edge_lut0e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut0d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut0d)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0d = motion_edge_lut0d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut0c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut0c)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0c = motion_edge_lut0c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut0b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut0b)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0b = motion_edge_lut0b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut0a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut0a)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut0a = motion_edge_lut0a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut09(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut09)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut09 = motion_edge_lut09;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset), MOTION_EDGE_LUT_02.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut08(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut08)
{
    U_MOTION_EDGE_LUT_02 MOTION_EDGE_LUT_02;

    MOTION_EDGE_LUT_02.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_02.bits.motion_edge_lut08 = motion_edge_lut08;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_02.u32) + u32AddrOffset), MOTION_EDGE_LUT_02.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut17)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut17 = motion_edge_lut17;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut16)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut16 = motion_edge_lut16;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut15)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut15 = motion_edge_lut15;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut14)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut14 = motion_edge_lut14;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut13)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut13 = motion_edge_lut13;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut12)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut12 = motion_edge_lut12;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut11)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut11 = motion_edge_lut11;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset), MOTION_EDGE_LUT_03.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut10)
{
    U_MOTION_EDGE_LUT_03 MOTION_EDGE_LUT_03;

    MOTION_EDGE_LUT_03.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_03.bits.motion_edge_lut10 = motion_edge_lut10;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_03.u32) + u32AddrOffset), MOTION_EDGE_LUT_03.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut1f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut1f)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1f = motion_edge_lut1f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut1e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut1e)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1e = motion_edge_lut1e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut1d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut1d)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1d = motion_edge_lut1d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut1c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut1c)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1c = motion_edge_lut1c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut1b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut1b)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1b = motion_edge_lut1b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut1a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut1a)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut1a = motion_edge_lut1a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut19)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut19 = motion_edge_lut19;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset), MOTION_EDGE_LUT_04.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut18)
{
    U_MOTION_EDGE_LUT_04 MOTION_EDGE_LUT_04;

    MOTION_EDGE_LUT_04.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_04.bits.motion_edge_lut18 = motion_edge_lut18;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_04.u32) + u32AddrOffset), MOTION_EDGE_LUT_04.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut27)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut27 = motion_edge_lut27;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut26)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut26 = motion_edge_lut26;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut25)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut25 = motion_edge_lut25;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut24)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut24 = motion_edge_lut24;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut23)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut23 = motion_edge_lut23;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut22)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut22 = motion_edge_lut22;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut21)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut21 = motion_edge_lut21;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset), MOTION_EDGE_LUT_05.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut20)
{
    U_MOTION_EDGE_LUT_05 MOTION_EDGE_LUT_05;

    MOTION_EDGE_LUT_05.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_05.bits.motion_edge_lut20 = motion_edge_lut20;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_05.u32) + u32AddrOffset), MOTION_EDGE_LUT_05.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut2f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut2f)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2f = motion_edge_lut2f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut2e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut2e)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2e = motion_edge_lut2e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut2d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut2d)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2d = motion_edge_lut2d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut2c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut2c)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2c = motion_edge_lut2c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut2b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut2b)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2b = motion_edge_lut2b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut2a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut2a)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut2a = motion_edge_lut2a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut29)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut29 = motion_edge_lut29;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset), MOTION_EDGE_LUT_06.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut28)
{
    U_MOTION_EDGE_LUT_06 MOTION_EDGE_LUT_06;

    MOTION_EDGE_LUT_06.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_06.bits.motion_edge_lut28 = motion_edge_lut28;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_06.u32) + u32AddrOffset), MOTION_EDGE_LUT_06.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut37)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut37 = motion_edge_lut37;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut36)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut36 = motion_edge_lut36;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut35)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut35 = motion_edge_lut35;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut34)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut34 = motion_edge_lut34;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut33)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut33 = motion_edge_lut33;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut32)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut32 = motion_edge_lut32;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut31)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut31 = motion_edge_lut31;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset), MOTION_EDGE_LUT_07.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut30)
{
    U_MOTION_EDGE_LUT_07 MOTION_EDGE_LUT_07;

    MOTION_EDGE_LUT_07.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_07.bits.motion_edge_lut30 = motion_edge_lut30;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_07.u32) + u32AddrOffset), MOTION_EDGE_LUT_07.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut3f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut3f)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3f = motion_edge_lut3f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut3e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut3e)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3e = motion_edge_lut3e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut3d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut3d)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3d = motion_edge_lut3d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut3c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut3c)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3c = motion_edge_lut3c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut3b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut3b)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3b = motion_edge_lut3b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut3a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut3a)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut3a = motion_edge_lut3a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut39(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut39)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut39 = motion_edge_lut39;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset), MOTION_EDGE_LUT_08.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut38)
{
    U_MOTION_EDGE_LUT_08 MOTION_EDGE_LUT_08;

    MOTION_EDGE_LUT_08.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_08.bits.motion_edge_lut38 = motion_edge_lut38;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_08.u32) + u32AddrOffset), MOTION_EDGE_LUT_08.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut47(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut47)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut47 = motion_edge_lut47;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut46(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut46)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut46 = motion_edge_lut46;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut45(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut45)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut45 = motion_edge_lut45;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut44(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut44)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut44 = motion_edge_lut44;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut43)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut43 = motion_edge_lut43;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut42)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut42 = motion_edge_lut42;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut41)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut41 = motion_edge_lut41;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset), MOTION_EDGE_LUT_09.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut40)
{
    U_MOTION_EDGE_LUT_09 MOTION_EDGE_LUT_09;

    MOTION_EDGE_LUT_09.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_09.bits.motion_edge_lut40 = motion_edge_lut40;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_09.u32) + u32AddrOffset), MOTION_EDGE_LUT_09.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut4f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut4f)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4f = motion_edge_lut4f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut4e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut4e)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4e = motion_edge_lut4e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut4d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut4d)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4d = motion_edge_lut4d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut4c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut4c)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4c = motion_edge_lut4c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut4b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut4b)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4b = motion_edge_lut4b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut4a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut4a)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut4a = motion_edge_lut4a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut49(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut49)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut49 = motion_edge_lut49;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset), MOTION_EDGE_LUT_10.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut48(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut48)
{
    U_MOTION_EDGE_LUT_10 MOTION_EDGE_LUT_10;

    MOTION_EDGE_LUT_10.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_10.bits.motion_edge_lut48 = motion_edge_lut48;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_10.u32) + u32AddrOffset), MOTION_EDGE_LUT_10.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut57(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut57)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut57 = motion_edge_lut57;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut56(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut56)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut56 = motion_edge_lut56;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut55(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut55)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut55 = motion_edge_lut55;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut54(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut54)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut54 = motion_edge_lut54;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut53(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut53)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut53 = motion_edge_lut53;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut52(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut52)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut52 = motion_edge_lut52;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut51(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut51)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut51 = motion_edge_lut51;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset), MOTION_EDGE_LUT_11.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut50(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut50)
{
    U_MOTION_EDGE_LUT_11 MOTION_EDGE_LUT_11;

    MOTION_EDGE_LUT_11.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_11.bits.motion_edge_lut50 = motion_edge_lut50;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_11.u32) + u32AddrOffset), MOTION_EDGE_LUT_11.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut5f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut5f)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5f = motion_edge_lut5f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut5e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut5e)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5e = motion_edge_lut5e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut5d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut5d)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5d = motion_edge_lut5d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut5c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut5c)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5c = motion_edge_lut5c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut5b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut5b)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5b = motion_edge_lut5b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut5a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut5a)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut5a = motion_edge_lut5a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut59(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut59)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut59 = motion_edge_lut59;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset), MOTION_EDGE_LUT_12.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut58(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut58)
{
    U_MOTION_EDGE_LUT_12 MOTION_EDGE_LUT_12;

    MOTION_EDGE_LUT_12.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_12.bits.motion_edge_lut58 = motion_edge_lut58;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_12.u32) + u32AddrOffset), MOTION_EDGE_LUT_12.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut67(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut67)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut67 = motion_edge_lut67;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut66(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut66)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut66 = motion_edge_lut66;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut65(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut65)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut65 = motion_edge_lut65;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut64(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut64)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut64 = motion_edge_lut64;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut63(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut63)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut63 = motion_edge_lut63;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut62(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut62)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut62 = motion_edge_lut62;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut61(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut61)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut61 = motion_edge_lut61;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset), MOTION_EDGE_LUT_13.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut60(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut60)
{
    U_MOTION_EDGE_LUT_13 MOTION_EDGE_LUT_13;

    MOTION_EDGE_LUT_13.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_13.bits.motion_edge_lut60 = motion_edge_lut60;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_13.u32) + u32AddrOffset), MOTION_EDGE_LUT_13.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut6f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut6f)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6f = motion_edge_lut6f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut6e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut6e)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6e = motion_edge_lut6e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut6d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut6d)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6d = motion_edge_lut6d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut6c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut6c)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6c = motion_edge_lut6c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut6b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut6b)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6b = motion_edge_lut6b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut6a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut6a)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut6a = motion_edge_lut6a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut69(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut69)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut69 = motion_edge_lut69;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset), MOTION_EDGE_LUT_14.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut68(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut68)
{
    U_MOTION_EDGE_LUT_14 MOTION_EDGE_LUT_14;

    MOTION_EDGE_LUT_14.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_14.bits.motion_edge_lut68 = motion_edge_lut68;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_14.u32) + u32AddrOffset), MOTION_EDGE_LUT_14.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut77(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut77)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut77 = motion_edge_lut77;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut76(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut76)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut76 = motion_edge_lut76;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut75(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut75)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut75 = motion_edge_lut75;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut74(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut74)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut74 = motion_edge_lut74;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut73(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut73)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut73 = motion_edge_lut73;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut72(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut72)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut72 = motion_edge_lut72;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut71(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut71)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut71 = motion_edge_lut71;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset), MOTION_EDGE_LUT_15.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut70(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut70)
{
    U_MOTION_EDGE_LUT_15 MOTION_EDGE_LUT_15;

    MOTION_EDGE_LUT_15.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_15.bits.motion_edge_lut70 = motion_edge_lut70;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_15.u32) + u32AddrOffset), MOTION_EDGE_LUT_15.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut7f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut7f)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7f = motion_edge_lut7f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut7e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut7e)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7e = motion_edge_lut7e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut7d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut7d)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7d = motion_edge_lut7d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut7c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut7c)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7c = motion_edge_lut7c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut7b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut7b)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7b = motion_edge_lut7b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut7a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut7a)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut7a = motion_edge_lut7a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut79(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut79)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut79 = motion_edge_lut79;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset), MOTION_EDGE_LUT_16.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut78(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut78)
{
    U_MOTION_EDGE_LUT_16 MOTION_EDGE_LUT_16;

    MOTION_EDGE_LUT_16.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_16.bits.motion_edge_lut78 = motion_edge_lut78;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_16.u32) + u32AddrOffset), MOTION_EDGE_LUT_16.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut87(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut87)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut87 = motion_edge_lut87;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut86(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut86)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut86 = motion_edge_lut86;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut85(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut85)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut85 = motion_edge_lut85;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut84(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut84)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut84 = motion_edge_lut84;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut83(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut83)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut83 = motion_edge_lut83;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut82(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut82)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut82 = motion_edge_lut82;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut81(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut81)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut81 = motion_edge_lut81;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset), MOTION_EDGE_LUT_17.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut80(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut80)
{
    U_MOTION_EDGE_LUT_17 MOTION_EDGE_LUT_17;

    MOTION_EDGE_LUT_17.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_17.bits.motion_edge_lut80 = motion_edge_lut80;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_17.u32) + u32AddrOffset), MOTION_EDGE_LUT_17.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut8f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut8f)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8f = motion_edge_lut8f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut8e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut8e)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8e = motion_edge_lut8e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut8d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut8d)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8d = motion_edge_lut8d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut8c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut8c)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8c = motion_edge_lut8c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut8b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut8b)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8b = motion_edge_lut8b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut8a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut8a)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut8a = motion_edge_lut8a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut89(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut89)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut89 = motion_edge_lut89;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset), MOTION_EDGE_LUT_18.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut88(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut88)
{
    U_MOTION_EDGE_LUT_18 MOTION_EDGE_LUT_18;

    MOTION_EDGE_LUT_18.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_18.bits.motion_edge_lut88 = motion_edge_lut88;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_18.u32) + u32AddrOffset), MOTION_EDGE_LUT_18.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut97(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut97)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut97 = motion_edge_lut97;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut96(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut96)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut96 = motion_edge_lut96;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut95(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut95)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut95 = motion_edge_lut95;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut94(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut94)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut94 = motion_edge_lut94;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut93(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut93)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut93 = motion_edge_lut93;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut92(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut92)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut92 = motion_edge_lut92;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut91(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut91)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut91 = motion_edge_lut91;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset), MOTION_EDGE_LUT_19.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut90(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut90)
{
    U_MOTION_EDGE_LUT_19 MOTION_EDGE_LUT_19;

    MOTION_EDGE_LUT_19.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_19.bits.motion_edge_lut90 = motion_edge_lut90;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_19.u32) + u32AddrOffset), MOTION_EDGE_LUT_19.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLut9f(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut9f)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9f = motion_edge_lut9f;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut9e(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut9e)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9e = motion_edge_lut9e;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut9d(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut9d)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9d = motion_edge_lut9d;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut9c(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut9c)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9c = motion_edge_lut9c;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut9b(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut9b)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9b = motion_edge_lut9b;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut9a(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut9a)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut9a = motion_edge_lut9a;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut99(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut99)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut99 = motion_edge_lut99;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset), MOTION_EDGE_LUT_20.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLut98(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lut98)
{
    U_MOTION_EDGE_LUT_20 MOTION_EDGE_LUT_20;

    MOTION_EDGE_LUT_20.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_20.bits.motion_edge_lut98 = motion_edge_lut98;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_20.u32) + u32AddrOffset), MOTION_EDGE_LUT_20.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLuta7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta7)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta7 = motion_edge_luta7;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuta6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta6)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta6 = motion_edge_luta6;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuta5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta5)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta5 = motion_edge_luta5;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuta4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta4)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta4 = motion_edge_luta4;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuta3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta3)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta3 = motion_edge_luta3;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuta2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta2)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta2 = motion_edge_luta2;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuta1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta1)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta1 = motion_edge_luta1;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset), MOTION_EDGE_LUT_21.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuta0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta0)
{
    U_MOTION_EDGE_LUT_21 MOTION_EDGE_LUT_21;

    MOTION_EDGE_LUT_21.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_21.bits.motion_edge_luta0 = motion_edge_luta0;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_21.u32) + u32AddrOffset), MOTION_EDGE_LUT_21.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutaf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutaf)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutaf = motion_edge_lutaf;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutae(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutae)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutae = motion_edge_lutae;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutad(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutad)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutad = motion_edge_lutad;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutac(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutac)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutac = motion_edge_lutac;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutab(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutab)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutab = motion_edge_lutab;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutaa(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutaa)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_22.bits.motion_edge_lutaa = motion_edge_lutaa;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuta9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta9)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_22.bits.motion_edge_luta9 = motion_edge_luta9;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset), MOTION_EDGE_LUT_22.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuta8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luta8)
{
    U_MOTION_EDGE_LUT_22 MOTION_EDGE_LUT_22;

    MOTION_EDGE_LUT_22.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_22.bits.motion_edge_luta8 = motion_edge_luta8;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_22.u32) + u32AddrOffset), MOTION_EDGE_LUT_22.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutb7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb7)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb7 = motion_edge_lutb7;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutb6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb6)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb6 = motion_edge_lutb6;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutb5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb5)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb5 = motion_edge_lutb5;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutb4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb4)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb4 = motion_edge_lutb4;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutb3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb3)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb3 = motion_edge_lutb3;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutb2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb2)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb2 = motion_edge_lutb2;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutb1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb1)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb1 = motion_edge_lutb1;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset), MOTION_EDGE_LUT_23.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutb0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb0)
{
    U_MOTION_EDGE_LUT_23 MOTION_EDGE_LUT_23;

    MOTION_EDGE_LUT_23.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_23.bits.motion_edge_lutb0 = motion_edge_lutb0;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_23.u32) + u32AddrOffset), MOTION_EDGE_LUT_23.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutbf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutbf)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbf = motion_edge_lutbf;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutbe(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutbe)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbe = motion_edge_lutbe;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutbd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutbd)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbd = motion_edge_lutbd;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutbc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutbc)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbc = motion_edge_lutbc;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutbb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutbb)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutbb = motion_edge_lutbb;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutba(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutba)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutba = motion_edge_lutba;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutb9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb9)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutb9 = motion_edge_lutb9;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset), MOTION_EDGE_LUT_24.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutb8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutb8)
{
    U_MOTION_EDGE_LUT_24 MOTION_EDGE_LUT_24;

    MOTION_EDGE_LUT_24.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_24.bits.motion_edge_lutb8 = motion_edge_lutb8;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_24.u32) + u32AddrOffset), MOTION_EDGE_LUT_24.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutc7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc7)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc7 = motion_edge_lutc7;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutc6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc6)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc6 = motion_edge_lutc6;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutc5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc5)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc5 = motion_edge_lutc5;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutc4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc4)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc4 = motion_edge_lutc4;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutc3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc3)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc3 = motion_edge_lutc3;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutc2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc2)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc2 = motion_edge_lutc2;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutc1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc1)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc1 = motion_edge_lutc1;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset), MOTION_EDGE_LUT_25.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutc0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc0)
{
    U_MOTION_EDGE_LUT_25 MOTION_EDGE_LUT_25;

    MOTION_EDGE_LUT_25.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_25.bits.motion_edge_lutc0 = motion_edge_lutc0;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_25.u32) + u32AddrOffset), MOTION_EDGE_LUT_25.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutcf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutcf)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutcf = motion_edge_lutcf;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutce(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutce)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutce = motion_edge_lutce;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutcd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutcd)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutcd = motion_edge_lutcd;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutcc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutcc)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutcc = motion_edge_lutcc;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutcb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutcb)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutcb = motion_edge_lutcb;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutca(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutca)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutca = motion_edge_lutca;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutc9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc9)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutc9 = motion_edge_lutc9;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset), MOTION_EDGE_LUT_26.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutc8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutc8)
{
    U_MOTION_EDGE_LUT_26 MOTION_EDGE_LUT_26;

    MOTION_EDGE_LUT_26.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_26.bits.motion_edge_lutc8 = motion_edge_lutc8;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_26.u32) + u32AddrOffset), MOTION_EDGE_LUT_26.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutd7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd7)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd7 = motion_edge_lutd7;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutd6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd6)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd6 = motion_edge_lutd6;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutd5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd5)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd5 = motion_edge_lutd5;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutd4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd4)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd4 = motion_edge_lutd4;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutd3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd3)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd3 = motion_edge_lutd3;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutd2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd2)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd2 = motion_edge_lutd2;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutd1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd1)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd1 = motion_edge_lutd1;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset), MOTION_EDGE_LUT_27.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutd0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd0)
{
    U_MOTION_EDGE_LUT_27 MOTION_EDGE_LUT_27;

    MOTION_EDGE_LUT_27.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_27.bits.motion_edge_lutd0 = motion_edge_lutd0;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_27.u32) + u32AddrOffset), MOTION_EDGE_LUT_27.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutdf(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutdf)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutdf = motion_edge_lutdf;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutde(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutde)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutde = motion_edge_lutde;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutdd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutdd)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutdd = motion_edge_lutdd;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutdc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutdc)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutdc = motion_edge_lutdc;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutdb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutdb)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutdb = motion_edge_lutdb;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutda(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutda)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutda = motion_edge_lutda;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutd9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd9)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutd9 = motion_edge_lutd9;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset), MOTION_EDGE_LUT_28.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutd8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutd8)
{
    U_MOTION_EDGE_LUT_28 MOTION_EDGE_LUT_28;

    MOTION_EDGE_LUT_28.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_28.bits.motion_edge_lutd8 = motion_edge_lutd8;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_28.u32) + u32AddrOffset), MOTION_EDGE_LUT_28.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLute7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute7)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute7 = motion_edge_lute7;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLute6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute6)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute6 = motion_edge_lute6;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLute5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute5)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute5 = motion_edge_lute5;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLute4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute4)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute4 = motion_edge_lute4;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLute3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute3)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute3 = motion_edge_lute3;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLute2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute2)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute2 = motion_edge_lute2;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLute1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute1)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute1 = motion_edge_lute1;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset), MOTION_EDGE_LUT_29.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLute0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute0)
{
    U_MOTION_EDGE_LUT_29 MOTION_EDGE_LUT_29;

    MOTION_EDGE_LUT_29.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_29.bits.motion_edge_lute0 = motion_edge_lute0;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_29.u32) + u32AddrOffset), MOTION_EDGE_LUT_29.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutef(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutef)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_30.bits.motion_edge_lutef = motion_edge_lutef;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutee(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutee)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_30.bits.motion_edge_lutee = motion_edge_lutee;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuted(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luted)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_30.bits.motion_edge_luted = motion_edge_luted;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutec(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutec)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_30.bits.motion_edge_lutec = motion_edge_lutec;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLuteb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_luteb)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_30.bits.motion_edge_luteb = motion_edge_luteb;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutea(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutea)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_30.bits.motion_edge_lutea = motion_edge_lutea;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLute9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute9)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_30.bits.motion_edge_lute9 = motion_edge_lute9;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset), MOTION_EDGE_LUT_30.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLute8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lute8)
{
    U_MOTION_EDGE_LUT_30 MOTION_EDGE_LUT_30;

    MOTION_EDGE_LUT_30.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_30.bits.motion_edge_lute8 = motion_edge_lute8;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_30.u32) + u32AddrOffset), MOTION_EDGE_LUT_30.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutf7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf7)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf7 = motion_edge_lutf7;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutf6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf6)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf6 = motion_edge_lutf6;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutf5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf5)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf5 = motion_edge_lutf5;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutf4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf4)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf4 = motion_edge_lutf4;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutf3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf3)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf3 = motion_edge_lutf3;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutf2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf2)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf2 = motion_edge_lutf2;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutf1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf1)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf1 = motion_edge_lutf1;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset), MOTION_EDGE_LUT_31.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutf0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf0)
{
    U_MOTION_EDGE_LUT_31 MOTION_EDGE_LUT_31;

    MOTION_EDGE_LUT_31.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_31.bits.motion_edge_lutf0 = motion_edge_lutf0;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_31.u32) + u32AddrOffset), MOTION_EDGE_LUT_31.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionEdgeLutff(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutff)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutff = motion_edge_lutff;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutfe(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutfe)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfe = motion_edge_lutfe;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutfd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutfd)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfd = motion_edge_lutfd;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutfc(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutfc)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfc = motion_edge_lutfc;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutfb(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutfb)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfb = motion_edge_lutfb;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutfa(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutfa)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutfa = motion_edge_lutfa;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutf9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf9)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutf9 = motion_edge_lutf9;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset), MOTION_EDGE_LUT_32.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionEdgeLutf8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motion_edge_lutf8)
{
    U_MOTION_EDGE_LUT_32 MOTION_EDGE_LUT_32;

    MOTION_EDGE_LUT_32.u32 = VPSS_RegRead((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset));
    MOTION_EDGE_LUT_32.bits.motion_edge_lutf8 = motion_edge_lutf8;
    VPSS_RegWrite((&(pstVpssRegs->MOTION_EDGE_LUT_32.u32) + u32AddrOffset), MOTION_EDGE_LUT_32.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMarketcoor(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 marketcoor)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset));
    VPSS_TNR_CONTRL.bits.marketcoor = marketcoor;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMarketmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 marketmode)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset));
    VPSS_TNR_CONTRL.bits.marketmode = marketmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMarketmodeen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 marketmodeen)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset));
    VPSS_TNR_CONTRL.bits.marketmodeen = marketmodeen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCnren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cnren)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset));
    VPSS_TNR_CONTRL.bits.cnren = cnren;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYnren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ynren)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset));
    VPSS_TNR_CONTRL.bits.ynren = ynren;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset), VPSS_TNR_CONTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetNren(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 nren)
{
    U_VPSS_TNR_CONTRL VPSS_TNR_CONTRL;

    VPSS_TNR_CONTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset));
    VPSS_TNR_CONTRL.bits.nren = nren;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CONTRL.u32) + u32AddrOffset), VPSS_TNR_CONTRL.u32);

    return ;
}



HI_VOID VPSS_Sys_SetAlpha2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 alpha2)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.alpha2 = alpha2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetAlpha1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 alpha1)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.alpha1 = alpha1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCmotionlpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmotionlpfmode)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.cmotionlpfmode = cmotionlpfmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYmotionlpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ymotionlpfmode)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.ymotionlpfmode = ymotionlpfmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCmotioncalcmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmotioncalcmode)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.cmotioncalcmode = cmotioncalcmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYmotioncalcmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ymotioncalcmode)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.ymotioncalcmode = ymotioncalcmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeancadjshift(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 meancadjshift)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.meancadjshift = meancadjshift;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanyadjshift(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 meanyadjshift)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.meanyadjshift = meanyadjshift;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanCmotionAdjEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_cmotion_adj_en)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.mean_cmotion_adj_en = mean_cmotion_adj_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanYmotionAdjEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_ymotion_adj_en)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.mean_ymotion_adj_en = mean_ymotion_adj_en;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMdprelpfen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mdprelpfen)
{
    U_VPSS_TNR_MAMD_CTRL VPSS_TNR_MAMD_CTRL;

    VPSS_TNR_MAMD_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_CTRL.bits.mdprelpfen = mdprelpfen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAMD_CTRL.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmdcore)
{
    U_VPSS_TNR_MAMD_GAIN VPSS_TNR_MAMD_GAIN;

    VPSS_TNR_MAMD_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_GAIN.bits.cmdcore = cmdcore;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAMD_GAIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmdgain)
{
    U_VPSS_TNR_MAMD_GAIN VPSS_TNR_MAMD_GAIN;

    VPSS_TNR_MAMD_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_GAIN.bits.cmdgain = cmdgain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAMD_GAIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ymdcore)
{
    U_VPSS_TNR_MAMD_GAIN VPSS_TNR_MAMD_GAIN;

    VPSS_TNR_MAMD_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_GAIN.bits.ymdcore = ymdcore;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAMD_GAIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ymdgain)
{
    U_VPSS_TNR_MAMD_GAIN VPSS_TNR_MAMD_GAIN;

    VPSS_TNR_MAMD_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAMD_GAIN.bits.ymdgain = ymdgain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMD_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAMD_GAIN.u32);

    return ;
}



HI_VOID VPSS_Sys_SetRandomctrlmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 randomctrlmode)
{
    U_VPSS_TNR_MAND_CTRL VPSS_TNR_MAND_CTRL;

    VPSS_TNR_MAND_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAND_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAND_CTRL.bits.randomctrlmode = randomctrlmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAND_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAND_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetBlkdiffthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 blkdiffthd)
{
    U_VPSS_TNR_MAND_CTRL VPSS_TNR_MAND_CTRL;

    VPSS_TNR_MAND_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAND_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAND_CTRL.bits.blkdiffthd = blkdiffthd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAND_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAND_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetNoisedetecten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 noisedetecten)
{
    U_VPSS_TNR_MAND_CTRL VPSS_TNR_MAND_CTRL;

    VPSS_TNR_MAND_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAND_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAND_CTRL.bits.noisedetecten = noisedetecten;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAND_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAND_CTRL.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFlatthdmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 flatthdmax)
{
    U_VPSS_TNR_MAND_THD VPSS_TNR_MAND_THD;

    VPSS_TNR_MAND_THD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAND_THD.u32) + u32AddrOffset));
    VPSS_TNR_MAND_THD.bits.flatthdmax = flatthdmax;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAND_THD.u32) + u32AddrOffset), VPSS_TNR_MAND_THD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFlatthdmed(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 flatthdmed)
{
    U_VPSS_TNR_MAND_THD VPSS_TNR_MAND_THD;

    VPSS_TNR_MAND_THD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAND_THD.u32) + u32AddrOffset));
    VPSS_TNR_MAND_THD.bits.flatthdmed = flatthdmed;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAND_THD.u32) + u32AddrOffset), VPSS_TNR_MAND_THD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFlatthdmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 flatthdmin)
{
    U_VPSS_TNR_MAND_THD VPSS_TNR_MAND_THD;

    VPSS_TNR_MAND_THD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAND_THD.u32) + u32AddrOffset));
    VPSS_TNR_MAND_THD.bits.flatthdmin = flatthdmin;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAND_THD.u32) + u32AddrOffset), VPSS_TNR_MAND_THD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetSmvythd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 smvythd)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAME_CTRL.bits.smvythd = smvythd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetSmvxthd(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 smvxthd)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAME_CTRL.bits.smvxthd = smvxthd;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDiscardsmvyen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 discardsmvyen)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAME_CTRL.bits.discardsmvyen = discardsmvyen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDiscardsmvxen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 discardsmvxen)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAME_CTRL.bits.discardsmvxen = discardsmvxen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetGmAdj(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 gm_adj)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAME_CTRL.bits.gm_adj = gm_adj;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMvlpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mvlpfmode)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAME_CTRL.bits.mvlpfmode = mvlpfmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMvrefmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mvrefmode)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAME_CTRL.bits.mvrefmode = mvrefmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAME_CTRL.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionestimateen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motionestimateen)
{
    U_VPSS_TNR_MAME_CTRL VPSS_TNR_MAME_CTRL;

    VPSS_TNR_MAME_CTRL.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset));
    VPSS_TNR_MAME_CTRL.bits.motionestimateen = motionestimateen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_CTRL.u32) + u32AddrOffset), VPSS_TNR_MAME_CTRL.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMagPnlCoreXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mag_pnl_core_xmv)
{
    U_VPSS_TNR_MAME_GAIN VPSS_TNR_MAME_GAIN;

    VPSS_TNR_MAME_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAME_GAIN.bits.mag_pnl_core_xmv = mag_pnl_core_xmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAME_GAIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMagPnlGainXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mag_pnl_gain_xmv)
{
    U_VPSS_TNR_MAME_GAIN VPSS_TNR_MAME_GAIN;

    VPSS_TNR_MAME_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAME_GAIN.bits.mag_pnl_gain_xmv = mag_pnl_gain_xmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAME_GAIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMagPnlCore0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mag_pnl_core_0mv)
{
    U_VPSS_TNR_MAME_GAIN VPSS_TNR_MAME_GAIN;

    VPSS_TNR_MAME_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAME_GAIN.bits.mag_pnl_core_0mv = mag_pnl_core_0mv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAME_GAIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMagPnlGain0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mag_pnl_gain_0mv)
{
    U_VPSS_TNR_MAME_GAIN VPSS_TNR_MAME_GAIN;

    VPSS_TNR_MAME_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAME_GAIN.bits.mag_pnl_gain_0mv = mag_pnl_gain_0mv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAME_GAIN.u32);

    return ;
}



HI_VOID VPSS_Sys_SetStdPnlCoreXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 std_pnl_core_xmv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset));
    VPSS_TNR_MAME_STD_CORE.bits.std_pnl_core_xmv = std_pnl_core_xmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStdPnlGainXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 std_pnl_gain_xmv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset));
    VPSS_TNR_MAME_STD_CORE.bits.std_pnl_gain_xmv = std_pnl_gain_xmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStdPnlCore0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 std_pnl_core_0mv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset));
    VPSS_TNR_MAME_STD_CORE.bits.std_pnl_core_0mv = std_pnl_core_0mv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStdPnlGain0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 std_pnl_gain_0mv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset));
    VPSS_TNR_MAME_STD_CORE.bits.std_pnl_gain_0mv = std_pnl_gain_0mv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStdCoreXmv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 std_core_xmv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset));
    VPSS_TNR_MAME_STD_CORE.bits.std_core_xmv = std_core_xmv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStdCore0mv(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 std_core_0mv)
{
    U_VPSS_TNR_MAME_STD_CORE VPSS_TNR_MAME_STD_CORE;

    VPSS_TNR_MAME_STD_CORE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset));
    VPSS_TNR_MAME_STD_CORE.bits.std_core_0mv = std_core_0mv;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_STD_CORE.u32) + u32AddrOffset), VPSS_TNR_MAME_STD_CORE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetStdPnlCore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 std_pnl_core)
{
    U_VPSS_TNR_MAME_STD_GAIN VPSS_TNR_MAME_STD_GAIN;

    VPSS_TNR_MAME_STD_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_STD_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAME_STD_GAIN.bits.std_pnl_core = std_pnl_core;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_STD_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAME_STD_GAIN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetStdPnlGain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 std_pnl_gain)
{
    U_VPSS_TNR_MAME_STD_GAIN VPSS_TNR_MAME_STD_GAIN;

    VPSS_TNR_MAME_STD_GAIN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_STD_GAIN.u32) + u32AddrOffset));
    VPSS_TNR_MAME_STD_GAIN.bits.std_pnl_gain = std_pnl_gain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_STD_GAIN.u32) + u32AddrOffset), VPSS_TNR_MAME_STD_GAIN.u32);

    return ;
}



HI_VOID VPSS_Sys_SetAdjXmvMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 adj_xmv_max)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset));
    VPSS_TNR_MAME_MV_THD.bits.adj_xmv_max = adj_xmv_max;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetAdj0mvMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 adj_0mv_max)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset));
    VPSS_TNR_MAME_MV_THD.bits.adj_0mv_max = adj_0mv_max;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetAdjXmvMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 adj_xmv_min)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset));
    VPSS_TNR_MAME_MV_THD.bits.adj_xmv_min = adj_xmv_min;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetAdj0mvMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 adj_0mv_min)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset));
    VPSS_TNR_MAME_MV_THD.bits.adj_0mv_min = adj_0mv_min;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetAdjMvMin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 adj_mv_min)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset));
    VPSS_TNR_MAME_MV_THD.bits.adj_mv_min = adj_mv_min;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetAdjMvMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 adj_mv_max)
{
    U_VPSS_TNR_MAME_MV_THD VPSS_TNR_MAME_MV_THD;

    VPSS_TNR_MAME_MV_THD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset));
    VPSS_TNR_MAME_MV_THD.bits.adj_mv_max = adj_mv_max;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAME_MV_THD.u32) + u32AddrOffset), VPSS_TNR_MAME_MV_THD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCbcrweight2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cbcrweight2)
{
    U_VPSS_TNR_MAMC_CBCR_UPEN VPSS_TNR_MAMC_CBCR_UPEN;

    VPSS_TNR_MAMC_CBCR_UPEN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPEN.bits.cbcrweight2 = cbcrweight2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPEN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbcrweight1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cbcrweight1)
{
    U_VPSS_TNR_MAMC_CBCR_UPEN VPSS_TNR_MAMC_CBCR_UPEN;

    VPSS_TNR_MAMC_CBCR_UPEN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPEN.bits.cbcrweight1 = cbcrweight1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPEN.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbcrupdateen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cbcrupdateen)
{
    U_VPSS_TNR_MAMC_CBCR_UPEN VPSS_TNR_MAMC_CBCR_UPEN;

    VPSS_TNR_MAMC_CBCR_UPEN.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPEN.bits.cbcrupdateen = cbcrupdateen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPEN.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPEN.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCrend1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 crend1)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD1 VPSS_TNR_MAMC_CBCR_UPTHD1;

    VPSS_TNR_MAMC_CBCR_UPTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPTHD1.bits.crend1 = crend1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbend1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cbend1)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD1 VPSS_TNR_MAMC_CBCR_UPTHD1;

    VPSS_TNR_MAMC_CBCR_UPTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPTHD1.bits.cbend1 = cbend1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCrbegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 crbegin1)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD1 VPSS_TNR_MAMC_CBCR_UPTHD1;

    VPSS_TNR_MAMC_CBCR_UPTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPTHD1.bits.crbegin1 = crbegin1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPTHD1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbbegin1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cbbegin1)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD1 VPSS_TNR_MAMC_CBCR_UPTHD1;

    VPSS_TNR_MAMC_CBCR_UPTHD1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPTHD1.bits.cbbegin1 = cbbegin1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD1.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPTHD1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCrend2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 crend2)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD2 VPSS_TNR_MAMC_CBCR_UPTHD2;

    VPSS_TNR_MAMC_CBCR_UPTHD2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPTHD2.bits.crend2 = crend2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPTHD2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbend2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cbend2)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD2 VPSS_TNR_MAMC_CBCR_UPTHD2;

    VPSS_TNR_MAMC_CBCR_UPTHD2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPTHD2.bits.cbend2 = cbend2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPTHD2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCrbegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 crbegin2)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD2 VPSS_TNR_MAMC_CBCR_UPTHD2;

    VPSS_TNR_MAMC_CBCR_UPTHD2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPTHD2.bits.crbegin2 = crbegin2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPTHD2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCbbegin2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cbbegin2)
{
    U_VPSS_TNR_MAMC_CBCR_UPTHD2 VPSS_TNR_MAMC_CBCR_UPTHD2;

    VPSS_TNR_MAMC_CBCR_UPTHD2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_CBCR_UPTHD2.bits.cbbegin2 = cbbegin2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_CBCR_UPTHD2.u32) + u32AddrOffset), VPSS_TNR_MAMC_CBCR_UPTHD2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMotionmergeratio(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motionmergeratio)
{
    U_VPSS_TNR_MAMC_PRE_MAD VPSS_TNR_MAMC_PRE_MAD;

    VPSS_TNR_MAMC_PRE_MAD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_PRE_MAD.bits.motionmergeratio = motionmergeratio;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32) + u32AddrOffset), VPSS_TNR_MAMC_PRE_MAD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetPremotionalpha(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 premotionalpha)
{
    U_VPSS_TNR_MAMC_PRE_MAD VPSS_TNR_MAMC_PRE_MAD;

    VPSS_TNR_MAMC_PRE_MAD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_PRE_MAD.bits.premotionalpha = premotionalpha;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32) + u32AddrOffset), VPSS_TNR_MAMC_PRE_MAD.u32);

    return ;
}


HI_VOID VPSS_Sys_SetPremotionmergemode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 premotionmergemode)
{
    U_VPSS_TNR_MAMC_PRE_MAD VPSS_TNR_MAMC_PRE_MAD;

    VPSS_TNR_MAMC_PRE_MAD.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_PRE_MAD.bits.premotionmergemode = premotionmergemode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_PRE_MAD.u32) + u32AddrOffset), VPSS_TNR_MAMC_PRE_MAD.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCmotioncore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmotioncore)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_MAP.bits.cmotioncore = cmotioncore;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset), VPSS_TNR_MAMC_MAP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCmotiongain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmotiongain)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_MAP.bits.cmotiongain = cmotiongain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset), VPSS_TNR_MAMC_MAP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYmotioncore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ymotioncore)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_MAP.bits.ymotioncore = ymotioncore;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset), VPSS_TNR_MAMC_MAP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYmotiongain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ymotiongain)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_MAP.bits.ymotiongain = ymotiongain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset), VPSS_TNR_MAMC_MAP.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMotionmappingen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 motionmappingen)
{
    U_VPSS_TNR_MAMC_MAP VPSS_TNR_MAMC_MAP;

    VPSS_TNR_MAMC_MAP.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_MAP.bits.motionmappingen = motionmappingen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_MAP.u32) + u32AddrOffset), VPSS_TNR_MAMC_MAP.u32);

    return ;
}



HI_VOID VPSS_Sys_SetSaltuslevel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 saltuslevel)
{
    U_VPSS_TNR_MAMC_SALTUS VPSS_TNR_MAMC_SALTUS;

    VPSS_TNR_MAMC_SALTUS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_SALTUS.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_SALTUS.bits.saltuslevel = saltuslevel;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_SALTUS.u32) + u32AddrOffset), VPSS_TNR_MAMC_SALTUS.u32);

    return ;
}


HI_VOID VPSS_Sys_SetSaltusdecten(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 saltusdecten)
{
    U_VPSS_TNR_MAMC_SALTUS VPSS_TNR_MAMC_SALTUS;

    VPSS_TNR_MAMC_SALTUS.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_SALTUS.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_SALTUS.bits.saltusdecten = saltusdecten;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_SALTUS.u32) + u32AddrOffset), VPSS_TNR_MAMC_SALTUS.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCmclpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmclpfmode)
{
    U_VPSS_TNR_MAMC_MCADJ VPSS_TNR_MAMC_MCADJ;

    VPSS_TNR_MAMC_MCADJ.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_MCADJ.bits.cmclpfmode = cmclpfmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32) + u32AddrOffset), VPSS_TNR_MAMC_MCADJ.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYmclpfmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ymclpfmode)
{
    U_VPSS_TNR_MAMC_MCADJ VPSS_TNR_MAMC_MCADJ;

    VPSS_TNR_MAMC_MCADJ.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_MCADJ.bits.ymclpfmode = ymclpfmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32) + u32AddrOffset), VPSS_TNR_MAMC_MCADJ.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCmcadjen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmcadjen)
{
    U_VPSS_TNR_MAMC_MCADJ VPSS_TNR_MAMC_MCADJ;

    VPSS_TNR_MAMC_MCADJ.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_MCADJ.bits.cmcadjen = cmcadjen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32) + u32AddrOffset), VPSS_TNR_MAMC_MCADJ.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYmcadjen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ymcadjen)
{
    U_VPSS_TNR_MAMC_MCADJ VPSS_TNR_MAMC_MCADJ;

    VPSS_TNR_MAMC_MCADJ.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32) + u32AddrOffset));
    VPSS_TNR_MAMC_MCADJ.bits.ymcadjen = ymcadjen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MAMC_MCADJ.u32) + u32AddrOffset), VPSS_TNR_MAMC_MCADJ.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCnonrrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cnonrrange)
{
    U_VPSS_TNR_FILR_MODE VPSS_TNR_FILR_MODE;

    VPSS_TNR_FILR_MODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_FILR_MODE.u32) + u32AddrOffset));
    VPSS_TNR_FILR_MODE.bits.cnonrrange = cnonrrange;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_FILR_MODE.u32) + u32AddrOffset), VPSS_TNR_FILR_MODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYnonrrange(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ynonrrange)
{
    U_VPSS_TNR_FILR_MODE VPSS_TNR_FILR_MODE;

    VPSS_TNR_FILR_MODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_FILR_MODE.u32) + u32AddrOffset));
    VPSS_TNR_FILR_MODE.bits.ynonrrange = ynonrrange;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_FILR_MODE.u32) + u32AddrOffset), VPSS_TNR_FILR_MODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCmotionmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cmotionmode)
{
    U_VPSS_TNR_FILR_MODE VPSS_TNR_FILR_MODE;

    VPSS_TNR_FILR_MODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_FILR_MODE.u32) + u32AddrOffset));
    VPSS_TNR_FILR_MODE.bits.cmotionmode = cmotionmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_FILR_MODE.u32) + u32AddrOffset), VPSS_TNR_FILR_MODE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYmotionmode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ymotionmode)
{
    U_VPSS_TNR_FILR_MODE VPSS_TNR_FILR_MODE;

    VPSS_TNR_FILR_MODE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_FILR_MODE.u32) + u32AddrOffset));
    VPSS_TNR_FILR_MODE.bits.ymotionmode = ymotionmode;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_FILR_MODE.u32) + u32AddrOffset), VPSS_TNR_FILR_MODE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetScenechangeinfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechangeinfo)
{
    U_VPSS_TNR_SCENE_CHANGE VPSS_TNR_SCENE_CHANGE;

    VPSS_TNR_SCENE_CHANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_SCENE_CHANGE.u32) + u32AddrOffset));
    VPSS_TNR_SCENE_CHANGE.bits.scenechangeinfo = scenechangeinfo;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_SCENE_CHANGE.u32) + u32AddrOffset), VPSS_TNR_SCENE_CHANGE.u32);

    return ;
}


HI_VOID VPSS_Sys_SetScenechangeen(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scenechangeen)
{
    U_VPSS_TNR_SCENE_CHANGE VPSS_TNR_SCENE_CHANGE;

    VPSS_TNR_SCENE_CHANGE.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_SCENE_CHANGE.u32) + u32AddrOffset));
    VPSS_TNR_SCENE_CHANGE.bits.scenechangeen = scenechangeen;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_SCENE_CHANGE.u32) + u32AddrOffset), VPSS_TNR_SCENE_CHANGE.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCfgCmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cfg_cmdcore)
{
    U_VPSS_TNR_CFG VPSS_TNR_CFG;

    VPSS_TNR_CFG.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CFG.u32) + u32AddrOffset));
    VPSS_TNR_CFG.bits.cfg_cmdcore = cfg_cmdcore;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CFG.u32) + u32AddrOffset), VPSS_TNR_CFG.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCfgCmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cfg_cmdgain)
{
    U_VPSS_TNR_CFG VPSS_TNR_CFG;

    VPSS_TNR_CFG.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CFG.u32) + u32AddrOffset));
    VPSS_TNR_CFG.bits.cfg_cmdgain = cfg_cmdgain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CFG.u32) + u32AddrOffset), VPSS_TNR_CFG.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCfgYmdcore(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cfg_ymdcore)
{
    U_VPSS_TNR_CFG VPSS_TNR_CFG;

    VPSS_TNR_CFG.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CFG.u32) + u32AddrOffset));
    VPSS_TNR_CFG.bits.cfg_ymdcore = cfg_ymdcore;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CFG.u32) + u32AddrOffset), VPSS_TNR_CFG.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCfgYmdgain(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cfg_ymdgain)
{
    U_VPSS_TNR_CFG VPSS_TNR_CFG;

    VPSS_TNR_CFG.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CFG.u32) + u32AddrOffset));
    VPSS_TNR_CFG.bits.cfg_ymdgain = cfg_ymdgain;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CFG.u32) + u32AddrOffset), VPSS_TNR_CFG.u32);

    return ;
}



HI_VOID VPSS_Sys_SetFlatinfoymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 flatinfoymax)
{
    U_VPSS_TNR_FLAT_INFO VPSS_TNR_FLAT_INFO;

    VPSS_TNR_FLAT_INFO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_FLAT_INFO.u32) + u32AddrOffset));
    VPSS_TNR_FLAT_INFO.bits.flatinfoymax = flatinfoymax;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_FLAT_INFO.u32) + u32AddrOffset), VPSS_TNR_FLAT_INFO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFlatinfoxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 flatinfoxmax)
{
    U_VPSS_TNR_FLAT_INFO VPSS_TNR_FLAT_INFO;

    VPSS_TNR_FLAT_INFO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_FLAT_INFO.u32) + u32AddrOffset));
    VPSS_TNR_FLAT_INFO.bits.flatinfoxmax = flatinfoxmax;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_FLAT_INFO.u32) + u32AddrOffset), VPSS_TNR_FLAT_INFO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFlatinfoymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 flatinfoymin)
{
    U_VPSS_TNR_FLAT_INFO VPSS_TNR_FLAT_INFO;

    VPSS_TNR_FLAT_INFO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_FLAT_INFO.u32) + u32AddrOffset));
    VPSS_TNR_FLAT_INFO.bits.flatinfoymin = flatinfoymin;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_FLAT_INFO.u32) + u32AddrOffset), VPSS_TNR_FLAT_INFO.u32);

    return ;
}


HI_VOID VPSS_Sys_SetFlatinfoxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 flatinfoxmin)
{
    U_VPSS_TNR_FLAT_INFO VPSS_TNR_FLAT_INFO;

    VPSS_TNR_FLAT_INFO.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_FLAT_INFO.u32) + u32AddrOffset));
    VPSS_TNR_FLAT_INFO.bits.flatinfoxmin = flatinfoxmin;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_FLAT_INFO.u32) + u32AddrOffset), VPSS_TNR_FLAT_INFO.u32);

    return ;
}



HI_VOID VPSS_Sys_SetYblendingymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingymax)
{
    U_VPSS_TNR_YBLEND VPSS_TNR_YBLEND;

    VPSS_TNR_YBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLEND.u32) + u32AddrOffset));
    VPSS_TNR_YBLEND.bits.yblendingymax = yblendingymax;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLEND.u32) + u32AddrOffset), VPSS_TNR_YBLEND.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingxmax)
{
    U_VPSS_TNR_YBLEND VPSS_TNR_YBLEND;

    VPSS_TNR_YBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLEND.u32) + u32AddrOffset));
    VPSS_TNR_YBLEND.bits.yblendingxmax = yblendingxmax;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLEND.u32) + u32AddrOffset), VPSS_TNR_YBLEND.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingymin)
{
    U_VPSS_TNR_YBLEND VPSS_TNR_YBLEND;

    VPSS_TNR_YBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLEND.u32) + u32AddrOffset));
    VPSS_TNR_YBLEND.bits.yblendingymin = yblendingymin;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLEND.u32) + u32AddrOffset), VPSS_TNR_YBLEND.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingxmin)
{
    U_VPSS_TNR_YBLEND VPSS_TNR_YBLEND;

    VPSS_TNR_YBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLEND.u32) + u32AddrOffset));
    VPSS_TNR_YBLEND.bits.yblendingxmin = yblendingxmin;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLEND.u32) + u32AddrOffset), VPSS_TNR_YBLEND.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCblendingymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingymax)
{
    U_VPSS_TNR_CBLEND VPSS_TNR_CBLEND;

    VPSS_TNR_CBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLEND.u32) + u32AddrOffset));
    VPSS_TNR_CBLEND.bits.cblendingymax = cblendingymax;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLEND.u32) + u32AddrOffset), VPSS_TNR_CBLEND.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingxmax)
{
    U_VPSS_TNR_CBLEND VPSS_TNR_CBLEND;

    VPSS_TNR_CBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLEND.u32) + u32AddrOffset));
    VPSS_TNR_CBLEND.bits.cblendingxmax = cblendingxmax;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLEND.u32) + u32AddrOffset), VPSS_TNR_CBLEND.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingymin)
{
    U_VPSS_TNR_CBLEND VPSS_TNR_CBLEND;

    VPSS_TNR_CBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLEND.u32) + u32AddrOffset));
    VPSS_TNR_CBLEND.bits.cblendingymin = cblendingymin;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLEND.u32) + u32AddrOffset), VPSS_TNR_CBLEND.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingxmin)
{
    U_VPSS_TNR_CBLEND VPSS_TNR_CBLEND;

    VPSS_TNR_CBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLEND.u32) + u32AddrOffset));
    VPSS_TNR_CBLEND.bits.cblendingxmin = cblendingxmin;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLEND.u32) + u32AddrOffset), VPSS_TNR_CBLEND.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDtblendingymax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dtblendingymax)
{
    U_VPSS_TNR_DTBLEND VPSS_TNR_DTBLEND;

    VPSS_TNR_DTBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_DTBLEND.u32) + u32AddrOffset));
    VPSS_TNR_DTBLEND.bits.dtblendingymax = dtblendingymax;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_DTBLEND.u32) + u32AddrOffset), VPSS_TNR_DTBLEND.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDtblendingxmax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dtblendingxmax)
{
    U_VPSS_TNR_DTBLEND VPSS_TNR_DTBLEND;

    VPSS_TNR_DTBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_DTBLEND.u32) + u32AddrOffset));
    VPSS_TNR_DTBLEND.bits.dtblendingxmax = dtblendingxmax;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_DTBLEND.u32) + u32AddrOffset), VPSS_TNR_DTBLEND.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDtblendingymin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dtblendingymin)
{
    U_VPSS_TNR_DTBLEND VPSS_TNR_DTBLEND;

    VPSS_TNR_DTBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_DTBLEND.u32) + u32AddrOffset));
    VPSS_TNR_DTBLEND.bits.dtblendingymin = dtblendingymin;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_DTBLEND.u32) + u32AddrOffset), VPSS_TNR_DTBLEND.u32);

    return ;
}


HI_VOID VPSS_Sys_SetDtblendingxmin(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dtblendingxmin)
{
    U_VPSS_TNR_DTBLEND VPSS_TNR_DTBLEND;

    VPSS_TNR_DTBLEND.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_DTBLEND.u32) + u32AddrOffset));
    VPSS_TNR_DTBLEND.bits.dtblendingxmin = dtblendingxmin;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_DTBLEND.u32) + u32AddrOffset), VPSS_TNR_DTBLEND.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMeanMotionRatio3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio3)
{
    U_VPSS_TNR_MEAN_MOTION_LUT0 VPSS_TNR_MEAN_MOTION_LUT0;

    VPSS_TNR_MEAN_MOTION_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT0.bits.mean_motion_ratio3 = mean_motion_ratio3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio2)
{
    U_VPSS_TNR_MEAN_MOTION_LUT0 VPSS_TNR_MEAN_MOTION_LUT0;

    VPSS_TNR_MEAN_MOTION_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT0.bits.mean_motion_ratio2 = mean_motion_ratio2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio1)
{
    U_VPSS_TNR_MEAN_MOTION_LUT0 VPSS_TNR_MEAN_MOTION_LUT0;

    VPSS_TNR_MEAN_MOTION_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT0.bits.mean_motion_ratio1 = mean_motion_ratio1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio0)
{
    U_VPSS_TNR_MEAN_MOTION_LUT0 VPSS_TNR_MEAN_MOTION_LUT0;

    VPSS_TNR_MEAN_MOTION_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT0.bits.mean_motion_ratio0 = mean_motion_ratio0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT0.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMeanMotionRatio7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio7)
{
    U_VPSS_TNR_MEAN_MOTION_LUT1 VPSS_TNR_MEAN_MOTION_LUT1;

    VPSS_TNR_MEAN_MOTION_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT1.bits.mean_motion_ratio7 = mean_motion_ratio7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio6)
{
    U_VPSS_TNR_MEAN_MOTION_LUT1 VPSS_TNR_MEAN_MOTION_LUT1;

    VPSS_TNR_MEAN_MOTION_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT1.bits.mean_motion_ratio6 = mean_motion_ratio6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio5)
{
    U_VPSS_TNR_MEAN_MOTION_LUT1 VPSS_TNR_MEAN_MOTION_LUT1;

    VPSS_TNR_MEAN_MOTION_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT1.bits.mean_motion_ratio5 = mean_motion_ratio5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio4)
{
    U_VPSS_TNR_MEAN_MOTION_LUT1 VPSS_TNR_MEAN_MOTION_LUT1;

    VPSS_TNR_MEAN_MOTION_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT1.bits.mean_motion_ratio4 = mean_motion_ratio4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT1.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMeanMotionRatio11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio11)
{
    U_VPSS_TNR_MEAN_MOTION_LUT2 VPSS_TNR_MEAN_MOTION_LUT2;

    VPSS_TNR_MEAN_MOTION_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT2.bits.mean_motion_ratio11 = mean_motion_ratio11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio10)
{
    U_VPSS_TNR_MEAN_MOTION_LUT2 VPSS_TNR_MEAN_MOTION_LUT2;

    VPSS_TNR_MEAN_MOTION_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT2.bits.mean_motion_ratio10 = mean_motion_ratio10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio9)
{
    U_VPSS_TNR_MEAN_MOTION_LUT2 VPSS_TNR_MEAN_MOTION_LUT2;

    VPSS_TNR_MEAN_MOTION_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT2.bits.mean_motion_ratio9 = mean_motion_ratio9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio8)
{
    U_VPSS_TNR_MEAN_MOTION_LUT2 VPSS_TNR_MEAN_MOTION_LUT2;

    VPSS_TNR_MEAN_MOTION_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT2.bits.mean_motion_ratio8 = mean_motion_ratio8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT2.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetMeanMotionRatio15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio15)
{
    U_VPSS_TNR_MEAN_MOTION_LUT3 VPSS_TNR_MEAN_MOTION_LUT3;

    VPSS_TNR_MEAN_MOTION_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT3.bits.mean_motion_ratio15 = mean_motion_ratio15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio14)
{
    U_VPSS_TNR_MEAN_MOTION_LUT3 VPSS_TNR_MEAN_MOTION_LUT3;

    VPSS_TNR_MEAN_MOTION_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT3.bits.mean_motion_ratio14 = mean_motion_ratio14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio13)
{
    U_VPSS_TNR_MEAN_MOTION_LUT3 VPSS_TNR_MEAN_MOTION_LUT3;

    VPSS_TNR_MEAN_MOTION_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT3.bits.mean_motion_ratio13 = mean_motion_ratio13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetMeanMotionRatio12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mean_motion_ratio12)
{
    U_VPSS_TNR_MEAN_MOTION_LUT3 VPSS_TNR_MEAN_MOTION_LUT3;

    VPSS_TNR_MEAN_MOTION_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_MEAN_MOTION_LUT3.bits.mean_motion_ratio12 = mean_motion_ratio12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_MEAN_MOTION_LUT3.u32) + u32AddrOffset), VPSS_TNR_MEAN_MOTION_LUT3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetYblendingalphalut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut3)
{
    U_VPSS_TNR_YBLENDING_LUT0 VPSS_TNR_YBLENDING_LUT0;

    VPSS_TNR_YBLENDING_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut3 = yblendingalphalut3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut2)
{
    U_VPSS_TNR_YBLENDING_LUT0 VPSS_TNR_YBLENDING_LUT0;

    VPSS_TNR_YBLENDING_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut2 = yblendingalphalut2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut1)
{
    U_VPSS_TNR_YBLENDING_LUT0 VPSS_TNR_YBLENDING_LUT0;

    VPSS_TNR_YBLENDING_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut1 = yblendingalphalut1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut0)
{
    U_VPSS_TNR_YBLENDING_LUT0 VPSS_TNR_YBLENDING_LUT0;

    VPSS_TNR_YBLENDING_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT0.bits.yblendingalphalut0 = yblendingalphalut0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT0.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetYblendingalphalut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut7)
{
    U_VPSS_TNR_YBLENDING_LUT1 VPSS_TNR_YBLENDING_LUT1;

    VPSS_TNR_YBLENDING_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut7 = yblendingalphalut7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut6)
{
    U_VPSS_TNR_YBLENDING_LUT1 VPSS_TNR_YBLENDING_LUT1;

    VPSS_TNR_YBLENDING_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut6 = yblendingalphalut6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut5)
{
    U_VPSS_TNR_YBLENDING_LUT1 VPSS_TNR_YBLENDING_LUT1;

    VPSS_TNR_YBLENDING_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut5 = yblendingalphalut5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut4)
{
    U_VPSS_TNR_YBLENDING_LUT1 VPSS_TNR_YBLENDING_LUT1;

    VPSS_TNR_YBLENDING_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT1.bits.yblendingalphalut4 = yblendingalphalut4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT1.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetYblendingalphalut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut11)
{
    U_VPSS_TNR_YBLENDING_LUT2 VPSS_TNR_YBLENDING_LUT2;

    VPSS_TNR_YBLENDING_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut11 = yblendingalphalut11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut10)
{
    U_VPSS_TNR_YBLENDING_LUT2 VPSS_TNR_YBLENDING_LUT2;

    VPSS_TNR_YBLENDING_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut10 = yblendingalphalut10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut9)
{
    U_VPSS_TNR_YBLENDING_LUT2 VPSS_TNR_YBLENDING_LUT2;

    VPSS_TNR_YBLENDING_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut9 = yblendingalphalut9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut8)
{
    U_VPSS_TNR_YBLENDING_LUT2 VPSS_TNR_YBLENDING_LUT2;

    VPSS_TNR_YBLENDING_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT2.bits.yblendingalphalut8 = yblendingalphalut8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT2.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetYblendingalphalut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut15)
{
    U_VPSS_TNR_YBLENDING_LUT3 VPSS_TNR_YBLENDING_LUT3;

    VPSS_TNR_YBLENDING_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut15 = yblendingalphalut15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut14)
{
    U_VPSS_TNR_YBLENDING_LUT3 VPSS_TNR_YBLENDING_LUT3;

    VPSS_TNR_YBLENDING_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut14 = yblendingalphalut14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut13)
{
    U_VPSS_TNR_YBLENDING_LUT3 VPSS_TNR_YBLENDING_LUT3;

    VPSS_TNR_YBLENDING_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut13 = yblendingalphalut13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut12)
{
    U_VPSS_TNR_YBLENDING_LUT3 VPSS_TNR_YBLENDING_LUT3;

    VPSS_TNR_YBLENDING_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT3.bits.yblendingalphalut12 = yblendingalphalut12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT3.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetYblendingalphalut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut19)
{
    U_VPSS_TNR_YBLENDING_LUT4 VPSS_TNR_YBLENDING_LUT4;

    VPSS_TNR_YBLENDING_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut19 = yblendingalphalut19;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut18)
{
    U_VPSS_TNR_YBLENDING_LUT4 VPSS_TNR_YBLENDING_LUT4;

    VPSS_TNR_YBLENDING_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut18 = yblendingalphalut18;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut17)
{
    U_VPSS_TNR_YBLENDING_LUT4 VPSS_TNR_YBLENDING_LUT4;

    VPSS_TNR_YBLENDING_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut17 = yblendingalphalut17;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut16)
{
    U_VPSS_TNR_YBLENDING_LUT4 VPSS_TNR_YBLENDING_LUT4;

    VPSS_TNR_YBLENDING_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT4.bits.yblendingalphalut16 = yblendingalphalut16;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT4.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetYblendingalphalut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut23)
{
    U_VPSS_TNR_YBLENDING_LUT5 VPSS_TNR_YBLENDING_LUT5;

    VPSS_TNR_YBLENDING_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut23 = yblendingalphalut23;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut22)
{
    U_VPSS_TNR_YBLENDING_LUT5 VPSS_TNR_YBLENDING_LUT5;

    VPSS_TNR_YBLENDING_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut22 = yblendingalphalut22;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut21)
{
    U_VPSS_TNR_YBLENDING_LUT5 VPSS_TNR_YBLENDING_LUT5;

    VPSS_TNR_YBLENDING_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut21 = yblendingalphalut21;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut20)
{
    U_VPSS_TNR_YBLENDING_LUT5 VPSS_TNR_YBLENDING_LUT5;

    VPSS_TNR_YBLENDING_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT5.bits.yblendingalphalut20 = yblendingalphalut20;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT5.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetYblendingalphalut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut27)
{
    U_VPSS_TNR_YBLENDING_LUT6 VPSS_TNR_YBLENDING_LUT6;

    VPSS_TNR_YBLENDING_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut27 = yblendingalphalut27;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut26)
{
    U_VPSS_TNR_YBLENDING_LUT6 VPSS_TNR_YBLENDING_LUT6;

    VPSS_TNR_YBLENDING_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut26 = yblendingalphalut26;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut25)
{
    U_VPSS_TNR_YBLENDING_LUT6 VPSS_TNR_YBLENDING_LUT6;

    VPSS_TNR_YBLENDING_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut25 = yblendingalphalut25;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut24)
{
    U_VPSS_TNR_YBLENDING_LUT6 VPSS_TNR_YBLENDING_LUT6;

    VPSS_TNR_YBLENDING_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT6.bits.yblendingalphalut24 = yblendingalphalut24;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT6.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT6.u32);

    return ;
}



HI_VOID VPSS_Sys_SetYblendingalphalut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut31)
{
    U_VPSS_TNR_YBLENDING_LUT7 VPSS_TNR_YBLENDING_LUT7;

    VPSS_TNR_YBLENDING_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut31 = yblendingalphalut31;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut30)
{
    U_VPSS_TNR_YBLENDING_LUT7 VPSS_TNR_YBLENDING_LUT7;

    VPSS_TNR_YBLENDING_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut30 = yblendingalphalut30;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut29)
{
    U_VPSS_TNR_YBLENDING_LUT7 VPSS_TNR_YBLENDING_LUT7;

    VPSS_TNR_YBLENDING_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut29 = yblendingalphalut29;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetYblendingalphalut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 yblendingalphalut28)
{
    U_VPSS_TNR_YBLENDING_LUT7 VPSS_TNR_YBLENDING_LUT7;

    VPSS_TNR_YBLENDING_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32) + u32AddrOffset));
    VPSS_TNR_YBLENDING_LUT7.bits.yblendingalphalut28 = yblendingalphalut28;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_YBLENDING_LUT7.u32) + u32AddrOffset), VPSS_TNR_YBLENDING_LUT7.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCblendingalphalut3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut3)
{
    U_VPSS_TNR_CBLENDING_LUT0 VPSS_TNR_CBLENDING_LUT0;

    VPSS_TNR_CBLENDING_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut3 = cblendingalphalut3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut2)
{
    U_VPSS_TNR_CBLENDING_LUT0 VPSS_TNR_CBLENDING_LUT0;

    VPSS_TNR_CBLENDING_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut2 = cblendingalphalut2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut1)
{
    U_VPSS_TNR_CBLENDING_LUT0 VPSS_TNR_CBLENDING_LUT0;

    VPSS_TNR_CBLENDING_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut1 = cblendingalphalut1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT0.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut0)
{
    U_VPSS_TNR_CBLENDING_LUT0 VPSS_TNR_CBLENDING_LUT0;

    VPSS_TNR_CBLENDING_LUT0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT0.bits.cblendingalphalut0 = cblendingalphalut0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT0.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCblendingalphalut7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut7)
{
    U_VPSS_TNR_CBLENDING_LUT1 VPSS_TNR_CBLENDING_LUT1;

    VPSS_TNR_CBLENDING_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut7 = cblendingalphalut7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut6)
{
    U_VPSS_TNR_CBLENDING_LUT1 VPSS_TNR_CBLENDING_LUT1;

    VPSS_TNR_CBLENDING_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut6 = cblendingalphalut6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut5)
{
    U_VPSS_TNR_CBLENDING_LUT1 VPSS_TNR_CBLENDING_LUT1;

    VPSS_TNR_CBLENDING_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut5 = cblendingalphalut5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT1.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut4)
{
    U_VPSS_TNR_CBLENDING_LUT1 VPSS_TNR_CBLENDING_LUT1;

    VPSS_TNR_CBLENDING_LUT1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT1.bits.cblendingalphalut4 = cblendingalphalut4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT1.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCblendingalphalut11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut11)
{
    U_VPSS_TNR_CBLENDING_LUT2 VPSS_TNR_CBLENDING_LUT2;

    VPSS_TNR_CBLENDING_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut11 = cblendingalphalut11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut10)
{
    U_VPSS_TNR_CBLENDING_LUT2 VPSS_TNR_CBLENDING_LUT2;

    VPSS_TNR_CBLENDING_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut10 = cblendingalphalut10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut9)
{
    U_VPSS_TNR_CBLENDING_LUT2 VPSS_TNR_CBLENDING_LUT2;

    VPSS_TNR_CBLENDING_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut9 = cblendingalphalut9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT2.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut8)
{
    U_VPSS_TNR_CBLENDING_LUT2 VPSS_TNR_CBLENDING_LUT2;

    VPSS_TNR_CBLENDING_LUT2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT2.bits.cblendingalphalut8 = cblendingalphalut8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT2.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCblendingalphalut15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut15)
{
    U_VPSS_TNR_CBLENDING_LUT3 VPSS_TNR_CBLENDING_LUT3;

    VPSS_TNR_CBLENDING_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut15 = cblendingalphalut15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut14)
{
    U_VPSS_TNR_CBLENDING_LUT3 VPSS_TNR_CBLENDING_LUT3;

    VPSS_TNR_CBLENDING_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut14 = cblendingalphalut14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut13)
{
    U_VPSS_TNR_CBLENDING_LUT3 VPSS_TNR_CBLENDING_LUT3;

    VPSS_TNR_CBLENDING_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut13 = cblendingalphalut13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT3.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut12)
{
    U_VPSS_TNR_CBLENDING_LUT3 VPSS_TNR_CBLENDING_LUT3;

    VPSS_TNR_CBLENDING_LUT3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT3.bits.cblendingalphalut12 = cblendingalphalut12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT3.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCblendingalphalut19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut19)
{
    U_VPSS_TNR_CBLENDING_LUT4 VPSS_TNR_CBLENDING_LUT4;

    VPSS_TNR_CBLENDING_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut19 = cblendingalphalut19;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut18)
{
    U_VPSS_TNR_CBLENDING_LUT4 VPSS_TNR_CBLENDING_LUT4;

    VPSS_TNR_CBLENDING_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut18 = cblendingalphalut18;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut17)
{
    U_VPSS_TNR_CBLENDING_LUT4 VPSS_TNR_CBLENDING_LUT4;

    VPSS_TNR_CBLENDING_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut17 = cblendingalphalut17;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT4.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut16)
{
    U_VPSS_TNR_CBLENDING_LUT4 VPSS_TNR_CBLENDING_LUT4;

    VPSS_TNR_CBLENDING_LUT4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT4.bits.cblendingalphalut16 = cblendingalphalut16;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT4.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCblendingalphalut23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut23)
{
    U_VPSS_TNR_CBLENDING_LUT5 VPSS_TNR_CBLENDING_LUT5;

    VPSS_TNR_CBLENDING_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut23 = cblendingalphalut23;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut22)
{
    U_VPSS_TNR_CBLENDING_LUT5 VPSS_TNR_CBLENDING_LUT5;

    VPSS_TNR_CBLENDING_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut22 = cblendingalphalut22;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut21)
{
    U_VPSS_TNR_CBLENDING_LUT5 VPSS_TNR_CBLENDING_LUT5;

    VPSS_TNR_CBLENDING_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut21 = cblendingalphalut21;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT5.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut20)
{
    U_VPSS_TNR_CBLENDING_LUT5 VPSS_TNR_CBLENDING_LUT5;

    VPSS_TNR_CBLENDING_LUT5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT5.bits.cblendingalphalut20 = cblendingalphalut20;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT5.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCblendingalphalut27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut27)
{
    U_VPSS_TNR_CBLENDING_LUT6 VPSS_TNR_CBLENDING_LUT6;

    VPSS_TNR_CBLENDING_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut27 = cblendingalphalut27;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut26)
{
    U_VPSS_TNR_CBLENDING_LUT6 VPSS_TNR_CBLENDING_LUT6;

    VPSS_TNR_CBLENDING_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut26 = cblendingalphalut26;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut25)
{
    U_VPSS_TNR_CBLENDING_LUT6 VPSS_TNR_CBLENDING_LUT6;

    VPSS_TNR_CBLENDING_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut25 = cblendingalphalut25;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT6.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut24)
{
    U_VPSS_TNR_CBLENDING_LUT6 VPSS_TNR_CBLENDING_LUT6;

    VPSS_TNR_CBLENDING_LUT6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT6.bits.cblendingalphalut24 = cblendingalphalut24;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT6.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT6.u32);

    return ;
}



HI_VOID VPSS_Sys_SetCblendingalphalut31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut31)
{
    U_VPSS_TNR_CBLENDING_LUT7 VPSS_TNR_CBLENDING_LUT7;

    VPSS_TNR_CBLENDING_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut31 = cblendingalphalut31;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut30)
{
    U_VPSS_TNR_CBLENDING_LUT7 VPSS_TNR_CBLENDING_LUT7;

    VPSS_TNR_CBLENDING_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut30 = cblendingalphalut30;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut29)
{
    U_VPSS_TNR_CBLENDING_LUT7 VPSS_TNR_CBLENDING_LUT7;

    VPSS_TNR_CBLENDING_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut29 = cblendingalphalut29;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT7.u32);

    return ;
}


HI_VOID VPSS_Sys_SetCblendingalphalut28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cblendingalphalut28)
{
    U_VPSS_TNR_CBLENDING_LUT7 VPSS_TNR_CBLENDING_LUT7;

    VPSS_TNR_CBLENDING_LUT7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32) + u32AddrOffset));
    VPSS_TNR_CBLENDING_LUT7.bits.cblendingalphalut28 = cblendingalphalut28;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_TNR_CBLENDING_LUT7.u32) + u32AddrOffset), VPSS_TNR_CBLENDING_LUT7.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug0)
{
    U_VPSS_DEBUG0 VPSS_DEBUG0;

    VPSS_DEBUG0.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG0.u32) + u32AddrOffset));
    VPSS_DEBUG0.bits.debug0 = debug0;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG0.u32) + u32AddrOffset), VPSS_DEBUG0.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug1)
{
    U_VPSS_DEBUG1 VPSS_DEBUG1;

    VPSS_DEBUG1.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG1.u32) + u32AddrOffset));
    VPSS_DEBUG1.bits.debug1 = debug1;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG1.u32) + u32AddrOffset), VPSS_DEBUG1.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug2)
{
    U_VPSS_DEBUG2 VPSS_DEBUG2;

    VPSS_DEBUG2.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG2.u32) + u32AddrOffset));
    VPSS_DEBUG2.bits.debug2 = debug2;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG2.u32) + u32AddrOffset), VPSS_DEBUG2.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug3)
{
    U_VPSS_DEBUG3 VPSS_DEBUG3;

    VPSS_DEBUG3.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG3.u32) + u32AddrOffset));
    VPSS_DEBUG3.bits.debug3 = debug3;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG3.u32) + u32AddrOffset), VPSS_DEBUG3.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug4)
{
    U_VPSS_DEBUG4 VPSS_DEBUG4;

    VPSS_DEBUG4.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG4.u32) + u32AddrOffset));
    VPSS_DEBUG4.bits.debug4 = debug4;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG4.u32) + u32AddrOffset), VPSS_DEBUG4.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug5)
{
    U_VPSS_DEBUG5 VPSS_DEBUG5;

    VPSS_DEBUG5.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG5.u32) + u32AddrOffset));
    VPSS_DEBUG5.bits.debug5 = debug5;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG5.u32) + u32AddrOffset), VPSS_DEBUG5.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug6)
{
    U_VPSS_DEBUG6 VPSS_DEBUG6;

    VPSS_DEBUG6.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG6.u32) + u32AddrOffset));
    VPSS_DEBUG6.bits.debug6 = debug6;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG6.u32) + u32AddrOffset), VPSS_DEBUG6.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug7)
{
    U_VPSS_DEBUG7 VPSS_DEBUG7;

    VPSS_DEBUG7.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG7.u32) + u32AddrOffset));
    VPSS_DEBUG7.bits.debug7 = debug7;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG7.u32) + u32AddrOffset), VPSS_DEBUG7.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug8(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug8)
{
    U_VPSS_DEBUG8 VPSS_DEBUG8;

    VPSS_DEBUG8.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG8.u32) + u32AddrOffset));
    VPSS_DEBUG8.bits.debug8 = debug8;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG8.u32) + u32AddrOffset), VPSS_DEBUG8.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug9(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug9)
{
    U_VPSS_DEBUG9 VPSS_DEBUG9;

    VPSS_DEBUG9.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG9.u32) + u32AddrOffset));
    VPSS_DEBUG9.bits.debug9 = debug9;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG9.u32) + u32AddrOffset), VPSS_DEBUG9.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug10(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug10)
{
    U_VPSS_DEBUG10 VPSS_DEBUG10;

    VPSS_DEBUG10.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG10.u32) + u32AddrOffset));
    VPSS_DEBUG10.bits.debug10 = debug10;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG10.u32) + u32AddrOffset), VPSS_DEBUG10.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug11(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug11)
{
    U_VPSS_DEBUG11 VPSS_DEBUG11;

    VPSS_DEBUG11.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG11.u32) + u32AddrOffset));
    VPSS_DEBUG11.bits.debug11 = debug11;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG11.u32) + u32AddrOffset), VPSS_DEBUG11.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug12(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug12)
{
    U_VPSS_DEBUG12 VPSS_DEBUG12;

    VPSS_DEBUG12.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG12.u32) + u32AddrOffset));
    VPSS_DEBUG12.bits.debug12 = debug12;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG12.u32) + u32AddrOffset), VPSS_DEBUG12.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug13(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug13)
{
    U_VPSS_DEBUG13 VPSS_DEBUG13;

    VPSS_DEBUG13.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG13.u32) + u32AddrOffset));
    VPSS_DEBUG13.bits.debug13 = debug13;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG13.u32) + u32AddrOffset), VPSS_DEBUG13.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug14(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug14)
{
    U_VPSS_DEBUG14 VPSS_DEBUG14;

    VPSS_DEBUG14.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG14.u32) + u32AddrOffset));
    VPSS_DEBUG14.bits.debug14 = debug14;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG14.u32) + u32AddrOffset), VPSS_DEBUG14.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug15(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug15)
{
    U_VPSS_DEBUG15 VPSS_DEBUG15;

    VPSS_DEBUG15.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG15.u32) + u32AddrOffset));
    VPSS_DEBUG15.bits.debug15 = debug15;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG15.u32) + u32AddrOffset), VPSS_DEBUG15.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug16(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug16)
{
    U_VPSS_DEBUG16 VPSS_DEBUG16;

    VPSS_DEBUG16.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG16.u32) + u32AddrOffset));
    VPSS_DEBUG16.bits.debug16 = debug16;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG16.u32) + u32AddrOffset), VPSS_DEBUG16.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug17(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug17)
{
    U_VPSS_DEBUG17 VPSS_DEBUG17;

    VPSS_DEBUG17.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG17.u32) + u32AddrOffset));
    VPSS_DEBUG17.bits.debug17 = debug17;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG17.u32) + u32AddrOffset), VPSS_DEBUG17.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug18(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug18)
{
    U_VPSS_DEBUG18 VPSS_DEBUG18;

    VPSS_DEBUG18.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG18.u32) + u32AddrOffset));
    VPSS_DEBUG18.bits.debug18 = debug18;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG18.u32) + u32AddrOffset), VPSS_DEBUG18.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug19(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug19)
{
    U_VPSS_DEBUG19 VPSS_DEBUG19;

    VPSS_DEBUG19.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG19.u32) + u32AddrOffset));
    VPSS_DEBUG19.bits.debug19 = debug19;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG19.u32) + u32AddrOffset), VPSS_DEBUG19.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug20(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug20)
{
    U_VPSS_DEBUG20 VPSS_DEBUG20;

    VPSS_DEBUG20.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG20.u32) + u32AddrOffset));
    VPSS_DEBUG20.bits.debug20 = debug20;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG20.u32) + u32AddrOffset), VPSS_DEBUG20.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug21(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug21)
{
    U_VPSS_DEBUG21 VPSS_DEBUG21;

    VPSS_DEBUG21.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG21.u32) + u32AddrOffset));
    VPSS_DEBUG21.bits.debug21 = debug21;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG21.u32) + u32AddrOffset), VPSS_DEBUG21.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug22(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug22)
{
    U_VPSS_DEBUG22 VPSS_DEBUG22;

    VPSS_DEBUG22.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG22.u32) + u32AddrOffset));
    VPSS_DEBUG22.bits.debug22 = debug22;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG22.u32) + u32AddrOffset), VPSS_DEBUG22.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug23(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug23)
{
    U_VPSS_DEBUG23 VPSS_DEBUG23;

    VPSS_DEBUG23.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG23.u32) + u32AddrOffset));
    VPSS_DEBUG23.bits.debug23 = debug23;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG23.u32) + u32AddrOffset), VPSS_DEBUG23.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug24(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug24)
{
    U_VPSS_DEBUG24 VPSS_DEBUG24;

    VPSS_DEBUG24.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG24.u32) + u32AddrOffset));
    VPSS_DEBUG24.bits.debug24 = debug24;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG24.u32) + u32AddrOffset), VPSS_DEBUG24.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug25(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug25)
{
    U_VPSS_DEBUG25 VPSS_DEBUG25;

    VPSS_DEBUG25.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG25.u32) + u32AddrOffset));
    VPSS_DEBUG25.bits.debug25 = debug25;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG25.u32) + u32AddrOffset), VPSS_DEBUG25.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug26(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug26)
{
    U_VPSS_DEBUG26 VPSS_DEBUG26;

    VPSS_DEBUG26.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG26.u32) + u32AddrOffset));
    VPSS_DEBUG26.bits.debug26 = debug26;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG26.u32) + u32AddrOffset), VPSS_DEBUG26.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug27(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug27)
{
    U_VPSS_DEBUG27 VPSS_DEBUG27;

    VPSS_DEBUG27.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG27.u32) + u32AddrOffset));
    VPSS_DEBUG27.bits.debug27 = debug27;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG27.u32) + u32AddrOffset), VPSS_DEBUG27.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug28(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug28)
{
    U_VPSS_DEBUG28 VPSS_DEBUG28;

    VPSS_DEBUG28.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG28.u32) + u32AddrOffset));
    VPSS_DEBUG28.bits.debug28 = debug28;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG28.u32) + u32AddrOffset), VPSS_DEBUG28.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug29(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug29)
{
    U_VPSS_DEBUG29 VPSS_DEBUG29;

    VPSS_DEBUG29.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG29.u32) + u32AddrOffset));
    VPSS_DEBUG29.bits.debug29 = debug29;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG29.u32) + u32AddrOffset), VPSS_DEBUG29.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug30(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug30)
{
    U_VPSS_DEBUG30 VPSS_DEBUG30;

    VPSS_DEBUG30.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG30.u32) + u32AddrOffset));
    VPSS_DEBUG30.bits.debug30 = debug30;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG30.u32) + u32AddrOffset), VPSS_DEBUG30.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug31(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug31)
{
    U_VPSS_DEBUG31 VPSS_DEBUG31;

    VPSS_DEBUG31.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG31.u32) + u32AddrOffset));
    VPSS_DEBUG31.bits.debug31 = debug31;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG31.u32) + u32AddrOffset), VPSS_DEBUG31.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug32(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug32)
{
    U_VPSS_DEBUG32 VPSS_DEBUG32;

    VPSS_DEBUG32.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG32.u32) + u32AddrOffset));
    VPSS_DEBUG32.bits.debug32 = debug32;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG32.u32) + u32AddrOffset), VPSS_DEBUG32.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug33(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug33)
{
    U_VPSS_DEBUG33 VPSS_DEBUG33;

    VPSS_DEBUG33.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG33.u32) + u32AddrOffset));
    VPSS_DEBUG33.bits.debug33 = debug33;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG33.u32) + u32AddrOffset), VPSS_DEBUG33.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug34(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug34)
{
    U_VPSS_DEBUG34 VPSS_DEBUG34;

    VPSS_DEBUG34.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG34.u32) + u32AddrOffset));
    VPSS_DEBUG34.bits.debug34 = debug34;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG34.u32) + u32AddrOffset), VPSS_DEBUG34.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug35(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug35)
{
    U_VPSS_DEBUG35 VPSS_DEBUG35;

    VPSS_DEBUG35.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG35.u32) + u32AddrOffset));
    VPSS_DEBUG35.bits.debug35 = debug35;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG35.u32) + u32AddrOffset), VPSS_DEBUG35.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug36(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug36)
{
    U_VPSS_DEBUG36 VPSS_DEBUG36;

    VPSS_DEBUG36.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG36.u32) + u32AddrOffset));
    VPSS_DEBUG36.bits.debug36 = debug36;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG36.u32) + u32AddrOffset), VPSS_DEBUG36.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug37(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug37)
{
    U_VPSS_DEBUG37 VPSS_DEBUG37;

    VPSS_DEBUG37.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG37.u32) + u32AddrOffset));
    VPSS_DEBUG37.bits.debug37 = debug37;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG37.u32) + u32AddrOffset), VPSS_DEBUG37.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug38(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug38)
{
    U_VPSS_DEBUG38 VPSS_DEBUG38;

    VPSS_DEBUG38.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG38.u32) + u32AddrOffset));
    VPSS_DEBUG38.bits.debug38 = debug38;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG38.u32) + u32AddrOffset), VPSS_DEBUG38.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug39(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug39)
{
    U_VPSS_DEBUG39 VPSS_DEBUG39;

    VPSS_DEBUG39.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG39.u32) + u32AddrOffset));
    VPSS_DEBUG39.bits.debug39 = debug39;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG39.u32) + u32AddrOffset), VPSS_DEBUG39.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug40(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug40)
{
    U_VPSS_DEBUG40 VPSS_DEBUG40;

    VPSS_DEBUG40.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG40.u32) + u32AddrOffset));
    VPSS_DEBUG40.bits.debug40 = debug40;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG40.u32) + u32AddrOffset), VPSS_DEBUG40.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug41(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug41)
{
    U_VPSS_DEBUG41 VPSS_DEBUG41;

    VPSS_DEBUG41.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG41.u32) + u32AddrOffset));
    VPSS_DEBUG41.bits.debug41 = debug41;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG41.u32) + u32AddrOffset), VPSS_DEBUG41.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug42(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug42)
{
    U_VPSS_DEBUG42 VPSS_DEBUG42;

    VPSS_DEBUG42.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG42.u32) + u32AddrOffset));
    VPSS_DEBUG42.bits.debug42 = debug42;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG42.u32) + u32AddrOffset), VPSS_DEBUG42.u32);

    return ;
}



HI_VOID VPSS_Sys_SetDebug43(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 debug43)
{
    U_VPSS_DEBUG43 VPSS_DEBUG43;

    VPSS_DEBUG43.u32 = VPSS_RegRead((&(pstVpssRegs->VPSS_DEBUG43.u32) + u32AddrOffset));
    VPSS_DEBUG43.bits.debug43 = debug43;
    VPSS_RegWrite((&(pstVpssRegs->VPSS_DEBUG43.u32) + u32AddrOffset), VPSS_DEBUG43.u32);

    return ;
}

#endif

//module_name : SYS



