#ifndef __VPSS_FUNC_MAC_RCHN_H__
#define __VPSS_FUNC_MAC_RCHN_H__

#include "vpss_define.h"
#include "ice_define.h"
#include "vpss_mac_define.h"
#include "vpss_drv_comm.h"

typedef struct
{
    XDP_CMP_TYPE_E      enCmpType    ;
} VPSS_DCMP_CFG_S;

typedef struct
{
    //cfg
    HI_BOOL                 bEn         ;
    HI_BOOL                 bEn1        ;
    XDP_DATA_TYPE_E         enDataType  ;
    XDP_PROC_FMT_E          enDataFmt   ;
    XDP_PKG_FMT_E           enPkgFmt    ;
    XDP_DATA_RMODE_E        enRdMode    ;
    XDP_DATA_WTH            enDataWidth ;
    XDP_RECT_S              stInRect    ;
    VPSS_MUTE_CFG_S         stMuteCfg   ;
    HI_BOOL                 bFlipEn     ;
    HI_BOOL                 bMirrorEn   ;
    HI_BOOL                 bUvInvEn    ;
    HI_BOOL                 bMmuBypass  ;
    HI_BOOL                 bTunlEn     ;
    //dcmp
    VPSS_DCMP_CFG_S         stDcmpCfg   ;
    //addr
    XDP_TRIO_ADDR_S         stAddr[VPSS_RCHN_ADDR_BUTT] ;
    // env
    HI_BOOL                 bSetFlag    ;
    HI_BOOL                 bAddrAutoCalcEn;
    HI_BOOL                 bAddrRandModeEn;
    HI_BOOL                 bAddrSafeModeEn;

} VPSS_MAC_RCHN_CFG_S;

//function declare

HI_VOID VPSS_MAC_InitRchnCfg(HI_U32 u32Layer,  VPSS_MAC_RCHN_CFG_S *pstRchnCfg);
HI_VOID VPSS_MAC_SetRchnCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_RCHN_E enLayer, VPSS_MAC_RCHN_CFG_S *pstRchnCfg);
HI_U64 VPSS_MAC_RchnCalcAddrStr(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_RCHN_E enLayer, VPSS_MAC_RCHN_CFG_S *pstRchnCfg, HI_U64 u64StartAddr, HI_BOOL bRandModeEn);


#endif

