/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name        : hipng.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : control hard decode dispose
Function List    :


History          :
Date                      Author                      Modification
2018/01/01                sdk                         Created file
**************************************************************************************************/
#ifndef _HIPNG_H_
#define _HIPNG_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cplusplus */
#endif  /* __cplusplus */


/*********************************add include here***********************************************/
#include "png.h"


/***************************** Macro Definition *************************************************/
#define HIPNG_TRANSFORM_ARGB1555    0x10000
#define HIPNG_TRANSFORM_ARGB4444    0x20000
#define HIPNG_TRANSFORM_RGB565      0x40000
#define HIPNG_TRANSFORM_RGB555      0x80000
#define HIPNG_TRANSFORM_RGB444      0x100000

#define HIPNG_ARGB1555 0x4000000L   /* Output format is ARGB1555 *//*CNcomment:Ŀ�����ARGB1555��ʽ*/
#define HIPNG_ARGB4444 0x10000000L	/* Output format is ARGB4444 *//*CNcomment:Ŀ�����ARGB4444��ʽ*/
#define HIPNG_RGB565 0x20000000L	/* Output format is RGB565   *//*CNcomment:Ŀ�����RGB565��ʽ  */
#define HIPNG_RGB555 0x40000000L	/* Output format is RGB555   *//*CNcomment:Ŀ�����RGB555��ʽ  */
#define HIPNG_RGB444 0x80000000L	/* Output format is RGB444   *//*CNcomment:Ŀ�����RGB444��ʽ  */

#define HIPNG_PREMULTI_ALPHA 0x8000000L



/*************************** Enum Definition ****************************************************/
typedef enum tag_HIPNG_FMT_E
{
    HIPNG_FMT_ARGB1555,
    HIPNG_FMT_ARGB4444,
    HIPNG_FMT_RGB565,
    HIPNG_FMT_RGB555,
    HIPNG_FMT_RGB444,
    HIPNG_FMT_BUTT
}HIPNG_FMT_E;

/* enumeraton of status for png decoding */
typedef enum tagPNG_STATE_E
{
    PNG_STATE_NOSTART = 0x0,  /* no start decod or abort,such as destroying decoder when decoding */
    PNG_STATE_DECING,         /* decoding */
    PNG_STATE_FINISH,         /* finish decoding */
    PNG_STATE_ERR,            /* failed for decoding */
    PNG_STATE_BUTT
}PNG_STATE_E;

typedef enum {
    PNG_FALSE = 0,
    PNG_TRUE  = 1,
}PNG_BOOL;

/*************************** Structure Definition ***********************************************/


/********************** Global Variable declaration *********************************************/

/******************************* API declaration ************************************************/
#if (PNG_LIBPNG_VER > 10246)
PNG_EXPORT(500, void, png_set_outfmt, (png_structp png_ptr, HIPNG_FMT_E eOutFmt));
PNG_EXPORT(501, void, png_set_swdec, (png_structp png_ptr));
PNG_EXPORT(502, void, png_get_state, (png_structp png_ptr, PNG_BOOL bBlock,PNG_STATE_E *pState));
PNG_EXPORT(503, void, png_set_inflexion, (png_structp png_ptr,png_uint_32 u32InflexionSize));
PNG_EXPORT(504, void, png_read_image_async, (png_structp png_ptr,png_bytepp image));
PNG_EXPORT(505, void, png_read_png_async, (png_structp png_ptr,png_infop info_ptr,int transforms,png_voidp params));
PNG_EXPORT(506, void, png_set_premulti_alpha, (png_structp png_ptr));
#else
extern PNG_EXPORT(void, png_set_outfmt) PNGARG((png_structp png_ptr, HIPNG_FMT_E eOutFmt));
extern PNG_EXPORT(void, png_set_swdec) PNGARG((png_structp png_ptr));
extern PNG_EXPORT(void, png_get_state) PNGARG((png_structp png_ptr, PNG_BOOL bBlock,PNG_STATE_E *pState));
extern PNG_EXPORT(void, png_set_inflexion) PNGARG((png_structp png_ptr,png_uint_32 u32InflexionSize));
extern PNG_EXPORT(void, png_read_image_async) PNGARG((png_structp png_ptr,png_bytepp image));
extern PNG_EXPORT(void, png_read_png_async) PNGARG((png_structp png_ptr,png_infop info_ptr,int transforms,png_voidp params));
extern PNG_EXPORT(void, png_set_premulti_alpha) PNGARG((png_structp png_ptr));
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
