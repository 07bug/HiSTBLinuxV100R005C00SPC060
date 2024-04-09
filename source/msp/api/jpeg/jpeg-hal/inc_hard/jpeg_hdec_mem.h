/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hdec_mem.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
***************************************************************************************************/
#ifndef __JPEG_HDEC_MEM_H__
#define __JPEG_HDEC_MEM_H__


/*********************************add include here*************************************************/
#include "hi_jpeg_config.h"
#include "hi_type.h"

/**************************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ***********************************************/

     #define CONFIG_JPEG_INPUT_DATA_BUFFER_ALIGN   64

     #define JPEG_MCU_8ALIGN                       8
     #define JPEG_MCU_16ALIGN                      16

     #define JPGD_HDEC_MMZ_CSCOUT_STRIDE_ALIGN     16

 #if   defined(CHIP_TYPE_hi3716mv310)  \
    || defined(CHIP_TYPE_hi3110ev500)  \
    || defined(CHIP_TYPE_hi3716mv320)  \
    || defined(CHIP_TYPE_hi3716mv330)  \
    || defined(CHIP_TYPE_hi3712)       \
    || defined(CHIP_TYPE_hi3716c)      \
    || defined(CHIP_TYPE_hi3716m)      \
    || defined(CHIP_TYPE_hi3716h)
       #define JPGD_HDEC_MMZ_YUVSP_STRIDE_ALIGN    128
   #else
       #define JPGD_HDEC_MMZ_YUVSP_STRIDE_ALIGN    64
   #endif

     #define JPGD_HDEC_MMZ_ARGB_STRIDE_ALIGN       128
     #define JPGD_HDEC_MMZ_ARGB_BUFFER_ALIGN       4
     #define JPGD_HDEC_MMZ_CSCOUT_BUFFER_ALIGN     16
     #define JPGD_HDEC_MMZ_YUVSP_BUFFER_ALIGN      128

     /*************************** Enum Definition *************************************************/
     #ifndef INT_MAX
        #define INT_MAX         ((int)(~0U>>1))
     #endif
     #ifndef INT_MIN
        #define INT_MIN         (-INT_MAX - 1)
     #endif
     #ifndef UINT_MAX
        #define UINT_MAX        (~0U)
     #endif
     #ifndef LONG_MAX
        #define LONG_MAX        ((long)(~0UL>>1))
     #endif
     #ifndef LONG_MIN
        #define LONG_MIN        (-LONG_MAX - 1)
     #endif
     #ifndef ULONG_MAX
        #define ULONG_MAX       (~0UL)
     #endif
    /*************************** Structure Definition *********************************************/


    /********************** Global Variable declaration *******************************************/

    /******************************* API declaration **********************************************/

    /**********************************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __JPEG_HDEC_MEM_H__*/
