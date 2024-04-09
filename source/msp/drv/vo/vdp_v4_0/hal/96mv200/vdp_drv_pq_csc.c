#include "vdp_drv_pq_ext.h"
#include "hi_type.h"
#include "vdp_hal_vid.h"
#include "vdp_drv_coef.h"
#include "vdp_drv_pq_csc.h"
#include "vdp_func_pq_csc.h"
#include "vdp_hal_comm.h"
#include "vdp_drv_comm.h"
extern VDP_COEF_ADDR_S gstVdpCoefBufAddr;
//extern  S_VDP_REGS_TYPE *pVdpReg;

HI_S32 VDP_PQ_GetCSCCoefPtr(HI_VOID *pstCscCtrl, VDP_CSC_MODE_E enCbbCscMode, HI_PQ_CSC_MODE_E enCscMode, HI_VOID *pstCscCoef, HI_VOID *pstCscDcCoef)
{
#ifdef VDP_PQ_STRATEGY
    DRV_PQ_GetCSCCoef(pstCscCtrl, enCscMode, pstCscCoef, pstCscDcCoef);
#else
    VDP_FUNC_GetCSCCoef(pstCscCtrl, enCbbCscMode, pstCscCoef, pstCscDcCoef);
#endif

    return HI_SUCCESS;

}

