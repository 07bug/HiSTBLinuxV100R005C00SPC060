/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_sdec_outinfo.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : output information
Function List    :


History          :
Date                  Author                 Modification
2018/01/01            sdk                    Created file
***************************************************************************************************/

/***************************** add include here****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jpeglib.h"
#include "jerror.h"

#include "hi_jpeg_api.h"
#include "jpeg_sdec_api.h"
/***************************** Macro Definition ***************************************************/


/***************************** Structure Definition ***********************************************/

/***************************** Global Variable declaration ****************************************/

/***************************** API forward declarations *******************************************/

/******************************* API realization **************************************************/
static inline HI_VOID JPEG_SDEC_SetOutputColorSpace(j_decompress_ptr cinfo, JPEG_IMG_INFO_S *pstImgInfo)
{
    switch(cinfo->out_color_space)
    {
        case JCS_EXT_XBGR:
        case JCS_EXT_ABGR:
            pstImgInfo->output_color_space = HI_JPEG_FMT_RGBA_8888;
            pstImgInfo->out_color_components = 4;
            pstImgInfo->output_components = 4;
            break;
        case JCS_EXT_XRGB:
        case JCS_EXT_ARGB:
            pstImgInfo->output_color_space = HI_JPEG_FMT_BGRA_8888;
            pstImgInfo->out_color_components = 4;
            pstImgInfo->output_components = 4;
            break;
        case JCS_RGBA_8888:
        case JCS_EXT_RGBX:
        case JCS_EXT_RGBA:
            pstImgInfo->output_color_space = HI_JPEG_FMT_ABGR_8888;
            pstImgInfo->out_color_components = 4;
            pstImgInfo->output_components = 4;
            break;
        case JCS_EXT_BGRX:
        case JCS_EXT_BGRA:
            pstImgInfo->output_color_space = HI_JPEG_FMT_ARGB_8888;
            pstImgInfo->out_color_components = 4;
            pstImgInfo->output_components = 4;
            break;

        case JCS_ARGB_1555:
            pstImgInfo->output_color_space = HI_JPEG_FMT_BGRA_5551;
            pstImgInfo->out_color_components = 2;
            pstImgInfo->output_components = 2;
            break;
        case JCS_ABGR_1555:
            pstImgInfo->output_color_space = HI_JPEG_FMT_RGBA_5551;
            pstImgInfo->out_color_components = 2;
            pstImgInfo->output_components = 2;
            break;
        case JCS_BGRA_5551:
            pstImgInfo->output_color_space = HI_JPEG_FMT_ARGB_1555;
            pstImgInfo->out_color_components = 2;
            pstImgInfo->output_components = 2;
            break;
        case JCS_RGBA_5551:
            pstImgInfo->output_color_space = HI_JPEG_FMT_ABGR_1555;
            pstImgInfo->out_color_components = 2;
            pstImgInfo->output_components = 2;
            break;

        case JCS_RGB:
        case JCS_EXT_RGB:
            pstImgInfo->output_color_space = HI_JPEG_FMT_BGR_888;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 3;
            break;
        case JCS_BGR:
        case JCS_EXT_BGR:
            pstImgInfo->output_color_space = HI_JPEG_FMT_RGB_888;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 3;
            break;

        case JCS_RGB565:
        case JCS_RGB_565:
            pstImgInfo->output_color_space = HI_JPEG_FMT_RGB_565;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 2;
            break;
        case JCS_BGR565:
            pstImgInfo->output_color_space = HI_JPEG_FMT_BGR_565;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 2;
            break;
         case JCS_YCbCr:
            pstImgInfo->output_color_space = HI_JPEG_FMT_YCbCr;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 3;
            break;
         case JCS_CrCbY:
            pstImgInfo->output_color_space = HI_JPEG_FMT_CrCbY;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 3;
            break;
         case JCS_YUV400_SP:
            pstImgInfo->output_color_space = HI_JPEG_FMT_YUV400;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 3;
            break;
         case JCS_YUV420_SP:
            pstImgInfo->output_color_space = HI_JPEG_FMT_YUV420;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 3;
            break;
         case JCS_YUV422_SP_12:
            pstImgInfo->output_color_space = HI_JPEG_FMT_YUV422_12;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 3;
            break;
         case JCS_YUV422_SP_21:
            pstImgInfo->output_color_space = HI_JPEG_FMT_YUV422_21;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 3;
            break;
         case JCS_YUV444_SP:
            pstImgInfo->output_color_space = HI_JPEG_FMT_YUV444;
            pstImgInfo->out_color_components = 3;
            pstImgInfo->output_components = 3;
            break;
        default:
            pstImgInfo->output_color_space = HI_JPEG_FMT_BUTT;
            pstImgInfo->out_color_components = 1;
            pstImgInfo->output_components = 1;
            break;
    }

    pstImgInfo->scale_num   = cinfo->scale_num;
    pstImgInfo->scale_denom = cinfo->scale_denom;

    return;
}


static inline HI_VOID JPEG_SDEC_SetOutPutInfo(j_decompress_ptr cinfo)
{
    JPEG_IMG_INFO_S stImgInfo;
    if (NULL == cinfo)
    {
       return;
    }

    HI_GFX_Memset(&stImgInfo, 0x0, sizeof(stImgInfo));

    JPEG_DEC_GetImgInfo((HI_ULONG)cinfo->client_data, &stImgInfo);

    if (HI_JPEG_FMT_BUTT != stImgInfo.output_color_space)
    {/** if has been set at jpeg_dec_outinfo.c**/
       return;
    }

    JPEG_SDEC_SetOutputColorSpace(cinfo, &stImgInfo);

    JPEG_DEC_SetImgInfo((HI_ULONG)cinfo->client_data, &stImgInfo);

    return;
}

static inline HI_VOID JPEG_SDEC_SaveCurInputData(j_decompress_ptr cinfo)
{
    JPEG_IMG_INFO_S stImgInfo;
    if (NULL == cinfo)
    {
       return;
    }

    HI_GFX_Memset(&stImgInfo, 0x0, sizeof(stImgInfo));

    JPEG_DEC_GetImgInfo((HI_ULONG)cinfo->client_data, &stImgInfo);

    stImgInfo.bytes_in_buffer  = cinfo->src->bytes_in_buffer;
    stImgInfo.next_input_byte  = (HI_CHAR*)cinfo->src->next_input_byte;

    JPEG_DEC_SetImgInfo((HI_ULONG)cinfo->client_data, &stImgInfo);

    return;
}
