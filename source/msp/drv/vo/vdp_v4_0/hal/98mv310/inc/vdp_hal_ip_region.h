#ifndef __VDP_HAL_IP_REGION_H__
#define __VDP_HAL_IP_REGION_H__

#include "hi_reg_common.h"
#include "vdp_hal_comm.h"


HI_VOID VDP_FDR_VID_SetMrgRdEn       ( HI_U32 offset, HI_U32 rd_en           );
HI_VOID VDP_FDR_VID_SetMrgRdRegion   ( HI_U32 offset, HI_U32 rd_region       );
HI_VOID VDP_FDR_VID_SetMrgLoadMode(HI_U32 offset, HI_U32 load_mode);
HI_VOID VDP_FDR_VID_SetMrgEn         ( HI_U32 offset, HI_U32 mrg_en          );
HI_VOID VDP_FDR_VID_SetMrgMuteEn     ( HI_U32 offset, HI_U32 mrg_mute_en     );
HI_VOID VDP_FDR_VID_SetMrgLmMmuBypass(HI_U32 offset, HI_U32 mrg_mmu_bypass)   ;
HI_VOID VDP_FDR_VID_SetMrgChmMmuBypass(HI_U32 offset, HI_U32 mrg_mmu_bypass)  ;
HI_VOID VDP_FDR_VID_SetMrgCropEn     ( HI_U32 offset, HI_U32 mrg_crop_en     );
HI_VOID VDP_FDR_VID_SetMrgEdgeTyp    ( HI_U32 offset, HI_U32 mrg_edge_typ    );
HI_VOID VDP_FDR_VID_SetMrgEdgeEn     ( HI_U32 offset, HI_U32 mrg_edge_en     );
HI_VOID VDP_FDR_VID_SetMrgYpos       ( HI_U32 offset, HI_U32 mrg_ypos        );
HI_VOID VDP_FDR_VID_SetMrgXpos       ( HI_U32 offset, HI_U32 mrg_xpos        );
HI_VOID VDP_FDR_VID_SetMrgHeight     ( HI_U32 offset, HI_U32 mrg_height      );
HI_VOID VDP_FDR_VID_SetMrgWidth      ( HI_U32 offset, HI_U32 mrg_width       );
HI_VOID VDP_FDR_VID_SetMrgSrcHeight  ( HI_U32 offset, HI_U32 mrg_src_height  );
HI_VOID VDP_FDR_VID_SetMrgSrcWidth   ( HI_U32 offset, HI_U32 mrg_src_width   );
HI_VOID VDP_FDR_VID_SetMrgSrcVoffset ( HI_U32 offset, HI_U32 mrg_src_voffset );
HI_VOID VDP_FDR_VID_SetMrgSrcHoffset ( HI_U32 offset, HI_U32 mrg_src_hoffset );
HI_VOID VDP_FDR_VID_SetMrgYAddr      ( HI_U32 offset, HI_U32 mrg_y_addr      );
HI_VOID VDP_FDR_VID_SetMrgCAddr      ( HI_U32 offset, HI_U32 mrg_c_addr      );
HI_VOID VDP_FDR_VID_SetMrgYStride    ( HI_U32 offset, HI_U32 mrg_y_stride    );
HI_VOID VDP_FDR_VID_SetMrgCStride    ( HI_U32 offset, HI_U32 mrg_c_stride    );
HI_VOID VDP_FDR_VID_SetMrgYhAddr     ( HI_U32 offset, HI_U32 mrg_yh_addr     );
HI_VOID VDP_FDR_VID_SetMrgChAddr     ( HI_U32 offset, HI_U32 mrg_c_addr      );
HI_VOID VDP_FDR_VID_SetMrgYhStride   ( HI_U32 offset, HI_U32 mrg_y_stride    );
HI_VOID VDP_FDR_VID_SetMrgChStride   ( HI_U32 offset, HI_U32 mrg_c_stride    );

#endif
