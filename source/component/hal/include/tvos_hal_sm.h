/**
 * \file
 * \brief Describes the information about the hdmi module.
 */

#ifndef __TVOS_HAL_SM_H__
#define __TVOS_HAL_SM_H__

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
/** \addtogroup      HAL_SM */
/** @{ */  /** <!-- [HAL_SM] */
/*****************************************************************************/
/**Defines the SM module name*/
/**CNcomment:定义SM 模块名称 */
#define SM_HARDWARE_MODULE_ID "session_manager"

/**Defines the sm module name*/
/**CNcomment:定义SM 设备名称 */
#define SM_HARDWARE_SM0       "sm0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HAL_SM */
/** @{ */  /** <!-- [HAL_SM] */

/**Struct of SM module init parameter*/
/**CNcomment:SM 模块初始化参数*/
typedef struct _SM_INIT_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: 以后扩展用 */
} SM_INIT_PARAMS_S;

/**Struct of SM module terminate parameter*/
/**CNcomment:SM 模块终止参数  */
typedef struct _SM_TERM_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: 以后扩展用 */
} SM_TERM_PARAMS_S;

/**Struct of SM module create parameter*/
/**CNcomment:SM 模块创建参数*/
typedef struct _SM_CREATE_PARAMS_S
{
    U32 u32SessionID;
} SM_CREATE_PARAMS_S;

/**Struct of SM destroy parameter*/
/**CNcomment:关闭SM实例参数  */
typedef struct _SM_DESTROY_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: 以后扩展用 */
} SM_DESTROY_PARAMS_S;

/** the type of module */
/**CNcomment: 模块类型 */
typedef enum
{
    SM_MODULE_AV = 0,
    SM_MODULE_BUTT
} SM_MODULE_TYPE_E;

/**Defines the information about module resource*/
/**CNcomment: 定义资源模块信息*/
typedef struct
{
    HANDLE hHandle; /**<Module handler *//**<CNcomment: 模块句柄 */
    U32 u32Reserve; /**<Resvered*//**<CNcomment: 以后扩展用 */
} SM_MODULE_RESOURCE_S;

#ifdef ANDROID_HAL_MODULE_USED
/** SM module structure(Android require)*/
/**CNcomment:SM模块结构(Android对接要求) */
typedef struct _SM_MODULE_S
{
    struct hw_module_t stCommon;
} SM_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HAL_SM */
/** @{ */  /** <!-- [HAL_SM] */

/**SM device structure*//** CNcomment:回话管理设备结构 */
typedef struct _SM_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief SM module init.CNcomment:SM 模块初始化.CNend
    \attention \n
    Other functions cannot be useful before init, return SUCCESS when repeated called.
    CNcomment: 在初始化之前, 其他函数都不能正确运行, 重复调用init 接口,返回SUCCESS. CNend
    \param[in] pstInitParams SM module init param.CNcomment:初始化模块参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SM_INIT_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*sm_init)(struct _SM_DEVICE_S* pstDev, const SM_INIT_PARAMS_S* pstInitParams);

    /**
    \brief Terminate SM module.CNcomment:模块终止.CNend
    \attention \n
    Return SUCCESS when repeated called.
    CNcomment: 重复term 返回SUCCESS. CNend
    \param[in] pstTermParams Terminate param.CNcomment:终止参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:模块未初始化CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SM_TERM_PARAMS_S
    */
    S32 (*sm_term)(struct _SM_DEVICE_S* pstDev, const SM_TERM_PARAMS_S* pstTermParams);

    /**
    \brief Create a SM instance.CNcomment:创建一个回话管理实例 .CNend
    \attention \n
    None
    \param[out] phSM Return SM handle.CNcomment:返回SM句柄 CNend
    \param[in] pstCreateParams Create param.CNcomment:创建参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SM_CREATE_PARAMS_S
    */
    S32 (*sm_create)(struct _SM_DEVICE_S* pstDev, HANDLE* phSM, const SM_CREATE_PARAMS_S* pstCreateParams);

    /**
    \brief Destroy a SM instance.CNcomment:销毁一个实例.CNend
    \attention \n
    None
    \param[in] hSM SM handle.CNcomment:SM句柄 CNend
    \param[in] pstDestroyParams Destroy param.CNcomment:销毁参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SM_DESTROY_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*sm_destroy)(struct _SM_DEVICE_S* pstDev, const HANDLE hSM, const SM_DESTROY_PARAMS_S* pstDestroyParams);

    /**
    \brief Add the resouce to the SM module. CNcomment:添加资源到回话管理模块 CNend
    \attention \n
    None
    \param[in] hSM SM handle.CNcomment:SM句柄 CNend
    \param[in] enModuleType resource module type.CNcomment:资源模块类型 CNend
    \param[in] pstResource  resource module param.CNcomment:资源信息参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SM_MODULE_RESOURCE_S
    */
    S32 (*sm_add_resource)(struct _SM_DEVICE_S* pstDev, const HANDLE hSM, SM_MODULE_TYPE_E enModuleType, SM_MODULE_RESOURCE_S* pstResource);

    /**
    \brief Delete the resouce from the SM module. CNcomment:从回话管理模块删除资源 CNend
    \attention \n
    None
    \param[in] hSM SM handle.CNcomment:SM句柄 CNend
    \param[in] enModuleType resource module type.CNcomment:资源模块类型 CNend
    \param[in] pstResource  resource module param.CNcomment:资源信息参数 CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::SM_MODULE_RESOURCE_S
    */
    S32 (*sm_del_resource)(struct _SM_DEVICE_S* pstDev, const HANDLE hSM, SM_MODULE_TYPE_E enModuleType, SM_MODULE_RESOURCE_S* pstResource);

    /**
    \brief Get the SM handle by session id. CNcomment:根据回话id查找回话管理模块句柄 CNend
    \attention \n
    None
    \param[out] phSM Return SM handle.CNcomment:返回SM句柄 CNend
    \param[in] u32SessionID session id.CNcomment:回话ID CNend

    \retval ::SUCCESS CNcomment:成功 CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:空指针CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    */
    S32 (*sm_get_handle_by_sid)(struct _SM_DEVICE_S* pstDev, HANDLE* phSM, U32 u32SessionID);

} SM_DEVICE_S;

/**
\brief direct get SM device api, for linux and android.CNcomment:获取视HDMI 设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get SM device api，for linux and andorid.
CNcomment:获取SM 设备接口，linux和android平台都可以使用. CNend
\retval  SM device pointer when success.CNcomment:成功返回SM设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::SM_DEVICE_S

\par example
*/
SM_DEVICE_S* getSMDevice();

/**
\brief  Open HAL SM module device.CNcomment:打开HAL HDMI模块设备CNend
\attention \n
Open HAL SM module device(for compatible Android HAL).
CNcomment:打开HAL SM 模块设备(为兼容android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice SM device structure.CNcomment:SM 设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other system error.CNcomment:其它SM 错误 CNend
\see \n
::SM_DEVICE_S

\par example
*/
static inline int sm_open(const struct hw_module_t* pstModule, SM_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, SM_HARDWARE_SM0, (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getSMDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL SM module device.CNcomment:关闭HAL  SM 模块设备 CNend
\attention \n
Close HAL SM module device(for compatible android HAL).
CNcomment:关闭HAL SM 模块设备(为兼容android HAL结构). CNend
\param[in] pstDevice SM device structure.CNcomment:SM 设备数据结构 CNend
\retval 0  SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::SM_DEVICE_S

\par example
*/
static inline int sm_close(SM_DEVICE_S* pstDevice)
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

#endif /*__TVOS_HAL_SM_H__*/

