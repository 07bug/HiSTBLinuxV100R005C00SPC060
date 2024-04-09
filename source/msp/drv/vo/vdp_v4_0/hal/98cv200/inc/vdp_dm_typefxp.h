
#ifndef __VDP_DM_TYPE_FXP_H__
#define __VDP_DM_TYPE_FXP_H__


#include "vdp_dm_modctrl.h"
#include "vdp_dm_type.h"
#include "vdp_dm_typefxpcmn.h"

typedef   int                HI_S32;
typedef   unsigned int       HI_U32;
typedef   unsigned char      HI_U8;
typedef   short              HI_S16;
typedef   unsigned short     HI_U16;
typedef   unsigned long long HI_U64;
#define VDP_MAX_PIVOT       9
#define VDP_MAX_POLY_ORDER  2
#define VDP_MAX_DMEXT_BLOCKS 255


typedef struct tagVDP_HDR10_FRMINFO_S
{
    HI_U8 infoframe_type_code      ;
    HI_U8 infoframe_version_number ;
    HI_U8 length_of_info_frame     ;
    HI_U8 data_byte_1              ;
    HI_U8 data_byte_2              ;
    HI_U8 display_primaries_x_0_LSB;
    HI_U8 display_primaries_x_0_MSB;
    HI_U8 display_primaries_y_0_LSB;
    HI_U8 display_primaries_y_0_MSB;
    HI_U8 display_primaries_x_1_LSB;
    HI_U8 display_primaries_x_1_MSB;
    HI_U8 display_primaries_y_1_LSB;
    HI_U8 display_primaries_y_1_MSB;
    HI_U8 display_primaries_x_2_LSB;
    HI_U8 display_primaries_x_2_MSB;
    HI_U8 display_primaries_y_2_LSB;
    HI_U8 display_primaries_y_2_MSB;
    HI_U8 white_point_x_LSB        ;
    HI_U8 white_point_x_MSB        ;
    HI_U8 white_point_y_LSB        ;
    HI_U8 white_point_y_MSB        ;
    HI_U8 max_display_mastering_luminance_LSB;
    HI_U8 max_display_mastering_luminance_MSB;
    HI_U8 min_display_mastering_luminance_LSB;
    HI_U8 min_display_mastering_luminance_MSB;
    HI_U8 max_content_light_level_LSB        ;
    HI_U8 max_content_light_level_MSB        ;
    HI_U8 max_frame_average_light_level_LSB  ;
    HI_U8 max_frame_average_light_level_MSB  ;
} VDP_HDR10_FRMINFO_S;

typedef struct tagVDP_FIXPT_MAIN_CFG_S
{
    HI_U32  rpu_VDR_bit_depth;
    HI_U32  rpu_BL_bit_depth;
    HI_U32  rpu_EL_bit_depth;
    HI_U32  coefficient_log2_denom;
    HI_U32  num_pivots[3];
    HI_U32  pivot_value[3][VDP_MAX_PIVOT];
    HI_U32  mapping_idc[3];
    HI_U32  poly_order[3][VDP_MAX_PIVOT - 1];
    HI_S32   poly_coef_int[3][VDP_MAX_PIVOT - 1][VDP_MAX_POLY_ORDER + 1];
    HI_U32  poly_coef[3][VDP_MAX_PIVOT - 1][VDP_MAX_POLY_ORDER + 1];
    HI_U32  MMR_order[2];
    HI_S32   MMR_coef_int[2][22];
    HI_U32  MMR_coef[2][22];
    HI_U8   NLQ_method_idc;
    HI_U8   disable_residual_flag;
    HI_U8   el_spatial_resampling_filter_flag;
    HI_U8   reserved_8bit;
    HI_U32  NLQ_offset[3];
    HI_S32   NLQ_coeff_int[3][3];
    HI_U32  NLQ_coeff[3][3];
    HI_U32  spatial_resampling_filter_flag;
    HI_U32  spatial_resampling_explicit_filter_flag;
    HI_U32  spatial_filter_exp_coef_log2_denom;
    HI_U32  spatial_resampling_mode_hor_idc;
    HI_U32  spatial_resampling_mode_ver_idc;
    HI_U32  spatial_resampling_filter_hor_idc[3];
    HI_U32  spatial_resampling_filter_ver_idc[3];
    HI_U32  spatial_resampling_luma_pivot[2];
    HI_S32   spatial_filter_coeff_hor_int[3][8];
    HI_U32  spatial_filter_coeff_hor[3][8];
    HI_S32   spatial_filter_coeff_ver_int[2][3][6];
    HI_U32  spatial_filter_coeff_ver[2][3][6];
} VDP_FIXPT_MAIN_CFG_S;

typedef struct tagVDP_BASE_METADATA_S
{

    HI_U8 dm_metadata_id;
    HI_U8 scene_refresh_flag;
    HI_U8 YCCtoRGB_coef0_hi;
    HI_U8 YCCtoRGB_coef0_lo;
    HI_U8 YCCtoRGB_coef1_hi;
    HI_U8 YCCtoRGB_coef1_lo;
    HI_U8 YCCtoRGB_coef2_hi;
    HI_U8 YCCtoRGB_coef2_lo;
    HI_U8 YCCtoRGB_coef3_hi;
    HI_U8 YCCtoRGB_coef3_lo;
    HI_U8 YCCtoRGB_coef4_hi;
    HI_U8 YCCtoRGB_coef4_lo;
    HI_U8 YCCtoRGB_coef5_hi;
    HI_U8 YCCtoRGB_coef5_lo;
    HI_U8 YCCtoRGB_coef6_hi;
    HI_U8 YCCtoRGB_coef6_lo;
    HI_U8 YCCtoRGB_coef7_hi;
    HI_U8 YCCtoRGB_coef7_lo;
    HI_U8 YCCtoRGB_coef8_hi;
    HI_U8 YCCtoRGB_coef8_lo;
    HI_U8 YCCtoRGB_offset0_byte3;
    HI_U8 YCCtoRGB_offset0_byte2;
    HI_U8 YCCtoRGB_offset0_byte1;
    HI_U8 YCCtoRGB_offset0_byte0;
    HI_U8 YCCtoRGB_offset1_byte3;
    HI_U8 YCCtoRGB_offset1_byte2;
    HI_U8 YCCtoRGB_offset1_byte1;
    HI_U8 YCCtoRGB_offset1_byte0;
    HI_U8 YCCtoRGB_offset2_byte3;
    HI_U8 YCCtoRGB_offset2_byte2;
    HI_U8 YCCtoRGB_offset2_byte1;
    HI_U8 YCCtoRGB_offset2_byte0;
    HI_U8 RGBtoLMS_coef0_hi;
    HI_U8 RGBtoLMS_coef0_lo;
    HI_U8 RGBtoLMS_coef1_hi;
    HI_U8 RGBtoLMS_coef1_lo;
    HI_U8 RGBtoLMS_coef2_hi;
    HI_U8 RGBtoLMS_coef2_lo;
    HI_U8 RGBtoLMS_coef3_hi;
    HI_U8 RGBtoLMS_coef3_lo;
    HI_U8 RGBtoLMS_coef4_hi;
    HI_U8 RGBtoLMS_coef4_lo;
    HI_U8 RGBtoLMS_coef5_hi;
    HI_U8 RGBtoLMS_coef5_lo;
    HI_U8 RGBtoLMS_coef6_hi;
    HI_U8 RGBtoLMS_coef6_lo;
    HI_U8 RGBtoLMS_coef7_hi;
    HI_U8 RGBtoLMS_coef7_lo;
    HI_U8 RGBtoLMS_coef8_hi;
    HI_U8 RGBtoLMS_coef8_lo;
    HI_U8 signal_eotf_hi;
    HI_U8 signal_eotf_lo;
    HI_U8 signal_eotf_param0_hi;
    HI_U8 signal_eotf_param0_lo;
    HI_U8 signal_eotf_param1_hi;
    HI_U8 signal_eotf_param1_lo;
    HI_U8 signal_eotf_param2_byte3;
    HI_U8 signal_eotf_param2_byte2;
    HI_U8 signal_eotf_param2_byte1;
    HI_U8 signal_eotf_param2_byte0;
    HI_U8 signal_bit_depth;
    HI_U8 signal_color_space;
    HI_U8 signal_chroma_format;
    HI_U8 signal_full_range_flag;

    HI_U8 source_min_PQ_hi;
    HI_U8 source_min_PQ_lo;
    HI_U8 source_max_PQ_hi;
    HI_U8 source_max_PQ_lo;
    HI_U8 source_diagonal_hi;
    HI_U8 source_diagonal_lo;

    HI_U8 num_ext_blocks;
} VDP_BASE_METADATA_S;

typedef struct tagVDP_EXTLEVEL1_S
{
    HI_U8 min_PQ_hi;
    HI_U8 min_PQ_lo;
    HI_U8 max_PQ_hi;
    HI_U8 max_PQ_lo;
    HI_U8 avg_PQ_hi;
    HI_U8 avg_PQ_lo;
} VDP_EXTLEVEL1_S;

typedef struct tagVDP_EXTLEVEL2_S
{
    HI_U8 target_max_PQ_hi       ;
    HI_U8 target_max_PQ_lo       ;
    HI_U8 trim_slope_hi          ;
    HI_U8 trim_slope_lo          ;
    HI_U8 trim_offset_hi         ;
    HI_U8 trim_offset_lo         ;
    HI_U8 trim_power_hi          ;
    HI_U8 trim_power_lo          ;
    HI_U8 trim_chroma_weight_hi  ;
    HI_U8 trim_chroma_weight_lo  ;
    HI_U8 trim_saturation_gain_hi;
    HI_U8 trim_saturation_gain_lo;
    HI_U8 ms_weight_hi           ;
    HI_U8 ms_weight_lo           ;
} VDP_EXTLEVEL2_S;

typedef struct tagVDP_EXTLEVEL4_S
{
    HI_U8 anchor_PQ_hi       ;
    HI_U8 anchor_PQ_lo       ;
    HI_U8 anchor_power_hi    ;
    HI_U8 anchor_power_lo    ;
} VDP_EXTLEVEL4_S;

typedef struct tagVDP_EXTLEVEL5_S
{
    HI_U8 active_area_left_offset_hi  ;
    HI_U8 active_area_left_offset_lo  ;
    HI_U8 active_area_right_offset_hi ;
    HI_U8 active_area_right_offset_lo ;
    HI_U8 active_area_top_offset_hi   ;
    HI_U8 active_area_top_offset_lo   ;
    HI_U8 active_area_bottom_offset_hi;
    HI_U8 active_area_bottom_offset_lo;
} VDP_EXTLEVEL5_S;

typedef struct tagVDP_EXTLEVEL6_S
{
    HI_U8 max_display_mastering_luminance_hi;
    HI_U8 max_display_mastering_luminance_lo;
    HI_U8 min_display_mastering_luminance_hi;
    HI_U8 min_display_mastering_luminance_lo;
    HI_U8 max_content_light_level_hi        ;
    HI_U8 max_content_light_level_lo        ;
    HI_U8 max_frame_average_light_level_hi  ;
    HI_U8 max_frame_average_light_level_lo  ;
} VDP_EXTLEVEL6_S;
typedef struct tagVDP_EXT_METADATA_S
{
    HI_U8 ext_block_length_byte3;
    HI_U8 ext_block_length_byte2;
    HI_U8 ext_block_length_byte1;
    HI_U8 ext_block_length_byte0;
    HI_U8 ext_block_level;
    union
    {
        VDP_EXTLEVEL1_S level_1;
        VDP_EXTLEVEL2_S level_2;
        VDP_EXTLEVEL4_S level_4;
        VDP_EXTLEVEL5_S level_5;
        VDP_EXTLEVEL6_S level_6;
    } l;
} VDP_EXT_METADATA_S;

typedef struct tagVDP_METADATA_S
{
    VDP_BASE_METADATA_S base;
    VDP_EXT_METADATA_S ext[VDP_MAX_DMEXT_BLOCKS];
} VDP_METADATA_S;



typedef struct tagVDP_E2O_FXPPARAM_S
{

    HI_U16 rangeMin, range;
    HI_U32 rangeInv;
    HI_U16 bdp;

    KEotf_t eotf;
#if (REDUCED_COMPLEXITY == 0)
    HI_U16 gamma;
    HI_U16 a, b;
    HI_U32 g;
#endif
} VDP_E2O_FXPPARAM_S;


typedef struct tagVDP_O2E_FXPPARAM_S
{

    HI_U32 min, max;
    HI_U16 rangeMin, range;
    HI_U32 rangeOverOne;
    HI_U16 bdp;


    KEotf_t oetf;
} VDP_O2E_FXPPARAM_S;


typedef struct tagVDP_DM_INMAP_FXP_S
{
#if !EN_IPT_PQ_ONLY_OPTION
    KClr_t clr;
    HI_S16 m33Yuv2RgbScale2P;
    HI_S16 m33Yuv2Rgb[3][3];
    HI_S32 v3Yuv2RgbOffInRgb[3];

    VDP_E2O_FXPPARAM_S eotfParam;
#if 1
    HI_U32 g2L[DEF_G2L_LUT_SIZE];
#endif

    HI_S16 m33Rgb2LmsScale2P;
    HI_S16 m33Rgb2Lms[3][3];

    HI_S16 m33Lms2IptScale2P;
    HI_S16 m33Lms2Ipt[3][3];
#endif

    HI_S32 iptScale;
    HI_S32 v3IptOff[3];
} VDP_DM_INMAP_FXP_S;

#if DM_SIMPLE_SEC_INPUT

typedef struct tagVDP_DM_INMAP_SDRFXP_S
{
    KClr_t clr;
    VDP_E2O_FXPPARAM_S eotfParam;

    HI_S16 m33Rgb2LmsScale2P;
    HI_S16 m33Rgb2Lms[3][3];

    HI_S16 m33Lms2IptScale2P;
    HI_S16 m33Lms2Ipt[3][3];
} VDP_DM_INMAP_SDRFXP_S;
#endif

typedef struct tagVDP_TMAP_FXP_S
{
#if 1
    VDP_DM_TCLUTDIR_S tcLutDir;
#endif

    HI_S16 tmLutISizeM1;


    HI_S16 tmLutSSizeM1;
    HI_S16 tmLutI[TM1_LUT_MAX_SIZE];
    HI_S16 tmLutS[TM1_LUT_MAX_SIZE];

    HI_S16 smLutISizeM1, smLutSSizeM1;
    HI_S16 smLutI[TM1_LUT_MAX_SIZE];
    HI_S16 smLutS[TM1_LUT_MAX_SIZE];

} DmKsTMapFxp_t;

#if DM_SIMPLE_SEC_INPUT

typedef struct Dm3KsTMapReducedFxp_t_
{
#if 1
    VDP_DM_TCLUTDIR_S tcLutDir;
#endif

    HI_S16 tmLutISizeM1;

    HI_S16 tmLutSSizeM1;
    HI_S16 tmLutI[TM2_LUT_MAX_SIZE];
    HI_S16 tmLutS[TM2_LUT_MAX_SIZE];

    HI_S16 smLutISizeM1, smLutSSizeM1;
    HI_S16 smLutI[TM2_LUT_MAX_SIZE];
    HI_S16 smLutS[TM2_LUT_MAX_SIZE];

} DmKsTMapReducedFxp_t;
#endif


typedef struct tagVDP_DM3_OUTMAP_FXP_S
{

    HI_S16 m33Ipt2LmsScale2P;
    HI_S16 m33Ipt2Lms[3][3];


    HI_S16 m33Lms2RgbScale2P;
    HI_S16 m33Lms2Rgb[3][3];

    VDP_O2E_FXPPARAM_S oetfParam;


    KClr_t clr;
    HI_S16 m33Rgb2YuvScale2P;
    HI_S16 m33Rgb2Yuv[3][3];
    HI_S32 v3Rgb2YuvOff[3];
    HI_S32 iptScale;
    HI_S32 v3IptOff[3];
} VDP_DM3_OUTMAP_FXP_S;

typedef struct tagVDP_DM3_OUTMAP_FXP_S  tagVDP_DM_OUTMAP_FXP_S;
typedef VDP_DM3_OUTMAP_FXP_S VDP_DM_OUTMAP_FXP_S;





#if 0

typedef struct DmKsUdsFxp_t_
{

#if 1
    KChrm_t chrmIn, chrmOut;
#endif

    HI_S16 minUs, maxUs, minDs, maxDs;

#if 1
    HI_S16 filterUvRowUsHalfSize;
    HI_S16 filterUvRowUsScale2P;
    HI_S16 filterUvRowUs0_m[8];
    HI_S16 filterUvRowUs1_m[8];

    HI_S16 filterUvColUsHalfSize;
    HI_S16 filterUvColUsScale2P;
    HI_S16 filterUvColUs_m[8];

    HI_S16 filterUvColDsRadius;
    HI_S16 filterUvColDsScale2P;
    HI_S16 filterUvColDs_m[16];
#endif
} DmKsUdsFxp_t;

#define VDP_DM_US_FXP_S DmKsUdsFxp_t
#define VDP_DM_DS_FXP_S DmKsUdsFxp_t
#else

typedef struct tagVDP_DM_US_FXP_S
{


#if 1
    KChrm_t chrmIn;
#endif

    HI_S16 minUs, maxUs;


#if 1

    HI_S16 filterUvRowUsHalfSize;
    HI_S16 filterUvRowUsScale2P;
    HI_S16 filterUvRowUs0_m[8];
    HI_S16 filterUvRowUs1_m[8];

    HI_S16 filterUvColUsHalfSize;
    HI_S16 filterUvColUsScale2P;
    HI_S16 filterUvColUs_m[8];
#endif
} VDP_DM_US_FXP_S;

typedef struct tagVDP_DM_DS_FXP_S
{

#if 1
    KChrm_t chrmOut;
#endif

    HI_S16 minDs, maxDs;

#if 1

    HI_S16 filterUvColDsRadius;
    HI_S16 filterUvColDsScale2P;
    HI_S16 filterUvColDs_m[16];
#endif
} VDP_DM_DS_FXP_S;

#endif


typedef struct DmKsFxp_t_
{
#if 1

    HI_S16 rowPitchNum;

    HI_U64 frmBuf0, frmBuf1, frmBuf2;

#endif

#if 1

    HI_U64 frmBuf0G, frmBuf1G, frmBuf2G;
#endif


#if 0

    DmKsUdsFxp_t ksUds;
#define ksUs   ksUds
#define ksDs   ksUds
#else
    VDP_DM_US_FXP_S ksUs;
    VDP_DM_DS_FXP_S ksDs;

#endif

    VDP_DM_KSCTRL_S ksDmCtrl;

    VDP_DM_FRM_FMT_S ksFrmFmtI;

    VDP_DM_INMAP_FXP_S  ksIMap;

    DmKsTMapFxp_t ksTMap;

#if DM_SEC_INPUT
#if EN_GENERAL_SEC_INPUT
    VDP_DM_US_FXP_S ksUsG;
    VDP_DM_FRM_FMT_S ksFrmFmtA;
    HI_U32 rangeInvA;
#endif

    VDP_DM_FRM_FMT_S ksFrmFmtG;

#if DM_SIMPLE_SEC_INPUT
    VDP_DM_INMAP_SDRFXP_S  ksIMapSdrG;

    DmKsTMapReducedFxp_t ksTMapReducedG;
#endif
    VDP_DM_INMAP_FXP_S  ksIMapG;

    DmKsTMapFxp_t ksTMapG;
#endif
    VDP_DM_OUTMAP_FXP_S ksOMap;

    VDP_DM_FRM_FMT_S ksFrmFmtO;

#if 1
    HI_S16 bypassShift;
#endif


} DmKsFxp_t;


#endif
