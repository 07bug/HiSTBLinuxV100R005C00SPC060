/**
* \file
* \brief Describes the information about the system module.
*/

#ifndef __TVOS_HAL_SYSTEM_H__
#define __TVOS_HAL_SYSTEM_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

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
#endif

/*************************** Macro Definition ****************************/
/** \addtogroup     HAL_SYSTEM */
/** @{ */  /** <!-- [HAL_SYSTEM] */

/**Module id define.*//** CNcomment:模块ID 定义 */
#define SYSTEM_HARDWARE_MODULE_ID       "system"

/**Device name define .*//** CNcomment:设备名称定义 */
#define SYSTEM_HARDWARE_SYSTEM0         "system0"

/**Chip ID max length.*//** CNcomment:芯片ID 最大长度 */
#define SYSTEM_CHIP_ID_LENGTH           (256)

/**Standby wakeup max key number.*//** CNcomment:可配置的待机唤醒键最大个数 */
#define SYSTEM_STANDBY_WKUP_KEY_MAXNUM  (8)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_SYSTEM */
/** @{ */  /** <!-- [HAL_SYSTEM] */

/**System init param *//** CNcomment:系统初始化参数 */
typedef struct _SYSTEM_INIT_PARAMS_S
{
    U32      u32MemSize;                /**<System total memory size(BYTE), can be ignored(zero) *//**<CNcomment:系统总共内存大小(BYTE), 可以忽略(0) */
    U32      u32SysMemSize;             /**<OS and driver total memory size(BYTE), can be ignored(zero) *//**<CNcomment: 操作系统和设备驱动内存大小 (BYTE), 可以忽略(0) */
    U32      u32DmxMemSize;             /**<Dmx driver memory size(BYTE), can be ignored(zero) *//**<CNcomment:Dmx 驱动内存大小(BYTE), 可以忽略(0) */
    U32      u32AvMemSize;              /**<AV Memory size(BYTE), can be ignored(zero) *//**<CNcomment:AV内存大小(BYTE), 可以忽略(0) */
    U32      u32UsrShareMemSize;        /**<usr_share Memory size(BYTE), can be ignored(zero) *//**<CNcomment:usr_share内存大小(BYTE), 可以忽略(0) */
} SYSTEM_INIT_PARAMS_S;

/**System deinit param *//** CNcomment:系统去初始化参数 */
typedef struct _SYSTEM_TERM_PARAMS_S
{
    U32 u32Dummy;    /**<Reserve *//**<CNcomment:保留*/
} SYSTEM_TERM_PARAMS_S;

#ifdef HAL_HISI_EXTEND_H
/**Defines of SYS event.*/
/**CNcomment: 定义SYS事件*/
typedef enum _SYS_EVT_E
{
    SYS_RM_EVT_WND_LACK    = 0x1,  /**<Indicates the current available window, no parameter *//**<CNcomment:指示当前没有可用的window, 无参数*/
    SYS_RM_EVT_WND_CREATED = 0x2,   /**<Indicates the window has been created, no parameter *//**<CNcomment:指示window已经创建了, 无参数*/
    SYS_RM_EVT_WND_DESTROYED = 0x4, /**<Indicates the window has been destroyed, no parameter *//**<CNcomment:指示window已经销毁了, 无参数*/
    SYS_RM_EVT_BUTT
} SYS_EVT_E;

/**
\brief SYS event callback. CNcomment:sys 事件回调函数类型声明 CNend
\attention \n
The function could call the api of sys module
\param[in] pClient sys client.CNcomment:sys client CNend
\param[in] enEvt sys event type.CNcomment:sys事件类型 CNend
\param[in] u32EventPara The data with event, see SYS_EVT_E.CNcomment:请参考 SYS_EVT_E 的说明 CNend
\retval ::SUCCESS CNcomment:成功 CNend
\retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化 CNend
\retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
\see \n
::SYS_EVT_E
*/
typedef S32 (*SYS_CALLBACK_PFN_T)(VOID* pClient,  SYS_EVT_E enEvent, U32 u32EventPara);

/**Struct of sys event config parameter*/
/**CNcomment:系统事件配置参数*/
typedef struct _SYS_EVT_CONFIG_PARAMS_S
{
    SYS_EVT_E           enEvt;                  /**<sys event*//**<CNcomment: sys事件,表示此配置对哪个事件有效*/
    BOOL                bEnable;                /**<enable*//**<CNcomment: 使能标志*/
    VOID*               pClient;                /**<fn client*//**<CNcomment: 回调函数的client*/
    SYS_CALLBACK_PFN_T  pfnCallback;            /**<Callback*//**<CNcomment: 回调函数*/
} SYS_EVT_CONFIG_PARAMS_S;
#endif

/**System work mode *//** CNcomment:系统工作模式 */
typedef enum _SYSTEN_SYSTEM_MODE_E
{
    SYSTEM_SYSTEM_MODE_NORMAL = 0,      /**<Normal work mode *//**<CNcomment:正常工作模式*/
    SYSTEM_SYSTEM_MODE_SLOW,            /**<Low power mode, fake standby, front panel led can display time *//**<CNcomment:低功耗工作模式, 对应假待机,前面板可显示时间*/
    SYSTEM_SYSTEM_MODE_STANDBY,         /**<standby work mode, true standby, front panel led cann't display*//**<CNcomment:真待机工作模式, 前面板不可显示*/
    SYSTEM_SYSTEM_MODE_BUTT
} SYSTEN_SYSTEM_MODE_E;

/**Key code structure *//** CNcomment:按键值结构 */
typedef struct _SYSTEM_KEY_CODE_S
{
    U32     u32KeyLowerValue;            /**<Key code value low  *//**<CNcomment:按键值低位*/
    U32     u32KeyUpperValue;            /**<Key code value high  *//**<CNcomment:按键值高位*/
} SYSTEM_KEY_CODE_S;

/**Key type type *//** CNcomment:按键类型 */
typedef enum _SYSTEM_KEY_TYPE_E
{
    KEY_TYPE_IR = 0,                     /**<IR type *//**<CNcomment:红外遥控按键*/
    KEY_TYPE_PANEL,                      /**<Front panel type *//**<CNcomment:前面板按键*/
    KEY_TYPE_BUTT
} SYSTEM_KEY_TYPE_E;

/**Key info *//** CNcomment:按键信息*/
typedef struct _SYSTEM_KDB_KEY_DATA_S
{
    BOOL                  bExist;        /**<Whether valid *//**<CNcomment:配置是否有效*/
    SYSTEM_KEY_TYPE_E     enType;        /**<Key type, IR or panel key *//**<CNcomment:按键类型，遥控器或面板按键*/
    SYSTEM_KEY_CODE_S     stCode;        /**<Key value *//**<CNcomment:接收到的按键键值*/
} SYSTEM_KDB_KEY_DATA_S;

/**Time info, UTC time *//** CNcomment:时间信息，用UTC时间表达*/
typedef struct _SYSTEM_TIME_S
{
    U64   u64TimeSec;
} SYSTEM_TIME_S;

/**Time info, UTC time *//** CNcomment:时间信息，用UTC时间表达*/
typedef struct _SYSTEM_WAKEUPINFO_S
{
    SYSTEM_KDB_KEY_DATA_S stWakeupKey;
    SYSTEM_TIME_S stStandbyPeriodTime;
} SYSTEM_WAKEUPINFO_S;

/**System standby  config param *//** CNcomment:系统待机配置参数 */
typedef struct _SYSTEM_STANDBY_PARA_S
{
    SYSTEN_SYSTEM_MODE_E    enSystemMode;       /**<System work mode *//**<CNcomment:系统工作模式*/
    SYSTEM_KDB_KEY_DATA_S   astStandbyKey[SYSTEM_STANDBY_WKUP_KEY_MAXNUM]; /**<Standby wakeup key config *//**<CNcomment:待机唤醒键配置*/
    BOOL                    bAutoWakeup;        /**<Whether auto wakeup *//**<CNcomment: 是否自动唤醒*/
    BOOL                    bDispTimeEnable;    /**<Whether display time when standby *//**<CNcomment: 待机时前面板是否显示时间*/
    SYSTEM_TIME_S           stCurrTime;         /**<System current time *//**<CNcomment:系统当前时间*/
    SYSTEM_TIME_S           stAlarmTime;        /**<System wakeup time *//**<CNcomment:系统自动唤醒时间*/
    BOOL                    bWifiPowerOn;       /**<Whether Wifi power supply when standby   *//**<CNcomment:待机时wifi是否供电*/
    BOOL                    bCmPowerOn;         /**<Whether cable moderm power supply when standby   *//**<CNcomment:待机时cable moderm是否供电*/
    U32                     u32Dummy;           /**<Reserve *//**<CNcomment:保留*/
} SYSTEM_STANDBY_PARA_S;

/**System crypt mode *//** CNcomment:系统加解密模式 */
typedef enum _SYSTEM_CRYPT_MODE_E
{
    SYSTEM_CRYPT_MODE_PLAIN,        /**<Plain mode *//**<CNcomment:Plain模式*/
    SYSTEM_CRYPT_MODE_ENCRYPT,      /**<Encrypt mode *//**<CNcomment:Encrypt模式*/
    SYSTEM_CRYPT_MODE_DECRYPT,      /**<Decrypt mode *//**<CNcomment:Decrypt模式*/
    SYSTEM_CRYPT_MODE_BYTT
} SYSTEM_CRYPT_MODE_E;

/**chip desc info *//** CNcomment:芯片描述信息 */
typedef struct _SYSTEM_CHIP_ID_S
{
    U32     u32ActLen;                             /**<chip id length *//**<CNcomment:芯片ID 实际长度*/
    U8      au8ChipIdBuf[SYSTEM_CHIP_ID_LENGTH];   /**<chip id info buf *//**<CNcomment:芯片ID buffer*/
} SYSTEM_CHIP_ID_S;

#ifdef ANDROID_HAL_MODULE_USED
/**System module structure(Android require) */
/**CNcomment:系统模块结构(Android对接要求) */
typedef struct _SYSTEM_MODULE_S
{
    struct hw_module_t stCommon;                   /**<Module common structure(Android require) *//**<CNcomment:模块通用结构(Android对接要求 ) */
} SYSTEM_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup     HAL_SYSTEM */
/** @{ */  /** <!-- [HAL_SYSTEM] */

/**System device structure*//** CNcomment:系统设备结构 */
typedef struct _SYSTEM_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:模块通用结构(Android对接要求 ) */
#endif

    /**
    \brief System  init.CNcomment:系统初始化 CNend
    \attention \n
    Soc development kit init and alloc necessary resource, should be called before other module, repeat call return success.
    CNcomment:板级开发包初始化及分配必要的资源, 应该在其他模块初始化前被调用,本函数重复调用返回成功. CNend
    \param[in] pstInitParams system module init param.CNcomment:初始化参数 CNend

    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_SYSTEM_INIT_FAILED  Soc development kit init error.CNcomment:板级开发包初始化错误。CNend
    \retval ::ERROR_NO_MEMORY not enough memory .CNcomment:内存不足。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SYSTEM_INIT_PARAMS_S

    \par example
    \code
    SYSTEM_INIT_PARAMS_S stInitParam;
    memset(&stInitParam, 0x0, sizeof(SYSTEM_INIT_PARAMS_S));
    stInitParam.u32Memsize=256*1024*1024;
    if (SUCCESS != system_init(pstDev, (const SYSTEM_INIT_PARAMS_S * const)&stInitParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_init)(struct _SYSTEM_DEVICE_S* pstDev, const SYSTEM_INIT_PARAMS_S* const pstInitParams);

    /**
    \brief System  deinit.CNcomment:系统去初始化 CNend
    \attention \n
    Soc development kit deinit and release occupied resource, should be called after other module deinit, repeat call return success.
    CNcomment:板级开发包去初始化及释放占用的资源, 应该在其他模块去初始化后调用,本函数重复调用返回成功. CNend
    \param[in] pstTermParams system module term param.CNcomment:初始化模块去初始化参数 CNend

    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_SYSTEM_DEINIT_FAILED  Soc development kit deinit error.CNcomment:板级开发包去初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SYSTEM_TERM_PARAMS_S

    \par example
    \code
    SYSTEM_TERM_PARAMS_S stDeInitParam;
    stDeInitParam.u32Dummy = 0;
    if (SUCCESS != system_term(pstDev, (const SYSTEM_TERM_PARAMS_S * const)&stDeInitParam))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_term)(struct _SYSTEM_DEVICE_S* pstDev, const SYSTEM_TERM_PARAMS_S* const pstTermParams);

#ifdef HAL_HISI_EXTEND_H
    /**
    \brief Config the callback attribute of SYS event. CNcomment:配置某一SYS事件的参数 CNend
    \attention \n
    The function can execute regist/unregist
    1.Each event can register callback function and set it's config independently.
    2.Only one callback function can be registered for a SYS event, so the callback function will be recovered.
    CNcomment: 通过本函数可以执行的操作有regist/remove/disable/enable
    1. 每个事件都可以独立注册/反注册自己的回调函数.
    3. 同一个事件只能注册一个回调函数,即:后面注册的回调函数会覆盖原有的回调函数.
    CNend
    \param[in] pstCfg Config param.CNcomment:事件配置参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::ERROR_INVALID_PARAM Parameter invalid .CNcomment:参数错误CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SYS_EVT_CONFIG_PARAMS_S
    */
    S32 (*system_evt_config)(struct _SYSTEM_DEVICE_S* pstDev, const SYS_EVT_CONFIG_PARAMS_S* pstCfg);
#endif
    /**
    \brief System standby mode switch.CNcomment:待机模式切换 CNend
    \attention \n
    This interface is the last step of the standby operation, before call, should stop related system operation, such as close AV/DMX , three cases:
    1. lower layer part standby operate, this interface normal return, system is still normal running, apps need to recognize waking signal and deal with the signal
    2. lower layer standby, system blocks in this interface, lower layer needs to recognize waking signal and notify apps
    3. lower layer enters true standby by MCU, equivalent to hardware turnoff, wake up signal received by MCU
    CNcomment:此接口为待机的最后一步操作，调用接口前，应先停止相应的系统操作，比如关闭AV，DMX等
    调用此接口时,将可能出现三种情况:
    1. 调用后，底层做了部分待机操作后，函数正常返回，系统实际还在运行，由应用程序自己识别唤醒信号，
        并做相应的操作;
    2. 函数调用后，底层待机，并且阻塞在待机函数里面，直到底层自己识别到唤醒按键后正常返回，
        并在函数返回同时向应用程序模拟发送一次唤醒信号，之后应用程序再进行开AV播放等操作
    3. 函数调用后，直接由MCU真待机，此时相当于硬件关机, 由MCU 接收唤醒信号    CNend
    \param[in] standby standy config.CNcomment: 待机参数 CNend
    \param[out] pstWakeupInfo wake up information.CNcomment: 待机唤醒参数 CNend

    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED system don't init.CNcomment:系统未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SYSTEM_STANDBY_FAILED lower layer standby failed.CNcomment:底层待机操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SYSTEM_STANDBY_PARA_S

    \par example
    \code
    SYSTEM_STANDBY_PARA_S stStandbyPara;

    memset(&stStandbyPara, 0x0, sizeof(SYSTEM_STANDBY_PARA_S));
    stStandbyPara.enSystemMode = SYSTEM_SYSTEM_MODE_STANDBY;
    if (SUCCESS != system_switch_standby((const SYSTEM_STANDBY_PARA_S*const)&stStandbyPara))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_switch_standby)(struct _SYSTEM_DEVICE_S* pstDev, const SYSTEM_STANDBY_PARA_S* const pstPara, SYSTEM_WAKEUPINFO_S* pstWakeupInfo);

    /**
    \brief Get the period during standby status.
    CNcomment:\brief 获取从待机到唤醒持续的时间。CNend

    \attention \n

    \param[out] pu32Period  The period of standby. CNcomment:待机持续的时间 CNend
    \retval ::ERROR_NOT_INITED  The PMoC device is not started.            CNcomment:PMoC设备未打开 CNend
    \retval ::ERROR_NULL_PTR  The pointer is invalid.               CNcomment:非法指针 CNend
    \retval ::FAILURE  It fails to get standby period.    CNcomment:获取待机时间失败 CNend
    \see \n
    N/A
    */
    S32 (*system_get_standby_period)(U32 *pu32Period);

    /**
    \brief Gets the wake-up mode of the ARM.
    CNcomment:\brief 获取当前待机方式。CNend

    \attention \n

    \param[out] pstPara  Wake-up mode of the ARM                            CNcomment:ARM唤醒方式。CNend
    \retval HI_SUCCESS Success                                              CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  The PMoC device is not started.         CNcomment:PMoC设备未打开 CNend
    \retval ::ERROR_NULL_PTR  The pointer is invalid.            CNcomment:非法指针 CNend
    \retval ::ERROR_INVALID_PARAM  The parameter is invalid.           CNcomment:非法参数 CNend
    \retval ::FAILURE It fails to set power val.    CNcomment:获取唤醒方式失败 CNend
    \see \n
    N/A
    */
    S32 (*system_get_standby_param)(SYSTEM_STANDBY_PARA_S* pstPara);

    /**
    \brief Sets the wake-up mode of the ARM.
    CNcomment:\brief 设置当前待机方式。CNend

    \attention \n
    You can query the original IR code values by referring to IR remote manuals.\n
    In addition, you can query the relationships between the keys and key IDs by checking the connection between hardware and chips.\n
    CNcomment:IR原始码值可以通过遥控器的使用手册得到\n
    按键与键值的对应关系可以通过硬件和芯片的连接关系得到。CNend

    \param[in] pstPara  Wake-up mode of the ARM                             CNcomment:ARM唤醒方式。CNend
    \retval HI_SUCCESS Success                                              CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  The PMoC device is not started.         CNcomment:PMoC设备未打开 CNend
    \retval ::ERROR_NULL_PTR  The pointer is invalid.            CNcomment:非法指针 CNend
    \retval ::ERROR_INVALID_PARAM  The parameter is invalid.           CNcomment:非法参数 CNend
    \retval ::FAILURE It fails to set power val.    CNcomment:设置唤醒方式失败 CNend
    \see \n
    N/A
    */
    S32 (*system_set_standby_param)(const SYSTEM_STANDBY_PARA_S* const pstPara);

    /**
    \brief Perform a generic transfer with the cryptocore.CNcomment:加解密数据转换 CNend
    \attention \n
    Implementation is related with platform, maybe need ncache memory or dma  .
    CNcomment:具体实现平台相关,可能用到ncache内存和dma. CNend
    \param[in] u32SrcBuf source buffer addr.CNcomment:源地址 CNend
    \param[in] u32DestBuf dest buffer addr buffer.CNcomment:目的地址 CNend
    \param[in] u32DataSize data size.CNcomment: 数据大小 CNend
    \param[in] enMode operate mode.CNcomment: 操作模式 CNend
    \param[in] bBlock block flag.CNcomment: 是否阻塞的标志 CNend

    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_SUPPORTED not supported.CNcomment:不支持。CNend
    \retval ::ERROR_INVALID_PARAM invalid param.CNcomment:参数错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SYSTEM_CRYPT_MODE_E

    \par example
    */
    S32 (*system_crypt_transfer)(struct _SYSTEM_DEVICE_S* pstDev, U32 u32SrcBuf, U32 u32DestBuf, U32 u32DataSize, SYSTEM_CRYPT_MODE_E enMode, BOOL bBlock);

    /**
    \brief get chip id info.CNcomment:获取芯片ID信息 CNend
    \attention \n
    None.
    \param[out] pstChipId chip id info.CNcomment:芯片ID信息 CNend

    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_SUPPORTED not supported.CNcomment:不支持。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SYSTEM_CHIP_ID_S

    \par example
    \code
    SYSTEM_CHIP_ID_S stSystemChipInfo;
    memset(&stSystemChipInfo, 0x0, sizeof(SYSTEM_CHIP_ID_S));
    if (SUCCESS != system_get_chip_id(pstDev, (SYSTEM_CHIP_ID_S * const)&stSystemChipInfo))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_get_chip_id)(struct _SYSTEM_DEVICE_S* pstDev, SYSTEM_CHIP_ID_S* const pstChipId);

    /**
    \brief system reboot.CNcomment:系统重启 CNend
    \attention \n
    if success, cann't return.
    \param[in] u32TimeMs system reboot time(ms).CNcomment:系统重启时间(ms) CNend

    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_SUPPORTED not supported.CNcomment:不支持。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    if (SUCCESS != system_sys_reboot(pstDev, 0))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_sys_reboot)(struct _SYSTEM_DEVICE_S* pstDev, const U32 u32TimeMs);

    /**
    \brief system halt.CNcomment:系统关机 CNend
    \attention \n
    if success, cann't return.
    \param[in] u32TimeMs system halt time(ms).CNcomment:系统关机时间(ms) CNend

    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_SUPPORTED not supported.CNcomment:不支持。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    if (SUCCESS != system_sys_halt(pstDev, 0))
    {
        return FAILURE;
    }

    \endcode
    */
    S32 (*system_sys_halt)(struct _SYSTEM_DEVICE_S* pstDev, const U32 u32TimeMs);
} SYSTEM_DEVICE_S ;

/**
\brief direct get system device api, for linux and android.CNcomment:获取系统设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get system device api，for linux and andorid.
CNcomment:获取系统设备接口，linux和android平台都可以使用. CNend
\retval  system device pointer when success.CNcomment:成功返回system设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::SYSTEM_DEVICE_S

\par example
*/
SYSTEM_DEVICE_S *getSystemDevice();

/**
\brief Open HAL System module device.CNcomment:打开HAL系统模块设备 CNend
\attention \n
Open HAL System module device(for compatible Android HAL).
CNcomment:打开HAL系统模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice system device structure.CNcomment:系统设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::SYSTEM_DEVICE_S

\par example
*/
static inline int system_open(const struct hw_module_t* pstModule, SYSTEM_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, SYSTEM_HARDWARE_SYSTEM0, (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getSystemDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL System module device.CNcomment:关闭HAL系统模块设备 CNend
\attention \n
Close HAL System module device(for compatible Android HAL).
CNcomment:关闭HAL系统模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice system device structure.CNcomment:系统设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::SYSTEM_DEVICE_S

\par example
*/
static inline int system_close(SYSTEM_DEVICE_S* pstDevice)
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
#endif

#endif /*__TVOS_HAL_SYSTEM_H__*/

