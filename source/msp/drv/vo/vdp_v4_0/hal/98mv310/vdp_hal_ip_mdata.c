#ifndef __VDP_HAL_IP_MDATA_H__
#define __VDP_HAL_IP_MDATA_H__

#include "vdp_hal_ip_mdata.h"
#include "vdp_hal_comm.h"

extern S_VDP_REGS_TYPE *pVdpReg;

HI_VOID VDP_MDATA_SetChnEn( HI_U32 chn_en)
{
	U_MSREQ_CTRL MSREQ_CTRL;

	MSREQ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)));
	MSREQ_CTRL.bits.chn_en = chn_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)),MSREQ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_MDATA_SetNosecFlag( HI_U32 nosec_flag)
{
	U_MSREQ_CTRL MSREQ_CTRL;

	MSREQ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)));
	MSREQ_CTRL.bits.nosec_flag = nosec_flag;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)),MSREQ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_MDATA_SetMmuBypass( HI_U32 mmu_bypass)
{
	U_MSREQ_CTRL MSREQ_CTRL;

	MSREQ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)));
	MSREQ_CTRL.bits.mmu_bypass = mmu_bypass;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)),MSREQ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_MDATA_SetAviValid( HI_U32 avi_valid)
{
	U_MSREQ_CTRL MSREQ_CTRL;

	MSREQ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)));
	MSREQ_CTRL.bits.avi_valid = avi_valid;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)),MSREQ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_MDATA_SetSmdValid( HI_U32 smd_valid)
{
	U_MSREQ_CTRL MSREQ_CTRL;

	MSREQ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)));
	MSREQ_CTRL.bits.smd_valid = smd_valid;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)),MSREQ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_MDATA_SetSreqDelay( HI_U32 sreq_delay)
{
	U_MSREQ_CTRL MSREQ_CTRL;

	MSREQ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)));
	MSREQ_CTRL.bits.sreq_delay = sreq_delay;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->MSREQ_CTRL.u32)),MSREQ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_MDATA_SetRegup( HI_U32 regup)
{
	U_MSREQ_RUPD MSREQ_RUPD;

	MSREQ_RUPD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MSREQ_RUPD.u32)));
	MSREQ_RUPD.bits.regup = regup;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->MSREQ_RUPD.u32)),MSREQ_RUPD.u32);
	
	return ;
}


HI_VOID VDP_MDATA_SetMaddr( HI_U32 maddr)
{
	U_MSREQ_ADDR MSREQ_ADDR;

	MSREQ_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MSREQ_ADDR.u32)));
	MSREQ_ADDR.bits.maddr = maddr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->MSREQ_ADDR.u32)),MSREQ_ADDR.u32);
	
	return ;
}


HI_VOID VDP_MDATA_SetMburst( HI_U32 mburst)
{
	U_MSREQ_BURST MSREQ_BURST;

	MSREQ_BURST.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->MSREQ_BURST.u32)));
	MSREQ_BURST.bits.mburst = mburst;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->MSREQ_BURST.u32)),MSREQ_BURST.u32);
	
	return ;
}

#if 0
HI_U32 VDP_MDATA_GetWorkAddr(S_VDP_REGS_TYPE * pVdpReg)
{
	U_MSREQ_DEBUG0 MSREQ_DEBUG0;
	MSREQ_DEBUG0.u32 = VDP_RegReadEx(VDP_BASE_ADDR + offsetof(S_VDP_REGS_TYPE, MSREQ_DEBUG0));
	return MSREQ_DEBUG0.bits.work_addr;
}


HI_U32 VDP_MDATA_GetSendNum(S_VDP_REGS_TYPE * pVdpReg)
{
	U_MSREQ_DEBUG1 MSREQ_DEBUG1;
	MSREQ_DEBUG1.u32 = VDP_RegReadEx(VDP_BASE_ADDR + offsetof(S_VDP_REGS_TYPE, MSREQ_DEBUG1));
	return MSREQ_DEBUG1.bits.send_num;
}


HI_U32 VDP_MDATA_GetDebugSta(S_VDP_REGS_TYPE * pVdpReg)
{
	U_MSREQ_DEBUG2 MSREQ_DEBUG2;
	MSREQ_DEBUG2.u32 = VDP_RegReadEx(VDP_BASE_ADDR + offsetof(S_VDP_REGS_TYPE, MSREQ_DEBUG2));
	return MSREQ_DEBUG2.bits.debug_sta;
}
#endif


#endif

