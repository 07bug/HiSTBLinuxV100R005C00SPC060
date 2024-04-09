/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hdec_hal.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : 硬件解码及新增功能对外接口
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
***************************************************************************************************/
#ifndef __JPEG_HDEC_HAL_H__
#define __JPEG_HDEC_HAL_H__

/*********************************add include here*************************************************/
#include "hi_type.h"
#include "hi_jpeg_config.h"
#include "hi_jpeg_api.h"

/**************************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


    /***************************** Macro Definition ***********************************************/
    #define MAX_NUM_HUFF_TBLS              4
    #define MAX_NUM_QUANT_TBLS             4
     /*************************** Enum Definition *************************************************/


    /*************************** Structure Definition *********************************************/
    typedef struct tagJPEG_CROP_S
     {
         HI_U32 x, y;
         HI_U32 w, h;
     }JPEG_CROP_S;

     typedef struct tagJPEGHUFFTBL
     {
        HI_U8   bits[17];
        HI_U8   huffval[256];
        HI_BOOL bHasHuffTbl;
     }JPEG_HUFF_TBL;

     typedef struct tagJPEGQUANTTBL
     {
         HI_BOOL bHasQuantTbl;
         HI_U16  quantval[HI_DCT_SIZE2];
     }JPEG_QUANT_TBL;

     typedef struct tagCOMPONENT_INFO_S
     {
          HI_U8   u8HorSampleFac;
          HI_U8   u8VerSampleFac;
          HI_S32  ComponentId;
          HI_S32  ComponentIndex;
          HI_S32  QuantTblNo;
          HI_S32  DcTblNo;
          HI_S32  AcTblNo;
     }COMPONENT_INFO_S;

     typedef struct tagJPEG_SURFACE_S
     {
         HI_CHAR* BufVir[HI_JPEG_MAX_COMPONENT_NUM];
         HI_U32 BufPhy[HI_JPEG_MAX_COMPONENT_NUM];
         HI_U32 Width[HI_JPEG_MAX_COMPONENT_NUM];
         HI_U32 Height[HI_JPEG_MAX_COMPONENT_NUM];
         HI_U32 Stride[HI_JPEG_MAX_COMPONENT_NUM];
         HI_U32 Size[HI_JPEG_MAX_COMPONENT_NUM];
         JPEG_CROP_S stCropRect;
     }JPEG_SURFACE_S;

    typedef struct tagJPEG_IMG_INFO_S
    {
        HI_BOOL HuffTabNoSupport;
        HI_BOOL SampleFactorSupport;
        HI_BOOL progressive_mode;
        HI_BOOL arith_code;
        HI_CHAR* next_input_byte;
        HI_U8 u8Fac[HI_JPEG_MAX_COMPONENT_NUM][2];
        HI_U32 scale_num;
        HI_U32 scale_denom;
        HI_U32 data_precision;
        HI_U32 restart_interval;
        HI_U32 image_width;
        HI_U32 image_height;
        HI_U32 output_width;
        HI_U32 output_height;
        HI_U32 out_color_components;
        HI_U32 output_components;
        HI_U32 bytes_in_buffer;
        HI_U32 curpos_in_buffer;
        HI_S32 LuDcLen[6];
        HI_S32 QuantTab[HI_DCT_SIZE2];
        HI_U32 HuffDcTab[12];
        HI_U32 HufAcMinTab[HI_DCT_SIZE];
        HI_U32 HufAcBaseTab[HI_DCT_SIZE];
        HI_U32 HufAcSymbolTab[256];
        HI_JPEG_FMT_E jpeg_color_space;
        HI_JPEG_FMT_E output_color_space;
        /** parse by myself **/
        HI_BOOL bSofMark;
        HI_S32 ComInScan;
        HI_S32 Ss;
        HI_S32 Se;
        HI_S32 Ah;
        HI_S32 Al;
        HI_U32 num_components;
        COMPONENT_INFO_S stComponentInfo[HI_JPEG_MAX_COMPONENT_NUM];
        JPEG_HUFF_TBL    DcHuffTbl[MAX_NUM_HUFF_TBLS];
        JPEG_HUFF_TBL    AcHuffTbl[MAX_NUM_HUFF_TBLS];
        JPEG_QUANT_TBL   QuantTbl[MAX_NUM_QUANT_TBLS];
    }JPEG_IMG_INFO_S;

    typedef struct tagJPEG_HDEC_SOFINFO_S
    {
         HI_BOOL bCalcSize;
         HI_U32  u32YWidth;
         HI_U32  u32YHeight;
         HI_U32  u32YMcuHeight;
         HI_U32  u32YSize;
         HI_U32  u32CWidth;
         HI_U32  u32CHeight;
         HI_U32  u32CMcuHeight;
         HI_U32  u32CSize;
         HI_U32  u32YStride;
         HI_U32  u32CbCrStride;
         HI_U32  DecOutWidth;
         HI_U32  DecOutHeight;
         HI_U32  DecOutStride;
         HI_U32  u32InWandH;
         HI_U32  u32McuWidth;
         HI_U32  u32MINSize;
         HI_U32  u32MIN1Size;
         HI_U32  u32RGBSizeReg;
    }JPEG_HDEC_SOFINFO_S;

    /********************** Global Variable declaration *******************************************/
    typedef struct tagJPEG_SDEC_COLOR_CONVERT_S
    {
      HI_VOID (*JPEG_SDEC_YCC_ConVert)(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue);
      HI_VOID (*JPEG_SDEC_GRAY_ConVert)(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue);
      HI_VOID (*JPEG_SDEC_YCCK_ConVert)(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue);
      HI_VOID (*JPEG_SDEC_CMYK_ConVert)(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue, HI_U32 Alpha);
      HI_VOID (*JPEG_SDEC_RGB_ConVert)(HI_ULONG HdeHandle, HI_CHAR* OutBuf, HI_U32 Red, HI_U32 Green, HI_U32 Blue);
    }JPEG_SDEC_COLOR_CONVERT_S;

    /******************************* API declaration **********************************************/

    /**********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __JPEG_HDEC_HAL_H__*/
