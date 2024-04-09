
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
/** @{ */  /** <!��[HiMuxer]*/

#define TRANSCODER_MUXER_MEM_MAX (16)

/** @} */  /*! <!-- Macro Definition End */


/*************************** Structure Definition ****************************/
/** \addtogroup      HiMuxer */
/** @{*/  /** <!��[HiMuxer]*/

/**transcoder muxer file type*//** CNcomment:ת��ģ��ת���ļ���װ���� */
typedef enum eTran_Muxerype
{
    TRANSCODER_MUTEX_FLV = 1,
    TRANSCODER_MUTEX_TS = 2,
    TRANSCODER_MUTEX_RTP = 4,
    TRANSCODER_MUTEX_ES = 8,
    TRANSCODER_MUTEX_BUTT,
} Transcoder_MuxerType;

/**transcoder muxer create attr*//** CNcomment:ת��ģ��ת���ļ���װ������� */
typedef struct tagTran_MuxerAttr
{
    Transcoder_MediaCodec audioCodec;   /**<audio codec id*//**<CNcomment:��ƵCodecID */
    Transcoder_MediaCodec videoCodec;   /**<video codec id*//**<CNcomment:��ƵCodecID */
    HI_S32 s32Width;                                        /**<video resolution --width*//**<CNcomment:��Ƶ�ֱ���--�� */
    HI_S32 s32Height;                                       /**<video resolution --height*//**<CNcomment:��Ƶ�ֱ���--�� */
    HI_U32 u32VideoBitRate;                          /**<video bitrate*//**<CNcomment:��Ƶ������ */
    HI_S32 s32VideoFrameRate;             /**<video frame rate*//**<CNcomment:��Ƶ֡�� */
    HI_S32 s32AudioSampleRate;                 /**<audio sample rate*//**<CNcomment:��Ƶ������ */
    HI_S32 s32AudioBandWidth;                   /**<audio band width*//**<CNcomment:��Ƶ������� */
    HI_S32 s32AudioChannels;                     /**<audio channel num*//**<CNcomment:��Ƶ�������������� */
} Transcoder_MuxerAttr;

/** @}*/  /** <!-- ==== Structure Definition End ====*/


/******************************* API Declaration *****************************/
/** \addtogroup      HiMuxer */
/** @{ */  /** <!��[HiMuxer]*/

/**-----Standard Functions--------*/
/**
\brief muxer module initialization function.CNcomment:ģ���ʼ��CNend
\attention \n

\param[in] void.CNcomment:void��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. init error happened.CNcomment:��ʼ��ʧ�ܡ�CNend
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
\brief muxer  uninitialization function.CNcomment:ģ��ȥ��ʼ��CNend
\attention \n

\param[in] void.CNcomment:void��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. deinit error happened.CNcomment:ȥ��ʼ��ʧ�ܡ�CNend
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
\brief Protocol  muxer  create handle function .CNcomment:muxerģ�鴴�����CNend
\attention \n
this function called by user and protocol, create a new muxer handle.
CNcomment:�˽ӿ���protocol���ã���������һ��muxer�Ľӿڡ�CNend

\param[in] muxerType muxer type.CNcomment:���õ�Muxer�����͡�CNend
\param[in] muxerAttr muxer create attr.CNcomment:���õ�Muxer�����ԡ�CNend
\param[out] hMuxerHandle  created muxer handle.CNcomment:���ɵ�Muxer�����CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. create error happened.CNcomment:����ʧ�ܡ�CNend
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
\brief muxer  module destroy protocol handle.CNcomment:muxerģ������Protocol���CNend
\attention \n
this function called by user and protocol, destroy a new muxer handle.
CNcomment:�˽ӿ���protocol���ã���������һ��muxer�Ľӿڡ�CNend

\param[in] hMuxerHandle muxer handle.CNcomment:�Ѵ�����muxer�����CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:����ʧ�ܡ�CNend
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
\brief muxer  get file header.CNcomment:muxerģ���ȡͷ����CNend
\attention \n
this function called by user and protocol,get the file header or special frame.
CNcomment:�˽ӿ���protocol���ã�������ȡ��һ��ͷ���ݻ�����֡��CNend

\param[in] hMuxerHandle muxer handle.CNcomment:�Ѵ�����muxer�����CNend
\param[out] pTAGFrame returned header content .CNcomment:���ص�muxerͷ�����ݡ�CNend
\param[in/out] ps32Len input buffer length ,returned header length.CNcomment:����buffer ���ȣ����ͷ�����ȡ�CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:����ʧ�ܡ�CNend
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
\brief muxer get normal frame.CNcomment:muxerģ���ȡ��ͨ����CNend
\attention \n
this function called by user and protocol,muxer a ES frame to a Muxer TAG.
CNcomment:�˽ӿ���protocol���ã�������ȡһ����װ����ͨ TAG���ݡ�CNend

\param[in] hMuxerHandle muxer handle.CNcomment:�Ѵ�����muxer�����CNend
\param[out] pTAGFrame returned frame content .CNcomment:���ص�frame���ݡ�CNend
\param[in/out] ps32Len input buffer length ,returned data length packed.CNcomment:����buffer ���ȣ����Muxer֮������ݰ����ȡ�CNend
\param[in] pstTranFrame ES stream get from Transcoder to do muxer.CNcomment:��Transcoder�ж�ȡ������֡��CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. domuxer error happened.CNcomment:��װʧ�ܡ�CNend
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
\brief muxer set private attr.CNcomment:muxerģ������˽������CNend
\attention \n
this function called by user and protocol,to set muxer private attr.
CNcomment:�˽ӿ���protocol���ã���������һ��muxer��˽�����ԡ�CNend

\param[in] hMuxerHandle muxer handle.CNcomment:�Ѵ�����muxer�����CNend
\param[in] stAttr private attr defined by protocol specific module .CNcomment:���õ�˽�в�����CNend
\param[in] s32Len  the private attr data len.CNcomment:˽�в����ĳ��ȡ�CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. set private data to muxer error happened.CNcomment:����muxer˽������ʧ�ܡ�CNend
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
\brief Muxer register external muxer lib .CNcomment:Muxer ע���ⲿ��װ��ʽ����CNend
\attention \n
called after HI_Muxer_Init.CNcomment:�˺�������HI_Muxer_Init����ܵ��á�CNend

\param[in] pLibMuxerName external muxer lib name.CNcomment:Ҫע��Ŀ����ơ�CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1.  register external muxer lib error happened.CNcomment:ע������Muxer ��ʧ�ܡ�CNend
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
\brief Muxer unregister external muxer lib .CNcomment:Muxer ȥע���ⲿ��װ��ʽ����CNend
\attention \n
called after HI_Muxer_Init.CNcomment:�˺�������HI_Muxer_Init����ܵ��á�CNend

\param[in] pLibMuxerName external muxer lib name.CNcomment:Ҫȥע��Ŀ����ơ�CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1.  unregister external muxer lib error happened.CNcomment:ȥע������Muxer ��ʧ�ܡ�CNend
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