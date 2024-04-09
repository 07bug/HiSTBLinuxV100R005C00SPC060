/**************************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name        : patch_include_files.c
Version          : Initial Draft
Author           :
Created          : 2017/10/01
Description      : 用来包含开源代码之外的其他文件实现
Function List    :

History          :
Date                     Author           Modification
2017/10/01               sdk              Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

#include "jpeg_hdec_hal.h"

/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
static inline HI_VOID JPEG_HDEC_GetTimeStamp(HI_U32 *pu32TimeMs, HI_U32 *pu32TimeUs)
{
    HI_S32 Ret = HI_SUCCESS;
    struct timespec timenow = {0, 0};
    clockid_t id = CLOCK_MONOTONIC_RAW;

    if (HI_NULL == pu32TimeMs)
    {
        return;
    }

    Ret = clock_gettime(id, &timenow);
    if (Ret < 0)
    {
        return;
    }

    *pu32TimeMs = (HI_U32)(timenow.tv_sec * 1000 + timenow.tv_nsec/1000000);

    if (HI_NULL == pu32TimeUs)
    {
        return;
    }

    *pu32TimeUs = (HI_U32)(timenow.tv_sec * 1000000 + timenow.tv_nsec/1000);

    return;
}

/**************************** begin add include   ***********************************************/
#include "jpeg_hdec_rwreg.c"
#include "jpeg_hdec_csc.c"
#include "jpeg_hdec_mem.c"
#include "jpeg_hdec_dev.c"
#include "jpeg_hdec_debug.c"
#include "jpeg_hdec_lowdelay.c"
#include "jpeg_hdec_parse.c"
#include "jpeg_hdec_subtile.c"
#include "jpeg_hdec_support.c"
#include "jpeg_hdec_setpara.c"
#include "jpeg_hdec_startdec.c"

/** 调用上面文件的实现 **/
#include "jpeg_hdec_hal.c"
/**************************** end add include     ***********************************************/
