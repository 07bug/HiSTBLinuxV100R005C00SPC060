#ifndef __FUNC_PQ_CSC_H__
#define __FUNC_PQ_CSC_H__
#include "hi_type.h"
#include "vdp_define.h"
#include "vdp_drv_comm.h"
#include "vdp_drv_pq_csc.h"

HI_S32 VDP_FUNC_GetCSCCoef(HI_PQ_CSC_CRTL_S* pstCscCtrl, VDP_CSC_MODE_E enCscMode, HI_PQ_CSC_COEF_S* pstCscCoef, HI_PQ_CSC_DCCOEF_S* pstCscDcCoef);

HI_VOID VDP_FUNC_SetCSC1DcCoef(HI_PQ_CSC_DCCOEF_S  *pstCscDcCoef);
HI_VOID VDP_FUNC_SetCSC1Coef(HI_PQ_CSC_COEF_S  *pstCscCoef);

HI_VOID VDP_FUNC_SetCSC2DcCoef(HI_PQ_CSC_DCCOEF_S  *pstCscDcCoef);
HI_VOID VDP_FUNC_SetCSC2Coef(HI_PQ_CSC_COEF_S  *pstCscCoef);

#endif
