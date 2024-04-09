/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name        : jpeg_hdec_debug.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :


History          :
Date                        Author                     Modification
2018/01/01                   sdk                       Created file
***************************************************************************************************/

#ifdef CONFIG_GFX_PROC_SUPPORT

/*********************************add include here*************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
#include <cutils/log.h>
#include <cutils/properties.h>
#endif

#include "jpeg_hdec_hal.h"
#include "jpeg_hdec_api.h"

#include "hi_gfx_comm.h"

/**************************************************************************************************/


/***************************** Macro Definition ***************************************************/
#define JPEG_PATH_MAX_LEN                 256

#define DADA_WRITE( file,fmt, args... )\
     do { \
          fprintf(file,fmt, ##args );\
     } while (0)


#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
    #define SAVE_JPEG_FILE_DIR              "/mnt/sdcard/Pictures"
    #define SAVE_MJPEG_FILE_DIR             "/mnt/sdcard/Pictures"
    #define SAVE_YUVSP_FILE_DIR             "/mnt/sdcard/Pictures"
#else
    #define SAVE_JPEG_FILE_DIR              "/tmp"
    #define SAVE_MJPEG_FILE_DIR             "/tmp"
    #define SAVE_YUVSP_FILE_DIR             "/tmp"
#endif


#ifdef LOG_TAG
#undef LOG_TAG
#endif

#define LOG_TAG "libjpeg"
/*************************** Structure Definition *************************************************/


/********************** Global Variable declaration ***********************************************/


/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/


/******************************* API realization **************************************************/
HI_VOID JPEG_DEC_SaveInputFile(HI_VOID* pInputStrem, HI_U32 StreamSize)
{
    HI_S32 Fd = -1;
    static HI_S32 Cnt = 0;
    FILE *pFile = NULL;
    HI_CHAR FileName[JPEG_PATH_MAX_LEN] = {'\0'};

    if ((NULL == pInputStrem) || (0 == StreamSize))
    {
       JPEG_TRACE("++++ input stream is null\n");
       return;
    }

    Cnt = (Cnt >= 100) ? (0) : (Cnt + 1);
    snprintf(FileName,JPEG_PATH_MAX_LEN,"%s/input_mjpeg_stream_%d.jpg",SAVE_JPEG_FILE_DIR,Cnt);
    FileName[JPEG_PATH_MAX_LEN - 1] = '\0';

    pFile = fopen(FileName,"wb+");
    if (NULL == pFile)
    {
       JPEG_TRACE("++++ open %s failure\n",FileName);
       return;
    }

    Fd = fileno(pFile);
    if (Fd < 0)
    {
       fclose(pFile);
       return;
    }

    if (0 != fchmod(Fd, S_IRUSR | S_IWUSR))
    {
       fclose(pFile);
       return;
    }

    (HI_VOID)fwrite(pInputStrem,StreamSize,1,pFile);
    fclose(pFile);

    JPEG_TRACE("\n=====================================================================\n");
    JPEG_TRACE("save %s success\n",FileName);
    JPEG_TRACE("=====================================================================\n");

    return;
}

HI_VOID JPEG_DEC_SaveInputMjpeg(HI_VOID* pInputStrem, HI_U32 StreamSize)
{
    HI_S32 Fd = -1;
    FILE *pFile = NULL;
    HI_CHAR FileName[JPEG_PATH_MAX_LEN] = {'\0'};

    if ((NULL == pInputStrem) || (0 == StreamSize))
    {
       JPEG_TRACE("++++ input stream is null\n");
       return;
    }

    snprintf(FileName,JPEG_PATH_MAX_LEN,"%s/input_mjpeg_stream.avi",SAVE_MJPEG_FILE_DIR);
    FileName[JPEG_PATH_MAX_LEN - 1] = '\0';

    pFile = fopen(FileName, "ab+");
    if (NULL == pFile)
    {
       JPEG_TRACE("++++ open %s failure\n",FileName);
       return;
    }

    Fd = fileno(pFile);
    if (Fd < 0)
    {
       fclose(pFile);
       return;
    }

    if (0 != fchmod(Fd, S_IRUSR | S_IWUSR))
    {
       fclose(pFile);
       return;
    }

    (HI_VOID)fwrite(&StreamSize,4,1,pFile);
    (HI_VOID)fwrite(pInputStrem,StreamSize,1,pFile);
    fclose(pFile);

    return;
}

HI_VOID JPEG_DEC_SaveYuvSp(HI_CHAR* pYStream, HI_S32 YWidth, HI_S32 YHeight, HI_S32 YStride,
                           HI_CHAR* pUVStream,HI_S32 UVWidth,HI_S32 UVHeight,HI_S32 UVStride,
                           HI_JPEG_FMT_E eFmt)
{
     HI_CHAR pFileName[JPEG_PATH_MAX_LEN] = {'\0'};
     HI_CHAR pHdrName[JPEG_PATH_MAX_LEN] = {'\0'};
     FILE* pOutFile = NULL;
     FILE* pHdrFile = NULL;
     HI_S32 s32Cnt  = 0;
     HI_S32 s32Cnt1 = 0;
     HI_S32 FileFd = -1;
     HI_S32 HdrFd = -1;
     HI_CHAR *pTmp  = NULL;
     HI_CHAR pTmpCbCr[10000];
     static HI_U32 Cnt = 0;

     Cnt = (Cnt >= 100) ? (0) : (Cnt + 1);

     snprintf(pFileName,256,"%s_%d.yuv",SAVE_YUVSP_FILE_DIR,Cnt);
     pFileName[JPEG_PATH_MAX_LEN - 1] = '\0';

     snprintf(pHdrName,256,"%s_%d.hdr",SAVE_YUVSP_FILE_DIR,Cnt);
     pHdrName[JPEG_PATH_MAX_LEN - 1] = '\0';

     pOutFile = fopen(pFileName,"wb+");
     if (NULL == pOutFile)
     {
        JPEG_TRACE("open %s failure\n",pFileName);
        goto FINISH_EXIT;
     }

     FileFd = fileno(pOutFile);
     if (FileFd < 0)
     {
        goto FINISH_EXIT;
     }

     if (0 != fchmod(FileFd, S_IRUSR | S_IWUSR))
     {
        goto FINISH_EXIT;
     }

     pHdrFile = fopen(pHdrName,"wb+");
     if (NULL == pHdrFile)
     {
        JPEG_TRACE("open %s failure\n",pHdrName);
        goto FINISH_EXIT;
     }

     HdrFd = fileno(pHdrFile);
     if (HdrFd < 0)
     {
        goto FINISH_EXIT;
     }

     if (0 != fchmod(HdrFd, S_IRUSR | S_IWUSR))
     {
        goto FINISH_EXIT;
     }

     /**<-- save y data >**/
     if ((NULL == pYStream) || (0 == YWidth))
     {
        goto FINISH_EXIT;
     }

     pTmp = pYStream;
     for (s32Cnt = 0; s32Cnt < YHeight; s32Cnt++)
     {
         (HI_VOID)fwrite(pTmp, YWidth, 1, pOutFile);
         pTmp += YStride;
     }

     /**<-- save uv data >**/
     if ((NULL == pUVStream) || (0 == UVWidth) || (UVWidth >= (HI_S32)sizeof(pTmpCbCr)))
     {
        goto SAVE_HDR_FINISH_EXIT;
     }
     if (UVWidth >= 10000)
     {
         JPEG_TRACE("UVWidth >= 10000,UVWidth=%d\n",UVWidth);
         goto FINISH_EXIT;
     }
     /**<-- save u data >**/
     pTmp = pUVStream;
     for (s32Cnt = 0; s32Cnt < UVHeight; s32Cnt++)
     {
         for (s32Cnt1 = 0; s32Cnt1 < UVWidth; s32Cnt1++)
         {
             pTmpCbCr[s32Cnt1] = pTmp[2 * s32Cnt1 + 1];
         }
         (HI_VOID)fwrite(pTmpCbCr, UVWidth, 1, pOutFile );
         pTmp += UVStride;
     }

     /**<-- save v data >**/
     pTmp = pUVStream;
     for (s32Cnt = 0; s32Cnt < UVHeight; s32Cnt++)
     {
         for (s32Cnt1 = 0; s32Cnt1 < UVWidth; s32Cnt1++)
         {
             pTmpCbCr[s32Cnt1] = pTmp[2*s32Cnt1 + 0];
         }
         (HI_VOID)fwrite(pTmpCbCr, UVWidth, 1, pOutFile);
         pTmp += UVStride;
     }

SAVE_HDR_FINISH_EXIT:
     /**<-- save hdr data >**/
     switch (eFmt)
     {
         case HI_JPEG_FMT_YUV400:
             DADA_WRITE(pHdrFile, "format = \"Y\" ;\n");
             break;
         case HI_JPEG_FMT_YUV420:
             DADA_WRITE(pHdrFile, "format = \"YUV420\" ;\n");
             break;
         case HI_JPEG_FMT_YUV422_12:
             DADA_WRITE(pHdrFile, "format = \"YUV422\" ;\n");
             break;
         case HI_JPEG_FMT_YUV422_21:
             DADA_WRITE(pHdrFile, "format = \"YUV422\" ;\n");
             break;
         case HI_JPEG_FMT_YUV444:
             DADA_WRITE(pHdrFile, "format = \"YUV444\" ;\n");
             break;
         default:
             JPEG_TRACE("format is unknow ;\n");
             break;
     }

     DADA_WRITE(pHdrFile, "offset = 0 ;\n");
     DADA_WRITE(pHdrFile, "width = %d ;\n",   YWidth);
     DADA_WRITE(pHdrFile, "height = %d ;\n",  YHeight);
     DADA_WRITE(pHdrFile, "framerate = 50 ;\n");
     DADA_WRITE(pHdrFile, "loop = 1 ;\n");

     JPEG_TRACE("\n=====================================================================\n");
     JPEG_TRACE("save %s success\n",pFileName);
     JPEG_TRACE("save %s success\n",pHdrName);
     JPEG_TRACE("=====================================================================\n");

FINISH_EXIT:
     if (NULL != pOutFile)
     {
        fclose(pOutFile);
     }

     if (NULL != pHdrFile)
     {
        fclose(pHdrFile);
     }

     return;
}
#endif

static inline HI_VOID JPEG_HDEC_WhetherDebug(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
#ifndef CONFIG_GFX_PROC_UNSUPPORT
  #ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
    HI_CHAR JpegDecMod[256] = {'\0'};
    /**<-- setprop persist.sys.jpeg.debug open >**/

    property_get("persist.sys.jpeg.debug",JpegDecMod,"close");
    JpegDecMod[sizeof(JpegDecMod) - 1] = '\0';

    if (0 == strncmp("open", JpegDecMod, strlen("open") > strlen(JpegDecMod) ? (strlen("open")) : (strlen(JpegDecMod))))
    {
        pJpegHandle->stProcInfo.NeedProcMsg = HI_TRUE;
        return;
    }
  #else
    HI_CHAR *pJpegDecMod = NULL;
    /** export HISI_JPEG_DEBUG=open **/
    pJpegDecMod = getenv("HISI_JPEG_DEBUG");
    if (NULL == pJpegDecMod)
    {
         return;
    }

    if (0 == strncmp("open", pJpegDecMod, strlen("open") > strlen(pJpegDecMod) ? (strlen("open")) : (strlen(pJpegDecMod))))
    {
        pJpegHandle->stProcInfo.NeedProcMsg = HI_TRUE;
        return;
    }
  #endif
#endif

    return;
}

static HI_VOID PrintImageInfo(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    JPEG_TRACE("input jpeg information:\n");

    JPEG_TRACE("---input [w h] : [%d %d]\n",pJpegHandle->stImgInfo.image_width,pJpegHandle->stImgInfo.image_height);
    JPEG_TRACE("---scale times : %d\n",pJpegHandle->stImgInfo.scale_denom);

    switch (pJpegHandle->stImgInfo.jpeg_color_space)
    {
         case HI_JPEG_FMT_YUV400:
             JPEG_TRACE("---input color : yuv400\n");
             break;
         case HI_JPEG_FMT_YUV420:
             JPEG_TRACE("---input color : yuv420\n");
             break;
         case HI_JPEG_FMT_YUV422_12:
             JPEG_TRACE("---input color : yuv422_12\n");
             break;
         case HI_JPEG_FMT_YUV422_21:
             JPEG_TRACE("---input color : yuv422_21\n");
             break;
         case HI_JPEG_FMT_YUV444:
             JPEG_TRACE("---input color : yuv444\n");
             break;
         case HI_JPEG_FMT_YCCK:
             JPEG_TRACE("---input color : YCCK\n");
             break;
         case HI_JPEG_FMT_CMYK:
             JPEG_TRACE("---input color : CMYK\n");
             break;
         case HI_JPEG_FMT_RGB_888:
             JPEG_TRACE("---input color : adobe rgb\n");
             break;
         default:
             JPEG_TRACE("---input color : format is unknow\n");
             break;
    }
    return;
}

static HI_VOID PrintOutInfo(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    JPEG_TRACE("output jpeg information:\n");

    JPEG_TRACE("---output [w h] : [%d %d]\n",pJpegHandle->stImgInfo.output_width,pJpegHandle->stImgInfo.output_height);

    switch (pJpegHandle->stImgInfo.output_color_space)
    {
         case HI_JPEG_FMT_YUV400:
             JPEG_TRACE("---output color : yuv400\n");
             break;
         case HI_JPEG_FMT_YUV420:
             JPEG_TRACE("---output color : yuv420\n");
             break;
         case HI_JPEG_FMT_YUV422_12:
             JPEG_TRACE("---output color : yuv422_12\n");
             break;
         case HI_JPEG_FMT_YUV422_21:
             JPEG_TRACE("---output color : yuv422_21\n");
             break;
         case HI_JPEG_FMT_YUV444:
             JPEG_TRACE("---output color : yuv444\n");
             break;
         case HI_JPEG_FMT_YCCK:
             JPEG_TRACE("---output color : YCCK\n");
             break;
         case HI_JPEG_FMT_CMYK:
             JPEG_TRACE("---output color : CMYK\n");
             break;
         case HI_JPEG_FMT_RGB_888:
             JPEG_TRACE("---output color : rgb888\n");
             break;
         case HI_JPEG_FMT_BGR_888:
             JPEG_TRACE("---output color : bgr888\n");
             break;
         case HI_JPEG_FMT_RGB_565:
             JPEG_TRACE("---output color : rgb565\n");
             break;
         case HI_JPEG_FMT_BGR_565:
             JPEG_TRACE("---output color : bgr565\n");
             break;
         case HI_JPEG_FMT_ARGB_8888:
             JPEG_TRACE("---output color : argb8888\n");
             break;
         case HI_JPEG_FMT_ABGR_8888:
             JPEG_TRACE("---output color : abgr8888\n");
             break;
         case HI_JPEG_FMT_ARGB_1555:
             JPEG_TRACE("---output color : argb1555\n");
             break;
         default:
             JPEG_TRACE("---output color : format is unknow\n");
             break;
    }
    return;
}

static HI_VOID PrintSupportHardDec(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    JPEG_TRACE("whether support hard decode:\n");
    if (HI_FALSE == pJpegHandle->stProcInfo.LowDelaySupport)
    {
       JPEG_TRACE("---soft decode: can not support lowdelay---\n");
       return;
    }

    if (HI_SUCCESS != pJpegHandle->stProcInfo.SupportOutUsrBuf)
    {
       JPEG_TRACE("---soft decode:  only support out to usr buffer---\n");
       return;
    }

    if (HI_TRUE == pJpegHandle->stProcInfo.ProgressiveMode)
    {
       JPEG_TRACE("---soft decode:  progressive picture---\n");
       return;
    }

    if (HI_TRUE == pJpegHandle->stProcInfo.ArithMode)
    {
       JPEG_TRACE("---soft decode:  arith mode picture---\n");
       return;
    }

    if (8 != pJpegHandle->stProcInfo.DataPrecision)
    {
       JPEG_TRACE("---soft decode:  data precision is not equal to 8---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.DriSupport)
    {
       JPEG_TRACE("---soft decode:  can not support dri mark---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.HufNumSupport)
    {
       JPEG_TRACE("---soft decode:  can not support more num table---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.ScaleSupport)
    {
       JPEG_TRACE("---soft decode:  can not support other scale---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.SampleFactorSupport)
    {
       JPEG_TRACE("---soft decode:  can not support factor---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.InputImgSizeSupport)
    {
       JPEG_TRACE("---soft decode:  can not support large size---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.OutColorSpaceSupport)
    {
       JPEG_TRACE("---soft decode:  can not support other color---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.OpenDevSuccess)
    {
       JPEG_TRACE("---soft decode:  open jpeg dev failure---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.GetDevSuccess)
    {
       JPEG_TRACE("---soft decode:  get jpeg dev failure---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.OpenCscDevSuccess)
    {
       JPEG_TRACE("---soft decode:  open csc dev failure---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.OpenIonDevSuccess)
    {
       JPEG_TRACE("---soft decode:  open ion dev failure---\n");
       return;
    }

    if (HI_FALSE == pJpegHandle->stProcInfo.AllocMemSuccess)
    {
       JPEG_TRACE("---soft decode:  not enough memory---\n");
       return;
    }

    if (HI_TRUE == pJpegHandle->bHdecSuccess)
    {
        JPEG_TRACE("---hard decode success---\n");
    }
    else
    {
        JPEG_TRACE("---soft decode success---\n");
    }

    return;
}

HI_VOID JPEG_DEC_PrintProcMsg(HI_ULONG DecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)DecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    JPEG_HDEC_WhetherDebug(pJpegHandle);
    if (HI_FALSE == pJpegHandle->stProcInfo.NeedProcMsg)
    {
        return;
    }

    JPEG_TRACE("\n======================= jpeg dec information =======================\n");

    if (HI_TRUE == pJpegHandle->stProcInfo.UseStandardLibDec)
    {
       JPEG_TRACE("use standard jpeg lib decode\n");
    }
    else
    {
       JPEG_TRACE("use hisi hard decode lib for mjpeg\n");
    }

    JPEG_TRACE("decode cost times   : %dms\n", pJpegHandle->stProcInfo.DecCostTimes);
    JPEG_TRACE("hard dec cost times : %dms\n", pJpegHandle->stProcInfo.HardDecTimes);

    PrintImageInfo(pJpegHandle);
    PrintOutInfo(pJpegHandle);
    PrintSupportHardDec(pJpegHandle);

    JPEG_TRACE("=====================================================================\n");
}
