#include "hi_type.h"
#include "vdp_define.h"
#include "vdp_drv_pq_hdr.h"
#include "vdp_drv_hdr.h"
#include "vdp_hal_hdr.h"
#include "vdp_hal_vid.h"
#include "vdp_hal_gfx.h"
#include "vdp_hal_mmu.h"
#include "vdp_hal_chn.h"
#include "drv_pq_ext.h"
#include "vdp_drv_func.h"

#include "vdp_drv_comm.h"
#include "vdp_drv_pq_zme.h"
#include "vdp_hal_comm.h"
#if VDP_CBB_FPGA
#include "hi_drv_mmz.h"
#endif
#include "vdp_drv_hihdr.h"
#include "vdp_drv_bt2020.h"




HI_VOID VDP_DRV_SetHisiGdmHlgInHlgOut(VDP_HISI_HDR_CFG_S  *stHdrCfg);
HI_VOID VDP_DRV_SetHisiGdmHlgInSdrOut(VDP_HISI_HDR_CFG_S  *stHdrCfg);
HI_VOID VDP_DRV_SetHisiGdmHlgInHdr10Out(VDP_HISI_HDR_CFG_S  *stHdrCfg);
HI_S32 VDP_DRV_SetHisiVdmHlg2Hdr10(HI_VOID);

HI_S32 VDP_DRV_SetHisiVdmHdr102Hlg(HI_VOID);
HI_VOID VDP_DRV_SetHisiGdmHdr10InHlgOut(VDP_HISI_HDR_CFG_S  *stHdrCfg);





