#ifndef __VDP_IP_DRV_VDM_H__
#define __VDP_IP_DRV_VDM_H__

#include "vdp_hal_comm.h"
#include "vdp_hal_ip_vdm.h"
//#include <stdio.h>

typedef enum
{
    VDP_VID_VDM_TYP = 0,
    VDP_VID_VDM_TYP1 ,
    VDP_VID_VDM_RAND ,
    VDP_VID_VDM_MAX ,
    VDP_VID_VDM_MIN ,
    VDP_VID_VDM_ZERO ,
    VDP_VID_VDM_BUTT
} VDP_VID_VDM_MODE_E;

typedef enum
{
    VDM_HDR10_IN_SDR_OUT = 0,
    VDM_HDR10_IN_SDR_PIP_OUT ,
    VDM_BBC_IN_SDR_OUT   ,
    VDM_BBC_IN_SDR_PIP_OUT   ,
    VDM_AVS_IN_SDR_OUT   ,
    VDM_AVS_IN_SDR_PIP_OUT   ,
    VDM_HDR10_IN_BBC_OUT ,
    VDM_HDR10_IN_BBC_PIP_OUT ,
    VDM_BBC_IN_HDR10_OUT ,
    VDM_BBC_IN_HDR10_PIP_OUT ,
    VDM_AVS_IN_HDR10_OUT ,
    VDM_AVS_IN_HDR10_PIP_OUT ,

    VDM_BT2020_IN_709_OUT,
    VDM_BT2020_IN_709_PIP_OUT,

    VDM_XVYCC            ,//new scene
    VDM_XVYCC_PIP            ,//new scene
    VDM_SDR_BT2020CL_IN_BT709_OUT,//new scene
    VDM_SDR_BT2020CL_IN_BT709_PIP_OUT,  // ADD BY ZJY FOR PIP CL
    VDM_SDR_IN_HDR10_OUT,//ADD FOR PIP
    VDM_SDR_IN_HDR10_IN_HDR10_PIP_OUT,

    VDM_BYPASS_MODE      ,
    VDM_BUTT
} VDM_SCENE_MODE_E;

typedef struct
{
    HI_U32 vdm_yuv2rgb_en    ;
    HI_U32 vdm_en            ;
    HI_U32 vdm_degmm_en      ;
    HI_U32 vdm_csc_en        ;
    HI_U32 vdm_tmap_en       ;
    HI_U32 vdm_gmm_en        ;
    HI_U32 vdm_dither_en     ;
    HI_U32 vdm_rgb2yuv_en    ;
    //     HI_U32 vdm_y2r_cl_en     ;
    HI_U32 vdm_cadj_en       ;

    // Y2R PIP Ctrl
    HI_U32 vdm_v0_csc_en     ;
    HI_U32 vdm_v1_csc_en     ;
    HI_U32 vdm_v0_gamma_en   ;
    HI_U32 vdm_v1_gamma_en   ;
    HI_U32 vdm_v0_cl_en     ;
    HI_U32 vdm_v1_cl_en     ;

    HI_U32 vdm_csc_bind      ;
    HI_U32 vdm_ck_gt_en      ;

    // Dither Ctrl
    HI_U32 u32_dither_round         ;
    HI_U32 u32_dither_domain_mode   ;
    HI_U32 u32_dither_tap_mode      ;
    HI_U32 u32_dither_round_unlim   ;

    //HDR Scene
    VDM_SCENE_MODE_E VdmSceneMode;
} VDP_VDM_CFG_S;

typedef struct
{

    HI_U32 gmm_x1_step;
    HI_U32 gmm_x2_step;
    HI_U32 gmm_x3_step;
    HI_U32 gmm_x4_step;
    HI_U32 gmm_x5_step;
    HI_U32 gmm_x6_step;
    HI_U32 gmm_x7_step;
    HI_U32 gmm_x8_step;

    HI_U32 gmm_x1_pos;
    HI_U32 gmm_x2_pos;
    HI_U32 gmm_x3_pos;
    HI_U32 gmm_x4_pos;
    HI_U32 gmm_x5_pos;
    HI_U32 gmm_x6_pos;
    HI_U32 gmm_x7_pos;
    HI_U32 gmm_x8_pos;

    HI_U32 gmm_x1_num;
    HI_U32 gmm_x2_num;
    HI_U32 gmm_x3_num;
    HI_U32 gmm_x4_num;
    HI_U32 gmm_x5_num;
    HI_U32 gmm_x6_num;
    HI_U32 gmm_x7_num;
    HI_U32 gmm_x8_num;


    HI_U32 *gmm_lut;        //???

} HIHDR_TF_PARA_S;

typedef struct _DITHER_REG_S
{

    HI_U32 u32_dither_round      ;
    HI_U32 u32_dither_domain_mode;
    HI_U32 u32_dither_tap_mode   ;
    HI_U32 u32_dither_round_unlim;
    HI_U32 u32_dither_thr_max    ;
    HI_U32 u32_dither_thr_min    ;
    HI_U32 u32_dither_sed_y0     ;
    HI_U32 u32_dither_sed_u0     ;
    HI_U32 u32_dither_sed_v0     ;
    HI_U32 u32_dither_sed_w0     ;
    HI_U32 u32_dither_sed_y1     ;
    HI_U32 u32_dither_sed_u1     ;
    HI_U32 u32_dither_sed_v1     ;
    HI_U32 u32_dither_sed_w1     ;

} DITHER_REG_S;


typedef struct DmCfg_t_
{

    //     HDR_Param_S   HDR_Param        ;

    HIHDR_TF_PARA_S DePQPara         ;
    HIHDR_TF_PARA_S TMPara           ;
    HIHDR_TF_PARA_S SMPara           ;
    HIHDR_TF_PARA_S GammaPara        ;

    // YUV2RGB
    HI_S16 s16M33YUV2RGB0[3][3]    ;
    HI_S16 s16M33YUV2RGB1[3][3]    ;
    HI_U16 u16ScaleYUV2RGB_v0      ;
    HI_U16 u16ScaleYUV2RGB_v1      ;
    HI_S32 s32InOffsetYUV2RGB0[3]  ;
    HI_S32 s32InOffsetYUV2RGB1[3]  ;
    HI_S32 s32OutOffsetYUV2RGB0[3] ;
    HI_S32 s32OutOffsetYUV2RGB1[3] ;
    HI_U16 u16ClipMinYUV2RGB_v0    ;
    HI_U16 u16ClipMaxYUV2RGB_v0    ;
    HI_U16 u16ClipMinYUV2RGB_v1    ;
    HI_U16 u16ClipMaxYUV2RGB_v1    ;

    // CSC
    HI_S32 s32DcInSrc2Disp[3]      ; // S21.0
    HI_S32 s32DcOutSrc2Disp[3]     ; // S21.0
    HI_S16 s16M33Src2Disp[3][3]    ;
    HI_U16 u16ScaleSrc2Disp        ;
    HI_U32 u32ClipMinCSC           ;
    HI_U32 u32ClipMaxCSC           ;

    // Tonemapping
    HI_U16 u16M3LumaCal[3]         ;
    HI_U16 u16ScaleLumaCal         ;
    HI_U16 u16ScaleCoefTM          ;
    HI_U32 u32ClipMinTM            ;
    HI_U32 u32ClipMaxTM            ;
    HI_S32 s32TMOff0               ;
    HI_S32 s32TMOff1               ;
    HI_S32 s32TMOff2               ;

    // Round or Dither
    HI_U16 u16ClipMinGmm           ;
    HI_U16 u16ClipMaxGmm           ;

    // RGB2YUV
    HI_U16 u16ScaleRGB2YUV         ;
    HI_S16 s16M33RGB2YUV[3][3]     ;
    HI_S16 s16InOffsetRGB2YUV[3]   ;
    HI_S16 s16OutOffsetRGB2YUV[3]  ;
    HI_U16 u16ClipMinRGB2YUV_Y     ;
    HI_U16 u16ClipMinRGB2YUV_C     ;
    HI_U16 u16ClipMaxRGB2YUV_Y     ;
    HI_U16 u16ClipMaxRGB2YUV_C     ;

    // Chroma Adj
    HI_U16 u16ScaleCoefSM          ;

    // Module enable
    HI_U32 vdm_yuv2rgb_en          ;
    HI_U32 vdm_en                  ;
    HI_U32 vdm_degmm_en            ;
    HI_U32 vdm_csc_en              ;
    HI_U32 vdm_tmap_en             ;
    HI_U32 vdm_gmm_en              ;
    HI_U32 vdm_dither_en           ;
    HI_U32 vdm_rgb2yuv_pip_en      ;
    HI_U32 vdm_rgb2yuv_en          ;
    HI_U32 vdm_cadj_en             ;

    // Y2R PIP Ctrl
    HI_U32 vdm_v0_csc_en           ;
    HI_U32 vdm_v1_csc_en           ;
    HI_U32 vdm_v0_gamma_en         ;
    HI_U32 vdm_v1_gamma_en         ;
    HI_U32 vdm_v0_cl_en            ;
    HI_U32 vdm_v1_cl_en            ;

    HI_U32 vdm_csc_bind            ;
    HI_U32 vdm_ck_gt_en            ;

    HI_U32 vdm_dither_mode         ; // 0:12bit->10bit

    HI_U32 vdm_tmap_in_bdp         ;

    DITHER_REG_S stDitherCfg      ;

    //HDR Scene
    VDM_SCENE_MODE_E VdmSceneMode;
} DmCfg_t;


typedef struct Y2RCfg_t_
{
    // Y2R PIP Ctrl
    HI_S16 s16M33YUV2RGB0[3][3]    ;
    HI_S16 s16M33YUV2RGB1[3][3]    ;
    HI_U16 u16ScaleYUV2RGB_V0         ;
    HI_U16 u16ScaleYUV2RGB_V1         ;
    HI_S32 s32InOffsetYUV2RGB0[3]  ;
    HI_S32 s32InOffsetYUV2RGB1[3]  ;
    HI_S32 s32OutOffsetYUV2RGB0[3] ;
    HI_S32 s32OutOffsetYUV2RGB1[3] ;
    HI_U16 u16ClipMinYUV2RGB_V0       ;
    HI_U16 u16ClipMaxYUV2RGB_V0       ;
    HI_U16 u16ClipMinYUV2RGB_V1       ;
    HI_U16 u16ClipMaxYUV2RGB_V1       ;
} Y2RCfg_t;

typedef struct R2YCfg_t_
{
    HI_U16 u16ScaleRGB2YUV         ;
    HI_S16 s16M33RGB2YUV[3][3]     ;
    HI_S16 s16InOffsetRGB2YUV[3]   ;
    HI_S16 s16OutOffsetRGB2YUV[3]  ;
    HI_U16 u16ClipMinRGB2YUV       ;
    HI_U16 u16ClipMaxRGB2YUV       ;
} R2YCfg_t;

typedef enum
{
    YUV2RGB_601   = 0,
    YUV2RGB_709   ,
    YUV2RGB_2020  ,
    YUV2RGB_CFG   ,
    YUV2RGB_BUTT
} YUV2RGB_MODE_E ;

typedef enum
{
    RGB2YUV_601   = 0,
    RGB2YUV_709   ,
    RGB2YUV_2020  ,
    RGB2YUV_CFG   ,
    RGB2YUV_BUTT
} RGB2YUV_MODE_E ;

//function declare




#endif



