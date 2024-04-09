/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name        : patch_for_jdcolorxrgb.c
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

#include "jpeg_sdec_dcolorargb8888.c"
#include "jpeg_sdec_dcolorargb1555.c"
#include "jpeg_sdec_dcolorrgb888.c"
#include "jpeg_sdec_dcolorrgb565.c"
/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
static inline HI_VOID JPEG_SDEC_YCC_XRGB_Convert(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
    register JSAMPROW inptr0, inptr1, inptr2;
    register JSAMPLE * range_limit = cinfo->sample_range_limit;
    register int * Crrtab  = cconvert->Cr_r_tab;
    register int * Cbbtab  = cconvert->Cb_b_tab;
    register long * Crgtab = (long*)cconvert->Cr_g_tab;
    register long * Cbgtab = (long*)cconvert->Cb_g_tab;
    SHIFT_TEMPS

    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;
    register HI_S32 Y = 0, Cb = 0, Cr = 0;
    register HI_U32 Red = 0, Green = 0, Blue = 0;
    register HI_U32 PixOffset = 0;

    HI_CHAR* OutPutBuf = NULL;
    HI_U32 OutputStride = 0;
    HI_U32 SkipLines = 0;
    HI_JPEG_FMT_E OutputFmt = HI_JPEG_FMT_BUTT;
    JPEG_SDEC_COLOR_CONVERT_S *pstSdecColorConvert = NULL;

    OutputFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);
    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutPutBuf, &OutputStride, NULL, NULL);
    JPEG_DEC_GetSkipLines((HI_ULONG)cinfo->client_data,&SkipLines);

    JPEG_DEC_GetConvert((HI_ULONG)cinfo->client_data,&pstSdecColorConvert);
    if (NULL == pstSdecColorConvert || NULL == pstSdecColorConvert->JPEG_SDEC_YCC_ConVert)
    {
       ERREXIT(cinfo, JERR_NO_IMAGE);
    }

    PixOffset = ((HI_JPEG_FMT_RGB_565 != OutputFmt) && (HI_JPEG_FMT_BGR_565 != OutputFmt)) ? (cinfo->out_color_components) : (2);

    while (--num_rows >= 0)
    {
        inptr0 = input_buf[0][input_row];
        inptr1 = input_buf[1][input_row];
        inptr2 = input_buf[2][input_row];
        input_row++;

        if (NULL == OutPutBuf)
        {
           OutPutBuf = (HI_CHAR*)(*output_buf++);
        }
        else
        {
            RowNum  = OutputStride * ((cinfo->output_scanline - SkipLines) + HasBeenReadRowNum);
            OutPutBuf = (HI_CHAR*)(OutPutBuf + RowNum);
            HasBeenReadRowNum++;
        }

        for (Col = 0; Col < cinfo->output_width; Col++)
        {
            Y  = GETJSAMPLE(inptr0[Col]); /**< Green >**/
            Cb = GETJSAMPLE(inptr1[Col]); /**< Blue  >**/
            Cr = GETJSAMPLE(inptr2[Col]); /**< Red   >**/

            Red   = range_limit[Y + Crrtab[Cr]];
            Green = range_limit[Y + ((int)RIGHT_SHIFT(Cbgtab[Cb]+Crgtab[Cr], SCALEBITS))];
            Blue  = range_limit[Y + Cbbtab[Cb]];
            pstSdecColorConvert->JPEG_SDEC_YCC_ConVert((HI_ULONG)cinfo->client_data,OutPutBuf,Red,Green,Blue);
            OutPutBuf += PixOffset;
        }
    }

    return;
}

static inline HI_VOID JPEG_SDEC_GRAY_XRGB_Convert(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    register JSAMPROW inptr;
    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;
    register HI_U32 Red = 0;
    register HI_U32 PixOffset = 0;

    HI_CHAR* OutPutBuf  = NULL;
    HI_U32 OutputStride = 0;
    HI_U32 SkipLines = 0;
    HI_JPEG_FMT_E OutputFmt = HI_JPEG_FMT_BUTT;
    JPEG_SDEC_COLOR_CONVERT_S *pstSdecColorConvert = NULL;

    OutputFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);
    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutPutBuf, &OutputStride, NULL, NULL);
    JPEG_DEC_GetSkipLines((HI_ULONG)cinfo->client_data,&SkipLines);

    JPEG_DEC_GetConvert((HI_ULONG)cinfo->client_data,&pstSdecColorConvert);
    if (NULL == pstSdecColorConvert || NULL == pstSdecColorConvert->JPEG_SDEC_GRAY_ConVert)
    {
       ERREXIT(cinfo, JERR_NO_IMAGE);
    }

    PixOffset = ((HI_JPEG_FMT_RGB_565 != OutputFmt) && (HI_JPEG_FMT_BGR_565 != OutputFmt)) ? (cinfo->out_color_components) : (2);

    while (--num_rows >= 0)
    {
        inptr = input_buf[0][input_row++];

        if (NULL == OutPutBuf)
        {
           OutPutBuf = (HI_CHAR*)(*output_buf++);
        }
        else
        {
            RowNum  = OutputStride * ((cinfo->output_scanline - SkipLines) + HasBeenReadRowNum);
            OutPutBuf = (HI_CHAR*)(OutPutBuf + RowNum);
            HasBeenReadRowNum++;
        }

        for (Col = 0; Col < cinfo->output_width; Col++)
        {
           Red = inptr[Col];
           pstSdecColorConvert->JPEG_SDEC_GRAY_ConVert((HI_ULONG)cinfo->client_data,OutPutBuf,Red,Red,Red);
           OutPutBuf += PixOffset;
        }
    }

    return;
}

static inline HI_VOID JPEG_SDEC_YCCK_XRGB_Convert(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
    register JSAMPROW inptr0, inptr1, inptr2, inptr3;
    register JSAMPLE * range_limit = cinfo->sample_range_limit;
    register int * Crrtab = cconvert->Cr_r_tab;
    register int * Cbbtab = cconvert->Cb_b_tab;
    register long * Crgtab = (long*)cconvert->Cr_g_tab;
    register long * Cbgtab = (long*)cconvert->Cb_g_tab;
    SHIFT_TEMPS

    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;
    register HI_S32 Y = 0, Cb = 0, Cr = 0;
    register HI_U32 Red = 0, Green = 0, Blue = 0;

    HI_U8 YCCK[4];
	HI_U8 MaxVal = 0;
	register HI_S32 C  = 0;	/** cyan	**/
	register HI_S32 M  = 1;	/** magenta **/
	register HI_S32 YE = 2;	/** yellow	**/
	register HI_S32 K  = 3;	/** black	**/

    register HI_U32 PixOffset = 0;

    HI_CHAR* OutPutBuf = NULL;
    HI_U32 OutputStride = 0;
    HI_U32 SkipLines = 0;
    HI_JPEG_FMT_E OutputFmt = HI_JPEG_FMT_BUTT;
    JPEG_SDEC_COLOR_CONVERT_S *pstSdecColorConvert = NULL;

    OutputFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);
    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutPutBuf, &OutputStride, NULL, NULL);
    JPEG_DEC_GetSkipLines((HI_ULONG)cinfo->client_data,&SkipLines);

    JPEG_DEC_GetConvert((HI_ULONG)cinfo->client_data,&pstSdecColorConvert);
    if (NULL == pstSdecColorConvert || NULL == pstSdecColorConvert->JPEG_SDEC_YCCK_ConVert)
    {
       ERREXIT(cinfo, JERR_NO_IMAGE);
    }

    PixOffset = ((HI_JPEG_FMT_RGB_565 != OutputFmt) && (HI_JPEG_FMT_BGR_565 != OutputFmt)) ? (cinfo->out_color_components) : (2);

    while (--num_rows >= 0)
    {
        inptr0 = input_buf[0][input_row];
		inptr1 = input_buf[1][input_row];
		inptr2 = input_buf[2][input_row];
		inptr3 = input_buf[3][input_row];
		input_row++;

        if (NULL == OutPutBuf)
        {
           OutPutBuf = (HI_CHAR*)(*output_buf++);
        }
        else
        {
            RowNum  = OutputStride * ((cinfo->output_scanline - SkipLines) + HasBeenReadRowNum);
            OutPutBuf = (HI_CHAR*)(OutPutBuf + RowNum);
            HasBeenReadRowNum++;
        }

        for (Col = 0; Col < cinfo->output_width; Col++)
        {
              Y  = GETJSAMPLE(inptr0[Col]);
              Cb = GETJSAMPLE(inptr1[Col]);
              Cr = GETJSAMPLE(inptr2[Col]);

              YCCK[C]  = range_limit[MAXJSAMPLE - (Y + Crrtab[Cr])];
              YCCK[M]  = range_limit[MAXJSAMPLE - (Y + ((int) RIGHT_SHIFT(Cbgtab[Cb] + Crgtab[Cr],SCALEBITS)))];
              YCCK[YE] = range_limit[MAXJSAMPLE - (Y + Cbbtab[Cb])];
              YCCK[K]  = inptr3[Col];

              MaxVal = (YCCK[C] > YCCK[M])  ? (YCCK[C]) : (YCCK[M]);
              MaxVal = (MaxVal  > YCCK[YE]) ? (MaxVal)  : (YCCK[YE]);
              MaxVal = (MaxVal  > YCCK[K])  ? (MaxVal)  : (YCCK[K]);

              Red   = (0 == MaxVal) ? (YCCK[K]) : ((YCCK[K] * YCCK[C])  / MaxVal);
              Green = (0 == MaxVal) ? (YCCK[K]) : ((YCCK[K] * YCCK[M])  / MaxVal);
              Blue  = (0 == MaxVal) ? (YCCK[K]) : ((YCCK[K] * YCCK[YE]) / MaxVal);

              pstSdecColorConvert->JPEG_SDEC_YCCK_ConVert((HI_ULONG)cinfo->client_data,OutPutBuf,Red,Green,Blue);
              OutPutBuf += PixOffset;
        }
    }

    return;
}

static inline HI_VOID JPEG_SDEC_CMYK_XRGB_Convert(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    register JSAMPROW inptr0, inptr1, inptr2, inptr3;
    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;
    register HI_S32 Y = 0, Cb = 0, Cr = 0, A = 0;
    register HI_U32 PixOffset = 0;

    HI_CHAR* OutPutBuf = NULL;
    HI_U32 OutputStride = 0;
    HI_U32 SkipLines = 0;
    HI_JPEG_FMT_E OutputFmt = HI_JPEG_FMT_BUTT;
    JPEG_SDEC_COLOR_CONVERT_S *pstSdecColorConvert = NULL;

    OutputFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);
    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutPutBuf, &OutputStride, NULL, NULL);
    JPEG_DEC_GetSkipLines((HI_ULONG)cinfo->client_data,&SkipLines);

    JPEG_DEC_GetConvert((HI_ULONG)cinfo->client_data,&pstSdecColorConvert);
    if (NULL == pstSdecColorConvert || NULL == pstSdecColorConvert->JPEG_SDEC_CMYK_ConVert)
    {
       ERREXIT(cinfo, JERR_NO_IMAGE);
    }

    PixOffset = ((HI_JPEG_FMT_RGB_565 != OutputFmt) && (HI_JPEG_FMT_BGR_565 != OutputFmt)) ? (cinfo->out_color_components) : (2);

    while (--num_rows >= 0)
    {
        inptr0 = input_buf[0][input_row];
        inptr1 = input_buf[1][input_row];
        inptr2 = input_buf[2][input_row];
        inptr3 = input_buf[3][input_row];
        input_row++;

        if (NULL == OutPutBuf)
        {
           OutPutBuf = (HI_CHAR*)(*output_buf++);
        }
        else
        {
            RowNum  = OutputStride * ((cinfo->output_scanline - SkipLines) + HasBeenReadRowNum);
            OutPutBuf = (HI_CHAR*)(OutPutBuf + RowNum);
            HasBeenReadRowNum++;
        }

        for (Col = 0; Col < cinfo->output_width; Col++)
        {
            Y  = GETJSAMPLE(inptr0[Col]);
            Cb = GETJSAMPLE(inptr1[Col]);
            Cr = GETJSAMPLE(inptr2[Col]);
            A  = GETJSAMPLE(inptr3[Col]);

            pstSdecColorConvert->JPEG_SDEC_CMYK_ConVert((HI_ULONG)cinfo->client_data,OutPutBuf,Y,Cb,Cr,A);
            OutPutBuf += PixOffset;
        }
    }

    return;
}

static inline HI_VOID JPEG_SDEC_RGB_XRGB_Convert(j_decompress_ptr cinfo,JSAMPIMAGE input_buf,JDIMENSION input_row,JSAMPARRAY output_buf,int num_rows)
{
    register JSAMPROW inptr0, inptr1, inptr2;

    register HI_U32 RowNum = 0;
    register HI_U32 HasBeenReadRowNum = 0;
    register HI_U32 Col = 0;
    register HI_U32 Red = 0, Green = 0, Blue = 0;
    register HI_U32 PixOffset = 0;

    HI_CHAR* OutPutBuf = NULL;
    HI_U32 OutputStride = 0;
    HI_U32 SkipLines = 0;
    HI_JPEG_FMT_E OutputFmt = HI_JPEG_FMT_BUTT;
    JPEG_SDEC_COLOR_CONVERT_S *pstSdecColorConvert = NULL;

    OutputFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);
    JPEG_DEC_GetOutUsrBuf((HI_ULONG)cinfo->client_data, &OutPutBuf, &OutputStride, NULL, NULL);
    JPEG_DEC_GetSkipLines((HI_ULONG)cinfo->client_data,&SkipLines);

    JPEG_DEC_GetConvert((HI_ULONG)cinfo->client_data,&pstSdecColorConvert);
    if (NULL == pstSdecColorConvert || NULL == pstSdecColorConvert->JPEG_SDEC_RGB_ConVert)
    {
       ERREXIT(cinfo, JERR_NO_IMAGE);
    }

    PixOffset = ((HI_JPEG_FMT_RGB_565 != OutputFmt) && (HI_JPEG_FMT_BGR_565 != OutputFmt)) ? (cinfo->out_color_components) : (2);

    while (--num_rows >= 0)
    {
        inptr0 = input_buf[0][input_row];
        inptr1 = input_buf[1][input_row];
        inptr2 = input_buf[2][input_row];
        input_row++;

        if (NULL == OutPutBuf)
        {
           OutPutBuf = (HI_CHAR*)(*output_buf++);
        }
        else
        {
            RowNum  = OutputStride * ((cinfo->output_scanline - SkipLines) + HasBeenReadRowNum);
            OutPutBuf = (HI_CHAR*)(OutPutBuf + RowNum);
            HasBeenReadRowNum++;
        }

        for (Col = 0; Col < cinfo->output_width; Col++)
        {
            Red   = inptr0[Col];
            Green = inptr1[Col];
            Blue  = inptr2[Col];
            pstSdecColorConvert->JPEG_SDEC_RGB_ConVert((HI_ULONG)cinfo->client_data,OutPutBuf,Red,Green,Blue);
            OutPutBuf += PixOffset;
        }
    }

    return;
}


/*****************************************************************************
* func          : JPEG_SDEC_InitOutToXRGB
* description   : decode output xrgb
                  CNcomment:解码输出格式为xrgb  格式 CNend\n
* param[in]     : cinfo  CNcomment: 解码器句柄    CNend\n
* retval        : NA
* others:       : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_InitOutToXRGB(j_decompress_ptr cinfo)
{
    HI_S32 Ret = HI_SUCCESS;
    my_cconvert_ptr cconvert = (my_cconvert_ptr)cinfo->cconvert;

    Ret = JPEG_SDEC_SupportARGB8888(cinfo);
    Ret &= JPEG_SDEC_SupportARGB1555(cinfo);
    Ret &= JPEG_SDEC_SupportRGB888(cinfo);
    Ret &= JPEG_SDEC_SupportRGB565(cinfo);
    if (HI_SUCCESS != Ret)
    {
       return HI_FAILURE;
    }

    cinfo->output_components = (TRUE == cinfo->quantize_colors) ? (1) : (cinfo->out_color_components);

    if (cinfo->jpeg_color_space == JCS_YCbCr)
    {
        cconvert->pub.color_convert = JPEG_SDEC_YCC_XRGB_Convert;
        build_ycc_rgb_table(cinfo);
        return HI_SUCCESS;
    }

    if (cinfo->jpeg_color_space == JCS_GRAYSCALE)
    {
       cconvert->pub.color_convert = JPEG_SDEC_GRAY_XRGB_Convert;
       return HI_SUCCESS;
    }

    if (cinfo->jpeg_color_space == JCS_YCCK)
    {
       cconvert->pub.color_convert = JPEG_SDEC_YCCK_XRGB_Convert;
       build_ycc_rgb_table(cinfo);
       return HI_SUCCESS;
    }

    if (cinfo->jpeg_color_space == JCS_CMYK)
    {
       cconvert->pub.color_convert = JPEG_SDEC_CMYK_XRGB_Convert;
       return HI_SUCCESS;
    }

    if (cinfo->jpeg_color_space == JCS_RGB)
    {
       cconvert->pub.color_convert = JPEG_SDEC_RGB_XRGB_Convert;
       return HI_SUCCESS;
    }

    ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);

    return HI_SUCCESS;
}
