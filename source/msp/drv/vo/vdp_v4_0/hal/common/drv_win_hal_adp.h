#ifndef __WIN_HAL_ADP_H
#define __WIN_HAL_ADP_H
#include "drv_pq_ext.h"
HI_S32 Chip_Specific_LayerZmeFunc(HI_PQ_ZME_LAYER_E u32LayerId,
                                  HI_PQ_ZME_PARA_IN_S *pstZmeI,
                                  HI_U32     bFirlterEnable);


HI_VOID Chip_Specific_CBM_GetMixvPrio(VDP_CBM_MIX_E enMixer, HI_U32 u32prio, HI_U32 *pu32layer_id);
#endif
