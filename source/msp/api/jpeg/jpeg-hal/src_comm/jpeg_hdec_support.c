/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hdec_support.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : check whether hard decode support CNend\n
Function List    :


History          :
Date                      Author                Modification
2018/01/01                sdk                    Created file
*************************************************************************************************/

/***************************** add include here**************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include "hi_jpeg_config.h"

#include "jpeg_hdec_api.h"
#include "hi_type.h"
/***************************** Macro Definition *************************************************/

#define  ANDROID_VERSION_2_2     "ndroid.cts.stub"
#define  ANDROID_VERSION_4_4     "id.cts.graphics"
#define  ANDROID_VERSION_5_1     "id.graphics.cts"
#define  ANDROID_VERSION_7_0     "roid.camera.cts"
#define  ANDROID_VERSION_8_0     "system_server"
#define  ANDROID_VERSION_8_0_1   "stscontainerapp"

/***************************** Structure Definition *********************************************/

#ifdef LOG_TAG
  #undef LOG_TAG
#endif
#define LOG_TAG  "libjpeg"

/***************************** Global Variable declaration **************************************/

/***************************** API forward declarations *****************************************/
static inline HI_S32  JPEG_HDEC_SupportOutUsrBuf(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_BOOL JPEG_HDEC_ForceToSoftDec(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_BOOL JPEG_HDEC_SupportCts(HI_VOID);
static inline HI_BOOL JPEG_HDEC_DriSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_BOOL JPEG_HDEC_HufTableNumSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_BOOL JPEG_HDEC_ScaleSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_BOOL JPEG_HDEC_SampleFactorSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_BOOL JPEG_HDEC_InputImgSizeSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);
static inline HI_BOOL JPEG_HDEC_OutColorSpaceSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle);

/***************************** API realization **************************************************/
static HI_VOID JPEG_DEC_SupportHardDecompress(HI_ULONG HdecHandle)
{
    HI_BOOL SupportCts = HI_FALSE;
    HI_BOOL ForceToSoftDec = HI_FALSE;
    HI_BOOL OpenDevSuccess = HI_FALSE;

    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
       return;
    }

    /**<-- has been call start decode>**/
    /**<--已经调用过解码>**/
    if (HI_TRUE == pJpegHandle->bCheckedSupportHardDec)
    {
       return;
    }

    pJpegHandle->bCheckedSupportHardDec = HI_TRUE;

    /**<-- initial hard dec not support >**/
    /**<--初始化硬件解码不支持>**/
    pJpegHandle->SupportHardDec = HI_FALSE;

    /**<-- initial resources has been release >**/
    /**<--初始化资源已经被释放>**/
    pJpegHandle->bReleaseRes =  HI_FALSE;

    pJpegHandle->stProcInfo.LowDelaySupport = JPEG_HDEC_SupportLowDelay(HdecHandle);
    if (HI_FALSE == pJpegHandle->stProcInfo.LowDelaySupport)
    {
       return;
    }

    JPEG_HDEC_GetImagInfo(HdecHandle);

    /**<-- only support out to phymem  >**/
    /**<-- 只支持解码输出到用户连续的物理内存 >**/
    pJpegHandle->stProcInfo.SupportOutUsrBuf = JPEG_HDEC_SupportOutUsrBuf(pJpegHandle);
    if (HI_SUCCESS != pJpegHandle->stProcInfo.SupportOutUsrBuf)
    {
        return;
    }

    ForceToSoftDec = JPEG_HDEC_ForceToSoftDec(pJpegHandle);
    if (HI_TRUE == ForceToSoftDec)
    {
        return;
    }

    SupportCts = JPEG_HDEC_SupportCts();
    if (HI_TRUE == SupportCts)
    {
        return;
    }

    pJpegHandle->stProcInfo.DriSupport = JPEG_HDEC_DriSupport(pJpegHandle);
    if (HI_TRUE != pJpegHandle->stProcInfo.DriSupport)
    {
        return;
    }

    pJpegHandle->stProcInfo.HufNumSupport = JPEG_HDEC_HufTableNumSupport(pJpegHandle);
    if (HI_TRUE != pJpegHandle->stProcInfo.HufNumSupport)
    {
        return;
    }

    pJpegHandle->stProcInfo.ScaleSupport = JPEG_HDEC_ScaleSupport(pJpegHandle);
    if (HI_TRUE != pJpegHandle->stProcInfo.ScaleSupport)
    {
        return;
    }

    pJpegHandle->stProcInfo.SampleFactorSupport = JPEG_HDEC_SampleFactorSupport(pJpegHandle);
    if (HI_TRUE != pJpegHandle->stProcInfo.SampleFactorSupport)
    {
        return;
    }

    pJpegHandle->stProcInfo.InputImgSizeSupport = JPEG_HDEC_InputImgSizeSupport(pJpegHandle);
    if (HI_TRUE != pJpegHandle->stProcInfo.InputImgSizeSupport)
    {
        return;
    }

    pJpegHandle->stProcInfo.OutColorSpaceSupport = JPEG_HDEC_OutColorSpaceSupport(pJpegHandle);
    if (HI_TRUE != pJpegHandle->stProcInfo.OutColorSpaceSupport)
    {
        return;
    }

    OpenDevSuccess = JPEG_HDEC_OpenDev(HdecHandle);
    if (HI_TRUE != OpenDevSuccess)
    {
        return;
    }

    pJpegHandle->stProcInfo.AllocMemSuccess = JPEG_HDEC_AllocDecodeMemory(HdecHandle);
    if (HI_TRUE != pJpegHandle->stProcInfo.AllocMemSuccess)
    {
        JPEG_HDEC_FreeDecodeMemory(HdecHandle);
        return;
    }

    /**<-- initial hard dec support >**/
    /**<--初始化硬件解码支持>**/
    pJpegHandle->SupportHardDec = HI_TRUE;

    return;
}

static inline HI_BOOL JPEG_HDEC_ForceToSoftDec(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    /**<-- not support progressive >**/
    /**<--不支持progressive 图片>**/
    if (HI_FALSE != pJpegHandle->stImgInfo.progressive_mode)
    {
        pJpegHandle->stProcInfo.ProgressiveMode = HI_TRUE;
        return HI_TRUE;
    }

    /**<-- not support arith code >**/
    /**<--不支持算术编码>**/
    if (HI_FALSE != pJpegHandle->stImgInfo.arith_code)
    {
       pJpegHandle->stProcInfo.ArithMode = HI_TRUE;
       return HI_TRUE;
    }

    /**<-- not support data precision is 8 bits >**/
    /**<--不支持精度不为8 的>**/
    if (8 != pJpegHandle->stImgInfo.data_precision)
    {
        return HI_TRUE;
    }
    pJpegHandle->stProcInfo.DataPrecision = pJpegHandle->stImgInfo.data_precision;

    return HI_FALSE;
}

static inline HI_BOOL JPEG_HDEC_SupportCts(HI_VOID)
{
#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
    HI_S32 C = 0;
    HI_S32 Cnt = 0;
    HI_S32 Fd = -1;
    HI_CHAR ProcName[PATH_MAX] = {'\0'};

    HI_S32 Pid = 0;
    FILE* pProcessStatus = NULL;
    HI_CHAR ProcessStatusPath[PATH_MAX] = {'\0'};
    HI_CHAR acRealPath[PATH_MAX] = {'\0'};

    struct stat st;
    HI_GFX_Memset(&st,0x0,sizeof(st));

    Pid = getpid();
    snprintf(ProcessStatusPath,PATH_MAX,"%s%d%s","/proc/",Pid,"/status");
    ProcessStatusPath[sizeof(ProcessStatusPath) - 1] = '\0';

    if (NULL == realpath(ProcessStatusPath, acRealPath))
    {
       return HI_FALSE;
    }
    acRealPath[sizeof(acRealPath) - 1] = '\0';

    pProcessStatus = fopen(acRealPath, "r");
    if (NULL == pProcessStatus)
    {
        return HI_FALSE;
    }

    Fd = fileno(pProcessStatus);
    if (Fd < 0)
    {
       fclose(pProcessStatus);
       return HI_FALSE;
    }

    if (0 != fstat(Fd, &st))
    {
       fclose(pProcessStatus);
       return HI_FALSE;
    }

    if (S_IRUSR != (st.st_mode & S_IRUSR))
    {
       fchmod(Fd, S_IRUSR);
    }

    C = fgetc(pProcessStatus);
    while (C != '\n' && C != EOF && Cnt < (PATH_MAX - 1))
    {
       if (('\t' == C) || (' ' == C))
       {
          Cnt = 0;
          HI_GFX_Memset(ProcName,'\0',sizeof(ProcName));
       }
       else
       {
          ProcName[Cnt++] = C;
       }
       C = fgetc(pProcessStatus);
    }
    ProcName[Cnt] = '\0';

    fclose(pProcessStatus);

    if (  (0 == strncmp(ANDROID_VERSION_2_2, ProcName, strlen(ANDROID_VERSION_2_2) > strlen(ProcName) ? strlen(ANDROID_VERSION_2_2) : strlen(ProcName)))
        ||(0 == strncmp(ANDROID_VERSION_4_4, ProcName, strlen(ANDROID_VERSION_4_4) > strlen(ProcName) ? strlen(ANDROID_VERSION_4_4) : strlen(ProcName)))
        ||(0 == strncmp(ANDROID_VERSION_5_1, ProcName, strlen(ANDROID_VERSION_5_1) > strlen(ProcName) ? strlen(ANDROID_VERSION_5_1) : strlen(ProcName)))
        ||(0 == strncmp(ANDROID_VERSION_7_0, ProcName, strlen(ANDROID_VERSION_7_0) > strlen(ProcName) ? strlen(ANDROID_VERSION_7_0) : strlen(ProcName)))
        ||(0 == strncmp(ANDROID_VERSION_8_0, ProcName, strlen(ANDROID_VERSION_8_0) > strlen(ProcName) ? strlen(ANDROID_VERSION_8_0) : strlen(ProcName)))
        ||(0 == strncmp(ANDROID_VERSION_8_0_1, ProcName, strlen(ANDROID_VERSION_8_0_1) > strlen(ProcName) ? strlen(ANDROID_VERSION_8_0_1) : strlen(ProcName))))
    {
        return HI_TRUE;
    }
#endif
    return HI_FALSE;
}

static inline HI_BOOL JPEG_HDEC_DriSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
#ifndef CONFIG_JPEG_DRI_SUPPORT
     if (  (0 != pJpegHandle->stImgInfo.LuDcLen[0]) || (0 != pJpegHandle->stImgInfo.LuDcLen[1])
         ||(0 != pJpegHandle->stImgInfo.LuDcLen[2]) || (0 != pJpegHandle->stImgInfo.LuDcLen[3])
         ||(0 != pJpegHandle->stImgInfo.LuDcLen[4]) || (0 != pJpegHandle->stImgInfo.LuDcLen[5]))
     {
         return HI_FALSE;
     }
#else
     HI_UNUSED(pJpegHandle);
#endif
     return HI_TRUE;
}

static inline HI_BOOL JPEG_HDEC_ScaleSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    if (pJpegHandle->ScalRation > CONFIG_JPEG_SCALE_MULTIPLE_8)
    {
        return HI_FALSE;
    }

#ifdef CONFIG_JPEG_OUTPUT_YUV420SP
    if ( (HI_TRUE == pJpegHandle->bOutYUV420SP) && (CONFIG_JPEG_SCALE_MULTIPLE_8 == pJpegHandle->ScalRation))
    {
        return HI_FALSE;
    }
 #endif

    return HI_TRUE;
}


static inline HI_BOOL JPEG_HDEC_SampleFactorSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
#ifdef CONFIG_JPEG_SET_SAMPLEFACTOR
    return pJpegHandle->stImgInfo.SampleFactorSupport;
#endif
    return HI_TRUE;
}


static inline HI_BOOL JPEG_HDEC_InputImgSizeSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
     if ( (pJpegHandle->stImgInfo.image_width  < 1) || (pJpegHandle->stImgInfo.image_width  > 8096)
        ||(pJpegHandle->stImgInfo.image_height < 1) || (pJpegHandle->stImgInfo.image_height > 8096))
     {
         return HI_FALSE;
     }

     return HI_TRUE;
}


static inline HI_BOOL JPEG_HDEC_OutColorSpaceSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
     if (  (HI_JPEG_FMT_CMYK == pJpegHandle->stImgInfo.jpeg_color_space)
         ||(HI_JPEG_FMT_YCCK == pJpegHandle->stImgInfo.jpeg_color_space)
         ||(HI_JPEG_FMT_BUTT == pJpegHandle->stImgInfo.jpeg_color_space)
         ||(HI_JPEG_FMT_RGB_888 == pJpegHandle->stImgInfo.jpeg_color_space))
     {
          return HI_FALSE;
     }

     if (  (HI_JPEG_FMT_YCbCr == pJpegHandle->stImgInfo.output_color_space)
         ||(HI_JPEG_FMT_CrCbY == pJpegHandle->stImgInfo.output_color_space)
         ||(HI_JPEG_FMT_BUTT  == pJpegHandle->stImgInfo.output_color_space))
     {
          return HI_FALSE;
     }

     return HI_TRUE;
}


static inline HI_BOOL JPEG_HDEC_HufTableNumSupport(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    if (HI_FALSE == pJpegHandle->stImgInfo.HuffTabNoSupport)
    {
         return HI_FALSE;
    }

     return HI_TRUE;
}


static inline HI_S32 JPEG_HDEC_SupportOutUsrBuf(JPEG_HDEC_HANDLE_S_PTR pJpegHandle)
{
    /**<-- decode out to yuv semi-planer  >**/
    /**<-- 解码输出yuv semi planer >**/
    if (HI_TRUE == pJpegHandle->bOutYCbCrSP)
    {
       if (HI_TRUE != pJpegHandle->bOutUsrBuf)
       {
          //JPEG_TRACE("++++++ only support out to user buffer\n");
          return HI_FAILURE;
       }

       if (0 == pJpegHandle->stOutSurface.BufPhy[0])
       {
          //JPEG_TRACE("++++++ only support out to user phy buffer\n");
          return HI_FAILURE;
       }

       if ((HI_JPEG_FMT_YUV400 != pJpegHandle->stImgInfo.output_color_space) && (0 == pJpegHandle->stOutSurface.BufPhy[1]))
       {
          //JPEG_TRACE("++++++ only support out to user buffer\n");
          return HI_FAILURE;
       }

       pJpegHandle->stProcInfo.SupportOutUsrBuf = HI_TRUE;

       return HI_SUCCESS;
   }

   /**<-- decode out to xrgb  >**/
   /**<-- 解码输出xrgb >**/
   if (HI_TRUE != pJpegHandle->bOutUsrBuf)
   {
       pJpegHandle->stProcInfo.SupportOutUsrBuf = HI_TRUE;
       return HI_SUCCESS;
   }

   if (0 == pJpegHandle->stOutSurface.BufPhy[0])
   {
       //JPEG_TRACE("++++++ only support out to user buffer\n");
       return HI_FAILURE;
   }

   pJpegHandle->stProcInfo.SupportOutUsrBuf = HI_TRUE;

   return HI_SUCCESS;
}
