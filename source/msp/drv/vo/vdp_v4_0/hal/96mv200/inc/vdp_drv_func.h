#ifndef __DRV_FUNC_H__
#define __DRV_FUNC_H__

#ifndef __DISP_PLATFORM_BOOT__
#include "vdp_define.h"
#include "vdp_drv_ip_sharpen.h"

#if EDA_TEST
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "c_union_define.h"
#include "vdp_assert.h"
//for HDR composer
//#include "rpu_ext_config.h"
#include "vdp_dm_typefxp.h.h"

#endif

#include "hi_reg_common.h"

#include "vdp_define.h"
#include "vdp_ip_define.h"
#include "vdp_drv_comm.h"

#include "vdp_drv_hdr.h"
//#include "vdp_test.h"
#include "vdp_drv_ip_snr.h"


#if VDP_CBB_FPGA
//#include "vdp_assert.h"
#include "vdp_fpga_define.h"
#endif

#define         MAX_WIN_NUM_PER_LAYER       16

#define CheckError(x) { if (x) { printf("\nErr @ (%s, %d)\n", __FILE__, __LINE__); \
            exit(-__LINE__); } }

//add ACC ADDR
#define VDP_ACC_ADDR VDP_BASE_ADDR+0x6700

//HI_U32 uGetRand(HI_U32 max, HI_U32 min);
//HI_S32 sGetRand(HI_S32 max, HI_S32 min);

typedef enum tagVDP_SR_SCALE_MODE_E
{
    VDP_SR_H1P1V1P1    = 0x0,
    VDP_SR_H1P1V1P2    ,
    VDP_SR_H1P2V1P1    ,
    VDP_SR_H1P2V1P2    ,

    VDP_VDP_SR__BUTT

} VDP_SR_SCALE_MODE_E;


typedef enum tagVDP_POS_MODE_E
{
    VDP_POS_MODE_FULL         = 0x0,  //video  = disp = mix
    VDP_POS_MODE_CENTER       = 0x1,  //video! = disp = mix mid

    VDP_POS_MODE_TOP          = 0x2,  //video! = disp = mix up
    VDP_POS_MODE_BOTTOM       = 0x3,  //video! = disp = mix down
    VDP_POS_MODE_LEFT         = 0x4,  //video! = disp = mix left
    VDP_POS_MODE_RIGHT        = 0x5,  //video! = disp = mix right

    VDP_POS_MODE_TOP_LEFT     = 0x6,  //video! = disp = mix up
    VDP_POS_MODE_BOTTOM_LEFT  = 0x7,  //video! = disp = mix down
    VDP_POS_MODE_TOP_RIGHT    = 0x8,  //video! = disp = mix left
    VDP_POS_MODE_BOTTOM_RIGHT = 0x9, //video! = disp = mix right

    VDP_POS_MODE_BUTT

} VDP_POS_MODE_E;
typedef enum tagVDP_REGIONMODE_E
{
    VDP_PIP_BOTTOM       = 0,
    VDP_PIP_TOP          = 1,
    VDP_PIP_LEFT         = 2,
    VDP_PIP_RIGHT        = 3,
    VDP_PIP_TOP_LEFT     = 4,
    VDP_PIP_TOP_RIGHT    = 5,
    VDP_PIP_BOTTOM_LEFT  = 6,
    VDP_PIP_BOTTOM_RIGHT = 7,
    VDP_POP_NORM         = 8,

    VDP_REGIONMODE_BUTT

} VDP_REGIONMODE_E;

typedef struct tagVDP_REGION_CFG_S
{
    VDP_REGIONMODE_E  u32VdpRegionMode;
    VDP_RECT_S        u32LargeVideoReso;
    VDP_RECT_S        u32SmallVideoReso;
    VDP_VID_IFMT_E    u32VideoFmt;
    HI_U32            u32LargeVideoLStr;
    HI_U32            u32LargeVideoCStr;
    HI_U32            u32LargeVideoLAddr;
    HI_U32            u32LargeVideoCAddr;
    HI_U32            u32SmallVideoLAddr;
    HI_U32            u32SmallVideoCAddr;
    HI_U32            u32SmallVideoLStr;
    HI_U32            u32SmallVideoCStr;

} VDP_REGION_CFG_S;




typedef enum tagVDP_SCALE_MODE_E
{
    NO_SCALE      = 0x0,  //video  = disp = mix
    UP_SCALE      = 0x1,  //video! = disp = mix mid
    DOWN_SCALE    = 0x2, //video! = disp = mix up

    VDP_SCALE_MODE_BUTT

} VDP_SCALE_MODE_E;

typedef struct hiVDP_LAYER_RESO_S
{
    VDP_RECT_S              stVdp_rect_in;
    VDP_RECT_S              stVdp_rect_out;
    VDP_RECT_S              stVdp_rect_vid;
    VDP_RECT_S              stVdp_rect_disp;
    VDP_RECT_S              stPosMinReso;
    HI_U32                  u32AlignWH;
    HI_U32                  u32AlignXY;
    HI_U32                  u32AlignW;
    HI_U32                  u32AlignH;
    HI_U32                  u32AlignX;
    HI_U32                  u32AlignY;

} VDP_LAYER_RESO_S;
//layer pos gen out
typedef struct hiVDP_LAYER_POS_S
{
    VDP_RECT_S stInReso;
    VDP_RECT_S stPos;
    VDP_RECT_S stPosMinReso;


    HI_U32     u32AlignXY;
    HI_U32     u32AlignWH;
    HI_U32     u32AlignX;
    HI_U32     u32AlignY;

    HI_U32     u32AlignW;
    HI_U32     u32AlignH;

} VDP_LAYER_POS_S;

//layer pos gen in
typedef struct hiVDP_POS_GEN_CFG_S
{
    VDP_RECT_S stReso;
    VDP_POS_MODE_E enPosMode;
    HI_U32 u32SclMode;
    HI_U32 u32AlignXY;
    HI_U32 u32AlignWH;

} VDP_POS_GEN_CFG_S;

typedef enum tagVDP_VP_DCI_MODE_E
{
    VDP_VP_DCI_TYP      = 0x0,
    VDP_VP_DCI_RAND     = 0x1,
    VDP_VP_DCI_MAX      = 0x2,
    VDP_VP_DCI_MIN      = 0x3,

    VDP_VP_DCI_CFG_BUTT

} VDP_VP_DCI_MODE_E;

//read mode
typedef enum tagVDP_RM_READ_E
{
    VDP_ZME_READ    = 0,
    VDP_SHARPEN_READ = 1,
    VDP_DCI_READ     = 2,
    VDP_GAMMA_READ   = 3,
    VDP_ACM_READ     = 4,
    VDP_DIMMING_READ = 5,
    VDP_C6_READ     = 6,
    VDP_CVM_READ     = 7,
    VDP_VDM_READ     = 8,
    VDP_GDM_DEGAMM   = 9,
    VDP_GDM_GAMM     = 10,
    VDP_MD_READ      = 11,
    VDP_ZME2_READ    = 12,
    VDM_COEF_DEGAMMA = 13,
    VDM_COEF_TONEMAPPING = 14,
    VDM_COEF_GAMMA   = 15,
    VDM_COEF_SMAP    = 16,
    GDM_COEF_TONEMAPPING = 17,
    GDM_COEF_GAMMA   = 18

} VDP_RM_READ_E ;

typedef struct hiVDP_SCL_NONLINEAR_S
{
    HI_U32    u32StartStep;
    HI_U32    u32LZoneEndPos;
    HI_U32    u32MZoneEndPos;
    HI_S32    s32LZone_delta;
    HI_S32    s32RZone_delta;
    HI_BOOL   bEnable;
} VDP_SCL_NONLINEAR_S;

typedef enum tagVDP_DISP_DIMMING_MODE_E
{
    VDP_DISP_DIMMING_TYP0      = 0x0 ,
    VDP_DISP_DIMMING_TYP1      = 0x1 ,
    VDP_DISP_DIMMING_TYP2      = 0x2 ,
    VDP_DISP_DIMMING_TYP3      = 0x3 ,
    VDP_DISP_DIMMING_TYP4      = 0x4 ,
    VDP_DISP_DIMMING_TYP5      = 0x5 ,
    VDP_DISP_DIMMING_TYP6      = 0x6 ,
    VDP_DISP_DIMMING_TYP7      = 0x7 ,
    VDP_DISP_DIMMING_TYP8      = 0x8 ,
    VDP_DISP_DIMMING_TYP9      = 0x9 ,
    VDP_DISP_DIMMING_TYP10     = 0x10,
    VDP_DISP_DIMMING_TYP11     = 0x11,
    VDP_DISP_DIMMING_TYP12     = 0x12,
    VDP_DISP_DIMMING_TYP13     = 0x13,
    VDP_DISP_DIMMING_TYP14     = 0x14,
    VDP_DISP_DIMMING_TYP15     = 0x15,
    VDP_DISP_DIMMING_TYP16     = 0x16,
    VDP_DISP_DIMMING_TYP17     = 0x17,
    VDP_DISP_DIMMING_MAX       = 0x18,
    VDP_DISP_DIMMING_MIN       = 0x19,
    VDP_DISP_DIMMING_RAND      = 0x20,
    VDP_DISP_DIMMING_RAND1     = 0x21,
    VDP_DISP_DIMMING_2CHN      = 0x22,
    VDP_DISP_DIMMING_4k_13_TEST = 0x23,
    VDP_DISP_DIMMING_4k_31_TEST = 0x24,
    VDP_DISP_DIMMING_4k_01_TEST = 0x25,
    VDP_DISP_DIMMING_4k_02_TEST = 0x26,

    VDP_DISP_DIMMING_CFG_BUTT

} VDP_DISP_DIMMING_MODE_E;
typedef enum tagVDP_VP_SR_MODE_E
{
    VDP_VP_SR_TYP    = 0x0,
    VDP_VP_SR_RAND     ,
    VDP_VP_SR_MAX      ,
    VDP_VP_SR_MIN      ,

    VDP_VP_SR_CFG_BUTT

} VDP_VP_SR_MODE_E;
#if 0
typedef enum tagVDP_SR_COEF_MODE_E
{
    VDP_SR_COEF_TYP  = 1,
    VDP_SR_COEF_MAX = 1,
    VDP_SR_COEF_MIN = 1,
    VDP_SR_COEF_RAND = 1,

    VDP_SR_COEF_BUTT
} VDP_SR_COEF_MODE_E;
#endif
typedef enum tagVDP_V0_ES_MODE_E
{
    VDP_V0_ES_TYP_1    = 0x0,
    VDP_V0_ES_TYP_2    ,
    VDP_V0_ES_RAND     ,
    VDP_V0_ES_MAX      ,
    VDP_V0_ES_MIN      ,
    VDP_V0_ES_CFG_BUTT

} VDP_V0_ES_MODE_E;

typedef enum tagVDP_TEST_MODE_E
{
    VDP_TEST_MODE_NORM = 0,
    VDP_TEST_MODE_RAND = 1,
    VDP_TEST_MODE_COMB = 2,

    VDP_TEST_MODE_BUTT
} VDP_TEST_MODE_E;


typedef struct tagVDP_LAYER_CFG_S
{
#if VDP_CBB_FPGA
    VDP_RM_LAYER_E              enRmLayer;
#endif

    VDP_LAYER_VID_E              vid_layer;
    HI_U32                       u32LayerEn;
    VDP_DATA_RMODE_E             enReadMode;
    VDP_VID_IFMT_E              enInFmt;
    VDP_DATA_WTH                enDataWidth;

    VDP_RECT_S                  stInReso;
    VDP_RECT_S                  stOutReso;
    VDP_RECT_S                  stVidPos;
    VDP_RECT_S                  stDispPos;
    VDP_RECT_S                  stCropOut;

    HI_U32                       u32DcmpEn;
    //ADD sec_flag
    HI_BOOL                     bSecFlag ;
    HI_BOOL                     bDataSecFlag ;

    HI_BOOL                     bIop;

    VDP_RECT_S                  stRegionRect[MAX_WIN_NUM_PER_LAYER];
    VDP_DISP_MODE_E             enDispMode;
    HI_BOOL                     enMultimode;

    HI_U32                      u32PicNum;
    HI_U32                      u32gAlpha ;
    //gfx
    VDP_LAYER_GFX_E             gfx_layer;
    HI_U32                      u32GfxGalpha;
    HI_U32                      u32GfxPalpha0;
    HI_U32                      u32GfxPalpha1;
    HI_BOOL                     bGfxPalphaEn;
    HI_BOOL                     bGfxPalphaRange;
    HI_BOOL                     bGfxUpdMode;

    HI_BOOL                     u32GfxDcmpEn;
    HI_BOOL                     u32GfxDcmpAddrEn;

    HI_BOOL                     bGfxPremultEn;
    HI_BOOL                     bGpDePremultEn;


    VDP_GFX_BITEXTEND_E         stBitExtend;
    HI_BOOL                     iSRgb;

    HI_U32                      u32VidAlpha ;
    HI_BOOL                     bCscEnable ;
    VDP_CSC_MODE_E              enCscMode;
    VDP_CSC_COEF_S              st_csc_coef;
    VDP_CSC_DC_COEF_S           st_csc_dc_coef;
    HI_BOOL                     bMute ;
    VDP_BKG_S                   stVidMuteBkg;
    VDP_BKG_S                   stVidBgc;
    VDP_IFIRMODE_E              stIfirMode;
    HI_BOOL                     bPreReadEn;
    HI_BOOL                     bUvorder;
    HI_BOOL                     bKeyEn;
    VDP_GFX_CKEY_S              stKey;
    VDP_GFX_MASK_S              stMsk;
    HI_U32                      u32Gfx2ConnectDhd;
    HI_U32                      u32Gfx3ConnectDhd;

    HI_BOOL                     bGfxDcmpEn;
    HI_BOOL                     bGfxLosslessEn;
    HI_BOOL                     bGfxLosslessAlphaEn;
    HI_U32                      bCmpMode;

    // zme
    HI_S32 s32ZmeHorPhase;
    HI_S32 s32ZmeVerPhase;
    HI_U32 u32HFirEn;
    HI_U32 u32VFirEn;

    HI_U32 u32HMidEn;
    HI_U32 u32VMidEn;
    //multi region for V1 and V4
    HI_U32                      u32RegionNumX;
    HI_U32                      u32RegionNumY;
    HI_BOOL                     bMultiRegionEn;
    //crop
    HI_U32                      u32CropEn;
    VDP_RECT_S                  stCrop;
    //preread
    HI_U32            u32PreReadEn;//for vp
    HI_BOOL                     bAcmEn;
    HI_BOOL                     bAccEn;
    HI_BOOL                     bAcmDebug;
    HI_BOOL                     bAccDebug;

    HI_BOOL                     bDciEn;

    HI_BOOL                     bDofEn;
    HI_S32                      s32LeftStp;
    HI_S32                      s32RightStp;

    //wbc
    HI_U32 u32WbcYStride;
    HI_U32 u32WbcCStride;

    HI_U32 u32WbcYAddr;
    HI_U32 u32WbcCAddr;

    VDP_WBC_OFMT_E              enOutFmt;
    HI_U32                      u32OutIop;
    VDP_WBC_3D_MODE_E           enTriMode;
    VDP_DRAW_MODE_E             stDrawMode;
    HI_U32                      u32TestMode;
    HI_BOOL                     bWbcDispEn;
    HI_BOOL                     u32WbcCscEn ;
    VDP_CSC_MODE_E              u32WbcCscMd ;

    HI_U32                      u32MdOut;

    HI_BOOL                     bP2iEn;

    VDP_LAYER_CONN_E            enWbcVpConnPoint;

    //dhd
    VDP_CHN_E                   enDhd0ChnSel;

    VDP_CHN_E                   enDsd0ChnSel;//for wbc dhd for see pictures!!!
    HI_BOOL                     bDisp0En;
    HI_BOOL                     bDisp1En;
    VDP_DISP_DIGFMT_E           stDisp0Fmt;
    VDP_DISP_DIGFMT_E           stDisp1Fmt;

    //Intf
    HI_U32                      u32Intf0Width;
    HI_U32                      u32Intf1Width;
    HI_U32                      u32Intf0Height;
    HI_U32                      u32Intf1Height;
    VDP_DISP_INTF_E             stIntfFmt;

    HI_U32                      u32IntfIop;

    HI_U32                      u32IntfcscEn;
    VDP_CSC_MODE_E              enIntfCscMode;
    HI_U32                      u32IntfHpEn;
    VDP_BKG_S                   stDhdBkg;

    VDP_DISP_CLIP_S             stClipData;
    HI_U32                      u32DitherEn;
    VDP_DITHER_E                enDitherMode;
    VDP_DITHER_COEF_S           dither_coefs;

    HI_BOOL                     bSharpenEn;
    HI_BOOL                     bSharpenDebugEn;
    VDP_VID_SHARPEN_MODE_E      enSharpMode;
    HI_U32                      u32SharpenPos;
    HI_U32                      u32SharpenDebugMode;

    //dcmp
    HI_U32                  enThreeDMode;
    HI_U32                  u32HorZmeEn;
    HI_U32                  u32DrawMode;
    HI_U32                  u32DrawModeRation;
    HI_U32                  u32UnpdrawEn;

    VDP_SR_SCALE_MODE_E    enSrScaleMode;

    HI_U32                  bDcmpEn;
    HI_U32                  u32PixelLoss;
    HI_U32                  u32AlphaLoss;

    HI_U32                  u32LumLosslessEn;
    HI_U32                  u32ChmLosslessEn;
    HI_BOOL                 bCmpEn;
    HI_U32                  u32HeadSize;

    HI_BOOL                 bIsLossEn;
    //vid
    HI_U32                 u32DataWidth;

    VDP_LAYER_CONN_E       u32LayerConn;
    //sr
    VDP_SR_PARA_INFO       SrParaInfo;
    VDP_VP_SR_MODE_E       enSrMode;
    VDP_SR_SCALE_MODE_E    enSrScaleMd;
    VDP_SR_IORESO          stIOReso;
    HI_U32                 SrMode;
    VDP_SR_IORESO          stSrIOReso;

    HI_BOOL               bP2iEnable;

    HI_U32            enTestMode;
    HI_U32            u32CbmIop;
    HI_U32            u32Flip;
    HI_U32            u32YAddr;
    HI_U32            u32CAddr;
    HI_U32            u32YheadAddr;
    HI_U32            u32CheadAddr;
    HI_U32            u32TileHeadSize;
    HI_U32            u32HeadStride;

    HI_U32            u32YStride;
    HI_U32            u32CStride;

    HI_U32            u32NYAddr;
    HI_U32            u32NCAddr;

    HI_U32            u32NYStride;
    HI_U32            u32NCStride;

    //GFX DCMP
    HI_U32            u32DcmpARAddr ;
    HI_U32            u32DcmpGBAddr ;
    HI_U32            u32DcmpARGBStride ;
    HI_U32            u32DcmpARHeadAddr ;
    HI_U32            u32DcmpGBHeadAddr ;
    HI_U32            u32DcmpHeadStride ;

    //vid for  region config
    HI_U32            region_en;
    HI_U32            rim_wth;
    HI_U32            num;

    HI_U32            rim_en;
    HI_U32            rim_col;

    HI_U32            mute_en;
    HI_U32            u32_laddr;
    HI_U32            u32_caddr;
    HI_U32            VidYStride;
    HI_U32            VidCStride;
    VDP_RECT_S        region_rect;
    //VDP_RIM_COL0_S          stRimCol0;
    //VDP_RIM_COL1_S          stRimCol1;

    //prio
    VDP_CBM_LAYER_E enDhd1Mixer[3];
    VDP_CBM_LAYER_E enDhd0Mixer[2];
    VDP_CBM_LAYER_E enMixgMixer[3];
    VDP_CBM_LAYER_E enMixvMixer[2];

    HI_U32   u32Dhd1MixerPrio[3];
    HI_U32   u32Dhd0MixerPrio[2];
    HI_U32   u32MixgMixerPrio[3];
    HI_U32   u32MixvMixerPrio[2];


    HI_U32   u32MixerPrio;
    HI_U32   u32CbmVid;
    HI_U32   u32CbmGfx;
    //axi
    HI_U32  u32ReqCtrl;
    HI_U32  u32IdSel;
    VDP_MASTER_E  enAxiMstSel;
    HI_U32  u32AxiId;
    HI_U32  u32AxiRdOutStd;
    HI_U32  u32AxiWrOutStd;

#if 1 //add for scene test
    //v0
    HI_U32            u32v0_tile_dcmp_yaddr ;
    HI_U32            u32v0_tile_dcmp_caddr ;
    HI_U32            u32v0_tile_dcmp_ystride ;
    HI_U32            u32v0_tile_dcmp_cstride ;

    HI_U32            u32v0_tile_dcmp_head_yaddr ;
    HI_U32            u32v0_tile_dcmp_head_caddr ;
    HI_U32            u32v0_tile_dcmp_head_ystride ;
    HI_U32            u32v0_tile_dcmp_head_cstride ;
    HI_U32            u32v0_tile_dcmp_head_size ;

    HI_U32            u32v0_tile_dcmp_tile_low2b_ystride ;
    HI_U32            u32v0_tile_dcmp_tile_low2b_cstride ;


    HI_U32            u32v0_tile_yaddr ;
    HI_U32            u32v0_tile_caddr ;
    HI_U32            u32v0_tile_ystride ;
    HI_U32            u32v0_tile_cstride ;

    HI_U32            u32v0_420_yaddr ;
    HI_U32            u32v0_420_caddr ;
    HI_U32            u32v0_420_ystride ;
    HI_U32            u32v0_420_cstride ;

    HI_U32            u32v0_420_yaddr_r ;
    HI_U32            u32v0_420_caddr_r ;
    HI_U32            u32v0_420_ystride_r ;
    HI_U32            u32v0_420_cstride_r ;

    HI_U32            u32v0_422_yaddr ;
    HI_U32            u32v0_422_caddr ;
    HI_U32            u32v0_422_ystride ;
    HI_U32            u32v0_422_cstride ;

    HI_U32            u32v0_422_yaddr_r ;
    HI_U32            u32v0_422_caddr_r ;
    HI_U32            u32v0_422_ystride_r ;
    HI_U32            u32v0_422_cstride_r ;

    //v1
    HI_U32            u32v1_420_yaddr ;
    HI_U32            u32v1_420_caddr ;
    HI_U32            u32v1_420_ystride ;
    HI_U32            u32v1_420_cstride ;

    HI_U32            u32v1_422_yaddr ;
    HI_U32            u32v1_422_caddr ;
    HI_U32            u32v1_422_ystride ;
    HI_U32            u32v1_422_cstride ;

    HI_U32            u32v1_422_yaddr_r ;
    HI_U32            u32v1_422_caddr_r ;
    HI_U32            u32v1_422_ystride_r ;
    HI_U32            u32v1_422_cstride_r ;


    //v3
    HI_U32            u32v3_422_yaddr ;
    HI_U32            u32v3_422_caddr ;
    HI_U32            u32v3_422_ystride ;
    HI_U32            u32v3_422_cstride ;

    HI_U32            u32v3_422_yaddr_r ;
    HI_U32            u32v3_422_caddr_r ;
    HI_U32            u32v3_422_ystride_r ;
    HI_U32            u32v3_422_cstride_r ;


    //g0
    HI_U32            u32g0_argb8888_dcmp_ar_addr ;
    HI_U32            u32g0_argb8888_dcmp_ar_stride ;
    HI_U32            u32g0_argb8888_dcmp_gb_addr ;
    HI_U32            u32g0_argb8888_dcmp_gb_stride ;

    HI_U32            u32g0_argb8888_dcmp_head_ar_addr ;
    HI_U32            u32g0_argb8888_dcmp_head_gb_addr ;

    HI_U32            u32g0_argb8888_dcmp_addren_ar_addr ;
    HI_U32            u32g0_argb8888_dcmp_addren_ar_stride ;
    HI_U32            u32g0_argb8888_dcmp_addren_gb_addr ;
    HI_U32            u32g0_argb8888_dcmp_addren_gb_stride ;

    HI_U32            u32g0_argb8888_dcmp_addren_head_ar_addr ;
    HI_U32            u32g0_argb8888_dcmp_addren_head_gb_addr ;

    HI_U32            u32g0_argb8888_dcmp_addr_en ;

    HI_U32            u32g0_argb8888_addr ;
    HI_U32            u32g0_argb8888_stride ;

    HI_U32            u32g0_argb8888_addr_r ;
    HI_U32            u32g0_argb8888_stride_r ;

    //g1
    HI_U32            u32g1_argb8888_addr ;
    HI_U32            u32g1_argb8888_stride ;

    HI_U32            u32g1_argb8888_addr_r ;
    HI_U32            u32g1_argb8888_stride_r ;
    //g4
    HI_U32            u32g4_argb8888_addr ;
    HI_U32            u32g4_argb8888_stride ;

    HI_U32            u32g4_argb8888_addr_r ;
    HI_U32            u32g4_argb8888_stride_r ;
#endif




} VDP_LAYER_CFG_S;






typedef enum tagVDP_MULTI_MODE_E
{
    VDP_MULTI_GAP_EQ_WTH     = 0,
    VDP_MULTI_GAP_NOEQ_WTH   = 1,
    VDP_MULTI_NOGAP_EQ_WTH   = 2,
    VDP_MULTI_NOGAP_NOEQ_WTH = 3,
    VDP_MULTI_RAND           = 4,
    VDP_MULTI_MODE_RAND      = 5,

    VDP_MULTI_BUTT

} VDP_MULTI_MODE_E;

typedef struct
{
    HI_U32 u32IntfIop;
    HI_U32 u32HorNum;
    HI_U32 u32VerNum;

    HI_U32 u32Wth;//u32LayerWth; //layer reso
    HI_U32 u32Hgt;//u32LayerHgt;
    VDP_MULTI_MODE_E enMultiMode;

    HI_U32 u32_laddr   ;
    HI_U32 u32_caddr   ;
    HI_U32 u32YStride  ;
    HI_U32 u32CStride  ;
    HI_U32 enInFmt;

} VDP_MULTI_CFG_S;

typedef enum tagVDP_V0_USING_MODE_E
{
    VDP_V0_USING_CONST_0    = 0x0,
    VDP_V0_USING_CONST_1         ,
    VDP_V0_USING_RAND_BY_TYPE    ,//pick one cfg in 16 cfg type, only three cfg type make using = 1
    VDP_V0_USING_RAND_BY_USING   ,//50% using =0 50% using =1
    VDP_V0_USING_SET_TYPE        ,
    VDP_V0_USING_SET_USING       ,
    VDP_V0_USING_WRONG_USING

} VDP_V0_USING_MODE_E;

typedef enum tagVDP_V0_TNR_MODE_E
{
    VDP_V0_TNR_TYP_1    = 0x0,
    VDP_V0_TNR_ZERO     ,
    VDP_V0_TNR_RAND     ,
    VDP_V0_TNR_MAX      ,
    VDP_V0_TNR_MIN      ,
    VDP_V0_TNR_CFG_BUTT

} VDP_V0_TNR_MODE_E;

typedef enum tagVDP_V0_DBM_MODE_E
{
    VDP_V0_DBM_TYP_1    = 0x0,
    VDP_V0_DBM_STREAM   ,
    VDP_V0_DBM_RAND     ,
    VDP_V0_DBM_MAX      ,
    VDP_V0_DBM_MIN      ,
    VDP_V0_DBM_CFG_BUTT

} VDP_V0_DBM_MODE_E;


typedef enum tagVDP_V0_DB_DETECT_MODE_E
{
    VDP_V0_DB_DETECT_TYP_1    = 0x0,
    VDP_V0_DB_DETECT_STREAM   ,
    VDP_V0_DB_DETECT_RAND     ,
    VDP_V0_DB_DETECT_MAX      ,
    VDP_V0_DB_DETECT_MIN      ,
    VDP_V0_DB_DETECT_CFG_BUTT

} VDP_V0_DB_DETECT_MODE_E;

typedef enum
{
    VDP_HDR_COMPOSER_CFG_TYP = 0,
    VDP_HDR_COMPOSER_CFG_RAND ,
    VDP_HDR_COMPOSER_CFG_RAND_COEF ,
    VDP_HDR_COMPOSER_CFG_MAX  ,
    VDP_HDR_COMPOSER_CFG_MIN  ,
    VDP_HDR_COMPOSER_CFG_BUTT
} VDP_HDR_COMPOSER_CFG_E;

typedef enum
{
    VDP_BT2020_CFG_TYP = 0,
    VDP_BT2020_CFG_RAND ,
    VDP_BT2020_CFG_MAX  ,
    VDP_BT2020_CFG_MIN  ,
    VDP_BT2020_CFG_BUTT
} VDP_BT2020_CFG_E;
typedef enum
{
    VDP_HDR_DM_CFG_TYP = 0,
    VDP_HDR_DM_CFG_RAND ,
    VDP_HDR_DM_CFG_RAND_COEF ,
    VDP_HDR_DM_CFG_RAND_YUV2RGB ,
    VDP_HDR_DM_CFG_RAND_RGB2LMS ,
    VDP_HDR_DM_CFG_RAND_LMS2IPT ,
    VDP_HDR_DM_CFG_RAND_IPT2LMS ,
    VDP_HDR_DM_CFG_RAND_LMS2RGB ,
    VDP_HDR_DM_CFG_RAND_RGB2YUV ,
    VDP_HDR_DM_CFG_MAX  ,
    VDP_HDR_DM_CFG_MIN  ,
    VDP_HDR_DM_CFG_ZERO ,
    VDP_HDR_DM_CFG_12BIT_YUV2RGB,
    VDP_HDR_DM_CFG_14BIT_YUV2RGB,
    VDP_HDR_DM_CFG_BUTT
} VDP_HDR_DM_CFG_E;


typedef enum
{
    VDP_HDR_CLR_SPACE_601 = 0,
    VDP_HDR_CLR_SPACE_709 ,
    VDP_HDR_CLR_SPACE_2020 ,
    VDP_HDR_CLR_SPACE_BUTT

} VDP_HDR_CLR_SPACE_E;

typedef enum
{
    VDP_HD_DIV1_SD_DIV1 = 0,
    VDP_HD_DIV1_SD_DIV2 ,
    VDP_HD_DIV1_SD_DIV4 ,
    VDP_HD_DIV2_SD_DIV2 ,
    VDP_HD_DIV2_SD_DIV4 ,
    VDP_HD_DIV4_SD_DIV4 ,
    VDP_CLK_CLR_SPACE_BUTT
} VDP_CLK_CFG_E;

#if VID_BT2020_EN
typedef enum
{
    VDP_BT2020_TYP = 0,
    VDP_BT2020_RAND ,
    VDP_BT2020_MAX  ,
    VDP_BT2020_MIN  ,
    VDP_BT2020_BUTT
} VDP_BT2020_MODE_E;
typedef enum
{
    VDP_HDR_DM_TYP = 0,
    VDP_HDR_DM_RAND ,
    VDP_HDR_DM_RAND_COEF ,
    VDP_HDR_DM_RAND_YUV2RGB ,
    VDP_HDR_DM_RAND_RGB2LMS ,
    VDP_HDR_DM_RAND_LMS2IPT ,
    VDP_HDR_DM_RAND_IPT2LMS ,
    VDP_HDR_DM_RAND_LMS2RGB ,
    VDP_HDR_DM_RAND_RGB2YUV ,
    VDP_HDR_DM_MAX  ,
    VDP_HDR_DM_MIN  ,
    VDP_HDR_DM_ZERO ,
    VDP_HDR_DM_12BIT_YUV2RGB,
    VDP_HDR_DM_14BIT_YUV2RGB,
    VDP_HDR_DM_BUTT
} VDP_HDR_DM_MODE_E;
#endif

HI_U32 uGetRandEx(HI_U32 max, HI_U32 min);
HI_S32 sGetRandEx(HI_S32 max, HI_S32 min);


HI_VOID VDP_FUNC_SetSrMode(VDP_SR_PARA_INFO SrParaInfo, VDP_VP_SR_MODE_E SrMode, VDP_SR_IORESO IOReso);

HI_VOID VDP_FUNC_SetEsMode(VDP_ES_PARA_INFO EsParaInfo, VDP_V0_ES_MODE_E EsMode);

//HI_VOID VDP_FUNC_SetAcmMode(VDP_TEST_MODE_E enAcmMode);

HI_S32 VDP_VID_GetNonLnrSclInfo(HI_U32 u32ZoneMWidthIn,
                                HI_U32 u32ZoneMWidthOut,
                                HI_U32 u32DeltaConfig,
                                HI_U32 u32WidthIn,
                                HI_U32 u32WidthOut,
                                VDP_SCL_NONLINEAR_S *pstLumaNLnr,
                                VDP_SCL_NONLINEAR_S *pstChomNLnr);

HI_VOID VDP_FUNC_SetVdpUsing(VDP_V0_USING_MODE_E UsingMode, double clk_ppc_t, HI_U32 using_cfg);
HI_VOID VDP_FUNC_SetTnrMode(VDP_TNR_PARA_INFO TnrParaInfo, VDP_V0_TNR_MODE_E TnrMode);

typedef enum tagVDP_WCG_MODE_E
{
    VDP_WCG_MODE_TYP      = 0x0,
    VDP_WCG_MODE_RAND     = 0x1,
    VDP_WCG_MODE_MAX      = 0x2,
    VDP_WCG_MODE_MIN      = 0x3,

    VDP_WCG_MODE_BUTT

} VDP_WCG_MODE_E;

HI_VOID VDP_FUNC_SetWcgGmaLinThr   (VDP_WCG_COEF_S *stWcgCoef, VDP_WCG_MODE_E WcgMode);
HI_VOID VDP_FUNC_SetWcgGmaLincoef  (VDP_WCG_COEF_S *stWcgCoef, VDP_WCG_MODE_E WcgMode);
HI_VOID VDP_FUNC_SetWcgLinGmaThr   (VDP_WCG_COEF_S *stWcgCoef, VDP_WCG_MODE_E WcgMode);
HI_VOID VDP_FUNC_SetWcgLinGmaCoef  (VDP_WCG_COEF_S *stWcgCoef, VDP_WCG_MODE_E WcgMode);
HI_VOID VDP_FUNC_SetWcgCscCoef     (VDP_WCG_COEF_S *stWcgCoef, VDP_WCG_MODE_E WcgMode);
HI_VOID VDP_FUNC_SetDimmingMode(VDP_CHN_E  enLayer, VDP_DISP_DIMMING_MODE_E  DimmingMode, HI_U32 w, HI_U32 h);

HI_VOID VDP_FUNC_SetMultiMode      (VDP_LAYER_VID_E enLayer, VDP_MULTI_CFG_S stMultiCfg);
HI_VOID VDP_FUNC_LayerPosGen       (VDP_POS_GEN_CFG_S stPosGenCfg, VDP_LAYER_POS_S *stLayerPos);
HI_VOID VDP_SetRegionCfg           (VDP_REGION_CFG_S  stRegionCfg);

HI_VOID VDP_FUNC_SetVidCfg(HI_U32 u32LayerId, VDP_LAYER_CFG_S *pstCfg);
HI_VOID VDP_FUNC_SetVidComb( VDP_LAYER_CFG_S *st_vid_cfg, VDP_LAYER_CFG_S *st_vp0_cfg);
//HI_VOID VDP_FUNC_SetVpRandCfg( VDP_LAYER_CFG_S  *stVidInfo,VDP_LAYER_CFG_S *st_vp0_cfg);
HI_VOID VDP_FUNC_SetVpComb(HI_U32 u32LayerId, VDP_LAYER_CFG_S *pstCfg);

//HI_VOID VDP_FUNC_SetGpRandCfg( VDP_LAYER_CFG_S *st_gfx_cfg,VDP_LAYER_CFG_S *st_gp0_cfg);
//HI_VOID VDP_FUNC_SetGfxCombCfg( VDP_LAYER_CFG_S *st_g0_cfg,VDP_LAYER_CFG_S *st_gp0_cfg);

HI_VOID VDP_SetWbcVp_VpAcsc_ppi(VDP_DISP_MODE_E setdisp_mode, VDP_RECT_S dhd0_rect);
HI_VOID VDP_SetWbcVp_Vidbzme_ppp(VDP_DISP_MODE_E setdisp_mode, VDP_RECT_S dhd0_rect);
HI_VOID VDP_SetWbcVp_Vidbzme_ppi(VDP_DISP_MODE_E setdisp_mode, VDP_RECT_S dhd0_rect);
HI_VOID VDP_SetWbcVp_VpAcsc_ppp(VDP_DISP_MODE_E setdisp_mode, VDP_RECT_S dhd0_rect);
HI_VOID VDP_SetWbcVp_Vidbzme_pii(VDP_DISP_MODE_E setdisp_mode, VDP_RECT_S dhd0_rect);
HI_VOID VDP_SetWbcVp_Vidbzme_pip(VDP_DISP_MODE_E setdisp_mode, VDP_RECT_S dhd0_rect);
HI_VOID VDP_SetWbcVp_VpAcsc_iii(VDP_DISP_MODE_E setdisp_mode, VDP_RECT_S dhd0_rect);
HI_VOID VDP_SetWbcVp_Vidbzme_iii(VDP_DISP_MODE_E setdisp_mode, VDP_RECT_S dhd0_rect);
HI_VOID VDP_FUNC_SetMultiMode_zjy(VDP_LAYER_VID_E enLayer, VDP_MULTI_CFG_S stMultiCfg);

typedef enum tagVDP_HDR_GDM_MODE_E
{
    VDP_HDR_GDM_TYP = 0,
    VDP_HDR_GDM_RAND ,
    VDP_HDR_GDM_RAND_COEF ,
    VDP_HDR_GDM_ZERO ,
    VDP_HDR_GDM_RAND_YUV2RGB ,
    VDP_HDR_GDM_RAND_RGB2LMS ,
    VDP_HDR_GDM_RAND_LMS2IPT ,
    VDP_HDR_GDM_RAND_IPT2LMS ,
    VDP_HDR_GDM_RAND_LMS2RGB ,
    VDP_HDR_GDM_RAND_RGB2YUV ,
    VDP_HDR_GDM_MAX  ,
    VDP_HDR_GDM_MIN  ,
    VDP_HDR_GDM_BUTT
} VDP_HDR_GDM_MODE_E;


HI_U32 VDP_FUNC_HdrHdmiMdParse(HI_U8 *buf, HI_U32 size, const char *FileName);
HI_U32 VDP_FUNC_HdrHdmiHeadParse(HI_U32 u32FrmCnt, const char *FileName);

HI_U32 VDP_FUNC_GetHdrHdmiMdLen(HI_U32 u32FrmCnt, const char *FileName);

HI_VOID VDP_SetRegUp (void);
//HI_U32 VDP_ProcessInt (stVdpTestCfg  *stVdpInfo);
HI_U32 VDP_FUNC_SetHdrModeFpga(VDP_HDR_CFG_S *stHdrCfg, HI_U32 u32FrmNum, const char *pFilePath, VDP_FIXPT_MAIN_CFG_S *comp_cfg, DmKsFxp_t *pKs);

#endif

#endif//end of __DRV_FUNC_H__
