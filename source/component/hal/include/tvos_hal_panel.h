 /**
 * \file
 * \brief Describes the information about the PANEL module.
 */

#ifndef __TVOS_HAL_PANEL_H__
#define __TVOS_HAL_PANEL_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include "tvos_hal_type.h"

#ifdef ANDROID_HAL_MODULE_USED
#include "hardware.h"
#else
#include "tvos_hal_linux_adapter.h"
#endif

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

/*************************** Macro Definition ****************************/
/** \addtogroup      HAL_PANEL */
/** @{ */  /** <!-- [HAL_PANEL] */
/*****************************************************************************/

/**Module id define.*//** CNcomment:ģ��ID ���� */
#define PANEL_HARDWARE_MODULE_ID    "panel"

/**Device name define .*//** CNcomment:�豸���ƶ��� */
#define PANEL_HARDWARE_PANEL0       "panel0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HAL_PANEL */
/** @{ */  /** <!-- [HAL_PANEL] */

/**PANEL ID *//** CNcomment:PANEL ID */
typedef enum _PANEL_ID_E
{
    PANEL_ID_0 = 0,
    PANEL_ID_BUTT
} PANEL_ID_E;

/**panel init param *//** CNcomment:PANELģ���ʼ������ */
typedef struct _PANEL_INIT_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:����*/
} PANEL_INIT_PARAMS_S;

/**panel deinit param *//** CNcomment:ģ��ȥ��ʼ������  */
typedef struct _PANEL_TERM_PARAMS_S
{
    U32 u32Dummy; /**<Reserve *//**<CNcomment:����*/
} PANEL_TERM_PARAMS_S;

/**panel create param *//** CNcomment:PANEL�������� */
typedef struct _PANEL_CREATE_PARAMS_S
{
    PANEL_ID_E enPanelId; /**<Panel ID *//**<CNcomment:PANELID*/
} PANEL_CREATE_PARAMS_S;

/**panel destroy param *//** CNcomment:PANEL���ٲ��� */
typedef struct _PANEL_DESTORY_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:����*/
} PANEL_DESTORY_PARAMS_S;


/**panel aspect *//**CNcomment:panel��ʾ�ı���ģʽ*/
typedef enum _PANEL_ASPECT_E
{
    PANEL_ASPECT_4_3 = 0,    /**<aspect is 4:3 *//**CNcomment: 4:3 ��ʾ */
    PANEL_ASPECT_16_9,       /**<aspect is 16:9 *//**CNcomment: 16:9 ��ʾ */
    PANEL_ASPECT_14_9,       /**<aspect is 14:9 *//**CNcomment: 14:9 ��ʾ */
    PANEL_ASPECT_21_9,       /**<aspect is 21:9 *//**CNcomment: 21:9 ��ʾ */
    PANEL_ASPECT_16_10,      /**<aspect is 16:10 *//**CNcomment: 16:10 ��ʾ */

    PANEL_ASPECT_BUTT,       /**<Invalid value*//**<CNcomment:�Ƿ��߽�ֵ*/
}PANEL_ASPECT_E;


/**panel attr *//**CNcomment:panel����*/
typedef struct _PANEL_ATTR_S
{
    U32                     u32Width;   /**<Width *//**CNcomment: Panel�Ŀ�� */
    U32                     u32Height;  /**<Height *//**CNcomment: Panel�ĸ߶� */
    PANEL_ASPECT_E          enAspect;   /**<aspect *//**CNcomment: Panel�ı���ģʽ */
}PANEL_ATTR_S;



#ifdef ANDROID_HAL_MODULE_USED
/**Panel module structure(Android require)*/
/**CNcomment:Panelģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _PANEL_MODULE_S
{
    struct hw_module_t stCommon;
} PANEL_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/*************************** API declaration ****************************/
/** \addtogroup      HAL_PANEL */
/** @{ */  /** <!-- [HAL_PANEL] */

/**Panel device structure*//** CNcomment:���豸�ṹ*/
typedef struct _PANEL_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:ģ��ͨ�ýṹ(Android�Խ�Ҫ�� ) */
#endif

    /**
    \brief Panel  init.CNcomment:��ģ���ʼ�� CNend
    \attention \n
    Lower layer panel module init and alloc necessary repanel,  repeat call return success.
    CNcomment:�ײ���ģ���ʼ���������Ҫ����Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstInitParams system module init param.CNcomment:��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_PANEL_INIT_FAILED  Lower layer panel module init error.CNcomment:�ײ���ģ���ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::PANEL_INIT_PARAMS_S

    \par example
    \code
    PANEL_INIT_PARAMS_S stInitParam;
    memset(&stInitParam, 0x0, sizeof(PANEL_INIT_PARAMS_S));
    if (SUCCESS != panel_init(pstDev, (const PANEL_INIT_PARAMS_S * const)&stInitParam))
    {
        return FAILUE;
    }

    \endcode
    */
    S32 (*panel_init)(struct _PANEL_DEVICE_S* pstDev, const PANEL_INIT_PARAMS_S * const pstInitParams);

    /**
    \brief Panel  deinit.CNcomment:��ģ��ȥ��ʼ�� CNend
    \attention \n
    Lower layer panel module deinit and release occupied repanel,  repeat call return success.
    CNcomment:�ײ���ģ��ȥ��ʼ�����ͷ�ռ�õ���Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstTermParams enc module deinit param.CNcomment:ȥ��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_PANEL_DEINIT_FAILED  Lower layer panel module deinit error.CNcomment:�ײ���ģ��ȥ��ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::PANEL_TERM_PARAMS_S

    \par example
    \code
    PANEL_TERM_PARAMS_S stDeInitParam;
    memset(&stDeInitParam, 0x0, sizeof(PANEL_TERM_PARAMS_S));
    if (SUCCESS != panel_term(pstDev, (const PANEL_TERM_PARAMS_S * const)&stDeInitParam))
    {
        return FAILUE;
    }

    \endcode
    */
    S32 (*panel_term)(struct _PANEL_DEVICE_S* pstDev, const PANEL_TERM_PARAMS_S *const  pstTermParams);

    /**
    \brief Create panel.CNcomment:����Panel CNend
    \attention \n
    \param[in] pstCreateParams create param.CNcomment:�������� CNend
    \param[out] pPanelHandle generated handle.CNcomment:���ɵľ�� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:��ָ�롣CNend
    \retval ::ERROR_PANEL_OP_FAILED panel operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::PANEL_CREATE_PARAMS_S

    \par example
    */
    S32 (* panel_create)(struct _PANEL_DEVICE_S* pstDev, HANDLE * const pPanelHandle, PANEL_CREATE_PARAMS_S * const pstCreateParams);

    /**
    \brief destory panel.CNcomment:����PANEL CNend
    \attention \n
    \param[in] hPanel panel handle.CNcomment:����Դ��� CNend
    \param[in] pstDestoryParams destory param.CNcomment:���ٲ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:����ģ��δ��ʼ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED panel operate failed.CNcomment:����Դ�豸��������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    ::PANEL_DESTORY_PARAMS_S

    \par example
    */
    S32 (* panel_destory)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, PANEL_DESTORY_PARAMS_S * const pstDestoryParams);

    /**
    \brief set power on the PANEL device. CNcomment:���������µ�ʱ�� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] bEnable: power state CNcomment:���������ʹ����Ϣ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_power_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief set back light the PANEL device. CNcomment:�������ı��� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] bEnable: back light state CNcomment:�����������״̬ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_backlight_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief get back light the PANEL device. CNcomment:��ȡ���ı���״̬ CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pbEnable: back light state CNcomment:����ǰ�����״̬ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_backlight_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL *pbEnable);

    /**
    \brief get attr of PANEL device. CNcomment:��ȡ�������� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pstPanelAttr: panel attr  CNcomment:�������� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (*panel_get_panel_attr)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, PANEL_ATTR_S *pstPanelAttr);


    /**
    \brief set dynamic backlight enable the PANEL device. CNcomment:�������Ķ�̬����ʹ�� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] pbEnable: dynamic back light enable flag CNcomment:��̬����ʹ�ñ�־ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (*panel_set_dynamic_backlight_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief set back light level the PANEL device. CNcomment:�������ı���ȼ� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] u32Level: back light level CNcomment:����ĵȼ� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_backlight_level)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Level);

    /**
    \brief set back light level the PANEL device. CNcomment:��ȡ���ı���ȼ� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] u32Level: back light level CNcomment:����ĵȼ� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_backlight_level)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Level);

    /**
    \brief set local dimming on/off . CNcomment:������localdimming���� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] u32Level: local dimming enable flag CNcomment:localdimmingʹ�ܱ�־ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_localdimming_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief get local dimming the PANEL device. CNcomment:��ȡ��localdimming���� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] u32Level: local dimming on off status CNcomment:localdimming����״̬ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_localdimming_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL *pbEnable);

    /**
    \brief set spread enable .CNcomment:����չƵ���� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] bEnable spread enable flag. CNcomment:չƵ���ر�־ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_set_lvds_spread_enable )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief set lvds spread ratio .CNcomment:����lvdsչƵ����CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] ratio lvds spread ratio value range[0,100] . CNcomment:lvdsչƵ���� range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_lvds_spread_ratio )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Ratio);

    /**
    \brief get lvds spread ratio .CNcomment:lvds չƵֵ CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pu32Ratio lvds spread ratio range[0,100]. CNcomment:lvds չƵֵ range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_lvds_spread_ratio )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Ratio);

    /**
    \brief set lvds spread freq .CNcomment:����lvdsչƵƵ�� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] u32Freq lvds spread freq range[0,100]. CNcomment:lvds չƵƵ��range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_lvds_spread_freq )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Freq);

    /**
    \brief get lvds spread freq .CNcomment:��ȡlvdsչƵƵ�� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pu32Freq lvds spread freq,range[0,100]. CNcomment:lvdsչƵƵ��,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_lvds_spread_freq )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Freq);

    /**
    \brief set lvds drving current .CNcomment:����lvds�������� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] u32Current lvds drving current,range[0,100]. CNcomment:lvds��������,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_lvds_drviver_current)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Current);

    /**
    \brief get lvds drving current .CNcomment:��ȡlvds�������� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pfBert get from panel,range[0,100]. CNcomment:lvds�������� ,range[0,100]CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_lvds_driver_current)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Current);

    /**
    \brief set lvds common voltage .CNcomment:����lvds��ģ��ѹ CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] u32Voltage lvds common voltage,range[0,100]. CNcomment:lvds��ģ��ѹ,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_lvds_common_voltage)(struct _PANEL_DEVICE_S* pstDev,  const HANDLE hPanel, U32 u32Voltage);

    /**
    \brief get lvds common voltage .CNcomment:��ȡlvds��ģ��ѹ CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pu32Voltage lvds common voltage,range[0,100]. CNcomment:lvds��ģ��ѹ,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_lvds_common_voltage)(struct _PANEL_DEVICE_S* pstDev,  const HANDLE hPanel, U32 *pu32Voltage);
    /**
    \brief set vbo spread ratio .CNcomment:����vboչƵ���� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] u32Ratio vbone spread ratio,range[0,100]. CNcomment:vboչƵ����,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
     S32 (*panel_set_vbo_spread_ratio)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Ratio);
    /**
    \brief get vbo spread ratio .CNcomment:��ȡvboչƵ���� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pu32Ratio vbo spread ratio,range[0,100]. CNcomment:vboչƵ���� ,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_vbo_spread_ratio)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Ratio);

    /**
    \brief set vbone spread freq .CNcomment:����vboչƵƵ�� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] u32Freq vbone spread freq,range[0,100]. CNcomment:vboչƵƵ��,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_vbo_spread_freq)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Freq);

    /**
    \brief get vbone spread freq .CNcomment:��ȡvboչƵƵ�� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pu32Freq vbone spread freq,range[0,100]. CNcomment:vboչƵƵ�� range[0,100]CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_vbo_spread_freq)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Freq);

    /**
    \brief lock sync .CNcomment: ����VBOչƵ���� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] bEnable vbo spread enable flag. CNcomment:VBOչƵ���ر�־ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_vbo_spread_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief set vbo drving current .CNcomment:����vbo�������� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] u32Current vbo drving current, range[0,100]. CNcomment:vbo��������range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_set_vbone_driver_current)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Current);

    /**
    \brief  .CNcomment:��ȡvbo�������� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pu32Current vbo driving current range[0,100]. CNcomment:vbo�������� range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_get_vbone_driver_current)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Current);

    /**
    \brief set vbo emphasis value .CNcomment:����vboԤ���� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[in] u32emphasis set vbo emphasis value range[0,100]. CNcomment:vboԤ����ֵ range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_set_vbo_emphasis)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32emphasis);

    /**
    \brief get vbo emphasis value.CNcomment:��ȡvboԤ���� CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:��� CNend
    \param[out] pu32emphasis vbo emphasis valuse, range[0,100]. CNcomment:vboԤ����ֵ range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_get_vboEmphasis)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32emphasis);


} PANEL_DEVICE_S;

/**
\brief direct get panel device api, for linux and android.CNcomment:��ȡ���豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get panel device api��for linux and andorid.
CNcomment:��ȡ���豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
\retval  panel device pointer when success.CNcomment:�ɹ��������豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::PANEL_DEVICE_S

\par example
*/
PANEL_DEVICE_S* getPanelDevice();

/**
\brief Open HAL panel module device.CNcomment:��HAL panelģ���豸 CNend
\attention \n
Open HAL panel module device(for compatible Android HAL).
CNcomment:��HAL panelģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice panel device structure.CNcomment:���豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::PANEL_DEVICE_S

\par example
*/
static inline int panel_open(const struct hw_module_t* pstModule, PANEL_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, PANEL_HARDWARE_PANEL0,  (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getPanelDevice();
    return SUCCESS;
#endif
}

/**
\brief Close HAL panel module device.CNcomment:�ر�HAL panelģ���豸 CNend
\attention \n
Close HAL panel module device(for compatible Android HAL).
CNcomment:�ر�HAL panelģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice panel device structure.CNcomment:���豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
\see \n
::PANEL_DEVICE_S

\par example
*/
static inline int panel_close(PANEL_DEVICE_S* pstDevice)
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

#endif /* __TVOS_HAL_PANEL */

