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
/**Module id define.*//** CNcomment:模块ID 定义 */
#define FRONTEND_HARDWARE_MODULE_ID "frontend"

/**Device name define .*//** CNcomment:设备名称定义 */
#define FRONTEND_HARDWARE_FRONTEND0 "frontend0"

/**Tuner name max length.*//** CNcomment:Tuner 名称最大长度 */
#define FRONTEND_DEVICENAME_LENGTH  (32)

/**count callback setted in every frontend_handle.*//** CNcomment:每个frontend_handle 注册的回调函数的最大个数*/
#define FRONTEND_CALLBACK_MAX       (8)

/**Tuner max .*//** CNcomment:Tuner 最多有多少tuner */
#define FRONTEND_FE_NUM_MAX         (8)

/** @} */  /** <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_FRONTEND */
/** @{ */  /** <!-- [HAL_FRONTEND] */

/**Tuner name type*//** CNcomment:Tuner 名称数据结构 */
typedef char FRONTEND_DEVICE_NAME[FRONTEND_DEVICENAME_LENGTH + 1];

/**System init param *//** CNcomment:系统初始化参数 */
typedef struct _FRONTEND_INIT_PARAMS_S
{
    U32  u32Dummy;                        /**<for expand *//**<CNcomment:扩展使用*/
} FRONTEND_INIT_PARAMS_S;

/**System deinit param *//** CNcomment:系统去初始化参数 */
typedef struct _FRONTEND_TERM_PARAMS_S
{
    U32  u32Dummy;                        /**<for expand *//**<CNcomment:扩展使用*/
} FRONTEND_TERM_PARAMS_S;

/**frontend fe status *//** CNcomment:前端状态 */
typedef enum _FRONTEND_FE_STATUS_E
{
    FRONTEND_STATUS_UNKNOW = 0 ,          /**<Unknow status *//**<CNcomment:未知状态，设备初始化后但是没有任何实例时，处于未知状态*/
    FRONTEND_STATUS_UNLOCKED,             /**<unlocked *//**<CNcomment:未锁定，尝试多次不能锁定后才返回该状态. 底层仍然在尝试*/
    FRONTEND_STATUS_SCANNING,             /**<locking *//**<CNcomment:正在扫描，尝试多次如果不能锁定后改成TUNER_STATUS_UNLOCKED(扫描结束后确定是否为锁定状态)*/
    FRONTEND_STATUS_LOCKED,               /**<locked *//**<CNcomment:锁定*/
    FRONTEND_STATUS_NOSIGNAL,             /**<no signal *//**<CNcomment:没有信号，可以同TUNER_STATUS_UNLOCKED*/
    FRONTEND_STATUS_DISCONNECTED,         /**<disconnected *//**<CNcomment:已断开TS流数据*/
    FRONTEND_STATUS_IDLE,                 /**<idle *//**<CNcomment:初始状态，以及调用了disconnect函数。该状态下不会主动锁频(类似空闲状态)*/
    FRONTEND_STATUS_BLINDSCANING,         /**<blind scanning *//**<CNcomment:Demod 处于盲扫状态, 应用需要等待盲扫完成, 或者发送锁频消息强制退出盲扫*/
    FRONTEND_STATUS_BLINDSCAN_COMPLETE,   /**<blind scan complete *//**<CNcomment:Demod 盲扫完成*/
    FRONTEND_STATUS_BLINDSCAN_QUIT,       /**<User quit*//**<CNcomment:用户退出*/
    FRONTEND_STATUS_BLINDSCAN_FAIL,       /**<Scan fail*//**<CNcomment:扫描失败*/
    FRONTEND_STATUS_MOTOR_MOVING,         /**<Motor move*//**<CNcomment:马达移动*/
    FRONTEND_STATUS_MOTOR_STOP,           /**<Motor stop*//**<CNcomment:马达停止*/
    FRONTEND_STATUS_BUTT
} FRONTEND_FE_STATUS_E;

/**frontend type  *//** CNcomment:前端类型. */
typedef enum _FRONTEND_FE_TYPE_E
{
    FRONTEND_FE_SATELLITE1   = 1 << 0,    /** -S */ /**<CNcomment:卫星*/
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
                                          /**<CNcomment:作为入参J83B不会与其他信号或操作后传入，所以FRONTEND_FE_BUTT 值为 FRONTEND_FE_J83B + 1。当描述能力时使用的是U32不用该枚举*/
} FRONTEND_FE_TYPE_E;

/**frontend scan mode(satellite)  *//** CNcomment:卫星频点搜索方式*/
typedef enum _FRONTEND_SEARCH_MODE_E
{
    FRONTEND_SEARCH_MOD_NORMAL = 0,       /**<default *//**<CNcomment:默认方式*/
    FRONTEND_SEARCH_MOD_BLIND,            /**<offset freq and SR are Unknown *//**<CNcomment:频点步长和SR都未知*/
    FRONTEND_SEARCH_MOD_COLD_START,       /**<only the SR is known *//**<CNcomment:已知SR*/
    FRONTEND_SEARCH_MOD_WARM_START,       /**<offset freq and SR are known *//**<CNcomment:已知频点步长和SR*/
    FRONTEND_SEARCH_MOD_SAT_BLIND_MANUAL, /**<set startfreq endfreq, see FRONTEND_SAT_BLINDSCAN_PARA_S *//**<CNcomment:设置频点起始，极化和高低本振。查看 FRONTEND_SAT_BLINDSCAN_PARA_S*/
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

/** LNB type *//** CNcomment:LNB类型*/
typedef enum _FRONTEND_LNB_TYPE_E
{
    FRONTEND_LNB_SINGLE_FREQUENCY = 0,    /**<Single LO frequency*//**<CNcomment:单本振*/
    FRONTEND_LNB_DUAL_FREQUENCY,          /**<Dual LO frequency*//**<CNcomment:双本振*/
    FRONTEND_LNB_UNICABLE,                /**<Unicable LNB *//**<CNcomment:unicable高频头*/
    FRONTEND_LNB_TYPE_BUTT                /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_LNB_TYPE_E;

/** LNB band type*//** CNcomment:卫星信号频段*/
typedef enum _FRONTEND_LNB_BAND_E
{
    FRONTEND_LNB_BAND_C = 0,              /**<C *//**<CNcomment:C波段*/
    FRONTEND_LNB_BAND_KU,                 /**<Ku *//**<CNcomment:Ku波段*/
    FRONTEND_LNB_BAND_BUTT                /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_LNB_BAND_E;

/**LNB Power (satellite, Ter)  *//** CNcomment:LNB供电开关(卫星,地面) FRONTEND_LNB_POWER_AUTO: 可以不实现.*/
typedef enum _FRONTEND_LNB_POWER_E
{
    FRONTEND_LNB_POWER_OFF = 0,           /**<LNB_POWER_OFF *//**<CNcomment:LNB_POWER_OFF*/
    FRONTEND_LNB_POWER_ON,                /**<LNB power auto, 13V/18V, default*/                                  /**<CNcomment:默认的13/18V供电*/
    FRONTEND_LNB_POWER_ENHANCED,          /**<LNB power auto, 14V/19V, some LNB control device can support.*/     /**<CNcomment:加强供电*/
    FRONTEND_LNB_POWER_AUTO,              /**<LNB_POWER_AUTO *//**<CNcomment:LNB_POWER_AUTO*/
    FRONTEND_LNB_POWER_BUTT
} FRONTEND_LNB_POWER_E;

/**FRONTEND rolloff (satellite)  *//** CNcomment:滚降系数(卫星).*/
typedef enum _FRONTEND_ROLLOFF_E
{
    FRONTEND_ROLLOFF_35 = 0,              /**<ROLLOFF_35 *//**<CNcomment:ROLLOFF_35*/
    FRONTEND_ROLLOFF_25,                  /**<ROLLOFF_25 *//**<CNcomment:ROLLOFF_25*/
    FRONTEND_ROLLOFF_20,                  /**<ROLLOFF_20 *//**<CNcomment:ROLLOFF_20*/
    FRONTEND_ROLLOFF_BUTT
} FRONTEND_ROLLOFF_E;

/**FRONTEND POLARIZATION (satellite)  *//** CNcomment:极化方式(卫星).*/
typedef enum _FRONTEND_POLARIZATION_E
{
    FRONTEND_PLR_HORIZONTAL = 0,  /**<HORIZONTAL *//**<CNcomment:水平极化*/
    FRONTEND_PLR_VERTICAL,    /**<VERTICAL *//**<CNcomment:垂直极化*/
    FRONTEND_PLR_LEFT,        /**<LEFT *//**<CNcomment:左极化*/
    FRONTEND_PLR_RIGHT,       /**<RIGHT *//**<CNcomment:右极化*/
    FRONTEND_PLR_AUTO,    /**<AUTO *//**<CNcomment:自动极化方式*/
    FRONTEND_PLR_BUTT
} FRONTEND_POLARIZATION_E;

/**FRONTEND 12V out switch (satellite)  *//** CNcomment:12V控制(卫星).*/
typedef enum _FRONTEND_LNB_12V_E
{
    FRONTEND_LNB_12V_OFF = 0, /**<12V off*//**<CNcomment:12V off*/
    FRONTEND_LNB_12V_ON,      /**<12V on *//**<CNcomment:12V on*/
    FRONTEND_LNB_12V_AUTO,    /**<12V auto *//**<CNcomment:12V auto*/
    FRONTEND_LNB_12V_BUTT
} FRONTEND_LNB_12V_E;

/** 0/12V switch*//** CNcomment:0/12V开关*/
typedef enum _FRONTEND_SWITCH_0_12V_E
{
    FRONTEND_SWITCH_0_12V_NONE = 0,         /**< None, default*//**<CNcomment:不接开关状态*/
    FRONTEND_SWITCH_0_12V_0,                /**< 0V*//**<CNcomment:0V状态*/
    FRONTEND_SWITCH_0_12V_12,               /**< 12V*//**<CNcomment:12V状态*/
    FRONTEND_SWITCH_0_12V_BUTT              /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_SWITCH_0_12V_E;

/**FRONTEND 22K out descripe LNB(satellite)  *//** CNcomment:22k输出控制(卫星).*/
typedef enum _FRONTEND_LNB_22K_E
{
    FRONTEND_LNB_22K_OFF = 0,               /**<22K_OFF*//**<CNcomment:22K_OFF*/
    FRONTEND_LNB_22K_ON,                    /**<22K_ON*//**<CNcomment:22K_ON*/
    FRONTEND_LNB_22K_AUTO,                  /**<22K_AUTO*//**<CNcomment:22K_AUTO*/
    FRONTEND_LNB_22K_BUTT
} FRONTEND_LNB_22K_E;

/** 22KHz switch*//** CNcomment:22K开关控制*/
typedef enum _FRONTEND_SWITCH_22K_E
{
    FRONTEND_SWITCH_22K_NONE = 0,            /**< None, default*//**<CNcomment:不接开关状态*/
    FRONTEND_SWITCH_22K_OFF,                 /**< 0*//**<CNcomment:0kHz端口*/
    FRONTEND_SWITCH_22K_ON,                  /**< 22KHz*//**<CNcomment:22kHz端口*/
    FRONTEND_SWITCH_22K_BUTT                 /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_SWITCH_22K_E;

/** Tone burst switch*/
/** CNcomment:Tone burst开关*/
typedef enum _FRONTEND_SWITCH_TONEBURST_E
{
    FRONTEND_SWITCH_TONEBURST_NONE = 0,      /**< Don't send tone burst, default*//**<CNcomment:不接开关状态*/
    FRONTEND_SWITCH_TONEBURST_0,             /**< Tone burst 0*//**<CNcomment:0 port*/
    FRONTEND_SWITCH_TONEBURST_1,             /**< Tone burst 1*//**<CNcomment:1 port*/
    FRONTEND_SWITCH_TONEBURST_BUTT           /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_SWITCH_TONEBURST_E;

/** DiSEqC Switch port*/
/** CNcomment:DiSEqC开关端口枚举*/
typedef enum _FRONTEND_DISEQC_SWITCH_PORT_E
{
    FRONTEND_DISEQC_SWITCH_NONE = 0,         /**<none*//**<CNcomment:不接开关*/
    FRONTEND_DISEQC_SWITCH_PORT_1,           /**<port1*//**<CNcomment:端口1*/
    FRONTEND_DISEQC_SWITCH_PORT_2,           /**<port2*//**<CNcomment:端口2*/
    FRONTEND_DISEQC_SWITCH_PORT_3,           /**<port3*//**<CNcomment:端口3*/
    FRONTEND_DISEQC_SWITCH_PORT_4,           /**<port4*//**<CNcomment:端口4*/
    FRONTEND_DISEQC_SWITCH_PORT_5,           /**<port5*//**<CNcomment:端口5*/
    FRONTEND_DISEQC_SWITCH_PORT_6,           /**<port6*//**<CNcomment:端口6*/
    FRONTEND_DISEQC_SWITCH_PORT_7,           /**<port7*//**<CNcomment:端口7*/
    FRONTEND_DISEQC_SWITCH_PORT_8,           /**<port8*//**<CNcomment:端口8*/
    FRONTEND_DISEQC_SWITCH_PORT_9,           /**<port9*//**<CNcomment:端口9*/
    FRONTEND_DISEQC_SWITCH_PORT_10,          /**<port10*//**<CNcomment:端口10*/
    FRONTEND_DISEQC_SWITCH_PORT_11,          /**<port11*//**<CNcomment:端口11*/
    FRONTEND_DISEQC_SWITCH_PORT_12,          /**<port12*//**<CNcomment:端口12*/
    FRONTEND_DISEQC_SWITCH_PORT_13,          /**<port13*//**<CNcomment:端口13*/
    FRONTEND_DISEQC_SWITCH_PORT_14,          /**<port14*//**<CNcomment:端口14*/
    FRONTEND_DISEQC_SWITCH_PORT_15,          /**<port15*//**<CNcomment:端口15*/
    FRONTEND_DISEQC_SWITCH_PORT_16,          /**<port16*//**<CNcomment:端口16*/
    FRONTEND_DISEQC_SWITCH_PORT_BUTT         /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_DISEQC_SWITCH_PORT_E;

/**FRONTEND Diseqc cmd (satellite)  *//** CNcomment:Diseqc协议(卫星).*/
typedef enum _FRONTEND_LNB_DISEQC_CMD_E
{
    FRONTEND_DISEQC_COMMAND = 0,                  /**< DiSEqC (1.2/2)command   *//**<CNcomment:DiSEqC (1.2/2)命令*/
    FRONTEND_DISEQC_TONE_BURST_UNMODULATED = 5,   /**<TONE_BURST_UNMODULATED*//**<CNcomment:TONE_BURST_UNMODULATED*/
    FRONTEND_DISEQC_TONE_BURST_MODULATED   = 6,   /**<TONE_BURST_MODULATED*//**<CNcomment:TONE_BURST_MODULATED*/

    FRONTEND_DISEQC_TONE_BURST_SEND_0_UNMODULATED = FRONTEND_DISEQC_TONE_BURST_UNMODULATED,      /**< send of 0 for 12.5 ms ;continuous tone*<CNcomment:TONE_BURST_UNMODULATED*/
    FRONTEND_DISEQC_TONE_BURST_SEND_0_MODULATED   = FRONTEND_DISEQC_TONE_BURST_MODULATED,        /**< 0-2/3 duty cycle tone*<CNcomment:TONE_BURST_MODULATED*/

    FRONTEND_DISEQC_BUTT
} FRONTEND_LNB_DISEQC_CMD_E;

/**FRONTEND Diseqc Ver (satellite)  *//** CNcomment:Diseqc版本(卫星).*/
typedef enum _FRONTEND_DISEQC_VER_E
{
    FRONTEND_DISEQC_VER_NONE = 0,    /**< not support */ /**<CNcomment:不支持*/

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

/**(Satellite) FRONTEND lnb command type，can use "|" to set more commands *//** CNcomment:LNB控制命令类型(卫星),如果同时对多个项目进行设置，可采用"或"操作.*/
typedef enum _FRONTEND_LNB_CMD_TYPE_E
{
    FRONTEND_LNB_CMD_SET_PWR    = 1,     /**< set Lnb Power  */ /**<CNcomment: 设置LNB电源开关*/
    FRONTEND_LNB_CMD_SET_POL    = 2,     /**< set lnb pol */ /**<CNcomment: 设置极化方式*/
    FRONTEND_LNB_CMD_SET_22K    = 4,     /**< Set lnb 22K  */ /**<CNcomment: 设置22K开关*/
    FRONTEND_LNB_CMD_SET_12V    = 8,     /**< set lnb 12V  */ /**<CNcomment: 设置12V开关*/
    FRONTEND_LNB_CMD_SET_DISQ   = 16,    /**< set lnb disqc  */ /**<CNcomment: 设置diseqc*/
    FRONTEND_LNB_CMD_BUTT
} FRONTEND_LNB_CMD_TYPE_E;

/** control type for antenna independent control*//** CNcomment:天线单独设置类型 */
typedef enum _FRONTEND_ANTENNA_CMD_TYPE_E
{
    //for all antenna
    FRONTEND_EXTRA_ANTENNA_CONFIG_ALL = 0,     /**<Reference:FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S*//**<CNcomment:请参考FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S*/

    FRONTEND_SET_LNB_POWER,
    FRONTEND_SET_SWITCH_22K,
    //for diseqc switch
    FRONTEND_DISEQC_SWITCH_4PORT,        /**<Reference:FRONTEND_DISEQC_SWITCH4PORT_S*//**<CNcomment:请参考FRONTEND_DISEQC_SWITCH4PORT_S*/
    FRONTEND_DISEQC_SWITCH_16PORT,       /**<Reference:FRONTEND_DISEQC_SWITCH16PORT_S*//**<CNcomment:请参考FRONTEND_DISEQC_SWITCH16PORT_S*/

    //for Satellite motor
    FRONTEND_MOTOR_SET_COORDINATE,       /**<Reference:FRONTEND_COORDINATE_S  *//**<CNcomment:请参考FRONTEND_COORDINATE_S*/
    FRONTEND_MOTOR_STORE_POSITION,       /**<Reference:FRONTEND_MOTOR_POSITION_S*//**<CNcomment:请参考FRONTEND_MOTOR_POSITION_S*/
    FRONTEND_MOTOR_GOTO_POSITION,        /**<Reference:FRONTEND_MOTOR_POSITION_S*//**<CNcomment:请参考FRONTEND_MOTOR_POSITION_S*/
    FRONTEND_MOTOR_LIMIT,                /**<Reference:FRONTEND_MOTOR_LIMIT_S*//**<CNcomment:请参考FRONTEND_MOTOR_LIMIT_S*/
    FRONTEND_MOTOR_MOVE,                 /**<Reference:FRONTEND_MOTOR_MOVE_S*//**<CNcomment:请参考FRONTEND_MOTOR_MOVE_S*/
    FRONTEND_MOTOR_STOP,                 /**<Reference:FRONTEND_DISEQC_VER_E*//**<CNcomment:请参考FRONTEND_DISEQC_VER_E*/
    FRONTEND_MOTOR_CALC_ANGULAR,         /**<Reference:FRONTEND_MOTOR_CALC_ANGULAR_S [in/out]*//**<CNcomment:请参考FRONTEND_MOTOR_CALC_ANGULAR_S [in/out]*/
    FRONTEND_MOTOR_GOTO_ANGULAR,         /**<Reference:FRONTEND_MOTOR_USALS_ANGULAR_S*//**<CNcomment:请参考FRONTEND_MOTOR_USALS_ANGULAR_S*/
    //FRONTEND_MOTOR_RECALCULATE,        /**<Reference:FRONTEND_DISEQC_RECALCULATE_S*//**<CNcomment:请参考FRONTEND_DISEQC_RECALCULATE_S*/
    //FRONTEND_MOTOR_RESET,              /**<Reference:FRONTEND_DISEQC_VER_E*//**<CNcomment:请参考FRONTEND_DISEQC_VER_E*/
    FRONTEND_MOTOR_SET_MANUAL,

    //for unicale lnb
    FRONTEND_UNICABLE_SCAN_USERBANDS,     /**< scan 950~2150 frequency range,and find out the user bands. Can set FRONTEND_REG_UNICABLE_SCAN_CALLBACK get scan status and data *//**<CNcomment:扫描950-2150找出用户频带, 可以设置FRONTEND_REG_UNICABLE_SCAN_CALLBACK回调函数获取状态和数据*/
    FRONTEND_UNICABLE_EXIT_SCANUSERBANDS, /**< stop scan frequency range, No need param*//**<CNcomment:停止扫描用户频段*/
    FRONTEND_UNICABLE_GET_USERBANDSINFO,  /**< Copy scanned results,get user bands information. Data type FRONTEND_UNICABLE_USERBANDS_S*.*//**<CNcomment:获取扫描结果，获取用户频带信息，FRONTEND_UNICBALE_USERBANDS_S*.*/
    FRONTEND_ANTENNA_CMD_BUTT
} FRONTEND_ANTENNA_CMD_TYPE_E;

/** motor protocol *//** CNcomment:马达协议 */
typedef enum _FRONTEND_MOTORTYPE_E
{
    FRONTEND_MOTOR_NONE = 0,               /**<None*//**<CNcomment:不使用马达*/
    FRONTEND_MOTOR_DISEQC12,               /**<DiSEqC1.2 protocol*//**<CNcomment:DiSEqC1.2协议*/
    FRONTEND_MOTOR_USLAS,                  /**<USLAS protocol*//**<CNcomment:DiSEqC1.3或USLAS协议*/
    FRONTEND_MOTOR_BUTT
} FRONTEND_MOTORTYPE_E;

/** DiSEqC motor limit setting*//** CNcomment:DiSEqC马达极限设置*/
typedef enum _FRONTEND_MOTOR_LIMIT_E
{
    FRONTEND_MOTOR_LIMIT_OFF = 0,          /**<Disable Limits*//**<CNcomment:无限制*/
    FRONTEND_MOTOR_LIMIT_EAST,             /**<Set East Limit*//**<CNcomment:东向限制*/
    FRONTEND_MOTOR_LIMIT_WEST,             /**<Set West Limit*//**<CNcomment:西向限制*/
    FRONTEND_MOTOR_LIMIT_BUTT              /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_MOTOR_LIMIT_E;

/** Difinition of DiSEqC motor move direction*//** CNcomment:DiSEqC马达移动方向*/
typedef enum _FRONTEND_MOTOR_MOVE_DIR_E
{
    FRONTEND_MOTOR_MOVE_DIR_EAST = 0,      /**<Move east*//**<CNcomment:向东移动*/
    FRONTEND_MOTOR_MOVE_DIR_WEST,          /**<Move west*//**<CNcomment:向西移动*/
    FRONTEND_MOTOR_MOVE_DIR_BUTT           /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_MOTOR_MOVE_DIR_E;

/** unicable multi-switch port.*//** CNcomment:unicable开关端口枚举*/
typedef enum _FRONTEND_UNICABLE_SATPOSITION_E
{
    FRONTEND_UNICABLE_SATPOSN_A = 0,       /**<unicable switch port A*//**<CNcomment:端口A*/
    FRONTEND_UNICABLE_SATPOSN_B,           /**<unicable switch port B*//**<CNcomment:端口B*/
    FRONTEND_UNICABLE_SATPOSN_BUT          /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_UNICABLE_SATPOSITION_E;

/////    DVB-S enmu end     ////////////////////////////////////////////

/**(Satellite Ter Cable) FEC *//** CNcomment:前向纠错率，码率(卫星、地面、有线).*/
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

/**MODULATION *//** CNcomment:调制方式.*/
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

/**FRONTEND SPECTRUM (Cable TER)*//** CNcomment:频谱反转控制(有线,地面).*/
typedef enum _FRONTEND_SPECTRUM_E
{
    FRONTEND_SPECTRUM_INVERSION_OFF  = 1,       /**<off*//**<CNcomment:off*/
    FRONTEND_SPECTRUM_INVERSION      = 2,       /**<on*//**<CNcomment:on*/
    FRONTEND_SPECTRUM_INVERSION_AUTO = 4,       /**<AUTO*//**<CNcomment:AUTO*/
    FRONTEND_SPECTRUM_INVERSION_UNK  = 8,       /**<UNK*//**<CNcomment:UNK*/
    FRONTEND_SPECTRUM_INVERSION_BUTT
} FRONTEND_SPECTRUM_E;

/**FRONTEND band width (Cable TER)*//** CNcomment:传输带宽(地面、有线).*/
typedef enum _FRONTEND_BAND_WIDTH_E
{
    FRONTEND_BANDWIDTH_8_MHZ = 0,        /**<BANDWIDTH_8_MHZ*//**<CNcomment:BANDWIDTH_8_MHZ*/
    FRONTEND_BANDWIDTH_7_MHZ,            /**<BANDWIDTH_7_MHZ*//**<CNcomment:BANDWIDTH_7_MHZ*/
    FRONTEND_BANDWIDTH_6_MHZ,            /**<BANDWIDTH_6_MHZ*//**<CNcomment:BANDWIDTH_6_MHZ*/
    FRONTEND_BANDWIDTH_BUTT
} FRONTEND_BAND_WIDTH_E;

/**FRONTEND transmit mod (TER)*//** CNcomment:传输模式(地面).*/
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

/**FRONTEND guard interval (TER, C2)*//** CNcomment:保护间隔(地面,C2).*/
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
/** CNcomment:仅用于DVB-T*/
typedef enum _FRONTEND_TER_TS_PRIORITY_E
{
    FRONTEND_TER_TS_PRIORITY_NONE = 0,      /**<no priority mode*/          /**<CNcomment:无优先级模式*/
    FRONTEND_TER_TS_PRIORITY_HP,            /**<high priority mode*/        /**<CNcomment:高优先级模式*/
    FRONTEND_TER_TS_PRIORITY_LP,            /**<low priority mode*/         /**<CNcomment:低优先级模式*/
    FRONTEND_TER_TS_PRIORITY_BUTT           /**<Invalid value*/             /**<CNcomment:非法边界值*/
} FRONTEND_TER_TS_PRIORITY_E;

/** base channel or lite channel, only used in DVB-T2*/
/** CNcomment:仅用于DVB-T2*/
typedef enum _FRONTEND_TER2_MODE_E
{
    FRONTEND_TER2_MODE_BASE = 0,     /**< the channel is base mode*/         /**<CNcomment:通道中仅支持base信号*/
    FRONTEND_TER2_MODE_LITE,         /**< the channel is lite mode*/         /**<CNcomment:通道中需要支持lite信号*/
    FRONTEND_TER2_MODE_BUTT      /**<Invalid value*/            /**<CNcomment:非法边界值*/
} FRONTEND_TER2_MODE_E;

/** PLP type of DVB-T2.*//** CNcomment:T2下物理层管道类型*/
typedef enum _FRONTEND_TER2_PLP_TYPE_E
{
    FRONTEND_TER2_PLP_TYPE_COM = 0,       /**<common type*//**<CNcomment:普通*/
    FRONTEND_TER2_PLP_TYPE_DAT1,          /**<data1 type*//**<CNcomment:数据1*/
    FRONTEND_TER2_PLP_TYPE_DAT2,          /**<data2 type*//**<CNcomment:数据2*/
    FRONTEND_TER2_PLP_TYPE_BUTT           /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_TER2_PLP_TYPE_E;

/**FRONTEND callback status (TER, C2)*//** CNcomment:配置回调函数状态.*/
typedef enum _FRONTEND_CFG_CALLBACK_E
{
    FRONTEND_CALLBACK_ENABLE = 0,         /**< enable*//**<CNcomment: 启用*/
    FRONTEND_CALLBACK_DISABLE,            /**< disable*//**<CNcomment: 失效*/
    FRONTEND_CALLBACK_REMOVE              /**< remove*//**<CNcomment: 移除*/
} FRONTEND_CFG_CALLBACK_E;

/**FRONTEND open params*//** CNcomment:设备启动参数.*/
typedef struct _FRONTEND_OPEN_PARAMS_S
{
    U32 u32FrontendIndex;                 /**< witch tuner to open*//**<CNcomment: 打开哪一个tuner，当有相同类型tuner时需要指定打开哪一个*/
    FRONTEND_FE_TYPE_E   enFeType;        /**< init tuner this type*//**<CNcomment: 初始化tuner为此类型*/
    FRONTEND_FEC_RATE_E  enFecRate;       /**< Fec Rate*//**<CNcomment: Fec Rate*/
} FRONTEND_OPEN_PARAMS_S;

/** FRONTEND LNB Power status *//** CNcomment:LNB供电状态. */
typedef enum _FRONTEND_LNB_PWR_STATUS_E
{
    FRONTEND_LNB_PWR_STATUS_ON = 0,                 /**< Normal on*//**<CNcomment: 打开的正常状态*/
    FRONTEND_LNB_PWR_STATUS_OFF,                    /**< Power off*//**<CNcomment: 关闭的正常状态*/
    FRONTEND_LNB_PWR_STATUS_SHORT_CIRCUIT,          /**< Short circuit *//**<CNcomment: LNB输出电路被短路*/
    FRONTEND_LNB_PWR_STATUS_OVER_TEMPERATURE,       /**< Over termperature  *//**<CNcomment:LNB输出模块温度太高*/
    FRONTEND_LNB_PWR_STATUS_LOW_VOLTAGE,            /**< Low voltage *//**<CNcomment: LNB输出电压太低*/
    FRONTEND_LNB_PWR_STATUS_OVER_VOLTAGE,           /**< Over voltage *//**<CNcomment:  LNB输出电压太高*/
    FRONTEND_LNB_PWR_STATUS_BUTT
} FRONTEND_LNB_PWR_STATUS_E;

/** FRONTEND Control ts out cmd *//** CNcomment:控制输出码流的命令. */
typedef enum _FRONTEND_TSOUT_CMD_TYPE_E
{
    //for T2
    FRONTEND_TSOUT_TER2_GET_PLPNUM = 0,             /**< Get the PLP number, data type U8*//**<CNcomment:得到PLP的数目,类型U8*/
    FRONTEND_TSOUT_TER2_GET_PLP_TYPE,               /**< Get PLP type, Reference:FRONTEND_TER2_PLP_TYPE_E*//**<CNcomment:得到PLP的类型,FRONTEND_TER2_PLP_TYPE_E*/
    FRONTEND_TSOUT_TER2_GET_PLP_GROUPID,            /**< PLP group ID, data type U8*//**<CNcomment:得到PLP group ID,类型U8*/
    FRONTEND_TSOUT_TER2_SET_PLP_MODE,               /**< Sets PLP read or write mode, data type U8*, 1-read, 0-write. *//**<CNcomment:设置物理层管道读写模式，类型U8* 1-读模式，0-切换模式。*/
    FRONTEND_TSOUT_TER2_SET_PLPID,                  /**< PLP ID, data type U8*//**<CNcomment:传入PLPID,类型U8*/
    FRONTEND_TSOUT_TER2_SET_COMMON_PLPID,           /**< Sets common plp id, data type U8* plp id. *//**<CNcomment:设置共享物理层管道ID。类型U8* */
    FRONTEND_TSOUT_TER2_SET_COMPLP_COMB,            /**< Sets common plp and data plp combination flag, data type U8*, 1-combinate, 0-no need. *//**<CNcomment:设置共享物理层管道和数据物理层管道是否需要组合标志，类型U8* 1-组合，0-不组合。*/

    //for S2 mutiple Transport Streams
    FRONTEND_TSOUT_SAT2_GET_ISINUM,                 /**< Get the streams number, data type U8*//**<CNcomment:得到PLP的数目,类型U8*/
    FRONTEND_TSOUT_SAT2_GET_ISIID,                  /**< Get ISI ID, data type FRONTEND_SAT2_ISIID_S* *//**<CNcomment:传入FRONTEND_SAT2_ISIID_S* */
    FRONTEND_TSOUT_SAT2_SET_ISIID,                  /**< Set ISI ID, data type U8*//**<CNcomment:传入PLPID,类型U8*/

    //For ISDB-T
    FRONTEND_TSOUT_ISDBT_GET_TMCC_INFO,             /**< Get TMCC infomation about ISDB-T signal, date type FRONTEND_ISDBT_TMCC_INFO_S *//**<CNcomment:获取ISDB-T信号的TMCC信息,参数类型FRONTEND_ISDBT_TMCC_INFO_S*/

    FRONTEND_TSOUT_CMD_END
} FRONTEND_TSOUT_CMD_TYPE_E;

/** Parameter for ISDB-T TMCC information*/
/** CNcomment:ISDB-T模式下，TMCC 信息*/
typedef struct _FRONTEND_ISDBT_TMCC_INFO_S
{
    U8 u8EmergencyFlag;      /**<the start flag for emergency alarm broadcasting*//**<CNcomment:紧急报警播报开始标志*/
    U8 u8PartialFlag;        /**<partial reception flag*//**<CNcomment:部分接收标志*/
    U8 u8PhaseShiftCorr;     /**<phase shift correction value for connected segment transmission*//**<CNcomment:相位偏移值*/
    U8 u8IsdbtSystemId;      /**<system identification[0 = ISDB_T,1 = ISDB_T_SB]*//**<CNcomment:系统标识*/
} FRONTEND_ISDBT_TMCC_INFO_S;

/** Parameter for DiSEqC 1.0/2.0 switch
   Some DiSEqC device need set polarization(13/18V) and 22K, you can set them here. */
/** CNcomment:DiSEqC 1.0/2.0 开关参数
   有些DiSEqC设备需要设置极化方式和22K的，如果用了这种设备，需要在这里设置 */
typedef struct _FRONTEND_DISEQC_SWITCH4PORT_S
{
    FRONTEND_DISEQC_VER_E            enLevel;       /**<DiSEqC device level*//**<CNcomment:器件版本*/
    FRONTEND_DISEQC_SWITCH_PORT_E    enPort;        /**<DiSEqC switch port*//**<CNcomment:选通端口号*/
    FRONTEND_POLARIZATION_E          enPolar;       /**<Polarization type *//**<CNcomment:极化方式*/
    FRONTEND_LNB_22K_E               enLNB22K;      /**<22K status*//**<CNcomment:22k状态*/
} FRONTEND_DISEQC_SWITCH4PORT_S;

/** Parameter for DiSEqC 1.1/2.1 switch *//** CNcomment:DiSEqC 1.1/2.1 开关参数 */
typedef struct _FRONTEND_DISEQC_SWITCH16PORT_S
{
    FRONTEND_DISEQC_VER_E             enLevel;      /**<DiSEqC device level*//**<CNcomment:器件版本*/
    FRONTEND_DISEQC_SWITCH_PORT_E     enPort;       /**<DiSEqC switch port*//**<CNcomment:选通端口号*/
} FRONTEND_DISEQC_SWITCH16PORT_S;

/** coordinate *//** CNcomment:本地经纬度 */
typedef struct _FRONTEND_COORDINATE_S
{
    U16  u16MyLongitude;                  /**<local longitude, is 10*longitude, in param, E:0-1800, W:1800-3600(3600-longtitude) *//**<CNcomment:本地经度*/
    U16  u16MyLatitude;                   /**<local latitude, is 10*latitude, in param N:0-900, S:900-1800(1800-latitude)*//**<CNcomment:本地纬度*/
} FRONTEND_COORDINATE_S;

/** Parameter for DiSEqC motor store position*//** CNcomment:天线存储位置参数*/
typedef struct _FRONTEND_MOTOR_POSITION_S
{
    FRONTEND_DISEQC_VER_E enLevel;        /**<DiSEqC device level*//**<CNcomment:器件版本*/
    U32                   u32Pos;         /**<Index of position, 0-255*//**<CNcomment:位置序号*/
} FRONTEND_MOTOR_POSITION_S;

/** Parameter for DiSEqC motor limit setting*//** CNcomment:天线Limit设置参数*/
typedef struct _FRONTEND_MOTOR_LIMIT_S
{
    FRONTEND_DISEQC_VER_E enLevel;        /**<DiSEqC device level*//**<CNcomment:器件版本*/
    FRONTEND_MOTOR_LIMIT_E enLimit;       /**<Limit setting*//**<CNcomment:限制设定*/
} FRONTEND_MOTOR_LIMIT_S;

/** Parameter for DiSEqC motor moving*//** CNcomment:DiSEqC马达移动参数*/
typedef struct _FRONTEND_MOTOR_MOVE_S
{
    FRONTEND_DISEQC_VER_E      enLevel;   /**<DiSEqC device level*//**<CNcomment:器件版本*/
    FRONTEND_MOTOR_MOVE_DIR_E  enDir;     /**<Moving direction*//**<CNcomment:移动方向*/
    U32                        u32RunningSteps;    /**<0 mean running continus;1~128 mean running steps every time.*//**<CNcomment:0表示持续转动；1~128之间表示每次转动step数，*/
} FRONTEND_MOTOR_MOVE_S;

/** calculate angular *//** CNcomment:计算角度 */
typedef struct _FRONTEND_MOTOR_CALC_ANGULAR_S
{
    U16 u16SatLongitude;                  /**<sat longitude, is 10*longitude, in param, E:0-1800, W:1800-3600(3600-longtitude)  *//**<CNcomment:卫星所在经度*/
    U16 u16Angular;                       /**<calculate result, out param, if the result is larger than 850, return FAILURE according to the device limitation*//**<CNcomment:计算后得到的角度*/
} FRONTEND_MOTOR_CALC_ANGULAR_S;

/** Parameter for USALS goto angular*//** CNcomment:USALS角度参数*/
typedef struct _FRONTEND_MOTOR_USALS_ANGULAR_S
{
    FRONTEND_DISEQC_VER_E  enLevel;       /**<DiSEqC device level*//**<CNcomment:器件版本*/
    U32                    u32Angular;    /**<Angular, calculated by FRONTEND_MOTOR_CALC_ANGULAR cmd*//**<CNcomment:角度值，可通过函数FRONTEND_MOTOR_CALC_ANGULAR 命令调用SDK计算得到*/
} FRONTEND_MOTOR_USALS_ANGULAR_S;

/** LNB configurating parameters*//** CNcomment:LNB配置参数*/
typedef struct _FRONTEND_SAT_LNB_CONFIG_S
{
    FRONTEND_LNB_TYPE_E  enLNBType;                   /**<LNB type*//**<CNcomment:LNB类型*/
    U32                  u32LowLO;                    /**< Low Local Oscillator Frequency, MHz *//**<CNcomment:LNB低本振频率，单位MHz*/
    U32                  u32HighLO;                   /**< High Local Oscillator Frequency, MHz*//**<CNcomment:LNB高本振频率，单位MHz*/
    FRONTEND_LNB_BAND_E  enLNBBand;                   /**< LNB band, C or Ku *//**<CNcomment:LNB波段：C或Ku*/
    U32                  u32UNIC_SCRNO;               /**< SCR number, 0-7 *//**<CNcomment:SCR序号，取值为0-7*/
    U32                  u32UNICIFFreqMHz;            /**< SCR IF frequency, unit MHz *//**<CNcomment:SCR中频频率， 单位MHz*/
    FRONTEND_UNICABLE_SATPOSITION_E enSatPosn;        /**< unicable multi-switch port *//**<CNcomment:unicable开关端口号*/
} FRONTEND_SAT_LNB_CONFIG_S;

/** satellite antenna parameter *//** CNcomment:卫星天线参数 */
typedef struct _FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S
{
    FRONTEND_SWITCH_22K_E         enSwitch22K;        /**<22k switch */ /**<CNcomment:22k开关  FRONTEND_SWITCH_22K_E*/
    FRONTEND_SWITCH_TONEBURST_E   enToneburst;        /**<Switch of Tone burst : Reference: FRONTEND_SWITCH_TONEBURST_E. */ /**CNcomment:Tone burst开关。参考 FRONTEND_SWITCH_TONEBURST_E*/
    FRONTEND_SWITCH_0_12V_E       enSwitch12V;        /**<Switch of 12V Reference: FRONTEND_SWITCH_0_12V_E*//**CNcomment:12V开关，一般不用。 参考FRONTEND_SWITCH_0_12V_E  */
    FRONTEND_DISEQC_VER_E         enDiSEqCLevel;      /**<DiSEqC device level*/            /**<CNcomment:器件版本*/
    FRONTEND_DISEQC_SWITCH_PORT_E enPort4;            /**<1~4 switch Reference: FRONTEND_DISEQC_SWITCH_PORT_E For DISEQC_SWITCH4PORT, diseqc1.0 *//**<CNcomment:四切一开关,参考FRONTEND_DISEQC_SWITCH_PORT_E*/
    FRONTEND_DISEQC_SWITCH_PORT_E enPort16;           /**<1~16 switch Reference: FRONTEND_DISEQC_SWITCH_PORT_E For DISEQC_SWITCH16PORT, diseqc1.1*//**<CNcomment:十六切一开关,参考FRONTEND_DISEQC_SWITCH_PORT_E*/
    FRONTEND_MOTORTYPE_E          enMotorType;        /**<Reference FRONTEND_MOTORTYPE_E*/ /**CNcomment:参考FRONTEND_MOTORTYPE_E */
    U32                           u32Longitude;       /**<Longitude */ /**<CNcomment:卫星所在经度*/
    U32                           u32MotoPos;         /**<Motor position*/ /**CNcomment:  马达位置编号,最多存256个马达位置，受限于马达硬件存储容量*/
} FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S;

typedef struct _FRONTEND_UNICABLE_SCR_UB_S   //for unicable
{
    U32      u32SCRNo;                                /**<user band number of unicable*//**<CNcomment:unicable的用户频段号*/
    S32      s32CenterFreq;                           /**<user band frequency of unicable,unit MHz*//**<CNcomment:unicable的用户频段中心频率,单位MHz*/
} FRONTEND_UNICABLE_SCR_UB_S;

/** for unicable getting parameter *//** CNcomment:unicable LNB 扫描信息获取用数据结构 */
typedef struct _FRONTEND_UNICABLE_USERBANDS_S
{
    FRONTEND_UNICABLE_SCR_UB_S**  ppUserBandsinfo;    /**<point to array which type is FRONTEND_UNICABLE_SCR_UB_S*//**<CNcomment:unicable用户频段存储数组的指针*/
    U32*                          pu32Num;            /**<size of the array *//**<CNcomment:该数组的大小*/
} FRONTEND_UNICABLE_USERBANDS_S;

/** for S2 FRONTEND_TSOUT_SAT2_GET_ISIID parameter *//** CNcomment:FRONTEND_TSOUT_SAT2_GET_ISIID 获取ISIID 参数  */
typedef struct _FRONTEND_SAT2_ISIID_S
{
    U8 u8StreamNum;      /**<input parameter, streamNum*/
    U8 u8IsiID;          /**<output parameter, Get streamNumID according to StreamNum*/
} FRONTEND_SAT2_ISIID_S;

/** FRONTEND LNB ctrl info *//** CNcomment:LNB控制参数.*/
typedef struct _FRONTEND_SAT_LNB_INFO_S
{
    FRONTEND_LNB_CMD_TYPE_E   enCmdType;              /**< cmd type *//**<CNcomment: 命令类型*/
    FRONTEND_LNB_POWER_E      enLnbPower;             /**< lnb power*//**<CNcomment: lnb 的供电状态*/
    FRONTEND_POLARIZATION_E   enPolarization;         /**< polarization*//**<CNcomment: 极化*/
    FRONTEND_LNB_12V_E        enLnb12vState;          /**< lnb 12v state*//**<CNcomment: 12V控制状态*/
    FRONTEND_LNB_22K_E        enLnb22kState;          /**< lnb 22k state*//**<CNcomment: 22k 状态*/
    FRONTEND_LNB_DISEQC_CMD_E enDiseqcCmd;            /**< diseqc cmd*//**<CNcomment: DiSEqC 状态*/
    BOOL                      bDiseqcNeedResponse;    /**< need response */ /**<CNcomment: 是否需要diseqc回应(diseqc2.x).TRUE:response;FALSE:not response*/
    U32                       u32DiseqcDataLen;       /**< TRUE must set this lenth *//**<CNcomment: diseqc控制数据长度bytes.如果is_diseqc_response=TRUE,配置diseqc后,存储回应diseqc的长度*/
    U8*                       pDiseqcData;            /**< data for response *//**<CNcomment: diseqc控制数据.如果is_diseqc_response=TRUE,配置diseqc后, 存储回应数据,此时缓冲区大小>=6bytes*/
} FRONTEND_SAT_LNB_INFO_S;

/** Definition of blind scan event type*/
/** CNcomment:TUNER盲扫事件*/
typedef enum _FRONTEND_SAT_BLINDSCAN_EVT_E
{
    FRONTEND_SAT_BLINDSCAN_EVT_STATUS = 0,            /**<New status*//**<CNcomment:状态变化*/
    FRONTEND_SAT_BLINDSCAN_EVT_PROGRESS,              /**<New Porgress *//**<CNcomment:进度变化*/
    FRONTEND_SAT_BLINDSCAN_EVT_NEWRESULT,             /**<Find new channel*//**<CNcomment:新频点*/
    FRONTEND_SAT_BLINDSCAN_EVT_BUTT                   /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_SAT_BLINDSCAN_EVT_E;

/** Satellite TP Info of blindscan result *//**CNcomment: 卫星盲扫结果*/
typedef struct _FRONTEND_SAT_BLINDSCAN_TP_INFO_S
{
    //U32 u32IfFreq;                                  /**<If freq *//**<CNcomment: 中频频率,需要和本振运算得到TP 频点,单位KHz */
    U32                      u32Freq;                 /**<freq *//**<CNcomment: 频率,TP 频点,单位KHz */
    U32                      u32Sym;                  /**<sumbole rate *//**<CNcomment: 符号率,单位Kbps*/
    FRONTEND_MODULATION_E    enModulation;            /**<Modulation *//**<CNcomment: 调制模式,8PSK,QPSK等，对应DVB-S1,S2 */
    FRONTEND_POLARIZATION_E  enPolar;                 /**<Polarization type*//**<CNcomment:极化方式*/
    FRONTEND_IQ_IVT_E        enIQInt;                 /**<IQ *//**<CNcomment: IQ模式 */
} FRONTEND_SAT_BLINDSCAN_TP_INFO_S;

/** Satellite TP Info of blindscan result *//**CNcomment: 卫星盲扫结果*/
typedef struct _FRONTEND_SAT_BLINDSCAN_DATA_S
{
    U32                                u32CenterFreq; /**<current center freq, use for calc percent*//**<CNcomment: 当前盲扫的中心频率(MHz),用于App 计算盲扫进度*/
    U32                                u32TpCnt;      /**<TP count get by blindscan *//**<CNcomment: 当前频段搜索到的TP 个数, 0 表示未搜索到,具体信息在:p_tp_info 里面*/
    FRONTEND_SAT_BLINDSCAN_TP_INFO_S*  pTpInfo;       /**<TP info get by blindscan *//**<CNcomment: 指向TP(transponder)  信息数组.数组的元素个数是:tp_cnt*/
} FRONTEND_SAT_BLINDSCAN_DATA_S;

/** Notify structure of tuner blind scan */
/** CNcomment:TUNER盲扫通知信息*/
typedef union _FRONTEND_SAT_BLINDSCAN_NOTIFY_U
{
    FRONTEND_FE_STATUS_E*              penStatus;             /**<Scanning status*//**<CNcomment:盲扫状态*/
    U16*                               pu16ProgressPercent;   /**<Scanning progress*//**<CNcomment:盲扫进度*/
    FRONTEND_SAT_BLINDSCAN_TP_INFO_S*  pstResult;             /**<Scanning result*//**<CNcomment:盲扫结果*/
} FRONTEND_SAT_BLINDSCAN_NOTIFY_U;

/** Parameter of the satellite tuner blind scan */
/** CNcomment:卫星TUNER盲扫参数*/
typedef struct _FRONTEND_SAT_BLINDSCAN_PARA_S
{
    /**<LNB Polarization type, only take effect in manual blind scan mode*/
    /**<CNcomment:LNB极化方式，自动扫描模式设置无效*/
    FRONTEND_POLARIZATION_E enPolar;

    /**<LNB 22K signal status, for Ku band LNB which has dual LO, 22K ON will select high LO and 22K off select low LO,
        only take effect in manual blind scan mode*/
    /**<CNcomment:LNB 22K状态，对于Ku波段双本振LNB，ON选择高本振，OFF选择低本振，自动扫描模式设置无效*/
    FRONTEND_LNB_22K_E      enLNB22K;

    /**<Blind scan start IF, in kHz, only take effect in manual blind scan mode */
    /**<CNcomment:盲扫起始频率(中频)，单位：kHz，自动扫描模式设置无效*/
    U32                     u32StartFreq;

    /**<Blind scan stop IF, in kHz, only take effect in manual blind scan mode */
    /**<CNcomment:盲扫结束频率(中频)，单位：kHz，自动扫描模式设置无效*/
    U32                     u32StopFreq;

    /**<The execution of the blind scan may change the 13/18V or 22K status.
        If you use any DiSEqC device which need send command when 13/18V or 22K status change,
        you should registe a callback here. Otherwise, you can set NULL here.*/
    /**<CNcomment:盲扫过程可能会切换极化方式和22K，如果你用了某些DiSEqC设备需要设置13/18V和22K的，
        请注册这个回调，如果没有用，请可传NULL */
    VOID (*pfnDISEQCSet)(const HANDLE hFrontend, const FRONTEND_POLARIZATION_E enPolar,
                         const FRONTEND_LNB_22K_E enLNB22K);

    /**<Callback when scan status change, scan progress change or find new channel.*/
    /**<CNcomment:扫描状态或进度百分比发生变化时、发现新的频点时回调*/
    VOID (*pfnEVTNotify)(const HANDLE hFrontend, const FRONTEND_SAT_BLINDSCAN_EVT_E enEVT,
                         const FRONTEND_SAT_BLINDSCAN_NOTIFY_U* punNotify);
} FRONTEND_SAT_BLINDSCAN_PARA_S;

/** FRONTEND Sat scan(lock or blindscan) ctrl info*//** CNcomment:卫星信号搜索(锁频或者盲扫)参数.*/
typedef struct _FRONTEND_SAT_SCAN_INFO_S
{
    U32                     u32Freq;             /**< freq KHz *//**<CNcomment: 下行频率,单位KHz*/
    U32                     u32Sym;              /**< symbole rate *//**<CNcomment: 符号率,单位KSyms/s*/
    FRONTEND_POLARIZATION_E enPolar;             /**<Polarization type*//**<CNcomment:极化方式*/
    U32                     u32ScrambleValue;    /**<initial scrambling code,range 0~262141,when value is not 0,signal is special,
                                                     and the value must be telled by signal owner.default 0 must be configed when TP signal is not special*/
    /**<CNcomment:物理层扰码初始值，范围0~262141，该值为非0时属于特殊信号，该值只能由信号发送方告知；当频点不是特殊信号时，该值必须配置为默认值0*/

    FRONTEND_MODULATION_E   enModulation;        /**< modulation *//**<CNcomment: 调制模式,8PSK,QPSK等，对应DVB-S1,S2*/
    U32                     u32StopFreq;         /**< stop freq just for blindscan *//**<CNcomment: 扫频截止频率,仅盲扫模式有效(MHz). 如果小于freq_mhz 时,HDI 做调整.*/
    FRONTEND_ROLLOFF_E      enRolloff;           /**< rolloff *//**<CNcomment: 滚降因子选项*/
    FRONTEND_IQ_IVT_E       enIQInt;             /**< iq mod *//**<CNcomment: IQ模式*/
    FRONTEND_FEC_RATE_E     enFecRate;           /**< fec rate *//**<CNcomment: FEC，一般搜台时不需要填此项*/
    U8                      u8ChannelIndex;                   /**< ISI index, first lock use 0, after locked can get from funtion *<CNcomment: DVB-S2.channel_index是ISI的索引[1,max],刚开始搜索时,使用0,后面可以从接口获取. S2只有一个PLP(physical layer pipe),可能多个ISI(input stream identifier).*/

    U32                     u32SymOffset;        /**< sym offset *//**<CNcomment: 符号率偏移*/
    U32                     u32FreqOffset;       /**< freq offset *//**<CNcomment: 下行频率偏移*/

    FRONTEND_SEARCH_MODE_E  enSearchMod;         /**< search mod lock one freq or blindsacn *//**<CNcomment: 搜索模式 盲扫之类*/

    FRONTEND_SAT_BLINDSCAN_PARA_S* pstBindScanParam;

    FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstExAntenna;   /**< if pstExAntenna not null, will set antenna first, then scan freq *//**<CNcomment: 如果设置了天线参数，则先设置天线参数，再锁频*/
} FRONTEND_SAT_SCAN_INFO_S;

/** FRONTEND cable scan(lock) ctrl info*//** CNcomment:有线信号搜索(锁频)参数.*/
typedef struct _FRONTEND_CAB_SCAN_INFO_S
{
    U32 u32Freq;                               /**< freq  KHz*//**<CNcomment: 搜索频率(KHz)*/
    U32 u32Sym;                                /**< symbol rate *//**<CNcomment: 符号率(Syms/s)*/
    FRONTEND_MODULATION_E     enModulation;    /**< qam *//**<CNcomment: 调制方式*/
    FRONTEND_SPECTRUM_E       enSpectrum;      /**< spectrum *//**<CNcomment: 频谱极性*/
    FRONTEND_BAND_WIDTH_E     enBandWidth;     /**< band_width *//**<CNcomment: 带宽*/
    FRONTEND_GUARD_INTERVAL_E enGuardInterval; /**< guard_interval *//**<CNcomment: DVB-C2*/
    U8  u8ChannelIndex;                        /**< ISI index, first lock use 0, after locked can get from funtion *//**<CNcomment: DVB-C2.channel_index是ISI的索引[1,max],刚开始搜索时,使用0,后面可以从接口获取. C2可能有多个PLP(physical layer pipe),每个PLP只有一个ISI(input stream identifier).*/
} FRONTEND_CAB_SCAN_INFO_S;

/** FRONTEND Ter scan(lock) ctrl info*//** CNcomment:地面信号搜索(锁频)参数.*/
typedef struct _FRONTEND_TER_SCAN_INFO_S
{
    U32 u32Freq;                                /**< freq  KHz*//**<CNcomment: 搜索频率(KHz)*/
    FRONTEND_BAND_WIDTH_E      enBandWidth;      /**< BandWidth*//**<CNcomment: 带宽*/
    FRONTEND_MODULATION_E      enModulation;     /**< Modulation*//**<CNcomment: 模式*/
    FRONTEND_SPECTRUM_E        enSpectrum;       /**< spectrum *//**<CNcomment: 频谱极性*/
    FRONTEND_FEC_RATE_E        enCoderate;       /**< Coderate*//**<CNcomment: Coderate*/
    FRONTEND_GUARD_INTERVAL_E  enGuardInterval;  /**< GuardInterval*//**<CNcomment: 间隔*/
    FRONTEND_TRANSMIT_MOD_E    enTransmitMod;    /**< TransmitMod*//**<CNcomment: TransmitMod*/
    FRONTEND_TER2_MODE_E       enTer2ChannelMode; /**< T2 base mode ,lite mode *//**<CNcomment: Base模式*/
    FRONTEND_TER_TS_PRIORITY_E enTerTsPriority;  /**< T Priority of TS *//**<CNcomment: TS的优先级模式*/
    U8  u8ChannelIndex;                         /**< PLP index, first lock use 0, after locked can get from funtion *//**<CNcomment: DVB-T2.channel_index是PLP的索引[1,max],刚开始搜索时,使用0,后面可以从接口获取. T2可能有多个PLP(physical layer pipe),每个PLP只有一个ISI(input stream identifier).*/
} FRONTEND_TER_SCAN_INFO_S;

/** FRONTEND ATV System*//** CNcomment:ATV制式信息.*/
typedef enum _FRONTEND_ATV_SYSTEM_E
{
    FRONTEND_ATV_SYSTEM_PAL_BG = 0,          /**< PAL_BG *//**<CNcomment: PAL BG电视制式*/
    FRONTEND_ATV_SYSTEM_PAL_DK,              /**< PAL_DK  *//**<CNcomment: PAL DK电视制式*/
    FRONTEND_ATV_SYSTEM_PAL_I,               /**< PAL_I *//**<CNcomment: PAL I电视制式*/
    FRONTEND_ATV_SYSTEM_PAL_M,               /**< PAL_M *//**<CNcomment: PAL M电视制式*/
    FRONTEND_ATV_SYSTEM_PAL_N,               /**< PAL_N *//**<CNcomment: PAL N电视制式*/
    FRONTEND_ATV_SYSTEM_SECAM_BG,            /**< SECAM_BG *//**<CNcomment: SECAM BG电视制式*/
    FRONTEND_ATV_SYSTEM_SECAM_DK,            /**< SECAM_DK *//**<CNcomment: SECAM DK电视制式*/
    FRONTEND_ATV_SYSTEM_SECAM_L_PRIME,       /**< SECAM_L_PRIME *//**<CNcomment: SECAM L PRIME电视制式*/
    FRONTEND_ATV_SYSTEM_SECAM_LL,            /**< SECAM_LL *//**<CNcomment: SECAM LL电视制式*/
    FRONTEND_ATV_SYSTEM_NTSC_M,              /**<NTSC_M  *//**<CNcomment: NTSC M电视制式*/
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
    FRONTEND_CONNECT_WORK_MODE_NORMAL = 0,   /**<normal  *//**<CNcomment: 正常工作模式 */
    FRONTEND_CONNECT_WORK_MODE_CHAN_SCAN,    /**<chan scan  *//**<CNcomment: RF搜台模式 */
    FRONTEND_CONNECT_WORK_MODE_BUTT,
} FRONTEND_ATV_CONNECT_WORK_MODE_E;

/** FRONTEND ATV scan info*//** CNcomment:ATV搜索参数.*/
typedef struct _FRONTEND_ATV_SCAN_INFO_S
{
    U32                               u32Freq;            /**< freq  KHz*//**<CNcomment: 搜索频率(KHz)*/
    FRONTEND_ATV_SYSTEM_E             enSystem;           /**<CNcomment: ATV制式 */
    FRONTEND_ATV_SIF_BW_E             enSifBw;            /**< Atv sif bandwidth */
    FRONTEND_ATV_CONNECT_WORK_MODE_E  enConnectWorkMode;  /**<connect mode :scan or switch */
} FRONTEND_ATV_SCAN_INFO_S;

/** FRONTEND ATV signal info*//** CNcomment: ATV信号信息*/
typedef struct _FRONTEND_ATV_SIGNALINFO_S
{
    BOOL bVifLock;            /**< vif lock status *//**<CNcomment: 中频是否锁定 */
    BOOL bAfcWin;             /**< TRUE in afc window, FALSE no*//**<CNcomment: 是否在AFC窗口里面 */
    BOOL bCarrDet;            /**< TRUE carr detec on, FALSE off*//**<CNcomment: 调频伴音载波检测 */
    S32  s32AfcFreq;          /**< freq  KHz*//**<CNcomment: AFC频率值，单位Khz */
} FRONTEND_ATV_SIGNALINFO_S;

/** FRONTEND ATV lock status *//** CNcomment: ATV前端lock状态*/
typedef enum _FRONTEND_ATV_LOCK_STATUS_E
{
    FRONTEND_ATV_UNLOCK = 0,  /**< UNLOCK*//**<CNcomment:UNLOCK */
    FRONTEND_ATV_LOCK,        /**< LOCK*//**<CNcomment: LOCK */
    FRONTEND_ATV_BUTT
} FRONTEND_ATV_LOCK_STATUS_E;

/** FRONTEND DTMB carrier mode *//**CNcomment: DTMB 载波类型*/
typedef enum _DTMB_CARRIER_MODE_E
{
    FRONTEND_DTMB_CARRIER_UNKNOWN = 0,  /**<CNcomment: 未知类型*/
    FRONTEND_DTMB_CARRIER_SINGLE,       /**<Single carrier  *//**<CNcomment: 单载波*/
    FRONTEND_DTMB_CARRIER_MULTI,        /**<Multi carrier  *//**<CNcomment: 多载波*/
    FRONTEND_DTMB_CARRIER_BUTT
} FRONTEND_DTMB_CARRIER_MODE_E;

/** FRONTEND DTMB code rate *//**CNcomment:DTMB 码率类型*/
typedef enum _FRONTEND_DTMB_CODE_RATE_E
{
    FRONTEND_DTMB_CODE_RATE_UNKNOWN = 0, /**<CNcomment: 未知类型*/
    FRONTEND_DTMB_CODE_RATE_0_DOT_4,     /**< 0.4  *//**<CNcomment: 0.4 码率*/
    FRONTEND_DTMB_CODE_RATE_0_DOT_6,     /**< 0.6  *//**<CNcomment: 0.6 码率*/
    FRONTEND_DTMB_CODE_RATE_0_DOT_8,     /**< 0.8  */ /**<CNcomment: 0.8 码率*/
    FRONTEND_DTMB_CODE_RATE_BUTT
} FRONTEND_DTMB_CODE_RATE_E;

/** FRONTEND DTMB time interleave *//**CNcomment: DTMB 时域交织类型*/
typedef enum _FRONTEND_DTMB_TIME_INTERLEAVE_E
{
    FRONTEND_DTMB_TIME_INTERLEAVER_UNKNOWN = 0, /**<CNcomment: 未知类型*/
    FRONTEND_DTMB_TIME_INTERLEAVER_240,         /**< 240  *//**<CNcomment: 240 类型*/
    FRONTEND_DTMB_TIME_INTERLEAVER_720,         /**< 720  *//**<CNcomment: 720 类型*/
    FRONTEND_DTMB_TIME_INTERLEAVER_BUTT
} FRONTEND_DTMB_TIME_INTERLEAVE_E;

/** FRONTEND DTMB time interval *//**CNcomment:  DTMB 保护间隔类型*/
typedef enum _FRONTEND_DTMB_GUARD_INTERVAL_E
{
    FRONTEND_DTMB_GI_UNKNOWN = 0,   /**<unknown type*//**<CNcomment:未知类型*/
    FRONTEND_DTMB_GI_420,           /**<420 type*//**<CNcomment:420 类型*/
    FRONTEND_DTMB_GI_595,           /**<595 type*//**<CNcomment:595 类型*/
    FRONTEND_DTMB_GI_945,           /**<945 type*//**<CNcomment:945 类型*/
    FRONTEND_DTMB_GI_BUTT
} FRONTEND_DTMB_GUARD_INTERVAL_E;

/** FRONTEND DTMB scan param *//**CNcomment:  DTMB搜索参数*/
typedef struct _FRONTEND_DTMB_SCAN_INFO_S
{
    U32                              u32Freq;               /**< freq  KHz*//**<CNcomment: 搜索频率(KHz)*/
    FRONTEND_BAND_WIDTH_E            enBandWidth;           /**< BandWidth*//**<CNcomment: 带宽*/
    FRONTEND_MODULATION_E            enModulation;          /**< Modulation*//**<CNcomment: 模式*/
    FRONTEND_SPECTRUM_E              enSpectrum;            /**< spectrum *//**<CNcomment: 频谱极性*/

    FRONTEND_DTMB_CARRIER_MODE_E     enCarrierMode;         /**<Carrier type*//**<CNcomment:载波类型*/
    FRONTEND_DTMB_CODE_RATE_E        enCoderate;            /**<Code rate type*//**<CNcomment:码率类型*/
    FRONTEND_DTMB_TIME_INTERLEAVE_E  enTimeInterleave;      /**<Time interleave type*//**<CNcomment:时域交织类型*/
    FRONTEND_DTMB_GUARD_INTERVAL_E   enGuardInterval;       /**<Guard interval type*//**<CNcomment:保护时间类型*/
    U8  u8ChannelIndex;
} FRONTEND_DTMB_SCAN_INFO_S;

/** FRONTEND scan param union *//**CNcomment:  信号搜索参数*/
typedef union _FRONTEND_SIGNAL_SCAN_INFO_U
{
    FRONTEND_SAT_SCAN_INFO_S    stSatInfo;   /**<Sat info *//**<CNcomment:卫星锁频信息*/
    FRONTEND_CAB_SCAN_INFO_S    stCabInfo;   /**<Cab info *//**<CNcomment:有线锁频信息*/
    FRONTEND_TER_SCAN_INFO_S    stTerInfo;   /**<Ter info *//**<CNcomment:Ter锁频信息*/
    FRONTEND_ATV_SCAN_INFO_S    stAtvInfo;   /**<Atv info *//**<CNcomment:模拟锁频信息*/
    FRONTEND_DTMB_SCAN_INFO_S   stDtmbInfo;  /**<Dtmb info*//**<CNcomment:Dtmb锁频信息*/
} FRONTEND_SIGNAL_SCAN_INFO_U;

/** FRONTEND scan freq info *//**CNcomment:  频点信息*/
typedef struct _FRONTEND_SCAN_INFO_S
{
    U16                         u16TsIndex;       /**<Ts index *//**<CNcomment: ts流通道，相当于bank*/
    FRONTEND_FE_TYPE_E          enFrontendType;   /**<Type *//**<CNcomment: 锁频类型*/
    FRONTEND_SIGNAL_SCAN_INFO_U unScanInfo;       /**<Scan info  *//**<CNcomment: 锁频参数*/
} FRONTEND_SCAN_INFO_S;

/** FRONTEND status *//**CNcomment:  频点质量，强度，误码率锁频信息*/
typedef struct _FRONTEND_FRONTEND_STATUS_S
{
    U32     u32Strength;         /**<Strength *//**<CNcomment: 信号强度*/
    U32     u32Quality;          /**<Quality *//**<CNcomment: 信号质量*/
    float   fBert;               /**<Ber*//**<CNcomment: 误码率*/
} FRONTEND_FRONTEND_STATUS_S ;

typedef enum _FRONTEND_UNICABLE_SCAN_EVT_E
{
    FRONTEND_UNICABLE_SCAN_EVT_STATUS = 0,      /**<New status*//**<CNcomment:状态变化*/
    FRONTEND_UNICABLE_SCAN_EVT_PROGRESS,        /**<New Porgress *//**<CNcomment:进度变化*/
    FRONTEND_UNICABLE_SCAN_EVT_BUTT             /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_UNICABLE_SCAN_EVT_E;

typedef enum _FRONTEND_UNICABLE_SCAN_STATUS_E
{
    FRONTEND_UNICABLE_SCAN_STATUS_IDLE = 0,     /**<Idel*//**<CNcomment:空闲*/
    FRONTEND_UNICABLE_SCAN_STATUS_SCANNING,     /**<Scanning*//**<CNcomment:扫描中*/
    FRONTEND_UNICABLE_SCAN_STATUS_FINISH,       /**<Finish*//**<CNcomment:成功完成*/
    FRONTEND_UNICABLE_SCAN_STATUS_QUIT,         /**<User quit*//**<CNcomment:用户退出*/
    FRONTEND_UNICABLE_SCAN_STATUS_FAIL,         /**<Scan fail*//**<CNcomment:扫描失败*/
    FRONTEND_UNICABLE_SCAN_STATUS_BUTT          /**<Invalid value*//**<CNcomment:非法边界值*/
} FRONTEND_UNICABLE_SCAN_STATUS_E;

typedef union _FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U
{
    FRONTEND_UNICABLE_SCAN_STATUS_E* penStatus;             /**<Scanning status*//**<CNcomment:盲扫状态*/
    U16*                             pu16ProgressPercent;   /**<Scanning progress*//**<CNcomment:盲扫进度*/
} FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U;

/**
\brief FrontEnd callback.CNcomment:FrontEnd回调函数
\attention \n
N/A
\param[in] hFrontend    frontend handle                             CNcomment:设备句柄
\param[in] enBlindscanStatus      notify event                      CNcomment:上抛的事件
\param[in] pstBlindscanData       ref:FRONTEND_SAT_BLINDSCAN_DATA_S CNcomment:上抛的内容 FRONTEND_SAT_BLINDSCAN_DATA_S
\param[in] u32UserData  FRONTEND_REG_CALLBACK_PARAMS_S 3rd param    CNcomment:用户注册传入的参数，直接回传
\retval ::SUCCESS:   success                                     CNcomment:成功
\retval ::FAILURE:   fail                                        CNcomment:失败
\see \n
::FRONTEND_FE_STATUS_E
::FRONTEND_SAT_BLINDSCAN_DATA_S
::FRONTEND_REG_CALLBACK_PARAMS_S
N/A
*/

/** Satellite TP blindscan callback funtion *//**CNcomment: 盲扫状态/数据回调函数*/
typedef void (*FRONTEND_SAT_BLINDSCAN_STATUS_PFN)(
    const HANDLE    hFrontend,
    const FRONTEND_FE_STATUS_E  enBlindscanStatus,          /**<CNcomment: 盲扫状态 */
    const FRONTEND_SAT_BLINDSCAN_DATA_S*   const pstBlindscanData,   /**<CNcomment:  盲扫数据*/
    const U32 u32UserData /**<CNcomment:  用户私有数据*/);

/**
\brief FrontEnd callback.CNcomment:FrontEnd回调函数
\attention \n
N/A
\param[in] hFrontend    frontend handle                             CNcomment:设备句柄
\param[in] enOldStatus  oldstatus                                   CNcomment:旧状态
\param[in] enNewStatus  newstatus ref:FRONTEND_FE_STATUS_E          CNcomment:新状态 FRONTEND_FE_STATUS_E
\param[in] u32UserData  FRONTEND_REG_CALLBACK_PARAMS_S 3rd param    CNcomment:用户注册传入的参数，直接回传
\retval ::SUCCESS:   success                                     CNcomment:成功
\retval ::FAILURE:   fail                                        CNcomment:失败
\see \n
::FRONTEND_FE_STATUS_E
::FRONTEND_REG_CALLBACK_PARAMS_S
N/A
*/

/** Satellite TP lock status callback funtion, call this when status change *//**CNcomment: 锁定状态通知回调函数,锁定状态改变的时候回调.*/
typedef void (*FRONTEND_NOTIFY_STATUS_PFN)(const HANDLE hFrontend,
        const FRONTEND_FE_STATUS_E enOldStatus,
        const FRONTEND_FE_STATUS_E enNewStatus,
        const U32 u32UserData /**<CNcomment:  用户私有数据*/);

/**
\brief FrontEnd callback.CNcomment:FrontEnd回调函数
\attention \n
On some platform frontend_get_signal_strength() may take more time. there are three ways to make it right.
1. Use these frontend_get_signal_strength(), frontend_get_signal_quality(),frontend_get_bert().
2. Take strength guality ber at set intervals, and return them in frontend_get_signal_strength(), frontend_get_signal_quality(),frontend_get_bert().
3. Take strength guality ber at variable intervals, and if FRONTEND_REG_GETSTATUS_CALLBACK is not NULL, get them by a thread and callback return them.
CNcomment:在有些平台上面,获取信号质量,信号强度,误码率需要很长时间而且很占cup资源.
1. 在调用frontend_get_signal_strength(), frontend_get_signal_quality(),frontend_get_bert() 的时候,直接从底层获取这样可能会导致获取的时候应用菜单响应比较慢.
2. 每隔一段长的时间,从底层获取一次,保存在frontend里面,应用获取的时候,直接返回保存的值.这样不会影响菜单响应时间,但是对cup资源占用可能有影响.
3. 不定时获取误码率,信号质量,信号强度.在应用调用任意一个frontend_get_signal_strength(), frontend_get_signal_quality(),frontend_get_bert()直接返回原来保存的信号强度/信号质量/误码率
   同时,如果注册的FRONTEND_REG_GETSTATUS_CALLBACK 类型的回调函数指针不为空,任务会再次去获取一次当前的信号质量,信号强度,误码率.然后回调回去.
   这样既避免了导致应用菜单响应慢,又避免了定时获取占用CPU 资源的问题.
这三种方式, 接口在实现的时候,具体采用哪种方式,取决于具体平台获取的效率.不需要每种都实现.CNend

N/A
\param[in] hFrontend    frontend handle                             CNcomment:设备句柄
\param[in] pFrontendStatus   strength, quality, ber                 CNcomment:当前信号的强度，质量，误码率
\param[in] u32UserData  userdata                                    CNcomment:用户注册传入的参数，直接回传
\retval ::SUCCESS:   success                                     CNcomment:成功
\retval ::FAILURE:   fail                                        CNcomment:失败
\see \n
N/A
*/

typedef void (*FRONTEND_GET_STATUS_PFN)(const HANDLE hFrontend,
                                        const FRONTEND_FRONTEND_STATUS_S* const pFrontendStatus,
                                        const U32 u32UserData );

/**
\brief FrontEnd callback.CNcomment:FrontEnd回调函数
\attention \n
N/A
\param[in] hFrontend    frontend handle                             CNcomment:设备句柄
\param[in] enOldStatus  oldstatus                                   CNcomment:旧状态
\param[in] enNewStatus  newstatus ref:FRONTEND_LNB_PWR_STATUS_E     CNcomment:新状态 FRONTEND_LNB_PWR_STATUS_E
\param[in] u32UserData  FRONTEND_REG_CALLBACK_PARAMS_S 3rd param    CNcomment:用户注册传入的参数，直接回传
\retval ::SUCCESS:   success                                     CNcomment:成功
\retval ::FAILURE:   fail                                        CNcomment:失败
\see \n
::FRONTEND_LNB_PWR_STATUS_E
N/A
*/

typedef void (*FRONTEND_NOTIFY_LNB_PWR_STATUS_PFN)(const HANDLE hFrontend,
        const FRONTEND_LNB_PWR_STATUS_E enOldStatus,
        const FRONTEND_LNB_PWR_STATUS_E enNewStatus,
        const U32 u32UserData /**<CNcomment:  用户私有数据*/);

/**
\brief FrontEnd unicable scan callback.CNcomment:FrontEnd unicable 搜索回调函数
\attention \n
N/A
\param[in] hFrontend    frontend handle                             CNcomment:设备句柄
\param[in] enEVT  FRONTEND_UNICABLE_SCAN_EVT_E type of data         CNcomment:返回的数据类型
\param[in] pData  FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U data      CNcomment:返回的数据，联合数据类型
\retval ::SUCCESS:   success                                     CNcomment:成功
\retval ::FAILURE:   fail                                        CNcomment:失败
\see \n
::FRONTEND_UNICABLE_SCAN_EVT_E
::FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U
N/A
*/

typedef void (*FRONTEND_UNICABLE_SCAN_PFN)(const HANDLE hFrontend, FRONTEND_UNICABLE_SCAN_EVT_E enEVT, FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U* pData);

/** FRONTEND register callback type *//**CNcomment: 回调函数类型*/
typedef enum _FRONTEND_REG_CALLBACK_TYPE_E
{
    FRONTEND_REG_LOCKSTATUS_CALLBACK = 0,   /**< Callback ProtoType :  frontend_notify_status_pfn_t*/
    FRONTEND_REG_GETSTATUS_CALLBACK,        /**< Callback ProtoType :  frontend_get_status_pfn_t */
    FRONTEND_REG_BLINDSCAN_CALLBACK,        /**< Callback ProtoType :  frontend_sat_blindscan_status_pfn_t*/
    FRONTEND_REG_LNB_PWR_STATUS_CALLBACK,   /**< Callback ProtoType :  frontend_notify_lnb_pwr_status_pfn_t*/
    FRONTEND_REG_UNICABLE_SCAN_CALLBACK,    /**< Callback ProtoType :  FRONTEND_UNICABLE_SCAN_PFN*/
    FRONTEND_REG_CALLBACK_TYPE_BUTT
} FRONTEND_REG_CALLBACK_TYPE_E ;

/** FRONTEND register callback params *//**CNcomment: 回调函数注册参数*/
typedef struct _FRONTEND_REG_CALLBACK_PARAMS_S
{
    FRONTEND_REG_CALLBACK_TYPE_E    enCallbackType;    /**<see FRONTEND_REG_CALLBACK_TYPE_E *//**<CNcomment: 回调函数类型, 决定下面的p_callback 原型  */
    void*   pCallBack;                                 /**< funtion callback *//**<CNcomment: 需要注册的回调函数*/
    U32     u32UserData;                               /**< date user want send back *//**<CNcomment: 用户想要回传的数据*/
    BOOL    bDisable;                                  /**< FALSE is enable ; TRUE is disable *//**<CNcomment:  是否使能该回调: FALSE is enable ; TRUE is disable*/
} FRONTEND_REG_CALLBACK_PARAMS_S;

/** FRONTEND info *//**CNcomment: frontend 信息，tuner信息*/
typedef struct _FRONTEND_INFO_S
{
    FRONTEND_DEVICE_NAME    aszDevName; /**< name *//**<CNcomment: 名称*/
    U32 u32CallbackNum;   /**< callback num *//**<CNcomment: 回调函数的个数.*/
    U32 u32SourceId;      /**< source id,diffrent means on diffrent platform, so use it right way */
    /**<CNcomment: 对应的TS流来源通道.不同平台他的物理意义可能不一样,要和sk_hdi_dmx 模块约定好, 因为dmx需要他来获取数据, dmx 模块和CI模块实现的时候用source_id 能转换成具体ts来源数据 类型. */
    FRONTEND_DISEQC_VER_E   enDiseqcVer; /**< Diseqc Ver *//**<CNcomment: 支持的DISEQC版本.*/
    U32 u32Generation;    /**< eg. c c2 s s2 *//**<CNcomment: 支持哪代前端(eg C,C2).or关系,第一代使用0x1,第二代使用0x1<<1,
                                    * 依次类推.如果支持多代使用or关系(eg. C|C2 <=> 0x3).*/
    DMX_ID_E    enDemuxSetArr[DMX_NUMBER_OF_DMX_ID]; /**< demux_set_arr[0]=DMX_ID_0|DMX_ID_3 means frontend 0 support out to DMX_ID_0 DMX_ID_3. *//**<CNcomment: 被此前端支持的dmx集(or关系). 如果demux_set_arr[0]=DMX_ID_0|DMX_ID_3.表示该frontend支持ts输出到DMX_ID_0,也可以同时输出到DMX_ID_3.
                                                            *  如果demux_set_arr[i]=0, 表示该frontend不支持SK_HDI_DMX_ID_i,以及它和其他dmx的任意组合.*/
} FRONTEND_INFO_S;

/** FRONTEND CAPABILITY *//**CNcomment: frontend 能力(多模tuner)*/
typedef struct _FRONTEND_CAPABILITY_S
{
    U32 u32TunerNum;
    U32 au32FeCurType[FRONTEND_FE_NUM_MAX];
    U32 au32FeType[FRONTEND_FE_NUM_MAX];  /**< eg. au32FeType[0]=3 means this tuner has two capability,one is FRONTEND_FE_SATELLITE1 (1) the other is FRONTEND_FE_SATELLITE2(2)*/
    /**<CNcomment: 在au32FeType 中FRONTEND_FE_TYPE_E 各个枚举成员的对应的位不为0,
    * 则系统有该类型的tuner, 比如:au32FeType[0]=3,表示第一第二位不为0
    * 因此系统中tuner 0有FRONTEND_FE_SATELLITE1 (1) 和FRONTEND_FE_SATELLITE2(2)两个能力.
    * au32FeType[1]=4,表示第三位不为0,因此系统中tuner 1 有FRONTEND_FE_CABLE1(3)一个能力.
    * 注意,使用的时候,要用FRONTEND_FE_TYPE_E,各个枚举值,不要使用数字,
    * 避免以后修伽枚举带来维护的麻烦.
    */
} FRONTEND_CAPABILITY_S;

/** FRONTEND generation 2: DVB-C2,DVB-T2,DVB-S2,modulation and FEC rate.*//**CNcomment: DVB-C2,DVB-T2,DVB-S2,modulation and FEC rate.*/
typedef struct _FRONTEND_G2_MODFEC_S
{
    FRONTEND_FEC_RATE_E     enFecRate;       /**< FEC rate.*//**<CNcomment: FEC rate*/
    FRONTEND_MODULATION_E   enModulation;    /**< modulation.*//**<CNcomment: 模式*/
} FRONTEND_G2_MODFEC_S;

/** FRONTEND DVB-C2,DVB-T2,DVB-S2 stream type. *//**CNcomment: DVB-C2,DVB-T2,DVB-S2输入流的格式.*/
typedef enum _FRONTEND_G2_STREAM_TYPE_E
{
    FRONTEND_G2_STREAM_TYPE_UNKNOWN = 0,      /**< UNKNOWN.*//**<CNcomment: 未知*/
    FRONTEND_G2_STREAM_TYPE_TS      = 1 << 0, /**< MPEG-TS.*/ /**<CNcomment: MPEG-TS*/
    FRONTEND_G2_STREAM_TYPE_GSE     = 1 << 1, /**< Generic Encapsulated Stream.*/ /**<CNcomment: GSE*/
    FRONTEND_G2_STREAM_TYPE_GCS     = 1 << 2, /**< Generic Continuous Stream.*/ /**<CNcomment: GCS*/
    FRONTEND_G2_STREAM_TYPE_GFPS    = 1 << 3, /**< Generic Packetized Stream.*/ /**<CNcomment: GFPS*/
    FRONTEND_G2_STREAM_TYPE_BUTT
} FRONTEND_G2_STREAM_TYPE_E;

/** FRONTEND DVB-C2,DVB-T2,DVB-S2 channel info. *//**CNcomment: DVB-C2,DVB-T2 PLP,DVB-S2 ISI 信息.*/
typedef struct _FRONTEND_G2_CHANNEL_INFO_S
{
    U8  u8Isi;                                  /**< Input Stream Identifier.*/
    FRONTEND_G2_STREAM_TYPE_E   enStreamType;   /**< Input Stream type.*//**<CNcomment: DVB-C2,DVB-T2,DVB-S2输入流的格式.*/
    BOOL bCcm;                                  /**< TRUE:Constant Coding and Modulation;FALSE:Variable/Adaptive Coding and Modulation.*/
    BOOL bIssActive;                            /**< whether ISS active.ISS:Input Stream Synchronization.TRUE:active;FALSE:not active.*/
    BOOL bNpdActive;                            /**< whether NPD active.NPD:Null Packet deletion.TRUE:active;FALSE:not active.
                                                     If NPD active, then DNP shall be computed and appended after UPs(User Packets)*/
    FRONTEND_ROLLOFF_E  enRollOff;              /**< only DVB-S2 .*/
    FRONTEND_G2_MODFEC_S    stModFec;           /**< modulation and FEC rate .*/
    BOOL bShortFrame;                           /**< TRUE:16 200 bits,FALSE:64 800 bits.*/
} FRONTEND_G2_CHANNEL_INFO_S;

/** FRONTEND DVB-C2,DVB-T2,DVB-S2 params. *//**CNcomment: DVB-C2,DVB-T2,DVB-S2 信道配置参数.*/
typedef struct _FRONTEND_G2_REQ_PARAMS_S
{
    FRONTEND_G2_MODFEC_S    stModFec;           /**< see sk_hdi_frontend_g2_modcod_t.*/
    BOOL                    bPilots;            /**< TRUE:pilots, FALSE:no pilots.*/
} FRONTEND_G2_REQ_PARAMS_S;

/** FRONTEND DVB-C2,DVB-T2,DVB-S2 response . *//**CNcomment: DVB-C2,DVB-T2,DVB-S2 信道配置回应参数.*/
typedef struct _FRONTEND_G2_RPN_PARAMS_S
{
    U8  u8ModFecAck;                /**< coded according to the MODCOD_RQ conventions.*/
} FRONTEND_G2_RPN_PARAMS_S;

#ifdef ANDROID_HAL_MODULE_USED
/**Frontend module structure(Android require)*/
/**CNcomment:Frontend模块结构(Android对接要求) */
typedef struct _FRONTEND_MODULE_S
{
    struct hw_module_t common;
} FRONTEND_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_FRONTEND*/
/** @{*/  /** <!-- -HAL_FRONTEND=*/

/**Frontend device structure*//** CNcomment:Frontend设备结构*/
typedef struct _FRONTEND_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif
    /**
    \brief Frontend init.CNcomment:frontend初始化 CNend
    \attention \n
    frontend module init ,  repeat call return success.
    CNcomment:frontend模块初始化, 本函数重复调用返回成功. CNend

    \param[in] pstInitParams frontend module init param.CNcomment:初始化模块参数 CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_FRONTEND_INIT_FAILED  lower layer frontend init error.CNcomment:frontend底层初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Frontend open.CNcomment:frontend 打开实例 CNend
    \attention \n
    Frontend open.
    CNcomment:Frontend 打开实例. CNend
    \param[out] phFrontend frontend hanlde. CNcomment:实例句柄，外部定义 CNend
    \param[in] pstInitParams frontend module init param.CNcomment:实例打开参数 CNend
    \retval 0  SUCCESS Success.CNcomment:成功.重复调用init返回成功。CNend
    \retval ::ERROR_FRONTEND_NOT_INIT  frontend not init.CNcomment:frontend未初始化。CNend
    \retval ::ERROR_FRONTEND_OPEN_FAILED frontend open error. CNcomment:打开实例失败。CNend
    \retval ::ERROR_FRONTEND_ALREADY_OPEN this handle already open.CNcomment:该句柄的实例已经打开。 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Frontend open.CNcomment:frontend 关闭实例 CNend
    \attention \n
    Frontend close.
    CNcomment:Frontend 关闭实例. CNend
    \param[in] frontend_handle frontend hanlde. CNcomment:实例句柄，外部定义 CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_FRONTEND_NOT_INIT  frontend not init.CNcomment:frontend未初始化。CNend
    \retval ::ERROR_FRONTEND_NOT_OPEN frontend handle not open, or no this handle CNcomment:实例未打开或者没有改句柄的设备。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::FAILURE  other error.CNcomment:关闭错误 CNend
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
     \brief Get Frontend handle by index.CNcomment:根据index获取frontend句柄 CNend
     \attention \n
    Tuner of u32FrontendIndex must be init。
    CNcomment:该Tuner必须初始化. CNend
    \param[out] phFrontend frontend hanlde. CNcomment:实例句柄，外部定义 CNend
     \param[in] u32FrontendIndex frontend index.CNcomment:初始化时使用的FrontendIndex CNend
     \retval 0  SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_FRONTEND_NOT_INIT  Not init.CNcomment:该index的tuner没有初始化 CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::FRONTEND_TERM_PARAMS_S

     \par example
     \code
     \endcode
    */
    S32 (*frontend_get_handle)(struct _FRONTEND_DEVICE_S* pstDev, U32 u32FrontendIndex, HANDLE* const phFrontend);

    /**
    \brief Frontend term.CNcomment:frontend去初始化 CNend
    \attention \n
    frontend module deinit and release occupied resource,  repeat call return success.
    CNcomment:frontend模块去初始化及释放占用的资源, 本函数重复调用返回成功. CNend

    \param[in] pstTermParams frontend module term param.CNcomment:去初始化模块参数 CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_FRONTEND_DEINIT_FAILED  Lower layer frontend module deinit error.CNcomment:底层frontend模块去初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Get scan info of tuner.CNcomment:获取frontend 当前的scan 状态CNend
    \attention \n
    Get scan info of Frontend by handle.
    CNcomment:获取Frontend 当前scan的状态. CNend
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] pstScanInfo frontend scan info .CNcomment: 获取的scan 信息 CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_SCAN_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_scan_info)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                                  FRONTEND_SCAN_INFO_S* const pstScanInfo);

    /**
    \brief set sat lnb config .CNcomment: 设置lnb CNend
    \attention \n
    Before search satellite, or play program on one satellite.
    CNcomment:搜台前，或者播放一个节目前，同一个卫星在切换极化和本振时需要设置. CNend
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[in] pstLnbInfo lnb info. CNcomment: 需要设置的lnb信息 CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_SAT_LNB_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_sat_config_lnb)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_SAT_LNB_INFO_S* const pstLnbInfo);

    /**
     \brief init sat lnb config .CNcomment: 初始化lnb基本配置 CNend
     \attention \n
    Before search satellite, or play program on one satellite.
    CNcomment:搜台前，或者播放一个节目前，同一个卫星可以不用多次设置. CNend
     \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
     \param[in] pstLnbConfig lnb info. CNcomment: 需要设置的lnb信息 CNend
     \retval 0  SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::FRONTEND_SAT_LNB_CONFIG_S

     \par example
     \code
     \endcode
    */
    S32 (*frontend_sat_init_lnb)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_SAT_LNB_CONFIG_S* const pstLnbConfig);

    /**
     \brief set sat antenna config .CNcomment: 设置天线基本配置 CNend
     \attention \n
    Before search satellite, or play program on one satellite.
    CNcomment:搜台前，或者播放一个节目前，同一个卫星可以不用多次设置. CNend
     \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
     \param[in] enAntennaCmd  type of FRONTEND_ANTENNA_CMD_TYPE_E. CNcomment: 设置命令 CNend
     \param[in] pParam: Data type acording to enAntennaCmd. CNcomment: 需要设置的天线信息 CNend
     \retval 0  SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::FRONTEND_ANTENNA_CMD_TYPE_E

     \par example
     \code
     \endcode
    */
    S32 (*frontend_sat_config_antenna)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_ANTENNA_CMD_TYPE_E enAntennaCmd, void* pParam);

    /**
    \brief get lnb power status .CNcomment: 获取lnb 供电状态 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] penLnbPwrStatus lnb power info. CNcomment: 获取的lnb供电状态 CNend
    \retval 0  SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_LNB_PWR_STATUS_E

    \par example
    \code

    \endcode
    */

    S32 (*frontend_get_lnb_pwr_status)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, FRONTEND_LNB_PWR_STATUS_E* const penLnbPwrStatus);

    /**
    \brief scan one freq or set blindscan (sat)  .CNcomment: 锁频或者盲扫 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[in] pstScanParams scan params. CNcomment: 锁频参数，盲扫参数CNend
    \param[in] bSynch TRUE wait for lock or timeout, not use for blindscan. CNcomment: 是否同步锁频，盲扫无效，盲扫为异步 CNend
    \param[in] u32Timeout timeout for locked, not use for blindscan. CNcomment: 超时时间，盲扫无效 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::FRONTEND_FE_STATUS_E  see FRONTEND_FE_STATUS_E. CNcomment:返回FRONTEND_FE_STATUS_E状态，如果和上一个频点相同，直接返回状态。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief stop scan one freq or set blindscan (sat)  .CNcomment:终止 锁频或者盲扫 CNend
    \attention \n
    stop frontend_start_scan() when bsynch is TRUE and timeout is not 0. stop blindscan.
    CNcomment:终止同步锁频，但是后天继续锁频，或者终止卫星盲扫，后台不在继续盲扫发现卫星频点. CNend
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_TERM_PARAMS_S

    \par example
    \code

    \endcode
    */
    S32  (*frontend_abort)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend);

    /**
    \brief register callback .CNcomment: 注册回调函数 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[in] pstRegParams frontend callback param.CNcomment:回调函数参数 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_REG_CALLBACK_PARAMS_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_register_callback)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend, const FRONTEND_REG_CALLBACK_PARAMS_S* const pstRegParams);

    /**
    \brief config callback .CNcomment: 注册回调函数 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[in] pCallback callback funtion. CNcomment:回调函数指针 CNend
    \param[in] enCallbackCfg frontend callback config.CNcomment:回调函数工作与否的参数 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_CFG_CALLBACK_E

    \par example
    \code

    \endcode
    */

    S32 (*frontend_config_callback)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend, const void* const  pCallback, const FRONTEND_CFG_CALLBACK_E enCallbackCfg);

    /**
    \brief lock sync .CNcomment:同步锁定 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */

    S32 (*frontend_lock)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend);

    /**
    \brief get ber.CNcomment:获取误码率 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] pfBert get from frontend. CNcomment:误码率指针 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_bert)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,  float* const pfBert);

    /**
    \brief get quality.CNcomment:获取信号质量 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] pu32Quality get from frontend. CNcomment:信号质量指针 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */

    S32 (*frontend_get_signal_quality)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                                       U32* const pu32Quality);

    /**
    \brief get strength.CNcomment:获取信号强度 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] pu32Strength get from frontend. CNcomment:信号强度指针 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_signal_strength)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                                        U32* const pu32Strength);

    /**
    \brief get atv signal info.CNcomment:获取信号信息 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] pstSignalInfo get from frontend. CNcomment:信号信息指针 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_ATV_SIGNALINFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_atvsignalinfo)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, FRONTEND_ATV_SIGNALINFO_S* const pstSignalInfo);

    /**
    \brief get signal connect status.CNcomment:获取信号锁频信息 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] penStatus get from frontend. CNcomment:信号锁频状态指针 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_FE_STATUS_E

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_connect_status)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, FRONTEND_FE_STATUS_E* const penStatus);

    /**
    \brief get frontend all info. CNcomment:获frontend 所有信息 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] pstInfo get from frontend. CNcomment:frontend 信息指针 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_info)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend,
                             FRONTEND_INFO_S*   const pstInfo);

    /**
    \brief get frontend capability. CNcomment:获frontend 能力 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] pstCapability get from frontend. CNcomment:指向能力数据的指针 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_CAPABILITY_S

    \par example
    \code

    \endcode
    */
    S32  (*frontend_get_capability)(struct _FRONTEND_DEVICE_S* pstDev, FRONTEND_CAPABILITY_S* const pstCapability);

    /**
    \brief get TS channel num just use for DVBC2,DVBT2,DVBS2 for DVBC,DVBT,DVBS ChannelNum is 1 . CNcomment:获得通道数量只对DVBC2,DVBT2,DVBS2有用，对DVBC,DVBT,DVBS 返回 1 CNend
    \attention \n
    if tuner is auto support DVBT DVBT2 or DVBS DVBS2, after lock must use this funtion to know Versio. num 1 means 1 PLP, or 1 ISI.
    CNcomment:如果tuner具有自适应的功能，请调用该函数确定是否为Ver2版本的协议.有多少通道，通道为1可以不考虑PLP或 ISI 操作 CNend
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] pu8ChannelNum get from frontend. CNcomment:ChannelNum CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32  (*frontend_get_channel_num)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend, U8* const pu8ChannelNum);

    /**
    \brief get TS channel info just use for DVBC2,DVBT2,DVBS2 . CNcomment:获取通道信息 CNend
    \attention \n
    just use for install program. play program use frontend_config_channel().
    CNcomment:搜索节目时会使用，播放时用 frontend_config_channel().
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[in] u8ChannelIndex channle index.CNcomment:通道序号 CNend
    \param[out] pstChannelInfo get from frontend. CNcomment:通道信息 CNend
    \param[in] u32Timeout timeout for get channelinfo.CNcomment:超时时间 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_G2_CHANNEL_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_get_channel_info)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const U8 u8ChannelIndex, FRONTEND_G2_CHANNEL_INFO_S* const pstChannelInfo, const U32 u32Timeout);

    /**
    \brief set TS channel info just use for DVBS2 . CNcomment:设置通道信息 只支持DVBS2 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[in] u8ChannelIndex channel index.CNcomment:通道序号 CNend
    \param[in] pstReqParams channel info .CNcomment:通道设置参数 CNend
    \param[out] pstRpnParams response from frontend, can be NULL . CNcomment:反馈信息，可以NULL CNend
    \param[in] u32Timeout timeout for get channelinfo.CNcomment:超时时间 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
     \brief set demod out ts. CNcomment: 设置输出流 CNend
     \attention \n
    For T2 PLP & S2 ISI.
    CNcomment: 设置和获取T2多PLP模式，设置和获取S2多ISI模式 CNend
     \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
     \param[in] enTsoutCmd  type of FRONTEND_TSOUT_CMD_TYPE_E. CNcomment: 设置命令 CNend
     \param[in] pParam: Data type acording to enAntennaCmd. CNcomment: 需要设置的参数信息 CNend
     \retval 0  SUCCESS Success.CNcomment:成功。CNend
     \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
     \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
     \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
     \retval ::FAILURE  other error.CNcomment:其它错误 CNend
     \see \n
    ::FRONTEND_ANTENNA_CMD_TYPE_E

     \par example
     \code
     \endcode
    */
    S32 (*frontend_config_tsout)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_TSOUT_CMD_TYPE_E enTsoutCmd, void* pParam);

    /**
    \brief get ATV lock status. CNcomment:获取锁频状态 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[out] penLockStatus response from frontend, can be NULL . CNcomment:锁频状态 CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief fine tuned tunner frequency. CNcomment:微调tunner的频率  CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \param[in] s32Steps fine tunned tunner step. CNcomment:微调频率的偏移量 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_atv_fineTune)(struct _FRONTEND_DEVICE_S* pstDev, HANDLE  hFrontend, S32 s32Steps);

    /**
    \brief Frontend standby. CNcomment:TUNER待机 CNend
    \attention \n
    \param[in] frontend_handle frontend handle param.CNcomment:句柄 CNend
    \retval ::SUCCESS standby success.CNcomment:设置成功。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_standby)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE frontend_handle);

    /**
    \brief wake up tuner. CNcomment:TUNER唤醒 CNend
    \attention \n
    \param[in] hFrontend frontend handle param.CNcomment:句柄 CNend
    \retval ::SUCCESS wakeup success.CNcomment:设置成功。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_FRONTEND_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::FRONTEND_INFO_S

    \par example
    \code

    \endcode
    */
    S32 (*frontend_wakeup)(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE frontend_handle);

} FRONTEND_DEVICE_S;

/**
\brief direct get frontend device api, for linux and android.CNcomment:获取frontend设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get frontend device api，for linux and andorid.
CNcomment:获取frontend设备接口，linux和android平台都可以使用. CNend
\retval  frontend device pointer when success.CNcomment:成功返回frontend设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::FRONTEND_DEVICE_S

\par example
*/
FRONTEND_DEVICE_S* getFrontEndDevice();

/**
\brief  Open HAL frontend module device.CNcomment: 打开HAL frontend模块设备 CNend
\attention \n
Open HAL frontend module device(for compatible Android HAL).
CNcomment:打开HAL frontend模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice FrontEnd device structure.CNcomment:FrontEnd设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
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
\brief  Close HAL frontend module device.CNcomment: 关闭HAL frontend模块设备 CNend
\attention \n
Close HAL frontend module deinit(for compatible Android HAL).
CNcomment:关闭HAL frontend模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice frontEnd device structure.CNcomment:frontEnd设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
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

