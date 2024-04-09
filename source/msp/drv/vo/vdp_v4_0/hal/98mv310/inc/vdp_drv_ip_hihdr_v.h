#ifndef __VDP_IP_DRV_HIHDR_V_H__
#define __VDP_IP_DRV_HIHDR_V_H__

#include "vdp_drv_comm.h"
#include "vdp_hal_ip_hihdr_v.h"

typedef struct
{
	HI_U32 v_degmm_x1_step                  ;
	HI_U32 v_degmm_x2_step                  ;
	HI_U32 v_degmm_x3_step                  ;
	HI_U32 v_degmm_x4_step                  ;
	HI_U32 v_degmm_x5_step                  ;
	HI_U32 v_degmm_x6_step                  ;
	HI_U32 v_degmm_x7_step                  ;
	HI_U32 v_degmm_x8_step                  ;
	HI_U32 v_degmm_x1_pos                   ;
	HI_U32 v_degmm_x2_pos                   ;
	HI_U32 v_degmm_x3_pos                   ;
	HI_U32 v_degmm_x4_pos                   ;
	HI_U32 v_degmm_x5_pos                   ;
	HI_U32 v_degmm_x6_pos                   ;
	HI_U32 v_degmm_x7_pos                   ;
	HI_U32 v_degmm_x8_pos                   ;
	HI_U32 v_degmm_x1_num                   ;
	HI_U32 v_degmm_x2_num                   ;
	HI_U32 v_degmm_x3_num                   ;
	HI_U32 v_degmm_x4_num                   ;
	HI_U32 v_degmm_x5_num                   ;
	HI_U32 v_degmm_x6_num                   ;
	HI_U32 v_degmm_x7_num                   ;
	HI_U32 v_degmm_x8_num                   ;
	HI_S32 vhdr_gamut_coef00                ;
	HI_S32 vhdr_gamut_coef01                ;
	HI_S32 vhdr_gamut_coef02                ;
	HI_S32 vhdr_gamut_coef10                ;
	HI_S32 vhdr_gamut_coef11                ;
	HI_S32 vhdr_gamut_coef12                ;
	HI_S32 vhdr_gamut_coef20                ;
	HI_S32 vhdr_gamut_coef21                ;
	HI_S32 vhdr_gamut_coef22                ;
	HI_U32 vhdr_gamut_scale                 ;
	HI_S32 vhdr_gamut_idc0                  ;
	HI_S32 vhdr_gamut_idc1                  ;
	HI_S32 vhdr_gamut_idc2                  ;
	HI_S32 vhdr_gamut_odc0                  ;
	HI_S32 vhdr_gamut_odc1                  ;
	HI_S32 vhdr_gamut_odc2                  ;
	HI_U32 vhdr_gamut_clip_min              ;
	HI_U32 vhdr_gamut_clip_max              ;
	HI_U32 v_tmap_x1_step                   ;
	HI_U32 v_tmap_x2_step                   ;
	HI_U32 v_tmap_x3_step                   ;
	HI_U32 v_tmap_x4_step                   ;
	HI_U32 v_tmap_x5_step                   ;
	HI_U32 v_tmap_x6_step                   ;
	HI_U32 v_tmap_x7_step                   ;
	HI_U32 v_tmap_x8_step                   ;
	HI_U32 v_tmap_x1_pos                    ;
	HI_U32 v_tmap_x2_pos                    ;
	HI_U32 v_tmap_x3_pos                    ;
	HI_U32 v_tmap_x4_pos                    ;
	HI_U32 v_tmap_x5_pos                    ;
	HI_U32 v_tmap_x6_pos                    ;
	HI_U32 v_tmap_x7_pos                    ;
	HI_U32 v_tmap_x8_pos                    ;
	HI_U32 v_tmap_x1_num                    ;
	HI_U32 v_tmap_x2_num                    ;
	HI_U32 v_tmap_x3_num                    ;
	HI_U32 v_tmap_x4_num                    ;
	HI_U32 v_tmap_x5_num                    ;
	HI_U32 v_tmap_x6_num                    ;
	HI_U32 v_tmap_x7_num                    ;
	HI_U32 v_tmap_x8_num                    ;
	HI_U32 v_smap_x1_step                   ;
	HI_U32 v_smap_x2_step                   ;
	HI_U32 v_smap_x3_step                   ;
	HI_U32 v_smap_x4_step                   ;
	HI_U32 v_smap_x5_step                   ;
	HI_U32 v_smap_x6_step                   ;
	HI_U32 v_smap_x7_step                   ;
	HI_U32 v_smap_x8_step                   ;
	HI_U32 v_smap_x1_pos                    ;
	HI_U32 v_smap_x2_pos                    ;
	HI_U32 v_smap_x3_pos                    ;
	HI_U32 v_smap_x4_pos                    ;
	HI_U32 v_smap_x5_pos                    ;
	HI_U32 v_smap_x6_pos                    ;
	HI_U32 v_smap_x7_pos                    ;
	HI_U32 v_smap_x8_pos                    ;
	HI_U32 v_smap_x1_num                    ;
	HI_U32 v_smap_x2_num                    ;
	HI_U32 v_smap_x3_num                    ;
	HI_U32 v_smap_x4_num                    ;
	HI_U32 v_smap_x5_num                    ;
	HI_U32 v_smap_x6_num                    ;
	HI_U32 v_smap_x7_num                    ;
	HI_U32 v_smap_x8_num                    ;
	HI_U32 vhdr_tmap_luma_coef0             ;
	HI_U32 vhdr_tmap_luma_coef1             ;
	HI_U32 vhdr_tmap_luma_coef2             ;
	HI_U32 vhdr_tmap_luma_scale             ;
	HI_U32 vhdr_tmap_coef_scale             ;
	HI_U32 vhdr_tmap_out_clip_min           ;
	HI_U32 vhdr_tmap_out_clip_max           ;
	HI_S32 vhdr_tmap_out_dc0                ;
	HI_S32 vhdr_tmap_out_dc1                ;
	HI_S32 vhdr_tmap_out_dc2                ;
	HI_U32 vhdr_tmap_scale_mix_alpha        ;
	HI_U32 vhdr_tmap_mix_alpha              ;
	HI_U32 v_gmm_x1_step                    ;
	HI_U32 v_gmm_x2_step                    ;
	HI_U32 v_gmm_x3_step                    ;
	HI_U32 v_gmm_x4_step                    ;
	HI_U32 v_gmm_x5_step                    ;
	HI_U32 v_gmm_x6_step                    ;
	HI_U32 v_gmm_x7_step                    ;
	HI_U32 v_gmm_x8_step                    ;
	HI_U32 v_gmm_x1_pos                     ;
	HI_U32 v_gmm_x2_pos                     ;
	HI_U32 v_gmm_x3_pos                     ;
	HI_U32 v_gmm_x4_pos                     ;
	HI_U32 v_gmm_x5_pos                     ;
	HI_U32 v_gmm_x6_pos                     ;
	HI_U32 v_gmm_x7_pos                     ;
	HI_U32 v_gmm_x8_pos                     ;
	HI_U32 v_gmm_x1_num                     ;
	HI_U32 v_gmm_x2_num                     ;
	HI_U32 v_gmm_x3_num                     ;
	HI_U32 v_gmm_x4_num                     ;
	HI_U32 v_gmm_x5_num                     ;
	HI_U32 v_gmm_x6_num                     ;
	HI_U32 v_gmm_x7_num                     ;
	HI_U32 v_gmm_x8_num                     ;
	HI_U32 vhdr_dither_sed_y0               ;
	HI_U32 vhdr_dither_sed_u0               ;
	HI_U32 vhdr_dither_sed_v0               ;
	HI_U32 vhdr_dither_sed_w0               ;
	HI_U32 vhdr_dither_sed_y1               ;
	HI_U32 vhdr_dither_sed_u1               ;
	HI_U32 vhdr_dither_sed_v1               ;
	HI_U32 vhdr_dither_sed_w1               ;
	HI_U32 vhdr_dither_thr_max              ;
	HI_U32 vhdr_dither_thr_min              ;
	HI_S32 vhdr_r2y_coef00                  ;
	HI_S32 vhdr_r2y_coef01                  ;
	HI_S32 vhdr_r2y_coef02                  ;
	HI_S32 vhdr_r2y_coef10                  ;
	HI_S32 vhdr_r2y_coef11                  ;
	HI_S32 vhdr_r2y_coef12                  ;
	HI_S32 vhdr_r2y_coef20                  ;
	HI_S32 vhdr_r2y_coef21                  ;
	HI_S32 vhdr_r2y_coef22                  ;
	HI_U32 vhdr_cadj_scale2p                ;
	HI_U32 vhdr_r2y_scale2p                 ;
	HI_S32 vhdr_r2y_idc0                    ;
	HI_S32 vhdr_r2y_idc1                    ;
	HI_S32 vhdr_r2y_idc2                    ;
	HI_S32 vhdr_r2y_odc0                    ;
	HI_S32 vhdr_r2y_odc1                    ;
	HI_S32 vhdr_r2y_odc2                    ;
	HI_U32 vhdr_r2y_clip_c_min              ;
	HI_U32 vhdr_r2y_clip_y_min              ;
	HI_U32 vhdr_r2y_clip_c_max              ;
	HI_U32 vhdr_r2y_clip_y_max              ;

}VDP_HIHDR_V_PQ_CFG_S;


typedef struct
{
    //PQ ctrl
    HI_S32 hihdr_y2r_coef00        ;
    HI_S32 hihdr_y2r_coef01        ;
    HI_S32 hihdr_y2r_coef02        ;
    HI_S32 hihdr_y2r_coef03        ;
    HI_S32 hihdr_y2r_coef04        ;
    HI_S32 hihdr_y2r_coef05        ;
    HI_S32 hihdr_y2r_coef06        ;
    HI_S32 hihdr_y2r_coef07        ;
    HI_S32 hihdr_y2r_coef08        ;
    HI_S32 hihdr_y2r_coef10        ;
    HI_S32 hihdr_y2r_coef11        ;
    HI_S32 hihdr_y2r_coef12        ;
    HI_S32 hihdr_y2r_coef13        ;
    HI_S32 hihdr_y2r_coef14        ;
    HI_S32 hihdr_y2r_coef15        ;
    HI_S32 hihdr_y2r_coef16        ;
    HI_S32 hihdr_y2r_coef17        ;
    HI_S32 hihdr_y2r_coef18        ;
    HI_U32 hihdr_y2r_v1_scale2p    ;
    HI_U32 hihdr_y2r_v0_scale2p    ;
    HI_S32 hihdr_y2r_idc00         ;
    HI_S32 hihdr_y2r_idc01         ;
    HI_S32 hihdr_y2r_idc02         ;
    HI_S32 hihdr_y2r_odc00         ;
    HI_S32 hihdr_y2r_odc01         ;
    HI_S32 hihdr_y2r_odc02         ;
    HI_S32 hihdr_y2r_idc10         ;
    HI_S32 hihdr_y2r_idc11         ;
    HI_S32 hihdr_y2r_idc12         ;
    HI_S32 hihdr_y2r_odc10         ;
    HI_S32 hihdr_y2r_odc11         ;
    HI_S32 hihdr_y2r_odc12         ;
    HI_U32 hihdr_y2r_v1_clip_min   ;
    HI_U32 hihdr_y2r_v0_clip_min   ;
    HI_U32 hihdr_y2r_v1_clip_max   ;
    HI_U32 hihdr_y2r_v0_clip_max   ;

}VDP_HIHDR_V_Y2R_CFG_S;

typedef struct
{
	//Module ctrl
	HI_U32 vhdr_en                 ;
	HI_U32 vhdr_ck_gt_en           ;
	HI_U32 vhdr_degmm_en           ;
	HI_U32 vhdr_gamut_en           ;
	HI_U32 vhdr_tmap_en            ;
	HI_U32 vhdr_gmm_en             ;
	HI_U32 vhdr_dither_en          ;
	HI_U32 vhdr_r2y_en             ;
	HI_U32 hihdr_y2r_en            ;
	HI_U32 hihdr_y2r_ck_gt_en      ;
	HI_U32 vhdr_cadj_en            ;
	HI_U32 vhdr_gamut_bind         ;

	//Demo ctrl
	HI_U32 hihdr_v_demo_en    ;
	HI_U32 hihdr_v_demo_mode  ;
	HI_U32 hihdr_v_demo_pos   ;

	//PIP ctrl
	HI_U32 hihdr_v0_y2r_en    ;
	HI_U32 hihdr_v1_y2r_en    ;
	HI_U32 hihdr_v0_vhdr_en   ;
	HI_U32 hihdr_v1_vhdr_en   ;
	HI_U32 hihdr_v0_cl_en     ;
	HI_U32 hihdr_v1_cl_en     ;

    //Dither ctrl
	HI_U32 vhdr_dither_round_unlim ;
	HI_U32 vhdr_dither_round       ;
	HI_U32 vhdr_dither_mode        ;
	HI_U32 vhdr_dither_domain_mode ;
	HI_U32 vhdr_dither_tap_mode    ;

    //PQ ctrl
    VDP_HIHDR_V_PQ_CFG_S  stHiHdrPqCfg;
    VDP_HIHDR_V_Y2R_CFG_S stHiHdrY2RCfg;

}VDP_HIHDR_V_CFG_S;

HI_S32 VDP_DRV_SetHiHdrCfg(HI_U32 u32LayerId, VDP_HIHDR_V_CFG_S *pstHiHdrCfg);

#endif



