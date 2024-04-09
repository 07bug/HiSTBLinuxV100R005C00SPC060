//**********************************************************************
//
// Copyright(c)2008, Hisilicon Technologies Co., Ltd
// All rights reserved.
//
// File Name   : vdp_define.h
// Author      : sdk
// Email       :
// Data        : 2012/10/17
// Version     : v1.0
// Abstract    : header of vdp define
//
// Modification history
//----------------------------------------------------------------------
// Version       Data(yyyy/mm/dd)      name
// Description
//
//
//
//
//
//**********************************************************************

#ifndef _VDP_DEFINE_H_
#define _VDP_DEFINE_H_

#include "hi_type.h"
#include "xdp_define.h"

//-----------------------------------
//System
//-----------------------------------
typedef enum
{
    VDP_MASTER0 = 0,
    VDP_MASTER1 = 1,
    VDP_MASTER2 = 2,
    VDP_MASTER3 = 3,
    VDP_MASTER_BUTT

} VDP_MASTER_E;

typedef enum
{
    VDP_AXI_EDGE_MODE_128  = 0,
    VDP_AXI_EDGE_MODE_256 ,
    VDP_AXI_EDGE_MODE_1024,
    VDP_AXI_EDGE_MODE_2048,
    VDP_AXI_EDGE_MODE_4096,
    VDP_AXI_EDGE_MODE_BUTT
} VDP_AXI_EDGE_MODE_E;

typedef enum tagVDP_MASTER_ARB_MODE_E
{
    VDP_MASTER_ARB_MODE_ASK = 0 ,
    VDP_MASTER_ARB_MODE_GFX_PRE,
    VDP_MASTER_ARB_MODE_BUTT,
} VDP_MASTER_ARB_MODE_E;

typedef enum tagVDP_AXI_CMD_E
{
    VDP_AXI_CMD_RID0 = 0,
    VDP_AXI_CMD_RID1,
    VDP_AXI_CMD_WID0,

    VDP_AXI_CMD_RID0OTD,
    VDP_AXI_CMD_RID1OTD,
    VDP_AXI_CMD_WID0OTD,

    VDP_AXI_CMD_BUTT
} VDP_AXI_CMD_E;

typedef enum
{
    VDP_INT_CHN0 = 1,
    VDP_INT_CHN1    ,
    VDP_INT_CHN2    ,//DSD0
    VDP_INT_WBC_HD0 ,
    VDP_INT_WBC_GP0 ,
    VDP_INT_WBC_G0  ,
    VDP_INT_WBC_G4  ,
    VDP_INT_WBC_ME  ,
    VDP_INT_WBC_FI  ,
    VDP_INT_WBC_BMP ,
    VDP_INT_HC_BMP ,
    VDP_INT_WBC_ALL ,
    VDP_INT_RM_CHN0 ,//for RM_Enable
    VDP_INT_RM_CHN1 ,//for RM_Enable
    VDP_INT_RM_CHN2 ,//for RM_Enable
    VDP_INT_UT,
    VDP_INT_CHN0_2,  //for low mem int
    VDP_INT_DTV_BACK,  //for low mem int
    VDP_INT_DTV_FRM_CHANGE,  //for low mem int
    VDP_INT_DTV_START,  //for low mem int

    WRAP_INT
} INT_VECTOR;

typedef enum tagVDP_INTMSK_E
{
    VDP_INTMSK_NONE        = 0,

    VDP_INTMSK_DHD0_VTTHD  = 0x1,
    VDP_INTMSK_DHD0_VTTHD2 = 0x2,
    VDP_INTMSK_DHD0_VTTHD3 = 0x4,
    VDP_INTMSK_DHD0_UFINT  = 0x8,

    VDP_INTMSK_DHD1_VTTHD  = 0x10,
    VDP_INTMSK_DHD1_VTTHD2 = 0x20,
    VDP_INTMSK_DHD1_VTTHD3 = 0x40,
    VDP_INTMSK_DHD1_UFINT  = 0x80,

    VDP_INTMSK_WBC_GP0_INT = 0x100,
    VDP_INTMSK_WBC_HD0_INT = 0x200,
    VDP_INTMSK_WBC_G0_INT  = 0x400,
    VDP_INTMSK_WBC_G4_INT  = 0x800,

    VDP_INTMSK_VDAC0_INT   = 0x1000,
    VDP_INTMSK_VDAC1_INT   = 0x2000,
    VDP_INTMSK_VDAC2_INT   = 0x4000,
    VDP_INTMSK_VDAC3_INT   = 0x8000,

    VDP_INTMSK_DSD0_VTTHD  = 0x10000,
    VDP_INTMSK_DSD0_UFINT  = 0x20000,

    VDP_INTMSK_DTV_BACK_INT         = 0x100000,
    VDP_INTMSK_DTV_FRM_CHANGE_INT   = 0x200000,
    VDP_INTMSK_DTV_START_INT        = 0x400000,
    //VDP_INTMSK_VSDRRINT    = 0x100000,
    //VDP_INTMSK_VADRRINT    = 0x200000,
    //VDP_INTMSK_VHDRRINT    = 0x400000,
    VDP_INTMSK_G0RRINT     = 0x800000,

    VDP_INTMSK_G1RRINT     = 0x1000000,

    VDP_INTMSK_LOWDLY_INT  = 0x20000000,
    VDP_INTMSK_UTENDINT    = 0x40000000,
    VDP_INTMSK_BUSEERINT   = 0x80000000,

    HAL_INTMSK_ALL         = 0xffffffff

} VDP_INTMSK_E;

typedef enum tagVDP_INT_E
{
    VDP_INT_VTTHD  = 1,
    VDP_INT_VTTHD2 = 2,
    VDP_INT_VTTHD3 = 3,
    VDP_INT_BUTT
} VDP_INT_E;


typedef enum tagVDP_LAYER_VID_E
{
    VDP_LAYER_VID0  = 0,
    VDP_LAYER_VID1  = 1,
    VDP_LAYER_VID2  = 2,
    VDP_LAYER_VID3  = 3,
    VDP_LAYER_VID4  = 4,
    VDP_LAYER_VID5  = 5,
    VDP_LAYER_VID6  = 6,//for FI pixel
    VDP_LAYER_VID7  = 7,//for FI info

    VDP_LAYER_VID_BUTT

} VDP_LAYER_VID_E;

typedef enum tagVDP_LAYER_GFX_E
{
    VDP_LAYER_GFX0  = 0,
    VDP_LAYER_GFX1  = 1,
    VDP_LAYER_GFX2  = 2,
    VDP_LAYER_GFX3  = 3,

    VDP_LAYER_GFX_BUTT

} VDP_LAYER_GFX_E;

typedef enum tagVDP_LAYER_WBC_E
{
    VDP_LAYER_WBC_HD0  = 0,
    VDP_LAYER_WBC_GP0  ,
    VDP_LAYER_WBC_OD   ,
    VDP_LAYER_WBC_G0   ,
    VDP_LAYER_WBC_G4   ,
    VDP_LAYER_WBC_ME   ,
    VDP_LAYER_WBC_FI   ,
    VDP_LAYER_WBC_BMP  ,
    VDP_LAYER_HC_BMP   ,

    VDP_LAYER_WBC_BUTT

} VDP_LAYER_WBC_E;

typedef enum tagVDP_CHN_E
{
    VDP_CHN_DHD0    = 0,
    VDP_CHN_DHD1    = 1,
    VDP_CHN_DSD0    = 2,
    VDP_CHN_WBC0    = 3,
    VDP_CHN_WBC1    = 4,
    VDP_CHN_WBC2    = 5,
    VDP_CHN_WBC3    = 6,
    VDP_CHN_NONE    = 7,
    VDP_CHN_BUTT

} VDP_CHN_E;

typedef enum tagVDP_DATA_RMODE_E
{
    VDP_RMODE_INTERFACE   = 0,
    VDP_RMODE_INTERLACE   = 0,
    VDP_RMODE_PROGRESSIVE = 1,
    VDP_RMODE_TOP         = 2,
    VDP_RMODE_BOTTOM      = 3,
    VDP_RMODE_PRO_TOP     = 4,
    VDP_RMODE_PRO_BOTTOM  = 5,
    VDP_RMODE_BUTT

} VDP_DATA_RMODE_E;

typedef enum
{
    VDP_RMODE_3D_INTF   = 0,
    VDP_RMODE_3D_SRC    = 1,
    VDP_RMODE_3D_BUTT

} VDP_RMODE_3D_E;


typedef enum tagVDP_PROC_FMT_E
{
    VDP_PROC_FMT_SP_420      = 0x0,
    VDP_PROC_FMT_SP_422      = 0x1,
    VDP_PROC_FMT_SP_444      = 0x2,//plannar,in YUV color domain
    VDP_PROC_FMT_SP_400      = 0x3,//plannar,in YUV color domain
    VDP_PROC_FMT_RGB_888     = 0x3,//package,in RGB color domain
    VDP_PROC_FMT_RGB_444     = 0x4,//plannar,in RGB color domain

    VDP_PROC_FMT_BUTT

} VDP_PROC_FMT_E;

typedef struct
{
    HI_U32 u32SX;
    HI_U32 u32X;
    HI_U32 u32Y;

    HI_U32 u32Wth;
    HI_U32 u32Hgt;

} VDP_RECT_S;

typedef enum
{
    VDP_TESTPTTN_MODE_STATIC  ,
    VDP_TESTPTTN_MODE_RAND    ,
    VDP_TESTPTTN_MODE_DYNAMIC ,
    VDP_TESTPTTN_MODE_BUTT
} VDP_TESTPTTN_MODE_E;


//-----------------------------------
//video layer
//-----------------------------------
typedef enum tagVDP_DATA_WTH
{
    VDP_DATA_WTH_8  = 0,
    VDP_DATA_WTH_10 = 1,
    VDP_DATA_WTH_12 = 2,
    VDP_DATA_WTH_BUTT
} VDP_DATA_WTH;

typedef enum tagVDP_REQ_LENGHT
{
    VDP_REQ_LENGTH_16 = 0,
    VDP_REQ_LENGTH_8  = 1,
    VDP_REQ_LENGTH_BUTT
} VDP_REQ_LENGTH_E;

typedef enum tagVDP_UVORDER_E
{
    VDP_UVORDER_U_FIRST = 0,
    VDP_UVORDER_V_FIRST = 1,
    VDP_UVORDER_BUTT
} VDP_UVORDER_E;

typedef enum tagVDP_VID_IFMT_E
{
    VDP_VID_IFMT_SP_400      = 0x1,
    VDP_VID_IFMT_SP_420      = 0x3,
    VDP_VID_IFMT_SP_422      = 0x4,
    VDP_VID_IFMT_SP_444      = 0x5,
    VDP_VID_IFMT_SP_TILE     = 0x6,
    VDP_VID_IFMT_SP_TILE_64  = 0x7,
    VDP_VID_IFMT_PKG_UYVY    = 0x9,
    VDP_VID_IFMT_PKG_YUYV    = 0xa,
    VDP_VID_IFMT_PKG_YVYU    = 0xb,
    VDP_VID_IFMT_PKG_12      = 0xc,
    VDP_VID_IFMT_RGB_888     = 0x8,
    VDP_VID_IFMT_PKG_YUV444  = 0xe,
    VDP_VID_IFMT_ARGB_8888   = 0xf,
    VDP_VID_IFMT_BUTT

} VDP_VID_IFMT_E;

typedef enum tagVDP_VID_DATA_FMT_E
{
    VDP_VID_DATA_FMT_LINEAR  = 0x0,
    VDP_VID_DATA_FMT_TILE    = 0x1,
    VDP_VID_DATA_FMT_PKG     = 0x2,
    VDP_VID_DATA_FMT_BUTT

} VDP_VID_DATA_FMT_E;

typedef enum tagVDP_VID_DATA_TYPE_E
{
    VDP_VID_DATA_TYPE_YUV400   = 0x1,
    VDP_VID_DATA_TYPE_YUV420   = 0x2,
    VDP_VID_DATA_TYPE_YUV422   = 0x3,
    VDP_VID_DATA_TYPE_YUV444   = 0x4,
    VDP_VID_DATA_TYPE_RGB888   = 0x5,
    VDP_VID_DATA_TYPE_ARGB8888 = 0x6,
    VDP_VID_DATA_TYPE_BUTT

} VDP_VID_DATA_TYPE_E;

typedef enum tagVDP_DRAW_MODE_E
{
    VDP_DRAW_MODE_1 = 0,
    VDP_DRAW_MODE_2 = 1,
    VDP_DRAW_MODE_4 = 2,
    VDP_DRAW_MODE_8 = 3,

    VDP_DRAW_MODE_BUTT
} VDP_DRAW_MODE_E;

typedef enum tagVDP_CMP_COMPONENT_E
{
    VDP_CMP_COMPONENT_Y    = 0,
    VDP_CMP_COMPONENT_C    = 1,
    VDP_CMP_COMPONENT_AR   = 2,
    VDP_CMP_COMPONENT_GB   = 3,
    VDP_CMP_COMPONENT_YUV  = 4,
    VDP_CMP_COMPONENT_A    = 5,
    VDP_CMP_COMPONENT_R    = 6,
    VDP_CMP_COMPONENT_G    = 7,
    VDP_CMP_COMPONENT_B    = 8,

    VDP_CMP_COMPONENT_BUTT
} VDP_CMP_COMPONENT_E;

//-----------------------------------
//graphics layer
//-----------------------------------
typedef enum tagVDP_GFX_IFMT_E
{
    VDP_GFX_IFMT_CLUT_1BPP   = 0x00,
    VDP_GFX_IFMT_CLUT_2BPP   = 0x10,
    VDP_GFX_IFMT_CLUT_4BPP   = 0x20,
    VDP_GFX_IFMT_CLUT_8BPP   = 0x30,

    VDP_GFX_IFMT_ACLUT_44    = 0x38,

    VDP_GFX_IFMT_RGB_444     = 0x40,
    VDP_GFX_IFMT_RGB_555     = 0x41,
    VDP_GFX_IFMT_RGB_565     = 0x42,

    VDP_GFX_IFMT_PKG_UYVY    = 0x43,
    VDP_GFX_IFMT_PKG_YUYV    = 0x44,
    VDP_GFX_IFMT_PKG_YVYU    = 0x45,

    VDP_GFX_IFMT_ACLUT_88    = 0x46,
    VDP_GFX_IFMT_ARGB_4444   = 0x48,
    VDP_GFX_IFMT_ARGB_1555   = 0x49,

    VDP_GFX_IFMT_RGB_888     = 0x50,//24bpp
    VDP_GFX_IFMT_YCBCR_888   = 0x51,//24bpp
    VDP_GFX_IFMT_ARGB_8565   = 0x5a,//24bpp

    VDP_GFX_IFMT_KRGB_888    = 0x60,
    VDP_GFX_IFMT_ARGB_8888   = 0x68,
    VDP_GFX_IFMT_AYCBCR_8888 = 0x69,

    VDP_GFX_IFMT_RGBA_4444   = 0xc8,
    VDP_GFX_IFMT_RGBA_5551   = 0xc9,
    VDP_GFX_IFMT_RGBA_5658   = 0xda,//24bpp
    VDP_GFX_IFMT_RGBA_8888   = 0xe8,
    VDP_GFX_IFMT_YCBCRA_8888 = 0xe9,
    VDP_GFX_IFMT_ABGR_8888   = 0xef,

    VDP_GFX_IFMT_STILL_888   = 0x100, // only use by environment

    VDP_GFX_IFMT_BUTT

} VDP_GFX_IFMT_E;

typedef enum tagVDP_GP_ORDER_E
{
    VDP_GP_ORDER_NULL     = 0x0,
    VDP_GP_ORDER_CSC      = 0x1,
    VDP_GP_ORDER_ZME      = 0x2,
    VDP_GP_ORDER_CSC_ZME  = 0x3,
    VDP_GP_ORDER_ZME_CSC  = 0x4,

    VDP_GP_ORDER_BUTT
} VDP_GP_ORDER_E;

typedef enum tagVDP_GFX_BITEXTEND_E
{
    VDP_GFX_BITEXTEND_1ST =   0,
    VDP_GFX_BITEXTEND_2ND = 0x2,
    VDP_GFX_BITEXTEND_3RD = 0x3,

    VDP_GFX_BITEXTEND_BUTT
} VDP_GFX_BITEXTEND_E;

typedef struct
{
    HI_U32  uAData  ;
    HI_U32  uRData  ;
    HI_U32  uGData  ;
    HI_U32  uBData  ;
} VDP_GFX_LUT_DATA_S;

typedef struct tagVDP_GFX_CKEY_S
{
    HI_U32 u32Key_r_min;
    HI_U32 u32Key_g_min;
    HI_U32 u32Key_b_min;

    HI_U32 u32Key_r_max;
    HI_U32 u32Key_g_max;
    HI_U32 u32Key_b_max;

    HI_U32 u32Key_r_msk;
    HI_U32 u32Key_g_msk;
    HI_U32 u32Key_b_msk;

    HI_U32 bKeyMode;

    //    HI_U32 u32KeyAlpha; //no use

} VDP_GFX_CKEY_S;

typedef struct tagVDP_GFX_MASK_S
{
    HI_U32 u32Mask_r;
    HI_U32 u32Mask_g;
    HI_U32 u32Mask_b;

} VDP_GFX_MASK_S;

typedef enum
{
    VDP_REQ_CTRL_16BURST_1,
    VDP_REQ_CTRL_16BURST_2,
    VDP_REQ_CTRL_16BURST_4,
    VDP_REQ_CTRL_16BURST_8,
    VDP_REQ_CTRL_BUTT
} VDP_REQ_CTRL_E;

//-----------------------------------
//wbc layer
//-----------------------------------
typedef enum tagVDP_WBC_3D_MODE_E
{
    VDP_WBC_3D_MODE_TWOEYE = 0,
    VDP_WBC_3D_MODE_LEFTEYE = 2,
    VDP_WBC_3D_MODE_RIGHTEYE = 3,

    VDP_WBC_3D_MODE_BUTT
} VDP_WBC_3D_MODE_E;

//-----------------------------------
//channel & interface
//-----------------------------------
typedef enum tagVDP_DISP_MODE_E
{
    VDP_DISP_MODE_2D  = 0,
    VDP_DISP_MODE_SBS = 1,
    VDP_DISP_MODE_LBL = 2,
    VDP_DISP_MODE_FS  = 3,
    VDP_DISP_MODE_TAB = 4,
    VDP_DISP_MODE_FP  = 5,

    VDP_DISP_MODE_BUTT
} VDP_DISP_MODE_E;

typedef enum tagVDP_DISP_INTF_E
{
    VDP_DISP_INTF_HDMI   = 0,
    VDP_DISP_INTF_VGA    = 1,
    VDP_DISP_INTF_BT1120 = 2,
    //VDP_DISP_INTF_DATE   = 3,
    VDP_DISP_INTF_SDDATE = 3,
    VDP_DISP_INTF_CVBS   = 3,
    VDP_DISP_INTF_LCD    = 4,
    VDP_DISP_INTF_HDDATE = 5,
    VDP_DISP_INTF_BUTT   = 6,
} VDP_DISP_INTF_E;

typedef enum tagVDP_DISP_INTF_OFMT_E
{
    VDP_DISP_INTF_OFMT_RGB888 = 0 ,
    VDP_DISP_INTF_OFMT_YUV422  ,
    VDP_DISP_INTF_OFMT_BUTT  ,
} VDP_DISP_INTF_OFMT_E;


typedef struct tagVDP_BKG_S
{
    HI_U32 u32BkgY;
    HI_U32 u32BkgU;
    HI_U32 u32BkgV;
    HI_U32 u32BkgA;
    HI_U32 bBkType;

} VDP_BKG_S;

typedef enum tagVDP_CHKSUM_E
{
    VDP_CHKSUM_A = 0,
    VDP_CHKSUM_Y = 1,
    VDP_CHKSUM_U = 2,
    VDP_CHKSUM_V = 3,

    VDP_CHKSUM_BUTT
} VDP_CHKSUM_E;


typedef enum tagSTI_FILE_TYPE_E
{
    STI_FILE_DATA_VID0 = 0 ,
    STI_FILE_DATA_VID1     ,
    STI_FILE_DATA_VID2     ,
    STI_FILE_DATA_VID3     ,
    STI_FILE_DATA_VID4     ,
    STI_FILE_DATA_GFX0     ,
    STI_FILE_DATA_GFX1     ,
    STI_FILE_DATA_GFX2     ,
    STI_FILE_DATA_GFX3     ,
    STI_FILE_DATA_GFX4     ,

    STI_FILE_COEF_OD       ,
    STI_FILE_COEF_CLUT     ,

    STI_FILE_V0_Y,
    STI_FILE_V0_C,

    STI_FILE_CMP_V0_Y_HEAD ,
    STI_FILE_CMP_V0_Y_DATA ,
    STI_FILE_CMP_V0_Y_EXT  ,
    STI_FILE_CMP_V0_C_HEAD ,
    STI_FILE_CMP_V0_C_DATA ,
    STI_FILE_CMP_V0_C_EXT  ,

    STI_FILE_CMP_V1_Y_HEAD ,
    STI_FILE_CMP_V1_Y_DATA ,
    STI_FILE_CMP_V1_Y_EXT  ,
    STI_FILE_CMP_V1_C_HEAD ,
    STI_FILE_CMP_V1_C_DATA ,
    STI_FILE_CMP_V1_C_EXT  ,

    STI_FILE_CMP_G0_AR ,
    STI_FILE_CMP_G0_GB ,
    STI_FILE_CMP_G1_AR ,
    STI_FILE_CMP_G1_GB ,

    STI_FILE_ESL ,
    STI_FILE_MMU_MAP  ,
    STI_FILE_MMU_PAGE ,

    STI_FILE_TYPE_BUTT
} STI_FILE_TYPE_E;


#endif
