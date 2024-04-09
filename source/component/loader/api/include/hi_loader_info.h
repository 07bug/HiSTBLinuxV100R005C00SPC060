/*******************************************************************************
 *             Copyright 2013 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: hi_loader_info.h
 * Description:
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 ******************************************************************************/
#ifndef __HI_LOADER_INFO_H__
#define __HI_LOADER_INFO_H__

#include "hi_type.h"
#include "hi_unf_frontend.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      LOADER */
/** @{ */  /** <!--[LOADER] */

/**Maximum length of upgrade file name*/
/**CNcomment:�����ļ�������󳤶�*/
#define LOADER_FILE_NAME_LEN 128

/**Maximum length of user name.*/
/**CNcomment:�û�������󳤶� */
#define LOADER_USER_NAME_LEN 32

/**Maximum length of password.*/
/**CNcomment:�������󳤶� */
#define LOADER_PASSWORD_LEN 32

/**IP address definition*/
/**CNcomment:IP��ַ����*/
typedef HI_U32 HI_IPAddr;

/**IP port number definition*/
/**CNcomment:IP�˿ںŶ���*/
typedef HI_U16 HI_IPPort;

#define DEF_CHECK_FLAG 0x5a5a5a5a

/**Upgrade type definition*/
/**CNcomment:�������Ͷ���*/
typedef enum tagLOADER_TYPE_E
{
    HI_LOADER_TYPE_OTA = 0, /**< Cable upgrade *//**<CNcomment: CABLE ���� */
    HI_LOADER_TYPE_IP, /**< IP upgrade *//**<CNcomment: IP���� */
    HI_LOADER_TYPE_USB, /**< USB upgrade *//**<CNcomment: USB���� */
    HI_LOADER_TYPE_BUTT, /**< Do not upgrade *//**<CNcomment: ������ */
} HI_LOADER_TYPE_E;

/**Definition of the IP address type used in IP upgrade*/
/**CNcomment:����ʱʹ������Э�鶨��*/
typedef enum tagProto_TYPE_E
{
    HI_PROTO_TFTP = 0, /**<Use TFTP protocol*//**<CNcomment: TFTPЭ������ */
    HI_PROTO_FTP, /**<Use FTP protocol*//**<CNcomment: FTPЭ������ */
    HI_PROTO_HTTP, /**<Use HTTP protocol*//**<CNcomment: HTTPЭ������*/

    HI_PROTO_BUTT
} HI_PROTO_TYPE_E;

/**CNcomment:IP����ʱʹ��IP��ַ���Ͷ���*/
typedef enum tagIP_TYPE_E
{
    HI_IP_STATIC = 0, /**< Use static IP *//**<CNcomment: ʹ�þ�̬IP */
    HI_IP_DHCP, /**< Use dynamic IP *//**<CNcomment: ʹ�ö�̬IP */
    HI_IP_BUTT,
} HI_IP_TYPE_E;

/**TUNER signal type*/
typedef enum tagTunerSignalType_E
{
    HI_TUNER_SIG_TYPE_CAB = 0,     /**<Cable signal*//**<CNcomment: �����ź� */
    HI_TUNER_SIG_TYPE_TER,         /**<Terrestrial signal*//**<CNcomment: �����ź� */
    HI_TUNER_SIG_TYPE_SAT,          /**<Satellite signal*//**<CNcomment: �����ź� */

    HI_TUNER_SIG_TYPE_BUTT           /**invalid type*//**<CNcomment: ��Ч�ź����� */
} HI_TUNER_SIG_TYPE_E;

typedef struct hiLOADER_USB_PARAM_S
{
    HI_S8 as8FileName[LOADER_FILE_NAME_LEN];
} HI_LOADER_USB_PARAM_S;

/**Parameter for DiSEqC 1.0/2.0 switch
   Some DiSEqC device need set polarization(13/18V) and 22K, you can set them here. */

/**CNcomment:DiSEqC 1.0/2.0 ���ز�����ЩDiSEqC�豸��Ҫ���ü�����ʽ��22K�ģ�������������豸����Ҫ���������� */
typedef struct hiTunerSwitch4Port_S
{
    HI_U32 u32Level;  /**<DiSEqC device level*//**<CNcomment: ���� */
    HI_U32 u32Port;   /**<DiSEqC switch port*//**<CNcomment:  ���ض˿�*/
    HI_U32 u32Polar;  /**<Polarization type *//**<CNcomment:  ������ʽ*/
    HI_U32 u32LNB22K; /**<22K status*//**<CNcomment: 22K����״̬ */
} HI_TUNER_SWITCH4PORT_S;

/**Parameter for DiSEqC 1.1/2.1 switch */
/**CNcomment:DiSEqC 1.1/2.1 ���ز��� */
typedef struct hiTunerSwitch16PORT_S
{
    HI_U32 u32Level;          /**<DiSEqC device level*//**<CNcomment: ���� */
    HI_U32 u32Port;           /**<DiSEqC switch port*//**<CNcomment: ���ض˿� */
} HI_TUNER_SWITCH16PORT_S;

/*Define Cable tuner parameter */
typedef struct tagLoaderCabPara
{
    HI_U32 u32OtaPid;          /**< TS PID. The parameter is vital and set it with caution..*//**<CNcomment: PID */
    HI_U32 u32OtaFreq;         /**< frequency pointer in kHz, for example, 403000. *//**<CNcomment: Ƶ�㣬��λ kHz */
    HI_U32 u32OtaSymbRate;     /**< symbol rate in kbps, for example, 6875. *//**<CNcomment: �����ʣ���λ kbps */
    HI_U32 u32OtaModulation;   /**< constellation count.0:16QAM 1:32QAM 2:64QAM 3:128QAM 4:256QAM  *//**<CNcomment: QAM��ʽ��0:16QAM 1:32QAM 2:64QAM 3:128QAM 4:256QAM  */
} HI_LOADER_CAB_PARA_S;

/*Define Terrestrial tuner parameter */
typedef struct tagLoaderTerPara
{
    HI_U32 u32OtaPid;          /**< TS PID. The parameter is vital and set it with caution..*//**<CNcomment: PID */
    HI_U32 u32OtaFreq;         /**< frequency pointer in kHz, for example, 177500. *//**<CNcomment: Ƶ�㣬��λ kHz */
    HI_U32 u32OtaBandWidth;     /**< BandWidth in kHz, for example, 7000. *//**<CNcomment: ������λ kHz */
    HI_U32 u32OtaModulation;   /**< constellation count.0:16QAM 1:32QAM 2:64QAM 3:128QAM 4:256QAM  *//**<CNcomment: QAM��ʽ��0:16QAM 1:32QAM 2:64QAM 3:128QAM 4:256QAM  */
	HI_UNF_TUNER_TER_MODE_E     enChannelMode;      //dvb-t2
    HI_UNF_TUNER_TS_PRIORITY_E  enDVBTPrio;         //dvb-t
} HI_LOADER_TER_PARA_S;

/*Define Sat tuner parameter */
typedef struct tagLoaderSatPara
{
    HI_U32 u32OtaPid;          /**< TS PID. The parameter is vital and set it with caution..*//**<CNcomment: PID */
    HI_U32 u32OtaFreq;         /**< frequency pointer in kHz, for example, 403000. *//**<CNcomment: Ƶ�㣬��λ kHz */
    HI_U32 u32OtaSymbRate;     /**< symbol rate in kbps, for example, 27500. *//**<CNcomment: �����ʣ���λ kbps */
    HI_U32 u32Polar;                /**<Polarization type:
                                                 0:Horizontal Polarization
                                                 1:Vertical Polarization
                                                 2:Left-hand circular polarization
                                                 3:Right-hand circular polarization>*/

    HI_U32 u32LowLO;           /**< Low Local Oscillator Frequency, MHz *//**<CNcomment: �ͱ��� */
    HI_U32 u32HighLO;          /**< High Local Oscillator Frequency, MHz*//**<CNcomment: �߱��� */

    /*support kinds of switch, support class-relation*/
    /**CNcomment:֧�ָ��ֿ��أ�֧�ּ��� */
    HI_TUNER_SWITCH16PORT_S st16Port;
    HI_TUNER_SWITCH4PORT_S  st4Port;
    HI_U32                  u32Switch22K; /** 22KHz switch *//**<CNcomment: 22K���� */
    HI_U32                  u32LNBPower;/*LNB Power*//**<CNcomment: LNB������� */
    HI_BOOL   u32UnicFlag;             /**<u32UnicFlag, used by unicable .*//**<CNcomment: unicableʹ�ñ�־λ */
} HI_LOADER_SAT_PARA_S;

/*Define Turner parameter */
typedef struct tagOTAParaInfo
{
    HI_UNF_TUNER_SIG_TYPE_E eSigType;         /**<Signal type*//**<CNcomment: �ź����� */
    union
    {
        HI_LOADER_CAB_PARA_S stCab;       /**<Cable signal parameter *//**<CNcomment: �����źŲ��� */
        HI_LOADER_SAT_PARA_S stSat;        /**<Satellite signal parameter*//**<CNcomment: �����źŲ��� */
        HI_LOADER_TER_PARA_S stTer;        /**<Terrestrial signal parameter*//**<CNcomment: �����źŲ��� */
    } unConnPara;
} HI_LOADER_OTA_PARA_S;

/* Define IP upgrade parameter. */
typedef struct tagIpParam_S
{
    HI_PROTO_TYPE_E eProtoType; /**< Protocol of data download 0:TFTP, 1:FTP, 2 HTTP>*//**<CNcomment: ��������Э�� 0:TFTP, 1:FTP, 2 HTTP */
    HI_IP_TYPE_E    eIpType; /**< IP obtaining mode.*/            /**<CNcomment: ip��ȡ���� */

    /*Configure the following parameters only when static IP addresses are used.*/
    HI_IPAddr ipOurIp; /**< Local IP address. *//**<CNcomment: ����ip */
    HI_IPAddr ipGateway; /**< Gateway*//**<CNcomment: ���� */
    HI_IPAddr ipSubnetMask; /**< Subnet mask*//**<CNcomment: �������� */
    HI_IPAddr ipServer; /**< Server IP address. *//**<CNcomment: ������ip */
    HI_IPPort ipServerPort; /**< Server port.*/ /**<CNcomment: ������port */
    HI_S8     as8FileName[LOADER_FILE_NAME_LEN]; /**< Upgrade file name.*/    /**<CNcomment:�����ļ��� */
    HI_U32    u32FileSize; /* Size of upgrade file.*/          /**<CNcomment: �����ļ���С */
    HI_S8     as8UserName[LOADER_USER_NAME_LEN];    /**<Username, used by FTP.*//**<CNcomment: �û��� */
    HI_S8     as8Password[LOADER_USER_NAME_LEN];    /**<Password, used by FTP .*//**<CNcomment: ���� */
} HI_LOADER_IP_PARA_S;

/** Data structure for defining upgrade parameters*/
/**CNcomment:���������������ӿڽṹ��*/
typedef struct hiLOADER_PARAMETER_S
{
    /* Variable for the interaction between the application and loader */
    HI_LOADER_TYPE_E eUpdateType;        /**< Update type*//**<CNcomment: ��������*/

    union
    {
        HI_LOADER_OTA_PARA_S stOTAPara;        /**< ota upgrade parameters *//**<CNcomment: ota����*/
        HI_LOADER_IP_PARA_S stIPParam;          /**< ip upgrade parameters*//**<CNcomment: ip��������*/
        HI_LOADER_USB_PARAM_S stUSBParam;    /*usb upgrade parameters*//**<CNcomment: usb��������*/
    } stPara;

    HI_U32 u32CurSoftware;    /**< application software version *//**<CNcomment: ����汾��*/

    HI_U8 au8AppUse[20];      /**< Private upper-layer application *//**<CNcomment: App ����*/
} HI_LOADER_PARAMETER_S;

/**STB infor */
typedef struct hiLOADER_STBINFO_S
{
    HI_U32 u32OUI; /**< Vendor ID *//**<CNcomment: ����id */
    HI_U32 u32AreaCode; /**< Region code *//**<CNcomment: ������*/
    HI_U32 u32HWVersion; /**< Hardware version *//**<CNcomment: Ӳ���汾�� */
    HI_U32 u32HWSerialNum; /**< Hardware serial number *//**<CNcomment: Ӳ��ϵ�к�*/
} HI_LOADER_STB_INFO_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      LOADER */
/** @{ */  /** <!-- [LOADER] */

/**
 \brief Obtains upgrade parameter data from the flash or E2ROM. CNcomment:��FLASH��E2ROM�л�ȡ�����������ݡ�CNend
 \attention \n
 \param[out] info    Upgrade parameters. The memory is allocated externally.
CNcomment:\param[out] info  loader��������,�ⲿ�����ڴ档CNend
 \retval ::HI_SUCCESS Success. CNcomment:�ɹ���CNend
 \retval ::HI_FAILURE This API fails to be called.  CNcomment:APIϵͳ����ʧ�ܡ�CNend
 \see ::HI_LOADER_PARAMETER_S \n
For details, see the definition in HI_LOADER_PARAMETER_S.
CNcomment:��ϸ��Ϣ,��ο�HI_LOADER_PARAMETER_S���塣CNend
 */
HI_S32 HI_LOADER_ReadParameters(HI_LOADER_PARAMETER_S* info);

/**
 \brief This API is used to update upgrade parameters to the flash or E2ROM. CNcomment:���������������ݵ�FLASH��E2ROM��CNend
 \attention \n
 \param[in] info  Upgrade parameters to be updated.
CNcomment:\param[in] info   Ҫ���µ�����������CNend
 \retval ::HI_SUCCESS Success. CNcomment:�ɹ���CNend
 \retval ::HI_FAILURE This API fails to be called. CNcomment:APIϵͳ����ʧ�ܡ�CNend
 \see ::HI_LOADER_PARAMETER_S \n
For details, see the definition in HI_LOADER_PARAMETER_S.
CNcomment:��ϸ��Ϣ,��ο�HI_LOADER_PARAMETER_S���塣CNend
 */
HI_S32 HI_LOADER_WriteParameters(HI_LOADER_PARAMETER_S* info);

/**
 \brief Obtains STB serial number from the flash or E2ROM.CNcomment:��FLASH��E2ROM�л�ȡ���������к���Ϣ��CNend
 \attention \n
Serial number information includes the hardware version and vendor ID to be verified during the upgrade. Different service provider and vendors have different serial numbers for STBs.\n
CNcomment:���кź�������ʱ��Ҫ�Ƚϵ�Ӳ���汾��,���̱�š���ͬ����Ӫ�̺ͳ����в�ͬ�Ĺ������е����кš�\n CNend
A serial number contains the following information:\n
          External serial number, such as  00000003-00000001-1d000021      \n
          External serial number is in the following format:\n
          AAAAAAAA-BBBBBBBB-CCCCCCCC ....\n
          AAAAAAAA 	Terminal product vendor authentication number\n
          BBBBBBBB 	Hardware version\n
          CCCCCCCC 	Hareware serial number.\n

CNcomment:���кŵĸ�ʽ�������: \n
          �������к���:  00000003-00000001-1d000021�� \n
          �������кŸ�ʽ����: \n
          AAAAAAAA-BBBBBBBB-CCCCCCCC ....\n
          AAAAAAAA 	�ն˲�Ʒ����������֤��š� \n
          BBBBBBBB 	Ӳ���汾�š�\n
          CCCCCCCC 	Ӳ��ϵ�кš�\n CNend
 \param[out] pstStbinfo  STB serial number information. The memory is allocated externally.CNcomment:���������к���Ϣ.�ⲿ�����ڴ档 CNend
 \retval ::HI_SUCCESS Success. CNcomment:�ɹ��� CNend
 \retval ::HI_FAILURE  This API fails to be called. CNcomment:APIϵͳ����ʧ�ܡ� CNend
 \see ::HI_LOADER_STB_INFO_S \n
For details, see the definition in HI_LOADER_STB_INFO_S.
CNcomment:��ϸ��Ϣ,��ο�HI_LOADER_STB_INFO_S���塣 CNend
 */
HI_S32 HI_LOADER_ReadSTBInfo(HI_LOADER_STB_INFO_S* pstStbinfo);

/**
 \brief Upgrades flash or E2ROM STB serial number.CNcomment:����FLASH��E2ROM���������к���Ϣ�� CNend
 \attention \n
Serial number information includes the hardware version and vendor ID to be verified during the upgrade. \n
Different carriers and vendors have different serial numbers for STBs.\n
You can change the serial number rules as required. \n
This API responds to the au8OutSn(STB  external serial number).
CNcomment:���кź�������ʱ��Ҫ�Ƚϵ�Ӳ���汾��,���̱�š�\n CNend
CNcomment:��ͬ����Ӫ�̺ͳ����в�ͬ�Ĺ������е����кţ�\n CNend
CNcomment:�û��ɸ���ʵ����Ҫ���޸����кŹ���\n CNend
CNcomment:�ýӿ�ֻ���au8OutSn(�������ⲿ���к�)������\n CNend
A serial number contains the following information:\n
          External serial number, such as  00000003-00000001-1d000021      \n
          External serial number is in the following format:\n
          AAAAAAAA-BBBBBBBB-CCCCCCCC ....\n
          AAAAAAAA 	Terminal product vendor authentication number\n
          BBBBBBBB 	Hardware version\n
          CCCCCCCC 	Hareware serial number.\n

CNcomment:���кŵĸ�ʽ�������: \n
          �������к���:  00000003-00000001-1d000021�� \n
          �������кŸ�ʽ����: \n
          AAAAAAAA-BBBBBBBB-CCCCCCCC ....\n
          AAAAAAAA 	�ն˲�Ʒ����������֤��š� \n
          BBBBBBBB 	Ӳ���汾�š�\n
          CCCCCCCC 	Ӳ��ϵ�кš�\n CNend
 \param[out] pstStbinfo  STB serial number information. The memory is allocated externally.CNcomment:���������к���Ϣ.�ⲿ�����ڴ档\nCNend
 \retval ::HI_SUCCESS Success. CNcomment:�ɹ���CNend
 \retval ::HI_FAILURE  This API fails to be called. CNcomment:APIϵͳ����ʧ�ܡ�CNend
 \see ::HI_LOADER_STB_INFO_S \n
For details, see the definition in HI_LOADER_STB_INFO_S
CNcomment:��ϸ��Ϣ,��ο�HI_LOADER_STB_INFO_S���塣CNend
 */
HI_S32 HI_LOADER_WriteSTBInfo(HI_LOADER_STB_INFO_S* pstStbinfo);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
 #if __cplusplus
}

 #endif
#endif

#endif
