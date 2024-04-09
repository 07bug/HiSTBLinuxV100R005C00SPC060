/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hal_dev.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : 硬件解码及新增功能对外接口
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "jpeg_hal_dev.h"
/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/

/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/


/******************************* API realization **************************************************/
HI_S32 HI_JPEG_HAL_OpenJpegDev(HI_VOID)
{
    HI_S32 Fd = open("/dev/jpeg", O_RDWR | O_SYNC, S_IRUSR);

    return Fd;
}

HI_VOID HI_JPEG_HAL_CloseJpegDev(HI_S32 Fd)
{
    if (Fd < 0)
    {
        return;
    }

    close(Fd);

    return;
}

HI_S32 HI_JPEG_HAL_OpenGfx2dDev()
{
    HI_S32 Fd = open("/dev/hi_tde", O_RDWR, S_IRUSR);

    return Fd;
}

HI_VOID HI_JPEG_HAL_CloseGfx2dDev(HI_S32 Fd)
{
    if (Fd < 0)
    {
       return;
    }

    close(Fd);

    return;
}

HI_S32 HI_JPEG_HAL_OpenMemDev()
{
    HI_S32 Fd = open("/dev/ion", O_RDWR, S_IRUSR);

    return Fd;
}

HI_VOID HI_JPEG_HAL_CloseMemDev(HI_S32 Fd)
{
    if (Fd < 0)
    {
       return;
    }

    close(Fd);

    return;
}
