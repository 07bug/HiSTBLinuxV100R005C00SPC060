/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : mjpeg.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2012/12/03
  Description   :
  History       :
  1.Date        : 2012/12/03
    Author      : sdk
    Modification: Created file

******************************************************************************/

/******************************* Include Files *******************************/

/* Sys headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <pthread.h>

/* Other headers */
#include "hi_type.h"
#include "hi_module.h"
#include "hi_debug.h"
#include "hi_codec.h"
#include "drv_vdec_ioctl.h"
#include "hi_mpi_stat.h"

/* jpeg dec headers */
#include "jpeglib.h"
#include "hi_jpeg_api.h"

/****************************** Macro Definition *****************************/
#define HI_MJPEG_MAX_CHANNEL (HI_VDEC_MAX_INSTANCE_NEW)
#define HI_MJPEG_OUTPUT_SEMIPLANAR_444 (1)
#define MJPEG_INST_HANDLE(hInst) (hInst & 0xff)

#define MJPEG_FHD_WIDTH  1920
#define MJEG_FHD_HEIGHT  1088

#define HI_ERR_CODEC(fmt...) \
    HI_ERR_PRINT(HI_ID_VDEC, fmt)
#define HI_WARN_CODEC(fmt...) \
    HI_WARN_PRINT(HI_ID_VDEC, fmt)
#define HI_INFO_CODEC(fmt...) \
    HI_INFO_PRINT(HI_ID_VDEC, fmt)

//#define JPEG_DEC_CAPA_ENABLE
//#define JPEG_DEBUG_ENABLE
#if defined(JPEG_DEBUG_ENABLE) || defined(JPEG_DEC_CAPA_ENABLE)
#include <sys/time.h>
#include "utils/Log.h"

#define LOG_TAG "libhi_msp"

#define DEC_TINIT()   struct timeval tv_start, tv_end; unsigned int time_cost,line_start
#define DEC_TSTART()  gettimeofday(&tv_start, NULL);line_start = __LINE__
#define DEC_TEND()    \
    gettimeofday(&tv_end, NULL); \
    time_cost = ((tv_end.tv_usec - tv_start.tv_usec)/1000 + (tv_end.tv_sec - tv_start.tv_sec)*1000); \
    ALOGE("=============================================================================\n"); \
    ALOGE("FROM LINE: %d TO LINE: %d COST: %d ms\n",line_start, __LINE__, time_cost);         \
    ALOGE("=============================================================================\n")
#endif
/************************ Static Structure Definition ************************/

typedef struct
{
    HI_BOOL bUsed;
    HI_U32 u32Width;
    HI_U32 u32Height;
    HI_ULONG DecHandle;
    struct jpeg_decompress_struct stInfo;
} HI_MJPEG_PARAM_S;

/***************************** Global Definition *****************************/

HI_U32 g_lowDelayFrameIndex[HI_VDEC_MAX_INSTANCE_NEW];
extern HI_U32 g_lowDelayVdecHandle[HI_VDEC_MAX_INSTANCE_NEW];
extern HI_U32 g_lowDelayLinePhyAddr[HI_VDEC_MAX_INSTANCE_NEW];
extern HI_U64 g_lowDelayLineVirAddr[HI_VDEC_MAX_INSTANCE_NEW];

/***************************** Static Definition *****************************/

HI_S32 MJPEG_GetCap(HI_CODEC_CAP_S *pstCodecCap);
HI_S32 MJPEG_Create(HI_HANDLE *phInst, const HI_CODEC_OPENPARAM_S *pstParam);
HI_S32 MJPEG_Destroy(HI_HANDLE hInst);
HI_S32 MJPEG_SetAttr(HI_HANDLE hInst, const HI_CODEC_ATTR_S *pstAttr);
HI_S32 MJPEG_GetAttr(HI_HANDLE hInst, HI_CODEC_ATTR_S *pstAttr);
HI_S32 MJPEG_DecodeFrame(HI_HANDLE hInst, HI_CODEC_STREAM_S *pstIn, HI_CODEC_FRAME_S *pstOut);
HI_S32 MJPEG_GetStreamInfo(HI_HANDLE hInst, HI_CODEC_STREAMINFO_S *pstStreamInfo);
HI_S32 MJPEG_StopDecodeFrame(HI_HANDLE hInst);

static HI_MJPEG_PARAM_S s_stMjpegParam[HI_MJPEG_MAX_CHANNEL];
static pthread_mutex_t  s_stMjpegMutex = PTHREAD_MUTEX_INITIALIZER;        /* Mutex */

static HI_CODEC_SUPPORT_S s_stCodecSupport =
{
    .u32Type        = HI_CODEC_TYPE_DEC,
    .enID           = HI_CODEC_ID_VIDEO_MJPEG,
    .pstNext        = HI_NULL
};

static HI_CODEC_S hi_codec_entry =
{
    .pszName        = "MJPEG",
    .unVersion        = {.stVersion = {1, 0, 0, 0}},
    .pszDescription = "Hisilicon MJPEG codec",

    .GetCap            = MJPEG_GetCap,
    .Create            = MJPEG_Create,
    .Destroy        = MJPEG_Destroy,
    .Start            = HI_NULL,
    .Stop            = HI_NULL,
    .Reset            = HI_NULL,
    .SetAttr        = MJPEG_SetAttr,
    .GetAttr        = MJPEG_GetAttr,
    .DecodeFrame    = MJPEG_DecodeFrame,
    .EncodeFrame    = HI_NULL,
    .GetStreamInfo    = MJPEG_GetStreamInfo,
    .Control        = HI_NULL,
};

/*********************************** Code ************************************/

HI_CODEC_S *VDEC_MJPEG_Codec(HI_VOID)
{
    return &hi_codec_entry;
}

HI_S32 MJPEG_GetCap(HI_CODEC_CAP_S *pstCodecCap)
{
    if (HI_NULL == pstCodecCap)
    {
        return HI_ERR_CODEC_INVALIDPARAM;
    }

    pstCodecCap->u32CapNumber = HI_CODEC_CAP_DRIVENOUTSIDE | HI_CODEC_CAP_OUTPUT2SPECADDR;
    pstCodecCap->pstSupport = &s_stCodecSupport;
    HI_INFO_CODEC("MJPEG_GetCap success.\n");
    return HI_SUCCESS;
}

HI_S32 MJPEG_Create(HI_HANDLE *phInst, const HI_CODEC_OPENPARAM_S *pstParam)
{
    HI_S32 i;

    if (HI_NULL == phInst)
    {
        return HI_ERR_CODEC_INVALIDPARAM;
    }

    VDEC_LOCK(s_stMjpegMutex);

    i = MJPEG_INST_HANDLE(*phInst);

    if (!s_stMjpegParam[i].bUsed)
    {
        s_stMjpegParam[i].u32Width = 0;
        s_stMjpegParam[i].u32Height = 0;
        s_stMjpegParam[i].bUsed = HI_TRUE;
        VDEC_UNLOCK(s_stMjpegMutex);
        *phInst = (HI_HANDLE)i;
        HI_INFO_CODEC("MJPEG_Create success.");
        return HI_SUCCESS;
    }

    for (i = 0; i < HI_MJPEG_MAX_CHANNEL; i++)
    {
        if (!s_stMjpegParam[i].bUsed)
        {
            s_stMjpegParam[i].u32Width = 0;
            s_stMjpegParam[i].u32Height = 0;
            s_stMjpegParam[i].bUsed = HI_TRUE;
            VDEC_UNLOCK(s_stMjpegMutex);
            *phInst = (HI_HANDLE)i;
            HI_INFO_CODEC("MJPEG_Create success.\n");
            return HI_SUCCESS;
        }
    }

    VDEC_UNLOCK(s_stMjpegMutex);

    return HI_ERR_CODEC_NOENOUGHRES;
}

HI_S32 MJPEG_Destroy(HI_HANDLE hInst)
{
    if (hInst < HI_MJPEG_MAX_CHANNEL)
    {
        VDEC_LOCK(s_stMjpegMutex);
        s_stMjpegParam[hInst].bUsed = HI_FALSE;
        VDEC_UNLOCK(s_stMjpegMutex);
        HI_INFO_CODEC("MJPEG_Destroy success.\n");
    }

    if (((hInst & 0xff) < HI_VDEC_MAX_INSTANCE_NEW) && ((hInst & 0xff) > 0))
    {
        g_lowDelayFrameIndex[(hInst & 0xff)] = 0;
    }

    return HI_SUCCESS;
}

HI_S32 MJPEG_SetAttr(HI_HANDLE hInst, const HI_CODEC_ATTR_S *pstAttr)
{
    HI_INFO_CODEC("MJPEG_SetAttr success.\n");
    return HI_SUCCESS;
}

HI_S32 MJPEG_GetAttr(HI_HANDLE hInst, HI_CODEC_ATTR_S *pstAttr)
{
    if ((hInst >= HI_MJPEG_MAX_CHANNEL) || (HI_NULL == pstAttr))
    {
        return HI_ERR_CODEC_INVALIDPARAM;
    }

    pstAttr->enID = HI_CODEC_ID_VIDEO_MJPEG;
    HI_INFO_CODEC("MJPEG_GetAttr success.\n");
    return HI_SUCCESS;
}

HI_S32 MJPEG_GetStreamInfo(HI_HANDLE hInst, HI_CODEC_STREAMINFO_S *pstStreamInfo)
{
    if ((hInst >= HI_MJPEG_MAX_CHANNEL) || (HI_NULL == pstStreamInfo))
    {
        return HI_ERR_CODEC_INVALIDPARAM;
    }

    pstStreamInfo->stVideo.enCodecID = HI_CODEC_ID_VIDEO_MJPEG;
    pstStreamInfo->stVideo.enSubStandard = HI_CODEC_VIDEO_SUB_STANDARD_UNKNOWN;
    pstStreamInfo->stVideo.u32SubVersion = 0;
    pstStreamInfo->stVideo.u32Profile = 0;
    pstStreamInfo->stVideo.u32Level = 0;
    pstStreamInfo->stVideo.enDisplayNorm = HI_CODEC_ENC_FMT_BUTT;
    pstStreamInfo->stVideo.bProgressive = HI_TRUE;
    pstStreamInfo->stVideo.u32AspectWidth = 0;
    pstStreamInfo->stVideo.u32AspectHeight = 2;
    pstStreamInfo->stVideo.u32bps = 0;
    pstStreamInfo->stVideo.u32FrameRateInt = 0;
    pstStreamInfo->stVideo.u32FrameRateDec = 0;
    pstStreamInfo->stVideo.u32Width = s_stMjpegParam[hInst].u32Width;
    pstStreamInfo->stVideo.u32Height = s_stMjpegParam[hInst].u32Height;
    pstStreamInfo->stVideo.u32DisplayWidth = s_stMjpegParam[hInst].u32Width;
    pstStreamInfo->stVideo.u32DisplayHeight = s_stMjpegParam[hInst].u32Height;
    pstStreamInfo->stVideo.u32DisplayCenterX = s_stMjpegParam[hInst].u32Width / 2;
    pstStreamInfo->stVideo.u32DisplayCenterY = s_stMjpegParam[hInst].u32Height / 2;

    HI_INFO_CODEC("MJPEG_GetStreamInfo success.\n");
    return HI_SUCCESS;
}

/** 跳转函数变量 **/
static jmp_buf s_stJmpBuf;
static jmp_buf s_stDecJmpBuf;

/*****************************************************************************
* func            : JPEG_Error
* description    : CNcomment:解码错误的跳转函数  CNend\n
* param[in]     : cinfo      CNcomment: 解码对象   CNend\n
* retval        : NA
* others:        : NA
*****************************************************************************/
HI_VOID JPEG_Error(j_common_ptr cinfo)
{
    if (0 == cinfo)
    {
        return ;
    }

    (*cinfo->err->output_message)(cinfo);
    longjmp(s_stJmpBuf, 1);
}

HI_VOID JPEG_DEC_Error(j_common_ptr cinfo)
{
    if (0 == cinfo)
    {
        return ;
    }

    (*cinfo->err->output_message)(cinfo);
    longjmp(s_stDecJmpBuf, 1);
}

/*****************************************************************************
* func         : MJPEG_DecodeFrame
* description  : CNcomment:帧解码 CNend\n
* param[in]    : hInst    CNcomment:  CNend\n
* param[in]    : *pstIn   CNcomment:  CNend\n
* param[in]    : *pstOut  CNcomment:  CNend\n
* retval       : NA
* others:      : NA
*****************************************************************************/
HI_S32 MJPEG_DecodeFrame(HI_HANDLE hInst, HI_CODEC_STREAM_S *pstIn, HI_CODEC_FRAME_S *pstOut)
{
    struct jpeg_error_mgr stErrMsg;

    HI_JPEG_SURFACE_S stSurfaceDesc;
    HI_JPEG_INFO_S stJpegInfo;
    HI_JPEG_OUT_INFO_S stOutInfo;

    HI_LD_Event_S  LdEvent;
    HI_U32 hVdecHandle = 0;

    HI_S32 Ret = HI_SUCCESS;
    HI_ULONG DecHandle = 0;

    if ((hInst >= HI_MJPEG_MAX_CHANNEL) || (HI_NULL == pstIn) || (HI_NULL == pstOut))
    {
        return HI_ERR_CODEC_INVALIDPARAM;
    }

    /* record low delay event */
    hVdecHandle = g_lowDelayVdecHandle[hInst];
    LdEvent.evt_id = EVENT_VDEC_FRM_IN;
    LdEvent.frame = g_lowDelayFrameIndex[hVdecHandle & 0xff];
    LdEvent.handle = ((HI_ID_VDEC << 16) | hVdecHandle);
    (HI_VOID)HI_SYS_GetTimeStampMs(&(LdEvent.time));

    (HI_VOID)HI_MPI_STAT_NotifyLowDelayEvent(&LdEvent);
    g_lowDelayFrameIndex[hVdecHandle & 0xff]++;

    VDEC_LOCK(s_stMjpegMutex);

#ifdef JPEG_DEC_CAPA_ENABLE
    DEC_TINIT();
    DEC_TSTART();
#endif

    /** begin to decode **/
    memset(&s_stMjpegParam[hInst].stInfo, 0, sizeof(struct jpeg_decompress_struct));
    s_stMjpegParam[hInst].DecHandle = 0;

    s_stMjpegParam[hInst].stInfo.err = jpeg_std_error(&stErrMsg);
    stErrMsg.error_exit = JPEG_Error;

    if (setjmp(s_stJmpBuf))
    {
        goto DEC_ERR;
    }

#ifdef JPEG_DEBUG_ENABLE
    ALOGE("\n=====================================================================\n");
    ALOGE("start mjpeg dec\n");
#endif

    memset(&stSurfaceDesc, 0x0, sizeof(HI_JPEG_SURFACE_S));
    memset(&stJpegInfo, 0x0, sizeof(HI_JPEG_INFO_S));
    memset(&stOutInfo, 0x0, sizeof(HI_JPEG_OUT_INFO_S));

    jpeg_create_decompress(&s_stMjpegParam[hInst].stInfo);

    if (NULL == s_stMjpegParam[hInst].stInfo.client_data)
    {
        jpeg_destroy_decompress(&s_stMjpegParam[hInst].stInfo);

        DecHandle = HI_JPEG_CreateDecompress(pstIn->u32PhyAddr, pstIn->u32Size, (HI_CHAR *)pstIn->pu8Addr, pstIn->u32Size, NULL, 0);

        if (0 == DecHandle)
        {
            goto DEC_ERR;
        }

        Ret = HI_JPEG_ParseHeader(DecHandle);

        if (HI_SUCCESS != Ret)
        {
            goto DEC_ERR;
        }

        s_stMjpegParam[hInst].DecHandle = DecHandle;
    }
    else
    {
        DecHandle = (HI_ULONG)(s_stMjpegParam[hInst].stInfo.client_data);

        jpeg_mem_src(&s_stMjpegParam[hInst].stInfo, (HI_UCHAR *)(pstIn->pu8Addr), pstIn->u32Size);

        HI_JPEG_SetStreamBufInfo(DecHandle, pstIn->u32PhyAddr, pstIn->u32Size, (HI_CHAR *)pstIn->pu8Addr, pstIn->u32Size, NULL, 0);

        jpeg_read_header(&s_stMjpegParam[hInst].stInfo, TRUE);

        s_stMjpegParam[hInst].DecHandle = DecHandle;
    }

    stJpegInfo.bOutInfo = HI_FALSE;
    Ret = HI_JPEG_GetJpegInfo(DecHandle, &stJpegInfo);

    if (HI_SUCCESS != Ret)
    {
        goto DEC_ERR;
    }

    /*********************************************************************/
    s_stMjpegParam[hInst].stInfo.scale_num   = 1;
    s_stMjpegParam[hInst].stInfo.scale_denom = 1;

    /*********************************************************************/
    switch (stJpegInfo.enFmt)
    {
        case HI_JPEG_FMT_YUV400:
            pstOut->unInfo.stVideo.enColorFormat = HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_400;
            break;

        case HI_JPEG_FMT_YUV420:
            pstOut->unInfo.stVideo.enColorFormat = HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_420;
            break;

        case HI_JPEG_FMT_YUV444:
            pstOut->unInfo.stVideo.enColorFormat = HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_444;
            break;

        case HI_JPEG_FMT_YUV422_12:
            pstOut->unInfo.stVideo.enColorFormat = HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_422_1X2;
            break;

        case HI_JPEG_FMT_YUV422_21:
            pstOut->unInfo.stVideo.enColorFormat = HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_422_2X1;
            break;

        default:
            pstOut->unInfo.stVideo.enColorFormat = HI_CODEC_COLOR_FORMAT_YUV_BUTT;
            goto DEC_ERR;
    }

    /***VPSS only support semi-planar 400/420/422(2x1)***/
    stOutInfo.scale_num   = s_stMjpegParam[hInst].stInfo.scale_num;
    stOutInfo.scale_denom = s_stMjpegParam[hInst].stInfo.scale_denom;
    stOutInfo.OutFmt = stJpegInfo.enFmt;

    if ((stJpegInfo.enFmt == HI_JPEG_FMT_YUV444) || (stJpegInfo.enFmt == HI_JPEG_FMT_YUV422_12))
    {
        stOutInfo.OutFmt = HI_JPEG_FMT_YUV420;
        pstOut->unInfo.stVideo.enColorFormat = HI_CODEC_COLOR_FORMAT_YUV_SEMIPLANAR_420;
    }

    Ret = HI_JPEG_SetOutInfo(DecHandle, &stOutInfo);

    if (HI_SUCCESS != Ret)
    {
        goto DEC_ERR;
    }

    stJpegInfo.bOutInfo = HI_TRUE;
    Ret = HI_JPEG_GetJpegInfo(DecHandle, &stJpegInfo);

    if (HI_SUCCESS != Ret)
    {
        goto DEC_ERR;
    }

#ifndef HI_NVR_SUPPORT
    if (stJpegInfo.u32Width[0] * stJpegInfo.u32Height[0] > MJPEG_FHD_WIDTH * MJEG_FHD_HEIGHT)
    {
        goto DEC_ERR;
    }
#endif

    stSurfaceDesc.u32OutPhy[0] = pstOut->stOutputAddr.u32Phy;
    stSurfaceDesc.u32OutPhy[1] = pstOut->stOutputAddr.u32Phy + stJpegInfo.u32OutSize[0];
    stSurfaceDesc.pOutVir[0]   = (HI_CHAR *)pstOut->stOutputAddr.pu8Vir;
    stSurfaceDesc.pOutVir[1]   = (HI_CHAR *)(pstOut->stOutputAddr.pu8Vir + stJpegInfo.u32OutSize[0]);
    stSurfaceDesc.u32OutStride[0] = stJpegInfo.u32OutStride[0];
    stSurfaceDesc.u32OutStride[1] = stJpegInfo.u32OutStride[1];

    Ret = HI_JPEG_SetOutDesc(DecHandle, &stSurfaceDesc);

    if (HI_SUCCESS != Ret)
    {
        HI_ERR_VDEC("HI_JPEG_SetOutDesc failure\n");
        goto DEC_ERR;
    }

    if (g_lowDelayLinePhyAddr[hInst] == 0)
    {
        MJPEG_StopDecodeFrame(hInst);
    }

#ifdef JPEG_DEBUG_ENABLE
    ALOGE("end start mjpeg dec\n");
    ALOGE("=====================================================================\n");
#endif

    pstOut->unInfo.stVideo.u32Width   = stJpegInfo.u32Width[0];
    pstOut->unInfo.stVideo.u32Height  = stJpegInfo.u32Height[0];
    pstOut->unInfo.stVideo.u32YStride = stJpegInfo.u32OutStride[0];
    pstOut->unInfo.stVideo.u32UStride = stJpegInfo.u32OutStride[1];
    pstOut->unInfo.stVideo.u32YAddr   = pstOut->stOutputAddr.u32Phy;
    pstOut->unInfo.stVideo.u32UAddr   = pstOut->stOutputAddr.u32Phy + stJpegInfo.u32OutSize[0];
    pstOut->unInfo.stVideo.u32VAddr   = 0;
    pstOut->unInfo.stVideo.u32VStride = 0;

    pstOut->s64PtsMs    = pstIn->s64PtsMs;
    pstOut->s64SrcPtsMs = pstIn->s64PtsMs;
    pstOut->unInfo.stVideo.enFrameType        = HI_CODEC_VIDEO_FRAME_TYPE_I;
    pstOut->unInfo.stVideo.bProgressive       = HI_TRUE;
    pstOut->unInfo.stVideo.enFieldMode        = HI_CODEC_VIDEO_FIELD_ALL;
    pstOut->unInfo.stVideo.bTopFieldFirst     = HI_FALSE;
    pstOut->unInfo.stVideo.enFramePackingType = HI_CODEC_VIDEO_FRAME_PACKING_NONE;
    pstOut->unInfo.stVideo.u32FrameRate    = 0;
    pstOut->unInfo.stVideo.u32AspectWidth  = 0;
    pstOut->unInfo.stVideo.u32AspectHeight = 2;
    pstOut->unInfo.stVideo.pu8UserData     = HI_NULL;
    pstOut->unInfo.stVideo.u32UserDataSize = 0;

    s_stMjpegParam[hInst].u32Width  = pstOut->unInfo.stVideo.u32Width;
    s_stMjpegParam[hInst].u32Height = pstOut->unInfo.stVideo.u32Height;

#ifdef JPEG_DEC_CAPA_ENABLE
    DEC_TEND();
#endif

    VDEC_UNLOCK(s_stMjpegMutex);

    return HI_SUCCESS;

DEC_ERR:

    if (NULL != s_stMjpegParam[hInst].stInfo.client_data)
    {
        jpeg_destroy_decompress(&s_stMjpegParam[hInst].stInfo);
    }
    else
    {
        HI_JPEG_DestroyDecompress(DecHandle);
    }

    VDEC_UNLOCK(s_stMjpegMutex);

    HI_ERR_VDEC("motion jpeg decode failure!\n");

    return HI_FAILURE;
}

HI_S32 MJPEG_StopDecodeFrame(HI_HANDLE hInst)
{
    HI_S32 Ret = HI_SUCCESS;
    struct jpeg_error_mgr stErrMsg;

    s_stMjpegParam[hInst].stInfo.err = jpeg_std_error(&stErrMsg);
    stErrMsg.error_exit = JPEG_DEC_Error;

    if (setjmp(s_stDecJmpBuf))
    {
        goto DEC_ERR;
    }

    if (NULL != s_stMjpegParam[hInst].stInfo.client_data)
    {
        jpeg_start_decompress(&s_stMjpegParam[hInst].stInfo);

        while (s_stMjpegParam[hInst].stInfo.output_scanline < s_stMjpegParam[hInst].stInfo.output_height)
        {
            jpeg_read_scanlines(&s_stMjpegParam[hInst].stInfo, NULL, 1);
        }

        jpeg_finish_decompress(&s_stMjpegParam[hInst].stInfo);
    }
    else
    {
        Ret = HI_JPEG_StartDecompress(s_stMjpegParam[hInst].DecHandle);

        if (HI_SUCCESS != Ret)
        {
            goto DEC_ERR;
        }
    }

DEC_ERR:

    if (NULL != s_stMjpegParam[hInst].stInfo.client_data)
    {
        jpeg_destroy_decompress(&s_stMjpegParam[hInst].stInfo);
    }
    else
    {
        HI_JPEG_DestroyDecompress(s_stMjpegParam[hInst].DecHandle);
    }

    return HI_SUCCESS;
}

HI_S32 StopDecodeFrame(HI_HANDLE hInst)
{
    if ((hInst >= HI_MJPEG_MAX_CHANNEL) || (hInst < 0))
    {
        return HI_FAILURE;
    }

    VDEC_LOCK(s_stMjpegMutex);

    HI_JPEG_SetLowDelayInf(s_stMjpegParam[hInst].DecHandle, g_lowDelayLinePhyAddr[hInst], (HI_CHAR *)(HI_ULONG)g_lowDelayLineVirAddr[hInst]);

    MJPEG_StopDecodeFrame(hInst);

    VDEC_UNLOCK(s_stMjpegMutex);

    return HI_SUCCESS;
}
