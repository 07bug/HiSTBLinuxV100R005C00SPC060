
#ifndef __VDM_COEF_H__
#define __VDM_COEF_H__


#include "hi_type.h"
#include "vdp_hdr_cfg.h"



#ifndef  __DISP_PLATFORM_BOOT__
HI_VOID Vdp_Drv_SetHdrVdmCoef_gmm(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg);
HI_VOID Vdp_Drv_SetHdrVdmCoef_Degmm(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg);
HI_VOID Vdp_Drv_SetHdrVdmCoef_Tmapping(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg);
HI_VOID Vdp_Drv_SetHdrVdmCoef_Smapping(HIHDR_SCENE_MODE_E enHiHdrMode, HI_PQ_HDR_CFG *pstHiHdrCfg);

#endif

#endif
