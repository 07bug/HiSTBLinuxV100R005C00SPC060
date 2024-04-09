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

/**platform dmx id number.*//** CNcomment:dmx �豸id���� */
#define DMX_NUMBER_OF_DMX_ID 24

/**file name max length.*//** CNcomment:�ļ�����󳤶� */
#define DMX_FILE_NAME_LENGTH 255

/**callback number for every channel.*//** CNcomment:ÿ��channel ע��Ļص������������� */
#define DMX_CHANNEL_CALLBACK_MAX (8)

/**invalid PID.*//** CNcomment:��Ч��PID*/
#define DMX_INVALID_PID         (0x1FFF)

/**invalid channel ID.*//** CNcomment:��Ч��ͨ��ID*/
#define DMX_INVALID_CHN_ID  (0xFFFFFFFF)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_DMX */
/** @{ */  /** <!-- [HAL_DMX] */

#ifdef ANDROID_HAL_MODULE_USED
/** demux module *//** CNcomment:demuxģ�� */
typedef struct _DEMUX_MODULE_S
{
    struct hw_module_t common;
} DEMUX_MODULE_S;
#endif

/** channel type *//** CNcomment:ͨ������ */
typedef enum _DMX_CHANNEL_TYPE_E
{
    DMX_VIDEO_CHANNEL = 0,         /**< demux channel to output video es data only.*//**<CNcomment:demux��Ƶͨ�����������Ƶes���� */
    DMX_AUDIO_CHANNEL,             /**< demux channel to output audio es data only.*//**<CNcomment:demux��Ƶͨ�����������Ƶes���� */
    DMX_PES_CHANNEL,               /**< demux channel to output PES packets. *//**<CNcomment:demux PES���ݹ���ͨ�� */
    DMX_SECTION_CHANNEL,           /**< demux channel to output Section packets. *//**<CNcomment:demux Section���ݹ���ͨ�� */
    DMX_POST_CHANNEL,              /**< demux channel to full packets. *//**<CNcomment:demux��������ͨ�������ڽ���ĳPID������TS�� */
    DMX_PCR_CHANNEL,               /**< demux channel to output pcr packets. *//**<CNcomment:demux PCR������ͨ�������ڽ���ĳPID��PCR TS�� */
    DMX_CHANNEL_BUTT               /**< demux channel used of ECM data only. (used for clock recovery.) *//**<CNcomment:demux ECM����ͨ��(����clock recovery) */
} DMX_CHANNEL_TYPE_E;

/** Secure mode type*/
/**CNcomment:��ȫģʽ����*/
typedef enum _DMX_SECURE_MODE_E
{
    DMX_SECURE_MODE_NONE = 0,        /** <no security protection*/ /**<CNcomment:�ް�ȫ����*/
    DMX_SECURE_MODE_TEE,             /** <trustedzone security protection*/ /**<CNcomment:trustedzone��ȫ����*/
    DMX_SECURE_MODE_BUTT
} DMX_SECURE_MODE_E;

/** descrambler type *//** CNcomment:���������� */
typedef enum _DMX_DESCRAMBLER_TYPE_E
{
    DMX_CA_NORMAL_DESCRAMBLER = 0, /**<normal ca descrambler.*//**<CNcomment:��ͨCA���� */
    DMX_CA_ADVANCE_DESCRAMBLER,    /**<advanced ca descrambler.*//**<CNcomment:�߰�CA ����*/
    DMX_CA_BUTT
} DMX_DESCRAMBLER_TYPE_E;

/** demux device id *//** CNcomment:demux�豸id */
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

/** demux event *//** CNcomment:demux�¼� */
typedef enum _DMX_EVT_E
{
    DMX_ALL_EVT             = 0,          /**< all event .*//**<CNcomment:ȫ���¼� */
    DMX_EVT_DATA_AVAILABLE  = 1,          /**< Available data.*//**<CNcomment:���������¼� */
    DMX_EVT_DATA_ERROR      = 1 << 1,     /**< Error data.*//**<CNcomment:���ݴ����¼� */
    DMX_EVT_CRC_ERROR       = 1 << 2,     /**< Crc error.*//**<CNcomment:CRCУ��ʧ���¼� */
    DMX_EVT_BUF_OVERFLOW    = 1 << 3,     /**< Buffer overflow.*//**<CNcomment:������� */
    DMX_EVT_SCRAMBLED_ERROR = 1 << 4,     /**< Scrambled error.*//**<CNcomment:���Ŵ��� */
    DMX_EVT_CHANNEL_TIMEOUT = 1 << 5,     /**< Channel timeout.*//**<CNcomment:ͨ����ʱ */
    DMX_EVT_BUTT
} DMX_EVT_E;

/** The type of notify callback. The callback of each channel is same. */
/** CNcomment: ����֪ͨ�������õ�����,ÿ��ͨ���Ļص�������ͳһ�� */
typedef enum _DMX_NOTIFY_TYPE_E
{
    DMX_NOTIFY_DATA = 0,                  /**< Callback with data. *//**<CNcomment: ֪ͨ�������ḽ�����ݣ������ݽ���ӻ�����ȡ��. �������޷�ͨ��read����ȡ��.*/
    DMX_NOTIFY_NODATA,                    /**< Callback without data. Get data by call functiong read() *//**<CNcomment: ֪ͨ�������ḽ�����ݣ��������ݵĽṹ��ԱpstSectionDataΪNULL, ����ͨ��read����ȡ��*/
    DMX_NOTIFY_BUTT
} DMX_NOTIFY_TYPE_E;

/** Channel status */
/** CNcomment: ͨ��״̬ */
typedef enum _DMX_CHANNEL_STATUS_E
{
    DMX_CHANNEL_ENABLE = 0,               /**<channel enable*//**<CNcomment:ͨ��ʹ�� */
    DMX_CHANNEL_DISABLE,                  /**<channel disable*//**<CNcomment:ͨ��ȥʹ�� */
    DMX_CHANNEL_RESET                     /**<channel reset*//**<CNcomment:ͨ������ */
} DMX_CHANNEL_STATUS_E;

/** Demux callback option type */
/** CNcomment: Demux�ص������������� */
typedef enum _DMX_CFG_CALLBACK_E
{
    DMX_CALLBACK_ENABLE = 0,              /**<callback enable*//**<CNcomment:�ص�ʹ�� */
    DMX_CALLBACK_DISABLE,                 /**<callback disable*//**<CNcomment:�ص�ȥʹ�� */
    DMX_CALLBACK_REMOVE                   /**<callback remove*//**<CNcomment:�ص�����ȥ�� */
} DMX_CFG_CALLBACK_E;

/** Demux filter repeat mode */
/** CNcomment: Demux�ϱ����ݷ�ʽ */
typedef enum _DMX_FILTER_REPEAT_MODE_E
{
    DMX_FILTER_REPEAT_MODE_REPEATED = 0,  /**<Repeated*/   /**<CNcomment:�ظ��ϱ����� */
    DMX_FILTER_REPEAT_MODE_ONE_SHOT,      /**<One shot*/   /**<CNcomment:���ϱ�һ������ */
    DMX_FILTER_REPEAT_MODE_BUTT
} DMX_FILTER_REPEAT_MODE_E;

/** Demux descrambler associate type */
/** CNcomment: �������������� */
typedef enum _DMX_DESC_ASSOCIATE_MODE_E
{
    DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDS = 0,    /**<With pids*/   /**<CNcomment:��PID���� */
    DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNEL,     /**<With channel*/   /**<CNcomment:��ͨ������ */
    DMX_DESCRAMBLER_ASSOCIATE_BUTT
} DMX_DESC_ASSOCIATE_MODE_E;

/** Demux descrambler type */
/** CNcomment: ���ż������� */
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
/**CNcomment:�ؼ���ģʽ*/
typedef enum _DMX_CA_ENTROPY_E
{
    DMX_CA_ENTROPY_REDUCTION_CLOSE = 0,   /**<64bit*/
    DMX_CA_ENTROPY_REDUCTION_OPEN,        /**<48bit*/

    DMX_CA_ENTROPY_REDUCTION_BUTT
} DMX_CA_ENTROPY_E;

/** Demux descrambler style */
/** CNcomment: �������� */
typedef enum _DMX_DESC_STYLE_E
{
    DMX_DESC_STYLE_NONE = 0,              /**< Not support descramble */  /**<CNcomment:��֧�ֽ��� */
    DMX_DESC_STYLE_SOLE,                  /**< Each pid can descramble sole channel */  /**<CNcomment:ͬһ��pid,ֻ�ܽ���һ· */
    DMX_DESC_STYLE_SHARE,                 /**< Each pid can descramble share */  /**<CNcomment:ͬһ��pid,һ��������ͬʱ���Ŷ�·,���ܿ���������� */
    DMX_DESC_STYLE_BIUNIQUE,              /**< Each pid can descramble multi channel, Each descrambler for each channel */  /**<CNcomment:ͬһ��pid,���������ͬʱ���Ŷ�·,��������ͨ��һ��һ */
    DMX_DESC_STYLE_BUTT
} DMX_DESC_STYLE_E;

/** Source type. Just support tuner. */
/** CNcomment: ������Դ����.����ֻ��֧��tuner, ��������pvrģ�� */
typedef enum _DMX_SOURCE_TYPE_E
{
    DMX_SOURCE_TUNER = 0,                 /**< Tuner, av or pvr. *//**<CNcomment: tuner: ֱ��,pvr¼�Ƶ�*/
    DMX_SOURCE_FILE,                      /**< File *//**<CNcomment: �ļ� */
    DMX_SOURCE_MEM,                       /**< Ts inject *//**<CNcomment: TS��ע�� */
    DMX_SOURCE_PVR,                       /**< PVR file or local stream file. *//**<CNcomment: pvr�����ļ�,����ý�岥��. */
    DMX_SOURCE_NONE,                      /**< Free demux without source *//**<CNcomment: ���е�demux */
    DMX_SOURCE_BUTT
} DMX_SOURCE_TYPE_E;

/** Demux filter attr */
/** CNcomment:1.u8Match,u8Mask,u8Notmask ���ǰ���bit Ϊ��λ��������.
        2. ���u8Notmask==NULL, �򲻴����ƥ������.
        3. u8Match ��u8Mask ����ΪNULL.
        4. u8Mask ָ��ƥ�������ָ��,
            ��u8Match��Ӧ�ı�������,���u8Mask ��ĳλΪ1,���յ������ݱ�����u8Match�ж�Ӧ�ı���ƥ��,
              ���Ϊu8Mask��ĳλ0,���λ����.
        5. u8Notmaskָ���ƥ�������ָ��.
            ��u8MaskΪ1�����ж�Ӧ�ı��ص���,���յ�����������Ӧ����һ��������u8Match��һ��,
             ����Ϊ���ܵ�������ƥ���,������еı��ض���ƥ���,����Ϊ�ǲ�ƥ���.
        6. section�ĵ�2,3�����ֽ�������section length�ֶ�,һ�㲻�����˴���.����
             hdi ����ݾ���ƽ̨ȷ���Ƿ�����2,3,�ֽ�.
        7. ��Щƽ̨�ϴ����� u8Notmask ����,���ǲ�ͬ��filter ����.���ҿ�������ͬһ��channel�����в�ͬ���͵�filter.
             ��������ƽ̨,Ӧ��Ҫ���ú�filter����,
        8. ��Щƽ̨�ϴ����� u8Notmask ����,���ǲ�ͬ��filter ����.���ҿ�������ͬһ��filter ���ܶ�̬�޸� filter ����.
             ��������ƽ̨,HDI �Լ�Ҫ���ü���.(����������͵�ʱ��,���ϵ�filter ��close,��open).
        9. ��u8Notmask��u8Mask ��Ӧλ��ͻ��ʱ��,��u8Notmask,Ϊ׼.
 */
typedef struct  _DMX_FILTER_DATA_S
{
    DMX_FILTER_REPEAT_MODE_E enFilterRepeatMode;  /**< Data repeat type. *//**<CNcomment: �����ظ�ģʽ */
    U32                      u32FilterSize;       /**< Filter size *//**<CNcomment: �������ݵ���Ч����.*/
    U8*                      pu8Match;            /**< Matched bytes of a filter.The data is compared by bit.*/ /**< CNcomment:������ƥ���ֽ�,��bit�Ƚ�*/
    U8*                      pu8Mask;             /**< Point to mask *//**<CNcomment: ָ��ƥ�������ָ��.*/
    U8*                      pu8Notmask;          /**< Point to not mask *//**<CNcomment: ָ���ƥ�������ָ��.*/
} DMX_FILTER_DATA_S;

/** Source type params */
/** CNcomment: ������Դ���� DMX_SOURCE_TYPE_E, dmd_info_s, av_inject_status_s,pvr_play_info_s.
1. enSourceType == DMX_SOURCE_TUNER:hDmx ��鿴dmd_info_s::source_id;
3. enSourceType == DMX_SOURCE_FILE:u8FileName Ŀǰ��ʱû�ж���,
3. enSourceType == DMX_SOURCE_MEM:hInjecter ��鿴av_inject_status_s::m_source_id;
4. enSourceType == DMX_SOURCE_PVR:u32PlaychnId ��鿴pvr_play_info_s::m_source_id;
5. enSourceType == DMX_SOURCE_NONE:u32Dummy �Ժ���չ��;
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
/** CNcomment: �������������� */
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
/**CNcomment:����������*/
typedef struct _DMX_DESCRAMBLER_ATTR_S
{
    DMX_DESCRAMBLER_TYPE_E enCaType;                 /**<Whether the descrambler adopts advanced CA.*/ /**< CNcomment:�������Ƿ�ʹ�ø߰�ȫCA*/
    DMX_DESC_TYPE_E enDescramblerType;               /**<Descrambling protocol type of the descrambler*/ /**< CNcomment:����������Э������*/
    DMX_CA_ENTROPY_E enEntropyReduction;             /**<CA Entropy reduction mode,for CSA2.0*/ /**< CNcomment:�ؼ���ģʽ��CSA2.0��Ч*/
} DMX_DESCRAMBLER_ATTR_S;

/** advanced CA Encrypt arith*/
typedef enum _DMX_KL_ALG_E
{
    DMX_KL_ALG_TDES = 0,                             /**<Encrypt arith : 3DES*/
    DMX_KL_ALG_AES,                                  /**<Encrypt arith : AES*/
    DMX_KL_ALG_BUTT
} DMX_KL_ALG_E;

/**Defines the setting of the DCAS keyladder.*/
/**CNcomment: ����DCAS keyladder���ýṹ��.*/
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
/**CNcomment: ����DCAS keyladder���ýṹ��.*/
typedef struct _DMX_DCAS_NONCE_SETTING_S
{
    DMX_KL_ALG_E enKLAlg;                 /**<Keyladder algorithm, TDES/AES*/
    U32 u32CAVid;                         /**<Verdor_SysID*/
    U8* pu8EK2;                           /**<EK3(K2) key, 16bytes*/
    U8* pu8Nonce;                         /**<Nonce, 16bytes*/
} DMX_DCAS_NONCE_SETTING_S;

/** Channel setting params */
/** CNcomment:ͨ�����ò���
channel���ò�������Ӧ��get��set��������ȡ������
ע��,��Ҫ�޸���Щ����ʱ,����get����,�޸���Ҫ�޸ĵĳ�Ա��set��ȥ
set�����������û�иı�ĳ�Ա�����޸�
ע��:���ǵ����������,get�����Ĳ�����set��ȥ֮ǰ,�����������Ѿ���set����
���Ǵ�ʱ��set�п��ܻḲ����������set����������
*/
typedef  struct DMX_CHANNEL_SETTING_S
{
    DMX_NOTIFY_TYPE_E enNotifyType;       /**< DMX_NOTIFY_TYPE_E*/
    U32               u32IsCRC;           /**< If enable CRC,default 1, 0 for disable CRC and 1 for enable CRC. *//**<CNcomment: �ڽ�������ʱ�Ƿ��CRCУ��,Ĭ��:1,0:�ر�CRCУ��.1:��CRCУ��, ���CRC У��ʧ��,����û��CRC,���Ӧ�����ݶ���.*/
    U32               u32AddData;         /**< Additional data *//**<CNcomment: ���ӵ����ݡ���һЩCA�������*/
    U32               u32Tag;             /**< Optional tag value *//**<CNcomment: ��־λֵ����ѡ*/
} DMX_CHANNEL_SETTING_S;

/** Channel info, just like channel type, channel status, channel PID etc. */
/** CNcomment:ͨ����Ϣ������ͨ������,��ǰ����״̬,��ǰpid�� */
typedef  struct _DMX_CHANNEL_INFO_S
{
    DMX_ID_E             enDemuxId;       /**<Demux ID *//**<CNcomment: ��ʶ �����ĸ�DEMUX*/
    DMX_CHANNEL_TYPE_E   enType;          /**<Channel ID *//**<CNcomment: �������ݵ����ͣ�PES����SECTION*/
    DMX_CHANNEL_STATUS_E enStatus;        /**<Channel status *//**<CNcomment: ��ͨ����ǰ�Ĺ���״̬*/
    U32                  u32CallbackNum;  /**<Callback number *//**<CNcomment: �ص������ĸ���*/
    U32                  u32FilterNum;    /**<Filter number *//**<CNcomment: filter�ĸ���*/
    U32                  u32PacketCount;  /**<Packet number *//**<CNcomment: ����Ҫ��ȷ�ĸ���,��Ҫ���ڲ�ѯ��û����������,���ڲ��*/
    U16                  u16Pid;          /**<Channel PID *//**<CNcomment: Ҫ�������ݵ�PID��*/
    U32                  u32Len;          /**<The max data size *//**<CNcomment: �����յ����ݳ��ȣ�DEMUX��������ڴ�����������*/
} DMX_CHANNEL_INFO_S;

/** Section data */
/** CNcomment:Section���� */
typedef struct  _DMX_SECTION_DATA_S
{
    U32      u32Length;
    VOID*    pData;
} DMX_SECTION_DATA_S;

/** Demux callback params */
/** CNcomment:�ص��������� */
typedef struct  _DMX_CALLBACK_DATA_S
{
    DMX_SECTION_DATA_S*   pstSectionData; /**<Section data. It can be NULL if no data send. *//**<CNcomment: section ����,��Ϊ�ձ�ʾ�ص���������������*/
    U32                   u32ChannelId;   /**<Channel ID *//**<CNcomment:  ��ǰ��ͨ���� */
    DMX_EVT_E             enEvt;          /**<Channel event *//**<CNcomment:  ��ǰ��ͨ�����¼�*/
    DMX_ID_E              enDemuxId;      /**<Demux ID *//**< CNcomment: ��ǰ��ͨ����demux id*/
    U32                   u32FilterId;    /**<Filter ID *//**<CNcomment: ��ǰ��channel��u32FilterId, �����֧��,����: INVALID_ID */
} DMX_CALLBACK_DATA_S;

/**
 \brief channel callback.CNcomment:ͨ���ص����� CNend
 \attention \n
It can call api in this module.
CNcomment:�ص�����������Ե��ñ�ģ��Ľӿ�. CNend
 \param[in] pstData callback params.CNcomment:�ص��������� CNend
 \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
 \retval ::FAILURE  other error.CNcomment:�������� CNend
 \see \n
::DMX_CALLBACK_DATA_S
 */
typedef S32 (*DMX_CALLBACK_PFN)(const DMX_CALLBACK_DATA_S* const pstData);

/** Demux registe callback sturct */
/** CNcomment:demuxע��ص������ṹ */
typedef struct  _DMX_REG_CALLBACK_PARAMS_S
{
    DMX_CALLBACK_PFN pfnCallback;         /**<Callback function.*//**<CNcomment:��Ҫע��Ļص�����*/
    U32              u32IsDisable;        /**<If set the function able.*//**<CNcomment:�Ƿ�ʹ�ܸûص�: 0 is enable; 1 is disable*/
    DMX_EVT_E        enEvt;               /**<Demux event.*//**<CNcomment:demux�¼�,��ʶ����ص�����Щ�¼���Ч, 1.���Թ��˵��Լ������ĵ��¼�,2.TVOS_HAL_DMX_ALL_EVT��ʾ��ͨ�������������¼�������ô˻ص����� */
} DMX_REG_CALLBACK_PARAMS_S;

/** Demux init params */
/** CNcomment:demux��ʼ������ */
typedef  struct _DMX_INIT_PARAMS_S
{
    U32 u32TaskPriority;                  /**<Task priority.*//**<CNcomment: �������ȼ�����ƽ̨������ͳһ����*/
} DMX_INIT_PARAMS_S;

/** Demux term params */
/** CNcomment:demuxͨ����ֹ���� */
typedef  struct _DMX_TERM_PARAM_S
{
    U8 u8Dummy;                           /**<Reserved.*//**< CNcomment: ��������.*/
} DMX_TERM_PARAM_S;

/** Demux open params */
/** CNcomment:demuxͨ���򿪲��� */
typedef  struct _DMX_CHANNEL_OPEN_PARAM_S
{
    U32                   u32Pid;            /**<Channel PID. It can be setted by dmx_channel_set_pid. */ /**<CNcomment:Ҫ�������ݵ�PID��Ҳ�������Ժ�ͨ��dmx_channel_set_pid�������趨*/
    U32                   u32Len;            /**<Length of memory to receiving data. */ /**<CNcomment:�����յ����ݳ��ȣ���������DEMUXӦ�÷�������ڴ�����������, ���Ӧ�ô�������buf����̫С, ���뱣֤������.*/
    DMX_CHANNEL_TYPE_E    enType;            /**<Channel type */ /**<CNcomment: �������ݵ����� */
    U32                   u32FirstIndex;     /**<First channel index to find free one *//**<CNcomment:ȷ����ָ��dmx���ĸ�ʵ�ʵ�����channel��ʼ���ҿ��Դ򿪵�channel����:����Ԥ��ǰ�漸��ͨ������ */
    DMX_CHANNEL_SETTING_S stChannelSettings; /**<Channel settings*//**<CNcomment:��ǰ��channel����*/
    DMX_SECURE_MODE_E     enSecureMode;      /**<Secure channel indication*/ /**<CNcomment:��ȫͨ����ʾ*/
} DMX_CHANNEL_OPEN_PARAM_S;

/** Demux close params */
/** CNcomment:demuxͨ���رղ��� */
typedef  struct _DMX_CHANNEL_CLOSE_PARAMS_S
{
    U8 u8Dummy;                           /**<Reserved.*//**< CNcomment: ��������.*/
} DMX_CHANNEL_CLOSE_PARAMS_S;

/** Demux capability */
/** CNcomment:demux���� */
typedef struct  _DMX_CAPABILITY_S
{
    U32              u32DMXNum;
    U32              u32ChannelNumArr[DMX_ID_BUTT];
    U32              u32FilterNumArr[DMX_ID_BUTT];
    U32              u32DescramblerNumArr[DMX_ID_BUTT];
    DMX_DESC_STYLE_E enDescStyle;         /**<Descrambler style.*//**< CNcomment: ���������.*/
    DMX_DESC_STYLE_E enAdvDescStyle;      /**<Advanced descrambler style.*//**< CNcomment: �߰����������.*/
} DMX_CAPABILITY_S;

/** Demux status */
/** CNcomment:demux״̬ */
typedef struct  _DMX_STATUS_S
{
    U32 u32FreeChannelNum;                /**<Free channel number.*//**<CNcomment: ����ͨ������ */
    U32 u32FreeFilterNum;                 /**<Free filter number.*//**<CNcomment: ���й��������� */
    U32 u32FreeDescramblerNum;            /**<Free descrambler number.*//**<CNcomment: ���н��������� */
    U32 u32TsPacketCount;                 /**<Ts packet number.*//**<CNcomment: ts������ */
    U32 u32IsConnect;                     /**<Is connect.*//**<CNcomment: �Ƿ����� */
} DMX_STATUS_S;

/** Demux channel data struct */
/** CNcomment:��ȡDEMUXͨ�����ݰ��ṹ*/
typedef enum _DMX_CHANNEL_DATA_TYPE_E
{
    DMX_DATA_TYPE_WHOLE = 0,              /**<Whole data.*//**<CNcomment: �˶����ݰ������������ݰ�, ����SECTIONÿ��������������*/
    DMX_DATA_TYPE_HEAD,                   /**<Head data. Just for PES *//**<CNcomment: �˶����ݰ������ݰ�����ʼ�����ǲ�һ���������İ�, ֻ����PES����*/
    DMX_DATA_TYPE_BODY,                   /**<Body data. Just for PES *//**<CNcomment:  �˶����ݰ������ݰ������ݣ���������ʼ�������н�β, ֻ����PES����*/
    DMX_DATA_TYPE_TAIL,                   /**<Tail data. Just for PES *//**<CNcomment: �˶����ݰ������ݰ��Ľ�β������ָʾ��ʶ��İ�����, ֻ����PES����*/
    DMX_DATA_TYPE_BUTT
} DMX_CHANNEL_DATA_TYPE_E;

/** Demux channel data struct */
/**CNcomment:��ȡDEMUXͨ�����ݰ��ṹ*/
typedef struct _DMX_CHANNEL_DATA_S
{
    U8*                     pu8Data;      /**<Data pointer*//**< CNcomment:����ָ�� */
    U32                     u32Size;      /**<Data length*//**< CNcomment:���ݳ��� */
    DMX_CHANNEL_DATA_TYPE_E enDataType;   /**<Data packet type*//**< CNcomment:���ݰ������� */
} DMX_CHANNEL_DATA_S;


/**Defines of Defines of demux AVFilter video stream type.*/
/**CNcomment: ��Ƶ������*/
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

/**CNcomment: ��Ƶ������*/
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
/**CNcomment:Demuxģ��������ݴ򿪲��� */
typedef  struct _DMX_PARSER_FILTER_OPEN_PARAM_S
{
    U32                     u32Pid;       /**<Channel pid. */ /**<CNcomment:  �������ݵ�ͨ��PID */
    DMX_CHANNEL_TYPE_E      enType;       /**<Channel type */ /**<CNcomment:  �������ݵ����� */
    union _DMX_AV_STREAM_TYPE_U
    {
        DMX_VID_STREAM_TYPE_E enVIDEsTpye; /**<video type *//**<CNcomment:  ��Ƶ������ */
        DMX_AUD_STREAM_TYPE_E enAUDEsType; /**<audio type *//**<CNcomment:  ��Ƶ������ */
    } DMX_AV_STREAM_TYPE_U;

} DMX_PARSER_FILTER_OPEN_PARAM_S;

/**Demux esframe info*/
/**CNcomment:Demux es֡��Ϣ */
typedef struct _DMX_ESFRAME_INFO_S
{
    U64 u64BufferAddr;  /**<Buffer address. */ /**<CNcomment:  ���ݵ�ַ */
    U32 u32Lenght;      /**<Frame length. */ /**<CNcomment:  ֡���� */
    U64 u64Timestamp;   /**<PTS. */ /**<CNcomment:  ʱ��� */
} DMX_ESFRAME_INFO_S;

/** Stream data */
/** CNcomment:������ */
typedef struct  _DMX_STREAM_DATA_S
{
    U32      u32Length;
    U8*      pu8Data;
} DMX_STREAM_DATA_S;

/** TS buffer attribute*/
/**CNcomment:TS buffer ����*/
typedef struct _DMX_TSBUF_ATTR_S
{
    DMX_SECURE_MODE_E   enSecureMode;   /**<Secure indication*/ /**<CNcomment:��ȫ��ʾ*/
    U32                 u32BufSize;     /**<Buffer size*/ /**< CNcomment:��������С*/
} DMX_TSBUF_ATTR_S;


#ifdef ANDROID_HAL_MODULE_USED
/**Demux module structure(Android require)*/
/**CNcomment:�⸴��ģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _DMX_MODULE_S
{
    struct hw_module_t stCommon;
} DMX_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_DMX*/
/** @{*/  /** <!-- -[HAL_DMX]=*/

/**Demux device structure*//** CNcomment:�⸴���豸�ṹ*/
typedef struct _DEMUX_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
     \brief Demux  init.CNcomment:dmxģ���ʼ�������� CNend
     \attention \n
    Repeat call return success.
    CNcomment:�ظ�����init �ӿ�,����SUCCESS. CNend
     \param[in] pstInitParams system module init param.CNcomment:��ʼ��ģ����� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_DMX_INIT_FAILED  Lower layer dmx module init error.CNcomment:�ײ�DMXģ���ʼ������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_INIT_PARAMS_S
     */
    S32 (*dmx_init)(struct _DEMUX_DEVICE_S* pstDev, const DMX_INIT_PARAMS_S* const pstInitParams );

    /**
     \brief Demux  deinit. CNcomment:dmxģ����ֹ CNend
     \attention \n
    CNcomment:�ͷ������Դ,��ֹ��������³�ʼ���������²�������: ��ֹ����˻�ȡ�汾��Ϣ�ͳ�ʼ������������������������ȷ����. �ظ�term ����SUCCESS.CNend
     \param[in] pstTermParams system module deinit param.CNcomment:��ֹ���� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_DMX_DEINIT_FAILED  Lower layer dmx module deinit error.CNcomment:�ײ�DMXģ��ȥ��ʼ������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_TERM_PARAM_S
     */
    S32 (*dmx_term)(struct _DEMUX_DEVICE_S* pstDev, const DMX_TERM_PARAM_S* const pstTermParams );

    /**
     \brief Set demux source. CNcomment:����Demux����Դ CNend
     \attention \n
    CNcomment: ����֮��������״̬ CNend
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \param[in] pstSourceParams source param. CNcomment:Դ���� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_SOURCE_PARAMS_S
     */
    S32 (*dmx_set_source_params)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, const DMX_SOURCE_PARAMS_S* pstSourceParams);

    /**
     \brief Get demux source param. CNcomment:��ȡDemux����Դ���� CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \param[out] pstSourceParams source param. CNcomment:Դ���� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_SOURCE_PARAMS_S
     */
    S32 (*dmx_get_source_params)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, DMX_SOURCE_PARAMS_S* const pstSourceParams);

    /**
     \brief Demux disconnect. CNcomment:�Ͽ�dmx������Դ(��dmd)�Ĺ���,����Ĭ���ǹ����� CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_ID_E
     */
    S32 (*dmx_disconnect)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId);

    /**
     \brief Demux reconnect. CNcomment:�ָ�dmx�뵱ǰ���õ�����Դ(��dmd)�Ĺ���,����Ĭ���ǹ����� CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_ID_E
     */
    S32 (*dmx_reconnect)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId);

    /**
     \brief Get demux capability. CNcomment:��ȡdemux������ CNend
     \attention \n
     \param[out] pstCapability demux capability.CNcomment:Demux���� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_CAPABILITY_S
     */
    S32 (*dmx_get_capability)(struct _DEMUX_DEVICE_S* pstDev, DMX_CAPABILITY_S* const pstCapability);

    /**
     \brief Get demux status. CNcomment:��ȡdemux״̬ CNend
     \attention \n
    CNcomment:��Щƽ̨ͨ��/������/�������ڶ�demux_id�乲����ȡ�Ľ������� CNend
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \param[out] pstStatus demux status.CNcomment:Demux״̬ CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_STATUS_S
     */
    S32 (*dmx_get_status)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, DMX_STATUS_S* const pstStatus);

    /**
     \brief Open a demux. CNcomment:����һ������ͨ���� CNend
     \attention \n
    CNcomment:open����disable״̬. open ��ʱ����Դ���Ƿ���pid,�Ժ���ͨ��dmx_channel_set_pid()������. CNend
     \param[in] enDemuxId demux id.CNcomment:demux id CNend
     \param[out] pu32ChannelId demux channel id.CNcomment:Demuxͨ��ID CNend
     \param[in] pstOpenParams demux open params.CNcomment:Demux�򿪲��� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_CHANNEL_OPEN_PARAM_S
     */
    S32 (*dmx_channel_open)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32ChannelId, const DMX_CHANNEL_OPEN_PARAM_S* const pstOpenParams);

    /**
     \brief Close a demux. CNcomment:�ر�һ������ͨ�������ͷ������Դ�� CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:Demuxͨ��ID CNend
     \param[in] pstCloseParams demux close params.CNcomment:Demux�رղ��� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_CHANNEL_CLOSE_PARAMS_S
     */
    S32 (*dmx_channel_close)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_CHANNEL_CLOSE_PARAMS_S* pstCloseParams );

    /**
     \brief Set channel pid. CNcomment:��������ͨ��PID�� CNend
     \attention \n
    CNcomment:���(u16Pid==INVALID_PID)���ƽ̨֧��,��clear��ͨ����pid. ���pid �������� INVALID_PID, HDI ��Ҫ����ΪINVALID_PID. CNend
     \param[in] u32ChannelId demux channel id.CNcomment:Demuxͨ��ID CNend
     \param[in] u16Pid demux pid.CNcomment:Demux PID CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_channel_set_pid)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U16 u16Pid);

    /**
     \brief Search channel pid. CNcomment:��ѯ�Ƿ������ø�PID��ͨ��CNend
     \attention \n
     \param[in] enDemuxId demux  id.CNcomment:�ĸ�demux�� CNend
     \param[out] pu32ChannelId Channel id pointer .CNcomment:��PID��Ӧ��ͨ��ID CNend
     \param[in] u16Pid recevie data pid.CNcomment: Ҫ�������ݵ�PID CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_ID_E
     */

    S32 (*dmx_channel_query)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32ChannelId, const U16 u16Pid);

    /**
     \brief open a demux. CNcomment:��������ͨ����ʼ�������ݡ� CNend
     \attention \n
    CNcomment: channel enable ��ʱ��, �ڸ�channel �Ͽ������е�filter ��enable. CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_channel_enable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId );

    /**
     \brief stop demux recevie data. CNcomment:ֹͣ����ͨ���������ݡ� CNend
     \attention \n
    CNcomment: channel disable ��ʱ��, �ڸ�channel �Ͽ������е�filter ��disable. CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_channel_disable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId);

    /**
     \brief reset a demux. CNcomment:��λ����ͨ�� CNend
     \attention \n
    CNcomment:  ��λ����disable״̬. CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_channel_reset)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId );

    /**
     \brief get demux channel info. CNcomment:��ȡ����ͨ����Ϣ CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[out] pstInfo info pointer.CNcomment:����ͨ����ϢCNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_CHANNEL_INFO_S
     */
    S32 (*dmx_channel_get_info)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, DMX_CHANNEL_INFO_S* const pstInfo);

    /**
     \brief set demux channel param. CNcomment:����ͨ������ CNend
     \attention \n
     CNcomment: ע��,�޸�channel����ʱ,����get����,�޸���Ҫ�޸ĵĳ�Ա��set��ȥ
     set�����������û�иı�ĳ�Ա�����޸�CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] pstSettings settings pointer.CNcomment: ���� ָ�� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_CHANNEL_SETTING_S
     */
    S32 (*dmx_channel_set)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_CHANNEL_SETTING_S* const pstSettings);

    /**
     \brief get demux channel. CNcomment:��ȡͨ��������CNend
     \attention \n
    CNcomment: ע��,�޸�channel����ʱ,����get����,�޸���Ҫ�޸ĵĳ�Ա��set��ȥ
    set�����������û�иı�ĳ�Ա�����޸�CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[out] pstSettings settings pointer.CNcomment: ���� ָ�� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_CHANNEL_SETTING_S
     */
    S32 (*dmx_channel_get)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, DMX_CHANNEL_SETTING_S* const pstSettings);

#ifdef HAL_HISI_EXTEND_H
    /**
    \brief Obtains the handles of all channels that receive new data.CNcomment:��ȡ�������ݵ��������ͨ���ľ����CNend
    \attention \n
    When you call this API, the parameter pu32ChNum serves as the input parameter and is used to specify the data length pointed by pu32ChannelId. pu32ChNum indicates the number of channels to be queried.\n
    The number of channels must be initialized, and the initial value cannot be 0.\n
    It is recommended to set the number of channels to the total number. For details about the total number of channels.\n
    After you call this API successfully, the parameter pu32ChNum serves as the output parameter and is used to specify the valid data length pointed by phChannel.\n
    The block time is configurable (in ms). If u32TimeOutMs is set to 0, it indicates that the block time is 0; if u32TimeOutMs is set to 0xFFFFFFFF, it indicates infinite wait.\n
    CNcomment:���øýӿ�ʱ��pu32ChNum��Ϊ�������������ָ��pu32ChannelIdָ������ĳ��ȣ���ʾҪ��ѯ��ͨ��������\n
    ͨ�����������ʼ�����ҳ�ʼֵ����Ϊ��0ֵ\n
    ���齫ͨ����������Ϊͨ�����ܸ���\n
    ���ýӿڵ��óɹ�ʱ��pu32ChNum��Ϊ���������ָ��pu32ChannelIdָ���������Ч����\n
    ����ʱ��������ã�ʱ�䵥λΪ���룬����Ϊ0���ȴ�������Ϊ0xffffffffһֱ�ȴ���CNend
    \param[out] pu32ChannelId  Pointer to the number of channels. The number of channels depends on the value of pu32ChNum.CNcomment:ָ�����ͣ�ָ��ͨ��������顣���鳤����pu32ChNum������CNend
    \param[in] pu32ChNum Pointer type
                               Input: indicates the number of channel handles to which pChannelHandle points.
                               Output: indicates the number of lower-layer channels that receive new data. The maximum value cannot be greater than the input value.
                               CNcomment: ָ�����͡�ע��:�ò���ͬʱ��Ϊ����������CNend
                               CNcomment: ���룺pChannelHandleָ������ĳ��ȡ�CNend
                               CNcomment: ������ײ���������ͨ������Ŀ����಻�����������ֵ��CNend
    \param[in] u32TimeOutMs      Wait timeout, in ms.CNcomment:�ȴ���ʱʱ�䣬��λms��CNend
    \retval ::HI_SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
    \see \n
     N/A.CNcomment:�ޡ�CNend
    */
    S32 (*dmx_channel_get_data_handle)(struct _DEMUX_DEVICE_S* pstDev, U32* pu32ChannelId, U32* pu32ChNum, const U32 u32TimeoutMs);
#endif

    /**
     \brief get a demux channel buffer. CNcomment:��ȡָ������ͨ��������CNend
     \attention \n
    CNcomment:  �ú���Ϊͬ���������ȴ�ֱ���õ����ݻ��߳�ʱ���ء�
    ����sectionͨ����ECM/EMMͨ����ÿ�����ݰ�����һ��������section
    ����PESͨ����ÿ�����ݰ���������������pes���������pes̫�󣬿���Ҫ�ֶ��pes�������
    ����������Ƿ�����ͨ�����ݰ��ṹ��enDataType�ֶ�ָ��
    ����POST���͵�ͨ����ÿ�����ݰ�����һ������������TS����TS����188�ֽ�
    ��������Ƶͨ���ǲ���ͨ���˽ӿڻ�ȡ���ݵģ�����Ƶ���ݻ�ͨ���ڲ��ӿ�ֱ���͸����������н���
    �������ظ����ô˽ӿڣ�����һ���������ͷţ������ͷű��밴˳�򣬶����ͷŵĵ�ַ�ͳ��ȱ���������һ��
    ����ֻ���ͷ������е����ݰ������ٴ����󣬷��򷵻��ظ���������롣CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] u32AcquirePackageNum expect acquire package number.CNcomment: ������ȡ���ݵ��ܰ��� CNend
     \param[out] pu32AcquiredNum acquire package number.CNcomment:ʵ�ʻ�ȡ���ݵ��ܰ�����С�ڵ���acquire_package_numCNend
     \param[out] pstChannelData obtained data.CNcomment: ��ȡ�������ݼ�˵�� CNend
     \param[in] u32TimeoutMs waiting time.CNcomment: �ȴ�ʱ��,����һ��ĵȴ�ʱ����,֧�����޳�ʱ��������ʱ��������ȴ�ʱ�� CNend
     \retval
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_DMX_GETBUF_TIMEOUT time out.CNcomment:��ʱ��CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_CHANNEL_DATA_S
     */
    S32 (*dmx_channel_get_buf)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32 u32AcquirePackageNum, U32* pu32AcquiredNum, DMX_CHANNEL_DATA_S* pstChannelData, const U32 u32TimeoutMs );

    /**
     \brief release demux channel buffer. CNcomment:�ͷ����ݰ�ռ�õĻ���ռ�CNend
     \attention \n
    CNcomment: ���ӿ��ͷŵĻ�����һ����ͨ��dmx_channel_get_buf��ȡ�Ļ��������������ĵ�ַ�ͳ��Ȳ��ܸ���
    �ͷŵĻ�������������С�ڻ�ȡ�Ļ���������CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] u32ReleaseNum release package number .CNcomment:�ͷ����ݰ�����CNend
     \param[in] pstChannelData a pointer pointing to release buffer.CNcomment:ָ�����ͣ�ָ���ͷŻ�������Ϣ���飬������release_num����CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_CHANNEL_DATA_S
     */
    S32 (*dmx_channel_release_buf)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32 u32ReleaseNum, DMX_CHANNEL_DATA_S* pstChannelData);

    /**
     \brief register callback . CNcomment:ע��ص�����CNend
     \attention \n
    CNcomment:  �ص�������ͨ�� ��,  һ��ͨ��������ע��DMX_CHANNEL_CALLBACK_MAX ���ص�����CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] pstReg register parameter configuration pointer.CNcomment:   ע��������ýṹָ�� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_REG_CALLBACK_PARAMS_S
     */
    S32 (*dmx_channel_register_callback)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_REG_CALLBACK_PARAMS_S* const pstReg);

    /**
     \brief config demux channel callback. CNcomment:���ö�Ӧ����ͨ���Ļص�������CNend
     \attention \n
    CNcomment: �ص�������ͨ�� ��,һ��ͨ��������ע��DMX_CHANNEL_CALLBACK_MAX ���ص�����,
    ���pfnCallback==NULL��ʾ�Ը�channel���еĻص�������ЧCNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] pfnCallback point to the callback need to config CNcomment:ָ����Ҫ���õĻص����� CNend
     \param[in] parameters of config CNcomment:���ò��� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_CALLBACK_PFN, DMX_CALLBACK_PFN
     */
    S32 (*dmx_channel_config_callback)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const DMX_CALLBACK_PFN pfnCallback, const DMX_CFG_CALLBACK_E enCfg);

    /**
     \brief add filter and set it. CNcomment:Ϊ����ͨ������������������ù������ݡ�CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] pu32FilterId return filter id CNcomment:���ط���Ĺ�����ID��CNend
     \param[in] pstFilterData filter data pointer CNcomment:����������ָ��CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_FILTER_DATA_S
     */
    S32 (*dmx_channel_add_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32* const pu32FilterId, const DMX_FILTER_DATA_S* const pstFilterData);

    /**
     \brief set filters. CNcomment:���ù������Ĺ���������CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] u32FilterId  filter id CNcomment:������ID��CNend
     \param[in] pstFilterData filter data pointer CNcomment:����������ָ��CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_FILTER_DATA_S
     */
    S32 (*dmx_channel_set_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId, const DMX_FILTER_DATA_S* const pstFilterData);

    /**
     \brief get filters. CNcomment:��ȡ�������Ĺ���������CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] u32FilterId  filter id CNcomment:������ID��CNend
     \param[out] pstFilterData filter data pointer CNcomment:����������ָ, ���buffer �ռ䲻��(���Ȼ�ָ��),����ʧ��CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    :: DMX_FILTER_DATA_S
     */
    S32 (*dmx_channel_get_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId, DMX_FILTER_DATA_S* const pstFilterData);

    /**
     \brief close filters. CNcomment:�رչ�������CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] u32FilterId  filter id CNcomment:������ID��CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_channel_destroy_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId);

    /**
     \brief close all filters. CNcomment:�ر�ָ������ͨ�������й�������CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_channel_destroy_all_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId );

    /**
     \brief enable filter. CNcomment:��������ͨ����ָ����������ʼ�������ݡ�CNend
     \attention \n
    CNcomment: һ����һ������ͨ�����ڶ���������������ʹ��CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] u32FilterId  filter id CNcomment:������ID��CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_channel_enable_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId );

    /**
     \brief disable filter. CNcomment:��ֹ����ͨ���е�ָ����������CNend
     \attention \n
    CNcomment:һ����һ������ͨ�����ڶ���������������ʹ�á�CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[in] u32FilterId  filter id CNcomment:������ID��CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_channel_disable_filter)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, const U32 u32FilterId);

    /**
     \brief query filter by table id
    CNcomment:channel��filter�Ƿ����ĳ��table id ��ext id��filter ��CNend
     \attention \n
    CNcomment:u8TableId ��u16ExtId �����ϸ�ƥ��,��������������Ϊ0�Ĳ��ᱻƥ�� CNend
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[out] pu32FilterId  filter id pointer  CNcomment:���ط��������Ĺ�����ID��INVALID_ID ��ʾû��CNend
     \param[in] u8TableId table id CNcomment:table ID CNend
     \param[in] u16ExtId table extend id CNcomment: table extend ID CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_channel_query_filter_by_table_id)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32* const pu32FilterId, const U8 u8TableId, const U16 u16ExtId);

    /**
     \brief query filter by filter data. CNcomment:channel��filter�Ƿ������ͬ�Ĺ���������CNend
     \attention \n
     \param[in] u32ChannelId demux channel id.CNcomment:����ͨ��ID CNend
     \param[out] pu32FilterId  filter id pointer  CNcomment:���ط��������Ĺ�����ID��INVALID_ID ��ʾû��CNend
     \param[in] pstFilterData filter data pointer CNcomment:����������ָ��CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_FILTER_DATA_S
     */
    S32 (*dmx_channel_query_filter_by_filter_data)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32ChannelId, U32* const pu32FilterId, const DMX_FILTER_DATA_S* const pstFilterData);

    /**
     \brief open descrambler. CNcomment:����һ������ͨ����CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:�⸴����ID CNend
     \param[out] pu32DescId  descrambler id pointer. CNcomment:����ͨ��ID ָ��CNend
     \param[in] enMode see DMX_DESC_ASSOCIATE_MODE_E CNcomment:see DMX_DESC_ASSOCIATE_MODE_E CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_DESC_ASSOCIATE_MODE_E
     */
    S32 (*dmx_descrambler_open)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32DescId, const DMX_DESC_ASSOCIATE_MODE_E enMode);

    /**
     \brief allocate descrambler expansion interface . CNcomment:����һ������ͨ����չ�ӿ�.CNend
     \attention \n
    CNcomment:��Щƽ̨,��ca���ܵ���cw�������ĵĻ�,��Ҫ�� DMX_CA_ADVANCE_DESCRAMBLER���Ե�descrambler,
     ������ܵ���cw�����ĵĻ���Ҫ��һ��DMX_CA_NORMAL_DESCRAMBLER���Ե�descrambler CNend
     \param[in] enDemuxId demux id.CNcomment:�⸴����ID CNend
     \param[out] pu32DescId  descrambler id pointer. CNcomment:����ͨ��ID ָ��CNend
     \param[in] pstDesramblerAttr  descrambler attribute. CNcomment:��������������CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_DESC_ASSOCIATE_MODE_E, DMX_DESCRAMBLER_TYPE_E
     */

    S32 (*dmx_descrambler_open_ex)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32DescId, const DMX_DESCRAMBLER_ATTR_S* pstDesramblerAttr);

    /**
     \brief enable a descrambler. CNcomment:enable һ������ͨ����CNend
     \attention \n
    CNcomment:����������֮ǰ,����enable. CNend
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_descrambler_enable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId );

    /**
     \brief disable a descrambler. CNcomment:disable һ������ͨ��.CNend
     \attention \n
    CNcomment:see dmx_opendescrambler. CNend
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_descrambler_disable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId );

    /**
     \brief close a descrambler. CNcomment:�ر� һ������ͨ��. CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_descrambler_close)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId );

    /**
     \brief associate descrambler. CNcomment:��������������Ҫ����PID����ͨ��. CNend
     \attention \n
    CNcomment:��pid����channel��p_params->m_mode����
    ��p_params->m_mode==DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDSʱ,  ���m_pid==INVALID_PID, ��ȡ����ǰ�Ĺ���(Disassociate)
    ��������Ҫ���й���
    ��p_params->m_mode==DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNELʱ,  ���m_channel_id==DMX_INVALID_PID, ��ȡ����ǰ�Ĺ���(Disassociate)
    ��������Ҫ���й���.
    �����PID����, ��PIDͨ����û��OPEN,�������,�����سɹ�.(CA ��AV �첽���õ�����.)    CNend
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[in] pstParams associate param pointer.CNcomment: ��������ָ��.  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_DESC_ASSOCIATE_PARAMS_S
     */
    S32 (*dmx_descrambler_associate)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DESC_ASSOCIATE_PARAMS_S* const pstParams );

    /**
     \brief get associate info. CNcomment:��ȡ�����������Ľ���PID����ͨ��. CNend
     \attention \n
    CNcomment: ��������û�й���ʱ,    ���p_params->m_mode==DMX_DESCRAMBLER_ASSOCIATE_WITH_PIDS��m_pid=DMX_INVALID_PID
    ���p_params->m_mode==DMX_DESCRAMBLER_ASSOCIATE_WITH_CHANNEL��m_channel_id=DMX_INVALID_CHN_ID  CNend
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[out] pstParams associate param pointer.CNcomment: ��������ָ��.  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_DESC_ASSOCIATE_PARAMS_S
     */
    S32 (*dmx_descrambler_get_associate_info)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, DMX_DESC_ASSOCIATE_PARAMS_S* const pstParams);

    /**
     \brief set even key for descrambler. CNcomment:���ý���ͨ����ż��Կ��CNend
     \attention \n
     CNcomment:����������֮ǰ,����set key. CNend
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[in] pu8Key pointing to the key .CNcomment:ָ�������Կ��ָ��.  CNend
     \param[in] u32Len the lenth of key.:��Կ����.  CNend
     \param[in] u32Option retention param.CNcomment:��������.  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_descrambler_set_even_key)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8Key, const U32 u32Len, const U32 u32Option );

    /**
     \brief set even key iv for descrambler. CNcomment:���ý���ͨ����ż��Կ��Ӧ���ݵĳ�ʼ������CNend
     \attention \n
     CNcomment: ��. CNend
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[in] pu8IV pointing to the IV .CNcomment:ָ���ʼ������ָ��.  CNend
     \param[in] u32Len the lenth of IV. CNcomment:��������.  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_descrambler_set_even_iv)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8IV, const U32 u32Len);

    /**
     \brief set odd key for descrambler. CNcomment:���ý���ͨ��������Կ��CNend
     \attention \n
     CNcomment:����������֮ǰ,����set key. CNend
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[in] pu8Key pointing to the key .CNcomment:ָ�������Կ��ָ��.  CNend
     \param[in] u32Len the lenth of key.:��Կ����.  CNend
     \param[in] u32Option retention param.CNcomment:��������.  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_descrambler_set_odd_key)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8Key, const U32 u32Len, const U32 u32Option );

    /**
     \brief set even key iv for descrambler. CNcomment:���ý���ͨ��������Կ��Ӧ���ݵĳ�ʼ������CNend
     \attention \n
     CNcomment: ��. CNend
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[in] pu8IV pointing to the IV .CNcomment:ָ���ʼ������ָ��.  CNend
     \param[in] u32Len the lenth of IV. CNcomment:��������.  CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_descrambler_set_odd_iv)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const U8* const pu8IV, const U32 u32Len);

    /**
     \brief set descrambler attribute. CNcomment:���� ����ͨ�����ԡ�CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[in] pstAttr descrambler attribute.CNcomment:����ͨ������ CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_set_descrambler_attribute)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, DMX_DESCRAMBLER_ATTR_S* pstAttr );

    /**
     \brief get descrambler attribute. CNcomment:��ȡ����ͨ�����ԡ�CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[out] pstAttr descrambler attribute pointer.CNcomment:����ͨ�����Խṹ��ָ�� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_get_descrambler_attribute)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, DMX_DESCRAMBLER_ATTR_S* pstAttr );

    /**
     \brief set dcas keyladder TS descrambling parameters. CNcomment����DCAS keyladder TS�����Ų�����CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[in] pstDcasKLConfig DCAS keyladder config pointer.CNcomment:DCAS keyladder���ýṹ��ָ�� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */

    S32 (*dmx_dcas_keyladder_config)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DCAS_KEYLADDER_SETTING_S* pstDcasKLConfig);

    /**
     \brief get DA(nonce). CNcomment��ȡDA(nonce)��CNend
     \attention \n
     \param[in] u32DescId descrambler id.CNcomment:����ͨ��ID.  CNend
     \param[in] pstDcasNonceConfig DCAS keyladder nonce config pointer.CNcomment:DCAS keyladder Nonce���ýṹ��ָ�� CNend
     \param[out] pu8DANonce DA(nonce) result. CNcomment:DA(nonce)������ CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */

    S32 (*dmx_dcas_get_nonce)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32DescId, const DMX_DCAS_NONCE_SETTING_S* pstDcasNonceConfig, U8* pu8DANonce);

    /**
     \brief Open an filter. CNcomment:��һ����������������������Ƶ���� CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] pstFilterOpenPara open param.CNcomment:�򿪲��� CNend
     \param[out] pu32AVFilterId av filter id .CNcomment:��������� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_PARSER_FILTER_OPEN_PARAM_S
     */
    S32 (*dmx_avfilter_open)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32AVFilterId, const DMX_PARSER_FILTER_OPEN_PARAM_S* const pstFilterOpenPara);

    /**
     \brief Enable demux av filter. CNcomment:ʹ��av������ CNend
     \attention \n
     \param[in] pu32AVFilterId av filter id.CNcomment:��������� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_avfilter_enable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId);

    /**
     \brief Get part of es frame. CNcomment:��ȡ֡���ݲ��֡�CNend
     \attention \n
     Got data maybe not a whole frame. CNcomment:��ȡ�������ݿ��ܲ���������֡���� CNend
     \param[in] pu32AVFilterId av filter id .CNcomment:��������� CNend
     \param[out] pstFrameInfo point to es frame data.CNcomment:��ȡ����֡����ָ�� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_ESFRAME_INFO_S
     */
    S32 (*dmx_avfilter_get_esframe)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId, DMX_ESFRAME_INFO_S* pstFrameInfo);

    /**
     \brief Release es frame. CNcomment:�ͷ�֡���ݡ�CNend
     \attention \n
        If you release buffers by calling this API, the buffers must be those obtained by calling ::dmx_avfilter_get_esframe, and the addresses and sizes of these buffers cannot be changed.\n
        CNcomment:���ӿ��ͷŵĻ�����һ����ͨ��::dmx_avfilter_get_esframe��ȡ�Ļ��������������ĵ�ַ�ͳ��Ȳ��ܸ���CNend
     \param[in] pu32AVFilterId av filter id .CNcomment:��������� CNend
     \param[in] pstFrameInfo point to es frame data.CNcomment:֡����ָ�� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::DMX_DESC_TYPE_E
     */
    S32 (*dmx_avfilter_release_esframe)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId, DMX_ESFRAME_INFO_S* pstFrameInfo);

    /**
     \brief Disable demux av filter. CNcomment:ȥʹ��av������ CNend
     \attention \n
     \param[in] pu32AVFilterId av filter id. CNcomment:��������� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_avfilter_disable)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId);

    /**
     \brief Close an filter. CNcomment:�ر�һ����������������������Ƶ���� CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] pu32AVFilterId av filter id .CNcomment:��������� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_avfilter_close)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32AVFilterId);

    /**
     \brief Open a pcr channel. CNcomment:��һ��pcrͨ�� CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] u32Pid PCR PID .CNcomment:PCRͨ��PID CNend
     \param[out] pu32PcrId  id .CNcomment:��� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_pcr_open)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32PcrId, const U32 u32Pid);

    /**
     \brief Close a pcr channel. CNcomment:�ر�һ��pcrͨ�� CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] u32PcrId  id .CNcomment:��� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_pcr_close)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32PcrId);

    /**
     \brief Get pcr. CNcomment:��ȡpcr CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[in] u32PcrId  id .CNcomment:��� CNend
     \param[out] pu64StcTime  Stc time .CNcomment:Stcʱ�� CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_pcr_get)(struct _DEMUX_DEVICE_S* pstDev, const U32 u32PcrId, U64* pu64StcTime);

    /**
     \brief Creates a TS buffer for the RAM port to receive the TS data from Internet or local memory.
      CNcomment:ΪRAM�˿ڴ���TS Buffer���ڽ��մ�����򱾵ش洢�������TS���ݡ�CNend
     \attention \n
     \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
     \param[out] pu32TsBufferId ts buffer id .CNcomment:TS������ CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_tsbuffer_create)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, U32* const pu32TsBufferId);

    /**
     \brief Obtains a TS buffer to input data.CNcomment:��ȡTS Buffer�ռ䣬�����������롣CNend
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
    CNcomment:�ظ�get����ͬһ��buffer��ַ\n
    ��������ʱע��ÿ����������ݳ��ȣ�̫�����ܻᵼ���������ݲ���ʱ\n
    ̫�̿��ܻᵼ�µ���̫Ƶ���������½�\n
    ��ʣ��ռ�С�ڵ�������ĳ���ʱ�����ش�����\n
    ÿ������ĳ���ҪС��ʣ��ʣ�೤�ȣ���buffer�����ܱ�����\n
    ���󳤶Ȳ�����Ϊ0�����򷵻ز����Ƿ�������\n
    u32TimeoutMs����Ϊ0��ʾ���ȴ�������Ϊ0xffffffff��ʾһֱ�ȴ�������Ϊ����ֵ��ʾ�ȴ�u32TimeoutMs���롣\n
    ����������ʱ�䣬���޷����뵽Buffer���򷵻�ERROR_DMX_TIMEOUT������\n
    u32TimeoutMs����Ϊ0ʱ��������벻��Buffer��˵����ʱ�ڲ�TS Buffer�ռ���������Ҫͨ��usleep(10000)�ͷ�cpu
    ��ʹ�����߳��ܹ��õ����ȡ�CNend
    \param[in] u32TsBufferId Handle of a TS buffer.CNcomment:TS Buffer�����CNend
    \param[in] u32Size Requested data length.CNcomment:�������ݵĳ��ȡ�CNend
    \param[in] u32TimeoutMs      Wait timeout, in ms.CNcomment:�ȴ���ʱʱ�䣬��λms��CNend
    \param[out] pstStreamData  Data buffer.CNcomment:����buffer�ṹ��CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_tsbuffer_get)(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId, U32 u32Size, U32 u32TimeoutMs, DMX_STREAM_DATA_S* pstStreamData);

    /**
     \brief Updates the write pointer of a TS buffer after the TS data is input.CNcomment:TS����������ϣ����ڸ���TS Bufferдָ�롣CNend
     \attention \n
    This API must work with dmx_tsbuffer_get. That is, if you call dmx_tsbuffer_put without calling dmx_tsbuffer_get, no operation takes effect, but the error code SUCCESS is returned.\n
    If the valid data length is 0, no operation takes effect, and the error code SUCCESS.\n
    The valid data length cannot be greater than data length queried by calling dmx_tsbuffer_get. Otherwise, the error code HI_ERR_DMX_INVALID_PARA is returned.\n
    If the valid data length is smaller than the data length queried by calling dmx_tsbuffer_get, it indicates that a part of data is stored.
    CNcomment:�˽ӿڱ����Get�ӿ����ʹ�ã����û��Get�����Put�������򲻻�����κβ����������سɹ�\n
    Put�ĳ������Ϊ0��Ҳ��������κβ���ֱ�ӷ��سɹ�\n
    ������Put���ȴ���ʵ��Get���ĳ��ȣ����򷵻ز����Ƿ�������\n
    ����Put����С��Get���ȣ�����ֻ������һ��������\n
    Ϊ���Ч�ʣ�Put�ĳ��Ⱦ�����Ҫ̫�̣�����������10��ts������Putһ�Σ�����̫�̻ᵼ�������½�\n��CNend
    \param[in] u32TsBufferId Handle of a TS buffer.CNcomment:TS Buffer�����CNend
    \param[in] u32ValidDataLen Valid data length.CNcomment:��Ч���ݵĳ��ȡ�CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_tsbuffer_put)(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId, U32 u32ValidDataLen);

    /**
    \brief Destroys an existing TS buffer. CNcomment:���ٴ�����TS Buffer��CNend
     \attention \n
    A TS buffer cannot be destroyed repeatedly. If a TS buffer is destroyed, its handle is also destroyed.\n
    In addition, if a buffer is destroyed, its data is cleared. In this case, the get and put operations are not available.\n
    However, the data in channels is retained when a TS buffer is destroyed. To switch streams, you need disable the channel, and then enable the channel again.
    CNcomment:�����ظ�����һ��TS Buffer,����֮��handle�Ͳ�������\n
    ����֮��buffer�е����ݾͻᱻ��գ������ٽ���Get��Put����\n
    ����TS buffer���������ͨ�������ݣ�Ҫ�л�������Ҫע��ر�ͨ�������´򿪡�CNend
    \param[in] u32TsBufferId Handle of a TS buffer.CNcomment:TS Buffer�����CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
     */
    S32 (*dmx_tsbuffer_destroy)(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId);

#ifdef HAL_HISI_EXTEND_H
    /**
    \brief Creates a TS buffer for the RAM port to receive the TS data from Internet or local memory. CNcomment:ΪRAM�˿ڴ���TS Buffer���ڽ��մ�����򱾵ش洢�������TS����CNend
    \attention \n
    A TS buffer can be created for the RAM port only.\n
    The TS buffer cannot be created for the same port for multiple times; otherwise, an error code is returned.
    CNcomment:ֻ��RAM �˿ڿ��Դ���TS Buffer\n
    ͬһ�˿ڲ����ظ�����TS Buffer�����򷵻ش��� CNend
    \param[in] enDemuxId demux id.CNcomment:demux ID.  CNend
    \param[in] pstBufAttr Attributes of a TS buffer.CNcomment:TS Buffer��������CNend
    \param[out] pu32TsBufferId ts buffer id .CNcomment:TS������ CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    */
    S32 (*dmx_tsbuffer_create_ex)(struct _DEMUX_DEVICE_S* pstDev, const DMX_ID_E enDemuxId, DMX_TSBUF_ATTR_S* pstBufAttr, U32* const pu32TsBufferId);

    /**
    \brief Obtains a TS buffer to input data.CNcomment:��ȡTS Buffer�ռ䣬�����������롣CNend
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
    CNcomment:�ظ�get����ͬһ��buffer��ַ\n
    ��������ʱע��ÿ����������ݳ��ȣ�̫�����ܻᵼ���������ݲ���ʱ\n
    ̫�̿��ܻᵼ�µ���̫Ƶ���������½�\n
    ��ʣ��ռ�С�ڵ�������ĳ���ʱ�����ش�����\n
    ÿ������ĳ���ҪС��ʣ��ʣ�೤�ȣ���buffer�����ܱ�����\n
    ���󳤶Ȳ�����Ϊ0�����򷵻ز����Ƿ�������\n
    u32TimeoutMs����Ϊ0��ʾ���ȴ�������Ϊ0xffffffff��ʾһֱ�ȴ�������Ϊ����ֵ��ʾ�ȴ�u32TimeoutMs���롣\n
    ����������ʱ�䣬���޷����뵽Buffer���򷵻�ERROR_DMX_TIMEOUT������\n
    u32TimeoutMs����Ϊ0ʱ��������벻��Buffer��˵����ʱ�ڲ�TS Buffer�ռ���������Ҫͨ��usleep(10000)�ͷ�cpu
    ��ʹ�����߳��ܹ��õ����ȡ�CNend
    \param[in] u32TsBufferId Handle of a TS buffer.CNcomment:TS Buffer�����CNend
    \param[in] u32Size Requested data length.CNcomment:�������ݵĳ��ȡ�CNend
    \param[in] u32TimeoutMs      Wait timeout, in ms.CNcomment:�ȴ���ʱʱ�䣬��λms��CNend
    \param[out] pstStreamData  Data buffer.CNcomment:����buffer�ṹ��CNend
    \param[out] pu32PhyAddr  buffer physical address.CNcomment:buffer�������ַ��CNend
     \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    */
    S32 (*dmx_tsbuffer_get_ex)(struct _DEMUX_DEVICE_S* pstDev, U32 u32TsBufferId, U32 u32Size, U32 u32TimeoutMs, DMX_STREAM_DATA_S* pstStreamData, U32 *pu32PhyAddr);
#endif

    /**
    \brief get TEE keyladder streampath . CNcomment:��ȡ��TEE������keyladder����Ҫ��streampath������CNend
     \attention \n
    TEE attach descrambler, requires REE side to provide streampath information.
    CNcomment:TEE����ҪREE��streampath��Ϣ���ܰ󶨽�������CNend
    \param[in] enDemuxId Demux id.CNcomment:demux ID��CNend
    \param[out] pstStreamData  streampath data, bytes stream.CNcomment:streampath���ݣ��ֽ�����CNend
    \param[out] pStreamPathLength  streampath data length.CNcomment:streampath���ݳ��ȡ�CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_DMX_OP_FAILED DMX operate failed.CNcomment:DMX�豸��������CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    */
    S32 (*dmx_get_streampath_param)(struct _DEMUX_DEVICE_S *pstDev, DMX_ID_E enDemuxId, UCHAR  *pStreamPath, S32 *pStreamPathLength);
} DEMUX_DEVICE_S;


/**
\brief direct get demux device api, for linux and android.CNcomment:��ȡdemux�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get demux device api��for linux and andorid.
CNcomment:��ȡdemux�豸��linux��androidƽ̨������ʹ��. CNend
\retval  demux device pointer when success.CNcomment:�ɹ�����demux�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::DEMUX_DEVICE_S

\par example
*/
DEMUX_DEVICE_S *getDemuxDevice();

/**
\brief Open HAL demux module device.CNcomment: ��HAL�⸴��ģ���豸 CNend
\attention \n
Open HAL demux module device( for compatible android HAL).
CNcomment: ��HAL�⸴��ģ���豸(for compatible Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice demux device structure.CNcomment:demux�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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
\brief Close HAL demux module device.CNcomment:�ر�HAL�⸴��ģ���豸 CNend
\attention \n
Close HAL demux module device(for compatible Android HAL).
CNcomment:�ر�HAL�⸴��ģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice demux device structure.CNcomment:demux�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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
