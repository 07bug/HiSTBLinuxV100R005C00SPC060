/******************************************************************************

  Copyright (C), 2001-2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : dolby_wrap.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2017/12/25
  Description   :
  History       :
  1.Date        : 2017/12/25
    Author      : sdk
    Modification: Created file
    note        : This file ONLY for SDK MPI use, 
                  DO NOT put any structures that related with dolby here!

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/********************************************************************************
wrap layer err code(the same as hi_error_mpi.h) 
*********************************************************************************/
#define   ERR_DOLBY_WRAP_NO_INIT           (signed int)(0x80110006)
#define   ERR_DOLBY_WRAP_NOT_SUPPORT       (signed int)(0x80110042)
#define   ERR_DOLBY_WRAP_NULL_POINTER      (signed int)(0x80110005)
#define   ERR_DOLBY_WRAP_INVALID_COMMAND   (signed int)(0x80110030)
#define   ERR_DOLBY_WRAP_INVALID_PARA      (signed int)(0x80110007)


/********************************************************************************
for mpi debug.
*********************************************************************************/
#define   HISI_DMKS_LEN    10944
#define   COMPOSER_LEN     1800

/********************************************************************************
common structures 
*********************************************************************************/
typedef struct coeff_s
{
    uint64_t u64Addr;
    uint32_t u32Len;
}dolby_coeff_s;


/********************************************************************************
structure for CMD_GENERATE_CONFIG 
*********************************************************************************/
typedef struct hiRPU_S
{
    unsigned char *p_rpu_addr;
    unsigned int  rpu_len;
}RPU_S;

typedef enum {
  chroma_420 = 0,
  chroma_422,
  chroma_444,
} chroma_format_t;

typedef enum {
  range_narrow = 0, // head
  range_full  = 1, // will be the in data type(bits) range
  range_sdi = 2, // pq
} range_t;

typedef enum priority_mode_e
{
    VIDEO_PRIORITY = 0,
    GRAPHIC_PRIORITY = 1
} priority_mode_t;

/*! @brief HDR10 parameters data structure.
           This is the data structure used for the HDR10 SEI messages.
           Details for each entry can be found in HEVC specification
*/
typedef struct hdr10_param_s
{
    uint32_t min_display_mastering_luminance; /**< @brief */
    uint32_t max_display_mastering_luminance; /**< @brief */
    uint16_t Rx;                              /**< @brief */
    uint16_t Ry;                              /**< @brief */
    uint16_t Gx;                              /**< @brief */
    uint16_t Gy;                              /**< @brief */
    uint16_t Bx;                              /**< @brief */
    uint16_t By;                              /**< @brief */
    uint16_t Wx;                              /**< @brief */
    uint16_t Wy;                              /**< @brief */
    uint16_t max_content_light_level;         /**< @brief */
    uint16_t max_pic_average_light_level;     /**< @brief */
} hdr10_param_t;

/*! @brief HDR10 infoframe data structure.
           This is the data structure used for the HDR10 infoframe.
           Details for each entry can be found in CEA-861.3
*/
typedef struct hdr_10_infoframe_s
{
    uint8_t infoframe_type_code      ;
    uint8_t infoframe_version_number ;
    uint8_t length_of_info_frame     ;
    uint8_t data_byte_1              ;
    uint8_t data_byte_2              ;
    uint8_t display_primaries_x_0_LSB;
    uint8_t display_primaries_x_0_MSB;
    uint8_t display_primaries_y_0_LSB;
    uint8_t display_primaries_y_0_MSB;
    uint8_t display_primaries_x_1_LSB;
    uint8_t display_primaries_x_1_MSB;
    uint8_t display_primaries_y_1_LSB;
    uint8_t display_primaries_y_1_MSB;
    uint8_t display_primaries_x_2_LSB;
    uint8_t display_primaries_x_2_MSB;
    uint8_t display_primaries_y_2_LSB;
    uint8_t display_primaries_y_2_MSB;
    uint8_t white_point_x_LSB        ;
    uint8_t white_point_x_MSB        ;
    uint8_t white_point_y_LSB        ;
    uint8_t white_point_y_MSB        ;
    uint8_t max_display_mastering_luminance_LSB;
    uint8_t max_display_mastering_luminance_MSB;
    uint8_t min_display_mastering_luminance_LSB;
    uint8_t min_display_mastering_luminance_MSB;
    uint8_t max_content_light_level_LSB        ;
    uint8_t max_content_light_level_MSB        ;
    uint8_t max_frame_average_light_level_LSB  ;
    uint8_t max_frame_average_light_level_MSB  ;
} hdr_10_infoframe_t;

typedef struct edid_info_s
{
    int edid_min;
    int edid_max;
}edid_info_t;

typedef enum {
    display_out_sdr_normal,
    display_out_sdr_authentication,
    display_out_hdr10,
    display_out_dolby_ipt,
    display_out_dolby_yuv,
}display_out_type_t;

typedef struct target_info_s{
    uint32_t w,h;
    int16_t Contrast, Brightness;
    display_out_type_t tgt_type;
}target_info_t;

typedef enum {
    src_video_sdr,
    src_video_hdr10,
    src_video_dolby_yuv,
    src_video_dolby_ipt,
}src_video_type_t;

typedef struct src_videoinfo_s{
    uint32_t   w,h;
    uint32_t   bits;
    RPU_S   stRpu;
    chroma_format_t  chroma_format;
    range_t   range_type;
    int dovi_src_min;    /*dovi_src_min   Minimum source display luminance from DoVi metadata, in 12-bit PQ encoding*/
    int dovi_src_max;  /*dovi_src_max  Maximum source display luminance from DoVi metadata, in 12-bit PQ encoding*/
    src_video_type_t video_type;
    hdr10_param_t   hdr10_param;
}src_videoinfo_t;

typedef struct src_grcinfo_s{
    uint32_t w,h;
    int graphics_on;
    int graphic_min;
    int graphic_max;
}src_grcinfo_t;

/********************************************************************************
structure for CMD_GET_VERSION_INFO 
*********************************************************************************/
typedef struct dolby_vision_info_s{
    char *pbuild_time;
    char *pversion;
    char *puser_name;
    uint32_t user_id[4];
}dolby_vision_info_t;

typedef struct commit_regs_s
{
    dolby_coeff_s stComposer;
    dolby_coeff_s stDmMetadata;
    dolby_coeff_s stDmKs;//This structure has been adaptered to 64-bit issue.
    dolby_coeff_s stHdr10InfoFrm;
    dolby_coeff_s stUpdateMetadata;
    unsigned int  u32TotalLen;
}dolby_commit_regs_s;

typedef struct generate_config_para_in_s
{
    dolby_coeff_s   stRegsBuffer; /* buffer mpi has been malloc, para out will use this buffer to store composer/dmKs,etc.*/
    src_videoinfo_t stSrcVideoInfo;
    target_info_t   stTargetInfo;
    src_grcinfo_t   stSrcGfxInfo;
    edid_info_t     stEdidInfo;
}cmd_generate_config_para_in_s;

typedef struct generate_config_para_out_s
{
    dolby_commit_regs_s stCommitRegs;
}cmd_generate_config_para_out_s;

/********************************************************************************
command for dolby lib
*********************************************************************************/
typedef enum hiDOLBY_LIB_COMMAND_E
{
    /* arg1 is para in, arg2 is para out. */
    CMD_LIB_INIT  = 0x0,      /* arg1:null, arg2:null. */
    CMD_LIB_DEINIT,           /* arg1:null, arg2:null. */
    CMD_GET_VERSION_INFO,     /* arg1:null, arg2:dolby_vision_info_t. */
    CMD_GENERATE_CONFIG,      /* arg1:cmd_generate_config_para_in_s, arg2:cmd_generate_config_para_out_s*/
    CMD_BUTT
}HI_DOLBY_LIB_COMMAND_E;

int dolby_lib_wrap_interface(HI_DOLBY_LIB_COMMAND_E enCmd, 
                                     void *pstParaIn,
                                     void *pstParaOut);


typedef int (*FN_dolby_lib_wrap_interface)(HI_DOLBY_LIB_COMMAND_E enCmd, 
                                     void *pstParaIn,
                                     void *pstParaOut);

typedef struct
{
    FN_dolby_lib_wrap_interface  pfn_dolby_lib_wrap_interface;
}DOLBY_UNIVERSAL_FUN_S;


