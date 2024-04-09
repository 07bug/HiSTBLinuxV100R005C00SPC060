/***********************************************************************************
*              Copyright 2015 - 2025, skyworth . Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tvos_hal_frontend.c
* Description:
*
* History:
* Version   Date               Author     DefectNum    Description
* main\1    2015-09-23         hhc        NULL         Create this file.
***********************************************************************************/

#define LOG_TAG "frontend"
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#include <sys/ioctl.h>
#include <sys/time.h>

#include <pthread.h>

#ifndef LINUX_OS
#include <cutils/log.h>
#include <cutils/atomic.h>
#include <cutils/properties.h>
#endif

#include "tvos_hal_frontend.h"
#include "tvos_hal_errno.h"
#include "tvos_hal_common.h"

#include "ini_iofile.h"

#include "hi_unf_demux.h"
#include "hi_unf_i2c.h"
#include "hi_unf_gpio.h"
#include "hi_unf_frontend.h"
#include "hi_unf_version.h"

/*****************************************************************************/
/*lint -e655 */

#ifndef __unused
#define __unused
#endif

#define HAL_TV_PRODUCT_CODE 2
#define HAL_STB_PRODUCT_CODE 1

#ifdef LINUX_OS
#define HAL_FACTORY_DIR "/usr/data/frontend/"
#else
#if (HAL_TV_PRODUCT_CODE == UNF_PRODUCT_CODE)
#define HAL_FACTORY_DIR "/atv/dtv/etc/"
#else
#define HAL_FACTORY_DIR "/etc/dtv/"
#endif
#endif

#define FRONTEND_CONFIG_INI_PATH           HAL_FACTORY_DIR "frontend_config.ini"

#define FRONTEND_MODE_ID                   (0x1f01) //mode id


#define FRONTEND_MSG_RECIEVE_TIMEOUT       (200)
#define FRONTEND_SIG_LOST_CHECK_COUNT      (5)      //if signal never lock,  (FE_SIG_LOST_CHECK_COUNT * FE_SIG_STATUS_CHECK_INTERVAL)ms will get signal unlock message
#define FRONTEND_SIG_UNLOCK_CHECK_COUNT    (15)     //if signal never lock,  (FRONTEND_SIG_UNLOCK_CHECK_COUNT * FE_SIG_STATUS_CHECK_INTERVAL)ms will get signal unlock message

#define NEED_RESET           (1)
#define NOT_NEED_RESET       (0)
#define USE_GPIO_I2C         (1)
#define NOT_USE_GPIO_I2C     (0)
#define TS_OUT_REDEINE       (1)
#define TS_OUT_DATA_NUM      (8)
#define FE_INVILID_COORDINATE       (0xffff)
#define FRONTEND_INI_KEY_MAX_LENGTH (256)

#define FRONTEND_MAX_COUNT (8)
#define FRONTEND_REG_CALLBACK_COUNT (8)
#define FRONTEND_PIN_REUSE_MAX_COUNT (64)

/*define default value of device init*/
#define DEF_TUNER_NUM             (1)
#define DEF_SIG_TYPE              (HI_UNF_TUNER_SIG_TYPE_SAT)
#define DEF_TUNRE_DEVICEID        (0)
#define DEF_TUNRE_SIGTYPE         (1)
#define DEF_TUNRE_STATUS          (0)
#define DEF_TUNER_TYPE            (HI_UNF_TUNER_DEV_TYPE_SHARP7903)
#define DEF_DEMOD_TYPE            (HI_UNF_DEMOD_DEV_TYPE_AVL6211)
#define DEF_TUNER_OUT_PUT_MOD     (HI_UNF_TUNER_OUTPUT_MODE_SERIAL)
#define DEF_TUNER_I2C_ADDR        (192)
#define DEF_DEMOD_I2C_ADDR        (12)
#define DEF_I2C_TYPE              (USE_GPIO_I2C)/*if this is USE_GPIO_I2C,should config the pin of gpip i2c,else should config DEF_I2C_CHN_NUM*/
#define DEF_I2C_CHN_NUM           (0)
#define DEF_GPIO_I2C_CLK_GRP      (11)
#define DEF_GPIO_I2C_CLK_BIT      (3)
#define DEF_GPIO_I2C_SDA_GRP      (12)
#define DEF_GPIO_I2C_SDA_BIT      (5)
#define DEF_RST_TYPE              (NEED_RESET)/*if this is NEED_RESET, should config DEF_RST_USE_GPIO*/
#define DEF_RST_USE_GPIO          (68)/*GPIO8_4*/
#define DEF_DEMOD_TS_OUT_MOD      (0)
#define DEF_TS_DATA_LINE_OUT_SEL  (0x76543210)
#define DEF_TS_CTRL_LINE_OUT_SEL  (0xa89)
#define DEF_TS_PORT_ID            (1)/**/
#define DEF_DEMUX_ID              (0)/**/
#define DEF_DEMUX_PORT_TYPE       (HI_UNF_DMX_PORT_TYPE_SERIAL)/**/
#define DEF_SER_BIT_SEL           (0)/*Port line sequence select In parallel mode: 0: cdata[7] is the most significant bit (MSB) (default). 1: cdata[0] is the MSB.
                                                                In serial mode: 1: cdata[0] is the data line (default). 0: cdata[7] is the data line.*/
#define DEF_SAT_DEMOD_CLK         (16000)/*KHz,The possible values are 4000,4500,10000,16000,27000 for AV6211*/
#define DEF_SAT_TUNER_MAX_LPF     (34)/**/
#define DEF_SAT_TUNER_I2C_CLK     (400)/*khz*/
#define DEF_SAT_RF_AGC            (HI_UNF_TUNER_RFAGC_INVERT)
#define DEF_SAT_IQ_SPECTRUM       (HI_UNF_TUNER_IQSPECTRUM_NORMAL)
#define DEF_SAT_TS_CLK_POLAR      (HI_UNF_TUNER_TSCLK_POLAR_RISING)
#define DEF_SAT_TS_FORMAT         (HI_UNF_TUNER_TS_FORMAT_TS)
#define DEF_SAT_TS_SER_PIN        (HI_UNF_TUNER_TS_SERIAL_PIN_0)
#define DEF_SAT_DISEQC_WAVE       (HI_UNF_TUNER_DISEQCWAVE_NORMAL)/**/
#define DEF_SAT_LNB_CTRL_DEV      (HI_UNF_LNBCTRL_DEV_TYPE_ISL9492)/**/
#define DEF_SAT_LNB_CTRL_DEV_I2C_ADDR    (16)/*default addr of MPS8125 is 0,default addr of ISL9492 is 16*/

#define DEF_TER_DEMOD_CLK         (24000)/*khz*/
#define DEF_TER_TUNER_MAX_LPF     (34)/**/
#define DEF_TER_TUNER_I2C_CLK     (400)/*khz*/
#define DEF_TER_RESET_GPIO_NO     (0)
#define DEF_TER_RF_AGC            (HI_UNF_TUNER_RFAGC_INVERT)
#define DEF_TER_IQ_SPECTRUM       (HI_UNF_TUNER_IQSPECTRUM_NORMAL)
#define DEF_TER_TS_CLK_POLAR      (HI_UNF_TUNER_TSCLK_POLAR_FALLING)
#define DEF_TER_TS_FORMAT         (HI_UNF_TUNER_TS_FORMAT_TS)
#define DEF_TER_TS_SER_PIN        (HI_UNF_TUNER_TS_SERIAL_PIN_0)
#define DEF_TER_TS_SYNC_HEAD      (0)/*see HI_UNF_TUNER_TS_SYNC_HEAD_E,this enum defined by UNF3.2 so use number */

#define DEF_TER_RELOCK_STATUS_DEFAULT (0)
#define DEF_TER_RELOCK_TTIMEOUT   (1000)
#define DEF_TER_RELOCK_T2TIMEOUT  (2000)
#define DEF_TER_DMX_PORT_INCLK     (0)/**<Whether to reverse the phase of the clock input from the tuner*/ /**< CNcomment:Tuner输入时钟是否反相.0: 同相(默认); 1: 反相*/
#define DEF_TER_DMX_PORT_SHARECLK  (HI_UNF_DMX_PORT_BUTT)/**<Port of clock that this port shared, only valid for TSI port tpye *//**< CNcomment:指定该端口所复用时钟的对应端口，该成员仅对TSI端口类型有效*/

/** CAB*/
#define CAB_RF_MIN                  (45000)     /**<kHz*/
#define CAB_RF_MAX                  (870000)    /**<kHz*/
#define CAB_SYMBOLRATE_MIN          (900000)
#define CAB_SYMBOLRATE_MAX          (7200000)

/** TER*/
#define TER_RF_MIN                  (48000)     /**<kHz*/
#define TER_RF_MAX                  (870000)    /**<kHz*/
#define TER_BW_MIN                  (1700)      /**<kHz*/
#define TER_BW_MAX                  (10000)     /**<kHz*/

/** SAT*/
#define SAT_C_MIN_KHZ               (3000000)
#define SAT_C_MAX_KHZ               (4800000)
#define SAT_KU_MIN_KHZ              (10600000)
#define SAT_KU_MID_KHZ              (11700000)
#define SAT_KU_MAX_KHZ              (12750000)
#define SAT_C_MIN_LOWLO             (3000 + 950)
#define SAT_C_MAX_HIGHLO            (4200 + 2150)
#define SAT_KU_MIN_LOWLO            (10600 - 2150)
#define SAT_KU_MAX_HIGHLO           (12750 - 950)

#define SAT_MOTOR_CHECK_DEFAULT_TIMEOUT (30000) //ms

/** ISDB-T*/
#define ISDBT_RF_MIN                (93000)     /**<kHz*/
#define ISDBT_RF_MAX                (870000)    /**<kHz*/
#define ISDBT_BW_MIN                (6000)      /**<kHz*/
#define ISDBT_BW_MAX                (8000)      /**<kHz*/

#define SAT_SYMBOLRATE_MAX          (60000000)  /**<(45000000)*/

#define SAT_DEFAULT_MOTOR_TIMEOUT   (30*1000) /*30 s*/

#define FRONTEND_DEVICE_NUM 1

#define HI_UNF_TUNER_SIG_TYPE_DVBT_ALL (HI_UNF_TUNER_SIG_TYPE_DVB_T | HI_UNF_TUNER_SIG_TYPE_DVB_T2)
#define FRONTEND_FE_CABLE_ALL (FRONTEND_FE_CABLE1 | FRONTEND_FE_CABLE2)
#define FRONTEND_FE_SATELLITE_ALL (FRONTEND_FE_SATELLITE1 | FRONTEND_FE_SATELLITE2)
#define FRONTEND_FE_TERRESTRIAL_ALL (FRONTEND_FE_TERRESTRIAL1 | FRONTEND_FE_TERRESTRIAL2)
/*****************************************************************************/

#define FRONTEND_CHECK_PTR(ptr)\
    do {\
        if (NULL == ptr)\
        {\
            HAL_ERROR("ERROR_NULL_PTR");\
            return ERROR_NULL_PTR;\
        }\
    } while(0)

#define FRONTEND_CHECK_INIT()\
    do {\
        if (FALSE == s_bFeInit)\
        {\
            HAL_ERROR("ERROR_NOT_INITED");\
            return ERROR_NOT_INITED;\
        }\
    } while(0)

#define FRONTEND_CHECK_RETURN_ERR(val, ret)                            \
    do {                                                    \
        if ((val))                                          \
        {                                                   \
            HAL_ERROR("ERROR[%d]: %d", __LINE__, ret);                       \
            return ret;                                    \
        }                                                   \
    } while (0)

#define FRONTEND_CHECK_DOFUNC(func)                            \
    do{                                         \
        S32 s32FeRet = 0 ;                        \
        s32FeRet = func ;                            \
        if(s32FeRet != SUCCESS)                   \
        {                                        \
            HAL_ERROR("%s fail:%d" , #func, s32FeRet);           \
        };                                       \
    }while(0)
#define FRONTEND_CHECK_DOFUNC_RETURN(func)                            \
    do{                                         \
        HI_S32 s32FeRet = 0 ;                        \
        s32FeRet = func ;                            \
        if(s32FeRet != SUCCESS)                   \
        {                                        \
            HAL_ERROR("%s fail:%d" , #func, s32FeRet);          \
            return s32FeRet;                        \
        };                                       \
    }while(0)

#define FRONTEND_LOCK()    pthread_mutex_lock(&s_frontend_mutex)
#define FRONTEND_UNLOCK()  pthread_mutex_unlock(&s_frontend_mutex)

/*****************************************************************************/

struct frontend_context_t
{
    FRONTEND_DEVICE_S device;
    /* our private state goes below here */
};

typedef struct msg_event_s
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    U8 state;
} MSG_EVENT_S;

/** MSG type *//** CNcomment:MSG type*/
typedef enum _FRONTEND_MSG_TYPE_E
{
    FRONTEND_MSG_SCAN_FREQ,
    FRONTEND_MSG_SET_ANTENNA,
    FRONTEND_MSG_SEND_EVENT,
    FRONTEND_MSG_STATUS_IDLE,
    FRONTEND_MSG_STATUS_GO,
    FRONTEND_MSG_BUTT
} FRONTEND_MSG_TYPE_E;

/** INIT type *//** CNcomment:INIT type*/
typedef enum _FRONTEND_INIT_TYPE_E
{
    FRONTEND_INIT_FIRST_TIME,
    FRONTEND_INIT_SIGNAL_CHANGE,
    FRONTEND_INIT_REINIT,
    FRONTEND_INIT_BUTT
} FRONTEND_INIT_TYPE_E;

/** INIT type *//** CNcomment:INIT type*/
typedef enum _FRONTEND_ANTENNA_SET_TYPE_E
{
    FRONTEND_ANTENNA_SET_FIRST,
    FRONTEND_ANTENNA_SET_RELOCK,
    FRONTEND_ANTENNA_SET_FORCE,
    FRONTEND_ANTENNA_SET_BUTT
} FRONTEND_ANTENNA_SET_TYPE_E;

/** T T2 signal auto lock*/
typedef struct _FRONTEND_TER_RELOCK_PARAM_S
{
    BOOL                     bTT2AutoLock;
    BOOL                     bTSignalTry;
    BOOL                     bT2SignalTry;
    U32                      u32StartTime;       //record connect begin time everytime
    U32                      u32Timeout;         //record timeout every connect
    U32                      u32TSignalTimeout;  //setted by user, T sig timeout
    U32                      u32T2SignalTimeout; //setted by user, T2 sig timeout
} FRONTEND_TER_RELOCK_PARAM_S;

/** ini cfg info*/
typedef struct _FRONTEND_SYSCFG_INFO_S
{
    HI_U32 u32TunerDeviceID;
    HI_U32 u32TunerSigType;
    HI_U32 u32TunerDeviceStatus;
    HI_U32 u32I2cType;
    HI_U32 u32TunerRstType;
    HI_U32 u32DemodTsOutMode;
    HI_U32 u32TsDataLineOutSel;
    HI_U32 u32TsCtrlLineOutSel;
    HI_U32 u32TsPortId;
    HI_U32 u32DemuxPortType;
    HI_U32 u32SerBitSel;
    HI_U32 u32TunerInClk;
    HI_U32 u32SatMotorTimeout;

    HI_UNF_DMX_PORT_E enSerialPortShareClk;

    FRONTEND_TER_RELOCK_PARAM_S stTRelockParam;
    HI_UNF_TUNER_ATTR_S stTunerAttr;
    HI_UNF_TUNER_SAT_ATTR_S* pstSatAttr;
    HI_UNF_TUNER_TER_ATTR_S* pstTunerTerAttr;
} FRONTEND_SYSCFG_INFO_S;

/** T2 PLP param*/
typedef struct _FRONTEND_TER2_PLP_PARAM_S
{
    BOOL                bNeedSetCommonPlpID;
    BOOL                bNeedSetCommonPlpCombination;
    U8                  u8T2PlpID;
    U8                  u8T2CommonPlpID;
    U8                  u8T2CommonPlpCombination;
} FRONTEND_TER2_PLP_PARAM_S;

typedef struct _FRONTEND_DEV_INFO_S
{
    HANDLE                            hDevice;
    U32                               u32TunerId;
    U32                               u32Capability;
    FRONTEND_FE_TYPE_E                enSignalType;
    HI_UNF_DMX_PORT_E                 enDemuxPort;
    BOOL                              bDevValid;// same as   bInit;
    FRONTEND_OPEN_PARAMS_S            stOpenParam;
    BOOL                              bOpen;
    FRONTEND_FE_STATUS_E              enNewStatus;
    FRONTEND_FE_STATUS_E              enOldStatus;
    FRONTEND_SCAN_INFO_S              stScanInfo;  //same as    SVR_FE_ALLCONNECT_PARAM_S   stAllConnectParam;
    HI_UNF_TUNER_CONNECT_PARA_S       stUnfConnectPara;

    FRONTEND_REG_CALLBACK_PARAMS_S    astCallback[FRONTEND_REG_CALLBACK_COUNT];  //same as    SVR_FE_CALLBACK_INFO_S      stCallbackFunc;   SVR_FE_USER_S               stUser[FE_MAX_USER];
    pthread_t                         hTask;  // same as   SVR_FE_CHECKTASK_INFO_S     stCheckTaskInfo;
    MSG_EVENT_S*                      pstMsgEvt;    // same as   HI_MsgQueue_p               pFEMsgQueue;
    FRONTEND_MSG_TYPE_E               enMsgInfo;
    U32                               u32FeStatusCheckCount;
    U32                               u32FeSatRelockCount;
    BOOL                              bFreqSameAsLastScan;

    //for S2
    U8                                u8S2IsiID;

    //for T2
    FRONTEND_TER_RELOCK_PARAM_S       stTRelockParam;
    FRONTEND_TER2_PLP_PARAM_S         stT2PlpParam;

    //for S blindscan
    BOOL                              bBlindScan;
    FRONTEND_SAT_BLINDSCAN_PARA_S     stBlindScanParam;

    //for S antenna
    FRONTEND_SAT_LNB_CONFIG_S         stLnbCfg;
    FRONTEND_LNB_POWER_E              enLnbPower;
    FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S stScanExAntennaInfo; // for sat antenna,connect scan param
    FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S stCurExAntennaInfo; // for sat antenna,save cur antenna param
    HI_UNF_TUNER_DISEQC_SWITCH4PORT_S stSatSwitch4PortParam;
    //motor
    BOOL                              bMotorManual;
    U16                               u16Angular;
    //U32                             u32MotorStartTime;          //time moto start turn
    U32                               u32MotorTimeout;

    //U32                             u32DiSEqCCmdInterval;

} FRONTEND_DEV_INFO_S;

#ifndef LINUX_OS
static FRONTEND_DEVICE_S*    module_device      = NULL;
#endif
static pthread_mutex_t      s_frontend_mutex    = PTHREAD_MUTEX_INITIALIZER;
//static pthread_mutex_t      s_frontend_mutex    = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

static BOOL                 s_bFeInit     = FALSE;

static U32 s_u32FeCfgNum = 0;
static U32 s_u32FeNum = 0;

static U32 s_u32TimeBegin = 0;
static U32 s_u32TimeUsed = 0;

static FRONTEND_SYSCFG_INFO_S* s_pstFeCfgInfo = NULL;
static FRONTEND_DEV_INFO_S* s_pstFeDevInfo = NULL;

static FRONTEND_COORDINATE_S s_stCoordinate;

static U32 time_get_now(HI_VOID)
{
    struct timespec ts;
    S32 s32Ret = SUCCESS;
    s32Ret = clock_gettime(CLOCK_MONOTONIC, &ts);

    if (s32Ret < 0)
    { return 0; }
    else
    { return (U32)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000); }
}

static S32 msg_event_create(MSG_EVENT_S** p_event_id, const U32 init_is_set)
{
    S32 s32Ret = SUCCESS;
    MSG_EVENT_S* e = (MSG_EVENT_S*) malloc (sizeof(MSG_EVENT_S));

    if (NULL == e)
    {
        HAL_ERROR("not malloc mem. ");

        return ERROR_NO_MEMORY;
    }

    s32Ret = pthread_mutex_init(&e->mutex, NULL);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("event id [%p] error", *p_event_id);
        free(e);

        return FAILURE;
    }

    s32Ret = pthread_mutex_lock(&e->mutex);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("event id [%p] error", *p_event_id);
        pthread_mutex_unlock(&e->mutex);
        pthread_mutex_destroy(&e->mutex);
        free(e);

        return FAILURE;

    }

    s32Ret = pthread_cond_init(&e->cond, NULL);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("event id [%p] error", *p_event_id);
        pthread_mutex_unlock(&e->mutex);
        pthread_mutex_destroy(&e->mutex);
        free(e);

        return FAILURE;
    }

    if (init_is_set)
    { e->state = 1; }
    else
    { e->state = 0; }

    *p_event_id = e;
    s32Ret = pthread_mutex_unlock(&e->mutex);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("event id [%p] error", *p_event_id);
        pthread_mutex_destroy(&e->mutex);
        s32Ret = pthread_cond_destroy(&e->cond);
        return FAILURE;
    }

    return SUCCESS;
}

static S32 msg_event_destroy(MSG_EVENT_S* event_id)
{
    S32 s32Ret = SUCCESS;

    MSG_EVENT_S* e = event_id;

    if (NULL == e)
    {
        HAL_ERROR("event id is error [%p] ", event_id);
        return ERROR_NULL_PTR;
    }

    s32Ret = pthread_mutex_lock(&e->mutex);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("event id [%p] error", event_id);
    }

    s32Ret = pthread_cond_signal(&e->cond);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("event id [%p] error", event_id);
    }

    s32Ret = pthread_mutex_unlock(&e->mutex);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("event id [%p] error", event_id);
    }

    usleep(10 * 1000);

    s32Ret = pthread_cond_destroy(&e->cond);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("destroy event [%p] cond failed", event_id);
    }

    pthread_mutex_destroy(&e->mutex);
    free(e);

    return SUCCESS;
}

static S32 msg_event_wait(MSG_EVENT_S*  event_id, const U32 is_auto_reset, const U32 timeout_ms)
{
    struct timespec tout;
    struct timeval  tm;

    S32 s32Ret = SUCCESS;

    MSG_EVENT_S* e = event_id;

    HAL_CHK_RETURN_NO_PRINT((NULL == e), ERROR_NULL_PTR);

    if ((0xffffffff) == timeout_ms)
    {
        s32Ret = pthread_mutex_lock(&e->mutex);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "event id [%p] error. ", event_id);

        if (e->state != 1)
        {
            pthread_cond_wait(&e->cond, &e->mutex);
        }

        if (is_auto_reset)
        {
            e->state = 1;
        }
        else
        {
            e->state = 0;
        }

        s32Ret = pthread_mutex_unlock(&e->mutex);
        HAL_CHK_PRINTF((SUCCESS != s32Ret), "event id [%p] error", event_id);

        return SUCCESS;
    }

    gettimeofday(&tm, NULL);
    tout.tv_sec  = tm.tv_sec + (timeout_ms) / 1000;
    tout.tv_nsec = tm.tv_usec * 1000 + ((timeout_ms) % 1000) * 1000000;

    if (tout.tv_nsec >= (1E+9))
    {
        tout.tv_sec++;
        tout.tv_nsec -= (1E+9);
    }

    s32Ret = pthread_mutex_lock(&e->mutex);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "event id [%p] error", event_id);

    while (e->state != 1)
    {
        s32Ret = pthread_cond_timedwait(&e->cond, &e->mutex, &tout);

        if (ETIMEDOUT == s32Ret)
        {
            pthread_mutex_unlock(&e->mutex);
            return FAILURE;
        }
    }

    if (is_auto_reset)
    { e->state = 1; }
    else
    { e->state = 0; }

    s32Ret = pthread_mutex_unlock(&e->mutex);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "event id [%p] error", event_id);

    return SUCCESS;

}

static S32 msg_event_set(MSG_EVENT_S* event_id)
{
    MSG_EVENT_S* e = event_id;
    S32 s32Ret = SUCCESS;

    if (e == NULL)
    { return  ERROR_NULL_PTR; }

    s32Ret = pthread_mutex_lock(&e->mutex);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "event id [%p] error", event_id);

    e->state = 1;
    s32Ret = pthread_cond_signal(&e->cond);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "event id [%p] error", event_id);

    s32Ret = pthread_mutex_unlock(&e->mutex);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "event id [%p] error", event_id);

    return SUCCESS;
}

static S32 msg_event_reset(MSG_EVENT_S*  event_id)
{
    S32 s32Ret = SUCCESS;
    MSG_EVENT_S* e = event_id;

    if (NULL == e)
    { return  ERROR_NULL_PTR; }

    s32Ret = pthread_mutex_lock(&e->mutex);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "event id [%p] error", event_id);

    e->state = 0;
    s32Ret = pthread_mutex_unlock(&e->mutex);
    HAL_CHK_PRINTF((SUCCESS != s32Ret), "event id [%p] error", event_id);

    return 0;
}

#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)
static U32 conver_lnb_power_to_unf(U32 u32HalLnbPower)
{
    switch (u32HalLnbPower)
    {
        case FRONTEND_LNB_POWER_OFF:
            return HI_UNF_TUNER_FE_LNB_POWER_OFF;
        case FRONTEND_LNB_POWER_ON:
            return HI_UNF_TUNER_FE_LNB_POWER_ON;
        case FRONTEND_LNB_POWER_ENHANCED:
            return HI_UNF_TUNER_FE_LNB_POWER_ENHANCED;
        default:
            return HI_UNF_TUNER_FE_LNB_POWER_ON;
    }
}
#endif

static U32 conver_lnb_22k_to_unf(U32 u32HalLnb22k)
{
    switch (u32HalLnb22k)
    {
        case FRONTEND_LNB_22K_OFF:
            return HI_UNF_TUNER_FE_LNB_22K_OFF;
        case FRONTEND_LNB_22K_ON:
            return HI_UNF_TUNER_FE_LNB_22K_ON;
        default:
            return HI_UNF_TUNER_FE_LNB_22K_OFF;
    }
}

static VOID conver_lnb_config_to_unf(const FRONTEND_SAT_LNB_CONFIG_S* const pstLNBParam, HI_UNF_TUNER_FE_LNB_CONFIG_S* const pstUnfLNB)
{
    pstUnfLNB->enLNBType = (HI_UNF_TUNER_FE_LNB_TYPE_E)pstLNBParam->enLNBType;
    pstUnfLNB->u32LowLO = pstLNBParam->u32LowLO;
    pstUnfLNB->u32HighLO = pstLNBParam->u32HighLO;
    pstUnfLNB->enLNBBand = (HI_UNF_TUNER_FE_LNB_TYPE_E)pstLNBParam->enLNBBand;
    pstUnfLNB->u8UNIC_SCRNO = pstLNBParam->u32UNIC_SCRNO;
    pstUnfLNB->u32UNICIFFreqMHz = pstLNBParam->u32UNICIFFreqMHz;
    pstUnfLNB->enSatPosn = (FRONTEND_UNICABLE_SATPOSITION_E)pstLNBParam->enSatPosn;
    return;
}

static U32 conver_signal_to_unf(U32 u32HalSigType)
{
    switch (u32HalSigType)
    {
        case FRONTEND_FE_CABLE1:
        case FRONTEND_FE_CABLE2:
        case ((FRONTEND_FE_TYPE_E)(FRONTEND_FE_CABLE1 | FRONTEND_FE_CABLE2)):
            return HI_UNF_TUNER_SIG_TYPE_CAB;

        case FRONTEND_FE_SATELLITE1:
        case FRONTEND_FE_SATELLITE2:
        case ((FRONTEND_FE_TYPE_E)(FRONTEND_FE_SATELLITE1 | FRONTEND_FE_SATELLITE2)):
            return HI_UNF_TUNER_SIG_TYPE_SAT;

        case FRONTEND_FE_TERRESTRIAL1:
            return HI_UNF_TUNER_SIG_TYPE_DVB_T;

        case FRONTEND_FE_TERRESTRIAL2:
            return HI_UNF_TUNER_SIG_TYPE_DVB_T2;

        case ((FRONTEND_FE_TYPE_E)FRONTEND_FE_TERRESTRIAL_ALL):
            return HI_UNF_TUNER_SIG_TYPE_DVBT_ALL;

        case FRONTEND_FE_DTMB1:
            return HI_UNF_TUNER_SIG_TYPE_DTMB;

        case FRONTEND_FE_ISDBT1:
            return HI_UNF_TUNER_SIG_TYPE_ISDB_T;

        default:
            return HI_UNF_TUNER_SIG_TYPE_BUTT;
    }
}

static HI_UNF_MODULATION_TYPE_E conver_mod_to_unf(FRONTEND_MODULATION_E enModType)
{
    switch (enModType)
    {
        case FRONTEND_MOD_QAM16:
            return HI_UNF_MOD_TYPE_QAM_16;

        case FRONTEND_MOD_QAM32:
            return HI_UNF_MOD_TYPE_QAM_32;

        case FRONTEND_MOD_QAM64:
            return HI_UNF_MOD_TYPE_QAM_64;

        case FRONTEND_MOD_QAM128:
            return HI_UNF_MOD_TYPE_QAM_128;

        case FRONTEND_MOD_QAM256:
            return HI_UNF_MOD_TYPE_QAM_256;

        case FRONTEND_MOD_QPSK:
            return HI_UNF_MOD_TYPE_QPSK;

        case FRONTEND_MOD_8PSK:
            return HI_UNF_MOD_TYPE_8PSK;

        case FRONTEND_MOD_BPSK:
            return HI_UNF_MOD_TYPE_BPSK;

        default:
            return HI_UNF_MOD_TYPE_BUTT;
    }
}

static U32 conver_bandwidth_to_unf(FRONTEND_BAND_WIDTH_E enBandwidth)
{
    U32 u32Bandwidth = 8000;

    if (FRONTEND_BANDWIDTH_7_MHZ == enBandwidth)
    {
        u32Bandwidth = 7000;
    }
    else if (FRONTEND_BANDWIDTH_6_MHZ == enBandwidth)
    {
        u32Bandwidth = 6000;
    }

    return u32Bandwidth;
}

static HI_UNF_TUNER_FE_POLARIZATION_E conver_polar_to_unf(FRONTEND_POLARIZATION_E enPolar)
{
    switch (enPolar)
    {
        case FRONTEND_PLR_HORIZONTAL:
            return HI_UNF_TUNER_FE_POLARIZATION_H;

        case FRONTEND_PLR_VERTICAL:
            return HI_UNF_TUNER_FE_POLARIZATION_V;

        case FRONTEND_PLR_LEFT:
            return HI_UNF_TUNER_FE_POLARIZATION_L;

        case FRONTEND_PLR_RIGHT:
            return HI_UNF_TUNER_FE_POLARIZATION_R;

        default:
            return HI_UNF_TUNER_FE_POLARIZATION_H;
    }
}

static S32 conver_scan_param_to_unf(const FRONTEND_SCAN_INFO_S* pstScanInfo, HI_UNF_TUNER_CONNECT_PARA_S* pstConnParam)
{
    S32 s32Ret = SUCCESS;

    switch (pstScanInfo->enFrontendType)
    {
        case FRONTEND_FE_CABLE1:
        case FRONTEND_FE_CABLE2:
        {
            pstConnParam->unConnectPara.stCab.bReverse = HI_FALSE;

            if (FRONTEND_SPECTRUM_INVERSION == pstScanInfo->unScanInfo.stCabInfo.enSpectrum)
            {
                pstConnParam->unConnectPara.stCab.bReverse = HI_TRUE;
            }

            pstConnParam->unConnectPara.stCab.enModType = conver_mod_to_unf(pstScanInfo->unScanInfo.stCabInfo.enModulation);

            pstConnParam->enSigType                         = HI_UNF_TUNER_SIG_TYPE_CAB;
            pstConnParam->unConnectPara.stCab.u32Freq       = pstScanInfo->unScanInfo.stCabInfo.u32Freq;
            pstConnParam->unConnectPara.stCab.u32SymbolRate = pstScanInfo->unScanInfo.stCabInfo.u32Sym;

        }
        break;

        case FRONTEND_FE_SATELLITE1:
        case FRONTEND_FE_SATELLITE2:
        {
            pstConnParam->unConnectPara.stSat.enPolar = conver_polar_to_unf(pstScanInfo->unScanInfo.stSatInfo.enPolar);

            pstConnParam->enSigType                         = HI_UNF_TUNER_SIG_TYPE_SAT;
            pstConnParam->unConnectPara.stSat.u32Freq       = pstScanInfo->unScanInfo.stSatInfo.u32Freq;
            pstConnParam->unConnectPara.stSat.u32SymbolRate = pstScanInfo->unScanInfo.stSatInfo.u32Sym;
#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)
            pstConnParam->unConnectPara.stSat.u32ScrambleValue = pstScanInfo->unScanInfo.stSatInfo.u32ScrambleValue;
#endif
        }

        break;

        case FRONTEND_FE_TERRESTRIAL1:
        case FRONTEND_FE_TERRESTRIAL2:
        {
            pstConnParam->unConnectPara.stTer.bReverse = HI_FALSE;

            if (FRONTEND_SPECTRUM_INVERSION == pstScanInfo->unScanInfo.stTerInfo.enSpectrum)
            {
                pstConnParam->unConnectPara.stTer.bReverse = HI_TRUE;
            }

            pstConnParam->unConnectPara.stTer.enModType = conver_mod_to_unf(pstScanInfo->unScanInfo.stTerInfo.enModulation);
            pstConnParam->unConnectPara.stTer.u32BandWidth = conver_bandwidth_to_unf(pstScanInfo->unScanInfo.stTerInfo.enBandWidth);

            pstConnParam->enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T;

            if (FRONTEND_FE_TERRESTRIAL2 == pstScanInfo->enFrontendType)
            {
                pstConnParam->enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T2;
            }

            pstConnParam->unConnectPara.stTer.u32Freq = pstScanInfo->unScanInfo.stTerInfo.u32Freq;
        }

        break;

        case FRONTEND_FE_DTMB1:
        {
            pstConnParam->unConnectPara.stTer.bReverse = HI_FALSE;

            if (FRONTEND_SPECTRUM_INVERSION == pstScanInfo->unScanInfo.stDtmbInfo.enSpectrum)
            {
                pstConnParam->unConnectPara.stTer.bReverse = HI_TRUE;
            }

            pstConnParam->unConnectPara.stTer.enModType = conver_mod_to_unf(pstScanInfo->unScanInfo.stDtmbInfo.enModulation);
            pstConnParam->unConnectPara.stTer.u32BandWidth = conver_bandwidth_to_unf(pstScanInfo->unScanInfo.stDtmbInfo.enBandWidth);

            pstConnParam->enSigType = HI_UNF_TUNER_SIG_TYPE_DTMB;
            pstConnParam->unConnectPara.stTer.u32Freq       = pstScanInfo->unScanInfo.stTerInfo.u32Freq;
        }

        break;

        case FRONTEND_FE_ISDBT1:
        {
            pstConnParam->unConnectPara.stTer.bReverse = HI_FALSE;

            if (FRONTEND_SPECTRUM_INVERSION == pstScanInfo->unScanInfo.stTerInfo.enSpectrum)
            {
                pstConnParam->unConnectPara.stTer.bReverse = HI_TRUE;
            }

            pstConnParam->unConnectPara.stTer.enModType = conver_mod_to_unf(pstScanInfo->unScanInfo.stTerInfo.enModulation);
            pstConnParam->unConnectPara.stTer.u32BandWidth = conver_bandwidth_to_unf(pstScanInfo->unScanInfo.stTerInfo.enBandWidth);

            pstConnParam->enSigType = HI_UNF_TUNER_SIG_TYPE_ISDB_T;
            pstConnParam->unConnectPara.stTer.u32Freq       = pstScanInfo->unScanInfo.stTerInfo.u32Freq;
        }

        break;

        default:
            s32Ret = FAILURE;
            break;
    }

    return s32Ret;
}

static FRONTEND_POLARIZATION_E conver_polar_to_hal(HI_UNF_TUNER_FE_POLARIZATION_E enPolar)
{
    switch (enPolar)
    {
        case HI_UNF_TUNER_FE_POLARIZATION_H:
            return FRONTEND_PLR_HORIZONTAL;

        case HI_UNF_TUNER_FE_POLARIZATION_V:
            return FRONTEND_PLR_VERTICAL;

        case HI_UNF_TUNER_FE_POLARIZATION_L:
            return FRONTEND_PLR_LEFT;

        case HI_UNF_TUNER_FE_POLARIZATION_R:
            return FRONTEND_PLR_RIGHT;

        default:
            return FRONTEND_PLR_BUTT;
    }
}

#if 0 //conver from unf to hal, for now no use
static U32 conver_signal_to_hal(U32 u32UnfSigType)
{
    switch (u32UnfSigType)
    {
        case HI_UNF_TUNER_SIG_TYPE_CAB:
            return FRONTEND_FE_CABLE1;

        case HI_UNF_TUNER_SIG_TYPE_SAT:
            return FRONTEND_FE_SATELLITE1;

        case HI_UNF_TUNER_SIG_TYPE_DVB_T:
            return FRONTEND_FE_TERRESTRIAL1;

        case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
            return FRONTEND_FE_TERRESTRIAL2;

        case HI_UNF_TUNER_SIG_TYPE_DTMB:
            return FRONTEND_FE_DTMB1;

        case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
            return FRONTEND_FE_ISDBT1;

        case HI_UNF_TUNER_SIG_TYPE_J83B:
            return FRONTEND_FE_J83B;

        case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
            return FRONTEND_FE_ATSCT;

        default:
            return FRONTEND_FE_BUTT;
    }

    return FRONTEND_FE_BUTT;
}

static FRONTEND_BAND_WIDTH_E conver_bandwidth_to_hal(U32 u32Bindwidth)
{
    FRONTEND_BAND_WIDTH_E enBandwidth = FRONTEND_BANDWIDTH_8_MHZ;

    if (7000 == u32Bindwidth)
    {
        enBandwidth = FRONTEND_BANDWIDTH_7_MHZ;
    }
    else if (6000 == u32Bindwidth)
    {
        enBandwidth = FRONTEND_BANDWIDTH_6_MHZ;
    }

    return enBandwidth;
}

static FRONTEND_MODULATION_E conver_mod_to_hal(HI_UNF_MODULATION_TYPE_E enModType)
{
    switch (enModType)
    {
        case HI_UNF_MOD_TYPE_QAM_16:
            return FRONTEND_MOD_QAM16;

        case HI_UNF_MOD_TYPE_QAM_32:
            return FRONTEND_MOD_QAM32;

        case HI_UNF_MOD_TYPE_QAM_64:
            return FRONTEND_MOD_QAM64;

        case HI_UNF_MOD_TYPE_QAM_128:
            return FRONTEND_MOD_QAM128;

        case HI_UNF_MOD_TYPE_QAM_256:
            return FRONTEND_MOD_QAM256;

        case HI_UNF_MOD_TYPE_QPSK:
            return FRONTEND_MOD_QPSK;

        case HI_UNF_MOD_TYPE_8PSK:
            return FRONTEND_MOD_8PSK;

        case HI_UNF_MOD_TYPE_BPSK:
            return FRONTEND_MOD_BPSK;

        case HI_UNF_MOD_TYPE_16APSK:
            return FRONTEND_MOD_16APSK;

        case HI_UNF_MOD_TYPE_32APSK:
            return FRONTEND_MOD_32APSK;

        case HI_UNF_MOD_TYPE_8VSB:
            return FRONTEND_MOD_8VSB;

        case HI_UNF_MOD_TYPE_16VSB:
            return FRONTEND_MOD_16VSB;

        default:
            return FRONTEND_MOD_BUTT;
    }
}

static S32 conver_scan_param_to_hal(const HI_UNF_TUNER_CONNECT_PARA_S* pstConnParam, FRONTEND_SCAN_INFO_S* pstScanInfo)
{
    S32 s32Ret = SUCCESS;

    switch (pstConnParam->enSigType)
    {
        case HI_UNF_TUNER_SIG_TYPE_CAB:
        {
            pstScanInfo->unScanInfo.stCabInfo.enSpectrum = FRONTEND_SPECTRUM_INVERSION_OFF;

            if (pstConnParam->unConnectPara.stCab.bReverse)
            {
                pstScanInfo->unScanInfo.stCabInfo.enSpectrum = FRONTEND_SPECTRUM_INVERSION;
            }

            pstScanInfo->unScanInfo.stCabInfo.enModulation = conver_mod_to_hal(pstConnParam->unConnectPara.stCab.enModType);

            pstScanInfo->enFrontendType = FRONTEND_FE_CABLE1;
            pstScanInfo->unScanInfo.stCabInfo.u32Freq = pstConnParam->unConnectPara.stCab.u32Freq      ;
            pstScanInfo->unScanInfo.stCabInfo.u32Sym = pstConnParam->unConnectPara.stCab.u32SymbolRate ;

        }
        break;

        case HI_UNF_TUNER_SIG_TYPE_SAT:
        {
            pstScanInfo->unScanInfo.stSatInfo.enPolar = conver_polar_to_hal(pstConnParam->unConnectPara.stSat.enPolar);

            pstScanInfo->enFrontendType = FRONTEND_FE_SATELLITE1;
            pstScanInfo->unScanInfo.stSatInfo.u32Freq = pstConnParam->unConnectPara.stSat.u32Freq      ;
            pstScanInfo->unScanInfo.stSatInfo.u32Sym = pstConnParam->unConnectPara.stSat.u32SymbolRate;
            pstScanInfo->unScanInfo.stSatInfo.u32ScrambleValue = pstConnParam->unConnectPara.stSat.u32ScrambleValue;
        }

        break;

        case HI_UNF_TUNER_SIG_TYPE_DVB_T:
        case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
        {
            pstScanInfo->unScanInfo.stTerInfo.enSpectrum = FRONTEND_SPECTRUM_INVERSION_OFF;

            if (pstConnParam->unConnectPara.stTer.bReverse)
            {
                pstScanInfo->unScanInfo.stTerInfo.enSpectrum = FRONTEND_SPECTRUM_INVERSION;
            }

            pstScanInfo->unScanInfo.stTerInfo.enModulation = conver_mod_to_hal(pstConnParam->unConnectPara.stTer.enModType);
            pstScanInfo->unScanInfo.stTerInfo.enBandWidth = conver_bandwidth_to_hal(pstConnParam->unConnectPara.stTer.u32BandWidth);

            pstScanInfo->enFrontendType = FRONTEND_FE_TERRESTRIAL1;

            if (HI_UNF_TUNER_SIG_TYPE_DVB_T2 == pstConnParam->enSigType)
            {
                pstScanInfo->enFrontendType = FRONTEND_FE_TERRESTRIAL2;
            }

            pstScanInfo->unScanInfo.stTerInfo.u32Freq = pstConnParam->unConnectPara.stTer.u32Freq;
        }
        break;

        case HI_UNF_TUNER_SIG_TYPE_DTMB:
        {
            pstScanInfo->unScanInfo.stDtmbInfo.enSpectrum = FRONTEND_SPECTRUM_INVERSION_OFF;

            if (pstConnParam->unConnectPara.stTer.bReverse)
            {
                pstScanInfo->unScanInfo.stDtmbInfo.enSpectrum = FRONTEND_SPECTRUM_INVERSION;
            }

            pstScanInfo->unScanInfo.stDtmbInfo.enModulation = conver_mod_to_hal(pstConnParam->unConnectPara.stTer.enModType);
            pstScanInfo->unScanInfo.stDtmbInfo.enBandWidth = conver_bandwidth_to_hal(pstConnParam->unConnectPara.stTer.u32BandWidth);

            pstScanInfo->enFrontendType = FRONTEND_FE_DTMB1;
            pstScanInfo->unScanInfo.stDtmbInfo.u32Freq = pstConnParam->unConnectPara.stTer.u32Freq;
        }
        break;

        case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
            //if((src->unScanInfo.stSatInfo.u32Freq == dst->unScanInfo.stSatInfo.u32Freq)
            //   && (src->unScanInfo.stSatInfo.u32Sym == dst->unScanInfo.stSatInfo.u32Sym)
            //   && (src->unScanInfo.stSatInfo.enPolar == dst->unScanInfo.stSatInfo.enPolar))
            //{
            //    return SUCCESS;
            //}
            break;

        default:

            s32Ret = FAILURE;
            break;
    }

    return s32Ret;
}
#endif

static S32 config_free()
{
    U32 i = 0;
    FRONTEND_SYSCFG_INFO_S* pstFeCfgInfo;

    pstFeCfgInfo = s_pstFeCfgInfo;

    for (i = 0; (i < s_u32FeCfgNum) && (pstFeCfgInfo != NULL); i++ , pstFeCfgInfo++)
    {
        if (pstFeCfgInfo->pstTunerTerAttr != NULL)
        {
            free(pstFeCfgInfo->pstTunerTerAttr);
            pstFeCfgInfo->pstTunerTerAttr = NULL;
        }

        if (pstFeCfgInfo->pstSatAttr != NULL)
        {
            free(pstFeCfgInfo->pstSatAttr);
            pstFeCfgInfo->pstSatAttr = NULL;
        }
    }

    if (s_pstFeCfgInfo != NULL)
    {
        free(s_pstFeCfgInfo);
        s_pstFeCfgInfo = NULL;
    }

    return SUCCESS;
}

static S32 config_read_ter_attr(HI_UNF_TUNER_TER_ATTR_S* pTunerTerAttr, HI_CHAR* pszEntry)
{
    FRONTEND_CHECK_PTR(pTunerTerAttr);
    FRONTEND_CHECK_PTR(pszEntry);

    memset(pTunerTerAttr, 0, sizeof(HI_UNF_TUNER_TER_ATTR_S));
    pTunerTerAttr->u32DemodClk = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32TerDemodeClk", DEF_TER_DEMOD_CLK, pszEntry);
#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)
    pTunerTerAttr->u16TunerMaxLPF = (HI_U16)Ini_IOFile_GetValue((HI_CHAR*)"u16TerTunerMaxLPF", DEF_TER_TUNER_MAX_LPF, pszEntry);
    pTunerTerAttr->u16TunerI2CClk = (HI_U16)Ini_IOFile_GetValue((HI_CHAR*)"u16TerTunerI2CClk", DEF_TER_TUNER_I2C_CLK, pszEntry);
    pTunerTerAttr->enIQSpectrum = (HI_UNF_TUNER_IQSPECTRUM_MODE_E)Ini_IOFile_GetValue((HI_CHAR*)"u32TerEnIQSpectrum", DEF_TER_IQ_SPECTRUM, pszEntry);
#endif
    pTunerTerAttr->u32ResetGpioNo = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32TerResetGpioNo", DEF_TER_RESET_GPIO_NO, pszEntry);
    pTunerTerAttr->enRFAGC = (HI_UNF_TUNER_RFAGC_MODE_E)Ini_IOFile_GetValue((HI_CHAR*)"u32TerEnRFAGC", DEF_TER_RF_AGC, pszEntry);
    pTunerTerAttr->enTSClkPolar = (HI_UNF_TUNER_TSCLK_POLAR_E)Ini_IOFile_GetValue((HI_CHAR*)"u32TerEnTsClkPolar", DEF_TER_TS_CLK_POLAR, pszEntry);
    pTunerTerAttr->enTSFormat = (HI_UNF_TUNER_TS_FORMAT_E)Ini_IOFile_GetValue((HI_CHAR*)"u32TerEnTsFormat", DEF_TER_TS_FORMAT, pszEntry);
    pTunerTerAttr->enTSSerialPIN = (HI_UNF_TUNER_TS_SERIAL_PIN_E)Ini_IOFile_GetValue((HI_CHAR*)"u32TerEnTsSerialPIN", DEF_TER_TS_SER_PIN, pszEntry);
    pTunerTerAttr->enTSSyncHead = (HI_UNF_TUNER_TS_SYNC_HEAD_E)Ini_IOFile_GetValue((HI_CHAR*)"u32TerEnTsSyncHead", DEF_TER_TS_SYNC_HEAD, pszEntry);

    return SUCCESS;
}

static S32 config_read_sat_attr(HI_UNF_TUNER_SAT_ATTR_S* pSatAttr, HI_CHAR* pszEntry)
{

    FRONTEND_CHECK_PTR(pSatAttr);
    FRONTEND_CHECK_PTR(pszEntry);

    memset(pSatAttr, 0, sizeof(HI_UNF_TUNER_SAT_ATTR_S));
    pSatAttr->u32DemodClk = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32SatDemodClk", DEF_SAT_DEMOD_CLK, pszEntry);
    pSatAttr->u16TunerMaxLPF = (HI_U16)Ini_IOFile_GetValue((HI_CHAR*)"u32SatTunerMaxLPF", DEF_SAT_TUNER_MAX_LPF, pszEntry);
    pSatAttr->u16TunerI2CClk = (HI_U16)Ini_IOFile_GetValue((HI_CHAR*)"u32SatTunerI2cClk", DEF_SAT_TUNER_I2C_CLK, pszEntry);
    pSatAttr->enRFAGC = (HI_UNF_TUNER_RFAGC_MODE_E)Ini_IOFile_GetValue((HI_CHAR*)"u32SatRfAgc", DEF_SAT_RF_AGC, pszEntry);
    pSatAttr->enIQSpectrum = (HI_UNF_TUNER_IQSPECTRUM_MODE_E)Ini_IOFile_GetValue((HI_CHAR*)"u32SatIqSpectrum", DEF_SAT_IQ_SPECTRUM, pszEntry);
    pSatAttr->enTSClkPolar = (HI_UNF_TUNER_TSCLK_POLAR_E)Ini_IOFile_GetValue((HI_CHAR*)"u32SatTsClkPolar", DEF_SAT_TS_CLK_POLAR, pszEntry);
    pSatAttr->enTSFormat = (HI_UNF_TUNER_TS_FORMAT_E)Ini_IOFile_GetValue((HI_CHAR*)"u32SatTsFormat", DEF_SAT_TS_FORMAT, pszEntry);
    pSatAttr->enTSSerialPIN = (HI_UNF_TUNER_TS_SERIAL_PIN_E)Ini_IOFile_GetValue((HI_CHAR*)"u32SatTsSerialPin", DEF_SAT_TS_SER_PIN, pszEntry);
    pSatAttr->enDiSEqCWave = (HI_UNF_TUNER_DISEQCWAVE_MODE_E)Ini_IOFile_GetValue((HI_CHAR*)"u32SatDiseqcWave", DEF_SAT_DISEQC_WAVE, pszEntry);
    pSatAttr->enLNBCtrlDev = (HI_UNF_LNBCTRL_DEV_TYPE_E)Ini_IOFile_GetValue((HI_CHAR*)"u32SatLnbCtrlDev", DEF_SAT_LNB_CTRL_DEV, pszEntry);
    pSatAttr->u16LNBDevAddress = (HI_U16)Ini_IOFile_GetValue((HI_CHAR*)"u32SatLnbCtrlDevI2cAddr", DEF_SAT_LNB_CTRL_DEV_I2C_ADDR, pszEntry);

    return SUCCESS;
}

static VOID config_read_tuner_attr(FRONTEND_SYSCFG_INFO_S* pstFeCfgInfo, HI_CHAR* pszEntry)
{
    HI_UNF_TUNER_ATTR_S* pTunerAttr = NULL;
    U32 u32SdaGrp = 0, u32SdaBit = 0, u32ClkGrp = 0, u32ClkBit = 0;
    U32 u32I2cChn = 0, u32RstGpioNum = 0;
    U32 u32I2cData = 0;
    U32 u32I2cClock = 0;

    pTunerAttr = &pstFeCfgInfo->stTunerAttr;
    pstFeCfgInfo->u32TunerDeviceStatus = 0;
    pstFeCfgInfo->u32TunerSigType = Ini_IOFile_GetValue((HI_CHAR*)"u32SigType", DEF_SIG_TYPE, pszEntry);
    pTunerAttr->enSigType = (HI_UNF_TUNER_SIG_TYPE_E)conver_signal_to_unf(pstFeCfgInfo->u32TunerSigType);

    if (HI_UNF_TUNER_SIG_TYPE_DVBT_ALL == pTunerAttr->enSigType)
    {
        pTunerAttr->enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T;
    }

    pTunerAttr->enTunerDevType = (HI_UNF_TUNER_DEV_TYPE_E)Ini_IOFile_GetValue((HI_CHAR*)"u32TunerType", DEF_TUNER_TYPE, pszEntry);
    pTunerAttr->enDemodDevType = (HI_UNF_DEMOD_DEV_TYPE_E)Ini_IOFile_GetValue((HI_CHAR*)"u32DemodType", DEF_DEMOD_TYPE, pszEntry);
    pTunerAttr->enOutputMode = (HI_UNF_TUNER_OUPUT_MODE_E)Ini_IOFile_GetValue((HI_CHAR*)"u32TunerOutPutMode", DEF_TUNER_OUT_PUT_MOD, pszEntry);
    pTunerAttr->u32TunerAddr = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32TunerI2cAddr", DEF_TUNER_I2C_ADDR, pszEntry);
    pTunerAttr->u32DemodAddr = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32DemodI2cAddr", DEF_DEMOD_I2C_ADDR, pszEntry);

    pstFeCfgInfo->u32I2cType = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32I2cType", DEF_I2C_TYPE, pszEntry);

    if (USE_GPIO_I2C != pstFeCfgInfo->u32I2cType)
    {
        u32I2cChn = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32I2cChNum", DEF_I2C_CHN_NUM, pszEntry);
    }
    else
    {
        u32ClkGrp = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32GpioI2cClkGroup", DEF_GPIO_I2C_CLK_GRP, pszEntry);
        u32ClkBit = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32GpioI2cClkBit", DEF_GPIO_I2C_CLK_BIT, pszEntry);
        u32SdaGrp = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32GpioI2cSdaGroup", DEF_GPIO_I2C_SDA_GRP, pszEntry);
        u32SdaBit = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32GpioI2cSdaBit", DEF_GPIO_I2C_SDA_BIT, pszEntry);

        u32I2cClock = (u32ClkGrp << 3) + u32ClkBit;
        u32I2cData = (u32SdaGrp << 3) + u32SdaBit;

        if (HI_SUCCESS != HI_UNF_I2C_CreateGpioI2c(&u32I2cChn, u32I2cClock, u32I2cData))
        {
            HAL_ERROR("CreateGpioI2c falied \n");
        }
    }

    pTunerAttr->enI2cChannel = (HI_U8)u32I2cChn;

    pstFeCfgInfo->u32TunerRstType = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32RstType", DEF_RST_TYPE, pszEntry);

    if (NEED_RESET == pstFeCfgInfo->u32TunerRstType)
    {
        u32RstGpioNum = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32RstUseGpio", DEF_RST_USE_GPIO, pszEntry);
        pTunerAttr->u32ResetGpioNo = u32RstGpioNum;
    }

    pstFeCfgInfo->u32DemodTsOutMode = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32DemodTsOutMode", DEF_DEMOD_TS_OUT_MOD, pszEntry);

    //ts out line redefine by user
    if (TS_OUT_REDEINE == pstFeCfgInfo->u32DemodTsOutMode)
    {
        pstFeCfgInfo->u32TsDataLineOutSel = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32TsDataLineOutSel", DEF_TS_DATA_LINE_OUT_SEL, pszEntry);
        pstFeCfgInfo->u32TsCtrlLineOutSel = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32TsCtrlLineOutSel", DEF_TS_CTRL_LINE_OUT_SEL, pszEntry);
    }

    /*get demux port cfg info*/
    pstFeCfgInfo->u32TsPortId = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32TsPortId", DEF_TS_PORT_ID, pszEntry);
    pstFeCfgInfo->u32DemuxPortType = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32DemuxPortType", DEF_DEMUX_PORT_TYPE, pszEntry);
    pstFeCfgInfo->u32SerBitSel = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32SerBitSel", DEF_SER_BIT_SEL, pszEntry);
}

// new fun to init by config file, for all paltform
static S32 config_read_file(HI_VOID)
{
    U32 i, j;
    CHAR acEntry[FRONTEND_INI_KEY_MAX_LENGTH];
    CHAR* pszEntry = acEntry;
    U32 u32TunerDeviceID = 0;
    BOOL bMallocError = FALSE;
    FRONTEND_SYSCFG_INFO_S* pstFeCfgInfo;
    HI_UNF_TUNER_ATTR_S* pTunerAttr;
    U32 au32FeDev[FRONTEND_MAX_COUNT];
    s_u32FeNum = 0;

    s_u32FeCfgNum = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32TunerNum", DEF_TUNER_NUM, (HI_CHAR*)"tunernum");

    if (0 == s_u32FeCfgNum)
    {
        return FAILURE;
    }

    if (s_u32FeCfgNum > FRONTEND_MAX_COUNT) // just support tuner num FRONTEND_MAX_COUNT
    {
        s_u32FeCfgNum = FRONTEND_MAX_COUNT;
    }

    s_pstFeCfgInfo = (FRONTEND_SYSCFG_INFO_S*)malloc(sizeof(FRONTEND_SYSCFG_INFO_S) * s_u32FeCfgNum);

    if (NULL == s_pstFeCfgInfo)
    {
        HAL_ERROR("malloc FRONTEND_SYSCFG_INFO_S error");
        bMallocError = TRUE;
        return ERROR_NO_MEMORY;
    }

    memset(au32FeDev, 0, sizeof(au32FeDev));
    memset(s_pstFeCfgInfo, 0, sizeof(FRONTEND_SYSCFG_INFO_S)*s_u32FeCfgNum);
    pstFeCfgInfo = s_pstFeCfgInfo;

    for (i = 0; i < s_u32FeCfgNum; i++ , pstFeCfgInfo++)
    {
        pTunerAttr = &pstFeCfgInfo->stTunerAttr;
        snprintf(pszEntry, FRONTEND_INI_KEY_MAX_LENGTH, "tuner%dinfo", i);
        pstFeCfgInfo->u32TunerDeviceID = (U32)Ini_IOFile_GetValue((CHAR*)"u32TunerDeviceID", DEF_TUNRE_DEVICEID, pszEntry);
        u32TunerDeviceID = pstFeCfgInfo->u32TunerDeviceID;

        if (u32TunerDeviceID >= FRONTEND_MAX_COUNT)
        {
            continue;
        }

        au32FeDev[u32TunerDeviceID]++;

        config_read_tuner_attr(pstFeCfgInfo, pszEntry);

        if (HI_UNF_TUNER_SIG_TYPE_SAT == pTunerAttr->enSigType)
        {
            pstFeCfgInfo->u32SatMotorTimeout = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32SatMotorTimeout", SAT_MOTOR_CHECK_DEFAULT_TIMEOUT, pszEntry);
            pstFeCfgInfo->pstSatAttr = (HI_UNF_TUNER_SAT_ATTR_S*)malloc(sizeof(HI_UNF_TUNER_SAT_ATTR_S));

            if (SUCCESS != config_read_sat_attr(pstFeCfgInfo->pstSatAttr, pszEntry))
            {
                bMallocError = TRUE;
                HAL_ERROR("malloc HI_UNF_TUNER_SAT_ATTR_S error");
                break;
            }
        }

        if (HI_UNF_TUNER_SIG_TYPE_DVB_T == pTunerAttr->enSigType || HI_UNF_TUNER_SIG_TYPE_DVB_T2 == pTunerAttr->enSigType)
        {
            pstFeCfgInfo->stTRelockParam.u32TSignalTimeout = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32TT2AutoLockTerTimeout", DEF_TER_RELOCK_TTIMEOUT, pszEntry);
            pstFeCfgInfo->stTRelockParam.u32T2SignalTimeout = (HI_U32)Ini_IOFile_GetValue((HI_CHAR*)"u32TT2AutoLockTer2Timeout", DEF_TER_RELOCK_T2TIMEOUT, pszEntry);

            pstFeCfgInfo->pstTunerTerAttr = (HI_UNF_TUNER_TER_ATTR_S*)malloc(sizeof(HI_UNF_TUNER_SAT_ATTR_S));

            if (SUCCESS != config_read_ter_attr(pstFeCfgInfo->pstTunerTerAttr, pszEntry))
            {
                bMallocError = TRUE;
                HAL_ERROR("malloc HI_UNF_TUNER_TER_ATTR_S error");
                break;
            }
        }

        pstFeCfgInfo->u32TunerInClk = (HI_UNF_DMX_PORT_E)Ini_IOFile_GetValue((CHAR*)"u32TunerInClk", DEF_TER_DMX_PORT_INCLK, pszEntry);
        pstFeCfgInfo->enSerialPortShareClk = (HI_UNF_DMX_PORT_E)Ini_IOFile_GetValue((CHAR*)"u32PortShareClk", DEF_TER_DMX_PORT_SHARECLK, pszEntry);

    }

    if (bMallocError)
    {
        config_free();
        return ERROR_NO_MEMORY;
    }

    U32 u32FeDevID[FRONTEND_MAX_COUNT];
    memset(u32FeDevID, 0 , sizeof(u32FeDevID));

    for (i = 0; i < FRONTEND_MAX_COUNT; i++)
    {
        if (au32FeDev[i] > 0)
        {
            u32FeDevID[s_u32FeNum] = i;
            s_u32FeNum++;
        }
    }

    s_pstFeDevInfo = (FRONTEND_DEV_INFO_S*)malloc(sizeof(FRONTEND_DEV_INFO_S) * s_u32FeNum);

    if (NULL == s_pstFeDevInfo)
    {
        config_free();
        HAL_ERROR("malloc FRONTEND_DEV_INFO_S error");
        return ERROR_NO_MEMORY;
    }

    memset(s_pstFeDevInfo, 0, sizeof(FRONTEND_DEV_INFO_S)*s_u32FeNum);

    for (i = 0; i < s_u32FeNum; i++)
    {
        s_pstFeDevInfo[i].u32TunerId = u32FeDevID[i];

        for (j = 0; j < s_u32FeCfgNum; j++)
        {
            if (s_pstFeDevInfo[i].u32TunerId == s_pstFeCfgInfo[j].u32TunerDeviceID)
            {
                s_pstFeDevInfo[i].stTRelockParam.bTT2AutoLock = FALSE;
                s_pstFeDevInfo[i].stTRelockParam.u32TSignalTimeout = s_pstFeCfgInfo[j].stTRelockParam.u32TSignalTimeout;
                s_pstFeDevInfo[i].stTRelockParam.u32T2SignalTimeout = s_pstFeCfgInfo[j].stTRelockParam.u32T2SignalTimeout;
                s_pstFeDevInfo[i].enDemuxPort = (HI_UNF_DMX_PORT_E)s_pstFeCfgInfo[j].u32TsPortId;
                HAL_DEBUG("index %d  hal sig %d unf sig %d \n", j, s_pstFeCfgInfo[j].u32TunerSigType, conver_signal_to_unf(s_pstFeCfgInfo[j].u32TunerSigType));
                s_pstFeDevInfo[i].u32Capability |= s_pstFeCfgInfo[j].u32TunerSigType;
                s_pstFeDevInfo[i].u32MotorTimeout = s_pstFeCfgInfo[j].u32SatMotorTimeout;
            }
        }
    }

    // 默认打开tuner 0；
    s_pstFeCfgInfo->u32TunerDeviceStatus = 1;

    return HI_SUCCESS;
}

static S32 config_find_running_by_tuner_id(U32 u32TunerID, U32* pu32Index)
{
    U32 i = 0;

    for (i = 0; i < s_u32FeCfgNum; i++)
    {
        if ((1 == s_pstFeCfgInfo[i].u32TunerDeviceStatus) && (s_pstFeCfgInfo[i].u32TunerDeviceID == u32TunerID))
        {
            break;
        }
    }

    if (i == s_u32FeCfgNum)
    {
        return FAILURE;
    }

    *pu32Index = i;
    return SUCCESS;
}

static S32 config_find_by_signal(U32 u32TunerID, U32 u32HalSigType, U32* pu32Index)
{
    U32 i = 0;

    for (i = 0; i < s_u32FeCfgNum; i++)
    {
        if (s_pstFeCfgInfo[i].u32TunerDeviceID == u32TunerID)
        {
            if (FRONTEND_FE_TERRESTRIAL_ALL == u32HalSigType)
            {
                if (FRONTEND_FE_TERRESTRIAL_ALL != s_pstFeCfgInfo[i].u32TunerSigType)
                {
                    continue;
                }

                break;
            }
            else
            {
                if (s_pstFeCfgInfo[i].u32TunerSigType & u32HalSigType)
                {
                    break;
                }
            }
        }
    }

    if (i == s_u32FeCfgNum)
    {
        return FAILURE;
    }

    *pu32Index = i;
    return SUCCESS;

}

static S32 fe_port_reuse()
{
    U32 i = 0;
    U32      u32PinMuxNum = 0;
    U32      u32PinMuxAddress = 0;
    U32      u32PinMuxValue = 0;
    CHAR     aszPinMuxAddr[FRONTEND_INI_KEY_MAX_LENGTH];
    CHAR     aszPinMuxValue[FRONTEND_INI_KEY_MAX_LENGTH];

    u32PinMuxNum = (U32)Ini_IOFile_GetValue((CHAR*)"u32PinMuxNum", 0, (CHAR*)"boardpinmux");

    if (u32PinMuxNum > FRONTEND_PIN_REUSE_MAX_COUNT)
    {
        HAL_ERROR("Only support reuse %d port\n", FRONTEND_PIN_REUSE_MAX_COUNT);
        u32PinMuxNum = FRONTEND_PIN_REUSE_MAX_COUNT;
    }

    for (i = 0; i < u32PinMuxNum; i++)
    {
        HI_U8* pu8MUXAddr = NULL;

        memset(aszPinMuxAddr, 0, FRONTEND_INI_KEY_MAX_LENGTH);
        memset(aszPinMuxValue, 0, FRONTEND_INI_KEY_MAX_LENGTH);
        snprintf(aszPinMuxAddr, FRONTEND_INI_KEY_MAX_LENGTH, "u32PinMuxAddr%d", i);
        snprintf(aszPinMuxValue, FRONTEND_INI_KEY_MAX_LENGTH, "u32PinMuxValue%d", i);

        u32PinMuxAddress = (U32)Ini_IOFile_GetValue((CHAR*)aszPinMuxAddr, 0, (CHAR*)"boardpinmux");
        u32PinMuxValue = (U32)Ini_IOFile_GetValue((CHAR*)aszPinMuxValue, 0, (CHAR*)"boardpinmux");

        if (0 != u32PinMuxAddress)
        {
            pu8MUXAddr = (U8*)HI_MEM_Map(u32PinMuxAddress, 0x1);
        }

        if (NULL != pu8MUXAddr)
        {
            *pu8MUXAddr = (HI_U8)u32PinMuxValue;
        }
    }

    return SUCCESS;
}

// TODO: if atv use this init, do not need this fun
static BOOL fe_init_check(FRONTEND_SYSCFG_INFO_S* pstFeCfgInfo __unused)
{
    BOOL bChanged = FALSE;
#if (HAL_TV_PRODUCT_CODE == UNF_PRODUCT_CODE)
    S32 s32Ret = SUCCESS;
    U32 u32TunerID = 0;
    HI_UNF_TUNER_ATTR_S  stStatus;

    u32TunerID = pstFeCfgInfo->u32TunerDeviceID;
    memset(&stStatus, 0, sizeof(stStatus));
    s32Ret = HI_UNF_TUNER_GetAttr(u32TunerID, &stStatus);

    if (SUCCESS != s32Ret || stStatus.enSigType != pstFeCfgInfo->stTunerAttr.enSigType)
    {
        HAL_ERROR("++++sinal dismatch 0x%x %d %d %d++\n", s32Ret, u32TunerID,
            stStatus.enSigType, pstFeCfgInfo->stTunerAttr.enSigType);
        bChanged = TRUE;
    }
    else
    {
        HAL_ERROR("++++sinal match 0x%x %d %d %d++\n", s32Ret, u32TunerID,
            stStatus.enSigType, pstFeCfgInfo->stTunerAttr.enSigType);
    }
#endif

    return bChanged;
}

static S32 fe_init_ts(FRONTEND_DEV_INFO_S* pstDevInfo, FRONTEND_SYSCFG_INFO_S* pstFeCfgInfo)
{
    S32 s32Ret = HI_SUCCESS;
    U32 i = 0;
    U32 u32TunerID = pstFeCfgInfo->u32TunerDeviceID;
    HI_UNF_TUNER_TSOUT_SET_S stTSOut;
    HI_UNF_DMX_PORT_ATTR_S stDmxAttr;

    memset(&stDmxAttr, 0x0, sizeof(HI_UNF_DMX_PORT_ATTR_S));

    //config ts out
    if (TS_OUT_REDEINE == pstFeCfgInfo->u32DemodTsOutMode)
    {
        memset(&stTSOut, 0, sizeof(stTSOut));

        for (i = 0; i < TS_OUT_DATA_NUM; i++)
        {
            stTSOut.enTSOutput[i] = (HI_UNF_TUNER_OUTPUT_TS_E)((pstFeCfgInfo->u32TsDataLineOutSel & (0xf << (i * 4))) >> (i * 4));
        }

        stTSOut.enTSOutput[8] = (HI_UNF_TUNER_OUTPUT_TS_E)(pstFeCfgInfo->u32TsCtrlLineOutSel & 0xf);
        stTSOut.enTSOutput[9] = (HI_UNF_TUNER_OUTPUT_TS_E)((pstFeCfgInfo->u32TsCtrlLineOutSel & 0xf0) >> 4);
        stTSOut.enTSOutput[10] = (HI_UNF_TUNER_OUTPUT_TS_E)((pstFeCfgInfo->u32TsCtrlLineOutSel & 0xf00) >> 8);

        s32Ret = HI_UNF_TUNER_SetTSOUT(u32TunerID, &stTSOut);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("call HI_UNF_TUNER_SetTSOUT Tuner %d failed,s32Ret = 0x%x.\n", u32TunerID, s32Ret);
            return s32Ret;
        }
    }

    //config ts in
    if (HI_SUCCESS != HI_UNF_DMX_Init())
    {
        s32Ret = FAILURE;
        HAL_ERROR("ERROR: dmx init fail.\n");
    }

    s32Ret = HI_UNF_DMX_GetTSPortAttr((HI_UNF_DMX_PORT_E)(pstFeCfgInfo->u32TsPortId), &stDmxAttr);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("call HI_UNF_DMX_GetTSPortAttr port %d failed,s32Ret = 0x%x.\n", pstFeCfgInfo->u32TsPortId, s32Ret);
    }

    stDmxAttr.enPortType = (HI_UNF_DMX_PORT_TYPE_E)(pstFeCfgInfo->u32DemuxPortType);
    stDmxAttr.u32SerialBitSelector = pstFeCfgInfo->u32SerBitSel;
    stDmxAttr.u32TunerInClk = pstFeCfgInfo->u32TunerInClk;

    if (DEF_TER_DMX_PORT_SHARECLK != pstFeCfgInfo->enSerialPortShareClk)
    {
        stDmxAttr.enSerialPortShareClk = pstFeCfgInfo->enSerialPortShareClk;
    }
    s32Ret = HI_UNF_DMX_SetTSPortAttr((HI_UNF_DMX_PORT_E)(pstFeCfgInfo->u32TsPortId), &stDmxAttr);

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("call HI_UNF_DMX_SetTSPortAttr port %d failed,s32Ret = 0x%x.\n", pstFeCfgInfo->u32TsPortId, s32Ret);
    }
    pstDevInfo->enDemuxPort = (HI_UNF_DMX_PORT_E)(pstFeCfgInfo->u32TsPortId);

    return s32Ret;
}

S32 fe_init(FRONTEND_DEV_INFO_S* pstDevInfo, FRONTEND_SYSCFG_INFO_S* pstFeCfgInfo , FRONTEND_INIT_TYPE_E enInitType __unused)
{
    S32 s32Ret = HI_SUCCESS;
    U32 u32TunerID = 0;

    if (pstFeCfgInfo->u32TunerDeviceStatus)
    {
        s32Ret = HI_UNF_TUNER_Open(pstFeCfgInfo->u32TunerDeviceID);
    }

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_TUNER_Open Tuner %d failed,s32Ret = 0x%x \n ", u32TunerID, s32Ret);
        return HI_FAILURE;
    }

    u32TunerID = pstFeCfgInfo->u32TunerDeviceID;

    s32Ret = HI_UNF_TUNER_SetAttr(u32TunerID, &(pstFeCfgInfo->stTunerAttr));

    if (HI_SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_TUNER_SetAttr Tuner %d failed,s32Ret = 0x%x \n ", u32TunerID, s32Ret);
        return HI_FAILURE;
    }

    if (HI_UNF_TUNER_SIG_TYPE_DVB_T == pstFeCfgInfo->stTunerAttr.enSigType
        || HI_UNF_TUNER_SIG_TYPE_DVB_T2 == pstFeCfgInfo->stTunerAttr.enSigType)
    {
        s32Ret = HI_SUCCESS;
#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)
        s32Ret = HI_UNF_TUNER_SetTerAttr(u32TunerID, pstFeCfgInfo->pstTunerTerAttr);
#endif
        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_UNF_TUNER_SetTerAttr Tuner %d failed,s32Ret=0x%x\n ", u32TunerID, s32Ret);
            return HI_FAILURE;
        }
    }

    if (HI_UNF_TUNER_SIG_TYPE_SAT == pstFeCfgInfo->stTunerAttr.enSigType)
    {

        s32Ret = HI_UNF_TUNER_SetSatAttr(u32TunerID, pstFeCfgInfo->pstSatAttr);

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("HI_UNF_TUNER_SetSatAttr Tuner %d failed,s32Ret=0x%x\n", u32TunerID, s32Ret);
            return HI_FAILURE;
        }
    }

    pstDevInfo->enSignalType = (FRONTEND_FE_TYPE_E)pstFeCfgInfo->u32TunerSigType;

    s32Ret = fe_init_ts(pstDevInfo, pstFeCfgInfo);

    return s32Ret;
}

static FRONTEND_DEV_INFO_S* fe_open_device(const FRONTEND_OPEN_PARAMS_S* pstOpenParam)
{
    U32 u32Index = pstOpenParam->u32FrontendIndex;
    U32 u32CurCfgIndex = 0;
    U32 u32DstCfgIndex = 0;
    U32 u32SigType = 0;
    BOOL bChanged = FALSE;
    S32 s32Ret = FAILURE;

    if ((s_pstFeDevInfo[u32Index].u32Capability & pstOpenParam->enFeType))
    {
        if (0 == s_pstFeDevInfo[u32Index].enSignalType)
        {
            // find fecfg index
            for (u32CurCfgIndex = 0; u32CurCfgIndex < s_u32FeCfgNum; u32CurCfgIndex++)
            {
                HAL_DEBUG("s_pstFeCfgInfo[%d].u32TunerDeviceStatus %d \n", u32CurCfgIndex, s_pstFeCfgInfo[u32CurCfgIndex].u32TunerDeviceStatus);
                if (s_pstFeCfgInfo[u32CurCfgIndex].u32TunerDeviceID == s_pstFeDevInfo[u32Index].u32TunerId)
                {
                    break;
                }
            }

            if (u32CurCfgIndex == s_u32FeCfgNum)
            {
                return NULL;
            }

            s_pstFeCfgInfo[u32CurCfgIndex].u32TunerDeviceStatus = 1;
            s32Ret = fe_init(&s_pstFeDevInfo[u32Index], &s_pstFeCfgInfo[u32CurCfgIndex], FRONTEND_INIT_FIRST_TIME);
        }
        else if (0 == (s_pstFeDevInfo[u32Index].enSignalType & pstOpenParam->enFeType))
        {
            //check signal,
            s32Ret = config_find_running_by_tuner_id(s_pstFeDevInfo[u32Index].u32TunerId, &u32CurCfgIndex);

            if (SUCCESS != s32Ret)
            {
                return NULL;
            }

            u32SigType = pstOpenParam->enFeType;
            s32Ret = config_find_by_signal(s_pstFeDevInfo[u32Index].u32TunerId, u32SigType, &u32DstCfgIndex);

            if (SUCCESS != s32Ret)
            {
                return NULL;
            }

            //reinit
            s_pstFeCfgInfo[u32CurCfgIndex].u32TunerDeviceStatus = 0;
            s_pstFeCfgInfo[u32DstCfgIndex].u32TunerDeviceStatus = 1;

            s32Ret = fe_init(&s_pstFeDevInfo[u32Index], &s_pstFeCfgInfo[u32DstCfgIndex], FRONTEND_INIT_SIGNAL_CHANGE);
        }
        else
        {
            s32Ret = SUCCESS; // alread init, so set ret success first. then check.
            bChanged = fe_init_check(&s_pstFeCfgInfo[u32CurCfgIndex]);

            if (bChanged)
            {
                s32Ret = fe_init(&s_pstFeDevInfo[u32Index], &s_pstFeCfgInfo[u32CurCfgIndex], FRONTEND_INIT_REINIT);
            }
        }

    }

    if (SUCCESS != s32Ret)
    {
        return NULL;
    }

    return &s_pstFeDevInfo[u32Index];
}

static void fe_event_callbak(FRONTEND_DEV_INFO_S* pstDevInfo, FRONTEND_FE_STATUS_E enOldStatus, FRONTEND_FE_STATUS_E enNewStatus)
{
    S32 i;

    for (i = 0 ; i < FRONTEND_REG_CALLBACK_TYPE_BUTT; i++)
    {
        if (pstDevInfo->astCallback[i].pCallBack && !pstDevInfo->astCallback[i].bDisable)
        {
            switch (pstDevInfo->astCallback[i].enCallbackType)
            {
                case FRONTEND_REG_LOCKSTATUS_CALLBACK:

                    ((FRONTEND_NOTIFY_STATUS_PFN)(pstDevInfo->astCallback[i].pCallBack))(pstDevInfo->hDevice, enOldStatus, enNewStatus, pstDevInfo->astCallback[i].u32UserData);/*lint !e611*/
                    break;

                case FRONTEND_REG_GETSTATUS_CALLBACK:
                case FRONTEND_REG_BLINDSCAN_CALLBACK:
                case FRONTEND_REG_LNB_PWR_STATUS_CALLBACK:
                    break;

                default:
                    break;
            }
        }
    }

    return;
}

static void fe_event_blindscan_set_diseqc(HI_U32 u32TunerId, HI_UNF_TUNER_FE_POLARIZATION_E enPolar, HI_UNF_TUNER_FE_LNB_22K_E enLNB22K)
{
    FRONTEND_DEV_INFO_S* pstDevInfo = NULL;
    FRONTEND_POLARIZATION_E enHalPolar;
    FRONTEND_LNB_22K_E enHalLnb22K = FRONTEND_LNB_22K_OFF;

    if (s_pstFeDevInfo[u32TunerId].bOpen)
    {
        pstDevInfo = &s_pstFeDevInfo[u32TunerId];
    }

    if (pstDevInfo == NULL)
    {
        return;
    }

    enHalPolar = conver_polar_to_hal(enPolar);

    if (enLNB22K == HI_UNF_TUNER_FE_LNB_22K_ON)
    {
        enHalLnb22K = FRONTEND_LNB_22K_ON;
    }

    if (pstDevInfo->stBlindScanParam.pfnDISEQCSet)
    {
        pstDevInfo->stBlindScanParam.pfnDISEQCSet(pstDevInfo->hDevice, enHalPolar, enHalLnb22K);
    }

    return;
}

static void fe_event_blindscan_notify(HI_U32 u32TunerId, HI_UNF_TUNER_BLINDSCAN_EVT_E enEVT, HI_UNF_TUNER_BLINDSCAN_NOTIFY_U* punNotify)
{
    FRONTEND_DEV_INFO_S* pstDevInfo = NULL;
    FRONTEND_FE_STATUS_E enStatus = FRONTEND_STATUS_IDLE;
    U16 u16ProgressPercent = 0;
    FRONTEND_SAT_BLINDSCAN_TP_INFO_S  stBlindScanResult;             /**<Scanning result*//**<CNcomment:盲扫结果*/
    FRONTEND_SAT_BLINDSCAN_NOTIFY_U unBlindScanNotify;
    FRONTEND_SAT_BLINDSCAN_EVT_E enBlindScanEvent = FRONTEND_SAT_BLINDSCAN_EVT_BUTT;
    unBlindScanNotify.penStatus = &enStatus;

    if (s_pstFeDevInfo[u32TunerId].bOpen)
    {
        pstDevInfo = &s_pstFeDevInfo[u32TunerId];
    }

    if (pstDevInfo == NULL)
    {
        return;
    }

    if (HI_UNF_TUNER_BLINDSCAN_EVT_STATUS == enEVT)
    {
        enBlindScanEvent = FRONTEND_SAT_BLINDSCAN_EVT_STATUS;

        switch (*(punNotify->penStatus))
        {
            case HI_UNF_TUNER_BLINDSCAN_STATUS_IDLE:
                enStatus = FRONTEND_STATUS_IDLE;
                break;

            case HI_UNF_TUNER_BLINDSCAN_STATUS_SCANNING:
                enStatus = FRONTEND_STATUS_BLINDSCANING;
                break;

            case HI_UNF_TUNER_BLINDSCAN_STATUS_FINISH:
                enStatus = FRONTEND_STATUS_BLINDSCAN_COMPLETE;
                break;

            case HI_UNF_TUNER_BLINDSCAN_STATUS_QUIT:
                enStatus = FRONTEND_STATUS_BLINDSCAN_QUIT;
                break;

            case HI_UNF_TUNER_BLINDSCAN_STATUS_FAIL:
                enStatus = FRONTEND_STATUS_BLINDSCAN_FAIL;
                break;

            case HI_UNF_TUNER_BLINDSCAN_STATUS_BUTT:
            default:
                enStatus = FRONTEND_STATUS_BUTT;
                break;
        }

        unBlindScanNotify.penStatus = &enStatus;
    }
    else if (HI_UNF_TUNER_BLINDSCAN_EVT_PROGRESS == enEVT)
    {
        enBlindScanEvent = FRONTEND_SAT_BLINDSCAN_EVT_PROGRESS;
        u16ProgressPercent = *(punNotify->pu16ProgressPercent);
        unBlindScanNotify.pu16ProgressPercent = &u16ProgressPercent;
    }
    else if (HI_UNF_TUNER_BLINDSCAN_EVT_NEWRESULT == enEVT)
    {
        enBlindScanEvent = FRONTEND_SAT_BLINDSCAN_EVT_NEWRESULT;
        memset(&stBlindScanResult, 0, sizeof(stBlindScanResult));
        unBlindScanNotify.pstResult = &stBlindScanResult;
        stBlindScanResult.u32Freq = punNotify->pstResult->u32Freq;
        stBlindScanResult.u32Sym = punNotify->pstResult->u32SymbolRate;
        stBlindScanResult.enPolar = conver_polar_to_hal(punNotify->pstResult->enPolar);
    }

    if (pstDevInfo->stBlindScanParam.pfnEVTNotify)
    {
        pstDevInfo->stBlindScanParam.pfnEVTNotify(pstDevInfo->hDevice, enBlindScanEvent, &unBlindScanNotify);
    }

    return;
}

#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)
static void fe_event_unicable_notify(HI_U32 u32TunerId, HI_UNF_TUNER_UNICABLE_SCAN_USER_BAND_EVT_E enEVT, HI_UNF_TUNER_UNICABLE_SCAN_USER_BAND_NOTIFY_S* pNotify)
{
    S32 i;
    FRONTEND_DEV_INFO_S* pstDevInfo = NULL;

    if (s_pstFeDevInfo[u32TunerId].bOpen)
    {
        pstDevInfo = &s_pstFeDevInfo[u32TunerId];
    }

    if (pstDevInfo == NULL)
    {
        return;
    }

    for (i = 0 ; i < FRONTEND_REG_CALLBACK_TYPE_BUTT; i++)
    {
        if (pstDevInfo->astCallback[i].pCallBack && !pstDevInfo->astCallback[i].bDisable)
        {
            switch (pstDevInfo->astCallback[i].enCallbackType)
            {
                case FRONTEND_REG_UNICABLE_SCAN_CALLBACK:
                    ((FRONTEND_UNICABLE_SCAN_PFN)(pstDevInfo->astCallback[i].pCallBack))(pstDevInfo->hDevice, (FRONTEND_UNICABLE_SCAN_EVT_E)enEVT, (FRONTEND_UNICABLE_SCAN_NOTIFYDATA_U*) pNotify);/*lint !e611*/
                    break;

                default:
                    break;
            }
        }
    }

}
#endif

static S32 fe_check_scan_param(FRONTEND_DEV_INFO_S const* pstDevInfo , FRONTEND_SCAN_INFO_S const* pstScanParam)
{
    HAL_DEBUG("=========signal %d ==========", pstScanParam->enFrontendType);

    switch (pstScanParam->enFrontendType)
    {
        case FRONTEND_FE_SATELLITE1:
        case FRONTEND_FE_SATELLITE2:
            HAL_DEBUG("sig sat: freq: %d u32SymbolRate: %d enPolar: %d ",
                      pstScanParam->unScanInfo.stSatInfo.u32Freq,
                      pstScanParam->unScanInfo.stSatInfo.u32Sym,
                      pstScanParam->unScanInfo.stSatInfo.enPolar);
            FRONTEND_CHECK_RETURN_ERR((FRONTEND_FE_SATELLITE1 != pstDevInfo->enSignalType) && (FRONTEND_FE_SATELLITE2 != pstDevInfo->enSignalType), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR((!((SAT_C_MIN_KHZ <= pstScanParam->unScanInfo.stSatInfo.u32Freq) && (SAT_C_MAX_KHZ >= pstScanParam->unScanInfo.stSatInfo.u32Freq))
                                       && !((SAT_KU_MIN_KHZ <= pstScanParam->unScanInfo.stSatInfo.u32Freq) && (SAT_KU_MAX_KHZ >= pstScanParam->unScanInfo.stSatInfo.u32Freq))), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR((SAT_SYMBOLRATE_MAX < pstScanParam->unScanInfo.stSatInfo.u32Sym), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR((FRONTEND_PLR_BUTT <= pstScanParam->unScanInfo.stSatInfo.enPolar), ERROR_INVALID_PARAM);
            break;

        case FRONTEND_FE_CABLE1:
        case FRONTEND_FE_CABLE2:
            HAL_DEBUG("sig cab: freq: %d bandWidth: %d modtype: %d ",
                      pstScanParam->unScanInfo.stCabInfo.u32Freq,
                      pstScanParam->unScanInfo.stCabInfo.u32Sym,
                      pstScanParam->unScanInfo.stCabInfo.enModulation);
            FRONTEND_CHECK_RETURN_ERR(((FRONTEND_FE_CABLE1 != pstDevInfo->enSignalType) && (FRONTEND_FE_CABLE2 != pstDevInfo->enSignalType)), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR(((pstScanParam->unScanInfo.stCabInfo.u32Freq < CAB_RF_MIN) || (pstScanParam->unScanInfo.stCabInfo.u32Freq > CAB_RF_MAX)), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR(((pstScanParam->unScanInfo.stCabInfo.u32Sym < CAB_SYMBOLRATE_MIN) || (pstScanParam->unScanInfo.stCabInfo.u32Sym > CAB_SYMBOLRATE_MAX)), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR((!((pstScanParam->unScanInfo.stCabInfo.enModulation == FRONTEND_MOD_QAM16)
                                         || (pstScanParam->unScanInfo.stCabInfo.enModulation == FRONTEND_MOD_QAM32)
                                         || (pstScanParam->unScanInfo.stCabInfo.enModulation == FRONTEND_MOD_QAM64)
                                         || (pstScanParam->unScanInfo.stCabInfo.enModulation == FRONTEND_MOD_QAM128)
                                         || (pstScanParam->unScanInfo.stCabInfo.enModulation == FRONTEND_MOD_QAM256))), ERROR_INVALID_PARAM);
            break;

        case FRONTEND_FE_TERRESTRIAL1:
        case FRONTEND_FE_TERRESTRIAL2:
            HAL_DEBUG("sig Ter : signal %d  freq: %d  bandWidth: %d  modtype: %d ",
                      pstScanParam->enFrontendType,
                      pstScanParam->unScanInfo.stTerInfo.u32Freq,
                      pstScanParam->unScanInfo.stTerInfo.enBandWidth,
                      pstScanParam->unScanInfo.stTerInfo.enModulation);
            if (FRONTEND_FE_TERRESTRIAL1 == pstDevInfo->enSignalType)
            {
                FRONTEND_CHECK_RETURN_ERR((FRONTEND_FE_TERRESTRIAL1 != pstScanParam->enFrontendType), ERROR_INVALID_PARAM);
            }
            else if (FRONTEND_FE_TERRESTRIAL2 == pstDevInfo->enSignalType)
            {
                FRONTEND_CHECK_RETURN_ERR((FRONTEND_FE_TERRESTRIAL2 != pstScanParam->enFrontendType), ERROR_INVALID_PARAM);
            }
            else
            {
                FRONTEND_CHECK_RETURN_ERR(((FRONTEND_FE_TERRESTRIAL_ALL) != pstDevInfo->enSignalType), ERROR_INVALID_PARAM);
            }

            FRONTEND_CHECK_RETURN_ERR(((pstScanParam->unScanInfo.stTerInfo.u32Freq < TER_RF_MIN) || (pstScanParam->unScanInfo.stTerInfo.u32Freq > TER_RF_MAX)), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR((pstScanParam->unScanInfo.stTerInfo.enBandWidth >= FRONTEND_BANDWIDTH_BUTT), ERROR_INVALID_PARAM);
            break;

        case FRONTEND_FE_DTMB1:
            HAL_DEBUG("sig Dtmb: freq: %d  bandWidth: %d  modtype: %d ",
                      pstScanParam->unScanInfo.stDtmbInfo.u32Freq,
                      pstScanParam->unScanInfo.stDtmbInfo.enBandWidth ,
                      pstScanParam->unScanInfo.stDtmbInfo.enModulation);

            FRONTEND_CHECK_RETURN_ERR((FRONTEND_FE_DTMB1 != pstDevInfo->enSignalType), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR(((pstScanParam->unScanInfo.stDtmbInfo.u32Freq < TER_RF_MIN) || (pstScanParam->unScanInfo.stDtmbInfo.u32Freq > TER_RF_MAX)), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR((pstScanParam->unScanInfo.stDtmbInfo.enBandWidth >= FRONTEND_BANDWIDTH_BUTT), ERROR_INVALID_PARAM);
            break;

        case FRONTEND_FE_ISDBT1:
            HAL_DEBUG("sig ISDB-T: freq: %d  bandWidth: %d",
                      pstScanParam->unScanInfo.stTerInfo.u32Freq,
                      pstScanParam->unScanInfo.stTerInfo.enBandWidth);

            FRONTEND_CHECK_RETURN_ERR((FRONTEND_FE_ISDBT1 != pstDevInfo->enSignalType), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR(((pstScanParam->unScanInfo.stTerInfo.u32Freq < ISDBT_RF_MIN) || (pstScanParam->unScanInfo.stTerInfo.u32Freq > ISDBT_RF_MAX)), ERROR_INVALID_PARAM);
            FRONTEND_CHECK_RETURN_ERR((pstScanParam->unScanInfo.stTerInfo.enBandWidth >= FRONTEND_BANDWIDTH_BUTT), ERROR_INVALID_PARAM);
            break;

        default:

            return ERROR_INVALID_PARAM;
            break;
    }

    return SUCCESS;
}

static BOOL fe_check_cableinfo_same(FRONTEND_SCAN_INFO_S* src, FRONTEND_SCAN_INFO_S const* dst)
{
    if ((src->unScanInfo.stCabInfo.u32Freq == dst->unScanInfo.stCabInfo.u32Freq)
        && (src->unScanInfo.stCabInfo.u32Sym == dst->unScanInfo.stCabInfo.u32Sym)
        && (src->unScanInfo.stCabInfo.enModulation == dst->unScanInfo.stCabInfo.enModulation)
        && (src->unScanInfo.stCabInfo.enSpectrum == dst->unScanInfo.stCabInfo.enSpectrum))
    {
        return TRUE;
    }

    return FALSE;
}

static BOOL fe_check_terinfo_same(FRONTEND_SCAN_INFO_S* src, FRONTEND_SCAN_INFO_S const* dst)
{
    if ((src->unScanInfo.stTerInfo.u32Freq == dst->unScanInfo.stTerInfo.u32Freq)
        && (src->unScanInfo.stTerInfo.enBandWidth == dst->unScanInfo.stTerInfo.enBandWidth)
        && (src->unScanInfo.stTerInfo.enModulation == dst->unScanInfo.stTerInfo.enModulation))
    {
        return TRUE;
    }

    return FALSE;
}

static S32 fe_check_scan_status(FRONTEND_SCAN_INFO_S* src, FRONTEND_SCAN_INFO_S const* dst)
{
    if (src->enFrontendType != dst->enFrontendType)
    {
        return FAILURE;
    }

    switch (src->enFrontendType)
    {
        case FRONTEND_FE_CABLE1:
        case FRONTEND_FE_CABLE2:
            if (fe_check_cableinfo_same(src, dst))
            {
                return SUCCESS;
            }

            break;

        case FRONTEND_FE_SATELLITE1:
        case FRONTEND_FE_SATELLITE2:
            if ((src->unScanInfo.stSatInfo.u32Freq == dst->unScanInfo.stSatInfo.u32Freq)
                && (src->unScanInfo.stSatInfo.u32Sym == dst->unScanInfo.stSatInfo.u32Sym)
                && (src->unScanInfo.stSatInfo.enPolar == dst->unScanInfo.stSatInfo.enPolar))
            {
                return SUCCESS;
            }

            break;

        case FRONTEND_FE_TERRESTRIAL1:
        case FRONTEND_FE_TERRESTRIAL2:
            if (fe_check_terinfo_same(src, dst))
            {
                return SUCCESS;
            }

            break;

        case FRONTEND_FE_DTMB1:
            if ((src->unScanInfo.stDtmbInfo.u32Freq == dst->unScanInfo.stDtmbInfo.u32Freq)
                && (src->unScanInfo.stDtmbInfo.enBandWidth == dst->unScanInfo.stDtmbInfo.enBandWidth)
                && (src->unScanInfo.stDtmbInfo.enModulation == dst->unScanInfo.stDtmbInfo.enModulation))
            {
                return SUCCESS;
            }

            break;

        case FRONTEND_FE_ISDBT1:
            if((src->unScanInfo.stTerInfo.u32Freq == dst->unScanInfo.stTerInfo.u32Freq)
                && (src->unScanInfo.stTerInfo.enBandWidth == dst->unScanInfo.stTerInfo.enBandWidth))
            {
                return SUCCESS;
            }
            break;

        default:
            break;
    }

    return FAILURE;
}


#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)

#ifdef DISEQC_SUPPORT
static S32 fe_sat_switch4port(FRONTEND_DEV_INFO_S* pstDevInfo,
                                    const HI_UNF_TUNER_CONNECT_PARA_S* pstConnParam,
                                    const FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstExAntennaParam,
                                    FRONTEND_ANTENNA_SET_TYPE_E enAntennaSetType)
{
    U32 u32TunerID = pstDevInfo->u32TunerId;

    FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstLastExAntennaInfo = &(pstDevInfo->stCurExAntennaInfo);

    HI_UNF_TUNER_DISEQC_SWITCH4PORT_S st4Port;
    HI_UNF_TUNER_DISEQC_SWITCH4PORT_S* pstLast4Port;
    memset(&st4Port, 0, sizeof(st4Port));
    st4Port.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
    st4Port.enPort  = (HI_UNF_TUNER_DISEQC_SWITCH_PORT_E)pstExAntennaParam->enPort4;

    pstLast4Port = &(pstDevInfo->stSatSwitch4PortParam);

    if (pstExAntennaParam->enSwitch22K > FRONTEND_SWITCH_22K_OFF)
    {
        st4Port.enLNB22K = HI_UNF_TUNER_FE_LNB_22K_ON;
    }
    else
    {
        st4Port.enLNB22K = HI_UNF_TUNER_FE_LNB_22K_OFF;
    }

    st4Port.enPolar = HI_UNF_TUNER_FE_POLARIZATION_V;

    if (pstConnParam != HI_NULL)
    {
        if (pstConnParam->unConnectPara.stSat.enPolar < HI_UNF_TUNER_FE_POLARIZATION_BUTT)
        {
            st4Port.enPolar = pstConnParam->unConnectPara.stSat.enPolar;
        }

        if ((pstDevInfo->stLnbCfg.enLNBBand == FRONTEND_LNB_BAND_KU)
            && (pstExAntennaParam->enSwitch22K == FRONTEND_SWITCH_22K_NONE))
        {
            if (pstConnParam->unConnectPara.stSat.u32Freq >= SAT_KU_MID_KHZ && pstConnParam->unConnectPara.stSat.u32Freq <= SAT_KU_MAX_KHZ)
            {
                st4Port.enLNB22K = HI_UNF_TUNER_FE_LNB_22K_ON;
            }
            else if (pstConnParam->unConnectPara.stSat.u32Freq >= SAT_KU_MIN_KHZ && pstConnParam->unConnectPara.stSat.u32Freq < SAT_KU_MID_KHZ)
            {
                st4Port.enLNB22K = HI_UNF_TUNER_FE_LNB_22K_OFF;
            }
        }
    }

    if (enAntennaSetType || (0 != memcmp(&st4Port, pstLast4Port, sizeof(HI_UNF_TUNER_DISEQC_SWITCH4PORT_S))))
    {
        HAL_DEBUG("====SVR_FE_SatSwitch4Port tuner id %d  enlevel %d port %d enpolar %d enlnb22k %d ========",
                  u32TunerID, st4Port.enLevel, st4Port.enPort, st4Port.enPolar, st4Port.enLNB22K);
        pstLastExAntennaInfo->enDiSEqCLevel = pstExAntennaParam->enDiSEqCLevel;
        pstLastExAntennaInfo->enPort4 = pstExAntennaParam->enPort4;
        memcpy(pstLast4Port, &st4Port, sizeof(HI_UNF_TUNER_DISEQC_SWITCH4PORT_S));
        return HI_UNF_TUNER_DISEQC_Switch4Port(u32TunerID, &st4Port);
    }

    return HI_SUCCESS;
}

static S32 fe_sat_switch16port(FRONTEND_DEV_INFO_S* pstDevInfo,
                               const FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstExAntennaParam,
                               FRONTEND_ANTENNA_SET_TYPE_E enAntennaSetType)
{
    U32 u32TunerID = pstDevInfo->u32TunerId;

    HI_UNF_TUNER_DISEQC_SWITCH16PORT_S st16Port;

    FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstLastExAntennaInfo = &(pstDevInfo->stCurExAntennaInfo);

    st16Port.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
    st16Port.enPort = (HI_UNF_TUNER_DISEQC_SWITCH_PORT_E)pstExAntennaParam->enPort16;

    if (st16Port.enPort == HI_UNF_TUNER_DISEQC_SWITCH_NONE)
    {
        return HI_SUCCESS;
    }

    if (enAntennaSetType
         || (pstExAntennaParam->enDiSEqCLevel != pstLastExAntennaInfo->enDiSEqCLevel)
         || (pstExAntennaParam->enPort16 != pstLastExAntennaInfo->enPort16))
    {
        pstLastExAntennaInfo->enDiSEqCLevel = pstExAntennaParam->enDiSEqCLevel;
        pstLastExAntennaInfo->enPort16 = pstExAntennaParam->enPort16;
        return HI_UNF_TUNER_DISEQC_Switch16Port(u32TunerID, &st16Port);
    }

    return HI_SUCCESS;
}
#endif

static S32 fe_sat_set_switch(FRONTEND_DEV_INFO_S* pstDevInfo,
                            const HI_UNF_TUNER_CONNECT_PARA_S* pstConnParam,
                            const FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstExAntennaParam,
                            FRONTEND_ANTENNA_SET_TYPE_E enAntennaSetType)
{
    if (pstExAntennaParam->enPort4 != FRONTEND_DISEQC_SWITCH_NONE)
    {
#ifdef DISEQC_SUPPORT

        FRONTEND_CHECK_DOFUNC(fe_sat_switch4port(pstDevInfo, pstConnParam, pstExAntennaParam, enAntennaSetType));
#else
        return ERROR_NOT_SUPPORTED;
#endif
    }

    if (pstExAntennaParam->enPort16 != FRONTEND_DISEQC_SWITCH_NONE)
    {
#ifdef DISEQC_SUPPORT

        FRONTEND_CHECK_DOFUNC(fe_sat_switch16port(pstDevInfo, pstExAntennaParam, enAntennaSetType));

        if (pstExAntennaParam->enPort4 != FRONTEND_DISEQC_SWITCH_NONE)
        {
            FRONTEND_CHECK_DOFUNC(fe_sat_switch4port(pstDevInfo, pstConnParam, pstExAntennaParam, enAntennaSetType));
        }
#else
        return ERROR_NOT_SUPPORTED;
#endif
    }

    return HI_SUCCESS;
}

#ifdef DISEQC_SUPPORT
static S32 fe_sat_set_motor(FRONTEND_DEV_INFO_S* pstDevInfo,
                            const FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstExAntennaParam,
                            FRONTEND_ANTENNA_SET_TYPE_E enAntennaSetType)
{
    U32 u32TunerID = pstDevInfo->u32TunerId;

    FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstLastExAntennaParam = &(pstDevInfo->stCurExAntennaInfo);

    pstLastExAntennaParam->enMotorType = pstExAntennaParam->enMotorType;

    //if relock and manul type , we need not turn motor
    if ((TRUE == pstDevInfo->bMotorManual) && (FRONTEND_ANTENNA_SET_RELOCK == enAntennaSetType))
    {
        return SUCCESS;
    }

    switch (pstExAntennaParam->enMotorType)
    {
        case FRONTEND_MOTOR_DISEQC12:
        {
            HI_UNF_TUNER_DISEQC_POSITION_S stPos;
            stPos.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stPos.u32Pos = pstExAntennaParam->u32MotoPos;

            if ((enAntennaSetType && (pstLastExAntennaParam->u32MotoPos != 0) && (pstExAntennaParam->u32MotoPos != 0))
                || pstLastExAntennaParam->u32MotoPos != pstExAntennaParam->u32MotoPos)
            {
                pstDevInfo->enNewStatus = FRONTEND_STATUS_MOTOR_MOVING;
                fe_event_callbak(pstDevInfo, pstDevInfo->enOldStatus, pstDevInfo->enNewStatus);
                HAL_DEBUG("u32LastMotorPos %d ======u32Pos = %d", pstLastExAntennaParam->u32MotoPos, stPos.u32Pos);
                HI_UNF_TUNER_DISEQC_GotoPos(u32TunerID, &stPos);
                pstLastExAntennaParam->u32MotoPos = stPos.u32Pos;
                //Motor postion and angular only one vilid, so when action of go to postion, clear the angular
                pstDevInfo->u16Angular = 0;
            }
        }
        break;

        case FRONTEND_MOTOR_USLAS:
        {
            HI_UNF_TUNER_DISEQC_USALS_ANGULAR_S stTurnParam;
            HI_UNF_TUNER_DISEQC_USALS_PARA_S stCalcParam;
            memset(&stCalcParam, 0, sizeof(stCalcParam));
            stCalcParam.u16LocalLongitude = s_stCoordinate.u16MyLongitude;
            stCalcParam.u16LocalLatitude = s_stCoordinate.u16MyLatitude;
            stCalcParam.u16SatLongitude = (U16)pstExAntennaParam->u32Longitude;
            stCalcParam.u16Angular = 0;

            HI_UNF_TUNER_DISEQC_CalcAngular(pstDevInfo->u32TunerId, &stCalcParam);
            stTurnParam.enLevel     = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stTurnParam.u16Angular  = stCalcParam.u16Angular;

            if (enAntennaSetType || pstDevInfo->u16Angular != stTurnParam.u16Angular)
            {
                HAL_DEBUG("u32LastMotorPos ======uangular %d", stTurnParam.u16Angular);
                pstDevInfo->enNewStatus = FRONTEND_STATUS_MOTOR_MOVING;
                fe_event_callbak(pstDevInfo, pstDevInfo->enOldStatus, pstDevInfo->enNewStatus);
                HI_UNF_TUNER_DISEQC_GotoAngular(pstDevInfo->u32TunerId, &stTurnParam);
                pstDevInfo->u16Angular = stTurnParam.u16Angular;
                pstLastExAntennaParam->u32Longitude = pstExAntennaParam->u32Longitude;
                //Motor postion and angular only one vilid, so when action of turn by angular, clear the postion
                pstLastExAntennaParam->u32MotoPos = 0xff;
            }
        }
        break;

        default:
            break;
    }

    return HI_SUCCESS;
}
#endif
#endif
static S32 fe_ter2_config_tsout(FRONTEND_DEV_INFO_S* pstDevInfo, const FRONTEND_TSOUT_CMD_TYPE_E enTsoutCmd, void* pParam)
{
    S32 s32Ret = SUCCESS;

    switch (enTsoutCmd)
    {
        case FRONTEND_TSOUT_TER2_GET_PLPNUM:
            return HI_UNF_TUNER_GetPLPNum(pstDevInfo->u32TunerId, (HI_U8*)pParam);

        case FRONTEND_TSOUT_TER2_GET_PLP_TYPE:
            return HI_UNF_TUNER_GetCurrentPLPType(pstDevInfo->u32TunerId, (HI_UNF_TUNER_T2_PLP_TYPE_E*)pParam);

        case FRONTEND_TSOUT_TER2_GET_PLP_GROUPID:
            return HI_UNF_TUNER_GetPLPGrpId(pstDevInfo->u32TunerId, (HI_U8*)pParam);

        case FRONTEND_TSOUT_TER2_SET_PLP_MODE:
            //set read mode, just for read plp type and plp grouptype.
            return HI_UNF_TUNER_SetPLPMode(pstDevInfo->u32TunerId, *(HI_U8*)pParam);

        case FRONTEND_TSOUT_TER2_SET_PLPID:
        {
            if (((*(HI_U8*)pParam) == pstDevInfo->stT2PlpParam.u8T2PlpID) && (HI_TRUE == pstDevInfo->bFreqSameAsLastScan))
            {
                return SUCCESS;
            }

            s32Ret = HI_UNF_TUNER_SetPLPID(pstDevInfo->u32TunerId, *(HI_U8*)pParam);
            pstDevInfo->enOldStatus = FRONTEND_STATUS_SCANNING;
            if (s32Ret == SUCCESS)
            {
                pstDevInfo->stT2PlpParam.bNeedSetCommonPlpID = HI_TRUE;
                pstDevInfo->stT2PlpParam.bNeedSetCommonPlpCombination = HI_TRUE;
                pstDevInfo->stT2PlpParam.u8T2PlpID = *(HI_U8*)pParam;
            }

            return s32Ret;
        }
        break;

        case FRONTEND_TSOUT_TER2_SET_COMMON_PLPID:

            //the same program setting u8T2CommonPlpID more than once will cause mosaic
            if (pstDevInfo->stT2PlpParam.bNeedSetCommonPlpID || ((*(HI_U8*)pParam) != pstDevInfo->stT2PlpParam.u8T2CommonPlpID))
            {
                s32Ret = HI_UNF_TUNER_SetCommonPLPID(pstDevInfo->u32TunerId, *(HI_U8*)pParam);

                if (s32Ret == HI_SUCCESS)
                {
                    pstDevInfo->stT2PlpParam.bNeedSetCommonPlpID = HI_FALSE;
                    pstDevInfo->stT2PlpParam.u8T2CommonPlpID = *(HI_U8*)pParam;
                }

                return s32Ret;
            }

            break;

        case FRONTEND_TSOUT_TER2_SET_COMPLP_COMB:

            //the same program setting u8T2CommonPlpCombination more than once will cause mosaic
            if (pstDevInfo->stT2PlpParam.bNeedSetCommonPlpCombination || ((*(HI_U8*)pParam) != pstDevInfo->stT2PlpParam.u8T2CommonPlpCombination))
            {
                s32Ret = HI_UNF_TUNER_SetCommonPLPCombination(pstDevInfo->u32TunerId, *(HI_U8*)pParam);

                if (s32Ret == HI_SUCCESS)
                {
                    pstDevInfo->stT2PlpParam.bNeedSetCommonPlpCombination = HI_FALSE;
                    pstDevInfo->stT2PlpParam.u8T2CommonPlpCombination = *(HI_U8*)pParam;
                }

                return s32Ret;
            }
            break;
        default:
            return ERROR_NOT_SUPPORTED ;
    }

    return HI_SUCCESS;
}

#ifdef DISEQC_SUPPORT
static S32 fe_sat_config_motor(FRONTEND_DEV_INFO_S* pstDevInfo, const FRONTEND_ANTENNA_CMD_TYPE_E enAntennaCmd, void* pParam)
{
#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)
    S32 s32Ret = FAILURE;

    switch (enAntennaCmd)
    {
        case FRONTEND_MOTOR_SET_COORDINATE:
        {
            FRONTEND_COORDINATE_S*  stCoordinate = (FRONTEND_COORDINATE_S*)pParam;
            FRONTEND_CHECK_RETURN_ERR(((stCoordinate->u16MyLatitude > 1800) || (stCoordinate->u16MyLongitude > 3600)), ERROR_INVALID_PARAM);
            s_stCoordinate.u16MyLatitude  = stCoordinate->u16MyLatitude;
            s_stCoordinate.u16MyLongitude = stCoordinate->u16MyLongitude;
            return HI_SUCCESS;
        }
        break;

        case FRONTEND_MOTOR_STORE_POSITION:
        {
            HI_UNF_TUNER_DISEQC_POSITION_S stPos;
            stPos.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stPos.u32Pos = ((FRONTEND_MOTOR_POSITION_S*)pParam)->u32Pos;
            pstDevInfo->stCurExAntennaInfo.u32MotoPos = ((FRONTEND_MOTOR_POSITION_S*)pParam)->u32Pos;
            pstDevInfo->u16Angular = 0;

            return HI_UNF_TUNER_DISEQC_StorePos(pstDevInfo->u32TunerId, &stPos);
        }
        break;

        case FRONTEND_MOTOR_GOTO_POSITION:
        {
            HI_UNF_TUNER_DISEQC_POSITION_S stPos;
            stPos.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stPos.u32Pos = ((FRONTEND_MOTOR_POSITION_S*)pParam)->u32Pos;

            if ((stPos.u32Pos != pstDevInfo->stCurExAntennaInfo.u32MotoPos) || (stPos.u32Pos != 0))
            {
                pstDevInfo->stCurExAntennaInfo.u32MotoPos = stPos.u32Pos;
                pstDevInfo->u16Angular = 0;
                return HI_UNF_TUNER_DISEQC_GotoPos(pstDevInfo->u32TunerId, &stPos);
            }

            return HI_SUCCESS;
        }
        break;

        case FRONTEND_MOTOR_LIMIT:
        {
            HI_UNF_TUNER_DISEQC_LIMIT_S stDiseqcLimit;
            memset(&stDiseqcLimit, 0, sizeof(stDiseqcLimit));
            stDiseqcLimit.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stDiseqcLimit.enLimit = (HI_UNF_TUNER_DISEQC_LIMIT_E)(((FRONTEND_MOTOR_LIMIT_S*)pParam)->enLimit);
            return HI_UNF_TUNER_DISEQC_SetLimit(pstDevInfo->u32TunerId, &stDiseqcLimit);
        }
        break;

        case FRONTEND_MOTOR_MOVE:
        {
            pstDevInfo->stCurExAntennaInfo.u32MotoPos = 0xff;
            pstDevInfo->u16Angular = 0;
            HI_UNF_TUNER_DISEQC_RUN_S stDiseqcRun;
            memset(&stDiseqcRun, 0 , sizeof(stDiseqcRun));
            stDiseqcRun.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stDiseqcRun.enDir = (HI_UNF_TUNER_DISEQC_MOVE_DIR_E)(((FRONTEND_MOTOR_MOVE_S*)pParam)->enDir);
            stDiseqcRun.u32RunningSteps = ((FRONTEND_MOTOR_MOVE_S*)pParam)->u32RunningSteps;
            return HI_UNF_TUNER_DISEQC_RunStep(pstDevInfo->u32TunerId, &stDiseqcRun);
        }
        break;

        case FRONTEND_MOTOR_STOP:

            return HI_UNF_TUNER_DISEQC_Stop(pstDevInfo->u32TunerId, HI_UNF_TUNER_DISEQC_LEVEL_1_X);

        case FRONTEND_MOTOR_CALC_ANGULAR:
        {
            if ((FE_INVILID_COORDINATE == s_stCoordinate.u16MyLatitude)
                && (FE_INVILID_COORDINATE == s_stCoordinate.u16MyLongitude))
            {
                HAL_ERROR(" Please set the Coordinate first!!\n");
                return HI_FAILURE;
            }

            FRONTEND_MOTOR_CALC_ANGULAR_S* pstAngular = (FRONTEND_MOTOR_CALC_ANGULAR_S*)pParam;
            HI_UNF_TUNER_DISEQC_USALS_PARA_S stUsalsParam;
            stUsalsParam.u16SatLongitude   = pstAngular->u16SatLongitude;
            stUsalsParam.u16LocalLatitude  = s_stCoordinate.u16MyLatitude;
            stUsalsParam.u16LocalLongitude = s_stCoordinate.u16MyLongitude;
            stUsalsParam.u16Angular = 0;
            s32Ret = HI_UNF_TUNER_DISEQC_CalcAngular(pstDevInfo->u32TunerId, &stUsalsParam);
            pstAngular->u16Angular = stUsalsParam.u16Angular;
            return s32Ret;
        }
        break;

        case FRONTEND_MOTOR_GOTO_ANGULAR:
        {
            FRONTEND_MOTOR_USALS_ANGULAR_S* pstHalUsalAngular = (FRONTEND_MOTOR_USALS_ANGULAR_S*)pParam;

            HI_UNF_TUNER_DISEQC_USALS_ANGULAR_S stUsalAngular;
            memset(&stUsalAngular, 0, sizeof(stUsalAngular));
            stUsalAngular.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stUsalAngular.u16Angular = pstHalUsalAngular->u32Angular;

            pstDevInfo->stCurExAntennaInfo.u32MotoPos = 0xff;
            pstDevInfo->u16Angular = stUsalAngular.u16Angular;
            HAL_ERROR("HI_SVR_FE_DISEQC_GOTO_ANGULAR %d ", pstDevInfo->u16Angular);
            return HI_UNF_TUNER_DISEQC_GotoAngular(pstDevInfo->u32TunerId, &stUsalAngular);
        }
        break;
        case FRONTEND_MOTOR_SET_MANUAL:
            if (HI_NULL == pParam)
            {
                return HI_FAILURE;
            }

            HI_BOOL bManual = *(HI_BOOL*)pParam;

            if (bManual)
            {
                pstDevInfo->bMotorManual = HI_TRUE;
            }
            else
            {
                pstDevInfo->bMotorManual = HI_FALSE;
            }

            return HI_SUCCESS;

        default:
            return ERROR_NOT_SUPPORTED ;
    }
#endif

    return ERROR_NOT_SUPPORTED;
}
#endif
static S32 fe_sat_set_antenna(FRONTEND_DEV_INFO_S* pstDevInfo,
                              const HI_UNF_TUNER_CONNECT_PARA_S* pstConnParam,
                              FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstExAntennaParam,
                              FRONTEND_ANTENNA_SET_TYPE_E enAntennaSetType)
{
#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)
    U32 u32TunerID = pstDevInfo->u32TunerId;

    HAL_DEBUG("fe_sat_set_antenna enAntennaSetTupe %d  ", enAntennaSetType);

    FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S* pstLastExAntennaParam = &(pstDevInfo->stCurExAntennaInfo);

#if 0
    static HI_U32 u32FirstPowerOn = 0;

    // set all antenna param
    if (bForceSet || (pstLastExAntennaParam->enLnbPower != pstExAntennaParam->enLnbPower))
    {
        HAL_DEBUG("HI_UNF_TUNER_SetLNBPower ");
        FRONTEND_CHECK_DOFUNC(HI_UNF_TUNER_SetLNBPower(u32TunerID, (HI_UNF_TUNER_FE_LNB_POWER_E)(pstExAntennaParam->enLnbPower)));
        pstLastExAntennaParam->enLnbPower = pstExAntennaParam->enLnbPower;

        if ((0 == u32FirstPowerOn)
            && (pstExAntennaParam->enLnbPower > 0)
            && (pstExAntennaParam->enMotorType > 0))
        {
            /*diseqc 1.2 1.3:
            motor first power on must wait 100ms for init,
            so just deal power on and playing with motor at once.
            do not need dealing LNB power off ---> on, motor has more time to init on this*/
            usleep(150 * 1000);
            u32FirstPowerOn++;
        }
    }

    if (bForceSet || (0 != memcmp(&(pstLastExAntennaParam->stLnbCfg), &(pstExAntennaParam->stLnbCfg), sizeof(FRONTEND_SAT_LNB_CONFIG_S))))
    {
        HAL_DEBUG("HI_UNF_TUNER_SetLNBConfig band %d ", pstLastExAntennaParam->stLnbCfg.enLNBBand);
        memcpy(&(pstLastExAntennaParam->stLnbCfg), &(pstExAntennaParam->stLnbCfg), sizeof(HI_UNF_TUNER_FE_LNB_CONFIG_S));
        FRONTEND_CHECK_DOFUNC(HI_UNF_TUNER_SetLNBConfig(u32TunerID, (HI_UNF_TUNER_FE_LNB_CONFIG_S*) & (pstExAntennaParam->stLnbCfg)));
    }

#endif

    //toneburst, little use
    if (pstExAntennaParam->enToneburst != FRONTEND_SWITCH_TONEBURST_NONE)
    {
        if (enAntennaSetType || (pstLastExAntennaParam->enToneburst != pstExAntennaParam->enToneburst))
        {
            pstLastExAntennaParam->enToneburst = pstExAntennaParam->enToneburst;
            HI_UNF_TUNER_SwitchToneBurst(u32TunerID, (HI_UNF_TUNER_SWITCH_TONEBURST_E)pstExAntennaParam->enToneburst);
        }
    }

    //12V switch, little use
    if (pstExAntennaParam->enSwitch12V != FRONTEND_SWITCH_0_12V_NONE)
    {
        if (enAntennaSetType || (pstLastExAntennaParam->enSwitch12V != pstExAntennaParam->enSwitch12V))
        {
            pstLastExAntennaParam->enSwitch12V = pstExAntennaParam->enSwitch12V;
            FRONTEND_CHECK_DOFUNC(HI_UNF_TUNER_Switch012V(u32TunerID, (HI_UNF_TUNER_SWITCH_0_12V_E)pstExAntennaParam->enSwitch12V));
        }
    }


    FRONTEND_CHECK_DOFUNC(fe_sat_set_switch(pstDevInfo, pstConnParam, pstExAntennaParam, enAntennaSetType));

    //moto set
    if (pstExAntennaParam->enMotorType != FRONTEND_MOTOR_NONE)
    {
#ifdef DISEQC_SUPPORT
        FRONTEND_CHECK_DOFUNC(fe_sat_set_motor(pstDevInfo, pstExAntennaParam, enAntennaSetType));
#else
    return ERROR_NOT_SUPPORTED;
#endif
    }

    //set 22k switch
    if (pstExAntennaParam->enSwitch22K != FRONTEND_SWITCH_22K_NONE)
    {
        if (enAntennaSetType || (pstLastExAntennaParam->enSwitch22K != pstExAntennaParam->enSwitch22K))
        {
            HAL_DEBUG("HI_UNF_TUNER_Switch22K  %d", pstExAntennaParam->enSwitch22K);
            pstLastExAntennaParam->enSwitch22K = pstExAntennaParam->enSwitch22K;
            FRONTEND_CHECK_DOFUNC(HI_UNF_TUNER_Switch22K(u32TunerID, (HI_UNF_TUNER_SWITCH_22K_E)(pstExAntennaParam->enSwitch22K)));
        }
    }
#endif

    return HI_SUCCESS;
}

static S32 fe_sat_blindscan(FRONTEND_DEV_INFO_S* pstDevInfo, const FRONTEND_SCAN_INFO_S*   const  pstScanParams)
{
    S32 s32Ret = FAILURE;
    HI_UNF_TUNER_BLINDSCAN_PARA_S stUnfBSParam;
    FRONTEND_SAT_BLINDSCAN_PARA_S* pstFeBSParam;

    if (NULL == pstScanParams->unScanInfo.stSatInfo.pstBindScanParam)
    {
        return s32Ret;
    }

    memset(&stUnfBSParam, 0, sizeof(stUnfBSParam));
    pstFeBSParam = pstScanParams->unScanInfo.stSatInfo.pstBindScanParam;

    stUnfBSParam.unScanPara.stSat.pfnDISEQCSet = fe_event_blindscan_set_diseqc;
    stUnfBSParam.unScanPara.stSat.pfnEVTNotify = fe_event_blindscan_notify;

    stUnfBSParam.enMode = HI_UNF_TUNER_BLINDSCAN_MODE_AUTO;

    if (pstScanParams->unScanInfo.stSatInfo.enSearchMod == FRONTEND_SEARCH_MOD_SAT_BLIND_MANUAL)
    {
        stUnfBSParam.enMode = HI_UNF_TUNER_BLINDSCAN_MODE_MANUAL;
        stUnfBSParam.unScanPara.stSat.u32StartFreq = pstFeBSParam->u32StartFreq;
        stUnfBSParam.unScanPara.stSat.u32StopFreq = pstFeBSParam->u32StopFreq;
        stUnfBSParam.unScanPara.stSat.enLNB22K = (HI_UNF_TUNER_FE_LNB_22K_E)conver_lnb_22k_to_unf(pstFeBSParam->enLNB22K);

        if (stUnfBSParam.unScanPara.stSat.enLNB22K > HI_UNF_TUNER_FE_LNB_22K_BUTT)
        {
            stUnfBSParam.unScanPara.stSat.enLNB22K = HI_UNF_TUNER_FE_LNB_22K_BUTT;
        }

        stUnfBSParam.unScanPara.stSat.enPolar = conver_polar_to_unf(pstFeBSParam->enPolar);
    }

    memcpy(&(pstDevInfo->stBlindScanParam), pstScanParams->unScanInfo.stSatInfo.pstBindScanParam, sizeof(FRONTEND_SAT_BLINDSCAN_PARA_S));
    s32Ret = HI_UNF_TUNER_BlindScanStart(pstDevInfo->u32TunerId, &stUnfBSParam);

    if (SUCCESS != s32Ret)
    {
        HAL_ERROR("HI_UNF_TUNER_BlindScanStart error ret 0x%x", s32Ret);
        return FAILURE;
    }

    pstDevInfo->bBlindScan = TRUE;

    return s32Ret;

}

static S32 fe_sat_lock(FRONTEND_DEV_INFO_S* pstDevInfo, HI_UNF_TUNER_CONNECT_PARA_S* pstConnParam, U32 u32Timeout, BOOL bRelock)
{
    U32 u32TunerID = pstDevInfo->u32TunerId;
    S32 s32Ret = FAILURE;

    if (bRelock)
    {
        HAL_DEBUG("set antenna relock ");
        FRONTEND_CHECK_DOFUNC(fe_sat_set_antenna(pstDevInfo, pstConnParam, &(pstDevInfo->stCurExAntennaInfo), FRONTEND_ANTENNA_SET_RELOCK));
    }
    else if (NULL != pstDevInfo->stScanInfo.unScanInfo.stSatInfo.pstExAntenna)
    {
        HAL_DEBUG("set antenna first time");
        FRONTEND_CHECK_DOFUNC(fe_sat_set_antenna(pstDevInfo, pstConnParam, pstDevInfo->stScanInfo.unScanInfo.stSatInfo.pstExAntenna, FRONTEND_ANTENNA_SET_FIRST));
        memcpy(&(pstDevInfo->stCurExAntennaInfo), pstDevInfo->stScanInfo.unScanInfo.stSatInfo.pstExAntenna, sizeof(FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S));
    }

    s_u32TimeBegin = time_get_now();
    s32Ret = HI_UNF_TUNER_Connect(u32TunerID, pstConnParam, u32Timeout);
    s_u32TimeUsed = time_get_now() - s_u32TimeBegin;
    HAL_DEBUG(" freq %d  s32Ret %d time used %d bRelock %d \n", pstConnParam->unConnectPara.stSat.u32Freq, s32Ret, s_u32TimeUsed, bRelock);
    return s32Ret;
}

static S32 fe_ter_lock(FRONTEND_DEV_INFO_S* pstDevInfo, HI_UNF_TUNER_CONNECT_PARA_S* pstConnParam, U32 u32Timeout)
{
    U32 u32TunerID = pstDevInfo->u32TunerId;
    S32 s32Ret = FAILURE;

    //when bTT2AutoLock is true, set u32Timeout, so fe will try T T2 as a loop. this will setted by user, not use by search
    if (pstDevInfo->stTRelockParam.bTT2AutoLock)
    {
        pstDevInfo->stTRelockParam.bTSignalTry = HI_FALSE;
        pstDevInfo->stTRelockParam.bT2SignalTry = HI_FALSE;
        pstDevInfo->stTRelockParam.u32StartTime = time_get_now();
        pstDevInfo->stTRelockParam.u32Timeout = pstDevInfo->stTRelockParam.u32T2SignalTimeout;

        if (HI_UNF_TUNER_SIG_TYPE_DVB_T == pstConnParam->enSigType)
        {
            pstDevInfo->stTRelockParam.u32Timeout = pstDevInfo->stTRelockParam.u32TSignalTimeout;
        }
    }

    s_u32TimeBegin = time_get_now();
    s32Ret = HI_UNF_TUNER_Connect(u32TunerID, pstConnParam, u32Timeout);
    s_u32TimeUsed = time_get_now() - s_u32TimeBegin;
    HAL_DEBUG(" freq %d  s32Ret 0x%x time used %d \n", pstConnParam->unConnectPara.stTer.u32Freq, s32Ret, s_u32TimeUsed);
    return s32Ret;
}

static S32 fe_ter_relock(FRONTEND_DEV_INFO_S* pstDevInfo, HI_UNF_TUNER_CONNECT_PARA_S* pstConnParam)
{
    U32 u32TunerID = pstDevInfo->u32TunerId;

    if ((time_get_now() - pstDevInfo->stTRelockParam.u32StartTime) >= pstDevInfo->stTRelockParam.u32Timeout)
    {
        if (HI_UNF_TUNER_SIG_TYPE_DVB_T == pstConnParam->enSigType)
        {
            pstDevInfo->stTRelockParam.bTSignalTry = HI_TRUE;
            pstConnParam->enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T2;
            pstDevInfo->stTRelockParam.u32Timeout = pstDevInfo->stTRelockParam.u32T2SignalTimeout;
        }
        else if (HI_UNF_TUNER_SIG_TYPE_DVB_T2 == pstConnParam->enSigType)
        {
            pstDevInfo->stTRelockParam.bT2SignalTry = HI_TRUE;
            pstConnParam->enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T;
            pstDevInfo->stTRelockParam.u32Timeout = pstDevInfo->stTRelockParam.u32TSignalTimeout;
        }

        FRONTEND_CHECK_DOFUNC_RETURN(HI_UNF_TUNER_Connect(u32TunerID, pstConnParam, 0));
        pstDevInfo->stTRelockParam.u32StartTime = time_get_now();
    }

    return SUCCESS;
}

static S32 fe_lock(FRONTEND_DEV_INFO_S* dev, U32 u32Timeout, BOOL bRelock)
{
    HI_UNF_TUNER_CONNECT_PARA_S stConnectPara;
    memset(&stConnectPara, 0 , sizeof(stConnectPara));

    FRONTEND_CHECK_DOFUNC_RETURN(conver_scan_param_to_unf(&(dev->stScanInfo), &stConnectPara));

    if (stConnectPara.enSigType == HI_UNF_TUNER_SIG_TYPE_SAT)
    {
        FRONTEND_CHECK_DOFUNC_RETURN(fe_sat_lock(dev, &stConnectPara, u32Timeout, bRelock));
    }
    else if (stConnectPara.enSigType == HI_UNF_TUNER_SIG_TYPE_DVB_T
             || stConnectPara.enSigType == HI_UNF_TUNER_SIG_TYPE_DVB_T2)
    {
        FRONTEND_CHECK_DOFUNC_RETURN(fe_ter_lock(dev, &stConnectPara, u32Timeout));
    }
    else
    {
        FRONTEND_CHECK_DOFUNC_RETURN(HI_UNF_TUNER_Connect(dev->u32TunerId, &stConnectPara, u32Timeout));
    }

    return SUCCESS;
}

static FRONTEND_FE_STATUS_E fe_check_status(HI_U32 u32TunerPort, HI_U32 u32Timeout)
{
    HI_S32                 s32Ret;
    HI_UNF_TUNER_STATUS_S  stStatus;
    HI_U32                 u32WaitLoop = u32Timeout / 10;
    FRONTEND_FE_STATUS_E   fe_status = FRONTEND_STATUS_UNLOCKED;

    do
    {
        s32Ret = HI_UNF_TUNER_GetStatus (u32TunerPort, &stStatus);

        if ((HI_SUCCESS == s32Ret) && (stStatus.enLockStatus == HI_UNF_TUNER_SIGNAL_LOCKED))
        {
            fe_status = FRONTEND_STATUS_LOCKED;
            break;
        }
    }while (u32WaitLoop--);

    return fe_status;
}

static void fe_task_unlock(FRONTEND_DEV_INFO_S* pstDevInfo)
{
    if (((FRONTEND_FE_TERRESTRIAL1 == pstDevInfo->stScanInfo.enFrontendType)
         || (FRONTEND_FE_TERRESTRIAL2 == pstDevInfo->stScanInfo.enFrontendType))
        && (pstDevInfo->u32Capability & FRONTEND_FE_TERRESTRIAL_ALL)
        && (pstDevInfo->stTRelockParam.bTT2AutoLock))
    {
        //try T & T2 signal auto lock
        fe_ter_relock(pstDevInfo, &pstDevInfo->stUnfConnectPara);

        if (pstDevInfo->stTRelockParam.bTSignalTry
            && pstDevInfo->stTRelockParam.bT2SignalTry)
        {
            fe_event_callbak(pstDevInfo, pstDevInfo->enOldStatus, pstDevInfo->enNewStatus);
            pstDevInfo->enOldStatus = pstDevInfo->enNewStatus;
        }
    }
    else
    {
        pstDevInfo->u32FeStatusCheckCount++;

        if (pstDevInfo->u32FeStatusCheckCount > FRONTEND_SIG_UNLOCK_CHECK_COUNT)
        {
            fe_event_callbak(pstDevInfo, pstDevInfo->enOldStatus, pstDevInfo->enNewStatus);
            pstDevInfo->u32FeStatusCheckCount = 0;
            pstDevInfo->enOldStatus = pstDevInfo->enNewStatus;

        }
    }

    return;
}
static void fe_task_lost(FRONTEND_DEV_INFO_S* pstDevInfo)
{
    pstDevInfo->u32FeStatusCheckCount++;

    if (pstDevInfo->u32FeStatusCheckCount > FRONTEND_SIG_LOST_CHECK_COUNT)
    {
        fe_event_callbak(pstDevInfo, pstDevInfo->enOldStatus, pstDevInfo->enNewStatus);
        pstDevInfo->u32FeStatusCheckCount = 0;
        pstDevInfo->u32FeSatRelockCount = 0;
        pstDevInfo->enOldStatus = pstDevInfo->enNewStatus;
    }

    return;
}
static void fe_task_relock(FRONTEND_DEV_INFO_S* pstDevInfo)
{
    HI_U32 u32Threshold = FRONTEND_SIG_LOST_CHECK_COUNT;
    if (((FRONTEND_FE_TERRESTRIAL1 == pstDevInfo->stScanInfo.enFrontendType)
         || (FRONTEND_FE_TERRESTRIAL2 == pstDevInfo->stScanInfo.enFrontendType))
        && (pstDevInfo->u32Capability & FRONTEND_FE_TERRESTRIAL_ALL)
        && (pstDevInfo->stTRelockParam.bTT2AutoLock))
    {
        //try T & T2 signal auto lock
        fe_ter_relock(pstDevInfo, &pstDevInfo->stUnfConnectPara);
    }
    else if (((FRONTEND_FE_SATELLITE1 == pstDevInfo->stScanInfo.enFrontendType)
             || (FRONTEND_FE_SATELLITE2 == pstDevInfo->stScanInfo.enFrontendType))
             && (pstDevInfo->bBlindScan != HI_TRUE))
    {
        pstDevInfo->u32FeSatRelockCount++;
        if (pstDevInfo->stCurExAntennaInfo.enMotorType != FRONTEND_MOTOR_NONE)
        {
            u32Threshold = FRONTEND_SIG_LOST_CHECK_COUNT + (pstDevInfo->u32MotorTimeout / FRONTEND_MSG_RECIEVE_TIMEOUT);
        }

        if (pstDevInfo->u32FeSatRelockCount > u32Threshold)
        {
            pstDevInfo->u32FeSatRelockCount = 0;
            fe_lock(pstDevInfo, 0, TRUE);
        }
    }

    return;
}

static void* fe_task(void* ptr)
{
    FRONTEND_DEV_INFO_S* pstDevInfo = (FRONTEND_DEV_INFO_S*)ptr;

    while (pstDevInfo->bOpen)
    {
        if (SUCCESS == msg_event_wait(pstDevInfo->pstMsgEvt, 0, FRONTEND_MSG_RECIEVE_TIMEOUT))
        {
            if (FRONTEND_MSG_SET_ANTENNA == pstDevInfo->enMsgInfo)
            {
                //set antenna, use force flag
                fe_sat_set_antenna(pstDevInfo, NULL, pstDevInfo->stScanInfo.unScanInfo.stSatInfo.pstExAntenna, FRONTEND_ANTENNA_SET_FORCE);
            }
            else if (FRONTEND_MSG_SCAN_FREQ == pstDevInfo->enMsgInfo)
            {
                fe_lock(pstDevInfo, 0, FALSE);
                pstDevInfo->enOldStatus = FRONTEND_STATUS_SCANNING;
            }
            else if (FRONTEND_MSG_SEND_EVENT == pstDevInfo->enMsgInfo)
            {
                fe_event_callbak(pstDevInfo, pstDevInfo->enOldStatus, pstDevInfo->enNewStatus);
            }
        }
        else if (FRONTEND_MSG_STATUS_IDLE != pstDevInfo->enMsgInfo)//status check
        {
            pstDevInfo->enNewStatus = fe_check_status(pstDevInfo->u32TunerId, 0);

            switch (pstDevInfo->enNewStatus)
            {
                case FRONTEND_STATUS_LOCKED:
                    if (pstDevInfo->enOldStatus != FRONTEND_STATUS_LOCKED)
                    {
                        fe_event_callbak(pstDevInfo, pstDevInfo->enOldStatus, pstDevInfo->enNewStatus);
                        pstDevInfo->enOldStatus = pstDevInfo->enNewStatus;
                    }

                    break;

                case FRONTEND_STATUS_UNLOCKED:

                    //connect msg send, need callback status
                    if (pstDevInfo->enOldStatus == FRONTEND_STATUS_SCANNING)
                    {
                        fe_task_unlock(pstDevInfo);
                    }
                    //signal lost, need callback status
                    else if (pstDevInfo->enOldStatus == FRONTEND_STATUS_LOCKED)
                    {
                        fe_task_lost(pstDevInfo);
                    }
                    // no need callback status, some signal need do something
                    else if (pstDevInfo->enOldStatus == FRONTEND_STATUS_UNLOCKED)
                    {
                        fe_task_relock(pstDevInfo);
                    }

                    break;

                default:
                    break;
            }

        }

    }

    pthread_detach(pthread_self());
    return NULL;
}

static S32 frontend_init(struct _FRONTEND_DEVICE_S* pstDev __unused, const FRONTEND_INIT_PARAMS_S*  const pstInitParams __unused)
{
    S32 s32Ret = FAILURE;
    U32 i = 0;
    U32 j = 0;
    FRONTEND_DEV_INFO_S* pstDevInfo = NULL;

    FRONTEND_LOCK();

    if (s_bFeInit)
    {
        FRONTEND_UNLOCK();
        return SUCCESS;
    }

    s32Ret = Ini_IOFile_Init();
    s32Ret |= Ini_IOFile_LoadFile(FRONTEND_CONFIG_INI_PATH);

    do
    {
        if (s32Ret != SUCCESS)
        {
            HAL_ERROR("Load file error %s\n", FRONTEND_CONFIG_INI_PATH);
            break;
        }

        s32Ret = HI_UNF_I2C_Init();

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("%s,%d error!! ret(0x%08x)", __func__, __LINE__, s32Ret);
            break;
        }

        s32Ret = config_read_file();

        if (HI_SUCCESS != s32Ret)
        {
            HAL_ERROR("ERROR: config_read_file fail.\n");
            break;
        }

        s32Ret = fe_port_reuse();

        if (HI_SUCCESS != s32Ret)
        {
            break;
        }

        s32Ret = HI_UNF_TUNER_Init();

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("ERROR: UNF Tuner Init fail.\n");
            break;
        }

        for (i = 0; i < s_u32FeCfgNum; i++)
        {
            if (s_pstFeCfgInfo[i].u32TunerDeviceStatus)
            {
                pstDevInfo = NULL;
                for (j = 0; j < s_u32FeNum; j++)
                {
                    if (s_pstFeDevInfo[j].u32TunerId == s_pstFeCfgInfo[i].u32TunerDeviceID)
                    {
                        pstDevInfo = &s_pstFeDevInfo[j];
                        break;
                    }
                }
                if (NULL != pstDevInfo)
                {
                    FRONTEND_CHECK_DOFUNC(fe_init(pstDevInfo, &s_pstFeCfgInfo[i], FRONTEND_INIT_FIRST_TIME));
                }
            }
        }

        s_bFeInit =  TRUE;
        s_stCoordinate.u16MyLatitude = FE_INVILID_COORDINATE;
        s_stCoordinate.u16MyLongitude = FE_INVILID_COORDINATE;
    }while (0);

    Ini_IOFile_DeInit();

    FRONTEND_UNLOCK();
    return s32Ret;
}

static S32 frontend_get_Index(HANDLE frontend_handle, U32 *pstIndex)
{
    U32 Index = 0;

    if (NULL == pstIndex)
    {
        HAL_ERROR("pstIndex is null\n!!");
        return FAILURE;
    }

    if (FRONTEND_MODE_ID != (frontend_handle >> 16))
    {
        HAL_ERROR("frontend_handle is invalid\n!!");
        return FAILURE;
    }

    Index = (frontend_handle & 0xffff);
    if (Index >= s_u32FeNum)
    {
        HAL_ERROR("frontend_handle is invalid\n!!");
        return FAILURE;
    }

    if (NULL == s_pstFeDevInfo)
    {
        HAL_ERROR("s_pstFeDevInfo is invalid\n!!");
        return FAILURE;
    }

    if (s_pstFeDevInfo[Index].hDevice != frontend_handle)
    {
        HAL_ERROR("frontend_handle is invalid\n!!");
        return FAILURE;
    }

    *pstIndex = Index;

    return SUCCESS;
}

static S32 frontend_open_device(struct _FRONTEND_DEVICE_S* pstDev, HANDLE* const phFrontend, const  FRONTEND_OPEN_PARAMS_S*  const pOpenParams)
{
    S32                     s32Ret = SUCCESS;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;
    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(phFrontend);
    FRONTEND_CHECK_PTR(pOpenParams);
    FRONTEND_CHECK_RETURN_ERR((pOpenParams->u32FrontendIndex >= s_u32FeNum), ERROR_INVALID_PARAM);

    FRONTEND_LOCK();

    do
    {
        // first open device, if need change mode, change mode.
        pstDevInfo = fe_open_device(pOpenParams);
        if (pstDevInfo == NULL)
        {
            HAL_ERROR("fe_open_device fail enFeType %d\n", pOpenParams->enFeType);
            s32Ret  = ERROR_FRONTEND_OPEN_FAILED;
            break;
        }

        // if not open task, need init task. if already open, clear status.
        if (!pstDevInfo->bOpen)
        {
            pstDevInfo->stOpenParam.u32FrontendIndex = pOpenParams->u32FrontendIndex;
            pstDevInfo->stOpenParam.enFeType         = pOpenParams->enFeType;
            pstDevInfo->stOpenParam.enFecRate        = pOpenParams->enFecRate;
            pstDevInfo->bOpen                        = TRUE;
            pstDevInfo->hDevice                      = ((FRONTEND_MODE_ID << 16) | pOpenParams->u32FrontendIndex);

            // no need put openParam to pstDevInfo, already change pstDevInfo->enSignalType in init funtion
            //pstDevInfo->enSignalType = pOpenParams->enFeType;
            pstDevInfo->bFreqSameAsLastScan = FALSE;

            *phFrontend = pstDevInfo->hDevice;

            msg_event_create(&pstDevInfo->pstMsgEvt, 0);

            pthread_create(&pstDevInfo->hTask , NULL, fe_task, (void*)pstDevInfo);
        }
        else
        {
            //clear status
            *phFrontend = pstDevInfo->hDevice;
        }
    }while (0);

    FRONTEND_UNLOCK();
    return s32Ret;
}

static S32 frontend_close_device(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE frontend_handle)
{
    S32                     s32Ret = SUCCESS;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(frontend_handle, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        if (pstDevInfo->bOpen)
        {
            pstDevInfo->bOpen  = FALSE;
            usleep(200 * 1000);
            msg_event_reset(pstDevInfo->pstMsgEvt);
            msg_event_destroy(pstDevInfo->pstMsgEvt);
        }
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_get_handle(struct _FRONTEND_DEVICE_S* pstDev __unused, U32 u32FrontendIndex, HANDLE* const phFrontend)
{
    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(phFrontend);

    FRONTEND_CHECK_RETURN_ERR((u32FrontendIndex >= s_u32FeNum), ERROR_INVALID_PARAM);

    FRONTEND_LOCK();

    if (s_pstFeDevInfo[u32FrontendIndex].bOpen)
    {
        *phFrontend = s_pstFeDevInfo[u32FrontendIndex].hDevice;
        FRONTEND_UNLOCK();
        return SUCCESS;
    }

    FRONTEND_UNLOCK();
    return FAILURE;
}

static S32 frontend_term(struct _FRONTEND_DEVICE_S* pstDev __unused, const FRONTEND_TERM_PARAMS_S* const pstTermParams __unused)
{
    U32 i = 0;
    S32 s32Ret = SUCCESS;

    FRONTEND_LOCK();

    if (FALSE == s_bFeInit)
    {
        FRONTEND_UNLOCK();
        HAL_DEBUG("frontend Already Deinit!!");
        return s32Ret;
    }

    do
    {
        // stop thread
        for (i = 0; i < s_u32FeNum; i ++)
        {
            if (s_pstFeDevInfo[i].bOpen)
            {
                s_pstFeDevInfo[i].bOpen = FALSE;
                usleep(200 * 1000);
                msg_event_reset(s_pstFeDevInfo[i].pstMsgEvt);
                msg_event_destroy(s_pstFeDevInfo[i].pstMsgEvt);
            }
        }

        config_free();

        if (s_pstFeDevInfo != NULL)
        {
            free(s_pstFeDevInfo);
            s_pstFeDevInfo = NULL;
        }

        s_bFeInit =  FALSE;
        s32Ret = SUCCESS;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_get_scan_info(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                                  FRONTEND_SCAN_INFO_S* const pstScanInfo)
{
    S32                     s32Ret = SUCCESS;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pstScanInfo);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        memcpy(pstScanInfo, &pstDevInfo->stScanInfo, sizeof(FRONTEND_SCAN_INFO_S));
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_sat_config_lnb(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_SAT_LNB_INFO_S*   const pstLnbInfo)
{
    S32 s32Ret = SUCCESS;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pstLnbInfo);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        if (FRONTEND_LNB_CMD_SET_PWR == (pstLnbInfo->enCmdType & FRONTEND_LNB_CMD_SET_PWR))
        {
            pstDevInfo->enLnbPower = pstLnbInfo->enLnbPower;
            s32Ret = HI_UNF_TUNER_SetLNBPower(pstDevInfo->u32TunerId, (HI_UNF_TUNER_FE_LNB_POWER_E)pstLnbInfo->enLnbPower);
            usleep(40 * 1000);
        }

        if (FRONTEND_LNB_CMD_SET_PWR != pstLnbInfo->enCmdType)
        {
            HAL_ERROR(" Just support set Lnb power!!");
            s32Ret = ERROR_NOT_SUPPORTED;
        }
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_sat_init_lnb(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_SAT_LNB_CONFIG_S* const pstLnbConfig)
{
    S32                     s32Ret = FAILURE;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;
    HI_UNF_TUNER_FE_LNB_CONFIG_S stUnfLnbConfig = {0};

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pstLnbConfig);
    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        memset(&stUnfLnbConfig, 0, sizeof(stUnfLnbConfig));
        conver_lnb_config_to_unf(pstLnbConfig, &stUnfLnbConfig);
        s32Ret = HI_UNF_TUNER_SetLNBConfig(pstDevInfo->u32TunerId, &stUnfLnbConfig);

        if (SUCCESS == s32Ret)
        {
            memcpy(&pstDevInfo->stLnbCfg, pstLnbConfig, sizeof(FRONTEND_SAT_LNB_CONFIG_S));
        }
    }while (0);

    FRONTEND_UNLOCK();
    return s32Ret;
}


static S32 frontend_sat_config_antenna(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_ANTENNA_CMD_TYPE_E enAntennaCmd, void* pParam)
{
#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;
    S32 s32Ret = FAILURE;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    if ((FRONTEND_UNICABLE_EXIT_SCANUSERBANDS != enAntennaCmd)
        && (FRONTEND_UNICABLE_SCAN_USERBANDS != enAntennaCmd))
    {
        FRONTEND_CHECK_PTR(pParam);
    }

#ifdef DISEQC_SUPPORT

    if (enAntennaCmd >= FRONTEND_MOTOR_SET_COORDINATE && enAntennaCmd <= FRONTEND_MOTOR_SET_MANUAL)
    {
        s32Ret = fe_sat_config_motor(pstDevInfo, enAntennaCmd, pParam);
        return s32Ret;
    }
#endif

    switch (enAntennaCmd)
    {
        case FRONTEND_SET_LNB_POWER:
        {
            FRONTEND_LNB_POWER_E enLnbPower = *(FRONTEND_LNB_POWER_E*)pParam;
            if (pstDevInfo->enLnbPower != enLnbPower)
            {
                HI_UNF_TUNER_FE_LNB_POWER_E enUnfPower = (HI_UNF_TUNER_FE_LNB_POWER_E)conver_lnb_power_to_unf(enLnbPower);
                s32Ret = HI_UNF_TUNER_SetLNBPower(pstDevInfo->u32TunerId, enUnfPower);
            }
            else
            {
                return HI_SUCCESS;
            }

            if (HI_SUCCESS == s32Ret)
            {
                if (FRONTEND_LNB_POWER_OFF == pstDevInfo->enLnbPower)
                {
                    usleep(40 * 1000);
                }
                pstDevInfo->enLnbPower = enLnbPower;
            }
            return s32Ret;
        }

        case FRONTEND_SET_SWITCH_22K:
            pstDevInfo->stCurExAntennaInfo.enSwitch22K = *(FRONTEND_SWITCH_22K_E*)pParam;
            return HI_UNF_TUNER_Switch22K(pstDevInfo->u32TunerId, *(HI_UNF_TUNER_SWITCH_22K_E*)pParam);

#ifdef DISEQC_SUPPORT
        case FRONTEND_DISEQC_SWITCH_4PORT:

            pstDevInfo->stCurExAntennaInfo.enDiSEqCLevel = FRONTEND_DISEQC_VER_1_X;
            pstDevInfo->stCurExAntennaInfo.enPort4 = ((FRONTEND_DISEQC_SWITCH4PORT_S*)pParam)->enPort;

            pstDevInfo->stSatSwitch4PortParam.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            pstDevInfo->stSatSwitch4PortParam.enPort = (HI_UNF_TUNER_DISEQC_SWITCH_PORT_E)pstDevInfo->stCurExAntennaInfo.enPort4;
            pstDevInfo->stSatSwitch4PortParam.enLNB22K = (HI_UNF_TUNER_FE_LNB_22K_E)conver_lnb_22k_to_unf(((FRONTEND_DISEQC_SWITCH4PORT_S*)pParam)->enLNB22K);

            if (pstDevInfo->stSatSwitch4PortParam.enLNB22K >= HI_UNF_TUNER_FE_LNB_22K_BUTT)
            {
                pstDevInfo->stSatSwitch4PortParam.enLNB22K = HI_UNF_TUNER_FE_LNB_22K_OFF;
            }

            pstDevInfo->stSatSwitch4PortParam.enPolar = conver_polar_to_unf(((FRONTEND_DISEQC_SWITCH4PORT_S*)pParam)->enPolar);
            return HI_UNF_TUNER_DISEQC_Switch4Port(pstDevInfo->u32TunerId, &(pstDevInfo->stSatSwitch4PortParam));
            break;

        case FRONTEND_DISEQC_SWITCH_16PORT:
        {
            HI_UNF_TUNER_DISEQC_SWITCH16PORT_S stSwitch16PortParam;

            pstDevInfo->stCurExAntennaInfo.enDiSEqCLevel = FRONTEND_DISEQC_VER_1_X;
            pstDevInfo->stCurExAntennaInfo.enPort16 = ((FRONTEND_DISEQC_SWITCH16PORT_S*)pParam)->enPort;
            stSwitch16PortParam.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
            stSwitch16PortParam.enPort = (HI_UNF_TUNER_DISEQC_SWITCH_PORT_E)pstDevInfo->stCurExAntennaInfo.enPort16;

            return HI_UNF_TUNER_DISEQC_Switch16Port(pstDevInfo->u32TunerId, &stSwitch16PortParam);
        }
        break;

        case FRONTEND_UNICABLE_SCAN_USERBANDS:
        {
            HI_UNF_TUNER_UNICABLE_SCAN_PARA_S stUnicableScanPara;
            memset(&stUnicableScanPara, 0 , sizeof(stUnicableScanPara));
            stUnicableScanPara.pfnEVTNotify = fe_event_unicable_notify;
            return HI_UNF_TUNER_UNICABLE_ScanUserBands(pstDevInfo->u32TunerId, stUnicableScanPara);
        }
        break;

        case FRONTEND_UNICABLE_EXIT_SCANUSERBANDS:
            return HI_UNF_TUNER_UNICABLE_ExitScanUserBands(pstDevInfo->u32TunerId);
            break;

        case FRONTEND_UNICABLE_GET_USERBANDSINFO:
        {
            HI_UNF_TUNER_SCR_UB_S**  ppUBinfo = (HI_UNF_TUNER_SCR_UB_S**)(((FRONTEND_UNICABLE_USERBANDS_S*)pParam)->ppUserBandsinfo);
            return HI_UNF_TUNER_UNICABLE_GetUserBandsInfo(pstDevInfo->u32TunerId, ppUBinfo, ((FRONTEND_UNICABLE_USERBANDS_S*)pParam)->pu32Num);
        }
            break;
#endif

        case FRONTEND_EXTRA_ANTENNA_CONFIG_ALL:
        {
            return fe_sat_set_antenna(pstDevInfo, NULL, (FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S*)pParam, FRONTEND_ANTENNA_SET_FORCE);
        }

        default:
            return ERROR_NOT_SUPPORTED;
            break;
    }

    return SUCCESS;
#else
    return ERROR_NOT_SUPPORTED;
#endif
}

static S32 frontend_get_lnb_pwr_status(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend __unused, FRONTEND_LNB_PWR_STATUS_E* const penLnbPwrStatus __unused)
{
    S32 s32Ret = SUCCESS;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    do
    {
        s32Ret = ERROR_NOT_SUPPORTED;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_start_scan(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                               const FRONTEND_SCAN_INFO_S*   const  pstScanParams,
                               const BOOL bSynch,
                               const U32 u32Timeout)
{
    S32 s32Ret = SUCCESS;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pstScanParams);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        if ((pstScanParams->enFrontendType == FRONTEND_FE_SATELLITE1) || (pstScanParams->enFrontendType == FRONTEND_FE_SATELLITE2))
        {
            if ((pstScanParams->unScanInfo.stSatInfo.enSearchMod == FRONTEND_SEARCH_MOD_BLIND)
                || (pstScanParams->unScanInfo.stSatInfo.enSearchMod == FRONTEND_SEARCH_MOD_SAT_BLIND_MANUAL))
            {
                s32Ret = fe_sat_blindscan(pstDevInfo, pstScanParams);
                break;
            }
        }

        if (pstScanParams->u16TsIndex == 1)
        {
            pstDevInfo->stTRelockParam.bTT2AutoLock = TRUE;
        }
        else
        {
            pstDevInfo->stTRelockParam.bTT2AutoLock = FALSE;
        }

        pstDevInfo->bFreqSameAsLastScan = FALSE;
        //check scan param
        s32Ret = fe_check_scan_param(pstDevInfo, pstScanParams);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("frontend_start_scan: param error");
            break;
        }

        if (SUCCESS != conver_scan_param_to_unf(pstScanParams, &pstDevInfo->stUnfConnectPara))
        {
            HAL_ERROR("conver_scan_param_to_unf not support this signal %d ", pstScanParams->enFrontendType);
            break;
        }

        //check scan param is same as now
        if (SUCCESS == fe_check_scan_status(&pstDevInfo->stScanInfo, pstScanParams))
        {
            if (pstDevInfo->enNewStatus == FRONTEND_STATUS_LOCKED)
            {
                pstDevInfo->bFreqSameAsLastScan = TRUE;
                pstDevInfo->enMsgInfo = FRONTEND_MSG_SEND_EVENT;
                msg_event_set(pstDevInfo->pstMsgEvt);
                break;
            }
        }

        //lock sync or send connect msg
        memcpy(&pstDevInfo->stScanInfo, pstScanParams, sizeof(FRONTEND_SCAN_INFO_S));
        if (((pstScanParams->enFrontendType == FRONTEND_FE_SATELLITE1) || (pstScanParams->enFrontendType == FRONTEND_FE_SATELLITE2))
            && (NULL != pstScanParams->unScanInfo.stSatInfo.pstExAntenna))
        {
            memcpy(&pstDevInfo->stScanExAntennaInfo, pstScanParams->unScanInfo.stSatInfo.pstExAntenna, sizeof(FRONTEND_SAT_EXTRA_ANTENNA_CONFIG_S));
            pstDevInfo->stScanInfo.unScanInfo.stSatInfo.pstExAntenna = &pstDevInfo->stScanExAntennaInfo;
        }

        pstDevInfo->enNewStatus = FRONTEND_STATUS_SCANNING;

        if (bSynch)
        {
            pstDevInfo->enOldStatus = FRONTEND_STATUS_SCANNING;
            pstDevInfo->enNewStatus = FRONTEND_STATUS_SCANNING;
            s32Ret = fe_lock(pstDevInfo, u32Timeout, FALSE);

            if (FRONTEND_STATUS_LOCKED == fe_check_status(pstDevInfo->u32TunerId, 0))
            {
                pstDevInfo->enOldStatus = FRONTEND_STATUS_LOCKED;
                pstDevInfo->enNewStatus = FRONTEND_STATUS_LOCKED;
            }
            else
            {
                pstDevInfo->enOldStatus = FRONTEND_STATUS_UNLOCKED;
                pstDevInfo->enNewStatus = FRONTEND_STATUS_UNLOCKED;
                HAL_DEBUG("Lock fail UNf ret 0x%x", s32Ret);
                s32Ret = ERROR_FRONTEND_OP_FAILED;
            }
            pstDevInfo->enMsgInfo = FRONTEND_MSG_STATUS_GO;
            msg_event_set(pstDevInfo->pstMsgEvt);
        }
        else
        {
            pstDevInfo->enMsgInfo = FRONTEND_MSG_SCAN_FREQ;
            msg_event_set(pstDevInfo->pstMsgEvt);
        }
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32  frontend_abort(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend)
{
    S32                     s32Ret = SUCCESS;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    if (pstDevInfo->bBlindScan)
    {
        // this fun will wait for ever, if blindscan thread is not exit. So do not lock here.
        s32Ret = HI_UNF_TUNER_BlindScanStop(pstDevInfo->u32TunerId);

        if (SUCCESS != s32Ret)
        {
            HAL_ERROR("stop blindscan error %d", s32Ret);
            s32Ret = ERROR_FRONTEND_OP_FAILED;
        }
        else
        {
            pstDevInfo->bBlindScan = FALSE;
        }
    }
    else
    {
        pstDevInfo->enMsgInfo = FRONTEND_MSG_STATUS_IDLE;
        pstDevInfo->enNewStatus = FRONTEND_STATUS_IDLE;
        pstDevInfo->enOldStatus = FRONTEND_STATUS_IDLE;
        memset(&(pstDevInfo->stScanInfo), 0, sizeof(FRONTEND_SCAN_INFO_S));
        msg_event_set(pstDevInfo->pstMsgEvt);
        s32Ret = SUCCESS;
    }

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_register_callback(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend,
                                      const FRONTEND_REG_CALLBACK_PARAMS_S* const pstRegParams)
{
    S32                     s32Ret = SUCCESS;
    U32                     i = 0;
    BOOL                    bFlag = FALSE;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pstRegParams);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        for (i = 0; i < FRONTEND_REG_CALLBACK_COUNT; i++)
        {
            if (pstDevInfo->astCallback[i].pCallBack == pstRegParams->pCallBack)
            {
                HAL_DEBUG("Function has been registered");
                bFlag = TRUE;
                break;
            }
        }

        if (bFlag)
        {
            break;
        }

        for (i = 0; i < FRONTEND_REG_CALLBACK_COUNT; i++)
        {
            if (pstDevInfo->astCallback[i].pCallBack == NULL)
            {
                memcpy(&pstDevInfo->astCallback[i], pstRegParams, sizeof(FRONTEND_REG_CALLBACK_PARAMS_S));
                break;
            }
        }

        if (i == FRONTEND_REG_CALLBACK_COUNT)
        {
            HAL_ERROR("Just can registe %d funtions", FRONTEND_REG_CALLBACK_COUNT);
            s32Ret = FAILURE;
        }

    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}
static S32 frontend_config_callback(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend, const void* const  pCallback,
                                    const FRONTEND_CFG_CALLBACK_E enCallbackCfg)
{
    S32                     s32Ret = SUCCESS;
    U32                     i = 0;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pCallback);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        for (i = 0; i < FRONTEND_REG_CALLBACK_COUNT; i++)
        {
            if (pstDevInfo->astCallback[i].pCallBack == pCallback)
            {
                if (enCallbackCfg == FRONTEND_CALLBACK_ENABLE)
                {
                    pstDevInfo->astCallback[i].bDisable = TRUE;
                }
                else if (enCallbackCfg == FRONTEND_CALLBACK_DISABLE)
                {
                    pstDevInfo->astCallback[i].bDisable = FALSE;
                }
                else
                {
                    pstDevInfo->astCallback[i].enCallbackType = FRONTEND_REG_CALLBACK_TYPE_BUTT;
                    pstDevInfo->astCallback[i].u32UserData = 0;
                    pstDevInfo->astCallback[i].pCallBack = NULL;
                    pstDevInfo->astCallback[i].bDisable  = FALSE;
                }

                break;
            }
        }

        if (FRONTEND_REG_CALLBACK_COUNT == i)
        {
            HAL_ERROR("Can not find funtion.");
        }
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_lock(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend)
{
    S32                     s32Ret = SUCCESS;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        pstDevInfo->enNewStatus = FRONTEND_STATUS_SCANNING;
        msg_event_set(pstDevInfo->pstMsgEvt);
        s32Ret = fe_lock(pstDevInfo, 100, FALSE);

        if (s32Ret != SUCCESS && s32Ret != HI_ERR_TUNER_FAILED_CONNECT)
        {
            s32Ret = ERROR_FRONTEND_OP_FAILED;
        }
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_get_bert(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,  float* const pfBert)
{
    S32                  s32Ret = 0;
    U32                  Index = 0;
    FRONTEND_DEV_INFO_S* pstDevInfo = NULL;
    U32                  ar_bert[3] = { 0 };
    S32                  i = 0;
    float                f_bert = (float)((1.12 * 100000) / 10000000); // 1.12e-2;
    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pfBert);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        if (pstDevInfo->enNewStatus == FRONTEND_STATUS_LOCKED)
        {
            s32Ret = HI_UNF_TUNER_GetBER (pstDevInfo->u32TunerId, ar_bert);

            if (SUCCESS != s32Ret)
            {
                s32Ret = ERROR_FRONTEND_OP_FAILED;
            }

            for (f_bert = (float) (ar_bert[1]); f_bert > 1.0; f_bert /= 10.0) ;

            f_bert = f_bert + (float) (ar_bert[0]);

            for (i = ar_bert[2]; i > 0; i--)
            {
                f_bert /= 10.0;
            }

            f_bert *= 0.557;

        }
        else
        {
            s32Ret = ERROR_FRONTEND_OP_FAILED;
        }

        * pfBert = f_bert;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_get_signal_quality(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend,
                                       U32* const pu32Quality)
{
    S32                         s32Ret = SUCCESS;
    U32                         Index = 0;
    FRONTEND_DEV_INFO_S*        pstDevInfo = NULL;
    HI_U32                      u32Quality = 0;
    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pu32Quality);
    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        s32Ret = HI_UNF_TUNER_GetSignalQuality(pstDevInfo->u32TunerId, &u32Quality);
        *pu32Quality = u32Quality;

        if (pstDevInfo->enNewStatus != FRONTEND_STATUS_LOCKED)
        {
            *pu32Quality = 0;
        }

        if (SUCCESS != s32Ret)
        {
            s32Ret = ERROR_FRONTEND_OP_FAILED;
        }
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_get_signal_strength(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, U32* const pu32Strength)
{
    S32                         s32Ret = SUCCESS;
    U32                         Index = 0;
    FRONTEND_DEV_INFO_S*        pstDevInfo = NULL;
    HI_U32                      signal_strength = 0;
    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pu32Strength);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        if (pstDevInfo->enNewStatus == FRONTEND_STATUS_LOCKED)
        {
            s32Ret = HI_UNF_TUNER_GetSignalStrength(pstDevInfo->u32TunerId, &signal_strength);

            if (HI_SUCCESS != s32Ret)
            {
                s32Ret = ERROR_FRONTEND_OP_FAILED;
                signal_strength = 0;
            }
        }
        else if (pstDevInfo->enSignalType == FRONTEND_FE_SATELLITE1 || pstDevInfo->enSignalType == FRONTEND_FE_SATELLITE2)
        {
            s32Ret = HI_UNF_TUNER_GetSignalStrength(pstDevInfo->u32TunerId, &signal_strength);
            HAL_DEBUG("DVBS get signal_strength %d \n", signal_strength);

            if (HI_SUCCESS != s32Ret)
            {
                s32Ret = ERROR_FRONTEND_OP_FAILED;
                signal_strength = 0;
            }
        }
        else
        {
            signal_strength = 0;
            s32Ret = ERROR_FRONTEND_OP_FAILED;
        }

        if (signal_strength >= 30 && signal_strength <= 37)
        {
            signal_strength = signal_strength - 1;
        }

        *pu32Strength = signal_strength;

    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_get_atvsignalinfo(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend __unused, FRONTEND_ATV_SIGNALINFO_S* const pstSignalInfo __unused)
{
    S32 s32Ret = 0;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    do
    {
        s32Ret = ERROR_NOT_SUPPORTED;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_get_connect_status(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, FRONTEND_FE_STATUS_E* const penStatus)
{
    S32                         s32Ret = 0;
    U32                         Index = 0;
    FRONTEND_DEV_INFO_S*        pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(penStatus);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        *penStatus = pstDevInfo->enNewStatus;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_get_info(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend,
                             FRONTEND_INFO_S*   const pstInfo)
{
    S32                         s32Ret = 0;
    U32                         Index = 0;
    FRONTEND_DEV_INFO_S*        pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pstInfo);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    do
    {
        memset(pstInfo, 0x00, sizeof(FRONTEND_INFO_S));
        pstInfo->u32SourceId  = pstDevInfo->enDemuxPort;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_get_capability(struct _FRONTEND_DEVICE_S* pstDev __unused, FRONTEND_CAPABILITY_S* const pstCapability)
{
    S32 s32Ret = SUCCESS;
    U32 i;

    FRONTEND_CHECK_PTR(pstCapability);
    FRONTEND_LOCK();

    if (FALSE == s_bFeInit)
    {
        s32Ret = Ini_IOFile_Init();
        s32Ret |= Ini_IOFile_LoadFile(FRONTEND_CONFIG_INI_PATH);

        if (s32Ret != SUCCESS)
        {
            HAL_ERROR("Load file error \n");
        }

        s32Ret = config_read_file();

        if (s32Ret != SUCCESS)
        {
            Ini_IOFile_DeInit();
            HAL_ERROR("read file error \n");
            FRONTEND_UNLOCK();
            return s32Ret;
        }

        Ini_IOFile_DeInit();
    }

    do
    {
        memset(pstCapability, 0, sizeof(FRONTEND_CAPABILITY_S));
        pstCapability->u32TunerNum = s_u32FeNum;

        for (i = 0; i < s_u32FeNum; i++)
        {
            pstCapability->au32FeType[i] = s_pstFeDevInfo[i].u32Capability;
            pstCapability->au32FeCurType[i] = s_pstFeDevInfo[i].enSignalType;
        }
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_get_channel_num(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE  hFrontend, U8* const pu8ChannelNum)
{
    S32                       s32Ret = 0;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pu8ChannelNum);

    FRONTEND_LOCK();

    do
    {
        s32Ret = ERROR_NOT_SUPPORTED;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_get_channel_info(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend __unused, const U8 u8ChannelIndex __unused,
                                     FRONTEND_G2_CHANNEL_INFO_S* const pstChannelInfo __unused, const U32 u32Timeout __unused)
{
    S32 s32Ret = 0;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    do
    {
        s32Ret = ERROR_NOT_SUPPORTED;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_config_channel(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend __unused,
                                   const U8 u8ChannelIndex __unused,
                                   const FRONTEND_G2_REQ_PARAMS_S* const pstReqParams __unused,
                                   FRONTEND_G2_RPN_PARAMS_S* const pstRpnParams __unused,
                                   const U32 u32Timeout __unused)
{
    S32 s32Ret = 0;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    do
    {
        s32Ret = ERROR_NOT_SUPPORTED;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;

}

static S32 frontend_config_tsout(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE hFrontend, const FRONTEND_TSOUT_CMD_TYPE_E enTsoutCmd, void* pParam)
{
    S32                       s32Ret = SUCCESS;
    U32                       Index = 0;
    FRONTEND_DEV_INFO_S*      pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);
    FRONTEND_CHECK_PTR(pParam);

    FRONTEND_LOCK();
    s32Ret = frontend_get_Index(hFrontend, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    if (enTsoutCmd <= FRONTEND_TSOUT_TER2_SET_COMPLP_COMB)
    {
        s32Ret = fe_ter2_config_tsout(pstDevInfo, enTsoutCmd, pParam);
        FRONTEND_UNLOCK();
        return s32Ret;
    }

    switch (enTsoutCmd)
    {
#if (HAL_STB_PRODUCT_CODE == UNF_PRODUCT_CODE)
        case FRONTEND_TSOUT_SAT2_GET_ISINUM:
            //for S2 mutiple Transport Streams
            s32Ret = HI_UNF_TUNER_GetSatTotalStream(pstDevInfo->u32TunerId, (HI_U8*)pParam);

            break;

        case FRONTEND_TSOUT_SAT2_GET_ISIID:
            s32Ret = HI_UNF_TUNER_GetSatIsiID(pstDevInfo->u32TunerId, ((FRONTEND_SAT2_ISIID_S*)pParam)->u8StreamNum,
                                            &(((FRONTEND_SAT2_ISIID_S*)pParam)->u8IsiID));
            break;

        case FRONTEND_TSOUT_SAT2_SET_ISIID:
        {
            if (((*(HI_U8*)pParam) == pstDevInfo->u8S2IsiID) && (HI_TRUE == pstDevInfo->bFreqSameAsLastScan))
            {
                s32Ret = HI_SUCCESS;
            }
            else
            {
                s32Ret = HI_UNF_TUNER_SetSatIsiID(pstDevInfo->u32TunerId, *(HI_U8*)pParam);
                if (s32Ret == HI_SUCCESS)
                {
                    pstDevInfo->u8S2IsiID = *(HI_U8*)pParam;
                }
            }

        }
            break;
#endif
        case FRONTEND_TSOUT_ISDBT_GET_TMCC_INFO:
            //For ISDB-T
            {
                s32Ret = ERROR_NOT_SUPPORTED;
#if (HAL_TV_PRODUCT_CODE == UNF_PRODUCT_CODE)
                HI_UNF_TUNER_SIGNALINFO_S stSignalInfo;
                FRONTEND_ISDBT_TMCC_INFO_S* pstTmccInfo = (FRONTEND_ISDBT_TMCC_INFO_S*)pParam;
                memset(&stSignalInfo, 0, sizeof(stSignalInfo));
                s32Ret = HI_UNF_TUNER_GetSignalInfo(pstDevInfo->u32TunerId, &stSignalInfo);

                if (s32Ret == HI_SUCCESS)
                {
                    pstTmccInfo->u8EmergencyFlag = stSignalInfo.unSignalInfo.stIsdbT.stISDBTTMCCInfo.u8EmergencyFlag;
                    pstTmccInfo->u8PartialFlag = stSignalInfo.unSignalInfo.stIsdbT.stISDBTTMCCInfo.u8PartialFlag;
                    pstTmccInfo->u8PhaseShiftCorr = stSignalInfo.unSignalInfo.stIsdbT.stISDBTTMCCInfo.u8PhaseShiftCorr;
                    pstTmccInfo->u8IsdbtSystemId = stSignalInfo.unSignalInfo.stIsdbT.stISDBTTMCCInfo.u8IsdbtSystemId;
                }
#endif
            }
            break;

        default:
            s32Ret = ERROR_NOT_SUPPORTED ;
            break;
    }

    FRONTEND_UNLOCK();
    return s32Ret;
}

static S32 frontend_atv_get_lock_status(struct _FRONTEND_DEVICE_S* pstDev, HANDLE  hFrontend __unused, FRONTEND_ATV_LOCK_STATUS_E* penLockStatus __unused)
{
    S32 s32Ret = 0;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    do
    {
        s32Ret = ERROR_NOT_SUPPORTED;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_atv_fineTune(struct _FRONTEND_DEVICE_S* pstDev __unused, HANDLE  hFrontend __unused, S32 s32Steps __unused)
{
    S32 s32Ret = 0;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    do
    {
        s32Ret = ERROR_NOT_SUPPORTED;
    }while (0);

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_standby(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE frontend_handle)
{
    S32                     s32Ret = SUCCESS;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(frontend_handle, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    pstDevInfo->enMsgInfo = FRONTEND_MSG_STATUS_IDLE;
    pstDevInfo->enNewStatus = FRONTEND_STATUS_IDLE;
    pstDevInfo->enOldStatus = FRONTEND_STATUS_IDLE;
    memset(&(pstDevInfo->stScanInfo), 0, sizeof(FRONTEND_SCAN_INFO_S));
    msg_event_set(pstDevInfo->pstMsgEvt);
    s32Ret = HI_UNF_TUNER_Standby(pstDevInfo->u32TunerId);

    if (HI_SUCCESS != s32Ret)
    {
        s32Ret = ERROR_FRONTEND_OP_FAILED;
    }

    FRONTEND_UNLOCK();

    return s32Ret;
}

static S32 frontend_wakeup(struct _FRONTEND_DEVICE_S* pstDev, const HANDLE frontend_handle)
{
    S32                     s32Ret = SUCCESS;
    U32                     Index = 0;
    FRONTEND_DEV_INFO_S*    pstDevInfo = NULL;

    FRONTEND_CHECK_INIT();
    FRONTEND_CHECK_PTR(pstDev);

    FRONTEND_LOCK();

    s32Ret = frontend_get_Index(frontend_handle, &Index);
    if (FAILURE == s32Ret)
    {
        FRONTEND_UNLOCK();
        return FAILURE;
    }

    pstDevInfo = &(s_pstFeDevInfo[Index]);

    s32Ret = HI_UNF_TUNER_WakeUp(pstDevInfo->u32TunerId);

    if (HI_SUCCESS != s32Ret)
    {
        s32Ret = ERROR_FRONTEND_OP_FAILED;
    }

    FRONTEND_UNLOCK();

    return s32Ret;
}

# ifdef TVOS_PLATFORM
static int frontend_device_close(struct hw_device_t *dev)
{
    struct frontend_context_t* ctx = (struct frontend_context_t*)dev;
    if (ctx) {
        free(ctx);
    }

    module_device = NULL;

    return 0;
}

/*****************************************************************************/

static int frontend_device_open(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device)
{
    int status = -EINVAL;

    if (!strcmp(name, FRONTEND_HARDWARE_FRONTEND0)) {

        struct frontend_context_t *dev = NULL;

        if (NULL == device)
        {
            return FAILURE;
        }

        if (module_device != NULL)
        {
            *device = (hw_device_t *)module_device;
            return 0;
        }

        dev = (struct frontend_context_t*)malloc(sizeof(*dev));
        if (NULL == dev)
        {
            return FAILURE;
        }

        /* initialize our state here */
        memset(dev, 0, sizeof(*dev));

        /* initialize the procs */
        dev->device.stCommon.tag     = HARDWARE_DEVICE_TAG;
        dev->device.stCommon.version = 1;
        dev->device.stCommon.module  = (hw_module_t*)(module);
        dev->device.stCommon.close   = frontend_device_close;

        dev->device.frontend_init                = frontend_init;
        dev->device.frontend_open                = frontend_open_device;
        dev->device.frontend_close               = frontend_close_device;
        dev->device.frontend_get_handle          = frontend_get_handle;
        dev->device.frontend_term                = frontend_term;
        dev->device.frontend_get_scan_info       = frontend_get_scan_info;
        dev->device.frontend_sat_config_lnb      = frontend_sat_config_lnb;
        dev->device.frontend_sat_init_lnb        = frontend_sat_init_lnb;
        dev->device.frontend_sat_config_antenna  = frontend_sat_config_antenna;
        dev->device.frontend_get_lnb_pwr_status  = frontend_get_lnb_pwr_status;
        dev->device.frontend_start_scan          = frontend_start_scan;
        dev->device.frontend_abort               = frontend_abort;
        dev->device.frontend_register_callback   = frontend_register_callback;
        dev->device.frontend_config_callback     = frontend_config_callback;
        dev->device.frontend_lock                = frontend_lock;
        dev->device.frontend_get_bert            = frontend_get_bert;
        dev->device.frontend_get_signal_quality  = frontend_get_signal_quality;
        dev->device.frontend_get_signal_strength = frontend_get_signal_strength;
        dev->device.frontend_get_atvsignalinfo   = frontend_get_atvsignalinfo;
        dev->device.frontend_get_connect_status  = frontend_get_connect_status;
        dev->device.frontend_get_info            = frontend_get_info;
        dev->device.frontend_get_capability      = frontend_get_capability;
        dev->device.frontend_get_channel_num     = frontend_get_channel_num;
        dev->device.frontend_get_channel_info    = frontend_get_channel_info;
        dev->device.frontend_config_tsout        = frontend_config_tsout;
        dev->device.frontend_config_channel      = frontend_config_channel;
        dev->device.frontend_atv_get_lock_status = frontend_atv_get_lock_status;
        dev->device.frontend_atv_fineTune        = frontend_atv_fineTune;
        dev->device.frontend_standby             = frontend_standby;
        dev->device.frontend_wakeup              = frontend_wakeup;


        *device = &dev->device.stCommon;

        module_device = (FRONTEND_DEVICE_S *)&dev->device.stCommon;;

        status = 0;
    }

    return status;
}


static struct hw_module_methods_t frontend_module_methods = {
    open: frontend_device_open
};

FRONTEND_MODULE_S HAL_MODULE_INFO_SYM = {
    common: {
        tag: HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
        id: FRONTEND_HARDWARE_MODULE_ID,
        name: "The frontend module",
        author: "The Skyworth' hhc",
        methods: &frontend_module_methods,
    }
};
#endif

static FRONTEND_DEVICE_S s_stDevice_frontend =
{
    .frontend_init                = frontend_init,
    .frontend_open                = frontend_open_device,
    .frontend_close               = frontend_close_device,
    .frontend_get_handle          = frontend_get_handle,
    .frontend_term                = frontend_term,
    .frontend_get_scan_info       = frontend_get_scan_info,
    .frontend_sat_config_lnb      = frontend_sat_config_lnb,
    .frontend_sat_init_lnb        = frontend_sat_init_lnb,
    .frontend_sat_config_antenna  = frontend_sat_config_antenna,
    .frontend_get_lnb_pwr_status  = frontend_get_lnb_pwr_status,
    .frontend_start_scan          = frontend_start_scan,
    .frontend_abort               = frontend_abort,
    .frontend_register_callback   = frontend_register_callback,
    .frontend_config_callback     = frontend_config_callback,
    .frontend_lock                = frontend_lock,
    .frontend_get_bert            = frontend_get_bert,
    .frontend_get_signal_quality  = frontend_get_signal_quality,
    .frontend_get_signal_strength = frontend_get_signal_strength,
    .frontend_get_atvsignalinfo   = frontend_get_atvsignalinfo,
    .frontend_get_connect_status  = frontend_get_connect_status,
    .frontend_get_info            = frontend_get_info,
    .frontend_get_capability      = frontend_get_capability,
    .frontend_get_channel_num     = frontend_get_channel_num,
    .frontend_get_channel_info    = frontend_get_channel_info,
    .frontend_config_tsout        = frontend_config_tsout,
    .frontend_config_channel      = frontend_config_channel,
    .frontend_atv_get_lock_status = frontend_atv_get_lock_status,
    .frontend_atv_fineTune        = frontend_atv_fineTune,
    .frontend_standby             = frontend_standby,
    .frontend_wakeup              = frontend_wakeup,
};

FRONTEND_DEVICE_S* getFrontEndDevice()
{
    return &s_stDevice_frontend;
}
