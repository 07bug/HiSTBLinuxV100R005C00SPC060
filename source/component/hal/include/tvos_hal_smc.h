/**
 * \file
 * \brief Describes the information about the smc module.
 */

#ifndef  __TVOS_HAL_SMC_H__
#define __TVOS_HAL_SMC_H__

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
/** \addtogroup     HAL_SMC */
/** @{ */  /** <!-- [HAL_SMC] */

/**Module id define.*//** CNcomment:模块ID 定义 */
#define SMC_HARDWARE_MODULE_ID  "smc"

/**Device name define .*//** CNcomment:设备名称定义 */
#define SMC_HARDWARE_SMC0       "smc0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_SMC */
/** @{ */  /** <!-- [HAL_SMC] */

/**SMC active level *//** CNcomment:SMC有效电平 */
typedef enum _SMC_POLARITY_E
{
    SMC_EN_LOW = 0,             /**<Active low*//**<CNcomment:低电平有效 */
    SMC_EN_HIGH,                /**<Active high*//**<CNcomment:高电平有效 */
    SMC_EN_BUTT
} SMC_POLARITY_E;

/**Status of the SMC *//** CNcomment:智能卡状态  */
typedef enum _SMC_STATUS_E
{
    SMC_TERM = 0,               /**<The smc is not initialized.*//**<CNcomment: smc未初始化 */
    SMC_RESET,                  /**<The smc is resetting.*//**<CNcomment: smc正在复位 */
    SMC_INSERTED,               /**<The smc is inserted.*//**<CNcomment: smc已插入 */
    SMC_REMOVED,                /**<The smc is removed.*//**<CNcomment: smc被拔出 */
    SMC_RESET_COMPLETE,         /**<The smc is resetted completely.*//**<CNcomment: smc复位完成 */
    SMC_RESET_TIMEOUT,          /**<The smc reset timeout.*//**<CNcomment: smc复位超时 */
    SMC_RW_COMPLETE,            /**<The smc read/write completely.*//**<CNcomment: smc读写完成 */
    SMC_RW_TIMEOUT,             /**<The smc read/write timeout.*//**<CNcomment: smc读写超时 */
    SMC_POWER_DOWN_COMPLETE,    /**<The smc powerdown complete.*//**<CNcomment: smc下电完成 */
    SMC_POWER_DOWN_TIMEOUT,     /**<The smc powerdown timeout.*//**<CNcomment: smc下电超时 */
    SMC_UNKNOW_ERROR,           /**<The smc unkonwn error.*//**<CNcomment: smc故障 */
    SMC_STATUS_BUTT
} SMC_STATUS_E;

/**smart card protocol *//** CNcomment:智能卡协议类型  */
typedef enum _SMC_PROTOCOL_E
{
    SMC_PROTOCOL_T0 = 0,        /**<7816 T0 protocol*/   /**<CNcomment:7816 T0 协议 */
    SMC_PROTOCOL_T1,            /**<7816 T1 protocol*/   /**<CNcomment:7816 T1 协议 */
    SMC_PROTOCOL_T14 = 14,      /**<7816 T14 protocol*/  /**<CNcomment:7816 T14 协议 */
    SMC_PROTOCOL_BUTT
} SMC_PROTOCOL_E;

/**smart card standard *//** CNcomment:智能卡标准 */
typedef enum _SMC_STANDARD_E
{
    SMC_ISO = 0,
    SMC_N,
    SMC_IRD,
    SMC_TF,
    SMC_DVN,
    SMC_SUV,
    SMC_STANDARD_BUTT
} SMC_STANDARD_E;

/**
\brief smc status calback function.CNcomment:智能卡状态回调函数 CNend
\attention \n
none. CNcomment: 无。CNend
\param[in] handle handle.CNcomment:句柄。CNend
\param[in] status smc status.CNcomment:智能卡状态。CNend
\see \n
none. CNcomment: 无。CNend
*/
 typedef void (*smc_status_callback_pfn)(const HANDLE   smc_handle,
                                            const SMC_STATUS_E status);

/**smc module init param *//** CNcomment:智能卡模块初始化参数 */
typedef struct _SMC_INIT_PARA_S
{
    U32 u32SmcBaud;                   /**< smc baud*//**<CNcomment:smc波特率*/
    U32 u32SmcEtu;                    /**< smc etu*//**<CNcomment:smc etu*/
    U32 u32SmcClk;                    /**< smc clock*//**<CNcomment:smc 时钟*/

    SMC_STANDARD_E  enStandard;       /**< smc standard*//**<CNcomment:smc 标准*/
    SMC_PROTOCOL_E  enProtocol;       /**< smc protocol*//**<CNcomment:smc 协议*/

    SMC_POLARITY_E  enSmcVcc;         /**< active level of the VCCEN signal*//**<CNcomment:VCCEN信号线的有效电平*/
    SMC_POLARITY_E  enSmcDetect;      /**< active level of the DETECT signal*//**<CNcomment:DETECT信号线的有效电平*/
    SMC_POLARITY_E  enSmcRst;         /**< active level of the RESET signal*//**<CNcomment:RESET线的有效电平*/
} SMC_INIT_PARA_S;

/**smc port *//** CNcomment:smc端口 */
typedef enum _SMC_PORT_E
{
    SMC_PORT0 = 0,          /**< smc port 0*//**<CNcomment:smc端口0*/
    SMC_PORT1               /**< smc port 1*//**<CNcomment:smc端口1*/
} SMC_PORT_E;

/**smc open param *//** CNcomment:智能卡打开实例参数 */
typedef struct _SMC_OPEN_PARA_S
{
    SMC_PORT_E enSmcPort;   /**<smc port*//**<CNcomment:smc 端口 */
} SMC_OPEN_PARA_S;

/**smc module term param *//** CNcomment:智能卡模块终止参数 */
typedef struct _SMC_TERM_PARAMS_S
{
    U32  u32Dummy;          /**<Later extended*//**<CNcomment:以后扩展用*/
} SMC_TERM_PARAMS_S;

/**smc open info *//** CNcomment:智能卡信息 */
typedef struct _SMC_INFO_S
{
    SMC_STANDARD_E  enStandard;        /**< smc standard*//**<CNcomment:smc 标准*/
    SMC_PROTOCOL_E  enProtocol;        /**< smc protocol*//**<CNcomment:smc 协议*/
    SMC_STATUS_E    enStatus;          /**< smc status*//**<CNcomment:smc 状态*/
    U32             u32SmcBaud;        /**< smc baud*//**<CNcomment:smc波特率*/
    U32             u32SmcEtu;         /**< smc etu*//**<CNcomment:smc etu*/
    U32             u32SmcClk;         /**< smc clock*//**<CNcomment:smc 时钟*/
} SMC_INFO_S;

#ifdef ANDROID_HAL_MODULE_USED
/**smc module structure (Android require)*/
/**CNcomment:smc模块结构(Android对接要求)*/
typedef struct _SMC_MODULE_S
{
    struct hw_module_t common; /**<Module common structure(Android require) *//**<CNcomment:模块通用结构(Android对接要求 ) */
} SMC_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HAL_SMC*/
/** @{*/  /** <!-- -[HAL_SMC]=*/

/**SMC device structure*//** CNcomment:智能卡设备结构*/
typedef struct _SMC_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:模块通用结构(Android对接要求 ) */
#endif
    /**
    \brief smc module init.CNcomment:智能卡模块初始化 CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] pstInitPara smart card module init param.CNcomment:初始化模块参数 CNend
    \retval ::SUCCESS  success.CNcomment:初始化成功。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_INIT_FAILED  failure.CNcomment:初始化失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*sk_hdi_smc_init)(struct _SMC_DEVICE_S* pstDev, const SMC_INIT_PARA_S* const pstInitPara);

    /**
    \brief open an smc instance.CNcomment:打开智能卡实例 CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] pstOpenPara smart card module open param.CNcomment:打开smc模块的参数。 CNend
    \param[out] pHandle handle.CNcomment:句柄。 CNend
    \retval ::SUCCESS  success.CNcomment:打开实例成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_SMC_ALREADY_OPENED  invalid param.CNcomment:该实例已经打开。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_open)(struct _SMC_DEVICE_S* pstDev, HANDLE* const  pHandle,
                     const SMC_OPEN_PARA_S* const pstOpenPara);

    /**
    \brief close an smc instance.CNcomment:关闭智能卡实例 CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:实例句柄。 CNend
    \retval ::SUCCESS  success.CNcomment:关闭实例成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_close)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle);

    /**
    \brief term smc module.CNcomment:终止智能卡模块 CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] pTermParams handle.CNcomment:终止参数。CNend
    \retval ::SUCCESS  success.CNcomment:终止实例成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_SMC_DEINIT_FAILED  failure.CNcomment:模块终止失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_term)(struct _SMC_DEVICE_S* pstDev, const SMC_TERM_PARAMS_S* const  pstTermParams);

    /**
    \brief get the status of smart card. CNcomment: 获取智能卡状态。CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:句柄。CNend
    \param[out] pstSmcInfo handle.CNcomment:smc设置信息。CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_get_info)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, SMC_INFO_S* pstSmcInfo);

    /**
    \brief  register callback function of smc status. CNcomment:注册卡状态回调函数CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:句柄。CNend
    \param[in]  pfnCallBack  Callback function  CNcomment: 回调函数指针。CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*smc_status_register_callback)(struct _SMC_DEVICE_S* pstDev, const HANDLE   handle,
                                        const smc_status_callback_pfn pfnCallBack);

    /**
    \brief reset smartcard. CNcomment: 复位智能卡。CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:句柄。CNend
    \param[in]  enProtocol  protocol  CNcomment: 复位采用的协议类型CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_reset_card)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, const SMC_PROTOCOL_E enProtocol);

    /**
    \brief transmits data to smart card. CNcomment: 向智能卡发送数据。CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:句柄。CNend
    \param[in]  u32len  length  CNcomment: 发送数据的长度CNend
    \param[in]  pu8Buf  data buffer  CNcomment: 待发送的数据CNend
    \param[out]  pu32SendLen  length of send success  CNcomment: 成功发送数据的长度CNend
    \param[in]  u32Timeout  wait timeout(in ms)  CNcomment:超时时间, 单位是毫秒CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32 (*smc_send)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U32 u32len, U8* pu8Buf,
                    U32* pu32SendLen, U32 u32Timeout);

    /**
    \brief Receives data from smart card. CNcomment: 从智能卡接收数据。CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:句柄。CNend
    \param[in]  u32len  length  CNcomment: 准备接收数据的长度CNend
    \param[in]  pu8Buf  data buffer  CNcomment: 接收到的数据CNend
    \param[out]  pu32ReceiveLen  length of receive success  CNcomment: 实际接收的数据长度CNend
    \param[in]  u32Timeout  wait timeout(in ms)  CNcomment:超时时间, 单位是毫秒CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_receive)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U32 u32Len, U8* pu8Buf,
                        U32* pu32ReceiveLen, U32 u32Timeout);

    /**
    \brief send command to smart card and reciver response. CNcomment: 向对应的卡发送命令和接收应答CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:句柄。CNend
    \param[in]  u32SendLen  length  CNcomment:  发送数据的长度CNend
    \param[in]  pu8SendBuf  send data buffer  CNcomment:  待发送的数据CNend
    \param[out]  pu32ReceiveLen  send data buffer  CNcomment:  准备接收数据的长度CNend
    \param[out]  pu8ReceiveBuf  data buffer  CNcomment: 接收到的数据CNend
    \param[in]  u32Timeout  wait timeout(in ms)  CNcomment:超时时间, 单位是毫秒CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_transfer)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U32 u32SendLen, U8* pu8SendBuf,
                         U32* pu32ReceiveLen, U8* pu8ReceiveBuf, U32 u32Timeout);

    /**
    \brief Obtains the ATR data of an SCI card. CNcomment: 获取SCI卡ATR数据CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:句柄。CNend
    \param[out]  pu8Len  length  CNcomment:  读取ATR 的长度CNend
    \param[out]  pu8Buf   data buffer  CNcomment:  ATR 数据CNend
    \param[in]  u32Timeout  wait timeout(in ms)  CNcomment:超时时间, 单位是毫秒CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_get_atr)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U8* pu8Len, U8* pu8Buf, U32 u32Timeout);

    /**
    \brief adjust the communication parameters according to ATR. CNcomment:根据ATR 调整通讯参数CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:句柄。CNend
    \param[in]  pu8Buf   data buffer  CNcomment:  ATR 数据CNend
    \param[in]  pu8Len  length  CNcomment:  ATR 的长度CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_set_para_from_atr)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle, U8* pu8Buf, U32 u32Len);

    /**
    \brief get handle of an card. CNcomment:获取智能卡句柄.CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[out] handle handle.CNcomment:句柄。CNend
    \param[in]  enSmcPort  port  CNcomment:  端口CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_NOT_OPEN  invalid param.CNcomment:实例没有打开。CNend
    \retval ::ERROR_SMC_INVALID_PARAM  invalid param.CNcomment:参数错误。CNend
    \retval ::ERROR_SMC_NULL_PTR  null ptr.CNcomment:空指针。CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_get_active)(struct _SMC_DEVICE_S* pstDev, HANDLE* const pHandle, SMC_PORT_E enSmcPort);

    /**
    \brief remove the residual data. CNcomment: 清除底层BUFF中的残余数据.CNend
    \attention \n
    none. CNcomment: 无。CNend
    \param[in] handle handle.CNcomment:句柄。CNend
    \retval ::SUCCESS  success.CNcomment:成功。CNend
    \retval ::ERROR_SMC_NOT_INIT  not init.CNcomment:没有初始化。CNend
    \retval ::ERROR_SMC_INVALID_HANDLE  invalid param.CNcomment:无效句柄。 CNend
    \retval ::FAILURE  failure.CNcomment:失败。 CNend
    \see \n
    none. CNcomment: 无。CNend
    */
    S32  (*smc_flush)(struct _SMC_DEVICE_S* pstDev, const HANDLE handle);

} SMC_DEVICE_S;

/**
 \brief direct get smc device api, for linux and android.CNcomment:获取智能卡设备的接口, Linux和Android平台都可以使用 CNend
 \attention \n
get smc device api, for linux and andorid.
CNcomment:获取智能卡设备接口，linux和android平台都可以使用. CNend
 \retval  smc device pointer when success.CNcomment:成功返回smc设备指针。CNend
 \retval ::NULL when failure.CNcomment:失败返回空指针 CNend
 \see \n
::SMC_DEVICE_S

 \par example
 */
SMC_DEVICE_S* getSmcDevice();

/**
\brief  Open HAL smc module device.CNcomment: 打开HAL smc系统模块设备 CNend
\attention \n
Open HAL smc module device(for compatible Android HAL).
CNcomment:打开HAL smc系统模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice smc device structure.CNcomment:系统smc设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::SMC_DEVICE_S

\par example
*/
static inline int smc_open(const struct hw_module_t* pstModule, SMC_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, SMC_HARDWARE_SMC0, (hw_device_t**)ppstDevice);
#else
    *ppstDevice = getSmcDevice();
    return SUCCESS;
#endif
}

/**
\brief  Close HAL smc module device.CNcomment:关闭HAL smc模块设备。CNend
\attention \n
Close HAL smc module device(for compatible Android HAL).
CNcomment:关闭HAL smc模块设备 (为兼容Android HAL结构)。CNend
\param[in] pstDevice smc device structure.CNcomment:系统smc设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 。CNend
\see \n
::SMC_DEVICE_S

\par example
*/
static inline int smc_close(SMC_DEVICE_S* pstDevice)
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

#endif /* __TVOS_HAL_SMC_H__ */
