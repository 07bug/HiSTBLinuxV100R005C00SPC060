/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hdec_hal.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : Ӳ�����뼰�������ܶ���ӿ�
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

#include "hi_jpeg_config.h"
#include "jpeg_hdec_api.h"

#include "jpeg_hdec_hal.h"

/***************************** Macro Definition     ***********************************************/

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/

/********************** API forward declarations    ***********************************************/
static inline HI_VOID JPEG_DEC_ReleaseRes(HI_ULONG HdecHandle);

/**********************       API realization       ***********************************************/


/******************************* API realization **************************************************/

/*****************************************************************************
 * func         : JPEG_DEC_CreateDecompress
 * description  : create decompress for self
                  CNcomment: ����˽�н�����  CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID* JPEG_DEC_CreateDecompress()
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = NULL;

    pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)calloc(1, sizeof(JPEG_HDEC_HANDLE_S) * 8);
    if (NULL == pJpegHandle)
    {
        JPEG_TRACE("++++++++HI_JPEG_CreatHdecHandle failure\n");
        return NULL;
    }

    JPEG_HDEC_GetTimeStamp(&pJpegHandle->stProcInfo.DecCostTimes, NULL);

    pJpegHandle->JpegDev      = -1;
    pJpegHandle->CscDev       = -1;
    pJpegHandle->MemDev       = -1;
    pJpegHandle->SkipLines    = 0;
    pJpegHandle->u8ImageCount = 1;
    pJpegHandle->stImgInfo.jpeg_color_space   = HI_JPEG_FMT_BUTT;
    pJpegHandle->stImgInfo.output_color_space = HI_JPEG_FMT_BUTT;

    pJpegHandle->stProcInfo.UseStandardLibDec = HI_TRUE;

    return (HI_VOID*)pJpegHandle;
}

/*****************************************************************************
 * func         : JPEG_DEC_DestoryDecompress
 * description  : destory decompress
                  CNcomment:���ٽ����� CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_DestoryDecompress(HI_ULONG Handle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)Handle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    if (HI_FALSE == pJpegHandle->bReleaseRes)
    {
        JPEG_DEC_ReleaseRes(Handle);
    }

    free(pJpegHandle);

    return;
}

static inline HI_VOID JPEG_DEC_ReleaseRes(HI_ULONG HdecHandle)
{
    HI_U32 PreTime = 0;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    JPEG_DEC_SetLowDelayBufferDate(HdecHandle);

    JPEG_HDEC_FreeDecodeMemory(HdecHandle);

    JPEG_DEC_CloseDev(HdecHandle);

    PreTime = pJpegHandle->stProcInfo.DecCostTimes;
    JPEG_HDEC_GetTimeStamp(&pJpegHandle->stProcInfo.DecCostTimes,NULL);
    pJpegHandle->stProcInfo.DecCostTimes = pJpegHandle->stProcInfo.DecCostTimes - PreTime;

    JPEG_DEC_PrintProcMsg(HdecHandle);

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_ResetDecompress
 * description  : reset decompress
                  CNcomment:��λ������ CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_ResetDecompress(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    if (HI_FALSE == pJpegHandle->bReleaseRes)
    {
       JPEG_DEC_ReleaseRes(HdecHandle);
    }

    HI_GFX_Memset(pJpegHandle,0,sizeof(JPEG_HDEC_HANDLE_S));

    pJpegHandle->bReleaseRes  =  HI_TRUE;
    pJpegHandle->JpegDev      = -1;
    pJpegHandle->CscDev       = -1;
    pJpegHandle->MemDev       = -1;
    pJpegHandle->SkipLines    = 0;
    pJpegHandle->u8ImageCount = 1;
    pJpegHandle->stImgInfo.jpeg_color_space   = HI_JPEG_FMT_BUTT;
    pJpegHandle->stImgInfo.output_color_space = HI_JPEG_FMT_BUTT;

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_SetImgInfo
 * description  : set image info
                  CNcomment: ��������ͼƬ��Ϣ CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * param[in]    : pstImgInfo  CNcomment:    ͼ����Ϣ CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_SetImgInfo(HI_ULONG HdecHandle,JPEG_IMG_INFO_S *pstImgInfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL == pstImgInfo)
    {
        return;
    }

    HI_GFX_Memcpy(&(pJpegHandle->stImgInfo), pstImgInfo, sizeof(JPEG_IMG_INFO_S));

    if ((HI_JPEG_FMT_YUV420 == pstImgInfo->output_color_space) && (HI_JPEG_FMT_YUV420 != pstImgInfo->jpeg_color_space))
    {
        pJpegHandle->bOutYUV420SP = HI_TRUE;
    }

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_GetImgInfo
 * description  : Get image info
                  CNcomment:  ��ȡ����ͼƬ��Ϣ CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * param[in]    : pstImgInfo  CNcomment:    ͼ����Ϣ CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_GetImgInfo(HI_ULONG HdecHandle,JPEG_IMG_INFO_S *pstImgInfo)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    if (NULL == pstImgInfo)
    {
        return;
    }

    HI_GFX_Memcpy(pstImgInfo, &(pJpegHandle->stImgInfo), sizeof(JPEG_IMG_INFO_S));

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_IfSupport
 * description  : check whether hard decompress support
                  CNcomment: �ж�Ӳ�������Ƿ�֧�� CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
 HI_VOID JPEG_DEC_IfSupport(HI_ULONG HdecHandle)
{
    JPEG_DEC_SupportHardDecompress(HdecHandle);
}

/*****************************************************************************
 * func         : JPEG_DEC_GetSupportHdecState
 * description  : get if support hard decompress
                  CNcomment: �Ƿ�֧��Ӳ������ CNend\n
 * param[in]    : HdecHandle  CNcomment:    ���������        CNend\n
 * param[in]    : SupportHdec CNcomment:    Ӳ������֧��״̬  CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_GetSupportHdecState(HI_ULONG HdecHandle, HI_BOOL *SupportHdec)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL != SupportHdec)
    {
       *SupportHdec = pJpegHandle->SupportHardDec;
    }

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_SetSupportHdecState
 * description  : set support hard decompress
                  CNcomment: ����֧��Ӳ������ CNend\n
 * param[in]    : HdecHandle  CNcomment:    ���������        CNend\n
 * param[in]    : SupportHdec CNcomment:    Ӳ������֧��״̬  CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_SetSupportHdecState(HI_ULONG HdecHandle, HI_BOOL SupportHdec)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    pJpegHandle->SupportHardDec = SupportHdec;

    return;
}


/*****************************************************************************
 * func         : JPEG_DEC_GetHdecSuccess
 * description  : finish hard decompress
                  CNcomment: �Ƿ�Ӳ��������� CNend\n
 * param[in]    : HdecHandle   CNcomment:    ���������        CNend\n
 * param[in]    : HdecSuccess  CNcomment:    Ӳ���������״̬  CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_GetHdecSuccess(HI_ULONG HdecHandle, HI_BOOL *HdecSuccess)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL == HdecSuccess)
    {
       return;
    }

    if (HI_FALSE == pJpegHandle->SupportHardDec)
    {
       *HdecSuccess = HI_FALSE;
       return;
    }

    *HdecSuccess = pJpegHandle->bHdecSuccess;

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_IfOutPutYuv420Sp
 * description  : dec output yuv420sp
                  CNcomment: �������yuv420 CNend\n
 * param[in]    : HdecHandle      CNcomment:   ���������   CNend\n
 * param[in]    : OutPutYuv420Sp  CNcomment:   �Ƿ�������yuv420sp CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_IfOutPutYuv420Sp(HI_ULONG HdecHandle, HI_BOOL* OutPutYuv420Sp)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL != OutPutYuv420Sp)
    {
       *OutPutYuv420Sp = pJpegHandle->bOutYUV420SP;
    }

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_IfOutPutYuvSp
 * description  : dec output yuvsp
                  CNcomment: �������yuv CNend\n
 * param[in]    : HdecHandle   CNcomment:   ���������        CNend\n
 * param[in]    : OutPutYuvSp  CNcomment:   �Ƿ�������yuvsp CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_IfOutPutYuvSp(HI_ULONG HdecHandle, HI_BOOL* OutPutYuvSp)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL != OutPutYuvSp)
    {
      *OutPutYuvSp = pJpegHandle->bOutYCbCrSP;
    }

    return;
}


/*****************************************************************************
 * func         : JPEG_DEC_IfOutToUsrBuf
 * description  : out to usr buffer
                  CNcomment: �������yuv CNend\n
 * param[in]    : HdecHandle   CNcomment:   ���������        CNend\n
 * param[in]    : OutToUsrBuf  CNcomment:   �Ƿ��������û�buffer CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_IfOutToUsrBuf(HI_ULONG HdecHandle, HI_BOOL* OutToUsrBuf)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL != OutToUsrBuf)
    {
      *OutToUsrBuf = pJpegHandle->bOutUsrBuf;
    }

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_GetOutUsrBuf
 * description  : get out to usr buffer
                  CNcomment: ��ȡ�������yuv buffer CNend\n
 * param[in]    : HdecHandle   CNcomment:   ���������     CNend\n
 * param[in]    : OutYBuf      CNcomment:   �������buffer CNend\n
 * param[in]    : YStride      CNcomment:   �������stride CNend\n
 * param[in]    : OutUVBuf     CNcomment:   ���ɫ��buffer CNend\n
 * param[in]    : UVStride     CNcomment:   ���ɫ��stride CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
 HI_VOID JPEG_DEC_GetOutUsrBuf(HI_ULONG HdecHandle,HI_CHAR** OutYBuf,HI_U32 *YStride,HI_CHAR** OutUVBuf,HI_U32 *UVStride)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    if ((HI_FALSE == pJpegHandle->bHdecSuccess) && (HI_FALSE == pJpegHandle->bOutUsrBuf))
    {/** should output to scanlines buffer **/
        return;
    }

    if (NULL != OutYBuf)
    {
       *OutYBuf = pJpegHandle->stOutSurface.BufVir[0];
    }

    if (NULL != OutUVBuf)
    {
       *OutUVBuf = pJpegHandle->stOutSurface.BufVir[1];
    }

    if (NULL != YStride)
    {
        *YStride = pJpegHandle->stOutSurface.Stride[0];
    }

    if (NULL != UVStride)
    {
        *UVStride = pJpegHandle->stOutSurface.Stride[1];
    }

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_GetInputFmt
 * description  : input color space
                  CNcomment: �������ظ�ʽ CNend\n
 * param[in]    : HdecHandle      CNcomment:   ���������   CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_JPEG_FMT_E JPEG_DEC_GetInputFmt(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_JPEG_FMT_BUTT;
    }

    return pJpegHandle->stImgInfo.jpeg_color_space;
}


/*****************************************************************************
 * func         : JPEG_DEC_GetOutputFmt
 * description  : output color space
                  CNcomment: ������ظ�ʽ CNend\n
 * param[in]    : HdecHandle      CNcomment:   ���������   CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_JPEG_FMT_E JPEG_DEC_GetOutputFmt(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return HI_JPEG_FMT_BUTT;
    }

    return pJpegHandle->stImgInfo.output_color_space;
}

/*****************************************************************************
 * func         : JPEG_DEC_SetLuPixSum
 * description  : set lu pixel sum value
                  CNcomment: ����������Ⱥ� CNend\n
 * param[in]    : HdecHandle      CNcomment:   ���������   CNend\n
 * param[in]    : LuPixValue      CNcomment:   ���Ⱥ�   CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_SetLuPixSum(HI_ULONG HdecHandle, HI_ULONG LuPixValue)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    pJpegHandle->u64LuPixValue = LuPixValue;

    return;
}

 /*****************************************************************************
 * func         : JPEG_DEC_GetLuPixSum
 * description  : get lu pixel sum value
                  CNcomment: ��ȡ������Ⱥ� CNend\n
 * param[in]    : HdecHandle      CNcomment:   ���������   CNend\n
 * param[in]    : LuPixValue      CNcomment:   ���Ⱥ�   CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_GetLuPixSum(HI_ULONG HdecHandle, HI_U64 *LuPixValue)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL != LuPixValue)
    {
       *LuPixValue = pJpegHandle->u64LuPixValue;
    }

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_GetConvert
 * description  : get color convert function
                  CNcomment: ��ȡɫ�ʿռ�ת������ CNend\n
 * param[in]    : HdecHandle          CNcomment:���������       CNend\n
 * param[in]    : pstSdecColorConvert CNcomment:ɫ�ʿռ�ת������ CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_GetConvert(HI_ULONG HdecHandle, JPEG_SDEC_COLOR_CONVERT_S **pstSdecColorConvert)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    if (NULL != pstSdecColorConvert)
    {
       *pstSdecColorConvert = &(pJpegHandle->stSdecColorConvert);
    }

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_SetStreamBuffer
 * description  : set stream buffer
                  CNcomment: ������������buffer CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_SetStreamBuffer(HI_ULONG HdecHandle, HI_U32 DataSize, HI_BOOL bReadEof)
{
    HI_U32 DecDataBufIndex = 0;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    DecDataBufIndex = pJpegHandle->stInputDataBufInfo.DecDataBufIndex;
    if (DecDataBufIndex >= CONFIG_JPED_INPUT_DATA_BUFFER_NUM)
    {
       return;
    }

    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[DecDataBufIndex].SaveStreamBufSize = DataSize;

    pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[DecDataBufIndex].DecDataEof = bReadEof;

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_GetStreamBuffer
 * description  : get stream buffer
                  CNcomment: ��ȡ��������buffer CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_GetStreamBuffer(HI_ULONG HdecHandle, HI_CHAR** pStreamBuf, HI_U32 *pBufSize, HI_BOOL *pPhyInput)
{
    HI_U32 ReadDataIndex = 0;
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    ReadDataIndex = pJpegHandle->stInputDataBufInfo.ReadDataBufIndex;
    if (ReadDataIndex >= CONFIG_JPED_INPUT_DATA_BUFFER_NUM)
    {
       return;
    }

    pJpegHandle->stInputDataBufInfo.DecDataBufIndex = ReadDataIndex;

    if (NULL != pStreamBuf)
    {
      *pStreamBuf = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[ReadDataIndex].pSaveStreamVirBuf;
    }

    if (NULL != pBufSize)
    {
       *pBufSize = pJpegHandle->stInputDataBufInfo.stSaveStreamBuf[ReadDataIndex].SaveStreamBufSize;
    }

    if (NULL != pPhyInput)
    {
       *pPhyInput = pJpegHandle->stInputDataBufInfo.stInputStreamBuf.SupportUserPhyInputDataBuf;
    }

    ReadDataIndex++;

    if (ReadDataIndex >= CONFIG_JPED_INPUT_DATA_BUFFER_NUM)
    {
       ReadDataIndex = 0;
    }

    pJpegHandle->stInputDataBufInfo.ReadDataBufIndex = ReadDataIndex;

    return;
}

/*****************************************************************************
 * func         : JPEG_DEC_SeekInputBuffer
 * description  : seek stream buffer
                  CNcomment: �������� CNend\n
 * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
 * retval       : NA
 * retval       : NA
 * others:      : NA
 *****************************************************************************/
HI_VOID JPEG_DEC_SeekInputBuffer(HI_ULONG HdecHandle, HI_CHAR** pCurBuf, HI_U32 *pBufPos, HI_U32 *pSeekPos)
{
    JPEG_IMG_INFO_S stImgInfo;

    HI_GFX_Memset(&stImgInfo,0x0,sizeof(JPEG_IMG_INFO_S));

    JPEG_DEC_GetImgInfo(HdecHandle, &stImgInfo);

    if (NULL != pCurBuf)
    {
       *pCurBuf = stImgInfo.next_input_byte;
    }

    if (NULL != pBufPos)
    {
       *pBufPos = stImgInfo.bytes_in_buffer;
    }

    if (NULL != pSeekPos)
    {
       *pSeekPos = stImgInfo.curpos_in_buffer;
    }

    return;
}
