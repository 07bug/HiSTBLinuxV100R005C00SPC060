/**
* \file
* \brief Describes the information about the frontend module.
*/

#ifndef  __TVOS_HAL_FRONTEND_H__
#define __TVOS_HAL_FRONTEND_H__

#include "tvos_hal_type.h"
#include "tvos_hal_dmx.h"

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
/** \addtogroup     HAL_FRONTEND */
/** @{ */  /** <!-- [HAL_FRONTEND] */
/**Module id define.*//** CNcomment:ģ��ID ���� */
#define FRONTEND_HARDWARE_MODULE_ID "frontend"

/**Device name define .*//** CNcomment:�豸���ƶ��� */
#define FRONTEND_HARDWARE_FRONTEND0 "frontend0"

/**Tuner name max length.*//** CNcomment:Tuner ������󳤶� */
#define FRONTEND_DEVICENAME_LENGTH  (32)

/**count callback setted in every frontend_handle.*//** CNcomment:ÿ��frontend_handle ע��Ļص�������������*/
#define FRONTEND_CALLBACK_MAX       (8)

/**Tuner max .*//** CNcomment:Tuner ����ж���tuner */
#define FRONTEND_FE_NUM_MAX         (8)

/** @} */  /** <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_FRONTEND */
/** @{ */  /** <!-- [HAL_FRONTEND] */

/**Tuner name type*//** CNcomment:Tuner �������ݽṹ */
typedef char FRONTEND_DEVICE_NAME[FRONTEND_DEVICENAME_LENGTH + 1];

/**System init param *//** CNcomment:ϵͳ��ʼ������ */
typedef struct _FRONTEND_INIT_PARAMS_S
{
    U32  u32Dummy;                        /**<for expand *//**<CNcomment:��չʹ��*/
} FRONTEND_INIT_PARAMS_S;

/**System deinit param *//** CNcomment:ϵͳȥ��ʼ������ */
typedef struct _FRONTEND_TERM_PARAMS_S
{
    U32  u32Dummy;                        /**<for expand *//**<CNcomment:��չʹ��*/
} FRONTEND_TERM_PARAMS_S;

/**frontend fe status *//** CNcomment:ǰ��״̬ */
typedef enum _FRONTEND_FE_STATUS_E
{
    FRONTEND_STATUS_UNKNOW = 0 ,          /**<Unknow status *//**<CNcomment:δ֪״̬���豸��ʼ������û���κ�ʵ��ʱ������δ֪״̬*/
    FRONTEND_STATUS_UNLOCKED,             /**<unlocked *//**<CNcomment:δ���������Զ�β���������ŷ��ظ�״̬. �ײ���Ȼ�ڳ���*/
    FRONTEND_STATUS_SCANNING,             /**<locking *//**<CNcomment:����ɨ�裬���Զ���������������ĳ�TUNER_STATUS_UNLOCKED(ɨ�������ȷ���Ƿ�Ϊ����״̬)*/
    FRONTEND_STATUS_LOCKED,               /**<locked *//**<CNcomment:����*/
    FRONTEND_STATUS_NOSIGNAL,             /**<no signal *//**<CNcomment:û���źţ�����ͬTUNER_STATUS_UNLOCKED*/
    FRONTEND_STATUS_DISCONNECTED,         /**<disconnected *//**<CNcomment:�ѶϿ�TS������*/
    FRONTEND_STATUS_IDLE,                 /**<idle *//**<CNcomment:��ʼ״̬���Լ�������disconnect��������״̬�²���������Ƶ(���ƿ���״̬)*/
    FRONTEND_STATUS_BLINDSCANING,         /**<blind scanning *//**<CNcomment:Demod ����äɨ״̬, Ӧ����Ҫ�ȴ�äɨ���, ���߷�����Ƶ��Ϣǿ���˳�äɨ*/
    FRONTEND_STATUS_BLINDSCAN_COMPLETE,   /**<blind scan complete *//**<CNcomment:Demod äɨ���*/
    FRONTEND_STATUS_BLINDSCAN_QUIT,       /**<User quit*//**<CNcomment:�û��˳�*/
    FRONTEND_STATUS_BLINDSCAN_FAIL,       /**<Scan fail*//**<CNcomment:ɨ��ʧ��*/
    FRONTEND_STATUS_MOTOR_MOVING,         /**<Motor move*//**<CNcomment:����ƶ�*/
    FRONTEND_STATUS_MOTOR_STOP,           /**<Motor stop*//**<CNcomment:���ֹͣ*/
    FRONTEND_STATUS_BUTT
} FRONTEND_FE_STATUS_E;

/**frontend type  *//** CNcomment:ǰ������. */
typedef enum _FRONTEND_FE_TYPE_E
{
    FRONTEND_FE_SATELLITE1   = 1 << 0,    /** -S */ /**<CNcomment:����*/
    FRONTEND_FE_SATELLITE2   = 1 << 1,    /** -S2 */ /**<CNcomment:S2*/
    FRONTEND_FE_CABLE1       = 1 << 2,    /** -C */ /**<CNcomment:C*/
    FRONTEND_FE_CABLE2       = 1 << 3,    /** -C2 */ /**<CNcomment:C2*/
    FRONTEND_FE_TERRESTRIAL1 = 1 << 4,    /** -T */ /**<CNcomment:TERRESTRIAL1*/
    FRONTEND_FE_TERRESTRIAL2 = 1 << 5,    /** -T2 */ /**<CNcomment:TERRESTRIAL2*/
    FRONTEND_FE_ATV1         = 1 << 6,    /** -ATV */ /**<CNcomment:ATV1*/
    FRONTEND_FE_DTMB1        = 1 << 7,    /** -DTMB */ /**<CNcomment:DTMB1*/
    FRONTEND_FE_ISDBT1       = 1 << 8,    /** -ISDBT */ /**<CNcomment:ISDB-T*/
    FRONTEND_FE_ATSCT        = 1 << 9,    /** -ATSC-T */ /**<CNcomment:ATSC-T*/
    FRONTEND_FE_J83B         = 1 << 10,   /** -J83B */ /**<CNcomment:J83B*/
    FRONTEND_FE_ABSS         = 1 << 11,   /** -ABSS */ /**<CNcomment:ABSS*/
    FRONTEND_FE_BUTT                      /** J83B can not or with others, so FRONTEND_FE_BUTT is FRONTEND_FE_J83B + 1, use U32 for capability description */
                                          /**<CNcomment:��Ϊ���J83B�����������źŻ�������룬����FRONTEND_FE_BUTT ֵΪ FRONTEND_FE_J83B + 1������������ʱʹ�õ���U32���ø�ö��*/
} FRONTEND_FE_TYPE_E;

/**frontend scan mode(satellite)  *//** CNcomment:����Ƶ��������ʽ*/
typedef enum _FRONTEND_SEARCH_MODE_E
{
    FRONTEND_SEARCH_MOD_NORMAL = 0,       /**<default *//**<CNcomment:Ĭ�Ϸ�ʽ*/
    FRONTEND_SEARCH_MOD_BLIND,            /**<offset freq and SR are Unknown *//**<CNcomment:Ƶ�㲽����SR��δ֪*/
    FRONTEND_SEARCH_MOD_COLD_START,       /**<only the SR is known *//**<CNcomment:��֪SR*/
    FRONTEND_SEARCH_MOD_WARM_START,       /**<offset freq and SR are known *//**<CNcomment:��֪Ƶ�㲽����SR*/
    FRONTEND_SEARCH_MOD_SAT_BLIND_MANUAL, /**<set startfreq endfreq, see FRONTEND_SAT_BLINDSCAN_PARA_S *//**<CNcomment:����Ƶ����ʼ�������͸ߵͱ��񡣲鿴 FRONTEND_SAT_BLINDSCAN_PARA_S*/
    FRONTEND_SEARCH_MOD_BUTT
} FRONTEND_SEARCH_MODE_E;

/**FRONTEND_IQ_IVT_E  *//** CNcomment:FRONTEND_IQ_IVT_E*/
typedef enum  _FRONTEND_IQ_IVT_E
{
    FRONTEND_IQ_AUTO = 0,                 /**<IQ_AUTO *//**<CNcomment:IQ_AUTO*/
    FRONTEND_IQ_AUTO_NORMAL_FIRST,        /**<IQ_AUTO_NORMAL_FIRST *//**<CNcomment:IQ_AUTO_NORMAL_FIRST*/
    FRONTEND_IQ_FORCE_NORMAL,             /**<IQ_FORCE_NORMAL *//**<CNcomment:IQ_FORCE_NORMAL*/
    FRONTEND_IQ_FORCE_SWAPPED,            /**<IQ_FORCE_SWAPPED *//**<CNcomment:IQ_FORCE_SWAPPED*/
    FRONTEND_IQ_BUTT
} FRONTEND_IQ_IVT_E;

/////////////////////////////////////////////////////////////////
//DVB-S enum begin

/** LNB type *//** CNcomment:LNB����*/
typedef enum _FRONTEND_LNB_TYPE_E
{
    FRONTEND_LNB_SINGLE_FREQUENCY = 0,    /**<Single LO frequency*//**<CNcomment:������*/
    FRONTEND_LNB_DUAL_FREQUENCY,          /**<Dual LO frequency*//**<CNcomment:˫����*/
    FRONTEND_LNB_UNICABLE,                /**<Unicable LNB *//**<CNcomment:unicable��Ƶͷ*/
    FRONTEND_LNB_TYPE_BUTT                /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_LNB_TYPE_E;

/** LNB band type*//** CNcomment:�����ź�Ƶ��*/
typedef enum _FRONTEND_LNB_BAND_E
{
    FRONTEND_LNB_BAND_C = 0,              /**<C *//**<CNcomment:C����*/
    FRONTEND_LNB_BAND_KU,                 /**<Ku *//**<CNcomment:Ku����*/
    FRONTEND_LNB_BAND_BUTT                /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_LNB_BAND_E;

/**LNB Power (satellite, Ter)  *//** CNcomment:LNB���翪��(����,����) FRONTEND_LNB_POWER_AUTO: ���Բ�ʵ��.*/
typedef enum _FRONTEND_LNB_POWER_E
{
    FRONTEND_LNB_POWER_OFF = 0,           /**<LNB_POWER_OFF *//**<CNcomment:LNB_POWER_OFF*/
    FRONTEND_LNB_POWER_ON,                /**<LNB power auto, 13V/18V, default*/                                  /**<CNcomment:Ĭ�ϵ�13/18V����*/
    FRONTEND_LNB_POWER_ENHANCED,          /**<LNB power auto, 14V/19V, some LNB control device can support.*/     /**<CNcomment:��ǿ����*/
    FRONTEND_LNB_POWER_AUTO,              /**<LNB_POWER_AUTO *//**<CNcomment:LNB_POWER_AUTO*/
    FRONTEND_LNB_POWER_BUTT
} FRONTEND_LNB_POWER_E;

/**FRONTEND rolloff (satellite)  *//** CNcomment:����ϵ��(����).*/
typedef enum _FRONTEND_ROLLOFF_E
{
    FRONTEND_ROLLOFF_35 = 0,              /**<ROLLOFF_35 *//**<CNcomment:ROLLOFF_35*/
    FRONTEND_ROLLOFF_25,                  /**<ROLLOFF_25 *//**<CNcomment:ROLLOFF_25*/
    FRONTEND_ROLLOFF_20,                  /**<ROLLOFF_20 *//**<CNcomment:ROLLOFF_20*/
    FRONTEND_ROLLOFF_BUTT
} FRONTEND_ROLLOFF_E;

/**FRONTEND POLARIZATION (satellite)  *//** CNcomment:������ʽ(����).*/
typedef enum _FRONTEND_POLARIZATION_E
{
    FRONTEND_PLR_HORIZONTAL = 0,  /**<HORIZONTAL *//**<CNcomment:ˮƽ����*/
    FRONTEND_PLR_VERTICAL,    /**<VERTICAL *//**<CNcomment:��ֱ����*/
    FRONTEND_PLR_LEFT,        /**<LEFT *//**<CNcomment:�󼫻�*/
    FRONTEND_PLR_RIGHT,       /**<RIGHT *//**<CNcomment:�Ҽ���*/
    FRONTEND_PLR_AUTO,    /**<AUTO *//**<CNcomment:�Զ�������ʽ*/
    FRONTEND_PLR_BUTT
} FRONTEND_POLARIZATION_E;

/**FRONTEND 12V out switch (satellite)  *//** CNcomment:12V����(����).*/
typedef enum _FRONTEND_LNB_12V_E
{
    FRONTEND_LNB_12V_OFF = 0, /**<12V off*//**<CNcomment:12V off*/
    FRONTEND_LNB_12V_ON,      /**<12V on *//**<CNcomment:12V on*/
    FRONTEND_LNB_12V_AUTO,    /**<12V auto *//**<CNcomment:12V auto*/
    FRONTEND_LNB_12V_BUTT
} FRONTEND_LNB_12V_E;

/** 0/12V switch*//** CNcomment:0/12V����*/
typedef enum _FRONTEND_SWITCH_0_12V_E
{
    FRONTEND_SWITCH_0_12V_NONE = 0,         /**< None, default*//**<CNcomment:���ӿ���״̬*/
    FRONTEND_SWITCH_0_12V_0,                /**< 0V*//**<CNcomment:0V״̬*/
    FRONTEND_SWITCH_0_12V_12,               /**< 12V*//**<CNcomment:12V״̬*/
    FRONTEND_SWITCH_0_12V_BUTT              /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_SWITCH_0_12V_E;

/**FRONTEND 22K out descripe LNB(satellite)  *//** CNcomment:22k�������(����).*/
typedef enum _FRONTEND_LNB_22K_E
{
    FRONTEND_LNB_22K_OFF = 0,               /**<22K_OFF*//**<CNcomment:22K_OFF*/
    FRONTEND_LNB_22K_ON,                    /**<22K_ON*//**<CNcomment:22K_ON*/
    FRONTEND_LNB_22K_AUTO,                  /**<22K_AUTO*//**<CNcomment:22K_AUTO*/
    FRONTEND_LNB_22K_BUTT
} FRONTEND_LNB_22K_E;

/** 22KHz switch*//** CNcomment:22K���ؿ���*/
typedef enum _FRONTEND_SWITCH_22K_E
{
    FRONTEND_SWITCH_22K_NONE = 0,            /**< None, default*//**<CNcomment:���ӿ���״̬*/
    FRONTEND_SWITCH_22K_OFF,                 /**< 0*//**<CNcomment:0kHz�˿�*/
    FRONTEND_SWITCH_22K_ON,                  /**< 22KHz*//**<CNcomment:22kHz�˿�*/
    FRONTEND_SWITCH_22K_BUTT                 /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_SWITCH_22K_E;

/** Tone burst switch*/
/** CNcomment:Tone burst����*/
typedef enum _FRONTEND_SWITCH_TONEBURST_E
{
    FRONTEND_SWITCH_TONEBURST_NONE = 0,      /**< Don't send tone burst, default*//**<CNcomment:���ӿ���״̬*/
    FRONTEND_SWITCH_TONEBURST_0,             /**< Tone burst 0*//**<CNcomment:0 port*/
    FRONTEND_SWITCH_TONEBURST_1,             /**< Tone burst 1*//**<CNcomment:1 port*/
    FRONTEND_SWITCH_TONEBURST_BUTT           /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_SWITCH_TONEBURST_E;

/** DiSEqC Switch port*/
/** CNcomment:DiSEqC���ض˿�ö��*/
typedef enum _FRONTEND_DISEQC_SWITCH_PORT_E
{
    FRONTEND_DISEQC_SWITCH_NONE = 0,         /**<none*//**<CNcomment:���ӿ���*/
    FRONTEND_DISEQC_SWITCH_PORT_1,           /**<port1*//**<CNcomment:�˿�1*/
    FRONTEND_DISEQC_SWITCH_PORT_2,           /**<port2*//**<CNcomment:�˿�2*/
    FRONTEND_DISEQC_SWITCH_PORT_3,           /**<port3*//**<CNcomment:�˿�3*/
    FRONTEND_DISEQC_SWITCH_PORT_4,           /**<port4*//**<CNcomment:�˿�4*/
    FRONTEND_DISEQC_SWITCH_PORT_5,           /**<port5*//**<CNcomment:�˿�5*/
    FRONTEND_DISEQC_SWITCH_PORT_6,           /**<port6*//**<CNcomment:�˿�6*/
    FRONTEND_DISEQC_SWITCH_PORT_7,           /**<port7*//**<CNcomment:�˿�7*/
    FRONTEND_DISEQC_SWITCH_PORT_8,           /**<port8*//**<CNcomment:�˿�8*/
    FRONTEND_DISEQC_SWITCH_PORT_9,           /**<port9*//**<CNcomment:�˿�9*/
    FRONTEND_DISEQC_SWITCH_PORT_10,          /**<port10*//**<CNcomment:�˿�10*/
    FRONTEND_DISEQC_SWITCH_PORT_11,          /**<port11*//**<CNcomment:�˿�11*/
    FRONTEND_DISEQC_SWITCH_PORT_12,          /**<port12*//**<CNcomment:�˿�12*/
    FRONTEND_DISEQC_SWITCH_PORT_13,          /**<port13*//**<CNcomment:�˿�13*/
    FRONTEND_DISEQC_SWITCH_PORT_14,          /**<port14*//**<CNcomment:�˿�14*/
    FRONTEND_DISEQC_SWITCH_PORT_15,          /**<port15*//**<CNcomment:�˿�15*/
    FRONTEND_DISEQC_SWITCH_PORT_16,          /**<port16*//**<CNcomment:�˿�16*/
    FRONTEND_DISEQC_SWITCH_PORT_BUTT         /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_DISEQC_SWITCH_PORT_E;

/**FRONTEND Diseqc cmd (satellite)  *//** CNcomment:DiseqcЭ��(����).*/
typedef enum _FRONTEND_LNB_DISEQC_CMD_E
{
    FRONTEND_DISEQC_COMMAND = 0,                  /**< DiSEqC (1.2/2)command   *//**<CNcomment:DiSEqC (1.2/2)����*/
    FRONTEND_DISEQC_TONE_BURST_UNMODULATED = 5,   /**<TONE_BURST_UNMODULATED*//**<CNcomment:TONE_BURST_UNMODULATED*/
    FRONTEND_DISEQC_TONE_BURST_MODULATED   = 6,   /**<TONE_BURST_MODULATED*//**<CNcomment:TONE_BURST_MODULATED*/

    FRONTEND_DISEQC_TONE_BURST_SEND_0_UNMODULATED = FRONTEND_DISEQC_TONE_BURST_UNMODULATED,      /**< send of 0 for 12.5 ms ;continuous tone*<CNcomment:TONE_BURST_UNMODULATED*/
    FRONTEND_DISEQC_TONE_BURST_SEND_0_MODULATED   = FRONTEND_DISEQC_TONE_BURST_MODULATED,        /**< 0-2/3 duty cycle tone*<CNcomment:TONE_BURST_MODULATED*/

    FRONTEND_DISEQC_BUTT
} FRONTEND_LNB_DISEQC_CMD_E;

/**FRONTEND Diseqc Ver (satellite)  *//** CNcomment:Diseqc�汾(����).*/
typedef enum _FRONTEND_DISEQC_VER_E
{
    FRONTEND_DISEQC_VER_NONE = 0,    /**< not support */ /**<CNcomment:��֧��*/

    /* 1.x */
    FRONTEND_DISEQC_VER_1_0,    /**< DiSEqC V1.0  *//**<CNcomment:DiSEqC V1.0*/
    FRONTEND_DISEQC_VER_1_1,    /**< DiSEqC V1.1  *//**<CNcomment:DiSEqC V1.1*/
    FRONTEND_DISEQC_VER_1_2,    /**< DiSEqC V1.2  *//**<CNcomment:DiSEqC V1.2*/
    FRONTEND_DISEQC_VER_1_X,    /**< DiSEqC V1.x all V1  *//**<CNcomment:DiSEqC V1.x all V1*/

    /* 2.x */
    FRONTEND_DISEQC_VER_2_0,    /**< DiSEqC V2.0  *//**<CNcomment:DiSEqC V1.1*/
    FRONTEND_DISEQC_VER_2_1,    /**< DiSEqC V2.1  *//**<CNcomment:DiSEqC V2.1*/
    FRONTEND_DISEQC_VER_2_2,    /**< DiSEqC V2.2  *//**<CNcomment:DiSEqC V2.2*/
    FRONTEND_DISEQC_VER_2_X,    /**< DiSEqC V2.x all V2  *//**<CNcomment:DiSEqC V2.x all V2*/

    FRONTEND_DISEQC_VER_BUTT
} FRONTEND_DISEQC_VER_E;

/**(Satellite) FRONTEND lnb command type��can use "|" to set more commands *//** CNcomment:LNB������������(����),���ͬʱ�Զ����Ŀ�������ã��ɲ���"��"����.*/
typedef enum _FRONTEND_LNB_CMD_TYPE_E
{
    FRONTEND_LNB_CMD_SET_PWR    = 1,     /**< set Lnb Power  */ /**<CNcomment: ����LNB��Դ����*/
    FRONTEND_LNB_CMD_SET_POL    = 2,     /**< set lnb pol */ /**<CNcomment: ���ü�����ʽ*/
    FRONTEND_LNB_CMD_SET_22K    = 4,     /**< Set lnb 22K  */ /**<CNcomment: ����22K����*/
    FRONTEND_LNB_CMD_SET_12V    = 8,     /**< set lnb 12V  */ /**<CNcomment: ����12V����*/
    FRONTEND_LNB_CMD_SET_DISQ   = 16,    /**< set lnb disqc  */ /**<CNcomment: ����diseqc*/
    FRONTEND_LNB_CMD_BUTT
} FRONTEND_LNB_CMD_TYPE_E;

/** control type for antenna independent control*//** CNcomment:���ߵ����������� */
typedef enum _FRONTEND_ANTENNA_CMD_TYPE_E
{
    //for all antenna
    FRONTEND_EXTRA_ANTENNA_CONFIG_ALL = 0,     /**<Reference:FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S*//**<CNcomment:��ο�FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S*/

    FRONTEND_SET_LNB_POWER,
    FRONTEND_SET_SWITCH_22K,
    //for diseqc switch
    FRONTEND_DISEQC_SWITCH_4PORT,        /**<Reference:FRONTEND_DISEQC_SWITCH4PORT_S*//**<CNcomment:��ο�FRONTEND_DISEQC_SWITCH4PORT_S*/
    FRONTEND_DISEQC_SWITCH_16PORT,       /**<Reference:FRONTEND_DISEQC_SWITCH16PORT_S*//**<CNcomment:��ο�FRONTEND_DISEQC_SWITCH16PORT_S*/

    //for Satellite motor
    FRONTEND_MOTOR_SET_COORDINATE,       /**<Reference:FRONTEND_COORDINATE_S  *//**<CNcomment:��ο�FRONTEND_COORDINATE_S*/
    FRONTEND_MOTOR_STORE_POSITION,       /**<Reference:FRONTEND_MOTOR_POSITION_S*//**<CNcomment:��ο�FRONTEND_MOTOR_POSITION_S*/
    FRONTEND_MOTOR_GOTO_POSITION,        /**<Reference:FRONTEND_MOTOR_POSITION_S*//**<CNcomment:��ο�FRONTEND_MOTOR_POSITION_S*/
    FRONTEND_MOTOR_LIMIT,                /**<Reference:FRONTEND_MOTOR_LIMIT_S*//**<CNcomment:��ο�FRONTEND_MOTOR_LIMIT_S*/
    FRONTEND_MOTOR_MOVE,                 /**<Reference:FRONTEND_MOTOR_MOVE_S*//**<CNcomment:��ο�FRONTEND_MOTOR_MOVE_S*/
    FRONTEND_MOTOR_STOP,                 /**<Reference:FRONTEND_DISEQC_VER_E*//**<CNcomment:��ο�FRONTEND_DISEQC_VER_E*/
    FRONTEND_MOTOR_CALC_ANGULAR,         /**<Reference:FRONTEND_MOTOR_CALC_ANGULAR_S [in/out]*//**<CNcomment:��ο�FRONTEND_MOTOR_CALC_ANGULAR_S [in/out]*/
    FRONTEND_MOTOR_GOTO_ANGULAR,         /**<Reference:FRONTEND_MOTOR_USALS_ANGULAR_S*//**<CNcomment:��ο�FRONTEND_MOTOR_USALS_ANGULAR_S*/
    //FRONTEND_MOTOR_RECALCULATE,        /**<Reference:FRONTEND_DISEQC_RECALCULATE_S*//**<CNcomment:��ο�FRONTEND_DISEQC_RECALCULATE_S*/
    //FRONTEND_MOTOR_RESET,              /**<Reference:FRONTEND_DISEQC_VER_E*//**<CNcomment:��ο�FRONTEND_DISEQC_VER_E*/
    FRONTEND_MOTOR_SET_MANUAL,

    //for unicale lnb
    FRONTEND_UNICABLE_SCAN_USERBANDS,     /**< scan 950~2150 frequency range,and find out the user bands. Can set FRONTEND_REG_UNICABLE_SCAN_CALLBACK get scan status and data *//**<CNcomment:ɨ��950-2150�ҳ��û�Ƶ��, ��������FRONTEND_REG_UNICABLE_SCAN_CALLBACK�ص�������ȡ״̬������*/
    FRONTEND_UNICABLE_EXIT_SCANUSERBANDS, /**< stop scan frequency range, No need param*//**<CNcomment:ֹͣɨ���û�Ƶ��*/
    FRONTEND_UNICABLE_GET_USERBANDSINFO,  /**< Copy scanned results,get user bands information. Data type FRONTEND_UNICABLE_USERBANDS_S*.*//**<CNcomment:��ȡɨ��������ȡ�û�Ƶ����Ϣ��FRONTEND_UNICBALE_USERBANDS_S*.*/
    FRONTEND_ANTENNA_CMD_BUTT
} FRONTEND_ANTENNA_CMD_TYPE_E;

/** motor protocol *//** CNcomment:���Э�� */
typedef enum _FRONTEND_MOTORTYPE_E
{
    FRONTEND_MOTOR_NONE = 0,               /**<None*//**<CNcomment:��ʹ�����*/
    FRONTEND_MOTOR_DISEQC12,               /**<DiSEqC1.2 protocol*//**<CNcomment:DiSEqC1.2Э��*/
    FRONTEND_MOTOR_USLAS,                  /**<USLAS protocol*//**<CNcomment:DiSEqC1.3��USLASЭ��*/
    FRONTEND_MOTOR_BUTT
} FRONTEND_MOTORTYPE_E;

/** DiSEqC motor limit setting*//** CNcomment:DiSEqC��Ｋ������*/
typedef enum _FRONTEND_MOTOR_LIMIT_E
{
    FRONTEND_MOTOR_LIMIT_OFF = 0,          /**<Disable Limits*//**<CNcomment:������*/
    FRONTEND_MOTOR_LIMIT_EAST,             /**<Set East Limit*//**<CNcomment:��������*/
    FRONTEND_MOTOR_LIMIT_WEST,             /**<Set West Limit*//**<CNcomment:��������*/
    FRONTEND_MOTOR_LIMIT_BUTT              /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_MOTOR_LIMIT_E;

/** Difinition of DiSEqC motor move direction*//** CNcomment:DiSEqC����ƶ�����*/
typedef enum _FRONTEND_MOTOR_MOVE_DIR_E
{
    FRONTEND_MOTOR_MOVE_DIR_EAST = 0,      /**<Move east*//**<CNcomment:���ƶ�*/
    FRONTEND_MOTOR_MOVE_DIR_WEST,          /**<Move west*//**<CNcomment:�����ƶ�*/
    FRONTEND_MOTOR_MOVE_DIR_BUTT           /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_MOTOR_MOVE_DIR_E;

/** unicable multi-switch port.*//** CNcomment:unicable���ض˿�ö��*/
typedef enum _FRONTEND_UNICABLE_SATPOSITION_E
{
    FRONTEND_UNICABLE_SATPOSN_A = 0,       /**<unicable switch port A*//**<CNcomment:�˿�A*/
    FRONTEND_UNICABLE_SATPOSN_B,           /**<unicable switch port B*//**<CNcomment:�˿�B*/
    FRONTEND_UNICABLE_SATPOSN_BUT          /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_UNICABLE_SATPOSITION_E;

/////    DVB-S enmu end     ////////////////////////////////////////////

/**(Satellite Ter Cable) FEC *//** CNcomment:ǰ������ʣ�����(���ǡ����桢����).*/
typedef enum _FRONTEND_FEC_RATE_E
{
    FRONTEND_FEC_AUTO = 0,   /**< FEC_AUTO  *//**<CNcomment: FEC_AUTO*/
    FRONTEND_FEC_1_2,        /**< FEC 1/2  *//**<CNcomment: FEC 1/2*/
    FRONTEND_FEC_2_3,        /**< FEC 2/3  *//**<CNcomment: FEC 2/3*/
    FRONTEND_FEC_3_4,        /**< FEC 3/4  *//**<CNcomment: FEC 3/4*/
    FRONTEND_FEC_3_5,        /**< FEC 3/5  *//**<CNcomment: FEC 3/5*/
    FRONTEND_FEC_4_5,        /**< FEC 4/5  *//**<CNcomment: FEC 4/5*/
    FRONTEND_FEC_5_6,        /**< FEC 5/6  *//**<CNcomment: FEC 5/6*/
    FRONTEND_FEC_6_7,        /**< FEC 6/7  *//**<CNcomment: FEC 6/7*/
    FRONTEND_FEC_7_8,        /**< FEC 7/8  *//**<CNcomment: FEC 7/8*/
    FRONTEND_FEC_8_9,        /**< FEC 8/9  *//**<CNcomment: FEC 8/9*/
    FRONTEND_FEC_9_10,       /**< FEC 9/10  *//**<CNcomment: FEC 9/10*/
    FRONTEND_FEC_ANNEX_B,    /**< FEC ANNEX_B  *//**<CNcomment: FEC ANNEX_B*/
    FRONTEND_FEC_1_3,        /**< FEC 1/3  *//**<CNcomment: FEC 1/3*/
    FRONTEND_FEC_1_4,        /**< FEC 1/4  *//**<CNcomment: FEC 1/4*/
    FRONTEND_FEC_2_5,        /**< FEC 2/5  *//**<CNcomment: FEC 2/5*/
    FRONTEND_FEC_BUTT
} FRONTEND_FEC_RATE_E;

/**MODULATION *//** CNcomment:���Ʒ�ʽ.*/
typedef enum _FRONTEND_MODULATION_E
{
    FRONTEND_MOD_AUTO = 0,   /**<AUTO*//**<CNcomment:AUTO*/
    FRONTEND_MOD_QAM16,      /**<QAM16*//**<CNcomment:QAM16*/
    FRONTEND_MOD_QAM32,      /**<QAM32*//**<CNcomment:QAM32*/
    FRONTEND_MOD_QAM64,      /**<QAM64*//**<CNcomment:QAM64*/
    FRONTEND_MOD_QAM128,     /**<QAM128*//**<CNcomment:QAM128*/
    FRONTEND_MOD_QAM256,     /**<QAM256*//**<CNcomment:QAM256*/
    FRONTEND_MOD_QPSK,       /**<QPSK*//**<CNcomment:QPSK*/
    FRONTEND_MOD_8PSK,       /**<8PSK*//**<CNcomment:8PSK*/
    FRONTEND_MOD_BPSK,       /**<BPSK*//**<CNcomment:BPSK*/
    FRONTEND_MOD_DVBT,       /**< DVBT*//**<CNcomment:DVBT*/
    FRONTEND_MOD_DVBT2,      /**<DVBT2*//**<CNcomment:DVBT2*/
    FRONTEND_MOD_ISDBT,      /**<ISDBT*//**<CNcomment:ISDBT*/
    FRONTEND_MOD_QAM1024,    /**<QAM1024*//**<CNcomment:QAM1024*/
    FRONTEND_MOD_QAM4096,    /**<QAM4096*//**<CNcomment:QAM4096*/
    FRONTEND_MOD_16APSK,     /**<16APSK*//**<CNcomment:16APSK*/
    FRONTEND_MOD_32APSK,     /**<32APSK*//**<CNcomment:32APSK*/
    FRONTEND_MOD_8VSB,       /**<8VSB*//**<CNcomment:8VSB*/
    FRONTEND_MOD_16VSB,      /**<16VSB*//**<CNcomment:16VSB*/
    FRONTEND_MOD_BUTT
} FRONTEND_MODULATION_E;

/**FRONTEND SPECTRUM (Cable TER)*//** CNcomment:Ƶ�׷�ת����(����,����).*/
typedef enum _FRONTEND_SPECTRUM_E
{
    FRONTEND_SPECTRUM_INVERSION_OFF  = 1,       /**<off*//**<CNcomment:off*/
    FRONTEND_SPECTRUM_INVERSION      = 2,       /**<on*//**<CNcomment:on*/
    FRONTEND_SPECTRUM_INVERSION_AUTO = 4,       /**<AUTO*//**<CNcomment:AUTO*/
    FRONTEND_SPECTRUM_INVERSION_UNK  = 8,       /**<UNK*//**<CNcomment:UNK*/
    FRONTEND_SPECTRUM_INVERSION_BUTT
} FRONTEND_SPECTRUM_E;

/**FRONTEND band width (Cable TER)*//** CNcomment:�������(���桢����).*/
typedef enum _FRONTEND_BAND_WIDTH_E
{
    FRONTEND_BANDWIDTH_8_MHZ = 0,        /**<BANDWIDTH_8_MHZ*//**<CNcomment:BANDWIDTH_8_MHZ*/
    FRONTEND_BANDWIDTH_7_MHZ,            /**<BANDWIDTH_7_MHZ*//**<CNcomment:BANDWIDTH_7_MHZ*/
    FRONTEND_BANDWIDTH_6_MHZ,            /**<BANDWIDTH_6_MHZ*//**<CNcomment:BANDWIDTH_6_MHZ*/
    FRONTEND_BANDWIDTH_BUTT
} FRONTEND_BAND_WIDTH_E;

/**FRONTEND transmit mod (TER)*//** CNcomment:����ģʽ(����).*/
typedef enum _FRONTEND_TRANSMIT_MOD_E
{
    FRONTEND_TRANS_MOD_1K = 0,    /**<MOD_1K*//**<CNcomment:MOD_1K*/
    FRONTEND_TRANS_MOD_2K = 1,    /**<MOD_2K*//**<CNcomment:MOD_2K*/
    FRONTEND_TRANS_MOD_4K,        /**<MOD_4K*//**<CNcomment:MOD_4K*/
    FRONTEND_TRANS_MOD_8K,        /**<MOD_8K*//**<CNcomment:MOD_8K*/
    FRONTEND_TRANS_MOD_16K,       /**<MOD_16K*//**<CNcomment:MOD_16K*/
    FRONTEND_TRANS_MOD_32K,       /**<MOD_32K*//**<CNcomment:MOD_32K*/
    FRONTEND_TRANS_MOD_AUTO,      /**<MOD_AUTO*//**<CNcomment:MOD_AUTO*/
    FRONTEND_TRANS_MOD_BUTT
} FRONTEND_TRANSMIT_MOD_E;

/**FRONTEND guard interval (TER, C2)*//** CNcomment:�������(����,C2).*/
typedef enum _FRONTEND_GUARD_INTERVAL_E
{
    FRONTEND_GUARDINTERVAL_1_128 = 0,  /**<GUARDINTERVAL 1/128*//**<CNcomment:GUARDINTERVAL 1/128*/
    FRONTEND_GUARDINTERVAL_1_64,       /**<GUARDINTERVAL 1/64*//**<CNcomment:GUARDINTERVAL 1/64*/
    FRONTEND_GUARDINTERVAL_1_32,       /**<GUARDINTERVAL 1/32*//**<CNcomment:GUARDINTERVAL 1/32*/
    FRONTEND_GUARDINTERVAL_1_16,       /**<GUARDINTERVAL 1/16*//**<CNcomment:GUARDINTERVAL 1/16*/
    FRONTEND_GUARDINTERVAL_19_256,     /**<GUARDINTERVAL 19/256*//**<CNcomment:GUARDINTERVAL 19/256*/
    FRONTEND_GUARDINTERVAL_1_8,        /**<GUARDINTERVAL 1/8*//**<CNcomment:GUARDINTERVAL_1/8*/
    FRONTEND_GUARDINTERVAL_19_128,     /**<GUARDINTERVAL 19/128*//**<CNcomment:GUARDINTERVAL 19/128*/
    FRONTEND_GUARDINTERVAL_1_4,        /**<GUARDINTERVAL 1/4*//**<CNcomment:GUARDINTERVAL 1/4*/
    FRONTEND_GUARDINTERVAL_AUTO,       /**<GUARDINTERVAL auto*//**<CNcomment:GUARDINTERVAL auto*/
    FRONTEND_GUARDINTERVAL_BUTT
} FRONTEND_GUARD_INTERVAL_E;

/** TS Priority, only used in DVB-T*/
/** CNcomment:������DVB-T*/
typedef enum _FRONTEND_TER_TS_PRIORITY_E
{
    FRONTEND_TER_TS_PRIORITY_NONE = 0,      /**<no priority mode*/          /**<CNcomment:�����ȼ�ģʽ*/
    FRONTEND_TER_TS_PRIORITY_HP,            /**<high priority mode*/        /**<CNcomment:�����ȼ�ģʽ*/
    FRONTEND_TER_TS_PRIORITY_LP,            /**<low priority mode*/         /**<CNcomment:�����ȼ�ģʽ*/
    FRONTEND_TER_TS_PRIORITY_BUTT           /**<Invalid value*/             /**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_TER_TS_PRIORITY_E;

/** base channel or lite channel, only used in DVB-T2*/
/** CNcomment:������DVB-T2*/
typedef enum _FRONTEND_TER2_MODE_E
{
    FRONTEND_TER2_MODE_BASE = 0,     /**< the channel is base mode*/         /**<CNcomment:ͨ���н�֧��base�ź�*/
    FRONTEND_TER2_MODE_LITE,         /**< the channel is lite mode*/         /**<CNcomment:ͨ������Ҫ֧��lite�ź�*/
    FRONTEND_TER2_MODE_BUTT      /**<Invalid value*/            /**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_TER2_MODE_E;

/** PLP type of DVB-T2.*//** CNcomment:T2�������ܵ�����*/
typedef enum _FRONTEND_TER2_PLP_TYPE_E
{
    FRONTEND_TER2_PLP_TYPE_COM = 0,       /**<common type*//**<CNcomment:��ͨ*/
    FRONTEND_TER2_PLP_TYPE_DAT1,          /**<data1 type*//**<CNcomment:����1*/
    FRONTEND_TER2_PLP_TYPE_DAT2,          /**<data2 type*//**<CNcomment:����2*/
    FRONTEND_TER2_PLP_TYPE_BUTT           /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_TER2_PLP_TYPE_E;

/**FRONTEND callback status (TER, C2)*//** CNcomment:���ûص�����״̬.*/
typedef enum _FRONTEND_CFG_CALLBACK_E
{
    FRONTEND_CALLBACK_ENABLE = 0,         /**< enable*//**<CNcomment: ����*/
    FRONTEND_CALLBACK_DISABLE,            /**< disable*//**<CNcomment: ʧЧ*/
    FRONTEND_CALLBACK_REMOVE              /**< remove*//**<CNcomment: �Ƴ�*/
} FRONTEND_CFG_CALLBACK_E;

/**FRONTEND open params*//** CNcomment:�豸��������.*/
typedef struct _FRONTEND_OPEN_PARAMS_S
{
    U32 u32FrontendIndex;                 /**< witch tuner to open*//**<CNcomment: ����һ��tuner��������ͬ����tunerʱ��Ҫָ������һ��*/
    FRONTEND_FE_TYPE_E   enFeType;        /**< init tuner this type*//**<CNcomment: ��ʼ��tunerΪ������*/
    FRONTEND_FEC_RATE_E  enFecRate;       /**< Fec Rate*//**<CNcomment: Fec Rate*/
} FRONTEND_OPEN_PARAMS_S;

/** FRONTEND LNB Power status *//** CNcomment:LNB����״̬. */
typedef enum _FRONTEND_LNB_PWR_STATUS_E
{
    FRONTEND_LNB_PWR_STATUS_ON = 0,                 /**< Normal on*//**<CNcomment: �򿪵�����״̬*/
    FRONTEND_LNB_PWR_STATUS_OFF,                    /**< Power off*//**<CNcomment: �رյ�����״̬*/
    FRONTEND_LNB_PWR_STATUS_SHORT_CIRCUIT,          /**< Short circuit *//**<CNcomment: LNB�����·����·*/
    FRONTEND_LNB_PWR_STATUS_OVER_TEMPERATURE,       /**< Over termperature  *//**<CNcomment:LNB���ģ���¶�̫��*/
    FRONTEND_LNB_PWR_STATUS_LOW_VOLTAGE,            /**< Low voltage *//**<CNcomment: LNB�����ѹ̫��*/
    FRONTEND_LNB_PWR_STATUS_OVER_VOLTAGE,           /**< Over voltage *//**<CNcomment:  LNB�����ѹ̫��*/
    FRONTEND_LNB_PWR_STATUS_BUTT
} FRONTEND_LNB_PWR_STATUS_E;

/** FRONTEND Control ts out cmd *//** CNcomment:�����������������. */
typedef enum _FRONTEND_TSOUT_CMD_TYPE_E
{
    //for T2
    FRONTEND_TSOUT_TER2_GET_PLPNUM = 0,             /**< Get the PLP number, data type U8*//**<CNcomment:�õ�PLP����Ŀ,����U8*/
    FRONTEND_TSOUT_TER2_GET_PLP_TYPE,               /**< Get PLP type, Reference:FRONTEND_TER2_PLP_TYPE_E*//**<CNcomment:�õ�PLP������,FRONTEND_TER2_PLP_TYPE_E*/
    FRONTEND_TSOUT_TER2_GET_PLP_GROUPID,            /**< PLP group ID, data type U8*//**<CNcomment:�õ�PLP group ID,����U8*/
    FRONTEND_TSOUT_TER2_SET_PLP_MODE,               /**< Sets PLP read or write mode, data type U8*, 1-read, 0-write. *//**<CNcomment:���������ܵ���дģʽ������U8* 1-��ģʽ��0-�л�ģʽ��*/
    FRONTEND_TSOUT_TER2_SET_PLPID,                  /**< PLP ID, data type U8*//**<CNcomment:����PLPID,����U8*/
    FRONTEND_TSOUT_TER2_SET_COMMON_PLPID,           /**< Sets common plp id, data type U8* plp id. *//**<CNcomment:���ù��������ܵ�ID������U8* */
    FRONTEND_TSOUT_TER2_SET_COMPLP_COMB,            /**< Sets common plp and data plp combination flag, data type U8*, 1-combinate, 0-no need. *//**<CNcomment:���ù��������ܵ������������ܵ��Ƿ���Ҫ��ϱ�־������U8* 1-��ϣ�0-����ϡ�*/

    //for S2 mutiple Transport Streams
    FRONTEND_TSOUT_SAT2_GET_ISINUM,                 /**< Get the streams number, data type U8*//**<CNcomment:�õ�PLP����Ŀ,����U8*/
    FRONTEND_TSOUT_SAT2_GET_ISIID,                  /**< Get ISI ID, data type FRONTEND_SAT2_ISIID_S* *//**<CNcomment:����FRONTEND_SAT2_ISIID_S* */
    FRONTEND_TSOUT_SAT2_SET_ISIID,                  /**< Set ISI ID, data type U8*//**<CNcomment:����PLPID,����U8*/

    //For ISDB-T
    FRONTEND_TSOUT_ISDBT_GET_TMCC_INFO,             /**< Get TMCC infomation about ISDB-T signal, date type FRONTEND_ISDBT_TMCC_INFO_S *//**<CNcomment:��ȡISDB-T�źŵ�TMCC��Ϣ,��������FRONTEND_ISDBT_TMCC_INFO_S*/

    FRONTEND_TSOUT_CMD_END
} FRONTEND_TSOUT_CMD_TYPE_E;

/** Parameter for ISDB-T TMCC information*/
/** CNcomment:ISDB-Tģʽ�£�TMCC ��Ϣ*/
typedef struct _FRONTEND_ISDBT_TMCC_INFO_S
{
    U8 u8EmergencyFlag;      /**<the start flag for emergency alarm broadcasting*//**<CNcomment:��������������ʼ��־*/
    U8 u8PartialFlag;        /**<partial reception flag*//**<CNcomment:���ֽ��ձ�־*/
    U8 u8PhaseShiftCorr;     /**<phase shift correction value for connected segment transmission*//**<CNcomment:��λƫ��ֵ*/
    U8 u8IsdbtSystemId;      /**<system identification[0 = ISDB_T,1 = ISDB_T_SB]*//**<CNcomment:ϵͳ��ʶ*/
} FRONTEND_ISDBT_TMCC_INFO_S;

/** Parameter for DiSEqC 1.0/2.0 switch
   Some DiSEqC device need set polarization(13/18V) and 22K, you can set them here. */
/** CNcomment:DiSEqC 1.0/2.0 ���ز���
   ��ЩDiSEqC�豸��Ҫ���ü�����ʽ��22K�ģ�������������豸����Ҫ���������� */
typedef struct _FRONTEND_DISEQC_SWITCH4PORT_S
{
    FRONTEND_DISEQC_VER_E            enLevel;       /**<DiSEqC device level*//**<CNcomment:�����汾*/
    FRONTEND_DISEQC_SWITCH_PORT_E    enPort;        /**<DiSEqC switch port*//**<CNcomment:ѡͨ�˿ں�*/
    FRONTEND_POLARIZATION_E          enPolar;       /**<Polarization type *//**<CNcomment:������ʽ*/
    FRONTEND_LNB_22K_E               enLNB22K;      /**<22K status*//**<CNcomment:22k״̬*/
} FRONTEND_DISEQC_SWITCH4PORT_S;

/** Parameter for DiSEqC 1.1/2.1 switch *//** CNcomment:DiSEqC 1.1/2.1 ���ز��� */
typedef struct _FRONTEND_DISEQC_SWITCH16PORT_S
{
    FRONTEND_DISEQC_VER_E             enLevel;      /**<DiSEqC device level*//**<CNcomment:�����汾*/
    FRONTEND_DISEQC_SWITCH_PORT_E     enPort;       /**<DiSEqC switch port*//**<CNcomment:ѡͨ�˿ں�*/
} FRONTEND_DISEQC_SWITCH16PORT_S;

/** coordinate *//** CNcomment:���ؾ�γ�� */
typedef struct _FRONTEND_COORDINATE_S
{
    U16  u16MyLongitude;                  /**<local longitude, is 10*longitude, in param, E:0-1800, W:1800-3600(3600-longtitude) *//**<CNcomment:���ؾ���*/
    U16  u16MyLatitude;                   /**<local latitude, is 10*latitude, in param N:0-900, S:900-1800(1800-latitude)*//**<CNcomment:����γ��*/
} FRONTEND_COORDINATE_S;

/** Parameter for DiSEqC motor store position*//** CNcomment:���ߴ洢λ�ò���*/
typedef struct _FRONTEND_MOTOR_POSITION_S
{
    FRONTEND_DISEQC_VER_E enLevel;        /**<DiSEqC device level*//**<CNcomment:�����汾*/
    U32                   u32Pos;         /**<Index of position, 0-255*//**<CNcomment:λ�����*/
} FRONTEND_MOTOR_POSITION_S;

/** Parameter for DiSEqC motor limit setting*//** CNcomment:����Limit���ò���*/
typedef struct _FRONTEND_MOTOR_LIMIT_S
{
    FRONTEND_DISEQC_VER_E enLevel;        /**<DiSEqC device level*//**<CNcomment:�����汾*/
    FRONTEND_MOTOR_LIMIT_E enLimit;       /**<Limit setting*//**<CNcomment:�����趨*/
} FRONTEND_MOTOR_LIMIT_S;

/** Parameter for DiSEqC motor moving*//** CNcomment:DiSEqC����ƶ�����*/
typedef struct _FRONTEND_MOTOR_MOVE_S
{
    FRONTEND_DISEQC_VER_E      enLevel;   /**<DiSEqC device level*//**<CNcomment:�����汾*/
    FRONTEND_MOTOR_MOVE_DIR_E  enDir;     /**<Moving direction*//**<CNcomment:�ƶ�����*/
    U32                        u32RunningSteps;    /**<0 mean running continus;1~128 mean running steps every time.*//**<CNcomment:0��ʾ����ת����1~128֮���ʾÿ��ת��step����*/
} FRONTEND_MOTOR_MOVE_S;

/** calculate angular *//** CNcomment:����Ƕ� */
typedef struct _FRONTEND_MOTOR_CALC_ANGULAR_S
{
    U16 u16SatLongitude;                  /**<sat longitude, is 10*longitude, in param, E:0-1800, W:1800-3600(3600-longtitude)  *//**<CNcomment:�������ھ���*/
    U16 u16Angular;                       /**<calculate result, out param, if the result is larger than 850, return FAILURE according to the device limitation*//**<CNcomment:�����õ��ĽǶ�*/
} FRONTEND_MOTOR_CALC_ANGULAR_S;

/** Parameter for USALS goto angular*//** CNcomment:USALS�ǶȲ���*/
typedef struct _FRONTEND_MOTOR_USALS_ANGULAR_S
{
    FRONTEND_DISEQC_VER_E  enLevel;       /**<DiSEqC device level*//**<CNcomment:�����汾*/
    U32                    u32Angular;    /**<Angular, calculated by FRONTEND_MOTOR_CALC_ANGULAR cmd*//**<CNcomment:�Ƕ�ֵ����ͨ������FRONTEND_MOTOR_CALC_ANGULAR �������SDK����õ�*/
} FRONTEND_MOTOR_USALS_ANGULAR_S;

/** LNB configurating parameters*//** CNcomment:LNB���ò���*/
typedef struct _FRONTEND_SAT_LNB_CONFIG_S
{
    FRONTEND_LNB_TYPE_E  enLNBType;                   /**<LNB type*//**<CNcomment:LNB����*/
    U32                  u32LowLO;                    /**< Low Local Oscillator Frequency, MHz *//**<CNcomment:LNB�ͱ���Ƶ�ʣ���λMHz*/
    U32                  u32HighLO;                   /**< High Local Oscillator Frequency, MHz*//**<CNcomment:LNB�߱���Ƶ�ʣ���λMHz*/
    FRONTEND_LNB_BAND_E  enLNBBand;                   /**< LNB band, C or Ku *//**<CNcomment:LNB���Σ�C��Ku*/
    U32                  u32UNIC_SCRNO;               /**< SCR number, 0-7 *//**<CNcomment:SCR��ţ�ȡֵΪ0-7*/
    U32                  u32UNICIFFreqMHz;            /**< SCR IF frequency, unit MHz *//**<CNcomment:SCR��ƵƵ�ʣ� ��λMHz*/
    FRONTEND_UNICABLE_SATPOSITION_E enSatPosn;        /**< unicable multi-switch port *//**<CNcomment:unicable���ض˿ں�*/
} FRONTEND_SAT_LNB_CONFIG_S;

/** satellite antenna parameter *//** CNcomment:�������߲��� */
typedef struct _FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S
{
    FRONTEND_SWITCH_22K_E         enSwitch22K;        /**<22k switch */ /**<CNcomment:22k����  FRONTEND_SWITCH_22K_E*/
    FRONTEND_SWITCH_TONEBURST_E   enToneburst;        /**<Switch of Tone burst : Reference: FRONTEND_SWITCH_TONEBURST_E. */ /**CNcomment:Tone burst���ء��ο� FRONTEND_SWITCH_TONEBURST_E*/
    FRONTEND_SWITCH_0_12V_E       enSwitch12V;        /**<Switch of 12V Reference: FRONTEND_SWITCH_0_12V_E*//**CNcomment:12V���أ�һ�㲻�á� �ο�FRONTEND_SWITCH_0_12V_E  */
    FRONTEND_DISEQC_VER_E         enDiSEqCLevel;      /**<DiSEqC device level*/            /**<CNcomment:�����汾*/
    FRONTEND_DISEQC_SWITCH_PORT_E enPort4;            /**<1~4 switch Reference: FRONTEND_DISEQC_SWITCH_PORT_E For DISEQC_SWITCH4PORT, diseqc1.0 *//**<CNcomment:����һ����,�ο�FRONTEND_DISEQC_SWITCH_PORT_E*/
    FRONTEND_DISEQC_SWITCH_PORT_E enPort16;           /**<1~16 switch Reference: FRONTEND_DISEQC_SWITCH_PORT_E For DISEQC_SWITCH16PORT, diseqc1.1*//**<CNcomment:ʮ����һ����,�ο�FRONTEND_DISEQC_SWITCH_PORT_E*/
    FRONTEND_MOTORTYPE_E          enMotorType;        /**<Reference FRONTEND_MOTORTYPE_E*/ /**CNcomment:�ο�FRONTEND_MOTORTYPE_E */
    U32                           u32Longitude;       /**<Longitude */ /**<CNcomment:�������ھ���*/
    U32                           u32MotoPos;         /**<Motor position*/ /**CNcomment:  ���λ�ñ��,����256�����λ�ã����������Ӳ���洢����*/
} FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S;

typedef struct _FRONTEND_UNICABLE_SCR_UB_S   //for unicable
{
    U32      u32SCRNo;                                /**<user band number of unicable*//**<CNcomment:unicable���û�Ƶ�κ�*/
    S32      s32CenterFreq;                           /**<user band frequency of unicable,unit MHz*//**<CNcomment:unicable���û�Ƶ������Ƶ��,��λMHz*/
} FRONTEND_UNICABLE_SCR_UB_S;

/** for unicable getting parameter *//** CNcomment:unicable LNB ɨ����Ϣ��ȡ�����ݽṹ */
typedef struct _FRONTEND_UNICABLE_USERBANDS_S
{
    FRONTEND_UNICABLE_SCR_UB_S**  ppUserBandsinfo;    /**<point to array which type is FRONTEND_UNICABLE_SCR_UB_S*//**<CNcomment:unicable�û�Ƶ�δ洢�����ָ��*/
    U32*                          pu32Num;            /**<size of the array *//**<CNcomment:������Ĵ�С*/
} FRONTEND_UNICABLE_USERBANDS_S;

/** for S2 FRONTEND_TSOUT_SAT2_GET_ISIID parameter *//** CNcomment:FRONTEND_TSOUT_SAT2_GET_ISIID ��ȡISIID ����  */
typedef struct _FRONTEND_SAT2_ISIID_S
{
    U8 u8StreamNum;      /**<input parameter, streamNum*/
    U8 u8IsiID;          /**<output parameter, Get streamNumID according to StreamNum*/
} FRONTEND_SAT2_ISIID_S;

/** FRONTEND LNB ctrl info *//** CNcomment:LNB���Ʋ���.*/
typedef struct _FRONTEND_SAT_LNB_INFO_S
{
    FRONTEND_LNB_CMD_TYPE_E   enCmdType;              /**< cmd type *//**<CNcomment: ��������*/
    FRONTEND_LNB_POWER_E      enLnbPower;             /**< lnb power*//**<CNcomment: lnb �Ĺ���״̬*/
    FRONTEND_POLARIZATION_E   enPolarization;         /**< polarization*//**<CNcomment: ����*/
    FRONTEND_LNB_12V_E        enLnb12vState;          /**< lnb 12v state*//**<CNcomment: 12V����״̬*/
    FRONTEND_LNB_22K_E        enLnb22kState;          /**< lnb 22k state*//**<CNcomment: 22k ״̬*/
    FRONTEND_LNB_DISEQC_CMD_E enDiseqcCmd;            /**< diseqc cmd*//**<CNcomment: DiSEqC ״̬*/
    BOOL                      bDiseqcNeedResponse;    /**< need response */ /**<CNcomment: �Ƿ���Ҫdiseqc��Ӧ(diseqc2.x).TRUE:response;FALSE:not response*/
    U32                       u32DiseqcDataLen;       /**< TRUE must set this lenth *//**<CNcomment: diseqc�������ݳ���bytes.���is_diseqc_response=TRUE,����diseqc��,�洢��Ӧdiseqc�ĳ���*/
    U8*                       pDiseqcData;            /**< data for response *//**<CNcomment: diseqc��������.���is_diseqc_response=TRUE,����diseqc��, �洢��Ӧ����,��ʱ��������С>=6bytes*/
} FRONTEND_SAT_LNB_INFO_S;

/** Definition of blind scan event type*/
/** CNcomment:TUNERäɨ�¼�*/
typedef enum _FRONTEND_SAT_BLINDSCAN_EVT_E
{
    FRONTEND_SAT_BLINDSCAN_EVT_STATUS = 0,            /**<New status*//**<CNcomment:״̬�仯*/
    FRONTEND_SAT_BLINDSCAN_EVT_PROGRESS,              /**<New Porgress *//**<CNcomment:���ȱ仯*/
    FRONTEND_SAT_BLINDSCAN_EVT_NEWRESULT,             /**<Find new channel*//**<CNcomment:��Ƶ��*/
    FRONTEND_SAT_BLINDSCAN_EVT_BUTT                   /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_SAT_BLINDSCAN_EVT_E;

/** Satellite TP Info of blindscan result *//**CNcomment: ����äɨ���*/
typedef struct _FRONTEND_SAT_BLINDSCAN_TP_INFO_S
{
    //U32 u32IfFreq;                                  /**<If freq *//**<CNcomment: ��ƵƵ��,��Ҫ�ͱ�������õ�TP Ƶ��,��λKHz */
    U32                      u32Freq;                 /**<freq *//**<CNcomment: Ƶ��,TP Ƶ��,��λKHz */
    U32                      u32Sym;                  /**<sumbole rate *//**<CNcomment: ������,��λKbps*/
    FRONTEND_MODULATION_E    enModulation;            /**<Modulation *//**<CNcomment: ����ģʽ,8PSK,QPSK�ȣ���ӦDVB-S1,S2 */
    FRONTEND_POLARIZATION_E  enPolar;                 /**<Polarization type*//**<CNcomment:������ʽ*/
    FRONTEND_IQ_IVT_E        enIQInt;                 /**<IQ *//**<CNcomment: IQģʽ */
} FRONTEND_SAT_BLINDSCAN_TP_INFO_S;

/** Satellite TP Info of blindscan result *//**CNcomment: ����äɨ���*/
typedef struct _FRONTEND_SAT_BLINDSCAN_DATA_S
{
    U32                                u32CenterFreq; /**<current center freq, use for calc percent*//**<CNcomment: ��ǰäɨ������Ƶ��(MHz),����App ����äɨ����*/
    U32                                u32TpCnt;      /**<TP count get by blindscan *//**<CNcomment: ��ǰƵ����������TP ����, 0 ��ʾδ������,������Ϣ��:p_tp_info ����*/
    FRONTEND_SAT_BLINDSCAN_TP_INFO_S*  pTpInfo;       /**<TP info get by blindscan *//**<CNcomment: ָ��TP(transponder)  ��Ϣ����.�����Ԫ�ظ�����:tp_cnt*/
} FRONTEND_SAT_BLINDSCAN_DATA_S;

/** Notify structure of tuner blind scan */
/** CNcomment:TUNERäɨ֪ͨ��Ϣ*/
typedef union _FRONTEND_SAT_BLINDSCAN_NOTIFY_U
{
    FRONTEND_FE_STATUS_E*              penStatus;             /**<Scanning status*//**<CNcomment:äɨ״̬*/
    U16*                               pu16ProgressPercent;   /**<Scanning progress*//**<CNcomment:äɨ����*/
    FRONTEND_SAT_BLINDSCAN_TP_INFO_S*  pstResult;             /**<Scanning result*//**<CNcomment:äɨ���*/
} FRONTEND_SAT_BLINDSCAN_NOTIFY_U;

/** Parameter of the satellite tuner blind scan */
/** CNcomment:����TUNERäɨ����*/
typedef struct _FRONTEND_SAT_BLINDSCAN_PARA_S
{
    /**<LNB Polarization type, only take effect in manual blind scan mode*/
    /**<CNcomment:LNB������ʽ���Զ�ɨ��ģʽ������Ч*/
    FRONTEND_POLARIZATION_E enPolar;

    /**<LNB 22K signal status, for Ku band LNB which has dual LO, 22K ON will select high LO and 22K off select low LO,
        only take effect in manual blind scan mode*/
    /**<CNcomment:LNB 22K״̬������Ku����˫����LNB��ONѡ��߱���OFFѡ��ͱ����Զ�ɨ��ģʽ������Ч*/
    FRONTEND_LNB_22K_E      enLNB22K;

    /**<Blind scan start IF, in kHz, only take effect in manual blind scan mode */
    /**<CNcomment:äɨ��ʼƵ��(��Ƶ)����λ��kHz���Զ�ɨ��ģʽ������Ч*/
    U32                     u32StartFreq;

    /**<Blind scan stop IF, in kHz, only take effect in manual blind scan mode */
    /**<CNcomment:äɨ����Ƶ��(��Ƶ)����λ��kHz���Զ�ɨ��ģʽ������Ч*/
    U32                     u32StopFreq;

    /**<The execution of the blind scan may change the 13/18V or 22K status.
        If you use any DiSEqC device which need send command when 13/18V or 22K status change,
        you should registe a callback here. Otherwise, you can set NULL here.*/
    /**<CNcomment:äɨ���̿��ܻ��л�������ʽ��22K�����������ĳЩDiSEqC�豸��Ҫ����13/18V��22K�ģ�
        ��ע������ص������û���ã���ɴ�NULL */
    VOID (*pfnDISEQCSet)(const HANDLE hFrontend, const FRONTEND_POLARIZATION_E enPolar,
                         const FRONTEND_LNB_22K_E enLNB22K);

    /**<Callback when scan status change, scan progress change or find new channel.*/
    /**<CNcomment:ɨ��״̬����Ȱٷֱȷ����仯ʱ�������µ�Ƶ��ʱ�ص�*/
    VOID (*pfnEVTNotify)(const HANDLE hFrontend, const FRONTEND_SAT_BLINDSCAN_EVT_E enEVT,
                         const FRONTEND_SAT_BLINDSCAN_NOTIFY_U* punNotify);
} FRONTEND_SAT_BLINDSCAN_PARA_S;

/** FRONTEND Sat scan(lock or blindscan) ctrl info*//** CNcomment:�����ź�����(��Ƶ����äɨ)����.*/
typedef struct _FRONTEND_SAT_SCAN_INFO_S
{
    U32                     u32Freq;             /**< freq KHz *//**<CNcomment: ����Ƶ��,��λKHz*/
    U32                     u32Sym;              /**< symbole rate *//**<CNcomment: ������,��λKSyms/s*/
    FRONTEND_POLARIZATION_E enPolar;             /**<Polarization type*//**<CNcomment:������ʽ*/
    U32                     u32ScrambleValue;    /**<initial scrambling code,range 0~262141,when value is not 0,signal is special,
                                                     and the value must be telled by signal owner.default 0 must be configed when TP signal is not special*/
    /**<CNcomment:����������ʼֵ����Χ0~262141����ֵΪ��0ʱ���������źţ���ֵֻ�����źŷ��ͷ���֪����Ƶ�㲻�������ź�ʱ����ֵ��������ΪĬ��ֵ0*/

    FRONTEND_MODULATION_E   enModulation;        /**< modulation *//**<CNcomment: ����ģʽ,8PSK,QPSK�ȣ���ӦDVB-S1,S2*/
    U32                     u32StopFreq;         /**< stop freq just for blindscan *//**<CNcomment: ɨƵ��ֹƵ��,��äɨģʽ��Ч(MHz). ���С��freq_mhz ʱ,HDI ������.*/
    FRONTEND_ROLLOFF_E      enRolloff;           /**< rolloff *//**<CNcomment: ��������ѡ��*/
    FRONTEND_IQ_IVT_E       enIQInt;             /**< iq mod *//**<CNcomment: IQģʽ*/
    FRONTEND_FEC_RATE_E     enFecRate;           /**< fec rate *//**<CNcomment: FEC��һ����̨ʱ����Ҫ�����*/
    U8                      u8ChannelIndex;                   /**< ISI index, first lock use 0, after locked can get from funtion *<CNcomment: DVB-S2.channel_index��ISI������[1,max],�տ�ʼ����ʱ,ʹ��0,������Դӽӿڻ�ȡ. S2ֻ��һ��PLP(physical layer pipe),���ܶ��ISI(input stream identifier).*/

    U32                     u32SymOffset;        /**< sym offset *//**<CNcomment: ������ƫ��*/
    U32                     u32FreqOffset;       /**< freq offset *//**<CNcomment: ����Ƶ��ƫ��*/

    FRONTEND_SEARCH_MODE_E  enSearchMod;         /**< search mod lock one freq or blindsacn *//**<CNcomment: ����ģʽ äɨ֮��*/

    FRONTEND_SAT_BLINDSCAN_PARA_S* pstBindScanParam;

    FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstExAntenna;   /**< if pstExAntenna not null, will set antenna first, then scan freq *//**<CNcomment: ������������߲����������������߲���������Ƶ*/
} FRONTEND_SAT_SCAN_INFO_S;

/** FRONTEND cable scan(lock) ctrl info*//** CNcomment:�����ź�����(��Ƶ)����.*/
typedef struct _FRONTEND_CAB_SCAN_INFO_S
{
    U32 u32Freq;                               /**< freq  KHz*//**<CNcomment: ����Ƶ��(KHz)*/
    U32 u32Sym;                                /**< symbol rate *//**<CNcomment: ������(Syms/s)*/
    FRONTEND_MODULATION_E     enModulation;    /**< qam *//**<CNcomment: ���Ʒ�ʽ*/
    FRONTEND_SPECTRUM_E       enSpectrum;      /**< spectrum *//**<CNcomment: Ƶ�׼���*/
    FRONTEND_BAND_WIDTH_E     enBandWidth;     /**< band_width *//**<CNcomment: ����*/
    FRONTEND_GUARD_INTERVAL_E enGuardInterval; /**< guard_interval *//**<CNcomment: DVB-C2*/
    U8  u8ChannelIndex;                        /**< ISI index, first lock use 0, after locked can get from funtion *//**<CNcomment: DVB-C2.channel_index��ISI������[1,max],�տ�ʼ����ʱ,ʹ��0,������Դӽӿڻ�ȡ. C2�����ж��PLP(physical layer pipe),ÿ��PLPֻ��һ��ISI(input stream identifier).*/
} FRONTEND_CAB_SCAN_INFO_S;

/** FRONTEND Ter scan(lock) ctrl info*//** CNcomment:�����ź�����(��Ƶ)����.*/
typedef struct _FRONTEND_TER_SCAN_INFO_S
{
    U32 u32Freq;                                /**< freq  KHz*//**<CNcomment: ����Ƶ��(KHz)*/
    FRONTEND_BAND_WIDTH_E      enBandWidth;      /**< BandWidth*//**<CNcomment: ����*/
    FRONTEND_MODULATION_E      enModulation;     /**< Modulation*//**<CNcomment: ģʽ*/
    FRONTEND_SPECTRUM_E        enSpectrum;       /**< spectrum *//**<CNcomment: Ƶ�׼���*/
    FRONTEND_FEC_RATE_E        enCoderate;       /**< Coderate*//**<CNcomment: Coderate*/
    FRONTEND_GUARD_INTERVAL_E  enGuardInterval;  /**< GuardInterval*//**<CNcomment: ���*/
    FRONTEND_TRANSMIT_MOD_E    enTransmitMod;    /**< TransmitMod*//**<CNcomment: TransmitMod*/
    FRONTEND_TER2_MODE_E       enTer2ChannelMode; /**< T2 base mode ,lite mode *//**<CNcomment: Baseģʽ*/
    FRONTEND_TER_TS_PRIORITY_E enTerTsPriority;  /**< T Priority of TS *//**<CNcomment: TS�����ȼ�ģʽ*/
    U8  u8ChannelIndex;                         /**< PLP index, first lock use 0, after locked can get from funtion *//**<CNcomment: DVB-T2.channel_index��PLP������[1,max],�տ�ʼ����ʱ,ʹ��0,������Դӽӿڻ�ȡ. T2�����ж��PLP(physical layer pipe),ÿ��PLPֻ��һ��ISI(input stream identifier).*/
} FRONTEND_TER_SCAN_INFO_S;

/** FRONTEND ATV System*//** CNcomment:ATV��ʽ��Ϣ.*/
typedef enum _FRONTEND_ATV_SYSTEM_E
{
    FRONTEND_ATV_SYSTEM_PAL_BG = 0,          /**< PAL_BG *//**<CNcomment: PAL BG������ʽ*/
    FRONTEND_ATV_SYSTEM_PAL_DK,              /**< PAL_DK  *//**<CNcomment: PAL DK������ʽ*/
    FRONTEND_ATV_SYSTEM_PAL_I,               /**< PAL_I *//**<CNcomment: PAL I������ʽ*/
    FRONTEND_ATV_SYSTEM_PAL_M,               /**< PAL_M *//**<CNcomment: PAL M������ʽ*/
    FRONTEND_ATV_SYSTEM_PAL_N,               /**< PAL_N *//**<CNcomment: PAL N������ʽ*/
    FRONTEND_ATV_SYSTEM_SECAM_BG,            /**< SECAM_BG *//**<CNcomment: SECAM BG������ʽ*/
    FRONTEND_ATV_SYSTEM_SECAM_DK,            /**< SECAM_DK *//**<CNcomment: SECAM DK������ʽ*/
    FRONTEND_ATV_SYSTEM_SECAM_L_PRIME,       /**< SECAM_L_PRIME *//**<CNcomment: SECAM L PRIME������ʽ*/
    FRONTEND_ATV_SYSTEM_SECAM_LL,            /**< SECAM_LL *//**<CNcomment: SECAM LL������ʽ*/
    FRONTEND_ATV_SYSTEM_NTSC_M,              /**<NTSC_M  *//**<CNcomment: NTSC M������ʽ*/
    FRONTEND_ATV_SYSTEM_BUTT
} FRONTEND_ATV_SYSTEM_E;

typedef enum _FRONTEND_ATV_SIF_BW_E
{
    FRONTEND_ATV_SIF_BW_WIDE = 0,   /**< For Auto Scan Mode */
    FRONTEND_ATV_SIF_BW_NORMAL,     /**< For Normal Play Mode */
    FRONTEND_ATV_SIF_BW_NARROW,     /**< Not Recommended */
    FRONTEND_ATV_SIF_BW_BUTT
} FRONTEND_ATV_SIF_BW_E;

typedef enum _FRONTEND_ATV_CONNECT_WORK_MODE_E
{
    FRONTEND_CONNECT_WORK_MODE_NORMAL = 0,   /**<normal  *//**<CNcomment: ��������ģʽ */
    FRONTEND_CONNECT_WORK_MODE_CHAN_SCAN,    /**<chan scan  *//**<CNcomment: RF��̨ģʽ */
    FRONTEND_CONNECT_WORK_MODE_BUTT,
} FRONTEND_ATV_CONNECT_WORK_MODE_E;

/** FRONTEND ATV scan info*//** CNcomment:ATV��������.*/
typedef struct _FRONTEND_ATV_SCAN_INFO_S
{
    U32                               u32Freq;            /**< freq  KHz*//**<CNcomment: ����Ƶ��(KHz)*/
    FRONTEND_ATV_SYSTEM_E             enSystem;           /**<CNcomment: ATV��ʽ */
    FRONTEND_ATV_SIF_BW_E             enSifBw;            /**< Atv sif bandwidth */
    FRONTEND_ATV_CONNECT_WORK_MODE_E  enConnectWorkMode;  /**<connect mode :scan or switch */
} FRONTEND_ATV_SCAN_INFO_S;

/** FRONTEND ATV signal info*//** CNcomment: ATV�ź���Ϣ*/
typedef struct _FRONTEND_ATV_SIGNALINFO_S
{
    BOOL bVifLock;            /**< vif lock status *//**<CNcomment: ��Ƶ�Ƿ����� */
    BOOL bAfcWin;             /**< TRUE in afc window, FALSE no*//**<CNcomment: �Ƿ���AFC�������� */
    BOOL bCarrDet;            /**< TRUE carr detec on, FALSE off*//**<CNcomment: ��Ƶ�����ز���� */
    S32  s32AfcFreq;          /**< freq  KHz*//**<CNcomment: AFCƵ��ֵ����λKhz */
} FRONTEND_ATV_SIGNALINFO_S;

/** FRONTEND ATV lock status *//** CNcomment: ATVǰ��lock״̬*/
typedef enum _FRONTEND_ATV_LOCK_STATUS_E
{
    FRONTEND_ATV_UNLOCK = 0,  /**< UNLOCK*//**<CNcomment:UNLOCK */
    FRONTEND_ATV_LOCK,        /**< LOCK*//**<CNcomment: LOCK */
    FRONTEND_ATV_BUTT
} FRONTEND_ATV_LOCK_STATUS_E;

/** FRONTEND DTMB carrier mode *//**CNcomment: DTMB �ز�����*/
typedef enum _DTMB_CARRIER_MODE_E
{
    FRONTEND_DTMB_CARRIER_UNKNOWN = 0,  /**<CNcomment: δ֪����*/
    FRONTEND_DTMB_CARRIER_SINGLE,       /**<Single carrier  *//**<CNcomment: ���ز�*/
    FRONTEND_DTMB_CARRIER_MULTI,        /**<Multi carrier  *//**<CNcomment: ���ز�*/
    FRONTEND_DTMB_CARRIER_BUTT
} FRONTEND_DTMB_CARRIER_MODE_E;

/** FRONTEND DTMB code rate *//**CNcomment:DTMB ��������*/
typedef enum _FRONTEND_DTMB_CODE_RATE_E
{
    FRONTEND_DTMB_CODE_RATE_UNKNOWN = 0, /**<CNcomment: δ֪����*/
    FRONTEND_DTMB_CODE_RATE_0_DOT_4,     /**< 0.4  *//**<CNcomment: 0.4 ����*/
    FRONTEND_DTMB_CODE_RATE_0_DOT_6,     /**< 0.6  *//**<CNcomment: 0.6 ����*/
    FRONTEND_DTMB_CODE_RATE_0_DOT_8,     /**< 0.8  */ /**<CNcomment: 0.8 ����*/
    FRONTEND_DTMB_CODE_RATE_BUTT
} FRONTEND_DTMB_CODE_RATE_E;

/** FRONTEND DTMB time interleave *//**CNcomment: DTMB ʱ��֯����*/
typedef enum _FRONTEND_DTMB_TIME_INTERLEAVE_E
{
    FRONTEND_DTMB_TIME_INTERLEAVER_UNKNOWN = 0, /**<CNcomment: δ֪����*/
    FRONTEND_DTMB_TIME_INTERLEAVER_240,         /**< 240  *//**<CNcomment: 240 ����*/
    FRONTEND_DTMB_TIME_INTERLEAVER_720,         /**< 720  *//**<CNcomment: 720 ����*/
    FRONTEND_DTMB_TIME_INTERLEAVER_BUTT
} FRONTEND_DTMB_TIME_INTERLEAVE_E;

/** FRONTEND DTMB time interval *//**CNcomment:  DTMB �����������*/
typedef enum _FRONTEND_DTMB_GUARD_INTERVAL_E
{
    FRONTEND_DTMB_GI_UNKNOWN = 0,   /**<unknown type*//**<CNcomment:δ֪����*/
    FRONTEND_DTMB_GI_420,           /**<420 type*//**<CNcomment:420 ����*/
    FRONTEND_DTMB_GI_595,           /**<595 type*//**<CNcomment:595 ����*/
    FRONTEND_DTMB_GI_945,           /**<945 type*//**<CNcomment:945 ����*/
    FRONTEND_DTMB_GI_BUTT
} FRONTEND_DTMB_GUARD_INTERVAL_E;

/** FRONTEND DTMB scan param *//**CNcomment:  DTMB��������*/
typedef struct _FRONTEND_DTMB_SCAN_INFO_S
{
    U32                              u32Freq;               /**< freq  KHz*//**<CNcomment: ����Ƶ��(KHz)*/
    FRONTEND_BAND_WIDTH_E            enBandWidth;           /**< BandWidth*//**<CNcomment: ����*/
    FRONTEND_MODULATION_E            enModulation;          /**< Modulation*//**<CNcomment: ģʽ*/
    FRONTEND_SPECTRUM_E              enSpectrum;            /**< spectrum *//**<CNcomment: Ƶ�׼���*/

    FRONTEND_DTMB_CARRIER_MODE_E     enCarrierMode;         /**<Carrier type*//**<CNcomment:�ز�����*/
    FRONTEND_DTMB_CODE_RATE_E        enCoderate;            /**<Code rate type*//**<CNcomment:��������*/
    FRONTEND_DTMB_TIME_INTERLEAVE_E  enTimeInterleave;      /**<Time interleave type*//**<CNcomment:ʱ��֯����*/
    FRONTEND_DTMB_GUARD_INTERVAL_E   enGuardInterval;       /**<Guard interval type*//**<CNcomment:����ʱ������*/
    U8  u8ChannelIndex;
} FRONTEND_DTMB_SCAN_INFO_S;

/** FRONTEND scan param union *//**CNcomment:  �ź���������*/
typedef union _FRONTEND_SIGNAL_SCAN_INFO_U
{
    FRONTEND_SAT_SCAN_INFO_S    stSatInfo;   /**<Sat info *//**<CNcomment:������Ƶ��Ϣ*/
    FRONTEND_CAB_SCAN_INFO_S    stCabInfo;   /**<Cab info *//**<CNcomment:������Ƶ��Ϣ*/
    FRONTEND_TER_SCAN_INFO_S    stTerInfo;   /**<Ter info *//**<CNcomment:Ter��Ƶ��Ϣ*/
    FRONTEND_ATV_SCAN_INFO_S    stAtvInfo;   /**<Atv info *//**<CNcomment:ģ����Ƶ��Ϣ*/
    FRONTEND_DTMB_SCAN_INFO_S   stDtmbInfo;  /**<Dtmb info*//**<CNcomment:Dtmb��Ƶ��Ϣ*/
} FRONTEND_SIGNAL_SCAN_INFO_U;

/** FRONTEND scan freq info *//**CNcomment:  Ƶ����Ϣ*/
typedef struct _FRONTEND_SCAN_INFO_S
{
    U16                         u16TsIndex;       /**<Ts index *//**<CNcomment: ts��ͨ�����൱��bank*/
    FRONTEND_FE_TYPE_E          enFrontendType;   /**<Type *//**<CNcomment: ��Ƶ����*/
    FRONTEND_SIGNAL_SCAN_INFO_U unScanInfo;       /**<Scan info  *//**<CNcomment: ��Ƶ����*/
} FRONTEND_SCAN_INFO_S;

/** FRONTEND status *//**CNcomment:  Ƶ��������ǿ�ȣ���������Ƶ��Ϣ*/
typedef struct _FRONTEND_FRONTEND_STATUS_S
{
    U32     u32Strength;         /**<Strength *//**<CNcomment: �ź�ǿ��*/
    U32     u32Quality;          /**<Quality *//**<CNcomment: �ź�����*/
    float   fBert;               /**<Ber*//**<CNcomment: ������*/
} FRONTEND_FRONTEND_STATUS_S ;

typedef enum _FRONTEND_UNICABLE_SCAN_EVT_E
{
    FRONTEND_UNICABLE_SCAN_EVT_STATUS = 0,      /**<New status*//**<CNcomment:״̬�仯*/
    FRONTEND_UNICABLE_SCAN_EVT_PROGRESS,        /**<New Porgress *//**<CNcomment:���ȱ仯*/
    FRONTEND_UNICABLE_SCAN_EVT_BUTT             /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_UNICABLE_SCAN_EVT_E;

typedef enum _FRONTEND_UNICABLE_SCAN_STATUS_E
{
    FRONTEND_UNICABLE_SCAN_STATUS_IDLE = 0,     /**<Idel*//**<CNcomment:����*/
    FRONTEND_UNICABLE_SCAN_STATUS_SCANNING,     /**<Scanning*//**<CNcomment:ɨ����*/
    FRONTEND_UNICABLE_SCAN_STATUS_FINISH,       /**<Finish*//**<CNcomment:�ɹ����*/
    FRONTEND_UNICABLE_SCAN_STATUS_QUIT,         /**<User quit*//**<CNcomment:�û��˳�*/
    FRONTEND_UNICABLE_SCAN_STATUS_FAIL,         /**<Scan fail*//**<CNcomment:ɨ��ʧ��*/
    FRONTEND_UNICABLE_SCAN_STATUS_BUTT          /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
} FRONTEND_UNICABLE_SCAN_STATUS_E;

typedef union _FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U
{
    FRONTEND_UNICABLE_SCAN_STATUS_E* penStatus;             /**<Scanning status*//**<CNcomment:äɨ״̬*/
    U16*                             pu16ProgressPercent;   /**<Scanning progress*//**<CNcomment:äɨ����*/
} FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U;

/**
\brief FrontEnd callback.CNcomment:FrontEnd�ص�����
\attention \n
N/A
\param[in] hFrontend    frontend handle                             CNcomment:�豸���
\param[in] enBlindscanStatus      notify event                      CNcomment:���׵��¼�
\param[in] pstBlindscanData       ref:FRONTEND_SAT_BLINDSCAN_DATA_S CNcomment:���׵����� FRONTEND_SAT_BLINDSCAN_DATA_S
\param[in] u32UserData  FRONTEND_REG_CALLBACK_PARAMS_S 3rd param    CNcomment:�û�ע�ᴫ��Ĳ�����ֱ�ӻش�
\retval ::SUCCESS:   success                                     CNcomment:�ɹ�
\retval ::FAILURE:   fail                                        CNcomment:ʧ��
\see \n
::FRONTEND_FE_STATUS_E
::FRONTEND_SAT_BLINDSCAN_DATA_S
::FRONTEND_REG_CALLBACK_PARAMS_S
N/A
*/

/** Satellite TP blindscan callback funtion *//**CNcomment: äɨ״̬/���ݻص�����*/
typedef void (*FRONTEND_SAT_BLINDSCAN_STATUS_PFN)(
    const HANDLE    hFrontend,
    const FRONTEND_FE_STATUS_E  enBlindscanStatus,          /**<CNcomment: äɨ״̬ */
    const FRONTEND_SAT_BLINDSCAN_DATA_S*   const pstBlindscanData,   /**<CNcomment:  äɨ����*/
    const U32 u32UserData /**<CNcomment:  �û�˽������*/);

/**
\brief FrontEnd callback.CNcomment:FrontEnd�ص�����
\attention \n
N/A
\param[in] hFrontend    frontend handle                             CNcomment:�豸���
\param[in] enOldStatus  oldstatus                                   CNcomment:��״̬
\param[in] enNewStatus  newstatus ref:FRONTEND_FE_STATUS_E          CNcomment:��״̬ FRONTEND_FE_STATUS_E
\param[in] u32UserData  FRONTEND_REG_CALLBACK_PARAMS_S 3rd param    CNcomment:�û�ע�ᴫ��Ĳ�����ֱ�ӻش�
\retval ::SUCCESS:   success                                     CNcomment:�ɹ�
\retval ::FAILURE:   fail                                        CNcomment:ʧ��
\see \n
::FRONTEND_FE_STATUS_E
::FRONTEND_REG_CALLBACK_PARAMS_S
N/A
*/

/** Satellite TP lock status callback funtion, call this when status change *//**CNcomment: ����״̬֪ͨ�ص�����,����״̬�ı��ʱ��ص�.*/
typedef void (*FRONTEND_NOTIFY_STATUS_PFN)(const HANDLE hFrontend,
        const FRONTEND_FE_STATUS_E enOldStatus,
        const FRONTEND_FE_STATUS_E enNewStatus,
        const U32 u32UserData /**<CNcomment:  �û�˽������*/);

/**
\brief FrontEnd callback.CNcomment:FrontEnd�ص�����
\attention \n
On some platform frontend_get_signal_strength() may take more time. there are three ways to make it right.
1. Use these frontend_get_signal_strength(), frontend_get_signal_quality(),frontend_get_bert().
2. Take strength guality ber at set intervals, and return them in frontend_get_signal_strength(), frontend_get_signal_quality(),frontend_get_bert().
3. Take strength guality ber at variable intervals, and if FRONTEND_REG_GETSTATUS_CALLBACK is not NULL, get them by a thread and callback return them.
CNcomment:����Щƽ̨����,��ȡ�ź�����,�ź�ǿ��,��������Ҫ�ܳ�ʱ����Һ�ռcup��Դ.
1. �ڵ���frontend_get_signal_strength(), frontend_get_signal_quality(),frontend_get_bert() ��ʱ��,ֱ�Ӵӵײ��ȡ�������ܻᵼ�»�ȡ��ʱ��Ӧ�ò˵���Ӧ�Ƚ���.
2. ÿ��һ�γ���ʱ��,�ӵײ��ȡһ��,������frontend����,Ӧ�û�ȡ��ʱ��,ֱ�ӷ��ر����ֵ.��������Ӱ��˵���Ӧʱ��,���Ƕ�cup��Դռ�ÿ�����Ӱ��.
3. ����ʱ��ȡ������,�ź�����,�ź�ǿ��.��Ӧ�õ�������һ��frontend_get_signal_strength(), frontend_get_signal_quality(),frontend_get_bert()ֱ�ӷ���ԭ��������ź�ǿ��/�ź�����/������
   ͬʱ,���ע���FRONTEND_REG_GETSTATUS_CALLBACK ���͵Ļص�����ָ�벻Ϊ��,������ٴ�ȥ��ȡһ�ε�ǰ���ź�����,�ź�ǿ��,������.Ȼ��ص���ȥ.
   �����ȱ����˵���Ӧ�ò˵���Ӧ��,�ֱ����˶�ʱ��ȡռ��CPU ��Դ������.
�����ַ�ʽ, �ӿ���ʵ�ֵ�ʱ��,����������ַ�ʽ,ȡ���ھ���ƽ̨��ȡ��Ч��.����Ҫÿ�ֶ�ʵ��.CNend

N/A
\param[in] hFrontend    frontend handle                             CNcomment:�豸���
\param[in] pFrontendStatus   strength, quality, ber                 CNcomment:��ǰ�źŵ�ǿ�ȣ�������������
\param[in] u32UserData  userdata                                    CNcomment:�û�ע�ᴫ��Ĳ�����ֱ�ӻش�
\retval ::SUCCESS:   success                                     CNcomment:�ɹ�
\retval ::FAILURE:   fail                                        CNcomment:ʧ��
\see \n
N/A
*/

typedef void (*FRONTEND_GET_STATUS_PFN)(const HANDLE hFrontend,
                                        const FRONTEND_FRONTEND_STATUS_S* const pFrontendStatus,
                                        const U32 u32UserData );

/**
\brief FrontEnd callback.CNcomment:FrontEnd�ص�����
\attention \n
N/A
\param[in] hFrontend    frontend handle                             CNcomment:�豸���
\param[in] enOldStatus  oldstatus                                   CNcomment:��״̬
\param[in] enNewStatus  newstatus ref:FRONTEND_LNB_PWR_STATUS_E     CNcomment:��״̬ FRONTEND_LNB_PWR_STATUS_E
\param[in] u32UserData  FRONTEND_REG_CALLBACK_PARAMS_S 3rd param    CNcomment:�û�ע�ᴫ��Ĳ�����ֱ�ӻش�
\retval ::SUCCESS:   success                                     CNcomment:�ɹ�
\retval ::FAILURE:   fail                                        CNcomment:ʧ��
\see \n
::FRONTEND_LNB_PWR_STATUS_E
N/A
*/

typedef void (*FRONTEND_NOTIFY_LNB_PWR_STATUS_PFN)(const HANDLE hFrontend,
        const FRONTEND_LNB_PWR_STATUS_E enOldStatus,
        const FRONTEND_LNB_PWR_STATUS_E enNewStatus,
        const U32 u32UserData /**<CNcomment:  �û�˽������*/);

/**
\brief FrontEnd unicable scan callback.CNcomment:FrontEnd unicable �����ص�����
\attention \n
N/A
\param[in] hFrontend    frontend handle                             CNcomment:�豸���
\param[in] enEVT  FRONTEND_UNICABLE_SCAN_EVT_E type of data         CNcomment:���ص���������
\param[in] pData  FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U data      CNcomment:���ص����ݣ�������������
\retval ::SUCCESS:   success                                     CNcomment:�ɹ�
\retval ::FAILURE:   fail                                        CNcomment:ʧ��
\see \n
::FRONTEND_UNICABLE_SCAN_EVT_E
::FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U
N/A
*/

typedef void (*FRONTEND_UNICABLE_SCAN_PFN)(const HANDLE hFrontend, FRONTEND_UNICABLE_SCAN_EVT_E enEVT, FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U* pData);

/** FRONTEND register callback type *//**CNcomment: �ص���������*/
typedef enum _FRONTEND_REG_CALLBACK_TYPE_E
{
    FRONTEND_REG_LOCKSTATUS_CALLBACK = 0,   /**< Callback ProtoType :  frontend_notify_status_pfn_t*/
    FRONTEND_REG_GETSTATUS_CALLBACK,        /**< Callback ProtoType :  frontend_get_status_pfn_t */
    FRONTEND_REG_BLINDSCAN_CALLBACK,        /**< Callback ProtoType :  frontend_sat_blindscan_status_pfn_t*/
    FRONTEND_REG_LNB_PWR_STATUS_CALLBACK,   /**< Callback ProtoType :  frontend_notify_lnb_pwr_status_pfn_t*/
    FRONTEND_REG_UNICABLE_SCAN_CALLBACK,    /**< Callback ProtoType :  FRONTEND_UNICABLE_SCAN_PFN*/
    FRONTEND_REG_CALLBACK_TYPE_BUTT
} FRONTEND_REG_CALLBACK_TYPE_E ;

/** FRONTEND register callback params *//**CNcomment: �ص�����ע�����*/
typedef struct _FRONTEND_REG_CALLBACK_PARAMS_S
{
    FRONTEND_REG_CALLBACK_TYPE_E    enCallbackType;    /**<see FRONTEND_REG_CALLBACK_TYPE_E *//**<CNcomment: �ص���������, ���������p_callback ԭ��  */
    void*   pCallBack;                                 /**< funtion callback *//**<CNcomment: ��Ҫע��Ļص�����*/
    U32     u32UserData;                               /**< date user want send back *//**<CNcomment: �û���Ҫ�ش�������*/
    BOOL    bDisable;                                  /**< FALSE is enable ; TRUE is disable *//**<CNcomment:  �Ƿ�ʹ�ܸûص�: FALSE is enable ; TRUE is disable*/
} FRONTEND_REG_CALLBACK_PARAMS_S;

/** FRONTEND info *//**CNcomment: frontend ��Ϣ��tuner��Ϣ*/
typedef struct _FRONTEND_INFO_S
{
    FRONTEND_DEVICE_NAME    aszDevName; /**< name *//**<CNcomment: ����*/
    U32 u32CallbackNum;   /**< callback num *//**<CNcomment: �ص������ĸ���.*/
    U32 u32SourceId;      /**< source id,diffrent means on diffrent platform, so use it right way */
    /**<CNcomment: ��Ӧ��TS����Դͨ��.��ͬƽ̨��������������ܲ�һ��,Ҫ��sk_hdi_dmx ģ��Լ����, ��Ϊdmx��Ҫ������ȡ����, dmx ģ���CIģ��ʵ�ֵ�ʱ����source_id ��ת���ɾ���ts��Դ���� ����. */
    FRONTEND_DISEQC_VER_E   enDiseqcVer; /**< Diseqc Ver *//**<CNcomment: ֧�ֵ�DISEQC�汾.*/
    U32 u32Generation;    /**< eg. c c2 s s2 *//**<CNcomment: ֧���Ĵ�ǰ��(eg C,C2).or��ϵ,��һ��ʹ��0x1,�ڶ���ʹ��0x1<<1,
                                    * ��������.���֧�ֶ��ʹ��or��ϵ(eg. C|C2 <=> 0x3).*/
    DMX_ID_E    enDemuxSetArr[DMX_NUMBER_OF_DMX_ID]; /**< demux_set_arr[0]=DMX_ID_0|DMX_ID_3 means frontend 0 support out to DMX_ID_0 DMX_ID_3. *//**<CNcomment: ����ǰ��֧�ֵ�dmx��(or��ϵ). ���demux_set_arr[0]=DMX_ID_0|DMX_ID_3.��ʾ��frontend֧��ts�����DMX_ID_0,Ҳ����ͬʱ�����DMX_ID_3.
                                                            *  ���demux_set_arr[i]=0, ��ʾ��frontend��֧��SK_HDI_DMX_ID_i,�Լ���������dmx���������.*/
} FRONTEND_INFO_S;

/** FRONTEND CAPABILITY *//**CNcomment: frontend ����(��ģtuner)*/
typedef struct _FRONTEND_CAPABILITY_S
{
    U32 u32TunerNum;
    U32 au32FeCurType[FRONTEND_FE_NUM_MAX];
    U32 au32FeType[FRONTEND_FE_NUM_MAX];  /**< eg. au32FeType[0]=3 means this tuner has two capability,one is FRONTEND_FE_SATELLITE1 (1) the other is FRONTEND_FE_SATELLITE2(2)*/
    /**<CNcomment: ��au32FeType ��FRONTEND_FE_TYPE_E ����ö�ٳ�Ա�Ķ�Ӧ��λ��Ϊ0,
    * ��ϵͳ�и����͵�tuner, ����:au32FeType[0]=3,��ʾ��һ�ڶ�λ��Ϊ0
    * ���ϵͳ��tuner 0��FRONTEND_FE_SATELLITE1 (1) ��FRONTEND_FE_SATELLITE2(2)��������.
    * au32FeType[1]=4,��ʾ����λ��Ϊ0,���ϵͳ��tuner 1 ��FRONTEND_FE_CABLE1(3)һ������.
    * ע��,ʹ�õ�ʱ��,Ҫ��FRONTEND_FE_TYPE_E,����ö��ֵ,��Ҫʹ������,
    * �����Ժ���٤ö�ٴ���ά�����鷳.
    */
} FRONTEND_CAPABILITY_S;

/** FRONTEND generation 2: DVB-C2,DVB-T2,DVB-S2,modulation and FEC rate.*//**CNcomment: DVB-C2,DVB-T2,DVB-S2,modulation and FEC rate.*/
typedef struct _FRONTEND_G2_MODFEC_S
{
    FRONTEND_FEC_RATE_E     enFecRate;       /**< FEC rate.*//**<CNcomment: FEC rate*/
    FRONTEND_MODULATION_E   enModulation;    /**< modulation.*//**<CNcomment: ģʽ*/
} FRONTEND_G2_MODFEC_S;

/** FRONTEND DVB-C2,DVB-T2,DVB-S2 stream type. *//**CNcomment: DVB-C2,DVB-T2,DVB-S2�������ĸ�ʽ.*/
typedef enum _FRONTEND_G2_STREAM_TYPE_E
{
    FRONTEND_G2_STREAM_TYPE_UNKNOWN = 0,      /**< UNKNOWN.*//**<CNcomment: δ֪*/
    FRONTEND_G2_STREAM_TYPE_TS      = 1 << 0, /**< MPEG-TS.*/ /**<CNcomment: MPEG-TS*/
    FRONTEND_G2_STREAM_TYPE_GSE     = 1 << 1, /**< Generic Encapsulated Stream.*/ /**<CNcomment: GSE*/
    FRONTEND_G2_STREAM_TYPE_GCS     = 1 << 2, /**< Generic Continuous Stream.*/ /**<CNcomment: GCS*/
    FRONTEND_G2_STREAM_TYPE_GFPS    = 1 << 3, /**< Generic Packetized Stream.*/ /**<CNcomment: GFPS*/
    FRONTEND_G2_STREAM_TYPE_BUTT
} FRONTEND_G2_STREAM_TYPE_E;

/** FRONTEND DVB-C2,DVB-T2,DVB-S2 channel info. *//**CNcomment: DVB-C2,DVB-T2 PLP,DVB-S2 ISI ��Ϣ.*/
typedef struct _FRONTEND_G2_CHANNEL_INFO_S
{
    U8  u8Isi;                                  /**< Input Stream Identifier.*/
    FRONTEND_G2_STREAM_TYPE_E   enStreamType;   /**< Input Stream type.*//**<CNcomment: DVB-C2,DVB-T2,DVB-S2�������ĸ�ʽ.*/
    BOOL bCcm;                                  /**< TRUE:Constant Coding and Modulation;FALSE:Variable/Adaptive Coding and Modulation.*/
    BOOL bIssActive;                            /**< whether ISS active.ISS:Input Stream Synchronization.TRUE:active;FALSE:not active.*/
    BOOL bNpdActive;                            /**< whether NPD active.NPD:Null Packet deletion.TRUE:active;FALSE:not active.
                                                     If NPD active, then DNP shall be computed and appended after UPs(User Packets)*/
    FRONTEND_ROLLOFF_E  enRollOff;              /**< only DVB-S2 .*/
    FRONTEND_G2_MODFEC_S    stModFec;           /**< modulation and FEC rate .*/
    BOOL bShortFrame;                           /**< TRUE:16 200 bits,FALSE:64 800 bits.*/
} FRONTEND_G2_CHANNEL_INFO_S;

/** FRONTEND DVB-C2,DVB-T2,DVB-S2 params. *//**CNcomment: DVB-C2,DVB-T2,DVB-S2 �ŵ����ò���.*/
typedef struct _FRONTEND_G2_REQ_PARAMS_S
{
    FRONTEND_G2_MODFEC_S    stModFec;           /**< see sk_hdi_frontend_g2_modcod_t.*/
    BOOL                    bPilots;            /**< TRUE:pilots, FALSE:no pilots.*/
} FRONTEND_G2_REQ_PARAMS_S;

/** FRONTEND DVB-C2,DVB-T2,DVB-S2 response . *//**CNcomment: DVB-C2,DVB-T2,DVB-S2 �ŵ����û�Ӧ����.*/
typedef struct _FRONTEND_G2_RPN_PARAMS_S
{
    U8  u8ModFecAck;                /**< coded according to the MODCOD_RQ conventions.*/
} FRONTEND_G2_RPN_PARAMS_S;

#ifdef ANDROID_HAL_MODULE_USED
/**Frontend module structure(Android require)*/
/**CNcomment:Frontendģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _FRONTEND_MODULE_S
{
    struct hw_module_t common;
} FRONTEND_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_FRONTEND*/
/** @{*/  /** <!-- -HAL_FRONTEND=*/

/**Frontend device structure*//** CNcomment:Frontend�豸�ṹ*/
typedef struct _FRONTEND_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif
    /**
    \brief Frontend init.CNcomment:frontend��ʼ�� CNend
    \attention \n
    frontend module init ,  repeat call return success.
    CNcomment:frontendģ���ʼ��, �������ظ����÷��سɹ�. CNend

    \param[in] pstInitParams frontend module init param.CNcomment:��ʼ��ģ����� CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_FRONTEND_INIT_FAILED  lower layer frontend init error.CNcomment:frontend�ײ��ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_INIT_PARAMS_S

    \par example
    \code
    FRONTEND_INIT_PARAMS_S stInitParam;
    memset(&stInitParam, 0x0, sizeof(FRONTEND_INIT_PARAMS_S));
    if (SUCCESS != frontend_init(pstDev, (const FRONTEND_INIT_PARAMS_S * const)&stInitParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*frontend_init)(struct _FRONTEND_DEVICE_S* pstDev, const FRONTEND_INIT_PARAMS_S*  const pstInitParams);

    /**
    \brief Frontend open.CNcomment:frontend ��ʵ�� CNend
    \attention \n
    Frontend open.
    CNcomment:Frontend ��ʵ��. CNend
    \param[out] phFrontend frontend hanlde. CNcomment:ʵ��������ⲿ���� CNend
    \param[in] pstInitParams frontend module init param.CNcomment:ʵ���򿪲��� CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ�.�ظ�����init���سɹ���CNend
    \retval ::ERROR_FRONTEND_NOT_INIT  frontend not init.CNcomment:frontendδ��ʼ����CNend
    \retval ::ERROR_FRONTEND_OPEN_FAILED frontend open error. CNcomment:��ʵ��ʧ�ܡ�CNend
    \retval ::ERROR_FRONTEND_ALREADY_OPEN this handle already open.CNcomment:�þ����ʵ���Ѿ��򿪡� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_OPEN_PARAMS_S

    \par example
    \code
    FRONTEND_OPEN_PARAMS_S stOpenParam;
    memset(&stOpenParam, 0x0, sizeof(FRONTEND_OPEN_PARAMS_S));
    if (SUCCESS != frontend_open(pstDev, "tuner0",(const FRONTEND_OPEN_PARAMS_S * const)&stOpenParam))
    {
        return FAILURE;
    }

    or

    FRONTEND_OPEN_PARAMS_S stOpenParam;
    memset(&stOpenParam, 0x0, sizeof(FRONTEND_OPEN_PARAMS_S));
    u32 tunerId = 0;
    if (SUCCESS != frontend_open(pstDev, const (HANDLE*)&tunerId,(const FRONTEND_OPEN_PARAMS_S * const)&stOpenParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*frontend_open) (struct _FRONTEND_DEVICE_S* pstDev, HANDLE* const phFrontend,
                          const  FRONTEND_OPEN_PARAMS_S*  const pOpenParams);

    /**
    \brief Frontend open.CNcomment:frontend �ر�ʵ�� CNend
    \attention \n
    Frontend close.
    CNcomment:Frontend �ر�ʵ��. CNend
    \param[in] frontend_handle frontend hanlde. CNcomment:ʵ��������ⲿ���� CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_FRONTEND_NOT_INIT  frontend not init.CNcomment:frontendδ��ʼ����CNend
    \retval ::ERROR_FRONTEND_NOT_OPEN frontend handle not open, or no this handle CNcomment:ʵ��δ�򿪻���û�иľ�����豸��CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::FAILURE  other error.CNcomment:�رմ��� CNend
    \see \n
    ::SYSTEM_INIT_PARAMS_S

    \par example
    \code
    if (SUCCESS != frontend_close(pstDev, "tuner0"))
    {
        return FAILURE;
    }
    or
    u32 tunerId = 0;
    if (SUCCESS != frontend_close(pstDev, tunerId))
    {
        return FAILURE;
    }

    \endcode
    */

    S32 (*frontend_close)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE frontend_handle);

    /**
     \brief Get Frontend handle by index.CNcomment:����index��ȡfrontend��� CNend
     \attention \n
    Tuner of u32FrontendIndex must be init��
    CNcomment:��Tuner�����ʼ��. CNend
    \param[out] phFrontend frontend hanlde. CNcomment:ʵ��������ⲿ���� CNend
     \param[in] u32FrontendIndex frontend index.CNcomment:��ʼ��ʱʹ�õ�FrontendIndex CNend
     \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_FRONTEND_NOT_INIT  Not init.CNcomment:��index��tunerû�г�ʼ�� CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::FRONTEND_TERM_PARAMS_S

     \par example
     \code
     \endcode
    */
    S32 (*frontend_get_handle)(struct _FRONTEND_DEVICE_S* pstDev, U32 u32FrontendIndex, HANDLE* const phFrontend);

    /**
    \brief Frontend term.CNcomment:frontendȥ��ʼ�� CNend
    \attention \n
    frontend module deinit and release occupied resource,  repeat call return success.
    CNcomment:frontendģ��ȥ��ʼ�����ͷ�ռ�õ���Դ, �������ظ����÷��سɹ�. CNend

    \param[in] pstTermParams frontend module term param.CNcomment:ȥ��ʼ��ģ����� CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_FRONTEND_DEINIT_FAILED  Lower layer frontend module deinit error.CNcomment:�ײ�frontendģ��ȥ��ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_TERM_PARAMS_S

    \par example
    \code
    FRONTEND_TERM_PARAMS_S stTermParam;
    memset(&stInitParam, 0x0, sizeof(FRONTEND_TERM_PARAMS_S));
    if (SUCCESS != frontend_term(pstDev, (const FRONTEND_TERM_PARAMS_S * const)&stTermParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*frontend_term)(struct _FRONTEND_DEVICE_S* pstDev, const FRONTEND_TERM_PARAMS_S* const pstTermParams);

    /**
    \brief Get scan info of tuner.CNcomment:��ȡfrontend ��ǰ��scan ״̬CNend
    \attention \n
    Get scan info of Frontend by handle.
    CNcomment:��ȡFrontend ��ǰscan��״̬. CNend
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] pstScanInfo frontend scan info .CNcomment: ��ȡ��scan ��Ϣ CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_SCAN_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_scan_info)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                                  FRONTEND_SCAN_INFO_S* const pstScanInfo);

    /**
    \brief set sat lnb config .CNcomment: ����lnb CNend
    \attention \n
    Before search satellite, or play program on one satellite.
    CNcomment:��̨ǰ�����߲���һ����Ŀǰ��ͬһ���������л������ͱ���ʱ��Ҫ����. CNend
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[in] pstLnbInfo lnb info. CNcomment: ��Ҫ���õ�lnb��Ϣ CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_SAT_LNB_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_sat_config_lnb)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_SAT_LNB_INFO_S* const pstLnbInfo);

    /**
     \brief init sat lnb config .CNcomment: ��ʼ��lnb�������� CNend
     \attention \n
    Before search satellite, or play program on one satellite.
    CNcomment:��̨ǰ�����߲���һ����Ŀǰ��ͬһ�����ǿ��Բ��ö������. CNend
     \param[in] hFrontend frontend handle param.CNcomment:��� CNend
     \param[in] pstLnbConfig lnb info. CNcomment: ��Ҫ���õ�lnb��Ϣ CNend
     \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::FRONTEND_SAT_LNB_CONFIG_S

     \par example
     \code
     \endcode
    */
    S32 (*frontend_sat_init_lnb)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_SAT_LNB_CONFIG_S* const pstLnbConfig);

    /**
     \brief set sat antenna config .CNcomment: �������߻������� CNend
     \attention \n
    Before search satellite, or play program on one satellite.
    CNcomment:��̨ǰ�����߲���һ����Ŀǰ��ͬһ�����ǿ��Բ��ö������. CNend
     \param[in] hFrontend frontend handle param.CNcomment:��� CNend
     \param[in] enAntennaCmd  type of FRONTEND_ANTENNA_CMD_TYPE_E. CNcomment: �������� CNend
     \param[in] pParam: Data type acording to enAntennaCmd. CNcomment: ��Ҫ���õ�������Ϣ CNend
     \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::FRONTEND_ANTENNA_CMD_TYPE_E

     \par example
     \code
     \endcode
    */
    S32 (*frontend_sat_config_antenna)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_ANTENNA_CMD_TYPE_E enAntennaCmd, void* pParam);

    /**
    \brief get lnb power status .CNcomment: ��ȡlnb ����״̬ CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] penLnbPwrStatus lnb power info. CNcomment: ��ȡ��lnb����״̬ CNend
    \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_LNB_PWR_STATUS_E

    \par example
    \code

    \endcode
    */

    S32 (*frontend_get_lnb_pwr_status)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, FRONTEND_LNB_PWR_STATUS_E* const penLnbPwrStatus);

    /**
    \brief scan one freq or set blindscan (sat)  .CNcomment: ��Ƶ����äɨ CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[in] pstScanParams scan params. CNcomment: ��Ƶ������äɨ����CNend
    \param[in] bSynch TRUE wait for lock or timeout, not use for blindscan. CNcomment: �Ƿ�ͬ����Ƶ��äɨ��Ч��äɨΪ�첽 CNend
    \param[in] u32Timeout timeout for locked, not use for blindscan. CNcomment: ��ʱʱ�䣬äɨ��Ч CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::FRONTEND_FE_STATUS_E  see FRONTEND_FE_STATUS_E. CNcomment:����FRONTEND_FE_STATUS_E״̬���������һ��Ƶ����ͬ��ֱ�ӷ���״̬��CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_SCAN_INFO_S

    \par example
    \code

    \endcode
    */

    S32 (*frontend_start_scan)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                               const FRONTEND_SCAN_INFO_S*   const  pstScanParams,
                               const BOOL bSynch,
                               const U32 u32Timeout);

    /**
    \brief stop scan one freq or set blindscan (sat)  .CNcomment:��ֹ ��Ƶ����äɨ CNend
    \attention \n
    stop frontend_start_scan() when bsynch is TRUE and timeout is not 0. stop blindscan.
    CNcomment:��ֹͬ����Ƶ�����Ǻ��������Ƶ��������ֹ����äɨ����̨���ڼ���äɨ��������Ƶ��. CNend
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_TERM_PARAMS_S

    \par example
    \code

    \endcode
    */
    S32  (*frontend_abort)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend);

    /**
    \brief register callback .CNcomment: ע��ص����� CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[in] pstRegParams frontend callback param.CNcomment:�ص��������� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_REG_CALLBACK_PARAMS_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_register_callback)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend, const FRONTEND_REG_CALLBACK_PARAMS_S* const pstRegParams);

    /**
    \brief config callback .CNcomment: ע��ص����� CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[in] pCallback callback funtion. CNcomment:�ص�����ָ�� CNend
    \param[in] enCallbackCfg frontend callback config.CNcomment:�ص������������Ĳ��� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_CFG_CALLBACK_E

    \par example
    \code

    \endcode
    */

    S32 (*frontend_config_callback)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend, const void* const  pCallback, const FRONTEND_CFG_CALLBACK_E enCallbackCfg);

    /**
    \brief lock sync .CNcomment:ͬ������ CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */

    S32 (*frontend_lock)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend);

    /**
    \brief get ber.CNcomment:��ȡ������ CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] pfBert get from frontend. CNcomment:������ָ�� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_bert)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,  float* const pfBert);

    /**
    \brief get quality.CNcomment:��ȡ�ź����� CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] pu32Quality get from frontend. CNcomment:�ź�����ָ�� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */

    S32 (*frontend_get_signal_quality)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                                       U32* const pu32Quality);

    /**
    \brief get strength.CNcomment:��ȡ�ź�ǿ�� CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] pu32Strength get from frontend. CNcomment:�ź�ǿ��ָ�� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_signal_strength)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                                        U32* const pu32Strength);

    /**
    \brief get atv signal info.CNcomment:��ȡ�ź���Ϣ CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] pstSignalInfo get from frontend. CNcomment:�ź���Ϣָ�� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_ATV_SIGNALINFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_atvsignalinfo)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, FRONTEND_ATV_SIGNALINFO_S* const pstSignalInfo);

    /**
    \brief get signal connect status.CNcomment:��ȡ�ź���Ƶ��Ϣ CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] penStatus get from frontend. CNcomment:�ź���Ƶ״ָ̬�� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_FE_STATUS_E

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_connect_status)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, FRONTEND_FE_STATUS_E* const penStatus);

    /**
    \brief get frontend all info. CNcomment:��frontend ������Ϣ CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] pstInfo get from frontend. CNcomment:frontend ��Ϣָ�� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_info)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend,
                             FRONTEND_INFO_S*   const pstInfo);

    /**
    \brief get frontend capability. CNcomment:��frontend ���� CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] pstCapability get from frontend. CNcomment:ָ���������ݵ�ָ�� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_CAPABILITY_S

    \par example
    \code

    \endcode
    */
    S32  (*frontend_get_capability)(struct _FRONTEND_DEVICE_S* pstDev, FRONTEND_CAPABILITY_S* const pstCapability);

    /**
    \brief get TS channel num just use for DVBC2,DVBT2,DVBS2 for DVBC,DVBT,DVBS ChannelNum is 1 . CNcomment:���ͨ������ֻ��DVBC2,DVBT2,DVBS2���ã���DVBC,DVBT,DVBS ���� 1 CNend
    \attention \n
    if tuner is auto support DVBT DVBT2 or DVBS DVBS2, after lock must use this funtion to know Versio. num 1 means 1 PLP, or 1 ISI.
    CNcomment:���tuner��������Ӧ�Ĺ��ܣ�����øú���ȷ���Ƿ�ΪVer2�汾��Э��.�ж���ͨ����ͨ��Ϊ1���Բ�����PLP�� ISI ���� CNend
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] pu8ChannelNum get from frontend. CNcomment:ChannelNum CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32  (*frontend_get_channel_num)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend, U8* const pu8ChannelNum);

    /**
    \brief get TS channel info just use for DVBC2,DVBT2,DVBS2 . CNcomment:��ȡͨ����Ϣ CNend
    \attention \n
    just use for install program. play program use frontend_config_channel().
    CNcomment:������Ŀʱ��ʹ�ã�����ʱ�� frontend_config_channel().
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[in] u8ChannelIndex channle index.CNcomment:ͨ����� CNend
    \param[out] pstChannelInfo get from frontend. CNcomment:ͨ����Ϣ CNend
    \param[in] u32Timeout timeout for get channelinfo.CNcomment:��ʱʱ�� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_G2_CHANNEL_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_channel_info)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const U8 u8ChannelIndex, FRONTEND_G2_CHANNEL_INFO_S* const pstChannelInfo, const U32 u32Timeout);

    /**
    \brief set TS channel info just use for DVBS2 . CNcomment:����ͨ����Ϣ ֻ֧��DVBS2 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[in] u8ChannelIndex channel index.CNcomment:ͨ����� CNend
    \param[in] pstReqParams channel info .CNcomment:ͨ�����ò��� CNend
    \param[out] pstRpnParams response from frontend, can be NULL . CNcomment:������Ϣ������NULL CNend
    \param[in] u32Timeout timeout for get channelinfo.CNcomment:��ʱʱ�� CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_G2_REQ_PARAMS_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_config_channel)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                                   const U8 u8ChannelIndex,
                                   const FRONTEND_G2_REQ_PARAMS_S* const pstReqParams,
                                   FRONTEND_G2_RPN_PARAMS_S* const pstRpnParams,
                                   const U32 u32Timeout);

    /**
     \brief set demod out ts. CNcomment: ��������� CNend
     \attention \n
    For T2 PLP & S2 ISI.
    CNcomment: ���úͻ�ȡT2��PLPģʽ�����úͻ�ȡS2��ISIģʽ CNend
     \param[in] hFrontend frontend handle param.CNcomment:��� CNend
     \param[in] enTsoutCmd  type of FRONTEND_TSOUT_CMD_TYPE_E. CNcomment: �������� CNend
     \param[in] pParam: Data type acording to enAntennaCmd. CNcomment: ��Ҫ���õĲ�����Ϣ CNend
     \retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
     \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
     \retval ::FAILURE  other error.CNcomment:�������� CNend
     \see \n
    ::FRONTEND_ANTENNA_CMD_TYPE_E

     \par example
     \code
     \endcode
    */
    S32 (*frontend_config_tsout)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_TSOUT_CMD_TYPE_E enTsoutCmd, void* pParam);

    /**
    \brief get ATV lock status. CNcomment:��ȡ��Ƶ״̬ CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[out] penLockStatus response from frontend, can be NULL . CNcomment:��Ƶ״̬ CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_ATV_LOCK_STATUS_E

    \par example
    \code
    FRONTEND_ATV_LOCK_STATUS_E enenLockStatus;
    frontend_atv_get_lock_status(dev, hFrontend,&enLockStatus);
    \endcode
    */
    S32 (*frontend_atv_get_lock_status)(struct _FRONTEND_DEVICE_S* pstDev, HANDLE  hFrontend, FRONTEND_ATV_LOCK_STATUS_E* penLockStatus);

    /**
    \brief fine tuned tunner frequency. CNcomment:΢��tunner��Ƶ��  CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \param[in] s32Steps fine tunned tunner step. CNcomment:΢��Ƶ�ʵ�ƫ���� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_atv_fineTune)(struct _FRONTEND_DEVICE_S* pstDev, HANDLE  hFrontend, S32 s32Steps);

    /**
    \brief Frontend standby. CNcomment:TUNER���� CNend
    \attention \n
    \param[in] frontend_handle frontend handle param.CNcomment:��� CNend
    \retval ::SUCCESS standby success.CNcomment:���óɹ���CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_standby)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE frontend_handle);

    /**
    \brief wake up tuner. CNcomment:TUNER���� CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:��� CNend
    \retval ::SUCCESS wakeup success.CNcomment:���óɹ���CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::FRONTEND_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_wakeup)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE frontend_handle);

} FRONTEND_DEVICE_S;

/**
\brief direct get frontend device api, for linux and android.CNcomment:��ȡfrontend�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get frontend device api��for linux and andorid.
CNcomment:��ȡfrontend�豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
\retval  frontend device pointer when success.CNcomment:�ɹ�����frontend�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::FRONTEND_DEVICE_S

\par example
*/
FRONTEND_DEVICE_S* getFrontEndDevice();

/**
\brief  Open HAL frontend module device.CNcomment: ��HAL frontendģ���豸 CNend
\attention \n
Open HAL frontend module device(for compatible Android HAL).
CNcomment:��HAL frontendģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice FrontEnd device structure.CNcomment:FrontEnd�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� ��CNend
\see \n
::FRONTEND_DEVICE_S

\par example
*/
static inline int frontend_open(const struct hw_module_t* pstModule, FRONTEND_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, FRONTEND_HARDWARE_FRONTEND0, (hw_device_t**)ppstDevice);
#else
    *ppstDevice = getFrontEndDevice();
    return SUCCESS;
#endif

}

/**
\brief  Close HAL frontend module device.CNcomment: �ر�HAL frontendģ���豸 CNend
\attention \n
Close HAL frontend module deinit(for compatible Android HAL).
CNcomment:�ر�HAL frontendģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice frontEnd device structure.CNcomment:frontEnd�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::FRONTEND_DEVICE_S

\par example
*/
static inline int frontend_close(FRONTEND_DEVICE_S* pstDevice)
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

#endif /* __TVOS_HAL_FRONTEND_H__ */

