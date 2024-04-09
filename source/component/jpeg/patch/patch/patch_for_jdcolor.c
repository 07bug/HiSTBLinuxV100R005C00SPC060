/**************************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name        : patch_for_jdcolor.c
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
#include "jpeg_sdec_color.c"

/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
#define adp_for_init_ext_color_space       if (HI_SUCCESS == JPEG_SDEC_InitOutToYuv420Sp(cinfo))\
                                           {\
                                               return;\
                                           }\
                                           if (HI_SUCCESS == JPEG_SDEC_InitOutToYuvSp(cinfo))\
                                           {\
                                                return;\
                                           }\
                                           if (HI_SUCCESS == JPEG_SDEC_InitOutToXRGB(cinfo))\
                                           {\
                                                 return;\
                                           }\
                                           if (HI_SUCCESS == JPEG_SDEC_InitOutToYCbCr(cinfo))\
                                           {\
                                                 return;\
                                           }
