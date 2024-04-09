/******************************************************************************

  Copyright (C), 2001-2011, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name     : hi_unf_frontend.h
Version       : Initial draft
Author        : HiSilicon multimedia software group
Created Date   : 2008-06-05
Last Modified by:
Description   : Application programming interfaces (APIs) of the external chip software (ECS)
Function List :
Change History:
 ******************************************************************************/
#ifndef __HI_UNF_FRONTEND_H__
#define __HI_UNF_FRONTEND_H__

#include "hi_common.h"
//#include "hi_error_mpi.h"

//#include "hi_unf_keyled.h"
//#include "hi_unf_ir.h"
//#include "hi_unf_pmoc.h"
//#include "hi_unf_i2c.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define HI_I2C_MAX_NUM_USER (15)    /**<Maximum I2C channel ID*/ /**<CNcomment:���I2Cͨ����*/

#define HI_UNF_DISEQC_MSG_MAX_LENGTH (6)    /**<DiSEqC message length*/  /**<CNcomment:DiSEqC��Ϣ����*/
#define HI_UNF_DISEQC_MAX_REPEAT_TIMES (4)  /**<DiSEqC message max repeat times*/
#define MAX_TS_LINE 11                      /** The NO of ts lines that can be configured*/ /** CNcomment:�����õ�ts�ź�������*/

//#ifdef HI_BOOT_DISEQC_SUPPORT
#define DISEQC_MAX_MOTOR_PISITION (255) /**<DiSEqC motor max stored position*/ 
//#endif /* HI_BOOT_DISEQC_SUPPORT */
/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4_1 */
/** @{ */  /** <!-- [QAM] */

/**Modulation mode*/
/**CNcomment: ���Ʒ�ʽ*/
typedef enum hiUNF_QAM_TYPE_E
{
    HI_UNF_MOD_TYPE_DEFAULT,          /**<Default QAM mode. The default QAM mode is HI_UNF_MOD_TYPE_QAM_64 at present.*/   /**<CNcomment:Ĭ�ϵ�QAM����, ��ǰϵͳĬ��ΪHI_UNF_MOD_TYPE_QAM_64 */
    HI_UNF_MOD_TYPE_QAM_16 = 0x100,   /**<Enumeration corresponding to the 16QAM mode*/                                    /**<CNcomment:16QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_32,           /**<Enumeration corresponding to the 32QAM mode*/                                    /**<CNcomment:32QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_64,           /**<Enumeration corresponding to the 64QAM mode*/                                    /**<CNcomment:64QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_128,          /**<Enumeration corresponding to the 128QAM mode*/                                   /**<CNcomment:128QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_256,          /**<Enumeration corresponding to the 256QAM mode*/                                   /**<CNcomment:256QAM��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QAM_512,          /**<Enumeration corresponding to the 512QAM mode*/                                   /**<CNcomment:512QAM��Ӧ��ö��ֵ*/

    HI_UNF_MOD_TYPE_BPSK = 0x200,     /**<Enumeration corresponding to the binary phase shift keying (BPSK) mode. */         /**<CNcomment:BPSK��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_QPSK = 0x300,     /**<Enumeration corresponding to the quaternary phase shift keying (QPSK) mode. */     /**<CNcomment:QPSK��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_DQPSK,
    HI_UNF_MOD_TYPE_8PSK,             /**<Enumeration corresponding to the 8 phase shift keying (8PSK) mode*/              /**<CNcomment:8PSK��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_16APSK,           /**<Enumeration corresponding to the 16-Ary Amplitude and Phase Shift Keying (16APSK) mode*/      /**<CNcomment:16APSK��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_32APSK,           /**<Enumeration corresponding to the 32-Ary Amplitude and Phase Shift Keying (32APSK) mode*/      /**<CNcomment:32APSK��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_8VSB,           /**<Enumeration corresponding to (8VSB) mode*/      /**<CNcomment:8VSB��Ӧ��ö��ֵ*/
    HI_UNF_MOD_TYPE_16VSB,           /**<Enumeration corresponding to (16VSB) mode*/      /**<CNcomment:16VSB��Ӧ��ö��ֵ*/

    /**<Enumeration corresponding to the auto mode. For DVB-S/S2, if detect modulation type fail, it will return auto*/
    /**<CNcomment:�����źŵ��Ʒ�ʽ�Զ���⣬������ʧ�ܷ���AUTO*/
    HI_UNF_MOD_TYPE_AUTO,

    HI_UNF_MOD_TYPE_BUTT              /**<Invalid Modulation mode*/       /**<CNcomment:�Ƿ��ĵ�������ö��ֵ*/
}HI_UNF_MODULATION_TYPE_E;

/**Frequency locking status of the tuner*/
/**CNcomment:TUNER��Ƶ״̬*/
typedef enum  hiUNF_TUNER_LOCK_STATUS_E
{
    HI_UNF_TUNER_SIGNAL_DROPPED = 0,      /**<The signal is not locked.*/  /**<CNcomment:�ź�δ����*/
    HI_UNF_TUNER_SIGNAL_LOCKED,            /**<The signal is locked.*/  /**<CNcomment:�ź�������*/
    HI_UNF_TUNER_SIGNAL_BUTT             /**<Invalid value*/   /**<CNcomment:�Ƿ��߽�ֵ*/
}HI_UNF_TUNER_LOCK_STATUS_E;

/**Output mode of the tuner*/
/**CNcomment:TUNER���ģʽ */
typedef enum hiUNF_TUNER_OUTPUT_MODE_E
{
    HI_UNF_TUNER_OUTPUT_MODE_DEFAULT ,            /**<Default mode*/        /**<CNcomment:Ĭ��ģʽ*/
    HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A,     /**<Parallel mode A*/     /**<CNcomment:����ģʽA*/
    HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_B,     /**<Parallel mode B*/     /**<CNcomment:����ģʽB*/
    HI_UNF_TUNER_OUTPUT_MODE_SERIAL,              /**<Serial mode 74.25M*/     /**<CNcomment:����ģ74.25M*/ 
    HI_UNF_TUNER_OUTPUT_MODE_SERIAL_50,           /**<Serial mode 50M*/  /**<CNcomment:����ģ50M*/
    HI_UNF_TUNER_OUTPUT_MODE_SERIAL_2BIT,
    HI_UNF_TUNER_OUTPUT_MODE_BUTT                 /**<Invalid value*/       /**<CNcomment:�Ƿ�ֵ*/
}HI_UNF_TUNER_OUPUT_MODE_E;

/**Output order*/
/**CNcomment:TUNER������� */
typedef enum hiUNF_TUNER_OUTPUT_TS_E
{
    HI_UNF_TUNER_OUTPUT_TSDAT0,        /**<data0*/                       /**<CNcomment:������0bit*/
    HI_UNF_TUNER_OUTPUT_TSDAT1,        /**<data1*/                       /**<CNcomment:������1bit*/
    HI_UNF_TUNER_OUTPUT_TSDAT2,        /**<data2*/                       /**<CNcomment:������2bit*/
    HI_UNF_TUNER_OUTPUT_TSDAT3,        /**<data3*/                       /**<CNcomment:������3bit*/
    HI_UNF_TUNER_OUTPUT_TSDAT4,        /**<data4*/                       /**<CNcomment:������4bit*/
    HI_UNF_TUNER_OUTPUT_TSDAT5,        /**<data5*/                       /**<CNcomment:������5bit*/
    HI_UNF_TUNER_OUTPUT_TSDAT6,        /**<data6*/                       /**<CNcomment:������6bit*/
    HI_UNF_TUNER_OUTPUT_TSDAT7,        /**<data7*/                       /**<CNcomment:������7bit*/
    HI_UNF_TUNER_OUTPUT_TSSYNC,        /**<sync*/                        /**<CNcomment:sync�ź���*/
    HI_UNF_TUNER_OUTPUT_TSVLD,         /**<valid*/                       /**<CNcomment:valid�ź���*/
    HI_UNF_TUNER_OUTPUT_TSERR,         /**<err*/                         /**<CNcomment:err�ź���*/
    HI_UNF_TUNER_OUTPUT_BUTT           /**<Invalid value*/               /**<CNcomment:�Ƿ�ֵ*/
} HI_UNF_TUNER_OUTPUT_TS_E;

typedef struct hiUNF_TUNER_TSOUT_SET_S
{
    HI_UNF_TUNER_OUTPUT_TS_E enTSOutput[MAX_TS_LINE];
}HI_UNF_TUNER_TSOUT_SET_S;

/**Signal type of the tuner*/
/**CNcomment:TUNER�ź�����*/
typedef enum    hiTUNER_SIG_TYPE_E
{
    HI_UNF_TUNER_SIG_TYPE_CAB = 1,      /**<Cable signal*/          /**<CNcomment:ITU-T J.83 ANNEX A/C(DVB_C)�ź��ź�*/
    HI_UNF_TUNER_SIG_TYPE_SAT = 2,          /**<Satellite signal*/      /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_DVB_T = 4,        /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_DVB_T2 = 8,       /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_ISDB_T = 16,       /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_ATSC_T = 32,       /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_DTMB = 64,         /**<Terrestrial signal*/    /**<CNcomment:�����ź�*/
    HI_UNF_TUNER_SIG_TYPE_J83B = 128,         /**<Cable signal*/          /**<CNcomment:ITU-T J.83 ANNEX B(US Cable)�ź�*/

    HI_UNF_TUNER_SIG_TYPE_BUTT          /**<Invalid value*/         /**<CNcomment:�Ƿ�ֵ*/
} HI_UNF_TUNER_SIG_TYPE_E;

/**type of TUNER device*/
/**CNcomment:TUNER�豸����*/
typedef enum    hiUNF_TUNER_DEV_TYPE_E
{
    HI_UNF_TUNER_DEV_TYPE_XG_3BL,               /**<XG_3BL*/                    /**<CNcomment:֧�������ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_CD1616,               /**<CD1616*/                    /**<CNcomment:֧��CD1616��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_ALPS_TDAE,            /**<ALPS_TDAE*/                 /**<CNcomment:֧��ALPS_TDAE��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_TDCC,                 /**<TDCC*/                      /**<CNcomment:֧��TDCC��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_TDA18250,             /**<TDA18250*/                  /**<CNcomment:֧��TDA18250��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_CD1616_DOUBLE,        /**<CD1616 with double agc*/    /**<CNcomment:֧��CD1616��˫agc��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_MT2081,               /**<MT2081*/                    /**<CNcomment:֧��MT2081��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_TMX7070X,             /**<THOMSON7070X*/              /**<CNcomment:֧��THOMSON7070X��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_R820C,                /**<R820C*/                     /**<CNcomment:֧��R820C��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_MXL203,               /**<MXL203 */                   /**<CNcomment:֧��MXL203��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_AV2011,               /**<AV2011*/                    /**<CNcomment:֧��AV2011��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_SHARP7903,            /**<SHARP7903*/                 /**<CNcomment:֧��SHARP7903��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_MXL101,               /**<MXL101*/                    /**<CNcomment:֧��MXL101��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_MXL603,               /**<MXL603*/                    /**<CNcomment:֧��MXL603��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_IT9170,               /**<IT9170*/                    /**<CNcomment:֧��IT9170��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_IT9133,               /**<IT9133*/                    /**<CNcomment:֧��IT9133��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_TDA6651,              /**<TDA6651*/                   /**<CNcomment:֧��TDA6651��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_TDA18250B,            /**<TDA18250B*/                 /**<CNcomment:֧��TDA18250B��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_M88TS2022,            /**<M88TS2022*/                 /**<CNcomment:֧��M88TS2022��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_RDA5815,              /**<RDA5815*/                   /**<CNcomment:֧��RDA5815��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_MXL254,               /**<MXL254*/                    /**<CNcomment:֧��MXL254��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_CXD2861,              /**<CXD2861*/                   /**<CNcomment:֧��CXD2861��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_SI2147,               /**<Si2147*/                    /**<CNcomment:֧��Si2147��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_RAFAEL836,				/**<Rafael836*/					/**<CNcomment:֧��Rafael836��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_MXL608,				/**<MXL608*/                    /**<CNcomment:֧��MXL608��ƵоƬ*/
    HI_UNF_TUNER_DEV_TYPE_MXL214,               /**<MXL214*/                    /**<CNcomment:֧��MXL214��ƵоƬ*/    
    HI_UNF_TUNER_DEV_TYPE_TDA18280,             /**<TDA18280*/                    /**<CNcomment:֧��TDA18280��ƵоƬ*/ 
    HI_UNF_TUNER_DEV_TYPE_TDA182I5A,             /**<TDA182I5A*/       			/**<CNcomment:֧��TDA182I5AоƬ*/
    HI_UNF_TUNER_DEV_TYPE_SI2144,             /**<Si2144*/       			/**<CNcomment:֧��Si2144оƬ*/
    HI_UNF_TUNER_DEV_TYPE_AV2018,             /**<AV2018*/       			/**<CNcomment:֧��AV2018оƬ*/
    HI_UNF_TUNER_DEV_TYPE_MXL251,		      /**<MXL251*/				    /**<CNcomment:֧��MXL251оƬ*/
    HI_UNF_TUNER_DEV_TYPE_M88TC3800,			/**<M88TC3800*/				    /**<CNcomment:֧��M88TC3800оƬ*/
    HI_UNF_TUNER_DEV_TYPE_BUTT                  /**<Invalid value*/             /**<CNcomment:�Ƿ��߽�ֵ*/
} HI_UNF_TUNER_DEV_TYPE_E ;

/**Type of the demod device*/
/**CNcomment:demod�豸����*/
typedef enum    hiUNF_DEMOD_DEV_TYPE_E
{
    HI_UNF_DEMOD_DEV_TYPE_NONE,                 /**<Not supported*/         /**<CNcomment:��֧��*/
    HI_UNF_DEMOD_DEV_TYPE_3130I = 0x100,        /**<Internal QAM*/          /**<CNcomment:�ڲ�QAM*/
    HI_UNF_DEMOD_DEV_TYPE_3130E,                /**<External Hi3130*/       /**<CNcomment:�ⲿQAM hi3130оƬ*/
    HI_UNF_DEMOD_DEV_TYPE_J83B,                 /**<suppoort j83b*/         /**<CNcomment:֧��j83b*/
    HI_UNF_DEMOD_DEV_TYPE_AVL6211,              /**<Avalink 6211*/          /**<CNcomment:֧��Avalink 6211*/
    HI_UNF_DEMOD_DEV_TYPE_MXL101,               /**<Maxlinear mxl101*/      /**<CNcomment:֧��Maxlinear mxl101*/
    HI_UNF_DEMOD_DEV_TYPE_MN88472,              /**<PANASONIC mn88472*/     /**<CNcomment:֧��PANASONIC mn88472*/
    HI_UNF_DEMOD_DEV_TYPE_IT9170,               /**<ITE it9170*/            /**<CNcomment:֧��ITE it9170*/
    HI_UNF_DEMOD_DEV_TYPE_IT9133,               /**<ITE it9133*/            /**<CNcomment:֧��ITE it9133*/
    HI_UNF_DEMOD_DEV_TYPE_3136,                 /**<External Hi3136*/       /**<CNcomment:�ⲿhi3136оƬ*/
    HI_UNF_DEMOD_DEV_TYPE_3136I,                /**<Internal Hi3136*/       /**<CNcomment:�ڲ�hi3136оƬ*/
    HI_UNF_DEMOD_DEV_TYPE_MXL254,               /**<External mxl254*/       /**<CNcomment:�ⲿMXL254оƬ*/
    HI_UNF_DEMOD_DEV_TYPE_CXD2837,              /**Sony cxd2837*/           /**<CNcomment:֧��sony cxd2837*/
    HI_UNF_DEMOD_DEV_TYPE_3137,                 /**External Hi3137*/        /**<CNcomment:֧���ⲿhi3137оƬ*/
    HI_UNF_DEMOD_DEV_TYPE_MXL214,               /**<External mxl214*/       /**<CNcomment:�ⲿMXL214оƬ*/
    HI_UNF_DEMOD_DEV_TYPE_TDA18280,             /**<External tda18280*/       /**<CNcomment:�ⲿtda18280оƬ*/
	HI_UNF_DEMOD_DEV_TYPE_BUTT                  /**<Invalid value*/         /**<CNcomment:�Ƿ��߽�ֵ*/
} HI_UNF_DEMOD_DEV_TYPE_E;

/**Defines the cable transmission signal.*/
/**CNcomment:����CABLE�����ź�*/
typedef struct  hiUNF_CAB_CONNECT_PARA_S
{
    HI_U32                      u32Freq;            /**<Frequency, in kHz*/      /**<CNcomment:Ƶ�ʣ���λ��kHz*/
    HI_U32                      u32SymbolRate ;     /**<Symbol rate, in bit/s*/  /**<CNcomment:�����ʣ���λbps */
    HI_UNF_MODULATION_TYPE_E    enModType ;         /**<QAM mode*/               /**<CNcomment:QAM���Ʒ�ʽ*/
    HI_BOOL                     bReverse ;          /**<Spectrum reverse mode*/  /**<CNcomment:Ƶ�׵��ô���ʽ*/
}HI_UNF_CAB_CONNECT_PARA_S ;

/*Guard interval of OFDM*/
/*CNcomment:���ز������µı������*/
typedef enum hiUNF_TUNER_FE_GUARD_INTV_E
{
    HI_UNF_TUNER_FE_GUARD_INTV_DEFALUT = 0 ,    /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_1_128       ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_1_32       ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_1_16       ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_1_8        ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_1_4        ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_19_128       ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_19_256       ,       /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_BUTT     ,       /**< */
}HI_UNF_TUNER_FE_GUARD_INTV_E;

/*Not used currently*/
/*CNcomment:��δʹ��*/
typedef enum hiUNF_TUNER_FE_DEPUNC_RATE_E
{
    HI_UNF_TUNER_FE_DEPUNC_RATE_DEFAULT = 0 ,    /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_12      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_23      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_34      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_45      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_56      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_67      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_78      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_89      ,        /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_BUTT    ,        /**< */
}HI_UNF_TUNER_FE_DEPUNC_RATE_E ;

/*OFDM Mode, used in multi-carrier modulation*/
/*CNcomment:OFDMģʽ�����ڶ��ز�����ģʽ��*/
typedef enum hiUNF_TUNER_FE_FFT_E
{
    HI_UNF_TUNER_FE_FFT_DEFAULT = 0,   /**< */
    HI_UNF_TUNER_FE_FFT_1K ,           /**< */
    HI_UNF_TUNER_FE_FFT_2K ,           /**< */
    HI_UNF_TUNER_FE_FFT_4K ,           /**< */
    HI_UNF_TUNER_FE_FFT_8K ,           /**< */
    HI_UNF_TUNER_FE_FFT_16K ,           /**< */
    HI_UNF_TUNER_FE_FFT_32K ,           /**< */
    HI_UNF_TUNER_FE_FFT_BUTT ,         /**< */
}HI_UNF_TUNER_FE_FFT_E;

/*Hierarchical modulation mode, only used in DVB-T*/
/*CNcomment:������DVB-T*/
typedef enum hiUNF_TUNER_FE_HIERARCHY_E
{
    HI_UNF_TUNER_FE_HIERARCHY_DEFAULT = 0 ,   /**< */
    HI_UNF_TUNER_FE_HIERARCHY_NO,             /**< */
    HI_UNF_TUNER_FE_HIERARCHY_ALHPA1,         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_ALHPA2,         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_ALHPA4,         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_BUTT,           /**< */
}HI_UNF_TUNER_FE_HIERARCHY_E ;

/*TS Priority, only used in DVB-T*/
/*CNcomment:������DVB-T*/
typedef enum hiUNF_TUNER_TS_PRIORITY_E
{
    HI_UNF_TUNER_TS_PRIORITY_NONE = 0 ,   /**< */
    HI_UNF_TUNER_TS_PRIORITY_HP,             /**< */
    HI_UNF_TUNER_TS_PRIORITY_LP,         /**< */
    HI_UNF_TUNER_TS_PRIORITY_BUTT,           /**< */
}HI_UNF_TUNER_TS_PRIORITY_E ;

/** CNcomment:������DVB-T2*/
typedef enum hiUNF_TUNER_TER_MODE_E
{
    HI_UNF_TUNER_TER_MODE_BASE = 0,     /**< the channel is base mode*/         /**<CNcomment:ͨ���н�֧��base�ź�*/
    HI_UNF_TUNER_TER_MODE_LITE,         /**< the channel is lite mode*/         /**<CNcomment:ͨ������Ҫ֧��lite�ź�*/
    HI_UNF_TUNER_TER_MODE_BUTT      /**<Invalid value*/            /**<CNcomment:�Ƿ��߽�ֵ*/
} HI_UNF_TUNER_TER_MODE_E;

typedef struct  hiUNF_TER_CONNECT_PARA_S
{
    HI_U32          u32Freq     ;                    /**<freq in KHz */
    HI_U32          u32BandWidth    ;                /**<bandwidth in KHz */
    HI_UNF_MODULATION_TYPE_E enModType  ;            /**< */
    HI_BOOL                     bReverse ;          /**<Spectrum reverse mode*/  /**<CNcomment:Ƶ�׷�ת����ʽ*/
    HI_UNF_TUNER_TER_MODE_E     enChannelMode;      //dvb-t2
    HI_UNF_TUNER_TS_PRIORITY_E  enDVBTPrio;         //dvb-t
}HI_UNF_TER_CONNECT_PARA_S ;

#if 0
/*CNcomment:��δʹ��*/
typedef struct  hiUNF_TUNER_TER_ATTR_S
{
    HI_UNF_TUNER_FE_DEPUNC_RATE_E   enHpCode ;      /**< */
    HI_UNF_TUNER_FE_DEPUNC_RATE_E   enLpCode ;      /**< */
    HI_UNF_TUNER_FE_GUARD_INTV_E    enGuardIntv ;   /**< */
    HI_UNF_TUNER_FE_FFT_E       enFftType ;         /**< */
    HI_UNF_TUNER_FE_HIERARCHY_E enHierType ;        /**< */

}HI_UNF_TUNER_TER_ATTR_S;
#endif

/**TS clock polarization*/
/*CNcomment:TSʱ�Ӽ���*/
typedef enum hiUNF_TUNER_TSCLK_POLAR_E
{
    HI_UNF_TUNER_TSCLK_POLAR_FALLING,       /**<Falling edge*/      /**<CNcomment:�½���*/
    HI_UNF_TUNER_TSCLK_POLAR_RISING,        /**<Rising edge*/       /**<CNcomment:������*/
    HI_UNF_TUNER_TSCLK_POLAR_BUTT           /**<Invalid value*/     /**<CNcomment:�Ƿ��߽�ֵ*/
} HI_UNF_TUNER_TSCLK_POLAR_E;

/**TS format*/
typedef enum hiUNF_TUNER_TS_FORMAT_E
{
    HI_UNF_TUNER_TS_FORMAT_TS,              /**<188*/
    HI_UNF_TUNER_TS_FORMAT_TSP,             /**<204*/
    HI_UNF_TUNER_TS_FORMAT_BUTT             /**<Invalid value*/     /**<CNcomment:�Ƿ��߽�ֵ*/
} HI_UNF_TUNER_TS_FORMAT_E;

/**TS serial PIN*/
typedef enum hiUNF_TUNER_TS_SERIAL_PIN_E
{
    HI_UNF_TUNER_TS_SERIAL_PIN_0,           /**<Serial pin 0, default*/
    HI_UNF_TUNER_TS_SERIAL_PIN_7,           /**<Serial pin 7*/
    HI_UNF_TUNER_TS_SERIAL_PIN_BUTT         /**<Invalid value*/     /**<CNcomment:�Ƿ��߽�ֵ*/
} HI_UNF_TUNER_TS_SERIAL_PIN_E;

/** Tuner RF AGC mode */
typedef enum hiUNF_TUNER_RFAGC_MODE_E
{
    /**< Inverted polarization, default.This setting is used for a tuner whose gain decreases with increased AGC voltage */
    HI_UNF_TUNER_RFAGC_INVERT, 

    /**< Normal polarization. This setting is used for a tuner whose gain increases with increased AGC voltage */
    HI_UNF_TUNER_RFAGC_NORMAL,
    HI_UNF_TUNER_RFAGC_BUTT
} HI_UNF_TUNER_RFAGC_MODE_E;

/** Tuner IQ spectrum mode */
typedef enum hiUNF_TUNER_IQSPECTRUM_MODE_E
{
    HI_UNF_TUNER_IQSPECTRUM_NORMAL,         /**<The received signal spectrum is not inverted */
    HI_UNF_TUNER_IQSPECTRUM_INVERT,         /**<The received signal spectrum is inverted */
    HI_UNF_TUNER_IQSPECTRUM_BUTT
} HI_UNF_TUNER_IQSPECTRUM_MODE_E;

/** DiSEqC Wave Mode */
typedef enum hiUNF_TUNER_DISEQCWAVE_MODE_E
{
    HI_UNF_TUNER_DISEQCWAVE_NORMAL,         /**<Waveform produced by demod */
    HI_UNF_TUNER_DISEQCWAVE_ENVELOPE,       /**<Waveform produced by LNB control device */
    HI_UNF_TUNER_DISEQCWAVE_BUTT
} HI_UNF_TUNER_DISEQCWAVE_MODE_E;

/** LNB power supply and control device */
typedef enum hiUNF_LNBCTRL_DEV_TYPE_E
{
    HI_UNF_LNBCTRL_DEV_TYPE_NONE,           /**<No LNB control device */
    HI_UNF_LNBCTRL_DEV_TYPE_MPS8125,        /**<MPS8125 */
    HI_UNF_LNBCTRL_DEV_TYPE_ISL9492,        /**<ISL9492 */
    HI_UNF_LNBCTRL_DEV_TYPE_BUTT
} HI_UNF_LNBCTRL_DEV_TYPE_E;

typedef struct  hiUNF_TUNER_SAT_ATTR_S
{
    HI_U32                         u32DemodClk;     /**<Demod reference clock frequency, KHz */
    HI_U16                         u16TunerMaxLPF;  /**<Tuner max LFP, MHz */
    HI_U16                         u16TunerI2CClk;  /**<Tuner I2C clock, kHz */
    HI_UNF_TUNER_RFAGC_MODE_E      enRFAGC;         /**<Tuner RF AGC mode */
    HI_UNF_TUNER_IQSPECTRUM_MODE_E enIQSpectrum;    /**<Tuner IQ spectrum mode */
    HI_UNF_TUNER_TSCLK_POLAR_E     enTSClkPolar;    /**<TS clock polarization */
    HI_UNF_TUNER_TS_FORMAT_E       enTSFormat;      /**<TS format */
    HI_UNF_TUNER_TS_SERIAL_PIN_E   enTSSerialPIN;   /**<TS serial PIN */
    HI_UNF_TUNER_DISEQCWAVE_MODE_E enDiSEqCWave;    /**<DiSEqC Wave Mode */
    HI_UNF_LNBCTRL_DEV_TYPE_E      enLNBCtrlDev;    /**<LNB power supply and control device */
    HI_U16                         u16LNBDevAddress;/**<LNB control device address */
} HI_UNF_TUNER_SAT_ATTR_S;

//typedef struct  hiUNF_TUNER_TER_ATTR_S
//{
//    HI_U32                         u32ResetGpioNo;  /**<Demod reset GPIO NO.*/
//} HI_UNF_TUNER_TER_ATTR_S;
/** Polarization type */
typedef enum hiUNF_TUNER_FE_POLARIZATION_E
{
    HI_UNF_TUNER_FE_POLARIZATION_H,         /**< Horizontal Polarization */
    HI_UNF_TUNER_FE_POLARIZATION_V,         /**< Vertical Polarization */
    HI_UNF_TUNER_FE_POLARIZATION_L,         /**< Left-hand circular Polarization */
    HI_UNF_TUNER_FE_POLARIZATION_R,         /**< Right-hand circular Polarization */
    HI_UNF_TUNER_FE_POLARIZATION_BUTT,      /**< Invalid */
} HI_UNF_TUNER_FE_POLARIZATION_E;

/** FEC Type */
typedef enum hiUNF_TUNER_FE_FECTYPE_E
{
    HI_UNF_TUNER_FE_DVBS,
    HI_UNF_TUNER_FE_DVBS2,
    HI_UNF_TUNER_FE_DIRECTV,
    HI_UNF_TUNER_FE_BUTT
} HI_UNF_TUNER_FE_FECTYPE_E;

/** FEC Rate */
typedef enum hiUNF_TUNER_FE_FECRATE_E
{
    HI_UNF_TUNER_FE_FEC_AUTO = 0,
    HI_UNF_TUNER_FE_FEC_1_2,
    HI_UNF_TUNER_FE_FEC_2_3,
    HI_UNF_TUNER_FE_FEC_3_4,
    HI_UNF_TUNER_FE_FEC_4_5,
    HI_UNF_TUNER_FE_FEC_5_6,
    HI_UNF_TUNER_FE_FEC_6_7,
    HI_UNF_TUNER_FE_FEC_7_8,
    HI_UNF_TUNER_FE_FEC_8_9,
    HI_UNF_TUNER_FE_FEC_9_10,
    HI_UNF_TUNER_FE_FEC_1_4,
    HI_UNF_TUNER_FE_FEC_1_3,
    HI_UNF_TUNER_FE_FEC_2_5,
    HI_UNF_TUNER_FE_FEC_3_5,
    HI_UNF_TUNER_FE_FECRATE_BUTT
} HI_UNF_TUNER_FE_FECRATE_E;

/** LNB type */
typedef enum hiUNF_TUNER_FE_FE_LNBTYPE_E
{
    HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY,   /**<Single LO frequency */
    HI_UNF_TUNER_FE_LNB_DUAL_FREQUENCY,     /**<Dual LO frequency */
    HI_UNF_TUNER_FE_LNB_TYPE_BUTT
} HI_UNF_TUNER_FE_LNB_TYPE_E;

/** LNB band type */
typedef enum hiUNF_TUNER_FE_LNB_BAND_E
{
    HI_UNF_TUNER_FE_LNB_BAND_C,             /**<C */
    HI_UNF_TUNER_FE_LNB_BAND_KU,            /**<Ku */
    HI_UNF_TUNER_FE_LNB_BAND_BUTT
} HI_UNF_TUNER_FE_LNB_BAND_E;

/** LNB power control */
typedef enum hiUNF_TUNER_FE_LNB_POWER_E
{
    HI_UNF_TUNER_FE_LNB_POWER_OFF,          /**<LNB power off */
    HI_UNF_TUNER_FE_LNB_POWER_ON,           /**<LNB power auto, 13V/18V, default */
    HI_UNF_TUNER_FE_LNB_POWER_ENHANCED,     /**<LNB power auto, 14V/19V, some LNB control device can support.*/
    HI_UNF_TUNER_FE_LNB_POWER_BUTT
} HI_UNF_TUNER_FE_LNB_POWER_E;

/** LNB 22K tone status, for Ku band LNB */
typedef enum hiUNF_TUNER_FE_LNB_22K_E
{
    HI_UNF_TUNER_FE_LNB_22K_OFF,            /**<default */
    HI_UNF_TUNER_FE_LNB_22K_ON,
    HI_UNF_TUNER_FE_LNB_22K_BUTT
} HI_UNF_TUNER_FE_LNB_22K_E;

/** 0/12V switch */
typedef enum hiUNF_TUNER_SWITCH_0_12V_E
{
    HI_UNF_TUNER_SWITCH_0_12V_NONE,         /**< None, default */
    HI_UNF_TUNER_SWITCH_0_12V_0,            /**< 0V */
    HI_UNF_TUNER_SWITCH_0_12V_12,           /**< 12V */
    HI_UNF_TUNER_SWITCH_0_12V_BUTT
} HI_UNF_TUNER_SWITCH_0_12V_E;

/** 22KHz switch */
typedef enum hiUNF_TUNER_SWITCH_22K_E
{
    HI_UNF_TUNER_SWITCH_22K_NONE,           /**< None, default */
    HI_UNF_TUNER_SWITCH_22K_0,              /**< 0 */
    HI_UNF_TUNER_SWITCH_22K_22,             /**< 22KHz */
    HI_UNF_TUNER_SWITCH_22K_BUTT
} HI_UNF_TUNER_SWITCH_22K_E;

/** Tone burst switch */
typedef enum hiUNF_TUNER_SWITCH_TONEBURST_E
{
    HI_UNF_TUNER_SWITCH_TONEBURST_NONE,     /**< Don't send tone burst, default */
    HI_UNF_TUNER_SWITCH_TONEBURST_0,        /**< Tone burst 0 */
    HI_UNF_TUNER_SWITCH_TONEBURST_1,        /**< Tone burst 1 */
    HI_UNF_TUNER_SWITCH_TONEBURST_BUTT
} HI_UNF_TUNER_SWITCH_TONEBURST_E;

/**Structure of the satellite transmission signal.*/
/**CNcomment:����Satellite�����ź�*/
typedef struct  hiUNF_SAT_CONNECT_PARA_S
{
    HI_U32                         u32Freq;         /**<Downlink frequency, in kHz*/ /**<CNcomment:����Ƶ�ʣ���λ��kHz*/
    HI_U32                         u32SymbolRate;   /**<Symbol rate, in bit/s*/      /**<CNcomment:�����ʣ���λbps */
    HI_UNF_TUNER_FE_POLARIZATION_E enPolar;         /**<Polarization type*/          /**<CNcomment:������ʽ*/
	HI_U32                         u32ScrambleValue; /**<initial scrambling code,range 0~262141,when value is not 0,signal is special,
    and the value must be telled by signal owner.default 0 must be configed when TP signal is not special*/
} HI_UNF_SAT_CONNECT_PARA_S;

/**Structure of the satellite transmission signal's detailed information.*/
/**CNcomment:�����ź���ϸ��Ϣ*/
typedef struct  hiUNF_TUNER_SAT_SIGNALINFO_S
{
    HI_U32                         u32Freq;         /**<Downlink frequency, in kHz*/ /**<CNcomment:����Ƶ�ʣ���λ��kHz*/
    HI_U32                         u32SymbolRate;   /**<Symbol rate, in bit/s*/      /**<CNcomment:�����ʣ���λbps */
    HI_UNF_MODULATION_TYPE_E       enModType;       /**<Modulation type*/            /**<CNcomment:���Ʒ�ʽ*/
    HI_UNF_TUNER_FE_POLARIZATION_E enPolar;         /**<Polarization type*/          /**<CNcomment:������ʽ*/
    HI_UNF_TUNER_FE_FECTYPE_E      enSATType;       /**<Saterllite standard, DVB-S/S2/DIRECTV*/   /**<CNcomment:���Ǳ�׼�� ֧��DVB-S/S2/DIRECTV*/
    HI_UNF_TUNER_FE_FECRATE_E      enFECRate;       /**<FEC rate*/                   /**<CNcomment:ǰ���������*/
} HI_UNF_TUNER_SAT_SIGNALINFO_S;

typedef enum hiUNF_TUNER_T2_PLP_TYPE_E
{   
    HI_UNF_TUNER_T2_PLP_TYPE_COM=0, 
    HI_UNF_TUNER_T2_PLP_TYPE_DAT1,  
    HI_UNF_TUNER_T2_PLP_TYPE_DAT2,
    HI_UNF_TUNER_T2_PLP_TYPE_BUTT   
} HI_UNF_TUNER_T2_PLP_TYPE_E;

/**Structure of the terrestrial transmission signal's detailed information.*/
/**CNcomment:�����ź���ϸ��Ϣ*/
typedef struct  hiUNF_TUNER_TER_SIGNALINFO_S
{
    HI_U32                         u32Freq;         /**<Frequency, in kHz*/ /**<CNcomment:Ƶ�ʣ���λ��kHz*/
    HI_U32                         u32BandWidth;   /**<Band width, in KHz*/      /**<CNcomment:������λKHz */
    HI_UNF_MODULATION_TYPE_E       enModType;       /**<Modulation type*/            /**<CNcomment:���Ʒ�ʽ*/
    HI_UNF_TUNER_FE_FECRATE_E      enFECRate;       /**<FEC rate*/                   /**<CNcomment:ǰ���������*/
    HI_UNF_TUNER_FE_GUARD_INTV_E enGuardIntv;
    HI_UNF_TUNER_FE_FFT_E enFFTMode;
    HI_UNF_TUNER_FE_HIERARCHY_E enHierMod; /**<Hierarchical Modulation and alpha, only used in DVB-T*/
    HI_UNF_TUNER_TS_PRIORITY_E enTsPriority; /**<The TS priority, only used in DVB-T*/
} HI_UNF_TUNER_TER_SIGNALINFO_S;
/**CNcomment:TUNER����*/
typedef struct hiUNF_TUNER_SIGNALINFO_S
{
    HI_UNF_TUNER_SIG_TYPE_E enSigType;              /**<Signal transmission type*/  /**<CNcomment:�ź�����*/

    union
    {
        HI_UNF_TUNER_SAT_SIGNALINFO_S stSat;        /**<Signal info of satellite*/  /**<CNcomment:�����ź���Ϣ*/
        HI_UNF_TUNER_TER_SIGNALINFO_S stTer;        /**<Signal info of terrestrial*/  /**<CNcomment:�����ź���Ϣ*/
    } unSignalInfo;
} HI_UNF_TUNER_SIGNALINFO_S;

/** LNB configurating parameters */
typedef struct hiUNF_TUNER_FE_LNB_CONFIG_S
{
    HI_UNF_TUNER_FE_LNB_TYPE_E  enLNBType;      /**<LNB type*/                              /**<CNcomment:LNB����*/
    HI_U32                      u32LowLO;       /**< Low Local Oscillator Frequency, MHz */ /**<CNcomment:LNB�ͱ���Ƶ�ʣ���λMHz*/
    HI_U32                      u32HighLO;      /**< High Local Oscillator Frequency, MHz*/ /**<CNcomment:LNB�߱���Ƶ�ʣ���λMHz*/
    HI_UNF_TUNER_FE_LNB_BAND_E  enLNBBand;      /**< LNB band, C or Ku */                   /**<CNcomment:LNB���Σ�C��Ku*/
} HI_UNF_TUNER_FE_LNB_CONFIG_S;

/**CNcomment:TUNER����*/
typedef struct  hiTUNER_ATTR_S
{
    HI_UNF_TUNER_SIG_TYPE_E     enSigType ;         /**<Signal type*/                             /**<CNcomment:�ź�����*/
    HI_UNF_TUNER_DEV_TYPE_E enTunerDevType;     /**<Tuner type*/                              /**<CNcomment:TUNER����*/
    HI_U32 u32TunerAddr;                                      /*The i2c address of tuner, if demod type is 3130I,3130E or J83B, you cannot set it*/
    HI_UNF_DEMOD_DEV_TYPE_E enDemodDevType;     /**<QAM type*/                                /**<CNcomment:QAM����*/
    HI_U32 u32DemodAddr;                                   /*The i2c address of demod, if demod type is 3130I,3130E or J83B, you cannot set it*/
    HI_UNF_TUNER_OUPUT_MODE_E   enOutputMode ;      /**<Output mode of transport streams (TSs)*/  /**<CNcomment:TS�����ģʽ*/
    HI_U8   enI2cChannel;       /**<I2C channel used by the tuner*/           /**<CNcomment:TUNERʹ�õ�I2Cͨ��*/
    HI_U32                         u32ResetGpioNo;  /**<Demod reset GPIO NO.*/
    //union
    //{
    //    HI_UNF_TUNER_TER_ATTR_S stTer ;         /**<Attributes of the terrestrial signal. */  /**<CNcomment:�����ź�����*/
    //    HI_UNF_TUNER_SAT_ATTR_S stSat;          /**<Attributes of the satellite signal.*/     /**<CNcomment:�����ź�����*/
    //} unTunerAttr;
} HI_UNF_TUNER_ATTR_S ;

/**Frequency locking parameters of the tuner*/
/**CNcomment:TUNER��Ƶ����*/
typedef struct  hiUNF_TUNER_CONNECT_PARA_S
{
    HI_UNF_TUNER_SIG_TYPE_E enSigType ;        /**<Signal type*/                 /**<CNcomment:�ź�����*/

    union
    {
        HI_UNF_CAB_CONNECT_PARA_S   stCab ;   /**<Cable transmission signal*/    /**<CNcomment:CABLE�����ź�*/
        HI_UNF_TER_CONNECT_PARA_S stTer ;       /**<Terrestrial transmission signal*/ /**<CNcomment:���洫���ź�*/
        HI_UNF_SAT_CONNECT_PARA_S stSat;        /**<Satellite transmission signal*/   /**<CNcomment:���Ǵ����ź�*/
    } unConnectPara;
} HI_UNF_TUNER_CONNECT_PARA_S ;

/**Frequency locking status and parameters of the tuner*/
/**CNcomment:TUNER��Ƶ״̬����Ƶ����*/
typedef struct  hiUNF_TUNER_STATUS_S
{
    HI_UNF_TUNER_LOCK_STATUS_E  enLockStatus ;  /**<Frequency locking status*/               /**<CNcomment:��Ƶ״̬*/
    HI_UNF_TUNER_CONNECT_PARA_S stConnectPara;  /**<Actual frequency locking parameters*/    /**<CNcomment:ʵ����Ƶ����*/
}HI_UNF_TUNER_STATUS_S ;
/**Tuner blind scan type*/
/**CNcomment:TUNERäɨ��ʽ*/
typedef enum hiUNF_TUNER_BLINDSCAN_MODE_E
{
    HI_UNF_TUNER_BLINDSCAN_MODE_AUTO = 0,       /**<Blind scan automatically*/  /**<CNcomment:�Զ�ɨ��*/
    HI_UNF_TUNER_BLINDSCAN_MODE_MANUAL,         /**<Blind scan manually*/       /**<CNcomment:�ֶ�ɨ��*/
    HI_UNF_TUNER_BLINDSCAN_MODE_BUTT
} HI_UNF_TUNER_BLINDSCAN_MODE_E;

/**Definition of blind scan event type*/
/**CNcomment:TUNERäɨ�¼�*/
typedef enum hiUNF_TUNER_BLINDSCAN_EVT_E
{
    HI_UNF_TUNER_BLINDSCAN_EVT_STATUS,          /**<New status*/        /**<CNcomment:״̬�仯*/
    HI_UNF_TUNER_BLINDSCAN_EVT_PROGRESS,        /**<New Porgress */     /**<CNcomment:���ȱ仯*/
    HI_UNF_TUNER_BLINDSCAN_EVT_NEWRESULT,       /**<Find new channel*/  /**<CNcomment:��Ƶ��*/
    HI_UNF_TUNER_BLINDSCAN_EVT_BUTT
} HI_UNF_TUNER_BLINDSCAN_EVT_E;

/**Definition of tuner blind scan status*/
/**CNcomment:TUNERäɨ״̬*/
typedef enum hiUNF_TUNER_BLINDSCAN_STATUS_E
{
    HI_UNF_TUNER_BLINDSCAN_STATUS_IDLE,         /**<Idel*/              /**<����*/
    HI_UNF_TUNER_BLINDSCAN_STATUS_SCANNING,     /**<Scanning*/          /**<ɨ����*/
    HI_UNF_TUNER_BLINDSCAN_STATUS_FINISH,       /**<Finish*/            /**<�ɹ����*/
    HI_UNF_TUNER_BLINDSCAN_STATUS_QUIT,         /**<User quit*/         /**<�û��˳�*/
    HI_UNF_TUNER_BLINDSCAN_STATUS_FAIL,         /**<Scan fail*/         /**<ɨ��ʧ��*/
    HI_UNF_TUNER_BLINDSCAN_STATUS_BUTT
} HI_UNF_TUNER_BLINDSCAN_STATUS_E;

/**Structure of satellite TP*/
/**CNcomment:TUNERɨ��TP��Ϣ*/
typedef struct  hiUNF_TUNER_SAT_TPINFO_S
{
    HI_U32                         u32Freq;         /**<Downlink frequency, in kHz*/ /**<CNcomment:����Ƶ�ʣ���λ��kHz*/
    HI_U32                         u32SymbolRate;   /**<Symbol rate, in bit/s*/      /**<CNcomment:�����ʣ���λbps */
    HI_UNF_TUNER_FE_POLARIZATION_E enPolar;         /**<Polarization type*/          /**<CNcomment:������ʽ*/
    //HI_U8 agc_h8;                                   /**<*The high 8 bits of AGC*/    /**<CNcomment:AGC�����ָ�8bit*/
    HI_U8 cbs_reliablity;                           /**<TP reliability*/             /**<CNcomment:TP�Ŀɿ���*/
} HI_UNF_TUNER_SAT_TPINFO_S;

#if 0
/**Result of tuner blind scan */
/**CNcomment:TUNERäɨ�����Ϣ*/
typedef union hiUNF_TUNER_BLINDSCAN_RESULT_U
{
    HI_UNF_TUNER_SAT_TPINFO_S stSat;                /**<Information of new channel*/ /**<CNcomment:��Ƶ����Ϣ*/
} HI_UNF_TUNER_BLINDSCAN_RESULT_U;
#endif

/**Notify structure of tuner blind scan */
/**CNcomment:TUNERäɨ֪ͨ��Ϣ*/
typedef union hiUNF_TUNER_BLINDSCAN_NOTIFY_U
{
    HI_UNF_TUNER_BLINDSCAN_STATUS_E* penStatus;             /**<Scanning status*/
    HI_U16*                          pu16ProgressPercent;   /**<Scanning progress*/
    HI_UNF_TUNER_SAT_TPINFO_S* pstResult;             /**<Scanning result*/
} HI_UNF_TUNER_BLINDSCAN_NOTIFY_U;

/**Parameter of the satellite tuner blind scan */
/**CNcomment:����TUNERäɨ����*/
typedef struct hiUNF_TUNER_SAT_BLINDSCAN_PARA_S
{
    /**<LNB Polarization type, only take effect in manual blind scan mode*/
    /**<CNcomment:LNB������ʽ���Զ�ɨ��ģʽ������Ч*/
    HI_UNF_TUNER_FE_POLARIZATION_E enPolar;
    
    /**<LNB 22K signal status, for Ku band LNB which has dual LO, 22K ON will select high LO and 22K off select low LO,
        only take effect in manual blind scan mode*/
    /**<CNcomment:LNB 22K״̬������Ku����˫����LNB��ONѡ��߱���OFFѡ��ͱ����Զ�ɨ��ģʽ������Ч*/
    HI_UNF_TUNER_FE_LNB_22K_E      enLNB22K;

    /**<Blind scan start IF, in kHz, only take effect in manual blind scan mode */
    /**<CNcomment:äɨ��ʼƵ��(��Ƶ)����λ��kHz���Զ�ɨ��ģʽ������Ч*/
    HI_U32                         u32StartFreq;   

    /**<Blind scan stop IF, in kHz, only take effect in manual blind scan mode */
    /**<CNcomment:äɨ����Ƶ��(��Ƶ)����λ��kHz���Զ�ɨ��ģʽ������Ч*/
    HI_U32                         u32StopFreq; 

    /**<The execution of the blind scan may change the 13/18V or 22K status. 
        If you use any DiSEqC device which need send command when 13/18V or 22K status change,
        you should registe a callback here. Otherwise, you can set NULL here.*/
    /**<CNcomment:äɨ���̿��ܻ��л�������ʽ��22K�����������ĳЩDiSEqC�豸��Ҫ����13/18V��22K�ģ�
        ��ע������ص������û���ã���ɴ�NULL */
    HI_VOID (*pfnDISEQCSet)(HI_U32 u32TunerId, HI_UNF_TUNER_FE_POLARIZATION_E enPolar,
                            HI_UNF_TUNER_FE_LNB_22K_E enLNB22K);

    /**<Callback when scan status change, scan progress change or find new channel.*/
    /**<CNcomment:ɨ��״̬����Ȱٷֱȷ����仯ʱ�������µ�Ƶ��ʱ�ص�*/
    HI_VOID (*pfnEVTNotify)(HI_U32 u32TunerId, HI_UNF_TUNER_BLINDSCAN_EVT_E enEVT, HI_UNF_TUNER_BLINDSCAN_NOTIFY_U * punNotify);
} HI_UNF_TUNER_SAT_BLINDSCAN_PARA_S;

/**Parameter of the tuner blind scan */
/**CNcomment:TUNERäɨ����*/
typedef struct hiUNF_TUNER_BLINDSCAN_PARA_S
{
    HI_UNF_TUNER_BLINDSCAN_MODE_E enMode;
    union
    {
        HI_UNF_TUNER_SAT_BLINDSCAN_PARA_S stSat;
    } unScanPara;
} HI_UNF_TUNER_BLINDSCAN_PARA_S;


/**DiSEqC Level*/
typedef enum hiUNF_TUNER_DISEQC_LEVEL_E
{
    HI_UNF_TUNER_DISEQC_LEVEL_1_X,      /**<1.x, one way*/                  /**<1.x������ */
    HI_UNF_TUNER_DISEQC_LEVEL_2_X,      /**<2.x, two way, support reply*/   /**<2.x��˫��֧��Reply*/
    HI_UNF_TUNER_DISEQC_LEVEL_BUTT
} HI_UNF_TUNER_DISEQC_LEVEL_E;

/**Receive status of DiSEqC reply massage */
/**CNcomment:DiSEqC��Ϣ����״̬*/
typedef enum hiUNF_TUNER_DISEQC_RECV_STATUS_E
{
    HI_UNF_TUNER_DISEQC_RECV_OK,        /**<Receive successfully*/          /**<���ճɹ�*/
    HI_UNF_TUNER_DISEQC_RECV_UNSUPPORT, /**<Device don't support reply*/    /**<�豸��֧�ֻش�*/    
    HI_UNF_TUNER_DISEQC_RECV_TIMEOUT,   /**<Receive timeout*/               /**<���ճ�ʱ*/
    HI_UNF_TUNER_DISEQC_RECV_ERROR,     /**<Receive fail*/                  /**<���ճ���*/
    HI_UNF_TUNER_DISEQC_RECV_BUTT
} HI_UNF_TUNER_DISEQC_RECV_STATUS_E;

/**Structure of the DiSEqC send massage */
/**CNcomment:DiSEqC������Ϣ�ṹ*/
typedef struct hiUNF_TUNER_DISEQC_SENDMSG_S
{
    HI_UNF_TUNER_DISEQC_LEVEL_E     enLevel;        /**<Device device level*/
    HI_UNF_TUNER_SWITCH_TONEBURST_E enToneBurst;    /**<Tone Burst */
    HI_U8                           au8Msg[HI_UNF_DISEQC_MSG_MAX_LENGTH]; /**<Message data*/
    HI_U8                           u8Length;       /**<Message length*/
    HI_U8                           u8RepeatTimes;  /**<Message repeat times*/
} HI_UNF_TUNER_DISEQC_SENDMSG_S;

/**Structure of the DiSEqC reply massage */
/**CNcomment:DiSEqC������Ϣ�ṹ*/
typedef struct hiUNF_TUNER_DISEQC_RECVMSG_S
{
    HI_UNF_TUNER_DISEQC_RECV_STATUS_E enStatus;     /**<Recieve status*/
    HI_U8                             au8Msg[HI_UNF_DISEQC_MSG_MAX_LENGTH]; /**<Recieve message data*/
    HI_U8                             u8Length;     /**<Recieve message length*/
} HI_UNF_TUNER_DISEQC_RECVMSG_S;

//#ifdef HI_BOOT_DISEQC_SUPPORT
/**DiSEqC Switch port */
typedef enum hiUNF_TUNER_DISEQC_SWITCH_PORT_E
{
    HI_UNF_TUNER_DISEQC_SWITCH_NONE = 0,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_1,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_2,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_3,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_4,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_5,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_6,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_7,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_8,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_9,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_10,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_11,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_12,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_13,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_14,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_15,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_16,
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_BUTT
} HI_UNF_TUNER_DISEQC_SWITCH_PORT_E;

/**Parameter for DiSEqC 1.0/2.0 switch
   Some DiSEqC device need set polarization(13/18V) and 22K, you can set them here. */
/**CNcomment:DiSEqC 1.0/2.0 ���ز���
   ��ЩDiSEqC�豸��Ҫ���ü�����ʽ��22K�ģ�������������豸����Ҫ���������� */
typedef struct hiUNF_TUNER_DISEQC_SWITCH4PORT_S
{
    HI_UNF_TUNER_DISEQC_LEVEL_E       enLevel;  /**<DiSEqC device level*/
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_E enPort;   /**<DiSEqC switch port*/
    HI_UNF_TUNER_FE_POLARIZATION_E    enPolar;  /**<Polarization type */
    HI_UNF_TUNER_FE_LNB_22K_E         enLNB22K; /**<22K status*/
} HI_UNF_TUNER_DISEQC_SWITCH4PORT_S;

/**Parameter for DiSEqC 1.1/2.1 switch */
/**CNcomment:DiSEqC 1.1/2.1 ���ز��� */
typedef struct hiUNF_TUNER_DISEQC_SWITCH16PORT_S
{
    HI_UNF_TUNER_DISEQC_LEVEL_E       enLevel;  /**<DiSEqC device level*/
    HI_UNF_TUNER_DISEQC_SWITCH_PORT_E enPort;   /**<DiSEqC switch port*/
} HI_UNF_TUNER_DISEQC_SWITCH16PORT_S;

/**DiSEqC motor limit setting*/
/**CNcomment:DiSEqC��Ｋ������ */
typedef enum hiUNF_TUNER_DISEQC_LIMIT_E
{
    HI_UNF_TUNER_DISEQC_LIMIT_OFF,              /**<Disable Limits*/
    HI_UNF_TUNER_DISEQC_LIMIT_EAST,             /**<Set East Limit*/
    HI_UNF_TUNER_DISEQC_LIMIT_WEST,             /**<Set West Limit*/
    HI_UNF_TUNER_DISEQC_LIMIT_BUTT
} HI_UNF_TUNER_DISEQC_LIMIT_E;

/**Difinition of DiSEqC motor move direction*/
/**CNcomment:DiSEqC����ƶ����� */
typedef enum hiUNF_TUNER_DISEQC_MOVE_DIR_E
{
    HI_UNF_TUNER_DISEQC_MOVE_DIR_EAST,          /**<Move east*/
    HI_UNF_TUNER_DISEQC_MOVE_DIR_WEST,          /**<Move west*/
    HI_UNF_TUNER_DISEQC_MOVE_DIR_BUTT
} HI_UNF_TUNER_DISEQC_MOVE_DIR_E;

/**Difinition of DiSEqC motor move type*/
/**CNcomment:DiSEqC����ƶ���ʽ*/
typedef enum hiUNF_TUNER_DISEQC_MOVE_TYPE_E
{
    HI_UNF_TUNER_DISEQC_MOVE_STEP_SLOW,         /**<1 step one time, default*/
    HI_UNF_TUNER_DISEQC_MOVE_STEP_FAST,         /**<5 step one time*/
    HI_UNF_TUNER_DISEQC_MOVE_CONTINUE,          /**<Continuous moving*/
    HI_UNF_TUNER_DISEQC_MOVE_TYPE_BUTT
} HI_UNF_TUNER_DISEQC_MOVE_TYPE_E;

/**Parameter for DiSEqC motor store position*/
/**CNcomment:���ߴ洢λ�ò���*/
typedef struct hiUNF_TUNER_DISEQC_POSITION_S
{
    HI_UNF_TUNER_DISEQC_LEVEL_E enLevel;        /**<DiSEqC device level*/
    HI_U32                      u32Pos;         /**<Index of position, 0-255*/
} HI_UNF_TUNER_DISEQC_POSITION_S;

/**Parameter for DiSEqC motor limit setting*/
/**CNcomment:����Limit���ò���*/
typedef struct hiUNF_TUNER_DISEQC_LIMIT_S
{
    HI_UNF_TUNER_DISEQC_LEVEL_E enLevel;        /**<DiSEqC device level*/
    HI_UNF_TUNER_DISEQC_LIMIT_E enLimit;        /**<Limit setting*/
} HI_UNF_TUNER_DISEQC_LIMIT_S;

/**Parameter for DiSEqC motor moving*/
/**CNcomment:DiSEqC����ƶ�����*/
typedef struct hiUNF_TUNER_DISEQC_MOVE_S
{
    HI_UNF_TUNER_DISEQC_LEVEL_E     enLevel;    /**<DiSEqC device level*/
    HI_UNF_TUNER_DISEQC_MOVE_DIR_E  enDir;      /**<Moving direction */
    HI_UNF_TUNER_DISEQC_MOVE_TYPE_E enType;     /**<Moving type */
} HI_UNF_TUNER_DISEQC_MOVE_S;

/**Parameter for DiSEqC motor recalculate*/
/**CNcomment:DiSEqC�����ؼ������*/
typedef struct hiUNF_TUNER_DISEQC_RECALCULATE_S
{
    HI_UNF_TUNER_DISEQC_LEVEL_E enLevel;        /**<DiSEqC device level*/
    HI_U8                       u8Para1;        /**<Parameter 1 */
    HI_U8                       u8Para2;        /**<Parameter 2 */
    HI_U8                       u8Para3;        /**<Parameter 3 */
    HI_U8                       u8Reserve;      /**<Reserve */
} HI_UNF_TUNER_DISEQC_RECALCULATE_S;

/**Parameter for USALS*/
/**CNcomment:USALS ����*/
typedef struct hiUNF_TUNER_DISEQC_USALS_PARA_S
{
    HI_U16 u16LocalLongitude;   /**<local longitude, is 10*longitude, in param, E:0-1800, W:1800-3600(3600-longtitude) */
    HI_U16 u16LocalLatitude;    /**<local latitude, is 10*latitude, in param N:0-900, S:900-1800(1800-latitude)*/
    HI_U16 u16SatLongitude;     /**<sat longitude, is 10*longitude, in param, E:0-1800, W:1800-3600(3600-longtitude)  */
    HI_U16 u16Angular;          /**<calculate result, out param */
} HI_UNF_TUNER_DISEQC_USALS_PARA_S;

/**Parameter for USALS goto angular*/
/**CNcomment:USALS�ǶȲ���*/
typedef struct hiUNF_TUNER_DISEQC_USALS_ANGULAR_S
{
    HI_UNF_TUNER_DISEQC_LEVEL_E enLevel;        /**<DiSEqC device level*/
    HI_U16                      u16Angular;     /**<Angular, calculated by HI_UNF_TUNER_DISEQC_CalcAngular()*/
} HI_UNF_TUNER_DISEQC_USALS_ANGULAR_S;
//#endif /* HI_BOOT_DISEQC_SUPPORT */

/** @} */  /** <!-- ==== Structure Definition end ==== */


/******************************* API Declaration *****************************/
/** \addtogroup      H_1_4_10 */
/** @{ */  /** <!-- [TUNER] */
/*---TUNER---*/
/** 
\brief Initializes the tuner.
CNcomment:\brief ��ʼ��TUNER�豸��

\attention \n
The error code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:֧���ظ���ʼ��TUNER�豸����ʱֱ�ӷ��سɹ���
\param N/A                                    CNcomment:��
\retval ::HI_SUCCESS Success                  CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails. CNcomment:APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_Init(HI_VOID);


/** 
\brief Deinitializes the tuner.
CNcomment:\brief ȥ��ʼ��TUNER�豸��

\attention \n
The error code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:֧���ظ�ȥ��ʼ��TUNER�豸����ʱֱ�ӷ��سɹ���
\param  N/A                    CNcomment:��
\retval ::HI_SUCCESS Success   CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails. CNcomment:APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DeInit(HI_VOID);


/**
\brief  Obtains the default attributes of the tuner. 
CNcomment:\brief  ��ȡTUNER��Ĭ�����ԡ�
\attention \n
This API is available only after the tuner is initialized.
CNcomment:�˽ӿ���TUNER�豸��ʼ�������ʹ�á�
\param[in] u32tunerId   tuner port ID. The port ID can be 0-2.             CNcomment:TUNER�˿ںţ�ȡֵΪ0-2��
\param[out] pstTunerAttr The default attributes of the tuner are returned. CNcomment:���ص�ǰTUNER��Ĭ�����ԡ�
\retval ::HI_SUCCESS Success                                               CNcomment: �ɹ�
\retval ::HI_FAILURE Calling this API fails.                               CNcomment:APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_GetDeftAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr );


/** 
\brief Sets the current attributes of the tuner.
CNcomment:\brief ����TUNER��ǰ���ԡ�
\attention \n
N/A
\param[in] u32tunerId   tuner port ID. The port ID can be 0-2.      CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstTunerAttr tuner attributes                            CNcomment:TUNER�����ԡ�
\retval ::HI_SUCCESS Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails.                       CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_SetAttr(HI_U32  u32tunerId , const HI_UNF_TUNER_ATTR_S *pstTunerAttr );

/** 
\brief While using satellite channel, sets the current attributes of the tuner.
CNcomment:\brief ��������TUNER�������ԡ�CNend
\attention \n
N/A
\param[in] u32tunerId   tuner port ID. The port ID can be 0-2.      CNcomment:����TUNER�˿ںţ�ȡֵΪ0-2 CNend
\param[in] pstSatTunerAttr tuner attributes                         CNcomment:����TUNER�ĸ������ԡ�CNend
\retval ::HI_SUCCESS Success                                        CNcomment:�ɹ� CNend
\retval ::HI_FAILURE  Calling this API fails.                       CNcomment:APIϵͳ����ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_SetSatAttr(HI_U32	u32tunerId , const HI_UNF_TUNER_SAT_ATTR_S *pstSatTunerAttr);

/** 
\brief Obtains the attributes of the tuner.
CNcomment:\brief ��ȡTUNER�����ԡ�

\attention \n
This API is available only after the tuner is initialized.
CNcomment:�˽ӿ���TUNER�豸��ʼ�������ʹ�á�

\param[in] u32tunerId  tuner port ID. The port ID can be 0-2.                CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[out] pstTunerAttr   The current attributes of the tuner are returned. CNcomment:���ص�ǰTUNER�����ԡ�
\retval ::HI_SUCCESS Success                                                 CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails.                                CNcomment: APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_GetAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr );


/** 
\brief Starts the tuner.
CNcomment:\brief ��TUNER�豸��

\attention \n
The error code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:֧���ظ���TUNER�豸����ʱ��ֱ�ӷ��سɹ���

\param[in] u32tunerId   tuner port ID. The port ID can be 0-2.      CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\retval ::HI_SUCCESS Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE Calling this API fails.                        CNcomment:APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_Open (HI_U32    u32tunerId);


/** 
\brief Stops the tuner.
CNcomment:\brief �ر�TUNER�豸��

\attention \n
The error code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:֧���ظ��ر�TUNER�豸����ʱ��ֱ�ӷ��سɹ���

\param[in] u32tunerId  tuner port ID. The port ID can be 0-2.     CNcomment:TUNER�˿ںţ�ȡֵΪ0-2 
\retval ::HI_SUCCESS Success                                      CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails.                     CNcomment:APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_Close(HI_U32    u32tunerId);


/** 
\brief Locks the frequency of the tuner.
CNcomment:\brief TUNER��Ƶ��
\attention \n
N/A
\param[in] u32tunerId  tuner port ID. The port ID can be 0-2.             CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstConnectPara   Information about the frequency of the tuner  CNcomment:TUNER��Ƶ����Ϣ��
\param[in] u32TimeOut  Wait timeout (in ms) when the frequency of the tuner is locked. The value 0 indicates no wait, and any other value indicates the maximum wait period.  CNcomment:TUNER�������ȴ���ʱʱ�䣬0Ϊ���ȴ�������Ϊ��ȴ�ʱ�䣬��λms��
\retval ::HI_SUCCESS Success                                              CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails.                             CNcomment:APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_Connect(HI_U32  u32tunerId , const HI_UNF_TUNER_CONNECT_PARA_S  *pstConnectPara,HI_U32 u32TimeOut);


/**
\brief  set TS out.CNcomment:����TS���
\attention \n
\Please call this API to set TS out. \n
\There are 12 signals in ts interface, ts_dat[0..7], ts_sync, ts_vld, ts_err, ts_clk.\n 
\There're 12 pins in HI3136 chip, and each pin can be set to output ts_dat[0..7], ts_sync,\n
\ts_vld or ts_err, but ts_clk is binded to one pin, cannot be setted.\n
CNcomment:ts�ӿڹ���12���ź��ߣ��ֱ���ts_dat[0..7], ts_sync, ts_vld, ts_err, ts_clk��HI3136оƬ����12��ts�ܽţ�ÿ���ܽſ���\n
���óɳ�ts_clk֮�������һ���ܽţ�ts_clk�ǹ̶���HI3136оƬ�ϵģ���֧�����á�

\param[in] u32tunerId  tuner port ID. The port ID can be 0-2.             CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstTSOUT   pointer of ts pin.                                  CNcomment:ָ�����ͣ�ts�ܽŶ��壬��μ�::HI_UNF_TUNER_TSOUT_SET_S
\retval ::HI_SUCCESS                                                      CNcomment: success.�ɹ�
\retval ::HI_FAILURE  Calling this API fails.                             CNcomment:APIϵͳ����ʧ��
\see \n
none.CNcomment:��
*/
HI_S32 HI_UNF_TUNER_SetTSOUT(HI_U32 u32TunerId, HI_UNF_TUNER_TSOUT_SET_S *pstTSOUT);

/** 
\brief Obtains the frequency locking status and parameters of the tuner.
CNcomment:\brief ��ȡTUNER��Ƶ״̬����Ƶ������
\attention \n
N/A
\param[in] u32tunerId tuner port ID. The port ID can be 0-2.             CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] u32TimeOut frequency locking timeout, unit: ms, frequency locking time is related to strength of signal CNcomment:��Ƶ�ĳ�ʱʱ�䣬��λ�Ǻ��룬��Ƶʱ����ź�ǿ���й�ϵ��
               if you want to get the state of locking, the u32TimeOut should be set 100ms at least;
               if the u32TimeOut is 0, just config register without locking state, return HI_SUCCESS
               CNcomment: �����õ�����״̬����Ƶ��ʱ��С����Ϊ100ms��
               CNcomment: �����ʱʱ��Ϊ0��ֻ���üĴ��������ж�����״̬������HI_SUCCESS��
\param[out] pstTunerStatus: The current frequency locking status and parameters of the tuner are returned. Note: This parameter is valid only when HI_SUCCESS is returned.  CNcomment: ���ص�ǰTUNER����Ƶ״̬����Ƶ������ ע�⣺�˲���ֻ�ں������سɹ�������²������塣
\retval ::HI_SUCCESS Success                    CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails.  CNcomment:APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_GetStatus(HI_U32    u32tunerId , HI_UNF_TUNER_STATUS_S  *pstTunerStatus);


/** 
\brief Obtains the current bit error rate (BER) of the tuner. The BER is expressed by using the scientific notation.
CNcomment:\brief ��ȡ��ǰTUNER �������ʣ��ÿ�ѧ��������ʾ��
\attention \n
N/A
\param[in] u32tunerId tuner port ID. The port ID can be 0-2.             CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[out] pu32BER  Pointer to the current BER of the tuner The error bit rate consists of three elements. Their definitions are as follows:
                      Their definitions are as follows:
                    pu32BER[0]: integral part of the base number of the BER
                    pu32BER[1]: decimal part of the base number of the BER x 1000
                    pu32BER[2]: absolute value of the exponential of the BER
                    For example, if the BER is 2.156E-7, the values of the three elements are
                    2, 156, and 7 respectively.
                    The three elements are valid only when HI_SUCCESS is returned.
                    Otherwise, the application layer sets a large value as required, for example, 0.5 (the values of the three elements are 5, 0, and 1 respectively).
                         0.5 (the values of the three elements are 5, 0, and 1 respectively).
CNcomment:\param[out] pu32BER  ָ��ǰTUNER �����ʵ�ָ�롣��ָ��ָ��һ����������Ԫ�ص����飬����Ԫ�غ�������:
CNcomment:                    pu32BER[0]:�����ʵ�������������
CNcomment:                    pu32BER[1]:�����ʵ�����С�����ֳ���1000
CNcomment:                    pu32BER[2]:������ָ������ȡ����ֵ
CNcomment:                    ����:������Ϊ2.156E-7����ô����Ԫ�ص�ȡֵ�ֱ�Ϊ
CNcomment:                    2��156��7
CNcomment:                    ������Ԫ��ֻ�ں������سɹ�������²������壬
CNcomment:                    ����Ӧ�ò�ɸ���ʵ�������������һ���ϴ�ֵ(����0.5��������Ԫ�طֱ�Ϊ5��0��1)��
\retval ::HI_SUCCESS Success                  CNcomment:�ɹ�
\retval ::HI_FAILURE Calling this API fails.  CNcomment:APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_GetBER(HI_U32   u32tunerId , HI_U32 *pu32BER);


/** 
\brief Obtains the current signal-to-noise ratio (SNR) of the tuner.
CNcomment:\brief ��ȡ��ǰTUNER ������ȡ�
\attention \n
N/A
\param[in] u32tunerId  tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[out] pu32SNR  Pointer to the current SNR of the tuner
                    The value of *pu32SNR ranges from 22 to 51.
                    This parameter is valid only when HI_SUCCESS is returned.
                   Otherwise, the application layer sets the parameter to a small value.
CNcomment:\param[out] pu32SNR  ָ��ǰTUNER����ȵ�ָ�롣
CNcomment:                    *pu32SNRȡֵ��ΧΪ22 ~ 51
CNcomment:                    �˲���ֻ�ں������سɹ�������²������壬
CNcomment:                    ����Ӧ�ò�ɽ���ֵ����Ϊ��Сֵ��
\retval ::HI_SUCCESS Success                   CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails.  CNcomment:APIϵͳ����ʧ��

\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_GetSNR(HI_U32   u32tunerId , HI_U32 *pu32SNR );             /* range : 0-255  */


/** 
\brief Obtains the current signal strength of the tuner.
CNcomment:\brief ��ȡ��ǰTUNER���ź�ǿ�ȡ�
\attention \n
N/A
\param[in] u32tunerId  tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[out] pu32SignalStrength  Pointer to the current signal strength of the tuner
                            For cable signal, the value of *pu32SignalStrength ranges from 20~120.
                            For satellite signal, the value is 15~130��unit in dBuv.
                  This parameter is valid only when HI_SUCCESS is returned.
                  Otherwise, the application layer sets the parameter to a small value.
CNcomment:\param[out] pu32SignalStrength  ָ��ǰTUNER�ź�ǿ�ȵ�ָ�롣
CNcomment:                  ����Cable�źţ�*pu32SignalStrength��ȡֵ��ΧΪ20~120
CNcomment:                  ����Satellite�źţ�*pu32SignalStrength��ȡֵ��ΧΪ15~130����λΪdBuv
CNcomment:                  �˲���ֻ�ں������سɹ�������²������壬
CNcomment:                  ����Ӧ�ò�ɽ���ֵ����Ϊ��Сֵ��
\retval ::HI_SUCCESS Success                  CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails. CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_GetSignalStrength(HI_U32   u32tunerId , HI_U32 *pu32SignalStrength );

/**
\brief Obtains the current signal quality of the tuner, returns a percentage value. 
CNcomment:\brief ��ȡ��ǰTUNER���ź����������ذٷֱȡ�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[out] pu32SignalQuality   Output pointer.                       CNcomment:ָ���ź�������ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_GetSignalQuality(HI_U32 u32TunerId, HI_U32 *pu32SignalQuality);

/**
\brief Obtains the actual frequency and symbol rate of the current tuner for cable and satellite
signal, for terrestrial signal, symbol rate means nothing, ignore it. 
CNcomment:\brief ��ȡ��ǰTUNER��ʵ��Ƶ�ʺͷ����ʡ�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[out] pu32Freq   Pointer to the current frequency of the tuner. CNcomment:ָ��ǰTUNERƵ���ָ�롣
\param[out] pu32Symb   Points to the current symbol rate.             CNcomment:ָ��ǰ������               
\retval ::HI_SUCCESS Success                                          CNcomment:�ɹ�
\retval ::HI_FAILURE  Calling this API fails.                         CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_GetRealFreqSymb( HI_U32 u32TunerId, HI_U32 *pu32Freq, HI_U32 *pu32Symb );

/**
\brief Obtains current signal information of the TUNER, used in satellite and terrestrial, not necessary for cable. 
CNcomment:\brief ��ȡ��ǰTUNER���ź���Ϣ��
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[out] pstSignalInfo Pointer to a signal info structure.         CNcomment:ָ���ź���Ϣ�ṹ���ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_GetSignalInfo(HI_U32 u32TunerId, HI_UNF_TUNER_SIGNALINFO_S *pstSignalInfo);

/**
\brief Sets the LNB parameter. 
CNcomment:\brief ����LNB������
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstLNB      Pointer to a LNB parameter structure.          CNcomment:ָ��LNB�����ṹ���ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_SetLNBConfig(HI_U32 u32TunerId, const HI_UNF_TUNER_FE_LNB_CONFIG_S *pstLNB);

/**
\brief Sets the LNB power. 
CNcomment:\brief ����LNB���硣
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] enLNBPower  The enumeration of the LNB power type.         CNcomment:LNB���緽ʽö��ֵ��
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_SetLNBPower(HI_U32 u32TunerId, HI_UNF_TUNER_FE_LNB_POWER_E enLNBPower);

/**
\brief Sets PLP ID, only used in DVB-T2. 
CNcomment:\brief ���������ܵ�ID��
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] u8PLPID  The PLP ID.         CNcomment:�����ܵ�ID��
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/

HI_S32 HI_UNF_TUNER_SetPLPID(HI_U32 u32TunerId, HI_U8 u8PLPID);

/**
\brief Gets PLP number, only used in DVB-T2. 
CNcomment:\brief ��ȡ�����ܵ�������
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[out] pu8PLPNum  The PLP number.         CNcomment:�����ܵ�������
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/

HI_S32 HI_UNF_TUNER_GetPLPNum(HI_U32 u32TunerId, HI_U8 *pu8PLPNum);


/**
\brief Gets current PLP type, only used in DVB-T2. 
CNcomment:\brief ��ȡ��ǰ�����ܵ����͡�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[out] penPLPType  The PLP type.         CNcomment:�����ܵ����͡�
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/

HI_S32 HI_UNF_TUNER_GetCurrentPLPType(HI_U32 u32TunerId, HI_UNF_TUNER_T2_PLP_TYPE_E *penPLPType);


/**
\brief Starts blind scan. 
CNcomment:\brief ��ʼäɨ��
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstPara     The pointer to the blind scan parameter.       CNcomment:ָ��äɨ������ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see Please refer to definition of HI_UNF_TUNER_BLINDSCAN_PARA_S.
N/A
*/
HI_S32 HI_UNF_TUNER_BlindScanStart(HI_U32 u32TunerId, const HI_UNF_TUNER_BLINDSCAN_PARA_S *pstPara);

/**
\brief Stops blind scan. 
CNcomment:\brief ֹͣäɨ��
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_BlindScanStop(HI_U32 u32TunerId);

/**
\brief TUNER standby. 
CNcomment:\brief TUNER����
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_Standby(HI_U32 u32TunerId);

/**
\brief Wakes up TUNER. 
CNcomment:\brief TUNER����
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_WakeUp( HI_U32 u32TunerId);

/**
\brief Sends and receives DiSEqC message, only the devices supporting DiSEqC 2.x support receive message. 
CNcomment:\brief ���ͽ���DiSEqC��Ϣ����֧��DiSEqC 2.x���豸֧�ֽ�����Ϣ��
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstSendMsg  The pointer to a sending message structure.    CNcomment:ָ������Ϣ�ṹ���ָ�롣
\param[out] pstRecvMsg The pointer to a receiving message structure.If your device is DiSEqC 1.x, you can pass NULL here.
CNcomment:\param[out] pstRecvMsg ָ�������Ϣ�ṹ���ָ�롣�����DiSEqC 1.x�豸��������Դ�NULL��
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
/*HI_S32 HI_UNF_TUNER_DISEQC_SendRecvMessage(HI_U32 u32TunerId,
                                           HI_UNF_TUNER_DISEQC_SENDMSG_S* pstSendMsg,
                                           HI_UNF_TUNER_DISEQC_RECVMSG_S* pstRecvMsg);*/

/**
\brief Sets 0/12V switch. Don't support now. 
CNcomment:\brief ����0/12V����״̬���ݲ�֧�֡�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] enPort      The enumeration of the switch port.            CNcomment:����ö��ֵ��
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_Switch012V(HI_U32 u32TunerId, HI_UNF_TUNER_SWITCH_0_12V_E enPort);

/**
\brief Sets 22KHz switch. 
CNcomment:\brief ����22KHz����״̬��
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] enPort      The enumeration of the switch port.            CNcomment:����ö��ֵ��
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_Switch22K(HI_U32 u32TunerId, HI_UNF_TUNER_SWITCH_22K_E enPort);

/**
\brief Sets tone burst switch. 
CNcomment:\brief ����Tone burst����״̬��
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] enStatus    The enumeration of the switch port.            CNcomment:����ö��ֵ��
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_SwitchToneBurst(HI_U32 u32TunerId, HI_UNF_TUNER_SWITCH_TONEBURST_E enStatus);

//#ifdef HI_BOOT_DISEQC_SUPPORT
/**
\brief Sets DiSEqC 1.0/2.0 switch, at most 4 port.
CNcomment:\brief ����DiSEqC 1.0/2.0���أ�����4�ڡ�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstPara     The pointer to a switch parameter structure.   CNcomment:ָ�򿪹ز�����ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see Please refer to definition of HI_UNF_TUNER_DISEQC_SWITCH4PORT_S.
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_Switch4Port(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_SWITCH4PORT_S* pstPara);

/**
\brief Sets DiSEqC 1.1/2.1 switch, supports 8in1, 16in1 switches. 
CNcomment:\brief ����DiSEqC 1.1/2.1���أ�֧��8�ڣ�16�ڿ��ء�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstPara     The pointer to a switch parameter structure.   CNcomment:ָ�򿪹ز�����ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_Switch16Port(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_SWITCH16PORT_S* pstPara);

/**
\brief Lets the DiSEqC motor store current position. 
CNcomment:\brief DiSEqC���洢��ǰλ�á�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstPara     The pointer to a position parameter structure. CNcomment:ָ��λ�ò�����ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_StorePos(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_POSITION_S *pstPara);

/**
\brief Lets the DiSEqC motor move to stored position. 
CNcomment:\brief DiSEqC���ת�����洢λ�á�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstPara     The pointer to a position parameter structure. CNcomment:ָ��λ�ò�����ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_GotoPos(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_POSITION_S *pstPara);

/**
\brief Enables or disables the DiSEqC motor's limit setting. 
CNcomment:\brief �򿪡��ر�DiSEqC���Ȩ�����á�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstPara     The pointer to a limit parameter structure.    CNcomment:ָ��limit������ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_SetLimit(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_LIMIT_S* pstPara);

/**
\brief Drives DiSEqC motor. 
CNcomment:\brief ����DiSEqC����ƶ���
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstPara     The pointer to a movement parameter structure. CNcomment:ָ���ƶ�������ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_Move(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_MOVE_S* pstPara);

/**
\brief Halts DiSEqC motor. 
CNcomment:\brief ֹͣDiSEqC����ƶ���
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] enLevel     The command level of the DiSEqC motor.         CNcomment:���֧�ֵ�����ȼ���
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_Stop(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_LEVEL_E enLevel);

/**
\brief Lets the DiSEqC motor recalculate its stored positions. 
CNcomment:\brief ���¼������洢λ�á�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstPara     The pointer to a recaulculate parameter structure. CNcomment:ָ���ؼ��������ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_Recalculate(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_RECALCULATE_S* pstPara);

/**
\brief Calculates the angular, basing on site-longitude, site-latitude and satellite-longitude. 
CNcomment:\brief USALS���ݵ��ؾ�γ�ȡ����Ǿ��ȼ������ǽǶȡ�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in/out] pstPara The pointer to a USALS parameter structure.    CNcomment:ָ��USALS���������ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_CalcAngular(HI_U32 u32TunerId, HI_UNF_TUNER_DISEQC_USALS_PARA_S* pstPara);

/**
\brief Gotos the indicated angular. 
CNcomment:\brief USALS�豸ת��ĳ�Ƕȡ�
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] pstPara     The pointer to a USALS angular structure.      CNcomment:ָ��USALS�ǶȲ�����ָ�롣
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_GotoAngular(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_USALS_ANGULAR_S* pstPara);

/**
\brief Resets DiSEqC device. 
CNcomment:\brief ��λDiSEqC�豸��
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] enLevel     The command level of the DiSEqC device.        CNcomment:�豸֧�ֵ�����ȼ���
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_Reset(HI_U32 u32TunerId, HI_UNF_TUNER_DISEQC_LEVEL_E enLevel);

/**
\brief DiSEqC device standby. 
CNcomment:\brief DiSEqC�豸������
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] enLevel     The command level of the DiSEqC device.        CNcomment:�豸֧�ֵ�����ȼ���
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_Standby(HI_U32 u32TunerId, HI_UNF_TUNER_DISEQC_LEVEL_E enLevel);

/**
\brief Wakes up DiSEqC device. 
CNcomment:\brief ����DiSEqC�豸��
\attention \n
N/A
\param[in] u32TunerId  Tuner port ID. The port ID can be 0-2.         CNcomment:TUNER�˿ںţ�ȡֵΪ0-2
\param[in] enLevel     The command level of the DiSEqC device.        CNcomment:�豸֧�ֵ�����ȼ���
\retval ::HI_SUCCESS   Success                                        CNcomment:�ɹ�
\retval ::HI_FAILURE   Calling this API fails.                        CNcomment:APIϵͳ����ʧ��
\see \n
N/A
*/
HI_S32 HI_UNF_TUNER_DISEQC_WakeUp(HI_U32 u32TunerId, HI_UNF_TUNER_DISEQC_LEVEL_E enLevel);
//#endif /* HI_BOOT_DISEQC_SUPPORT */

/** @} */  /** <!-- ==== API declaration end ==== */
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_ECS_TYPE_H__ */

