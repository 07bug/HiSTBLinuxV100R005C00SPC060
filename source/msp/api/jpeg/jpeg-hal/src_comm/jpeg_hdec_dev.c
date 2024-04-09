/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name        : jpeg_hdec_dev.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : 设备操作文件
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
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


/** drv **/
#include "hi_jpeg_config.h"
#include "jpeg_hdec_api.h"

/** drv **/
#include "hi_jpeg_reg.h"

#ifdef CONFIG_GFX_ANDROID_HIDL
#include "jpeg_hidl_hal.h"
#endif
/***************************** Macro Definition     ***********************************************/

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG  "libjpeg"

/***************************** Structure Definition ***********************************************/

/********************** Global Variable declaration ***********************************************/

/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/
extern HI_VOID JPEG_DEC_PrintProcMsg(HI_ULONG DecHandle);

/******************************* API realization **************************************************/
static HI_VOID JPEG_DEC_CloseDev(HI_ULONG HdecHandle)
{
    JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
    if (NULL == pJpegHandle)
    {
        return;
    }

    if (NULL != pJpegHandle->pJpegRegVirAddr)
    {
       (HI_VOID)munmap((void*)pJpegHandle->pJpegRegVirAddr, JPGD_REG_LENGTH);
       pJpegHandle->pJpegRegVirAddr = NULL;
    }

    if (pJpegHandle->JpegDev >= 0)
    {
    #ifdef CONFIG_GFX_ANDROID_HIDL
       if (HI_TRUE == pJpegHandle->UseHidlOpen)
       {
          JPEG_HIDL_CloseJpegDev(pJpegHandle->JpegDev);
       }
       else
    #endif
       {
          close(pJpegHandle->JpegDev);
       }
       pJpegHandle->JpegDev = -1;
    }

    if (pJpegHandle->CscDev >= 0)
    {
    #ifdef CONFIG_GFX_ANDROID_HIDL
       if (HI_TRUE == pJpegHandle->UseHidlOpen)
       {
          JPEG_HIDL_CloseGfx2dDev(pJpegHandle->CscDev);
       }
    #endif
       {
          JPEG_DEC_CSC_Close(pJpegHandle->CscDev);
       }
       pJpegHandle->CscDev = -1;
    }

#ifdef CONFIG_GFX_MEM_ION
    if (pJpegHandle->MemDev >= 0)
    {
    #ifdef CONFIG_GFX_ANDROID_HIDL
        if (HI_TRUE == pJpegHandle->UseHidlOpen)
        {
           JPEG_HIDL_CloseMemDev(pJpegHandle->MemDev);
        }
    #endif
        {
           JPEG_DEC_CloseMemDev(pJpegHandle->MemDev);
        }
        pJpegHandle->MemDev = -1;
    }
#endif

    return;
}


static HI_BOOL JPEG_HDEC_OpenDev(HI_ULONG HdecHandle)
{
     HI_S32 Ret = HI_SUCCESS;
     JPEG_HDEC_HANDLE_S_PTR pJpegHandle = (JPEG_HDEC_HANDLE_S_PTR)HdecHandle;
     if (NULL == pJpegHandle)
     {
         return HI_FALSE;
     }

     pJpegHandle->JpegDev = open("/dev/jpeg", O_RDWR | O_SYNC, S_IRUSR);
#if 0//def CONFIG_GFX_ANDROID_HIDL
     if (pJpegHandle->JpegDev < 0)
     {
         pJpegHandle->JpegDev = JPEG_HIDL_OpenJpegDev();
         pJpegHandle->UseHidlOpen = HI_TRUE;
     }
#endif
     if (pJpegHandle->JpegDev < 0)
     {
         return HI_FALSE;
     }
     pJpegHandle->stProcInfo.OpenDevSuccess = HI_TRUE;

     Ret = ioctl(pJpegHandle->JpegDev, CMD_JPG_GETDEVICE);
     if (HI_SUCCESS != Ret)
     {
         JPEG_DEC_CloseDev(HdecHandle);
         return HI_FALSE;
     }
     pJpegHandle->stProcInfo.GetDevSuccess = HI_TRUE;

     pJpegHandle->pJpegRegVirAddr = (volatile char*)mmap(NULL,JPGD_REG_LENGTH,PROT_READ | PROT_WRITE,MAP_SHARED,pJpegHandle->JpegDev,(off_t)0);
     if (MAP_FAILED == pJpegHandle->pJpegRegVirAddr)
     {
         JPEG_DEC_CloseDev(HdecHandle);
         return HI_FALSE;
     }

#ifndef CONFIG_JPEG_CSC_DISABLE
     pJpegHandle->CscDev = JPEG_DEC_CSC_Open();
  #if 0//def CONFIG_GFX_ANDROID_HIDL
     if (pJpegHandle->CscDev < 0)
     {
         pJpegHandle->CscDev = JPEG_HIDL_OpenGfx2dDev();
         pJpegHandle->UseHidlOpen = HI_TRUE;
     }
  #endif
     if (pJpegHandle->CscDev < 0)
     {
         JPEG_DEC_CloseDev(HdecHandle);
         return HI_FALSE;
     }
     pJpegHandle->stProcInfo.OpenCscDevSuccess = HI_TRUE;
#endif

#ifdef CONFIG_GFX_MEM_ION
     pJpegHandle->MemDev = JPEG_HDEC_OpenMemDev();
   #if 0//def CONFIG_GFX_ANDROID_HIDL
     if (pJpegHandle->MemDev < 0)
     {
         pJpegHandle->MemDev = JPEG_HIDL_OpenMemDev();
         pJpegHandle->UseHidlOpen = HI_TRUE;
     }
   #endif
     if (pJpegHandle->MemDev < 0)
     {
         JPEG_DEC_CloseDev(HdecHandle);
         return HI_FALSE;
     }
     pJpegHandle->stProcInfo.OpenIonDevSuccess = HI_TRUE;
#endif

     return HI_TRUE;
}
