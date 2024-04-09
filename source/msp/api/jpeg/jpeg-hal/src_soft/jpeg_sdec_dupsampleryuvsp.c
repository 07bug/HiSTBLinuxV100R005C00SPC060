/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name       : jpeg_sdec_dupsampleryuvsp.c
Version         : Initial Draft
Author          :
Created         : 2018/01/01
Description     : output yuv semi-planer
                  上采样输出yuv semi-planer
Function List   :

History         :
Date                     Author                    Modification
2018/01/01               sdk                       Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "jpeglib.h"
#include "jerror.h"

#include "jpeg_sdec_api.h"
/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
 static inline HI_VOID JPEG_SDEC_YUV400_UPLANER_TO_YUVSp(j_decompress_ptr cinfo,
                                                         JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                                         JDIMENSION in_row_groups_avail,
                                                         JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                                         JDIMENSION out_rows_avail)
{
    HI_CHAR* OutYBuf = NULL;
    HI_U32 YStride = 0;
    register HI_U32 OutYBufOffset = 0;

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);
    if (NULL != out_row_ctr)
    {
      *out_row_ctr = 1;
    }

    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutYBuf, &YStride, NULL, NULL);
    if (NULL == OutYBuf)
    {
        return;
    }

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    OutYBufOffset = YStride * cinfo->output_scanline;
    OutYBuf = OutYBuf + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][*in_row_group_ctr], sizeof(char) * YStride);

    (*in_row_group_ctr)++;

    return;
}


static inline HI_VOID JPEG_SDEC_YUV400_H2V2_UPLANER_TO_YUVSp(j_decompress_ptr cinfo,
                                                             JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                                             JDIMENSION in_row_groups_avail,
                                                             JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                                             JDIMENSION out_rows_avail)
{
    my_upsample_ptr upsample = (my_upsample_ptr) cinfo->upsample;

    HI_CHAR* OutYBuf = NULL;
    HI_U32 YStride = 0;
    register HI_U32 OutYBufOffset = 0;

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);
    if (NULL != out_row_ctr)
    {
      *out_row_ctr = 1;
    }

    if (TRUE == upsample->spare_full)
    {
       upsample->spare_full = FALSE;
       return;
    }
    upsample->spare_full = TRUE;

    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutYBuf, &YStride, NULL, NULL);
    if (NULL == OutYBuf)
    {
        return;
    }

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    OutYBufOffset = YStride * cinfo->output_scanline;
    OutYBuf = OutYBuf + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][(*in_row_group_ctr) * 2], sizeof(char) * YStride);

    OutYBuf += YStride;
    HI_GFX_Memcpy(OutYBuf, input_buf[0][(*in_row_group_ctr) * 2 + 1], sizeof(char) * YStride);

    (*in_row_group_ctr)++;

    return;
}


static inline HI_VOID JPEG_SDEC_YUV444_UPLANER_TO_YUVSp(j_decompress_ptr cinfo,
                                             		    JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                             		    JDIMENSION in_row_groups_avail,
                                             		    JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                             		    JDIMENSION out_rows_avail)
{
    HI_U32 Col = 0;

    HI_CHAR* OutYBuf = NULL;
    HI_U32 YStride = 0;
    register HI_U32 OutYBufOffset = 0;
    HI_CHAR* OutCbCrBuf = NULL;
    HI_U32 CbCrStride = 0;
    register HI_U32 OutCbCrBufOffset = 0;

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);
    if (NULL != out_row_ctr)
    {
      *out_row_ctr = 1;
    }

    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutYBuf, &YStride, &OutCbCrBuf, &CbCrStride);
    if ((NULL == OutYBuf) || (NULL == OutCbCrBuf))
    {
        return;
    }

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    OutYBufOffset = YStride * cinfo->output_scanline;
    OutYBuf = OutYBuf + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][*in_row_group_ctr], sizeof(char) * YStride);

    /**<--out Cb Cr data >**/
    /**<-- 输出 Cb Cr  数据>**/
    OutCbCrBufOffset = CbCrStride * cinfo->output_scanline;
    OutCbCrBuf = OutCbCrBuf + OutCbCrBufOffset;

    for (Col = 0; Col < CbCrStride / 2; Col++)
    {
       OutCbCrBuf[2 * Col]   = input_buf[2][*in_row_group_ctr][Col];
       OutCbCrBuf[2 * Col + 1] = input_buf[1][*in_row_group_ctr][Col];
    }

    (*in_row_group_ctr)++;

    return;
}



static inline HI_VOID JPEG_SDEC_YUV420_UPLANER_TO_YUVSp(j_decompress_ptr cinfo,
                                            		    JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                            		    JDIMENSION in_row_groups_avail,
                                            		    JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                            		    JDIMENSION out_rows_avail)
{
    HI_U32 Col = 0;
    my_upsample_ptr upsample = (my_upsample_ptr) cinfo->upsample;

    HI_CHAR* OutYBuf = NULL;
    HI_U32 YStride = 0;
    register HI_U32 OutYBufOffset = 0;
    HI_CHAR* OutCbCrBuf = NULL;
    HI_U32 CbCrStride = 0;
    register HI_U32 OutCbCrBufOffset = 0;

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);
    if (NULL != out_row_ctr)
    {
      *out_row_ctr = 1;
    }


    if (TRUE == upsample->spare_full)
    {
       upsample->spare_full = FALSE;
       return;
    }
    upsample->spare_full = TRUE;

    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutYBuf, &YStride, &OutCbCrBuf, &CbCrStride);
    if ((NULL == OutYBuf) || (NULL == OutCbCrBuf))
    {
        return;
    }

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    OutYBufOffset = YStride * cinfo->output_scanline;
    OutYBuf = OutYBuf + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][(*in_row_group_ctr) * 2], sizeof(char) * YStride);

    OutYBuf += YStride;
    HI_GFX_Memcpy(OutYBuf, input_buf[0][(*in_row_group_ctr) * 2 + 1], sizeof(char) * YStride);

    /**<--out Cb Cr data >**/
    /**<-- 输出 Cb Cr  数据>**/
	if (0 != cinfo->output_scanline % 2)
	{
       (*in_row_group_ctr)++;
       return;
	}


    OutCbCrBufOffset = CbCrStride * (cinfo->output_scanline / 2);
    OutCbCrBuf = OutCbCrBuf + OutCbCrBufOffset;

    for (Col = 0; Col < CbCrStride / 2; Col++)
    {
       OutCbCrBuf[2 * Col]   = input_buf[2][*in_row_group_ctr][Col];
       OutCbCrBuf[2 * Col + 1] = input_buf[1][*in_row_group_ctr][Col];
    }

	(*in_row_group_ctr)++;

    return;
}


static inline HI_VOID JPEG_SDEC_YUV42212_UPLANER_TO_YUVSp(j_decompress_ptr cinfo,
                                            		      JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                            		      JDIMENSION in_row_groups_avail,
                                            		      JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                            		      JDIMENSION out_rows_avail)
{
    JPEG_SDEC_YUV420_UPLANER_TO_YUVSp(cinfo,input_buf,in_row_group_ctr,in_row_groups_avail,output_buf,out_row_ctr,out_rows_avail);
    return;
}



static inline HI_VOID JPEG_SDEC_YUV42221_UPLANER_TO_YUVSp(j_decompress_ptr cinfo,
                                                		  JSAMPIMAGE input_buf, JDIMENSION *in_row_group_ctr,
                                                		  JDIMENSION in_row_groups_avail,
                                                		  JSAMPARRAY output_buf, JDIMENSION *out_row_ctr,
                                                		  JDIMENSION out_rows_avail)
{
    HI_U32 Col = 0;
    my_upsample_ptr upsample = (my_upsample_ptr) cinfo->upsample;

    HI_CHAR* OutYBuf = NULL;
    HI_U32 YStride = 0;
    register HI_U32 OutYBufOffset = 0;
    HI_CHAR* OutCbCrBuf = NULL;
    HI_U32 CbCrStride = 0;
    register HI_U32 OutCbCrBufOffset = 0;

    HI_UNUSED(output_buf);
    HI_UNUSED(out_rows_avail);
    HI_UNUSED(in_row_groups_avail);
    if (NULL != out_row_ctr)
    {
      *out_row_ctr = 1;
    }


    if (TRUE == upsample->spare_full)
    {
       upsample->spare_full = FALSE;
       return;
    }
    upsample->spare_full = TRUE;

    /**<--out y data >**/
    /**<-- 输出Y  数据>**/
    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutYBuf, &YStride, &OutCbCrBuf, &CbCrStride);
    if ((NULL == OutYBuf) || (NULL == OutCbCrBuf))
    {
        return;
    }

    OutYBufOffset = YStride * cinfo->output_scanline;
    OutYBuf = OutYBuf + OutYBufOffset;

    HI_GFX_Memcpy(OutYBuf, input_buf[0][*in_row_group_ctr], sizeof(char) * YStride);

    /**<--out Cb Cr data >**/
    /**<-- 输出 Cb Cr  数据>**/
    OutCbCrBufOffset = CbCrStride * (cinfo->output_scanline / 2);
    OutCbCrBuf = OutCbCrBuf + OutCbCrBufOffset;

    for (Col = 0; Col < CbCrStride / 2; Col++)
    {
       OutCbCrBuf[2 * Col]   = input_buf[2][*in_row_group_ctr][Col];
       OutCbCrBuf[2 * Col + 1] = input_buf[1][*in_row_group_ctr][Col];
    }

    (*in_row_group_ctr)++;

    return;
}


/*****************************************************************************
* func          : JPEG_DEC_InitUpsamplerForYuvsp
* description   : 上采样输出yuv semi-planer
* param[in]     : cinfo   CNcomment: 解码器句柄    CNend\n
* retval        : NA
* others:       : NA
*****************************************************************************/
static inline HI_S32 JPEG_DEC_InitUpsamplerForYuvsp(j_decompress_ptr cinfo)
{
    my_upsample_ptr upsample  = (my_upsample_ptr)cinfo->upsample;
    HI_JPEG_FMT_E OutputFmt = HI_JPEG_FMT_BUTT;

    OutputFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);

    if (   (HI_JPEG_FMT_YUV400    != OutputFmt) && (HI_JPEG_FMT_YUV420    != OutputFmt)
        && (HI_JPEG_FMT_YUV422_12 != OutputFmt) && (HI_JPEG_FMT_YUV422_21 != OutputFmt)
        && (HI_JPEG_FMT_YUV444    != OutputFmt))
    {
        return HI_FAILURE;
    }

    if (JCS_GRAYSCALE == cinfo->jpeg_color_space)
    {/** 400 **/
       if(cinfo->max_h_samp_factor == 2)
       {
           upsample->pub.upsample = JPEG_SDEC_YUV400_H2V2_UPLANER_TO_YUVSp;
       }
       else
       {
           upsample->pub.upsample = JPEG_SDEC_YUV400_UPLANER_TO_YUVSp;
       }
       return HI_SUCCESS;
    }

    if ((cinfo->max_h_samp_factor == 2) && (cinfo->max_v_samp_factor == 2))
    {/** 420 **/
       upsample->pub.upsample = JPEG_SDEC_YUV420_UPLANER_TO_YUVSp;
       return HI_SUCCESS;
    }

    if ((cinfo->max_h_samp_factor == 2) && (cinfo->max_v_samp_factor == 1))
    {/** 422 2*1 **/
       upsample->pub.upsample = JPEG_SDEC_YUV42221_UPLANER_TO_YUVSp;
       return HI_SUCCESS;
    }

    if ((cinfo->max_h_samp_factor == 1) && (cinfo->max_v_samp_factor == 2))
    {/** 422 1*2 **/
       upsample->pub.upsample = JPEG_SDEC_YUV42212_UPLANER_TO_YUVSp;
       return HI_SUCCESS;
    }

    if ((cinfo->max_h_samp_factor == 1) && (cinfo->max_v_samp_factor == 1))
    {/** 444 **/
       upsample->pub.upsample = JPEG_SDEC_YUV444_UPLANER_TO_YUVSp;
       return HI_SUCCESS;
    }

    return HI_FAILURE;
}
