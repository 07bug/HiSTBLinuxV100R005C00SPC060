#ifndef __HA_AUDIO_OPUS_CODEC_H__
#define __HA_AUDIO_OPUS_CODEC_H__

#include "hi_type.h"
#include "hi_audio_codec.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

typedef struct {
   HI_S32 s32Version;
   HI_U32 u32Channels; /* Number of channels: 1..255 */
   HI_S32 s32Preskip;
   HI_U32 u32SampleRate;
   HI_S32 s32Gain; /* in dB S7.8 should be zero whenever possible */
   HI_S32 s32ChannelMap;
   /* The rest is only used if channel_mapping != 0 */
   HI_S32 s32NBStreams;
   HI_S32 s32NBCoupled;
   HI_U8  u8StreamMap[255];
} OPUS_HEAD_CONFIG_S;

#define HA_OPUS_DecGetDefalutHeadConfig(pConfigParam) \
    do { \
        ((OPUS_HEAD_CONFIG_S*)(pConfigParam))->s32Version = 1; \
        ((OPUS_HEAD_CONFIG_S*)(pConfigParam))->u32Channels = 2; \
        ((OPUS_HEAD_CONFIG_S*)(pConfigParam))->s32Preskip = 0; \
        ((OPUS_HEAD_CONFIG_S*)(pConfigParam))->u32SampleRate = 0; \
        ((OPUS_HEAD_CONFIG_S*)(pConfigParam))->s32Gain = 0; \
        ((OPUS_HEAD_CONFIG_S*)(pConfigParam))->s32ChannelMap = 0; \
        ((OPUS_HEAD_CONFIG_S*)(pConfigParam))->s32NBStreams = 0; \
        ((OPUS_HEAD_CONFIG_S*)(pConfigParam))->s32NBCoupled = 0; \
        memset(((OPUS_HEAD_CONFIG_S*)(pConfigParam))->u8StreamMap, 0, 255); \
    } while (0)

#define HA_OPUS_DecGetDefalutOpenParam(pOpenParam, pstPrivateParams) \
    do { HI_S32 i; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->enDecMode = HD_DEC_MODE_RAWPCM; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->pCodecPrivateData = HI_NULL; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->u32CodecPrivateDataSize = 0; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32DesiredOutChannels = 2; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.bInterleaved  = HI_TRUE; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32BitPerSample = 16; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->sPcmformat.u32DesiredSampleRate = 48000; \
        for (i = 0; i < HA_AUDIO_MAXCHANNELS; i++) \
        { \
            ((HI_HADECODE_OPENPARAM_S *)pOpenParam)->sPcmformat.enChannelMapping[i] = HA_AUDIO_ChannelNone; \
        } \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->pCodecPrivateData = (HI_VOID*)pstPrivateParams; \
        ((HI_HADECODE_OPENPARAM_S *)(pOpenParam))->u32CodecPrivateDataSize = sizeof(OPUS_HEAD_CONFIG_S); \
    } while (0)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HISI_AUDIO_DECODER_OPUS_H__ */

