#if 1
#include "vpss_hal_ip_master.h"
#include "vpss_hal_comm.h"
#include "vpss_cbb_reg.h"

HI_VOID VPSS_MASTER_SetMstr2Woutstanding(S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr2_woutstanding)
{
    U_VPSS_MST_OUTSTANDING VPSS_MST_OUTSTANDING;

    VPSS_MST_OUTSTANDING.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_OUTSTANDING.u32)));
    VPSS_MST_OUTSTANDING.bits.mstr2_woutstanding = mstr2_woutstanding;
    VPSS_RegWrite((&(pstReg->VPSS_MST_OUTSTANDING.u32)), VPSS_MST_OUTSTANDING.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMstr2Routstanding(S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr2_routstanding)
{
    U_VPSS_MST_OUTSTANDING VPSS_MST_OUTSTANDING;

    VPSS_MST_OUTSTANDING.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_OUTSTANDING.u32)));
    VPSS_MST_OUTSTANDING.bits.mstr2_routstanding = mstr2_routstanding;
    VPSS_RegWrite((&(pstReg->VPSS_MST_OUTSTANDING.u32)), VPSS_MST_OUTSTANDING.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMstr1Woutstanding(S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr1_woutstanding)
{
    U_VPSS_MST_OUTSTANDING VPSS_MST_OUTSTANDING;

    VPSS_MST_OUTSTANDING.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_OUTSTANDING.u32)));
    VPSS_MST_OUTSTANDING.bits.mstr1_woutstanding = mstr1_woutstanding;
    VPSS_RegWrite((&(pstReg->VPSS_MST_OUTSTANDING.u32)), VPSS_MST_OUTSTANDING.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMstr1Routstanding(S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr1_routstanding)
{
    U_VPSS_MST_OUTSTANDING VPSS_MST_OUTSTANDING;

    VPSS_MST_OUTSTANDING.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_OUTSTANDING.u32)));
    VPSS_MST_OUTSTANDING.bits.mstr1_routstanding = mstr1_routstanding;
    VPSS_RegWrite((&(pstReg->VPSS_MST_OUTSTANDING.u32)), VPSS_MST_OUTSTANDING.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMstr0Woutstanding(S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr0_woutstanding)
{
    U_VPSS_MST_OUTSTANDING VPSS_MST_OUTSTANDING;

    VPSS_MST_OUTSTANDING.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_OUTSTANDING.u32)));
    VPSS_MST_OUTSTANDING.bits.mstr0_woutstanding = mstr0_woutstanding;
    VPSS_RegWrite((&(pstReg->VPSS_MST_OUTSTANDING.u32)), VPSS_MST_OUTSTANDING.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMstr0Routstanding(S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr0_routstanding)
{
    U_VPSS_MST_OUTSTANDING VPSS_MST_OUTSTANDING;

    VPSS_MST_OUTSTANDING.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_OUTSTANDING.u32)));
    VPSS_MST_OUTSTANDING.bits.mstr0_routstanding = mstr0_routstanding;
    VPSS_RegWrite((&(pstReg->VPSS_MST_OUTSTANDING.u32)), VPSS_MST_OUTSTANDING.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMidEnable(S_VPSS_REGS_TYPE *pstReg, HI_U32 mid_enable)
{
    U_VPSS_MST_CTRL VPSS_MST_CTRL;

    VPSS_MST_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_CTRL.u32)));
    VPSS_MST_CTRL.bits.mid_enable = mid_enable;
    VPSS_RegWrite((&(pstReg->VPSS_MST_CTRL.u32)), VPSS_MST_CTRL.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetArbMode(S_VPSS_REGS_TYPE *pstReg, HI_U32 arb_mode)
{
    U_VPSS_MST_CTRL VPSS_MST_CTRL;

    VPSS_MST_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_CTRL.u32)));
    VPSS_MST_CTRL.bits.arb_mode = arb_mode;
    VPSS_RegWrite((&(pstReg->VPSS_MST_CTRL.u32)), VPSS_MST_CTRL.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetSplitMode(S_VPSS_REGS_TYPE *pstReg, HI_U32 split_mode)
{
    U_VPSS_MST_CTRL VPSS_MST_CTRL;

    VPSS_MST_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_CTRL.u32)));
    VPSS_MST_CTRL.bits.split_mode = split_mode;
    VPSS_RegWrite((&(pstReg->VPSS_MST_CTRL.u32)), VPSS_MST_CTRL.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetRchnPrio(S_VPSS_REGS_TYPE *pstReg, HI_U32 id, HI_U32 prio)
{
    HI_U32 u32Prio = prio & 0x1;
    HI_U32 u32RchnPrio = 0;

    if (id < 32)
    {
        u32RchnPrio = VPSS_RegRead((&(pstReg->VPSS_MST_RCHN_PRIO0.u32)));
        u32RchnPrio &= (~(0x1 << id));
        u32RchnPrio |= (u32Prio << id);
        VPSS_RegWrite((&(pstReg->VPSS_MST_RCHN_PRIO0.u32)), u32RchnPrio);
    }
    //else
    //{
    //  u32RchnPrio = VPSS_RegRead((&(pstReg->VPSS_MST_RCHN_PRIO1.u32)));
    //  u32RchnPrio &= (~(0x1 << (id-32)));
    //  u32RchnPrio |= (u32Prio << (id-32));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_RCHN_PRIO1.u32)),u32RchnPrio);
    //}

    return ;
}


HI_VOID VPSS_MASTER_SetWchnPrio(S_VPSS_REGS_TYPE *pstReg, HI_U32 id, HI_U32 prio)
{
    HI_U32 u32Prio = prio & 0x1;
    HI_U32 u32WchnPrio = 0;

    if (id < 32)
    {
        u32WchnPrio = VPSS_RegRead((&(pstReg->VPSS_MST_WCHN_PRIO0.u32)));
        u32WchnPrio &= (~(0x1 << id));
        u32WchnPrio |= (u32Prio << id);
        VPSS_RegWrite((&(pstReg->VPSS_MST_WCHN_PRIO0.u32)), u32WchnPrio);
    }
    //else
    //{
    //  u32WchnPrio = VPSS_RegRead((&(pstReg->VPSS_MST_WCHN_PRIO1.u32)));
    //  u32WchnPrio &= (~(0x1 << (id-32)));
    //  u32WchnPrio |= (u32Prio << (id-32));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_WCHN_PRIO1.u32)),u32WchnPrio);
    //}

    return ;
}


HI_VOID VPSS_MASTER_SetRchnSel(S_VPSS_REGS_TYPE *pstReg, HI_U32 id, HI_U32 sel)
{
    //HI_U32 u32Sel = sel & 0x3;
    //HI_U32 u32RchnSel = 0;
    //
    //if(id<16)
    //{
    //  u32RchnSel = VPSS_RegRead((&(pstReg->VPSS_MST_RCHN_SEL0.u32)));
    //  u32RchnSel &= (~(0x3 << (id*2)));
    //  u32RchnSel |= (u32Sel << (id*2));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_RCHN_SEL0.u32)),u32RchnSel);
    //}
    //else if(id<32)
    //{
    //  u32RchnSel = VPSS_RegRead((&(pstReg->VPSS_MST_RCHN_SEL1.u32)));
    //  u32RchnSel &= (~(0x3 << ((id-16)*2)));
    //  u32RchnSel |= (u32Sel << ((id-16)*2));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_RCHN_SEL1.u32)),u32RchnSel);
    //}
    //else if(id<48)
    //{
    //  u32RchnSel = VPSS_RegRead((&(pstReg->VPSS_MST_RCHN_SEL2.u32)));
    //  u32RchnSel &= (~(0x3 << ((id-32)*2)));
    //  u32RchnSel |= (u32Sel << ((id-32)*2));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_RCHN_SEL2.u32)),u32RchnSel);
    //}
    //else
    //{
    //  u32RchnSel = VPSS_RegRead((&(pstReg->VPSS_MST_RCHN_SEL3.u32)));
    //  u32RchnSel &= (~(0x3 << ((id-48)*2)));
    //  u32RchnSel |= (u32Sel << ((id-48)*2));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_RCHN_SEL3.u32)),u32RchnSel);
    //}

    return ;
}


HI_VOID VPSS_MASTER_SetWchnSel(S_VPSS_REGS_TYPE *pstReg, HI_U32 id, HI_U32 sel)
{
    //HI_U32 u32Sel = sel & 0x3;
    //HI_U32 u32WchnSel = 0;
    //
    //if(id<16)
    //{
    //  u32WchnSel = VPSS_RegRead((&(pstReg->VPSS_MST_WCHN_SEL0.u32)));
    //  u32WchnSel &= (~(0x3 << (id*2)));
    //  u32WchnSel |= (u32Sel << (id*2));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_WCHN_SEL0.u32)),u32WchnSel);
    //}
    //else if(id<32)
    //{
    //  u32WchnSel = VPSS_RegRead((&(pstReg->VPSS_MST_WCHN_SEL1.u32)));
    //  u32WchnSel &= (~(0x3 << ((id-16)*2)));
    //  u32WchnSel |= (u32Sel << ((id-16)*2));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_WCHN_SEL1.u32)),u32WchnSel);
    //}
    //else if(id<48)
    //{
    //  u32WchnSel = VPSS_RegRead((&(pstReg->VPSS_MST_WCHN_SEL2.u32)));
    //  u32WchnSel &= (~(0x3 << ((id-32)*2)));
    //  u32WchnSel |= (u32Sel << ((id-32)*2));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_WCHN_SEL2.u32)),u32WchnSel);
    //}
    //else
    //{
    //  u32WchnSel = VPSS_RegRead((&(pstReg->VPSS_MST_WCHN_SEL3.u32)));
    //  u32WchnSel &= (~(0x3 << ((id-48)*2)));
    //  u32WchnSel |= (u32Sel << ((id-48)*2));
    //  VPSS_RegWrite((&(pstReg->VPSS_MST_WCHN_SEL3.u32)),u32WchnSel);
    //}

    return ;
}


HI_VOID VPSS_MASTER_SetBusErrorClr(S_VPSS_REGS_TYPE *pstReg, HI_U32 bus_error_clr)
{
    U_VPSS_MST_BUS_ERR_CLR VPSS_MST_BUS_ERR_CLR;

    VPSS_MST_BUS_ERR_CLR.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_BUS_ERR_CLR.u32)));
    VPSS_MST_BUS_ERR_CLR.bits.bus_error_clr = bus_error_clr;
    VPSS_RegWrite((&(pstReg->VPSS_MST_BUS_ERR_CLR.u32)), VPSS_MST_BUS_ERR_CLR.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMst2WError(S_VPSS_REGS_TYPE *pstReg, HI_U32 mst2_w_error)
{
    U_VPSS_MST_BUS_ERR VPSS_MST_BUS_ERR;

    VPSS_MST_BUS_ERR.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_BUS_ERR.u32)));
    VPSS_MST_BUS_ERR.bits.mst2_w_error = mst2_w_error;
    VPSS_RegWrite((&(pstReg->VPSS_MST_BUS_ERR.u32)), VPSS_MST_BUS_ERR.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMst2RError(S_VPSS_REGS_TYPE *pstReg, HI_U32 mst2_r_error)
{
    U_VPSS_MST_BUS_ERR VPSS_MST_BUS_ERR;

    VPSS_MST_BUS_ERR.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_BUS_ERR.u32)));
    VPSS_MST_BUS_ERR.bits.mst2_r_error = mst2_r_error;
    VPSS_RegWrite((&(pstReg->VPSS_MST_BUS_ERR.u32)), VPSS_MST_BUS_ERR.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMst1WError(S_VPSS_REGS_TYPE *pstReg, HI_U32 mst1_w_error)
{
    U_VPSS_MST_BUS_ERR VPSS_MST_BUS_ERR;

    VPSS_MST_BUS_ERR.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_BUS_ERR.u32)));
    VPSS_MST_BUS_ERR.bits.mst1_w_error = mst1_w_error;
    VPSS_RegWrite((&(pstReg->VPSS_MST_BUS_ERR.u32)), VPSS_MST_BUS_ERR.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMst1RError(S_VPSS_REGS_TYPE *pstReg, HI_U32 mst1_r_error)
{
    U_VPSS_MST_BUS_ERR VPSS_MST_BUS_ERR;

    VPSS_MST_BUS_ERR.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_BUS_ERR.u32)));
    VPSS_MST_BUS_ERR.bits.mst1_r_error = mst1_r_error;
    VPSS_RegWrite((&(pstReg->VPSS_MST_BUS_ERR.u32)), VPSS_MST_BUS_ERR.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMst0WError(S_VPSS_REGS_TYPE *pstReg, HI_U32 mst0_w_error)
{
    U_VPSS_MST_BUS_ERR VPSS_MST_BUS_ERR;

    VPSS_MST_BUS_ERR.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_BUS_ERR.u32)));
    VPSS_MST_BUS_ERR.bits.mst0_w_error = mst0_w_error;
    VPSS_RegWrite((&(pstReg->VPSS_MST_BUS_ERR.u32)), VPSS_MST_BUS_ERR.u32);

    return ;
}


HI_VOID VPSS_MASTER_SetMst0RError(S_VPSS_REGS_TYPE *pstReg, HI_U32 mst0_r_error)
{
    U_VPSS_MST_BUS_ERR VPSS_MST_BUS_ERR;

    VPSS_MST_BUS_ERR.u32 = VPSS_RegRead((&(pstReg->VPSS_MST_BUS_ERR.u32)));
    VPSS_MST_BUS_ERR.bits.mst0_r_error = mst0_r_error;
    VPSS_RegWrite((&(pstReg->VPSS_MST_BUS_ERR.u32)), VPSS_MST_BUS_ERR.u32);

    return ;
}
#endif
