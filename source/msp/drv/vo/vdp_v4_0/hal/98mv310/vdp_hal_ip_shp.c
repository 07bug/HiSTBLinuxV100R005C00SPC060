
#include "vdp_hal_ip_shp.h"
#include "vdp_hal_comm.h"
extern S_VDP_REGS_TYPE *pVdpReg;

HI_VOID VDP_VID_SetSharpDbgEn(HI_U32 u32LayerId, HI_U32 bEnable)
{
    VDP_SHP_SetDemoEn(bEnable);
}

HI_VOID VDP_VID_SetSharpDemoMode(HI_U32 u32LayerId, HI_U32 DemoMode)
{
    VDP_SHP_SetDemoMode(DemoMode);
}


HI_VOID VDP_VID_SetSharpEnable(HI_U32 u32LayerId, HI_U32 bEnable)
{
    VDP_SHP_SetSharpenEn(bEnable);
}

HI_VOID VDP_VID_SetSharpDemoPos( HI_U32 u32LayerId, HI_U32 u32DemoPos)
{
    VDP_SHP_SetDemoPos(u32DemoPos);
}

HI_VOID VDP_SHP_SetWinsizeV(HI_U32 winsize_v)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.winsize_v = winsize_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetWinsizeH(HI_U32 winsize_h)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.winsize_h = winsize_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetShpCkGtEn(HI_U32 shp_ck_gt_en)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.shp_ck_gt_en = shp_ck_gt_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetHfreqEnD(HI_U32 hfreq_en_d)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.hfreq_en_d = hfreq_en_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetHfreqEnV(HI_U32 hfreq_en_v)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.hfreq_en_v = hfreq_en_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetHfreqEnH(HI_U32 hfreq_en_h)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.hfreq_en_h = hfreq_en_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetDetecEn(HI_U32 detec_en)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.detec_en = detec_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetPeakEn(HI_U32 peak_en)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.peak_en = peak_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetEnsctrl(HI_U32 ensctrl)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.ensctrl = ensctrl;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetDemoPos(HI_U32 demo_pos)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.demo_pos = demo_pos;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetDemoMode(HI_U32 demo_mode)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.demo_mode = demo_mode;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetSharpenEn(HI_U32 sharpen_en)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.sharpen_en = sharpen_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetDemoEn(HI_U32 demo_en)
{
	U_SPCTRL SPCTRL;
	
	SPCTRL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCTRL.u32));
	SPCTRL.bits.demo_en = demo_en;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCTRL.u32),SPCTRL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetWinsizeD(HI_U32 winsize_d)
{
	U_SPGAIN SPGAIN;
	
	SPGAIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAIN.u32));
	SPGAIN.bits.winsize_d = winsize_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAIN.u32),SPGAIN.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetDirGain(HI_U32 dir_gain)
{
	U_SPGAIN SPGAIN;
	
	SPGAIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAIN.u32));
	SPGAIN.bits.dir_gain = dir_gain;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAIN.u32),SPGAIN.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetEdgeGain(HI_U32 edge_gain)
{
	U_SPGAIN SPGAIN;
	
	SPGAIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAIN.u32));
	SPGAIN.bits.edge_gain = edge_gain;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAIN.u32),SPGAIN.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetPeakGain(HI_U32 peak_gain)
{
	U_SPGAIN SPGAIN;
	
	SPGAIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAIN.u32));
	SPGAIN.bits.peak_gain = peak_gain;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAIN.u32),SPGAIN.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetPeakCoring(HI_U32 peak_coring)
{
	U_SPPEAKSHOOTCTL SPPEAKSHOOTCTL;
	
	SPPEAKSHOOTCTL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPPEAKSHOOTCTL.u32));
	SPPEAKSHOOTCTL.bits.peak_coring = peak_coring;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPPEAKSHOOTCTL.u32),SPPEAKSHOOTCTL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetPeakMixratio(HI_U32 peak_mixratio)
{
	U_SPPEAKSHOOTCTL SPPEAKSHOOTCTL;
	
	SPPEAKSHOOTCTL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPPEAKSHOOTCTL.u32));
	SPPEAKSHOOTCTL.bits.peak_mixratio = peak_mixratio;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPPEAKSHOOTCTL.u32),SPPEAKSHOOTCTL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetPeakUnderThr(HI_U32 peak_under_thr)
{
	U_SPPEAKSHOOTCTL SPPEAKSHOOTCTL;
	
	SPPEAKSHOOTCTL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPPEAKSHOOTCTL.u32));
	SPPEAKSHOOTCTL.bits.peak_under_thr = peak_under_thr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPPEAKSHOOTCTL.u32),SPPEAKSHOOTCTL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetPeakOverThr(HI_U32 peak_over_thr)
{
	U_SPPEAKSHOOTCTL SPPEAKSHOOTCTL;
	
	SPPEAKSHOOTCTL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPPEAKSHOOTCTL.u32));
	SPPEAKSHOOTCTL.bits.peak_over_thr = peak_over_thr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPPEAKSHOOTCTL.u32),SPPEAKSHOOTCTL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGainPosD(HI_U32 gain_pos_d)
{
	U_SPGAINPOS SPGAINPOS;
	
	SPGAINPOS.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAINPOS.u32));
	SPGAINPOS.bits.gain_pos_d = gain_pos_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAINPOS.u32),SPGAINPOS.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGainPosV(HI_U32 gain_pos_v)
{
	U_SPGAINPOS SPGAINPOS;
	
	SPGAINPOS.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAINPOS.u32));
	SPGAINPOS.bits.gain_pos_v = gain_pos_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAINPOS.u32),SPGAINPOS.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGainPosH(HI_U32 gain_pos_h)
{
	U_SPGAINPOS SPGAINPOS;
	
	SPGAINPOS.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAINPOS.u32));
	SPGAINPOS.bits.gain_pos_h = gain_pos_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAINPOS.u32),SPGAINPOS.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGainNegD(HI_U32 gain_neg_d)
{
	U_SPGAINNEG SPGAINNEG;
	
	SPGAINNEG.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAINNEG.u32));
	SPGAINNEG.bits.gain_neg_d = gain_neg_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAINNEG.u32),SPGAINNEG.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGainNegV(HI_U32 gain_neg_v)
{
	U_SPGAINNEG SPGAINNEG;
	
	SPGAINNEG.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAINNEG.u32));
	SPGAINNEG.bits.gain_neg_v = gain_neg_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAINNEG.u32),SPGAINNEG.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGainNegH(HI_U32 gain_neg_h)
{
	U_SPGAINNEG SPGAINNEG;
	
	SPGAINNEG.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGAINNEG.u32));
	SPGAINNEG.bits.gain_neg_h = gain_neg_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGAINNEG.u32),SPGAINNEG.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetUnderThrH(HI_U32 under_thr_h)
{
	U_SPOVERTHR SPOVERTHR;
	
	SPOVERTHR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPOVERTHR.u32));
	SPOVERTHR.bits.under_thr_h = under_thr_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPOVERTHR.u32),SPOVERTHR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetOverThrD(HI_U32 over_thr_d)
{
	U_SPOVERTHR SPOVERTHR;
	
	SPOVERTHR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPOVERTHR.u32));
	SPOVERTHR.bits.over_thr_d = over_thr_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPOVERTHR.u32),SPOVERTHR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetOverThrV(HI_U32 over_thr_v)
{
	U_SPOVERTHR SPOVERTHR;
	
	SPOVERTHR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPOVERTHR.u32));
	SPOVERTHR.bits.over_thr_v = over_thr_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPOVERTHR.u32),SPOVERTHR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetOverThrH(HI_U32 over_thr_h)
{
	U_SPOVERTHR SPOVERTHR;
	
	SPOVERTHR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPOVERTHR.u32));
	SPOVERTHR.bits.over_thr_h = over_thr_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPOVERTHR.u32),SPOVERTHR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetMixratioV(HI_U32 mixratio_v)
{
	U_SPUNDERTHR SPUNDERTHR;
	
	SPUNDERTHR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPUNDERTHR.u32));
	SPUNDERTHR.bits.mixratio_v = mixratio_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPUNDERTHR.u32),SPUNDERTHR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetMixratioH(HI_U32 mixratio_h)
{
	U_SPUNDERTHR SPUNDERTHR;
	
	SPUNDERTHR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPUNDERTHR.u32));
	SPUNDERTHR.bits.mixratio_h = mixratio_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPUNDERTHR.u32),SPUNDERTHR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetUnderThrD(HI_U32 under_thr_d)
{
	U_SPUNDERTHR SPUNDERTHR;
	
	SPUNDERTHR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPUNDERTHR.u32));
	SPUNDERTHR.bits.under_thr_d = under_thr_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPUNDERTHR.u32),SPUNDERTHR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetUnderThrV(HI_U32 under_thr_v)
{
	U_SPUNDERTHR SPUNDERTHR;
	
	SPUNDERTHR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPUNDERTHR.u32));
	SPUNDERTHR.bits.under_thr_v = under_thr_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPUNDERTHR.u32),SPUNDERTHR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetMixratioD(HI_U32 mixratio_d)
{
	U_SPCORINGZERO SPCORINGZERO;
	
	SPCORINGZERO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCORINGZERO.u32));
	SPCORINGZERO.bits.mixratio_d = mixratio_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCORINGZERO.u32),SPCORINGZERO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetCoringzeroD(HI_U32 coringzero_d)
{
	U_SPCORINGZERO SPCORINGZERO;
	
	SPCORINGZERO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCORINGZERO.u32));
	SPCORINGZERO.bits.coringzero_d = coringzero_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCORINGZERO.u32),SPCORINGZERO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetCoringzeroV(HI_U32 coringzero_v)
{
	U_SPCORINGZERO SPCORINGZERO;
	
	SPCORINGZERO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCORINGZERO.u32));
	SPCORINGZERO.bits.coringzero_v = coringzero_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCORINGZERO.u32),SPCORINGZERO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetCoringzeroH(HI_U32 coringzero_h)
{
	U_SPCORINGZERO SPCORINGZERO;
	
	SPCORINGZERO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCORINGZERO.u32));
	SPCORINGZERO.bits.coringzero_h = coringzero_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCORINGZERO.u32),SPCORINGZERO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetCoringthrV(HI_U32 coringthr_v)
{
	U_SPCORINGRATIO SPCORINGRATIO;
	
	SPCORINGRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32));
	SPCORINGRATIO.bits.coringthr_v = coringthr_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32),SPCORINGRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetCoringthrH(HI_U32 coringthr_h)
{
	U_SPCORINGRATIO SPCORINGRATIO;
	
	SPCORINGRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32));
	SPCORINGRATIO.bits.coringthr_h = coringthr_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32),SPCORINGRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetCoringratioD(HI_U32 coringratio_d)
{
	U_SPCORINGRATIO SPCORINGRATIO;
	
	SPCORINGRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32));
	SPCORINGRATIO.bits.coringratio_d = coringratio_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32),SPCORINGRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetCoringratioV(HI_U32 coringratio_v)
{
	U_SPCORINGRATIO SPCORINGRATIO;
	
	SPCORINGRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32));
	SPCORINGRATIO.bits.coringratio_v = coringratio_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32),SPCORINGRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetCoringratioH(HI_U32 coringratio_h)
{
	U_SPCORINGRATIO SPCORINGRATIO;
	
	SPCORINGRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32));
	SPCORINGRATIO.bits.coringratio_h = coringratio_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPCORINGRATIO.u32),SPCORINGRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGradcontrastthr(HI_U32 gradcontrastthr)
{
	U_SPLMTRATIO SPLMTRATIO;
	
	SPLMTRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32));
	SPLMTRATIO.bits.gradcontrastthr = gradcontrastthr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32),SPLMTRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetCoringthrD(HI_U32 coringthr_d)
{
	U_SPLMTRATIO SPLMTRATIO;
	
	SPLMTRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32));
	SPLMTRATIO.bits.coringthr_d = coringthr_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32),SPLMTRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitRatioD(HI_U32 limit_ratio_d)
{
	U_SPLMTRATIO SPLMTRATIO;
	
	SPLMTRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32));
	SPLMTRATIO.bits.limit_ratio_d = limit_ratio_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32),SPLMTRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitRatioV(HI_U32 limit_ratio_v)
{
	U_SPLMTRATIO SPLMTRATIO;
	
	SPLMTRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32));
	SPLMTRATIO.bits.limit_ratio_v = limit_ratio_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32),SPLMTRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitRatioH(HI_U32 limit_ratio_h)
{
	U_SPLMTRATIO SPLMTRATIO;
	
	SPLMTRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32));
	SPLMTRATIO.bits.limit_ratio_h = limit_ratio_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTRATIO.u32),SPLMTRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitpos1H(HI_U32 limitpos1_h)
{
	U_SPLMTPOS0 SPLMTPOS0;
	
	SPLMTPOS0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTPOS0.u32));
	SPLMTPOS0.bits.limitpos1_h = limitpos1_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTPOS0.u32),SPLMTPOS0.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitpos0D(HI_U32 limitpos0_d)
{
	U_SPLMTPOS0 SPLMTPOS0;
	
	SPLMTPOS0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTPOS0.u32));
	SPLMTPOS0.bits.limitpos0_d = limitpos0_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTPOS0.u32),SPLMTPOS0.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitpos0V(HI_U32 limitpos0_v)
{
	U_SPLMTPOS0 SPLMTPOS0;
	
	SPLMTPOS0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTPOS0.u32));
	SPLMTPOS0.bits.limitpos0_v = limitpos0_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTPOS0.u32),SPLMTPOS0.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitpos0H(HI_U32 limitpos0_h)
{
	U_SPLMTPOS0 SPLMTPOS0;
	
	SPLMTPOS0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTPOS0.u32));
	SPLMTPOS0.bits.limitpos0_h = limitpos0_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTPOS0.u32),SPLMTPOS0.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitpos1V(HI_U32 limitpos1_v)
{
	U_SPBOUNDPOS SPBOUNDPOS;
	
	SPBOUNDPOS.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPBOUNDPOS.u32));
	SPBOUNDPOS.bits.limitpos1_v = limitpos1_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPBOUNDPOS.u32),SPBOUNDPOS.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetBoundposD(HI_U32 boundpos_d)
{
	U_SPBOUNDPOS SPBOUNDPOS;
	
	SPBOUNDPOS.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPBOUNDPOS.u32));
	SPBOUNDPOS.bits.boundpos_d = boundpos_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPBOUNDPOS.u32),SPBOUNDPOS.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetBoundposV(HI_U32 boundpos_v)
{
	U_SPBOUNDPOS SPBOUNDPOS;
	
	SPBOUNDPOS.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPBOUNDPOS.u32));
	SPBOUNDPOS.bits.boundpos_v = boundpos_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPBOUNDPOS.u32),SPBOUNDPOS.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetBoundposH(HI_U32 boundpos_h)
{
	U_SPBOUNDPOS SPBOUNDPOS;
	
	SPBOUNDPOS.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPBOUNDPOS.u32));
	SPBOUNDPOS.bits.boundpos_h = boundpos_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPBOUNDPOS.u32),SPBOUNDPOS.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitneg0D(HI_U32 limitneg0_d)
{
	U_SPLMTNEG0 SPLMTNEG0;
	
	SPLMTNEG0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTNEG0.u32));
	SPLMTNEG0.bits.limitneg0_d = limitneg0_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTNEG0.u32),SPLMTNEG0.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitneg0V(HI_U32 limitneg0_v)
{
	U_SPLMTNEG0 SPLMTNEG0;
	
	SPLMTNEG0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTNEG0.u32));
	SPLMTNEG0.bits.limitneg0_v = limitneg0_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTNEG0.u32),SPLMTNEG0.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitneg0H(HI_U32 limitneg0_h)
{
	U_SPLMTNEG0 SPLMTNEG0;
	
	SPLMTNEG0.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTNEG0.u32));
	SPLMTNEG0.bits.limitneg0_h = limitneg0_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTNEG0.u32),SPLMTNEG0.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitneg1D(HI_U32 limitneg1_d)
{
	U_SPLMTNEG1 SPLMTNEG1;
	
	SPLMTNEG1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTNEG1.u32));
	SPLMTNEG1.bits.limitneg1_d = limitneg1_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTNEG1.u32),SPLMTNEG1.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitneg1V(HI_U32 limitneg1_v)
{
	U_SPLMTNEG1 SPLMTNEG1;
	
	SPLMTNEG1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTNEG1.u32));
	SPLMTNEG1.bits.limitneg1_v = limitneg1_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTNEG1.u32),SPLMTNEG1.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitneg1H(HI_U32 limitneg1_h)
{
	U_SPLMTNEG1 SPLMTNEG1;
	
	SPLMTNEG1.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPLMTNEG1.u32));
	SPLMTNEG1.bits.limitneg1_h = limitneg1_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPLMTNEG1.u32),SPLMTNEG1.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetBoundnegD(HI_U32 boundneg_d)
{
	U_SPBOUNDNEG SPBOUNDNEG;
	
	SPBOUNDNEG.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPBOUNDNEG.u32));
	SPBOUNDNEG.bits.boundneg_d = boundneg_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPBOUNDNEG.u32),SPBOUNDNEG.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetBoundnegV(HI_U32 boundneg_v)
{
	U_SPBOUNDNEG SPBOUNDNEG;
	
	SPBOUNDNEG.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPBOUNDNEG.u32));
	SPBOUNDNEG.bits.boundneg_v = boundneg_v;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPBOUNDNEG.u32),SPBOUNDNEG.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetBoundnegH(HI_U32 boundneg_h)
{
	U_SPBOUNDNEG SPBOUNDNEG;
	
	SPBOUNDNEG.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPBOUNDNEG.u32));
	SPBOUNDNEG.bits.boundneg_h = boundneg_h;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPBOUNDNEG.u32),SPBOUNDNEG.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetLimitpos1D(HI_U32 limitpos1_d)
{
	U_SPEDGESHOOTCTL SPEDGESHOOTCTL;
	
	SPEDGESHOOTCTL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPEDGESHOOTCTL.u32));
	SPEDGESHOOTCTL.bits.limitpos1_d = limitpos1_d;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPEDGESHOOTCTL.u32),SPEDGESHOOTCTL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetEdgeMixratio(HI_U32 edge_mixratio)
{
	U_SPEDGESHOOTCTL SPEDGESHOOTCTL;
	
	SPEDGESHOOTCTL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPEDGESHOOTCTL.u32));
	SPEDGESHOOTCTL.bits.edge_mixratio = edge_mixratio;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPEDGESHOOTCTL.u32),SPEDGESHOOTCTL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetEdgeUnderThr(HI_U32 edge_under_thr)
{
	U_SPEDGESHOOTCTL SPEDGESHOOTCTL;
	
	SPEDGESHOOTCTL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPEDGESHOOTCTL.u32));
	SPEDGESHOOTCTL.bits.edge_under_thr = edge_under_thr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPEDGESHOOTCTL.u32),SPEDGESHOOTCTL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetEdgeOverThr(HI_U32 edge_over_thr)
{
	U_SPEDGESHOOTCTL SPEDGESHOOTCTL;
	
	SPEDGESHOOTCTL.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPEDGESHOOTCTL.u32));
	SPEDGESHOOTCTL.bits.edge_over_thr = edge_over_thr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPEDGESHOOTCTL.u32),SPEDGESHOOTCTL.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetUshootratioe(HI_U32 ushootratioe)
{
	U_SPEDGEEI SPEDGEEI;
	
	SPEDGEEI.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPEDGEEI.u32));
	SPEDGEEI.bits.ushootratioe = ushootratioe;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPEDGEEI.u32),SPEDGEEI.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetEdgeEiratio(HI_U32 edge_eiratio)
{
	U_SPEDGEEI SPEDGEEI;
	
	SPEDGEEI.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPEDGEEI.u32));
	SPEDGEEI.bits.edge_eiratio = edge_eiratio;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPEDGEEI.u32),SPEDGEEI.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetEdgeEi1(HI_U32 edge_ei1)
{
	U_SPEDGEEI SPEDGEEI;
	
	SPEDGEEI.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPEDGEEI.u32));
	SPEDGEEI.bits.edge_ei1 = edge_ei1;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPEDGEEI.u32),SPEDGEEI.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetEdgeEi0(HI_U32 edge_ei0)
{
	U_SPEDGEEI SPEDGEEI;
	
	SPEDGEEI.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPEDGEEI.u32));
	SPEDGEEI.bits.edge_ei0 = edge_ei0;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPEDGEEI.u32),SPEDGEEI.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGradminslop(HI_U32 gradminslop)
{
	U_SPGRADMIN SPGRADMIN;
	
	SPGRADMIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGRADMIN.u32));
	SPGRADMIN.bits.gradminslop = gradminslop;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGRADMIN.u32),SPGRADMIN.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGradminthrh(HI_U32 gradminthrh)
{
	U_SPGRADMIN SPGRADMIN;
	
	SPGRADMIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGRADMIN.u32));
	SPGRADMIN.bits.gradminthrh = gradminthrh;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGRADMIN.u32),SPGRADMIN.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGradminthrl(HI_U32 gradminthrl)
{
	U_SPGRADMIN SPGRADMIN;
	
	SPGRADMIN.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGRADMIN.u32));
	SPGRADMIN.bits.gradminthrl = gradminthrl;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGRADMIN.u32),SPGRADMIN.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetChessboardthr(HI_U32 chessboardthr)
{
	U_SPGRADCTR SPGRADCTR;
	
	SPGRADCTR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGRADCTR.u32));
	SPGRADCTR.bits.chessboardthr = chessboardthr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGRADCTR.u32),SPGRADCTR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGradminthr(HI_U32 gradminthr)
{
	U_SPGRADCTR SPGRADCTR;
	
	SPGRADCTR.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPGRADCTR.u32));
	SPGRADCTR.bits.gradminthr = gradminthr;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPGRADCTR.u32),SPGRADCTR.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetOshootratiot(HI_U32 oshootratiot)
{
	U_SPSHOOTRATIO SPSHOOTRATIO;
	
	SPSHOOTRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPSHOOTRATIO.u32));
	SPSHOOTRATIO.bits.oshootratiot = oshootratiot;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPSHOOTRATIO.u32),SPSHOOTRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetOshootratioe(HI_U32 oshootratioe)
{
	U_SPSHOOTRATIO SPSHOOTRATIO;
	
	SPSHOOTRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPSHOOTRATIO.u32));
	SPSHOOTRATIO.bits.oshootratioe = oshootratioe;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPSHOOTRATIO.u32),SPSHOOTRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetUshootratiot(HI_U32 ushootratiot)
{
	U_SPSHOOTRATIO SPSHOOTRATIO;
	
	SPSHOOTRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPSHOOTRATIO.u32));
	SPSHOOTRATIO.bits.ushootratiot = ushootratiot;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPSHOOTRATIO.u32),SPSHOOTRATIO.u32);
	
	return ;
}


HI_VOID VDP_SHP_SetGradcontrastslop(HI_U32 gradcontrastslop)
{
	U_SPSHOOTRATIO SPSHOOTRATIO;
	
	SPSHOOTRATIO.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->SPSHOOTRATIO.u32));
	SPSHOOTRATIO.bits.gradcontrastslop = gradcontrastslop;
	VDP_RegWrite((HI_ULONG)&(pVdpReg->SPSHOOTRATIO.u32),SPSHOOTRATIO.u32);
	
	return ;
}

//layer_name  : VID
//module_name : SHP





