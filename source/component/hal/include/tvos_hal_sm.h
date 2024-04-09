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
/**CNcomment:����SM ģ������ */
#define SM_HARDWARE_MODULE_ID "session_manager"

/**Defines the sm module name*/
/**CNcomment:����SM �豸���� */
#define SM_HARDWARE_SM0       "sm0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HAL_SM */
/** @{ */  /** <!-- [HAL_SM] */

/**Struct of SM module init parameter*/
/**CNcomment:SM ģ���ʼ������*/
typedef struct _SM_INIT_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} SM_INIT_PARAMS_S;

/**Struct of SM module terminate parameter*/
/**CNcomment:SM ģ����ֹ����  */
typedef struct _SM_TERM_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} SM_TERM_PARAMS_S;

/**Struct of SM module create parameter*/
/**CNcomment:SM ģ�鴴������*/
typedef struct _SM_CREATE_PARAMS_S
{
    U32 u32SessionID;
} SM_CREATE_PARAMS_S;

/**Struct of SM destroy parameter*/
/**CNcomment:�ر�SMʵ������  */
typedef struct _SM_DESTROY_PARAMS_S
{
    U32 u32Dummy;              /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} SM_DESTROY_PARAMS_S;

/** the type of module */
/**CNcomment: ģ������ */
typedef enum
{
    SM_MODULE_AV = 0,
    SM_MODULE_BUTT
} SM_MODULE_TYPE_E;

/**Defines the information about module resource*/
/**CNcomment: ������Դģ����Ϣ*/
typedef struct
{
    HANDLE hHandle; /**<Module handler *//**<CNcomment: ģ���� */
    U32 u32Reserve; /**<Resvered*//**<CNcomment: �Ժ���չ�� */
} SM_MODULE_RESOURCE_S;

#ifdef ANDROID_HAL_MODULE_USED
/** SM module structure(Android require)*/
/**CNcomment:SMģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _SM_MODULE_S
{
    struct hw_module_t stCommon;
} SM_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HAL_SM */
/** @{ */  /** <!-- [HAL_SM] */

/**SM device structure*//** CNcomment:�ػ������豸�ṹ */
typedef struct _SM_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief SM module init.CNcomment:SM ģ���ʼ��.CNend
    \attention \n
    Other functions cannot be useful before init, return SUCCESS when repeated called.
    CNcomment: �ڳ�ʼ��֮ǰ, ����������������ȷ����, �ظ�����init �ӿ�,����SUCCESS. CNend
    \param[in] pstInitParams SM module init param.CNcomment:��ʼ��ģ����� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SM_INIT_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*sm_init)(struct _SM_DEVICE_S* pstDev, const SM_INIT_PARAMS_S* pstInitParams);

    /**
    \brief Terminate SM module.CNcomment:ģ����ֹ.CNend
    \attention \n
    Return SUCCESS when repeated called.
    CNcomment: �ظ�term ����SUCCESS. CNend
    \param[in] pstTermParams Terminate param.CNcomment:��ֹ���� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NOT_INITED  Module has not been inited.CNcomment:ģ��δ��ʼ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SM_TERM_PARAMS_S
    */
    S32 (*sm_term)(struct _SM_DEVICE_S* pstDev, const SM_TERM_PARAMS_S* pstTermParams);

    /**
    \brief Create a SM instance.CNcomment:����һ���ػ�����ʵ�� .CNend
    \attention \n
    None
    \param[out] phSM Return SM handle.CNcomment:����SM��� CNend
    \param[in] pstCreateParams Create param.CNcomment:�������� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SM_CREATE_PARAMS_S
    */
    S32 (*sm_create)(struct _SM_DEVICE_S* pstDev, HANDLE* phSM, const SM_CREATE_PARAMS_S* pstCreateParams);

    /**
    \brief Destroy a SM instance.CNcomment:����һ��ʵ��.CNend
    \attention \n
    None
    \param[in] hSM SM handle.CNcomment:SM��� CNend
    \param[in] pstDestroyParams Destroy param.CNcomment:���ٲ��� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SM_DESTROY_PARAMS_S

    \par example
    \code
    \endcode
    */
    S32 (*sm_destroy)(struct _SM_DEVICE_S* pstDev, const HANDLE hSM, const SM_DESTROY_PARAMS_S* pstDestroyParams);

    /**
    \brief Add the resouce to the SM module. CNcomment:�����Դ���ػ�����ģ�� CNend
    \attention \n
    None
    \param[in] hSM SM handle.CNcomment:SM��� CNend
    \param[in] enModuleType resource module type.CNcomment:��Դģ������ CNend
    \param[in] pstResource  resource module param.CNcomment:��Դ��Ϣ���� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SM_MODULE_RESOURCE_S
    */
    S32 (*sm_add_resource)(struct _SM_DEVICE_S* pstDev, const HANDLE hSM, SM_MODULE_TYPE_E enModuleType, SM_MODULE_RESOURCE_S* pstResource);

    /**
    \brief Delete the resouce from the SM module. CNcomment:�ӻػ�����ģ��ɾ����Դ CNend
    \attention \n
    None
    \param[in] hSM SM handle.CNcomment:SM��� CNend
    \param[in] enModuleType resource module type.CNcomment:��Դģ������ CNend
    \param[in] pstResource  resource module param.CNcomment:��Դ��Ϣ���� CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::SM_MODULE_RESOURCE_S
    */
    S32 (*sm_del_resource)(struct _SM_DEVICE_S* pstDev, const HANDLE hSM, SM_MODULE_TYPE_E enModuleType, SM_MODULE_RESOURCE_S* pstResource);

    /**
    \brief Get the SM handle by session id. CNcomment:���ݻػ�id���һػ�����ģ���� CNend
    \attention \n
    None
    \param[out] phSM Return SM handle.CNcomment:����SM��� CNend
    \param[in] u32SessionID session id.CNcomment:�ػ�ID CNend

    \retval ::SUCCESS CNcomment:�ɹ� CNend
    \retval ::ERROR_NULL_PTR Parameter invalid .CNcomment:��ָ��CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    */
    S32 (*sm_get_handle_by_sid)(struct _SM_DEVICE_S* pstDev, HANDLE* phSM, U32 u32SessionID);

} SM_DEVICE_S;

/**
\brief direct get SM device api, for linux and android.CNcomment:��ȡ��HDMI �豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get SM device api��for linux and andorid.
CNcomment:��ȡSM �豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
\retval  SM device pointer when success.CNcomment:�ɹ�����SM�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::SM_DEVICE_S

\par example
*/
SM_DEVICE_S* getSMDevice();

/**
\brief  Open HAL SM module device.CNcomment:��HAL HDMIģ���豸CNend
\attention \n
Open HAL SM module device(for compatible Android HAL).
CNcomment:��HAL SM ģ���豸(Ϊ����android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice SM device structure.CNcomment:SM �豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other system error.CNcomment:����SM ���� CNend
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
\brief Close HAL SM module device.CNcomment:�ر�HAL  SM ģ���豸 CNend
\attention \n
Close HAL SM module device(for compatible android HAL).
CNcomment:�ر�HAL SM ģ���豸(Ϊ����android HAL�ṹ). CNend
\param[in] pstDevice SM device structure.CNcomment:SM �豸���ݽṹ CNend
\retval 0  SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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

