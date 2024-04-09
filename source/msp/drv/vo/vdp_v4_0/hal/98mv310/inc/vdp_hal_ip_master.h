#ifndef __VDP_HAL_IP_MASTER_H__
#define __VDP_HAL_IP_MASTER_H__

#include "vdp_define.h"
#include "vdp_hal_comm.h"

HI_VOID VDP_MASTER_SetMstr2Woutstanding (HI_U32 mstr2_woutstanding);
HI_VOID VDP_MASTER_SetMstr2Routstanding (HI_U32 mstr2_routstanding);
HI_VOID VDP_MASTER_SetMstr1Woutstanding (HI_U32 mstr1_woutstanding);
HI_VOID VDP_MASTER_SetMstr1Routstanding (HI_U32 mstr1_routstanding);
HI_VOID VDP_MASTER_SetMstr0Woutstanding (HI_U32 mstr0_woutstanding);
HI_VOID VDP_MASTER_SetMstr0Routstanding (HI_U32 mstr0_routstanding);
HI_VOID VDP_MASTER_SetWportSel          (HI_U32 wport_sel);
HI_VOID VDP_MASTER_SetMidEnable         (HI_U32 mid_enable);
HI_VOID VDP_MASTER_SetArbMode           (HI_U32 arb_mode);
HI_VOID VDP_MASTER_SetSplitMode         (HI_U32 split_mode);
HI_VOID VDP_MASTER_SetRchnPrio          (HI_U32 id, HI_U32 prio);
HI_VOID VDP_MASTER_SetWchnPrio          (HI_U32 id, HI_U32 prio);
HI_VOID VDP_MASTER_SetBusErrorClr       (HI_U32 bus_error_clr);
HI_VOID VDP_MASTER_SetMst2WError        (HI_U32 mst2_w_error);
HI_VOID VDP_MASTER_SetMst2RError        (HI_U32 mst2_r_error);
HI_VOID VDP_MASTER_SetMst1WError        (HI_U32 mst1_w_error);
HI_VOID VDP_MASTER_SetMst1RError        (HI_U32 mst1_r_error);
HI_VOID VDP_MASTER_SetMst0WError        (HI_U32 mst0_w_error);
HI_VOID VDP_MASTER_SetMst0RError        (HI_U32 mst0_r_error);
HI_VOID VDP_MASTER_SetMstAxiDetEnable   (HI_U32 axi_det_enable);

#endif

