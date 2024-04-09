//******************************************************************************
//  Copyright (C), 2003-2011, Hisilicon Technologies Co., Ltd.
//
//******************************************************************************
// File Name       : vpss_define.h
// Version         : 1.0
// Author          : chenwanjun/c57657
// Created         : 2011-3-11
// Last Modified   :
// Description     :
// Function List   :
// History         :
// 1 Date          : 2011-3-11
//   Author        : chenwanjun/c57657
//   Modification  : Created file
//
//******************************************************************************
#ifndef _VPSS_DEFINE_H_
#define _VPSS_DEFINE_H_

#include "hi_type.h"
//#include "xdp_define.h"
#include "hi_reg_common.h"
#include "vdp_define.h"
//#include "xdp_debug.h"

typedef enum
{
    VPSS_ADDR_TYPE_DATA = 0,//2d left eye data
    VPSS_ADDR_TYPE_HEAD_TOP,//dcmp head data top
    VPSS_ADDR_TYPE_HEAD_BOT,//dcmp head data bottom
    VPSS_ADDR_TYPE_2B      ,//2bit
    VPSS_ADDR_TYPE_BUTT
} VPSS_ADDR_TYPE_E;

typedef struct
{
    XDP_TRIO_ADDR_S stAddr[VPSS_ADDR_TYPE_BUTT];

} VPSS_MAC_ADDR_CFG_S;

typedef enum
{
    VPSS_DITHER_MODE_RAND  = 0,
    VPSS_DITHER_MODE_ROUND ,
    VPSS_DITHER_MODE_BUTT
} VPSS_DITHER_MODE_E;

typedef struct
{
    HI_BOOL             bEn   ;
    VPSS_DITHER_MODE_E  enMode;
} VPSS_DITHER_CFG_S;

typedef enum
{
    VPSS_RCHN_ADDR_DATA = 0,//2d left eye data
    VPSS_RCHN_ADDR_HEAD_TOP,//dcmp head data top
    VPSS_RCHN_ADDR_HEAD_BOT,//dcmp head data bottom
    VPSS_RCHN_ADDR_2B      ,//2bit
    VPSS_RCHN_ADDR_BUTT
} VPSS_RCHN_ADDR_E;

typedef struct
{
    HI_BOOL bMuteEn   ;
    HI_U32  u32MuteY  ;
    HI_U32  u32MuteC  ;
} VPSS_MUTE_CFG_S;

typedef enum tagVDP_RM_COEF_MODE_E
{
    VDP_RM_COEF_MODE_TYP  = 0x0,
    VDP_RM_COEF_MODE_RAN  = 0x1,
    VDP_RM_COEF_MODE_MIN  = 0x2,
    VDP_RM_COEF_MODE_MAX  = 0x3,
    VDP_RM_COEF_MODE_ZRO  = 0x4,
    VDP_RM_COEF_MODE_CUS  = 0x5,
    VDP_RM_COEF_MODE_UP   = 0x6,
    VDP_RM_COEF_MODE_LBL_TYP = 0x7,
    VDP_RM_COEF_MODE_LBL_RAN = 0x8,
    VDP_RM_COEF_MODE_LBL_MIN = 0x9,
    VDP_RM_COEF_MODE_LBL_MAX = 0x10,
    //    VDP_RM_COEF_MODE_DOWN = 0x7,
    VDP_RM_COEF_MODE_BUTT
} VDP_RM_COEF_MODE_E;

typedef enum
{
    VPSS_PROC_COMP_YC_BOTH = 0,
    VPSS_PROC_COMP_Y_ONLY  = 1,
    VPSS_PROC_COMP_C_ONLY  = 2,
    VPSS_PROC_COMP_BUTT
} VPSS_PROC_COMP_E;

typedef enum
{
    VPSS_ROTATE_ANGLE_90  = 0,
    VPSS_ROTATE_ANGLE_270 = 1,
    VPSS_ROTATE_ANGLE_BUTT
} VPSS_ROTATE_ANGLE_E;

typedef enum
{
    V3MODE = 0,
    V5MODE,
    MAMODE,
    THRDRSMODE_BUTT
} THRDRS_MODE_E;

typedef enum
{
    VPSS_CHANNEL_NONE  = 0x00,
    VPSS_CHANNEL_VHD0,
    VPSS_CHANNEL_VHD1,
    VPSS_CHANNEL_VSD,
    VPSS_CHANNEL_VAD,
    VPSS_CHANNEL_RFR,
    VPSS_CHANNEL_IN,
    VPSS_CHANNEL_CUR,
    VPSS_CHANNEL_REF,
    VPSS_CHANNEL_NXT1,
    VPSS_CHANNEL_NXT2,
    VPSS_CHANNEL_NXT3,
    VPSS_CHANNEL_PR1,
    VPSS_CHANNEL_PR2,
    VPSS_CHANNEL_PR0,

    VPSS_CHANNEL_RMAD,
    VPSS_CHANNEL_WMAD,

    VPSS_CHANNEL_BUTT
} HAL_VPSS_INPUTOUTPUT_CHANNEL_E;

typedef struct
{
    //int hlpre_coef_pre0[2];
    //int vlpre_coef_pre0[2];
    //int hcpre_coef_pre0[2];
    //int vcpre_coef_pre0[4];
    //int hlcoef_pre0[17][8];
    //int hccoef_pre0[17][4];
    //int vlcoef_pre0[17][6];
    //int vccoef_pre0[17][4];
    //int hlpre_coef_pre1[2];
    //int vlpre_coef_pre1[2];
    //int hcpre_coef_pre1[2];
    //int vcpre_coef_pre1[4];
    int hlcoef_vad[17][8];
    int hccoef_vad[17][4];
    int vlcoef_vad[17][6];
    int vccoef_vad[17][4];
    int hlticoef_vad[17][8];
    int hcticoef_vad[17][4];
    int vlticoef_vad[17][2];
    int vcticoef_vad[17][2];
    int hlcoef_vsd[17][8];
    int hccoef_vsd[17][8];
    int vlcoef_vsd[17][6];
    int vccoef_vsd[17][6];
    int hlticoef_vsd[17][8];
    int hcticoef_vsd[17][4];
    int vlticoef_vsd[17][2];
    int vcticoef_vsd[17][2];
    //int vc_coef_bstr[2];
    //int hlpre_coef_lstr[2];
    //int vlpre_coef_lstr[2];
    //int hcpre_coef_lstr[2];
    //int vcpre_coef_lstr[4];
    int hlcoef_vhd0[17][6];
    int hccoef_vhd0[17][4];
    int vlcoef_vhd0[17][4];
    int vccoef_vhd0[17][4];
    int hlticoef_vhd0[17][8];
    int hcticoef_vhd0[17][4];
    int vlticoef_vhd0[17][2];
    int vcticoef_vhd0[17][2];
    int hlcoef_vhd1[17][8];
    int hccoef_vhd1[17][8];
    int vlcoef_vhd1[17][6];
    int vccoef_vhd1[17][6];
    int hlticoef_vhd1[17][8];
    int hcticoef_vhd1[17][4];
    int vlticoef_vhd1[17][2];
    int vcticoef_vhd1[17][2];
    int hlticoef_str[17][8];
    int hcticoef_str[17][4];
    int vlticoef_str[17][2];
    int vcticoef_str[17][2];
    int hlcoef_str[17][8];//======[32][8]
    int hccoef_str[17][8];
    int vlcoef_str[17][6];
    int vccoef_str[17][6];
    int hlcoef_h2fir[17][8];
    int hccoef_h2fir[17][4];
    int vlcoef_h2fir[17][6];
    int vccoef_h2fir[17][4];
    int hlcoef_hscl[17][8];
    int hccoef_hscl[17][8];
} CVPSSScalerCoef;


//----------------------------------------------------------------------
// Platform define, EDA and FPGA is difference
//----------------------------------------------------------------------
#define VPSS_PNEXT_ADDR 0x2fc
#define VPSS_BASE_ADDR 0xff1c0000
#define VPSS_BASE_ADDR_REG_TEST 0xff1c0000
#define VPSS_APB0_END_ADDR 0x5Fc
#define VPSS_APB0_START_ADDR 0x300
#define VPSS_APB1_START_ADDR 0xF000

//Channel define
#define RCHN_MAX       10
#define WCHN_MAX       10

//OFFSET define, for driver

//FROM VDP FILE

//-----------------------------------
//video layer
//-----------------------------------

#endif // _VPSS_DEFINE_H_

