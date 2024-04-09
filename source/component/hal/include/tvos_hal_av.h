/**
* \file
* \brief Describes the information about the audio/video play control module.
*/

#ifndef __TVOS_HAL_AV_H__
#define __TVOS_HAL_AV_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "tvos_hal_type.h"
#include "tvos_hal_dmx.h"
#include "tvos_hal_aout.h"
#include "tvos_hal_vout.h"

#ifdef ANDROID_HAL_MODULE_USED
#include <hardware/hardware.h>
#else
#include "tvos_hal_linux_adapter.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************** Macro Definition ****************************/
/** \addtogroup      HAL_AV */
/** @{ */  /** <!-- [HAL_AV] */

/*****************************************************************************/

/*****************************************************************************/

/**Defines the av module name*/
/**CNcomment:����AV ģ������ */
#define AV_HARDWARE_MODULE_ID "audio_video"

/**Defines the av module name*/
/**CNcomment:����AV �豸���� */
#define AV_HARDWARE_AV0       "av0"

/**Invalid av handle*/
#define AV_INVALID_HANDLE     (0)

/**Defines the dts drc mode min and max*/
#define DTS_DRCMODE_MIN      (0)
#define DTS_DRCMODE_MAX      (100)

/* Compare up to three letters + one char for null termination */
#define AC4_PREF_LANG_MAX_LEN  (4)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HAL_AV */
/** @{ */  /** <!-- [HAL_AV] */

/**Defines the state of AV decode
1.Dafault is AV_DECODER_STATE_STOPPED after init;
2.Stop/start/pause/freeze can be useful in AV_DECODER_STATE_RUNNING;
3.PAUSE/FREEZE can be useful only in AV_DECODER_STATE_RUNNING;
4.Stop/resume/startcan be useful in AV_DECODER_STATE_FREEZING/AV_DECODER_STATE_PAUSING
5.Only start can be useful in AV_DECODER_STATE_STOPPED
*/
/**CNcomment:�������״̬
1.ģ���ʼ������AV_DECODER_STATE_STOPPED ״̬.
2.AV_DECODER_STATE_RUNNING ״̬��,����stop/start/pause/freeze
    AV_DECODER_STATE_RUNNING ״̬��,���û�е���stop�ӿ�,
    ֱ�ӵ���start�ӿ�.Ҳ����stop,����settings,��start,
    ����������ΪӦ�þ���û�п��ƺ�״̬,��start�µ���start.
3.ֻ��AV_DECODER_STATE_RUNNING ״̬�²���PAUSE/FREEZE
4.AV_DECODER_STATE_FREEZING/AV_DECODER_STATE_PAUSING ״̬��
    ����stop/resume/start
5.AV_DECODER_STATE_STOPPED ״̬��ֻ��start.*/
typedef enum _AV_DECODER_STATE_E
{
    AV_DECODER_STATE_RUNNING = 0,          /**<Playing*//**<CNcomment: ���ڽ���*/
    AV_DECODER_STATE_PAUSING,              /**<Pause*//**<CNcomment: ��ͣ����, ʵʱ��������ͣ*/
    AV_DECODER_STATE_FREEZING,             /**<Freeze picture, keep decoding, it means pause for real-time stream*//**<CNcomment: ����,����ʾ,����ʵʱ������ʹ�����������ͣ*/
    AV_DECODER_STATE_STOPPED,              /**<Stop*//**<CNcomment: ֹͣ����*/
    AV_DECODER_STATE_UNKNOWN,
    AV_DECODER_STATE_BUTT
} AV_DECODER_STATE_E;

/**Defines the recovery mode of video decode error, default is AV_ERROR_RECOVERY_MODE_HIGH after system init*/
/**CNcomment:��Ƶ�������ָ�ģʽ,ϵͳ��ʼ��֮��,Ĭ��AV_ERROR_RECOVERY_MODE_HIGH.*/
typedef enum _AV_ERROR_RECOVERY_MODE_E
{
    AV_ERROR_RECOVERY_MODE_NONE = 0,       /**<No correction, for debug*//**<CNcomment: �޾���������*/
    AV_ERROR_RECOVERY_MODE_PARTIAL,        /**<Part correction*//**<CNcomment: ���־���*/
    AV_ERROR_RECOVERY_MODE_HIGH,           /**<Part correction*//**<CNcomment: ���־���*/
    AV_ERROR_RECOVERY_MODE_FULL,           /**<All correction, for debug, discard any picture if has error*//**<CNcomment: ȫ���������ã��д��󼴶���*/
    AV_ERROR_RECOVERY_MODE_BUTT
} AV_ERROR_RECOVERY_MODE_E;

/**Defines of audio stream type.*/
/**CNcomment: ��Ƶ������*/
typedef enum _AV_AUD_STREAM_TYPE_E
{
    AV_AUD_STREAM_TYPE_MP2         = 0,        /**<MPEG audio layer 1, 2.*/ /**<CNcomment:MPEG��Ƶ��һ�㡢�ڶ��� */
    AV_AUD_STREAM_TYPE_MP3,                    /**<MPEG audio layer 1, 2, 3.*/ /**<CNcomment:MPEG��Ƶ��һ�㡢�ڶ��� ��������*/
    AV_AUD_STREAM_TYPE_AAC,
    AV_AUD_STREAM_TYPE_AC3,
    AV_AUD_STREAM_TYPE_DTS,
    AV_AUD_STREAM_TYPE_DTS_EXPRESS = 5,
    AV_AUD_STREAM_TYPE_VORBIS,
    AV_AUD_STREAM_TYPE_DVAUDIO,
    AV_AUD_STREAM_TYPE_WMAV1,
    AV_AUD_STREAM_TYPE_WMAV2,
    AV_AUD_STREAM_TYPE_MACE3       = 10,
    AV_AUD_STREAM_TYPE_MACE6,
    AV_AUD_STREAM_TYPE_VMDAUDIO,
    AV_AUD_STREAM_TYPE_SONIC,
    AV_AUD_STREAM_TYPE_SONIC_LS,
    AV_AUD_STREAM_TYPE_FLAC        = 15,
    AV_AUD_STREAM_TYPE_MP3ADU,
    AV_AUD_STREAM_TYPE_MP3ON4,
    AV_AUD_STREAM_TYPE_SHORTEN,
    AV_AUD_STREAM_TYPE_ALAC,
    AV_AUD_STREAM_TYPE_WESTWOOD_SND1 = 20,
    AV_AUD_STREAM_TYPE_GSM,
    AV_AUD_STREAM_TYPE_QDM2,
    AV_AUD_STREAM_TYPE_COOK,
    AV_AUD_STREAM_TYPE_TRUESPEECH,
    AV_AUD_STREAM_TYPE_TTA         = 25,
    AV_AUD_STREAM_TYPE_SMACKAUDIO,
    AV_AUD_STREAM_TYPE_QCELP,
    AV_AUD_STREAM_TYPE_WAVPACK,
    AV_AUD_STREAM_TYPE_DSICINAUDIO,
    AV_AUD_STREAM_TYPE_IMC         = 30,
    AV_AUD_STREAM_TYPE_MUSEPACK7,
    AV_AUD_STREAM_TYPE_MLP,
    AV_AUD_STREAM_TYPE_GSM_MS,
    AV_AUD_STREAM_TYPE_ATRAC3,
    AV_AUD_STREAM_TYPE_VOXWARE     = 35,
    AV_AUD_STREAM_TYPE_APE,
    AV_AUD_STREAM_TYPE_NELLYMOSER,
    AV_AUD_STREAM_TYPE_MUSEPACK8,
    AV_AUD_STREAM_TYPE_SPEEX,
    AV_AUD_STREAM_TYPE_WMAVOICE    = 40,
    AV_AUD_STREAM_TYPE_WMAPRO,
    AV_AUD_STREAM_TYPE_WMALOSSLESS,
    AV_AUD_STREAM_TYPE_ATRAC3P,
    AV_AUD_STREAM_TYPE_EAC3,
    AV_AUD_STREAM_TYPE_SIPR        = 45,
    AV_AUD_STREAM_TYPE_MP1,
    AV_AUD_STREAM_TYPE_TWINVQ,
    AV_AUD_STREAM_TYPE_TRUEHD,
    AV_AUD_STREAM_TYPE_MP4ALS,
    AV_AUD_STREAM_TYPE_ATRAC1      = 50,
    AV_AUD_STREAM_TYPE_BINKAUDIO_RDFT,
    AV_AUD_STREAM_TYPE_BINKAUDIO_DCT,
    AV_AUD_STREAM_TYPE_DRA,
    AV_AUD_STREAM_TYPE_PCM,
    AV_AUD_STREAM_TYPE_PCM_BLURAY  = 55,
    AV_AUD_STREAM_TYPE_ADPCM ,
    AV_AUD_STREAM_TYPE_AMR_NB,
    AV_AUD_STREAM_TYPE_AMR_WB,
    AV_AUD_STREAM_TYPE_AMR_AWB,
    AV_AUD_STREAM_TYPE_RA_144      = 60,
    AV_AUD_STREAM_TYPE_RA_288,
    AV_AUD_STREAM_TYPE_DPCM,
    AV_AUD_STREAM_TYPE_G711,
    AV_AUD_STREAM_TYPE_G722,
    AV_AUD_STREAM_TYPE_G7231       = 65,
    AV_AUD_STREAM_TYPE_G726,
    AV_AUD_STREAM_TYPE_G728,
    AV_AUD_STREAM_TYPE_G729AB,
    AV_AUD_STREAM_TYPE_MULTI,
    AV_AUD_STREAM_TYPE_MS12_DDP    = 70,
    AV_AUD_STREAM_TYPE_MS12_AAC,
    AV_AUD_STREAM_TYPE_MS12_AC4,
    AV_AUD_STREAM_TYPE_BUTT
} AV_AUD_STREAM_TYPE_E;

/**Defines of video stream type.*/
/**CNcomment: ��Ƶ������*/
typedef enum _AV_VID_STREAM_TYPE_E
{
    AV_VID_STREAM_TYPE_MPEG2      = 0,        /**<MPEG2*/
    AV_VID_STREAM_TYPE_MPEG4,                 /**<MPEG4 DIVX4 DIVX5*/
    AV_VID_STREAM_TYPE_AVS,                   /**<AVS*/
    AV_VID_STREAM_TYPE_AVSPLUS,               /**<AVSPLUS*/
    AV_VID_STREAM_TYPE_H263,                  /**<H263*/
    AV_VID_STREAM_TYPE_H264       = 5,        /**<H264*/
    AV_VID_STREAM_TYPE_REAL8,                 /**<REAL*/
    AV_VID_STREAM_TYPE_REAL9,                 /**<REAL*/
    AV_VID_STREAM_TYPE_VC1,                   /**<VC-1*/
    AV_VID_STREAM_TYPE_VP6,                   /**<VP6*/
    AV_VID_STREAM_TYPE_VP6F       = 10,       /**<VP6F*/
    AV_VID_STREAM_TYPE_VP6A,                  /**<VP6A*/
    AV_VID_STREAM_TYPE_MJPEG,                 /**<MJPEG*/
    AV_VID_STREAM_TYPE_SORENSON,              /**<SORENSON SPARK*/
    AV_VID_STREAM_TYPE_DIVX3,                 /**<DIVX3*/
    AV_VID_STREAM_TYPE_RAW        = 15,       /**<RAW*/
    AV_VID_STREAM_TYPE_JPEG,                  /**<JPEG,added for VENC*/
    AV_VID_STREAM_TYPE_VP8,                   /**<VP8*/
    AV_VID_STREAM_TYPE_VP9,                   /**<VP9*/
    AV_VID_STREAM_TYPE_MSMPEG4V1,             /**<MS private MPEG4 */
    AV_VID_STREAM_TYPE_MSMPEG4V2  = 20,
    AV_VID_STREAM_TYPE_MSVIDEO1,              /**<MS video */
    AV_VID_STREAM_TYPE_WMV1,
    AV_VID_STREAM_TYPE_WMV2,
    AV_VID_STREAM_TYPE_RV10,
    AV_VID_STREAM_TYPE_RV20       = 25,
    AV_VID_STREAM_TYPE_SVQ1,                  /**<Apple video */
    AV_VID_STREAM_TYPE_SVQ3,                  /**<Apple video */
    AV_VID_STREAM_TYPE_H261,
    AV_VID_STREAM_TYPE_VP3,
    AV_VID_STREAM_TYPE_VP5        = 30,
    AV_VID_STREAM_TYPE_CINEPAK,
    AV_VID_STREAM_TYPE_INDEO2,
    AV_VID_STREAM_TYPE_INDEO3,
    AV_VID_STREAM_TYPE_INDEO4,
    AV_VID_STREAM_TYPE_INDEO5     = 35,
    AV_VID_STREAM_TYPE_MJPEGB,
    AV_VID_STREAM_TYPE_MVC,
    AV_VID_STREAM_TYPE_HEVC,
    AV_VID_STREAM_TYPE_DV,
    AV_VID_STREAM_TYPE_WMV3       = 40,
    AV_VID_STREAM_TYPE_HUFFYUV,
    AV_VID_STREAM_TYPE_REALMAGICMPEG4,
    AV_VID_STREAM_TYPE_DIVX,
    AV_VID_STREAM_TYPE_AVS2,
    AV_VID_STREAM_TYPE_BUTT
} AV_VID_STREAM_TYPE_E;

/**Defines of AV event.*/
/**CNcomment: ����AV �¼�*/
typedef enum _AV_EVT_E
{
    AV_EVT_BASE = 0,

    /*video event*/
    AV_VID_EVT_BASE         = AV_EVT_BASE,
    AV_VID_EVT_DECODE_START = AV_VID_EVT_BASE,          /**<Video decode start, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:��Ƶ���뿪ʼ��Я��������AV_VID_STATUS_S*/
    AV_VID_EVT_DECODE_STOPPED,                          /**<Video decode stopped, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:��Ƶ����ֹͣ��Я��������AV_VID_STATUS_S*/
    AV_VID_EVT_NEW_PICTURE_DECODED,                     /**<New picture decoded, this event passes a (AV_VID_FRAMEINFO_S *) as parameter *//**<CNcomment:�»��������ɣ�Я��������AV_VID_FRAMEINFO_S*/
    AV_VID_EVT_DISCARD_FRAME,                           /**<Discard a video frame *//**<CNcomment:����һ֡��Ƶ֡*/
    AV_VID_EVT_PTS_ERROR,                               /**<Error pts of video frame *//**<CNcomment:��Ƶpts����*/
    AV_VID_EVT_UNDERFLOW,                               /**<Video stream underflow *//**<CNcomment:��Ƶ��������*/

    AV_VID_EVT_ASPECT_RATIO_CHANGE,                     /**<Aspect ratio changed, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:��Ƶ��߱ȷ����˱仯�� Я��������AV_VID_STATUS_S*/

    AV_VID_EVT_STREAM_FORMAT_CHANGE,                    /**<Stream format changed, this event passes a (AV_FORMAT_CHANGE_PARAM_S *) as parameter *//**<CNcomment:��Ƶ����ʽ�����˱仯�� Я��������AV_FORMAT_CHANGE_PARAM_S*/

    AV_VID_EVT_OUT_OF_SYNC,                             /**<Synchronization lost, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:ͬ����ʧ��Я��������AV_VID_STATUS_S*/
    AV_VID_EVT_BACK_TO_SYNC,                            /**<Synchronization resume, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:ͬ���ָ���Я��������AV_VID_STATUS_S*/

    AV_VID_EVT_DATA_OVERFLOW,                           /**<Video data overflow, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:��Ƶ��������� Я��������AV_VID_STATUS_S*/
    AV_VID_EVT_DATA_UNDERFLOW,                          /**<Video data underflow, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:��Ƶ����Ƿ�أ� Я��������AV_VID_STATUS_S*/

    AV_VID_EVT_PICTURE_DECODING_ERROR,                  /**<Pictrue decode error, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:ͼ�����ʧ�ܣ� Я��������AV_VID_STATUS_S*/
    AV_VID_EVT_CODEC_UNSUPPORT,
    AV_VID_EVT_FRAME_INFO,                              /**<Video frame infos, each decoded frame will be generated *//**<CNcomment:��Ƶ֡��Ϣ��Я��֡��Ϣ��ÿ������֡���ᷢ��*/
    AV_VID_EVT_PEEK_FIRST_PTS,                          /**<Video first peek frame pts, this event passes a HI_U32 PTS as parameter *//**<CNcomment:��Ƶ��ʾ��һ֡peekframe������¼���Я��������HI_U32 PTS*/
    AV_VID_EVT_FIRST_FRAME_DISPLAYED,                   /**<Video play first frame display event, no param *//**<CNcomment:��Ƶִ�в���������һ֡��ʾ�˵��¼����޸��Ӳ���*/
    AV_VID_EVT_LASTFRMFLAG,                             /**<Report vdec last frame flag event *//**<CNcomment: �ϱ�vdec���һ֡�¼�*/
    AV_VID_EVT_BUTT,

    /*audio event*/
    AV_AUD_EVT_BASE         = AV_VID_EVT_BUTT,
    AV_AUD_EVT_DECODE_START = AV_AUD_EVT_BASE,          /**<Audio decode start, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:��Ƶ���뿪ʼ Я��������AV_AUD_STATUS_S*/
    AV_AUD_EVT_DECODE_STOPPED,                          /**<Audio decode stopped, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:��Ƶ����ֹͣ Я��������AV_AUD_STATUS_S*/
    AV_AUD_EVT_NEW_FRAME,                               /**<New audio frame decoded, this event passes a ( AV_AUD_FRAMEINFO_S*) as parameter *//**<CNcomment:����Ƶ֡������ɣ� Я��������AV_AUD_FRAMEINFO_S*/
    AV_AUD_EVT_DISCARD_FRAME,                           /**<Discard an audio frame *//**<CNcomment:����һ֡��Ƶ֡*/
    AV_AUD_EVT_PTS_ERROR,                               /**<Error pts of audio frame *//**<CNcomment:��Ƶpts����*/
    AV_AUD_EVT_UNDERFLOW,                               /**<Audio stream underflow *//**<CNcomment:��Ƶ��������*/
    AV_AUD_EVT_DECODING_ERROR,                          /**<Audio decode error *//**<CNcomment:��Ƶ����ʧ��*/

    AV_AUD_EVT_PCM_UNDERFLOW,                           /**<PCM data undeflow, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:PCM����Ƿ�� Я��������AV_AUD_STATUS_S*/
    AV_AUD_EVT_FIFO_OVERFLOW,                           /**<Audio data overflow, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:��Ƶ������� Я��������AV_AUD_STATUS_S*/
    AV_AUD_EVT_LOW_DATA_LEVEL,                          /**<This event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment: Я��������AV_AUD_STATUS_S*/
    AV_AUD_EVT_OUT_OF_SYNC,                             /**<Synchronization lost,  this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:ͬ����ʧ�� Я��������AV_AUD_STATUS_S*/
    AV_AUD_EVT_BACK_TO_SYNC,                            /**<Synchronization resume, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:ͬ���ָ��� Я��������AV_AUD_STATUS_S*/
    AV_AUD_EVT_CODEC_UNSUPPORT,                         /**<Not support this Codec *//**<CNcomment:�����ʽ��֧��*/
    AV_AUD_EVT_BUTT,

    /*inject event*/
    AV_INJECT_EVT_BASE           = AV_AUD_EVT_BUTT,
    AV_INJECT_EVT_DATA_UNDERFLOW = AV_INJECT_EVT_BASE,  /**<Inject data underflow, this event passes a ( AV_INJECT_STATUS_S*) as parameter *//**<CNcomment:ע������Ƿ�أ� Я��������AV_INJECT_STATUS_S*/
    AV_INJECT_EVT_DATA_OVERFLOW,                        /**<Inject data overflow, this event passes a ( AV_INJECT_STATUS_S*) as parameter *//**<CNcomment:ע����������� Я��������AV_INJECT_STATUS_S*/
    AV_INJECT_EVT_IMPOSSIBLE_WITH_MEM_PROFILE,          /**<Impossible with memery profile, this event passes a ( AV_INJECT_STATUS_S*) as parameter *//**<CNcomment:��ǰ�ڴ����ò�֧�֣� Я��������AV_INJECT_STATUS_S*/
    AV_INJECT_EVT_BUTT,

    AV_STREAM_EVT_PLAY_EOS,

    AV_EVT_BUTT
} AV_EVT_E;

/**Defines of stop mode when stop video, default is AV_VID_STOP_MODE_BLACK.*/
/**CNcomment: ������Ƶֹͣģʽ��Ĭ��Ϊ����*/
typedef enum _AV_VID_STOP_MODE_E
{
    AV_VID_STOP_MODE_FREEZE = 0,        /**<Freeze the last frame *//**<CNcomment: ��֡*/
    AV_VID_STOP_MODE_BLACK,             /**<Show black screen *//**<CNcomment: ����*/
    AV_VID_STOP_MODE_BUTT
} AV_VID_STOP_MODE_E;

/**Defines of source type of AV data
The source of audio and video are different sometimes.
Because iframe or pcm data can be injected into decoder directly, such as:
Inject iframe data while playing audio data from tuner, or inject pcm data as audio while playing video from tuner or file.
*/
/**CNcomment: ��Ŀ������Դ����
��ʱ��audio & video�� �����ǲ�ͬ��.
ԭ����:iframe, pcm �Ȳ��þ���dmxֱ�ӽ���decoder.
��:����ע��iframe��ͬʱ��������tuner��audio.
���߲���ĳ��tuner����file��Դ��video��ͬʱע��pcm����.*/
typedef enum _AV_SOURCE_TYPE_E
{
    AV_SOURCE_TUNER = 1,               /**<Data comes from tuner *//**<CNcomment: ��������tuner*/
    AV_SOURCE_MEM   = 1 << 1           /**<Data comes from memery */ /**<CNcomment: ���������ڴ�*/
} AV_SOURCE_TYPE_E;

// TODO: ΪʲôҪIFRAME���ͣ�IFRAME��Ҳ��ES��?
/**Defines of the type of inject data.*/
/**CNcomment: �ڴ�ע����������*/
typedef enum _AV_DATA_TYPE_E
{
    AV_DATA_TYPE_NONE   = 0,
    AV_DATA_TYPE_TS     = 1,          /**< mem ts, through demux*//**<CNcomment:TS��ʽ����, ���뾭��dmx*/
    AV_DATA_TYPE_PES    = 1 << 1,     /**< mem PES */ /**<CNcomment:PES ��ʽ����*/
    AV_DATA_TYPE_ES     = 1 << 2,     /**< mem ES*/ /**<CNcomment:ES ��ʽ����*/
    AV_DATA_TYPE_PCM    = 1 << 3,     /**< mem PCM */ /**<CNcomment:PCM ��ʽ����*/
    AV_DATA_TYPE_IFRAME = 1 << 4      /**< mem IFRAME */ /**<CNcomment:Iframe ��ʽ����*/
} AV_DATA_TYPE_E;

/**Defines of the type sync mode.
Default is AV_SYNC_MODE_PCR, sync effect of each sync mode as follows:
1.AV_SYNC_MODE_PCR:
   Must keep synchronous and smooth in synchronization region and synchronization adjuest region;
   Must keep synchronous in synchronization abnormal region, and may not be smooth;
   Must keep smooth in synchronization exception abnormal region, and may not be synchronous;
2.AV_SYNC_MODE_DISABLE:
   Must keep smooth in all synchronization regions, and may not be synchronous;
3.AV_SYNC_MODE_AUTO:
   Must keep synchronous and smooth in synchronization region and synchronization adjuest region;
   Must keep smooth in synchronization abnormal region and synchronization exception abnormal region, and may not be synchronous;
4.AV_SYNC_MODE_VID:
   Must keep effect as AV_SYNC_MODE_DISABLE if can not get video PTS;
   Must keep effect as AV_SYNC_MODE_PCR if get video PTS;
5.AV_SYNC_MODE_AUD:
   Must keep effect as AV_SYNC_MODE_DISABLE if can not get audio PTS;
   Must keep effect as AV_SYNC_MODE_PCR if get audio PTS;*/
/**CNcomment: ����Ƶͬ��ģʽ
ϵͳ��ʼ��֮��, Ĭ����AV_SYNC_MODE_PCR, ����ģʽ��ͬ��Ч������:
1. AV_SYNC_MODE_PCR:
    ��ͬ�������ͬ�������������ͬ��,�Ҳ��ܿ���.
    ���쳣����ͬ���������п���.
    �ھ��쳣���䲻ͬ��,���ǲ��ܿ���.
2. AV_SYNC_MODE_DISABLE:
    ������������Բ�ͬ��,���ǲ��ܿ���.
3. AV_SYNC_MODE_AUTO:
    ��ͬ�������ͬ�������������ͬ��,�Ҳ��ܿ���.
    ͬ���쳣�����ͬ�����쳣������Բ�ͬ��,���ǲ��ܿ���.
4. AV_SYNC_MODE_VID:
    ���û����ƵPTS,Ч����AV_SYNC_MODE_DISABLE,
    �������ƵPTS,Ч����AV_SYNC_MODE_PCR.
5. AV_SYNC_MODE_AUD:
    ���û����ƵPTS,Ч����:AV_SYNC_MODE_DISABLE.
    �������ƵPTS,Ч����AV_SYNC_MODE_PCR.*/
typedef enum _AV_SYNC_MODE_E
{
    AV_SYNC_MODE_DISABLE = 0,       /**<Free playing without synchronization*//**<CNcomment:�ر�ͬ��*/
    AV_SYNC_MODE_AUTO,              /**<Deal with synchronization mode and parameters auto*//**<CNcomment: �Լ�����ͬ��ģʽ��ͬ������*/
    AV_SYNC_MODE_PCR,               /**<Program Clock Reference (PCR)-based synchronization*//**<CNcomment:��PCRΪΪ��׼*/
    AV_SYNC_MODE_VID,               /**<Video-based synchronization*//**<CNcomment:��ƵPTSΪʱ�ӻ�׼��ͬ��ģʽ*/
    AV_SYNC_MODE_AUD,               /**<Audio-based synchronization*/ /**<CNcomment:��ƵPTSΪʱ�ӻ�׼��ͬ��ģʽ*/
    AV_SYNC_MODE_SCR,               /**<System-clock synchronization*/ /**<CNcomment:ϵͳʱ�ӻ�׼��ͬ��ģʽ*/
    AV_SYNC_MODE_BUTT
} AV_SYNC_MODE_E;

/**Defines of the content type of inject data.*/
/**CNcomment: �ڴ�ע���������ݵ�����*/
typedef enum _AV_CONTENT_TYPE_E
{
    AV_CONTENT_DEFAULT = 0,         /**<Default type, such as TS data*//**<CNcomment: ȱʡ����, ��ts���� */
    AV_CONTENT_AUDIO,               /**<Audio data*//**<CNcomment: ��Ƶ���� */
    AV_CONTENT_VIDEO,               /**<Video data*//**<CNcomment: ��Ƶ���� */
    AV_CONTENT_BUTT
} AV_CONTENT_TYPE_E;

/**Defines of 3D format, default is AV_3D_FORMAT_OFF.*/
/**CNcomment: ����3D ����Դ��ʽ, Ĭ��AV_3D_FORMAT_OFF*/
typedef enum _AV_3D_FORMAT_E
{
    AV_3D_FORMAT_OFF = 0,
    AV_3D_FORMAT_SIDE_BY_SIDE,      /**<3d type:Side by side half*//**<CNcomment:3d ģʽ:����ʽ ���Ұ��*/
    AV_3D_FORMAT_TOP_AND_BOTTOM,    /**<3d type:Top and Bottom*//**<CNcomment:3d ģʽ:����ģʽ*/
    AV_3D_FORMAT_SIDE_BY_SIDE_FULL, /**<3d type:Side by side full*//**<CNcomment:3d ģʽ:����ʽ ����ȫ��*/
    AV_3D_FORMAT_FRAME_PACKING,     /**<3d type:Frame Packing*//**<CNcomment:3d ģʽ:֡��װ*/
    AV_3D_FORMAT_FIELD_ALTERNATIVE, /**<3d type:Field alternative*//**<CNcomment:3d ģʽ:������*/
    AV_3D_FORMAT_LINE_ALTERNATIVE,  /**<3d type:Line alternative*//**<CNcomment:3d ģʽ:�н���*/
    AV_3D_FORMAT_AUTO,              /**<Depended on stream*//**<CNcomment: AUTO ��Ҫ��������ͬʱ֧�ֲ���*/
    AV_3D_FORMAT_BUTT
} AV_3D_FORMAT_E;

/**defines the ROTATION type.*/
/**CNcomment:������Ƶ��ת�Ƕ�*/
typedef enum _AV_VID_ROTATION_E
{
    AV_VID_ROTATION_0 = 0,          /**< 0 degree rotation*//**<CNcomment: 0����ת*/
    AV_VID_ROTATION_90,             /**< 90 degree rotation*//**<CNcomment: 90����ת*/
    AV_VID_ROTATION_180,            /**< 180 degree rotation*//**<CNcomment: 180����ת*/
    AV_VID_ROTATION_270,            /**< 270 degree rotation*//**<CNcomment: 270����ת*/
    AV_VID_ROTATION_BUTT
} AV_VID_ROTATION_E;

/**Defines the type of an input stream interface.*/
/**CNcomment:���������������ӿ����� */
typedef enum _AV_STREAM_TYPE_E
{
    AV_STREAM_TYPE_TS = 0,     /**<Transport stream (TS)*//**<CNcomment:TS���� */
    AV_STREAM_TYPE_ES,         /**<ES stream*//**<CNcomment:ES���� */

    AV_STREAM_TYPE_BUTT
} AV_STREAM_TYPE_E;

/**Defines of video decode capability(Resolution)*/
/**CNcomment:��������������(�ֱ���)  */
typedef enum _VDEC_RESO_LEVEL_E
{
    VDEC_RESO_LEVEL_QCIF = 0,
    VDEC_RESO_LEVEL_CIF,
    VDEC_RESO_LEVEL_D1,
    VDEC_RESO_LEVEL_720P,
    VDEC_RESO_LEVEL_FULLHD,
    VDEC_RESO_LEVEL_1280x800,
    VDEC_RESO_LEVEL_800x1280,
    VDEC_RESO_LEVEL_1488x1280,
    VDEC_RESO_LEVEL_1280x1488,
    VDEC_RESO_LEVEL_2160x1280,
    VDEC_RESO_LEVEL_1280x2160,
    VDEC_RESO_LEVEL_2160x2160,
    VDEC_RESO_LEVEL_4096x2160,
    VDEC_RESO_LEVEL_2160x4096,
    VDEC_RESO_LEVEL_4096x4096,
    VDEC_RESO_LEVEL_8192x4096,
    VDEC_RESO_LEVEL_4096x8192,
    VDEC_RESO_LEVEL_8192x8192,
    VDEC_RESO_LEVEL_BUTT
} VDEC_RESO_LEVEL_E;

/**Defines the information about video frames address*/
/**CNcomment: ������Ƶ֡��ַ*/
typedef struct _AV_VID_FRAMEADDR_S
{
    U32             u32YAddr;      /**<Address of the Y component in the current frame*/ /**<CNcomment: ��ǰ֡Y�������ݵĵ�ַ*/
    U32             u32CAddr;      /**<Address of the C component in the current frame*/ /**<CNcomment: ��ǰ֡C�������ݵĵ�ַ*/
    U32             u32CrAddr;     /**<Address of the Cr component in the current frame*/ /**<CNcomment: ��ǰ֡Cr�������ݵĵ�ַ*/

    U32             u32YStride;    /**<Stride of the Y component*/ /**<CNcomment: Y�������ݵĿ��*/
    U32             u32CStride;    /**<Stride of the C component*/ /**<CNcomment: C�������ݵĿ��*/
    U32             u32CrStride;   /**<Stride of the Cr component*/ /**<CNcomment: Cr�������ݵĿ��*/
} AV_VID_FRAMEADDR_S;

/**Defines the video format.*/
/**CNcomment: ������Ƶ��ʽö��*/
typedef enum _AV_VID_FORMAT_E
{
    AV_VID_FORMAT_YUV_SEMIPLANAR_422 = 0X10,       /**<The YUV spatial sampling format is 4:2:2.*/ /**<CNcomment: YUV�ռ������ʽΪ4:2:2*/
    AV_VID_FORMAT_YUV_SEMIPLANAR_420 = 0X11,       /**<The YUV spatial sampling format is 4:2:0.*/ /**<CNcomment: YUV�ռ������ʽΪ4:2:0*/
    AV_VID_FORMAT_YUV_PACKAGE_UYVY,                /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is UYVY.*/ /**<CNcomment: YUV�ռ������ʽΪpackage,�ڴ�����ΪUYVY*/
    AV_VID_FORMAT_YUV_PACKAGE_YUYV,                /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YUYV.*/ /**<CNcomment: YUV�ռ������ʽΪpackage,�ڴ�����ΪYUYV*/
    AV_VID_FORMAT_YUV_PACKAGE_YVYU,                /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YVYU.*/ /**<CNcomment: YUV�ռ������ʽΪpackage,�ڴ�����ΪYVYU*/
    AV_VID_FORMAT_YUV_BUTT
} AV_VID_FORMAT_E;

/**Defines the video frame/field mode.*/
/**CNcomment: ������Ƶ֡��ģʽö��*/
typedef enum _AV_VID_FIELD_MODE_E
{
    AV_VID_FIELD_ALL = 0,            /**<Frame mode*/ /**<CNcomment: ֡ģʽ*/
    AV_VID_FIELD_TOP,                /**<Top field mode*/ /**<CNcomment: ����ģʽ*/
    AV_VID_FIELD_BOTTOM,             /**<Bottom field mode*/ /**<CNcomment: �׳�ģʽ*/
    AV_VID_FIELD_BUTT
} AV_VID_FIELD_MODE_E;

/**Defines the information about video frames.*/
/**CNcomment: ������Ƶ֡��Ϣ�ṹ*/
typedef struct _AV_VID_FRAMEINFO_S
{
    U32                              u32FrameIndex;         /**<Frame index ID of a video sequence*/ /**<CNcomment: ��Ƶ�����е�֡������*/
    AV_VID_FORMAT_E                  enVideoFormat;         /**<Video YUV format*/ /**<CNcomment: ��ƵYUV��ʽ*/
    AV_VID_FRAMEADDR_S               stVideoFrameAddr[2];   /**<Fame buffer addr, parameter 0 is left picture, 1 is right picture */
    U32                              u32Width;              /**<Width of the source picture*/ /**<CNcomment: ԭʼͼ���*/
    U32                              u32Height;             /**<Height of the source picture*/ /**<CNcomment: ԭʼͼ���*/
    S64                              s64SrcPts;             /**<Original PTS of a video frame*/ /**<CNcomment: ��Ƶ֡��ԭʼʱ���*/
    S64                              s64Pts;                /**<PTS of a video frame*/ /**<CNcomment: ��Ƶ֡��ʱ���*/
    U32                              u32AspectWidth;
    U32                              u32AspectHeight;
    U32                              u32fpsInteger;         /**<Integral part of the frame rate (in frame/s)*/ /**<CNcomment: ������֡�ʵ���������, fps */
    U32                              u32fpsDecimal;         /**<Fractional part (calculated to three decimal places) of the frame rate (in frame/s)*//**<CNcomment: ������֡�ʵ�С�����֣�����3λ��, fps */

    BOOL                             bProgressive;          /**<Sampling type (progressive or interlaced)*/ /**<CNcomment: ������ʽ(����/����) */
    AV_VID_FIELD_MODE_E              enFieldMode;           /**<Frame or field encoding mode*/ /**<CNcomment: ֡�򳡱���ģʽ*/
    BOOL                             bTopFieldFirst;        /**<Top field first flag*/ /**<CNcomment: �������ȱ�־*/
    AV_3D_FORMAT_E                   enFramePackingType;    /**<3D frame packing type*/
    U32                              u32Circumrotate;       /**<Need circumrotate, 1 need */
    BOOL                             bVerticalMirror;
    BOOL                             bHorizontalMirror;
    U32                              u32DisplayWidth;       /**<Width of the displayed picture*/ /**<CNcomment: ��ʾͼ���*/
    U32                              u32DisplayHeight;      /**<Height of the displayed picture*/ /**<CNcomment: ��ʾͼ���*/
    U32                              u32DisplayCenterX;     /**<Horizontal coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: ��ʾ����x���꣬ԭʼͼ�����Ͻ�Ϊ����ԭ��*/
    U32                              u32DisplayCenterY;     /**<Vertical coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: ��ʾ����y���꣬ԭʼͼ�����Ͻ�Ϊ����ԭ��*/
    U32                              u32ErrorLevel;         /**<Error percentage of a decoded picture, ranging from 0% to 100%*/ /**<CNcomment: һ������ͼ���еĴ��������ȡֵΪ0��100*/
    U32                              u32Private[64];        /**<Save private info,indicate the frame is stored in security buffer */
} AV_VID_FRAMEINFO_S;

/**Defines the information about audio frames.*/
/**CNcomment: ������Ƶ֡��Ϣ�ṹ*/
typedef struct _AV_AUD_FRAMEINFO_S
{
    /** s32BitPerSample: (PCM) Data depth, and format of storing the output data
          If the data depth is 16 bits, 16-bit word memory is used.
          If the data depth is greater than 16 bits, 32-bit word memory is used, and data is stored as left-aligned data. That is, the valid data is at upper bits.
     */
    /**CNcomment: s32BitPerSample: (PCM) ����λ������. �����Ÿ�ʽ
          ����16bit:   ռ��16bit word�ڴ�
          ����16bit:   ռ��32bit word�ڴ�, ��������뷽ʽ���(��Ч�����ڸ�λ)
     */
    S32  s32BitPerSample;          /**<Data depth*/ /**<CNcomment: ����λ��*/
    BOOL bInterleaved;             /**<Whether the data is interleaved*/ /**<CNcomment: �����Ƿ�֯*/
    U32  u32SampleRate;            /**<Sampling rate*/ /**<CNcomment: ������*/
    U32  u32Channels;              /**<Number of channels*/ /**<CNcomment: ͨ������*/
    S64  s64PtsMs;                 /**<Presentation time stamp (PTS)*/ /**<CNcomment: ʱ���*/
    S32* ps32PcmBuffer;            /**<Pointer to the buffer for storing the pulse code modulation (PCM) data*/ /**<CNcomment: PCM���ݻ���ָ��*/
    S32* ps32BitsBuffer;           /**<Pointer to the buffer for storing the stream data*/ /**<CNcomment: �������ݻ���ָ��*/
    U32  u32PcmSamplesPerFrame;    /**<Number of sampling points of the PCM data*/ /**<CNcomment: PCM���ݲ���������*/
    U32  u32BitsBytesPerFrame;     /**<IEC61937 data size*/ /**<CNcomment: IEC61937���ݳ���*/
    U32  u32FrameIndex;            /**<Frame ID*/ /**<CNcomment: ֡��� */
    U32  u32IEC61937DataType;      /**<IEC61937 Data Type*/ /**<CNcomment: IEC61937�������ͱ�ʶ����8bitΪIEC�������� */
} AV_AUD_FRAMEINFO_S;


#ifdef HAL_HISI_EXTEND_H
/********************************* Extend Emum and Structure Definition Before ***************************/
/**Defines the type of the video frame.*/
/**CNcomment: ������Ƶ֡������ö��*/
typedef enum _AV_VID_FRAME_TYPE_E
{
    AV_VID_FRAME_TYPE_UNKNOWN,   /**<Unknown*/ /**<CNcomment: δ֪��֡����*/
    AV_VID_FRAME_TYPE_I,         /**<I frame*/ /**<CNcomment: I֡*/
    AV_VID_FRAME_TYPE_P,         /**<P frame*/ /**<CNcomment: P֡*/
    AV_VID_FRAME_TYPE_B,         /**<B frame*/ /**<CNcomment: B֡*/
    AV_VID_FRAME_TYPE_IDR,       /**<IDR frame*/ /**<CNcomment: IDR֡*/
    AV_VID_FRAME_TYPE_BUTT
} AV_VID_FRAME_TYPE_E;

/**Defines the parameters of video frame info */
/**CNcomment: ������Ƶ֡��Ϣ����ز���*/
typedef struct _AV_UVMOS_FRAMEINFO_S
{
    AV_VID_FRAME_TYPE_E enVidFrmType; /**<Type of video frame*/ /**<CNcomment: ��Ƶ֡����*/
    U32 u32VidFrmStreamSize;             /**<Size of video frame*/ /**<CNcomment: ��Ƶ֡��С*/
    U32 u32VidFrmQP;                     /**<QP of video frame*/ /**<CNcomment: ��Ƶ֡QP*/
    U32 u32VidFrmPTS;                    /**<PTS of video frame*/ /**<CNcomment: ��Ƶ֡pts*/
    U32 u32MaxMV;                        /**<MAX MV*/ /**<CNcomment: ��Ƶ֡���MV*/
    U32 u32MinMV;                        /**<MIN MV*/ /**<CNcomment: ��Ƶ֡��СMV*/
    U32 u32AvgMV;                        /**<AVG MV*/ /**<CNcomment: ��Ƶ֡MVƽ��ֵ*/
    U32 u32SkipRatio;                    /**<MB ratio */ /**<CNcomment: ��Ƶ֡MB����0~100*/
} AV_UVMOS_FRAMEINFO_S;

/**Defines the mode of the video decoder.*/
/**CNcomment: ������Ƶ������ģʽö��*/
typedef enum _AV_VDEC_MODE_E
{
    AV_VDEC_MODE_NORMAL = 0,        /**<Decode all frames.*/ /**<CNcomment: ������֡*/
    AV_VDEC_MODE_IP,                /**<Decode only I frames and P frames.*/ /**<CNcomment: ֻ��IP֡*/
    AV_VDEC_MODE_I,                 /**<Decode only I frames.*/ /**<CNcomment: ֻ��I֡*/
    AV_VDEC_MODE_DROP_INVALID_B,    /**<Decode all frames except the first B frame sequence behind I frames */ /**<CNcomment: ������֡�����˽�����I֡�����B֡*/
    AV_VDEC_MODE_BUTT
} AV_VDEC_MODE_E;

/**Defines the source of frame rate.*/
/**CNcomment: ����֡����Դ���͵�ö�� */
typedef enum hiAV_VDEC_FRMRATE_TYPE_E
{
    AV_VDEC_FRMRATE_TYPE_PTS,         /**<Use the frame rate calculates from PTS*//**<CNcomment: ����PTS����֡�� */
    AV_VDEC_FRMRATE_TYPE_STREAM,      /**<Use the frame rate comes from stream*//**<CNcomment: ����������Ϣ�е�֡�� */
    AV_VDEC_FRMRATE_TYPE_USER,        /**<Use the frame rate set by user*//**<CNcomment: �����û����õ�֡�� */
    AV_VDEC_FRMRATE_TYPE_USER_PTS,    /**<Use the frame rate set by user until the 2nd I frame comes, then use the frame rate calculates from PTS*//**<CNcomment: �ڶ���I֡��֮ǰ�����û����õ�֡�ʣ�֮�����PTS����֡�� */
    AV_VDEC_FRMRATE_TYPE_BUTT
} AV_VDEC_FRMRATE_TYPE_E;

typedef struct _AV_VDEC_FRAMERATE_PARAM_S
{
    U32                     u32Fps;          /**<Frames per second*//**<CNcomment: ֡��(x1000) ,ʵ��֡�ʳ�1000, 0��ʾ����ע*/
    AV_VDEC_FRMRATE_TYPE_E  enFrmRateType;   /**<The source of frame rate*//**<CNcomment: ֡����Դ���� */
} AV_VDEC_FRAMERATE_PARAM_S;


/**Defines the stream type of HDR.*/
/**CNcomment: ����DOLBY HDR�������� */
typedef enum _AV_HDR_STREAM_TYPE_E
{
    AV_HDR_STREAM_TYPE_NONE = 0,
    AV_HDR_STREAM_TYPE_DL_SINGLE_VES,    /**<Dolby Vision Dual layer Single VES Format *//**<CNcomment:  ����˫���ʽ.*/
    AV_HDR_STREAM_TYPE_DL_DUAL_VES,          /**<Dolby Vision Dual Layer Dual VES Format *//**<CNcomment:  ˫��˫���ʽ.*/
    AV_HDR_STREAM_TYPE_SL_VES,               /**<Dolby Vision Single Layer VES Format *//**<CNcomment:  ���������ʽ.*/
    AV_HDR_STREAM_TYPE_BUTT
} AV_HDR_STREAM_TYPE_E;
/**Defines special control operation of decoder*/
/**CNcomment: ���������������������ѡ�� */
typedef enum _AV_VDEC_CTRL_OPTION_E
{
    AV_VDEC_CTRL_OPTION_SIMPLE_DPB = 0x1,
} AV_VDEC_CTRL_OPTION_E;

/**Defines the bit width of the output*/
/**CNcomment: ���������λ��*/
typedef enum _AV_PIXEL_BITWIDTH_E
{
    AV_PIXEL_BITWIDTH_8BIT = 0,
    AV_PIXEL_BITWIDTH_10BIT,
    AV_PIXEL_BITWIDTH_12BIT,
    AV_PIXEL_BITWIDTH_AUTO,
    AV_PIXEL_BITWIDTH_BUTT,
} AV_PIXEL_BITWIDTH_E;

/**AV invoke CODEC AV_CODEC_SET_CMD_FRAMEENDFLAG param.*/
/**CNcomment: AV invoke�ӿ�AV_CODEC_SET_CMD_FRAMEENDFLAG���ĸ��Ӳ���*/
typedef struct _AV_VCODEC_FRAMEENDCMD_PARAM_S
{
    HANDLE hInjecter;             /**<AV inject handler *//**<CNcomment: AV inject��� */
    BOOL   bFrameEndFlag;   /**<frame end flag, true means end *//**<CNcomment: ֡������־, true��ʾ֡���� */
} AV_VCODEC_FRAMEENDCMD_PARAM_S;

/*Struct of set start render position.*/
/*CNcomment: ������Ⱦ��ʼλ�õĽṹ��*/
typedef struct _AV_INVOKE_SET_START_RENDER_POS_S
{
    S64     s64Pts;                 /**<the position to start rendering from*/ /**<CNcomment:��ʼ��Ⱦλ�õ�pts*/
    S64     s64IdrPts;              /**<the closest IDR at or before pts*/ /**<CNcomment:λ����ʼpts֮ǰ�������ʼpts��idr֡��pts*/
    BOOL    bPeekFrame;             /**<render the given frame in either pause state or not*/ /**<CNcomment:��ͣ״̬�Ƿ���Ⱦָ����pts֡*/
} AV_INVOKE_SET_START_RENDER_POS_S;

/*Struct of attribute for set video buffer pool.*/
/*CNcomment: ������Ƶ����ص�����*/
typedef struct _AV_INVOKE_VBPOOL_ATTR
{
    BOOL bTvp;                      /** video security flag */ /**<CNcomment: ��Ƶ��ȫ��־*/
    U32 u32FrameCount;              /** video buffer count */ /**<CNcomment: ����ظ���*/
    U32 u32FrameWidth;              /** video width */ /**<CNcomment: ��Ƶ��*/
    U32 u32FrameHeight;             /** video height */ /**<CNcomment: ��Ƶ��*/
} AV_INVOKE_VBPOOL_ATTR;

/*Struct of set video buffer pool.*/
/*CNcomment: ������Ƶ����صĽṹ��*/
typedef struct _AV_INVOKE_SET_VIDEO_BUFFER_POOL_S
{
    BOOL bEnable;                   /** video buffer pool enable flag */ /**<CNcomment: ��Ƶ�����ʹ�ܱ�־*/
    AV_INVOKE_VBPOOL_ATTR* pstAttr; /** the attribute of video buffer pool */ /**<CNcomment: ��Ƶ����ص�����*/
} AV_INVOKE_SET_VIDEO_BUFFER_POOL_S;

/**AV invoke CODEC AV_CODEC_GET_CMD_RAWCHANNEL param.*/
/**CNcomment: AV invoke�ӿ�AV_CODEC_GET_CMD_RAWCHANNEL���ĸ��Ӳ���*/
typedef enum
{
    AV_ACODEC_RAWCHANNEL_MODE10 = 0,
    AV_ACODEC_RAWCHANNEL_MODE11,
    AV_ACODEC_RAWCHANNEL_MODE20,
    AV_ACODEC_RAWCHANNEL_MODE21,
    AV_ACODEC_RAWCHANNEL_MODE30,
    AV_ACODEC_RAWCHANNEL_MODE31,
    AV_ACODEC_RAWCHANNEL_MODE40,
    AV_ACODEC_RAWCHANNEL_MODE41,
    AV_ACODEC_RAWCHANNEL_MODE50,
    AV_ACODEC_RAWCHANNEL_MODE51,
    AV_ACODEC_RAWCHANNEL_BUTT = 0x100,   /* Unsupported Channel Mode */
}AV_ACODEC_RAWCHANNEL_MODE;


/**Defines the dts decoder config.*/
/**CNcomment: ����dts��������*/
typedef struct _AV_AUD_DTSDEC_CFG_S
{
    S32  s32DtsDrcMode;
} AV_AUD_DTSDEC_CFG_S;

/**Defines the parameters of vdec configuration Attributes */
/**CNcomment: ������Ƶ��������������*/
typedef struct _AV_VDEC_CFG_S
{
    AV_VID_FORMAT_E         enOutFormat;      /**<Vdec output Video YUV format*/ /**<CNcomment: �����������ƵYUV��ʽ*/
    AV_PIXEL_BITWIDTH_E     enBitWidth;       /**<the bit width of the output*/ /**<CNcomment: �����λ��*/
} AV_VDEC_CFG_S;

/** Define Setting parameter of ad enable and ad balance
    -bEnable:    AD on/off
                 - HI_TRUE:  AD is turned on
                 - HI_FALSE: AD is turned off
    -s32Balance: User defined balance between main and associated signal
                 Value range is between -32 and +32 (in dB)
                 -32dB indicates main only (mute associated)
                 +32dB indicates associated only (mute main) */
/**CNcomment: ����AD��������*/
typedef struct _AV_AUD_AD_CFG_S
{
    BOOL  bEnable;
    S32   s32Balance;
} AV_AUD_AD_CFG_S;

/** Define MS decode mode:
    - 0: single stream, single decode
    - 1: single stream, dual decode, single instance
    - 2: single stream, dual decode, dual instance
    - 3: dual stream, dual decode */
/**CNcomment: ����MS����ģʽ*/
typedef enum
{
    AV_AUD_MS_DECODE_MODE_SS_SD    = 0, /**< single stream, single decode */
    AV_AUD_MS_DECODE_MODE_DD_SI    = 1, /**< single stream, dual decode, single instance */
    AV_AUD_MS_DECODE_MODE_SS_DD_DI = 2, /**< single stream, dual decode, dual instance */
    AV_AUD_MS_DECODE_MODE_DS_DD    = 3, /**< dual stream, dual decode */
} AV_AUD_MS_DECODE_MODE_E;

/** Preferred associated type for decoding by the user*/
/**CNcomment: ����ƫ�õĸ�·��������*/
typedef enum
{
    AV_AUD_AC4_ASSOC_TYPE_UNDEFINED         = 0,              /* Associated content type is undefined.          */
    AV_AUD_AC4_ASSOC_TYPE_VISUALLY_IMPAIRED = 1,              /* Visually impaired content type is preferred    */
    AV_AUD_AC4_ASSOC_TYPE_HEARING_IMPAIRED  = 2,              /* Hearing impaired content is preferred          */
    AV_AUD_AC4_ASSOC_TYPE_COMMENTARY        = 3,              /* Commentary content is preferred                */
} AV_AUD_AC4_ASSOC_TYPE_E;

/* Input user preferences for presentation selection.
 * Usage of FirstPrefLang and SecondPrefLang to perform a presentation selection based on user preferences
 * in the Dolby AC-4 decoder library:
 * Language tags in the bitstream must be written as defined in IETF BCP 47.
 * The library only considers the primary language tag (i.e. the first two or three characters) of the language tag transmitted in the bitstream.
 * In order to match the language code transmitted in the bitstream with the language codes specified by the user's preference, the user's preference will be
 * converted internally to comply to BCP 47. i.e. a three-letter language code is converted to a two-letter language code, if such exist.
 *
 * -bAssocMixing: Boolean indicating whether main only (false) or main + associated (true) is preferred.
 * -FirstPrefLang: Zero-terminated ISO 639-1 two-letter or zero-terminated 639-2 three-letter language code of the first preferred language.
 * -SecondPrefLang: Zero-terminated ISO 639-1 two-letter or zero-terminated 639-2 three-letter language code of the second preferred language.
 * -enPrefAssocType: Preferred associated type to be decoded.
 * -bPrefAssocTypeOverLanguage: Boolean whether associate type or language has higher priority.
 */
typedef struct
{
    BOOL                     bAssocMixing;
    CHAR                     FirstPrefLang[AC4_PREF_LANG_MAX_LEN];
    CHAR                     SecondPrefLang[AC4_PREF_LANG_MAX_LEN];
    AV_AUD_AC4_ASSOC_TYPE_E  enPrefAssocType;
    BOOL                     bPrefAssocTypeOverLanguage;
} AV_AUD_AC4_PRESENTATION_S;

/**CNcomment: ����session�Ľṹ��*/
typedef struct _AV_INVOKE_SET_SESSION_S
{
    BOOL    bSessionEnable;             /**<whether enable session or not*/ /**<CNcomment:�Ƿ�����session */
    U32     u32SessionID;               /**<session ID, available if bSessionEnable equal TRUE*/ /**<CNcomment:session ID, ��bSessionEnable==TRUEʱ��Ч */
} AV_INVOKE_SET_SESSION_S;

/**Defines the set command of codec*/
/**CNcomment:��������������������*/
typedef enum _AV_CODEC_SET_CMD_E
{
    // VCODEC Command
    AV_CODEC_SET_CMD_DPBFULL = 0,           /**VCODEC Command to set dpb full control, Additional parameters is BOOL*/
                                            /**CNcomment:VCODEC�������dpb����ʱ��Ĵ������, ������Ӧ����ΪBOOL*/
    AV_CODEC_SET_CMD_SOURCE,                /**VCODEC Command to set source type, Additional parameters is BOOL*/
                                            /**<CNcomment: VCODEC����,����Դ����,������Ӧ����ΪBOOL*/
    AV_CODEC_SET_CMD_FRAMEENDFLAG,          /**VCODEC Command to inject send data frame end flag, for first frame display instand,  Additional parameters is AV_VCODEC_FRAMEENDCMD_PARAM_S */
                                            /**<CNcomment: VCODEC����, inject������ʱ��֡������־����ʾһ֡������ʣ�����һ���������ˣ�������֡��ǰ��ʾ�ĳ��������Ӳ���ΪAV_VCODEC_FRAMEENDCMD_PARAM_S����.*/
    AV_CODEC_SET_CMD_OUTFORMAT,             /**VCODEC Command to set output format, Additional parameters is AV_VID_FORMAT_E*/
                                            /**<CNcomment: VCODEC����,������Ƶ����������ͣ���Ӧ���õĸ��Ӳ���������AV_VID_FORMAT_E */
    AV_CODEC_SET_CMD_PROGRESSIVE,           /**VCODEC Command to set prigressive,parameters is BOOL*/
                                            /**<CNcomment:VCODEC����,����ǿ�����й��ܡ�true����,false���ر� */
    AV_CODEC_SET_CMD_VDECCFG,               /**VCODEC Command to set vdec configuration, Additional parameters is AV_VDEC_CFG_S*/
                                            /**<CNcomment: VCODEC����,������Ƶ�������������ԣ���Ӧ���õĸ��Ӳ���������AV_VDEC_CFG_S */
    AV_CODEC_GET_CMD_VDECCFG,               /**VCODEC Command to get vdec configuration, Additional parameters is AV_VDEC_CFG_S*/
                                            /**<CNcomment: VCODEC����,��ȡ��Ƶ�������������ԣ���Ӧ���õĸ��Ӳ���������AV_VDEC_CFG_S */
    // ACODEC Command
    AV_CODEC_GET_CMD_RAWCHANNEL = 100,      /**ACODEC Command to get raw channel mode, parameters is AV_ACODEC_RAWCHANNEL_MODE*/
                                            /**<CNcomment: ACODEC�����ȡRAWͨ�����ͣ���Ӧ����������AV_ACODEC_RAWCHANNEL_MODE */
    AV_ACODEC_SET_DTSDRC_CMD,               /**ACODEC Command to set DTS DRC mode, Additional parameters is AV_AUD_DTSDEC_CFG_S*/
                                            /**<CNcomment: ACODEC�������DTS��Ƶ��DRCģʽ����Ӧ�ĸ��Ӳ���������AV_AUD_DTSDEC_CFG_S */
    AV_ACODEC_SET_AD_CONFIG_CMD,            /**ACODEC Command to set audio description config, parameters is AV_AUD_AD_CFG_S*/
                                            /**<CNcomment: ACODEC�������AD���ԣ���Ӧ����������AV_AUD_AD_CFG_S*/
    AV_ACODEC_SET_MS_DECODE_MODE_CMD,       /**ACODEC Command to set MS decode mode, parameters is AV_AUD_MS_DECODE_MODE_E*/
                                            /**<CNcomment: ACODEC�������MS����ģʽ����Ӧ����������AV_AUD_MS_DECODE_MODE_E*/
    AV_ACODEC_SET_AC4_PRESENTATION_CMD,     /**ACODEC Command to set ac4 presentation, parameters is AV_AUD_AC4_PRESENTATION_S*/
                                            /**<CNcomment: ACODEC����������ԣ���Ӧ����������AV_AUD_AC4_PRESENTATION_S*/

    AV_CODEC_SET_CMD_BUTT
}AV_CODEC_SET_CMD_E;

/**Struct of audio and video codec commands.*/
/**CNcomment: ����Ƶ���������������*/
typedef struct _AV_VCODEC_CMD_S
{
    U32  u32CmdIdx;                         /**<Command Index, see AV_CODEC_SET_CMD_E*//**<CNcomment: ����Index, �μ�AV_CODEC_SET_CMD_E*/
    VOID *pParam;                           /**<Control parameter, see AV_CODEC_SET_CMD_E*//**<CNcomment: ����Я������,�μ�AV_CODEC_SET_CMD_E*/
} AV_VCODEC_CMD_S;

/**Defines the type of AV invoke.*/
/**CNcomment: ����AV Invoke�������͵�ö�� */
typedef enum _AV_INVOKE_E
{
    AV_INVOKE_ACODEC = 0x0,                  /**<Invoke command to control audio codec, additional param is AV_VCODEC_CMD_S*//**<CNcomment: ������Ƶ��������Invoke����,���ӵĲ����ṹ��AV_VCODEC_CMD_S */
    AV_INVOKE_VCODEC,                        /**<Invoke command to control video codec, additional param is AV_VCODEC_CMD_S*//**<CNcomment: ������Ƶ��������Invoke����,���ӵĲ����ṹ��AV_VCODEC_CMD_S */
    AV_INVOKE_SET_START_RENDER_POS,          /**<Invoke command to set start render position, additional param structure is AV_INVOKE_SET_START_RENDER_POS_S */
                                             /**<CNcomment: ������Ƶ��Ⱦ����ʼλ��, ���ӵĲ����ṹ��AV_INVOKE_SET_START_RENDER_POS_S*/
    AV_INVOKE_SET_VID_LASTFRMFLAG,           /**<Invoke command to vdec for last frame flag*//**<CNcomment: ����VDEC���һ֡��־*/
    AV_INVOKE_SET_MULTIAUD,                  /**<Invoke command to set multi audio, additional param structure is AV_INVOKE_SET_MULTI_AUD_S */
                                             /**<CNcomment: ���ö���Ƶ, ���ӵĲ����ṹ��AV_INVOKE_SET_MULTI_AUD_S*/
    AV_INVOKE_REG_CALLBACK,                  /**<Invoke command to register av callback*//**<CNcomment: ע��av���ⲿ�����Ļص��ӿ� */
    AV_INVOKE_SET_SESSION,                   /**<Invoke command to set session, additional param structure is AV_INVOKE_SET_SESSION_S */
                                             /**<CNcomment: ����session, ���ӵĲ����ṹ��AV_INVOKE_SET_SESSION_S*/
    AV_INVOKE_SET_VIDEO_BUFFER_POOL,         /**<Invoke command to set video buffer pool, additional param structure is AV_INVOKE_SET_VIDEO_BUFFER_POOL_S*/
                                             /**<CNcomment: ������Ƶ�����, ���ӵĲ����ṹ����AV_INVOKE_SET_VIDEO_BUFFER_POOL_S*/
    AV_INVOKE_BUTT
} AV_INVOKE_E;

/**Defines the type of inject free buffer.*/
/**CNcomment: ����ע�뻺�������͵�ö�� */
typedef enum _AV_INJECT_BUF_TYPE_E
{
    AV_INJECT_BUF_TYPE_COMMON = 0x0,    /**<AV inject common buffer*//**<CNcomment: ��ͨ������ */
    AV_INJECT_BUF_TYPE_HDR_BL,          /**<AV inject HDR BL buffer*//**<CNcomment: HDR BL������ */
    AV_INJECT_BUF_TYPE_HDR_EL,          /**<AV inject HDR EL buffer*//**<CNcomment: HDR EL������ */
    AV_BUFFER_TYPE_BUTT
} AV_INJECT_BUF_TYPE_E;

/**Defines the type of audio volume curve.*/
/**CNcomment: ������Ƶ�����������͵�ö��*/
typedef enum _AV_VOLUME_CURVE_E
{
    AV_VOLUME_CURVE_LINEAR,             /**<Linear curve, up:g(x)=x, down:f(x) = 1-x*/ /**<CNcomment:������������*/
    AV_VOLUME_CURVE_INCUBE,             /**<In cube,up:g(x) = x^3, down:f(x)=1-x^3 */ /**<CNcomment:Cubic-in��������*/
    AV_VOLUME_CURVE_OUTCUBE,            /**<Out cube,up:g(x) = 1-(1-x)^3, down:f(x)=(1-x)^3 */ /**<CNcomment:Cubic-out��������*/
    AV_VOLUME_CURVE_BUTT,
} AV_VOLUME_CURVE_E;


/**Struct of audio volume command.*/
/**CNcomment: ��Ƶ������������*/
typedef struct _AV_AUDIO_VOLUME_CMD_S
{
    U32  enCmd;                         /**<set volume cmd */ /**<CNcomment:������������*/
    AV_VOLUME_CURVE_E enVolumeCurve;    /**<Volume curve*/ /**<CNcomment:������������*/
    U32  u32IntVolume;                  /**<Target Int attenuation(range:0 - 100)*/ /**<CNcomment:����ֵ,�������֣���0��100*/
    U32  u32DecVolume;                  /**<Target Dec attenuation(range:0 - 100)*/ /**<CNcomment:����ֵ,С�����֣���0��100*/
    U32  u32FadeTime;                   /**<Duration of ramp in milliseconds(range:0-60000)*/ /**<CNcomment:����������Чʱ��0-60000����*/
} AV_AUDIO_VOLUME_CMD_S;

/**Defines the dolby decoder config.*/
/**CNcomment: ����dolby��������*/
typedef struct _AV_AUD_DOLBYDEC_CFG_S
{
    S32  s32DoblyRange;
    S32  s32DolbyDrcMode;
} AV_AUD_DOLBYDEC_CFG_S;

/** Dolby format external information */
/** CNcomment:�űȸ�ʽ����ϸ��Ϣ */
typedef struct _AV_AUD_DOLBY_INFO_S
{
    U32 u32DecoderType;      /**<Audio Decoder type *//**< CNcomment:������ID */
    S32 s32StreamType;       /**<dolby type 0:dolby 1:dolby plus *//**< CNcomment:�űȸ�ʽ���Ͳμ�DOLBYPLUS_STREAM_INFO_S */
    S32 s32ACMode;           /**<dolby ac mode *//**< CNcomment:�μ�DOLBYPLUS_STREAM_INFO_S */
} AV_AUD_DOLBY_INFO_S;

/** DTS format external information */
/** CNcomment:DTS��ʽ����ϸ��Ϣ */
typedef struct _AV_AUD_DTS_INFO_S
{
    U32 u32DecoderType;      /**<Audio Decoder type *//**< CNcomment:������ID */
    U32 u32StreamType;       /**< CNcomment:DTSM6��ʽ���Ͳμ�DTSM6_STREAM_INFO_S */
    U32 u32DecInfo;          /**< CNcomment:DTSM6��ʽ���Ͳμ�DTSM6_STREAM_INFO_S */
} AV_AUD_DTS_INFO_S;

/** struct of HDR param */
/** CNcomment:HDR���� */
typedef struct _AV_HDR_PARAM_S
{
    BOOL                    bEnable;    /**<Is Dolby HDR enable or not.*//**<CNcomment: �ű� HDR�Ƿ�ʹ��.*/
    BOOL                    bCompatible;/**<Dolby frame is compatible or not.*/ /**<CNcomment: �ű�֡�Ƿ����.*/
    AV_HDR_STREAM_TYPE_E    enHdrType;  /**< Dolby Vision VES Format.*//**<CNcomment:. �ű� HDR������.*/
    AV_VID_STREAM_TYPE_E    enElType;   /**<Video encoding type*/ /**<CNcomment: EL��Ƶ��������*/
} AV_HDR_PARAM_S;

/**Defines the attribute of low delay.*/
/**CNcomment: �������ʱ���Խṹ��*/
typedef struct _AV_LOW_DELAY_S
{
    BOOL  bEnable;  /**<Is low delay enable or not*//**<CNcomment: ����ʱ�Ƿ�ʹ��*/
} AV_LOW_DELAY_S;


/**Defines the parameters of sync refence */
/**CNcomment: ����ͬ���ο���Ϣ*/
typedef struct _AV_SYNC_REF_S
{
    S64         s64SrcPts;          /**<srouce pts*/ /**<CNcomment: Դpts*/
    S64         s64Pts;             /**<current PTS of the decoder *//**<CNcomment: ��ǰ������ʹ�õ�PTS*/
    U32         u32FpsInteger;      /**<Integer part of the frame rate *//**<CNcomment: ֡�ʵ���������*/
    U32         u32FpsDecimal;      /**<Decimal part of the frame rate *//**<CNcomment: ֡�ʵ�С������*/
    U32         u32DelayTime;       /**<delay time*/ /**<CNcomment: �ӳ�ʱ��*/
    U32         u32FreshRate;       /**<refresh rate*/ /**<CNcomment: ˢ����*/
    BOOL        bFreeRun;           /**<free run flag*/ /**<CNcomment: ���ɲ��ű�ʾ*/
    BOOL        bProgressive;       /**<Sampling type (progressive or interlaced)*/ /**<CNcomment: ������ʽ(����/����) */
} AV_SYNC_REF_S;

/**Defines the parameters of sync type */
/**CNcomment: ����ͬ����������*/
typedef enum _AV_SYNC_PROC_E
{
    AV_SYNC_PROC_DISCARD = 0,   /**<discard frame*/ /**<CNcomment: ������ǰ֡*/
    AV_SYNC_PROC_REPEAT,        /**<repeat frame*/ /**<CNcomment: �ظ���ʾ֡*/
    AV_SYNC_PROC_PLAY,          /**<play frame*/ /**<CNcomment: ���ŵ�ǰ֡*/
    AV_SYNC_PROC_QUICKOUTPUT,   /**<quick output frame*/ /**<CNcomment: ���������ǰ֡*/
    AV_SYNC_PROC_TPLAY,         /**<tplay frame*/ /**<CNcomment: �������ŵ�ǰ֡*/
    AV_SYNC_PROC_CONTINUE,      /**<continue proc frame*/ /**<CNcomment: ��������ǰ֡*/
    AV_SYNC_PROC_BUTT
} AV_SYNC_PROC_E;

/**Defines the parameters of sync process */
/**CNcomment: ����ͬ��������Ϣ*/
typedef struct _AV_SYNC_INFO_S
{
    AV_SYNC_PROC_E      enSyncProc;     /**<sync process type*/ /**<CNcomment: ͬ����������*/
    U32                 u32RepeatTime;  /**<repeate time*/ /**<CNcomment: �ظ���ʾ��ʱ��*/
    U32                 u32DispCount;   /**<display counter*/ /**<CNcomment: ��ʾ����*/
} AV_SYNC_INFO_S;

/**Defines the type of buffer alloc method */
/**CNcomment: ������Ƶ���������仺��ķ�ʽ*/
typedef enum _AV_FRAME_BUFFER_MODE_E
{
    AV_VID_FRAME_BUF_ALLOC_BY_SELF = 0, /**<alloc by self*/ /**<CNcomment: ��Ƶ������������仺��*/
    AV_VID_FRAME_BUF_ALLOC_BY_USER,     /**<alloc by user*/ /**<CNcomment: �û����仺��*/
    AV_VID_FRAME_BUF_BUTT
} AV_FRAME_BUFFER_MODE_E;

/**Defines the parameters of user buffer */
/**CNcomment: �����û��������Ϣ*/
typedef struct _AV_USER_BUFFER_S
{
    U32  u32Stride;             /**<buffer stride*/ /**<CNcomment: ���沽��*/
    BOOL bVideoBypass;          /**<video bypass flag*/ /**<CNcomment: ��Ƶ�Ƿ�͸��*/
    U32  u32FrameBufSize;       /**<frame buffer size*/ /**<CNcomment: ֡�����С*/
    U32  u32FrameBuf;           /**<frame buffer*/ /**<CNcomment: ֡����*/
    S32  s32FrameBufFd;         /**<frame buffer handle*/ /**<CNcomment: ֡������*/
    U32  u32MetadataBufSize;    /**<metadata buffer size*/ /**<CNcomment: Ԫ���ݻ����С*/
    U32  u32MetadataBuf;        /**<metadata buffer*/ /**<CNcomment: Ԫ���ݻ����ַ*/
    U32  u32PrivMetadataOffset; /**<private medata offerset*/ /**<CNcomment: ˽��Ԫ����ƫ����*/
    S32  s32MetadataBufFd;      /**<metadata buffer handle*/ /**<CNcomment: Ԫ���ݻ�����*/
} AV_USER_BUFFER_S;

/**Defines HDR mastering display Info  */
/**CNcomment: ����HDR10 mastering display������Ϣ*/
typedef struct _AV_VIDEO_MASTERING_DISPLAY_COLOUR_VOLUME_S
{
    U16 u16DisplayPrimaries_x[3];           /**<[0]:Red X chromaticity coordinate; [1]:Green X chromaticity coordinate; [2]:Blue X chromaticity coordinate. Values from range [0, 50000].*/ /**<CNcomment: �����е�����Ԫ�طֱ��ʾX���귽���ϵ�R,G,Bɫ��ֵ. ȡֵ��Χ[0,50000].*/
    U16 u16DisplayPrimaries_y[3];           /**<[0]:Red Y chromaticity coordinate; [1]:Green Y chromaticity coordinate; [2]:Blue Y chromaticity coordinate. Values from range [0, 50000].*/ /**<CNcomment: �����е�����Ԫ�طֱ��ʾY���귽���ϵ�R,G,Bɫ��ֵ. ȡֵ��Χ[0,50000].*/
    U16 u16WhitePoint_x;                    /**<White point X chromaticity coordinate,  Values from range [0, 50000].*/ /**<CNcomment: X���귽���ϵ�white pointɫ��ֵ, ȡֵ��Χ[0,50000].*/
    U16 u16WhitePoint_y;                    /**<White point Y chromaticity coordinate,  Values from range [0, 50000].*/ /**<CNcomment: Y���귽���ϵ�white pointɫ��ֵ, ȡֵ��Χ[0,50000].*/
    U32 u32MaxDisplayMasteringLuminance;    /**<Maximum luminance, Represented in candelas per square meter. Values from range [0, 10000].*/ /**<CNcomment: ÿƽ�����ϵ��������ֵ(���ȵ�λ:candelas), ȡֵ��Χ[0,10000].*/
    U32 u32MinDisplayMasteringLuminance;    /**<Minimum luminance, Represented in candelas per square meter. Values from range [0, 10000].*/ /**<CNcomment: ÿƽ�����ϵ���С����ֵ(���ȵ�λ:candelas), ȡֵ��Χ[0,10000].*/
} AV_VIDEO_MASTERING_DISPLAY_COLOUR_VOLUME_S;

/**Defines HDR content light Info  */
/**CNcomment: ����HDR10 content light������Ϣ*/
typedef struct _AV_VIDEO_CONTENT_LIGHT_LEVEL_S
{
    U32 u32MaxContentLightLevel;    /**<Maximum brightness of a single pixel (Maximum Content Light Level) in candelas per square meter*/ /**<CNcomment: ÿƽ�����ϵ�һ���ص���������ֵ(���ȵ�λ:candelas)*/
    U32 u32MaxPicAverageLightLevel; /**<Maximum brightness of a single full frame (Maximum Frame-Average Light Level) in candelas per square meter*/ /**<CNcomment: ÿƽ�����ϵ�һfull frame���������ֵ(���ȵ�λ:candelas)*/
} AV_VIDEO_CONTENT_LIGHT_LEVEL_S;

/**Defines HDR10 Metadata Info  */
/**CNcomment: ����HDR10Ԫ������Ϣ*/
typedef struct _AV_VIDEO_HDR10_INFO_S
{
    U8  u8FullRangeFlag;            /**<Whether the color space in fullrange.*/ /**<CNcomment: Color space�Ƿ���fullrange��.*/
    U8  u8ColourPrimaries;          /**<The colour primaries type, BT709, BT2020.*/ /**<CNcomment: Colour primaries���ͱ�ʶ, ��BT709, BT2020.*/
    U8  u8TransferCharacteristics;  /**<The transfer characteristics type.*/ /**<CNcomment: Transfer characteristics���ͱ�ʶ.*/
    U8  u8MatrixCoeffs;             /**<The Matrix Coefficients, BT2020CL, BT2020NCL.*/ /**<CNcomment: ����ϵ��, ��BT2020CL, BT2020NCL.*/
    U8  u8MasteringAvailable;       /**<Whether the Mastering available, The value 0 indicates available, The value 1 indicates unavailable.*/
                                    /**<CNcomment: Mastering�����Ƿ����, 0:������; 1:����*/
    U8  u8ContentAvailable;         /**<Whether the Content available, The value 0 indicates available, The value 1 indicates unavailable.*/
                                    /**<CNcomment: Content�����Ƿ����, 0:������; 1:����*/
    AV_VIDEO_MASTERING_DISPLAY_COLOUR_VOLUME_S  stMasteringInfo;    /**< Matering display Info */ /**<CNcomment: Matering display���� */
    AV_VIDEO_CONTENT_LIGHT_LEVEL_S              stContentInfo;      /**< Content light Info */ /**<CNcomment: Content light���� */
} AV_VIDEO_HDR10_INFO_S;

/**Defines HLG Metadata Info  */
/**CNcomment: ����HLGԪ������Ϣ*/
typedef struct _AV_VIDEO_HLG_INFO_S
{
    U8  u8FullRangeFlag;            /**<Whether the color space in fullrange.*/ /**<CNcomment: Color space�Ƿ���fullrange��.*/
    U8  u8ColourPrimaries;          /**<The colour primaries type, BT709, BT2020.*/ /**<CNcomment: Colour primaries���ͱ�ʶ, ��BT709, BT2020.*/
    U8  u8TransferCharacteristics;  /**<The transfer characteristics type.*/ /**<CNcomment: Transfer characteristics���ͱ�ʶ.*/
    U8  u8MatrixCoeffs;             /**<The Matrix Coefficients, BT2020CL, BT2020NCL.*/ /**<CNcomment: ����ϵ��, ��BT2020CL, BT2020NCL.*/
    U8  u8MasteringAvailable;       /**<Whether the Mastering available,The value 0 indicates available, The value 1 indicates unavailable.*/
                                    /**<CNcomment: Mastering�����Ƿ����,0:�����ã�1:����*/
    U8  u8ContentAvailable;         /**<Whether the Content available,,The value 0 indicates available, The value 1 indicates unavailable.*/
                                    /**<CNcomment: Content�����Ƿ����,0:�����ã�1:����*/
    AV_VIDEO_MASTERING_DISPLAY_COLOUR_VOLUME_S  stMasteringInfo;    /**< Matering display Info */ /**<CNcomment: Matering display���� */
    AV_VIDEO_CONTENT_LIGHT_LEVEL_S              stContentInfo;      /**< Content light Info */ /**<CNcomment: Content light���� */
    U8  u8BackWardsCompatible;
} AV_VIDEO_HLG_INFO_S;

/**Defines video Metadata type  */
/**CNcomment: ������ƵԪ��������*/
typedef enum _AV_VIDEO_METADATA_TYPE_E
{
    AV_VIDEO_METADATA_TYPE_HDR10 = 0,
    AV_VIDEO_METADATA_TYPE_HLG,
    AV_VIDEO_METADATA_TYPE_BUTT
} AV_VIDEO_METADATA_TYPE_E;

/**Defines video Metadata info  */
/**CNcomment: ������ƵԪ������Ϣ�Ĺ�ͬ��*/
typedef union _AV_VIDEO_METADATA_INFO_U
{
    AV_VIDEO_HDR10_INFO_S stHdr10Info;
    AV_VIDEO_HLG_INFO_S   stHlgInfo;
} AV_VIDEO_METADATA_INFO_U;

/**Defines the struct of video Metadata info  */
/**CNcomment: ������ƵԪ������Ϣ�ṹ*/
typedef struct _AV_VIDEO_METADATA_INFO_S
{
    AV_VIDEO_METADATA_TYPE_E      enMetadataType;   /**<the type of metadata.*/ /**<CNcomment: ��ƵԪ��������.*/
    AV_VIDEO_METADATA_INFO_U      unMetadataInfo;   /**<the union of metadata information.*/ /**<CNcomment: ��ƵԪ������Ϣ�Ĺ�ͬ��.*/
    BOOL                          bPaddingInfo;     /**<if need padding metadata information to frame information.*/ /**<CNcomment: �Ƿ���Ҫ��䵽֡��Ϣ��.*/
} AV_VIDEO_METADATA_INFO_S;

/********************************* Extend Emum and Structure Definition End ***************************/
#endif//HAL_HISI_EXTEND_H

/**Defines the parameters of format changing */
/**CNcomment: ������ʽ�л�����ز���*/
typedef struct _AV_FORMAT_CHANGE_PARAM_S
{
    U32                 u32NewFormat;            /**<New format*/ /**<CNcomment: �µ���ʽ*/
    U32                 u32ImageWidth;          /**<Width of image*/ /**<CNcomment: ͼ����*/
    U32                 u32ImageHeight;         /**<Height of image*/ /**<CNcomment: ͼ��߶�*/
    BOOL                bProgressive;           /**<Sampling type (progressive or interlaced)*/ /**<CNcomment: ������ʽ(����/����) */
    U32                 u32FrameRate;           /**<Frame rate*//**<CNcomment:֡��*/
    U32                 u32ImageStride;         /**<Stride of image*/ /**<CNcomment: ͼ����*/
    U32                 u32ImageSize;           /**<Size of image*/ /**<CNcomment: ͼ���С*/
    U32                 u32ImageNum;            /**<Num of image*/ /**<CNcomment: ��Ҫ����*/
    U32                 u32ImageBitDepth;        /**<BitDepth of image*/ /**<CNcomment: ͼ��ı������*/
} AV_FORMAT_CHANGE_PARAM_S;

/**Strcut of sync region parameter.
Define several regions depend on stream information, sync operations are different in each region,
see the defines of AV_SETTINGS_S,AV_SYNC_MODE_E */
/**CNcomment: ͬ����������趨.
���Ǹ����������,��ͬ�������ֿ��ɼ�����ͬ������.
�ڲ�ͬ��������,ͬ�������ǲ�һ����.
�μ�AV_SETTINGS_S,AV_SYNC_REGION_PARAMS_S,AV_SYNC_MODE_E �Ķ���*/
typedef struct _AV_SYNC_REGION_PARAMS_S
{
    S32 s32VidPlusTime;             /**<Plus time range during video synchronization*//**<CNcomment: ��Ƶ��ǰͬ����׼��ʱ��,0:����,if(enAvSyncMode==AV_SYNC_MODE_VID) ��ֵ��Ч.*/
    S32 s32VidNegativeTime;         /**<Negative time range during video synchronization*//**<CNcomment: ��Ƶ���ͬ����׼��ʱ��,0:����,if(enAvSyncMode==AV_SYNC_MODE_VID) ��ֵ��Ч.*/
    S32 s32AudPlusTime;             /**<Plus time range during audio synchronization*//**<CNcomment: ��Ƶ��ǰͬ����׼��ʱ��,0:����,if(enAvSyncMode==AV_SYNC_MODE_AUD) ��ֵ��Ч.*/
    S32 s32AudNegativeTime;         /**<Negative time range during audio synchronization*//**<CNcomment: ��Ƶ���ͬ����׼��ʱ��,0:����,if(enAvSyncMode==AV_SYNC_MODE_AUD) ��ֵ��Ч.*/
    BOOL bSmoothPlay;               /**<Slow playing enable.TRUE:Sync slowly, repeat a iframe every several iframes or discard a iframe,  seems like slow motion; FALSE: Sync quickly, will be not smooth*//**<CNcomment: TRUE:����ͬ��,����֡�ظ����߶���һ֡,Ч���Ͽ��ܿ���������,FALSE:����ͬ��,Ч���Ͽ��ܿ�������*/
} AV_SYNC_REGION_PARAMS_S;

/**Strcut of AV play synchronization parameter
This parameter settings should be ignored when synchronization mode isAV_SYNC_MODE_DISABLE or AV_SYNC_MODE_AUTO .
Several synchronization regions depend on stream information, different treatment will be used in different regions:
If Difference range between PTS of video or audio and synchronous time reference is in [0,stSyncStartRegion], it means in sync;
If Difference range between PTS of video or audio and synchronous time reference is in [stSyncStartRegion,stSyncNovelRegion], it means in synchronous adjustment region;
If Difference range between PTS of video or audio and synchronous time reference is in [stSyncNovelRegion,10s], it means in synchronization abnormal region;
If Difference range between PTS of video or audio and synchronous time reference is more than 10s, it means in synchronization exception abnormal region, auto give up sync;
u32PreSyncTimeoutMs means the timeout of presync when start to play:
1. if u32PreSyncTimeoutMs is 0, no pre-sync processing;
2. if u32PreSyncTimeoutMs is non-0, synchronization effect depend on the value of bPreSyncSmoothPlay;
3. if bQuickOutput is FALSE, output picture after sync finish or timeout;
4.  if bQuickOutput is TRUE, output picture of the first iframe immediately, and then depend on the value of bPreSyncSmoothPlay;
see the defines of AV_SETTINGS_S,AV_SYNC_REGION_PARAMS_S,AV_SYNC_MODE_E */
/**CNcomment:  av ͬ�������趨.
��ͬ��ģʽ��:AV_SYNC_MODE_DISABLE ��AV_SYNC_MODE_AUTO ��ʱ��,AV_SYNC_PARAM_S �����ñ�����.
��������״̬,��ͬ�������ֳɼ�������,��ͬ��������ʽ��һ��:
�������Ƶ��ͬ��ʱ���׼��Χ��:[0,stSyncStartRegion),��ʾ����ͬ��״̬,
�������Ƶ��ͬ��ʱ���׼��Χ��:[stSyncStartRegion,stSyncNovelRegion),��ʾ����ͬ����������.
�������Ƶ��ͬ��ʱ���׼��Χ��:[stSyncNovelRegion,10s),��ʾ����ͬ���쳣����.
�������Ƶ��ͬ��ʱ���׼������10s, ���ڳ��쳣״̬,��������ͬ��.
Ԥͬ����ʱʱ��u32PreSyncTimeoutMs,��ʾ�������ŵ�ʱ��,����Ԥͬ���ĳ�ʱʱ��,
1.���u32PreSyncTimeoutMs==0,��ô����Ԥͬ������,
2.���u32PreSyncTimeoutMs!=0,��ô�ڳ�ʱʱ��֮��,���bPreSyncSmoothPlay==TRUE,��ô�Ǽ�֡�ظ����߶���һ֡,���ܿ���������,���bPreSyncSmoothPlay==FALS,��ô�����ͬ��,���ܿ�������.
3. ���bQuickOutput==FALSE,��ô��ͬ��֮��,����u32PreSyncTimeoutMs��ʱ֮�����ʾ���,
4. ���bQuickOutput==TRUE,��ôһ�����������,�����ʱ��û��ͬ��,��ô��u32PreSyncTimeoutMs��ʱ֮�ڻ���ͬ�����֮ǰ,
��������������ǿ���ȡ����bPreSyncSmoothPlay��u32PreSyncTimeoutMs�Ĵ�С.
�μ� AV_SETTINGS_S,AV_SYNC_REGION_PARAMS_S,AV_SYNC_MODE_E �Ķ���
Ϊ�˼����ϴ���,AV_SYNC_MODE_E ��u32AudSyncOffseMs,u32VidSyncOffseMs ������AV_SETTINGS_S ����*/
typedef struct _AV_SYNC_PARAM_S
{
    AV_SYNC_REGION_PARAMS_S stSyncStartRegion;      /**<Synchronization start region*//**<CNcomment: ��ʼͬ����������*/
    AV_SYNC_REGION_PARAMS_S stSyncNovelRegion;      /**<Synchronization exception region*//**<CNcomment: ��ʼͬ���쳣��������*/

    U32                     u32PreSyncTimeoutMs;    /**<Pre-synchronization timeout, in ms*//**<CNcomment: �������ŵ�ʱ��,Ԥͬ����ʱʱ��,���Ϊ0,��ʾ����Ԥͬ��*/
    BOOL                    bPreSyncSmoothPlay;     /**<Output mode while doing presync before synchronization finished, the output effect is same with bSmoothPlay of AV_SYNC_REGION_PARAMS_S*//**<CNcomment: �������ŵ�ʱ��,�ﵽͬ��֮ǰ����Ԥͬ����ʱʱ��֮�ڵ�ͬ����ʽ. */
    BOOL                    bQuickOutput;           /**<Fast output enable*//**<CNcomment: �������ŵ�ʱ���Ƿ���������һ֡.*/
} AV_SYNC_PARAM_S;

// TODO: u32InjectMinLen����ʲô�õ�?
/**Struct of inject setting param.*/
/**CNcomment: ����ע�����ò���*/
typedef struct _AV_INJECT_SETTINGS_S
{
    AV_DATA_TYPE_E      enDataType;         /**<Stream type*//**<CNcomment: ע�����������*/
    AV_CONTENT_TYPE_E   enInjectContent;    /**<Inject content type*//**<CNcomment:ע������ݸ�ʽ */
    U32                 u32BufSize;         /**<If 0, automatically sets the appropriate size*//**<CNcomment:  Ϊ��ʱ,�Լ�����*/
    U32                 u32InjectMinLen;    /**<If 0, automatically sets the appropriate size*//**<CNcomment:  Ϊ��ʱ,�Լ�����*/
} AV_INJECT_SETTINGS_S;

/**Struct of buffer status.*/
/**CNcomment: �ڴ�״̬��Ϣ*/
typedef struct _AV_BUF_STATUS_S
{
    AV_DATA_TYPE_E  enDataType;             /**<Data type*//**<CNcomment: ��������*/
    U32             u32Size;                   /**<Buffer size*//**<CNcomment: �����С*/
    U32             u32Free;                /**<Free buffer size*//**<CNcomment: ���л����С*/
    U32             u32Used;                /**<Used buffer size*//**<CNcomment: ��ʹ�û����С*/
    U32             u32InjectMinLen;        /**<Minimum data length of injected*//**<CNcomment: ÿ��ע�����ݵ���С����*/
} AV_BUF_STATUS_S;

/**Struct of inject status*/
/**CNcomment: ע��״̬*/
typedef struct _AV_INJECT_STATUS_S
{
    HANDLE                  hInjecter;       /**<Injecter handle*//**<CNcomment: ע�������*/
    HANDLE                  hAv;             /**<AV handle that injecter attached *//**<CNcomment: ���������*/
    AV_BUF_STATUS_S         stBufStatus;     /**<buffer status*//**<CNcomment: �ڴ�״̬*/
    // TODO: should support ts stream?
    DMX_ID_E                enSourceId;      /**<CNcomment: TSע��ʱ,��Ӧ��TS��ͨ��,
                                              * ��ͬƽ̨�����������岻һ��,
                                              * Ҫ��tvos_hal_dmx ģ��Լ����
                                              * ��Ϊdmx��Ҫ������ȡ����
                                              * dmx ģ���CIģ��ʵ�ֵ�ʱ����m_source_id ��ת���ɾ���ts��Դ���� ����.
                                              */
} AV_INJECT_STATUS_S;

/**Struct of injecter open param*/
/**CNcomment:ע�����򿪲���*/
typedef struct _AV_INJECTER_OPEN_PARAMS_S
{
    AV_INJECT_SETTINGS_S stSettings; /**<Inject setting param*//**<CNcomment: ע�������ò���*/
} AV_INJECTER_OPEN_PARAMS_S;

/**Struct of injecter close param*/
/**CNcomment:ע�����رղ���*/
typedef struct _AV_INJECTER_CLOSE_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} AV_INJECTER_CLOSE_PARAMS_S;

/**Struct of data suorce if the data from which demux*/
/**CNcomment:��Ŀ��Դ����
ֻ�����������ĸ�dmx,�����ע��,�ǲ���Ҫ����,injecter ����֮��,ע������������dxm������.
�����tsע�뵽dmx�⸴��,�ٽ���,��ôAV_SOURCE_PARAMS_S,Ҳ����,��Ϊts����ע�� ��dmx��injecter��dmx��������Դ.
dmx_source_params_t�������������Ǵ��ĸ�tuner(dmd),�����ĸ�injecter,��������.*/
typedef struct _AV_SOURCE_PARAMS_S
{
    DMX_ID_E enDemuxId; /**<demux id of data source*//**<CNcomment: ֻ�е����ݱ��뾭��dmx����Ч*/
} AV_SOURCE_PARAMS_S;

/**Struct of audio decode status: stream info, decode state, DAC status
The stream info may be not corrent when decode stopped*/
/**CNcomment:��Ƶ״̬, ��ǰ��,������,DAC��״̬
��������ֹͣʱ,��������״̬�����ǲ�׼ȷ��*/
typedef struct _AV_AUD_STATUS_S
{
    U32                     u32PacketCount;         /**<Count of audio packet*//**<CNcomment: ͨ������Ƿ�����Ƶ������ȷ����û����Ƶ*/
    U32                     u32FrameCount;          /**<Count of audio frame*//**<CNcomment: ͨ�������Ƶ֡����Ŀ��ȷ����û����Ƶ*/
    AV_DECODER_STATE_E      enDecodeState;          /**<decode state*//**<CNcomment: ��Ƶ����״̬*/
    AV_AUD_STREAM_TYPE_E    enStreamType;           /**<Stream type*//**<CNcomment: ���������ȡ����������*/
    U32                     u32SampleRate;          /**<Sample rate*/ /**< ��Ƶ������ (32000,44100,48000 )*/
    U32                     u32BitWidth;            /**<Bit width*//**< ��Ƶÿ����������ռ�ı�����, ��:8bit,16bit */
    AV_SOURCE_TYPE_E        enSourceType;           /**<Data source*/ /**< ������Դ*/
    U32                     u32PesBufferSize;       /**<Pes buffer size*//**<CNcomment: Pes �����С*/
    U32                     u32PesBufferFreeSize;   /**<Free Pes buffer size*//**<CNcomment: ����Pes �����С*/
    U32                     u32EsBufferSize;        /**<ES buffer size*//**<CNcomment: ES �����С*/
    U32                     u32EsBufferFreeSize;    /**<Free ES buffer size*//**<CNcomment: ����ES �����С*/
    S64                     s64Pts;                 /**<current PTS of the audio decoder *//**<CNcomment: ��ǰ��������ʹ�õ�PTC*/
    S64                     s64FirstPts;            /**<First pts of video decode *//**<CNcomment: �������õ��ĵ�һ��PTS*/
    U32                     u32Stc;                 /**<current STC used by the audio decoder *//**<CNcomment: ��ǰ��Ƶ������ʹ�õ�STC*/
    U16                     u16Pid;                 /**<Audio pid *//**<CNcomment: ��Ƶpid*/
    U16                     u16ADPid;               /**<Audio AD pid *//**<CNcomment: ��Ƶpid*/
    U32                     u32FrameBufTime;        /**<Frame buffer time*//**<CNcomment: ֡����ʱ�� */
#ifdef HAL_HISI_EXTEND_H
    U32                     u32Bps;                 /**<Bits per second*//**<CNcomment: ��Ƶ����,bit/s ,0��ʾ����ע*/
#endif
} AV_AUD_STATUS_S;

/**Struct of video decode status: stream info, decode state, DAC status
The stream info may be not corrent when decode stopped*/
/**CNcomment:��Ƶ״̬, ��ǰ��,������,DAC��״̬
��������ֹͣʱ,��������״̬�����ǲ�׼ȷ��*/
typedef struct _AV_VID_STATUS_S
{
    U32 u32DispPicCount;    /**< CNcomment:ͨ�������ʾ��Ƶ֡����Ŀ��ȷ����û����Ƶ
                             * ��ʱ��ҪCA����,������"��̨ʱֻʹ�ü��ŵ�ES PIDs����,
                             * ���ǲ�������PMT(CAû������)" ������������Ȼ�ܼ�⵽�Ƿ�����Ƶ
                             */
    AV_DECODER_STATE_E      enDecodeState;          /**<Video decode state*//**<CNcomment: ��Ƶ������״̬*/
    AV_VID_STREAM_TYPE_E    enStreamType;           /**<Video stream type*//**<CNcomment: ��Ƶ����*/
    U16                     u16FpsInteger;          /**<Integer part of the frame rate *//**<CNcomment: ֡�ʵ���������*/
    U16                     u16FpsDecimal;          /**<Decimal part of the frame rate *//**<CNcomment: ֡�ʵ�С������*/

    AV_SOURCE_TYPE_E        enSourceType;           /**<Data source *//**<CNcomment: ������Դ*/
    AV_3D_FORMAT_E          en3dFormat;             /**<3D format *//**< 3D TV ��ĿԴ��Ϣ*/
    U32                     u32PesBufferSize;       /**<Pes buffer size*//**<CNcomment: Pes �����С*/
    U32                     u32PesBufferFreeSize;   /**<Free Pes buffer size*//**<CNcomment: ����Pes �����С*/
    U32                     u32EsBufferSize;        /**<ES buffer size*//**<CNcomment: ES �����С*/
    U32                     u32EsBufferFreeSize;    /**<Free ES buffer size*//**<CNcomment: ����ES �����С*/
    S64                     s64Pts;                 /**<current PTS of the audio decoder *//**<CNcomment: ��ǰ��Ƶ������ʹ�õ�PTC*/
    S64                     s64FirstPts;            /**<First pts of video decode *//**<CNcomment: �������õ��ĵ�һ��PTS*/
    U32                     u32Stc;                 /**<current STC used by the audio decoder *//**<CNcomment: ��ǰ��Ƶ������ʹ�õ�STC*/
    BOOL                    bInterlaced;            /**<is interlaced*//**<CNcomment: ���л��Ǹ���*/
    U32                     u32SourceWidth;         /**<width*//**<CNcomment: ��ƵԴ���*/
    U32                     u32SouceHeight;         /**<height*//**<CNcomment: ��ƵԴ�߶�*/
    U32                     u32DisplayWidth;        /**<width*//**<CNcomment: ��Ƶ��ʾ���*/
    U32                     u32DisplayHeight;       /**<height*//**<CNcomment: ��Ƶ��ʾ�߶�*/
    BOOL                    bByPass;
    U16                     u16Pid;                 /**<video pid*//**<CNcomment: ��Ƶpid*/
    U32                     u32FrameBufTime;        /**<Frame buffer time*//**<CNcomment: ֡����ʱ�� */
#ifdef HAL_HISI_EXTEND_H
    U32                     u32PicNotDecodeCount;   /**<frame counter of not decode*//**<CNcomment: ����������δ�����֡��*/
    U32                     u32Bps;                 /**<Bits per second*//**<CNcomment: ��Ƶ����,bit/s ,0��ʾ����ע*/
#endif
} AV_VID_STATUS_S;

/**Struct of av player status:display status and decode status of audio and video decoder
TODO*/
/**CNcomment:����״̬,��ǰ����Ƶ����������ʾ��״̬
1. m_disp_fmt_arr:��ǰϵͳ��ʵ�����õ���ʽ(�ֱ���),
    m_disp_fmt_arr��stVidStatus::m_stream_format��ͬ,
    ǰ���ǵ�ǰϵͳʵ�ʵ����õ���ʽ(�ֱ���), �����ǵ�ǰ�������Ƶ����ʽ(�ֱ���)
2. m_frame_rate_arr:��ǰϵͳ��ʵ�����õ�֡��
    m_frame_rate_arr��stVidStatus::m_frame_rate��ͬ,
    ǰ���ǵ�ǰϵͳʵ�ʵ����õ�֡��, �����ǵ�ǰ�������Ƶ��֡��.
3. m_aspect_ratio_arr:��ǰϵͳ��ʵ�����õĿ�߱�.
    m_aspect_ratio_arr��stVidStatus::m_aspect_ratio��ͬ,
    ǰ���ǵ�ǰϵͳʵ�ʵ����õĿ�߱�, �����ǵ�ǰ�������Ƶ�Ŀ�߱�.*/
typedef struct _AV_STATUS_S
{
    AV_AUD_STATUS_S         stAudStatus;                           /**<Audio play status *//**<CNcomment: ��Ƶ����״̬*/
    AV_VID_STATUS_S         stVidStatus;                           /**<Video play status *//**<CNcomment: ��Ƶ����״̬*/
    U32                     u32TsBufferSize;                       /**<TS buffer size*//**<CNcomment:TS �����С*/
    U32                     u32TsBufferFreeSize;                   /**<TS buffer size not used*//**<CNcomment:����TS �����С*/
    U32                     u32TsPacketSize;                       /**<TS packet size*//**<CNcomment:TS����С*/
    HANDLE                  ahInjecter[AV_CONTENT_BUTT];           /**<Injecters attached on the av player, 0 is invalid handle*//**<�������󶨵�ע��������::AV_CONTENT_EΪ�±�����,, 0 Ϊ�Ƿ�handle*/
    S64                     s64LocalTime;                          /**<Local synchronization reference time, -1 is invalid*//**<CNcomment: ����ͬ���ο�ʱ�䣬-1Ϊ��Чֵ*/
    U16                     u16PcrPid;                             /**<PCR pid*//**<CNcomment: PCR pid*/
    S32                     s32AVDiffTime;                         /**<Diff time between audio and video in millisecond *//**<CNcomment: ����Ƶͬ��ʱ����λ����*/
} AV_STATUS_S;

/**Struct of audio decode parameter, only special audio format need to be set*/
/**CNcomment:��Ƶ����������,һ����Ƶ��ʽ����Ҫ����,ֻ���ض���ʽ��Ҫ����*/
typedef struct _AV_ADEC_PARAM_S
{
    U32 u32Version;        /**<Audio encoding version, such as 0x160(WMAV1) and 0x161 (WMAV2). It is valid only for WMA encoding. *//**< CNcomment:��Ƶ����汾������wma���룬0x160(WMAV1), 0x161 (WMAV2) */
    U32 u32SampleRate;     /**<Sample rate*//**<CNcomment: ��Ƶ������ (32000,44100,48000 ),0��ʾ����ע*/
    U32 u32BitWidth;       /**<Bit width*//**<CNcomment: ��Ƶÿ����������ռ�ı�����, ��:8bit,16bit,0��ʾ����ע */
    U32 u32Channels;       /**<Audio channels*//**<CNcomment: ������:0,1,2,4,6,8,10... ,0��ʾ����ע*/
    U32 u32BlockAlign;     /**<Number of bytes contained in a packet*//**<CNcomment: ����С ,0��ʾ����ע*/
    U32 u32Bps;            /**<Bits per second*//**<CNcomment: ��Ƶ����,bit/s ,0��ʾ����ע*/
    BOOL bBigEndian;       /**<Big endian or little endian. It is valid only for the PCM format *//**< CNcomment:��С�ˣ���pcm��ʽ��Ч */
    U32  u32ExtradataSize; /**<Length of the extended data *//**< CNcomment:��չ���ݳ��� */
    U8*  pu8Extradata;     /**<Extended data *//**<CNcomment:��չ���� */
    VOID*  pCodecContext;  /**<Audio decode context *//**<CNcomment:��Ƶ���������� */
} AV_ADEC_PARAM_S;

/*Struct of multi audio.*/
/*CNcomment: ���ö���Ƶ�Ľṹ��*/
typedef struct _AV_INVOKE_SET_MULTI_AUD_S
{
    U16                     u16PidNum;      /**<the number of Audio PID *//**< CNcomment:��ƵPID���� */
    U16                     *pu16AudPid;    /**<Pointer to the array of audio PID*//**< CNcomment:ָ��PID�����ָ�� */
    AV_AUD_STREAM_TYPE_E    *penAudType;    /**<Pointer to the array of audio type*//**< CNcomment:ָ����Ƶ���������ָ�� */
    AV_ADEC_PARAM_S         *pstAdec;       /**<Pointer to the audio decode parameters*//**< CNcomment:ָ����Ƶ������������ָ�� */
} AV_INVOKE_SET_MULTI_AUD_S;

/**Struct of video decode parameter, only special audio format need to be set*/
/**CNcomment:��Ƶ����������,һ����Ƶ��ʽ����Ҫ����,ֻ���ض���ʽ��Ҫ����*/
typedef struct _AV_VDEC_PARAM_S
{
    U32 u32Fps;            /**<Frames per second*//**<CNcomment: ֡��(x1000) ,ʵ��֡�ʳ�1000, 0��ʾ����ע*/
    U32 u32Bps;            /**<Bits per second*//**<CNcomment: ��Ƶ����,bit/s ,0��ʾ����ע*/
    U16 u16Width;          /**<Video width*//**<CNcomment: ���,��λ���� ,0��ʾ����ע*/
    U16 u16Height;         /**<Video height*//**<CNcomment: �߶�,��λ���� ,0��ʾ����ע*/
    U32 u32Profile;        /**<Profile level. *//**<CNcomment:Profile���� */
    U32 u32Version;        /**<Version of codec. *//**<CNcomment:Codec �汾 */
    BOOL bFlip;            /**<Set this parameter to 1. In this cases, set it to 0.*//**<CNcomment: ͼ����Ҫ��תʱ��1��������0*/
    VOID*  pCodecContext;  /**<Video decode context *//**<CNcomment:��Ƶ���������� */
#ifdef HAL_HISI_EXTEND_H
    AV_VDEC_FRMRATE_TYPE_E enFrmRateType;   /**<The source of frame rate*//**<CNcomment: ֡����Դ���� */
    S32 s32CtrlOptions;    /**<The value is AV_VDEC_CTRL_OPTION_E, or the 'or' value of several enum type*/
                           /**<CNcomment: ȡֵΪ::AV_VDEC_CTRL_OPTION_E�����߼���ö�ٵ�'��' */
#endif
} AV_VDEC_PARAM_S;

/**Struct of av player parameter
1.Get AV param first, and then renew the param, then set.
2.The set operation may be cover the settings set by other task.
3.If pid is bigger than INVALID_PID, should correct to INVALID_PID.
4.If the value of volume is over range, should auto set valid value.*/
/**CNcomment:av���ò���
1. ��Ҫ�޸���Щ����ʱ,����get����,�޸���Ҫ�޸ĵĳ�Ա��set��ȥ
    set�����������û�иı�ĳ�Ա�����޸�
2. ���ǵ����������,get�����Ĳ�����set��ȥ֮ǰ,�����������Ѿ���set����
    Ҳ���Ǵ�ʱ��set�п��ܻḲ����������set����������.
3. ���pid �������� INVALID_PID, ��Ҫ����ΪINVALID_PID.
4. �������(u32LeftVol,u32RightVol)����������Χ, ��Ҫ�Զ�����������Χ.*/
typedef struct _AV_SETTINGS_S
{
    AV_ADEC_PARAM_S             stAdecParams;          /**<Audio decode parameters for special audio format*//**<CNcomment: һ����Ƶ��ʽ����Ҫ����,ֻ���ض���ʽ��Ҫ����.*/
    AV_VDEC_PARAM_S             stVdecParams;          /**<Video decode parameters for special Video format*//**<CNcomment: һ����Ƶ��ʽ����Ҫ����,ֻ���ض���ʽ��Ҫ����.*/
    AV_SOURCE_PARAMS_S          stSourceParams;        /**<Data source*//**<CNcomment:������Դ*/
    AV_SYNC_MODE_E              enAvSyncMode;          /**<Sync mode*//**<CNcomment:ͬ��ģʽ*/
    AV_SYNC_PARAM_S             stSyncParams;          /**<Sync parameter*//**<CNcomment:ͬ������*/
    AV_ERROR_RECOVERY_MODE_E    enErrRecoveryMode;     /**<Recovery mode*//**<CNcomment:����ָ�ģʽ*/
    AV_VID_STOP_MODE_E          enVidStopMode;         /**<Stop mode*//**<CNcomment:��Ƶֹͣģʽ*/
    AV_VID_STREAM_TYPE_E        enVidStreamType;       /**<Video stream type*//**<CNcomment:��Ƶ������*/
    AV_AUD_STREAM_TYPE_E        enAudStreamType;       /**<Audio stream type*//**<CNcomment:��Ƶ������*/
    AV_3D_FORMAT_E              en3dFormat;            /**<3D format*/ /**<CNcomment: 3D TV ����*/
    BOOL                        bVidDecodeOnce;        /**<FALSE:decode all data; TRUE:only decode the first pictrue for preview *//**<CNcomment: FALSE : ��������,����������������; TRUE :ֻ���һ��ͼƬ,��Ҫ����Ԥ��*/
    S32                         s32Speed;              /**<The trick modes consist in rewind, forward at slow and fast speed. 100: normal play, 200:Fast forward at two times the normal speed, -200:Fast backward at two times the normal speed,  50:Slow forward at 1/2 times the normal speed, 0 is free run*//**<CNcomment:  100 :��������,200:������,-200:����2����,50:����֮һ����������0Ϊ���ɲ��ŵ�. ��Ҫ���ڱ�ʶ�������*/
    U16                         u16PcrPid;             /**<Pcr pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)���ƽ̨֧��,��clear��ͨ����pid*/
    U16                         u16AudPid;             /**<Audio pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)���ƽ̨֧��,��clear��ͨ����pid*/
    U16                         u16AudADPid;           /**<Audio AD pid, used in ms12 scene, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)���ƽ̨֧��,��clear��ͨ����pid*/
    U16                         u16VidPid;             /**<Video pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)���ƽ̨֧��,��clear��ͨ����pid*/
    S32                         s32AudSyncOffseMs;     /**<Audio offset for synchronization*//**<CNcomment: ������Ƶ�����ͬ����׼��ʱ��ƫ��,Ĭ��Ϊ0,�������޸�,if(enAvSyncMode==AV_SYNC_MODE_AUD) ��ֵ��Ч.*/
    S32                         s32VidSyncOffseMs;     /**<Video offset for synchronization*//**<CNcomment: ������Ƶ�����ͬ����׼��ʱ��ƫ��,Ĭ��Ϊ0,�������޸�,if(enAvSyncMode==AV_SYNC_MODE_VID) ��ֵ��Ч.*/
    BOOL                        bEos;
    AV_VID_ROTATION_E           enVideoRotation;       /**<Rotation of picture*//**<CNcomment: ��Ƶ��ת�Ƕ�*/
#ifdef HAL_HISI_EXTEND_H
    BOOL                        bEnableTVP;            /**<Is trusted video path enable or not*//**<CNcomment: ��ȫ��Ƶͨ·�Ƿ�ʹ��*/
    AV_VDEC_MODE_E              eDecMode;              /**<Video decoder mode *//**<CNcomment:��Ƶ����ģʽ*/
    AV_AUD_DOLBYDEC_CFG_S       stDolbyDecCfg;         /**<Dolby deocder config *//**<CNcomment:Dolby�������ò���*/
    AV_AUD_DOLBY_INFO_S         stDolbyInfo;           /**<Dolby info, only support getting *//**<CNcomment:Dolby����Ϣ����֧�ֻ�ȡ*/
    AV_AUD_DTS_INFO_S           stDtsInfo;             /**<Dts info, only support getting *//**<CNcomment:Dts����Ϣ����֧�ֻ�ȡ*/
    AV_LOW_DELAY_S              stLowDelayCfg;         /**<Low Delay Attr *//**<CNcomment: ����ʱ����*/
    AV_HDR_PARAM_S              stHdrParams;           /**<HDR parameter*//**<CNcomment:HDR����*/
    BOOL                        bEnableAudSecurity;    /**<Is audio security path enable or not*//**<CNcomment: ��ȫ��Ƶͨ·�Ƿ�ʹ��*/
#endif
} AV_SETTINGS_S;

typedef enum _AV_ATTR_ID_TYPE_E
{
    AV_ATTR_ID_ADEC,                /**<Audio decode parameters for special audio format, AV_ADEC_PARAM_S*//**<CNcomment: һ����Ƶ��ʽ����Ҫ����,ֻ���ض���ʽ��Ҫ����, AV_ADEC_PARAM_S.*/
    AV_ATTR_ID_VDEC,                /**<Video decode parameters for special Video format, AV_VDEC_PARAM_S*//**<CNcomment: һ����Ƶ��ʽ����Ҫ����,ֻ���ض���ʽ��Ҫ����, AV_VDEC_PARAM_S.*//* */

    AV_ATTR_ID_ASTREAMTYPE,         /**<Audio stream type, AV_AUD_STREAM_TYPE_E*//**<CNcomment:��Ƶ�����ͣ�AV_AUD_STREAM_TYPE_E*/
    AV_ATTR_ID_VSTREAMTYPE,         /**<Video stream type, AV_VID_STREAM_TYPE_E*//**<CNcomment:��Ƶ�����ͣ�AV_VID_STREAM_TYPE_E*/

    AV_ATTR_ID_AUD_PID,             /**<Audio pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)���ƽ̨֧��,��clear��ͨ����pid*/
    AV_ATTR_ID_VID_PID,             /**<Video pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)���ƽ̨֧��,��clear��ͨ����pid*/
    AV_ATTR_ID_PCR_PID,             /**<Pcr pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)���ƽ̨֧��,��clear��ͨ����pid*/

    AV_ATTR_ID_FRMRATE_PARAM,       /**<Frame Rate Parameter, AV_VDEC_FRAMERATE_PARAM_S*//**<CNcomment:,֡�ʲ���, AV_VDEC_FRAMERATE_PARAM_S.*/

#if 0 //�������
    AV_ATTR_ID_DOLBYDEC_CFG,        /**<Dolby deocder config, AV_AUD_DOLBYDEC_CFG_S *//**<CNcomment:Dolby�������ò���, AV_AUD_DOLBYDEC_CFG_S*/
    AV_ATTR_ID_DOLBY_INFO,          /**<Dolby info, only support getting, AV_AUD_DOLBY_INFO_S *//**<CNcomment:Dolby����Ϣ����֧�ֻ�ȡ, AV_AUD_DOLBY_INFO_S*/
    AV_ATTR_ID_DTS_INFO,            /**<Dts info, only support getting, AV_AUD_DTS_INFO_S *//**<CNcomment:Dts����Ϣ����֧�ֻ�ȡ, AV_AUD_DTS_INFO_S*/
    AV_ATTR_ID_AD,                  /* Audio Description attr, AV_AD_ATTR_S *//**<CNcomment:Audio Description����, AV_AD_ATTR_S*/

    AV_ATTR_ID_VDEC_MODE,           /**<Video decoder mode, AV_VDEC_MODE_E *//**<CNcomment:��Ƶ����ģʽ, AV_VDEC_MODE_E*/

    AV_ATTR_ID_SOURCE_PARAM,        /**<Data source, AV_SOURCE_PARAMS_S*//**<CNcomment:������Դ, AV_SOURCE_PARAMS_S*/
    AV_ATTR_ID_SYNC,                /**<Sync parameter, AV_SYNC_PARAM_S*//**<CNcomment:ͬ������, AV_SYNC_PARAM_S*/
    AV_ATTR_ID_STOP_MODE,           /**<Stop mode, AV_VID_STOP_MODE_E*//**<CNcomment:��Ƶֹͣģʽ, AV_VID_STOP_MODE_E*/
    AV_ATTR_ID_3D_FORMAT,           /**<3D format, AV_3D_FORMAT_E*/ /**<CNcomment: 3D TV ����, AV_3D_FORMAT_E*/
    AV_ATTR_ID_PLAY_SPEED,          /**<The trick modes consist in rewind, forward at slow and fast speed. 100: normal play, 200:Fast forward at two times the normal speed, -200:Fast backward at two times the normal speed,  50:Slow forward at 1/2 times the normal speed, 0 is free run*/
                                    /**<CNcomment:  100 :��������,200:������,-200:����2����,50:����֮һ����������0Ϊ���ɲ��ŵ�. ��Ҫ���ڱ�ʶ�������*/
    AV_ATTR_ID_VID_ROTATION,        /**<Rotation of picture, AV_VID_ROTATION_E*//**<CNcomment: ��Ƶ��ת�Ƕ�, AV_VID_ROTATION_E*/
    AV_ATTR_ID_LOW_DELAY,           /**<Low Delay Attr, AV_LOW_DELAY_S *//**<CNcomment: ����ʱ����, AV_LOW_DELAY_S*/
    AV_ATTR_ID_HDR_PARAM,           /**<HDR parameter, AV_HDR_PARAM_S*//**<CNcomment:HDR����, AV_HDR_PARAM_S*/
#endif
    AV_ATTR_ID_BUTT
} AV_ATTR_ID_TYPE_E;


/**Struct of iframe parameter*/
/**CNcomment:iframe ����(���ݼ��䳤��)  */
typedef struct _AV_IFRAME_PARAMS_S
{
    U32   u32DataLength;                    /**<Data address*//**<CNcomment:���ݵ�ַ*/
    VOID* pvIframeData;                     /**<Data length*//**<CNcomment:���ݳ���*/
    AV_VID_STREAM_TYPE_E enType;            /**<Data type*//**<CNcomment:����Codec ����*/
} AV_IFRAME_PARAMS_S;

/**Struct of iframe decode parameter*/
/**CNcomment:iframe �������*/
typedef struct _AV_IFRAME_DECODE_PARAMS_S
{
    AV_IFRAME_PARAMS_S stIframeParams;      /**<iframe parameter*//**<CNcomment:I֡������Ϣ*/
} AV_IFRAME_DECODE_PARAMS_S;

/**
\brief AV event callback. CNcomment:av �¼��ص������������� CNend
\attention \n
The function could call the api of AV module
CNcomment: �˺���������Ե��ñ�ģ���api, Ҳ����˵�����ڻص�������ʱ��Ҫͬʱ���ǵ������������������CNend
\param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
\param[in] enEvt Av event type.CNcomment:AV�¼����� CNend
\param[in] pvData The data with event, see AV_EVT_E.CNcomment:��ο� AV_EVT_E ��˵�� CNend
\retval ::SUCCESS CNcomment:�ɹ� CNend
\retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ�� CNend
\retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
\see \n
::AV_EVT_E
*/
typedef S32 (* AV_CALLBACK_PFN_T)(const HANDLE hAvHandle, const AV_EVT_E enEvt, const VOID* pvData);

/**Struct of av event config parameter*/
/**CNcomment:�����¼����ò���*/
typedef struct _AV_EVT_CONFIG_PARAMS_S
{
    AV_EVT_E            enEvt;                  /**<AV event*//**<CNcomment: av�¼�,��ʾ�����ö��ĸ��¼���Ч*/
    AV_CALLBACK_PFN_T   pfnCallback;            /**<Callback*//**<CNcomment: ��pfnCallbackΪ��ʱ,����Ѿ�ע���˻ص��������Ƴ�,ȡ����ע��*/
    BOOL                bEnableCallback;        /**<Wether enable callback*//**<CNcomment: ��ʾ�Ƿ�ʹ�ܸ��¼��ص�*/
    U32                 u32NotificationToSkip;  /**<Skip count before call callback*//**<CNcomment: ��ʾ�ڵ���ע��Ļص�����֮ǰ,��Ҫ�������η����ĸ��¼�*/
} AV_EVT_CONFIG_PARAMS_S;

/**Struct of AV module init parameter*/
/**CNcomment:AV ģ���ʼ������*/
typedef struct _AV_INIT_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} AV_INIT_PARAMS_S;

/**Struct of AV player create parameter*/
/**CNcomment:������ʵ���������� */
typedef struct _AV_CREATE_PARAMS_S
{
    AV_SOURCE_PARAMS_S stSourceParams;       /**<Source parameter, can be modifed dynamically*//**<CNcomment: ����ֵ,�Ժ���Զ�̬�޸�TODO*/
    AV_STREAM_TYPE_E   enStreamType;
} AV_CREATE_PARAMS_S;

/**Struct of AV player destroy parameter*/
/**CNcomment:�رղ�����ʵ������  */
typedef struct _AV_DESTROY_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} AV_DESTROY_PARAMS_S;

/**Struct of AV module terminate parameter*/
/**CNcomment:AVģ����ֹ����  */
typedef struct _AV_TERM_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} AV_TERM_PARAMS_S;

/**Struct of PCM data parameter*/
/**CNcomment:����PCM���ݲ����Ľṹ����  */
typedef struct _AV_PCM_PARAMS_S
{
    U32  u32SampleRate;        /**<Sample rate*//**<CNcomment: ��Ƶ������ (32000,44100,48000 ),0��ʾ����ע*/
    U32  u32BitWidth;          /**<Bit width*//**<CNcomment: ��Ƶÿ����������ռ�ı�����, ��:8bit,16bit,0��ʾ����ע */
    U32  u32AudChannel;        /**<Audio channels*//**<CNcomment: ������:0,1,2,4,6,8,10... ,0��ʾ����ע*/
    BOOL bBigEndian;           /**<TRUE: big endian; FALSE: little endian*//**<CNcomment: TRUE: ���; FALSE: С��*/
} AV_PCM_PARAMS_S;

/**Struct of video decode capability*/
/**CNcomment:����������*/
typedef struct _AV_VDEC_CAPABILITY_S
{
    // TODO: what is the bSupportedDecType mean?
    BOOL                bSupportedDecType;  /**<Wether supported the type of enDecCapLevel*//**<CNcomment: �Ƿ�֧��enDecCapLevel  ������*/
    VDEC_RESO_LEVEL_E   enDecCapLevel;      /**<video decode capability*//**<CNcomment: ��������*/
    U32                 u32Number;          /**<Max number of video decode*//**<CNcomment: �����Ƶ�������*/
    U32                 u32Fps;             /**<Frames per second*//**<CNcomment:  ֡��(x1000) ,ʵ��֡�ʳ�1000*/
    U32                 u32Dummy;           /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} AV_VDEC_CAPABILITY_S;

/**Struct of AV player decode capability*/
/**CNcomment:����������������*/
typedef struct _AV_DECODER_CAPABILITY_S
{
    AV_DATA_TYPE_E          enInjectDataType;                       /**<Injected data type*//**<CNcomment: ע����������� */
    U32                     au32AudDecode[AV_AUD_STREAM_TYPE_BUTT]; /**<non-0:supported,0:unsupported*//**<CNcomment: ��::AV_AUD_STREAM_TYPE_E����Ϊ����,����:֧��,0:��֧��*/
    U32                     au32AudBypass[AV_AUD_STREAM_TYPE_BUTT]; /**<non-0:supported,0:unsupported*//**<CNcomment: ��::AV_AUD_STREAM_TYPE_E����Ϊ����,����:֧��,0:��֧��*/
    AV_VDEC_CAPABILITY_S    stVidDecoder[AV_VID_STREAM_TYPE_BUTT];  /**<Video decode capability*//**<CNcomment:��Ƶ��������*/
} AV_DECODER_CAPABILITY_S;

/**Struct of AV player capability*/
/**CNcomment:����������*/
typedef struct _AV_CAPABILITY_S
{
    AV_DECODER_CAPABILITY_S stDecoderCapability; /**<AV player decode capability*//**<CNcomment:��������������*/
} AV_CAPABILITY_S;

// TODO: �Ƿ����ɾ��?
/**Struct of ES data parameter*/
/**CNcomment:ES ���ݲ���*/
typedef struct _AV_ES_PARAMS_S
{
    U32 u32SampleRate;    /**<Sample rate*//**<CNcomment: ��Ƶ������ (32000,44100,48000 ),0��ʾ����ע*/
} AV_ES_PARAMS_S;

/**Struct of ES data parameter*/
/**CNcomment:ES ���ݲ���*/
typedef struct _AV_ES_DATA_S
{
    S64         s64TimeStamp;       /**<TimeStamp*//**<CNcomment: ʱ��� */
    VOID*       pvHeader;           /**<Es Buffer header, NULL is no header*//**<CNcomment:  ES����ͷ�����û������ΪNULL */
    U32         u32HeaderLen;       /**<Length of es Buffer header, 0 is no header*//**<CNcomment:  ES����ͷ���ȣ����û������Ϊ0 */
    VOID*       pvEsBuf;            /**<Buffer address*//**<CNcomment:  ���ݻ�������ַ */
    U32         u32EsLen;           /**<Buffer length*//**<CNcomment:  ���������� */
    VOID*       pvPrivate;          /**<private address*//**<CNcomment:  ˽�����ݻ�������ַ */
    U32         u32PrivateLen;      /**<private length*//**<CNcomment:  ˽�����ݻ��������� */
    BOOL        bEndOfFrm;          /**<whether this package of stream contains the end of one frame*//**<CNcomment: �ð������Ƿ����һ֡�Ľ�β*/
} AV_ES_DATA_S;


#ifdef ANDROID_HAL_MODULE_USED
/**AV module structure(Android require)*/
/**CNcomment:AVģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _AV_MODULE_S
{
    struct hw_module_t stCommon;
} AV_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HAL_AV */
/** @{ */  /** <!-- [HAL_AV] */

/**AV device structure*//** CNcomment:AV�豸�ṹ*/
typedef struct _AV_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif
    /**
    \brief AV module init.CNcomment:AV ģ���ʼ��.CNend
    \attention \n
    Other functions cannot be useful before init, return SUCCESS when repeated called.
    CNcomment: �ڳ�ʼ��֮ǰ, ����������������ȷ����, �ظ�����init �ӿ�,����SUCCESS. CNend
    \param[in] pstInitParams Vout module init param.CNcomment:��ʼ��ģ����� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_AV_INIT_FAILED  other error.CNcomment:��ʼ������ CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AOUT_INIT_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_init)(struct _AV_DEVICE_S* pstDev, const AV_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief Create a AV player instance.CNcomment:����һ��������ʵ�� .CNend
    \attention \n
    None
    \param[out] phAv Return AV handle.CNcomment:����AV  ��� CNend
    \param[in] pstCreateParams Create param.CNcomment:�������� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  av not init.CNcomment:δ��ʼ�� CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::ERROR_AV_OP_FAILED Create too max av handle. CNcomment:��������avʵ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_CREATE_PARAMS_S

    \par example
    \code
    AV_CREATE_PARAMS_S stCreateParams;
    HANDLE hAvHandle = NULL;
    S32 s32Ret = SUCCESS;

    memset(&stCreateParams, 0x0, sizeof(AV_CREATE_PARAMS_S));
    stCreateParams.stSourceParams.enDemuxId = 0;
    s32Ret = av_create(pstDev, &hAvHandle, (const AV_CREATE_PARAMS_S * const)&stCreateParams);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }
    \endcode
    */
    S32 (*av_create)(struct _AV_DEVICE_S* pstDev, HANDLE* const phAv,
                     const AV_CREATE_PARAMS_S* const pstCreateParams);

    /**
    \brief Destroy a AV player instance.CNcomment:����һ��ʵ��.CNend
    \attention \n
    This operation will detach injecter but close it. CNcomment: �ò�������ע�������ǲ���ر�ע����CNend
    \param[in] hAvHandle AV handle.CNcomment:AV  ��� CNend
    \param[in] pstDestroyParams Destroy param.CNcomment:���ٲ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_DESTROY_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_destroy)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle,
                      const AV_DESTROY_PARAMS_S* const pstDestroyParams);

    /**
    \brief Terminate AV module.CNcomment:ģ����ֹ.CNend
    \attention \n
    Return SUCCESS when repeated called.
    CNcomment: �ظ�term ����SUCCESS. CNend
    \param[in] pstTermParams Terminate param.CNcomment:��ֹ���� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_TERM_FAILED Term av module fail, maybe has av or injecter not destroy. CNcomment:av ģ��ȥ��ʼ��ʧ�ܣ���������Ϊ��av����ע�������δ�ͷ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_TERM_PARAMS_S
    */
    S32 (*av_term)(struct _AV_DEVICE_S* pstDev, const AV_TERM_PARAMS_S* const pstTermParams);

    /**
    \brief Get the capability of AV module. CNcomment:��ȡģ���豸���� CNend
    \attention \n
    None
    \param[out] pstCapability Return capability.CNcomment:����ģ������ CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_CAPABILITY_S
    */
    S32 (*av_get_capability)(struct _AV_DEVICE_S* pstDev, AV_CAPABILITY_S* pstCapability);

    /**
    \brief Config the callback attribute of AV event. CNcomment:����ĳһAV�¼��Ĳ��� CNend
    \attention \n
    The function can execute regist/remove/disable/enable
    1.Each event can register callback function and set it's config independently.
    2.Callback function bind with AV handle.
    3.Only one callback function can be registered for a AV event on the same AV handle, so the callback function will be recovered.
    CNcomment: ͨ������������ִ�еĲ�����regist/remove/disable/enable
    1. ÿ���¼������Զ���ע��������Լ��Ļص�����.
    2. �ص�������handle��.
    3. ͬһ��handle, һ���¼�ֻ��ע��һ���ص�����,��:����ע��Ļص������Ḳ��ԭ�еĻص�����.
    CNend
    \param[in] hAvHandle AV handle.CNcomment:VOUT ��� CNend
    \param[in] pstCfg Config param.CNcomment:�¼����ò��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_EVT_CONFIG_PARAMS_S

    \par example
    //register
    VOID VidEvtCallback(const HANDLE hAvHandle, const AV_EVT_E enEvt, const void * const pvData)
    {
        switch (enEvt)
        {
            case AV_VID_EVT_DECODE_START:
            {
                AV_VID_STATUS_S *pstVidStatus = NULL;

                if (HI_NULL != pvData)
                {
                    pstVidStatus = (AV_VID_STATUS_S *)pvData;
                    printf("Video pid = %#x", pstVidStatus->u16Pid);
                }

            }
            break;

            default:
            break;
        }
    }

    AV_EVT_CONFIG_PARAMS_S stAvEvtCfg;
    S32 s32Ret = SUCCESS;

    memset(&stAvEvtCfg, 0x0, sizeof(AV_EVT_CONFIG_PARAMS_S));
    stAvEvtCfg.enEvt = AV_VID_EVT_DECODE_START;
    stAvEvtCfg.pfnCallback = VidEvtCallback;
    stAvEvtCfg.bEnableCallback = TRUE;
    stAvEvtCfg.u32NotificationToSkip = 0;
    s32Ret = av_evt_config(pstDev, hAvHandle, (const AV_EVT_CONFIG_PARAMS_S * const)&stAvEvtCfg);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    //remove
    AV_EVT_CONFIG_PARAMS_S stAvEvtCfg;
    S32 s32Ret = SUCCESS;

    memset(&stAvEvtCfg, 0x0, sizeof(AV_EVT_CONFIG_PARAMS_S));
    stAvEvtCfg.enEvt = AV_VID_EVT_DECODE_START;
    stAvEvtCfg.pfnCallback = NULL;
    stAvEvtCfg.bEnableCallback = FALSE;
    stAvEvtCfg.u32NotificationToSkip = 0;
    s32Ret = av_evt_config(pstDev, hAvHandle, (const AV_EVT_CONFIG_PARAMS_S * const)&stAvEvtCfg);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    //disable
    AV_EVT_CONFIG_PARAMS_S stAvEvtCfg;
    S32 s32Ret = SUCCESS;

    memset(&stAvEvtCfg, 0x0, sizeof(AV_EVT_CONFIG_PARAMS_S));
    s32Ret = av_get_evt_config(pstDev, hAvHandle, AV_VID_EVT_DECODE_START, &stAvEvtCfg);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    stAvEvtCfg.bEnableCallback = FALSE;
    s32Ret = av_evt_config(pstDev, hAvHandle, (const AV_EVT_CONFIG_PARAMS_S * const)&stAvEvtCfg);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    //enable
    AV_EVT_CONFIG_PARAMS_S stAvEvtCfg;
    S32 s32Ret = SUCCESS;

    memset(&stAvEvtCfg, 0x0, sizeof(AV_EVT_CONFIG_PARAMS_S));
    stAvEvtCfg.enEvt = AV_VID_EVT_DECODE_START;
    s32Ret = av_get_evt_config(pstDev, hAvHandle, &stAvEvtCfg);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    stAvEvtCfg.bEnableCallback = TRUE;
    s32Ret = av_evt_config(pstDev, hAvHandle, (const AV_EVT_CONFIG_PARAMS_S * const)&stAvEvtCfg);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    \code
    \endcode
    */
    S32 (*av_evt_config)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle,
                         const AV_EVT_CONFIG_PARAMS_S* const pstCfg);

    /**
    \brief Get the config of a AV event. CNcomment:��ȡĳһAV �¼������ò��� CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] enEvt AV evnet type.CNcomment:AV�¼����� CNend
    \param[out] pstCfg Config param.CNcomment:�¼����ò��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_EVT_CONFIG_PARAMS_S

    \par example
    \code
    AV_EVT_CONFIG_PARAMS_S stAvEvtCfg;
    S32 s32Ret = SUCCESS;

    memset(&stAvEvtCfg, 0x0, sizeof(AV_EVT_CONFIG_PARAMS_S));
    s32Ret = av_get_evt_config(pstDev, hAvHandle, AV_VID_EVT_DECODE_START, &stAvEvtCfg);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }
    \endcode
    */
    S32 (*av_get_evt_config)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle,
                             const AV_EVT_E enEvt, AV_EVT_CONFIG_PARAMS_S* const pstCfg);

    /**
    \brief Get status of AV instance. CNcomment:��ȡav״̬ CNend
    \attention \n
    Stream info, decode status, DAC status.
    CNcomment: ��ǰ��,������,DAC��״̬CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[out] pstStatus Status param.CNcomment:״̬���� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_STATUS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_get_status)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_STATUS_S* pstStatus);

    /**
    \brief Get config of AV instance. CNcomment:��ȡav���� CNend
    \attention \n
    Get AV param first, and then renew the param, then set.
    CNcomment: �޸�av����ʱ,����get����,�޸���Ҫ�޸ĵĳ�Ա��set��ȥCNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[out] pstSettings Return setting param.CNcomment:�������ò��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_SETTINGS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_get_config)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_SETTINGS_S* pstSettings);

    /**
    \brief Set config of AV instance. CNcomment:����av���� CNend
    \attention \n
    Get AV param first, and then renew the param, then set.
    CNcomment: �޸�av����ʱ,����get����,�޸���Ҫ�޸ĵĳ�Ա��set��ȥCNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] pstSettings Setting param.CNcomment:���ò��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_SETTINGS_S

    \par example
    \code
    AV_SETTINGS_S stSettings;
    S32 s32Ret = SUCCESS;

    memset(&stSettings, 0x0, sizeof(AV_SETTINGS_S));
    s32Ret = av_get_config(pstDev, hAvHandle, &stSettings);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    stSettings.enVidStreamType = AV_VID_STREAM_TYPE_MPEG2;
    stSettings.u16VidPid = 0x100;
    stSettings.enAudStreamType = AV_AUD_STREAM_TYPE_MP3;
    stSettings.u16AudPid = 0x101;
    stSettings.u16PcrPid = 0x100;
    s32Ret = av_get_config(pstDev, hAvHandle, &stSettings);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }
    \endcode
    */
    S32 (*av_set_config)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_SETTINGS_S* const pstSettings);

    /**
    \brief Get attribte of AV instance. CNcomment:��ȡav���� CNend
    \attention \n
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] enAttrID attribe ID.CNcomment:��������ID CNend
    \param[out] pstSettings Return attribte param.CNcomment:�����������ԣ�����enAttrID��Ӧ��ͬ���͡� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_ATTR_ID_TYPE_E

    \par example
    \code
    \endcode
    */
    S32 (*av_get_attr)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_ATTR_ID_TYPE_E enAttrID, VOID* pstSettings);

    /**
    \brief Set attribte of AV instance. CNcomment:����av���� CNend
    \attention \n
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] enAttrID attribe ID.CNcomment:��������ID CNend
    \param[in] pstSettings attribte param.CNcomment:���Խṹ��ָ�룬����enAttrID��Ӧ��ͬ���� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_ATTR_ID_TYPE_E
    */
    S32 (*av_set_attr)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_ATTR_ID_TYPE_E enAttrID, VOID* const pstSettings);

    /**
    \brief Start AV play. CNcomment: ��ʼAV���� CNend
    \attention \n
    Since the app does not manage the status, should stop first, and then renew settings, then start again.
    CNcomment: ����Ӧ�þ���û�й����״̬,����Ƶ��֮��,��start״̬��start, Ϊ�˱��ⲥ�ų�����,��start״̬��start, ��Ҫ��stop,����settings��start. CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:δ�����ݵ�ԪCNend
    \retval ::ERROR_AV_VID_AND_AUD_START_FAIL Video and audio start fail. CNcomment:����Ƶ������ʧ��CNend
    \retval ::ERROR_AV_AUD_START_FAIL Audio start fail but video start success. CNcomment:��Ƶ�����ɹ�����Ƶ����ʧ��CNend
    \retval ::ERROR_AV_VID_START_FAIL Audio start fail but video start success. CNcomment:��Ƶ�����ɹ�����Ƶ����ʧ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_start)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop AV play. CNcomment:ֹͣAV����CNend
    \attention \n
    This operation will not detach or close injecters. CNcomment: �ò�������ִ��ע�����Ľ�󶨻�رն��� CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_stop)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Pause video and audio play, real-time streaming does not support. CNcomment:��ͣ����Ƶ����, ʵʱ����֧��sCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pause)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Resume video and audio play, real-time streaming does not support. CNcomment:�ָ�����Ƶ����, ʵʱ����֧��sCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_resume)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Reset video and audio play. CNcomment:��������Ƶ���嵽ĳ��ʱ���CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] s64TimeMs Reset time, unit is ms.CNcomment:����ʱ���,��λ����CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_reset)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, S64 s64TimeMs);

    /**
    \brief Start video play. CNcomment:������Ƶ����CNend
    \attention \n
    Since the app does not manage the status, should stop first, and then renew settings, then start again.
    CNcomment: ����Ӧ�þ���û�й����״̬,����Ƶ��֮��,��start״̬��start,  Ϊ�˱��ⲥ�ų�����,��start״̬��start, ��Ҫ��stop,����settings��start. CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:δ�����ݵ�ԪCNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_start_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Pause video play, real-time streaming does not support. CNcomment:��ͣ��Ƶ����, ʵʱ����֧��sCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pause_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Freeze current picture, video decoding continues. CNcomment:��Ƶ�����������������ʾCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] bFreeze Freeze or unfreeze video picture, ::TRUE freeze video picture, ::FALSE unfreeze video picture. CNcomment: �����ָ���ƵCNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_freeze_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, BOOL bFreeze);

    /**
    \brief Resume video play. CNcomment:�ָ���Ƶ����CNend
    \attention \n
    Resume from pause status.
    CNcomment: ��pause״̬�лָ�. CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_resume_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop video play. CNcomment:ֹͣ��Ƶ����CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_stop_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Clear the picture on the screen and video data in the display buffer.
    CNcomment:�����Ƶ��ʾbuf�е�����,ͬʱ�������Ļ�ϵ���ʾ,��Щƽ̨���ܲ�֧��CNend
    \attention \n
    You should call av_stop_video before call this function.
    CNcomment:
    ��Ҫvideo stop֮����ܵ���,(����iframe ��ʾ���) .
    CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_clear_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Start audio play. CNcomment:��ʼ��Ƶ����CNend
    \attention \n
    Since the app does not manage the status, should stop first, and then renew settings, then start again.
    CNcomment: ����Ӧ�þ���û�й����״̬,����Ƶ��֮��,��start״̬��start,  Ϊ�˱��ⲥ�ų�����,��start״̬��start, ��Ҫ��stop,����settings��start. CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:δ�����ݵ�ԪCNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_start_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Pause audio play, real-time streaming does not support. CNcomment:��ͣ��Ƶ���룬ʵʱ����֧��sCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pause_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Resume audio play, real-time streaming does not support. CNcomment:�ָ���Ƶ����CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_resume_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop audio play. CNcomment:ֹͣ��Ƶ����CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_stop_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Decode iframe data. CNcomment:iframe ���ݽ���CNend
    \attention \n
    Decode a ifame, wether renew screen depend on the current display mode.
    If pstCapPicture is null, the decoded I frames are displayed in the window,and do not need release memory; \n
    if pstCapPicture is not null, the information about I frames is reported, and need invoke ::av_release_iframe to release memory.
    CNcomment:
    ����һ��iframe, �Ƿ������Ƶ��ʾȡ���ڵ�ǰ��Ƶ��ʾ����
    ��pstCapPictureΪ��ָ��ʱ�������I֡����window����ʾ�������ͷ��ڴ棬����ǿգ��򲻻���ʾ���ǽ�I֡��Ϣ�ϱ�,ͬʱI֡������Ϻ���Ҫ����av_release_iframe���ͷ�I֡
    video ���iframe�ɵ���av_enable_video������ʾ;av_disable_video����
    video ���iframe������Ƶ���¿�ʼ�µĽ���󱻳��
    CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] pstIframeDacodeParams Iframe info.CNcomment:iframe�������CNend
    \param[in] pstCapPicture Iframe info.CNcomment:iframe�������CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_IFRAME_DECODE_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_decode_iframe)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle,
                            const AV_IFRAME_DECODE_PARAMS_S* const pstIframeDacodeParams, AV_VID_FRAMEINFO_S* pstCapPicture);

    /**
    \brief Release memory of I frame. CNcomment:�ͷ�I֡֡��CNend
    \attention \n
    If you call av_decode_iframe with non-null pstCapPicture, you need call this API to release the memory.
    CNcomment:�����av_decode_iframeʱpstCapPicture��Ϊ�գ���Ҫ���ô˽ӿ����ͷ��ڴ� CNend
    CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] pstCapPicture Pointer to the frame information.CNcomment:ָ�����ͣ��ͷŵ�֡��Ϣ CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_VID_FRAMEINFO_S

    \par example
    \code
    \endcode
    */
    S32 (*av_release_iframe)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, const AV_VID_FRAMEINFO_S* pstCapPicture);

    /**
    \brief Open a injecter instance. CNcomment:��һ��ע��ʵ��CNend
    \attention \n
    None
    \param[out] phInjecter Return injecter handle.CNcomment:����ע�������CNend
    \param[in] pstOpenParams Open param.CNcomment:iframe�򿪲���CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_injecter_open)(struct _AV_DEVICE_S* pstDev, HANDLE* const  phInjecter,
                            AV_INJECTER_OPEN_PARAMS_S* const pstOpenParams);

    /**
    \brief Close a injecter instance. CNcomment:�ر�һ��ע��ʵ��CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] pstCloseParams Close param.CNcomment:iframe�ر� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_injecter_close)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                             AV_INJECTER_CLOSE_PARAMS_S* const pstCloseParams);

    /**
    \brief Attach injecter and AV handle. CNcomment:��һ��ע����������decoder��ȥCNend
    \attention \n
    1. One av player can be attached by multi injecter:
       You inject PCM while playing video from tuner, or inject es video data while playing audio from tuner;
       But injecter with the same AV_CONTENT_TYPE_E type should be only one, so audio or video injecter must be only one.
    2. If av player has no attached injecter, the data come from tuner defaultly.
        If av player has been attached with any injecter, then the data of injecter will precedence over tuner data.
        If av player has been attached with PCM injecter, the player should process the audio data of injecter but not the audio data from tuner.
        If av player has been attached with Video ES injecter, the player should process the video data of injecter but not the video data from tuner.
        If injecter which attached with av player inject the data into demux, it will affect the data of audio and video.
        If injecter which attached with av player just inject the data into decoder, it will not affect the data of demux and data of other decoder.
        If av player has been attached with PCM injecter, it will not affect the data of demux and data of video channel.
    3. Settings of injecter of single channel(A/V) will not affect other channels.
        For example, inject iframe will not affect the playing of PCM
    CNcomment:
    1. һ��hAv ���Թ������ hInjecter,
        ���Ա߲���tuner ts������Ƶ,��ע��pcm,���߲߱���tuner ts ����audio,��ע��es video
        ����AV_CONTENT_TYPE_E ��ͬ��hInjecter ֻ����һ��,
        ������Ƶͨ��ֻ�ܹ���һ��hInjecter,��Ƶͨ��Ҳֻ�ܹ���һ��hInjecter.
    2. ���hAv  ��Ӧͨ��û�й���hInjecter,��ô�������ݽ�Ĭ�ϴ�tuner����.
        ����ĳ��ͨ���Ϲ�����hInjecter, ��ô�������ݽ�������tuner������.
        ���������pcm �� hInjecter, ��ô��Ϊ��Ƶ�����Ǵ�injecter ����,������tuner.
        ���������video es ��hInjecter,��ô��Ϊ��Ƶ�����Ǵ�injecter����,������tuner.
        ���������hInjecter ����dmxע������,��ô����Ӱ������Ƶ����ͨ����������Դ
        ���������hInjecterֻ����decoderע������,��ô������Ӱ��dmx������.Ҳ����Ӱ��decoder ����ͨ��������
        ���������pcm ��hInjecter,������Ӱ��dmx & videoͨ��������
    3. ����ͨ��(a/v) injecter �����ò���Ӱ������ͨ��
        ���������iframe��ע�벻�ᵼ��ԭ��pcm���ŵ��жϻ���ͣ��.
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    AV_CREATE_PARAMS_S stCreateParams;
    HANDLE hAvHandle = NULL;
    S32 s32Ret = SUCCESS;

    memset(&stCreateParams, 0x0, sizeof(AV_CREATE_PARAMS_S));
    stCreateParams.stSourceParams.enDemuxId = 0;
    s32Ret = av_create(pstDev, &hAvHandle, (const AV_CREATE_PARAMS_S * const)&stCreateParams);
    if (SUCCESS != s32Ret)
    {
        return FAILURE;
    }

    AV_INJECTER_OPEN_PARAMS_S stInjectOpen;
    HANDLE hInjecter = NULL;

    memset(&stInjectOpen, 0x0, sizeof(stInjectOpen));
    stInjectOpen.stSettings.enDataType = AV_DATA_TYPE_TS;
    stInjectOpen.stSettings.enInjectContent = AV_INJECT_CONTENT_DEFAULT;
    stInjectOpen.stSettings.u32BufSize = 0;
    stInjectOpen.stSettings.u32InjectMinLen = 0;
    s32Ret = av_injecter_open(pstDev, &hInjecter, &stInjectOpen);
    if (SUCCESS != s32Ret)
    {
        av_destroy(pstDev, hAvHandle, NULL);
        return FAILURE;
    }

    s32Ret = av_injecter_attach(pstDev, hInjecter, hAvHandle);
    if (SUCCESS != s32Ret)
    {
        av_destroy(pstDev, hAvHandle, NULL);
        av_injecter_close(pstDev, hInjecter, NULL);
        return FAILURE;
    }

    \endcode
    */
    S32 (*av_injecter_attach)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                              const HANDLE hAvHandle);

    /**
    \brief Detach injecter and AV handle. CNcomment:ȡ��ע��������CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_injecter_detach)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter);

    /**
    \brief Inject data. CNcomment:ע����Ҫ���������CNend
    \attention \n
    The data will be injected to demux or decoder, depend on the data type.
    If the sample rate of PCM data is 16 bit, the data must be 4-bytes alignment.
    If TS data, the data must be a complete TS package.
    If PES data, the data must be a complete PES package.
    If es data which does not need to sync, the data must be a complete frame.
    If es data which need to sync, call av_inject_es_data, and input timestamp.
    CNcomment:
    ����ע�����ݵ����ͣ�������ע��dmxҲ������ע��decoder
    �����16λ������pcm����,�밴16λ����ע��
    �����ts����,��Ҫ��������ts��Ϊ��λע��
    �����PES����,��Ҫ��������pes ��Ϊ��λע��
    ����ǲ���Ҫͬ����es����(����ʱ���),����һ��֡Ϊ��λע��
    �������Ҫͬ����es����,�����av_inject_es_data()����ע��,����ʱ���
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] pvData Data address, the address should be approprite byte aglinment depend on the platform.CNcomment:ע�����ݵ�ַ,Ϊ������ٶȣ�����ݸ���ƽ̨�����ȡ���ʵĶ��뷽ʽCNend
    \param[in] u32Length Data length.CNcomment:���ݳ��� CNend
    \param[in] u32TimeoutMs Timeout in ms.CNcomment:��ʱʱ��, ��λ���� CNend

    \retval ::>0 Length of send data successful. CNcomment:�ɹ����͵������ֽ��� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_data)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                          VOID* const pvData, const U32 u32Length, U32 u32TimeoutMs);

    /**
    \brief Get free buffer of the injecter.
    CNcomment:
     ��ȡ�´�ע�뻺�����еĿ���Buffer��ַָ�����������Buffer�Ĵ�С��
     ������ݺ�ͨ��av_inject_write_complete �������������͵������� CNend
    \attention \n
    The buffer returned must be contiguous space, and buffer length must be a multipe of u32InjectMinLen;
    If the buffer is full, this interface should return fail, and the value of *puLength is 0;
    Must be paired with av_inject_write_complete, consider thread safety.
    CNcomment:
     ��ʱ��û�аѵ�buf��ѭ��bufʹ��,ʹ�õ��������Ŀռ�,
     ֻ��֤buf��С��u32InjectMinLen�ı���,
     ���buffer�Ѿ������ô˽ӿ�Ӧ�÷���ʧ�ܣ���puLength����Ϊ0
     ������av_inject_write_complete���ʹ��,����Ҫ�����̰߳�ȫ
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] u32ReqLen Request data buffer len.CNcomment:����ȡ�����ݳ��� CNend
    \param[out] ppvBufFree Return free buffer address pointer.CNcomment:���ؿ��пռ�ĵ�ַָ��CNend
    \param[out] pu32FreeSize Return free buffer size.CNcomment:���ؿռ�ռ䳤��CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_freebuf)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter, U32 u32ReqLen,
                                 VOID** ppvBufFree, U32* pu32FreeSize);


    /**
    \brief After call av_inject_get_freebuf function and copy date to free buffer, then call this function to send to decoder.
    CNcomment:����av_inject_get_freebuf��ȡ����buffer���ҿ��������ݺ󣬵��øú����͸�������CNend
    \attention \n
    Must be paired with av_inject_get_freebuf, consider thread safety.
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] u32WriteSize Number of bytes that are written to the buffer.CNcomment:ʵ��д�뻺�������ֽ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_write_complete)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                    U32 u32WriteSize, S64 s64Pts);

    /**
    \brief Get the buffer status of injecter
    CNcomment:��ȡ�ڴ�ע�뷽ʽ��buf״̬CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[out] pstBufStatus Return buffer status.CNcomment:���ػ���״̬CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_buf_status)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                    AV_BUF_STATUS_S* const pstBufStatus);

    /**
    \brief Get the status of injecter
    CNcomment:��ȡע����״̬CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[out] pstStatus Return Injecter status.CNcomment:����ע����״̬CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_status)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                AV_INJECT_STATUS_S* const pstStatus);

    /**
    \brief Get the settings of injector
    CNcomment:��ȡע�������ò���CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[out] pstSettings Return Injecter settings.CNcomment:����ע�������ò���  CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_setting)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                 AV_INJECT_SETTINGS_S* const pstSettings);

    /**
    \brief Reset injecter buf
    CNcomment:��λע��buffer CNend
    \attention \n
    To aviod error, it is best to call in the decoder stopped state
    CNcomment:
    Ϊ�˱������,�����decoderֹͣ״̬�µ���
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_reset_buf)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter);

    // TODO: �ĺ���������������ã�av_set_config�Ѿ������˹���
    /**
    \brief Set PCM param
    CNcomment:����PCM ����CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] pstParams PCM param.CNcomment:PCM ����CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid.CNcomment:��ָ��CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE other error.CNcomment:�������� CNend
    \see \n
    ::AV_PCM_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_set_pcm_params)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                    AV_PCM_PARAMS_S* const pstParams);

    // TODO: �ĺ���������������ã�av_set_config�Ѿ������˹���
    /**
    \brief Set es param
    CNcomment:����es  ����CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] pstParams ES param.CNcomment:ES ����CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:��ǰ״̬�²�֧�ֵĲ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_PCM_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_set_es_params)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                   AV_ES_PARAMS_S* const pstParams);

    /**
    \brief Inject es data to injecter
    CNcomment:�ڴ淽ʽע��es����CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] pstEsData ES data.CNcomment:ES ����CNend
    \param[in] u32TimeoutMs Timeout in ms.CNcomment:��ʱʱ��,��λ����CNend

    \retval ::>0 Length of send data successful. CNcomment:�ɹ����͵������ֽ��� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_es_data)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                             AV_ES_DATA_S* const pstEsData, U32 u32TimeoutMs);

    /**
    \brief Abort injected data
    CNcomment:��ֹ����ע��CNend
    \attention \n
    Abort av_inject_es_data and av_inject_data.
    When timeout is not 0, av_inject_es_data and av_inject_data will be blocked, and av_inject_abort can break the blocking status, the inject operation will fail.
    CNcomment:
    ��ֹav_inject_es_data(),av_inject_data().
    ��av_inject_es_data(),av_inject_data().�ĳ�ʱʱ�䲻Ϊ0ʱ,����������,av_inject_abort()���Խ������,�����˳�.����ע�����ʧ��.
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] pstPesData ES data.CNcomment:ES ����CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_abort)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter);

#ifdef HAL_HISI_EXTEND_H
    /********************************* Extend Function Definition Before ***************************/

   /**
    \brief Get free buffer of the injecter expansion interface.
    CNcomment:
     ָ�������Ļ���������,��ȡ�´�ע�뻺�����еĿ���Buffer��ַָ�����������Buffer�Ĵ�С��
     ������ݺ�ͨ��av_inject_write_complete �������������͵������� CNend
    \attention \n
    The buffer returned must be contiguous space, and buffer length must be a multipe of u32InjectMinLen;
    If the buffer is full, this interface should return fail, and the value of *puLength is 0;
    Must be paired with av_inject_write_complete, consider thread safety.
    CNcomment:
     ��ʱ��û�аѵ�buf��ѭ��bufʹ��,ʹ�õ��������Ŀռ�,
     ֻ��֤buf��С��u32InjectMinLen�ı���,
     ���buffer�Ѿ������ô˽ӿ�Ӧ�÷���ʧ�ܣ���puLength����Ϊ0
     ������av_inject_write_complete���ʹ��,����Ҫ�����̰߳�ȫ
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:ע������� CNend
    \param[in] u32ReqLen Request data buffer len.CNcomment:����ȡ�����ݳ��� CNend
    \param[in] eReqBufType Request buffer type.CNcomment:������ȡ�Ļ��������� CNend
    \param[out] ppvBufFree Return free buffer address pointer.CNcomment:���ؿ��пռ�ĵ�ַָ��CNend
    \param[out] pu32FreeSize Return free buffer size.CNcomment:���ؿ��пռ䳤�� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:ע����û�д�CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_freebuf_ex)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter, U32 u32ReqLen,
                                    AV_INJECT_BUF_TYPE_E eReqBufType, VOID** ppvBufFree, U32* pu32FreeSize);

    /**
     \brief Acquire audio or video frame that after decode
    CNcomment:��ȡ��������Ƶ����Ƶ֡����CNend
     \attention \n
     None
     \param[in] hHandle vout window or aout track handle, vout window handle for get video frame, aout track handle for get audio frame .
     CNcomment:��Ƶ����Ƶ�������ȡ��Ƶ֡��vout window�������ȡ��Ƶ֡��aout track���CNend
     \param[in] eFrameType Data type, video or audio.CNcomment:�������ͣ���Ƶ����ƵCNend
     \param[in] u32TimeoutMs Timeout in ms.CNcomment:��ʱʱ��,��λ����CNend
     \param[out] pFrame Information of acquiring frame, if eFrameType is ::AV_CONTENT_AUDIO, pFrame type is ::AV_AUD_FRAMEINFO_S, if eFrameType is ::AV_CONTENT_VIDEO, pFrame type is ::AV_VID_FRAMEINFO_S.
                    CNcomment:��ȡ������Ƶ֡��Ϣ, ���eFrameType Ϊ::AV_CONTENT_AUDIO, pFrame ����Ϊ::AV_AUD_FRAMEINFO_S, ���eFrameType Ϊ::AV_CONTENT_VIDEO, pFrame ����Ϊ::AV_VID_FRAMEINFO_S CNend

     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
    */
    S32 (*av_acquire_frame)(struct _AV_DEVICE_S* pstDev, const HANDLE hHandle, AV_CONTENT_TYPE_E eFrameType, VOID* pFrame, U32 u32TimeoutMs);

    /**
     \brief Release audio or video frame that acquiring frome AV.
    CNcomment:�ͷŻ�ȡ������Ƶ֡����CNend
     \attention \n
     None
     \param[in] hHandle vout window or aout track handle, vout window handle for get video frame, aout track handle for get audio frame .
     CNcomment:��Ƶ����Ƶ�������ȡ��Ƶ֡��vout window�������ȡ��Ƶ֡��aout track���CNend
     \param[in] eFrameType Data type, video or audio.CNcomment:�������ͣ���Ƶ����ƵCNend
     \param[in] pFrame Information of acquiring frame, if eFrameType is ::AV_CONTENT_AUDIO, pFrame type is ::AV_AUD_FRAMEINFO_S, if eFrameType is ::AV_CONTENT_VIDEO, pFrame type is ::AV_VID_FRAMEINFO_S.
                    CNcomment:��ȡ������Ƶ֡��Ϣ, ���eFrameType Ϊ::AV_CONTENT_AUDIO, pFrame ����Ϊ::AV_AUD_FRAMEINFO_S, ���eFrameType Ϊ::AV_CONTENT_VIDEO, pFrame ����Ϊ::AV_VID_FRAMEINFO_S CNend

     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
    */
    S32 (*av_release_frame)(struct _AV_DEVICE_S* pstDev, const HANDLE hHandle, AV_CONTENT_TYPE_E eFrameType, const VOID* pFrame);

    /**
    \brief AV set vdec buffer mode
    CNcomment:����vdec��buffer���䷽ʽCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV��� CNend
    \param[in] buffer mode.CNcomment:BufferģʽCNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_set_buf_mode)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_FRAME_BUFFER_MODE_E eBufMode);

    /**
    \brief AV acquire user buffer
    CNcomment:��vdec�����ⲿbuffer CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV��� CNend
    \param[in] pstBuf Buffer pointer.CNcomment:Bufferָ��CNend
    \param[in] u32Cnt Buffer counter.CNcomment:Buffer����CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_acquire_user_buf)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_USER_BUFFER_S* pstBuf, U32 u32Cnt);

    /**
    \brief AV acquire user buffer
    CNcomment:vdec �ͷ��ⲿbuffer CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV��� CNend
    \param[in] pstBuf Buffer pointer.CNcomment:Bufferָ��CNend
    \param[in] u32Cnt Buffer counter.CNcomment:Buffer����CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_release_user_buf)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_USER_BUFFER_S* pstBuf, U32 u32Cnt);

    /**
    \brief AV format change CNcomment:AV��ʽ�л�CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle. CNcomment:AV��� CNend
    \param[in] u32Width format width. CNcomment:��ʽ��� CNend
    \param[in] u32Height format height. CNcomment:��ʽ�߶� CNend
    \param[in,out] pbVideoBypass video bypass flag.CNcomment:video�Ƿ�͸����־CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_format_change)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, U32* pu32Width, U32* pu32Height, BOOL* pbVideoBypass);

    /**
    \brief AV sync frame
    CNcomment:��ȡAV֡ͬ����ϢCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV��� CNend
    \param[in] pvFrame frame pointer.CNcomment:ָ֡��CNend
    \param[in] pstSyncRef sync ref info.CNcomment:ͬ���ο���ϢCNend
    \param[in,out] pstSyncInfo sync info.CNcomment:ͬ����ϢCNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_sync_frame)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, const VOID* pvFrame, const AV_SYNC_REF_S* pstSyncRef, AV_SYNC_INFO_S* pstSyncInfo);

    /**
    \brief AV register audio lib
    CNcomment:ע�������Ƶ��CNend
    \attention \n
    None
    \param[in] pstDev AV handle.CNcomment:AV��� CNend
    \param[in] ps8Audlib audlib name.CNcomment:��Ƶ������CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_register_audiolib)(struct _AV_DEVICE_S* pstDev, const S8* ps8Audlib);

    /**
    \brief AV invoke function, extend other function by user.
    CNcomment:invoke ��չ�ӿڣ������û�˽�й�����չCNend
    \attention \n
    None
    \param[in] pstDev AV handle.CNcomment:AV��� CNend
    \param[in] hAvHandle AV handle.CNcomment:AV��� CNend
    \param[in] eCmd Invoke ID, defined is ::AV_INVOKE_E.CNcomment:Invoke ID, ������� ::AV_INVOKE_E CNend
    \param[in,out] pArg Command parameter.CNcomment:������� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE other error.CNcomment:�������� CNend
    \see \n
    ::AV_INVOKE_E

    \par example
    \code
    \endcode
    */
    S32 (*av_invoke)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_INVOKE_E eCmd, VOID* pArg);

    /**
    \brief AV set HDR10 info function.
    CNcomment:����HDR10��ϢCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] pstHDR10Info HDR10 info.CNcomment:HDR10 ��Ϣ CNend
    \param[in] bPaddingHdrInfo if need padding HDR information to frame information.CNcomment:�Ƿ���Ҫ���HDR��Ϣ��֡��Ϣ�� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE other error.CNcomment:�������� CNend
    \see \n
    ::AV_VIDEO_HDR10_INFO_S

    \par example
    \code
    \endcode
    */
    S32 (*av_set_hdr10_info)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, const AV_VIDEO_HDR10_INFO_S* pstHDR10Info, BOOL bPaddingHdrInfo);

    /**
    \brief AV set metadata info function.
    CNcomment:����Metadata��ϢCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \param[in] pstMetaDataInfo Metadata info.CNcomment:��Ҫ���õ�Metadata��Ϣ CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE other error.CNcomment:�������� CNend
    \see \n
    ::AV_VIDEO_METADATA_INFO_S

    \par example
    \code
    \endcode
    */
    S32 (*av_set_metadata_info)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, const AV_VIDEO_METADATA_INFO_S* pstMetaDataInfo);

    /**
    \brief Start video to prepare play mode, which just demux ts stream. CNcomment: ������Ƶ���Ž���Ԥ����(PERPLAY)״̬ CNend
    \attention \n
    PREPLAY mode just dsemux ts, is used for fullband. CNcomment: Ԥ����״̬������TS�Ľ⸴�ã�����Fullband��̨CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:δ�����ݵ�ԪCNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pre_start_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop video to prepare stop mode,the interface is reserved for future use. CNcomment: ֹͣ��Ƶ���Ž���Ԥֹͣ(PERSTOP)״̬���ýӿڱ������� CNend
    \attention \n
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_SUPPORTED  not support for the moment.CNcomment:�ݲ�֧�֡�CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pre_stop_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Start audio to prepare play mode, which just demux ts stream. CNcomment: ������Ƶ���Ž���Ԥ����(PERPLAY)״̬ CNend
    \attention \n
    PREPLAY mode just dsemux ts, is used for fullband. CNcomment: Ԥ����״̬������TS�Ľ⸴�ã�����Fullband��̨CNend
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:ʵ��δ����CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:δ�����ݵ�ԪCNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pre_start_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop audio to prepare stop mode, the interface is reserved for future use. CNcomment: ֹͣ��Ƶ���Ž���Ԥֹͣ(PERSTOP)״̬���ýӿڱ������� CNend
    \attention \n
    \param[in] hAvHandle AV handle.CNcomment:AV ��� CNend
    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_SUPPORTED  not support for the moment.CNcomment:�ݲ�֧�֡�CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pre_stop_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /********************************* Extend Function Definition End ***************************/
#endif//HAL_HISI_EXTEND_H
} AV_DEVICE_S;

/**
\brief direct get av device api, for linux and android.CNcomment:��ȡav�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get av device api��for linux and andorid.
CNcomment:��ȡav�豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
\retval  av device pointer when success.CNcomment:�ɹ�����av�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::AV_DEVICE_S

\par example
*/
AV_DEVICE_S* getAVDevice();

/**
\brief  Open HAL AV play module device.CNcomment:��HAL������ģ���豸 CNend
\attention \n
Open HAL AV play module device(for compatible Android HAL).
CNcomment:��HAL������ģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice AV play device structure.CNcomment:�������豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::FAILURE error.CNcomment:�������� CNend
\see \n
::AV_DEVICE_S

\par example
*/
static inline S32 av_open(const struct hw_module_t* pstModule, AV_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, AV_HARDWARE_AV0,  (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getAVDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL AV play module device.CNcomment:�ر�HAL������ģ���豸 CNend
\attention \n
Close HAL AV play module device(for compatible Android HAL).
CNcomment:�ر�HAL������ģ���豸(Ϊ����Android HAL). CNend
\param[in] pstDevice AV device structure.CNcomment:AV�豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::AV_DEVICE_S

\par example
*/
static inline S32 av_close(AV_DEVICE_S* pstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstDevice->stCommon.close(&pstDevice->stCommon);
#else
    return SUCCESS;
#endif
}

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*__TVOS_HAL_AV_H__*/
