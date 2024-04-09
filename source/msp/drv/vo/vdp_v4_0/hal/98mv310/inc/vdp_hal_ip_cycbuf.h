#ifndef __VDP_HAL_IP_CYCBUF_H__
#define __VDP_HAL_IP_CYCBUF_H__

#include "hi_reg_common.h"
#include "vdp_hal_comm.h"


HI_VOID VDP_CYCBUF_SetVid0BindEn      (  HI_U32 offset, HI_U32 vid0_bind_en      );
HI_VOID VDP_CYCBUF_SetVid0SuccEn      (  HI_U32 offset, HI_U32 vid0_succ_en      );
HI_VOID VDP_CYCBUF_SetVid1BindEn      (  HI_U32 offset, HI_U32 vid1_bind_en      );
HI_VOID VDP_CYCBUF_SetVid1SuccEn      (  HI_U32 offset, HI_U32 vid1_succ_en      );
HI_VOID VDP_CYCBUF_SetGfxBindEn       (  HI_U32 offset, HI_U32 gfx_bind_en       );
HI_VOID VDP_CYCBUF_SetGfxSuccEn       (  HI_U32 offset, HI_U32 gfx_succ_en       );
HI_VOID VDP_CYCBUF_SetRegup           (  HI_U32 offset, HI_U32 regup             );
HI_VOID VDP_CYCBUF_SetSmmuBypass      (  HI_U32 offset, HI_U32 smmu_bypass       );
HI_VOID VDP_CYCBUF_SetDebugSta0       (  HI_U32 offset, HI_U32 debug_sta0        );
HI_VOID VDP_CYCBUF_SetDebugSta1       (  HI_U32 offset, HI_U32 debug_sta1        );
HI_VOID VDP_CYCBUF_SetDebugSta2       (  HI_U32 offset, HI_U32 debug_sta2        );
HI_VOID VDP_CYCBUF_SetDebugSta3       (  HI_U32 offset, HI_U32 debug_sta3        );

HI_VOID VDP_CYCBUF_SetFrmChangeMode   (  HI_U32 offset, HI_U32 frm_change_mode   );
HI_VOID VDP_CYCBUF_SetDtvMode         (  HI_U32 offset, HI_U32 dtv_mode          );
HI_VOID VDP_CYCBUF_SetResetMode       (  HI_U32 offset, HI_U32 reset_mode        );
HI_VOID VDP_CYCBUF_SetResetEn         (  HI_U32 offset, HI_U32 reset_en          );
HI_VOID VDP_CYCBUF_SetBurstMask       (  HI_U32 offset, HI_U32 burst_mask        );
HI_VOID VDP_CYCBUF_SetHburstNum       (  HI_U32 offset, HI_U32 hburst_num        );
HI_VOID VDP_CYCBUF_SetLburstNum       (  HI_U32 offset, HI_U32 lburst_num        );
HI_VOID VDP_CYCBUF_SetWriteReady      (  HI_U32 offset, HI_U32 write_ready       );
HI_VOID VDP_CYCBUF_SetFirstFieldSel   (  HI_U32 offset, HI_U32 first_field_sel   );
HI_VOID VDP_CYCBUF_SetBtmDispNum      (  HI_U32 offset, HI_U32 btm_disp_num      );
HI_VOID VDP_CYCBUF_SetTopDispNum      (  HI_U32 offset, HI_U32 top_disp_num      );
HI_VOID VDP_CYCBUF_SetDtvCfgAddr      (  HI_U32 offset, HI_U32 dtv_cfg_addr      );
HI_VOID VDP_CYCBUF_SetDtvBackAddr     (  HI_U32 offset, HI_U32 dtv_back_addr     );
HI_VOID VDP_CYCBUF_SetDtvBackPassword (  HI_U32 offset, HI_U32 dtv_back_password );
HI_VOID VDP_CYCBUF_SetMuteClr         (  HI_U32 offset, HI_U32 mute_clr          );
HI_VOID VDP_CYCBUF_SetCfgReady        (  HI_U32 offset, HI_U32 cfg_ready         );
HI_VOID VDP_CYCBUF_SetDtvChangeAddr   (  HI_U32 offset, HI_U32 dtv_change_addr   );
HI_VOID VDP_CYCBUF_SetDtvDispAddr     (  HI_U32 offset, HI_U32 dtv_disp_addr     );
HI_VOID VDP_CYCBUF_SetBackNum         (  HI_U32 offset, HI_U32 back_num          );
HI_VOID VDP_CYCBUF_SetBackErr         (  HI_U32 offset, HI_U32 back_err          );
HI_VOID VDP_CYCBUF_SetSendErr         (  HI_U32 offset, HI_U32 send_err          );
HI_VOID VDP_CYCBUF_SetDebugClr        (  HI_U32 offset, HI_U32 debug_clr         );
HI_VOID VDP_CYCBUF_SetDispCnt         (  HI_U32 offset, HI_U32 disp_cnt          );
HI_VOID VDP_CYCBUF_SetBackFifoSta     (  HI_U32 offset, HI_U32 back_fifo_sta     );
HI_VOID VDP_CYCBUF_SetDispFifoSta     (  HI_U32 offset, HI_U32 disp_fifo_sta     );
HI_VOID VDP_CYCBUF_SetUnderloadSta    (  HI_U32 offset, HI_U32 underload_sta     );
HI_VOID VDP_CYCBUF_SetUnderloadCnt    (  HI_U32 offset, HI_U32 underload_cnt     );

HI_U32  VDP_CYCBUF_GetDtvBackAddr     (  HI_U32 offset);
HI_U32  VDP_CYCBUF_GetDtvChangeAddr   (  HI_U32 offset);
HI_U32  VDP_CYCBUF_GetDtvDispAddr     (  HI_U32 offset);
HI_U32  VDP_CYCBUF_GetBackNum         (  HI_U32 offset);
HI_U32  VDP_CYCBUF_GetBackErr         (  HI_U32 offset);
HI_U32  VDP_CYCBUF_GetSendErr         (  HI_U32 offset);
HI_U32  VDP_CYCBUF_GetDispCnt         (  HI_U32 offset);
HI_U32  VDP_CYCBUF_GetBackFifoSta     (  HI_U32 offset);
HI_U32  VDP_CYCBUF_GetDispFifoSta     (  HI_U32 offset);


#endif

