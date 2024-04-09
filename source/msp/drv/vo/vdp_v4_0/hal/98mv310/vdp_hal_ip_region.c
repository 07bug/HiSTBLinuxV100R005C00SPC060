#include "vdp_hal_comm.h"
#include "vdp_hal_ip_region.h"

extern S_VDP_REGS_TYPE *pVdpReg;


HI_VOID VDP_FDR_VID_SetMrgRdEn(HI_U32 offset, HI_U32 rd_en)
{
	U_V1_MRG_READ_EN V1_MRG_READ_EN;

	V1_MRG_READ_EN.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_READ_EN.u32) + offset));
	V1_MRG_READ_EN.bits.rd_en = rd_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_READ_EN.u32) + offset),V1_MRG_READ_EN.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgRdRegion(HI_U32 offset, HI_U32 rd_region)
{
	U_V1_MRG_READ_CTRL V1_MRG_READ_CTRL;

	V1_MRG_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_READ_CTRL.u32) + offset));
	V1_MRG_READ_CTRL.bits.rd_region = rd_region;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_READ_CTRL.u32) + offset),V1_MRG_READ_CTRL.u32);

	return ;
}

HI_VOID VDP_FDR_VID_SetMrgLoadMode(HI_U32 offset, HI_U32 load_mode)
{
	U_V1_MRG_READ_CTRL V1_MRG_READ_CTRL;

	V1_MRG_READ_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_READ_CTRL.u32)));
	V1_MRG_READ_CTRL.bits.load_mode = load_mode;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_READ_CTRL.u32)),V1_MRG_READ_CTRL.u32);

	return ;
}

HI_VOID VDP_FDR_VID_SetMrgEn(HI_U32 offset, HI_U32 mrg_en)
{
	U_V1_MRG_CTRL V1_MRG_CTRL;

	V1_MRG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset));
	V1_MRG_CTRL.bits.mrg_en = mrg_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset),V1_MRG_CTRL.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgMuteEn(HI_U32 offset, HI_U32 mrg_mute_en)
{
	U_V1_MRG_CTRL V1_MRG_CTRL;

	V1_MRG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset));
	V1_MRG_CTRL.bits.mrg_mute_en = mrg_mute_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset),V1_MRG_CTRL.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgLmMmuBypass(HI_U32 offset, HI_U32 mrg_mmu_bypass)
{
	U_V1_MRG_CTRL V1_MRG_CTRL;

	V1_MRG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset));
	V1_MRG_CTRL.bits.mrg_lm_mmu_bypass = mrg_mmu_bypass;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset),V1_MRG_CTRL.u32);

	return ;
}

HI_VOID VDP_FDR_VID_SetMrgChmMmuBypass(HI_U32 offset, HI_U32 mrg_mmu_bypass)
{
	U_V1_MRG_CTRL V1_MRG_CTRL;

	V1_MRG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset));
	V1_MRG_CTRL.bits.mrg_chm_mmu_bypass = mrg_mmu_bypass;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset),V1_MRG_CTRL.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgCropEn(HI_U32 offset, HI_U32 mrg_crop_en)
{
	U_V1_MRG_CTRL V1_MRG_CTRL;

	V1_MRG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset));
	V1_MRG_CTRL.bits.mrg_crop_en = mrg_crop_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset),V1_MRG_CTRL.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgEdgeTyp(HI_U32 offset, HI_U32 mrg_edge_typ)
{
	U_V1_MRG_CTRL V1_MRG_CTRL;

	V1_MRG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset));
	V1_MRG_CTRL.bits.mrg_edge_typ = mrg_edge_typ;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset),V1_MRG_CTRL.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgEdgeEn(HI_U32 offset, HI_U32 mrg_edge_en)
{
	U_V1_MRG_CTRL V1_MRG_CTRL;

	V1_MRG_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset));
	V1_MRG_CTRL.bits.mrg_edge_en = mrg_edge_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_CTRL.u32) + offset),V1_MRG_CTRL.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgYpos(HI_U32 offset, HI_U32 mrg_ypos)
{
	U_V1_MRG_DISP_POS V1_MRG_DISP_POS;

	V1_MRG_DISP_POS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_DISP_POS.u32) + offset));
	V1_MRG_DISP_POS.bits.mrg_ypos = mrg_ypos;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_DISP_POS.u32) + offset),V1_MRG_DISP_POS.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgXpos(HI_U32 offset, HI_U32 mrg_xpos)
{
	U_V1_MRG_DISP_POS V1_MRG_DISP_POS;

	V1_MRG_DISP_POS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_DISP_POS.u32) + offset));
	V1_MRG_DISP_POS.bits.mrg_xpos = mrg_xpos;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_DISP_POS.u32) + offset),V1_MRG_DISP_POS.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgHeight(HI_U32 offset, HI_U32 mrg_height)
{
	U_V1_MRG_DISP_RESO V1_MRG_DISP_RESO;

	V1_MRG_DISP_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_DISP_RESO.u32) + offset));
	V1_MRG_DISP_RESO.bits.mrg_height = mrg_height;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_DISP_RESO.u32) + offset),V1_MRG_DISP_RESO.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgWidth(HI_U32 offset, HI_U32 mrg_width)
{
	U_V1_MRG_DISP_RESO V1_MRG_DISP_RESO;

	V1_MRG_DISP_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_DISP_RESO.u32) + offset));
	V1_MRG_DISP_RESO.bits.mrg_width = mrg_width;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_DISP_RESO.u32) + offset),V1_MRG_DISP_RESO.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgSrcHeight(HI_U32 offset, HI_U32 mrg_src_height)
{
	U_V1_MRG_SRC_RESO V1_MRG_SRC_RESO;

	V1_MRG_SRC_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_SRC_RESO.u32) + offset));
	V1_MRG_SRC_RESO.bits.mrg_src_height = mrg_src_height;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_SRC_RESO.u32) + offset),V1_MRG_SRC_RESO.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgSrcWidth(HI_U32 offset, HI_U32 mrg_src_width)
{
	U_V1_MRG_SRC_RESO V1_MRG_SRC_RESO;

	V1_MRG_SRC_RESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_SRC_RESO.u32) + offset));
	V1_MRG_SRC_RESO.bits.mrg_src_width = mrg_src_width;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_SRC_RESO.u32) + offset),V1_MRG_SRC_RESO.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgSrcVoffset(HI_U32 offset, HI_U32 mrg_src_voffset)
{
	U_V1_MRG_SRC_OFFSET V1_MRG_SRC_OFFSET;

	V1_MRG_SRC_OFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_SRC_OFFSET.u32) + offset));
	V1_MRG_SRC_OFFSET.bits.mrg_src_voffset = mrg_src_voffset;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_SRC_OFFSET.u32) + offset),V1_MRG_SRC_OFFSET.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgSrcHoffset(HI_U32 offset, HI_U32 mrg_src_hoffset)
{
	U_V1_MRG_SRC_OFFSET V1_MRG_SRC_OFFSET;

	V1_MRG_SRC_OFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_SRC_OFFSET.u32) + offset));
	V1_MRG_SRC_OFFSET.bits.mrg_src_hoffset = mrg_src_hoffset;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_SRC_OFFSET.u32) + offset),V1_MRG_SRC_OFFSET.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgYAddr(HI_U32 offset, HI_U32 mrg_y_addr)
{
	U_V1_MRG_Y_ADDR V1_MRG_Y_ADDR;

	V1_MRG_Y_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_Y_ADDR.u32) + offset));
	V1_MRG_Y_ADDR.bits.mrg_y_addr = mrg_y_addr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_Y_ADDR.u32) + offset),V1_MRG_Y_ADDR.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgCAddr(HI_U32 offset, HI_U32 mrg_c_addr)
{
	U_V1_MRG_C_ADDR V1_MRG_C_ADDR;

	V1_MRG_C_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_C_ADDR.u32) + offset));
	V1_MRG_C_ADDR.bits.mrg_c_addr = mrg_c_addr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_C_ADDR.u32) + offset),V1_MRG_C_ADDR.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgYStride(HI_U32 offset, HI_U32 mrg_y_stride)
{
	U_V1_MRG_STRIDE V1_MRG_STRIDE;

	V1_MRG_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_STRIDE.u32) + offset));
	V1_MRG_STRIDE.bits.mrg_y_stride = mrg_y_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_STRIDE.u32) + offset),V1_MRG_STRIDE.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgCStride(HI_U32 offset, HI_U32 mrg_c_stride)
{
	U_V1_MRG_STRIDE V1_MRG_STRIDE;

	V1_MRG_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_STRIDE.u32) + offset));
	V1_MRG_STRIDE.bits.mrg_c_stride = mrg_c_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_STRIDE.u32) + offset),V1_MRG_STRIDE.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgYhAddr(HI_U32 offset, HI_U32 mrg_yh_addr)
{
	U_V1_MRG_YH_ADDR V1_MRG_YH_ADDR;

	V1_MRG_YH_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_YH_ADDR.u32) + offset));
	V1_MRG_YH_ADDR.bits.mrg_yh_addr = mrg_yh_addr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_YH_ADDR.u32) + offset),V1_MRG_YH_ADDR.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgChAddr(HI_U32 offset, HI_U32 mrg_ch_addr)
{
	U_V1_MRG_CH_ADDR V1_MRG_CH_ADDR;

	V1_MRG_CH_ADDR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_CH_ADDR.u32) + offset));
	V1_MRG_CH_ADDR.bits.mrg_ch_addr = mrg_ch_addr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_CH_ADDR.u32) + offset),V1_MRG_CH_ADDR.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgYhStride(HI_U32 offset, HI_U32 mrg_yh_stride)
{
	U_V1_MRG_HSTRIDE V1_MRG_HSTRIDE;

	V1_MRG_HSTRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_HSTRIDE.u32) + offset));
	V1_MRG_HSTRIDE.bits.mrg_yh_stride = mrg_yh_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_HSTRIDE.u32) + offset),V1_MRG_HSTRIDE.u32);

	return ;
}


HI_VOID VDP_FDR_VID_SetMrgChStride(HI_U32 offset, HI_U32 mrg_ch_stride)
{
	U_V1_MRG_HSTRIDE V1_MRG_HSTRIDE;

	V1_MRG_HSTRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_MRG_HSTRIDE.u32) + offset));
	V1_MRG_HSTRIDE.bits.mrg_ch_stride = mrg_ch_stride;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_MRG_HSTRIDE.u32) + offset),V1_MRG_HSTRIDE.u32);

	return ;
}




