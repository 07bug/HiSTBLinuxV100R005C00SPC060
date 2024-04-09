/**************************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hidl_hal.h
Version          : Initial Draft
Author           :
Created          : 2017/10/01
Description      : libjpeg调用libhi_msp中硬件解码接口，通过hidl去调用
Function List    :

History          :
Date                     Author           Modification
2017/10/01               sdk              Created file
***************************************************************************************************/
#ifndef __JPEG_HIDL_HAL_H__
#define __JPEG_HIDL_HAL_H__


/*********************************add include here*************************************************/

#include "hi_type.h"

/**************************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ***********************************************/

     /*************************** Enum Definition *************************************************/


    /*************************** Structure Definition *********************************************/

    /********************** Global Variable declaration *******************************************/

    /******************************* API declaration **********************************************/
    HI_S32  JPEG_HIDL_OpenJpegDev(HI_VOID);
    HI_VOID JPEG_HIDL_CloseJpegDev(HI_S32 Fd);

    HI_S32  JPEG_HIDL_OpenGfx2dDev(HI_VOID);
    HI_VOID JPEG_HIDL_CloseGfx2dDev(HI_S32 Fd);

    HI_S32  JPEG_HIDL_OpenMemDev(HI_VOID);
    HI_VOID JPEG_HIDL_CloseMemDev(HI_S32 Fd);
    /**********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __JPEG_HIDL_HAL_H__*/
