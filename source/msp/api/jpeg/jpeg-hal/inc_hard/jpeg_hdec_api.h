/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : jpeg_hdec_api.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/
#ifndef __JPEG_HDEC_API_H__
#define __JPEG_HDEC_API_H__

/*********************************add include here**********************************************/
#include  "hi_jpeg_config.h"
#include  "hi_drv_jpeg.h"

#ifdef CONFIG_JPEG_SAVE_SCEN
#include "hi_jpeg_reg.h"
#endif


#include  "jpeg_hdec_hal.h"

#include  "jpeg_sdec_exif.h"

/***********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ********************************************/
     #define CONFIG_JPEG_SCALE_MULTIPLE_8                           (3)
     #define CONFIG_JPED_INPUT_DATA_BUFFER_NUM                      (2)

     #define CONFIG_JPED_INPUT_DATA_BUFFER_ALIGN                    (128)
     #define CONFIG_JPED_INPUT_DATA_ONE_BUFFER_RESERVE_SIZE         (128)
     #define CONFIG_JPED_INPUT_DATA_ONE_BUFFER_SIZE                 (512 * 1024)

     /*************************** Enum Definition **********************************************/


    /*************************** Structure Definition ******************************************/
     typedef struct tatINPUT_STREAM_BUF_S
     {
         HI_BOOL UseSecondInputBuf;           /**<-- use second input buffer     >**//**<-- 是否使用第二块码流buffer >**/
         HI_BOOL SupportUserPhyInputDataBuf;  /**<-- whether user input data buffer is physical      >**//**<-- 使用用户输入的物理内存buffer 数据处理>**/
         HI_BOOL SupportUserInputBufReturn;   /**<-- check whether stream save with two buffer  >**//**<-- 支持内存回绕方式的处理 >**/
         HI_CHAR *pUserSecondInputDataVirBuf; /**<-- this is second input data virtual buffer  >**//**<-- 内存回绕方式第二块码流虚拟内存>**/
         HI_CHAR *pUserFirstInputDataVirBuf;  /**<-- this is first input data virtual buffer or input data start virtual buffer   >**//**<-- 第一块码流虚拟内存>**/
         HI_U32 UserInputDataPhyBuf;          /**<-- input one or pool physical buffer start address  >**//**<-- 用户输入的码流连续物理地址 >**/
         HI_ULONG UserTotalInputBufSize;      /**<-- input one or pool buffer size   >**//**<-- 用户输入的码流数据大小 >**/
         HI_ULONG UserFirstInputBufSize;      /**<-- first input data buffer size       >**//**<-- 用户输入的第一块码流数据大小>**/
         HI_ULONG UserSecondInputBufSize;     /**<-- second input data buffer size  >**//**<-- 用户输入的第二块码流数据大小 >**/
         HI_ULONG UserInputCurPos;            /**<-- the input data current position, file or vir mem used  >**//**<-- 进入硬件解码之前码流读取的位置>**/
         HI_ULONG UserDataHasBeenReadSize;    /**<-- the input data has been read size, memory return used  >**//**<-- 码流已经被读取的大小，仅在内存回绕方式使用>**/
     }INPUT_STREAM_BUF_S;

     typedef struct tagINPUT_DATA_BUF_S
     {
         HI_BOOL DecDataEof;
         HI_U32 SaveStreamBufSize;
         HI_CHAR *pSaveStreamVirBuf;  /**<-- input data virtual buffer that be use to decode        >**//**<-- 存储码流buffer  虚拟地址 >**/
         HI_U32 SaveStreamPhyBuf;     /**<-- input data physical buffer that be use to decode     >**//**<-- 存储码流buffer 连续物理地址 >**/
     }INPUT_DEC_DATA_BUF_S;

     typedef struct tagJPEG_INPUT_DATA_BUF_INFO_S
     {
         HI_U32 ReadDataBufIndex;
         HI_U32 DecDataBufIndex;
         INPUT_STREAM_BUF_S stInputStreamBuf;
         INPUT_DEC_DATA_BUF_S stSaveStreamBuf[CONFIG_JPED_INPUT_DATA_BUFFER_NUM]; /**<-- hard decode data buffer >**//**<-- 解码使用的存储码流buffer 信息 >**/
     }JPEG_INPUT_DATA_BUF_INFO_S;

     typedef struct tagJPEG_PROC_INFO_S
     {
         HI_BOOL NeedProcMsg;
         HI_BOOL UseStandardLibDec;
         HI_BOOL LowDelaySupport;
         HI_BOOL ProgressiveMode;
         HI_BOOL ArithMode;
         HI_BOOL DriSupport;
         HI_BOOL HufNumSupport;
         HI_BOOL ScaleSupport;
         HI_BOOL SampleFactorSupport;
         HI_BOOL InputImgSizeSupport;
         HI_BOOL OutColorSpaceSupport;
         HI_BOOL OpenDevSuccess;
         HI_BOOL AllocMemSuccess;
         HI_BOOL GetDevSuccess;
         HI_BOOL OpenCscDevSuccess;
         HI_BOOL OpenIonDevSuccess;
         HI_S32  SupportOutUsrBuf;
         HI_U32  DataPrecision;
         HI_U32  HardDecTimes;
         HI_U32  DecCostTimes;
     }JPEG_PROC_INFO_S;

     typedef struct tagJPEG_HDEC_HANDLE_S
     {
          volatile HI_CHAR *pJpegRegVirAddr;
          HI_BOOL bUseHisiLib;
          HI_BOOL bDiscardScanlines;
          HI_BOOL bSeekToSoftDec;
          HI_BOOL bOutUsrBuf;
          HI_BOOL SupportHardDec;
          HI_BOOL EnStopDecode;
          HI_BOOL bHdecSuccess;
          HI_BOOL bCSCEnd;
          HI_BOOL bOutYCbCrSP;
          HI_BOOL bDecOutColorSpaecXRGB;
          HI_BOOL bFinishSetPara;
          HI_BOOL bCheckedSupportHardDec;
          HI_BOOL bCrop;
          HI_BOOL bSetCropRect;
          HI_U32  DecXRGBLinePhyBuf;
          HI_U32  SkipLines;
          #ifdef CONFIG_JPEG_SAVE_SCEN
          HI_S32  s32RegData[JPGD_REG_LENGTH];
          FILE* pScenFile;
          #endif
          HI_BOOL  bOutYUV420SP;
          /** pix sum **/
          HI_U64   u64LuPixValue;
          /**<------------lowdelay info ------**/
          HI_BOOL  bLowDelayEn;
          HI_U32   u32PhyLineBuf;
          HI_CHAR* pVirLineBuf;
          /**<--------------------------------**/
          HI_S32   s32ClientData;
          HI_S32   JpegDev;
          HI_S32   CscDev;
          HI_S32   MemDev;
          HI_U32   ScalRation;
          HI_BOOL  bReleaseRes;
          HI_BOOL  UseHidlOpen;
          /** ion mem **/
          HI_VOID *pSaveStreamMemHandle;
          HI_VOID *pMiddleMemHandle;
          HI_VOID *pMinMemHandle;
          HI_VOID *pOutMemHandle;
          /************************/
          HI_U32 ResByteConsum;
          JPEG_HDEC_SOFINFO_S stJpegSofInfo;
          /**<------------proc info ----------**/
          JPEG_PROC_INFO_S stProcInfo;
          /**<--------------------------------**/
          JPEG_SURFACE_S  stDecSurface;
          JPEG_SURFACE_S  stOutSurface;
          JPEG_IMG_INFO_S stImgInfo;
          JPEG_INPUT_DATA_BUF_INFO_S stInputDataBufInfo;
          JPEG_SDEC_COLOR_CONVERT_S stSdecColorConvert;
          /**<------------exif para ----------**/
	      HI_BOOL  bExifSupport;
	      HI_BOOL  bIsHDR;
	      HI_U8    u8ImageCount;
	      HI_CHAR* pThumbnailAddr;
	      HI_U32   u32ThumbnailSize;
          JPEG_EXIF_INFO_S  stExifInfo;
          /**<--------------------------------**/
    }JPEG_HDEC_HANDLE_S,*JPEG_HDEC_HANDLE_S_PTR;

    /********************** Global Variable declaration ****************************************/

    /******************************* API declaration *******************************************/

    /*******************************************************************************************/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __JPEG_HDEC_API_H__*/
