#ifndef __VDP_HAL_IP_CAP_H__
#define __VDP_HAL_IP_CAP_H__

#include "hi_reg_common.h"
#include "vdp_hal_comm.h"

HI_VOID VDP_CAP_SetCapCkGtEn      (HI_U32 offset, HI_U32 cap_ck_gt_en);
HI_VOID VDP_CAP_SetWbcCmpEn       (HI_U32 offset, HI_U32 wbc_cmp_en       );
HI_VOID VDP_CAP_SetWbc3dMode      (HI_U32 offset, HI_U32 wbc_3d_mode      );
HI_VOID VDP_CAP_SetChksumEn       (HI_U32 offset, HI_U32 chksum_en        );
HI_VOID VDP_CAP_SetFlipEn         (HI_U32 offset, HI_U32 flip_en          );
HI_VOID VDP_CAP_SetUvOrder        (HI_U32 offset, HI_U32 uv_order         );
HI_VOID VDP_CAP_SetDataWidth      (HI_U32 offset, HI_U32 data_width       );
HI_VOID VDP_CAP_SetWbcLen         (HI_U32 offset, HI_U32 wbc_len          );
HI_VOID VDP_CAP_SetReqInterval    (HI_U32 offset, HI_U32 req_interval     );
HI_VOID VDP_CAP_SetSttBypass      (HI_U32 offset, HI_U32 stt_bypass       );
HI_VOID VDP_CAP_SetMmu3dBypass    (HI_U32 offset, HI_U32 mmu_3d_bypass    );
HI_VOID VDP_CAP_SetMmu2dBypass    (HI_U32 offset, HI_U32 mmu_2d_bypass    );
HI_VOID VDP_CAP_SetLowdlyEn       (HI_U32 offset, HI_U32 lowdly_en        );
HI_VOID VDP_CAP_SetLowdlyTest     (HI_U32 offset, HI_U32 lowdly_test      );
HI_VOID VDP_CAP_SetPartfnsLineNum (HI_U32 offset, HI_U32 partfns_line_num );
HI_VOID VDP_CAP_SetWbPerLineNum   (HI_U32 offset, HI_U32 wb_per_line_num  );
HI_VOID VDP_CAP_SetWbcTunladdrH   (HI_U32 offset, HI_U32 wbc_tunladdr_h   );
HI_VOID VDP_CAP_SetWbcTunladdrL   (HI_U32 offset, HI_U32 wbc_tunladdr_l   );
HI_VOID VDP_CAP_SetPartFinish     (HI_U32 offset, HI_U32 part_finish      );
HI_VOID VDP_CAP_SetWbcYaddrH      (HI_U32 offset, HI_U32 wbc_yaddr_h      );
HI_VOID VDP_CAP_SetWbcYaddrL      (HI_U32 offset, HI_U32 wbc_yaddr_l      );
HI_VOID VDP_CAP_SetWbcCaddrH      (HI_U32 offset, HI_U32 wbc_caddr_h      );
HI_VOID VDP_CAP_SetWbcCaddrL      (HI_U32 offset, HI_U32 wbc_caddr_l      );
HI_VOID VDP_CAP_SetWbcYstride     (HI_U32 offset, HI_U32 wbc_ystride      );
HI_VOID VDP_CAP_SetWbcCstride     (HI_U32 offset, HI_U32 wbc_cstride      );
HI_VOID VDP_CAP_SetWbcYnaddrH     (HI_U32 offset, HI_U32 wbc_ynaddr_h     );
HI_VOID VDP_CAP_SetWbcYnaddrL     (HI_U32 offset, HI_U32 wbc_ynaddr_l     );
HI_VOID VDP_CAP_SetWbcCnaddrH     (HI_U32 offset, HI_U32 wbc_cnaddr_h     );
HI_VOID VDP_CAP_SetWbcCnaddrL     (HI_U32 offset, HI_U32 wbc_cnaddr_l     );
HI_VOID VDP_CAP_SetWbcYnstride    (HI_U32 offset, HI_U32 wbc_ynstride     );
HI_VOID VDP_CAP_SetWbcCnstride    (HI_U32 offset, HI_U32 wbc_cnstride     );
HI_VOID VDP_CAP_SetWbcSttAddrH    (HI_U32 offset, HI_U32 wbc_stt_addr_h   );
HI_VOID VDP_CAP_SetWbcSttAddrL    (HI_U32 offset, HI_U32 wbc_stt_addr_l   );
HI_VOID VDP_CAP_SetCapHeight      (HI_U32 offset, HI_U32 cap_height       );
HI_VOID VDP_CAP_SetCapWidth       (HI_U32 offset, HI_U32 cap_width        );
HI_VOID VDP_CAP_SetCapInfoH       (HI_U32 offset, HI_U32 cap_info_h       );
HI_VOID VDP_CAP_SetCapInfoL       (HI_U32 offset, HI_U32 cap_info_l       );

#endif
