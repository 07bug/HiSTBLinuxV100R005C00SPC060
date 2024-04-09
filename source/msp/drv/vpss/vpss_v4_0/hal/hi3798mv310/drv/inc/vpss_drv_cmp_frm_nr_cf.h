#ifndef __VPSS_DRV_CMP_FRM_NR_CF_H__
#define __VPSS_DRV_CMP_FRM_NR_CF_H__

#include "vpss_define.h"
#include "ice_define.h"
#include "hi_reg_common.h"
#include "vpss_mac_define.h"

#include "codec_hqv4_if.h"
#include "cmp_hqv4_config_2ppc.h"

HI_VOID VPSS_ICE_SetCmpFrmNrCf      (S_VPSS_REGS_TYPE *pstReg, ICE_FRM_CFG_S *pstIceCfg);
HI_VOID VPSS_ICE_SetCmpFrmAloneCfY  (S_VPSS_REGS_TYPE *pstReg, CMP_HQV4_ALONE_PARM_T *pCmpParm, HI_BOOL bCmpEn);
HI_VOID VPSS_ICE_SetCmpFrmAloneCfC  (S_VPSS_REGS_TYPE *pstReg, CMP_HQV4_ALONE_PARM_T *pCmpParm, HI_BOOL bCmpEn);

#endif

