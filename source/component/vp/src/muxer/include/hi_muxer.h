
/**
 * \file hi_muxer.h
 * \brief Describes the information about HiSilicion Transcoder Muxer (HiMuxer).
*/

#ifndef __HI_MUXER_H__
#define __HI_MUXER_H__

#include "hi_type.h"
#include "hi_transcoder.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/
/** \addtogroup      HiMuxer */
/** @{ */  /** <!—[HiMuxer]*/

#define TRANSCODER_MUXER_MEM_MAX (16)

/** @} */  /*! <!-- Macro Definition End */


/*************************** Structure Definition ****************************/
/** \addtogroup      HiMuxer */
/** @{*/  /** <!—[HiMuxer]*/

/**transcoder muxer file type*//** CNcomment:转码模块转码文件封装类型 */
typedef enum eTran_Muxerype
{
    TRANSCODER_MUTEX_FLV = 1,
    TRANSCODER_MUTEX_TS = 2,
    TRANSCODER_MUTEX_RTP = 4,
    TRANSCODER_MUTEX_ES = 8,
    TRANSCODER_MUTEX_BUTT,
} Transcoder_MuxerType;

/**transcoder muxer create attr*//** CNcomment:转码模块转码文件封装输入参数 */
typedef struct tagTran_MuxerAttr
{
    Transcoder_MediaCodec audioCodec;   /**<audio codec id*//**<CNcomment:音频CodecID */
    Transcoder_MediaCodec videoCodec;   /**<video codec id*//**<CNcomment:视频CodecID */
    HI_S32 s32Width;                                        /**<video resolution --width*//**<CNcomment:视频分辨率--宽 */
    HI_S32 s32Height;                                       /**<video resolution --height*//**<CNcomment:视频分辨率--高 */
    HI_U32 u32VideoBitRate;                          /**<video bitrate*//**<CNcomment:视频比特率 */
    HI_S32 s32VideoFrameRate;             /**<video frame rate*//**<CNcomment:视频帧率 */
    HI_S32 s32AudioSampleRate;                 /**<audio sample rate*//**<CNcomment:音频采样率 */
    HI_S32 s32AudioBandWidth;                   /**<audio band width*//**<CNcomment:音频采样宽度 */
    HI_S32 s32AudioChannels;                     /**<audio channel num*//**<CNcomment:音频采样的声道数量 */
} Transcoder_MuxerAttr;

/** @}*/  /** <!-- ==== Structure Definition End ====*/


/******************************* API Declaration *****************************/
/** \addtogroup      HiMuxer */
/** @{ */  /** <!—[HiMuxer]*/

/**-----Standard Functions--------*/
/**
\brief muxer module initialization function.CNcomment:模块初始化CNend
\attention \n

\param[in] void.CNcomment:void。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. init error happened.CNcomment:初始化失败。CNend
\see \n

\par example
\code
if (HI_Muxer_Init() < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Muxer_Init();


/**-----Standard Functions--------*/
/**
\brief muxer  uninitialization function.CNcomment:模块去初始化CNend
\attention \n

\param[in] void.CNcomment:void。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. deinit error happened.CNcomment:去初始化失败。CNend
\see \n

\par example
\code
if (HI_Muxer_DeInit() < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Muxer_DeInit();


/**-----Standard Functions--------*/
/**
\brief Protocol  muxer  create handle function .CNcomment:muxer模块创建句柄CNend
\attention \n
this function called by user and protocol, create a new muxer handle.
CNcomment:此接口由protocol调用，用来生成一个muxer的接口。CNend

\param[in] muxerType muxer type.CNcomment:设置的Muxer的类型。CNend
\param[in] muxerAttr muxer create attr.CNcomment:设置的Muxer的属性。CNend
\param[out] hMuxerHandle  created muxer handle.CNcomment:生成的Muxer句柄。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. create error happened.CNcomment:创建失败。CNend
\see \n

\par example
\code
HI_HANDLE hMuxerHandle;
Transcoder_MuxerAttr muxerAttr;
HI_U32 muxerType = TRANSCODER_MUTEX_TS;
if (HI_Muxer_Create(&hProtocolHandle, &pstTranAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Muxer_Create(HI_ULONG* hMuxerHandle, HI_U32 muxerType, Transcoder_MuxerAttr* muxerAttr);


/**-----Standard Functions--------*/
/**
\brief muxer  module destroy protocol handle.CNcomment:muxer模块销毁Protocol句柄CNend
\attention \n
this function called by user and protocol, destroy a new muxer handle.
CNcomment:此接口由protocol调用，用来销毁一个muxer的接口。CNend

\param[in] hMuxerHandle muxer handle.CNcomment:已创建的muxer句柄。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:销毁失败。CNend
\see \n

\par example
\code
if (HI_Muxer_Destroy(hMuxerHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Muxer_Destroy(HI_ULONG hMuxerHandle);


/**-----Standard Functions--------*/
/**
\brief muxer  get file header.CNcomment:muxer模块获取头数据CNend
\attention \n
this function called by user and protocol,get the file header or special frame.
CNcomment:此接口由protocol调用，用来获取第一个头数据或特征帧。CNend

\param[in] hMuxerHandle muxer handle.CNcomment:已创建的muxer句柄。CNend
\param[out] pTAGFrame returned header content .CNcomment:返回的muxer头部内容。CNend
\param[in/out] ps32Len input buffer length ,returned header length.CNcomment:输入buffer 长度，输出头部长度。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:销毁失败。CNend
\see \n

\par example
\code
HI_CHAR pTAGFrame[num];
HI_S32 ps32Len = num;

if (HI_Muxer_GetHeader(hMuxerHandle, pTAGFrame , ps32Len) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Muxer_GetHeader(HI_ULONG hMuxerHandle, HI_CHAR* pTAGFrame, HI_S32* ps32Len);


/**-----Standard Functions--------*/
/**
\brief muxer get normal frame.CNcomment:muxer模块获取普通数据CNend
\attention \n
this function called by user and protocol,muxer a ES frame to a Muxer TAG.
CNcomment:此接口由protocol调用，用来获取一个封装的普通 TAG数据。CNend

\param[in] hMuxerHandle muxer handle.CNcomment:已创建的muxer句柄。CNend
\param[out] pTAGFrame returned frame content .CNcomment:返回的frame内容。CNend
\param[in/out] ps32Len input buffer length ,returned data length packed.CNcomment:输入buffer 长度，输出Muxer之后的数据包长度。CNend
\param[in] pstTranFrame ES stream get from Transcoder to do muxer.CNcomment:从Transcoder中读取的数据帧。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1. domuxer error happened.CNcomment:封装失败。CNend
\see \n

\par example
\code
HI_CHAR pTAGFrame[num];
HI_S32 ps32Len = num;
if (HI_Muxer_DoMuxer(hMuxerHandle, pTAGFrame , ps32Len, pstTranFrame) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Muxer_DoMuxer(HI_ULONG hMuxerHandle, HI_CHAR* pTAGFrame, HI_S32* ps32Len, TRANSCODER_STRAM* pstTranFrame);


/**-----Standard Functions--------*/
/**
\brief muxer set private attr.CNcomment:muxer模块设置私有属性CNend
\attention \n
this function called by user and protocol,to set muxer private attr.
CNcomment:此接口由protocol调用，用来设置一个muxer的私有属性。CNend

\param[in] hMuxerHandle muxer handle.CNcomment:已创建的muxer句柄。CNend
\param[in] stAttr private attr defined by protocol specific module .CNcomment:设置的私有参数。CNend
\param[in] s32Len  the private attr data len.CNcomment:私有参数的长度。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. set private data to muxer error happened.CNcomment:设置muxer私有属性失败。CNend
\see \n

\par example
\code
if (HI_Muxer_SetPrivateData(hMuxerHandle, stAttr , ps32Len) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Muxer_SetPrivateData(HI_ULONG hMuxerHandle, HI_VOID* stAttr, HI_S32 s32Len);


/**-----Standard Functions--------*/
/**
\brief Muxer register external muxer lib .CNcomment:Muxer 注册外部封装格式函数CNend
\attention \n
called after HI_Muxer_Init.CNcomment:此函数需在HI_Muxer_Init后才能调用。CNend

\param[in] pLibMuxerName external muxer lib name.CNcomment:要注册的库名称。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。CNend
\retval ::HI_FAILURE  -1.  register external muxer lib error happened.CNcomment:注册外链Muxer 库失败。CNend
\see \n

\par example
\code
HI_CHAR pLibMuxerName = {lib*muxer.so};
if (HI_Muxer_RegistMuxer(pLibMuxerName) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Muxer_RegistMuxer(const HI_CHAR* pLibMuxerName);


/**-----Standard Functions--------*/
/**
\brief Muxer unregister external muxer lib .CNcomment:Muxer 去注册外部封装格式函数CNend
\attention \n
called after HI_Muxer_Init.CNcomment:此函数需在HI_Muxer_Init后才能调用。CNend

\param[in] pLibMuxerName external muxer lib name.CNcomment:要去注册的库名称。CNend
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1.  unregister external muxer lib error happened.CNcomment:去注册外链Muxer 库失败。CNend
\see \n

\par example
\code
HI_CHAR pLibMuxerName = {lib*muxer.so};
if (HI_Muxer_DeRegistMuxer(pLibMuxerName) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Muxer_DeRegistMuxer(const HI_CHAR* pLibMuxerName);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
}
#endif /* __cplusplus*/


#endif /* __HI_MUXER_H__*/