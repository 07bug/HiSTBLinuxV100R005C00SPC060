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
/**CNcomment:定义音频输出 模块名称 */
#define AOUT_HARDWARE_MODULE_ID "audio_output"

/**Defines the audio output device name*/
/**CNcomment:定义音频输出 设备名称 */
#define AOUT_HARDWARE_AOUT0 "aout0"

/**Platform aout id number.*/
/** CNcomment:aout 设备id 个数 */
#define AOUT_ID_NUM 4

/**Auto set the valid values when the values of volume is unvalid*/
/**CNcomment: 如果音量入口参数超出合法范围, 将自动修复为合法范围.*/

/**Valid range of volume.*/
/**CNcomment:音量范围*/
#define AOUT_VOL_DB_MAX     (12)    /**CNcomment:STB最大音量为0，大于0的音量只用于TV*/
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
/**CNcomment:音频输出 ID，支持多个aout.*/
typedef enum _AOUT_ID_E
{
    AOUT_ID_0 = 1,
    AOUT_ID_1 = 1 << 1,
    AOUT_ID_2 = 1 << 2,
    AOUT_ID_3 = 1 << 3
} AOUT_ID_E;

/**Device of audio output, can be combined*/
/**CNcomment:音频输出设备， 输出设备类型要支持组合方式*/
typedef enum _AOUT_DEVICE_TYPE_E
{
    AOUT_DEVICE_NONE = 0,
    AOUT_DEVICE_RCA     = 1,                 /**<CNcomment: 音频左右声道输出*/
    AOUT_DEVICE_SPDIF   = 1 << 1,            /**<CNcomment: 音频SPDIF输出*/
    AOUT_DEVICE_HDMI    = 1 << 2,            /**<CNcomment: HDMI音频输出 */
    AOUT_DEVICE_SPEAKER = 1 << 3,            /**<CNcomment: 扬声器输出*/
    AOUT_DEVICE_ARC     = 1 << 4,            /**<CNcomment: ARC 输出*/
    AOUT_DEVICE_ALL     = (U32) 0xffffffff   /**<CNcomment: 所有输出设备*/
} AOUT_DEVICE_TYPE_E;

/**Audio output mode*/
/**CNcomment:音频输出模式*/
typedef enum _AOUT_DIGITAL_OUTPUT_MODE_E
{
    AOUT_DIGITAL_OUTPUT_MODE_PCM,            /**<CNcomment: 解码输出*/
    AOUT_DIGITAL_OUTPUT_MODE_RAW,            /**<CNcomment: 源码输出*/
    AOUT_DIGITAL_OUTPUT_MODE_AUTO,           /**<CNcomment: 自动输出, 根据HDMI  EDID 协商，优先级HBR(DD+/DTSHD) > LBR(DD/DTS) > PCM */
} AOUT_DIGITAL_OUTPUT_MODE_E;

/**Audio data format.*/
/**CNcomment:音频数据格式*/
typedef enum _AOUT_DATA_FORMAT_E
{
    AOUT_DATA_FORMAT_LE_PCM_16_BIT,                 /**< 16bit 线性pcm, 小端格式 */
    AOUT_DATA_FORMAT_EXTENSIONS = (U32)0x10000000,  /**<Reserved region*/ /**<CNcomment: 用于扩展*/
    AOUT_DATA_FORMAT_BUTT = (U32)0x7fffffff
} AOUT_DATA_FORMAT_E;

/**Channel mode.*/
/**CNcomment:声道模式*/
typedef enum _AOUT_CHANNEL_MODE_E
{
    AOUT_CHANNEL_MONO = 0,                  /**<Data is output after being mixed in the audio-left channel and audio-right channel.*//**<CNcomment: 混合声*/
    AOUT_CHANNEL_RIGHT,                     /**<The audio-left channel and audio-right channel output the data of the audio-right channel.*//**<CNcomment: 右声道*/
    AOUT_CHANNEL_LEFT,                      /**<The audio-left channel and audio-right channel output the data of the audio-left channel.*//**<CNcomment: 左声道*/
    AOUT_CHANNEL_STER,                      /**<Stero*//**<CNcomment: 立体声*/
    AOUT_CHANNEL_BUTT
} AOUT_CHANNEL_MODE_E;

/**CNcomment: 定义音频声道模式枚举*/
typedef enum _TRACK_MODE_E
{
    TRACK_MODE_STEREO = 0,          /**<Stereo*/ /**<CNcomment: 立体声*/
    TRACK_MODE_DOUBLE_MONO,         /**<Data is output after being mixed in the audio-left channel and audio-right channel.*/ /**<CNcomment: 左右声道混合后输出*/
    TRACK_MODE_DOUBLE_LEFT,         /**<The audio-left channel and audio-right channel output the data of the audio-left channel.*/ /**<CNcomment: 左右声道输出左声道数据*/
    TRACK_MODE_DOUBLE_RIGHT,        /**<The audio-left channel and audio-right channel output the data of the audio-right channel.*/ /**<CNcomment: 左右声道输出右声道数据*/
    TRACK_MODE_EXCHANGE,            /**<Data is output after being exchanged in the audio-left channel and audio-right channel.*/ /**<CNcomment: 左右声道数据交换输出 */
    TRACK_MODE_ONLY_RIGHT,          /**<Only the data in the audio-right channel is output.*/ /**<CNcomment: 只输出右声道数据*/
    TRACK_MODE_ONLY_LEFT,           /**<Only the data in the audio-left channel is output.*/ /**<CNcomment: 只输出左声道数据*/
    TRACK_MODE_MUTED,               /**<Mute*/ /**<CNcomment: 静音*/
    TRACK_MODE_BUTT
} TRACK_CHANNEL_MODE_E;

typedef struct _TRACK_GAIN_ATTR_S
{
    BOOL bLinearMode; /**< gain type of volume*/ /**<CNcomment:音量模式 */
    S32  s32Gain; /**<Linear gain(bLinearMode is TRUE) , ranging from 0 to 100*/ /**<CNcomment:线性音量: 0~100 */
                  /**<Decibel gain(bLinearMode is FALSE) , ranging from -70dB to 0dB */ /**<CNcomment: dB音量:-70~0*/
} TRACK_GAIN_ATTR_S;
/**Struct of create param of audio track */
/**CNcomment:Aout track 创建参数*/
typedef struct _AOUT_TRACK_PARAMS_S
{
    AOUT_DATA_FORMAT_E enFormat;             /**<Data format *//**<CNcomment:  数据格式 */
    BOOL               bPtsSync;             /**<pts sync flag*/ /**<CNcomment: 是否支持Pts同步 */
    U32                u32SampleRate;        /**<Sample rate *//**<CNcomment:  采样频率 */
    U32                u32Channels;          /**<Audio channels *//**<CNcomment:  声道 */
    U32                u32BufferSize;        /**<Audio data buffer size *//**<CNcomment: 数据缓冲区大小 */
} AOUT_TRACK_PARAMS_S;

typedef struct _AOUT_TRACK_PASSTHROUGHDATA
{
    /** s32BitPerSample: (PCM) Data depth, and format of storing the output data
          If the data depth is 16 bits, 16-bit word memory is used.
          If the data depth is greater than 16 bits, 32-bit word memory is used, and data is stored as left-aligned data. That is, the valid data is at upper bits.
     */
    /**CNcomment: s32BitPerSample: (PCM) 数据位宽设置. 输出存放格式
          等于16bit:   占用16bit word内存
          大于16bit:   占用32bit word内存, 数据左对齐方式存放(有效数据在高位)
     */
    U32  u32BitPerSample;       /**<Data depth*/ /**<CNcomment: 数据位宽*/
    U32  u32Interleaved;        /**<Whether the data is interleaved*/ /**<CNcomment: 数据是否交织*/
    U32  u32SampleRate;         /**<Sampling rate*/ /**<CNcomment: 采样率*/
    U32  u32Channels;           /**<Number of channels*/ /**<CNcomment: 通道数量*/
    U32  u32PtsMs;              /**<Presentation time stamp (PTS)*/ /**<CNcomment: 时间戳*/
    S32 *ps32PcmBuffer;         /**<Pointer to the buffer for storing the pulse code modulation (PCM) data*/ /**<CNcomment: PCM数据缓冲指针*/
    S32 *ps32BitsBuffer;        /**<Pointer to the buffer for storing the stream data*/ /**<CNcomment: 码流数据缓冲指针*/
    U32  u32PcmSamplesPerFrame; /**<Number of sampling points of the PCM data*/ /**<CNcomment: PCM数据采样点数量*/
    U32  u32BitsBytesPerFrame;  /**<IEC61937 data size*/ /**<CNcomment: IEC61937数据长度*/
    U32  u32FrameIndex;         /**<Frame ID*/ /**<CNcomment: 帧序号 */
    U32  u32IEC61937DataType;   /**<IEC61937 Data Type*/ /**<CNcomment: IEC61937数据类型标识，低8bit为IEC数据类型 */
} AOUT_TRACK_PASSTHROUGHDATA;

/**Struct of audio track mix param
1. s16IntGain, the device must support AOUT_VOL_DB_ZERO and above.
2. s16DecGain,  if the device do not support gain fine tunning, ignore it.
*/
/**CNcomment:Aout track 混音参数
1. s16IntGain,   设备至少需要支持AOUT_VOL_DB_ZERO 或以上增益.
2. s16DecGain,  设备不支持小数增益微调，可忽略该参数.
*/
typedef struct _AOUT_TRACK_MIX_PARAMS_S
{
    S32 s32IntGain;    /**<Integer part of volume*//**<CNcomment: 混音音量值的整数部分，范围[AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX],  步长(1.0 dB ) */
    S32 s32DecGain;    /**<Fractional part of volume*//**<CNcomment: 混音音量值的小数部分，范围(0~7),    步长(0.125 dB  */
    U32 u32Dummy;      /**<Reserved*//**<CNcomment: 以后扩展用 */
} AOUT_TRACK_MIX_PARAMS_S;

/**Struct of init param of audio output*/
/**CNcomment:音频输出模块初始化参数*/
typedef struct _AOUT_INIT_PARAMS_S
{
    U32 u32Dummy;                         /**<Reserved*//**<CNcomment: 以后扩展用 */
} AOUT_INIT_PARAMS_S;

/**Struct of settings param of audio output*/
/**CNcomment:音频输出 配置参数*/
typedef struct _AOUT_SETTINGS_S
{
    AOUT_DEVICE_TYPE_E enOutputDevice;
    U32                u32Dummy;          /**<Reserved*//**<CNcomment: 以后扩展用 */
} AOUT_SETTINGS_S;

/**Struct of audio output capability*/
/**CNcomment:音频输出 模块的能力*/
typedef struct _AOUT_CAPABILITY_S
{
    U8                 u8SupportedIdNum;
    AOUT_DEVICE_TYPE_E enOutputDevice[AOUT_ID_NUM];        /**<Audio output device*//**<CNcomment:音频输出设备 */
    U8                 u8SupportedTrackNum[AOUT_ID_NUM];    /**<Max track number supported*//**<CNcomment:   track  最大通道数 */
} AOUT_CAPABILITY_S;

/**Struct of terminate param*/
/**CNcomment:模块终止参数*/
typedef struct _AOUT_TERM_PARAMS_S
{
    U32 u32Dummy;               /**<Reserved*//**<CNcomment: 以后扩展用 */
} AOUT_TERM_PARAMS_S;

/**Struct of open param of Aout instance*/
/**CNcomment:音频输出 实例打开参数*/
typedef struct _AOUT_OPEN_PARAMS_S
{
    AOUT_ID_E       enId;       /**<Audio output ID*//**<CNcomment:音频输出 ID */
    AOUT_SETTINGS_S stSettings; /**<Audio output settings*//**<CNcomment:音频输出 设置*/
} AOUT_OPEN_PARAMS_S;

/**Struct of close param of Aout instance*/
/**CNcomment:音频输出 实例关闭参数*/
typedef struct _AOUT_CLOSE_PARAMS_S
{
    U32 u32Dummy;               /**<Reserved*//**<CNcomment: 以后扩展用 */
} AOUT_CLOSE_PARAMS_S;

#ifdef HAL_HISI_EXTEND_H

/**Defines the type of AOUT invoke.*/
/**CNcomment: 定义AOUT Invoke调用类型的枚举 */
typedef enum _AOUT_INVOKE_E
{
    AOUT_INVOKE_REG_CALLBACK = 0x0,             /**<Invoke command to register aout callback*//**<CNcomment: 注册aout对外部依赖的回调接口 */
    AOUT_INVOKE_GET_DOLBY_ATMOS_FLAG,           /**<Invoke command to get dolby atmos output flag, param type is BOOL*//**<CNcomment: 获取aout是否是DOLBY ATMOS输出,参数类型是BOOL */
    AOUT_INVOKE_BUTT
} AOUT_INVOKE_E;

#endif

#ifdef ANDROID_HAL_MODULE_USED
/**Audio output module structure(Android require)*/
/**CNcomment:音频输出模块结构(Android对接要求) */
typedef struct _AOUT_MODULE_S
{
    struct hw_module_t stCommon;
} AOUT_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_AOUT*/
/** @{*/  /** <!-- -HAL_AOUT=*/

/**Audio out device structure*//** CNcomment:音频输出设备结构*/
typedef struct _AOUT_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
     \brief Audio output init.CNcomment:音频输出初始化 CNend
     \attention \n
    Other functions cannot be useful before init, return SUCCESS when repeated called.
    CNcomment: 在初始化之前, 其他函数都不能正确运行, 重复调用init 接口,返回SUCCESS. CNend
     \param[in] pstInitParams Vout module init param.CNcomment:初始化模块参数 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_INIT_FAILED  other error.CNcomment:其它错误 CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_INIT_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_init)(struct _AOUT_DEVICE_S* pstDev, const AOUT_INIT_PARAMS_S* pstInitParams);

    /**
     \brief Terminate video output module. CNcomment:模块终止 CNend
     \attention \n
    Return SUCCESS when repeated called.
    CNcomment: 重复term 返回SUCCESS. CNend
     \param[in] pstTermParams Terminate param,  if NULL, force to terminate.CNcomment:终止模块参数，为NULL  表示强制终止 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_TERM_FAILED  other error.CNcomment:其它错误 CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \see \n
    ::AOUT_TERM_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_term)(struct _AOUT_DEVICE_S* pstDev, const AOUT_TERM_PARAMS_S* pstTermParams);

    /**
     \brief Get the capability of audio ouput module. CNcomment:获取模块设备能力 CNend
     \attention \n
    CNcomment: 无CNend
     \param[out] pstCapability Capability param.CNcomment:模块能力参数 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_CAPABILITY_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_capability)(struct _AOUT_DEVICE_S* pstDev, AOUT_CAPABILITY_S* pstCapability);

    /**
     \brief Open a audio output instance.CNcomment:打开一个音频输出实例 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] pstOpenParams Open param.CNcomment:实例打开参数 CNend
     \param[out] phAout Return AOUT handle .CNcomment:返回AOUT句柄 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
     \retval ::ERROR_AO_OPEN_FAILED  Other error.CNcomment:其它错误 CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::VOUT_OPEN_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_open)(struct _AOUT_DEVICE_S* pstDev, HANDLE* phAout, const AOUT_OPEN_PARAMS_S* pstOpenParams);

    /**
     \brief Close a audio output instance.CNcomment:关闭一个音频输出实例 CNend
     \attention \n
    If hAout is the last instance of the device, relese hardware resource at the same time
    CNcomment: 如果aout_close()函数close 的是AOUT_ID_E 上的最后一个hAout, 释放硬件资源.CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[in] pstCloseParams Close param.CNcomment:实例关闭参数 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_AO_CLOSE_FAILED  other error.CNcomment:其它错误 CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_CLOSE_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*aout_close)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout, const AOUT_CLOSE_PARAMS_S* pstCloseParams);

    /**
     \brief Set the volume of audio output device.CNcomment:设置输出设备音量 CNend
     \attention \n
    1. s32IntGain, the device must support AOUT_VOL_DB_ZERO and above.
    2. s32DecGain,  if the device do not support gain fine tunning, ignore it.
    CNcomment:
    1. s16IntGain, 设备至少需要支持AOUT_VOL_DB_ZERO 或以上增益.
    2. s16DecGain,  设备不支持小数增益微调，可忽略该参数.
    CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备类型CNend
     \param[in] s32IntGain Integer part of volume, the range is [AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX], step is (1.0 dB ) .CNcomment:音量值的整数部分，范围[AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX],  步长(1.0 dB )  CNend
     \param[in] s32DecGain Fractional part of volume, the range is (0~7), step is(0.125 dB ).CNcomment:音量值的小数部分，范围(0~7),  步长(0.125 dB ) CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_volume)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout, AOUT_DEVICE_TYPE_E enOutputDevice,
                           S32 s32IntGain, S32 s32DecGain);

    /**
     \brief Get the volume of audio output device.CNcomment:获取输出设备音量 CNend
     \attention \n
    1. ps32IntGain, the device must support AOUT_VOL_DB_ZERO and above.
    2. ps32DecGain,  if the device do not support gain fine tunning, ignore it.
    CNcomment:
    1. ps32IntGain, 设备至少需要支持AOUT_VOL_DB_ZERO 或以上增益.
    2. ps32DecGain,  设备不支持小数增益微调，可忽略该参数.
    CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备 CNend
     \param[out] ps32IntGain Return integer part of volume, the range is [AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX] .CNcomment:音量值的整数部分，范围[AOUT_VOL_DB_MIN , AOUT_VOL_DB_MAX] CNend
     \param[out] ps32DecGain Return fractianl part of volume, the range is (0~7).CNcomment:音量值的小数部分，范围(0~7) CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_volume)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout, AOUT_DEVICE_TYPE_E enOutputDevice,
                           S32* ps32IntGain, S32* ps32DecGain);

    /**
     \brief Set digital output mode.CNcomment:设置数字输出模式 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备 CNend
     \param[in] enMode Output mode .CNcomment:输出模式CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_DIGITAL_OUTPUT_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_digital_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                                 AOUT_DEVICE_TYPE_E enOutputDevice, AOUT_DIGITAL_OUTPUT_MODE_E enMode);

    /**
     \brief Get digital output mode.CNcomment:获取数字输出模式 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备 CNend
     \param[out] penMode Return output mode .CNcomment:返回输出模式CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_DIGITAL_OUTPUT_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_digital_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                                 AOUT_DEVICE_TYPE_E enOutputDevice, AOUT_DIGITAL_OUTPUT_MODE_E* penMode);

    /**
     \brief Set output device mute.CNcomment:设置输出静音 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备 CNend
     \param[in] bMute TRUE:mute, FALSE:mute .CNcomment:TRUE: 设置静音, FALSE: 撤销静音CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_mute)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                         AOUT_DEVICE_TYPE_E enOutputDevice, BOOL bMute);

    /**
     \brief Get mute status of output device .CNcomment:获取静音状态 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备 CNend
     \param[out] bMute TRUE:mute, FALSE:mute .CNcomment:TRUE: 设置静音, FALSE: 撤销静音CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_mute)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                         AOUT_DEVICE_TYPE_E enOutputDevice, BOOL* pbMute);

    /**
     \brief Set track mode of output device .CNcomment:设置声道模式 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备 CNend
     \param[in] enMode Track mode .CNcomment:声道模式CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_channel_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                                 AOUT_DEVICE_TYPE_E enOutputDevice, AOUT_CHANNEL_MODE_E enMode);

    /**
     \brief Get track mode of output device .CNcomment:获取声道模式 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备 CNend
     \param[out] penMute Return track mode .CNcomment:返回声道模式CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
     \brief Set aout config.CNcomment:设置aout的相关配置
     \attention \n
    CNcomment:无CNend
     \param[in] hAout aout handle.CNcomment:aout 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备 CNend
     \param[in] u32Index config index.CNcomment:Config indexCNend
     \param[in] pConfig point to config.CNcomment:指向config的指针 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*aout_set_config)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                          AOUT_DEVICE_TYPE_E enOutputDevice, U32 u32Index, const VOID* pConfig);

    /**
     \brief Get aout config.CNcomment:获取aout的相关配置
     \attention \n
    CNcomment:无CNend
     \param[in] hAout aout handle.CNcomment:aout 句柄 CNend
     \param[in] enOutputDevice Output device.CNcomment:输出设备 CNend
     \param[in] u32Index config index.CNcomment:Config indexCNend
     \param[out] pConfig point to config.CNcomment:指向config的指针 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*aout_get_config)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout,
                          AOUT_DEVICE_TYPE_E enOutputDevice, U32 u32Index, VOID* pConfig);


    /**
    \brief aout invoke function, extend other function by user.
    CNcomment:invoke 扩展接口，用于用户私有功能扩展
    \attention \n
    None
    \param[in] hInvokeHandle the handle of Invoke Command, aout handle or track handle.CNcomment:Invloke命令需要的句柄，aout句柄或track句柄 CNend
    \param[in] eCmd Invoke ID, defined is ::AOUT_INVOKE_E.CNcomment:Invoke ID, 定义详见 ::AOUT_INVOKE_E CNend
    \param[in,out] pArg Command parameter.CNcomment:命令参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE other error.CNcomment:其它错误 CNend
    \see \n
    ::AOUT_INVOKE_E

    \par example
    \code
    \endcode
    */
    S32 (*aout_invoke)(struct _AOUT_DEVICE_S* pstDev, const HANDLE hInvokeHandle, AOUT_INVOKE_E eCmd, VOID* pArg);

#endif
    /**
     \brief get default track attr .CNcomment:获取默认的track参数
     \attention \n
    CNcomment:无CNend
     \param[out] pstParams track param.CNcomment:属性指针 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_default_attr)(struct _AOUT_DEVICE_S* pstDev, AOUT_TRACK_PARAMS_S* pstParams);

    /**
     \brief Create a track instance, disabled dafautly after created .CNcomment:创建一个track  通道实例 ,  create后处于disable状态 CNend
     \attention \n
    1. Multi tracks output to the same device(RCA/SPDIF/HDMI, etc.) after mixed.
    2. When bind source and track , track param(AOUT_TRACK_PARAMS_S) can be set dynamicly.
    3. When playback, not attach,  track param must be set correctly, you must stop track before renew track param.
    CNcomment:
    1.  多个track 的音频混音后输出到同一个aout 的enOutputDevice(RCA/SPDIF/HDMI等)
    2. source 和track 绑定场景(attach)，source 可以动态设置track 的AOUT_TRACK_PARAMS_S
    3. playback 场景(非attach)，必须正确设置track 的AOUT_TRACK_PARAMS_S,  如果需要修改参数，必须先stop track
    CNend
     \param[in] hAout AOUT handle.CNcomment:AOUT 句柄 CNend
     \param[out] phTrack Return track handle.CNcomment:返回track 句柄 CNend
     \param[in] pstParams Track param .CNcomment:创建track  的参数CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_TRACK_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_create)(struct _AOUT_DEVICE_S* pstDev, HANDLE hAout, HANDLE* phTrack,
                        const AOUT_TRACK_PARAMS_S* pstParams);

    /**
     \brief Destroy a track instance .CNcomment:销毁一个track  通道实例CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_destroy)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Attach source and track .CNcomment:绑定source 句柄到音频track 通道 .CNend
     \attention \n
    Track will be started after attached.
    CNcomment:绑定后，track 处于start 状态.CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[in] hSource Source handle,  source module handle or av module handle.
     CNcomment:被绑定的source 句柄，该句柄是source模块或av模块句柄 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_attach_input)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, HANDLE hSource);

    /**
     \brief Detach source and track .CNcomment:从track，解 绑定source 句柄 .CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[in] hSource Source handle.CNcomment:被绑定的source 句柄 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_detach_input)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, HANDLE hSource);

    /**
     \brief Start track, the device of Aout will outoput the audio data .CNcomment:启动 track 通道，track 音频数据可以从aout 输出 .CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_start)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Stop track, the audio data in the buffer will be cleared.CNcomment:停止track 通道，通道buffer 的音频数据被清空 .CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_stop)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Notifies to the aout  to stop track however the queued buffers are retained by the track. Useful for implementing pause/resume.
     CNcomment: 暂停 track 通道，track 音频数据停止从aout 输出 .CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_pause)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Notifies to the aout to resume the track playback following a pause.
     \ Returns error if called without matching pause.CNcomment: 恢复track 通道，通道buffer 的音频数据继续输出 .CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_resume)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Notifies to the aout driver to flush the queued data. track must already be paused before calling flush() .
     CNcomment: 恢复track 通道，通道buffer 的音频数据继续输出 .CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_flush)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack);

    /**
     \brief Set param fo track.CNcomment:设置track 属性.CNend
     \attention \n
    Stop track before set param fo track
    CNcomment:通道stop 后，才能设置track 属性CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[in] pstParams Track param.CNcomment:Track 参数 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_TRACK_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_set_params)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                            const AOUT_TRACK_PARAMS_S* pstParams);

    /**
     \brief Get param fo track.CNcomment:获取track 属性.CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[out] pstParams Return param of track.CNcomment:返回track 属性 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_TRACK_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_get_params)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                            AOUT_TRACK_PARAMS_S* pstParams);

    /**
     \brief Set mix param of track.CNcomment:设置track 混音参数.CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[in] pstParams Mix param.CNcomment:混音参数 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_TRACK_MIX_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_set_mix_params)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                                const AOUT_TRACK_MIX_PARAMS_S* pstParams);

    /**
     \brief Get mix param of track.CNcomment:获取track 混音参数.CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[out] pstParams Return mix param.CNcomment:返回混音参数 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_TRACK_MIX_PARAMS_S

     \par example
     \code
     \endcode
     */
    S32 (*track_get_mix_params)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                                AOUT_TRACK_MIX_PARAMS_S* pstParams);

    /**
     \brief Set track mute.CNcomment:设置TRACK静音 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hTrack ATRACK handle.CNcomment:HTRACK 句柄 CNend
     \param[in] bMute TRUE:mute, FALSE:mute .CNcomment:TRUE: 设置静音, FALSE: 撤销静音CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*track_set_mute)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, BOOL bMute);
    /**
     \brief Get mute status of track .CNcomment:获取TRACK 静音状态 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hTrack ATRACK handle.CNcomment:HTRACK 句柄 CNend
     \param[out] *bMute TRUE:mute, FALSE:mute .CNcomment:获取静音CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E

     \par example
     \code
     \endcode
     */
    S32 (*track_get_mute)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, BOOL *pbMute);
    /**
     \brief Set channel mode of track .CNcomment:设置声道模式 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hTrack handle.CNcomment:TRACK 句柄 CNend
     \param[in] enMode Track mode .CNcomment:声道模式CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*track_set_channel_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, TRACK_CHANNEL_MODE_E enMode);

   /**
     \brief Get channel mode of track .CNcomment:获取声道模式 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hTrack handle.CNcomment:HTRACK 句柄 CNend
     \param[out] penMute Return track mode .CNcomment:返回声道模式CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

     \par example
     \code
     \endcode
     */
    S32 (*track_get_channel_mode)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, TRACK_CHANNEL_MODE_E *penMode);

   /**
     \brief set track weight .CNcomment:设置声道权重 CNend
     \attention \n
    CNcomment: 无CNend
     \param[in] hTrack handle.CNcomment:HTRACK 句柄 CNend
     \param[in] stTrackGainAttr .CNcomment:声道权重CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_AO_NOT_OPENED  Module has not been inited.CNcomment:实例未打开。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::AOUT_DEVICE_TYPE_E, AOUT_CHANNEL_MODE_E

      \par example
      \code
      \endcode
      */
    S32 (*track_set_weight)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack,
                                const TRACK_GAIN_ATTR_S stTrackGainAttr);
    /**
      \brief get track weight.CNcomment:获取声道权重 CNend
      \attention \n
     CNcomment: 无CNend
      \param[in] hTrack handle.CNcomment:HTRACK 句柄 CNend
      \param[out] pstMixWeightGain .CNcomment:声道权重CNend
      \retval ::SUCCESS CNcomment:成功 CNend
      \retval ::HI_ERR_AO_SOUND_NOT_OPEN  Module has not been inited.CNcomment:实例未打开。CNend
      \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
      \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
      \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
     * the output has exited standby. CNcomment:获取输出到硬件的音频帧数，单位: .CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[out] pu32Frames Return frame of track wirtten to HW.CNcomment:返回已经输出到硬件的音频帧数 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_render_position)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32* pu32Frames);
    /**
     \brief Get pts of data in the track buf, unit: ms.CNcomment:获取track 当前播放的pts，单位: ms
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[out] pS64Pts Return pts.CNcomment:返回pts 大小 CNend
     \retval ::HI_SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_NOT_SUPPORTED  Track is not support to require pts.CNcomment:Track 不支持获取pts。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_pts)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, S64* ps64Pts);
    /**
     \brief adjust track data consume speed, unit: ms.CNcomment:对track的播放进行调速
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[in] s32Speed consume speed(-100~100), ms.CNcomment:调速速度(-100~100)，毫秒
     \retval ::HI_SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_NOT_SUPPORTED  Track is not support to require pts.CNcomment:Track 不支持获取pts。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_adjust_speed)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, S32 s32Speed);
    /**
     \brief Get free szie of track buf, Unit: Byte.CNcomment:获取track buf 剩余空间，单位: Byte.CNend
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[out] pu32Bytes Return free size of track buf.CNcomment:返回剩余字节数 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_buf_avail)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32* pu32Bytes);

    /**
     \brief Get play time of data in the track buf, unit: ms.CNcomment:获取track buf 可播放数据的时长，单位: ms
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[out] pu32Latency Return play time.CNcomment:返回播放时间 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_latency)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32* pu32Latency);

    /**
     \brief Write audio data to track buffer.CNcomment:向track buf  写入待播放的音频数
     \attention \n
    This function is blocking operation, you should confirm enough size by track_get_buf_avail
    CNcomment:本函数为阻塞操作，写入前必须通过track_get_buf_avail 确认是否有足够空间，否则将会立刻返回失败CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[in] pvbuffer Data address.CNcomment:源数据地址CNend
     \param[in] u32Bytes Data length.CNcomment:源数据字节数 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_write)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, const void* pvBuffer, U32 u32Bytes);

    /**
     \brief Write audio data to track buffer(include transmission data or PCM data).CNcomment:向track buf  写入待播放的音频数据(包括透传或PCM数据)
     \attention \n
    This function is blocking operation, you should confirm enough size by track_get_buf_avail
    CNcomment:本函数为阻塞操作，写入前必须通过track_get_buf_avail 确认是否有足够空间，否则将会立刻返回失败CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[in] pstData Data struct.CNcomment:源数结构体地址CNend
     \retval ::SUCCESS CNcomment:成功 CNend

     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_write_passthrough)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, AOUT_TRACK_PASSTHROUGHDATA* pstData);

    /**
     \brief Set track config, CNcomment:设置Track config
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[in] u32Index config index.CNcomment:Config indexCNend
     \param[in] pConfig point to config.CNcomment:指向config的指针 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_set_config)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32 u32Index, VOID* pConfig);

    /**
     \brief Get track config.CNcomment:获取Track的相关配置
     \attention \n
    CNcomment:无CNend
     \param[in] hTrack Track handle.CNcomment:Track 句柄 CNend
     \param[in] u32Index config index.CNcomment:Config indexCNend
     \param[out] pConfig point to config.CNcomment:指向config的指针 CNend
     \retval ::SUCCESS CNcomment:成功 CNend
     \retval ::ERROR_VO_TRACK_NOT_CREATED  Track has not been created.CNcomment:Track 实例未创建。CNend
     \retval ::ERROR_AO_OP_FAILED Operation fail.CNcomment:操作失败。CNend
     \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
     \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n

     \par example
     \code
     \endcode
     */
    S32 (*track_get_config)(struct _AOUT_DEVICE_S* pstDev, HANDLE hTrack, U32 u32Index, VOID* pConfig);
} AOUT_DEVICE_S;

/**
 \brief direct get aout device api, for linux and android.CNcomment:获取音频设备的接口, Linux和Android平台都可以使用 CNend
 \attention \n
get aout device api，for linux and andorid.
CNcomment:获取音频设备接口，linux和android平台都可以使用. CNend
 \retval  aout device pointer when success.CNcomment:成功返回aout设备指针。CNend
 \retval ::NULL when failure.CNcomment:失败返回空指针 CNend
 \see \n
::AOUT_DEVICE_S

 \par example
 */
AOUT_DEVICE_S* getAOutDevice();

/**
\brief Open HAL Audio output module device.CNcomment:打开HAL音频输出模块设备 CNend
\attention \n
Open HAL Audio output module device(for compatible android HAL).
CNcomment:打开HAL音频输出模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice Audio output device structure.CNcomment:音频输出设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
\brief Close HAL Audio output module device.CNcomment:关闭HAL音频输出模块设备 CNend
\attention \n
Close HAL Audio output module device(for compatible Android HAL).
CNcomment:关闭HAL音频输出模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice Audio output device structure.CNcomment:音频输出设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
