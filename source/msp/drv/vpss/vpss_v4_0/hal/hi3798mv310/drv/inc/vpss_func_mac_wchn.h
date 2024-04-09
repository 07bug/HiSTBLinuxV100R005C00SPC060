#ifndef __VPSS_FUNC_MAC_WCHN_H__
#define __VPSS_FUNC_MAC_WCHN_H__

#include "vpss_define.h"
#include "ice_define.h"
#include "vpss_mac_define.h"
#include "vpss_drv_comm.h"

typedef enum
{
    VPSS_WCHN_ADDR_DATA = 0,//data
    VPSS_WCHN_ADDR_HEAD    ,//cmp head data
    VPSS_WCHN_ADDR_BUTT
} VPSS_WCHN_ADDR_E;

typedef struct
{
} VPSS_CMP_CFG_S;

typedef struct
{
    //cfg
    HI_BOOL                 bEn         ;
    XDP_DATA_TYPE_E         enDataType  ;
    XDP_DATA_WTH            enDataWidth ;
    HI_BOOL                 bFlipEn     ;
    HI_BOOL                 bMirrorEn   ;
    HI_BOOL                 bUvInvEn    ;
    VPSS_DITHER_CFG_S       stDitherCfg ;
    HI_BOOL                 bMmuBypass  ;
    HI_BOOL                 bTunlEn     ;
    //cmp
    XDP_CMP_TYPE_E          enCmpType   ;
    //addr
    XDP_TRIO_ADDR_S         stAddr[VPSS_WCHN_ADDR_BUTT] ;
    // env
    HI_BOOL                 bSetFlag    ;
    HI_BOOL                 bAddrAutoCalcEn;
    HI_BOOL                 bAddrRandModeEn;
    HI_BOOL                 bAddrSafeModeEn;
    XDP_PROC_FMT_E          enDataFmt   ;
    XDP_DATA_RMODE_E        enRdMode    ;
    XDP_RECT_S              stOutRect   ; // offset_x/y have real regs
    HI_U64                  u64Finfo    ;

} VPSS_MAC_WCHN_CFG_S;

//function declare

HI_VOID VPSS_MAC_InitWchnCfg(HI_U32 u32Layer,  VPSS_MAC_WCHN_CFG_S *pstWchnCfg);
HI_VOID VPSS_MAC_SetWchnCfg(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_WCHN_E enLayer, VPSS_MAC_WCHN_CFG_S *pstWchnCfg);
HI_U64 VPSS_MAC_WchnCalcAddrStr(S_VPSS_REGS_TYPE *pstReg, VPSS_MAC_WCHN_E enLayer, VPSS_MAC_WCHN_CFG_S *pstWchnCfg, HI_U64 u64StartAddr, HI_BOOL bRandModeEn);

#endif
