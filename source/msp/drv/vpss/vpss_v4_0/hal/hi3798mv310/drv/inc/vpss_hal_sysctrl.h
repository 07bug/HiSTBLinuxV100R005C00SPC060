#ifndef __HAL_SYSCTRL_H__
#define __HAL_SYSCTRL_H__

#include "vpss_define.h"
#include "hi_reg_common.h"

//-------------------------------------------------
// vpss hal system APB
//-------------------------------------------------
HI_VOID VPSS_Sys_SetIntMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32Mask);
HI_U32 VPSS_Sys_GetIntState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMaskIntState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_VOID VPSS_Sys_SetIntClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32Data1);

HI_U32 VPSS_Sys_GetNodeCnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScan0Cnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScan1Cnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScan2Cnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScan3Cnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScanCnt(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScanNum(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetNodeNum(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMacDebug0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMacDebug1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMacDebug2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMacDebug3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetStartCurState(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetNodeAddrPNextH(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetNodeAddrPNextL(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScanAddrPNextH(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScanAddrPNextL(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScanAddrSpNextH(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetScanAddrSpNextL(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst0RError(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst0WError(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst1RError(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst1WError(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst2RError(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst2WError(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetSrc0Status0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetSrc0Status1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetSrc1Status0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetSrc1Status1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetSrc2Status0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetSrc2Status1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetAxiMst0LatencyMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetAxiMst0LatencyAvg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetAxiMst1LatencyMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetAxiMst1LatencyAvg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetAxiMst2LatencyMax(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetAxiMst2LatencyAvg(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst0RdInfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst0WrInfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst1RdInfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst1WrInfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst2RdInfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);
HI_U32 VPSS_Sys_GetMst2WrInfo(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset);


HI_VOID VPSS_Sys_SetAxiDetEnable(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 axi_det_enable);
HI_VOID VPSS_Sys_SetAxiDeClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 axi_det_clr);
HI_VOID VPSS_Sys_SetBusErrorClr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 bus_error_clr);


HI_VOID VPSS_Sys_SetCkGtEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ck_gt_en);
HI_VOID VPSS_Sys_SetRftfWct(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rftf_wct);
HI_VOID VPSS_Sys_SetRftsKp(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfts_kp);
HI_VOID VPSS_Sys_SetRftsRct(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfts_rct);
HI_VOID VPSS_Sys_SetRftsWct(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfts_wct);
HI_VOID VPSS_Sys_SetRfsRtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfs_rtsel);
HI_VOID VPSS_Sys_SetRfsWtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfs_wtsel);
HI_VOID VPSS_Sys_SetRfsuhdRtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfsuhd_rtsel);
HI_VOID VPSS_Sys_SetRfsuhdWtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfsuhd_wtsel);
HI_VOID VPSS_Sys_SetRftEmasa(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rft_emasa);
HI_VOID VPSS_Sys_SetRfsColldisn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfs_colldisn);
HI_VOID VPSS_Sys_SetRftEmab(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rft_emab);
HI_VOID VPSS_Sys_SetRftEmaa(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rft_emaa);
HI_VOID VPSS_Sys_SetRet1n(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ret1n);
HI_VOID VPSS_Sys_SetRfsEmaw(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfs_emaw);
HI_VOID VPSS_Sys_SetRfsEma(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rfs_ema);
HI_VOID VPSS_Sys_SetRasRtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ras_rtsel);
HI_VOID VPSS_Sys_SetRasWtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ras_wtsel);
HI_VOID VPSS_Sys_SetRashdmRtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rashdm_rtsel);
HI_VOID VPSS_Sys_SetRashdmWtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rashdm_wtsel);
HI_VOID VPSS_Sys_SetRashdsRtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rashds_rtsel);
HI_VOID VPSS_Sys_SetRashdsWtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rashds_wtsel);
HI_VOID VPSS_Sys_SetRasshdmRtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rasshdm_rtsel);
HI_VOID VPSS_Sys_SetRasshdmWtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rasshdm_wtsel);
HI_VOID VPSS_Sys_SetRasshdsRtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rasshds_rtsel);
HI_VOID VPSS_Sys_SetRasshdsWtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rasshds_wtsel);
HI_VOID VPSS_Sys_SetRftMtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rft_mtsel);
HI_VOID VPSS_Sys_SetRftRtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rft_rtsel);
HI_VOID VPSS_Sys_SetRftWtsel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rft_wtsel);
HI_VOID VPSS_Sys_SetRftfKp(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rftf_kp);
HI_VOID VPSS_Sys_SetRftfRct(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rftf_rct);

HI_VOID VPSS_Sys_SetNodeTimeout(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 node_timeout);

HI_VOID VPSS_Sys_SetNodeRstEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 node_rst_en);
HI_VOID VPSS_Sys_SetNodeInitTimer(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 node_init_timer);


HI_VOID VPSS_Sys_SetPNextEx(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32TaskId, HI_U32 u32PnextH, HI_U32 u32PnextL);
HI_VOID VPSS_Sys_SetVpssStart(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32TaskId, HI_U32 u32Start);

//-------------------------------------------------
// vpss hal system AXI
//-------------------------------------------------
HI_VOID VPSS_Sys_SetPNext(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32PnextH, HI_U32 u32PnextL);

HI_VOID VPSS_Sys_SetNodeSrcMintMask(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 node_src_mint_mask);
HI_VOID VPSS_Sys_SetTnrRecDitherEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 tnr_rec_dither_en);
HI_VOID VPSS_Sys_SetTnrRecDitherMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 tnr_rec_dither_mode);
HI_VOID VPSS_Sys_SetSnrMadDisable(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 snr_mad_disable);
HI_VOID VPSS_Sys_SetHfrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hfr_en);
HI_VOID VPSS_Sys_SetLbdEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 lbd_en);
HI_VOID VPSS_Sys_SetTnrRec8BitEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 tnr_rec_8bit_en);
HI_VOID VPSS_Sys_SetTnrMadMode(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 tnr_mad_mode);
HI_VOID VPSS_Sys_SetHctiEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hcti_en);
HI_VOID VPSS_Sys_SetScdEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scd_en);
HI_VOID VPSS_Sys_SetVc1En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vc1_en);
HI_VOID VPSS_Sys_SetHspEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 hsp_en);
HI_VOID VPSS_Sys_SetRotateEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rotate_en);
HI_VOID VPSS_Sys_SetRotateAngle(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rotate_angle);
HI_VOID VPSS_Sys_SetSnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 snr_en);
HI_VOID VPSS_Sys_SetCcclEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 cccl_en);
HI_VOID VPSS_Sys_SetMedsEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 meds_en);
HI_VOID VPSS_Sys_SetTnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 tnr_en);
HI_VOID VPSS_Sys_SetMcnrEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcnr_en);
HI_VOID VPSS_Sys_SetDeiEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 dei_en);
HI_VOID VPSS_Sys_SetMcdiEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mcdi_en);
HI_VOID VPSS_Sys_SetIfmdEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ifmd_en);
HI_VOID VPSS_Sys_SetIgbmEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 igbm_en);
HI_VOID VPSS_Sys_SetRgmeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 rgme_en);
HI_VOID VPSS_Sys_SetMeVersion(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 me_version);
HI_VOID VPSS_Sys_SetMaMacSel(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 ma_mac_sel);
HI_VOID VPSS_Sys_SetVpss3drsEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 vpss_3drs_en);

HI_VOID VPSS_Sys_SetSlow(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 slow);
HI_VOID VPSS_Sys_SetMask0(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mask0);
HI_VOID VPSS_Sys_SetMask1(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mask1);
HI_VOID VPSS_Sys_SetMask2(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mask2);
HI_VOID VPSS_Sys_SetMask3(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mask3);
HI_VOID VPSS_Sys_SetMask4(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mask4);
HI_VOID VPSS_Sys_SetMask5(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mask5);
HI_VOID VPSS_Sys_SetMask6(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mask6);
HI_VOID VPSS_Sys_SetMask7(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 mask7);

HI_VOID VPSS_Sys_SetSttRAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32SttAddrH, HI_U32 u32SttAddrL);
HI_VOID VPSS_Sys_SetSttWAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32SttAddrH, HI_U32 u32SttAddrL);

HI_VOID VPSS_Sys_SetVpssOkNum(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32VpssOkNum);
HI_VOID VPSS_Sys_SetVpssHoldEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32VpssHoldEn);
HI_VOID VPSS_Sys_SetScanOkNum(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32ScanOkNum);
HI_VOID VPSS_Sys_SetScanHoldEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32ScanHoldEn);

HI_VOID VPSS_Sys_SetRupdEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32RupdEn);

#endif

