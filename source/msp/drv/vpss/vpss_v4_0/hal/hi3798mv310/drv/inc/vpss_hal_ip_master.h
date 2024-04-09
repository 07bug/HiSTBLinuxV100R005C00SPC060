#ifndef __VPSS_HAL_IP_MASTER_H__
#define __VPSS_HAL_IP_MASTER_H__

#include "vpss_define.h"
#include "hi_reg_common.h"

HI_VOID VPSS_MASTER_SetMstr2Woutstanding ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr2_woutstanding);
HI_VOID VPSS_MASTER_SetMstr2Routstanding ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr2_routstanding);
HI_VOID VPSS_MASTER_SetMstr1Woutstanding ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr1_woutstanding);
HI_VOID VPSS_MASTER_SetMstr1Routstanding ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr1_routstanding);
HI_VOID VPSS_MASTER_SetMstr0Woutstanding ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr0_woutstanding);
HI_VOID VPSS_MASTER_SetMstr0Routstanding ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mstr0_routstanding);
HI_VOID VPSS_MASTER_SetMidEnable         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mid_enable);
HI_VOID VPSS_MASTER_SetArbMode           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 arb_mode);
HI_VOID VPSS_MASTER_SetSplitMode         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 split_mode);


HI_VOID VPSS_MASTER_SetRchnPrio          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 id, HI_U32 prio);
HI_VOID VPSS_MASTER_SetWchnPrio          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 id, HI_U32 prio);
HI_VOID VPSS_MASTER_SetRchnSel           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 id, HI_U32 sel );
HI_VOID VPSS_MASTER_SetWchnSel           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 id, HI_U32 sel );

HI_VOID VPSS_MASTER_SetBusErrorClr       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 bus_error_clr);
HI_VOID VPSS_MASTER_SetMst2WError        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mst2_w_error);
HI_VOID VPSS_MASTER_SetMst2RError        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mst2_r_error);
HI_VOID VPSS_MASTER_SetMst1WError        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mst1_w_error);
HI_VOID VPSS_MASTER_SetMst1RError        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mst1_r_error);
HI_VOID VPSS_MASTER_SetMst0WError        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mst0_w_error);
HI_VOID VPSS_MASTER_SetMst0RError        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 mst0_r_error);

#endif
