/**************************************************************************************************
*
* Copyright (C) 2017 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : jpeg_hidl_hal.c
Version          : Initial Draft
Author           :
Created          : 2017/10/01
Description      : 硬件解码及新增功能对外接口
Function List    :

History          :
Date                     Author           Modification
2017/10/01               sdk              Created file
***************************************************************************************************/


/****************************  add include here     ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include "utils/Log.h"

#include "jpeg_hidl_hal.h"

#include <vendor/hisilicon/hardware/hwjpeg/1.0/IHwjpeg.h>
#include <vendor/hisilicon/hardware/hwjpeg/1.0/types.h>

using vendor::hisilicon::hardware::hwjpeg::V1_0::IHwjpeg;
using ::android::hardware::hidl_string;

/***************************** Macro Definition     ***********************************************/
//#define SERVICE_CAPA_DEBUG

#ifdef LOG_TAG
  #undef LOG_TAG
#endif
#define LOG_TAG  "libjpeg"


#ifdef SERVICE_CAPA_DEBUG
#define SERVICE_TINIT()   struct timeval tv_start, tv_end; unsigned int time_cost,line_start
#define SERVICE_TSTART()  gettimeofday(&tv_start, NULL);line_start = __LINE__
#define SERVICE_TEND()    \
	gettimeofday(&tv_end, NULL); \
	time_cost = ((tv_end.tv_usec - tv_start.tv_usec) + (tv_end.tv_sec - tv_start.tv_sec)*1000000); \
	ALOGE("=============================================================================\n"); \
	ALOGE("FROM LINE: %d TO LINE: %d COST: %d us\n",line_start, __LINE__, time_cost);		  \
	ALOGE("=============================================================================\n")
#endif

/***************************** Structure Definition ***********************************************/


/********************** Global Variable declaration ***********************************************/

/********************** API forward declarations    ***********************************************/

/**********************       API realization       ***********************************************/


/******************************* API realization **************************************************/
//begin namespace
namespace android {

HI_S32 call_HIDL_OpenJpegDev(HI_VOID)
{
    HI_S32 Fd = -1;
	sp<IHwjpeg> mHal = NULL;

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TINIT();
	SERVICE_TSTART();
#endif

	mHal = IHwjpeg::getService();
	if (mHal != NULL)
	{
		Fd = mHal->OpenJpegDev();
	}
    else
    {
        ALOGE("+++++++func %s line %d getService failure\n",__FUNCTION__,__LINE__);
 	}

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TEND();
#endif

    return Fd;
}

HI_VOID call_HIDL_CloseJpegDev(HI_S32 Fd)
{
	sp<IHwjpeg> mHal = NULL;

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TINIT();
	SERVICE_TSTART();
#endif

    if (Fd < 0)
	{
       return;
	}

	mHal = IHwjpeg::getService();
	if (mHal != NULL)
	{
	   mHal->CloseJpegDev(Fd);
	}
	else
	{
		ALOGE("+++++++func %s line %d getService failure\n",__FUNCTION__,__LINE__);
	}

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TEND();
#endif
}

HI_S32 call_HIDL_OpenGfx2dDev(HI_VOID)
{
	HI_S32 Fd = -1;
	sp<IHwjpeg> mHal = NULL;

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TINIT();
	SERVICE_TSTART();
#endif

   mHal = IHwjpeg::getService();
   if (mHal != NULL)
   {
   	  Fd = mHal->OpenGfx2dDev();
   }
   else
   {
   	  ALOGE("+++++++func %s line %d getService failure\n",__FUNCTION__,__LINE__);
   }

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TEND();
#endif

	return Fd;
}

HI_VOID call_HIDL_CloseGfx2dDev(HI_S32 Fd)
{
	sp<IHwjpeg> mHal = NULL;

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TINIT();
	SERVICE_TSTART();
#endif

	if (Fd < 0)
	{
	   return;
	}

	mHal = IHwjpeg::getService();
	if (mHal != NULL)
	{
	   mHal->CloseGfx2dDev(Fd);
	}
    else
    {
       ALOGE("+++++++func %s line %d getService failure\n",__FUNCTION__,__LINE__);
    }

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TEND();
#endif
}


HI_S32 call_HIDL_OpenMemDev(HI_VOID)
{
	HI_S32 Fd = -1;
	sp<IHwjpeg> mHal = NULL;

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TINIT();
	SERVICE_TSTART();
#endif

    mHal = IHwjpeg::getService();
    if (mHal != NULL)
    {
       Fd = mHal->OpenMemDev();
    }
	else
    {
       ALOGE("+++++++func %s line %d getService failure\n",__FUNCTION__,__LINE__);
    }

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TEND();
#endif

	return Fd;
}


HI_VOID call_HIDL_CloseMemDev(HI_S32 Fd)
{
	sp<IHwjpeg> mHal = NULL;

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TINIT();
	SERVICE_TSTART();
#endif

	if (Fd < 0)
	{
	   return;
	}

	mHal = IHwjpeg::getService();
	if (mHal != NULL)
	{
	   mHal->CloseMemDev(Fd);
	}
	else
    {
       ALOGE("+++++++func %s line %d getService failure\n",__FUNCTION__,__LINE__);
    }

#ifdef SERVICE_CAPA_DEBUG
	SERVICE_TEND();
#endif
}


};
//end namespace


extern "C" {

    HI_S32 JPEG_HIDL_OpenJpegDev(HI_VOID)
    {
        return android::call_HIDL_OpenJpegDev();
    }

    HI_VOID JPEG_HIDL_CloseJpegDev(HI_S32 Fd)
    {
        android::call_HIDL_CloseJpegDev(Fd);
    }

    HI_S32 JPEG_HIDL_OpenGfx2dDev(HI_VOID)
    {
        return android::call_HIDL_OpenGfx2dDev();
    }

    HI_VOID JPEG_HIDL_CloseGfx2dDev(HI_S32 Fd)
    {
        android::call_HIDL_CloseGfx2dDev(Fd);
    }

	HI_S32 JPEG_HIDL_OpenMemDev(HI_VOID)
    {
        return android::call_HIDL_OpenMemDev();
    }

    HI_VOID JPEG_HIDL_CloseMemDev(HI_S32 Fd)
    {
        android::call_HIDL_CloseMemDev(Fd);
    }
}
