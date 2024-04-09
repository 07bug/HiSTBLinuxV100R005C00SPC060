#define LOG_TAG "AV"

#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

#include "hi_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_vo.h"
#include "hi_unf_sound.h"
#include "hi_video_codec.h"
#include "hi_mpi_avplay.h"
#include "hi_mpi_vdec.h"
#include "hi_drv_sync.h"
#include "hi_unf_session_manager.h"

#include "HA.AUDIO.AC3PASSTHROUGH.decode.h"
#include "HA.AUDIO.DTSPASSTHROUGH.decode.h"
#include "HA.AUDIO.TRUEHDPASSTHROUGH.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DTSHD.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.COOK.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "HA.AUDIO.AMRWB.codec.h"
#include "HA.AUDIO.FFMPEG_DECODE.decode.h"
#include "HA.AUDIO.FFMPEG_WMAPRO.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.DTSM6.decode.h"
#include "HA.AUDIO.DOLBYTRUEHD.decode.h"
#include "HA.AUDIO.BLURAYLPCM.decode.h"
#include "HA.AUDIO.DOLBYPLUS.decode.h"

#include "tvos_hal_common.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_av.h"

/***************************** Macro Definition ************************/
/** av handle mode ID */
#define AV_INJECT_MODE_ID              (0x1f00)

/** max number of av player handle */
#define AV_HAL_MAX_COUNT               (32)

/** max number of av inject handle */
#define AV_INJECT_MAX_COUNT            (96)

/** invalid handle */
#define AV_HAL_INVALID_IDX             (AV_HAL_MAX_COUNT + 1)
#define AV_INJECT_INVALID_IDX          (AV_INJECT_MAX_COUNT + 1)

/** Invalid handle */
/** CNcomment:ÈùûÊ≥ïÂè•ÊüÑ */
#define AV_MAX_EVENT_NUM               (32)

#define AV_VDEC_CAP_LEVEL_4096_WIDTH   (4096)
#define AV_VDEC_CAP_LEVEL_2160_HEIGHT  (2160)

#define AV_VDEC_CAP_LEVEL_2160_WIDTH   (2160)
#define AV_VDEC_CAP_LEVEL_1280_HEIGHT  (1280)

#define AV_MAX_AUDIO_CACHE_BUF         (64*1024)

#define AV_SLEEP_10_MS                 (1000 * 10)
#define AV_INVALID_PTS                 (-1)
#define AV_INVALID_PID                 (0x1FFF)
#define AV_NORMAL_PLAY_SPEED           (100)
#define AV_MAX_VDEC_5NUMBER            (5)
#define AV_MAX_VDEC_1NUMBER            (1)
#define AV_VDEC_30FPS                  (30)
#define AV_VDEC_1FPS                   (1)

#define AV_HEADER_VERSION       (1)
#define AV_DEVICE_API_VERSION_1_0 HARDWARE_DEVICE_API_VERSION_2(1, 0, AV_HEADER_VERSION)

#define PTHREAD_MUTEX_T pthread_mutex_t

#define AV_SDK_INVALID_PTS              (0xffffffff)
#define AV_SDK_PTS_TO_HAL(pts)          (AV_SDK_INVALID_PTS == (pts) ? AV_INVALID_PTS : (S64)(pts))
#define AV_HANDLE_Lock()                (VOID)pthread_mutex_lock(&s_AvHandleMutex)
#define AV_HANDLE_UnLock()              (VOID)pthread_mutex_unlock(&s_AvHandleMutex)

#define AV_DO_FUNC(func, ret) \
    do {   \
        (ret) = func; \
        if (SUCCESS != (ret)) \
        { \
            HAL_ERROR("Do %s error, error code = 0x%08x", #func, (ret)); \
        } \
    } while (0)

#define AV_MIN(a, b) ((a) < (b) ? (a) : (b))

#ifdef HI_HD_FULL
#define AV_AUDIO_BUFF_SIZE          (256* 1024)
#define AV_VIDEO_BUFF_SIZE          (3 * 1024 * 1024)
#else
#define AV_AUDIO_BUFF_SIZE          (2 * 1024 * 1024)
#define AV_VIDEO_BUFF_SIZE          (20 * 1024 * 1024)
#endif

/*************************** Structure Definition **********************/

/** info of av player handle */
typedef struct _AV_HAL_INFO_S
{
    U32    u32AvIdx;         /* index of av handle in s_stAvHandleInfo array */
    HANDLE hAvPlayerSdk;    /* handle of sdk avplay */
    HANDLE hVidInjecter;    /* handle of Video inject */
    HANDLE hAudInjecter;    /* handle of Audio inject */
    HANDLE hWindowSdk;      /* handle of sdk window */
    HANDLE hTrackSdk;       /* handle of sdk track not used*/
    HANDLE hSM;             /* session manager handler */
    BOOL   bFreezeVideo;    /* does freeze video */
    BOOL   bVidStart;
    BOOL   bAudStart;

    DOLBYPLUS_STREAM_INFO_S         stDolbyStreamInfo;      /* real dolby stream info */
    DOLBYPLUS_DECODE_OPENCONFIG_S   stDolbyDecOpenConfig;   /* dolby dec info */
    HI_UNF_AVPLAY_STREAM_TYPE_E     enStreamType;           /* stream type of avplay used */
    DMX_ID_E enDemuxId;                                     /* demux id */

    AV_SETTINGS_S stAvSettings;
    AV_EVT_CONFIG_PARAMS_S stAvCbParam[AV_MAX_EVENT_NUM];
} AV_HAL_INFO_S;

typedef struct _AV_HAL_HANDLE_S
{
    HANDLE hAvHal;              /**< handle of av */
    BOOL   bUsed;               /**< used flag */
    AV_HAL_INFO_S* pstAvHalInfo;
} AV_HAL_HANDLE_S;

/** info of inject */
typedef struct _AV_INJECT_INFO_S
{
    HI_UNF_AVPLAY_MEDIA_CHAN_E enAvChanType;
    HANDLE hAvHal;              /**< av handle that inject attached */
    BOOL   bTerm;               /**< term current operation */
    AV_INJECT_SETTINGS_S stInjectSettings;
} AV_INJECT_INFO_S;

typedef struct _AV_INJECT_HANDLE_S
{
    HANDLE hInject;             /**< handle of inject */
    BOOL   bUsed;               /**< used flag */
    AV_INJECT_INFO_S *pstInjecterInfo;
} AV_INJECT_HANDLE_S;



/** init flag of av player module */
static BOOL s_bAvInit = FALSE;

/** handle list of av play */
static AV_HAL_HANDLE_S s_stAvHandleInfo[AV_HAL_MAX_COUNT];

/** handle list of inject */
static AV_INJECT_HANDLE_S s_stInjectHandleInfo[AV_INJECT_MAX_COUNT];

/** mutex of av play*/
static PTHREAD_MUTEX_T s_AvHandleMutex = PTHREAD_MUTEX_INITIALIZER;

/////////////////////////////////////////////////////////////////////////////////////////

static VOID* AV_MALLOCZ(U32 size)
{
    if(0 == size)
    {
        return NULL;
    }

    VOID* ptr = malloc(size);

    if (ptr)
    {
        memset(ptr, 0, size);
    }

    return ptr;
}

static VOID AV_FREEP(VOID* arg)
{
    VOID** ptr = (VOID**)arg;

    if (ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
    }
}

static S32 av_start_video(AV_DEVICE_S* pstDev, HANDLE hAvHandle);
static S32 av_start_audio(AV_DEVICE_S* pstDev, HANDLE hAvHandle);
static S32 av_stop_video(AV_DEVICE_S* pstDev,  HANDLE hAvHandle);
static S32 av_stop_audio(AV_DEVICE_S* pstDev,  HANDLE hAvHandle);
static S32 av_get_status(AV_DEVICE_S* pstDev,  const HANDLE hAvHandle, AV_STATUS_S* pstStatus);
static S32 av_injecter_detach(AV_DEVICE_S* pstDev, const HANDLE hInjecter);
static S32 av_inject_get_status(AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                AV_INJECT_STATUS_S* const pstStatus);
static S32 AV_SDK_EvtCallback(HANDLE hAvPlayerSdk, HI_UNF_AVPLAY_EVENT_E enEvent, VOID *pPara);
static S32 AV_SDK_GetVdecInfo(HANDLE hAvPlayerSdk, HI_UNF_AVPLAY_VDEC_INFO_S* pstVdecInfo);

extern HI_S32 HI_MPI_AVPLAY_GetWindowHandle(HI_HANDLE hAvplay, HI_HANDLE* phWindow);
extern HI_S32 HI_MPI_AVPLAY_GetSndHandle(HI_HANDLE hAvplay, HI_HANDLE* phTrack);

static inline U32 AV_GetSystemTime()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    return (U32)(tv.tv_sec % 10000000 * 1000 + tv.tv_usec / 1000);
}

static inline S32 AV_IS_Init(VOID)
{
    return ((s_bAvInit == TRUE) ? 1 : 0);
}

static inline S32 AV_MALLOC_HANDLE_Index(const HANDLE hAvHandle)
{
    U32 u32Index = 0;

    for (u32Index = 0; u32Index < AV_HAL_MAX_COUNT; u32Index++)
    {
        if (AV_INVALID_HANDLE == hAvHandle &&
            hAvHandle == s_stAvHandleInfo[u32Index].hAvHal &&
                !s_stAvHandleInfo[u32Index].bUsed)
            {
                break;
            }
    }
    if (AV_HAL_MAX_COUNT <= u32Index)
    { return AV_HAL_INVALID_IDX; }
    return u32Index;
}
static inline S32 AV_GET_HANDLE_Index(const HANDLE hAvHandle)
{
    U32 u32Index = 0;
    for (u32Index = 0; u32Index < AV_HAL_MAX_COUNT; u32Index++)
    {
        if (AV_INVALID_HANDLE == hAvHandle)
        {
             return AV_HAL_INVALID_IDX;
        }
        else if (hAvHandle == s_stAvHandleInfo[u32Index].hAvHal)
        {
            break;
        }
    }

    if (AV_HAL_MAX_COUNT <= u32Index)
    { return AV_HAL_INVALID_IDX; }

    return u32Index;
}

static inline S32 AV_HANDLE_IdxByAvPlayer(const HANDLE hAvPlayerSdk)
{
    U32 u32Index = 0;
    AV_HAL_INFO_S* pstAvInfo = NULL;

    /* find sdk av player handle in s_stAvHandleInfo arrary */
    for (u32Index = 0; u32Index < AV_HAL_MAX_COUNT; u32Index++)
    {
        if (AV_INVALID_HANDLE == s_stAvHandleInfo[u32Index].hAvHal
            || !s_stAvHandleInfo[u32Index].bUsed
            || NULL == s_stAvHandleInfo[u32Index].pstAvHalInfo)
        {
            continue;
        }

        pstAvInfo = (AV_HAL_INFO_S*)s_stAvHandleInfo[u32Index].pstAvHalInfo;

        if (hAvPlayerSdk == pstAvInfo->hAvPlayerSdk)
        { break; }
    }

    if (AV_HAL_MAX_COUNT <= u32Index)
    { return AV_HAL_INVALID_IDX; }

    return u32Index;
}

static inline S32 AV_MALLOC_INJECT_Index(const HANDLE hAvInjectHdl)
{
    U32 u32Index = 0;

    for (u32Index = 0; u32Index < AV_INJECT_MAX_COUNT; u32Index++)
    {
        if (AV_INVALID_HANDLE == hAvInjectHdl &&
            hAvInjectHdl == s_stInjectHandleInfo[u32Index].hInject &&
            FALSE  == s_stInjectHandleInfo[u32Index].bUsed)
            {
                break;
            }
    }
    if (AV_INJECT_MAX_COUNT <= u32Index)
    { return AV_INJECT_INVALID_IDX; }
    return u32Index;
}
static inline S32 AV_GET_INJECT_Index(const HANDLE hAvInjectHdl)
{
    U32 u32Index = 0;
    for (u32Index = 0; u32Index < AV_INJECT_MAX_COUNT; u32Index++)
    {
        if (AV_INVALID_HANDLE == hAvInjectHdl)
        {
            return AV_INJECT_INVALID_IDX;
        }
        else if (hAvInjectHdl == s_stInjectHandleInfo[u32Index].hInject)
        {
            break;
        }
    }

    if (AV_INJECT_MAX_COUNT <= u32Index)
    { return AV_INJECT_INVALID_IDX; }

    return u32Index;
}

static U32 AV_HANDLE_Num(HI_VOID)
{
    U32 i = 0;
    U32 u32Num = 0;

    for (i = 0; i < AV_HAL_MAX_COUNT; i++)
    {
        if (AV_INVALID_HANDLE != s_stAvHandleInfo[i].hAvHal)
        {
            u32Num++;
        }
    }

    return u32Num;
}

static U32 AV_INJECT_Num(HI_VOID)
{
    U32 i = 0;
    U32 u32Num = 0;

    for (i = 0; i < AV_INJECT_MAX_COUNT; i++)
    {
        if (AV_INVALID_HANDLE != s_stInjectHandleInfo[i].hInject)
        {
            u32Num++;
        }
    }

    return u32Num;
}

static VOID AV_SDK_StatusToHal(HI_UNF_AVPLAY_STATUS_E eSdkStatus,
                               AV_DECODER_STATE_E* peHalStatus)
{
    switch (eSdkStatus)
    {
        case HI_UNF_AVPLAY_STATUS_STOP:
        case HI_UNF_AVPLAY_STATUS_EOS:
            *peHalStatus = AV_DECODER_STATE_STOPPED;
            break;

        case HI_UNF_AVPLAY_STATUS_PLAY:
        case HI_UNF_AVPLAY_STATUS_TPLAY:
            *peHalStatus = AV_DECODER_STATE_RUNNING;
            break;

        case HI_UNF_AVPLAY_STATUS_PAUSE:
            *peHalStatus = AV_DECODER_STATE_PAUSING;
            break;

        case HI_UNF_AVPLAY_STATUS_PREPLAY:
        case HI_UNF_AVPLAY_STATUS_SEEK:
            *peHalStatus = AV_DECODER_STATE_UNKNOWN;
            break;

        default:
            *peHalStatus = AV_DECODER_STATE_UNKNOWN;
            break;
    }

    return;
}

static VOID AV_SDK_3DFormatToHal(HI_UNF_VIDEO_FRAME_PACKING_TYPE_E eSdkFromatType,
                                 AV_3D_FORMAT_E* pHalFormatType)
{
    switch (eSdkFromatType)
    {
        case HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE:
            *pHalFormatType = AV_3D_FORMAT_SIDE_BY_SIDE;
            break;

        case HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM:
            *pHalFormatType = AV_3D_FORMAT_TOP_AND_BOTTOM;
            break;

        case HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED:
            *pHalFormatType = AV_3D_FORMAT_AUTO;
            break;

        case HI_UNF_FRAME_PACKING_TYPE_FRAME_PACKING:
            *pHalFormatType = AV_3D_FORMAT_FRAME_PACKING;
            break;

        case HI_UNF_FRAME_PACKING_TYPE_NONE:
            *pHalFormatType = AV_3D_FORMAT_OFF;
            break;

        default:
            break;
    }

    return;
}

static VOID AV_HAL_3DFormatToSdk(AV_3D_FORMAT_E eHalFormatType,
                                 HI_UNF_VIDEO_FRAME_PACKING_TYPE_E* pSdkFormatType)
{
    switch ((eHalFormatType))
    {
        case AV_3D_FORMAT_SIDE_BY_SIDE:
        case AV_3D_FORMAT_SIDE_BY_SIDE_FULL:
            *pSdkFormatType = HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE;
            break;

        case AV_3D_FORMAT_TOP_AND_BOTTOM:
            *pSdkFormatType = HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM;
            break;

        case AV_3D_FORMAT_AUTO:
            *pSdkFormatType = HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED;
            break;

        case AV_3D_FORMAT_FRAME_PACKING:
            *pSdkFormatType = HI_UNF_FRAME_PACKING_TYPE_FRAME_PACKING;
            break;

        case AV_3D_FORMAT_OFF:
        case AV_3D_FORMAT_FIELD_ALTERNATIVE:
        case AV_3D_FORMAT_LINE_ALTERNATIVE:
        default:
            *pSdkFormatType = HI_UNF_FRAME_PACKING_TYPE_NONE;
            break;
    }

    return;
}

static VOID AV_SDK_EvtToHal(HANDLE hAvPlayerSdk,
                            HI_UNF_AVPLAY_EVENT_E eSdkEvt,
                            VOID *pParam,
                            AV_EVT_E* peHalEvt)
{
    HI_UNF_AVPLAY_BUF_STATE_E eBufState;

    switch (eSdkEvt)
    {
        case HI_UNF_AVPLAY_EVENT_STOP:
        case HI_UNF_AVPLAY_EVENT_RNG_BUF_STATE:
            break;

        case HI_UNF_AVPLAY_EVENT_EOS:
            *peHalEvt = AV_STREAM_EVT_PLAY_EOS;
            break;

        case HI_UNF_AVPLAY_EVENT_NORM_SWITCH:
            *peHalEvt = AV_VID_EVT_STREAM_FORMAT_CHANGE;
            break;

        case HI_UNF_AVPLAY_EVENT_FRAMEPACKING_CHANGE:
            break;

        case HI_UNF_AVPLAY_EVENT_NEW_VID_FRAME:
            *peHalEvt = AV_VID_EVT_NEW_PICTURE_DECODED;
            break;

        case HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME:
            *peHalEvt = AV_AUD_EVT_NEW_FRAME;
            break;

        case HI_UNF_AVPLAY_EVENT_IFRAME_ERR:
            *peHalEvt = AV_VID_EVT_PICTURE_DECODING_ERROR;
            break;

        case HI_UNF_AVPLAY_EVENT_VID_BUF_STATE:
            eBufState = *(HI_UNF_AVPLAY_BUF_STATE_E*)pParam;

            if (HI_UNF_AVPLAY_BUF_STATE_EMPTY == eBufState
                || HI_UNF_AVPLAY_BUF_STATE_LOW == eBufState)
            {
                *peHalEvt = AV_VID_EVT_UNDERFLOW;
            }
            else if (HI_UNF_AVPLAY_BUF_STATE_FULL == eBufState)
            {
                *peHalEvt = AV_INJECT_EVT_DATA_OVERFLOW;
            }

            break;

        case HI_UNF_AVPLAY_EVENT_AUD_BUF_STATE:
            eBufState = *(HI_UNF_AVPLAY_BUF_STATE_E*)pParam;

            if (HI_UNF_AVPLAY_BUF_STATE_EMPTY == eBufState
                || HI_UNF_AVPLAY_BUF_STATE_LOW == eBufState)
            {
                *peHalEvt = AV_AUD_EVT_UNDERFLOW;
            }
            else if (HI_UNF_AVPLAY_BUF_STATE_FULL == eBufState)
            {
                *peHalEvt = AV_INJECT_EVT_DATA_OVERFLOW;
            }

            break;

        case HI_UNF_AVPLAY_EVENT_VID_UNSUPPORT:
            *peHalEvt = AV_VID_EVT_CODEC_UNSUPPORT;
            break;

        case HI_UNF_AVPLAY_EVENT_AUD_UNSUPPORT:
            *peHalEvt = AV_AUD_EVT_CODEC_UNSUPPORT;
            break;

        case HI_UNF_AVPLAY_EVENT_SYNC_PTS_JUMP:
        {
            HI_UNF_SYNC_PTSJUMP_PARAM_S *pPtsJumpParam = (HI_UNF_SYNC_PTSJUMP_PARAM_S *)pParam;

            if (pPtsJumpParam->enPtsChan == HI_UNF_SYNC_PTS_CHAN_VID)
            {
                *peHalEvt = AV_VID_EVT_PTS_ERROR;
            }
            else if(pPtsJumpParam->enPtsChan == HI_UNF_SYNC_PTS_CHAN_AUD)
            {
                *peHalEvt = AV_AUD_EVT_PTS_ERROR;
            }
            else
            {
                *peHalEvt = AV_EVT_BUTT;
            }

            break;
        }

        case HI_UNF_AVPLAY_EVENT_SYNC_STAT_CHANGE:
        {
            HI_UNF_SYNC_STAT_PARAM_S *pStatParam = (HI_UNF_SYNC_STAT_PARAM_S *)pParam;
            HI_UNF_SYNC_ATTR_S stSync;
            HI_S32 s32Ret = HI_SUCCESS;

            memset(&stSync, 0, sizeof(HI_UNF_SYNC_ATTR_S));
            s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSync);
            if (HI_SUCCESS != s32Ret)
            {
                *peHalEvt = AV_EVT_BUTT;
                break;
            }

            if (pStatParam->s32VidAudDiff >= stSync.stSyncStartRegion.s32VidPlusTime)
            {
                if (stSync.enSyncRef == HI_UNF_SYNC_REF_PCR)
                {
                    *peHalEvt = AV_AUD_EVT_DISCARD_FRAME;
                    break;
                }
            }
            else if (pStatParam->s32VidAudDiff <= stSync.stSyncStartRegion.s32VidNegativeTime)
            {
                *peHalEvt = AV_VID_EVT_DISCARD_FRAME;
                break;
            }

            *peHalEvt = AV_EVT_BUTT;
            break;
        }

        case HI_UNF_AVPLAY_EVENT_VID_FRAME_INFO:
            *peHalEvt = AV_VID_EVT_FRAME_INFO;
            break;

        case HI_UNF_AVPLAY_EVENT_AUD_FRAME_ERR:
            *peHalEvt = AV_AUD_EVT_DECODING_ERROR;
            break;
#ifdef HAL_HISI_EXTEND_H
        case HI_UNF_AVPLAY_EVENT_FIRST_FRAME_DISPLAYED:
            *peHalEvt = AV_VID_EVT_FIRST_FRAME_DISPLAYED;
            break;

        case HI_UNF_AVPLAY_EVENT_VID_LASTFRMFLAG:
            *peHalEvt = AV_VID_EVT_LASTFRMFLAG;
            break;
#endif
        case HI_UNF_AVPLAY_EVENT_NEW_USER_DATA:
        case HI_UNF_AVPLAY_EVENT_GET_AUD_ES:
        case HI_UNF_AVPLAY_EVENT_VID_ERR_RATIO:
        case HI_UNF_AVPLAY_EVENT_AUD_INFO_CHANGE:
        default:
            *peHalEvt = AV_EVT_BUTT;
            break;
    }

    return;
}

static VOID AV_HAL_EvtToSdk(AV_EVT_E enHalEvt, HI_UNF_AVPLAY_EVENT_E* penSdkEvent1, HI_UNF_AVPLAY_EVENT_E* penSdkEvent2)
{
    *penSdkEvent1 = HI_UNF_AVPLAY_EVENT_BUTT;
    *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_BUTT;

    switch (enHalEvt)
    {
        case AV_VID_EVT_DECODE_START:
        case AV_AUD_EVT_DECODE_START:
        case AV_VID_EVT_DECODE_STOPPED:
        case AV_AUD_EVT_DECODE_STOPPED:
            /* current not support */
            break;

        case AV_VID_EVT_NEW_PICTURE_DECODED:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_NEW_VID_FRAME;
            break;

        case AV_AUD_EVT_NEW_FRAME:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME;
            break;

        case AV_VID_EVT_ASPECT_RATIO_CHANGE:
            /* current not support, should support it */
            break;

        case AV_VID_EVT_STREAM_FORMAT_CHANGE:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_NORM_SWITCH;
            break;

        case AV_VID_EVT_OUT_OF_SYNC:
        case AV_VID_EVT_BACK_TO_SYNC:
        case AV_AUD_EVT_OUT_OF_SYNC:
        case AV_AUD_EVT_BACK_TO_SYNC:
            /* current not support */
            break;

        case AV_VID_EVT_DATA_OVERFLOW:
        case AV_VID_EVT_DATA_UNDERFLOW:
        case AV_AUD_EVT_PCM_UNDERFLOW:
        case AV_AUD_EVT_FIFO_OVERFLOW:
        case AV_AUD_EVT_LOW_DATA_LEVEL:
            /* current not support, maybe vout and aout should support it */
            break;

        case AV_VID_EVT_CODEC_UNSUPPORT:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_VID_UNSUPPORT;

            break;

        case AV_AUD_EVT_CODEC_UNSUPPORT:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_AUD_UNSUPPORT;
            break;

        case AV_STREAM_EVT_PLAY_EOS:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_EOS;
            break;

        case AV_AUD_EVT_UNDERFLOW:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_AUD_BUF_STATE;
            break;

        case AV_VID_EVT_UNDERFLOW:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_VID_BUF_STATE;
            break;

        case AV_INJECT_EVT_DATA_OVERFLOW:
            *penSdkEvent1 = HI_UNF_AVPLAY_EVENT_AUD_BUF_STATE;
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_VID_BUF_STATE;
            break;

        case AV_VID_EVT_PICTURE_DECODING_ERROR:
            *penSdkEvent2 =  HI_UNF_AVPLAY_EVENT_IFRAME_ERR;
            break;

        case AV_INJECT_EVT_IMPOSSIBLE_WITH_MEM_PROFILE:
            break;

        case AV_AUD_EVT_DISCARD_FRAME:
        case AV_VID_EVT_DISCARD_FRAME:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_SYNC_STAT_CHANGE;
            break;

        case AV_AUD_EVT_PTS_ERROR:
        case AV_VID_EVT_PTS_ERROR:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_SYNC_PTS_JUMP;
            break;

        case AV_AUD_EVT_DECODING_ERROR:
            *penSdkEvent2 =  HI_UNF_AVPLAY_EVENT_AUD_FRAME_ERR;
            break;

#ifdef HAL_HISI_EXTEND_H
        case AV_VID_EVT_FIRST_FRAME_DISPLAYED:
             *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_FIRST_FRAME_DISPLAYED;
            break;

        case AV_VID_EVT_LASTFRMFLAG:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_VID_LASTFRMFLAG;
            break;
#endif
        case AV_VID_EVT_FRAME_INFO:
            *penSdkEvent2 = HI_UNF_AVPLAY_EVENT_VID_FRAME_INFO;
            break;

        default:
            break;
    }

    return;
}

static VOID AV_HAL_VidCodecToSdk(AV_VID_STREAM_TYPE_E eHalStreamType,
                                 HI_UNF_VCODEC_TYPE_E* peCodecType)
{
    switch (eHalStreamType)
    {
        case AV_VID_STREAM_TYPE_MPEG2:
            *peCodecType = HI_UNF_VCODEC_TYPE_MPEG2;
            break;

        case AV_VID_STREAM_TYPE_MPEG4:
        case AV_VID_STREAM_TYPE_REALMAGICMPEG4:
            *peCodecType = HI_UNF_VCODEC_TYPE_MPEG4;
            break;

        case AV_VID_STREAM_TYPE_DIVX:
            *peCodecType = HI_UNF_VCODEC_TYPE_BUTT;
            HAL_ERROR("Divx is not support\n");
            break;

        case AV_VID_STREAM_TYPE_AVS:
        case AV_VID_STREAM_TYPE_AVSPLUS:
            *peCodecType = HI_UNF_VCODEC_TYPE_AVS;
            break;

        case AV_VID_STREAM_TYPE_H263:
            *peCodecType = HI_UNF_VCODEC_TYPE_H263;
            break;

        case AV_VID_STREAM_TYPE_H264:
            *peCodecType = HI_UNF_VCODEC_TYPE_H264;
            break;

        case AV_VID_STREAM_TYPE_REAL8:
            *peCodecType = HI_UNF_VCODEC_TYPE_REAL8;
            break;

        case AV_VID_STREAM_TYPE_REAL9:
            *peCodecType = HI_UNF_VCODEC_TYPE_REAL9;
            break;

        case AV_VID_STREAM_TYPE_VC1:
        case AV_VID_STREAM_TYPE_WMV3:
            *peCodecType = HI_UNF_VCODEC_TYPE_VC1;
            break;

        case AV_VID_STREAM_TYPE_VP6:
            *peCodecType = HI_UNF_VCODEC_TYPE_VP6;
            break;

        case AV_VID_STREAM_TYPE_VP6F:
            *peCodecType = HI_UNF_VCODEC_TYPE_VP6F;
            break;

        case AV_VID_STREAM_TYPE_VP6A:
            *peCodecType = HI_UNF_VCODEC_TYPE_VP6A;
            break;

        case AV_VID_STREAM_TYPE_MJPEG:
            *peCodecType = HI_UNF_VCODEC_TYPE_MJPEG;
            break;

        case AV_VID_STREAM_TYPE_SORENSON:
            *peCodecType = HI_UNF_VCODEC_TYPE_SORENSON;
            break;

        case AV_VID_STREAM_TYPE_DIVX3:
            *peCodecType = HI_UNF_VCODEC_TYPE_DIVX3;
            break;

        case AV_VID_STREAM_TYPE_RAW:
            *peCodecType = HI_UNF_VCODEC_TYPE_RAW;
            break;

        case AV_VID_STREAM_TYPE_JPEG:
            *peCodecType = HI_UNF_VCODEC_TYPE_JPEG;
            break;

        case AV_VID_STREAM_TYPE_VP8:
            *peCodecType = HI_UNF_VCODEC_TYPE_VP8;
            break;

        case AV_VID_STREAM_TYPE_VP9:
            *peCodecType = HI_UNF_VCODEC_TYPE_VP9;
            break;

        case AV_VID_STREAM_TYPE_MSMPEG4V1:
            *peCodecType = HI_UNF_VCODEC_TYPE_MSMPEG4V1;
            break;

        case AV_VID_STREAM_TYPE_MSMPEG4V2:
            *peCodecType = HI_UNF_VCODEC_TYPE_MSMPEG4V2;
            break;

        case AV_VID_STREAM_TYPE_MSVIDEO1:
            *peCodecType = HI_UNF_VCODEC_TYPE_MSVIDEO1;
            break;

        case AV_VID_STREAM_TYPE_WMV1:
            *peCodecType = HI_UNF_VCODEC_TYPE_WMV1;
            break;

        case AV_VID_STREAM_TYPE_WMV2:
            *peCodecType = HI_UNF_VCODEC_TYPE_WMV2;
            break;

        case AV_VID_STREAM_TYPE_RV10:
            *peCodecType = HI_UNF_VCODEC_TYPE_RV10;
            break;

        case AV_VID_STREAM_TYPE_RV20:
            *peCodecType = HI_UNF_VCODEC_TYPE_RV20;
            break;

        case AV_VID_STREAM_TYPE_SVQ1:
            *peCodecType = HI_UNF_VCODEC_TYPE_SVQ1;
            break;

        case AV_VID_STREAM_TYPE_SVQ3:
            *peCodecType = HI_UNF_VCODEC_TYPE_SVQ3;
            break;

        case AV_VID_STREAM_TYPE_H261:
            *peCodecType = HI_UNF_VCODEC_TYPE_H261;
            break;

        case AV_VID_STREAM_TYPE_VP3:
            *peCodecType = HI_UNF_VCODEC_TYPE_VP3;
            break;

        case AV_VID_STREAM_TYPE_VP5:
            *peCodecType = HI_UNF_VCODEC_TYPE_VP5;
            break;

        case AV_VID_STREAM_TYPE_CINEPAK:
            *peCodecType = HI_UNF_VCODEC_TYPE_CINEPAK;
            break;

        case AV_VID_STREAM_TYPE_INDEO2:
            *peCodecType = HI_UNF_VCODEC_TYPE_INDEO2;
            break;

        case AV_VID_STREAM_TYPE_INDEO3:
            *peCodecType = HI_UNF_VCODEC_TYPE_INDEO3;
            break;

        case AV_VID_STREAM_TYPE_INDEO4:
            *peCodecType = HI_UNF_VCODEC_TYPE_INDEO4;
            break;

        case AV_VID_STREAM_TYPE_INDEO5:
            *peCodecType = HI_UNF_VCODEC_TYPE_INDEO5;
            break;

        case AV_VID_STREAM_TYPE_MJPEGB:
            *peCodecType = HI_UNF_VCODEC_TYPE_MJPEGB;
            break;

        case AV_VID_STREAM_TYPE_MVC:
            *peCodecType = HI_UNF_VCODEC_TYPE_MVC;
            break;

        case AV_VID_STREAM_TYPE_HEVC:
            *peCodecType = HI_UNF_VCODEC_TYPE_HEVC;
            break;

        case AV_VID_STREAM_TYPE_DV:
            *peCodecType = HI_UNF_VCODEC_TYPE_DV;
            break;

        case AV_VID_STREAM_TYPE_HUFFYUV:
            *peCodecType = HI_UNF_VCODEC_TYPE_BUTT;
            HAL_ERROR("AV_VID_STREAM_TYPE_HUFFYUV is not support\n");
            break;

        case AV_VID_STREAM_TYPE_AVS2:
            *peCodecType = HI_UNF_VCODEC_TYPE_AVS2;
            break;

        default:
            *peCodecType = HI_UNF_VCODEC_TYPE_BUTT;
            HAL_ERROR("eHalStreamType is not support\n");
            break;
    }

    return;
}

static VOID AV_HAL_AudCodecToSdk(AV_AUD_STREAM_TYPE_E eStreamType,
                                 HA_FORMAT_E* peSdkAudFormat)
{
    switch (eStreamType)
    {
        case AV_AUD_STREAM_TYPE_MP2:
            *peSdkAudFormat = FORMAT_MP2;
            break;

        case AV_AUD_STREAM_TYPE_MP3:
            *peSdkAudFormat = FORMAT_MP3;
            break;

        case AV_AUD_STREAM_TYPE_AAC:
            *peSdkAudFormat = FORMAT_AAC;
            break;

        case AV_AUD_STREAM_TYPE_AC3:
            *peSdkAudFormat = FORMAT_AC3;
            break;

        case AV_AUD_STREAM_TYPE_DTS:
            *peSdkAudFormat = FORMAT_DTS;
            break;

        case AV_AUD_STREAM_TYPE_DTS_EXPRESS:
            *peSdkAudFormat = FORMAT_DTS;
            break;

        case AV_AUD_STREAM_TYPE_VORBIS:
            *peSdkAudFormat = FORMAT_VORBIS;
            break;

        case AV_AUD_STREAM_TYPE_DVAUDIO:
            *peSdkAudFormat = FORMAT_DVAUDIO;
            break;

        case AV_AUD_STREAM_TYPE_WMAV1:
            *peSdkAudFormat = FORMAT_WMAV1;
            break;

        case AV_AUD_STREAM_TYPE_WMAV2:
            *peSdkAudFormat = FORMAT_WMAV2;
            break;

        case AV_AUD_STREAM_TYPE_MACE3:
            *peSdkAudFormat = FORMAT_MACE3;
            break;

        case AV_AUD_STREAM_TYPE_MACE6:
            *peSdkAudFormat = FORMAT_MACE6;
            break;

        case AV_AUD_STREAM_TYPE_VMDAUDIO:
            *peSdkAudFormat = FORMAT_VMDAUDIO;
            break;

        case AV_AUD_STREAM_TYPE_SONIC:
            *peSdkAudFormat = FORMAT_SONIC;
            break;

        case AV_AUD_STREAM_TYPE_SONIC_LS:
            *peSdkAudFormat = FORMAT_SONIC_LS;
            break;

        case AV_AUD_STREAM_TYPE_FLAC:
            *peSdkAudFormat = FORMAT_FLAC;
            break;

        case AV_AUD_STREAM_TYPE_MP3ADU:
            *peSdkAudFormat = FORMAT_MP3ADU;
            break;

        case AV_AUD_STREAM_TYPE_MP3ON4:
            *peSdkAudFormat = FORMAT_MP3ON4;
            break;

        case AV_AUD_STREAM_TYPE_SHORTEN:
            *peSdkAudFormat = FORMAT_SHORTEN;
            break;

        case AV_AUD_STREAM_TYPE_ALAC:
            *peSdkAudFormat = FORMAT_ALAC;
            break;

        case AV_AUD_STREAM_TYPE_WESTWOOD_SND1:
            *peSdkAudFormat = FORMAT_WESTWOOD_SND1;
            break;

        case AV_AUD_STREAM_TYPE_GSM:
            *peSdkAudFormat = FORMAT_GSM;
            break;

        case AV_AUD_STREAM_TYPE_QDM2:
            *peSdkAudFormat = FORMAT_QDM2;
            break;

        case AV_AUD_STREAM_TYPE_COOK:
            *peSdkAudFormat = FORMAT_COOK;
            break;

        case AV_AUD_STREAM_TYPE_TRUESPEECH:
            *peSdkAudFormat = FORMAT_TRUESPEECH;
            break;

        case AV_AUD_STREAM_TYPE_TTA:
            *peSdkAudFormat = FORMAT_TTA;
            break;

        case AV_AUD_STREAM_TYPE_SMACKAUDIO:
            *peSdkAudFormat = FORMAT_SMACKAUDIO;
            break;

        case AV_AUD_STREAM_TYPE_QCELP:
            *peSdkAudFormat = FORMAT_QCELP;
            break;

        case AV_AUD_STREAM_TYPE_WAVPACK:
            *peSdkAudFormat = FORMAT_WAVPACK;
            break;

        case AV_AUD_STREAM_TYPE_DSICINAUDIO:
            *peSdkAudFormat = FORMAT_DSICINAUDIO;
            break;

        case AV_AUD_STREAM_TYPE_IMC:
            *peSdkAudFormat = FORMAT_IMC;
            break;

        case AV_AUD_STREAM_TYPE_MUSEPACK7:
            *peSdkAudFormat = FORMAT_MUSEPACK7;
            break;

        case AV_AUD_STREAM_TYPE_MLP:
            *peSdkAudFormat = FORMAT_MLP;
            break;

        case AV_AUD_STREAM_TYPE_GSM_MS:
            *peSdkAudFormat = FORMAT_GSM_MS;
            break;

        case AV_AUD_STREAM_TYPE_ATRAC3:
            *peSdkAudFormat = FORMAT_ATRAC3;
            break;

        case AV_AUD_STREAM_TYPE_VOXWARE:
            *peSdkAudFormat = FORMAT_VOXWARE;
            break;

        case AV_AUD_STREAM_TYPE_APE:
            *peSdkAudFormat = FORMAT_APE;
            break;

        case AV_AUD_STREAM_TYPE_NELLYMOSER:
            *peSdkAudFormat = FORMAT_NELLYMOSER;
            break;

        case AV_AUD_STREAM_TYPE_MUSEPACK8:
            *peSdkAudFormat = FORMAT_MUSEPACK8;
            break;

        case AV_AUD_STREAM_TYPE_SPEEX:
            *peSdkAudFormat = FORMAT_SPEEX;
            break;

        case AV_AUD_STREAM_TYPE_WMAVOICE:
            *peSdkAudFormat = FORMAT_WMAVOICE;
            break;

        case AV_AUD_STREAM_TYPE_WMAPRO:
            *peSdkAudFormat = FORMAT_WMAPRO;
            break;

        case AV_AUD_STREAM_TYPE_WMALOSSLESS:
            *peSdkAudFormat = FORMAT_WMALOSSLESS;
            break;

        case AV_AUD_STREAM_TYPE_ATRAC3P:
            *peSdkAudFormat = FORMAT_ATRAC3P;
            break;

        case AV_AUD_STREAM_TYPE_EAC3:
            *peSdkAudFormat = FORMAT_EAC3;
            break;

        case AV_AUD_STREAM_TYPE_SIPR:
            *peSdkAudFormat = FORMAT_SIPR;
            break;

        case AV_AUD_STREAM_TYPE_MP1:
            *peSdkAudFormat = FORMAT_MP1;
            break;

        case AV_AUD_STREAM_TYPE_TWINVQ:
            *peSdkAudFormat = FORMAT_TWINVQ;
            break;

        case AV_AUD_STREAM_TYPE_TRUEHD:
            *peSdkAudFormat = FORMAT_TRUEHD;
            break;

        case AV_AUD_STREAM_TYPE_MP4ALS:
            *peSdkAudFormat = FORMAT_MP4ALS;
            break;

        case AV_AUD_STREAM_TYPE_ATRAC1:
            *peSdkAudFormat = FORMAT_ATRAC1;
            break;

        case AV_AUD_STREAM_TYPE_BINKAUDIO_RDFT:
            *peSdkAudFormat = FORMAT_BINKAUDIO_RDFT;
            break;

        case AV_AUD_STREAM_TYPE_BINKAUDIO_DCT:
            *peSdkAudFormat = FORMAT_BINKAUDIO_DCT;
            break;

        case AV_AUD_STREAM_TYPE_DRA:
            *peSdkAudFormat = FORMAT_DRA;
            break;

        case AV_AUD_STREAM_TYPE_PCM:
            *peSdkAudFormat = FORMAT_PCM;
            break;

        case AV_AUD_STREAM_TYPE_PCM_BLURAY:
            *peSdkAudFormat = FORMAT_PCM_BLURAY;
            break;

        case AV_AUD_STREAM_TYPE_ADPCM:
            *peSdkAudFormat = FORMAT_ADPCM;
            break;

        case AV_AUD_STREAM_TYPE_AMR_NB:
            *peSdkAudFormat = FORMAT_AMR_NB;
            break;

        case AV_AUD_STREAM_TYPE_AMR_WB:
            *peSdkAudFormat = FORMAT_AMR_WB;
            break;

        case AV_AUD_STREAM_TYPE_AMR_AWB:
            *peSdkAudFormat = FORMAT_AMR_AWB;
            break;

        case AV_AUD_STREAM_TYPE_RA_144:
            *peSdkAudFormat = FORMAT_RA_144;
            break;

        case AV_AUD_STREAM_TYPE_RA_288:
            *peSdkAudFormat = FORMAT_RA_288;
            break;

        case AV_AUD_STREAM_TYPE_DPCM:
            *peSdkAudFormat = FORMAT_DPCM;
            break;

        case AV_AUD_STREAM_TYPE_G711:
            *peSdkAudFormat = FORMAT_G711;
            break;

        case AV_AUD_STREAM_TYPE_G722:
            *peSdkAudFormat = FORMAT_G722;
            break;

        case AV_AUD_STREAM_TYPE_G7231:
            *peSdkAudFormat = FORMAT_G7231;
            break;

        case AV_AUD_STREAM_TYPE_G726:
            *peSdkAudFormat = FORMAT_G726;
            break;

        case AV_AUD_STREAM_TYPE_G728:
            *peSdkAudFormat = FORMAT_G728;
            break;

        case AV_AUD_STREAM_TYPE_G729AB:
            *peSdkAudFormat = FORMAT_G729AB;
            break;

        case AV_AUD_STREAM_TYPE_MULTI:
            *peSdkAudFormat = FORMAT_MULTI;
            break;

        default:
            break;
    }

    return;
}

static VOID AV_SDK_SyncModeToHal(HI_UNF_SYNC_REF_E eSdkSyncMod,
                                 AV_SYNC_MODE_E* pHalSyncMode)
{
    switch (eSdkSyncMod)
    {
        case HI_UNF_SYNC_REF_NONE:
            *pHalSyncMode = AV_SYNC_MODE_DISABLE;
            break;

        case HI_UNF_SYNC_REF_AUDIO:
            *pHalSyncMode = AV_SYNC_MODE_AUD;
            break;

        case HI_UNF_SYNC_REF_VIDEO:
            *pHalSyncMode = AV_SYNC_MODE_VID;
            break;

        case HI_UNF_SYNC_REF_PCR:
            *pHalSyncMode = AV_SYNC_MODE_PCR;
            break;

        case HI_UNF_SYNC_REF_SCR:
            *pHalSyncMode = AV_SYNC_MODE_SCR;
            break;

        default:
            *pHalSyncMode = AV_SYNC_MODE_AUD;
            break;
    }

    return;
}

static VOID AV_HAL_SyncModeToSdk(AV_SYNC_MODE_E eHalSyncMod,
                                 HI_UNF_SYNC_REF_E* pSdkSyncMode)
{
    switch (eHalSyncMod)
    {
        case AV_SYNC_MODE_DISABLE:
            *pSdkSyncMode = HI_UNF_SYNC_REF_NONE;
            break;

        case AV_SYNC_MODE_AUTO:
            *pSdkSyncMode = HI_UNF_SYNC_REF_AUDIO;
            break;

        case AV_SYNC_MODE_PCR:
            *pSdkSyncMode = HI_UNF_SYNC_REF_PCR;
            break;

        case AV_SYNC_MODE_VID:
            *pSdkSyncMode = HI_UNF_SYNC_REF_VIDEO;
            break;

        case AV_SYNC_MODE_AUD:
            *pSdkSyncMode = HI_UNF_SYNC_REF_AUDIO;
            break;

        case AV_SYNC_MODE_SCR:
            *pSdkSyncMode = HI_UNF_SYNC_REF_SCR;
            break;

        default:
            *pSdkSyncMode = HI_UNF_SYNC_REF_AUDIO;
            break;
    }

    return;
}

static VOID AV_SDK_VidFrameInfoToHal(HI_UNF_VIDEO_FRAME_INFO_S* pstSdkFrameInfo,
                                     AV_VID_FRAMEINFO_S* pstHalFrameInfo)
{
    pstHalFrameInfo->u32FrameIndex                        = pstSdkFrameInfo->u32FrameIndex;
    pstHalFrameInfo->stVideoFrameAddr[0].u32YAddr         = pstSdkFrameInfo->stVideoFrameAddr[0].u32YAddr;
    pstHalFrameInfo->stVideoFrameAddr[0].u32CAddr         = pstSdkFrameInfo->stVideoFrameAddr[0].u32CAddr;
    pstHalFrameInfo->stVideoFrameAddr[0].u32CrAddr        = pstSdkFrameInfo->stVideoFrameAddr[0].u32CrAddr;
    pstHalFrameInfo->stVideoFrameAddr[0].u32YStride       = pstSdkFrameInfo->stVideoFrameAddr[0].u32YStride;
    pstHalFrameInfo->stVideoFrameAddr[0].u32CStride       = pstSdkFrameInfo->stVideoFrameAddr[0].u32CStride;
    pstHalFrameInfo->stVideoFrameAddr[0].u32CrStride      = pstSdkFrameInfo->stVideoFrameAddr[0].u32CrStride;

    pstHalFrameInfo->stVideoFrameAddr[1].u32YAddr         = pstSdkFrameInfo->stVideoFrameAddr[1].u32YAddr;
    pstHalFrameInfo->stVideoFrameAddr[1].u32CAddr         = pstSdkFrameInfo->stVideoFrameAddr[1].u32CAddr;
    pstHalFrameInfo->stVideoFrameAddr[1].u32CrAddr        = pstSdkFrameInfo->stVideoFrameAddr[1].u32CrAddr;
    pstHalFrameInfo->stVideoFrameAddr[1].u32YStride       = pstSdkFrameInfo->stVideoFrameAddr[1].u32YStride;
    pstHalFrameInfo->stVideoFrameAddr[1].u32CStride       = pstSdkFrameInfo->stVideoFrameAddr[1].u32CStride;
    pstHalFrameInfo->stVideoFrameAddr[1].u32CrStride      = pstSdkFrameInfo->stVideoFrameAddr[1].u32CrStride;

    pstHalFrameInfo->u32Width                   = pstSdkFrameInfo->u32Width;
    pstHalFrameInfo->u32Height                  = pstSdkFrameInfo->u32Height;
    pstHalFrameInfo->s64SrcPts                  = (S64)pstSdkFrameInfo->u32SrcPts;
    pstHalFrameInfo->s64Pts                     = (S64)pstSdkFrameInfo->u32Pts;
    /*pstHalFrameInfo->enVideoFormat        = pstSdkFrameInfo->enVideoFormat;*/
    pstHalFrameInfo->u32AspectWidth             = pstSdkFrameInfo->u32AspectWidth;
    pstHalFrameInfo->u32AspectHeight            = pstSdkFrameInfo->u32AspectHeight;
    pstHalFrameInfo->u32fpsInteger              = pstSdkFrameInfo->stFrameRate.u32fpsInteger;
    pstHalFrameInfo->u32fpsDecimal              = pstSdkFrameInfo->stFrameRate.u32fpsDecimal;
    pstHalFrameInfo->bProgressive               = pstSdkFrameInfo->bProgressive;
    /*pstHalFrameInfo->enFieldMode          = pstSdkFrameInfo->enFieldMode*/
    pstHalFrameInfo->bTopFieldFirst             = pstSdkFrameInfo->bTopFieldFirst;
    /*pstHalFrameInfo->enFramePackingType   = pstSdkFrameInfo->enFramePackingType*/
    pstHalFrameInfo->u32Circumrotate            = pstSdkFrameInfo->u32Circumrotate;
    pstHalFrameInfo->bVerticalMirror            = pstSdkFrameInfo->bVerticalMirror;
    pstHalFrameInfo->bHorizontalMirror          = pstSdkFrameInfo->bHorizontalMirror;
    pstHalFrameInfo->u32DisplayWidth            = pstSdkFrameInfo->u32DisplayWidth;
    pstHalFrameInfo->u32DisplayHeight           = pstSdkFrameInfo->u32DisplayHeight;
    pstHalFrameInfo->u32DisplayCenterX          = pstSdkFrameInfo->u32DisplayCenterX;
    pstHalFrameInfo->u32DisplayCenterY          = pstSdkFrameInfo->u32DisplayCenterY;
    pstHalFrameInfo->u32ErrorLevel              = pstSdkFrameInfo->u32ErrorLevel;

    HAL_MEMCPY(pstHalFrameInfo->u32Private, pstSdkFrameInfo->u32Private, sizeof(U32) * 64);

    return;
}

static VOID AV_HAL_VidFrameInfoToSdk(AV_VID_FRAMEINFO_S* pstHalFrameInfo,
                                     HI_UNF_VIDEO_FRAME_INFO_S* pstSdkFrameInfo)
{
    pstSdkFrameInfo->u32FrameIndex                        = pstHalFrameInfo->u32FrameIndex;
    pstSdkFrameInfo->stVideoFrameAddr[0].u32YAddr         = pstHalFrameInfo->stVideoFrameAddr[0].u32YAddr;
    pstSdkFrameInfo->stVideoFrameAddr[0].u32CAddr         = pstHalFrameInfo->stVideoFrameAddr[0].u32CAddr;
    pstSdkFrameInfo->stVideoFrameAddr[0].u32CrAddr        = pstHalFrameInfo->stVideoFrameAddr[0].u32CrAddr;
    pstSdkFrameInfo->stVideoFrameAddr[0].u32YStride       = pstHalFrameInfo->stVideoFrameAddr[0].u32YStride;
    pstSdkFrameInfo->stVideoFrameAddr[0].u32CStride       = pstHalFrameInfo->stVideoFrameAddr[0].u32CStride;
    pstSdkFrameInfo->stVideoFrameAddr[0].u32CrStride      = pstHalFrameInfo->stVideoFrameAddr[0].u32CrStride;

    pstSdkFrameInfo->stVideoFrameAddr[1].u32YAddr         = pstHalFrameInfo->stVideoFrameAddr[1].u32YAddr;
    pstSdkFrameInfo->stVideoFrameAddr[1].u32CAddr         = pstHalFrameInfo->stVideoFrameAddr[1].u32CAddr;
    pstSdkFrameInfo->stVideoFrameAddr[1].u32CrAddr        = pstHalFrameInfo->stVideoFrameAddr[1].u32CrAddr;
    pstSdkFrameInfo->stVideoFrameAddr[1].u32YStride       = pstHalFrameInfo->stVideoFrameAddr[1].u32YStride;
    pstSdkFrameInfo->stVideoFrameAddr[1].u32CStride       = pstHalFrameInfo->stVideoFrameAddr[1].u32CStride;
    pstSdkFrameInfo->stVideoFrameAddr[1].u32CrStride      = pstHalFrameInfo->stVideoFrameAddr[1].u32CrStride;

    pstSdkFrameInfo->u32Width                   = pstHalFrameInfo->u32Width;
    pstSdkFrameInfo->u32Height                  = pstHalFrameInfo->u32Height;
    pstSdkFrameInfo->u32SrcPts                  = (U32)pstHalFrameInfo->s64SrcPts;
    pstSdkFrameInfo->u32Pts                     = (U32)pstHalFrameInfo->s64Pts;
    /*pstSdkFrameInfo->enVideoFormat    = pstHalFrameInfo->enVideoFormat; */
    pstSdkFrameInfo->u32AspectWidth             = pstHalFrameInfo->u32AspectWidth;
    pstSdkFrameInfo->u32AspectHeight            = pstHalFrameInfo->u32AspectHeight;
    pstSdkFrameInfo->stFrameRate.u32fpsInteger  = pstHalFrameInfo->u32fpsInteger;
    pstSdkFrameInfo->stFrameRate.u32fpsDecimal  = pstHalFrameInfo->u32fpsDecimal;
    pstSdkFrameInfo->bProgressive               = (FALSE == pstHalFrameInfo->bProgressive) ? HI_FALSE : HI_TRUE;
    /*pstSdkFrameInfo->enFieldMode          = pstHalFrameInfo->enFieldMode;*/
    pstSdkFrameInfo->bTopFieldFirst             = (FALSE == pstHalFrameInfo->bTopFieldFirst) ? HI_FALSE : HI_TRUE;
    /*pstSdkFrameInfo->enFramePackingType   = pstHalFrameInfo->enFramePackingType*/
    pstSdkFrameInfo->u32Circumrotate            = pstHalFrameInfo->u32Circumrotate;
    pstSdkFrameInfo->bVerticalMirror            = (FALSE == pstHalFrameInfo->bVerticalMirror) ? HI_FALSE : HI_TRUE;
    pstSdkFrameInfo->bHorizontalMirror          = (FALSE == pstHalFrameInfo->bHorizontalMirror) ? HI_FALSE : HI_TRUE;
    pstSdkFrameInfo->u32DisplayWidth            = pstHalFrameInfo->u32DisplayWidth;
    pstSdkFrameInfo->u32DisplayHeight           = pstHalFrameInfo->u32DisplayHeight;
    pstSdkFrameInfo->u32DisplayCenterX          = pstHalFrameInfo->u32DisplayCenterX;
    pstSdkFrameInfo->u32DisplayCenterY          = pstHalFrameInfo->u32DisplayCenterY;
    pstSdkFrameInfo->u32ErrorLevel              = pstHalFrameInfo->u32ErrorLevel;

    HAL_MEMCPY(pstSdkFrameInfo->u32Private, pstHalFrameInfo->u32Private, sizeof(U32) * 64);

    return;
}

static VOID AV_SDK_AudFrameInfoToHal(HI_UNF_AO_FRAMEINFO_S* pstSdkFrameInfo,
                                     AV_AUD_FRAMEINFO_S* pstHalFrameInfo)
{
    pstHalFrameInfo->s32BitPerSample       = pstSdkFrameInfo->s32BitPerSample;
    pstHalFrameInfo->bInterleaved          = (HI_TRUE == pstSdkFrameInfo->bInterleaved) ? TRUE : FALSE;
    pstHalFrameInfo->u32SampleRate         = pstSdkFrameInfo->u32SampleRate;
    pstHalFrameInfo->u32Channels           = pstSdkFrameInfo->u32Channels;
    pstHalFrameInfo->s64PtsMs              = (S64)pstSdkFrameInfo->u32PtsMs;
    pstHalFrameInfo->ps32PcmBuffer         = pstSdkFrameInfo->ps32PcmBuffer;
    pstHalFrameInfo->ps32BitsBuffer        = pstSdkFrameInfo->ps32BitsBuffer;
    pstHalFrameInfo->u32PcmSamplesPerFrame = pstSdkFrameInfo->u32PcmSamplesPerFrame;
    pstHalFrameInfo->u32BitsBytesPerFrame  = pstSdkFrameInfo->u32BitsBytesPerFrame;
    pstHalFrameInfo->u32FrameIndex         = pstSdkFrameInfo->u32FrameIndex;
    pstHalFrameInfo->u32IEC61937DataType   = pstSdkFrameInfo->u32IEC61937DataType;

    return;
}

static VOID AV_HAL_AudFrameInfoToSdk(AV_AUD_FRAMEINFO_S* pstHalFrameInfo,
                                     HI_UNF_AO_FRAMEINFO_S* pstSdkFrameInfo)
{
    pstSdkFrameInfo->s32BitPerSample       = pstHalFrameInfo->s32BitPerSample;
    pstSdkFrameInfo->bInterleaved          = (TRUE == pstHalFrameInfo->bInterleaved) ? HI_TRUE : HI_FALSE;
    pstSdkFrameInfo->u32SampleRate         = pstHalFrameInfo->u32SampleRate;
    pstSdkFrameInfo->u32Channels           = pstHalFrameInfo->u32Channels;
    pstSdkFrameInfo->u32PtsMs              = (S32)pstHalFrameInfo->s64PtsMs;
    pstSdkFrameInfo->ps32PcmBuffer         = pstHalFrameInfo->ps32PcmBuffer;
    pstSdkFrameInfo->ps32BitsBuffer        = pstHalFrameInfo->ps32BitsBuffer;
    pstSdkFrameInfo->u32PcmSamplesPerFrame = pstHalFrameInfo->u32PcmSamplesPerFrame;
    pstSdkFrameInfo->u32BitsBytesPerFrame  = pstHalFrameInfo->u32BitsBytesPerFrame;
    pstSdkFrameInfo->u32FrameIndex         = pstHalFrameInfo->u32FrameIndex;
    pstSdkFrameInfo->u32IEC61937DataType   = pstHalFrameInfo->u32IEC61937DataType;

    return;
}

#ifdef HAL_HISI_EXTEND_H
static VOID AV_HAL_HdrTypeToSdk(AV_HDR_STREAM_TYPE_E eAvHdrType,
                                HI_UNF_AVPLAY_HDR_STREAM_TYPE_E* peSdkHdrType)
{
    switch (eAvHdrType)
    {
        case AV_HDR_STREAM_TYPE_DL_SINGLE_VES:
            *peSdkHdrType = HI_UNF_AVPLAY_HDR_STREAM_TYPE_DL_SINGLE_VES;
            break;

        case AV_HDR_STREAM_TYPE_DL_DUAL_VES:
            *peSdkHdrType = HI_UNF_AVPLAY_HDR_STREAM_TYPE_DL_DUAL_VES;
            break;

        case AV_HDR_STREAM_TYPE_SL_VES:
            *peSdkHdrType = HI_UNF_AVPLAY_HDR_STREAM_TYPE_SL_VES;
            break;

        default:
            *peSdkHdrType = HI_UNF_AVPLAY_HDR_STREAM_TYPE_BUTT;
            break;
    }

    return;
}

static VOID AV_HAL_InvokeCmdToSdk(AV_INVOKE_E enCmd, HI_UNF_AVPLAY_INVOKE_E* penInvokeType)
{
    switch (enCmd)
    {
      case AV_INVOKE_ACODEC:
          *penInvokeType = HI_UNF_AVPLAY_INVOKE_ACODEC;
          break;

      case AV_INVOKE_VCODEC:
          *penInvokeType = HI_UNF_AVPLAY_INVOKE_VCODEC;
          break;

      case AV_INVOKE_SET_VID_LASTFRMFLAG:
          *penInvokeType = HI_UNF_AVPLAY_INVOKE_VCODEC;
          break;
      default:
          break;
    }
    return;
}

static S32 AV_HAL_VcodecCmdToSdk(AV_CODEC_SET_CMD_E enCodecSetCmd, HI_CODEC_VIDEO_CMD_S* pstVcodecCmd)
{
    if (AV_CODEC_SET_CMD_DPBFULL == enCodecSetCmd)
    {
        pstVcodecCmd->u32CmdID = HI_UNF_AVPLAY_SET_DPBFULL_CTRL_CMD;
    }
    else if (AV_CODEC_SET_CMD_PROGRESSIVE == enCodecSetCmd)
    {
        pstVcodecCmd->u32CmdID = HI_UNF_AVPLAY_SET_PROGRESSIVE_CMD;
    }
    else
    {
       HAL_ERROR("the command is invalid");
       return FAILURE;
    }

    return SUCCESS;
}
#endif

static S32 AV_SDK_Init(VOID)
{
    S32 s32Ret = SUCCESS;

    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.MP3.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DOLBYPLUS.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DTSHD.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DTSM6.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.MP2.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AAC.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DRA.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DOLBYTRUEHD.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.TRUEHDPASSTHROUGH.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AMRNB.codec.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AMRWB.codec.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.WMA.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.COOK.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.BLURAYLPCM.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.FFMPEG_ADEC.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.PCM.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AC3PASSTHROUGH.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DTSPASSTHROUGH.decode.so"), s32Ret);
    AV_DO_FUNC(HI_UNF_AVPLAY_RegisterVcodecLib("libHV.VIDEO.FFMPEG_VDEC.decode.so"), s32Ret);

    /* init avplay */
    s32Ret = HI_UNF_AVPLAY_Init();
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "AVPlay init error, s32Ret(0x%08x)", s32Ret);

    return SUCCESS;
}

static S32 AV_SDK_Deinit(VOID)
{
    S32 s32Ret = SUCCESS;

    /* deinit avplay */
    s32Ret = HI_UNF_AVPLAY_DeInit();
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "AVPlay Deinit error, s32Ret(0x%08x)", s32Ret);

    return SUCCESS;
}

static S32 AV_SDK_SetEvent(HANDLE hAvPlayerSdk, AV_EVT_E enEvtID, BOOL bRegister)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_AVPLAY_EVENT_E enEvtType = HI_UNF_AVPLAY_EVENT_BUTT;
    HI_UNF_AVPLAY_EVENT_E enEvtType1 = HI_UNF_AVPLAY_EVENT_BUTT;

    AV_HAL_EvtToSdk(enEvtID, &enEvtType1, &enEvtType);

    if (HI_UNF_AVPLAY_EVENT_BUTT == enEvtType)
    {
        HAL_ERROR("do not support the event type(%d)", enEvtID);
        return ERROR_INVALID_PARAM;
    }

    if (bRegister)
    {
        HAL_DEBUG("Register event(%d)", enEvtID);

        s32Ret = HI_UNF_AVPLAY_RegisterEvent64(hAvPlayerSdk, enEvtType, AV_SDK_EvtCallback);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "sdk avplayer event(%d) register failed.", enEvtType);

        if (HI_UNF_AVPLAY_EVENT_BUTT != enEvtType1)
        {
            s32Ret = HI_UNF_AVPLAY_RegisterEvent64(hAvPlayerSdk, enEvtType1, AV_SDK_EvtCallback);
            HAL_CHK_PRINTF((SUCCESS != s32Ret), "sdk avplayer event(%d) register failed.", enEvtType1);
        }
    }
    else
    {
        HAL_DEBUG("Unregister event(%d)", enEvtID);

        s32Ret = HI_UNF_AVPLAY_UnRegisterEvent(hAvPlayerSdk, enEvtType);
        HAL_CHK_PRINTF((s32Ret != SUCCESS), "sdk avplayer event(%d) unregister error(0x%08x)", enEvtType, s32Ret);

        if (HI_UNF_AVPLAY_EVENT_BUTT != enEvtType1)
        {
            s32Ret = HI_UNF_AVPLAY_UnRegisterEvent(hAvPlayerSdk, enEvtType1);
            HAL_CHK_PRINTF((s32Ret != SUCCESS), "sdk avplayer event1(%d) unregister error(0x%08x)", enEvtType1, s32Ret);
        }
    }

    return (SUCCESS == s32Ret) ? SUCCESS : FAILURE;
}

static S32 AV_SDK_Create(const AV_CREATE_PARAMS_S* const pstCreateParams,
                         U32 u32Index,
                         AV_HAL_INFO_S** ppstAvInfo)
{
    S32 s32Ret = SUCCESS;
    U32 i = 0;
    AV_HAL_INFO_S* pstAvInfo = NULL;

    HANDLE hAvPlayerSdk = AV_INVALID_HANDLE;
    HI_UNF_AVPLAY_ATTR_S stAvAttr;
    HI_UNF_SYNC_ATTR_S   stSyncAttr;

    pstAvInfo = (AV_HAL_INFO_S*)AV_MALLOCZ(sizeof(AV_HAL_INFO_S));
    HAL_CHK_RETURN((NULL == pstAvInfo), ERROR_NO_MEMORY, "av error, malloc av handle failed.");

    /* config av default parameter. */
    pstAvInfo->u32AvIdx               = u32Index;
    pstAvInfo->hAvPlayerSdk           = AV_INVALID_HANDLE;
    pstAvInfo->hAudInjecter           = AV_INVALID_HANDLE;
    pstAvInfo->hVidInjecter           = AV_INVALID_HANDLE;
    pstAvInfo->hWindowSdk             = AV_INVALID_HANDLE;
    pstAvInfo->hTrackSdk              = AV_INVALID_HANDLE;
    pstAvInfo->hSM                    = AV_INVALID_HANDLE;
    pstAvInfo->enStreamType           = HI_UNF_AVPLAY_STREAM_TYPE_TS;
    pstAvInfo->enDemuxId              = DMX_ID_0;
    pstAvInfo->bAudStart              = FALSE;
    pstAvInfo->bVidStart              = FALSE;

    for (i = 0; i < AV_MAX_EVENT_NUM; i++)
    {
        pstAvInfo->stAvCbParam[i].enEvt       = AV_EVT_BUTT;
        pstAvInfo->stAvCbParam[i].pfnCallback = NULL;
    }

    HAL_MEMSET_NO_VERIFY(&stAvAttr, 0, sizeof(stAvAttr));

    /* use user config parameter */

    switch (pstCreateParams->enStreamType)
    {
        case AV_STREAM_TYPE_TS:
            pstAvInfo->enStreamType = HI_UNF_AVPLAY_STREAM_TYPE_TS;
            break;

        case AV_STREAM_TYPE_ES:
            pstAvInfo->enStreamType = HI_UNF_AVPLAY_STREAM_TYPE_ES;
            break;

        default:
            pstAvInfo->enStreamType = HI_UNF_AVPLAY_STREAM_TYPE_ES;
            break;
    }

    /* ts mode */
    pstAvInfo->enDemuxId = pstCreateParams->stSourceParams.enDemuxId;

    s32Ret = HI_UNF_AVPLAY_GetDefaultConfig(&stAvAttr, pstAvInfo->enStreamType);
    HAL_CHK_CALL_RETURN((SUCCESS != s32Ret), ERROR_AV_OP_FAILED, AV_FREEP(&pstAvInfo), "av error, s32Ret(0x%08x)", s32Ret);

    stAvAttr.u32DemuxId = pstCreateParams->stSourceParams.enDemuxId;
    HAL_DEBUG("enDemuxId:%d, enStreamType:%d, u32VidBufSize:%#x, u32AudBufSize:%#x",
              stAvAttr.u32DemuxId, stAvAttr.stStreamAttr.enStreamType,
              stAvAttr.stStreamAttr.u32VidBufSize,
              stAvAttr.stStreamAttr.u32AudBufSize);

    /* create av */
    s32Ret = HI_UNF_AVPLAY_Create(&stAvAttr, &hAvPlayerSdk);
    HAL_CHK_CALL_RETURN((SUCCESS != s32Ret), ERROR_AV_OP_FAILED, AV_FREEP(&pstAvInfo), "av error, s32Ret(0x%08x)", s32Ret);

    /* set default param, need add more setting...*/
    pstAvInfo->stAvSettings.stSourceParams.enDemuxId = pstCreateParams->stSourceParams.enDemuxId;
    pstAvInfo->stAvSettings.enAudStreamType = AV_AUD_STREAM_TYPE_BUTT;
    pstAvInfo->stAvSettings.enVidStreamType = AV_VID_STREAM_TYPE_BUTT;

    HAL_MEMSET_NO_VERIFY(&stSyncAttr, 0, sizeof(stSyncAttr));
    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSyncAttr);

    if (SUCCESS == s32Ret)
    {
        AV_SDK_SyncModeToHal(stSyncAttr.enSyncRef, &pstAvInfo->stAvSettings.enAvSyncMode);
        pstAvInfo->stAvSettings.stSyncParams.stSyncStartRegion.bSmoothPlay        = stSyncAttr.stSyncStartRegion.bSmoothPlay;
        pstAvInfo->stAvSettings.stSyncParams.stSyncStartRegion.s32VidNegativeTime = stSyncAttr.stSyncStartRegion.s32VidNegativeTime;
        pstAvInfo->stAvSettings.stSyncParams.stSyncStartRegion.s32VidPlusTime     = stSyncAttr.stSyncStartRegion.s32VidPlusTime;

        pstAvInfo->stAvSettings.stSyncParams.stSyncNovelRegion.bSmoothPlay        = stSyncAttr.stSyncNovelRegion.bSmoothPlay;
        pstAvInfo->stAvSettings.stSyncParams.stSyncNovelRegion.s32VidNegativeTime = stSyncAttr.stSyncNovelRegion.s32VidNegativeTime;
        pstAvInfo->stAvSettings.stSyncParams.stSyncNovelRegion.s32VidPlusTime     = stSyncAttr.stSyncNovelRegion.s32VidPlusTime;
        pstAvInfo->stAvSettings.stSyncParams.u32PreSyncTimeoutMs                  = stSyncAttr.u32PreSyncTimeoutMs;
        pstAvInfo->stAvSettings.stSyncParams.bPreSyncSmoothPlay                   = (0 == stSyncAttr.u32PreSyncTimeoutMs) ? FALSE : TRUE;
        pstAvInfo->stAvSettings.stSyncParams.bQuickOutput                         = stSyncAttr.bQuickOutput;
        pstAvInfo->stAvSettings.enVideoRotation                                   = AV_VID_ROTATION_0;
        pstAvInfo->stAvSettings.u16AudPid                                         = AV_INVALID_PID;
        pstAvInfo->stAvSettings.u16VidPid                                         = AV_INVALID_PID;
        pstAvInfo->stAvSettings.u16PcrPid                                         = AV_INVALID_PID;
        pstAvInfo->stAvSettings.s32Speed                                          = AV_NORMAL_PLAY_SPEED;
        pstAvInfo->stAvSettings.en3dFormat                                        = AV_3D_FORMAT_BUTT;
        pstAvInfo->stAvSettings.enVidStopMode                                     = AV_VID_STOP_MODE_BLACK;
        pstAvInfo->stAvSettings.enErrRecoveryMode                                 = AV_ERROR_RECOVERY_MODE_NONE;

#ifdef HAL_HISI_EXTEND_H
        pstAvInfo->stAvSettings.bEnableTVP                                        = FALSE;
        pstAvInfo->stAvSettings.bEnableAudSecurity                                = FALSE;
        pstAvInfo->stAvSettings.stLowDelayCfg.bEnable                             = FALSE;
#endif

    }

    pstAvInfo->hAvPlayerSdk = hAvPlayerSdk;

    *ppstAvInfo = pstAvInfo;

    HAL_DEBUG("av_open success, sdk handle:0x%x", hAvPlayerSdk);

    return SUCCESS;
}

static S32 AV_SDK_Close(AV_HAL_INFO_S* pstAvInfo)
{
    S32 s32Ret = SUCCESS;
    U32 u32Idx = 0;

    HAL_CHK_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, "av error, invalid handle:0x%p", pstAvInfo);

    /* Step1. call av_stop funtion to stop audio and video
          Step2. call Aout and Vout detach function to detach audio and video output
          Step3. then call AV_SDK_Close function to close audio and video channel
      */
    if (AV_INVALID_HANDLE != pstAvInfo->hAudInjecter)
    {
        /* detach audio track */
        (VOID)av_injecter_detach(NULL, pstAvInfo->hAudInjecter);
        pstAvInfo->hAudInjecter = AV_INVALID_HANDLE;
    }

    if (AV_INVALID_HANDLE != pstAvInfo->hVidInjecter)
    {
        /* disable window and detach window */
        (VOID)av_injecter_detach(NULL, pstAvInfo->hVidInjecter);
        pstAvInfo->hVidInjecter = AV_INVALID_HANDLE;
    }

    /* unregister avplay event */
    for (u32Idx = 0; u32Idx < AV_MAX_EVENT_NUM; u32Idx++)
    {
        if (AV_EVT_BUTT != pstAvInfo->stAvCbParam[u32Idx].enEvt)
        {
            (VOID)AV_SDK_SetEvent(pstAvInfo->hAvPlayerSdk, pstAvInfo->stAvCbParam[u32Idx].enEvt, FALSE);
        }
    }

    /* destory sdk av handle */
    s32Ret = HI_UNF_AVPLAY_Destroy(pstAvInfo->hAvPlayerSdk);

    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "avplay destroy return s32Ret(0x%08x)", s32Ret);

    AV_FREEP(&pstAvInfo);

    return SUCCESS;
}

static S32 AV_SDK_GetStatus(HANDLE hAvPlayerSdk, const AV_HAL_INFO_S* pstAvInfo, AV_STATUS_S* pstStatus)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_AVPLAY_STATUS_INFO_S         stStatusInfo;
    HI_UNF_AVPLAY_STREAM_INFO_S         stStreaminfo;
    HI_UNF_AVPLAY_VIDEO_FRAME_INFO_S    stVideoFrameInfo;

#ifdef HAL_HISI_EXTEND_H
    HI_UNF_AVPLAY_VDEC_INFO_S           stVdecInfo;
#endif

    HAL_MEMSET_NO_VERIFY(&stStatusInfo, 0, sizeof(HI_UNF_AVPLAY_STATUS_INFO_S));
    HAL_MEMSET_NO_VERIFY(&stStreaminfo, 0, sizeof(HI_UNF_AVPLAY_STREAM_INFO_S));
    HAL_MEMSET_NO_VERIFY(&stVideoFrameInfo, 0, sizeof(HI_UNF_AVPLAY_VIDEO_FRAME_INFO_S));

    s32Ret = HI_UNF_AVPLAY_GetStatusInfo(hAvPlayerSdk, &stStatusInfo);
    s32Ret |= HI_UNF_AVPLAY_GetStreamInfo(hAvPlayerSdk, &stStreaminfo);

    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "call sdk avplay get info fail");

    // TODO: sdk currently not support this function.
    //s32Ret = HI_UNF_AVPLAY_GetVideoFrameInfo(hAvPlayerSdk, &stVideoFrameInfo);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE,
                   "get video frame info fail, s32Ret(0x%08x)", s32Ret);

    HAL_MEMSET_NO_VERIFY(&pstStatus->stAudStatus, 0, sizeof(AV_AUD_STATUS_S));
    HAL_MEMSET_NO_VERIFY(&pstStatus->stVidStatus, 0, sizeof(AV_VID_STATUS_S));

    pstStatus->stAudStatus.enDecodeState = AV_DECODER_STATE_BUTT;
    pstStatus->stVidStatus.enDecodeState = AV_DECODER_STATE_BUTT;

    pstStatus->ahInjecter[AV_CONTENT_VIDEO] = pstAvInfo->hVidInjecter;
    pstStatus->ahInjecter[AV_CONTENT_AUDIO] = pstAvInfo->hAudInjecter;
    pstStatus->s64LocalTime                 = AV_SDK_PTS_TO_HAL(stStatusInfo.stSyncStatus.u32LocalTime);

    /* only config audio codec, we set the audio status information */
    if (AV_AUD_STREAM_TYPE_BUTT != pstAvInfo->stAvSettings.enAudStreamType)
    {
        pstStatus->stAudStatus.u32PacketCount       = stStatusInfo.u32AuddFrameCount;
        pstStatus->stAudStatus.u32FrameCount        = stStatusInfo.u32AuddFrameCount;
        pstStatus->stAudStatus.enStreamType         = pstAvInfo->stAvSettings.enAudStreamType;

        AV_SDK_StatusToHal(stStatusInfo.enRunStatus, &pstStatus->stAudStatus.enDecodeState);

        pstStatus->stAudStatus.u32Bps               = stStreaminfo.stAudStreamInfo.u32BitRate;
        pstStatus->stAudStatus.u32SampleRate        = stStreaminfo.stAudStreamInfo.enSampleRate;
        pstStatus->stAudStatus.u32BitWidth          = (U32)stStreaminfo.stAudStreamInfo.enBitDepth;
        pstStatus->stAudStatus.enSourceType
            = (HI_UNF_AVPLAY_STREAM_TYPE_TS == pstAvInfo->enStreamType) ? AV_SOURCE_TUNER : AV_SOURCE_MEM;
        pstStatus->stAudStatus.u32EsBufferFreeSize
            = stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_AUD].u32BufSize - stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_AUD].u32UsedSize;
        pstStatus->stAudStatus.u32PesBufferSize     = 0;
        pstStatus->stAudStatus.u32PesBufferFreeSize = 0;
        pstStatus->stAudStatus.u32EsBufferSize      = stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_AUD].u32BufSize;
        pstStatus->stAudStatus.u32Stc               = 0;
        pstStatus->stAudStatus.s64Pts               = AV_SDK_PTS_TO_HAL(stStatusInfo.stSyncStatus.u32LastAudPts);
        pstStatus->stAudStatus.s64FirstPts          = AV_SDK_PTS_TO_HAL(stStatusInfo.stSyncStatus.u32FirstAudPts);
        pstStatus->stAudStatus.u16Pid               = pstAvInfo->stAvSettings.u16AudPid;
        pstStatus->stAudStatus.u32FrameBufTime      = stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_AUD].u32FrameBufTime;
    }

    if (AV_VID_STREAM_TYPE_BUTT != pstAvInfo->stAvSettings.enVidStreamType)
    {
        AV_SDK_StatusToHal(stStatusInfo.enRunStatus, &pstStatus->stVidStatus.enDecodeState);
        pstStatus->stVidStatus.enDecodeState
            = (TRUE == pstAvInfo->bFreezeVideo) ? AV_DECODER_STATE_FREEZING : pstStatus->stVidStatus.enDecodeState;

        pstStatus->stVidStatus.u32DispPicCount      = stStatusInfo.u32VidFrameCount;
        pstStatus->stVidStatus.enStreamType         = pstAvInfo->stAvSettings.enVidStreamType;
        pstStatus->stVidStatus.u16FpsDecimal        = stStreaminfo.stVidStreamInfo.u32fpsDecimal;
        pstStatus->stVidStatus.u16FpsInteger        = stStreaminfo.stVidStreamInfo.u32fpsInteger;

        pstStatus->stVidStatus.enSourceType
            = (HI_UNF_AVPLAY_STREAM_TYPE_TS == pstAvInfo->enStreamType) ? AV_SOURCE_TUNER : AV_SOURCE_MEM;
        AV_SDK_3DFormatToHal(stVideoFrameInfo.enFramePackingType, &pstStatus->stVidStatus.en3dFormat);
        pstStatus->stVidStatus.u32PesBufferSize     = 0;
        pstStatus->stVidStatus.u32PesBufferFreeSize = 0;
        pstStatus->stVidStatus.u32EsBufferSize      = stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_VID].u32BufSize;
        pstStatus->stVidStatus.u32EsBufferFreeSize
            = stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_VID].u32BufSize - stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_VID].u32UsedSize;

        pstStatus->stVidStatus.bInterlaced          = (TRUE == stStreaminfo.stVidStreamInfo.bProgressive) ? FALSE : TRUE;
        pstStatus->stVidStatus.u32SourceWidth       = stStreaminfo.stVidStreamInfo.u32Width;
        pstStatus->stVidStatus.u32SouceHeight       = stStreaminfo.stVidStreamInfo.u32Height;
        pstStatus->stVidStatus.u32DisplayWidth      = stStreaminfo.stVidStreamInfo.u32DisplayWidth;
        pstStatus->stVidStatus.u32DisplayHeight     = stStreaminfo.stVidStreamInfo.u32DisplayHeight;
        pstStatus->stVidStatus.u32Bps               = stStreaminfo.stVidStreamInfo.u32bps;

        pstStatus->stVidStatus.u16Pid               = pstAvInfo->stAvSettings.u16VidPid;
        pstStatus->u16PcrPid                        = pstAvInfo->stAvSettings.u16PcrPid;

        pstStatus->stVidStatus.s64Pts               = AV_SDK_PTS_TO_HAL(stStatusInfo.stSyncStatus.u32LastVidPts);
        pstStatus->stVidStatus.s64FirstPts          = AV_SDK_PTS_TO_HAL(stStatusInfo.stSyncStatus.u32FirstVidPts);
        pstStatus->stVidStatus.u32Stc               = 0;

        pstStatus->s32AVDiffTime                    = stStatusInfo.stSyncStatus.s32DiffAvPlayTime;
        pstStatus->stVidStatus.u32FrameBufTime      = stStatusInfo.stBufStatus[HI_UNF_AVPLAY_BUF_ID_ES_VID].u32FrameBufTime;

    #ifdef HAL_HISI_EXTEND_H
        s32Ret = AV_SDK_GetVdecInfo(hAvPlayerSdk, &stVdecInfo);
        pstStatus->stVidStatus.u32PicNotDecodeCount = (SUCCESS == s32Ret) ? stVdecInfo.u32UndecFrmNum : 0;
    #endif
    }

    return SUCCESS;
}

static S32 AV_SDK_EvtCallback(HANDLE hAvPlayerSdk,
                              HI_UNF_AVPLAY_EVENT_E enEvent,
                              VOID *pPara)
{
    U32 u32Index = AV_HAL_INVALID_IDX;
    AV_EVT_E            enEvtCbType = AV_EVT_BUTT;
    AV_STATUS_S         stAvStatus;
    AV_HAL_INFO_S*      pstAvInfo = NULL;
    AV_HAL_INFO_S       stAvInfo;
    AV_CALLBACK_PFN_T   pCallBack = NULL;
    AV_VID_STATUS_S     stVidStatus;
    AV_VID_FRAMEINFO_S  stVidFrameInfo;
    AV_AUD_FRAMEINFO_S  stAudFrameInfo;

    HI_UNF_NORMCHANGE_PARAM_S* pstUnfFormatParam = NULL;
    AV_FORMAT_CHANGE_PARAM_S stAVFormatParam;
    AV_INJECT_STATUS_S  stInjectStatus;
    BOOL                bEnableCallback = FALSE;

    HI_UNF_AO_FRAMEINFO_S*     pstAudioInfo = NULL;
    HI_UNF_VIDEO_FRAME_INFO_S* pstVideoInfo = NULL;

#ifdef HAL_HISI_EXTEND_H
    AV_UVMOS_FRAMEINFO_S stUvmosFrameInfo;
    HI_UNF_VIDEO_FRM_STATUS_INFO_S* pstFrameInfo = NULL;
#endif


    AV_HANDLE_Lock();
    u32Index = AV_HANDLE_IdxByAvPlayer(hAvPlayerSdk);

    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32Index), FAILURE, AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvPlayerSdk);

    pstAvInfo = (AV_HAL_INFO_S*)s_stAvHandleInfo[u32Index].pstAvHalInfo;
    AV_SDK_EvtToHal(hAvPlayerSdk, enEvent, pPara, &enEvtCbType);

    for (u32Index = 0; u32Index < AV_MAX_EVENT_NUM; u32Index++)
    {
        if (pstAvInfo->stAvCbParam[u32Index].enEvt == enEvtCbType)
        {
            pCallBack       = pstAvInfo->stAvCbParam[u32Index].pfnCallback;
            bEnableCallback = pstAvInfo->stAvCbParam[u32Index].bEnableCallback;
            break;
        }
    }

    /* this event is disable callback */
    HAL_CHK_CALL_RETURN((NULL == pCallBack || TRUE != bEnableCallback), SUCCESS, AV_HANDLE_UnLock(),
                        "not register this event");

    HAL_MEMCPY_NO_VERIFY(&stAvInfo, pstAvInfo, sizeof(AV_HAL_INFO_S));

    AV_HANDLE_UnLock();

    switch (enEvent)
    {
        case HI_UNF_AVPLAY_EVENT_EOS:
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, NULL);
            break;

        case HI_UNF_AVPLAY_EVENT_NORM_SWITCH:
            pstUnfFormatParam = (HI_UNF_NORMCHANGE_PARAM_S*)pPara;
            HAL_MEMSET_NO_VERIFY(&stAVFormatParam, 0, sizeof(stAVFormatParam));
            stAVFormatParam.u32NewFormat   = pstUnfFormatParam->enNewFormat;
            stAVFormatParam.u32ImageWidth  = pstUnfFormatParam->u32ImageWidth;
            stAVFormatParam.u32ImageHeight = pstUnfFormatParam->u32ImageHeight;
            stAVFormatParam.bProgressive   = pstUnfFormatParam->bProgressive;
            stAVFormatParam.u32FrameRate   = pstUnfFormatParam->u32FrameRate;
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, (VOID*)&stAVFormatParam);
            break;

        case HI_UNF_AVPLAY_EVENT_NEW_VID_FRAME:
            pstVideoInfo = (HI_UNF_VIDEO_FRAME_INFO_S*)pPara;

            HAL_MEMSET_NO_VERIFY(&stVidFrameInfo, 0, sizeof(AV_VID_FRAMEINFO_S));
            AV_SDK_VidFrameInfoToHal(pstVideoInfo, &stVidFrameInfo);

            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, (VOID*)&stVidFrameInfo);
            break;

        case HI_UNF_AVPLAY_EVENT_NEW_AUD_FRAME:
            pstAudioInfo = (HI_UNF_AO_FRAMEINFO_S*)pPara;

            HAL_MEMSET_NO_VERIFY(&stAudFrameInfo, 0, sizeof(AV_AUD_FRAMEINFO_S));
            AV_SDK_AudFrameInfoToHal(pstAudioInfo, &stAudFrameInfo);

            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, (VOID*)&stAudFrameInfo);
            break;

        case HI_UNF_AVPLAY_EVENT_IFRAME_ERR:
            HAL_MEMSET_NO_VERIFY(&stAvStatus, 0, sizeof(stAvStatus));
            HAL_MEMSET_NO_VERIFY(&stVidStatus, 0, sizeof(stVidStatus));
            //(VOID)AV_SDK_GetStatus(hAvPlayerSdk, &stAvInfo, &stAvStatus);
            HAL_MEMCPY_NO_VERIFY(&stVidStatus, &stAvStatus.stVidStatus, sizeof(stVidStatus));
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, (VOID*)&stVidStatus);
            break;

        case HI_UNF_AVPLAY_EVENT_VID_BUF_STATE:
            HAL_MEMSET_NO_VERIFY(&stInjectStatus, 0, sizeof(AV_INJECT_STATUS_S));
            //(VOID)av_inject_get_status(NULL, pstAvInfo->hVidInjecter, &stInjectStatus);
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, (VOID*)&stInjectStatus);
            break;

        case HI_UNF_AVPLAY_EVENT_AUD_BUF_STATE:
            HAL_MEMSET_NO_VERIFY(&stInjectStatus, 0, sizeof(AV_INJECT_STATUS_S));
            //(VOID)av_inject_get_status(NULL, pstAvInfo->hAudInjecter, &stInjectStatus);
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, (VOID*)&stInjectStatus);
            break;

        case HI_UNF_AVPLAY_EVENT_VID_UNSUPPORT:
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, NULL);
            break;

        case HI_UNF_AVPLAY_EVENT_AUD_UNSUPPORT:
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, NULL);
            break;

        case HI_UNF_AVPLAY_EVENT_SYNC_STAT_CHANGE:
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, NULL);
            break;

        case HI_UNF_AVPLAY_EVENT_SYNC_PTS_JUMP:
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, NULL);
            break;

        case HI_UNF_AVPLAY_EVENT_AUD_FRAME_ERR:
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, NULL);
            break;
#ifdef HAL_HISI_EXTEND_H
        case HI_UNF_AVPLAY_EVENT_VID_FRAME_INFO:
            pstFrameInfo = (HI_UNF_VIDEO_FRM_STATUS_INFO_S*)pPara;
            HAL_MEMSET_NO_VERIFY(&stUvmosFrameInfo, 0, sizeof(stUvmosFrameInfo));
            stUvmosFrameInfo.enVidFrmType = pstFrameInfo->enVidFrmType;
            stUvmosFrameInfo.u32VidFrmStreamSize = pstFrameInfo->u32VidFrmStreamSize;
            stUvmosFrameInfo.u32VidFrmQP  = pstFrameInfo->u32VidFrmQP;
            stUvmosFrameInfo.u32VidFrmPTS = pstFrameInfo->u32VidFrmPTS;
            stUvmosFrameInfo.u32MaxMV     = pstFrameInfo->u32MaxMV;
            stUvmosFrameInfo.u32MinMV     = pstFrameInfo->u32MinMV;
            stUvmosFrameInfo.u32AvgMV     = pstFrameInfo->u32AvgMV;
            stUvmosFrameInfo.u32SkipRatio = pstFrameInfo->u32SkipRatio;
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, (VOID*)&stUvmosFrameInfo);
            break;

        case HI_UNF_AVPLAY_EVENT_FIRST_FRAME_DISPLAYED:
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, NULL);
            break;

        case HI_UNF_AVPLAY_EVENT_VID_LASTFRMFLAG:
            pCallBack(pstAvInfo->hAvPlayerSdk, enEvtCbType, (VOID *)pPara);
            break;
#endif
        default:
            break;
    }

    return SUCCESS;
}

static S32 AV_SDK_GetAvPlayDhl(const HANDLE hAvHandle,
                               HANDLE* phSdkAvPlayHdl)
{
    HAL_CHK_RETURN((NULL == phSdkAvPlayHdl), ERROR_INVALID_PARAM, "av module error, handle is null.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_INVALID_PARAM, "av module error, handle is invalid.");

    *phSdkAvPlayHdl = hAvHandle;

    return SUCCESS;
}

static BOOL AV_SDK_IsSupportInject(AV_DATA_TYPE_E eDataType,
                                   AV_CONTENT_TYPE_E eContentType)
{
    if (AV_DATA_TYPE_ES == eDataType
        && (eContentType == AV_CONTENT_VIDEO || eContentType == AV_CONTENT_AUDIO))
    {
        return TRUE;
    }
    else if (AV_DATA_TYPE_PCM == eDataType
             && eContentType == AV_CONTENT_AUDIO)
    {
        return TRUE;
    }
    else if (AV_DATA_TYPE_IFRAME == eDataType
             && eContentType == AV_CONTENT_VIDEO)
    {
        return TRUE;
    }
    else if (AV_DATA_TYPE_TS == eDataType
             && eContentType == AV_CONTENT_DEFAULT)
    {
        // TODO: should support ts data type?
        return FALSE;
    }

    return FALSE;
}

#ifdef HAL_HISI_EXTEND_H
static HI_UNF_AVPLAY_BUFID_E AV_SDK_GetAvBufID(HI_UNF_AVPLAY_BUFID_E eBufID,
        AV_HDR_STREAM_TYPE_E eHDRType,
        U8* pu8PrivaData)
{
    HI_UNF_AVPLAY_BUFID_E enAvBufId = eBufID;

    if (HI_UNF_AVPLAY_BUF_ID_ES_VID == enAvBufId)
    {
        if (AV_HDR_STREAM_TYPE_DL_SINGLE_VES == eHDRType)
        {
            enAvBufId = HI_UNF_AVPLAY_BUF_ID_ES_VID_HDR_DL;
        }
        else if (AV_HDR_STREAM_TYPE_DL_DUAL_VES == eHDRType)
        {
            enAvBufId = HI_UNF_AVPLAY_BUF_ID_ES_VID_HDR_BL;

            if (NULL != pu8PrivaData && *pu8PrivaData)
            {
                enAvBufId = HI_UNF_AVPLAY_BUF_ID_ES_VID_HDR_EL;
            }
        }
        else if (AV_HDR_STREAM_TYPE_SL_VES == eHDRType)
        {
            enAvBufId = HI_UNF_AVPLAY_BUF_ID_ES_VID_HDR_BL;
        }
    }

    return enAvBufId;
}
#endif

static S32 AV_SDK_SendData(const HANDLE hInjecter,
                           VOID* const pHeader,
                           const U32 u32HeaderLen,
                           VOID* const pEsData,
                           const U32 u32EsLength,
                           const VOID* pvPrivate,
                           const U32 u32PrivateLen,
                           U32 u32TimeoutMs,
                           S64 s64Pts)
{
    S32  s32Ret = SUCCESS;
    U32  u32InjectIdx = AV_INJECT_INVALID_IDX;
    U32  u32AvIdx = AV_HAL_INVALID_IDX;
    U32  u32ReqLen = 0, u32SendLen = 0;

    AV_INJECT_INFO_S* pstInjectInfo = NULL;
    const AV_HAL_INFO_S* pstAvInfo = NULL;
    AV_AUD_STREAM_TYPE_E eAudStreamType = AV_AUD_STREAM_TYPE_BUTT;
    HANDLE hAvHandleSdk = AV_INVALID_HANDLE;
    HI_UNF_AVPLAY_BUFID_E enAvBufId = HI_UNF_AVPLAY_BUF_ID_BUTT;
    HI_UNF_STREAM_BUF_S   stBuffer;
    U8* pu8PrivaData = (U8*)pvPrivate;

    //HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((0 == u32HeaderLen && 0 == u32EsLength), ERROR_INVALID_PARAM, "parameter is invalid.");
    HAL_CHK_RETURN((NULL == pHeader && NULL == pEsData), ERROR_NULL_PTR, "parameter is NULL.");

    AV_HANDLE_Lock();
    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);

    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED, AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    s32Ret = AV_SDK_GetAvPlayDhl(pstInjectInfo->hAvHal, &hAvHandleSdk);
    u32AvIdx = AV_GET_HANDLE_Index(pstInjectInfo->hAvHal);
    HAL_CHK_CALL_RETURN((SUCCESS != s32Ret || AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED, AV_HANDLE_UnLock(),
                        "sdk av play not create, hal av handle(0x%x)", pstInjectInfo->hAvHal);

    pstAvInfo = (AV_HAL_INFO_S*)s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    enAvBufId = (AV_CONTENT_AUDIO == pstInjectInfo->stInjectSettings.enInjectContent)
                ? HI_UNF_AVPLAY_BUF_ID_ES_AUD : HI_UNF_AVPLAY_BUF_ID_ES_VID;

    eAudStreamType = pstAvInfo->stAvSettings.enAudStreamType;

#ifdef HAL_HISI_EXTEND_H
    enAvBufId = AV_SDK_GetAvBufID(enAvBufId, pstAvInfo->stAvSettings.stHdrParams.enHdrType, pu8PrivaData);
#endif

    AV_HANDLE_UnLock();

    u32ReqLen = u32HeaderLen + u32EsLength + u32PrivateLen;

    if (HI_UNF_AVPLAY_BUF_ID_ES_AUD == enAvBufId)
    {
        u32ReqLen = u32ReqLen > AV_MAX_AUDIO_CACHE_BUF ? AV_MAX_AUDIO_CACHE_BUF : u32ReqLen;

        /* for dts audio, length of data should alignment with 4 Byte*/
        if (AV_AUD_STREAM_TYPE_DTS == eAudStreamType ||
            AV_AUD_STREAM_TYPE_DTS_EXPRESS == eAudStreamType)
        {
            if (u32ReqLen & 0x3)
            {
                u32ReqLen += 4 - (u32ReqLen & 0x3);
            }
        }
    }

    HAL_MEMSET_NO_VERIFY(&stBuffer, 0, sizeof(stBuffer));
    s32Ret = HI_UNF_AVPLAY_GetBuf(hAvHandleSdk, enAvBufId, u32ReqLen, &stBuffer, u32TimeoutMs);

    HAL_CHK_RETURN_NO_PRINT((SUCCESS != s32Ret || stBuffer.u32Size < u32ReqLen), FAILURE);
    //if (SUCCESS != s32Ret || stBuffer.u32Size < u32ReqLen)
    //{
    //HAL_DEBUG("sdk get buffer error(0x%x), bufId = %d, request len = %u, get len = %u",
    //    s32Ret, enAvBufId, u32Len, stBuffer.u32Size);
    //return FAILURE;
    //}

    u32SendLen = stBuffer.u32Size;

    if (NULL != pHeader && u32HeaderLen > 0 && u32SendLen > 0)
    {
        HAL_MEMCPY(stBuffer.pu8Data, (U8*)pHeader, AV_MIN(u32SendLen, u32HeaderLen));
    }

    if (NULL != pEsData && u32EsLength > 0 && u32SendLen > u32HeaderLen)
    {
        HAL_MEMCPY(stBuffer.pu8Data + u32HeaderLen, (U8*)pEsData, AV_MIN(u32SendLen - u32HeaderLen, u32EsLength));
    }

    if (NULL != pu8PrivaData && u32PrivateLen > 0 && u32SendLen > (u32HeaderLen + u32EsLength))
    {
        pu8PrivaData++;
        HAL_MEMCPY(stBuffer.pu8Data + u32HeaderLen + u32EsLength, pu8PrivaData, AV_MIN(u32SendLen - u32HeaderLen - u32EsLength, u32PrivateLen));
    }

    s32Ret = HI_UNF_AVPLAY_PutBuf(hAvHandleSdk, enAvBufId, u32SendLen, s64Pts);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("sdk put buffer error(0x%x), request len = %u, get len = %u",
                  s32Ret, u32ReqLen, stBuffer.u32Size);
        u32SendLen = 0;
    }

    // TODO: should add ts stream type support?

    //HAL_DEBUG_EXIT();

    return (SUCCESS == s32Ret) ? (HI_S32)u32SendLen : FAILURE;
}

static VOID AV_SDK_DolbyPlusCallBack(DOLBYPLUS_EVENT_E Event,
                                     VOID* pUserData)
{
    return;
}

static S32 AV_SDK_SetADecAttr(HANDLE hAvPlayerSdk,
                              AV_AUD_STREAM_TYPE_E eAudStreamType,
                              AV_ADEC_PARAM_S* pstAdecParam,
                              DOLBYPLUS_DECODE_OPENCONFIG_S* pDolbyDecConfig)
{
    S32 s32Ret = HI_FAILURE;
    U32 u32AudioFormat = FORMAT_BUTT;
    HI_UNF_ACODEC_ATTR_S stAdecAttr;

    WAV_FORMAT_S                        stWavFormat;
    WMAPro_FORMAT_S                     stFFMPEGWMmapro;
    RA_FORMAT_INFO_S                    stRaFormat;
    TRUEHD_DECODE_OPENCONFIG_S          stTrueHDConfig;
    DTSM6_DECODE_OPENCONFIG_S           stDtsM6DecConfig;
    AMRNB_DECODE_OPENCONFIG_S           stAmrNb;
    AMRWB_DECODE_OPENCONFIG_S           stAmrWb;
    DTSHD_DECODE_OPENCONFIG_S           stDtsHdDecConfig;
    HA_BLURAYLPCM_DECODE_OPENCONFIG_S   stLpcmDecConfig;
    HA_FFMPEG_DECODE_OPENCONFIG_S       stFfmpeg;
    HA_CODEC_GET_DECOPENPARAM_PARAM_S   stHaCodecOpenParam;

    AV_HAL_AudCodecToSdk(eAudStreamType, (HA_FORMAT_E*)&u32AudioFormat);
    HAL_CHK_RETURN((FORMAT_BUTT == u32AudioFormat), FAILURE, "not support audio codec.");

    /* get AVPLAY's audio attribute */
    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_ADEC, &stAdecAttr);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get adec attr fail.");

    /* set AVPLAY's audio attribute */
    stAdecAttr.stDecodeParam.enDecMode = HD_DEC_MODE_RAWPCM;
    stAdecAttr.enType                  = HA_AUDIO_ID_MP3;

    /* get a audio codec object id */
    s32Ret = HI_UNF_AVPLAY_FoundSupportDeoder((HA_FORMAT_E)u32AudioFormat, (HI_U32*)&stAdecAttr.enType);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "find audio codec fail, format(%u), error code(0x%08x)", u32AudioFormat, s32Ret);

    switch (stAdecAttr.enType)
    {
        case HA_AUDIO_ID_PCM: /*lint !e778*/
            stWavFormat.nChannels       = (0 != pstAdecParam->u32Channels) ? (U16)pstAdecParam->u32Channels : 2;
            stWavFormat.nSamplesPerSec  = (0 != pstAdecParam->u32SampleRate) ? pstAdecParam->u32SampleRate : 48000;
            stWavFormat.wBitsPerSample  = (0 != pstAdecParam->u32BitWidth) ? pstAdecParam->u32BitWidth : 16;

            if (TRUE == pstAdecParam->bBigEndian)
            {
                stWavFormat.cbSize       = (U16)pstAdecParam->u32ExtradataSize;
                stWavFormat.cbExtWord[0] = pstAdecParam->pu8Extradata[0];
            }

            HA_PCM_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stWavFormat);
            break;

        case HA_AUDIO_ID_DOLBY_PLUS: /*lint !e778*/
            HAL_DEBUG("Dolby config: enDrcMode is %d, enOutLfe is %d, enDmxMode is %d, s16DynScaleHigh is %d, s16DynScaleLow is %d",
                        pDolbyDecConfig->enDrcMode, pDolbyDecConfig->enOutLfe, pDolbyDecConfig->enDmxMode, pDolbyDecConfig->s16DynScaleHigh, pDolbyDecConfig->s16DynScaleLow);
            HA_DOLBYPLUS_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), pDolbyDecConfig);
            stAdecAttr.stDecodeParam.enDecMode = HD_DEC_MODE_SIMUL;
            break;

        case HA_AUDIO_ID_DOLBY_TRUEHD: /*lint !e778*/
            HA_DOLBY_TRUEHD_DecGetDefalutOpenConfig(&stTrueHDConfig);
            HA_DOLBY_TRUEHD_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stTrueHDConfig);
            break;

        case HA_AUDIO_ID_MP2: /*lint !e778*/
            HA_MP2_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam));
            break;

        case HA_AUDIO_ID_AAC: /*lint !e778*/
            HA_AAC_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam));
            break;

        case HA_AUDIO_ID_MP3: /*lint !e778*/
            HA_MP3_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam));
            break;

        case HA_AUDIO_ID_AMRNB: /*lint !e778*/
            stAmrNb.enFormat = AMRNB_MIME;
            HA_AMRNB_GetDecDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stAmrNb);
            break;

        case HA_AUDIO_ID_AMRWB: /*lint !e778*/
            stAmrWb.enFormat = AMRWB_FORMAT_MIME;
            HA_AMRWB_GetDecDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stAmrWb);
            break;

        case HA_AUDIO_ID_WMA9STD: /*lint !e778*/
            stWavFormat.wFormatTag          = (U16)pstAdecParam->u32Version;
            stWavFormat.nChannels           = (U16)pstAdecParam->u32Channels;
            stWavFormat.nSamplesPerSec      = pstAdecParam->u32SampleRate;
            stWavFormat.nBlockAlign         = (U16)pstAdecParam->u32BlockAlign;
            stWavFormat.nAvgBytesPerSec     = pstAdecParam->u32Bps / 8;
            stWavFormat.cbSize              = (U16)pstAdecParam->u32ExtradataSize;
            stWavFormat.wBitsPerSample      = (0 != pstAdecParam->u32BitWidth) ? pstAdecParam->u32BitWidth : 16;

            if ((stWavFormat.cbSize < sizeof(stWavFormat.cbExtWord)) && pstAdecParam->pu8Extradata)
            {
                HAL_MEMCPY((U8*)(stWavFormat.cbExtWord), pstAdecParam->pu8Extradata, stWavFormat.cbSize);
            }

            HA_WMA_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stWavFormat);
            break;

        case HA_AUDIO_ID_COOK: /*lint !e778*/
            stRaFormat.ulActualRate     = pstAdecParam->u32SampleRate;
            stRaFormat.ulBitsPerFrame   = pstAdecParam->u32BlockAlign;
            stRaFormat.ulGranularity    = pstAdecParam->u32BlockAlign;
            stRaFormat.ulSampleRate     = pstAdecParam->u32SampleRate;
            stRaFormat.usAudioQuality   = 100;
            stRaFormat.usFlavorIndex    = 7;
            stRaFormat.usNumChannels    = (U16)pstAdecParam->u32Channels;
            stRaFormat.usBitsPerSample  = (0 != pstAdecParam->u32BitWidth) ? pstAdecParam->u32BitWidth : 16;
            stRaFormat.pOpaqueData      = pstAdecParam->pu8Extradata;
            stRaFormat.ulOpaqueDataSize = pstAdecParam->u32ExtradataSize;
            HA_COOK_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stRaFormat);
            break;

        case HA_AUDIO_ID_DTSHD: /*lint !e778*/
            HA_DTSHD_DecGetDefalutOpenConfig(&stDtsHdDecConfig);
            HA_DTSHD_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stDtsHdDecConfig);
            break;

        case HA_AUDIO_ID_DTSM6: /*lint !e778*/
            HA_DTSM6_DecGetDefalutOpenConfig(&stDtsM6DecConfig);
            HA_DTSM6_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stDtsM6DecConfig);
            break;

        case (HA_CODEC_ID_E)HA_AUDIO_ID_FFMPEG_WMAPRO: /*lint !e778*/
            stFFMPEGWMmapro.hAvCtx          = pstAdecParam->pCodecContext;
            stFFMPEGWMmapro.wFormatTag      = (U16)pstAdecParam->u32Version;
            stFFMPEGWMmapro.nChannels       = (U16)pstAdecParam->u32Channels;
            stFFMPEGWMmapro.nSamplesPerSec  = pstAdecParam->u32SampleRate;
            stFFMPEGWMmapro.nBlockAlign     = (U16)pstAdecParam->u32BlockAlign;
            stFFMPEGWMmapro.nAvgBytesPerSec = pstAdecParam->u32Bps / 8;
            stFFMPEGWMmapro.wBitsPerSample  = pstAdecParam->u32BitWidth;
            stFFMPEGWMmapro.cbSize          = 3 * sizeof(U16) + 3 * sizeof(U32);
            HAL_DEBUG("wFormatTag: %x, chn: %d, sample: %d, block: %d, bitrate: %d, bit: %d ",
                      stFFMPEGWMmapro.wFormatTag, stFFMPEGWMmapro.nChannels,
                      stFFMPEGWMmapro.nSamplesPerSec, stFFMPEGWMmapro.nBlockAlign,
                      stFFMPEGWMmapro.nAvgBytesPerSec, stFFMPEGWMmapro.wBitsPerSample);
            HA_FFMPEGC_WMAPROC_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stFFMPEGWMmapro);
            break;

        case HA_AUDIO_ID_BLYRAYLPCM: /*lint !e778*/
            HA_BLYRAYLPCM_DecGetDefalutOpenConfig(&stLpcmDecConfig);
            HA_BLYRAYLPCM_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stLpcmDecConfig);
            break;

        case HA_AUDIO_ID_FFMPEG_DECODE: /*lint !e778*/
            HA_FFMPEG_DecGetDefalutOpenConfig(&stFfmpeg);
            stFfmpeg.hAvCtx = pstAdecParam->pCodecContext;
            HA_FFMPEGC_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam), &stFfmpeg);
            break;

        case HA_AUDIO_ID_TRUEHD: /*lint !e778*/
            HA_TRUEHD_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam));
            break;

        case HA_AUDIO_ID_DRA: /*lint !e778*/
            HA_DRA_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam));
            break;

        case HA_AUDIO_ID_AC3PASSTHROUGH: /*lint !e778*/
            HA_AC3PASSTHROUGH_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam));
            break;

        case HA_AUDIO_ID_DTSPASSTHROUGH: /*lint !e778*/
            HA_DTSPASSTHROUGH_DecGetDefalutOpenParam(&(stAdecAttr.stDecodeParam));
            break;

        default:
            HAL_DEBUG("use user audio codec libraray!");
            HAL_MEMSET_NO_VERIFY(&stHaCodecOpenParam, 0, sizeof(HA_CODEC_GET_DECOPENPARAM_PARAM_S));

            stHaCodecOpenParam.enCmd           = HA_CODEC_GET_DECOPENPARAM_CMD;
            stHaCodecOpenParam.pstDecodeParams = &stAdecAttr.stDecodeParam;

            s32Ret = HI_UNF_AVPLAY_ConfigAcodec(stAdecAttr.enType, &stHaCodecOpenParam);
            HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get audio decode param fail!");
            break;
    }

    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_ADEC, &stAdecAttr);
    HAL_CHK_RETURN((s32Ret != HI_SUCCESS), FAILURE, "set adec attr fail");

    return SUCCESS;
}

#ifdef HAL_HISI_EXTEND_H
static S32 AV_SDK_SetLowDelay(HANDLE hAvPlayerSdk,
                              AV_LOW_DELAY_S* pstLowDelayCfg)
{
    S32 s32Ret = FAILURE;
    HI_UNF_AVPLAY_LOW_DELAY_ATTR_S stLowDelayAttr;

    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_LOW_DELAY, &stLowDelayAttr);
    HAL_CHK_RETURN((HI_SUCCESS != s32Ret), FAILURE, "call HI_UNF_AVPLAY_GetAttr LOW_DELAY failed, ret[%d]", s32Ret);

    if (stLowDelayAttr.bEnable == pstLowDelayCfg->bEnable)
    {
        HAL_DEBUG("low delay is already set\n");
        return SUCCESS;
    }

    stLowDelayAttr.bEnable = (TRUE == pstLowDelayCfg->bEnable) ? HI_TRUE : HI_FALSE;
    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_LOW_DELAY, &stLowDelayAttr);
    HAL_CHK_RETURN((HI_SUCCESS != s32Ret), s32Ret, "call HI_UNF_AVPLAY_SetAttr LOW_DELAY failed, ret[%d]", s32Ret);

    return SUCCESS;
}
#endif

static S32 AV_SDK_SetVDecAttr(HANDLE hAvPlayerSdk,
                              AV_VID_STREAM_TYPE_E eVidStreamType,
                              AV_VDEC_PARAM_S* pstVdecParam)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_VCODEC_ATTR_S stVdecAttr;
    HI_UNF_AVPLAY_FRMRATE_PARAM_S stFrameRate;

    /* get AVPLAY's vedio attribute */
    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get vdec attr fail");

    /* set AVPLAY's vedio attribute */
    AV_HAL_VidCodecToSdk(eVidStreamType, &stVdecAttr.enType);
    stVdecAttr.enMode         = HI_UNF_VCODEC_MODE_NORMAL;
    stVdecAttr.bOrderOutput   = HI_FALSE;
    stVdecAttr.pCodecContext  = pstVdecParam->pCodecContext;
#ifdef HAL_HISI_EXTEND_H
    stVdecAttr.s32CtrlOptions = pstVdecParam->s32CtrlOptions;
#endif

    if (HI_UNF_VCODEC_TYPE_VC1 == stVdecAttr.enType)
    {
        stVdecAttr.unExtAttr.stVC1Attr.bAdvancedProfile = (0 == pstVdecParam->u32Profile) ? HI_FALSE : HI_TRUE;
        stVdecAttr.unExtAttr.stVC1Attr.u32CodecVersion  = pstVdecParam->u32Version;
    }
    else if (HI_UNF_VCODEC_TYPE_VP6 == stVdecAttr.enType
             || HI_UNF_VCODEC_TYPE_VP6F == stVdecAttr.enType
             || HI_UNF_VCODEC_TYPE_VP6A == stVdecAttr.enType)
    {
#ifdef LINUX_OS
        stVdecAttr.unExtAttr.stVP6Attr.u16DispWidth = pstVdecParam->u16Width;
        stVdecAttr.unExtAttr.stVP6Attr.u16DispHeight = pstVdecParam->u16Height;
#else
        stVdecAttr.unExtAttr.stVP6Attr.u16DispWidth = pstVdecParam->u16Width;
        stVdecAttr.unExtAttr.stVP6Attr.u16DispHeight = pstVdecParam->u16Height;
#endif
        stVdecAttr.unExtAttr.stVP6Attr.bReversed = (TRUE == pstVdecParam->bFlip) ? HI_TRUE : HI_FALSE;
    }

    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set vdec attr fail");

    if (0 != pstVdecParam->u32Fps)
    {
        stFrameRate.enFrmRateType = HI_UNF_AVPLAY_FRMRATE_TYPE_USER_PTS;
        stFrameRate.stSetFrmRate.u32fpsInteger = pstVdecParam->u32Fps / 1000;
        stFrameRate.stSetFrmRate.u32fpsDecimal = pstVdecParam->u32Fps % 1000;

#ifdef HAL_HISI_EXTEND_H
        if (AV_VDEC_FRMRATE_TYPE_USER == pstVdecParam->enFrmRateType
            && stFrameRate.stSetFrmRate.u32fpsDecimal)
        {
            stFrameRate.enFrmRateType = HI_UNF_AVPLAY_FRMRATE_TYPE_USER;
        }
#endif
        s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_FRMRATE_PARAM, (HI_VOID*)&stFrameRate);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set video frame rate fail, fps is (%d.%d)",
                       stFrameRate.stSetFrmRate.u32fpsInteger,
                       stFrameRate.stSetFrmRate.u32fpsDecimal);
    }

    return SUCCESS;
}

static S32 AV_SDK_GetVdecInfo(HANDLE hAvPlayerSdk, HI_UNF_AVPLAY_VDEC_INFO_S* pstVdecInfo)
{
    S32 s32Ret = SUCCESS;
    HI_CODEC_VIDEO_CMD_S        stVidPara;

    pstVdecInfo->u32UndecFrmNum = 0;
    stVidPara.u32CmdID = HI_UNF_AVPLAY_GET_VDEC_INFO_CMD;
    stVidPara.pPara = pstVdecInfo;

    s32Ret = HI_UNF_AVPLAY_Invoke(hAvPlayerSdk, HI_UNF_AVPLAY_INVOKE_VCODEC, &stVidPara);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get vdec info fail");

    return SUCCESS;
}

static S32 AV_SDK_SetSyncAttr(HANDLE hAvPlayerSdk,
                              AV_SYNC_MODE_E eSyncMode,
                              AV_SYNC_PARAM_S* pstSyncParam)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_SYNC_ATTR_S stSync;

    /* get AVPLAY's vedio attribute */
    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSync);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get sync attr fail");

    AV_HAL_SyncModeToSdk(eSyncMode, &stSync.enSyncRef);

    stSync.bQuickOutput                         = (TRUE == pstSyncParam->bQuickOutput) ? HI_TRUE : HI_FALSE;
    stSync.u32PreSyncTimeoutMs                  = pstSyncParam->u32PreSyncTimeoutMs;
    stSync.stSyncNovelRegion.bSmoothPlay        = (TRUE == pstSyncParam->stSyncNovelRegion.bSmoothPlay) ? HI_TRUE : HI_FALSE;
    stSync.stSyncNovelRegion.s32VidNegativeTime = pstSyncParam->stSyncNovelRegion.s32VidNegativeTime;
    stSync.stSyncNovelRegion.s32VidPlusTime     = pstSyncParam->stSyncNovelRegion.s32VidPlusTime;
    stSync.stSyncStartRegion.bSmoothPlay        = (TRUE == pstSyncParam->stSyncStartRegion.bSmoothPlay) ? HI_TRUE : HI_FALSE;
    stSync.stSyncStartRegion.s32VidNegativeTime = pstSyncParam->stSyncStartRegion.s32VidNegativeTime;
    stSync.stSyncStartRegion.s32VidPlusTime     = pstSyncParam->stSyncStartRegion.s32VidPlusTime;

    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSync);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set sync attr fail");

    return SUCCESS;
}

static S32 AV_SDK_SetErroCovery(HANDLE hAvPlayerSdk,
                                U32 u32ErrorCovery)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_VCODEC_ATTR_S stVdecAttr;

    /* get AVPLAY's vedio attribute */
    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get vdec attr fail");

    /* set AVPLAY's vedio attribute */
    stVdecAttr.u32ErrCover = u32ErrorCovery;

    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_VDEC, &stVdecAttr);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set vdec error covery attr fail");

    return SUCCESS;
}

static S32 AV_SDK_Set3DFormat(HANDLE hAvPlayerSdk,
                              AV_3D_FORMAT_E e3DFormat)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_VIDEO_FRAME_PACKING_TYPE_E eFormat = HI_UNF_FRAME_PACKING_TYPE_NONE;

    AV_HAL_3DFormatToSdk(e3DFormat, &eFormat);

    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_FRMPACK_TYPE, &eFormat);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set frame pack type fail");

    return SUCCESS;
}

static S32 AV_SDK_TPlay(HANDLE hAvPlayerSdk,
                        S32 s32Speed)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_AVPLAY_TPLAY_OPT_S stOption;

    /* if speed value is 100, resume to normal play status. */
    if (AV_NORMAL_PLAY_SPEED != s32Speed)
    {
        if (0 != s32Speed)
        {
            stOption.enTplayDirect   = (s32Speed > 0) ? HI_UNF_AVPLAY_TPLAY_DIRECT_FORWARD : HI_UNF_AVPLAY_TPLAY_DIRECT_BACKWARD;
            stOption.u32SpeedInteger = abs(s32Speed / AV_NORMAL_PLAY_SPEED);
            stOption.u32SpeedDecimal = (s32Speed % AV_NORMAL_PLAY_SPEED) * 1000 / AV_NORMAL_PLAY_SPEED;

            HAL_DEBUG("tplay speed = %d.%u ", s32Speed / AV_NORMAL_PLAY_SPEED, stOption.u32SpeedDecimal);

            /* ff/bw play audio or video stream */
            s32Ret = HI_UNF_AVPLAY_Tplay(hAvPlayerSdk, &stOption);
        }
        else
        {
            s32Ret = HI_UNF_AVPLAY_Tplay(hAvPlayerSdk, NULL);
        }

        HI_UNF_VCODEC_ATTR_S stVdecAdvAttr;
        s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_VDEC, (HI_VOID*)&stVdecAdvAttr);

        if (HI_SUCCESS == s32Ret)
        {
            stVdecAdvAttr.bOrderOutput = (s32Speed < 0) ? HI_TRUE : HI_FALSE;
            stVdecAdvAttr.u32ErrCover  = 0;
            s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_VDEC, (HI_VOID*)&stVdecAdvAttr);
        }

        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set tplay attribute fail");
    }
    else
    {
        s32Ret = HI_UNF_AVPLAY_Resume(hAvPlayerSdk, NULL);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "resume tplay fail");
    }

    return HI_SUCCESS;
}

#ifdef HAL_HISI_EXTEND_H
static S32 AV_SDK_SetDecMode(HANDLE hAvPlayerSdk,
                             AV_VDEC_MODE_E eDecMode)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_VCODEC_MODE_E eSdkDecMode = HI_UNF_VCODEC_MODE_NORMAL;

    switch (eDecMode)
    {
        case AV_VDEC_MODE_NORMAL:
            eSdkDecMode = HI_UNF_VCODEC_MODE_NORMAL;
            break;

        case AV_VDEC_MODE_IP:
            eSdkDecMode = HI_UNF_VCODEC_MODE_IP;
            break;

        case AV_VDEC_MODE_I:
            eSdkDecMode = HI_UNF_VCODEC_MODE_I;
            break;

        case AV_VDEC_MODE_DROP_INVALID_B:
            eSdkDecMode = HI_UNF_VCODEC_MODE_DROP_INVALID_B;
            break;

        default:
            break;
    }

    s32Ret = HI_UNF_AVPLAY_SetDecodeMode(hAvPlayerSdk, eSdkDecMode);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set decoder mode fail");

    return SUCCESS;
}
#endif

static S32 AV_SDK_SetPid(HANDLE hAvPlayerSdk,
                         U32 vidPid,
                         U32 audPid,
                         U32 pcrPid)
{
    S32 s32Ret = SUCCESS;

    if (AV_INVALID_PID != vidPid)
    {
        s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_VID_PID, &vidPid);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set video pid fail, ret(0x%x)", s32Ret);
    }

    if (AV_INVALID_PID != audPid)
    {
        s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &audPid);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set audio pid fail, ret(0x%x)", s32Ret);
    }

    if (AV_INVALID_PID != pcrPid)
    {
        s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_PCR_PID, &pcrPid);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set pcr pid fail, ret(0x%x)", s32Ret);
    }

    return SUCCESS;
}

static S32 AV_SDK_SetSyncOffset(HANDLE hAvPlayerSdk,
                                S32 s32AudOffset,
                                S32 s32VidOffset)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_SYNC_ATTR_S stSync;

    /* get AVPLAY's vedio attribute */
    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSync);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get sync attr fail");

    stSync.s32AudPtsAdjust = s32AudOffset;
    stSync.s32VidPtsAdjust = s32VidOffset;

    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_SYNC, &stSync);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set pts offset fail");

    return SUCCESS;
}

#ifdef HAL_HISI_EXTEND_H
static S32 AV_SDK_EnableTVP(HANDLE hAvPlayerSdk,
                            BOOL bEnableTvp)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_AVPLAY_TVP_ATTR_S stTvpAttr;

    stTvpAttr.bEnable = (FALSE == bEnableTvp) ? HI_FALSE : HI_TRUE;

    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_TVP, &stTvpAttr);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set tvp attribute fail");

    return SUCCESS;
}

static S32 AV_SDK_EnableAudSecurity(HANDLE hAvPlayerSdk,
                            BOOL bEnable)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_AVPLAY_AUD_SECURITY_ATTR_S stTvpAttr;

    stTvpAttr.bEnable = (FALSE == bEnable) ? HI_FALSE : HI_TRUE;

    s32Ret = HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_AUD_SECURITY, &stTvpAttr);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set Aud Security attribute fail");

    return SUCCESS;
}

#endif

static S32 AV_SDK_SetRotation(HANDLE hAvPlayerSdk,
                              AV_VID_ROTATION_E enVideoRotation)
{
    S32 s32Ret = SUCCESS;
    HANDLE hWindow = AV_INVALID_HANDLE;
    HI_UNF_VO_ROTATION_E eRotation = HI_UNF_VO_ROTATION_0;
    HI_UNF_VO_ROTATION_E eLastRotation = HI_UNF_VO_ROTATION_0;

    switch (enVideoRotation)
    {
        case AV_VID_ROTATION_0:
            eRotation = HI_UNF_VO_ROTATION_0;
            break;

        case AV_VID_ROTATION_90:
            eRotation = HI_UNF_VO_ROTATION_90;
            break;

        case AV_VID_ROTATION_180:
            eRotation = HI_UNF_VO_ROTATION_180;
            break;

        case AV_VID_ROTATION_270:
            eRotation = HI_UNF_VO_ROTATION_270;
            break;

        default:
            eRotation = HI_UNF_VO_ROTATION_0;
            break;
    }

    s32Ret = HI_MPI_AVPLAY_GetWindowHandle(hAvPlayerSdk, &hWindow);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get window handle fail");

    s32Ret = HI_UNF_VO_GetRotation(hWindow, &eLastRotation);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "Get video rotation fail");

    if (eLastRotation != eRotation)
    {
        s32Ret = HI_UNF_VO_SetRotation(hWindow, eRotation);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set video rotation fail");
    }


    return SUCCESS;
}

#if 0
static S32 AV_SDK_AttackWindow(HANDLE hAvPlayerSdk,
                               HANDLE* phWindow)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_WINDOW_ATTR_S stWinAttr;
    HANDLE hWindow = AV_INVALID_HANDLE;

    /* if av not attach any window,
             we will create a virtual window for calling av_acquire_frame to get video frame */
    HAL_MEMSET_NO_VERIFY(&stWinAttr, 0, sizeof(stWinAttr));
    stWinAttr.enDisp                                = HI_UNF_DISPLAY1;
    stWinAttr.bVirtual                              = HI_FALSE;
    stWinAttr.stWinAspectAttr.enAspectCvrs          = HI_UNF_VO_ASPECT_CVRS_IGNORE;
    stWinAttr.stWinAspectAttr.bUserDefAspectRatio   = HI_FALSE;
    stWinAttr.bUseCropRect                          = HI_FALSE;
    stWinAttr.bVirtual                              = HI_TRUE;
    stWinAttr.enVideoFormat                         = HI_UNF_FORMAT_YUV_SEMIPLANAR_420;

    s32Ret = HI_UNF_VO_CreateWindow(&stWinAttr, &hWindow);

    if (SUCCESS != s32Ret || AV_INVALID_HANDLE == hWindow)
    {
        *phWindow = AV_INVALID_HANDLE;
        HAL_ERROR("create window fail, vid start fail");
        return FAILURE;
    }

    s32Ret = HI_UNF_VO_AttachWindow(hWindow, hAvPlayerSdk);
    HAL_CHK_PRINTF(SUCCESS != s32Ret, "attach window fail");

    s32Ret = HI_UNF_VO_SetWindowEnable(hWindow, HI_TRUE);
    HAL_CHK_PRINTF(SUCCESS != s32Ret, "enable window fail");

    *phWindow = hWindow;

    return SUCCESS;
}
#endif

#ifdef HAL_HISI_EXTEND_H
static S32 AV_SDK_SetHdrAttr(HANDLE hAvPlayerSdk, const AV_HDR_PARAM_S* pstAvHdrParams)
{
    HI_UNF_AVPLAY_HDR_ATTR_S stHdrAttr;
    HI_UNF_AVPLAY_OPEN_OPT_S stElDefaultCodecOpt;

    HAL_DEBUG_ENTER();

    HAL_MEMSET_NO_VERIFY(&stHdrAttr, 0, sizeof(HI_UNF_AVPLAY_HDR_ATTR_S));
    stElDefaultCodecOpt.enDecType = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
    stElDefaultCodecOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    stElDefaultCodecOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;

    if (!pstAvHdrParams->bEnable || AV_HDR_STREAM_TYPE_NONE == pstAvHdrParams->enHdrType)
    {
        return SUCCESS;
    }

    stHdrAttr.bEnable = TRUE;
    stHdrAttr.bCompatible = pstAvHdrParams->bCompatible;
    AV_HAL_HdrTypeToSdk(pstAvHdrParams->enHdrType, &stHdrAttr.enHDRStreamType);
    AV_HAL_VidCodecToSdk(pstAvHdrParams->enElType, &stHdrAttr.enElType);

    HAL_CHK_RETURN(HI_UNF_AVPLAY_HDR_STREAM_TYPE_BUTT == stHdrAttr.enHDRStreamType,
                   ERROR_NOT_SUPPORTED, "Unknow HDR streamType!!");

    if (AV_HDR_STREAM_TYPE_DL_SINGLE_VES == pstAvHdrParams->enHdrType
        || AV_HDR_STREAM_TYPE_DL_DUAL_VES == pstAvHdrParams->enHdrType)
    {
        HAL_MEMCPY_NO_VERIFY(&stHdrAttr.stElCodecOpt, &stElDefaultCodecOpt, sizeof(HI_UNF_AVPLAY_OPEN_OPT_S));
    }

    HI_S32 s32Ret =  HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_HDR, &stHdrAttr);

    HAL_DEBUG_EXIT();

    return s32Ret;
}
#endif

static S32 AV_SDK_SetInjectHdl(HANDLE hAvHandle,
                               AV_CONTENT_TYPE_E eContentType,
                               HANDLE hInjecter)
{
    U32 u32AvIdx = AV_HAL_INVALID_IDX;
    AV_HAL_INFO_S* pstAvInfo = NULL;

    AV_HANDLE_Lock();
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    if (AV_CONTENT_AUDIO == eContentType)
    {
        pstAvInfo->hAudInjecter = hInjecter;
    }
    else if (AV_CONTENT_VIDEO == eContentType)
    {
        pstAvInfo->hVidInjecter = hInjecter;
    }

    AV_HANDLE_UnLock();

    return SUCCESS;
}

static S32 AV_SDK_SetAttachAvHdl(HANDLE hInjecter,
                                 HI_UNF_AVPLAY_MEDIA_CHAN_E eType,
                                 HANDLE hAvHandle)
{
    U32 u32InjectIdx = AV_INJECT_INVALID_IDX;
    AV_INJECT_INFO_S* pstInjectInfo = NULL;

    AV_HANDLE_Lock();
    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    pstInjectInfo->enAvChanType = eType;
    pstInjectInfo->hAvHal       = hAvHandle;

    AV_HANDLE_UnLock();

    return SUCCESS;
}

static S32 AV_SDK_TermInjecter(HANDLE hInjecter,
                               BOOL bTerm)
{
    U32 u32InjectIdx = AV_INJECT_INVALID_IDX;
    AV_INJECT_INFO_S* pstInjectInfo = NULL;

    AV_HANDLE_Lock();
    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    pstInjectInfo->bTerm = bTerm;

    AV_HANDLE_UnLock();

    return SUCCESS;
}

static S32 AV_SDK_SetAttr(HI_HANDLE hAvPlaySdk,
                          AV_HAL_INFO_S*  pstAvSettingInfo,
                          DOLBYPLUS_DECODE_OPENCONFIG_S* pDolbyConfig,
                          AV_SETTINGS_S* const pstSettings)
{
    S32 s32Ret = SUCCESS;

    HAL_CHK_RETURN_NO_PRINT((NULL == pstAvSettingInfo || NULL == pstSettings), FAILURE);

    /* 1. set audio decoder attributes, should set after inject attached */
    if (0 != HAL_MEMCMP(&pstAvSettingInfo->stAvSettings.stAdecParams, &pstSettings->stAdecParams, sizeof(AV_ADEC_PARAM_S))
        || pstAvSettingInfo->stAvSettings.enAudStreamType != pstSettings->enAudStreamType
        || 0 != HAL_MEMCMP(&pstAvSettingInfo->stDolbyDecOpenConfig, pDolbyConfig, sizeof(DOLBYPLUS_DECODE_OPENCONFIG_S)))
    {
        s32Ret = AV_SDK_SetADecAttr(hAvPlaySdk,
                                    pstSettings->enAudStreamType,
                                    &pstSettings->stAdecParams,
                                    pDolbyConfig);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set adec attr fail, streamtype: %d ", pstSettings->enAudStreamType);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "param is version: %d, samplerate: %d, bitwidth: %d, channels: %d, blockalign: %d, bps: %d, bigendian: %d ",
                       pstSettings->stAdecParams.u32Version, pstSettings->stAdecParams.u32SampleRate,
                       pstSettings->stAdecParams.u32BitWidth, pstSettings->stAdecParams.u32Channels,
                       pstSettings->stAdecParams.u32BlockAlign, pstSettings->stAdecParams.u32Bps,
                       pstSettings->stAdecParams.bBigEndian);
    }

    /* 2. current not support */
    HAL_CHK_PRINTF((pstAvSettingInfo->stAvSettings.stSourceParams.enDemuxId != pstSettings->stSourceParams.enDemuxId),
                   "not upport set source params");

    /* 3. sync attribute set, should set after inject attached */
    if (0 != HAL_MEMCMP(&pstAvSettingInfo->stAvSettings.stSyncParams, &pstSettings->stSyncParams, sizeof(AV_SYNC_PARAM_S))
        || pstAvSettingInfo->stAvSettings.enAvSyncMode != pstSettings->enAvSyncMode)
    {
        s32Ret = AV_SDK_SetSyncAttr(hAvPlaySdk, pstSettings->enAvSyncMode, &pstSettings->stSyncParams);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "param is sync mode: %d, presync time: %d, bquickoutput: %d ",
                       pstSettings->enAvSyncMode,
                       pstSettings->stSyncParams.u32PreSyncTimeoutMs,
                       pstSettings->stSyncParams.bQuickOutput);
    }

    /* 5. set 3D format */
    if (pstSettings->en3dFormat != pstAvSettingInfo->stAvSettings.en3dFormat)
    {
        s32Ret = AV_SDK_Set3DFormat(hAvPlaySdk, pstSettings->en3dFormat);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set 3d format fail.");
    }
#ifdef HAL_HISI_EXTEND_H
    /* 7. set decoder mode */
    if (pstSettings->eDecMode != pstAvSettingInfo->stAvSettings.eDecMode)
    {
        s32Ret = AV_SDK_SetDecMode(hAvPlaySdk, pstSettings->eDecMode);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set decoder mode fail.");
    }
#endif
    /* 6. set tplay speed */
    if (pstSettings->s32Speed != pstAvSettingInfo->stAvSettings.s32Speed)
    {
        s32Ret = AV_SDK_TPlay(hAvPlaySdk, pstSettings->s32Speed);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set tplay fail.");
    }
#ifdef HAL_HISI_EXTEND_H
    /* 8. set tvp attribute */
    if (pstSettings->bEnableTVP != pstAvSettingInfo->stAvSettings.bEnableTVP)
    {
        s32Ret = AV_SDK_EnableTVP(hAvPlaySdk, pstSettings->bEnableTVP);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set tvp enable flag fail.");
    }

    if (pstSettings->bEnableAudSecurity != pstAvSettingInfo->stAvSettings.bEnableAudSecurity)
    {
        s32Ret = AV_SDK_EnableAudSecurity(hAvPlaySdk, pstSettings->bEnableAudSecurity);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set Aud security enable flag fail.");
    }
#endif
    /* 9. TODO: set video decoder once */

    /* 10. save pid */
    if (pstAvSettingInfo->stAvSettings.u16AudPid != pstSettings->u16AudPid)
    {
        HAL_ERROR("Old aud pid(0x%x), new aud pid(0x%x)",
                  pstAvSettingInfo->stAvSettings.u16AudPid, pstSettings->u16AudPid);
        s32Ret = AV_SDK_SetPid(hAvPlaySdk, AV_INVALID_PID,
                               (U32)pstSettings->u16AudPid, AV_INVALID_PID);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set audio pid fail.");
    }

    if (pstAvSettingInfo->stAvSettings.u16VidPid != pstSettings->u16VidPid)
    {
        HAL_ERROR("Old vid pid(0x%x), new vid pid(0x%x)",
                  pstAvSettingInfo->stAvSettings.u16VidPid, pstSettings->u16VidPid);
        s32Ret = AV_SDK_SetPid(hAvPlaySdk, (U32)pstSettings->u16VidPid,
                               AV_INVALID_PID, AV_INVALID_PID);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set video pid fail.");
    }

    if (pstAvSettingInfo->stAvSettings.u16PcrPid != pstSettings->u16PcrPid
        && AV_SYNC_MODE_PCR == pstSettings->enAvSyncMode)
    {
        HAL_ERROR("Old pcr pid(0x%x), new pcr pid(0x%x)",
                  pstAvSettingInfo->stAvSettings.u16PcrPid, pstSettings->u16PcrPid);
        s32Ret = AV_SDK_SetPid(hAvPlaySdk, AV_INVALID_PID,
                               AV_INVALID_PID, (U32)pstSettings->u16PcrPid);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set pcr pid fail.");
    }

    /* 11. set sync offset */
    if (pstSettings->s32AudSyncOffseMs != pstAvSettingInfo->stAvSettings.s32AudSyncOffseMs
        || pstSettings->s32VidSyncOffseMs != pstAvSettingInfo->stAvSettings.s32VidSyncOffseMs)
    {
        s32Ret = AV_SDK_SetSyncOffset(hAvPlaySdk,
                                      pstSettings->s32AudSyncOffseMs,
                                      pstSettings->s32VidSyncOffseMs);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set sync offset fail.");
    }

    return s32Ret;
}

/*!
*@brief Get sdk av handle through HAL av handle. This function can be externed in other module.
*/
S32 av_get_sdk_avplay_hdl(const HANDLE hAvHandle,
                          HANDLE* phSdkAvPlayHdl)
{
    S32 s32Ret = FAILURE;

    HAL_DEBUG_ENTER();

    AV_HANDLE_Lock();
    s32Ret = AV_SDK_GetAvPlayDhl(hAvHandle, phSdkAvPlayHdl);
    AV_HANDLE_UnLock();

    HAL_DEBUG_EXIT();

    return s32Ret;
}

static S32 av_init(AV_DEVICE_S* pstDev,
                   const AV_INIT_PARAMS_S* const pstInitParams)
{
    S32 s32Ret = FAILURE;
    U32 u32Index = 0;

    HAL_DEBUG_ENTER();

    /* init av, some modules may call unf avplay deinit, so must call avplay init in av_init */
    s32Ret = AV_SDK_Init();

    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AV_INIT_FAILED, "av module error, s32Ret(0x%08x)", s32Ret);

    /* only init once in one proccess */
    HAL_CHK_RETURN(AV_IS_Init(), SUCCESS, "av is already init.");

    AV_HANDLE_Lock();

    for (u32Index = 0; u32Index < AV_HAL_MAX_COUNT; u32Index++)
    {
        s_stAvHandleInfo[u32Index].hAvHal = AV_INVALID_HANDLE;
        s_stAvHandleInfo[u32Index].bUsed  = FALSE;
        s_stAvHandleInfo[u32Index].pstAvHalInfo = NULL;
    }

    for (u32Index = 0; u32Index < AV_INJECT_MAX_COUNT; u32Index++)
    {
        s_stInjectHandleInfo[u32Index].hInject = AV_INVALID_HANDLE;
        s_stInjectHandleInfo[u32Index].bUsed   = FALSE;
    }

    AV_HANDLE_UnLock();

    s_bAvInit = TRUE;
    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_create(AV_DEVICE_S* pstDev,
                     HANDLE* const phAvHandle,
                     const AV_CREATE_PARAMS_S* const pstCreateParams)
{
    S32 s32Ret   = FAILURE;
    U32 u32Index = AV_HAL_INVALID_IDX;
    DMX_ID_E enDemuxId         = DMX_ID_BUTT;
    AV_HAL_INFO_S *pstAvInfo   = NULL;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "av not init.");
    HAL_CHK_RETURN((!phAvHandle || !pstCreateParams), ERROR_NULL_PTR,
                   "phAvHandle:0x%p, pstCreateParams:0x%p", phAvHandle, pstCreateParams);

    enDemuxId   = pstCreateParams->stSourceParams.enDemuxId;
    *phAvHandle = AV_INVALID_HANDLE;

    HAL_CHK_RETURN((enDemuxId >= DMX_ID_BUTT && AV_STREAM_TYPE_TS == pstCreateParams->enStreamType),
                   ERROR_INVALID_PARAM,
                   "invalid demux id:%d", enDemuxId);
    HAL_DEBUG("enDemuxId:%d", pstCreateParams->stSourceParams.enDemuxId);

    AV_HANDLE_Lock();

    u32Index = AV_MALLOC_HANDLE_Index(AV_INVALID_HANDLE);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32Index), FAILURE, AV_HANDLE_UnLock(),
                        "create too many av handle.");

    s_stAvHandleInfo[u32Index].bUsed = TRUE;
    AV_HANDLE_UnLock();

    s32Ret = AV_SDK_Create(pstCreateParams, u32Index, &pstAvInfo);

    AV_HANDLE_Lock();

    if (SUCCESS != s32Ret)
    {
        s_stAvHandleInfo[u32Index].bUsed = FALSE;
        HAL_ERROR("create sdk avplay fail.");
        AV_HANDLE_UnLock();
        return FAILURE;
    }

    s_stAvHandleInfo[u32Index].pstAvHalInfo = pstAvInfo;
    *phAvHandle = s_stAvHandleInfo[u32Index].pstAvHalInfo->hAvPlayerSdk; /*av handle ”Îavplay handle œ‡Õ¨*/
    s_stAvHandleInfo[u32Index].hAvHal = *phAvHandle;

    AV_HANDLE_UnLock();

    if (AV_STREAM_TYPE_TS == pstCreateParams->enStreamType)
    {
        s32Ret = HI_UNF_AVPLAY_ChnOpen(pstAvInfo->hAvPlayerSdk, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "open video channel fail, ret = 0x%x", s32Ret);

        s32Ret = HI_UNF_AVPLAY_ChnOpen(pstAvInfo->hAvPlayerSdk, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "open audio channel fail, ret = 0x%x", s32Ret);
    }

    HAL_DEBUG_EXIT();

    return s32Ret;
}

static S32 av_destroy(struct _AV_DEVICE_S* pstDev,
                      const HANDLE hAvHandle,
                      const AV_DESTROY_PARAMS_S* const pstDestroyParams)
{
    S32 s32Ret = FAILURE;
    U32 u32Index = AV_HAL_INVALID_IDX;
    AV_HAL_INFO_S* pstAvInfo = NULL;
    HANDLE hAvSdkHdl = AV_INVALID_HANDLE;
    HI_UNF_AVPLAY_STREAM_TYPE_E eStreamType = HI_UNF_AVPLAY_STREAM_TYPE_BUTT;

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "av not init.");

    AV_HANDLE_Lock();

    u32Index = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32Index), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av module error, handle no found.");
    pstAvInfo = s_stAvHandleInfo[u32Index].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "av error, handle is null.");

    hAvSdkHdl   = pstAvInfo->hAvPlayerSdk;
    eStreamType = pstAvInfo->enStreamType;

#ifdef SM_SUPPORT
    if (AV_INVALID_HANDLE != pstAvInfo->hSM)
    {
        s32Ret = HI_UNF_SM_Destroy(pstAvInfo->hSM);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "HI_UNF_SM_Destroy fail");

        s32Ret = HI_UNF_SM_DeInit();
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "HI_UNF_SM_DeInit fail");

        pstAvInfo->hSM = AV_INVALID_HANDLE;
    }
#endif

    AV_HANDLE_UnLock();

    if (HI_UNF_AVPLAY_STREAM_TYPE_TS == eStreamType)
    {
        s32Ret = HI_UNF_AVPLAY_ChnClose(hAvSdkHdl, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "close video channel fail, ret = 0x%x", s32Ret);

        s32Ret = HI_UNF_AVPLAY_ChnClose(hAvSdkHdl, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "close audio channel fail, ret = 0x%x", s32Ret);
    }

    s32Ret = AV_SDK_Close(pstAvInfo);
    AV_HANDLE_Lock();
    s_stAvHandleInfo[u32Index].hAvHal = AV_INVALID_HANDLE;
    s_stAvHandleInfo[u32Index].bUsed  = FALSE;
    s_stAvHandleInfo[u32Index].pstAvHalInfo = NULL;
    AV_HANDLE_UnLock();

    HAL_DEBUG_EXIT();

    return s32Ret;
}

static S32 av_term(AV_DEVICE_S* pstDev,
                   const AV_TERM_PARAMS_S* const pstTermParams)
{
    S32 s32Ret = FAILURE;

    HAL_DEBUG_ENTER();

    if (!AV_IS_Init())
    {
        HAL_DEBUG("Av Already Deinit!!");
        return SUCCESS;
    }

    AV_HANDLE_Lock();

    /* must destroy all av and inject handles before term av module */
    HAL_CHK_CALL_RETURN((0 < AV_HANDLE_Num() || 0 < AV_INJECT_Num()),
                        ERROR_AV_TERM_FAILED,
                        AV_HANDLE_UnLock(),
                        "has av or inject handle not destroy!");

    AV_HANDLE_UnLock();

    /* deinit av */
    s32Ret = AV_SDK_Deinit();
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AV_DEINIT_FAILED,
                   "sdk deinit return s32Ret(0x%08x)", s32Ret);

    s_bAvInit = FALSE;
    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_get_capability(AV_DEVICE_S* pstDev,
                             AV_CAPABILITY_S* pstCapability)
{
    AV_VDEC_CAPABILITY_S stVdecCap;
    U32 i = 0;

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((NULL == pstCapability), ERROR_NULL_PTR, "av module error, input null ptr");

    HAL_MEMSET_NO_VERIFY(pstCapability, 0, sizeof(AV_CAPABILITY_S));

    /* set capbility flags */
    pstCapability->stDecoderCapability.enInjectDataType =
        (AV_DATA_TYPE_E)((U32)AV_DATA_TYPE_TS | (U32)AV_DATA_TYPE_PES |
                         (U32)AV_DATA_TYPE_ES | (U32)AV_DATA_TYPE_PCM |
                         (U32)AV_DATA_TYPE_IFRAME);

    /* support all audio codec */
    HAL_MEMSET_NO_VERIFY(pstCapability->stDecoderCapability.au32AudDecode, TRUE, sizeof(U32) * AV_AUD_STREAM_TYPE_BUTT);

    /* only ac3 and dts codec support passthrought */
    pstCapability->stDecoderCapability.au32AudBypass[AV_AUD_STREAM_TYPE_AC3] = (U32)TRUE;
    pstCapability->stDecoderCapability.au32AudBypass[AV_AUD_STREAM_TYPE_DTS] = (U32)TRUE;

    /* video codec capability, if u32Dummy value is TRUE, the codec is hardware, otherwise is software codec */
    stVdecCap.bSupportedDecType = TRUE;
    stVdecCap.enDecCapLevel     = VDEC_RESO_LEVEL_D1;
    stVdecCap.u32Number         = AV_MAX_VDEC_5NUMBER;    /* software codec capability */
    stVdecCap.u32Fps            = AV_VDEC_30FPS ;
    stVdecCap.u32Dummy          = FALSE;

    for (i = 0; i < AV_VID_STREAM_TYPE_BUTT; i++)
    {
        HAL_MEMCPY_NO_VERIFY(&pstCapability->stDecoderCapability.stVidDecoder,
                             &stVdecCap, sizeof(AV_VDEC_CAPABILITY_S));
    }

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG2].bSupportedDecType = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG2].enDecCapLevel     = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG2].u32Number         = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG2].u32Fps            = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG2].u32Dummy          = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG4].bSupportedDecType = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG4].enDecCapLevel     = VDEC_RESO_LEVEL_4096x2160;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG4].u32Number         = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG4].u32Fps            = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MPEG4].u32Dummy          = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVS].bSupportedDecType   = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVS].enDecCapLevel       = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVS].u32Number           = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVS].u32Fps              = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVS].u32Dummy            = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVSPLUS].bSupportedDecType   = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVSPLUS].enDecCapLevel       = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVSPLUS].u32Number           = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVSPLUS].u32Fps              = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_AVSPLUS].u32Dummy            = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H263].bSupportedDecType  = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H263].enDecCapLevel      = VDEC_RESO_LEVEL_720P;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H263].u32Number          = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H263].u32Fps             = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H263].u32Dummy           = FALSE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H264].bSupportedDecType  = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H264].enDecCapLevel      = VDEC_RESO_LEVEL_4096x2160;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H264].u32Number          = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H264].u32Fps             = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_H264].u32Dummy           = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL8].bSupportedDecType = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL8].enDecCapLevel     = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL8].u32Number         = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL8].u32Fps            = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL8].u32Dummy          = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL9].bSupportedDecType = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL9].enDecCapLevel     = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL9].u32Number         = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL9].u32Fps            = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_REAL9].u32Dummy          = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VC1].bSupportedDecType   = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VC1].enDecCapLevel       = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VC1].u32Number           = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VC1].u32Fps              = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VC1].u32Dummy            = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6].bSupportedDecType   = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6].enDecCapLevel       = VDEC_RESO_LEVEL_720P;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6].u32Number           = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6].u32Fps              = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6].u32Dummy            = FALSE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6F].bSupportedDecType  = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6F].enDecCapLevel      = VDEC_RESO_LEVEL_720P;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6F].u32Number          = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6F].u32Fps             = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6F].u32Dummy           = FALSE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6A].bSupportedDecType  = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6A].enDecCapLevel      = VDEC_RESO_LEVEL_720P;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6A].u32Number          = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6A].u32Fps             = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP6A].u32Dummy           = FALSE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MJPEG].bSupportedDecType = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MJPEG].enDecCapLevel     = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MJPEG].u32Number         = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MJPEG].u32Fps            = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MJPEG].u32Dummy          = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_SORENSON].bSupportedDecType = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_SORENSON].enDecCapLevel     = VDEC_RESO_LEVEL_720P;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_SORENSON].u32Number         = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_SORENSON].u32Fps            = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_SORENSON].u32Dummy          = FALSE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_DIVX3].bSupportedDecType = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_DIVX3].enDecCapLevel     = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_DIVX3].u32Number         = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_DIVX3].u32Fps            = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_DIVX3].u32Dummy          = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_JPEG].bSupportedDecType  = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_JPEG].enDecCapLevel      = VDEC_RESO_LEVEL_8192x8192;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_JPEG].u32Number          = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_JPEG].u32Fps             = AV_VDEC_1FPS;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_JPEG].u32Dummy           = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP8].bSupportedDecType   = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP8].enDecCapLevel       = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP8].u32Number           = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP8].u32Fps              = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP8].u32Dummy            = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP9].bSupportedDecType   = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP9].enDecCapLevel       = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP9].u32Number           = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP9].u32Fps              = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_VP9].u32Dummy            = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MVC].bSupportedDecType   = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MVC].enDecCapLevel       = VDEC_RESO_LEVEL_FULLHD;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MVC].u32Number           = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MVC].u32Fps              = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_MVC].u32Dummy            = TRUE;

    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_HEVC].bSupportedDecType  = TRUE;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_HEVC].enDecCapLevel      = VDEC_RESO_LEVEL_4096x2160;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_HEVC].u32Number          = AV_MAX_VDEC_1NUMBER;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_HEVC].u32Fps             = AV_VDEC_30FPS ;
    pstCapability->stDecoderCapability.stVidDecoder[AV_VID_STREAM_TYPE_HEVC].u32Dummy           = TRUE;

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_evt_config(AV_DEVICE_S* pstDev,
                         const HANDLE hAvHandle,
                         const AV_EVT_CONFIG_PARAMS_S* const pstCfg)
{
    S32 s32Ret = SUCCESS;
    U32 i = 0, u32IdleIndex = AV_MAX_EVENT_NUM, u32EvtIndex = AV_MAX_EVENT_NUM;
    U32 u32AvIdx    = AV_HAL_INVALID_IDX;
    BOOL bRegister = FALSE;
    AV_HAL_INFO_S*  pstAvInfo = NULL;
    HANDLE          hAvPlaySdk = AV_INVALID_HANDLE;
    AV_EVT_CONFIG_PARAMS_S  stEventCfgBak;
    AV_EVT_CONFIG_PARAMS_S* pstEventParam = NULL;

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pstCfg), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((AV_EVT_BUTT == pstCfg->enEvt), ERROR_INVALID_PARAM, "parameter is invalid.");

    AV_HANDLE_Lock();

    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    hAvPlaySdk = pstAvInfo->hAvPlayerSdk;

    for (i = 0; i < AV_MAX_EVENT_NUM; i++)
    {
         /*whether av event is full*/
        if (AV_EVT_BUTT == pstAvInfo->stAvCbParam[i].enEvt && AV_MAX_EVENT_NUM == u32IdleIndex)
        {
            u32IdleIndex = i;
        }

         /*whether the event has been registered*/
        if (pstAvInfo->stAvCbParam[i].enEvt == pstCfg->enEvt && AV_MAX_EVENT_NUM == u32EvtIndex)
        {
            u32EvtIndex = i;
        }

         /*av event is not full and the event has been registered*/
        if (AV_MAX_EVENT_NUM != u32IdleIndex && AV_MAX_EVENT_NUM != u32EvtIndex)
        {
            break;
        }
    }

    HAL_MEMSET_NO_VERIFY(&stEventCfgBak, 0, sizeof(AV_EVT_CONFIG_PARAMS_S));

    /*the event has not been registered*/
    if (u32EvtIndex >= AV_MAX_EVENT_NUM)
    {
        HAL_CHK_CALL_RETURN((AV_MAX_EVENT_NUM <= u32IdleIndex), FAILURE,
                            AV_HANDLE_UnLock(),
                            "av event register is full!!");

        bRegister = TRUE;
        pstEventParam = &pstAvInfo->stAvCbParam[u32IdleIndex];
        HAL_MEMCPY_NO_VERIFY(&stEventCfgBak, pstEventParam, sizeof(AV_EVT_CONFIG_PARAMS_S));
        HAL_MEMCPY(pstEventParam, pstCfg, sizeof(AV_EVT_CONFIG_PARAMS_S));
    }
     /*the event has been registered, now unregister it*/
    else if (NULL == pstCfg->pfnCallback)
    {
        bRegister = FALSE;
        pstEventParam = &pstAvInfo->stAvCbParam[u32EvtIndex];
        HAL_MEMCPY_NO_VERIFY(&stEventCfgBak, pstEventParam, sizeof(AV_EVT_CONFIG_PARAMS_S));
        HAL_MEMSET(pstEventParam, 0, sizeof(AV_EVT_CONFIG_PARAMS_S));
        pstEventParam->enEvt = AV_EVT_BUTT;
    }
     /*the event has been registered, now update the callback*/
    else
    {
        HAL_DEBUG("event(%d) pfnCallback != NULL, update the callback.", pstCfg->enEvt);

        pstEventParam = &pstAvInfo->stAvCbParam[u32EvtIndex];
        HAL_MEMCPY(pstEventParam, pstCfg, sizeof(AV_EVT_CONFIG_PARAMS_S));
        AV_HANDLE_UnLock();
        return HI_SUCCESS;
    }

    AV_HANDLE_UnLock();

    s32Ret = AV_SDK_SetEvent(hAvPlaySdk, pstCfg->enEvt, bRegister);

    if (SUCCESS != s32Ret && NULL != pstEventParam)
    {
        AV_HANDLE_Lock();

        HAL_MEMCPY_NO_VERIFY(pstEventParam, &stEventCfgBak, sizeof(AV_EVT_CONFIG_PARAMS_S));

        AV_HANDLE_UnLock();
    }

    return s32Ret;
}

static S32 av_get_evt_config(AV_DEVICE_S* pstDev,
                             const HANDLE hAvHandle,
                             const AV_EVT_E enEvt,
                             AV_EVT_CONFIG_PARAMS_S* const pstCfg)
{
    U32 u32Index = AV_HAL_INVALID_IDX;
    AV_HAL_INFO_S* pstAvInfo = NULL;

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pstCfg), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((AV_EVT_BUTT <= enEvt), ERROR_INVALID_PARAM, "parameter is invalid.");

    AV_HANDLE_Lock();

    u32Index = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32Index), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32Index].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    for (u32Index = 0; u32Index < AV_MAX_EVENT_NUM; u32Index++)
    {
        if (pstAvInfo->stAvCbParam[u32Index].enEvt == enEvt)
        {
            break;
        }
    }

    HAL_CHK_CALL_RETURN((u32Index >= AV_MAX_EVENT_NUM), FAILURE,
                        AV_HANDLE_UnLock(),
                        "not register this event(0x%x)!!", (U32)enEvt);

    HAL_MEMCPY(pstCfg, &pstAvInfo->stAvCbParam[u32Index], sizeof(AV_EVT_CONFIG_PARAMS_S));
    AV_HANDLE_UnLock();

    return SUCCESS;
}

static S32 av_get_status(AV_DEVICE_S* pstDev,
                         const HANDLE hAvHandle,
                         AV_STATUS_S* pstStatus)
{
    U32 u32AvIdx = AV_HAL_INVALID_IDX;
    HANDLE          hAvPlayerSdk = AV_INVALID_HANDLE;
    AV_HAL_INFO_S   stAvInfo;
    AV_HAL_INFO_S*  pstAvInfo = NULL;

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pstStatus), ERROR_NULL_PTR, "parameter is NULL.");

    AV_HANDLE_Lock();

    HAL_MEMSET_NO_VERIFY(&stAvInfo, 0, sizeof(AV_HAL_INFO_S));
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    HAL_MEMCPY_NO_VERIFY(&stAvInfo, pstAvInfo, sizeof(AV_HAL_INFO_S));
    hAvPlayerSdk = stAvInfo.hAvPlayerSdk;

    AV_HANDLE_UnLock();

    return AV_SDK_GetStatus(hAvPlayerSdk, &stAvInfo, pstStatus);
}

static S32 av_get_config(AV_DEVICE_S* pstDev,
                         const HANDLE hAvHandle,
                         AV_SETTINGS_S* pstSettings)
{
    S32 s32Ret = SUCCESS;
    U32 u32AvIdx = AV_HAL_INVALID_IDX;
    const AV_HAL_INFO_S* pstAvInfo = NULL;
    HI_UNF_ACODEC_ATTR_S stAdecAttr;
    BOOL bAudStart = FALSE;

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pstSettings), ERROR_NULL_PTR, "parameter is NULL.");

    AV_HANDLE_Lock();

    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    HAL_MEMCPY_NO_VERIFY(pstSettings, &pstAvInfo->stAvSettings, sizeof(AV_SETTINGS_S));

#ifdef HAL_HISI_EXTEND_H
    /* 0 is invalid value */
    pstSettings->stDolbyInfo.s32ACMode     = (S32)pstAvInfo->stDolbyStreamInfo.s16Acmod;
    pstSettings->stDolbyInfo.s32StreamType = (S32)pstAvInfo->stDolbyStreamInfo.s16StreamType;
#endif
    /*
    HAL_DEBUG("AC mode is %d,dolby stream type is %d",
              pstSettings->stDolbyInfo.s32ACMode,
              pstSettings->stDolbyInfo.s32StreamType);
    */

    bAudStart = pstAvInfo->bAudStart;

    AV_HANDLE_UnLock();

    if (TRUE == bAudStart)
    {
        HAL_MEMSET_NO_VERIFY(&stAdecAttr, 0, sizeof(stAdecAttr));
        s32Ret = HI_UNF_AVPLAY_GetAttr(pstAvInfo->hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_ADEC, &stAdecAttr);

        if (SUCCESS == s32Ret)
        {
#ifdef HAL_HISI_EXTEND_H
            pstSettings->stDolbyInfo.u32DecoderType = (U32)stAdecAttr.enType;
#endif
        }
        else
        {
            HAL_DEBUG("get sdk adec codec id fail");
        }
    }

    return SUCCESS;
}

static VOID AV_SET_DolbyDec_Config(AV_DEVICE_S* pstDev,
                                   AV_HAL_INFO_S* pstAvInfo,
                                   AV_SETTINGS_S* const pstSettings, AV_HAL_INFO_S* pstAvSettingInfo)
{
#ifdef HAL_HISI_EXTEND_H
    HAL_MEMCPY_NO_VERIFY(&pstAvInfo->stAvSettings.stDolbyDecCfg, &pstSettings->stDolbyDecCfg, sizeof(AV_AUD_DOLBYDEC_CFG_S));
#endif
   HAL_MEMCPY_NO_VERIFY(pstAvSettingInfo, pstAvInfo, sizeof(AV_HAL_INFO_S));
    if (AV_AUD_STREAM_TYPE_AC3 == pstSettings->enAudStreamType || AV_AUD_STREAM_TYPE_EAC3 == pstSettings->enAudStreamType)
    {
        HA_DOLBYPLUS_DecGetDefalutOpenConfig(&pstAvInfo->stDolbyDecOpenConfig);
        pstAvInfo->stDolbyDecOpenConfig.pfnEvtCbFunc[HA_DOLBYPLUS_EVENT_SOURCE_CHANGE] = AV_SDK_DolbyPlusCallBack;
        pstAvInfo->stDolbyDecOpenConfig.pAppData[HA_DOLBYPLUS_EVENT_SOURCE_CHANGE]     = &pstAvInfo->stDolbyStreamInfo;
 #ifdef HAL_HISI_EXTEND_H
        pstAvInfo->stDolbyDecOpenConfig.enDrcMode = (DOLBYPLUS_DRC_MODE_E)pstSettings->stDolbyDecCfg.s32DolbyDrcMode;
        if (DOLBYPLUS_DRC_LINE == pstSettings->stDolbyDecCfg.s32DolbyDrcMode)
        {
            pstAvInfo->stDolbyDecOpenConfig.enOutLfe  = DOLBYPLUS_LFEOUTOFF;
            pstAvInfo->stDolbyDecOpenConfig.enDmxMode = DOLBYPLUS_DMX_SRND;
        }

        pstAvInfo->stDolbyDecOpenConfig.s16DynScaleHigh = pstSettings->stDolbyDecCfg.s32DoblyRange;
        pstAvInfo->stDolbyDecOpenConfig.s16DynScaleLow  = pstSettings->stDolbyDecCfg.s32DoblyRange;
 #endif
    }
    return;
}

static S32 av_set_config(AV_DEVICE_S* pstDev,
                         const HANDLE hAvHandle,
                         AV_SETTINGS_S* const pstSettings)
{
    S32 s32Ret = SUCCESS;
    U32 u32AvIdx = AV_HAL_INVALID_IDX;
    HANDLE hAvPlaySdk = AV_INVALID_HANDLE;
    AV_HAL_INFO_S* pstAvInfo = NULL;
    AV_HAL_INFO_S  stAvSettingInfo;
    DOLBYPLUS_DECODE_OPENCONFIG_S* pstDoblyDecOpenConfig = NULL;

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pstSettings), ERROR_NULL_PTR, "parameter is NULL.");

    AV_HANDLE_Lock();

    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");
    hAvPlaySdk = pstAvInfo->hAvPlayerSdk;

    /* save dolby decoder config */

    AV_SET_DolbyDec_Config(pstDev, pstAvInfo, pstSettings, &stAvSettingInfo);

    pstDoblyDecOpenConfig = &pstAvInfo->stDolbyDecOpenConfig;

    /* 1. save audio decoder attribute */
    pstAvInfo->stAvSettings.enAudStreamType = pstSettings->enAudStreamType;
    HAL_MEMCPY_NO_VERIFY(&pstAvInfo->stAvSettings.stAdecParams, &pstSettings->stAdecParams, sizeof(AV_ADEC_PARAM_S));

    /* 2. save video decoder attributes, should set in av_start_video function */
    if (0 != HAL_MEMCMP(&pstAvInfo->stAvSettings.stVdecParams, &pstSettings->stVdecParams, sizeof(AV_VDEC_PARAM_S))
        || pstAvInfo->stAvSettings.enVidStreamType != pstSettings->enVidStreamType)
    {
        pstAvInfo->stAvSettings.enVidStreamType = pstSettings->enVidStreamType;
        HAL_MEMCPY_NO_VERIFY(&pstAvInfo->stAvSettings.stVdecParams, &pstSettings->stVdecParams, sizeof(AV_VDEC_PARAM_S));
        HAL_DEBUG("set vdec codec type = 0x%x", pstAvInfo->stAvSettings.enVidStreamType);
    }

    /* 3. save sync parameters */
    HAL_MEMCPY_NO_VERIFY(&pstAvInfo->stAvSettings.stSyncParams, &pstSettings->stSyncParams, sizeof(AV_SYNC_PARAM_S));

    /* 4. save err recovery parameter */
    pstAvInfo->stAvSettings.enErrRecoveryMode = pstSettings->enErrRecoveryMode;

    /* 5. save stop mode */
    if (pstSettings->enVidStopMode < AV_VID_STOP_MODE_BUTT)
    {
        pstAvInfo->stAvSettings.enVidStopMode = pstSettings->enVidStopMode;
    }

    /* 6. save 3D format mode */
    pstAvInfo->stAvSettings.en3dFormat = pstSettings->en3dFormat;

    /* 7. save play speed */
    pstAvInfo->stAvSettings.s32Speed = pstSettings->s32Speed;
#ifdef HAL_HISI_EXTEND_H
    /* 8. save decoder mode */
    pstAvInfo->stAvSettings.eDecMode = pstSettings->eDecMode;

    /* 9. save tvp enable flag */
    pstAvInfo->stAvSettings.bEnableTVP = pstSettings->bEnableTVP;
    pstAvInfo->stAvSettings.bEnableAudSecurity = pstSettings->bEnableAudSecurity;
#endif

    /* 10. set video rotation */
    if (pstSettings->enVideoRotation != pstAvInfo->stAvSettings.enVideoRotation)
    {
        pstAvInfo->stAvSettings.enVideoRotation = pstSettings->enVideoRotation;

        if (AV_INVALID_HANDLE != pstAvInfo->hWindowSdk)
        {
            s32Ret = AV_SDK_SetRotation(pstAvInfo->hAvPlayerSdk, pstSettings->enVideoRotation);
            HAL_CHK_PRINTF((SUCCESS != s32Ret), "set video rotation fail");
        }
    }

    /* 11. save pid info */
    pstAvInfo->stAvSettings.u16AudPid = pstSettings->u16AudPid;
    pstAvInfo->stAvSettings.u16VidPid = pstSettings->u16VidPid;
    pstAvInfo->stAvSettings.u16PcrPid = pstSettings->u16PcrPid;

    /* 12. save sync offset info */
    pstAvInfo->stAvSettings.s32AudSyncOffseMs = pstSettings->s32AudSyncOffseMs;
    pstAvInfo->stAvSettings.s32VidSyncOffseMs = pstSettings->s32VidSyncOffseMs;

    if (AV_SYNC_MODE_BUTT > pstSettings->enAvSyncMode)
    {
        pstAvInfo->stAvSettings.enAvSyncMode = pstSettings->enAvSyncMode;
    }

#ifdef HAL_HISI_EXTEND_H
    /* 13. save low delay config */
    HAL_MEMCPY_NO_VERIFY(&pstAvInfo->stAvSettings.stLowDelayCfg, &pstSettings->stLowDelayCfg, sizeof(AV_LOW_DELAY_S));

    /* 14. save HDR info */
    if (0 != HAL_MEMCMP(&pstAvInfo->stAvSettings.stHdrParams, &pstSettings->stHdrParams, sizeof(AV_HDR_PARAM_S)))
    {
        HAL_MEMCPY_NO_VERIFY(&pstAvInfo->stAvSettings.stHdrParams, &pstSettings->stHdrParams, sizeof(AV_HDR_PARAM_S));
        HAL_DEBUG("set hdr type = %d", pstAvInfo->stAvSettings.stHdrParams.enHdrType);
    }
 #endif


    AV_HANDLE_UnLock();

    s32Ret = AV_SDK_SetAttr(hAvPlaySdk, &stAvSettingInfo, pstDoblyDecOpenConfig, pstSettings);

    /* 12. set EOS */
    if (pstSettings->bEos)
    {
        (VOID)HI_UNF_AVPLAY_FlushStream(hAvPlaySdk, NULL);
    }

    // TODO:
    /*
     1. if ts mode, we should open channel in here, then set the attribute.
     2. if es mode, should attach audio and video injecters first, then set the attribute.
     */

    return s32Ret;
}

static S32 av_start(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    S32 s32VidRet = SUCCESS, s32AudRet = SUCCESS;

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    s32VidRet = av_start_video(pstDev, hAvHandle);
    s32AudRet = av_start_audio(pstDev, hAvHandle);

    HAL_CHK_RETURN((SUCCESS != s32VidRet && SUCCESS != s32AudRet),
                   ERROR_AV_VID_AND_AUD_START_FAIL, "audio and video start fail");
    HAL_CHK_RETURN((SUCCESS != s32VidRet), ERROR_AV_VID_START_FAIL, "video start fail");
    HAL_CHK_RETURN((SUCCESS != s32AudRet), ERROR_AV_AUD_START_FAIL, "audio start fail");

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_stop(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    S32 s32Ret = SUCCESS;

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    s32Ret = av_stop_video(pstDev, hAvHandle);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "av video stop fail!");

    s32Ret = av_stop_audio(pstDev, hAvHandle);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "av audio stop fail!");

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_pause(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfo;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    HAL_MEMSET_NO_VERIFY(&stStatusInfo, 0, sizeof(stStatusInfo));
    s32Ret = HI_UNF_AVPLAY_GetStatusInfo(hAvHandle, &stStatusInfo);

    if (SUCCESS == s32Ret && HI_UNF_AVPLAY_STATUS_PAUSE == stStatusInfo.enRunStatus)
    {
        return SUCCESS;
    }

    s32Ret = HI_UNF_AVPLAY_Pause(hAvHandle, NULL);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "pase sdk avplay fail, s32Ret(0x%08x)", s32Ret);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

VOID AV_SDK_GetErrorCover(AV_ERROR_RECOVERY_MODE_E eErrCovery, U32 *pu32ErrRecovery)
{
    switch (eErrCovery)
    {
        case AV_ERROR_RECOVERY_MODE_FULL:
            *pu32ErrRecovery = 0;
            break;

        case AV_ERROR_RECOVERY_MODE_HIGH:
            *pu32ErrRecovery = 25;
            break;

        case AV_ERROR_RECOVERY_MODE_PARTIAL:
            *pu32ErrRecovery = 50;
            break;

        case AV_ERROR_RECOVERY_MODE_NONE:
            *pu32ErrRecovery = 100;
            break;
        default:
            HAL_ERROR("AV_SDK_GetErrorCover eErrCovery is invalid\n");
            *pu32ErrRecovery = 0;
            break;
    }
}

static S32 av_resume(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    S32 s32Ret = SUCCESS;
    U32 u32AvIdx = AV_HAL_INVALID_IDX;
    U32 u32ErrRecovery = 0;
    AV_HAL_INFO_S* pstAvInfo = NULL;
    HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfo;
    HI_UNF_VCODEC_ATTR_S stVdecAdvAttr;
    HANDLE hAvPlayerSdk = AV_INVALID_HANDLE;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    //HAL_CHK_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, "parameter is NULL.");

    AV_HANDLE_Lock();

    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    if (AV_NORMAL_PLAY_SPEED != pstAvInfo->stAvSettings.s32Speed)
    {
        pstAvInfo->stAvSettings.s32Speed = AV_NORMAL_PLAY_SPEED;
    }

    if (AV_VDEC_MODE_NORMAL != pstAvInfo->stAvSettings.eDecMode)
    {
        pstAvInfo->stAvSettings.eDecMode = AV_VDEC_MODE_NORMAL;
    }

    AV_HANDLE_UnLock();

    s32Ret = av_get_sdk_avplay_hdl(hAvHandle, &hAvPlayerSdk);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "get sdk avplay handle fail");

    HAL_MEMSET_NO_VERIFY(&stStatusInfo, 0, sizeof(stStatusInfo));
    s32Ret = HI_UNF_AVPLAY_GetStatusInfo(hAvPlayerSdk, &stStatusInfo);

    if (SUCCESS == s32Ret && HI_UNF_AVPLAY_STATUS_PLAY == stStatusInfo.enRunStatus)
    {
        return SUCCESS;
    }

    s32Ret = HI_UNF_AVPLAY_Resume(hAvPlayerSdk, NULL);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "resume sdk avplay fail, s32Ret(0x%08x)", s32Ret);

    AV_SDK_GetErrorCover(pstAvInfo->stAvSettings.enErrRecoveryMode, &u32ErrRecovery);

    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_VDEC, (HI_VOID*)&stVdecAdvAttr);
    HAL_CHK_PRINTF(HI_SUCCESS != s32Ret, "get vdec adv attr fail");

    if (HI_SUCCESS == s32Ret)
    {
        stVdecAdvAttr.bOrderOutput = HI_FALSE;
        stVdecAdvAttr.u32ErrCover  = u32ErrRecovery;
        (HI_VOID)HI_UNF_AVPLAY_SetAttr(hAvPlayerSdk, HI_UNF_AVPLAY_ATTR_ID_VDEC, (HI_VOID*)&stVdecAdvAttr);
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_reset(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, S64 s64TimeMs)
{
    S32 s32Ret = SUCCESS;

    HI_UNF_AVPLAY_RESET_OPT_S stResetOpt;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    //HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "get sdk avplay handle fail");

    stResetOpt.u32SeekPtsMs = (U32)s64TimeMs;

    if (s64TimeMs != AV_INVALID_PTS)
    {
        s32Ret = HI_UNF_AVPLAY_Reset(hAvHandle, &stResetOpt);
    }
    else
    {
        s32Ret = HI_UNF_AVPLAY_Reset(hAvHandle, NULL);
    }

    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "reset sdk avplay fail, s32Ret(0x%08x)", s32Ret);
    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_start_video(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    S32 s32Ret          = SUCCESS;
    U32 u32AvIdx        = AV_HAL_INVALID_IDX;
    U32 u32ErrRecovery  = 0;
    HANDLE hWindow      = AV_INVALID_HANDLE;
    HANDLE hAvPlayerSdk = AV_INVALID_HANDLE;
    AV_VID_STREAM_TYPE_E eVidStreamType = AV_VID_STREAM_TYPE_BUTT;
    AV_VDEC_PARAM_S      stVdecParams;
    AV_VID_ROTATION_E    eRotation = AV_VID_ROTATION_0;

#ifdef HAL_HISI_EXTEND_H
    AV_LOW_DELAY_S       stLowDelayCfg;
#endif

    AV_ERROR_RECOVERY_MODE_E eErrCovery = AV_ERROR_RECOVERY_MODE_FULL;

    AV_HAL_INFO_S* pstAvInfo = NULL;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_MEMSET_NO_VERIFY(&stVdecParams, 0, sizeof(AV_VDEC_PARAM_S));

#ifdef HAL_HISI_EXTEND_H
    HAL_MEMSET_NO_VERIFY(&stLowDelayCfg, 0, sizeof(AV_LOW_DELAY_S));
#endif

    AV_HANDLE_Lock();
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);

    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    HAL_CHK_CALL_RETURN((TRUE == pstAvInfo->bVidStart), SUCCESS,
                        AV_HANDLE_UnLock(),
                        "video already start");

    hAvPlayerSdk    = pstAvInfo->hAvPlayerSdk;
    eVidStreamType  = pstAvInfo->stAvSettings.enVidStreamType;
    eRotation       = pstAvInfo->stAvSettings.enVideoRotation;
    eErrCovery      = pstAvInfo->stAvSettings.enErrRecoveryMode;
    HAL_MEMCPY_NO_VERIFY(&stVdecParams, &pstAvInfo->stAvSettings.stVdecParams, sizeof(stVdecParams));

#ifdef HAL_HISI_EXTEND_H
    HAL_MEMCPY_NO_VERIFY(&stLowDelayCfg, &pstAvInfo->stAvSettings.stLowDelayCfg, sizeof(stLowDelayCfg));
#endif

    AV_HANDLE_UnLock();

    s32Ret = HI_MPI_AVPLAY_GetWindowHandle(hAvPlayerSdk, &hWindow);

    if (SUCCESS != s32Ret)
    {
        hWindow = AV_INVALID_HANDLE;
    }

    s32Ret = AV_SDK_SetVDecAttr(hAvPlayerSdk, eVidStreamType, &stVdecParams);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AV_VID_START_FAIL, "set video decoder attr fail, s32Ret(0x%08x)", s32Ret);

    /* set video decoder error covery, should set after inject attached */
    AV_SDK_GetErrorCover(eErrCovery, &u32ErrRecovery);
    s32Ret = AV_SDK_SetErroCovery(hAvPlayerSdk, u32ErrRecovery);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "set error covery fail.");

#ifdef HAL_HISI_EXTEND_H
    s32Ret = AV_SDK_SetLowDelay(hAvPlayerSdk, &stLowDelayCfg);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "set low delay config fail");
#endif

    s32Ret = AV_SDK_SetRotation(hAvPlayerSdk, eRotation);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "set video rotation fail");

    s32Ret = HI_UNF_AVPLAY_Start(hAvPlayerSdk, HI_UNF_AVPLAY_MEDIA_CHAN_VID, NULL);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AV_VID_START_FAIL, "start sdk avplay vid channel fail, s32Ret(0x%08x)", s32Ret);

    AV_HANDLE_Lock();
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), FAILURE,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);

    pstAvInfo->bVidStart    = TRUE;
    pstAvInfo->hWindowSdk   = hWindow;
    AV_HANDLE_UnLock();

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_pause_video(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    return ERROR_NOT_SUPPORTED;
}

static S32 av_freeze_video(AV_DEVICE_S* pstDev, const HANDLE hAvHandle, BOOL bFreeze)
{
    // TODO: this function support in vout module
    /* vout already support this function, should not support in av module */
    return ERROR_NOT_SUPPORTED;
}

static S32 av_resume_video(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    return ERROR_NOT_SUPPORTED;
}

static S32 av_stop_video(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    S32 s32Ret = SUCCESS;
    U32 u32AvIdx = AV_HAL_INVALID_IDX;
    AV_HAL_INFO_S* pstAvInfo = NULL;
    HI_UNF_AVPLAY_STOP_OPT_S    stStopOpt;
    HANDLE                      hAvPlayerSdk = AV_INVALID_HANDLE;
    AV_VID_STOP_MODE_E          enVidStopMode = AV_VID_STOP_MODE_BLACK;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    AV_HANDLE_Lock();
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    if (AV_NORMAL_PLAY_SPEED != pstAvInfo->stAvSettings.s32Speed)
    {
        pstAvInfo->stAvSettings.s32Speed = AV_NORMAL_PLAY_SPEED;
    }

    HAL_CHK_CALL_RETURN((FALSE == pstAvInfo->bVidStart), SUCCESS,
                        AV_HANDLE_UnLock(),
                        "video already stop");

    hAvPlayerSdk  = pstAvInfo->hAvPlayerSdk;
    enVidStopMode = pstAvInfo->stAvSettings.enVidStopMode;
    AV_HANDLE_UnLock();

    HAL_MEMSET_NO_VERIFY(&stStopOpt, 0, sizeof(stStopOpt));
    stStopOpt.u32TimeoutMs = 0;

    if (AV_VID_STOP_MODE_FREEZE == enVidStopMode)
    {
        stStopOpt.enMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
    }
    else
    {
        // TODO: need clear window at here?
        stStopOpt.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;
    }

    s32Ret = HI_UNF_AVPLAY_Stop(hAvPlayerSdk,
                                HI_UNF_AVPLAY_MEDIA_CHAN_VID,
                                &stStopOpt);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "stop sdk vid channel error, s32Ret(0x%08x)", s32Ret);

    AV_HANDLE_Lock();
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), FAILURE,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);

    pstAvInfo->bVidStart = FALSE;
    AV_HANDLE_UnLock();

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_clear_video(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    S32 s32Ret = SUCCESS;
    U32 u32AvIdx = AV_HAL_INVALID_IDX;
    AV_HAL_INFO_S* pstAvInfo = NULL;
    HI_UNF_AVPLAY_STOP_OPT_S stStopOpt;
    HI_UNF_AVPLAY_STATUS_INFO_S stStatusInfo;
    HANDLE hAvPlayerSdk = AV_INVALID_HANDLE;
    BOOL   bVidStart = TRUE;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    AV_HANDLE_Lock();
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    hAvPlayerSdk = pstAvInfo->hAvPlayerSdk;
    bVidStart    = pstAvInfo->bVidStart;
    AV_HANDLE_UnLock();

    /* if not start, we call reset function to clear audio and video es buffer data */
    if (FALSE == bVidStart)
    {
        (VOID)HI_UNF_AVPLAY_Reset(hAvPlayerSdk, NULL);
        return SUCCESS;
    }

    HAL_MEMSET_NO_VERIFY(&stStatusInfo, 0, sizeof(stStatusInfo));
    s32Ret = HI_UNF_AVPLAY_GetStatusInfo(hAvPlayerSdk, &stStatusInfo);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get sdk avplay status fail");

    HAL_MEMSET_NO_VERIFY(&stStopOpt, 0, sizeof(stStopOpt));
    stStopOpt.u32TimeoutMs = 0;
    stStopOpt.enMode = HI_UNF_AVPLAY_STOP_MODE_BLACK;

    /* if in play status, clear  */
    s32Ret = HI_UNF_AVPLAY_Stop(hAvPlayerSdk,
                                HI_UNF_AVPLAY_MEDIA_CHAN_VID,
                                &stStopOpt);
    s32Ret |= HI_UNF_AVPLAY_Start(hAvPlayerSdk,
                                  HI_UNF_AVPLAY_MEDIA_CHAN_VID,
                                  NULL);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "clear av video fail!");

    /* if it is pause status before clear video, return to pause status */
    if (HI_UNF_AVPLAY_STATUS_PAUSE == stStatusInfo.enRunStatus)
    {
        (VOID)HI_UNF_AVPLAY_Pause(hAvPlayerSdk, NULL);
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_start_audio(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    S32 s32Ret    = SUCCESS;
    U32 u32AvIdx  = AV_HAL_INVALID_IDX;
    HANDLE hAvPlayerSdk = AV_INVALID_HANDLE;

    AV_HAL_INFO_S* pstAvInfo = NULL;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    AV_HANDLE_Lock();

    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    HAL_CHK_CALL_RETURN((TRUE == pstAvInfo->bAudStart), SUCCESS,
                        AV_HANDLE_UnLock(),
                        "audio already start");

    hAvPlayerSdk = pstAvInfo->hAvPlayerSdk;
    AV_HANDLE_UnLock();

    s32Ret = HI_UNF_AVPLAY_Start(hAvPlayerSdk,
                                 HI_UNF_AVPLAY_MEDIA_CHAN_AUD,
                                 NULL);

    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AV_AUD_START_FAIL,
                   "start sdk avplay aud channel fail, s32Ret(0x%08x)", s32Ret);

    AV_HANDLE_Lock();
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), FAILURE,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);

    pstAvInfo->bAudStart = TRUE;
    AV_HANDLE_UnLock();

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_pause_audio(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    return ERROR_NOT_SUPPORTED;
}

static S32 av_resume_audio(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    return ERROR_NOT_SUPPORTED;
}

static S32 av_stop_audio(AV_DEVICE_S* pstDev, const HANDLE hAvHandle)
{
    S32 s32Ret = SUCCESS;
    U32 u32AvIdx = AV_HAL_INVALID_IDX;
    AV_HAL_INFO_S* pstAvInfo = NULL;
    HANDLE hAvPlayerSdk = AV_INVALID_HANDLE;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    AV_HANDLE_Lock();
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);
    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    HAL_CHK_CALL_RETURN((FALSE == pstAvInfo->bAudStart), SUCCESS,
                        AV_HANDLE_UnLock(),
                        "audio already stop");

    hAvPlayerSdk = pstAvInfo->hAvPlayerSdk;
    AV_HANDLE_UnLock();

    s32Ret = HI_UNF_AVPLAY_Stop(hAvPlayerSdk, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "stop sdk aud channel error, s32Ret(0x%08x)", s32Ret);

    AV_HANDLE_Lock();
    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), FAILURE,
                        AV_HANDLE_UnLock(),
                        "av player handle:0x%x not found!", hAvHandle);

    pstAvInfo->bAudStart = FALSE;
    AV_HANDLE_UnLock();

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_decode_iframe(AV_DEVICE_S* pstDev,
                            const HANDLE hAvHandle,
                            const AV_IFRAME_DECODE_PARAMS_S* const pstIframeDacodeParams,
                            AV_VID_FRAMEINFO_S* pstCapPicture)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_AVPLAY_I_FRAME_S   stIframeParam;
    HI_UNF_VIDEO_FRAME_INFO_S stVideoFrame, *pstVideoFrame = NULL;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    HAL_CHK_RETURN((NULL == pstIframeDacodeParams || NULL == pstCapPicture), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((NULL == pstIframeDacodeParams->stIframeParams.pvIframeData), ERROR_INVALID_PARAM, "parameter is invalid.");
    HAL_CHK_RETURN((AV_VID_STREAM_TYPE_BUTT == pstIframeDacodeParams->stIframeParams.enType), ERROR_INVALID_PARAM, "parameter is invalid.");

    HAL_MEMSET_NO_VERIFY(&stIframeParam, 0, sizeof(stIframeParam));
    HAL_MEMSET_NO_VERIFY(&stVideoFrame, 0, sizeof(stVideoFrame));

    AV_HAL_VidCodecToSdk(pstIframeDacodeParams->stIframeParams.enType, &stIframeParam.enType);
    stIframeParam.pu8Addr    = (U8*)pstIframeDacodeParams->stIframeParams.pvIframeData;
    stIframeParam.u32BufSize = pstIframeDacodeParams->stIframeParams.u32DataLength;

    s32Ret = HI_UNF_AVPLAY_DecodeIFrame(hAvHandle, &stIframeParam, &stVideoFrame);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "sdk av decode i frame error, s32Ret(0x%08x)", s32Ret);

    pstVideoFrame = &stVideoFrame;
    AV_SDK_VidFrameInfoToHal(pstVideoFrame, pstCapPicture);

    return SUCCESS;
}

static S32 av_release_iframe(struct _AV_DEVICE_S* pstDev,
                             const HANDLE hAvHandle,
                             const AV_VID_FRAMEINFO_S* pstCapPicture)
{
    S32 s32Ret = SUCCESS;

    HI_UNF_VIDEO_FRAME_INFO_S stVideoFrame;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    HAL_CHK_RETURN((NULL == pstCapPicture), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((AV_VID_FIELD_BUTT <= pstCapPicture->enFieldMode ||
                    AV_3D_FORMAT_BUTT <= pstCapPicture->enFramePackingType ||
                    AV_VID_FORMAT_YUV_BUTT <= pstCapPicture->enVideoFormat), ERROR_INVALID_PARAM, "parameter is invalid.");

    HAL_MEMSET_NO_VERIFY(&stVideoFrame, 0, sizeof(stVideoFrame));
    AV_HAL_VidFrameInfoToSdk((AV_VID_FRAMEINFO_S*)pstCapPicture, &stVideoFrame);

    s32Ret = HI_UNF_AVPLAY_ReleaseIFrame(hAvHandle, &stVideoFrame);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "sdk av release i frame error, s32Ret(0x%08x)", s32Ret);

    return SUCCESS;
}

#ifdef HAL_HISI_EXTEND_H
static S32 av_acquire_frame(struct _AV_DEVICE_S* pstDev,
                            const HANDLE hHandle,
                            AV_CONTENT_TYPE_E eFrameType,
                            VOID* pFrame,
                            U32 u32TimeoutMs)
{
    S32 s32Ret        = SUCCESS;
    HI_UNF_VIDEO_FRAME_INFO_S stSdkVidFrameInfo;
    HI_UNF_AO_FRAMEINFO_S     stSdkAudFrameInfo;

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pFrame), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    if (AV_CONTENT_VIDEO == eFrameType)
    {
        AV_VID_FRAMEINFO_S* pstVidFrameInfo = (AV_VID_FRAMEINFO_S*)pFrame;

        HAL_MEMSET_NO_VERIFY(&stSdkVidFrameInfo, 0, sizeof(stSdkVidFrameInfo));
        s32Ret = HI_UNF_VO_AcquireFrame(hHandle, &stSdkVidFrameInfo, u32TimeoutMs);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "acquire video frame fail");

        AV_SDK_VidFrameInfoToHal(&stSdkVidFrameInfo, pstVidFrameInfo);
    }
    else if (AV_CONTENT_AUDIO == eFrameType)
    {
        AV_AUD_FRAMEINFO_S* pstAudFrameInfo = (AV_AUD_FRAMEINFO_S*)pFrame;

        HAL_MEMSET_NO_VERIFY(&stSdkAudFrameInfo, 0, sizeof(stSdkAudFrameInfo));
        s32Ret = HI_UNF_SND_AcquireTrackFrame(hHandle, &stSdkAudFrameInfo, u32TimeoutMs);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "acquire audio frame fail");

        AV_SDK_AudFrameInfoToHal(&stSdkAudFrameInfo, pstAudFrameInfo);
    }
    else
    {
        return ERROR_INVALID_PARAM;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_release_frame(struct _AV_DEVICE_S* pstDev,
                            const HANDLE hHandle,
                            AV_CONTENT_TYPE_E eFrameType,
                            const VOID* pFrame)
{
    S32 s32Ret        = SUCCESS;
    HI_UNF_VIDEO_FRAME_INFO_S stSdkVidFrameInfo;
    HI_UNF_AO_FRAMEINFO_S     stSdkAudFrameInfo;

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pFrame), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    if (AV_CONTENT_VIDEO == eFrameType)
    {
        AV_VID_FRAMEINFO_S* pstVidFrameInfo = (AV_VID_FRAMEINFO_S*)pFrame;

        HAL_MEMSET_NO_VERIFY(&stSdkVidFrameInfo, 0, sizeof(stSdkVidFrameInfo));
        AV_HAL_VidFrameInfoToSdk(pstVidFrameInfo, &stSdkVidFrameInfo);

        s32Ret = HI_UNF_VO_ReleaseFrame(hHandle, &stSdkVidFrameInfo);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "release video frame fail");
    }
    else if (AV_CONTENT_AUDIO == eFrameType)
    {
        AV_AUD_FRAMEINFO_S* pstAudFrameInfo = (AV_AUD_FRAMEINFO_S*)pFrame;

        HAL_MEMSET_NO_VERIFY(&stSdkAudFrameInfo, 0, sizeof(stSdkAudFrameInfo));
        AV_HAL_AudFrameInfoToSdk(pstAudFrameInfo, &stSdkAudFrameInfo);

        s32Ret = HI_UNF_SND_ReleaseTrackFrame(hHandle, &stSdkAudFrameInfo);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "release audio frame fail");
    }
    else
    {
        return ERROR_INVALID_PARAM;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

extern HI_S32 HI_MPI_WIN_CalMediaRect(HI_CHIP_TYPE_E enChipType,
                                      HI_RECT_S stStreamRect,
                                      HI_RECT_S* pstMediaRect);

static S32 av_format_change(struct _AV_DEVICE_S* pstDev,
                            const HANDLE hAvHandle,
                            U32* pu32Width,
                            U32* pu32Height,
                            BOOL* pbVideoBypass)
{
    S32                     s32Ret = SUCCESS;
    HANDLE                  hVdec, hSync;
    HI_SYS_VERSION_S        stVersion;
    VDEC_RESOLUTION_ATTR_S  stResolution;
    HI_RECT_S               stOrigRect, stFinalRect;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    HAL_CHK_RETURN((NULL == pu32Width || NULL == pu32Height || NULL == pbVideoBypass), ERROR_NULL_PTR, "parameter is NULL.");

    stVersion.enChipTypeHardWare = HI_CHIP_TYPE_BUTT;
    s32Ret = HI_SYS_GetVersion(&stVersion);

    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    s32Ret = HI_MPI_AVPLAY_GetSyncVdecHandle(hAvHandle, &hVdec, &hSync);

    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    HAL_MEMSET_NO_VERIFY(&stOrigRect, 0, sizeof(stOrigRect));
    HAL_MEMSET_NO_VERIFY(&stFinalRect, 0, sizeof(stFinalRect));
    stOrigRect.s32Width     = *pu32Width;
    stOrigRect.s32Height    = *pu32Height;
    s32Ret = HI_MPI_WIN_CalMediaRect(stVersion.enChipTypeHardWare, stOrigRect, &stFinalRect);

    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    *pu32Width = stFinalRect.s32Width;
    *pu32Height = stFinalRect.s32Height;
    if (stFinalRect.s32Width != stOrigRect.s32Width && stFinalRect.s32Height != stOrigRect.s32Height)
    {
        stResolution.s32Width = stFinalRect.s32Width;
        stResolution.s32Height = stFinalRect.s32Height;
        s32Ret = HI_MPI_VDEC_SetResolution(hVdec, &stResolution);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "set vdec Resolution failed");
    }

    (VOID)HI_MPI_VDEC_GetVideoBypass(hVdec, (HI_BOOL*)pbVideoBypass);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

extern HI_S32 HI_MPI_SYNC_VidJudge(HI_HANDLE hSync, SYNC_VID_INFO_S* pVidInfo, SYNC_VID_OPT_S* pVidOpt);
extern HI_S32 HI_MPI_SYNC_GetStatus(HI_HANDLE hSync, HI_UNF_SYNC_STATUS_S* pSyncStatus);

static S32 av_sync_frame(AV_DEVICE_S* pstDev,
                         const HANDLE hAvHandle,
                         const VOID* pvFrame,
                         const AV_SYNC_REF_S* pstSyncRef,
                         AV_SYNC_INFO_S* pstSyncInfo)
{
    S32                         s32Ret = SUCCESS;
    HANDLE                      hVdec, hSync;
    U32                         u32DispCount = 1;
    HI_UNF_VIDEO_FRAME_INFO_S*  pstVidFrame = NULL;
    SYNC_VID_INFO_S             stVidInfo;
    SYNC_VID_OPT_S              stVidOpt;
    HI_UNF_SYNC_STATUS_S        stSync;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    HAL_CHK_RETURN((NULL == pstSyncRef), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((NULL == pstSyncInfo), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((AV_SYNC_PROC_BUTT <= pstSyncInfo->enSyncProc), ERROR_INVALID_PARAM, "parameter is invalid.");

    if (NULL != pvFrame && !pstSyncRef->bFreeRun)
    {
        pstVidFrame = (HI_UNF_VIDEO_FRAME_INFO_S*)pvFrame;
        s32Ret = HI_MPI_AVPLAY_CalculateFRC(hAvHandle,
                                            pstVidFrame, pstSyncRef->u32FreshRate, (HI_S32*)&u32DispCount);
        if (SUCCESS != s32Ret)
        {
            return FAILURE;
        }
    }

    HAL_MEMSET_NO_VERIFY(&stVidInfo, 0, sizeof(SYNC_VID_INFO_S));
    stVidInfo.bProgressive  = (HI_BOOL)pstSyncRef->bProgressive;
    stVidInfo.SrcPts        = (U32)pstSyncRef->s64SrcPts;
    stVidInfo.Pts           = (U32)pstSyncRef->s64Pts;
    stVidInfo.FrameTime     = pstSyncRef->u32FpsInteger ?
                              (1000000 / (pstSyncRef->u32FpsInteger * 1000 + pstSyncRef->u32FpsDecimal))
                              : 40;
    stVidInfo.DispTime      = u32DispCount;
    stVidInfo.DispRate      = pstSyncRef->u32FpsInteger * 100;
    stVidInfo.DelayTime     = pstSyncRef->u32DelayTime;

    s32Ret = HI_MPI_AVPLAY_GetSyncVdecHandle(hAvHandle, &hVdec, &hSync);

    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    HAL_MEMSET_NO_VERIFY(&stVidOpt, 0, sizeof(SYNC_VID_OPT_S));
    stVidOpt.SyncProc = SYNC_PROC_DISCARD;
    s32Ret = HI_MPI_SYNC_VidJudge(hSync, &stVidInfo, &stVidOpt);

    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    pstSyncInfo->enSyncProc = (AV_SYNC_PROC_E)stVidOpt.SyncProc;
    pstSyncInfo->u32DispCount = u32DispCount;
    pstSyncInfo->u32RepeatTime = 0;

    stVidInfo.FrameTime = stVidInfo.FrameTime > 200 ? 200 : stVidInfo.FrameTime;
    HAL_MEMSET_NO_VERIFY(&stSync, 0, sizeof(HI_UNF_SYNC_STATUS_S));
    s32Ret = HI_MPI_SYNC_GetStatus(hSync, &stSync);

    if (SUCCESS == s32Ret && stSync.s32DiffAvPlayTime > 0)
    {
        pstSyncInfo->u32RepeatTime = stSync.s32DiffAvPlayTime > 100 ? stVidInfo.FrameTime
                                     : (HI_U32)stSync.s32DiffAvPlayTime;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_set_buf_mode(AV_DEVICE_S* pstDev,
                           const HANDLE hAvHandle,
                           AV_FRAME_BUFFER_MODE_E eBufMode)
{
    S32                         s32Ret = SUCCESS;
    HANDLE                      hVdec, hSync;

    VDEC_RESOLUTION_ATTR_S      stResolution;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    HAL_CHK_RETURN((AV_VID_FRAME_BUF_BUTT <= eBufMode), ERROR_INVALID_PARAM, "parameter is invalid.");

    if (AV_VID_FRAME_BUF_ALLOC_BY_USER == eBufMode)
    {
        s32Ret = HI_MPI_AVPLAY_GetSyncVdecHandle(hAvHandle, &hVdec, &hSync);

        if (SUCCESS != s32Ret)
        {
            return FAILURE;
        }

        s32Ret = HI_MPI_VDEC_SetChanBufferMode(hVdec, VDEC_BUF_USER_ALLOC_MANAGE);
        HAL_DEBUG("Set vdec to user mode, result code = 0x%08x!\n", s32Ret);

        stResolution.s32Width = 0;
        stResolution.s32Height = 0;
        s32Ret = HI_MPI_VDEC_SetResolution(hVdec, &stResolution);
        HAL_DEBUG("Set vdec resolution, result code = 0x%08x!\n", s32Ret);
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_acquire_user_buf(AV_DEVICE_S* pstDev,
                               const HANDLE hAvHandle,
                               AV_USER_BUFFER_S* pstBuf,
                               U32 u32Cnt)
{
    S32                         s32Ret = SUCCESS;

    HI_MPI_EXT_BUFFER_S         stMpiBuf;
    U32                         i = 0;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");
    HAL_CHK_RETURN((NULL == pstBuf), ERROR_NULL_PTR, "parameter is NULL.");

    if (u32Cnt >= HI_MPI_MAX_BUF_NUM)
    {
        HAL_ERROR("invalid user buffer number:%d", u32Cnt);
        return ERROR_INVALID_PARAM;
    }

    HAL_MEMSET_NO_VERIFY(&stMpiBuf, 0, sizeof(stMpiBuf));
    stMpiBuf.u32BufCnt              = u32Cnt;
    stMpiBuf.u32Stride              = pstBuf[0].u32Stride;
    stMpiBuf.u32FrameBufSize        = pstBuf[0].u32FrameBufSize;
    stMpiBuf.u32MetadataBufSize     = pstBuf[0].u32MetadataBufSize;
    stMpiBuf.u32PrivMetadataOffset  = pstBuf[0].u32PrivMetadataOffset;
    stMpiBuf.bVideoBypass           = pstBuf[0].bVideoBypass;

    for (i = 0; i < u32Cnt; i++)
    {
        stMpiBuf.au32FrameBuffer[i]    = pstBuf[i].u32FrameBuf;
        stMpiBuf.as32FrameBufFd[i]     = pstBuf[i].s32FrameBufFd;
        stMpiBuf.au32MetadataBuf[i]    = pstBuf[i].u32MetadataBuf;
        stMpiBuf.as32MetadataBufFd[i]  = pstBuf[i].s32MetadataBufFd;
    }

    s32Ret = HI_MPI_AVPLAY_UseExternalBuffer(hAvHandle, &stMpiBuf);
    HAL_DEBUG("Av use external buffer, result code = 0x%08x", s32Ret);

    HAL_DEBUG_EXIT();

    return s32Ret;
}

static S32 av_release_user_buf(AV_DEVICE_S* pstDev,
                               const HANDLE hAvHandle,
                               AV_USER_BUFFER_S* pstBuf,
                               U32 u32Cnt)
{
    S32                         s32Ret = SUCCESS;
    HI_MPI_EXT_BUFFER_S         stMpiBuf;
    U32                         i = 0;
    //AV_HAL_INFO_S*              pstAvInfo = (AV_HAL_INFO_S*)hAvHandle;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");
    HAL_CHK_RETURN((NULL == pstBuf), ERROR_NULL_PTR, "parameter is NULL.");

    if (u32Cnt >= HI_MPI_MAX_BUF_NUM)
    {
        HAL_ERROR("invalid user buffer number:%d", u32Cnt);
        return ERROR_INVALID_PARAM;
    }

    HAL_MEMSET_NO_VERIFY(&stMpiBuf, 0, sizeof(stMpiBuf));
    stMpiBuf.u32BufCnt          = u32Cnt;
    stMpiBuf.u32Stride          = pstBuf[0].u32Stride;
    stMpiBuf.u32MetadataBufSize = pstBuf[0].u32MetadataBufSize;
    stMpiBuf.u32FrameBufSize    = pstBuf[0].u32FrameBufSize;

    for (i = 0; i < u32Cnt; i++)
    {
        stMpiBuf.au32FrameBuffer[i]    = pstBuf[i].u32FrameBuf;
        stMpiBuf.as32FrameBufFd[i]     = pstBuf[i].s32FrameBufFd;
        stMpiBuf.au32MetadataBuf[i]    = pstBuf[i].u32MetadataBuf;
        stMpiBuf.as32MetadataBufFd[i]  = pstBuf[i].s32MetadataBufFd;
    }

    s32Ret = HI_MPI_AVPLAY_DeleteExternalBuffer(hAvHandle, &stMpiBuf);
    HAL_DEBUG("Av recycle user buffer, result code = 0x%08x", s32Ret);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}
#endif

static S32 av_injecter_open(AV_DEVICE_S* pstDev,
                            HANDLE* const  phInjecter,
                            AV_INJECTER_OPEN_PARAMS_S* const pstOpenParams)
{
    S32 s32Ret = SUCCESS;
    U32 u32Idx = AV_INJECT_INVALID_IDX;
    BOOL bSupportInject = FALSE;
    AV_INJECT_INFO_S* pstInjectInfo = NULL;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((NULL == pstOpenParams), ERROR_NULL_PTR, "parameter is NULL.");

    bSupportInject = AV_SDK_IsSupportInject(pstOpenParams->stSettings.enDataType,
                                            pstOpenParams->stSettings.enInjectContent);

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == phInjecter), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((FALSE == bSupportInject), ERROR_INVALID_PARAM, "not support data type.");

    AV_HANDLE_Lock();
    u32Idx = AV_MALLOC_INJECT_Index(AV_INVALID_HANDLE);
    HAL_CHK_CALL_RETURN((AV_INJECT_MAX_COUNT <= u32Idx), FAILURE, AV_HANDLE_UnLock(),
                        "create too many injecters!");

    pstInjectInfo = (AV_INJECT_INFO_S*)AV_MALLOCZ(sizeof(AV_INJECT_INFO_S));

    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NO_MEMORY, AV_HANDLE_UnLock(),
                        "malloc inject handle fail.");

    pstInjectInfo->enAvChanType = HI_UNF_AVPLAY_MEDIA_CHAN_BUTT;
    pstInjectInfo->hAvHal       = AV_INVALID_HANDLE;
    HAL_MEMCPY(&pstInjectInfo->stInjectSettings, &pstOpenParams->stSettings, sizeof(AV_INJECT_SETTINGS_S));


    *phInjecter = ((AV_INJECT_MODE_ID << 16) | u32Idx);

    s_stInjectHandleInfo[u32Idx].bUsed   = TRUE;
    s_stInjectHandleInfo[u32Idx].pstInjecterInfo = pstInjectInfo;
    s_stInjectHandleInfo[u32Idx].hInject = *phInjecter;

    HAL_DEBUG("av_inject_open success, inject handle:0x%x", *phInjecter);
    AV_HANDLE_UnLock();

    HAL_DEBUG_EXIT();

    return s32Ret;
}

static S32 av_injecter_close(AV_DEVICE_S* pstDev,
                             const HANDLE hInjecter,
                             AV_INJECTER_CLOSE_PARAMS_S* const pstCloseParams)
{
    S32 s32Ret = SUCCESS;
    U32 u32Idx = AV_INJECT_INVALID_IDX;
    AV_INJECT_INFO_S* pstInjectInfo = NULL;

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    AV_HANDLE_Lock();

    u32Idx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_MAX_COUNT <= u32Idx), ERROR_AV_INJECT_NOT_OPENED, AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32Idx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    if (AV_INVALID_HANDLE != pstInjectInfo->hAvHal)
    {
        HAL_ERROR("please detach injecter first!\n");
        AV_HANDLE_UnLock();
        return FAILURE;
    }

    AV_FREEP(&pstInjectInfo);
    s_stInjectHandleInfo[u32Idx].bUsed   = FALSE;
    s_stInjectHandleInfo[u32Idx].hInject = AV_INVALID_HANDLE;
    s_stInjectHandleInfo[u32Idx].pstInjecterInfo = NULL;

    AV_HANDLE_UnLock();

    HAL_DEBUG_EXIT();

    return s32Ret;
}

static S32 av_injecter_attach(AV_DEVICE_S* pstDev,
                              const HANDLE hInjecter,
                              const HANDLE hAvHandle)
{
    S32 s32Ret = SUCCESS;
    U32 u32InjectIdx = AV_INJECT_INVALID_IDX, u32AvIdx = AV_HAL_INVALID_IDX;
    U32 u32PixelNum = 0;
    U32 u32BufSize = 0, u32Height = 0, u32Width = 0;
    HANDLE   hAvHandleSdk = AV_INVALID_HANDLE;
    HANDLE   hVidInjecter = AV_INVALID_HANDLE;
    HANDLE   hAudInjecter = AV_INVALID_HANDLE;
    AV_INJECT_INFO_S* pstInjectInfo = NULL;
    AV_HAL_INFO_S*    pstAvInfo = NULL;
#ifdef HAL_HISI_EXTEND_H
    const AV_HDR_PARAM_S* pstAvHdrParams = NULL;
#endif
    HI_UNF_AVPLAY_OPEN_OPT_S stOpenOpt;
    HI_UNF_AVPLAY_ATTR_S     stAvPlayAttr;
    AV_CONTENT_TYPE_E        enInjectContent;
    AV_VID_STREAM_TYPE_E     enVidStreamType;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    AV_HANDLE_Lock();
    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);

    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
    s32Ret   = AV_SDK_GetAvPlayDhl(hAvHandle, &hAvHandleSdk);

    HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx || SUCCESS != s32Ret), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "not found this av, handle is(0x%x).", hAvHandle);

    pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
    HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    HAL_CHK_CALL_RETURN((pstAvInfo->hAudInjecter == hInjecter || pstAvInfo->hVidInjecter == hInjecter), SUCCESS,
                        AV_HANDLE_UnLock(), "injecter already attached");

    enInjectContent = pstInjectInfo->stInjectSettings.enInjectContent;
    hAudInjecter    = pstAvInfo->hAudInjecter;
    hVidInjecter    = pstAvInfo->hVidInjecter;
    u32BufSize      = pstInjectInfo->stInjectSettings.u32BufSize;
    enVidStreamType = pstAvInfo->stAvSettings.enVidStreamType;
    u32Height       = (U32)pstAvInfo->stAvSettings.stVdecParams.u16Height;
    u32Width        = (U32)pstAvInfo->stAvSettings.stVdecParams.u16Width;
#ifdef HAL_HISI_EXTEND_H
    pstAvHdrParams  = &pstAvInfo->stAvSettings.stHdrParams;
#endif
    AV_HANDLE_UnLock();

    s32Ret = HI_UNF_AVPLAY_GetAttr(hAvHandleSdk, HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE, &stAvPlayAttr);

    /* Open audio and video channel, video channel must set decode level. Attirbutes like decode type, sync mode, ..., set in av_start_video
          and av_start_audio functions. */
    if (AV_CONTENT_AUDIO == enInjectContent)
    {
        HAL_CHK_RETURN((AV_INVALID_HANDLE != hAudInjecter), ERROR_AV_INJECT_NOT_DETACH, "already attach audio injecter.");

        if (u32BufSize)
        {
            stAvPlayAttr.stStreamAttr.u32AudBufSize = u32BufSize;
        }
        else
        {
            // TODO:
            stAvPlayAttr.stStreamAttr.u32AudBufSize = AV_AUDIO_BUFF_SIZE;
        }

        s32Ret = HI_UNF_AVPLAY_SetAttr(hAvHandleSdk, HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE, &stAvPlayAttr);
        HAL_CHK_PRINTF((s32Ret != SUCCESS), "set audio es stream buffer fail");

        s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvHandleSdk, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, NULL);
        HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AV_OP_FAILED, "open audio inject fail.");

        AV_SDK_SetInjectHdl(hAvHandle, AV_CONTENT_AUDIO, hInjecter);
        AV_SDK_SetAttachAvHdl(hInjecter, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, hAvHandle);
    }
    else if (AV_CONTENT_VIDEO == enInjectContent)
    {
        HAL_CHK_RETURN((AV_INVALID_HANDLE != hVidInjecter), ERROR_AV_INJECT_NOT_DETACH, "already attach video injecter.");

        u32PixelNum = u32Height * u32Width;

        /*default values*/
        stOpenOpt.enDecType       = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
        stOpenOpt.enCapLevel      = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
        stOpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;

        if (u32PixelNum > (U32)(AV_VDEC_CAP_LEVEL_4096_WIDTH * AV_VDEC_CAP_LEVEL_2160_HEIGHT))
        {
            stOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_4096x4096;
            HAL_DEBUG("set CapLevel HI_UNF_VCODEC_CAP_LEVEL_4096x4096");
        }
        else if (u32PixelNum >= (U32)(AV_VDEC_CAP_LEVEL_2160_WIDTH * AV_VDEC_CAP_LEVEL_1280_HEIGHT))
        {
            stOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_4096x2160;
            HAL_DEBUG("set CapLevel HI_UNF_VCODEC_CAP_LEVEL_4096x2160");
        }

        if (AV_VID_STREAM_TYPE_H263 == enVidStreamType
            || AV_VID_STREAM_TYPE_SORENSON == enVidStreamType)
        {
            stOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_720P;
            HAL_DEBUG("set CapLevel HI_UNF_VCODEC_CAP_LEVEL_720P");
        }
        else if (AV_VID_STREAM_TYPE_VC1 == enVidStreamType)
        {
            stOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
            HAL_DEBUG("set CapLevel HI_UNF_VCODEC_CAP_LEVEL_FULLHD");
        }

        if (AV_VID_STREAM_TYPE_MVC == enVidStreamType)
        {
            stOpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_MVC;
        }

        /* avplay create by using default es buffer size, when attach injecters, resetting the es buffer size */
        if (u32BufSize)
        {
            stAvPlayAttr.stStreamAttr.u32VidBufSize = u32BufSize;
        }
        else
        {
            // TODO:
            stAvPlayAttr.stStreamAttr.u32VidBufSize = AV_VIDEO_BUFF_SIZE;
        }

        s32Ret = HI_UNF_AVPLAY_SetAttr(hAvHandleSdk, HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE, &stAvPlayAttr);
        HAL_CHK_PRINTF((s32Ret != SUCCESS), "set video es stream buffer fail");

        s32Ret = HI_UNF_AVPLAY_ChnOpen(hAvHandleSdk, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stOpenOpt);
        HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AV_OP_FAILED, "open video inject fail.");

#ifdef HAL_HISI_EXTEND_H
        AV_SDK_SetHdrAttr(hAvHandleSdk, pstAvHdrParams);
#endif
        AV_SDK_SetInjectHdl(hAvHandle, AV_CONTENT_VIDEO, hInjecter);
        AV_SDK_SetAttachAvHdl(hInjecter, HI_UNF_AVPLAY_MEDIA_CHAN_VID, hAvHandle);
    }

    // TODO: should support ts data type?

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_injecter_detach(AV_DEVICE_S* pstDev, const HANDLE hInjecter)
{
    S32 s32Ret = SUCCESS;
    U32 u32InjectIdx = AV_INJECT_INVALID_IDX;
    AV_INJECT_INFO_S* pstInjectInfo = NULL;
    HANDLE hAvHandleSdk = AV_INVALID_HANDLE;
    HI_UNF_AVPLAY_MEDIA_CHAN_E enAvChanType;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    AV_HANDLE_Lock();

    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    s32Ret = AV_SDK_GetAvPlayDhl(pstInjectInfo->hAvHal, &hAvHandleSdk);

    enAvChanType = pstInjectInfo->enAvChanType;

    AV_HANDLE_UnLock();

    /* Before detach audio or video inject, app should detach AOut or Vout. */
    if (HI_UNF_AVPLAY_MEDIA_CHAN_AUD == enAvChanType)
    {
        s32Ret = HI_UNF_AVPLAY_ChnClose(hAvHandleSdk, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE,
                       "audio inject detach fail, may be Aout not detached.");

        AV_SDK_SetInjectHdl((HANDLE)pstInjectInfo->hAvHal, AV_CONTENT_AUDIO, AV_INVALID_HANDLE);
        AV_SDK_SetAttachAvHdl((HANDLE)hInjecter, HI_UNF_AVPLAY_MEDIA_CHAN_BUTT, AV_INVALID_HANDLE);
    }
    else if (HI_UNF_AVPLAY_MEDIA_CHAN_VID == enAvChanType)
    {
        s32Ret = HI_UNF_AVPLAY_ChnClose(hAvHandleSdk, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE,
                       "video inject detach fail, may be Vout not detached.");

        AV_SDK_SetInjectHdl((HANDLE)pstInjectInfo->hAvHal, AV_CONTENT_VIDEO, AV_INVALID_HANDLE);
        AV_SDK_SetAttachAvHdl((HANDLE)hInjecter, HI_UNF_AVPLAY_MEDIA_CHAN_BUTT, AV_INVALID_HANDLE);
    }

    AV_SDK_TermInjecter(hInjecter, TRUE);
    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_inject_data(AV_DEVICE_S* pstDev,
                          const HANDLE hInjecter,
                          VOID* const pvData,
                          const U32 u32Length,
                          U32 u32TimeoutMs)
{
    return AV_SDK_SendData(hInjecter, NULL, 0, pvData, u32Length, NULL, 0, u32TimeoutMs, AV_INVALID_PTS);
}

static S32 av_inject_get_freebuf(AV_DEVICE_S* pstDev, const HANDLE hInjecter, U32 u32ReqLen,
                                 VOID** ppvBufFree, U32* pu32FreeSize)
{
    S32  s32Ret = SUCCESS;
    U32  u32InjectIdx = AV_INJECT_INVALID_IDX;

    AV_INJECT_INFO_S* pstInjectInfo = NULL;

    HANDLE hAvHandleSdk = AV_INVALID_HANDLE;
    HI_UNF_AVPLAY_BUFID_E enAvBufId = HI_UNF_AVPLAY_BUF_ID_BUTT;
    HI_UNF_STREAM_BUF_S   stBuffer;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == ppvBufFree || NULL == pu32FreeSize), ERROR_NULL_PTR, "parameter is NULL.");

    AV_HANDLE_Lock();

    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    s32Ret = AV_SDK_GetAvPlayDhl(pstInjectInfo->hAvHal, &hAvHandleSdk);
    HAL_CHK_CALL_RETURN((SUCCESS != s32Ret), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "sdk av play not create, hal av handle(0x%x)", pstInjectInfo->hAvHal);

    enAvBufId = (AV_CONTENT_AUDIO == pstInjectInfo->stInjectSettings.enInjectContent)
                ? HI_UNF_AVPLAY_BUF_ID_ES_AUD : HI_UNF_AVPLAY_BUF_ID_ES_VID;

    AV_HANDLE_UnLock();

    s32Ret = HI_UNF_AVPLAY_GetBuf(hAvHandleSdk, enAvBufId, u32ReqLen, &stBuffer, 0);
    if (s32Ret != SUCCESS)
    {
        *ppvBufFree   = NULL;
        *pu32FreeSize = 0;
        HAL_DEBUG("get free buffer fail.");
        return FAILURE;
    }

    *ppvBufFree   = (VOID*)stBuffer.pu8Data;
    *pu32FreeSize = stBuffer.u32Size;

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_inject_write_complete(AV_DEVICE_S* pstDev,
                                    const HANDLE hInjecter,
                                    U32 u32WriteSize,
                                    S64 s64Pts)
{
    S32  s32Ret = SUCCESS;
    U32  u32InjectIdx = AV_INJECT_INVALID_IDX;

    AV_INJECT_INFO_S* pstInjectInfo = NULL;
    HI_UNF_AVPLAY_BUFID_E enAvBufId = HI_UNF_AVPLAY_BUF_ID_BUTT;

    HANDLE hAvHandleSdk = AV_INVALID_HANDLE;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    AV_HANDLE_Lock();

    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    s32Ret = AV_SDK_GetAvPlayDhl(pstInjectInfo->hAvHal, &hAvHandleSdk);
    HAL_CHK_CALL_RETURN((SUCCESS != s32Ret), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "sdk av play not create, hal av handle(0x%x)", pstInjectInfo->hAvHal);

    enAvBufId = (AV_CONTENT_AUDIO == pstInjectInfo->stInjectSettings.enInjectContent)
                ? HI_UNF_AVPLAY_BUF_ID_ES_AUD : HI_UNF_AVPLAY_BUF_ID_ES_VID;

    AV_HANDLE_UnLock();

    s32Ret = HI_UNF_AVPLAY_PutBuf(hAvHandleSdk, enAvBufId, u32WriteSize, (U32)s64Pts);
    HAL_CHK_RETURN((SUCCESS != s32Ret),FAILURE, "inject write complete fail, ret(0x%x)", s32Ret);

    return SUCCESS;
}

static S32 av_inject_get_buf_status(AV_DEVICE_S* pstDev,
                                    const HANDLE hInjecter,
                                    AV_BUF_STATUS_S* const pstBufStatus)
{
    S32  s32Ret = SUCCESS;
    U32  u32InjectIdx = AV_INJECT_INVALID_IDX;

    AV_INJECT_INFO_S* pstInjectInfo = NULL;

    HANDLE hAvHandleSdk = AV_INVALID_HANDLE;
    HI_UNF_AVPLAY_BUFID_E enAvBufId = HI_UNF_AVPLAY_BUF_ID_BUTT;
    HI_UNF_AVPLAY_STATUS_INFO_S stStatus;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pstBufStatus), ERROR_NULL_PTR, "parameter is NULL.");

    AV_HANDLE_Lock();

    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    s32Ret = AV_SDK_GetAvPlayDhl(pstInjectInfo->hAvHal, &hAvHandleSdk);
    HAL_CHK_CALL_RETURN((SUCCESS != s32Ret), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "sdk av play not create, hal av handle(0x%x)", pstInjectInfo->hAvHal);

    enAvBufId = (AV_CONTENT_AUDIO == pstInjectInfo->stInjectSettings.enInjectContent)
                ? HI_UNF_AVPLAY_BUF_ID_ES_AUD : HI_UNF_AVPLAY_BUF_ID_ES_VID;

    HAL_MEMSET_NO_VERIFY(pstBufStatus, 0, sizeof(AV_BUF_STATUS_S));
    pstBufStatus->enDataType      = pstInjectInfo->stInjectSettings.enDataType;
    pstBufStatus->u32InjectMinLen = pstInjectInfo->stInjectSettings.u32InjectMinLen;

    AV_HANDLE_UnLock();

    HAL_MEMSET_NO_VERIFY(&stStatus, 0, sizeof(stStatus));
    s32Ret = HI_UNF_AVPLAY_GetStatusInfo(hAvHandleSdk, &stStatus);

    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get sdk avplay status info fail, s32Ret(0x%08x)", s32Ret);

    pstBufStatus->u32Size = stStatus.stBufStatus[enAvBufId].u32BufSize;
    pstBufStatus->u32Used = stStatus.stBufStatus[enAvBufId].u32UsedSize;
    pstBufStatus->u32Free = stStatus.stBufStatus[enAvBufId].u32BufSize - stStatus.stBufStatus[enAvBufId].u32UsedSize;

    HAL_DEBUG("inject buf status size(%d) used(%d) free(%d)",
              pstBufStatus->u32Size, pstBufStatus->u32Used, pstBufStatus->u32Free);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_inject_get_status(AV_DEVICE_S* pstDev,
                                const HANDLE hInjecter,
                                AV_INJECT_STATUS_S* const pstStatus)
{
    U32  u32InjectIdx = AV_INJECT_INVALID_IDX;
    U32  u32AvIdx     = AV_HAL_INVALID_IDX;

    AV_INJECT_INFO_S* pstInjectInfo = NULL;
    HANDLE hAv = AV_INVALID_HANDLE;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pstStatus), ERROR_NULL_PTR, "parameter is NULL.");

    AV_HANDLE_Lock();

    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    u32AvIdx = AV_GET_HANDLE_Index(pstInjectInfo->hAvHal);
    if(AV_HAL_INVALID_IDX == u32AvIdx)
    {
       HAL_ERROR("sdk av play not create, hal av handle(0x%x)", pstInjectInfo->hAvHal);
       hAv = AV_INVALID_HANDLE;
    }
    else
    {
       hAv = s_stAvHandleInfo[u32AvIdx].hAvHal;
    }

    AV_HANDLE_UnLock();

    (VOID)av_inject_get_buf_status(pstDev, hInjecter, &pstStatus->stBufStatus);
    pstStatus->hInjecter  = hInjecter;
    pstStatus->hAv        = hAv;

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_inject_get_setting(AV_DEVICE_S* pstDev,
                         const HANDLE hInjecter,
                         AV_INJECT_SETTINGS_S* const pstSettings)
{
    U32  u32InjectIdx = AV_INJECT_INVALID_IDX;

    AV_INJECT_INFO_S* pstInjectInfo = NULL;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((NULL == pstSettings), ERROR_NULL_PTR, "parameter is NULL.");

    AV_HANDLE_Lock();

    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    HAL_MEMCPY(pstSettings, &pstInjectInfo->stInjectSettings, sizeof(AV_INJECT_SETTINGS_S));

    AV_HANDLE_UnLock();
    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 av_inject_reset_buf(AV_DEVICE_S* pstDev, const HANDLE hInjecter)
{
    S32  s32Ret = SUCCESS;
    U32  u32InjectIdx = AV_INJECT_INVALID_IDX;
    AV_INJECT_INFO_S* pstInjectInfo = NULL;
    HANDLE hAvHandleSdk = AV_INVALID_HANDLE;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    AV_HANDLE_Lock();

    u32InjectIdx = AV_GET_INJECT_Index(hInjecter);
    HAL_CHK_CALL_RETURN((AV_INJECT_INVALID_IDX == u32InjectIdx), ERROR_AV_INJECT_NOT_OPENED,
                        AV_HANDLE_UnLock(),
                        "not found this inject, handle is(0x%x).", hInjecter);

    pstInjectInfo = s_stInjectHandleInfo[u32InjectIdx].pstInjecterInfo;
    HAL_CHK_CALL_RETURN((NULL == pstInjectInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

    s32Ret = AV_SDK_GetAvPlayDhl(pstInjectInfo->hAvHal, &hAvHandleSdk);
    HAL_CHK_CALL_RETURN((SUCCESS != s32Ret), ERROR_AV_PLAYER_NOT_CREATED,
                        AV_HANDLE_UnLock(),
                        "sdk av play not create, hal av handle(0x%x)", pstInjectInfo->hAvHal);

    AV_HANDLE_UnLock();

    // TODO: avplay reset will reset audio and video injecter, may not satisfy requirements.

    s32Ret = HI_UNF_AVPLAY_Reset(hAvHandleSdk, NULL);
    HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "sdk avplay reset fail.");

    return SUCCESS;
}

static S32 av_inject_set_pcm_params(AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                    AV_PCM_PARAMS_S* const pstParams)
{
    // TODO: does need this function
    return ERROR_NOT_SUPPORTED;
}

static S32 av_inject_set_es_params(AV_DEVICE_S* pstDev,
                                   const HANDLE hInjecter,
                                   AV_ES_PARAMS_S* const pstParams)
{
    // TODO: does need this function
    return ERROR_NOT_SUPPORTED;
}

static S32 av_inject_es_data(AV_DEVICE_S* pstDev,
                             const HANDLE hInjecter,
                             AV_ES_DATA_S* const pData,
                             U32 u32TimeoutMs)
{
    HAL_CHK_RETURN((NULL == pData), ERROR_NULL_PTR, "param is null ptr.");

    return AV_SDK_SendData(hInjecter, pData->pvHeader, pData->u32HeaderLen,
                           pData->pvEsBuf, pData->u32EsLen,
                           pData->pvPrivate, pData->u32PrivateLen,
                           u32TimeoutMs, pData->s64TimeStamp);
}

S32 av_inject_abort(AV_DEVICE_S* pstDev, const HANDLE hInjecter)
{
    S32 s32Ret = FAILURE;

    HAL_DEBUG_ENTER();

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");

    s32Ret = AV_SDK_TermInjecter(hInjecter, TRUE);

    HAL_DEBUG_EXIT();

    return s32Ret;
}

#ifdef HAL_HISI_EXTEND_H
S32 av_register_audiolib(AV_DEVICE_S* pstDev, const S8* ps8Audlib)
{
    S32 s32Ret = FAILURE;

    HAL_DEBUG_ENTER();
    HAL_CHK_RETURN((NULL == ps8Audlib), ERROR_NULL_PTR, "parameter is NULL.");
    s32Ret = HI_UNF_AVPLAY_RegisterAcodecLib((const HI_CHAR *)ps8Audlib);
    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("Register audlib %s fail:0x%x", ps8Audlib, s32Ret);
        s32Ret = FAILURE;
    }
    HAL_DEBUG_EXIT();
    return s32Ret;
}

S32 av_invoke(AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_INVOKE_E eCmd, VOID* pArg)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_AVPLAY_INVOKE_E enInvokeType = HI_UNF_AVPLAY_INVOKE_BUTT;
    AV_VCODEC_CMD_S        stVcodecCmd;
    HI_CODEC_VIDEO_CMD_S   stVideoCmd;

    HAL_DEBUG_ENTER();
    HAL_MEMSET_NO_VERIFY(&stVcodecCmd, 0, sizeof(AV_VCODEC_CMD_S));
    HAL_MEMSET_NO_VERIFY(&stVideoCmd, 0, sizeof(HI_CODEC_VIDEO_CMD_S));

    HAL_CHK_RETURN((0 == AV_IS_Init()), ERROR_NOT_INITED, "AV not init.");
    HAL_CHK_RETURN((AV_INVALID_HANDLE == hAvHandle), ERROR_AV_PLAYER_NOT_CREATED, "AV handle is not created.");

    HAL_CHK_RETURN((NULL == pArg), ERROR_NULL_PTR, "parameter is NULL.");
    HAL_CHK_RETURN((AV_INVOKE_BUTT <= eCmd), ERROR_INVALID_PARAM, "parameter is invalid.");

    AV_HAL_InvokeCmdToSdk(eCmd, &enInvokeType);
    if (AV_INVOKE_VCODEC == eCmd)
    {
        HAL_MEMCPY_NO_VERIFY(&stVcodecCmd, (AV_VCODEC_CMD_S*)pArg, sizeof(AV_VCODEC_CMD_S));
        stVideoCmd.pPara = stVcodecCmd.pParam;

        s32Ret = AV_HAL_VcodecCmdToSdk((AV_CODEC_SET_CMD_E)(stVcodecCmd.u32CmdIdx), &stVideoCmd);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "get sdk command fail");

        s32Ret = HI_UNF_AVPLAY_Invoke(hAvHandle, enInvokeType, (HI_VOID *)&stVideoCmd);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "avplay invoke fail, ret(%08x)", s32Ret);
    }
    else if (AV_INVOKE_ACODEC == eCmd)
    {
        s32Ret = HI_UNF_AVPLAY_Invoke(hAvHandle, enInvokeType, pArg);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "avplay invoke fail, ret(%08x)", s32Ret);
    }
    else if (AV_INVOKE_SET_VID_LASTFRMFLAG == eCmd)
    {
        stVideoCmd.pPara = pArg;
        stVideoCmd.u32CmdID = HI_UNF_AVPLAY_SET_VDEC_LSTFRAME_CMD;

        s32Ret = HI_UNF_AVPLAY_Invoke(hAvHandle, enInvokeType, (HI_VOID *)&stVideoCmd);
        HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "avplay invoke fail, ret(%08x)", s32Ret);
    }
#ifdef SM_SUPPORT
    else if (AV_INVOKE_SET_SESSION == eCmd)
    {
        HANDLE hSM = AV_INVALID_HANDLE;
        U32  u32AvIdx = AV_HAL_INVALID_IDX;
        AV_HAL_INFO_S* pstAvInfo = NULL;
        HI_UNF_SM_ATTR_S stSMAttr;
        AV_INVOKE_SET_SESSION_S *pstSMAttr = (AV_INVOKE_SET_SESSION_S *)pArg;
        HI_UNF_SM_MODULE_S  SmModule;

        AV_HANDLE_Lock();
        u32AvIdx = AV_GET_HANDLE_Index(hAvHandle);
        HAL_CHK_CALL_RETURN((AV_HAL_INVALID_IDX == u32AvIdx), ERROR_AV_PLAYER_NOT_CREATED,
                            AV_HANDLE_UnLock(),
                            "av player handle:0x%x not found!", hAvHandle);

        pstAvInfo = s_stAvHandleInfo[u32AvIdx].pstAvHalInfo;
        HAL_CHK_CALL_RETURN((NULL == pstAvInfo), ERROR_NULL_PTR, AV_HANDLE_UnLock(), "parameter is NULL.");

        if (pstSMAttr->bSessionEnable)
        {
            (VOID)HI_UNF_SM_Init();

            stSMAttr.u32SessionID = pstSMAttr->u32SessionID;
            s32Ret = HI_UNF_SM_Create(&hSM, &stSMAttr);
            if (s32Ret != HI_SUCCESS)
            {
                (VOID)HI_UNF_SM_DeInit();
                AV_HANDLE_UnLock();
                HAL_ERROR("HI_UNF_SM_Create error, ret %#x", s32Ret);
                return FAILURE;
            }

            pstAvInfo->hSM = hSM;
            SmModule.hHandle = pstAvInfo->hAvPlayerSdk;
            s32Ret = HI_UNF_SM_AddResource(pstAvInfo->hSM, HI_UNF_SM_MODULE_AVPLAY, &SmModule);
            if (s32Ret != HI_SUCCESS)
            {
                (VOID)HI_UNF_SM_Destroy(hSM);
                (VOID)HI_UNF_SM_DeInit();
                AV_HANDLE_UnLock();
                HAL_ERROR("HI_UNF_SM_AddResource error, ret %#x", s32Ret);
                return FAILURE;
            }
        }

        AV_HANDLE_UnLock();
    }
#endif
    else
    {
        HAL_ERROR("invoke command can not find.CMD=0x%x\n", eCmd);
        return FAILURE;
    }
    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 av_set_metadata_info(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, const AV_VIDEO_METADATA_INFO_S* pstMetaDataInfo)
{
    S32 s32Ret = SUCCESS;
    HAL_DEBUG_ENTER();
    HI_UNF_VIDEO_HDR_INFO_S stVideHdrInfo;

    memset(&stVideHdrInfo, 0, sizeof(HI_UNF_VIDEO_HDR_INFO_S));

    switch(pstMetaDataInfo->enMetadataType)
    {
        case AV_VIDEO_METADATA_TYPE_HDR10:
            stVideHdrInfo.enHdrType = HI_UNF_VIDEO_HDR_TYPE_HDR10;
            memcpy(&stVideHdrInfo.unHdrMetadata.stHdr10Info, &pstMetaDataInfo->unMetadataInfo.stHdr10Info, sizeof(HI_UNF_VIDEO_HDR10_INFO_S));
            s32Ret = HI_UNF_AVPLAY_SetHDRInfo(hAvHandle, &stVideHdrInfo, pstMetaDataInfo->bPaddingInfo, 0);
            HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set METADATA_TYPE_HDR10 is fail, ret(%08x)", s32Ret);
            break;

        case AV_VIDEO_METADATA_TYPE_HLG:
            stVideHdrInfo.enHdrType = HI_UNF_VIDEO_HDR_TYPE_HLG;
            memcpy(&stVideHdrInfo.unHdrMetadata.stHlgInfo, &pstMetaDataInfo->unMetadataInfo.stHlgInfo, sizeof(HI_UNF_VIDEO_HLG_INFO_S));
            s32Ret = HI_UNF_AVPLAY_SetHDRInfo(hAvHandle, &stVideHdrInfo, pstMetaDataInfo->bPaddingInfo, 0);
            HAL_CHK_RETURN((SUCCESS != s32Ret), FAILURE, "set METADATA_TYPE_HLG is fail, ret(%08x)", s32Ret);
            break;

        default:
            HAL_ERROR("metadata info type not find . TYPE=0x%x\n", pstMetaDataInfo->enMetadataType);
            return FAILURE;
            break;
    }

    HAL_DEBUG_EXIT();
    return SUCCESS;
}

#endif

#ifdef TVOS_PLATFORM
static int av_dev_close(struct hw_device_t *pstAvDevice)
{
    AV_DEVICE_S* pCtx = (AV_DEVICE_S *)pstAvDevice;
    if (pCtx)
    {
        free(pCtx);
        pCtx = NULL;
    }
    return SUCCESS;
}

static int av_dev_open(const struct hw_module_t *module, const char *name, struct hw_device_t **device)
{
    #define INIT_ZERO(obj) (memset(&(obj), 0, sizeof((obj))))

    if (strcmp(name, AV_HARDWARE_AV0) != 0)
    {
        return FAILURE;
    }

    if (NULL == device)
    {
        return FAILURE;
    }

    AV_DEVICE_S *pstAvDev = (AV_DEVICE_S *)malloc(sizeof(AV_DEVICE_S));
    if (NULL == pstAvDev)
    {
        printf("%s,%d malloc memory failed!\n", __func__, __LINE__);
        return FAILURE;
    }

    memset(pstAvDev, 0, sizeof(AV_DEVICE_S));

    pstAvDev->stCommon.tag = HARDWARE_DEVICE_TAG;
    pstAvDev->stCommon.version = AV_DEVICE_API_VERSION_1_0;
    pstAvDev->stCommon.module = (hw_module_t*)module;
    pstAvDev->stCommon.close = av_dev_close;

    pstAvDev->av_init                        = av_init;
    pstAvDev->av_create                      = av_create;
    pstAvDev->av_destroy                     = av_destroy;
    pstAvDev->av_term                        = av_term;

    pstAvDev->av_get_capability              = av_get_capability;
    pstAvDev->av_evt_config                  = av_evt_config;
    pstAvDev->av_get_evt_config              = av_get_evt_config;
    pstAvDev->av_get_status                  = av_get_status;
    pstAvDev->av_get_config                  = av_get_config;
    pstAvDev->av_set_config                  = av_set_config;

    pstAvDev->av_start                       = av_start;
    pstAvDev->av_stop                        = av_stop;
    pstAvDev->av_pause                       = av_pause;
    pstAvDev->av_resume                      = av_resume;
    pstAvDev->av_reset                       = av_reset;

    pstAvDev->av_start_video                 = av_start_video;
    pstAvDev->av_pause_video                 = av_pause_video;
    pstAvDev->av_freeze_video                = av_freeze_video;
    pstAvDev->av_resume_video                = av_resume_video;
    pstAvDev->av_stop_video                  = av_stop_video;
    pstAvDev->av_clear_video                 = av_clear_video;

    pstAvDev->av_start_audio                 = av_start_audio;
    pstAvDev->av_pause_audio                 = av_pause_audio;
    pstAvDev->av_resume_audio                = av_resume_audio;
    pstAvDev->av_stop_audio                  = av_stop_audio;

    pstAvDev->av_decode_iframe               = av_decode_iframe;
    pstAvDev->av_release_iframe              = av_release_iframe;

    pstAvDev->av_injecter_open               = av_injecter_open;
    pstAvDev->av_injecter_close              = av_injecter_close;
    pstAvDev->av_injecter_attach             = av_injecter_attach;
    pstAvDev->av_injecter_detach             = av_injecter_detach;
    pstAvDev->av_inject_data                 = av_inject_data;

#if 0
    pstAvDev->av_get_player_handle = av_get_player_handle;
    pstAvDev->av_get_inject_handle = av_get_inject_handle;
#endif

    pstAvDev->av_inject_get_freebuf          = av_inject_get_freebuf;
    pstAvDev->av_inject_write_complete       = av_inject_write_complete;
    pstAvDev->av_inject_get_buf_status       = av_inject_get_buf_status;
    pstAvDev->av_inject_get_status           = av_inject_get_status;
    pstAvDev->av_inject_get_setting          = av_inject_get_setting;
    pstAvDev->av_inject_reset_buf            = av_inject_reset_buf;
    pstAvDev->av_inject_set_pcm_params       = av_inject_set_pcm_params;
    pstAvDev->av_inject_set_es_params        = av_inject_set_es_params;
    pstAvDev->av_inject_es_data              = av_inject_es_data;
    pstAvDev->av_inject_abort                = av_inject_abort;
#ifdef HAL_HISI_EXTEND_H
    pstAvDev->av_acquire_frame               = av_acquire_frame;
    pstAvDev->av_release_frame               = av_release_frame;
    pstAvDev->av_set_buf_mode                = av_set_buf_mode;
    pstAvDev->av_acquire_user_buf            = av_acquire_user_buf;
    pstAvDev->av_release_user_buf            = av_release_user_buf;
    pstAvDev->av_format_change               = av_format_change;
    pstAvDev->av_sync_frame                  = av_sync_frame;
    pstAvDev->av_register_audiolib           = av_register_audiolib;
    pstAvDev->av_invoke                      = av_invoke;
    pstAvDev->av_set_metadata_info           = av_set_metadata_info,
#endif
    *device = &pstAvDev->stCommon;
    return SUCCESS;
}

static struct hw_module_methods_t av_module_methods = {
    .open = av_dev_open,
};
AV_MODULE_S HAL_MODULE_INFO_SYM = {
    .stCommon= {
        .tag= HARDWARE_MODULE_TAG,
        .version_major= 1,
        .version_minor= 0,
        .id= AV_HARDWARE_MODULE_ID,
        .name= "Sample halav module",
        .author= "The Android Open Source Project",
        .methods= &av_module_methods,
        .dso= NULL,
    }
};
#endif

static AV_DEVICE_S s_stDevice_av =
{
    /* register the callbacks */
    .av_init                        = av_init,
    .av_create                      = av_create,
    .av_destroy                     = av_destroy,
    .av_term                        = av_term,

    .av_get_capability              = av_get_capability,
    .av_evt_config                  = av_evt_config,
    .av_get_evt_config              = av_get_evt_config,
    .av_get_status                  = av_get_status,
    .av_get_config                  = av_get_config,
    .av_set_config                  = av_set_config,

    .av_start                       = av_start,
    .av_stop                        = av_stop,
    .av_pause                       = av_pause,
    .av_resume                      = av_resume,
    .av_reset                       = av_reset,

    .av_start_video                 = av_start_video,
    .av_pause_video                 = av_pause_video,
    .av_freeze_video                = av_freeze_video,
    .av_resume_video                = av_resume_video,
    .av_stop_video                  = av_stop_video,
    .av_clear_video                 = av_clear_video,

    .av_start_audio                 = av_start_audio,
    .av_pause_audio                 = av_pause_audio,
    .av_resume_audio                = av_resume_audio,
    .av_stop_audio                  = av_stop_audio,

    .av_decode_iframe               = av_decode_iframe,
    .av_release_iframe              = av_release_iframe,
    .av_injecter_open               = av_injecter_open,
    .av_injecter_close              = av_injecter_close,
    .av_injecter_attach             = av_injecter_attach,
    .av_injecter_detach             = av_injecter_detach,
    .av_inject_data                 = av_inject_data,

    .av_inject_get_freebuf          = av_inject_get_freebuf,
    .av_inject_write_complete       = av_inject_write_complete,
    .av_inject_get_buf_status       = av_inject_get_buf_status,
    .av_inject_get_status           = av_inject_get_status,
    .av_inject_get_setting          = av_inject_get_setting,
    .av_inject_reset_buf            = av_inject_reset_buf,
    .av_inject_set_pcm_params       = av_inject_set_pcm_params,
    .av_inject_set_es_params        = av_inject_set_es_params,
    .av_inject_es_data              = av_inject_es_data,
    .av_inject_abort                = av_inject_abort,
#ifdef HAL_HISI_EXTEND_H
    .av_acquire_frame               = av_acquire_frame,
    .av_release_frame               = av_release_frame,
    .av_set_buf_mode                = av_set_buf_mode,
    .av_acquire_user_buf            = av_acquire_user_buf,
    .av_release_user_buf            = av_release_user_buf,
    .av_format_change               = av_format_change,
    .av_sync_frame                  = av_sync_frame,
    .av_register_audiolib           = av_register_audiolib,
    .av_invoke                      = av_invoke,
    .av_set_metadata_info           = av_set_metadata_info,
#endif
};

AV_DEVICE_S* getAVDevice()
{
    return &s_stDevice_av;
}

/** @} */  /** <!-- ==== API declaration end ==== */
