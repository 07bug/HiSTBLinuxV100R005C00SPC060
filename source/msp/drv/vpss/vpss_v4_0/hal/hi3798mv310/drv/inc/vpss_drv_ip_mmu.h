#ifndef __VPSS_DRV_IP_MMU_H__
#define __VPSS_DRV_IP_MMU_H__

#include "vpss_define.h"
#include "hi_reg_common.h"
#include "xdp_drv_ip_mmu.h"


HI_VOID VPSS_MMU_InitCfg(XDP_MMU_CFG_S *pstMmuCfg);
HI_VOID VPSS_MMU_SetCfg (S_VPSS_REGS_TYPE *pstReg, HI_U32 enLayer, XDP_MMU_CFG_S *pstMmuCfg);

#endif

