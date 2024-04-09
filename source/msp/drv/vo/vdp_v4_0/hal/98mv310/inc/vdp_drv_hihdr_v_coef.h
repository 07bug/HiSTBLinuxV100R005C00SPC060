
#ifndef __VDP_DRV_HIHDRV_COEF_H__
#define __VDP_DRV_HIHDRV_COEF_H__

#include "vdp_gen_coef.h"
#include "vdp_drv_ip_hihdr_v.h"
#include "vdp_drv_vid.h"

#ifndef  __DISP_PLATFORM_BOOT__
HI_VOID VDP_DRV_SetHdrVCoef(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg);
#endif

#endif
