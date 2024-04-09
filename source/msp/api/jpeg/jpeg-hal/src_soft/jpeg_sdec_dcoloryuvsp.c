/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name        : patch_for_jdcoloryuvsp.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
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

/***************************** Macro Definition     ***********************************************/
#define JPEG_CHECK_WHETHER_SUPPORT_OUT_YUV400(jpeg_color_space) \
        if (JCS_GRAYSCALE != jpeg_color_space)\
        {\
            ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);\
        }

#define JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(jpeg_color_space) \
        if (JCS_YCbCr != jpeg_color_space)\
        {\
            ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);\
        }
/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/
static inline HI_VOID JPEG_SDEC_OutY(j_decompress_ptr cinfo, JSAMPROW InputYBuf);
static inline HI_VOID JPEG_SDEC_OutWholeCbCr(j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf);
static inline HI_VOID JPEG_SDEC_OutHalfRowCbCr(j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf);
static inline HI_VOID JPEG_SDEC_OutHalfColCbCr(j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf);
static inline HI_VOID JPEG_SDEC_OutHalfRowColCbCr(j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf);
static inline HI_VOID JPEG_SDEC_CheckYUVSPBuf(j_decompress_ptr cinfo);

/**********************       API realization       ***********************************************/
/*****************************************************************************
* func          : JPEG_SDEC_OutYuv400Sp
* description   : decode output yuv400 semi-planer
                    CNcomment:解码输出yuv400 semi-planer，
                              这里变量的定义要和开源保准保持一致CNend\n
* param[in]     : cinfo        CNcomment: 解码器句柄    CNend\n
* param[in]     : input_buf    CNcomment: yuv  数据               CNend\n
* param[ou]     : output_buf   CNcomment:输出buffer               CNend\n
* param[in]     : num_rows     CNcomment: 一次性输入的码流行数CNend\n
* retval        : NA
* others:       : NA
*****************************************************************************/
static inline HI_VOID JPEG_SDEC_YUV400_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    register JSAMPROW Inptr = NULL;
    HI_UNUSED(output_buf);

    while (--num_rows >= 0)
    {
       Inptr = input_buf[0][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr);
    }

    return;
}

static inline HI_VOID JPEG_SDEC_YUV444_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    HI_BOOL bOutputYuv420sp = HI_FALSE;
    register JSAMPROW Inptr0 = NULL,Inptr1 = NULL,Inptr2 = NULL;
    HI_UNUSED(output_buf);

    JPEG_DEC_IfOutPutYuv420Sp((HI_ULONG)cinfo->client_data, &bOutputYuv420sp);

    while (--num_rows >= 0)
    {
       Inptr0 = input_buf[0][input_row];
       Inptr1 = input_buf[1][input_row];
       Inptr2 = input_buf[2][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr0);

       if (HI_TRUE == bOutputYuv420sp)
       {
          JPEG_SDEC_OutHalfRowColCbCr(cinfo, Inptr2, Inptr1);
          continue;
       }

       JPEG_SDEC_OutWholeCbCr(cinfo, Inptr2, Inptr1);
    }

    return;
}


static inline HI_VOID JPEG_SDEC_YUV420_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    register JSAMPROW Inptr0 = NULL,Inptr1 = NULL,Inptr2 = NULL;
    HI_UNUSED(output_buf);

    while (--num_rows >= 0)
    {
       Inptr0 = input_buf[0][input_row];
       Inptr1 = input_buf[1][input_row];
       Inptr2 = input_buf[2][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr0);
       JPEG_SDEC_OutHalfRowCbCr(cinfo, Inptr2, Inptr1);
    }

    return;
}


static inline HI_VOID JPEG_SDEC_YUV42212_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    HI_BOOL bOutputYuv420sp = HI_FALSE;
    register JSAMPROW Inptr0 = NULL,Inptr1 = NULL,Inptr2 = NULL;
    HI_UNUSED(output_buf);

    JPEG_DEC_IfOutPutYuv420Sp((HI_ULONG)cinfo->client_data, &bOutputYuv420sp);

    while (--num_rows >= 0)
    {
       Inptr0 = input_buf[0][input_row];
       Inptr1 = input_buf[1][input_row];
       Inptr2 = input_buf[2][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr0);

       if (HI_TRUE == bOutputYuv420sp)
       {
          JPEG_SDEC_OutHalfRowColCbCr(cinfo, Inptr2, Inptr1);
          return;
       }
       JPEG_SDEC_OutHalfColCbCr(cinfo, Inptr2, Inptr1);
    }

    return;
}


static inline HI_VOID JPEG_SDEC_YUV42221_TO_YUVSp (j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf, int num_rows)
{
    register JSAMPROW Inptr0 = NULL,Inptr1 = NULL,Inptr2 = NULL;
    HI_UNUSED(output_buf);

    while (--num_rows >= 0)
    {
       Inptr0 = input_buf[0][input_row];
       Inptr1 = input_buf[1][input_row];
       Inptr2 = input_buf[2][input_row];
       input_row++;

       JPEG_SDEC_OutY(cinfo, Inptr0);
       JPEG_SDEC_OutHalfRowCbCr(cinfo, Inptr2, Inptr1);
    }

    return;
}

static inline HI_VOID JPEG_SDEC_OutY (j_decompress_ptr cinfo, JSAMPROW InputYBuf)
{
    HI_CHAR* OutYBuf = NULL;
    HI_U32 YStride = 0;
#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    HI_U64 LuPixSum = 0;
#endif
    register HI_U32 OutYBufOffset = 0;
    register HI_U32 Col = 0;

    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutYBuf, &YStride, NULL, NULL);
    if (NULL == OutYBuf)
    {
       return;
    }

#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    JPEG_DEC_GetLuPixSum((HI_ULONG)cinfo->client_data, &LuPixSum);
#endif

    OutYBufOffset = YStride * cinfo->output_scanline;

    for (Col = 0; Col < cinfo->output_width; Col++)
    {
       OutYBuf[OutYBufOffset + Col] = GETJSAMPLE(InputYBuf[Col]);
#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
       LuPixSum += OutYBuf[OutYBufOffset + Col];
#endif
    }

#ifdef CONFIG_JPEG_OUTPUT_LUPIXSUM
    JPEG_DEC_SetLuPixSum((HI_ULONG)cinfo->client_data, LuPixSum);
#endif

    return;
}

static inline HI_VOID JPEG_SDEC_OutWholeCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf)
{
    HI_CHAR* OutCbCrBuf = NULL;
    HI_U32 UVStride = 0;
    register HI_U32 OutCbCrBufOffset = 0;
    register HI_U32 Col = 0;

    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, NULL, NULL, &OutCbCrBuf, &UVStride);
    if (NULL == OutCbCrBuf)
    {
       return;
    }

    OutCbCrBufOffset = UVStride * cinfo->output_scanline;

    for (Col = 0; Col < cinfo->output_width; Col++)
    {
       OutCbCrBuf[OutCbCrBufOffset + 2 * Col]   = GETJSAMPLE(InputCbBuf[Col]);
       OutCbCrBuf[OutCbCrBufOffset + 2 * Col + 1] = GETJSAMPLE(InputCrBuf[Col]);
    }

     return;
}

static inline HI_VOID JPEG_SDEC_OutHalfRowColCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf)
{
    HI_CHAR* OutCbCrBuf = NULL;
    HI_U32 UVStride = 0;
    register HI_U32 OutCbCrBufOffset = 0;
    register HI_U32 Col = 0;
    register HI_U32 HasBeenReadSize = 0;

    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, NULL, NULL, &OutCbCrBuf, &UVStride);
    if (NULL == OutCbCrBuf)
    {
       return;
    }

    OutCbCrBufOffset = UVStride * (cinfo->output_scanline / 2);

    if (0 != cinfo->output_scanline % 2)
	{
       return;
	}

    for (Col = 0; Col < cinfo->output_width; Col++)
    {
        if (0 != Col % 2)
        {
           continue;
        }

        OutCbCrBuf[OutCbCrBufOffset + 2 * HasBeenReadSize]   = GETJSAMPLE(InputCbBuf[Col]);
        OutCbCrBuf[OutCbCrBufOffset + 2 * HasBeenReadSize + 1] = GETJSAMPLE(InputCrBuf[Col]);
        HasBeenReadSize++;
    }


    return;
}


static inline HI_VOID JPEG_SDEC_OutHalfRowCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf)
{
    HI_JPEG_FMT_E ImgFmt = HI_JPEG_FMT_BUTT;
    HI_BOOL bOutputYuv420sp = HI_FALSE;
    HI_CHAR* OutCbCrBuf = NULL;
    HI_U32 UVStride = 0;
    register HI_U32 OutCbCrBufOffset = 0;
    register HI_U32 Col = 0;

    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, NULL, NULL, &OutCbCrBuf, &UVStride);
    if (NULL == OutCbCrBuf)
    {
       return;
    }

    JPEG_DEC_IfOutPutYuv420Sp((HI_ULONG)cinfo->client_data, &bOutputYuv420sp);
    ImgFmt = JPEG_DEC_GetInputFmt((HI_ULONG)cinfo->client_data);

    if ((HI_TRUE == bOutputYuv420sp) || (HI_JPEG_FMT_YUV420 == ImgFmt))
    {
        OutCbCrBufOffset = UVStride * (cinfo->output_scanline / 2);
    }
    else
    {
         OutCbCrBufOffset = UVStride * cinfo->output_scanline;
    }

    if ((0 != cinfo->output_scanline % 2) && ((HI_TRUE == bOutputYuv420sp) || (HI_JPEG_FMT_YUV420 == ImgFmt)))
	{
       return;
	}

    for (Col = 0; Col < cinfo->output_width; Col += 2)
    {
       OutCbCrBuf[OutCbCrBufOffset + Col] = GETJSAMPLE(InputCbBuf[Col]);
    }

    for (Col = 1; Col < cinfo->output_width; Col += 2)
    {
       OutCbCrBuf[OutCbCrBufOffset + Col] = GETJSAMPLE(InputCrBuf[Col]);
    }

    return;
}


static inline HI_VOID JPEG_SDEC_OutHalfColCbCr (j_decompress_ptr cinfo, JSAMPROW InputCbBuf, JSAMPROW InputCrBuf)
{
    HI_CHAR* OutCbCrBuf = NULL;
    HI_U32 UVStride = 0;
    register HI_U32 OutCbCrBufOffset = 0;
    register HI_U32 Col = 0;

    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, NULL, NULL, &OutCbCrBuf, &UVStride);
    if (NULL == OutCbCrBuf)
    {
       return;
    }

    OutCbCrBufOffset = UVStride * (cinfo->output_scanline / 2);

    if (0 != cinfo->output_scanline % 2)
	{
	    return;
	}

    for (Col = 0; Col < cinfo->output_width; Col++)
    {
       OutCbCrBuf[OutCbCrBufOffset + 2 * Col] = GETJSAMPLE(InputCbBuf[Col]);
       OutCbCrBuf[OutCbCrBufOffset + 2 * Col + 1] = GETJSAMPLE(InputCrBuf[Col]);
    }

     return;
}


/*****************************************************************************
* func          : JPEG_SDEC_InitOutToYuv420Sp
* description   : decode output yuv420 semi-planer
                  CNcomment:解码输出格式统一为yuv420 semi-planer CNend\n
* param[in]     : cinfo        CNcomment: 解码器句柄    CNend\n
* retval        : HI_SUCCESS   解码输出yuv420sp
* retval        : HI_FAILURE   不支持解码输出yuv420sp
* others:       : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_InitOutToYuv420Sp (j_decompress_ptr cinfo)
{
    HI_BOOL bOutPutYuv420sp = HI_FALSE;
    HI_JPEG_FMT_E InputFmt = HI_JPEG_FMT_BUTT;
    my_cconvert_ptr cconvert;

    cinfo->out_color_components = cinfo->num_components;
    cinfo->output_components = (TRUE == cinfo->quantize_colors) ? (1) : (cinfo->out_color_components);
    cconvert = (my_cconvert_ptr)cinfo->cconvert;

    JPEG_DEC_IfOutPutYuv420Sp((HI_ULONG)cinfo->client_data,&bOutPutYuv420sp);
    if (HI_TRUE != bOutPutYuv420sp)
    {
       return HI_FAILURE;
    }

    InputFmt = JPEG_DEC_GetInputFmt((HI_ULONG)cinfo->client_data);
    if (HI_JPEG_FMT_YUV400 == InputFmt)
    {
       JPEG_CHECK_WHETHER_SUPPORT_OUT_YUV400(cinfo->jpeg_color_space);
       cconvert->pub.color_convert = JPEG_SDEC_YUV400_TO_YUVSp;
       return HI_SUCCESS;
    }

    switch (InputFmt)
    {
      case HI_JPEG_FMT_YUV444:
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV444_TO_YUVSp;
           break;

      case HI_JPEG_FMT_YUV420:
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV420_TO_YUVSp;
           break;

      case HI_JPEG_FMT_YUV422_21:
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV42221_TO_YUVSp;
           break;

      case HI_JPEG_FMT_YUV422_12:
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV42212_TO_YUVSp;
           break;

      default:
           if (HI_TRUE == bOutPutYuv420sp)
           {
              ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
           }
           break;
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* func          : JPEG_SDEC_InitOutToYuvSp
* description   : decode output yuv semi-planer
                  CNcomment:解码输出格式为yuv semi-planer CNend\n
* param[in]     : cinfo  CNcomment: 解码器句柄    CNend\n
* retval        : NA
* others:       : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_InitOutToYuvSp (j_decompress_ptr cinfo)
{
    my_cconvert_ptr cconvert;
    HI_JPEG_FMT_E OutputFmt = HI_JPEG_FMT_BUTT;

    cinfo->out_color_components = cinfo->num_components;
    cinfo->output_components = (TRUE == cinfo->quantize_colors) ? (1) : (cinfo->out_color_components);
    cconvert = (my_cconvert_ptr)cinfo->cconvert;

    OutputFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);

    if (HI_JPEG_FMT_YUV400 == OutputFmt)
    {
       JPEG_SDEC_CheckYUVSPBuf(cinfo);
       JPEG_CHECK_WHETHER_SUPPORT_OUT_YUV400(cinfo->jpeg_color_space);
       cconvert->pub.color_convert = JPEG_SDEC_YUV400_TO_YUVSp;
       return HI_SUCCESS;
    }

    switch (OutputFmt)
    {
      case HI_JPEG_FMT_YUV444:
           JPEG_SDEC_CheckYUVSPBuf(cinfo);
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV444_TO_YUVSp;
           break;

      case HI_JPEG_FMT_YUV420:
           JPEG_SDEC_CheckYUVSPBuf(cinfo);;
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV420_TO_YUVSp;
           break;

      case HI_JPEG_FMT_YUV422_21:
           JPEG_SDEC_CheckYUVSPBuf(cinfo);
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV42221_TO_YUVSp;
           break;

      case HI_JPEG_FMT_YUV422_12:
           JPEG_SDEC_CheckYUVSPBuf(cinfo);
           JPEG_CHECK_WHETHER_SUPPORT_OUT_UNYUV400(cinfo->jpeg_color_space);
           cconvert->pub.color_convert = JPEG_SDEC_YUV42212_TO_YUVSp;
           break;

      default:
           return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static inline HI_VOID JPEG_SDEC_CheckYUVSPBuf(j_decompress_ptr cinfo)
{
   HI_CHAR *OutYBuf = NULL;
   HI_CHAR *OutUVBuf = NULL;
   HI_BOOL bOutPutYuvsp = HI_FALSE;
   HI_BOOL bOutToUsrBuf = HI_FALSE;
   HI_JPEG_FMT_E OutputFmt = HI_JPEG_FMT_BUTT;

   JPEG_DEC_IfOutPutYuvSp((HI_ULONG)cinfo->client_data, &bOutPutYuvsp);
   if (HI_TRUE != bOutPutYuvsp)
   {
      return;
   }

   JPEG_DEC_IfOutToUsrBuf((HI_ULONG)cinfo->client_data, &bOutToUsrBuf);
   if (HI_TRUE != bOutToUsrBuf)
   {
      ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
   }

   JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutYBuf, NULL, &OutUVBuf, NULL);
   if (NULL == OutYBuf)
   {
      ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
   }

   OutputFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);
   if ((HI_JPEG_FMT_YUV400 != OutputFmt) && (NULL == OutUVBuf))
   {
      ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
   }

   return;
}
