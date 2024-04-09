/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hal_dev.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : 硬件解码及新增功能对外接口
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
***************************************************************************************************/
#ifndef __JPEG_HAL_DEV_H__
#define __JPEG_HAL_DEV_H__


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
    HI_S32  HI_JPEG_HAL_OpenJpegDev(HI_VOID);
    HI_VOID HI_JPEG_HAL_CloseJpegDev(HI_S32 Fd);

    HI_S32  HI_JPEG_HAL_OpenGfx2dDev(HI_VOID);
    HI_VOID HI_JPEG_HAL_CloseGfx2dDev(HI_S32 Fd);

    HI_S32  HI_JPEG_HAL_OpenMemDev(HI_VOID);
    HI_VOID HI_JPEG_HAL_CloseMemDev(HI_S32 Fd);

    /**********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __JPEG_HAL_DEV_H__*/
