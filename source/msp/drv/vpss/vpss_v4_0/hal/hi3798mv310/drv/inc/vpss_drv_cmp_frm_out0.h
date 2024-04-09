#ifndef __VPSS_DRV_CMP_FRM_OUT0_H__
#define __VPSS_DRV_CMP_FRM_OUT0_H__

#include "vpss_define.h"
#include "ice_define.h"
#include "hi_reg_common.h"
#include "vpss_mac_define.h"

#include "cmp_hqv4_config_2ppc.h"

HI_VOID VPSS_MAC_SetCmpFrmOut0 (S_VPSS_REGS_TYPE *pstReg, ICE_FRM_CFG_S *pstIceCfg);
HI_VOID VPSS_ICE_SetCmpFrmMerge(S_VPSS_REGS_TYPE *pstReg, CMP_HQV4_PARM_T *pCmpParm, HI_BOOL bCmpEn);

#endif

