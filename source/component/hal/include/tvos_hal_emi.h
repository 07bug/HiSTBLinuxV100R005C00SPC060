 /**
 * \file
 * \brief Describes the information about the EMI module.
 */

#ifndef __TVOS_HAL_EMI_H__
#define __TVOS_HAL_EMI_H__

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
/** \addtogroup      HAL_EMI */
/** @{ */  /** <!-- [HAL_EMI] */
/*****************************************************************************/

/**Module id define.*/
/** CNcomment:模块ID 定义 */
#define EMI_HARDWARE_MODULE_ID "emi"

/**Device name define .*/
/** CNcomment:设备名称定义 */
#define EMI_HARDWARE_EMI0      "emi0"

/** @} */  /*! <!-- Macro Definition End */


/*************************** Structure Definition ****************************/
/** \addtogroup     HAL_EMI */
/** @{ */  /** <!-- [HAL_EMI] */

/**EMI ID *//** CNcomment:EMI ID */
typedef enum _EMI_ID_E
{
    EMI_ID_0 = 0,
    EMI_ID_BUTT
} EMI_ID_E;

/**emi init param *//** CNcomment:EMI模块初始化参数 */
typedef struct _EMI_INIT_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:保留*/
} EMI_INIT_PARAMS_S;

/**emi deinit param *//** CNcomment:模块去初始化参数  */
typedef struct _EMI_TERM_PARAMS_S
{
    U32 u32Dummy; /**<Reserve *//**<CNcomment:保留*/
} EMI_TERM_PARAMS_S;

/**emi create param *//** CNcomment:EMI创建参数 */
typedef struct _EMI_CREATE_PARAMS_S
{
    EMI_ID_E enEmiId; /**<Emi ID *//**<CNcomment:EMIID*/
} EMI_CREATE_PARAMS_S;

/**emi destroy param *//** CNcomment:EMI销毁参数 */
typedef struct _EMI_DESTORY_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:保留*/
} EMI_DESTORY_PARAMS_S;

#ifdef ANDROID_HAL_MODULE_USED
/**EMI module structure(Android require)*/
/**CNcomment:EMI模块结构(Android对接要求) */
typedef struct _EMI_MODULE_S
{
    struct hw_module_t stCommon;
} EMI_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API declaration *****************************/
/** \addtogroup      HAL_EMI */
/** @{ */  /** <!-- [HAL_EMI] */

/**Emi device structure*//** CNcomment:EMI设备结构*/
typedef struct _EMI_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:模块通用结构(Android对接要求 ) */
#endif

    /**
    \brief Emi  init.CNcomment:EMI 模块初始化 CNend
    \attention \n
    Lower layer emi module init and alloc necessary reemi,  repeat call return success.
    CNcomment:底层EMI 模块初始化及分配必要的资源, 本函数重复调用返回成功. CNend
    \param[in] pstInitParams system module init param.CNcomment:初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_EMI_INIT_FAILED  Lower layer emi module init error.CNcomment:底层EMI 模块初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_INIT_PARAMS_S

    \par example
    \code
    EMI_INIT_PARAMS_S stInitParam;
    memset(&stInitParam, 0x0, sizeof(EMI_INIT_PARAMS_S));
    if (SUCCESS != emi_init(pstDev, (const EMI_INIT_PARAMS_S * const)&stInitParam))
    {
        return FAILUE;
    }

    \endcode
    */
    S32 (*emi_init)(struct _EMI_DEVICE_S* pstDev, const EMI_INIT_PARAMS_S * const pstInitParams);

    /**
    \brief Emi  deinit.CNcomment:EMI 模块去初始化 CNend
    \attention \n
    Lower layer emi module deinit and release occupied reemi,  repeat call return success.
    CNcomment:底层EMI 模块去初始化及释放占用的资源, 本函数重复调用返回成功. CNend
    \param[in] pstTermParams enc module deinit param.CNcomment:去初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_EMI_DEINIT_FAILED  Lower layer emi module deinit error.CNcomment:底层EMI 模块去初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_TERM_PARAMS_S

    \par example
    \code
    EMI_TERM_PARAMS_S stDeInitParam;
    memset(&stDeInitParam, 0x0, sizeof(EMI_TERM_PARAMS_S));
    if (SUCCESS != emi_term(pstDev, (const EMI_TERM_PARAMS_S * const)&stDeInitParam))
    {
        return FAILUE;
    }

    \endcode
    */
    S32 (*emi_term)(struct _EMI_DEVICE_S* pstDev, const EMI_TERM_PARAMS_S *const  pstTermParams);

    /**
    \brief Create emi.CNcomment:创建Emi CNend
    \attention \n
    \param[in] pstCreateParams create param.CNcomment:创建参数 CNend
    \param[out] pEmiHandle generated handle.CNcomment:生成的句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_CREATE_PARAMS_S

    \par example
    */
    S32 (* emi_create)(struct _EMI_DEVICE_S* pstDev, HANDLE * const pEmiHandle, EMI_CREATE_PARAMS_S * const pstCreateParams);

    /**
    \brief destory emi.CNcomment:销毁EMI CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI句柄 CNend
    \param[in] pstDestoryParams destory param.CNcomment:销毁参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_destory)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, EMI_DESTORY_PARAMS_S * const pstDestoryParams);


    /**
    \brief set DDR Enable emi.CNcomment:设置 DDR 开关 CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI句柄 CNend
    \param[in] bEnable DDR Enable.CNcomment:DDR 展频开关 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */

    S32 (* emi_set_ddr_spread_enable)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, BOOL bEnable);

    /**
    \brief set ddr spread ratio.CNcomment:设置 ddr 展频比  CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI句柄 CNend
    \param[in] u32Ratio destory param, rang[0,100].CNcomment:销毁参数 , rang[0,100]CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_ddr_spread_ratio)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, U32 u32Ratio);

    /**
    \brief set ddr spread freq.CNcomment:设置 DDR 展频频率 CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI句柄 CNend
    \param[in] u32Freq ddr spread freq, rang[0,100].CNcomment:DDR 展频频率, rang[0,100] CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_ddr_spread_freq)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, U32 u32Freq);

    /**
    \brief set Gmac Enable emi.CNcomment:设置 DDR 开关 CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI句柄 CNend
    \param[in] bEnable Gmac Enable.CNcomment:Gmac 开关 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_gmac_enable)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, BOOL bEnable);

    /**
    \brief set Gmac spread Enable emi.CNcomment:设置 Gmac 展频开关 CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI句柄 CNend
    \param[in] bEnable Gmac spread Enable.CNcomment:Gmac展频 开关 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_gmac_spread_enable)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, BOOL bEnable);

    /**
    \brief set Gmac Spread ratio.CNcomment:设置 Gmac 展频比 CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI句柄 CNend
    \param[in] u32Ratio Gmac Spread ratio, rang[0,100].CNcomment:Gmac 展频比 , rang[0,100]CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_gmac_spread_ratio)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, U32 u32Ratio);

    /**
    \brief set Gmac Spread freq.CNcomment:设置 Gmac 展频频率 CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI句柄 CNend
    \param[in] u32Freq Gmac Spread freq, rang[0,100].CNcomment:Gmac 展频频率, rang[0,100] CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_gmac_spread_freq)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, U32 u32Freq);

    /**
    \brief set CI Enable emi.CNcomment:设置 CI 开关 CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI句柄 CNend
    \param[in] bEnable CI Enable.CNcomment:CI 开关 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_ci_enable)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, BOOL bEnable);

} EMI_DEVICE_S;


/**
\brief direct get EMI device api, for linux and android.CNcomment:获取EMI设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get EMI device api，for linux and andorid.
CNcomment:获取EMI设备，linux和android平台都可以使用. CNend
\retval  EMI device pointer when success.CNcomment:成功返回EMI设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::EMI_DEVICE_S

\par example
*/
EMI_DEVICE_S* getEmiDevice();

/**
\brief Open HAL EMI module device.CNcomment:打开HAL EMI模块设备 CNend
\attention \n
Open HAL EMI module device(for compatible Android HAL).
CNcomment:打开HAL EMI模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice source device structure.CNcomment:EMI设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other android system error.CNcomment:其它Android系统错误 CNend
\see \n
::EMI_DEVICE_S

\par example
*/
static inline int emi_open(const struct hw_module_t* pstModule, EMI_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, EMI_HARDWARE_EMI0,  (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getEmiDevice();
    return SUCCESS;
#endif
    return SUCCESS;
}

/**
\brief Close HAL EMI module device.CNcomment:关闭HAL EMI模块设备 CNend
\attention \n
Close HAL EMI module device(for compatible Android HAL).
CNcomment:关闭HAL EMI模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice source device structure.CNcomment:EMI设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other android system error.CNcomment:其它Android系统错误 CNend
\see \n
::EMI_DEVICE_S

\par example
*/
static inline int emi_close(EMI_DEVICE_S* pstDevice)
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

#endif /* __TVOS_HAL_EMI */


