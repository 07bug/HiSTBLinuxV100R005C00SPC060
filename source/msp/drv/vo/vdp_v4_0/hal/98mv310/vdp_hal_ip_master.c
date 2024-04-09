#include "vdp_hal_ip_master.h"
#include "vdp_hal_comm.h"


extern S_VDP_REGS_TYPE *pVdpReg;
HI_VOID VDP_MASTER_SetMstr2Woutstanding( HI_U32 mstr2_woutstanding)
{
	U_VDP_MST_OUTSTANDING VDP_MST_OUTSTANDING;

	VDP_MST_OUTSTANDING.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)));
	VDP_MST_OUTSTANDING.bits.mstr2_woutstanding = mstr2_woutstanding;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)),VDP_MST_OUTSTANDING.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMstr2Routstanding( HI_U32 mstr2_routstanding)
{
	U_VDP_MST_OUTSTANDING VDP_MST_OUTSTANDING;

	VDP_MST_OUTSTANDING.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)));
	VDP_MST_OUTSTANDING.bits.mstr2_routstanding = mstr2_routstanding;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)),VDP_MST_OUTSTANDING.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMstr1Woutstanding( HI_U32 mstr1_woutstanding)
{
	U_VDP_MST_OUTSTANDING VDP_MST_OUTSTANDING;

	VDP_MST_OUTSTANDING.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)));
	VDP_MST_OUTSTANDING.bits.mstr1_woutstanding = mstr1_woutstanding;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)),VDP_MST_OUTSTANDING.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMstr1Routstanding( HI_U32 mstr1_routstanding)
{
	U_VDP_MST_OUTSTANDING VDP_MST_OUTSTANDING;

	VDP_MST_OUTSTANDING.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)));
	VDP_MST_OUTSTANDING.bits.mstr1_routstanding = mstr1_routstanding;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)),VDP_MST_OUTSTANDING.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMstr0Woutstanding( HI_U32 mstr0_woutstanding)
{
	U_VDP_MST_OUTSTANDING VDP_MST_OUTSTANDING;

	VDP_MST_OUTSTANDING.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)));
	VDP_MST_OUTSTANDING.bits.mstr0_woutstanding = mstr0_woutstanding;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)),VDP_MST_OUTSTANDING.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMstr0Routstanding( HI_U32 mstr0_routstanding)
{
	U_VDP_MST_OUTSTANDING VDP_MST_OUTSTANDING;

	VDP_MST_OUTSTANDING.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)));
	VDP_MST_OUTSTANDING.bits.mstr0_routstanding = mstr0_routstanding;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_OUTSTANDING.u32)),VDP_MST_OUTSTANDING.u32);

	return ;
}


HI_VOID VDP_MASTER_SetWportSel( HI_U32 wport_sel)
{
	U_VDP_MST_CTRL VDP_MST_CTRL;

	VDP_MST_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_CTRL.u32)));
	VDP_MST_CTRL.bits.wport_sel = wport_sel;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_CTRL.u32)),VDP_MST_CTRL.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMidEnable( HI_U32 mid_enable)
{
	U_VDP_MST_CTRL VDP_MST_CTRL;

	VDP_MST_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_CTRL.u32)));
	VDP_MST_CTRL.bits.mid_enable = mid_enable;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_CTRL.u32)),VDP_MST_CTRL.u32);

	return ;
}


HI_VOID VDP_MASTER_SetArbMode( HI_U32 arb_mode)
{
	U_VDP_MST_CTRL VDP_MST_CTRL;

	VDP_MST_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_CTRL.u32)));
	VDP_MST_CTRL.bits.arb_mode = arb_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_CTRL.u32)),VDP_MST_CTRL.u32);

	return ;
}


HI_VOID VDP_MASTER_SetSplitMode( HI_U32 split_mode)
{
	U_VDP_MST_CTRL VDP_MST_CTRL;

	VDP_MST_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_CTRL.u32)));
	VDP_MST_CTRL.bits.split_mode = split_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_CTRL.u32)),VDP_MST_CTRL.u32);

	return ;
}


HI_VOID VDP_MASTER_SetRchnPrio( HI_U32 id, HI_U32 prio)
{
	HI_U32 u32Prio = prio & 0x1;
	HI_U32 u32RchnPrio = 0;

	if(id<32)
	{
		u32RchnPrio = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_RCHN_PRIO0.u32)));
		u32RchnPrio &= (~(0x1 << id));
		u32RchnPrio |= (u32Prio << id);
		VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_RCHN_PRIO0.u32)),u32RchnPrio);
	}

	return ;
}


HI_VOID VDP_MASTER_SetWchnPrio( HI_U32 id, HI_U32 prio)
{
	HI_U32 u32Prio = prio & 0x1;
	HI_U32 u32WchnPrio = 0;

	if(id<32)
	{
		u32WchnPrio = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_WCHN_PRIO0.u32)));
		u32WchnPrio &= (~(0x1 << id));
		u32WchnPrio |= (u32Prio << id);
		VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_WCHN_PRIO0.u32)),u32WchnPrio);
	}
	return ;
}


HI_VOID VDP_MASTER_SetBusErrorClr( HI_U32 bus_error_clr)
{
	U_VDP_MST_BUS_ERR_CLR VDP_MST_BUS_ERR_CLR;

	VDP_MST_BUS_ERR_CLR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR_CLR.u32)));
	VDP_MST_BUS_ERR_CLR.bits.bus_error_clr = bus_error_clr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR_CLR.u32)),VDP_MST_BUS_ERR_CLR.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMst2WError( HI_U32 mst2_w_error)
{
	U_VDP_MST_BUS_ERR VDP_MST_BUS_ERR;

	VDP_MST_BUS_ERR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)));
	VDP_MST_BUS_ERR.bits.mst2_w_error = mst2_w_error;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)),VDP_MST_BUS_ERR.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMst2RError( HI_U32 mst2_r_error)
{
	U_VDP_MST_BUS_ERR VDP_MST_BUS_ERR;

	VDP_MST_BUS_ERR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)));
	VDP_MST_BUS_ERR.bits.mst2_r_error = mst2_r_error;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)),VDP_MST_BUS_ERR.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMst1WError( HI_U32 mst1_w_error)
{
	U_VDP_MST_BUS_ERR VDP_MST_BUS_ERR;

	VDP_MST_BUS_ERR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)));
	VDP_MST_BUS_ERR.bits.mst1_w_error = mst1_w_error;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)),VDP_MST_BUS_ERR.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMst1RError( HI_U32 mst1_r_error)
{
	U_VDP_MST_BUS_ERR VDP_MST_BUS_ERR;

	VDP_MST_BUS_ERR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)));
	VDP_MST_BUS_ERR.bits.mst1_r_error = mst1_r_error;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)),VDP_MST_BUS_ERR.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMst0WError( HI_U32 mst0_w_error)
{
	U_VDP_MST_BUS_ERR VDP_MST_BUS_ERR;

	VDP_MST_BUS_ERR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)));
	VDP_MST_BUS_ERR.bits.mst0_w_error = mst0_w_error;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)),VDP_MST_BUS_ERR.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMst0RError( HI_U32 mst0_r_error)
{
	U_VDP_MST_BUS_ERR VDP_MST_BUS_ERR;

	VDP_MST_BUS_ERR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)));
	VDP_MST_BUS_ERR.bits.mst0_r_error = mst0_r_error;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_BUS_ERR.u32)),VDP_MST_BUS_ERR.u32);

	return ;
}


HI_VOID VDP_MASTER_SetMstAxiDetEnable( HI_U32 axi_det_enable)
{
	U_VDP_MST_DEBUG_CTRL VDP_MST_DEBUG_CTRL;

	VDP_MST_DEBUG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VDP_MST_DEBUG_CTRL.u32)));
	VDP_MST_DEBUG_CTRL.bits.axi_det_enable = axi_det_enable;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VDP_MST_DEBUG_CTRL.u32)),VDP_MST_DEBUG_CTRL.u32);

	return ;
}

