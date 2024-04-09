#ifndef __VPSS_DRV_CMP_FRM_NR_H__
#define __VPSS_DRV_CMP_FRM_NR_H__

#include "vpss_define.h"
#include "ice_define.h"
#include "hi_reg_common.h"
#include "vpss_mac_define.h"

#include "cmp_hqv4_config_2ppc.h"

HI_VOID VPSS_MAC_SetDcmpFrmNr     (S_VPSS_REGS_TYPE *pstReg, ICE_FRM_CFG_S *pstIceCfg);
HI_VOID VPSS_MAC_SetCmpFrmNr      (S_VPSS_REGS_TYPE *pstReg, ICE_FRM_CFG_S *pstIceCfg);
HI_VOID VPSS_ICE_SetDcmpFrmAloneY (S_VPSS_REGS_TYPE *pstReg, DCMP_HQV4_ALONE_PARM_T *pCmpParm, HI_BOOL bDcmpEn);
HI_VOID VPSS_ICE_SetDcmpFrmAloneC (S_VPSS_REGS_TYPE *pstReg, DCMP_HQV4_ALONE_PARM_T *pCmpParm, HI_BOOL bDcmpEn);
HI_VOID VPSS_ICE_SetCmpFrmAloneY  (S_VPSS_REGS_TYPE *pstReg, CMP_HQV4_ALONE_PARM_T *pCmpParm, HI_BOOL bCmpEn);
HI_VOID VPSS_ICE_SetCmpFrmAloneC  (S_VPSS_REGS_TYPE *pstReg, CMP_HQV4_ALONE_PARM_T *pCmpParm, HI_BOOL bCmpEn);

#endif

