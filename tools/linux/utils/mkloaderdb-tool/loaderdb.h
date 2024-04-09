/*********************************************************************************
*
*  Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
*
*  This program is confidential and proprietary to Hisilicon Technologies Co., Ltd.
*  (Hisilicon), and may not be copied, reproduced, modified, disclosed to
*  others, published or used, in whole or in part, without the express prior
*  written permission of Hisilicon.
*
***********************************************************************************/

/*******************************************************************************/

#ifndef __LOADERDB_H__
#define __LOADERDB_H__

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define LOADER_INFOBASIC  "loaderdb"

typedef unsigned short HI_U16;
typedef unsigned char  HI_U8;
typedef unsigned int   HI_U32;

typedef short        HI_S16;
typedef char         HI_S8;
typedef int          HI_S32;
typedef void         HI_VOID;
typedef unsigned int HI_HANDLE;

typedef enum {
    HI_FALSE    = 0,
    HI_TRUE     = 1,
} HI_BOOL;

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2*/
/** @{ */  /** <!- [Data structure of loader upgrade parameter area] */

/**LOADER magic number of DB and OTA parameters. it is used as a flag of data verification.*/
/**CNcomment:LOADER DB��OTA����ħ��,����У�����ݵı�ʶ*/
#define LOADER_MAGIC_NUMBER 0x4C4F4144

/**Maximum length of upgrade file name*/
/**CNcomment:�����ļ�������󳤶�*/
#define LOADER_FILE_NAME_LEN       128

/**Maximum length of user name.*/
/**CNcomment:�û�������󳤶� */
#define LOADER_USER_NAME_LEN        32

/**Maximum length of password.*/
/**CNcomment:�������󳤶� */
#define LOADER_PASSWORD_LEN         32

/**IP address definition*/
/**CNcomment:IP��ַ����*/
typedef HI_U32 HI_IPAddr;

/**IP port number definition*/
/**CNcomment:IP�˿ںŶ���*/
typedef HI_U16 HI_IPPort;

/**Magic check flag*/
/**CNcomment:��ʾħ��ֵ*/
#define DEF_CHECK_FLAG  		0x5a5a5a5a

/**Upgrade type definition*/
/**CNcomment:�������Ͷ���*/
typedef enum tagLOADER_TYPE_E {
    HI_UPDATE_OTA  = 0,    /**< Cable upgrade *//**CNcomment:< CABLE ���� */
    HI_UPDATE_IP,          /**< IP upgrade *//**CNcomment:< IP���� */
    HI_UPDATE_USB,         /**< USB upgrade *//** CNcomment:< USB ���� */
    HI_UPDATE_NULL,        /**< Do not upgrade *//**CNcomment:< ������ */
}HI_LOADER_TYPE_E;

/**Definition of the IP address type used in IP upgrade*/
/*CNcomment:*����ʱʹ������Э�鶨��*/
typedef enum tagProto_TYPE_E {
    HI_PROTO_TFTP = 0,     /**<Use TFTP protocol*//**CNcomment:< TFTPЭ������ */
    HI_PROTO_FTP,          /**<Use FTP protocol*//**CNcomment:< FTPЭ������ */
    HI_PROTO_HTTP,         /**<Use HTTP protocol*//**CNcomment:< HTTPЭ������*/

    HI_PROTO_BUTT
}HI_PROTO_TYPE_E;

/**Definition of ip update addr type*/
/**CNcomment:IP����ʱʹ��IP��ַ���Ͷ���*/
typedef enum tagIP_TYPE_E {
    HI_IP_STATIC = 0,    /**< Use static IP *//**CNcomment:< ʹ�þ�̬IP */
    HI_IP_DHCP,          /**< Use dynamic IP *//**CNcomment:< ʹ�ö�̬IP */
    HI_IP_BUTT,
}HI_IP_TYPE_E;

/**Definition of OSD UI language type*/
/**CNcomment:����OSDʹ�ú���������ʾ��Ϣ*/
typedef enum tagUILang
{
    HI_UI_LANG_EN,    /**< Use chinese UI *//**CNcomment:< ʹ��Ӣ����ʾ */    
    HI_UI_LANG_CN,    /**< Use english UI *//**CNcomment:< ʹ��������ʾ */

    HI_UI_LANG_BUTT
}HI_UI_LANG_E;

/**Definition of TUNER signal type*/
/**CNcomment:����TUNER�ź�����*/
typedef enum tagTunerSignalType_E
{
    HI_UNF_TUNER_SIG_TYPE_CAB = 1,      /**<Cable signal*/          /**<CNcomment:ITU-T J.83 ANNEX A/C(DVB_C)�ź�*/
    HI_UNF_TUNER_SIG_TYPE_SAT = 2,          /**<Satellite signal*/      /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_DVB_T = 4,        /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_DVB_T2 = 8,       /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_ISDB_T = 16,       /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_ATSC_T = 32,       /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_DTMB = 64,         /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_J83B = 128,         /**<Cable signal*/          /**<CNcomment:ITU-T J.83 ANNEX B(US Cable)�ź�*/

    HI_UNF_TUNER_SIG_TYPE_BUTT          /**<Invalid value*/         /**<CNcomment:�Ƿ�ֵ*/
}HI_TUNER_SIG_TYPE_E;

/**Parameter for DiSEqC 1.0/2.0 switch
   Some DiSEqC device need set polarization(13/18V) and 22K, you can set them here. */
/**CNcomment:DiSEqC 1.0/2.0 ���ز�����ЩDiSEqC�豸��Ҫ���ü�����ʽ��22K�ģ�������������豸����Ҫ���������� */
typedef struct hiTunerSwitch4Port_S
{
    HI_U32    u32Level;  /**<DiSEqC device level*/
    HI_U32    u32Port;   /**<DiSEqC switch port*/
    HI_U32    u32Polar;  /**<Polarization type */
    HI_U32    u32LNB22K; /**<22K status*/
} HI_TUNER_SWITCH4PORT_S;

/**Parameter for DiSEqC 1.1/2.1 switch */
/**CNcomment:DiSEqC 1.1/2.1 ���ز��� */
typedef struct hiTunerSwitch16PORT_S
{
    HI_U32       u32Level;          /**<DiSEqC device level*/
    HI_U32       u32Port;           /**<DiSEqC switch port*/
} HI_TUNER_SWITCH16PORT_S;

/*TS Priority, only used in DVB-T*/
/*CNcomment:������DVB-T*/
typedef enum hiUNF_TUNER_TS_PRIORITY_E
{
    HI_UNF_TUNER_TS_PRIORITY_NONE = 0 ,   /**< */
    HI_UNF_TUNER_TS_PRIORITY_HP,             /**< */
    HI_UNF_TUNER_TS_PRIORITY_LP,         /**< */
    HI_UNF_TUNER_TS_PRIORITY_BUTT,           /**< */
}HI_UNF_TUNER_TS_PRIORITY_E ;

/** base channel or lite channel, only used in DVB-T2*/
/** CNcomment:������DVB-T2*/
typedef enum hiUNF_TUNER_TER_MODE_E
{
    HI_UNF_TUNER_TER_MODE_BASE = 0,     /**< the channel is base mode*/         /**<CNcomment:ͨ���н�֧��base�ź�*/
    HI_UNF_TUNER_TER_MODE_LITE,         /**< the channel is lite mode*/         /**<CNcomment:ͨ������Ҫ֧��lite�ź�*/
    HI_UNF_TUNER_TER_MODE_BUTT      /**<Invalid value*/            /**<CNcomment:�Ƿ��߽�ֵ*/
} HI_UNF_TUNER_TER_MODE_E;

/**Define Cable TUNER parameter */
/**CNcomment:Cable TUNER�����ò���*/
typedef struct tagLoaderCabPara
{
    HI_U32      u32OtaPid;          /**< Upgrade data stream TS PID. The parameter is vital and set it with caution..*/
    HI_U32      u32OtaFreq;         /**< Upgrade data stream frequency pointer in kHz, for example, 403000. */
    HI_U32      u32OtaSymbRate;     /**< Upgrade data stream symbol rate in kbps, for example, 6875. */
    HI_U32      u32OtaModulation;   /**< Upgrade data stream constellation count.0:16QM 1:32QAM 2:64QAM 3:128QAM 4:256QAM  */

}HI_LOADER_CAB_PARA_S;

/*Define Terrestrial tuner parameter */
typedef struct tagLoaderTerPara
{
    HI_U32 u32OtaPid;          /**< TS PID. The parameter is vital and set it with caution..*//**<CNcomment: PID */
    HI_U32 u32OtaFreq;         /**< frequency pointer in kHz, for example, 177500. *//**<CNcomment: Ƶ�㣬��λ kHz */
    HI_U32 u32OtaBandWidth;     /**< BandWidth in kHz, for example, 7000. *//**<CNcomment: ������λ kHz */
    HI_U32 u32OtaModulation;   /**< constellation count.0:16QAM 1:32QAM 2:64QAM 3:128QAM 4:256QAM  *//**<CNcomment: QAM��ʽ��0:16QAM 1:32QAM 2:64QAM 3:128QAM 4:256QAM  */
	HI_UNF_TUNER_TER_MODE_E     enChannelMode;          //dvb-t2
    HI_UNF_TUNER_TS_PRIORITY_E  enDVBTPrio;             //dvb-t
} HI_LOADER_TER_PARA_S;

/**Define Sat TUNER parameter */
/**CNcomment:����TUNER�����ò���*/
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
}HI_LOADER_SAT_PARA_S;

/**Define TUNER type parameter */
/**CNcomment:����TUNER����ƥ��Ĳ���*/
typedef struct tagTunerParaInfo
{
    HI_TUNER_SIG_TYPE_E eSigType;         /**<Signal type*/
    union
    {
        HI_LOADER_CAB_PARA_S stCab;       /**<Cable transmission signal*/
        HI_LOADER_SAT_PARA_S stSat;        /**<Satellite transmission signal*/
		HI_LOADER_TER_PARA_S stTer;        /**<Terrestrial signal parameter*//**<CNcomment: �����źŲ��� */
    }unConnPara;

}HI_LOADER_OTA_PARA_S;

/**Define IP update parameter */
/**CNcomment:����IP������صĲ���*/
typedef struct tagIpParam_S
{
    HI_PROTO_TYPE_E  eProtoType;    /**< Protocol of data download 0:TFTP, 1:FTP, 2 HTTP>*//**CNcomment:< ��������Э�� 0:TFTP, 1:FTP, 2 HTTP >*/
    HI_IP_TYPE_E     eIpType;            /**< Used by the IP loader. IP obtaining mode.*//**CNcomment:< ip  loaderʹ��, ip��ȡ����*/

    /*Configure the following parameters only when static IP addresses are used.*/
    HI_IPAddr    ipOurIp;            /**< Used by the IP loader. Local IP address. *//**CNcomment:< ip  loaderʹ��, ����ip*/
    HI_IPAddr    ipGateway;          /**< Used by the IP loader. Gateway*//**CNcomment:< ip  loaderʹ��, ����*/
    HI_IPAddr    ipSubnetMask;       /**< Used by the IP loader. Subnet mask*//**CNcomment:< ip  loaderʹ��, ��������*/
    HI_IPAddr    ipServer;           /**< Used by the IP loader. Server IP address. *//**CNcomment:< ip  loaderʹ��, ������ip*/
    HI_IPPort    ipServerPort;       /**< Used by the IP loader. Server port.*/ /**CNcomment:< ip  loaderʹ��, ������port*/
    HI_S8        as8FileName[LOADER_FILE_NAME_LEN]; /**<IP Used by the IP loader. Upgrade file name.*/ /**CNcomment:<IP ip  loaderʹ��, �����ļ���*/
    HI_U32       u32FileSize;        /*Used by the IP loader. Size of upgrade file.*//*CNcomment:*<IP ip  loaderʹ��, �����ļ���С */
    HI_S8        as8UserName[LOADER_USER_NAME_LEN]; /**<Username, used by FTP.>*/
    HI_S8        as8Password[LOADER_USER_NAME_LEN]; /**<Password, used by FTP .>*/

}HI_LOADER_IP_PARA_S;

/**Define USB update parameter */
/**CNcomment:����USB������صĲ���*/
typedef struct tagUSBParam_S
{
    HI_S8 as8FileName[LOADER_FILE_NAME_LEN];
} HI_LOADER_USB_PARAM_S;

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
}HI_LOADER_PARAMETER_S;

typedef struct tagParaHead
{
    HI_U32   u32MagicNumber;     /**<  magic number name */
    HI_U32   u32Crc;             /**< CRC verification value */
    HI_U32   u32Length;          /*length of upgrade parameter.*/
}UPGRD_PARA_HEAD_S;


/*Define upgrade tag parameter.*/
typedef struct tagLoaderUpgrdTagParam
{
    HI_BOOL         bTagNeedUpgrd;        /*  whether normal upgrade.*/
    HI_BOOL         bTagManuForceUpgrd;   /*  whether force upgrade.*/
	HI_BOOL 		bTagUsbBurn;   		  /*  whether burn empty chipset from usb disk.*/
}UPGRD_TAG_PARA_S;

typedef struct tagLoaderPrivateParam
{
    HI_U32  u32FailedCnt;                /**< Number of upgrade failures. It can be ignored for user.*/
    HI_BOOL bTagDestroy;        /**< It can be ignored.*/
    HI_U8   au8Reserved[20];
} UPGRD_PRIVATE_PARAM_S;

typedef struct tagLoaderinfo
{
    UPGRD_PARA_HEAD_S     stTagParaHead;
    UPGRD_TAG_PARA_S      stTagPara;
    UPGRD_PARA_HEAD_S     stLoaderParaHead;
    HI_LOADER_PARAMETER_S  stLoaderParam;
	UPGRD_PRIVATE_PARAM_S stLoaderPrivate;
	
}UPGRD_LOADER_INFO_S;

#ifdef __cplusplus
 #if __cplusplus
}

 #endif
#endif

#endif

