#include "vdp_hal_ip_cap.h"
#include "vdp_hal_comm.h"

extern S_VDP_REGS_TYPE *pVdpReg;
HI_VOID VDP_CAP_SetWbcCmpEn( HI_U32 offset, HI_U32 wbc_cmp_en)
{
	U_WBC_CTRL WBC_CTRL;

	WBC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset));
	WBC_CTRL.bits.wbc_cmp_en = wbc_cmp_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset),WBC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_CAP_SetCapCkGtEn( HI_U32 offset, HI_U32 cap_ck_gt_en)
{
	U_WBC_CTRL WBC_CTRL;
	
	WBC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset));
	WBC_CTRL.bits.cap_ck_gt_en = cap_ck_gt_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset),WBC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_CAP_SetWbc3dMode( HI_U32 offset, HI_U32 wbc_3d_mode)
{
	U_WBC_CTRL WBC_CTRL;

	WBC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset));
	WBC_CTRL.bits.wbc_3d_mode = wbc_3d_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset),WBC_CTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetChksumEn( HI_U32 offset, HI_U32 chksum_en)
{
	U_WBC_CTRL WBC_CTRL;

	WBC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset));
	WBC_CTRL.bits.chksum_en = chksum_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset),WBC_CTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetFlipEn( HI_U32 offset, HI_U32 flip_en)
{
	U_WBC_CTRL WBC_CTRL;

	WBC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset));
	WBC_CTRL.bits.flip_en = flip_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset),WBC_CTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetUvOrder( HI_U32 offset, HI_U32 uv_order)
{
	U_WBC_CTRL WBC_CTRL;

	WBC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset));
	WBC_CTRL.bits.uv_order = uv_order;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset),WBC_CTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetDataWidth( HI_U32 offset, HI_U32 data_width)
{
	U_WBC_CTRL WBC_CTRL;

	WBC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset));
	WBC_CTRL.bits.data_width = data_width;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CTRL.u32) + offset),WBC_CTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcLen( HI_U32 offset, HI_U32 wbc_len)
{
	U_WBC_MAC_CTRL WBC_MAC_CTRL;

	WBC_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_MAC_CTRL.u32) + offset));
	WBC_MAC_CTRL.bits.wbc_len = wbc_len;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_MAC_CTRL.u32) + offset),WBC_MAC_CTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetReqInterval( HI_U32 offset, HI_U32 req_interval)
{
	U_WBC_MAC_CTRL WBC_MAC_CTRL;

	WBC_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_MAC_CTRL.u32) + offset));
	WBC_MAC_CTRL.bits.req_interval = req_interval;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_MAC_CTRL.u32) + offset),WBC_MAC_CTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetSttBypass( HI_U32 offset, HI_U32 stt_bypass)
{
	U_WBC_SMMU_BYPASS WBC_SMMU_BYPASS;

	WBC_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_SMMU_BYPASS.u32) + offset));
	WBC_SMMU_BYPASS.bits.stt_bypass = stt_bypass;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_SMMU_BYPASS.u32) + offset),WBC_SMMU_BYPASS.u32);

	return ;
}


HI_VOID VDP_CAP_SetMmu3dBypass( HI_U32 offset, HI_U32 mmu_3d_bypass)
{
	U_WBC_SMMU_BYPASS WBC_SMMU_BYPASS;

	WBC_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_SMMU_BYPASS.u32) + offset));
	WBC_SMMU_BYPASS.bits.mmu_3d_bypass = mmu_3d_bypass;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_SMMU_BYPASS.u32) + offset),WBC_SMMU_BYPASS.u32);

	return ;
}


HI_VOID VDP_CAP_SetMmu2dBypass( HI_U32 offset, HI_U32 mmu_2d_bypass)
{
	U_WBC_SMMU_BYPASS WBC_SMMU_BYPASS;

	WBC_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_SMMU_BYPASS.u32) + offset));
	WBC_SMMU_BYPASS.bits.mmu_2d_bypass = mmu_2d_bypass;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_SMMU_BYPASS.u32) + offset),WBC_SMMU_BYPASS.u32);

	return ;
}


HI_VOID VDP_CAP_SetLowdlyEn( HI_U32 offset, HI_U32 lowdly_en)
{
	U_WBC_LOWDLYCTRL WBC_LOWDLYCTRL;

	WBC_LOWDLYCTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_LOWDLYCTRL.u32) + offset));
	WBC_LOWDLYCTRL.bits.lowdly_en = lowdly_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_LOWDLYCTRL.u32) + offset),WBC_LOWDLYCTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetLowdlyTest( HI_U32 offset, HI_U32 lowdly_test)
{
	U_WBC_LOWDLYCTRL WBC_LOWDLYCTRL;

	WBC_LOWDLYCTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_LOWDLYCTRL.u32) + offset));
	WBC_LOWDLYCTRL.bits.lowdly_test = lowdly_test;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_LOWDLYCTRL.u32) + offset),WBC_LOWDLYCTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetPartfnsLineNum( HI_U32 offset, HI_U32 partfns_line_num)
{
	U_WBC_LOWDLYCTRL WBC_LOWDLYCTRL;

	WBC_LOWDLYCTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_LOWDLYCTRL.u32) + offset));
	WBC_LOWDLYCTRL.bits.partfns_line_num = partfns_line_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_LOWDLYCTRL.u32) + offset),WBC_LOWDLYCTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbPerLineNum( HI_U32 offset, HI_U32 wb_per_line_num)
{
	U_WBC_LOWDLYCTRL WBC_LOWDLYCTRL;

	WBC_LOWDLYCTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_LOWDLYCTRL.u32) + offset));
	WBC_LOWDLYCTRL.bits.wb_per_line_num = wb_per_line_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_LOWDLYCTRL.u32) + offset),WBC_LOWDLYCTRL.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcTunladdrH( HI_U32 offset, HI_U32 wbc_tunladdr_h)
{
	U_WBC_TUNLADDR_H WBC_TUNLADDR_H;

	WBC_TUNLADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_TUNLADDR_H.u32) + offset));
	WBC_TUNLADDR_H.bits.wbc_tunladdr_h = wbc_tunladdr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_TUNLADDR_H.u32) + offset),WBC_TUNLADDR_H.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcTunladdrL( HI_U32 offset, HI_U32 wbc_tunladdr_l)
{
	U_WBC_TUNLADDR_L WBC_TUNLADDR_L;

	WBC_TUNLADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_TUNLADDR_L.u32) + offset));
	WBC_TUNLADDR_L.bits.wbc_tunladdr_l = wbc_tunladdr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_TUNLADDR_L.u32) + offset),WBC_TUNLADDR_L.u32);

	return ;
}


HI_VOID VDP_CAP_SetPartFinish( HI_U32 offset, HI_U32 part_finish)
{
	U_WBC_LOWDLYSTA WBC_LOWDLYSTA;

	WBC_LOWDLYSTA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_LOWDLYSTA.u32) + offset));
	WBC_LOWDLYSTA.bits.part_finish = part_finish;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_LOWDLYSTA.u32) + offset),WBC_LOWDLYSTA.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcYaddrH( HI_U32 offset, HI_U32 wbc_yaddr_h)
{
	U_WBC_YADDR_H WBC_YADDR_H;

	WBC_YADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_YADDR_H.u32) + offset));
	WBC_YADDR_H.bits.wbc_yaddr_h = wbc_yaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_YADDR_H.u32) + offset),WBC_YADDR_H.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcYaddrL( HI_U32 offset, HI_U32 wbc_yaddr_l)
{
	U_WBC_YADDR_L WBC_YADDR_L;

	WBC_YADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_YADDR_L.u32) + offset));
	WBC_YADDR_L.bits.wbc_yaddr_l = wbc_yaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_YADDR_L.u32) + offset),WBC_YADDR_L.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcCaddrH( HI_U32 offset, HI_U32 wbc_caddr_h)
{
	U_WBC_CADDR_H WBC_CADDR_H;

	WBC_CADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CADDR_H.u32) + offset));
	WBC_CADDR_H.bits.wbc_caddr_h = wbc_caddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CADDR_H.u32) + offset),WBC_CADDR_H.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcCaddrL( HI_U32 offset, HI_U32 wbc_caddr_l)
{
	U_WBC_CADDR_L WBC_CADDR_L;

	WBC_CADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CADDR_L.u32) + offset));
	WBC_CADDR_L.bits.wbc_caddr_l = wbc_caddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CADDR_L.u32) + offset),WBC_CADDR_L.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcYstride( HI_U32 offset, HI_U32 wbc_ystride)
{
	U_WBC_YSTRIDE WBC_YSTRIDE;

	WBC_YSTRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_YSTRIDE.u32) + offset));
	WBC_YSTRIDE.bits.wbc_ystride = wbc_ystride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_YSTRIDE.u32) + offset),WBC_YSTRIDE.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcCstride( HI_U32 offset, HI_U32 wbc_cstride)
{
	U_WBC_CSTRIDE WBC_CSTRIDE;

	WBC_CSTRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CSTRIDE.u32) + offset));
	WBC_CSTRIDE.bits.wbc_cstride = wbc_cstride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CSTRIDE.u32) + offset),WBC_CSTRIDE.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcYnaddrH( HI_U32 offset, HI_U32 wbc_ynaddr_h)
{
	U_WBC_YNADDR_H WBC_YNADDR_H;

	WBC_YNADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_YNADDR_H.u32) + offset));
	WBC_YNADDR_H.bits.wbc_ynaddr_h = wbc_ynaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_YNADDR_H.u32) + offset),WBC_YNADDR_H.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcYnaddrL( HI_U32 offset, HI_U32 wbc_ynaddr_l)
{
	U_WBC_YNADDR_L WBC_YNADDR_L;

	WBC_YNADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_YNADDR_L.u32) + offset));
	WBC_YNADDR_L.bits.wbc_ynaddr_l = wbc_ynaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_YNADDR_L.u32) + offset),WBC_YNADDR_L.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcCnaddrH( HI_U32 offset, HI_U32 wbc_cnaddr_h)
{
	U_WBC_CNADDR_H WBC_CNADDR_H;

	WBC_CNADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CNADDR_H.u32) + offset));
	WBC_CNADDR_H.bits.wbc_cnaddr_h = wbc_cnaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CNADDR_H.u32) + offset),WBC_CNADDR_H.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcCnaddrL( HI_U32 offset, HI_U32 wbc_cnaddr_l)
{
	U_WBC_CNADDR_L WBC_CNADDR_L;

	WBC_CNADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CNADDR_L.u32) + offset));
	WBC_CNADDR_L.bits.wbc_cnaddr_l = wbc_cnaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CNADDR_L.u32) + offset),WBC_CNADDR_L.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcYnstride( HI_U32 offset, HI_U32 wbc_ynstride)
{
	U_WBC_YNSTRIDE WBC_YNSTRIDE;

	WBC_YNSTRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_YNSTRIDE.u32) + offset));
	WBC_YNSTRIDE.bits.wbc_ynstride = wbc_ynstride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_YNSTRIDE.u32) + offset),WBC_YNSTRIDE.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcCnstride( HI_U32 offset, HI_U32 wbc_cnstride)
{
	U_WBC_CNSTRIDE WBC_CNSTRIDE;

	WBC_CNSTRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CNSTRIDE.u32) + offset));
	WBC_CNSTRIDE.bits.wbc_cnstride = wbc_cnstride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CNSTRIDE.u32) + offset),WBC_CNSTRIDE.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcSttAddrH( HI_U32 offset, HI_U32 wbc_stt_addr_h)
{
	U_WBC_STT_ADDR_H WBC_STT_ADDR_H;

	WBC_STT_ADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_STT_ADDR_H.u32) + offset));
	WBC_STT_ADDR_H.bits.wbc_stt_addr_h = wbc_stt_addr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_STT_ADDR_H.u32) + offset),WBC_STT_ADDR_H.u32);

	return ;
}


HI_VOID VDP_CAP_SetWbcSttAddrL( HI_U32 offset, HI_U32 wbc_stt_addr_l)
{
	U_WBC_STT_ADDR_L WBC_STT_ADDR_L;

	WBC_STT_ADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_STT_ADDR_L.u32) + offset));
	WBC_STT_ADDR_L.bits.wbc_stt_addr_l = wbc_stt_addr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_STT_ADDR_L.u32) + offset),WBC_STT_ADDR_L.u32);

	return ;
}


HI_VOID VDP_CAP_SetCapHeight( HI_U32 offset, HI_U32 cap_height)
{
	U_WBC_CAP_RESO WBC_CAP_RESO;
	WBC_CAP_RESO.u32 = VDP_DdrRead((&(pVdpReg->WBC_CAP_RESO.u32) + offset));
	//WBC_CAP_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CAP_RESO.u32) + offset));
	WBC_CAP_RESO.bits.cap_height = cap_height;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CAP_RESO.u32) + offset),WBC_CAP_RESO.u32);

#if 0
	VDP_RegWriteEx(ADDR_WBC0_HEIGHT+ offset * WBC_OFFSET , cap_height);
#endif

	return ;
}


HI_VOID VDP_CAP_SetCapWidth( HI_U32 offset, HI_U32 cap_width)
{
	U_WBC_CAP_RESO WBC_CAP_RESO;
	WBC_CAP_RESO.u32 = VDP_DdrRead((&(pVdpReg->WBC_CAP_RESO.u32) + offset));
	//WBC_CAP_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CAP_RESO.u32) + offset));
	WBC_CAP_RESO.bits.cap_width = cap_width;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CAP_RESO.u32) + offset),WBC_CAP_RESO.u32);

#if 0
	VDP_RegWriteEx(ADDR_WBC0_WIDTH + offset * WBC_OFFSET , cap_width);
#endif

	return ;
}


HI_VOID VDP_CAP_SetCapInfoH( HI_U32 offset, HI_U32 cap_info_h)
{
	U_WBC_CAP_INFO WBC_CAP_INFO;

	WBC_CAP_INFO.u32 = VDP_DdrRead((&(pVdpReg->WBC_CAP_INFO.u32) + offset));
	//WBC_CAP_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CAP_INFO.u32) + offset));
	WBC_CAP_INFO.bits.cap_info_h = cap_info_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CAP_INFO.u32) + offset),WBC_CAP_INFO.u32);

#if 0
	VDP_RegWriteEx(ADDR_WBC0_FINFO + offset * WBC_OFFSET , cap_info_h);
#endif

	return ;
}


HI_VOID VDP_CAP_SetCapInfoL( HI_U32 offset, HI_U32 cap_info_l)
{
	U_WBC_CAP_INFO1 WBC_CAP_INFO1;

	WBC_CAP_INFO1.u32 = VDP_DdrRead((&(pVdpReg->WBC_CAP_INFO1.u32) + offset));
	//WBC_CAP_INFO1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_CAP_INFO1.u32) + offset));
	WBC_CAP_INFO1.bits.cap_info_l = cap_info_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_CAP_INFO1.u32) + offset),WBC_CAP_INFO1.u32);

#if 0
	VDP_RegWriteEx(ADDR_WBC0_FINFO + offset * WBC_OFFSET , cap_info_l);
#endif

	return ;
}


