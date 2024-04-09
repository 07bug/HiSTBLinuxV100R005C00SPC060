/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hal_parse.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : 自己解析
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
***************************************************************************************************/

#ifndef CONFIG_GFX_JPEG_MINI_SUPPROT

/****************************  add include here     ***********************************************/
#ifndef HI_BUILD_IN_BOOT
  #include "hi_math.h"
#else
  #include "hi_gfx_sys.h"
#endif

#include "jpeg_hdec_api.h"
/***************************** Macro Definition ***************************************************/

#define JPEG_TAG     0xFF

#define INPUT_BYTE(curpos0,datavir0,datavir1,datalen0,datalen1,code)  \
        if (curpos0 < datalen0)                       \
        {\
            if (NULL != datavir0)\
            {\
               code = *(HI_U8*)(datavir0 + curpos0);  \
            }\
            curpos0++;                                \
        }\
        else if (curpos0 < (datalen0 + datalen1))\
        {\
            if (NULL != datavir1)\
            {\
               code = *(HI_U8*)(datavir1 + (curpos0 - datalen0));\
            }\
            curpos0++;\
        }\
        else\
        {\
        }

#define INPUT_2BYTE(curpos0,datavir0,datavir1,datalen0,datalen1,code)  \
        if((curpos0 + 1) < datalen0)\
        {\
            if (NULL != datavir0)\
            {\
              code = ((*(HI_U8*)(datavir0 + curpos0)) << 8) + (*(HI_U8*)(datavir0 + curpos0 + 1)); \
            }\
            curpos0 += 2;\
        }\
        else if(((curpos0 + 1) == datalen0) && (0 != datalen1)) \
        {\
            if ((NULL != datavir0) && (NULL != datavir1))\
            {\
              code = ((*(HI_U8*)(datavir0 + curpos0)) << 8) + (*(HI_U8*)datavir1); \
            }\
            curpos0 += 2;  \
        }\
        else if((curpos0 + 1) < (datalen0 + datalen1))\
        {\
            if (NULL != datavir1)\
            {\
              code = ((*(HI_U8*)(datavir1 + (curpos0 - datalen0))) << 8) + (*(HI_U8*)(datavir1 + (curpos0 - datalen0) + 1)); \
            }\
            curpos0 += 2;\
        }\
        else\
        {\
        }

#define INPUT_BYTE_DATA(imginfo,code,byte)\
        {\
            if(1 == byte)\
            {\
                INPUT_BYTE(imginfo->UserInputCurPos,\
                           imginfo->pUserFirstInputDataVirBuf, imginfo->pUserSecondInputDataVirBuf,   \
                           imginfo->UserFirstInputBufSize,imginfo->UserSecondInputBufSize,code);      \
            }\
            else\
            {\
                INPUT_2BYTE(imginfo->UserInputCurPos,\
                            imginfo->pUserFirstInputDataVirBuf, imginfo->pUserSecondInputDataVirBuf, \
                            imginfo->UserFirstInputBufSize, imginfo->UserSecondInputBufSize,code);   \
            }\
        }

#define SOS_SUPPORT(DataMark) \
           if (   (M_JPEG_SOF2 == DataMark) || (M_JPEG_SOF9 == DataMark) || (M_JPEG_SOF10 == DataMark) || (M_JPEG_SOF3 == DataMark) \
               || (M_JPEG_SOF5 == DataMark) || (M_JPEG_SOF6 == DataMark) || (M_JPEG_SOF7 == DataMark) || (M_JPEG_JPG == DataMark)   \
               || (M_JPEG_SOF11 == DataMark) || (M_JPEG_SOF13 == DataMark) || (M_JPEG_SOF14 == DataMark) || (M_JPEG_SOF15 == DataMark))\
           {\
               return HI_FAILURE;\
           }

#define RST_SUPPORT(DataMark) \
                      if (   (M_JPEG_RST0 == DataMark) || (M_JPEG_RST1 == DataMark) || (M_JPEG_RST2 == DataMark) || (M_JPEG_RST3 == DataMark) \
                          || (M_JPEG_RST4 == DataMark) || (M_JPEG_RST5 == DataMark) || (M_JPEG_RST6 == DataMark) || (M_JPEG_RST7 == DataMark))\
                      {\
                          return HI_FAILURE;\
                      }

#define DAX_SUPPORT(DataMark) \
                      if (   (M_JPEG_DAC == DataMark) || (M_JPEG_TEM == DataMark) || (M_JPEG_DNL == DataMark))\
                      {\
                          return HI_FAILURE;\
                      }

/*************************** Structure Definition *************************************************/
typedef enum tagJPEGMARKE{
  M_JPEG_SOF0  = 0xc0,
  M_JPEG_SOF1  = 0xc1,
  M_JPEG_SOF2  = 0xc2,    /** progressive                          **/
  M_JPEG_SOF3  = 0xc3,    /** Lossless, Huffman                    **/

  M_JPEG_SOF5  = 0xc5,    /** Differential sequential, Huffman     **/
  M_JPEG_SOF6  = 0xc6,    /** Differential progressive, Huffman    **/
  M_JPEG_SOF7  = 0xc7,    /** Differential lossless, Huffman       **/

  M_JPEG_JPG   = 0xc8,    /** Reserved for JPEG extensions         **/
  M_JPEG_SOF9  = 0xc9,    /** arithmetic                           **/
  M_JPEG_SOF10 = 0xca,    /** Progressive, arithmetic              **/
  M_JPEG_SOF11 = 0xcb,    /** Lossless, arithmetic                 **/

  M_JPEG_SOF13 = 0xcd,    /** Differential sequential, arithmetic  **/
  M_JPEG_SOF14 = 0xce,    /** Differential progressive, arithmetic **/
  M_JPEG_SOF15 = 0xcf,    /** Differential lossless, arithmetic    **/

  M_JPEG_DHT   = 0xc4,

  M_JPEG_DAC   = 0xcc,

  M_JPEG_RST0  = 0xd0,
  M_JPEG_RST1  = 0xd1,
  M_JPEG_RST2  = 0xd2,
  M_JPEG_RST3  = 0xd3,
  M_JPEG_RST4  = 0xd4,
  M_JPEG_RST5  = 0xd5,
  M_JPEG_RST6  = 0xd6,
  M_JPEG_RST7  = 0xd7,

  M_JPEG_SOI   = 0xd8,
  M_JPEG_EOI   = 0xd9,
  M_JPEG_SOS   = 0xda,
  M_JPEG_DQT   = 0xdb,
  M_JPEG_DNL   = 0xdc,
  M_JPEG_DRI   = 0xdd,
  M_JPEG_DHP   = 0xde,
  M_JPEG_EXP   = 0xdf,

  M_JPEG_APP0  = 0xe0,
  M_JPEG_APP1  = 0xe1,
  M_JPEG_APP2  = 0xe2,
  M_JPEG_APP3  = 0xe3,
  M_JPEG_APP4  = 0xe4,
  M_JPEG_APP5  = 0xe5,
  M_JPEG_APP6  = 0xe6,
  M_JPEG_APP7  = 0xe7,
  M_JPEG_APP8  = 0xe8,
  M_JPEG_APP9  = 0xe9,
  M_JPEG_APP10 = 0xea,
  M_JPEG_APP11 = 0xeb,
  M_JPEG_APP12 = 0xec,
  M_JPEG_APP13 = 0xed,
  M_JPEG_APP14 = 0xee,
  M_JPEG_APP15 = 0xef,

  M_JPEG_JPG0  = 0xf0,
  M_JPEG_JPG13 = 0xfd,
  M_JPEG_COM   = 0xfe,

  M_JPEG_TEM   = 0x01,

  M_JPEG_ERROR = 0x100
} JPEG_MARK_E;



typedef enum tagJPEG_PARSE_E
{
   JPEG_PARSE_NOT_JPEG   = 0,
   JPEG_PARSE_SOFN,
   JPEG_PARSE_SOS,
   JPEG_PARSE_DQT,
   JPEG_PARSE_DHT,
   JPEG_PARSE_DRI,
   JPEG_PARSE_CONTINUE,
   JPEG_PARSE_ERROR,
   JPEG_PARSE_FINISH,
   JPEG_PARSE_BUTT
}JPEG_PARSE_E;

/********************** Global Variable declaration ***********************************************/

/******************************* API forward declarations *****************************************/
static inline HI_S32  DRV_JPEG_ParseMarkInfo(HI_S32 DataMark,JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_BOOL DRV_JPEG_CheckIsSupportSofInfo(JPEG_IMG_INFO_S *pstImgInfo);
static inline HI_BOOL DRV_JPEG_CheckIsSupportFactor(JPEG_IMG_INFO_S *pstImgInfo);
static inline HI_S32  DRV_JPEG_CheckWhetherSupportSofMark(HI_S32 DataMark);
static inline HI_S32  DRV_JPEG_CheckWhetherSupportAPPMark(HI_S32 DataMark,INPUT_STREAM_BUF_S *pstImgInfo);
static inline HI_S32  DRV_JPEG_CheckWhetherSupportRstMark(HI_S32 DataMark);
static inline HI_S32  DRV_JPEG_CheckWhetherSupportOthersMark(HI_S32 DataMark);

/******************************* API realization **************************************************/
static HI_BOOL parse_fist_marker(INPUT_STREAM_BUF_S *pstInputStreamBuf)
{
    HI_S32 s32Code  = 0;
    HI_S32 s32Code1 = 0;

    INPUT_BYTE_DATA(pstInputStreamBuf,s32Code,1);
    INPUT_BYTE_DATA(pstInputStreamBuf,s32Code1,1);

    if (JPEG_TAG == s32Code && M_JPEG_SOI == s32Code1)
    {
        return HI_TRUE;
    }

    return HI_FALSE;
}

static HI_S32 parse_next_marker(INPUT_STREAM_BUF_S *pstInputStreamBuf, HI_S32 *ps32Mark)
{
    HI_S32 s32Code = 0;

    while (pstInputStreamBuf->UserInputCurPos <= pstInputStreamBuf->UserFirstInputBufSize)
    {
        INPUT_BYTE_DATA(pstInputStreamBuf,s32Code,1);
        while ((s32Code != 0xFF) && (pstInputStreamBuf->UserInputCurPos <= pstInputStreamBuf->UserFirstInputBufSize))
        {
           INPUT_BYTE_DATA(pstInputStreamBuf,s32Code,1);
        }

        do
        {
          INPUT_BYTE_DATA(pstInputStreamBuf,s32Code,1);
        } while ((s32Code == 0xFF) && (pstInputStreamBuf->UserInputCurPos <= pstInputStreamBuf->UserFirstInputBufSize));

        if (s32Code != 0)
        {
           break;
        }
    }

    if (pstInputStreamBuf->UserInputCurPos == pstInputStreamBuf->UserFirstInputBufSize)
    {/**<--  已经解析到头了 >**/
        return HI_FAILURE;
    }

    *ps32Mark = s32Code;

    return HI_SUCCESS;
}

static HI_BOOL parse_dri_marker(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_S32 s32Len  = 0;
    HI_S32 s32Code = 0;
    INPUT_STREAM_BUF_S *pstInputStreamBuf = &(pJpegHandle->stInputDataBufInfo.stInputStreamBuf);

    INPUT_BYTE_DATA(pstInputStreamBuf,s32Len,2);

    if (s32Len != 4)
    {
      JPEG_TRACE("the dri len is bad\n");
      return HI_FALSE;
    }

    INPUT_BYTE_DATA(pstInputStreamBuf,s32Code,2);

    pJpegHandle->stImgInfo.restart_interval = s32Code;

    return HI_TRUE;
}


static HI_BOOL parse_appn_marker(INPUT_STREAM_BUF_S *pstInputStreamBuf)
{
    HI_S32 s32Len = 0;

    INPUT_BYTE_DATA(pstInputStreamBuf,s32Len,2);
    s32Len -= 2;

    if ( (pstInputStreamBuf->UserInputCurPos + s32Len) < pstInputStreamBuf->UserFirstInputBufSize)
    {
        pstInputStreamBuf->UserInputCurPos = pstInputStreamBuf->UserInputCurPos + s32Len;
    }

    return HI_TRUE;
}

static HI_BOOL parse_com_marker(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_S32 s32Len = 0;
    INPUT_STREAM_BUF_S *pstInputStreamBuf = &(pJpegHandle->stInputDataBufInfo.stInputStreamBuf);

    INPUT_BYTE_DATA(pstInputStreamBuf,s32Len,2);
    s32Len -= 2;

    if ( (pstInputStreamBuf->UserInputCurPos + s32Len) < pstInputStreamBuf->UserFirstInputBufSize)
    {
        pstInputStreamBuf->UserInputCurPos = pstInputStreamBuf->UserInputCurPos + s32Len;
    }

    return HI_TRUE;
}


static HI_BOOL parse_sofn_marker(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_U32 Len = 0;
    HI_S32 s32DataPrecision   = 0;
    HI_S32 s32Code = 0;
    HI_U32 Cnt  = 0;
    HI_BOOL bSofSupport = HI_FALSE;
    INPUT_STREAM_BUF_S *pstInputStreamBuf = &(pJpegHandle->stInputDataBufInfo.stInputStreamBuf);

    INPUT_BYTE_DATA(pstInputStreamBuf,Len,2);

    INPUT_BYTE_DATA(pstInputStreamBuf,s32DataPrecision,1);

    if (8 != s32DataPrecision)
    {/**< 精度硬件不支持 >**/
        JPEG_TRACE("the data precison is %d,hard dec not support\n",s32DataPrecision);
        return HI_FALSE;
    }

    INPUT_BYTE_DATA(pstInputStreamBuf,pJpegHandle->stImgInfo.image_height, 2);
    INPUT_BYTE_DATA(pstInputStreamBuf,pJpegHandle->stImgInfo.image_width,  2);
    INPUT_BYTE_DATA(pstInputStreamBuf,pJpegHandle->stImgInfo.num_components,1);

    Len -= 8;
    if (Len != pJpegHandle->stImgInfo.num_components * 3)
    {
       JPEG_TRACE("the s32Len is larger\n");
       return HI_FALSE;
    }

    bSofSupport = DRV_JPEG_CheckIsSupportSofInfo(&(pJpegHandle->stImgInfo));
    if (HI_FALSE == bSofSupport)
    {
       return HI_FALSE;
    }

    for (Cnt = 0; Cnt < pJpegHandle->stImgInfo.num_components; Cnt++)
    {
        pJpegHandle->stImgInfo.stComponentInfo[Cnt].ComponentIndex = Cnt;

        INPUT_BYTE_DATA(pstInputStreamBuf,pJpegHandle->stImgInfo.stComponentInfo[Cnt].ComponentId,1);
        INPUT_BYTE_DATA(pstInputStreamBuf,s32Code,1);
        pJpegHandle->stImgInfo.stComponentInfo[Cnt].u8HorSampleFac = (s32Code >> 4) & 15;
        pJpegHandle->stImgInfo.stComponentInfo[Cnt].u8VerSampleFac = (s32Code     ) & 15;
        INPUT_BYTE_DATA(pstInputStreamBuf,pJpegHandle->stImgInfo.stComponentInfo[Cnt].QuantTblNo,1);
    }

    if (1 == pJpegHandle->stImgInfo.num_components)
    {
       if (pJpegHandle->stImgInfo.stComponentInfo[0].u8HorSampleFac == pJpegHandle->stImgInfo.stComponentInfo[0].u8VerSampleFac)
       {
             pJpegHandle->stImgInfo.jpeg_color_space = HI_JPEG_FMT_YUV400;
             pJpegHandle->stImgInfo.u8Fac[0][0] = 1;
             pJpegHandle->stImgInfo.u8Fac[0][1] = 1;
             pJpegHandle->stImgInfo.u8Fac[1][0] = 0;
             pJpegHandle->stImgInfo.u8Fac[1][1] = 0;
             pJpegHandle->stImgInfo.u8Fac[2][0] = 0;
             pJpegHandle->stImgInfo.u8Fac[2][1] = 0;
       }
    }
    else if (   (3 == pJpegHandle->stImgInfo.num_components)  \
             && (pJpegHandle->stImgInfo.stComponentInfo[1].u8HorSampleFac == pJpegHandle->stImgInfo.stComponentInfo[2].u8HorSampleFac) \
             && (pJpegHandle->stImgInfo.stComponentInfo[1].u8VerSampleFac == pJpegHandle->stImgInfo.stComponentInfo[2].u8VerSampleFac))
    {
        if (pJpegHandle->stImgInfo.stComponentInfo[0].u8HorSampleFac == ((pJpegHandle->stImgInfo.stComponentInfo[1].u8HorSampleFac)<<1))
        {
             if (pJpegHandle->stImgInfo.stComponentInfo[0].u8VerSampleFac == ((pJpegHandle->stImgInfo.stComponentInfo[1].u8VerSampleFac)<<1))
             {
                 pJpegHandle->stImgInfo.jpeg_color_space = HI_JPEG_FMT_YUV420;
             }
             else if (pJpegHandle->stImgInfo.stComponentInfo[0].u8VerSampleFac == pJpegHandle->stImgInfo.stComponentInfo[1].u8VerSampleFac)
             {
                 pJpegHandle->stImgInfo.jpeg_color_space = HI_JPEG_FMT_YUV422_21;
             }

         }
         else if (pJpegHandle->stImgInfo.stComponentInfo[0].u8HorSampleFac == pJpegHandle->stImgInfo.stComponentInfo[1].u8HorSampleFac)
         {
               if (pJpegHandle->stImgInfo.stComponentInfo[0].u8VerSampleFac == ((pJpegHandle->stImgInfo.stComponentInfo[1].u8VerSampleFac)<<1))
               {
                    pJpegHandle->stImgInfo.jpeg_color_space = HI_JPEG_FMT_YUV422_12;
               }
               else if (pJpegHandle->stImgInfo.stComponentInfo[0].u8VerSampleFac == pJpegHandle->stImgInfo.stComponentInfo[1].u8VerSampleFac)
               {
                    pJpegHandle->stImgInfo.jpeg_color_space = HI_JPEG_FMT_YUV444;
               }
          }
          pJpegHandle->stImgInfo.u8Fac[0][0] = pJpegHandle->stImgInfo.stComponentInfo[0].u8HorSampleFac;
          pJpegHandle->stImgInfo.u8Fac[0][1] = pJpegHandle->stImgInfo.stComponentInfo[0].u8VerSampleFac;
          pJpegHandle->stImgInfo.u8Fac[1][0] = pJpegHandle->stImgInfo.stComponentInfo[1].u8HorSampleFac;
          pJpegHandle->stImgInfo.u8Fac[1][1] = pJpegHandle->stImgInfo.stComponentInfo[1].u8VerSampleFac;
          pJpegHandle->stImgInfo.u8Fac[2][0] = pJpegHandle->stImgInfo.stComponentInfo[2].u8HorSampleFac;
          pJpegHandle->stImgInfo.u8Fac[2][1] = pJpegHandle->stImgInfo.stComponentInfo[2].u8VerSampleFac;
    }
    else
    {
       pJpegHandle->stImgInfo.jpeg_color_space = HI_JPEG_FMT_BUTT;
       return HI_FALSE;
    }

    return HI_TRUE;

}

static inline HI_BOOL DRV_JPEG_CheckIsSupportSofInfo(JPEG_IMG_INFO_S *pstImgInfo)
{
    if (pstImgInfo->num_components > HI_JPEG_MAX_COMPONENT_NUM)
    {
        JPEG_TRACE("the s32NumComponent is larger,not support\n");
        return HI_FALSE;
    }

    if ((pstImgInfo->image_width > 8095) || (pstImgInfo->image_height > 8095))
    {
        JPEG_TRACE("the image w and h is to large\n");
        return HI_FALSE;
    }

    return HI_TRUE;
}

static HI_BOOL parse_sos_marker(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_S32 s32Len = 0;
    HI_S32 s32NumComponent = 0;
    HI_S32 s32Cnt   = 0;
    HI_U32 Cnt1  = 0;
    HI_S32 s32Code  = 0;
    HI_S32 s32Code1 = 0;
    HI_BOOL bFacSupport = HI_FALSE;
    INPUT_STREAM_BUF_S *pstInputStreamBuf = &(pJpegHandle->stInputDataBufInfo.stInputStreamBuf);

    if (HI_FALSE == pJpegHandle->stImgInfo.bSofMark)
    {
        JPEG_TRACE("not has sof befor sos\n");
        return HI_FALSE;
    }

    INPUT_BYTE_DATA(pstInputStreamBuf,s32Len,2);

    INPUT_BYTE_DATA(pstInputStreamBuf,s32NumComponent,1);

    if (s32Len != (s32NumComponent * 2 + 6) || s32NumComponent < 1 || s32NumComponent > HI_MAX_COMPS_IN_SCAN)
    {
        JPEG_TRACE("the len is larger\n");
        return HI_FALSE;
    }

    /** 扫描行内组件数 **/
    pJpegHandle->stImgInfo.ComInScan = s32NumComponent;
    if (s32NumComponent > HI_JPEG_MAX_COMPONENT_NUM)
    {
        JPEG_TRACE("the component num is larger\n");
        return HI_FALSE;
    }

    if (pJpegHandle->stImgInfo.num_components > HI_JPEG_MAX_COMPONENT_NUM)
    {
        JPEG_TRACE("the component num is larger\n");
        return HI_FALSE;
    }

    for (s32Cnt = 0; s32Cnt < s32NumComponent; s32Cnt++)
    {
        INPUT_BYTE_DATA(pstInputStreamBuf,s32Code1,1);
        INPUT_BYTE_DATA(pstInputStreamBuf,s32Code,1);

        for (Cnt1 = 0; Cnt1 < pJpegHandle->stImgInfo.num_components; Cnt1++)
        {
          if (s32Code1 == pJpegHandle->stImgInfo.stComponentInfo[Cnt1].ComponentId)
                goto id_found;
        }
        JPEG_TRACE("can not find component id\n");
        return HI_FALSE;

        id_found:
            pJpegHandle->stImgInfo.stComponentInfo[Cnt1].DcTblNo = (s32Code >> 4) & 15;
            pJpegHandle->stImgInfo.stComponentInfo[Cnt1].AcTblNo = (s32Code     ) & 15;

    }
    INPUT_BYTE_DATA(pstInputStreamBuf,pJpegHandle->stImgInfo.Ss,1);
    INPUT_BYTE_DATA(pstInputStreamBuf,pJpegHandle->stImgInfo.Se,1);
    INPUT_BYTE_DATA(pstInputStreamBuf,s32Code,1);

    pJpegHandle->stImgInfo.Ah = (s32Code >> 4) & 15;
    pJpegHandle->stImgInfo.Al = (s32Code     ) & 15;

    bFacSupport = DRV_JPEG_CheckIsSupportFactor(&(pJpegHandle->stImgInfo));

    return bFacSupport;
}

static inline HI_BOOL DRV_JPEG_CheckIsSupportFactor(JPEG_IMG_INFO_S *pstImgInfo)
{
#ifndef CONFIG_JPEG_SET_SAMPLEFACTOR
     HI_S32 ci = 0;
     HI_BOOL bY22 = HI_FALSE;
     HI_BOOL bU12 = HI_FALSE;
     HI_BOOL bV12 = HI_FALSE;

     if (pstImgInfo->ComInScan > HI_JPEG_MAX_COMPONENT_NUM)
     {
        return HI_FALSE;
     }

     for (ci = 0; ci < pstImgInfo->ComInScan; ci++)
     {
         if ( (0 == ci) && (2 == pstImgInfo->u8Fac[ci][0]) && (2 == pstImgInfo->u8Fac[ci][1]))
             bY22 = HI_TRUE;
         if ( (1 == ci) && (1 == pstImgInfo->u8Fac[ci][0]) && (2 == pstImgInfo->u8Fac[ci][1]))
             bU12 = HI_TRUE;
         if ( (2 == ci) && (1 == pstImgInfo->u8Fac[ci][0]) && (2 == pstImgInfo->u8Fac[ci][1]))
             bV12 = HI_TRUE;
     }
     if ( (HI_TRUE == bY22) && (HI_TRUE == bU12) && (HI_TRUE == bV12))
     {
         return HI_FALSE;
     }
     if ( (HI_JPEG_FMT_YUV444 == pstImgInfo->jpeg_color_space) && (HI_TRUE == bU12) && (HI_TRUE == bV12))
     {
         return HI_FALSE;
     }
#else
     HI_UNUSED(pstImgInfo);
#endif
     return HI_TRUE;
}


static HI_BOOL parse_dht_marker(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_S32 s32Len      = 0;
    HI_S32 s32HTIndex  = 0;
    HI_U8 bits[17]     = {0};
    HI_U8 huffval[256] = {0};
    HI_S32 s32Count    = 0;
    HI_S32 s32Cnt      = 0;
    JPEG_HUFF_TBL *htblptr = NULL;
    INPUT_STREAM_BUF_S *pstInputStreamBuf = &(pJpegHandle->stInputDataBufInfo.stInputStreamBuf);

    INPUT_BYTE_DATA(pstInputStreamBuf,s32Len,2);

    s32Len -= 2;

    while (s32Len > 16)
    {
        INPUT_BYTE_DATA(pstInputStreamBuf,s32HTIndex,1);
        bits[0]  = 0;
        s32Count = 0;
        for(s32Cnt = 1; s32Cnt <= 16; s32Cnt++)
        {
          INPUT_BYTE_DATA(pstInputStreamBuf,bits[s32Cnt],1);
          s32Count += bits[s32Cnt];
        }
        s32Len -= 1 + 16;

        #if 0
        JPEG_TRACE("bits1->bits8[%d %d %d %d %d %d %d %d]\n",
             bits[1], bits[2], bits[3], bits[4],
             bits[5], bits[6], bits[7], bits[8]);
        JPEG_TRACE("bits9->bits16[%d %d %d %d %d %d %d %d]\n",
             bits[9], bits[10], bits[11], bits[12],
             bits[13], bits[14], bits[15], bits[16]);
        #endif

        if (s32Count > 256 || s32Count > s32Len)
        {
           JPEG_TRACE("the dht is bad\n");
           return HI_FALSE;
        }

        for (s32Cnt = 0; s32Cnt < s32Count; s32Cnt++)
        {
            INPUT_BYTE_DATA(pstInputStreamBuf,huffval[s32Cnt],1);
        }

        s32Len -= s32Count;

        if (s32HTIndex & 0x10)
        {/** AC table definition **/
              s32HTIndex -= 0x10;
              if(s32HTIndex < 0 || s32HTIndex >= MAX_NUM_HUFF_TBLS)
                {/** deal codecc warning **/
                  JPEG_TRACE("the dht index is error\n");
                  return HI_FALSE;
                }
              htblptr = &pJpegHandle->stImgInfo.AcHuffTbl[s32HTIndex];
              pJpegHandle->stImgInfo.AcHuffTbl[s32HTIndex].bHasHuffTbl = HI_TRUE;
        }
        else
        {/** DC table definition **/
              if(s32HTIndex < 0 || s32HTIndex >= MAX_NUM_HUFF_TBLS)
                {/** deal codecc warning **/
                  JPEG_TRACE("the dht index is error\n");
                  return HI_FALSE;
                }
              htblptr = &pJpegHandle->stImgInfo.DcHuffTbl[s32HTIndex];
              pJpegHandle->stImgInfo.DcHuffTbl[s32HTIndex].bHasHuffTbl = HI_TRUE;
              if(0 == s32HTIndex)
              {
                pJpegHandle->stImgInfo.LuDcLen[0] = bits[11];
                pJpegHandle->stImgInfo.LuDcLen[1] = bits[12];
                pJpegHandle->stImgInfo.LuDcLen[2] = bits[13];
                pJpegHandle->stImgInfo.LuDcLen[3] = bits[14];
                pJpegHandle->stImgInfo.LuDcLen[4] = bits[15];
                pJpegHandle->stImgInfo.LuDcLen[5] = bits[16];
              }
        }
        HI_GFX_Memcpy(htblptr->bits, bits, sizeof(htblptr->bits));
        HI_GFX_Memcpy(htblptr->huffval, huffval, sizeof(htblptr->huffval));
    }

    if (s32Len != 0)
    {
       JPEG_TRACE("the dht len is error\n");
       return HI_FALSE;
    }

#ifndef CONFIG_JPEG_DRI_SUPPORT
    if (   0 != pJpegHandle->stImgInfo.LuDcLen[0] || 0 != pJpegHandle->stImgInfo.LuDcLen[1] \
        || 0 != pJpegHandle->stImgInfo.LuDcLen[2] || 0 != pJpegHandle->stImgInfo.LuDcLen[3] \
        || 0 != pJpegHandle->stImgInfo.LuDcLen[4] || 0 != pJpegHandle->stImgInfo.LuDcLen[5])
    {
      JPEG_TRACE("the dri is not support\n");
      return HI_FALSE;
    }
#endif

    return HI_TRUE;
}

static HI_BOOL parse_dqt_marker(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_S32 s32Len  = 0;
    HI_S32 s32Code = 0;
    HI_S32 s32Cnt  = 0;
    HI_U32 tmp     = 0;
    HI_S32 s32Precision = 0;
    JPEG_QUANT_TBL *quantptr = NULL;
    INPUT_STREAM_BUF_S *pstInputStreamBuf = &(pJpegHandle->stInputDataBufInfo.stInputStreamBuf);

    HI_S32 s32Zorder[HI_DCT_SIZE2 + 16] = {
                              0,  1,  8, 16,  9,  2,  3, 10,
                             17, 24, 32, 25, 18, 11,  4,  5,
                             12, 19, 26, 33, 40, 48, 41, 34,
                             27, 20, 13,  6,  7, 14, 21, 28,
                             35, 42, 49, 56, 57, 50, 43, 36,
                             29, 22, 15, 23, 30, 37, 44, 51,
                             58, 59, 52, 45, 38, 31, 39, 46,
                             53, 60, 61, 54, 47, 55, 62, 63,
                             63, 63, 63, 63, 63, 63, 63, 63,
                             63, 63, 63, 63, 63, 63, 63, 63
                          };

    INPUT_BYTE_DATA(pstInputStreamBuf,s32Len,2);

    s32Len -= 2;

    while (s32Len > 0)
    {
        INPUT_BYTE_DATA(pstInputStreamBuf,s32Code,1);

        s32Precision = s32Code >> 4;
        s32Code &= 0x0F;
        if (s32Code >= MAX_NUM_QUANT_TBLS)
        {
            JPEG_TRACE("the qt table is to larger\n");
            return HI_FALSE;
        }
        pJpegHandle->stImgInfo.QuantTbl[s32Code].bHasQuantTbl = HI_TRUE;

        quantptr = &pJpegHandle->stImgInfo.QuantTbl[s32Code];

        for (s32Cnt = 0; s32Cnt < HI_DCT_SIZE2; s32Cnt++)
        {
              if (s32Precision)
              {
                  INPUT_BYTE_DATA(pstInputStreamBuf,tmp,2);
              }
              else
              {
                  INPUT_BYTE_DATA(pstInputStreamBuf,tmp,1);
              }
              /** We convert the zigzag-order table to natural array order. **/
              quantptr->quantval[s32Zorder[s32Cnt]] = (HI_U16)tmp;
        }

        #if 0
            for (s32Cnt = 0; s32Cnt < HI_DCT_SIZE2; s32Cnt += 8)
            {
                 JPEG_TRACE("quantable[%d %d %d %d %d %d %d %d]\n",
                 quantptr->quantval[s32Cnt],   quantptr->quantval[s32Cnt+1],
                 quantptr->quantval[s32Cnt+2], quantptr->quantval[s32Cnt+3],
                 quantptr->quantval[s32Cnt+4], quantptr->quantval[s32Cnt+5],
                 quantptr->quantval[s32Cnt+6], quantptr->quantval[s32Cnt+7]);
            }
            JPEG_TRACE("QuanTbl[%d].bHasQuantTbl = %d\n",s32Code,pJpegHandle->stImgInfo.QuantTbl[s32Code].bHasQuantTbl);
        #endif

        s32Len -= HI_DCT_SIZE2 + 1;
        if (s32Precision)
        {
            s32Len -= HI_DCT_SIZE2;
        }

    }

    if (s32Len != 0)
    {
       JPEG_TRACE("the dqt len is error\n");
       return HI_FALSE;
    }

    return HI_TRUE;
}

static HI_S32 JPEG_HAL_Parse(HI_ULONG DecHandle)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_S32 s32Mark = 0;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
        return HI_FAILURE;
    }

    if (NULL == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.pUserFirstInputDataVirBuf)
    {
        return HI_FAILURE;
    }

    if (0 == pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize)
    {
        return HI_FAILURE;
    }

    if (! parse_fist_marker(&(pJpegHandle->stInputDataBufInfo.stInputStreamBuf)))
    {
        JPEG_TRACE("is not a jpeg\n");
        return HI_FAILURE;
    }

    while (pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserInputCurPos <= pJpegHandle->stInputDataBufInfo.stInputStreamBuf.UserFirstInputBufSize)
    {
        if (HI_SUCCESS != parse_next_marker(&(pJpegHandle->stInputDataBufInfo.stInputStreamBuf),&s32Mark))
        {
           return HI_FAILURE;
        }

        Ret = DRV_JPEG_ParseMarkInfo(s32Mark,pJpegHandle);
        if (JPEG_PARSE_FINISH == Ret)
        {
           return HI_SUCCESS;
        }

        if (JPEG_PARSE_ERROR == Ret)
        {
           return HI_FAILURE;
        }
    }

    return HI_FAILURE;
}

static inline HI_S32 DRV_JPEG_ParseMarkInfo(HI_S32 DataMark,JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    HI_S32 Ret = HI_SUCCESS;

    Ret = DRV_JPEG_CheckWhetherSupportSofMark(DataMark);
    if (HI_SUCCESS != Ret)
    {
        JPEG_TRACE("is not sof mark\n");
        return JPEG_PARSE_ERROR;
    }

    Ret = DRV_JPEG_CheckWhetherSupportAPPMark(DataMark,&(pJpegHandle->stInputDataBufInfo.stInputStreamBuf));
    if (HI_SUCCESS != Ret)
    {
        JPEG_TRACE("is not app mark\n");
        return JPEG_PARSE_ERROR;
    }

    Ret = DRV_JPEG_CheckWhetherSupportRstMark(DataMark);
    if (HI_SUCCESS != Ret)
    {
        JPEG_TRACE("is not sof rst\n");
        return JPEG_PARSE_ERROR;
    }

    Ret = DRV_JPEG_CheckWhetherSupportOthersMark(DataMark);
    if (HI_SUCCESS != Ret)
    {
        JPEG_TRACE("is not others mark\n");
        return JPEG_PARSE_ERROR;
    }

    switch (DataMark)
    {
        case M_JPEG_SOI: /**<-- start data 0xffd8 >**/
              break;
        /**<-- baseline --- huffman >**/
        case M_JPEG_SOF0:
        case M_JPEG_SOF1:
              if(! parse_sofn_marker(pJpegHandle))
              {
                 JPEG_TRACE("parse sof failure\n");
                 return JPEG_PARSE_ERROR;
              }
              pJpegHandle->stImgInfo.bSofMark  = HI_TRUE;
              break;
        case M_JPEG_SOS:
              if(! parse_sos_marker(pJpegHandle))
              {
                 JPEG_TRACE("parse sos failure\n");
                 return JPEG_PARSE_ERROR;
              }
              /**<-- ok,parse the dec stream,should not continue parse file >**/
              return JPEG_PARSE_FINISH;

        case M_JPEG_DHT:
              if(! parse_dht_marker(pJpegHandle))
              {
                 JPEG_TRACE("parse dht failure\n");
                 return JPEG_PARSE_ERROR;
              }
              break;

        case M_JPEG_DQT:
              if(! parse_dqt_marker(pJpegHandle))
              {
                 JPEG_TRACE("parse dqt failure\n");
                 return JPEG_PARSE_ERROR;
              }
              break;
        case M_JPEG_DRI:
              if(! parse_dri_marker(pJpegHandle))
              {
                 JPEG_TRACE("parse dri failure\n");
                 return JPEG_PARSE_ERROR;
              }
              break;
        case M_JPEG_COM:
              if(! parse_com_marker(pJpegHandle))
              {
                 JPEG_TRACE("parse com failure\n");
                 return JPEG_PARSE_ERROR;
              }
              break;
        case M_JPEG_EOI:
              JPEG_TRACE("is end jpeg\n");
              return JPEG_PARSE_ERROR;
        default:
              return JPEG_PARSE_CONTINUE;
     }

     return JPEG_PARSE_CONTINUE;
}


static inline HI_S32 DRV_JPEG_CheckWhetherSupportSofMark(HI_S32 DataMark)
{
     SOS_SUPPORT(DataMark);
     return HI_SUCCESS;
}

static inline HI_S32 DRV_JPEG_CheckWhetherSupportAPPMark(HI_S32 DataMark,INPUT_STREAM_BUF_S *pstInputStreamBuf)
{
     switch(DataMark)
     {
        case M_JPEG_APP0:
        case M_JPEG_APP1:
        case M_JPEG_APP2:
        case M_JPEG_APP3:
        case M_JPEG_APP4:
        case M_JPEG_APP5:
        case M_JPEG_APP6:
        case M_JPEG_APP7:
        case M_JPEG_APP8:
        case M_JPEG_APP9:
        case M_JPEG_APP10:
        case M_JPEG_APP11:
        case M_JPEG_APP12:
        case M_JPEG_APP13:
        case M_JPEG_APP14:
        case M_JPEG_APP15:
            if(! parse_appn_marker(pstInputStreamBuf))
            {
               return HI_FAILURE;
            }
            break;
        default:
             break;
     }
     return HI_SUCCESS;
}


static inline HI_S32 DRV_JPEG_CheckWhetherSupportRstMark(HI_S32 DataMark)
{
     RST_SUPPORT(DataMark);
     return HI_SUCCESS;
}


static inline HI_S32 DRV_JPEG_CheckWhetherSupportOthersMark(HI_S32 DataMark)
{
     DAX_SUPPORT(DataMark);
     return HI_SUCCESS;
}
#endif
