//**********************************************************************
// File Name   : vdp_define.h
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

#include "vdp_ip_define.h"
#include "xdp_define.h"
#include "vdp_mac_define.h"
//#include <linux/kernel.h>

#define VDP_HI3798CV200
#define VDP_HI3798MV200
#define VDP_HI3798MV200T
#define VDP_HDR_MODE 0
#define VDP_DB_HDR_MODE 0
#define VDP_HDR10    1

#define UNDERFLOW_MASK          0
#define INTF_PAUSE              0
//-----------------------------------
//mmu define
//-----------------------------------
#define MMU_TEST                0      //when mmu test ,false 1

#define VDP_MMU_WR_ERR_DEFAULT_ADDR    0x00100f00
#define VDP_MMU_RD_ERR_DEFAULT_ADDR    0x00101f00

#define VDP_MMU_WR_ERR_DEFAULT_SADDR   0x00200f00
#define VDP_MMU_RD_ERR_DEFAULT_SADDR   0x00201f00

//for mmu norm test
#define VDP_MMU_PAGE_START_ADDR        0xffc00000//4G/4k=0x100000(1M)
#define MMU_VA_START_ADDR              0x0
#define MMU_VA_END_ADDR                0x7fffffff
#define MMU_PA_START_ADDR              0x0
#define MMU_PA_END_ADDR                0x7fffffff

//for mmu secure test
#define VDP_MMU_UNSAFE_PAGE_START_ADDR 0xffc00000
#define VDP_MMU_SAFE_PAGE_START_ADDR   0xffd40000

#define MMU_VA_UNSAFE_START_ADDR       0x0
#define MMU_VA_UNSAFE_END_ADDR         0x4fffffff
#define MMU_VA_SAFE_START_ADDR         0x50000000
#define MMU_VA_SAFE_END_ADDR           0x7fffffff

#define MMU_PA_UNSAFE_START_ADDR       0x0
#define MMU_PA_UNSAFE_END_ADDR         0x4fffffff
#define MMU_PA_SAFE_START_ADDR         0x50000000
#define MMU_PA_SAFE_END_ADDR           0x7fffffff

//-----------------------------------
//debug define
//-----------------------------------
#define PC_TEST         0
#define AUTO_CFG_FPGA   0
#define EDA_TEST        0
#define BT_TEST         0

#define FPGA_TEST       1
#define UT_TEST         0
#define VDP_CBB_FPGA    1
#define VDP_C_COMPILE   0
#define DAMNED_DEBUG_EN 1

//-----------------------------------
//architecture define
//-----------------------------------
#define VDP_CHK_SUM VDP_BASE_ADDR + 0xc5e0
#define ONE_CHK_CHN (3+2*3)
#define MAX_CHK_CHN (ONE_CHK_CHN*CHN_MAX)
#define MAX_CHK_FRM  10000

#define VID_MAX        2
#define GFX_MAX        2
#define WBC_MAX        1
#define CHN_MAX        3
#define INTF_MAX       4
#define GP_MAX         2
#define VP_MAX         2
#define CBM_MAX        5

#define SD0_EN         0
#define PARA_MAX       2

//layer define
#define VP0_EN         1
#define VP1_EN         0
#define VP2_EN         0
#define GP0_EN         1
#define GP1_EN         0
#define WBC_GP0_EN     0
#define WBC_DHD0_EN    1
#define INTF_EN        0

//multi region define
#define VID_REGION_NUM 4

#define OFL_INT        0

//low cost cmp for S5V200
#define LOW_COST_CMP   1
#define VDP_TILE_DCMP  1
#define VDP_LINE_HUFF_DCMP  1
#define VDP_LINE_HUFF_CMP   1

#define VID_PIXEL_COPY  0

#ifdef VPSS_VDP_TEST
    #define VID_WBC_TNR     1
#else
    #define VID_WBC_TNR     0
#endif

#define VID_WBC_TNR_CMP 1

//gfx cmp for hi3798
#define OSDCMPTODUT    1

#define GCVM_COEF_A_SCALE         5
#define GDM_CSC_ALPHA_WIDTH       8
#define GDM_CSC_ALPHA_MAX_VALUE   ((1<<GDM_CSC_ALPHA_WIDTH)-1)
#define GDM_GMM_LUT_SIZE          64
#define CLIP_NEW(a_, mn_, mx_)  ( ((a_) >= (mn_)) ? ( ((a_) <= (mx_)) ? (a_) : (mx_) ) : (mn_) )

#define VDP_ASSERT(expr)  if(!(expr)) {printk("Error at :\n >>>>>>>>>>Function : %s\n >>>>>>>>>>LINE = %d\n >>>>>>>>>>Condition: %s\n",__FUNCTION__,__LINE__, #expr);  ; }

#ifdef _DISP_PLATFORM_BOOT_
  #define VDP_PRINT   printf
#else

  #if (EDA_TEST || VDP_C_COMPILE)
    #include <stdio.h>
    #define VDP_PRINT   printf
  #else
    #define VDP_PRINT   printk
  #endif

#endif//_DISP_PLATFORM_BOOT_

#if FPGA_TEST
    #define W_4096    4096
    #define W_2160P   3840
    #define H_2160P   2160
    #define W_1600P   2560
    #define H_1600P   1600
    #define W_1080P   1920
    #define H_1080P   1080
    #define W_720P    1280
    #define H_720P    720
    #define W_D1      720
    #define H_D1      480
    #define W_576P    720
    #define H_576P    576
    #define W_480P    720
    #define H_480P    480
    #define W_HVGA    480
    #define H_HVGA    320
    #define W_CIF     352
    #define H_CIF     288
    #define W_QCIF    176
    #define H_QCIF    144
    #define W_HC      128
    #define H_HC      128
#endif


#define DISP_BASE_ADDRESS 0xf8cc0000UL
#define DISP_INT_NUMBER   122

typedef enum tagDISP_VENC_E
{
    DISP_VENC_HDATE0 = 0,
    DISP_VENC_SDATE0,
    DISP_VENC_VGA0,
    DISP_VENC_MAX
}DISP_VENC_E;


typedef enum tagVDP_RM_LAYER_E
{
    VDP_RM_LAYER_VID0 = 0,
    VDP_RM_LAYER_VID1,
    VDP_RM_LAYER_VID2,
    VDP_RM_LAYER_VID3,
    VDP_RM_LAYER_VID4,
    VDP_RM_LAYER_GFX0,
    VDP_RM_LAYER_GFX1,
    VDP_RM_LAYER_GFX2,
    VDP_RM_LAYER_GFX3,
    VDP_RM_LAYER_GFX4,
    VDP_RM_LAYER_WBC_HD0,
    VDP_RM_LAYER_WBC_GP0,
    VDP_RM_LAYER_GP0,
    VDP_RM_LAYER_GP1,
    VDP_RM_LAYER_VP0,
    VDP_RM_LAYER_TT,

} VDP_RM_LAYER_E;


#endif
