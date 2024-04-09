#ifndef __HIHDR_COEF_H__
#define __HIHDR_COEF_H__


#include "hi_type.h"
#include "vdp_ip_define.h"
#include "vdp_drv_vid.h"

#include "vdp_drv_pq_ext.h"
#include "vdp_drv_ip_gdm.h"



// Lut Size
#define DEGMM_LUT_SIZE      64
#define TMAP_LUT_SIZE       64
#define GMM_LUT_SIZE        64

#if 0
typedef struct VDP_HIHDR_EXTERN
{
    HI_BOOL                bRegionEn;
    HI_U32                 u32RegionNO;
    HI_BOOL                bRegionModeEn;
    HI_U32                 u32LayerZorder;

    VDP_DATA_RMODE_E       enReadMode;

    VDP_DRAW_MODE_E        enDrawMode;
    VDP_DRAW_PIXEL_MODE_E  enDrawPixelMode;
    HI_BOOL                bHzmeEn;
    VDP_HZME_MODE_E  enHzmeMode;//add by hyx t28
    VDP_RECT_S             stZme2InRect;
    VDP_DISP_MODE_E        enDispMode;

} VDP_HIHDR_EXTERN_S;



typedef struct VDP_HISI_HDR_CFG_S
{
    HIHDR_SCENE_MODE_E eHiHdrMode;
    GDM_SCENE_MODE_E   enHiHdrGfxMode;
    HI_BOOL            bMuteEn;
    VDP_SRC_INFO_S         stSrcInfo;
    VDP_RECT_S             stCropRect;
    VDP_RECT_S             stVideoRect;
    VDP_RECT_S             stDispRect;
    //VDP_RECT_S               stZme1OutRect;
    VDP_DISP_INF_S          stVdpDispInfo;

    VDP_HIHDR_EXTERN_S     stHdrVdpCfgExt;

    VDP_ZME_DRV_PARA_S pstZmeDrvPara;//add by hyx
    HI_U32 u32LayerId;

} VDP_HISI_HDR_CFG_S;
#endif


#endif
