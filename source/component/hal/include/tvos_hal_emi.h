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
/** CNcomment:ģ��ID ���� */
#define EMI_HARDWARE_MODULE_ID "emi"

/**Device name define .*/
/** CNcomment:�豸���ƶ��� */
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

/**emi init param *//** CNcomment:EMIģ���ʼ������ */
typedef struct _EMI_INIT_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:����*/
} EMI_INIT_PARAMS_S;

/**emi deinit param *//** CNcomment:ģ��ȥ��ʼ������  */
typedef struct _EMI_TERM_PARAMS_S
{
    U32 u32Dummy; /**<Reserve *//**<CNcomment:����*/
} EMI_TERM_PARAMS_S;

/**emi create param *//** CNcomment:EMI�������� */
typedef struct _EMI_CREATE_PARAMS_S
{
    EMI_ID_E enEmiId; /**<Emi ID *//**<CNcomment:EMIID*/
} EMI_CREATE_PARAMS_S;

/**emi destroy param *//** CNcomment:EMI���ٲ��� */
typedef struct _EMI_DESTORY_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:����*/
} EMI_DESTORY_PARAMS_S;

#ifdef ANDROID_HAL_MODULE_USED
/**EMI module structure(Android require)*/
/**CNcomment:EMIģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _EMI_MODULE_S
{
    struct hw_module_t stCommon;
} EMI_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API declaration *****************************/
/** \addtogroup      HAL_EMI */
/** @{ */  /** <!-- [HAL_EMI] */

/**Emi device structure*//** CNcomment:EMI�豸�ṹ*/
typedef struct _EMI_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:ģ��ͨ�ýṹ(Android�Խ�Ҫ�� ) */
#endif

    /**
    \brief Emi  init.CNcomment:EMI ģ���ʼ�� CNend
    \attention \n
    Lower layer emi module init and alloc necessary reemi,  repeat call return success.
    CNcomment:�ײ�EMI ģ���ʼ���������Ҫ����Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstInitParams system module init param.CNcomment:��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_EMI_INIT_FAILED  Lower layer emi module init error.CNcomment:�ײ�EMI ģ���ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
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
    \brief Emi  deinit.CNcomment:EMI ģ��ȥ��ʼ�� CNend
    \attention \n
    Lower layer emi module deinit and release occupied reemi,  repeat call return success.
    CNcomment:�ײ�EMI ģ��ȥ��ʼ�����ͷ�ռ�õ���Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstTermParams enc module deinit param.CNcomment:ȥ��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_EMI_DEINIT_FAILED  Lower layer emi module deinit error.CNcomment:�ײ�EMI ģ��ȥ��ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
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
    \brief Create emi.CNcomment:����Emi CNend
    \attention \n
    \param[in] pstCreateParams create param.CNcomment:�������� CNend
    \param[out] pEmiHandle generated handle.CNcomment:���ɵľ�� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_CREATE_PARAMS_S

    \par example
    */
    S32 (* emi_create)(struct _EMI_DEVICE_S* pstDev, HANDLE * const pEmiHandle, EMI_CREATE_PARAMS_S * const pstCreateParams);

    /**
    \brief destory emi.CNcomment:����EMI CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI��� CNend
    \param[in] pstDestoryParams destory param.CNcomment:���ٲ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_destory)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, EMI_DESTORY_PARAMS_S * const pstDestoryParams);


    /**
    \brief set DDR Enable emi.CNcomment:���� DDR ���� CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI��� CNend
    \param[in] bEnable DDR Enable.CNcomment:DDR չƵ���� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */

    S32 (* emi_set_ddr_spread_enable)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, BOOL bEnable);

    /**
    \brief set ddr spread ratio.CNcomment:���� ddr չƵ��  CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI��� CNend
    \param[in] u32Ratio destory param, rang[0,100].CNcomment:���ٲ��� , rang[0,100]CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_ddr_spread_ratio)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, U32 u32Ratio);

    /**
    \brief set ddr spread freq.CNcomment:���� DDR չƵƵ�� CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI��� CNend
    \param[in] u32Freq ddr spread freq, rang[0,100].CNcomment:DDR չƵƵ��, rang[0,100] CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_ddr_spread_freq)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, U32 u32Freq);

    /**
    \brief set Gmac Enable emi.CNcomment:���� DDR ���� CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI��� CNend
    \param[in] bEnable Gmac Enable.CNcomment:Gmac ���� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_gmac_enable)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, BOOL bEnable);

    /**
    \brief set Gmac spread Enable emi.CNcomment:���� Gmac չƵ���� CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI��� CNend
    \param[in] bEnable Gmac spread Enable.CNcomment:GmacչƵ ���� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_gmac_spread_enable)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, BOOL bEnable);

    /**
    \brief set Gmac Spread ratio.CNcomment:���� Gmac չƵ�� CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI��� CNend
    \param[in] u32Ratio Gmac Spread ratio, rang[0,100].CNcomment:Gmac չƵ�� , rang[0,100]CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_gmac_spread_ratio)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, U32 u32Ratio);

    /**
    \brief set Gmac Spread freq.CNcomment:���� Gmac չƵƵ�� CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI��� CNend
    \param[in] u32Freq Gmac Spread freq, rang[0,100].CNcomment:Gmac չƵƵ��, rang[0,100] CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_set_gmac_spread_freq)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, U32 u32Freq);

    /**
    \brief set CI Enable emi.CNcomment:���� CI ���� CNend
    \attention \n
    \param[in] hEmi emi handle.CNcomment:EMI��� CNend
    \param[in] bEnable CI Enable.CNcomment:CI ���� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_EMI_OP_FAILED emi operate failed.CNcomment:EMI�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::EMI_DESTORY_PARAMS_S

    \par example
    */
    S32 (* emi_ci_enable)(struct _EMI_DEVICE_S* pstDev, const HANDLE hEmi, BOOL bEnable);

} EMI_DEVICE_S;


/**
\brief direct get EMI device api, for linux and android.CNcomment:��ȡEMI�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get EMI device api��for linux and andorid.
CNcomment:��ȡEMI�豸��linux��androidƽ̨������ʹ��. CNend
\retval  EMI device pointer when success.CNcomment:�ɹ�����EMI�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::EMI_DEVICE_S

\par example
*/
EMI_DEVICE_S* getEmiDevice();

/**
\brief Open HAL EMI module device.CNcomment:��HAL EMIģ���豸 CNend
\attention \n
Open HAL EMI module device(for compatible Android HAL).
CNcomment:��HAL EMIģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice source device structure.CNcomment:EMI�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other android system error.CNcomment:����Androidϵͳ���� CNend
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
\brief Close HAL EMI module device.CNcomment:�ر�HAL EMIģ���豸 CNend
\attention \n
Close HAL EMI module device(for compatible Android HAL).
CNcomment:�ر�HAL EMIģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice source device structure.CNcomment:EMI�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other android system error.CNcomment:����Androidϵͳ���� CNend
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


