
#include "vdp_hal_ip_gp_zme.h"
#include "vdp_hal_comm.h"
extern volatile volatile S_VDP_REGS_TYPE* pVdpReg;

HI_VOID VDP_GP_ZME_SetCkGtEn(HI_U32 ck_gt_en)
{
	U_GP0_ZME_HINFO GP0_ZME_HINFO;
	
	GP0_ZME_HINFO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32));
	GP0_ZME_HINFO.bits.ck_gt_en = ck_gt_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32),GP0_ZME_HINFO.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetOutWidth(HI_U32 out_width)
{
	U_GP0_ZME_HINFO GP0_ZME_HINFO;
	
	GP0_ZME_HINFO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32));
	GP0_ZME_HINFO.bits.out_width = out_width;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32),GP0_ZME_HINFO.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHscEn(HI_U32 hsc_en)
{
	U_GP0_ZME_HSP GP0_ZME_HSP;
	
	GP0_ZME_HSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32));
	GP0_ZME_HSP.bits.hsc_en = hsc_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32),GP0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHamidEn(HI_U32 hamid_en)
{
	U_GP0_ZME_HSP GP0_ZME_HSP;
	
	GP0_ZME_HSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32));
	GP0_ZME_HSP.bits.hamid_en = hamid_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32),GP0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHlmidEn(HI_U32 hlmid_en)
{
	U_GP0_ZME_HSP GP0_ZME_HSP;
	
	GP0_ZME_HSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32));
	GP0_ZME_HSP.bits.hlmid_en = hlmid_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32),GP0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHchmidEn(HI_U32 hchmid_en)
{
	U_GP0_ZME_HSP GP0_ZME_HSP;
	
	GP0_ZME_HSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32));
	GP0_ZME_HSP.bits.hchmid_en = hchmid_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32),GP0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHfirEn(HI_U32 hfir_en)
{
	U_GP0_ZME_HSP GP0_ZME_HSP;
	
	GP0_ZME_HSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32));
	GP0_ZME_HSP.bits.hfir_en = hfir_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32),GP0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHafirEn(HI_U32 hafir_en)
{
	U_GP0_ZME_HSP GP0_ZME_HSP;
	
	GP0_ZME_HSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32));
	GP0_ZME_HSP.bits.hafir_en = hafir_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32),GP0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHfirOrder(HI_U32 hfir_order)
{
	U_GP0_ZME_HSP GP0_ZME_HSP;
	
	GP0_ZME_HSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32));
	GP0_ZME_HSP.bits.hfir_order = hfir_order;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32),GP0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHratio(HI_U32 hratio)
{
	U_GP0_ZME_HSP GP0_ZME_HSP;
	
	GP0_ZME_HSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32));
	GP0_ZME_HSP.bits.hratio = hratio;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32),GP0_ZME_HSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHorLoffset(HI_U32 hor_loffset)
{
	U_GP0_ZME_HLOFFSET GP0_ZME_HLOFFSET;
	
	GP0_ZME_HLOFFSET.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HLOFFSET.u32));
	GP0_ZME_HLOFFSET.bits.hor_loffset = hor_loffset;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HLOFFSET.u32),GP0_ZME_HLOFFSET.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetHorCoffset(HI_U32 hor_coffset)
{
	U_GP0_ZME_HCOFFSET GP0_ZME_HCOFFSET;
	
	GP0_ZME_HCOFFSET.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_HCOFFSET.u32));
	GP0_ZME_HCOFFSET.bits.hor_coffset = hor_coffset;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_HCOFFSET.u32),GP0_ZME_HCOFFSET.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetOutPro(HI_U32 out_pro)
{
	U_GP0_ZME_VINFO GP0_ZME_VINFO;
	
	GP0_ZME_VINFO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VINFO.u32));
	GP0_ZME_VINFO.bits.out_pro = out_pro;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VINFO.u32),GP0_ZME_VINFO.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetOutHeight(HI_U32 out_height)
{
	U_GP0_ZME_VINFO GP0_ZME_VINFO;
	
	GP0_ZME_VINFO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VINFO.u32));
	GP0_ZME_VINFO.bits.out_height = out_height;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VINFO.u32),GP0_ZME_VINFO.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVscEn(HI_U32 vsc_en)
{
	U_GP0_ZME_VSP GP0_ZME_VSP;
	
	GP0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32));
	GP0_ZME_VSP.bits.vsc_en = vsc_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32),GP0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVamidEn(HI_U32 vamid_en)
{
	U_GP0_ZME_VSP GP0_ZME_VSP;
	
	GP0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32));
	GP0_ZME_VSP.bits.vamid_en = vamid_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32),GP0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVlmidEn(HI_U32 vlmid_en)
{
	U_GP0_ZME_VSP GP0_ZME_VSP;
	
	GP0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32));
	GP0_ZME_VSP.bits.vlmid_en = vlmid_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32),GP0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVchmidEn(HI_U32 vchmid_en)
{
	U_GP0_ZME_VSP GP0_ZME_VSP;
	
	GP0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32));
	GP0_ZME_VSP.bits.vchmid_en = vchmid_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32),GP0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVfir2tapEn(HI_U32 vfir_2tap_en)
{
	U_GP0_ZME_VSP GP0_ZME_VSP;
	
	GP0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32));
	GP0_ZME_VSP.bits.vfir_2tap_en = vfir_2tap_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32),GP0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVfir1tapEn(HI_U32 vfir_1tap_en)
{
	U_GP0_ZME_VSP GP0_ZME_VSP;
	
	GP0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32));
	GP0_ZME_VSP.bits.vfir_1tap_en = vfir_1tap_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32),GP0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVfirEn(HI_U32 vfir_en)
{
	U_GP0_ZME_VSP GP0_ZME_VSP;
	
	GP0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32));
	GP0_ZME_VSP.bits.vfir_en = vfir_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32),GP0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVafirEn(HI_U32 vafir_en)
{
	U_GP0_ZME_VSP GP0_ZME_VSP;
	
	GP0_ZME_VSP.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32));
	GP0_ZME_VSP.bits.vafir_en = vafir_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32),GP0_ZME_VSP.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVratio(HI_U32 vratio)
{
	U_GP0_ZME_VSR GP0_ZME_VSR;
	
	GP0_ZME_VSR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VSR.u32));
	GP0_ZME_VSR.bits.vratio = vratio;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VSR.u32),GP0_ZME_VSR.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVtpOffset(HI_U32 vtp_offset)
{
	U_GP0_ZME_VOFFSET GP0_ZME_VOFFSET;
	
	GP0_ZME_VOFFSET.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32));
	GP0_ZME_VOFFSET.bits.vtp_offset = vtp_offset;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32),GP0_ZME_VOFFSET.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetVbtmOffset(HI_U32 vbtm_offset)
{
	U_GP0_ZME_VOFFSET GP0_ZME_VOFFSET;
	
	GP0_ZME_VOFFSET.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32));
	GP0_ZME_VOFFSET.bits.vbtm_offset = vbtm_offset;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32),GP0_ZME_VOFFSET.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetApbG0HfRenA(HI_U32 apb_g0_hf_ren_a)
{
	U_GP0_ZMECOEF GP0_ZMECOEF;
	
	GP0_ZMECOEF.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32));
	GP0_ZMECOEF.bits.apb_g0_hf_ren_a = apb_g0_hf_ren_a;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32),GP0_ZMECOEF.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetApbG0HfRenB(HI_U32 apb_g0_hf_ren_b)
{
	U_GP0_ZMECOEF GP0_ZMECOEF;
	
	GP0_ZMECOEF.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32));
	GP0_ZMECOEF.bits.apb_g0_hf_ren_b = apb_g0_hf_ren_b;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32),GP0_ZMECOEF.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetApbG0VfRen(HI_U32 apb_g0_vf_ren)
{
	U_GP0_ZMECOEF GP0_ZMECOEF;
	
	GP0_ZMECOEF.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32));
	GP0_ZMECOEF.bits.apb_g0_vf_ren = apb_g0_vf_ren;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32),GP0_ZMECOEF.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetApbG0LctiHlRen(HI_U32 apb_g0_lcti_hl_ren)
{
	U_GP0_ZMECOEF GP0_ZMECOEF;
	
	GP0_ZMECOEF.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32));
	GP0_ZMECOEF.bits.apb_g0_lcti_hl_ren = apb_g0_lcti_hl_ren;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32),GP0_ZMECOEF.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetApbG0LctiHcRen(HI_U32 apb_g0_lcti_hc_ren)
{
	U_GP0_ZMECOEF GP0_ZMECOEF;
	
	GP0_ZMECOEF.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32));
	GP0_ZMECOEF.bits.apb_g0_lcti_hc_ren = apb_g0_lcti_hc_ren;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32),GP0_ZMECOEF.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetApbG0LctiVlRen(HI_U32 apb_g0_lcti_vl_ren)
{
	U_GP0_ZMECOEF GP0_ZMECOEF;
	
	GP0_ZMECOEF.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32));
	GP0_ZMECOEF.bits.apb_g0_lcti_vl_ren = apb_g0_lcti_vl_ren;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32),GP0_ZMECOEF.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetApbG0LctiVcRen(HI_U32 apb_g0_lcti_vc_ren)
{
	U_GP0_ZMECOEF GP0_ZMECOEF;
	
	GP0_ZMECOEF.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32));
	GP0_ZMECOEF.bits.apb_g0_lcti_vc_ren = apb_g0_lcti_vc_ren;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZMECOEF.u32),GP0_ZMECOEF.u32);
	
	return ;
}


HI_VOID VDP_GP_ZME_SetApbG0CoefRaddr(HI_U32 apb_g0_coef_raddr)
{
	U_GP0_ZMECOEFAD GP0_ZMECOEFAD;
	
	GP0_ZMECOEFAD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->GP0_ZMECOEFAD.u32));
	GP0_ZMECOEFAD.bits.apb_g0_coef_raddr = apb_g0_coef_raddr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->GP0_ZMECOEFAD.u32),GP0_ZMECOEFAD.u32);
	
	return ;
}

//layer_name  : VDP
//module_name : gp_zme





