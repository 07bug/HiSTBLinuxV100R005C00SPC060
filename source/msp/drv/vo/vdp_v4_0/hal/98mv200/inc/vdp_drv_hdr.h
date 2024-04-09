#ifndef __DRV_HDR_H__
#define __DRV_HDR_H__

#include "vdp_drv_vid.h"
#include "vdp_dm_typefxp.h"

typedef enum tagXDP_DOLBY_CFG_MODE_E
{
    //dolby 2_3 case
    XDP_DOVI_BC_IN_DOVI_IPT_OUT    = 0x0  ,
    XDP_DOVI_BC_IN_HDR10_OUT_CERT      ,
    XDP_DOVI_BC_IN_HDR10_OUT,
    XDP_DOVI_BC_IN_SDR_OUT_CERT        ,
    XDP_DOVI_BC_IN_SDR_OUT             ,
    XDP_DOVI_NBC_IN_HDR10_OUT_CERT     ,
    XDP_DOVI_NBC_IN_HDR10_OUT         ,
    XDP_DOVI_NBC_IN_DOVI_IPT_OUT       ,
    XDP_DOVI_NBC_IN_SDR_OUT_CERT       ,
    XDP_DOVI_NBC_IN_SDR_OUT       ,

    XDP_HDR10_IN_HDR10_OUT_CERT        ,
    XDP_HDR10_IN_HDR10_OUT             ,
    XDP_HDR10_IN_SDR_OUT_CERT          ,
    XDP_HDR10_IN_SDR_OUT               ,
    XDP_HDR10_IN_DOLBY_OUT             ,

    XDP_SDR_IN_HDR10_OUT_CERT        ,
    XDP_SDR_IN_HDR10_OUT        ,
    XDP_SDR_IN_DOLBY_OUT        ,


    XDP_DOVI_NBC_IN_SDR_YUV_OUT_CERT,
    XDP_DOVI_BC_IN_SDR_YUV_OUT_CERT,
    XDP_DOVI_HDR10_IN_SDR_YUV_OUT_CERT,
    XDP_DOVI_BC_IPT_IN_DOVI_IPT_OUT,
    XDP_DOVI_BC_IN_SDR_OUT_HISI,
    XDP_DOVI_NBC_IN_SDR_OUT_HISI,
    XDP_HDR10_IN_SDR_OUT_HISI,
    XDP_HDR_CFG_MODE_BUTT

} XDP_DOLBY_CFG_MODE_E;



typedef struct
{
    HI_BOOL bPreZme;
    HI_BOOL bPreZmeFir;

} VDP_PREZME_CONFIG_S;

typedef enum tagVDP_HDR_OMAPPING_POSITION_E
{
    VDP_HDR_OMAPPING_POSITION_CBM = 0,
    VDP_HDR_OMAPPING_POSITION_VP = 1,

    VDP_HDR_OMAPPING_POSITION_BUTT

} VDP_HDR_OMAPPING_POSITION_E;

typedef struct
{
    //enable
    HI_BOOL bHdrEn           ;
    HI_BOOL bBlEn            ;
    HI_BOOL bElEn            ;
    HI_BOOL bComposerEn      ;
    HI_BOOL bEdrEn           ;
    HI_BOOL bEdrMdEn         ;
    HI_BOOL bEdrDsEn         ;

    //vdm
    HI_BOOL bVdmYuv2RgbEn;
    HI_BOOL bVdmV0Yuv2RgbEn;
    HI_BOOL bVdmV1Yuv2RgbEn ;
    HI_BOOL bVdmNormEn       ;
    HI_BOOL bVdmDegmmEn;
    HI_BOOL bVdmRgb2LmsEn;
    HI_BOOL bVdmGmmEn;
    HI_BOOL bVdmV0GmmEn;     ;
    HI_BOOL bVdmV1GmmEn  ;
    HI_BOOL bCvm1Lms2IptEn;
    HI_BOOL bVdmIptInEn;
    HI_BOOL bVdmS2UEn;

    //gdm
    HI_BOOL bGdmEn           ;
    HI_BOOL bGdmRgb2LmsEn;
    HI_BOOL bGdmDegmmEn;
    HI_BOOL bGdmGmmEn        ;
    HI_BOOL bCvm2Lms2IptEn   ;
    HI_BOOL GcvmEn           ;
    HI_BOOL bGdmS2UEn        ;

    //output mapping
    HI_BOOL bOmapIptOutEn;
    HI_BOOL bOmapIpt2LmsEn;
    HI_BOOL bOmapLms2RgbEn;
    HI_BOOL bOmapRgb2YuvEn;
    HI_BOOL bOmapDenormEn;
    HI_BOOL bOmapDegmmEn;
    HI_BOOL bOmapGmmEn;
    HI_BOOL bOmapU2SEn;

    HI_BOOL bOmapSel;//0: in DHD; 1:in VP0

    //mixg bypass
    HI_BOOL bMixvBypassEn    ;
    HI_BOOL bMixvBypassMode  ;
    HI_BOOL bMixvPremultEn;
    HI_BOOL bMixvDePremultEn;
    HI_BOOL bGfxPreMultEn;

    //CVM
    HI_BOOL bVcvmEn ;
    HI_BOOL bGcvmEn ;

    HI_S32 s32Cvm2Lms2IptOutDc[3];

    VDP_HDR_OMAPPING_POSITION_E  enOmapPosition;


} XDP_HDR_CTRL_S;

typedef struct
{
    VDP_DATA_WTH u32DataWidth;//0:8bit; 1:10bit
    VDP_RECT_S stVidReso ; //vid input reso
    VDP_RECT_S stBlReso  ; //vid zme output reso
    VDP_RECT_S stElReso  ; //el input reso
    VDP_RECT_S stGfxReso ; //gfx input reso
    VDP_RECT_S stGfx1Reso ; //gfx input reso

    VDP_ADDR_S stBlAddr  ;
    VDP_ADDR_S stBlAddr_2LowBit  ;
    VDP_ADDR_S stElAddr  ;
    VDP_ADDR_S stHeadAddr; //dcmp head data addr

    HI_BOOL bDcmpEn;
    HI_BOOL bMuteEn;
    HI_BOOL bGfxEn;
    HI_BOOL bGfx1En;

    HI_BOOL bIoP;

    HI_BOOL bPreMult;
    //HI_U32 u32CoefAddr[5];

    VDP_DRAW_MODE_E enDrawMode;

    VDP_VID_IFMT_E  enVdpBlVidIFmt;
    VDP_VID_IFMT_E  enVdpElVidIFmt;

    VDP_GFX_IFMT_E enGfxIfmt;

    HI_BOOL           bSmmuEn               ;

} VDP_HDR_CFG_S;

HI_S32 VDP_DRV_SetHdrMode(XDP_LAYER_VID_INFO_S  *stXdpHdrCfgIn, VDP_FIXPT_MAIN_CFG_S *pstCompCfg, DmKsFxp_t *pstDmKs);
HI_S32 VDP_DRV_SetHdrEdaCfg       ( VDP_HDR_CFG_S *stHdrCfg);
HI_S32 VDP_DRV_SetComposer        ( VDP_FIXPT_MAIN_CFG_S *pstCompCfg);
HI_S32 VDP_DRV_SetVdm             ( DmKsFxp_t *pstDmKs);
HI_S32 VDP_DRV_SetHdrHdmiMetadata ( HI_U8 *pu8HeadData, HI_U32 u32MdLen, HI_U8 *pu8MdBuf);
HI_VOID VDP_DRV_HdrRegClean(HI_VOID);
HI_VOID VDP_DRV_GetPreZmeConfig(VDP_RECT_S  stZmeIn, VDP_RECT_S  stZmeOut, VDP_DRAW_PIXEL_MODE_E *penHScalerMode, VDP_DRAW_MODE_E *penVScalerMode, VDP_PREZME_CONFIG_S *pstPreZmeConfig);
HI_S32 VDP_DRV_SetXdpRegUp(HI_VOID);


#endif
