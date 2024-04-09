#include "hi_type.h"
#include "vdp_drv_gfx_hdr.h"

HI_S32  XDP_DRV_GfxHdrRegClean(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetHiHdrGfxCfg(HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    return HI_SUCCESS;
}

HI_S32 VDP_DRV_SetHisiGfxHdr(HI_PQ_GFXHDR_CFG *pstPqGfxHdrCfg)
{
    XDP_DRV_GfxHdrRegClean();
    return HI_SUCCESS;
}

