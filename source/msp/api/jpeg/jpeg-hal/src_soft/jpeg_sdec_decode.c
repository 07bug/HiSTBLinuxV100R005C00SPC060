/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_sdec_decode.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : send stream and start decompress
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

#include "jpeg_sdec_api.h"
/***************************** Macro Definition ***************************************************/

#ifdef LOG_TAG
  #undef LOG_TAG
#endif
#define LOG_TAG  "libjpeg"

/***************************** Structure Definition ***********************************************/

/***************************** Global Variable declaration ****************************************/

/***************************** API forward declarations *******************************************/

/******************************* API realization **************************************************/
static inline HI_VOID JPEG_SDEC_GetStream(j_decompress_ptr cinfo)
{
    HI_BOOL UserInputDataEof = HI_FALSE;
    HI_U32 TotalReadTotalBytes = 0;

    HI_BOOL bUsePhyBuf = HI_FALSE;
    HI_CHAR* pInputDataBuf = NULL;
    HI_U32 BufSize = 0;

    HI_U32 EveryTimeReadBytes = 0;
    HI_BOOL bFillRet = HI_TRUE;

    JPEG_DEC_GetStreamBuffer((HI_ULONG)cinfo->client_data, &pInputDataBuf, &BufSize, &bUsePhyBuf);
    if ((NULL == pInputDataBuf) || (0 == BufSize) || (HI_TRUE == bUsePhyBuf))
    {/** use user input buffer, should not read data **/
        return;
    }

    do
    {
        if (0 != cinfo->src->bytes_in_buffer)
        {
           EveryTimeReadBytes = (cinfo->src->bytes_in_buffer > BufSize) ? (BufSize) : (cinfo->src->bytes_in_buffer);
           EveryTimeReadBytes = ((BufSize - TotalReadTotalBytes) > EveryTimeReadBytes) ?
                                                                  (EveryTimeReadBytes) : (BufSize - TotalReadTotalBytes);

           HI_GFX_Memcpy((pInputDataBuf + TotalReadTotalBytes), (HI_CHAR*)cinfo->src->next_input_byte, EveryTimeReadBytes);
           cinfo->src->next_input_byte += EveryTimeReadBytes;
           cinfo->src->bytes_in_buffer -= EveryTimeReadBytes;
           TotalReadTotalBytes += EveryTimeReadBytes;
        }
        else
        {
           bFillRet = cinfo->src->fill_input_buffer(cinfo);
        }

        if (HI_FALSE == bFillRet)
        {
           break;
        }

        if ((2 == cinfo->src->bytes_in_buffer) && (0xFF == (*(cinfo->src->next_input_byte))) && (0xD9 == (*(cinfo->src->next_input_byte + 1))))
        {
           break;
        }
     }while(TotalReadTotalBytes < BufSize);

     if (TotalReadTotalBytes < BufSize)
     {
         UserInputDataEof = HI_TRUE;
     }
     else
     {
         UserInputDataEof = HI_FALSE;
     }

     JPEG_DEC_SetStreamBuffer((HI_ULONG)cinfo->client_data, TotalReadTotalBytes, UserInputDataEof);

     return;
}


/*****************************************************************************
 * func         : JPEG_DEC_Scanlines
 * description  : start decompress
                  CNcomment: 启动解码 CNend\n
 * param[in]    : cinfo        CNcomment:   解码器句柄   CNend\n
 * param[in]    : LineBuf      CNcomment:   行buffer     CNend\n
 * param[in]    : HdecHandle   CNcomment:   解码行数     CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
static inline HI_U32 JPEG_DEC_Scanlines(j_decompress_ptr cinfo, HI_CHAR* LineBuf, HI_U32 MaxLines)
{
    HI_CHAR* CurInputBuffer = NULL;
    HI_U32 CurInputPos = 0;
    HI_U32 SeekPos = 0;
    HI_BOOL bFinishDec = HI_FALSE;
    HI_BOOL HardDecSuccess = HI_FALSE;
    HI_BOOL SupportHardDec = HI_FALSE;
    HI_BOOL StopDec = HI_FALSE;
    HI_BOOL HasBeenStartDec = HI_FALSE;
    HI_BOOL SupportSeekToSoft = HI_FALSE;

    JPEG_DEC_GetStopDec((HI_ULONG)cinfo->client_data, &StopDec);
    if (HI_TRUE == StopDec)
    {
        ERREXIT(cinfo, JERR_NO_IMAGE);
    }

    JPEG_DEC_GetHdecSuccess((HI_ULONG)cinfo->client_data, &HardDecSuccess);
    if (HI_TRUE == HardDecSuccess)
    {
        return (HI_U32)JPEG_DEC_CscConvert((HI_ULONG)cinfo->client_data, LineBuf, MaxLines, &(cinfo->output_scanline));
    }

    JPEG_DEC_SetPara((HI_ULONG)cinfo->client_data);

    JPEG_DEC_GetSupportHdecState((HI_ULONG)cinfo->client_data, &SupportHardDec);
    if (HI_FALSE == SupportHardDec)
    {
        return 0;
    }

    if (NULL != cinfo->src->seek_input_data)
    {
        SupportSeekToSoft = HI_TRUE;
    }

    do
    {
        /** read data to stream buffer **/
        JPEG_SDEC_GetStream(cinfo);

        /** start hard decode **/
        bFinishDec = JPEG_DEC_StartDec((HI_ULONG)cinfo->client_data,HasBeenStartDec,SupportSeekToSoft);

        HasBeenStartDec = HI_TRUE;
    /** continue decode **/
    }while(HI_FALSE == bFinishDec);

    JPEG_DEC_GetHdecSuccess((HI_ULONG)cinfo->client_data, &HardDecSuccess);
    if (HI_TRUE == HardDecSuccess)
    {
#ifdef CONFIG_GFX_PRINT
        JPEG_TRACE("++++++++hard dec success [%s %d]\n",__FUNCTION__,__LINE__);
#endif
        return (HI_U32)JPEG_DEC_CscConvert((HI_ULONG)cinfo->client_data, LineBuf, MaxLines,&(cinfo->output_scanline));
    }

    JPEG_DEC_SeekInputBuffer((HI_ULONG)cinfo->client_data, &CurInputBuffer, &CurInputPos, &SeekPos);

    if (HI_FALSE == SupportSeekToSoft)
    {
#ifdef CONFIG_GFX_PRINT
       JPEG_TRACE("++++++++seek_input_data func is null [%s %d]\n",__FUNCTION__,__LINE__);
#endif
       cinfo->src->next_input_byte = (JOCTET*)CurInputBuffer;
       cinfo->src->bytes_in_buffer = CurInputPos;
       return 0;
    }

    if (HI_FALSE == cinfo->src->seek_input_data(cinfo, SeekPos))
    {
       JPEG_TRACE("+++++++++++++seek_input_data failure [%s %d]\n",__FUNCTION__,__LINE__);
    }

#ifdef CONFIG_GFX_PRINT
    JPEG_TRACE("+++++++++++++seek pos = %d\n",SeekPos);
#endif

    cinfo->src->bytes_in_buffer = 0;

    return 0;
}
