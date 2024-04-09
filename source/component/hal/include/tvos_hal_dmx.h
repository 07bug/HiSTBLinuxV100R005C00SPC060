/**
 * \file
 * \brief Describes the information about the demux module.
 */

#ifndef  __TVOS_HAL_DMX_H__
#define __TVOS_HAL_DMX_H__

#include "tvos_hal_type.h"

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

/*************************** Macro Definition ****************************/
/** \addtogroup     HAL_DMX */
/** @{ */  /** <!-- [HAL_DMX] */

#define DEMUX_HARDWARE_MODULE_ID      "dmx"
#define DEMUX_HARDWARE_DEMUX0         "demux0"
#define DEMUX_HEADER_VERSION          (1)
#define DEMUX_DEVICE_API_VERSION_1_0  HARDWARE_DEVICE_API_VERSION_2(1, 0, DEMUX_HEADER_VERSION)

/**platform dmx id number.*//** CNcomment:dmx 设备id个数 */
#define DMX_NUMBER_OF_DMX_ID 24

/**file name max length.*//** CNcomment:文件名最大长度 */
#define DMX_FILE_NAME_LENGTH 255

/**callback number for every channel.*//** CNcomment:每个channel 注册的回调函数的最大个数 */
#define DMX_CHANNEL_CALLBACK_MAX (8)

/**invalid PID.*//** CNcomment:无效的PID*/
#define DMX_INVALID_PID         (0x1FFF)

/**invalid channel ID.*//** CNcomment:无效的通道ID*/
#define DMX_INVALID_CHN_ID  (0xFFFFFFFF)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_DMX */
/** @{ */  /** <!-- [HAL_DMX] */

#ifdef ANDROID_HAL_MODULE_USED
/** demux module *//** CNcomment:demux模块 */
typedef struct _DEMUX_MODULE_S
{
    struct hw_module_t common;
} DEMUX_MODULE_S;
#endif

/** channel type *//** CNcomment:通道类型 */
typedef enum _DMX_CHANNEL_TYPE_E
{
    DMX_VIDEO_CHANNEL = 0,         /**< demux channel to output video es data only.*//**<CNcomment:demux视频通道，仅输出视频es数据 */
    DMX_AUDIO_CHANNEL,             /**< demux channel to output audio es data only.*//**<CNcomment:demux音频通道，仅输出音频es数据 */
    DMX_PES_CHANNEL,               /**< demux channel to output PES packets. *//**<CNcomment:demux PES数据过滤通道 */
    DMX_SECTION_CHANNEL,           /**< demux channel to output Section packets. *//**<CNcomment:demux Section数据过滤通道 */
    DMX_POST_CHANNEL,              /**< demux channel to full packets. *//**<CNcomment:demux整包上送通道，用于接收某PID的完整TS包 */
    DMX_PCR_CHANNEL,               /**< demux channel to output pcr packets. *//**<CNcomment:demux PCR包上送通道，用于接收某PID的PCR TS包 */
    DMX_CHANNEL_BUTT               /**< demux channel used of ECM data only. (used for clock recovery.) *//**<CNcomment:demux ECM过滤通道(用于clock recovery) */
} DMX_CHANNEL_TYPE_E;

/** Secure mode type*/
/**CNcomment:安全模式类型*/
typedef enum _DMX_SECURE_MODE_E
{
    DMX_SECURE_MODE_NONE = 0,        /** <no security protection*/ /**<CNcomment:无安全保护*/
    DMX_SECURE_MODE_TEE,             /** <trustedzone security protection*/ /**<CNcomment:trustedzone安全保护*/
    DMX_SECURE_MODE_BUTT
} DMX_SECURE_MODE_E;

/** descrambler type *//** CNcomment:解扰器类型 */
typedef enum _DMX_DESCRAMBLER_TYPE_E
{
    DMX_CA_NORMAL_DESCRAMBLER = 0, /**<normal ca descrambler.*//**<CNcomment:普通CA解扰 */
    DMX_CA_ADVANCE_DESCRAMBLER,    /**<advanced ca descrambler.*//**<CNcomment:高安CA 解扰*/
    DMX_CA_BUTT
} DMX_DESCRAMBLER_TYPE_E;

/** demux device id *//** CNcomment:demux设备id */
typedef enum _DMX_ID_E
{
    DMX_ID_0  = 0,
    DMX_ID_1,
    DMX_ID_2,
    DMX_ID_3,
    DMX_ID_4,
    DMX_ID_5,
    DMX_ID_6,
    DMX_ID_7,
    DMX_ID_8,
    DMX_ID_9,
    DMX_ID_10,
    DMX_ID_11,
    DMX_ID_12,
    DMX_ID_13,
    DMX_ID_14,
    DMX_ID_15,
    DMX_ID_16,
    DMX_ID_17,
    DMX_ID_18,
    DMX_ID_19,
    DMX_ID_20,
    DMX_ID_21,
    DMX_ID_22,
    DMX_ID_23,
    DMX_ID_BUTT
} DMX_ID_E;

/** demux event *//** CNcomment:demux事件 */
typedef enum _DMX_EVT_E
{
    DMX_ALL_EVT             = 0,          /**< all event .*//**<CNcomment:全部事件 */
    DMX_EVT_DATA_AVAILABLE  = 1,          /**< Available data.*//**<CNcomment:可用数据事件 */
    DMX_EVT_DATA_ERROR      = 1 << 1,     /**< Error data.*//**<CNcomment:数据错误事件 */
    DMX_EVT_CRC_ERROR       = 1 << 2,     /**< Crc error.*//**<CNcomment:CRC校验失败事件 */
    DMX_EVT_BUF_OVERFLOW    = 1 << 3,     /**< Buffer overflow.*//**<CNcomment:缓存溢出 */
    DMX_EVT_SCRAMBLED_ERROR = 1 << 4,     /**< Scrambled error.*//**<CNcomment:加扰错误 */
    DMX_EVT_CHANNEL_TIMEOUT = 1 << 5,     /**< Channel timeout.*//**<CNcomment:通道超时 */
    DMX_EVT_BUTT
} DMX_EVT_E;

/** The type of notify callback. The callback of each channel is same. */
/** CNcomment: 定义通知函数调用的类型,每个通道的回调类型是统一的 */
typedef enum _DMX_NOTIFY_TYPE_E
{
    DMX_NOTIFY_DATA = 0,                  /**< Callback with data. *//**<CNcomment: 通知函数将会附带数据，该数据将会从缓存中取出. 该数据无法通过read函数取出.*/
    DMX_NOTIFY_NODATA,                    /**< Callback without data. Get data by call functiong read() *//**<CNcomment: 通知函数不会附带数据，附带数据的结构成员pstSectionData为NULL, 数据通过read函数取出*/
    DMX_NOTIFY_BUTT
} DMX_NOTIFY_TYPE_E;

/** Channel status */
/** CNcomment: 通道状态 */
typedef enum _DMX_CHANNEL_STATUS_E
{
    DMX_CHANNEL_ENABLE = 0,               /**<channel enable*//**<CNcomment:通道使能 */
    DMX_CHANNEL_DISABLE,                  /**<channel disable*//**<CNcomment:通道去使能 */
    DMX_CHANNEL_RESET                     /**<channel reset*//**<CNcomment:通道重置 */
} DMX_CHANNEL_STATUS_E;

/** Demux callback option type */
/** CNcomment: Demux回调函数操作类型 */
typedef enum _DMX_CFG_CALLBACK_E
{
    DMX_CALLBACK_ENABLE = 0,              /**<callback enable*//**<CNcomment:回调使能 */
    DMX_CALLBACK_DISABLE,                 /**<callback disable*//**<CNcomment:回调去使能 */
    DMX_CALLBACK_REMOVE                   /**<callback remove*//**<CNcomment:回调函数去除 */
} DMX_CFG_CALLBACK_E;

/** Demux filter repeat mode */
/** CNcomment: Demux上报数据方式 */
typedef enum _DMX_FILTER_REPEAT_MODE_E
{
    DMX_FILTER_REPEAT_MODE_REPEATED = 0,  /**<Repeated*/   /**<CNcomment:重复上报数据 */
    DMX_FILTER_REPEAT_MODE_ONE_SHOT,      /**<One shot*/   /**<CNcomment:仅上报一次数据 */
    DMX_FILTER_REPEAT_MODE_BUTT
} DMX_FILTER_REPEAT_MODE_E;

/** Demux descrambler associate type */
/** CNcomment: 解扰器关联类型 */
typedef enum _DMX_DESC_ASSOCIATE_MODE_E
{
    DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDS = 0,    /**<With pids*/   /**<CNcomment:与PID关联 */
    DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNEL,     /**<With channel*/   /**<CNcomment:与通道关联 */
    DMX_DESCRAMBLER_ASSOCIATE_BUTT
} DMX_DESC_ASSOCIATE_MODE_E;

/** Demux descrambler type */
/** CNcomment: 解扰加密类型 */
typedef enum _DMX_DESC_TYPE_E
{
    DMX_DESC_TYPE_CSA2 = 0,               /**<CSA2.0*/
    DMX_DESC_TYPE_CSA3,                   /**<CSA3.0*/
    DMX_DESC_TYPE_DES_CI,                 /**<DES CIPLUS*/
    DMX_DESC_TYPE_DES_CBC,                /**<DES CBC*/
    DMX_DESC_TYPE_DES_IPTV,               /**<DES IPTV*/
    DMX_DESC_TYPE_TDES_ECB,               /**<TDES ECB*/
    DMX_DESC_TYPE_TDES_CBC,               /**<TDES CBC*/
    DMX_DESC_TYPE_TDES_IPTV,              /**<TDES IPTV*/
    DMX_DESC_TYPE_AES_ECB,                /**<SPE AES ECB*/
    DMX_DESC_TYPE_AES_CBC,                /**<AES CBC*/
    DMX_DESC_TYPE_AES_IPTV,               /**<AES IPTV of SPE*/
    DMX_DESC_TYPE_AES_NS,                 /**<AES NS-Mode*/
    DMX_DESC_TYPE_AES_CI,                 /**<SPE AES CIPLUS*/
    DMX_DESC_TYPE_SMS4_ECB,               /**<SMS4 ECB*/
    DMX_DESC_TYPE_SMS4_CBC,               /**<SMS4 CBC*/
    DMX_DESC_TYPE_SMS4_IPTV,              /**<SMS4 IPTV*/
    DMX_DESC_TYPE_SMS4_NS,                /**<SMS4 NS-Mode*/
    DMX_DESC_TYPE_BUTT
} DMX_DESC_TYPE_E;

/**CA Entropy reduction mode*/
/**CNcomment:熵减少模式*/
typedef enum _DMX_CA_ENTROPY_E
{
    DMX_CA_ENTROPY_REDUCTION_CLOSE = 0,   /**<64bit*/
    DMX_CA_ENTROPY_REDUCTION_OPEN,        /**<48bit*/

    DMX_CA_ENTROPY_REDUCTION_BUTT
} DMX_CA_ENTROPY_E;

/** Demux descrambler style */
/** CNcomment: 解扰类型 */
typedef enum _DMX_DESC_STYLE_E
{
    DMX_DESC_STYLE_NONE = 0,              /**< Not support descramble */  /**<CNcomment:不支持解扰 */
    DMX_DESC_STYLE_SOLE,                  /**< Each pid can descramble sole channel */  /**<CNcomment:同一个pid,只能解扰一路 */
    DMX_DESC_STYLE_SHARE,                 /**< Each pid can descramble share */  /**<CNcomment:同一个pid,一个解扰器同时解扰多路,不能开多个解扰器 */
    DMX_DESC_STYLE_BIUNIQUE,              /**< Each pid can descramble multi channel, Each descrambler for each channel */  /**<CNcomment:同一个pid,多个解扰器同时解扰多路,解扰器与通道一对一 */
    DMX_DESC_STYLE_BUTT
} DMX_DESC_STYLE_E;

/** Source type. Just support tuner. */
/** CNcomment: 数据来源类型.这里只是支持tuner, 其他放在pvr模块 */
typedef enum _DMX_SOURCE_TYPE_E
{
    DMX_SOURCE_TUNER = 0,                 /**< Tuner, av or pvr. *//**<CNcomment: tuner: 直播,pvr录制等*/
    DMX_SOURCE_FILE,                      /**< File *//**<CNcomment: 文件 */
    DMX_SOURCE_MEM,                       /**< Ts inject *//**<CNcomment: TS流注入 */
    DMX_SOURCE_PVR,                       /**< PVR file or local stream file. *//**<CNcomment: pvr播放文件,本地媒体播放. */
    DMX_SOURCE_NONE,                      /**< Free demux without source *//**<CNcomment: 空闲的demux */
    DMX_SOURCE_BUTT
} DMX_SOURCE_TYPE_E;

/** Demux filter attr */
/** CNcomment:1.u8Match,u8Mask,u8Notmask 都是按照bit 为单位来操作的.
        2. 如果u8Notmask==NULL, 则不处理非匹配掩码.
        3. u8Match 和u8Mask 不能为NULL.
        4. u8Mask 指向匹配掩码的指针,
            与u8Match对应的比特相与,如果u8Mask 的某位为1,接收到的数据必须与u8Match中对应的比特匹配,
              如果为u8Mask的某位0,则该位忽略.
        5. u8Notmask指向非匹配掩码的指针.
            在u8Mask为1的所有对应的比特当中,接收到的数据至少应该有一个比特与u8Match不一致,
             则认为接受的数据是匹配的,如果所有的比特都是匹配的,则认为是不匹配的.
        6. section的第2,3两个字节数据是section length字段,一般不做过滤处理.不过
             hdi 会根据具体平台确定是否跳过2,3,字节.
        7. 有些平台上带不带 u8Notmask 数据,将是不同的filter 类型.而且可能限制同一个channel不能有不同类型的filter.
             对于这种平台,应用要设置好filter类型,
        8. 有些平台上带不带 u8Notmask 数据,将是不同的filter 类型.而且可能限制同一个filter 不能动态修改 filter 类型.
             对于这种平台,HDI 自己要做好兼容.(比如更改类型的时候,把老的filter 先close,再open).
        9. 当u8Notmask和u8Mask 相应位冲突的时候,以u8Notmask,为准.
 */
typedef struct  _DMX_FILTER_DATA_S
{
    DMX_FILTER_REPEAT_MODE_E enFilterRepeatMode;  /**< Data repeat type. *//**<CNcomment: 数据重复模式 */
    U32                      u32FilterSize;       /**< Filter size *//**<CNcomment: 过滤数据的有效长度.*/
    U8*                      pu8Match;            /**< Matched bytes of a filter.The data is compared by bit.*/ /**< CNcomment:过滤器匹配字节,按bit比较*/
    U8*                      pu8Mask;             /**< Point to mask *//**<CNcomment: 指向匹配掩码的指针.*/
    U8*                      pu8Notmask;          /**< Point to not mask *//**<CNcomment: 指向非匹配掩码的指针.*/
} DMX_FILTER_DATA_S;

/** Source type params */
/** CNcomment: 数据来源参数 DMX_SOURCE_TYPE_E, dmd_info_s, av_inject_status_s,pvr_play_info_s.
1. enSourceType == DMX_SOURCE_TUNER:hDmx 请查看dmd_info_s::source_id;
3. enSourceType == DMX_SOURCE_FILE:u8FileName 目前暂时没有定义,
3. enSourceType == DMX_SOURCE_MEM:hInjecter 请查看av_inject_status_s::m_source_id;
4. enSourceType == DMX_SOURCE_PVR:u32PlaychnId 请查看pvr_play_info_s::m_source_id;
5. enSourceType == DMX_SOURCE_NONE:u32Dummy 以后扩展用;
 */
typedef struct  _DMX_SOURCE_PARAMS_S
{
    DMX_SOURCE_TYPE_E enSourceType;
    union _DMX_SOURCE_U
    {
        HANDLE hSource;                              /**< enSourceType == DMX_SOURCE_TUNER*//**<CNcomment: enSourceType == DMX_SOURCE_TUNER*/
        CHAR u8FileName[DMX_FILE_NAME_LENGTH + 1];   /**< enSourceType == DMX_SOURCE_FILE*//**<CNcomment: enSourceType == DMX_SOURCE_FILE*/
        HANDLE hInjecter;                            /**< enSourceType == DMX_SOURCE_MEM*//**<CNcomment: enSourceType == DMX_SOURCE_MEM*/
        U32 u32PlaychnId;                            /**< enSourceType == DMX_SOURCE_PVR*//**<CNcomment: enSourceType == DMX_SOURCE_PVR*/
        U32 u32Dummy;                                /**< enSourceType == DMX_SOURCE_NONE*//**<CNcomment: enSourceType == DMX_SOURCE_NONE*/
    } DMX_SOURCE_U;
} DMX_SOURCE_PARAMS_S;

/** Demux descrambler associate params */
/** CNcomment: 解扰器关联参数 */
typedef struct  _DMX_DESC_ASSOCIATE_PARAMS_S
{
    DMX_DESC_ASSOCIATE_MODE_E enMode;
    union _DMX_ASSOCIATE_U
    {
        U32 u32ChannelId;                            /**< enMode == DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNEL */
        U16 u16Pid;                                  /**< enMode == DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDS */
    } DMX_ASSOCIATE_U;
} DMX_DESC_ASSOCIATE_PARAMS_S;

/**Attribute of the descrambler.*/
/**CNcomment:解扰器属性*/
typedef struct _DMX_DESCRAMBLER_ATTR_S
{
    DMX_DESCRAMBLER_TYPE_E enCaType;                 /**<Whether the descrambler adopts advanced CA.*/ /**< CNcomment:解扰器是否使用高安全CA*/
    DMX_DESC_TYPE_E enDescramblerType;               /**<Descrambling protocol type of the descrambler*/ /**< CNcomment:解扰器解扰协议类型*/
    DMX_CA_ENTROPY_E enEntropyReduction;             /**<CA Entropy reduction mode,for CSA2.0*/ /**< CNcomment:熵减少模式，CSA2.0有效*/
} DMX_DESCRAMBLER_ATTR_S;

/** advanced CA Encrypt arith*/
typedef enum _DMX_KL_ALG_E
{
    DMX_KL_ALG_TDES = 0,                             /**<Encrypt arith : 3DES*/
    DMX_KL_ALG_AES,                                  /**<Encrypt arith : AES*/
    DMX_KL_ALG_BUTT
} DMX_KL_ALG_E;

/**Defines the setting of the DCAS keyladder.*/
/**CNcomment: 定义DCAS keyladder设置结构体.*/
typedef struct _DMX_DCAS_KEYLADDER_SETTING_S
{
    DMX_KL_ALG_E enKLAlg;                 /**<Keyladder algorithm, TDES/AES*/
    U32 u32CAVid;                         /**<Verdor_SysID*/
    U8* pu8EK2;                           /**<EK3(K2) key, 16bytes*/
    U8* pu8EK1;                           /**<EK2(K1) key, 16bytes*/
    U8* pu8EvenKey;                       /**<EK1(CW) even key, 16bytes, if it's NULL, there is no even key*/
    U8* pu8OddKey;                        /**<EK1(CW) odd key, 16bytes, if it's NULL, there is no odd key*/
} DMX_DCAS_KEYLADDER_SETTING_S;

/**Defines the setting of the DCAS keyladder.*/
/**CNcomment: 定义DCAS keyladder设置结构体.*/
typedef struct _DMX_DCAS_NONCE_SETTING_S
{
    DMX_KL_ALG_E enKLAlg;                 /**<Keyladder algorithm, TDES/AES*/
    U32 u32CAVid;                         /**<Verdor_SysID*/
    U8* pu8EK2;                           /**<EK3(K2) key, 16bytes*/
    U8* pu8Nonce;                         /**<Nonce, 16bytes*/
} DMX_DCAS_NONCE_SETTING_S;

/** Channel setting params */
/** CNcomment:通道配置参数
channel设置参数有相应的get和set函数来获取和设置
注意,需要修改这些参数时,请先get出来,修改需要修改的成员再set回去
set函数里面对于没有改变的成员不做修改
注意:考虑到多任务操作,get出来的参数在set回去之前,别的任务可能已经有set操作
就是此时的set有可能会覆盖其他任务set函数的设置
*/
typedef  struct DMX_CHANNEL_SETTING_S
{
    DMX_NOTIFY_TYPE_E enNotifyType;       /**< DMX_NOTIFY_TYPE_E*/
    U32               u32IsCRC;           /**< If enable CRC,default 1, 0 for disable CRC and 1 for enable CRC. *//**<CNcomment: 在接收数据时是否打开CRC校验,默认:1,0:关闭CRC校验.1:打开CRC校验, 如果CRC 校验失败,或者没有CRC,则对应的数据丢弃.*/
    U32               u32AddData;         /**< Additional data *//**<CNcomment: 附加的数据。在一些CA里面会用*/
    U32               u32Tag;             /**< Optional tag value *//**<CNcomment: 标志位值，可选*/
} DMX_CHANNEL_SETTING_S;

/** Channel info, just like channel type, channel status, channel PID etc. */
/** CNcomment:通道信息，包括通道类型,当前工作状态,当前pid等 */
typedef  struct _DMX_CHANNEL_INFO_S
{
    DMX_ID_E             enDemuxId;       /**<Demux ID *//**<CNcomment: 标识 属于哪个DEMUX*/
    DMX_CHANNEL_TYPE_E   enType;          /**<Channel ID *//**<CNcomment: 接收数据的类型，PES或者SECTION*/
    DMX_CHANNEL_STATUS_E enStatus;        /**<Channel status *//**<CNcomment: 该通道当前的工作状态*/
    U32                  u32CallbackNum;  /**<Callback number *//**<CNcomment: 回调函数的个数*/
    U32                  u32FilterNum;    /**<Filter number *//**<CNcomment: filter的个数*/
    U32                  u32PacketCount;  /**<Packet number *//**<CNcomment: 不需要精确的个数,主要用于查询有没有数据上来,用于查错*/
    U16                  u16Pid;          /**<Channel PID *//**<CNcomment: 要接收数据的PID，*/
    U32                  u32Len;          /**<The max data size *//**<CNcomment: 最大接收的数据长度，DEMUX分配多少内存来接收数据*/
} DMX_CHANNEL_INFO_S;

/** Section data */
/** CNcomment:Section数据 */
typedef struct  _DMX_SECTION_DATA_S
{
    U32      u32Length;
    VOID*    pData;
} DMX_SECTION_DATA_S;

/** Demux callback params */
/** CNcomment:回调函数参数 */
typedef struct  _DMX_CALLBACK_DATA_S
{
    DMX_SECTION_DATA_S*   pstSectionData; /**<Section data. It can be NULL if no data send. *//**<CNcomment: section 数据,如为空表示回调函数不附带数据*/
    U32                   u32ChannelId;   /**<Channel ID *//**<CNcomment:  当前的通道号 */
    DMX_EVT_E             enEvt;          /**<Channel event *//**<CNcomment:  当前的通道的事件*/
    DMX_ID_E              enDemuxId;      /**<Demux ID *//**< CNcomment: 当前的通道的demux id*/
    U32                   u32FilterId;    /**<Filter ID *//**<CNcomment: 当前的channel的u32FilterId, 如果不支持,返回: INVALID_ID */
} DMX_CALLBACK_DATA_S;

/**
 \brief channel callback.CNcomment:通道回调函数 CNend
 \attention \n
It can call api in this module.
CNcomment:回调函数里面可以调用本模块的接口. CNend
 \param[in] pstData callback params.CNcomment:回调函数参数 CNend
 \retval ::SUCCESS Success.CNcomment:成功。CNend
 \retval ::FAILURE  other error.CNcomment:其它错误 CNend
 \see \n
::DMX_CALLBACK_DATA_S
 */
typedef S32 (*DMX_CALLBACK_PFN)(const DMX_CALLBACK_DATA_S* const pstData);

/** Demux registe callback sturct */
/** CNcomment:demux注册回调函数结构 */
typedef struct  _DMX_REG_CALLBACK_PARAMS_S
{
    DMX_CALLBACK_PFN pfnCallback;         /**<Callback function.*//**<CNcomment:需要注册的回调函数*/
    U32              u32IsDisable;        /**<If set the function able.*//**<CNcomment:是否使能该回调: 0 is enable; 1 is disable*/
    DMX_EVT_E        enEvt;               /**<Demux event.*//**<CNcomment:demux事件,标识这个回调对哪些事件有效, 1.可以过滤掉自己不关心的事件,2.TVOS_HAL_DMX_ALL_EVT表示该通道发生的所有事件都会调用此回调函数 */
} DMX_REG_CALLBACK_PARAMS_S;

/** Demux init params */
/** CNcomment:demux初始化参数 */
typedef  struct _DMX_INIT_PARAMS_S
{
    U32 u32TaskPriority;                  /**<Task priority.*//**<CNcomment: 任务优先级，由平台集成者统一管理*/
} DMX_INIT_PARAMS_S;

/** Demux term params */
/** CNcomment:demux通道终止参数 */
typedef  struct _DMX_TERM_PARAM_S
{
    U8 u8Dummy;                           /**<Reserved.*//**< CNcomment: 保留参数.*/
} DMX_TERM_PARAM_S;

/** Demux open params */
/** CNcomment:demux通道打开参数 */
typedef  struct _DMX_CHANNEL_OPEN_PARAM_S
{
    U32                   u32Pid;            /**<Channel PID. It can be setted by dmx_channel_set_pid. */ /**<CNcomment:要接收数据的PID，也可以在以后通过dmx_channel_set_pid函数来设定*/
    U32                   u32Len;            /**<Length of memory to receiving data. */ /**<CNcomment:最大接收的数据长度，用来告诉DEMUX应该分配多少内存来接收数据, 如果应用传进来的buf长度太小, 必须保证不死机.*/
    DMX_CHANNEL_TYPE_E    enType;            /**<Channel type */ /**<CNcomment: 接收数据的类型 */
    U32                   u32FirstIndex;     /**<First channel index to find free one *//**<CNcomment:确定从指定dmx上哪个实际的物理channel开始查找可以打开的channel，即:可以预留前面几个通道出来 */
    DMX_CHANNEL_SETTING_S stChannelSettings; /**<Channel settings*//**<CNcomment:当前的channel设置*/
    DMX_SECURE_MODE_E     enSecureMode;      /**<Secure channel indication*/ /**<CNcomment:安全通道标示*/
} DMX_CHANNEL_OPEN_PARAM_S;

/** Demux close params */
/** CNcomment:demux通道关闭参数 */
typedef  struct _DMX_CHANNEL_CLOSE_PARAMS_S
{
    U8 u8Dummy;                           /**<Reserved.*//**< CNcomment: 保留参数.*/
} DMX_CHANNEL_CLOSE_PARAMS_S;

/** Demux capability */
/** CNcomment:demux能力 */
typedef struct  _DMX_CAPABILITY_S
{
    U32              u32DMXNum;
    U32              u32ChannelNumArr[DMX_ID_BUTT];
    U32              u32FilterNumArr[DMX_ID_BUTT];
    U32              u32DescramblerNumArr[DMX_ID_BUTT];
    DMX_DESC_STYLE_E enDescStyle;         /**<Descrambler style.*//**< CNcomment: 解扰器风格.*/
    DMX_DESC_STYLE_E enAdvDescStyle;      /**<Advanced descrambler style.*//**< CNcomment: 高安解扰器风格.*/
} DMX_CAPABILITY_S;

/** Demux status */
/** CNcomment:demux状态 */
typedef struct  _DMX_STATUS_S
{
    U32 u32FreeChannelNum;                /**<Free channel number.*//**<CNcomment: 空闲通道数量 */
    U32 u32FreeFilterNum;                 /**<Free filter number.*//**<CNcomment: 空闲过滤器数量 */
    U32 u32FreeDescramblerNum;            /**<Free descrambler number.*//**<CNcomment: 空闲解扰器数量 */
    U32 u32TsPacketCount;                 /**<Ts packet number.*//**<CNcomment: ts包数量 */
    U32 u32IsConnect;                     /**<Is connect.*//**<CNcomment: 是否连接 */
} DMX_STATUS_S;

/** Demux channel data struct */
/** CNcomment:获取DEMUX通道数据包结构*/
typedef enum _DMX_CHANNEL_DATA_TYPE_E
{
    DMX_DATA_TYPE_WHOLE = 0,              /**<Whole data.*//**<CNcomment: 此段数据包含完整的数据包, 对于SECTION每个包都是完整的*/
    DMX_DATA_TYPE_HEAD,                   /**<Head data. Just for PES *//**<CNcomment: 此段数据包含数据包的起始，但是不一定是完整的包, 只用于PES数据*/
    DMX_DATA_TYPE_BODY,                   /**<Body data. Just for PES *//**<CNcomment:  此段数据包含数据包的内容，不包含起始，可能有结尾, 只用于PES数据*/
    DMX_DATA_TYPE_TAIL,                   /**<Tail data. Just for PES *//**<CNcomment: 此段数据包含数据包的结尾，用于指示可识别的包结束, 只用于PES数据*/
    DMX_DATA_TYPE_BUTT
} DMX_CHANNEL_DATA_TYPE_E;

/** Demux channel data struct */
/**CNcomment:获取DEMUX通道数据包结构*/
typedef struct _DMX_CHANNEL_DATA_S
{
    U8*                     pu8Data;      /**<Data pointer*//**< CNcomment:数据指针 */
    U32                     u32Size;      /**<Data length*//**< CNcomment:数据长度 */
    DMX_CHANNEL_DATA_TYPE_E enDataType;   /**<Data packet type*//**< CNcomment:数据包的类型 */
} DMX_CHANNEL_DATA_S;


/**Defines of Defines of demux AVFilter video stream type.*/
/**CNcomment: 视频流类型*/
typedef enum _DMX_VID_STREAM_TYPE_E
{
    DMX_VID_STREAM_TYPE_UNKNOWN = -1,
    DMX_VID_STREAM_TYPE_MPEG2 = 0,   /**<MPEG2*/
    DMX_VID_STREAM_TYPE_MPEG4,       /**<MPEG4 DIVX4 DIVX5*/
    DMX_VID_STREAM_TYPE_AVS,         /**<AVS*/
    DMX_VID_STREAM_TYPE_AVSPLUS,     /**<AVSPLUS*/
    DMX_VID_STREAM_TYPE_H263,        /**<H263*/
    DMX_VID_STREAM_TYPE_H264,        /**<H264*/
    DMX_VID_STREAM_TYPE_REAL8,       /**<REAL*/
    DMX_VID_STREAM_TYPE_REAL9,       /**<REAL*/
    DMX_VID_STREAM_TYPE_VC1,         /**<VC-1*/
    DMX_VID_STREAM_TYPE_VP6,         /**<VP6*/
    DMX_VID_STREAM_TYPE_VP6F,        /**<VP6F*/
    DMX_VID_STREAM_TYPE_VP6A,        /**<VP6A*/
    DMX_VID_STREAM_TYPE_MJPEG,       /**<MJPEG*/
    DMX_VID_STREAM_TYPE_SORENSON,    /**<SORENSON SPARK*/
    DMX_VID_STREAM_TYPE_DIVX3,       /**<DIVX3*/
    DMX_VID_STREAM_TYPE_RAW,         /**<RAW*/
    DMX_VID_STREAM_TYPE_JPEG,        /**<JPEG,added for VENC*/
    DMX_VID_STREAM_TYPE_VP8,         /**<VP8*/
    DMX_VID_STREAM_TYPE_VP9,         /**<VP9*/
    DMX_VID_STREAM_TYPE_MSMPEG4V1,   /**<MS private MPEG4 */
    DMX_VID_STREAM_TYPE_MSMPEG4V2,
    DMX_VID_STREAM_TYPE_MSVIDEO1,    /**<MS video */
    DMX_VID_STREAM_TYPE_WMV1,
    DMX_VID_STREAM_TYPE_WMV2,
    DMX_VID_STREAM_TYPE_RV10,
    DMX_VID_STREAM_TYPE_RV20,
    DMX_VID_STREAM_TYPE_SVQ1,        /**<Apple video */
    DMX_VID_STREAM_TYPE_SVQ3,        /**<Apple video */
    DMX_VID_STREAM_TYPE_H261,
    DMX_VID_STREAM_TYPE_VP3,
    DMX_VID_STREAM_TYPE_VP5,
    DMX_VID_STREAM_TYPE_CINEPAK,
    DMX_VID_STREAM_TYPE_INDEO2,
    DMX_VID_STREAM_TYPE_INDEO3,
    DMX_VID_STREAM_TYPE_INDEO4,
    DMX_VID_STREAM_TYPE_INDEO5,
    DMX_VID_STREAM_TYPE_MJPEGB,
    DMX_VID_STREAM_TYPE_MVC,
    DMX_VID_STREAM_TYPE_HEVC,
    DMX_VID_STREAM_TYPE_DV,
    DMX_VID_STREAM_TYPE_BUTT
} DMX_VID_STREAM_TYPE_E;

/**CNcomment: 音频流类型*/
typedef enum _DMX_AUD_STREAM_TYPE_E
{
    DMX_AUD_STREAM_TYPE_UNKNOWN = -1,
    DMX_AUD_STREAM_TYPE_MP2 = 0x000,
    DMX_AUD_STREAM_TYPE_MP3,
    DMX_AUD_STREAM_TYPE_AAC,
    DMX_AUD_STREAM_TYPE_AC3,
    DMX_AUD_STREAM_TYPE_DTS,
    DMX_AUD_STREAM_TYPE_VORBIS,
    DMX_AUD_STREAM_TYPE_DVAUDIO,
    DMX_AUD_STREAM_TYPE_WMAV1,
    DMX_AUD_STREAM_TYPE_WMAV2,
    DMX_AUD_STREAM_TYPE_MACE3,
    DMX_AUD_STREAM_TYPE_MACE6,
    DMX_AUD_STREAM_TYPE_VMDAUDIO,
    DMX_AUD_STREAM_TYPE_SONIC,
    DMX_AUD_STREAM_TYPE_SONIC_LS,
    DMX_AUD_STREAM_TYPE_FLAC,
    DMX_AUD_STREAM_TYPE_MP3ADU,
    DMX_AUD_STREAM_TYPE_MP3ON4,
    DMX_AUD_STREAM_TYPE_SHORTEN,
    DMX_AUD_STREAM_TYPE_ALAC,
    DMX_AUD_STREAM_TYPE_WESTWOOD_SND1,
    DMX_AUD_STREAM_TYPE_GSM,
    DMX_AUD_STREAM_TYPE_QDM2,
    DMX_AUD_STREAM_TYPE_COOK,
    DMX_AUD_STREAM_TYPE_TRUESPEECH,
    DMX_AUD_STREAM_TYPE_TTA,
    DMX_AUD_STREAM_TYPE_SMACKAUDIO,
    DMX_AUD_STREAM_TYPE_QCELP,
    DMX_AUD_STREAM_TYPE_WAVPACK,
    DMX_AUD_STREAM_TYPE_DSICINAUDIO,
    DMX_AUD_STREAM_TYPE_IMC,
    DMX_AUD_STREAM_TYPE_MUSEPACK7,
    DMX_AUD_STREAM_TYPE_MLP,
    DMX_AUD_STREAM_TYPE_GSM_MS,
    DMX_AUD_STREAM_TYPE_ATRAC3,
    DMX_AUD_STREAM_TYPE_VOXWARE,
    DMX_AUD_STREAM_TYPE_APE,
    DMX_AUD_STREAM_TYPE_NELLYMOSER,
    DMX_AUD_STREAM_TYPE_MUSEPACK8,
    DMX_AUD_STREAM_TYPE_SPEEX,
    DMX_AUD_STREAM_TYPE_WMAVOICE,
    DMX_AUD_STREAM_TYPE_WMAPRO,
    DMX_AUD_STREAM_TYPE_WMALOSSLESS,
    DMX_AUD_STREAM_TYPE_ATRAC3P,
    DMX_AUD_STREAM_TYPE_EAC3,
    DMX_AUD_STREAM_TYPE_SIPR,
    DMX_AUD_STREAM_TYPE_MP1,
    DMX_AUD_STREAM_TYPE_TWINVQ,
    DMX_AUD_STREAM_TYPE_TRUEHD,
    DMX_AUD_STREAM_TYPE_MP4ALS,
    DMX_AUD_STREAM_TYPE_ATRAC1,
    DMX_AUD_STREAM_TYPE_BINKAUDIO_RDFT,
    DMX_AUD_STREAM_TYPE_BINKAUDIO_DCT,
    DMX_AUD_STREAM_TYPE_DRA,
    DMX_AUD_STREAM_TYPE_PCM,
    DMX_AUD_STREAM_TYPE_PCM_BLURAY,
    DMX_AUD_STREAM_TYPE_ADPCM ,
    DMX_AUD_STREAM_TYPE_AMR_NB,
    DMX_AUD_STREAM_TYPE_AMR_WB,
    DMX_AUD_STREAM_TYPE_AMR_AWB,
    DMX_AUD_STREAM_TYPE_RA_144,
    DMX_AUD_STREAM_TYPE_RA_288,
    DMX_AUD_STREAM_TYPE_DPCM,
    DMX_AUD_STREAM_TYPE_G711,
    DMX_AUD_STREAM_TYPE_G722,
    DMX_AUD_STREAM_TYPE_G7231,
    DMX_AUD_STREAM_TYPE_G726,
    DMX_AUD_STREAM_TYPE_G728,
    DMX_AUD_STREAM_TYPE_G729AB,
    DMX_AUD_STREAM_TYPE_MULTI,
    DMX_AUD_STREAM_TYPE_BUTT,
} DMX_AUD_STREAM_TYPE_E;

/**Demux parser filter open param*/
/**CNcomment:Demux模块过滤数据打开参数 */
typedef  struct _DMX_PARSER_FILTER_OPEN_PARAM_S
{
    U32                     u32Pid;       /**<Channel pid. */ /**<CNcomment:  接收数据的通道PID */
    DMX_CHANNEL_TYPE_E      enType;       /**<Channel type */ /**<CNcomment:  接收数据的类型 */
    union _DMX_AV_STREAM_TYPE_U
    {
        DMX_VID_STREAM_TYPE_E enVIDEsTpye; /**<video type *//**<CNcomment:  视频流类型 */
        DMX_AUD_STREAM_TYPE_E enAUDEsType; /**<audio type *//**<CNcomment:  音频流类型 */
    } DMX_AV_STREAM_TYPE_U;

} DMX_PARSER_FILTER_OPEN_PARAM_S;

/**Demux esframe info*/
/**CNcomment:Demux es帧信息 */
typedef struct _DMX_ESFRAME_INFO_S
{
    U64 u64BufferAddr;  /**<Buffer address. */ /**<CNcomment:  数据地址 */
    U32 u32Lenght;      /**<Frame length. */ /**<CNcomment:  帧长度 */
    U64 u64Timestamp;   /**<PTS. */ /**<CNcomment:  时间戳 */
} DMX_ESFRAME_INFO_S;

/** Stream data */
/** CNcomment:流数据 */
typedef struct  _DMX_STREAM_DATA_S
{
    U32      u32Length;
    U8*      pu8Data;
} DMX_STREAM_DATA_S;

/** TS buffer attribute*/
/**CNcomment:TS buffer 属性*/
typedef struct _DMX_TSBUF_ATTR_S
{
    DMX_SECURE_MODE_E   enSecureMode;   /**<Secure indication*/ /**<CNcomment:安全标示*/
    U32                 u32BufSize;     /**<Buffer size*/ /**< CNcomment:缓冲区大小*/
} DMX_TSBUF_ATTR_S;


#ifdef ANDROID_HAL_MODULE_USED
/**Demux module structure(Android require)*/
/**CNcomment:解复用模块结构(Android对接要求) */
typedef struct _DMX_MODULE_S
{
    struct hw_module_t stCommon;
} DMX_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_DMX*/
/** @{*/  /** <!-- -[HAL_DMX]=*/

/**Demux device structure*//** CNcomment:解复用设备结构*/
typedef struct _DEMUX_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
     \brief Demux  init.CNcomment:dmx模块初始化函数。 CNend
     \attention \n
    Repeat call return success.
    CNcomment:重复调用init 接口,返回SUCCESS. CNend
     \param[in] pstInitParams system module init param.CNcomment:初始化模块参数 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_DMX_INIT_FAILED  Lower layer dmx module init error.CNcomment:底层DMX模块初始化错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_INIT_PARAMS_S
     */
    S32 (*dmx_init)(struct _DEMUX_DEVICE_S* pstDev, const DMX_INIT_PARAMS_S* const pstInitParams );

    /**
     \brief Demux  deinit. CNcomment:dmx模块终止 CNend
     \attention \n
    CNcomment:释放相关资源,终止后必须重新初始化才能重新操作，即: 终止后除了获取版本信息和初始化函数，其他函数都不能正确运行. 重复term 返回SUCCESS.CNend
     \param[in] pstTermParams system module deinit param.CNcomment:终止参数 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_DMX_DEINIT_FAILED  Lower layer dmx module deinit error.CNcomment:底层DMX模块去初始化错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_TERM_PARAM_S
     */
    S32 (*dmx_term)(struct _DEMUX_DEVICE_S* pstDev, const DMX_TERM_PARAM_S* const pstTermParams );

    /**
     \brief Set demux source. CNcomment:设置Demux数据源 CNend
     \attention \n
    CNcomment: 设置之后处于连接状态 CNend
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \param[in] pstSourceParams source param. CNcomment:源参数 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_SOURCE_PARAMS_S
     */
    S32 (*dmx_set_source_params)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, const DMX_SOURCE_PARAMS_S* pstSourceParams);

    /**
     \brief Get demux source param. CNcomment:获取Demux数据源参数 CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \param[out] pstSourceParams source param. CNcomment:源参数 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_SOURCE_PARAMS_S
     */
    S32 (*dmx_get_source_params)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, DMX_SOURCE_PARAMS_S* const pstSourceParams);

    /**
     \brief Demux disconnect. CNcomment:断开dmx与数据源(如dmd)的关联,开机默认是关联的 CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_ID_E
     */
    S32 (*dmx_disconnect)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId);

    /**
     \brief Demux reconnect. CNcomment:恢复dmx与当前设置的数据源(如dmd)的关联,开机默认是关联的 CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_ID_E
     */
    S32 (*dmx_reconnect)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId);

    /**
     \brief Get demux capability. CNcomment:获取demux的能力 CNend
     \attention \n
     \param[out] pstCapability demux capability.CNcomment:Demux能力 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_CAPABILITY_S
     */
    S32 (*dmx_get_capability)(struct _DEMUX_DEVICE_S* pstDev, DMX_CAPABILITY_S* const pstCapability);

    /**
     \brief Get demux status. CNcomment:获取demux状态 CNend
     \attention \n
    CNcomment:有些平台通道/过滤器/解扰器在多demux_id间共享，获取的将是总数 CNend
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \param[out] pstStatus demux status.CNcomment:Demux状态 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_STATUS_S
     */
    S32 (*dmx_get_status)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, DMX_STATUS_S* const pstStatus);

    /**
     \brief Open a demux. CNcomment:开启一个数据通道。 CNend
     \attention \n
    CNcomment:open后处于disable状态. open 的时候可以传入非法的pid,以后在通过dmx_channel_set_pid()来设置. CNend
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \param[out] pu32ChannelId demux channel id.CNcomment:Demux通道ID CNend
     \param[in] pstOpenParams demux open params.CNcomment:Demux打开参数 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_CHANNEL_OPEN_PARAM_S
     */
    S32 (*dmx_channel_open)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32ChannelId, const DMX_CHANNEL_OPEN_PARAM_S* const pstOpenParams);

    /**
     \brief Close a demux. CNcomment:关闭一个数据通道，并释放相关资源。 CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:Demux通道ID CNend
     \param[in] pstCloseParams demux close params.CNcomment:Demux关闭参数 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_CHANNEL_CLOSE_PARAMS_S
     */
    S32 (*dmx_channel_close)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_CHANNEL_CLOSE_PARAMS_S* pstCloseParams );

    /**
     \brief Set channel pid. CNcomment:设置数据通道PID。 CNend
     \attention \n
    CNcomment:如果(u16Pid==INVALID_PID)如果平台支持,请clear该通道的pid. 如果pid 参数大于 INVALID_PID, HDI 需要修正为INVALID_PID. CNend
     \param[in] u32ChannelId demux channel id.CNcomment:Demux通道ID CNend
     \param[in] u16Pid demux pid.CNcomment:Demux PID CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_channel_set_pid)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U16 u16Pid);

    /**
     \brief Search channel pid. CNcomment:查询是否有设置该PID的通道CNend
     \attention \n
     \param[in] enDemuxId demux  id.CNcomment:哪个demux上 CNend
     \param[out] pu32ChannelId Channel id pointer .CNcomment:该PID对应的通道ID CNend
     \param[in] u16Pid recevie data pid.CNcomment: 要接收数据的PID CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_ID_E
     */

    S32 (*dmx_channel_query)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32ChannelId, const U16 u16Pid);

    /**
     \brief open a demux. CNcomment:开启数据通道开始接收数据。 CNend
     \attention \n
    CNcomment: channel enable 的时候, 在该channel 上开的所有的filter 都enable. CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_channel_enable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId );

    /**
     \brief stop demux recevie data. CNcomment:停止数据通道接收数据。 CNend
     \attention \n
    CNcomment: channel disable 的时候, 在该channel 上开的所有的filter 都disable. CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_channel_disable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId);

    /**
     \brief reset a demux. CNcomment:复位数据通道 CNend
     \attention \n
    CNcomment:  复位后处于disable状态. CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_channel_reset)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId );

    /**
     \brief get demux channel info. CNcomment:获取数据通道信息 CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[out] pstInfo info pointer.CNcomment:数据通道信息CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_CHANNEL_INFO_S
     */
    S32 (*dmx_channel_get_info)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, DMX_CHANNEL_INFO_S* const pstInfo);

    /**
     \brief set demux channel param. CNcomment:设置通道参数 CNend
     \attention \n
     CNcomment: 注意,修改channel参数时,请先get出来,修改需要修改的成员再set回去
     set函数里面对于没有改变的成员不做修改CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] pstSettings settings pointer.CNcomment: 配置 指针 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_CHANNEL_SETTING_S
     */
    S32 (*dmx_channel_set)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_CHANNEL_SETTING_S* const pstSettings);

    /**
     \brief get demux channel. CNcomment:获取通道的配置CNend
     \attention \n
    CNcomment: 注意,修改channel参数时,请先get出来,修改需要修改的成员再set回去
    set函数里面对于没有改变的成员不做修改CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[out] pstSettings settings pointer.CNcomment: 配置 指针 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_CHANNEL_SETTING_S
     */
    S32 (*dmx_channel_get)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, DMX_CHANNEL_SETTING_S* const pstSettings);

#ifdef HAL_HISI_EXTEND_H
    /**
    \brief Obtains the handles of all channels that receive new data.CNcomment:获取有新数据到达的所有通道的句柄。CNend
    \attention \n
    When you call this API, the parameter pu32ChNum serves as the input parameter and is used to specify the data length pointed by pu32ChannelId. pu32ChNum indicates the number of channels to be queried.\n
    The number of channels must be initialized, and the initial value cannot be 0.\n
    It is recommended to set the number of channels to the total number. For details about the total number of channels.\n
    After you call this API successfully, the parameter pu32ChNum serves as the output parameter and is used to specify the valid data length pointed by phChannel.\n
    The block time is configurable (in ms). If u32TimeOutMs is set to 0, it indicates that the block time is 0; if u32TimeOutMs is set to 0xFFFFFFFF, it indicates infinite wait.\n
    CNcomment:调用该接口时，pu32ChNum作为输入参数，用于指定pu32ChannelId指向数组的长度，表示要查询的通道个数；\n
    通道个数必须初始化，且初始值必须为非0值\n
    建议将通道个数设置为通道的总个数\n
    当该接口调用成功时，pu32ChNum作为输出参数，指定pu32ChannelId指向数组的有效长度\n
    阻塞时间可以设置，时间单位为毫秒，设置为0不等待，设置为0xffffffff一直等待。CNend
    \param[out] pu32ChannelId  Pointer to the number of channels. The number of channels depends on the value of pu32ChNum.CNcomment:指针类型，指向通道句柄数组。数组长度有pu32ChNum决定。CNend
    \param[in] pu32ChNum Pointer type
                               Input: indicates the number of channel handles to which pChannelHandle points.
                               Output: indicates the number of lower-layer channels that receive new data. The maximum value cannot be greater than the input value.
                               CNcomment: 指针类型。注意:该参数同时作为输入和输出。CNend
                               CNcomment: 输入：pChannelHandle指向数组的长度。CNend
                               CNcomment: 输出：底层有新数据通道的数目；最多不超过输入的数值。CNend
    \param[in] u32TimeOutMs      Wait timeout, in ms.CNcomment:等待超时时间，单位ms。CNend
    \retval ::HI_SUCCESS Success.CNcomment:成功。CNend
    \retval ::HI_FAILURE  Calling this API fails.CNcomment:API系统调用失败。CNend
    \see \n
     N/A.CNcomment:无。CNend
    */
    S32 (*dmx_channel_get_data_handle)(struct _DEMUX_DEVICE_S* pstDev, U32* pu32ChannelId, U32* pu32ChNum, const U32 u32TimeoutMs);
#endif

    /**
     \brief get a demux channel buffer. CNcomment:获取指定数据通道的数据CNend
     \attention \n
    CNcomment:  该函数为同步函数，等待直到得到数据或者超时返回。
    对于section通道和ECM/EMM通道，每个数据包包含一个完整的section
    对于PES通道，每个数据包尽量包含完整的pes，但是如果pes太大，可能要分多个pes包输出，
    输出的数据是否完整通过数据包结构的enDataType字段指定
    对于POST类型的通道，每个数据包包含一个或多个完整的TS包，TS包长188字节
    对于音视频通道是不能通过此接口获取数据的，音视频数据会通过内部接口直接送给解码器进行解码
    不允许重复调用此接口，可以一次请求多次释放，但是释放必须按顺序，而且释放的地址和长度必须和请求的一致
    并且只有释放完所有的数据包才能再次请求，否则返回重复请求错误码。CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] u32AcquirePackageNum expect acquire package number.CNcomment: 期望获取数据的总包数 CNend
     \param[out] pu32AcquiredNum acquire package number.CNcomment:实际获取数据的总包数，小于等于acquire_package_numCNend
     \param[out] pstChannelData obtained data.CNcomment: 获取到的数据及说明 CNend
     \param[in] u32TimeoutMs waiting time.CNcomment: 等待时间,除了一般的等待时间外,支持无限超时和立即超时两个特殊等待时间 CNend
     \retval
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_DMX_GETBUF_TIMEOUT time out.CNcomment:超时。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_CHANNEL_DATA_S
     */
    S32 (*dmx_channel_get_buf)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32 u32AcquirePackageNum, U32* pu32AcquiredNum, DMX_CHANNEL_DATA_S* pstChannelData, const U32 u32TimeoutMs );

    /**
     \brief release demux channel buffer. CNcomment:释放数据包占用的缓冲空间CNend
     \attention \n
    CNcomment: 本接口释放的缓冲区一定是通过dmx_channel_get_buf获取的缓冲区，缓冲区的地址和长度不能更改
    释放的缓冲区个数可以小于获取的缓冲区个数CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] u32ReleaseNum release package number .CNcomment:释放数据包个数CNend
     \param[in] pstChannelData a pointer pointing to release buffer.CNcomment:指针类型，指向释放缓冲区信息数组，长度由release_num决定CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_CHANNEL_DATA_S
     */
    S32 (*dmx_channel_release_buf)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32 u32ReleaseNum, DMX_CHANNEL_DATA_S* pstChannelData);

    /**
     \brief register callback . CNcomment:注册回调函数CNend
     \attention \n
    CNcomment:  回调函数和通道 绑定,  一个通道最多可以注册DMX_CHANNEL_CALLBACK_MAX 个回调函数CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] pstReg register parameter configuration pointer.CNcomment:   注册参数配置结构指针 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_REG_CALLBACK_PARAMS_S
     */
    S32 (*dmx_channel_register_callback)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_REG_CALLBACK_PARAMS_S* const pstReg);

    /**
     \brief config demux channel callback. CNcomment:配置对应数据通道的回调函数。CNend
     \attention \n
    CNcomment: 回调函数和通道 绑定,一个通道最多可以注册DMX_CHANNEL_CALLBACK_MAX 个回调函数,
    如果pfnCallback==NULL表示对该channel所有的回调函数有效CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] pfnCallback point to the callback need to config CNcomment:指明需要配置的回调函数 CNend
     \param[in] parameters of config CNcomment:配置参数 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_CALLBACK_PFN, DMX_CALLBACK_PFN
     */
    S32 (*dmx_channel_config_callback)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_CALLBACK_PFN pfnCallback, const DMX_CFG_CALLBACK_E enCfg);

    /**
     \brief add filter and set it. CNcomment:为数据通道分配过滤器，并设置过滤数据。CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] pu32FilterId return filter id CNcomment:返回分配的过滤器ID；CNend
     \param[in] pstFilterData filter data pointer CNcomment:过滤器数据指针CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_FILTER_DATA_S
     */
    S32 (*dmx_channel_add_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32* const pu32FilterId, const DMX_FILTER_DATA_S* const pstFilterData);

    /**
     \brief set filters. CNcomment:设置过滤器的过滤条件。CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] u32FilterId  filter id CNcomment:过滤器ID；CNend
     \param[in] pstFilterData filter data pointer CNcomment:过滤器数据指针CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_FILTER_DATA_S
     */
    S32 (*dmx_channel_set_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId, const DMX_FILTER_DATA_S* const pstFilterData);

    /**
     \brief get filters. CNcomment:获取过滤器的过滤条件。CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] u32FilterId  filter id CNcomment:过滤器ID；CNend
     \param[out] pstFilterData filter data pointer CNcomment:过滤器数据指, 如果buffer 空间不足(长度或指针),返回失败CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    :: DMX_FILTER_DATA_S
     */
    S32 (*dmx_channel_get_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId, DMX_FILTER_DATA_S* const pstFilterData);

    /**
     \brief close filters. CNcomment:关闭过滤器。CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] u32FilterId  filter id CNcomment:过滤器ID；CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_channel_destroy_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId);

    /**
     \brief close all filters. CNcomment:关闭指定数据通道的所有过滤器。CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_channel_destroy_all_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId );

    /**
     \brief enable filter. CNcomment:开启数据通道的指定过滤器开始接收数据。CNend
     \attention \n
    CNcomment: 一般在一个数据通道存在多个过滤器的情况下使用CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] u32FilterId  filter id CNcomment:过滤器ID；CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_channel_enable_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId );

    /**
     \brief disable filter. CNcomment:禁止数据通道中的指定过滤器。CNend
     \attention \n
    CNcomment:一般在一个数据通道存在多个过滤器的情况下使用。CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[in] u32FilterId  filter id CNcomment:过滤器ID；CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_channel_disable_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId);

    /**
     \brief query filter by table id
    CNcomment:channel的filter是否存在某个table id 和ext id的filter 。CNend
     \attention \n
    CNcomment:u8TableId 和u16ExtId 必须严格匹配,过滤器条件长度为0的不会被匹配 CNend
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[out] pu32FilterId  filter id pointer  CNcomment:返回符合条件的过滤器ID，INVALID_ID 表示没有CNend
     \param[in] u8TableId table id CNcomment:table ID CNend
     \param[in] u16ExtId table extend id CNcomment: table extend ID CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_channel_query_filter_by_table_id)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32* const pu32FilterId, const U8 u8TableId, const U16 u16ExtId);

    /**
     \brief query filter by filter data. CNcomment:channel的filter是否存在相同的过滤条件。CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:数据通道ID CNend
     \param[out] pu32FilterId  filter id pointer  CNcomment:返回符合条件的过滤器ID，INVALID_ID 表示没有CNend
     \param[in] pstFilterData filter data pointer CNcomment:过滤器数据指针CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_FILTER_DATA_S
     */
    S32 (*dmx_channel_query_filter_by_filter_data)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32* const pu32FilterId, const DMX_FILTER_DATA_S* const pstFilterData);

    /**
     \brief open descrambler. CNcomment:分配一个解扰通道。CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:解复用器ID CNend
     \param[out] pu32DescId  descrambler id pointer. CNcomment:解扰通道ID 指针CNend
     \param[in] enMode see DMX_DESC_ASSOCIATE_MODE_E CNcomment:see DMX_DESC_ASSOCIATE_MODE_E CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_DESC_ASSOCIATE_MODE_E
     */
    S32 (*dmx_descrambler_open)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32DescId, const DMX_DESC_ASSOCIATE_MODE_E enMode);

    /**
     \brief allocate descrambler expansion interface . CNcomment:分配一个解扰通道扩展接口.CNend
     \attention \n
    CNcomment:有些平台,当ca接受到的cw字是密文的话,需要打开 DMX_CA_ADVANCE_DESCRAMBLER属性的descrambler,
     如果接受到的cw是明文的话需要打开一个DMX_CA_NORMAL_DESCRAMBLER属性的descrambler CNend
     \param[in] enDemuxId demux id.CNcomment:解复用器ID CNend
     \param[out] pu32DescId  descrambler id pointer. CNcomment:解扰通道ID 指针CNend
     \param[in] pstDesramblerAttr  descrambler attribute. CNcomment:解扰器属性设置CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_DESC_ASSOCIATE_MODE_E, DMX_DESCRAMBLER_TYPE_E
     */

    S32 (*dmx_descrambler_open_ex)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32DescId, const DMX_DESCRAMBLER_ATTR_S* pstDesramblerAttr);

    /**
     \brief enable a descrambler. CNcomment:enable 一个解扰通道。CNend
     \attention \n
    CNcomment:解扰器关联之前,不能enable. CNend
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_descrambler_enable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId );

    /**
     \brief disable a descrambler. CNcomment:disable 一个解扰通道.CNend
     \attention \n
    CNcomment:see dmx_opendescrambler. CNend
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_descrambler_disable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId );

    /**
     \brief close a descrambler. CNcomment:关闭 一个解扰通道. CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_descrambler_close)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId );

    /**
     \brief associate descrambler. CNcomment:关联解扰器和需要解扰PID或者通道. CNend
     \attention \n
    CNcomment:是pid还是channel由p_params->m_mode决定
    当p_params->m_mode==DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDS时,  如果m_pid==INVALID_PID, 则取消当前的关联(Disassociate)
    否则是需要进行关联
    当p_params->m_mode==DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNEL时,  如果m_channel_id==DMX_INVALID_PID, 则取消当前的关联(Disassociate)
    否则是需要进行关联.
    如果是PID关联, 当PID通道还没有OPEN,允许关联,并返回成功.(CA 和AV 异步调用的需求.)    CNend
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[in] pstParams associate param pointer.CNcomment: 关联参数指针.  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_DESC_ASSOCIATE_PARAMS_S
     */
    S32 (*dmx_descrambler_associate)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DESC_ASSOCIATE_PARAMS_S* const pstParams );

    /**
     \brief get associate info. CNcomment:获取解扰器关联的解扰PID或者通道. CNend
     \attention \n
    CNcomment: 当解扰器没有关联时,    如果p_params->m_mode==DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDS则m_pid=DMX_INVALID_PID
    如果p_params->m_mode==DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNEL则m_channel_id=DMX_INVALID_CHN_ID  CNend
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[out] pstParams associate param pointer.CNcomment: 关联参数指针.  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_DESC_ASSOCIATE_PARAMS_S
     */
    S32 (*dmx_descrambler_get_associate_info)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, DMX_DESC_ASSOCIATE_PARAMS_S* const pstParams);

    /**
     \brief set even key for descrambler. CNcomment:设置解扰通道的偶密钥。CNend
     \attention \n
     CNcomment:解扰器关联之前,不能set key. CNend
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[in] pu8Key pointing to the key .CNcomment:指向包含密钥的指针.  CNend
     \param[in] u32Len the lenth of key.:密钥长度.  CNend
     \param[in] u32Option retention param.CNcomment:保留参数.  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_descrambler_set_even_key)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8Key, const U32 u32Len, const U32 u32Option );

    /**
     \brief set even key iv for descrambler. CNcomment:设置解扰通道的偶密钥对应数据的初始向量。CNend
     \attention \n
     CNcomment: 无. CNend
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[in] pu8IV pointing to the IV .CNcomment:指向初始向量的指针.  CNend
     \param[in] u32Len the lenth of IV. CNcomment:向量长度.  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_descrambler_set_even_iv)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8IV, const U32 u32Len);

    /**
     \brief set odd key for descrambler. CNcomment:设置解扰通道的奇密钥。CNend
     \attention \n
     CNcomment:解扰器关联之前,不能set key. CNend
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[in] pu8Key pointing to the key .CNcomment:指向包含密钥的指针.  CNend
     \param[in] u32Len the lenth of key.:密钥长度.  CNend
     \param[in] u32Option retention param.CNcomment:保留参数.  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_descrambler_set_odd_key)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8Key, const U32 u32Len, const U32 u32Option );

    /**
     \brief set even key iv for descrambler. CNcomment:设置解扰通道的奇密钥对应数据的初始向量。CNend
     \attention \n
     CNcomment: 无. CNend
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[in] pu8IV pointing to the IV .CNcomment:指向初始向量的指针.  CNend
     \param[in] u32Len the lenth of IV. CNcomment:向量长度.  CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_descrambler_set_odd_iv)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8IV, const U32 u32Len);

    /**
     \brief set descrambler attribute. CNcomment:设置 解扰通道属性。CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[in] pstAttr descrambler attribute.CNcomment:解扰通道属性 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_set_descrambler_attribute)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, DMX_DESCRAMBLER_ATTR_S* pstAttr );

    /**
     \brief get descrambler attribute. CNcomment:获取解扰通道属性。CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[out] pstAttr descrambler attribute pointer.CNcomment:解扰通道属性结构体指针 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_get_descrambler_attribute)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, DMX_DESCRAMBLER_ATTR_S* pstAttr );

    /**
     \brief set dcas keyladder TS descrambling parameters. CNcomment设置DCAS keyladder TS流解扰参数。CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[in] pstDcasKLConfig DCAS keyladder config pointer.CNcomment:DCAS keyladder配置结构体指针 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */

    S32 (*dmx_dcas_keyladder_config)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DCAS_KEYLADDER_SETTING_S* pstDcasKLConfig);

    /**
     \brief get DA(nonce). CNcomment获取DA(nonce)。CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:解扰通道ID.  CNend
     \param[in] pstDcasNonceConfig DCAS keyladder nonce config pointer.CNcomment:DCAS keyladder Nonce配置结构体指针 CNend
     \param[out] pu8DANonce DA(nonce) result. CNcomment:DA(nonce)输出结果 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */

    S32 (*dmx_dcas_get_nonce)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DCAS_NONCE_SETTING_S* pstDcasNonceConfig, U8* pu8DANonce);

    /**
     \brief Open an filter. CNcomment:打开一个过滤器，用来过滤音视频数据 CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] pstFilterOpenPara open param.CNcomment:打开参数 CNend
     \param[out] pu32AVFilterId av filter id .CNcomment:过滤器句柄 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_PARSER_FILTER_OPEN_PARAM_S
     */
    S32 (*dmx_avfilter_open)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32AVFilterId, const DMX_PARSER_FILTER_OPEN_PARAM_S* const pstFilterOpenPara);

    /**
     \brief Enable demux av filter. CNcomment:使能av过滤器 CNend
     \attention \n
     \param[in] pu32AVFilterId av filter id.CNcomment:过滤器句柄 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_avfilter_enable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId);

    /**
     \brief Get part of es frame. CNcomment:获取帧数据部分。CNend
     \attention \n
     Got data maybe not a whole frame. CNcomment:获取到的数据可能不是完整的帧数据 CNend
     \param[in] pu32AVFilterId av filter id .CNcomment:过滤器句柄 CNend
     \param[out] pstFrameInfo point to es frame data.CNcomment:获取到的帧数据指针 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_ESFRAME_INFO_S
     */
    S32 (*dmx_avfilter_get_esframe)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId, DMX_ESFRAME_INFO_S* pstFrameInfo);

    /**
     \brief Release es frame. CNcomment:释放帧数据。CNend
     \attention \n
        If you release buffers by calling this API, the buffers must be those obtained by calling ::dmx_avfilter_get_esframe, and the addresses and sizes of these buffers cannot be changed.\n
        CNcomment:本接口释放的缓冲区一定是通过::dmx_avfilter_get_esframe获取的缓冲区，缓冲区的地址和长度不能更改CNend
     \param[in] pu32AVFilterId av filter id .CNcomment:过滤器句柄 CNend
     \param[in] pstFrameInfo point to es frame data.CNcomment:帧数据指针 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::DMX_DESC_TYPE_E
     */
    S32 (*dmx_avfilter_release_esframe)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId, DMX_ESFRAME_INFO_S* pstFrameInfo);

    /**
     \brief Disable demux av filter. CNcomment:去使能av过滤器 CNend
     \attention \n
     \param[in] pu32AVFilterId av filter id. CNcomment:过滤器句柄 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_avfilter_disable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId);

    /**
     \brief Close an filter. CNcomment:关闭一个过滤器，用来过滤音视频数据 CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] pu32AVFilterId av filter id .CNcomment:过滤器句柄 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_avfilter_close)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId);

    /**
     \brief Open a pcr channel. CNcomment:打开一个pcr通道 CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] u32Pid PCR PID .CNcomment:PCR通道PID CNend
     \param[out] pu32PcrId  id .CNcomment:句柄 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_pcr_open)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32PcrId, const U32 u32Pid);

    /**
     \brief Close a pcr channel. CNcomment:关闭一个pcr通道 CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] u32PcrId  id .CNcomment:句柄 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_pcr_close)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32PcrId);

    /**
     \brief Get pcr. CNcomment:获取pcr CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] u32PcrId  id .CNcomment:句柄 CNend
     \param[out] pu64StcTime  Stc time .CNcomment:Stc时间 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_pcr_get)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32PcrId, U64* pu64StcTime);

    /**
     \brief Creates a TS buffer for the RAM port to receive the TS data from Internet or local memory.
      CNcomment:为RAM端口创建TS Buffer用于接收从网络或本地存储中输入的TS数据。CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[out] pu32TsBufferId ts buffer id .CNcomment:TS缓存句柄 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_tsbuffer_create)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32TsBufferId);

    /**
     \brief Obtains a TS buffer to input data.CNcomment:获取TS Buffer空间，用于数据输入。CNend
     \attention \n
    If you call this API repeatedly, the address of the same buffer is returned.\n
    The input data length must be appropriate. If the data length is too large, data cannot be input in time.\n
    If the data length is too small, the buffer is scheduled frequently, which causes the system performance to deteriorate.\n
    If the size of the available space is smaller than the requested data length, an error code is returned.\n
    To be specific, the requested data length must be smaller than the size of the available space, that is, the buffer cannot be full.\n
    In addition, the requested data length cannot be 0; otherwise, the error code HI_ERR_DMX_INVALID_PARA is returned.\n
    If u32TimeOutMs is set to 0, it indicates that the waiting time is 0; if u32TimeOutMs is set to 0XFFFFFFFF, it indicates infinite wait; if u32TimeOutMs is set to other values, it indicates that the waiting time is u32TimeOutMs ms.\n
    If no buffer can be applied for during the block period, the error code HI_ERR_DMX_TIMEOUT is returned.\n
    If u32TimeOutMs is set to 0, and no buffer can be applied for, it indicates that the internal TS buffer is full. In this case, you need to call the usleep(10000) function to release the CPU. Therefore, other threads can be scheduled.
    CNcomment:重复get返回同一个buffer地址\n
    输入数据时注意每次输入的数据长度，太长可能会导致输入数据不及时\n
    太短可能会导致调度太频繁，性能下降\n
    当剩余空间小于等于请求的长度时，返回错误码\n
    每次申请的长度要小于剩余剩余长度，即buffer不可能被填满\n
    请求长度不允许为0，否则返回参数非法错误码\n
    u32TimeoutMs设置为0表示不等待，设置为0xffffffff表示一直等待，设置为其他值表示等待u32TimeoutMs毫秒。\n
    若超过阻塞时间，还无法申请到Buffer，则返回ERROR_DMX_TIMEOUT错误码\n
    u32TimeoutMs配置为0时，如果申请不到Buffer，说明此时内部TS Buffer空间已满，需要通过usleep(10000)释放cpu
    以使其它线程能够得到调度。CNend
    \param[in] u32TsBufferId Handle of a TS buffer.CNcomment:TS Buffer句柄。CNend
    \param[in] u32Size Requested data length.CNcomment:请求数据的长度。CNend
    \param[in] u32TimeoutMs      Wait timeout, in ms.CNcomment:等待超时时间，单位ms。CNend
    \param[out] pstStreamData  Data buffer.CNcomment:数据buffer结构。CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_tsbuffer_get)(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId, U32 u32Size, U32 u32TimeoutMs, DMX_STREAM_DATA_S* pstStreamData);

    /**
     \brief Updates the write pointer of a TS buffer after the TS data is input.CNcomment:TS数据输入完毕，用于更新TS Buffer写指针。CNend
     \attention \n
    This API must work with dmx_tsbuffer_get. That is, if you call dmx_tsbuffer_put without calling dmx_tsbuffer_get, no operation takes effect, but the error code SUCCESS is returned.\n
    If the valid data length is 0, no operation takes effect, and the error code SUCCESS.\n
    The valid data length cannot be greater than data length queried by calling dmx_tsbuffer_get. Otherwise, the error code HI_ERR_DMX_INVALID_PARA is returned.\n
    If the valid data length is smaller than the data length queried by calling dmx_tsbuffer_get, it indicates that a part of data is stored.
    CNcomment:此接口必须和Get接口配对使用，如果没有Get则进行Put操作，则不会进行任何操作，但返回成功\n
    Put的长度如果为0，也不会进行任何操作直接返回成功\n
    不允许Put长度大于实际Get到的长度，否则返回参数非法错误码\n
    允许Put长度小于Get长度，表明只输入了一部分数据\n
    为提高效率，Put的长度尽量不要太短，尽量保持在10个ts包以上Put一次，数据太短会导致性能下降\n。CNend
    \param[in] u32TsBufferId Handle of a TS buffer.CNcomment:TS Buffer句柄。CNend
    \param[in] u32ValidDataLen Valid data length.CNcomment:有效数据的长度。CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_tsbuffer_put)(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId, U32 u32ValidDataLen);

    /**
    \brief Destroys an existing TS buffer. CNcomment:销毁创建的TS Buffer。CNend
     \attention \n
    A TS buffer cannot be destroyed repeatedly. If a TS buffer is destroyed, its handle is also destroyed.\n
    In addition, if a buffer is destroyed, its data is cleared. In this case, the get and put operations are not available.\n
    However, the data in channels is retained when a TS buffer is destroyed. To switch streams, you need disable the channel, and then enable the channel again.
    CNcomment:不能重复销毁一个TS Buffer,销毁之后handle就不存在了\n
    销毁之后buffer中的数据就会被清空，不能再进行Get和Put操作\n
    销毁TS buffer并不能清空通道中数据，要切换码流，要注意关闭通道，重新打开。CNend
    \param[in] u32TsBufferId Handle of a TS buffer.CNcomment:TS Buffer句柄。CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
     */
    S32 (*dmx_tsbuffer_destroy)(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId);

#ifdef HAL_HISI_EXTEND_H
    /**
    \brief Creates a TS buffer for the RAM port to receive the TS data from Internet or local memory. CNcomment:为RAM端口创建TS Buffer用于接收从网络或本地存储中输入的TS数据CNend
    \attention \n
    A TS buffer can be created for the RAM port only.\n
    The TS buffer cannot be created for the same port for multiple times; otherwise, an error code is returned.
    CNcomment:只有RAM 端口可以创建TS Buffer\n
    同一端口不能重复创建TS Buffer，否则返回错误 CNend
    \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
    \param[in] pstBufAttr Attributes of a TS buffer.CNcomment:TS Buffer创建属性CNend
    \param[out] pu32TsBufferId ts buffer id .CNcomment:TS缓存句柄 CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    */
    S32 (*dmx_tsbuffer_create_ex)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, DMX_TSBUF_ATTR_S* pstBufAttr, U32* const pu32TsBufferId);

    /**
    \brief Obtains a TS buffer to input data.CNcomment:获取TS Buffer空间，用于数据输入。CNend
    \attention \n
    If you call this API repeatedly, the address of the same buffer is returned.\n
    The input data length must be appropriate. If the data length is too large, data cannot be input in time.\n
    If the data length is too small, the buffer is scheduled frequently, which causes the system performance to deteriorate.\n
    If the size of the available space is smaller than the requested data length, an error code is returned.\n
    To be specific, the requested data length must be smaller than the size of the available space, that is, the buffer cannot be full.\n
    In addition, the requested data length cannot be 0; otherwise, the error code HI_ERR_DMX_INVALID_PARA is returned.\n
    If u32TimeOutMs is set to 0, it indicates that the waiting time is 0; if u32TimeOutMs is set to 0XFFFFFFFF, it indicates infinite wait; if u32TimeOutMs is set to other values, it indicates that the waiting time is u32TimeOutMs ms.\n
    If no buffer can be applied for during the block period, the error code HI_ERR_DMX_TIMEOUT is returned.\n
    If u32TimeOutMs is set to 0, and no buffer can be applied for, it indicates that the internal TS buffer is full. In this case, you need to call the usleep(10000) function to release the CPU. Therefore, other threads can be scheduled.
    CNcomment:重复get返回同一个buffer地址\n
    输入数据时注意每次输入的数据长度，太长可能会导致输入数据不及时\n
    太短可能会导致调度太频繁，性能下降\n
    当剩余空间小于等于请求的长度时，返回错误码\n
    每次申请的长度要小于剩余剩余长度，即buffer不可能被填满\n
    请求长度不允许为0，否则返回参数非法错误码\n
    u32TimeoutMs设置为0表示不等待，设置为0xffffffff表示一直等待，设置为其他值表示等待u32TimeoutMs毫秒。\n
    若超过阻塞时间，还无法申请到Buffer，则返回ERROR_DMX_TIMEOUT错误码\n
    u32TimeoutMs配置为0时，如果申请不到Buffer，说明此时内部TS Buffer空间已满，需要通过usleep(10000)释放cpu
    以使其它线程能够得到调度。CNend
    \param[in] u32TsBufferId Handle of a TS buffer.CNcomment:TS Buffer句柄。CNend
    \param[in] u32Size Requested data length.CNcomment:请求数据的长度。CNend
    \param[in] u32TimeoutMs      Wait timeout, in ms.CNcomment:等待超时时间，单位ms。CNend
    \param[out] pstStreamData  Data buffer.CNcomment:数据buffer结构。CNend
    \param[out] pu32PhyAddr  buffer physical address.CNcomment:buffer的物理地址。CNend
     \retval ::SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    */
    S32 (*dmx_tsbuffer_get_ex)(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId, U32 u32Size, U32 u32TimeoutMs, DMX_STREAM_DATA_S* pstStreamData, U32 *pu32PhyAddr);
#endif

    /**
    \brief get TEE keyladder streampath . CNcomment:获取在TEE侧设置keyladder所需要的streampath参数。CNend
     \attention \n
    TEE attach descrambler, requires REE side to provide streampath information.
    CNcomment:TEE侧需要REE传streampath信息才能绑定解扰器。CNend
    \param[in] enDemuxId Demux id.CNcomment:demux ID。CNend
    \param[out] pstStreamData  streampath data, bytes stream.CNcomment:streampath数据，字节流。CNend
    \param[out] pStreamPathLength  streampath data length.CNcomment:streampath数据长度。CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX设备操作错误。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    */
    S32 (*dmx_get_streampath_param)(struct _DEMUX_DEVICE_S *pstDev, DMX_ID_E enDemuxId, UCHAR  *pStreamPath, S32 *pStreamPathLength);
} DEMUX_DEVICE_S;


/**
\brief direct get demux device api, for linux and android.CNcomment:获取demux设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get demux device api，for linux and andorid.
CNcomment:获取demux设备，linux和android平台都可以使用. CNend
\retval  demux device pointer when success.CNcomment:成功返回demux设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::DEMUX_DEVICE_S

\par example
*/
DEMUX_DEVICE_S *getDemuxDevice();

/**
\brief Open HAL demux module device.CNcomment: 打开HAL解复用模块设备 CNend
\attention \n
Open HAL demux module device( for compatible android HAL).
CNcomment: 打开HAL解复用模块设备(for compatible Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice demux device structure.CNcomment:demux设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::DEMUX_DEVICE_S

\par example
*/
static inline int demux_open(const struct hw_module_t* pstModule, DEMUX_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, DEMUX_HARDWARE_DEMUX0, (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getDemuxDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL demux module device.CNcomment:关闭HAL解复用模块设备 CNend
\attention \n
Close HAL demux module device(for compatible Android HAL).
CNcomment:关闭HAL解复用模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice demux device structure.CNcomment:demux设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::DEMUX_DEVICE_S

\par example
*/
static inline int demux_close(DEMUX_DEVICE_S* pstDevice)
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

#endif /* __TVOS_HAL_DMX_H__ */
