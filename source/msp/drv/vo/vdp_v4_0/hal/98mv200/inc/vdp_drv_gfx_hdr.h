#include "hi_type.h"

#ifndef  __DISP_PLATFORM_BOOT__
#include "drv_pq_ext_hdr.h"

#if (!EDA_TEST)
#include <linux/string.h>
#include <linux/kernel.h>
#else
#include <string.h>
#endif

HI_S32  XDP_DRV_GfxHdrRegClean(HI_BOOL bRgbOutColorSpace);
HI_S32 VDP_DRV_SetHisiGfxHdr(HI_PQ_GFXHDR_CFG  *pstPqGfxHdrCfg, VDP_CLR_SPACE_E enOutColorSpace);


#endif
