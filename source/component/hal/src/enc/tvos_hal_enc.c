#define LOG_TAG "hal_enc"
#include <pthread.h>

#include "hi_common.h"
#include "hi_unf_venc.h"
#include "hi_unf_aenc.h"
#include "hi_unf_audio.h"
#include "hi_unf_avplay.h"
#include "hi_unf_vo.h"
#include "hi_error_mpi.h"

#include "tvos_hal_enc.h"
#include "tvos_hal_enc_cfg.h"
#include "tvos_hal_common.h"
#include "tvos_hal_errno.h"

#include "HA.AUDIO.AAC.encode.h"

/**************************************************************************/
#define ENC_HEADER_VERSION          1
#define ENC_DEVICE_API_VERSION_1_0  HARDWARE_DEVICE_API_VERSION_2(1, 0, ENC_HEADER_VERSION)

#define AAC_ENCODE_DLL_NAME "libHA.AUDIO.AAC.encode.so"
/**************************************************************************/

#define INVALID_HANDLE (0)
#define AENC_MAX_COUNT (8)
#define VENC_MAX_COUNT (8)
#define VENC_MAX_QUEUE_NUM (6)
#define NO_CONCERN_VALUE (0)
#define PTS_RATIO (90)
#define DEFAULT_OUTPUT_CHANNELS (2)
#define DEFAULT_BITWIDTH_PER_SAMPLE (16)
#define DEFAULT_SAMPLE_RATE (48000)
#define TIMEOUT_SPLIT (10)
#define U32_STRM_BUF_SIZE (2 * 1920 * 1080)
#define U32_TARGET_BIT_RATE (2 * 1024 * 1024)
#define U32_TARGET_FRM_RATE (30)
#define U32_INPUT_FRM_RATE (30)
#define U32_GOP (30)
#define U32_MAX_QP (50)
#define U32_MIN_QP (10)
#define ALIGN_UP(val, align) ( (val+((align)-1))&~((align)-1) )

#define ENC_LOCK(mutex) \
    do \
    { \
        (VOID)pthread_mutex_lock((mutex)); \
    } while (0)

#define ENC_UNLOCK(mutex) \
    do \
    { \
        (VOID)pthread_mutex_unlock((mutex)); \
    } while (0)

#define CHECK_NULL_PARAM(PTR) \
    do\
    {\
        if(HI_NULL == PTR)\
        {\
            return ERROR_NULL_PTR;\
        }\
    }while(0);

#define CHECK_ENC_INIT() \
    do\
    {\
        if(!s_bVencInited || !s_bAencInited)\
        {\
            HAL_ERROR("Enc Not Inited Yet");\
            return ERROR_NOT_INITED;\
        }\
    }while(0);

#define GET_ENC_HANDLE_INDEX(TYPE, HANDLER, INDEX) \
    do\
    {\
        S32 s32Result = get_enc_handle_index(TYPE, HANDLER, INDEX);\
        if (SUCCESS != s32Result)\
        {\
            HAL_ERROR("%s,%d call get_enc_handle_index error, ret(0x%08x)", __func__, __LINE__, s32Result);\
            return s32Result;\
        }\
    }while(0);

extern S32 av_get_sdk_avplay_hdl(const HANDLE hAvHandle, HANDLE* phSdkAvPlayHdl);

/*****
 * TODO
 * 1. covert_param_vid_format_to_unf: SEMIPLANNAR/PLANNAR doesn't match unf, maybe need know UV or VU in hal.
 * 2. inject need set timeout?
 */

typedef struct _AENC_EXTRA_INFO_S
{
    ENC_SOURCE_PARAMS_S        stAencSrcPara;
    ENC_OUTPUT_PARAMS_S        stAencOutPara;
    ENC_OUTPUT_STREAM_FORMAT_E enAencOutStrFmt;
} AENC_EXTRA_INFO_S;

typedef struct _VENC_EXTRA_INFO_S
{
    ENC_SOURCE_PARAMS_S        stVencSrcPara;
    ENC_OUTPUT_PARAMS_S        stVencOutPara;
    ENC_OUTPUT_STREAM_FORMAT_E enVencOutStrFmt;

    ENC_COLOR_TYPE_E           enVencColorType;
    ENC_STORE_TYPE_E           enVencStoreType;
    ENC_YUV_PACKAGE_SEQ_E      enVencYuvPackSeq;
} VENC_EXTRA_INFO_S;

typedef struct _VENC_QUEUE_MMZ_S
{
    HI_MMZ_BUF_S               stHiMmzBuf;
    BOOL                       bMmzUsed;
} VENC_QUEUE_MMZ_S;

typedef struct _VENC_QUEUE_INFO_S
{
    VENC_QUEUE_MMZ_S           stVencQueueMmz[VENC_MAX_QUEUE_NUM];
    pthread_mutex_t            sameHandleQueueMutex;
} VENC_QUEUE_INFO_S;

typedef struct _AENC_HANDLE_S
{
    HANDLE            hAencHandle;
    HANDLE            hVirtualTrack;
    HANDLE            hAudCast;
    AENC_EXTRA_INFO_S stAencExtraInfo;
    BOOL              bUsed;
    BOOL              bAbortFlag;
} AENC_HANDLE_S;

typedef struct _VENC_HANDLE_S
{
    HANDLE            hVencHandle;
    HANDLE            hVirtualWin;
    HANDLE            hCast;
    VENC_EXTRA_INFO_S stVencExtraInfo;
    VENC_QUEUE_INFO_S stVencQueueInfo;
    BOOL              bUsed;
    BOOL              bAbortFlag;
} VENC_HANDLE_S;

static AENC_HANDLE_S s_stAencHandle[AENC_MAX_COUNT];
static VENC_HANDLE_S s_stVencHandle[VENC_MAX_COUNT];
static pthread_mutex_t s_enc_mutex = PTHREAD_MUTEX_INITIALIZER;

/* init flag */
static BOOL s_bVencInited = FALSE;
static BOOL s_bAencInited = FALSE;

static BOOL s_bAACSupported = FALSE;

typedef enum _HI_ENC_TYPE_E
{
    HI_ENC_VENC = 0,
    HI_ENC_AENC,
    HI_ENC_BUTT
} HI_ENC_TYPE_E;

// hal BOOL -> unf HI_BOOL
static inline HI_BOOL hal_to_unf_for_bool(BOOL bHalValue)
{
    return (HI_BOOL)(TRUE == bHalValue) ? HI_TRUE : HI_FALSE;
}

// unf HI_BOOL -> hal BOOL
static inline BOOL unf_to_hal_for_bool(HI_BOOL bUnfValue)
{
    return (BOOL)(HI_TRUE == bUnfValue) ? TRUE : FALSE;
}

static S32 get_enc_handle_index(const ENC_ENCODER_TYPE_E enEncType, const HANDLE encHandle, U32* u32Count)
{
    U32 u32Index = 0;

    if (ENC_ENCODE_VIDEO == enEncType)
    {
        for (u32Index = 0; u32Index < VENC_MAX_COUNT; u32Index++)
        {
            if ( (encHandle != INVALID_HANDLE)
                 && (encHandle == s_stVencHandle[u32Index].hVencHandle)
                 && (TRUE == s_stVencHandle[u32Index].bUsed) )
            {
                break;
            }

        }

        if (VENC_MAX_COUNT == u32Index)
        {
            HAL_ERROR("%s,%d error!! invalid handle:%#x.", __func__, __LINE__, encHandle);
            return ERROR_ENC_NO_SUCH_HANDLE;
        }
    }
    else if (ENC_ENCODE_AUDIO == enEncType)
    {
        for (u32Index = 0; u32Index < AENC_MAX_COUNT; u32Index++)
        {
            if (  (encHandle != INVALID_HANDLE)
                  && (encHandle == s_stAencHandle[u32Index].hAencHandle)
                  && (TRUE == s_stAencHandle[u32Index].bUsed) )
            {
                break;
            }
        }

        if (AENC_MAX_COUNT == u32Index)
        {
            HAL_ERROR("%s,%d error!! invalid handle:%#x.", __func__, __LINE__, encHandle);
            return ERROR_ENC_NO_SUCH_HANDLE;
        }
    }
    else
    {
        HAL_ERROR("UnSupported enc type.");
        return ERROR_NOT_SUPPORTED;
    }

    *u32Count = u32Index;
    return SUCCESS;
}

static HI_ENC_TYPE_E find_handle_type(HANDLE hEnc)
{
    U32 u32Index = 0;
    S32 s32Ret = FAILURE;

    s32Ret = get_enc_handle_index(ENC_ENCODE_VIDEO, hEnc, &u32Index);
    HAL_CHK_RETURN((SUCCESS == s32Ret), HI_ENC_VENC, "get vidoe handle index succ");

    s32Ret = get_enc_handle_index(ENC_ENCODE_AUDIO, hEnc, &u32Index);
    HAL_CHK_RETURN((SUCCESS == s32Ret), HI_ENC_AENC, "get audio handle index succ");

    return HI_ENC_BUTT;
}

static S32 covert_param_venc_type_to_unf(AV_VID_STREAM_TYPE_E enHalType, HI_UNF_VCODEC_TYPE_E* const penUnfType)
{
    switch (enHalType)
    {
        case AV_VID_STREAM_TYPE_H264:
        {
            *penUnfType = HI_UNF_VCODEC_TYPE_H264;
            break;
        }

        default:
        {
            HAL_ERROR("UnSupported other venc type: [%d].", enHalType);
            return ERROR_NOT_SUPPORTED;
        }
    }

    return SUCCESS;
}

static S32 covert_param_venc_setting_to_unf(HI_UNF_VENC_CHN_ATTR_S* pstVencAttr, const ENC_VENC_SETTINGS_S* const pstVencSetting)
{
    S32 s32Ret = FAILURE;
    HI_UNF_VCODEC_TYPE_E enVencType;
    memset(&enVencType, 0, sizeof(HI_UNF_VCODEC_TYPE_E));

    if (ENC_OUTPUT_MEM != pstVencSetting->stOutputParams.enOutputType)
    {
        HAL_ERROR("UnSupported other output Type.");
        return ERROR_NOT_SUPPORTED;
    }

    if (ENC_OUTPUT_STREAM_FORMAT_NONE == pstVencSetting->enOutputStreamFormat)
    {
        HAL_ERROR("output stream format error");
        return ERROR_INVALID_PARAM;
    }

    s32Ret = covert_param_venc_type_to_unf(pstVencSetting->enType, &enVencType);

    if (SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    pstVencAttr->enVencType = enVencType;
    pstVencAttr->enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    pstVencAttr->enVencProfile = HI_UNF_H264_PROFILE_BASELINE;
    pstVencAttr->u32Width = pstVencSetting->u32Width;
    pstVencAttr->u32Height = pstVencSetting->u32Height;
    pstVencAttr->u32StrmBufSize = pstVencSetting->u32BufSize;

    if (NO_CONCERN_VALUE == pstVencAttr->u32StrmBufSize)
    {
        pstVencAttr->u32StrmBufSize = U32_STRM_BUF_SIZE;
    }

    pstVencAttr->bSlcSplitEn = hal_to_unf_for_bool(pstVencSetting->bSliceSplit);
    pstVencAttr->u32TargetBitRate = pstVencSetting->u32BitRate;

    if (NO_CONCERN_VALUE == pstVencAttr->u32TargetBitRate)
    {
        pstVencAttr->u32TargetBitRate = U32_TARGET_BIT_RATE;
    }

    pstVencAttr->u32TargetFrmRate = pstVencSetting->u32OutputFrameRate;

    if (NO_CONCERN_VALUE == pstVencAttr->u32TargetFrmRate)
    {
        pstVencAttr->u32TargetFrmRate = U32_TARGET_FRM_RATE;
    }

    pstVencAttr->u32InputFrmRate = pstVencSetting->u32InputFrameRate;

    if (NO_CONCERN_VALUE == pstVencAttr->u32InputFrmRate)
    {
        pstVencAttr->u32InputFrmRate = U32_INPUT_FRM_RATE;
    }

    pstVencAttr->u32Gop = pstVencSetting->u32Gop;

    if (NO_CONCERN_VALUE == pstVencAttr->u32Gop)
    {
        pstVencAttr->u32Gop = U32_GOP;
    }

    pstVencAttr->u32MaxQp = pstVencSetting->u32MaxQp;

    if (NO_CONCERN_VALUE == pstVencAttr->u32MaxQp)
    {
        pstVencAttr->u32MaxQp = U32_MAX_QP;
    }

    pstVencAttr->u32MinQp = pstVencSetting->u32MinQp;

    if (NO_CONCERN_VALUE == pstVencAttr->u32MinQp)
    {
        pstVencAttr->u32MinQp = U32_MIN_QP;
    }

    pstVencAttr->bQuickEncode = hal_to_unf_for_bool(pstVencSetting->bQuickEncode);
    pstVencAttr->u32Qlevel = pstVencSetting->u32JpegQl;
    pstVencAttr->u32DriftRateThr = -1;
    pstVencAttr->u32SplitSize = pstVencSetting->u32SplitSize;

    return SUCCESS;
}

static U32 covert_param_aenc_type_to_unf(AV_AUD_STREAM_TYPE_E enHalType)
{
    switch (enHalType)
    {
        case AV_AUD_STREAM_TYPE_MP2:
        {
            return HA_AUDIO_ID_MP2;
        }

        case AV_AUD_STREAM_TYPE_MP3:
        {
            return HA_AUDIO_ID_MP3;
        }

        case AV_AUD_STREAM_TYPE_AAC:
        {
            return HA_AUDIO_ID_AAC;
        }

        default:
        {
            return HA_AUDIO_ID_AAC;
        }
    }
}

static S32 covert_param_aenc_setting_to_unf(HI_UNF_AENC_ATTR_S* pstAencAttr, const ENC_AENC_SETTINGS_S* const pstAencSetting, VOID* pstEncConfig)
{
    HI_U32 u32AencType = 0;

    if (ENC_OUTPUT_MEM != pstAencSetting->stOutputParams.enOutputType)
    {
        HAL_ERROR("UnSupported other output Type.");
        return ERROR_NOT_SUPPORTED;
    }

    if (ENC_OUTPUT_STREAM_FORMAT_NONE == pstAencSetting->enOutputStreamFormat)
    {
        HAL_ERROR("output stream format error");
        return ERROR_INVALID_PARAM;
    }

    u32AencType = covert_param_aenc_type_to_unf(pstAencSetting->enType);

    switch (u32AencType)
    {
        case HA_AUDIO_ID_AAC:
        {
            HA_AAC_GetDefaultConfig(pstEncConfig);
            HA_AAC_GetEncDefaultOpenParam(&(pstAencAttr->sOpenParam), pstEncConfig);
            break;
        }

        default:
        {
            HAL_ERROR("UnSupported other aenc type: [%d].", u32AencType);
            return ERROR_NOT_SUPPORTED;
        }
    }

    pstAencAttr->enAencType = u32AencType;
    pstAencAttr->sOpenParam.u32DesiredOutChannels = pstAencSetting->u32Channels;

    if (NO_CONCERN_VALUE == pstAencAttr->sOpenParam.u32DesiredOutChannels)
    {
        pstAencAttr->sOpenParam.u32DesiredOutChannels = DEFAULT_OUTPUT_CHANNELS;
    }

    pstAencAttr->sOpenParam.bInterleaved = hal_to_unf_for_bool(pstAencSetting->bInterleaved);
    pstAencAttr->sOpenParam.s32BitPerSample = pstAencSetting->u32BitPerSample;

    if (NO_CONCERN_VALUE == pstAencAttr->sOpenParam.s32BitPerSample)
    {
        pstAencAttr->sOpenParam.s32BitPerSample = DEFAULT_BITWIDTH_PER_SAMPLE;
    }

    pstAencAttr->sOpenParam.u32DesiredSampleRate = pstAencSetting->u32SampleRate;

    if (NO_CONCERN_VALUE == pstAencAttr->sOpenParam.u32DesiredSampleRate)
    {
        pstAencAttr->sOpenParam.u32DesiredSampleRate = DEFAULT_SAMPLE_RATE;
    }

    pstAencAttr->sOpenParam.u32SamplePerFrame = pstAencSetting->u32SamplePerFrame;

    return SUCCESS;
}

static S32 is_audio_type_support(AV_AUD_STREAM_TYPE_E enType)
{
    switch (enType)
    {
        case AV_AUD_STREAM_TYPE_AAC:
        {
            if (!s_bAACSupported)
            {
                HAL_DEBUG("AAC lib didn't load success");
                return ERROR_ENC_OP_FAILED;
            }

            break;
        }

        default:
        {
            HAL_ERROR("UnSupported aenc enType.");
            return ERROR_NOT_SUPPORTED;
        }
    }

    return SUCCESS;
}

static AV_VID_STREAM_TYPE_E covert_param_venc_type_to_hal(HI_UNF_VCODEC_TYPE_E enUnfType)
{
    switch (enUnfType)
    {
        case HI_UNF_VCODEC_TYPE_MPEG2:
        {
            return AV_VID_STREAM_TYPE_MPEG2;
        }

        case HI_UNF_VCODEC_TYPE_MPEG4:
        {
            return AV_VID_STREAM_TYPE_MPEG4;
        }

        case HI_UNF_VCODEC_TYPE_AVS:
        {
            return AV_VID_STREAM_TYPE_AVS;
        }

        case HI_UNF_VCODEC_TYPE_H263:
        {
            return AV_VID_STREAM_TYPE_H263;
        }

        case HI_UNF_VCODEC_TYPE_H264:
        {
            return AV_VID_STREAM_TYPE_H264;
        }

        case HI_UNF_VCODEC_TYPE_AVS2:
        {
            return AV_VID_STREAM_TYPE_AVS2;
        }

        case HI_UNF_VCODEC_TYPE_HEVC:
        {
            return AV_VID_STREAM_TYPE_HEVC;
        }

        default:
        {
            return AV_VID_STREAM_TYPE_BUTT;
        }
    }
}

static S32 covert_param_venc_setting_to_hal(ENC_VENC_SETTINGS_S* pstVencSetting, HI_UNF_VENC_CHN_ATTR_S* pstVencAttr)
{
    pstVencSetting->enType = covert_param_venc_type_to_hal(pstVencAttr->enVencType);
    pstVencSetting->u32Width = pstVencAttr->u32Width;
    pstVencSetting->u32Height = pstVencAttr->u32Height;
    pstVencSetting->bInterleaved = FALSE;
    pstVencSetting->u32OutputFrameRate = pstVencAttr->u32TargetFrmRate;
    pstVencSetting->u32InputFrameRate = pstVencAttr->u32InputFrmRate;
    pstVencSetting->u32BufSize = pstVencAttr->u32StrmBufSize;

    pstVencSetting->bSliceSplit = pstVencAttr->bSlcSplitEn;
    pstVencSetting->u32SplitSize = pstVencAttr->u32SplitSize;
    pstVencSetting->u32JpegQl = pstVencAttr->u32Qlevel;
    pstVencSetting->u32BitRate = pstVencAttr->u32TargetBitRate;
    pstVencSetting->u32Gop = pstVencAttr->u32Gop;
    pstVencSetting->u32MaxQp = pstVencAttr->u32MaxQp;
    pstVencSetting->u32MinQp = pstVencAttr->u32MinQp;
    pstVencSetting->bQuickEncode = pstVencAttr->bQuickEncode;
    return SUCCESS;
}

static AV_AUD_STREAM_TYPE_E covert_param_aenc_type_to_hal(HI_U32 enAencType)
{
    switch (enAencType)
    {
        case HA_AUDIO_ID_MP2:
        {
            return AV_AUD_STREAM_TYPE_MP2;
        }

        case HA_AUDIO_ID_MP3:
        {
            return AV_AUD_STREAM_TYPE_MP3;
        }

        case HA_AUDIO_ID_AAC:
        {
            return AV_AUD_STREAM_TYPE_AAC;
        }

        default:
        {
            return AV_AUD_STREAM_TYPE_BUTT;
        }
    }
}
static S32 covert_param_aenc_setting_to_hal(ENC_AENC_SETTINGS_S* pstAencSetting, HI_UNF_AENC_ATTR_S* pstAencAttr)
{
    pstAencSetting->enType = covert_param_aenc_type_to_hal(pstAencAttr->enAencType);
    pstAencSetting->u32BufSize = NO_CONCERN_VALUE;
    pstAencSetting->u32Channels = pstAencAttr->sOpenParam.u32DesiredOutChannels;
    pstAencSetting->u32BitPerSample = pstAencAttr->sOpenParam.s32BitPerSample;
    pstAencSetting->u32SampleRate = pstAencAttr->sOpenParam.u32DesiredSampleRate;
    pstAencSetting->bInterleaved = pstAencAttr->sOpenParam.bInterleaved;
    pstAencSetting->u32SamplePerFrame = pstAencAttr->sOpenParam.u32SamplePerFrame;

    return SUCCESS;
}

static ENC_MPEG4_PACK_TYPE_E covert_param_mpeg4_pack_type_to_hal(HI_UNF_MPEG4E_PACK_TYPE_E enMPEG4EType)
{
    switch (enMPEG4EType)
    {
        case HI_UNF_MPEG4E_PACK_VO:
        {
            return ENC_MPEG4_PACK_VO;
        }

        case HI_UNF_MPEG4E_PACK_VOS:
        {
            return ENC_MPEG4_PACK_VOS;
        }

        case HI_UNF_MPEG4E_PACK_VOL:
        {
            return ENC_MPEG4_PACK_VOL;
        }

        case HI_UNF_MPEG4E_PACK_VOP:
        {
            return ENC_MPEG4_PACK_VOP;
        }

        case HI_UNF_MPEG4E_PACK_SLICE:
        {
            return ENC_MPEG4_PACK_SLICE;
        }

        default:
        {
            return ENC_MPEG4_PACK_BUTT;
        }
    }
}

static ENC_H263_NALU_TYPE_E covert_param_h263_pack_type_to_hal(HI_UNF_H263E_PACK_TYPE_E enH263EType)
{
    switch (enH263EType)
    {
        case HI_UNF_H263E_NALU_PSLICE:
        {
            return ENC_H263_NALU_P_SLICE;
        }

        case HI_UNF_H263E_NALU_ISLICE:
        {
            return ENC_H263_NALU_I_SLICE;
        }

        case HI_UNF_H263E_NALU_SEI:
        {
            return ENC_H263_NALU_SEI;
        }

        case HI_UNF_H263E_NALU_SPS:
        {
            return ENC_H263_NALU_SPS;
        }

        case HI_UNF_H263E_NALU_PPS:
        {
            return ENC_H263_NALU_PPS;
        }

        default:
        {
            return ENC_H263_NALU_BUTT;
        }
    }
}

static ENC_H264_NALU_TYPE_E covert_param_h264_pack_type_to_hal(HI_UNF_H264E_NALU_TYPE_E enH264EType)
{
    switch (enH264EType)
    {
        case HI_UNF_H264E_NALU_PSLICE:
        {
            return ENC_H264_NALU_P_SLICE;
        }

        case HI_UNF_H264E_NALU_ISLICE:
        {
            return ENC_H264_NALU_I_SLICE;
        }

        case HI_UNF_H264E_NALU_SEI:
        {
            return ENC_H264_NALU_SEI;
        }

        case HI_UNF_H264E_NALU_SPS:
        {
            return ENC_H264_NALU_SPS;
        }

        case HI_UNF_H264E_NALU_PPS:
        {
            return ENC_H264_NALU_PPS;
        }

        default:
        {
            return ENC_H264_NALU_BUTT;
        }
    }
}

static ENC_HEVC_NALU_TYPE_E covert_param_hevc_pack_type_to_hal(HI_UNF_HEVCE_NALU_TYPE_E enHevcEType)
{
    switch (enHevcEType)
    {
        case HI_UNF_HEVCE_NALU_PSLICE:
        {
            return ENC_HEVC_NALU_P_SLICE;
        }

        case HI_UNF_HEVCE_NALU_ISLICE:
        {
            return ENC_HEVC_NALU_I_SLICE;
        }

        case HI_UNF_HEVCE_NALU_VPS:
        {
            return ENC_HEVC_NALU_VPS;
        }

        case HI_UNF_HEVCE_NALU_SEI:
        {
            return ENC_HEVC_NALU_SEI;
        }

        case HI_UNF_HEVCE_NALU_SPS:
        {
            return ENC_HEVC_NALU_SPS;
        }

        case HI_UNF_HEVCE_NALU_PPS:
        {
            return ENC_HEVC_NALU_PPS;
        }

        default:
        {
            return ENC_HEVC_NALU_BUTT;
        }
    }
}


static S32 covert_param_vid_data_to_hal(ENC_VID_ES_DATA_S* pstVidEsData, HI_UNF_VENC_STREAM_S* pstVencStream, HI_UNF_VCODEC_TYPE_E enVencType)
{
    pstVidEsData->pBuffer = pstVencStream->pu8Addr;
    pstVidEsData->u32Length = pstVencStream->u32SlcLen;
    pstVidEsData->u64Pts = (U64)pstVencStream->u32PtsMs * PTS_RATIO;
    pstVidEsData->bFrameEnd = pstVencStream->bFrameEnd;

    pstVidEsData->stDataType.enType = covert_param_venc_type_to_hal(enVencType);

    switch (enVencType)
    {
        case HI_UNF_VCODEC_TYPE_H264:
        {
            pstVidEsData->stDataType.uData.enH264 = covert_param_h264_pack_type_to_hal(pstVencStream->enDataType.enH264EType);
            break;
        }

        case HI_UNF_VCODEC_TYPE_MPEG4:
        {
            pstVidEsData->stDataType.uData.enMpeg4 = covert_param_mpeg4_pack_type_to_hal(pstVencStream->enDataType.enMPEG4EType);
            break;
        }

        case HI_UNF_VCODEC_TYPE_H263:
        {
            pstVidEsData->stDataType.uData.enH263 = covert_param_h263_pack_type_to_hal(pstVencStream->enDataType.enH263EType);
            break;
        }

        case HI_UNF_VCODEC_TYPE_HEVC:
        {
            pstVidEsData->stDataType.uData.enHevc = covert_param_hevc_pack_type_to_hal(pstVencStream->enDataType.enHEVCEType);
            break;
        }

        default:
        {
            HAL_ERROR("UnSupported other venc type: [%d].", enVencType);
            return ERROR_NOT_SUPPORTED;
        }
    }

    return SUCCESS;
}

static S32 covert_param_mpeg4_pack_type_to_unf(ENC_MPEG4_PACK_TYPE_E enMPEG4HALEType, HI_UNF_MPEG4E_PACK_TYPE_E *enMPEG4UNFEType)
{
    switch (enMPEG4HALEType)
    {
        case ENC_MPEG4_PACK_VO:
        {
             *enMPEG4UNFEType = HI_UNF_MPEG4E_PACK_VO;
             break;
        }

        case ENC_MPEG4_PACK_VOS:
        {
            *enMPEG4UNFEType = HI_UNF_MPEG4E_PACK_VOS;
            break;
        }

        case ENC_MPEG4_PACK_VOL:
        {
            *enMPEG4UNFEType = HI_UNF_MPEG4E_PACK_VOL;
            break;
        }

        case ENC_MPEG4_PACK_VOP:
        {
            *enMPEG4UNFEType = HI_UNF_MPEG4E_PACK_VOP;
            break;
        }

        case ENC_MPEG4_PACK_SLICE:
        {
            *enMPEG4UNFEType = HI_UNF_MPEG4E_PACK_SLICE;
            break;
        }

        default:
        {
            HAL_ERROR("covert hal mpeg4 packtype to unf err, enMPEG4EType: [%d]\n", enMPEG4HALEType);
            return ERROR_NOT_SUPPORTED;
        }
    }

    return SUCCESS;
}

static S32 covert_param_h263_pack_type_to_unf(ENC_H263_NALU_TYPE_E enH263HALEType, HI_UNF_H263E_PACK_TYPE_E *enH263UNFEType)
{
    switch (enH263HALEType)
    {
        case ENC_H263_NALU_P_SLICE:
        {
            *enH263UNFEType = HI_UNF_H263E_NALU_PSLICE;
            break;
        }

        case ENC_H263_NALU_I_SLICE:
        {
            *enH263UNFEType = HI_UNF_H263E_NALU_ISLICE;
            break;
        }

        case ENC_H263_NALU_SEI:
        {
            *enH263UNFEType = HI_UNF_H263E_NALU_SEI;
            break;
        }

        case ENC_H263_NALU_SPS:
        {
            *enH263UNFEType = HI_UNF_H263E_NALU_SPS;
            break;
        }

        case ENC_H263_NALU_PPS:
        {
            *enH263UNFEType = HI_UNF_H263E_NALU_PPS;
            break;
        }

        default:
        {
            *enH263UNFEType = HI_UNF_H263E_NALU_BUTT;
            break;
        }
    }

    return SUCCESS;
}

static S32 covert_param_h264_pack_type_to_unf(ENC_H264_NALU_TYPE_E enH264HALEType, HI_UNF_H264E_NALU_TYPE_E *enH264UNFEType)
{
    switch (enH264HALEType)
    {
        case ENC_H264_NALU_P_SLICE:
        {
            *enH264UNFEType = HI_UNF_H264E_NALU_PSLICE;
            break;
        }

        case ENC_H264_NALU_I_SLICE:
        {
            *enH264UNFEType = HI_UNF_H264E_NALU_ISLICE;
            break;
        }

        case ENC_H264_NALU_SEI:
        {
            *enH264UNFEType = HI_UNF_H264E_NALU_SEI;
            break;
        }

        case ENC_H264_NALU_SPS:
        {
            *enH264UNFEType = HI_UNF_H264E_NALU_SPS;
            break;
        }

        case ENC_H264_NALU_PPS:
        {
            *enH264UNFEType = HI_UNF_H264E_NALU_PPS;
            break;
        }

        default:
        {
            *enH264UNFEType = HI_UNF_H264E_NALU_BUTT;
            break;
        }
    }

    return SUCCESS;
}

static S32 covert_param_hevc_pack_type_to_unf(ENC_HEVC_NALU_TYPE_E enHevcHALEType, HI_UNF_HEVCE_NALU_TYPE_E *enHevcUNFEType)
{
    switch (enHevcHALEType)
    {
        case ENC_HEVC_NALU_P_SLICE:
        {
            *enHevcUNFEType = HI_UNF_HEVCE_NALU_PSLICE;
            break;
        }

        case ENC_HEVC_NALU_I_SLICE:
        {
            *enHevcUNFEType = HI_UNF_HEVCE_NALU_ISLICE;
            break;
        }

        case ENC_HEVC_NALU_VPS:
        {
            *enHevcUNFEType = HI_UNF_HEVCE_NALU_VPS;
            break;
        }

        case ENC_HEVC_NALU_SEI:
        {
            *enHevcUNFEType = HI_UNF_HEVCE_NALU_SEI;
            break;
        }

        case ENC_HEVC_NALU_SPS:
        {
            *enHevcUNFEType = HI_UNF_HEVCE_NALU_SPS;
            break;
        }

        case ENC_HEVC_NALU_PPS:
        {
            *enHevcUNFEType = HI_UNF_HEVCE_NALU_PPS;
            break;
        }

        default:
        {
            *enHevcUNFEType = HI_UNF_HEVCE_NALU_BUTT;
            break;
        }
    }

    return SUCCESS;
}


static S32 covert_param_vid_data_to_unf(ENC_VID_ES_DATA_S* pstVidEsData, HI_UNF_VENC_STREAM_S* pstVencStream)
{
    S32 Ret = FAILURE;
    pstVencStream->pu8Addr   = pstVidEsData->pBuffer;
    pstVencStream->u32SlcLen = pstVidEsData->u32Length;
    pstVencStream->u32PtsMs  = (U32)(pstVidEsData->u64Pts/PTS_RATIO);
    pstVencStream->bFrameEnd = pstVidEsData->bFrameEnd;

    switch (pstVidEsData->stDataType.enType)
    {
        case AV_VID_STREAM_TYPE_H264:
        {
            Ret = covert_param_h264_pack_type_to_unf(pstVidEsData->stDataType.uData.enH264, &(pstVencStream->enDataType.enH264EType));
            break;
        }

        case AV_VID_STREAM_TYPE_MPEG4:
        {
            Ret = covert_param_mpeg4_pack_type_to_unf(pstVidEsData->stDataType.uData.enMpeg4, &(pstVencStream->enDataType.enMPEG4EType));
            break;
        }

        case AV_VID_STREAM_TYPE_H263:
        {
            Ret = covert_param_h263_pack_type_to_unf(pstVidEsData->stDataType.uData.enH263, &(pstVencStream->enDataType.enH263EType));
            break;
        }

        case AV_VID_STREAM_TYPE_HEVC:
        {
            Ret = covert_param_hevc_pack_type_to_unf(pstVidEsData->stDataType.uData.enHevc, &(pstVencStream->enDataType.enHEVCEType));
            break;
        }

        default:
        {
            HAL_ERROR("covert param vid data to unf err!,venc type: [%d]\n", pstVidEsData->stDataType.enType);
            return ERROR_NOT_SUPPORTED;
        }
    }

    return Ret;
}


static S32 covert_param_aud_data_to_hal(ENC_AUD_ES_DATA_S* pstAudEsData, HI_UNF_ES_BUF_S* pstAencEsbuf)
{
    pstAudEsData->pBuffer = pstAencEsbuf->pu8Buf;
    pstAudEsData->u32Length = pstAencEsbuf->u32BufLen;
    pstAudEsData->u64Pts = (U64)pstAencEsbuf->u32PtsMs * PTS_RATIO;
    return SUCCESS;
}

static S32 covert_param_vid_format_to_unf_for_semiplannar(HI_UNF_VIDEO_FORMAT_E* penVideoFormat, ENC_COLOR_TYPE_E enColorType)
{
    switch (enColorType)
    {
        case ENC_COLOR_TYPE_YUV_420:
        {
            *penVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_420;
            break;
        }

        case ENC_COLOR_TYPE_YUV_422:
        {
            *penVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_422;
            break;
        }

        case ENC_COLOR_TYPE_YUV_444:
        {
            *penVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_444;
            break;
        }

        default:
        {
            *penVideoFormat = HI_UNF_FORMAT_RGB_BUTT;
            break;
        }
    }

    return SUCCESS;
}

static S32 covert_param_vid_format_to_unf_for_plannar(HI_UNF_VIDEO_FORMAT_E* penVideoFormat, ENC_COLOR_TYPE_E enColorType)
{
    switch (enColorType)
    {
        case ENC_COLOR_TYPE_YUV_420:
        {
            *penVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_420;
            break;
        }

        case ENC_COLOR_TYPE_YUV_422:
        {
            *penVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_422_1X2;
            break;
        }

        case ENC_COLOR_TYPE_YUV_444:
        {
            *penVideoFormat = HI_UNF_FORMAT_YUV_PLANAR_444;
            break;
        }

        default:
        {
            *penVideoFormat = HI_UNF_FORMAT_RGB_BUTT;
            break;
        }

    }

    return SUCCESS;
}

static S32 covert_param_vid_format_to_unf_for_package(HI_UNF_VIDEO_FORMAT_E* penVideoFormat, ENC_YUV_PACKAGE_SEQ_E enPackageSeq)
{
    switch (enPackageSeq)
    {
        case ENC_PACKAGE_UY0VY1:
        case ENC_PACKAGE_UY1VY0:
        {
            *penVideoFormat = HI_UNF_FORMAT_YUV_PACKAGE_UYVY;
            break;
        }

        case ENC_PACKAGE_Y0UY1V:
        case ENC_PACKAGE_Y1UY0V:
        {
            *penVideoFormat = HI_UNF_FORMAT_YUV_PACKAGE_YUYV;
            break;
        }

        case ENC_PACKAGE_Y0VY1U:
        case ENC_PACKAGE_Y1VY0U:
        {
            *penVideoFormat = HI_UNF_FORMAT_YUV_PACKAGE_YVYU;
            break;
        }

        default:
        {
            *penVideoFormat = HI_UNF_FORMAT_RGB_BUTT;
            break;
        }
    }

    return SUCCESS;
}

static S32 covert_param_vid_format_to_unf(HI_UNF_VIDEO_FORMAT_E* penVideoFormat, ENC_STORE_TYPE_E enStoreType, ENC_COLOR_TYPE_E enColorType, ENC_YUV_PACKAGE_SEQ_E enPackageSeq)
{
    switch (enStoreType)
    {
        case ENC_STORE_TYPE_SEMIPLANNAR:
        {
            (VOID)covert_param_vid_format_to_unf_for_semiplannar(penVideoFormat, enColorType);
            break;
        }

        case  ENC_STORE_TYPE_PLANNAR:
        {
            (VOID)covert_param_vid_format_to_unf_for_plannar(penVideoFormat, enColorType);
            break;
        }

        case ENC_STORE_TYPE_PACKAGE:
        {
            (VOID)covert_param_vid_format_to_unf_for_package(penVideoFormat, enPackageSeq);
            break;
        }

        default:
        {
            *penVideoFormat = HI_UNF_FORMAT_RGB_BUTT;
        }
    }

    return SUCCESS;
}

static S32 covert_param_vid_format_to_hal(ENC_STORE_TYPE_E* penStoreType, ENC_COLOR_TYPE_E* penColorType, ENC_YUV_PACKAGE_SEQ_E* penPackageSeq, HI_UNF_VIDEO_FORMAT_E enVideoFormat)
{
    switch (enVideoFormat)
    {
        case HI_UNF_FORMAT_YUV_SEMIPLANAR_422:
        {
            *penStoreType = ENC_STORE_TYPE_SEMIPLANNAR;
            *penColorType = ENC_COLOR_TYPE_YUV_422;
            break;
        }

        case HI_UNF_FORMAT_YUV_SEMIPLANAR_420:
        {
            *penStoreType = ENC_STORE_TYPE_SEMIPLANNAR;
            *penColorType = ENC_COLOR_TYPE_YUV_420;
            break;
        }

        case HI_UNF_FORMAT_YUV_SEMIPLANAR_444:
        {
            *penStoreType = ENC_STORE_TYPE_SEMIPLANNAR;
            *penColorType = ENC_COLOR_TYPE_YUV_444;
            break;
        }

        case HI_UNF_FORMAT_YUV_PACKAGE_UYVY:
        {
            *penStoreType = ENC_STORE_TYPE_PACKAGE;
            *penPackageSeq = ENC_PACKAGE_UY0VY1;
            break;
        }

        case HI_UNF_FORMAT_YUV_PACKAGE_YUYV:
        {
            *penStoreType = ENC_STORE_TYPE_PACKAGE;
            *penPackageSeq = ENC_PACKAGE_Y0UY1V;
            break;
        }

        case HI_UNF_FORMAT_YUV_PACKAGE_YVYU:
        {
            *penStoreType = ENC_STORE_TYPE_PACKAGE;
            *penPackageSeq = ENC_PACKAGE_Y0VY1U;
            break;
        }

        case HI_UNF_FORMAT_YUV_PLANAR_422_1X2:
        case HI_UNF_FORMAT_YUV_PLANAR_422_2X1:
        {
            *penStoreType = ENC_STORE_TYPE_PLANNAR;
            *penColorType = ENC_COLOR_TYPE_YUV_422;
            break;
        }

        case HI_UNF_FORMAT_YUV_PLANAR_420:
        {
            *penStoreType = ENC_STORE_TYPE_PLANNAR;
            *penColorType = ENC_COLOR_TYPE_YUV_420;
            break;
        }

        case HI_UNF_FORMAT_YUV_PLANAR_444:
        {
            *penStoreType = ENC_STORE_TYPE_PLANNAR;
            *penColorType = ENC_COLOR_TYPE_YUV_444;
            break;
        }

        default:
        {
            *penStoreType = ENC_STORE_TYPE_BUTT;
            *penColorType = ENC_COLOR_TYPE_BUTT;
            break;
        }
    }

    return SUCCESS;
}

static S32 covert_param_vid_field_type_to_unf(HI_UNF_VIDEO_FIELD_MODE_E* penFieldMode, ENC_VID_FIELD_TYPE_E enFieldType)
{
    switch (enFieldType)
    {
        case ENC_VID_FIELD_ALL:
        {
            *penFieldMode = HI_UNF_VIDEO_FIELD_ALL;
            break;
        }

        case ENC_VID_FIELD_TOP:
        {
            *penFieldMode = HI_UNF_VIDEO_FIELD_TOP;
            break;
        }

        case ENC_VID_FIELD_BOTTOM:
        {
            *penFieldMode = HI_UNF_VIDEO_FIELD_BOTTOM;
            break;
        }

        case ENC_VID_FIELD_BUTT:
        {
            *penFieldMode = HI_UNF_VIDEO_FIELD_BUTT;
            break;
        }

        default:
        {
            *penFieldMode = HI_UNF_VIDEO_FIELD_BUTT;
            break;
        }
    }

    return SUCCESS;
}

static S32 covert_param_vid_field_type_to_hal(ENC_VID_FIELD_TYPE_E* penFieldType, HI_UNF_VIDEO_FIELD_MODE_E enFieldMode)
{
    switch (enFieldMode)
    {
        case HI_UNF_VIDEO_FIELD_ALL:
        {
            *penFieldType = ENC_VID_FIELD_ALL;
            break;
        }

        case HI_UNF_VIDEO_FIELD_TOP:
        {
            *penFieldType = ENC_VID_FIELD_TOP;
            break;
        }

        case HI_UNF_VIDEO_FIELD_BOTTOM:
        {
            *penFieldType = ENC_VID_FIELD_BOTTOM;
            break;
        }

        case HI_UNF_VIDEO_FIELD_BUTT:
        {
            *penFieldType = ENC_VID_FIELD_BUTT;
            break;
        }

        default:
        {
            *penFieldType = ENC_VID_FIELD_BUTT;
            break;
        }
    }

    return SUCCESS;
}

static S32 covert_param_vid_frame_packing_type_to_unf(HI_UNF_VIDEO_FRAME_PACKING_TYPE_E* penFramePackingType, AV_3D_FORMAT_E enAvFormat)
{
    switch (enAvFormat)
    {
        case AV_3D_FORMAT_OFF:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_NONE;
            break;
        }

        case AV_3D_FORMAT_SIDE_BY_SIDE:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE;
            break;
        }

        case AV_3D_FORMAT_TOP_AND_BOTTOM:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM;
            break;
        }

        case AV_3D_FORMAT_SIDE_BY_SIDE_FULL:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE;
            break;
        }

        case AV_3D_FORMAT_FRAME_PACKING:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_FRAME_PACKING;
            break;
        }

        case AV_3D_FORMAT_FIELD_ALTERNATIVE:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED;
            break;
        }

        case AV_3D_FORMAT_LINE_ALTERNATIVE:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED;
            break;
        }

        case AV_3D_FORMAT_AUTO:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_3D_TILE;
            break;
        }

        case AV_3D_FORMAT_BUTT:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_BUTT;
            break;
        }

        default:
        {
            *penFramePackingType = HI_UNF_FRAME_PACKING_TYPE_BUTT;
            break;
        }
    }

    return SUCCESS;
}

static S32 covert_param_vid_frame_packing_type_to_hal(AV_3D_FORMAT_E* penAvFormat, HI_UNF_VIDEO_FRAME_PACKING_TYPE_E enFramePackingType)
{
    switch (enFramePackingType)
    {
        case HI_UNF_FRAME_PACKING_TYPE_NONE:
        {
            *penAvFormat = AV_3D_FORMAT_OFF;
            break;
        }

        case HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE:
        {
            *penAvFormat = AV_3D_FORMAT_SIDE_BY_SIDE;
            break;
        }

        case HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM:
        {
            *penAvFormat = AV_3D_FORMAT_TOP_AND_BOTTOM;
            break;
        }

        case HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED:
        {
            *penAvFormat = AV_3D_FORMAT_FIELD_ALTERNATIVE;
            break;
        }

        case HI_UNF_FRAME_PACKING_TYPE_FRAME_PACKING:
        {
            *penAvFormat = AV_3D_FORMAT_FRAME_PACKING;
            break;
        }

        case HI_UNF_FRAME_PACKING_TYPE_3D_TILE:
        {
            *penAvFormat = AV_3D_FORMAT_AUTO;
            break;
        }

        case HI_UNF_FRAME_PACKING_TYPE_BUTT:
        {
            *penAvFormat = AV_3D_FORMAT_BUTT;
            break;
        }

        default:
        {
            *penAvFormat = AV_3D_FORMAT_BUTT;
            break;
        }
    }

    return SUCCESS;
}

static S32 covert_param_vid_frame_addr_to_unf(const HANDLE hEnc, HI_UNF_VIDEO_FRAME_INFO_S* pstVideoFrameInfo, ENC_VENC_DATA_S* pstVencData)
{
    S32 s32Ret = FAILURE;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    U32 u32Offset = 0;
    U32 u32QueueIndex = 0;
    HI_MMZ_BUF_S* pstMmzBuf = NULL;

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, hEnc, &u32Index);

    // same handle for multi-thread need lock
    ENC_LOCK(&s_stVencHandle[u32Index].stVencQueueInfo.sameHandleQueueMutex);

    for (u32QueueIndex = 0; u32QueueIndex < VENC_MAX_QUEUE_NUM; u32QueueIndex++)
    {
        if (!s_stVencHandle[u32Index].stVencQueueInfo.stVencQueueMmz[u32QueueIndex].bMmzUsed)
        {
            pstMmzBuf = &s_stVencHandle[u32Index].stVencQueueInfo.stVencQueueMmz[u32QueueIndex].stHiMmzBuf;
            s_stVencHandle[u32Index].stVencQueueInfo.stVencQueueMmz[u32QueueIndex].bMmzUsed = TRUE;
            break;
        }
    }

    s32Ret = ERROR_ENC_NO_FREE_RESOURCE;
    HAL_CHK_GOTO((VENC_MAX_QUEUE_NUM == u32QueueIndex), ERROR_COVERT_ADDR, "queue buffer enough, plz dequeue buffer first.");
    HAL_CHK_GOTO((NULL == pstMmzBuf), ERROR_COVERT_ADDR, "can't get free venc queue slot.");

    memset(pstMmzBuf, 0, sizeof(HI_MMZ_BUF_S));

    s32Ret = ERROR_INVALID_PARAM;
    HAL_CHK_GOTO((0 == pstVencData->stAddr.u32YAddr), ERROR_COVERT_ADDR, "user mode video frame addr is null, plz check");

    snprintf(pstMmzBuf->bufname, MAX_BUFFER_NAME_SIZE, "%s", "VENC_MMZ");

    s32Ret = ERROR_ENC_OP_FAILED;

    if (ENC_STORE_TYPE_PLANNAR == pstVencData->enStoreType && ENC_COLOR_TYPE_YUV_420 == pstVencData->enColorType)
    {
        pstMmzBuf->bufsize = (ALIGN_UP(pstVencData->u32Width, 16) + ALIGN_UP(pstVencData->u32Width / 2, 16) ) * pstVencData->u32Height;
        hiS32Ret = HI_MMZ_Malloc(pstMmzBuf);
        HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), ERROR_COVERT_ADDR, "HI_MMZ_Malloc error, ret(0x%08x)", hiS32Ret);
        u32Offset = ALIGN_UP(pstVencData->u32Width, 16) * pstVencData->u32Height;
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CAddr = pstMmzBuf->phyaddr + u32Offset;
        u32Offset += (ALIGN_UP(pstVencData->u32Width / 2, 16) * pstVencData->u32Height) / 2;
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CrAddr = pstMmzBuf->phyaddr + u32Offset;
        pstVideoFrameInfo->stVideoFrameAddr[0].u32YStride = ALIGN_UP(pstVencData->u32Width, 16);
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CStride = ALIGN_UP(pstVencData->u32Width / 2, 16);
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CrStride = ALIGN_UP(pstVencData->u32Width / 2, 16);
    }
    else if (ENC_STORE_TYPE_SEMIPLANNAR == pstVencData->enStoreType && ENC_COLOR_TYPE_YUV_420 == pstVencData->enColorType)
    {
        pstMmzBuf->bufsize = ALIGN_UP(pstVencData->u32Width, 16) * pstVencData->u32Height * 3 / 2;
        hiS32Ret = HI_MMZ_Malloc(pstMmzBuf);
        HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), ERROR_COVERT_ADDR, "HI_MMZ_Malloc error, ret(0x%08x)", hiS32Ret);
        u32Offset = ALIGN_UP(pstVencData->u32Width, 16) * pstVencData->u32Height;
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CAddr = pstMmzBuf->phyaddr + u32Offset;
        pstVideoFrameInfo->stVideoFrameAddr[0].u32YStride = ALIGN_UP(pstVencData->u32Width, 16);
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CStride = ALIGN_UP(pstVencData->u32Width, 16);
    }
    else if (ENC_STORE_TYPE_PACKAGE == pstVencData->enStoreType && ENC_COLOR_TYPE_YUV_422 == pstVencData->enColorType)
    {
        pstMmzBuf->bufsize = ALIGN_UP(pstVencData->u32Width, 16) * pstVencData->u32Height * 2;
        hiS32Ret = HI_MMZ_Malloc(pstMmzBuf);
        HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), ERROR_COVERT_ADDR, "HI_MMZ_Malloc error, ret(0x%08x)", hiS32Ret);
        u32Offset = ALIGN_UP(pstVencData->u32Width * 2, 16) * pstVencData->u32Height;
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CAddr = pstMmzBuf->phyaddr + u32Offset;
        pstVideoFrameInfo->stVideoFrameAddr[0].u32YStride = ALIGN_UP(pstVencData->u32Width * 2, 16);
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CStride = 0;
    }
    else if (ENC_STORE_TYPE_SEMIPLANNAR == pstVencData->enStoreType && ENC_COLOR_TYPE_YUV_422 == pstVencData->enColorType)
    {
        pstMmzBuf->bufsize = ALIGN_UP(pstVencData->u32Width, 16) * pstVencData->u32Height * 2;
        hiS32Ret = HI_MMZ_Malloc(pstMmzBuf);
        HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), ERROR_COVERT_ADDR, "HI_MMZ_Malloc error, ret(0x%08x)", hiS32Ret);
        u32Offset = ALIGN_UP(pstVencData->u32Width, 16) * pstVencData->u32Height;
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CAddr = pstMmzBuf->phyaddr + u32Offset;
        pstVideoFrameInfo->stVideoFrameAddr[0].u32YStride = ALIGN_UP(pstVencData->u32Width, 16);
        pstVideoFrameInfo->stVideoFrameAddr[0].u32CStride = ALIGN_UP(pstVencData->u32Width / 2, 16);
    }
    else
    {
        HAL_ERROR("UnSupported yuv store type[%d][%d]", pstVencData->enStoreType, pstVencData->enColorType);
        s32Ret = ERROR_NOT_SUPPORTED;
        goto ERROR_COVERT_ADDR;
    }

    pstVideoFrameInfo->stVideoFrameAddr[0].u32YAddr = pstMmzBuf->phyaddr;

    s32Ret = ERROR_INVALID_PARAM;
    HAL_CHK_GOTO((pstVencData->stAddr.u32YStride < pstMmzBuf->bufsize), ERROR_FREE_MMZ, "user mode video frame length not enough");

    memcpy(pstMmzBuf->user_viraddr, (U8*)NULL + pstVencData->stAddr.u32YAddr, pstMmzBuf->bufsize);

    ENC_UNLOCK(&s_stVencHandle[u32Index].stVencQueueInfo.sameHandleQueueMutex);

    return SUCCESS;
ERROR_FREE_MMZ:
    hiS32Ret = HI_MMZ_Free(pstMmzBuf);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_MMZ_Free error, ret(0x%08x)", hiS32Ret);

ERROR_COVERT_ADDR:
    ENC_UNLOCK(&s_stVencHandle[u32Index].stVencQueueInfo.sameHandleQueueMutex);
    return s32Ret;
}

static S32 covert_param_venc_data_to_unf(const HANDLE hEnc, HI_UNF_VIDEO_FRAME_INFO_S* pstVideoFrameInfo, ENC_VENC_DATA_S* pstVencData)
{
    S32 s32Ret = FAILURE;
    pstVideoFrameInfo->u32FrameIndex = pstVencData->u32FrameIndex;

    pstVideoFrameInfo->u32Width = pstVencData->u32Width;
    pstVideoFrameInfo->u32Height = pstVencData->u32Height;

    pstVideoFrameInfo->u32Pts = pstVencData->u64Pts / PTS_RATIO;

    // for example: in hal: frameRate = 1234, in SDK: frameRate = {1, 234}
    pstVideoFrameInfo->stFrameRate.u32fpsInteger = pstVencData->u32FrameRate / 1000;
    pstVideoFrameInfo->stFrameRate.u32fpsDecimal = pstVencData->u32FrameRate % 1000;

    (VOID)covert_param_vid_format_to_unf(&pstVideoFrameInfo->enVideoFormat, pstVencData->enStoreType, pstVencData->enColorType, pstVencData->enPackageSeq);

    pstVideoFrameInfo->bProgressive = HI_FALSE;
    (VOID)covert_param_vid_field_type_to_unf(&pstVideoFrameInfo->enFieldMode, pstVencData->enFieldType);

    pstVideoFrameInfo->bTopFieldFirst = hal_to_unf_for_bool(pstVencData->bTopFieldFirst);

    (VOID)covert_param_vid_frame_packing_type_to_unf(&pstVideoFrameInfo->enFramePackingType, pstVencData->en3dFormat);

    pstVideoFrameInfo->u32Circumrotate = 0;

    s32Ret = covert_param_vid_frame_addr_to_unf(hEnc, pstVideoFrameInfo, pstVencData);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "covert_param_vid_frame_addr_to_unf error, ret(0x%08x)", s32Ret);

    return SUCCESS;
}

static S32 covert_param_venc_data_to_hal(ENC_VENC_DATA_S* pstVencData, HI_UNF_VIDEO_FRAME_INFO_S* pstVideoFrameInfo)
{
    pstVencData->u32Width = pstVideoFrameInfo->u32Width;
    pstVencData->u32Height = pstVideoFrameInfo->u32Height;

    pstVencData->bInterleaved = FALSE;
    pstVencData->u32FrameRate = pstVideoFrameInfo->stFrameRate.u32fpsInteger * 1000 + pstVideoFrameInfo->stFrameRate.u32fpsDecimal;
    (VOID)covert_param_vid_format_to_hal(&pstVencData->enStoreType, &pstVencData->enColorType, &pstVencData->enPackageSeq, pstVideoFrameInfo->enVideoFormat);

    (VOID)covert_param_vid_field_type_to_hal(&pstVencData->enFieldType, pstVideoFrameInfo->enFieldMode);
    (VOID)covert_param_vid_frame_packing_type_to_hal(&pstVencData->en3dFormat, pstVideoFrameInfo->enFramePackingType);

    pstVencData->bTopFieldFirst = pstVideoFrameInfo->bTopFieldFirst;
    pstVencData->u32FrameIndex = pstVideoFrameInfo->u32FrameIndex;
    pstVencData->u64Pts = (U64)pstVideoFrameInfo->u32Pts * PTS_RATIO;

    pstVencData->stAddr.u32YAddr = pstVideoFrameInfo->stVideoFrameAddr[0].u32YAddr;
    pstVencData->stAddr.u32CAddr = pstVideoFrameInfo->stVideoFrameAddr[0].u32CAddr;
    pstVencData->stAddr.u32CrAddr = pstVideoFrameInfo->stVideoFrameAddr[0].u32CrAddr;
    pstVencData->stAddr.u32YStride = pstVideoFrameInfo->stVideoFrameAddr[0].u32YStride;
    pstVencData->stAddr.u32CStride = pstVideoFrameInfo->stVideoFrameAddr[0].u32CStride;
    pstVencData->stAddr.u32CrStride = pstVideoFrameInfo->stVideoFrameAddr[0].u32CrStride;

    return SUCCESS;
}

static void clearVencHandleInfo(const U32 u32Index)
{
    U32 u32QueueIndex = 0;

    if (u32Index < VENC_MAX_COUNT)
    {
        s_stVencHandle[u32Index].hVencHandle = INVALID_HANDLE;
        s_stVencHandle[u32Index].hVirtualWin = INVALID_HANDLE;
        s_stVencHandle[u32Index].hCast = INVALID_HANDLE;
        memset(&s_stVencHandle[u32Index].stVencExtraInfo, 0, sizeof(VENC_EXTRA_INFO_S));
        s_stVencHandle[u32Index].bUsed = FALSE;
        s_stVencHandle[u32Index].bAbortFlag = FALSE;

        for (u32QueueIndex = 0; u32QueueIndex < VENC_MAX_QUEUE_NUM; u32QueueIndex++)
        {
            memset(&s_stVencHandle[u32Index].stVencQueueInfo.stVencQueueMmz[u32QueueIndex].stHiMmzBuf, 0, sizeof(HI_MMZ_BUF_S));
            s_stVencHandle[u32Index].stVencQueueInfo.stVencQueueMmz[u32QueueIndex].bMmzUsed = FALSE;
        }

        pthread_mutex_init(&s_stVencHandle[u32Index].stVencQueueInfo.sameHandleQueueMutex, NULL);
    }
}

static void clearAencHandleInfo(const U32 u32Index)
{
    if (u32Index < AENC_MAX_COUNT)
    {
        s_stAencHandle[u32Index].hAencHandle = INVALID_HANDLE;
        s_stAencHandle[u32Index].hVirtualTrack = INVALID_HANDLE;
        s_stAencHandle[u32Index].hAudCast = INVALID_HANDLE;
        memset(&s_stAencHandle[u32Index].stAencExtraInfo, 0, sizeof(AENC_EXTRA_INFO_S));
        s_stAencHandle[u32Index].bUsed = FALSE;
        s_stAencHandle[u32Index].bAbortFlag = FALSE;
    }
}

static void initAllVencHandleInfo()
{
    U32 u32Index = 0;

    for (u32Index = 0; u32Index < VENC_MAX_COUNT; u32Index++)
    {
        clearVencHandleInfo(u32Index);
    }
}

static void  initAllAencHandleInfo()
{
    U32 u32Index = 0;

    for (u32Index = 0; u32Index < AENC_MAX_COUNT; u32Index++)
    {
        clearAencHandleInfo(u32Index);
    }
}

static S32 find_free_enc_handle_index(const ENC_ENCODER_TYPE_E enEncType, U32* u32Count)
{
    U32 u32Index = 0;

    if (ENC_ENCODE_VIDEO == enEncType)
    {
        for (u32Index = 0; u32Index < VENC_MAX_COUNT; u32Index++)
        {
            if ( (INVALID_HANDLE == s_stVencHandle[u32Index].hVencHandle)
                 || (FALSE == s_stVencHandle[u32Index].bUsed))
            {
                *u32Count = u32Index;
                return SUCCESS;
            }
        }
    }
    else if (ENC_ENCODE_AUDIO == enEncType)
    {
        for (u32Index = 0; u32Index < AENC_MAX_COUNT; u32Index++)
        {
            if ( (INVALID_HANDLE == s_stAencHandle[u32Index].hAencHandle)
                 || (FALSE == s_stAencHandle[u32Index].bUsed))
            {
                *u32Count = u32Index;
                return SUCCESS;
            }
        }
    }

    return ERROR_ENC_NO_FREE_RESOURCE;
}


static S32 attach_venc_avplay(HANDLE vencHandle)
{
    S32 s32Ret = FAILURE;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    HANDLE hAv = INVALID_HANDLE;
    HANDLE hAvSdk = INVALID_HANDLE;
    HI_UNF_WINDOW_ATTR_S stVoWinAttr;
    memset(&stVoWinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, vencHandle, &u32Index);

    hAv = s_stVencHandle[u32Index].stVencExtraInfo.stVencSrcPara.uSource.hAv;

    CHECK_NULL_PARAM(hAv);

    s32Ret = av_get_sdk_avplay_hdl(hAv, &hAvSdk);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "av_get_sdk_avplay_hdl error, ret(0x%08x)", s32Ret);

    // create virtual window
    stVoWinAttr.bVirtual = HI_TRUE;
    stVoWinAttr.stWinAspectAttr.enAspectCvrs = HI_UNF_VO_ASPECT_CVRS_IGNORE;
    stVoWinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    stVoWinAttr.enVideoFormat = HI_UNF_FORMAT_YUV_SEMIPLANAR_420;
    stVoWinAttr.bUseCropRect = HI_FALSE;
    stVoWinAttr.enDisp = HI_UNF_DISPLAY0;

    hiS32Ret = HI_UNF_VO_CreateWindow(&stVoWinAttr, &s_stVencHandle[u32Index].hVirtualWin);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), VENC_DESTORY, "HI_UNF_VO_CreateWindow error, ret(0x%08x)", hiS32Ret);

    // attach avplay -> virtual window
    hiS32Ret = HI_UNF_VO_AttachWindow(s_stVencHandle[u32Index].hVirtualWin, hAvSdk);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), VO_DESTORY, "HI_UNF_VO_AttachWindow error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_VO_SetWindowEnable(s_stVencHandle[u32Index].hVirtualWin, HI_TRUE);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), VO_DETACH, "HI_UNF_VO_SetWindowEnable error, ret(0x%08x)", hiS32Ret);

    // attach virtual window -> venc
    hiS32Ret = HI_UNF_VENC_AttachInput(vencHandle, s_stVencHandle[u32Index].hVirtualWin);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), VO_DETACH, "HI_UNF_VENC_AttachInput error, ret(0x%08x)", hiS32Ret);

    return SUCCESS;

VO_DETACH:
    hiS32Ret = HI_UNF_VO_DetachWindow(s_stVencHandle[u32Index].hVirtualWin, hAvSdk);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_VO_DetachWindow error, ret(0x%08x)", hiS32Ret);

VO_DESTORY:
    hiS32Ret = HI_UNF_VO_DestroyWindow(s_stVencHandle[u32Index].hVirtualWin);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_VO_DestroyWindow error, ret(0x%08x)", hiS32Ret);

    ENC_LOCK(&s_enc_mutex);
    s_stVencHandle[u32Index].hVirtualWin = INVALID_HANDLE;
    ENC_UNLOCK(&s_enc_mutex);

VENC_DESTORY:

    if (SUCCESS == s32Ret)
    {
        s32Ret = ERROR_ENC_OP_FAILED;
    }

    return s32Ret;
}

static S32 covert_param_vout_display_channel_to_unf(HI_UNF_DISP_E* const penUnfDispType, VOUT_DISPLAY_CHANNEL_E enHalType)
{
    /* display channel convert */
    switch (enHalType)
    {
        case VOUT_DISPLAY_HD0:
        case VOUT_DISPLAY_SD0:
        {
            *penUnfDispType = HI_UNF_DISPLAY0;
            break;
        }

        case VOUT_DISPLAY_HD1:
        {
            *penUnfDispType = HI_UNF_DISPLAY1;
            break;
        }

        case VOUT_DISPLAY_HD2:
        case VOUT_DISPLAY_SD2:
        {
            *penUnfDispType = HI_UNF_DISPLAY2;
            break;
        }

        default:
        {
            HAL_ERROR("UnSupported display channel.");
            return ERROR_NOT_SUPPORTED;
        }
    }

    return SUCCESS;
}

static S32 attach_venc_display(HANDLE vencHandle)
{
    S32 s32Ret = ERROR_ENC_OP_FAILED;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;;
    HI_UNF_DISP_E enUnfDispType = HI_UNF_DISPLAY_BUTT;
    HI_UNF_DISP_CAST_ATTR_S stCfg;
    memset(&stCfg, 0, sizeof(HI_UNF_DISP_CAST_ATTR_S));

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, vencHandle, &u32Index);

    // switch DISPLAY
    s32Ret = covert_param_vout_display_channel_to_unf(&enUnfDispType, s_stVencHandle[u32Index].stVencExtraInfo.stVencSrcPara.uSource.enDisplayChanel);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "convert_dispchannel_type error, ret(0x%08x)", s32Ret);

    hiS32Ret = HI_UNF_DISP_Init();
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), VENC_DESTORY, "HI_UNF_DISP_Init error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_DISP_GetDefaultCastAttr(enUnfDispType, &stCfg);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), VENC_DESTORY, "HI_UNF_DISP_GetDefaultCastAttr error, ret(0x%08x)", hiS32Ret);

    s32Ret = cfg_enc_set_default_cast_attr(&stCfg);
    HAL_CHK_GOTO((SUCCESS != s32Ret), VENC_DESTORY, "cfg_enc_set_default_cast_attr error, ret(0x%08x)", s32Ret);

    hiS32Ret = HI_UNF_DISP_CreateCast(enUnfDispType, &stCfg, &s_stVencHandle[u32Index].hCast);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), DISP_DEINIT, "HI_UNF_DISP_CreateCast error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_DISP_SetCastEnable(s_stVencHandle[u32Index].hCast, HI_TRUE);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), DISP_CAST_DESTROY, "HI_UNF_DISP_SetCastEnable error, ret(0x%08x)", hiS32Ret);

    // attach cast -> venc
    hiS32Ret = HI_UNF_VENC_AttachInput(vencHandle, s_stVencHandle[u32Index].hCast);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), DISP_CAST_DESTROY, "HI_UNF_VENC_AttachInput error, ret(0x%08x)", hiS32Ret);

    return SUCCESS;

DISP_CAST_DESTROY:
    hiS32Ret = HI_UNF_DISP_DestroyCast(s_stVencHandle[u32Index].hCast);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_DISP_DestroyCast error, ret(0x%08x)", hiS32Ret);

DISP_DEINIT:
    hiS32Ret = HI_UNF_DISP_DeInit();
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_DISP_DeInit error, ret(0x%08x)", hiS32Ret);

VENC_DESTORY:

    if (SUCCESS == s32Ret)
    {
        s32Ret = ERROR_ENC_OP_FAILED;
    }

    return s32Ret;
}

static S32 attach_aenc_avplay(HANDLE aencHandle)
{
    S32 s32Ret = FAILURE;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    HANDLE hAv = INVALID_HANDLE;
    HANDLE hAvSdk = INVALID_HANDLE;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;
    memset(&stTrackAttr, 0, sizeof(HI_UNF_AUDIOTRACK_ATTR_S));

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, aencHandle, &u32Index);

    hAv = s_stAencHandle[u32Index].stAencExtraInfo.stAencSrcPara.uSource.hAv;

    CHECK_NULL_PARAM(hAv);

    s32Ret = av_get_sdk_avplay_hdl(hAv, &hAvSdk);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "av_get_sdk_avplay_hdl error, ret(0x%08x)", s32Ret);

    hiS32Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_VIRTUAL, &stTrackAttr);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), AENC_DESTORY, "HI_UNF_SND_GetDefaultTrackAttr error, ret(0x%08x)", hiS32Ret);

    s32Ret = cfg_enc_set_default_track_attr(&stTrackAttr);
    HAL_CHK_GOTO((SUCCESS != s32Ret), AENC_DESTORY, "cfg_enc_set_default_track_attr error, ret(0x%08x)", s32Ret);

    hiS32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &s_stAencHandle[u32Index].hVirtualTrack);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), AENC_DESTORY, "HI_UNF_SND_CreateTrack error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_SND_Attach(s_stAencHandle[u32Index].hVirtualTrack, hAvSdk);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), VIRTUAL_TRACK_DESTROY, "HI_UNF_SND_Attach error, ret(0x%08x)", hiS32Ret);

    hiS32Ret =  HI_UNF_AENC_AttachInput(aencHandle, s_stAencHandle[u32Index].hVirtualTrack);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), VIRTUAL_TRACK_DETACH, "HI_UNF_AENC_AttachInput error, ret(0x%08x)", hiS32Ret);

    return SUCCESS;

VIRTUAL_TRACK_DETACH:
    hiS32Ret = HI_UNF_SND_Detach(s_stAencHandle[u32Index].hVirtualTrack, hAvSdk);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_SND_Detach error, ret(0x%08x)", hiS32Ret);

VIRTUAL_TRACK_DESTROY:
    hiS32Ret = HI_UNF_SND_DestroyTrack(s_stAencHandle[u32Index].hVirtualTrack);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_SND_DestroyTrack error, ret(0x%08x)", hiS32Ret);

    ENC_LOCK(&s_enc_mutex);
    s_stAencHandle[u32Index].hVirtualTrack = INVALID_HANDLE;
    ENC_UNLOCK(&s_enc_mutex);

AENC_DESTORY:

    if (SUCCESS == s32Ret)
    {
        s32Ret = ERROR_ENC_OP_FAILED;
    }

    return s32Ret;
}

static HI_S32 init_snd(HI_UNF_SND_E enSnd)
{
    HI_S32 hiS32Ret = HI_FAILURE;
    HI_UNF_SND_ATTR_S stAttr;

    memset(&stAttr, 0x00, sizeof(HI_UNF_SND_ATTR_S));

    hiS32Ret = HI_UNF_SND_Init();
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), hiS32Ret, "HI_UNF_SND_Init error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_SND_GetDefaultOpenAttr(enSnd, &stAttr);
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), hiS32Ret, "HI_UNF_SND_GetDefaultOpenAttr error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_SND_Open(enSnd, &stAttr);
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), hiS32Ret, "HI_UNF_SND_Open error, ret(0x%08x)", hiS32Ret);

    return HI_SUCCESS;
}

static HI_S32 deinit_snd(HI_UNF_SND_E enSnd)
{
    HI_S32 hiS32Ret = HI_FAILURE;

    hiS32Ret = HI_UNF_SND_Close(enSnd);
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), hiS32Ret, "HI_UNF_SND_Close error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_SND_DeInit();
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), hiS32Ret, "HI_UNF_SND_DeInit error, ret(0x%08x)", hiS32Ret);

    return HI_SUCCESS;
}

static HI_UNF_SND_E convert_aout_id_to_unf(AOUT_ID_E enAoutID)
{
    switch (enAoutID)
    {
        case AOUT_ID_0:
            return HI_UNF_SND_0;

        case AOUT_ID_1:
            return HI_UNF_SND_1;

        case AOUT_ID_2:
            return HI_UNF_SND_2;

        case AOUT_ID_3:
            return HI_UNF_SND_BUTT;

        default:
            return HI_UNF_SND_BUTT;
    }
}

static S32 attach_aenc_snd(HANDLE aencHandle)
{
    HI_S32 hiS32Ret = HI_FAILURE;
    HI_UNF_SND_E enSnd = HI_UNF_SND_BUTT;
    U32 u32Index = 0;
    HI_UNF_SND_CAST_ATTR_S stCastAttr;

    memset(&stCastAttr, 0x00, sizeof(HI_UNF_SND_CAST_ATTR_S));

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, aencHandle, &u32Index);

    AOUT_ID_E enAoutId = s_stAencHandle[u32Index].stAencExtraInfo.stAencSrcPara.uSource.enAoutId;

    // AOUT_ID_E -> HI_UNF_SND_E
    enSnd = convert_aout_id_to_unf(enAoutId);
    HAL_CHK_GOTO((HI_UNF_SND_BUTT == enSnd), AENC_DESTORY, "convert_aout_id_to_unf error, aout id[%d]", enAoutId);

    hiS32Ret = init_snd(enSnd);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), AENC_DESTORY, "init_snd error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_SND_GetDefaultCastAttr(enSnd, &stCastAttr);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), AENC_DESTORY, "HI_UNF_SND_GetDefaultCastAttr error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_SND_CreateCast(enSnd, &stCastAttr, &s_stAencHandle[u32Index].hAudCast);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), SND_DEINIT, "HI_UNF_SND_CreateCast error, ret(0x%08x)", hiS32Ret);

    HAL_DEBUG("Create Cast Success");

    hiS32Ret = HI_UNF_AENC_AttachInput(aencHandle, s_stAencHandle[u32Index].hAudCast);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), CAST_DESTORY, "HI_UNF_AENC_AttachInput error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_SND_SetCastEnable(s_stAencHandle[u32Index].hAudCast, HI_TRUE);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), CAST_DESTORY, "HI_UNF_SND_SetCastEnable error, ret(0x%08x)", hiS32Ret);

    HAL_DEBUG("Attach Cast Success");
    return SUCCESS;

CAST_DESTORY:
    hiS32Ret = HI_UNF_SND_DestroyCast(s_stAencHandle[u32Index].hAudCast);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_SND_DestroyCast error, ret(0x%08x)", hiS32Ret);

SND_DEINIT:
    hiS32Ret = deinit_snd(enSnd);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "deinit_snd error, ret(0x%08x)", hiS32Ret);

AENC_DESTORY:
    return ERROR_ENC_OP_FAILED;
}

static S32 dettach_venc_avplay(HANDLE vencHandle)
{
    S32 s32Ret = FAILURE;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    HANDLE hAv = INVALID_HANDLE;
    HANDLE hAvSdk = INVALID_HANDLE;

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, vencHandle, &u32Index);

    hiS32Ret = HI_UNF_VO_SetWindowEnable(s_stVencHandle[u32Index].hVirtualWin, HI_FALSE);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_VO_SetWindowEnable error, ret(0x%08x)", hiS32Ret);

    hAv = s_stVencHandle[u32Index].stVencExtraInfo.stVencSrcPara.uSource.hAv;

    CHECK_NULL_PARAM(hAv);

    s32Ret = av_get_sdk_avplay_hdl(hAv, &hAvSdk);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "av_get_sdk_avplay_hdl error, ret(0x%08x)", s32Ret);

    hiS32Ret = HI_UNF_VO_DetachWindow(s_stVencHandle[u32Index].hVirtualWin, hAvSdk);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_VO_DetachWindow error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_VENC_DetachInput(vencHandle);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_VENC_DetachInput error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_VO_DestroyWindow(s_stVencHandle[u32Index].hVirtualWin);
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VO_DestroyWindow error, ret(0x%08x)", hiS32Ret);

    ENC_LOCK(&s_enc_mutex);
    s_stVencHandle[u32Index].hVirtualWin = INVALID_HANDLE;
    ENC_UNLOCK(&s_enc_mutex);

    return SUCCESS;
}

static S32 dettach_venc_display(HANDLE vencHandle)
{
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, vencHandle, &u32Index);

    hiS32Ret = HI_UNF_VENC_DetachInput(vencHandle);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_VENC_DetachInput error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_DISP_DestroyCast(s_stVencHandle[u32Index].hCast);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_DISP_DestroyCast error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_DISP_DeInit();
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_DISP_DeInit error, ret(0x%08x)", hiS32Ret);

    ENC_LOCK(&s_enc_mutex);
    s_stVencHandle[u32Index].hCast = INVALID_HANDLE;
    ENC_UNLOCK(&s_enc_mutex);

    return SUCCESS;
}

static S32 dettach_venc_source(HANDLE vencHandle)
{
    U32 u32Index = 0;

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, vencHandle, &u32Index);

    switch (s_stVencHandle[u32Index].stVencExtraInfo.stVencSrcPara.enSourceType)
    {
        case ENC_SOURCE_DECODER:
        {
            return dettach_venc_avplay(vencHandle);
        }

        case ENC_SOURCE_MEM:
        {
            return SUCCESS;
        }

        case ENC_SOURCE_FILE:
        {
            HAL_ERROR("venc UnSupported FILE source type");
            return ERROR_NOT_SUPPORTED;
        }

        case ENC_SOURCE_AOUT:
        {
            HAL_ERROR("venc UnSupported AOUT source type");
            return ERROR_NOT_SUPPORTED;
        }

        case ENC_SOURCE_VOUT:
        {
            return dettach_venc_display(vencHandle);
        }

        case ENC_SOURCE_SOURCE:
        {
            HAL_ERROR("venc UnSupported SOURCE source type");
            return ERROR_NOT_SUPPORTED;
        }

        default:
        {
            HAL_ERROR("venc wrong source type.");
            return ERROR_INVALID_PARAM;
        }
    }

    return SUCCESS;
}

static S32 dettach_aenc_avplay(HANDLE aencHandle)
{
    S32 s32Ret = FAILURE;
    HANDLE hAv = INVALID_HANDLE;
    HANDLE hAvSdk = INVALID_HANDLE;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, aencHandle, &u32Index);

    hiS32Ret = HI_UNF_AENC_DetachInput(aencHandle);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_AENC_DetachInput error, ret(0x%08x)", hiS32Ret);

    hAv = s_stAencHandle[u32Index].stAencExtraInfo.stAencSrcPara.uSource.hAv;

    CHECK_NULL_PARAM(hAv);

    s32Ret = av_get_sdk_avplay_hdl(hAv, &hAvSdk);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "av_get_sdk_avplay_hdl error, ret(0x%08x)", s32Ret);

    hiS32Ret = HI_UNF_SND_Detach(s_stAencHandle[u32Index].hVirtualTrack, hAvSdk);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_SND_Detach error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_SND_DestroyTrack(s_stAencHandle[u32Index].hVirtualTrack);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_SND_DestroyTrack error, ret(0x%08x)", hiS32Ret);

    ENC_LOCK(&s_enc_mutex);
    s_stAencHandle[u32Index].hVirtualTrack = INVALID_HANDLE;
    ENC_UNLOCK(&s_enc_mutex);

    return SUCCESS;
}

static S32 dettach_aenc_snd(HANDLE aencHandle)
{
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, aencHandle, &u32Index);

    hiS32Ret = HI_UNF_AENC_DetachInput(aencHandle);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_AENC_DetachInput error, ret(0x%08x)", hiS32Ret);

    hiS32Ret = HI_UNF_SND_DestroyCast(s_stAencHandle[u32Index].hAudCast);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_SND_DestroyCast error, ret(0x%08x)", hiS32Ret);

    AOUT_ID_E enAoutId = s_stAencHandle[u32Index].stAencExtraInfo.stAencSrcPara.uSource.enAoutId;
    // AOUT_ID_E -> HI_UNF_SND_E
    HI_UNF_SND_E enSnd = convert_aout_id_to_unf(enAoutId);
    hiS32Ret = deinit_snd(enSnd);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "deinit_snd error, ret(0x%08x)", hiS32Ret);

    ENC_LOCK(&s_enc_mutex);
    s_stAencHandle[u32Index].hAudCast = INVALID_HANDLE;
    ENC_UNLOCK(&s_enc_mutex);

    return SUCCESS;
}

static S32 dettach_aenc_source(HANDLE aencHandle)
{
    U32 u32Index = 0;

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, aencHandle, &u32Index);

    switch (s_stAencHandle[u32Index].stAencExtraInfo.stAencSrcPara.enSourceType)
    {
        case ENC_SOURCE_DECODER:
        {
            return dettach_aenc_avplay(aencHandle);
        }

        case ENC_SOURCE_MEM:
        {
            return SUCCESS;
        }

        case ENC_SOURCE_FILE:
        {
            HAL_ERROR("aenc UnSupported FILE source type");
            return ERROR_NOT_SUPPORTED;
        }

        case ENC_SOURCE_AOUT:
        {
            return dettach_aenc_snd(aencHandle);
        }

        case ENC_SOURCE_VOUT:
        {
            HAL_ERROR("aenc UnSupported VOUT source type");
            return ERROR_NOT_SUPPORTED;
        }

        case ENC_SOURCE_SOURCE:
        {
            HAL_ERROR("aenc UnSupported SOURCE source type");
            return ERROR_NOT_SUPPORTED;
        }

        default:
        {
            HAL_ERROR("aenc wrong source type.");
            return ERROR_INVALID_PARAM;
        }
    }

    return SUCCESS;
}

static S32 attach_venc_source(HANDLE vencHandle)
{
    U32 u32Index = 0;

    HAL_DEBUG_ENTER();

    CHECK_ENC_INIT();

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, vencHandle, &u32Index);

    switch (s_stVencHandle[u32Index].stVencExtraInfo.stVencSrcPara.enSourceType)
    {
        case ENC_SOURCE_DECODER:
        {
            S32 s32Ret = attach_venc_avplay(vencHandle);
            HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "attach_venc_avplay error, ret(0x%08x)", s32Ret);
            break;
        }

        case ENC_SOURCE_MEM:
        {
            break;
        }

        case ENC_SOURCE_FILE:
        {
            HAL_ERROR("venc UnSupported FILE source type");
            return ERROR_NOT_SUPPORTED;
        }

        case ENC_SOURCE_AOUT:
        {
            HAL_ERROR("venc UnSupported AOUT source type");
            return ERROR_NOT_SUPPORTED;
        }

        case ENC_SOURCE_VOUT:
        {
            S32 s32Ret = attach_venc_display(vencHandle);
            HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "attach_venc_display error, ret(0x%08x)", s32Ret);
            break;
        }

        case ENC_SOURCE_SOURCE:
        {
            HAL_ERROR("venc UnSupported SOURCE source type");
            return ERROR_NOT_SUPPORTED;
        }

        default:
        {
            HAL_ERROR("venc wrong source type.");
            return ERROR_INVALID_PARAM;
        }
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 attach_aenc_source(HANDLE aencHandle)
{
    U32 u32Index = 0;

    HAL_DEBUG_ENTER();

    CHECK_ENC_INIT();

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, aencHandle, &u32Index);

    switch (s_stAencHandle[u32Index].stAencExtraInfo.stAencSrcPara.enSourceType)
    {
        case ENC_SOURCE_DECODER:
        {
            S32 s32Ret = attach_aenc_avplay(aencHandle);
            HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "attach_aenc_avplay error, ret(0x%08x)", s32Ret);
            break;
        }

        case ENC_SOURCE_MEM:
        {
            break;
        }

        case ENC_SOURCE_FILE:
        {
            HAL_ERROR("aenc UnSupported FILE source type");
            return ERROR_NOT_SUPPORTED;
        }

        case ENC_SOURCE_AOUT:
        {
            S32 s32Ret = attach_aenc_snd(aencHandle);
            HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "attach_aenc_snd error, ret(0x%08x)", s32Ret);
            break;
        }

        case ENC_SOURCE_VOUT:
        {
            HAL_ERROR("aenc UnSupported VOUT source type");
            return ERROR_NOT_SUPPORTED;
        }

        case ENC_SOURCE_SOURCE:
        {
            HAL_ERROR("aenc UnSupported SOURCE source type");
            return ERROR_NOT_SUPPORTED;
        }

        default:
        {
            HAL_ERROR("aenc wrong source type.");
            return ERROR_INVALID_PARAM;
        }
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

static S32 create_venc(HANDLE* const pEncHandle, const ENC_VENC_SETTINGS_S* const pstVencSetting)
{
    S32 s32Ret = FAILURE;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    HI_UNF_VENC_CHN_ATTR_S stVencAttr;

    memset(&stVencAttr, 0, sizeof(HI_UNF_VENC_CHN_ATTR_S));

    CHECK_NULL_PARAM(pstVencSetting);

    hiS32Ret = HI_UNF_VENC_GetDefaultAttr(&stVencAttr);
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OPEN_FAILED, "HI_UNF_VENC_GetDefaultAttr error, ret(0x%08x)", hiS32Ret);

    ENC_LOCK(&s_enc_mutex);

    s32Ret = find_free_enc_handle_index(ENC_ENCODE_VIDEO, &u32Index);
    HAL_CHK_GOTO((SUCCESS != s32Ret), VENC_OPEN_FAILED, "find_free_enc_handle_index error, ret(0x%08x)", s32Ret);

    // ENC_VENC_SETTINGS_S -> HI_UNF_VENC_CHN_ATTR_S
    s32Ret = covert_param_venc_setting_to_unf(&stVencAttr, pstVencSetting);
    HAL_CHK_GOTO((SUCCESS != s32Ret), VENC_OPEN_FAILED, "covert_param_venc_setting_to_unf error, ret(0x%08x)", s32Ret);

    hiS32Ret = HI_UNF_VENC_Create(pEncHandle, &stVencAttr);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), VENC_OPEN_FAILED, "HI_UNF_VENC_Create error, ret(0x%08x)", hiS32Ret);

    s_stVencHandle[u32Index].hVencHandle = *pEncHandle;
    s_stVencHandle[u32Index].bUsed = TRUE;
    s_stVencHandle[u32Index].stVencExtraInfo.stVencSrcPara = pstVencSetting->stSourceParams;
    s_stVencHandle[u32Index].stVencExtraInfo.stVencOutPara = pstVencSetting->stOutputParams;
    s_stVencHandle[u32Index].stVencExtraInfo.enVencOutStrFmt = pstVencSetting->enOutputStreamFormat;
    s_stVencHandle[u32Index].stVencExtraInfo.enVencColorType = pstVencSetting->enColorType;
    s_stVencHandle[u32Index].stVencExtraInfo.enVencStoreType = pstVencSetting->enStoreType;
    s_stVencHandle[u32Index].stVencExtraInfo.enVencYuvPackSeq = pstVencSetting->enPackageSeq;

    // after Venc Create, attach source or create file
    s32Ret = attach_venc_source(*pEncHandle);
    HAL_CHK_GOTO((SUCCESS != s32Ret), VENC_ATTACH_FAILED, "attach_venc_source error, ret(0x%08x)", s32Ret);

    ENC_UNLOCK(&s_enc_mutex);

    return SUCCESS;

VENC_ATTACH_FAILED:
    hiS32Ret = HI_UNF_VENC_Destroy(*pEncHandle);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_VENC_Destroy error, ret(0x%08x)", hiS32Ret);

VENC_OPEN_FAILED:
    clearVencHandleInfo(u32Index);
    ENC_UNLOCK(&s_enc_mutex);

    if (SUCCESS == s32Ret)
    {
        s32Ret = ERROR_ENC_OPEN_FAILED;
    }

    return s32Ret;
}

static S32 create_aenc(HANDLE* const pEncHandle, const ENC_AENC_SETTINGS_S* const pstAencSetting)
{
    S32 s32Ret = FAILURE;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    HI_UNF_AENC_ATTR_S stAencAttr;
    AAC_ENC_CONFIG stAACEncCfg;

    memset(&stAencAttr, 0, sizeof(HI_UNF_AENC_ATTR_S));
    memset(&stAACEncCfg, 0, sizeof(AAC_ENC_CONFIG));

    CHECK_NULL_PARAM(pstAencSetting);

    ENC_LOCK(&s_enc_mutex);

    s32Ret = find_free_enc_handle_index(ENC_ENCODE_AUDIO, &u32Index);
    HAL_CHK_GOTO((SUCCESS != s32Ret), AENC_OPEN_FAILED, "find_free_enc_handle_index error, ret(0x%08x)", s32Ret);

    s32Ret = is_audio_type_support(pstAencSetting->enType);
    HAL_CHK_GOTO((SUCCESS != s32Ret), AENC_OPEN_FAILED, "is_audio_type_support error, ret(0x%08x)", s32Ret);

    s32Ret = covert_param_aenc_setting_to_unf(&stAencAttr, pstAencSetting, &stAACEncCfg);
    HAL_CHK_GOTO((SUCCESS != s32Ret), AENC_OPEN_FAILED, "covert_param_aenc_setting_to_unf error, ret(0x%08x)", s32Ret);

    hiS32Ret = HI_UNF_AENC_Create(&stAencAttr, pEncHandle);
    HAL_CHK_GOTO((HI_SUCCESS != hiS32Ret), AENC_OPEN_FAILED, "HI_UNF_AENC_Create error, ret(0x%08x)", hiS32Ret);

    HAL_DEBUG("Create AENC Success");

    s_stAencHandle[u32Index].hAencHandle = *pEncHandle;
    s_stAencHandle[u32Index].bUsed = TRUE;
    s_stAencHandle[u32Index].stAencExtraInfo.stAencSrcPara = pstAencSetting->stSourceParams;
    s_stAencHandle[u32Index].stAencExtraInfo.stAencOutPara = pstAencSetting->stOutputParams;
    s_stAencHandle[u32Index].stAencExtraInfo.enAencOutStrFmt = pstAencSetting->enOutputStreamFormat;

    // after Aenc Create, attach source or create file
    s32Ret = attach_aenc_source(*pEncHandle);
    HAL_CHK_GOTO((SUCCESS != s32Ret), AENC_ATTACH_FAILED, "attach_aenc_source error, ret(0x%08x)", s32Ret);

    ENC_UNLOCK(&s_enc_mutex);

    return SUCCESS;

AENC_ATTACH_FAILED:
    hiS32Ret = HI_UNF_AENC_Destroy(*pEncHandle);
    HAL_CHK_PRINTF((HI_SUCCESS != hiS32Ret), "HI_UNF_AENC_Destroy error, ret(0x%08x)", hiS32Ret);

AENC_OPEN_FAILED:
    clearAencHandleInfo(u32Index);
    ENC_UNLOCK(&s_enc_mutex);

    if (SUCCESS == s32Ret)
    {
        s32Ret = ERROR_ENC_OP_FAILED;
    }

    return s32Ret;
}

S32 hi_enc_init(struct _ENC_DEVICE_S* pstDev, const ENC_INIT_PARAMS_S* const pstInitParams)
{
    S32 s32Ret = ERROR_ENC_INIT_FAILED;

    HAL_DEBUG_ENTER();

    ENC_LOCK(&s_enc_mutex);

    if (s_bVencInited)
    {
        HAL_DEBUG("Venc Already Inited.");
    }
    else
    {
        if (HI_SUCCESS == HI_UNF_VENC_Init())
        {
            s_bVencInited = TRUE;
            initAllVencHandleInfo();
        }
        else
        {
            HAL_DEBUG("Venc Init Failed.");
            ENC_UNLOCK(&s_enc_mutex);
            return ERROR_ENC_INIT_FAILED;
        }
    }

    if (s_bAencInited)
    {
        HAL_DEBUG("Aenc Already Inited.");
    }
    else
    {
        if (HI_SUCCESS == HI_UNF_AENC_Init())
        {
            s_bAencInited = TRUE;

            // now just support AAC
            if (HI_SUCCESS == HI_UNF_AENC_RegisterEncoder(AAC_ENCODE_DLL_NAME))
            {
                s_bAACSupported = TRUE;
            }

            initAllAencHandleInfo();
        }
    }

    if (s_bVencInited && s_bAencInited)
    {
        s32Ret = SUCCESS;
    }

    ENC_UNLOCK(&s_enc_mutex);

    HAL_DEBUG_EXIT();

    return s32Ret;
}

S32 hi_enc_term(struct _ENC_DEVICE_S* pstDev,  const ENC_TERM_PARAMS_S* const  pstTermParams)
{
    S32 s32Ret = ERROR_ENC_DEINIT_FAILED;

    HAL_DEBUG_ENTER();

    ENC_LOCK(&s_enc_mutex);

    if (!s_bVencInited)
    {
        HAL_DEBUG("Venc Not Inited Yet.");
    }
    else
    {
        if (HI_SUCCESS == HI_UNF_VENC_DeInit())
        {
            s_bVencInited = FALSE;
        }
    }

    if (!s_bAencInited)
    {
        HAL_DEBUG("Aenc Not Inited Yet.");
    }
    else
    {
        if (HI_SUCCESS == HI_UNF_AENC_DeInit())
        {
            s_bAencInited = FALSE;
            s_bAACSupported = FALSE;
        }
    }

    if (!s_bVencInited && !s_bAencInited)
    {
        s32Ret = SUCCESS;
    }

    ENC_UNLOCK(&s_enc_mutex);

    HAL_DEBUG_EXIT();

    return s32Ret;
}

S32 hi_enc_get_capability(struct _ENC_DEVICE_S* pstDev, ENC_CAPABILITY_S* const pstCapability)
{
    S32 s32Ret = FAILURE;

    HAL_DEBUG_ENTER();

    CHECK_NULL_PARAM(pstCapability);

    s32Ret = cfg_enc_get_capability(pstCapability);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "cfg_enc_get_capability error, ret(0x%08x)", s32Ret);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_open(struct _ENC_DEVICE_S* pstDev, HANDLE* const pEncHandle, const ENC_OPEN_PARAMS_S* const pstOpenParams)
{
    S32 s32Ret = ERROR_ENC_OPEN_FAILED;

    HAL_DEBUG_ENTER();

    CHECK_NULL_PARAM(pEncHandle);
    CHECK_NULL_PARAM(pstOpenParams);

    CHECK_ENC_INIT();

    if (ENC_ENCODE_VIDEO == pstOpenParams->enType)
    {
        s32Ret = create_venc(pEncHandle, (ENC_VENC_SETTINGS_S*)pstOpenParams->pSetting);
    }
    else if (ENC_ENCODE_AUDIO == pstOpenParams->enType)
    {
        s32Ret = create_aenc(pEncHandle, (ENC_AENC_SETTINGS_S*)pstOpenParams->pSetting);
    }
    else
    {
        s32Ret = ERROR_INVALID_PARAM;
    }

    if (SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_close(struct _ENC_DEVICE_S* pstDev, HANDLE hEnc, const ENC_CLOSE_PARAMS_S* const pstCloseParams)
{
    S32 s32Ret = ERROR_ENC_CLOSE_FAILED;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    HI_ENC_TYPE_E enHandleType = HI_ENC_BUTT;

    HAL_DEBUG_ENTER();

    CHECK_NULL_PARAM(hEnc);
    CHECK_NULL_PARAM(pstCloseParams);

    CHECK_ENC_INIT();

    enHandleType = find_handle_type(hEnc);

    switch (enHandleType)
    {
        case HI_ENC_VENC:
        {
            s32Ret = dettach_venc_source(hEnc);
            HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "dettach_venc_source error, ret(0x%08x)", s32Ret);

            hiS32Ret = HI_UNF_VENC_Destroy(hEnc);
            HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_CLOSE_FAILED, "HI_UNF_VENC_Destroy error, ret(0x%08x)", hiS32Ret);

            ENC_LOCK(&s_enc_mutex);

            if (SUCCESS == get_enc_handle_index(ENC_ENCODE_VIDEO, hEnc, &u32Index))
            {
                clearVencHandleInfo(u32Index);
            }

            ENC_UNLOCK(&s_enc_mutex);

            break;
        }

        case HI_ENC_AENC:
        {
            s32Ret = dettach_aenc_source(hEnc);
            HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "dettach_aenc_source error, ret(0x%08x)", s32Ret);

            hiS32Ret = HI_UNF_AENC_Destroy(hEnc);
            HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_CLOSE_FAILED, "HI_UNF_AENC_Destroy error, ret(0x%08x)", hiS32Ret);

            ENC_LOCK(&s_enc_mutex);

            if (SUCCESS == get_enc_handle_index(ENC_ENCODE_AUDIO, hEnc, &u32Index))
            {
                clearAencHandleInfo(u32Index);
            }

            ENC_UNLOCK(&s_enc_mutex);

            break;
        }

        default:
        {
            return ERROR_ENC_NO_SUCH_HANDLE;
        }
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_set_private_data(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType, const VOID* const pData, const U32 u32Length)
{
    // not support
    return ERROR_NOT_SUPPORTED;
}

S32 hi_enc_get_private_data(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType, VOID* const pData, const U32 u32Length, U32* const  pu32ActLength)
{
    // not support
    return ERROR_NOT_SUPPORTED;
}

S32 hi_enc_set(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,   VOID* const pSettings)
{
    S32 s32Ret = ERROR_ENC_OP_FAILED;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    ENC_AENC_SETTINGS_S* pstAencSetting = NULL;
    ENC_VENC_SETTINGS_S* pstVencSetting = NULL;

    HI_UNF_VENC_CHN_ATTR_S stVencAttr;
    HI_UNF_AENC_ATTR_S stAencAttr;
    // private data
    AAC_ENC_CONFIG stAACEncCfg;

    HAL_DEBUG_ENTER();

    memset(&stVencAttr, 0, sizeof(HI_UNF_VENC_CHN_ATTR_S));
    memset(&stAencAttr, 0, sizeof(HI_UNF_AENC_ATTR_S));
    memset(&stAACEncCfg, 0, sizeof(AAC_ENC_CONFIG));

    CHECK_NULL_PARAM(hEnc);
    CHECK_NULL_PARAM(pSettings);

    CHECK_ENC_INIT();

    if (ENC_ENCODE_VIDEO == enEncType)
    {
        pstVencSetting = (ENC_VENC_SETTINGS_S*)pSettings;

        GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, hEnc, &u32Index);

        hiS32Ret = HI_UNF_VENC_GetAttr(hEnc, &stVencAttr);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_GetAttr error, ret(0x%08x)", hiS32Ret);

        // ENC_VENC_SETTINGS_S -> HI_UNF_VENC_CHN_ATTR_S
        s32Ret = covert_param_venc_setting_to_unf(&stVencAttr, pstVencSetting);
        HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "covert_param_venc_setting_to_unf error, ret(0x%08x)", s32Ret);

        hiS32Ret = HI_UNF_VENC_SetAttr(hEnc, &stVencAttr);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_SetAttr error, ret(0x%08x)", hiS32Ret);

        ENC_LOCK(&s_enc_mutex);

        s_stVencHandle[u32Index].stVencExtraInfo.stVencSrcPara = pstVencSetting->stSourceParams;
        s_stVencHandle[u32Index].stVencExtraInfo.stVencOutPara = pstVencSetting->stOutputParams;
        s_stVencHandle[u32Index].stVencExtraInfo.enVencOutStrFmt = pstVencSetting->enOutputStreamFormat;
        s_stVencHandle[u32Index].stVencExtraInfo.enVencColorType = pstVencSetting->enColorType;
        s_stVencHandle[u32Index].stVencExtraInfo.enVencStoreType = pstVencSetting->enStoreType;
        s_stVencHandle[u32Index].stVencExtraInfo.enVencYuvPackSeq = pstVencSetting->enPackageSeq;

        ENC_UNLOCK(&s_enc_mutex);
    }
    else if (ENC_ENCODE_AUDIO == enEncType)
    {
        pstAencSetting = (ENC_AENC_SETTINGS_S*)pSettings;

        GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, hEnc, &u32Index);

        s32Ret = is_audio_type_support(pstAencSetting->enType);
        HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "is_audio_type_support error, ret(0x%08x)", s32Ret);

        s32Ret = covert_param_aenc_setting_to_unf(&stAencAttr, pstAencSetting, &stAACEncCfg);
        HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "covert_param_aenc_setting_to_unf error, ret(0x%08x)", s32Ret);

        ENC_LOCK(&s_enc_mutex);

        s_stAencHandle[u32Index].stAencExtraInfo.stAencSrcPara = pstAencSetting->stSourceParams;
        s_stAencHandle[u32Index].stAencExtraInfo.stAencOutPara = pstAencSetting->stOutputParams;
        s_stAencHandle[u32Index].stAencExtraInfo.enAencOutStrFmt = pstAencSetting->enOutputStreamFormat;

        ENC_UNLOCK(&s_enc_mutex);

        hiS32Ret = HI_UNF_AENC_SetAttr(hEnc, &stAencAttr);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_AENC_SetAttr error, ret(0x%08x)", hiS32Ret);
    }
    else
    {
        return ERROR_INVALID_PARAM;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_get(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,   VOID* const pSettings)
{
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    ENC_AENC_SETTINGS_S* pstAencSetting = NULL;
    ENC_VENC_SETTINGS_S* pstVencSetting = NULL;
    HI_UNF_VENC_CHN_ATTR_S stVencAttr;
    HI_UNF_AENC_ATTR_S stAencAttr;

    HAL_DEBUG_ENTER();

    memset(&stVencAttr, 0, sizeof(HI_UNF_VENC_CHN_ATTR_S));
    memset(&stAencAttr, 0, sizeof(HI_UNF_AENC_ATTR_S));

    CHECK_NULL_PARAM(hEnc);
    CHECK_NULL_PARAM(pSettings);

    CHECK_ENC_INIT();

    if (ENC_ENCODE_VIDEO == enEncType)
    {
        GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, hEnc, &u32Index);

        hiS32Ret = HI_UNF_VENC_GetAttr(hEnc, &stVencAttr);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_GetAttr error, ret(0x%08x)", hiS32Ret);

        // HI_UNF_VENC_CHN_ATTR_S -> ENC_VENC_SETTINGS_S
        pstVencSetting = (ENC_VENC_SETTINGS_S*)pSettings;

        (VOID)covert_param_venc_setting_to_hal(pstVencSetting, &stVencAttr);

        ENC_LOCK(&s_enc_mutex);

        pstVencSetting->stSourceParams = s_stVencHandle[u32Index].stVencExtraInfo.stVencSrcPara;
        pstVencSetting->stOutputParams = s_stVencHandle[u32Index].stVencExtraInfo.stVencOutPara;
        pstVencSetting->enOutputStreamFormat = s_stVencHandle[u32Index].stVencExtraInfo.enVencOutStrFmt;
        pstVencSetting->enColorType = s_stVencHandle[u32Index].stVencExtraInfo.enVencColorType;
        pstVencSetting->enStoreType = s_stVencHandle[u32Index].stVencExtraInfo.enVencStoreType;
        pstVencSetting->enPackageSeq = s_stVencHandle[u32Index].stVencExtraInfo.enVencYuvPackSeq;

        ENC_UNLOCK(&s_enc_mutex);
    }
    else if ( ENC_ENCODE_AUDIO == enEncType)
    {
        GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, hEnc, &u32Index);

        hiS32Ret = HI_UNF_AENC_GetAttr(hEnc, &stAencAttr);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_AENC_GetAttr error, ret(0x%08x)", hiS32Ret);

        // HI_UNF_AENC_CHN_ATTR_S -> ENC_AENC_SETTINGS_S
        pstAencSetting = (ENC_AENC_SETTINGS_S*)pSettings;

        (VOID)covert_param_aenc_setting_to_hal(pstAencSetting, &stAencAttr);

        ENC_LOCK(&s_enc_mutex);

        pstAencSetting->stSourceParams = s_stAencHandle[u32Index].stAencExtraInfo.stAencSrcPara;
        pstAencSetting->stOutputParams = s_stAencHandle[u32Index].stAencExtraInfo.stAencOutPara;
        pstAencSetting->enOutputStreamFormat = s_stAencHandle[u32Index].stAencExtraInfo.enAencOutStrFmt;

        ENC_UNLOCK(&s_enc_mutex);
    }
    else
    {
        return ERROR_INVALID_PARAM;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_start(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc)
{
    HI_ENC_TYPE_E enHandleType = HI_ENC_BUTT;
    HI_S32 hiS32Ret = HI_FAILURE;

    HAL_DEBUG_ENTER();

    CHECK_NULL_PARAM(hEnc);

    CHECK_ENC_INIT();

    enHandleType = find_handle_type(hEnc);

    switch (enHandleType)
    {
        case HI_ENC_VENC:
        {
            hiS32Ret = HI_UNF_VENC_Start(hEnc);
            HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_Start error, ret(0x%08x)", hiS32Ret);
            break;
        }

        case HI_ENC_AENC:
        {
            hiS32Ret = HI_UNF_AENC_Start(hEnc);
            HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_AENC_Start error, ret(0x%08x)", hiS32Ret);
            break;
        }

        default:
        {
            return ERROR_ENC_NO_SUCH_HANDLE;
        }
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_stop(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc)
{
    HI_ENC_TYPE_E enHandleType = HI_ENC_BUTT;
    HI_S32 hiS32Ret = HI_FAILURE;

    HAL_DEBUG_ENTER();

    CHECK_NULL_PARAM(hEnc);

    CHECK_ENC_INIT();

    enHandleType = find_handle_type(hEnc);

    switch (enHandleType)
    {
        case HI_ENC_VENC:
        {
            hiS32Ret = HI_UNF_VENC_Stop(hEnc);
            HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_Stop error, ret(0x%08x)", hiS32Ret);
            break;
        }

        case HI_ENC_AENC:
        {
            hiS32Ret = HI_UNF_AENC_Stop(hEnc);
            HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_AENC_Stop error, ret(0x%08x)", hiS32Ret);
            break;
        }

        default:
        {
            return ERROR_ENC_NO_SUCH_HANDLE;
        }
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_inject_data(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,  VOID* const pData, const  U32 u32TimeoutMs)
{
    U32 u32Index = 0;
    HI_S32 hiS32Ret = HI_FAILURE;
    ENC_AENC_DATA_S* pstAencData;
    HI_UNF_AO_FRAMEINFO_S stUNFAoFrame;

    HAL_DEBUG_ENTER();

    memset(&stUNFAoFrame, 0, sizeof(HI_UNF_AO_FRAMEINFO_S));

    CHECK_NULL_PARAM(hEnc);
    CHECK_NULL_PARAM(pData);

    CHECK_ENC_INIT();

    if ( ENC_ENCODE_VIDEO == enEncType)
    {
        HAL_DEBUG("UnSupported inject video data.");
        return ERROR_NOT_SUPPORTED;
    }
    else if ( ENC_ENCODE_AUDIO == enEncType)
    {
        GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, hEnc, &u32Index);
        pstAencData = (ENC_AENC_DATA_S*)pData;
        stUNFAoFrame.s32BitPerSample = pstAencData->u32BitPerSample;
        stUNFAoFrame.bInterleaved = hal_to_unf_for_bool(pstAencData->bInterleaved);
        stUNFAoFrame.u32SampleRate = pstAencData->u32SampleRate;
        stUNFAoFrame.u32Channels = pstAencData->u32Channels;
        stUNFAoFrame.u32PtsMs = (pstAencData->u64Pts) / PTS_RATIO;
        stUNFAoFrame.ps32PcmBuffer = pstAencData->pBuffer;
        stUNFAoFrame.ps32BitsBuffer = NO_CONCERN_VALUE;
        stUNFAoFrame.u32PcmSamplesPerFrame = pstAencData->u32SamplesPerPrame;
        stUNFAoFrame.u32BitsBytesPerFrame = NO_CONCERN_VALUE;
        stUNFAoFrame.u32FrameIndex = pstAencData->u32FrameIndex;
        stUNFAoFrame.u32IEC61937DataType = NO_CONCERN_VALUE;

        hiS32Ret = HI_UNF_AENC_SendFrame(hEnc, &stUNFAoFrame);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_AENC_SendFrame error, ret(0x%08x)", hiS32Ret);
    }
    else
    {
        return ERROR_INVALID_PARAM;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_acquire_stream(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,  VOID* const pData, const  U32 u32TimeoutMs)
{
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    ENC_VID_ES_DATA_S* pstVidEsData = NULL;
    ENC_AUD_ES_DATA_S* pstAudEsData = NULL;
    HI_UNF_VENC_STREAM_S stVencStream;
    HI_UNF_VENC_CHN_ATTR_S stVencAttr;
    HI_UNF_ES_BUF_S stAencEsbuf;
    U32 u32Times = (0 == u32TimeoutMs/TIMEOUT_SPLIT) ? 1 : u32TimeoutMs/TIMEOUT_SPLIT;

    HAL_DEBUG_ENTER();

    memset(&stVencStream, 0, sizeof(HI_UNF_VENC_STREAM_S));
    memset(&stVencAttr, 0, sizeof(HI_UNF_VENC_CHN_ATTR_S));
    memset(&stAencEsbuf, 0, sizeof(HI_UNF_ES_BUF_S));

    CHECK_NULL_PARAM(hEnc);
    CHECK_NULL_PARAM(pData);

    CHECK_ENC_INIT();

    if (ENC_ENCODE_VIDEO == enEncType)
    {
        GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, hEnc, &u32Index);
        s_stVencHandle[u32Index].bAbortFlag = FALSE;

        do
        {
            hiS32Ret = HI_UNF_VENC_AcquireStream(hEnc, &stVencStream, TIMEOUT_SPLIT);

            if (HI_SUCCESS == hiS32Ret)
            {
                break;
            }
        }
        while ((--u32Times) && (!s_stVencHandle[u32Index].bAbortFlag));

        // no encoded data
        HAL_CHK_RETURN_NO_PRINT((HI_ERR_VENC_BUF_EMPTY == hiS32Ret), ERROR_ENC_OP_FAILED);

        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_AcquireStream error, ret(0x%08x)", hiS32Ret);

        hiS32Ret = HI_UNF_VENC_GetAttr(hEnc, &stVencAttr);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_GetAttr error, ret(0x%08x)", hiS32Ret);

        pstVidEsData = (ENC_VID_ES_DATA_S*)pData;
        // HI_UNF_VENC_STREAM_S -> ENC_VID_ES_DATA_S
        (VOID)covert_param_vid_data_to_hal(pstVidEsData, &stVencStream, stVencAttr.enVencType);
    }
    else if (ENC_ENCODE_AUDIO == enEncType)
    {
        GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, hEnc, &u32Index);
        s_stAencHandle[u32Index].bAbortFlag = FALSE;

        do
        {
            hiS32Ret = HI_UNF_AENC_AcquireStream(hEnc, &stAencEsbuf, TIMEOUT_SPLIT);

            if (HI_SUCCESS == hiS32Ret)
            {
                break;
            }
        }
        while ((--u32Times) && (!s_stAencHandle[u32Index].bAbortFlag));

        // no encoded data
        HAL_CHK_RETURN_NO_PRINT((HI_ERR_AENC_OUT_BUF_EMPTY == hiS32Ret), ERROR_ENC_OP_FAILED);

        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_AENC_AcquireStream error, ret(0x%08x)", hiS32Ret);

        // HI_UNF_ES_BUF_S -> ENC_AUD_ES_DATA_S
        pstAudEsData = (ENC_AUD_ES_DATA_S*)pData;
        (VOID)covert_param_aud_data_to_hal(pstAudEsData, &stAencEsbuf);
    }
    else
    {
        return ERROR_INVALID_PARAM;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_release_stream(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,  VOID* const pData)
{
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    ENC_VID_ES_DATA_S* pVdata = NULL;
    ENC_AUD_ES_DATA_S* pAdata = NULL;
    HI_UNF_VENC_STREAM_S stVencStream;
    HI_UNF_ES_BUF_S stAencEsbuf;

    HAL_DEBUG_ENTER();

    memset(&stVencStream, 0, sizeof(HI_UNF_VENC_STREAM_S));
    memset(&stAencEsbuf, 0, sizeof(HI_UNF_ES_BUF_S));

    CHECK_NULL_PARAM(hEnc);
    CHECK_NULL_PARAM(pData);

    CHECK_ENC_INIT();

    if (ENC_ENCODE_VIDEO == enEncType)
    {
        GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, hEnc, &u32Index);
        pVdata = (ENC_VID_ES_DATA_S*)pData;

        hiS32Ret = covert_param_vid_data_to_unf(pVdata, &stVencStream);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "covert_param_vid_data_to_unf error, ret(0x%08x)", hiS32Ret);

        hiS32Ret = HI_UNF_VENC_ReleaseStream(hEnc, &stVencStream);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_ReleaseStream error, ret(0x%08x)", hiS32Ret);
    }
    else if (ENC_ENCODE_AUDIO == enEncType)
    {
        GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, hEnc, &u32Index);
        pAdata = (ENC_AUD_ES_DATA_S*)pData;
        // ENC_AUD_ES_DATA_S -> HI_UNF_ES_BUF_S
        stAencEsbuf.pu8Buf = pAdata->pBuffer;
        stAencEsbuf.u32BufLen = pAdata->u32Length;
        stAencEsbuf.u32PtsMs = pAdata->u64Pts / PTS_RATIO;

        hiS32Ret = HI_UNF_AENC_ReleaseStream(hEnc, &stAencEsbuf);
        HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_AENC_ReleaseStream error, ret(0x%08x)", hiS32Ret);
    }
    else
    {
        return ERROR_INVALID_PARAM;
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_request_iframe(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc)
{
    HI_S32 hiS32Ret = HI_FAILURE;

    HAL_DEBUG_ENTER();

    CHECK_NULL_PARAM(hEnc);

    CHECK_ENC_INIT();

    hiS32Ret = HI_UNF_VENC_RequestIFrame(hEnc);
    HAL_CHK_RETURN((HI_ERR_VENC_NO_INIT == hiS32Ret), ERROR_NOT_INITED, "HI_UNF_AENC_ReleaseStream error, ret(0x%08x)", hiS32Ret);
    HAL_CHK_RETURN((HI_ERR_VENC_CHN_NOT_EXIST == hiS32Ret), ERROR_ENC_NO_SUCH_HANDLE, "HI_UNF_AENC_ReleaseStream error, ret(0x%08x)", hiS32Ret);
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_AENC_ReleaseStream error, ret(0x%08x)", hiS32Ret);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_abort(struct _ENC_DEVICE_S* pstDev, const HANDLE enc_handle)
{
    U32 u32Index = 0;
    HI_ENC_TYPE_E enHandleType = HI_ENC_BUTT;

    HAL_DEBUG_ENTER();

    CHECK_NULL_PARAM(enc_handle);

    CHECK_ENC_INIT();

    enHandleType = find_handle_type(enc_handle);

    switch (enHandleType)
    {
        case HI_ENC_VENC:
        {
            GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, enc_handle, &u32Index);
            s_stVencHandle[u32Index].bAbortFlag = TRUE;
            break;
        }

        case HI_ENC_AENC:
        {
            GET_ENC_HANDLE_INDEX(ENC_ENCODE_AUDIO, enc_handle, &u32Index);
            s_stAencHandle[u32Index].bAbortFlag = TRUE;
            break;
        }

        default:
        {
            return ERROR_ENC_NO_SUCH_HANDLE;
        }
    }

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_queue_frame(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, ENC_VENC_DATA_S* pVideoData)
{
    S32 s32Ret = ERROR_ENC_OP_FAILED;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    ENC_VENC_SETTINGS_S stVencSettings;
    HI_UNF_VIDEO_FRAME_INFO_S stVideoFrameInfo;

    HAL_DEBUG_ENTER();

    memset(&stVencSettings, 0, sizeof(ENC_VENC_SETTINGS_S));
    memset(&stVideoFrameInfo, 0, sizeof(HI_UNF_VIDEO_FRAME_INFO_S));

    CHECK_NULL_PARAM(hEnc);
    CHECK_NULL_PARAM(pVideoData);

    CHECK_ENC_INIT();

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, hEnc, &u32Index);

    s32Ret = hi_enc_get(pstDev, hEnc, ENC_ENCODE_VIDEO, (VOID * const)&stVencSettings);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "hi_enc_get error, ret(0x%08x)", s32Ret);

    // 1. check type
    HAL_CHK_RETURN((pVideoData->enType != stVencSettings.enType), ERROR_INVALID_PARAM, "queue venc type[%d] != venc setting type[%d]", pVideoData->enType, stVencSettings.enType);

    // 2. check width/height
    HAL_CHK_RETURN((pVideoData->u32Width != stVencSettings.u32Width || pVideoData->u32Height != stVencSettings.u32Height),
                   ERROR_INVALID_PARAM, "queue venc width[%d] or height[%d] != venc setting width[%d] or height[%d]",
                   pVideoData->u32Width, pVideoData->u32Height, stVencSettings.u32Width, stVencSettings.u32Height);

    // 3. interleaved/frameRate in ENC_VENC_DATA_S not concern

    ENC_LOCK(&s_enc_mutex);

    // 4. update colorType/storeType/packageSeq
    if (pVideoData->enColorType != stVencSettings.enColorType)
    {
        s_stVencHandle[u32Index].stVencExtraInfo.enVencColorType = pVideoData->enColorType;
    }

    if (pVideoData->enStoreType != stVencSettings.enStoreType)
    {
        s_stVencHandle[u32Index].stVencExtraInfo.enVencStoreType = pVideoData->enStoreType;
    }

    if (pVideoData->enPackageSeq != stVencSettings.enPackageSeq)
    {
        s_stVencHandle[u32Index].stVencExtraInfo.enVencYuvPackSeq = pVideoData->enPackageSeq;
    }

    ENC_UNLOCK(&s_enc_mutex);

    s32Ret = covert_param_venc_data_to_unf(hEnc, &stVideoFrameInfo, pVideoData);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "covert_param_venc_data_to_unf error, ret(0x%08x)", s32Ret);

    hiS32Ret = HI_UNF_VENC_QueueFrame(hEnc, &stVideoFrameInfo);
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_QueueFrame error, ret(0x%08x)", hiS32Ret);

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

S32 hi_enc_dequeue_frame(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, ENC_VENC_DATA_S* pVideoData)
{
    S32 s32Ret = ERROR_ENC_OP_FAILED;
    HI_S32 hiS32Ret = HI_FAILURE;
    U32 u32Index = 0;
    U32 u32QueueIndex = 0;
    HI_UNF_VIDEO_FRAME_INFO_S stVideoFrameInfo;
    ENC_VENC_SETTINGS_S stVencSettings;

    HAL_DEBUG_ENTER();

    memset(&stVideoFrameInfo, 0, sizeof(HI_UNF_VIDEO_FRAME_INFO_S));
    memset(&stVencSettings, 0, sizeof(ENC_VENC_SETTINGS_S));

    CHECK_NULL_PARAM(hEnc);
    CHECK_NULL_PARAM(pVideoData);

    CHECK_ENC_INIT();

    GET_ENC_HANDLE_INDEX(ENC_ENCODE_VIDEO, hEnc, &u32Index);

    hiS32Ret = HI_UNF_VENC_DequeueFrame(hEnc, &stVideoFrameInfo);
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_UNF_VENC_DequeueFrame error, ret(0x%08x)", hiS32Ret);

    (VOID)covert_param_venc_data_to_hal(pVideoData, &stVideoFrameInfo);

    // need to HI_MMZ_Free, needn't lock
    for (u32QueueIndex = 0; u32QueueIndex < VENC_MAX_QUEUE_NUM; u32QueueIndex++)
    {
        if (s_stVencHandle[u32Index].stVencQueueInfo.stVencQueueMmz[u32QueueIndex].stHiMmzBuf.phyaddr == stVideoFrameInfo.stVideoFrameAddr[0].u32YAddr)
        {
            s_stVencHandle[u32Index].stVencQueueInfo.stVencQueueMmz[u32QueueIndex].bMmzUsed = FALSE;
            break;
        }
    }

    HAL_CHK_RETURN((VENC_MAX_QUEUE_NUM == u32QueueIndex), ERROR_ENC_OP_FAILED, "deuqueFrame doesn't match any queue slot.");

    hiS32Ret = HI_MMZ_Free(&s_stVencHandle[u32Index].stVencQueueInfo.stVencQueueMmz[u32QueueIndex].stHiMmzBuf);
    HAL_CHK_RETURN((HI_SUCCESS != hiS32Ret), ERROR_ENC_OP_FAILED, "HI_MMZ_Free error, ret(0x%08x)", hiS32Ret);

    s32Ret = hi_enc_get(pstDev, hEnc, ENC_ENCODE_VIDEO, (VOID * const)&stVencSettings);
    HAL_CHK_RETURN((SUCCESS != s32Ret), s32Ret, "hi_enc_get error, ret(0x%08x)", hiS32Ret);

    pVideoData->enType = stVencSettings.enType;

    HAL_DEBUG_EXIT();

    return SUCCESS;
}

#ifdef TVOS_PLATFORM
static int enc_device_close(struct hw_device_t *pstDev)
{
    struct ENC_DEVICE_S* pCtx = (struct ENC_DEVICE_S*)pstDev;
    if (pCtx) {
        free(pCtx);
        pCtx = NULL;
    }
    return 0;
}

static int enc_device_open(const struct hw_module_t* module, const char* name, struct hw_device_t** device)
{
    S32 s32Ret = FAILURE;
    if (!strcmp(name, ENC_HARDWARE_ENC0))
    {
        if (NULL == device)
        {
            return FAILURE;
        }

        ENC_DEVICE_S * pstENCdev = (ENC_DEVICE_S*)malloc(sizeof(ENC_DEVICE_S));
        if (NULL == pstENCdev)
        {
            //HAL_ERROR("malloc memory failed! ");
            return FAILURE;
        }

        /* initialize our state here */
        memset(pstENCdev, 0, sizeof( *pstENCdev ));

        /* initialize the procs */
        pstENCdev->stCommon.tag     = HARDWARE_DEVICE_TAG;
        pstENCdev->stCommon.version = ENC_DEVICE_API_VERSION_1_0;
        pstENCdev->stCommon.module  = (hw_module_t*)module;
        pstENCdev->stCommon.close   = enc_device_close;

        /* register the callbacks */
        pstENCdev->enc_init = hi_enc_init;
        pstENCdev->enc_term = hi_enc_term;
        pstENCdev->enc_get_capability = hi_enc_get_capability;
        pstENCdev->enc_open = hi_enc_open;
        pstENCdev->enc_close = hi_enc_close;
        pstENCdev->enc_set_private_data = hi_enc_set_private_data;
        pstENCdev->enc_get_private_data = hi_enc_get_private_data;
        pstENCdev->enc_set = hi_enc_set;
        pstENCdev->enc_get = hi_enc_get;
        pstENCdev->enc_start = hi_enc_start;
        pstENCdev->enc_stop = hi_enc_stop;
        pstENCdev->enc_inject_data = hi_enc_inject_data;
        pstENCdev->enc_acquire_stream = hi_enc_acquire_stream;
        pstENCdev->enc_release_stream = hi_enc_release_stream;
        pstENCdev->enc_request_iframe = hi_enc_request_iframe;
        pstENCdev->enc_abort = hi_enc_abort;
        pstENCdev->enc_queue_frame = hi_enc_queue_frame,
        pstENCdev->enc_dequeue_frame = hi_enc_dequeue_frame,

        *device = &(pstENCdev->stCommon);
        s32Ret = SUCCESS;
    }
    return s32Ret;
}
static int enc_device_open(const struct hw_module_t* module, const char* name,
                          struct hw_device_t** device);

static struct hw_module_methods_t enc_module_methods = {
    open: enc_device_open
};

ENC_MODULE_S HAL_MODULE_INFO_SYM = {
    stCommon: {
        tag: HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
        id: ENC_HARDWARE_MODULE_ID,
        name: "Sample halenc module",
        author: "The Android Open Source Project",
        methods: &enc_module_methods,
        dso: NULL,
        reserved: {0},
    }
};
#endif

static ENC_DEVICE_S s_stDevice_enc =
{
    /* register the callbacks */
    .enc_init = hi_enc_init,
    .enc_term = hi_enc_term,
    .enc_get_capability = hi_enc_get_capability,
    .enc_open = hi_enc_open,
    .enc_close = hi_enc_close,
    .enc_set_private_data = hi_enc_set_private_data,
    .enc_get_private_data = hi_enc_get_private_data,
    .enc_set = hi_enc_set,
    .enc_get = hi_enc_get,
    .enc_start = hi_enc_start,
    .enc_stop = hi_enc_stop,
    .enc_inject_data = hi_enc_inject_data,
    .enc_acquire_stream = hi_enc_acquire_stream,
    .enc_release_stream = hi_enc_release_stream,
    .enc_request_iframe = hi_enc_request_iframe,
    .enc_abort = hi_enc_abort,
    .enc_queue_frame = hi_enc_queue_frame,
    .enc_dequeue_frame = hi_enc_dequeue_frame,
};

ENC_DEVICE_S* getEncDevice()
{
    return &s_stDevice_enc;
}
