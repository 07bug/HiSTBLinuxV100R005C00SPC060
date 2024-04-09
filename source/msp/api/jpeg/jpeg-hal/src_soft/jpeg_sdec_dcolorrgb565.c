/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name        : patch_for_jdcolorrgb565.c
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



/***************************** Macro Definition     ***********************************************/

#define CONVERT_PACK_SHORT_565(r,g,b)    ((((r) >> 3) << 11)|(((g)>> 2) << 5)|(((b)>>3)))

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
static inline HI_VOID RGB565_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    HI_JPEG_FMT_E OutFmt = HI_JPEG_FMT_BUTT;

    if (NULL == OutBuf)
    {
       return;
    }

    OutFmt = JPEG_DEC_GetOutputFmt(HdeHandle);

    if (HI_JPEG_FMT_RGB_565 == OutFmt)
    {
       *(INT16*)OutBuf = CONVERT_PACK_SHORT_565(Red,Green,Blue);
       return;
    }

    *(INT16*)OutBuf = CONVERT_PACK_SHORT_565(Blue,Green,Red);

    return;
}

static inline HI_VOID JPEG_SDEC_YCC_RGB565_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB565_Convert(HdeHandle,OutBuf,Red,Green,Blue);
    return;
}

static inline HI_VOID JPEG_SDEC_GRAY_RGB565_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB565_Convert(HdeHandle,OutBuf,Red,Green,Blue);
    return;
}

static inline HI_VOID JPEG_SDEC_YCCK_RGB565_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB565_Convert(HdeHandle,OutBuf,Red,Green,Blue);
    return;
}

static inline HI_VOID JPEG_SDEC_CMYK_RGB565_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha)
{
    register HI_U32 R = 0, G = 0, B = 0;

    R  =  MulDiv255Round(Red,Alpha);
    G  =  MulDiv255Round(Green,Alpha);
    B  =  MulDiv255Round(Blue,Alpha);

    RGB565_Convert(HdeHandle,OutBuf,R,G,B);

    return;
}

static inline HI_VOID JPEG_SDEC_RGB_RGB565_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    RGB565_Convert(HdeHandle,OutBuf,Red,Green,Blue);
    return;
}

/*****************************************************************************
* func           : JPEG_SDEC_SupportRGB565
* description    : decode output rgb565
                   CNcomment:解码输出格式为rgb565CNend\n
* param[in]      : cinfo CNcomment: 解码器句柄    CNend\n
* retval         : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_SupportRGB565(j_decompress_ptr cinfo)
{
    HI_JPEG_FMT_E OutFmt = HI_JPEG_FMT_BUTT;
    JPEG_SDEC_COLOR_CONVERT_S *pstSdecColorConvert = NULL;

    OutFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);

    if ((HI_JPEG_FMT_RGB_565 != OutFmt) && (HI_JPEG_FMT_BGR_565 != OutFmt))
    {
        return HI_FAILURE;
    }

    cinfo->out_color_components = 3;

    JPEG_DEC_GetConvert((HI_ULONG)cinfo->client_data, &pstSdecColorConvert);
    if (NULL == pstSdecColorConvert)
    {
       ERREXIT(cinfo, JERR_NO_IMAGE);
    }

    pstSdecColorConvert->JPEG_SDEC_YCC_ConVert  = JPEG_SDEC_YCC_RGB565_Convert;
    pstSdecColorConvert->JPEG_SDEC_GRAY_ConVert = JPEG_SDEC_GRAY_RGB565_Convert;
    pstSdecColorConvert->JPEG_SDEC_YCCK_ConVert = JPEG_SDEC_YCCK_RGB565_Convert;
    pstSdecColorConvert->JPEG_SDEC_CMYK_ConVert = JPEG_SDEC_CMYK_RGB565_Convert;
    pstSdecColorConvert->JPEG_SDEC_RGB_ConVert  = JPEG_SDEC_RGB_RGB565_Convert;

    return HI_SUCCESS;
}
