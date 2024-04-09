#ifndef __VDP_HAL_IP_SHP_H__
#define __VDP_HAL_IP_SHP_H__

#include "vdp_define.h"
HI_VOID VDP_VID_SetSharpDbgEn         (HI_U32 u32LayerId, HI_U32 bEnable)   ;
HI_VOID VDP_VID_SetSharpDemoMode      (HI_U32 u32LayerId, HI_U32 DemoMode)  ;
HI_VOID VDP_VID_SetSharpEnable        (HI_U32 u32LayerId, HI_U32 bEnable)   ;
HI_VOID VDP_VID_SetSharpDemoPos       (HI_U32 u32LayerId, HI_U32 u32DemoPos);

HI_VOID VDP_SHP_SetWinsizeV(HI_U32 winsize_v);
HI_VOID VDP_SHP_SetWinsizeH(HI_U32 winsize_h);
HI_VOID VDP_SHP_SetShpCkGtEn(HI_U32 shp_ck_gt_en);
HI_VOID VDP_SHP_SetHfreqEnD(HI_U32 hfreq_en_d);
HI_VOID VDP_SHP_SetHfreqEnV(HI_U32 hfreq_en_v);
HI_VOID VDP_SHP_SetHfreqEnH(HI_U32 hfreq_en_h);
HI_VOID VDP_SHP_SetDetecEn(HI_U32 detec_en);
HI_VOID VDP_SHP_SetPeakEn(HI_U32 peak_en);
HI_VOID VDP_SHP_SetEnsctrl(HI_U32 ensctrl);
HI_VOID VDP_SHP_SetDemoPos(HI_U32 demo_pos);
HI_VOID VDP_SHP_SetDemoMode(HI_U32 demo_mode);
HI_VOID VDP_SHP_SetSharpenEn(HI_U32 sharpen_en);
HI_VOID VDP_SHP_SetDemoEn(HI_U32 demo_en);
HI_VOID VDP_SHP_SetWinsizeD(HI_U32 winsize_d);
HI_VOID VDP_SHP_SetDirGain(HI_U32 dir_gain);
HI_VOID VDP_SHP_SetEdgeGain(HI_U32 edge_gain);
HI_VOID VDP_SHP_SetPeakGain(HI_U32 peak_gain);
HI_VOID VDP_SHP_SetPeakCoring(HI_U32 peak_coring);
HI_VOID VDP_SHP_SetPeakMixratio(HI_U32 peak_mixratio);
HI_VOID VDP_SHP_SetPeakUnderThr(HI_U32 peak_under_thr);
HI_VOID VDP_SHP_SetPeakOverThr(HI_U32 peak_over_thr);
HI_VOID VDP_SHP_SetGainPosD(HI_U32 gain_pos_d);
HI_VOID VDP_SHP_SetGainPosV(HI_U32 gain_pos_v);
HI_VOID VDP_SHP_SetGainPosH(HI_U32 gain_pos_h);
HI_VOID VDP_SHP_SetGainNegD(HI_U32 gain_neg_d);
HI_VOID VDP_SHP_SetGainNegV(HI_U32 gain_neg_v);
HI_VOID VDP_SHP_SetGainNegH(HI_U32 gain_neg_h);
HI_VOID VDP_SHP_SetUnderThrH(HI_U32 under_thr_h);
HI_VOID VDP_SHP_SetOverThrD(HI_U32 over_thr_d);
HI_VOID VDP_SHP_SetOverThrV(HI_U32 over_thr_v);
HI_VOID VDP_SHP_SetOverThrH(HI_U32 over_thr_h);
HI_VOID VDP_SHP_SetMixratioV(HI_U32 mixratio_v);
HI_VOID VDP_SHP_SetMixratioH(HI_U32 mixratio_h);
HI_VOID VDP_SHP_SetUnderThrD(HI_U32 under_thr_d);
HI_VOID VDP_SHP_SetUnderThrV(HI_U32 under_thr_v);
HI_VOID VDP_SHP_SetMixratioD(HI_U32 mixratio_d);
HI_VOID VDP_SHP_SetCoringzeroD(HI_U32 coringzero_d);
HI_VOID VDP_SHP_SetCoringzeroV(HI_U32 coringzero_v);
HI_VOID VDP_SHP_SetCoringzeroH(HI_U32 coringzero_h);
HI_VOID VDP_SHP_SetCoringthrV(HI_U32 coringthr_v);
HI_VOID VDP_SHP_SetCoringthrH(HI_U32 coringthr_h);
HI_VOID VDP_SHP_SetCoringratioD(HI_U32 coringratio_d);
HI_VOID VDP_SHP_SetCoringratioV(HI_U32 coringratio_v);
HI_VOID VDP_SHP_SetCoringratioH(HI_U32 coringratio_h);
HI_VOID VDP_SHP_SetGradcontrastthr(HI_U32 gradcontrastthr);
HI_VOID VDP_SHP_SetCoringthrD(HI_U32 coringthr_d);
HI_VOID VDP_SHP_SetLimitRatioD(HI_U32 limit_ratio_d);
HI_VOID VDP_SHP_SetLimitRatioV(HI_U32 limit_ratio_v);
HI_VOID VDP_SHP_SetLimitRatioH(HI_U32 limit_ratio_h);
HI_VOID VDP_SHP_SetLimitpos1H(HI_U32 limitpos1_h);
HI_VOID VDP_SHP_SetLimitpos0D(HI_U32 limitpos0_d);
HI_VOID VDP_SHP_SetLimitpos0V(HI_U32 limitpos0_v);
HI_VOID VDP_SHP_SetLimitpos0H(HI_U32 limitpos0_h);
HI_VOID VDP_SHP_SetLimitpos1V(HI_U32 limitpos1_v);
HI_VOID VDP_SHP_SetBoundposD(HI_U32 boundpos_d);
HI_VOID VDP_SHP_SetBoundposV(HI_U32 boundpos_v);
HI_VOID VDP_SHP_SetBoundposH(HI_U32 boundpos_h);
HI_VOID VDP_SHP_SetLimitneg0D(HI_U32 limitneg0_d);
HI_VOID VDP_SHP_SetLimitneg0V(HI_U32 limitneg0_v);
HI_VOID VDP_SHP_SetLimitneg0H(HI_U32 limitneg0_h);
HI_VOID VDP_SHP_SetLimitneg1D(HI_U32 limitneg1_d);
HI_VOID VDP_SHP_SetLimitneg1V(HI_U32 limitneg1_v);
HI_VOID VDP_SHP_SetLimitneg1H(HI_U32 limitneg1_h);
HI_VOID VDP_SHP_SetBoundnegD(HI_U32 boundneg_d);
HI_VOID VDP_SHP_SetBoundnegV(HI_U32 boundneg_v);
HI_VOID VDP_SHP_SetBoundnegH(HI_U32 boundneg_h);
HI_VOID VDP_SHP_SetLimitpos1D(HI_U32 limitpos1_d);
HI_VOID VDP_SHP_SetEdgeMixratio(HI_U32 edge_mixratio);
HI_VOID VDP_SHP_SetEdgeUnderThr(HI_U32 edge_under_thr);
HI_VOID VDP_SHP_SetEdgeOverThr(HI_U32 edge_over_thr);
HI_VOID VDP_SHP_SetUshootratioe(HI_U32 ushootratioe);
HI_VOID VDP_SHP_SetEdgeEiratio(HI_U32 edge_eiratio);
HI_VOID VDP_SHP_SetEdgeEi1(HI_U32 edge_ei1);
HI_VOID VDP_SHP_SetEdgeEi0(HI_U32 edge_ei0);
HI_VOID VDP_SHP_SetGradminslop(HI_U32 gradminslop);
HI_VOID VDP_SHP_SetGradminthrh(HI_U32 gradminthrh);
HI_VOID VDP_SHP_SetGradminthrl(HI_U32 gradminthrl);
HI_VOID VDP_SHP_SetChessboardthr(HI_U32 chessboardthr);
HI_VOID VDP_SHP_SetGradminthr(HI_U32 gradminthr);
HI_VOID VDP_SHP_SetOshootratiot(HI_U32 oshootratiot);
HI_VOID VDP_SHP_SetOshootratioe(HI_U32 oshootratioe);
HI_VOID VDP_SHP_SetUshootratiot(HI_U32 ushootratiot);
HI_VOID VDP_SHP_SetGradcontrastslop(HI_U32 gradcontrastslop);

#endif


