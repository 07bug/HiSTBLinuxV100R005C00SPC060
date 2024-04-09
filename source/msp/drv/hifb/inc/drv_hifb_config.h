/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name          : hifb_config.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        :
Function List      :
History            :
Date                       Author                   Modification
2018/01/01                 sdk                       Created file
*************************************************************************************************/
#ifndef __DRV_HIFB_CONFIG_H__
#define __DRV_HIFB_CONFIG_H__

/*********************************add include here************************************************/

#include "hi_type.h"

/*************************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
   extern "C"
{
#endif
#endif /* __cplusplus */


/***************************** Macro Definition **************************************************/
#define CONFIG_HIFB_LAYER_0BUFFER    0
#define CONFIG_HIFB_LAYER_1BUFFER    1
#define CONFIG_HIFB_LAYER_2BUFFER    2
#define CONFIG_HIFB_LAYER_3BUFFER    3

#define CONFIG_HIFB_LAYER_MAXWIDTH         12288 /** 4096 * 3buffer **/
#define CONFIG_HIFB_LAYER_MAXHEIGHT        12288 /** 4096 * 3buffer **/
#define CONFIG_HIFB_LAYER_STRIDE           32768 /** need > w * 4 * 1.3 **/
#define CONFIG_HIFB_LAYER_BITSPERPIX       32

#define CONFIG_HIFB_STEREO_BUFFER_MAX_NUM       2
#ifdef CFG_HIFB_ANDROID_SUPPORT
    #define CONFIG_HIFB_LAYER_BUFFER_MAX_NUM    3
#else
    #define CONFIG_HIFB_LAYER_BUFFER_MAX_NUM    2
#endif

#define CONFIG_HIFB_CHN_OFFSET          0x400
#define CONFIG_HIFB_WBC_OFFSET          0x400

#if defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) \
 || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450) \
 || defined(CHIP_TYPE_hi3798mv300)
    #define CONFIG_HIFB_GFX_OFFSET     0x200
    #define CONFIG_HIFB_GP_OFFSET      0x800
#elif defined(CHIP_TYPE_hi3798mv310) || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_CTL_OFFSET     0x800
    #define CONFIG_HIFB_GFX_OFFSET     0x200
    #define CONFIG_HIFB_GP_OFFSET      0x100
#else
    #define CONFIG_HIFB_GFX_OFFSET     0x800
    #define CONFIG_HIFB_GP_OFFSET      0x800
#endif

#define CONFIG_VDP_SIZE                0xfff0


#define CONFIG_VDP_REG_BASEADDR                         (0xf8cc0000)

#if defined(CHIP_TYPE_hi3798cv200)  || defined(CHIP_TYPE_hi3798mv200)   \
  || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)   \
  || defined(CHIP_TYPE_hi3798mv300)
    #define CONFIG_HIFB_HD0_REG_BASEADDR                (0xf8cc7000)
    #define CONFIG_HIFB_GP0_REG_BASEADDR                (0xf8cc8000)
    #define CONFIG_HIFB_SD_LOGO_REG_BASEADDR            (0xf8cc7800)
    #define CONFIG_HIFB_WBC_SLAYER_REG_BASEADDR         (0xf8cc7800)
    #define CONFIG_HIFB_WBC_GP0_REG_BASEADDR            (0xf8cc9400)
#elif defined(CHIP_TYPE_hi3798mv310)  || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_HD0_REG_BASEADDR                (0xf8cc5000)
    #define CONFIG_HIFB_GP0_REG_BASEADDR                (0xf8cc6800)
    #define CONFIG_HIFB_SD_LOGO_REG_BASEADDR            (0xf8cc8000)
    #define CONFIG_HIFB_WBC_SLAYER_REG_BASEADDR         (0xf8cc8000)
    #define CONFIG_HIFB_WBC_GP0_REG_BASEADDR            (0xf8cca800)
#elif defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    #define CONFIG_HIFB_HD0_REG_BASEADDR                (0xf8cc6000)
    #define CONFIG_HIFB_GP0_REG_BASEADDR                (0xf8cc9000)
    #define CONFIG_HIFB_SD_LOGO_REG_BASEADDR            (0xf8cc8000)
    #define CONFIG_HIFB_WBC_SLAYER_REG_BASEADDR         (0xf8cc8000)
    #define CONFIG_HIFB_WBC_GP0_REG_BASEADDR            (0xf8cca800)
#else
    #define CONFIG_HIFB_HD0_REG_BASEADDR                (0xf8cc6000)
    #define CONFIG_HIFB_GP0_REG_BASEADDR                (0xf8cc9000)
    #define CONFIG_HIFB_SD_LOGO_REG_BASEADDR            (0xf8cc7800)
    #define CONFIG_HIFB_WBC_SLAYER_REG_BASEADDR         (0xf8cc8000)
    #define CONFIG_HIFB_WBC_GP0_REG_BASEADDR            (0xf8cca800)
#endif

#if defined(CHIP_TYPE_hi3716cv200)
    #define CONFIG_HIFB_GFX3_TO_GFX5
#endif

#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3716dv100)   \
    || defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)	\
    || defined(CHIP_TYPE_hi3798mv310)	\
    || defined(CHIP_TYPE_hi3796mv200)   \
    || defined(CHIP_TYPE_hi3716mv450)   \
    || defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3716mv420)   \
    || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_PRECISION_ZMERATIONH_12BITOFFSET          8
#else
    #define CONFIG_HIFB_PRECISION_ZMERATIONH_12BITOFFSET          0
#endif

#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3716dv100)   \
    || defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300) 	\
    || defined(CHIP_TYPE_hi3798mv310)	\
    || defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3796mv200)   \
    || defined(CHIP_TYPE_hi3716mv450)   \
    || defined(CHIP_TYPE_hi3716mv420)   \
    || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_GP0_ZME_HLC_OFFSET_ENABLE
#endif

#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3716dv100)   \
    || defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)	\
    || defined(CHIP_TYPE_hi3798mv310)	\
    || defined(CHIP_TYPE_hi3796mv200)   \
    || defined(CHIP_TYPE_hi3716mv450)   \
    || defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3716mv420)   \
    || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_ALG_G_HZME_PRECISION      1048576
    #define CONFIG_HIFB_ALG_G_VZME_PRECISION      4096
#else
    #define CONFIG_HIFB_ALG_G_HZME_PRECISION      4096
    #define CONFIG_HIFB_ALG_G_VZME_PRECISION      4096
#endif


#if     defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100) \
     || defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    #define CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT          2 /** (G0 G1) **/
    #define CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT          1 /** (G4)    **/
#elif defined(CHIP_TYPE_hi3798cv200)
    #define CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT          3 /** (G0 G1 G3) **/
    #define CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT          1 /** (G4) **/
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) \
     || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450)
    #define CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT          2 /** (G0 G1) **/
    #define CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT          1 /** (G4) **/
#elif defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT          2 /** (G0 G3) **/
    #define CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT          1 /** (G1) **/
#else
    #define CONFIG_HIFB_GP0_SUPPORT_GFX_COUNT          3 /** (G0 G1 G2)  **/
    #define CONFIG_HIFB_GP1_SUPPORT_GFX_COUNT          2 /** (G3(±‰G5) G4 G5) **/
#endif


#if defined(CHIP_TYPE_hi3798mv100)  || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100)   \
 || defined(CHIP_TYPE_hi3716mv410)  || defined(CHIP_TYPE_hi3716mv420)
    #define CONFIG_HIFB_ZME_ORDER_VH
#elif  defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) \
    || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450) \
    || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) \
    || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_ZME_ORDER_HV
#else
    #define CONFIG_HIFB_ZME_ORDER_HV
#endif


#if defined(CHIP_TYPE_hi3798mv100)   || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100)   \
 || defined(CHIP_TYPE_hi3716mv410)   || defined(CHIP_TYPE_hi3716mv420)   \
 || defined(CHIP_TYPE_hi3798cv200)   || defined(CHIP_TYPE_hi3798mv200)   \
 || defined(CHIP_TYPE_hi3796mv200)   || defined(CHIP_TYPE_hi3716mv450)   \
 || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)     \
 || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_EXTRACE_DISABLE
#endif


#if    defined(CHIP_TYPE_hi3798mv100)   \
    || defined(CHIP_TYPE_hi3796mv100)   \
    || defined(CHIP_TYPE_hi3716dv100)   \
    || defined(CHIP_TYPE_hi3798cv200)   \
    || defined(CHIP_TYPE_hi3798mv200)   \
    || defined(CHIP_TYPE_hi3798mv300)   \
    || defined(CHIP_TYPE_hi3798mv310)   \
    || defined(CHIP_TYPE_hi3716mv430)   \
    || defined(CHIP_TYPE_hi3796mv200)   \
    || defined(CHIP_TYPE_hi3716mv450)   \
    || defined(CHIP_TYPE_hi3716mv410)   \
    || defined(CHIP_TYPE_hi3716mv420)
    #define CONFIG_HIFB_USE_COMM_REGH
#endif


#ifndef HI_BUILD_IN_BOOT
    #if defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    #define CONFIG_HIFB_HD1_LAYER_16BIT_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_24BIT_FMT            0
    #define CONFIG_HIFB_HD1_LAYER_32BIT_FMT            0
    #define CONFIG_HIFB_HD1_LAYER_CLUT1_FMT            0
    #define CONFIG_HIFB_HD1_LAYER_CLUT2_FMT            0
    #define CONFIG_HIFB_HD1_LAYER_CLUT4_FMT            0
    #define CONFIG_HIFB_HD1_LAYER_CLUT8_FMT            0
    #else
    #define CONFIG_HIFB_HD1_LAYER_16BIT_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_24BIT_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_32BIT_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_CLUT1_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_CLUT2_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_CLUT4_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_CLUT8_FMT            1
    #endif
#else
    #define CONFIG_HIFB_HD1_LAYER_16BIT_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_24BIT_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_32BIT_FMT            1
    #define CONFIG_HIFB_HD1_LAYER_CLUT1_FMT            0
    #define CONFIG_HIFB_HD1_LAYER_CLUT2_FMT            0
    #define CONFIG_HIFB_HD1_LAYER_CLUT4_FMT            0
    #define CONFIG_HIFB_HD1_LAYER_CLUT8_FMT            0
#endif


#if    defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3716dv100) \
    || defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420)
    #define CONFIG_HIFB_HD0_LAYER_SUPPORT                  HI_TRUE
    #define CONFIG_HIFB_HD1_LAYER_SUPPORT                  HI_TRUE
    #define CONFIG_HIFB_HD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_HD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD0_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD1_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD0_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD1_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_CURSOR_LAYER_SUPPORT               HI_FALSE
#elif defined(CHIP_TYPE_hi3798cv200)
    #define CONFIG_HIFB_HD0_LAYER_SUPPORT                  HI_TRUE/** G0 **/
    #define CONFIG_HIFB_HD1_LAYER_SUPPORT                  HI_TRUE/** G1 **/
    #define CONFIG_HIFB_HD2_LAYER_SUPPORT                  HI_TRUE/** G3 **/
    #define CONFIG_HIFB_HD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD0_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD1_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD0_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD1_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_CURSOR_LAYER_SUPPORT               HI_FALSE
#elif defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3716mv450) \
   || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) \
   || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_HD0_LAYER_SUPPORT                  HI_TRUE
    #define CONFIG_HIFB_HD1_LAYER_SUPPORT                  HI_TRUE
    #define CONFIG_HIFB_HD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_HD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD0_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD1_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD0_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD1_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_CURSOR_LAYER_SUPPORT               HI_FALSE
#else
    #define CONFIG_HIFB_HD0_LAYER_SUPPORT                  HI_TRUE
    #define CONFIG_HIFB_HD1_LAYER_SUPPORT                  HI_TRUE
    #define CONFIG_HIFB_HD2_LAYER_SUPPORT                  HI_TRUE
    #define CONFIG_HIFB_HD3_LAYER_SUPPORT                  HI_TRUE
    #define CONFIG_HIFB_SD0_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD1_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_SD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD0_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD1_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD2_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_AD3_LAYER_SUPPORT                  HI_FALSE
    #define CONFIG_HIFB_CURSOR_LAYER_SUPPORT               HI_FALSE
#endif

#if    defined(CHIP_TYPE_hi3798mv100)    \
    || defined(CHIP_TYPE_hi3796mv100)    \
    || defined(CHIP_TYPE_hi3716dv100)    \
    || defined(CHIP_TYPE_hi3798cv200)    \
    || defined(CHIP_TYPE_hi3798mv200)    \
    || defined(CHIP_TYPE_hi3798mv300)    \
    || defined(CHIP_TYPE_hi3798mv310)    \
    || defined(CHIP_TYPE_hi3796mv200)    \
    || defined(CHIP_TYPE_hi3716mv450)    \
    || defined(CHIP_TYPE_hi3716mv410)    \
    || defined(CHIP_TYPE_hi3716mv420)    \
    || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_HD0_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_HD1_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_HD2_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_HD3_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_SD0_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_SD1_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_SD2_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_SD3_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_AD0_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_AD1_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_AD2_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_AD3_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_CURSOR_COMPRESSION_SUPPORT         HI_FALSE
#else
    #define CONFIG_HIFB_HD0_COMPRESSION_SUPPORT            HI_TRUE
    #define CONFIG_HIFB_HD1_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_HD2_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_HD3_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_SD0_COMPRESSION_SUPPORT            HI_TRUE
    #define CONFIG_HIFB_SD1_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_SD2_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_SD3_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_AD0_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_AD1_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_AD2_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_AD3_COMPRESSION_SUPPORT            HI_FALSE
    #define CONFIG_HIFB_CURSOR_COMPRESSION_SUPPORT         HI_FALSE
#endif

#if   defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) \
   || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450) \
   || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
    #define CONFIG_HIFB_HD_LAYER_MAXWIDTH         1920
    #define CONFIG_HIFB_HD_LAYER_MAXHEIGHT        1080
    #define CONFIG_HIFB_SD_LAYER_MAXWIDTH         720
    #define CONFIG_HIFB_SD_LAYER_MAXHEIGHT        576
    #define CONFIG_HIFB_AD_LAYER_MAXWIDTH         1920
    #define CONFIG_HIFB_AD_LAYER_MAXHEIGHT        1080
    #define CONFIG_HIFB_CURSOR_LAYER_MAXWIDTH     1920
    #define CONFIG_HIFB_CURSOR_LAYER_MAXHEIGHT    1080
#elif defined(CHIP_TYPE_hi3716mv410) || defined(CHIP_TYPE_hi3716mv420) || defined(CHIP_TYPE_hi3716mv430)
    #define CONFIG_HIFB_HD_LAYER_MAXWIDTH         1280
    #define CONFIG_HIFB_HD_LAYER_MAXHEIGHT        720
    #define CONFIG_HIFB_SD_LAYER_MAXWIDTH         720
    #define CONFIG_HIFB_SD_LAYER_MAXHEIGHT        576
    #define CONFIG_HIFB_AD_LAYER_MAXWIDTH         1280
    #define CONFIG_HIFB_AD_LAYER_MAXHEIGHT        720
    #define CONFIG_HIFB_CURSOR_LAYER_MAXWIDTH     1280
    #define CONFIG_HIFB_CURSOR_LAYER_MAXHEIGHT    720
#else
    #define CONFIG_HIFB_HD_LAYER_MAXWIDTH         1920
    #define CONFIG_HIFB_HD_LAYER_MAXHEIGHT        1080
    #define CONFIG_HIFB_SD_LAYER_MAXWIDTH         1920
    #define CONFIG_HIFB_SD_LAYER_MAXHEIGHT        1080
    #define CONFIG_HIFB_AD_LAYER_MAXWIDTH         1920
    #define CONFIG_HIFB_AD_LAYER_MAXHEIGHT        1080
    #define CONFIG_HIFB_CURSOR_LAYER_MAXWIDTH     1920
    #define CONFIG_HIFB_CURSOR_LAYER_MAXHEIGHT    1080
#endif

#if   defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) \
   || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450) \
   || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310) \
   || defined(CHIP_TYPE_hi3716mv430)
    #define GFX_CONFIG_GP0_MZE_VSP_2TAB_EN
#endif

#define CONFIG_HIFB_STRIDE_16ALIGN          16


#if   defined(CHIP_TYPE_hi3798cv200) || defined(CHIP_TYPE_hi3798mv200) \
   || defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450) \
   || defined(CHIP_TYPE_hi3798mv300) || defined(CHIP_TYPE_hi3798mv310)
      #define CONFIG_HIFB_MMU_SUPPORT
#endif

#ifdef CHIP_TYPE_hi3798mv310
#define CONFIG_HIFB_WBC_UNSUPPORT
#endif

#if defined(CHIP_TYPE_hi3796mv200)  || defined(CHIP_TYPE_hi3716mv450)
#define CONFIG_HIFB_LOWPOWER_SUPPORT
#endif

#if defined(CHIP_TYPE_hi3798cv200)
#define CONFIG_HIFB_GP0CSC_USE_HDRMOD
#define CONFIG_HIFB_BI2020_SUPPORT
#endif

#if defined(CHIP_TYPE_hi3798cv200)
#define  CONFIG_HIFB_CALCSTRIDE_WITH_ONEPOINTTHREE
#endif

/*************************** Structure Definition ************************************************/

/********************** Global Variable declaration **********************************************/



/******************************* API declaration *************************************************/

#ifdef __cplusplus

#if __cplusplus

}
#endif
#endif /* __cplusplus */

#endif /* __DRV_HIFB_CONFIG_H__ */
