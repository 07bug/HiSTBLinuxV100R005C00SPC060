/**
 * \file tvos_hal_pvr.h
 * \brief tvos hal pvr hal api.
*/

#ifndef  TVOS_HAL_PVR_H
#define TVOS_HAL_PVR_H


#include "tvos_hal_type.h"
#include "tvos_hal_av.h"
#include "tvos_hal_dmx.h"
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
#endif /* __cplusplus */

/*************************************************************************/
#define PVR_ST_DMX_ID_PLAY              1
#define PVR_ST_DMX_ID_REC               0
#define PVR_RECORD_PORT_ID              (0x20)
#define PVR_PLAYBACK_PORT_ID            (0x80)
#define DMX_PLAYBACK_TSBUFFER_SIZE      (4 * 1024 * 1024)
#define TUNER_FREQ                      618
#define TUNER_SYMBOLRATE                6875
#define TUNER_THIRD_PARAM               64
#define FIRST_TUNER   0
#define SECOND_TUNER  1
#define THIRD_TUNER   2
#define FOURTH_TUNER  3

typedef U32 HI_HANDLE;
/*************************************************************************/

/*************************** Macro Definition ****************************/
/** \addtogroup     HAL_PVR */
/** @{ */  /** <!-- [HAL_PVR] */

#define PVR_HARDWARE_MODULE_ID      "pvr"
#define PVR_HARDWARE_PVR0           "pvr0"
#define PVR_HEADER_VERSION          (1)
#define PVR_DEVICE_API_VERSION_1_0  HARDWARE_DEVICE_API_VERSION_2(1, 0, PVR_HEADER_VERSION)

/**Maximum length of the encryption key, in byte. Note: The valid key length may not be the maximum length, and depends on the encryption algorithm.*/
/** CNcomment: 加密密钥最大长度，单位:字节。注意: 密钥的有效长度不一定是最大长度，而是由加密的算法决定 */
#define PVR_HAL_MAX_CIPHER_KEY_LEN  (128)

/**file name max length.*//** CNcomment:文件名最大长度 */
#define PVR_FILE_NAME_LENGTH        (255)

#define PVR_MAX_FILENAME_LEN        (256)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_PVR */
/** @{ */  /** <!-- [HAL_PVR] */

/**Struct of PVR init parameters*/
/**CNcomment:PVR模块初始化参数 */
typedef struct  _PVR_RECINIT_PARAMS_S
{
    U8 u8Dummy; /**<Reserved.*//**< CNcomment: 保留参数.*/
} PVR_RECINIT_PARAMS_S;

/**Struct of PVR terminate parameters*/
/**CNcomment:PVR模块终止参数   */
typedef  struct _PVR_TERM_PARAMS_S
{
    U8 u8Dummy; /**<Reserved.*//**< CNcomment: 保留参数.*/
} PVR_TERM_PARAMS_S;

/**Type of recorded and played streams of the PVR*//** CNcomment: PVR录制、播放支持的码流类型 */
typedef enum  _PVR_STREAM_TYPE_E
{
    PVR_STREAM_TS = 1 << 0,         /**<Transport stream (TS)*/ /**<CNcomment:  TS流 */
    PVR_STREAM_PES = 1 << 1,        /**<Packetized elementary stream (PES)*/ /**<CNcomment: PES流 */
    PVR_STREAM_ALL_TS = 1 << 2,     /**<All types of streams. That is, the streams at all frequencies are recorded.*/ /**<CNcomment: 全码流录制，录制整个频点的所有码流 */
    PVR_STREAM_OTHER = 1 << 3,      /**<Invalid*/ /**<CNcomment:  无效的类型 */
    PVR_STREAM_BUTT
} PVR_STREAM_TYPE_E;

/** PVR capability */
/** CNcomment: PVR能力*/
typedef struct  _PVR_CAPABILITY_S
{
    U32                 u32SupportRecNumber;    /**<Support max record channel number.*//**< CNcomment: 可支持的最大录制通道数.*/
    U32                 u32SupportPlayNumber;   /**<Support max play channel number.*//**< CNcomment: 可支持的最大播放通道数.*/
    BOOL                bSupportTimeShift;      /**<Whether support timeshift.*//**< CNcomment: 是否支持时移功能.*/
    PVR_STREAM_TYPE_E   enStreamType;           /**<Support recorded and played stream type, support OR operate.*//**< CNcomment: PVR录制、播放支持的码流类型，支持或操作.*/
} PVR_CAPABILITY_S;

/**Index type*//** CNcomment: 索引类型 */
typedef enum _PVR_REC_INDEX_TYPE_E
{
    PVR_REC_INDEX_TYPE_NONE,      /**<No index is created. You need to select this type when recording all streams.*//**<CNcomment: <不建索引。全码流录制的时候请使用此类型  */
    PVR_REC_INDEX_TYPE_VIDEO,     /**<The index is created based on videos.*//**<CNcomment: <针对视频建立索引。 */
    PVR_REC_INDEX_TYPE_AUDIO,     /**<The index is created based on audios. *//**<CNcomment: <针对音频建立索引。 */
    PVR_REC_INDEX_TYPE_BUTT       /**<Invalid*//**<CNcomment: <无效的索引类型。   */
} PVR_REC_INDEX_TYPE_E;

/** Cipher algorithm */
/** CNcomment:CIPHER加密算法 */
typedef enum _PVR_CIPHER_ALG_E
{
    CIPHER_ALG_DES           = 0x0,  /**< Data encryption standard (DES) algorithm */     /**< CNcomment: DES算法 */
    CIPHER_ALG_3DES          = 0x1,  /**< 3DES algorithm */                               /**< CNcomment: 3DES算法 */
    CIPHER_ALG_AES           = 0x2,  /**< Advanced encryption standard (AES) algorithm */ /**< CNcomment: AES算法 */
    CIPHER_ALG_BUTT          = 0x3
} PVR_CIPHER_ALG_E;

/**Encryption or decryption configuration of the PVR*//** CNcomment:  PVR加解密配置 */
typedef struct _PVR_CIPHER_S
{
    BOOL                       bDoCipher;                                                 /**<Whether to perform encryption or decryption. When this parameter is set to HI_FALSE, other parameters are invalid.*//**<CNcomment:  是否进行加密或者解密，此项配置为HI_FALSE时，其他项没有意义 */
    PVR_CIPHER_ALG_E  enType;                                                      /**<Algorithm for encryption or decryption*//**<CNcomment: 加密或者解码的算法类型 */
    U8                            au8Key[PVR_HAL_MAX_CIPHER_KEY_LEN];    /**<In normal PVR,it's cipher key.If advance security PVR, it's Keyladder's first session key*//**<CNcomment: 普通PVR方案中，作为Cipher的密钥，高安全PVR方案中，作为Keyladder的一级会话密钥 */
    U32                          u32KeyLen;                                                 /**<Cipher key length*//**<CNcomment: 密钥长度 */
} PVR_CIPHER_S;

/**Attributes of a recording channel*//** CNcomment: 录制通道属性数据结构 */
typedef struct _PVR_REC_OPENPARAMS_S
{
    PVR_REC_INDEX_TYPE_E    enIndexType;                        /**<Index type, static attribute.*//**<CNcomment:  索引类型，静态属性。 */
    AV_VID_STREAM_TYPE_E    enVidType;                          /**<Video encoding protocol with which the stream (for which an index is to be created) complies. The protocol (static attribute) needs to be set only when the index type is PVR_REC_INDEX_TYPE_VIDEO.*/
    U32                     u32IndexPid;                        /**<Index PID, static attribute.*//**<CNcomment:  索引PID，静态属性*/
    U32                     u32DavBufSize;                      /**<Size (in byte) of a data stream buffer, static attribute.*//**<CNcomment:  数据流缓冲区大小，单位为Byte，静态属性。  */
    U32                     u32ScdBufSize;                      /**<Size (in byte) of an index data buffer, static attribute.*//**<CNcomment:  索引数据缓存区大小，单位为Byte，静态属性。*/
    U32                     u32UsrDataInfoSize;                 /**<Size (in byte) of the private user data, static attribute.*//**<CNcomment:  用户私有数据大小，单位为Byte，静态属性。  */
    PVR_STREAM_TYPE_E       enStreamType;                       /**<Type of the data to be recorded, static attribute.*//**<CNcomment: 待录制的数据类型，静态属性。*/
    PVR_CIPHER_S            stEncryptCfg;                       /**<Stream encryption configuration, static attribute.*//**<CNcomment: 码流加密配置信息，静态属性。*/
    U64                     u64MaxFileSize;                     /**<Size of the file to be recorded, static attribute. If the value is 0, it indicates that there is no limit on the file size. The minimum file size is 5242880 bytes (5 MB). If the disk space is sufficient, it is recommended to set the file size to a value greater than 512 MB. The file size cannot be 0 in rewind mode. */
    /**<CNcomment: 待录制的文件大小，为0时表示无限制，静态属性。最小值为50M,如果磁盘空间足够的话，推荐配置为512M以上。配置为回绕时不允许把文件大小和文件播放时间都配置为0。 */
    U64                     u64MaxTimeInMs;                     /**<Max play time of the file to be recorded, static attribute. If the value is 0, it indicates that there is no limit on the file play time. The minimum file time is 60*1024 MS (1 Min).  The file size  and file time cannot both be 0 in rewind mode.*/
    /**<CNcomment: 待录制的文件的最长播放时间长度，为0时表示无限制，静态属性。最小播放时间为60*1024毫秒(1分钟)。回绕模式下，不能将文件最大大小和文件最长播放时间同时设置为0。*/
    BOOL                    bRewind;                            /**<Whether to rewind, static attribute. If this item is set to HI_TRUE, the PVR rewinds to the file header to record streams after the recorded file size reaches u64MaxFileSize. If this item is set to HI_FALSE, the PVR stops recording after the recorded file size reaches u64MaxFileSize.*/
    /**<CNcomment: 是否回绕，静态属性。如配置为HI_TRUE，录制文件大小到达u64MaxFileSize后，会回绕到文件头继续进行录制；如配置为HI_FALSE，则录制文件大小到达u64MaxFileSize后，会停止录制。*/
    CHAR                    szFileName[PVR_FILE_NAME_LENGTH];   /**<Name of a stream file, static attribute*//**<CNcomment: 码流文件名，静态属性。*/
    U32                     u32FileNameLen;                     /**<Length of a stream file name, static attribute. You need to set the item to strlen (szFileName).*//**<CNcomment: 码流文件名长度，静态属性。取值为strlen（szFileName）即可 */
    U32                     u32Reserved;
} PVR_REC_OPENPARAMS_S;

/**Struct of record close parameters*/
/**CNcomment:录制通道关闭参数   */
typedef  struct _PVR_REC_CLOSECHNPARAMS_S
{
    U8      u8Dummy; /*!<  以后扩展用 */
} PVR_REC_CLOSECHNPARAMS_S;


/**Status of a recording channel, INVALID -> INIT -> RUNNING -> STOPPING ->    STOP ->    INVALID  (saveIndex)  (saveStream)*/
/**CNcomment: 录制通道的状态 */
typedef enum _PVR_REC_STATE_E
{
    PVR_REC_STATE_INVALID = 0,    /**<Not initialized*//**<CNcomment:  未初始化。    */
    PVR_REC_STATE_INIT,           /**<Initialized*//**<CNcomment:  初始化。      */
    PVR_REC_STATE_RUNNING,        /**<Recording*//**<CNcomment:  录制中。      */
    PVR_REC_STATE_PAUSE,          /**<Pause*//**<CNcomment:  暂停中        */
    PVR_REC_STATE_STOPPING,       /**<Stopping*//**<CNcomment: 正在停止。    */
    PVR_REC_STATE_STOP,           /**<<Stopped*//**<CNcomment: 已经停止。    */
    PVR_REC_STATE_BUTT            /**<Invalid*//**<CNcomment: 无效的状态值。*/
} PVR_REC_STATE_E;

/**Status of a recording channel.
The following describes the relationships among u32CurTimeInMs, u32StartTimeInMs, and u32EndTimeInMs by taking examples:
1. Assume that the total recording time is 10000 ms, and no rewind occurs. In this case, u32StartTimeInMs is 0 ms, u32EndTimeInMs is 10000 ms, and u32CurTimeInMs is 10000 ms.
2. Assume that the total recording time is 10000 ms, and rewind occurs at 8000 ms. In this case, u32StartTimeInMs is 2000 ms, u32EndTimeInMs is 10000 ms, and u32CurTimeInMs is 8000 ms.
*/
/** CNcomment:录制通道状态数据结构.
对u32CurTimeInMs、u32StartTimeInMs、u32EndTimeInMs三者的关系举例说明如下：
1·假设从开始录制后一共录制了10000毫秒，如果没有发生回绕，那么u32StartTimeInMs 为0，u32EndTimeInMs 为10000， u32CurTimeInMs为10000。
2·假设从开始录制后一共录制了10000毫秒，并且在第8000毫秒的时候发生了回绕，那么u32StartTimeInMs 为2000，u32EndTimeInMs 为10000， u32CurTimeInMs为8000。
*/
typedef struct _PVR_REC_STATUS_S
{
    PVR_REC_STATE_E          enState;                 /**<Current status of a channel*//**<CNcomment: 通道所处的状态。    */
    U32                      u32Reserved;             /**<Reserved, for alignment*//**<CNcomment: 保留，用作对齐。    */
    U64                      u64CurWritePos;          /**<Current recording position of file, in byte*//**<CNcomment: 当前录制写文件的位置（单位：byte）。 */
    U32                      u32CurWriteFrame;        /**<Number of currently recorded frames*//**<CNcomment: 当前录制的帧数。                  */
    U32                      u32CurTimeInMs;          /**<Current recording time (in ms). The value is the valid time for recording the file.*//**<CNcomment: 当前录制的毫秒数。其值为录制文件的实际有效时长。*/
    U32                      u32StartTimeInMs;        /**<Actual start time for recording files. Before the recording is rewound, the time is that of the first frame; after the recording is rewound, the time is the rewind time.*//**<CNcomment: 录制文件的实际起始点。录制回绕前，为第一帧时间；录制回绕后，为回绕点的时间。 */
    U32                      u32EndTimeInMs;          /**<Time of the end frame in the recorded file. Before the recording is rewound, the time is that of the last frame.*//**<CNcomment:录制文件中结束帧的时间，没有环回前即最后一帧的时间。    */
    //UNF_PVR_BUF_STATUS_S     stRecBufStatus;          /**<Status of the recording channel buffer*//**<CNcomment:录制通道缓冲区状态。    */
} PVR_REC_STATUS_S;

/**Attributes of a playing channel*//** CNcomment:播放通道属性 */
typedef struct _PVR_PLAY_OPENPARAMS_S
{
    PVR_STREAM_TYPE_E    enStreamType;                         /**<Type of the played stream, static attributes. At present, only the TS is supported.*//**<CNcomment: 播放码流类型，目前只支持TS，静态属性。*/
    PVR_CIPHER_S         stDecryptCfg;                         /**<Decryption configuration, static attribute                  *//**<CNcomment: 解密配置，静态属性。                  */
    CHAR                     szFileName[PVR_MAX_FILENAME_LEN];     /**<Name of the file that contains the streams to be played, static attribute        *//**<CNcomment: 待播放码流的文件名，静态属性。        */
} PVR_PLAY_OPENPARAMS_S;

/**Speed of PVR play*/
/**CNcomment: PVR播放倍速*/
typedef enum  _PVR_PLAY_SPEEDMULTIPLE_E
{
    PVR_PLAY_SPEED_1X = 0,
    PVR_PLAY_SPEED_2X,
    PVR_PLAY_SPEED_4X,
    PVR_PLAY_SPEED_8X,
    PVR_PLAY_SPEED_16X,
    PVR_PLAY_SPEED_32X,
    PVR_PLAY_SPEED_BUTT
} PVR_PLAY_SPEEDMULTIPLE_E ;

/**Trick direction of PVR play*/
/**CNcomment: PVR播放trick方向*/
typedef enum  _PVR_PLAY_TRICKDIRECTION_E
{
    PVR_PLAY_TRICK_BACK = 0,
    PVR_PLAY_TRICK_ONWARD
} PVR_PLAY_TRICKDIRECTION_E;

/**Trick mode of PVR play*/
/**CNcomment: PVR播放trick模式*/
typedef enum _PVR_PLAY_TRICK_MODE_E
{
    PVR_PLAY_TRICKMODE_NORMAL = 0,
    PVR_PLAY_TRICKMODE_SPEED,
    PVR_PLAY_TRICKMODE_STEPFRAME
} PVR_PLAY_TRICK_MODE_E;

/**Speed of PVR play*/
/**CNcomment: PVR倍速播放类型*/
typedef enum  _PVR_PLAY_SPEEDCHANGE_E
{
    PVR_PLAY_SPEED_SLOW = 0,    /*!< 慢播*/
    PVR_PLAY_SPEED_FAST         /*!< 快播*/
} PVR_PLAY_SPEEDCHANGE_E;

/**Trick parameters of PVR play*/
/**CNcomment: PVR播放trick参数*/
typedef struct _PVR_PLAY_TRICKPARAMS_S
{
    PVR_PLAY_TRICK_MODE_E  enMode;
    union
    {
        struct
        {
            PVR_PLAY_SPEEDMULTIPLE_E   enMultiple;
            PVR_PLAY_TRICKDIRECTION_E  enDirection;
            PVR_PLAY_SPEEDCHANGE_E     enChange;
        } stSpeed;
        PVR_PLAY_TRICKDIRECTION_E      enStep;
    } unData;
} PVR_PLAY_TRICKPARAMS_S;

/**Seek types of PVR play*/
/**CNcomment: PVR播放seek类型*/
typedef enum _PVR_PLAY_SEEKTYPE_E
{
    PVR_PLAY_SEEKTYPE_STAMPTIME,   /*!<  by time stamp */
    PVR_PLAY_SEEKTYPE_UNKOWN
} PVR_PLAY_SEEKTYPE_E;

/**Seek mode of PVR play*/
/**CNcomment: PVR播放seek模式*/
typedef enum _PVR_PLAY_SEEKMODE_E
{
    PVR_PLAY_SEEKMODE_SET = 0,
    PVR_PLAY_SEEKMODE_CUR,
    PVR_PLAY_SEEKMODE_END
} PVR_PLAY_SEEKMODE_E;

/*!
* play position
 * Note for m_offset:
 *  Unit: second
 *  Value:
 *      Positive -- forward seek
 *      Negative -- backward seek
 *note 1. m_offset:由于历史原因,m_seekmode=PVR_PLAY_SEEKMODE_END 时, m_offset 是正值,
 *         表示往文件开始方向偏移, 如果和具体平台逻辑相反, 需要HDI 内部转换成负值.
 *        2. 文件开始是当前录制文件的实际起始点,录制回绕前,为第一帧位置,
 *             录制回绕后,为回绕点的位置.
 *        3. 文件结束是当前录制文件中结束帧的位置, 没有回绕前是最后一帧的位置.
 */
typedef struct _PVR_PLAY_SEEKPARAMS_S
{
    PVR_PLAY_SEEKTYPE_E    enType;
    PVR_PLAY_SEEKMODE_E    enSeekMode;
    S64                    s64Offset;
} PVR_PLAY_SEEKPARAMS_S;

/**Status of a playing channel*//** CNcomment: 播放通道的状态  */
typedef enum _PVR_PALY_STATE_E
{
    PVR_PLAY_STATE_INVALID,       /**<Not initialized*//**<CNcomment: 未初始化            */
    PVR_PLAY_STATE_INIT,          /**<Initialized*//**<CNcomment: 初始化              */
    PVR_PLAY_STATE_PLAY,          /**<Normal playing*//**<CNcomment: 正常播放中          */
    PVR_PLAY_STATE_PAUSE,         /**<Pause*//**<CNcomment: 暂停                */
    PVR_PLAY_STATE_FF,            /**<Fast forward*//**<CNcomment: 快进                */
    PVR_PLAY_STATE_FB,            /**<Fast backward*//**<CNcomment: 快退                */
    PVR_PLAY_STATE_SF,            /**<Slow forward*//**<CNcomment: 慢放                */
    PVR_PLAY_STATE_SB,            /**<Slow backward*//**<CNcomment:慢退         */
    PVR_PLAY_STATE_STEPF,         /**<Step forward*//**<CNcomment:逐帧播放            */
    PVR_PLAY_STATE_STEPB,         /**<Step backward*//**<CNcomment: 逐帧倒放            */
    PVR_PLAY_STATE_STOP,          /**<Stop*//**<CNcomment: 停止                */
    PVR_PLAY_STATE_BUTT           /**<Invalid*//**<CNcomment: 无效的状态值        */
} PVR_PLAY_STATE_E;

/**Status of a playing channel*//** CNcomment:播放通道的状态 */
typedef struct _PVR_PLAY_STATUS_S
{
    PVR_PLAY_STATE_E        enState;                /**<Status of a playing channel*//**<CNcomment:播放通道状态。*/
    PVR_PLAY_TRICKPARAMS_S  stTrickParam;           /**<Parameters of trick*//**<CNcomment:播放的trick参数。*/
    U32                     u32CurPlayTimeInMs;     /**<PTS of the current frame, in ms*//**<CNcomment: 当前播放帧的PTS, 单位毫秒。*/
} PVR_PLAY_STATUS_S;

/**Information about a stream file recorded by the PVR*//** CNcomment:  PVR录制的码流文件信息 */
typedef struct _PVR_FILE_ATTR_S
{
    PVR_REC_INDEX_TYPE_E          enIdxType;          /**<Index type*//**<CNcomment:  索引类型 */
    U32                           u32FrameNum;        /**<For a video file: number of frames in the file. For an audio file: number of PESs in the file*//**<CNcomment:  对视频文件：文件帧数;对音频文件：文件中的PES数 */
    U32                           u32StartTimeInMs;   /**<Start time of the file, in ms*//**<CNcomment: 文件内容的起始时间，起始帧PTS，单位ms */
    U32                           u32EndTimeInMs;     /**<End time of the file, in ms*//**<CNcomment: 文件内容的结束时间，结束帧PTS，单位ms  */
    U64                           u64ValidSizeInByte; /**<Valid data length of the file, in byte *//**<CNcomment:  文件的有效数据长度，单位byte */
} PVR_FILE_ATTR_S;

/**Type of the PVR event*//** CNcomment:  PVR事件类型 */
typedef enum _PVR_EVENT_E
{
    PVR_EVENT_PLAY_EOF        = 0x001,          /**<A file is played at the end of file (EOF).*//**<CNcomment:  播放到文件尾 */
    PVR_EVENT_PLAY_SOF        = 0x002,          /**<A file is played to the start of file (SOF).*//**<CNcomment:  回退到文件头 */
    PVR_EVENT_PLAY_ERROR      = 0x003,          /**<An internal error occurs during playing.*//**<CNcomment:  播放内部错误 */
    PVR_EVENT_PLAY_REACH_REC  = 0x004,          /**<The playing speed reaches the recording speed during time shift.*//**<CNcomment:  时移的时候播放追上录制 */
    PVR_EVENT_PLAY_RESV       = 0x00f,          /**<Reserved*//**<CNcomment:  保留 */
    PVR_EVENT_REC_DISKFULL    = 0x010,          /**<The disk is full.*//**<CNcomment:  磁盘满 */
    PVR_EVENT_REC_ERROR       = 0x011,          /**<An internal error occurs during recording.*//**<CNcomment:  录制内部错误 */
    PVR_EVENT_REC_OVER_FIX    = 0x012,          /**<The length of the recorded data reaches the specified length. This event is available only in non-rewind mode.*//**<CNcomment: 录制长度达到指定的长度,只有非回绕录制才有这个事件 */
    PVR_EVENT_REC_REACH_PLAY  = 0x013,          /**<The recording speed reaches the playing speed during time shift.*//**<CNcomment:  时移的时候录制追上播放 */
    PVR_EVENT_REC_DISK_SLOW   = 0x014,          /**<The storage speed of the disk is slower than the recording speed.*//**<CNcomment: 磁盘存储速度慢于录制速度 */
    PVR_EVENT_REC_RESV        = 0x01f,          /**<Reserved*//**<CNcomment:  保留 */
    PVR_EVENT_BUTT            = 0x020           /**<Invalid event type*//**<CNcomment: 无效的事件类型 */
} PVR_EVENT_E;

/**Callback function of PVR event*//** CNcomment: PVR事件回调函数 */
typedef void (*pvr_eventCallBack)(U32 u32ChnID, PVR_EVENT_E EventType, S32 s32EventValue, VOID* args);

#ifdef ANDROID_HAL_MODULE_USED
/**PVR module structure(Android require)*/
/**CNcomment:PVR模块结构(Android对接要求) */
typedef struct _PVR_MODULE_S
{
    struct hw_module_t stCommon;
} PVR_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_PVR*/
/** @{*/  /** <!-- -[HAL_PVR]=*/

/**PVR device structure*//** CNcomment:PVR设备结构*/
typedef struct _PVR_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief PVR module init.CNcomment: 模块初始化函数 CNend
    \attention \n
    N/A
    \param[in] pstInitParams  PVR module init param.CNcomment:初始化模块参数 CNend
    \retval ::SUCCESS Success  CNcomment: 成功 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A
    */
    S32  (*pvr_init)(struct _PVR_DEVICE_S* pstDev, const PVR_RECINIT_PARAMS_S*   const  pstInitParams);

    /**
    \brief Terminate PVR module.CNcomment: PVR模块终止 CNend
    \attention \n
    N/A
    \param[in] pstTermParams Terminate param,  if NULL, force to terminate.CNcomment:终止模块参数，为NULL  表示强制终止 CNend
    \retval ::HI_SUCCESS Success  CNcomment: 成功 CNend
    \retval ::ERROR_NOT_INITED    The specified channel is not initialized.  CNcomment:模块未初始化 CNend
    \retval ::ERROR_INVALID_PARAM The pointer is null. CNcomment:参数错误 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A
    */
    S32  (*pvr_term)(struct _PVR_DEVICE_S* pstDev, const PVR_TERM_PARAMS_S* const  pstTrmParams);

    /**
    \brief Get the capability of pvr module. CNcomment:获取PVR模块设备能力 CNend
    \attention \n
    CNcomment: 无CNend
    \param[in] pstCapability Capability param.CNcomment:模块能力参数 CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::PVR_CAPABILITY_S

    \par example
    \code
    \endcode
    */
    S32  (*pvr_get_capability)(struct _PVR_DEVICE_S* pstDev, PVR_CAPABILITY_S*   const  pstCapability);

    /**
    \brief Open a record channel. CNcomment:开启一个pvr record 通道.open后处于stop状态 CNend
    \attention \n
    \param[out] pu32RecchnId Pointer to a record channel ID.CNcomment:指向录制通道ID的指针 CNend
    \param[in] enDmxId demux ID.CNcomment:demux ID CNend
    \param[in] pstRecParams record parameters.CNcomment:录制参数 CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::ERROR_PVR_REC_INVALID_DMXID demux ID is invalid .CNcomment:无效的demux ID。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::PVR_REC_OPENPARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*pvr_rec_open)(struct _PVR_DEVICE_S* pstDev, U32* const  pu32RecchnId, DMX_ID_E const enDmxId, const PVR_REC_OPENPARAMS_S* const pstRecParams);

    /**
    \brief Close a record channel. CNcomment:关闭一个PVR录制通道 CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:录制通道ID CNend
    \param[in] pstReccloseParams close parameters.CNcomment:关闭录制通道参数 CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::PVR_REC_CLOSECHNPARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*pvr_rec_close)(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId, const PVR_REC_CLOSECHNPARAMS_S*  pstReccloseParams);

    /**
    \brief start to record. CNcomment:开始录制 CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:录制通道ID CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32 (*pvr_rec_start)(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId);

    /**
    \brief stop record. CNcomment:停止录制 CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:录制通道ID CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32 (*pvr_rec_stop)(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId);

    /**
    \brief pause record. CNcomment:暂停录制 CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:录制通道ID CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_rec_pause)(struct _PVR_DEVICE_S* pstDev, const U32  u32RecchnId);

    /**
    \brief resume record. CNcomment:恢复录制 CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:录制通道ID CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_rec_resume)(struct _PVR_DEVICE_S* pstDev, const U32  u32RecchnId);

    /**
    \brief Obtains the status of a recording channel.CNcomment:  获取录制通道状态 CNend
    \attention \n
    N/A
    \param[in] u32ChnID  Channel ID  CNcomment:通道号 CNend
    \param[out] pstRecStatus   Pointer to the recording status   CNcomment:录制状态信息指针 CNend
    \retval ::HI_SUCCESS Success  CNcomment: 成功 CNend
    \retval ::HI_ERR_PVR_NOT_INIT    The PVR recording module is not initialized.  CNcomment:PVR录制模块未初始化 CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID   The channel ID is invalid.   CNcomment: 通道号非法 CNend
    \retval ::HI_ERR_PVR_CHN_NOT_INIT    The specified channel is not initialized.  CNcomment:指定的通道未初始化 CNend
    \retval ::HI_ERR_PVR_NUL_PTR        The pointer is null. CNcomment:指针参数为空 CNend
    \see \n
    N/A
    */
    S32  (*pvr_rec_getstatus)(struct _PVR_DEVICE_S* pstDev, U32  u32RecchnId, PVR_REC_STATUS_S* pstRecStatus);

    /**
    \brief add rec pid.CNcomment:  增加要录制的PID CNend
    \attention \n
    N/A
    \param[in] enDmxId  Demux ID  CNcomment:Demux 号 CNend
    \param[in] u32RecchnId  record channel ID  CNcomment:录制通道号 CNend
    \param[in] u32Pid  pid CNcomment:pid号 CNend
    \param[in] enType  pid channel type CNcomment:pid通道类型CNend
    \retval ::HI_SUCCESS Success  CNcomment: 成功 CNend
    \retval ::HI_ERR_PVR_NOT_INIT    The PVR recording module is not initialized.  CNcomment:PVR录制模块未初始化 CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID   The channel ID is invalid.   CNcomment: 通道号非法 CNend
    \retval ::HI_ERR_PVR_CHN_NOT_INIT    The specified channel is not initialized.  CNcomment:指定的通道未初始化 CNend
    \retval ::HI_ERR_PVR_NUL_PTR        The pointer is null. CNcomment:指针参数为空 CNend
    \see \n
    N/A
    */
    S32  (*pvr_rec_addpid)(struct _PVR_DEVICE_S* pstDev, DMX_ID_E  enDmxId,  U32  u32RecchnId, U32 u32Pid, DMX_CHANNEL_TYPE_E enType);

    /**
    \brief del rec pid.CNcomment:  删除录制PID CNend
    \attention \n
    N/A
    \param[in] enDmxId  Demux ID  CNcomment:Demux 号 CNend
    \param[in] u32RecchnId  record channel ID  CNcomment:录制通道号 CNend
    \param[in] u32Pid  pid CNcomment:pid号 CNend
    \retval ::HI_SUCCESS Success  CNcomment: 成功 CNend
    \retval ::HI_ERR_PVR_NOT_INIT    The PVR recording module is not initialized.  CNcomment:PVR录制模块未初始化 CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID   The channel ID is invalid.   CNcomment: 通道号非法 CNend
    \retval ::HI_ERR_PVR_CHN_NOT_INIT    The specified channel is not initialized.  CNcomment:指定的通道未初始化 CNend
    \retval ::HI_ERR_PVR_NUL_PTR        The pointer is null. CNcomment:指针参数为空 CNend
    \see \n
    N/A
    */
    S32  (*pvr_rec_delpid)(struct _PVR_DEVICE_S* pstDev, DMX_ID_E  enDmxId,  U32  u32RecchnId, U32 u32Pid);

    /**
    \brief Open a PVR play channel. CNcomment:开启一个PVR播放通道 CNend
    \attention \n
    \param[out] pu32PlaychnId Pointer to a play channel ID.CNcomment:指向播放通道ID的指针 CNend
    \param[in] enDmxId demux ID.CNcomment:demux ID CNend
    \param[in] pstPlayParams play parameters.CNcomment:播放参数 CNend
    \param[in] u32TsBufferId TS buffer ID.CNcomment:TS Buffer句柄 CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::ERROR_PVR_PLAY_INVALID_DMXID demux ID is invalid .CNcomment:无效的demux ID。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::dmx_tsbuffer_create

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_open)(struct _PVR_DEVICE_S* pstDev, U32* const pu32PlaychnId, const PVR_PLAY_OPENPARAMS_S* const pstPlayParams, HANDLE hAV, U32 u32TsBufferId);

    /**
    \brief Close a PVR play channel. CNcomment:关闭一个PVR播放通道 CNend
    \attention \n
    \param[out] pu32PlaychnId Pointer to a play channel ID.CNcomment:指向播放通道ID的指针 CNend
    \param[in] enDmxId demux ID.CNcomment:demux ID CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::ERROR_PVR_PLAY_INVALID_DMXID demux ID is invalid .CNcomment:无效的demux ID。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_close)(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);

    /**
    \brief start to PVR play. CNcomment:开始PVR回放 CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR回放通道ID CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_start)(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);

    /**
    \brief stop PVR play. CNcomment:停止PVR回放 CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR回放通道ID CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_stop)(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);

    /**
    \brief pause PVR play. CNcomment:暂停PVR回放 CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR回放通道ID CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_pause)(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);

    /**
    \brief resume PVR play. CNcomment:恢复PVR回放 CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR回放通道ID CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_resume)(struct _PVR_DEVICE_S* pstDev,  const U32  u32PlaychnId);

    /**
    \brief start PVR trick playing mode. CNcomment:调用此接口可以进行特技播放，即进行快进、快退、慢放、正常播放等操作 CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR回放通道ID CNend
    \param[in] pstPlayTrickMode trick parameters.CNcomment:特技播放参数 CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    PVR_PLAY_TRICKPARAMS_S

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_trick)(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, const PVR_PLAY_TRICKPARAMS_S* pstPlayTrickMode);

    /**
    \brief Seeks a specified position to play. CNcomment:定位到指定位置进行播放 CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR回放通道ID CNend
    \param[in] pstPlaySeekParams seek parameters.CNcomment:定位参数 CNend
    \retval ::HI_SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误。CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    PVR_PLAY_SEEKPARAMS_S

    \par example
    \code
    \endcode
    */

    S32  (*pvr_play_seek)(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, const PVR_PLAY_SEEKPARAMS_S* pstPlaySeekParams);

    /**
    \brief Obtains the playing status of the PVR. CNcomment:获取PVR回放的状态 CNend
    \attention \n
    Before calling this API to obtain the playing status, you must create a player.
    CNcomment:获取播放的状态，注意在播放器创建之后调用 CNend
    \param[in] u32ChnID
    \param[in] pstStatus
    \retval ::HI_SUCCESS Success  CNcomment: 成功 CNend
    \retval ::HI_ERR_PVR_NOT_INIT  The PVR recording module is not initialized CNcomment: PVR录制模块未初始化 CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID The channel ID is invalid.  CNcomment:通道号非法 CNend
    \retval ::HI_ERR_PVR_BUSY   The system is busy. Please try again later. CNcomment:系统忙，遇到这种情况，请重试。 CNend
    \see \n
    N/A
    */
    S32  (*pvr_play_getstatus)(struct _PVR_DEVICE_S* pstDev, U32 u32PlaychnId, PVR_PLAY_STATUS_S* const  pstStatus);

    /**
    \brief Obtains the information about the stream file recorded by the PVR based on the ID of the playing channel.  CNcomment:通过播放通道ID，获取PVR录制的码流文件信息 CNend
    \attention \n
    You can call this API to obtain the fixed information about the file to be played. However, the information is variable in the time-shift scenario.
    You can call ::HI_UNF_PVR_PlayGetStatus to obtain the current playing position during playing.\n
    You can call ::HI_UNF_PVR_RecGetStatus to obtain the current recording position during time shifting.
    In addition, if both recording and playing do not start, you can call ::HI_UNF_PVR_GetFileAttrByFileName to obtain the attributes of a file.
    CNcomment: 调用此接口用来获取播放文件的固定信息，但是对于时移场景这些信息是不断变化的
    在播放过程中可以通过::HI_UNF_PVR_PlayGetStatus接口获取当前的播放位置 \n
    在时移过程中可以通过::HI_UNF_PVR_RecGetStatus接口获取当前的录制位置
    此外，如果既没有启动录制也没有启动播放，可以通过::HI_UNF_PVR_GetFileAttrByFileName接口获取文件属性 CNend
    \param[in] u32ChnID  Channel ID  CNcomment:通道号 CNend
    \param[in] pAttr Pointer to the playing status
    \param[in] pAttr   CNcomment:播放状态信息指针 CNend
    \retval ::HI_SUCCESS  Success  CNcomment:成功 CNend
    \retval ::HI_ERR_PVR_NOT_INIT            The PVR playing module is not initialized.  CNcomment:PVR播放模块未初始化 CNend
    \retval ::HI_ERR_PVR_NUL_PTR           The pointer is null.   CNcomment: 空指针错误 CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID      The channel ID is invalid.   CNcomment:通道号非法 CNend
    \retval ::HI_ERR_PVR_CHN_NOT_INIT        The specified channel is not initialized. CNcomment: 指定的通道未初始化 CNend
    \retval ::HI_ERR_PVR_FILE_CANT_OPEN      The file cannot be opened.  CNcomment:无法打开文件 CNend
    \retval ::HI_ERR_PVR_FILE_CANT_READ    The file cannot be read.   CNcomment: 无法读文件 CNend
    \see \n
    N/A
    */

    S32  (*pvr_play_getfileattrbychannel)(struct _PVR_DEVICE_S* pstDev, U32 u32PlaychnId, PVR_FILE_ATTR_S* const pAttr);

    /**
    \brief
    Obtains the information about a stream file.
    By calling this API, you can obtain the information about a specified stream file without creating a playing channel.
    CNcomment:获取码流文件信息。调用此接口可以在不申请播放通道的情况下获取指定码流文件的信息 CNend
    \attention \n
    pFileName points to the name of a stream file rather than an index file.\n
    You can call this API to obtain the attributes of a stream file at any time.
    CNcomment:指向码流文件名而不是索引文件名.任何时候都可以调用此接口获取码流文件的属性 CNend
    \param[in] pFileName Name of a stream file  CNcomment:码流文件名 CNend
    \param[in] pAttr   Pointer to the playing status   CNcomment:播放状态信息指针 CNend
    \retval ::HI_SUCCESS  Success  CNcomment:成功 CNend
    \retval ::HI_ERR_PVR_NUL_PTR       The pointer is null.    CNcomment:空指针错误 CNend
    \retval ::HI_ERR_PVR_FILE_CANT_OPEN  The file cannot be opened.  CNcomment:无法打开文件 CNend
    \retval ::HI_ERR_PVR_FILE_CANT_READ   The file cannot be read. CNcomment:无法读文件 CNend
    \see \n
    N/A
    */
    S32  (*pvr_play_getfileattrbyfilename)(struct _PVR_DEVICE_S* pstDev, const CHAR* pFileName, PVR_FILE_ATTR_S* const pAttr);

    /**
    \brief  Writes the user data. CNcomment: 写入用户数据 CNend
    \attention \n
    pFileName points to the name of a stream file rather than an index file.\n
    The value of u32UsrDataLen cannot be greater than that of u32UsrDataInfoSize. The value of u32UsrDataInfoSize (one of recording channel attributes) is set before a file is recorded.
    The user data is saved in the index file.\n
    You need to write the user data after starting a recording channel.
    CNcomment:pFileName指向码流文件名而不是索引文件名 \n
    u32UsrDataLen的取值不能大于录制此文件时在录制通道属性里面指定的u32UsrDataInfoSize的取值 \n
    用户数据被保存在索引文件中 \n
    请在启动录制通道后再写入用户数据信息 CNend
    \param[in] pFileName Name of a stream file CNcomment: 码流文件名 CNend
    \param[in] pInfo    Pointer to the user data. The memory is allocated by customers. CNcomment:用户数据指针，空间由用户分配 CNend
    \param[in] u32UsrDataLen   Length of the user data CNcomment: 用户数据长度 CNend
    \retval ::HI_SUCCESS  Success  CNcomment:成功 CNend
    \retval ::HI_ERR_PVR_NUL_PTR       The pointer is null.   CNcomment: 空指针错误 CNend
    \retval ::HI_ERR_PVR_FILE_CANT_OPEN   The file cannot be opened.CNcomment:无法打开文件 CNend
    \retval ::HI_ERR_PVR_FILE_CANT_READ  The file cannot be read.  CNcomment:无法读文件 CNend
    \retval ::HI_ERR_DMX_INVALID_PARA    The parameter is invalid.  CNcomment: 参数非法 CNend
    \see \n
    N/A
    */
    S32  (*pvr_usrdata_setbyfilename)(struct _PVR_DEVICE_S* pstDev, const CHAR* pFileName, U8* pInfo, U32 u32UsrDataLen);

    /**
    \brief  Reads the user data. CNcomment: 读取用户数据 CNend
    \attention \n
    pFileName points to the name of a stream file rather than an index file.\n
    The return value of pUsrDataLen indicates the length of the obtained user data. The value is the smaller one between the values of u32BufLen and actual length of the user data.
    The actual length of the user data is greater than or equal to the maximum length of the user data set by calling HI_UNF_PVR_RecCreateChn. In this way, all user data can be read.\n
    The PVR does not save the length of the user data set by calling HI_UNF_PVR_SetUsrDataInfoByFileName, but save the maximum length of the user data set by calling HI_UNF_PVR_RecCreateChn.
    CNcomment:pFileName指向码流文件名而不是索引文件名 \n
    pUsrDataLen返回读取到的用户数据的长度，其取值为u32BufLen和"实际用户数据长度"二者中的较小值。
    "实际用户数据长度"将不小于HI_UNF_PVR_RecNewChn时配置的最大用户数据长度，以保证能够把全部用户数据读出 \n
    PVR模块不保存HI_UNF_PVR_SetUsrDataInfoByFileName时传入的用户数据长度，只保存HI_UNF_PVR_RecNewChn时配置的最大用户数据长度 CNend
    \param[in] pFileName    Name of a stream file CNcomment:码流文件名 CNend
    \param[in] pInfo    User data buffer. The memory is allocated by customers.   CNcomment:用户数据缓冲区，空间由用户分配 CNend
    \param[in] u32BufLen   Buffer length .CNcomment:缓冲区长度 CNend
    \param[in] pUsrDataLen Actual length of the obtained user data .CNcomment:实际读取到的用户数据长度 CNend
    \retval ::HI_SUCCESS  Success  CNcomment:成功 CNend
    \retval ::HI_ERR_PVR_NUL_PTR        The pointer is null.      CNcomment: 空指针错误 CNend
    \retval ::HI_ERR_PVR_FILE_CANT_OPEN    The file cannot be opened. CNcomment:无法打开文件 CNend
    \retval ::HI_ERR_PVR_FILE_CANT_READ    The file cannot be read.  CNcomment:无法读文件 CNend
    \retval ::HI_ERR_DMX_INVALID_PARA      The parameter is invalid.  CNcomment: 参数非法 CNend
    \see \n
    N/A
    */

    S32  (*pvr_usrdata_getbyfilename)(struct _PVR_DEVICE_S* pstDev, const CHAR* pFileName, U8* pInfo, U32 u32BufLen, U32* pUsrDataLen);

    /**
    \brief  Registers an event callback function. You can call this API to register a callback function for PVR event. In this way, you can handle the events occurred during PVR recording and playing.
    CNcomment: 注册事件回调函数。调用此接口可以注册PVR事件的回调函数，从而对PVR录制、播放过程中产生的事件进行处理 CNend
    \attention \n
    You can call ::HI_UNF_PVR_UnRegisterEvent to deregister an event. If a registered event is not deregistered, it is always valid.
    For the PVR_EVENT_PLAY_REACH_REC message, it is recommended to stop the playing of the PVR by calling the registered callback function, and switch the playing mode to live mode of the AVPLAY.
    If the recording attribute is set to non-rewind, the PVR_EVENT_REC_OVER_FIX message is reported at the end of recording when the recording length reaches the specified length.
    When the recording attribute is set to rewind, the PVR_EVENT_REC_OVER_FIX message is reported during each rewind. In this case, the value of s32EventValue of the message handling callback function is the times of rewind (counting from 1).
    The PVR_EVENT_REC_REACH_PLAY message is reported when the recording speed will reach the playing speed. In this case, the value of s32EventValue is the number of bytes between the recording position and the playing position.
    CNcomment: 可以使用::HI_UNF_PVR_UnRegisterEvent来反注册1个事件，否则已经注册的事件将一直保持有效
    对于PVR_EVENT_PLAY_REACH_REC消息，建议用户在注册的回调函数中停止PVR播放，并切换到直播模式用AVPLAY进行播放。
    当录制属性配置为不回绕的时候，PVR_EVENT_REC_OVER_FIX消息在录制长度到达指定长度，即将停止录制的时候上报；
    当录制属性配置为回绕的时候，PVR_EVENT_REC_OVER_FIX消息在每次回绕的时候都会上报，此时，消息处理回调函数的s32EventValue参数值为回绕的次数(从1开始计数)。
    PVR_EVENT_REC_REACH_PLAY消息在录制即将追上播放的时候上报，此时，消息处理回调函数的s32EventValue参数值为录制位置距离播放位置的字节数。 CNend
    \param[in] enEventType  Type of the event to be registered.  CNcomment: 想要注册的事件类型 CNend
    \param[in] callBack   Event handling callback function.   CNcomment: 事件处理函数 CNend
    \param[in] args      Parameters of a customized callback function.    CNcomment:用户自定义回调函数的参数 CNend
    \retval ::HI_SUCCESS   Success CNcomment: 成功 CNend
    \retval ::HI_ERR_PVR_INTF_EVENT_INVAL   The event is invalid.  CNcomment: 非法的事件 CNend
    \retval ::HI_ERR_PVR_ALREADY         The registering event has been registered.    CNcomment: 尝试对已经注册的事件再次注册 CNend
    \retval ::HI_ERR_PVR_INTF_EVENT_NOREG    Registration fails because the callback function pointer is incorrect. CNcomment:  回调函数指针出错，无法注册成功 CNend
    \see \n
    N/A
    */
    S32  (*pvr_event_register)(struct _PVR_DEVICE_S* pstDev, PVR_EVENT_E enEvent, pvr_eventCallBack pCallBack, VOID* pArgs);

    /**
    \brief  Deregisters a PVR event. CNcomment: 去注册PVR事件的回调函数 CNend
    \attention \n
    You can call this API to deregister an event. If a registered event is not deregistered, it is always valid.
    CNcomment: 可以使用此接口来去注册1个事件，否则已经注册的事件将一直保持有效 CNend
    \param[in] enEventType      Type of the event to be deregistered    CNcomment: 想要去注册的事件类型 CNend
    \retval ::HI_SUCCESS   Success  CNcomment:成功 CNend
    \retval ::HI_ERR_PVR_INTF_EVENT_INVAL  The event is invalid. CNcomment: 非法的事件 CNend
    \retval ::HI_ERR_PVR_INTF_EVENT_NOREG  The deregistering event is not registered. CNcomment: 对没有注册的事件进行去注册 CNend
    \see \n
    N/A
    */
    S32  (*pvr_event_unregister)(struct _PVR_DEVICE_S* pstDev, PVR_EVENT_E enEvent);

    /**
    \brief  Deletes the stream files and index files generated during recording. CNcomment:删除录制时生成的码流文件和索引文件 CNend
    \attention \n
    pFileName points to the name of a stream file rather than an index file.\n
    After this API is called, the stream files and index files generated during stream recording are deleted.
    If a stream file is greater than 4 GB, multiple files named data.ts, data.ts.0001, data.ts.0002, data.ts.0003, and ... are generated. To delete these files, you only need to enter the file name data.ts.
    CNcomment:pFileName指向码流文件名而不是索引文件名\n
    调用此接口后，录制此码流时生成的码流文件和索引文件都将被删除\n
    如果码流文件大于4G将会生成data.ts, data.ts.0001, data.ts.0002, data.ts.0003 ...\n
    等多个文件，但是删除时只需要传入文件名"data.ts"就可以了。 CNend
    \param[in] pFileName  Name of a stream file  CNcomment:码流文件名 CNend
    \retval none
    \see \n
    N/A
    */
    S32  (*pvr_remove_file)(struct _PVR_DEVICE_S* pstDev, const CHAR* pFileName);

} PVR_DEVICE_S;

/**
\brief direct get PVR device api, for linux and android.CNcomment:获取PVR设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get PVR device api，for linux and andorid.
CNcomment:获取PVR设备接口，linux和android平台都可以使用. CNend
\retval  PVR device pointer when success.CNcomment:成功返回vout设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::PVR_DEVICE_S

\par example
*/
PVR_DEVICE_S* getPVRDevice();

/**
\brief  Open HAL PVR module device.CNcomment:打开HAL PVR模块设备CNend
\attention \n
Open HAL PVR module device(for compatible Android HAL).
CNcomment:打开HAL PVR模块设备(为兼容android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice PVR device structure.CNcomment:PVR设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::PVR_DEVICE_S

\par example
*/
static inline int pvr_open(const struct hw_module_t* pstModule, PVR_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, PVR_HARDWARE_PVR0,  (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getPVRDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL PVR module deinit.CNcomment:关闭HAL PVR模块设备 CNend
\attention \n
Close HAL PVR module deinit(for compatible android HAL).
CNcomment:关闭HAL PVR模块设备(为兼容android HAL结构). CNend
\param[in] pstDevice Video output device structure.CNcomment:PVR设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::PVR_DEVICE_S

\par example
*/
static inline int pvr_close(PVR_DEVICE_S* pstDevice)
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
#endif /* __cplusplus */

#endif /* __TVOS_HAL_PVR_H__ */

