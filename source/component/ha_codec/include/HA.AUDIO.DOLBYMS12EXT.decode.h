/******************************************************************************
 Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : HA.AUDIO.DOLBYMS12EXT.decode.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#ifndef __HA_AUDIO_DOLBYMS12EXT_DECODE_H__
#define __HA_AUDIO_DOLBYMS12EXT_DECODE_H__

#include "hi_type.h"
#include "hi_audio_codec.h"
#include "HA.AUDIO.DOLBYMS12.decode.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define  MS12_MAX_STREAM_NUM         (6)
#define  MS12_MIXER_NUM              (2)
#define  MS12_MIXER_MAX_SOURCE_NUM   (3)

#define  MS12_SUPPORT_FORMAT_DDP     (1 << 0)
#define  MS12_SUPPORT_FORMAT_AAC     (1 << 1)
#define  MS12_SUPPORT_FORMAT_AC4     (1 << 2)
#define  MS12_SUPPORT_FORMAT_MP3     (1 << 3)

#define  HA_CODEC_MS12_DECODE_FRAME_CMD               ((((HI_U32)HA_MS12_ID) << 16) | 0x2000)
#define  HA_CODEC_MS12_ENABLE_DECODE_CMD              ((((HI_U32)HA_MS12_ID) << 16) | 0x2001)
#define  HA_CODEC_MS12_ENABLE_MIX_CMD                 ((((HI_U32)HA_MS12_ID) << 16) | 0x2002)
#define  HA_CODEC_MS12_DROP_FRAME_CMD                 ((((HI_U32)HA_MS12_ID) << 16) | 0x2003)
#define  HA_CODEC_MS12_SET_STREAM_INDEX_CMD           ((((HI_U32)HA_MS12_ID) << 16) | 0x2004)
#define  HA_CODEC_MS12_ADJUST_STRATEGY_CMD            ((((HI_U32)HA_MS12_ID) << 16) | 0x2005)
#define  HA_CODEC_MS12_RESET_CMD                      ((((HI_U32)HA_MS12_ID) << 16) | 0x2006)
#define  HA_CODEC_MS12_SET_EOSFLAG_CMD                ((((HI_U32)HA_MS12_ID) << 16) | 0x2007)
#define  HA_CODEC_MS12_SET_MEDIAVOLATTENUATE_CMD      ((((HI_U32)HA_MS12_ID) << 16) | 0x2008)
#define  HA_CODEC_MS12_SET_PROCINFO_CMD               ((((HI_U32)HA_MS12_ID) << 16) | 0x2009)
#define  HA_CODEC_MS12_SET_MIXER1_VOLUME_CMD          ((((HI_U32)HA_MS12_ID) << 16) | 0x200A)
#define  HA_CODEC_MS12_GET_CAPABILITY_CMD             ((((HI_U32)HA_MS12_ID) << 16) | 0x200B)
#define  HA_CODEC_MS12_SET_DEC_POLICY_CMD             ((((HI_U32)HA_MS12_ID) << 16) | 0x200C)
#define  HA_CODEC_MS12_SOFTRESET_CMD                  ((((HI_U32)HA_MS12_ID) << 16) | 0x200D)
#define  HA_CODEC_MS12_SET_PES_DATA_CMD               ((((HI_U32)HA_MS12_ID) << 16) | 0x200E)
#define  HA_CODEC_MS12_SET_INPUTTYPE_CMD              ((((HI_U32)HA_MS12_ID) << 16) | 0x200F)
#define  HA_CODEC_MS12_SET_ATMOSLOCK_CMD              ((((HI_U32)HA_MS12_ID) << 16) | 0x2010)
#define  HA_CODEC_MS12_SET_SOURCEMUTE_CMD             ((((HI_U32)HA_MS12_ID) << 16) | 0x2011)
#define  HA_CODEC_MS12_SET_SOURCEPRESCALE_CMD         ((((HI_U32)HA_MS12_ID) << 16) | 0x2012)

typedef enum
{
    MS11_CONFIG,
    MS12_CONFIG_B,
    MS12_CONFIG_D,
} MS12_CONFIG_E;

typedef enum
{
    MS12_STREAM_IDLE = 0,
    MS12_STREAM_RUNNING,
    MS12_STREAM_PAUSE,
    MS12_STREAM_STOP,
    MS12_STREAM_ACTIVATE,
} MS12_STREAM_STATE_E;

/** Define Dec Policy mode
    - 0: Only dec main
    - 1: Only dec assoc
    - 2: dec dual */
typedef enum
{
    MS12_DEC_MAIN = 0,
    MS12_DEC_ASSOC,
    MS12_DEC_DUAL,
} MS12_DEC_POLICY_E;

typedef struct
{
    HI_U32 u32TryCnt;
    HI_U32 u32OkCnt;
    HI_U32 u32PriUnderRunCnt;
    HI_U32 u32SecUnderRunCnt;
    HI_U32 u32ThirdUnderRunCnt;
    HI_U32 u32InBufBytes[MS12_MIXER_MAX_SOURCE_NUM];
} MS12_MIXER_PROC_S;

/** Define proc info of stream */
typedef struct
{
    MS12_STREAM_TYPE_E enStreamType;
    HI_BOOL            bDecodeEnable;
    HI_BOOL            bMixEnable;
    HI_BOOL            bLfeExist;
    HI_U32             u32StreamLeftBytes;
    HI_U32             u32SampleRate;
    HI_U32             u32BitRate;
    HI_U32             u32Acmod;
    HI_U32             u32LeftDropMs;
    HI_S32             s32Volume;
    HI_U32             u32CurOutFrameMs;
    HI_U32             u32NotEnoughCnt;
    HI_U32             u32DecodeTryCnt;
    HI_U32             u32DecodeOkCnt;
    HI_U32             u32DecodeErrCnt;
    HI_U32             u32DecodeInBufBytes;
    HI_BOOL            bMute;
    HI_U32             u32IntPrescale;
    HI_S32             s32DecPrescale;
} MS12_STREAM_PROC_S;

typedef struct
{
    MS12_CONFIG_E      enConfig;
    HI_BOOL            bSupportHeaac;
    HI_U32             u32OutChannels;
    HI_U32             u32OutSampleRate;
    HI_U32             u32DebugLevel;
    HI_BOOL            bDumpFile;
    HI_BOOL            bDumpSectionFile;
    HI_U32             u32FlushCnt;
    HI_U32             u32SoftResetCnt;
    HI_BOOL            bExtMain;
    MS12_MIXER_PROC_S  stMixerProc[MS12_MIXER_NUM];
    MS12_STREAM_PROC_S stStreamProc[MS12_MAX_STREAM_NUM];
    DOLBYMS12_CODEC_OPENCONFIG_S stCodecConfig;
    HI_BOOL            bAtmosOutput;
} HA_MS12_PROC_S;

typedef struct
{
    MS12_STREAM_STATE_E     enStreamState[MS12_MAX_STREAM_NUM];
    HI_HADECODE_INPACKET_S* pstInPack[MS12_MAX_STREAM_NUM];

    HI_BOOL  bPassthruBypass;
    HI_U32   u32TrackDelayMs;
    HI_CHAR* acUnifyWorkBuf[2];
    HI_U32   u32UseCase;
} MS12_INPUT_S;

typedef struct
{
    HI_U32  u32OutFrameMs[MS12_MAX_STREAM_NUM];
    HI_U32  u32DecodeLeftBytes[MS12_MAX_STREAM_NUM];
    HI_U32  u32PcmDelayMs[MS12_MAX_STREAM_NUM];
    HI_U32  u32DecoderStaticDelay[MS12_MAX_STREAM_NUM];
    HI_S32  s32ErrState[MS12_MAX_STREAM_NUM];
    HI_BOOL bStreamEnough[MS12_MAX_STREAM_NUM];
    HI_HADECODE_OUTPUT_S* pstOutput;
    HI_BOOL bAtmosOutActive;
    HI_U32  u32AddMediaPauseMuteMs;
    HI_U32  u32AddMediaMixerMuteMs;
} MS12_OUTPUT_S;

typedef struct
{
    MS12_INPUT_S  stInput;
    MS12_OUTPUT_S stOutput;
} HA_MS12_STREAM_S;

/** Define decoding parameter
    - enCmd: HA_CODEC_MS12_DECODE_FRAME_CMD */
typedef struct
{
    HI_U32 enCmd;
    HA_MS12_STREAM_S stStream;
} HA_MS12_DECODE_STREAM_S;

/** Define Setting proc info parameter
    - enCmd: HA_CODEC_MS12_SET_PROCINFO_CMD */
typedef struct
{
    HI_U32 enCmd;
    HA_MS12_PROC_S stProc;
} HA_MS12_SET_PROCINFO_S;

/** Define Setting stream index parameter
    - enCmd: HA_CODEC_MS12_SET_STREAM_INDEX_CMD
    - u32Index: Indicates the stream index, support 0 ~ 3 */
typedef struct
{
    HI_U32 enCmd;
    HI_U32 u32Index;
} HA_MS12_SET_STREAM_INDEX_S;

/** Define adjusting strategy parameter
    - enCmd: HA_CODEC_MS12_ADJUST_STRATEGY_CMD
    - s32AdjustTime: The time to adjust (ms) */
typedef struct
{
    HI_U32  enCmd;
    HI_S32  s32AdjustTime;
} HA_MS12_ADJUST_STRATEGY_S;

/** Define enable decode parameter
    -enCmd: HA_CODEC_ENABLE_DECODE_CMD
    -bEnable: Indicates whether to decode */
typedef struct
{
    HI_U32  enCmd;
    HI_BOOL bEnable;
} HA_MS12_DECODE_ENABLE_S;

/** Define parameter of enable mix
    -enCmd: HA_CODEC_ENABLE_MIX_CMD
    -bEnable: Indicates whether to mix to the output */
typedef struct
{
    HI_U32  enCmd;
    HI_BOOL bEnable;
} HA_MS12_MIX_ENABLE_S;

/** Define dropping frame parameter
    -enCmd: HA_CODEC_DROP_FRAME_CMD
    -u32FrameCnt: frame count to drop for one stream */
typedef struct
{
    HI_U32  enCmd;
    HI_U32  u32FrameCnt;
} HA_MS12_DROP_FRAME_S;

/** Define Setting parameter of eos flag
    -enCmd: HA_CODEC_SET_EOSFLAG_CMD
    -bEosFlag: Is the stream reach the end */
typedef struct
{
    HI_U32  enCmd;
    HI_BOOL bEosFlag;
} HA_MS12_SET_EOSFLAG_S;

/** Define Setting parameter of media volume attenuation
    -enCmd: HA_CODEC_SET_MEDIAVOLATTENUATE_CMD
    -bEnable: Indicates whether to attenuate media volume */
typedef struct
{
    HI_U32  enCmd;
    HI_BOOL bEnable;
} HA_MS12_SET_MEDIAVOLATTENUATE_S;

/** Define Getting MS12 Capability
    -enCmd: HA_CODEC_MS12_GET_CAPABILITY_CMD
    -u32Capability: Indicates MS12 support all format */
typedef struct
{
    HI_U32  enCmd;
    HI_U32  u32Capability;
} HA_MS12_GET_CAPABILITY_S;

/** Define Setting parameter of dec policy mode
    - enCmd: HA_CODEC_MS12_SET_DEC_POLICY_CMD */
typedef struct
{
    HI_U32 enCmd;
    MS12_DEC_POLICY_E enPolicy;
} HA_MS12_DEC_POLICY_S;

/** Define Setting parameter of Audio Description
    -enCmd:          HA_CODEC_MS12_SET_PES_DATA_CMD
    -au8Data[0]:  fade_byte
    -au8Data[1]:  gain_byte_center
    -au8Data[2]:  gain_byte_front
    -au8Data[3]:  gain_byte_surround
    -au8Data[4]:  pan_byte */
typedef struct
{
    HI_U32 enCmd;
    HI_U8  au8Data[5];
} HA_MS12_SET_PES_DATA_S;

/** Define Setting parameter of main input type
    -enCmd: HA_CODEC_MS12_SET_INPUTTYPE_CMD
    -enInputType: Indicates main input type */
typedef struct
{
    HI_U32  enCmd;
    MS12_INPUT_TYPE_E enInputType;
} HA_MS12_SET_INPUTTYPE_S;

/** Define Setting parameter of atmos lock
    -enCmd: HA_CODEC_MS12_SET_ATMOSLOCK_CMD
    -bEnable: Indicates atmos lock */
typedef struct
{
    HI_U32  enCmd;
    HI_BOOL bEnable;
} HA_MS12_SET_ATMOSLOCK_S;

/** Define Setting parameter of source mute
    -enCmd: HA_CODEC_MS12_SET_SOURCEMUTE_CMD
    -bEnable: Indicates mute status */
typedef struct
{
    HI_U32  enCmd;
    HI_BOOL bEnable;
} HA_MS12_SET_SOURCEMUTE_S;

/** Define Setting parameter of source prescale
    -enCmd: HA_CODEC_MS12_SET_SOURCEPRESCALE_CMD
    -s32IntegerGain: Interger part of high preicision gain
    -s32DecimalGain: decimal part of high preicision gain, if -0.125dB, value is -125 */
typedef struct
{
    HI_U32  enCmd;
    HI_S32  s32IntegerGain;
    HI_S32  s32DecimalGain;
} HA_MS12_SET_SOURCEPRESCALE_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HA_AUDIO_DOLBYMS12EXT_DECODE_H__ */
