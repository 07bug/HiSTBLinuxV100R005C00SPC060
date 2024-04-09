/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : jpeg_sdec_api.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/
#ifndef __JPEG_SDEC_API_H__
#define __JPEG_SDEC_API_H__


/*********************************add include here**********************************************/
#include  "hi_jpeg_config.h"
#include  "hi_drv_jpeg.h"

#ifdef CONFIG_JPEG_SAVE_SCEN
#include "hi_jpeg_reg.h"
#endif


#include  "jpeg_hdec_hal.h"

/***********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


  /***************************** Macro Definition ********************************************/

   /*************************** Enum Definition **********************************************/

  /*************************** Structure Definition ******************************************/

  /********************** Global Variable declaration ****************************************/

  /******************************* API declaration *******************************************/

  /*****************************************************************************
   * func         : JPEG_DEC_CreateDecompress
   * description  : create decompress for self
                    CNcomment: ����˽�н�����  CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID* JPEG_DEC_CreateDecompress();

   /*****************************************************************************
    * func         : JPEG_DEC_DestoryDecompress
    * description  : destory decompress
                     CNcomment:���ٽ����� CNend\n
    * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
    * retval       : NA
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
    HI_VOID JPEG_DEC_DestoryDecompress(HI_ULONG Handle);

   /*****************************************************************************
   * func         : JPEG_DEC_ResetDecompress
   * description  : reset decompress
                    CNcomment:��λ������ CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_ResetDecompress(HI_ULONG HdecHandle);

  /*****************************************************************************
   * func         : JPEG_DEC_SetStreamBuffer
   * description  : set stream buffer
                    CNcomment: ������������buffer CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetStreamBuffer(HI_ULONG HdecHandle, HI_U32 DataSize, HI_BOOL bReadEof);

  /*****************************************************************************
   * func         : JPEG_DEC_GetStreamBuffer
   * description  : get stream buffer
                    CNcomment: ��ȡ��������buffer CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_GetStreamBuffer(HI_ULONG HdecHandle, HI_CHAR** pStreamBuf, HI_U32 *pBufSize, HI_BOOL *pPhyInput);

   /*****************************************************************************
   * func         : JPEG_DEC_SeekInputBuffer
   * description  : seek stream buffer
                    CNcomment: �������� CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SeekInputBuffer(HI_ULONG HdecHandle, HI_CHAR** pCurBuf, HI_U32 *pBufPos, HI_U32 *pSeekPos);

   /*****************************************************************************
   * func         : JPEG_DEC_SetImgInfo
   * description  : set image info
                    CNcomment:  ��������ͼƬ��Ϣ CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * param[in]    : pstImgInfo  CNcomment:    ͼ����Ϣ CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetImgInfo(HI_ULONG HdecHandle,JPEG_IMG_INFO_S *pstImgInfo);

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
   HI_VOID JPEG_DEC_GetImgInfo(HI_ULONG HdecHandle,JPEG_IMG_INFO_S *pstImgInfo);

   /*****************************************************************************
   * func         : JPEG_DEC_IfSupport
   * description  : check whether hard decompress support
                    CNcomment: �ж�Ӳ�������Ƿ�֧�� CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_IfSupport(HI_ULONG HdecHandle);

   /*****************************************************************************
   * func         : JPEG_HDEC_SupportCrop
   * description  : check whether support crop decode
                    CNcomment: �ж��Ƿ�֧��������� CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_BOOL JPEG_DEC_SupportCrop(HI_ULONG HdecHandle);

   /*****************************************************************************
   * func         : JPEG_DEC_SetCropRect
   * description  : set crop rect
                    CNcomment: ���òü����� CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * param[in]    : PosX   CNcomment:    X����    CNend\n
   * param[in]    : PosY   CNcomment:    Y����     CNend\n
   * param[in]    : Width  CNcomment:    ���      CNend\n
   * param[in]    : Height CNcomment:    �߶�      CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetCropRect(HI_ULONG HdecHandle,HI_U32 PosX, HI_U32 PosY, HI_U32 Width,HI_U32 Height);

   /*****************************************************************************
   * func         : JPEG_DEC_SetCropXW
   * description  : set crop x and width
                    CNcomment: ���ý������x����Ϳ�� CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * param[in]    : Crop_X      CNcomment:    X����      CNend\n
   * param[in]    : Crop_Width  CNcomment:    ���       CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetCropXW(HI_ULONG HdecHandle,HI_U32 Crop_X, HI_U32 Crop_Width);

   /*****************************************************************************
   * func         : JPEG_DEC_SetCropYH
   * description  : set crop y and height
                    CNcomment: ���ý������y����͸߶� CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * param[in]    : Crop_Y      CNcomment:    Y����      CNend\n
   * param[in]    : Crop_H      CNcomment:    �߶�       CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_S32  JPEG_DEC_SetCropYH(HI_ULONG HdecHandle, HI_U32 Crop_Y, HI_U32 Crop_H);

   /*****************************************************************************
   * func         : JPEG_DEC_SetSkipLines
   * description  : set skip lines
                    CNcomment: ���ö��˶����� CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * param[in]    : SkipLines   CNcomment:    ��������   CNend\n
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_S32  JPEG_DEC_SetSkipLines(HI_ULONG HdecHandle, HI_U32 SkipLines);

   /*****************************************************************************
   * func         : JPEG_DEC_GetSkipLines
   * description  : get skip lines
                    CNcomment: ��ȡ���˶����� CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * param[in]    : SkipLines   CNcomment:    ��ȡ��������   CNend\n
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_GetSkipLines(HI_ULONG HdecHandle, HI_U32 *SkipLines);

   /*****************************************************************************
   * func         : JPEG_DEC_SetDisScanMark
   * description  : set skip mark
                    CNcomment: ���ö��б��  CNend\n
   * param[in]    : HdecHandle  CNcomment:    ��������� CNend\n
   * param[in]    : bDiscardScanlines   CNcomment:���   CNend\n
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetDisScanMark(HI_ULONG HdecHandle, HI_BOOL bDiscardScanlines);

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
   HI_VOID JPEG_DEC_GetSupportHdecState(HI_ULONG HdecHandle, HI_BOOL *SupportHdec);

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
   HI_VOID JPEG_DEC_SetSupportHdecState(HI_ULONG HdecHandle, HI_BOOL SupportHdec);

   /*****************************************************************************
   * func         : JPEG_DEC_GetHdecSuccess
   * description  : finish hard decompress
                    CNcomment: �Ƿ�Ӳ��������� CNend\n
   * param[in]    : HdecHandle  CNcomment:    ���������        CNend\n
   * param[in]    : HdecSuccess  CNcomment:   Ӳ���������״̬  CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_GetHdecSuccess(HI_ULONG HdecHandle, HI_BOOL *HdecSuccess);

   /*****************************************************************************
    * func         : JPEG_DEC_SetPara
    * description  : set hard register para in jpeg_start_decompress
                     CNcomment: �ڿ�ʼ���������üĴ��� CNend\n
    * param[in]    : HdecHandle   CNcomment:   ���������   CNend\n
    * retval       : NA
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
    HI_VOID JPEG_DEC_SetPara(HI_ULONG HdecHandle);

   /*****************************************************************************
    * func         : JPEG_DEC_StartDec
    * description  : start decompress
                     CNcomment: �������� CNend\n
    * param[in]    : HdecHandle        CNcomment:   ���������   CNend\n
    * param[in]    : HasBeenStartDec   CNcomment:   �Ƿ��Ѿ�����������   CNend\n
    * param[in]    : SupportSeekToSoft CNcomment:   �Ƿ�֧���������˽��� CNend\n
    * retval       : if finish hard dec
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
   HI_BOOL JPEG_DEC_StartDec(HI_ULONG HdecHandle, HI_BOOL HasBeenStartDec, HI_BOOL SupportSeekToSoft);

    /*****************************************************************************
     * func         : JPEG_DEC_CscConvert
     * description  : csc convert
                      CNcomment: CSC ɫ�ʿռ�ת�� CNend\n
     * param[in]    : HdecHandle   CNcomment:   ���������   CNend\n
     * retval       : NA
     * retval       : NA
     * others:      : NA
     *****************************************************************************/
     HI_S32 JPEG_DEC_CscConvert(HI_ULONG HdecHandle, HI_CHAR* ScanlineBuf, HI_U32 MaxLines, HI_U32 *pCurScanlines);

   /*****************************************************************************
    * func         : JPEG_DEC_GetStopDec
    * description  : get stop decompress
                     CNcomment: ��ȡ��ֹ����״̬ CNend\n
    * param[in]    : HdecHandle   CNcomment:   ���������   CNend\n
    * param[in]    : StopDec      CNcomment:   �Ƿ���ֹ���� CNend\n
    * retval       : NA
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
    HI_VOID JPEG_DEC_GetStopDec(HI_ULONG HdecHandle, HI_BOOL* StopDec);

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
   HI_VOID JPEG_DEC_IfOutPutYuv420Sp(HI_ULONG HdecHandle, HI_BOOL* OutPutYuv420Sp);

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
   HI_VOID JPEG_DEC_IfOutPutYuvSp(HI_ULONG HdecHandle, HI_BOOL* OutPutYuvSp);

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
   HI_VOID JPEG_DEC_IfOutToUsrBuf(HI_ULONG HdecHandle, HI_BOOL* OutToUsrBuf);

  /*****************************************************************************
   * func         : JPEG_DEC_GetInputFmt
   * description  : input color space
                    CNcomment: �������ظ�ʽ CNend\n
   * param[in]    : HdecHandle      CNcomment:   ���������   CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_JPEG_FMT_E JPEG_DEC_GetInputFmt(HI_ULONG HdecHandle);

  /*****************************************************************************
   * func         : JPEG_DEC_GetOutputFmt
   * description  : output color space
                    CNcomment: ������ظ�ʽ CNend\n
   * param[in]    : HdecHandle      CNcomment:   ���������   CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_JPEG_FMT_E JPEG_DEC_GetOutputFmt(HI_ULONG HdecHandle);

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
   HI_VOID JPEG_DEC_GetOutUsrBuf(HI_ULONG HdecHandle,HI_CHAR** OutYBuf,HI_U32 *YStride,HI_CHAR** OutUVBuf,HI_U32 *UVStride);


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
    HI_VOID JPEG_DEC_SetLuPixSum(HI_ULONG HdecHandle, HI_ULONG LuPixValue);

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
    HI_VOID JPEG_DEC_GetLuPixSum(HI_ULONG HdecHandle, HI_U64 *LuPixValue);

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
    HI_VOID JPEG_DEC_GetConvert(HI_ULONG HdecHandle, JPEG_SDEC_COLOR_CONVERT_S **pstSdecColorConvert);

    /*******************************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __JPEG_SDEC_API_H__*/
