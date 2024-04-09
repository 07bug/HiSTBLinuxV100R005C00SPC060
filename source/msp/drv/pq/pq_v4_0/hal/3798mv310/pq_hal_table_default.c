/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_hal_table_default.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2015/10/30
  Description   :

******************************************************************************/

#include "hi_drv_pq.h"
#include "pq_hal_table_default.h"

static PQ_PHY_REG_S sg_stPhyRegDefault[PHY_REG_MAX] =
{
    /*Addr         Lsb       Msb  SourceMode  OutputMode   Module     Value        Description*/

    /***********************************************DEI***********************************************/
    /*IP_DETECT*/
    {0x0001,       0,      1,      0,      0,      HI_PQ_MODULE_DEI,       0},     //ip_detect_choice
    {0x0005,       0,      15,     0,      0,      HI_PQ_MODULE_DEI,       23800}, //sg_u32FrmRateThr_L
    {0x0009,       0,      15,     0,      0,      HI_PQ_MODULE_DEI,       24200}, //sg_u32FrmRateThr_H
    /*vpss_diectrl*/
    {0x1000,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       64},    //edge_smooth_ratio
    {0x1000,        17,     17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //die_rst
    {0x1000,        18,     18,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mchdir_c
    {0x1000,        19,     19,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mchdir_l
    {0x1000,        20,     20,     0,      0,      HI_PQ_MODULE_DEI,       0},     //edge_smooth_en
    {0x1000,        21,     21,     0,      0,      HI_PQ_MODULE_DEI,       0},     //ma_only
    {0x1000,        22,     22,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mc_only
    {0x1000,        23,     23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //two_four_pxl_share
    {0x1000,        24,     25,     0,      0,      HI_PQ_MODULE_DEI,       1},     //die_c_mode
    {0x1000,        26,     27,     0,      0,      HI_PQ_MODULE_DEI,       1},     //die_l_mode
    {0x1000,        28,     28,     0,      0,      HI_PQ_MODULE_DEI,       0},     //die_out_sel_c
    {0x1000,        29,     29,     0,      0,      HI_PQ_MODULE_DEI,       0},     //die_out_sel_l
    /*vpss_dielma2*/
    {0x1004,        1,      1,      0,      0,      HI_PQ_MODULE_DEI,       1},     //frame_motion_smooth_en
    {0x1004,        2,      2,      0,      0,      HI_PQ_MODULE_DEI,       0},     //luma_scesdf_max
    {0x1004,        4,      4,      0,      0,      HI_PQ_MODULE_DEI,       1},     //motion_iir_en
    {0x1004,        5,      5,      0,      0,      HI_PQ_MODULE_DEI,       0},     //luma_mf_max
    {0x1004,        6,      6,      0,      0,      HI_PQ_MODULE_DEI,       0},     //chroma_mf_max
    {0x1004,        7,      7,      0,      0,      HI_PQ_MODULE_DEI,       1},     //rec_mode_en
    {0x1004,        8,      23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //dei_st_rst_value
    {0x1004,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       8},     //chroma_mf_offset
    /*vpss_dieinten*/
    {0x1008,        0,      1,      0,      0,      HI_PQ_MODULE_DEI,       0},     //rec_mode_set_pre_info_mode
    {0x1008,        2,      2,      0,      0,      HI_PQ_MODULE_DEI,       0},     //rec_mode_output_mode
    {0x1008,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       2},     //dir_ratio_north
    {0x1008,        16,     31,     0,      0,      HI_PQ_MODULE_DEI,       0},     //min_north_strength
    /*vpss_diescale*/
    {0x100c,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       8},     //range_scale
    /*vpss_diecheck1*/
    {0x1010,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       30},    //bc1_max_dz
    {0x1010,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       2},     //bc1_autodz_gain
    {0x1010,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       4},     //bc1_gain
    /*vpss_diecheck2*/
    {0x1014,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       30},    //bc2_max_dz
    {0x1014,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       2},     //bc2_autodz_gain
    {0x1014,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       4},     //bc2_gain
    /*vpss_diedir0_3*/
    {0x1018,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       16},    //dir0_scale
    {0x1018,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir1_scale
    {0x1018,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir2_scale
    {0x1018,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir3_scale
    /*vpss_diedir4_7*/
    {0x101c,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       16},    //dir4_scale
    {0x101c,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir5_scale
    {0x101c,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir6_scale
    {0x101c,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir7_scale
    /*vpss_diedir8_11*/
    {0x1020,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       16},    //dir8_scale
    {0x1020,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir9_scale
    {0x1020,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir10_scale
    {0x1020,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       16},    //dir11_scale
    /*vpss_diedir12_14*/
    {0x1024,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       0},     //dir12_scale
    {0x1024,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       0},     //dir13_scale
    {0x1024,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       0},     //dir14_scale
    /*vpss_dieintpscl0*/
    {0x102c,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       6},     //intp_scale_ratio_1
    {0x102c,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       5},     //intp_scale_ratio_2
    {0x102c,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       5},     //intp_scale_ratio_3
    {0x102c,        12,     15,     0,      0,      HI_PQ_MODULE_DEI,       6},     //intp_scale_ratio_4
    {0x102c,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       6},     //intp_scale_ratio_5
    {0x102c,        20,     23,     0,      0,      HI_PQ_MODULE_DEI,       7},     //intp_scale_ratio_6
    {0x102c,        24,     27,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_7
    {0x102c,        28,     31,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_8
    /*vpss_dieintpscl1*/
    {0x1030,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_9
    {0x1030,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_10
    {0x1030,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_11
    {0x1030,        12,     15,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_12
    {0x1030,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_13
    {0x1030,        20,     23,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_14
    {0x1030,        24,     27,     0,      0,      HI_PQ_MODULE_DEI,       8},     //intp_scale_ratio_15
    /*vpss_diedirthd*/
    {0x1034,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       0},     //dir_thd
    {0x1034,        12,     12,     0,      0,      HI_PQ_MODULE_DEI,       1},     //edge_mode
    {0x1034,        13,     13,     0,      0,      HI_PQ_MODULE_DEI,       0},     //hor_edge_en
    /*vpss_diejitmtn*/
    {0x1038,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       8},     //jitter_gain
    {0x1038,        4,      11,     0,      0,      HI_PQ_MODULE_DEI,       0},     //jitter_coring
    {0x1038,        12,     19,     0,      0,      HI_PQ_MODULE_DEI,       0},     //fld_motion_coring
    /*vpss_diefldmtn*/
    {0x103c,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //fld_motion_thd_low
    {0x103c,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       255},   //fld_motion_thd_high
    {0x103c,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       -2},    //fld_motion_curve_slope
    {0x103c,        24,     27,     0,      0,      HI_PQ_MODULE_DEI,       8},     //fld_motion_gain
    {0x103c,        28,     28,     0,      0,      HI_PQ_MODULE_DEI,       1},     //fld_motion_wnd_mode
    {0x103c,        29,     29,     0,      0,      HI_PQ_MODULE_DEI,       1},     //long_motion_shf
    /*vpss_diemtndiffthd0*/
    {0x1040,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       16},    //motion_diff_thd_0
    {0x1040,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       144},   //motion_diff_thd_1
    {0x1040,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       208},   //motion_diff_thd_2
    {0x1040,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       255},   //motion_diff_thd_3
    /*vpss_diemtndiffthd1*/
    {0x1044,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       255},   //motion_diff_thd_4
    {0x1044,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       255},   //motion_diff_thd_5
    {0x1044,        16,     22,     0,      0,      HI_PQ_MODULE_DEI,       32},    //min_motion_iir_ratio
    {0x1044,        24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //max_motion_iir_ratio
    /*vpss_diemtniirslp*/
    {0x1048,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       1},     //motion_iir_curve_slope_0
    {0x1048,        6,      11,     0,      0,      HI_PQ_MODULE_DEI,       2},     //motion_iir_curve_slope_1
    {0x1048,        12,     17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //motion_iir_curve_slope_2
    {0x1048,        18,     23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //motion_iir_curve_slope_3
    {0x1048,        24,     30,     0,      0,      HI_PQ_MODULE_DEI,       32},    //motion_iir_curve_ratio_0
    /*vpss_diemtniirrat*/
    {0x104c,        0,      6,      0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_iir_curve_ratio_1
    {0x104c,        8,      14,     0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_iir_curve_ratio_2
    {0x104c,        16,     22,     0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_iir_curve_ratio_3
    {0x104c,        24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_iir_curve_ratio_4
    /*vpss_diehismode*/
    {0x1050,        0,      2,      0,      0,      HI_PQ_MODULE_DEI,       2},     //rec_mode_fld_motion_step_0
    {0x1050,        4,      6,      0,      0,      HI_PQ_MODULE_DEI,       2},     //rec_mode_fld_motion_step_1
    {0x1050,        8,      9,      0,      0,      HI_PQ_MODULE_DEI,       0},     //rec_mode_frm_motion_step_0
    {0x1050,        12,     13,     0,      0,      HI_PQ_MODULE_DEI,       0},     //rec_mode_frm_motion_step_1
    {0x1050,        16,     16,     0,      0,      HI_PQ_MODULE_DEI,       1},     //ppre_info_en
    {0x1050,        17,     17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //pre_info_en
    {0x1050,        18,     18,     0,      0,      HI_PQ_MODULE_DEI,       1},     //his_motion_en
    {0x1050,        19,     19,     0,      0,      HI_PQ_MODULE_DEI,       1},     //his_motion_using_mode
    {0x1050,        20,     20,     0,      0,      HI_PQ_MODULE_DEI,       0},     //his_motion_write_mode
    {0x1050,        21,     21,     0,      0,      HI_PQ_MODULE_DEI,       0},     //his_motion_info_write_mode
    /*vpss_diemorflt*/
    {0x1054,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //mor_flt_thd
    {0x1054,        8,      9,      0,      0,      HI_PQ_MODULE_DEI,       0},     //mor_flt_size
    {0x1054,        24,     24,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mor_flt_en
    {0x1054,        26,     26,     0,      0,      HI_PQ_MODULE_DEI,       0},     //med_blend_en
    /*vpss_diecombchk0*/
    {0x1058,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       255},   //comb_chk_min_hthd
    {0x1058,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       15},    //comb_chk_min_vthd
    {0x1058,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       9},     //comb_chk_lower_limit
    {0x1058,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       160},   //comb_chk_upper_limit
    /*vpss_diecombchk1*/
    {0x105c,        0,      6,      0,      0,      HI_PQ_MODULE_DEI,       16},    //comb_chk_edge_thd
    {0x105c,        8,      12,     0,      0,      HI_PQ_MODULE_DEI,       20},    //comb_chk_md_thd
    {0x105c,        16,     16,     0,      0,      HI_PQ_MODULE_DEI,       0},     //comb_chk_en
    /*vpss_diefrmmtnsmththd0*/
    {0x1060,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       8},     //frame_motion_smooth_thd0
    {0x1060,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       72},    //frame_motion_smooth_thd1
    {0x1060,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_motion_smooth_thd2
    {0x1060,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_motion_smooth_thd3
    /*vpss_diefrmmtnsmththd1*/
    {0x1064,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_motion_smooth_thd4
    {0x1064,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       255},   //frame_motion_smooth_thd5
    {0x1064,        16,     22,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_ratio_min
    {0x1064,        24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_motion_smooth_ratio_max
    /*vpss_diefrmmtnsmthslp*/
    {0x1068,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       8},     //frame_motion_smooth_slope0
    {0x1068,        6,      11,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_slope1
    {0x1068,        12,     17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_slope2
    {0x1068,        18,     23,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_slope3
    {0x1068,        24,     30,     0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_motion_smooth_ratio0
    /*vpss_diefrmmtnsmthrat*/
    {0x106c,        0,      6,      0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_motion_smooth_ratio1
    {0x106c,        8,      14,     0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_motion_smooth_ratio2
    {0x106c,        16,     22,     0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_motion_smooth_ratio3
    {0x106c,        24,     30,     0,      0,      HI_PQ_MODULE_DEI,       64},    //frame_motion_smooth_ratio4
    /*vpss_diemtnadj*/
    {0x1080,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_adjust_gain
    {0x1080,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       0},     //motion_adjust_coring
    {0x1080,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       64},    //motion_adjust_gain_chr
    /*vpss_dieedgeformc*/
    {0x109c,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       0},     //edge_coring
    {0x109c,        10,     19,     0,      0,      HI_PQ_MODULE_DEI,       6},     //edge_scale
    /*vpss_diefusion0*/
    {0x10a8,        0,      6,      0,      0,      HI_PQ_MODULE_DEI,       16},    //k_y_mcw
    {0x10a8,        16,     22,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_c_mcw
    /*vpss_diefusion1*/
    {0x10ac,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       64},    //x0_mcw_adj
    {0x10ac,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k0_mcw_adj
    {0x10ac,        16,     27,     0,      0,      HI_PQ_MODULE_DEI,       1023},  //g0_mcw_adj
    /*vpss_diefusion2*/
    {0x10b0,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       128},   //k1_mcw_adj
    /*vpss_diefusion3*/
    {0x10b4,        20,     20,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mc_lai_bldmode
    /*vpss_diemagbmthd0*/
    {0x10b8,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       48},    //ma_gbm_thd1
    {0x10b8,        16,     25,     0,      0,      HI_PQ_MODULE_DEI,       16},    //ma_gbm_thd0
    /*vpss_diemagbmthd1*/
    {0x10bc,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       112},   //ma_gbm_thd3
    {0x10bc,        16,     25,     0,      0,      HI_PQ_MODULE_DEI,       80},    //ma_gbm_thd2
    /*vpss_diemcgbmcoef0*/
    {0x10c0,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       4},     //mtth0_gmd
    {0x10c0,        4,      8,      0,      0,      HI_PQ_MODULE_DEI,       12},    //mtth1_gmd
    {0x10c0,        12,     17,     0,      0,      HI_PQ_MODULE_DEI,       20},    //mtth2_gmd
    {0x10c0,        20,     25,     0,      0,      HI_PQ_MODULE_DEI,       28},    //mtth3_gmd
    {0x10c0,        28,     28,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mtfilten_gmd
    /*vpss_diemcgbmcoef1*/
    {0x10c4,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       4},     //k_maxmag_gmd
    {0x10c4,        4,      10,     0,      0,      HI_PQ_MODULE_DEI,       22},    //k_difh_gmd
    {0x10c4,        12,     19,     0,      0,      HI_PQ_MODULE_DEI,       96},    //k_mag_gmd
    /*vpss_diekmag1*/
    {0x10c8,        0,      6,      0,      0,      HI_PQ_MODULE_DEI,       31},    //kmagh_1
    {0x10c8,        7,      13,     0,      0,      HI_PQ_MODULE_DEI,       31},    //kmagh_2
    {0x10c8,        14,     18,     0,      0,      HI_PQ_MODULE_DEI,       8},     //kmagv_1
    {0x10c8,        19,     23,     0,      0,      HI_PQ_MODULE_DEI,       2},     //kmagv_2
    {0x10c8,        24,     28,     0,      0,      HI_PQ_MODULE_DEI,       31},    //khoredge
    /*vpss_diekmag2*/
    {0x10cc,        0,      2,      0,      0,      HI_PQ_MODULE_DEI,       2},     //scaler_horedge
    {0x10cc,        3,      3,      0,      0,      HI_PQ_MODULE_DEI,       0},     //frame_mag_en
    {0x10cc,        4,      11,     0,      0,      HI_PQ_MODULE_DEI,       60},    //motion_limt_1
    {0x10cc,        12,     19,     0,      0,      HI_PQ_MODULE_DEI,       60},    //motion_limt_2
    {0x10cc,        20,     22,     0,      0,      HI_PQ_MODULE_DEI,       4},     //scaler_framemotion
    /*vpss_die_s3add*/
    {0x10d0,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       8},     //dir_ratio_c
    {0x10d0,        4,      8,      0,      0,      HI_PQ_MODULE_DEI,       0},     //edge_str_coring_c
    /*vpss_mcdi_rgdify*/
    {0x1108,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       511},   //lmt_rgdify
    {0x1108,        10,     13,     0,      0,      HI_PQ_MODULE_DEI,       7},     //core_rgdify
    {0x1108,        14,     23,     0,      0,      HI_PQ_MODULE_DEI,       1023},  //g_rgdifycore
    {0x1108,        24,     27,     0,      0,      HI_PQ_MODULE_DEI,       3},     //k_rgdifycore
    /*vpss_mcdi_rgsad*/
    {0x110c,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       255},   //g_tpdif_rgsad
    {0x110c,        9,      14,     0,      0,      HI_PQ_MODULE_DEI,       63},    //k_tpdif_rgsad
    {0x110c,        15,     21,     0,      0,      HI_PQ_MODULE_DEI,       32},    //kmv_rgsad
    {0x110c,        23,     25,     0,      0,      HI_PQ_MODULE_DEI,       1},     //coef_sadlpf
    /*vpss_mcdi_rgmv*/
    {0x1110,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       256},   //th_0mvsad_rgmv
    {0x1110,        10,     18,     0,      0,      HI_PQ_MODULE_DEI,       128},   //th_saddif_rgmv
    {0x1110,        19,     26,     0,      0,      HI_PQ_MODULE_DEI,       48},     //thmag_rgmv
    /*vpss_mcdi_rgmag0*/
    {0x1114,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       255},   //lmt_mag_rg
    {0x1114,        10,     13,     0,      0,      HI_PQ_MODULE_DEI,       3},     //core_mag_rg
    /*vpss_mcdi_rgmag1*/
    {0x1118,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       1},     //en_mvadj_rgmvls
    {0x1118,        1,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //th_mvadj_rgmvls
    {0x1118,        5,      8,      0,      0,      HI_PQ_MODULE_DEI,       12},    //k_mag_rgmvls
    {0x1118,        9,      15,     0,      0,      HI_PQ_MODULE_DEI,       -64},   //core_mag_rgmvls
    {0x1118,        16,     20,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k_mv_rgmvls
    {0x1118,        21,     25,     0,      0,      HI_PQ_MODULE_DEI,       2},     //core_mv_rgmvls
    /*vpss_mcdi_rgls*/
    {0x111c,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       8},     //k_sadcore_rgmv
    {0x111c,        4,      8,      0,      0,      HI_PQ_MODULE_DEI,       8},     //th_sad_rgls
    {0x111c,        9,      14,     0,      0,      HI_PQ_MODULE_DEI,       40},    //th_mag_rgls
    {0x111c,        15,     18,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_sad_rgls
    /*vpss_mcdi_sel*/
    {0x1120,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //force_mvx
    {0x1120,        8,      8,      0,      0,      HI_PQ_MODULE_DEI,       0},     //force_mven
    /*vpss_mcdi_dlt0*/
    {0x1124,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       4},     //th_hblkdist_mvdlt
    {0x1124,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       1},     //th_vblkdist_mvdlt
    {0x1124,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       8},     //th_ls_mvdlt
    {0x1124,        12,     15,     0,      0,      HI_PQ_MODULE_DEI,       4},     //th_rgmvx_mvdlt
    {0x1124,        16,     18,     0,      0,      HI_PQ_MODULE_DEI,       6},     //th_blkmvx_mvdlt
    /*vpss_mcdi_dlt1*/
    {0x1128,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       16},    //thh_sad_mvdlt
    {0x1128,        5,      11,     0,      0,      HI_PQ_MODULE_DEI,       96},    //thl_sad_mvdlt
    {0x1128,        12,     17,     0,      0,      HI_PQ_MODULE_DEI,       16},    //g_mag_mvdlt
    {0x1128,        18,     22,     0,      0,      HI_PQ_MODULE_DEI,       12},    //th_mag_mvdlt
    {0x1128,        23,     25,     0,      0,      HI_PQ_MODULE_DEI,       2},     //k_sadcore_mvdlt
    /*vpss_mcdi_rgmcw0*/
    {0x112c,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //k_core_simimv
    {0x112c,        5,      7,      0,      0,      HI_PQ_MODULE_DEI,       0},     //gl_core_simimv
    {0x112c,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       15},    //gh_core_simimv
    {0x112c,        14,     19,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k_simimvw
    {0x112c,        20,     24,     0,      0,      HI_PQ_MODULE_DEI,       20},    //k_rglsw
    /*vpss_mcdi_rgmcw1*/
    {0x1130,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       1},     //rgtb_en_mcw
    {0x1130,        1,      3,      0,      0,      HI_PQ_MODULE_DEI,       3},     //core_mvy_mcw
    {0x1130,        4,      9,      0,      0,      HI_PQ_MODULE_DEI,       16},    //k_mvy_mcw
    {0x1130,        10,     18,     0,      0,      HI_PQ_MODULE_DEI,       64},    //core_rgsadadj_mcw
    {0x1130,        19,     22,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_rgsadadj_mcw
    {0x1130,        23,     27,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k_core_vsaddif
    /*vpss_mcdi_rgmcw2*/
    {0x1134,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //gl_core_vsaddif
    {0x1134,        5,      11,     0,      0,      HI_PQ_MODULE_DEI,       64},    //gh_core_vsad_dif
    {0x1134,        12,     17,     0,      0,      HI_PQ_MODULE_DEI,       8},    //k_vsaddifw
    {0x1134,        18,     18,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mode_rgysad_mcw
    {0x1134,        19,     26,     0,      0,      HI_PQ_MODULE_DEI,       24},    //core_rgmag_mcw
    /*vpss_mcdi_rgmcw3*/
    {0x1138,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       64},    //x0_rgmag_mcw
    {0x1138,        9,      17,     0,      0,      HI_PQ_MODULE_DEI,       256},   //k0_rgmag_mcw
    {0x1138,        18,     25,     0,      0,      HI_PQ_MODULE_DEI,       64},    //g0_rgmag_mcw
    /*vpss_mcdi_rgmcw4*/
    {0x113c,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       320},   //k1_rgmag_mcw
    {0x113c,        9,      16,     0,      0,      HI_PQ_MODULE_DEI,       96},    //core_rgsad_mcw
    {0x113c,        17,     26,     0,      0,      HI_PQ_MODULE_DEI,       512},   //x0_rgsad_mcw
    /*vpss_mcdi_rgmcw5*/
    {0x1140,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       160},   //k0_rgsad_mcw
    {0x1140,        9,      16,     0,      0,      HI_PQ_MODULE_DEI,       255},   //g0_rgsad_mcw
    {0x1140,        17,     25,     0,      0,      HI_PQ_MODULE_DEI,       128},   //k1_rgsad_mcw
    /*vpss_mcdi_rgmcw6*/
    {0x1144,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       16},    //x0_smrg_mcw
    {0x1144,        8,      15,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k0_smrg_mcw
    {0x1144,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       112},   //x_rgsad_mcw
    {0x1144,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       24},    //k_rgsad_mcw
    /*vpss_mcdi_tpmcw0*/
    {0x1148,        0,      7,      0,      0,      HI_PQ_MODULE_DEI,       255},   //x0_tpmvdist_mcw
    {0x1148,        8,      14,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k0_tpmvdist_mcw
    {0x1148,        15,     22,     0,      0,      HI_PQ_MODULE_DEI,       0},     //g0_tpmvdist_mcw
    {0x1148,        23,     29,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k1_tpmvdist_mcw
    /*vpss_mcdi_tpmcw1*/
    {0x114c,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       4},     //k_minmvdist_mcw
    {0x114c,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       4},     //k_avgmvdist_mcw
    {0x114c,        8,      10,     0,      0,      HI_PQ_MODULE_DEI,       2},     //b_core_tpmvdist_mcw
    {0x114c,        11,     13,     0,      0,      HI_PQ_MODULE_DEI,       2},     //k_core_tpmvdist_mcw
    /*vpss_mcdi_wndmcw0*/
    {0x1150,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       18},    //k_difhcore_mcw
    {0x1150,        5,      10,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k_difvcore_mcw
    {0x1150,        11,     14,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_max_core_mcw
    {0x1150,        15,     18,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_max_dif_mcw
    {0x1150,        19,     22,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k1_max_mag_mcw
    {0x1150,        23,     26,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k0_max_mag_mcw
    {0x1150,        27,     30,     0,      0,      HI_PQ_MODULE_DEI,       15},    //k_tbdif_mcw
    /*vpss_mcdi_wndmcw1*/
    {0x1154,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       0},     //k_tbmag_mcw
    {0x1154,        4,      10,     0,      0,      HI_PQ_MODULE_DEI,       32},    //x0_mag_wnd_mcw
    {0x1154,        11,     14,     0,      0,      HI_PQ_MODULE_DEI,       6},     //k0_mag_wnd_mcw
    {0x1154,        15,     20,     0,      0,      HI_PQ_MODULE_DEI,       24},    //g0_mag_wnd_mcw
    {0x1154,        21,     24,     0,      0,      HI_PQ_MODULE_DEI,       6},     //k1_mag_wnd_mcw
    /*vpss_mcdi_wndmcw2*/
    {0x1158,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       288},   //g1_mag_wnd_mcw
    {0x1158,        9,      15,     0,      0,      HI_PQ_MODULE_DEI,       8},     //x0_sad_wnd_mcw
    {0x1158,        16,     20,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k0_sad_wnd_mcw
    {0x1158,        21,     28,     0,      0,      HI_PQ_MODULE_DEI,       16},    //g0_sad_wnd_mcw
    /*vpss_mcdi_wndmcw3*/
    {0x115c,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       16},    //k1_sad_wnd_mcw
    {0x115c,        5,      13,     0,      0,      HI_PQ_MODULE_DEI,       288},   //g1_sad_wnd_mcw
    /*vpss_mcdi_vertweight0*/
    {0x1160,        0,      3,      0,      0,      HI_PQ_MODULE_DEI,       12},    //k_max_hvdif_dw
    {0x1160,        4,      7,      0,      0,      HI_PQ_MODULE_DEI,       15},    //gain_lpf_dw
    {0x1160,        8,      11,     0,      0,      HI_PQ_MODULE_DEI,       5},     //core_bhvdif_dw
    {0x1160,        12,     18,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k_bhvdif_dw
    {0x1160,        20,     22,     0,      0,      HI_PQ_MODULE_DEI,       0},     //b_bhvdif_dw
    {0x1160,        24,     26,     0,      0,      HI_PQ_MODULE_DEI,       0},     //b_hvdif_dw
    /*vpss_mcdi_vertweight1*/
    {0x1164,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       16},    //core_hvdif_dw
    {0x1164,        8,      12,     0,      0,      HI_PQ_MODULE_DEI,       20},    //k_difv_dw
    {0x1164,        16,     19,     0,      0,      HI_PQ_MODULE_DEI,       -2},    //core_mv_dw
    {0x1164,        20,     25,     0,      0,      HI_PQ_MODULE_DEI,       56},    //b_mv_dw
    /*vpss_mcdi_vertweight2*/
    {0x1168,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       256},   //x0_hvdif_dw
    {0x1168,        9,      12,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k0_hvdif_dw
    {0x1168,        16,     24,     0,      0,      HI_PQ_MODULE_DEI,       128},   //g0_hvdif_dw
    {0x1168,        25,     30,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k1_hvdif_dw
    /*vpss_mcdi_vertweight3*/
    {0x116c,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //x0_mv_dw
    {0x116c,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       16},    //k0_mv_dw
    {0x116c,        16,     21,     0,      0,      HI_PQ_MODULE_DEI,       32},    //g0_mv_dw
    {0x116c,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       64},    //k1_mv_dw
    /*vpss_mcdi_vertweight4*/
    {0x1170,        0,      6,      0,      0,      HI_PQ_MODULE_DEI,       32},    //x0_mt_dw
    {0x1170,        8,      13,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k0_mt_dw
    {0x1170,        16,     23,     0,      0,      HI_PQ_MODULE_DEI,       64},    //g0_mt_dw
    {0x1170,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       32},    //k1_mt_dw
    /*vpss_mcdi_vertweight5*/
    {0x1174,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       31},    //g0_mv_mt
    {0x1174,        8,      9,      0,      0,      HI_PQ_MODULE_DEI,       1},     //x0_mv_mt
    {0x1174,        12,     16,     0,      0,      HI_PQ_MODULE_DEI,       20},    //k1_mv_mt
    {0x1174,        24,     31,     0,      0,      HI_PQ_MODULE_DEI,       0},     //b_mt_dw
    /*vpss_mcdi_mc0*/
    {0x1178,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       16},    //gain_up_mclpfv
    {0x1178,        5,      9,      0,      0,      HI_PQ_MODULE_DEI,       16},    //gain_dn_mclpfv
    {0x1178,        10,     14,     0,      0,      HI_PQ_MODULE_DEI,       16},    //gain_mclpfh
    {0x1178,        15,     15,     0,      0,      HI_PQ_MODULE_DEI,       0},     //rs_pxlmag_mcw
    {0x1178,        16,     18,     0,      0,      HI_PQ_MODULE_DEI,       2},     //x_pxlmag_mcw
    {0x1178,        20,     26,     0,      0,      HI_PQ_MODULE_DEI,       8},     //k_pxlmag_mcw
    {0x1178,        28,     28,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mclpf_mode
    /*vpss_mcdi_mc1*/
    {0x117c,        0,      5,      0,      0,      HI_PQ_MODULE_DEI,       0},     //g_pxlmag_mcw
    /*vpss_mcdi_mc2*/
    {0x1180,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //k_y_vertw
    {0x1180,        5,      11,     0,      0,      HI_PQ_MODULE_DEI,       15},    //k_c_vertw
    /*vpss_mcdi_mc3*/
    {0x1184,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       8},     //k_delta
    {0x1184,        5,      7,      0,      0,      HI_PQ_MODULE_DEI,       4},     //bdh_mcpos
    {0x1184,        8,      10,     0,      0,      HI_PQ_MODULE_DEI,       4},     //bdv_mcpos
    /*vpss_mcdi_mc5*/
    {0x118c,        6,      17,     0,      0,      HI_PQ_MODULE_DEI,       0},     //c0_mc
    {0x118c,        18,     29,     0,      0,      HI_PQ_MODULE_DEI,       0},     //r0_mc
    /*vpss_mcdi_mc6*/
    {0x1190,        0,      11,     0,      0,      HI_PQ_MODULE_DEI,       4095},  //c1_mc
    {0x1190,        12,     23,     0,      0,      HI_PQ_MODULE_DEI,       4095},  //r1_mc
    {0x1190,        24,     29,     0,      0,      HI_PQ_MODULE_DEI,       32},    //mcmvrange
    /*vpss_mcdi_mc7*/
    {0x1194,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       0},     //scenechange_mc
    {0x1194,        1,      5,      0,      0,      HI_PQ_MODULE_DEI,       8},     //x_frcount_mc
    {0x1194,        6,      12,     0,      0,      HI_PQ_MODULE_DEI,       48},    //k_frcount_mc
    /*vpss_mcdi_numt*/
    {0x11a0,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       0},     //numt_lpf_en
    {0x11a0,        1,      6,      0,      0,      HI_PQ_MODULE_DEI,       0},     //numt_coring
    {0x11a0,        7,      14,     0,      0,      HI_PQ_MODULE_DEI,       32},    //numt_gain
    {0x11a0,        15,     15,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mc_numt_blden
    /*vpss_mcdi_s3add0*/
    {0x11a4,        0,      2,      0,      0,      HI_PQ_MODULE_DEI,       0},     //core_rglsw
    /*vpss_mcdi_s3add3*/
    {0x11b0,        21,     29,     0,      0,      HI_PQ_MODULE_DEI,       128},   //th_cur_blksad
    /*vpss_mcdi_s3add4*/
    {0x11b4,        0,      8,      0,      0,      HI_PQ_MODULE_DEI,       256},   //thh_neigh_blksad
    {0x11b4,        9,      17,     0,      0,      HI_PQ_MODULE_DEI,       128},   //thl_neigh_blksad
    {0x11b4,        18,     22,     0,      0,      HI_PQ_MODULE_DEI,       8},     //th_cur_blkmotion
    /*vpss_mcdi_s3add5*/
    {0x11b8,        0,      9,      0,      0,      HI_PQ_MODULE_DEI,       512},   //th_rgmv_mag
    {0x11b8,        10,     10,     0,      0,      HI_PQ_MODULE_DEI,       1},     //blkmv_update_en
    /*vpss_mcdi_s3add7*/
    {0x11c0,        18,     18,     0,      0,      HI_PQ_MODULE_DEI,       0},     //submv_sadchk_en
    /*vpss_mcdi_stillcnt0*/
    {0x11c4,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       2},     //cntlut_0
    {0x11c4,        5,      9,      0,      0,      HI_PQ_MODULE_DEI,       2},     //cntlut_1
    {0x11c4,        10,     14,     0,      0,      HI_PQ_MODULE_DEI,       1},     //cntlut_2
    {0x11c4,        15,     19,     0,      0,      HI_PQ_MODULE_DEI,       1},     //cntlut_3
    {0x11c4,        20,     24,     0,      0,      HI_PQ_MODULE_DEI,       -15},   //cntlut_4
    {0x11c4,        25,     29,     0,      0,      HI_PQ_MODULE_DEI,       -15},   //cntlut_5
    /*vpss_mcdi_stillcnt1*/
    {0x11c8,        0,      4,      0,      0,      HI_PQ_MODULE_DEI,       -15},   //cntlut_6
    {0x11c8,        5,      9,      0,      0,      HI_PQ_MODULE_DEI,       -15},   //cntlut_7
    {0x11c8,        10,     14,     0,      0,      HI_PQ_MODULE_DEI,       -15},   //cntlut_8
    {0x11c8,        15,     15,     0,      0,      HI_PQ_MODULE_DEI,       0},     //mc_mtshift
    {0x11c8,        16,     16,     0,      0,      HI_PQ_MODULE_DEI,       1},     //mcw_scnt_en
    {0x11c8,        17,     25,     0,      0,      HI_PQ_MODULE_DEI,       273},   //mcw_scnt_gain
    /*vpss_mcdi_demo*/
    {0x11cc,        0,      0,      0,      0,      HI_PQ_MODULE_DEI,       0},     //demo_en
    {0x11cc,        1,      2,      0,      0,      HI_PQ_MODULE_DEI,       2},     //demo_mode_l
    {0x11cc,        3,      4,      0,      0,      HI_PQ_MODULE_DEI,       2},     //demo_mode_r
    {0x11cc,        5,      16,     0,      0,      HI_PQ_MODULE_DEI,       0},     //demo_border

    /***********************************************FMD***********************************************/
    /*FMD_CTRL*/
    {0x1000,        20,     20,     0,      0,      HI_PQ_MODULE_FMD,       0},     //edge_smooth_en
    {0x1000,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       32},    //edge_smooth_ratio
    {0x10dc,        0,      2,      0,      0,      HI_PQ_MODULE_FMD,       6},     //
    /*FMD_CTRL_ReadOnly*/
    {0x1000,        19,     19,     0,      0,      HI_PQ_MODULE_FMD,       0},     //mchdir_l
    {0x1000,        18,     18,     0,      0,      HI_PQ_MODULE_FMD,       0},     //mchdir_c
    /*VPSS_PDPCCMOV*/
    {0x10d8,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       20},    //mov_coring_norm
    {0x10d8,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       50},    //mov_coring_tkr
    {0x10d8,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       20},    //mov_coring_blk
    /*VPSS_PDPHISTTHD*/
    {0x10d4,        24,     31,     0,      0,      HI_PQ_MODULE_FMD,       32},    //hist_thd3
    {0x10d4,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       32},    //hist_thd2
    {0x10d4,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       16},    //hist_thd1
    {0x10d4,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       8},     //hist_thd0
    /*VPSS_PDCTRL*/
    {0x10dc,        19,     19,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_mode
    {0x10e0,        20,     27,     0,      0,      HI_PQ_MODULE_FMD,       30},    //diff_movblk_thd
    /*VPSS_PDUMTHD*/
    {0x10e4,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       64},    //um_thd2
    {0x10e4,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       32},    //um_thd1
    {0x10e4,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       8},     //um_thd0
    /*VPSS_PDPCCCORING*/
    {0x10e8,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       16},    //coring_blk
    {0x10e8,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       16},    //coring_norm
    {0x10e8,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       90},    //coring_tkr
    /*VPSS_PDPCCHVTHD*/
    {0x10ec,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       16},    //pcc_hthd
    {0x10f0,        24,     31,     0,      0,      HI_PQ_MODULE_FMD,       128},   //pcc_vthd3
    {0x10f0,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       64},    //pcc_vthd2
    {0x10f0,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       32},    //pcc_vthd1
    {0x10f0,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       16},    //pcc_vthd0
    /*VPSS_PDITDIFFVTHD*/
    {0x10f4,        24,     31,     0,      0,      HI_PQ_MODULE_FMD,       32},    //itdiff_vthd3
    {0x10f4,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       16},    //itdiff_vthd2
    {0x10f4,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       8},     //itdiff_vthd1
    {0x10f4,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       4},     //itdiff_vthd0
    /*VPSS_PDLASITHD*/
    {0x10f8,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       32},    //lasi_mov_thd
    {0x10f8,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       15},    //lasi_edge_thd
    {0x10f8,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       20},    //lasi_coring_thd
    /*PDLASIMODE0COEF*/
    {0x10fc,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_coring
    {0x10fc,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,      32},     //lasi_txt_alpha
    {0x1100,        24,     31,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_thd3
    {0x1100,        16,     23,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_thd2
    {0x1100,        8,      15,     0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_thd1
    {0x1100,        0,      7,      0,      0,      HI_PQ_MODULE_FMD,       0},     //lasi_txt_thd0
    /*PDLASIMODE0COEF*/
    {0x1104,        12,     23,     0,      0,      HI_PQ_MODULE_FMD,       0},     //region1_y_stt
    {0x1104,        0,      11,     0,      0,      HI_PQ_MODULE_FMD,       0},     //region1_y_end

    /***********************************************DB***********************************************/
    /*VPSS_DB_CTRL*/
    {0x2100,        0,      0,      0,      0,      HI_PQ_MODULE_DB,        1},     //db_en
    {0x2100,        1,      1,      0,      0,      HI_PQ_MODULE_DB,        1},     //dm_en
    {0x2100,        2,      2,      0,      0,      HI_PQ_MODULE_DB,        1},     //snr_en
    {0x2100,        3,      3,      0,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_hor_en
    {0x2100,        9,      9,      0,      0,      HI_PQ_MODULE_DB,        0},     //dbm_demo_en
    {0x2100,        10,     10,     0,      0,      HI_PQ_MODULE_DB,        0},     //dbm_demo_mode
    {0x2100,        13,     13,     0,      0,      HI_PQ_MODULE_DB,        1},     //det_hy_en
    {0x2100,        16,     18,     0,      0,      HI_PQ_MODULE_DB,        6},     //dbm_out_mode
    /*vpss_dbm_demo*/
    {0x2104,        0,      15,     0,      0,      HI_PQ_MODULE_DB,        0},     //dbm_demo_pos_x
    /*vpss_db_dir*/
    {0x2108,        0,      4,      0,      0,      HI_PQ_MODULE_DB,        24},    //db_grad_sub_ratio
    {0x2108,        8,      12,     0,      0,      HI_PQ_MODULE_DB,        2},     //db_ctrst_thresh
    /*vpss_db_blk*/
    {0x210c,        0,      6,      0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_h_blk_size
    /*vpss_db_ratio*/
    {0x2110,        0,      1,      0,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_hor_scale_ratio
    {0x2110,        8,      9,      0,      0,      HI_PQ_MODULE_DB,        1},     //db_lum_hor_filter_sel
    {0x2110,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_global_db_strenth_lum
    {0x2110,        20,     21,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_txt_win_size
    /*vpss_db_lhhf*/
    {0x2114,        0,      6,      0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_diff_core
    {0x2114,        8,      11,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_diff_gain1
    {0x2114,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_diff_gain2
    {0x2114,        16,     22,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_hf_var_core
    {0x2114,        24,     27,     0,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_hf_var_gain1
    {0x2114,        28,     31,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_hf_var_gain2
    /*vpss_db_lvhf*/
    {0x2118,        16,     20,     0,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_adj_gain
    {0x2118,        21,     23,     0,      0,      HI_PQ_MODULE_DB,        7},     //db_lum_hor_bord_adj_gain
    /*vpss_db_ctrs*/
    {0x211c,        0,      4,      0,      0,      HI_PQ_MODULE_DB,        0},     //db_ctrst_adj_core
    {0x211c,        5,      6,      0,      0,      HI_PQ_MODULE_DB,        2},     //db_dir_smooth_mode
    {0x211c,        8,      11,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_ctrst_adj_gain1
    {0x211c,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_ctrst_adj_gain2
    {0x211c,        16,     19,     0,      0,      HI_PQ_MODULE_DB,        4},     //db_max_lum_hor_db_dist
    /*vpss_db_lut0*/
    {0x2120,        0,      3,      0,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_delta_lut_p0
    {0x2120,        4,      7,      0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p1
    {0x2120,        8,      11,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p2
    {0x2120,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p3
    {0x2120,        16,     19,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p4
    {0x2120,        20,     23,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p5
    {0x2120,        24,     27,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p6
    {0x2120,        28,     31,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p7
    /*vpss_db_lut1*/
    {0x2124,        0,      3,      0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p8
    {0x2124,        4,      7,      0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p9
    {0x2124,        8,      11,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_lum_hor_delta_lut_p10
    {0x2124,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        6},     //db_lum_hor_delta_lut_p11
    {0x2124,        16,     19,     0,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_hor_delta_lut_p12
    {0x2124,        20,     23,     0,      0,      HI_PQ_MODULE_DB,        2},     //db_lum_hor_delta_lut_p13
    {0x2124,        24,     27,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_delta_lut_p14
    {0x2124,        28,     31,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_hor_delta_lut_p15
    /*vpss_db_lut2*/
    {0x2128,        0,      2,      0,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_h_str_fade_lut_p0
    {0x2128,        3,      5,      0,      0,      HI_PQ_MODULE_DB,        4},     //db_lum_h_str_fade_lut_p1
    {0x2128,        6,      8,      0,      0,      HI_PQ_MODULE_DB,        3},     //db_lum_h_str_fade_lut_p2
    {0x2128,        9,      11,     0,      0,      HI_PQ_MODULE_DB,        3},     //db_lum_h_str_fade_lut_p3
    {0x2128,        12,     14,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p4
    {0x2128,        15,     17,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p5
    {0x2128,        18,     20,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p6
    {0x2128,        21,     23,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p7
    {0x2128,        24,     26,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p8
    {0x2128,        27,     29,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p9
    /*vpss_db_lut3*/
    {0x212c,        0,      2,      0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p10
    {0x212c,        3,      5,      0,      0,      HI_PQ_MODULE_DB,        0},     //db_lum_h_str_fade_lut_p11
    /*vpss_db_lut4*/
    {0x2130,        0,      3,      0,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_gain_lut_p0
    {0x2130,        4,      7,      0,      0,      HI_PQ_MODULE_DB,        5},     //db_dir_str_gain_lut_p1
    {0x2130,        8,      11,     0,      0,      HI_PQ_MODULE_DB,        3},     //db_dir_str_gain_lut_p2
    {0x2130,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        1},     //db_dir_str_gain_lut_p3
    {0x2130,        16,     19,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p4
    {0x2130,        20,     23,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p5
    {0x2130,        24,     27,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p6
    {0x2130,        28,     31,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_gain_lut_p7
    /*vpss_db_lut5*/
    {0x2134,        0,      3,      0,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p0
    {0x2134,        4,      7,      0,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p1
    {0x2134,        8,      11,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p2
    {0x2134,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p3
    {0x2134,        16,     19,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p4
    {0x2134,        20,     23,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p5
    {0x2134,        24,     27,     0,      0,      HI_PQ_MODULE_DB,        8},     //db_dir_str_lut_p6
    {0x2134,        28,     31,     0,      0,      HI_PQ_MODULE_DB,        6},     //db_dir_str_lut_p7
    /*vpss_db_lut6*/
    {0x2138,        0,      3,      0,      0,      HI_PQ_MODULE_DB,        1},     //db_dir_str_lut_p8
    {0x2138,        4,      7,      0,      0,      HI_PQ_MODULE_DB,        1},     //db_dir_str_lut_p9
    {0x2138,        8,      11,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p10
    {0x2138,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p11
    {0x2138,        16,     19,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p12
    {0x2138,        20,     23,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p13
    {0x2138,        24,     27,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p14
    {0x2138,        28,     31,     0,      0,      HI_PQ_MODULE_DB,        0},     //db_dir_str_lut_p15
    /*vpss_dbd_thdedge*/
    {0x2150,        0,      5,      0,      0,      HI_PQ_MODULE_DB,        32},    //dbd_hy_thd_edge
    /*vpss_dbd_thdtxt*/
    {0x2154,        0,      5,      0,      0,      HI_PQ_MODULE_DB,        16},    //dbd_hy_thd_txt
    /*vpss_dbd_lutwgt0*/
    {0x2158,        0,      3,      0,      0,      HI_PQ_MODULE_DB,        0},     //dbd_det_lut_wgt0
    {0x2158,        4,      7,      0,      0,      HI_PQ_MODULE_DB,        0},     //dbd_det_lut_wgt1
    {0x2158,        8,      11,     0,      0,      HI_PQ_MODULE_DB,        1},     //dbd_det_lut_wgt2
    {0x2158,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        2},     //dbd_det_lut_wgt3
    {0x2158,        16,     19,     0,      0,      HI_PQ_MODULE_DB,        5},     //dbd_det_lut_wgt4
    {0x2158,        20,     23,     0,      0,      HI_PQ_MODULE_DB,        7},     //dbd_det_lut_wgt5
    {0x2158,        24,     27,     0,      0,      HI_PQ_MODULE_DB,        10},    //dbd_det_lut_wgt6
    {0x2158,        28,     31,     0,      0,      HI_PQ_MODULE_DB,        12},    //dbd_det_lut_wgt7
    /*vpss_dbd_lutwgt1*/
    {0x215c,        0,      3,      0,      0,      HI_PQ_MODULE_DB,        12},    //dbd_det_lut_wgt8
    {0x215c,        4,      7,      0,      0,      HI_PQ_MODULE_DB,        13},    //dbd_det_lut_wgt9
    {0x215c,        8,      11,     0,      0,      HI_PQ_MODULE_DB,        13},    //dbd_det_lut_wgt10
    {0x215c,        12,     15,     0,      0,      HI_PQ_MODULE_DB,        14},    //dbd_det_lut_wgt11
    {0x215c,        16,     19,     0,      0,      HI_PQ_MODULE_DB,        14},    //dbd_det_lut_wgt12
    {0x215c,        20,     23,     0,      0,      HI_PQ_MODULE_DB,        15},    //dbd_det_lut_wgt13
    {0x215c,        24,     27,     0,      0,      HI_PQ_MODULE_DB,        15},    //dbd_det_lut_wgt14
    {0x215c,        28,     31,     0,      0,      HI_PQ_MODULE_DB,        15},    //dbd_det_lut_wgt15
    /*vpss_dbd_rtnbdtxt*/
    {0x2160,        0,      4,      0,      0,      HI_PQ_MODULE_DB,        20},    //dbd_hy_rtn_bd_txt
    /*vpss_dbd_tstblknum*/
    {0x2164,        0,      9,      0,      0,      HI_PQ_MODULE_DB,        90},    //dbd_hy_tst_blk_num
    /*vpss_dbd_hyrdx8binlut0*/
    {0x2168,        0,      10,     0,      0,      HI_PQ_MODULE_DB,        16},    //dbd_hy_rdx8bin_lut0
    {0x2168,        12,     22,     0,      0,      HI_PQ_MODULE_DB,        48},    //dbd_hy_rdx8bin_lut1
    /*vpss_dbd_hyrdx8binlut1*/
    {0x216c,        0,      10,     0,      0,      HI_PQ_MODULE_DB,        80},    //dbd_hy_rdx8bin_lut2
    {0x216c,        12,     22,     0,      0,      HI_PQ_MODULE_DB,        112},   //dbd_hy_rdx8bin_lut3
    /*vpss_dbd_hyrdx8binlut2*/
    {0x2170,        0,      10,     0,      0,      HI_PQ_MODULE_DB,        144},   //dbd_hy_rdx8bin_lut4
    {0x2170,        12,     22,     0,      0,      HI_PQ_MODULE_DB,        176},   //dbd_hy_rdx8bin_lut5
    /*vpss_dbd_hyrdx8binlut3*/
    {0x2174,        0,      10,     0,      0,      HI_PQ_MODULE_DB,        208},   //dbd_hy_rdx8bin_lut6
    /*vpss_dbd_blksize*/
    {0x2178,        0,      5,      0,      0,      HI_PQ_MODULE_DB,        4},     //dbd_min_blk_size
    {0x2178,        8,      14,     0,      0,      HI_PQ_MODULE_DB,        16},    //dbd_hy_max_blk_size
    /*vpss_dbd_flat*/
    {0x217c,        0,      4,      0,      0,      HI_PQ_MODULE_DB,        20},    //dbd_thr_flat

    /***********************************************DM***********************************************/
    /*VPSS_DB_CTRL*/
    {0x2100,       1,      1,      0,      0,      HI_PQ_MODULE_DM,        1},     //dm_en
    /*VPSS_DM_DIR*/
    {0x2190,       16,     17,     0,      0,      HI_PQ_MODULE_DM,        2},     //dm_opp_ang_ctrst_div
    {0x2190,       8,      15,     0,      0,      HI_PQ_MODULE_DM,        18},    //dm_opp_ang_ctrst_t
    {0x2190,       6,      7,      0,      0,      HI_PQ_MODULE_DM,        2},     //dm_ctrst_thresh
    {0x2190,       0,      4,      0,      0,      HI_PQ_MODULE_DM,        24},    //dm_grad_sub_ratio
    /*VPSS_DM_EDGE*/
    {0x2194,       22,     25,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_global_str
    {0x2194,       1,      2,      0,      0,      HI_PQ_MODULE_DM,        1},     //dm_init_val_step
    {0x2194,       0,      0,      0,      0,      HI_PQ_MODULE_DM,        0},     //dm_mmf_set
    /*VPSS_DM_LUT0*/
    {0x2198,       24,     30,     0,      0,      HI_PQ_MODULE_DM,        32},    //dm_sw_wht_lut_p3
    {0x2198,       16,     22,     0,      0,      HI_PQ_MODULE_DM,        16},    //dm_sw_wht_lut_p2
    {0x2198,       8,      14,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_sw_wht_lut_p1
    {0x2198,       0,      6,      0,      0,      HI_PQ_MODULE_DM,        4},     //dm_sw_wht_lut_p0
    /*VPSS_DM_LUT1*/
    {0x219c,       16,     25,     0,      0,      HI_PQ_MODULE_DM,        32},    //dm_limit_t_10
    {0x219c,       8,      15,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_limit_t
    {0x219c,       0,      6,      0,      0,      HI_PQ_MODULE_DM,        64},    //dm_sw_wht_lut_p4
    /*VPSS_DM_LUT2*/
    {0x21a0,       28,     31,     0,      0,      HI_PQ_MODULE_DM,        5},     //dm_dir_str_gain_lut_p7
    {0x21a0,       24,     27,     0,      0,      HI_PQ_MODULE_DM,        6},     //dm_dir_str_gain_lut_p6
    {0x21a0,       20,     23,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_gain_lut_p5
    {0x21a0,       16,     19,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_gain_lut_p4
    {0x21a0,       12,     15,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_gain_lut_p3
    {0x21a0,       8,      11,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_gain_lut_p2
    {0x21a0,       4,      7,      0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_gain_lut_p1
    {0x21a0,       0,      3,      0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_gain_lut_p0
    /*VPSS_DM_LUT3*/
    {0x21a4,       28,     31,     0,      0,      HI_PQ_MODULE_DM,        6},     //dm_dir_str_lut_p7
    {0x21a4,       24,     27,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_lut_p6
    {0x21a4,       20,     23,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_lut_p5
    {0x21a4,       16,     19,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_lut_p4
    {0x21a4,       12,     15,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_lut_p3
    {0x21a4,       8,      11,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_lut_p2
    {0x21a4,       4,      7,      0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_lut_p1
    {0x21a4,       0,      3,      0,      0,      HI_PQ_MODULE_DM,        8},     //dm_dir_str_lut_p0
    /*VPSS_DM_LUT4*/
    {0x21a8,       28,     31,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_dir_str_lut_p15
    {0x21a8,       24,     27,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_dir_str_lut_p14
    {0x21a8,       20,     23,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_dir_str_lut_p13
    {0x21a8,       16,     19,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_dir_str_lut_p12
    {0x21a8,       12,     15,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_dir_str_lut_p11
    {0x21a8,       8,      11,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_dir_str_lut_p10
    {0x21a8,       4,      7,      0,      0,      HI_PQ_MODULE_DM,        1},     //dm_dir_str_lut_p9
    {0x21a8,       0,      3,      0,      0,      HI_PQ_MODULE_DM,        1},     //dm_dir_str_lut_p8
    /*VPSS_DM_DIRC*/
    {0x21ac,       31,     31,     0,      0,      HI_PQ_MODULE_DM,        1},     //dm_mmf_limit_en
    {0x21ac,       18,     25,     0,      0,      HI_PQ_MODULE_DM,        15},    //dm_mndir_opp_ctrst_t
    /*VPSS_DM_DIRO*/
    {0x21b0,       22,     31,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_csw_trsnt_st_10
    /*VPSS_DM_LSW*/
    {0x21b4,       27,     29,     0,      0,      HI_PQ_MODULE_DM,        4},     //dm_lsw_ratio
    {0x21b4,       18,     25,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_csw_trsnt_st
    {0x21b4,       8,      17,     0,      0,      HI_PQ_MODULE_DM,        120},   //dm_lw_ctrst_t_10
    {0x21b4,       0,      7,      0,      0,      HI_PQ_MODULE_DM,        30},    //dm_lw_ctrst_t
    /*VPSS_DM_MMFLR*/
    {0x21b8,       20,     27,     0,      0,      HI_PQ_MODULE_DM,        35},    //dm_csw_trsnt_lt
    {0x21b8,       9,      19,     0,      0,      HI_PQ_MODULE_DM,        80},    //dm_mmf_lr_10
    {0x21b8,       0,      8,      0,      0,      HI_PQ_MODULE_DM,        20},    //dm_mmf_lr
    /*VPSS_DM_MMFSR*/
    {0x21bc,       20,     29,     0,      0,      HI_PQ_MODULE_DM,        140},   //dm_csw_trsnt_lt_10
    {0x21bc,       9,      19,     0,      0,      HI_PQ_MODULE_DM,        0},     //dm_mmf_sr_10
    {0x21bc,       0,      8,      0,      0,      HI_PQ_MODULE_DM,        0},     //dm_mmf_sr
    /*VPSS_DM_THR0*/
    {0x21c0,       12,     15,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_dir_blend_str
    {0x21c0,       8,      11,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_lim_res_blend_str2
    {0x21c0,       4,      7,      0,      0,      HI_PQ_MODULE_DM,        7},     //dm_lim_res_blend_str1
    {0x21c0,       0,      2,      0,      0,      HI_PQ_MODULE_DM,        4},     //dm_limit_lsw_ratio
    /*VPSS_DM_LUT5*/
    {0x21c4,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        4},     //dm_trans_band_lut_p4
    {0x21c4,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        3},     //dm_trans_band_lut_p3
    {0x21c4,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        2},     //dm_trans_band_lut_p2
    {0x21c4,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        1},     //dm_trans_band_lut_p1
    {0x21c4,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        0},     //dm_trans_band_lut_p0
    /*VPSS_DM_LUT6*/
    {0x21c8,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        9},     //dm_trans_band_lut_p9
    {0x21c8,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        8},     //dm_trans_band_lut_p8
    {0x21c8,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        7},     //dm_trans_band_lut_p7
    {0x21c8,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        6},     //dm_trans_band_lut_p6
    {0x21c8,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        5},     //dm_trans_band_lut_p5
    /*VPSS_DM_LUT7*/
    {0x21cc,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        14},    //dm_trans_band_lut_p14
    {0x21cc,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        13},    //dm_trans_band_lut_p13
    {0x21cc,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        12},    //dm_trans_band_lut_p12
    {0x21cc,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        11},    //dm_trans_band_lut_p11
    {0x21cc,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        10},    //dm_trans_band_lut_p10
    /*VPSS_DM_LUT8*/
    {0x21d0,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        19},    //dm_trans_band_lut_p19
    {0x21d0,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        18},    //dm_trans_band_lut_p18
    {0x21d0,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        17},    //dm_trans_band_lut_p17
    {0x21d0,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        16},    //dm_trans_band_lut_p16
    {0x21d0,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        15},    //dm_trans_band_lut_p15
    /*VPSS_DM_LUT9*/
    {0x21d4,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        24},    //dm_trans_band_lut_p24
    {0x21d4,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        23},    //dm_trans_band_lut_p23
    {0x21d4,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        22},    //dm_trans_band_lut_p22
    {0x21d4,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        21},    //dm_trans_band_lut_p21
    {0x21d4,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        20},    //dm_trans_band_lut_p20
    /*VPSS_DM_LUT10*/
    {0x21d8,       24,     29,     0,      0,      HI_PQ_MODULE_DM,        29},    //dm_trans_band_lut_p29
    {0x21d8,       18,     23,     0,      0,      HI_PQ_MODULE_DM,        28},    //dm_trans_band_lut_p28
    {0x21d8,       12,     17,     0,      0,      HI_PQ_MODULE_DM,        27},    //dm_trans_band_lut_p27
    {0x21d8,       6,      11,     0,      0,      HI_PQ_MODULE_DM,        26},    //dm_trans_band_lut_p26
    {0x21d8,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        25},    //dm_trans_band_lut_p25
    /*VPSS_DM_LUT11*/
    {0x21dc,       0,      5,      0,      0,      HI_PQ_MODULE_DM,        30},    //dm_trans_band_lut_p30

    /***********************************************SNR***********************************************/
    /*VPSS_SNR_CTRL*/
    //{0x2100,        16,     18,     0,      0,      HI_PQ_MODULE_SNR,       3},     //dbm_out_mode
    /*{0x2100,        14,     15,     0,      0,      HI_PQ_MODULE_SNR,       0},     //mad_mode*/
    {0x2100,        2,      2,      0,      0,      HI_PQ_MODULE_SNR,       1},     //snr_en
    /*VPSS_SNR_ENABLE*/
    {0x2300,        7,      7,      0,      0,      HI_PQ_MODULE_SNR,       0},     //test_en
    {0x2300,        5,      5,      0,      0,      HI_PQ_MODULE_SNR,       1},     //edgeprefilteren
    {0x2300,        4,      4,      0,      0,      HI_PQ_MODULE_SNR,       0},     //colorweighten
    {0x2300,        3,      3,      0,      0,      HI_PQ_MODULE_SNR,       1},     //motionedgeweighten
    {0x2300,        2,      2,      0,      0,      HI_PQ_MODULE_SNR,       0},     //cnr2den
    {0x2300,        1,      1,      0,      0,      HI_PQ_MODULE_SNR,       1},     //ynr2den
    /*vpss_snr_edge_ratiorange*/
    {0x2304,        8,      11,     0,      0,      HI_PQ_MODULE_SNR,       15},    //edgeoriratio
    {0x2304,        4,      7,      0,      0,      HI_PQ_MODULE_SNR,       1},     //edgeminratio
    {0x2304,        0,      3,      0,      0,      HI_PQ_MODULE_SNR,       15},    //edgemaxratio
    /*vpss_snr_edge_strrange*/
    {0x2308,        8,      11,     0,      0,      HI_PQ_MODULE_SNR,       0},     //edgeoristrength
    {0x2308,        4,      7,      0,      0,      HI_PQ_MODULE_SNR,       0},     //edgeminstrength
    {0x2308,        0,      3,      0,      0,      HI_PQ_MODULE_SNR,       15},    //edgemaxstrength
    /*VPSS_SNR_WIN*/
    {0x2328,        13,     14,     0,      0,      HI_PQ_MODULE_SNR,       3},     //c2dwinheight
    {0x2328,        9,      12,     0,      0,      HI_PQ_MODULE_SNR,       5},     //c2dwinwidth
    {0x2328,        5,      8,      0,      0,      HI_PQ_MODULE_SNR,       5},     //y2dwinheight
    {0x2328,        0,      4,      0,      0,      HI_PQ_MODULE_SNR,       9},     //y2dwinwidth
    /*VPSS_SNR_STR*/
    {0x232c,        8,      15,     0,      0,      HI_PQ_MODULE_SNR,       24},    //csnrstr
    {0x232c,        0,      7,      0,      0,      HI_PQ_MODULE_SNR,       24},    //ysnrstr
    /*VPSS_SNR_STR_OFFSET*/
    {0x2330,        6,      7,      0,      0,      HI_PQ_MODULE_SNR,       3},     //stroffset3
    {0x2330,        4,      5,      0,      0,      HI_PQ_MODULE_SNR,       2},     //stroffset2
    {0x2330,        2,      3,      0,      0,      HI_PQ_MODULE_SNR,       1},     //stroffset1
    {0x2330,        0,      1,      0,      0,      HI_PQ_MODULE_SNR,       0},     //stroffset0
    /*VPSS_SNR_STR_ADJUST*/
    {0x2334,        6,      11,     0,      0,      HI_PQ_MODULE_SNR,       16},    //cstradjust
    {0x2334,        0,      5,      0,      0,      HI_PQ_MODULE_SNR,       16},    //ystradjust
    /*VPSS_SNR_SCHANGE_TH*/
    {0x2338,        0,      3,      0,      0,      HI_PQ_MODULE_SNR,       3},     //scenechangeth
    /*VPSS_SNR_TEST_COLOR*/
    {0x234c,        10,     19,     0,      0,      HI_PQ_MODULE_SNR,       512},   //test_color_cr
    {0x234c,        0,      9,      0,      0,      HI_PQ_MODULE_SNR,       512},   //test_color_cb
    /*VPSS_SNR_SCHANGE*/
    {0x2350,        30,     30,     0,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_mode2_en
    {0x2350,        20,     29,     0,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_bldcore
    {0x2350,        10,     19,     0,      0,      HI_PQ_MODULE_SNR,       96},    //scenechange_bldk
    {0x2350,        9,       9,     0,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_mode1_en
    {0x2350,        8,       8,     0,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_en
    {0x2350,        0,      7,      0,      0,      HI_PQ_MODULE_SNR,       0},     //scenechange_info
    /*VPSS_SNR_MT*/
    {0x2354,        0,      5,      0,      0,      HI_PQ_MODULE_SNR,       8},    //motionalpha
    /*VPSS_SNR_CBCR_W1*/
    {0x2358,        24,     27,     0,      0,      HI_PQ_MODULE_SNR,       15},    //cbcr_weight1
    {0x2358,        18,     23,     0,      0,      HI_PQ_MODULE_SNR,       0},     //cr_end1
    {0x2358,        12,     17,     0,      0,      HI_PQ_MODULE_SNR,       0},     //cb_end1
    {0x2358,        6,      11,     0,      0,      HI_PQ_MODULE_SNR,       0},     //cr_begin1
    {0x2358,        0,      5,      0,      0,      HI_PQ_MODULE_SNR,       0},     //cb_begin1
    /*VPSS_SNR_CBCR_W2*/
    {0x235c,        24,     27,     0,      0,      HI_PQ_MODULE_SNR,       15},    //cbcr_weight2
    {0x235c,        18,     23,     0,      0,      HI_PQ_MODULE_SNR,       0},     //cr_end2
    {0x235c,        12,     17,     0,      0,      HI_PQ_MODULE_SNR,       0},     //cb_end2
    {0x235c,        6,      11,     0,      0,      HI_PQ_MODULE_SNR,       0},     //cr_begin2
    {0x235c,        0,      5,      0,      0,      HI_PQ_MODULE_SNR,       0},     //cb_begin2

    /*************************************TNR****************************************/
    /*SD*/
    /*vpss_tnr_contrl*/
    {0x3800,        7,      19,     1,      0,      HI_PQ_MODULE_TNR,       0},     //marketcoor
    {0x3800,        6,      6,      1,      0,      HI_PQ_MODULE_TNR,       0},     //marketmode
    {0x3800,        5,      5,      1,      0,      HI_PQ_MODULE_TNR,       0},     //marketmodeen
    {0x3800,        2,      2,      1,      0,      HI_PQ_MODULE_TNR,       1},     //cnren
    {0x3800,        1,      1,      1,      0,      HI_PQ_MODULE_TNR,       1},     //ynren
    {0x3800,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //nren
    /*vpss_tnr_mamd_ctrl*/
    {0x3804,        20,     22,     1,      0,      HI_PQ_MODULE_TNR,       0},     //alpha2
    {0x3804,        17,     19,     1,      0,      HI_PQ_MODULE_TNR,       0},     //alpha1
    {0x3804,        15,     16,     1,      0,      HI_PQ_MODULE_TNR,       2},     //cmotionlpfmode
    {0x3804,        13,     14,     1,      0,      HI_PQ_MODULE_TNR,       2},     //ymotionlpfmode
    {0x3804,        11,     12,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cmotioncalcmode
    {0x3804,        9,      10,     1,      0,      HI_PQ_MODULE_TNR,       0},     //ymotioncalcmode
    {0x3804,        6,      8,      1,      0,      HI_PQ_MODULE_TNR,       4},     //meancadjshift
    {0x3804,        3,      5,      1,      0,      HI_PQ_MODULE_TNR,       4},     //meanyadjshift
    {0x3804,        2,      2,      1,      0,      HI_PQ_MODULE_TNR,       0},     //mean_cmotion_adj_en
    {0x3804,        1,      1,      1,      0,      HI_PQ_MODULE_TNR,       0},     //mean_ymotion_adj_en
    {0x3804,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //mdprelpfen
    /*vpss_tnr_mamd_gain*/
    {0x3808,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cmdcore
    {0x3808,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       15},    //cmdgain
    {0x3808,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       0},     //ymdcore
    {0x3808,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       15},    //ymdgain
    /*vpss_tnr_mand_ctrl*/
    {0x380c,        9,      10,     1,      0,      HI_PQ_MODULE_TNR,       3},     //randomctrlmode
    {0x380c,        1,      8,      1,      0,      HI_PQ_MODULE_TNR,       32},    //blkdiffthd
    {0x380c,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //noisedetecten
    /*vpss_tnr_mand_thd*/
    {0x3810,        16,     23,     1,      0,      HI_PQ_MODULE_TNR,       32},    //flatthdmax
    {0x3810,        8,      15,     1,      0,      HI_PQ_MODULE_TNR,       20},    //flatthdmed
    {0x3810,        0,      7,      1,      0,      HI_PQ_MODULE_TNR,       12},    //flatthdmin
    /*vpss_tnr_mame_ctrl*/
    {0x3814,        13,     15,     1,      0,      HI_PQ_MODULE_TNR,       4},     //smvythd
    {0x3814,        10,     12,     1,      0,      HI_PQ_MODULE_TNR,       4},     //smvxthd
    {0x3814,        9,      9,      1,      0,      HI_PQ_MODULE_TNR,       0},     //discardsmvyen
    {0x3814,        8,      8,      1,      0,      HI_PQ_MODULE_TNR,       0},     //discardsmvxen
    {0x3814,        5,      7,      1,      0,      HI_PQ_MODULE_TNR,       0},     //gm_adj
    {0x3814,        3,      4,      1,      0,      HI_PQ_MODULE_TNR,       2},     //mvlpfmode
    {0x3814,        1,      2,      1,      0,      HI_PQ_MODULE_TNR,       0},     //mvrefmode
    {0x3814,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //motionestimateen
    /*vpss_tnr_mame_gain*/
    {0x3818,        24,     31,     1,      0,      HI_PQ_MODULE_TNR,       63},    //mag_pnl_core_xmv
    {0x3818,        16,     23,     1,      0,      HI_PQ_MODULE_TNR,       127},   //mag_pnl_gain_xmv
    {0x3818,        8,      15,     1,      0,      HI_PQ_MODULE_TNR,       63},    //mag_pnl_core_0mv
    {0x3818,        0,      7,      1,      0,      HI_PQ_MODULE_TNR,       127},   //mag_pnl_gain_0mv
    /*vpss_tnr_mame_std_core*/
    {0x381c,        25,     29,     1,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_core_xmv
    {0x381c,        20,     24,     1,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_gain_xmv
    {0x381c,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_core_0mv
    {0x381c,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_gain_0mv
    {0x381c,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       0},     //std_core_xmv
    {0x381c,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       28},    //std_core_0mv
    /*vpss_tnr_mame_std_gain*/
    {0x3820,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       0},     //std_pnl_core
    {0x3820,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       31},    //std_pnl_gain
    /*vpss_tnr_mame_mv_thd*/
    {0x3824,        25,     29,     1,      0,      HI_PQ_MODULE_TNR,       16},    //adj_xmv_max
    {0x3824,        20,     24,     1,      0,      HI_PQ_MODULE_TNR,       16},    //adj_0mv_max
    {0x3824,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       4},     //adj_xmv_min
    {0x3824,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       4},     //adj_0mv_min
    {0x3824,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       10},    //adj_mv_min
    {0x3824,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       24},    //adj_mv_max
    /*vpss_tnr_mamc_cbcr_upen*/
    {0x3828,        5,      8,      1,      0,      HI_PQ_MODULE_TNR,       15},    //cbcrweight2
    {0x3828,        1,      4,      1,      0,      HI_PQ_MODULE_TNR,       15},    //cbcrweight1
    {0x3828,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cbcrupdateen
    /*vpss_tnr_mamc_cbcr_upthd1*/
    {0x382c,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       0},     //crend1
    {0x382c,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cbend1
    {0x382c,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       0},     //crbegin1
    {0x382c,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cbbegin1
    /*vpss_tnr_mamc_cbcr_upthd2*/
    {0x3830,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       0},     //crend2
    {0x3830,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cbend2
    {0x3830,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       0},     //crbegin2
    {0x3830,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cbbegin2
    /*vpss_tnr_mamc_pre_mad*/
    {0x3834,        6,      10,     1,      0,      HI_PQ_MODULE_TNR,       20},    //motionmergeratio
    {0x3834,        1,      5,      1,      0,      HI_PQ_MODULE_TNR,       12},    //premotionalpha
    {0x3834,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //premotionmergemode
    /*vpss_tnr_mamc_map*/
    {0x3838,        17,     22,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cmotioncore
    {0x3838,        12,     16,     1,      0,      HI_PQ_MODULE_TNR,       24},    //cmotiongain
    {0x3838,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       0},     //ymotioncore
    {0x3838,        1,      5,      1,      0,      HI_PQ_MODULE_TNR,       24},    //ymotiongain
    {0x3838,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       0},     //motionmappingen
    /*vpss_tnr_mamc_saltus*/
    {0x383c,        1,      5,      1,      0,      HI_PQ_MODULE_TNR,       0},     //saltuslevel
    {0x383c,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //saltusdecten
    /*vpss_tnr_mamc_mcadj*/
    {0x3840,        4,      5,      1,      0,      HI_PQ_MODULE_TNR,       3},     //cmclpfmode
    {0x3840,        2,      3,      1,      0,      HI_PQ_MODULE_TNR,       3},     //ymclpfmode
    {0x3840,        1,      1,      1,      0,      HI_PQ_MODULE_TNR,       1},     //cmcadjen
    {0x3840,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //ymcadjen
    /*vpss_tnr_filr_mode*/
    {0x3844,        7,      11,     1,      0,      HI_PQ_MODULE_TNR,       2},     //cnonrrange
    {0x3844,        2,      6,      1,      0,      HI_PQ_MODULE_TNR,       2},     //ynonrrange
    {0x3844,        1,      1,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cmotionmode
    {0x3844,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       1},     //ymotionmode
    /*vpss_tnr_scene_change*/
    {0x3848,        1,      8,      1,      0,      HI_PQ_MODULE_TNR,       0},     //scenechangeinfo
    {0x3848,        0,      0,      1,      0,      HI_PQ_MODULE_TNR,       0},     //scenechangeen
    /*vpss_tnr_cfg*/
    {0x384c,        17,     21,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cfg_cmdcore
    {0x384c,        11,     16,     1,      0,      HI_PQ_MODULE_TNR,       15},    //cfg_cmdgain
    {0x384c,        6,      10,     1,      0,      HI_PQ_MODULE_TNR,       0},     //cfg_ymdcore
    {0x384c,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       15},    //cfg_ymdgain
    /*vpss_tnr_flat_info*/
    {0x3850,        24,     31,     1,      0,      HI_PQ_MODULE_TNR,       0},     //flatinfoymax
    {0x3850,        16,     23,     1,      0,      HI_PQ_MODULE_TNR,       56},    //flatinfoxmax
    {0x3850,        8,      15,     1,      0,      HI_PQ_MODULE_TNR,       0},     //flatinfoymin
    {0x3850,        0,      7,      1,      0,      HI_PQ_MODULE_TNR,       64},    //flatinfoxmin
    /*vpss_tnr_yblend*/
    {0x3854,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       31},    //yblendingymax
    {0x3854,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       12},     //yblendingxmax
    {0x3854,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       16},    //yblendingymin
    {0x3854,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       0},     //yblendingxmin
    /*vpss_tnr_cblend*/
    {0x3858,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       31},    //cblendingymax
    {0x3858,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       12},     //cblendingxmax
    {0x3858,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       16},    //cblendingymin
    {0x3858,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       0},     //cblendingxmin
    /*vpss_tnr_dtblend*/
    {0x385c,        15,     19,     1,      0,      HI_PQ_MODULE_TNR,       31},    //dtblendingymax
    {0x385c,        10,     14,     1,      0,      HI_PQ_MODULE_TNR,       15},    //dtblendingxmax
    {0x385c,        5,      9,      1,      0,      HI_PQ_MODULE_TNR,       12},    //dtblendingymin
    {0x385c,        0,      4,      1,      0,      HI_PQ_MODULE_TNR,       1},     //dtblendingxmin
    /*vpss_tnr_mean_motion_lut0*/
    {0x3900,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio3
    {0x3900,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio2
    {0x3900,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio1
    {0x3900,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio0
    /*vpss_tnr_mean_motion_lut1*/
    {0x3904,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio7
    {0x3904,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio6
    {0x3904,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio5
    {0x3904,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio4
    /*vpss_tnr_mean_motion_lut2*/
    {0x3908,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio11
    {0x3908,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio10
    {0x3908,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio9
    {0x3908,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio8
    /*vpss_tnr_mean_motion_lut3*/
    {0x390c,        18,     23,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio15
    {0x390c,        12,     17,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio14
    {0x390c,        6,      11,     1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio13
    {0x390c,        0,      5,      1,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio12

    /*HD*/
    /*vpss_tnr_contrl*/
    {0x3800,        7,      19,     2,      0,      HI_PQ_MODULE_TNR,       0},     //marketcoor
    {0x3800,        6,      6,      2,      0,      HI_PQ_MODULE_TNR,       0},     //marketmode
    {0x3800,        5,      5,      2,      0,      HI_PQ_MODULE_TNR,       0},     //marketmodeen
    {0x3800,        2,      2,      2,      0,      HI_PQ_MODULE_TNR,       1},     //cnren
    {0x3800,        1,      1,      2,      0,      HI_PQ_MODULE_TNR,       1},     //ynren
    {0x3800,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //nren
    /*vpss_tnr_mamd_ctrl*/
    {0x3804,        20,     22,     2,      0,      HI_PQ_MODULE_TNR,       0},     //alpha2
    {0x3804,        17,     19,     2,      0,      HI_PQ_MODULE_TNR,       0},     //alpha1
    {0x3804,        15,     16,     2,      0,      HI_PQ_MODULE_TNR,       2},     //cmotionlpfmode
    {0x3804,        13,     14,     2,      0,      HI_PQ_MODULE_TNR,       2},     //ymotionlpfmode
    {0x3804,        11,     12,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cmotioncalcmode
    {0x3804,        9,      10,     2,      0,      HI_PQ_MODULE_TNR,       0},     //ymotioncalcmode
    {0x3804,        6,      8,      2,      0,      HI_PQ_MODULE_TNR,       4},     //meancadjshift
    {0x3804,        3,      5,      2,      0,      HI_PQ_MODULE_TNR,       4},     //meanyadjshift
    {0x3804,        2,      2,      2,      0,      HI_PQ_MODULE_TNR,       0},     //mean_cmotion_adj_en
    {0x3804,        1,      1,      2,      0,      HI_PQ_MODULE_TNR,       0},     //mean_ymotion_adj_en
    {0x3804,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //mdprelpfen
    /*vpss_tnr_mamd_gain*/
    {0x3808,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cmdcore
    {0x3808,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       24},    //cmdgain
    {0x3808,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       0},     //ymdcore
    {0x3808,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       24},    //ymdgain
    /*vpss_tnr_mand_ctrl*/
    {0x380c,        9,      10,     2,      0,      HI_PQ_MODULE_TNR,       3},     //randomctrlmode
    {0x380c,        1,      8,      2,      0,      HI_PQ_MODULE_TNR,       64},    //blkdiffthd
    {0x380c,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //noisedetecten
    /*vpss_tnr_mand_thd*/
    {0x3810,        16,     23,     2,      0,      HI_PQ_MODULE_TNR,       35},    //flatthdmax
    {0x3810,        8,      15,     2,      0,      HI_PQ_MODULE_TNR,       24},    //flatthdmed
    {0x3810,        0,      7,      2,      0,      HI_PQ_MODULE_TNR,       12},    //flatthdmin
    /*vpss_tnr_mame_ctrl*/
    {0x3814,        13,     15,     2,      0,      HI_PQ_MODULE_TNR,       0},     //smvythd
    {0x3814,        10,     12,     2,      0,      HI_PQ_MODULE_TNR,       0},     //smvxthd
    {0x3814,        9,      9,      2,      0,      HI_PQ_MODULE_TNR,       0},     //discardsmvyen
    {0x3814,        8,      8,      2,      0,      HI_PQ_MODULE_TNR,       0},     //discardsmvxen
    {0x3814,        5,      7,      2,      0,      HI_PQ_MODULE_TNR,       0},     //gm_adj
    {0x3814,        3,      4,      2,      0,      HI_PQ_MODULE_TNR,       2},     //mvlpfmode
    {0x3814,        1,      2,      2,      0,      HI_PQ_MODULE_TNR,       0},     //mvrefmode
    {0x3814,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //motionestimateen
    /*vpss_tnr_mame_gain*/
    {0x3818,        24,     31,     2,      0,      HI_PQ_MODULE_TNR,       0},   //mag_pnl_core_xmv
    {0x3818,        16,     23,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mag_pnl_gain_xmv
    {0x3818,        8,      15,     2,      0,      HI_PQ_MODULE_TNR,       0},   //mag_pnl_core_0mv
    {0x3818,        0,      7,      2,      0,      HI_PQ_MODULE_TNR,       16},    //mag_pnl_gain_0mv
    /*vpss_tnr_mame_std_core*/
    {0x381c,        25,     29,     2,      0,      HI_PQ_MODULE_TNR,       0},    //std_pnl_core_xmv
    {0x381c,        20,     24,     2,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_gain_xmv
    {0x381c,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       0},    //std_pnl_core_0mv
    {0x381c,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       16},    //std_pnl_gain_0mv
    {0x381c,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       0},     //std_core_xmv
    {0x381c,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       0},    //std_core_0mv
    /*vpss_tnr_mame_std_gain*/
    {0x3820,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       0},     //std_pnl_core
    {0x3820,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       31},    //std_pnl_gain
    /*vpss_tnr_mame_mv_thd*/
    {0x3824,        25,     29,     2,      0,      HI_PQ_MODULE_TNR,       16},    //adj_xmv_max
    {0x3824,        20,     24,     2,      0,      HI_PQ_MODULE_TNR,       16},    //adj_0mv_max
    {0x3824,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       16},     //adj_xmv_min
    {0x3824,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       16},     //adj_0mv_min
    {0x3824,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       10},    //adj_mv_min
    {0x3824,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       24},    //adj_mv_max
    /*vpss_tnr_mamc_cbcr_upen*/
    {0x3828,        5,      8,      2,      0,      HI_PQ_MODULE_TNR,       15},    //cbcrweight2
    {0x3828,        1,      4,      2,      0,      HI_PQ_MODULE_TNR,       15},    //cbcrweight1
    {0x3828,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cbcrupdateen
    /*vpss_tnr_mamc_cbcr_upthd1*/
    {0x382c,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       0},     //crend1
    {0x382c,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cbend1
    {0x382c,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       0},     //crbegin1
    {0x382c,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cbbegin1
    /*vpss_tnr_mamc_cbcr_upthd2*/
    {0x3830,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       0},     //crend2
    {0x3830,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cbend2
    {0x3830,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       0},     //crbegin2
    {0x3830,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cbbegin2
    /*vpss_tnr_mamc_pre_mad*/
    {0x3834,        6,      10,     2,      0,      HI_PQ_MODULE_TNR,       16},    //motionmergeratio
    {0x3834,        1,      5,      2,      0,      HI_PQ_MODULE_TNR,       18},    //premotionalpha
    {0x3834,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //premotionmergemode
    /*vpss_tnr_mamc_map*/
    {0x3838,        17,     22,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cmotioncore
    {0x3838,        12,     16,     2,      0,      HI_PQ_MODULE_TNR,       16},    //cmotiongain
    {0x3838,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       0},     //ymotioncore
    {0x3838,        1,      5,      2,      0,      HI_PQ_MODULE_TNR,       16},    //ymotiongain
    {0x3838,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //motionmappingen
    /*vpss_tnr_mamc_saltus*/
    {0x383c,        1,      5,      2,      0,      HI_PQ_MODULE_TNR,       0},     //saltuslevel
    {0x383c,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //saltusdecten
    /*vpss_tnr_mamc_mcadj*/
    {0x3840,        4,      5,      2,      0,      HI_PQ_MODULE_TNR,       3},     //cmclpfmode
    {0x3840,        2,      3,      2,      0,      HI_PQ_MODULE_TNR,       3},     //ymclpfmode
    {0x3840,        1,      1,      2,      0,      HI_PQ_MODULE_TNR,       1},     //cmcadjen
    {0x3840,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       1},     //ymcadjen
    /*vpss_tnr_filr_mode*/
    {0x3844,        7,      11,     2,      0,      HI_PQ_MODULE_TNR,       2},     //cnonrrange
    {0x3844,        2,      6,      2,      0,      HI_PQ_MODULE_TNR,       2},     //ynonrrange
    {0x3844,        1,      1,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cmotionmode
    {0x3844,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //ymotionmode
    /*vpss_tnr_scene_change*/
    {0x3848,        1,      8,      2,      0,      HI_PQ_MODULE_TNR,       0},     //scenechangeinfo
    {0x3848,        0,      0,      2,      0,      HI_PQ_MODULE_TNR,       0},     //scenechangeen
    /*vpss_tnr_cfg*/
    {0x384c,        17,     21,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cfg_cmdcore
    {0x384c,        11,     16,     2,      0,      HI_PQ_MODULE_TNR,       15},    //cfg_cmdgain
    {0x384c,        6,      10,     2,      0,      HI_PQ_MODULE_TNR,       0},     //cfg_ymdcore
    {0x384c,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       15},    //cfg_ymdgain
    /*vpss_tnr_flat_info*/
    {0x3850,        24,     31,     2,      0,      HI_PQ_MODULE_TNR,       0},    //flatinfoymax
    {0x3850,        16,     23,     2,      0,      HI_PQ_MODULE_TNR,       56},    //flatinfoxmax
    {0x3850,        8,      15,     2,      0,      HI_PQ_MODULE_TNR,       0},     //flatinfoymin
    {0x3850,        0,      7,      2,      0,      HI_PQ_MODULE_TNR,       64},     //flatinfoxmin
    /*vpss_tnr_yblend*/
    {0x3854,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       31},    //yblendingymax
    {0x3854,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       12},     //yblendingxmax
    {0x3854,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       16},    //yblendingymin
    {0x3854,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       0},     //yblendingxmin
    /*vpss_tnr_cblend*/
    {0x3858,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       31},    //cblendingymax
    {0x3858,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       12},     //cblendingxmax
    {0x3858,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       16},    //cblendingymin
    {0x3858,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       0},     //cblendingxmin
    /*vpss_tnr_dtblend*/
    {0x385c,        15,     19,     2,      0,      HI_PQ_MODULE_TNR,       31},    //dtblendingymax
    {0x385c,        10,     14,     2,      0,      HI_PQ_MODULE_TNR,       15},    //dtblendingxmax
    {0x385c,        5,      9,      2,      0,      HI_PQ_MODULE_TNR,       12},     //dtblendingymin
    {0x385c,        0,      4,      2,      0,      HI_PQ_MODULE_TNR,       1},    //dtblendingxmin
    /*vpss_tnr_mean_motion_lut0*/
    {0x3900,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio3
    {0x3900,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio2
    {0x3900,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio1
    {0x3900,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio0
    /*vpss_tnr_mean_motion_lut1*/
    {0x3904,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio7
    {0x3904,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio6
    {0x3904,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio5
    {0x3904,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio4
    /*vpss_tnr_mean_motion_lut2*/
    {0x3908,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio11
    {0x3908,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio10
    {0x3908,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio9
    {0x3908,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio8
    /*vpss_tnr_mean_motion_lut3*/
    {0x390c,        18,     23,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio15
    {0x390c,        12,     17,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio14
    {0x390c,        6,      11,     2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio13
    {0x390c,        0,      5,      2,      0,      HI_PQ_MODULE_TNR,       16},    //mean_motion_ratio12

    {0x3808,        18,     23,     2,      4,      HI_PQ_MODULE_TNR,       3},     //cmdcore
    {0x3808,        12,     17,     2,      4,      HI_PQ_MODULE_TNR,       12},    //cmdgain
    {0x3808,        6,      11,     2,      4,      HI_PQ_MODULE_TNR,       3},     //ymdcore
    {0x3808,        0,      5,      2,      4,      HI_PQ_MODULE_TNR,       12},    //ymdgain
    {0x3808,        18,     23,     2,      5,      HI_PQ_MODULE_TNR,       0},     //cmdcore
    {0x3808,        12,     17,     2,      5,      HI_PQ_MODULE_TNR,       24},    //cmdgain
    {0x3808,        6,      11,     2,      5,      HI_PQ_MODULE_TNR,       0},     //ymdcore
    {0x3808,        0,      5,      2,      5,      HI_PQ_MODULE_TNR,       24},    //ymdgain

    /***********************************************LCHDR***********************************************/
    /*vpss_lchdr_ctrl*/
    {0x2400,        0,      0,      0,      0,      HI_PQ_MODULE_LCHDR,       0},     //lchdr_en
    {0x2400,        1,      1,      0,      0,      HI_PQ_MODULE_LCHDR,       1},     //lchdr_tmen
    {0x2400,        2,      2,      0,      0,      HI_PQ_MODULE_LCHDR,       1},     //lchdr_dithen
    {0x2400,        3,      3,      0,      0,      HI_PQ_MODULE_LCHDR,       1},     //lchdr_satmapyen
    {0x2400,        4,      4,      0,      0,      HI_PQ_MODULE_LCHDR,       1},     //lchdr_cscen
    {0x2400,        5,      5,      0,      0,      HI_PQ_MODULE_LCHDR,       0},     //lchdr_fullorlimt
    /*vpss_lchdr_csc_coef0*/
    {0x2404,        0,      15,     0,      0,      HI_PQ_MODULE_LCHDR,       0},     //lchdr_csc_coef12
    {0x2404,        16,     31,     0,      0,      HI_PQ_MODULE_LCHDR,       5461},  //lchdr_csc_coef11
    /*vpss_lchdr_csc_coef1*/
    {0x2408,        0,      15,     0,      0,      HI_PQ_MODULE_LCHDR,       8192},  //lchdr_csc_coef22
    {0x2408,        16,     31,     0,      0,      HI_PQ_MODULE_LCHDR,       0},     //lchdr_csc_coef21
    /*vpss_lchdr_scale2p*/
    {0x240c,        0,      3,      0,      0,      HI_PQ_MODULE_LCHDR,       8},     //lchdr_satsclcoef
    {0x240c,        4,      7,      0,      0,      HI_PQ_MODULE_LCHDR,       13},    //lchdr_csc_scale
    /*vpss_lchdr_tmap_step*/
    {0x2410,        0,      3,      0,      0,      HI_PQ_MODULE_LCHDR,       1},     //gmm_x4_step
    {0x2410,        4,      7,      0,      0,      HI_PQ_MODULE_LCHDR,       4},     //gmm_x3_step
    {0x2410,        8,      11,     0,      0,      HI_PQ_MODULE_LCHDR,       3},     //gmm_x2_step
    {0x2410,        12,     15,     0,      0,      HI_PQ_MODULE_LCHDR,       6},     //gmm_x1_step
    /*vpss_lchdr_tmap_num*/
    {0x2414,        0,      5,      0,      0,      HI_PQ_MODULE_LCHDR,       6},     //gmm_x4_num
    {0x2414,        8,      13,     0,      0,      HI_PQ_MODULE_LCHDR,       52},    //gmm_x3_num
    {0x2414,        16,     21,     0,      0,      HI_PQ_MODULE_LCHDR,       4},     //gmm_x2_num
    {0x2414,        24,     29,     0,      0,      HI_PQ_MODULE_LCHDR,       1},     //gmm_x1_num
    /*vpss_lchdr_tmap_pos0*/
    {0x2418,        0,      9,      0,      0,      HI_PQ_MODULE_LCHDR,       96},    //gmm_x2_pos
    {0x2418,        16,     25,     0,      0,      HI_PQ_MODULE_LCHDR,       64},    //gmm_x1_pos
    /*vpss_lchdr_tmap_pos1*/
    {0x241c,        0,      9,      0,      0,      HI_PQ_MODULE_LCHDR,       940},   //gmm_x4_pos
    {0x241c,        16,     25,     0,      0,      HI_PQ_MODULE_LCHDR,       928},   //gmm_x3_pos
    /*vpss_lchdr_dither_func*/
    {0x2420,        0,      0,      0,      0,      HI_PQ_MODULE_LCHDR,       0},     //lchdr_dither_round
    {0x2420,        1,      1,      0,      0,      HI_PQ_MODULE_LCHDR,       0},     //lchdr_dither_domain_mode
    {0x2420,        2,      3,      0,      0,      HI_PQ_MODULE_LCHDR,       0},     //lchdr_dither_tap_mode
    {0x2420,        4,      4,      0,      0,      HI_PQ_MODULE_LCHDR,       0},     //lchdr_dither_round_unlim
    /*vpss_lchdr_dither_thr*/
    {0x2424,        0,      15,     0,      0,      HI_PQ_MODULE_LCHDR,       65535}, //lchdr_dither_thr_max
    {0x2424,        16,     31,     0,      0,      HI_PQ_MODULE_LCHDR,       0},     //lchdr_dither_thr_min

    /***********************************************ACC***********************************************/
    /*VHDACCTHD1*/
    {0x7200,        31,     31,     0,      0,      HI_PQ_MODULE_DCI,       1},     //acc_en
    {0x7200,        30,     30,     0,      0,      HI_PQ_MODULE_DCI,       0},     //acc_mode
    {0x7200,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       280},   //thd_med_low
    {0x7200,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       620},   //thd_high
    {0x7200,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       400},   //thd_low
    /*VHDACCTHD2*/
    {0x7204,        13,     13,     0,      0,      HI_PQ_MODULE_DCI,       0},     //ck_gt_en
    {0x7204,        12,     12,     0,      0,      HI_PQ_MODULE_DCI,       0},     //acc_rst
    {0x7204,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       740},   //thd_med_high
    /*VHDACCDEMO*/
    {0x7208,        4,      15,     0,      0,      HI_PQ_MODULE_DCI,       0},     //demo_split_point
    {0x7208,        1,      1,      0,      0,      HI_PQ_MODULE_DCI,       0},     //demo_mode
    {0x7208,        0,      0,      0,      0,      HI_PQ_MODULE_DCI,       0},     //demo_en
    /*VHDACCLOWN*/
    {0x720c,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       286},   //low_table_data2
    {0x720c,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       146},   //low_table_data1
    {0x720c,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       0},     //low_table_data0
    /*VHDACCLOWN*/
    {0x7210,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       670},   //low_table_data5
    {0x7210,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       550},   //low_table_data4
    {0x7210,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       426},   //low_table_data3
    /*VHDACCLOWN*/
    {0x7214,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       1023},  //low_table_data8
    {0x7214,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       896},   //low_table_data7
    {0x7214,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       768},   //low_table_data6
    /*VHDACCMEDN*/
    {0x7218,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       240},   //mid_table_data2
    {0x7218,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       110},   //mid_table_data1
    {0x7218,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       0},     //mid_table_data0
    /*VHDACCMEDN*/
    {0x721c,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       670},   //mid_table_data5
    {0x721c,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       540},   //mid_table_data4
    {0x721c,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       384},   //mid_table_data3
    /*VHDACCMEDN*/
    {0x7220,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       1023},  //mid_table_data8
    {0x7220,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       880},   //mid_table_data7
    {0x7220,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       800},   //mid_table_data6
    /*VHDACCHIGHN*/
    {0x7224,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       240},   //high_table_data2
    {0x7224,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       100},   //high_table_data1
    {0x7224,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       0},     //high_table_data0
    /*VHDACCHIGHN*/
    {0x7228,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       620},   //high_table_data5
    {0x7228,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       496},   //high_table_data4
    {0x7228,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       360},   //high_table_data3
    /*VHDACCHIGHN*/
    {0x722c,        20,     29,     0,      0,      HI_PQ_MODULE_DCI,       1023},  //high_table_data8
    {0x722c,        10,     19,     0,      0,      HI_PQ_MODULE_DCI,       864},   //high_table_data7
    {0x722c,        0,      9,      0,      0,      HI_PQ_MODULE_DCI,       764},   //high_table_data6
    /***********************************************ACM_CTRL***********************************************/
    /*VHDACM0*/
    {0xb800,       31,     31,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //acm3_en
    {0xb800,       30,     30,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //acm2_en
    {0xb800,       29,     29,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //acm1_en
    {0xb800,       28,     28,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //acm0_en
    {0xb800,       24,     27,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_sec_blk
    {0xb800,       20,     23,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_fir_blk
    {0xb800,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_d_u_off
    {0xb800,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_c_u_off
    {0xb800,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},   //acm_b_u_off
    {0xb800,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_a_u_off
    /*VHDACM1*/
    {0xb804,       22,     22,     0,      0,      HI_PQ_MODULE_COLOR,     1},     //bw_pro_mode
    {0xb804,       21,     21,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_dbg_mode
    {0xb804,       20,     20,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_test_en
    {0xb804,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_d_v_off
    {0xb804,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_v_off
    {0xb804,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_b_v_off
    {0xb804,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_a_v_off
    /*VHDACM2*/
    {0xb808,       24,     27,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_sec_blk
    {0xb808,       20,     23,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_fir_blk
    {0xb808,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_d_u_off
    {0xb808,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_u_off
    {0xb808,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_b_u_off
    {0xb808,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_a_u_off
    /*VHDACM3*/
    {0xb80c,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_d_v_off
    {0xb80c,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_v_off
    {0xb80c,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_b_v_off
    {0xb80c,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_a_v_off
    /*VHDACM4*/
    {0xb810,       24,     27,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_sec_blk
    {0xb810,       20,     23,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_fir_blk
    {0xb810,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_d_u_off
    {0xb810,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_c_u_off
    {0xb810,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_b_u_off
    {0xb810,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_a_u_off
    /*VHDACM5*/
    {0xb814,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_d_v_off
    {0xb814,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_v_off
    {0xb814,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_b_v_off
    {0xb814,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_a_v_off
    /*VHDACM6*/
    {0xb818,       24,     27,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_sec_blk
    {0xb818,       20,     23,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_fir_blk
    {0xb818,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_d_u_off
    {0xb818,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_c_u_off
    {0xb818,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_b_u_off
    {0xb818,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_a_u_off
    /*VHDACM7*/
    {0xb81c,       15,     19,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_d_v_off
    {0xb81c,       10,     14,     0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_c_v_off
    {0xb81c,       5,      9,      0,      0,      HI_PQ_MODULE_COLOR,     0},     //acm_b_v_off
    {0xb81c,       0,      4,      0,      0,      HI_PQ_MODULE_COLOR,     0},    //acm_a_v_off
    /***********************************************SHARPEN***********************************************/
    /*SD source*/
    /*SPCTRL*/
    /*spctrl*/
    {0x7000,        3,      18,     1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_pos
    {0x7000,        2,       2,     1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_mode
    {0x7000,        1,       1,     1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //sharpen_en
    {0x7000,        0,       0,     1,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_en
    {0x7000,        19,     19,     1,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //ensctrl
    {0x7000,        20,     20,     1,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //peak_en
    {0x7000,        21,     21,     1,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //detec_en
    {0x7000,        22,     22,     1,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //hfreq_en_h
    {0x7000,        23,     23,     1,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //hfreq_en_v
    {0x7000,        24,     24,     1,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //hfreq_en_d
    {0x7000,        26,     28,     1,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //winsize_h
    {0x7000,        29,     31,     1,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //winsize_v
    /*spgain*/
    {0x7004,        0,      9,      1,      0,      HI_PQ_MODULE_SHARPNESS, 256},   //peak_gain
    {0x7004,        10,     19,     1,      0,      HI_PQ_MODULE_SHARPNESS, 768},   //edge_gain
    {0x7004,        20,     27,     1,      0,      HI_PQ_MODULE_SHARPNESS, 8},     //dir_gain
    {0x7004,        28,     30,     1,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //winsize_d
    /*sppeakshootctl*/
    {0x7008,        0,      7,      1,      0,      HI_PQ_MODULE_SHARPNESS, 0},    //peak_over_thr
    {0x7008,        8,      15,     1,      0,      HI_PQ_MODULE_SHARPNESS, 0},    //peak_under_thr
    {0x7008,        16,     23,     1,      0,      HI_PQ_MODULE_SHARPNESS, 96},    //peak_mixratio
    {0x7008,        24,     31,     1,      0,      HI_PQ_MODULE_SHARPNESS, 20},     //peak_coring
    /*spgainpos*/
    {0x700c,        0,      8,      1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_pos_h
    {0x700c,        9,      17,     1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_pos_v
    {0x700c,        18,     26,     1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_pos_d
    /*spgainneg*/
    {0x7010,        0,      8,      1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_neg_h
    {0x7010,        9,      17,     1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_neg_v
    {0x7010,        18,     26,     1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_neg_d
    /*spoverthr*/
    {0x7014,        0,      7,      1,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //over_thr_h
    {0x7014,        8,      15,     1,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //over_thr_v
    {0x7014,        16,     23,     1,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //over_thr_d
    {0x7014,        24,     31,     1,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //under_thr_h
    /*spunderthr*/
    {0x7018,        0,      7,      1,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //under_thr_v
    {0x7018,        8,      15,     1,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //under_thr_d
    {0x7018,        16,     23,     1,      0,      HI_PQ_MODULE_SHARPNESS, 96},    //mixratio_h
    {0x7018,        24,     31,     1,      0,      HI_PQ_MODULE_SHARPNESS, 96},    //mixratio_v
    /*spcoringzero*/
    {0x701c,        0,      7,      1,      0,      HI_PQ_MODULE_SHARPNESS, 3},     //coringzero_h
    {0x701c,        8,      15,     1,      0,      HI_PQ_MODULE_SHARPNESS, 3},     //coringzero_v
    {0x701c,        16,     23,     1,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //coringzero_d
    {0x701c,        24,     31,     1,      0,      HI_PQ_MODULE_SHARPNESS, 96},    //mixratio_d
    /*spcoringratio*/
    {0x7020,        0,      4,      1,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //coringratio_h
    {0x7020,        5,      9,      1,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //coringratio_v
    {0x7020,        10,     14,     1,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //coringratio_d
    {0x7020,        15,     22,     1,      0,      HI_PQ_MODULE_SHARPNESS, 7},     //coringthr_h
    {0x7020,        23,     30,     1,      0,      HI_PQ_MODULE_SHARPNESS, 7},     //coringthr_v
    /*splmtratio*/
    {0x7024,        0,      2,      1,      0,      HI_PQ_MODULE_SHARPNESS, 6},     //limit_ratio_h
    {0x7024,        3,      5,      1,      0,      HI_PQ_MODULE_SHARPNESS, 6},     //limit_ratio_v
    {0x7024,        6,      8,      1,      0,      HI_PQ_MODULE_SHARPNESS, 6},     //limit_ratio_d
    {0x7024,        9,      16,     1,      0,      HI_PQ_MODULE_SHARPNESS, 7},     //coringthr_d
    {0x7024,        17,     24,     1,      0,      HI_PQ_MODULE_SHARPNESS, 64},    //gradcontrastthr
    /*splmtpos0*/
    {0x7028,        0,      7,      1,      0,      HI_PQ_MODULE_SHARPNESS, 64},    //limitpos0_h
    {0x7028,        8,      15,     1,      0,      HI_PQ_MODULE_SHARPNESS, 64},    //limitpos0_v
    {0x7028,        16,     23,     1,      0,      HI_PQ_MODULE_SHARPNESS, 64},    //limitpos0_d
    {0x7028,        24,     31,     1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //limitpos1_h
    /*spboundpos*/
    {0x702c,        0,      7,      1,      0,      HI_PQ_MODULE_SHARPNESS, 112},   //boundpos_h
    {0x702c,        8,      15,     1,      0,      HI_PQ_MODULE_SHARPNESS, 112},   //boundpos_v
    {0x702c,        16,     23,     1,      0,      HI_PQ_MODULE_SHARPNESS, 112},   //boundpos_d
    {0x702c,        24,     31,     1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //limitpos1_v
    /*splmtneg0*/
    {0x7030,        0,      8,      1,      0,      HI_PQ_MODULE_SHARPNESS, -64},   //limitneg0_h
    {0x7030,        9,      17,     1,      0,      HI_PQ_MODULE_SHARPNESS, -64},   //limitneg0_v
    {0x7030,        18,     26,     1,      0,      HI_PQ_MODULE_SHARPNESS, -64},   //limitneg0_d
    /*splmtneg1*/
    {0x7034,        0,      8,      1,      0,      HI_PQ_MODULE_SHARPNESS, -128},  //limitneg1_h
    {0x7034,        9,      17,     1,      0,      HI_PQ_MODULE_SHARPNESS, -128},  //limitneg1_v
    {0x7034,        18,     26,     1,      0,      HI_PQ_MODULE_SHARPNESS, -128},  //limitneg1_d
    /*spboundneg*/
    {0x7038,        0,      8,      1,      0,      HI_PQ_MODULE_SHARPNESS, -112},  //boundneg_h
    {0x7038,        9,      17,     1,      0,      HI_PQ_MODULE_SHARPNESS, -112},  //boundneg_v
    {0x7038,        18,     26,     1,      0,      HI_PQ_MODULE_SHARPNESS, -112},  //boundneg_d
    /*spedgeshootctl*/
    {0x703c,        0,      7,      1,      0,      HI_PQ_MODULE_SHARPNESS, 10},    //edge_over_thr
    {0x703c,        8,      15,     1,      0,      HI_PQ_MODULE_SHARPNESS, 10},    //edge_under_thr
    {0x703c,        16,     23,     1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //edge_mixratio
    {0x703c,        24,     31,     1,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //limitpos1_d
    /*spedgeei*/
    {0x7040,        0,      7,      1,      0,      HI_PQ_MODULE_SHARPNESS, 68},    //edge_ei0
    {0x7040,        8,      15,     1,      0,      HI_PQ_MODULE_SHARPNESS, 100},   //edge_ei1
    {0x7040,        16,     23,     1,      0,      HI_PQ_MODULE_SHARPNESS, 4},     //edge_eiratio
    {0x7040,        24,     30,     1,      0,      HI_PQ_MODULE_SHARPNESS, 16},    //ushootratioe
    /*spgradmin*/
    {0x7044,        0,      9,      1,      0,      HI_PQ_MODULE_SHARPNESS, 8},     //gradminthrl
    {0x7044,        10,     19,     1,      0,      HI_PQ_MODULE_SHARPNESS, 40},    //gradminthrh
    {0x7044,        20,     27,     1,      0,      HI_PQ_MODULE_SHARPNESS, 4},     //gradminslop
    /*spgradctr*/
    {0x7048,        0,      9,      1,      0,      HI_PQ_MODULE_SHARPNESS, 16},    //gradminthr
    {0x7048,        10,     25,     1,      0,      HI_PQ_MODULE_SHARPNESS, 1600},  //chessboardthr
    /*spshootratio*/
    {0x704c,        0,      8,      1,      0,      HI_PQ_MODULE_SHARPNESS, 4},     //gradcontrastslop
    {0x704c,        9,      15,     1,      0,      HI_PQ_MODULE_SHARPNESS, 16},    //ushootratiot
    {0x704c,        16,     22,     1,      0,      HI_PQ_MODULE_SHARPNESS, 127},   //oshootratioe
    {0x704c,        23,     29,     1,      0,      HI_PQ_MODULE_SHARPNESS, 127},   //oshootratiot

    /*HD source*/
    /*spctrl*/
    {0x7000,        3,      18,     2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_pos
    {0x7000,        2,       2,     2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_mode
    {0x7000,        1,       1,     2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //sharpen_en
    {0x7000,        0,       0,     2,      0,      HI_PQ_MODULE_SHARPNESS,   0},     //demo_en
    {0x7000,        19,     19,     2,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //ensctrl
    {0x7000,        20,     20,     2,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //peak_en
    {0x7000,        21,     21,     2,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //detec_en
    {0x7000,        22,     22,     2,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //hfreq_en_h
    {0x7000,        23,     23,     2,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //hfreq_en_v
    {0x7000,        24,     24,     2,      0,      HI_PQ_MODULE_SHARPNESS, 1},     //hfreq_en_d
    {0x7000,        26,     28,     2,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //winsize_h
    {0x7000,        29,     31,     2,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //winsize_v
    /*spgain*/
    {0x7004,        0,      9,      2,      0,      HI_PQ_MODULE_SHARPNESS, 96},    //peak_gain
    {0x7004,        10,     19,     2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //edge_gain
    {0x7004,        20,     27,     2,      0,      HI_PQ_MODULE_SHARPNESS, 8},     //dir_gain
    {0x7004,        28,     30,     2,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //winsize_d
    /*sppeakshootctl*/
    {0x7008,        0,      7,      2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //peak_over_thr
    {0x7008,        8,      15,     2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //peak_under_thr
    {0x7008,        16,     23,     2,      0,      HI_PQ_MODULE_SHARPNESS, 96},    //peak_mixratio
    {0x7008,        24,     31,     2,      0,      HI_PQ_MODULE_SHARPNESS, 3},     //peak_coring
    /*spgainpos*/
    {0x700c,        0,      8,      2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_pos_h
    {0x700c,        9,      17,     2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_pos_v
    {0x700c,        18,     26,     2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_pos_d
    /*spgainneg*/
    {0x7010,        0,      8,      2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_neg_h
    {0x7010,        9,      17,     2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_neg_v
    {0x7010,        18,     26,     2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //gain_neg_d
    /*spoverthr*/
    {0x7014,        0,      7,      2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //over_thr_h
    {0x7014,        8,      15,     2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //over_thr_v
    {0x7014,        16,     23,     2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //over_thr_d
    {0x7014,        24,     31,     2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //under_thr_h
    /*spunderthr*/
    {0x7018,        0,      7,      2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //under_thr_v
    {0x7018,        8,      15,     2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //under_thr_d
    {0x7018,        16,     23,     2,      0,      HI_PQ_MODULE_SHARPNESS, 96},    //mixratio_h
    {0x7018,        24,     31,     2,      0,      HI_PQ_MODULE_SHARPNESS, 96},    //mixratio_v
    /*spcoringzero*/
    {0x701c,        0,      7,      2,      0,      HI_PQ_MODULE_SHARPNESS, 3},     //coringzero_h
    {0x701c,        8,      15,     2,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //coringzero_v
    {0x701c,        16,     23,     2,      0,      HI_PQ_MODULE_SHARPNESS, 2},     //coringzero_d
    {0x701c,        24,     31,     2,      0,      HI_PQ_MODULE_SHARPNESS, 96},    //mixratio_d
    /*spcoringratio*/
    {0x7020,        0,      4,      2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //coringratio_h
    {0x7020,        5,      9,      2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //coringratio_v
    {0x7020,        10,     14,     2,      0,      HI_PQ_MODULE_SHARPNESS, 15},    //coringratio_d
    {0x7020,        15,     22,     2,      0,      HI_PQ_MODULE_SHARPNESS, 7},     //coringthr_h
    {0x7020,        23,     30,     2,      0,      HI_PQ_MODULE_SHARPNESS, 7},     //coringthr_v
    /*splmtratio*/
    {0x7024,        0,      2,      2,      0,      HI_PQ_MODULE_SHARPNESS, 6},     //limit_ratio_h
    {0x7024,        3,      5,      2,      0,      HI_PQ_MODULE_SHARPNESS, 6},     //limit_ratio_v
    {0x7024,        6,      8,      2,      0,      HI_PQ_MODULE_SHARPNESS, 6},     //limit_ratio_d
    {0x7024,        9,      16,     2,      0,      HI_PQ_MODULE_SHARPNESS, 7},     //coringthr_d
    {0x7024,        17,     24,     2,      0,      HI_PQ_MODULE_SHARPNESS, 64},    //gradcontrastthr
    /*splmtpos0*/
    {0x7028,        0,      7,      2,      0,      HI_PQ_MODULE_SHARPNESS, 64},    //limitpos0_h
    {0x7028,        8,      15,     2,      0,      HI_PQ_MODULE_SHARPNESS, 64},    //limitpos0_v
    {0x7028,        16,     23,     2,      0,      HI_PQ_MODULE_SHARPNESS, 64},    //limitpos0_d
    {0x7028,        24,     31,     2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //limitpos1_h
    /*spboundpos*/
    {0x702c,        0,      7,      2,      0,      HI_PQ_MODULE_SHARPNESS, 112},   //boundpos_h
    {0x702c,        8,      15,     2,      0,      HI_PQ_MODULE_SHARPNESS, 112},   //boundpos_v
    {0x702c,        16,     23,     2,      0,      HI_PQ_MODULE_SHARPNESS, 112},   //boundpos_d
    {0x702c,        24,     31,     2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //limitpos1_v
    /*splmtneg0*/
    {0x7030,        0,      8,      2,      0,      HI_PQ_MODULE_SHARPNESS, -64},   //limitneg0_h
    {0x7030,        9,      17,     2,      0,      HI_PQ_MODULE_SHARPNESS, -64},   //limitneg0_v
    {0x7030,        18,     26,     2,      0,      HI_PQ_MODULE_SHARPNESS, -64},   //limitneg0_d
    /*splmtneg1*/
    {0x7034,        0,      8,      2,      0,      HI_PQ_MODULE_SHARPNESS, -128},  //limitneg1_h
    {0x7034,        9,      17,     2,      0,      HI_PQ_MODULE_SHARPNESS, -128},  //limitneg1_v
    {0x7034,        18,     26,     2,      0,      HI_PQ_MODULE_SHARPNESS, -128},  //limitneg1_d
    /*spboundneg*/
    {0x7038,        0,      8,      2,      0,      HI_PQ_MODULE_SHARPNESS, -112},  //boundneg_h
    {0x7038,        9,      17,     2,      0,      HI_PQ_MODULE_SHARPNESS, -112},  //boundneg_v
    {0x7038,        18,     26,     2,      0,      HI_PQ_MODULE_SHARPNESS, -112},  //boundneg_d
    /*spedgeshootctl*/
    {0x703c,        0,      7,      2,      0,      HI_PQ_MODULE_SHARPNESS, 10},    //edge_over_thr
    {0x703c,        8,      15,     2,      0,      HI_PQ_MODULE_SHARPNESS, 10},    //edge_under_thr
    {0x703c,        16,     23,     2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //edge_mixratio
    {0x703c,        24,     31,     2,      0,      HI_PQ_MODULE_SHARPNESS, 128},   //limitpos1_d
    /*spedgeei*/
    {0x7040,        0,      7,      2,      0,      HI_PQ_MODULE_SHARPNESS, 68},    //edge_ei0
    {0x7040,        8,      15,     2,      0,      HI_PQ_MODULE_SHARPNESS, 100},   //edge_ei1
    {0x7040,        16,     23,     2,      0,      HI_PQ_MODULE_SHARPNESS, 4},     //edge_eiratio
    {0x7040,        24,     30,     2,      0,      HI_PQ_MODULE_SHARPNESS, 16},    //ushootratioe
    /*spgradmin*/
    {0x7044,        0,      9,      2,      0,      HI_PQ_MODULE_SHARPNESS, 8},     //gradminthrl
    {0x7044,        10,     19,     2,      0,      HI_PQ_MODULE_SHARPNESS, 40},    //gradminthrh
    {0x7044,        20,     27,     2,      0,      HI_PQ_MODULE_SHARPNESS, 4},     //gradminslop
    /*spgradctr*/
    {0x7048,        0,      9,      2,      0,      HI_PQ_MODULE_SHARPNESS, 16},    //gradminthr
    {0x7048,        10,     25,     2,      0,      HI_PQ_MODULE_SHARPNESS, 1600},  //chessboardthr
    /*spshootratio*/
    {0x704c,        0,      8,      2,      0,      HI_PQ_MODULE_SHARPNESS, 4},     //gradcontrastslop
    {0x704c,        9,      15,     2,      0,      HI_PQ_MODULE_SHARPNESS, 16},    //ushootratiot
    {0x704c,        16,     22,     2,      0,      HI_PQ_MODULE_SHARPNESS, 127},   //oshootratioe
    {0x704c,        23,     29,     2,      0,      HI_PQ_MODULE_SHARPNESS, 127},   //oshootratiot

    /*videophone*/
    {0x7004,    10,      19,        0,      4,      HI_PQ_MODULE_SHARPNESS, 256},     //edge_gain
    {0x7004,     0,       9,        0,      4,      HI_PQ_MODULE_SHARPNESS, 400},     //peak_gain

    {0x7004,    10,      19,        0,      5,      HI_PQ_MODULE_SHARPNESS, 256},     //edge_gain
    {0x7004,     0,       9,        0,      5,      HI_PQ_MODULE_SHARPNESS, 400},     //peak_gain

    {0x7004,    10,      19,        1,      2,      HI_PQ_MODULE_SHARPNESS, 176},     //edge_gain
    {0x7004,     0,       9,        1,      2,      HI_PQ_MODULE_SHARPNESS, 352},     //peak_gain

    {0x7004,    10,      19,        1,      3,      HI_PQ_MODULE_SHARPNESS, 768},     //edge_gain
    {0x7004,     0,       9,        1,      3,      HI_PQ_MODULE_SHARPNESS, 456},     //peak_gain

    /************************************* ZME DS *****************************************/
    /* SHOOTCTRL_HL */
    {0x22f8,    17,     17,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_shootctrl_en
    {0x22f8,    16,     16,        0,        0,   HI_PQ_MODULE_ARTDS,        0},         //hl_shootctrl_mode
    {0x22f8,    15,     15,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_flatdect_mode
    {0x22f8,    14,     14,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_coringadj_en
    {0x22f8,    8,      13,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //hl_gain
    {0x22f8,    0,       7,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //hl_coring
    /* SHOOTCTRL_VL */
    {0x2300,    17,     17,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_shootctrl_en
    {0x2300,    16,     16,        0,        0,   HI_PQ_MODULE_ARTDS,        0},         //vl_shootctrl_mode
    {0x2300,    15,     15,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_flatdect_mode
    {0x2300,    14,     14,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_coringadj_en
    {0x2300,    8,      13,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //vl_gain
    {0x2300,    0,       7,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //vl_coring

    /* ZME2 DS */
    /* SHOOTCTRL_HL */
    {0x24f8,    17,     17,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_shootctrl_en
    {0x24f8,    16,     16,        0,        0,   HI_PQ_MODULE_ARTDS,        0},         //hl_shootctrl_mode
    {0x24f8,    15,     15,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_flatdect_mode
    {0x24f8,    14,     14,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //hl_coringadj_en
    {0x24f8,    8,      13,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //hl_gain
    {0x24f8,    0,       7,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //hl_coring
    /* SHOOTCTRL_VL */
    {0x2500,    17,     17,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_shootctrl_en
    {0x2500,    16,     16,        0,        0,   HI_PQ_MODULE_ARTDS,        0},         //vl_shootctrl_mode
    {0x2500,    15,     15,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_flatdect_mode
    {0x2500,    14,     14,        0,        0,   HI_PQ_MODULE_ARTDS,        1},         //vl_coringadj_en
    {0x2500,    8,      13,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //vl_gain
    {0x2500,    0,       7,        0,        0,   HI_PQ_MODULE_ARTDS,       32},         //vl_coring

};

static PQ_PHY_REG_S sg_stPQSoftReg[SOFT_REG_MAX] =
{
    /***************************************************************************
      * Special Register
     ***************************************************************************/

    /*Addr                                   Lsb       Msb    SourceMode  OutputMode   Module     Value        Description*/
    /***********************************************FMD_CTRL***********************************************/
    /*IP_DETECT*/
    {PQ_SOFT_IP_DETECT,         0,       1,        0,        0,     HI_PQ_MODULE_FMD,       0},       //ip_detect_choice
    {PQ_SOFT_FRMRATETHR_L,      0,      15,        0,        0,     HI_PQ_MODULE_FMD,   23800},       //g_u32FrmRateThr_L
    {PQ_SOFT_FRMRATETHR_H,      0,      15,        0,        0,     HI_PQ_MODULE_FMD,   24200},       //g_u32FrmRateThr_H

    /*COLOR_TEMP*/
    {PQ_SOFT_COLOR_TEMP_R,      0,       0,        0,        0,     HI_PQ_MODULE_CSC,      50},       //colortemp red
    {PQ_SOFT_COLOR_TEMP_G,      0,       0,        0,        0,     HI_PQ_MODULE_CSC,      50},       //colortemp green
    {PQ_SOFT_COLOR_TEMP_B,      0,       0,        0,        0,     HI_PQ_MODULE_CSC,      50},       //colortemp blue

    /*MODULE_ON_OR_OFF*/
    {PQ_SOFT_MODULE_FMD_SD,     0,       0,        0,        0,     HI_PQ_MODULE_FMD,       1},       //fmd sd on/off
    {PQ_SOFT_MODULE_FMD_HD,     0,       0,        0,        0,     HI_PQ_MODULE_FMD,       1},       //fmd hd on/off
    {PQ_SOFT_MODULE_FMD_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_FMD,       0},       //fmd uhd on/off
    {PQ_SOFT_MODULE_TNR_SD,     0,       0,        0,        0,     HI_PQ_MODULE_TNR,       1},       //tnr sd on/off
    {PQ_SOFT_MODULE_TNR_HD,     0,       0,        0,        0,     HI_PQ_MODULE_TNR,       1},       //tnr hd on/off
    {PQ_SOFT_MODULE_TNR_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_TNR,       0},       //tnr uhd on/off
    {PQ_SOFT_MODULE_SNR_SD,     0,       0,        0,        0,     HI_PQ_MODULE_SNR,       1},       //snr sd on/off
    {PQ_SOFT_MODULE_SNR_HD,     0,       0,        0,        0,     HI_PQ_MODULE_SNR,       0},       //snr hd on/off
    {PQ_SOFT_MODULE_SNR_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_SNR,       0},       //snr uhd on/off
    {PQ_SOFT_MODULE_LCHDR_SD,   0,       0,        0,        0,     HI_PQ_MODULE_LCHDR,     1},       //lchdr sd on/off
    {PQ_SOFT_MODULE_LCHDR_FHD,  0,       0,        0,        0,     HI_PQ_MODULE_LCHDR,     1},       //lchdr hd on/off
    {PQ_SOFT_MODULE_LCHDR_UHD,  0,       0,        0,        0,     HI_PQ_MODULE_LCHDR,     1},       //lchdr uhd on/off
    {PQ_SOFT_MODULE_DB_SD,      0,       0,        0,        0,     HI_PQ_MODULE_DB,        1},       //db sd on/off
    {PQ_SOFT_MODULE_DB_HD,      0,       0,        0,        0,     HI_PQ_MODULE_DB,        0},       //db hd on/off
    {PQ_SOFT_MODULE_DB_UHD,     0,       0,        0,        0,     HI_PQ_MODULE_DB,        0},       //db uhd on/off
    {PQ_SOFT_MODULE_DR_SD,      0,       0,        0,        0,     HI_PQ_MODULE_DR,        0},       //dr sd on/off
    {PQ_SOFT_MODULE_DR_HD,      0,       0,        0,        0,     HI_PQ_MODULE_DR,        0},       //dr hd on/off
    {PQ_SOFT_MODULE_DR_UHD,     0,       0,        0,        0,     HI_PQ_MODULE_DR,        0},       //dr uhd on/off
    {PQ_SOFT_MODULE_DM_SD,      0,       0,        0,        0,     HI_PQ_MODULE_DM,        1},       //dm sd on/off
    {PQ_SOFT_MODULE_DM_HD,      0,       0,        0,        0,     HI_PQ_MODULE_DM,        0},       //dm hd on/off
    {PQ_SOFT_MODULE_DM_UHD,     0,       0,        0,        0,     HI_PQ_MODULE_DM,        0},       //dm uhd on/off
    {PQ_SOFT_MODULE_SHARPN_SD,  0,       0,        0,        0,     HI_PQ_MODULE_SHARPNESS, 1},       //sharp sd on/off
    {PQ_SOFT_MODULE_SHARPN_HD,  0,       0,        0,        0,     HI_PQ_MODULE_SHARPNESS, 1},       //sharphd on/off
    {PQ_SOFT_MODULE_SHARPN_UHD, 0,       0,        0,        0,     HI_PQ_MODULE_SHARPNESS, 0},       //sharp uhd on/off
    {PQ_SOFT_MODULE_DCI_SD,     0,       0,        0,        0,     HI_PQ_MODULE_DCI,       1},       //dci sd on/off
    {PQ_SOFT_MODULE_DCI_HD,     0,       0,        0,        0,     HI_PQ_MODULE_DCI,       1},       //dci hd on/off
    {PQ_SOFT_MODULE_DCI_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_DCI,       1},       //dci uhd on/off
    {PQ_SOFT_MODULE_ACM_SD,     0,       0,        0,        0,     HI_PQ_MODULE_COLOR,     1},       //acm sd on/off
    {PQ_SOFT_MODULE_ACM_HD,     0,       0,        0,        0,     HI_PQ_MODULE_COLOR,     1},       //acm hd on/off
    {PQ_SOFT_MODULE_ACM_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_COLOR,     1},       //acm uhd on/off
    {PQ_SOFT_MODULE_CSC_SD,     0,       0,        0,        0,     HI_PQ_MODULE_CSC,       1},       //csc sd on/off
    {PQ_SOFT_MODULE_CSC_HD,     0,       0,        0,        0,     HI_PQ_MODULE_CSC,       1},       //csc hd on/off
    {PQ_SOFT_MODULE_CSC_UHD,    0,       0,        0,        0,     HI_PQ_MODULE_CSC,       1},       //csc uhd on/off
    {PQ_SOFT_MODULE_DS_SD,      0,       0,        0,        0,     HI_PQ_MODULE_DS,        1},       //fmd sd on/off
    {PQ_SOFT_MODULE_DS_HD,      0,       0,        0,        0,     HI_PQ_MODULE_DS,        1},       //fmd hd on/off
    {PQ_SOFT_MODULE_DS_UHD,     0,       0,        0,        0,     HI_PQ_MODULE_DS,        1},       //fmd uhd on/off
};


PQ_PHY_REG_S *PQ_TABLE_GetPhyRegDefault(HI_VOID)
{
    return sg_stPhyRegDefault;
}

PQ_PHY_REG_S *PQ_TABLE_GetSoftRegDefault(HI_VOID)
{
    return sg_stPQSoftReg;
}

