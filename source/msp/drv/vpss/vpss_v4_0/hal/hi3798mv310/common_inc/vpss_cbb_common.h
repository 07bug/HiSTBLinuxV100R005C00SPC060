//描述每个项目逻辑共性的部分，比如逻辑基地址，节点地址，位宽枚举，数据格式等。
//
//
#ifndef __VPSS_CBB_COMMON_H__
#define __VPSS_CBB_COMMON_H__

//#include <stdio.h>
//#include <string.h>
#include "hi_type.h"
//#include "hi_reg_common.h"
//#include "vpss_stt_reg.h"
#include "vpss_cbb_debug.h"
#include "xdp_ip_head.h"
#ifdef XDP_VPSS_FPGA
#else
#include "vpss_cbb_hal.h"
#include "hi_common.h"
#endif

#include "vpss_cbb_hal_die.h"

#define DEF_CBB_MAX_NODE_NUM VPSS_HAL_NODE_BUTT

#define VPSS_MULTI_VER 4096
#define VPSS_MULTI_HOR 1048576


typedef struct
{
    HI_U32 u32BasePhyAddr;   //逻辑物理基地址
    HI_U8 *pu8BaseVirAddr;   //逻辑虚拟基地址

    HI_U32 u32NodePhyAddr;   //DDR中节点物理基地址
    HI_U8 *pu8NodeVirAddr;   //DDR中节点虚拟基地址
} CBB_REG_ADDR_S;

typedef enum
{
    CBB_BITWIDTH_8BIT = 0,
    CBB_BITWIDTH_10BIT,
    CBB_BITWIDTH_12BIT,
    CBB_BITWIDTH_10BIT_CTS,
    CBB_BITWIDTH_BUTT,
} CBB_BITWIDTH_E;

typedef struct
{
    HI_U32 u32PhyAddr_YHead;
    HI_U32 u32PhyAddr_Y;
    HI_U8 *pu8VirAddr_YHead;
    HI_U8 *pu8VirAddr_Y;
    HI_BOOL bSmmu_Y;
    HI_BOOL bSmmu_YHead;

    HI_U32 u32PhyAddr_CHead;
    HI_U32 u32PhyAddr_C;
    HI_U8 *pu8VirAddr_CHead;
    HI_U8 *pu8VirAddr_C;
    HI_BOOL bSmmu_C;
    HI_BOOL bSmmu_CHead;

    HI_U32 u32Stride_Y;
    HI_U32 u32Stride_C;

    HI_U32  u32Head_Stride;
    HI_U32  u32Head_Size;
} CBB_FRAME_ADDR_S;

typedef enum
{
    INPUTFMT_LINEAR_SP420            = 0x0,
    INPUTFMT_SEMIPLANAR_422_2X1      = 0x1,
    INPUTFMT_TILE_SP420              = 0x2,
    INPUTFMT_400                     = 0x3,
    INPUTFMT_TILE_400                = 0x4,
    INPUTFMT_PLANAR_444              = 0x5,
    INPUTFMT_PLANAR_422_2X1          = 0x6,
    INPUTFMT_PLANAR_422_1X2          = 0x7,
    INPUTFMT_PLANAR_420              = 0x8,
    INPUTFMT_PLANAR_411              = 0x9,
    INPUTFMT_PLANAR_410              = 0xa,
    INPUTFMT_PACKAGE_422_YUYV        = 0xb,
    INPUTFMT_PACKAGE_422_YVYU        = 0xc,
    INPUTFMT_PACKAGE_422_UYVY        = 0xd,
    INPUTFMT_LINEAR_SP444            = 0x15,
    INPUTFMT_BUTT
} CBB_PIXEL_FMT_E;

typedef enum
{
    VPSS_REQ_LEN_16BURST = 0,
    VPSS_REQ_LEN_8BURST,
    VPSS_REQ_LEN_BUTT
} CBB_BURST_LENGTH_E;

typedef enum
{
    VPSS_REQ_NUM_1 = 0,
    VPSS_REQ_NUM_2 = 1,
    VPSS_REQ_NUM_4 = 2
} CBB_BURST_NUM_E;


typedef enum
{
    VPSS_SPLITE_MODE_128  = 0,
    VPSS_SPLITE_MODE_256 ,
    VPSS_SPLITE_MODE_1024,
    VPSS_SPLITE_MODE_2048,
    VPSS_SPLITE_MODE_4096,
    VPSS_SPLITE_MODE_BUTT
} CBB_SPLITE_MODE_E;

typedef enum
{
    AXI_BURST_LEN_16 = 0x0,
    AXI_BURST_LEN_8,
    AXI_BURST_LEN_4,
} CBB_AXI_BURST_LEN_E;

typedef struct
{
    HI_U32 u32NodePhyAddr[DEF_CBB_MAX_NODE_NUM];
    HI_U8 *pu8NodeVirAddr[DEF_CBB_MAX_NODE_NUM];
    HI_U32 u32NodeValid[DEF_CBB_MAX_NODE_NUM];
} CBB_START_CFG_S;

typedef struct
{
    HI_U32 u32ROutStd;
    HI_U32 u32WOutStd;
    HI_U32 u32Mid_enable;
    HI_U32 u32Arb_mode;
    CBB_SPLITE_MODE_E  enSplitMode;
} CBB_OUTSTANDING_S;

typedef struct
{
    CBB_BURST_LENGTH_E enBurstLen;
    CBB_BURST_NUM_E    enBurstNum;
} CBB_BUS_CTRL_S;

typedef enum
{
    /* vhd0通道垂直预缩放模式：
        0：垂直缩小2倍；
        1：垂直缩小4倍；
        2：垂直缩小8倍；
        3：抽底场。
    */
    CBB_FIR_X2 = 0,
    CBB_FIR_X4 = 1,
    CBB_FIR_X8 = 2,
    CBB_FIR_EXT_BOTTOM = 3, //extract bottom field
    CBB_FIR_BUTT,
} CBB_FIR_MODE_E;

typedef enum
{
    CBB_TUNOUT_2 = 0,
    CBB_TUNOUT_4 = 1,
    CBB_TUNOUT_8 = 2,
    CBB_TUNOUT_16 = 3,
    CBB_TUNOUT_BUTT,
} CBB_TUNOUT_MODE_E;


typedef enum
{
    CBB_COLOR_BLACK = 0,
    CBB_COLOR_RED,
    CBB_COLOR_WHITE,
    CBB_COLOR_GREEN,
    CBB_COLOR_BLUE,
    CBB_COLOR_YELLOW,
    CBB_COLOR_BUTT,
} CBB_COLOR_E;


typedef enum
{
    CBB_FREAM_BUF_8BIT = 0,
    CBB_FREAM_BUF_2BIT_LB,
    CBB_FREAM_BUF_CMP_HEADER,
    CBB_FREAM_BUF_BUTT,
    CBB_FREAM_BUF_CNT = CBB_FREAM_BUF_BUTT,
} CBB_FRAME_BUF_TYPE_E;


typedef enum
{
    CBB_ZME_MODE_HOR = 0 ,
    CBB_ZME_MODE_VER     ,

    CBB_ZME_MODE_HORL    ,
    CBB_ZME_MODE_HORC    ,
    CBB_ZME_MODE_VERL    ,
    CBB_ZME_MODE_VERC    ,

    CBB_ZME_MODE_ALL     ,
    CBB_ZME_MODE_NONL    ,

    CBB_ZME_MODE_BUTT
} CBB_ZME_MODE_E;

typedef enum
{
    CBB_RAM_MODE_SDI     = 0,
    CBB_RAM_MODE_HDI     = 1,
    CBB_RAM_MODE_SDP     = 2,
    CBB_RAM_MODE_HDP     = 3,
    CBB_RAM_MODE_OTHER   = 5,// rtt,4k 8bit,10bit
    CBB_RAM_MODE_BUTT,
} CBB_RAM_MODE_E;

#endif
