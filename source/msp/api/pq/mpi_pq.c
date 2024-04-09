/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : mpi_pq.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2014/04/01
  Description   : MPI层封装函数

******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#include "hi_type.h"
#include <pthread.h>
#include "hi_mpi_pq.h"
#include "hi_mpi_mem.h"

/* PQ设备文件描述符 */
static HI_S32 sg_s32PQFd = -1;

static HI_BOOL sg_bPQInitFlag = HI_FALSE;

static pthread_mutex_t   g_PqApiMutex = PTHREAD_MUTEX_INITIALIZER;

#define HI_PQ_LOCK()     (void)pthread_mutex_lock(&g_PqApiMutex);
#define HI_PQ_UNLOCK()   (void)pthread_mutex_unlock(&g_PqApiMutex);

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 \PQ初始化
 \attention \n

 \param[in] pszPath:PQ配置文件路径
 \param[out]

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_Init(HI_CHAR *pszPath)
{
    HI_PQ_LOCK();

    if (HI_TRUE == sg_bPQInitFlag)
    {
        HI_PQ_UNLOCK();
        return HI_SUCCESS;
    }

    /* PQ设备初始化 */
    sg_s32PQFd = open("/dev/hi_pq", O_RDWR | O_NONBLOCK, 0);
    if (sg_s32PQFd <= 0)
    {
        HI_ERR_PQ("PQ device open error!\n");
        HI_PQ_UNLOCK();
        return HI_ERR_PQ_DEV_OPEN_ERR;
    }

    sg_bPQInitFlag = HI_TRUE;
    HI_PQ_UNLOCK();

    return HI_SUCCESS;
}

/**
 \PQ去初始化
 \attention \n

 \param[in]
 \param[out]

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_LOCK();

    if (HI_FALSE == sg_bPQInitFlag)
    {
        HI_PQ_UNLOCK();
        return HI_SUCCESS;
    }

    s32Ret = close(sg_s32PQFd);
    if (HI_SUCCESS != s32Ret)
    {
        HI_PQ_UNLOCK();
        return HI_ERR_PQ_DEV_CLOSE_ERR;
    }

    sg_bPQInitFlag = HI_FALSE;

    HI_PQ_UNLOCK();
    return s32Ret;
}

/**
 \brief 获取亮度
 \attention \n
无

 \param[in] pu32Brightness 亮度值,有效范围: 0~100;
 \param[out]

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetBrightness(HI_DRV_DISPLAY_E enChan, HI_U32 *pu32Brightness)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RetNum = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Brightness);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SD_BRIGHTNESS, &u32RetNum);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_HD_BRIGHTNESS, &u32RetNum);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_BRIGHTNESS Failure [%d]!\n", enChan);
        return s32Ret;
    }

    *pu32Brightness = u32RetNum;

    return s32Ret;
}

/**
 \brief 设置亮度
 \attention \n
无

 \param[in] u32Brightness, 亮度值,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetBrightness(HI_DRV_DISPLAY_E enChan, HI_U32 u32Brightness)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 Brightness = u32Brightness;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Brightness, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SD_BRIGHTNESS, &Brightness);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HD_BRIGHTNESS, &Brightness);
    }

    return s32Ret;
}


/**
 \brief 获取对比度
 \attention \n
无

 \param[in]
 \param[out] pu32Contrast 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetContrast(HI_DRV_DISPLAY_E enChan, HI_U32 *pu32Contrast)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RetNum = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Contrast);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SD_CONTRAST, &u32RetNum);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_HD_CONTRAST, &u32RetNum);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_CONTRAST Failure [%d]!\n", enChan);
        return s32Ret;
    }

    *pu32Contrast = u32RetNum;

    return s32Ret;
}

/**
 \brief 设置对比度
 \attention \n
无

 \param[in] u32Contrast, 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetContrast(HI_DRV_DISPLAY_E enChan, HI_U32 u32Contrast)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 Contrast = u32Contrast;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Contrast, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SD_CONTRAST, &Contrast);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HD_CONTRAST, &Contrast);
    }

    return s32Ret;
}

/**
 \brief 获取饱和度
 \attention \n
无

 \param[out] pu32Saturation：饱和度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetSaturation(HI_DRV_DISPLAY_E enChan, HI_U32 *pu32Saturation)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RetNum = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Saturation);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SD_SATURATION, &u32RetNum);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_HD_SATURATION, &u32RetNum);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_SATURATION Failure [%d]!\n", enChan);
        return s32Ret;
    }

    *pu32Saturation = u32RetNum;

    return s32Ret;
}

/**
 \brief 设置饱和度
 \attention \n
无

 \param[in] u32Saturation：饱和度,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSaturation(HI_DRV_DISPLAY_E enChan, HI_U32 u32Saturation)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 Saturation = u32Saturation;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Saturation, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SD_SATURATION, &Saturation);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HD_SATURATION, &Saturation);
    }

    return s32Ret;
}

/**
 \brief 获取色调
 \attention \n
无

 \param[in]
 \param[out] pu32Hue：色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetHue(HI_DRV_DISPLAY_E enChan, HI_U32 *pu32Hue)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RetNum = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Hue);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SD_HUE, &u32RetNum);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_HD_HUE, &u32RetNum);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_HUE Failure [%d]!\n", enChan);
        return s32Ret;
    }

    *pu32Hue = u32RetNum;

    return s32Ret;
}

/**
 \brief 设置色调
 \attention \n
无

 \param[in] u32Hue：色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetHue(HI_DRV_DISPLAY_E enChan, HI_U32 u32Hue)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 Hue = u32Hue;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Hue, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SD_HUE, &Hue);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HD_HUE, &Hue);
    }

    return s32Ret;
}

HI_S32 HI_MPI_PQ_SetHdrOffsetParam(HI_DRV_DISPLAY_E enChan, HI_PQ_SETHDROFFSET_S stSetHdrOffsetParam)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffsetParam.enHdrProcessScene, HI_PQ_HDR_MODE_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HDROFFSET_PARAM, &stSetHdrOffsetParam);

    return s32Ret;
}

/**
 \brief 设置色温
 \attention \n
无

 \param[in] stColorTemperature：色温, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetColorTemperature(HI_DRV_DISPLAY_E enChan, HI_PQ_COLORTEMPERATURE_S stColorTemperature)
{
    HI_S32 s32Ret = HI_SUCCESS;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(stColorTemperature.u32Red, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stColorTemperature.u32Green, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stColorTemperature.u32Blue, PQ_API_MAX_LEVEL);

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SD_TEMPERATURE, &stColorTemperature);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HD_TEMPERATURE, &stColorTemperature);
    }

    return s32Ret;
}

/**
 \brief 获取色温
 \attention \n
无

 \param[in]
 \param[out] pu32Hue：色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetColorTemperature(HI_DRV_DISPLAY_E enChan, HI_PQ_COLORTEMPERATURE_S *pstColorTemperature)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstColorTemperature);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SD_TEMPERATURE, pstColorTemperature);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_HD_TEMPERATURE, pstColorTemperature);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ GetColorTemperature Failure [%d]!\n", enChan);
        return s32Ret;
    }

    return s32Ret;
}

HI_S32 HI_MPI_PQ_SetBasicImageParam(HI_MPI_PQ_IMAGE_TYPE_E enType, HI_DRV_DISPLAY_E enChan, HI_PQ_IMAGE_PARAM_S stParam)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enType, HI_MPI_PQ_IMAGE_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_MPI_PQ_IMAGE_GRAPH == enType)
    {
        if (HI_DRV_DISPLAY_0 == enChan)
        {
            s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_GRAPH_SD_PARAM, &stParam);
        }
        else if (HI_DRV_DISPLAY_1 == enChan)
        {
            s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_GRAPH_HD_PARAM, &stParam);
        }
    }
    else if (HI_MPI_PQ_IMAGE_VIDEO == enType)
    {
        if (HI_DRV_DISPLAY_0 == enChan)
        {
            s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VIDEO_SD_PARAM, &stParam);
        }
        else if (HI_DRV_DISPLAY_1 == enChan)
        {
            s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VIDEO_HD_PARAM, &stParam);
        }
    }

    return s32Ret;
}

HI_S32 HI_MPI_PQ_GetBasicImageParam(HI_MPI_PQ_IMAGE_TYPE_E enType, HI_DRV_DISPLAY_E enChan, HI_PQ_IMAGE_PARAM_S *pstParam)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enType, HI_MPI_PQ_IMAGE_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pstParam);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_MPI_PQ_IMAGE_GRAPH == enType)
    {
        if (HI_DRV_DISPLAY_0 == enChan)
        {
            s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_GRAPH_SD_PARAM, pstParam);
        }
        else if (HI_DRV_DISPLAY_1 == enChan)
        {
            s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_GRAPH_HD_PARAM, pstParam);
        }
    }
    else if (HI_MPI_PQ_IMAGE_VIDEO == enType)
    {
        if (HI_DRV_DISPLAY_0 == enChan)
        {
            s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VIDEO_SD_PARAM, pstParam);
        }
        else if (HI_DRV_DISPLAY_1 == enChan)
        {
            s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VIDEO_HD_PARAM, pstParam);
        }
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ GetBasicImageParam Failure [%d] [%d]!\n", enType,enChan);
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 获取降噪强度
 \attention \n
无

 \param[out] pu32NRLevel: 降噪等级, 有效范围: 0~255


 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetTNR(HI_U32 *pu32NRLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pu32NRLevel);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR, pu32NRLevel);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_TNR Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 设置降噪强度
 \attention \n
无

 \param[in] u32TNRLevel: 降噪等级, 有效范围: 0~255

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNR(HI_U32 u32TNRLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NUM_OVER_RANGE(u32TNRLevel, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR, &u32TNRLevel);

    return s32Ret;
}

/**
 \brief 空域获取降噪强度
 \attention \n
无

 \param[out] pu32NRLevel: 降噪等级, 有效范围: 0~255


 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetSNR(HI_U32 *pu32NRLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pu32NRLevel);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SNR, pu32NRLevel);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_SNR Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 设置空域降噪强度
 \attention \n
无

 \param[in] u32SNRLevel: 降噪等级, 有效范围: 0~255

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSNR(HI_U32 u32SNRLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SNR, &u32SNRLevel);

    return s32Ret;
}

/**
 \brief 获取SR演示类型
 \attention \n
无

 \param[out] *penType


 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetSRMode(HI_PQ_SR_DEMO_E *penType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(penType);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SR_DEMO, penType);

    return s32Ret;
}

/**
 \brief 设置SR演示类型
 \attention \n
无

 \param[in] enType

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSRMode(HI_PQ_SR_DEMO_E enType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enType, HI_PQ_SR_DEMO_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SR_DEMO, &enType);

    return s32Ret;
}

/**
 \brief 获取清晰度
 \attention \n
无

 \param[out] pu32Sharpness：清晰度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetSharpness(HI_U32 *pu32Sharpness)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Num = 0;

    PQ_API_CHECK_NULL_PTR(pu32Sharpness);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SHARPNESS, &u32Num);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_SHARPNESS Failure !\n");
        return s32Ret;
    }

    *pu32Sharpness = u32Num;

    return s32Ret;
}

/**
 \brief 设置清晰度
 \attention \n
无

 \param[in] u32Sharpness：清晰度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSharpness(HI_U32 u32Sharpness)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Num = u32Sharpness;

    PQ_API_CHECK_NUM_OVER_RANGE(u32Sharpness, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SHARPNESS, &u32Num);

    return s32Ret;
}

/**
 \brief 获取块降噪De-blocking强度
 \attention \n
无

 \param[out] pu32DBlevel：降噪等级, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetDeBlocking(HI_U32 *pu32DBlevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pu32DBlevel);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DB, pu32DBlevel);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_DB Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 设置块降噪De-blocking强度
 \attention \n
无

 \param[in] u32DBlevel:降噪等级, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetDeBlocking(HI_U32 u32DBlevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NUM_OVER_RANGE(u32DBlevel, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DB, &u32DBlevel);

    return s32Ret;
}

HI_S32 HI_MPI_PQ_GetDeMosquito(HI_U32 *pu32DMlevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pu32DMlevel);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DM, pu32DMlevel);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_DM Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

HI_S32 HI_MPI_PQ_SetDeMosquito(HI_U32 u32DMlevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NUM_OVER_RANGE(u32DMlevel, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DM, &u32DMlevel);

    return s32Ret;
}


/**
 \brief 获取肤色增强
 \attention \n
  无

 \param[out] penFleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetFleshTone(HI_UNF_PQ_FLESHTONE_E *penFleshToneLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(penFleshToneLevel);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_FLESHTONE, penFleshToneLevel);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_FLESHTONE Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 设置肤色增强
 \attention \n
  无

 \param[in] enFleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetFleshTone( HI_UNF_PQ_FLESHTONE_E enFleshToneLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enFleshToneLevel, HI_UNF_PQ_FLESHTONE_GAIN_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_FLESHTONE, &enFleshToneLevel);

    return s32Ret;
}


/**
 \brief 设置颜色增强类型
 \attention \n
  无

 \param[in] enSixBaseColor

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetColorEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E enColorMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enColorMode, HI_PQ_COLOR_MODE_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_COLOR_ENHANCE_MODE, &enColorMode);

    return s32Ret;
}


/**
 \brief 获取颜色增强类型
 \attention \n
  无

 \param[in] enSixBaseColor

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetColorEnhanceMode(HI_UNF_PQ_COLOR_SPEC_MODE_E *penColorMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(penColorMode);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_COLOR_ENHANCE_MODE, penColorMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_COLOR_ENHANCE_MODE Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 获取六基色类型
 \attention \n
  无

 \param[out] pu32SixBaseColor

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetSixBaseColor(HI_UNF_PQ_SIX_BASE_S *pstSixBaseColor)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstSixBaseColor);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SIXBASECOLOR, pstSixBaseColor);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_SIXBASECOLOR Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 设置六基色类型
 \attention \n
  无

 \param[in] enSixBaseColor

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSixBaseColor(HI_PQ_SIX_BASE_COLOR_S *pstSixBaseColor)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstSixBaseColor);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SIXBASECOLOR, pstSixBaseColor);

    return s32Ret;
}

/**
 \brief 获取PQ模块开关
 \attention \n
  无

 \param[in] enFlags
 \param[in] pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetPQModule( HI_UNF_PQ_MODULE_E enFlags, HI_U32 *pu32OnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_MODULE_S stPQModule = {HI_PQ_MODULE_SHARPNESS, 0};

    PQ_API_CHECK_ENID_OVER_RANGE(enFlags, HI_UNF_PQ_MODULE_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32OnOff);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_UNF_PQ_MODULE_SHARPNESS == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SHARPNESS;
    }
    else if (HI_UNF_PQ_MODULE_DCI == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_DCI;
    }
    else if (HI_UNF_PQ_MODULE_COLOR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_COLOR;
    }
    else if (HI_UNF_PQ_MODULE_SR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SR;
    }
    else if (HI_UNF_PQ_MODULE_TNR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_TNR;
    }
    else if (HI_UNF_PQ_MODULE_SNR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SNR;
    }
    else if (HI_UNF_PQ_MODULE_DBM == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_DB;
    }
    else if (HI_UNF_PQ_MODULE_MCDI == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_DEI;
    }
    else if (HI_UNF_PQ_MODULE_ALL == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_ALL;
    }
    else
    {
        HI_ERR_PQ("PQ MODULE is error!\n");
        return HI_ERR_PQ_INVALID_PARA;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_MODULE, &stPQModule);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_MODULE Failure [%d]!\n", enFlags);
        return s32Ret;
    }

    *pu32OnOff = stPQModule.u32OnOff;

    return s32Ret;
}

/**
 \brief 设置PQ模块开关
 \attention \n
  无

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_E enFlags, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_MODULE_S stPQModule = {HI_PQ_MODULE_SHARPNESS, 0};

    PQ_API_CHECK_ENID_OVER_RANGE(enFlags, HI_UNF_PQ_MODULE_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (u32OnOff > 1)
    {
        HI_ERR_PQ("u32OnOff:%d illegal!\n", u32OnOff);
        return HI_ERR_PQ_INVALID_PARA;
    }

    stPQModule.u32OnOff = u32OnOff;

    if (HI_UNF_PQ_MODULE_SHARPNESS == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SHARPNESS;
    }
    else if (HI_UNF_PQ_MODULE_DCI == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_DCI;
    }
    else if (HI_UNF_PQ_MODULE_COLOR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_COLOR;
    }
    else if (HI_UNF_PQ_MODULE_SR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SR;
    }
    else if (HI_UNF_PQ_MODULE_TNR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_TNR;
    }
    else if (HI_UNF_PQ_MODULE_SNR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SNR;
    }
    else if (HI_UNF_PQ_MODULE_DBM == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_DB;
    }
    else if (HI_UNF_PQ_MODULE_MCDI == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_DEI;
    }
    else if (HI_UNF_PQ_MODULE_ALL == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_ALL;
    }
    else
    {
        HI_ERR_PQ("PQ MODULE is error!\n");
        return HI_ERR_PQ_INVALID_PARA;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_MODULE, &stPQModule);

    return s32Ret;
}

/**
 \brief 设置卖场模式开关
 \attention \n
无

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetDemo( HI_UNF_PQ_DEMO_E enFlags, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_DEMO_S stDemo;

    PQ_API_CHECK_ENID_OVER_RANGE(enFlags, HI_UNF_PQ_DEMO_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (1 == u32OnOff)
    {
        stDemo.bOnOff = HI_TRUE;
    }
    else if (0 == u32OnOff)
    {
        stDemo.bOnOff = HI_FALSE;
    }
    else
    {
        HI_ERR_PQ("u32OnOff:%d illegal!\n", u32OnOff);
        return HI_ERR_PQ_INVALID_PARA;
    }

    if (HI_UNF_PQ_DEMO_SHARPNESS == enFlags)
    {
        stDemo.enModule = HI_PQ_MODULE_SHARPNESS;
    }
    else if (HI_UNF_PQ_DEMO_DCI == enFlags)
    {
        stDemo.enModule = HI_PQ_MODULE_DCI;
    }
    else if (HI_UNF_PQ_DEMO_COLOR == enFlags)
    {
        stDemo.enModule = HI_PQ_MODULE_COLOR;
    }
    else if (HI_UNF_PQ_DEMO_SR == enFlags)
    {
        stDemo.enModule = HI_PQ_MODULE_SR;
    }
    else if (HI_UNF_PQ_DEMO_TNR == enFlags)
    {
        stDemo.enModule = HI_PQ_MODULE_TNR;
    }
    else if (HI_UNF_PQ_DEMO_SNR == enFlags)
    {
        stDemo.enModule = HI_PQ_MODULE_SNR;
    }
    else if (HI_UNF_PQ_DEMO_DEI == enFlags)
    {
        stDemo.enModule = HI_PQ_MODULE_DEI;
    }
    else if (HI_UNF_PQ_DEMO_DBM == enFlags)
    {
        stDemo.enModule = HI_PQ_MODULE_DB;
    }
    else if (HI_UNF_PQ_DEMO_ALL == enFlags)
    {
        stDemo.enModule = HI_PQ_MODULE_ALL;
    }
    else
    {
        HI_ERR_PQ("PQ DEMO is error!\n");
        return HI_ERR_PQ_INVALID_PARA;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DEMO, &stDemo);

    return s32Ret;
}

/**
 \brief 设置卖场模式显示方式
 \attention \n
无

 \param[in] enChan
 \param[in] enMode

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetDemoMode( HI_DRV_DISPLAY_E enChan, HI_PQ_DEMO_MODE_E enMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(enMode, HI_PQ_DEMO_MODE_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DEMO_MODE, &enMode);

    return s32Ret;
}

/**
 \brief 获取卖场模式显示方式
 \attention \n
无

 \param[in] enChan
 \param[in] penMode

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetDemoMode( HI_DRV_DISPLAY_E enChan, HI_PQ_DEMO_MODE_E *penMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_DRV_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(penMode);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DEMO_MODE, penMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_DEMO_MODE Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 为入网指标测试设置PQ 的默认值
 \attention \n
  无

 \param[in]  N/A

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetDefaultParam(HI_BOOL bDefault)
{
    HI_S32  s32Ret = HI_SUCCESS;
    HI_BOOL bOnOff = bDefault;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DEFAULT_PARAM, &bOnOff);

    return s32Ret;
}


/**
 \brief 获取DCI LEVEL
 \attention \n
  无

 \param[in] *pstDCITable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetDciLevel(HI_U32 *pu32DCIlevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pu32DCIlevel);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DCI_LEVEL, pu32DCIlevel);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_DCI_LEVEL Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 设置DCI LEVEL
 \attention \n
  无

 \param[in] *pstDCITable

 \retval ::HI_SUCCESS

 */


HI_S32 HI_MPI_PQ_SetDciLevel( HI_U32 u32DCIlevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NUM_OVER_RANGE(u32DCIlevel, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DCI_LEVEL, &u32DCIlevel);

    return s32Ret;
}

HI_S32 HI_MPI_PQ_SetDemoCoordinate(HI_U32 u32X)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NUM_OVER_RANGE(u32X, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DEMO_COORDINATE, &u32X);

    return s32Ret;
}

HI_S32 HI_MPI_PQ_GetDemoCoordinate(HI_U32 *pu32X)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pu32X);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DEMO_COORDINATE, pu32X);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_DEMO_COORDINATE Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

HI_S32 HI_MPI_PQ_SetImageMode(HI_UNF_PQ_IMAGE_MODE_E enImageMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_IMAGE_MODE_E enSetImageMode;

    PQ_API_CHECK_ENID_OVER_RANGE(enImageMode, HI_UNF_OPTION_MODE_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_UNF_OPTION_MODE_VIDEOPHONE == enImageMode)
    {
        enSetImageMode = HI_PQ_IMAGE_MODE_VIDEOPHONE;
    }
    else if (HI_UNF_OPTION_MODE_GALLERY == enImageMode)
    {
        enSetImageMode = HI_PQ_IMAGE_MODE_GALLERY;
    }
    else
    {
        enSetImageMode = HI_PQ_IMAGE_MODE_NORMAL;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_IMAGE_MODE, &enSetImageMode);

    return s32Ret;
}

HI_S32 HI_MPI_PQ_GetImageMode(HI_UNF_PQ_IMAGE_MODE_E *penImageMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_IMAGE_MODE_E enDrvImageMode = HI_PQ_IMAGE_MODE_NORMAL;

    PQ_API_CHECK_NULL_PTR(penImageMode);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_IMAGE_MODE, &enDrvImageMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_IMAGE_MODE Failure !\n");
        return s32Ret;
    }

    if (HI_PQ_IMAGE_MODE_VIDEOPHONE == enDrvImageMode)
    {
        *penImageMode = HI_UNF_OPTION_MODE_VIDEOPHONE;
    }
    else if (HI_PQ_IMAGE_MODE_GALLERY == enDrvImageMode)
    {
        *penImageMode = HI_UNF_OPTION_MODE_GALLERY;
    }
    else
    {
        *penImageMode = HI_UNF_OPTION_MODE_NORMAL;
    }

    return s32Ret;
}

/* ------------------------------------------------------------------------------------------- */

/**
 \brief 设置PQ寄存器
 \attention \n
无

 \param[in] u32RegAddr
 \param[in] u32Data

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_WritePQRegister(HI_U32 u32RegAddr, HI_U32 u32Data)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_REGISTER_S stRegister = {0};

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    stRegister.u32RegAddr   = u32RegAddr;
    stRegister.u32Value     = u32Data;

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_REGISTER, &stRegister);

    return s32Ret;
}

/**
 \brief 获取PQ寄存器
 \attention \n
无

 \param[in] u32RegAddr
 \param[in] *pu32Value

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_ReadPQRegister(HI_U32 u32RegAddr, HI_U32 *pu32Value)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_REGISTER_S stRegister = {0};

    PQ_API_CHECK_NULL_PTR(pu32Value);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    stRegister.u32RegAddr = u32RegAddr;

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_REGISTER, &stRegister);
    if (HI_FAILURE == s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_REGISTER Failure !\n");
        return s32Ret;
    }

    *pu32Value = stRegister.u32Value;

    return s32Ret;
}

/**
 \brief 获取ACM曲线
 \attention \n
  无

 \param[in] *pstGammaTable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetAcmTable( MPI_ACM_PARAM_S *pstColorTable)
{
    return HI_SUCCESS;
}

/**
 \brief 设置ACM曲线
 \attention \n
  无

 \param[in] *pstGammaTable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetAcmTable(HI_U32 u32RegAddr, MPI_ACM_PARAM_S *pstColorTable)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_ACM_LUT_S *pstAcmLut = HI_NULL;

    PQ_API_CHECK_NULL_PTR(pstColorTable);

    if (HI_FALSE == sg_bPQInitFlag)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    pstAcmLut = (HI_PQ_ACM_LUT_S *)HI_MALLOC(HI_ID_PQ, sizeof(HI_PQ_ACM_LUT_S));
    if (HI_NULL == pstAcmLut)
    {
        HI_ERR_PQ("%s:pstAcmLut is Null poniter!\n", __FUNCTION__);
        return HI_ERR_PQ_NULL_PTR;
    }
    pstAcmLut->u32LutType = u32RegAddr;

    memcpy(pstAcmLut->as16Lut, pstColorTable->as16Luma, sizeof(pstAcmLut->as16Lut));
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_ACM_LUMA, pstAcmLut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_S_ACM_LUMA Failure !\n");
        HI_FREE(HI_ID_PQ, pstAcmLut);
        return s32Ret;
    }

    memcpy(pstAcmLut->as16Lut, pstColorTable->as16Hue, sizeof(pstAcmLut->as16Lut));
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_ACM_HUE, pstAcmLut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_S_ACM_HUE Failure !\n");
        HI_FREE(HI_ID_PQ, pstAcmLut);
        return s32Ret;
    }

    memcpy(pstAcmLut->as16Lut, pstColorTable->as16Sat, sizeof(pstAcmLut->as16Lut));
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_ACM_SAT, pstAcmLut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_S_ACM_SAT Failure !\n");
        HI_FREE(HI_ID_PQ, pstAcmLut);
        return s32Ret;
    }

    HI_FREE(HI_ID_PQ, pstAcmLut);

    return s32Ret;
}

/**
 \brief 获取DCI曲线
 \attention \n
  无

 \param[in] *pstDCITable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetDciTable( HI_PQ_DCI_WGT_S *pstDCITable)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstDCITable);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DCI, (HI_PQ_DCI_WGT_S *)pstDCITable);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_DCI Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

/**
 \brief 设置DCI曲线
 \attention \n
  无

 \param[in] *pstDCITable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetDciTable( HI_PQ_DCI_WGT_S *pstDCITable)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstDCITable);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DCI, (HI_PQ_DCI_WGT_S *)pstDCITable);

    return s32Ret;
}

/**
 \brief 获取DCI直方图
 \attention \n
  无

 \param[in] *pstDCIHistgram

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetHistgram( HI_PQ_DCI_HISTGRAM_S *pstDCIHistgram)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstDCIHistgram);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DCI_HIST, (HI_PQ_DCI_HISTGRAM_S *)pstDCIHistgram);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_DCI_HIST Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}


/**
 \brief 获取TNR的亮度PixMean-to-Ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRLumaPixMean2Ratio( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_Y_PIXMEAN_2_RATIO, (HI_PQ_TNR_S *)pstTnrData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_TNR_Y_PIXMEAN_2_RATIO Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}
/**
 \brief 设置TNR的亮度PixMean-to-Ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRLumaPixMean2Ratio( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_Y_PIXMEAN_2_RATIO, (HI_PQ_TNR_S *)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取TNR的色度PixMean-to-Ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRChromPixMean2Ratio( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_C_PIXMEAN_2_RATIO, (HI_PQ_TNR_S *)pstTnrData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_TNR_C_PIXMEAN_2_RATIO Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}
/**
 \brief 设置TNR的色度PixMean-to-Ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRChromPixMean2Ratio( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_C_PIXMEAN_2_RATIO, (HI_PQ_TNR_S *)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取TNR的亮度MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRLumaMotionMapping( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_Y_MOTION_MAPPING, (HI_PQ_TNR_S *)pstTnrData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_TNR_Y_MOTION_MAPPING Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}
/**
 \brief 设置TNR的亮度MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRLumaMotionMapping( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_Y_MOTION_MAPPING, (HI_PQ_TNR_S *)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取TNR的色度MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRChromMotionMapping( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_C_MOTION_MAPPING, (HI_PQ_TNR_S *)pstTnrData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_TNR_C_MOTION_MAPPING Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}
/**
 \brief 设置TNR的色度MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRChromMotionMapping( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_C_MOTION_MAPPING, (HI_PQ_TNR_S *)pstTnrData);

    return s32Ret;
}

HI_S32 HI_MPI_PQ_GetTNRFMotionMapping(HI_PQ_TNR_FMOTION_S *pstTnrFMotion)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrFMotion);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_FMOTION_MAPPING, (HI_PQ_TNR_FMOTION_S *)pstTnrFMotion);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_TNR_FMOTION_MAPPING Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}

HI_S32 HI_MPI_PQ_SetTNRFMotionMapping(HI_PQ_TNR_FMOTION_S *pstTnrFMotion)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrFMotion);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_FMOTION_MAPPING, (HI_PQ_TNR_FMOTION_S *)pstTnrFMotion);

    return s32Ret;
}

/**
 \brief 获取TNR的亮度FINAL MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRLumaFinalMotionMapping( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_Y_FINAL_MOTION_MAPPING, (HI_PQ_TNR_S *)pstTnrData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_TNR_Y_FINAL_MOTION_MAPPING Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}
/**
 \brief 设置TNR的亮度FINAL MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRLumaFinalMotionMapping( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_Y_FINAL_MOTION_MAPPING, (HI_PQ_TNR_S *)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取TNR的色度FINAL MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRChromFinalMotionMapping( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_C_FINAL_MOTION_MAPPING, (HI_PQ_TNR_S *)pstTnrData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_TNR_C_FINAL_MOTION_MAPPING Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}
/**
 \brief 设置TNR的色度FINAL MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRChromFinalMotionMapping( HI_PQ_TNR_S *pstTnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstTnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_C_FINAL_MOTION_MAPPING, (HI_PQ_TNR_S *)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取SNR的pixmean-ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetSNRPixmean2Ratio( HI_PQ_SNR_PIXMEAN_2_RATIO_S *pstSnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstSnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SNR_PIXMEAN_2_RATIO, (HI_PQ_SNR_PIXMEAN_2_RATIO_S *)pstSnrData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_SNR_PIXMEAN_2_RATIO Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}
/**
 \brief 设置SNR的pixmean-ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSNRPixmean2Ratio( HI_PQ_SNR_PIXMEAN_2_RATIO_S *pstSnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstSnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SNR_PIXMEAN_2_RATIO, (HI_PQ_SNR_PIXMEAN_2_RATIO_S *)pstSnrData);

    return s32Ret;
}

/**
 \brief 获取SNR的pixdiff-edgestr曲线
 \attention \n
  无

 \param[in] *pstSnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetSNRPixdiff2Edgestr( HI_PQ_SNR_PIXDIFF_2_EDGESTR_S *pstSnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstSnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SNR_PIXDIFF_2_EDGESTR, (HI_PQ_SNR_PIXDIFF_2_EDGESTR_S *)pstSnrData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_SNR_PIXDIFF_2_EDGESTR Failure !\n");
        return s32Ret;
    }

    return s32Ret;
}
/**
 \brief 设置SNR的pixdiff-edgestr曲线
 \attention \n
  无

 \param[in] *pstSnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSNRPixdiff2Edgestr( HI_PQ_SNR_PIXDIFF_2_EDGESTR_S *pstSnrData)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pstSnrData);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SNR_PIXDIFF_2_EDGESTR, (HI_PQ_SNR_PIXDIFF_2_EDGESTR_S *)pstSnrData);

    return s32Ret;
}


/**
 \brief 获取亮度
 \attention \n
无

 \param[in] pu32Brightness 亮度值,有效范围: 0~100;
 \param[out]

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetVPBrightness(HI_DRV_PQ_VP_TYPE_E enDrvVPType, HI_U32 *pu32Brightness)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RetNum = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enDrvVPType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Brightness);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_PREVIEW_BRIGHTNESS, &u32RetNum);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_REMOTE_BRIGHTNESS, &u32RetNum);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_VP_BRIGHTNESS Failure [%d]!\n", enDrvVPType);
        return s32Ret;
    }

    *pu32Brightness = u32RetNum;

    return s32Ret;
}

/**
 \brief 设置亮度
 \attention \n
无

 \param[in] u32Brightness, 亮度值,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetVPBrightness(HI_DRV_PQ_VP_TYPE_E enDrvVPType, HI_U32 u32Brightness)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 Brightness = u32Brightness;

    PQ_API_CHECK_ENID_OVER_RANGE(enDrvVPType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Brightness, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_PREVIEW_BRIGHTNESS, &Brightness);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_REMOTE_BRIGHTNESS, &Brightness);
    }

    return s32Ret;
}


/**
 \brief 获取对比度
 \attention \n
无

 \param[in]
 \param[out] pu32Contrast 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetVPContrast(HI_DRV_PQ_VP_TYPE_E enDrvVPType, HI_U32 *pu32Contrast)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RetNum = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enDrvVPType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Contrast);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_PREVIEW_CONTRAST, &u32RetNum);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_REMOTE_CONTRAST, &u32RetNum);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_VP_CONTRAST Failure [%d]!\n", enDrvVPType);
        return s32Ret;
    }

    *pu32Contrast = u32RetNum;

    return s32Ret;
}

/**
 \brief 设置对比度
 \attention \n
无

 \param[in] u32Contrast, 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetVPContrast(HI_DRV_PQ_VP_TYPE_E enDrvVPType, HI_U32 u32Contrast)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 Contrast = u32Contrast;

    PQ_API_CHECK_ENID_OVER_RANGE(enDrvVPType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Contrast, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_PREVIEW_CONTRAST, &Contrast);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_REMOTE_CONTRAST, &Contrast);
    }

    return s32Ret;
}

/**
 \brief 获取饱和度
 \attention \n
无

 \param[out] pu32Saturation：饱和度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetVPSaturation(HI_DRV_PQ_VP_TYPE_E enDrvVPType, HI_U32 *pu32Saturation)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RetNum = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enDrvVPType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Saturation);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_PREVIEW_SATURATION, &u32RetNum);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_REMOTE_SATURATION, &u32RetNum);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_VP_SATURATION Failure [%d]!\n", enDrvVPType);
        return s32Ret;
    }

    *pu32Saturation = u32RetNum;

    return s32Ret;
}

/**
 \brief 设置饱和度
 \attention \n
无

 \param[in] u32Saturation：饱和度,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetVPSaturation(HI_DRV_PQ_VP_TYPE_E enDrvVPType, HI_U32 u32Saturation)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 Saturation = u32Saturation;

    PQ_API_CHECK_ENID_OVER_RANGE(enDrvVPType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Saturation, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_PREVIEW_SATURATION, &Saturation);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_REMOTE_SATURATION, &Saturation);
    }

    return s32Ret;
}

/**
 \brief 获取色调
 \attention \n
无

 \param[in]
 \param[out] pu32Hue：色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetVPHue(HI_DRV_PQ_VP_TYPE_E enDrvVPType, HI_U32 *pu32Hue)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RetNum = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enDrvVPType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Hue);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_PREVIEW_HUE, &u32RetNum);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_REMOTE_HUE, &u32RetNum);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("PQ HIIOC_PQ_G_VP_HUE Failure [%d]!\n", enDrvVPType);
        return s32Ret;
    }

    *pu32Hue = u32RetNum;

    return s32Ret;
}

/**
 \brief 设置色调
 \attention \n
无

 \param[in] u32Hue：色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetVPHue(HI_DRV_PQ_VP_TYPE_E enDrvVPType, HI_U32 u32Hue)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 Hue = u32Hue;

    PQ_API_CHECK_ENID_OVER_RANGE(enDrvVPType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Hue, PQ_API_MAX_LEVEL);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_PREVIEW_HUE, &Hue);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enDrvVPType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_REMOTE_HUE, &Hue);
    }

    return s32Ret;
}


HI_S32 HI_MPI_PQ_SetVPMode(HI_DRV_PQ_VP_TYPE_E enVPImageType, HI_DRV_PQ_VP_MODE_E enVPImageMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enVPImageType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(enVPImageMode, HI_DRV_PQ_VIDEOPHONE_MODE_BUTT);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enVPImageType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_PREVIEW_IMAGE_MODE, &enVPImageMode);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enVPImageType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_VP_REMOTE_IMAGE_MODE, &enVPImageMode);
    }

    return s32Ret;
}

HI_S32 HI_MPI_PQ_GetVPMode(HI_DRV_PQ_VP_TYPE_E enVPImageType, HI_DRV_PQ_VP_MODE_E *penVPImageMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enVPImageType, HI_DRV_PQ_VP_TYPE_BUTT);
    PQ_API_CHECK_NULL_PTR(penVPImageMode);

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!\n");
        return HI_ERR_PQ_NO_INIT;
    }

    if (HI_DRV_PQ_VP_TYPE_PREVIEW == enVPImageType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_PREVIEW_IMAGE_MODE, penVPImageMode);
    }
    else if (HI_DRV_PQ_VP_TYPE_REMOTE == enVPImageType)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_VP_REMOTE_IMAGE_MODE, penVPImageMode);
    }

    return s32Ret;
}

HI_S32 HI_MPI_PQ_SetMcdiSplitMode(HI_U32 u32HandleNo, HI_U32 u32SplitMode)
{
    HI_S32 s32Ret = HI_SUCCESS;
    PQ_API_CHECK_NUM_OVER_RANGE(u32HandleNo, 0);
    PQ_API_CHECK_NUM_OVER_RANGE(u32SplitMode, 5);

    if (HI_FALSE == sg_bPQInitFlag)
    {
        HI_ERR_PQ("PQ not init !\n");
        return HI_ERR_PQ_NO_INIT;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_MCDI_SPLIT_MODE, &u32SplitMode);

    return s32Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
