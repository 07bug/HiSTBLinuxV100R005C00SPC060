#ifndef __DRV_PQ_CSC_H__
#define __DRV_PQ_CSC_H__
#if EDA_TEST
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif

#include "vdp_ip_define.h"
#include "vdp_drv_pq_ext.h"


HI_S32 VDP_PQ_GetCSCCoefPtr(HI_VOID* pstCscCtrl,VDP_CSC_MODE_E enCbbCscMode, HI_PQ_CSC_MODE_E enCscMode, HI_VOID* pstCscCoef, HI_VOID* pstCscDcCoef);

#endif
