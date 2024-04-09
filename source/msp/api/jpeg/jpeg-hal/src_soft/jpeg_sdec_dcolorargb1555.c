/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name        : patch_for_jdcolorargb1555.c
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
#define CONVERT_PACK_SHORT_ARGB1555(a,r,g,b)  (((a) << 15) | (((r) >> 3) << 10) | (((g) >> 3) << 5) | ((b) >> 3))
#define CONVERT_PACK_SHORT_ABGR1555(a,r,g,b)  (((a) << 15) | (((b) >> 3) << 10) | (((g) >> 3) << 5) | ((r) >> 3))
#define CONVERT_PACK_SHORT_RGBA5551(a,r,g,b)  ((((r) >> 3) << 11) | (((g) >> 3) << 6) | (((b) >> 3) << 1) | (a))
#define CONVERT_PACK_SHORT_BGRA5551(a,r,g,b)  ((((b) >> 3) << 11) | (((g) >> 3) << 6) | (((r) >> 3) << 1) | (a))


/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
static inline HI_VOID ARGB1555_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha)
{
    HI_JPEG_FMT_E OutFmt = HI_JPEG_FMT_BUTT;

    if (NULL == OutBuf)
    {
       return;
    }

    OutFmt = JPEG_DEC_GetOutputFmt(HdeHandle);

    if (HI_JPEG_FMT_RGBA_5551 == OutFmt)
    {
       *(INT16*)OutBuf = CONVERT_PACK_SHORT_RGBA5551(Alpha,Red,Green,Blue);
       return;
    }

    if (HI_JPEG_FMT_BGRA_5551 == OutFmt)
    {
       *(INT16*)OutBuf = CONVERT_PACK_SHORT_BGRA5551(Alpha,Red,Green,Blue);
       return;
    }

    if (HI_JPEG_FMT_ARGB_1555 == OutFmt)
    {
       *(INT16*)OutBuf = CONVERT_PACK_SHORT_ARGB1555(Alpha,Red,Green,Blue);
       return;
    }

    *(INT16*)OutBuf = CONVERT_PACK_SHORT_ABGR1555(Alpha,Red,Green,Blue);

    return;
}

static inline HI_VOID JPEG_SDEC_YCC_ARGB1555_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB1555_Convert(HdeHandle,OutBuf,Red,Green,Blue,0x1);
    return;
}

static inline HI_VOID JPEG_SDEC_GRAY_ARGB1555_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB1555_Convert(HdeHandle,OutBuf,Red,Green,Blue,0x1);
    return;
}

static inline HI_VOID JPEG_SDEC_YCCK_ARGB1555_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB1555_Convert(HdeHandle,OutBuf,Red,Green,Blue,0x1);
    return;
}

static inline HI_VOID JPEG_SDEC_CMYK_ARGB1555_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha)
{
    register HI_U32 R = 0, G = 0, B = 0;

    R =  MulDiv255Round(Red,Alpha);
    G =  MulDiv255Round(Green,Alpha);
    B =  MulDiv255Round(Blue,Alpha);

    ARGB1555_Convert(HdeHandle,OutBuf,R,G,B,0xFF);

    return;
}

static inline HI_VOID JPEG_SDEC_RGB_ARGB1555_Convert(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue)
{
    ARGB1555_Convert(HdeHandle,OutBuf,Red,Green,Blue,0x1);
    return;
}

/*****************************************************************************
* func           : JPEG_SDEC_SupportARGB1555
* description    : decode output argb1555
                   CNcomment:���������ʽΪargb1555CNend\n
* param[in]      : cinfo  CNcomment: ���������    CNend\n
* retval         : NA
* others:        : NA
*****************************************************************************/
static inline HI_S32 JPEG_SDEC_SupportARGB1555(j_decompress_ptr cinfo)
{
    HI_JPEG_FMT_E OutFmt = HI_JPEG_FMT_BUTT;
    JPEG_SDEC_COLOR_CONVERT_S *pstSdecColorConvert = NULL;

    OutFmt = JPEG_DEC_GetOutputFmt((HI_ULONG)cinfo->client_data);

    if (  (HI_JPEG_FMT_ARGB_1555 != OutFmt) && (HI_JPEG_FMT_ABGR_1555 != OutFmt)
        &&(HI_JPEG_FMT_RGBA_5551 != OutFmt) && (HI_JPEG_FMT_BGRA_5551 != OutFmt))
    {
        return HI_FAILURE;
    }

    cinfo->out_color_components = 2;

    JPEG_DEC_GetConvert((HI_ULONG)cinfo->client_data, &pstSdecColorConvert);
    if (NULL == pstSdecColorConvert)
    {
       ERREXIT(cinfo, JERR_NO_IMAGE);
    }

    pstSdecColorConvert->JPEG_SDEC_YCC_ConVert  = JPEG_SDEC_YCC_ARGB1555_Convert;
    pstSdecColorConvert->JPEG_SDEC_GRAY_ConVert = JPEG_SDEC_GRAY_ARGB1555_Convert;
    pstSdecColorConvert->JPEG_SDEC_YCCK_ConVert = JPEG_SDEC_YCCK_ARGB1555_Convert;
    pstSdecColorConvert->JPEG_SDEC_CMYK_ConVert = JPEG_SDEC_CMYK_ARGB1555_Convert;
    pstSdecColorConvert->JPEG_SDEC_RGB_ConVert  = JPEG_SDEC_RGB_ARGB1555_Convert;

    return HI_SUCCESS;
}
