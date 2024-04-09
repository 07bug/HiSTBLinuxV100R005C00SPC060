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

/**enc module file max len.*//** CNcomment:����ģ�鶨����ļ�����󳤶� */
#define ENC_FILE_NAME_LENGTH   (255)

/** @} */  /** <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_ENC */
/** @{ */  /** <!-- [HAL_ENC] */

/** encoder type *//** CNcomment:���������� */
typedef enum _ENC_ENCODER_TYPE_E
{
    ENC_ENCODE_NONE  = 0,
    ENC_ENCODE_VIDEO = 1,                 /**<Video or OSD + Video*//**<CNcomment:Video ��OSD+Video*/
    ENC_ENCODE_AUDIO = 1 << 1,            /**<Audio */ /**<CNcomment:Audio */
    ENC_ENCODE_BUTT
}  ENC_ENCODER_TYPE_E;

/** enc output type *//** CNcomment:�������������. */
typedef enum _ENC_OUTPUT_TYPE_E
{
    ENC_OUTPUT_MEM = 0,                   /**<output to memory *//**<CNcomment:�����ڴ�����.ͨ�� enc_acquire_stream() ��ȡ */
    ENC_OUTPUT_FILE,                      /**<output to file *//**<CNcomment:д���ļ����� */
    ENC_OUTPUT_BUTT
}  ENC_OUTPUT_TYPE_E;

/** color space *//** CNcomment:ɫ�ʿռ� */
typedef enum _ENC_COLOR_TYPE_E
{
    ENC_COLOR_TYPE_NONE = 0,              /**<ingore, hal auto*//**<CNcomment:Ӧ�ò�����,HAL �Լ����� */
    ENC_COLOR_TYPE_YUV_420,               /**<YUV420*//**<CNcomment:YUV420 */
    ENC_COLOR_TYPE_YUV_422,               /**<YUV422*//**<CNcomment:YUV422 */
    ENC_COLOR_TYPE_YUV_444,               /**<YUV444*//**<CNcomment:YUV444 */
    ENC_COLOR_TYPE_BUTT
}  ENC_COLOR_TYPE_E;

/** store type *//** CNcomment:�洢��ʽ*/
typedef enum _ENC_STORE_TYPE_E
{
    ENC_STORE_TYPE_NONE = 0,              /**<ingore, hal auto*/ /**<CNcomment:Ӧ�ò�����,HAL �Լ����� */
    ENC_STORE_TYPE_SEMIPLANNAR,           /**<Semi-planar*//**<CNcomment:Semi-planar */
    ENC_STORE_TYPE_PLANNAR,               /**<Planar mode*//**<CNcomment:Planar mode, ��Y.U.V�����������ֱ����ڲ�ͬ�ľ����� */
    ENC_STORE_TYPE_PACKAGE,               /**<Package mode*//**<CNcomment:Package mode,  ��Y.U.Vֵ�����Macro Pixels����,��RGB�Ĵ�ŷ�ʽ����*/
    ENC_STORE_TYPE_BUTT
}  ENC_STORE_TYPE_E;

/** Storage sequence of package YUV *//** CNcomment:YUV���洢ϵ��*/
typedef enum _ENC_YUV_PACKAGE_SEQ_E
{
    ENC_PACKAGE_NONE = 0,        /**<ingore, hal auto*/ /**<CNcomment:Ӧ�ò�����,HAL �Լ����� */

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

/** Field type *//** CNcomment:������*/
typedef enum _ENC_VID_FIELD_TYPE_E
{
    ENC_VID_FIELD_ALL = 0,             /**<frame *//**<CNcomment:֡*/
    ENC_VID_FIELD_TOP,                 /**<top field *//**<CNcomment:����*/
    ENC_VID_FIELD_BOTTOM,              /**<bottom field *//**<CNcomment:�׳�*/
    ENC_VID_FIELD_BUTT
} ENC_VID_FIELD_TYPE_E ;

/** H.264 NALU type *//** CNcomment:H.264 NALU ����*/
typedef enum _ENC_H264_NALU_TYPE_E
{
    ENC_H264_NALU_P_SLICE = 0,         /**<P slice NALU *//**<CNcomment:P slice NALU*/
    ENC_H264_NALU_I_SLICE,             /**<I slice NALU *//**<CNcomment:I slice NALU*/
    ENC_H264_NALU_SEI,                 /**<SEI NALU *//**<CNcomment:SEI NALU*/
    ENC_H264_NALU_SPS,                 /**<SPS NALU *//**<CNcomment:SPS NALU*/
    ENC_H264_NALU_PPS,                 /**<PPS NALU *//**<CNcomment:PPS NALU*/
    ENC_H264_NALU_BUTT
} ENC_H264_NALU_TYPE_E ;

/** H.263 NALU type *//** CNcomment:H.263 NALU ����*/
typedef enum _ENC_H263_NALU_TYPE_E
{
    ENC_H263_NALU_P_SLICE = 0,         /**<P slice NALU *//**<CNcomment:P slice NALU*/
    ENC_H263_NALU_I_SLICE,             /**<I slice NALU *//**<CNcomment:I slice NALU*/
    ENC_H263_NALU_SEI,                 /**<SEI NALU *//**<CNcomment:SEI NALU*/
    ENC_H263_NALU_SPS,                 /**<SPS NALU *//**<CNcomment:SPS NALU*/
    ENC_H263_NALU_PPS,                 /**<PPS NALU *//**<CNcomment:PPS NALU*/
    ENC_H263_NALU_BUTT
} ENC_H263_NALU_TYPE_E ;

/** JPEG package type *//** CNcomment:JPEG �������*/
typedef enum _ENC_JPEG_PACK_TYPE_E
{
    ENC_JPEG_PACK_ECS = 0,             /**<ECS package *//**<CNcomment:ECS��*/
    ENC_JPEG_PACK_APP,                 /**<APP package *//**<CNcomment:APP��*/
    ENC_JPEG_PACK_VDO,                 /**<VDO package *//**<CNcomment:VDO��*/
    ENC_JPEG_PACK_PIC,                 /**<PIC package *//**<CNcomment:PIC��*/
    ENC_JPEG_PACK_TYPE_BUTT
} ENC_JPEG_PACK_TYPE_E;

/** MPEG4 package type *//** CNcomment:MPEG4 �������*/
typedef enum _ENC_MPEG4_PACK_TYPE_E
{
    ENC_MPEG4_PACK_VO = 0,             /**<VO package *//**<CNcomment:VO��*/
    ENC_MPEG4_PACK_VOS,                /**<VOS package *//**<CNcomment:VOS��*/
    ENC_MPEG4_PACK_VOL,                /**<VOL package *//**<CNcomment:VOL��*/
    ENC_MPEG4_PACK_VOP,                /**<VOP package *//**<CNcomment:VOP��*/
    ENC_MPEG4_PACK_SLICE,              /**<Slice package *//**<CNcomment:Slice��*/
    ENC_MPEG4_PACK_BUTT
} ENC_MPEG4_PACK_TYPE_E;

/**HEVC NALU type*//**CNcomment: HEVC NALU���� */
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

/**enc source type*//** CNcomment:������Դ���� */
typedef enum _ENC_SOURCE_TYPE_E
{
    ENC_SOURCE_NONE = 0,               /**<none, can't connect or disconnect *//**<CNcomment:δ����,���߶Ͽ�����*/
    ENC_SOURCE_DECODER,                /**<bind av handle, get av handle data *//**<CNcomment: �󶨽�����,ȡ�����Ժ������*/
    ENC_SOURCE_MEM,                    /**<app inject data *//**<CNcomment:Ӧ������ע������*/
    ENC_SOURCE_FILE,                   /**<file data *//**<CNcomment:���ļ�������*/
    ENC_SOURCE_AOUT,                   /**<aout data, bind aout ID *//**<CNcomment:����֮������ݣ���AOUT_ID_E*/
    ENC_SOURCE_VOUT,                   /**<vout data, bind vout channel  VOUT_DISPLAY_CHANNEL_E*//**<CNcomment:display���ݣ���voutͨ��VOUT_DISPLAY_CHANNEL_E*/
    ENC_SOURCE_SOURCE,                 /**<source data, bind source SOURCE_ID_E*//**<CNcomment:������ԴSOURCE_ID_E*/
    ENC_SOURCE_BUTT,
} ENC_SOURCE_TYPE_E;

/**Enc output stream format,  isn't necessary to support all types, capability inquire by enc_get_capability*/
/** CNcomment:�����������ʽ, ���Ǳ���֧�����е�����,���� ��enc_get_capability()����֧����� */
typedef enum _ENC_OUTPUT_STREAM_FORMAT_E
{
    ENC_OUTPUT_STREAM_FORMAT_NONE = 0,
    ENC_OUTPUT_STREAM_FORMAT_TS   = 1,                                  /**<TS type */ /**<CNcomment:TS����*/
    ENC_OUTPUT_STREAM_FORMAT_ES   = 1 << 1                              /**<ES type */ /**<CNcomment:ES����*/
} ENC_OUTPUT_STREAM_FORMAT_E;

/**enc source params*//** CNcomment:������Դ���Ͷ�Ӧ�Ĳ��� */
typedef struct _ENC_SOURCE_PARAMS_S
{
    ENC_SOURCE_TYPE_E          enSourceType;                            /**<source type *//**<CNcomment:Դ����*/
    union _ENC_SOURCE_U
    {
        HANDLE                 hAv;                                     /**<av handle map ENC_SOURCE_DECODER*//**<CNcomment:av�������ӦENC_SOURCE_DECODER�Ĳ���*/
        CHAR                   aFileName[ENC_FILE_NAME_LENGTH + 1];     /**<file name map ENC_SOURCE_FIL*//**<CNcomment:�ļ���,��Ӧm_source_type == ENC_SOURCE_FILE�Ĳ���*/
        AOUT_ID_E              enAoutId;                                /**<aout ID map ENC_SOURCE_AOUT*//**<CNcomment:aout id����ӦENC_SOURCE_AOUT�Ĳ���*/
        VOUT_DISPLAY_CHANNEL_E enDisplayChanel;                         /**<vout display channel map ENC_SOURCE_VOUT*//**<CNcomment:vout displayͨ������ӦENC_SOURCE_VOUT�Ĳ���*/
        SOURCE_ID_E            enSourceId;                              /**<source id map ENC_SOURCE_SOURCE*//**<CNcomment:����ԴID����ӦENC_SOURCE_SOURCE�Ĳ���*/
        U32                    u32Dummy;                                /**<Reserve *//**<CNcomment:����*/
    } uSource;
} ENC_SOURCE_PARAMS_S;

/**enc output params*//** CNcomment:������������� */
typedef struct _ENC_OUTPUT_PARAMS_S
{
    ENC_OUTPUT_TYPE_E       enOutputType;                               /**<output type *//**<CNcomment:�������*/
    union enc_output_u
    {
        CHAR                aFileName[ENC_FILE_NAME_LENGTH + 1 ];       /**<file name map ENC_OUTPUT_FILE */ /**<CNcomment:�ļ�����ENC_OUTPUT_FILE��Ӧ�Ĳ���*/
        U32                 u32Dummy;                                   /**<memory map ENC_OUTPUT_MEM *//**<CNcomment:���ݷ����ڴ�����.ͨ�� enc_acquire_stream() ��ȡ*/
    } uOutput;
} ENC_OUTPUT_PARAMS_S;

/**audio encoder format support capability *//** CNcomment:��Ƶ��������ʽ֧������ */
typedef struct _ENC_AENC_SUPPORT_S
{
    BOOL                    bSupportedDecType;                          /**<Whether support the format, TRUE means exist *//**<CNcomment:�Ƿ�֧�ָ���Ƶ��������ʽ*/
    U32                     u32Number;                                  /**<codec number *//**<CNcomment:����������*/
    U32                     u32Dummy;                                   /**<reserve *//**<CNcomment:����*/
} ENC_AENC_SUPPORT_S;

/**audio encoder capability *//** CNcomment:��Ƶ���������� */
typedef struct _ENC_AENC_CAPABILITY_S
{
    BOOL                    bExist;                                     /**<Whether exist audio encoder, TRUE means exist *//**<CNcomment:�Ƿ������Ƶ������*/
    ENC_AENC_SUPPORT_S      astStreamTypeArr[AV_AUD_STREAM_TYPE_BUTT];  /**<audio encoder type, index by  AV_AUD_STREAM_TYPE_E*//**<CNcomment:֧�ֵı�������. ��AV_AUD_STREAM_TYPE_E����Ϊ����*/
} ENC_AENC_CAPABILITY_S;

/**video encoder format support capability *//** CNcomment:��Ƶ��������ʽ֧������ */
typedef struct _ENC_VENC_SUPPORT_S
{
    BOOL                    bSupportedDecType;                          /**<Whether support the format, TRUE means exist *//**<CNcomment:�Ƿ�֧�ָ���Ƶ��������ʽ*/
    VDEC_RESO_LEVEL_E       enDecCapLevel;                              /**<reso capability *//**<CNcomment:֧�ֵķֱ�������*/
    U32                     u32Number;                                  /**<codec number *//**<CNcomment:����������*/
    U32                     u32Fps;                                     /**<codec fps *//**<CNcomment:������֡��*/
    U32                     u32Dummy;                                   /**<reserve *//**<CNcomment:����*/
} ENC_VENC_SUPPORT_S;

/**video encoder capability *//** CNcomment:��Ƶ���������� */
typedef struct _ENC_VENC_CAPABILITY_S
{
    BOOL                    bExist;                                     /**<Whether exist video encoder, TRUE means exist *//**<CNcomment:�Ƿ������Ƶ������*/
    ENC_ENCODER_TYPE_E      enType;                                     /**<Video encoder  type, support OR operate *//**<CNcomment:��Ƶ���������ͣ�֧�ֻ����*/
    ENC_VENC_SUPPORT_S      astVencSupport[AV_VID_STREAM_TYPE_BUTT];    /**<Video encoder format capability *//**<CNcomment:��Ƶ��������ʽ֧������*/
} ENC_VENC_CAPABILITY_S;

/**encoder capability *//** CNcomment:���������� */
typedef struct _ENC_CAPABILITY_S
{
    ENC_OUTPUT_STREAM_FORMAT_E      enOutputStreamFormat;               /**<venc output stream format, support OR operate *//**<CNcomment:֧�ֵ��������ʽ��֧�ֻ����*/
    ENC_AENC_CAPABILITY_S           stAencArr;                          /**<venc aenc capability desc *//**<CNcomment:��Ƶ������������*/
    ENC_VENC_CAPABILITY_S           stVencArr;                          /**<venc venc capability desc *//**<CNcomment:��Ƶ������������*/
} ENC_CAPABILITY_S;

/** aenc  settings *//** CNcomment:��Ƶ���������ò���*/
typedef struct _ENC_AENC_SETTINGS_S
{
    ENC_SOURCE_PARAMS_S  stSourceParams;                                /**<source params *//**<CNcomment:����Դ����*/
    ENC_OUTPUT_PARAMS_S  stOutputParams;                                /**<output params *//**<CNcomment:�����������*/
    ENC_OUTPUT_STREAM_FORMAT_E  enOutputStreamFormat;                   /**<output format *//**<CNcomment:���������ʽ*/
    AV_AUD_STREAM_TYPE_E enType;                                        /**<enc format *//**<CNcomment:�����ʽ*/
    U32                  u32BufSize;                                    /**<enc buffer size *//**<CNcomment:�����������С, 0��ʾ����ע*/
    U32                  u32Channels;                                   /**<audio track number *//**<CNcomment:������. ������:1,2 ,0��ʾ����ע*/
    U32                  u32BitPerSample;                               /**<bit width *//**<CNcomment: λ��.��Ƶÿ����������ռ�ı�����, ��:8bit,16bit ,0��ʾ����ע*/
    U32                  u32SampleRate;                                 /**<sample rate *//**<CNcomment:������.(32000,44100,48000 ),0��ʾ����ע*/
    BOOL                 bInterleaved;                                  /**<Whether interleave *//**<CNcomment:�Ƿ�����֯ģʽ*/
    U32                  u32SamplePerFrame;                             /**<sample per frame *//**<CNcomment:ÿ֡������*/
} ENC_AENC_SETTINGS_S;

/** venc  settings *//** CNcomment:��Ƶ���������ò���*/
typedef struct _ENC_VENC_SETTINGS_S
{
    ENC_SOURCE_PARAMS_S         stSourceParams;                         /**<source params *//**<CNcomment:����Դ����*/
    ENC_OUTPUT_PARAMS_S         stOutputParams;                         /**<output params *//**<CNcomment:�����������*/
    ENC_OUTPUT_STREAM_FORMAT_E  enOutputStreamFormat;                   /**<output format *//**<CNcomment:���������ʽ*/
    AV_VID_STREAM_TYPE_E        enType;                                 /**<enc format *//**<CNcomment:�����ʽ*/
    U32                         u32Width;                               /**<width *//**<CNcomment:�����ͼ��Ŀ��*/
    U32                         u32Height;                              /**<height *//**<CNcomment �����ͼ��ĸ߶�*/
    U32                         bInterleaved;                           /**<Whether interleave *//**<CNcomment:�Ƿ�����֯ģʽ*/
    U32                         u32OutputFrameRate;                     /**<enc output frame rate *//**<CNcomment��������֡��,m_frame_rate =ʵ��֡��x1000*/
    U32                         u32InputFrameRate;                      /**<enc input frame rate, only for mem and file, zero for auto *//**<CNcomment��������֡��,�����ڴ���ļ��������ͣ�0��ʾ��HAL�Լ�����*/
    U32                         u32BufSize;                             /**<buffer size, zero means ignore *//**<CNcomment:�����������С , �����0, hdi  �ڲ�����*/
    ENC_COLOR_TYPE_E            enColorType;                            /**<enc output format *//**<CNcomment:���������ʽ*/
    ENC_STORE_TYPE_E            enStoreType;                            /**<store type *//**<CNcomment:�洢����*/
    ENC_YUV_PACKAGE_SEQ_E       enPackageSeq;                           /**<package YUV sequence type *//**<CNcomment:YUV������*/
    BOOL                        bSliceSplit;                            /**<Whether slice split, FALSE means disable *//**<CNcomment:�Ƿ�ʹ�ָܷ�slice , FALSE:disable, TRUE:enable*/
    U32                         u32SplitSize;                           /**<slice split size *//**<CNcomment: �ָ�Ĵ�С, JPGE����MCUΪ��λ,H264����MP4���ֽ�Ϊ��λ, H263������*/
    U32                         u32JpegQl;                              /**<Jpeg quality *//**<CNcomment:GFX_IMAGE_QUALITY_LEVEL_MIN, GFX_IMAGE_QUALITY_LEVEL_MAX. ����Ϊ:0,��ʾ����,���JPGE��ʽ*/
    U32                         u32BitRate;                             /**<Bit rate *//**<CNcomment:Ŀ������: 1080P 5M����, 720P 3M����, 576P 2M ����. 0 ��hdi �ڲ�����*/
    U32                         u32Gop;                                 /**<Group Of Picture *//**<CNcomment:������Group Of Picture. ת��/ת�������½�������Ϊ30~100 ����;���ӵ绰�����½�������Ϊ100~300.  0 ��HAL �ڲ�����*/
    U32                         u32MaxQp;                               /**<quantization parameter *//**<CNcomment: �����������(quantization parameter) , ����:48.  0 ��HAL �ڲ�����*/
    U32                         u32MinQp;                               /**<quantization parameter *//**<CNcomment:��С��������(quantization parameter) .����: 16 .  0 ��HAL �ڲ�����*/
    BOOL                        bQuickEncode;                           /**<Whether enable quick encoder *//**<CNcomment:�Ƿ�ʹ�ܿ��ٱ���ģʽ, 0:disable; ����:enable*/
} ENC_VENC_SETTINGS_S;

/**aenc and venc setting *//** CNcomment:����Ƶ���������ò���*/
typedef struct _ENC_SETTINGS_S
{
    ENC_AENC_SETTINGS_S stAencSettings;                                 /**<aenc setting *//**<CNcomment:��Ƶ��������*/
    ENC_VENC_SETTINGS_S stVencSettings;                                 /**<venc setting *//**<CNcomment:��Ƶ��������*/
} ENC_SETTINGS_S;

/**aenc source attr, only for inject mode*//** CNcomment:���������ƵԴ����.����ע��ģʽ��ʹ�� */
typedef struct _ENC_AENC_DATA_S
{
    U32                        u32Channels;                             /**<audio track number *//**<CNcomment: ������*/
    BOOL                       bInterleaved;                            /**<Whether interleave *//**<CNcomment:�Ƿ�����֯ģʽ*/
    U32                        u32BitPerSample;                         /**<bit width *//**<CNcomment λ��*/
    U32                        u32SampleRate;                           /**<sample rate *//**<CNcomment������*/
    U32                        u32SamplesPerPrame;                      /**<PCM sample number *//**<CNcomment PCM ���ݲ���������*/
    U32                        u32FrameIndex;                           /**<frame index *//**<CNcomment  ֡���*/
    U64                        u64Pts;                                  /**<pts unit 90kHz *//**<CNcomment: ʱ���,  ��90kHz Ϊ��λ*/
    VOID*                      pBuffer;                                 /**<buffer ptr *//**<CNcomment: ���ݻ���ָ�� */
    U32                        u32Length;                               /**<data length *//**<CNcomment: ���ݳ���*/
} ENC_AENC_DATA_S;

/**video  addr*//** CNcomment:��Ƶ��ַ */
typedef struct _ENC_VID_FRAME_ADDR_S
{
    U32                        u32YAddr;              /**<y addr *//**<CNcomment:  Y�������ݵĵ�ַ*/
    U32                        u32CAddr;              /**<c addr *//**<CNcomment:  C�������ݵĵ�ַ*/
    U32                        u32CrAddr;             /**<cr addr *//**<CNcomment:  Cr�������ݵĵ�ַ*/
    U32                        u32YStride;            /**<y stride *//**<CNcomment:  Y�������ݵĿ��*/
    U32                        u32CStride;            /**<c stride *//**<CNcomment:  C�������ݵĿ��*/
    U32                        u32CrStride;           /**<cr stride *//**<CNcomment:  Cr�������ݵĿ��*/
} ENC_VID_FRAME_ADDR_S;

/**video source data *//** CNcomment:���������ƵԴ ����.����ע��ģʽ��ʹ�� */
typedef struct _ENC_VENC_DATA_S
{
    AV_VID_STREAM_TYPE_E        enType;               /**<video encoder type *//**<CNcomment: �����ʽ*/
    U32                         u32Width;             /**<width *//**<CNcomment:�����ͼ��Ŀ��*/
    U32                         u32Height;            /**<height *//**<CNcomment �����ͼ��ĸ߶�*/
    BOOL                        bInterleaved;         /**<Whether interleave *//**<CNcomment:�Ƿ�����֯ģʽ*/
    U32                         u32FrameRate;         /**<frame rate *//**<CNcomment:   ֡��,m_frame_rate =ʵ��֡��x1000*/
    ENC_COLOR_TYPE_E            enColorType;          /**<color type *//**<CNcomment:  ɫ������*/
    ENC_STORE_TYPE_E            enStoreType;          /**<store type *//**<CNcomment:  �洢����*/
    ENC_YUV_PACKAGE_SEQ_E       enPackageSeq;         /**<package YUV sequence *//**<CNcomment:  package YUV���˳��*/
    ENC_VID_FIELD_TYPE_E        enFieldType;          /**<field type *//**<CNcomment:  ������*/
    AV_3D_FORMAT_E              en3dFormat;           /**<3d format *//**<CNcomment:  3d��ʽ*/
    BOOL                        bTopFieldFirst;       /**<top field first *//**<CNcomment:  ��������,����:����*/
    U32                         u32FrameIndex;        /**<frame index *//**<CNcomment:  ֡���*/
    U64                         u64Pts;               /**<pts unit 90kHz *//**<CNcomment: ʱ���,  ��90kHz Ϊ��λ*/
    ENC_VID_FRAME_ADDR_S        stAddr;               /**<vid frame addr *//**<CNcomment: ��Ƶ֡��ַ*/
} ENC_VENC_DATA_S;

/**video data type *//** CNcomment:video�������� */
typedef struct  _ENC_VID_DATA_TYPE_S
{
    AV_VID_STREAM_TYPE_E        enType;               /**<video encoder type *//**<CNcomment: �����ʽ*/
    union _ENC_DATA_TYPE_U
    {
        ENC_JPEG_PACK_TYPE_E    enJpeg;               /**<Jpeg *//**<CNcomment: Jpeg*/
        ENC_MPEG4_PACK_TYPE_E   enMpeg4;              /**<Mpeg4 *//**<CNcomment: Mpeg4*/
        ENC_H263_NALU_TYPE_E    enH263;               /**<H263 *//**<CNcomment: H263*/
        ENC_H264_NALU_TYPE_E    enH264;               /**<H264 *//**<CNcomment: H264*/
        ENC_HEVC_NALU_TYPE_E    enHevc;               /**<HEVC *//**<CNcomment: Hevc*/
    } uData;
} ENC_VID_DATA_TYPE_S;

/**output video es attr *//** CNcomment:���video ES  �������� */
typedef struct _ENC_AUD_ES_DATA_S
{
    VOID*                       pBuffer;              /**<buffer ptr *//**<CNcomment: ���ݻ���ָ��,���ΪNULL, ��ʾû������*/
    U32                         u32Length;            /**<data length *//**<CNcomment: ���ݳ���*/
    U64                         u64Pts;               /**<pts unit 90kHz *//**<CNcomment: ʱ���,  ��90kHz Ϊ��λ*/
} ENC_AUD_ES_DATA_S;

/**output video es attr *//** CNcomment:���video ES  �������� */
typedef struct _ENC_VID_ES_DATA_S
{
    VOID*                       pBuffer;              /**<buffer ptr *//**<CNcomment: ���ݻ���ָ��,���ΪNULL, ��ʾû������*/
    U32                         u32Length;            /**<data length *//**<CNcomment: ���ݳ���*/
    U64                         u64Pts;               /**<pts unit 90kHz *//**<CNcomment: ʱ���,  ��90kHz Ϊ��λ*/
    BOOL                        bFrameEnd;            /**<Whether end *//**<CNcomment: �Ƿ�Ϊ֡����, �����ʾ����*/
    ENC_VID_DATA_TYPE_S         stDataType;           /**<vid data type *//**<CNcomment: VID��������*/
} ENC_VID_ES_DATA_S;

/**output ts attr *//** CNcomment:���TS  �������� */
typedef struct _ENC_TS_DATA_S
{
    VOID*                      pBuffer;               /**<buffer ptr *//**<CNcomment: ���ݻ���ָ��,���ΪNULL, ��ʾû������*/
    U32                        u32Length;             /**<data length *//**<CNcomment: ���ݳ���*/
} ENC_TS_DATA_S;

/**Enc init param *//** CNcomment:����ģ���ʼ������ */
typedef struct _ENC_INIT_PARAMS_S
{
    U32 u32Dummy;                 /**<Reserve *//**<CNcomment:����*/
} ENC_INIT_PARAMS_S;

/**Enc deinit param *//** CNcomment:����ģ��ȥ��ʼ������ */
typedef struct _ENC_TERM_PARAMS_S
{
    U32  u32Dummy;                /**<Reserve *//**<CNcomment:����*/
} ENC_TERM_PARAMS_S;

/**Enc open param *//** CNcomment:�������򿪲��� */
typedef struct _ENC_OPEN_PARAMS_S
{
    ENC_ENCODER_TYPE_E  enType;   /**<Encoder  type, support OR operate *//**<CNcomment:���������ͣ�֧�ֻ����*/
    VOID*               pSetting; /**<Encoder  setting, use ENC_SETTINGS_S or  AENC_SETTINGS_S or VENC_SETTINGS_S by enType*//**<CNcomment:���������ò���������������Ͷ�Ӧ����ENC_SETTINGS_S��AENC_SETTINGS_S��VENC_SETTINGS_S*/
} ENC_OPEN_PARAMS_S;

/**Enc close param *//** CNcomment:�������رղ��� */
typedef struct _ENC_CLOSE_PARAMS_S
{
    U32      u32Dummy;            /**<Reserve *//**<CNcomment:����*/
} ENC_CLOSE_PARAMS_S;

#ifdef ANDROID_HAL_MODULE_USED
/**ENC module structure(Android require)*/
/**CNcomment:����ģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _ENC_MODULE_S
{
    struct hw_module_t stCommon;
} ENC_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_ENC*/
/** @{*/  /** <!-- -[HAL_ENC]=*/

/**Enc device structure*//** CNcomment:�����豸�ṹ*/
typedef struct _ENC_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif
    /**
    \brief Enc  init.CNcomment:����ģ���ʼ�� CNend
    \attention \n
    Lower layer enc module init and alloc necessary resource,  repeat call return success.
    CNcomment:�ײ����ģ���ʼ���������Ҫ����Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstInitParams enc module init param.CNcomment:��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_ENC_INIT_FAILED  Lower layer enc module init error.CNcomment:�ײ����ģ���ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
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
    \brief Enc  deinit.CNcomment:����ģ��ȥ��ʼ�� CNend
    \attention \n
    Lower layer enc module deinit and release occupied resource,  repeat call return success.
    CNcomment:�ײ����ģ��ȥ��ʼ�����ͷ�ռ�õ���Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstTermParams enc module deinit param.CNcomment:ȥ��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_ENC_DEINIT_FAILED  Lower layer enc module deinit error.CNcomment:�ײ����ģ��ȥ��ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
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
    \brief get enc module capability.CNcomment:��ȡ������ģ������ CNend
    \attention \n
    Should call after enc_init. CNcomment:Ӧ���ڱ���ģ���ʼ��֮�����. CNend
    \param[out] pstCapability enc module capability param.CNcomment:����ģ���������� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
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
    \brief open encoder.CNcomment:�򿪱����� CNend
    \attention \n
    May aenc or venc or aenc add venc. CNcomment:��������Ƶ����������Ƶ������������Ƶ������. CNend
    \param[in] pstOpenParams encoder open param.CNcomment:�������򿪲��� CNend
    \param[out] pEncHandle encoder handle.CNcomment:��������� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param.CNcomment:��������CNend
    \retval ::ERROR_ENC_OPEN_FAILED lower layer enc open failed.CNcomment:�ײ�������򿪴���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::ENC_OPEN_PARAMS_S

    \par example
    */
    S32 (*enc_open)(struct _ENC_DEVICE_S* pstDev, HANDLE*   const pEncHandle, const ENC_OPEN_PARAMS_S* const pstOpenParams);

    /**
    \brief close encoder.CNcomment:�رձ����� CNend
    \attention \n
     Must be stop status. CNcomment:��Ҫ��ֹͣ״̬�¹ر�. CNend
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \param[in] pstCloseParams encoder close param.CNcomment:�������رղ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_CLOSE_FAILED lower layer enc close failed.CNcomment:�ײ�������رմ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::ENC_CLOSE_PARAMS_S

    \par example
    */
    S32 (*enc_close)(struct _ENC_DEVICE_S* pstDev, HANDLE hEnc, const ENC_CLOSE_PARAMS_S* const pstCloseParams);

    /**
    \brief set encoder private data.CNcomment:���ñ�����˽������ CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO and  ENC_ENCODE_VIDEO may divide set.CNcomment:������˽�в������ã�����Ƶ����ɷֿ����� CNend
    \param[in] pData private data.CNcomment:˽������ CNend
    \param[in] u32Length private data length.CNcomment:˽�����ݳ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_set_private_data)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType, const VOID* const pData, const U32 u32Length);

    /**
    \brief get encoder private data.CNcomment:��ȡ������˽������ CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO and  ENC_ENCODE_VIDEO may divide get.CNcomment:������˽�в������ã�����Ƶ����ɷֿ���ȡ CNend
    \param[out] pData private data.CNcomment:˽�����ݴ��buf CNend
    \param[in] u32Length private data buf length, if length don't enough, return failed.CNcomment:˽������buf���ȣ������������򷵻�ʧ�� CNend
    \param[out] pu32ActLength get private data length.CNcomment:ʵ�ʻ�ȡ��˽�����ݳ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_BUF_LENGTH_NOT_ENOUGH buffer length not enough.CNcomment:buf���Ȳ�����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_get_private_data)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType, VOID* const pData, const U32 u32Length, U32* const  pu32ActLength);

    /**
    \brief set encoder params.CNcomment:���ñ��������� CNend
    \attention \n
    The next start to take effect. CNcomment:��һ��������������Ч. CNend
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO and  ENC_ENCODE_VIDEO may divide set.CNcomment:�������������ã�����Ƶ����ɷֿ�����CNend
    \param[in] pSettings setting data , map AENC_ENCODE_SETTINGS_S or VENC_ENCODE_SETTINGS_S or ENC_ENCODE_SETTINGS_S.CNcomment:�������ݣ�setting�ṹ��ӦAENC_ENCODE_SETTINGS_S ��VENC_ENCODE_SETTINGS_S ��ENC_ENCODE_SETTINGS_S  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_set)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,   VOID* const pSettings);

    /**
    \brief get encoder params.CNcomment:��ȡ���������� CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO and  ENC_ENCODE_VIDEO may divide set.CNcomment:������������ȡ������Ƶ����ɷֿ���ȡCNend
    \param[out] pSettings get setting data , map AENC_ENCODE_SETTINGS_S or VENC_ENCODE_SETTINGS_S or ENC_ENCODE_SETTINGS_S.CNcomment:��ȡ�������ݣ�setting�ṹ��ӦAENC_ENCODE_SETTINGS_S ��VENC_ENCODE_SETTINGS_S ��ENC_ENCODE_SETTINGS_S  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_get)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,   VOID* const pSettings);

    /**
    \brief start encoder.CNcomment:����������. CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (*enc_start)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc);

    /**
    \brief stop encoder.CNcomment:ֹͣ������. CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (*enc_stop)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc);

    /**
    \brief inject encoder data.CNcomment:���������������� CNend
    \attention \n
    Memory mode inject data, other mode invalid. CNcomment:�ڴ�ģʽ��,�����������ԭʼ������Ƶ����,�Լ�����Դ��������ԣ�����ģʽ��Ч. CNend
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO or  ENC_ENCODE_VIDEO .CNcomment:���������ͣ�����Ƶ�������ݱ���ֿ�ע��CNend
    \param[in] pData inject data , audio or video source data.CNcomment:ע�����ݣ���Ƶ����ƵԴ����  CNend
    \param[in] u32TimeoutMs time out.CNcomment:��ʱʱ��  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::ERROR_ENC_JNJECT_TIMEOUT time out time.CNcomment:��ʱʱ�䡣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_inject_data)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,  VOID* const pData, const  U32 u32TimeoutMs);

    /**
    \brief acquire encoder output stream(ES/TS).CNcomment:��ȡ�������������(ES��TS) CNend
    \attention \n
    App cann't modify pData. CNcomment:Ӧ�ò�Ҫ�޸�pData ������. CNend
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO or  ENC_ENCODE_VIDEO .CNcomment:���������ͣ�ES������Ƶ�������ݱ���ֿ���ȡ(TS�����÷ֿ�)CNend
    \param[out] pData stream data , audio or video output data.CNcomment:����������Ƶ����Ƶ�������(TS�����÷ֿ���ES��Ҫ�ֿ�)  CNend
    \param[in] u32TimeoutMs time out.CNcomment:��ʱʱ��  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::ERROR_ENC_JNJECT_TIMEOUT time out.CNcomment:��ʱ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_acquire_stream)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,  VOID* const pData, const  U32 u32TimeoutMs);

    /**
    \brief release encoder stream buffer.CNcomment:�ͷŴӱ�������������ж�ȡ������ CNend
    \attention \n
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \param[in] enEncType encoder enc type, ENC_ENCODE_AUDIO or  ENC_ENCODE_VIDEO .CNcomment:���������ͣ�ES������Ƶ�������ݱ���ֿ���ȡ(TS�����÷ֿ�)CNend
    \param[in] pData stream data , audio or video output data.CNcomment:����������Ƶ����Ƶ�������(TS�����÷ֿ���ES��Ҫ�ֿ�)  CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::ENC_ENCODER_TYPE_E

    \par example
    */
    S32 (*enc_release_stream)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, const ENC_ENCODER_TYPE_E enEncType,  VOID* const pData);

    /**
    \brief request fast encoder I frame.CNcomment:������Ƶ������������I ֡ CNend
    \attention \n
    request fast encoder I frame,  For video phone scene.
    CNcomment:���øýӿں�, �������ᾡ������һ��I֡��.   һ�����ڿ��ӵ绰������ͨ�������ʹ���ָ�.
    �˽ӿ�ֻ��"���������"��������һ��I֡��, ����ڶ�ʱ���ڶ�ε��ô˽ӿ�,��ô���ܱ�֤ÿ�ε��ö��ܶ�Ӧ�����һ��I֡��CNend
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (*enc_request_iframe)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc);

    /**
    \brief abort enc.CNcomment:��ֹenc CNend
    \attention \n
    cancel blocking for enc_send_data() and enc_acquire_stream().
    CNcomment: ��ֹenc_send_data(),enc_acquire_stream()
    ��enc_send_data(),enc_acquire_stream().�ĳ�ʱʱ�䲻Ϊ0ʱ,������HAL����, enc_abort()���Խ������,�����˳�.����  ����ʧ��CNend
    \param[in] hEnc encoder handle.CNcomment:��������� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
    \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    */
    S32 (*enc_abort)(struct _ENC_DEVICE_S* pstDev, const HANDLE enc_handle);

    /**
     \brief inject encoder data.CNcomment:����Ƶ������������ CNend
     \attention \n
    Memory mode queue frame data, other mode invalid. This API should be matched with the API: enc_dequeue_frame.
    CNcomment:�ڴ�ģʽ��,�����������ԭʼ������Ƶ���ݣ�����ģʽ��Ч.
    �ýӿ���Ҫ�� enc_dequeue_frame �ӿ����ʹ��CNend
     \param[in] hEnc encoder handle.CNcomment:��������� CNend
     \param[in] pVideoData inject frame data , video source data.CNcomment:ע�����ݣ���ƵԴ����  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
     \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
     \retval ::ERROR_ENC_JNJECT_TIMEOUT time out time.CNcomment:��ʱʱ�䡣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::ENC_ENCODER_TYPE_E

     \par example
    */
    S32 (*enc_queue_frame)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, ENC_VENC_DATA_S * pVideoData);

    /**
     \brief inject encoder data.CNcomment:����Ƶ������������ CNend
     \attention \n
    Memory mode dequeue frame data, other mode invalid. If return SUCCESS, it means the corresponding frame buffer could be set free by user.
    CNcomment:�ڴ�ģʽ��,��������黹ԭʼ������Ƶ���ݣ�����ģʽ��Ч.
    ����ӿڷ��سɹ�����ζ�Ŷ�Ӧ��֡���û������ͷ� CNend
     \param[in] hEnc encoder handle.CNcomment:��������� CNend
     \param[out] pVideoData return frame data , video source data.CNcomment:�黹���ݣ���ƵԴ����  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid handle.CNcomment:������������Ч�ľ����CNend
     \retval ::ERROR_ENC_OP_FAILED lower layer enc operate failed.CNcomment:�ײ��������������CNend
     \retval ::ERROR_ENC_JNJECT_TIMEOUT time out time.CNcomment:��ʱʱ�䡣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::ENC_ENCODER_TYPE_E

     \par example
    */
    S32 (*enc_dequeue_frame)(struct _ENC_DEVICE_S* pstDev, const HANDLE hEnc, ENC_VENC_DATA_S * pVideoData);
} ENC_DEVICE_S;

/**
\brief direct get enc device api, for linux and android.CNcomment:��ȡ�����豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get enc device api, for linux and andorid.
CNcomment:��ȡ�����豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
\retval  enc device pointer when success.CNcomment:�ɹ�����enc�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::ENC_DEVICE_S

\par example
*/
ENC_DEVICE_S* getEncDevice();

/**
\brief  Open HAL AENC/VENC module device.CNcomment:��HAL����Ƶ����ģ���豸 CNend
\attention \n
Open HAL AENC/VENC module device(for compatible Android HAL).
CNcomment:��HAL����Ƶ����ģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice ENC device structure.CNcomment:�������豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ� CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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
\brief Close HAL enc module device.CNcomment: �ر�HAL����ģ���豸 CNend
\attention \n
Close HAL enc module device(for compatible Android HAL).
CNcomment: �ر�HAL����ģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice enc device structure.CNcomment:�����豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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

