#include "vpss_hal_comm.h"
#include "vpss_hal_ip_mmu.h"
#include "vpss_cbb_reg.h"

#define  MMU_OFFSET (0x800/4)

HI_VOID VPSS_MMU_SetPtwPf(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptw_pf)
{
    U_VPSS0_SMMU_SCR VPSS0_SMMU_SCR;

    VPSS0_SMMU_SCR.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_SCR.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_SCR.bits.ptw_pf = ptw_pf;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_SCR.u32) + layer * MMU_OFFSET), VPSS0_SMMU_SCR.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 int_en)
{
    U_VPSS0_SMMU_SCR VPSS0_SMMU_SCR;

    VPSS0_SMMU_SCR.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_SCR.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_SCR.bits.int_en = int_en;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_SCR.u32) + layer * MMU_OFFSET), VPSS0_SMMU_SCR.u32);

    return ;
}


HI_VOID VPSS_MMU_SetGlbBypass(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 glb_bypass)
{
    U_VPSS0_SMMU_SCR VPSS0_SMMU_SCR;

    VPSS0_SMMU_SCR.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_SCR.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_SCR.bits.glb_bypass = glb_bypass;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_SCR.u32) + layer * MMU_OFFSET), VPSS0_SMMU_SCR.u32);

    return ;
}


// HI_VOID VPSS_MMU_SetSmmuIdle(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 smmu_idle)
// {
//  U_VPSS0_SMMU_LP_CTRL VPSS0_SMMU_LP_CTRL;
//
//  VPSS0_SMMU_LP_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_LP_CTRL.u32) + layer * MMU_OFFSET));
//  VPSS0_SMMU_LP_CTRL.bits.smmu_idle = smmu_idle;
//  VPSS_RegWrite((&(pstReg->VPSS0_SMMU_LP_CTRL.u32) + layer * MMU_OFFSET),VPSS0_SMMU_LP_CTRL.u32);
//
//  return ;
// }


HI_VOID VPSS_MMU_SetAutoClkGtEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 auto_clk_gt_en)
{
    U_VPSS0_SMMU_LP_CTRL VPSS0_SMMU_LP_CTRL;

    VPSS0_SMMU_LP_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_LP_CTRL.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_LP_CTRL.bits.auto_clk_gt_en = auto_clk_gt_en;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_LP_CTRL.u32) + layer * MMU_OFFSET), VPSS0_SMMU_LP_CTRL.u32);

    return ;
}


HI_VOID VPSS_MMU_SetRfsRet1n(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 rfs_ret1n)
{
    U_VPSS0_SMMU_MEM_SPEEDCTRL VPSS0_SMMU_MEM_SPEEDCTRL;

    VPSS0_SMMU_MEM_SPEEDCTRL.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MEM_SPEEDCTRL.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MEM_SPEEDCTRL.bits.rfs_ret1n = rfs_ret1n;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MEM_SPEEDCTRL.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MEM_SPEEDCTRL.u32);

    return ;
}


HI_VOID VPSS_MMU_SetRfsEma(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 rfs_ema)
{
    U_VPSS0_SMMU_MEM_SPEEDCTRL VPSS0_SMMU_MEM_SPEEDCTRL;

    VPSS0_SMMU_MEM_SPEEDCTRL.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MEM_SPEEDCTRL.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MEM_SPEEDCTRL.bits.rfs_ema = rfs_ema;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MEM_SPEEDCTRL.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MEM_SPEEDCTRL.u32);

    return ;
}


HI_VOID VPSS_MMU_SetRfsEmaw(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 rfs_emaw)
{
    U_VPSS0_SMMU_MEM_SPEEDCTRL VPSS0_SMMU_MEM_SPEEDCTRL;

    VPSS0_SMMU_MEM_SPEEDCTRL.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MEM_SPEEDCTRL.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MEM_SPEEDCTRL.bits.rfs_emaw = rfs_emaw;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MEM_SPEEDCTRL.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MEM_SPEEDCTRL.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbinvalidWrMsk(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbinvalid_wr_msk)
{
    U_VPSS0_SMMU_INTMASK_S VPSS0_SMMU_INTMASK_S;

    VPSS0_SMMU_INTMASK_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTMASK_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTMASK_S.bits.ints_tlbinvalid_wr_msk = ints_tlbinvalid_wr_msk;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTMASK_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTMASK_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbinvalidRdMsk(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbinvalid_rd_msk)
{
    U_VPSS0_SMMU_INTMASK_S VPSS0_SMMU_INTMASK_S;

    VPSS0_SMMU_INTMASK_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTMASK_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTMASK_S.bits.ints_tlbinvalid_rd_msk = ints_tlbinvalid_rd_msk;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTMASK_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTMASK_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsPtwTransMsk(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_ptw_trans_msk)
{
    U_VPSS0_SMMU_INTMASK_S VPSS0_SMMU_INTMASK_S;

    VPSS0_SMMU_INTMASK_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTMASK_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTMASK_S.bits.ints_ptw_trans_msk = ints_ptw_trans_msk;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTMASK_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTMASK_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbmissMsk(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbmiss_msk)
{
    U_VPSS0_SMMU_INTMASK_S VPSS0_SMMU_INTMASK_S;

    VPSS0_SMMU_INTMASK_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTMASK_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTMASK_S.bits.ints_tlbmiss_msk = ints_tlbmiss_msk;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTMASK_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTMASK_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbinvalidWrRaw(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbinvalid_wr_raw)
{
    U_VPSS0_SMMU_INTRAW_S VPSS0_SMMU_INTRAW_S;

    VPSS0_SMMU_INTRAW_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTRAW_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTRAW_S.bits.ints_tlbinvalid_wr_raw = ints_tlbinvalid_wr_raw;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTRAW_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTRAW_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbinvalidRdRaw(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbinvalid_rd_raw)
{
    U_VPSS0_SMMU_INTRAW_S VPSS0_SMMU_INTRAW_S;

    VPSS0_SMMU_INTRAW_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTRAW_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTRAW_S.bits.ints_tlbinvalid_rd_raw = ints_tlbinvalid_rd_raw;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTRAW_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTRAW_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsPtwTransRaw(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_ptw_trans_raw)
{
    U_VPSS0_SMMU_INTRAW_S VPSS0_SMMU_INTRAW_S;

    VPSS0_SMMU_INTRAW_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTRAW_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTRAW_S.bits.ints_ptw_trans_raw = ints_ptw_trans_raw;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTRAW_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTRAW_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbmissRaw(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbmiss_raw)
{
    U_VPSS0_SMMU_INTRAW_S VPSS0_SMMU_INTRAW_S;

    VPSS0_SMMU_INTRAW_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTRAW_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTRAW_S.bits.ints_tlbmiss_raw = ints_tlbmiss_raw;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTRAW_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTRAW_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbinvalidWrStat(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbinvalid_wr_stat)
{
    U_VPSS0_SMMU_INTSTAT_S VPSS0_SMMU_INTSTAT_S;

    VPSS0_SMMU_INTSTAT_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTSTAT_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTSTAT_S.bits.ints_tlbinvalid_wr_stat = ints_tlbinvalid_wr_stat;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTSTAT_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTSTAT_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbinvalidRdStat(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbinvalid_rd_stat)
{
    U_VPSS0_SMMU_INTSTAT_S VPSS0_SMMU_INTSTAT_S;

    VPSS0_SMMU_INTSTAT_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTSTAT_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTSTAT_S.bits.ints_tlbinvalid_rd_stat = ints_tlbinvalid_rd_stat;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTSTAT_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTSTAT_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsPtwTransStat(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_ptw_trans_stat)
{
    U_VPSS0_SMMU_INTSTAT_S VPSS0_SMMU_INTSTAT_S;

    VPSS0_SMMU_INTSTAT_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTSTAT_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTSTAT_S.bits.ints_ptw_trans_stat = ints_ptw_trans_stat;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTSTAT_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTSTAT_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbmissStat(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbmiss_stat)
{
    U_VPSS0_SMMU_INTSTAT_S VPSS0_SMMU_INTSTAT_S;

    VPSS0_SMMU_INTSTAT_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTSTAT_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTSTAT_S.bits.ints_tlbmiss_stat = ints_tlbmiss_stat;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTSTAT_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTSTAT_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbinvalidWrClr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbinvalid_wr_clr)
{
    U_VPSS0_SMMU_INTCLR_S VPSS0_SMMU_INTCLR_S;

    VPSS0_SMMU_INTCLR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTCLR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTCLR_S.bits.ints_tlbinvalid_wr_clr = ints_tlbinvalid_wr_clr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTCLR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbinvalidRdClr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbinvalid_rd_clr)
{
    U_VPSS0_SMMU_INTCLR_S VPSS0_SMMU_INTCLR_S;

    VPSS0_SMMU_INTCLR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTCLR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTCLR_S.bits.ints_tlbinvalid_rd_clr = ints_tlbinvalid_rd_clr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTCLR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsPtwTransClr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_ptw_trans_clr)
{
    U_VPSS0_SMMU_INTCLR_S VPSS0_SMMU_INTCLR_S;

    VPSS0_SMMU_INTCLR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTCLR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTCLR_S.bits.ints_ptw_trans_clr = ints_ptw_trans_clr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTCLR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntsTlbmissClr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ints_tlbmiss_clr)
{
    U_VPSS0_SMMU_INTCLR_S VPSS0_SMMU_INTCLR_S;

    VPSS0_SMMU_INTCLR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTCLR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTCLR_S.bits.ints_tlbmiss_clr = ints_tlbmiss_clr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTCLR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbinvalidWrMsk(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbinvalid_wr_msk)
{
    U_VPSS0_SMMU_INTMASK_NS VPSS0_SMMU_INTMASK_NS;

    VPSS0_SMMU_INTMASK_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTMASK_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTMASK_NS.bits.intns_tlbinvalid_wr_msk = intns_tlbinvalid_wr_msk;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTMASK_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTMASK_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbinvalidRdMsk(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbinvalid_rd_msk)
{
    U_VPSS0_SMMU_INTMASK_NS VPSS0_SMMU_INTMASK_NS;

    VPSS0_SMMU_INTMASK_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTMASK_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTMASK_NS.bits.intns_tlbinvalid_rd_msk = intns_tlbinvalid_rd_msk;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTMASK_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTMASK_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsPtwTransMsk(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_ptw_trans_msk)
{
    U_VPSS0_SMMU_INTMASK_NS VPSS0_SMMU_INTMASK_NS;

    VPSS0_SMMU_INTMASK_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTMASK_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTMASK_NS.bits.intns_ptw_trans_msk = intns_ptw_trans_msk;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTMASK_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTMASK_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbmissMsk(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbmiss_msk)
{
    U_VPSS0_SMMU_INTMASK_NS VPSS0_SMMU_INTMASK_NS;

    VPSS0_SMMU_INTMASK_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTMASK_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTMASK_NS.bits.intns_tlbmiss_msk = intns_tlbmiss_msk;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTMASK_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTMASK_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbinvalidWrRaw(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbinvalid_wr_raw)
{
    U_VPSS0_SMMU_INTRAW_NS VPSS0_SMMU_INTRAW_NS;

    VPSS0_SMMU_INTRAW_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTRAW_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTRAW_NS.bits.intns_tlbinvalid_wr_raw = intns_tlbinvalid_wr_raw;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTRAW_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTRAW_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbinvalidRdRaw(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbinvalid_rd_raw)
{
    U_VPSS0_SMMU_INTRAW_NS VPSS0_SMMU_INTRAW_NS;

    VPSS0_SMMU_INTRAW_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTRAW_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTRAW_NS.bits.intns_tlbinvalid_rd_raw = intns_tlbinvalid_rd_raw;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTRAW_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTRAW_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsPtwTransRaw(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_ptw_trans_raw)
{
    U_VPSS0_SMMU_INTRAW_NS VPSS0_SMMU_INTRAW_NS;

    VPSS0_SMMU_INTRAW_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTRAW_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTRAW_NS.bits.intns_ptw_trans_raw = intns_ptw_trans_raw;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTRAW_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTRAW_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbmissRaw(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbmiss_raw)
{
    U_VPSS0_SMMU_INTRAW_NS VPSS0_SMMU_INTRAW_NS;

    VPSS0_SMMU_INTRAW_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTRAW_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTRAW_NS.bits.intns_tlbmiss_raw = intns_tlbmiss_raw;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTRAW_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTRAW_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbinvalidWrStat(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbinvalid_wr_stat)
{
    U_VPSS0_SMMU_INTSTAT_NS VPSS0_SMMU_INTSTAT_NS;

    VPSS0_SMMU_INTSTAT_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTSTAT_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTSTAT_NS.bits.intns_tlbinvalid_wr_stat = intns_tlbinvalid_wr_stat;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTSTAT_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTSTAT_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbinvalidRdStat(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbinvalid_rd_stat)
{
    U_VPSS0_SMMU_INTSTAT_NS VPSS0_SMMU_INTSTAT_NS;

    VPSS0_SMMU_INTSTAT_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTSTAT_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTSTAT_NS.bits.intns_tlbinvalid_rd_stat = intns_tlbinvalid_rd_stat;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTSTAT_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTSTAT_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsPtwTransStat(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_ptw_trans_stat)
{
    U_VPSS0_SMMU_INTSTAT_NS VPSS0_SMMU_INTSTAT_NS;

    VPSS0_SMMU_INTSTAT_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTSTAT_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTSTAT_NS.bits.intns_ptw_trans_stat = intns_ptw_trans_stat;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTSTAT_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTSTAT_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbmissStat(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbmiss_stat)
{
    U_VPSS0_SMMU_INTSTAT_NS VPSS0_SMMU_INTSTAT_NS;

    VPSS0_SMMU_INTSTAT_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTSTAT_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTSTAT_NS.bits.intns_tlbmiss_stat = intns_tlbmiss_stat;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTSTAT_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTSTAT_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbinvalidWrClr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbinvalid_wr_clr)
{
    U_VPSS0_SMMU_INTCLR_NS VPSS0_SMMU_INTCLR_NS;

    VPSS0_SMMU_INTCLR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTCLR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTCLR_NS.bits.intns_tlbinvalid_wr_clr = intns_tlbinvalid_wr_clr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTCLR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbinvalidRdClr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbinvalid_rd_clr)
{
    U_VPSS0_SMMU_INTCLR_NS VPSS0_SMMU_INTCLR_NS;

    VPSS0_SMMU_INTCLR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTCLR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTCLR_NS.bits.intns_tlbinvalid_rd_clr = intns_tlbinvalid_rd_clr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTCLR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsPtwTransClr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_ptw_trans_clr)
{
    U_VPSS0_SMMU_INTCLR_NS VPSS0_SMMU_INTCLR_NS;

    VPSS0_SMMU_INTCLR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTCLR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTCLR_NS.bits.intns_ptw_trans_clr = intns_ptw_trans_clr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTCLR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetIntnsTlbmissClr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 intns_tlbmiss_clr)
{
    U_VPSS0_SMMU_INTCLR_NS VPSS0_SMMU_INTCLR_NS;

    VPSS0_SMMU_INTCLR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_INTCLR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_INTCLR_NS.bits.intns_tlbmiss_clr = intns_tlbmiss_clr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_INTCLR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_NS.u32);

    return ;
}


// HI_VOID VPSS_MMU_SetScbTtbrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 scb_ttbr_h)
// {
//  U_VPSS0_SMMU_SCB_TTBR_H VPSS0_SMMU_SCB_TTBR_H;
//
//  VPSS0_SMMU_SCB_TTBR_H.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_SCB_TTBR_H.u32) + layer * MMU_OFFSET));
//  VPSS0_SMMU_SCB_TTBR_H.bits.scb_ttbr_h = scb_ttbr_h;
//  VPSS_RegWrite((&(pstReg->VPSS0_SMMU_SCB_TTBR_H.u32) + layer * MMU_OFFSET),VPSS0_SMMU_SCB_TTBR_H.u32);
//
//  return ;
// }


HI_VOID VPSS_MMU_SetScbTtbr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 scb_ttbr)
{
    U_VPSS0_SMMU_SCB_TTBR VPSS0_SMMU_SCB_TTBR;

    VPSS0_SMMU_SCB_TTBR.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_SCB_TTBR.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_SCB_TTBR.bits.scb_ttbr = scb_ttbr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_SCB_TTBR.u32) + layer * MMU_OFFSET), VPSS0_SMMU_SCB_TTBR.u32);

    return ;
}


// HI_VOID VPSS_MMU_SetCbTtbrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cb_ttbr_h)
// {
//  U_VPSS0_SMMU_CB_TTBR_H VPSS0_SMMU_CB_TTBR_H;
//
//  VPSS0_SMMU_CB_TTBR_H.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_CB_TTBR_H.u32) + layer * MMU_OFFSET));
//  VPSS0_SMMU_CB_TTBR_H.bits.cb_ttbr_h = cb_ttbr_h;
//  VPSS_RegWrite((&(pstReg->VPSS0_SMMU_CB_TTBR_H.u32) + layer * MMU_OFFSET),VPSS0_SMMU_CB_TTBR_H.u32);
//
//  return ;
// }


HI_VOID VPSS_MMU_SetCbTtbr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cb_ttbr)
{
    U_VPSS0_SMMU_CB_TTBR VPSS0_SMMU_CB_TTBR;

    VPSS0_SMMU_CB_TTBR.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_CB_TTBR.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_CB_TTBR.bits.cb_ttbr = cb_ttbr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_CB_TTBR.u32) + layer * MMU_OFFSET), VPSS0_SMMU_CB_TTBR.u32);

    return ;
}


// HI_VOID VPSS_MMU_SetErrSRdAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 err_s_rd_addr_h)
// {
//  U_VPSS0_SMMU_ERR_RDADDR_H_S VPSS0_SMMU_ERR_RDADDR_H_S;
//
//  VPSS0_SMMU_ERR_RDADDR_H_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_ERR_RDADDR_H_S.u32) + layer * MMU_OFFSET));
//  VPSS0_SMMU_ERR_RDADDR_H_S.bits.err_s_rd_addr_h = err_s_rd_addr_h;
//  VPSS_RegWrite((&(pstReg->VPSS0_SMMU_ERR_RDADDR_H_S.u32) + layer * MMU_OFFSET),VPSS0_SMMU_ERR_RDADDR_H_S.u32);
//
//  return ;
// }


HI_VOID VPSS_MMU_SetErrSRdAddr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 err_s_rd_addr)
{
    U_VPSS0_SMMU_ERR_RDADDR_S VPSS0_SMMU_ERR_RDADDR_S;

    VPSS0_SMMU_ERR_RDADDR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_ERR_RDADDR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_ERR_RDADDR_S.bits.err_s_rd_addr = err_s_rd_addr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_ERR_RDADDR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_ERR_RDADDR_S.u32);

    return ;
}


// HI_VOID VPSS_MMU_SetErrSWrAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 err_s_wr_addr_h)
// {
//  U_VPSS0_SMMU_ERR_WRADDR_H_S VPSS0_SMMU_ERR_WRADDR_H_S;
//
//  VPSS0_SMMU_ERR_WRADDR_H_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_ERR_WRADDR_H_S.u32) + layer * MMU_OFFSET));
//  VPSS0_SMMU_ERR_WRADDR_H_S.bits.err_s_wr_addr_h = err_s_wr_addr_h;
//  VPSS_RegWrite((&(pstReg->VPSS0_SMMU_ERR_WRADDR_H_S.u32) + layer * MMU_OFFSET),VPSS0_SMMU_ERR_WRADDR_H_S.u32);
//
//  return ;
// }


HI_VOID VPSS_MMU_SetErrSWrAddr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 err_s_wr_addr)
{
    U_VPSS0_SMMU_ERR_WRADDR_S VPSS0_SMMU_ERR_WRADDR_S;

    VPSS0_SMMU_ERR_WRADDR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_ERR_WRADDR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_ERR_WRADDR_S.bits.err_s_wr_addr = err_s_wr_addr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_ERR_WRADDR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_ERR_WRADDR_S.u32);

    return ;
}


// HI_VOID VPSS_MMU_SetErrNsRdAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 err_ns_rd_addr_h)
// {
//  U_VPSS0_SMMU_ERR_RDADDR_H_NS VPSS0_SMMU_ERR_RDADDR_H_NS;
//
//  VPSS0_SMMU_ERR_RDADDR_H_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_ERR_RDADDR_H_NS.u32) + layer * MMU_OFFSET));
//  VPSS0_SMMU_ERR_RDADDR_H_NS.bits.err_ns_rd_addr_h = err_ns_rd_addr_h;
//  VPSS_RegWrite((&(pstReg->VPSS0_SMMU_ERR_RDADDR_H_NS.u32) + layer * MMU_OFFSET),VPSS0_SMMU_ERR_RDADDR_H_NS.u32);
//
//  return ;
// }


HI_VOID VPSS_MMU_SetErrNsRdAddr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 err_ns_rd_addr)
{
    U_VPSS0_SMMU_ERR_RDADDR_NS VPSS0_SMMU_ERR_RDADDR_NS;

    VPSS0_SMMU_ERR_RDADDR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_ERR_RDADDR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_ERR_RDADDR_NS.bits.err_ns_rd_addr = err_ns_rd_addr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_ERR_RDADDR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_ERR_RDADDR_NS.u32);

    return ;
}


// HI_VOID VPSS_MMU_SetErrNsWrAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 err_ns_wr_addr_h)
// {
//  U_VPSS0_SMMU_ERR_WRADDR_H_NS VPSS0_SMMU_ERR_WRADDR_H_NS;
//
//  VPSS0_SMMU_ERR_WRADDR_H_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_ERR_WRADDR_H_NS.u32) + layer * MMU_OFFSET));
//  VPSS0_SMMU_ERR_WRADDR_H_NS.bits.err_ns_wr_addr_h = err_ns_wr_addr_h;
//  VPSS_RegWrite((&(pstReg->VPSS0_SMMU_ERR_WRADDR_H_NS.u32) + layer * MMU_OFFSET),VPSS0_SMMU_ERR_WRADDR_H_NS.u32);
//
//  return ;
// }


HI_VOID VPSS_MMU_SetErrNsWrAddr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 err_ns_wr_addr)
{
    U_VPSS0_SMMU_ERR_WRADDR_NS VPSS0_SMMU_ERR_WRADDR_NS;

    VPSS0_SMMU_ERR_WRADDR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_ERR_WRADDR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_ERR_WRADDR_NS.bits.err_ns_wr_addr = err_ns_wr_addr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_ERR_WRADDR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_ERR_WRADDR_NS.u32);

    return ;
}


// HI_VOID VPSS_MMU_SetFaultAddrhPtwS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_addrh_ptw_s)
// {
//  U_VPSS0_SMMU_FAULT_ADDRH_PTW_S VPSS0_SMMU_FAULT_ADDRH_PTW_S;
//
//  VPSS0_SMMU_FAULT_ADDRH_PTW_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ADDRH_PTW_S.u32) + layer * MMU_OFFSET));
//  VPSS0_SMMU_FAULT_ADDRH_PTW_S.bits.fault_addrh_ptw_s = fault_addrh_ptw_s;
//  VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ADDRH_PTW_S.u32) + layer * MMU_OFFSET),VPSS0_SMMU_FAULT_ADDRH_PTW_S.u32);
//
//  return ;
// }


HI_VOID VPSS_MMU_SetFaultAddrPtwS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_addr_ptw_s)
{
    U_VPSS0_SMMU_FAULT_ADDR_PTW_S VPSS0_SMMU_FAULT_ADDR_PTW_S;

    VPSS0_SMMU_FAULT_ADDR_PTW_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ADDR_PTW_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ADDR_PTW_S.bits.fault_addr_ptw_s = fault_addr_ptw_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ADDR_PTW_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ADDR_PTW_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultStrmIdS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_strm_id_s)
{
    U_VPSS0_SMMU_FAULT_ID_PTW_S VPSS0_SMMU_FAULT_ID_PTW_S;

    VPSS0_SMMU_FAULT_ID_PTW_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_PTW_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_PTW_S.bits.fault_strm_id_s = fault_strm_id_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_PTW_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_PTW_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultIndexIdS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_index_id_s)
{
    U_VPSS0_SMMU_FAULT_ID_PTW_S VPSS0_SMMU_FAULT_ID_PTW_S;

    VPSS0_SMMU_FAULT_ID_PTW_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_PTW_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_PTW_S.bits.fault_index_id_s = fault_index_id_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_PTW_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_PTW_S.u32);

    return ;
}


// HI_VOID VPSS_MMU_SetFaultAddrhPtwNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_addrh_ptw_ns)
// {
//  U_VPSS0_SMMU_FAULT_ADDRH_PTW_NS VPSS0_SMMU_FAULT_ADDRH_PTW_NS;
//
//  VPSS0_SMMU_FAULT_ADDRH_PTW_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ADDRH_PTW_NS.u32) + layer * MMU_OFFSET));
//  VPSS0_SMMU_FAULT_ADDRH_PTW_NS.bits.fault_addrh_ptw_ns = fault_addrh_ptw_ns;
//  VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ADDRH_PTW_NS.u32) + layer * MMU_OFFSET),VPSS0_SMMU_FAULT_ADDRH_PTW_NS.u32);
//
//  return ;
// }


HI_VOID VPSS_MMU_SetFaultAddrPtwNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_addr_ptw_ns)
{
    U_VPSS0_SMMU_FAULT_ADDR_PTW_NS VPSS0_SMMU_FAULT_ADDR_PTW_NS;

    VPSS0_SMMU_FAULT_ADDR_PTW_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ADDR_PTW_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ADDR_PTW_NS.bits.fault_addr_ptw_ns = fault_addr_ptw_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ADDR_PTW_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ADDR_PTW_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultStrmIdNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_strm_id_ns)
{
    U_VPSS0_SMMU_FAULT_ID_PTW_NS VPSS0_SMMU_FAULT_ID_PTW_NS;

    VPSS0_SMMU_FAULT_ID_PTW_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_PTW_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_PTW_NS.bits.fault_strm_id_ns = fault_strm_id_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_PTW_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_PTW_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultIndexIdNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_index_id_ns)
{
    U_VPSS0_SMMU_FAULT_ID_PTW_NS VPSS0_SMMU_FAULT_ID_PTW_NS;

    VPSS0_SMMU_FAULT_ID_PTW_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_PTW_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_PTW_NS.bits.fault_index_id_ns = fault_index_id_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_PTW_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_PTW_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultNsPtwNum(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_ns_ptw_num)
{
    U_VPSS0_SMMU_FAULT_PTW_NUM VPSS0_SMMU_FAULT_PTW_NUM;

    VPSS0_SMMU_FAULT_PTW_NUM.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_PTW_NUM.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_PTW_NUM.bits.fault_ns_ptw_num = fault_ns_ptw_num;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_PTW_NUM.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_PTW_NUM.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultSPtwNum(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_s_ptw_num)
{
    U_VPSS0_SMMU_FAULT_PTW_NUM VPSS0_SMMU_FAULT_PTW_NUM;

    VPSS0_SMMU_FAULT_PTW_NUM.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_PTW_NUM.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_PTW_NUM.bits.fault_s_ptw_num = fault_s_ptw_num;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_PTW_NUM.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_PTW_NUM.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultAddrWrS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_addr_wr_s)
{
    U_VPSS0_SMMU_FAULT_ADDR_WR_S VPSS0_SMMU_FAULT_ADDR_WR_S;

    VPSS0_SMMU_FAULT_ADDR_WR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ADDR_WR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ADDR_WR_S.bits.fault_addr_wr_s = fault_addr_wr_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ADDR_WR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ADDR_WR_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultTlbWrS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_tlb_wr_s)
{
    U_VPSS0_SMMU_FAULT_TLB_WR_S VPSS0_SMMU_FAULT_TLB_WR_S;

    VPSS0_SMMU_FAULT_TLB_WR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TLB_WR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TLB_WR_S.bits.fault_tlb_wr_s = fault_tlb_wr_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TLB_WR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TLB_WR_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultStrIdWrS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_str_id_wr_s)
{
    U_VPSS0_SMMU_FAULT_ID_WR_S VPSS0_SMMU_FAULT_ID_WR_S;

    VPSS0_SMMU_FAULT_ID_WR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_WR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_WR_S.bits.fault_str_id_wr_s = fault_str_id_wr_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_WR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_WR_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultIndexIdWrS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_index_id_wr_s)
{
    U_VPSS0_SMMU_FAULT_ID_WR_S VPSS0_SMMU_FAULT_ID_WR_S;

    VPSS0_SMMU_FAULT_ID_WR_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_WR_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_WR_S.bits.fault_index_id_wr_s = fault_index_id_wr_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_WR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_WR_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultAddrWrNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_addr_wr_ns)
{
    U_VPSS0_SMMU_FAULT_ADDR_WR_NS VPSS0_SMMU_FAULT_ADDR_WR_NS;

    VPSS0_SMMU_FAULT_ADDR_WR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ADDR_WR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ADDR_WR_NS.bits.fault_addr_wr_ns = fault_addr_wr_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ADDR_WR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ADDR_WR_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultTlbWrNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_tlb_wr_ns)
{
    U_VPSS0_SMMU_FAULT_TLB_WR_NS VPSS0_SMMU_FAULT_TLB_WR_NS;

    VPSS0_SMMU_FAULT_TLB_WR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TLB_WR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TLB_WR_NS.bits.fault_tlb_wr_ns = fault_tlb_wr_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TLB_WR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TLB_WR_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultStrIdWrNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_str_id_wr_ns)
{
    U_VPSS0_SMMU_FAULT_ID_WR_NS VPSS0_SMMU_FAULT_ID_WR_NS;

    VPSS0_SMMU_FAULT_ID_WR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_WR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_WR_NS.bits.fault_str_id_wr_ns = fault_str_id_wr_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_WR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_WR_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultIndexIdWrNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_index_id_wr_ns)
{
    U_VPSS0_SMMU_FAULT_ID_WR_NS VPSS0_SMMU_FAULT_ID_WR_NS;

    VPSS0_SMMU_FAULT_ID_WR_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_WR_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_WR_NS.bits.fault_index_id_wr_ns = fault_index_id_wr_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_WR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_WR_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultAddrRdS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_addr_rd_s)
{
    U_VPSS0_SMMU_FAULT_ADDR_RD_S VPSS0_SMMU_FAULT_ADDR_RD_S;

    VPSS0_SMMU_FAULT_ADDR_RD_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ADDR_RD_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ADDR_RD_S.bits.fault_addr_rd_s = fault_addr_rd_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ADDR_RD_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ADDR_RD_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultTlbRdS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_tlb_rd_s)
{
    U_VPSS0_SMMU_FAULT_TLB_RD_S VPSS0_SMMU_FAULT_TLB_RD_S;

    VPSS0_SMMU_FAULT_TLB_RD_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TLB_RD_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TLB_RD_S.bits.fault_tlb_rd_s = fault_tlb_rd_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TLB_RD_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TLB_RD_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultStrIdRdS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_str_id_rd_s)
{
    U_VPSS0_SMMU_FAULT_ID_RD_S VPSS0_SMMU_FAULT_ID_RD_S;

    VPSS0_SMMU_FAULT_ID_RD_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_RD_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_RD_S.bits.fault_str_id_rd_s = fault_str_id_rd_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_RD_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_RD_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultIndexIdRdS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_index_id_rd_s)
{
    U_VPSS0_SMMU_FAULT_ID_RD_S VPSS0_SMMU_FAULT_ID_RD_S;

    VPSS0_SMMU_FAULT_ID_RD_S.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_RD_S.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_RD_S.bits.fault_index_id_rd_s = fault_index_id_rd_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_RD_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_RD_S.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultAddrRdNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_addr_rd_ns)
{
    U_VPSS0_SMMU_FAULT_ADDR_RD_NS VPSS0_SMMU_FAULT_ADDR_RD_NS;

    VPSS0_SMMU_FAULT_ADDR_RD_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ADDR_RD_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ADDR_RD_NS.bits.fault_addr_rd_ns = fault_addr_rd_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ADDR_RD_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ADDR_RD_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultTlbRdNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_tlb_rd_ns)
{
    U_VPSS0_SMMU_FAULT_TLB_RD_NS VPSS0_SMMU_FAULT_TLB_RD_NS;

    VPSS0_SMMU_FAULT_TLB_RD_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TLB_RD_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TLB_RD_NS.bits.fault_tlb_rd_ns = fault_tlb_rd_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TLB_RD_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TLB_RD_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultStrIdRdNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_str_id_rd_ns)
{
    U_VPSS0_SMMU_FAULT_ID_RD_NS VPSS0_SMMU_FAULT_ID_RD_NS;

    VPSS0_SMMU_FAULT_ID_RD_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_RD_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_RD_NS.bits.fault_str_id_rd_ns = fault_str_id_rd_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_RD_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_RD_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultIndexIdRdNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_index_id_rd_ns)
{
    U_VPSS0_SMMU_FAULT_ID_RD_NS VPSS0_SMMU_FAULT_ID_RD_NS;

    VPSS0_SMMU_FAULT_ID_RD_NS.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_ID_RD_NS.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_ID_RD_NS.bits.fault_index_id_rd_ns = fault_index_id_rd_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_ID_RD_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_ID_RD_NS.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultTbuNum(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_tbu_num)
{
    U_VPSS0_SMMU_FAULT_TBU_INFO VPSS0_SMMU_FAULT_TBU_INFO;

    VPSS0_SMMU_FAULT_TBU_INFO.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_INFO.bits.fault_tbu_num = fault_tbu_num;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_INFO.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultTlbinvalidErrNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_tlbinvalid_err_ns)
{
    U_VPSS0_SMMU_FAULT_TBU_INFO VPSS0_SMMU_FAULT_TBU_INFO;

    VPSS0_SMMU_FAULT_TBU_INFO.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_INFO.bits.fault_tlbinvalid_err_ns = fault_tlbinvalid_err_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_INFO.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultTlbmissErrNs(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_tlbmiss_err_ns)
{
    U_VPSS0_SMMU_FAULT_TBU_INFO VPSS0_SMMU_FAULT_TBU_INFO;

    VPSS0_SMMU_FAULT_TBU_INFO.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_INFO.bits.fault_tlbmiss_err_ns = fault_tlbmiss_err_ns;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_INFO.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultTlbinvalidErrS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_tlbinvalid_err_s)
{
    U_VPSS0_SMMU_FAULT_TBU_INFO VPSS0_SMMU_FAULT_TBU_INFO;

    VPSS0_SMMU_FAULT_TBU_INFO.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_INFO.bits.fault_tlbinvalid_err_s = fault_tlbinvalid_err_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_INFO.u32);

    return ;
}


HI_VOID VPSS_MMU_SetFaultTlbmissErrS(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 fault_tlbmiss_err_s)
{
    U_VPSS0_SMMU_FAULT_TBU_INFO VPSS0_SMMU_FAULT_TBU_INFO;

    VPSS0_SMMU_FAULT_TBU_INFO.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_INFO.bits.fault_tlbmiss_err_s = fault_tlbmiss_err_s;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_INFO.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_INFO.u32);

    return ;
}


HI_VOID VPSS_MMU_SetReadCommandCounter(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 read_command_counter)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.read_command_counter = read_command_counter;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetArchStallN(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 arch_stall_n)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.arch_stall_n = arch_stall_n;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetTbuArreadym(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 tbu_arreadym)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.tbu_arreadym = tbu_arreadym;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetArReadys(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ar_readys)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.ar_readys = ar_readys;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetArValids(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ar_valids)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.ar_valids = ar_valids;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetWriteCommandCounter(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 write_command_counter)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.write_command_counter = write_command_counter;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetAwchStallN(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 awch_stall_n)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.awch_stall_n = awch_stall_n;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetTbuAwreadym(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 tbu_awreadym)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.tbu_awreadym = tbu_awreadym;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetAwReadys(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 aw_readys)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.aw_readys = aw_readys;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetAwValids(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 aw_valids)
{
    U_VPSS0_SMMU_FAULT_TBU_DBG VPSS0_SMMU_FAULT_TBU_DBG;

    VPSS0_SMMU_FAULT_TBU_DBG.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_FAULT_TBU_DBG.bits.aw_valids = aw_valids;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_FAULT_TBU_DBG.u32) + layer * MMU_OFFSET), VPSS0_SMMU_FAULT_TBU_DBG.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPrefBufferEmpty(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 pref_buffer_empty)
{
    U_VPSS0_SMMU_PREF_BUFFER_EMPTY VPSS0_SMMU_PREF_BUFFER_EMPTY;

    VPSS0_SMMU_PREF_BUFFER_EMPTY.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PREF_BUFFER_EMPTY.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PREF_BUFFER_EMPTY.bits.pref_buffer_empty = pref_buffer_empty;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PREF_BUFFER_EMPTY.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PREF_BUFFER_EMPTY.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq15IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq15_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq15_idle_state = ptwq15_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq14IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq14_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq14_idle_state = ptwq14_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq13IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq13_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq13_idle_state = ptwq13_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq12IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq12_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq12_idle_state = ptwq12_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq11IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq11_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq11_idle_state = ptwq11_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq10IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq10_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq10_idle_state = ptwq10_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq9IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq9_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq9_idle_state = ptwq9_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq8IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq8_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq8_idle_state = ptwq8_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq7IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq7_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq7_idle_state = ptwq7_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq6IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq6_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq6_idle_state = ptwq6_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq5IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq5_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq5_idle_state = ptwq5_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq4IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq4_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq4_idle_state = ptwq4_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq3IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq3_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq3_idle_state = ptwq3_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq2IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq2_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq2_idle_state = ptwq2_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq1IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq1_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq1_idle_state = ptwq1_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetPtwq0IdleState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 ptwq0_idle_state)
{
    U_VPSS0_SMMU_PTWQ_IDLE VPSS0_SMMU_PTWQ_IDLE;

    VPSS0_SMMU_PTWQ_IDLE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_PTWQ_IDLE.bits.ptwq0_idle_state = ptwq0_idle_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_PTWQ_IDLE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_PTWQ_IDLE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetSmmuRstState(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 smmu_rst_state)
{
    U_VPSS0_SMMU_RESET_STATE VPSS0_SMMU_RESET_STATE;

    VPSS0_SMMU_RESET_STATE.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_RESET_STATE.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_RESET_STATE.bits.smmu_rst_state = smmu_rst_state;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_RESET_STATE.u32) + layer * MMU_OFFSET), VPSS0_SMMU_RESET_STATE.u32);

    return ;
}


HI_VOID VPSS_MMU_SetInOutCmdCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 in_out_cmd_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG0 VPSS0_SMMU_MASTER_DBG0;

    VPSS0_SMMU_MASTER_DBG0.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG0.bits.in_out_cmd_cnt_rd = in_out_cmd_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG0.u32);

    return ;
}


HI_VOID VPSS_MMU_SetRdyDebugRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 rdy_debug_rd)
{
    U_VPSS0_SMMU_MASTER_DBG0 VPSS0_SMMU_MASTER_DBG0;

    VPSS0_SMMU_MASTER_DBG0.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG0.bits.rdy_debug_rd = rdy_debug_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG0.u32);

    return ;
}


HI_VOID VPSS_MMU_SetVldDebugRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 vld_debug_rd)
{
    U_VPSS0_SMMU_MASTER_DBG0 VPSS0_SMMU_MASTER_DBG0;

    VPSS0_SMMU_MASTER_DBG0.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG0.bits.vld_debug_rd = vld_debug_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG0.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurMissCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_miss_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG0 VPSS0_SMMU_MASTER_DBG0;

    VPSS0_SMMU_MASTER_DBG0.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG0.bits.cur_miss_cnt_rd = cur_miss_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG0.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastMissCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_miss_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG0 VPSS0_SMMU_MASTER_DBG0;

    VPSS0_SMMU_MASTER_DBG0.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG0.bits.last_miss_cnt_rd = last_miss_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG0.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG0.u32);

    return ;
}


HI_VOID VPSS_MMU_SetInOutCmdCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 in_out_cmd_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG1 VPSS0_SMMU_MASTER_DBG1;

    VPSS0_SMMU_MASTER_DBG1.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG1.bits.in_out_cmd_cnt_wr = in_out_cmd_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG1.u32);

    return ;
}


HI_VOID VPSS_MMU_SetRdyDebugWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 rdy_debug_wr)
{
    U_VPSS0_SMMU_MASTER_DBG1 VPSS0_SMMU_MASTER_DBG1;

    VPSS0_SMMU_MASTER_DBG1.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG1.bits.rdy_debug_wr = rdy_debug_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG1.u32);

    return ;
}


HI_VOID VPSS_MMU_SetVldDebugWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 vld_debug_wr)
{
    U_VPSS0_SMMU_MASTER_DBG1 VPSS0_SMMU_MASTER_DBG1;

    VPSS0_SMMU_MASTER_DBG1.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG1.bits.vld_debug_wr = vld_debug_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG1.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurMissCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_miss_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG1 VPSS0_SMMU_MASTER_DBG1;

    VPSS0_SMMU_MASTER_DBG1.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG1.bits.cur_miss_cnt_wr = cur_miss_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG1.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastMissCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_miss_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG1 VPSS0_SMMU_MASTER_DBG1;

    VPSS0_SMMU_MASTER_DBG1.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG1.bits.last_miss_cnt_wr = last_miss_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG1.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG1.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurDoubleUpdCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_double_upd_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG2 VPSS0_SMMU_MASTER_DBG2;

    VPSS0_SMMU_MASTER_DBG2.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG2.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG2.bits.cur_double_upd_cnt_rd = cur_double_upd_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG2.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG2.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastDoubleUpdCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_double_upd_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG2 VPSS0_SMMU_MASTER_DBG2;

    VPSS0_SMMU_MASTER_DBG2.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG2.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG2.bits.last_double_upd_cnt_rd = last_double_upd_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG2.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG2.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurDoubleMissCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_double_miss_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG2 VPSS0_SMMU_MASTER_DBG2;

    VPSS0_SMMU_MASTER_DBG2.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG2.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG2.bits.cur_double_miss_cnt_rd = cur_double_miss_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG2.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG2.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastDoubleMissCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_double_miss_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG2 VPSS0_SMMU_MASTER_DBG2;

    VPSS0_SMMU_MASTER_DBG2.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG2.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG2.bits.last_double_miss_cnt_rd = last_double_miss_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG2.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG2.u32);

    return ;
}


HI_VOID VPSS_MMU_SetMstFsmCur(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 mst_fsm_cur)
{
    U_VPSS0_SMMU_MASTER_DBG3 VPSS0_SMMU_MASTER_DBG3;

    VPSS0_SMMU_MASTER_DBG3.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG3.bits.mst_fsm_cur = mst_fsm_cur;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG3.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurDoubleUpdCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_double_upd_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG3 VPSS0_SMMU_MASTER_DBG3;

    VPSS0_SMMU_MASTER_DBG3.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG3.bits.cur_double_upd_cnt_wr = cur_double_upd_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG3.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastDoubleUpdCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_double_upd_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG3 VPSS0_SMMU_MASTER_DBG3;

    VPSS0_SMMU_MASTER_DBG3.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG3.bits.last_double_upd_cnt_wr = last_double_upd_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG3.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurDoubleMissCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_double_miss_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG3 VPSS0_SMMU_MASTER_DBG3;

    VPSS0_SMMU_MASTER_DBG3.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG3.bits.cur_double_miss_cnt_wr = cur_double_miss_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG3.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastDoubleMissCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_double_miss_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG3 VPSS0_SMMU_MASTER_DBG3;

    VPSS0_SMMU_MASTER_DBG3.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG3.bits.last_double_miss_cnt_wr = last_double_miss_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG3.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG3.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastSel1ChnMissCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_sel1_chn_miss_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG4 VPSS0_SMMU_MASTER_DBG4;

    VPSS0_SMMU_MASTER_DBG4.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG4.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG4.bits.last_sel1_chn_miss_cnt_rd = last_sel1_chn_miss_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG4.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG4.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurSel1ChnMissCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_sel1_chn_miss_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG4 VPSS0_SMMU_MASTER_DBG4;

    VPSS0_SMMU_MASTER_DBG4.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG4.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG4.bits.cur_sel1_chn_miss_cnt_rd = cur_sel1_chn_miss_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG4.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG4.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastSel2ChnMissCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_sel2_chn_miss_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG5 VPSS0_SMMU_MASTER_DBG5;

    VPSS0_SMMU_MASTER_DBG5.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG5.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG5.bits.last_sel2_chn_miss_cnt_rd = last_sel2_chn_miss_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG5.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG5.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurSel2ChnMissCntRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_sel2_chn_miss_cnt_rd)
{
    U_VPSS0_SMMU_MASTER_DBG5 VPSS0_SMMU_MASTER_DBG5;

    VPSS0_SMMU_MASTER_DBG5.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG5.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG5.bits.cur_sel2_chn_miss_cnt_rd = cur_sel2_chn_miss_cnt_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG5.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG5.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastSel1ChnMissCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_sel1_chn_miss_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG6 VPSS0_SMMU_MASTER_DBG6;

    VPSS0_SMMU_MASTER_DBG6.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG6.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG6.bits.last_sel1_chn_miss_cnt_wr = last_sel1_chn_miss_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG6.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG6.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurSel1ChnMissCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_sel1_chn_miss_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG6 VPSS0_SMMU_MASTER_DBG6;

    VPSS0_SMMU_MASTER_DBG6.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG6.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG6.bits.cur_sel1_chn_miss_cnt_wr = cur_sel1_chn_miss_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG6.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG6.u32);

    return ;
}


HI_VOID VPSS_MMU_SetLastSel2ChnMissCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 last_sel2_chn_miss_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG7 VPSS0_SMMU_MASTER_DBG7;

    VPSS0_SMMU_MASTER_DBG7.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG7.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG7.bits.last_sel2_chn_miss_cnt_wr = last_sel2_chn_miss_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG7.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG7.u32);

    return ;
}


HI_VOID VPSS_MMU_SetCurSel2ChnMissCntWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 cur_sel2_chn_miss_cnt_wr)
{
    U_VPSS0_SMMU_MASTER_DBG7 VPSS0_SMMU_MASTER_DBG7;

    VPSS0_SMMU_MASTER_DBG7.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG7.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG7.bits.cur_sel2_chn_miss_cnt_wr = cur_sel2_chn_miss_cnt_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG7.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG7.u32);

    return ;
}


HI_VOID VPSS_MMU_SetSel1ChnRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 sel1_chn_rd)
{
    U_VPSS0_SMMU_MASTER_DBG8 VPSS0_SMMU_MASTER_DBG8;

    VPSS0_SMMU_MASTER_DBG8.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG8.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG8.bits.sel1_chn_rd = sel1_chn_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG8.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG8.u32);

    return ;
}


HI_VOID VPSS_MMU_SetSel2ChnRd(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 sel2_chn_rd)
{
    U_VPSS0_SMMU_MASTER_DBG8 VPSS0_SMMU_MASTER_DBG8;

    VPSS0_SMMU_MASTER_DBG8.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG8.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG8.bits.sel2_chn_rd = sel2_chn_rd;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG8.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG8.u32);

    return ;
}


HI_VOID VPSS_MMU_SetSel1ChnWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 sel1_chn_wr)
{
    U_VPSS0_SMMU_MASTER_DBG8 VPSS0_SMMU_MASTER_DBG8;

    VPSS0_SMMU_MASTER_DBG8.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG8.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG8.bits.sel1_chn_wr = sel1_chn_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG8.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG8.u32);

    return ;
}


HI_VOID VPSS_MMU_SetSel2ChnWr(S_VPSS_REGS_TYPE *pstReg, HI_U32 layer, HI_U32 sel2_chn_wr)
{
    U_VPSS0_SMMU_MASTER_DBG8 VPSS0_SMMU_MASTER_DBG8;

    VPSS0_SMMU_MASTER_DBG8.u32 = VPSS_RegRead((&(pstReg->VPSS0_SMMU_MASTER_DBG8.u32) + layer * MMU_OFFSET));
    VPSS0_SMMU_MASTER_DBG8.bits.sel2_chn_wr = sel2_chn_wr;
    VPSS_RegWrite((&(pstReg->VPSS0_SMMU_MASTER_DBG8.u32) + layer * MMU_OFFSET), VPSS0_SMMU_MASTER_DBG8.u32);

    return ;
}


HI_U32 VPSS_MMU_GetIntsStat(S_VPSS_REGS_TYPE *pVpssReg, HI_U32 layer)
{
    U_VPSS0_SMMU_INTSTAT_S VPSS0_SMMU_INTSTAT_S;

    VPSS0_SMMU_INTSTAT_S.u32 = VPSS_RegRead((&(pVpssReg ->VPSS0_SMMU_INTSTAT_S.u32) + layer * MMU_OFFSET));
    return VPSS0_SMMU_INTSTAT_S.u32;
}

HI_VOID VPSS_MMU_SetIntsClr(S_VPSS_REGS_TYPE *pVpssReg, HI_U32 layer, HI_U32 ints_clr)
{
    U_VPSS0_SMMU_INTCLR_S VPSS0_SMMU_INTCLR_S;

    VPSS0_SMMU_INTCLR_S.u32 = ints_clr;
    VPSS_RegWrite((&(pVpssReg ->VPSS0_SMMU_INTCLR_S.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_S.u32);

    return ;
}

HI_U32 VPSS_MMU_GetIntnsStat(S_VPSS_REGS_TYPE *pVpssReg, HI_U32 layer)
{
    U_VPSS0_SMMU_INTSTAT_NS VPSS0_SMMU_INTSTAT_NS;

    VPSS0_SMMU_INTSTAT_NS.u32 = VPSS_RegRead((&(pVpssReg ->VPSS0_SMMU_INTSTAT_NS.u32) + layer * MMU_OFFSET));
    return VPSS0_SMMU_INTSTAT_NS.u32;
}

HI_VOID VPSS_MMU_SetIntnsClr(S_VPSS_REGS_TYPE *pVpssReg, HI_U32 layer, HI_U32 intns_clr)
{
    U_VPSS0_SMMU_INTCLR_NS VPSS0_SMMU_INTCLR_NS;

    VPSS0_SMMU_INTCLR_NS.u32 = intns_clr;
    VPSS_RegWrite((&(pVpssReg ->VPSS0_SMMU_INTCLR_NS.u32) + layer * MMU_OFFSET), VPSS0_SMMU_INTCLR_NS.u32);

    return ;
}
