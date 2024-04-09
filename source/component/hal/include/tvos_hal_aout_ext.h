/**
 * \file
 * \brief the extention information about the audio output module.
 */

#ifndef __TVOS_HAL_AOUT_EXT_H__
#define __TVOS_HAL_AOUT_EXT_H__

#include "tvos_hal_type.h"
#include "tvos_hal_aout.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/**Audio data format.*/
/**CNcomment:��Ƶ��չ���ݸ�ʽ*/
typedef enum _AOUT_DATA_FORMAT_EXT_E
{
    AOUT_DATA_FORMAT_UNUSED = AOUT_DATA_FORMAT_EXTENSIONS + 0x00100000,
    AOUT_DATA_FORMAT_MASTER,             /**<master format type, for passthrough*/ /**<CNcomment:Master����format*/
    AOUT_DATA_FORMAT_SYSTEM,             /**<System format type, for UI audio*/ /**<CNcomment:System����, ���UI audio*/
    AOUT_DATA_FORMAT_TTS,                /**<TTS format type, for tts*/ /**<CNcomment:TTS����, ���tts*/
} AOUT_DATA_FORMAT_EXT_E;

typedef struct _AOUT_ARC_AUDIO_CAP_S
{
    BOOL bSupportDDP;                    /**<Support digital dolby plus*/ /**<CNcomment:�Ƿ�֧�ֶű�������Ƶ*/
} AOUT_ARC_AUDIO_CAP_S;

typedef enum _AOUT_CONFIG_TYPE_E
{
    AOUT_CONFIG_ENABLE_DEVICE = 0x1,             /**<enable device*/ /**<CNcomment:�豸ʹ������*/
    AOUT_CONFIG_DEVICE_CAPABILITY = 0x1 << 1,    /**<device capability*/ /**<CNcomment:�豸������*/
    AOUT_CONFIG_BUTT
} AOUT_CONFIG_TYPE_E;

typedef enum _TRACK_VOLUME_CURVE_E
{
    TRACK_VOLUME_CURVE_LINEAR,           /**<Linear curve, up:g(x)=x, down:f(x) = 1-x*/ /**<CNcomment:������������*/
    TRACK_VOLUME_CURVE_INCUBE,           /**<In cube,up:g(x) = x^3, down:f(x)=1-x^3 */ /**<CNcomment:Cubic-in��������*/
    TRACK_VOLUME_CURVE_OUTCUBE,          /**<Out cube,up:g(x) = 1-(1-x)^3, down:f(x)=(1-x)^3 */ /**<CNcomment:Cubic-out��������*/
    TRACK_VOLUME_CURVE_BUTT,
} TRACK_VOLUME_CURVE_E;

typedef struct _TRACK_VOLUME_CONFIG_S
{
    TRACK_VOLUME_CURVE_E enVolumeCurve;  /**<Volume curve*/ /**<CNcomment:������������*/
    U32 u32IntVolume;                    /**<Target Int attenuation(range:0 - 100)*/ /**<CNcomment:����ֵ,�������֣���0��100*/
    U32 u32DecVolume;                    /**<Target Dec attenuation(range:0 - 100)*/ /**<CNcomment:����ֵ,С�����֣���0��100*/
    U32 u32FadeTime;                     /**<Duration of ramp in milliseconds(range:0-60000)*/ /**<CNcomment:����������Чʱ��0-60000����*/
} TRACK_VOLUME_CONFIG_S;

typedef struct _TRACK_SETEOSFLAG_CONFIG_S
{
    U32 u32EosFlag;                      /**<Set track stream eos flag (0:not eos, 1:eos) */ /**<CNcomment:����track stream eos��־ (0:����, 1:��)*/
} TRACK_SETEOSFLAG_CONFIG_S;

typedef struct _TRACK_GETSYSTRACKALONEFLAG_CONFIG_S
{
    U32 u32Alone;                        /**<Is system track alone (0:not alone, 1:alone) */ /**<CNcomment:��ȡ�Ƿ�ֻ����system track (0:����, 1:��)*/
} TRACK_GETSYSTRACKALONE_CONFIG_S;

typedef struct _TRACK_SETMEDIAVOLUMEATTENUATION_CONFIG_S
{
    U32 u32Attenuate;                    /**<Is media need attenuate (0:not attenuate, 1:attenuate) */ /**<CNcomment:����Media�����Ƿ���Ҫ˥��(0:���ǣ�1:��)*/
} TRACK_SETMEDIAVOLUMEATTENUATION_CONFIG_S;

typedef enum _TRACK_CONFIG_TYPE_E
{
    TRACK_CONFIG_VOLUME     = 0x00001000,    /**< track volume*/ /**<CNcomment:������������*/
    TRACK_CONFIG_SETEOSFLAG = 0x00001001,    /**< set end of track stream*/ /**<CNcomment:���������Ľ�����ʶ��*/
    TRACK_CONFIG_GETSYSTEMTRACKALONEFLAG = 0x00001002,
    TRACK_CONFIG_SETMEDIAVOLUMEATTENUATION = 0x00001003,    /**<set media track attenuation*/ /**<CNcomment:ʹ��ý������˥��*/
    TRACK_CONFIG_BUTT,
} TRACK_CONFIG_TYPE_E;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

