#ifndef __HAL_SCANCTRL_H__
#define __HAL_SCANCTRL_H__

#include "vpss_define.h"
#include "hi_reg_common.h"

//-------------------------------------------------
// vpss hal scan
//-------------------------------------------------

HI_VOID VPSS_Scan_SetScanTimeout(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scan_timeout);
HI_VOID VPSS_Scan_SetScanRstEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scan_rst_en);
HI_VOID VPSS_Scan_SetScanInitTimer(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scan_init_timer);
HI_VOID VPSS_Scan_SetScanStartAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scan_start_addr_h, HI_U32 scan_start_addr_l);
HI_VOID VPSS_Scan_SetScanPnextAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 scan_pnext_addr_h, HI_U32 scan_pnext_addr_l);
HI_VOID VPSS_Scan_SetMeSttWAddr(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 u32SttAddrH, HI_U32 u32SttAddrL);


HI_VOID VPSS_Scan_SetMeCfOnlineEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 me_cf_online_en);
HI_VOID VPSS_Scan_SetMeVc1En(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 me_vc1_en);
HI_VOID VPSS_Scan_SetMeEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 me_en);
HI_VOID VPSS_Scan_SetMeMvUpsmpEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 me_mv_upsmp_en);
HI_VOID VPSS_Scan_SetMeMvDnsmpEn(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 me_mv_dnsmp_en);
HI_VOID VPSS_Scan_SetMeLayer(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 me_layer);
HI_VOID VPSS_Scan_SetMeScan(S_VPSS_REGS_TYPE *pstVpssRegs, HI_U32 u32AddrOffset, HI_U32 me_scan);
#endif

