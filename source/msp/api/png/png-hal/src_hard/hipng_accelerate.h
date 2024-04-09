/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name        : hipng_accelerate.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : control hard decode dispose
Function List    :


History          :
Date                      Author                      Modification
2018/01/01                sdk                         Created file
**************************************************************************************************/
#ifndef __HIPNG_ACCELERATE_H__
#define __HIPNG_ACCELERATE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cplusplus */
#endif  /* __cplusplus */


#define PNG_NO_PEDANTIC_WARNINGS
/*********************************add include here***********************************************/
#include "hi_type.h"
#include "png.h"
#include "hi_png_type.h"
#include "hi_png_api.h"
#include "hipng.h"
#include "hi_gfx_comm.h"


/***************************** Macro Definition *************************************************/
#define HIPNG_TRACE(fmt,args...)

#define HIPNG_NO_DEC                  0x0
#define HIPNG_SW_DEC                  0x1
#define HIPNG_HW_DEC                  0x2
#define HIPNG_HWCOPY_DEC              0x4

/*************************** Enum Definition ****************************************************/

/*************************** Structure Definition ***********************************************/
typedef struct tag_hipng_struct_hwctl_s
{
    HI_U8 u8DecMode;                /* dec mode                               */
    HI_U8 u8UserDecMode;            /* dec mode of user Specified             */
    HI_U8 u8SupportDecMode;
    HI_BOOL bSyncDec;               /* whether  or not Synchronous decoding   */
    HI_PNG_HANDLE s32Handle;        /* handle of hardware dec                 */
    HI_PNG_STATE_E eState;          /* status of Decoder                      */
    png_rw_ptr read_data_fn;        /* libpng original IO function pointer    */
    HI_PNG_READ_FN read_data_fn_hw; /* hardware IO function pointer           */
    png_bytepp image;               /* goal dec memory                        */
    png_uint_32 idat_size;          /* current IDAT size for read             */
    png_uint_32 crc;                /* current chunk CRC value                */
#if PNG_LIBPNG_VER > 10246
    png_uint_32 chunk_name;
#else
    png_byte chunk_name[5];
#endif
    png_uint_32 pallateaddr;
    HI_BOOL bPallateAlpha;
    HI_U32 u32TmpPhyaddr;
    HI_U8 *pu8TmpImage;
    HI_U32 u32TmpStride;
    HI_U32 u32InflexionSize;
    HI_U32 u32CopyRows;
    HI_S32 s32MmzFd;
	HI_VOID *pTmpMemData;
	HI_VOID *pPallateMemData;
	HI_PNG_BUF_S stBuf;		          /* ���������������buf                  */
	HI_U32 u32StreamLen;	          /* ����buf�е���Ч���ݳ���              */
	HI_U8 u8ReadHeadCount;	          /* ����ȡ��idat���ͷ���ֽ���           */
	HI_BOOL bCrc;			          /* �Ƿ�Ϊ��ȡCRC����״̬�������ã���֤���ݶ�ȡ�Ƿ�����*/
	HI_U8 u8PushState;	              /* ��ʽ����ʧ��                         */
	png_bytep save_buffer_ptr;        /* current location in save_buffer      */
	png_bytep save_buffer;            /* buffer for previously read data      */
	png_bytep current_buffer_ptr;     /* current location in current_buffer   */
	png_bytep current_buffer;         /* buffer for recently used data        */
	png_size_t save_buffer_size;      /* amount of data now in save_buffer    */
	png_size_t save_buffer_max;       /* total size of save_buffer            */
	png_size_t buffer_size;           /* total amount of available input data */
	png_size_t current_buffer_size;
	png_uint_32 push_length;
	png_uint_32 mode;
	png_byte pixel_depth;
	HI_U8 u8ExceptionMode;
	HI_BOOL bHasStream;
	HI_BOOL bChunkheadValid;
	png_byte chunkHead[8];
	HI_U8 u8IdatCount;
}hipng_struct_hwctl_s;

/********************** Global Variable declaration *********************************************/

/******************************* API declaration ************************************************/
/*****************************************************************
* func    : create the hardware information struct
* in      : user_png_ver,error_ptr,png_error_ptr,warn_fn
* out     : struct point
* ret     : none
* others  :
*****************************************************************/
hipng_struct_hwctl_s *hipng_create_read_struct_hw(png_const_charp user_png_ver, png_voidp error_ptr,png_error_ptr error_fn, png_error_ptr warn_fn);

/*****************************************************************
* func    : destroy hardware information struct
* in      : pstHwctlStruct (hardware information struct)
* out     : none
* ret     : none
* others  :
*****************************************************************/
HI_VOID hipng_destroy_read_struct_hw(hipng_struct_hwctl_s *pstHwctlStruct);

/*****************************************************************
* func    : png hardware dec
* in      : png_ptr png dec struct
* in      : image target line struct
* out     : image data
* ret     : HI_SUCCESS	decode success
*           HI_FAILURE	decode failed
* others  :
*****************************************************************/
HI_S32 hipng_read_rows(png_structp png_ptr, png_bytepp row, png_bytepp display_row, png_uint_32 num_rows);

void hipng_finish_switch(png_structp png_ptr);

HI_VOID hipng_read_transform_info(png_structp png_ptr, png_infop info_ptr);

#ifdef PNG_DO_PREMULTI_TO_ALPHA
HI_VOID png_do_premulti_alpha PNGARG((png_row_infop row_info, png_bytep row,png_uint_32 flags));
#endif

HI_VOID hipng_set_outfmt(png_structp png_ptr, int transforms);

HI_VOID hipng_push_switch_process(png_structp png_ptr);

HI_S32 hipng_push_decode(png_structp png_ptr);

HI_S32 hipng_push_stream(png_structp png_ptr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  /* __HIPNG_ACCELERATE_H__ */
