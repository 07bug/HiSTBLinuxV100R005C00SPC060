/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
 File Name     : HI.AUDIO.SOUNDTOUCH.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#ifndef __HISI_AUDIO_SONIC_H__
#define __HISI_AUDIO_SONIC_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define ADEC_SONIC_BUFFER_NUM 8

typedef enum
{
    HI_ADEC_SPEED_INT_SLOW = 0,
    HI_ADEC_SPEED_INT_NORMAL = 1,
    HI_ADEC_SPEED_INT_FAST = 2,
    HI_ADEC_SPEED_INT_BUTT,
}HA_ADEC_SPEED_INT_E;

#define HI_ADEC_SAMPLE_RATE_8K  8000
#define HI_ADEC_SAMPLE_RATE_192K  192000

typedef struct
{
    HI_U32  enCmd;
    HI_U32  u32SpeedInt;
    HI_U32  u32SpeedDeci;
    HI_U32  u32Sample; /* 采样率范围为8k~192k */
    HI_U32  u32Channel; /* 取值范围为1~8 */
    HI_U32  u32BitPerSample; /* 只支持16bit和24bit */
} HA_CODEC_SPEED_SET_PARAM_S;

#define HA_CODEC_SPEED_SET_CMD ((((HI_U32)HA_COMMON_CMD_ID) << 16) | 0x101A)

#define HA_SONIC_DecGetDefalutOpenParam(pOpenParam) \
    do{\
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->enDecMode = HD_DEC_MODE_RAWPCM; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->pCodecPrivateData = HI_NULL; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->u32CodecPrivateDataSize = 0; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32DesiredOutChannels = 2; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.bInterleaved  = HI_FALSE; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32BitPerSample = 16; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32DesiredSampleRate = 48000; \
    }while(0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

