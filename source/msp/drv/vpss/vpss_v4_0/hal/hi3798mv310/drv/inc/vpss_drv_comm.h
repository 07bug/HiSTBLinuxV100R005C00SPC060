
#ifndef __VPSS_DRV_COMM_H__
#define __VPSS_DRV_COMM_H__

#include "vpss_define.h"
#include "vpss_hal_comm.h"
#include "vpss_mac_define.h"
#include <linux/string.h>
#include <linux/math64.h>
//#include "xdp_basefunc.h"

#if EDA_TEST
#include "vpss_env_def.h"
#include "vdp_frw.h"
#endif

typedef struct
{
    XDP_TRIO_ADDR_S stRchnAddr[VPSS_RCHN_MAX];
    XDP_TRIO_ADDR_S stWchnAddr[VPSS_WCHN_MAX];
    XDP_TRIO_ADDR_S stRchnHeadAddr[VPSS_RCHN_MAX];
    XDP_TRIO_ADDR_S stWchnHeadAddr[VPSS_WCHN_MAX];
    XDP_TRIO_ADDR_S stRchn2BAddr[VPSS_RCHN_MAX];
    XDP_TRIO_ADDR_S stWchn2BAddr[VPSS_WCHN_MAX];
    HI_U64 u64AddrRdStt;
    HI_U64 u64AddrWrStt;
    HI_U64 u64AddrWrSttMe;
} VPSS_ADDR_CFG_S;

extern VPSS_ADDR_CFG_S  gstVpssAddrCfg;
extern HI_U64  gu64VpssSafeAddr  ;
extern HI_U64  gu64VpssUnsafeAddr;

HI_VOID VPSS_AddrInit(VPSS_ADDR_CFG_S *pstVpssAddrCfg, HI_U64 u64BaseAddr);

HI_U32 VpssCalcChmWth(HI_U32 u32LumWth, XDP_PROC_FMT_E enDataFmt);
HI_U32 VpssCalcChmHgt(HI_U32 u32LumHgt, XDP_PROC_FMT_E enDataFmt);

HI_U64 VpssUpAlign  (HI_U64 u64DataIn, HI_U64 u64Align);
HI_U64 VpssDownAlign(HI_U64 u64DataIn, HI_U64 u64Align);

HI_U64 VPSS_CalcAddrStr(XDP_SOLO_ADDR_S *pstAddr, XDP_RECT_S *pstRect, HI_U32 u32DataWidth, HI_BOOL bRandModeEn);

HI_U32 uGetRandEx(HI_U32 max, HI_U32 min);
HI_S32 sGetRandEx(HI_S32 max, HI_S32 min);
unsigned int uGetRand(unsigned int low, unsigned high);
int sGetRand(int low, int high);


#endif//__VPSS_DRV_COMM_H__
