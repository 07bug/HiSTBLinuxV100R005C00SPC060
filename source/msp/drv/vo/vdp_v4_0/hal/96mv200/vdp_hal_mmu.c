#include "vdp_hal_comm.h"
#include "vdp_hal_mmu.h"

#include "vdp_drv_func.h"
extern S_VDP_REGS_TYPE *pVdpReg;

HI_VOID VDP_VID_SetAllRegionSmmuBypassDisable (HI_U32 u32Data, HI_U32 u32Bypass)
{
    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_SetAllRegionSmmuBypassDisable() Select Wrong Video Layer ID\n");
        return ;
    }

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS0.u32) + u32Data * VID_OFFSET), u32Bypass);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS1.u32) + u32Data * VID_OFFSET), u32Bypass);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS2.u32) + u32Data * VID_OFFSET), u32Bypass);
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS3.u32) + u32Data * VID_OFFSET), u32Bypass);

    return ;
}


HI_VOID VDP_VID_Set16RegionSmmuLumBypass (HI_U32 u32Data, HI_U32 u32Num, HI_U32 u32Bypass)
{
    U_V0_SMMU_BYPASS0 V0_SMMU_BYPASS0;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_Set16RegionSmmuLumBypass() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Num >= VID_REGION_NUM)
    {
        VDP_PRINT("Error,VDP_VID_Set16RegionSmmuLumBypass() Select Wrong region ID\n");
        return ;
    }

    if (u32Num < 16)
    {
        u32Num = u32Num * 2;
        V0_SMMU_BYPASS0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS0.u32) + u32Data * VID_OFFSET));
        if (u32Bypass)
        {
            V0_SMMU_BYPASS0.u32 = (1 << u32Num) | V0_SMMU_BYPASS0.u32;
        }
        else
        {
            V0_SMMU_BYPASS0.u32 = (~(1 << u32Num)) & V0_SMMU_BYPASS0.u32;
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS0.u32) + u32Data * VID_OFFSET), V0_SMMU_BYPASS0.u32);
    }
    else if (u32Num < 32)
    {
        u32Num = (u32Num - 16) * 2;
        V0_SMMU_BYPASS0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS1.u32) + u32Data * VID_OFFSET));
        if (u32Bypass)
        {
            V0_SMMU_BYPASS0.u32 = (1 << u32Num) | V0_SMMU_BYPASS0.u32;
        }
        else
        {
            V0_SMMU_BYPASS0.u32 = (~(1 << u32Num)) & V0_SMMU_BYPASS0.u32;
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS1.u32) + u32Data * VID_OFFSET), V0_SMMU_BYPASS0.u32);
    }
    else if (u32Num < 48)
    {
        u32Num = (u32Num - 32) * 2;
        V0_SMMU_BYPASS0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS2.u32) + u32Data * VID_OFFSET));
        if (u32Bypass)
        {
            V0_SMMU_BYPASS0.u32 = (1 << u32Num) | V0_SMMU_BYPASS0.u32;
        }
        else
        {
            V0_SMMU_BYPASS0.u32 = (~(1 << u32Num)) & V0_SMMU_BYPASS0.u32;
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS2.u32) + u32Data * VID_OFFSET), V0_SMMU_BYPASS0.u32);
    }
    else if (u32Num < 64)
    {
        u32Num = (u32Num - 48) * 2;
        V0_SMMU_BYPASS0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS3.u32) + u32Data * VID_OFFSET));
        if (u32Bypass)
        {
            V0_SMMU_BYPASS0.u32 = (1 << u32Num) | V0_SMMU_BYPASS0.u32;
        }
        else
        {
            V0_SMMU_BYPASS0.u32 = (~(1 << u32Num)) & V0_SMMU_BYPASS0.u32;
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS3.u32) + u32Data * VID_OFFSET), V0_SMMU_BYPASS0.u32);
    }

    return ;
}



HI_VOID VDP_VID_Set16RegionSmmuChromBypass (HI_U32 u32Data, HI_U32 u32Num, HI_U32 u32Bypass)
{
    U_V0_SMMU_BYPASS0 V0_SMMU_BYPASS0;

    if (u32Data >= VID_MAX)
    {
        VDP_PRINT("Error,VDP_VID_Set16RegionSmmuChromBypass() Select Wrong Video Layer ID\n");
        return ;
    }

    if (u32Num >= VID_REGION_NUM)
    {
        VDP_PRINT("Error,VDP_VID_Set16RegionSmmuChromBypass() Select Wrong region ID\n");
        return ;
    }

    if (u32Num < 16)
    {
        u32Num = u32Num * 2 + 1;
        V0_SMMU_BYPASS0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS0.u32) + u32Data * VID_OFFSET));
        if (u32Bypass)
        {
            V0_SMMU_BYPASS0.u32 = (1 << u32Num) | V0_SMMU_BYPASS0.u32;
        }
        else
        {
            V0_SMMU_BYPASS0.u32 = (~(1 << u32Num)) & V0_SMMU_BYPASS0.u32;
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS0.u32) + u32Data * VID_OFFSET), V0_SMMU_BYPASS0.u32);
    }
    else if (u32Num < 32)
    {
        u32Num = (u32Num - 16) * 2 + 1;
        V0_SMMU_BYPASS0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS1.u32) + u32Data * VID_OFFSET));
        if (u32Bypass)
        {
            V0_SMMU_BYPASS0.u32 = (1 << u32Num) | V0_SMMU_BYPASS0.u32;
        }
        else
        {
            V0_SMMU_BYPASS0.u32 = (~(1 << u32Num)) & V0_SMMU_BYPASS0.u32;
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS1.u32) + u32Data * VID_OFFSET), V0_SMMU_BYPASS0.u32);
    }
    else if (u32Num < 48)
    {
        u32Num = (u32Num - 32) * 2 + 1;
        V0_SMMU_BYPASS0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS2.u32) + u32Data * VID_OFFSET));
        if (u32Bypass)
        {
            V0_SMMU_BYPASS0.u32 = (1 << u32Num) | V0_SMMU_BYPASS0.u32;
        }
        else
        {
            V0_SMMU_BYPASS0.u32 = (~(1 << u32Num)) & V0_SMMU_BYPASS0.u32;
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS2.u32) + u32Data * VID_OFFSET), V0_SMMU_BYPASS0.u32);
    }
    else if (u32Num < 64)
    {
        u32Num = (u32Num - 48) * 2 + 1;
        V0_SMMU_BYPASS0.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS3.u32) + u32Data * VID_OFFSET));
        if (u32Bypass)
        {
            V0_SMMU_BYPASS0.u32 = (1 << u32Num) | V0_SMMU_BYPASS0.u32;
        }
        else
        {
            V0_SMMU_BYPASS0.u32 = (~(1 << u32Num)) & V0_SMMU_BYPASS0.u32;
        }

        VDP_RegWrite(((HI_ULONG) & (pVdpReg->V0_SMMU_BYPASS3.u32) + u32Data * VID_OFFSET), V0_SMMU_BYPASS0.u32);
    }

    return ;
}

//WBC_DHD0
HI_VOID VDP_WBC_SetSmmuCBypass (HI_U32 u32Data, HI_U32 u32Bypass)
{
    U_WBC_DHD0_SMMU_BYPASS WBC_DHD0_SMMU_BYPASS;

    if (u32Data >= WBC_MAX)
    {
        VDP_PRINT("Error, VDP_WBC_SetSmmuCBypass Select Wrong Layer ID\n");
    }

    if (u32Data == VDP_LAYER_WBC_HD0 || u32Data == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_SMMU_BYPASS.u32 = VDP_RegRead((((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32)) + u32Data * WBC_OFFSET));
        WBC_DHD0_SMMU_BYPASS.bits.c_bypass = u32Bypass;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32)) + u32Data * WBC_OFFSET), WBC_DHD0_SMMU_BYPASS.u32);
    }
    else;

    return;
}


HI_VOID VDP_WBC_SetSmmuLBypass (HI_U32 u32Data, HI_U32 u32Bypass)
{
    U_WBC_DHD0_SMMU_BYPASS WBC_DHD0_SMMU_BYPASS;

    if (u32Data >= WBC_MAX)
    {
        VDP_PRINT("Error, VDP_WBC_SetSmmuLBypass Select Wrong Layer ID\n");
    }

    //if(u32Data == VDP_LAYER_WBC_HD0 || u32Data == VDP_LAYER_WBC_VP0)
    {
        WBC_DHD0_SMMU_BYPASS.u32 = VDP_RegRead((((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32)) + u32Data * WBC_OFFSET));
        WBC_DHD0_SMMU_BYPASS.bits.l_bypass = u32Bypass;
        VDP_RegWrite((((HI_ULONG) & (pVdpReg->WBC_DHD0_SMMU_BYPASS.u32)) + u32Data * WBC_OFFSET), WBC_DHD0_SMMU_BYPASS.u32);
    }
    //else;

    return;
}


HI_VOID VDP_SMMU_SetPtwPf (HI_U32 u32ptw_pf)
{
    U_SMMU_SCR SMMU_SCR;

    SMMU_SCR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_SCR.u32)));
    SMMU_SCR.bits.ptw_pf = u32ptw_pf;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_SCR.u32)), SMMU_SCR.u32);

    return ;
}


HI_VOID VDP_SMMU_SetIntEn (HI_U32 u32Enable)
{
    U_SMMU_SCR SMMU_SCR;

    SMMU_SCR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_SCR.u32)));
    SMMU_SCR.bits.int_en = u32Enable;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_SCR.u32)), SMMU_SCR.u32);

    return ;
}


HI_VOID VDP_SMMU_SetGlbBypass(HI_U32 u32GlbBypass)
{
    U_SMMU_SCR SMMU_SCR;

    SMMU_SCR.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_SCR.u32)));
    SMMU_SCR.bits.glb_bypass = u32GlbBypass;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_SCR.u32)), SMMU_SCR.u32);

    return ;
}

HI_VOID VDP_SMMU_SetIntsTlbinvalidRdMsk(HI_U32 u32Msk)
{
    U_SMMU_INTMASK_S SMMU_INTMASK_S;

    SMMU_INTMASK_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_S.u32)));
    SMMU_INTMASK_S.bits.ints_tlbinvalid_rd_msk = u32Msk;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_S.u32)), SMMU_INTMASK_S.u32);

    return ;
}

HI_VOID VDP_SMMU_SetIntsTlbinvalidWrMsk(HI_U32 u32Msk)
{
    U_SMMU_INTMASK_S SMMU_INTMASK_S;

    SMMU_INTMASK_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_S.u32)));
    SMMU_INTMASK_S.bits.ints_tlbinvalid_wr_msk = u32Msk;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_S.u32)), SMMU_INTMASK_S.u32);

    return ;
}

HI_VOID VDP_SMMU_SetIntsPtwTransMsk(HI_U32 u32Msk)
{
    U_SMMU_INTMASK_S SMMU_INTMASK_S;

    SMMU_INTMASK_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_S.u32)));
    SMMU_INTMASK_S.bits.ints_ptw_trans_msk = u32Msk;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_S.u32)), SMMU_INTMASK_S.u32);

    return ;
}


HI_VOID VDP_SMMU_SetIntsTlbmissMsk(HI_U32 u32Msk)
{
    U_SMMU_INTMASK_S SMMU_INTMASK_S;

    SMMU_INTMASK_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_S.u32)));
    SMMU_INTMASK_S.bits.ints_tlbmiss_msk = u32Msk;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_S.u32)), SMMU_INTMASK_S.u32);

    return ;
}


HI_VOID VDP_SMMU_SetIntsTlbinvalidRdClr(HI_U32 u32Clear)
{
    U_SMMU_INTCLR_S SMMU_INTCLR_S;

    SMMU_INTCLR_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_S.u32)));
    SMMU_INTCLR_S.bits.ints_tlbinvalid_rd_clr = u32Clear;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_S.u32)), SMMU_INTCLR_S.u32);

    return ;
}

HI_VOID VDP_SMMU_SetIntsTlbinvalidWrClr(HI_U32 u32Clear)
{
    U_SMMU_INTCLR_S SMMU_INTCLR_S;

    SMMU_INTCLR_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_S.u32)));
    SMMU_INTCLR_S.bits.ints_tlbinvalid_wr_clr = u32Clear;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_S.u32)), SMMU_INTCLR_S.u32);

    return ;
}

HI_VOID VDP_SMMU_SetIntsPtwTransClr(HI_U32 u32Clear)
{
    U_SMMU_INTCLR_S SMMU_INTCLR_S;

    SMMU_INTCLR_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_S.u32)));
    SMMU_INTCLR_S.bits.ints_ptw_trans_clr = u32Clear;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_S.u32)), SMMU_INTCLR_S.u32);

    return ;
}


HI_VOID VDP_SMMU_SetIntsTlbmissClr(HI_U32 u32Clear)
{
    U_SMMU_INTCLR_S SMMU_INTCLR_S;

    SMMU_INTCLR_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_S.u32)));
    SMMU_INTCLR_S.bits.ints_tlbmiss_clr = u32Clear;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_S.u32)), SMMU_INTCLR_S.u32);

    return ;
}


HI_VOID VDP_SMMU_SetIntnsTlbinvalidRdMsk(HI_U32 u32Msk)
{
    U_SMMU_INTMASK_NS SMMU_INTMASK_NS;

    SMMU_INTMASK_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_NS.u32)));
    SMMU_INTMASK_NS.bits.intns_tlbinvalid_rd_msk = u32Msk;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_NS.u32)), SMMU_INTMASK_NS.u32);

    return ;
}

HI_VOID VDP_SMMU_SetIntnsTlbinvalidWrMsk(HI_U32 u32Msk)
{
    U_SMMU_INTMASK_NS SMMU_INTMASK_NS;

    SMMU_INTMASK_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_NS.u32)));
    SMMU_INTMASK_NS.bits.intns_tlbinvalid_wr_msk = u32Msk;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_NS.u32)), SMMU_INTMASK_NS.u32);

    return ;
}

HI_VOID VDP_SMMU_SetIntnsPtwTransMsk(HI_U32 u32Msk)
{
    U_SMMU_INTMASK_NS SMMU_INTMASK_NS;

    SMMU_INTMASK_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_NS.u32)));
    SMMU_INTMASK_NS.bits.intns_ptw_trans_msk = u32Msk;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_NS.u32)), SMMU_INTMASK_NS.u32);

    return ;
}


HI_VOID VDP_SMMU_SetIntnsTlbmissMsk(HI_U32 u32Msk)
{
    U_SMMU_INTMASK_NS SMMU_INTMASK_NS;

    SMMU_INTMASK_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_NS.u32)));
    SMMU_INTMASK_NS.bits.intns_tlbmiss_msk = u32Msk;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTMASK_NS.u32)), SMMU_INTMASK_NS.u32);

    return ;
}



HI_VOID VDP_SMMU_SetIntnsTlbinvalidRdClr(HI_U32 u32Clear)
{
    U_SMMU_INTCLR_NS SMMU_INTCLR_NS;

    SMMU_INTCLR_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_NS.u32)));
    SMMU_INTCLR_NS.bits.intns_tlbinvalid_rd_clr = u32Clear;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_NS.u32)), SMMU_INTCLR_NS.u32);

    return ;
}

HI_VOID VDP_SMMU_SetIntnsTlbinvalidWrClr(HI_U32 u32Clear)
{
    U_SMMU_INTCLR_NS SMMU_INTCLR_NS;

    SMMU_INTCLR_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_NS.u32)));
    SMMU_INTCLR_NS.bits.intns_tlbinvalid_wr_clr = u32Clear;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_NS.u32)), SMMU_INTCLR_NS.u32);

    return ;
}

HI_VOID VDP_SMMU_SetIntnsPtwTransClr(HI_U32 u32Clear)
{
    U_SMMU_INTCLR_NS SMMU_INTCLR_NS;

    SMMU_INTCLR_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_NS.u32)));
    SMMU_INTCLR_NS.bits.intns_ptw_trans_clr = u32Clear;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_NS.u32)), SMMU_INTCLR_NS.u32);

    return ;
}


HI_VOID VDP_SMMU_SetIntnsTlbmissClr(HI_U32 u32Clear)
{
    U_SMMU_INTCLR_NS SMMU_INTCLR_NS;

    SMMU_INTCLR_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_NS.u32)));
    SMMU_INTCLR_NS.bits.intns_tlbmiss_clr = u32Clear;
    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_INTCLR_NS.u32)), SMMU_INTCLR_NS.u32);

    return ;
}


HI_VOID VDP_SMMU_SetCbTtbr(HI_U32 u32cb_ttbr)
{

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_CB_TTBR.u32)), u32cb_ttbr);

    return ;
}


HI_VOID VDP_SMMU_SetErrRdAddr(HI_U32 u32Addr)
{

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_ERR_RDADDR_S.u32)), u32Addr);

    return ;
}


HI_VOID VDP_SMMU_SetErrWrAddr(HI_U32 u32Addr)
{

    VDP_RegWrite(((HI_ULONG) & (pVdpReg->SMMU_ERR_WRADDR_S.u32)), u32Addr);

    return ;
}

HI_U32 VDP_SMMU_GetRdErrAddr(HI_VOID)
{
    return VDP_RegRead((HI_ULONG) & (pVdpReg->SMMU_FAULT_ADDR_RD_NS.u32));
}
HI_U32 VDP_SMMU_GetWrErrAddr(HI_VOID)
{
    return  VDP_RegRead((HI_ULONG) & (pVdpReg->SMMU_FAULT_ADDR_WR_NS.u32));
}
HI_U32 VDP_SMMU_GetSecureRdErrAddr(HI_VOID)
{
    return VDP_RegRead((HI_ULONG) & (pVdpReg->SMMU_FAULT_ADDR_RD_S.u32));
}
HI_U32 VDP_SMMU_GetSecureWrErrAddr(HI_VOID)
{
    return VDP_RegRead((HI_ULONG) & (pVdpReg->SMMU_FAULT_ADDR_WR_S.u32));
}

HI_U32 VDP_SMMU_GetIntsTlbinvalidRdSta(HI_VOID)
{
    U_SMMU_INTSTAT_S SMMU_INTSTAT_S;
    SMMU_INTSTAT_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTSTAT_S.u32)));
    return SMMU_INTSTAT_S.bits.ints_tlbinvalid_rd_stat;
}

HI_U32 VDP_SMMU_GetIntsTlbinvalidWrSta(HI_VOID)
{
    U_SMMU_INTSTAT_S SMMU_INTSTAT_S;
    SMMU_INTSTAT_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTSTAT_S.u32)));
    return SMMU_INTSTAT_S.bits.ints_tlbinvalid_wr_stat;
}

HI_U32 VDP_SMMU_GetIntsPtwTransSta(HI_VOID)
{
    U_SMMU_INTSTAT_S SMMU_INTSTAT_S;
    SMMU_INTSTAT_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTSTAT_S.u32)));

    return SMMU_INTSTAT_S.bits.ints_ptw_trans_stat;
}

HI_U32 VDP_SMMU_GetIntsTlbmissSta(HI_VOID)
{
    U_SMMU_INTSTAT_S SMMU_INTSTAT_S;
    SMMU_INTSTAT_S.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTSTAT_S.u32)));

    return SMMU_INTSTAT_S.bits.ints_tlbmiss_stat;
}


HI_U32 VDP_SMMU_GetIntnsTlbinvalidRdSta(HI_VOID)
{
    U_SMMU_INTSTAT_NS SMMU_INTSTAT_NS;
    SMMU_INTSTAT_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTSTAT_NS.u32)));

    return SMMU_INTSTAT_NS.bits.intns_tlbinvalid_rd_stat;
}

HI_U32 VDP_SMMU_GetIntnsTlbinvalidWrSta(HI_VOID)
{
    U_SMMU_INTSTAT_NS SMMU_INTSTAT_NS;
    SMMU_INTSTAT_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTSTAT_NS.u32)));

    return SMMU_INTSTAT_NS.bits.intns_tlbinvalid_wr_stat;
}

HI_U32 VDP_SMMU_GetIntnsPtwTransSta( HI_VOID)
{
    U_SMMU_INTSTAT_NS SMMU_INTSTAT_NS;
    SMMU_INTSTAT_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTSTAT_NS.u32)));

    return SMMU_INTSTAT_NS.bits.intns_ptw_trans_stat;
}


HI_U32 VDP_SMMU_GetIntnsTlbmissSta(HI_VOID)
{
    U_SMMU_INTSTAT_NS SMMU_INTSTAT_NS;
    SMMU_INTSTAT_NS.u32 = VDP_RegRead(((HI_ULONG) & (pVdpReg->SMMU_INTSTAT_NS.u32)));

    return SMMU_INTSTAT_NS.bits.intns_tlbmiss_stat;
}


