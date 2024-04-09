/*************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name        : hi_gfx2d_api.c
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :


History          :
Date                  Author                Modification
2018/01/01            sdk                   Created file
**************************************************************************************************/

/*********************************add include here************************************************/
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "hi_gfx2d_api.h"
#include "hi_gfx2d_errcode.h"
#include "drv_gfx2d_ioctl.h"


/***************************** Macro Definition **************************************************/


/*************************** Structure Definition ************************************************/

/********************** Global Variable declaration **********************************************/

/* device path */
static const HI_CHAR *gs_pszGFX2DDevPath = "/dev/hi_gfx2d";

/* device lock */
static pthread_mutex_t gs_GFX2DDevMutex = PTHREAD_MUTEX_INITIALIZER;

/* device description symbol */
static HI_S32 gs_s32GFX2DDevFd = -1;

/* device quoted count */
static HI_U32 gs_u32GFX2DDevRef = 0;

/* check dev id is invalid or not */
#define GFX2D_CHECK_DEVID(enDevId) do \
    {\
        if (enDevId >= HI_GFX2D_DEV_ID_BUTT)\
        {\
            return HI_ERR_GFX2D_INVALID_DEVID;\
        }\
    }while(0)

/* check dev is opened or not */
#define GFX2D_CHECK_DEVSTATE() do \
    {\
        if (-1 == gs_s32GFX2DDevFd)\
        {\
            return HI_ERR_GFX2D_DEV_NOT_OPEN; \
        } \
    } while (0)

/******************************* API forward declarations ****************************************/


/******************************* API realization *************************************************/

HI_S32 HI_GFX2D_Open(const HI_GFX2D_DEV_ID_E enDevId)
{
    HI_S32 s32Ret = HI_SUCCESS;

    GFX2D_CHECK_DEVID(enDevId);

    s32Ret = pthread_mutex_lock(&gs_GFX2DDevMutex);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_ERR_GFX2D_SYS;
    }

    if (0xffffffff == gs_u32GFX2DDevRef)
    {
        s32Ret = HI_ERR_GFX2D_SYS;
        goto GFX2D_EXIT;
    }

    /* device opened, return afrer adding ref */
    if (gs_s32GFX2DDevFd != -1)
    {
        gs_u32GFX2DDevRef++;
        goto GFX2D_EXIT;
    }

    gs_s32GFX2DDevFd = open(gs_pszGFX2DDevPath, O_RDWR, S_IRUSR);
    if (gs_s32GFX2DDevFd < 0)
    {
        s32Ret = HI_ERR_GFX2D_DEV_PERMISSION;
        goto GFX2D_EXIT;
    }

    gs_u32GFX2DDevRef++;

GFX2D_EXIT:
    if (pthread_mutex_unlock(&gs_GFX2DDevMutex) != HI_SUCCESS)
    {
        return HI_ERR_GFX2D_SYS;
    }

    return s32Ret;
}

HI_S32 HI_GFX2D_Close(const HI_GFX2D_DEV_ID_E enDevId)
{
    HI_S32 s32Ret = HI_SUCCESS;
    GFX2D_WAITALLDONE_CMD_S stCmd;

    s32Ret = pthread_mutex_lock(&gs_GFX2DDevMutex);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_ERR_GFX2D_SYS;
    }

    /* device is not open,return */
    if ((gs_s32GFX2DDevFd < 0) || (gs_u32GFX2DDevRef == 0))
    {
        goto GFX2D_EXIT;
    }

    if (--gs_u32GFX2DDevRef > 0)
    {
        goto GFX2D_EXIT;
    }

    memset(&stCmd, 0, sizeof(stCmd));

    /*Before close dev, wait all task done!*/
    stCmd.enDevId = enDevId;
    s32Ret = ioctl(gs_s32GFX2DDevFd, GFX2D_WAITALLDONE, &stCmd);

    close(gs_s32GFX2DDevFd);

    gs_s32GFX2DDevFd = -1;

GFX2D_EXIT:
    if (pthread_mutex_unlock(&gs_GFX2DDevMutex) != HI_SUCCESS)
    {
        return HI_ERR_GFX2D_SYS;
    }

    return s32Ret;
}

/*缩放时，输入宽度，高度大于等于2.*/
HI_S32 HI_GFX2D_ComposeSync(const HI_GFX2D_DEV_ID_E enDevId,
                            HI_GFX2D_COMPOSE_LIST_S *pstComposeList,
                            HI_GFX2D_SURFACE_S *pstDst,
                            const HI_U32 u32Timeout)
{
    HI_S32 s32Ret = HI_FAILURE;
    GFX2D_COMPOSE_CMD_S stCmd;

    GFX2D_CHECK_DEVID(enDevId);

    GFX2D_CHECK_DEVSTATE();

    if ((NULL == pstComposeList) || (NULL == pstDst) || (NULL == pstComposeList->pstCompose))
    {
        return HI_ERR_GFX2D_NULL_PTR;
    }

    if (u32Timeout > 10000)
    {
        return HI_ERR_GFX2D_TIMEOUT;
    }

    memset(&stCmd, 0, sizeof(stCmd));

    stCmd.enDevId        = enDevId;
    stCmd.stDst          = *pstDst;
    stCmd.u32Timeout     = u32Timeout;
    stCmd.bSync          = HI_TRUE;

    stCmd.stComposeList.u32BgColor    = pstComposeList->u32BgColor;
    stCmd.stComposeList.u32ComposeCnt = pstComposeList->u32ComposeCnt;
    stCmd.stComposeList.u64Compose = (HI_U64)(unsigned long)pstComposeList->pstCompose;

    s32Ret = ioctl(gs_s32GFX2DDevFd, GFX2D_COMPOSE, &stCmd);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    pstDst->s32ReleaseFenceFd = stCmd.stDst.s32ReleaseFenceFd;
    memcpy(&(pstDst->ExtInfo), &(stCmd.stDst.ExtInfo), sizeof(HI_GFX2D_EXTINFO_S));

    return HI_SUCCESS;

}

HI_S32 HI_GFX2D_ComposeAsync(const HI_GFX2D_DEV_ID_E enDevId,
                             HI_GFX2D_COMPOSE_LIST_S *pstComposeList,
                             HI_GFX2D_SURFACE_S *pstDst)
{
    HI_S32 s32Ret = HI_FAILURE;
    GFX2D_COMPOSE_CMD_S stCmd;
#ifdef GFX2D_FENCE_SUPPORT
    HI_U32 i = 0;
#endif

    GFX2D_CHECK_DEVID(enDevId);

    GFX2D_CHECK_DEVSTATE();

    if ((NULL == pstComposeList) || (NULL == pstDst) || (NULL == pstComposeList->pstCompose))
    {
        return HI_ERR_GFX2D_NULL_PTR;
    }

    memset(&stCmd, 0, sizeof(stCmd));

    stCmd.enDevId   = enDevId;
    stCmd.stDst     = *pstDst;
    stCmd.bSync     = HI_FALSE;

    stCmd.stComposeList.u32BgColor    = pstComposeList->u32BgColor;
    stCmd.stComposeList.u32ComposeCnt = pstComposeList->u32ComposeCnt;
    stCmd.stComposeList.u64Compose = (HI_U64)(unsigned long)pstComposeList->pstCompose;

    s32Ret = ioctl(gs_s32GFX2DDevFd, GFX2D_COMPOSE, &stCmd);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    pstDst->s32ReleaseFenceFd = stCmd.stDst.s32ReleaseFenceFd;
    memcpy(&(pstDst->ExtInfo), &(stCmd.stDst.ExtInfo), sizeof(HI_GFX2D_EXTINFO_S));

#ifdef GFX2D_FENCE_SUPPORT
    if (pstComposeList->u32ComposeCnt >= 7)
    {
        return HI_ERR_GFX2D_TIMEOUT;
    }
    for (i = 0; i < pstComposeList->u32ComposeCnt; i++)
    {
        pstComposeList->pstCompose[i].stSurface.s32ReleaseFenceFd = dup(pstDst->s32ReleaseFenceFd);
        if (pstComposeList->pstCompose[i].stSurface.s32ReleaseFenceFd < 0)
        {
            return HI_ERR_GFX2D_SYS;
        }
    }
#endif

    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_WaitAllDone(const HI_GFX2D_DEV_ID_E enDevId, const HI_U32 u32TimeOut)
{
    HI_S32 s32Ret = HI_FAILURE;
    GFX2D_WAITALLDONE_CMD_S stCmd;

    GFX2D_CHECK_DEVID(enDevId);

    GFX2D_CHECK_DEVSTATE();

    memset(&stCmd, 0, sizeof(stCmd));

    stCmd.enDevId = enDevId;
    stCmd.u32Timeout = u32TimeOut;
    if (u32TimeOut > 10000)
    {
        return HI_ERR_GFX2D_TIMEOUT;
    }

    s32Ret = ioctl(gs_s32GFX2DDevFd, GFX2D_WAITALLDONE, &stCmd);
    if (s32Ret != HI_SUCCESS)
    {
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_GetCmpSurfaceSize(const HI_GFX2D_DEV_ID_E enDevId,
                                  const HI_U32 u32Width, const HI_U32 u32Height,
                                  const HI_GFX2D_FMT_E enFmt, HI_U32 *pu32Size)
{
    HI_U32 u32Stride = 0;

    GFX2D_CHECK_DEVID(enDevId);

    GFX2D_CHECK_DEVSTATE();

    if (HI_NULL == pu32Size)
    {
        return HI_ERR_GFX2D_NULL_PTR;
    }

    if (HI_GFX2D_FMT_ARGB8888 != enFmt)
    {
        return HI_ERR_GFX2D_UNSUPPORT;
    }

    if (   (u32Width < 1) || (u32Width > 2560)
        || (u32Height < 1) || (u32Height > 1600))
    {
        return HI_ERR_GFX2D_INVALID_SURFACE_RESO;
    }

    if (u32Width & 0x1)
    {
        return HI_ERR_GFX2D_UNSUPPORT;
    }

#if HWC_VERSION >= 0x500
    u32Stride = ((u32Width * 2 + 0xff) & 0xffffff00);   //256 byte align

    u32Stride = (u32Stride % 512) ? u32Stride : (u32Stride + 256);  //256 * odd

    *pu32Size = ((16 * u32Height + 0xff) & 0xffffff00) * 2 + (u32Stride * u32Height) * 2;    //512 byte : compress head
#elif HWC_VERSION == 0x400
    u32Stride = (((HI_U32)((u32Width * 4) * 1.3) + 0xf) & 0xfffffff0);
    if (u32Stride < 320)
    {
        u32Stride = 320;
    }

    *pu32Size = u32Stride * u32Height;
#else
    u32Stride = ((u32Width * 2 + 0xff) & 0xffffff00);

    *pu32Size = u32Stride * u32Height  + ((u32Stride / 256 + 0xf) & 0xfffffff0) * u32Height;
    *pu32Size *= 2;

#endif

    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_GetCmpSurfaceStride(const HI_GFX2D_DEV_ID_E enDevId,
                                    const HI_U32 u32Width, const HI_GFX2D_FMT_E enFmt,
                                    HI_U32 *pu32Stride)
{
    GFX2D_CHECK_DEVID(enDevId);

    GFX2D_CHECK_DEVSTATE();

    if (HI_NULL == pu32Stride)
    {
        return HI_ERR_GFX2D_NULL_PTR;
    }

    if (HI_GFX2D_FMT_ARGB8888 != enFmt)
    {
        return HI_ERR_GFX2D_UNSUPPORT;
    }

    if ((u32Width < 1) || (u32Width > 2560))
    {
        return HI_ERR_GFX2D_INVALID_SURFACE_RESO;
    }

    if (u32Width & 0x1)
    {
        return HI_ERR_GFX2D_UNSUPPORT;
    }

#if HWC_VERSION >= 0x500
    *pu32Stride = ((u32Width * 2 + 0xff) & 0xffffff00);   //256 byte align

    *pu32Stride = (*pu32Stride % 512) ? *pu32Stride : (*pu32Stride + 256);  //256 * odd
#elif HWC_VERSION == 0x400
    *pu32Stride = (((HI_U32)((u32Width * 4) * 1.3) + 0xf) & 0xfffffff0);
    if (*pu32Stride < 320)
    {
        *pu32Stride = 320;
    }
#else
    *pu32Stride = ((u32Width * 2 + 0xff) & 0xffffff00);
#endif

    return HI_SUCCESS;
}
