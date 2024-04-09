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
/** CNcomment: ������Կ��󳤶ȣ���λ:�ֽڡ�ע��: ��Կ����Ч���Ȳ�һ������󳤶ȣ������ɼ��ܵ��㷨���� */
#define PVR_HAL_MAX_CIPHER_KEY_LEN  (128)

/**file name max length.*//** CNcomment:�ļ�����󳤶� */
#define PVR_FILE_NAME_LENGTH        (255)

#define PVR_MAX_FILENAME_LEN        (256)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_PVR */
/** @{ */  /** <!-- [HAL_PVR] */

/**Struct of PVR init parameters*/
/**CNcomment:PVRģ���ʼ������ */
typedef struct  _PVR_RECINIT_PARAMS_S
{
    U8 u8Dummy; /**<Reserved.*//**< CNcomment: ��������.*/
} PVR_RECINIT_PARAMS_S;

/**Struct of PVR terminate parameters*/
/**CNcomment:PVRģ����ֹ����   */
typedef  struct _PVR_TERM_PARAMS_S
{
    U8 u8Dummy; /**<Reserved.*//**< CNcomment: ��������.*/
} PVR_TERM_PARAMS_S;

/**Type of recorded and played streams of the PVR*//** CNcomment: PVR¼�ơ�����֧�ֵ��������� */
typedef enum  _PVR_STREAM_TYPE_E
{
    PVR_STREAM_TS = 1 << 0,         /**<Transport stream (TS)*/ /**<CNcomment:  TS�� */
    PVR_STREAM_PES = 1 << 1,        /**<Packetized elementary stream (PES)*/ /**<CNcomment: PES�� */
    PVR_STREAM_ALL_TS = 1 << 2,     /**<All types of streams. That is, the streams at all frequencies are recorded.*/ /**<CNcomment: ȫ����¼�ƣ�¼������Ƶ����������� */
    PVR_STREAM_OTHER = 1 << 3,      /**<Invalid*/ /**<CNcomment:  ��Ч������ */
    PVR_STREAM_BUTT
} PVR_STREAM_TYPE_E;

/** PVR capability */
/** CNcomment: PVR����*/
typedef struct  _PVR_CAPABILITY_S
{
    U32                 u32SupportRecNumber;    /**<Support max record channel number.*//**< CNcomment: ��֧�ֵ����¼��ͨ����.*/
    U32                 u32SupportPlayNumber;   /**<Support max play channel number.*//**< CNcomment: ��֧�ֵ���󲥷�ͨ����.*/
    BOOL                bSupportTimeShift;      /**<Whether support timeshift.*//**< CNcomment: �Ƿ�֧��ʱ�ƹ���.*/
    PVR_STREAM_TYPE_E   enStreamType;           /**<Support recorded and played stream type, support OR operate.*//**< CNcomment: PVR¼�ơ�����֧�ֵ��������ͣ�֧�ֻ����.*/
} PVR_CAPABILITY_S;

/**Index type*//** CNcomment: �������� */
typedef enum _PVR_REC_INDEX_TYPE_E
{
    PVR_REC_INDEX_TYPE_NONE,      /**<No index is created. You need to select this type when recording all streams.*//**<CNcomment: <����������ȫ����¼�Ƶ�ʱ����ʹ�ô�����  */
    PVR_REC_INDEX_TYPE_VIDEO,     /**<The index is created based on videos.*//**<CNcomment: <�����Ƶ���������� */
    PVR_REC_INDEX_TYPE_AUDIO,     /**<The index is created based on audios. *//**<CNcomment: <�����Ƶ���������� */
    PVR_REC_INDEX_TYPE_BUTT       /**<Invalid*//**<CNcomment: <��Ч���������͡�   */
} PVR_REC_INDEX_TYPE_E;

/** Cipher algorithm */
/** CNcomment:CIPHER�����㷨 */
typedef enum _PVR_CIPHER_ALG_E
{
    CIPHER_ALG_DES           = 0x0,  /**< Data encryption standard (DES) algorithm */     /**< CNcomment: DES�㷨 */
    CIPHER_ALG_3DES          = 0x1,  /**< 3DES algorithm */                               /**< CNcomment: 3DES�㷨 */
    CIPHER_ALG_AES           = 0x2,  /**< Advanced encryption standard (AES) algorithm */ /**< CNcomment: AES�㷨 */
    CIPHER_ALG_BUTT          = 0x3
} PVR_CIPHER_ALG_E;

/**Encryption or decryption configuration of the PVR*//** CNcomment:  PVR�ӽ������� */
typedef struct _PVR_CIPHER_S
{
    BOOL                       bDoCipher;                                                 /**<Whether to perform encryption or decryption. When this parameter is set to HI_FALSE, other parameters are invalid.*//**<CNcomment:  �Ƿ���м��ܻ��߽��ܣ���������ΪHI_FALSEʱ��������û������ */
    PVR_CIPHER_ALG_E  enType;                                                      /**<Algorithm for encryption or decryption*//**<CNcomment: ���ܻ��߽�����㷨���� */
    U8                            au8Key[PVR_HAL_MAX_CIPHER_KEY_LEN];    /**<In normal PVR,it's cipher key.If advance security PVR, it's Keyladder's first session key*//**<CNcomment: ��ͨPVR�����У���ΪCipher����Կ���߰�ȫPVR�����У���ΪKeyladder��һ���Ự��Կ */
    U32                          u32KeyLen;                                                 /**<Cipher key length*//**<CNcomment: ��Կ���� */
} PVR_CIPHER_S;

/**Attributes of a recording channel*//** CNcomment: ¼��ͨ���������ݽṹ */
typedef struct _PVR_REC_OPENPARAMS_S
{
    PVR_REC_INDEX_TYPE_E    enIndexType;                        /**<Index type, static attribute.*//**<CNcomment:  �������ͣ���̬���ԡ� */
    AV_VID_STREAM_TYPE_E    enVidType;                          /**<Video encoding protocol with which the stream (for which an index is to be created) complies. The protocol (static attribute) needs to be set only when the index type is PVR_REC_INDEX_TYPE_VIDEO.*/
    U32                     u32IndexPid;                        /**<Index PID, static attribute.*//**<CNcomment:  ����PID����̬����*/
    U32                     u32DavBufSize;                      /**<Size (in byte) of a data stream buffer, static attribute.*//**<CNcomment:  ��������������С����λΪByte����̬���ԡ�  */
    U32                     u32ScdBufSize;                      /**<Size (in byte) of an index data buffer, static attribute.*//**<CNcomment:  �������ݻ�������С����λΪByte����̬���ԡ�*/
    U32                     u32UsrDataInfoSize;                 /**<Size (in byte) of the private user data, static attribute.*//**<CNcomment:  �û�˽�����ݴ�С����λΪByte����̬���ԡ�  */
    PVR_STREAM_TYPE_E       enStreamType;                       /**<Type of the data to be recorded, static attribute.*//**<CNcomment: ��¼�Ƶ��������ͣ���̬���ԡ�*/
    PVR_CIPHER_S            stEncryptCfg;                       /**<Stream encryption configuration, static attribute.*//**<CNcomment: ��������������Ϣ����̬���ԡ�*/
    U64                     u64MaxFileSize;                     /**<Size of the file to be recorded, static attribute. If the value is 0, it indicates that there is no limit on the file size. The minimum file size is 5242880 bytes (5 MB). If the disk space is sufficient, it is recommended to set the file size to a value greater than 512 MB. The file size cannot be 0 in rewind mode. */
    /**<CNcomment: ��¼�Ƶ��ļ���С��Ϊ0ʱ��ʾ�����ƣ���̬���ԡ���СֵΪ50M,������̿ռ��㹻�Ļ����Ƽ�����Ϊ512M���ϡ�����Ϊ����ʱ��������ļ���С���ļ�����ʱ�䶼����Ϊ0�� */
    U64                     u64MaxTimeInMs;                     /**<Max play time of the file to be recorded, static attribute. If the value is 0, it indicates that there is no limit on the file play time. The minimum file time is 60*1024 MS (1 Min).  The file size  and file time cannot both be 0 in rewind mode.*/
    /**<CNcomment: ��¼�Ƶ��ļ��������ʱ�䳤�ȣ�Ϊ0ʱ��ʾ�����ƣ���̬���ԡ���С����ʱ��Ϊ60*1024����(1����)������ģʽ�£����ܽ��ļ�����С���ļ������ʱ��ͬʱ����Ϊ0��*/
    BOOL                    bRewind;                            /**<Whether to rewind, static attribute. If this item is set to HI_TRUE, the PVR rewinds to the file header to record streams after the recorded file size reaches u64MaxFileSize. If this item is set to HI_FALSE, the PVR stops recording after the recorded file size reaches u64MaxFileSize.*/
    /**<CNcomment: �Ƿ���ƣ���̬���ԡ�������ΪHI_TRUE��¼���ļ���С����u64MaxFileSize�󣬻���Ƶ��ļ�ͷ��������¼�ƣ�������ΪHI_FALSE����¼���ļ���С����u64MaxFileSize�󣬻�ֹͣ¼�ơ�*/
    CHAR                    szFileName[PVR_FILE_NAME_LENGTH];   /**<Name of a stream file, static attribute*//**<CNcomment: �����ļ�������̬���ԡ�*/
    U32                     u32FileNameLen;                     /**<Length of a stream file name, static attribute. You need to set the item to strlen (szFileName).*//**<CNcomment: �����ļ������ȣ���̬���ԡ�ȡֵΪstrlen��szFileName������ */
    U32                     u32Reserved;
} PVR_REC_OPENPARAMS_S;

/**Struct of record close parameters*/
/**CNcomment:¼��ͨ���رղ���   */
typedef  struct _PVR_REC_CLOSECHNPARAMS_S
{
    U8      u8Dummy; /*!<  �Ժ���չ�� */
} PVR_REC_CLOSECHNPARAMS_S;


/**Status of a recording channel, INVALID -> INIT -> RUNNING -> STOPPING ->    STOP ->    INVALID  (saveIndex)  (saveStream)*/
/**CNcomment: ¼��ͨ����״̬ */
typedef enum _PVR_REC_STATE_E
{
    PVR_REC_STATE_INVALID = 0,    /**<Not initialized*//**<CNcomment:  δ��ʼ����    */
    PVR_REC_STATE_INIT,           /**<Initialized*//**<CNcomment:  ��ʼ����      */
    PVR_REC_STATE_RUNNING,        /**<Recording*//**<CNcomment:  ¼���С�      */
    PVR_REC_STATE_PAUSE,          /**<Pause*//**<CNcomment:  ��ͣ��        */
    PVR_REC_STATE_STOPPING,       /**<Stopping*//**<CNcomment: ����ֹͣ��    */
    PVR_REC_STATE_STOP,           /**<<Stopped*//**<CNcomment: �Ѿ�ֹͣ��    */
    PVR_REC_STATE_BUTT            /**<Invalid*//**<CNcomment: ��Ч��״ֵ̬��*/
} PVR_REC_STATE_E;

/**Status of a recording channel.
The following describes the relationships among u32CurTimeInMs, u32StartTimeInMs, and u32EndTimeInMs by taking examples:
1. Assume that the total recording time is 10000 ms, and no rewind occurs. In this case, u32StartTimeInMs is 0 ms, u32EndTimeInMs is 10000 ms, and u32CurTimeInMs is 10000 ms.
2. Assume that the total recording time is 10000 ms, and rewind occurs at 8000 ms. In this case, u32StartTimeInMs is 2000 ms, u32EndTimeInMs is 10000 ms, and u32CurTimeInMs is 8000 ms.
*/
/** CNcomment:¼��ͨ��״̬���ݽṹ.
��u32CurTimeInMs��u32StartTimeInMs��u32EndTimeInMs���ߵĹ�ϵ����˵�����£�
1������ӿ�ʼ¼�ƺ�һ��¼����10000���룬���û�з������ƣ���ôu32StartTimeInMs Ϊ0��u32EndTimeInMs Ϊ10000�� u32CurTimeInMsΪ10000��
2������ӿ�ʼ¼�ƺ�һ��¼����10000���룬�����ڵ�8000�����ʱ�����˻��ƣ���ôu32StartTimeInMs Ϊ2000��u32EndTimeInMs Ϊ10000�� u32CurTimeInMsΪ8000��
*/
typedef struct _PVR_REC_STATUS_S
{
    PVR_REC_STATE_E          enState;                 /**<Current status of a channel*//**<CNcomment: ͨ��������״̬��    */
    U32                      u32Reserved;             /**<Reserved, for alignment*//**<CNcomment: �������������롣    */
    U64                      u64CurWritePos;          /**<Current recording position of file, in byte*//**<CNcomment: ��ǰ¼��д�ļ���λ�ã���λ��byte���� */
    U32                      u32CurWriteFrame;        /**<Number of currently recorded frames*//**<CNcomment: ��ǰ¼�Ƶ�֡����                  */
    U32                      u32CurTimeInMs;          /**<Current recording time (in ms). The value is the valid time for recording the file.*//**<CNcomment: ��ǰ¼�Ƶĺ���������ֵΪ¼���ļ���ʵ����Чʱ����*/
    U32                      u32StartTimeInMs;        /**<Actual start time for recording files. Before the recording is rewound, the time is that of the first frame; after the recording is rewound, the time is the rewind time.*//**<CNcomment: ¼���ļ���ʵ����ʼ�㡣¼�ƻ���ǰ��Ϊ��һ֡ʱ�䣻¼�ƻ��ƺ�Ϊ���Ƶ��ʱ�䡣 */
    U32                      u32EndTimeInMs;          /**<Time of the end frame in the recorded file. Before the recording is rewound, the time is that of the last frame.*//**<CNcomment:¼���ļ��н���֡��ʱ�䣬û�л���ǰ�����һ֡��ʱ�䡣    */
    //UNF_PVR_BUF_STATUS_S     stRecBufStatus;          /**<Status of the recording channel buffer*//**<CNcomment:¼��ͨ��������״̬��    */
} PVR_REC_STATUS_S;

/**Attributes of a playing channel*//** CNcomment:����ͨ������ */
typedef struct _PVR_PLAY_OPENPARAMS_S
{
    PVR_STREAM_TYPE_E    enStreamType;                         /**<Type of the played stream, static attributes. At present, only the TS is supported.*//**<CNcomment: �����������ͣ�Ŀǰֻ֧��TS����̬���ԡ�*/
    PVR_CIPHER_S         stDecryptCfg;                         /**<Decryption configuration, static attribute                  *//**<CNcomment: �������ã���̬���ԡ�                  */
    CHAR                     szFileName[PVR_MAX_FILENAME_LEN];     /**<Name of the file that contains the streams to be played, static attribute        *//**<CNcomment: �������������ļ�������̬���ԡ�        */
} PVR_PLAY_OPENPARAMS_S;

/**Speed of PVR play*/
/**CNcomment: PVR���ű���*/
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
/**CNcomment: PVR����trick����*/
typedef enum  _PVR_PLAY_TRICKDIRECTION_E
{
    PVR_PLAY_TRICK_BACK = 0,
    PVR_PLAY_TRICK_ONWARD
} PVR_PLAY_TRICKDIRECTION_E;

/**Trick mode of PVR play*/
/**CNcomment: PVR����trickģʽ*/
typedef enum _PVR_PLAY_TRICK_MODE_E
{
    PVR_PLAY_TRICKMODE_NORMAL = 0,
    PVR_PLAY_TRICKMODE_SPEED,
    PVR_PLAY_TRICKMODE_STEPFRAME
} PVR_PLAY_TRICK_MODE_E;

/**Speed of PVR play*/
/**CNcomment: PVR���ٲ�������*/
typedef enum  _PVR_PLAY_SPEEDCHANGE_E
{
    PVR_PLAY_SPEED_SLOW = 0,    /*!< ����*/
    PVR_PLAY_SPEED_FAST         /*!< �첥*/
} PVR_PLAY_SPEEDCHANGE_E;

/**Trick parameters of PVR play*/
/**CNcomment: PVR����trick����*/
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
/**CNcomment: PVR����seek����*/
typedef enum _PVR_PLAY_SEEKTYPE_E
{
    PVR_PLAY_SEEKTYPE_STAMPTIME,   /*!<  by time stamp */
    PVR_PLAY_SEEKTYPE_UNKOWN
} PVR_PLAY_SEEKTYPE_E;

/**Seek mode of PVR play*/
/**CNcomment: PVR����seekģʽ*/
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
 *note 1. m_offset:������ʷԭ��,m_seekmode=PVR_PLAY_SEEKMODE_END ʱ, m_offset ����ֵ,
 *         ��ʾ���ļ���ʼ����ƫ��, ����;���ƽ̨�߼��෴, ��ҪHDI �ڲ�ת���ɸ�ֵ.
 *        2. �ļ���ʼ�ǵ�ǰ¼���ļ���ʵ����ʼ��,¼�ƻ���ǰ,Ϊ��һ֡λ��,
 *             ¼�ƻ��ƺ�,Ϊ���Ƶ��λ��.
 *        3. �ļ������ǵ�ǰ¼���ļ��н���֡��λ��, û�л���ǰ�����һ֡��λ��.
 */
typedef struct _PVR_PLAY_SEEKPARAMS_S
{
    PVR_PLAY_SEEKTYPE_E    enType;
    PVR_PLAY_SEEKMODE_E    enSeekMode;
    S64                    s64Offset;
} PVR_PLAY_SEEKPARAMS_S;

/**Status of a playing channel*//** CNcomment: ����ͨ����״̬  */
typedef enum _PVR_PALY_STATE_E
{
    PVR_PLAY_STATE_INVALID,       /**<Not initialized*//**<CNcomment: δ��ʼ��            */
    PVR_PLAY_STATE_INIT,          /**<Initialized*//**<CNcomment: ��ʼ��              */
    PVR_PLAY_STATE_PLAY,          /**<Normal playing*//**<CNcomment: ����������          */
    PVR_PLAY_STATE_PAUSE,         /**<Pause*//**<CNcomment: ��ͣ                */
    PVR_PLAY_STATE_FF,            /**<Fast forward*//**<CNcomment: ���                */
    PVR_PLAY_STATE_FB,            /**<Fast backward*//**<CNcomment: ����                */
    PVR_PLAY_STATE_SF,            /**<Slow forward*//**<CNcomment: ����                */
    PVR_PLAY_STATE_SB,            /**<Slow backward*//**<CNcomment:����         */
    PVR_PLAY_STATE_STEPF,         /**<Step forward*//**<CNcomment:��֡����            */
    PVR_PLAY_STATE_STEPB,         /**<Step backward*//**<CNcomment: ��֡����            */
    PVR_PLAY_STATE_STOP,          /**<Stop*//**<CNcomment: ֹͣ                */
    PVR_PLAY_STATE_BUTT           /**<Invalid*//**<CNcomment: ��Ч��״ֵ̬        */
} PVR_PLAY_STATE_E;

/**Status of a playing channel*//** CNcomment:����ͨ����״̬ */
typedef struct _PVR_PLAY_STATUS_S
{
    PVR_PLAY_STATE_E        enState;                /**<Status of a playing channel*//**<CNcomment:����ͨ��״̬��*/
    PVR_PLAY_TRICKPARAMS_S  stTrickParam;           /**<Parameters of trick*//**<CNcomment:���ŵ�trick������*/
    U32                     u32CurPlayTimeInMs;     /**<PTS of the current frame, in ms*//**<CNcomment: ��ǰ����֡��PTS, ��λ���롣*/
} PVR_PLAY_STATUS_S;

/**Information about a stream file recorded by the PVR*//** CNcomment:  PVR¼�Ƶ������ļ���Ϣ */
typedef struct _PVR_FILE_ATTR_S
{
    PVR_REC_INDEX_TYPE_E          enIdxType;          /**<Index type*//**<CNcomment:  �������� */
    U32                           u32FrameNum;        /**<For a video file: number of frames in the file. For an audio file: number of PESs in the file*//**<CNcomment:  ����Ƶ�ļ����ļ�֡��;����Ƶ�ļ����ļ��е�PES�� */
    U32                           u32StartTimeInMs;   /**<Start time of the file, in ms*//**<CNcomment: �ļ����ݵ���ʼʱ�䣬��ʼ֡PTS����λms */
    U32                           u32EndTimeInMs;     /**<End time of the file, in ms*//**<CNcomment: �ļ����ݵĽ���ʱ�䣬����֡PTS����λms  */
    U64                           u64ValidSizeInByte; /**<Valid data length of the file, in byte *//**<CNcomment:  �ļ�����Ч���ݳ��ȣ���λbyte */
} PVR_FILE_ATTR_S;

/**Type of the PVR event*//** CNcomment:  PVR�¼����� */
typedef enum _PVR_EVENT_E
{
    PVR_EVENT_PLAY_EOF        = 0x001,          /**<A file is played at the end of file (EOF).*//**<CNcomment:  ���ŵ��ļ�β */
    PVR_EVENT_PLAY_SOF        = 0x002,          /**<A file is played to the start of file (SOF).*//**<CNcomment:  ���˵��ļ�ͷ */
    PVR_EVENT_PLAY_ERROR      = 0x003,          /**<An internal error occurs during playing.*//**<CNcomment:  �����ڲ����� */
    PVR_EVENT_PLAY_REACH_REC  = 0x004,          /**<The playing speed reaches the recording speed during time shift.*//**<CNcomment:  ʱ�Ƶ�ʱ�򲥷�׷��¼�� */
    PVR_EVENT_PLAY_RESV       = 0x00f,          /**<Reserved*//**<CNcomment:  ���� */
    PVR_EVENT_REC_DISKFULL    = 0x010,          /**<The disk is full.*//**<CNcomment:  ������ */
    PVR_EVENT_REC_ERROR       = 0x011,          /**<An internal error occurs during recording.*//**<CNcomment:  ¼���ڲ����� */
    PVR_EVENT_REC_OVER_FIX    = 0x012,          /**<The length of the recorded data reaches the specified length. This event is available only in non-rewind mode.*//**<CNcomment: ¼�Ƴ��ȴﵽָ���ĳ���,ֻ�зǻ���¼�Ʋ�������¼� */
    PVR_EVENT_REC_REACH_PLAY  = 0x013,          /**<The recording speed reaches the playing speed during time shift.*//**<CNcomment:  ʱ�Ƶ�ʱ��¼��׷�ϲ��� */
    PVR_EVENT_REC_DISK_SLOW   = 0x014,          /**<The storage speed of the disk is slower than the recording speed.*//**<CNcomment: ���̴洢�ٶ�����¼���ٶ� */
    PVR_EVENT_REC_RESV        = 0x01f,          /**<Reserved*//**<CNcomment:  ���� */
    PVR_EVENT_BUTT            = 0x020           /**<Invalid event type*//**<CNcomment: ��Ч���¼����� */
} PVR_EVENT_E;

/**Callback function of PVR event*//** CNcomment: PVR�¼��ص����� */
typedef void (*pvr_eventCallBack)(U32 u32ChnID, PVR_EVENT_E EventType, S32 s32EventValue, VOID* args);

#ifdef ANDROID_HAL_MODULE_USED
/**PVR module structure(Android require)*/
/**CNcomment:PVRģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _PVR_MODULE_S
{
    struct hw_module_t stCommon;
} PVR_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_PVR*/
/** @{*/  /** <!-- -[HAL_PVR]=*/

/**PVR device structure*//** CNcomment:PVR�豸�ṹ*/
typedef struct _PVR_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief PVR module init.CNcomment: ģ���ʼ������ CNend
    \attention \n
    N/A
    \param[in] pstInitParams  PVR module init param.CNcomment:��ʼ��ģ����� CNend
    \retval ::SUCCESS Success  CNcomment: �ɹ� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A
    */
    S32  (*pvr_init)(struct _PVR_DEVICE_S* pstDev, const PVR_RECINIT_PARAMS_S*   const  pstInitParams);

    /**
    \brief Terminate PVR module.CNcomment: PVRģ����ֹ CNend
    \attention \n
    N/A
    \param[in] pstTermParams Terminate param,  if NULL, force to terminate.CNcomment:��ֹģ�������ΪNULL  ��ʾǿ����ֹ CNend
    \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend
    \retval ::ERROR_NOT_INITED    The specified channel is not initialized.  CNcomment:ģ��δ��ʼ�� CNend
    \retval ::ERROR_INVALID_PARAM The pointer is null. CNcomment:�������� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A
    */
    S32  (*pvr_term)(struct _PVR_DEVICE_S* pstDev, const PVR_TERM_PARAMS_S* const  pstTrmParams);

    /**
    \brief Get the capability of pvr module. CNcomment:��ȡPVRģ���豸���� CNend
    \attention \n
    CNcomment: ��CNend
    \param[in] pstCapability Capability param.CNcomment:ģ���������� CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::PVR_CAPABILITY_S

    \par example
    \code
    \endcode
    */
    S32  (*pvr_get_capability)(struct _PVR_DEVICE_S* pstDev, PVR_CAPABILITY_S*   const  pstCapability);

    /**
    \brief Open a record channel. CNcomment:����һ��pvr record ͨ��.open����stop״̬ CNend
    \attention \n
    \param[out] pu32RecchnId Pointer to a record channel ID.CNcomment:ָ��¼��ͨ��ID��ָ�� CNend
    \param[in] enDmxId demux ID.CNcomment:demux ID CNend
    \param[in] pstRecParams record parameters.CNcomment:¼�Ʋ��� CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::ERROR_PVR_REC_INVALID_DMXID demux ID is invalid .CNcomment:��Ч��demux ID��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::PVR_REC_OPENPARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*pvr_rec_open)(struct _PVR_DEVICE_S* pstDev, U32* const  pu32RecchnId, DMX_ID_E const enDmxId, const PVR_REC_OPENPARAMS_S* const pstRecParams);

    /**
    \brief Close a record channel. CNcomment:�ر�һ��PVR¼��ͨ�� CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:¼��ͨ��ID CNend
    \param[in] pstReccloseParams close parameters.CNcomment:�ر�¼��ͨ������ CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::PVR_REC_CLOSECHNPARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*pvr_rec_close)(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId, const PVR_REC_CLOSECHNPARAMS_S*  pstReccloseParams);

    /**
    \brief start to record. CNcomment:��ʼ¼�� CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:¼��ͨ��ID CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32 (*pvr_rec_start)(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId);

    /**
    \brief stop record. CNcomment:ֹͣ¼�� CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:¼��ͨ��ID CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32 (*pvr_rec_stop)(struct _PVR_DEVICE_S* pstDev, const U32 u32RecchnId);

    /**
    \brief pause record. CNcomment:��ͣ¼�� CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:¼��ͨ��ID CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_rec_pause)(struct _PVR_DEVICE_S* pstDev, const U32  u32RecchnId);

    /**
    \brief resume record. CNcomment:�ָ�¼�� CNend
    \attention \n
    \param[in] u32RecchnId record channel ID.CNcomment:¼��ͨ��ID CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_rec_resume)(struct _PVR_DEVICE_S* pstDev, const U32  u32RecchnId);

    /**
    \brief Obtains the status of a recording channel.CNcomment:  ��ȡ¼��ͨ��״̬ CNend
    \attention \n
    N/A
    \param[in] u32ChnID  Channel ID  CNcomment:ͨ���� CNend
    \param[out] pstRecStatus   Pointer to the recording status   CNcomment:¼��״̬��Ϣָ�� CNend
    \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend
    \retval ::HI_ERR_PVR_NOT_INIT    The PVR recording module is not initialized.  CNcomment:PVR¼��ģ��δ��ʼ�� CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID   The channel ID is invalid.   CNcomment: ͨ���ŷǷ� CNend
    \retval ::HI_ERR_PVR_CHN_NOT_INIT    The specified channel is not initialized.  CNcomment:ָ����ͨ��δ��ʼ�� CNend
    \retval ::HI_ERR_PVR_NUL_PTR        The pointer is null. CNcomment:ָ�����Ϊ�� CNend
    \see \n
    N/A
    */
    S32  (*pvr_rec_getstatus)(struct _PVR_DEVICE_S* pstDev, U32  u32RecchnId, PVR_REC_STATUS_S* pstRecStatus);

    /**
    \brief add rec pid.CNcomment:  ����Ҫ¼�Ƶ�PID CNend
    \attention \n
    N/A
    \param[in] enDmxId  Demux ID  CNcomment:Demux �� CNend
    \param[in] u32RecchnId  record channel ID  CNcomment:¼��ͨ���� CNend
    \param[in] u32Pid  pid CNcomment:pid�� CNend
    \param[in] enType  pid channel type CNcomment:pidͨ������CNend
    \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend
    \retval ::HI_ERR_PVR_NOT_INIT    The PVR recording module is not initialized.  CNcomment:PVR¼��ģ��δ��ʼ�� CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID   The channel ID is invalid.   CNcomment: ͨ���ŷǷ� CNend
    \retval ::HI_ERR_PVR_CHN_NOT_INIT    The specified channel is not initialized.  CNcomment:ָ����ͨ��δ��ʼ�� CNend
    \retval ::HI_ERR_PVR_NUL_PTR        The pointer is null. CNcomment:ָ�����Ϊ�� CNend
    \see \n
    N/A
    */
    S32  (*pvr_rec_addpid)(struct _PVR_DEVICE_S* pstDev, DMX_ID_E  enDmxId,  U32  u32RecchnId, U32 u32Pid, DMX_CHANNEL_TYPE_E enType);

    /**
    \brief del rec pid.CNcomment:  ɾ��¼��PID CNend
    \attention \n
    N/A
    \param[in] enDmxId  Demux ID  CNcomment:Demux �� CNend
    \param[in] u32RecchnId  record channel ID  CNcomment:¼��ͨ���� CNend
    \param[in] u32Pid  pid CNcomment:pid�� CNend
    \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend
    \retval ::HI_ERR_PVR_NOT_INIT    The PVR recording module is not initialized.  CNcomment:PVR¼��ģ��δ��ʼ�� CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID   The channel ID is invalid.   CNcomment: ͨ���ŷǷ� CNend
    \retval ::HI_ERR_PVR_CHN_NOT_INIT    The specified channel is not initialized.  CNcomment:ָ����ͨ��δ��ʼ�� CNend
    \retval ::HI_ERR_PVR_NUL_PTR        The pointer is null. CNcomment:ָ�����Ϊ�� CNend
    \see \n
    N/A
    */
    S32  (*pvr_rec_delpid)(struct _PVR_DEVICE_S* pstDev, DMX_ID_E  enDmxId,  U32  u32RecchnId, U32 u32Pid);

    /**
    \brief Open a PVR play channel. CNcomment:����һ��PVR����ͨ�� CNend
    \attention \n
    \param[out] pu32PlaychnId Pointer to a play channel ID.CNcomment:ָ�򲥷�ͨ��ID��ָ�� CNend
    \param[in] enDmxId demux ID.CNcomment:demux ID CNend
    \param[in] pstPlayParams play parameters.CNcomment:���Ų��� CNend
    \param[in] u32TsBufferId TS buffer ID.CNcomment:TS Buffer��� CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::ERROR_PVR_PLAY_INVALID_DMXID demux ID is invalid .CNcomment:��Ч��demux ID��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::dmx_tsbuffer_create

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_open)(struct _PVR_DEVICE_S* pstDev, U32* const pu32PlaychnId, const PVR_PLAY_OPENPARAMS_S* const pstPlayParams, HANDLE hAV, U32 u32TsBufferId);

    /**
    \brief Close a PVR play channel. CNcomment:�ر�һ��PVR����ͨ�� CNend
    \attention \n
    \param[out] pu32PlaychnId Pointer to a play channel ID.CNcomment:ָ�򲥷�ͨ��ID��ָ�� CNend
    \param[in] enDmxId demux ID.CNcomment:demux ID CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::ERROR_PVR_PLAY_INVALID_DMXID demux ID is invalid .CNcomment:��Ч��demux ID��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_close)(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);

    /**
    \brief start to PVR play. CNcomment:��ʼPVR�ط� CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR�ط�ͨ��ID CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_start)(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);

    /**
    \brief stop PVR play. CNcomment:ֹͣPVR�ط� CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR�ط�ͨ��ID CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_stop)(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);

    /**
    \brief pause PVR play. CNcomment:��ͣPVR�ط� CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR�ط�ͨ��ID CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_pause)(struct _PVR_DEVICE_S* pstDev, const U32  u32PlaychnId);

    /**
    \brief resume PVR play. CNcomment:�ָ�PVR�ط� CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR�ط�ͨ��ID CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    N/A

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_resume)(struct _PVR_DEVICE_S* pstDev,  const U32  u32PlaychnId);

    /**
    \brief start PVR trick playing mode. CNcomment:���ô˽ӿڿ��Խ����ؼ����ţ������п�������ˡ����š��������ŵȲ��� CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR�ط�ͨ��ID CNend
    \param[in] pstPlayTrickMode trick parameters.CNcomment:�ؼ����Ų��� CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    PVR_PLAY_TRICKPARAMS_S

    \par example
    \code
    \endcode
    */
    S32  (*pvr_play_trick)(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, const PVR_PLAY_TRICKPARAMS_S* pstPlayTrickMode);

    /**
    \brief Seeks a specified position to play. CNcomment:��λ��ָ��λ�ý��в��� CNend
    \attention \n
    \param[in] u32PlaychnId PVR play channel ID.CNcomment:PVR�ط�ͨ��ID CNend
    \param[in] pstPlaySeekParams seek parameters.CNcomment:��λ���� CNend
    \retval ::HI_SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:��������CNend
    \retval ::ERROR_NULL_PTR Parameter is NULL .CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    PVR_PLAY_SEEKPARAMS_S

    \par example
    \code
    \endcode
    */

    S32  (*pvr_play_seek)(struct _PVR_DEVICE_S* pstDev, const U32 u32PlaychnId, const PVR_PLAY_SEEKPARAMS_S* pstPlaySeekParams);

    /**
    \brief Obtains the playing status of the PVR. CNcomment:��ȡPVR�طŵ�״̬ CNend
    \attention \n
    Before calling this API to obtain the playing status, you must create a player.
    CNcomment:��ȡ���ŵ�״̬��ע���ڲ���������֮����� CNend
    \param[in] u32ChnID
    \param[in] pstStatus
    \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend
    \retval ::HI_ERR_PVR_NOT_INIT  The PVR recording module is not initialized CNcomment: PVR¼��ģ��δ��ʼ�� CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID The channel ID is invalid.  CNcomment:ͨ���ŷǷ� CNend
    \retval ::HI_ERR_PVR_BUSY   The system is busy. Please try again later. CNcomment:ϵͳæ��������������������ԡ� CNend
    \see \n
    N/A
    */
    S32  (*pvr_play_getstatus)(struct _PVR_DEVICE_S* pstDev, U32 u32PlaychnId, PVR_PLAY_STATUS_S* const  pstStatus);

    /**
    \brief Obtains the information about the stream file recorded by the PVR based on the ID of the playing channel.  CNcomment:ͨ������ͨ��ID����ȡPVR¼�Ƶ������ļ���Ϣ CNend
    \attention \n
    You can call this API to obtain the fixed information about the file to be played. However, the information is variable in the time-shift scenario.
    You can call ::HI_UNF_PVR_PlayGetStatus to obtain the current playing position during playing.\n
    You can call ::HI_UNF_PVR_RecGetStatus to obtain the current recording position during time shifting.
    In addition, if both recording and playing do not start, you can call ::HI_UNF_PVR_GetFileAttrByFileName to obtain the attributes of a file.
    CNcomment: ���ô˽ӿ�������ȡ�����ļ��Ĺ̶���Ϣ�����Ƕ���ʱ�Ƴ�����Щ��Ϣ�ǲ��ϱ仯��
    �ڲ��Ź����п���ͨ��::HI_UNF_PVR_PlayGetStatus�ӿڻ�ȡ��ǰ�Ĳ���λ�� \n
    ��ʱ�ƹ����п���ͨ��::HI_UNF_PVR_RecGetStatus�ӿڻ�ȡ��ǰ��¼��λ��
    ���⣬�����û������¼��Ҳû���������ţ�����ͨ��::HI_UNF_PVR_GetFileAttrByFileName�ӿڻ�ȡ�ļ����� CNend
    \param[in] u32ChnID  Channel ID  CNcomment:ͨ���� CNend
    \param[in] pAttr Pointer to the playing status
    \param[in] pAttr   CNcomment:����״̬��Ϣָ�� CNend
    \retval ::HI_SUCCESS  Success  CNcomment:�ɹ� CNend
    \retval ::HI_ERR_PVR_NOT_INIT            The PVR playing module is not initialized.  CNcomment:PVR����ģ��δ��ʼ�� CNend
    \retval ::HI_ERR_PVR_NUL_PTR           The pointer is null.   CNcomment: ��ָ����� CNend
    \retval ::HI_ERR_PVR_INVALID_CHNID      The channel ID is invalid.   CNcomment:ͨ���ŷǷ� CNend
    \retval ::HI_ERR_PVR_CHN_NOT_INIT        The specified channel is not initialized. CNcomment: ָ����ͨ��δ��ʼ�� CNend
    \retval ::HI_ERR_PVR_FILE_CANT_OPEN      The file cannot be opened.  CNcomment:�޷����ļ� CNend
    \retval ::HI_ERR_PVR_FILE_CANT_READ    The file cannot be read.   CNcomment: �޷����ļ� CNend
    \see \n
    N/A
    */

    S32  (*pvr_play_getfileattrbychannel)(struct _PVR_DEVICE_S* pstDev, U32 u32PlaychnId, PVR_FILE_ATTR_S* const pAttr);

    /**
    \brief
    Obtains the information about a stream file.
    By calling this API, you can obtain the information about a specified stream file without creating a playing channel.
    CNcomment:��ȡ�����ļ���Ϣ�����ô˽ӿڿ����ڲ����벥��ͨ��������»�ȡָ�������ļ�����Ϣ CNend
    \attention \n
    pFileName points to the name of a stream file rather than an index file.\n
    You can call this API to obtain the attributes of a stream file at any time.
    CNcomment:ָ�������ļ��������������ļ���.�κ�ʱ�򶼿��Ե��ô˽ӿڻ�ȡ�����ļ������� CNend
    \param[in] pFileName Name of a stream file  CNcomment:�����ļ��� CNend
    \param[in] pAttr   Pointer to the playing status   CNcomment:����״̬��Ϣָ�� CNend
    \retval ::HI_SUCCESS  Success  CNcomment:�ɹ� CNend
    \retval ::HI_ERR_PVR_NUL_PTR       The pointer is null.    CNcomment:��ָ����� CNend
    \retval ::HI_ERR_PVR_FILE_CANT_OPEN  The file cannot be opened.  CNcomment:�޷����ļ� CNend
    \retval ::HI_ERR_PVR_FILE_CANT_READ   The file cannot be read. CNcomment:�޷����ļ� CNend
    \see \n
    N/A
    */
    S32  (*pvr_play_getfileattrbyfilename)(struct _PVR_DEVICE_S* pstDev, const CHAR* pFileName, PVR_FILE_ATTR_S* const pAttr);

    /**
    \brief  Writes the user data. CNcomment: д���û����� CNend
    \attention \n
    pFileName points to the name of a stream file rather than an index file.\n
    The value of u32UsrDataLen cannot be greater than that of u32UsrDataInfoSize. The value of u32UsrDataInfoSize (one of recording channel attributes) is set before a file is recorded.
    The user data is saved in the index file.\n
    You need to write the user data after starting a recording channel.
    CNcomment:pFileNameָ�������ļ��������������ļ��� \n
    u32UsrDataLen��ȡֵ���ܴ���¼�ƴ��ļ�ʱ��¼��ͨ����������ָ����u32UsrDataInfoSize��ȡֵ \n
    �û����ݱ������������ļ��� \n
    ��������¼��ͨ������д���û�������Ϣ CNend
    \param[in] pFileName Name of a stream file CNcomment: �����ļ��� CNend
    \param[in] pInfo    Pointer to the user data. The memory is allocated by customers. CNcomment:�û�����ָ�룬�ռ����û����� CNend
    \param[in] u32UsrDataLen   Length of the user data CNcomment: �û����ݳ��� CNend
    \retval ::HI_SUCCESS  Success  CNcomment:�ɹ� CNend
    \retval ::HI_ERR_PVR_NUL_PTR       The pointer is null.   CNcomment: ��ָ����� CNend
    \retval ::HI_ERR_PVR_FILE_CANT_OPEN   The file cannot be opened.CNcomment:�޷����ļ� CNend
    \retval ::HI_ERR_PVR_FILE_CANT_READ  The file cannot be read.  CNcomment:�޷����ļ� CNend
    \retval ::HI_ERR_DMX_INVALID_PARA    The parameter is invalid.  CNcomment: �����Ƿ� CNend
    \see \n
    N/A
    */
    S32  (*pvr_usrdata_setbyfilename)(struct _PVR_DEVICE_S* pstDev, const CHAR* pFileName, U8* pInfo, U32 u32UsrDataLen);

    /**
    \brief  Reads the user data. CNcomment: ��ȡ�û����� CNend
    \attention \n
    pFileName points to the name of a stream file rather than an index file.\n
    The return value of pUsrDataLen indicates the length of the obtained user data. The value is the smaller one between the values of u32BufLen and actual length of the user data.
    The actual length of the user data is greater than or equal to the maximum length of the user data set by calling HI_UNF_PVR_RecCreateChn. In this way, all user data can be read.\n
    The PVR does not save the length of the user data set by calling HI_UNF_PVR_SetUsrDataInfoByFileName, but save the maximum length of the user data set by calling HI_UNF_PVR_RecCreateChn.
    CNcomment:pFileNameָ�������ļ��������������ļ��� \n
    pUsrDataLen���ض�ȡ�����û����ݵĳ��ȣ���ȡֵΪu32BufLen��"ʵ���û����ݳ���"�����еĽ�Сֵ��
    "ʵ���û����ݳ���"����С��HI_UNF_PVR_RecNewChnʱ���õ�����û����ݳ��ȣ��Ա�֤�ܹ���ȫ���û����ݶ��� \n
    PVRģ�鲻����HI_UNF_PVR_SetUsrDataInfoByFileNameʱ������û����ݳ��ȣ�ֻ����HI_UNF_PVR_RecNewChnʱ���õ�����û����ݳ��� CNend
    \param[in] pFileName    Name of a stream file CNcomment:�����ļ��� CNend
    \param[in] pInfo    User data buffer. The memory is allocated by customers.   CNcomment:�û����ݻ��������ռ����û����� CNend
    \param[in] u32BufLen   Buffer length .CNcomment:���������� CNend
    \param[in] pUsrDataLen Actual length of the obtained user data .CNcomment:ʵ�ʶ�ȡ�����û����ݳ��� CNend
    \retval ::HI_SUCCESS  Success  CNcomment:�ɹ� CNend
    \retval ::HI_ERR_PVR_NUL_PTR        The pointer is null.      CNcomment: ��ָ����� CNend
    \retval ::HI_ERR_PVR_FILE_CANT_OPEN    The file cannot be opened. CNcomment:�޷����ļ� CNend
    \retval ::HI_ERR_PVR_FILE_CANT_READ    The file cannot be read.  CNcomment:�޷����ļ� CNend
    \retval ::HI_ERR_DMX_INVALID_PARA      The parameter is invalid.  CNcomment: �����Ƿ� CNend
    \see \n
    N/A
    */

    S32  (*pvr_usrdata_getbyfilename)(struct _PVR_DEVICE_S* pstDev, const CHAR* pFileName, U8* pInfo, U32 u32BufLen, U32* pUsrDataLen);

    /**
    \brief  Registers an event callback function. You can call this API to register a callback function for PVR event. In this way, you can handle the events occurred during PVR recording and playing.
    CNcomment: ע���¼��ص����������ô˽ӿڿ���ע��PVR�¼��Ļص��������Ӷ���PVR¼�ơ����Ź����в������¼����д��� CNend
    \attention \n
    You can call ::HI_UNF_PVR_UnRegisterEvent to deregister an event. If a registered event is not deregistered, it is always valid.
    For the PVR_EVENT_PLAY_REACH_REC message, it is recommended to stop the playing of the PVR by calling the registered callback function, and switch the playing mode to live mode of the AVPLAY.
    If the recording attribute is set to non-rewind, the PVR_EVENT_REC_OVER_FIX message is reported at the end of recording when the recording length reaches the specified length.
    When the recording attribute is set to rewind, the PVR_EVENT_REC_OVER_FIX message is reported during each rewind. In this case, the value of s32EventValue of the message handling callback function is the times of rewind (counting from 1).
    The PVR_EVENT_REC_REACH_PLAY message is reported when the recording speed will reach the playing speed. In this case, the value of s32EventValue is the number of bytes between the recording position and the playing position.
    CNcomment: ����ʹ��::HI_UNF_PVR_UnRegisterEvent����ע��1���¼��������Ѿ�ע����¼���һֱ������Ч
    ����PVR_EVENT_PLAY_REACH_REC��Ϣ�������û���ע��Ļص�������ֹͣPVR���ţ����л���ֱ��ģʽ��AVPLAY���в��š�
    ��¼����������Ϊ�����Ƶ�ʱ��PVR_EVENT_REC_OVER_FIX��Ϣ��¼�Ƴ��ȵ���ָ�����ȣ�����ֹͣ¼�Ƶ�ʱ���ϱ���
    ��¼����������Ϊ���Ƶ�ʱ��PVR_EVENT_REC_OVER_FIX��Ϣ��ÿ�λ��Ƶ�ʱ�򶼻��ϱ�����ʱ����Ϣ����ص�������s32EventValue����ֵΪ���ƵĴ���(��1��ʼ����)��
    PVR_EVENT_REC_REACH_PLAY��Ϣ��¼�Ƽ���׷�ϲ��ŵ�ʱ���ϱ�����ʱ����Ϣ����ص�������s32EventValue����ֵΪ¼��λ�þ��벥��λ�õ��ֽ����� CNend
    \param[in] enEventType  Type of the event to be registered.  CNcomment: ��Ҫע����¼����� CNend
    \param[in] callBack   Event handling callback function.   CNcomment: �¼������� CNend
    \param[in] args      Parameters of a customized callback function.    CNcomment:�û��Զ���ص������Ĳ��� CNend
    \retval ::HI_SUCCESS   Success CNcomment: �ɹ� CNend
    \retval ::HI_ERR_PVR_INTF_EVENT_INVAL   The event is invalid.  CNcomment: �Ƿ����¼� CNend
    \retval ::HI_ERR_PVR_ALREADY         The registering event has been registered.    CNcomment: ���Զ��Ѿ�ע����¼��ٴ�ע�� CNend
    \retval ::HI_ERR_PVR_INTF_EVENT_NOREG    Registration fails because the callback function pointer is incorrect. CNcomment:  �ص�����ָ������޷�ע��ɹ� CNend
    \see \n
    N/A
    */
    S32  (*pvr_event_register)(struct _PVR_DEVICE_S* pstDev, PVR_EVENT_E enEvent, pvr_eventCallBack pCallBack, VOID* pArgs);

    /**
    \brief  Deregisters a PVR event. CNcomment: ȥע��PVR�¼��Ļص����� CNend
    \attention \n
    You can call this API to deregister an event. If a registered event is not deregistered, it is always valid.
    CNcomment: ����ʹ�ô˽ӿ���ȥע��1���¼��������Ѿ�ע����¼���һֱ������Ч CNend
    \param[in] enEventType      Type of the event to be deregistered    CNcomment: ��Ҫȥע����¼����� CNend
    \retval ::HI_SUCCESS   Success  CNcomment:�ɹ� CNend
    \retval ::HI_ERR_PVR_INTF_EVENT_INVAL  The event is invalid. CNcomment: �Ƿ����¼� CNend
    \retval ::HI_ERR_PVR_INTF_EVENT_NOREG  The deregistering event is not registered. CNcomment: ��û��ע����¼�����ȥע�� CNend
    \see \n
    N/A
    */
    S32  (*pvr_event_unregister)(struct _PVR_DEVICE_S* pstDev, PVR_EVENT_E enEvent);

    /**
    \brief  Deletes the stream files and index files generated during recording. CNcomment:ɾ��¼��ʱ���ɵ������ļ��������ļ� CNend
    \attention \n
    pFileName points to the name of a stream file rather than an index file.\n
    After this API is called, the stream files and index files generated during stream recording are deleted.
    If a stream file is greater than 4 GB, multiple files named data.ts, data.ts.0001, data.ts.0002, data.ts.0003, and ... are generated. To delete these files, you only need to enter the file name data.ts.
    CNcomment:pFileNameָ�������ļ��������������ļ���\n
    ���ô˽ӿں�¼�ƴ�����ʱ���ɵ������ļ��������ļ�������ɾ��\n
    ��������ļ�����4G��������data.ts, data.ts.0001, data.ts.0002, data.ts.0003 ...\n
    �ȶ���ļ�������ɾ��ʱֻ��Ҫ�����ļ���"data.ts"�Ϳ����ˡ� CNend
    \param[in] pFileName  Name of a stream file  CNcomment:�����ļ��� CNend
    \retval none
    \see \n
    N/A
    */
    S32  (*pvr_remove_file)(struct _PVR_DEVICE_S* pstDev, const CHAR* pFileName);

} PVR_DEVICE_S;

/**
\brief direct get PVR device api, for linux and android.CNcomment:��ȡPVR�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get PVR device api��for linux and andorid.
CNcomment:��ȡPVR�豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
\retval  PVR device pointer when success.CNcomment:�ɹ�����vout�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::PVR_DEVICE_S

\par example
*/
PVR_DEVICE_S* getPVRDevice();

/**
\brief  Open HAL PVR module device.CNcomment:��HAL PVRģ���豸CNend
\attention \n
Open HAL PVR module device(for compatible Android HAL).
CNcomment:��HAL PVRģ���豸(Ϊ����android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice PVR device structure.CNcomment:PVR�豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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
\brief Close HAL PVR module deinit.CNcomment:�ر�HAL PVRģ���豸 CNend
\attention \n
Close HAL PVR module deinit(for compatible android HAL).
CNcomment:�ر�HAL PVRģ���豸(Ϊ����android HAL�ṹ). CNend
\param[in] pstDevice Video output device structure.CNcomment:PVR�豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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

