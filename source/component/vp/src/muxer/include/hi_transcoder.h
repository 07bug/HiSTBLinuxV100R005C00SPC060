
/**
 * \file hi_transcoder.h
 * \brief Describes the information about HiSilicion Transcoder trans module (HiTran).
*/

#ifndef __HI_TRANSCODER_H__
#define __HI_TRANSCODER_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/
/** \addtogroup      HiTran */
/** @{ */  /** <!—[HiTran]*/

/**software platform define*//** CNcomment:获取软件平台 */
#ifdef ANDROID_TOOLCHAIN
#define SOFT_BOARD_VERSION_ANDROID
#else
#define SOFT_BOARD_VERSION_LINUX
#endif

/** @} */  /*! <!-- Macro Definition End */


/*************************** Structure Definition ****************************/
/** \addtogroup      HiTran */
/** @{*/  /** <!—[HiTran]*/

/**transcoder media data type*//** CNcomment:读取帧数据类型 */
typedef enum eTran_PAYLOAD
{
    PAYLOAD_VIDEO_NORMAL_FRAME = 1,
    PAYLOAD_VIDEO_KEY_FRAME , //视频关键帧
    PAYLOAD_VIDEO_VPS_FRAME ,
    PAYLOAD_VIDEO_SPS_FRAME ,
    PAYLOAD_VIDEO_PPS_FRAME,
    PAYLOAD_AUDIO_FRAME = 10, //音频帧
    PAYLOAD_MD_FRAME, //MD数据
    PAYLOAD_BUTT
} TRANSCODER_PAYLOAD_E;

/**transcoder video/audio type*//** CNcomment:转码模块转码音视频类型 */
typedef enum eTran_MediaCodec
{
    TRANSCODER_CODEC_ID_H264 = 0,
    TRANSCODER_CODEC_ID_H265,
    TRANSCODER_CODEC_ID_H263,
    TRANSCODER_CODEC_ID_MPEG4,
    TRANSCODER_CODEC_ID_AACLC,
    TRANSCODER_CODEC_ID_AMRNB,
    TRANSCODER_CODEC_ID_G711A,
    TRANSCODER_CODEC_ID_NONE,
    TRANSCODER_CODEC_ID_BUTT
} Transcoder_MediaCodec;

/**transcoder attribute set of diff type*//** CNcomment:转码模块各类型属性集*/
typedef enum eTran_Attr_ID_E
{
    TRANSCODER_ALL_ATTR,
    TRANSCODER_VIDEO_ATTR,
    TRANSCODER_AUDIO_ATTR,
    TRANSCODER_BACKGND_ATTR,
    TRANSCODER_ATTR_BUTT
} Transcoder_Attr_ID_E;

/**transcoder source type*//** CNcomment:转码模块数据源类型*/
typedef enum eTran_Src_Type_E
{
    TRANSCODER_SOURCE_AVPLAY,
    TRANSCODER_SOURCE_OSD_VO_PCM,
    TRANSCODER_SOURCE_BUTT
} Transcoder_Src_Type_E;

typedef struct tagTran_VencStream
{
    HI_U8* pu8Addr;       /**<Stream virtual address*/ /**<CNcomment: 码流虚拟地址*/
    HI_U32 u32SlcLen;      /**<Stream length*/ /**<CNcomment: 码流长度*/
    HI_U32 u32PtsMs;        /**<Presentation time stamp (PTS), in ms*/ /**<CNcomment: 时间戳，单位是毫秒*/
} TRANSCODER_VENC_STREAM;

typedef struct tagTran_AencStream
{
    HI_U8* pu8Buf;    /**<User-state virtual address of the buffer*/ /**<CNcomment: buffer的用户态虚地址*/
    HI_U32 u32BufLen;  /**<Buffer length*/ /**<CNcomment: buffer的长度*/
    HI_U32 u32PtsMs;   /**<Presentation time stamp (PTS) value corresponding to the start of the stream. The invalid value is 0xFFFFFFFF.*/
    /**<CNcomment: 码流开始处对应的PTS值，无效为0xffffffff*/
} TRANSCODER_AENC_STREAM;

/**media data payload data structure*//** CNcomment:媒体数据payLoad数据类型*/
typedef union tagTran_StreamDataType
{
    TRANSCODER_VENC_STREAM stVencStream;  /**<video stream encoded data *//**<CNcomment:视频流编码数据 */
    TRANSCODER_AENC_STREAM stAencStream;            /**<audio stream encoded data *//**<CNcomment:音频流编码数据 */
} TRANSCODER_DATA_TYPE_U;

/**transcoder data frame structure*//** CNcomment:媒体数据帧结构*/
typedef struct tagTran_STREAM_S
{
    TRANSCODER_PAYLOAD_E ePayloadType;  /**<stream payload type *//**<CNcomment:PayLoad数据类型 */
    TRANSCODER_DATA_TYPE_U  enDataStream;             /**<stream data *//**<CNcomment:媒体流数据*/
} TRANSCODER_STRAM;


/**supply for user callback function, modified by user, set by source module*/
/** CNcomment:提供给用户的指令回调接口，根据不同的指令，设置属性后传入源端模块，
由源端模块确定其相应方式，如为后台转码，此函数会由 Transcoder实现*/
typedef HI_S32 (*HI_TRANSCODER_NODIFY_CALLBACK)(HI_HANDLE Handle, HI_U32 u32Command, HI_VOID* stAttr, HI_S32 s32Len );

/**transcoder module create attr*//** CNcomment:转码模块转码输入参数*/
typedef struct tagTran_HandleAttr
{
    Transcoder_MediaCodec audioCodec;   /**<audio codec id*//**<CNcomment:音频CodecID */
    Transcoder_MediaCodec videoCodec;   /**<video codec id*//**<CNcomment:视频CodecID */
    //   HI_U32 u32ProtocolMask;                       /**<protocol types mask*//**<CNcomment:打开时的打开协议的mask 值，可打开多个协议*/
    HI_U32 SourceType;                                   /**<source types ,reserve*//**<CNcomment:转码模块源处理音频源类型，为后续编码扩展预留*/
    //    HI_S32 s32X;                                            /**<X coordinate*//**<CNcomment:转码的起始位置 X 坐标*/
    //    HI_S32 s32Y;                                            /**<Y coordinate*//**<CNcomment:转码的起始位置 Y 坐标*/
    HI_S32 s32Width;                    /**<video resolution --width*//**<CNcomment:视频分辨率--宽 */
    HI_S32 s32Height;                     /**<video resolution --height*//**<CNcomment:视频分辨率--高 */
    HI_U32 u32VideoBitRate;                /**<video bitrate*//**<CNcomment:视频比特率 */
    HI_S32 s32VideoFrameRate;            /**<video frame rate*//**<CNcomment:视频帧率 */
    HI_S32 s32AudioSampleRate;            /**<audio sample rate*//**<CNcomment:音频采样率 */
    HI_S32 s32AudioBandWidth;            /**<audio band width*//**<CNcomment:音频采样宽度 */
    HI_S32 s32AudioChannels;                    /**<audio channel num*//**<CNcomment:音频采样的声道数量 */
    HI_S32 s32Gop;                     /**<video resolution --gop,can be set dynamically*//**<CNcomment:I帧间隔，可进行动态设置 */
    HI_BOOL bCycle;                                       /**<cycle flag for file input*//**<CNcomment:对于文件输入是否要循环 */
    HI_HANDLE hSrc;                   /**<transcoder input source handle*//**<CNcomment:转码输入源，如果为NULL，则全屏转码 */
    HI_HANDLE hVirtualWin;
    HI_TRANSCODER_NODIFY_CALLBACK pNodifySrcFunc;  /**<callback from transcode to source caller*//**<CNcomment:转码模块提供给其他模块的回调函数,后端端口回调给源端 */
} Transcoder_HandleAttr;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HiTran */
/** @{ */  /** <!—[HiTran]*/

/**-----Standard Functions--------*/
/**
\brief transcoder module initialization function.CNcomment:初始化转码器CNend
\attention \n
HiTranscoder module must init function.CNcomment:调用转码要求首先调用该接口。CNend

\param[in] void.CNcomment:void。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. init error happened.CNcomment:初始化失败。CNend
\see \n

\par example
\code
if (HI_Transcoder_Init() < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Init(void);


/**-----Standard Functions--------*/
/**
\brief transcoder  uninitialization function.CNcomment:去初始化转码器CNend
\attention \n
HiTranscoder module all clear function must called behind.CNcomment:转码退出要求最后调用该接口。CNend

\param[in] void.CNcomment:void。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. deinit error happened.CNcomment:去初始化失败。CNend
\see \n

\par example
\code
if (HI_Transcoder_DeInit() < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_DeInit(void);


/**-----Standard Functions--------*/
/**
\brief create transcoder function .CNcomment:打开转码通道CNend
\attention \n
transcoder create handle.must set Transcoder_HandleAttr attr,could call Transcoder_getDefaultAttr
when attr's property hsrc is NULL ,now version return failure.CNcomment:当业务需要使用转码能力时调用，
需要设置Transcoder_HandleAttr给转码通道，当转码属性中的hsrc为空时，现在版本返回错误
并且静音。CNend

\param[in] pstAttr transcoder handle attr.CNcomment:设置转码通道的属性。CNend
\param[out] pHandle  created the handle of transcoder.CNcomment:建立的转码通道句柄。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. create error happened.CNcomment:创建失败。CNend
\see \n

\par example
\code
HI_HANDLE pHandle;
Transcoder_HandleAttr pstAttr;
if (HI_Transcoder_Create(&pHandle, &pstAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Create(HI_HANDLE* pHandle, const Transcoder_HandleAttr* pstAttr);


/**-----Standard Functions--------*/
/**
\brief destroy transcoder handle.CNcomment:模块销毁transcoder句柄CNend
\attention \n
called this function,need destroy all protocol.
CNcomment:当业务需要关闭转码能力时调用，需要注意此时的状态需要销毁所有的协议，虚拟驱动。CNend

\param[in] pHandle created transcoder handle.CNcomment:已创建的transcoder句柄。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:销毁失败。CNend
\see \n

\par example
\code
if (HI_Transcoder_Destroy(pHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Destroy(HI_HANDLE pHandle);


/**-----Standard Functions--------*/
/**
\brief get the attr of transcoder handle.CNcomment:获取转码能力属性CNend
\attention \n
this function called after transcoder create handle function.
CNcomment:当业务需要获取转码能力属性，需要注意此接口需要在create函数调用后使用。CNend

\param[in] pHandle created transcoder handle.CNcomment:已创建的transcoder句柄。CNend
\param[in] eTranAttr attribute set type.CNcomment:指定返回的属性集类型。CNend
\param[out] pstAttr returned attribute set content.CNcomment:指定返回的属性集内容。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. get attribute error happened.CNcomment:获取属性集失败。CNend
\see \n

\par example
\code
Transcoder_Attr_ID_E eTranAttr = TRANSCODER_ALL_ATTR；
Transcoder_HandleAttr pstAttr；
if (HI_Transcoder_GetAttr(pHandle, eTranAttr,  &pstAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_GetAttr(HI_HANDLE pHandle, Transcoder_Attr_ID_E eTranAttr, Transcoder_HandleAttr* pstAttr);


/**-----Standard Functions--------*/
/**
\brief set transcoder handle attr.CNcomment:设置转码能力属性CNend
\attention \n
need called after transcoder create function.
CNcomment:当业务需要设置转码能力属性需要注意此接口需要在create函数调用后使用。CNend

\param[in] pHandle the handle who need set attr.CNcomment:已创建的transcoder句柄。CNend
\param[in] eTranAttr attribute set type.CNcomment:指定返回的属性集类型。CNend
\param[in] pstAttr the attr will set to handle.CNcomment:设置转码通道的属性。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. set attribute error happened.CNcomment:设置属性集失败。CNend
\see \n

\par example
\code
Transcoder_Attr_ID_E eTranAttr = TRANSCODER_ALL_ATTR；
Transcoder_HandleAttr pstAttr；
if (HI_Transcoder_SetAttr(pHandle, eTranAttr,  &pstAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_SetAttr(HI_HANDLE pHandle, Transcoder_Attr_ID_E eTranAttr, const Transcoder_HandleAttr* pstAttr);


/**-----Standard Functions--------*/
/**
\brief set transcoder handle status --- start.CNcomment:设置转码器状态机－－start  CNend
\attention \n
when transcoder enter stop-start status machine ,after transcoder create handle.
CNcomment:在转码器进入Stop-start状态接收该接口的状态机转换请求。CNend

\param[in] hTranHandle created transcoder handle.CNcomment:已创建的transcoder句柄。CNend
\param[in] bBlock blocked called or not .CNcomment:是否阻塞。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. transcoder start error happened.CNcomment:转码启动失败。CNend
\see \n

\par example
\code
HI_BOOL bBlock = HI_TRUE;
if (HI_Transcoder_Start(hTranHandle, bBlock) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Start(HI_HANDLE hTranHandle, HI_BOOL bBlock);


/**-----Standard Functions--------*/
/**
\brief set transcoder handle status --- stop.CNcomment:设置转码器状态机－－stop   CNend
\attention \n
transcoder enter stop-start status machine ,after transcoder create handle.
CNcomment:在转码器进入Stop-start状态接收该接口的状态机转换请求。CNend

\param[in] hTranHandle created transcoder handle.CNcomment:已创建的transcoder句柄。CNend
\param[in] bBlock blocked called or not .CNcomment:是否阻塞。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. transcoder stop error happened.CNcomment:转码关闭失败。CNend
\see \n

\par example
\code
HI_BOOL bBlock = HI_TRUE;
if (HI_Transcoder_Stop(hTranHandle, bBlock) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Stop(HI_HANDLE hTranHandle, HI_BOOL bBlock);


/**-----Standard Functions--------*/
/**
\brief sync called Transcoder module callback function,different because of command.CNcomment:同步启动Transcoder模块的回调函数，
其回调流程根据 Command不同而由用户指定不同的实现分支CNend
\attention \n
transcoder enter stop-start status machine ,after transcoder create handle.
CNcomment:在转码器进入Stop-start状态接收该接口的状态机转换请求。CNend

\param[in] hTranHandle created transcoder handle.CNcomment:已创建的transcoder句柄。CNend
\param[in] u32Command transcoder callback command.CNcomment:转码回调的指令。CNend
\param[in] pstAttr callback attr .CNcomment:指令的参数。CNend
\param[in] s32AttrLen callback attr len.CNcomment: 指令参数的长度。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. SetCommand error happened.CNcomment:回调caller失败。CNend
\see \n

\par example
\code
HI_BOOL bBlock = HI_TRUE;
HI_U32 u32Command = 0;
if (HI_Transcoder_SetCommand(hTranHandle, u32Command, pstAttr, s32AttrLen) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_SetCommand(HI_HANDLE hTranHandle, HI_U32 u32Command, HI_VOID* pstAttr, HI_S32 s32AttrLen);


/**-----Standard Functions--------*/
/**
\brief register media data read handle.CNcomment:注册媒体数据读取句柄CNend
\attention \n
register media data read handle,this function called by protocol and user.
CNcomment:注册媒体数据读出接口，该接口由protocol模块进行调用。CNend

\param[in] hTranHandle created transcoder handle.CNcomment:已创建的transcoder句柄。CNend
\param[out] phMbufReadHandle media data read handle.CNcomment:媒体数据的读取句柄。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. Register media Handle error happened.CNcomment:注册媒体读写句柄失败。CNend
\see \n

\par example
\code
HI_HANDLE phMbufReadHandle;
if (HI_Transcoder_RegisterHandle(hTranHandle, phMbufReadHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_RegisterHandle(HI_HANDLE hTranHandle, HI_HANDLE* phMbufReadHandle);


/**-----Standard Functions--------*/
/**
\brief unregister media data read handle.CNcomment:去注册媒体数据读取句柄CNend
\attention \n
unregister media data read handle,this function called by protocol and user.
CNcomment:去注册媒体数据读出接口，该接口由protocol模块进行调用。CNend

\param[in] phMbufReadHandle registed media data read handle.CNcomment:已注册的媒体数据的读取句柄。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. DeRegister media Handle error happened.CNcomment:去注册媒体读写句柄失败。CNend
\see \n

\par example
\code
HI_HANDLE phMbufReadHandle;
if (HI_Transcoder_DeRegisterHandle(phMbufReadHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_DeRegisterHandle(HI_HANDLE hMbufReadHandle);


/**-----Standard Functions--------*/
/**
\brief read media data from mbuf handle.CNcomment:读取媒体数据CNend
\attention \n
when there no data in buffer, will return HI_FAILURE.
CNcomment:读取的数据可能由于MBUF数据为空，无法读出，此时返回HI_FAILURE。CNend

\param[in] hReadHandle registed media data read handle.CNcomment:已注册的媒体数据的读取句柄。CNend
\param[out] pstTranFrame returned media data from read handle.CNcomment:从MBUF中读取的数据帧结构。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. read media stream error happened.CNcomment:读取媒体数据返回空。CNend
\see \n

\par example
\code
TRANSCODER_STRAM pstTranFrame;
if (HI_Transcoder_ReadStream(&pstTranFrame) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_ReadStream(HI_HANDLE hReadHandle, TRANSCODER_STRAM* pstTranFrame);


/**-----Standard Functions--------*/
/**
\brief get the default attribute set of transcoder.CNcomment:获取转码默认属性集CNend
\attention \n

\param[out] stTranHandleAttr returned default transcoder attribute set.CNcomment:返回转码的默认属性集。CNend
\retval void.CNcomment:void。
\see \n

\par example
\code
Transcoder_HandleAttr pstTranFrame;
if (Transcoder_getDefaultAttr(&stTranHandleAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_VOID Transcoder_getDefaultAttr(Transcoder_HandleAttr* stTranHandleAttr);
/**-----Standard Functions--------*/
/**
\brief Switch transcoding input source.CNcomment:切换转码输入源CNend
\attention \n
need called after transcoder start function. CNcomment:
当业务需要切换转码输入源情况需要注意此接口要在Start函数调用后使用CNend

\param[in] pHandle  the handle who need change srchandle.CNcomment:已创建的transcoder句柄。CNend
\param[in] hAVplay  transcoding input source.CNcomment:转码输入源。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. set attribute error happened.CNcomment:切换转码输入源失败。CNend
\see \n

\par example
\code
HI_HANDLE hAVplay；
if (HI_Transcoder_ChangeHandle(pHandle,hsrchandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_ChangeHandle(HI_HANDLE pHandle, HI_HANDLE hAVplay);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
}
#endif /* __cplusplus*/


#endif /* __HI_TRANSCODER_H__*/