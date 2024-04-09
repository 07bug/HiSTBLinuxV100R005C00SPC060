#ifndef __VDP_HAL_IP_MDATA_H__
#define __VDP_HAL_IP_MDATA_H__

#include "hi_reg_common.h"
#include "vdp_hal_comm.h"

HI_VOID VDP_MDATA_SetChnEn     (  HI_U32 chn_en     );
HI_VOID VDP_MDATA_SetNosecFlag (  HI_U32 nosec_flag );
HI_VOID VDP_MDATA_SetMmuBypass (  HI_U32 mmu_bypass );
HI_VOID VDP_MDATA_SetAviValid  (  HI_U32 avi_valid  );
HI_VOID VDP_MDATA_SetSmdValid  (  HI_U32 smd_valid  );
HI_VOID VDP_MDATA_SetSreqDelay (  HI_U32 sreq_delay );
HI_VOID VDP_MDATA_SetRegup     (  HI_U32 regup      );
HI_VOID VDP_MDATA_SetMaddr     (  HI_U32 maddr      );
HI_VOID VDP_MDATA_SetMburst    (  HI_U32 mburst     );

#if 0
HI_U32  VDP_MDATA_GetWorkAddr  ( S_VDP_REGS_TYPE * pstReg);
HI_U32  VDP_MDATA_GetSendNum   ( S_VDP_REGS_TYPE * pstReg);
HI_U32  VDP_MDATA_GetDebugSta  ( S_VDP_REGS_TYPE * pstReg);
#endif

#endif
