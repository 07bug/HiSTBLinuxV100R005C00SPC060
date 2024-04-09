#include "hi_type.h"
#include "vdp_drv_comm.h"
#include "vdp_drv_wbc.h"
#include "vdp_drv_vid.h"
//#include "vdp_hal_hdr.h"
#include "vdp_drv_pq_csc.h"
//#include "vdp_drv_pq_zme.h"
#include "vdp_drv_vid.h"
#include "vdp_hal_mmu.h"

#if (VDP_CBB_FPGA &&  !defined(__DISP_PLATFORM_BOOT__))

#include <linux/string.h>
#include <linux/kernel.h>
#endif

extern VDP_COEF_ADDR_S gstVdpCoefBufAddr;
HI_S32 VDP_DRV_GetWbcZmeStrategy(VDP_DRV_WBC_ZME_INFO_S *pstZmeInfo,
                                                HI_PQ_ZME_COEF_RATIO_E  *penHiPqZmeCoefRatio,
                                                HI_PQ_ZME_COEF_TYPE_E enPqZmeCoefRatio,
                                                VDP_PROC_FMT_E  enInZmeFmt,
                                                VDP_PROC_FMT_E  enOutZmeFmt,
                                                HI_U32 u32Ration)
{
    return  HI_SUCCESS;
}

HI_S32 VDP_DRV_SetWbcZme(HI_U32 u32LayerId, VDP_DRV_WBC_ZME_INFO_S *pstZmeInfo)
{
    return  HI_SUCCESS;


}

HI_S32 VDP_DRV_SetWbcDitherMode(HI_U32 u32LayerId, VDP_WBC_DITHER_MODE_E enDitherMode)
{
    return  HI_SUCCESS;
}

HI_S32 VDP_DRV_SetWbcLayer(HI_U32 u32LayerId, VDP_LAYER_WBC_INFO_S *pstInfo)
{
    return  HI_SUCCESS;

}

