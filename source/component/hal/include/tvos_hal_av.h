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
/**CNcomment:定义AV 模块名称 */
#define AV_HARDWARE_MODULE_ID "audio_video"

/**Defines the av module name*/
/**CNcomment:定义AV 设备名称 */
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
/**CNcomment:定义解码状态
1.模块初始化后处于AV_DECODER_STATE_STOPPED 状态.
2.AV_DECODER_STATE_RUNNING 状态下,可以stop/start/pause/freeze
    AV_DECODER_STATE_RUNNING 状态下,如果没有调用stop接口,
    直接调用start接口.也会先stop,更新settings,再start,
    这样做是因为应用经常没有控制好状态,在start下调用start.
3.只有AV_DECODER_STATE_RUNNING 状态下才能PAUSE/FREEZE
4.AV_DECODER_STATE_FREEZING/AV_DECODER_STATE_PAUSING 状态下
    可以stop/resume/start
5.AV_DECODER_STATE_STOPPED 状态下只能start.*/
typedef enum _AV_DECODER_STATE_E
{
    AV_DECODER_STATE_RUNNING = 0,          /**<Playing*//**<CNcomment: 正在解码*/
    AV_DECODER_STATE_PAUSING,              /**<Pause*//**<CNcomment: 暂停解码, 实时流不能暂停*/
    AV_DECODER_STATE_FREEZING,             /**<Freeze picture, keep decoding, it means pause for real-time stream*//**<CNcomment: 解码,不显示,对于实时流可以使用这个代替暂停*/
    AV_DECODER_STATE_STOPPED,              /**<Stop*//**<CNcomment: 停止解码*/
    AV_DECODER_STATE_UNKNOWN,
    AV_DECODER_STATE_BUTT
} AV_DECODER_STATE_E;

/**Defines the recovery mode of video decode error, default is AV_ERROR_RECOVERY_MODE_HIGH after system init*/
/**CNcomment:视频解码错误恢复模式,系统初始化之后,默认AV_ERROR_RECOVERY_MODE_HIGH.*/
typedef enum _AV_ERROR_RECOVERY_MODE_E
{
    AV_ERROR_RECOVERY_MODE_NONE = 0,       /**<No correction, for debug*//**<CNcomment: 无纠错，调试用*/
    AV_ERROR_RECOVERY_MODE_PARTIAL,        /**<Part correction*//**<CNcomment: 部分纠错*/
    AV_ERROR_RECOVERY_MODE_HIGH,           /**<Part correction*//**<CNcomment: 部分纠错*/
    AV_ERROR_RECOVERY_MODE_FULL,           /**<All correction, for debug, discard any picture if has error*//**<CNcomment: 全纠错，调试用，有错误即丢弃*/
    AV_ERROR_RECOVERY_MODE_BUTT
} AV_ERROR_RECOVERY_MODE_E;

/**Defines of audio stream type.*/
/**CNcomment: 音频流类型*/
typedef enum _AV_AUD_STREAM_TYPE_E
{
    AV_AUD_STREAM_TYPE_MP2         = 0,        /**<MPEG audio layer 1, 2.*/ /**<CNcomment:MPEG音频第一层、第二层 */
    AV_AUD_STREAM_TYPE_MP3,                    /**<MPEG audio layer 1, 2, 3.*/ /**<CNcomment:MPEG音频第一层、第二层 、第三层*/
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
/**CNcomment: 视频流类型*/
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
/**CNcomment: 定义AV 事件*/
typedef enum _AV_EVT_E
{
    AV_EVT_BASE = 0,

    /*video event*/
    AV_VID_EVT_BASE         = AV_EVT_BASE,
    AV_VID_EVT_DECODE_START = AV_VID_EVT_BASE,          /**<Video decode start, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:视频解码开始，携带数据是AV_VID_STATUS_S*/
    AV_VID_EVT_DECODE_STOPPED,                          /**<Video decode stopped, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:视频解码停止，携带数据是AV_VID_STATUS_S*/
    AV_VID_EVT_NEW_PICTURE_DECODED,                     /**<New picture decoded, this event passes a (AV_VID_FRAMEINFO_S *) as parameter *//**<CNcomment:新画面解码完成，携带数据是AV_VID_FRAMEINFO_S*/
    AV_VID_EVT_DISCARD_FRAME,                           /**<Discard a video frame *//**<CNcomment:丢掉一帧视频帧*/
    AV_VID_EVT_PTS_ERROR,                               /**<Error pts of video frame *//**<CNcomment:视频pts出错*/
    AV_VID_EVT_UNDERFLOW,                               /**<Video stream underflow *//**<CNcomment:视频数据下溢*/

    AV_VID_EVT_ASPECT_RATIO_CHANGE,                     /**<Aspect ratio changed, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:视频宽高比发生了变化， 携带数据是AV_VID_STATUS_S*/

    AV_VID_EVT_STREAM_FORMAT_CHANGE,                    /**<Stream format changed, this event passes a (AV_FORMAT_CHANGE_PARAM_S *) as parameter *//**<CNcomment:视频流制式发生了变化， 携带数据是AV_FORMAT_CHANGE_PARAM_S*/

    AV_VID_EVT_OUT_OF_SYNC,                             /**<Synchronization lost, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:同步丢失，携带数据是AV_VID_STATUS_S*/
    AV_VID_EVT_BACK_TO_SYNC,                            /**<Synchronization resume, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:同步恢复，携带数据是AV_VID_STATUS_S*/

    AV_VID_EVT_DATA_OVERFLOW,                           /**<Video data overflow, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:视频数据溢出， 携带数据是AV_VID_STATUS_S*/
    AV_VID_EVT_DATA_UNDERFLOW,                          /**<Video data underflow, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:视频数据欠载， 携带数据是AV_VID_STATUS_S*/

    AV_VID_EVT_PICTURE_DECODING_ERROR,                  /**<Pictrue decode error, this event passes a (AV_VID_STATUS_S *) as parameter *//**<CNcomment:图像解码失败， 携带数据是AV_VID_STATUS_S*/
    AV_VID_EVT_CODEC_UNSUPPORT,
    AV_VID_EVT_FRAME_INFO,                              /**<Video frame infos, each decoded frame will be generated *//**<CNcomment:视频帧信息，携带帧信息，每个解码帧都会发生*/
    AV_VID_EVT_PEEK_FIRST_PTS,                          /**<Video first peek frame pts, this event passes a HI_U32 PTS as parameter *//**<CNcomment:视频显示第一帧peekframe画面的事件，携带数据是HI_U32 PTS*/
    AV_VID_EVT_FIRST_FRAME_DISPLAYED,                   /**<Video play first frame display event, no param *//**<CNcomment:视频执行播放命令后第一帧显示了的事件，无附加参数*/
    AV_VID_EVT_LASTFRMFLAG,                             /**<Report vdec last frame flag event *//**<CNcomment: 上报vdec最后一帧事件*/
    AV_VID_EVT_BUTT,

    /*audio event*/
    AV_AUD_EVT_BASE         = AV_VID_EVT_BUTT,
    AV_AUD_EVT_DECODE_START = AV_AUD_EVT_BASE,          /**<Audio decode start, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:音频解码开始 携带数据是AV_AUD_STATUS_S*/
    AV_AUD_EVT_DECODE_STOPPED,                          /**<Audio decode stopped, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:音频解码停止 携带数据是AV_AUD_STATUS_S*/
    AV_AUD_EVT_NEW_FRAME,                               /**<New audio frame decoded, this event passes a ( AV_AUD_FRAMEINFO_S*) as parameter *//**<CNcomment:新音频帧解码完成， 携带数据是AV_AUD_FRAMEINFO_S*/
    AV_AUD_EVT_DISCARD_FRAME,                           /**<Discard an audio frame *//**<CNcomment:丢掉一帧音频帧*/
    AV_AUD_EVT_PTS_ERROR,                               /**<Error pts of audio frame *//**<CNcomment:音频pts出错*/
    AV_AUD_EVT_UNDERFLOW,                               /**<Audio stream underflow *//**<CNcomment:音频数据下溢*/
    AV_AUD_EVT_DECODING_ERROR,                          /**<Audio decode error *//**<CNcomment:音频解码失败*/

    AV_AUD_EVT_PCM_UNDERFLOW,                           /**<PCM data undeflow, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:PCM数据欠载 携带数据是AV_AUD_STATUS_S*/
    AV_AUD_EVT_FIFO_OVERFLOW,                           /**<Audio data overflow, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:音频数据溢出 携带数据是AV_AUD_STATUS_S*/
    AV_AUD_EVT_LOW_DATA_LEVEL,                          /**<This event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment: 携带数据是AV_AUD_STATUS_S*/
    AV_AUD_EVT_OUT_OF_SYNC,                             /**<Synchronization lost,  this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:同步丢失， 携带数据是AV_AUD_STATUS_S*/
    AV_AUD_EVT_BACK_TO_SYNC,                            /**<Synchronization resume, this event passes a ( AV_AUD_STATUS_S*) as parameter *//**<CNcomment:同步恢复， 携带数据是AV_AUD_STATUS_S*/
    AV_AUD_EVT_CODEC_UNSUPPORT,                         /**<Not support this Codec *//**<CNcomment:解码格式不支持*/
    AV_AUD_EVT_BUTT,

    /*inject event*/
    AV_INJECT_EVT_BASE           = AV_AUD_EVT_BUTT,
    AV_INJECT_EVT_DATA_UNDERFLOW = AV_INJECT_EVT_BASE,  /**<Inject data underflow, this event passes a ( AV_INJECT_STATUS_S*) as parameter *//**<CNcomment:注入数据欠载， 携带数据是AV_INJECT_STATUS_S*/
    AV_INJECT_EVT_DATA_OVERFLOW,                        /**<Inject data overflow, this event passes a ( AV_INJECT_STATUS_S*) as parameter *//**<CNcomment:注入数据溢出， 携带数据是AV_INJECT_STATUS_S*/
    AV_INJECT_EVT_IMPOSSIBLE_WITH_MEM_PROFILE,          /**<Impossible with memery profile, this event passes a ( AV_INJECT_STATUS_S*) as parameter *//**<CNcomment:当前内存配置不支持， 携带数据是AV_INJECT_STATUS_S*/
    AV_INJECT_EVT_BUTT,

    AV_STREAM_EVT_PLAY_EOS,

    AV_EVT_BUTT
} AV_EVT_E;

/**Defines of stop mode when stop video, default is AV_VID_STOP_MODE_BLACK.*/
/**CNcomment: 定义视频停止模式，默认为黑屏*/
typedef enum _AV_VID_STOP_MODE_E
{
    AV_VID_STOP_MODE_FREEZE = 0,        /**<Freeze the last frame *//**<CNcomment: 静帧*/
    AV_VID_STOP_MODE_BLACK,             /**<Show black screen *//**<CNcomment: 黑屏*/
    AV_VID_STOP_MODE_BUTT
} AV_VID_STOP_MODE_E;

/**Defines of source type of AV data
The source of audio and video are different sometimes.
Because iframe or pcm data can be injected into decoder directly, such as:
Inject iframe data while playing audio data from tuner, or inject pcm data as audio while playing video from tuner or file.
*/
/**CNcomment: 节目数据来源类型
有时候audio & video的 类型是不同的.
原因是:iframe, pcm 等不用经过dmx直接进入decoder.
如:可以注入iframe的同时播放来自tuner的audio.
或者播放某个tuner或者file来源的video的同时注入pcm伴音.*/
typedef enum _AV_SOURCE_TYPE_E
{
    AV_SOURCE_TUNER = 1,               /**<Data comes from tuner *//**<CNcomment: 数据来自tuner*/
    AV_SOURCE_MEM   = 1 << 1           /**<Data comes from memery */ /**<CNcomment: 数据来自内存*/
} AV_SOURCE_TYPE_E;

// TODO: 为什么要IFRAME类型，IFRAME不也是ES吗?
/**Defines of the type of inject data.*/
/**CNcomment: 内存注入数据类型*/
typedef enum _AV_DATA_TYPE_E
{
    AV_DATA_TYPE_NONE   = 0,
    AV_DATA_TYPE_TS     = 1,          /**< mem ts, through demux*//**<CNcomment:TS格式数据, 必须经过dmx*/
    AV_DATA_TYPE_PES    = 1 << 1,     /**< mem PES */ /**<CNcomment:PES 格式数据*/
    AV_DATA_TYPE_ES     = 1 << 2,     /**< mem ES*/ /**<CNcomment:ES 格式数据*/
    AV_DATA_TYPE_PCM    = 1 << 3,     /**< mem PCM */ /**<CNcomment:PCM 格式数据*/
    AV_DATA_TYPE_IFRAME = 1 << 4      /**< mem IFRAME */ /**<CNcomment:Iframe 格式数据*/
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
/**CNcomment: 音视频同步模式
系统初始化之后, 默认是AV_SYNC_MODE_PCR, 各个模式的同步效果如下:
1. AV_SYNC_MODE_PCR:
    在同步区间和同步调整区间必须同步,且不能卡顿.
    在异常区间同步但可能有卡顿.
    在巨异常区间不同步,但是不能卡顿.
2. AV_SYNC_MODE_DISABLE:
    在所有区间可以不同步,但是不能卡顿.
3. AV_SYNC_MODE_AUTO:
    在同步区间和同步调整区间必须同步,且不能卡顿.
    同步异常区间和同步巨异常区间可以不同步,但是不能卡顿.
4. AV_SYNC_MODE_VID:
    如果没有视频PTS,效果如AV_SYNC_MODE_DISABLE,
    如果有视频PTS,效果如AV_SYNC_MODE_PCR.
5. AV_SYNC_MODE_AUD:
    如果没有音频PTS,效果如:AV_SYNC_MODE_DISABLE.
    如果有音频PTS,效果如AV_SYNC_MODE_PCR.*/
typedef enum _AV_SYNC_MODE_E
{
    AV_SYNC_MODE_DISABLE = 0,       /**<Free playing without synchronization*//**<CNcomment:关闭同步*/
    AV_SYNC_MODE_AUTO,              /**<Deal with synchronization mode and parameters auto*//**<CNcomment: 自己处理同步模式和同步参数*/
    AV_SYNC_MODE_PCR,               /**<Program Clock Reference (PCR)-based synchronization*//**<CNcomment:以PCR为为基准*/
    AV_SYNC_MODE_VID,               /**<Video-based synchronization*//**<CNcomment:视频PTS为时钟基准的同步模式*/
    AV_SYNC_MODE_AUD,               /**<Audio-based synchronization*/ /**<CNcomment:音频PTS为时钟基准的同步模式*/
    AV_SYNC_MODE_SCR,               /**<System-clock synchronization*/ /**<CNcomment:系统时钟基准的同步模式*/
    AV_SYNC_MODE_BUTT
} AV_SYNC_MODE_E;

/**Defines of the content type of inject data.*/
/**CNcomment: 内存注入数据内容的类型*/
typedef enum _AV_CONTENT_TYPE_E
{
    AV_CONTENT_DEFAULT = 0,         /**<Default type, such as TS data*//**<CNcomment: 缺省类型, 如ts数据 */
    AV_CONTENT_AUDIO,               /**<Audio data*//**<CNcomment: 音频数据 */
    AV_CONTENT_VIDEO,               /**<Video data*//**<CNcomment: 视频数据 */
    AV_CONTENT_BUTT
} AV_CONTENT_TYPE_E;

/**Defines of 3D format, default is AV_3D_FORMAT_OFF.*/
/**CNcomment: 定义3D 码流源格式, 默认AV_3D_FORMAT_OFF*/
typedef enum _AV_3D_FORMAT_E
{
    AV_3D_FORMAT_OFF = 0,
    AV_3D_FORMAT_SIDE_BY_SIDE,      /**<3d type:Side by side half*//**<CNcomment:3d 模式:并排式 左右半边*/
    AV_3D_FORMAT_TOP_AND_BOTTOM,    /**<3d type:Top and Bottom*//**<CNcomment:3d 模式:上下模式*/
    AV_3D_FORMAT_SIDE_BY_SIDE_FULL, /**<3d type:Side by side full*//**<CNcomment:3d 模式:并排式 左右全场*/
    AV_3D_FORMAT_FRAME_PACKING,     /**<3d type:Frame Packing*//**<CNcomment:3d 模式:帧封装*/
    AV_3D_FORMAT_FIELD_ALTERNATIVE, /**<3d type:Field alternative*//**<CNcomment:3d 模式:场交错*/
    AV_3D_FORMAT_LINE_ALTERNATIVE,  /**<3d type:Line alternative*//**<CNcomment:3d 模式:行交错*/
    AV_3D_FORMAT_AUTO,              /**<Depended on stream*//**<CNcomment: AUTO 需要驱动和流同时支持才行*/
    AV_3D_FORMAT_BUTT
} AV_3D_FORMAT_E;

/**defines the ROTATION type.*/
/**CNcomment:定义视频旋转角度*/
typedef enum _AV_VID_ROTATION_E
{
    AV_VID_ROTATION_0 = 0,          /**< 0 degree rotation*//**<CNcomment: 0度旋转*/
    AV_VID_ROTATION_90,             /**< 90 degree rotation*//**<CNcomment: 90度旋转*/
    AV_VID_ROTATION_180,            /**< 180 degree rotation*//**<CNcomment: 180度旋转*/
    AV_VID_ROTATION_270,            /**< 270 degree rotation*//**<CNcomment: 270度旋转*/
    AV_VID_ROTATION_BUTT
} AV_VID_ROTATION_E;

/**Defines the type of an input stream interface.*/
/**CNcomment:定义数据输入流接口类型 */
typedef enum _AV_STREAM_TYPE_E
{
    AV_STREAM_TYPE_TS = 0,     /**<Transport stream (TS)*//**<CNcomment:TS码流 */
    AV_STREAM_TYPE_ES,         /**<ES stream*//**<CNcomment:ES码流 */

    AV_STREAM_TYPE_BUTT
} AV_STREAM_TYPE_E;

/**Defines of video decode capability(Resolution)*/
/**CNcomment:解码器解码能力(分辨率)  */
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
/**CNcomment: 定义视频帧地址*/
typedef struct _AV_VID_FRAMEADDR_S
{
    U32             u32YAddr;      /**<Address of the Y component in the current frame*/ /**<CNcomment: 当前帧Y分量数据的地址*/
    U32             u32CAddr;      /**<Address of the C component in the current frame*/ /**<CNcomment: 当前帧C分量数据的地址*/
    U32             u32CrAddr;     /**<Address of the Cr component in the current frame*/ /**<CNcomment: 当前帧Cr分量数据的地址*/

    U32             u32YStride;    /**<Stride of the Y component*/ /**<CNcomment: Y分量数据的跨幅*/
    U32             u32CStride;    /**<Stride of the C component*/ /**<CNcomment: C分量数据的跨幅*/
    U32             u32CrStride;   /**<Stride of the Cr component*/ /**<CNcomment: Cr分量数据的跨幅*/
} AV_VID_FRAMEADDR_S;

/**Defines the video format.*/
/**CNcomment: 定义视频格式枚举*/
typedef enum _AV_VID_FORMAT_E
{
    AV_VID_FORMAT_YUV_SEMIPLANAR_422 = 0X10,       /**<The YUV spatial sampling format is 4:2:2.*/ /**<CNcomment: YUV空间采样格式为4:2:2*/
    AV_VID_FORMAT_YUV_SEMIPLANAR_420 = 0X11,       /**<The YUV spatial sampling format is 4:2:0.*/ /**<CNcomment: YUV空间采样格式为4:2:0*/
    AV_VID_FORMAT_YUV_PACKAGE_UYVY,                /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is UYVY.*/ /**<CNcomment: YUV空间采样格式为package,内存排列为UYVY*/
    AV_VID_FORMAT_YUV_PACKAGE_YUYV,                /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YUYV.*/ /**<CNcomment: YUV空间采样格式为package,内存排列为YUYV*/
    AV_VID_FORMAT_YUV_PACKAGE_YVYU,                /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YVYU.*/ /**<CNcomment: YUV空间采样格式为package,内存排列为YVYU*/
    AV_VID_FORMAT_YUV_BUTT
} AV_VID_FORMAT_E;

/**Defines the video frame/field mode.*/
/**CNcomment: 定义视频帧场模式枚举*/
typedef enum _AV_VID_FIELD_MODE_E
{
    AV_VID_FIELD_ALL = 0,            /**<Frame mode*/ /**<CNcomment: 帧模式*/
    AV_VID_FIELD_TOP,                /**<Top field mode*/ /**<CNcomment: 顶场模式*/
    AV_VID_FIELD_BOTTOM,             /**<Bottom field mode*/ /**<CNcomment: 底场模式*/
    AV_VID_FIELD_BUTT
} AV_VID_FIELD_MODE_E;

/**Defines the information about video frames.*/
/**CNcomment: 定义视频帧信息结构*/
typedef struct _AV_VID_FRAMEINFO_S
{
    U32                              u32FrameIndex;         /**<Frame index ID of a video sequence*/ /**<CNcomment: 视频序列中的帧索引号*/
    AV_VID_FORMAT_E                  enVideoFormat;         /**<Video YUV format*/ /**<CNcomment: 视频YUV格式*/
    AV_VID_FRAMEADDR_S               stVideoFrameAddr[2];   /**<Fame buffer addr, parameter 0 is left picture, 1 is right picture */
    U32                              u32Width;              /**<Width of the source picture*/ /**<CNcomment: 原始图像宽*/
    U32                              u32Height;             /**<Height of the source picture*/ /**<CNcomment: 原始图像高*/
    S64                              s64SrcPts;             /**<Original PTS of a video frame*/ /**<CNcomment: 视频帧的原始时间戳*/
    S64                              s64Pts;                /**<PTS of a video frame*/ /**<CNcomment: 视频帧的时间戳*/
    U32                              u32AspectWidth;
    U32                              u32AspectHeight;
    U32                              u32fpsInteger;         /**<Integral part of the frame rate (in frame/s)*/ /**<CNcomment: 码流的帧率的整数部分, fps */
    U32                              u32fpsDecimal;         /**<Fractional part (calculated to three decimal places) of the frame rate (in frame/s)*//**<CNcomment: 码流的帧率的小数部分（保留3位）, fps */

    BOOL                             bProgressive;          /**<Sampling type (progressive or interlaced)*/ /**<CNcomment: 采样方式(逐行/隔行) */
    AV_VID_FIELD_MODE_E              enFieldMode;           /**<Frame or field encoding mode*/ /**<CNcomment: 帧或场编码模式*/
    BOOL                             bTopFieldFirst;        /**<Top field first flag*/ /**<CNcomment: 顶场优先标志*/
    AV_3D_FORMAT_E                   enFramePackingType;    /**<3D frame packing type*/
    U32                              u32Circumrotate;       /**<Need circumrotate, 1 need */
    BOOL                             bVerticalMirror;
    BOOL                             bHorizontalMirror;
    U32                              u32DisplayWidth;       /**<Width of the displayed picture*/ /**<CNcomment: 显示图像宽*/
    U32                              u32DisplayHeight;      /**<Height of the displayed picture*/ /**<CNcomment: 显示图像高*/
    U32                              u32DisplayCenterX;     /**<Horizontal coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: 显示中心x坐标，原始图像左上角为坐标原点*/
    U32                              u32DisplayCenterY;     /**<Vertical coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: 显示中心y坐标，原始图像左上角为坐标原点*/
    U32                              u32ErrorLevel;         /**<Error percentage of a decoded picture, ranging from 0% to 100%*/ /**<CNcomment: 一幅解码图像中的错误比例，取值为0～100*/
    U32                              u32Private[64];        /**<Save private info,indicate the frame is stored in security buffer */
} AV_VID_FRAMEINFO_S;

/**Defines the information about audio frames.*/
/**CNcomment: 定义音频帧信息结构*/
typedef struct _AV_AUD_FRAMEINFO_S
{
    /** s32BitPerSample: (PCM) Data depth, and format of storing the output data
          If the data depth is 16 bits, 16-bit word memory is used.
          If the data depth is greater than 16 bits, 32-bit word memory is used, and data is stored as left-aligned data. That is, the valid data is at upper bits.
     */
    /**CNcomment: s32BitPerSample: (PCM) 数据位宽设置. 输出存放格式
          等于16bit:   占用16bit word内存
          大于16bit:   占用32bit word内存, 数据左对齐方式存放(有效数据在高位)
     */
    S32  s32BitPerSample;          /**<Data depth*/ /**<CNcomment: 数据位宽*/
    BOOL bInterleaved;             /**<Whether the data is interleaved*/ /**<CNcomment: 数据是否交织*/
    U32  u32SampleRate;            /**<Sampling rate*/ /**<CNcomment: 采样率*/
    U32  u32Channels;              /**<Number of channels*/ /**<CNcomment: 通道数量*/
    S64  s64PtsMs;                 /**<Presentation time stamp (PTS)*/ /**<CNcomment: 时间戳*/
    S32* ps32PcmBuffer;            /**<Pointer to the buffer for storing the pulse code modulation (PCM) data*/ /**<CNcomment: PCM数据缓冲指针*/
    S32* ps32BitsBuffer;           /**<Pointer to the buffer for storing the stream data*/ /**<CNcomment: 码流数据缓冲指针*/
    U32  u32PcmSamplesPerFrame;    /**<Number of sampling points of the PCM data*/ /**<CNcomment: PCM数据采样点数量*/
    U32  u32BitsBytesPerFrame;     /**<IEC61937 data size*/ /**<CNcomment: IEC61937数据长度*/
    U32  u32FrameIndex;            /**<Frame ID*/ /**<CNcomment: 帧序号 */
    U32  u32IEC61937DataType;      /**<IEC61937 Data Type*/ /**<CNcomment: IEC61937数据类型标识，低8bit为IEC数据类型 */
} AV_AUD_FRAMEINFO_S;


#ifdef HAL_HISI_EXTEND_H
/********************************* Extend Emum and Structure Definition Before ***************************/
/**Defines the type of the video frame.*/
/**CNcomment: 定义视频帧的类型枚举*/
typedef enum _AV_VID_FRAME_TYPE_E
{
    AV_VID_FRAME_TYPE_UNKNOWN,   /**<Unknown*/ /**<CNcomment: 未知的帧类型*/
    AV_VID_FRAME_TYPE_I,         /**<I frame*/ /**<CNcomment: I帧*/
    AV_VID_FRAME_TYPE_P,         /**<P frame*/ /**<CNcomment: P帧*/
    AV_VID_FRAME_TYPE_B,         /**<B frame*/ /**<CNcomment: B帧*/
    AV_VID_FRAME_TYPE_IDR,       /**<IDR frame*/ /**<CNcomment: IDR帧*/
    AV_VID_FRAME_TYPE_BUTT
} AV_VID_FRAME_TYPE_E;

/**Defines the parameters of video frame info */
/**CNcomment: 定义视频帧信息的相关参数*/
typedef struct _AV_UVMOS_FRAMEINFO_S
{
    AV_VID_FRAME_TYPE_E enVidFrmType; /**<Type of video frame*/ /**<CNcomment: 视频帧类型*/
    U32 u32VidFrmStreamSize;             /**<Size of video frame*/ /**<CNcomment: 视频帧大小*/
    U32 u32VidFrmQP;                     /**<QP of video frame*/ /**<CNcomment: 视频帧QP*/
    U32 u32VidFrmPTS;                    /**<PTS of video frame*/ /**<CNcomment: 视频帧pts*/
    U32 u32MaxMV;                        /**<MAX MV*/ /**<CNcomment: 视频帧最大MV*/
    U32 u32MinMV;                        /**<MIN MV*/ /**<CNcomment: 视频帧最小MV*/
    U32 u32AvgMV;                        /**<AVG MV*/ /**<CNcomment: 视频帧MV平均值*/
    U32 u32SkipRatio;                    /**<MB ratio */ /**<CNcomment: 视频帧MB比例0~100*/
} AV_UVMOS_FRAMEINFO_S;

/**Defines the mode of the video decoder.*/
/**CNcomment: 定义视频解码器模式枚举*/
typedef enum _AV_VDEC_MODE_E
{
    AV_VDEC_MODE_NORMAL = 0,        /**<Decode all frames.*/ /**<CNcomment: 解所有帧*/
    AV_VDEC_MODE_IP,                /**<Decode only I frames and P frames.*/ /**<CNcomment: 只解IP帧*/
    AV_VDEC_MODE_I,                 /**<Decode only I frames.*/ /**<CNcomment: 只解I帧*/
    AV_VDEC_MODE_DROP_INVALID_B,    /**<Decode all frames except the first B frame sequence behind I frames */ /**<CNcomment: 解所有帧，除了紧跟着I帧后面的B帧*/
    AV_VDEC_MODE_BUTT
} AV_VDEC_MODE_E;

/**Defines the source of frame rate.*/
/**CNcomment: 定义帧率来源类型的枚举 */
typedef enum hiAV_VDEC_FRMRATE_TYPE_E
{
    AV_VDEC_FRMRATE_TYPE_PTS,         /**<Use the frame rate calculates from PTS*//**<CNcomment: 采用PTS计算帧率 */
    AV_VDEC_FRMRATE_TYPE_STREAM,      /**<Use the frame rate comes from stream*//**<CNcomment: 采用码流信息中的帧率 */
    AV_VDEC_FRMRATE_TYPE_USER,        /**<Use the frame rate set by user*//**<CNcomment: 采用用户设置的帧率 */
    AV_VDEC_FRMRATE_TYPE_USER_PTS,    /**<Use the frame rate set by user until the 2nd I frame comes, then use the frame rate calculates from PTS*//**<CNcomment: 第二个I帧来之前采用用户设置的帧率，之后根据PTS计算帧率 */
    AV_VDEC_FRMRATE_TYPE_BUTT
} AV_VDEC_FRMRATE_TYPE_E;

typedef struct _AV_VDEC_FRAMERATE_PARAM_S
{
    U32                     u32Fps;          /**<Frames per second*//**<CNcomment: 帧率(x1000) ,实际帧率乘1000, 0表示不关注*/
    AV_VDEC_FRMRATE_TYPE_E  enFrmRateType;   /**<The source of frame rate*//**<CNcomment: 帧率来源类型 */
} AV_VDEC_FRAMERATE_PARAM_S;


/**Defines the stream type of HDR.*/
/**CNcomment: 定义DOLBY HDR码流类型 */
typedef enum _AV_HDR_STREAM_TYPE_E
{
    AV_HDR_STREAM_TYPE_NONE = 0,
    AV_HDR_STREAM_TYPE_DL_SINGLE_VES,    /**<Dolby Vision Dual layer Single VES Format *//**<CNcomment:  单流双层格式.*/
    AV_HDR_STREAM_TYPE_DL_DUAL_VES,          /**<Dolby Vision Dual Layer Dual VES Format *//**<CNcomment:  双流双层格式.*/
    AV_HDR_STREAM_TYPE_SL_VES,               /**<Dolby Vision Single Layer VES Format *//**<CNcomment:  单流单层格式.*/
    AV_HDR_STREAM_TYPE_BUTT
} AV_HDR_STREAM_TYPE_E;
/**Defines special control operation of decoder*/
/**CNcomment: 定义解码器解码的特殊控制选项 */
typedef enum _AV_VDEC_CTRL_OPTION_E
{
    AV_VDEC_CTRL_OPTION_SIMPLE_DPB = 0x1,
} AV_VDEC_CTRL_OPTION_E;

/**Defines the bit width of the output*/
/**CNcomment: 定义输出的位宽*/
typedef enum _AV_PIXEL_BITWIDTH_E
{
    AV_PIXEL_BITWIDTH_8BIT = 0,
    AV_PIXEL_BITWIDTH_10BIT,
    AV_PIXEL_BITWIDTH_12BIT,
    AV_PIXEL_BITWIDTH_AUTO,
    AV_PIXEL_BITWIDTH_BUTT,
} AV_PIXEL_BITWIDTH_E;

/**AV invoke CODEC AV_CODEC_SET_CMD_FRAMEENDFLAG param.*/
/**CNcomment: AV invoke接口AV_CODEC_SET_CMD_FRAMEENDFLAG带的附加参数*/
typedef struct _AV_VCODEC_FRAMEENDCMD_PARAM_S
{
    HANDLE hInjecter;             /**<AV inject handler *//**<CNcomment: AV inject句柄 */
    BOOL   bFrameEndFlag;   /**<frame end flag, true means end *//**<CNcomment: 帧结束标志, true表示帧结束 */
} AV_VCODEC_FRAMEENDCMD_PARAM_S;

/*Struct of set start render position.*/
/*CNcomment: 设置渲染起始位置的结构体*/
typedef struct _AV_INVOKE_SET_START_RENDER_POS_S
{
    S64     s64Pts;                 /**<the position to start rendering from*/ /**<CNcomment:起始渲染位置的pts*/
    S64     s64IdrPts;              /**<the closest IDR at or before pts*/ /**<CNcomment:位于起始pts之前或等于起始pts的idr帧的pts*/
    BOOL    bPeekFrame;             /**<render the given frame in either pause state or not*/ /**<CNcomment:暂停状态是否渲染指定的pts帧*/
} AV_INVOKE_SET_START_RENDER_POS_S;

/*Struct of attribute for set video buffer pool.*/
/*CNcomment: 设置视频缓冲池的属性*/
typedef struct _AV_INVOKE_VBPOOL_ATTR
{
    BOOL bTvp;                      /** video security flag */ /**<CNcomment: 视频安全标志*/
    U32 u32FrameCount;              /** video buffer count */ /**<CNcomment: 缓存池个数*/
    U32 u32FrameWidth;              /** video width */ /**<CNcomment: 视频宽*/
    U32 u32FrameHeight;             /** video height */ /**<CNcomment: 视频高*/
} AV_INVOKE_VBPOOL_ATTR;

/*Struct of set video buffer pool.*/
/*CNcomment: 设置视频缓冲池的结构体*/
typedef struct _AV_INVOKE_SET_VIDEO_BUFFER_POOL_S
{
    BOOL bEnable;                   /** video buffer pool enable flag */ /**<CNcomment: 视频缓冲池使能标志*/
    AV_INVOKE_VBPOOL_ATTR* pstAttr; /** the attribute of video buffer pool */ /**<CNcomment: 视频缓冲池的属性*/
} AV_INVOKE_SET_VIDEO_BUFFER_POOL_S;

/**AV invoke CODEC AV_CODEC_GET_CMD_RAWCHANNEL param.*/
/**CNcomment: AV invoke接口AV_CODEC_GET_CMD_RAWCHANNEL带的附加参数*/
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
/**CNcomment: 定义dts解码配置*/
typedef struct _AV_AUD_DTSDEC_CFG_S
{
    S32  s32DtsDrcMode;
} AV_AUD_DTSDEC_CFG_S;

/**Defines the parameters of vdec configuration Attributes */
/**CNcomment: 定义视频解码器配置属性*/
typedef struct _AV_VDEC_CFG_S
{
    AV_VID_FORMAT_E         enOutFormat;      /**<Vdec output Video YUV format*/ /**<CNcomment: 解码器输出视频YUV格式*/
    AV_PIXEL_BITWIDTH_E     enBitWidth;       /**<the bit width of the output*/ /**<CNcomment: 输出的位宽*/
} AV_VDEC_CFG_S;

/** Define Setting parameter of ad enable and ad balance
    -bEnable:    AD on/off
                 - HI_TRUE:  AD is turned on
                 - HI_FALSE: AD is turned off
    -s32Balance: User defined balance between main and associated signal
                 Value range is between -32 and +32 (in dB)
                 -32dB indicates main only (mute associated)
                 +32dB indicates associated only (mute main) */
/**CNcomment: 定义AD配置属性*/
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
/**CNcomment: 定义MS解码模式*/
typedef enum
{
    AV_AUD_MS_DECODE_MODE_SS_SD    = 0, /**< single stream, single decode */
    AV_AUD_MS_DECODE_MODE_DD_SI    = 1, /**< single stream, dual decode, single instance */
    AV_AUD_MS_DECODE_MODE_SS_DD_DI = 2, /**< single stream, dual decode, dual instance */
    AV_AUD_MS_DECODE_MODE_DS_DD    = 3, /**< dual stream, dual decode */
} AV_AUD_MS_DECODE_MODE_E;

/** Preferred associated type for decoding by the user*/
/**CNcomment: 定义偏好的辅路解码类型*/
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

/**CNcomment: 设置session的结构体*/
typedef struct _AV_INVOKE_SET_SESSION_S
{
    BOOL    bSessionEnable;             /**<whether enable session or not*/ /**<CNcomment:是否设置session */
    U32     u32SessionID;               /**<session ID, available if bSessionEnable equal TRUE*/ /**<CNcomment:session ID, 在bSessionEnable==TRUE时有效 */
} AV_INVOKE_SET_SESSION_S;

/**Defines the set command of codec*/
/**CNcomment:定义编解码器的设置命令*/
typedef enum _AV_CODEC_SET_CMD_E
{
    // VCODEC Command
    AV_CODEC_SET_CMD_DPBFULL = 0,           /**VCODEC Command to set dpb full control, Additional parameters is BOOL*/
                                            /**CNcomment:VCODEC命令，设置dpb满的时候的处理策略, 参数对应类型为BOOL*/
    AV_CODEC_SET_CMD_SOURCE,                /**VCODEC Command to set source type, Additional parameters is BOOL*/
                                            /**<CNcomment: VCODEC命令,设置源类型,参数对应类型为BOOL*/
    AV_CODEC_SET_CMD_FRAMEENDFLAG,          /**VCODEC Command to inject send data frame end flag, for first frame display instand,  Additional parameters is AV_VCODEC_FRAMEENDCMD_PARAM_S */
                                            /**<CNcomment: VCODEC命令, inject送数据时，帧结束标志，表示一帧的数据剩下最后一包就送完了，由于首帧提前显示的场景，附加参数为AV_VCODEC_FRAMEENDCMD_PARAM_S类型.*/
    AV_CODEC_SET_CMD_OUTFORMAT,             /**VCODEC Command to set output format, Additional parameters is AV_VID_FORMAT_E*/
                                            /**<CNcomment: VCODEC命令,设置视频解码输出类型，对应设置的附加参数类型是AV_VID_FORMAT_E */
    AV_CODEC_SET_CMD_PROGRESSIVE,           /**VCODEC Command to set prigressive,parameters is BOOL*/
                                            /**<CNcomment:VCODEC命令,设置强制逐行功能。true：打开,false：关闭 */
    AV_CODEC_SET_CMD_VDECCFG,               /**VCODEC Command to set vdec configuration, Additional parameters is AV_VDEC_CFG_S*/
                                            /**<CNcomment: VCODEC命令,设置视频解码器配置属性，对应设置的附加参数类型是AV_VDEC_CFG_S */
    AV_CODEC_GET_CMD_VDECCFG,               /**VCODEC Command to get vdec configuration, Additional parameters is AV_VDEC_CFG_S*/
                                            /**<CNcomment: VCODEC命令,获取视频解码器配置属性，对应设置的附加参数类型是AV_VDEC_CFG_S */
    // ACODEC Command
    AV_CODEC_GET_CMD_RAWCHANNEL = 100,      /**ACODEC Command to get raw channel mode, parameters is AV_ACODEC_RAWCHANNEL_MODE*/
                                            /**<CNcomment: ACODEC命令，获取RAW通道类型，对应参数类型是AV_ACODEC_RAWCHANNEL_MODE */
    AV_ACODEC_SET_DTSDRC_CMD,               /**ACODEC Command to set DTS DRC mode, Additional parameters is AV_AUD_DTSDEC_CFG_S*/
                                            /**<CNcomment: ACODEC命令，设置DTS音频的DRC模式，对应的附加参数类型是AV_AUD_DTSDEC_CFG_S */
    AV_ACODEC_SET_AD_CONFIG_CMD,            /**ACODEC Command to set audio description config, parameters is AV_AUD_AD_CFG_S*/
                                            /**<CNcomment: ACODEC命令，设置AD属性，对应参数类型是AV_AUD_AD_CFG_S*/
    AV_ACODEC_SET_MS_DECODE_MODE_CMD,       /**ACODEC Command to set MS decode mode, parameters is AV_AUD_MS_DECODE_MODE_E*/
                                            /**<CNcomment: ACODEC命令，设置MS解码模式，对应参数类型是AV_AUD_MS_DECODE_MODE_E*/
    AV_ACODEC_SET_AC4_PRESENTATION_CMD,     /**ACODEC Command to set ac4 presentation, parameters is AV_AUD_AC4_PRESENTATION_S*/
                                            /**<CNcomment: ACODEC命令，设置语言，对应参数类型是AV_AUD_AC4_PRESENTATION_S*/

    AV_CODEC_SET_CMD_BUTT
}AV_CODEC_SET_CMD_E;

/**Struct of audio and video codec commands.*/
/**CNcomment: 音视频编解码器控制命令*/
typedef struct _AV_VCODEC_CMD_S
{
    U32  u32CmdIdx;                         /**<Command Index, see AV_CODEC_SET_CMD_E*//**<CNcomment: 命令Index, 参见AV_CODEC_SET_CMD_E*/
    VOID *pParam;                           /**<Control parameter, see AV_CODEC_SET_CMD_E*//**<CNcomment: 命令携带参数,参见AV_CODEC_SET_CMD_E*/
} AV_VCODEC_CMD_S;

/**Defines the type of AV invoke.*/
/**CNcomment: 定义AV Invoke调用类型的枚举 */
typedef enum _AV_INVOKE_E
{
    AV_INVOKE_ACODEC = 0x0,                  /**<Invoke command to control audio codec, additional param is AV_VCODEC_CMD_S*//**<CNcomment: 控制音频解码器的Invoke调用,附加的参数结构是AV_VCODEC_CMD_S */
    AV_INVOKE_VCODEC,                        /**<Invoke command to control video codec, additional param is AV_VCODEC_CMD_S*//**<CNcomment: 控制视频解码器的Invoke调用,附加的参数结构是AV_VCODEC_CMD_S */
    AV_INVOKE_SET_START_RENDER_POS,          /**<Invoke command to set start render position, additional param structure is AV_INVOKE_SET_START_RENDER_POS_S */
                                             /**<CNcomment: 设置视频渲染的起始位置, 附加的参数结构是AV_INVOKE_SET_START_RENDER_POS_S*/
    AV_INVOKE_SET_VID_LASTFRMFLAG,           /**<Invoke command to vdec for last frame flag*//**<CNcomment: 设置VDEC最后一帧标志*/
    AV_INVOKE_SET_MULTIAUD,                  /**<Invoke command to set multi audio, additional param structure is AV_INVOKE_SET_MULTI_AUD_S */
                                             /**<CNcomment: 设置多音频, 附加的参数结构是AV_INVOKE_SET_MULTI_AUD_S*/
    AV_INVOKE_REG_CALLBACK,                  /**<Invoke command to register av callback*//**<CNcomment: 注册av对外部依赖的回调接口 */
    AV_INVOKE_SET_SESSION,                   /**<Invoke command to set session, additional param structure is AV_INVOKE_SET_SESSION_S */
                                             /**<CNcomment: 设置session, 附加的参数结构是AV_INVOKE_SET_SESSION_S*/
    AV_INVOKE_SET_VIDEO_BUFFER_POOL,         /**<Invoke command to set video buffer pool, additional param structure is AV_INVOKE_SET_VIDEO_BUFFER_POOL_S*/
                                             /**<CNcomment: 设置视频缓冲池, 附加的参数结构体是AV_INVOKE_SET_VIDEO_BUFFER_POOL_S*/
    AV_INVOKE_BUTT
} AV_INVOKE_E;

/**Defines the type of inject free buffer.*/
/**CNcomment: 定义注入缓冲区类型的枚举 */
typedef enum _AV_INJECT_BUF_TYPE_E
{
    AV_INJECT_BUF_TYPE_COMMON = 0x0,    /**<AV inject common buffer*//**<CNcomment: 普通缓冲区 */
    AV_INJECT_BUF_TYPE_HDR_BL,          /**<AV inject HDR BL buffer*//**<CNcomment: HDR BL缓冲区 */
    AV_INJECT_BUF_TYPE_HDR_EL,          /**<AV inject HDR EL buffer*//**<CNcomment: HDR EL缓冲区 */
    AV_BUFFER_TYPE_BUTT
} AV_INJECT_BUF_TYPE_E;

/**Defines the type of audio volume curve.*/
/**CNcomment: 定义音频音量曲线类型的枚举*/
typedef enum _AV_VOLUME_CURVE_E
{
    AV_VOLUME_CURVE_LINEAR,             /**<Linear curve, up:g(x)=x, down:f(x) = 1-x*/ /**<CNcomment:线性音量曲线*/
    AV_VOLUME_CURVE_INCUBE,             /**<In cube,up:g(x) = x^3, down:f(x)=1-x^3 */ /**<CNcomment:Cubic-in曲线类型*/
    AV_VOLUME_CURVE_OUTCUBE,            /**<Out cube,up:g(x) = 1-(1-x)^3, down:f(x)=(1-x)^3 */ /**<CNcomment:Cubic-out曲线类型*/
    AV_VOLUME_CURVE_BUTT,
} AV_VOLUME_CURVE_E;


/**Struct of audio volume command.*/
/**CNcomment: 音频音量设置命令*/
typedef struct _AV_AUDIO_VOLUME_CMD_S
{
    U32  enCmd;                         /**<set volume cmd */ /**<CNcomment:音量设置命令*/
    AV_VOLUME_CURVE_E enVolumeCurve;    /**<Volume curve*/ /**<CNcomment:音量曲线类型*/
    U32  u32IntVolume;                  /**<Target Int attenuation(range:0 - 100)*/ /**<CNcomment:音量值,整数部分，从0到100*/
    U32  u32DecVolume;                  /**<Target Dec attenuation(range:0 - 100)*/ /**<CNcomment:音量值,小数部分，从0到100*/
    U32  u32FadeTime;                   /**<Duration of ramp in milliseconds(range:0-60000)*/ /**<CNcomment:音量调节生效时间0-60000毫秒*/
} AV_AUDIO_VOLUME_CMD_S;

/**Defines the dolby decoder config.*/
/**CNcomment: 定义dolby解码配置*/
typedef struct _AV_AUD_DOLBYDEC_CFG_S
{
    S32  s32DoblyRange;
    S32  s32DolbyDrcMode;
} AV_AUD_DOLBYDEC_CFG_S;

/** Dolby format external information */
/** CNcomment:杜比格式的详细信息 */
typedef struct _AV_AUD_DOLBY_INFO_S
{
    U32 u32DecoderType;      /**<Audio Decoder type *//**< CNcomment:解码器ID */
    S32 s32StreamType;       /**<dolby type 0:dolby 1:dolby plus *//**< CNcomment:杜比格式类型参见DOLBYPLUS_STREAM_INFO_S */
    S32 s32ACMode;           /**<dolby ac mode *//**< CNcomment:参见DOLBYPLUS_STREAM_INFO_S */
} AV_AUD_DOLBY_INFO_S;

/** DTS format external information */
/** CNcomment:DTS格式的详细信息 */
typedef struct _AV_AUD_DTS_INFO_S
{
    U32 u32DecoderType;      /**<Audio Decoder type *//**< CNcomment:解码器ID */
    U32 u32StreamType;       /**< CNcomment:DTSM6格式类型参见DTSM6_STREAM_INFO_S */
    U32 u32DecInfo;          /**< CNcomment:DTSM6格式类型参见DTSM6_STREAM_INFO_S */
} AV_AUD_DTS_INFO_S;

/** struct of HDR param */
/** CNcomment:HDR参数 */
typedef struct _AV_HDR_PARAM_S
{
    BOOL                    bEnable;    /**<Is Dolby HDR enable or not.*//**<CNcomment: 杜比 HDR是否使能.*/
    BOOL                    bCompatible;/**<Dolby frame is compatible or not.*/ /**<CNcomment: 杜比帧是否兼容.*/
    AV_HDR_STREAM_TYPE_E    enHdrType;  /**< Dolby Vision VES Format.*//**<CNcomment:. 杜比 HDR流类型.*/
    AV_VID_STREAM_TYPE_E    enElType;   /**<Video encoding type*/ /**<CNcomment: EL视频编码类型*/
} AV_HDR_PARAM_S;

/**Defines the attribute of low delay.*/
/**CNcomment: 定义低延时属性结构体*/
typedef struct _AV_LOW_DELAY_S
{
    BOOL  bEnable;  /**<Is low delay enable or not*//**<CNcomment: 低延时是否使能*/
} AV_LOW_DELAY_S;


/**Defines the parameters of sync refence */
/**CNcomment: 定义同步参考信息*/
typedef struct _AV_SYNC_REF_S
{
    S64         s64SrcPts;          /**<srouce pts*/ /**<CNcomment: 源pts*/
    S64         s64Pts;             /**<current PTS of the decoder *//**<CNcomment: 当前解码器使用的PTS*/
    U32         u32FpsInteger;      /**<Integer part of the frame rate *//**<CNcomment: 帧率的整数部分*/
    U32         u32FpsDecimal;      /**<Decimal part of the frame rate *//**<CNcomment: 帧率的小数部分*/
    U32         u32DelayTime;       /**<delay time*/ /**<CNcomment: 延迟时间*/
    U32         u32FreshRate;       /**<refresh rate*/ /**<CNcomment: 刷新率*/
    BOOL        bFreeRun;           /**<free run flag*/ /**<CNcomment: 自由播放标示*/
    BOOL        bProgressive;       /**<Sampling type (progressive or interlaced)*/ /**<CNcomment: 采样方式(逐行/隔行) */
} AV_SYNC_REF_S;

/**Defines the parameters of sync type */
/**CNcomment: 定义同步处理类型*/
typedef enum _AV_SYNC_PROC_E
{
    AV_SYNC_PROC_DISCARD = 0,   /**<discard frame*/ /**<CNcomment: 丢弃当前帧*/
    AV_SYNC_PROC_REPEAT,        /**<repeat frame*/ /**<CNcomment: 重复显示帧*/
    AV_SYNC_PROC_PLAY,          /**<play frame*/ /**<CNcomment: 播放当前帧*/
    AV_SYNC_PROC_QUICKOUTPUT,   /**<quick output frame*/ /**<CNcomment: 快速输出当前帧*/
    AV_SYNC_PROC_TPLAY,         /**<tplay frame*/ /**<CNcomment: 倍数播放当前帧*/
    AV_SYNC_PROC_CONTINUE,      /**<continue proc frame*/ /**<CNcomment: 继续处理当前帧*/
    AV_SYNC_PROC_BUTT
} AV_SYNC_PROC_E;

/**Defines the parameters of sync process */
/**CNcomment: 定义同步处理信息*/
typedef struct _AV_SYNC_INFO_S
{
    AV_SYNC_PROC_E      enSyncProc;     /**<sync process type*/ /**<CNcomment: 同步处理类型*/
    U32                 u32RepeatTime;  /**<repeate time*/ /**<CNcomment: 重复显示的时间*/
    U32                 u32DispCount;   /**<display counter*/ /**<CNcomment: 显示次数*/
} AV_SYNC_INFO_S;

/**Defines the type of buffer alloc method */
/**CNcomment: 定义视频解码器分配缓存的方式*/
typedef enum _AV_FRAME_BUFFER_MODE_E
{
    AV_VID_FRAME_BUF_ALLOC_BY_SELF = 0, /**<alloc by self*/ /**<CNcomment: 视频解码器自身分配缓存*/
    AV_VID_FRAME_BUF_ALLOC_BY_USER,     /**<alloc by user*/ /**<CNcomment: 用户分配缓存*/
    AV_VID_FRAME_BUF_BUTT
} AV_FRAME_BUFFER_MODE_E;

/**Defines the parameters of user buffer */
/**CNcomment: 定义用户缓存的信息*/
typedef struct _AV_USER_BUFFER_S
{
    U32  u32Stride;             /**<buffer stride*/ /**<CNcomment: 缓存步幅*/
    BOOL bVideoBypass;          /**<video bypass flag*/ /**<CNcomment: 视频是否透传*/
    U32  u32FrameBufSize;       /**<frame buffer size*/ /**<CNcomment: 帧缓存大小*/
    U32  u32FrameBuf;           /**<frame buffer*/ /**<CNcomment: 帧缓存*/
    S32  s32FrameBufFd;         /**<frame buffer handle*/ /**<CNcomment: 帧缓存句柄*/
    U32  u32MetadataBufSize;    /**<metadata buffer size*/ /**<CNcomment: 元数据缓存大小*/
    U32  u32MetadataBuf;        /**<metadata buffer*/ /**<CNcomment: 元数据缓存地址*/
    U32  u32PrivMetadataOffset; /**<private medata offerset*/ /**<CNcomment: 私有元数据偏移量*/
    S32  s32MetadataBufFd;      /**<metadata buffer handle*/ /**<CNcomment: 元数据缓存句柄*/
} AV_USER_BUFFER_S;

/**Defines HDR mastering display Info  */
/**CNcomment: 定义HDR10 mastering display数据信息*/
typedef struct _AV_VIDEO_MASTERING_DISPLAY_COLOUR_VOLUME_S
{
    U16 u16DisplayPrimaries_x[3];           /**<[0]:Red X chromaticity coordinate; [1]:Green X chromaticity coordinate; [2]:Blue X chromaticity coordinate. Values from range [0, 50000].*/ /**<CNcomment: 数组中的三个元素分别表示X坐标方向上的R,G,B色度值. 取值范围[0,50000].*/
    U16 u16DisplayPrimaries_y[3];           /**<[0]:Red Y chromaticity coordinate; [1]:Green Y chromaticity coordinate; [2]:Blue Y chromaticity coordinate. Values from range [0, 50000].*/ /**<CNcomment: 数组中的三个元素分别表示Y坐标方向上的R,G,B色度值. 取值范围[0,50000].*/
    U16 u16WhitePoint_x;                    /**<White point X chromaticity coordinate,  Values from range [0, 50000].*/ /**<CNcomment: X坐标方向上的white point色度值, 取值范围[0,50000].*/
    U16 u16WhitePoint_y;                    /**<White point Y chromaticity coordinate,  Values from range [0, 50000].*/ /**<CNcomment: Y坐标方向上的white point色度值, 取值范围[0,50000].*/
    U32 u32MaxDisplayMasteringLuminance;    /**<Maximum luminance, Represented in candelas per square meter. Values from range [0, 10000].*/ /**<CNcomment: 每平方米上的最大亮度值(亮度单位:candelas), 取值范围[0,10000].*/
    U32 u32MinDisplayMasteringLuminance;    /**<Minimum luminance, Represented in candelas per square meter. Values from range [0, 10000].*/ /**<CNcomment: 每平方米上的最小亮度值(亮度单位:candelas), 取值范围[0,10000].*/
} AV_VIDEO_MASTERING_DISPLAY_COLOUR_VOLUME_S;

/**Defines HDR content light Info  */
/**CNcomment: 定义HDR10 content light数据信息*/
typedef struct _AV_VIDEO_CONTENT_LIGHT_LEVEL_S
{
    U32 u32MaxContentLightLevel;    /**<Maximum brightness of a single pixel (Maximum Content Light Level) in candelas per square meter*/ /**<CNcomment: 每平方米上单一像素点的最大亮度值(亮度单位:candelas)*/
    U32 u32MaxPicAverageLightLevel; /**<Maximum brightness of a single full frame (Maximum Frame-Average Light Level) in candelas per square meter*/ /**<CNcomment: 每平方米上单一full frame的最大亮度值(亮度单位:candelas)*/
} AV_VIDEO_CONTENT_LIGHT_LEVEL_S;

/**Defines HDR10 Metadata Info  */
/**CNcomment: 定义HDR10元数据信息*/
typedef struct _AV_VIDEO_HDR10_INFO_S
{
    U8  u8FullRangeFlag;            /**<Whether the color space in fullrange.*/ /**<CNcomment: Color space是否是fullrange的.*/
    U8  u8ColourPrimaries;          /**<The colour primaries type, BT709, BT2020.*/ /**<CNcomment: Colour primaries类型标识, 如BT709, BT2020.*/
    U8  u8TransferCharacteristics;  /**<The transfer characteristics type.*/ /**<CNcomment: Transfer characteristics类型标识.*/
    U8  u8MatrixCoeffs;             /**<The Matrix Coefficients, BT2020CL, BT2020NCL.*/ /**<CNcomment: 矩阵系数, 如BT2020CL, BT2020NCL.*/
    U8  u8MasteringAvailable;       /**<Whether the Mastering available, The value 0 indicates available, The value 1 indicates unavailable.*/
                                    /**<CNcomment: Mastering数据是否可用, 0:不可用; 1:可用*/
    U8  u8ContentAvailable;         /**<Whether the Content available, The value 0 indicates available, The value 1 indicates unavailable.*/
                                    /**<CNcomment: Content数据是否可用, 0:不可用; 1:可用*/
    AV_VIDEO_MASTERING_DISPLAY_COLOUR_VOLUME_S  stMasteringInfo;    /**< Matering display Info */ /**<CNcomment: Matering display数据 */
    AV_VIDEO_CONTENT_LIGHT_LEVEL_S              stContentInfo;      /**< Content light Info */ /**<CNcomment: Content light数据 */
} AV_VIDEO_HDR10_INFO_S;

/**Defines HLG Metadata Info  */
/**CNcomment: 定义HLG元数据信息*/
typedef struct _AV_VIDEO_HLG_INFO_S
{
    U8  u8FullRangeFlag;            /**<Whether the color space in fullrange.*/ /**<CNcomment: Color space是否是fullrange的.*/
    U8  u8ColourPrimaries;          /**<The colour primaries type, BT709, BT2020.*/ /**<CNcomment: Colour primaries类型标识, 如BT709, BT2020.*/
    U8  u8TransferCharacteristics;  /**<The transfer characteristics type.*/ /**<CNcomment: Transfer characteristics类型标识.*/
    U8  u8MatrixCoeffs;             /**<The Matrix Coefficients, BT2020CL, BT2020NCL.*/ /**<CNcomment: 矩阵系数, 如BT2020CL, BT2020NCL.*/
    U8  u8MasteringAvailable;       /**<Whether the Mastering available,The value 0 indicates available, The value 1 indicates unavailable.*/
                                    /**<CNcomment: Mastering数据是否可用,0:不可用；1:可用*/
    U8  u8ContentAvailable;         /**<Whether the Content available,,The value 0 indicates available, The value 1 indicates unavailable.*/
                                    /**<CNcomment: Content数据是否可用,0:不可用；1:可用*/
    AV_VIDEO_MASTERING_DISPLAY_COLOUR_VOLUME_S  stMasteringInfo;    /**< Matering display Info */ /**<CNcomment: Matering display数据 */
    AV_VIDEO_CONTENT_LIGHT_LEVEL_S              stContentInfo;      /**< Content light Info */ /**<CNcomment: Content light数据 */
    U8  u8BackWardsCompatible;
} AV_VIDEO_HLG_INFO_S;

/**Defines video Metadata type  */
/**CNcomment: 定义视频元数据类型*/
typedef enum _AV_VIDEO_METADATA_TYPE_E
{
    AV_VIDEO_METADATA_TYPE_HDR10 = 0,
    AV_VIDEO_METADATA_TYPE_HLG,
    AV_VIDEO_METADATA_TYPE_BUTT
} AV_VIDEO_METADATA_TYPE_E;

/**Defines video Metadata info  */
/**CNcomment: 定义视频元数据信息的共同体*/
typedef union _AV_VIDEO_METADATA_INFO_U
{
    AV_VIDEO_HDR10_INFO_S stHdr10Info;
    AV_VIDEO_HLG_INFO_S   stHlgInfo;
} AV_VIDEO_METADATA_INFO_U;

/**Defines the struct of video Metadata info  */
/**CNcomment: 定义视频元数据信息结构*/
typedef struct _AV_VIDEO_METADATA_INFO_S
{
    AV_VIDEO_METADATA_TYPE_E      enMetadataType;   /**<the type of metadata.*/ /**<CNcomment: 视频元数据类型.*/
    AV_VIDEO_METADATA_INFO_U      unMetadataInfo;   /**<the union of metadata information.*/ /**<CNcomment: 视频元数据信息的共同体.*/
    BOOL                          bPaddingInfo;     /**<if need padding metadata information to frame information.*/ /**<CNcomment: 是否需要填充到帧信息中.*/
} AV_VIDEO_METADATA_INFO_S;

/********************************* Extend Emum and Structure Definition End ***************************/
#endif//HAL_HISI_EXTEND_H

/**Defines the parameters of format changing */
/**CNcomment: 定义制式切换的相关参数*/
typedef struct _AV_FORMAT_CHANGE_PARAM_S
{
    U32                 u32NewFormat;            /**<New format*/ /**<CNcomment: 新的制式*/
    U32                 u32ImageWidth;          /**<Width of image*/ /**<CNcomment: 图像宽度*/
    U32                 u32ImageHeight;         /**<Height of image*/ /**<CNcomment: 图像高度*/
    BOOL                bProgressive;           /**<Sampling type (progressive or interlaced)*/ /**<CNcomment: 采样方式(逐行/隔行) */
    U32                 u32FrameRate;           /**<Frame rate*//**<CNcomment:帧率*/
    U32                 u32ImageStride;         /**<Stride of image*/ /**<CNcomment: 图像跨度*/
    U32                 u32ImageSize;           /**<Size of image*/ /**<CNcomment: 图像大小*/
    U32                 u32ImageNum;            /**<Num of image*/ /**<CNcomment: 需要个数*/
    U32                 u32ImageBitDepth;        /**<BitDepth of image*/ /**<CNcomment: 图像的比特深度*/
} AV_FORMAT_CHANGE_PARAM_S;

/**Strcut of sync region parameter.
Define several regions depend on stream information, sync operations are different in each region,
see the defines of AV_SETTINGS_S,AV_SYNC_MODE_E */
/**CNcomment: 同步区域参数设定.
我们根据流的情况,把同步调整分开成几个不同的区间.
在不同的区间内,同步操作是不一样的.
参见AV_SETTINGS_S,AV_SYNC_REGION_PARAMS_S,AV_SYNC_MODE_E 的定义*/
typedef struct _AV_SYNC_REGION_PARAMS_S
{
    S32 s32VidPlusTime;             /**<Plus time range during video synchronization*//**<CNcomment: 视频超前同步基准的时间,0:忽略,if(enAvSyncMode==AV_SYNC_MODE_VID) 此值无效.*/
    S32 s32VidNegativeTime;         /**<Negative time range during video synchronization*//**<CNcomment: 视频落后同步基准的时间,0:忽略,if(enAvSyncMode==AV_SYNC_MODE_VID) 此值无效.*/
    S32 s32AudPlusTime;             /**<Plus time range during audio synchronization*//**<CNcomment: 音频超前同步基准的时间,0:忽略,if(enAvSyncMode==AV_SYNC_MODE_AUD) 此值无效.*/
    S32 s32AudNegativeTime;         /**<Negative time range during audio synchronization*//**<CNcomment: 音频落后同步基准的时间,0:忽略,if(enAvSyncMode==AV_SYNC_MODE_AUD) 此值无效.*/
    BOOL bSmoothPlay;               /**<Slow playing enable.TRUE:Sync slowly, repeat a iframe every several iframes or discard a iframe,  seems like slow motion; FALSE: Sync quickly, will be not smooth*//**<CNcomment: TRUE:慢慢同步,隔几帧重复或者丢弃一帧,效果上可能看到慢动作,FALSE:快速同步,效果上可能看到卡顿*/
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
/**CNcomment:  av 同步参数设定.
当同步模式是:AV_SYNC_MODE_DISABLE 和AV_SYNC_MODE_AUTO 的时候,AV_SYNC_PARAM_S 的设置被忽略.
根据流的状态,把同步调整分成几个区域,不同的区域处理方式不一样:
如果音视频和同步时间基准相差范围是:[0,stSyncStartRegion),表示处于同步状态,
如果音视频和同步时间基准相差范围是:[stSyncStartRegion,stSyncNovelRegion),表示处于同步调整区域.
如果音视频和同步时间基准相差范围是:[stSyncNovelRegion,10s),表示处于同步异常区域.
如果音视频和同步时间基准相差大于10s, 处于超异常状态,驱动放弃同步.
预同步超时时间u32PreSyncTimeoutMs,表示启动播放的时候,驱动预同步的超时时间,
1.如果u32PreSyncTimeoutMs==0,那么不做预同步处理,
2.如果u32PreSyncTimeoutMs!=0,那么在超时时间之内,如果bPreSyncSmoothPlay==TRUE,那么是几帧重复或者丢弃一帧,可能看到慢动作,如果bPreSyncSmoothPlay==FALS,那么会快速同步,可能看到卡顿.
3. 如果bQuickOutput==FALSE,那么在同步之后,或者u32PreSyncTimeoutMs超时之后才显示输出,
4. 如果bQuickOutput==TRUE,那么一解码马上输出,如果当时还没有同步,那么在u32PreSyncTimeoutMs超时之内或者同步完成之前,
输出是慢动作还是卡顿取决于bPreSyncSmoothPlay和u32PreSyncTimeoutMs的大小.
参见 AV_SETTINGS_S,AV_SYNC_REGION_PARAMS_S,AV_SYNC_MODE_E 的定义
为了兼容老代码,AV_SYNC_MODE_E 和u32AudSyncOffseMs,u32VidSyncOffseMs 保留在AV_SETTINGS_S 里面*/
typedef struct _AV_SYNC_PARAM_S
{
    AV_SYNC_REGION_PARAMS_S stSyncStartRegion;      /**<Synchronization start region*//**<CNcomment: 开始同步调整区域*/
    AV_SYNC_REGION_PARAMS_S stSyncNovelRegion;      /**<Synchronization exception region*//**<CNcomment: 开始同步异常调整区域*/

    U32                     u32PreSyncTimeoutMs;    /**<Pre-synchronization timeout, in ms*//**<CNcomment: 启动播放的时候,预同步超时时间,如果为0,表示不做预同步*/
    BOOL                    bPreSyncSmoothPlay;     /**<Output mode while doing presync before synchronization finished, the output effect is same with bSmoothPlay of AV_SYNC_REGION_PARAMS_S*//**<CNcomment: 启动播放的时候,达到同步之前或者预同步超时时间之内的同步方式. */
    BOOL                    bQuickOutput;           /**<Fast output enable*//**<CNcomment: 启动播放的时候是否快速输出第一帧.*/
} AV_SYNC_PARAM_S;

// TODO: u32InjectMinLen是做什么用的?
/**Struct of inject setting param.*/
/**CNcomment: 数据注入设置参数*/
typedef struct _AV_INJECT_SETTINGS_S
{
    AV_DATA_TYPE_E      enDataType;         /**<Stream type*//**<CNcomment: 注入的数据类型*/
    AV_CONTENT_TYPE_E   enInjectContent;    /**<Inject content type*//**<CNcomment:注入的数据格式 */
    U32                 u32BufSize;         /**<If 0, automatically sets the appropriate size*//**<CNcomment:  为零时,自己决定*/
    U32                 u32InjectMinLen;    /**<If 0, automatically sets the appropriate size*//**<CNcomment:  为零时,自己决定*/
} AV_INJECT_SETTINGS_S;

/**Struct of buffer status.*/
/**CNcomment: 内存状态信息*/
typedef struct _AV_BUF_STATUS_S
{
    AV_DATA_TYPE_E  enDataType;             /**<Data type*//**<CNcomment: 数据类型*/
    U32             u32Size;                   /**<Buffer size*//**<CNcomment: 缓存大小*/
    U32             u32Free;                /**<Free buffer size*//**<CNcomment: 空闲缓存大小*/
    U32             u32Used;                /**<Used buffer size*//**<CNcomment: 已使用缓存大小*/
    U32             u32InjectMinLen;        /**<Minimum data length of injected*//**<CNcomment: 每次注入数据的最小长度*/
} AV_BUF_STATUS_S;

/**Struct of inject status*/
/**CNcomment: 注入状态*/
typedef struct _AV_INJECT_STATUS_S
{
    HANDLE                  hInjecter;       /**<Injecter handle*//**<CNcomment: 注入器句柄*/
    HANDLE                  hAv;             /**<AV handle that injecter attached *//**<CNcomment: 播放器句柄*/
    AV_BUF_STATUS_S         stBufStatus;     /**<buffer status*//**<CNcomment: 内存状态*/
    // TODO: should support ts stream?
    DMX_ID_E                enSourceId;      /**<CNcomment: TS注入时,对应的TS流通道,
                                              * 不同平台他的物理意义不一样,
                                              * 要和tvos_hal_dmx 模块约定好
                                              * 因为dmx需要他来获取数据
                                              * dmx 模块和CI模块实现的时候用m_source_id 能转换成具体ts来源数据 类型.
                                              */
} AV_INJECT_STATUS_S;

/**Struct of injecter open param*/
/**CNcomment:注入器打开参数*/
typedef struct _AV_INJECTER_OPEN_PARAMS_S
{
    AV_INJECT_SETTINGS_S stSettings; /**<Inject setting param*//**<CNcomment: 注入器设置参数*/
} AV_INJECTER_OPEN_PARAMS_S;

/**Struct of injecter close param*/
/**CNcomment:注入器关闭参数*/
typedef struct _AV_INJECTER_CLOSE_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: 以后扩展用 */
} AV_INJECTER_CLOSE_PARAMS_S;

/**Struct of data suorce if the data from which demux*/
/**CNcomment:节目来源参数
只是设置来自哪个dmx,如果是注入,那不需要设置,injecter 关联之后,注入数据优先于dxm的数据.
如果是ts注入到dmx解复用,再进来,那么AV_SOURCE_PARAMS_S,也适用,因为ts数据注入 进dmx，injecter是dmx的数据来源.
dmx_source_params_t可以设置数据是从哪个tuner(dmd),还是哪个injecter,还是其他.*/
typedef struct _AV_SOURCE_PARAMS_S
{
    DMX_ID_E enDemuxId; /**<demux id of data source*//**<CNcomment: 只有当数据必须经过dmx才有效*/
} AV_SOURCE_PARAMS_S;

/**Struct of audio decode status: stream info, decode state, DAC status
The stream info may be not corrent when decode stopped*/
/**CNcomment:音频状态, 当前流,解码器,DAC的状态
当解码器停止时,读到流的状态可能是不准确的*/
typedef struct _AV_AUD_STATUS_S
{
    U32                     u32PacketCount;         /**<Count of audio packet*//**<CNcomment: 通过检查是否有音频包过来确认有没有音频*/
    U32                     u32FrameCount;          /**<Count of audio frame*//**<CNcomment: 通过检查音频帧的数目来确定有没有音频*/
    AV_DECODER_STATE_E      enDecodeState;          /**<decode state*//**<CNcomment: 音频解码状态*/
    AV_AUD_STREAM_TYPE_E    enStreamType;           /**<Stream type*//**<CNcomment: 从流里面获取到的流类型*/
    U32                     u32SampleRate;          /**<Sample rate*/ /**< 音频采样率 (32000,44100,48000 )*/
    U32                     u32BitWidth;            /**<Bit width*//**< 音频每个采样点所占的比特数, 如:8bit,16bit */
    AV_SOURCE_TYPE_E        enSourceType;           /**<Data source*/ /**< 数据来源*/
    U32                     u32PesBufferSize;       /**<Pes buffer size*//**<CNcomment: Pes 缓存大小*/
    U32                     u32PesBufferFreeSize;   /**<Free Pes buffer size*//**<CNcomment: 空闲Pes 缓存大小*/
    U32                     u32EsBufferSize;        /**<ES buffer size*//**<CNcomment: ES 缓存大小*/
    U32                     u32EsBufferFreeSize;    /**<Free ES buffer size*//**<CNcomment: 空闲ES 缓存大小*/
    S64                     s64Pts;                 /**<current PTS of the audio decoder *//**<CNcomment: 当前音解码器使用的PTC*/
    S64                     s64FirstPts;            /**<First pts of video decode *//**<CNcomment: 解码器得到的第一个PTS*/
    U32                     u32Stc;                 /**<current STC used by the audio decoder *//**<CNcomment: 当前音频解码器使用的STC*/
    U16                     u16Pid;                 /**<Audio pid *//**<CNcomment: 音频pid*/
    U16                     u16ADPid;               /**<Audio AD pid *//**<CNcomment: 音频pid*/
    U32                     u32FrameBufTime;        /**<Frame buffer time*//**<CNcomment: 帧缓冲时间 */
#ifdef HAL_HISI_EXTEND_H
    U32                     u32Bps;                 /**<Bits per second*//**<CNcomment: 音频码率,bit/s ,0表示不关注*/
#endif
} AV_AUD_STATUS_S;

/**Struct of video decode status: stream info, decode state, DAC status
The stream info may be not corrent when decode stopped*/
/**CNcomment:视频状态, 当前流,解码器,DAC的状态
当解码器停止时,读到流的状态可能是不准确的*/
typedef struct _AV_VID_STATUS_S
{
    U32 u32DispPicCount;    /**< CNcomment:通过检查显示视频帧的数目来确定有没有视频
                             * 此时需要CA启动,或者有"换台时只使用加扰的ES PIDs播出,
                             * 但是并不处理PMT(CA没有启动)" 这种需求下依然能检测到是否有视频
                             */
    AV_DECODER_STATE_E      enDecodeState;          /**<Video decode state*//**<CNcomment: 视频解码器状态*/
    AV_VID_STREAM_TYPE_E    enStreamType;           /**<Video stream type*//**<CNcomment: 视频类型*/
    U16                     u16FpsInteger;          /**<Integer part of the frame rate *//**<CNcomment: 帧率的整数部分*/
    U16                     u16FpsDecimal;          /**<Decimal part of the frame rate *//**<CNcomment: 帧率的小数部分*/

    AV_SOURCE_TYPE_E        enSourceType;           /**<Data source *//**<CNcomment: 数据来源*/
    AV_3D_FORMAT_E          en3dFormat;             /**<3D format *//**< 3D TV 节目源信息*/
    U32                     u32PesBufferSize;       /**<Pes buffer size*//**<CNcomment: Pes 缓存大小*/
    U32                     u32PesBufferFreeSize;   /**<Free Pes buffer size*//**<CNcomment: 空闲Pes 缓存大小*/
    U32                     u32EsBufferSize;        /**<ES buffer size*//**<CNcomment: ES 缓存大小*/
    U32                     u32EsBufferFreeSize;    /**<Free ES buffer size*//**<CNcomment: 空闲ES 缓存大小*/
    S64                     s64Pts;                 /**<current PTS of the audio decoder *//**<CNcomment: 当前视频解码器使用的PTC*/
    S64                     s64FirstPts;            /**<First pts of video decode *//**<CNcomment: 解码器得到的第一个PTS*/
    U32                     u32Stc;                 /**<current STC used by the audio decoder *//**<CNcomment: 当前视频解码器使用的STC*/
    BOOL                    bInterlaced;            /**<is interlaced*//**<CNcomment: 逐行还是隔行*/
    U32                     u32SourceWidth;         /**<width*//**<CNcomment: 视频源宽度*/
    U32                     u32SouceHeight;         /**<height*//**<CNcomment: 视频源高度*/
    U32                     u32DisplayWidth;        /**<width*//**<CNcomment: 视频显示宽度*/
    U32                     u32DisplayHeight;       /**<height*//**<CNcomment: 视频显示高度*/
    BOOL                    bByPass;
    U16                     u16Pid;                 /**<video pid*//**<CNcomment: 视频pid*/
    U32                     u32FrameBufTime;        /**<Frame buffer time*//**<CNcomment: 帧缓冲时间 */
#ifdef HAL_HISI_EXTEND_H
    U32                     u32PicNotDecodeCount;   /**<frame counter of not decode*//**<CNcomment: 解码器中尚未解码的帧数*/
    U32                     u32Bps;                 /**<Bits per second*//**<CNcomment: 视频码率,bit/s ,0表示不关注*/
#endif
} AV_VID_STATUS_S;

/**Struct of av player status:display status and decode status of audio and video decoder
TODO*/
/**CNcomment:播放状态,当前音视频解码器和显示的状态
1. m_disp_fmt_arr:当前系统中实际设置的制式(分辨率),
    m_disp_fmt_arr和stVidStatus::m_stream_format不同,
    前者是当前系统实际的设置的制式(分辨率), 后者是当前解码的视频的制式(分辨率)
2. m_frame_rate_arr:当前系统中实际设置的帧率
    m_frame_rate_arr和stVidStatus::m_frame_rate不同,
    前者是当前系统实际的设置的帧率, 后者是当前解码的视频的帧率.
3. m_aspect_ratio_arr:当前系统中实际设置的宽高比.
    m_aspect_ratio_arr和stVidStatus::m_aspect_ratio不同,
    前者是当前系统实际的设置的宽高比, 后者是当前解码的视频的宽高比.*/
typedef struct _AV_STATUS_S
{
    AV_AUD_STATUS_S         stAudStatus;                           /**<Audio play status *//**<CNcomment: 音频播放状态*/
    AV_VID_STATUS_S         stVidStatus;                           /**<Video play status *//**<CNcomment: 视频播放状态*/
    U32                     u32TsBufferSize;                       /**<TS buffer size*//**<CNcomment:TS 缓存大小*/
    U32                     u32TsBufferFreeSize;                   /**<TS buffer size not used*//**<CNcomment:空闲TS 缓存大小*/
    U32                     u32TsPacketSize;                       /**<TS packet size*//**<CNcomment:TS包大小*/
    HANDLE                  ahInjecter[AV_CONTENT_BUTT];           /**<Injecters attached on the av player, 0 is invalid handle*//**<播放器绑定的注入器，以::AV_CONTENT_E为下标索引,, 0 为非法handle*/
    S64                     s64LocalTime;                          /**<Local synchronization reference time, -1 is invalid*//**<CNcomment: 本地同步参考时间，-1为无效值*/
    U16                     u16PcrPid;                             /**<PCR pid*//**<CNcomment: PCR pid*/
    S32                     s32AVDiffTime;                         /**<Diff time between audio and video in millisecond *//**<CNcomment: 音视频同步时间差，单位毫秒*/
} AV_STATUS_S;

/**Struct of audio decode parameter, only special audio format need to be set*/
/**CNcomment:音频解码器参数,一般音频格式不需要设置,只有特定格式需要设置*/
typedef struct _AV_ADEC_PARAM_S
{
    U32 u32Version;        /**<Audio encoding version, such as 0x160(WMAV1) and 0x161 (WMAV2). It is valid only for WMA encoding. *//**< CNcomment:音频编码版本，仅对wma编码，0x160(WMAV1), 0x161 (WMAV2) */
    U32 u32SampleRate;     /**<Sample rate*//**<CNcomment: 音频采样率 (32000,44100,48000 ),0表示不关注*/
    U32 u32BitWidth;       /**<Bit width*//**<CNcomment: 音频每个采样点所占的比特数, 如:8bit,16bit,0表示不关注 */
    U32 u32Channels;       /**<Audio channels*//**<CNcomment: 声道数:0,1,2,4,6,8,10... ,0表示不关注*/
    U32 u32BlockAlign;     /**<Number of bytes contained in a packet*//**<CNcomment: 包大小 ,0表示不关注*/
    U32 u32Bps;            /**<Bits per second*//**<CNcomment: 音频码率,bit/s ,0表示不关注*/
    BOOL bBigEndian;       /**<Big endian or little endian. It is valid only for the PCM format *//**< CNcomment:大小端，仅pcm格式有效 */
    U32  u32ExtradataSize; /**<Length of the extended data *//**< CNcomment:扩展数据长度 */
    U8*  pu8Extradata;     /**<Extended data *//**<CNcomment:扩展数据 */
    VOID*  pCodecContext;  /**<Audio decode context *//**<CNcomment:音频解码上下文 */
} AV_ADEC_PARAM_S;

/*Struct of multi audio.*/
/*CNcomment: 设置多音频的结构体*/
typedef struct _AV_INVOKE_SET_MULTI_AUD_S
{
    U16                     u16PidNum;      /**<the number of Audio PID *//**< CNcomment:音频PID个数 */
    U16                     *pu16AudPid;    /**<Pointer to the array of audio PID*//**< CNcomment:指向PID数组的指针 */
    AV_AUD_STREAM_TYPE_E    *penAudType;    /**<Pointer to the array of audio type*//**< CNcomment:指向音频类型数组的指针 */
    AV_ADEC_PARAM_S         *pstAdec;       /**<Pointer to the audio decode parameters*//**< CNcomment:指向音频解码器参数的指针 */
} AV_INVOKE_SET_MULTI_AUD_S;

/**Struct of video decode parameter, only special audio format need to be set*/
/**CNcomment:视频解码器参数,一般音频格式不需要设置,只有特定格式需要设置*/
typedef struct _AV_VDEC_PARAM_S
{
    U32 u32Fps;            /**<Frames per second*//**<CNcomment: 帧率(x1000) ,实际帧率乘1000, 0表示不关注*/
    U32 u32Bps;            /**<Bits per second*//**<CNcomment: 视频码率,bit/s ,0表示不关注*/
    U16 u16Width;          /**<Video width*//**<CNcomment: 宽度,单位像素 ,0表示不关注*/
    U16 u16Height;         /**<Video height*//**<CNcomment: 高度,单位像素 ,0表示不关注*/
    U32 u32Profile;        /**<Profile level. *//**<CNcomment:Profile级别 */
    U32 u32Version;        /**<Version of codec. *//**<CNcomment:Codec 版本 */
    BOOL bFlip;            /**<Set this parameter to 1. In this cases, set it to 0.*//**<CNcomment: 图像需要倒转时置1，否则置0*/
    VOID*  pCodecContext;  /**<Video decode context *//**<CNcomment:视频解码上下文 */
#ifdef HAL_HISI_EXTEND_H
    AV_VDEC_FRMRATE_TYPE_E enFrmRateType;   /**<The source of frame rate*//**<CNcomment: 帧率来源类型 */
    S32 s32CtrlOptions;    /**<The value is AV_VDEC_CTRL_OPTION_E, or the 'or' value of several enum type*/
                           /**<CNcomment: 取值为::AV_VDEC_CTRL_OPTION_E，或者几个枚举的'或' */
#endif
} AV_VDEC_PARAM_S;

/**Struct of av player parameter
1.Get AV param first, and then renew the param, then set.
2.The set operation may be cover the settings set by other task.
3.If pid is bigger than INVALID_PID, should correct to INVALID_PID.
4.If the value of volume is over range, should auto set valid value.*/
/**CNcomment:av设置参数
1. 需要修改这些参数时,请先get出来,修改需要修改的成员再set回去
    set函数里面对于没有改变的成员不做修改
2. 考虑到多任务操作,get出来的参数在set回去之前,别的任务可能已经有set操作
    也就是此时的set有可能会覆盖其他任务set函数的设置.
3. 如果pid 参数大于 INVALID_PID, 需要修正为INVALID_PID.
4. 如果音量(u32LeftVol,u32RightVol)参数超出范围, 需要自动修正到合理范围.*/
typedef struct _AV_SETTINGS_S
{
    AV_ADEC_PARAM_S             stAdecParams;          /**<Audio decode parameters for special audio format*//**<CNcomment: 一般音频格式不需要设置,只有特定格式需要设置.*/
    AV_VDEC_PARAM_S             stVdecParams;          /**<Video decode parameters for special Video format*//**<CNcomment: 一般视频格式不需要设置,只有特定格式需要设置.*/
    AV_SOURCE_PARAMS_S          stSourceParams;        /**<Data source*//**<CNcomment:数据来源*/
    AV_SYNC_MODE_E              enAvSyncMode;          /**<Sync mode*//**<CNcomment:同步模式*/
    AV_SYNC_PARAM_S             stSyncParams;          /**<Sync parameter*//**<CNcomment:同步参数*/
    AV_ERROR_RECOVERY_MODE_E    enErrRecoveryMode;     /**<Recovery mode*//**<CNcomment:错误恢复模式*/
    AV_VID_STOP_MODE_E          enVidStopMode;         /**<Stop mode*//**<CNcomment:视频停止模式*/
    AV_VID_STREAM_TYPE_E        enVidStreamType;       /**<Video stream type*//**<CNcomment:视频流类型*/
    AV_AUD_STREAM_TYPE_E        enAudStreamType;       /**<Audio stream type*//**<CNcomment:音频流类型*/
    AV_3D_FORMAT_E              en3dFormat;            /**<3D format*/ /**<CNcomment: 3D TV 设置*/
    BOOL                        bVidDecodeOnce;        /**<FALSE:decode all data; TRUE:only decode the first pictrue for preview *//**<CNcomment: FALSE : 正常设置,解码所有输入数据; TRUE :只解第一副图片,主要用于预览*/
    S32                         s32Speed;              /**<The trick modes consist in rewind, forward at slow and fast speed. 100: normal play, 200:Fast forward at two times the normal speed, -200:Fast backward at two times the normal speed,  50:Slow forward at 1/2 times the normal speed, 0 is free run*//**<CNcomment:  100 :正常播放,200:两倍速,-200:快退2倍速,50:二分之一倍速慢进，0为自由播放等. 主要用于标识快进快退*/
    U16                         u16PcrPid;             /**<Pcr pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)如果平台支持,请clear该通道的pid*/
    U16                         u16AudPid;             /**<Audio pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)如果平台支持,请clear该通道的pid*/
    U16                         u16AudADPid;           /**<Audio AD pid, used in ms12 scene, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)如果平台支持,请clear该通道的pid*/
    U16                         u16VidPid;             /**<Video pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)如果平台支持,请clear该通道的pid*/
    S32                         s32AudSyncOffseMs;     /**<Audio offset for synchronization*//**<CNcomment: 设置音频相对于同步基准的时间偏移,默认为0,不建议修改,if(enAvSyncMode==AV_SYNC_MODE_AUD) 此值无效.*/
    S32                         s32VidSyncOffseMs;     /**<Video offset for synchronization*//**<CNcomment: 设置视频相对于同步基准的时间偏移,默认为0,不建议修改,if(enAvSyncMode==AV_SYNC_MODE_VID) 此值无效.*/
    BOOL                        bEos;
    AV_VID_ROTATION_E           enVideoRotation;       /**<Rotation of picture*//**<CNcomment: 视频旋转角度*/
#ifdef HAL_HISI_EXTEND_H
    BOOL                        bEnableTVP;            /**<Is trusted video path enable or not*//**<CNcomment: 安全视频通路是否使能*/
    AV_VDEC_MODE_E              eDecMode;              /**<Video decoder mode *//**<CNcomment:视频解码模式*/
    AV_AUD_DOLBYDEC_CFG_S       stDolbyDecCfg;         /**<Dolby deocder config *//**<CNcomment:Dolby解码配置参数*/
    AV_AUD_DOLBY_INFO_S         stDolbyInfo;           /**<Dolby info, only support getting *//**<CNcomment:Dolby流信息，仅支持获取*/
    AV_AUD_DTS_INFO_S           stDtsInfo;             /**<Dts info, only support getting *//**<CNcomment:Dts流信息，仅支持获取*/
    AV_LOW_DELAY_S              stLowDelayCfg;         /**<Low Delay Attr *//**<CNcomment: 低延时属性*/
    AV_HDR_PARAM_S              stHdrParams;           /**<HDR parameter*//**<CNcomment:HDR参数*/
    BOOL                        bEnableAudSecurity;    /**<Is audio security path enable or not*//**<CNcomment: 安全音频通路是否使能*/
#endif
} AV_SETTINGS_S;

typedef enum _AV_ATTR_ID_TYPE_E
{
    AV_ATTR_ID_ADEC,                /**<Audio decode parameters for special audio format, AV_ADEC_PARAM_S*//**<CNcomment: 一般音频格式不需要设置,只有特定格式需要设置, AV_ADEC_PARAM_S.*/
    AV_ATTR_ID_VDEC,                /**<Video decode parameters for special Video format, AV_VDEC_PARAM_S*//**<CNcomment: 一般视频格式不需要设置,只有特定格式需要设置, AV_VDEC_PARAM_S.*//* */

    AV_ATTR_ID_ASTREAMTYPE,         /**<Audio stream type, AV_AUD_STREAM_TYPE_E*//**<CNcomment:音频流类型，AV_AUD_STREAM_TYPE_E*/
    AV_ATTR_ID_VSTREAMTYPE,         /**<Video stream type, AV_VID_STREAM_TYPE_E*//**<CNcomment:视频流类型，AV_VID_STREAM_TYPE_E*/

    AV_ATTR_ID_AUD_PID,             /**<Audio pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)如果平台支持,请clear该通道的pid*/
    AV_ATTR_ID_VID_PID,             /**<Video pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)如果平台支持,请clear该通道的pid*/
    AV_ATTR_ID_PCR_PID,             /**<Pcr pid, clear it when pid is INVALID_PID*//**<CNcomment: if(pid==INVALID_PID)如果平台支持,请clear该通道的pid*/

    AV_ATTR_ID_FRMRATE_PARAM,       /**<Frame Rate Parameter, AV_VDEC_FRAMERATE_PARAM_S*//**<CNcomment:,帧率参数, AV_VDEC_FRAMERATE_PARAM_S.*/

#if 0 //后续添加
    AV_ATTR_ID_DOLBYDEC_CFG,        /**<Dolby deocder config, AV_AUD_DOLBYDEC_CFG_S *//**<CNcomment:Dolby解码配置参数, AV_AUD_DOLBYDEC_CFG_S*/
    AV_ATTR_ID_DOLBY_INFO,          /**<Dolby info, only support getting, AV_AUD_DOLBY_INFO_S *//**<CNcomment:Dolby流信息，仅支持获取, AV_AUD_DOLBY_INFO_S*/
    AV_ATTR_ID_DTS_INFO,            /**<Dts info, only support getting, AV_AUD_DTS_INFO_S *//**<CNcomment:Dts流信息，仅支持获取, AV_AUD_DTS_INFO_S*/
    AV_ATTR_ID_AD,                  /* Audio Description attr, AV_AD_ATTR_S *//**<CNcomment:Audio Description属性, AV_AD_ATTR_S*/

    AV_ATTR_ID_VDEC_MODE,           /**<Video decoder mode, AV_VDEC_MODE_E *//**<CNcomment:视频解码模式, AV_VDEC_MODE_E*/

    AV_ATTR_ID_SOURCE_PARAM,        /**<Data source, AV_SOURCE_PARAMS_S*//**<CNcomment:数据来源, AV_SOURCE_PARAMS_S*/
    AV_ATTR_ID_SYNC,                /**<Sync parameter, AV_SYNC_PARAM_S*//**<CNcomment:同步参数, AV_SYNC_PARAM_S*/
    AV_ATTR_ID_STOP_MODE,           /**<Stop mode, AV_VID_STOP_MODE_E*//**<CNcomment:视频停止模式, AV_VID_STOP_MODE_E*/
    AV_ATTR_ID_3D_FORMAT,           /**<3D format, AV_3D_FORMAT_E*/ /**<CNcomment: 3D TV 设置, AV_3D_FORMAT_E*/
    AV_ATTR_ID_PLAY_SPEED,          /**<The trick modes consist in rewind, forward at slow and fast speed. 100: normal play, 200:Fast forward at two times the normal speed, -200:Fast backward at two times the normal speed,  50:Slow forward at 1/2 times the normal speed, 0 is free run*/
                                    /**<CNcomment:  100 :正常播放,200:两倍速,-200:快退2倍速,50:二分之一倍速慢进，0为自由播放等. 主要用于标识快进快退*/
    AV_ATTR_ID_VID_ROTATION,        /**<Rotation of picture, AV_VID_ROTATION_E*//**<CNcomment: 视频旋转角度, AV_VID_ROTATION_E*/
    AV_ATTR_ID_LOW_DELAY,           /**<Low Delay Attr, AV_LOW_DELAY_S *//**<CNcomment: 低延时属性, AV_LOW_DELAY_S*/
    AV_ATTR_ID_HDR_PARAM,           /**<HDR parameter, AV_HDR_PARAM_S*//**<CNcomment:HDR参数, AV_HDR_PARAM_S*/
#endif
    AV_ATTR_ID_BUTT
} AV_ATTR_ID_TYPE_E;


/**Struct of iframe parameter*/
/**CNcomment:iframe 参数(数据及其长度)  */
typedef struct _AV_IFRAME_PARAMS_S
{
    U32   u32DataLength;                    /**<Data address*//**<CNcomment:数据地址*/
    VOID* pvIframeData;                     /**<Data length*//**<CNcomment:数据长度*/
    AV_VID_STREAM_TYPE_E enType;            /**<Data type*//**<CNcomment:数据Codec 类型*/
} AV_IFRAME_PARAMS_S;

/**Struct of iframe decode parameter*/
/**CNcomment:iframe 解码参数*/
typedef struct _AV_IFRAME_DECODE_PARAMS_S
{
    AV_IFRAME_PARAMS_S stIframeParams;      /**<iframe parameter*//**<CNcomment:I帧数据信息*/
} AV_IFRAME_DECODE_PARAMS_S;

/**
\brief AV event callback. CNcomment:av 事件回调函数类型声明 CNend
\attention \n
The function could call the api of AV module
CNcomment: 此函数里面可以调用本模块的api, 也就是说驱动在回调本函数时，要同时考虑到重入和死锁两个方面CNend
\param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
\param[in] enEvt Av event type.CNcomment:AV事件类型 CNend
\param[in] pvData The data with event, see AV_EVT_E.CNcomment:请参考 AV_EVT_E 的说明 CNend
\retval ::SUCCESS CNcomment:成功 CNend
\retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化 CNend
\retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
\see \n
::AV_EVT_E
*/
typedef S32 (* AV_CALLBACK_PFN_T)(const HANDLE hAvHandle, const AV_EVT_E enEvt, const VOID* pvData);

/**Struct of av event config parameter*/
/**CNcomment:播放事件配置参数*/
typedef struct _AV_EVT_CONFIG_PARAMS_S
{
    AV_EVT_E            enEvt;                  /**<AV event*//**<CNcomment: av事件,表示此配置对哪个事件有效*/
    AV_CALLBACK_PFN_T   pfnCallback;            /**<Callback*//**<CNcomment: 当pfnCallback为空时,如果已经注册了回调函数则移除,取消该注册*/
    BOOL                bEnableCallback;        /**<Wether enable callback*//**<CNcomment: 表示是否使能该事件回调*/
    U32                 u32NotificationToSkip;  /**<Skip count before call callback*//**<CNcomment: 表示在调用注册的回调函数之前,需要跳过几次发生的该事件*/
} AV_EVT_CONFIG_PARAMS_S;

/**Struct of AV module init parameter*/
/**CNcomment:AV 模块初始化参数*/
typedef struct _AV_INIT_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: 以后扩展用 */
} AV_INIT_PARAMS_S;

/**Struct of AV player create parameter*/
/**CNcomment:播放器实例创建参数 */
typedef struct _AV_CREATE_PARAMS_S
{
    AV_SOURCE_PARAMS_S stSourceParams;       /**<Source parameter, can be modifed dynamically*//**<CNcomment: 赋初值,以后可以动态修改TODO*/
    AV_STREAM_TYPE_E   enStreamType;
} AV_CREATE_PARAMS_S;

/**Struct of AV player destroy parameter*/
/**CNcomment:关闭播放器实例参数  */
typedef struct _AV_DESTROY_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: 以后扩展用 */
} AV_DESTROY_PARAMS_S;

/**Struct of AV module terminate parameter*/
/**CNcomment:AV模块终止参数  */
typedef struct _AV_TERM_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: 以后扩展用 */
} AV_TERM_PARAMS_S;

/**Struct of PCM data parameter*/
/**CNcomment:描述PCM数据参数的结构定义  */
typedef struct _AV_PCM_PARAMS_S
{
    U32  u32SampleRate;        /**<Sample rate*//**<CNcomment: 音频采样率 (32000,44100,48000 ),0表示不关注*/
    U32  u32BitWidth;          /**<Bit width*//**<CNcomment: 音频每个采样点所占的比特数, 如:8bit,16bit,0表示不关注 */
    U32  u32AudChannel;        /**<Audio channels*//**<CNcomment: 声道数:0,1,2,4,6,8,10... ,0表示不关注*/
    BOOL bBigEndian;           /**<TRUE: big endian; FALSE: little endian*//**<CNcomment: TRUE: 大端; FALSE: 小端*/
} AV_PCM_PARAMS_S;

/**Struct of video decode capability*/
/**CNcomment:解码器能力*/
typedef struct _AV_VDEC_CAPABILITY_S
{
    // TODO: what is the bSupportedDecType mean?
    BOOL                bSupportedDecType;  /**<Wether supported the type of enDecCapLevel*//**<CNcomment: 是否支持enDecCapLevel  的类型*/
    VDEC_RESO_LEVEL_E   enDecCapLevel;      /**<video decode capability*//**<CNcomment: 解码能力*/
    U32                 u32Number;          /**<Max number of video decode*//**<CNcomment: 最大视频解码个数*/
    U32                 u32Fps;             /**<Frames per second*//**<CNcomment:  帧率(x1000) ,实际帧率乘1000*/
    U32                 u32Dummy;           /**<Resvered*//**<CNcomment: 以后扩展用 */
} AV_VDEC_CAPABILITY_S;

/**Struct of AV player decode capability*/
/**CNcomment:播放器解码器能力*/
typedef struct _AV_DECODER_CAPABILITY_S
{
    AV_DATA_TYPE_E          enInjectDataType;                       /**<Injected data type*//**<CNcomment: 注入的数据类型 */
    U32                     au32AudDecode[AV_AUD_STREAM_TYPE_BUTT]; /**<non-0:supported,0:unsupported*//**<CNcomment: 以::AV_AUD_STREAM_TYPE_E变量为索引,非零:支持,0:不支持*/
    U32                     au32AudBypass[AV_AUD_STREAM_TYPE_BUTT]; /**<non-0:supported,0:unsupported*//**<CNcomment: 以::AV_AUD_STREAM_TYPE_E变量为索引,非零:支持,0:不支持*/
    AV_VDEC_CAPABILITY_S    stVidDecoder[AV_VID_STREAM_TYPE_BUTT];  /**<Video decode capability*//**<CNcomment:视频解码能力*/
} AV_DECODER_CAPABILITY_S;

/**Struct of AV player capability*/
/**CNcomment:播放器能力*/
typedef struct _AV_CAPABILITY_S
{
    AV_DECODER_CAPABILITY_S stDecoderCapability; /**<AV player decode capability*//**<CNcomment:播放器解码能力*/
} AV_CAPABILITY_S;

// TODO: 是否可以删除?
/**Struct of ES data parameter*/
/**CNcomment:ES 数据参数*/
typedef struct _AV_ES_PARAMS_S
{
    U32 u32SampleRate;    /**<Sample rate*//**<CNcomment: 音频采样率 (32000,44100,48000 ),0表示不关注*/
} AV_ES_PARAMS_S;

/**Struct of ES data parameter*/
/**CNcomment:ES 数据参数*/
typedef struct _AV_ES_DATA_S
{
    S64         s64TimeStamp;       /**<TimeStamp*//**<CNcomment: 时间戳 */
    VOID*       pvHeader;           /**<Es Buffer header, NULL is no header*//**<CNcomment:  ES数据头，如果没有设置为NULL */
    U32         u32HeaderLen;       /**<Length of es Buffer header, 0 is no header*//**<CNcomment:  ES数据头长度，如果没有设置为0 */
    VOID*       pvEsBuf;            /**<Buffer address*//**<CNcomment:  数据缓冲区地址 */
    U32         u32EsLen;           /**<Buffer length*//**<CNcomment:  缓冲区长度 */
    VOID*       pvPrivate;          /**<private address*//**<CNcomment:  私有数据缓冲区地址 */
    U32         u32PrivateLen;      /**<private length*//**<CNcomment:  私有数据缓冲区长度 */
    BOOL        bEndOfFrm;          /**<whether this package of stream contains the end of one frame*//**<CNcomment: 该包码流是否包含一帧的结尾*/
} AV_ES_DATA_S;


#ifdef ANDROID_HAL_MODULE_USED
/**AV module structure(Android require)*/
/**CNcomment:AV模块结构(Android对接要求) */
typedef struct _AV_MODULE_S
{
    struct hw_module_t stCommon;
} AV_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HAL_AV */
/** @{ */  /** <!-- [HAL_AV] */

/**AV device structure*//** CNcomment:AV设备结构*/
typedef struct _AV_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif
    /**
    \brief AV module init.CNcomment:AV 模块初始化.CNend
    \attention \n
    Other functions cannot be useful before init, return SUCCESS when repeated called.
    CNcomment: 在初始化之前, 其他函数都不能正确运行, 重复调用init 接口,返回SUCCESS. CNend
    \param[in] pstInitParams Vout module init param.CNcomment:初始化模块参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_AV_INIT_FAILED  other error.CNcomment:初始化错误 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AOUT_INIT_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_init)(struct _AV_DEVICE_S* pstDev, const AV_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief Create a AV player instance.CNcomment:创建一个播放器实例 .CNend
    \attention \n
    None
    \param[out] phAv Return AV handle.CNcomment:返回AV  句柄 CNend
    \param[in] pstCreateParams Create param.CNcomment:创建参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  av not init.CNcomment:未初始化 CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::ERROR_AV_OP_FAILED Create too max av handle. CNcomment:创建过多av实例CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Destroy a AV player instance.CNcomment:销毁一个实例.CNend
    \attention \n
    This operation will detach injecter but close it. CNcomment: 该操作会解绑定注入器但是不会关闭注入器CNend
    \param[in] hAvHandle AV handle.CNcomment:AV  句柄 CNend
    \param[in] pstDestroyParams Destroy param.CNcomment:销毁参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_DESTROY_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_destroy)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle,
                      const AV_DESTROY_PARAMS_S* const pstDestroyParams);

    /**
    \brief Terminate AV module.CNcomment:模块终止.CNend
    \attention \n
    Return SUCCESS when repeated called.
    CNcomment: 重复term 返回SUCCESS. CNend
    \param[in] pstTermParams Terminate param.CNcomment:终止参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_TERM_FAILED Term av module fail, maybe has av or injecter not destroy. CNcomment:av 模块去初始化失败，可能是因为有av或者注入器句柄未释放CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_TERM_PARAMS_S
    */
    S32 (*av_term)(struct _AV_DEVICE_S* pstDev, const AV_TERM_PARAMS_S* const pstTermParams);

    /**
    \brief Get the capability of AV module. CNcomment:获取模块设备能力 CNend
    \attention \n
    None
    \param[out] pstCapability Return capability.CNcomment:返回模块能力 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_CAPABILITY_S
    */
    S32 (*av_get_capability)(struct _AV_DEVICE_S* pstDev, AV_CAPABILITY_S* pstCapability);

    /**
    \brief Config the callback attribute of AV event. CNcomment:配置某一AV事件的参数 CNend
    \attention \n
    The function can execute regist/remove/disable/enable
    1.Each event can register callback function and set it's config independently.
    2.Callback function bind with AV handle.
    3.Only one callback function can be registered for a AV event on the same AV handle, so the callback function will be recovered.
    CNcomment: 通过本函数可以执行的操作有regist/remove/disable/enable
    1. 每个事件都可以独立注册和配置自己的回调函数.
    2. 回调函数和handle绑定.
    3. 同一个handle, 一个事件只能注册一个回调函数,即:后面注册的回调函数会覆盖原有的回调函数.
    CNend
    \param[in] hAvHandle AV handle.CNcomment:VOUT 句柄 CNend
    \param[in] pstCfg Config param.CNcomment:事件配置参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Get the config of a AV event. CNcomment:获取某一AV 事件的配置参数 CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] enEvt AV evnet type.CNcomment:AV事件类型 CNend
    \param[out] pstCfg Config param.CNcomment:事件配置参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Get status of AV instance. CNcomment:获取av状态 CNend
    \attention \n
    Stream info, decode status, DAC status.
    CNcomment: 当前流,解码器,DAC的状态CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[out] pstStatus Status param.CNcomment:状态参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_STATUS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_get_status)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_STATUS_S* pstStatus);

    /**
    \brief Get config of AV instance. CNcomment:获取av设置 CNend
    \attention \n
    Get AV param first, and then renew the param, then set.
    CNcomment: 修改av参数时,请先get出来,修改需要修改的成员再set回去CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[out] pstSettings Return setting param.CNcomment:返回设置参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_SETTINGS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_get_config)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_SETTINGS_S* pstSettings);

    /**
    \brief Set config of AV instance. CNcomment:设置av参数 CNend
    \attention \n
    Get AV param first, and then renew the param, then set.
    CNcomment: 修改av参数时,请先get出来,修改需要修改的成员再set回去CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] pstSettings Setting param.CNcomment:设置参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Get attribte of AV instance. CNcomment:获取av属性 CNend
    \attention \n
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] enAttrID attribe ID.CNcomment:属性类型ID CNend
    \param[out] pstSettings Return attribte param.CNcomment:返回设置属性，根据enAttrID对应不同类型。 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_ATTR_ID_TYPE_E

    \par example
    \code
    \endcode
    */
    S32 (*av_get_attr)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_ATTR_ID_TYPE_E enAttrID, VOID* pstSettings);

    /**
    \brief Set attribte of AV instance. CNcomment:设置av属性 CNend
    \attention \n
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] enAttrID attribe ID.CNcomment:属性类型ID CNend
    \param[in] pstSettings attribte param.CNcomment:属性结构体指针，根据enAttrID对应不同类型 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_ATTR_ID_TYPE_E
    */
    S32 (*av_set_attr)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_ATTR_ID_TYPE_E enAttrID, VOID* const pstSettings);

    /**
    \brief Start AV play. CNcomment: 开始AV解码 CNend
    \attention \n
    Since the app does not manage the status, should stop first, and then renew settings, then start again.
    CNcomment: 由于应用经常没有管理好状态,在切频点之后,在start状态下start, 为了避免播放出不来,在start状态下start, 需要先stop,更新settings再start. CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:未绑定数据单元CNend
    \retval ::ERROR_AV_VID_AND_AUD_START_FAIL Video and audio start fail. CNcomment:音视频都启动失败CNend
    \retval ::ERROR_AV_AUD_START_FAIL Audio start fail but video start success. CNcomment:视频启动成功，音频启动失败CNend
    \retval ::ERROR_AV_VID_START_FAIL Audio start fail but video start success. CNcomment:音频启动成功，视频启动失败CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_start)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop AV play. CNcomment:停止AV解码CNend
    \attention \n
    This operation will not detach or close injecters. CNcomment: 该操作不会执行注入器的解绑定或关闭动作 CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_stop)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Pause video and audio play, real-time streaming does not support. CNcomment:暂停音视频解码, 实时流不支持sCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pause)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Resume video and audio play, real-time streaming does not support. CNcomment:恢复音视频解码, 实时流不支持sCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_resume)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Reset video and audio play. CNcomment:重置音视频缓冲到某个时间点CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] s64TimeMs Reset time, unit is ms.CNcomment:重置时间点,单位毫秒CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_reset)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, S64 s64TimeMs);

    /**
    \brief Start video play. CNcomment:启动视频解码CNend
    \attention \n
    Since the app does not manage the status, should stop first, and then renew settings, then start again.
    CNcomment: 由于应用经常没有管理好状态,在切频点之后,在start状态下start,  为了避免播放出不来,在start状态下start, 需要先stop,更新settings再start. CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:未绑定数据单元CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_start_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Pause video play, real-time streaming does not support. CNcomment:暂停视频解码, 实时流不支持sCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pause_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Freeze current picture, video decoding continues. CNcomment:视频解码继续，不更新显示CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] bFreeze Freeze or unfreeze video picture, ::TRUE freeze video picture, ::FALSE unfreeze video picture. CNcomment: 冻结或恢复视频CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_freeze_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, BOOL bFreeze);

    /**
    \brief Resume video play. CNcomment:恢复视频解码CNend
    \attention \n
    Resume from pause status.
    CNcomment: 从pause状态中恢复. CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_resume_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop video play. CNcomment:停止视频解码CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_stop_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Clear the picture on the screen and video data in the display buffer.
    CNcomment:清除视频显示buf中的数据,同时会清除屏幕上的显示,有些平台可能不支持CNend
    \attention \n
    You should call av_stop_video before call this function.
    CNcomment:
    需要video stop之后才能调用,(比如iframe 显示完毕) .
    CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_clear_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Start audio play. CNcomment:开始音频解码CNend
    \attention \n
    Since the app does not manage the status, should stop first, and then renew settings, then start again.
    CNcomment: 由于应用经常没有管理好状态,在切频点之后,在start状态下start,  为了避免播放出不来,在start状态下start, 需要先stop,更新settings再start. CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:未绑定数据单元CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_start_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Pause audio play, real-time streaming does not support. CNcomment:暂停音频解码，实时流不支持sCNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pause_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Resume audio play, real-time streaming does not support. CNcomment:恢复音频解码CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_resume_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop audio play. CNcomment:停止音频解码CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_stop_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Decode iframe data. CNcomment:iframe 数据解码CNend
    \attention \n
    Decode a ifame, wether renew screen depend on the current display mode.
    If pstCapPicture is null, the decoded I frames are displayed in the window,and do not need release memory; \n
    if pstCapPicture is not null, the information about I frames is reported, and need invoke ::av_release_iframe to release memory.
    CNcomment:
    解码一幅iframe, 是否更新视频显示取决于当前视频显示设置
    当pstCapPicture为空指针时，解完的I帧将在window上显示，不需释放内存，如果非空，则不会显示而是将I帧信息上报,同时I帧处理完毕后，需要调用av_release_iframe来释放I帧
    video 层的iframe可调用av_enable_video函数显示;av_disable_video隐藏
    video 层的iframe会在视频重新开始新的解码后被冲掉
    CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] pstIframeDacodeParams Iframe info.CNcomment:iframe解码参数CNend
    \param[in] pstCapPicture Iframe info.CNcomment:iframe解码参数CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_IFRAME_DECODE_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_decode_iframe)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle,
                            const AV_IFRAME_DECODE_PARAMS_S* const pstIframeDacodeParams, AV_VID_FRAMEINFO_S* pstCapPicture);

    /**
    \brief Release memory of I frame. CNcomment:释放I帧帧存CNend
    \attention \n
    If you call av_decode_iframe with non-null pstCapPicture, you need call this API to release the memory.
    CNcomment:如果调av_decode_iframe时pstCapPicture不为空，需要调用此接口来释放内存 CNend
    CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] pstCapPicture Pointer to the frame information.CNcomment:指针类型，释放的帧信息 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_VID_FRAMEINFO_S

    \par example
    \code
    \endcode
    */
    S32 (*av_release_iframe)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, const AV_VID_FRAMEINFO_S* pstCapPicture);

    /**
    \brief Open a injecter instance. CNcomment:打开一个注入实例CNend
    \attention \n
    None
    \param[out] phInjecter Return injecter handle.CNcomment:返回注入器句柄CNend
    \param[in] pstOpenParams Open param.CNcomment:iframe打开参数CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_injecter_open)(struct _AV_DEVICE_S* pstDev, HANDLE* const  phInjecter,
                            AV_INJECTER_OPEN_PARAMS_S* const pstOpenParams);

    /**
    \brief Close a injecter instance. CNcomment:关闭一个注入实例CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] pstCloseParams Close param.CNcomment:iframe关闭 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:参数错误CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_injecter_close)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                             AV_INJECTER_CLOSE_PARAMS_S* const pstCloseParams);

    /**
    \brief Attach injecter and AV handle. CNcomment:把一个注入器关联到decoder上去CNend
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
    1. 一个hAv 可以关联多个 hInjecter,
        可以边播放tuner ts流的视频,边注入pcm,或者边播放tuner ts 流的audio,边注入es video
        但是AV_CONTENT_TYPE_E 相同的hInjecter 只能有一个,
        就是音频通道只能关联一个hInjecter,视频通道也只能关联一个hInjecter.
    2. 如果hAv  相应通道没有关联hInjecter,那么它的数据将默认从tuner过来.
        假如某个通道上关联了hInjecter, 那么它的数据将优先于tuner的数据.
        如果设置了pcm 的 hInjecter, 那么认为音频数据是从injecter 过来,而不是tuner.
        如果设置了video es 的hInjecter,那么认为视频数据是从injecter过来,而不是tuner.
        如果关联的hInjecter 是往dmx注入数据,那么它将影响音视频两个通道的数据来源
        如果关联的hInjecter只是往decoder注入数据,那么它不会影响dmx的数据.也不会影响decoder 其他通道的数据
        比如关联了pcm 的hInjecter,将不会影响dmx & video通道的数据
    3. 单个通道(a/v) injecter 的设置不会影响其他通道
        比如关联了iframe的注入不会导致原来pcm播放的中断或者停顿.
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Detach injecter and AV handle. CNcomment:取消注入器关联CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_injecter_detach)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter);

    /**
    \brief Inject data. CNcomment:注入需要解码的数据CNend
    \attention \n
    The data will be injected to demux or decoder, depend on the data type.
    If the sample rate of PCM data is 16 bit, the data must be 4-bytes alignment.
    If TS data, the data must be a complete TS package.
    If PES data, the data must be a complete PES package.
    If es data which does not need to sync, the data must be a complete frame.
    If es data which need to sync, call av_inject_es_data, and input timestamp.
    CNcomment:
    根据注入数据的类型，可能是注往dmx也可能是注往decoder
    如果是16位采样的pcm数据,请按16位对齐注入
    如果是ts数据,需要以完整的ts包为单位注入
    如果是PES数据,需要以完整的pes 包为单位注入
    如果是不需要同步的es数据(不带时间戳),请以一整帧为单位注入
    如果是需要同步的es数据,请调用av_inject_es_data()函数注入,传入时间戳
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] pvData Data address, the address should be approprite byte aglinment depend on the platform.CNcomment:注入数据地址,为了提高速度，请根据各个平台情况采取合适的对齐方式CNend
    \param[in] u32Length Data length.CNcomment:数据长度 CNend
    \param[in] u32TimeoutMs Timeout in ms.CNcomment:超时时间, 单位毫秒 CNend

    \retval ::>0 Length of send data successful. CNcomment:成功发送的数据字节数 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
     获取下次注入缓冲区中的空闲Buffer地址指针和连续空闲Buffer的大小，
     填充数据后通过av_inject_write_complete 函数将数据推送到解码器 CNend
    \attention \n
    The buffer returned must be contiguous space, and buffer length must be a multipe of u32InjectMinLen;
    If the buffer is full, this interface should return fail, and the value of *puLength is 0;
    Must be paired with av_inject_write_complete, consider thread safety.
    CNcomment:
     此时并没有把的buf当循环buf使用,使用的是连续的空间,
     只保证buf大小是u32InjectMinLen的倍数,
     如果buffer已经满调用此接口应该返回失败，且puLength长度为0
     必须与av_inject_write_complete配对使用,调用要考虑线程安全
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] u32ReqLen Request data buffer len.CNcomment:期望取的数据长度 CNend
    \param[out] ppvBufFree Return free buffer address pointer.CNcomment:返回空闲空间的地址指针CNend
    \param[out] pu32FreeSize Return free buffer size.CNcomment:返回空间空间长度CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_freebuf)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter, U32 u32ReqLen,
                                 VOID** ppvBufFree, U32* pu32FreeSize);


    /**
    \brief After call av_inject_get_freebuf function and copy date to free buffer, then call this function to send to decoder.
    CNcomment:调用av_inject_get_freebuf获取空闲buffer并且拷贝好数据后，调用该函数送给解码器CNend
    \attention \n
    Must be paired with av_inject_get_freebuf, consider thread safety.
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] u32WriteSize Number of bytes that are written to the buffer.CNcomment:实际写入缓冲区的字节数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_write_complete)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                    U32 u32WriteSize, S64 s64Pts);

    /**
    \brief Get the buffer status of injecter
    CNcomment:获取内存注入方式的buf状态CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[out] pstBufStatus Return buffer status.CNcomment:返回缓存状态CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_buf_status)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                    AV_BUF_STATUS_S* const pstBufStatus);

    /**
    \brief Get the status of injecter
    CNcomment:获取注入器状态CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[out] pstStatus Return Injecter status.CNcomment:返回注入器状态CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_status)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                AV_INJECT_STATUS_S* const pstStatus);

    /**
    \brief Get the settings of injector
    CNcomment:获取注入器设置参数CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[out] pstSettings Return Injecter settings.CNcomment:返回注入器设置参数  CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_setting)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                 AV_INJECT_SETTINGS_S* const pstSettings);

    /**
    \brief Reset injecter buf
    CNcomment:复位注入buffer CNend
    \attention \n
    To aviod error, it is best to call in the decoder stopped state
    CNcomment:
    为了避免出错,最好在decoder停止状态下调用
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_reset_buf)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter);

    // TODO: 改函数不清楚具体作用，av_set_config已经包含此功能
    /**
    \brief Set PCM param
    CNcomment:设置PCM 参数CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] pstParams PCM param.CNcomment:PCM 参数CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid.CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid.CNcomment:空指针CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_PCM_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_set_pcm_params)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter,
                                    AV_PCM_PARAMS_S* const pstParams);

    // TODO: 改函数不清楚具体作用，av_set_config已经包含此功能
    /**
    \brief Set es param
    CNcomment:设置es  参数CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] pstParams ES param.CNcomment:ES 参数CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::ERROR_NOT_SUPPORTED Not support operation in current status. CNcomment:当前状态下不支持的操作CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    CNcomment:内存方式注入es数据CNend
    \attention \n
    None
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] pstEsData ES data.CNcomment:ES 数据CNend
    \param[in] u32TimeoutMs Timeout in ms.CNcomment:超时时间,单位毫秒CNend

    \retval ::>0 Length of send data successful. CNcomment:成功发送的数据字节数 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    CNcomment:中止数据注入CNend
    \attention \n
    Abort av_inject_es_data and av_inject_data.
    When timeout is not 0, av_inject_es_data and av_inject_data will be blocked, and av_inject_abort can break the blocking status, the inject operation will fail.
    CNcomment:
    终止av_inject_es_data(),av_inject_data().
    当av_inject_es_data(),av_inject_data().的超时时间不为0时,阻塞在里面,av_inject_abort()可以解除阻塞,立即退出.本次注入操作失败.
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] pstPesData ES data.CNcomment:ES 数据CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
     指定期望的缓存区类型,获取下次注入缓冲区中的空闲Buffer地址指针和连续空闲Buffer的大小，
     填充数据后通过av_inject_write_complete 函数将数据推送到解码器 CNend
    \attention \n
    The buffer returned must be contiguous space, and buffer length must be a multipe of u32InjectMinLen;
    If the buffer is full, this interface should return fail, and the value of *puLength is 0;
    Must be paired with av_inject_write_complete, consider thread safety.
    CNcomment:
     此时并没有把的buf当循环buf使用,使用的是连续的空间,
     只保证buf大小是u32InjectMinLen的倍数,
     如果buffer已经满调用此接口应该返回失败，且puLength长度为0
     必须与av_inject_write_complete配对使用,调用要考虑线程安全
    CNend
    \param[in] hInjecter Injecter handle.CNcomment:注入器句柄 CNend
    \param[in] u32ReqLen Request data buffer len.CNcomment:期望取的数据长度 CNend
    \param[in] eReqBufType Request buffer type.CNcomment:期望获取的缓冲区类型 CNend
    \param[out] ppvBufFree Return free buffer address pointer.CNcomment:返回空闲空间的地址指针CNend
    \param[out] pu32FreeSize Return free buffer size.CNcomment:返回空闲空间长度 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED  Injecter has not been opened.CNcomment:注入器没有打开CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_inject_get_freebuf_ex)(struct _AV_DEVICE_S* pstDev, const HANDLE hInjecter, U32 u32ReqLen,
                                    AV_INJECT_BUF_TYPE_E eReqBufType, VOID** ppvBufFree, U32* pu32FreeSize);

    /**
     \brief Acquire audio or video frame that after decode
    CNcomment:获取解码后的音频或视频帧数据CNend
     \attention \n
     None
     \param[in] hHandle vout window or aout track handle, vout window handle for get video frame, aout track handle for get audio frame .
     CNcomment:视频或音频句柄，获取视频帧用vout window句柄，获取音频帧用aout track句柄CNend
     \param[in] eFrameType Data type, video or audio.CNcomment:数据类型，视频或音频CNend
     \param[in] u32TimeoutMs Timeout in ms.CNcomment:超时时间,单位毫秒CNend
     \param[out] pFrame Information of acquiring frame, if eFrameType is ::AV_CONTENT_AUDIO, pFrame type is ::AV_AUD_FRAMEINFO_S, if eFrameType is ::AV_CONTENT_VIDEO, pFrame type is ::AV_VID_FRAMEINFO_S.
                    CNcomment:获取的音视频帧信息, 如果eFrameType 为::AV_CONTENT_AUDIO, pFrame 类型为::AV_AUD_FRAMEINFO_S, 如果eFrameType 为::AV_CONTENT_VIDEO, pFrame 类型为::AV_VID_FRAMEINFO_S CNend

     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
     \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
    */
    S32 (*av_acquire_frame)(struct _AV_DEVICE_S* pstDev, const HANDLE hHandle, AV_CONTENT_TYPE_E eFrameType, VOID* pFrame, U32 u32TimeoutMs);

    /**
     \brief Release audio or video frame that acquiring frome AV.
    CNcomment:释放获取的音视频帧数据CNend
     \attention \n
     None
     \param[in] hHandle vout window or aout track handle, vout window handle for get video frame, aout track handle for get audio frame .
     CNcomment:视频或音频句柄，获取视频帧用vout window句柄，获取音频帧用aout track句柄CNend
     \param[in] eFrameType Data type, video or audio.CNcomment:数据类型，视频或音频CNend
     \param[in] pFrame Information of acquiring frame, if eFrameType is ::AV_CONTENT_AUDIO, pFrame type is ::AV_AUD_FRAMEINFO_S, if eFrameType is ::AV_CONTENT_VIDEO, pFrame type is ::AV_VID_FRAMEINFO_S.
                    CNcomment:获取的音视频帧信息, 如果eFrameType 为::AV_CONTENT_AUDIO, pFrame 类型为::AV_AUD_FRAMEINFO_S, 如果eFrameType 为::AV_CONTENT_VIDEO, pFrame 类型为::AV_VID_FRAMEINFO_S CNend

     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
     \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
    */
    S32 (*av_release_frame)(struct _AV_DEVICE_S* pstDev, const HANDLE hHandle, AV_CONTENT_TYPE_E eFrameType, const VOID* pFrame);

    /**
    \brief AV set vdec buffer mode
    CNcomment:设置vdec的buffer分配方式CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV句柄 CNend
    \param[in] buffer mode.CNcomment:Buffer模式CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_set_buf_mode)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_FRAME_BUFFER_MODE_E eBufMode);

    /**
    \brief AV acquire user buffer
    CNcomment:给vdec配置外部buffer CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV句柄 CNend
    \param[in] pstBuf Buffer pointer.CNcomment:Buffer指针CNend
    \param[in] u32Cnt Buffer counter.CNcomment:Buffer数量CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_acquire_user_buf)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_USER_BUFFER_S* pstBuf, U32 u32Cnt);

    /**
    \brief AV acquire user buffer
    CNcomment:vdec 释放外部buffer CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV句柄 CNend
    \param[in] pstBuf Buffer pointer.CNcomment:Buffer指针CNend
    \param[in] u32Cnt Buffer counter.CNcomment:Buffer数量CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_release_user_buf)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_USER_BUFFER_S* pstBuf, U32 u32Cnt);

    /**
    \brief AV format change CNcomment:AV制式切换CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle. CNcomment:AV句柄 CNend
    \param[in] u32Width format width. CNcomment:制式宽度 CNend
    \param[in] u32Height format height. CNcomment:制式高度 CNend
    \param[in,out] pbVideoBypass video bypass flag.CNcomment:video是否透传标志CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_format_change)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, U32* pu32Width, U32* pu32Height, BOOL* pbVideoBypass);

    /**
    \brief AV sync frame
    CNcomment:获取AV帧同步信息CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV句柄 CNend
    \param[in] pvFrame frame pointer.CNcomment:帧指针CNend
    \param[in] pstSyncRef sync ref info.CNcomment:同步参考信息CNend
    \param[in,out] pstSyncInfo sync info.CNcomment:同步信息CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_sync_frame)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, const VOID* pvFrame, const AV_SYNC_REF_S* pstSyncRef, AV_SYNC_INFO_S* pstSyncInfo);

    /**
    \brief AV register audio lib
    CNcomment:注册外挂音频库CNend
    \attention \n
    None
    \param[in] pstDev AV handle.CNcomment:AV句柄 CNend
    \param[in] ps8Audlib audlib name.CNcomment:音频库名称CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_ES_DATA_S

    \par example
    \code
    \endcode
    */
    S32 (*av_register_audiolib)(struct _AV_DEVICE_S* pstDev, const S8* ps8Audlib);

    /**
    \brief AV invoke function, extend other function by user.
    CNcomment:invoke 扩展接口，用于用户私有功能扩展CNend
    \attention \n
    None
    \param[in] pstDev AV handle.CNcomment:AV句柄 CNend
    \param[in] hAvHandle AV handle.CNcomment:AV句柄 CNend
    \param[in] eCmd Invoke ID, defined is ::AV_INVOKE_E.CNcomment:Invoke ID, 定义详见 ::AV_INVOKE_E CNend
    \param[in,out] pArg Command parameter.CNcomment:命令参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_INVOKE_E

    \par example
    \code
    \endcode
    */
    S32 (*av_invoke)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, AV_INVOKE_E eCmd, VOID* pArg);

    /**
    \brief AV set HDR10 info function.
    CNcomment:设置HDR10信息CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] pstHDR10Info HDR10 info.CNcomment:HDR10 信息 CNend
    \param[in] bPaddingHdrInfo if need padding HDR information to frame information.CNcomment:是否需要填充HDR信息到帧信息中 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_VIDEO_HDR10_INFO_S

    \par example
    \code
    \endcode
    */
    S32 (*av_set_hdr10_info)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, const AV_VIDEO_HDR10_INFO_S* pstHDR10Info, BOOL bPaddingHdrInfo);

    /**
    \brief AV set metadata info function.
    CNcomment:设置Metadata信息CNend
    \attention \n
    None
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \param[in] pstMetaDataInfo Metadata info.CNcomment:需要设置的Metadata信息 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE other error.CNcomment:其它错误 CNend
    \see \n
    ::AV_VIDEO_METADATA_INFO_S

    \par example
    \code
    \endcode
    */
    S32 (*av_set_metadata_info)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle, const AV_VIDEO_METADATA_INFO_S* pstMetaDataInfo);

    /**
    \brief Start video to prepare play mode, which just demux ts stream. CNcomment: 启动视频播放进入预播放(PERPLAY)状态 CNend
    \attention \n
    PREPLAY mode just dsemux ts, is used for fullband. CNcomment: 预播放状态仅仅做TS的解复用，用于Fullband切台CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:未绑定数据单元CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pre_start_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop video to prepare stop mode,the interface is reserved for future use. CNcomment: 停止视频播放进入预停止(PERSTOP)状态，该接口保留备用 CNend
    \attention \n
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_SUPPORTED  not support for the moment.CNcomment:暂不支持。CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pre_stop_video)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Start audio to prepare play mode, which just demux ts stream. CNcomment: 启动音频播放进入预播放(PERPLAY)状态 CNend
    \attention \n
    PREPLAY mode just dsemux ts, is used for fullband. CNcomment: 预播放状态仅仅做TS的解复用，用于Fullband切台CNend
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_AV_PLAYER_NOT_CREATED  AV instance has not been created.CNcomment:实例未创建CNend
    \retval ::ERROR_AV_INJECT_NOT_OPENED Not attach inject. CNcomment:未绑定数据单元CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*av_pre_start_audio)(struct _AV_DEVICE_S* pstDev, const HANDLE hAvHandle);

    /**
    \brief Stop audio to prepare stop mode, the interface is reserved for future use. CNcomment: 停止音频播放进入预停止(PERSTOP)状态，该接口保留备用 CNend
    \attention \n
    \param[in] hAvHandle AV handle.CNcomment:AV 句柄 CNend
    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_SUPPORTED  not support for the moment.CNcomment:暂不支持。CNend
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
\brief direct get av device api, for linux and android.CNcomment:获取av设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get av device api，for linux and andorid.
CNcomment:获取av设备接口，linux和android平台都可以使用. CNend
\retval  av device pointer when success.CNcomment:成功返回av设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::AV_DEVICE_S

\par example
*/
AV_DEVICE_S* getAVDevice();

/**
\brief  Open HAL AV play module device.CNcomment:打开HAL播放器模块设备 CNend
\attention \n
Open HAL AV play module device(for compatible Android HAL).
CNcomment:打开HAL播放器模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice AV play device structure.CNcomment:播放器设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功 CNend
\retval ::FAILURE error.CNcomment:其它错误 CNend
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
\brief Close HAL AV play module device.CNcomment:关闭HAL播放器模块设备 CNend
\attention \n
Close HAL AV play module device(for compatible Android HAL).
CNcomment:关闭HAL播放器模块设备(为兼容Android HAL). CNend
\param[in] pstDevice AV device structure.CNcomment:AV设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功 CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
