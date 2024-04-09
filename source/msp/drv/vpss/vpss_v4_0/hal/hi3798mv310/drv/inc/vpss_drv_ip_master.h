#ifndef __VPSS_DRV_IP_MASTER_H__
#define __VPSS_DRV_IP_MASTER_H__

#include "vpss_define.h"
#include "vpss_mac_define.h"
#include "hi_reg_common.h"

typedef enum
{
    VPSS_AXI_EDGE_MODE_128  = 0,
    VPSS_AXI_EDGE_MODE_256 ,
    VPSS_AXI_EDGE_MODE_1024,
    VPSS_AXI_EDGE_MODE_2048,
    VPSS_AXI_EDGE_MODE_4096,
    VPSS_AXI_EDGE_MODE_BUTT
} VPSS_AXI_EDGE_MODE_E;

typedef struct
{
    HI_BOOL bMidEn;
    HI_BOOL bArbEn;
    VPSS_AXI_EDGE_MODE_E enSplitMode;

    HI_U32 u32RdOutstd[VPSS_MASTER_SEL_BUTT];
    HI_U32 u32WrOutstd[VPSS_MASTER_SEL_BUTT];

    HI_U32 u32RchnPrio[64];
    HI_U32 u32WchnPrio[64];

    VPSS_MASTER_SEL_E enRchnSel[64];
    VPSS_MASTER_SEL_E enWchnSel[64];

} VPSS_MASTER_CFG_S;

HI_VOID VPSS_Master_InitCfg(VPSS_MASTER_CFG_S *pstMasterCfg);

HI_VOID VPSS_Master_SetCfg        ( S_VPSS_REGS_TYPE *pstReg, VPSS_MASTER_CFG_S *pstMasterCfg);
HI_VOID VPSS_Master_SetStaticCfg  ( S_VPSS_REGS_TYPE *pstReg, VPSS_MASTER_CFG_S *pstMasterCfg);
HI_VOID VPSS_Master_SetDynamicCfg ( S_VPSS_REGS_TYPE *pstReg, VPSS_MASTER_CFG_S *pstMasterCfg);

#endif

