
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
/** @{ */  /** <!��[HiTran]*/

/**software platform define*//** CNcomment:��ȡ���ƽ̨ */
#ifdef ANDROID_TOOLCHAIN
#define SOFT_BOARD_VERSION_ANDROID
#else
#define SOFT_BOARD_VERSION_LINUX
#endif

/** @} */  /*! <!-- Macro Definition End */


/*************************** Structure Definition ****************************/
/** \addtogroup      HiTran */
/** @{*/  /** <!��[HiTran]*/

/**transcoder media data type*//** CNcomment:��ȡ֡�������� */
typedef enum eTran_PAYLOAD
{
    PAYLOAD_VIDEO_NORMAL_FRAME = 1,
    PAYLOAD_VIDEO_KEY_FRAME , //��Ƶ�ؼ�֡
    PAYLOAD_VIDEO_VPS_FRAME ,
    PAYLOAD_VIDEO_SPS_FRAME ,
    PAYLOAD_VIDEO_PPS_FRAME,
    PAYLOAD_AUDIO_FRAME = 10, //��Ƶ֡
    PAYLOAD_MD_FRAME, //MD����
    PAYLOAD_BUTT
} TRANSCODER_PAYLOAD_E;

/**transcoder video/audio type*//** CNcomment:ת��ģ��ת������Ƶ���� */
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

/**transcoder attribute set of diff type*//** CNcomment:ת��ģ����������Լ�*/
typedef enum eTran_Attr_ID_E
{
    TRANSCODER_ALL_ATTR,
    TRANSCODER_VIDEO_ATTR,
    TRANSCODER_AUDIO_ATTR,
    TRANSCODER_BACKGND_ATTR,
    TRANSCODER_ATTR_BUTT
} Transcoder_Attr_ID_E;

/**transcoder source type*//** CNcomment:ת��ģ������Դ����*/
typedef enum eTran_Src_Type_E
{
    TRANSCODER_SOURCE_AVPLAY,
    TRANSCODER_SOURCE_OSD_VO_PCM,
    TRANSCODER_SOURCE_BUTT
} Transcoder_Src_Type_E;

typedef struct tagTran_VencStream
{
    HI_U8* pu8Addr;       /**<Stream virtual address*/ /**<CNcomment: ���������ַ*/
    HI_U32 u32SlcLen;      /**<Stream length*/ /**<CNcomment: ��������*/
    HI_U32 u32PtsMs;        /**<Presentation time stamp (PTS), in ms*/ /**<CNcomment: ʱ�������λ�Ǻ���*/
} TRANSCODER_VENC_STREAM;

typedef struct tagTran_AencStream
{
    HI_U8* pu8Buf;    /**<User-state virtual address of the buffer*/ /**<CNcomment: buffer���û�̬���ַ*/
    HI_U32 u32BufLen;  /**<Buffer length*/ /**<CNcomment: buffer�ĳ���*/
    HI_U32 u32PtsMs;   /**<Presentation time stamp (PTS) value corresponding to the start of the stream. The invalid value is 0xFFFFFFFF.*/
    /**<CNcomment: ������ʼ����Ӧ��PTSֵ����ЧΪ0xffffffff*/
} TRANSCODER_AENC_STREAM;

/**media data payload data structure*//** CNcomment:ý������payLoad��������*/
typedef union tagTran_StreamDataType
{
    TRANSCODER_VENC_STREAM stVencStream;  /**<video stream encoded data *//**<CNcomment:��Ƶ���������� */
    TRANSCODER_AENC_STREAM stAencStream;            /**<audio stream encoded data *//**<CNcomment:��Ƶ���������� */
} TRANSCODER_DATA_TYPE_U;

/**transcoder data frame structure*//** CNcomment:ý������֡�ṹ*/
typedef struct tagTran_STREAM_S
{
    TRANSCODER_PAYLOAD_E ePayloadType;  /**<stream payload type *//**<CNcomment:PayLoad�������� */
    TRANSCODER_DATA_TYPE_U  enDataStream;             /**<stream data *//**<CNcomment:ý��������*/
} TRANSCODER_STRAM;


/**supply for user callback function, modified by user, set by source module*/
/** CNcomment:�ṩ���û���ָ��ص��ӿڣ����ݲ�ͬ��ָ��������Ժ���Դ��ģ�飬
��Դ��ģ��ȷ������Ӧ��ʽ����Ϊ��̨ת�룬�˺������� Transcoderʵ��*/
typedef HI_S32 (*HI_TRANSCODER_NODIFY_CALLBACK)(HI_HANDLE Handle, HI_U32 u32Command, HI_VOID* stAttr, HI_S32 s32Len );

/**transcoder module create attr*//** CNcomment:ת��ģ��ת���������*/
typedef struct tagTran_HandleAttr
{
    Transcoder_MediaCodec audioCodec;   /**<audio codec id*//**<CNcomment:��ƵCodecID */
    Transcoder_MediaCodec videoCodec;   /**<video codec id*//**<CNcomment:��ƵCodecID */
    //   HI_U32 u32ProtocolMask;                       /**<protocol types mask*//**<CNcomment:��ʱ�Ĵ�Э���mask ֵ���ɴ򿪶��Э��*/
    HI_U32 SourceType;                                   /**<source types ,reserve*//**<CNcomment:ת��ģ��Դ������ƵԴ���ͣ�Ϊ����������չԤ��*/
    //    HI_S32 s32X;                                            /**<X coordinate*//**<CNcomment:ת�����ʼλ�� X ����*/
    //    HI_S32 s32Y;                                            /**<Y coordinate*//**<CNcomment:ת�����ʼλ�� Y ����*/
    HI_S32 s32Width;                    /**<video resolution --width*//**<CNcomment:��Ƶ�ֱ���--�� */
    HI_S32 s32Height;                     /**<video resolution --height*//**<CNcomment:��Ƶ�ֱ���--�� */
    HI_U32 u32VideoBitRate;                /**<video bitrate*//**<CNcomment:��Ƶ������ */
    HI_S32 s32VideoFrameRate;            /**<video frame rate*//**<CNcomment:��Ƶ֡�� */
    HI_S32 s32AudioSampleRate;            /**<audio sample rate*//**<CNcomment:��Ƶ������ */
    HI_S32 s32AudioBandWidth;            /**<audio band width*//**<CNcomment:��Ƶ������� */
    HI_S32 s32AudioChannels;                    /**<audio channel num*//**<CNcomment:��Ƶ�������������� */
    HI_S32 s32Gop;                     /**<video resolution --gop,can be set dynamically*//**<CNcomment:I֡������ɽ��ж�̬���� */
    HI_BOOL bCycle;                                       /**<cycle flag for file input*//**<CNcomment:�����ļ������Ƿ�Ҫѭ�� */
    HI_HANDLE hSrc;                   /**<transcoder input source handle*//**<CNcomment:ת������Դ�����ΪNULL����ȫ��ת�� */
    HI_HANDLE hVirtualWin;
    HI_TRANSCODER_NODIFY_CALLBACK pNodifySrcFunc;  /**<callback from transcode to source caller*//**<CNcomment:ת��ģ���ṩ������ģ��Ļص�����,��˶˿ڻص���Դ�� */
} Transcoder_HandleAttr;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HiTran */
/** @{ */  /** <!��[HiTran]*/

/**-----Standard Functions--------*/
/**
\brief transcoder module initialization function.CNcomment:��ʼ��ת����CNend
\attention \n
HiTranscoder module must init function.CNcomment:����ת��Ҫ�����ȵ��øýӿڡ�CNend

\param[in] void.CNcomment:void��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. init error happened.CNcomment:��ʼ��ʧ�ܡ�CNend
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
\brief transcoder  uninitialization function.CNcomment:ȥ��ʼ��ת����CNend
\attention \n
HiTranscoder module all clear function must called behind.CNcomment:ת���˳�Ҫ�������øýӿڡ�CNend

\param[in] void.CNcomment:void��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. deinit error happened.CNcomment:ȥ��ʼ��ʧ�ܡ�CNend
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
\brief create transcoder function .CNcomment:��ת��ͨ��CNend
\attention \n
transcoder create handle.must set Transcoder_HandleAttr attr,could call Transcoder_getDefaultAttr
when attr's property hsrc is NULL ,now version return failure.CNcomment:��ҵ����Ҫʹ��ת������ʱ���ã�
��Ҫ����Transcoder_HandleAttr��ת��ͨ������ת�������е�hsrcΪ��ʱ�����ڰ汾���ش���
���Ҿ�����CNend

\param[in] pstAttr transcoder handle attr.CNcomment:����ת��ͨ�������ԡ�CNend
\param[out] pHandle  created the handle of transcoder.CNcomment:������ת��ͨ�������CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. create error happened.CNcomment:����ʧ�ܡ�CNend
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
\brief destroy transcoder handle.CNcomment:ģ������transcoder���CNend
\attention \n
called this function,need destroy all protocol.
CNcomment:��ҵ����Ҫ�ر�ת������ʱ���ã���Ҫע���ʱ��״̬��Ҫ�������е�Э�飬����������CNend

\param[in] pHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:����ʧ�ܡ�CNend
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
\brief get the attr of transcoder handle.CNcomment:��ȡת����������CNend
\attention \n
this function called after transcoder create handle function.
CNcomment:��ҵ����Ҫ��ȡת���������ԣ���Ҫע��˽ӿ���Ҫ��create�������ú�ʹ�á�CNend

\param[in] pHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����CNend
\param[in] eTranAttr attribute set type.CNcomment:ָ�����ص����Լ����͡�CNend
\param[out] pstAttr returned attribute set content.CNcomment:ָ�����ص����Լ����ݡ�CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. get attribute error happened.CNcomment:��ȡ���Լ�ʧ�ܡ�CNend
\see \n

\par example
\code
Transcoder_Attr_ID_E eTranAttr = TRANSCODER_ALL_ATTR��
Transcoder_HandleAttr pstAttr��
if (HI_Transcoder_GetAttr(pHandle, eTranAttr,  &pstAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_GetAttr(HI_HANDLE pHandle, Transcoder_Attr_ID_E eTranAttr, Transcoder_HandleAttr* pstAttr);


/**-----Standard Functions--------*/
/**
\brief set transcoder handle attr.CNcomment:����ת����������CNend
\attention \n
need called after transcoder create function.
CNcomment:��ҵ����Ҫ����ת������������Ҫע��˽ӿ���Ҫ��create�������ú�ʹ�á�CNend

\param[in] pHandle the handle who need set attr.CNcomment:�Ѵ�����transcoder�����CNend
\param[in] eTranAttr attribute set type.CNcomment:ָ�����ص����Լ����͡�CNend
\param[in] pstAttr the attr will set to handle.CNcomment:����ת��ͨ�������ԡ�CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. set attribute error happened.CNcomment:�������Լ�ʧ�ܡ�CNend
\see \n

\par example
\code
Transcoder_Attr_ID_E eTranAttr = TRANSCODER_ALL_ATTR��
Transcoder_HandleAttr pstAttr��
if (HI_Transcoder_SetAttr(pHandle, eTranAttr,  &pstAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_SetAttr(HI_HANDLE pHandle, Transcoder_Attr_ID_E eTranAttr, const Transcoder_HandleAttr* pstAttr);


/**-----Standard Functions--------*/
/**
\brief set transcoder handle status --- start.CNcomment:����ת����״̬������start  CNend
\attention \n
when transcoder enter stop-start status machine ,after transcoder create handle.
CNcomment:��ת��������Stop-start״̬���ոýӿڵ�״̬��ת������CNend

\param[in] hTranHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����CNend
\param[in] bBlock blocked called or not .CNcomment:�Ƿ�������CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. transcoder start error happened.CNcomment:ת������ʧ�ܡ�CNend
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
\brief set transcoder handle status --- stop.CNcomment:����ת����״̬������stop   CNend
\attention \n
transcoder enter stop-start status machine ,after transcoder create handle.
CNcomment:��ת��������Stop-start״̬���ոýӿڵ�״̬��ת������CNend

\param[in] hTranHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����CNend
\param[in] bBlock blocked called or not .CNcomment:�Ƿ�������CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. transcoder stop error happened.CNcomment:ת��ر�ʧ�ܡ�CNend
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
\brief sync called Transcoder module callback function,different because of command.CNcomment:ͬ������Transcoderģ��Ļص�������
��ص����̸��� Command��ͬ�����û�ָ����ͬ��ʵ�ַ�֧CNend
\attention \n
transcoder enter stop-start status machine ,after transcoder create handle.
CNcomment:��ת��������Stop-start״̬���ոýӿڵ�״̬��ת������CNend

\param[in] hTranHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����CNend
\param[in] u32Command transcoder callback command.CNcomment:ת��ص���ָ�CNend
\param[in] pstAttr callback attr .CNcomment:ָ��Ĳ�����CNend
\param[in] s32AttrLen callback attr len.CNcomment: ָ������ĳ��ȡ�CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. SetCommand error happened.CNcomment:�ص�callerʧ�ܡ�CNend
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
\brief register media data read handle.CNcomment:ע��ý�����ݶ�ȡ���CNend
\attention \n
register media data read handle,this function called by protocol and user.
CNcomment:ע��ý�����ݶ����ӿڣ��ýӿ���protocolģ����е��á�CNend

\param[in] hTranHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����CNend
\param[out] phMbufReadHandle media data read handle.CNcomment:ý�����ݵĶ�ȡ�����CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. Register media Handle error happened.CNcomment:ע��ý���д���ʧ�ܡ�CNend
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
\brief unregister media data read handle.CNcomment:ȥע��ý�����ݶ�ȡ���CNend
\attention \n
unregister media data read handle,this function called by protocol and user.
CNcomment:ȥע��ý�����ݶ����ӿڣ��ýӿ���protocolģ����е��á�CNend

\param[in] phMbufReadHandle registed media data read handle.CNcomment:��ע���ý�����ݵĶ�ȡ�����CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. DeRegister media Handle error happened.CNcomment:ȥע��ý���д���ʧ�ܡ�CNend
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
\brief read media data from mbuf handle.CNcomment:��ȡý������CNend
\attention \n
when there no data in buffer, will return HI_FAILURE.
CNcomment:��ȡ�����ݿ�������MBUF����Ϊ�գ��޷���������ʱ����HI_FAILURE��CNend

\param[in] hReadHandle registed media data read handle.CNcomment:��ע���ý�����ݵĶ�ȡ�����CNend
\param[out] pstTranFrame returned media data from read handle.CNcomment:��MBUF�ж�ȡ������֡�ṹ��CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. read media stream error happened.CNcomment:��ȡý�����ݷ��ؿա�CNend
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
\brief get the default attribute set of transcoder.CNcomment:��ȡת��Ĭ�����Լ�CNend
\attention \n

\param[out] stTranHandleAttr returned default transcoder attribute set.CNcomment:����ת���Ĭ�����Լ���CNend
\retval void.CNcomment:void��
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
\brief Switch transcoding input source.CNcomment:�л�ת������ԴCNend
\attention \n
need called after transcoder start function. CNcomment:
��ҵ����Ҫ�л�ת������Դ�����Ҫע��˽ӿ�Ҫ��Start�������ú�ʹ��CNend

\param[in] pHandle  the handle who need change srchandle.CNcomment:�Ѵ�����transcoder�����CNend
\param[in] hAVplay  transcoding input source.CNcomment:ת������Դ��CNend
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�CNend
\retval ::HI_FAILURE  -1. set attribute error happened.CNcomment:�л�ת������Դʧ�ܡ�CNend
\see \n

\par example
\code
HI_HANDLE hAVplay��
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