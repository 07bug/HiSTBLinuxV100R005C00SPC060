#include "vdp_hal_ip_wd_zme.h"
#include "vdp_hal_comm.h"


extern volatile S_VDP_REGS_TYPE* pVdpReg;

HI_VOID VDP_WBC_VZME_SetCkGtEn(HI_U32 ck_gt_en)
{
	U_WBC_DHD0_ZME_VINFO WBC_DHD0_ZME_VINFO;
	
	WBC_DHD0_ZME_VINFO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32));
	WBC_DHD0_ZME_VINFO.bits.ck_gt_en = ck_gt_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32),WBC_DHD0_ZME_VINFO.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetOutFld(HI_U32 out_fld)
{
	U_WBC_DHD0_ZME_VINFO WBC_DHD0_ZME_VINFO;
	
	WBC_DHD0_ZME_VINFO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32));
	WBC_DHD0_ZME_VINFO.bits.out_fld = out_fld;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32),WBC_DHD0_ZME_VINFO.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetOutPro(HI_U32 out_pro)
{
	U_WBC_DHD0_ZME_VINFO WBC_DHD0_ZME_VINFO;
	
	WBC_DHD0_ZME_VINFO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32));
	WBC_DHD0_ZME_VINFO.bits.out_pro = out_pro;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32),WBC_DHD0_ZME_VINFO.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetOutHeight(HI_U32 out_height)
{
	U_WBC_DHD0_ZME_VINFO WBC_DHD0_ZME_VINFO;
	
	WBC_DHD0_ZME_VINFO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32));
	WBC_DHD0_ZME_VINFO.bits.out_height = out_height;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VINFO.u32),WBC_DHD0_ZME_VINFO.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVlmscEn(HI_U32 vlmsc_en)
{
	U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
	
	WBC_DHD0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32));
	WBC_DHD0_ZME_VSP.bits.vlmsc_en = vlmsc_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32),WBC_DHD0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVchmscEn(HI_U32 vchmsc_en)
{
	U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
	
	WBC_DHD0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32));
	WBC_DHD0_ZME_VSP.bits.vchmsc_en = vchmsc_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32),WBC_DHD0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVlmidEn(HI_U32 vlmid_en)
{
	U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
	
	WBC_DHD0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32));
	WBC_DHD0_ZME_VSP.bits.vlmid_en = vlmid_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32),WBC_DHD0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVchmidEn(HI_U32 vchmid_en)
{
	U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
	
	WBC_DHD0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32));
	WBC_DHD0_ZME_VSP.bits.vchmid_en = vchmid_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32),WBC_DHD0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVlfirEn(HI_U32 vlfir_en)
{
	U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
	
	WBC_DHD0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32));
	WBC_DHD0_ZME_VSP.bits.vlfir_en = vlfir_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32),WBC_DHD0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVchfirEn(HI_U32 vchfir_en)
{
	U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
	
	WBC_DHD0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32));
	WBC_DHD0_ZME_VSP.bits.vchfir_en = vchfir_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32),WBC_DHD0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetZmeOutFmt(HI_U32 zme_out_fmt)
{
	U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
	
	WBC_DHD0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32));
	WBC_DHD0_ZME_VSP.bits.zme_out_fmt = zme_out_fmt;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32),WBC_DHD0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetZmeInFmt(HI_U32 zme_in_fmt)
{
	U_WBC_DHD0_ZME_VSP WBC_DHD0_ZME_VSP;
	
	WBC_DHD0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32));
	WBC_DHD0_ZME_VSP.bits.zme_in_fmt = zme_in_fmt;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSP.u32),WBC_DHD0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVratio(HI_U32 vratio)
{
	U_WBC_DHD0_ZME_VSR WBC_DHD0_ZME_VSR;
	
	WBC_DHD0_ZME_VSR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSR.u32));
	WBC_DHD0_ZME_VSR.bits.vratio = vratio;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VSR.u32),WBC_DHD0_ZME_VSR.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVlumaOffset(HI_U32 vluma_offset)
{
	U_WBC_DHD0_ZME_VOFFSET WBC_DHD0_ZME_VOFFSET;
	
	WBC_DHD0_ZME_VOFFSET.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32));
	WBC_DHD0_ZME_VOFFSET.bits.vluma_offset = vluma_offset;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32),WBC_DHD0_ZME_VOFFSET.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVchromaOffset(HI_U32 vchroma_offset)
{
	U_WBC_DHD0_ZME_VOFFSET WBC_DHD0_ZME_VOFFSET;
	
	WBC_DHD0_ZME_VOFFSET.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32));
	WBC_DHD0_ZME_VOFFSET.bits.vchroma_offset = vchroma_offset;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VOFFSET.u32),WBC_DHD0_ZME_VOFFSET.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVblumaOffset(HI_U32 vbluma_offset)
{
	U_WBC_DHD0_ZME_VBOFFSET WBC_DHD0_ZME_VBOFFSET;
	
	WBC_DHD0_ZME_VBOFFSET.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32));
	WBC_DHD0_ZME_VBOFFSET.bits.vbluma_offset = vbluma_offset;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32),WBC_DHD0_ZME_VBOFFSET.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetVbchromaOffset(HI_U32 vbchroma_offset)
{
	U_WBC_DHD0_ZME_VBOFFSET WBC_DHD0_ZME_VBOFFSET;
	
	WBC_DHD0_ZME_VBOFFSET.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32));
	WBC_DHD0_ZME_VBOFFSET.bits.vbchroma_offset = vbchroma_offset;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VBOFFSET.u32),WBC_DHD0_ZME_VBOFFSET.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetApbVhdVfLren(HI_U32 apb_vhd_vf_lren)
{
	U_WBC_DHD0_ZME_VCOEF WBC_DHD0_ZME_VCOEF;
	
	WBC_DHD0_ZME_VCOEF.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VCOEF.u32));
	WBC_DHD0_ZME_VCOEF.bits.apb_vhd_vf_lren = apb_vhd_vf_lren;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VCOEF.u32),WBC_DHD0_ZME_VCOEF.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetApbVhdVfCren(HI_U32 apb_vhd_vf_cren)
{
	U_WBC_DHD0_ZME_VCOEF WBC_DHD0_ZME_VCOEF;
	
	WBC_DHD0_ZME_VCOEF.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VCOEF.u32));
	WBC_DHD0_ZME_VCOEF.bits.apb_vhd_vf_cren = apb_vhd_vf_cren;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VCOEF.u32),WBC_DHD0_ZME_VCOEF.u32);
	
	return ;
}


HI_VOID VDP_WBC_VZME_SetApbVhdVcoefRaddr(HI_U32 apb_vhd_vcoef_raddr)
{
	U_WBC_DHD0_ZME_VCOEFAD WBC_DHD0_ZME_VCOEFAD;
	
	WBC_DHD0_ZME_VCOEFAD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VCOEFAD.u32));
	WBC_DHD0_ZME_VCOEFAD.bits.apb_vhd_vcoef_raddr = apb_vhd_vcoef_raddr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_VCOEFAD.u32),WBC_DHD0_ZME_VCOEFAD.u32);
	
	return ;
}

#if 1
HI_VOID VDP_WBC_HZME_SetOutFmt(HI_U32 out_fmt)
{
	U_WBC_DHD0_ZME_HINFO WBC_DHD0_ZME_HINFO;
		
	WBC_DHD0_ZME_HINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32)));
	WBC_DHD0_ZME_HINFO.bits.out_fmt = out_fmt;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32)),WBC_DHD0_ZME_HINFO.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetCkGtEn(HI_U32 ck_gt_en)
{
	U_WBC_DHD0_ZME_HINFO WBC_DHD0_ZME_HINFO;
		
	WBC_DHD0_ZME_HINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32)));
	WBC_DHD0_ZME_HINFO.bits.ck_gt_en = ck_gt_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32)),WBC_DHD0_ZME_HINFO.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetOutWidth(HI_U32 out_width)
{
	U_WBC_DHD0_ZME_HINFO WBC_DHD0_ZME_HINFO;
		
	WBC_DHD0_ZME_HINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32)));
	WBC_DHD0_ZME_HINFO.bits.out_width = out_width;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HINFO.u32)),WBC_DHD0_ZME_HINFO.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHlmscEn(HI_U32 hlmsc_en)
{
	U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
		
	WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)));
	WBC_DHD0_ZME_HSP.bits.hlmsc_en = hlmsc_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)),WBC_DHD0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHchmscEn(HI_U32 hchmsc_en)
{
	U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
		
	WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)));
	WBC_DHD0_ZME_HSP.bits.hchmsc_en = hchmsc_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)),WBC_DHD0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHlmidEn(HI_U32 hlmid_en)
{
	U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
		
	WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)));
	WBC_DHD0_ZME_HSP.bits.hlmid_en = hlmid_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)),WBC_DHD0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHchmidEn(HI_U32 hchmid_en)
{
	U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
		
	WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)));
	WBC_DHD0_ZME_HSP.bits.hchmid_en = hchmid_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)),WBC_DHD0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHlfirEn(HI_U32 hlfir_en)
{
	U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
		
	WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)));
	WBC_DHD0_ZME_HSP.bits.hlfir_en = hlfir_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)),WBC_DHD0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHchfirEn(HI_U32 hchfir_en)
{
	U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
		
	WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)));
	WBC_DHD0_ZME_HSP.bits.hchfir_en = hchfir_en;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)),WBC_DHD0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHfirOrder(HI_U32 hfir_order)
{
	U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
		
	WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)));
	WBC_DHD0_ZME_HSP.bits.hfir_order = hfir_order;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)),WBC_DHD0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHratio(HI_U32 hratio)
{
	U_WBC_DHD0_ZME_HSP WBC_DHD0_ZME_HSP;
		
	WBC_DHD0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)));
	WBC_DHD0_ZME_HSP.bits.hratio = hratio;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HSP.u32)),WBC_DHD0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHorLoffset(HI_U32 hor_loffset)
{
	U_WBC_DHD0_ZME_HLOFFSET WBC_DHD0_ZME_HLOFFSET;
		
	WBC_DHD0_ZME_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32)));
	WBC_DHD0_ZME_HLOFFSET.bits.hor_loffset = hor_loffset;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HLOFFSET.u32)),WBC_DHD0_ZME_HLOFFSET.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetHorCoffset(HI_U32 hor_coffset)
{
	U_WBC_DHD0_ZME_HCOFFSET WBC_DHD0_ZME_HCOFFSET;
		
	WBC_DHD0_ZME_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32)));
	WBC_DHD0_ZME_HCOFFSET.bits.hor_coffset = hor_coffset;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HCOFFSET.u32)),WBC_DHD0_ZME_HCOFFSET.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetApbVhdHfLren(HI_U32 apb_vhd_hf_lren)
{
	U_WBC_DHD0_ZME_HRCOEF WBC_DHD0_ZME_HRCOEF;
		
	WBC_DHD0_ZME_HRCOEF.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HRCOEF.u32)));
	WBC_DHD0_ZME_HRCOEF.bits.apb_vhd_hf_lren = apb_vhd_hf_lren;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HRCOEF.u32)),WBC_DHD0_ZME_HRCOEF.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetApbVhdHfCren(HI_U32 apb_vhd_hf_cren)
{
	U_WBC_DHD0_ZME_HRCOEF WBC_DHD0_ZME_HRCOEF;
		
	WBC_DHD0_ZME_HRCOEF.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HRCOEF.u32)));
	WBC_DHD0_ZME_HRCOEF.bits.apb_vhd_hf_cren = apb_vhd_hf_cren;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HRCOEF.u32)),WBC_DHD0_ZME_HRCOEF.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetApbVhdHycoefRaddr(HI_U32 apb_vhd_hycoef_raddr)
{
	U_WBC_DHD0_ZME_HYCOEFAD WBC_DHD0_ZME_HYCOEFAD;
		
	WBC_DHD0_ZME_HYCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HYCOEFAD.u32)));
	WBC_DHD0_ZME_HYCOEFAD.bits.apb_vhd_hycoef_raddr = apb_vhd_hycoef_raddr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HYCOEFAD.u32)),WBC_DHD0_ZME_HYCOEFAD.u32);
	
	return ;
}


HI_VOID VDP_WBC_HZME_SetApbVhdHccoefRaddr(HI_U32 apb_vhd_hccoef_raddr)
{
	U_WBC_DHD0_ZME_HCCOEFAD WBC_DHD0_ZME_HCCOEFAD;
		
	WBC_DHD0_ZME_HCCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HCCOEFAD.u32)));
	WBC_DHD0_ZME_HCCOEFAD.bits.apb_vhd_hccoef_raddr = apb_vhd_hccoef_raddr;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->WBC_DHD0_ZME_HCCOEFAD.u32)),WBC_DHD0_ZME_HCCOEFAD.u32);
	
	return ;
}
#endif

