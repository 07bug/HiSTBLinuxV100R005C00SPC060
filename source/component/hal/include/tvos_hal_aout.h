/**
 * \file
 * \brief Describes the information about the audio output module.
 */

#ifndef __TVOS_HAL_AOUT_H__
#define __TVOS_HAL_AOUT_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "tvos_hal_type.h"
#include "tvos_hal_av.h"

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

/**Defines the audio output module name*/
/**CNcomment:������Ƶ��� ģ������ */
#define AOUT_HARDWARE_MODULE_ID "audio_output"

/**Defines the audio output device name*/
/**CNcomment:������Ƶ��� �豸���� */
#define AOUT_HARDWARE_AOUT0 "aout0"

/**Platform aout id number.*/
/** CNcomment:aout �豸id ���� */
#define AOUT_ID_NUM 4

/**Auto set the valid values when the values of volume is unvalid*/
/**CNcomment: ���������ڲ��������Ϸ���Χ, ���Զ��޸�Ϊ�Ϸ���Χ.*/

/**Valid range of volume.*/
/**CNcomment:������Χ*/
#define AOUT_VOL_DB_MAX     (12)    /**CNcomment:STB�������Ϊ0������0������ֻ����TV*/
#define AOUT_VOL_DB_ZERO    (0)
#define AOUT_VOL_DB_MIN     (-80)
#define TRACK_VOL_MIN       (0)
#define TRACK_VOL_MAX       (100)
#define TRACK_VOL_DB_MAX    (0)
#define TRACK_VOL_DB_MIN    (-70)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_AOUT */
/** @{ */  /** <!-- [HAL_AOUT] */

/**Aout ID, support multi-aout.*/
/**CNcomment:��Ƶ��� ID��֧�ֶ��aout.*/
typedef enum _AOUT_ID_E
{
    AOUT_ID_0 = 1,
    AOUT_ID_1 = 1 << 1,
    AOUT_ID_2 = 1 << 2,
    AOUT_ID_3 = 1 << 3
} AOUT_ID_E;

/**Device of audio output, can be combined*/
/**CNcomment:��Ƶ����豸�� ����豸����Ҫ֧����Ϸ�ʽ*/
typedef enum _AOUT_DEVICE_TYPE_E
{
    AOUT_DEVICE_NONE = 0,
    AOUT_DEVICE_RCA     = 1,                 /**<CNcomment: ��Ƶ�����������*/
    AOUT_DEVICE_SPDIF   = 1 << 1,            /**<CNcomment: ��ƵSPDIF���*/
    AOUT_DEVICE_HDMI    = 1 << 2,            /**<CNcomment: HDMI��Ƶ��� */
    AOUT_DEVICE_SPEAKER = 1 << 3,            /**<CNcomment: ���������*/
    AOUT_DEVICE_ARC     = 1 << 4,            /**<CNcomment: ARC ���*/
    AOUT_DEVICE_ALL     = (U32) 0xffffffff   /**<CNcomment: ��������豸*/
} AOUT_DEVICE_TYPE_E;

/**Audio output mode*/
/**CNcomment:��Ƶ���ģʽ*/
typedef enum _AOUT_DIGITAL_OUTPUT_MODE_E
{
    AOUT_DIGITAL_OUTPUT_MODE_PCM,            /**<CNcomment: �������*/
    AOUT_DIGITAL_OUTPUT_MODE_RAW,            /**<CNcomment: Դ�����*/
    AOUT_DIGITAL_OUTPUT_MODE_AUTO,           /**<CNcomment: �Զ����, ����HDMI  EDID Э�̣����ȼ�HBR(DD+/DTSHD) > LBR(DD/DTS) > PCM */
} AOUT_DIGITAL_OUTPUT_MODE_E;

/**Audio data format.*/
/**CNcomment:��Ƶ���ݸ�ʽ*/
typedef enum _AOUT_DATA_FORMAT_E
{
    AOUT_DATA_FORMAT_LE_PCM_16_BIT,                 /**< 16bit ����pcm, С�˸�ʽ */
    AOUT_DATA_FORMAT_EXTENSIONS = (U32)0x10000000,  /**<Reserved region*/ /**<CNcomment: ������չ*/
    AOUT_DATA_FORMAT_BUTT = (U32)0x7fffffff
} AOUT_DATA_FORMAT_E;

/**Channel mode.*/
/**CNcomment:����ģʽ*/
typedef enum _AOUT_CHANNEL_MODE_E
{
    AOUT_CHANNEL_MONO = 0,                  /**<Data is output after being mixed in the audio-left channel and audio-right channel.*//**<CNcomment: �����*/
    AOUT_CHANNEL_RIGHT,                     /**<The audio-left channel and audio-right channel output the data of the audio-right channel.*//**<CNcomment: ������*/
    AOUT_CHANNEL_LEFT,                      /**<The audio-left channel and audio-right channel output the data of the audio-left channel.*//**<CNcomment: ������*/
    AOUT_CHANNEL_STER,                      /**<Stero*//**<CNcomment: ������*/
    AOUT_CHANNEL_BUTT
} AOUT_CHANNEL_MODE_E;

/**CNcomment: ������Ƶ����ģʽö��*/
typedef enum _TRACK_MODE_E
{
    TRACK_MODE_STEREO = 0,          /**<Stereo*/ /**<CNcomment: ������*/
    TRACK_MODE_DOUBLE_MONO,         /**<Data is output after being mixed in the audio-left channel and audio-right channel.*/ /**<CNcomment: ����������Ϻ����*/
    TRACK_MODE_DOUBLE_LEFT,         /**<The audio-left channel and audio-right channel output the data of the audio-left channel.*/ /**<CNcomment: ���������������������*/
    TRACK_MODE_DOUBLE_RIGHT,        /**<The audio-left channel and audio-right channel output the data of the audio-right channel.*/ /**<CNcomment: ���������������������*/
    TRACK_MODE_EXCHANGE,            /**<Data is output after being exchanged in the audio-left channel and audio-right channel.*/ /**<CNcomment: �����������ݽ������ */
    TRACK_MODE_ONLY_RIGHT,          /**<Only the data in the audio-right channel is output.*/ /**<CNcomment: ֻ�������������*/
    TRACK_MODE_ONLY_LEFT,           /**<Only the data in the audio-left channel is output.*/ /**<CNcomment: ֻ�������������*/
    TRACK_MODE_MUTED,               /**<Mute*/ /**<CNcomment: ����*/
    TRACK_MODE_BUTT
} TRACK_CHANNEL_MODE_E;

typedef struct _TRACK_GAIN_ATTR_S
{
    BOOL bLinearMode; /**< gain type of volume*/ /**<CNcomment:����ģʽ */
    S32  s32Gain; /**<Linear gain(bLinearMode is TRUE) , ranging from 0 to 100*/ /**<CNcomment:��������: 0~100 */
                  /**<Decibel gain(bLinearMode is FALSE) , ranging from -70dB to 0dB */ /**<CNcomment: dB����:-70~0*/
} TRACK_GAIN_ATTR_S;
/**Struct of create param of audio track */
/**CNcomment:Aout track ��������*/
typedef struct _AOUT_TRACK_PARAMS_S
{
    AOUT_DATA_FORMAT_E enFormat;             /**<Data format *//**<CNcomment:  ���ݸ�ʽ */
    BOOL               bPtsSync;             /**<pts sync flag*/ /**<CNcomment: �Ƿ�֧��Ptsͬ�� */
    U32                u32SampleRate;        /**<Sample rate *//**<CNcomment:  ����Ƶ�� */
    U32                u32Channels;          /**<Audio channels *//**<CNcomment:  ���� */
    U32                u32BufferSize;        /**<Audio data buffer size *//**<CNcomment: ���ݻ�������С */
} AOUT_TRACK_PARAMS_S;

typedef struct _AOUT_TRACK_PASSTHROUGHDATA
{
    /** s32BitPerSample: (PCM) Data depth, and format of storing the output data
          If the data depth is 16 bits, 16-bit word memory is used.
          If the data depth is greater than 16 bits, 32-bit word memory is used, and data is stored as left-aligned data. That is, the valid data is at upper bits.
     */
    /**CNcomment: s32BitPerSample: (PCM) ����λ������. �����Ÿ�ʽ
          ����16bit:   ռ��16bit word�ڴ�
          ����16bit:   ռ��32bit word�ڴ�, ��������뷽ʽ���(��Ч�����ڸ�λ)
     */
    U32  u32BitPerSample;       /**<Data depth*/ /**<CNcomment: ����λ��*/
    U32  u32Interleaved;        /**<Whether the data is interleaved*/ /**<CNcomment: �����Ƿ�֯*/
    U32  u32SampleRate;         /**<Sampling rate*/ /**<CNcomment: ������*/
    U32  u32Channels;           /**<Number of channels*/ /**<CNcomment: ͨ������*/
    U32  u32PtsMs;              /**<Presentation time stamp (PTS)*/ /**<CNcomment: ʱ���*/
    S32 *ps32PcmBuffer;         /**<Pointer to the buffer for storing the pulse code modulation (PCM) data*/ /**<CNcomment: PCM���ݻ���ָ��*/
    S32 *ps32BitsBuffer;        /**<Pointer to the buffer for storing the stream data*/ /**<CNcomment: �������ݻ���ָ��*/
    U32  u32PcmSamplesPerFrame; /**<Number of sampling points of the PCM data*/ /**<CNcomment: PCM���ݲ���������*/
    U32  u32BitsBytesPerFrame;  /**<IEC61937 data size*/ /**<CNcomment: IEC61937���ݳ���*/
    U32  u32FrameIndex;         /**<Frame ID*/ /**<CNcomment: ֡��� */
    U32  u32IEC61937DataType;   /**<IEC61937 Data Type*/ /**<CNcomment: IEC61937�������ͱ�ʶ����8bitΪIEC�������� */
} AOUT_TRACK_PASSTHROUGHDATA;

/**Struct of audio track mix param
1. s16IntGain, the device must support AOUT_VOL_DB_ZERO and above.
2. s16DecGain,  if the device do not support gain fine tunning, ignore it.
*/
/**CNcomment:Aout track ��������
1. s16IntGain,   �豸������Ҫ֧��AOUT_VOL_DB_ZERO ����������.
2. s16DecGain,  �豸��֧��С������΢�����ɺ��Ըò���.
*/
typedef struct _AOUT_TRACK_MIX_PARAMS_S
{
    S32 s32IntGain;    /**<Integer part of volume*//**<CNcomment: ��������ֵ���������֣���Χ[AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX],  ����(1.0 dB ) */
    S32 s32DecGain;    /**<Fractional part of volume*//**<CNcomment: ��������ֵ��С�����֣���Χ(0~7),    ����(0.125 dB  */
    U32 u32Dummy;      /**<Reserved*//**<CNcomment: �Ժ���չ�� */
} AOUT_TRACK_MIX_PARAMS_S;

/**Struct of init param of audio output*/
/**CNcomment:��Ƶ���ģ���ʼ������*/
typedef struct _AOUT_INIT_PARAMS_S
{
    U32 u32Dummy;                         /**<Reserved*//**<CNcomment: �Ժ���չ�� */
} AOUT_INIT_PARAMS_S;

/**Struct of settings param of audio output*/
/**CNcomment:��Ƶ��� ���ò���*/
typedef struct _AOUT_SETTINGS_S
{
    AOUT_DEVICE_TYPE_E enOutputDevice;
    U32                u32Dummy;          /**<Reserved*//**<CNcomment: �Ժ���չ�� */
} AOUT_SETTINGS_S;

/**Struct of audio output capability*/
/**CNcomment:��Ƶ��� ģ�������*/
typedef struct _AOUT_CAPABILITY_S
{
    U8                 u8SupportedIdNum;
    AOUT_DEVICE_TYPE_E enOutputDevice[AOUT_ID_NUM];        /**<Audio output device*//**<CNcomment:��Ƶ����豸 */
    U8                 u8SupportedTrackNum[AOUT_ID_NUM];    /**<Max track number supported*//**<CNcomment:   track  ���ͨ���� */
} AOUT_CAPABILITY_S;

/**Struct of terminate param*/
/**CNcomment:ģ����ֹ����*/
typedef struct _AOUT_TERM_PARAMS_S
{
    U32 u32Dummy;               /**<Reserved*//**<CNcomment: �Ժ���չ�� */
} AOUT_TERM_PARAMS_S;

/**Struct of open param of Aout instance*/
/**CNcomment:��Ƶ��� ʵ���򿪲���*/
typedef struct _AOUT_OPEN_PARAMS_S
{
    AOUT_ID_E       enId;       /**<Audio output ID*//**<CNcomment:��Ƶ��� ID */
    AOUT_SETTINGS_S stSettings; /**<Audio output settings*//**<CNcomment:��Ƶ��� ����*/
} AOUT_OPEN_PARAMS_S;

/**Struct of close param of Aout instance*/
/**CNcomment:��Ƶ��� ʵ���رղ���*/
typedef struct _AOUT_CLOSE_PARAMS_S
{
    U32 u32Dummy;               /**<Reserved*//**<CNcomment: �Ժ���չ�� */
} AOUT_CLOSE_PARAMS_S;

#ifdef HAL_HISI_EXTEND_H

/**Defines the type of AOUT invoke.*/
/**CNcomment: ����AOUT Invoke�������͵�ö�� */
typedef enum _AOUT_INVOKE_E
{
    AOUT_INVOKE_REG_CALLBACK = 0x0,             /**<Invoke command to register aout callback*//**<CNcomment: ע��aout���ⲿ�����Ļص��ӿ� */
    AOUT_INVOKE_GET_DOLBY_ATMOS_FLAG,           /**<Invoke command to get dolby atmos output flag, param type is BOOL*//**<CNcomment: ��ȡaout�Ƿ���DOLBY ATMOS���,����������BOOL */
    AOUT_INVOKE_BUTT
} AOUT_INVOKE_E;

#endif

#ifdef ANDROID_HAL_MODULE_USED
/**Audio output module structure(Android require)*/
/**CNcomment:��Ƶ���ģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _AOUT_MODULE_S
{
    struct hw_module_t stCommon;
} AOUT_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_AOUT*/
/** @{*/  /** <!-- -HAL_AOUT=*/

/**Audio out device structure*//** CNcomment:��Ƶ����豸�ṹ*/
typedef struct _AOUT_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
     \brief Audio output init.CNcomment:��Ƶ�����ʼ�� CNend
     \attention \n
    Other functions cannot be useful before init, return SUCCESS when repeated called.
    CNcomment: �ڳ�ʼ��֮ǰ, ����������������ȷ����, �ظ�����init �ӿ�,����SUCCESS. CNend
     \param[in] pstInitParams Vout module init param.CNcomment:��ʼ��ģ����� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_INIT_FAILED  other error.CNcomment:�������� CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_INIT_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_init)(struct _AOUT_DEVICE_S* pstDev, const AOUT_INIT_PARAMS_S* pstInitParams);

    /**
     \brief Terminate video output module. CNcomment:ģ����ֹ CNend
     \attention \n
    Return SUCCESS when repeated called.
    CNcomment: �ظ�term ����SUCCESS. CNend
     \param[in] pstTermParams Terminate param,  if NULL, force to terminate.CNcomment:��ֹģ�������ΪNULL  ��ʾǿ����ֹ CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_TERM_FAILED  other error.CNcomment:�������� CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \see \n
    ::AOUT_TERM_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_term)(struct _AOUT_DEVICE_S* pstDev, const AOUT_TERM_PARAMS_S* pstTermParams);

    /**
     \brief Get the capability of audio ouput module. CNcomment:��ȡģ���豸���� CNend
     \attention \n
    CNcomment: ��CNend
     \param[out] pstCapability Capability param.CNcomment:ģ���������� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_CAPABILITY_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_capability)(struct _AOUT_DEVICE_S* pstDev, AOUT_CAPABILITY_S* pstCapability);

    /**
     \brief Open a audio output instance.CNcomment:��һ����Ƶ���ʵ�� CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] pstOpenParams Open param.CNcomment:ʵ���򿪲��� CNend
     \param[out] phAout Return AOUT handle .CNcomment:����AOUT��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
     \retval ::ERROR_AO_OPEN_FAILED  Other error.CNcomment:�������� CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::VOUT_OPEN_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_open)(struct _AOUT_DEVICE_S* pstDev, HANDLE* phAout, const AOUT_OPEN_PARAMS_S* pstOpenParams);

    /**
     \brief Close a audio output instance.CNcomment:�ر�һ����Ƶ���ʵ�� CNend
     \attention \n
    If hAout is the last instance of the device, relese hardware resource at the same time
    CNcomment: ���aout_close()����close ����AOUT_ID_E �ϵ����һ��hAout, �ͷ�Ӳ����Դ.CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[in] pstCloseParams Close param.CNcomment:ʵ���رղ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_AO_CLOSE_FAILED  other error.CNcomment:�������� CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_CLOSE_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_close)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout, const AOUT_CLOSE_PARAMS_S* pstCloseParams);

    /**
     \brief Set the volume of audio output device.CNcomment:��������豸���� CNend
     \attention \n
    1. s32IntGain, the device must support AOUT_VOL_DB_ZERO and above.
    2. s32DecGain,  if the device do not support gain fine tunning, ignore it.
    CNcomment:
    1. s16IntGain, �豸������Ҫ֧��AOUT_VOL_DB_ZERO ����������.
    2. s16DecGain,  �豸��֧��С������΢�����ɺ��Ըò���.
    CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸����CNend
     \param[in] s32IntGain Integer part of volume, the range is [AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX], step is (1.0 dB ) .CNcomment:����ֵ���������֣���Χ[AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX],  ����(1.0 dB )  CNend
     \param[in] s32DecGain Fractional part of volume, the range is (0~7), step is(0.125 dB ).CNcomment:����ֵ��С�����֣���Χ(0~7),  ����(0.125 dB ) CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_volume)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout, AOUT_DEVICE_TYPE_E enOutputDevice,
                           S32 s32IntGain, S32 s32DecGain);

    /**
     \brief Get the volume of audio output device.CNcomment:��ȡ����豸���� CNend
     \attention \n
    1. ps32IntGain, the device must support AOUT_VOL_DB_ZERO and above.
    2. ps32DecGain,  if the device do not support gain fine tunning, ignore it.
    CNcomment:
    1. ps32IntGain, �豸������Ҫ֧��AOUT_VOL_DB_ZERO ����������.
    2. ps32DecGain,  �豸��֧��С������΢�����ɺ��Ըò���.
    CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸 CNend
     \param[out] ps32IntGain Return integer part of volume, the range is [AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX] .CNcomment:����ֵ���������֣���Χ[AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX] CNend
     \param[out] ps32DecGain Return fractianl part of volume, the range is (0~7).CNcomment:����ֵ��С�����֣���Χ(0~7) CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_volume)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout, AOUT_DEVICE_TYPE_E enOutputDevice,
                           S32* ps32IntGain, S32* ps32DecGain);

    /**
     \brief Set digital output mode.CNcomment:�����������ģʽ CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸 CNend
     \param[in] enMode Output mode .CNcomment:���ģʽCNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_DIGITAL_OUTPUT_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_digital_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                                 AOUT_DEVICE_TYPE_E enOutputDevice, AOUT_DIGITAL_OUTPUT_MODE_E enMode);

    /**
     \brief Get digital output mode.CNcomment:��ȡ�������ģʽ CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸 CNend
     \param[out] penMode Return output mode .CNcomment:�������ģʽCNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_DIGITAL_OUTPUT_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_digital_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                                 AOUT_DEVICE_TYPE_E enOutputDevice, AOUT_DIGITAL_OUTPUT_MODE_E* penMode);

    /**
     \brief Set output device mute.CNcomment:����������� CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸 CNend
     \param[in] bMute TRUE:mute, FALSE:mute .CNcomment:TRUE: ���þ���, FALSE: ��������CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_mute)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                         AOUT_DEVICE_TYPE_E enOutputDevice, BOOL bMute);

    /**
     \brief Get mute status of output device .CNcomment:��ȡ����״̬ CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸 CNend
     \param[out] bMute TRUE:mute, FALSE:mute .CNcomment:TRUE: ���þ���, FALSE: ��������CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_mute)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                         AOUT_DEVICE_TYPE_E enOutputDevice, BOOL* pbMute);

    /**
     \brief Set track mode of output device .CNcomment:��������ģʽ CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸 CNend
     \param[in] enMode Track mode .CNcomment:����ģʽCNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_channel_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                                 AOUT_DEVICE_TYPE_E enOutputDevice, AOUT_CHANNEL_MODE_E enMode);

    /**
     \brief Get track mode of output device .CNcomment:��ȡ����ģʽ CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸 CNend
     \param[out] penMute Return track mode .CNcomment:��������ģʽCNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_channel_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                                 AOUT_DEVICE_TYPE_E enOutputDevice, AOUT_CHANNEL_MODE_E* penMode);

#ifdef HAL_HISI_EXTEND_H
    /**
     \brief Set aout config.CNcomment:����aout���������
     \attention \n
    CNcomment:��CNend
     \param[in] hAout aout handle.CNcomment:aout ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸 CNend
     \param[in] u32Index config index.CNcomment:Config indexCNend
     \param[in] pConfig point to config.CNcomment:ָ��config��ָ�� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_config)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                          AOUT_DEVICE_TYPE_E enOutputDevice, U32 u32Index, const VOID* pConfig);

    /**
     \brief Get aout config.CNcomment:��ȡaout���������
     \attention \n
    CNcomment:��CNend
     \param[in] hAout aout handle.CNcomment:aout ��� CNend
     \param[in] enOutputDevice Output device.CNcomment:����豸 CNend
     \param[in] u32Index config index.CNcomment:Config indexCNend
     \param[out] pConfig point to config.CNcomment:ָ��config��ָ�� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_config)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                          AOUT_DEVICE_TYPE_E enOutputDevice, U32 u32Index, VOID* pConfig);


    /**
    \brief aout invoke function, extend other function by user.
    CNcomment:invoke ��չ�ӿڣ������û�˽�й�����չ
    \attention \n
    None
    \param[in] hInvokeHandle the handle of Invoke Command, aout handle or track handle.CNcomment:Invloke������Ҫ�ľ����aout�����track��� CNend
    \param[in] eCmd Invoke ID, defined is ::AOUT_INVOKE_E.CNcomment:Invoke ID, ������� ::AOUT_INVOKE_E CNend
    \param[in,out] pArg Command parameter.CNcomment:������� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE other error.CNcomment:�������� CNend
    \see \n
    ::AOUT_INVOKE_E

    \par example
    \code
    \endcode
    */
    S32 (*aout_invoke)(struct _AOUT_DEVICE_S* pstDev, const HANDLE hInvokeHandle, AOUT_INVOKE_E eCmd, VOID* pArg);

#endif
    /**
     \brief get default track attr .CNcomment:��ȡĬ�ϵ�track����
     \attention \n
    CNcomment:��CNend
     \param[out] pstParams track param.CNcomment:����ָ�� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_default_attr)(struct _AOUT_DEVICE_S* pstDev, AOUT_TRACK_PARAMS_S* pstParams);

    /**
     \brief Create a track instance, disabled dafautly after created .CNcomment:����һ��track  ͨ��ʵ�� ,  create����disable״̬ CNend
     \attention \n
    1. Multi tracks output to the same device(RCA/SPDIF/HDMI, etc.) after mixed.
    2. When bind source and track , track param(AOUT_TRACK_PARAMS_S) can be set dynamicly.
    3. When playback, not attach,  track param must be set correctly, you must stop track before renew track param.
    CNcomment:
    1.  ���track ����Ƶ�����������ͬһ��aout ��enOutputDevice(RCA/SPDIF/HDMI��)
    2. source ��track �󶨳���(attach)��source ���Զ�̬����track ��AOUT_TRACK_PARAMS_S
    3. playback ����(��attach)��������ȷ����track ��AOUT_TRACK_PARAMS_S,  �����Ҫ�޸Ĳ�����������stop track
    CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT ��� CNend
     \param[out] phTrack Return track handle.CNcomment:����track ��� CNend
     \param[in] pstParams Track param .CNcomment:����track  �Ĳ���CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_TRACK_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_create)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout, HANDLE* phTrack,
                        const AOUT_TRACK_PARAMS_S* pstParams);

    /**
     \brief Destroy a track instance .CNcomment:����һ��track  ͨ��ʵ��CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_destroy)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Attach source and track .CNcomment:��source �������Ƶtrack ͨ�� .CNend
     \attention \n
    Track will be started after attached.
    CNcomment:�󶨺�track ����start ״̬.CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[in] hSource Source handle,  source module handle or av module handle.
     CNcomment:���󶨵�source ������þ����sourceģ���avģ���� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_attach_input)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, HANDLE hSource);

    /**
     \brief Detach source and track .CNcomment:��track���� ��source ��� .CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[in] hSource Source handle.CNcomment:���󶨵�source ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_detach_input)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, HANDLE hSource);

    /**
     \brief Start track, the device of Aout will outoput the audio data .CNcomment:���� track ͨ����track ��Ƶ���ݿ��Դ�aout ��� .CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_start)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Stop track, the audio data in the buffer will be cleared.CNcomment:ֹͣtrack ͨ����ͨ��buffer ����Ƶ���ݱ���� .CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_stop)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Notifies to the aout  to stop track however the queued buffers are retained by the track. Useful for implementing pause/resume.
     CNcomment: ��ͣ track ͨ����track ��Ƶ����ֹͣ��aout ��� .CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_pause)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Notifies to the aout to resume the track playback following a pause.
     \ Returns error if called without matching pause.CNcomment: �ָ�track ͨ����ͨ��buffer ����Ƶ���ݼ������ .CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_resume)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Notifies to the aout driver to flush the queued data. track must already be paused before calling flush() .
     CNcomment: �ָ�track ͨ����ͨ��buffer ����Ƶ���ݼ������ .CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_flush)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Set param fo track.CNcomment:����track ����.CNend
     \attention \n
    Stop track before set param fo track
    CNcomment:ͨ��stop �󣬲�������track ����CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[in] pstParams Track param.CNcomment:Track ���� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_TRACK_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_set_params)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                            const AOUT_TRACK_PARAMS_S* pstParams);

    /**
     \brief Get param fo track.CNcomment:��ȡtrack ����.CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[out] pstParams Return param of track.CNcomment:����track ���� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_TRACK_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_get_params)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                            AOUT_TRACK_PARAMS_S* pstParams);

    /**
     \brief Set mix param of track.CNcomment:����track ��������.CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[in] pstParams Mix param.CNcomment:�������� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_TRACK_MIX_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_set_mix_params)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                                const AOUT_TRACK_MIX_PARAMS_S* pstParams);

    /**
     \brief Get mix param of track.CNcomment:��ȡtrack ��������.CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[out] pstParams Return mix param.CNcomment:���ػ������� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_TRACK_MIX_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_get_mix_params)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                                AOUT_TRACK_MIX_PARAMS_S* pstParams);

    /**
     \brief Set track mute.CNcomment:����TRACK���� CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hTrack ATRACK handle.CNcomment:HTRACK ��� CNend
     \param[in] bMute TRUE:mute, FALSE:mute .CNcomment:TRUE: ���þ���, FALSE: ��������CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*track_set_mute)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, BOOL bMute);
    /**
     \brief Get mute status of track .CNcomment:��ȡTRACK ����״̬ CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hTrack ATRACK handle.CNcomment:HTRACK ��� CNend
     \param[out] *bMute TRUE:mute, FALSE:mute .CNcomment:��ȡ����CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*track_get_mute)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, BOOL *pbMute);
    /**
     \brief Set channel mode of track .CNcomment:��������ģʽ CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hTrack handle.CNcomment:TRACK ��� CNend
     \param[in] enMode Track mode .CNcomment:����ģʽCNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*track_set_channel_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, TRACK_CHANNEL_MODE_E enMode);

   /**
     \brief Get channel mode of track .CNcomment:��ȡ����ģʽ CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hTrack handle.CNcomment:HTRACK ��� CNend
     \param[out] penMute Return track mode .CNcomment:��������ģʽCNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*track_get_channel_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, TRACK_CHANNEL_MODE_E *penMode);

   /**
     \brief set track weight .CNcomment:��������Ȩ�� CNend
     \attention \n
    CNcomment: ��CNend
     \param[in] hTrack handle.CNcomment:HTRACK ��� CNend
     \param[in] stTrackGainAttr .CNcomment:����Ȩ��CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

      \par example
      \code
      \endcode
      */
    S32 (*track_set_weight)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                                const TRACK_GAIN_ATTR_S stTrackGainAttr);
    /**
      \brief get track weight.CNcomment:��ȡ����Ȩ�� CNend
      \attention \n
     CNcomment: ��CNend
      \param[in] hTrack handle.CNcomment:HTRACK ��� CNend
      \param[out] pstMixWeightGain .CNcomment:����Ȩ��CNend
      \retval ::SUCCESS CNcomment:�ɹ� CNend
      \retval ::HI_ERR_AO_SOUND_NOT_OPEN  Module has not been inited.CNcomment:ʵ��δ�򿪡�CNend
      \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
      \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
      \retval ::FAILURE  other error.CNcomment:�������� CNend
      \see \n
     ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

      \par example
      \code
      \endcode
      */
    S32 (*track_get_weight)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                                        TRACK_GAIN_ATTR_S* pstTrackGainAttr);
    /**
     \brief return the number of audio frames written by the aout to HW such as DAC/SPDIF/HDMI since
     * the output has exited standby. CNcomment:��ȡ�����Ӳ������Ƶ֡������λ: .CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[out] pu32Frames Return frame of track wirtten to HW.CNcomment:�����Ѿ������Ӳ������Ƶ֡�� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_render_position)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32* pu32Frames);
    /**
     \brief Get pts of data in the track buf, unit: ms.CNcomment:��ȡtrack ��ǰ���ŵ�pts����λ: ms
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[out] pS64Pts Return pts.CNcomment:����pts ��С CNend
     \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_NOT_SUPPORTED  Track is not support to require pts.CNcomment:Track ��֧�ֻ�ȡpts��CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_pts)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, S64* ps64Pts);
    /**
     \brief adjust track data consume speed, unit: ms.CNcomment:��track�Ĳ��Ž��е���
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[in] s32Speed consume speed(-100~100), ms.CNcomment:�����ٶ�(-100~100)������
     \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_NOT_SUPPORTED  Track is not support to require pts.CNcomment:Track ��֧�ֻ�ȡpts��CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_adjust_speed)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, S32 s32Speed);
    /**
     \brief Get free szie of track buf, Unit: Byte.CNcomment:��ȡtrack buf ʣ��ռ䣬��λ: Byte.CNend
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[out] pu32Bytes Return free size of track buf.CNcomment:����ʣ���ֽ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_buf_avail)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32* pu32Bytes);

    /**
     \brief Get play time of data in the track buf, unit: ms.CNcomment:��ȡtrack buf �ɲ������ݵ�ʱ������λ: ms
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[out] pu32Latency Return play time.CNcomment:���ز���ʱ�� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_latency)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32* pu32Latency);

    /**
     \brief Write audio data to track buffer.CNcomment:��track buf  д������ŵ���Ƶ��
     \attention \n
    This function is blocking operation, you should confirm enough size by track_get_buf_avail
    CNcomment:������Ϊ����������д��ǰ����ͨ��track_get_buf_avail ȷ���Ƿ����㹻�ռ䣬���򽫻����̷���ʧ��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[in] pvbuffer Data address.CNcomment:Դ���ݵ�ַCNend
     \param[in] u32Bytes Data length.CNcomment:Դ�����ֽ��� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_write)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, const void* pvBuffer, U32 u32Bytes);

    /**
     \brief Write audio data to track buffer(include transmission data or PCM data).CNcomment:��track buf  д������ŵ���Ƶ����(����͸����PCM����)
     \attention \n
    This function is blocking operation, you should confirm enough size by track_get_buf_avail
    CNcomment:������Ϊ����������д��ǰ����ͨ��track_get_buf_avail ȷ���Ƿ����㹻�ռ䣬���򽫻����̷���ʧ��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[in] pstData Data struct.CNcomment:Դ���ṹ���ַCNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend

     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_write_passthrough)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, AOUT_TRACK_PASSTHROUGHDATA* pstData);

    /**
     \brief Set track config, CNcomment:����Track config
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[in] u32Index config index.CNcomment:Config indexCNend
     \param[in] pConfig point to config.CNcomment:ָ��config��ָ�� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_set_config)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32 u32Index, VOID* pConfig);

    /**
     \brief Get track config.CNcomment:��ȡTrack���������
     \attention \n
    CNcomment:��CNend
     \param[in] hTrack Track handle.CNcomment:Track ��� CNend
     \param[in] u32Index config index.CNcomment:Config indexCNend
     \param[out] pConfig point to config.CNcomment:ָ��config��ָ�� CNend
     \retval ::SUCCESS CNcomment:�ɹ� CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track ʵ��δ������CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_config)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32 u32Index, VOID* pConfig);
} AOUT_DEVICE_S;

/**
 \brief direct get aout device api, for linux and android.CNcomment:��ȡ��Ƶ�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
 \attention \n
get aout device api��for linux and andorid.
CNcomment:��ȡ��Ƶ�豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
 \retval  aout device pointer when success.CNcomment:�ɹ�����aout�豸ָ�롣CNend
 \retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
 \see \n
::AOUT_DEVICE_S

 \par example
 */
AOUT_DEVICE_S* getAOutDevice();

/**
\brief Open HAL Audio output module device.CNcomment:��HAL��Ƶ���ģ���豸 CNend
\attention \n
Open HAL Audio output module device(for compatible android HAL).
CNcomment:��HAL��Ƶ���ģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice Audio output device structure.CNcomment:��Ƶ����豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::AOUT_DEVICE_S

\par example
*/
static inline int aout_open(const struct hw_module_t* pstModule, AOUT_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, AOUT_HARDWARE_AOUT0, (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getAOutDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL Audio output module device.CNcomment:�ر�HAL��Ƶ���ģ���豸 CNend
\attention \n
Close HAL Audio output module device(for compatible Android HAL).
CNcomment:�ر�HAL��Ƶ���ģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice Audio output device structure.CNcomment:��Ƶ����豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::AOUT_DEVICE_S

\par example
*/
static inline int aout_close(AOUT_DEVICE_S* pstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstDevice->stCommon.close(&pstDevice->stCommon);
#else
    return SUCCESS;
#endif
}

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*__TVOS_HAL_AOUT_H__*/

/* EOF */
