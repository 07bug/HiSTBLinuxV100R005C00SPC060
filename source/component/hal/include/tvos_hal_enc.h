/**
 * \file
 * \brief Describes the information about the enc module.
 */

#ifndef __TVOS_HAL_ENC_H__
#define __TVOS_HAL_ENC_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include "tvos_hal_type.h"
#include "tvos_hal_av.h"
#include "tvos_hal_vout.h"
#include "tvos_hal_source.h"

#ifdef ANDROID_HAL_MODULE_USED
#include <hardware/hardware.h>
#else
#include "tvos_hal_linux_adapter.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*************************** Macro Definition ****************************/
/** \addtogroup     HAL_ENC */
/** @{ */  /** <!-- [HAL_ENC] */

#define ENC_HARDWARE_MODULE_ID "encode"
#define ENC_HARDWARE_ENC0      "enc0"

/**enc module file max len.*//** CNcomment:编码模块定义的文件名最大长度 */
#define ENC_FILE_NAME_LENGTH   (255)

/** @} */  /** <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_ENC */
/** @{ */  /** <!-- [HAL_ENC] */

/** encoder type *//** CNcomment:编码器类型 */
typedef enum _ENC_ENCODER_TYPE_E
{
    ENC_ENCODE_NONE  = 0,
    ENC_ENCODE_VIDEO = 1,                 /**<Video or OSD + Video*//**<CNcomment:Video 或OSD+Video*/
    ENC_ENCODE_AUDIO = 1 << 1,            /**<Audio */ /**<CNcomment:Audio */
    ENC_ENCODE_BUTT
}  ENC_ENCODER_TYPE_E;

/** enc output type *//** CNcomment:编码器输出类型. */
typedef enum _ENC_OUTPUT_TYPE_E
{
    ENC_OUTPUT_MEM = 0,                   /**<output to memory *//**<CNcomment:放在内存里面.通过 enc_acquire_stream() 读取 */
    ENC_OUTPUT_FILE,                      /**<output to file *//**<CNcomment:写到文件里面 */
    ENC_OUTPUT_BUTT
}  ENC_OUTPUT_TYPE_E;

/** color space *//** CNcomment:色彩空间 */
typedef enum _ENC_COLOR_TYPE_E
{
    ENC_COLOR_TYPE_NONE = 0,              /**<ingore, hal auto*//**<CNcomment:应用不关心,HAL 自己决定 */
    ENC_COLOR_TYPE_YUV_420,               /**<YUV420*//**<CNcomment:YUV420 */
    ENC_COLOR_TYPE_YUV_422,               /**<YUV422*//**<CNcomment:YUV422 */
    ENC_COLOR_TYPE_YUV_444,               /**<YUV444*//**<CNcomment:YUV444 */
    ENC_COLOR_TYPE_BUTT
}  ENC_COLOR_TYPE_E;

/** store type *//** CNcomment:存储格式*/
typedef enum _ENC_STORE_TYPE_E
{
    ENC_STORE_TYPE_NONE = 0,              /**<ingore, hal auto*/ /**<CNcomment:应用不关心,HAL 自己决定 */
    ENC_STORE_TYPE_SEMIPLANNAR,           /**<Semi-planar*//**<CNcomment:Semi-planar */
    ENC_STORE_TYPE_PLANNAR,               /**<Planar mode*//**<CNcomment:Planar mode, 将Y.U.V的三个份量分别存放在不同的矩阵中 */
    ENC_STORE_TYPE_PACKAGE,               /**<Package mode*//**<CNcomment:Package mode,  将Y.U.V值储存成Macro Pixels阵列,和RGB的存放方式类似*/
    ENC_STORE_TYPE_BUTT
}  ENC_STORE_TYPE_E;

/** Storage sequence of package YUV *//** CNcomment:YUV包存储系列*/
typedef enum _ENC_YUV_PACKAGE_SEQ_E
{
    ENC_PACKAGE_NONE = 0,        /**<ingore, hal auto*/ /**<CNcomment:应用不关心,HAL 自己决定 */

    ENC_PACKAGE_Y0UY1V ,        /**<Y0U0Y1V0 *//**<CNcomment:Y0U0Y1V0*/
    ENC_PACKAGE_Y0UVY1 ,        /**<Y0U0V0Y1 *//**<CNcomment:Y0U0V0Y1*/
    ENC_PACKAGE_Y0Y1UV ,        /**<Y0Y1U0V0 *//**<CNcomment:Y0Y1U0V0*/
    ENC_PACKAGE_Y0Y1VU ,        /**<Y0Y1V0U0 *//**<CNcomment:Y0Y1V0U0*/
    ENC_PACKAGE_Y0VY1U ,        /**<Y0V0Y1U0 *//**<CNcomment:Y0V0Y1U0*/
    ENC_PACKAGE_Y0VUY1 ,        /**<Y0V0U0Y1 *//**<CNcomment:Y0V0U0Y1*/

    ENC_PACKAGE_UY0Y1V ,        /**<U0Y0Y1V0 *//**<CNcomment:U0Y0Y1V0*/
    ENC_PACKAGE_UY0VY1 ,        /**<U0Y0V0Y1 *//**<CNcomment:U0Y0V0Y1*/
    ENC_PACKAGE_UY1Y0V ,        /**<U0Y1Y0V0 *//**<CNcomment:U0Y1Y0V0*/
    ENC_PACKAGE_UY1VY0 ,        /**<U0Y1V0Y0 *//**<CNcomment:U0Y1V0Y0*/
    ENC_PACKAGE_UVY1Y0 ,        /**<U0V0Y1Y0 *//**<CNcomment:U0V0Y1Y0*/
    ENC_PACKAGE_UVY0Y1 ,        /**<U0V0Y0Y1 *//**<CNcomment:U0V0Y0Y1*/

    ENC_PACKAGE_Y1UY0V ,        /**<Y1U0Y0V0 *//**<CNcomment:Y1U0Y0V0*/
    ENC_PACKAGE_Y1UVY0 ,        /**<Y1U0V0Y0 *//**<CNcomment:Y1U0V0Y0*/
    ENC_PACKAGE_Y1Y0UV ,        /**<Y1Y0U0V0 *//**<CNcomment:Y1Y0U0V0*/
    ENC_PACKAGE_Y1Y0VU ,        /**<Y1Y0V0U0 *//**<CNcomment:Y1Y0V0U0*/
    ENC_PACKAGE_Y1VY0U ,        /**<Y1V0Y0U0 *//**<CNcomment:Y1V0Y0U0*/
    ENC_PACKAGE_Y1VUY0 ,        /**<Y1V0U0Y0 *//**<CNcomment:Y1V0U0Y0*/

    ENC_PACKAGE_VY0Y1U ,        /**<V0Y0Y1U0 *//**<CNcomment:V0Y0Y1U0*/
    ENC_PACKAGE_VY0UY1 ,        /**<V0Y0U0Y1 *//**<CNcomment:V0Y0U0Y1*/
    ENC_PACKAGE_VY1Y0U ,        /**<V0Y1Y0U0 *//**<CNcomment:V0Y1Y0U0*/
    ENC_PACKAGE_VY1UY0 ,        /**<V0Y1U0Y0 *//**<CNcomment:V0Y1U0Y0*/
    ENC_PACKAGE_VUY1Y0 ,        /**<V0U0Y1Y0 *//**<CNcomment:V0U0Y1Y0*/
    ENC_PACKAGE_VUY0Y1 ,        /**<V0U0Y0Y1 *//**<CNcomment:V0U0Y0Y1*/

    ENC_PACKAGE_BUTT
} ENC_YUV_PACKAGE_SEQ_E;

/** Field type *//** CNcomment:场类型*/
typedef enum _ENC_VID_FIELD_TYPE_E
{
    ENC_VID_FIELD_ALL = 0,             /**<frame *//**<CNcomment:帧*/
    ENC_VID_FIELD_TOP,                 /**<top field *//**<CNcomment:顶场*/
    ENC_VID_FIELD_BOTTOM,              /**<bottom field *//**<CNcomment:底场*/
    ENC_VID_FIELD_BUTT
} ENC_VID_FIELD_TYPE_E ;

/** H.264 NALU type *//** CNcomment:H.264 NALU 类型*/
typedef enum _ENC_H264_NALU_TYPE_E
{
    ENC_H264_NALU_P_SLICE = 0,         /**<P slice NALU *//**<CNcomment:P slice NALU*/
    ENC_H264_NALU_I_SLICE,             /**<I slice NALU *//**<CNcomment:I slice NALU*/
    ENC_H264_NALU_SEI,                 /**<SEI NALU *//**<CNcomment:SEI NALU*/
    ENC_H264_NALU_SPS,                 /**<SPS NALU *//**<CNcomment:SPS NALU*/
    ENC_H264_NALU_PPS,                 /**<PPS NALU *//**<CNcomment:PPS NALU*/
    ENC_H264_NALU_BUTT
} ENC_H264_NALU_TYPE_E ;

/** H.263 NALU type *//** CNcomment:H.263 NALU 类型*/
typedef enum _ENC_H263_NALU_TYPE_E
{
    ENC_H263_NALU_P_SLICE = 0,         /**<P slice NALU *//**<CNcomment:P slice NALU*/
    ENC_H263_NALU_I_SLICE,             /**<I slice NALU *//**<CNcomment:I slice NALU*/
    ENC_H263_NALU_SEI,                 /**<SEI NALU *//**<CNcomment:SEI NALU*/
    ENC_H263_NALU_SPS,                 /**<SPS NALU *//**<CNcomment:SPS NALU*/
    ENC_H263_NALU_PPS,                 /**<PPS NALU *//**<CNcomment:PPS NALU*/
    ENC_H263_NALU_BUTT
} ENC_H263_NALU_TYPE_E ;

/** JPEG package type *//** CNcomment:JPEG 打包类型*/
typedef enum _ENC_JPEG_PACK_TYPE_E
{
    ENC_JPEG_PACK_ECS = 0,             /**<ECS package *//**<CNcomment:ECS包*/
    ENC_JPEG_PACK_APP,                 /**<APP package *//**<CNcomment:APP包*/
    ENC_JPEG_PACK_VDO,                 /**<VDO package *//**<CNcomment:VDO包*/
    ENC_JPEG_PACK_PIC,                 /**<PIC package *//**<CNcomment:PIC包*/
    ENC_JPEG_PACK_TYPE_BUTT
} ENC_JPEG_PACK_TYPE_E;

/** MPEG4 package type *//** CNcomment:MPEG4 打包类型*/
typedef enum _ENC_MPEG4_PACK_TYPE_E
{
    ENC_MPEG4_PACK_VO = 0,             /**<VO package *//**<CNcomment:VO包*/
    ENC_MPEG4_PACK_VOS,                /**<VOS package *//**<CNcomment:VOS包*/
    ENC_MPEG4_PACK_VOL,                /**<VOL package *//**<CNcomment:VOL包*/
    ENC_MPEG4_PACK_VOP,                /**<VOP package *//**<CNcomment:VOP包*/
    ENC_MPEG4_PACK_SLICE,              /**<Slice package *//**<CNcomment:Slice包*/
    ENC_MPEG4_PACK_BUTT
} ENC_MPEG4_PACK_TYPE_E;

/**HEVC NALU type*//**CNcomment: HEVC NALU类型 */
typedef enum _ENC_HEVCE_NALU_TYPE_E
{
    ENC_HEVC_NALU_P_SLICE = 0,       /**<P slice NALU*/
    ENC_HEVC_NALU_I_SLICE,           /**<I slice NALU*/
    ENC_HEVC_NALU_VPS,               /**<VPS NALU*/
    ENC_HEVC_NALU_SPS,               /**<SPS NALU*/
    ENC_HEVC_NALU_PPS,               /**<PPS NALU*/
    ENC_HEVC_NALU_SEI,               /**<SEI NALU*/
    ENC_HEVC_NALU_BUTT
} ENC_HEVC_NALU_TYPE_E;

/**enc source type*//** CNcomment:数据来源类型 */
typedef enum _ENC_SOURCE_TYPE_E
{
    ENC_SOURCE_NONE = 0,               /**<none, can't connect or disconnect *//**<CNcomment:未连接,或者断开连接*/
    ENC_SOURCE_DECODER,                /**<bind av handle, get av handle data *//**<CNcomment: 绑定解码器,取解码以后的数据*/
    ENC_SOURCE_MEM,                    /**<app inject data *//**<CNcomment:应用主动注入数据*/
    ENC_SOURCE_FILE,                   /**<file data *//**<CNcomment:从文件读数据*/
    ENC_SOURCE_AOUT,                   /**<aout data, bind aout ID *//**<CNcomment:混音之后的数据，绑定AOUT_ID_E*/
    ENC_SOURCE_VOUT,                   /**<vout data, bind vout channel  VOUT_DISPLAY_CHANNEL_E*//**<CNcomment:display数据，绑定vout通道VOUT_DISPLAY_CHANNEL_E*/
    ENC_SOURCE_SOURCE,                 /**<source data, bind source SOURCE_ID_E*//**<CNcomment:绑定输入源SOURCE_ID_E*/
    ENC_SOURCE_BUTT,
} ENC_SOURCE_TYPE_E;

/**Enc output stream format,  isn't necessary to support all types, capability inquire by enc_get_capability*/
/** CNcomment:编码输出流格式, 不是必须支持所有的类型,具体 由enc_get_capability()返回支持情况 */
typedef enum _ENC_OUTPUT_STREAM_FORMAT_E
{
    ENC_OUTPUT_STREAM_FORMAT_NONE = 0,
    ENC_OUTPUT_STREAM_FORMAT_TS   = 1,                                  /**<TS type */ /**<CNcomment:TS类型*/
    ENC_OUTPUT_STREAM_FORMAT_ES   = 1 << 1                              /**<ES type */ /**<CNcomment:ES类型*/
} ENC_OUTPUT_STREAM_FORMAT_E;

/**enc source params*//** CNcomment:数据来源类型对应的参数 */
typedef struct _ENC_SOURCE_PARAMS_S
{
    ENC_SOURCE_TYPE_E          enSourceType;                            /**<source type *//**<CNcomment:源类型*/
    union _ENC_SOURCE_U
    {
        HANDLE                 hAv;                                     /**<av handle map ENC_SOURCE_DECODER*//**<CNcomment:av句柄，对应ENC_SOURCE_DECODER的参数*/
        CHAR                   aFileName[ENC_FILE_NAME_LENGTH + 1];     /**<file name map ENC_SOURCE_FIL*//**<CNcomment:文件名,对应m_source_type == ENC_SOURCE_FILE的参数*/
        AOUT_ID_E              enAoutId;                                /**<aout ID map ENC_SOURCE_AOUT*//**<CNcomment:aout id，对应ENC_SOURCE_AOUT的参数*/
        VOUT_DISPLAY_CHANNEL_E enDisplayChanel;                         /**<vout display channel map ENC_SOURCE_VOUT*//**<CNcomment:vout display通道，对应ENC_SOURCE_VOUT的参数*/
        SOURCE_ID_E            enSourceId;                              /**<source id map ENC_SOURCE_SOURCE*//**<CNcomment:输入源ID，对应ENC_SOURCE_SOURCE的参数*/
        U32                    u32Dummy;                                /**<Reserve *//**<CNcomment:保留*/
    } uSource;
} ENC_SOURCE_PARAMS_S;

/**enc output params*//** CNcomment:编码器输出参数 */
typedef struct _ENC_OUTPUT_PARAMS_S
{
    ENC_OUTPUT_TYPE_E       enOutputType;                               /**<output type *//**<CNcomment:输出类型*/
    union enc_output_u
    {
        CHAR                aFileName[ENC_FILE_NAME_LENGTH + 1 ];       /**<file name map ENC_OUTPUT_FILE */ /**<CNcomment:文件名，ENC_OUTPUT_FILE对应的参数*/
        U32                 u32Dummy;                                   /**<memory map ENC_OUTPUT_MEM *//**<CNcomment:数据放在内存里面.通过 enc_acquire_stream() 读取*/
    } uOutput;
} ENC_OUTPUT_PARAMS_S;

/**audio encoder format support capability *//** CNcomment:音频编码器格式支持能力 */
typedef struct _ENC_AENC_SUPPORT_S
{
    BOOL                    bSupportedDecType;                          /**<Whether support the format, TRUE means exist *//**<CNcomment:是否支持该音频编码器格式*/
    U32                     u32Number;                                  /**<codec number *//**<CNcomment:编码器个数*/
    U32                     u32Dummy;                                   /**<reserve *//**<CNcomment:保留*/
} ENC_AENC_SUPPORT_S;

/**audio encoder capability *//** CNcomment:音频编码器能力 */
typedef struct _ENC_AENC_CAPABILITY_S
{
    BOOL                    bExist;                                     /**<Whether exist audio encoder, TRUE means exist *//**<CNcomment:是否存在音频编码器*/
    ENC_AENC_SUPPORT_S      astStreamTypeArr[AV_AUD_STREAM_TYPE_BUTT];  /**<audio encoder type, index by  AV_AUD_STREAM_TYPE_E*//**<CNcomment:支持的编码类型. 以AV_AUD_STREAM_TYPE_E变量为索引*/
} ENC_AENC_CAPABILITY_S;

/**video encoder format support capability *//** CNcomment:视频编码器格式支持能力 */
typedef struct _ENC_VENC_SUPPORT_S
{
    BOOL                    bSupportedDecType;                          /**<Whether support the format, TRUE means exist *//**<CNcomment:是否支持该视频编码器格式*/
    VDEC_RESO_LEVEL_E       enDecCapLevel;                              /**<reso capability *//**<CNcomment:支持的分辨率能力*/
    U32                     u32Number;                                  /**<codec number *//**<CNcomment:编码器个数*/
    U32                     u32Fps;                                     /**<codec fps *//**<CNcomment:编码器帧率*/
    U32                     u32Dummy;                                   /**<reserve *//**<CNcomment:保留*/
} ENC_VENC_SUPPORT_S;

/**video encoder capability *//** CNcomment:视频编码器能力 */
typedef struct _ENC_VENC_CAPABILITY_S
{
    BOOL                    bExist;                                     /**<Whether exist video encoder, TRUE means exist *//**<CNcomment:是否存在视频编码器*/
    ENC_ENCODER_TYPE_E      enType;                                     /**<Video encoder  type, support OR operate *//**<CNcomment:视频编码器类型，支持或操作*/
    ENC_VENC_SUPPORT_S      astVencSupport[AV_VID_STREAM_TYPE_BUTT];    /**<Video encoder format capability *//**<CNcomment:视频编码器格式支持能力*/
} ENC_VENC_CAPABILITY_S;

/**encoder capability *//** CNcomment:编码器能力 */
typedef struct _ENC_CAPABILITY_S
{
    ENC_OUTPUT_STREAM_FORMAT_E      enOutputStreamFormat;               /**<venc output stream format, support OR operate *//**<CNcomment:支持的输出流格式，支持或操作*/
    ENC_AENC_CAPABILITY_S           stAencArr;                          /**<venc aenc capability desc *//**<CNcomment:音频编码能力描述*/
    ENC_VENC_CAPABILITY_S           stVencArr;                          /**<venc venc capability desc *//**<CNcomment:视频编码能力描述*/
} ENC_CAPABILITY_S;

/** aenc  settings *//** CNcomment:音频编码器设置参数*/
typedef struct _ENC_AENC_SETTINGS_S
{
    ENC_SOURCE_PARAMS_S  stSourceParams;                                /**<source params *//**<CNcomment:编码源参数*/
    ENC_OUTPUT_PARAMS_S  stOutputParams;                                /**<output params *//**<CNcomment:编码输出参数*/
    ENC_OUTPUT_STREAM_FORMAT_E  enOutputStreamFormat;                   /**<output format *//**<CNcomment:编码输出格式*/
    AV_AUD_STREAM_TYPE_E enType;                                        /**<enc format *//**<CNcomment:编码格式*/
    U32                  u32BufSize;                                    /**<enc buffer size *//**<CNcomment:编码器缓存大小, 0表示不关注*/
    U32                  u32Channels;                                   /**<audio track number *//**<CNcomment:声道数. 声道数:1,2 ,0表示不关注*/
    U32                  u32BitPerSample;                               /**<bit width *//**<CNcomment: 位宽.音频每个采样点所占的比特数, 如:8bit,16bit ,0表示不关注*/
    U32                  u32SampleRate;                                 /**<sample rate *//**<CNcomment:采样率.(32000,44100,48000 ),0表示不关注*/
    BOOL                 bInterleaved;                                  /**<Whether interleave *//**<CNcomment:是否开启交织模式*/
    U32                  u32SamplePerFrame;                             /**<sample per frame *//**<CNcomment:每帧采样点*/
} ENC_AENC_SETTINGS_S;

/** venc  settings *//** CNcomment:视频编码器设置参数*/
typedef struct _ENC_VENC_SETTINGS_S
{
    ENC_SOURCE_PARAMS_S         stSourceParams;                         /**<source params *//**<CNcomment:编码源参数*/
    ENC_OUTPUT_PARAMS_S         stOutputParams;                         /**<output params *//**<CNcomment:编码输出参数*/
    ENC_OUTPUT_STREAM_FORMAT_E  enOutputStreamFormat;                   /**<output format *//**<CNcomment:编码输出格式*/
    AV_VID_STREAM_TYPE_E        enType;                                 /**<enc format *//**<CNcomment:编码格式*/
    U32                         u32Width;                               /**<width *//**<CNcomment:编码后图像的宽度*/
    U32                         u32Height;                              /**<height *//**<CNcomment 编码后图像的高度*/
    U32                         bInterleaved;                           /**<Whether interleave *//**<CNcomment:是否开启交织模式*/
    U32                         u32OutputFrameRate;                     /**<enc output frame rate *//**<CNcomment编码后输出帧率,m_frame_rate =实际帧率x1000*/
    U32                         u32InputFrameRate;                      /**<enc input frame rate, only for mem and file, zero for auto *//**<CNcomment编码输入帧率,用于内存和文件输入类型，0表示由HAL自己决定*/
    U32                         u32BufSize;                             /**<buffer size, zero means ignore *//**<CNcomment:编码器缓存大小 , 如果是0, hdi  内部处理*/
    ENC_COLOR_TYPE_E            enColorType;                            /**<enc output format *//**<CNcomment:编码输出格式*/
    ENC_STORE_TYPE_E            enStoreType;                            /**<store type *//**<CNcomment:存储类型*/
    ENC_YUV_PACKAGE_SEQ_E       enPackageSeq;                           /**<package YUV sequence type *//**<CNcomment:YUV包序列*/
    BOOL                        bSliceSplit;                            /**<Whether slice split, FALSE means disable *//**<CNcomment:是否使能分割slice , FALSE:disable, TRUE:enable*/
    U32                         u32SplitSize;                           /**<slice split size *//**<CNcomment: 分割的大小, JPGE下以MCU为单位,H264或者MP4以字节为单位, H263不关心*/
    U32                         u32JpegQl;                              /**<Jpeg quality *//**<CNcomment:GFX_IMAGE_QUALITY_LEVEL_MIN, GFX_IMAGE_QUALITY_LEVEL_MAX. 设置为:0,表示忽略,如非JPGE格式*/
    U32                         u32BitRate;                             /**<Bit rate *//**<CNcomment:目标码率: 1080P 5M以上, 720P 3M以上, 576P 2M 左右. 0 是hdi 内部处理*/
    U32                         u32Gop;                                 /**<Group Of Picture *//**<CNcomment:画面组Group Of Picture. 转码/转屏场景下建议设置为30~100 以内;可视电话场景下建议设置为100~300.  0 是HAL 内部处理*/
    U32                         u32MaxQp;                               /**<quantization parameter *//**<CNcomment: 最大量化参数(quantization parameter) , 例如:48.  0 是HAL 内部处理*/
    U32                         u32MinQp;                               /**<quantization parameter *//**<CNcomment:最小量化参数(quantization parameter) .例如: 16 .  0 是HAL 内部处理*/
    BOOL                        bQuickEncode;                           /**<Whether enable quick encoder *//**<CNcomment:是否使能快速编码模式, 0:disable; 非零:enable*/
} ENC_VENC_SETTINGS_S;

/**aenc and venc setting *//** CNcomment:音视频编码器设置参数*/
typedef struct _ENC_SETTINGS_S
{
    ENC_AENC_SETTINGS_S stAencSettings;                                 /**<aenc setting *//**<CNcomment:音频编码设置*/
    ENC_VENC_SETTINGS_S stVencSettings;                                 /**<venc setting *//**<CNcomment:视频编码设置*/
} ENC_SETTINGS_S;

/**aenc source attr, only for inject mode*//** CNcomment:待编码的音频源属性.仅在注入模式下使用 */
typedef struct _ENC_AENC_DATA_S
{
    U32                        u32Channels;                             /**<audio track number *//**<CNcomment: 声道数*/
    BOOL                       bInterleaved;                            /**<Whether interleave *//**<CNcomment:是否开启交织模式*/
    U32                        u32BitPerSample;                         /**<bit width *//**<CNcomment 位宽*/
    U32                        u32SampleRate;                           /**<sample rate *//**<CNcomment采样率*/
    U32                        u32SamplesPerPrame;                      /**<PCM sample number *//**<CNcomment PCM 数据采样点数量*/
    U32                        u32FrameIndex;                           /**<frame index *//**<CNcomment  帧序号*/
    U64                        u64Pts;                                  /**<pts unit 90kHz *//**<CNcomment: 时间戳,  以90kHz 为单位*/
    VOID*                      pBuffer;                                 /**<buffer ptr *//**<CNcomment: 数据缓冲指针 */
    U32                        u32Length;                               /**<data length *//**<CNcomment: 数据长度*/
} ENC_AENC_DATA_S;

/**video  addr*//** CNcomment:视频地址 */
typedef struct _ENC_VID_FRAME_ADDR_S
{
    U32                        u32YAddr;              /**<y addr *//**<CNcomment:  Y分量数据的地址*/
    U32                        u32CAddr;              /**<c addr *//**<CNcomment:  C分量数据的地址*/
    U32                        u32CrAddr;             /**<cr addr *//**<CNcomment:  Cr分量数据的地址*/
    U32                        u32YStride;            /**<y stride *//**<CNcomment:  Y分量数据的跨幅*/
    U32                        u32CStride;            /**<c stride *//**<CNcomment:  C分量数据的跨幅*/
    U32                        u32CrStride;           /**<cr stride *//**<CNcomment:  Cr分量数据的跨幅*/
} ENC_VID_FRAME_ADDR_S;

/**video source data *//** CNcomment:待编码的视频源 属性.仅在注入模式下使用 */
typedef struct _ENC_VENC_DATA_S
{
    AV_VID_STREAM_TYPE_E        enType;               /**<video encoder type *//**<CNcomment: 编码格式*/
    U32                         u32Width;             /**<width *//**<CNcomment:编码后图像的宽度*/
    U32                         u32Height;            /**<height *//**<CNcomment 编码后图像的高度*/
    BOOL                        bInterleaved;         /**<Whether interleave *//**<CNcomment:是否开启交织模式*/
    U32                         u32FrameRate;         /**<frame rate *//**<CNcomment:   帧率,m_frame_rate =实际帧率x1000*/
    ENC_COLOR_TYPE_E            enColorType;          /**<color type *//**<CNcomment:  色彩类型*/
    ENC_STORE_TYPE_E            enStoreType;          /**<store type *//**<CNcomment:  存储类型*/
    ENC_YUV_PACKAGE_SEQ_E       enPackageSeq;         /**<package YUV sequence *//**<CNcomment:  package YUV存放顺序*/
    ENC_VID_FIELD_TYPE_E        enFieldType;          /**<field type *//**<CNcomment:  场类型*/
    AV_3D_FORMAT_E              en3dFormat;           /**<3d format *//**<CNcomment:  3d格式*/
    BOOL                        bTopFieldFirst;       /**<top field first *//**<CNcomment:  顶场优先,非零:优先*/
    U32                         u32FrameIndex;        /**<frame index *//**<CNcomment:  帧序号*/
    U64                         u64Pts;               /**<pts unit 90kHz *//**<CNcomment: 时间戳,  以90kHz 为单位*/
    ENC_VID_FRAME_ADDR_S        stAddr;               /**<vid frame addr *//**<CNcomment: 视频帧地址*/
} ENC_VENC_DATA_S;

/**video data type *//** CNcomment:video数据类型 */
typedef struct  _ENC_VID_DATA_TYPE_S
{
    AV_VID_STREAM_TYPE_E        enType;               /**<video encoder type *//**<CNcomment: 编码格式*/
    union _ENC_DATA_TYPE_U
    {
        ENC_JPEG_PACK_TYPE_E    enJpeg;               /**<Jpeg *//**<CNcomment: Jpeg*/
        ENC_MPEG4_PACK_TYPE_E   enMpeg4;              /**<Mpeg4 *//**<CNcomment: Mpeg4*/
        ENC_H263_NALU_TYPE_E    enH263;               /**<H263 *//**<CNcomment: H263*/
        ENC_H264_NALU_TYPE_E    enH264;               /**<H264 *//**<CNcomment: H264*/
        ENC_HEVC_NALU_TYPE_E    enHevc;               /**<HEVC *//**<CNcomment: Hevc*/
    } uData;
} ENC_VID_DATA_TYPE_S;

/**output video es attr *//** CNcomment:输出video ES  码流属性 */
typedef struct _ENC_AUD_ES_DATA_S
{
    VOID*                       pBuffer;              /**<buffer ptr *//**<CNcomment: 数据缓冲指针,如果为NULL, 表示没有数据*/
    U32                         u32Length;            /**<data length *//**<CNcomment: 数据长度*/
    U64                         u64Pts;               /**<pts unit 90kHz *//**<CNcomment: 时间戳,  以90kHz 为单位*/
} ENC_AUD_ES_DATA_S;

/**output video es attr *//** CNcomment:输出video ES  码流属性 */
typedef struct _ENC_VID_ES_DATA_S
{
    VOID*                       pBuffer;              /**<buffer ptr *//**<CNcomment: 数据缓冲指针,如果为NULL, 表示没有数据*/
    U32                         u32Length;            /**<data length *//**<CNcomment: 数据长度*/
    U64                         u64Pts;               /**<pts unit 90kHz *//**<CNcomment: 时间戳,  以90kHz 为单位*/
    BOOL                        bFrameEnd;            /**<Whether end *//**<CNcomment: 是否为帧结束, 非零表示结束*/
    ENC_VID_DATA_TYPE_S         stDataType;           /**<vid data type *//**<CNcomment: VID数据类型*/
} ENC_VID_ES_DATA_S;

/**output ts attr *//** CNcomment:输出TS  码流属性 */
typedef struct _ENC_TS_DATA_S
{
    VOID*                      pBuffer;               /**<buffer ptr *//**<CNcomment: 数据缓冲指针,如果为NULL, 表示没有数据*/
    U32                        u32Length;             /**<data length *//**<CNcomment: 数据长度*/
} ENC_TS_DATA_S;

/**Enc init param *//** CNcomment:编码模块初始化参数 */
typedef struct _ENC_INIT_PARAMS_S
{
    U32 u32Dummy;                 /**<Reserve *//**<CNcomment:保留*/
} ENC_INIT_PARAMS_S;

/**Enc deinit param *//** CNcomment:编码模块去初始化参数 */
typedef struct _ENC_TERM_PARAMS_S
{
    U32  u32Dummy;                /**<Reserve *//**<CNcomment:保留*/
} ENC_TERM_PARAMS_S;

/**Enc open param *//** CNcomment:编码器打开参数 */
typedef struct _ENC_OPEN_PARAMS_S
{
    ENC_ENCODER_TYPE_E  enType;   /**<Encoder  type, support OR operate *//**<CNcomment:编码器类型，支持或操作*/
    VOID*               pSetting; /**<Encoder  setting, use ENC_SETTINGS_S or  AENC_SETTINGS_S or VENC_SETTINGS_S by enType*//**<CNcomment:编码器设置参数，与编码器类型对应，用ENC_SETTINGS_S或AENC_SETTINGS_S或VENC_SETTINGS_S*/
} ENC_OPEN_PARAMS_S;

/**Enc close param *//** CNcomment:编码器关闭参数 */
typedef struct _ENC_CLOSE_PARAMS_S
{
    U32      u32Dummy;            /**<Reserve *//**<CNcomment:保留*/
} ENC_CLOSE_PARAMS_S;

#ifdef ANDROID_HAL_MODULE_USED
/**ENC module structure(Android require)*/
/**CNcomment:编码模块结构(Android对接要求) */
typedef struct _ENC_MODULE_S
{
    struct hw_module_t stCommon;
} ENC_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_ENC*/
/** @{*/  /** <!-- -[HAL_ENC]=*/

/**Enc device structure*//** CNcomment:编码设备结构*/
typedef struct _ENC_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif
    /**
    \brief Enc  init.CNcomment:编码模块初始化 CNend
    \attention \n
    Lower layer enc module init and alloc necessary resource,  repeat call return success.
    CNcomment:底层编码模块初始化及分配必要的资源, 本函数重复调用返回成功. CNend
    \param[in] pstInitParams enc module init param.CNcomment:初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_ENC_INIT_FAILED  Lower layer enc module init error.CNcomment:底层编码模块初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_INIT_PARAMS_S

    \par example
    \code
    ENC_INIT_PARAMS_S stInitParam;
    memset(&stInitParam, 0x0, sizeof(SYSTEM_INIT_PARAMS_S));
    stInitParam.u32Dummy = 0;
    if (SUCCESS != enc_init(pstDev, (const ENC_INIT_PARAMS_S * const)&stInitParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*enc_init)(struct _ENC_DEVICE_S* pstDev, const ENC_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief Enc  deinit.CNcomment:编码模块去初始化 CNend
    \attention \n
    Lower layer enc module deinit and release occupied resource,  repeat call return success.
    CNcomment:底层编码模块去初始化及释放占用的资源, 本函数重复调用返回成功. CNend
    \param[in] pstTermParams enc module deinit param.CNcomment:去初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_ENC_DEINIT_FAILED  Lower layer enc module deinit error.CNcomment:底层编码模块去初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_TERM_PARAMS_S

    \par example
    \code
    ENC_TERM_PARAMS_S stDeInitParam;
    memset(&stDeInitParam, 0x0, sizeof(ENC_TERM_PARAMS_S));
    stDeInitParam.u32Dummy = 0;
    if (SUCCESS != enc_term(pstDev, (const ENC_TERM_PARAMS_S * const)&stDeInitParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*enc_term)(struct _ENC_DEVICE_S* pstDev,  const ENC_TERM_PARAMS_S* const  pstTermParams);

    /**
    \brief get enc module capability.CNcomment:获取编码器模块能力 CNend
    \attention \n
    Should call after enc_init. CNcomment:应该在编码模块初始化之后调用. CNend
    \param[out] pstCapability enc module capability param.CNcomment:编码模块能力参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_CAPABILITY_S

    \par example
    \code
    ENC_CAPABILITY_S stVencCapability;
    memset(&stVencCapability, 0x0, sizeof(ENC_CAPABILITY_S));
    if (SUCCESS != enc_get_capability(pstDev, (const ENC_CAPABILITY_S * const)&stVencCapability))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*enc_get_capability)(struct _ENC_DEVICE_S* pstDev, ENC_CAPABILITY_S* const pstCapability);

    /**
    \brief open encoder.CNcomment:打开编码器 CNend
    \attention \n
    May aenc or venc or aenc add venc. CNcomment:可以是音频编码器或视频编码器或音视频编码器. CNend
    \param[in] pstOpenParams encoder open param.CNcomment:编码器打开参数 CNend
    \param[out] pEncHandle encoder handle.CNcomment:编码器句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_ENC_OPEN_FAILED lower layer enc open failed.CNcomment:底层编码器打开错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_OPEN_PARAMS_S

    \par example
    */
    S32 (*enc_open)(struct _ENC_DEVICE_S* pstDev, HANDLE*   const pEncHandle, const ENC_OPEN_PARAMS_S* const pstOpenParams);

    /**
    \brief close encoder.CNcomment:关闭编码器 CNend
    \attention \n
     Must be stop status. CNcomment:需要在停止状态下关闭. CNend
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \param[in] pstCloseParams encoder close param.CNcomment:编码器关闭参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_CLOSE_FAILED lower layer enc close failed.CNcomment:底层编码器关闭错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_CLOSE_PARAMS_S

    \par example
    */
    S32 (*enc_close)(struct _ENC_DEVICE_S* pstDev, HANDLE hEnc, const ENC_CLOSE_PARAMS_S* const pstCloseParams);

    /**
    \brief set encoder private data.CNcomment:设置编码器私有数据 CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO and  ENC_ENCODE_VIDEO may divide set.CNcomment:编码器私有参数设置，音视频编码可分开设置 CNend
    \param[in] pData private data.CNcomment:私有数据 CNend
    \param[in] u32Length private data length.CNcomment:私有数据长度 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_set_private_data)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType, const VOID* const pData, const U32 u32Length);

    /**
    \brief get encoder private data.CNcomment:获取编码器私有数据 CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO and  ENC_ENCODE_VIDEO may divide get.CNcomment:编码器私有参数设置，音视频编码可分开获取 CNend
    \param[out] pData private data.CNcomment:私有数据存放buf CNend
    \param[in] u32Length private data buf length, if length don't enough, return failed.CNcomment:私有数据buf长度，如果不够存放则返回失败 CNend
    \param[out] pu32ActLength get private data length.CNcomment:实际获取的私有数据长度 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_BUF_LENGTH_NOT_ENOUGH buffer length not enough.CNcomment:buf长度不够。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_get_private_data)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType, VOID* const pData, const U32 u32Length, U32* const  pu32ActLength);

    /**
    \brief set encoder params.CNcomment:设置编码器参数 CNend
    \attention \n
    The next start to take effect. CNcomment:下一次启动编码器生效. CNend
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO and  ENC_ENCODE_VIDEO may divide set.CNcomment:编码器参数设置，音视频编码可分开设置CNend
    \param[in] pSettings setting data , map AENC_ENCODE_SETTINGS_S or VENC_ENCODE_SETTINGS_S or ENC_ENCODE_SETTINGS_S.CNcomment:设置数据，setting结构对应AENC_ENCODE_SETTINGS_S 或VENC_ENCODE_SETTINGS_S 或ENC_ENCODE_SETTINGS_S  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_set)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,   VOID* const pSettings);

    /**
    \brief get encoder params.CNcomment:获取编码器参数 CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO and  ENC_ENCODE_VIDEO may divide set.CNcomment:编码器参数获取，音视频编码可分开获取CNend
    \param[out] pSettings get setting data , map AENC_ENCODE_SETTINGS_S or VENC_ENCODE_SETTINGS_S or ENC_ENCODE_SETTINGS_S.CNcomment:获取设置数据，setting结构对应AENC_ENCODE_SETTINGS_S 或VENC_ENCODE_SETTINGS_S 或ENC_ENCODE_SETTINGS_S  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_get)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,   VOID* const pSettings);

    /**
    \brief start encoder.CNcomment:启动编码器. CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (*enc_start)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc);

    /**
    \brief stop encoder.CNcomment:停止编码器. CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (*enc_stop)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc);

    /**
    \brief inject encoder data.CNcomment:给编码器输入数据 CNend
    \attention \n
    Memory mode inject data, other mode invalid. CNcomment:内存模式下,向编码器传送原始的音视频数据,以及数据源的相关属性，其它模式无效. CNend
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO or  ENC_ENCODE_VIDEO .CNcomment:编码器类型，音视频编码数据必须分开注入CNend
    \param[in] pData inject data , audio or video source data.CNcomment:注入数据，音频或视频源数据  CNend
    \param[in] u32TimeoutMs time out.CNcomment:超时时间  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::ERROR_ENC_JNJECT_TIMEOUT time out time.CNcomment:超时时间。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_inject_data)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,  VOID* const pData, const  U32 u32TimeoutMs);

    /**
    \brief acquire encoder output stream(ES/TS).CNcomment:获取编码输出数据流(ES或TS) CNend
    \attention \n
    App cann't modify pData. CNcomment:应用不要修改pData 的内容. CNend
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO or  ENC_ENCODE_VIDEO .CNcomment:编码器类型，ES流音视频编码数据必须分开获取(TS流不用分开)CNend
    \param[out] pData stream data , audio or video output data.CNcomment:数据流，音频或视频输出数据(TS流不用分开，ES流要分开)  CNend
    \param[in] u32TimeoutMs time out.CNcomment:超时时间  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::ERROR_ENC_JNJECT_TIMEOUT time out.CNcomment:超时。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_acquire_stream)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,  VOID* const pData, const  U32 u32TimeoutMs);

    /**
    \brief release encoder stream buffer.CNcomment:释放从编码器输出缓存中读取的数据 CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO or  ENC_ENCODE_VIDEO .CNcomment:编码器类型，ES流音视频编码数据必须分开获取(TS流不用分开)CNend
    \param[in] pData stream data , audio or video output data.CNcomment:数据流，音频或视频输出数据(TS流不用分开，ES流要分开)  CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_release_stream)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,  VOID* const pData);

    /**
    \brief request fast encoder I frame.CNcomment:请求视频编码器尽快编出I 帧 CNend
    \attention \n
    request fast encoder I frame,  For video phone scene.
    CNcomment:调用该接口后, 编码器会尽快编码出一个I帧来.   一般用于可视电话场景的通话建立和错误恢复.
    此接口只是"尽最大能力"尽快编码出一个I帧来, 如果在短时间内多次调用此接口,那么不能保证每次调用都能对应编码出一个I帧来CNend
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (*enc_request_iframe)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc);

    /**
    \brief abort enc.CNcomment:终止enc CNend
    \attention \n
    cancel blocking for enc_send_data() and enc_acquire_stream().
    CNcomment: 终止enc_send_data(),enc_acquire_stream()
    当enc_send_data(),enc_acquire_stream().的超时时间不为0时,阻塞在HAL里面, enc_abort()可以解除阻塞,立即退出.本次  操作失败CNend
    \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    */
    S32 (*enc_abort)(struct _ENC_DEVICE_S* pstDev, const HANDLE enc_handle);

    /**
     \brief inject encoder data.CNcomment:向视频编码器送数据 CNend
     \attention \n
    Memory mode queue frame data, other mode invalid. This API should be matched with the API: enc_dequeue_frame.
    CNcomment:内存模式下,向编码器传送原始的音视频数据，其它模式无效.
    该接口需要与 enc_dequeue_frame 接口配对使用CNend
     \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
     \param[in] pVideoData inject frame data , video source data.CNcomment:注入数据，视频源数据  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
     \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
     \retval ::ERROR_ENC_JNJECT_TIMEOUT time out time.CNcomment:超时时间。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::ENC_ENCODER_TYPE_E

     \par example
    */
    S32 (*enc_queue_frame)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, ENC_VENC_DATA_S * pVideoData);

    /**
     \brief inject encoder data.CNcomment:向视频编码器还数据 CNend
     \attention \n
    Memory mode dequeue frame data, other mode invalid. If return SUCCESS, it means the corresponding frame buffer could be set free by user.
    CNcomment:内存模式下,向编码器归还原始的音视频数据，其它模式无效.
    如果接口返回成功，意味着对应的帧存用户可以释放 CNend
     \param[in] hEnc encoder handle.CNcomment:编码器句柄 CNend
     \param[out] pVideoData return frame data , video source data.CNcomment:归还数据，视频源数据  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:参数错误，如无效的句柄。CNend
     \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:底层编码器操作错误。CNend
     \retval ::ERROR_ENC_JNJECT_TIMEOUT time out time.CNcomment:超时时间。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::ENC_ENCODER_TYPE_E

     \par example
    */
    S32 (*enc_dequeue_frame)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, ENC_VENC_DATA_S * pVideoData);
} ENC_DEVICE_S;

/**
\brief direct get enc device api, for linux and android.CNcomment:获取编码设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get enc device api, for linux and andorid.
CNcomment:获取编码设备接口，linux和android平台都可以使用. CNend
\retval  enc device pointer when success.CNcomment:成功返回enc设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::ENC_DEVICE_S

\par example
*/
ENC_DEVICE_S* getEncDevice();

/**
\brief  Open HAL AENC/VENC module device.CNcomment:打开HAL音视频编码模块设备 CNend
\attention \n
Open HAL AENC/VENC module device(for compatible Android HAL).
CNcomment:打开HAL音视频编码模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice ENC device structure.CNcomment:编码器设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功 CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::ENC_DEVICE_S

\par example
*/
static inline S32 enc_open(const struct hw_module_t* pstModule, ENC_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, ENC_HARDWARE_ENC0, (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getEncDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL enc module device.CNcomment: 关闭HAL编码模块设备 CNend
\attention \n
Close HAL enc module device(for compatible Android HAL).
CNcomment: 关闭HAL编码模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice enc device structure.CNcomment:编码设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::ENC_DEVICE_S

\par example
*/
static inline S32 enc_close(ENC_DEVICE_S* pstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstDevice->stCommon.close(&pstDevice->stCommon);
#else
    return SUCCESS;
#endif
}

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
}
#endif

#endif  /*__TVOS_HAL_ENC_H__*/

