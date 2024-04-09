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
                    CNcomment: 创建私有解码器  CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID* JPEG_DEC_CreateDecompress();

   /*****************************************************************************
    * func         : JPEG_DEC_DestoryDecompress
    * description  : destory decompress
                     CNcomment:销毁解码器 CNend\n
    * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
    * retval       : NA
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
    HI_VOID JPEG_DEC_DestoryDecompress(HI_ULONG Handle);

   /*****************************************************************************
   * func         : JPEG_DEC_ResetDecompress
   * description  : reset decompress
                    CNcomment:复位解码器 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_ResetDecompress(HI_ULONG HdecHandle);

  /*****************************************************************************
   * func         : JPEG_DEC_SetStreamBuffer
   * description  : set stream buffer
                    CNcomment: 设置输入码流buffer CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetStreamBuffer(HI_ULONG HdecHandle, HI_U32 DataSize, HI_BOOL bReadEof);

  /*****************************************************************************
   * func         : JPEG_DEC_GetStreamBuffer
   * description  : get stream buffer
                    CNcomment: 获取输入码流buffer CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_GetStreamBuffer(HI_ULONG HdecHandle, HI_CHAR** pStreamBuf, HI_U32 *pBufSize, HI_BOOL *pPhyInput);

   /*****************************************************************************
   * func         : JPEG_DEC_SeekInputBuffer
   * description  : seek stream buffer
                    CNcomment: 码流回退 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SeekInputBuffer(HI_ULONG HdecHandle, HI_CHAR** pCurBuf, HI_U32 *pBufPos, HI_U32 *pSeekPos);

   /*****************************************************************************
   * func         : JPEG_DEC_SetImgInfo
   * description  : set image info
                    CNcomment:  设置输入图片信息 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * param[in]    : pstImgInfo  CNcomment:    图像信息 CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetImgInfo(HI_ULONG HdecHandle,JPEG_IMG_INFO_S *pstImgInfo);

   /*****************************************************************************
    * func         : JPEG_DEC_GetImgInfo
    * description  : Get image info
                     CNcomment:  获取输入图片信息 CNend\n
    * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
    * param[in]    : pstImgInfo  CNcomment:    图像信息 CNend\n
    * retval       : NA
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
   HI_VOID JPEG_DEC_GetImgInfo(HI_ULONG HdecHandle,JPEG_IMG_INFO_S *pstImgInfo);

   /*****************************************************************************
   * func         : JPEG_DEC_IfSupport
   * description  : check whether hard decompress support
                    CNcomment: 判断硬件解码是否支持 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_IfSupport(HI_ULONG HdecHandle);

   /*****************************************************************************
   * func         : JPEG_HDEC_SupportCrop
   * description  : check whether support crop decode
                    CNcomment: 判断是否支持区域解码 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_BOOL JPEG_DEC_SupportCrop(HI_ULONG HdecHandle);

   /*****************************************************************************
   * func         : JPEG_DEC_SetCropRect
   * description  : set crop rect
                    CNcomment: 设置裁剪区域 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * param[in]    : PosX   CNcomment:    X坐标    CNend\n
   * param[in]    : PosY   CNcomment:    Y坐标     CNend\n
   * param[in]    : Width  CNcomment:    宽度      CNend\n
   * param[in]    : Height CNcomment:    高度      CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetCropRect(HI_ULONG HdecHandle,HI_U32 PosX, HI_U32 PosY, HI_U32 Width,HI_U32 Height);

   /*****************************************************************************
   * func         : JPEG_DEC_SetCropXW
   * description  : set crop x and width
                    CNcomment: 设置解码输出x坐标和宽度 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * param[in]    : Crop_X      CNcomment:    X坐标      CNend\n
   * param[in]    : Crop_Width  CNcomment:    宽度       CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetCropXW(HI_ULONG HdecHandle,HI_U32 Crop_X, HI_U32 Crop_Width);

   /*****************************************************************************
   * func         : JPEG_DEC_SetCropYH
   * description  : set crop y and height
                    CNcomment: 设置解码输出y坐标和高度 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * param[in]    : Crop_Y      CNcomment:    Y坐标      CNend\n
   * param[in]    : Crop_H      CNcomment:    高度       CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_S32  JPEG_DEC_SetCropYH(HI_ULONG HdecHandle, HI_U32 Crop_Y, HI_U32 Crop_H);

   /*****************************************************************************
   * func         : JPEG_DEC_SetSkipLines
   * description  : set skip lines
                    CNcomment: 设置丢了多少行 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * param[in]    : SkipLines   CNcomment:    丢的行数   CNend\n
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_S32  JPEG_DEC_SetSkipLines(HI_ULONG HdecHandle, HI_U32 SkipLines);

   /*****************************************************************************
   * func         : JPEG_DEC_GetSkipLines
   * description  : get skip lines
                    CNcomment: 获取丢了多少行 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * param[in]    : SkipLines   CNcomment:    获取丢的行数   CNend\n
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_GetSkipLines(HI_ULONG HdecHandle, HI_U32 *SkipLines);

   /*****************************************************************************
   * func         : JPEG_DEC_SetDisScanMark
   * description  : set skip mark
                    CNcomment: 设置丢行标记  CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄 CNend\n
   * param[in]    : bDiscardScanlines   CNcomment:标记   CNend\n
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetDisScanMark(HI_ULONG HdecHandle, HI_BOOL bDiscardScanlines);

   /*****************************************************************************
   * func         : JPEG_DEC_GetSupportHdecState
   * description  : get if support hard decompress
                    CNcomment: 是否支持硬件解码 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄        CNend\n
   * param[in]    : SupportHdec CNcomment:    硬件解码支持状态  CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_GetSupportHdecState(HI_ULONG HdecHandle, HI_BOOL *SupportHdec);

   /*****************************************************************************
   * func         : JPEG_DEC_SetSupportHdecState
   * description  : set support hard decompress
                    CNcomment: 设置支持硬件解码 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄        CNend\n
   * param[in]    : SupportHdec CNcomment:    硬件解码支持状态  CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_SetSupportHdecState(HI_ULONG HdecHandle, HI_BOOL SupportHdec);

   /*****************************************************************************
   * func         : JPEG_DEC_GetHdecSuccess
   * description  : finish hard decompress
                    CNcomment: 是否硬件解码完成 CNend\n
   * param[in]    : HdecHandle  CNcomment:    解码器句柄        CNend\n
   * param[in]    : HdecSuccess  CNcomment:   硬件解码完成状态  CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_GetHdecSuccess(HI_ULONG HdecHandle, HI_BOOL *HdecSuccess);

   /*****************************************************************************
    * func         : JPEG_DEC_SetPara
    * description  : set hard register para in jpeg_start_decompress
                     CNcomment: 在开始解码中设置寄存器 CNend\n
    * param[in]    : HdecHandle   CNcomment:   解码器句柄   CNend\n
    * retval       : NA
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
    HI_VOID JPEG_DEC_SetPara(HI_ULONG HdecHandle);

   /*****************************************************************************
    * func         : JPEG_DEC_StartDec
    * description  : start decompress
                     CNcomment: 启动解码 CNend\n
    * param[in]    : HdecHandle        CNcomment:   解码器句柄   CNend\n
    * param[in]    : HasBeenStartDec   CNcomment:   是否已经启动过解码   CNend\n
    * param[in]    : SupportSeekToSoft CNcomment:   是否支持码流回退解码 CNend\n
    * retval       : if finish hard dec
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
   HI_BOOL JPEG_DEC_StartDec(HI_ULONG HdecHandle, HI_BOOL HasBeenStartDec, HI_BOOL SupportSeekToSoft);

    /*****************************************************************************
     * func         : JPEG_DEC_CscConvert
     * description  : csc convert
                      CNcomment: CSC 色彩空间转换 CNend\n
     * param[in]    : HdecHandle   CNcomment:   解码器句柄   CNend\n
     * retval       : NA
     * retval       : NA
     * others:      : NA
     *****************************************************************************/
     HI_S32 JPEG_DEC_CscConvert(HI_ULONG HdecHandle, HI_CHAR* ScanlineBuf, HI_U32 MaxLines, HI_U32 *pCurScanlines);

   /*****************************************************************************
    * func         : JPEG_DEC_GetStopDec
    * description  : get stop decompress
                     CNcomment: 获取终止解码状态 CNend\n
    * param[in]    : HdecHandle   CNcomment:   解码器句柄   CNend\n
    * param[in]    : StopDec      CNcomment:   是否终止解码 CNend\n
    * retval       : NA
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
    HI_VOID JPEG_DEC_GetStopDec(HI_ULONG HdecHandle, HI_BOOL* StopDec);

  /*****************************************************************************
   * func         : JPEG_DEC_IfOutPutYuv420Sp
   * description  : dec output yuv420sp
                    CNcomment: 解码输出yuv420 CNend\n
   * param[in]    : HdecHandle      CNcomment:   解码器句柄   CNend\n
   * param[in]    : OutPutYuv420Sp  CNcomment:   是否解码输出yuv420sp CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_IfOutPutYuv420Sp(HI_ULONG HdecHandle, HI_BOOL* OutPutYuv420Sp);

  /*****************************************************************************
   * func         : JPEG_DEC_IfOutPutYuvSp
   * description  : dec output yuvsp
                    CNcomment: 解码输出yuv CNend\n
   * param[in]    : HdecHandle   CNcomment:   解码器句柄        CNend\n
   * param[in]    : OutPutYuvSp  CNcomment:   是否解码输出yuvsp CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_IfOutPutYuvSp(HI_ULONG HdecHandle, HI_BOOL* OutPutYuvSp);

  /*****************************************************************************
   * func         : JPEG_DEC_IfOutToUsrBuf
   * description  : out to usr buffer
                    CNcomment: 解码输出yuv CNend\n
   * param[in]    : HdecHandle   CNcomment:   解码器句柄        CNend\n
   * param[in]    : OutToUsrBuf  CNcomment:   是否解码输出用户buffer CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_IfOutToUsrBuf(HI_ULONG HdecHandle, HI_BOOL* OutToUsrBuf);

  /*****************************************************************************
   * func         : JPEG_DEC_GetInputFmt
   * description  : input color space
                    CNcomment: 输入像素格式 CNend\n
   * param[in]    : HdecHandle      CNcomment:   解码器句柄   CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_JPEG_FMT_E JPEG_DEC_GetInputFmt(HI_ULONG HdecHandle);

  /*****************************************************************************
   * func         : JPEG_DEC_GetOutputFmt
   * description  : output color space
                    CNcomment: 输出像素格式 CNend\n
   * param[in]    : HdecHandle      CNcomment:   解码器句柄   CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_JPEG_FMT_E JPEG_DEC_GetOutputFmt(HI_ULONG HdecHandle);

  /*****************************************************************************
   * func         : JPEG_DEC_GetOutUsrBuf
   * description  : get out to usr buffer
                    CNcomment: 获取解码输出yuv buffer CNend\n
   * param[in]    : HdecHandle   CNcomment:   解码器句柄     CNend\n
   * param[in]    : OutYBuf      CNcomment:   输出亮度buffer CNend\n
   * param[in]    : YStride      CNcomment:   输出亮度stride CNend\n
   * param[in]    : OutUVBuf     CNcomment:   输出色度buffer CNend\n
   * param[in]    : UVStride     CNcomment:   输出色度stride CNend\n
   * retval       : NA
   * retval       : NA
   * others:      : NA
   *****************************************************************************/
   HI_VOID JPEG_DEC_GetOutUsrBuf(HI_ULONG HdecHandle,HI_CHAR** OutYBuf,HI_U32 *YStride,HI_CHAR** OutUVBuf,HI_U32 *UVStride);


   /*****************************************************************************
    * func         : JPEG_DEC_SetLuPixSum
    * description  : set lu pixel sum value
                     CNcomment: 设置输出亮度和 CNend\n
    * param[in]    : HdecHandle      CNcomment:   解码器句柄   CNend\n
    * param[in]    : LuPixValue      CNcomment:   亮度和   CNend\n
    * retval       : NA
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
    HI_VOID JPEG_DEC_SetLuPixSum(HI_ULONG HdecHandle, HI_ULONG LuPixValue);

   /*****************************************************************************
    * func         : JPEG_DEC_GetLuPixSum
    * description  : get lu pixel sum value
                     CNcomment: 获取输出亮度和 CNend\n
    * param[in]    : HdecHandle      CNcomment:   解码器句柄   CNend\n
    * param[in]    : LuPixValue      CNcomment:   亮度和   CNend\n
    * retval       : NA
    * retval       : NA
    * others:      : NA
    *****************************************************************************/
    HI_VOID JPEG_DEC_GetLuPixSum(HI_ULONG HdecHandle, HI_U64 *LuPixValue);

    /*****************************************************************************
    * func         : JPEG_DEC_GetConvert
    * description  : get color convert function
                     CNcomment: 获取色彩空间转换函数 CNend\n
    * param[in]    : HdecHandle          CNcomment:解码器句柄       CNend\n
    * param[in]    : pstSdecColorConvert CNcomment:色彩空间转换函数 CNend\n
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
