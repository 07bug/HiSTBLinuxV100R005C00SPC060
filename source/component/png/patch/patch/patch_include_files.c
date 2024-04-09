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
/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/

/**************************** begin add include   ***********************************************/
#ifdef HIPNG_ACCELERATE
#include "png_accelerate.c"
#include "hi_png_api.c"
#endif
/**************************** end add include     ***********************************************/
