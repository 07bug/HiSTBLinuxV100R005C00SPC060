/*========================================================================
  Open MAX   Component: Video Encoder
  This module contains the class definition for openMAX decoder component.
author: sdk
==========================================================================*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <inttypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/file.h>

#include "omx_dbg.h"
#include "omx_venc.h"
#include "hi_unf_common.h"
#include "OMX_VideoExt.h"
#include "OMX_IndexExt.h"
#include "OMX_RoleNames.h"

#ifdef ANDROID
#ifdef ANDROID_O
#include <hardware/gralloc1.h>
#else
#include <hardware/gralloc.h>
#endif
#include "gralloc_priv.h"
#include "graphics.h"
#include "hi_tde_api.h"

#define TDE_CSCTABLE_SIZE 7
static HI_U32 s_Rgb2YuvCsc[TDE_CSCTABLE_SIZE] =
{0x00810042, 0xffda0019, 0x0070ffb6, 0xffa20070, 0x0000ffee, 0x00000000, 0x02010010};
#endif

#define PIC_ALIGN_SIZE (4)

#define VENC_DONE_SUCCESS (0)
#define VENC_DONE_FAILED  (-1)

//#define __VENC_DBG_DELAY_STAT__
//#define  __OMXVENC_FILE_OUT_SAVE__
//#define  __OMXVENC_FILE_IN_SAVE__
//#define __OMXVENC_RGB_BUFFER__

#define DBG_OUT_FILENAME "/mnt/sdcard/omx_venc_out.h264"
#define DBG_IN_FILENAME  "/mnt/omx_venc_in.yuv"
#define DBG_RGB_FILENAME "/data/omx_venc_rgb_in.rgb"

#define HI_VENC_MAX_fps         (60)
#define HI_VENC_MIN_fps         (1)

#ifdef  __VENC_DBG_DELAY_STAT__
static  struct timeval TmpTime[100][6] = {0};
static HI_U32 etb_id = 0;          //0
static HI_U32 etb_x_id = 0;          //5
static HI_U32 etb_done_id = 0;          //0
static HI_U32 ftb_id = 0;          //5
static HI_U32 ftb_x_id = 0;          //5
static HI_U32 ftb_done_id = 0;          //5

static HI_U32 flag   = 1;
#endif


HI_U32 g_etb_cnt = 0;
HI_U32 g_ftb_cnt = 0;

#ifdef  __OMXVENC_FILE_OUT_SAVE__
FILE*    g_pFiletoSave = NULL;
#endif

#ifdef __OMXVENC_FILE_IN_SAVE__
FILE*    g_pFiletoEnc = NULL;
char*    g_pU = NULL;
char*    g_pV = NULL;

OMX_U32 g_u32CountNum = 0;
OMX_U32 g_u32CountNum_etb = 0;

#endif

#ifdef __OMXRGB_FILE_IN_SAVE__
FILE*    g_rgbtoSave = NULL;
#endif

///////////////////////////////////////////////
enum
{
    OMX_STATE_IDLE_PENDING    = 1,
    OMX_STATE_LOADING_PENDING    ,
    OMX_STATE_INPUT_ENABLE_PENDING,
    OMX_STATE_OUTPUT_ENABLE_PENDING,
    OMX_STATE_OUTPUT_DISABLE_PENDING,
    OMX_STATE_INPUT_DISABLE_PENDING,
    OMX_STATE_OUTPUT_FLUSH_PENDING,
    OMX_STATE_INPUT_FLUSH_PENDING,
    OMX_STATE_PAUSE_PENDING,
    OMX_STATE_EXECUTE_PENDING
};
// Deferred callback identifiers
enum                                                          //���ڱ�ʾ���� CMD ����,�Ա��ڲ�����е�ʱ���ж�Ҫ����Ϣ�Ĵ�����Ҫ�����ĸ�����
{
    OMX_GENERATE_COMMAND_DONE           = 0x1,
    OMX_GENERATE_FTB                    = 0x2,
    OMX_GENERATE_ETB                    = 0x3,
    OMX_GENERATE_COMMAND                = 0x4,
    OMX_GENERATE_EBD                    = 0x5,
    OMX_GENERATE_FBD                    = 0x6,
    OMX_GENERATE_FLUSH_INPUT_DONE        = 0x7,
    OMX_GENERATE_FLUSH_OUTPUT_DONE        = 0x8,
    OMX_GENERATE_START_DONE                = 0x9,
    OMX_GENERATE_PAUSE_DONE                = 0xA,
    OMX_GENERATE_RESUME_DONE            = 0xB,
    OMX_GENERATE_STOP_DONE                = 0xC,
    OMX_GENERATE_EOS_DONE                = 0xD,
    OMX_GENERATE_HARDWARE_ERROR            = 0xE,
    OMX_GENERATE_IMAGE_SIZE_CHANGE        = 0xF,
    OMX_GENERATE_CROP_RECT_CHANGE        = 0x10,
    OMX_GENERATE_UNUSED                    = 0x11
};

/*���������б�: *//*Ԫ��˵��:�Զ���Э�����ƣ�omx��׼Э��ö�ٵ����ݣ�ԭ��unf�ӿڶ�Ӧ��ö��*/
static const struct codec_info codec_trans_list[] =
{
    {OMX_ROLE_VIDEO_ENCODER_AVC, OMX_VIDEO_CodingAVC, HI_UNF_VCODEC_TYPE_H264},
#ifdef OMXVENC_SUPPORT_HEVC
    {OMX_ROLE_VIDEO_ENCODER_HEVC, OMX_VIDEO_CodingHEVC, HI_UNF_VCODEC_TYPE_HEVC}
#endif
};

static const struct codec_profile_level avc_profile_level_list[] =
{
    {OMX_VIDEO_AVCProfileBaseline, OMX_VIDEO_AVCLevel1},
    {OMX_VIDEO_AVCProfileBaseline, OMX_VIDEO_AVCLevel2},
    {OMX_VIDEO_AVCProfileBaseline, OMX_VIDEO_AVCLevel21},
    {OMX_VIDEO_AVCProfileBaseline, OMX_VIDEO_AVCLevel3},
    {OMX_VIDEO_AVCProfileBaseline, OMX_VIDEO_AVCLevel31},
    {OMX_VIDEO_AVCProfileBaseline, OMX_VIDEO_AVCLevel32},
#ifdef OMXVENC_SUPPORT_1080P
    {OMX_VIDEO_AVCProfileBaseline, OMX_VIDEO_AVCLevel41},
#endif
    {OMX_VIDEO_AVCProfileMain, OMX_VIDEO_AVCLevel1},
    {OMX_VIDEO_AVCProfileMain, OMX_VIDEO_AVCLevel2},
    {OMX_VIDEO_AVCProfileMain, OMX_VIDEO_AVCLevel21},
    {OMX_VIDEO_AVCProfileMain, OMX_VIDEO_AVCLevel3},
    {OMX_VIDEO_AVCProfileMain, OMX_VIDEO_AVCLevel31},
    {OMX_VIDEO_AVCProfileMain, OMX_VIDEO_AVCLevel32},
#ifdef OMXVENC_SUPPORT_1080P
    {OMX_VIDEO_AVCProfileMain, OMX_VIDEO_AVCLevel41},
#endif
    {OMX_VIDEO_AVCProfileHigh, OMX_VIDEO_AVCLevel1},
    {OMX_VIDEO_AVCProfileHigh, OMX_VIDEO_AVCLevel2},
    {OMX_VIDEO_AVCProfileHigh, OMX_VIDEO_AVCLevel21},
    {OMX_VIDEO_AVCProfileHigh, OMX_VIDEO_AVCLevel3},
    {OMX_VIDEO_AVCProfileHigh, OMX_VIDEO_AVCLevel31},
    {OMX_VIDEO_AVCProfileHigh, OMX_VIDEO_AVCLevel32},
#ifdef OMXVENC_SUPPORT_1080P
    {OMX_VIDEO_AVCProfileHigh, OMX_VIDEO_AVCLevel41},
#endif
};

/* CodecType Relative */
#ifdef OMXVENC_SUPPORT_HEVC
static const struct codec_profile_level hevc_profile_level_list[] =
{
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCMainTierLevel1},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCHighTierLevel1},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCMainTierLevel2},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCHighTierLevel2},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCMainTierLevel21},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCHighTierLevel21},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCMainTierLevel3},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCHighTierLevel3},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCMainTierLevel31},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCHighTierLevel31},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCMainTierLevel4},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCHighTierLevel4},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCMainTierLevel41},
    {OMX_VIDEO_HEVCProfileMain,     OMX_VIDEO_HEVCHighTierLevel41},
};
#endif

enum
{
    OMX_VENC_YUV_420    = 0,
    OMX_VENC_YUV_422    = 1,
    OMX_VENC_YUV_444    = 2,
    OMX_VENC_YUV_NONE   = 3
};

enum
{
    OMX_VENC_V_U        = 0,
    OMX_VENC_U_V        = 1
};

enum
{
    OMX_VENC_STORE_SEMIPLANNAR  = 0,
    OMX_VENC_STORE_PACKAGE      = 1,
    OMX_VENC_STORE_PLANNAR      = 2
};

enum
{
    OMX_VENC_PACKAGE_UY0VY1     = 141/*0b10001101*/,
    OMX_VENC_PACKAGE_Y0UY1V     = 216/*0b11011000*/,
    OMX_VENC_PACKAGE_Y0VY1U     = 120/*0b01111000*/
};

#ifdef __VENC_DBG_DELAY_STAT__
////////////////////////////////////////////////////////////////////////  just for debug
static void write_output(void)
{
    OMX_S32 ret = 0;
    OMX_S32 i = 0;
    OMX_U32 diff1 = 0, diff2 = 0, diff3 = 0, diff4 = 0, diff5 = 0, diff6 = 0, total = 0;

    for (i = 0; i < 100; i++)
    {
        diff1 = (TmpTime[i][1].tv_sec == TmpTime[i][0].tv_sec) ? (TmpTime[i][1].tv_usec - TmpTime[i][0].tv_usec) : (TmpTime[i][1].tv_usec + 1000000 - TmpTime[i][0].tv_usec);
        diff2 = (TmpTime[i][2].tv_sec == TmpTime[i][1].tv_sec) ? (TmpTime[i][2].tv_usec - TmpTime[i][1].tv_usec) : (TmpTime[i][2].tv_usec + 1000000 - TmpTime[i][1].tv_usec);
        diff3 = (TmpTime[i][4].tv_sec == TmpTime[i][3].tv_sec) ? (TmpTime[i][4].tv_usec - TmpTime[i][3].tv_usec) : (TmpTime[i][4].tv_usec + 1000000 - TmpTime[i][3].tv_usec);
        diff4 = (TmpTime[i][5].tv_sec == TmpTime[i][4].tv_sec) ? (TmpTime[i][5].tv_usec - TmpTime[i][4].tv_usec) : (TmpTime[i][5].tv_usec + 1000000 - TmpTime[i][4].tv_usec);
        diff5 = (TmpTime[i][5].tv_sec == TmpTime[i][2].tv_sec) ? (TmpTime[i][5].tv_usec - TmpTime[i][2].tv_usec) : (TmpTime[i][5].tv_usec + 1000000 - TmpTime[i][2].tv_usec);
        total = (TmpTime[i][5].tv_sec == TmpTime[i][0].tv_sec) ? (TmpTime[i][5].tv_usec - TmpTime[i][0].tv_usec) : (TmpTime[i][5].tv_usec + 1000000 - TmpTime[i][0].tv_usec);
    }
}
///////////////////////////////////////////////////////////////////////
#endif

static OMX_ERRORTYPE omx_check_param_videoAvc(OMX_VIDEO_PARAM_AVCTYPE* pAvcType)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_U32 bError = 0;

    bError |= (OMX_U32)(pAvcType->nSliceHeaderSpacing   != 0);
    bError |= (OMX_U32)(pAvcType->nBFrames              != 0);
    bError |= (OMX_U32)(pAvcType->nRefIdx10ActiveMinus1 != 0);   //support B frame
    bError |= (OMX_U32)(pAvcType->nRefIdx11ActiveMinus1 != 0);   //support B frame
    bError |= (OMX_U32)(pAvcType->bEnableUEP            != OMX_FALSE);
    bError |= (OMX_U32)(pAvcType->bEnableFMO            != OMX_FALSE);
    bError |= (OMX_U32)(pAvcType->bEnableASO            != OMX_FALSE);
    bError |= (OMX_U32)(pAvcType->bEnableRS             != OMX_FALSE);
    bError |= (OMX_U32)((pAvcType->eProfile              == OMX_VIDEO_AVCProfileExtended) || (pAvcType->eProfile > OMX_VIDEO_AVCProfileHigh));
    bError |= (OMX_U32)((pAvcType->nAllowedPictureTypes  & 0xfffffffc) || (pAvcType->nAllowedPictureTypes == OMX_VIDEO_PictureTypeP));
    bError |= (OMX_U32)(pAvcType->eProfile == OMX_VIDEO_AVCProfileBaseline) ? (pAvcType->bEntropyCodingCABAC != OMX_FALSE) : (OMX_FALSE);
    bError |= (OMX_U32)(pAvcType->bDirect8x8Inference != OMX_FALSE) ? (pAvcType->eProfile != OMX_VIDEO_AVCProfileHigh) : (OMX_FALSE);
    bError |= (OMX_U32)(pAvcType->bDirectSpatialTemporal != OMX_FALSE);
    bError |= (OMX_U32)(pAvcType->nCabacInitIdc          != 0);

    if ((pAvcType->nAllowedPictureTypes == OMX_VIDEO_PictureTypeI) && (pAvcType->nPFrames != 0 ))
    {
        bError |= 1;
    }
    else if ((pAvcType->nAllowedPictureTypes == 0x3) && (pAvcType->nPFrames == 0 ))
    {
        bError |= 1;
    }

    if (bError != 0)
    {
        ret = OMX_ErrorBadParameter;
    }

    return ret;
}

#ifdef OMXVENC_SUPPORT_HEVC
static OMX_ERRORTYPE omx_check_param_videoHevc(OMX_VIDEO_PARAM_HEVCTYPE* pHevcType)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_U32 bError = 0;

    bError |= (OMX_U32)(pHevcType->eProfile   != OMX_VIDEO_HEVCProfileMain);
    bError |= (OMX_U32)((pHevcType->eLevel != OMX_VIDEO_HEVCMainTierLevel1)
                      &&(pHevcType->eLevel != OMX_VIDEO_HEVCMainTierLevel2)
                      &&(pHevcType->eLevel != OMX_VIDEO_HEVCMainTierLevel21)
                      &&(pHevcType->eLevel != OMX_VIDEO_HEVCMainTierLevel3)
                      &&(pHevcType->eLevel != OMX_VIDEO_HEVCMainTierLevel31)
                      &&(pHevcType->eLevel != OMX_VIDEO_HEVCMainTierLevel4)
                      &&(pHevcType->eLevel != OMX_VIDEO_HEVCMainTierLevel41));
    if (bError != 0)
    {
        ret = OMX_ErrorBadParameter;
    }

    return ret;
}
#endif

static void omx_report_event(OMX_COMPONENT_PRIVATE* pcom_priv,
                             OMX_IN OMX_EVENTTYPE event_type, OMX_IN OMX_U32 param1,
                             OMX_IN OMX_U32 param2, OMX_IN OMX_PTR pdata)
{
    if ((pcom_priv == NULL) || (pcom_priv->m_cb.EventHandler == NULL))
    {
        DEBUG_PRINT_ERROR("ptr is null!\n");
        return;
    }

    pcom_priv->m_cb.EventHandler(pcom_priv->m_pcomp,
                                 pcom_priv->m_app_data, event_type,
                                param1, param2, pdata);
    return;
}

static inline void omx_report_error(OMX_COMPONENT_PRIVATE* pcom_priv, OMX_S32 error_type)
{
    omx_report_event(pcom_priv, OMX_EventError, error_type, 0, NULL);
}

static OMX_BOOL port_full(OMX_COMPONENT_PRIVATE* pcom_priv, OMX_U32 port)
{
    OMX_PORT_PRIVATE* port_priv = &pcom_priv->m_port[port];
    OMX_U32 i;

    for (i = 0; i < port_priv->port_def.nBufferCountActual; i++)
    {
        if (bit_absent(&port_priv->m_buf_cnt, i))
        {
            return OMX_FALSE;
        }
    }

    return OMX_TRUE;
}

static OMX_BOOL port_empty(OMX_COMPONENT_PRIVATE* pcom_priv, OMX_U32 port)
{
    OMX_PORT_PRIVATE* port_priv = &pcom_priv->m_port[port];
    OMX_U32 i;

    for (i = 0; i < port_priv->port_def.nBufferCountActual; i++)
    {
        if (bit_present(&port_priv->m_buf_cnt, i))
        {
            return OMX_FALSE;
        }
    }

    return OMX_TRUE;
}

static OMX_BOOL ports_all_full(OMX_COMPONENT_PRIVATE* pcom_priv)
{
    if (port_full(pcom_priv, INPUT_PORT_INDEX) != OMX_TRUE)
    { return OMX_FALSE; }

    return port_full(pcom_priv, OUTPUT_PORT_INDEX);
}

static OMX_BOOL ports_all_empty(OMX_COMPONENT_PRIVATE* pcom_priv)
{
    if (port_empty(pcom_priv, INPUT_PORT_INDEX) != OMX_TRUE)
    { return OMX_FALSE; }

    return port_empty(pcom_priv, OUTPUT_PORT_INDEX);
}

static void post_event(OMX_COMPONENT_PRIVATE* pcom_priv,
                                OMX_U32 param1, OMX_U32 param2, OMX_U8 id)                //ѹ����У�д��ܵ�
{
    OMX_S32 ret_entry = 0;
    OMX_S32 n = -1;
    (void)pthread_mutex_lock(&pcom_priv->m_lock);
    if ((id == OMX_GENERATE_FTB) || (id == OMX_GENERATE_FBD))
    {
        ret_entry = push_entry(&pcom_priv->m_ftb_q, param1, param2, id);
    }
    else if ((id == OMX_GENERATE_ETB) || (id == OMX_GENERATE_EBD))
    {
        ret_entry = push_entry(&pcom_priv->m_etb_q, param1, param2, id);                       //param1:��Ӧ���� ��param2:��������������
    }
    else
    {
        ret_entry = push_entry(&pcom_priv->m_cmd_q, param1, param2, id);
    }

    if (ret_entry != 0)
    {
        DEBUG_PRINT("push_entry error!\n");
    }
    (void)pthread_mutex_unlock(&pcom_priv->m_lock);

    n = write(pcom_priv->m_pipe_out, &id, 1);
    if (n < 0)
    {
        DEBUG_PRINT_ERROR("post message failed,id = %d\n", id);
    }

}

static OMX_ERRORTYPE fill_buffer_done(OMX_COMPONENT_PRIVATE* pcom_priv, OMX_BUFFERHEADERTYPE* buffer)
{
    OMX_ERRORTYPE ret;
    OMX_PORT_PRIVATE* port_priv = NULL;
    OMX_CHECK_ARG_RETURN(pcom_priv == NULL);
    OMX_CHECK_ARG_RETURN(buffer == NULL);

    port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];

    if (port_priv->m_port_flushing)
    {
        buffer->nFilledLen = 0;
    }

    port_priv->m_buf_pend_cnt--;

    if (!pcom_priv->m_cb.FillBufferDone)
    {
        DEBUG_PRINT_ERROR("[FBD] FillBufferDone callback NULL!\n");
        return OMX_ErrorUndefined;
    }

#ifdef __VENC_DBG_DELAY_STAT__
    if (ftb_done_id <= 100)
    {
        ret = gettimeofday (&TmpTime[ftb_done_id][5] , NULL);
        if (ret == 0)
        {
            ftb_done_id++;
        }
    }
    else if (flag)
    {
        write_output();
        flag = 0;
    }
#endif

#ifdef __OMXVENC_FILE_OUT_SAVE__
    if ((g_pFiletoSave != NULL) && (buffer->nFilledLen != 0))
    {
        fwrite(buffer->pBuffer, 1, buffer->nFilledLen, g_pFiletoSave);
    }
#endif
    DEBUG_PRINT_EFTB("[FBD] VirAddr = %p,flag = 0x%lx,pts = %lld,cnt = %d\n",buffer->pBuffer,buffer->nFlags, buffer->nTimeStamp,g_ftb_cnt);
    ret = pcom_priv->m_cb.FillBufferDone(pcom_priv->m_pcomp, pcom_priv->m_app_data, buffer);

    return ret;
}

static OMX_ERRORTYPE empty_buffer_done(OMX_COMPONENT_PRIVATE* pcom_priv,
                                       OMX_BUFFERHEADERTYPE* buffer)
{
    OMX_ERRORTYPE ret;
    OMX_PORT_PRIVATE* port_priv = NULL;
    OMX_CHECK_ARG_RETURN(pcom_priv == NULL);
    OMX_CHECK_ARG_RETURN(buffer == NULL);

    port_priv = &pcom_priv->m_port[INPUT_PORT_INDEX];
    port_priv->m_buf_pend_cnt--;
    buffer->nFilledLen = 0;

    if (!pcom_priv->m_cb.EmptyBufferDone)
    {
        DEBUG_PRINT_ERROR("[EBD] EmptyBufferDone callback NULL!\n");
        return OMX_ErrorUndefined;
    }
#ifdef __VENC_DBG_DELAY_STAT__
    if (etb_done_id <= 100)
    {
        OMX_S32 ret = 0;
        ret = gettimeofday (&TmpTime[etb_done_id][2] , NULL);
        if (ret == 0)
        {
            etb_done_id++;
        }
    }
#endif
    DEBUG_PRINT_EFTB("[EBD] VirAddr = %p,flag = 0x%lx,num = %d, nTimeStamp = %lld\n",
               buffer->pBuffer,buffer->nFlags,g_etb_cnt,buffer->nTimeStamp);
    ret = pcom_priv->m_cb.EmptyBufferDone(pcom_priv->m_pcomp, pcom_priv->m_app_data, buffer);

    return ret;
}

#ifdef ANDROID
OMX_U32 conver_format_forMetaData(OMX_U32 MetaDataFormat, OMX_U32 flag) //0:storeType 1:sample   2:packageSel
{
    OMX_U32 RetFormat;

    switch (MetaDataFormat)
    {
        case HAL_PIXEL_FORMAT_RGBA_8888:
            if (flag == 0)
            {
                RetFormat = TDE2_COLOR_FMT_ABGR8888;
            }
            else if (flag == 1)
            {
                RetFormat = TDE2_COLOR_FMT_ABGR8888;
            }
            else
            {
                RetFormat = TDE2_COLOR_FMT_ABGR8888;
            }
            break;
        case HAL_PIXEL_FORMAT_RGBX_8888:
            if (flag == 0)
            {
                RetFormat = TDE2_COLOR_FMT_ABGR8888;
            }
            else if (flag == 1)
            {
                RetFormat = TDE2_COLOR_FMT_ABGR8888;
            }
            else
            {
                RetFormat = TDE2_COLOR_FMT_ABGR8888;
            }
            break;
        case HAL_PIXEL_FORMAT_YV12:    //planer 420 YCrCb
            if (flag == 0)
            {
                RetFormat = OMX_VENC_STORE_PLANNAR;
            }
            else if (flag == 1)
            {
                RetFormat = OMX_VENC_YUV_420;
            }
            else
            {
                RetFormat = 0;
            }
            break;
        case HAL_PIXEL_FORMAT_YCbCr_422_SP:
            if (flag == 0)
            {
                RetFormat = OMX_VENC_STORE_SEMIPLANNAR;
            }
            else if (flag == 1)
            {
                RetFormat = OMX_VENC_YUV_422;
            }
            else
            {
                RetFormat = OMX_VENC_V_U;
            }
            break;
        case HAL_PIXEL_FORMAT_YCrCb_420_SP:
            if (flag == 0)
            {
                RetFormat = OMX_VENC_STORE_SEMIPLANNAR;
            }
            else if (flag == 1)
            {
                RetFormat = OMX_VENC_YUV_420;
            }
            else
            {
                RetFormat = OMX_VENC_V_U;
            }
            break;
        case HAL_PIXEL_FORMAT_YCbCr_420_SP:
            if (flag == 0)
            {
                RetFormat = OMX_VENC_STORE_SEMIPLANNAR;
            }
            else if (flag == 1)
            {
                RetFormat = OMX_VENC_YUV_420;
            }
            else
            {
                RetFormat = OMX_VENC_U_V;
            }
            break;
        default:
            DEBUG_PRINT_ERROR("the MetaData format(0x%x) can't found!! use the format = HAL_PIXEL_FORMAT_RGBA_8888!",MetaDataFormat);
            RetFormat = TDE2_COLOR_FMT_ABGR8888;
            break;
    }

    return RetFormat;
}

static OMX_ERRORTYPE omxvenc_extractGrallocData(void* data, venc_user_info* buffer, OMX_COMPONENT_PRIVATE* pcom_priv)
{
    TDE_HANDLE handle;
    OMX_S32 s32Ret = 0;
    TDE2_SURFACE_S stForeGround;
    TDE2_SURFACE_S stDst;
    TDE2_RECT_S stForeGroundRect;
    TDE2_RECT_S stDstRect;
    TDE2_OPT_S stOpt ;
    HI_BOOL bBlock = HI_TRUE;
    OMX_U32 u32TimeOut = 50;
    FILE* fp = NULL;
    OMX_U32 retLen = 0;
    OMX_U32* pCscTableVir;
    HI_MMZ_BUF_S stBuf = {0};

    OMX_U32 type = *(OMX_U32*)data;
    OMX_U8* UserVirAddr = NULL;

    buffer_handle_t imgBuffer = *(buffer_handle_t*)((uint8_t*)data + 4);
    OMX_CHECK_ARG_RETURN(imgBuffer == NULL);

    private_handle_t* p_private_handle = (private_handle_t*)imgBuffer;
    OMX_CHECK_ARG_RETURN(p_private_handle == NULL);

    DEBUG_PRINT("%s:p_private_handle = 0x%x,(st_size = %d),payaddr = 0x%x,offset = %d,width = %d,height = %d,size = %d,format=%d\n",
                __func__,
                p_private_handle, sizeof(private_handle_t), p_private_handle->ion_phy_addr, p_private_handle->offset,
                p_private_handle->width,
                p_private_handle->height, p_private_handle->size, p_private_handle->format);

#if defined(__OMXVENC_FILE_IN_SAVE__) || defined(__OMXRGB_FILE_IN_SAVE__)
    UserVirAddr = p_private_handle->base;
    if (NULL ==  UserVirAddr)
    {
        DEBUG_PRINT_ERROR("%s() HI_MEM_Map error!\n", __func__);
        return OMX_ErrorUndefined;
    }
#endif

    if (p_private_handle->format == HAL_PIXEL_FORMAT_RGBA_8888 || p_private_handle->format == HAL_PIXEL_FORMAT_RGBX_8888)
    {
        memset(&stOpt, 0, sizeof(TDE2_OPT_S));
        memset(&stForeGround, 0, sizeof(TDE2_SURFACE_S));
        memset(&stDst, 0, sizeof(TDE2_SURFACE_S));
    #ifdef __OMXRGB_FILE_IN_SAVE__
        if ((g_rgbtoSave != NULL) && (p_private_handle->size != 0))
            {
                fwrite(UserVirAddr, 1, p_private_handle->size, g_rgbtoSave);
            }
    #endif
        if (p_private_handle->ion_phy_addr == 0xffffffff)   /*the rgb buffer not continuous*/
        {
#ifdef __OMXVENC_RGB_BUFFER__
            if ((pcom_priv->bufferaddr_RGB != 0) && (pcom_priv->bufferaddr_RGB != 0xffffffff))
            {
                 DEBUG_PRINT("%s,%d,bufferaddr_RGB = %p, base_addr = %p,size = %d\n",__func__,__LINE__,
                    pcom_priv->bufferaddr_RGB,p_private_handle->base,p_private_handle->size);
                 memcpy(pcom_priv->bufferaddr_RGB, p_private_handle->base, p_private_handle->size);
            }
            else
            {
                DEBUG_PRINT_ERROR("%s() p_private_handle->ion_phy_addr = -1,the rgb buffer not continuous!\n", __func__);
                return OMX_ErrorUndefined;
            }
#else
            DEBUG_PRINT_ERROR("%s() p_private_handle->ion_phy_addr = -1,the rgb buffer not continuous!\n", __func__);
            return OMX_ErrorUndefined;
#endif
        }

        snprintf(stBuf.bufname, 16, "%s", "OMXVENC_CSC");
        stBuf.bufsize = 28;

        s32Ret = HI_MMZ_Malloc(&stBuf);
        if (0 != s32Ret)
        {
            DEBUG_PRINT_ERROR("%s:ERROR: HI_MMZ_Malloc Failed!! Ret:%d\n", __func__, s32Ret);
            return -1;
        }

        buffer->user_buf.MetaDateFlag      = 0;
        buffer->ion_handle        = p_private_handle;

        buffer->user_buf.picWidth          = p_private_handle->width;
        buffer->user_buf.picHeight         = p_private_handle->height;

        buffer->user_buf.store_type        = OMX_VENC_STORE_PACKAGE;
        buffer->user_buf.sample_type       = OMX_VENC_YUV_422;
        buffer->user_buf.package_sel       = OMX_VENC_PACKAGE_UY0VY1;

        buffer->user_buf.strideY           = ALIGN_UP(buffer->user_buf.picWidth, 16) * 2;
        buffer->user_buf.data_len          = buffer->user_buf.picHeight * buffer->user_buf.strideY;
        buffer->user_buf.offset            = 64;

        /**************** set TDE process paramter **************/
        //input RGB
        stForeGround.u32PhyAddr   = (p_private_handle->ion_phy_addr != 0xffffffff)?
                                   p_private_handle->ion_phy_addr:pcom_priv->bufferaddr_Phy_RGB;
        stForeGround.enColorFmt   = conver_format_forMetaData(p_private_handle->format, 0);
        stForeGround.u32Width     = buffer->user_buf.picWidth ;
        stForeGround.u32Height    = buffer->user_buf.picHeight;
        stForeGround.u32Stride    = p_private_handle->stride * 4;

        stForeGroundRect.s32Xpos = 0;
        stForeGroundRect.s32Ypos = 0;
        stForeGroundRect.u32Height = stForeGround.u32Height;
        stForeGroundRect.u32Width = stForeGround.u32Width;

        //output YUV(package422 YUYV)
        stDst.u32PhyAddr   = buffer->user_buf.bufferaddr_Phy + buffer->user_buf.offset;   /*64 is the offset of struct header*/
        stDst.enColorFmt   = TDE2_COLOR_FMT_YCbCr422;
        stDst.u32Width     = buffer->user_buf.picWidth ;
        stDst.u32Height    = buffer->user_buf.picHeight;
        stDst.u32Stride    = ALIGN_UP(buffer->user_buf.picWidth, 16) * 2;

        stDstRect = stForeGroundRect;
        stOpt.stCscOpt.bICSCUserEnable  = 1;
        stOpt.stCscOpt.bICSCParamReload = 1;
        stOpt.stCscOpt.u32ICSCParamAddr = stBuf.phyaddr;

        memcpy(stBuf.user_viraddr, s_Rgb2YuvCsc, 28);

        DEBUG_PRINT("%s,TDE stCscOpt u32PhyAddr = 0x%x\n", __func__, stBuf.phyaddr);
        DEBUG_PRINT("%s,TDE input    u32PhyAddr = 0x%x, W = %d, H = %d, stride = %d\n", __func__, stForeGround.u32PhyAddr,stForeGround.u32Width ,stForeGround.u32Height,stForeGround.u32Stride);
        DEBUG_PRINT("%s,TDE output   u32PhyAddr = 0x%x, W = %d, H = %d, stride = %d\n", __func__, stDst.u32PhyAddr,stDst.u32Width ,stDst.u32Height,stDst.u32Stride);

        if (HI_TDE2_Open() != HI_SUCCESS)
        {
            DEBUG_PRINT_ERROR("%s,HI_TDE2_Open return failed!\n", __func__);
            return -1;
        }
        pcom_priv->hTDE = HI_TDE2_BeginJob();
        if ((pcom_priv->hTDE == HI_NULL) || (pcom_priv->hTDE == HI_INVALID_HANDLE))
        {
            DEBUG_PRINT_ERROR("%s,TDE failed to get Handle(ret = 0x%x)\n", __func__, pcom_priv->hTDE);
            return OMX_ErrorHardware;
        }
        s32Ret = HI_TDE2_Bitblit((TDE_HANDLE)pcom_priv->hTDE, HI_NULL, HI_NULL, &stForeGround, &stForeGroundRect,
                                 &stDst, &stDstRect, &stOpt);

        HI_TDE2_EndJob(pcom_priv->hTDE, HI_FALSE, HI_TRUE, 50);
        pcom_priv->hTDE = HI_INVALID_HANDLE;
        HI_TDE2_Close();

#ifdef __OMXVENC_FILE_IN_SAVE__

        if ((g_pFiletoEnc != NULL) && (buffer->user_buf.data_len != 0))
        {
            fwrite((char*)(buffer->user_buf.bufferaddr_Phy + buffer->user_buf.offset), 1, buffer->user_buf.picWidth * buffer->user_buf.picHeight * 2, g_pFiletoEnc);
        }
#endif

        s32Ret = HI_MMZ_Free(&stBuf);
        if (HI_FAILURE == s32Ret)
        {
            DEBUG_PRINT_ERROR("%s,%d,HI_MMZ_Free failed!!\n", __func__, __LINE__);
        }
    }
    else if (p_private_handle->format == HAL_PIXEL_FORMAT_YCrCb_420_SP || p_private_handle->format == HAL_PIXEL_FORMAT_YCbCr_420_SP)  /*sp420*/
    {

        venc_metadata_buf* pMetaData = &(buffer->user_buf.stMetaData);
        pMetaData->bufferaddr_Phy = p_private_handle->ion_phy_addr + p_private_handle->offset;
        pMetaData->buffer_size    = p_private_handle->size;

        buffer->user_buf.MetaDateFlag      = 1;
        buffer->ion_handle        = p_private_handle;

        buffer->user_buf.picWidth          = p_private_handle->width;
        buffer->user_buf.picHeight         = p_private_handle->height;

        buffer->user_buf.store_type        = conver_format_forMetaData(p_private_handle->format, 0);
        buffer->user_buf.sample_type       = conver_format_forMetaData(p_private_handle->format, 1);
        buffer->user_buf.package_sel       = conver_format_forMetaData(p_private_handle->format, 2);
        buffer->user_buf.data_len          = p_private_handle->height * p_private_handle->stride * 3 / 2;
        buffer->user_buf.strideY           = p_private_handle->stride;//ALIGN_UP(buffer->picWidth,16);
        buffer->user_buf.strideC           = buffer->user_buf.strideY;
        buffer->user_buf.offset            = 0;
        buffer->user_buf.offset_YC         = p_private_handle->height * p_private_handle->stride;  //YC������ƫ��

        DEBUG_PRINT("%s:%d,payaddr = 0x%x,width = %d,height = %d,store_type = %d,sample_type = %d,package_sel = %d\n",
                    __func__, __LINE__,
                    pMetaData->bufferaddr_Phy, buffer->user_buf.picWidth, buffer->user_buf.picHeight,
                    buffer->user_buf.store_type, buffer->user_buf.sample_type, buffer->user_buf.package_sel);
        DEBUG_PRINT("%s:%d,strideY= %d,strideC = %d , offset_YC = %d\n",
                    __func__, __LINE__,
                    buffer->user_buf.strideY, buffer->user_buf.strideC, buffer->user_buf.offset_YC);

#ifdef __OMXVENC_FILE_IN_SAVE__

        if ((g_pFiletoEnc != NULL) && (buffer->user_buf.data_len != 0))
        {
           // fwrite(pMetaData->bufferaddr, 1, buffer->data_len, g_pFiletoEnc);
        }
#endif
    }
    else
    {
        DEBUG_PRINT_ERROR("%s,%d,format = %d not support storeMateDate now!!\n", __func__, __LINE__, p_private_handle->format);
    }

    return 0;
}

#endif

static OMX_ERRORTYPE use_buffer_internal(OMX_COMPONENT_PRIVATE* pcom_priv,
        OMX_INOUT OMX_BUFFERHEADERTYPE** omx_bufhdr,
        OMX_IN OMX_PTR app_data,
        OMX_IN OMX_U32 port,
        OMX_IN OMX_U32 bytes,
        OMX_IN OMX_U8* buffer)
{
    OMX_ERRORTYPE error = OMX_ErrorNone;
    OMX_BUFFERHEADERTYPE* pomx_buf = NULL;
    OMX_PORT_PRIVATE* port_priv = NULL;
    OMX_U32 i = 0;
    OMX_S32 ret = -1;
    OMX_U32 buf_size = 0, buf_cnt = 0;

    HI_U32 Phyaddr, BufSize;

    venc_user_info* pvenc_buf = NULL;

    OMX_CHECK_ARG_RETURN(pcom_priv == NULL);
    OMX_CHECK_ARG_RETURN(buffer == NULL);

    port_priv = &pcom_priv->m_port[port];
    buf_cnt   = port_priv->port_def.nBufferCountActual;
    buf_size  = port_priv->port_def.nBufferSize;

    if (bytes != buf_size)
    {
        DEBUG_PRINT_ERROR("[UB] Error: buf size invalid, bytes = %lu, buf_size = %lu\n", bytes, buf_size);
        return OMX_ErrorBadParameter;
    }

    /* find an idle buffer slot */
    for (i = 0; i < buf_cnt; i++)
    {
        if (bit_absent(&port_priv->m_buf_cnt, i))
        { break; }
    }

    if (i >= buf_cnt)
    {
        DEBUG_PRINT_ERROR("[UB] Error: no Free buffer heads found\n");
        return OMX_ErrorInsufficientResources;
    }

    ret = HI_MMZ_GetPhyaddr(buffer, &Phyaddr, &BufSize);
    if (ret < 0)
    {
        DEBUG_PRINT_ERROR("%s() HI_MMZ_GetPhyaddr error!\n", __func__);
        return OMX_ErrorHardware;
    }

    pomx_buf = (OMX_BUFFERHEADERTYPE*)malloc(sizeof(OMX_BUFFERHEADERTYPE));
    pvenc_buf = (venc_user_info*)malloc(sizeof(venc_user_info));

    if (!pomx_buf || !pvenc_buf)
    {
        DEBUG_PRINT_ERROR("[UB] Error: alloc omx buffer head failed\n");
        error = OMX_ErrorInsufficientResources;
        goto error_exit;
    }
    memset(pomx_buf, 0, sizeof(OMX_BUFFERHEADERTYPE));
    memset(pvenc_buf, 0, sizeof(venc_user_info));

    /* skip buffer allocation, direct bind */
    pvenc_buf->user_buf.dir = (enum venc_port_dir)port_priv->port_def.eDir;
    pvenc_buf->user_buf.client_data  = (HI_VIRT_ADDR_T)(long)pomx_buf;

    pvenc_buf->ion_handle     = NULL;
    pvenc_buf->bufferaddr     = buffer;
    pvenc_buf->user_buf.bufferaddr_Phy = Phyaddr;
    pvenc_buf->user_buf.buffer_size    = bytes;

    pvenc_buf->user_buf.data_len = 0;
    pvenc_buf->user_buf.offset   = 0;
    pvenc_buf->user_buf.pmem_fd  = 0;
    pvenc_buf->user_buf.mmaped_size = bytes;

    if (pvenc_buf->user_buf.dir == PORT_DIR_INPUT)
    {
        pvenc_buf->user_buf.offset_YC  = ALIGN_UP((pcom_priv->m_port[0].port_def.format.video.nFrameWidth * pcom_priv->m_port[0].port_def.format.video.nFrameHeight), 16);
    }

    if (PORT_DIR_OUTPUT == pvenc_buf->user_buf.dir)
    {
        if (venc_mmap_kerel_vir(&(pcom_priv->drv_ctx), &(pvenc_buf->user_buf)) < 0)
        {
            DEBUG_PRINT_ERROR("[AB]Error: venc_mmap_kerel_vir failed\n");
            error =  OMX_ErrorUndefined;
            goto error_exit;
        }
    }

    /* init OMX buffer head */
    CONFIG_VERSION_SIZE(pomx_buf , OMX_BUFFERHEADERTYPE);
    pomx_buf->pBuffer                = pvenc_buf->bufferaddr;  //�û�̬�����ַ
    pomx_buf->nAllocLen                = pvenc_buf->user_buf.buffer_size;  //���볤��
    pomx_buf->nOffset                = 0;
    pomx_buf->pAppPrivate            = app_data;

    if (INPUT_PORT_INDEX == port)
    {
        pomx_buf->pOutputPortPrivate    = NULL;
        pomx_buf->pInputPortPrivate    = (OMX_PTR)pvenc_buf;
        pomx_buf->nInputPortIndex    = port_priv->port_def.nPortIndex;
    }
    else
    {
        pomx_buf->pInputPortPrivate    = NULL;
        pomx_buf->pOutputPortPrivate    = (OMX_PTR)pvenc_buf;
        pomx_buf->nOutputPortIndex   = port_priv->port_def.nPortIndex;
    }

    *omx_bufhdr = pomx_buf;
    bit_set(&port_priv->m_buf_cnt, i);

    port_priv->m_omx_bufhead[i] = pomx_buf;
    port_priv->m_venc_bufhead[i] = pvenc_buf;

    DEBUG_PRINT_STREAM("[UB] Use %s buffer %d success: phyaddr = %x, size = %d\n",
                       (port == INPUT_PORT_INDEX) ? "in" : "out", (int)i, pvenc_buf->user_buf.bufferaddr_Phy, pvenc_buf->user_buf.buffer_size);

    return OMX_ErrorNone;

error_exit:
    if (pvenc_buf)
    {
        free(pvenc_buf);
        pvenc_buf = NULL;
    }

    if (pomx_buf)
    {
        free(pomx_buf);
        pomx_buf = NULL;
    }
    DEBUG_PRINT_ERROR("[UB] Use %s buffer %d failed\n", (port == OUTPUT_PORT_INDEX) ? "out" : "in", (int)i);

    return error;
}

#ifdef ANDROID
static OMX_ERRORTYPE use_android_native_buffer_internal(
    OMX_COMPONENT_PRIVATE* pcom_priv,
    OMX_INOUT OMX_BUFFERHEADERTYPE** omx_bufhdr,
    OMX_IN OMX_PTR app_data,
    OMX_IN OMX_U32 port,
    OMX_IN OMX_U32 bytes,
    OMX_IN OMX_U8* p_handle)
{
    OMX_U32 i = 0;
    OMX_S32 ret = -1;
    OMX_U32 buf_size = 0, buf_cnt = 0;
    OMX_ERRORTYPE error = OMX_ErrorNone;
    OMX_PORT_PRIVATE* port_priv = NULL;
    OMX_BUFFERHEADERTYPE* pomx_buf = NULL;
    OMX_U8* UserVirAddr = NULL;

    private_handle_t* p_private_handle = (private_handle_t*)p_handle;

    venc_user_info* pvenc_buf = NULL;

    OMX_CHECK_ARG_RETURN(pcom_priv == NULL);
    OMX_CHECK_ARG_RETURN(p_handle == NULL);

    DEBUG_PRINT("p_private_handle = 0x%x,payaddr = %d,width = %d,height = %d\n",
                p_private_handle, p_private_handle->ion_phy_addr,
                p_private_handle->width,
                p_private_handle->height);
    OMX_CHECK_ARG_RETURN(p_private_handle->ion_phy_addr == 0);

    port_priv = &pcom_priv->m_port[port];
    buf_size = port_priv->port_def.nBufferSize;
    buf_cnt = port_priv->port_def.nBufferCountActual;

    if (bytes != buf_size)
    {
        DEBUG_PRINT_ERROR("[UB] Error: buf size invalid, bytes = %ld, buf_size = %ld\n", bytes, buf_size);
        return OMX_ErrorBadParameter;
    }

    /* find an idle buffer slot */
    for (i = 0; i < buf_cnt; i++)
    {
        if (bit_absent(&port_priv->m_buf_cnt, i))
        { break; }
    }

    if (i >= buf_cnt)
    {
        DEBUG_PRINT_ERROR("[UB] Error: no Free buffer heads found\n");
        return OMX_ErrorInsufficientResources;
    }

    UserVirAddr = p_private_handle->base;//HI_MEM_Map(p_private_handle->ion_phy_addr, bytes);
    if (NULL ==  UserVirAddr)
    {
        DEBUG_PRINT_ERROR("%s() HI_MEM_Map error!\n", __func__);
        return OMX_ErrorUndefined;
    }

    pomx_buf = (OMX_BUFFERHEADERTYPE*)malloc(sizeof(OMX_BUFFERHEADERTYPE));
    if (!pomx_buf)
    {
        DEBUG_PRINT_ERROR("[UB] Error: alloc omx buffer pomx_buf failed\n");
        error = OMX_ErrorInsufficientResources;
        goto error_exit0;
    }

    pvenc_buf = (venc_user_info*)malloc(sizeof(venc_user_info));
    if (!pvenc_buf)
    {
        DEBUG_PRINT_ERROR("[UB] Error: alloc omx buffer pvenc_buf failed\n");
        error = OMX_ErrorInsufficientResources;
        goto error_exit1;
    }

    memset(pomx_buf,  0, sizeof(OMX_BUFFERHEADERTYPE));
    memset(pvenc_buf, 0, sizeof(venc_user_info));

    /* skip buffer allocation, direct bind */
    pvenc_buf->user_buf.dir         = (enum venc_port_dir)port_priv->port_def.eDir;
    pvenc_buf->user_buf.client_data    = (HI_VIRT_ADDR_T)pomx_buf;

    pvenc_buf->ion_handle     = p_handle;
    pvenc_buf->bufferaddr      = UserVirAddr;
    pvenc_buf->user_buf.bufferaddr_Phy = p_private_handle->ion_phy_addr;
    pvenc_buf->user_buf.buffer_size    = bytes;

    pvenc_buf->user_buf.data_len        = 0;
    pvenc_buf->user_buf.offset          = 0;
    pvenc_buf->user_buf.pmem_fd          = 0;
    pvenc_buf->user_buf.mmaped_size      = bytes;

    if (pvenc_buf->user_buf.dir == INPUT_PORT_INDEX)
    {
        pvenc_buf->user_buf.offset_YC   = ALIGN_UP((pcom_priv->m_port[0].port_def.format.video.nFrameWidth * pcom_priv->m_port[0].port_def.format.video.nFrameHeight), 16);
    }

    if (PORT_DIR_OUTPUT == pvenc_buf->user_buf.dir)
    {
        if (venc_mmap_kerel_vir(&(pcom_priv->drv_ctx), &(pvenc_buf->user_buf)) < 0)
        {
            DEBUG_PRINT_ERROR("[AB]Error: venc_mmap_kerel_vir failed\n");
            error =  OMX_ErrorUndefined;
            goto error_exit2;
        }
    }

    /* init OMX buffer head */
    CONFIG_VERSION_SIZE(pomx_buf , OMX_BUFFERHEADERTYPE);
    pomx_buf->pBuffer                = p_handle; //pvenc_buf->bufferaddr;   //not �û�̬�����ַ
    pomx_buf->nSize                    = sizeof(OMX_BUFFERHEADERTYPE);
    pomx_buf->nVersion.nVersion       = OMX_VERSION;
    pomx_buf->nAllocLen                = bytes;  //���볤��
    pomx_buf->nOffset                = 0;
    pomx_buf->pAppPrivate            = app_data;

    if (INPUT_PORT_INDEX == port)
    {
        pomx_buf->pOutputPortPrivate    = NULL;
        pomx_buf->pInputPortPrivate    = (OMX_PTR)pvenc_buf;
        pomx_buf->nInputPortIndex    = port_priv->port_def.nPortIndex;
    }
    else
    {
        pomx_buf->pInputPortPrivate       = NULL;
        pomx_buf->pOutputPortPrivate    = (OMX_PTR)pvenc_buf;
        pomx_buf->nOutputPortIndex   = port_priv->port_def.nPortIndex;
    }

    *omx_bufhdr = pomx_buf;
    bit_set(&port_priv->m_buf_cnt, i);

    port_priv->m_omx_bufhead[i] = pomx_buf;
    port_priv->m_venc_bufhead[i] = pvenc_buf;

    DEBUG_PRINT_STREAM("[UB] Use %s buffer %d success: phyaddr = %x, size = %d\n",
                       (port == INPUT_PORT_INDEX) ? "in" : "out", (int)i, pvenc_buf->user_buf.bufferaddr_Phy, pvenc_buf->user_buf.buffer_size);

    return OMX_ErrorNone;

error_exit2:
    free(pvenc_buf);
    pvenc_buf = NULL;
error_exit1:
    free(pomx_buf);
    pomx_buf = NULL;
error_exit0:

    DEBUG_PRINT_ERROR("[UB] Use %s buffer %d failed\n", (port == OUTPUT_PORT_INDEX) ? "out" : "in", (int)i);

    return error;
}
#endif

static OMX_ERRORTYPE allocate_buffer_internal(OMX_COMPONENT_PRIVATE* pcom_priv,
        OMX_INOUT OMX_BUFFERHEADERTYPE** omx_bufhdr,
        OMX_IN OMX_PTR app_data,
        OMX_IN OMX_U32 port,
        OMX_IN OMX_U32 bytes)
{
    OMX_ERRORTYPE error = OMX_ErrorNone;
    OMX_BUFFERHEADERTYPE* pomx_buf = NULL;
    OMX_PORT_PRIVATE* port_priv = NULL;

    OMX_U32 i = 0;
    OMX_U32 buf_size = 0, buf_cnt = 0;

    venc_user_info* pvenc_buf = NULL;

    OMX_CHECK_ARG_RETURN(pcom_priv == NULL);

    port_priv = &pcom_priv->m_port[port];
    buf_cnt   = port_priv->port_def.nBufferCountActual;

    /*be careful that the bytes isn't match with the allac size in fact*/
    if (port == INPUT_PORT_INDEX)
    {
        buf_size  = FRAME_SIZE(port_priv->port_def.format.video.nFrameHeight, ALIGN_UP(port_priv->port_def.format.video.nStride, 16)) + 64;
    }
    else
    {
        buf_size  = port_priv->port_def.nBufferSize;
        /* check alloc bytes */
        if (bytes < buf_size)
        {
            DEBUG_PRINT_ERROR("[AB]Error: Requested %ld, espected %ld\n",
                              (OMX_S32)bytes, (OMX_S32)port_priv->port_def.nBufferSize);
            return OMX_ErrorBadParameter;
        }
    }

    /* find an idle buffer slot */
    for (i = 0; i < buf_cnt; i++)
    {
        if (bit_absent(&port_priv->m_buf_cnt, i))
        { break; }
    }

    if (i >= buf_cnt)
    {
        DEBUG_PRINT_ERROR("[AB]Error: no Free buffer heads found\n");
        return OMX_ErrorInsufficientResources;
    }

    pomx_buf = (OMX_BUFFERHEADERTYPE*)malloc(sizeof(OMX_BUFFERHEADERTYPE));
    pvenc_buf = (venc_user_info*)malloc(sizeof(venc_user_info));

    if (!pomx_buf || !pvenc_buf)
    {
        DEBUG_PRINT_ERROR("[AB]Error:alloc omx buffer head failed\n");
        error = OMX_ErrorInsufficientResources;
        goto error_exit0;
    }
    memset(pomx_buf, 0, sizeof(OMX_BUFFERHEADERTYPE));
    memset(pvenc_buf, 0, sizeof(venc_user_info));

    pvenc_buf->user_buf.dir = (enum venc_port_dir)port_priv->port_def.eDir;

    if (alloc_contigous_buffer(buf_size, port_priv->port_def.nBufferAlignment, pvenc_buf) < 0)
    {
        DEBUG_PRINT_ERROR("[AB]Error: alloc_contigous_buffer failed\n");
        error =  OMX_ErrorUndefined;
        goto error_exit0;
    }

    pvenc_buf->user_buf.client_data = (HI_VIRT_ADDR_T)(long)pomx_buf;
    if (pvenc_buf->user_buf.dir == PORT_DIR_INPUT)
    {
        pvenc_buf->user_buf.offset_YC   = ALIGN_UP((pcom_priv->m_port[0].port_def.format.video.nFrameWidth * pcom_priv->m_port[0].port_def.format.video.nFrameHeight), 16);
    }

    if (PORT_DIR_OUTPUT == pvenc_buf->user_buf.dir)
    {
        if (venc_mmap_kerel_vir(&(pcom_priv->drv_ctx), &(pvenc_buf->user_buf)) < 0)
        {
            DEBUG_PRINT_ERROR("[AB]Error: venc_mmap_kerel_vir failed\n");
            error =  OMX_ErrorUndefined;
            goto error_exit1;
        }
    }

    /* init buffer head */
    CONFIG_VERSION_SIZE(pomx_buf, OMX_BUFFERHEADERTYPE);
    pomx_buf->pBuffer                = pvenc_buf->bufferaddr;  //�û�̬�����ַ
    pomx_buf->nAllocLen                = pvenc_buf->user_buf.buffer_size;  //���볤��
    pomx_buf->nOffset                = 0;
    pomx_buf->pAppPrivate            = app_data;

    if (port == INPUT_PORT_INDEX)
    {
        pomx_buf->pOutputPortPrivate = NULL;
        pomx_buf->pInputPortPrivate    = (OMX_PTR)pvenc_buf;
        pomx_buf->nInputPortIndex    = port_priv->port_def.nPortIndex;
    }
    else
    {
        pomx_buf->pInputPortPrivate  = NULL;
        pomx_buf->pOutputPortPrivate    = (OMX_PTR)pvenc_buf;
        pomx_buf->nOutputPortIndex   = port_priv->port_def.nPortIndex;
    }

    *omx_bufhdr = pomx_buf;

    /* mark buffer to be allocated, used */
    bit_set(&port_priv->m_usage_bitmap, i);
    bit_set(&port_priv->m_buf_cnt, i);

    port_priv->m_omx_bufhead[i] = pomx_buf;
    port_priv->m_venc_bufhead[i] = pvenc_buf;

    DEBUG_PRINT("alloc %s buffer %ld success\n",
                (port == INPUT_PORT_INDEX) ? "input" : "output", (OMX_S32)i);
    return OMX_ErrorNone;

error_exit1:
    free_contigous_buffer(pvenc_buf);
error_exit0:
    if (pvenc_buf)
    {
        free(pvenc_buf);
        pvenc_buf = NULL;
    }

    if (pomx_buf)
    {
        free(pomx_buf);
        pomx_buf = NULL;
    }
    DEBUG_PRINT_ERROR("[AB]alloc %s buffer %ld failed\n",
                      (port == OUTPUT_PORT_INDEX) ? "output" : "input", (OMX_S32)i);
    return error;
}

static OMX_ERRORTYPE free_buffer_internal(OMX_COMPONENT_PRIVATE* pcom_priv,
        OMX_IN OMX_U32 port, OMX_IN OMX_BUFFERHEADERTYPE* omx_bufhdr)
{
    OMX_PORT_PRIVATE* port_priv = NULL;

    OMX_U32 i;

    venc_user_info* puser_buf = NULL;

    port_priv = &pcom_priv->m_port[port];

    /* santity check */
    for (i = 0; i < port_priv->port_def.nBufferCountActual; i++)
    {
        if (omx_bufhdr == port_priv->m_omx_bufhead[i])
        {
            break;
        }
    }

    if (i >= port_priv->port_def.nBufferCountActual)
    {
        DEBUG_PRINT_ERROR("no buffers found for address[%p]", omx_bufhdr);
        return OMX_ErrorBadParameter;
    }

    if (bit_absent(&port_priv->m_buf_cnt, i))
    {
        DEBUG_PRINT_ERROR("buffer 0x%p not been usaged?", omx_bufhdr);
        return OMX_ErrorBadParameter;
    }
    else
    {
        bit_clear(&port_priv->m_buf_cnt, i);
    }

    if (OUTPUT_PORT_INDEX == port)
    {
        puser_buf = (venc_user_info*)(omx_bufhdr->pOutputPortPrivate);
    }
    else
    {
        puser_buf = (venc_user_info*)(omx_bufhdr->pInputPortPrivate);
    }

    if (puser_buf)
    {
        if (port_priv->port_def.bPopulated)
        {
            port_priv->port_def.bPopulated = OMX_FALSE;
        }

        if (bit_present(&port_priv->m_usage_bitmap, i))
        {
            if (PORT_DIR_OUTPUT == puser_buf->user_buf.dir)
            {
                if (venc_unmmap_kerel_vir(&(pcom_priv->drv_ctx), &(puser_buf->user_buf)) < 0)
                {
                    DEBUG_PRINT_ERROR("[AB]Error: venc_unmmap_kerel_vir failed\n");
                    return OMX_ErrorHardware;
                }
            }

            free_contigous_buffer(puser_buf);
            bit_clear(&port_priv->m_usage_bitmap, i);
        }

        free(puser_buf);
        puser_buf = NULL;
    }

    free(omx_bufhdr);
    omx_bufhdr = NULL;

    port_priv->m_omx_bufhead[i] = NULL;
    port_priv->m_venc_bufhead[i] = NULL;

    DEBUG_PRINT("[FB] %s exit!\n", __func__);
    return OMX_ErrorNone;
}

static OMX_ERRORTYPE omx_flush_port( OMX_COMPONENT_PRIVATE* pcom_priv,
                                     OMX_U32 port)
{
    OMX_PORT_PRIVATE* port_priv = NULL;

    if (port == OUTPUT_PORT_INDEX || port == OMX_ALL)
    {
        port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
        port_priv->m_port_flushing = OMX_TRUE;
    }

    if (port == INPUT_PORT_INDEX || port == OMX_ALL)
    {
        port_priv = &pcom_priv->m_port[INPUT_PORT_INDEX];
        port_priv->m_port_flushing = OMX_TRUE;
    }

    if (channel_flush_port(&pcom_priv->drv_ctx, port, 1) < 0)
    {
        DEBUG_PRINT_ERROR("ioctl flush port failed\n");
        return OMX_ErrorHardware;
    }

    return OMX_ErrorNone;
}

static void return_outbuffers(OMX_COMPONENT_PRIVATE* pcom_priv)
{
    OMX_PORT_PRIVATE* port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
    OMX_U32 param1 = 0, param2 = 0, ident = 0;
    OMX_U32 Cnt = 0;
    (void)pthread_mutex_lock(&pcom_priv->m_lock);
    while ((get_q_size(&pcom_priv->m_ftb_q) > 0) && (Cnt < 100))
    {
        Cnt++;
        if (pop_entry(&pcom_priv->m_ftb_q, &param1, &param2, &ident) != 0)
        {
            DEBUG_PRINT("pop entry state\n");
        }

        if (ident == OMX_GENERATE_FTB )
        {
            port_priv->m_buf_pend_cnt++;
        }

        if (fill_buffer_done(pcom_priv, (OMX_BUFFERHEADERTYPE*)param1) != 0)
        {
            DEBUG_PRINT("fill buffer done state err!\n");
        }
    }

    if (Cnt >= 100)
    {
        DEBUG_PRINT_ERROR("queue size invalid! There may be an endless cycle!\n");
    }

    (void)pthread_mutex_unlock(&pcom_priv->m_lock);
}


static void return_inbuffers(OMX_COMPONENT_PRIVATE* pcom_priv)
{
    OMX_PORT_PRIVATE* port_priv = &pcom_priv->m_port[INPUT_PORT_INDEX];
    OMX_U32 param1 = 0, param2 = 0, ident = 0;
    OMX_U32 Cnt = 0;

    (void)pthread_mutex_lock(&pcom_priv->m_lock);
    while ((get_q_size(&pcom_priv->m_etb_q) > 0) && (Cnt < 100))
    {
        Cnt++;
        if (pop_entry(&pcom_priv->m_etb_q, &param1, &param2, &ident) != 0)
        {
            DEBUG_PRINT("pop entry state\n");
        }

        if (ident == OMX_GENERATE_ETB)
        {
            port_priv->m_buf_pend_cnt++;
        }

        if (empty_buffer_done(pcom_priv, (OMX_BUFFERHEADERTYPE*)param1) != 0)
        {
            DEBUG_PRINT("empty buffer done state is err!\n");
        }
    }

    if (Cnt >= 100)
    {
        DEBUG_PRINT_ERROR("queue size invalid! There may be an endless cycle!\n");
    }

    (void)pthread_mutex_unlock(&pcom_priv->m_lock);
}

static OMX_ERRORTYPE get_supported_profile_level(OMX_COMPONENT_PRIVATE* pcomp_priv, OMX_VIDEO_PARAM_PROFILELEVELTYPE* profileLevelType)
{
    OMX_U32 max_num;
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    const struct codec_profile_level* pinfo = NULL;

    OMX_CHECK_ARG_RETURN(pcomp_priv == NULL);
    OMX_CHECK_ARG_RETURN(profileLevelType == NULL);

    if (profileLevelType->nPortIndex != OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT_ERROR("%s(): should be queries on Input port only (%lu)\n", __func__, profileLevelType->nPortIndex);
        ret = OMX_ErrorBadPortIndex;
    }

    /* FIXME : profile & level may not correct! */
    if (!strncmp((OMX_STRING)pcomp_priv->m_role, OMX_ROLE_VIDEO_ENCODER_AVC, sizeof(OMX_ROLE_VIDEO_ENCODER_AVC)))
    {
        pinfo = avc_profile_level_list;
        max_num = COUNTOF(avc_profile_level_list);
    }
#ifdef OMXVENC_SUPPORT_HEVC
    else if (!strncmp((OMX_STRING)pcomp_priv->m_role, OMX_ROLE_VIDEO_ENCODER_HEVC, sizeof(OMX_ROLE_VIDEO_ENCODER_HEVC)))
    {
        pinfo = hevc_profile_level_list;
        max_num = COUNTOF(hevc_profile_level_list);
    }
#endif
    else
    {
        DEBUG_PRINT_ERROR("%s(): no profile & level found for %lu(%s)\n", __func__, profileLevelType->nPortIndex, (OMX_STRING)pcomp_priv->m_role);
        return OMX_ErrorUndefined;
    }

    if (profileLevelType->nIndex >= max_num)
    {
        DEBUG_PRINT_ERROR("%s(): ProfileIndex(%lu) exceed!\n", __func__, profileLevelType->nIndex);
        return OMX_ErrorNoMore;
    }

    pinfo += profileLevelType->nIndex;
    profileLevelType->eProfile = pinfo->profile;
    profileLevelType->eLevel   = pinfo->level;

    return ret;
}

static OMX_ERRORTYPE get_current_profile_level(OMX_COMPONENT_PRIVATE* pcomp_priv, OMX_VIDEO_PARAM_PROFILELEVELTYPE* profileLevelType)
{
    venc_chan_cfg* pVencChnCfg = NULL;
    OMX_CHECK_ARG_RETURN(pcomp_priv == NULL);
    OMX_CHECK_ARG_RETURN(profileLevelType == NULL);

    if (profileLevelType->nPortIndex != OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT_ERROR("%s(): should be queries on Input port only (%lu)\n", __func__, profileLevelType->nPortIndex);
        return  OMX_ErrorBadPortIndex;
    }

    pVencChnCfg = &(pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg);

    /* FIXME : profile & level may not correct! */
    if (!strncmp((OMX_STRING)pcomp_priv->m_role, OMX_ROLE_VIDEO_ENCODER_AVC, sizeof(OMX_ROLE_VIDEO_ENCODER_AVC)))
    {
        switch (pVencChnCfg->VencUnfAttr.enVencProfile)
        {
            case HI_UNF_H264_PROFILE_BASELINE:
                profileLevelType->eProfile = OMX_VIDEO_AVCProfileBaseline;
                break;

            case HI_UNF_H264_PROFILE_MAIN:
                profileLevelType->eProfile = OMX_VIDEO_AVCProfileMain;
                break;

            case HI_UNF_H264_PROFILE_HIGH:
                profileLevelType->eProfile = OMX_VIDEO_AVCProfileHigh;
                break;

            default:
                DEBUG_PRINT_ERROR("Bad parm of VencProfile %ld\n", (OMX_S32)pVencChnCfg->VencUnfAttr.enVencProfile);
                profileLevelType->eProfile = OMX_VIDEO_AVCProfileMax;
                break;
        }

    }
#ifdef OMXVENC_SUPPORT_HEVC
    else if (!strncmp((OMX_STRING)pcomp_priv->m_role, OMX_ROLE_VIDEO_ENCODER_HEVC, sizeof(OMX_ROLE_VIDEO_ENCODER_HEVC)))
    {
        profileLevelType->eProfile = OMX_VIDEO_HEVCProfileMain;
    }
#endif
    else
    {
        DEBUG_PRINT_ERROR("%s(): component roles error (%s)\n", __func__, pcomp_priv->m_role);
        return  OMX_ErrorBadParameter;
    }

    pVencChnCfg->h264Level = channel_get_current_level(pVencChnCfg->VencUnfAttr.u32Width, pVencChnCfg->VencUnfAttr.u32Height);
    switch (pVencChnCfg->h264Level)
    {
        case 10:
            profileLevelType->eLevel = OMX_VIDEO_AVCLevel1;
            break;

        case 20:
            profileLevelType->eLevel = OMX_VIDEO_AVCLevel2;
            break;

        case 21:
            profileLevelType->eLevel = OMX_VIDEO_AVCLevel21;
            break;

        case 30:
            profileLevelType->eLevel = OMX_VIDEO_AVCLevel3;
            break;

        case 31:
            profileLevelType->eLevel = OMX_VIDEO_AVCLevel31;
            break;

        case 32:
            profileLevelType->eLevel = OMX_VIDEO_AVCLevel32;
            break;

        case 41:
            profileLevelType->eLevel = OMX_VIDEO_AVCLevel41;
            break;

        default:
            DEBUG_PRINT_ERROR("Bad parm of Level %ld\n", (OMX_S32)pVencChnCfg->h264Level);
            profileLevelType->eLevel = OMX_VIDEO_AVCLevelMax;
            break;
    }

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE set_current_profile_level(OMX_COMPONENT_PRIVATE* pcomp_priv, OMX_VIDEO_PARAM_PROFILELEVELTYPE* profileLevelType)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    venc_chan_cfg* pVencChnCfg = NULL;
    OMX_CHECK_ARG_RETURN(pcomp_priv == NULL);
    OMX_CHECK_ARG_RETURN(profileLevelType == NULL);

    if (profileLevelType->nPortIndex != OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT_ERROR("%s(): should be queries on Input port only (%lu)\n", __func__, profileLevelType->nPortIndex);
        return  OMX_ErrorBadPortIndex;
    }

    if (1 == pcomp_priv->drv_ctx.venc_chan_attr.state) /* just can change profile when venc channel idle*/
    {
        ret = OMX_ErrorUnsupportedSetting;
        omx_report_error(pcomp_priv, ret);
        return ret;
    }

    pVencChnCfg = &(pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg);

    if (!strncmp((OMX_STRING)pcomp_priv->m_role, OMX_ROLE_VIDEO_ENCODER_AVC, sizeof(OMX_ROLE_VIDEO_ENCODER_AVC)))
    {
        switch (profileLevelType->eProfile)
        {
            case OMX_VIDEO_AVCProfileBaseline:
                pVencChnCfg->VencUnfAttr.enVencProfile = HI_UNF_H264_PROFILE_BASELINE;
                break;

            case OMX_VIDEO_AVCProfileMain:
                pVencChnCfg->VencUnfAttr.enVencProfile = HI_UNF_H264_PROFILE_MAIN;
                break;

            case OMX_VIDEO_AVCProfileHigh:
                pVencChnCfg->VencUnfAttr.enVencProfile = HI_UNF_H264_PROFILE_HIGH;
                break;

            default:
                DEBUG_PRINT_ERROR("Bad parm of VencProfile %ld\n", (OMX_S32)profileLevelType->eProfile);

                return OMX_ErrorBadParameter;
        }

    }
#ifdef OMXVENC_SUPPORT_HEVC
    else if (!strncmp((OMX_STRING)pcomp_priv->m_role, OMX_ROLE_VIDEO_ENCODER_HEVC, sizeof(OMX_ROLE_VIDEO_ENCODER_HEVC)))
    {
        switch (profileLevelType->eProfile)
        {
            case OMX_VIDEO_HEVCProfileMain:
                pVencChnCfg->VencUnfAttr.enVencProfile = HI_UNF_H264_PROFILE_MAIN;  //fix me
                break;

            default:
                DEBUG_PRINT_ERROR("Bad parm of VencProfile %ld\n", (OMX_S32)profileLevelType->eProfile);

                return OMX_ErrorBadParameter;
        }
    }
#endif
    else
    {
        DEBUG_PRINT_ERROR("%s(): component roles error (%s)\n", __func__, pcomp_priv->m_role);

        return  OMX_ErrorBadParameter;
    }

    if ((pcomp_priv->m_state >= OMX_StateIdle) && (pcomp_priv->m_state <= OMX_StateWaitForResources))
    {
        if (channel_set_attr(&(pcomp_priv->drv_ctx)) < 0)
        {
            DEBUG_PRINT_ERROR("ERROR: channel set attr failed!\n");
            omx_report_error(pcomp_priv, OMX_ErrorUnsupportedSetting);
            return OMX_ErrorUnsupportedSetting;
        }
    }

    return OMX_ErrorNone;
}

static OMX_U32 OMX_Convert_PIX_Format_StoreType(OMX_COLOR_FORMATTYPE Format)
{
    OMX_U32 Ret = HI_SUCCESS;

    switch (Format)
    {
        case OMX_COLOR_FormatYUV420Planar:
        case OMX_COLOR_FormatAndroidOpaque:
            Ret = OMX_VENC_STORE_PLANNAR;
            break;
        case OMX_COLOR_FormatYUV420SemiPlanar:
            Ret = OMX_VENC_STORE_SEMIPLANNAR;
            break;
        case OMX_QCOM_COLOR_FormatYVU420SemiPlanar:
            Ret = OMX_VENC_STORE_SEMIPLANNAR;
            break;
        case OMX_COLOR_FormatYUV422Planar:
            Ret = OMX_VENC_STORE_PLANNAR;
            break;
        case OMX_COLOR_FormatYUV422SemiPlanar:
            Ret = OMX_VENC_STORE_SEMIPLANNAR;
            break;
        case OMX_COLOR_FormatYCbYCr:
            Ret = OMX_VENC_STORE_PACKAGE;
            break;
        case OMX_COLOR_FormatYCrYCb :
            Ret = OMX_VENC_STORE_PACKAGE;
            break;
        case OMX_COLOR_FormatCbYCrY:
            Ret = OMX_VENC_STORE_PACKAGE;
            break;
        case OMX_COLOR_FormatCrYCbY:
            Ret = OMX_VENC_STORE_PACKAGE;
            break;
        case OMX_COLOR_FormatYVU420SemiPlanar:
            Ret = OMX_VENC_STORE_SEMIPLANNAR;
            break;
        case OMX_COLOR_FormatYVU422SemiPlanar:
            Ret = OMX_VENC_STORE_SEMIPLANNAR;
            break;
        case OMX_COLOR_FormatYVU420Planar:
            Ret = OMX_VENC_STORE_PLANNAR;
            break;
        default:
            Ret = OMX_VENC_STORE_SEMIPLANNAR;
            break;
    }

    return Ret;
}

static OMX_U32 OMX_Convert_PIX_Format_SampleType(OMX_COLOR_FORMATTYPE Format)
{
    OMX_U32 Ret = HI_SUCCESS;

    switch (Format)
    {
        case OMX_COLOR_FormatYUV420Planar:
        case OMX_COLOR_FormatAndroidOpaque:
            Ret = OMX_VENC_YUV_420;
            break;
        case OMX_COLOR_FormatYUV420SemiPlanar:
            Ret = OMX_VENC_YUV_420;
            break;
        case OMX_QCOM_COLOR_FormatYVU420SemiPlanar:
            Ret = OMX_VENC_YUV_420;
            break;
        case OMX_COLOR_FormatYUV422Planar:
            Ret = OMX_VENC_YUV_422;
            break;
        case OMX_COLOR_FormatYUV422SemiPlanar:
            Ret = OMX_VENC_YUV_422;
            break;
        case OMX_COLOR_FormatYCbYCr:
            Ret = OMX_VENC_YUV_422;
            break;
        case OMX_COLOR_FormatYCrYCb :
            Ret = OMX_VENC_YUV_422;
            break;
        case OMX_COLOR_FormatCbYCrY:
            Ret = OMX_VENC_YUV_422;
            break;
        case OMX_COLOR_FormatCrYCbY:
            Ret = OMX_VENC_YUV_422;
            break;
        case OMX_COLOR_FormatYVU420SemiPlanar:
            Ret = OMX_VENC_YUV_420;
            break;
        case OMX_COLOR_FormatYVU422SemiPlanar:
            Ret = OMX_VENC_YUV_422;
            break;
        case OMX_COLOR_FormatYVU420Planar:
            Ret = OMX_VENC_YUV_420;
            break;
        default:
            Ret = OMX_VENC_YUV_420;
            break;
    }

    return Ret;
}

static OMX_U32 OMX_Convert_PIX_Format_PackageSel(OMX_COLOR_FORMATTYPE Format)
{
    OMX_U32 Ret = HI_SUCCESS;

    switch (Format)
    {
        case OMX_COLOR_FormatYUV420Planar:
        case OMX_COLOR_FormatAndroidOpaque:
            Ret = OMX_VENC_U_V;
            break;
        case OMX_COLOR_FormatYUV420SemiPlanar:
            Ret = OMX_VENC_U_V;
            break;
        case OMX_QCOM_COLOR_FormatYVU420SemiPlanar:
            Ret = OMX_VENC_V_U;
            break;
        case OMX_COLOR_FormatYUV422Planar:
            Ret = OMX_VENC_U_V;
            break;
        case OMX_COLOR_FormatYUV422SemiPlanar:
            Ret = OMX_VENC_U_V;
            break;
        case OMX_COLOR_FormatYCbYCr:
            Ret = OMX_VENC_PACKAGE_Y0UY1V;
            break;
        case OMX_COLOR_FormatYCrYCb :
            Ret = OMX_VENC_PACKAGE_Y0VY1U;
            break;
        case OMX_COLOR_FormatCbYCrY:
            Ret = OMX_VENC_PACKAGE_UY0VY1;
            break;
        case OMX_COLOR_FormatCrYCbY:
            Ret = OMX_VENC_PACKAGE_UY0VY1;
            break;
        case OMX_COLOR_FormatYVU420SemiPlanar:
            Ret = OMX_VENC_V_U;
            break;
        case OMX_COLOR_FormatYVU422SemiPlanar:
            Ret = OMX_VENC_V_U;
            break;
        case OMX_COLOR_FormatYVU420Planar:
            Ret = OMX_VENC_V_U;
            break;
        default:
            Ret = OMX_VENC_U_V;
            break;
    }

    return Ret;
}

static OMX_U32 OMX_Convert_PIX_Format(OMX_COLOR_FORMATTYPE Format, OMX_U32 flag)
{
    OMX_U32 Ret = HI_SUCCESS;

    if (flag == 0) /*YUVStoreType*/
    {
        Ret = OMX_Convert_PIX_Format_StoreType(Format);
    }
    else if (flag == 1) /*YUVSampleType*/
    {
        Ret = OMX_Convert_PIX_Format_SampleType(Format);
    }
    else if (flag == 2) /*PackageSel*/
    {
        Ret = OMX_Convert_PIX_Format_PackageSel(Format);
    }
    else
    {
        Ret = HI_FALSE;
    }

    return Ret;
}

static void convert_format_info(OMX_IN OMX_BUFFERHEADERTYPE *pomx_buf,
                    venc_user_info *puser_buf, OMX_PORT_PRIVATE *port_priv)
{
    puser_buf->user_buf.picWidth     = port_priv->port_def.format.video.nFrameWidth;
    puser_buf->user_buf.picHeight    = port_priv->port_def.format.video.nFrameHeight;
    puser_buf->user_buf.store_type   = OMX_Convert_PIX_Format(port_priv->port_def.format.video.eColorFormat, 0);
    puser_buf->user_buf.sample_type  = OMX_Convert_PIX_Format(port_priv->port_def.format.video.eColorFormat, 1);
    puser_buf->user_buf.package_sel  = OMX_Convert_PIX_Format(port_priv->port_def.format.video.eColorFormat, 2);
    puser_buf->user_buf.data_len     = pomx_buf->nFilledLen;
    puser_buf->user_buf.offset       = pomx_buf->nOffset;

#ifdef __OMXVENC_FILE_IN_SAVE__
    if ((g_pU != NULL) && (g_pV != NULL))
    {
        if (port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatYUV420SemiPlanar)
        {
            char* YuvFile = puser_buf->bufferaddr;
            char* U_temp = g_pU;
            char* V_temp = g_pV;
            int i_temp = 0;
            int Y_size = (puser_buf->user_buf.picWidth * puser_buf->user_buf.picHeight);
            YuvFile += Y_size;
            for (i_temp = 0; i_temp < (Y_size / 4); i_temp++)
            {
                memcpy(U_temp, YuvFile, sizeof(HI_U8));
                YuvFile++;
                U_temp++;
                memcpy(V_temp, YuvFile, sizeof(HI_U8));
                YuvFile++;
                V_temp++;
            }
            if ((g_pFiletoEnc != NULL) && (pomx_buf->nFilledLen != 0))
            {
                fwrite(puser_buf->bufferaddr, 1, Y_size, g_pFiletoEnc);
                fwrite(g_pU, 1, Y_size / 4, g_pFiletoEnc);
                fwrite(g_pV, 1, Y_size / 4, g_pFiletoEnc);
            }
        }
        else if (port_priv->port_def.format.video.eColorFormat == OMX_QCOM_COLOR_FormatYVU420SemiPlanar)
        {
            char* YuvFile = puser_buf->bufferaddr;
            char* U_temp = g_pU;
            char* V_temp = g_pV;
            int i_temp = 0;
            int Y_size = (puser_buf->user_buf.picWidth * puser_buf->user_buf.picHeight);
            YuvFile += Y_size;
            for (i_temp = 0; i_temp < (Y_size / 4); i_temp++)
            {
                memcpy(V_temp, YuvFile, sizeof(HI_U8));
                YuvFile++;
                V_temp++;
                memcpy(U_temp, YuvFile, sizeof(HI_U8));
                YuvFile++;
                U_temp++;
            }
            if ((g_pFiletoEnc != NULL) && (pomx_buf->nFilledLen != 0))
            {
                fwrite(puser_buf->bufferaddr, 1, Y_size, g_pFiletoEnc);
                fwrite(g_pU, 1, Y_size / 4, g_pFiletoEnc);
                fwrite(g_pV, 1, Y_size / 4, g_pFiletoEnc);
            }
        }
        else if ((port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatYUV420Planar)
           || (port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatAndroidOpaque))
        {
            fwrite(puser_buf->bufferaddr, 1, puser_buf->user_buf.data_len, g_pFiletoEnc);
        }
    }
#endif

    if ((port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatYUV420SemiPlanar)
        || (port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatYVU420SemiPlanar)
        || (port_priv->port_def.format.video.eColorFormat == OMX_QCOM_COLOR_FormatYVU420SemiPlanar))
    {
        puser_buf->user_buf.strideY   = ALIGN_UP(port_priv->port_def.format.video.nFrameWidth, 16);
        puser_buf->user_buf.strideC   = ALIGN_UP(port_priv->port_def.format.video.nFrameWidth, 16);
        puser_buf->user_buf.offset_YC = puser_buf->user_buf.strideY * port_priv->port_def.format.video.nFrameHeight;
    }
    else if ((port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatYUV420Planar)
             || (port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatYVU420Planar)
             || (port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatAndroidOpaque))
    {
        puser_buf->user_buf.strideY = ALIGN_UP(port_priv->port_def.format.video.nFrameWidth, 16);
        puser_buf->user_buf.strideC = ALIGN_UP((port_priv->port_def.format.video.nFrameWidth / 2), 16);

        if ((port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatYUV420Planar)
            || (port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatAndroidOpaque))
        {
            puser_buf->user_buf.offset_YC  = puser_buf->user_buf.strideY * port_priv->port_def.format.video.nFrameHeight;
            puser_buf->user_buf.offset_YCr = puser_buf->user_buf.offset_YC + puser_buf->user_buf.strideC * port_priv->port_def.format.video.nFrameHeight / 2;
        }
        else
        {
            puser_buf->user_buf.offset_YC  = puser_buf->user_buf.strideY * port_priv->port_def.format.video.nFrameHeight
                                           + puser_buf->user_buf.strideC * port_priv->port_def.format.video.nFrameHeight / 2;
            puser_buf->user_buf.offset_YCr = puser_buf->user_buf.strideY * port_priv->port_def.format.video.nFrameHeight;

        }
    }
    else if ((port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatYCbYCr)
             || (port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatYCrYCb)
             || (port_priv->port_def.format.video.eColorFormat == OMX_COLOR_FormatCbYCrY))
    {
        puser_buf->user_buf.strideY   = ALIGN_UP((port_priv->port_def.format.video.nFrameWidth * 2), 16);
        puser_buf->user_buf.strideC   = 0;
        puser_buf->user_buf.offset_YC = 0;

    }
}

static OMX_ERRORTYPE empty_this_buffer_proxy(
    OMX_COMPONENT_PRIVATE* pcom_priv,
    OMX_IN OMX_BUFFERHEADERTYPE* pomx_buf)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    venc_user_info* puser_buf = NULL;
    OMX_PORT_PRIVATE* port_priv = NULL;
    int  ret_val = 0;
    if (!pcom_priv)
    {
        DEBUG_PRINT_ERROR("[FTB]Proxy: bad parameter:null PTR\n");
        return OMX_ErrorBadParameter;
    }

    if (!pomx_buf)
    {
        DEBUG_PRINT_ERROR("[ETB]Proxy: bad parameters\n");
        ret = OMX_ErrorBadParameter;
        goto empty_error;
    }
#ifdef ENABLE_BUFFER_LOCK
    ret_val = sem_trywait(&pcom_priv->m_buf_lock);
    if(0 != ret_val)
    {
        DEBUG_PRINT_ERROR("[ETB]Proxy: give up the frame (pts = %lld)!!\n",pomx_buf->nTimeStamp);
        return pcom_priv->m_cb.EmptyBufferDone(pcom_priv->m_pcomp, pcom_priv->m_app_data, pomx_buf);
    }
#endif

    port_priv = &pcom_priv->m_port[INPUT_PORT_INDEX];

    if ((port_priv->m_port_flushing == OMX_TRUE)
        || (port_priv->m_port_reconfig == OMX_TRUE))
    {
        DEBUG_PRINT_ERROR("[ETB]Proxy: port flushing or disabled\n");
        pomx_buf->nFilledLen = 0;
        post_event(pcom_priv, (OMX_U32)pomx_buf, VENC_DONE_SUCCESS, OMX_GENERATE_EBD);

        return OMX_ErrorNone;
    }

    if (!pomx_buf->pInputPortPrivate)
    {
        DEBUG_PRINT_ERROR("[ETB]Proxy: invalid user buffer!\n");
        ret =  OMX_ErrorUndefined;
        goto empty_error;
    }

    puser_buf = (venc_user_info*)pomx_buf->pInputPortPrivate;

#ifdef ANDROID
    if (pcom_priv->m_store_metadata_buf == HI_TRUE)
    {
        if ((pomx_buf->nFilledLen != 8) && (pomx_buf->nFilledLen != 0))
        {
            DEBUG_PRINT("MetaData buffer is wrong size! "
                              "(got %lu bytes, expected 8)", pomx_buf->nFilledLen);
            ret =  OMX_ErrorUndefined;
        }

        if (pomx_buf->nFilledLen != 0)
        {
            if (omxvenc_extractGrallocData(pomx_buf->pBuffer + pomx_buf->nOffset, puser_buf, pcom_priv) != 0)
            {
                DEBUG_PRINT("omxvenc_extractGrallocData failed\n");
            }
        }
        else
        {
            convert_format_info(pomx_buf, puser_buf, port_priv);
        }
    }
#endif

    if (pcom_priv->m_store_metadata_buf != OMX_TRUE)
    {
        convert_format_info(pomx_buf, puser_buf, port_priv);
    }

    puser_buf->user_buf.timestamp0   = (HI_U32)((HI_U64)pomx_buf->nTimeStamp & 0x00000000ffffffff) ;//pomx_buf->nTimeStamp / 1e3;
    puser_buf->user_buf.timestamp1   = (HI_U32)(((HI_U64)pomx_buf->nTimeStamp) >> 32) ;
    puser_buf->user_buf.flags        = pomx_buf->nFlags;

    if (puser_buf->user_buf.flags & OMX_BUFFERFLAG_EOS)
    {
        DEBUG_PRINT_STATE("[ETB]get EOS buffer !PTS = %d, %d, len= %d\n", puser_buf->user_buf.timestamp0,puser_buf->user_buf.timestamp1,puser_buf->user_buf.data_len);
        if (puser_buf->user_buf.data_len == 0)
        {
             memset(puser_buf->bufferaddr, 0, puser_buf->user_buf.buffer_size);
        }
    }

    g_etb_cnt++;
    DEBUG_PRINT_EFTB("[ETB] VirAddr = %p,flag = 0x%lx,pts = %lld,cnt = %d\n",pomx_buf->pBuffer,
        pomx_buf->nFlags,pomx_buf->nTimeStamp,g_etb_cnt);

    DEBUG_PRINT("%s(),%d, nFilledLen:%d,nOffset:%d, timestamp0 = %d,timestamp1 = %d,bufferaddr_Phy = 0x%x\n", __func__, __LINE__,
                puser_buf->user_buf.data_len , puser_buf->user_buf.offset, puser_buf->user_buf.timestamp0, \
                puser_buf->user_buf.timestamp1, puser_buf->user_buf.bufferaddr_Phy);
    DEBUG_PRINT("%s(),%d, strideY:%d,strideC:%d, offsetYC = %d,offsetYCr= %d\n", __func__, __LINE__,
                puser_buf->user_buf.strideY , puser_buf->user_buf.strideC, puser_buf->user_buf.offset_YC, puser_buf->user_buf.offset_YCr);

    if (channel_queue_Image(&pcom_priv->drv_ctx, &(puser_buf->user_buf)) < 0)      //change to queueFrame
    {
        /*Generate an async error and move to invalid state*/
        DEBUG_PRINT_ERROR("[ETB]proxy: queue_Image failed\n");
        ret = OMX_ErrorUndefined;
        goto empty_error;
    }

#ifdef __VENC_DBG_DELAY_STAT__
    if (etb_x_id < 100)
    {
        OMX_S32 ret = 0;
        ret = gettimeofday (&TmpTime[etb_x_id][1] , NULL);
        if (ret == 0)
        {
            etb_x_id++;
        }
    }
#endif

    /////////////////////////////////////////////////////////////////////////         end
    port_priv->m_buf_pend_cnt++;

    return OMX_ErrorNone;

empty_error:

    post_event(pcom_priv, (OMX_U32)pomx_buf, (OMX_U32)VENC_DONE_FAILED, OMX_GENERATE_EBD);

    return ret;
}

static OMX_ERRORTYPE  fill_this_buffer_proxy(
    OMX_COMPONENT_PRIVATE* pcom_priv,
    OMX_IN OMX_BUFFERHEADERTYPE* pomx_buf)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    venc_user_info* puser_buf = NULL;
    OMX_PORT_PRIVATE* port_priv = NULL;

    if (!pcom_priv)
    {
        DEBUG_PRINT_ERROR("[FTB]Proxy: bad parameter:null PTR\n");
        return OMX_ErrorBadParameter;
    }

    if (!pomx_buf)
    {
        DEBUG_PRINT_ERROR("[FTB]Proxy: bad parameter\n");
        ret = OMX_ErrorBadParameter;
        goto fill_error;
    }

    port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];

    if ((port_priv->m_port_flushing == OMX_TRUE) ||
        (port_priv->m_port_reconfig == OMX_TRUE))
    {
        DEBUG_PRINT("[FTB]Proxy: port is flushing or reconfig\n");
        pomx_buf->nFilledLen = 0;
        post_event(pcom_priv, (OMX_U32)pomx_buf, (OMX_U32)VENC_DONE_SUCCESS, OMX_GENERATE_FBD);

        return OMX_ErrorNone;
    }

    ///////////////////////////////////////////////////////////////////////////////  must be change
    puser_buf = (venc_user_info*)pomx_buf->pOutputPortPrivate;
    if (!puser_buf)
    {
        DEBUG_PRINT_ERROR("[FTB]Proxy: invalid user buf\n");
        ret = OMX_ErrorUndefined;
        goto fill_error;
    }
    puser_buf->user_buf.data_len = 0;
    pomx_buf->nFilledLen = 0;

    g_ftb_cnt++;
    DEBUG_PRINT_EFTB("[FTB] VirAddr = %p,flag = 0x%lx,cnt = %d\n",pomx_buf->pBuffer,pomx_buf->nFlags,g_ftb_cnt);
    if (channel_queue_stream(&pcom_priv->drv_ctx, &(puser_buf->user_buf)) < 0)
    {
        DEBUG_PRINT_ERROR("[FTB]Proxy: fill_stream_buffer failed\n");
        return OMX_ErrorHardware;
    }
    ///////////////////////////////////////////////////////////////////////////////////// end

#ifdef __VENC_DBG_DELAY_STAT__
    if (ftb_x_id <= 100)
    {
        ret = gettimeofday (&TmpTime[ftb_x_id][4] , NULL);
        if (ret == 0)
        {
            ftb_x_id++;
        }
    }
#endif

    port_priv->m_buf_pend_cnt++;

    DEBUG_PRINT("[FTB]Proxy: fill this buffer success!\n");
    return OMX_ErrorNone;

fill_error:
    post_event(pcom_priv, (OMX_U32)pomx_buf, (OMX_U32)VENC_DONE_FAILED, OMX_GENERATE_FBD);

    return ret;
}

static void message_process_case_output_done (OMX_COMPONENT_PRIVATE *pcom_priv, venc_msginfo *venc_msg)
{
    OMX_BUFFERHEADERTYPE *pomx_buf = NULL;
    OMX_PORT_PRIVATE *port_priv = NULL;
    OMX_U32 i = 0;
    venc_user_buf *puser_buf = NULL;

    DEBUG_PRINT("%s,VENC resp output done\n", __func__);
    puser_buf = &venc_msg->buf;
    port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
    if (puser_buf->client_data == 0)
    {
        DEBUG_PRINT_ERROR(" %s,venc resp out buffer invalid\n", __func__);
        post_event(pcom_priv, 0, (OMX_U32)VENC_DONE_FAILED, OMX_GENERATE_FBD);

        return;
    }

    pomx_buf = (OMX_BUFFERHEADERTYPE*)(long)puser_buf->client_data;

    /* check buffer validate*/
    for (i = 0; i < port_priv->port_def.nBufferCountActual; i++)
    {
        if (pomx_buf == port_priv->m_omx_bufhead[i])
        {
            break;
        }
    }

    if (i >= port_priv->port_def.nBufferCountActual)
    {
        DEBUG_PRINT_ERROR("%s[%d]no buffers found for address[%p]", __func__, __LINE__, pomx_buf);

        post_event(pcom_priv, 0, (OMX_U32)VENC_DONE_FAILED, OMX_GENERATE_FBD);

        return;
    }

    DEBUG_PRINT_STREAM("[FBD] venc resp out buffer %p,"
                       " buferaddr_phy:%x, data_len:%ld,pts = %d,%d, flag = 0x%x\n", pomx_buf,
                       puser_buf->bufferaddr_Phy, (OMX_S32)puser_buf->data_len,puser_buf->timestamp0,puser_buf->timestamp1,puser_buf->flags);

    {
        HI_U64 u64Pts0 = (HI_U64)puser_buf->timestamp0;
        HI_U64 u64Pts1 = (HI_U64)puser_buf->timestamp1;
        HI_U64 u64Pts = ((u64Pts1 << 32) & 0xffffffff00000000LL) | u64Pts0;

        pomx_buf->nFilledLen = puser_buf->data_len;
        pomx_buf->nFlags     = (OMX_U32)puser_buf->flags;
        pomx_buf->nTimeStamp = (OMX_TICKS)u64Pts;
    }

    if (pomx_buf->nFlags & OMX_BUFFERFLAG_EOS)
    {
        DEBUG_PRINT_STATE("[FBD]report EOS buffer !PTS = %d, %d, len= %d\n",puser_buf->timestamp0,puser_buf->timestamp1,(HI_U32)pomx_buf->nFilledLen);
    }

    post_event(pcom_priv, (OMX_U32)pomx_buf, venc_msg->status_code, OMX_GENERATE_FBD);
}

static void message_process (OMX_COMPONENT_PRIVATE*  pcom_priv, void* message)
{
    OMX_BUFFERHEADERTYPE* pomx_buf = NULL;
    OMX_PORT_PRIVATE* port_priv = NULL;

    OMX_U32 i = 0;

    venc_user_buf* puser_buf = NULL;
    venc_msginfo* venc_msg = NULL;

    if (!pcom_priv || !message)
    {
        DEBUG_PRINT_ERROR("async_message_process() invalid param\n");

        return;
    }

    venc_msg = (venc_msginfo*)message;

    switch (venc_msg->msgcode)
    {
        case VENC_MSG_RESP_FLUSH_INPUT_DONE:
            post_event(pcom_priv, 0, venc_msg->status_code, OMX_GENERATE_FLUSH_INPUT_DONE);

            if (bit_present(&pcom_priv->m_flags, OMX_STATE_INPUT_DISABLE_PENDING))
            {
                post_event(pcom_priv, (OMX_U32)OMX_CommandPortDisable, (OMX_U32)OUTPUT_PORT_INDEX,
                           OMX_GENERATE_COMMAND_DONE);
            }
            break;

        case VENC_MSG_RESP_FLUSH_OUTPUT_DONE:
            post_event(pcom_priv, 0, venc_msg->status_code, OMX_GENERATE_FLUSH_OUTPUT_DONE);

            if (bit_present(&pcom_priv->m_flags, OMX_STATE_OUTPUT_DISABLE_PENDING))
            {
                post_event(pcom_priv, (OMX_U32)OMX_CommandPortDisable, (OMX_U32)INPUT_PORT_INDEX,
                           OMX_GENERATE_COMMAND_DONE);
            }
            break;

        case VENC_MSG_RESP_START_DONE:
            post_event(pcom_priv, 0, venc_msg->status_code, OMX_GENERATE_START_DONE);
            break;

        case VENC_MSG_RESP_STOP_DONE:
            post_event(pcom_priv, 0, venc_msg->status_code, OMX_GENERATE_STOP_DONE);
            break;

        case VENC_MSG_RESP_PAUSE_DONE:
            post_event(pcom_priv, 0, venc_msg->status_code, OMX_GENERATE_PAUSE_DONE);
            break;

        case VENC_MSG_RESP_RESUME_DONE:
            post_event(pcom_priv, 0, venc_msg->status_code, OMX_GENERATE_RESUME_DONE);
            break;

        case VENC_MSG_RESP_INPUT_DONE:
            puser_buf = &venc_msg->buf;
            port_priv = &pcom_priv->m_port[INPUT_PORT_INDEX];

            if (puser_buf->client_data == 0)
            {
                DEBUG_PRINT_ERROR("venc resp buf struct invalid\n");
                post_event(pcom_priv, 0, (OMX_U32)VENC_DONE_FAILED, OMX_GENERATE_EBD);
                break;
            }

            pomx_buf = (OMX_BUFFERHEADERTYPE*)(long)puser_buf->client_data;
            for (i = 0; i < port_priv->port_def.nBufferCountActual; i++)
            {
                if (pomx_buf == port_priv->m_omx_bufhead[i])
                {
                    break;
                }
            }

            if (i >= port_priv->port_def.nBufferCountActual)
            {
                DEBUG_PRINT_ERROR("buffers[%p] no found", pomx_buf);
                post_event(pcom_priv, 0, (OMX_U32)VENC_DONE_FAILED, OMX_GENERATE_EBD);
                break;
            }

            DEBUG_PRINT("[EBD]venc resp in buffer %p,buferaddr:%p\n",
                        pomx_buf, pomx_buf->pBuffer);

            post_event(pcom_priv, (OMX_U32)pomx_buf, (OMX_U32)VENC_DONE_SUCCESS, OMX_GENERATE_EBD);
            break;

        case VENC_MSG_RESP_OUTPUT_DONE:
            message_process_case_output_done (pcom_priv, venc_msg);
            break;

        default:
            DEBUG_PRINT_ERROR("msg 0x%08x not process\n",
                              venc_msg->msgcode);
            break;
    }

    return;
}


static void* message_thread(void* input)
{
    OMX_COMPONENT_PRIVATE* pcom_priv = (OMX_COMPONENT_PRIVATE*)input;
    OMX_S32 error_code = 0;
    venc_msginfo msginfo;

    memset(&msginfo, 0, sizeof(venc_msginfo));
    DEBUG_PRINT("Message thread start!\n");

    while (!pcom_priv->msg_thread_exit)
    {
        memset(&msginfo, 0, sizeof(venc_msginfo));
        error_code = channel_get_msg(&pcom_priv->drv_ctx, &msginfo);
        if (error_code == HI_FAILURE)
        {
            DEBUG_PRINT("[%s]:get msg failed:%ld", __func__, error_code);
            continue;
        }
        message_process(pcom_priv, &msginfo);
    }

    DEBUG_PRINT("Message thread exit!\n");

    return NULL;
}

static OMX_ERRORTYPE generate_command_done(
    OMX_COMPONENT_PRIVATE* pcom_priv,
    OMX_U32 param1, OMX_U32 param2 )
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_PORT_PRIVATE* port_priv = NULL;

    OMX_CHECK_ARG_RETURN(pcom_priv == NULL);
    OMX_CHECK_ARG_RETURN(pcom_priv->m_cb.EventHandler == NULL);

    switch (param1)
    {
        case OMX_CommandStateSet:
            pcom_priv->m_state = (OMX_STATETYPE)param2;
            omx_report_event(pcom_priv, OMX_EventCmdComplete, param1, param2, NULL);
            break;

        case OMX_CommandPortEnable:
            DEBUG_PRINT("OMX_CommandPortEnable complete\n");
            port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
            if (port_priv->m_port_reconfig)
            {
                DEBUG_PRINT("clear flags for port reconfig!\n");
                port_priv->m_port_reconfig = OMX_FALSE;
            }

            omx_report_event(pcom_priv, OMX_EventCmdComplete, param1, param2, NULL);
            break;

        case OMX_CommandPortDisable:
            DEBUG_PRINT("OMX_CommandPortDisable complete\n");
            omx_report_event(pcom_priv, OMX_EventCmdComplete, param1, param2, NULL);
            break;

        case OMX_CommandFlush:

        default:
            DEBUG_PRINT_ERROR("unknown genereate event %lu\n", param1);
            ret = OMX_ErrorUndefined;
            break;
    }

    return ret;
}

static OMX_ERRORTYPE handle_command_state_set_loaded(
    OMX_COMPONENT_PRIVATE *pcom_priv,
    OMX_STATETYPE state, OMX_U32 *pflag)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_U32 flag = 1;
#ifdef __OMXVENC_RGB_BUFFER__
    HI_MMZ_BUF_S stBuf_RGB;
    HI_UNF_VENC_CHN_ATTR_S *pstVencCfg;
#endif

    /*  Loaded to idle */
    if (state == OMX_StateIdle)
    {
        if (channel_create(&pcom_priv->drv_ctx) < 0)
        {
            DEBUG_PRINT_ERROR("ERROR: channel create failed!\n");
            ret = OMX_ErrorHardware;

            return ret;
        }

#ifdef __OMXVENC_RGB_BUFFER__
        pstVencCfg = &pcom_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr;
        snprintf(stBuf_RGB.bufname, 16, "%s", "OMXVENC_RGB");
        stBuf_RGB.bufsize = ALIGN_UP(pstVencCfg->u32Width, 256) * pstVencCfg->u32Height * 4;
        if (pcom_priv->m_store_metadata_buf)
        {
            if (HI_MMZ_Malloc(&stBuf_RGB) != 0)
            {
                DEBUG_PRINT_ERROR("ERROR: channel create RGB buffer for StoreMetaData failed!\n");
                ret = OMX_ErrorHardware;

                return ret;
            }
            pcom_priv->bufferaddr_Phy_RGB = stBuf_RGB.phyaddr;
            pcom_priv->bufferaddr_RGB     = stBuf_RGB.user_viraddr;
            pcom_priv->buffer_size_RGB    = stBuf_RGB.bufsize;
        }
#endif

        if (ports_all_full(pcom_priv) ||
            (pcom_priv->m_port[0].port_def.bEnabled == OMX_FALSE &&
             pcom_priv->m_port[1].port_def.bEnabled == OMX_FALSE))
        {
            DEBUG_PRINT_STATE("Loaded-->Idle\n");
        }
        else
        {
            DEBUG_PRINT_STATE("Loaded-->Idle-Pending\n");
            bit_set(&pcom_priv->m_flags, OMX_STATE_IDLE_PENDING);
            flag = 0;
        }
    }
    /*  Loaded to Loaded */
    else if (state == OMX_StateLoaded)
    {
        DEBUG_PRINT_STATE("ERROR: Loaded-->Loaded\n");
        ret = OMX_ErrorSameState;
    }
    /*  Loaded to WaitForResources */
    else if (state == OMX_StateWaitForResources)
    {
        DEBUG_PRINT_STATE("Loaded-->WaitForResources\n");
        ret = OMX_ErrorNone;
    }
    /*  Loaded to Executing */
    else if (state == OMX_StateExecuting)
    {
        DEBUG_PRINT_STATE("ERROR:Loaded-->Executing\n");
        ret = OMX_ErrorIncorrectStateTransition;
    }
    /*  Loaded to Pause */
    else if (state == OMX_StatePause)
    {
        DEBUG_PRINT_STATE("ERROR: Loaded-->Pause\n");
        ret = OMX_ErrorIncorrectStateTransition;
    }
    else
    {
        DEBUG_PRINT_STATE("Loaded-->%d Not Handled)\n", state);
        ret = OMX_ErrorUndefined;
    }

    *pflag = flag;

    return ret;
}

static OMX_ERRORTYPE handle_command_state_set_idle(
    OMX_COMPONENT_PRIVATE *pcom_priv,
    OMX_STATETYPE state, OMX_U32 *pflag)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_U32 flag = 1;
#ifdef __OMXVENC_RGB_BUFFER__
    HI_MMZ_BUF_S stBuf_RGB;
#endif

    /*  Idle to Loaded */
    if (state == OMX_StateLoaded)
    {
        if (ports_all_empty(pcom_priv))
        {
            if (channel_destroy(&pcom_priv->drv_ctx) < 0)
            {
                DEBUG_PRINT_ERROR("ERROR: channel create failed!\n");
                ret = OMX_ErrorHardware;

                return ret;
            }
#ifdef __OMXVENC_RGB_BUFFER__
        stBuf_RGB.phyaddr      = pcom_priv->bufferaddr_Phy_RGB;
        stBuf_RGB.user_viraddr = pcom_priv->bufferaddr_RGB;
        stBuf_RGB.bufsize      = pcom_priv->buffer_size_RGB;
        if (pcom_priv->m_store_metadata_buf)
        {
            if (HI_MMZ_Free(&stBuf_RGB) != 0)
            {
                DEBUG_PRINT_ERROR("ERROR: channel free RGB buffer for StoreMetaData failed!\n");
                ret = OMX_ErrorHardware;
            }
            pcom_priv->bufferaddr_Phy_RGB = 0;
            pcom_priv->bufferaddr_RGB     = 0;
            pcom_priv->buffer_size_RGB    = 0;
        }
#endif
            pcom_priv->msg_thread_exit = OMX_TRUE;
            pthread_join(pcom_priv->msg_thread_id, NULL);

            DEBUG_PRINT_STATE("idle-->Loaded\n");
        }
        else
        {
            DEBUG_PRINT_STATE("idle-->Loaded-Pending\n");
            bit_set(&pcom_priv->m_flags, OMX_STATE_LOADING_PENDING);
            flag = 0;
        }
    }
    /*  Idle to Executing */
    else if (state == OMX_StateExecuting)
    {
        DEBUG_PRINT_STATE("idle-->Executing-Pending\n");
        if (channel_start(&pcom_priv->drv_ctx) < 0)
        {
            DEBUG_PRINT_ERROR("Channel start failed\n");
            ret = OMX_ErrorHardware;

            return ret;
        }

        pcom_priv->msg_thread_exit    = OMX_FALSE;
        if (pthread_create(&pcom_priv->msg_thread_id,
                           0, message_thread, pcom_priv) < 0)
        {
            DEBUG_PRINT_STATE("ERROR: failed to create msg thread\n");
            ret = OMX_ErrorInsufficientResources;

            return ret;
        }

        DEBUG_PRINT("message thread create ok\n");
        flag = 1;
    }
    /*  Idle to Idle */
    else if (state == OMX_StateIdle)
    {
        DEBUG_PRINT_STATE("ERROR: Idle-->Idle\n");
        ret = OMX_ErrorSameState;
    }
    /*  Idle to WaitForResources */
    else if (state == OMX_StateWaitForResources)
    {
        DEBUG_PRINT_STATE("ERROR: Idle-->WaitForResources\n");
        ret = OMX_ErrorIncorrectStateTransition;
    }
    /*  Idle to Pause */
    else if (state == OMX_StatePause)
    {
        DEBUG_PRINT_STATE("Idle-->Pause\n");
        bit_set(&pcom_priv->m_flags, OMX_STATE_PAUSE_PENDING);
        flag = 0;
    }
    else
    {
        DEBUG_PRINT_ERROR("Idle --> %d Not Handled\n", state);
        ret = OMX_ErrorBadParameter;
    }

    *pflag = flag;

    return ret;
}

static OMX_ERRORTYPE handle_command_state_set_executing(
    OMX_COMPONENT_PRIVATE *pcom_priv,
    OMX_STATETYPE state, OMX_U32 *pflag)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_U32 flag = 1;

    /*  Executing to Idle */
    if (state == OMX_StateIdle)
    {
        if (channel_stop(&pcom_priv->drv_ctx) < 0)
        {
            DEBUG_PRINT_ERROR("chan stop failed\n");
            ret = OMX_ErrorHardware;

            return ret;
        }

        DEBUG_PRINT_STATE("Executing-->Idle OK! \n");
        bit_set(&pcom_priv->m_flags, OMX_STATE_IDLE_PENDING);
        flag = 0;
    }
    /*  Executing to Paused */
    else if (state == OMX_StatePause)
    {
        if (channel_stop(&pcom_priv->drv_ctx) < 0)
        {
            DEBUG_PRINT_ERROR("Error In Pause State\n");
            ret = OMX_ErrorHardware;

            return ret;
        }

        DEBUG_PRINT_STATE("Executing-->Pause OK!\n");
        bit_set(&pcom_priv->m_flags, OMX_STATE_IDLE_PENDING);
        flag = 0;
    }
    /*  Executing to Loaded */
    else if (state == OMX_StateLoaded)
    {
        DEBUG_PRINT_STATE("Executing --> Loaded \n");
        ret = OMX_ErrorIncorrectStateTransition;
    }
    /*  Executing to WaitForResources */
    else if (state == OMX_StateWaitForResources)
    {
        DEBUG_PRINT_STATE("Executing --> WaitForResources \n");
        ret = OMX_ErrorIncorrectStateTransition;
    }
    /*  Executing to Executing */
    else if (state == OMX_StateExecuting)
    {
        DEBUG_PRINT_STATE("Executing --> Executing \n");
        ret = OMX_ErrorSameState;
    }
    else
    {
        DEBUG_PRINT_ERROR("Executing -->%d Not Handled\n", state);
        ret = OMX_ErrorBadParameter;
    }

    *pflag = flag;

    return ret;
}

static OMX_ERRORTYPE handle_command_state_set_pause(
    OMX_COMPONENT_PRIVATE *pcom_priv,
    OMX_STATETYPE state, OMX_U32 *sem_posted, OMX_U32 *pflag)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_U32 flag = 1;

    /*  Pause to Executing */
    if (state == OMX_StateExecuting)
    {
        if (channel_start(&pcom_priv->drv_ctx) < 0)
        {
            DEBUG_PRINT_ERROR("Channel start failed\n");
            ret = OMX_ErrorHardware;

            return ret;
        }
        DEBUG_PRINT_STATE("Pause-->Executing OK! \n");
        flag = 1;

    }
    /*  Pause to Idle */
    else if (state == OMX_StateIdle)
    {
        if (channel_stop(&pcom_priv->drv_ctx) < 0)
        {
            DEBUG_PRINT_ERROR("channel_stop failed\n");
            ret = OMX_ErrorHardware;

            return ret;
        }

        DEBUG_PRINT_STATE("Pause --> Idle!\n");
        bit_set(&pcom_priv->m_flags, OMX_STATE_IDLE_PENDING);
        flag = 0;

        if (!*sem_posted)
        {
            *sem_posted = 1;
            sem_post(&pcom_priv->m_cmd_lock);
            if (omx_flush_port(pcom_priv, OMX_ALL) != OMX_ErrorNone)
            {
                DEBUG_PRINT("omx flush port err!\n");
            }
        }
    }
    /*  Pause to loaded */
    else if (state == OMX_StateLoaded)
    {
        DEBUG_PRINT_STATE("Pause --> loaded \n");
        ret = OMX_ErrorIncorrectStateTransition;
    }
    /*  Pause to WaitForResources */
    else if (state == OMX_StateWaitForResources)
    {
        DEBUG_PRINT_STATE("Pause --> WaitForResources\n");
        ret = OMX_ErrorIncorrectStateTransition;
    }
    /*  Pause to Pause */
    else if (state == OMX_StatePause)
    {
        DEBUG_PRINT_STATE("Pause --> Pause\n");
        ret = OMX_ErrorSameState;
    }
    else
    {
        DEBUG_PRINT_STATE("ERROR:Paused -->%d Not Handled\n", state);
        ret = OMX_ErrorBadParameter;
    }

    *pflag = flag;

    return ret;
}

static OMX_ERRORTYPE handle_command_state_set_resources(
    OMX_COMPONENT_PRIVATE *pcom_priv,
    OMX_STATETYPE state)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;

    /*  WaitForResources to Loaded */
    if (state == OMX_StateLoaded)
    {
        DEBUG_PRINT_STATE("WaitForResources-->Loaded\n");
    }
    if (state == OMX_StateIdle)
    {
        DEBUG_PRINT_STATE("WaitForResources-->Idle\n");
    }
    /*  WaitForResources to WaitForResources */
    else if (state == OMX_StateWaitForResources)
    {
        DEBUG_PRINT_STATE("ERROR: WaitForResources-->WaitForResources\n");
        ret = OMX_ErrorSameState;
    }
    /*  WaitForResources to Executing */
    else if (state == OMX_StateExecuting)
    {
        DEBUG_PRINT_STATE("ERROR: WaitForResources-->Executing\n");
        ret = OMX_ErrorIncorrectStateTransition;
    }
    /*  WaitForResources to Pause */
    else if (state == OMX_StatePause)
    {
        DEBUG_PRINT_STATE("ERROR: WaitForResources-->Pause\n");
        ret = OMX_ErrorIncorrectStateTransition;
    }
    /*  WaitForResources to Loaded -
       is NOT tested by Khronos TS */
    else
    {
        DEBUG_PRINT_STATE("ERROR: %d --> %d(NotHandled)\n",
                          pcom_priv->m_state, state);
        ret = OMX_ErrorBadParameter;
    }

    return ret;
}

static OMX_ERRORTYPE handle_command_state_set(
    OMX_COMPONENT_PRIVATE* pcom_priv,
    OMX_STATETYPE state, OMX_U32* sem_posted)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_U32 flag = 1;

    /***************************/
    /* Current State is Loaded */
    /***************************/
    if (pcom_priv->m_state == OMX_StateLoaded)
    {
        ret = handle_command_state_set_loaded(pcom_priv, state, &flag);
    }
    /***************************/
    /* Current State is IDLE */
    /***************************/
    else if (pcom_priv->m_state == OMX_StateIdle)
    {
        ret = handle_command_state_set_idle(pcom_priv, state, &flag);
    }
    /******************************/
    /* Current State is Executing */
    /******************************/
    else if (pcom_priv->m_state == OMX_StateExecuting)
    {
        ret = handle_command_state_set_executing(pcom_priv, state, &flag);
    }
    /***************************/
    /* Current State is Pause  */
    /***************************/
    else if (pcom_priv->m_state == OMX_StatePause)
    {
        ret = handle_command_state_set_pause(pcom_priv, state, sem_posted, &flag);
    }
    /***************************/
    /* Current State is WaitForResources  */
    /***************************/
    else if (pcom_priv->m_state == OMX_StateWaitForResources)
    {
        ret = handle_command_state_set_resources(pcom_priv, state);
    }

    if (flag)
    {
        if (ret != OMX_ErrorNone)                     //�쳣�˳������֧
        {
            omx_report_error(pcom_priv, ret);
        }
        else
        {
            post_event(pcom_priv, OMX_CommandStateSet, state, OMX_GENERATE_COMMAND_DONE);
        }
    }

    return ret;
}

static OMX_ERRORTYPE handle_command_flush(
    OMX_COMPONENT_PRIVATE* pcom_priv,
    OMX_U32 port)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_PORT_PRIVATE* port_priv = NULL;

    DEBUG_PRINT("OMX_CommandFlush!\n");
    if ((port != OMX_ALL) && (port > OUTPUT_PORT_INDEX))
    {
        DEBUG_PRINT_ERROR("Error: Invalid Port %ld\n", (OMX_S32)port);
        return OMX_ErrorBadPortIndex;
    }

    if ((INPUT_PORT_INDEX == port) || (OMX_ALL == port))
    {
        bit_set(&pcom_priv->m_flags,
                OMX_STATE_INPUT_FLUSH_PENDING);
        port_priv = &pcom_priv->m_port[INPUT_PORT_INDEX];
        port_priv->m_port_flushing = OMX_TRUE;
    }
    if ((OUTPUT_PORT_INDEX == port) || (OMX_ALL == port))
    {
        bit_set(&pcom_priv->m_flags,
                OMX_STATE_OUTPUT_FLUSH_PENDING);
        port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
        port_priv->m_port_flushing = OMX_TRUE;
    }

    if (channel_flush_port(&pcom_priv->drv_ctx, port, 0) < 0)
    {
        DEBUG_PRINT_ERROR("ioctl flush port failed\n");
        ret = OMX_ErrorHardware;
        /*fixme: should clear flushing pending bits?!!*/
        omx_report_error(pcom_priv, ret);
    }
    else
    { DEBUG_PRINT("command flush ok!\n"); }
    return ret;
}

static OMX_ERRORTYPE handle_command_port_disable(
    OMX_COMPONENT_PRIVATE* pcom_priv,
    OMX_U32 port, OMX_U32* sem_posted)
{
    OMX_PORT_PRIVATE* port_priv = NULL;
    OMX_U32 flag = 1;

    if (port != OUTPUT_PORT_INDEX) {
        DEBUG_PRINT_ERROR("Port enable/disable allowed only on output ports.[current:disable]");
        omx_report_error(pcom_priv, OMX_ErrorUndefined);
        return OMX_EventError;
    }

    DEBUG_PRINT("OMX_CommandPortDisable\n");

    DEBUG_PRINT("Disable output port!\n");
    port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
    if (port_priv->port_def.bEnabled)
    {
        port_priv->port_def.bEnabled = OMX_FALSE;

        if (!port_empty(pcom_priv, OUTPUT_PORT_INDEX))
        {
            DEBUG_PRINT_STATE("out port Enabled-->Disable Pending\n");

            bit_set(&pcom_priv->m_flags,
                    OMX_STATE_OUTPUT_DISABLE_PENDING);

            if (!*sem_posted)
            {
                *sem_posted = 1;
                sem_post (&pcom_priv->m_cmd_lock);
            }
            if (omx_flush_port(pcom_priv, OUTPUT_PORT_INDEX) != OMX_ErrorNone)
            {
                DEBUG_PRINT("omx flush port err!\n");
            }

            flag = 0;
        }
    }
    else
    {
        DEBUG_PRINT("output already disabled\n");
    }

    if (flag)
    {
        DEBUG_PRINT_STATE("[ST]port state Disable Pending ->Disable\n");
        bit_clear((&pcom_priv->m_flags),
                  OMX_STATE_OUTPUT_DISABLE_PENDING);

        post_event(pcom_priv, OMX_CommandPortDisable,
                   OUTPUT_PORT_INDEX,
                   OMX_GENERATE_COMMAND_DONE);
    }

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE handle_command_port_enable(
    OMX_COMPONENT_PRIVATE* pcom_priv,
    OMX_U32 port)
{
    OMX_PORT_PRIVATE* port_priv = NULL;
    OMX_U32 flag = 1;

    if (port != OUTPUT_PORT_INDEX) {
        DEBUG_PRINT_ERROR("Port enable/disable allowed only on output ports.[current:enable]");
        omx_report_error(pcom_priv, OMX_ErrorUndefined);
        return OMX_EventError;
    }

    DEBUG_PRINT("OMX_CommandPortEnable\n");

    DEBUG_PRINT("Enable output port!\n");

    port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
    if (!port_priv->port_def.bEnabled)
    {
        port_priv->port_def.bEnabled = OMX_TRUE;

        if (!port_full(pcom_priv, OUTPUT_PORT_INDEX))
        {
            DEBUG_PRINT_STATE("Disabled-->Enabled Pending\n");
            bit_set(&pcom_priv->m_flags,
                    OMX_STATE_OUTPUT_ENABLE_PENDING);
            flag = 0;
        }
    }
    else
    {
        DEBUG_PRINT("Out port already enabled\n");
    }

    if (flag)
    {
        post_event(pcom_priv,
                   OMX_CommandPortEnable, OUTPUT_PORT_INDEX,
                   OMX_GENERATE_COMMAND_DONE);
    }

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE  send_command_proxy(
    OMX_COMPONENT_PRIVATE* pcom_priv,
    OMX_IN OMX_COMMANDTYPE cmd,
    OMX_IN OMX_U32 param1)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_U32 sem_posted = 0;

    OMX_CHECK_ARG_RETURN(pcom_priv == NULL);

    switch (cmd)
    {
        case OMX_CommandStateSet:
            ret = handle_command_state_set(
                      pcom_priv, (OMX_STATETYPE)param1, &sem_posted);
            break;

        case OMX_CommandFlush:
            ret = handle_command_flush(pcom_priv, param1);
            break;

        case OMX_CommandPortEnable:
            ret = handle_command_port_enable(pcom_priv, param1);
            break;

        case OMX_CommandPortDisable:
            ret = handle_command_port_disable(pcom_priv, param1, &sem_posted);
            break;

        default:
            DEBUG_PRINT_ERROR("Error: Invalid Command(%d)\n", cmd);
            ret = OMX_ErrorNotImplemented;
            break;
    }

    if (!sem_posted)
    {
        sem_post(&pcom_priv->m_cmd_lock);
    }

    return ret;
}


static OMX_U32 event_process_get_event_para(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_U32 id, OMX_U32 *pP1, OMX_U32 *pP2)
{
    OMX_U32 p1 = 0;
    OMX_U32 p2 = 0;
    OMX_U32 ident = 0;
    OMX_U32 qsize = 0;

    if (!pcom_priv || (id >= OMX_GENERATE_UNUSED))
    {
        DEBUG_PRINT_ERROR("ERROR: %s() invalid param!\n", __func__);

        return HI_FAILURE;
    }

    /* process event from cmd/etb/ftb queue */
    (void)pthread_mutex_lock(&pcom_priv->m_lock);
    if ((id == OMX_GENERATE_FTB) || (id == OMX_GENERATE_FBD))
    {
        qsize = get_q_size(&pcom_priv->m_ftb_q);
        if (qsize == 0)
        {
            (void)pthread_mutex_unlock(&pcom_priv->m_lock);

            return HI_FAILURE;
        }
        pop_entry(&pcom_priv->m_ftb_q, &p1, &p2, &ident);
    }
    else if ((id == OMX_GENERATE_ETB) || (id == OMX_GENERATE_EBD))
    {
        qsize = get_q_size(&pcom_priv->m_etb_q);
        if (qsize == 0)
        {
            (void)pthread_mutex_unlock(&pcom_priv->m_lock);

            return HI_FAILURE;
        }
        pop_entry(&pcom_priv->m_etb_q, &p1, &p2, &ident);
    }
    else
    {
        qsize = get_q_size(&pcom_priv->m_cmd_q);
        if (qsize == 0)
        {
            (void)pthread_mutex_unlock(&pcom_priv->m_lock);

            return HI_FAILURE;
        }
        pop_entry(&pcom_priv->m_cmd_q, &p1, &p2, &ident);
    }

    (void)pthread_mutex_unlock(&pcom_priv->m_lock);

    if (id != ident)
    {
        DEBUG_PRINT_ERROR("ID cannot match, id %lu, ident %lu\n", id, ident);

        return HI_FAILURE;
    }

    *pP1 = p1;
    *pP2 = p2;

    return HI_SUCCESS;
}

static void event_process_case_ebd(OMX_COMPONENT_PRIVATE *pcom_priv,OMX_U32 p1, OMX_U32 p2)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;

    if (p2 != VENC_DONE_SUCCESS)
    {
        DEBUG_PRINT_ERROR("OMX_GENERATE_EBD failure\n");
        omx_report_error(pcom_priv, OMX_ErrorUndefined);

        return;
    }

    ret = empty_buffer_done(pcom_priv, (OMX_BUFFERHEADERTYPE*)p1);
    if (ret != OMX_ErrorNone)
    {
        DEBUG_PRINT_ERROR("empty_buffer_done failure\n");
        omx_report_error(pcom_priv, ret);
    }
}

static void event_process_case_fbd(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_U32 p1, OMX_U32 p2)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;

    if (p2 != VENC_DONE_SUCCESS)
    {
        DEBUG_PRINT_ERROR("OMX_GENERATE_FBD failure %s,%d\n", __func__, __LINE__);
        omx_report_error(pcom_priv, OMX_ErrorUndefined);

        return;
    }

    ret = fill_buffer_done(pcom_priv, (OMX_BUFFERHEADERTYPE*)p1);
    if (ret != OMX_ErrorNone)
    {
        DEBUG_PRINT_ERROR("fill_buffer_done failure\n");
        omx_report_error (pcom_priv, ret);
    }
}

static void event_process_case_flush_input_done(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_U32 p2)
{
    OMX_PORT_PRIVATE *port_priv = NULL;

    DEBUG_PRINT("Driver flush i/p Port complete\n");
    port_priv = &pcom_priv->m_port[INPUT_PORT_INDEX];
    if (!port_priv->m_port_flushing)
    {
        DEBUG_PRINT("WARNING: Unexpected flush cmd\n");

        return;
    }
    else
    {
        port_priv->m_port_flushing = OMX_FALSE;
    }

    return_inbuffers(pcom_priv);

    if (p2 != VENC_DONE_SUCCESS)
    {
        DEBUG_PRINT_ERROR("input flush failure\n");
        omx_report_error(pcom_priv, OMX_ErrorHardware);

        return;
    }

    /*Check if we need generate event for Flush done*/
    if (bit_present(&pcom_priv->m_flags, OMX_STATE_INPUT_FLUSH_PENDING))
    {
        DEBUG_PRINT("Input Flush completed - Notify Client\n");
        bit_clear(&pcom_priv->m_flags, OMX_STATE_INPUT_FLUSH_PENDING);

        omx_report_event(pcom_priv, OMX_EventCmdComplete, OMX_CommandFlush, INPUT_PORT_INDEX, NULL);
    }
}

static void event_process_case_flush_output_done(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_U32 p2)
{
    OMX_PORT_PRIVATE *port_priv = NULL;

    DEBUG_PRINT("Driver flush o/p Port complete\n");
    port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
    if (!port_priv->m_port_flushing)
    {
        DEBUG_PRINT("WARNING: Unexpected flush cmd\n");

        return;
    }
    else
    {
        port_priv->m_port_flushing = OMX_FALSE;
    }
    return_outbuffers(pcom_priv);
    if (p2 != VENC_DONE_SUCCESS)
    {
        DEBUG_PRINT_ERROR("output flush failure\n");
        omx_report_error(pcom_priv, OMX_ErrorHardware);

        return;
    }

    /*Check if we need generate event for Flush done*/
    if (bit_present(&pcom_priv->m_flags, OMX_STATE_OUTPUT_FLUSH_PENDING))
    {
        DEBUG_PRINT("Notify Output Flush done\n");
        bit_clear (&pcom_priv->m_flags, OMX_STATE_OUTPUT_FLUSH_PENDING);
        omx_report_event(pcom_priv, OMX_EventCmdComplete, OMX_CommandFlush, OUTPUT_PORT_INDEX, NULL);
    }
}

static void event_process_case_start_done(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_U32 p2)
{
    if (p2 != VENC_DONE_SUCCESS)
    {
        DEBUG_PRINT_ERROR("OMX_GENERATE_START_DONE Failure\n");
        omx_report_error(pcom_priv, OMX_ErrorHardware);

        return;
    }

    if (bit_present(&pcom_priv->m_flags, OMX_STATE_EXECUTE_PENDING))
    {
        DEBUG_PRINT_STATE("Move to executing\n");
        bit_clear((&pcom_priv->m_flags), OMX_STATE_EXECUTE_PENDING);
        pcom_priv->m_state = OMX_StateExecuting;
        omx_report_event(pcom_priv, OMX_EventCmdComplete, OMX_CommandStateSet, OMX_StateExecuting, NULL);
    }

    if (bit_present(&pcom_priv->m_flags, OMX_STATE_PAUSE_PENDING))
    {
        if (channel_stop(&pcom_priv->drv_ctx) < 0)
        {
            DEBUG_PRINT_ERROR("channel_pause failed\n");
            omx_report_error(pcom_priv, OMX_ErrorHardware);
        }
    }
}

static void event_process_case_pause_done(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_U32 p2)
{
    if (p2 != VENC_DONE_SUCCESS)
    {
        DEBUG_PRINT_ERROR("OMX_GENERATE_PAUSE_DONE failed\n");
        omx_report_error(pcom_priv, OMX_ErrorHardware);

        return;
    }

    if (bit_present(&pcom_priv->m_flags, OMX_STATE_PAUSE_PENDING))
    {
        DEBUG_PRINT("OMX_GENERATE_PAUSE_DONE nofity\n");

        bit_clear(&pcom_priv->m_flags, OMX_STATE_PAUSE_PENDING);

        pcom_priv->m_state = OMX_StatePause;
        omx_report_event(pcom_priv, OMX_EventCmdComplete, OMX_CommandStateSet, OMX_StatePause, NULL);
    }
}

static void event_process_case_resume_done(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_U32 p2)
{
    if (p2 != VENC_DONE_SUCCESS)
    {
        DEBUG_PRINT_ERROR("OMX_GENERATE_RESUME_DONE failed\n");
        omx_report_error(pcom_priv, OMX_ErrorHardware);

        return;
    }

    if (bit_present(&pcom_priv->m_flags, OMX_STATE_EXECUTE_PENDING))
    {
        DEBUG_PRINT_STATE("Moving to execute state\n");

        bit_clear((&pcom_priv->m_flags), OMX_STATE_EXECUTE_PENDING);
        pcom_priv->m_state = OMX_StateExecuting;
        omx_report_event(pcom_priv, OMX_EventCmdComplete, OMX_CommandStateSet, OMX_StateExecuting, NULL);
    }
}

static void event_process_case_stop_done(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_U32 p2)
{
    if (p2 != VENC_DONE_SUCCESS)
    {
        DEBUG_PRINT_ERROR("OMX_GENERATE_STOP_DONE failed\n");
        omx_report_error(pcom_priv, OMX_ErrorHardware);

        return;
    }

    return_outbuffers(pcom_priv);
    return_inbuffers(pcom_priv);

    if (bit_present(&pcom_priv->m_flags, OMX_STATE_IDLE_PENDING))
    {
        bit_clear((&pcom_priv->m_flags), OMX_STATE_IDLE_PENDING);

        pcom_priv->m_state = OMX_StateIdle;

        DEBUG_PRINT_STATE("State Idle-pending -> Idle\n");

        omx_report_event(pcom_priv, OMX_EventCmdComplete, OMX_CommandStateSet, OMX_StateIdle, NULL);
    }
}

static void event_process(OMX_COMPONENT_PRIVATE *pcom_priv, OMX_U32 id)
{
    OMX_PORT_PRIVATE *port_priv = NULL;
    OMX_U32 p1 = 0;
    OMX_U32 p2 = 0;

    if(event_process_get_event_para(pcom_priv, id, &p1, &p2) == (OMX_U32)HI_FAILURE)
    {
        return;
    }

    /* event process instance */
    switch (id)
    {
        case OMX_GENERATE_COMMAND_DONE:
            generate_command_done(pcom_priv, p1, p2);
            break;

        case OMX_GENERATE_ETB:
            empty_this_buffer_proxy(pcom_priv, (OMX_BUFFERHEADERTYPE*)p1);
            break;

        case OMX_GENERATE_FTB:
            fill_this_buffer_proxy(pcom_priv, (OMX_BUFFERHEADERTYPE*)p1);
            break;

        case OMX_GENERATE_COMMAND:
            send_command_proxy(pcom_priv, (OMX_COMMANDTYPE)p1, (OMX_U32)p2);
            break;

        case OMX_GENERATE_EBD:
            event_process_case_ebd(pcom_priv, p1, p2);
            break;

        case OMX_GENERATE_FBD:
            event_process_case_fbd(pcom_priv, p1, p2);
            break;

        case OMX_GENERATE_FLUSH_INPUT_DONE:
            event_process_case_flush_input_done(pcom_priv, p2);
            break;

        case OMX_GENERATE_FLUSH_OUTPUT_DONE:
            event_process_case_flush_output_done(pcom_priv, p2);
            break;

        case OMX_GENERATE_START_DONE:
            event_process_case_start_done(pcom_priv, p2);
            break;

        case OMX_GENERATE_PAUSE_DONE:
            event_process_case_pause_done(pcom_priv, p2);
            break;

        case OMX_GENERATE_RESUME_DONE:
            event_process_case_resume_done(pcom_priv, p2);
            break;

        case OMX_GENERATE_STOP_DONE:
            event_process_case_stop_done(pcom_priv, p2);
            break;

        case OMX_GENERATE_EOS_DONE:
            DEBUG_PRINT("Rxd OMX_GENERATE_EOS_DONE\n");
            omx_report_event(pcom_priv, OMX_EventBufferFlag, OUTPUT_PORT_INDEX, OMX_BUFFERFLAG_EOS, NULL);
            break;

        case OMX_GENERATE_IMAGE_SIZE_CHANGE:
            DEBUG_PRINT("image size changed!\n");
            port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
            port_priv->m_port_reconfig = OMX_TRUE;
            omx_report_event(pcom_priv, OMX_EventPortSettingsChanged, OUTPUT_PORT_INDEX, OMX_IndexParamPortDefinition, NULL);
            break;

        case OMX_GENERATE_CROP_RECT_CHANGE:
            DEBUG_PRINT("crop rect changed!\n");
            omx_report_event(pcom_priv, OMX_EventPortSettingsChanged, OUTPUT_PORT_INDEX, OMX_IndexConfigCommonOutputCrop, NULL);
            break;

        case OMX_GENERATE_HARDWARE_ERROR:
            DEBUG_PRINT_ERROR("hardware failed\n");
            omx_report_error(pcom_priv, OMX_ErrorHardware);
            break;

        default:
            DEBUG_PRINT_ERROR("default process for msg %lu\n", id);
            break;
    }
}

static void* event_thread(void* input)
{
    OMX_COMPONENT_PRIVATE* pcom_priv =
        (OMX_COMPONENT_PRIVATE*)input;
    OMX_U8 id;
    OMX_S32 n = -1;
    sem_wait(&pcom_priv->m_async_sem);                                  //���ⲿ�ͷ�m_async_sem�ź�������ʽִ���߳�
    DEBUG_PRINT("Event thread start!\n");
    while (!pcom_priv->event_thread_exit)
    {
        sem_post(&pcom_priv->m_async_sem);
        n = read(pcom_priv->m_pipe_in, &id, 1);
        if (((n < 0) && (errno != EINTR)) || (n == 0))                   //errno!=EINTR -- ���������벻���� ���жϣ��¼�������������������ж�����Ĵ��󣬼���ִ��
        {
            DEBUG_PRINT("read from pipe failed, ret:%ld\n", n);
            break;
        }
        else if (n > 1)
        {
            DEBUG_PRINT_ERROR("read more than 1 byte\n");
            sem_wait(&pcom_priv->m_async_sem);
            continue;
        }
        event_process(pcom_priv, id);

        sem_wait(&pcom_priv->m_async_sem);
    }

    sem_post(&pcom_priv->m_async_sem);
    DEBUG_PRINT("Event thread exit!\n");

    return NULL;
}


static OMX_S32 ports_init(OMX_COMPONENT_PRIVATE* pcom_priv)
{
    OMX_PORT_PRIVATE* in_port  = NULL;
    OMX_PORT_PRIVATE* out_port = NULL;
    OMX_S32 result = -1;

    /* init in port private */
    in_port = &pcom_priv->m_port[INPUT_PORT_INDEX];
    in_port->m_omx_bufhead = (OMX_BUFFERHEADERTYPE**)malloc(sizeof(OMX_BUFFERHEADERTYPE*)* MAX_BUF_NUM_INPUT);

    in_port->m_venc_bufhead = (venc_user_info**)malloc(sizeof(venc_user_info*) * MAX_BUF_NUM_INPUT);
    if (!in_port->m_omx_bufhead || !in_port->m_venc_bufhead)
    {
        DEBUG_PRINT_ERROR("not enough memory!\n");
        goto inport_error;
    }

    memset(in_port->m_omx_bufhead, 0, sizeof(OMX_BUFFERHEADERTYPE*)* MAX_BUF_NUM_INPUT);
    memset(in_port->m_venc_bufhead, 0, sizeof(venc_user_info*) * MAX_BUF_NUM_INPUT);

    in_port->m_buf_cnt              = 0;
    in_port->m_buf_pend_cnt         = 0;
    in_port->m_port_reconfig        = OMX_FALSE;
    in_port->m_port_flushing        = OMX_FALSE;

    in_port->port_def.nVersion.nVersion                 = OMX_SPEC_VERSION;
    in_port->port_def.nSize                             = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);

    in_port->port_def.nPortIndex                        = INPUT_PORT_INDEX;
    in_port->port_def.eDir                              = OMX_DirInput;
    in_port->port_def.nBufferCountActual                = DEF_MAX_IN_BUF_CNT;
    in_port->port_def.nBufferCountMin                   = DEF_MIN_IN_BUF_CNT;
    in_port->port_def.nBufferSize                       = FRAME_SIZE(MAX_FRAME_WIDTH, MAX_FRAME_HEIGHT);   //��ʱ�����˱���������ܵ�buffer_size
    in_port->port_def.bEnabled                          = OMX_TRUE;
    in_port->port_def.bPopulated                        = OMX_FALSE;
    in_port->port_def.eDomain                           = OMX_PortDomainVideo;
    in_port->port_def.bBuffersContiguous                = OMX_TRUE;
    in_port->port_def.nBufferAlignment                  = DEFAULT_ALIGN_SIZE;

    in_port->port_def.format.video.nFrameWidth          = MAX_FRAME_WIDTH;
    in_port->port_def.format.video.nFrameHeight         = MAX_FRAME_HEIGHT;
    in_port->port_def.format.video.xFramerate           = DEFAULT_FPS << 16;
    in_port->port_def.format.video.nStride              = MAX_FRAME_WIDTH;
    in_port->port_def.format.video.nSliceHeight         = MAX_FRAME_HEIGHT;
    in_port->port_def.format.video.eColorFormat         = OMX_COLOR_FormatYUV420SemiPlanar;
    in_port->port_def.format.video.eCompressionFormat   = OMX_VIDEO_CodingUnused;
    in_port->port_def.format.video.bFlagErrorConcealment = OMX_FALSE;

    /* init out port private */
    out_port = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
    out_port->m_omx_bufhead = (OMX_BUFFERHEADERTYPE**)malloc(sizeof(OMX_BUFFERHEADERTYPE*)* MAX_BUF_NUM_OUTPUT);
    out_port->m_venc_bufhead = (venc_user_info**)malloc(sizeof(venc_user_info*) * MAX_BUF_NUM_OUTPUT);
    if (!out_port->m_omx_bufhead || !out_port->m_venc_bufhead)
    {
        DEBUG_PRINT_ERROR("not enough memory!\n");
        goto outport_error;
    }

    memset(out_port->m_omx_bufhead, 0, sizeof(OMX_BUFFERHEADERTYPE*)* MAX_BUF_NUM_OUTPUT);
    memset(out_port->m_venc_bufhead, 0, sizeof(venc_user_info*) * MAX_BUF_NUM_OUTPUT);

    out_port->m_buf_cnt                = 0;
    out_port->m_buf_pend_cnt        = 0;
    out_port->m_port_reconfig        = OMX_FALSE;
    out_port->m_port_flushing        = OMX_FALSE;

    //CONFIG_VERSION_SIZE(&(in_port->port_def), OMX_PARAM_PORTDEFINITIONTYPE);
    out_port->port_def.nVersion.nVersion                 = OMX_SPEC_VERSION;
    out_port->port_def.nSize                             = sizeof(OMX_PARAM_PORTDEFINITIONTYPE);
    out_port->port_def.nPortIndex                        = OUTPUT_PORT_INDEX;
    out_port->port_def.eDir                              = OMX_DirOutput;
    out_port->port_def.nBufferCountActual                = DEF_MAX_OUT_BUF_CNT;
    out_port->port_def.nBufferCountMin                   = DEF_MIN_OUT_BUF_CNT;
    out_port->port_def.nBufferSize                       = DEF_OUT_BUFFER_SIZE;//FRAME_SIZE(MAX_FRAME_WIDTH, MAX_FRAME_HEIGHT);   //��ʱ�����˱���������ܵ�buffer_size
    out_port->port_def.bEnabled                          = OMX_TRUE;
    out_port->port_def.bPopulated                        = OMX_FALSE;
    out_port->port_def.eDomain                           = OMX_PortDomainVideo;
    out_port->port_def.bBuffersContiguous                = OMX_TRUE;
    out_port->port_def.nBufferAlignment                  = DEFAULT_ALIGN_SIZE;

    out_port->port_def.format.video.nFrameWidth          = MAX_FRAME_WIDTH;
    out_port->port_def.format.video.nFrameHeight         = MAX_FRAME_HEIGHT;
    out_port->port_def.format.video.xFramerate           = DEFAULT_FPS << 16;
    out_port->port_def.format.video.nSliceHeight         = 0;                             // ??
    out_port->port_def.format.video.nBitrate             = DEFAULT_BITRATE;
    out_port->port_def.format.video.eColorFormat         = OMX_COLOR_FormatUnused;
    out_port->port_def.format.video.eCompressionFormat   = OMX_VIDEO_CodingAVC;
    out_port->port_def.format.video.bFlagErrorConcealment = OMX_FALSE;

    DEBUG_PRINT("exit %s()", __func__);
    return 0;

outport_error:
    if (out_port->m_omx_bufhead)
    {
        free(out_port->m_omx_bufhead);
        out_port->m_omx_bufhead = NULL;
    }

    if (out_port->m_venc_bufhead)
    {
        free(out_port->m_venc_bufhead);
        out_port->m_venc_bufhead = NULL;
    }

inport_error:
    if (in_port->m_omx_bufhead)
    {
        free(in_port->m_omx_bufhead);
        in_port->m_omx_bufhead = NULL;
    }

    if (in_port->m_venc_bufhead)
    {
        free(in_port->m_venc_bufhead);
        in_port->m_venc_bufhead = NULL;
    }

    return result;
}


static void ports_deinit(OMX_COMPONENT_PRIVATE* pcom_priv)
{
    OMX_S32 i = 0;
    for (; i < MAX_PORT_NUM; ++i)
    {
        if (pcom_priv->m_port[i].m_venc_bufhead)
        {
            free(pcom_priv->m_port[i].m_venc_bufhead);
            pcom_priv->m_port[i].m_venc_bufhead = NULL;
        }
        if (pcom_priv->m_port[i].m_omx_bufhead)
        {
            free(pcom_priv->m_port[i].m_omx_bufhead);
            pcom_priv->m_port[i].m_omx_bufhead = NULL;
        }
    }
    DEBUG_PRINT("exit %s()", __func__);
}


/* ==========================================================================
   FUNCTION
   get_component_version

   DESCRIPTION
   Returns the component specifcation version.

   PARAMETERS
   TBD.

   RETURN VALUE
   OMX_ErrorNone.
   ==========================================================================*/
static OMX_ERRORTYPE  get_component_version(
    OMX_IN  OMX_HANDLETYPE phandle,
    OMX_OUT OMX_STRING comp_name,
    OMX_OUT OMX_VERSIONTYPE* comp_version,
    OMX_OUT OMX_VERSIONTYPE* spec_version,
    OMX_OUT OMX_UUIDTYPE* componentUUID)
{
    OMX_COMPONENTTYPE* pcomp         = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;

    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(comp_name == NULL);
    OMX_CHECK_ARG_RETURN(comp_version == NULL);
    OMX_CHECK_ARG_RETURN(spec_version == NULL);
    OMX_CHECK_ARG_RETURN(componentUUID == NULL);


    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    strncpy((char*)comp_name, (char*)pcom_priv->m_comp_name , OMX_MAX_STRINGNAME_SIZE - 1);

    comp_version->nVersion = pcomp->nVersion.nVersion;
    spec_version->nVersion = OMX_SPEC_VERSION;

    return OMX_ErrorNone;
}


/* ==========================================================================
   FUNCTION
   send_command

   DESCRIPTION
   process command sent to component

   PARAMETERS
   None.

   RETURN VALUE
   Error None if successful. Or Error Type
   ==========================================================================*/
static OMX_ERRORTYPE  send_command(
    OMX_IN OMX_HANDLETYPE phandle,
    OMX_IN OMX_COMMANDTYPE cmd,
    OMX_IN OMX_U32 param1,
    OMX_IN OMX_PTR cmd_data)
{
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;

    OMX_CHECK_ARG_RETURN(phandle == NULL);

    pcomp     = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    post_event(pcom_priv,
               (OMX_U32)cmd, (OMX_U32)param1, OMX_GENERATE_COMMAND);      //���û��������ѹ����к͹ܵ���ʵ�ʴ��������ڲ��� send_command_proxy�������,�ȵ��ڲ�send_command_proxy�����꣬�ͷ��ź������˴�����ź����������ɹ���
    DEBUG_PRINT("send_command : cmd =%d\n", cmd);
    sem_wait(&pcom_priv->m_cmd_lock);

    return OMX_ErrorNone;
}

static OMX_ERRORTYPE get_parameter_VideoAvc(OMX_INOUT OMX_PTR param_data, OMX_COMPONENT_PRIVATE *pcomp_priv)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_VIDEO_PARAM_AVCTYPE *pAvcType = NULL;
    HI_UNF_VENC_CHN_ATTR_S *pVencUnfAttrs = NULL;

    pAvcType = (OMX_VIDEO_PARAM_AVCTYPE*)param_data;
    pVencUnfAttrs = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr;
    DEBUG_PRINT("get_param:OMX_IndexParamVideoAvc,PortIndex = %ld,state = %ld\n", (OMX_S32)pAvcType->nPortIndex, (OMX_S32)pcomp_priv->m_state);

    if ((pAvcType->nPortIndex > OUTPUT_PORT_INDEX) || (pAvcType->nPortIndex == INPUT_PORT_INDEX))
    {
        DEBUG_PRINT_ERROR("Bad Port idx %ld\n", (OMX_S32)pAvcType->nPortIndex);
        ret = OMX_ErrorBadPortIndex;

        return ret;
    }

    CONFIG_VERSION_SIZE(pAvcType , OMX_VIDEO_PARAM_AVCTYPE);

    pAvcType->nSliceHeaderSpacing   = 0;
    pAvcType->nPFrames              = pVencUnfAttrs->u32Gop - 1;
    pAvcType->nBFrames              = 0;
    pAvcType->bUseHadamard          = OMX_TRUE;
    pAvcType->nRefFrames            = 1;
    pAvcType->nRefIdx10ActiveMinus1 = 0;
    pAvcType->nRefIdx11ActiveMinus1 = 0;
    pAvcType->bEnableUEP            = OMX_FALSE;
    pAvcType->bEnableFMO            = OMX_FALSE;
    pAvcType->bEnableASO            = OMX_FALSE;
    pAvcType->bEnableRS             = OMX_FALSE;
    pAvcType->nAllowedPictureTypes  = (pAvcType->nPFrames == 0) ? (OMX_VIDEO_PictureTypeI) : ((OMX_U32)OMX_VIDEO_PictureTypeI | (OMX_U32)OMX_VIDEO_PictureTypeP);
    pAvcType->bFrameMBsOnly         = OMX_TRUE;
    pAvcType->bMBAFF                = OMX_FALSE;
    pAvcType->bEntropyCodingCABAC   = (pVencUnfAttrs->enVencProfile != HI_UNF_H264_PROFILE_BASELINE) ? (OMX_TRUE) : (OMX_FALSE);
    pAvcType->bWeightedPPrediction  = OMX_FALSE;
    pAvcType->nWeightedBipredicitonMode = OMX_FALSE;
    pAvcType->bconstIpred               = OMX_TRUE;
    pAvcType->bDirect8x8Inference       = OMX_FALSE;
    pAvcType->bDirectSpatialTemporal    = OMX_FALSE;
    pAvcType->nCabacInitIdc             = 0;
    pAvcType->eLoopFilterMode           = OMX_VIDEO_AVCLoopFilterEnable;

    switch (pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.h264Level)
    {
        case 10:
            pAvcType->eLevel = OMX_VIDEO_AVCLevel1;
            break;
        case 20:
            pAvcType->eLevel = OMX_VIDEO_AVCLevel2;
            break;
        case 21:
            pAvcType->eLevel = OMX_VIDEO_AVCLevel21;
            break;
        case 30:
            pAvcType->eLevel = OMX_VIDEO_AVCLevel3;
            break;
        case 31:
            pAvcType->eLevel = OMX_VIDEO_AVCLevel31;
            break;
        case 32:
            pAvcType->eLevel = OMX_VIDEO_AVCLevel32;
            break;
        case 41:
            pAvcType->eLevel = OMX_VIDEO_AVCLevel41;
            break;
        default:
            DEBUG_PRINT_ERROR("Bad parm of Level %ld\n", (OMX_S32)pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.h264Level);
            pAvcType->eLevel = OMX_VIDEO_AVCLevelMax;
            break;
    }
    switch (pVencUnfAttrs->enVencProfile)
    {
        case HI_UNF_H264_PROFILE_BASELINE:
            pAvcType->eProfile = OMX_VIDEO_AVCProfileBaseline;
            break;
        case HI_UNF_H264_PROFILE_MAIN:
            pAvcType->eProfile = OMX_VIDEO_AVCProfileMain;
            break;
        case HI_UNF_H264_PROFILE_HIGH:
            pAvcType->eProfile = OMX_VIDEO_AVCProfileHigh;
            break;
        default:
            DEBUG_PRINT_ERROR("Bad parm of VencProfile %ld\n", (OMX_S32)pVencUnfAttrs->enVencProfile);
            pAvcType->eProfile = OMX_VIDEO_AVCProfileMax;
            break;
    }

    return ret;
}

#ifdef OMXVENC_SUPPORT_HEVC
static OMX_ERRORTYPE get_parameter_VideoHevc(OMX_INOUT OMX_PTR param_data, OMX_COMPONENT_PRIVATE *pcomp_priv)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_VIDEO_PARAM_HEVCTYPE *pHevcType = NULL;
    HI_UNF_VENC_CHN_ATTR_S *pVencUnfAttrs = NULL;

    pHevcType = (OMX_VIDEO_PARAM_HEVCTYPE*)param_data;
    pVencUnfAttrs = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr;
    DEBUG_PRINT("get_param:OMX_IndexParamVideoAvc,PortIndex = %ld,state = %ld\n", (OMX_S32)pHevcType->nPortIndex, (OMX_S32)pcomp_priv->m_state);

    if ((pHevcType->nPortIndex > OUTPUT_PORT_INDEX) || (pHevcType->nPortIndex == INPUT_PORT_INDEX))
    {
        DEBUG_PRINT_ERROR("Bad Port idx %ld\n", (OMX_S32)pHevcType->nPortIndex);
        ret = OMX_ErrorBadPortIndex;

        return ret;
    }

    CONFIG_VERSION_SIZE(pHevcType , OMX_VIDEO_PARAM_HEVCTYPE);

    switch (pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.h264Level)
    {
        case 10:
            pHevcType->eLevel = OMX_VIDEO_HEVCMainTierLevel1;
            break;
        case 20:
            pHevcType->eLevel = OMX_VIDEO_HEVCMainTierLevel2;
            break;
        case 21:
            pHevcType->eLevel = OMX_VIDEO_HEVCMainTierLevel21;
            break;
        case 30:
            pHevcType->eLevel = OMX_VIDEO_HEVCMainTierLevel3;
            break;
        case 31:
            pHevcType->eLevel = OMX_VIDEO_HEVCMainTierLevel31;
            break;
        case 32:
            pHevcType->eLevel = OMX_VIDEO_HEVCMainTierLevel31;
            break;
        case 41:
            pHevcType->eLevel = OMX_VIDEO_HEVCMainTierLevel41;
            break;
        default:
            DEBUG_PRINT_ERROR("Bad parm of Level %ld\n", (OMX_S32)pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.h264Level);
            pHevcType->eLevel = OMX_VIDEO_HEVCHighTiermax;
            break;
    }

    pHevcType->eProfile = OMX_VIDEO_HEVCProfileMain;
    pHevcType->nKeyFrameInterval = pVencUnfAttrs->u32Gop;

    return ret;
}
#endif

static OMX_ERRORTYPE get_parameter_VideoPortFormat(OMX_INOUT OMX_PTR param_data, OMX_COMPONENT_PRIVATE *pcomp_priv)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_VIDEO_PARAM_PORTFORMATTYPE *portFmt = NULL;

    portFmt = (OMX_VIDEO_PARAM_PORTFORMATTYPE*)param_data;
    DEBUG_PRINT("get_param:OMX_IndexParamVideoPortFormat,PortIndex = %ld,state = %ld\n",
                (OMX_S32)portFmt->nPortIndex, (OMX_S32)pcomp_priv->m_state);

    CONFIG_VERSION_SIZE(portFmt, OMX_VIDEO_PARAM_PORTFORMATTYPE);

    if (INPUT_PORT_INDEX == portFmt->nPortIndex)
    {
        switch (portFmt->nIndex)
        {
            case 0:
                portFmt->eColorFormat = OMX_COLOR_FormatYUV420SemiPlanar;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 1:
                portFmt->eColorFormat = OMX_COLOR_FormatYVU420SemiPlanar;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 2:
                portFmt->eColorFormat = OMX_COLOR_FormatYUV420Planar;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 3:
                portFmt->eColorFormat = OMX_COLOR_FormatYVU420Planar;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 4:
                portFmt->eColorFormat = OMX_COLOR_FormatYCbYCr;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 5:
                portFmt->eColorFormat = OMX_COLOR_FormatYCrYCb;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 6:
                portFmt->eColorFormat = OMX_COLOR_FormatCbYCrY;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 7:
                portFmt->eColorFormat = OMX_COLOR_FormatYUV422SemiPlanar;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 8:
                portFmt->eColorFormat = OMX_COLOR_FormatYVU422SemiPlanar;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 9:
                portFmt->eColorFormat = OMX_QCOM_COLOR_FormatYVU420SemiPlanar;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                break;
            case 10:
                portFmt->eColorFormat = OMX_COLOR_FormatAndroidOpaque;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingUnused;
                DEBUG_PRINT("input format support : OMX_COLOR_FormatAndroidOpaque!\n");
                break;

            default:
                DEBUG_PRINT("no more input format\n");
                ret = OMX_ErrorNoMore;
                break;
        }
    }
    else if (OUTPUT_PORT_INDEX == portFmt->nPortIndex)
    {
        switch (portFmt->nIndex)
        {
            case 0:
                portFmt->eColorFormat = OMX_COLOR_FormatUnused;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingAVC;
                break;

            case 1:
                portFmt->eColorFormat = OMX_COLOR_FormatUnused;
                portFmt->eCompressionFormat = OMX_VIDEO_CodingHEVC;
                break;

            default:
                DEBUG_PRINT("no more output format\n");
                ret = OMX_ErrorNoMore;
                break;
        }
    }
    else
    {
        DEBUG_PRINT_ERROR("OMX_IndexParamVideoPortFormat: Bad Port Index, %d\n", (int)portFmt->nPortIndex);
        ret = OMX_ErrorBadPortIndex;
    }

    return ret;
}

/* ==========================================================================
   FUNCTION
   get_parameter

   DESCRIPTION
   OMX Get Parameter method implementation

   PARAMETERS
   <TBD>.

   RETURN VALUE
   Error None if successful. Or Error Type
   ==========================================================================*/
static OMX_ERRORTYPE  get_parameter(OMX_IN OMX_HANDLETYPE phandle,
                                    OMX_IN OMX_INDEXTYPE param_index,
                                    OMX_INOUT OMX_PTR param_data)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcomp_priv = NULL;
    OMX_S32 param;
    OMX_CHECK_ARG_RETURN(phandle == NULL);

    pcomp      = (OMX_COMPONENTTYPE*)phandle;
    pcomp_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    param = (OMX_S32)param_index;

    switch (param)
    {
        case OMX_IndexParamPortDefinition:                                          //ע��:��ʱ�������Ӧ���Ѿ����������param_data�ж�Ӧ�˿����Ե�nPortIndex���úã���ʾ��ȡ�ĸ�port������
        {
            OMX_PARAM_PORTDEFINITIONTYPE* portDefn =
                (OMX_PARAM_PORTDEFINITIONTYPE*)param_data;
            OMX_PORT_PRIVATE* port_priv = NULL;
            DEBUG_PRINT("get_param: OMX_IndexParamPortDefinition,PortIndex = %ld,state = %ld\n",
                        (OMX_S32)portDefn->nPortIndex, (OMX_S32)pcomp_priv->m_state);
            if (portDefn->nPortIndex > OUTPUT_PORT_INDEX)
            {
                DEBUG_PRINT_ERROR("Bad Port idx %ld\n", (OMX_S32)portDefn->nPortIndex);
                ret = OMX_ErrorBadPortIndex;
                break;
            }

            port_priv = &pcomp_priv->m_port[portDefn->nPortIndex];
            port_priv->port_def.format.video.nFrameWidth  = pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr.u32Width;
            port_priv->port_def.format.video.nFrameHeight = pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr.u32Height;
            *portDefn = port_priv->port_def;
            DEBUG_PRINT("get_param:OMX_IndexParamPortDefinition, eCompressionFormat(%ld),eColorFormat(%ld),portId(%ld),buffersize(%ld),W = %d,H= %d,Stride = %d,%d\n",
                        (OMX_S32)portDefn->format.video.eCompressionFormat,
                        (OMX_S32)portDefn->format.video.eColorFormat,
                        (OMX_S32)portDefn->nPortIndex,
                        (OMX_S32)portDefn->nBufferSize,
                        (OMX_S32)portDefn->format.video.nFrameWidth,(OMX_S32)portDefn->format.video.nFrameHeight,(OMX_S32)portDefn->format.video.nStride,(OMX_S32)portDefn->format.video.nSliceHeight);
            break;
        }

        /*Component come to be a video*/
        case OMX_IndexParamVideoInit:
        {
            OMX_PORT_PARAM_TYPE* portParamType = (OMX_PORT_PARAM_TYPE*) param_data;

            DEBUG_PRINT("get_param:OMX_IndexParamVideoInit,state = %ld\n", (OMX_S32)pcomp_priv->m_state);

            CONFIG_VERSION_SIZE(portParamType , OMX_PORT_PARAM_TYPE);

            portParamType->nPorts           = COUNTOF(pcomp_priv->m_port);
            portParamType->nStartPortNumber = INPUT_PORT_INDEX;
            break;
        }
        case OMX_IndexParamVideoAvc:
        {
            ret = get_parameter_VideoAvc(param_data, pcomp_priv);
            break;
        }
    #ifdef OMXVENC_SUPPORT_HEVC
        case OMX_IndexParamVideoHevc:
        {
            ret = get_parameter_VideoHevc(param_data, pcomp_priv);
            break;
        }
    #endif
        case OMX_IndexParamVideoPortFormat:
        {
            ret = get_parameter_VideoPortFormat(param_data, pcomp_priv);
            break;
        }
#ifdef KHRONOS_1_1
        case OMX_IndexParamStandardComponentRole:
        {
            OMX_PARAM_COMPONENTROLETYPE* comp_role =
                (OMX_PARAM_COMPONENTROLETYPE*)param_data;

            DEBUG_PRINT("get_param: OMX_IndexParamStandardComponentRole\n");

            CONFIG_VERSION_SIZE(comp_role , OMX_PARAM_COMPONENTROLETYPE);
            strncpy((char*)comp_role->cRole,(char*)pcomp_priv->m_role, OMX_MAX_STRINGNAME_SIZE - 1);
            break;
        }
#endif
        case OMX_IndexParamVideoProfileLevelQuerySupported:                     //�����֧��Ҫ���������ú�profileLevelType->nProfileIndex��nPortIndex��
        {
            OMX_VIDEO_PARAM_PROFILELEVELTYPE* profileLevelType =
                (OMX_VIDEO_PARAM_PROFILELEVELTYPE*)param_data;

            DEBUG_PRINT("get_param: OMX_IndexParamVideoProfileLevelQuerySupported,PortIndex = %ld,state = %ld\n",
                        (OMX_S32)profileLevelType->nPortIndex, (OMX_S32)pcomp_priv->m_state);


            CONFIG_VERSION_SIZE(profileLevelType , OMX_VIDEO_PARAM_PROFILELEVELTYPE);

            ret = get_supported_profile_level(pcomp_priv, profileLevelType);
            break;
        }
        case OMX_IndexParamVideoProfileLevelCurrent:
        {
            OMX_VIDEO_PARAM_PROFILELEVELTYPE* profileLevelType =
                (OMX_VIDEO_PARAM_PROFILELEVELTYPE*)param_data;

            DEBUG_PRINT("get_param: OMX_IndexParamVideoProfileLevelCurrent,PortIndex = %ld,state = %ld\n",
                        (OMX_S32)profileLevelType->nPortIndex, (OMX_S32)pcomp_priv->m_state);

            if (profileLevelType->nPortIndex != OUTPUT_PORT_INDEX)
            {
                DEBUG_PRINT_ERROR("Bad Port idx %ld\n", (OMX_S32)profileLevelType->nPortIndex);

                return OMX_ErrorBadPortIndex;
            }
            CONFIG_VERSION_SIZE(profileLevelType , OMX_VIDEO_PARAM_PROFILELEVELTYPE);

            ret = get_current_profile_level(pcomp_priv, profileLevelType);
            break;
        }
        case OMX_IndexParamVideoBitrate:
        {
            OMX_VIDEO_PARAM_BITRATETYPE* pVideoBitRate =
                (OMX_VIDEO_PARAM_BITRATETYPE*)param_data;

            if (pVideoBitRate->nPortIndex != OUTPUT_PORT_INDEX)
            {
                DEBUG_PRINT_ERROR("Bad Port idx %ld\n", (OMX_S32)pVideoBitRate->nPortIndex);
                ret = OMX_ErrorBadPortIndex;
            }
            CONFIG_VERSION_SIZE(pVideoBitRate , OMX_VIDEO_PARAM_BITRATETYPE);

            pVideoBitRate->eControlRate   = (OMX_VIDEO_CONTROLRATETYPE)pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.ControlRateType;
            pVideoBitRate->nTargetBitrate = pcomp_priv->m_port[pVideoBitRate->nPortIndex].port_def.format.video.nBitrate;
            break;
        }
#ifdef ANDROID
        case OMX_HisiIndexGetParameterSet:
        {
            OMX_VIDEO_PPS_SPS_DATA* pParameterSet =
                (OMX_VIDEO_PPS_SPS_DATA*)param_data;

            DEBUG_PRINT("get_param: OMX_HisiIndexGetParameterSet\n");

            if ((pcomp_priv->m_state >= OMX_StateLoaded) && (pcomp_priv->m_state <= OMX_StateWaitForResources))
            {
                if (channel_get_sps_pps(&(pcomp_priv->drv_ctx), (DRV_VIDEO_PPS_SPS_DATA*)pParameterSet) < 0)
                {
                    DEBUG_PRINT_ERROR("ERROR: channel get SPS&PPS  failed!\n");
                    ret = OMX_ErrorHardware;
                    omx_report_error(pcomp_priv, ret);
                }
            }
            break;

        }
#endif
        case OMX_HisiIndexAutoRequestIFrm:
        {
            struct AutoRequestIFrmParams* penable = (struct AutoRequestIFrmParams*)param_data;
            venc_chan_cfg* pVencChnAttr = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg;

            DEBUG_PRINT("get_parameter: OMX_HisiIndexAutoRequestIFrm\n");

            penable->nSize             = sizeof(AutoRequestIFrmParams);
            penable->bEnable = (OMX_BOOL)pVencChnAttr->bAutoRequestIFrm;
            break;
        }
        case OMX_GoogleIndexPrependSPSPPSToIDRFrames:
        {
            struct PrependSPSPPSToIDRFramesParams*  penable = (struct PrependSPSPPSToIDRFramesParams*)param_data;

            DEBUG_PRINT("get_parameter: OMX_GoogleIndexPrependSPSPPSToIDRFrames-> enable(%d)\n",(int)pcomp_priv->m_prepend_sps_pps);
            penable->bEnable = pcomp_priv->m_prepend_sps_pps;
            break;
        }

        default:
            DEBUG_PRINT_ERROR("get_param: unknown param %08x\n",
                              param_index);
            ret = OMX_ErrorUnsupportedIndex;
            break;
    }

    return ret;
}


static OMX_ERRORTYPE set_parameter_PortDefinition(OMX_IN OMX_PTR param_data, OMX_COMPONENT_PRIVATE *pcomp_priv)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_PARAM_PORTDEFINITIONTYPE *portDefn = NULL;
    OMX_PORT_PRIVATE *port_priv = NULL;
    venc_chan_cfg *pvenc_attr = NULL;

    portDefn = (OMX_PARAM_PORTDEFINITIONTYPE*)param_data;

    DEBUG_PRINT("set_param: OMX_IndexParamPortDefinition,PortIndex = %ld,state = %ld\n",
                (OMX_S32)portDefn->nPortIndex, (OMX_S32)pcomp_priv->m_state);

    DEBUG_PRINT("set_param: OMX_IndexParamPortDefinition,PortIndex(%ld),state(%ld),nBufferCountActual(%ld),nBufferCountMin(%ld),nBufferSize(%ld)\n",
                (OMX_S32)portDefn->nPortIndex, (OMX_S32)pcomp_priv->m_state,
                portDefn->nBufferCountActual,
                portDefn->nBufferCountMin,
                portDefn->nBufferSize);
    DEBUG_PRINT("set_param: OMX_IndexParamPortDefinition,bEnabled(%d),bPopulated(%d),bBuffersContiguous(%d),nBufferAlignment(%ld)\n",
                portDefn->bEnabled, portDefn->bPopulated,
                portDefn->bBuffersContiguous,
                portDefn->nBufferAlignment);
    DEBUG_PRINT("set_param: OMX_IndexParamPortDefinition,nFrameWidth(%ld),nFrameHeight(%ld),nStride(%ld),nSliceHeight(%ld),nBitrate(%ld),eCompressionFormat(%d),eColorFormat(%d)\n",
                (OMX_S32)portDefn->format.video.nFrameWidth, portDefn->format.video.nFrameHeight,
                portDefn->format.video.nStride, portDefn->format.video.nSliceHeight, portDefn->format.video.nBitrate,
                portDefn->format.video.eCompressionFormat, portDefn->format.video.eColorFormat);

    if (portDefn->nPortIndex > OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT("invalid port index!\n");

        return OMX_ErrorBadPortIndex;
    }

    port_priv = &pcomp_priv->m_port[portDefn->nPortIndex];
    pvenc_attr = &(pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg);

    if (portDefn->nBufferCountActual < portDefn->nBufferCountMin)
    {
        DEBUG_PRINT("setted buf cnt too small! nBufferCountActual[%lu] should > nBufferCountMin[%lu]!\n",
                    portDefn->nBufferCountActual, portDefn->nBufferCountMin);
        return OMX_ErrorUndefined;
    }

    if ((portDefn->format.video.nFrameWidth % PIC_ALIGN_SIZE) || (portDefn->format.video.nFrameHeight % PIC_ALIGN_SIZE))
    {
        DEBUG_PRINT_ERROR("Picture Width(%lu) or Heigth(%lu) invalid, should N*%d.\n", portDefn->format.video.nFrameWidth,
                          portDefn->format.video.nFrameHeight, PIC_ALIGN_SIZE);
        return OMX_ErrorUndefined;
    }

    port_priv->port_def = *portDefn ;
    DEBUG_PRINT("port = %d Picture Width(%lu) or Heigth(%lu) stride %d.====>\n", portDefn->nPortIndex,portDefn->format.video.nFrameWidth,
                          portDefn->format.video.nFrameHeight, portDefn->format.video.nStride);

    if (portDefn->nPortIndex == OUTPUT_PORT_INDEX)
    {
        port_priv->port_def.nBufferSize   = portDefn->nBufferSize;
        pvenc_attr->VencUnfAttr.u32Width  = portDefn->format.video.nFrameWidth;
        pvenc_attr->VencUnfAttr.u32Height = portDefn->format.video.nFrameHeight;
        pvenc_attr->VencUnfAttr.u32TargetFrmRate = pcomp_priv->m_port[0].port_def.format.video.xFramerate >> 16;
        if (pvenc_attr->VencUnfAttr.u32TargetFrmRate > HI_VENC_MAX_fps)
        {
            pvenc_attr->VencUnfAttr.u32TargetFrmRate = HI_VENC_MAX_fps;
        }

        pcomp_priv->m_port[1].port_def.format.video.xFramerate = pcomp_priv->m_port[0].port_def.format.video.xFramerate;
        switch (portDefn->format.video.eCompressionFormat)
        {
            case OMX_VIDEO_CodingAVC:
                pvenc_attr->VencUnfAttr.enVencType = HI_UNF_VCODEC_TYPE_H264;
                break;

            case OMX_VIDEO_CodingHEVC:
                pvenc_attr->VencUnfAttr.enVencType = HI_UNF_VCODEC_TYPE_HEVC;
                break;

            default:
                DEBUG_PRINT_ERROR("NOT support the role of %d\n", portDefn->format.video.eCompressionFormat);
                break;
        }
    }
    else
    {
        pvenc_attr->VencUnfAttr.u32Width  = portDefn->format.video.nFrameWidth;
        pvenc_attr->VencUnfAttr.u32Height = portDefn->format.video.nFrameHeight;
        pvenc_attr->VencUnfAttr.u32InputFrmRate = portDefn->format.video.xFramerate >> 16;
        if (pvenc_attr->VencUnfAttr.u32InputFrmRate > HI_VENC_MAX_fps)
        {
            pvenc_attr->VencUnfAttr.u32InputFrmRate = HI_VENC_MAX_fps;
        }
    }

    return ret;
}

static OMX_ERRORTYPE set_parameter_VideoAVC(OMX_IN OMX_PTR param_data, OMX_COMPONENT_PRIVATE *pcomp_priv)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_VIDEO_PARAM_AVCTYPE *pAvcType = NULL;
    HI_UNF_VENC_CHN_ATTR_S *pVencUnfAttrs = NULL;

    pAvcType = (OMX_VIDEO_PARAM_AVCTYPE*)param_data;
    pVencUnfAttrs = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr;

    DEBUG_PRINT("set_param:OMX_IndexParamVideoAvc,PortIndex = %ld,state=%ld\n",
                (OMX_S32)pAvcType->nPortIndex, (OMX_S32)pcomp_priv->m_state);

    if ((pAvcType->nPortIndex > OUTPUT_PORT_INDEX) || (pAvcType->nPortIndex == INPUT_PORT_INDEX))
    {
        DEBUG_PRINT_ERROR("Bad Port idx %ld\n", (OMX_S32)pAvcType->nPortIndex);
        ret = OMX_ErrorBadPortIndex;
    }

    if (OMX_ErrorNone != omx_check_param_videoAvc(pAvcType))
    {
        DEBUG_PRINT_ERROR(" Parameter of AVC not support!\n");
        ret = OMX_ErrorBadParameter;
    }

    pVencUnfAttrs->u32Gop = pAvcType->nPFrames + 1;

    switch (pAvcType->eProfile)
    {
        case OMX_VIDEO_AVCProfileBaseline:
            pVencUnfAttrs->enVencProfile = HI_UNF_H264_PROFILE_BASELINE;
            break;
        case OMX_VIDEO_AVCProfileMain:
            pVencUnfAttrs->enVencProfile = HI_UNF_H264_PROFILE_MAIN;
            break;
        case OMX_VIDEO_AVCProfileHigh:
            pVencUnfAttrs->enVencProfile = HI_UNF_H264_PROFILE_HIGH;
            break;
        default:
            DEBUG_PRINT_ERROR("profile : %d not support!\n", pAvcType->eProfile);
            ret = OMX_ErrorBadParameter;
            break;
    }

    if ((pcomp_priv->m_state >= OMX_StateIdle) && (pcomp_priv->m_state <= OMX_StateWaitForResources))
    {
        if (channel_set_attr(&(pcomp_priv->drv_ctx)) < 0)
        {
            DEBUG_PRINT_ERROR("ERROR: channel set attr failed!\n");
            ret = OMX_ErrorHardware;
            omx_report_error(pcomp_priv, ret);
        }
    }

    DEBUG_PRINT("set_param:OMX_IndexParamVideoAvc,PortIndex = %ld,state=%ld ret = %d\n",
                (OMX_S32)pAvcType->nPortIndex, (OMX_S32)pcomp_priv->m_state, ret);
    return ret;
}

#ifdef OMXVENC_SUPPORT_HEVC
static OMX_ERRORTYPE set_parameter_VideoHevc(OMX_IN OMX_PTR param_data, OMX_COMPONENT_PRIVATE *pcomp_priv)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_VIDEO_PARAM_HEVCTYPE *pHevcType = NULL;
    HI_UNF_VENC_CHN_ATTR_S *pVencUnfAttrs = NULL;

    pHevcType = (OMX_VIDEO_PARAM_HEVCTYPE*)param_data;
    pVencUnfAttrs = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr;
    DEBUG_PRINT("set_param:OMX_IndexParamVideoAvc,PortIndex = %ld,state=%ld\n",
                (OMX_S32)pHevcType->nPortIndex, (OMX_S32)pcomp_priv->m_state);

    if ((pHevcType->nPortIndex > OUTPUT_PORT_INDEX) || (pHevcType->nPortIndex == INPUT_PORT_INDEX))
    {
        DEBUG_PRINT_ERROR("Bad Port idx %ld\n", (OMX_S32)pHevcType->nPortIndex);
        ret = OMX_ErrorBadPortIndex;
    }

    if (OMX_ErrorNone != omx_check_param_videoHevc(pHevcType))
    {
        DEBUG_PRINT_ERROR(" Parameter of HEVC not support!\n");
        ret = OMX_ErrorBadParameter;
    }
    pVencUnfAttrs->u32Gop = pHevcType->nKeyFrameInterval;
    if ((pcomp_priv->m_state >= OMX_StateIdle) && (pcomp_priv->m_state <= OMX_StateWaitForResources))
    {
        if (channel_set_attr(&(pcomp_priv->drv_ctx)) < 0)
        {
            DEBUG_PRINT_ERROR("ERROR: channel set attr failed!\n");
            ret = OMX_ErrorHardware;
            omx_report_error(pcomp_priv, ret);
        }
    }
    DEBUG_PRINT("set_param:OMX_IndexParamVideoAvc,PortIndex = %ld,state=%ld Gop = %d ret = %d\n",
                (OMX_S32)pHevcType->nPortIndex, (OMX_S32)pcomp_priv->m_state, pVencUnfAttrs->u32Gop, ret);
    return ret;
}
#endif

static OMX_ERRORTYPE set_parameter_VideoBitrate(OMX_IN OMX_PTR param_data, OMX_COMPONENT_PRIVATE *pcomp_priv)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_VIDEO_PARAM_BITRATETYPE *pVideoBitRate = NULL;
    HI_UNF_VENC_CHN_ATTR_S *pVencUnfAttrs = NULL;

    pVideoBitRate = (OMX_VIDEO_PARAM_BITRATETYPE*)param_data;
    pVencUnfAttrs = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr;

    DEBUG_PRINT("set_param: OMX_IndexParamVideoBitrate,PortIndex = %lu,state = %d\n",
                pVideoBitRate->nPortIndex, pcomp_priv->m_state);
    DEBUG_PRINT("set_param: OMX_IndexParamVideoBitrate  ->eControlRate(%d),nTargetBitrate(%ld)\n",
                pVideoBitRate->eControlRate, pVideoBitRate->nTargetBitrate);

    if (pVideoBitRate->nPortIndex != OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT_ERROR("Bad Port idx %ld\n", (OMX_S32)pVideoBitRate->nPortIndex);
        ret = OMX_ErrorBadPortIndex;
    }

    pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.ControlRateType = (OMX_U32)pVideoBitRate->eControlRate;

    switch (pVideoBitRate->eControlRate)
    {
        case OMX_Video_ControlRateConstant:
            pVencUnfAttrs->u32MinQp   = 10;
            pVencUnfAttrs->u32MaxQp   = 50;
            break;
        case OMX_Video_ControlRateVariable:
            pVencUnfAttrs->u32MinQp   = 16;
            pVencUnfAttrs->u32MaxQp   = 48;
            break;
        default:
            DEBUG_PRINT_ERROR("ERROR: eControlRate Type(%d) can't support!!\n", pVideoBitRate->eControlRate);
            break;
    }

    pVencUnfAttrs->u32TargetBitRate   = pVideoBitRate->nTargetBitrate;
    pcomp_priv->m_port[pVideoBitRate->nPortIndex].port_def.format.video.nBitrate = pVideoBitRate->nTargetBitrate;

    if ((pcomp_priv->m_state >= OMX_StateIdle) && (pcomp_priv->m_state <= OMX_StateWaitForResources))
    {
        if (channel_set_attr(&(pcomp_priv->drv_ctx)) < 0)
        {
            DEBUG_PRINT_ERROR("ERROR: channel set attr failed!\n");
            ret = OMX_ErrorHardware;
            omx_report_error(pcomp_priv, ret);
        }
    }
    DEBUG_PRINT("set_param: OMX_IndexParamVideoBitrate  ->eControlRate(%lu),nTargetBitrate(%lu)\n",
                (OMX_U32)pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.ControlRateType, (OMX_U32)pVencUnfAttrs->u32TargetBitRate);
    return ret;
}

static OMX_ERRORTYPE set_parameter_VideoPortFormat(OMX_IN OMX_PTR param_data, OMX_COMPONENT_PRIVATE *pcomp_priv)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_PORT_PRIVATE *port_priv = NULL;
    OMX_VIDEO_PARAM_PORTFORMATTYPE *portFmt = NULL;

    portFmt = (OMX_VIDEO_PARAM_PORTFORMATTYPE*)param_data;
    if (portFmt->nPortIndex > OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT("invalid port index!\n");

        return OMX_ErrorBadPortIndex;
    }

    port_priv = &pcomp_priv->m_port[portFmt->nPortIndex];
    if (OUTPUT_PORT_INDEX == portFmt->nPortIndex)
    {
        OMX_U32 i;
        for (i = 0; i < COUNTOF(codec_trans_list); i++)
        {
            if (codec_trans_list[i].compress_fmt == portFmt->eCompressionFormat)
            { break; }
        }

        if (i >= COUNTOF(codec_trans_list))
        {
            DEBUG_PRINT_ERROR("fmt %d not support\n",
                              portFmt->eCompressionFormat);
            ret = OMX_ErrorUnsupportedSetting;
        }
        else
        {
            strncpy((char*)pcomp_priv->m_role,
                    (char*)codec_trans_list[i].role_name, OMX_MAX_STRINGNAME_SIZE - 1);

            pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr.enVencType =
                codec_trans_list[i].codec_type;

            pcomp_priv->m_encoder_fmt =
                codec_trans_list[i].compress_fmt;
        }
        port_priv->port_def.format.video.eColorFormat       = OMX_COLOR_FormatUnused;
        port_priv->port_def.format.video.eCompressionFormat = portFmt->eCompressionFormat;

    }
    else if (INPUT_PORT_INDEX == portFmt->nPortIndex)
    {
        if ((portFmt->eColorFormat    != OMX_COLOR_FormatYUV420SemiPlanar)  /* YCbCr 420 SP*/
            && (portFmt->eColorFormat != OMX_QCOM_COLOR_FormatYVU420SemiPlanar)
            && (portFmt->eColorFormat != OMX_COLOR_FormatYUV420Planar)
            && (portFmt->eColorFormat != OMX_COLOR_FormatYCbYCr)
            && (portFmt->eColorFormat != OMX_COLOR_FormatYCrYCb)
            && (portFmt->eColorFormat != OMX_COLOR_FormatCbYCrY)
            && (portFmt->eColorFormat != OMX_COLOR_FormatYUV422SemiPlanar)
            && (portFmt->eColorFormat != OMX_COLOR_FormatYVU420SemiPlanar)
            && (portFmt->eColorFormat != OMX_COLOR_FormatYVU422SemiPlanar)
            && (portFmt->eColorFormat != OMX_COLOR_FormatYVU420Planar)
            && (portFmt->eColorFormat != OMX_COLOR_FormatAndroidOpaque))    //as same as OMX_COLOR_FormatYUV420Planar refer to SotfEncode
        {
            DEBUG_PRINT_ERROR("Set output format failed\n");
            ret = OMX_ErrorUnsupportedSetting;
        }

        port_priv->port_def.format.video.eColorFormat       = portFmt->eColorFormat;
        port_priv->port_def.format.video.eCompressionFormat = OMX_VIDEO_CodingUnused;
    }
    else
    {
        DEBUG_PRINT_ERROR("get_parameter: Bad port index %ld\n",
                          (OMX_S32)portFmt->nPortIndex);
        ret = OMX_ErrorBadPortIndex;
    }

    return ret;
}

static OMX_ERRORTYPE set_parameter_StandardComponentRole(OMX_IN OMX_PTR param_data, OMX_COMPONENT_PRIVATE *pcomp_priv)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_PARAM_COMPONENTROLETYPE *comp_role = NULL;
    OMX_U32 i = 0;

    comp_role = (OMX_PARAM_COMPONENTROLETYPE*)param_data;
    DEBUG_PRINT("set_param: OMX_IndexParamStandardComponentRole\n");

    for (i = 0; i < COUNTOF(codec_trans_list); i++)
    {
        if (!strncmp((char*)codec_trans_list[i].role_name,
                     (char*)comp_role->cRole, OMX_MAX_STRINGNAME_SIZE))
        {
            break;
        }
    }

    if (i >= COUNTOF(codec_trans_list))
    {
        DEBUG_PRINT_ERROR("fmt %s not support\n", comp_role->cRole);
        ret = OMX_ErrorUnsupportedSetting;
    }
    else
    {
        strncpy((char*)pcomp_priv->m_role,
                (char*)codec_trans_list[i].role_name, OMX_MAX_STRINGNAME_SIZE - 1);

        pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr.enVencType =
            codec_trans_list[i].codec_type;

        pcomp_priv->m_encoder_fmt = codec_trans_list[i].compress_fmt;
    }

    return ret;
}

/* ==========================================================================
   FUNCTION
   set_parameter

   DESCRIPTION
   OMX Set Parameter method implementation.

   PARAMETERS
   <TBD>.

   RETURN VALUE
   OMX Error None if successful. Or Error Type.
   ==========================================================================*/
static OMX_ERRORTYPE  set_parameter(OMX_IN OMX_HANDLETYPE phandle,
                                    OMX_IN OMX_INDEXTYPE param_index,
                                    OMX_IN OMX_PTR param_data)
{
    OMX_S32 param;
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE *pcomp = NULL;
    OMX_COMPONENT_PRIVATE *pcomp_priv = NULL;

    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(param_data == NULL);

    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcomp_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    if (!pcomp_priv)
    {
        DEBUG_PRINT_ERROR("set_parameter: pcomp_priv is null\n");

        return OMX_ErrorBadParameter;
    }

    param = (OMX_S32)param_index;

    switch (param)
    {
        case OMX_IndexParamPortDefinition:
        {
            ret = set_parameter_PortDefinition(param_data, pcomp_priv);
            break;
        }
        case OMX_IndexParamVideoAvc:
        {
            ret = set_parameter_VideoAVC(param_data, pcomp_priv);
            break;
        }
    #ifdef OMXVENC_SUPPORT_HEVC
        case OMX_IndexParamVideoHevc:
        {
            ret = set_parameter_VideoHevc(param_data, pcomp_priv);
            break;
        }
    #endif
        case OMX_IndexParamVideoBitrate:
        {
            ret = set_parameter_VideoBitrate(param_data, pcomp_priv);
            break;
        }

        case OMX_IndexParamVideoPortFormat:
        {
            ret = set_parameter_VideoPortFormat(param_data, pcomp_priv);
            break;
        }

#ifdef KHRONOS_1_1
        case OMX_IndexParamStandardComponentRole:
        {
            ret = set_parameter_StandardComponentRole(param_data, pcomp_priv);
            break;
        }
#endif

        case OMX_IndexParamVideoProfileLevelCurrent:
        {
            OMX_VIDEO_PARAM_PROFILELEVELTYPE *profileLevelType =
                (OMX_VIDEO_PARAM_PROFILELEVELTYPE*)param_data;

            DEBUG_PRINT("set_param: OMX_IndexParamVideoProfileLevelCurrent,PortIndex = %ld,state = %ld\n",
                        (OMX_S32)profileLevelType->nPortIndex, (OMX_S32)pcomp_priv->m_state);

            if (profileLevelType->nPortIndex != OUTPUT_PORT_INDEX)
            {
                DEBUG_PRINT_ERROR("Bad Port idx %ld\n", (OMX_S32)profileLevelType->nPortIndex);

                return OMX_ErrorBadPortIndex;
            }

            ret = set_current_profile_level(pcomp_priv, profileLevelType);
            break;
        }

#ifdef ANDROID
        case OMX_GoogleIndexEnableAndroidNativeBuffers:
        {
            struct EnableAndroidNativeBuffersParams *penable = (struct EnableAndroidNativeBuffersParams*)param_data;

            DEBUG_PRINT("set_parameter: OMX_GoogleIndexEnableAndroidNativeBuffers-> nPortIndex (%d),enable(%d)\n",
                        (int)penable->nPortIndex, (int)penable->bEnable);

            if (penable->nPortIndex != OUTPUT_PORT_INDEX)
            {
                DEBUG_PRINT_ERROR("set_parameter: Bad port index %d\n", (int)penable->nPortIndex);

                return OMX_ErrorBadPortIndex;
            }

            pcomp_priv->m_use_native_buf = penable->bEnable;

            break;
        }

        case OMX_GoogleIndexStoreMetaDataInBuffers:
        {
            struct StoreMetaDataInBuffersParams *penable = (struct StoreMetaDataInBuffersParams*)param_data;

            DEBUG_PRINT("set_parameter: OMX_GoogleIndexStoreMetaDataInBuffers-> nPortIndex (%d),enable(%d)\n",
                        (int)penable->nPortIndex, (int)penable->bStoreMetaData);

            if (penable->nPortIndex != INPUT_PORT_INDEX)
            {
                DEBUG_PRINT_ERROR("set_parameter: Bad port index %d\n", (int)penable->nPortIndex);

                return OMX_ErrorBadPortIndex;
            }

            pcomp_priv->m_store_metadata_buf = penable->bStoreMetaData;

            break;
        }
#endif
        case OMX_GoogleIndexPrependSPSPPSToIDRFrames:
        {
            struct PrependSPSPPSToIDRFramesParams *penable = (struct PrependSPSPPSToIDRFramesParams*)param_data;
            venc_chan_cfg *pVencChnAttr = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg;

            DEBUG_PRINT("set_parameter: OMX_GoogleIndexPrependSPSPPSToIDRFrames-> enable(%d)\n", (int)penable->bEnable);

            if (0 == pcomp_priv->drv_ctx.venc_chan_attr.state)   //not create Chn yet
            {
                pVencChnAttr->bPrependSpsPps = penable->bEnable;
            }
            else
            {
                DEBUG_PRINT_ERROR("ERROR: set_parameter: OMX_HisiIndexAutoRequestIFrm-> enable(%d) no use!\n", penable->bEnable);
            }

            pcomp_priv->m_prepend_sps_pps = penable->bEnable;

            break;
        }

        case OMX_HisiIndexAutoRequestIFrm:
        {
            struct AutoRequestIFrmParams *penable = (struct AutoRequestIFrmParams*)param_data;
            venc_chan_cfg *pVencChnAttr = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg;

            DEBUG_PRINT("set_parameter: OMX_HisiIndexAutoRequestIFrm-> enable(%d)\n", (int)penable->bEnable);

            if (0 == pcomp_priv->drv_ctx.venc_chan_attr.state)   //not create Chn yet
            {
                pVencChnAttr->bAutoRequestIFrm = penable->bEnable;
            }
            else
            {
                DEBUG_PRINT_ERROR("ERROR: set_parameter: OMX_HisiIndexAutoRequestIFrm-> enable(%d) no use!\n", penable->bEnable);
            }
            break;
        }

        default:
            DEBUG_PRINT_ERROR("set_param: unknown param 0x%08x\n", param_index);
            ret = OMX_ErrorUnsupportedIndex;
            break;
    }

    return ret;
}



/* =========================================================================
   FUNCTION
   get_config

   DESCRIPTION
   OMX Get Config Method implementation.

   PARAMETERS
   <TBD>.

   RETURN VALUE
   OMX Error None if successful. Or Error Type.
   =========================================================================*/
static OMX_ERRORTYPE  get_config(OMX_IN OMX_HANDLETYPE   phandle,
                                 OMX_IN OMX_INDEXTYPE config_index,
                                 OMX_INOUT OMX_PTR     config_data)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcomp_priv = NULL;
    //OMX_CONFIG_RECTTYPE *prect = NULL;
    HI_UNF_VENC_CHN_ATTR_S* pVencUnfAttrs = NULL;
    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(config_data == NULL);

    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcomp_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    if (!pcomp_priv)
    {
        DEBUG_PRINT_ERROR("get_config: pcomp_priv = NULL!\n");
        return OMX_ErrorBadParameter;
    }

    pVencUnfAttrs = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr;

    switch (config_index)
    {
        case OMX_IndexConfigCommonOutputCrop:
        {
            OMX_CONFIG_RECTTYPE* prect = (OMX_CONFIG_RECTTYPE*)config_data;

            DEBUG_PRINT("get_config: OMX_IndexConfigCommonOutputCrop\n");

            if (prect->nPortIndex != OUTPUT_PORT_INDEX)
            { return OMX_ErrorBadPortIndex; }

            break;
        }
        case OMX_IndexConfigVideoAVCIntraPeriod:
        {
            OMX_VIDEO_CONFIG_AVCINTRAPERIOD* ptr_gop = (OMX_VIDEO_CONFIG_AVCINTRAPERIOD*)config_data;
            DEBUG_PRINT("get_config: OMX_IndexConfigVideoAVCIntraPeriod\n");
            if (ptr_gop->nPortIndex != OUTPUT_PORT_INDEX)
            { return OMX_ErrorBadPortIndex; }
            ptr_gop->nIDRPeriod = pVencUnfAttrs->u32Gop;
            ptr_gop->nPFrames   = pVencUnfAttrs->u32Gop - 1;

            break;
        }
        case OMX_IndexConfigVideoFramerate:
        {
            OMX_CONFIG_FRAMERATETYPE* ptr_framerate = (OMX_CONFIG_FRAMERATETYPE*)config_data;
            DEBUG_PRINT("get_config: OMX_IndexConfigVideoFramerate\n");
            if (ptr_framerate->nPortIndex == OUTPUT_PORT_INDEX)  //get the output framerate
            {
                ptr_framerate->xEncodeFramerate = pVencUnfAttrs->u32TargetFrmRate << 16;
            }
            else                                       //get the input  framerate
            {
                ptr_framerate->xEncodeFramerate = pVencUnfAttrs->u32InputFrmRate << 16;
            }
            break;
        }
        case OMX_IndexConfigVideoBitrate:
        {
            OMX_VIDEO_CONFIG_BITRATETYPE* ptr_bitrate =  (OMX_VIDEO_CONFIG_BITRATETYPE*)config_data;
            DEBUG_PRINT("get_config: OMX_IndexConfigVideoBitrate\n");
            if (ptr_bitrate->nPortIndex != OUTPUT_PORT_INDEX)  //get the output framerate
            {
                return OMX_ErrorBadPortIndex;
            }

            ptr_bitrate->nEncodeBitrate = pVencUnfAttrs->u32TargetBitRate;
            break;
        }
        default:
            DEBUG_PRINT_ERROR("get_config: unknown index 0x%08x\n",
                              config_index);
            ret = OMX_ErrorBadParameter;
            break;
    }

    return ret;
}


/* ========================================================================
   FUNCTION
   set_config

   DESCRIPTION
   OMX Set Config method implementation

   PARAMETERS
   <TBD>.

   RETURN VALUE
   OMX Error None if successful.
   ========================================================================*/
static OMX_ERRORTYPE  set_config(OMX_IN OMX_HANDLETYPE phandle,
                                 OMX_IN OMX_INDEXTYPE config_index, OMX_IN OMX_PTR config_data)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcomp_priv = NULL;
    HI_UNF_VENC_CHN_ATTR_S* pVencUnfAttrs = NULL;
    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(config_data == NULL);

    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcomp_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    if (!pcomp_priv)
    {
        DEBUG_PRINT_ERROR("get_config: pcomp_priv = NULL!\n");
        return OMX_ErrorBadParameter;
    }

    pVencUnfAttrs = &pcomp_priv->drv_ctx.venc_chan_attr.chan_cfg.VencUnfAttr;
    switch (config_index)
    {
        case OMX_IndexConfigCommonOutputCrop:
        {
            OMX_CONFIG_RECTTYPE* prect = (OMX_CONFIG_RECTTYPE*)config_data;

            DEBUG_PRINT("set_config: OMX_IndexConfigCommonOutputCrop\n");

            if (prect->nPortIndex != OUTPUT_PORT_INDEX)
            { return OMX_ErrorBadPortIndex; }

            break;
        }
        case OMX_IndexConfigVideoAVCIntraPeriod:
        {
            OMX_VIDEO_CONFIG_AVCINTRAPERIOD* ptr_gop = (OMX_VIDEO_CONFIG_AVCINTRAPERIOD*)config_data;
            DEBUG_PRINT("set_config: OMX_IndexConfigVideoAVCIntraPeriod\n");
            if (ptr_gop->nPortIndex != OUTPUT_PORT_INDEX)
            { return OMX_ErrorBadPortIndex; }
            pVencUnfAttrs->u32Gop = ptr_gop->nIDRPeriod;

            if (0 != pcomp_priv->drv_ctx.venc_chan_attr.state)
            {
                if (channel_set_attr(&(pcomp_priv->drv_ctx)) < 0)
                {
                    DEBUG_PRINT_ERROR("ERROR: channel set attr failed!\n");
                    ret = OMX_ErrorHardware;
                    omx_report_error(pcomp_priv, ret);
                }
            }
            break;
        }
        case OMX_IndexConfigVideoFramerate:
        {
            OMX_CONFIG_FRAMERATETYPE* ptr_framerate = (OMX_CONFIG_FRAMERATETYPE*)config_data;
            DEBUG_PRINT("set_config: OMX_IndexConfigVideoFramerate:port(%lu)\n", ptr_framerate->nPortIndex);

            if (ptr_framerate->nPortIndex > OUTPUT_PORT_INDEX)
            {
                return OMX_ErrorBadPortIndex;
            }
            pVencUnfAttrs->u32TargetFrmRate = ptr_framerate->xEncodeFramerate >> 16 ;
            pVencUnfAttrs->u32InputFrmRate  = ptr_framerate->xEncodeFramerate >> 16 ;
            pcomp_priv->m_port[ptr_framerate->nPortIndex].port_def.format.video.xFramerate = ptr_framerate->xEncodeFramerate;

            if (0 != pcomp_priv->drv_ctx.venc_chan_attr.state)
            {
                if (channel_set_attr(&(pcomp_priv->drv_ctx)) < 0)
                {
                    DEBUG_PRINT_ERROR("ERROR: channel set attr failed!\n");
                    ret = OMX_ErrorHardware;
                    omx_report_error(pcomp_priv, ret);
                    return ret;
                }
            }

            break;
        }
        case OMX_IndexConfigVideoBitrate:
        {
            OMX_VIDEO_CONFIG_BITRATETYPE* ptr_bitrate =  (OMX_VIDEO_CONFIG_BITRATETYPE*)config_data;
            DEBUG_PRINT("set_config: OMX_IndexConfigVideoBitrate\n");
            if (ptr_bitrate->nPortIndex != OUTPUT_PORT_INDEX)  //get the output framerate
            {
                return OMX_ErrorBadPortIndex;
            }
            pVencUnfAttrs->u32TargetBitRate = ptr_bitrate->nEncodeBitrate ;
            pcomp_priv->m_port[ptr_bitrate->nPortIndex].port_def.format.video.nBitrate = ptr_bitrate->nEncodeBitrate;
            if (0 != pcomp_priv->drv_ctx.venc_chan_attr.state)
            {
                if (channel_set_attr(&(pcomp_priv->drv_ctx)) < 0)
                {
                    DEBUG_PRINT_ERROR("ERROR: channel set attr failed!\n");
                    ret = OMX_ErrorHardware;
                    omx_report_error(pcomp_priv, ret);
                }
            }
            break;
        }
        case OMX_IndexConfigVideoIntraVOPRefresh:
        {
            OMX_CONFIG_INTRAREFRESHVOPTYPE* pVideoIntraVOPRefresh = (OMX_CONFIG_INTRAREFRESHVOPTYPE*)config_data;
            DEBUG_PRINT("set_config: OMX_IndexConfigVideoIntraVOPRefresh\n");
            if (pVideoIntraVOPRefresh->nPortIndex != OUTPUT_PORT_INDEX)
            {
                return OMX_ErrorBadPortIndex;
            }

            if (pVideoIntraVOPRefresh->IntraRefreshVOP)
            {
                if (1 == pcomp_priv->drv_ctx.venc_chan_attr.state) /*if component's state is Excuting*/
                {
                    if (channel_request_IFrame(&(pcomp_priv->drv_ctx)) < 0)
                    {
                        DEBUG_PRINT_ERROR("ERROR: channel set attr failed!\n");
                        ret = OMX_ErrorHardware;
                        omx_report_error(pcomp_priv, ret);
                    }
                }
            }
            break;
        }
        default:
            DEBUG_PRINT_ERROR("set_config: unknown index 0x%08x\n",
                              config_index);
            ret = OMX_ErrorBadParameter;
            break;
    }

    return ret;
}


/* =========================================================================
   FUNCTION
   get_extension_index

   DESCRIPTION
   OMX GetExtensionIndex method implementaion.  <TBD>

   PARAMETERS
   <TBD>.

   RETURN VALUE
   OMX Error None if everything successful.
   =========================================================================*/
static OMX_ERRORTYPE  get_extension_index(OMX_IN OMX_HANDLETYPE phandle,
        OMX_IN OMX_STRING param_name,
        OMX_OUT OMX_INDEXTYPE* pindex_type)
{
    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(param_name == NULL);
    OMX_CHECK_ARG_RETURN(pindex_type == NULL);


    OMX_U32 param_length = strlen(param_name);

    if (!strncmp(param_name, "OMX.Hisi.Param.Index.ChannelAttributes",\
                MAX(param_length, strlen("OMX.Hisi.Param.Index.ChannelAttributes"))))
    {
        *pindex_type = OMX_HisiIndexChannelAttributes;
    }
    else if (!strncmp(param_name, "OMX.google.android.index.prependSPSPPSToIDRFrames",\
                      MAX(param_length, strlen("OMX.google.android.index.prependSPSPPSToIDRFrames"))))
    {
        *pindex_type = OMX_GoogleIndexPrependSPSPPSToIDRFrames;
    }

    else if (!strncmp(param_name, "OMX.google.android.index.enableAndroidNativeBuffers",\
                      MAX(param_length, strlen("OMX.google.android.index.enableAndroidNativeBuffers"))))
    {
        *pindex_type = OMX_GoogleIndexEnableAndroidNativeBuffers;
    }
    else if (!strncmp(param_name, "OMX.google.android.index.storeMetaDataInBuffers",\
                      MAX(param_length, strlen("OMX.google.android.index.storeMetaDataInBuffers"))))
    {
        *pindex_type = OMX_GoogleIndexStoreMetaDataInBuffers;
    }
    else if (!strncmp(param_name, "OMX.google.android.index.useAndroidNativeBuffer2",\
                      MAX(param_length, strlen("OMX.google.android.index.useAndroidNativeBuffer2"))))
    {
        *pindex_type = OMX_GoogleIndexUseAndroidNativeBuffer;
    }
    else if (!strncmp(param_name, "OMX.Hisi.android.index.getParameterSet",\
                      MAX(param_length, strlen("OMX.Hisi.android.index.getParameterSet"))))
    {
        *pindex_type = OMX_HisiIndexGetParameterSet;
    }
    else if (!strncmp(param_name, "OMX.Hisi.android.index.autoRequestIFrmScnChg",\
                      MAX(param_length, strlen("OMX.Hisi.android.index.autoRequestIFrmScnChg"))))
    {
        *pindex_type = OMX_HisiIndexAutoRequestIFrm;
    }

    else
    {
        DEBUG_PRINT_ERROR("%s not implemented!\n", param_name);
        return OMX_ErrorNotImplemented;

    }

    DEBUG_PRINT("get_extension_index : param_name:%s pindex_type = %d!\n", param_name, *pindex_type);

    return OMX_ErrorNone;
}


/* ======================================================================
   FUNCTION
   get_state

   DESCRIPTION
   Returns the state information back to the caller.<TBD>

   PARAMETERS
   <TBD>.

   RETURN VALUE
   Error None if everything is successful.
   =======================================================================*/
static OMX_ERRORTYPE get_state(OMX_IN OMX_HANDLETYPE  phandle,
                               OMX_OUT OMX_STATETYPE* state)
{
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcomp_priv = NULL;

    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(state == NULL);

    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcomp_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    *state = pcomp_priv->m_state;
    return OMX_ErrorNone;
}


/* ======================================================================
   FUNCTION
   component_tunnel_request

   DESCRIPTION
   OMX Component Tunnel Request method implementation. Now not supported

   PARAMETERS
   None.

   RETURN VALUE
   OMX Error None if everything successful.
   =======================================================================*/
static OMX_ERRORTYPE  component_tunnel_request(
    OMX_IN OMX_HANDLETYPE phandle,
    OMX_IN OMX_U32 port,
    OMX_IN OMX_HANDLETYPE peerComponent,
    OMX_IN OMX_U32 peerPort,
    OMX_INOUT OMX_TUNNELSETUPTYPE* tunnelSetup)
{
    DEBUG_PRINT_ERROR("Error: Tunnel mode Not Implemented\n");
    return OMX_ErrorNotImplemented;
}


/* ======================================================================
   FUNCTION
   omx_vdec::AllocateBuffer. API Call

   DESCRIPTION
   None

   PARAMETERS
   None.

   RETURN VALUE
   OMX_TRUE/OMX_FALSE
   =======================================================================*/
static OMX_ERRORTYPE  allocate_buffer(OMX_IN OMX_HANDLETYPE  phandle,
                                      OMX_INOUT OMX_BUFFERHEADERTYPE** omx_bufhdr,
                                      OMX_IN OMX_U32 port,
                                      OMX_IN OMX_PTR app_data,
                                      OMX_IN OMX_U32 bytes)
{
    OMX_ERRORTYPE ret                = OMX_ErrorNone;
    OMX_COMPONENTTYPE* pcomp         = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;
    OMX_PORT_PRIVATE* port_priv      = NULL;

    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(omx_bufhdr == NULL);

    if (port > OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT_ERROR("[AB]Error: Invalid Port %ld\n", (OMX_S32)port);
        return OMX_ErrorBadPortIndex;
    }

    pcomp     = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    //state check
    if (!pcom_priv)
    {
        DEBUG_PRINT_ERROR("[AB] ERROR: pcom_priv = NULL!\n");
        return OMX_ErrorBadParameter;
    }

    if ((pcom_priv->m_state == OMX_StateIdle) ||
        (pcom_priv->m_state == OMX_StateExecuting) ||
        ((pcom_priv->m_state == OMX_StateLoaded) &&
         bit_present(&pcom_priv->m_flags, OMX_STATE_IDLE_PENDING)))                      //ֻ������������²��������ڴ�?
    {
        DEBUG_PRINT("[AB] Current State %d\n", pcom_priv->m_state);
    }
    else
    {
        DEBUG_PRINT("[AB] Invalid State %d to alloc the buffer !\n", pcom_priv->m_state);
        return OMX_ErrorIncorrectStateOperation;
    }

    ret = allocate_buffer_internal(                                                             //�ڲ�����buffer����
              pcom_priv, omx_bufhdr, app_data, port, bytes);
    if (ret != OMX_ErrorNone)
    {
        DEBUG_PRINT_ERROR("[AB] ERROR: Allocate Buf failed\n");
        return ret;
    }

    if ((port == INPUT_PORT_INDEX) && port_full(pcom_priv, port))
    {
        port_priv = &pcom_priv->m_port[port];

        if (port_priv->port_def.bEnabled)
        { port_priv->port_def.bPopulated = OMX_TRUE; }

        if (bit_present(&pcom_priv->m_flags, OMX_STATE_INPUT_ENABLE_PENDING))
        {
            bit_clear(&pcom_priv->m_flags, OMX_STATE_INPUT_ENABLE_PENDING);

            post_event(pcom_priv,                                                        //�� ����:OMX_CommandPortEnable ѹ����У�д��ܵ�
                       OMX_CommandPortEnable, INPUT_PORT_INDEX, OMX_GENERATE_COMMAND_DONE);
        }
    }

    if ((port == OUTPUT_PORT_INDEX) && port_full(pcom_priv, port))
    {
        port_priv = &pcom_priv->m_port[port];

        if (port_priv->port_def.bEnabled)
        { port_priv->port_def.bPopulated = OMX_TRUE; }

        if (bit_present(&pcom_priv->m_flags, OMX_STATE_OUTPUT_ENABLE_PENDING))
        {
            DEBUG_PRINT_STATE("[OmxState] Enable_Pending --> Enable\n");
            bit_clear(&pcom_priv->m_flags, OMX_STATE_OUTPUT_ENABLE_PENDING);

            post_event(pcom_priv,
                       OMX_CommandPortEnable, OUTPUT_PORT_INDEX, OMX_GENERATE_COMMAND_DONE);
        }
    }

    if (ports_all_full(pcom_priv))
    {
        if (bit_present(&pcom_priv->m_flags, OMX_STATE_IDLE_PENDING))
        {
            // Send the callback now
            DEBUG_PRINT_STATE("[OmxState] Idle_Pending --> Idle\n");

            bit_clear((&pcom_priv->m_flags), OMX_STATE_IDLE_PENDING);
            post_event(pcom_priv, OMX_CommandStateSet, OMX_StateIdle, OMX_GENERATE_COMMAND_DONE);
        }
    }

    return  OMX_ErrorNone;
}


/* ======================================================================
   FUNCTION
   FreeBuffer

   DESCRIPTION

   PARAMETERS
   None.

   RETURN VALUE
   OMX_TRUE/OMX_FALSE
   ======================================================================*/
static OMX_ERRORTYPE  free_buffer(OMX_IN OMX_HANDLETYPE phandle,
                                  OMX_IN OMX_U32 port,
                                  OMX_IN OMX_BUFFERHEADERTYPE* omx_bufhdr)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;
#ifdef __OMXVENC_RGB_BUFFER__
    HI_MMZ_BUF_S stBuf_RGB;
#endif

    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(omx_bufhdr == NULL);
    DEBUG_PRINT(" free_buffer : %lu!\n", port);
    if (port > OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT_ERROR("[AB]Error: Invalid Port %ld\n", (OMX_S32)port);
        return OMX_ErrorBadPortIndex;
    }

    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    //state check
    if (!pcom_priv)
    {
        DEBUG_PRINT_ERROR("[AB] ERROR: Invalid State\n");
        return OMX_ErrorBadParameter;
    }

    if ((pcom_priv->m_state == OMX_StateLoaded) ||
        (pcom_priv->m_state == OMX_StateExecuting) ||
        (pcom_priv->m_state == OMX_StateIdle))
    {
        DEBUG_PRINT("[AB] Current State %d\n", pcom_priv->m_state);
    }
    else
    {
        DEBUG_PRINT("[AB] Invalid State %d\n", pcom_priv->m_state);
        return OMX_ErrorIncorrectStateOperation;
    }

    ret = free_buffer_internal(pcom_priv, port, omx_bufhdr);
    if (ret != OMX_ErrorNone)
    {
        DEBUG_PRINT_ERROR("[FB]ERROR: free Buf internal failed\n");
        return ret;
    }

    if ((port == INPUT_PORT_INDEX) && port_empty(pcom_priv, port))
    {
        if (bit_present((&pcom_priv->m_flags),
                        OMX_STATE_INPUT_DISABLE_PENDING))
        {
            DEBUG_PRINT_STATE("[ST]port state Disable Pending ->Disable\n");
            bit_clear((&pcom_priv->m_flags),
                      OMX_STATE_INPUT_DISABLE_PENDING);

            post_event(pcom_priv, OMX_CommandPortDisable,
                       INPUT_PORT_INDEX,
                       OMX_GENERATE_COMMAND_DONE);
        }
    }

    if ((port == OUTPUT_PORT_INDEX) && port_empty(pcom_priv, port))
    {

        if (bit_present(&pcom_priv->m_flags,
                        OMX_STATE_OUTPUT_DISABLE_PENDING))
        {
            DEBUG_PRINT_STATE("[ST]port state Disable Pending ->Disable\n");
            bit_clear((&pcom_priv->m_flags),
                      OMX_STATE_OUTPUT_DISABLE_PENDING);

            post_event(pcom_priv, OMX_CommandPortDisable,
                       OUTPUT_PORT_INDEX,
                       OMX_GENERATE_COMMAND_DONE);
        }
    }

    if (ports_all_empty(pcom_priv))
    {
        if (bit_present(&pcom_priv->m_flags, OMX_STATE_LOADING_PENDING))
        {
            DEBUG_PRINT_STATE("loaded-pending ->loaded\n");
            bit_clear((&pcom_priv->m_flags),
                      OMX_STATE_LOADING_PENDING);

            post_event(pcom_priv, OMX_CommandStateSet,
                       OMX_StateLoaded,
                       OMX_GENERATE_COMMAND_DONE);

            pcom_priv->msg_thread_exit = OMX_TRUE;

            if (channel_destroy(&pcom_priv->drv_ctx) < 0)
            {
                DEBUG_PRINT_ERROR("ERROR: channel create failed!\n");
                ret = OMX_ErrorHardware;
            }
#ifdef __OMXVENC_RGB_BUFFER__
            stBuf_RGB.phyaddr      = pcom_priv->bufferaddr_Phy_RGB;
            stBuf_RGB.user_viraddr = pcom_priv->bufferaddr_RGB;
            stBuf_RGB.bufsize      = pcom_priv->buffer_size_RGB;
            if (pcom_priv->m_store_metadata_buf)
            {
                if (HI_MMZ_Free(&stBuf_RGB) != 0)
                {
                    DEBUG_PRINT_ERROR("ERROR: channel free RGB buffer for StoreMetaData failed!\n");
                    ret = OMX_ErrorHardware;
                }
                pcom_priv->bufferaddr_Phy_RGB = 0;
                pcom_priv->bufferaddr_RGB     = 0;
                pcom_priv->buffer_size_RGB    = 0;
            }
#endif
        }
    }
    return ret;
}


/* ======================================================================
   FUNCTION
   omx_vdec::UseBuffer

   DESCRIPTION
   OMX Use Buffer method implementation.

   PARAMETERS
   <TBD>.

   RETURN VALUE
   OMX Error None , if everything successful.
   =====================================================================*/
static OMX_ERRORTYPE use_buffer(
    OMX_IN OMX_HANDLETYPE            phandle,
    OMX_INOUT OMX_BUFFERHEADERTYPE** bufferHdr,
    OMX_IN OMX_U32                   port,
    OMX_IN OMX_PTR                   app_data,
    OMX_IN OMX_U32                   bytes,
    OMX_IN OMX_U8*                   buffer)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone; // OMX return type
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;
    OMX_PORT_PRIVATE* port_priv = NULL;

    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(bufferHdr == NULL);
    OMX_CHECK_ARG_RETURN(buffer == NULL);

    if (port > OUTPUT_PORT_INDEX)
    {
        DEBUG_PRINT_ERROR("[UB] Error: Invalid Port %d\n", (int)port);
        return OMX_ErrorBadPortIndex;
    }

    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    //state check
    if (!pcom_priv)
    {
        DEBUG_PRINT_ERROR("[UB] ERROR: Invalid State\n");
        return OMX_ErrorBadParameter;
    }

    if ((pcom_priv->m_state == OMX_StateIdle) || (pcom_priv->m_state == OMX_StateExecuting) ||
        ((pcom_priv->m_state == OMX_StateLoaded) && bit_present(&pcom_priv->m_flags, OMX_STATE_IDLE_PENDING)))
    {
        DEBUG_PRINT("[UB] Cur State %d\n", pcom_priv->m_state);
    }
    else
    {
        DEBUG_PRINT_ERROR("[UB] Invalid State %d\n", pcom_priv->m_state);
        return OMX_ErrorIncorrectStateOperation;
    }

#ifdef ANDROID
    if (pcom_priv->m_use_native_buf /*&& OUTPUT_PORT_INDEX == port*/)
    {
        ret = use_android_native_buffer_internal(pcom_priv, bufferHdr, app_data, port, bytes, buffer);
        if (ret != OMX_ErrorNone)
        {
            DEBUG_PRINT_ERROR("[UB]ERROR: use_android_native_buffer_internal failed\n");
            return OMX_ErrorInsufficientResources;
        }
    }
    else
#endif
    {
        ret = use_buffer_internal(pcom_priv, bufferHdr, app_data, port, bytes, buffer);
        if (ret != OMX_ErrorNone)
        {
            DEBUG_PRINT_ERROR("[UB]ERROR: use_buffer_internal failed\n");
            return OMX_ErrorInsufficientResources;
        }
    }

    if ((port == INPUT_PORT_INDEX) && port_full(pcom_priv, port))
    {
        port_priv = &pcom_priv->m_port[port];

        if (port_priv->port_def.bEnabled)
        { port_priv->port_def.bPopulated = OMX_TRUE; }

        if (bit_present(&pcom_priv->m_flags, OMX_STATE_INPUT_ENABLE_PENDING))
        {
            bit_clear(&pcom_priv->m_flags, OMX_STATE_INPUT_ENABLE_PENDING);
            post_event(pcom_priv,                                                        //�� ����:OMX_CommandPortEnable ѹ����У�д��ܵ�
                       OMX_CommandPortEnable, INPUT_PORT_INDEX, OMX_GENERATE_COMMAND_DONE);
        }
    }

    if ((port == OUTPUT_PORT_INDEX) && port_full(pcom_priv, port))
    {
        port_priv = &pcom_priv->m_port[port];

        if (port_priv->port_def.bEnabled)
        { port_priv->port_def.bPopulated = OMX_TRUE; }

        if (bit_present(&pcom_priv->m_flags, OMX_STATE_OUTPUT_ENABLE_PENDING))
        {
            DEBUG_PRINT_STATE("[OmxState] Enable_Pending --> Enable\n");
            bit_clear(&pcom_priv->m_flags, OMX_STATE_OUTPUT_ENABLE_PENDING);

            post_event(pcom_priv,
                       OMX_CommandPortEnable, OUTPUT_PORT_INDEX, OMX_GENERATE_COMMAND_DONE);
        }
    }

    if (ports_all_full(pcom_priv))
    {
        if (bit_present(&pcom_priv->m_flags, OMX_STATE_IDLE_PENDING))
        {
            // Send the callback now
            DEBUG_PRINT_STATE("[OmxState] Idle_Pending --> Idle\n");

            bit_clear((&pcom_priv->m_flags), OMX_STATE_IDLE_PENDING);
            post_event(pcom_priv, OMX_CommandStateSet, OMX_StateIdle, OMX_GENERATE_COMMAND_DONE);
        }
    }

    return  OMX_ErrorNone;
}


/* ======================================================================
   FUNCTION
   EmptyThisBuffer

   DESCRIPTION
   This routine is used to push the encoded video frames to
   the video decoder.

   PARAMETERS
   None.

   RETURN VALUE
   OMX Error None if everything went successful.
   =======================================================================*/
static OMX_ERRORTYPE  empty_this_buffer(OMX_IN OMX_HANDLETYPE phandle,
                                        OMX_IN OMX_BUFFERHEADERTYPE* buffer)
{
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;
    OMX_PORT_PRIVATE* port_priv = NULL;

    OMX_U32 i;

    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(buffer == NULL);

    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;
    //state check
    if (!pcom_priv)
    {
        DEBUG_PRINT_ERROR("[UB] ERROR: Invalid State\n");
        return OMX_ErrorBadParameter;
    }

    port_priv = &pcom_priv->m_port[INPUT_PORT_INDEX];

    if (pcom_priv->m_state != OMX_StateExecuting)
    {
        DEBUG_PRINT_ERROR("[ETB]ERROR: Invalid State\n");
        return OMX_ErrorIncorrectStateOperation;
    }

    if (!port_priv->port_def.bEnabled)
    {
        DEBUG_PRINT_ERROR("[ETB]ERROR: in port disabled.\n");
        return OMX_ErrorIncorrectStateOperation;
    }

    for (i = 0; i < port_priv->port_def.nBufferCountActual; i++)
    {
        if (buffer == port_priv->m_omx_bufhead[i])
        {
            break;
        }
    }

    if (i >= port_priv->port_def.nBufferCountActual)
    {
        DEBUG_PRINT_ERROR("no buffers found for address[%p]", buffer);
        return OMX_ErrorBadParameter;
    }

    if (buffer->nInputPortIndex != port_priv->port_def.nPortIndex/*INPUT_PORT_INDEX*/)
    {
        DEBUG_PRINT_ERROR("[ETB]ERROR:ETB invalid port \n");
        return OMX_ErrorBadPortIndex;
    }

    DEBUG_PRINT_EFTB("[ETB]bufhdr = %p, bufhdr->pbuffer = %p,nTimeStamp = %lld\n", buffer, buffer->pBuffer, buffer->nTimeStamp);
    post_event(pcom_priv, (OMX_U32)buffer, 0, OMX_GENERATE_ETB);

#ifdef __VENC_DBG_DELAY_STAT__
    if (etb_id < 100)
    {
        OMX_S32 ret = 0;
        ret = gettimeofday (&TmpTime[etb_id][0] , NULL);
        if (ret == 0)
        {
            etb_id++;
        }
    }
#endif

    return OMX_ErrorNone;
}


/* ======================================================================
   FUNCTION
   FillThisBuffer

   DESCRIPTION
   IL client uses this method to release the frame buffer
   after displaying them.

   PARAMETERS
   None

   RETURN VALUE
   OMX_TRUE/OMX_FALSE
   =======================================================================*/
static OMX_ERRORTYPE  fill_this_buffer(OMX_IN OMX_HANDLETYPE  phandle,
                                       OMX_IN OMX_BUFFERHEADERTYPE* buffer)
{
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;
    OMX_PORT_PRIVATE* port_priv = NULL;
    OMX_U32 i;

    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(buffer == NULL);

    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;
    if (!pcom_priv)
    {
        DEBUG_PRINT_ERROR("[UB] ERROR: Invalid State\n");
        return OMX_ErrorBadParameter;
    }
    port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];         //should be :port_priv = &pcom_priv->m_port[buffer->nOutputPortIndex]

    /* check component state */
    if (pcom_priv->m_state != OMX_StateExecuting)
    {
        DEBUG_PRINT_ERROR("[FTB]ERROR:Invalid State\n");
        return OMX_ErrorIncorrectStateOperation;
    }

    /* check port state */
    if (!port_priv->port_def.bEnabled)
    {
        DEBUG_PRINT_ERROR("[FTB]ERROR: out port disabled!\n");
        return OMX_ErrorIncorrectStateOperation;
    }

    /* check buffer validate */
    for (i = 0; i < port_priv->port_def.nBufferCountActual; i++)
    {
        if (buffer == port_priv->m_omx_bufhead[i])
        {
            break;
        }
    }

    if (i >= port_priv->port_def.nBufferCountActual)
    {
        DEBUG_PRINT_ERROR("[FTB]ERROR: buffers[%p] match failed\n", buffer);
        return OMX_ErrorBadParameter;
    }

    if (buffer->nOutputPortIndex != port_priv->port_def.nPortIndex/*OUTPUT_PORT_INDEX*/)
    {
        DEBUG_PRINT_ERROR("[FTB]ERROR:FTB invalid port\n");
        return OMX_ErrorBadParameter;
    }

    DEBUG_PRINT_STREAM("[FTB] bufhdr = %p, bufhdr->pBuffer = %p\n",
                       buffer, buffer->pBuffer);

    post_event(pcom_priv, (OMX_U32)buffer, 0, OMX_GENERATE_FTB);
#ifdef ENABLE_BUFFER_LOCK
    sem_post(&pcom_priv->m_buf_lock);
#endif
#ifdef __VENC_DBG_DELAY_STAT__
    if (ftb_id <= 100)
    {
        int ret = 0;
        ret = gettimeofday (&TmpTime[ftb_id][3] , NULL);
        if (ret == 0)
        {
            ftb_id++;
        }
    }
#endif

    return OMX_ErrorNone;
}


/* ======================================================================
   FUNCTION
   SetCallbacks

   DESCRIPTION
   Set the callbacks.

   PARAMETERS
   None.

   RETURN VALUE
   OMX Error None if everything successful.
   =======================================================================*/
static OMX_ERRORTYPE  set_callbacks(OMX_IN OMX_HANDLETYPE phandle,
                                    OMX_IN OMX_CALLBACKTYPE* callbacks, OMX_IN OMX_PTR app_data)
{
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;

    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(callbacks == NULL);
    OMX_CHECK_ARG_RETURN(callbacks->EventHandler == NULL);
    OMX_CHECK_ARG_RETURN(callbacks->EmptyBufferDone == NULL);
    OMX_CHECK_ARG_RETURN(callbacks->FillBufferDone == NULL);

    pcomp = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    pcom_priv->m_cb       = *callbacks;
    pcom_priv->m_app_data = app_data;

    return OMX_ErrorNone;
}


/* ======================================================================
   FUNCTION
   component_role_enum

   DESCRIPTION
   enum role omx component support

   PARAMETERS
   None.

   RETURN VALUE
   OMX Error None if everything successful.
   =======================================================================*/
static OMX_ERRORTYPE  component_role_enum(
    OMX_IN OMX_HANDLETYPE phandle, OMX_OUT OMX_U8* role,
    OMX_IN OMX_U32 nindex)
{
    OMX_ERRORTYPE ret = OMX_ErrorNone;
    OMX_CHECK_ARG_RETURN(phandle == NULL);
    OMX_CHECK_ARG_RETURN(role == NULL);

    if (nindex > COUNTOF(codec_trans_list) - 1)
    {
        DEBUG_PRINT("component_role_enum: no more roles\n");
        return OMX_ErrorNoMore;
    }

    strncpy((char*)role,
            (char*)codec_trans_list[nindex].role_name, OMX_MAX_STRINGNAME_SIZE - 1);

    return ret;
}


/* ======================================================================
   FUNCTION
   component_deinit

   DESCRIPTION
   component deinit, used to destroy component.

   PARAMETERS
   None.

   RETURN VALUE
   OMX Error None if everything successful.
   =======================================================================*/
OMX_ERRORTYPE  component_deinit(OMX_IN OMX_HANDLETYPE phandle)
{
    OMX_COMPONENTTYPE* pcomp = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;
    OMX_PORT_PRIVATE* port_priv = NULL;

    OMX_U32 i = 0;

    OMX_CHECK_ARG_RETURN(phandle == NULL);

    pcomp     = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)pcomp->pComponentPrivate;

    OMX_CHECK_ARG_RETURN(pcom_priv == NULL);

    if (OMX_StateLoaded != pcom_priv->m_state)                           //just can deinit the component when it is in the state of OMX_StateLoaded
    {
        DEBUG_PRINT_ERROR("OMX not in LOADED state!\n");
        DEBUG_PRINT_ERROR("current state %d\n", pcom_priv->m_state);
        return OMX_ErrorIncorrectStateOperation;
    }
    venc_deinit_drv_context(&pcom_priv->drv_ctx);                        // the venc hardwork device should be deinit
#ifdef __OMXVENC_RGB_BUFFER__
    {
        HI_MMZ_BUF_S stBuf_RGB;
        if (pcom_priv->bufferaddr_Phy_RGB != 0)
        {
            stBuf_RGB.phyaddr      = pcom_priv->bufferaddr_Phy_RGB;
            stBuf_RGB.user_viraddr = pcom_priv->bufferaddr_RGB;
            stBuf_RGB.bufsize      = pcom_priv->buffer_size_RGB;
            if (HI_MMZ_Free(&stBuf_RGB) != 0)
            {
                DEBUG_PRINT_ERROR("ERROR: channel free RGB buffer for StoreMetaData failed!\n");
            }
            pcom_priv->bufferaddr_Phy_RGB = 0;
            pcom_priv->bufferaddr_RGB     = 0;
            pcom_priv->buffer_size_RGB    = 0;
        }
    }
#endif
    /* Check port is deinit */
    if (!port_empty(pcom_priv, OUTPUT_PORT_INDEX))
    {
        port_priv = &pcom_priv->m_port[OUTPUT_PORT_INDEX];
        for (i = 0; i < port_priv->port_def.nBufferCountActual; i++)
        {
            if (port_priv->m_omx_bufhead[i] != NULL)
            {
                if (free_buffer_internal(pcom_priv, OUTPUT_PORT_INDEX, port_priv->m_omx_bufhead[i]) != OMX_ErrorNone)
                {
                    DEBUG_PRINT("free buffer internal err!\n");
                }
            }
        }
    }
    if (!port_empty(pcom_priv, INPUT_PORT_INDEX))
    {
        port_priv = &pcom_priv->m_port[INPUT_PORT_INDEX];
        for (i = 0; i < port_priv->port_def.nBufferCountActual; i++)
        {
            if (port_priv->m_omx_bufhead[i] != NULL)
            {
                if (free_buffer_internal(pcom_priv, INPUT_PORT_INDEX, port_priv->m_omx_bufhead[i]) != OMX_ErrorNone)
                {
                    DEBUG_PRINT("free buffer internal err!\n");
                }
            }
        }
    }

    ports_deinit(pcom_priv);
    if (!pcom_priv->msg_thread_exit)
    {
        pcom_priv->msg_thread_exit = OMX_TRUE;
        pthread_join(pcom_priv->msg_thread_id, NULL);
    }

    if (pcom_priv->m_store_metadata_buf == 1)
    {
        //HI_TDE2_Close();
    }
    /////////////////////
    close(pcom_priv->m_pipe_in);
    close(pcom_priv->m_pipe_out);
    sem_wait(&pcom_priv->m_async_sem);
    if (!pcom_priv->event_thread_exit)
    {
        pcom_priv->event_thread_exit = OMX_TRUE;
        sem_post(&pcom_priv->m_async_sem);
        pthread_join(pcom_priv->event_thread_id, NULL);
    }
    else
    {
        sem_post(&pcom_priv->m_async_sem);
    }
    (HI_VOID)pthread_mutex_destroy(&pcom_priv->m_lock);
    sem_destroy(&pcom_priv->m_cmd_lock);
    sem_destroy(&pcom_priv->m_async_sem);
#ifdef ENABLE_BUFFER_LOCK
    sem_post(&pcom_priv->m_buf_lock);
    sem_destroy(&pcom_priv->m_buf_lock);
#endif
    free(pcom_priv);
    pcom_priv = NULL;
    pcomp->pComponentPrivate = NULL;

#ifdef __OMXVENC_FILE_OUT_SAVE__
    if (g_pFiletoSave != NULL)
    {
        fclose(g_pFiletoSave);
        g_pFiletoSave = NULL;
    }
#endif

#ifdef __OMXVENC_FILE_IN_SAVE__
    if (g_pFiletoEnc != NULL)
    {
        fclose(g_pFiletoEnc);
        g_pFiletoEnc = NULL;
    }
    if (g_pU)
    {
       free(g_pU);
       g_pU = NULL;
    }
    if (g_pV)
    {
       free(g_pV);
       g_pV = NULL;
    }
#endif
#ifdef  __OMXRGB_FILE_IN_SAVE__
    if(g_rgbtoSave != NULL)
    {
        fclose(g_rgbtoSave);
        g_rgbtoSave = NULL;
    }
#endif
    DEBUG_PRINT("Hisilicon venc Omx Component exit!\n");

    return OMX_ErrorNone;
}


/* ======================================================================
   FUNCTION
   component_init

   DESCRIPTION
   component init

   PARAMETERS
   None.

   RETURN VALUE
   OMX Error None if everything successful.
   =======================================================================*/
OMX_ERRORTYPE component_init(OMX_HANDLETYPE phandle,
                             OMX_STRING comp_name)
{

    OMX_ERRORTYPE          error     = OMX_ErrorNone;
    OMX_COMPONENTTYPE*     pcomp     = NULL;
    OMX_COMPONENT_PRIVATE* pcom_priv = NULL;

    int fds[2];
    OMX_S32 result = -1;

    OMX_CHECK_ARG_RETURN(phandle == NULL);

    if (strncmp(comp_name, OMX_VENC_COMPONENT_NAME, sizeof(OMX_VENC_COMPONENT_NAME)) != 0)
    {
        DEBUG_PRINT_ERROR("compname:  %s not match \n", comp_name);
        return OMX_ErrorBadParameter;
    }

    pcomp     = (OMX_COMPONENTTYPE*)phandle;
    pcom_priv = (OMX_COMPONENT_PRIVATE*)malloc(sizeof(OMX_COMPONENT_PRIVATE));

    if (!pcom_priv)
    {
        DEBUG_PRINT_ERROR("component_init(): malloc failed\n");
        return OMX_ErrorInsufficientResources;
    }

    memset(pcom_priv, 0 , sizeof(OMX_COMPONENT_PRIVATE));

    pcom_priv->m_flags                    = 0;
    pcom_priv->event_thread_exit        = OMX_FALSE;
    pcom_priv->m_pre_timestamp            = 0;                             //PTS

    pcom_priv->m_encoder_fmt            = OMX_VIDEO_CodingUnused;


    strncpy((char*)pcom_priv->m_comp_name, (char*)comp_name, OMX_MAX_STRINGNAME_SIZE - 1);

    init_event_queue(&pcom_priv->m_cmd_q);
    init_event_queue(&pcom_priv->m_ftb_q);
    init_event_queue(&pcom_priv->m_etb_q);

    if (pthread_mutex_init(&pcom_priv->m_lock, NULL))
    {
        error = OMX_ErrorInsufficientResources;
        goto error_exit;
    }
    (HI_VOID)sem_init(&pcom_priv->m_cmd_lock,  0, 0);
    (HI_VOID)sem_init(&pcom_priv->m_async_sem, 0, 0);
#ifdef ENABLE_BUFFER_LOCK
    (HI_VOID)sem_init(&pcom_priv->m_buf_lock, 0, 100);
#endif
    /* create event theard */
    result = pthread_create(&pcom_priv->event_thread_id,
                            0, event_thread, pcom_priv);
    if (result < 0)
    {
        DEBUG_PRINT_ERROR("ERROR: failed to create event thread\n");
        error = OMX_ErrorInsufficientResources;
        goto error_exit0;
    }

    result = pipe(fds);
    if (result < 0)
    {
        DEBUG_PRINT_ERROR("pipe creation failed\n");
        error = OMX_ErrorInsufficientResources;
        goto error_exit1;
    }
    pcom_priv->m_pipe_in    = fds[0];
    pcom_priv->m_pipe_out   = fds[1];


    /******* set the default port attr *******************/
    result = ports_init(pcom_priv);
    if (result < 0)
    {
        DEBUG_PRINT_ERROR("pipe creation failed\n");
        error = OMX_ErrorInsufficientResources;
        goto error_exit2;
    }

    result = venc_init_drv_context(&pcom_priv->drv_ctx);
    if (result < 0)
    {
        DEBUG_PRINT_ERROR("drv ctx init failed\n");
        error = OMX_ErrorUndefined;
        goto error_exit4;
    }

    venc_get_default_attr(&pcom_priv->drv_ctx);

    /* init component callbacks */
    CONFIG_VERSION_SIZE(pcomp , OMX_COMPONENTTYPE);

    pcomp->SetCallbacks                = set_callbacks;
    pcomp->GetComponentVersion        = get_component_version;
    pcomp->SendCommand                = send_command;
    pcomp->GetParameter                = get_parameter;
    pcomp->SetParameter                = set_parameter;
    pcomp->GetState                    = get_state;
    pcomp->AllocateBuffer            = allocate_buffer;
    pcomp->FreeBuffer                = free_buffer;
    pcomp->EmptyThisBuffer            = empty_this_buffer;
    pcomp->FillThisBuffer           = fill_this_buffer;
    pcomp->ComponentDeInit            = component_deinit;

    pcomp->GetConfig                = get_config;
    pcomp->SetConfig                = set_config;
    pcomp->ComponentTunnelRequest    = component_tunnel_request;         //not support yet
    pcomp->UseBuffer                = use_buffer;                       //not support yet
    pcomp->GetExtensionIndex        = get_extension_index;              //not support yet
#ifdef KHRONOS_1_1
    pcomp->ComponentRoleEnum        = component_role_enum;
#endif

    pcomp->pComponentPrivate        = pcom_priv;
    pcom_priv->m_pcomp                = pcomp;

    pcom_priv->m_state                = OMX_StateLoaded;

    sem_post(&pcom_priv->m_async_sem);

#ifdef __OMXVENC_FILE_OUT_SAVE__
    {
        HI_CHAR RealPath[PATH_MAX + 1] = {0x0};
        if (strlen(DBG_OUT_FILENAME) > PATH_MAX || NULL == realpath(DBG_OUT_FILENAME,RealPath))
        {
            DEBUG_PRINT_ERROR("Error: FiletoSave[out] open error!!");
        }
        else
        {
            g_pFiletoSave = fopen(RealPath, "wb+");
            if (g_pFiletoSave == NULL)
            {
                DEBUG_PRINT_ERROR("FiletoSave[out]: open error!!");
            }
            else
            {
                DEBUG_PRINT("FiletoSave[out]: open OK!!");
            }
        }
    }
#endif

#ifdef __OMXVENC_FILE_IN_SAVE__
    {
        HI_CHAR RealPath[PATH_MAX + 1] = {0x0};
        if (strlen(DBG_IN_FILENAME) > PATH_MAX || NULL == realpath(DBG_IN_FILENAME,RealPath))
        {
            DEBUG_PRINT_ERROR("Error: FiletoSave[in] open error!!");
        }
        else
        {
            g_pFiletoEnc = fopen(RealPath, "wb+");
            if (g_pFiletoEnc == NULL)
            {
                DEBUG_PRINT_ERROR("FiletoSave[in]: open error!!");
            }
            else
            {
                DEBUG_PRINT("FiletoSave[in]: open OK!!");
                g_pU = malloc(1920 * 1088 / 4 * sizeof(HI_U8));
                if (g_pU)
                {
                    memset(g_pU, 0, 1920 * 1088 / 4 * sizeof(HI_U8));
                }
                g_pV = malloc(1920 * 1088 / 4 * sizeof(HI_U8));
                if (g_pV)
                {
                    memset(g_pV, 0, 1920 * 1088 / 4 * sizeof(HI_U8));
                }
            }
        }
    }

    g_u32CountNum = 0;
    g_u32CountNum_etb = 0;
#endif
#ifdef __OMXRGB_FILE_IN_SAVE__
    {
        HI_CHAR RealPath[PATH_MAX + 1] = {0x0};
        if (strlen(DBG_RGB_FILENAME) > PATH_MAX || NULL == realpath(DBG_RGB_FILENAME,RealPath))
        {
            DEBUG_PRINT_ERROR("Error: FiletoSave[rgb] open error!!");
        }
        else
        {
            g_rgbtoSave = fopen(RealPath, "wb+");
            if (g_rgbtoSave == NULL)
            {
                DEBUG_PRINT_ERROR("FiletoSave[rgb]: open error!!");
            }
            else
            {
                DEBUG_PRINT("FiletoSave[rgb]: open OK!!");
            }
        }
    }
#endif
    DEBUG_PRINT("Hisilicon Video Encoder Omx Component Verision 1.0");


    return OMX_ErrorNone;

error_exit4:
    ports_deinit(pcom_priv);
error_exit2:
    close(pcom_priv->m_pipe_in);
    close(pcom_priv->m_pipe_out);
error_exit1:
    sem_post(&pcom_priv->m_async_sem);
    pcom_priv->event_thread_exit        = OMX_TRUE;
    pthread_join(pcom_priv->event_thread_id, NULL);
error_exit0:
    (HI_VOID)pthread_mutex_destroy(&pcom_priv->m_lock);
#ifdef ENABLE_BUFFER_LOCK
    sem_destroy(&pcom_priv->m_buf_lock);
#endif
    sem_destroy(&pcom_priv->m_cmd_lock);
    sem_destroy(&pcom_priv->m_async_sem);
error_exit:
    free(pcom_priv);
    pcom_priv = NULL;
    pcomp->pComponentPrivate = NULL;

    return error;
}
