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

/**Module id define.*//** CNcomment:模块ID 定义 */
#define PANEL_HARDWARE_MODULE_ID    "panel"

/**Device name define .*//** CNcomment:设备名称定义 */
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

/**panel init param *//** CNcomment:PANEL模块初始化参数 */
typedef struct _PANEL_INIT_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:保留*/
} PANEL_INIT_PARAMS_S;

/**panel deinit param *//** CNcomment:模块去初始化参数  */
typedef struct _PANEL_TERM_PARAMS_S
{
    U32 u32Dummy; /**<Reserve *//**<CNcomment:保留*/
} PANEL_TERM_PARAMS_S;

/**panel create param *//** CNcomment:PANEL创建参数 */
typedef struct _PANEL_CREATE_PARAMS_S
{
    PANEL_ID_E enPanelId; /**<Panel ID *//**<CNcomment:PANELID*/
} PANEL_CREATE_PARAMS_S;

/**panel destroy param *//** CNcomment:PANEL销毁参数 */
typedef struct _PANEL_DESTORY_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:保留*/
} PANEL_DESTORY_PARAMS_S;


/**panel aspect *//**CNcomment:panel显示的比例模式*/
typedef enum _PANEL_ASPECT_E
{
    PANEL_ASPECT_4_3 = 0,    /**<aspect is 4:3 *//**CNcomment: 4:3 显示 */
    PANEL_ASPECT_16_9,       /**<aspect is 16:9 *//**CNcomment: 16:9 显示 */
    PANEL_ASPECT_14_9,       /**<aspect is 14:9 *//**CNcomment: 14:9 显示 */
    PANEL_ASPECT_21_9,       /**<aspect is 21:9 *//**CNcomment: 21:9 显示 */
    PANEL_ASPECT_16_10,      /**<aspect is 16:10 *//**CNcomment: 16:10 显示 */

    PANEL_ASPECT_BUTT,       /**<Invalid value*//**<CNcomment:非法边界值*/
}PANEL_ASPECT_E;


/**panel attr *//**CNcomment:panel属性*/
typedef struct _PANEL_ATTR_S
{
    U32                     u32Width;   /**<Width *//**CNcomment: Panel的宽度 */
    U32                     u32Height;  /**<Height *//**CNcomment: Panel的高度 */
    PANEL_ASPECT_E          enAspect;   /**<aspect *//**CNcomment: Panel的比例模式 */
}PANEL_ATTR_S;



#ifdef ANDROID_HAL_MODULE_USED
/**Panel module structure(Android require)*/
/**CNcomment:Panel模块结构(Android对接要求) */
typedef struct _PANEL_MODULE_S
{
    struct hw_module_t stCommon;
} PANEL_MODULE_S;
#endif

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/*************************** API declaration ****************************/
/** \addtogroup      HAL_PANEL */
/** @{ */  /** <!-- [HAL_PANEL] */

/**Panel device structure*//** CNcomment:屏设备结构*/
typedef struct _PANEL_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon; /**<Module common structure(Android require) *//**<CNcomment:模块通用结构(Android对接要求 ) */
#endif

    /**
    \brief Panel  init.CNcomment:屏模块初始化 CNend
    \attention \n
    Lower layer panel module init and alloc necessary repanel,  repeat call return success.
    CNcomment:底层屏模块初始化及分配必要的资源, 本函数重复调用返回成功. CNend
    \param[in] pstInitParams system module init param.CNcomment:初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_PANEL_INIT_FAILED  Lower layer panel module init error.CNcomment:底层屏模块初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Panel  deinit.CNcomment:屏模块去初始化 CNend
    \attention \n
    Lower layer panel module deinit and release occupied repanel,  repeat call return success.
    CNcomment:底层屏模块去初始化及释放占用的资源, 本函数重复调用返回成功. CNend
    \param[in] pstTermParams enc module deinit param.CNcomment:去初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_PANEL_DEINIT_FAILED  Lower layer panel module deinit error.CNcomment:底层屏模块去初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
    \brief Create panel.CNcomment:创建Panel CNend
    \attention \n
    \param[in] pstCreateParams create param.CNcomment:创建参数 CNend
    \param[out] pPanelHandle generated handle.CNcomment:生成的句柄 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_NULL_PTR null ptr.CNcomment:空指针。CNend
    \retval ::ERROR_PANEL_OP_FAILED panel operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::PANEL_CREATE_PARAMS_S

    \par example
    */
    S32 (* panel_create)(struct _PANEL_DEVICE_S* pstDev, HANDLE * const pPanelHandle, PANEL_CREATE_PARAMS_S * const pstCreateParams);

    /**
    \brief destory panel.CNcomment:销毁PANEL CNend
    \attention \n
    \param[in] hPanel panel handle.CNcomment:输入源句柄 CNend
    \param[in] pstDestoryParams destory param.CNcomment:销毁参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_NOT_INITED not inited.CNcomment:所在模块未初始化。CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED panel operate failed.CNcomment:输入源设备操作错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::PANEL_DESTORY_PARAMS_S

    \par example
    */
    S32 (* panel_destory)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, PANEL_DESTORY_PARAMS_S * const pstDestoryParams);

    /**
    \brief set power on the PANEL device. CNcomment:设置屏上下电时序 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] bEnable: power state CNcomment:给屏供电的使能信息 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_power_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief set back light the PANEL device. CNcomment:设置屏的背光 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] bEnable: back light state CNcomment:设置屏背光的状态 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_backlight_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief get back light the PANEL device. CNcomment:获取屏的背光状态 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pbEnable: back light state CNcomment:屏当前背光的状态 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_backlight_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL *pbEnable);

    /**
    \brief get attr of PANEL device. CNcomment:获取屏的属性 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pstPanelAttr: panel attr  CNcomment:屏的属性 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (*panel_get_panel_attr)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, PANEL_ATTR_S *pstPanelAttr);


    /**
    \brief set dynamic backlight enable the PANEL device. CNcomment:设置屏的动态背光使能 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] pbEnable: dynamic back light enable flag CNcomment:动态背光使用标志 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (*panel_set_dynamic_backlight_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief set back light level the PANEL device. CNcomment:设置屏的背光等级 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] u32Level: back light level CNcomment:背光的等级 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_backlight_level)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Level);

    /**
    \brief set back light level the PANEL device. CNcomment:获取屏的背光等级 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] u32Level: back light level CNcomment:背光的等级 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_backlight_level)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Level);

    /**
    \brief set local dimming on/off . CNcomment:设置屏localdimming开关 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] u32Level: local dimming enable flag CNcomment:localdimming使能标志 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_localdimming_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief get local dimming the PANEL device. CNcomment:获取屏localdimming开关 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] u32Level: local dimming on off status CNcomment:localdimming开关状态 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_localdimming_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL *pbEnable);

    /**
    \brief set spread enable .CNcomment:设置展频开关 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] bEnable spread enable flag. CNcomment:展频开关标志 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_set_lvds_spread_enable )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief set lvds spread ratio .CNcomment:设置lvds展频幅度CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] ratio lvds spread ratio value range[0,100] . CNcomment:lvds展频幅度 range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_lvds_spread_ratio )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Ratio);

    /**
    \brief get lvds spread ratio .CNcomment:lvds 展频值 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pu32Ratio lvds spread ratio range[0,100]. CNcomment:lvds 展频值 range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_lvds_spread_ratio )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Ratio);

    /**
    \brief set lvds spread freq .CNcomment:设置lvds展频频率 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] u32Freq lvds spread freq range[0,100]. CNcomment:lvds 展频频率range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_lvds_spread_freq )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Freq);

    /**
    \brief get lvds spread freq .CNcomment:读取lvds展频频率 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pu32Freq lvds spread freq,range[0,100]. CNcomment:lvds展频频率,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_lvds_spread_freq )(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Freq);

    /**
    \brief set lvds drving current .CNcomment:设置lvds驱动电流 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] u32Current lvds drving current,range[0,100]. CNcomment:lvds驱动电流,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_lvds_drviver_current)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Current);

    /**
    \brief get lvds drving current .CNcomment:读取lvds驱动电流 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pfBert get from panel,range[0,100]. CNcomment:lvds驱动电流 ,range[0,100]CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_lvds_driver_current)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Current);

    /**
    \brief set lvds common voltage .CNcomment:设置lvds共模电压 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] u32Voltage lvds common voltage,range[0,100]. CNcomment:lvds共模电压,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_lvds_common_voltage)(struct _PANEL_DEVICE_S* pstDev,  const HANDLE hPanel, U32 u32Voltage);

    /**
    \brief get lvds common voltage .CNcomment:获取lvds共模电压 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pu32Voltage lvds common voltage,range[0,100]. CNcomment:lvds共模电压,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_lvds_common_voltage)(struct _PANEL_DEVICE_S* pstDev,  const HANDLE hPanel, U32 *pu32Voltage);
    /**
    \brief set vbo spread ratio .CNcomment:设置vbo展频幅度 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] u32Ratio vbone spread ratio,range[0,100]. CNcomment:vbo展频幅度,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
     S32 (*panel_set_vbo_spread_ratio)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Ratio);
    /**
    \brief get vbo spread ratio .CNcomment:获取vbo展频幅度 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pu32Ratio vbo spread ratio,range[0,100]. CNcomment:vbo展频幅度 ,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_vbo_spread_ratio)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Ratio);

    /**
    \brief set vbone spread freq .CNcomment:设置vbo展频频率 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] u32Freq vbone spread freq,range[0,100]. CNcomment:vbo展频频率,range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_vbo_spread_freq)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Freq);

    /**
    \brief get vbone spread freq .CNcomment:读取vbo展频频率 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pu32Freq vbone spread freq,range[0,100]. CNcomment:vbo展频频率 range[0,100]CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_get_vbo_spread_freq)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Freq);

    /**
    \brief lock sync .CNcomment: 设置VBO展频开关 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] bEnable vbo spread enable flag. CNcomment:VBO展频开关标志 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code

    \endcode
    */
    S32 (*panel_set_vbo_spread_enable)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, BOOL bEnable);

    /**
    \brief set vbo drving current .CNcomment:设置vbo驱动电流 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] u32Current vbo drving current, range[0,100]. CNcomment:vbo驱动电流range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_set_vbone_driver_current)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32Current);

    /**
    \brief  .CNcomment:获取vbo驱动电流 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pu32Current vbo driving current range[0,100]. CNcomment:vbo驱动电流 range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_get_vbone_driver_current)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32Current);

    /**
    \brief set vbo emphasis value .CNcomment:设置vbo预加重 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[in] u32emphasis set vbo emphasis value range[0,100]. CNcomment:vbo预加重值 range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_set_vbo_emphasis)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 u32emphasis);

    /**
    \brief get vbo emphasis value.CNcomment:读取vbo预加重 CNend
    \attention \n
    \param[in] hPanel panel handle param.CNcomment:句柄 CNend
    \param[out] pu32emphasis vbo emphasis valuse, range[0,100]. CNcomment:vbo预加重值 range[0,100] CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PANEL_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code
    \endcode
    */
    S32 (*panel_get_vboEmphasis)(struct _PANEL_DEVICE_S* pstDev, const HANDLE hPanel, U32 *pu32emphasis);


} PANEL_DEVICE_S;

/**
\brief direct get panel device api, for linux and android.CNcomment:获取屏设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get panel device api，for linux and andorid.
CNcomment:获取屏设备接口，linux和android平台都可以使用. CNend
\retval  panel device pointer when success.CNcomment:成功返回屏设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::PANEL_DEVICE_S

\par example
*/
PANEL_DEVICE_S* getPanelDevice();

/**
\brief Open HAL panel module device.CNcomment:打开HAL panel模块设备 CNend
\attention \n
Open HAL panel module device(for compatible Android HAL).
CNcomment:打开HAL panel模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice panel device structure.CNcomment:屏设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
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
\brief Close HAL panel module device.CNcomment:关闭HAL panel模块设备 CNend
\attention \n
Close HAL panel module device(for compatible Android HAL).
CNcomment:关闭HAL panel模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice panel device structure.CNcomment:屏设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
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

