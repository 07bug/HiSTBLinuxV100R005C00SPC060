/**************************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name        : patch_for_jdmarker.c
Version          : Initial Draft
Author           :
Created          : 2017/10/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2017/10/01               sdk              Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include "jpeg_sdec_api.h"
#include "jpeg_sdec_exif.c"

/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/

/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
#ifdef CONFIG_JPEG_EXIF_SUPPORT
#define adp_for_set_exif                          marker->process_APPn[1] = JPEG_SDEC_GetExif;
#else
#define adp_for_set_exif                          do{}while(0);
#endif
