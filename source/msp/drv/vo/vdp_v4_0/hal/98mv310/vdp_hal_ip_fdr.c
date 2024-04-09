#include "vdp_hal_comm.h"
#include "vdp_hal_ip_fdr.h"

extern S_VDP_REGS_TYPE *pVdpReg;
//--------------------------------------------
// fdr vid driver
//--------------------------------------------
HI_VOID VDP_FDR_VID_SetMrgMuteMode(HI_U32 offset, HI_U32 mrg_mute_mode)
{
	U_VID_READ_CTRL VID_READ_CTRL;

	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.mrg_mute_mode = mrg_mute_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetFdrCkGtEn(HI_U32 offset, HI_U32 fdr_ck_gt_en)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.fdr_ck_gt_en = fdr_ck_gt_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetMrgEnable(HI_U32 offset, HI_U32 mrg_enable)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.mrg_enable = mrg_enable;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetVicapMuteEn(HI_U32 offset, HI_U32 vicap_mute_en)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.vicap_mute_en = vicap_mute_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetMuteReqEn(HI_U32 offset, HI_U32 mute_req_en)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.mute_req_en = mute_req_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetMuteEn(HI_U32 offset, HI_U32 mute_en)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.mute_en = mute_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetRmode3d(HI_U32 offset, HI_U32 rmode_3d)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.rmode_3d = rmode_3d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetChmCopyEn(HI_U32 offset, HI_U32 chm_copy_en)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.chm_copy_en = chm_copy_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetFlipEn(HI_U32 offset, HI_U32 flip_en)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.flip_en = flip_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetLmDrawMode(HI_U32 offset, HI_U32 lm_draw_mode)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.lm_draw_mode = lm_draw_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetChmDrawMode(HI_U32 offset, HI_U32 chm_draw_mode)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.chm_draw_mode = chm_draw_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetLmRmode(HI_U32 offset, HI_U32 lm_rmode)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.lm_rmode = lm_rmode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetChmRmode(HI_U32 offset, HI_U32 chm_rmode)
{
	U_VID_READ_CTRL VID_READ_CTRL;
	
		
	VID_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset));
	VID_READ_CTRL.bits.chm_rmode = chm_rmode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_READ_CTRL.u32) + offset),VID_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetPreRdEn(HI_U32 offset, HI_U32 pre_rd_en)
{
	U_VID_MAC_CTRL VID_MAC_CTRL;
	
		
	VID_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset));
	VID_MAC_CTRL.bits.pre_rd_en = pre_rd_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset),VID_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetReqLdMode(HI_U32 offset, HI_U32 req_ld_mode)
{
	U_VID_MAC_CTRL VID_MAC_CTRL;
	
	VID_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset));
	VID_MAC_CTRL.bits.req_ld_mode = req_ld_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset),VID_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetReqInterval(HI_U32 offset, HI_U32 req_interval)
{
	U_VID_MAC_CTRL VID_MAC_CTRL;
	
	VID_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset));
	VID_MAC_CTRL.bits.req_interval = req_interval;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset),VID_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetOflMaster(HI_U32 offset, HI_U32 ofl_master)
{
	U_VID_MAC_CTRL VID_MAC_CTRL;
	
		
	VID_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset));
	VID_MAC_CTRL.bits.ofl_master = ofl_master;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset),VID_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetReqLen(HI_U32 offset, HI_U32 req_len)
{
	U_VID_MAC_CTRL VID_MAC_CTRL;
	
		
	VID_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset));
	VID_MAC_CTRL.bits.req_len = req_len;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset),VID_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetReqCtrl(HI_U32 offset, HI_U32 req_ctrl)
{
	U_VID_MAC_CTRL VID_MAC_CTRL;
	
		
	VID_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset));
	VID_MAC_CTRL.bits.req_ctrl = req_ctrl;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_MAC_CTRL.u32) + offset),VID_MAC_CTRL.u32);
	
	return ;
}


 HI_VOID VDP_FDR_VID_SetDcmpFrmMaxEn(HI_U32 offset, HI_U32 dcmp_frm_max_en)
 {
 	U_VID_OUT_CTRL VID_OUT_CTRL;
 	
 		
 	VID_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset));
 	VID_OUT_CTRL.bits.dcmp_frm_max_en = dcmp_frm_max_en;
 	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset),VID_OUT_CTRL.u32);
 	
 	return ;
 }


HI_VOID VDP_FDR_VID_SetTestpatternEn(HI_U32 offset, HI_U32 testpattern_en)
{
	U_VID_OUT_CTRL VID_OUT_CTRL;
	
		
	VID_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset));
	VID_OUT_CTRL.bits.testpattern_en = testpattern_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset),VID_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetSinglePortMode(HI_U32 offset, HI_U32 single_port_mode)
{
	U_VID_OUT_CTRL VID_OUT_CTRL;
	
		
	VID_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset));
	VID_OUT_CTRL.bits.single_port_mode = single_port_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset),VID_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetUvOrderEn(HI_U32 offset, HI_U32 uv_order_en)
{
	U_VID_OUT_CTRL VID_OUT_CTRL;
	
		
	VID_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset));
	VID_OUT_CTRL.bits.uv_order_en = uv_order_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset),VID_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetDrawPixelMode(HI_U32 offset, HI_U32 draw_pixel_mode)
{
	U_VID_OUT_CTRL VID_OUT_CTRL;
	
		
	VID_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset));
	VID_OUT_CTRL.bits.draw_pixel_mode = draw_pixel_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_OUT_CTRL.u32) + offset),VID_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetMuteY(HI_U32 offset, HI_U32 mute_y)
{
	U_VID_MUTE_BK VID_MUTE_BK;
	
		
	VID_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_MUTE_BK.u32) + offset));
	VID_MUTE_BK.bits.mute_y = mute_y;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_MUTE_BK.u32) + offset),VID_MUTE_BK.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetMuteCb(HI_U32 offset, HI_U32 mute_cb)
{
	U_VID_MUTE_BK VID_MUTE_BK;
	
		
	VID_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_MUTE_BK.u32) + offset));
	VID_MUTE_BK.bits.mute_cb = mute_cb;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_MUTE_BK.u32) + offset),VID_MUTE_BK.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetMuteCr(HI_U32 offset, HI_U32 mute_cr)
{
	U_VID_MUTE_BK VID_MUTE_BK;
	
		
	VID_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_MUTE_BK.u32) + offset));
	VID_MUTE_BK.bits.mute_cr = mute_cr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_MUTE_BK.u32) + offset),VID_MUTE_BK.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetChmBypass3d(HI_U32 offset, HI_U32 chm_bypass_3d)
{
	U_VID_SMMU_BYPASS VID_SMMU_BYPASS;

	VID_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SMMU_BYPASS.u32) + offset));
	VID_SMMU_BYPASS.bits.chm_bypass_3d = chm_bypass_3d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SMMU_BYPASS.u32) + offset),VID_SMMU_BYPASS.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetLmBypass3d(HI_U32 offset, HI_U32 lm_bypass_3d)
{
	U_VID_SMMU_BYPASS VID_SMMU_BYPASS;

	VID_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SMMU_BYPASS.u32) + offset));
	VID_SMMU_BYPASS.bits.lm_bypass_3d = lm_bypass_3d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SMMU_BYPASS.u32) + offset),VID_SMMU_BYPASS.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetChmBypass2d(HI_U32 offset, HI_U32 chm_bypass_2d)
{
	U_VID_SMMU_BYPASS VID_SMMU_BYPASS;

	VID_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SMMU_BYPASS.u32) + offset));
	VID_SMMU_BYPASS.bits.chm_bypass_2d = chm_bypass_2d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SMMU_BYPASS.u32) + offset),VID_SMMU_BYPASS.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetLmBypass2d(HI_U32 offset, HI_U32 lm_bypass_2d)
{
	U_VID_SMMU_BYPASS VID_SMMU_BYPASS;

	VID_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SMMU_BYPASS.u32) + offset));
	VID_SMMU_BYPASS.bits.lm_bypass_2d = lm_bypass_2d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SMMU_BYPASS.u32) + offset),VID_SMMU_BYPASS.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetYFrmSize(HI_U32 offset, HI_U32 y_frm_size)
{
	U_VID_SRC_LFSIZE VID_SRC_LFSIZE;

	VID_SRC_LFSIZE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_LFSIZE.u32) + offset));
	VID_SRC_LFSIZE.bits.y_frm_size = y_frm_size;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_LFSIZE.u32) + offset),VID_SRC_LFSIZE.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetCFrmSize(HI_U32 offset, HI_U32 c_frm_size)
{
	U_VID_SRC_CFSIZE VID_SRC_CFSIZE;

	VID_SRC_CFSIZE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_CFSIZE.u32) + offset));
	VID_SRC_CFSIZE.bits.c_frm_size = c_frm_size;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_CFSIZE.u32) + offset),VID_SRC_CFSIZE.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetDcmpType(HI_U32 offset, HI_U32 dcmp_type)
{
	U_VID_SRC_INFO VID_SRC_INFO;
	
		
	VID_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset));
	VID_SRC_INFO.bits.dcmp_type = dcmp_type;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset),VID_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetDispMode(HI_U32 offset, HI_U32 disp_mode)
{
	U_VID_SRC_INFO VID_SRC_INFO;
	
		
	VID_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset));
	VID_SRC_INFO.bits.disp_mode = disp_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset),VID_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetFieldType(HI_U32 offset, HI_U32 field_type)
{
	U_VID_SRC_INFO VID_SRC_INFO;
	
		
	VID_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset));
	VID_SRC_INFO.bits.field_type = field_type;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset),VID_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetDataWidth(HI_U32 offset, HI_U32 data_width)
{
	U_VID_SRC_INFO VID_SRC_INFO;
	
		
	VID_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset));
	VID_SRC_INFO.bits.data_width = data_width;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset),VID_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetDataFmt(HI_U32 offset, HI_U32 data_fmt)
{
	U_VID_SRC_INFO VID_SRC_INFO;
	
		
	VID_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset));
	VID_SRC_INFO.bits.data_fmt = data_fmt;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset),VID_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetDataType(HI_U32 offset, HI_U32 data_type)
{
	U_VID_SRC_INFO VID_SRC_INFO;
	
		
	VID_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset));
	VID_SRC_INFO.bits.data_type = data_type;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_INFO.u32) + offset),VID_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetSrcH(HI_U32 offset, HI_U32 src_h)
{
	U_VID_SRC_RESO VID_SRC_RESO;
	
		
	VID_SRC_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_RESO.u32) + offset));
	VID_SRC_RESO.bits.src_h = src_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_RESO.u32) + offset),VID_SRC_RESO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetSrcW(HI_U32 offset, HI_U32 src_w)
{
	U_VID_SRC_RESO VID_SRC_RESO;
	
		
	VID_SRC_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_RESO.u32) + offset));
	VID_SRC_RESO.bits.src_w = src_w;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_RESO.u32) + offset),VID_SRC_RESO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetSrcCropY(HI_U32 offset, HI_U32 src_crop_y)
{
	U_VID_SRC_CROP VID_SRC_CROP;
	
		
	VID_SRC_CROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_CROP.u32) + offset));
	VID_SRC_CROP.bits.src_crop_y = src_crop_y;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_CROP.u32) + offset),VID_SRC_CROP.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetSrcCropX(HI_U32 offset, HI_U32 src_crop_x)
{
	U_VID_SRC_CROP VID_SRC_CROP;
	
		
	VID_SRC_CROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_SRC_CROP.u32) + offset));
	VID_SRC_CROP.bits.src_crop_x = src_crop_x;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_SRC_CROP.u32) + offset),VID_SRC_CROP.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetIresoH(HI_U32 offset, HI_U32 ireso_h)
{
	U_VID_IN_RESO VID_IN_RESO;
	
		
	VID_IN_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_IN_RESO.u32) + offset));
	VID_IN_RESO.bits.ireso_h = ireso_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_IN_RESO.u32) + offset),VID_IN_RESO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetIresoW(HI_U32 offset, HI_U32 ireso_w)
{
	U_VID_IN_RESO VID_IN_RESO;
	
		
	VID_IN_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_IN_RESO.u32) + offset));
	VID_IN_RESO.bits.ireso_w = ireso_w;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_IN_RESO.u32) + offset),VID_IN_RESO.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetVhdaddrH(HI_U32 offset, HI_U32 vhdaddr_h)
{
	U_VID_ADDR_H VID_ADDR_H;
	
		
	VID_ADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_ADDR_H.u32) + offset));
	VID_ADDR_H.bits.vhdaddr_h = vhdaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_ADDR_H.u32) + offset),VID_ADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetVhdaddrL(HI_U32 offset, HI_U32 vhdaddr_l)
{
	U_VID_ADDR_L VID_ADDR_L;
	
		
	VID_ADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_ADDR_L.u32) + offset));
	VID_ADDR_L.bits.vhdaddr_l = vhdaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_ADDR_L.u32) + offset),VID_ADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetVhdcaddrH(HI_U32 offset, HI_U32 vhdcaddr_h)
{
	U_VID_CADDR_H VID_CADDR_H;
	
		
	VID_CADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_CADDR_H.u32) + offset));
	VID_CADDR_H.bits.vhdcaddr_h = vhdcaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_CADDR_H.u32) + offset),VID_CADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetVhdcaddrL(HI_U32 offset, HI_U32 vhdcaddr_l)
{
	U_VID_CADDR_L VID_CADDR_L;
	
		
	VID_CADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_CADDR_L.u32) + offset));
	VID_CADDR_L.bits.vhdcaddr_l = vhdcaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_CADDR_L.u32) + offset),VID_CADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetVhdnaddrH(HI_U32 offset, HI_U32 vhdnaddr_h)
{
	U_VID_NADDR_H VID_NADDR_H;
	
		
	VID_NADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_NADDR_H.u32) + offset));
	VID_NADDR_H.bits.vhdnaddr_h = vhdnaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_NADDR_H.u32) + offset),VID_NADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetVhdnaddrL(HI_U32 offset, HI_U32 vhdnaddr_l)
{
	U_VID_NADDR_L VID_NADDR_L;
	
		
	VID_NADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_NADDR_L.u32) + offset));
	VID_NADDR_L.bits.vhdnaddr_l = vhdnaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_NADDR_L.u32) + offset),VID_NADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetVhdncaddrH(HI_U32 offset, HI_U32 vhdncaddr_h)
{
	U_VID_NCADDR_H VID_NCADDR_H;
	
		
	VID_NCADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_NCADDR_H.u32) + offset));
	VID_NCADDR_H.bits.vhdncaddr_h = vhdncaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_NCADDR_H.u32) + offset),VID_NCADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetVhdncaddrL(HI_U32 offset, HI_U32 vhdncaddr_l)
{
	U_VID_NCADDR_L VID_NCADDR_L;
	
		
	VID_NCADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_NCADDR_L.u32) + offset));
	VID_NCADDR_L.bits.vhdncaddr_l = vhdncaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_NCADDR_L.u32) + offset),VID_NCADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetHVhdaddrH(HI_U32 offset, HI_U32 h_vhdaddr_h)
{
	U_VID_HEAD_ADDR_H VID_HEAD_ADDR_H;

	VID_HEAD_ADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_HEAD_ADDR_H.u32) + offset));
	VID_HEAD_ADDR_H.bits.h_vhdaddr_h = h_vhdaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_HEAD_ADDR_H.u32) + offset),VID_HEAD_ADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetHVhdaddrL(HI_U32 offset, HI_U32 h_vhdaddr_l)
{
	U_VID_HEAD_ADDR_L VID_HEAD_ADDR_L;

	VID_HEAD_ADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_HEAD_ADDR_L.u32) + offset));
	VID_HEAD_ADDR_L.bits.h_vhdaddr_l = h_vhdaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_HEAD_ADDR_L.u32) + offset),VID_HEAD_ADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetHVhdcaddrH(HI_U32 offset, HI_U32 h_vhdcaddr_h)
{
	U_VID_HEAD_CADDR_H VID_HEAD_CADDR_H;

	VID_HEAD_CADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_HEAD_CADDR_H.u32) + offset));
	VID_HEAD_CADDR_H.bits.h_vhdcaddr_h = h_vhdcaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_HEAD_CADDR_H.u32) + offset),VID_HEAD_CADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetHVhdcaddrL(HI_U32 offset, HI_U32 h_vhdcaddr_l)
{
	U_VID_HEAD_CADDR_L VID_HEAD_CADDR_L;

	VID_HEAD_CADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_HEAD_CADDR_L.u32) + offset));
	VID_HEAD_CADDR_L.bits.h_vhdcaddr_l = h_vhdcaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_HEAD_CADDR_L.u32) + offset),VID_HEAD_CADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetBVhdaddrH(HI_U32 offset, HI_U32 b_vhdaddr_h)
{
	U_VID_2BIT_ADDR_H VID_2BIT_ADDR_H;

	VID_2BIT_ADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_2BIT_ADDR_H.u32) + offset));
	VID_2BIT_ADDR_H.bits.b_vhdaddr_h = b_vhdaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_2BIT_ADDR_H.u32) + offset),VID_2BIT_ADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetBVhdaddrL(HI_U32 offset, HI_U32 b_vhdaddr_l)
{
	U_VID_2BIT_ADDR_L VID_2BIT_ADDR_L;

	VID_2BIT_ADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_2BIT_ADDR_L.u32) + offset));
	VID_2BIT_ADDR_L.bits.b_vhdaddr_l = b_vhdaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_2BIT_ADDR_L.u32) + offset),VID_2BIT_ADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetBVhdcaddrH(HI_U32 offset, HI_U32 b_vhdcaddr_h)
{
	U_VID_2BIT_CADDR_H VID_2BIT_CADDR_H;

	VID_2BIT_CADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_2BIT_CADDR_H.u32) + offset));
	VID_2BIT_CADDR_H.bits.b_vhdcaddr_h = b_vhdcaddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_2BIT_CADDR_H.u32) + offset),VID_2BIT_CADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetBVhdcaddrL(HI_U32 offset, HI_U32 b_vhdcaddr_l)
{
	U_VID_2BIT_CADDR_L VID_2BIT_CADDR_L;

	VID_2BIT_CADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_2BIT_CADDR_L.u32) + offset));
	VID_2BIT_CADDR_L.bits.b_vhdcaddr_l = b_vhdcaddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_2BIT_CADDR_L.u32) + offset),VID_2BIT_CADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetChmStride(HI_U32 offset, HI_U32 chm_stride)
{
	U_VID_STRIDE VID_STRIDE;
	
		
	VID_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_STRIDE.u32) + offset));
	VID_STRIDE.bits.chm_stride = chm_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_STRIDE.u32) + offset),VID_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetLmStride(HI_U32 offset, HI_U32 lm_stride)
{
	U_VID_STRIDE VID_STRIDE;
	
		
	VID_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_STRIDE.u32) + offset));
	VID_STRIDE.bits.lm_stride = lm_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_STRIDE.u32) + offset),VID_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetChmTileStride(HI_U32 offset, HI_U32 chm_tile_stride)
{
	U_VID_2BIT_STRIDE VID_2BIT_STRIDE;
	
		
	VID_2BIT_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_2BIT_STRIDE.u32) + offset));
	VID_2BIT_STRIDE.bits.chm_tile_stride = chm_tile_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_2BIT_STRIDE.u32) + offset),VID_2BIT_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetLmTileStride(HI_U32 offset, HI_U32 lm_tile_stride)
{
	U_VID_2BIT_STRIDE VID_2BIT_STRIDE;
	
		
	VID_2BIT_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_2BIT_STRIDE.u32) + offset));
	VID_2BIT_STRIDE.bits.lm_tile_stride = lm_tile_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_2BIT_STRIDE.u32) + offset),VID_2BIT_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetChmHeadStride(HI_U32 offset, HI_U32 chm_head_stride)
{
	U_VID_HEAD_STRIDE VID_HEAD_STRIDE;
	
		
	VID_HEAD_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_HEAD_STRIDE.u32) + offset));
	VID_HEAD_STRIDE.bits.chm_head_stride = chm_head_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_HEAD_STRIDE.u32) + offset),VID_HEAD_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetLmHeadStride(HI_U32 offset, HI_U32 lm_head_stride)
{
	U_VID_HEAD_STRIDE VID_HEAD_STRIDE;
	
		
	VID_HEAD_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_HEAD_STRIDE.u32) + offset));
	VID_HEAD_STRIDE.bits.lm_head_stride = lm_head_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_HEAD_STRIDE.u32) + offset),VID_HEAD_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetTpMode(HI_U32 offset, HI_U32 tp_mode)
{
	U_VID_TESTPAT_CFG VID_TESTPAT_CFG;
	
		
	VID_TESTPAT_CFG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_TESTPAT_CFG.u32) + offset));
	VID_TESTPAT_CFG.bits.tp_mode = tp_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_TESTPAT_CFG.u32) + offset),VID_TESTPAT_CFG.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetTpColorMode(HI_U32 offset, HI_U32 tp_color_mode)
{
	U_VID_TESTPAT_CFG VID_TESTPAT_CFG;
	
		
	VID_TESTPAT_CFG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_TESTPAT_CFG.u32) + offset));
	VID_TESTPAT_CFG.bits.tp_color_mode = tp_color_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_TESTPAT_CFG.u32) + offset),VID_TESTPAT_CFG.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetTpLineW(HI_U32 offset, HI_U32 tp_line_w)
{
	U_VID_TESTPAT_CFG VID_TESTPAT_CFG;
	
		
	VID_TESTPAT_CFG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_TESTPAT_CFG.u32) + offset));
	VID_TESTPAT_CFG.bits.tp_line_w = tp_line_w;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_TESTPAT_CFG.u32) + offset),VID_TESTPAT_CFG.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetTpSpeed(HI_U32 offset, HI_U32 tp_speed)
{
	U_VID_TESTPAT_CFG VID_TESTPAT_CFG;
	
		
	VID_TESTPAT_CFG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_TESTPAT_CFG.u32) + offset));
	VID_TESTPAT_CFG.bits.tp_speed = tp_speed;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_TESTPAT_CFG.u32) + offset),VID_TESTPAT_CFG.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetTpSeed(HI_U32 offset, HI_U32 tp_seed)
{
	U_VID_TESTPAT_SEED VID_TESTPAT_SEED;
	
		
	VID_TESTPAT_SEED.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_TESTPAT_SEED.u32) + offset));
	VID_TESTPAT_SEED.bits.tp_seed = tp_seed;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_TESTPAT_SEED.u32) + offset),VID_TESTPAT_SEED.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetFdrPressEn(HI_U32 offset, HI_U32 fdr_press_en)
{
	U_VID_DEBUG_CTRL VID_DEBUG_CTRL;

	VID_DEBUG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DEBUG_CTRL.u32) + offset));
	VID_DEBUG_CTRL.bits.fdr_press_en = fdr_press_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DEBUG_CTRL.u32) + offset),VID_DEBUG_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetChecksumEn(HI_U32 offset, HI_U32 checksum_en)
{
	U_VID_DEBUG_CTRL VID_DEBUG_CTRL;

	VID_DEBUG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_DEBUG_CTRL.u32) + offset));
	VID_DEBUG_CTRL.bits.checksum_en = checksum_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_DEBUG_CTRL.u32) + offset),VID_DEBUG_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetScopeDrdyNum(HI_U32 offset, HI_U32 scope_drdy_num)
{
	U_VID_PRESS_CTRL VID_PRESS_CTRL;
	
	VID_PRESS_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_PRESS_CTRL.u32) + offset));
	VID_PRESS_CTRL.bits.scope_drdy_num = scope_drdy_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_PRESS_CTRL.u32) + offset),VID_PRESS_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetMinDrdyNum(HI_U32 offset, HI_U32 min_drdy_num)
{
	U_VID_PRESS_CTRL VID_PRESS_CTRL;
	
	VID_PRESS_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_PRESS_CTRL.u32) + offset));
	VID_PRESS_CTRL.bits.min_drdy_num = min_drdy_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_PRESS_CTRL.u32) + offset),VID_PRESS_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetScopeNodrdyNum(HI_U32 offset, HI_U32 scope_nodrdy_num)
{
	U_VID_PRESS_CTRL VID_PRESS_CTRL;
	
	VID_PRESS_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_PRESS_CTRL.u32) + offset));
	VID_PRESS_CTRL.bits.scope_nodrdy_num = scope_nodrdy_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_PRESS_CTRL.u32) + offset),VID_PRESS_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetMinNodrdyNum(HI_U32 offset, HI_U32 min_nodrdy_num)
{
	U_VID_PRESS_CTRL VID_PRESS_CTRL;
	
	VID_PRESS_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_PRESS_CTRL.u32) + offset));
	VID_PRESS_CTRL.bits.min_nodrdy_num = min_nodrdy_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_PRESS_CTRL.u32) + offset),VID_PRESS_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetTunlThd(HI_U32 offset, HI_U32 tunl_thd)
{
	U_VID_TUNL_CTRL VID_TUNL_CTRL;

	VID_TUNL_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_TUNL_CTRL.u32) + offset));
	VID_TUNL_CTRL.bits.tunl_thd = tunl_thd;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_TUNL_CTRL.u32) + offset),VID_TUNL_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetTunlInterval(HI_U32 offset, HI_U32 tunl_interval)
{
	U_VID_TUNL_CTRL VID_TUNL_CTRL;

	VID_TUNL_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_TUNL_CTRL.u32) + offset));
	VID_TUNL_CTRL.bits.tunl_interval = tunl_interval;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_TUNL_CTRL.u32) + offset),VID_TUNL_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetTunlAddrH(HI_U32 offset, HI_U32 tunl_addr_h)
{
	U_VID_TUNL_ADDR_H VID_TUNL_ADDR_H;
	
	VID_TUNL_ADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_TUNL_ADDR_H.u32) + offset));
	VID_TUNL_ADDR_H.bits.tunl_addr_h = tunl_addr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_TUNL_ADDR_H.u32) + offset),VID_TUNL_ADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetTunlAddrL(HI_U32 offset, HI_U32 tunl_addr_l)
{
	U_VID_TUNL_ADDR_L VID_TUNL_ADDR_L;
	
	VID_TUNL_ADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_TUNL_ADDR_L.u32) + offset));
	VID_TUNL_ADDR_L.bits.tunl_addr_l = tunl_addr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_TUNL_ADDR_L.u32) + offset),VID_TUNL_ADDR_L.u32);
	
	return ;
}

HI_VOID VDP_FDR_VID_SetYBsErr(HI_U32 offset, HI_U32 y_bs_err)
{
	U_VID_Y_DCMP_WRONG_STA VID_Y_DCMP_WRONG_STA;

	VID_Y_DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_Y_DCMP_WRONG_STA.u32) + offset));
	VID_Y_DCMP_WRONG_STA.bits.y_bs_err = y_bs_err;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_Y_DCMP_WRONG_STA.u32) + offset),VID_Y_DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetYConsume(HI_U32 offset, HI_U32 y_consume)
{
	U_VID_Y_DCMP_WRONG_STA VID_Y_DCMP_WRONG_STA;

	VID_Y_DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_Y_DCMP_WRONG_STA.u32) + offset));
	VID_Y_DCMP_WRONG_STA.bits.y_consume = y_consume;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_Y_DCMP_WRONG_STA.u32) + offset),VID_Y_DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetYForgive(HI_U32 offset, HI_U32 y_forgive)
{
	U_VID_Y_DCMP_WRONG_STA VID_Y_DCMP_WRONG_STA;

	VID_Y_DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_Y_DCMP_WRONG_STA.u32) + offset));
	VID_Y_DCMP_WRONG_STA.bits.y_forgive = y_forgive;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_Y_DCMP_WRONG_STA.u32) + offset),VID_Y_DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetYDcmpErr(HI_U32 offset, HI_U32 y_dcmp_err)
{
	U_VID_Y_DCMP_WRONG_STA VID_Y_DCMP_WRONG_STA;

	VID_Y_DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_Y_DCMP_WRONG_STA.u32) + offset));
	VID_Y_DCMP_WRONG_STA.bits.y_dcmp_err = y_dcmp_err;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_Y_DCMP_WRONG_STA.u32) + offset),VID_Y_DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetCBsErr(HI_U32 offset, HI_U32 c_bs_err)
{
	U_VID_C_DCMP_WRONG_STA VID_C_DCMP_WRONG_STA;

	VID_C_DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_C_DCMP_WRONG_STA.u32) + offset));
	VID_C_DCMP_WRONG_STA.bits.c_bs_err = c_bs_err;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_C_DCMP_WRONG_STA.u32) + offset),VID_C_DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetCConsume(HI_U32 offset, HI_U32 c_consume)
{
	U_VID_C_DCMP_WRONG_STA VID_C_DCMP_WRONG_STA;

	VID_C_DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_C_DCMP_WRONG_STA.u32) + offset));
	VID_C_DCMP_WRONG_STA.bits.c_consume = c_consume;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_C_DCMP_WRONG_STA.u32) + offset),VID_C_DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetCForgive(HI_U32 offset, HI_U32 c_forgive)
{
	U_VID_C_DCMP_WRONG_STA VID_C_DCMP_WRONG_STA;

	VID_C_DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_C_DCMP_WRONG_STA.u32) + offset));
	VID_C_DCMP_WRONG_STA.bits.c_forgive = c_forgive;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_C_DCMP_WRONG_STA.u32) + offset),VID_C_DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_VID_SetCDcmpErr(HI_U32 offset, HI_U32 c_dcmp_err)
{
	U_VID_C_DCMP_WRONG_STA VID_C_DCMP_WRONG_STA;

	VID_C_DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_C_DCMP_WRONG_STA.u32) + offset));
	VID_C_DCMP_WRONG_STA.bits.c_dcmp_err = c_dcmp_err;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->VID_C_DCMP_WRONG_STA.u32) + offset),VID_C_DCMP_WRONG_STA.u32);
	
	return ;
}


//--------------------------------------------
// gfx fdr driver
//--------------------------------------------

HI_VOID VDP_FDR_GFX_SetAddrMapEn(HI_U32 offset, HI_U32 addr_map_en)
{
	U_GFX_READ_CTRL GFX_READ_CTRL;

	GFX_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset));
	GFX_READ_CTRL.bits.addr_map_en = addr_map_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset),GFX_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetFdrCkGtEn(HI_U32 offset, HI_U32 fdr_ck_gt_en)
{
	U_GFX_READ_CTRL GFX_READ_CTRL;
	
		
	GFX_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset));
	GFX_READ_CTRL.bits.fdr_ck_gt_en = fdr_ck_gt_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset),GFX_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetMuteReqEn(HI_U32 offset, HI_U32 mute_req_en)
{
	U_GFX_READ_CTRL GFX_READ_CTRL;
	
		
	GFX_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset));
	GFX_READ_CTRL.bits.mute_req_en = mute_req_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset),GFX_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetMuteEn(HI_U32 offset, HI_U32 mute_en)
{
	U_GFX_READ_CTRL GFX_READ_CTRL;
	
		
	GFX_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset));
	GFX_READ_CTRL.bits.mute_en = mute_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset),GFX_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetRmode3d(HI_U32 offset, HI_U32 rmode_3d)
{
	U_GFX_READ_CTRL GFX_READ_CTRL;
	
		
	GFX_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset));
	GFX_READ_CTRL.bits.rmode_3d = rmode_3d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset),GFX_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetFlipEn(HI_U32 offset, HI_U32 flip_en)
{
	U_GFX_READ_CTRL GFX_READ_CTRL;
	
		
	GFX_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset));
	GFX_READ_CTRL.bits.flip_en = flip_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset),GFX_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetDrawMode(HI_U32 offset, HI_U32 draw_mode)
{
	U_GFX_READ_CTRL GFX_READ_CTRL;
	
		
	GFX_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset));
	GFX_READ_CTRL.bits.draw_mode = draw_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset),GFX_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetReadMode(HI_U32 offset, HI_U32 read_mode)
{
	U_GFX_READ_CTRL GFX_READ_CTRL;
	
		
	GFX_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset));
	GFX_READ_CTRL.bits.read_mode = read_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_READ_CTRL.u32) + offset),GFX_READ_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetReqLdMode(HI_U32 offset, HI_U32 req_ld_mode)
{
	U_GFX_MAC_CTRL GFX_MAC_CTRL;
	
	GFX_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset));
	GFX_MAC_CTRL.bits.req_ld_mode = req_ld_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset),GFX_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetReqInterval(HI_U32 offset, HI_U32 req_interval)
{
	U_GFX_MAC_CTRL GFX_MAC_CTRL;
	
	GFX_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset));
	GFX_MAC_CTRL.bits.req_interval = req_interval;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset),GFX_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetOflMaster(HI_U32 offset, HI_U32 ofl_master)
{
	U_GFX_MAC_CTRL GFX_MAC_CTRL;
	
		
	GFX_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset));
	GFX_MAC_CTRL.bits.ofl_master = ofl_master;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset),GFX_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetReqLen(HI_U32 offset, HI_U32 req_len)
{
	U_GFX_MAC_CTRL GFX_MAC_CTRL;
	
		
	GFX_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset));
	GFX_MAC_CTRL.bits.req_len = req_len;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset),GFX_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetReqCtrl(HI_U32 offset, HI_U32 req_ctrl)
{
	U_GFX_MAC_CTRL GFX_MAC_CTRL;
	
		
	GFX_MAC_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset));
	GFX_MAC_CTRL.bits.req_ctrl = req_ctrl;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_MAC_CTRL.u32) + offset),GFX_MAC_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetTestpatternEn(HI_U32 offset, HI_U32 testpattern_en)
{
	U_GFX_OUT_CTRL GFX_OUT_CTRL;
	
		
	GFX_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset));
	GFX_OUT_CTRL.bits.testpattern_en = testpattern_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset),GFX_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetPremultiEn(HI_U32 offset, HI_U32 premulti_en)
{
	U_GFX_OUT_CTRL GFX_OUT_CTRL;
	
		
	GFX_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset));
	GFX_OUT_CTRL.bits.premulti_en = premulti_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset),GFX_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetBitext(HI_U32 offset, HI_U32 bitext)
{
	U_GFX_OUT_CTRL GFX_OUT_CTRL;
	
		
	GFX_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset));
	GFX_OUT_CTRL.bits.bitext = bitext;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset),GFX_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyEn(HI_U32 offset, HI_U32 key_en)
{
	U_GFX_OUT_CTRL GFX_OUT_CTRL;
	
		
	GFX_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset));
	GFX_OUT_CTRL.bits.key_en = key_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset),GFX_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyMode(HI_U32 offset, HI_U32 key_mode)
{
	U_GFX_OUT_CTRL GFX_OUT_CTRL;
	
		
	GFX_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset));
	GFX_OUT_CTRL.bits.key_mode = key_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset),GFX_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetPalphaEn(HI_U32 offset, HI_U32 palpha_en)
{
	U_GFX_OUT_CTRL GFX_OUT_CTRL;
	
		
	GFX_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset));
	GFX_OUT_CTRL.bits.palpha_en = palpha_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset),GFX_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetPalphaRange(HI_U32 offset, HI_U32 palpha_range)
{
	U_GFX_OUT_CTRL GFX_OUT_CTRL;
	
		
	GFX_OUT_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset));
	GFX_OUT_CTRL.bits.palpha_range = palpha_range;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_OUT_CTRL.u32) + offset),GFX_OUT_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetMuteAlpha(HI_U32 offset, HI_U32 mute_alpha)
{
	U_GFX_MUTE_ALPHA GFX_MUTE_ALPHA;
	
		
	GFX_MUTE_ALPHA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_MUTE_ALPHA.u32) + offset));
	GFX_MUTE_ALPHA.bits.mute_alpha = mute_alpha;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_MUTE_ALPHA.u32) + offset),GFX_MUTE_ALPHA.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetMuteY(HI_U32 offset, HI_U32 mute_y)
{
	U_GFX_MUTE_BK GFX_MUTE_BK;
	
		
	GFX_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_MUTE_BK.u32) + offset));
	GFX_MUTE_BK.bits.mute_y = mute_y;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_MUTE_BK.u32) + offset),GFX_MUTE_BK.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetMuteCb(HI_U32 offset, HI_U32 mute_cb)
{
	U_GFX_MUTE_BK GFX_MUTE_BK;
	
		
	GFX_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_MUTE_BK.u32) + offset));
	GFX_MUTE_BK.bits.mute_cb = mute_cb;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_MUTE_BK.u32) + offset),GFX_MUTE_BK.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetMuteCr(HI_U32 offset, HI_U32 mute_cr)
{
	U_GFX_MUTE_BK GFX_MUTE_BK;
	
		
	GFX_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_MUTE_BK.u32) + offset));
	GFX_MUTE_BK.bits.mute_cr = mute_cr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_MUTE_BK.u32) + offset),GFX_MUTE_BK.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetSmmuBypassH3d(HI_U32 offset, HI_U32 smmu_bypass_h3d)
{
	U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;
	
	GFX_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SMMU_BYPASS.u32) + offset));
	GFX_SMMU_BYPASS.bits.smmu_bypass_h3d = smmu_bypass_h3d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SMMU_BYPASS.u32) + offset),GFX_SMMU_BYPASS.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetSmmuBypassH2d(HI_U32 offset, HI_U32 smmu_bypass_h2d)
{
	U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;
	
	GFX_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SMMU_BYPASS.u32) + offset));
	GFX_SMMU_BYPASS.bits.smmu_bypass_h2d = smmu_bypass_h2d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SMMU_BYPASS.u32) + offset),GFX_SMMU_BYPASS.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetSmmuBypass3d(HI_U32 offset, HI_U32 smmu_bypass_3d)
{
	U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;
	
		
	GFX_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SMMU_BYPASS.u32) + offset));
	GFX_SMMU_BYPASS.bits.smmu_bypass_3d = smmu_bypass_3d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SMMU_BYPASS.u32) + offset),GFX_SMMU_BYPASS.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetSmmuBypass2d(HI_U32 offset, HI_U32 smmu_bypass_2d)
{
	U_GFX_SMMU_BYPASS GFX_SMMU_BYPASS;
	
		
	GFX_SMMU_BYPASS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SMMU_BYPASS.u32) + offset));
	GFX_SMMU_BYPASS.bits.smmu_bypass_2d = smmu_bypass_2d;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SMMU_BYPASS.u32) + offset),GFX_SMMU_BYPASS.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetAlpha1(HI_U32 offset, HI_U32 alpha_1)
{
	U_GFX_1555_ALPHA GFX_1555_ALPHA;
	
		
	GFX_1555_ALPHA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_1555_ALPHA.u32) + offset));
	GFX_1555_ALPHA.bits.alpha_1 = alpha_1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_1555_ALPHA.u32) + offset),GFX_1555_ALPHA.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetAlpha0(HI_U32 offset, HI_U32 alpha_0)
{
	U_GFX_1555_ALPHA GFX_1555_ALPHA;
	
		
	GFX_1555_ALPHA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_1555_ALPHA.u32) + offset));
	GFX_1555_ALPHA.bits.alpha_0 = alpha_0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_1555_ALPHA.u32) + offset),GFX_1555_ALPHA.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetFrameSize0(HI_U32 offset, HI_U32 frame_size0)
{
	U_GFX_DCMP_FRAMESIZE0 GFX_DCMP_FRAMESIZE0;
	
	GFX_DCMP_FRAMESIZE0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_DCMP_FRAMESIZE0.u32) + offset));
	GFX_DCMP_FRAMESIZE0.bits.frame_size0 = frame_size0;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_DCMP_FRAMESIZE0.u32) + offset),GFX_DCMP_FRAMESIZE0.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetFrameSize1(HI_U32 offset, HI_U32 frame_size1)
{
	U_GFX_DCMP_FRAMESIZE1 GFX_DCMP_FRAMESIZE1;
	
	GFX_DCMP_FRAMESIZE1.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_DCMP_FRAMESIZE1.u32) + offset));
	GFX_DCMP_FRAMESIZE1.bits.frame_size1 = frame_size1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_DCMP_FRAMESIZE1.u32) + offset),GFX_DCMP_FRAMESIZE1.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetDcmpType(HI_U32 offset, HI_U32 dcmp_type)
{
	U_GFX_SRC_INFO GFX_SRC_INFO;
	
		
	GFX_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SRC_INFO.u32) + offset));
	GFX_SRC_INFO.bits.dcmp_type = dcmp_type;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SRC_INFO.u32) + offset),GFX_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetDispMode(HI_U32 offset, HI_U32 disp_mode)
{
	U_GFX_SRC_INFO GFX_SRC_INFO;
	
		
	GFX_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SRC_INFO.u32) + offset));
	GFX_SRC_INFO.bits.disp_mode = disp_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SRC_INFO.u32) + offset),GFX_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetTyp(HI_U32 offset, HI_U32 typ)
{
	U_GFX_SRC_INFO GFX_SRC_INFO;
	
		
	GFX_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SRC_INFO.u32) + offset));
	GFX_SRC_INFO.bits.typ = typ;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SRC_INFO.u32) + offset),GFX_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetIfmt(HI_U32 offset, HI_U32 ifmt)
{
	U_GFX_SRC_INFO GFX_SRC_INFO;
	
		
	GFX_SRC_INFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SRC_INFO.u32) + offset));
	GFX_SRC_INFO.bits.ifmt = ifmt;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SRC_INFO.u32) + offset),GFX_SRC_INFO.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetSrcH(HI_U32 offset, HI_U32 src_h)
{
	U_GFX_SRC_RESO GFX_SRC_RESO;
	
		
	GFX_SRC_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SRC_RESO.u32) + offset));
	GFX_SRC_RESO.bits.src_h = src_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SRC_RESO.u32) + offset),GFX_SRC_RESO.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetSrcW(HI_U32 offset, HI_U32 src_w)
{
	U_GFX_SRC_RESO GFX_SRC_RESO;
	
		
	GFX_SRC_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SRC_RESO.u32) + offset));
	GFX_SRC_RESO.bits.src_w = src_w;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SRC_RESO.u32) + offset),GFX_SRC_RESO.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetSrcCropY(HI_U32 offset, HI_U32 src_crop_y)
{
	U_GFX_SRC_CROP GFX_SRC_CROP;
	
		
	GFX_SRC_CROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SRC_CROP.u32) + offset));
	GFX_SRC_CROP.bits.src_crop_y = src_crop_y;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SRC_CROP.u32) + offset),GFX_SRC_CROP.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetSrcCropX(HI_U32 offset, HI_U32 src_crop_x)
{
	U_GFX_SRC_CROP GFX_SRC_CROP;
	
		
	GFX_SRC_CROP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_SRC_CROP.u32) + offset));
	GFX_SRC_CROP.bits.src_crop_x = src_crop_x;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_SRC_CROP.u32) + offset),GFX_SRC_CROP.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetIresoH(HI_U32 offset, HI_U32 ireso_h)
{
	U_GFX_IRESO GFX_IRESO;
	
		
	GFX_IRESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_IRESO.u32) + offset));
	GFX_IRESO.bits.ireso_h = ireso_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_IRESO.u32) + offset),GFX_IRESO.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetIresoW(HI_U32 offset, HI_U32 ireso_w)
{
	U_GFX_IRESO GFX_IRESO;
	
		
	GFX_IRESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_IRESO.u32) + offset));
	GFX_IRESO.bits.ireso_w = ireso_w;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_IRESO.u32) + offset),GFX_IRESO.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetGfxAddrH(HI_U32 offset, HI_U32 gfx_addr_h)
{
	U_GFX_ADDR_H GFX_ADDR_H;
	
		
	GFX_ADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_ADDR_H.u32) + offset));
	GFX_ADDR_H.bits.gfx_addr_h = gfx_addr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_ADDR_H.u32) + offset),GFX_ADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetGfxAddrL(HI_U32 offset, HI_U32 gfx_addr_l)
{
	U_GFX_ADDR_L GFX_ADDR_L;
	
		
	GFX_ADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_ADDR_L.u32) + offset));
	GFX_ADDR_L.bits.gfx_addr_l = gfx_addr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_ADDR_L.u32) + offset),GFX_ADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetGfxNaddrH(HI_U32 offset, HI_U32 gfx_naddr_h)
{
	U_GFX_NADDR_H GFX_NADDR_H;
	
		
	GFX_NADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_NADDR_H.u32) + offset));
	GFX_NADDR_H.bits.gfx_naddr_h = gfx_naddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_NADDR_H.u32) + offset),GFX_NADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetGfxNaddrL(HI_U32 offset, HI_U32 gfx_naddr_l)
{
	U_GFX_NADDR_L GFX_NADDR_L;
	
		
	GFX_NADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_NADDR_L.u32) + offset));
	GFX_NADDR_L.bits.gfx_naddr_l = gfx_naddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_NADDR_L.u32) + offset),GFX_NADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetDcmpStride(HI_U32 offset, HI_U32 dcmp_stride)
{
	U_GFX_STRIDE GFX_STRIDE;
	
	GFX_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_STRIDE.u32) + offset));
	GFX_STRIDE.bits.dcmp_stride = dcmp_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_STRIDE.u32) + offset),GFX_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetSurfaceStride(HI_U32 offset, HI_U32 surface_stride)
{
	U_GFX_STRIDE GFX_STRIDE;
	
		
	GFX_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_STRIDE.u32) + offset));
	GFX_STRIDE.bits.surface_stride = surface_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_STRIDE.u32) + offset),GFX_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetDcmpAddrH(HI_U32 offset, HI_U32 dcmp_addr_h)
{
	U_GFX_DCMP_ADDR_H GFX_DCMP_ADDR_H;
	
		
	GFX_DCMP_ADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_DCMP_ADDR_H.u32) + offset));
	GFX_DCMP_ADDR_H.bits.dcmp_addr_h = dcmp_addr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_DCMP_ADDR_H.u32) + offset),GFX_DCMP_ADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetDcmpAddrL(HI_U32 offset, HI_U32 dcmp_addr_l)
{
	U_GFX_DCMP_ADDR_L GFX_DCMP_ADDR_L;
	
		
	GFX_DCMP_ADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_DCMP_ADDR_L.u32) + offset));
	GFX_DCMP_ADDR_L.bits.dcmp_addr_l = dcmp_addr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_DCMP_ADDR_L.u32) + offset),GFX_DCMP_ADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetDcmpNaddrH(HI_U32 offset, HI_U32 dcmp_naddr_h)
{
	U_GFX_DCMP_NADDR_H GFX_DCMP_NADDR_H;
	
		
	GFX_DCMP_NADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_DCMP_NADDR_H.u32) + offset));
	GFX_DCMP_NADDR_H.bits.dcmp_naddr_h = dcmp_naddr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_DCMP_NADDR_H.u32) + offset),GFX_DCMP_NADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetDcmpNaddrL(HI_U32 offset, HI_U32 dcmp_naddr_l)
{
	U_GFX_DCMP_NADDR_L GFX_DCMP_NADDR_L;
	
		
	GFX_DCMP_NADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_DCMP_NADDR_L.u32) + offset));
	GFX_DCMP_NADDR_L.bits.dcmp_naddr_l = dcmp_naddr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_DCMP_NADDR_L.u32) + offset),GFX_DCMP_NADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetHAddrH(HI_U32 offset, HI_U32 h_addr_h)
{
	U_GFX_HEAD_ADDR_H GFX_HEAD_ADDR_H;
	
	GFX_HEAD_ADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_HEAD_ADDR_H.u32) + offset));
	GFX_HEAD_ADDR_H.bits.h_addr_h = h_addr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_HEAD_ADDR_H.u32) + offset),GFX_HEAD_ADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetHAddrL(HI_U32 offset, HI_U32 h_addr_l)
{
	U_GFX_HEAD_ADDR_L GFX_HEAD_ADDR_L;
	
	GFX_HEAD_ADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_HEAD_ADDR_L.u32) + offset));
	GFX_HEAD_ADDR_L.bits.h_addr_l = h_addr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_HEAD_ADDR_L.u32) + offset),GFX_HEAD_ADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetHead2Stride(HI_U32 offset, HI_U32 head2_stride)
{
	U_GFX_HEAD_STRIDE GFX_HEAD_STRIDE;
	
	GFX_HEAD_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_HEAD_STRIDE.u32) + offset));
	GFX_HEAD_STRIDE.bits.head2_stride = head2_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_HEAD_STRIDE.u32) + offset),GFX_HEAD_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetHeadStride(HI_U32 offset, HI_U32 head_stride)
{
	U_GFX_HEAD_STRIDE GFX_HEAD_STRIDE;
	
	GFX_HEAD_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_HEAD_STRIDE.u32) + offset));
	GFX_HEAD_STRIDE.bits.head_stride = head_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_HEAD_STRIDE.u32) + offset),GFX_HEAD_STRIDE.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetH2AddrH(HI_U32 offset, HI_U32 h2_addr_h)
{
	U_GFX_HEAD2_ADDR_H GFX_HEAD2_ADDR_H;
	
	GFX_HEAD2_ADDR_H.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_HEAD2_ADDR_H.u32) + offset));
	GFX_HEAD2_ADDR_H.bits.h2_addr_h = h2_addr_h;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_HEAD2_ADDR_H.u32) + offset),GFX_HEAD2_ADDR_H.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetH2AddrL(HI_U32 offset, HI_U32 h2_addr_l)
{
	U_GFX_HEAD2_ADDR_L GFX_HEAD2_ADDR_L;
	
	GFX_HEAD2_ADDR_L.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_HEAD2_ADDR_L.u32) + offset));
	GFX_HEAD2_ADDR_L.bits.h2_addr_l = h2_addr_l;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_HEAD2_ADDR_L.u32) + offset),GFX_HEAD2_ADDR_L.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyRMax(HI_U32 offset, HI_U32 key_r_max)
{
	U_GFX_CKEY_MAX GFX_CKEY_MAX;
	
		
	GFX_CKEY_MAX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_CKEY_MAX.u32) + offset));
	GFX_CKEY_MAX.bits.key_r_max = key_r_max;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_CKEY_MAX.u32) + offset),GFX_CKEY_MAX.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyGMax(HI_U32 offset, HI_U32 key_g_max)
{
	U_GFX_CKEY_MAX GFX_CKEY_MAX;
	
		
	GFX_CKEY_MAX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_CKEY_MAX.u32) + offset));
	GFX_CKEY_MAX.bits.key_g_max = key_g_max;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_CKEY_MAX.u32) + offset),GFX_CKEY_MAX.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyBMax(HI_U32 offset, HI_U32 key_b_max)
{
	U_GFX_CKEY_MAX GFX_CKEY_MAX;
	
		
	GFX_CKEY_MAX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_CKEY_MAX.u32) + offset));
	GFX_CKEY_MAX.bits.key_b_max = key_b_max;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_CKEY_MAX.u32) + offset),GFX_CKEY_MAX.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyRMin(HI_U32 offset, HI_U32 key_r_min)
{
	U_GFX_CKEY_MIN GFX_CKEY_MIN;
	
		
	GFX_CKEY_MIN.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_CKEY_MIN.u32) + offset));
	GFX_CKEY_MIN.bits.key_r_min = key_r_min;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_CKEY_MIN.u32) + offset),GFX_CKEY_MIN.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyGMin(HI_U32 offset, HI_U32 key_g_min)
{
	U_GFX_CKEY_MIN GFX_CKEY_MIN;
	
		
	GFX_CKEY_MIN.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_CKEY_MIN.u32) + offset));
	GFX_CKEY_MIN.bits.key_g_min = key_g_min;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_CKEY_MIN.u32) + offset),GFX_CKEY_MIN.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyBMin(HI_U32 offset, HI_U32 key_b_min)
{
	U_GFX_CKEY_MIN GFX_CKEY_MIN;
	
		
	GFX_CKEY_MIN.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_CKEY_MIN.u32) + offset));
	GFX_CKEY_MIN.bits.key_b_min = key_b_min;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_CKEY_MIN.u32) + offset),GFX_CKEY_MIN.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyRMsk(HI_U32 offset, HI_U32 key_r_msk)
{
	U_GFX_CKEY_MASK GFX_CKEY_MASK;
	
		
	GFX_CKEY_MASK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_CKEY_MASK.u32) + offset));
	GFX_CKEY_MASK.bits.key_r_msk = key_r_msk;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_CKEY_MASK.u32) + offset),GFX_CKEY_MASK.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyGMsk(HI_U32 offset, HI_U32 key_g_msk)
{
	U_GFX_CKEY_MASK GFX_CKEY_MASK;
	
		
	GFX_CKEY_MASK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_CKEY_MASK.u32) + offset));
	GFX_CKEY_MASK.bits.key_g_msk = key_g_msk;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_CKEY_MASK.u32) + offset),GFX_CKEY_MASK.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetKeyBMsk(HI_U32 offset, HI_U32 key_b_msk)
{
	U_GFX_CKEY_MASK GFX_CKEY_MASK;
	
		
	GFX_CKEY_MASK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_CKEY_MASK.u32) + offset));
	GFX_CKEY_MASK.bits.key_b_msk = key_b_msk;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_CKEY_MASK.u32) + offset),GFX_CKEY_MASK.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetTpMode(HI_U32 offset, HI_U32 tp_mode)
{
	U_GFX_TESTPAT_CFG GFX_TESTPAT_CFG;
	
		
	GFX_TESTPAT_CFG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_CFG.u32) + offset));
	GFX_TESTPAT_CFG.bits.tp_mode = tp_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_CFG.u32) + offset),GFX_TESTPAT_CFG.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetTpColorMode(HI_U32 offset, HI_U32 tp_color_mode)
{
	U_GFX_TESTPAT_CFG GFX_TESTPAT_CFG;
	
		
	GFX_TESTPAT_CFG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_CFG.u32) + offset));
	GFX_TESTPAT_CFG.bits.tp_color_mode = tp_color_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_CFG.u32) + offset),GFX_TESTPAT_CFG.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetTpLineW(HI_U32 offset, HI_U32 tp_line_w)
{
	U_GFX_TESTPAT_CFG GFX_TESTPAT_CFG;
	
		
	GFX_TESTPAT_CFG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_CFG.u32) + offset));
	GFX_TESTPAT_CFG.bits.tp_line_w = tp_line_w;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_CFG.u32) + offset),GFX_TESTPAT_CFG.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetTpSpeed(HI_U32 offset, HI_U32 tp_speed)
{
	U_GFX_TESTPAT_CFG GFX_TESTPAT_CFG;
	
		
	GFX_TESTPAT_CFG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_CFG.u32) + offset));
	GFX_TESTPAT_CFG.bits.tp_speed = tp_speed;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_CFG.u32) + offset),GFX_TESTPAT_CFG.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetTpSeed(HI_U32 offset, HI_U32 tp_seed)
{
	U_GFX_TESTPAT_SEED GFX_TESTPAT_SEED;
	
		
	GFX_TESTPAT_SEED.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_SEED.u32) + offset));
	GFX_TESTPAT_SEED.bits.tp_seed = tp_seed;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_TESTPAT_SEED.u32) + offset),GFX_TESTPAT_SEED.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetFdrPressEn(HI_U32 offset, HI_U32 fdr_press_en)
{
	U_GFX_DEBUG_CTRL GFX_DEBUG_CTRL;
	
	GFX_DEBUG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_DEBUG_CTRL.u32) + offset));
	GFX_DEBUG_CTRL.bits.fdr_press_en = fdr_press_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_DEBUG_CTRL.u32) + offset),GFX_DEBUG_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetChecksumEn(HI_U32 offset, HI_U32 checksum_en)
{
	U_GFX_DEBUG_CTRL GFX_DEBUG_CTRL;
	
	GFX_DEBUG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_DEBUG_CTRL.u32) + offset));
	GFX_DEBUG_CTRL.bits.checksum_en = checksum_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_DEBUG_CTRL.u32) + offset),GFX_DEBUG_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetScopeDrdyNum(HI_U32 offset, HI_U32 scope_drdy_num)
{
	U_GFX_PRESS_CTRL GFX_PRESS_CTRL;
	
	GFX_PRESS_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_PRESS_CTRL.u32) + offset));
	GFX_PRESS_CTRL.bits.scope_drdy_num = scope_drdy_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_PRESS_CTRL.u32) + offset),GFX_PRESS_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetMinDrdyNum(HI_U32 offset, HI_U32 min_drdy_num)
{
	U_GFX_PRESS_CTRL GFX_PRESS_CTRL;
	
	GFX_PRESS_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_PRESS_CTRL.u32) + offset));
	GFX_PRESS_CTRL.bits.min_drdy_num = min_drdy_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_PRESS_CTRL.u32) + offset),GFX_PRESS_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetScopeNodrdyNum(HI_U32 offset, HI_U32 scope_nodrdy_num)
{
	U_GFX_PRESS_CTRL GFX_PRESS_CTRL;
	
	GFX_PRESS_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_PRESS_CTRL.u32) + offset));
	GFX_PRESS_CTRL.bits.scope_nodrdy_num = scope_nodrdy_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_PRESS_CTRL.u32) + offset),GFX_PRESS_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetMinNodrdyNum(HI_U32 offset, HI_U32 min_nodrdy_num)
{
	U_GFX_PRESS_CTRL GFX_PRESS_CTRL;
	
	GFX_PRESS_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GFX_PRESS_CTRL.u32) + offset));
	GFX_PRESS_CTRL.bits.min_nodrdy_num = min_nodrdy_num;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->GFX_PRESS_CTRL.u32) + offset),GFX_PRESS_CTRL.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetWrongGb(HI_U32 offset, HI_U32 wrong_gb)
{
	U_DCMP_WRONG_STA DCMP_WRONG_STA;

	DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset));
	DCMP_WRONG_STA.bits.wrong_gb = wrong_gb;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset),DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetConsumeGb(HI_U32 offset, HI_U32 consume_gb)
{
	U_DCMP_WRONG_STA DCMP_WRONG_STA;

	DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset));
	DCMP_WRONG_STA.bits.consume_gb = consume_gb;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset),DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetForgiveGb(HI_U32 offset, HI_U32 forgive_gb)
{
	U_DCMP_WRONG_STA DCMP_WRONG_STA;

	DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset));
	DCMP_WRONG_STA.bits.forgive_gb = forgive_gb;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset),DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetWrongAr(HI_U32 offset, HI_U32 wrong_ar)
{
	U_DCMP_WRONG_STA DCMP_WRONG_STA;

	DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset));
	DCMP_WRONG_STA.bits.wrong_ar = wrong_ar;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset),DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetConsumeAr(HI_U32 offset, HI_U32 consume_ar)
{
	U_DCMP_WRONG_STA DCMP_WRONG_STA;

	DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset));
	DCMP_WRONG_STA.bits.consume_ar = consume_ar;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset),DCMP_WRONG_STA.u32);
	
	return ;
}


HI_VOID VDP_FDR_GFX_SetForgiveAr(HI_U32 offset, HI_U32 forgive_ar)
{
	U_DCMP_WRONG_STA DCMP_WRONG_STA;

	DCMP_WRONG_STA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset));
	DCMP_WRONG_STA.bits.forgive_ar = forgive_ar;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->DCMP_WRONG_STA.u32) + offset),DCMP_WRONG_STA.u32);
	
	return ;
}
