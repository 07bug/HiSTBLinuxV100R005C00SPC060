#define LOG_TAG "hal_aout"
//#define LOG_NDEBUG 0
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#ifdef HAL_HISI_EXTEND_H
#include "tvos_hal_source.h"
#endif
#include "tvos_hal_errno.h"
#include "tvos_hal_aout.h"
#include "tvos_hal_common.h"
#include "hi_unf_sound.h"
#include "hi_mpi_ao.h"
#include "hi_error_mpi.h"

/***************************** Macro Definition ************************/

#define AOUT_HEADER_VERSION       (1)
#define AOUT_DEVICE_API_VERSION_1_0 HARDWARE_DEVICE_API_VERSION_2(1, 0, AOUT_HEADER_VERSION)

#define AOUT_DEVICE_SUPPORT_NUM   (3)
#define DEVICE_SUPPORT_MAX        (5)
#define TRACK_SUPPORT_MAX         (8)
#define TRACK_HANDLE_UNUSED       (0xffffaaaa)
#define TRACK_DEFAULT_BUFFERSIZE  (1024)
#define TRACK_DEFAULT_CHANNEL     (2)
#define TRACK_DEFAULT_SAMPLERATE  (48000)
//#define STB_AOUT_SUPPORT   1  //3796M / 3798CV200
#define SND_SUPPORT_MAX           (3)

#ifndef __unused
#define __unused
#endif

#define DEBUG_V
#ifdef  DEBUG_V
#define trace()  HAL_DEBUG("%s called", __func__)
#define dbg      HAL_DEBUG
#else
#define trace()
#define dbg(fmt, ...)
#endif

//#ifdef STB_AOUT_SUPPORT
#define TRACK_DEFAULT_BUFMS 400  //ms
//#endif
/*************************** Structure Definition **********************/
typedef struct
{
    S32 s32IntGain[3];  //DAC0/SPDIF/HDMI
    S32 s32DecGain[3];
} Snd_RM_S;

typedef struct
{
    HI_HANDLE     hTrack;
    HI_UNF_SND_TRACK_TYPE_E enTrackType;
    AOUT_DATA_FORMAT_E enFormat;
    U32                u32SampleRate;
    U32                u32Channels;
    U32                u32BufferSize;

    U32                u32BufferMs;
    U32                u32FrameBytes;
    BOOL              bStarted;
} TRACK_RM_S;

typedef struct
{
    BOOL bInited;
    TRACK_RM_S astTrackEntity[TRACK_SUPPORT_MAX];
    Snd_RM_S astSndEntity[SND_SUPPORT_MAX];
} AO_GLOBAL_RM_S;

typedef struct
{
    HI_UNF_SND_E             enSound;
    HI_UNF_SND_OUTPUTPORT_E  enOutPort;
    HI_BOOL                  bMute;
} AO_MUTE_STATUS_S;

/*Store all audio output mute status.*/
static AO_MUTE_STATUS_S g_audioStatus[] =
{
    /*SND 0*/
    {HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_DAC0, HI_FALSE},
    {HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_I2S0, HI_FALSE},
    {HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_I2S1, HI_FALSE},
    {HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_FALSE},
    {HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_FALSE},
    {HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ARC0, HI_FALSE},
    {HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_EXT_DAC1, HI_FALSE},
    {HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_EXT_DAC2, HI_FALSE},
    {HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_EXT_DAC3, HI_FALSE},

    /*SND 1*/
    {HI_UNF_SND_1, HI_UNF_SND_OUTPUTPORT_DAC0, HI_FALSE},
    {HI_UNF_SND_1, HI_UNF_SND_OUTPUTPORT_I2S0, HI_FALSE},
    {HI_UNF_SND_1, HI_UNF_SND_OUTPUTPORT_I2S1, HI_FALSE},
    {HI_UNF_SND_1, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_FALSE},
    {HI_UNF_SND_1, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_FALSE},
    {HI_UNF_SND_1, HI_UNF_SND_OUTPUTPORT_ARC0, HI_FALSE},
    {HI_UNF_SND_1, HI_UNF_SND_OUTPUTPORT_EXT_DAC1, HI_FALSE},
    {HI_UNF_SND_1, HI_UNF_SND_OUTPUTPORT_EXT_DAC2, HI_FALSE},
    {HI_UNF_SND_1, HI_UNF_SND_OUTPUTPORT_EXT_DAC3, HI_FALSE},

    /*SND 2*/
    {HI_UNF_SND_2, HI_UNF_SND_OUTPUTPORT_DAC0, HI_FALSE},
    {HI_UNF_SND_2, HI_UNF_SND_OUTPUTPORT_I2S0, HI_FALSE},
    {HI_UNF_SND_2, HI_UNF_SND_OUTPUTPORT_I2S1, HI_FALSE},
    {HI_UNF_SND_2, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_FALSE},
    {HI_UNF_SND_2, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_FALSE},
    {HI_UNF_SND_2, HI_UNF_SND_OUTPUTPORT_ARC0, HI_FALSE},
    {HI_UNF_SND_2, HI_UNF_SND_OUTPUTPORT_EXT_DAC1, HI_FALSE},
    {HI_UNF_SND_2, HI_UNF_SND_OUTPUTPORT_EXT_DAC2, HI_FALSE},
    {HI_UNF_SND_2, HI_UNF_SND_OUTPUTPORT_EXT_DAC3, HI_FALSE},
};

/** record aout sound card instance open/close status, sound card instance number mustn't bigger than AOUT_ID_NUM */
static BOOL s_abAoutInstanceStatus[AOUT_ID_NUM];

static AO_GLOBAL_RM_S s_stAoGlobalRM;
static U32 s_bAoutInitCount = 0;
static pthread_mutex_t g_stAOutMutex;
/******************************* API declaration *****************************/
#define AOUT_LOCK(mutex) \
    do \
    { \
        (VOID)pthread_mutex_lock((mutex)); \
    } while (0)

#define AOUT_UNLOCK(mutex) \
    do \
    { \
        (VOID)pthread_mutex_unlock((mutex)); \
    } while (0)

#define Check_NullPtr(ptr) \
    do \
    { \
        if (NULL == ptr)\
        {\
            HAL_ERROR("check null point\n");\
            return ERROR_NULL_PTR;\
        }\
    } while(0)

#define Check_Inited() \
    do \
    {\
        if(0 == s_bAoutInitCount)\
        {\
            HAL_ERROR("check ao not inited\n");\
            return ERROR_AO_NOT_INITED;\
        }\
    } while(0)

#define Check_AoutHandle2SoundID(hAout, enSound) \
    do {\
        switch(hAout) {\
            case AOUT_ID_0:\
                enSound = HI_UNF_SND_0;\
                break;\
            case AOUT_ID_1:\
                enSound = HI_UNF_SND_1;\
                break;\
            case AOUT_ID_2:\
                enSound = HI_UNF_SND_2;\
                break;\
            case AOUT_ID_3:\
                enSound = HI_UNF_SND_BUTT;\
                break;\
            default:\
                HAL_ERROR("check aoutHandle2soundid(%#x) is Invalid\n", hAout);\
                return ERROR_AO_PARAMETER_INVALID;\
        }\
    } while(0)

#define Check_AoutHandle(hAout) \
    do { \
        U32 u32MacroIndex = (U32)hAout;  \
        if (u32MacroIndex >= (AOUT_ID_NUM - 1)) \
        { \
            HAL_ERROR("Aout handle is  invalid\n");\
            return ERROR_INVALID_PARAM; \
        } \
        if (FALSE == s_abAoutInstanceStatus[u32MacroIndex]) \
        { \
            HAL_ERROR("Aout handle doesn't open\n");\
            return ERROR_AO_NOT_OPENED;\
        } \
    }while(0)

#define Check_DeviceType(enOutputDevice) do{\
        if(AOUT_DEVICE_ALL != enOutputDevice &&\
           (0 == ((S32)enOutputDevice & (((S32)AOUT_DEVICE_RCA|(S32)AOUT_DEVICE_SPDIF|(S32)AOUT_DEVICE_HDMI|\
                                          (S32)AOUT_DEVICE_SPEAKER|(S32)AOUT_DEVICE_ARC))))) \
        {\
            HAL_ERROR("devicetype id(%#x) is invalid\n", enOutputDevice);\
            return ERROR_AO_PARAMETER_INVALID;\
        }\
    }while(0)

/* stb product not usd decimal gain, discard check it */
#define Check_SndVolume(s32IntegerGain, s32DecimalGain) do{\
        if(s32IntegerGain > AOUT_VOL_DB_ZERO ||\
           s32IntegerGain < AOUT_VOL_DB_MIN/* ||*/\
           /*s32DecimalGain > 7 ||*/\
           /*s32DecimalGain < 0*/)\
        {\
            HAL_ERROR("check volume value(%d, %d) is invalid\n", s32IntegerGain, s32DecimalGain);\
            return ERROR_AO_PARAMETER_INVALID;\
        }\
    }while(0)

#define Check_TrackVolume(s32IntegerGain, s32DecimalGain) do{\
        if(s32IntegerGain > AOUT_VOL_DB_MAX ||\
           s32IntegerGain < AOUT_VOL_DB_MIN/* ||*/\
           /*s32DecimalGain > 7 ||*/\
           /*s32DecimalGain < 0*/)\
        {\
            HAL_ERROR("check volume value(%d, %d) is invalid\n", s32IntegerGain, s32DecimalGain);\
            return ERROR_AO_PARAMETER_INVALID;\
        }\
    }while(0)

#define Check_TrackGAIN_LINEMODE(s32IntegerGain, s32DecimalGain) do{\
        if(s32IntegerGain > TRACK_VOL_MAX ||\
           s32IntegerGain < TRACK_VOL_MIN/* ||*/\
           /*s32DecimalGain > 7 ||*/\
           /*s32DecimalGain < 0*/)\
        {\
            HAL_ERROR("check volume value(%d, %d) is invalid\n", s32IntegerGain, s32DecimalGain);\
            return ERROR_AO_PARAMETER_INVALID;\
        }\
    }while(0)

#define Check_TrackGAIN(s32IntegerGain, s32DecimalGain) do{\
        if(s32IntegerGain > TRACK_VOL_DB_MAX ||\
           s32IntegerGain < TRACK_VOL_DB_MIN/* ||*/\
           /*s32DecimalGain > 7 ||*/\
           /*s32DecimalGain < 0*/)\
        {\
            HAL_ERROR("check volume value(%d, %d) is invalid\n", s32IntegerGain, s32DecimalGain);\
            return ERROR_AO_PARAMETER_INVALID;\
        }\
    }while(0)

#define Check_DeviceTypeMultiBit( enOutputDevice) do{\
        U32 i;\
        U32 j = 0;\
        for(i = 0; i < DEVICE_SUPPORT_MAX; i++)\
        {\
            if((U32)(1 << i) == ((1 << i)&enOutputDevice))\
                j++;\
        }\
        if(j > 1)\
        {\
            HAL_ERROR("outputDevice invalid multibit(0x%x)", enOutputDevice);\
            return ERROR_AO_PARAMETER_INVALID;\
        }\
    }while(0)

extern S32 av_get_sdk_avplay_hdl(const HANDLE hAvHandle, HANDLE* phSdkAvPlayHdl);

S32 disable_audio_output(VOID)
{
    U32 i = 0;
    S32 s32Ret = SUCCESS;

    /*save all audio output status.*/
    for (i = 0; i < sizeof(g_audioStatus) / sizeof(AO_MUTE_STATUS_S); i++)
    {
        s32Ret = HI_UNF_SND_GetMute(g_audioStatus[i].enSound, g_audioStatus[i].enOutPort, &g_audioStatus[i].bMute);
        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("ERR: HI_UNF_SND_GetMute fail! i=%d s32Ret=%x", i, s32Ret);
        }
    }

    /*mute all audio output.*/
    for (i = 0; i < sizeof(g_audioStatus) / sizeof(AO_MUTE_STATUS_S); i++)
    {
        s32Ret = HI_UNF_SND_SetMute(g_audioStatus[i].enSound, g_audioStatus[i].enOutPort, HI_TRUE);
        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("ERR: HI_UNF_SND_GetMute fail! i=%d s32Ret=%x", i, s32Ret);
        }
    }

    return SUCCESS;
}

S32 restore_audio_output(VOID)
{
    U32 i = 0;
    S32 s32Ret = SUCCESS;

    /*restore all audio output status.*/
    for (i = 0; i < sizeof(g_audioStatus) / sizeof(AO_MUTE_STATUS_S); i++)
    {
        s32Ret = HI_UNF_SND_SetMute(g_audioStatus[i].enSound, g_audioStatus[i].enOutPort, g_audioStatus[i].bMute);
        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("ERR: HI_UNF_SND_SetMute fail! i=%d s32Ret=%x", i, s32Ret);
        }
    }

    return SUCCESS;
}

static S32 build_sound_attr(HI_UNF_SND_ATTR_S* pstAttr, AOUT_SETTINGS_S stSettings)
{
    if (AOUT_DEVICE_NONE == stSettings.enOutputDevice)
    {
        HAL_ERROR("no found port");
        return FAILURE;
    }
    else if (AOUT_DEVICE_ALL == stSettings.enOutputDevice)
    {
        HAL_DEBUG("found all port use default port");
        return SUCCESS;
    }

    pstAttr->u32PortNum = 0;

    if ((S32)AOUT_DEVICE_SPEAKER & (S32)stSettings.enOutputDevice)
    {
        pstAttr->stOutport[pstAttr->u32PortNum].enOutPort = HI_UNF_SND_OUTPUTPORT_EXT_DAC1;
        pstAttr->stOutport[pstAttr->u32PortNum].unAttr.stDacAttr.u32Reserved = 0;
        pstAttr->u32PortNum++;
    }

    if ((S32)AOUT_DEVICE_SPDIF & (S32)stSettings.enOutputDevice)
    {
        pstAttr->stOutport[pstAttr->u32PortNum].enOutPort = HI_UNF_SND_OUTPUTPORT_SPDIF0;
        pstAttr->stOutport[pstAttr->u32PortNum].unAttr.stSpdifAttr.u32Reserved = 0;
        pstAttr->u32PortNum++;
    }

    if ((S32)AOUT_DEVICE_HDMI & (S32)stSettings.enOutputDevice)
    {
        pstAttr->stOutport[pstAttr->u32PortNum].enOutPort = HI_UNF_SND_OUTPUTPORT_HDMI0;
        pstAttr->stOutport[pstAttr->u32PortNum].unAttr.stHDMIAttr.u32Reserved = 0;
        pstAttr->u32PortNum++;
    }

    if ((S32)AOUT_DEVICE_RCA & (S32)stSettings.enOutputDevice)
    {
        pstAttr->stOutport[pstAttr->u32PortNum].enOutPort = HI_UNF_SND_OUTPUTPORT_DAC0;
        pstAttr->stOutport[pstAttr->u32PortNum].unAttr.stDacAttr.u32Reserved = 0;
        pstAttr->u32PortNum++;
    }

    if ((S32)AOUT_DEVICE_ARC & (S32)stSettings.enOutputDevice)
    {
        pstAttr->stOutport[pstAttr->u32PortNum].enOutPort = HI_UNF_SND_OUTPUTPORT_ARC0;
        pstAttr->stOutport[pstAttr->u32PortNum].unAttr.stArcAttr.u32Reserved = 0;
        pstAttr->u32PortNum++;
    }

    return SUCCESS;
}

//called after Check_DeviceTypeMultiBit
static HI_UNF_SND_OUTPUTPORT_E convert_devicetype_to_port(AOUT_DEVICE_TYPE_E enOutputDevice)
{
    HI_UNF_SND_OUTPUTPORT_E enOutput = HI_UNF_SND_OUTPUTPORT_BUTT;

    if (AOUT_DEVICE_SPEAKER == enOutputDevice)
    {
        enOutput = HI_UNF_SND_OUTPUTPORT_I2S0;
    }
    else if (AOUT_DEVICE_SPDIF == enOutputDevice)
    {
        enOutput = HI_UNF_SND_OUTPUTPORT_SPDIF0;
    }
    else if (AOUT_DEVICE_HDMI == enOutputDevice)
    {
        enOutput = HI_UNF_SND_OUTPUTPORT_HDMI0;
    }
    else if (AOUT_DEVICE_RCA == enOutputDevice)
    {
        enOutput = HI_UNF_SND_OUTPUTPORT_DAC0;
    }
    else if (AOUT_DEVICE_ARC == enOutputDevice)
    {
        enOutput = HI_UNF_SND_OUTPUTPORT_ARC0;
    }
    else
    {
        enOutput = HI_UNF_SND_OUTPUTPORT_BUTT;
    }

    return enOutput;
}

static HI_UNF_SND_OUTPUTPORT_E convert_devicetype_multibit_to_port(S32 s32Index,
        AOUT_DEVICE_TYPE_E enOutputDevice)
{
    HI_UNF_SND_OUTPUTPORT_E enOutPort = HI_UNF_SND_OUTPUTPORT_BUTT;

    if ((1 << s32Index)&enOutputDevice)
    {
        if (0 == s32Index)
        {
            enOutPort = HI_UNF_SND_OUTPUTPORT_DAC0;
        }
        else if (1 == s32Index)
        {
            enOutPort = HI_UNF_SND_OUTPUTPORT_SPDIF0;
        }
        else if (2 == s32Index)
        {
            enOutPort = HI_UNF_SND_OUTPUTPORT_HDMI0;
        }
        else if (3 == s32Index)
        {
            enOutPort = HI_UNF_SND_OUTPUTPORT_I2S0;
        }
        else if (4 == s32Index)
        {
            enOutPort = HI_UNF_SND_OUTPUTPORT_ARC0;
        }
        else
        {
            enOutPort = HI_UNF_SND_OUTPUTPORT_BUTT;
        }
    }

    return enOutPort;
}

static S32 push_track_rm(HANDLE hTrack, HI_UNF_SND_TRACK_TYPE_E enTrackType)
{
    U32 i = 0;

    for (i = 0; i < (U32)TRACK_SUPPORT_MAX; i++)
    {
        if (TRACK_HANDLE_UNUSED == (HANDLE)s_stAoGlobalRM.astTrackEntity[i].hTrack)
        {
            s_stAoGlobalRM.astTrackEntity[i].hTrack = hTrack;
            s_stAoGlobalRM.astTrackEntity[i].enTrackType = enTrackType;
            s_stAoGlobalRM.astTrackEntity[i].enFormat = AOUT_DATA_FORMAT_LE_PCM_16_BIT;
            s_stAoGlobalRM.astTrackEntity[i].u32SampleRate = 0;
            s_stAoGlobalRM.astTrackEntity[i].u32Channels = 0;
            s_stAoGlobalRM.astTrackEntity[i].u32BufferSize = 0;
            s_stAoGlobalRM.astTrackEntity[i].u32FrameBytes = 0;
            s_stAoGlobalRM.astTrackEntity[i].bStarted = FALSE;
            break;
        }
    }

    if ((U32)TRACK_SUPPORT_MAX == i)
    {
        return FAILURE;
    }

    return  SUCCESS;
}

static S32 pop_track_rm(HANDLE hTrack)
{
    U32 i = 0;

    for (i = 0; i < (U32)TRACK_SUPPORT_MAX; i++)
    {
        if (hTrack == (HANDLE)s_stAoGlobalRM.astTrackEntity[i].hTrack)
        {
            memset(&s_stAoGlobalRM.astTrackEntity[i], 0, sizeof(TRACK_RM_S));
            s_stAoGlobalRM.astTrackEntity[i].hTrack = TRACK_HANDLE_UNUSED;
            break;
        }
    }

    if ((U32)TRACK_SUPPORT_MAX == i)
    {
        return FAILURE;
    }

    return  SUCCESS;
}

static S32 fetch_track_rm(HANDLE hTrack, TRACK_RM_S** ppstTrackRM)
{
    U32 i = 0;
    Check_NullPtr(ppstTrackRM);

    for (i = 0; i < (U32)TRACK_SUPPORT_MAX; i++)
    {
        if (hTrack == (HANDLE)s_stAoGlobalRM.astTrackEntity[i].hTrack)
        {
            *ppstTrackRM = &s_stAoGlobalRM.astTrackEntity[i];
            break;
        }
    }

    if ((U32)TRACK_SUPPORT_MAX == i)
    {
        return FAILURE;
    }

    return  SUCCESS;
}

static S32 set_track_rm(HANDLE hTrack, const AOUT_TRACK_PARAMS_S* pstParams)
{
    U32 i;
    TRACK_RM_S* pstTrackRM = NULL;

    for (i = 0; i < TRACK_SUPPORT_MAX; i++)
    {
        if (hTrack == (HANDLE)s_stAoGlobalRM.astTrackEntity[i].hTrack)
        {
            pstTrackRM = &s_stAoGlobalRM.astTrackEntity[i];
            break;
        }
    }

    if (TRACK_SUPPORT_MAX <= i) //TODO
    {
        return ERROR_AO_TRACK_NOT_CREATED;
    }

    if (NULL == pstTrackRM)
    {
        return ERROR_AO_TRACK_NOT_CREATED;
    }

    if (TRUE == pstTrackRM->bStarted)
    {
        return ERROR_NOT_SUPPORTED;
    }

    pstTrackRM->enFormat = pstParams->enFormat;
    pstTrackRM->u32SampleRate = pstParams->u32SampleRate;
    pstTrackRM->u32Channels = pstParams->u32Channels;
    pstTrackRM->u32BufferSize = pstParams->u32BufferSize;
    pstTrackRM->u32FrameBytes = pstParams->u32Channels * 2;   //only support 16Bitdept

    pstTrackRM->u32BufferMs = (pstTrackRM->u32BufferSize / pstTrackRM->u32FrameBytes) * 1000 / pstTrackRM->u32SampleRate;

    HAL_DEBUG("pstTrackRM->enFormat:%d\n", pstParams->enFormat);
    HAL_DEBUG("pstTrackRM->u32SampleRate:%d\n", pstParams->u32SampleRate);
    HAL_DEBUG("pstTrackRM->u32Channels:%d\n", pstParams->u32Channels);
    HAL_DEBUG("pstTrackRM->u32BufferSize:%d\n", pstParams->u32BufferSize);
    HAL_DEBUG("pstTrackRM->u32FrameBytes:%d\n", pstTrackRM->u32FrameBytes);
    HAL_DEBUG("pstTrackRM->u32BufferMs:%d\n", pstTrackRM->u32BufferMs);

    if (TRACK_DEFAULT_BUFMS < pstTrackRM->u32BufferMs)  //TODO
    {
        HAL_ERROR("stTrackRM.u32BufferMs (%d) > 400ms\n", pstTrackRM->u32BufferMs);
        return ERROR_AO_PARAMETER_INVALID;
    }

    return  SUCCESS;
}

static S32 track_setparams(HANDLE hTrack, const AOUT_TRACK_PARAMS_S* pstParams)
{
    S32 s32Ret;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;
    Check_NullPtr(pstParams);
    trace();

    if (0 == pstParams->u32Channels || 0 == pstParams->u32BufferSize ||
        0 == pstParams->u32SampleRate)
    {
        HAL_DEBUG("invalid param enFormat:%d channels:%d SampleRate:%d BufferSize:%d",
                  pstParams->enFormat, pstParams->u32Channels,
                  pstParams->u32SampleRate, pstParams->u32BufferSize);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_GetTrackAttr((HI_HANDLE)hTrack, &stTrackAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_GetTrackAttr failed(0x%x)", s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    stTrackAttr.u32OutputBufSize = pstParams->u32BufferSize;

    s32Ret = set_track_rm(hTrack, pstParams);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AO_PARAMETER_INVALID, "set_track_rm failed(0x%x)", s32Ret);

    s32Ret = HI_UNF_SND_SetTrackAttr((HI_HANDLE)hTrack, &stTrackAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_SetTrackAttr failed(0x%x)", s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    return SUCCESS;
}

static S32 snd_set_spdif_mode(HANDLE hAout, HI_UNF_SND_OUTPUTPORT_E enOutPort, AOUT_DIGITAL_OUTPUT_MODE_E enMode)
{
    S32 s32Ret;
    HI_UNF_SND_SPDIF_MODE_E enSpdifMode;

    if (AOUT_DIGITAL_OUTPUT_MODE_PCM == enMode)
    {
        enSpdifMode = HI_UNF_SND_SPDIF_MODE_LPCM;
    }
    else if (AOUT_DIGITAL_OUTPUT_MODE_RAW == enMode)
    {
        enSpdifMode = HI_UNF_SND_SPDIF_MODE_RAW;
    }
    else
    {
        HAL_ERROR("Invalid AoutDigitalMode(0x%x)", enMode);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_SetSpdifMode((HI_UNF_SND_E) hAout, enOutPort, enSpdifMode);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_SetSpdifMode  failed(0x%x)", s32Ret);
        s32Ret = HI_ERR_AO_SOUND_NOT_OPEN == s32Ret ? ERROR_AO_NOT_OPENED : ERROR_AO_PARAMETER_INVALID;
        return s32Ret;
    }

    return SUCCESS;
}

static S32 snd_set_hdmi_mode(HANDLE hAout, HI_UNF_SND_OUTPUTPORT_E enOutPort, AOUT_DIGITAL_OUTPUT_MODE_E enMode)
{
    S32 s32Ret;
    HI_UNF_SND_HDMI_MODE_E enHdmiMode;

    if (AOUT_DIGITAL_OUTPUT_MODE_PCM == enMode)
    {
        enHdmiMode = HI_UNF_SND_HDMI_MODE_LPCM;
    }
    else if (AOUT_DIGITAL_OUTPUT_MODE_RAW == enMode)
    {
        enHdmiMode = HI_UNF_SND_HDMI_MODE_RAW;
    }
    else if (AOUT_DIGITAL_OUTPUT_MODE_AUTO == enMode)
    {
        enHdmiMode = HI_UNF_SND_HDMI_MODE_AUTO;
    }
    else
    {
        HAL_ERROR("Invalid AoutDigitalMode2(0x%x)", enMode);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_SetHdmiMode((HI_UNF_SND_E)hAout, enOutPort, enHdmiMode);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_SetHdmiMode  failed(0x%x)", s32Ret);
        s32Ret = HI_ERR_AO_SOUND_NOT_OPEN == s32Ret ? ERROR_AO_NOT_OPENED : ERROR_AO_PARAMETER_INVALID;
        return s32Ret;
    }

    return SUCCESS;
}

static S32 snd_get_spdif_mode(HANDLE hAout, HI_UNF_SND_OUTPUTPORT_E enOutPort, AOUT_DIGITAL_OUTPUT_MODE_E* penMode)
{
    S32 s32Ret;
    HI_UNF_SND_SPDIF_MODE_E enSpdifMode;

    s32Ret = HI_UNF_SND_GetSpdifMode((HI_UNF_SND_E)hAout, enOutPort, &enSpdifMode);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_GetSpdifMode failed(0x%x)", s32Ret);

        s32Ret = HI_ERR_AO_SOUND_NOT_OPEN == s32Ret ? ERROR_AO_NOT_OPENED : ERROR_AO_PARAMETER_INVALID;
        return s32Ret;
    }

    if (HI_UNF_SND_SPDIF_MODE_LPCM == enSpdifMode)
    {
        *penMode = AOUT_DIGITAL_OUTPUT_MODE_PCM;
    }
    else if (HI_UNF_SND_SPDIF_MODE_RAW == enSpdifMode)
    {
        *penMode = AOUT_DIGITAL_OUTPUT_MODE_RAW;
    }
    else
    {
        HAL_ERROR("get Invalid enSpdifMode(0x%x)", enSpdifMode);
        return ERROR_AO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

static S32 snd_get_hdmi_mode(HANDLE hAout, HI_UNF_SND_OUTPUTPORT_E enOutPort, AOUT_DIGITAL_OUTPUT_MODE_E* penMode)
{
    S32 s32Ret;
    HI_UNF_SND_HDMI_MODE_E enHdmiMode;

    s32Ret = HI_UNF_SND_GetHdmiMode((HI_UNF_SND_E)hAout, enOutPort, &enHdmiMode);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_GetHdmiMode failed(0x%x)", s32Ret);
        s32Ret = HI_ERR_AO_SOUND_NOT_OPEN == s32Ret ? ERROR_AO_NOT_OPENED : ERROR_AO_PARAMETER_INVALID;
        return s32Ret;
    }

    if (HI_UNF_SND_HDMI_MODE_LPCM == enHdmiMode)
    {
        *penMode = AOUT_DIGITAL_OUTPUT_MODE_PCM;
    }
    else if (HI_UNF_SND_HDMI_MODE_RAW == enHdmiMode)
    {
        *penMode = AOUT_DIGITAL_OUTPUT_MODE_RAW;
    }
    else if (HI_UNF_SND_HDMI_MODE_AUTO == enHdmiMode)
    {
        *penMode = AOUT_DIGITAL_OUTPUT_MODE_AUTO;
    }
    else
    {
        HAL_ERROR("Get Invalid enHdmiMode(0x%x)", enHdmiMode);
        return ERROR_AO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

static S32 out_init(struct _AOUT_DEVICE_S* pstDev __unused, const AOUT_INIT_PARAMS_S* pstInitParams __unused)
{
    HI_S32 s32Ret;
    U32 i;
    trace();

    AOUT_LOCK(&g_stAOutMutex);
    if (0 == s_bAoutInitCount)
    {
        s32Ret = HI_UNF_SND_Init();
        if (HI_ERR_AO_CREATE_FAIL == s32Ret)
        {
            HAL_ERROR("HI_UNF_SND_Init failed(0x%x)", s32Ret);
            AOUT_UNLOCK(&g_stAOutMutex);
            return ERROR_AO_INIT_FAILED;
        }

        memset(&s_stAoGlobalRM, 0, sizeof(AO_GLOBAL_RM_S));

        for (i = 0; i < TRACK_SUPPORT_MAX; i++)
        {
            s_stAoGlobalRM.astTrackEntity[i].hTrack = TRACK_HANDLE_UNUSED;
        }

        for (i = 0; i < AOUT_ID_NUM; i++)
        {
            s_abAoutInstanceStatus[i] = FALSE;
        }
    }

    s_bAoutInitCount++;
    AOUT_UNLOCK(&g_stAOutMutex);

    return SUCCESS;
}

static S32 out_term(struct _AOUT_DEVICE_S* pstDev __unused, const AOUT_TERM_PARAMS_S* pstTermParams __unused)
{
    HI_S32 s32Ret;
    trace();

    AOUT_LOCK(&g_stAOutMutex);
    if (0 == s_bAoutInitCount)
    {
        AOUT_UNLOCK(&g_stAOutMutex);
        HAL_ERROR("Aout already deinit.");
        return SUCCESS;
    }

    if (1 == s_bAoutInitCount)
    {
        s32Ret = HI_UNF_SND_DeInit();
        if (HI_SUCCESS != s32Ret)
        {
            AOUT_UNLOCK(&g_stAOutMutex);
            return FAILURE;
        }
    }

    s_bAoutInitCount--;
    AOUT_UNLOCK(&g_stAOutMutex);

    return SUCCESS;
}

static S32 out_get_capability(struct _AOUT_DEVICE_S* pstDev __unused, AOUT_CAPABILITY_S* pstCapability)
{
    trace();
    Check_NullPtr(pstCapability);
    Check_Inited();


#ifdef  STB_AOUT_SUPPORT //3796m
    pstCapability->u8SupportedIdNum = AOUT_DEVICE_SUPPORT_NUM;
    pstCapability->enOutputDevice[0] = AOUT_DEVICE_RCA;
    pstCapability->u8SupportedTrackNum[0] = 5;
    pstCapability->enOutputDevice[1] = AOUT_DEVICE_SPDIF;
    pstCapability->enOutputDevice[2] = AOUT_DEVICE_HDMI;
#else //todo
    pstCapability->u8SupportedIdNum = AOUT_ID_NUM;
    pstCapability->enOutputDevice[0] = AOUT_DEVICE_RCA;
    pstCapability->u8SupportedTrackNum[0] = 5;
    pstCapability->enOutputDevice[1] = AOUT_DEVICE_SPDIF;   //exclusive use with ARC
    pstCapability->enOutputDevice[2] = AOUT_DEVICE_SPEAKER;
    pstCapability->enOutputDevice[3] = AOUT_DEVICE_ARC;
#endif

    return SUCCESS;
}

static S32 out_open(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE* phAout, const AOUT_OPEN_PARAMS_S* pstOpenParams)
{
    S32 s32Ret;
    HI_UNF_SND_ATTR_S stAttr;
    HI_UNF_SND_E enSound;
    U32 u32Index;
    trace();

    Check_Inited();
    Check_NullPtr(phAout);
    Check_NullPtr(pstOpenParams);
    Check_AoutHandle2SoundID(pstOpenParams->enId, enSound);

    if (HI_UNF_SND_BUTT <= enSound)
    {
        HAL_ERROR("enSound is INVALID (0x%x)", enSound);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_GetDefaultOpenAttr(enSound,  &stAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("SND_GetDefaultOpenAttr(0x%x)", s32Ret);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = build_sound_attr(&stAttr, pstOpenParams->stSettings);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("not support aout settings(0x%x)", pstOpenParams->stSettings.enOutputDevice);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_Open(enSound, &stAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_Open failed(0x%x)", s32Ret);
        return s32Ret == FAILURE ? FAILURE : ERROR_AO_PARAMETER_INVALID;
    }

    /** sound card instance index(enSound) must less than  AOUT_ID_NUM*/
    assert(enSound < AOUT_ID_NUM);
    /**record sound card instance open/close status  */
    u32Index = (U32)enSound;
    s_abAoutInstanceStatus[u32Index] = TRUE;

    *phAout = enSound;

    return SUCCESS;
}

static S32 out_close(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout, const AOUT_CLOSE_PARAMS_S* pstCloseParams __unused)
{
    S32 s32Ret;
    U32 u32Index;

    trace();
    Check_Inited();
    Check_AoutHandle(hAout);

    s32Ret = HI_UNF_SND_Close((HI_UNF_SND_E)hAout);
    if (SUCCESS != s32Ret)  //HI_ERR_AO_SOUND_NOT_OPEN
    {
        HAL_ERROR("HI_UNF_SND_Close failed(0x%x)", s32Ret);
        return ERROR_AO_NOT_OPENED;
    }

    u32Index = (U32)(hAout);
    /** sound card instance index(enSound) must less than  AOUT_ID_NUM*/
    assert(u32Index < AOUT_ID_NUM);

    /**record sound card instance open/close status  */
    s_abAoutInstanceStatus[u32Index] = FALSE;

    return SUCCESS;
}

static S32 out_set_volume(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout, AOUT_DEVICE_TYPE_E enOutputDevice,
                          S32 s32IntGain, S32 s32DecGain)
{
    S32 s32Ret = SUCCESS;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    U32 i = 0;
    trace();

    Check_Inited();
    Check_AoutHandle(hAout);
    Check_DeviceType(enOutputDevice);
    Check_SndVolume(s32IntGain, s32DecGain);
#ifndef STB_AOUT_SUPPORT
    HI_UNF_SND_PRECIGAIN_ATTR_S stGain;
    stGain.s32IntegerGain = s32IntGain;
    stGain.s32DecimalGain = s32DecGain;
#endif

    if (AOUT_DEVICE_ALL == enOutputDevice)
    {
#ifdef STB_AOUT_SUPPORT
        HI_UNF_SND_GAIN_ATTR_S stGain;
        stGain.bLinearMode = HI_FALSE;
        stGain.s32Gain = (s32IntGain < -70) ? -70 : s32IntGain;
        s32Ret = HI_UNF_SND_SetVolume((HI_UNF_SND_E)hAout, HI_UNF_SND_OUTPUTPORT_ALL, &stGain);
#else
        s32Ret = HI_UNF_SND_SetPrecisionVolume((HI_UNF_SND_E)hAout, HI_UNF_SND_OUTPUTPORT_ALL,  &stGain);
#endif

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_UNF_SND_Set Volume failed(0x%x)", s32Ret);
            HAL_CHK_RETURN_NO_PRINT((HI_ERR_AO_NOTSUPPORT == s32Ret), ERROR_NOT_SUPPORTED);
            HAL_CHK_RETURN_NO_PRINT((HI_ERR_AO_SOUND_NOT_OPEN == s32Ret), ERROR_AO_NOT_OPENED);

            return ERROR_AO_PARAMETER_INVALID;
        }

        AOUT_LOCK(&g_stAOutMutex);
        s_stAoGlobalRM.astSndEntity[(HI_UNF_SND_E)hAout].s32IntGain[0] = s32IntGain;
        s_stAoGlobalRM.astSndEntity[(HI_UNF_SND_E)hAout].s32IntGain[1] = s32IntGain;
        s_stAoGlobalRM.astSndEntity[(HI_UNF_SND_E)hAout].s32IntGain[2] = s32IntGain;
        AOUT_UNLOCK(&g_stAOutMutex);

        return SUCCESS;
    }

    for (i = 0; i < DEVICE_SUPPORT_MAX; i++)
    {
        enOutPort = convert_devicetype_multibit_to_port(i, enOutputDevice);

        if (HI_UNF_SND_OUTPUTPORT_BUTT != enOutPort)
        {
#ifdef STB_AOUT_SUPPORT
            HI_UNF_SND_GAIN_ATTR_S stGain;
            stGain.bLinearMode = HI_FALSE;
            stGain.s32Gain = (s32IntGain < -70) ? -70 : s32IntGain;
            s32Ret = HI_UNF_SND_SetVolume((HI_UNF_SND_E)hAout, enOutPort, &stGain);
#else
            s32Ret = HI_UNF_SND_SetPrecisionVolume((HI_UNF_SND_E)hAout, enOutPort,  &stGain);
#endif

            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("HI_UNF_SND_Set Volume failed(0x%x)", s32Ret);
                HAL_CHK_RETURN_NO_PRINT((HI_ERR_AO_NOTSUPPORT == s32Ret), ERROR_NOT_SUPPORTED);
                HAL_CHK_RETURN_NO_PRINT((HI_ERR_AO_SOUND_NOT_OPEN == s32Ret), ERROR_AO_NOT_OPENED);

                return ERROR_AO_PARAMETER_INVALID;
            }

            AOUT_LOCK(&g_stAOutMutex);

            if (HI_UNF_SND_OUTPUTPORT_DAC0 == enOutPort)
            {
                s_stAoGlobalRM.astSndEntity[(HI_UNF_SND_E)hAout].s32IntGain[0] = s32IntGain;
            }
            else if (HI_UNF_SND_OUTPUTPORT_SPDIF0 == enOutPort)
            {
                s_stAoGlobalRM.astSndEntity[(HI_UNF_SND_E)hAout].s32IntGain[1] = s32IntGain;
            }
            else if (HI_UNF_SND_OUTPUTPORT_HDMI0 == enOutPort)
            {
                s_stAoGlobalRM.astSndEntity[(HI_UNF_SND_E)hAout].s32IntGain[2] = s32IntGain;
            }

            AOUT_UNLOCK(&g_stAOutMutex);
        }
    }

    return SUCCESS;
}

static S32 out_get_volume(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout, AOUT_DEVICE_TYPE_E enOutputDevice,
                          S32* ps32IntGain, S32* ps32DecGain)
{
    S32 s32Ret = SUCCESS;
#ifndef STB_AOUT_SUPPORT
    HI_UNF_SND_PRECIGAIN_ATTR_S stPreGain;
#endif
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    trace();

    Check_Inited();
    Check_NullPtr(ps32IntGain);
    Check_NullPtr(ps32DecGain);
    Check_AoutHandle(hAout);
    Check_DeviceType(enOutputDevice);
    Check_DeviceTypeMultiBit(enOutputDevice);

    enOutPort = convert_devicetype_to_port(enOutputDevice);
    if (HI_UNF_SND_OUTPUTPORT_BUTT == enOutPort)
    {
        HAL_ERROR("convert_devicetype_to_port Invalid(0x%x)", enOutPort);
        return ERROR_AO_PARAMETER_INVALID;
    }

#ifdef STB_AOUT_SUPPORT
    HI_UNF_SND_GAIN_ATTR_S stGain;
    stGain.bLinearMode = HI_FALSE;
    s32Ret = HI_UNF_SND_GetVolume((HI_UNF_SND_E)hAout, enOutPort, &stGain);
#else
    s32Ret = HI_UNF_SND_GetPrecisionVolume((HI_UNF_SND_E) hAout, enOutPort, &stPreGain);
#endif

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_Get Volume failed(0x%x)", s32Ret);

        if (HI_ERR_AO_NOTSUPPORT == s32Ret)
        {
            return ERROR_NOT_SUPPORTED;
        }

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }

        return ERROR_AO_PARAMETER_INVALID;
    }

#ifdef STB_AOUT_SUPPORT
    AOUT_LOCK(&g_stAOutMutex);
    if (HI_UNF_SND_OUTPUTPORT_DAC0 == enOutPort)
    {
        *ps32IntGain = s_stAoGlobalRM.astSndEntity[(HI_UNF_SND_E)hAout].s32IntGain[0];
    }
    else if (HI_UNF_SND_OUTPUTPORT_SPDIF0 == enOutPort)
    {
        *ps32IntGain = s_stAoGlobalRM.astSndEntity[(HI_UNF_SND_E)hAout].s32IntGain[1];
    }
    else if (HI_UNF_SND_OUTPUTPORT_HDMI0 == enOutPort)
    {
        *ps32IntGain = s_stAoGlobalRM.astSndEntity[(HI_UNF_SND_E)hAout].s32IntGain[2];
    }
    *ps32DecGain = 0;
    AOUT_UNLOCK(&g_stAOutMutex);
#else
    *ps32IntGain = stPreGain.s32IntegerGain;
    *ps32DecGain = stPreGain.s32DecimalGain;
#endif
    return SUCCESS;
}

static S32 out_set_digital_mode(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout,
                                AOUT_DEVICE_TYPE_E enOutputDevice, AOUT_DIGITAL_OUTPUT_MODE_E enMode)
{
    S32 s32Ret;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    trace();

    Check_Inited();
    Check_AoutHandle(hAout);
    Check_DeviceType(enOutputDevice);
    Check_DeviceTypeMultiBit(enOutputDevice);
    enOutPort = convert_devicetype_to_port(enOutputDevice);

    if (HI_UNF_SND_OUTPUTPORT_BUTT == enOutPort)
    {
        HAL_ERROR("convert_devicetype_to_port Invalid(0x%x)", enOutputDevice);
        return ERROR_AO_PARAMETER_INVALID;
    }

    if (HI_UNF_SND_OUTPUTPORT_SPDIF0 == enOutPort)
    {
        s32Ret = snd_set_spdif_mode(hAout, enOutPort, enMode);
        return s32Ret;
    }
    else  if (HI_UNF_SND_OUTPUTPORT_HDMI0 == enOutPort)
    {
        s32Ret = snd_set_hdmi_mode(hAout, enOutPort, enMode);
        return s32Ret;
    }
    else
    {
        HAL_ERROR("Invalid Parameter3(0x%x)", enOutputDevice);
        return ERROR_AO_PARAMETER_INVALID;
    }

}

static S32 out_get_digital_mode(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout,
                                AOUT_DEVICE_TYPE_E enOutputDevice, AOUT_DIGITAL_OUTPUT_MODE_E* penMode)
{
    S32 s32Ret;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;

    trace();
    Check_Inited();
    Check_NullPtr(penMode);
    Check_AoutHandle(hAout);
    Check_DeviceType(enOutputDevice);
    Check_DeviceTypeMultiBit(enOutputDevice);
    enOutPort = convert_devicetype_to_port(enOutputDevice);

    if (HI_UNF_SND_OUTPUTPORT_DAC0 == enOutPort)
    {
        *penMode = AOUT_DIGITAL_OUTPUT_MODE_PCM;
         return SUCCESS;
    }
    else if (HI_UNF_SND_OUTPUTPORT_SPDIF0 == enOutPort)
    {
        s32Ret = snd_get_spdif_mode(hAout, enOutPort, penMode);
        return s32Ret;
    }
    else  if (HI_UNF_SND_OUTPUTPORT_HDMI0 == enOutPort)
    {
        s32Ret = snd_get_hdmi_mode(hAout, enOutPort, penMode);
        return s32Ret;
    }
    else    //TODO ARC
    {
        HAL_ERROR("get Invalid devicetype(0x%x)", enOutputDevice);
        return ERROR_AO_PARAMETER_INVALID;
    }

}

static S32 out_set_mute(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout,
                        AOUT_DEVICE_TYPE_E enOutputDevice, BOOL bMute)
{
    HI_UNF_SND_OUTPUTPORT_E enOutput;
    U32 i;
    S32 s32Ret;
    trace();

    Check_Inited();
    Check_AoutHandle(hAout);
    Check_DeviceType(enOutputDevice);

    if (AOUT_DEVICE_ALL == enOutputDevice)
    {
        s32Ret = HI_UNF_SND_SetMute((HI_UNF_SND_E)hAout, HI_UNF_SND_OUTPUTPORT_ALL, (HI_BOOL)bMute);
        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_UNF_SND_SetMute failed(0x%x)", s32Ret);

            if (HI_ERR_AO_NOTSUPPORT == s32Ret)
            {
                return ERROR_NOT_SUPPORTED;
            }

            return ERROR_AO_PARAMETER_INVALID;
        }

        return SUCCESS;
    }

    for (i = 0; i < DEVICE_SUPPORT_MAX; i++)
    {
        enOutput = convert_devicetype_multibit_to_port(i, enOutputDevice);
        if (HI_UNF_SND_OUTPUTPORT_BUTT != enOutput)
        {
            s32Ret = HI_UNF_SND_SetMute((HI_UNF_SND_E)hAout, enOutput,  (HI_BOOL)bMute);
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("HI_UNF_SND_SetMute2 failed(0x%x)", s32Ret);

                if (HI_ERR_AO_NOTSUPPORT == s32Ret)
                {
                    return ERROR_NOT_SUPPORTED;
                }

                if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
                {
                    return ERROR_AO_NOT_OPENED;
                }

                return ERROR_AO_PARAMETER_INVALID;
            }
        }
    }

    return SUCCESS;
}

static S32 out_get_mute(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout,
                        AOUT_DEVICE_TYPE_E enOutputDevice, BOOL* pbMute)
{
    S32 s32Ret;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_BOOL bMute;
    trace();

    Check_Inited();
    Check_NullPtr(pbMute);
    Check_AoutHandle(hAout);
    Check_DeviceType(enOutputDevice);
    Check_DeviceTypeMultiBit(enOutputDevice);

    enOutPort = convert_devicetype_to_port(enOutputDevice);
    if (HI_UNF_SND_OUTPUTPORT_BUTT == enOutPort)
    {
        HAL_ERROR("convert_devicetype_to_port Invalid(0x%x)", enOutPort);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_GetMute((HI_UNF_SND_E) hAout, enOutPort, &bMute);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_GetMute failed(0x%x)", s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    *pbMute = (BOOL)bMute;

    return SUCCESS;
}

static S32 out_set_channel_mode(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout,
                                AOUT_DEVICE_TYPE_E enOutputDevice,  AOUT_CHANNEL_MODE_E enMode)
{
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    HI_UNF_TRACK_MODE_E enTrackMode;
    U32 i;
    S32 s32Ret;
    trace();

    Check_Inited();
    Check_AoutHandle(hAout);
    Check_DeviceType(enOutputDevice);

    if (AOUT_CHANNEL_MONO == enMode)
    {
        enTrackMode = HI_UNF_TRACK_MODE_DOUBLE_MONO;
    }
    else if (AOUT_CHANNEL_RIGHT == enMode)
    {
        enTrackMode = HI_UNF_TRACK_MODE_DOUBLE_RIGHT;
    }
    else if (AOUT_CHANNEL_LEFT == enMode)
    {
        enTrackMode = HI_UNF_TRACK_MODE_DOUBLE_LEFT;
    }
    else if (AOUT_CHANNEL_STER == enMode)
    {
        enTrackMode = HI_UNF_TRACK_MODE_STEREO;
    }
    else
    {
        HAL_ERROR("Invalid Channel Mode (0x%x)", enMode);
        return ERROR_AO_PARAMETER_INVALID;
    }

    if (AOUT_DEVICE_ALL == enOutputDevice)
    {
        s32Ret = HI_UNF_SND_SetTrackMode((HI_UNF_SND_E)hAout, HI_UNF_SND_OUTPUTPORT_ALL, enTrackMode);
        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_UNF_SND_SetTrackMode failed(0x%x)", s32Ret);

            if (HI_ERR_AO_NOTSUPPORT == s32Ret)
            {
                return ERROR_NOT_SUPPORTED;
            }

            return ERROR_AO_PARAMETER_INVALID;
        }

        return SUCCESS;
    }

    for (i = 0; i < DEVICE_SUPPORT_MAX; i++)
    {
        enOutPort = convert_devicetype_multibit_to_port(i, enOutputDevice);
        if (HI_UNF_SND_OUTPUTPORT_BUTT != enOutPort)
        {
            s32Ret = HI_UNF_SND_SetTrackMode((HI_UNF_SND_E)hAout, enOutPort,  enTrackMode);
            if (SUCCESS != s32Ret)
            {
                HAL_ERROR("HI_UNF_SND_SetTrackMode2 failed(0x%x)", s32Ret);
                if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
                {
                    return ERROR_AO_NOT_OPENED;
                }
                s32Ret = HI_ERR_AO_NOTSUPPORT == s32Ret ? ERROR_NOT_SUPPORTED : ERROR_AO_PARAMETER_INVALID;
                return s32Ret;
            }
        }
    }

    return SUCCESS;
}

static S32 out_get_channel_mode(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout,
                                AOUT_DEVICE_TYPE_E enOutputDevice,  AOUT_CHANNEL_MODE_E* penMode)
{
    HI_UNF_TRACK_MODE_E enTrackMode;
    HI_UNF_SND_OUTPUTPORT_E enOutPort;
    S32 s32Ret;
    trace();

    Check_Inited();
    Check_NullPtr(penMode);
    Check_AoutHandle(hAout);
    Check_DeviceType(enOutputDevice);
    Check_DeviceTypeMultiBit(enOutputDevice);

    enOutPort = convert_devicetype_to_port(enOutputDevice);
    if (HI_UNF_SND_OUTPUTPORT_BUTT == enOutPort)
    {
        HAL_ERROR("convert_devicetype_to_port Invalid(0x%x)", enOutPort);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_GetTrackMode((HI_UNF_SND_E) hAout, enOutPort, &enTrackMode);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_GetTrackMode failed(0x%x)", s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    if (HI_UNF_TRACK_MODE_STEREO == enTrackMode)
    {
        *penMode = AOUT_CHANNEL_STER;
    }
    else if (HI_UNF_TRACK_MODE_DOUBLE_LEFT == enTrackMode)
    {
        *penMode = AOUT_CHANNEL_LEFT;
    }
    else if (HI_UNF_TRACK_MODE_DOUBLE_RIGHT == enTrackMode)
    {
        *penMode = AOUT_CHANNEL_RIGHT;
    }
    else if (HI_UNF_TRACK_MODE_DOUBLE_MONO == enTrackMode)
    {
        *penMode = AOUT_CHANNEL_MONO;
    }
    else
    {
        HAL_ERROR("Get Invalid TrackMode(0x%x)", enTrackMode);
        return ERROR_AO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

static S32 track_get_default_attr(struct _AOUT_DEVICE_S* pstDev, AOUT_TRACK_PARAMS_S* pstParams)
{

    Check_Inited();
    Check_NullPtr(pstParams);

    pstParams->enFormat = AOUT_DATA_FORMAT_LE_PCM_16_BIT;
    pstParams->bPtsSync = FALSE;
    pstParams->u32BufferSize = (TRACK_DEFAULT_BUFMS * TRACK_DEFAULT_SAMPLERATE * TRACK_DEFAULT_CHANNEL * 2) / 1000;
    pstParams->u32Channels = TRACK_DEFAULT_CHANNEL;
    pstParams->u32SampleRate = TRACK_DEFAULT_SAMPLERATE ;
    return SUCCESS;
}

static S32 track_create(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hAout, HANDLE* phTrack,
                        const AOUT_TRACK_PARAMS_S* pstParams)
{
    S32 s32Ret;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;
    HI_HANDLE hTrack;
    HI_UNF_SND_TRACK_TYPE_E enTrackType = HI_UNF_SND_TRACK_TYPE_SLAVE;
    trace();

    Check_Inited();
    Check_NullPtr(phTrack);
    //Check_NullPtr(pstParams);
    Check_AoutHandle(hAout);

    if (NULL != pstParams)
    {
        enTrackType = pstParams->enFormat == AOUT_DATA_FORMAT_LE_PCM_16_BIT ?
                      HI_UNF_SND_TRACK_TYPE_SLAVE : HI_UNF_SND_TRACK_TYPE_MASTER;
        stTrackAttr.u32OutputBufSize = pstParams->u32BufferSize;
    }
    else
    {
        enTrackType = HI_UNF_SND_TRACK_TYPE_MASTER;
    }

    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(enTrackType, &stTrackAttr);
    HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AO_PARAMETER_INVALID, "HI_UNF_SND_GetDefaultTrackAttr failed(0x%x)", s32Ret);

    s32Ret = HI_UNF_SND_CreateTrack((HI_UNF_SND_E)hAout, &stTrackAttr, &hTrack);
    if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        return ERROR_AO_NOT_OPENED;

    if (SUCCESS != s32Ret && HI_UNF_SND_TRACK_TYPE_MASTER == enTrackType)
    {
        HAL_ERROR("HI_UNF_SND_CreateTrack failed(0x%x)", s32Ret);
        enTrackType = HI_UNF_SND_TRACK_TYPE_SLAVE;

        s32Ret = HI_UNF_SND_GetDefaultTrackAttr(enTrackType, &stTrackAttr);
        HAL_CHK_RETURN((SUCCESS != s32Ret), ERROR_AO_PARAMETER_INVALID, "HI_UNF_SND_GetDefaultTrackAttr failed(0x%x)", s32Ret);

        s32Ret = HI_UNF_SND_CreateTrack((HI_UNF_SND_E)hAout, &stTrackAttr, &hTrack);

        if (SUCCESS == s32Ret)
        {
            //do nothing
        }
        else if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else if (HI_ERR_AO_INVALID_PARA == s32Ret)
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
        else
        {
            return FAILURE;
        }
    }

    *phTrack = hTrack;

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = push_track_rm(hTrack, enTrackType);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("no enough rm malloc for track");
        goto ERR;
    }

    if (NULL == pstParams)
    {
        AOUT_UNLOCK(&g_stAOutMutex);
        return SUCCESS;
    }

    s32Ret = track_setparams(hTrack, pstParams);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("track_setparams failed(0x%x)", s32Ret);
        goto ERR;
    }

    AOUT_UNLOCK(&g_stAOutMutex);

    return SUCCESS;
ERR:
    AOUT_UNLOCK(&g_stAOutMutex);
    s32Ret = HI_UNF_SND_DestroyTrack((HI_HANDLE)hTrack);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "destroy tracj failed(0x%x)", s32Ret);

    return ERROR_AO_PARAMETER_INVALID;
}

static S32 track_destroy(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    trace();

    Check_Inited();

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }


        s32Ret = pop_track_rm(hTrack);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("no find rm for track");
            AOUT_UNLOCK(&g_stAOutMutex);
            return ERROR_AO_TRACK_NOT_CREATED;
        }

        AOUT_UNLOCK(&g_stAOutMutex);

        s32Ret = HI_UNF_SND_DestroyTrack((HI_HANDLE)hTrack);
        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_UNF_SND_DestroyTrack failed(0x%x)", s32Ret);

            if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
            {
                return ERROR_AO_NOT_OPENED;
            }
            else
            {
                return ERROR_AO_PARAMETER_INVALID;
            }
    }

    return s32Ret;
}

#ifndef STB_AOUT_SUPPORT
static S32 attach_normal_source(HANDLE hTrack, HANDLE hSource)
{
    HI_UNF_SND_SOURCE_E enSource = HI_UNF_SND_SOURCE_BUTT;
    switch (hSource)
    {
        case SOURCE_ID_ATV:
            enSource = HI_UNF_SND_SOURCE_ATV;
            break;
        case SOURCE_ID_CVBS1:
        case SOURCE_ID_CVBS2:
        case SOURCE_ID_CVBS3:
            enSource = HI_UNF_SND_SOURCE_AV;
            break;
        case SOURCE_ID_VGA:
            enSource = HI_UNF_SND_SOURCE_VGA;
            break;
        case SOURCE_ID_YPBPR1:
        case SOURCE_ID_YPBPR2:
        case SOURCE_ID_YPBPR3:
            enSource = HI_UNF_SND_SOURCE_YPBPR;
            break;
        case SOURCE_ID_HDMI1:
        case SOURCE_ID_HDMI2:
        case SOURCE_ID_HDMI3:
        case SOURCE_ID_HDMI4:
            enSource = HI_UNF_SND_SOURCE_HDMI;
            break;
        case SOURCE_ID_SCART:
            enSource = HI_UNF_SND_SOURCE_SCART;
            break;
        case SOURCE_ID_DTV:
            enSource = HI_UNF_SND_SOURCE_DTV;
            break;
        case SOURCE_ID_MEDIA:
            enSource = HI_UNF_SND_SOURCE_MEDIA;
            break;
        case SOURCE_ID_EXT:
            enSource = HI_UNF_SND_SOURCE_ALSA;
            break;
        default:
            return FAILURE;
    }

    return HI_UNF_SND_SetTrackSource(hTrack, enSource);
}
#endif
static S32 track_attach_input(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack, HANDLE hSource)
{
    S32 s32Ret;
    HANDLE hAvPlay = 0;
    TRACK_RM_S *pstTrackRM = NULL;
    trace();

    Check_Inited();

#ifndef STB_AOUT_SUPPORT
    s32Ret = attach_normal_source(hTrack, hSource);
    if (SUCCESS == s32Ret)
    {
        return s32Ret;
    }
#endif

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    s32Ret = av_get_sdk_avplay_hdl(hSource, &hAvPlay);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("av_get_sdk_avplay_hdl failed(0x%x)", s32Ret);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_Attach((HI_HANDLE)hTrack, (HI_HANDLE)hAvPlay);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_Attach failed(0x%x)", s32Ret);
        return ERROR_AO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

static S32 track_detach_input(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack, HANDLE hSource)
{
    S32 s32Ret;
    HANDLE hAvPlay = 0;
    TRACK_RM_S *pstTrackRM = NULL;
    trace();

    Check_Inited();

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    s32Ret = av_get_sdk_avplay_hdl(hSource, &hAvPlay);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("av_get_sdk_avplay_hdl failed(0x%x)", s32Ret);
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_Detach((HI_HANDLE)hTrack, (HI_HANDLE)hAvPlay);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_Detach failed(0x%x)", s32Ret);
        return ERROR_AO_PARAMETER_INVALID;
    }

    return SUCCESS;
}

static S32 track_start(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;

    trace();
    Check_Inited();

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

        s32Ret = HI_MPI_AO_Track_Start((HI_HANDLE)hTrack);
        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_MPI_AO_Track_Start failed(0x%x)", s32Ret);
            return ERROR_AO_PARAMETER_INVALID;
        }

    pstTrackRM->bStarted = TRUE;


    return s32Ret;
}

static S32 track_stop(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    trace();

    Check_Inited();

    AOUT_LOCK(&g_stAOutMutex);

    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }


    s32Ret = HI_MPI_AO_Track_Stop((HI_HANDLE)hTrack);  //TODO
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_MPI_AO_Track_Stop failed(0x%x)", s32Ret);

        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_PARAMETER_INVALID;
    }

    pstTrackRM->bStarted = FALSE;

    AOUT_UNLOCK(&g_stAOutMutex);
    return s32Ret;
}

static S32 track_pause(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    trace();

    Check_Inited();

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }

    s32Ret = HI_MPI_AO_Track_Pause((HI_HANDLE)hTrack);  //TODO
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_MPI_AO_Track_Pause failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    pstTrackRM->bStarted = TRUE;
    AOUT_UNLOCK(&g_stAOutMutex);

    return s32Ret;
}

static S32 track_resume(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    trace();

    Check_Inited();
    AOUT_LOCK(&g_stAOutMutex);

    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }


    s32Ret = HI_MPI_AO_Track_Resume((HI_HANDLE)hTrack);  //TODO
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_MPI_AO_Track_Resume failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    pstTrackRM->bStarted = TRUE;
    AOUT_UNLOCK(&g_stAOutMutex);

    return s32Ret;
}

static S32 track_flush(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM=NULL;
    trace();

    Check_Inited();
    AOUT_LOCK(&g_stAOutMutex);

    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }


    s32Ret = HI_MPI_AO_Track_Flush((HI_HANDLE)hTrack);  //TODO
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_MPI_AO_Track_Flush failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    pstTrackRM->bStarted = TRUE;
    AOUT_UNLOCK(&g_stAOutMutex);

    return s32Ret;
}

static S32 track_set_params(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack,
                            const AOUT_TRACK_PARAMS_S* pstParams)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM  = NULL;
    Check_Inited();
    Check_NullPtr(pstParams);

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }

    if (pstTrackRM->bStarted)
    {
    AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_NOT_SUPPORTED;
    }

    s32Ret = track_setparams(hTrack, pstParams);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_PARAMETER_INVALID;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    return s32Ret;
}

static S32 track_get_params(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack,
                            AOUT_TRACK_PARAMS_S* pstParams)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    trace();

    Check_Inited();
    Check_NullPtr(pstParams);

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    pstParams->enFormat = pstTrackRM->enFormat;
    pstParams->u32SampleRate = pstTrackRM->u32SampleRate;
    pstParams->u32Channels = pstTrackRM->u32Channels;
    pstParams->u32BufferSize = pstTrackRM->u32BufferSize;

    return SUCCESS;
}

static S32 track_set_mix_params(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack,
                                const AOUT_TRACK_MIX_PARAMS_S* pstParams)   //ignore s32DecimalGain
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    trace();

    Check_Inited();
    Check_NullPtr(pstParams);
    Check_TrackVolume(pstParams->s32IntGain, pstParams->s32DecGain);

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

#ifdef  STB_AOUT_SUPPORT //3796m
    HI_UNF_SND_ABSGAIN_ATTR_S stAbsWeightGain;
    stAbsWeightGain.bLinearMode = HI_FALSE;
    stAbsWeightGain.s32GainL = pstParams->s32IntGain;
    stAbsWeightGain.s32GainR = pstParams->s32IntGain;

    s32Ret = HI_UNF_SND_SetTrackAbsWeight((HI_HANDLE)hTrack, &stAbsWeightGain);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_SetTrackAbsWeight failed(0x%x)", s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }
#else
    HI_UNF_SND_PRECIGAIN_ATTR_S stPreciGain;
    stPreciGain.s32DecimalGain = pstParams->s32DecGain;
    stPreciGain.s32IntegerGain = pstParams->s32IntGain;

    s32Ret = HI_UNF_SND_SetTrackPrescale((HI_HANDLE)hTrack, &stPreciGain);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_SetTrackPrescale failed(0x%x)", s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }
#endif

    return SUCCESS;
}

static S32 track_get_mix_params(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack,
                                AOUT_TRACK_MIX_PARAMS_S* pstParams)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    trace();

    Check_Inited();
    Check_NullPtr(pstParams);

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

#ifdef  STB_AOUT_SUPPORT //3796m
    HI_UNF_SND_ABSGAIN_ATTR_S stAbsWeightGain;

    s32Ret = HI_UNF_SND_GetTrackAbsWeight((HI_HANDLE)hTrack, &stAbsWeightGain);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_GetTrackAbsWeight failed(0x%x)", s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    pstParams->s32IntGain = stAbsWeightGain.s32GainL;
    pstParams->s32DecGain = 0;
#else
    HI_UNF_SND_PRECIGAIN_ATTR_S stPreciGain;

    s32Ret = HI_UNF_SND_GetTrackPrescale((HI_HANDLE)hTrack, &stPreciGain);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_SetTrackPrescale failed(0x%x)", s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    pstParams->s32DecGain = stPreciGain.s32DecimalGain;
    pstParams->s32IntGain = stPreciGain.s32IntegerGain;
#endif

    return SUCCESS;
}

static S32 track_set_mute(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, BOOL bMute)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    HI_BOOL hibMute = HI_FALSE;
    Check_Inited();

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    hibMute = bMute ? HI_TRUE : HI_FALSE;

    s32Ret = HI_UNF_SND_SetTrackMute(hTrack, (HI_BOOL)hibMute);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_SetTrackMute failed(0x%x)", s32Ret);
        return FAILURE;
    }

    return s32Ret;
}

static S32 track_get_mute(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, BOOL* pbMute)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    HI_BOOL hibMute = HI_FALSE;
    Check_Inited();
    Check_NullPtr(pbMute);

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    s32Ret = HI_UNF_SND_GetTrackMute(hTrack, (HI_BOOL*)&hibMute);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s %d HI_UNF_SND_GetTrackMute failed(0x%x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    *pbMute = (hibMute == HI_TRUE) ? TRUE : FALSE;

    return s32Ret;
}

static S32 track_set_channel_mode(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, TRACK_CHANNEL_MODE_E enMode)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    HI_UNF_TRACK_MODE_E enHiMode;
    Check_Inited();

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    if (TRACK_MODE_STEREO == enMode)
    {
        enHiMode = HI_UNF_TRACK_MODE_STEREO;
    }
    else if (TRACK_MODE_DOUBLE_MONO == enMode)
    {
        enHiMode = HI_UNF_TRACK_MODE_DOUBLE_MONO;
    }
    else if (TRACK_MODE_DOUBLE_LEFT == enMode)
    {
        enHiMode = HI_UNF_TRACK_MODE_DOUBLE_LEFT;
    }
    else if (TRACK_MODE_DOUBLE_RIGHT == enMode)
    {
        enHiMode = HI_UNF_TRACK_MODE_DOUBLE_RIGHT;
    }
    else if (TRACK_MODE_EXCHANGE == enMode)
    {
        enHiMode = HI_UNF_TRACK_MODE_EXCHANGE;
    }
    else if (TRACK_MODE_ONLY_RIGHT == enMode)
    {
        enHiMode = HI_UNF_TRACK_MODE_ONLY_RIGHT;
    }
    else if (TRACK_MODE_ONLY_LEFT == enMode)
    {
        enHiMode = HI_UNF_TRACK_MODE_ONLY_LEFT;
    }
    else if (TRACK_MODE_MUTED == enMode)
    {
        enHiMode = HI_UNF_TRACK_MODE_MUTED;
    }
    else
    {
        return ERROR_AO_PARAMETER_INVALID;
    }

    s32Ret = HI_UNF_SND_SetTrackChannelMode(hTrack, enHiMode);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s %d HI_UNF_SND_SetTrackChannelMode failed(0x%x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    return s32Ret;
}

static S32 track_get_channel_mode(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, TRACK_CHANNEL_MODE_E* penMode)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM=NULL;
    Check_Inited();
    Check_NullPtr(penMode);

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    s32Ret = HI_UNF_SND_GetTrackChannelMode(hTrack, (HI_UNF_TRACK_MODE_E*)penMode);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_SetTrackChannelMode failed(0x%x)", s32Ret);
        return FAILURE;
    }

    return s32Ret;
}

static S32 track_set_weight(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                            TRACK_GAIN_ATTR_S stTrackGainAttr)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    Check_Inited();

    if (stTrackGainAttr.bLinearMode)
    {
        Check_TrackGAIN_LINEMODE(stTrackGainAttr.s32Gain, stTrackGainAttr.s32Gain);
    }
    else
    {
        Check_TrackGAIN(stTrackGainAttr.s32Gain, stTrackGainAttr.s32Gain);
    }

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    HI_UNF_SND_GAIN_ATTR_S stGainAttr;
    stGainAttr.bLinearMode = (stTrackGainAttr.bLinearMode == TRUE) ? HI_TRUE : HI_FALSE;
    stGainAttr.s32Gain = stTrackGainAttr.s32Gain;

    s32Ret = HI_UNF_SND_SetTrackWeight(hTrack, &stGainAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_SND_SetTrackWeight failed(0x%x)", s32Ret);
        return FAILURE;
    }

    return s32Ret;
}

static S32 track_get_weight(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                            TRACK_GAIN_ATTR_S* pstTrackGainAttr)
{
    S32 s32Ret;
    TRACK_RM_S *pstTrackRM = NULL;
    Check_Inited();
    Check_NullPtr(pstTrackGainAttr);

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    HI_UNF_SND_GAIN_ATTR_S stGainAttr;
    s32Ret = HI_UNF_SND_GetTrackWeight(hTrack, &stGainAttr);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s %d HI_UNF_SND_GetTrackWeight failed(0x%x)", __func__, __LINE__, s32Ret);
        return FAILURE;
    }

    pstTrackGainAttr->bLinearMode = (stGainAttr.bLinearMode == HI_TRUE) ? TRUE : FALSE;
    pstTrackGainAttr->s32Gain = stGainAttr.s32Gain;

    return s32Ret;
}

static S32 track_get_render_position(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack, U32* pu32Frames)
{
    S32 s32Ret;
    trace();

    Check_Inited();
    Check_NullPtr(pu32Frames);
    TRACK_RM_S *pstTrackRM = NULL;

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    return SUCCESS;
}

static S32 track_get_buf_avail(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack, U32* pu32Bytes)
{
    S32 s32Ret;
    trace();

    Check_Inited();
    Check_NullPtr(pu32Bytes);

    HI_U32 u32DelayMs;
    HI_U32 u32AvalidMs;
    TRACK_RM_S *pstTrackRM= NULL;

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    HAL_DEBUG("stTrackRM.hTrack(0x%x)", pstTrackRM->hTrack);
    HAL_DEBUG("stTrackRM.enFormat(%d)", pstTrackRM->enFormat);
    HAL_DEBUG("stTrackRM.u32SampleRate(%d)", pstTrackRM->u32SampleRate);
    HAL_DEBUG("stTrackRM.u32Channels(%d)", pstTrackRM->u32Channels);
    HAL_DEBUG("stTrackRM.u32BufferSize(%d)", pstTrackRM->u32BufferSize);
    HAL_DEBUG("stTrackRM.u32BufferMs(%d)", pstTrackRM->u32BufferMs);
    HAL_DEBUG("stTrackRM.u32FrameBytes(%d)", pstTrackRM->u32FrameBytes);

    s32Ret = HI_UNF_SND_GetTrackDelayMs(hTrack, &u32DelayMs);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s %d HI_UNF_SND_GetTrackDelayMs failed(0x%x)", __func__, __LINE__, s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    if (pstTrackRM->u32BufferMs < u32DelayMs) //means buf full
    {
        *pu32Bytes = 0;
        return SUCCESS;
    }

    u32AvalidMs = pstTrackRM->u32BufferMs - u32DelayMs;
    if (TRACK_DEFAULT_BUFMS == u32AvalidMs)
    {
        u32AvalidMs -= 1;
    }

    *pu32Bytes = (u32AvalidMs * pstTrackRM->u32SampleRate) * pstTrackRM->u32FrameBytes / 1000;
    return SUCCESS;
}

static S32 track_get_latency(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack, U32* pu32Latency)
{
    S32 s32Ret;
    HI_U32 u32DelayMs;
    trace();

    TRACK_RM_S *pstTrackRM = NULL;
    Check_Inited();
    Check_NullPtr(pu32Latency);

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("fetch_track_rm failed(0x%x)", s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    s32Ret = HI_UNF_SND_GetTrackDelayMs(hTrack, &u32DelayMs);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s %d HI_UNF_SND_GetTrackDelayMs failed(0x%x)", __func__, __LINE__, s32Ret);

        if (HI_ERR_AO_SOUND_NOT_OPEN == s32Ret)
        {
            return ERROR_AO_NOT_OPENED;
        }
        else
        {
            return ERROR_AO_PARAMETER_INVALID;
        }
    }

    *pu32Latency = u32DelayMs;

    return SUCCESS;
}

static S32 track_write(struct _AOUT_DEVICE_S* pstDev __unused, HANDLE hTrack, const void* pvbuffer, U32 u32Bytes)
{
    S32 s32Ret;
    HI_UNF_AO_FRAMEINFO_S stAOFrame;
    TRACK_RM_S *pstTrackRM = NULL;
    HI_U32 u32FrameSample = 0;
    U32 u32AvailableBytes = 0;
    trace();

    Check_Inited();
    Check_NullPtr(pvbuffer);

    AOUT_LOCK(&g_stAOutMutex);
    s32Ret = fetch_track_rm(hTrack, &pstTrackRM);
    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("%s %d fetch_track_rm failed(0x%x)", __func__, __LINE__, s32Ret);
        AOUT_UNLOCK(&g_stAOutMutex);
        return ERROR_AO_TRACK_NOT_CREATED;
    }
    AOUT_UNLOCK(&g_stAOutMutex);

    (void)track_get_buf_avail(NULL, hTrack, &u32AvailableBytes);
    if (u32Bytes > u32AvailableBytes)
    {
        return ERROR_AO_PARAMETER_INVALID;
    }

    HAL_DEBUG("u32Bytes:%d", u32Bytes);
    HAL_DEBUG("stTrackRM->hTrack:%d", pstTrackRM->hTrack);
    HAL_DEBUG("stTrackRM->enFormat:%d", pstTrackRM->enFormat);
    HAL_DEBUG("stTrackRM->u32SampleRate:%d", pstTrackRM->u32SampleRate);
    HAL_DEBUG("stTrackRM->u32Channels:%d", pstTrackRM->u32Channels);
    HAL_DEBUG("stTrackRM->u32BufferSize:%d", pstTrackRM->u32BufferSize);
    HAL_DEBUG("stTrackRM->u32FrameBytes:%d", pstTrackRM->u32FrameBytes);
    HAL_DEBUG("stTrackRM->u32BufferMs:%d", pstTrackRM->u32BufferMs);

    if (0 != pstTrackRM->u32FrameBytes)
    {
        u32FrameSample = u32Bytes / pstTrackRM->u32FrameBytes;
    }

    if (0 != u32Bytes % pstTrackRM->u32FrameBytes)
    {
        HAL_ERROR("the length of data to write not frame align (0x%x/0x%x)", u32Bytes, pstTrackRM->u32FrameBytes);
    }

    stAOFrame.s32BitPerSample = 16;  //TODO only support 16Bitdpt
    stAOFrame.u32Channels   = pstTrackRM->u32Channels;
    stAOFrame.bInterleaved  = HI_TRUE;
    stAOFrame.u32SampleRate = pstTrackRM->u32SampleRate;
    stAOFrame.u32PtsMs = 0xffffffff;
    stAOFrame.ps32BitsBuffer = NULL;
    stAOFrame.u32BitsBytesPerFrame = 0;
    stAOFrame.u32FrameIndex = 0;
    stAOFrame.u32PcmSamplesPerFrame = u32FrameSample;
    stAOFrame.ps32PcmBuffer = (S32*)(pvbuffer);

    s32Ret = HI_UNF_SND_SendTrackData(hTrack, &stAOFrame);
    if (SUCCESS != s32Ret)
    {
        return ERROR_AO_PARAMETER_INVALID;//HI_ERR_AO_OUT_BUF_FULL not continue
    }

    if (TRUE != pstTrackRM->bStarted)
    {
        pstTrackRM->bStarted = TRUE;
    }

    return SUCCESS;
}

static S32 track_get_pts(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, S64* ps64Pts)
{
    return ERROR_NOT_SUPPORTED;
}

static S32 track_adjust_speed(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, S32 s32Speed)
{
    return ERROR_NOT_SUPPORTED;
}

#ifdef TVOS_PLATFORM
static int adev_close(hw_device_t *device)
{
    trace();

    if(device)
        free(device);
    return 0;
}

static int adev_open(const hw_module_t* module, const char* name,
                     hw_device_t** device)
{
    AOUT_DEVICE_S *stAdev;
    int ret;
    trace();

    if (strcmp(name, AOUT_HARDWARE_AOUT0) != 0)
        return -EINVAL;

	if (NULL == device)
	{
		return -EINVAL;
	}

    stAdev = calloc(1, sizeof(AOUT_DEVICE_S));
    if (!stAdev)
        return -ENOMEM;

    stAdev->stCommon.tag = HARDWARE_DEVICE_TAG;
    stAdev->stCommon.version = AOUT_DEVICE_API_VERSION_1_0;
    stAdev->stCommon.module = (struct hw_module_t *) module;
    stAdev->stCommon.close = adev_close;

    stAdev->aout_init = out_init;
    stAdev->aout_term = out_term;
    stAdev->aout_get_capability = out_get_capability;
    stAdev->aout_open = out_open;
    stAdev->aout_close = out_close;
    stAdev->aout_set_volume = out_set_volume;
    stAdev->aout_get_volume = out_get_volume;
    stAdev->aout_set_digital_mode = out_set_digital_mode;
    stAdev->aout_get_digital_mode = out_get_digital_mode;
    stAdev->aout_set_mute = out_set_mute;
    stAdev->aout_get_mute = out_get_mute;
    stAdev->aout_set_channel_mode = out_set_channel_mode;
    stAdev->aout_get_channel_mode = out_get_channel_mode;

    stAdev->track_get_default_attr = track_get_default_attr;
    stAdev->track_create = track_create;
    stAdev->track_destroy = track_destroy;
    stAdev->track_attach_input = track_attach_input;
    stAdev->track_detach_input = track_detach_input;
    stAdev->track_start = track_start;
    stAdev->track_stop = track_stop;
    stAdev->track_pause = track_pause;
    stAdev->track_resume = track_resume;
    stAdev->track_flush = track_flush;
    stAdev->track_set_params = track_set_params;
    stAdev->track_get_params = track_get_params;
    stAdev->track_set_mix_params = track_set_mix_params;
    stAdev->track_get_mix_params = track_get_mix_params;
    stAdev->track_set_mute = track_set_mute;
    stAdev->track_get_mute = track_get_mute;
    stAdev->track_set_channel_mode = track_set_channel_mode;
    stAdev->track_get_channel_mode = track_get_channel_mode;
    stAdev->track_set_weight = track_set_weight;
    stAdev->track_get_weight = track_get_weight;
    stAdev->track_get_render_position = track_get_render_position;
    stAdev->track_get_buf_avail = track_get_buf_avail;
    stAdev->track_get_latency = track_get_latency;
    stAdev->track_write = track_write;
    stAdev->track_get_pts = track_get_pts;
    stAdev->track_adjust_speed = track_adjust_speed;
    *device = &stAdev->stCommon;
    return 0;
}

static struct hw_module_methods_t hal_module_methods = {
    .open = adev_open,
};

AOUT_MODULE_S HAL_MODULE_INFO_SYM = {
    .stCommon = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = 1,
        .id = AOUT_HARDWARE_MODULE_ID,
        .name = "Hisi Aout",
        .author = "His Audio",
        .methods = &hal_module_methods,
    },
};
#endif

static AOUT_DEVICE_S g_stDevice_aout =
{
    .aout_init = out_init,
    .aout_term = out_term,
    .aout_get_capability = out_get_capability,
    .aout_open = out_open,
    .aout_close = out_close,
    .aout_set_volume = out_set_volume,
    .aout_get_volume = out_get_volume,
    .aout_set_digital_mode = out_set_digital_mode,
    .aout_get_digital_mode = out_get_digital_mode,
    .aout_set_mute = out_set_mute,
    .aout_get_mute = out_get_mute,
    .aout_set_channel_mode = out_set_channel_mode,
    .aout_get_channel_mode = out_get_channel_mode,

    .track_get_default_attr = track_get_default_attr,
    .track_create = track_create,
    .track_destroy = track_destroy,
    .track_attach_input = track_attach_input,
    .track_detach_input = track_detach_input,
    .track_start = track_start,
    .track_stop = track_stop,
    .track_pause = track_pause,
    .track_resume = track_resume,
    .track_flush = track_flush,
    .track_set_params = track_set_params,
    .track_get_params = track_get_params,
    .track_set_mix_params = track_set_mix_params,
    .track_get_mix_params = track_get_mix_params,
    .track_set_mute = track_set_mute,
    .track_get_mute = track_get_mute,
    .track_set_channel_mode = track_set_channel_mode,
    .track_get_channel_mode = track_get_channel_mode,
    .track_set_weight = track_set_weight,
    .track_get_weight = track_get_weight,
    .track_get_render_position = track_get_render_position,
    .track_get_buf_avail = track_get_buf_avail,
    .track_get_pts = track_get_pts,
    .track_adjust_speed = track_adjust_speed,
    .track_get_latency = track_get_latency,
    .track_write = track_write,
};

AOUT_DEVICE_S* getAOutDevice()
{
    return &g_stDevice_aout;
}
