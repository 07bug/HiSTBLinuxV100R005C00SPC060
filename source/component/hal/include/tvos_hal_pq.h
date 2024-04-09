 /**
 * \file
 * \brief Describes the information about the PQ module.
 */

#ifndef __TVOS_HAL_PQ_H__
#define __TVOS_HAL_PQ_H__

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
/** \addtogroup      HAL_PQ */
/** @{ */  /** <!-- [HAL_PQ] */
/*****************************************************************************/

/**Module id define.*/
/** CNcomment:模块ID 定义 */
#define PQ_HARDWARE_MODULE_ID "pq"

/**Device name define .*/
/** CNcomment:设备名称定义 */
#define PQ_HARDWARE_PQ0      "pq0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HAL_PQ */
/** @{ */  /** <!-- [HAL_PQ] */

/**pq init param *//** CNcomment:PQ模块初始化参数 */
typedef struct _PQ_INIT_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:保留*/
} PQ_INIT_PARAMS_S;

/**pq deinit param *//** CNcomment:模块去初始化参数  */
typedef struct _PQ_TERM_PARAMS_S
{
    U32 u32Dummy; /**<Reserve *//**<CNcomment:保留*/
} PQ_TERM_PARAMS_S;

/**pq create param *//** CNcomment:PQ创建参数 */
typedef struct _PQ_CREATE_PARAMS_S
{
    PQ_ID_E enPqId; /**<Pq ID *//**<CNcomment:PQID*/
} PQ_CREATE_PARAMS_S;

/**pq destroy param *//** CNcomment:PQ销毁参数 */
typedef struct _PQ_DESTORY_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:保留*/
} PQ_DESTORY_PARAMS_S;


/**PQ matket mode */
/**CNcomment: PQ卖场模式 */
typedef enum _PQ_DEMO_E
{
     PQ_DEMO_DBMS,
     PQ_DEMO_NR,
     PQ_DEMO_SHARPNESS,
     PQ_DEMO_DCI,
    // PQ_DEMO_FRC,
     PQ_DEMO_COLOR,
     PQ_DEMO_SR,
     PQ_DEMO_HDR,
     PQ_DEMO_ALL,

     PQ_DEMO_BUTT
}  PQ_DEMO_E;

/**PQ on/off module */
/**CNcomment: PQ开关模块*/
typedef enum _PQ_MODULE_E
{
     PQ_MODULE_FMD = 0,
     PQ_MODULE_TNR,
     PQ_MODULE_SNR,
     PQ_MODULE_DB,
     PQ_MODULE_DM,
     PQ_MODULE_DS,
     PQ_MODULE_HSHARPNESS,
     PQ_MODULE_SHARPNESS,
     PQ_MODULE_CCCL,
     PQ_MODULE_COLOR_CORING,
     PQ_MODULE_BLUE_STRETCH,
     PQ_MODULE_GAMMA,
     PQ_MODULE_DBC,
     PQ_MODULE_DCI,
     PQ_MODULE_COLOR,
     PQ_MODULE_SR,
     PQ_MODULE_WCG,
     PQ_MODULE_HDR,
     PQ_MODULE_IQTM,

     PQ_MODULE_BUTT
}  PQ_MODULE_E;

/**Color temperature information*/
/**CNcomment: 色温信息*/
typedef struct _PQ_COLOR_TEMP_S
{
    U32 u32RedGain;
    U32 u32GreenGain;
    U32 u32BlueGain;
    U32 u32RedOffset;
    U32 u32GreenOffset;
    U32 u32BlueOffset;
}  PQ_COLOR_TEMP_S;

/**Flesh tone gain type*/
/**CNcomment: 肤色增益类型*/
typedef enum _PQ_FLESHTONE_E
{
     PQ_FLESHTONE_GAIN_OFF = 0,
     PQ_FLESHTONE_GAIN_LOW,
     PQ_FLESHTONE_GAIN_MID,
     PQ_FLESHTONE_GAIN_HIGH,

     PQ_FLESHTONE_GAIN_BUTT
}  PQ_FLESHTONE_E;

/**Six base color type*/
/**CNcomment: 六基色类型*/
typedef enum _PQ_SIX_BASE_COLOR_E
{
    PQ_SIX_BASE_COLOR_ALL_ON = 0,
    PQ_SIX_BASE_COLOR_R_OFF,//红
    PQ_SIX_BASE_COLOR_G_OFF,//绿
    PQ_SIX_BASE_COLOR_B_OFF,//蓝
    PQ_SIX_BASE_COLOR_CYAN_OFF,//青
    PQ_SIX_BASE_COLOR_MAGENTA_OFF,//紫
    PQ_SIX_BASE_COLOR_YELLOW_OFF,//黄
    PQ_SIX_BASE_COLOR_RGB_OFF,//红绿蓝
    PQ_SIX_BASE_COLOR_CMY_OFF,//青紫黄
    PQ_SIX_BASE_COLOR_ALL_OFF,//所有颜色关闭

    PQ_SIX_BASE_COLOR_BUTT
} PQ_SIX_BASE_COLOR_E;

/**SR demo mode*//**CNcomment: SR演示模式*/
typedef enum _PQ_SR_DEMO_E
{
     PQ_SR_DISABLE  = 0,//关掉SR,只ZME
     PQ_SR_ENABLE_R,  //  右边SR
     PQ_SR_ENABLE_L,  //左边SR
     PQ_SR_ENABLE_A,  //全屏

     PQ_SR_DEMO_BUTT
}PQ_SR_DEMO_E;

/**Brightness histgram information*//**CNcomment: 直方图位置信息*/
typedef enum _PQ_HISTGRAM_SITE_E
{
    PQ_HISTGRAM_VIDEO,
    PQ_HISTGRAM_VIDEO_OSD,

    PQ_HISTGRAM_BUTT
}PQ_HISTGRAM_SITE_E;

/**Brightness histgram information*//**CNcomment: 亮度直方图信息*/
typedef struct _PQ_DCI_HISTGRAM_S
{
    S32 s32HistGram[32];
}PQ_DCI_HISTGRAM_S;

/****  自动白平衡结果参数  ****/
typedef enum _PQ_WHITE_BALANCE_TMP_E
{
   PQ_WHITE_BALANCE_COOL,
   PQ_WHITE_BALANCE_STANDARD,
   PQ_WHITE_BALANCE_WARM,

   PQ_WHITE_BALANCE_BUTT
 }PQ_WHITE_BALANCE_TMP_E;

typedef struct _PQ_WHITE_BALANCE_BALANCE_SINGLE_PARAM_S
{
   U32 u32RGain;
   U32 u32GGain;
   U32 u32BGain;
   U32 u32ROffset;
   U32 u32GOffset;
   U32 u32BOffset;
}PQ_WHITE_BALANCE_SINGLE_PARAM_S;

typedef struct _PQ_WHITE_BALANCE_PARAM_S
{
   PQ_WHITE_BALANCE_SINGLE_PARAM_S astTepParam[PQ_WHITE_BALANCE_BUTT];
}PQ_WHITE_BALANCE_PARAM_S;


/**Sharpen GAIN*//**CNcomment: 高级清晰度增益*/
typedef struct _PQ_SHARP_GAIN_S
{
    U32 u32LtiGain; //范围[ 0 , 511]
    U32 u32HPeakRatio; //范围[ 0 , 511]
    U32 u32VPeakRatio; //范围[ 0 , 511]
    U32 u32DPeakRatio; //范围[ 0 , 511]
}PQ_SHARP_GAIN_S;

/**Color GAIN*//**CNcomment:Color   增益*/
typedef struct _PQ_COLOR_GAIN_S
{
    U32 u32LumGain; //范围[ 0 , 1023]
    U32 u32HueGain; //范围[ 0 , 1023]
    U32 u32SatGain; //范围[ 0 , 1023]
    U32 u32Reserved;
}PQ_COLOR_GAIN_S;

/**DCI GAIN*//**CNcomment:Color   增益*/
typedef struct _PQ_DCI_GAIN_S
{
    U32 u32LowGain; //范围[ 0 , 63]
    U32 u32MiddleGain; //范围[ 0 , 63]
    U32 u32HighGain; //范围[ 0 , 63]
    U32 u32Reserved;
}PQ_DCI_GAIN_S;

/**Color Section*//**CNcomment:FIXMODE :颜色分段类型 */
typedef enum _PQ_COLOR_E
{
    PQ_COLOR_R,//红
    PQ_COLOR_G,//绿
    PQ_COLOR_B,//蓝
    PQ_COLOR_CYAN,//青
    PQ_COLOR_PURPLE,//紫
    PQ_COLOR_YELLOW,//黄
    PQ_COLOR_FLESH,//肤色

    PQ_COLOR_BUTT
} PQ_COLOR_E;

/**Color SATGAIN*//**CNcomment:FIXMODE :颜色饱和度增益  */
typedef struct _PQ_SAT_GAIN_S
{
    PQ_COLOR_E enColorType;
    S32 s32Gain;
}PQ_SAT_GAIN_S;


/**Color HUEGAIN*//**CNcomment:颜色色调增益 */
typedef struct _PQ_HUE_GAIN_S
{
    PQ_COLOR_E enColorType;
    S32 s32Gain;
}PQ_HUE_GAIN_S;

/**Color YGAIN*//**CNcomment:颜色亮度增益  */
typedef struct _PQ_BRI_GAIN_S
{
    PQ_COLOR_E enColorType;
    S32 s32Gain;
}PQ_BRI_GAIN_S;

/**struct of gamma*//**CNcomment:gamma结构  */
/**/
typedef struct _PQ_GAMMA_TABLE_S
{
    U32 au32R[257];
    U32 au32G[257];
    U32 au32B[257];
} PQ_GAMMA_TABLE_S;

/*NR  str type Y/C*/
typedef enum PQ_NRSTR_E
{
     PQ_NRSTR_Y = 0,
     PQ_NRSTR_C,
     PQPQ_NRSTR_BUTT
} PQ_NRSTR_E;

typedef struct PQ_NRSTR_GAIN_S
{
    PQ_NRSTR_E enNRSTR;
    U32 u32Gain;
}PQ_NRSTR_GAIN_S;


/**dolby mode*//**CNcomment:杜比模式信息  */
typedef enum PQ_DOLBY_MODE_E
{
    PQ_DOLBY_MODE_ENHANCE = 0,
    PQ_DOLBY_MODE_STANDARD,
    PQ_DOLBY_MODE_BUTT
}PQ_DOLBY_MODE_E;

/**HDR TYPE info *//**CNcomment: HDR 类型信息  */
typedef enum PQ_HDR_TYPE_E
{
    PQ_HDR_TYPE_SDR = 0,//SDR
    PQ_HDR_HDR10_NONCONSTLUM,//HDR10非恒定亮度
    PQ_HDR_HDR10_CONSTLUM,//HDR10恒定亮度
    PQ_HDR_SDR_BT2020_NONCONSTLUM,// 2020非恒定亮度
    PQ_HDR_SDR_BT2020_CONSTLUM,// 2020恒定亮度
    PQ_HDR_SDR_XVYCC,// XVYCC
    PQ_HDR_DOLBY_VISION,//杜比
    PQ_HDR_TYPE_BUTT
}PQ_HDR_TYPE_E;

#ifdef ANDROID_HAL_MODULE_USED
/**PQ module structure(Android require)*/
/**CNcomment:PQ模块结构(Android对接要求) */
typedef struct _PQ_MODULE_S
{
    struct hw_module_t stCommon;
} PQ_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HAL_PQ */
/** @{ */  /** <!-- [HAL_PQ] */

/**PQ device structure*//** CNcomment:PQ设备结构*/
typedef struct _PQ_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief PQ  init.CNcomment:PQ模块初始化 CNend
    \attention \n
    Lower layer pq module init and alloc necessary repq,  repeat call return success.
    CNcomment:底层PQ模块初始化及分配必要的资源, 本函数重复调用返回成功. CNend
    \param[in] pstInitParams system module init param.CNcomment:初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_PQ_INIT_FAILED  Lower layer pq module init error.CNcomment:底层PQ模块初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::PQ_INIT_PARAMS_S

    \par example
    \code
    PQ_INIT_PARAMS_S stInitParam;
    memset(&stInitParam, 0x0, sizeof(PQ_INIT_PARAMS_S));
    if (SUCCESS != pq_init(pstDev, (const PQ_INIT_PARAMS_S * const)&stInitParam))
    {
        return FAILUE;
    }

    \endcode
    */
    S32 (* pq_Init)(struct _PQ_DEVICE_S* pstDev, const PQ_INIT_PARAMS_S * const pstInitParams);

    /**
    \brief PQ  term.CNcomment:PQ模块终止 CNend
    \attention \n
    Lower layer pq module init and alloc necessary repq,  repeat call return success.
    CNcomment:底层PQ模块初始化及分配必要的资源, 本函数重复调用返回成功. CNend
    \param[in] pstInitParams system module init param.CNcomment:初始化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_PQ_INIT_FAILED  Lower layer pq module init error.CNcomment:底层PQ模块初始化错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    ::PQ_INIT_PARAMS_S

    \par example
    \code
    PQ_INIT_PARAMS_S stTermParams;
    memset(&stTermParams, 0x0, sizeof(PQ_TERM_PARAMS_S));
    if (SUCCESS != pq_term(pstDev, (const PQ_TERM_PARAMS_S * const)&stTermParams))
    {
        return FAILUE;
    }

    \endcode
    */
    S32 (* pq_term)(struct _PQ_DEVICE_S* pstDev, const PQ_TERM_PARAMS_S * const pstTermParams);

    /**
    \brief PQ  init.CNcomment:PQ模块初始化 CNend
    \attention \n
    \param[out] pPqHandle Pointor to the PQ handle.CNcomment:指向PQ句柄的指针 CNend
    \param[in] pstInitParams system module create param.CNcomment:创建化参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_PQ_INIT_FAILED  Lower layer pq module init error.CNcomment:底层PQ模块创建错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    \par example
    \code

    \endcode
    */
    S32 (* pq_create)(struct _PQ_DEVICE_S* pstDev, HANDLE * const pPqHandle, PQ_CREATE_PARAMS_S * const pstCreateParams);

    /**
    \brief PQ  destory.CNcomment:PQ模块销毁 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] pstDestoryParams system module destory param.CNcomment:销毁参数 CNend
    \retval ::SUCCESS Success.CNcomment:成功。CNend
    \retval ::ERROR_PQ_INIT_FAILED  Lower layer pq module init error.CNcomment:底层PQ模块销毁错误。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n
    \par example
    \code

    \endcode
    */
    S32 (* pq_destory)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DESTORY_PARAMS_S * const pstDestoryParams);

    /**
    \brief get brightness. CNcomment:获取亮度 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pu32Brightness.CNcomment:亮度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_brightness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Brightness);

    /**
    \brief set brightness. CNcomment:设置亮度 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] u32Brightness.CNcomment:亮度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_brightness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Brightness);

    /**
    \brief get contrast. CNcomment:获取对比度 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pu32Contrast.CNcomment:对比值,有效范围为0~255 CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_contrast)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Contrast);

    /**
    \brief set Contrast. CNcomment:设置对比度 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] u32Contrast.CNcomment:对比度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_contrast)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Contrast);

    /**
    \brief get saturation. CNcomment:获取饱和度 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pu32Saturation.CNcomment:饱和度 值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_satuation)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Saturation);

    /**
    \brief set saturation. CNcomment:设置饱和度 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] u32Saturation.CNcomment:饱和度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_saturation)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Saturation);

    /**
    \brief get hue. CNcomment:获取色调CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pu32Hue.CNcomment:色调值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_hue)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Hue);

    /**
    \brief set hue. CNcomment:设置色调CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] u32Hue.CNcomment:色调值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_hue)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Hue);

    /**
    \brief get noise reduction level. CNcomment:获取降噪强度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pu32NrLevel.CNcomment:降噪强度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_nr)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32NrLevel);


    /**
    \brief set noise reduction level. CNcomment:获取降噪强度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] u32NrLevel.CNcomment:降噪强度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_nr)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32NrLevel);

    /**
    \brief get  auto noise reduction status. CNcomment:获取自动降噪开关状态CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pbEnable.CNcomment:开关状态 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_nr_auto_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pbEnable);

    /**
    \brief set  auto noise reduction status. CNcomment:设置自动降噪开关状态CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] bEnable.CNcomment: Auto NR开关 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_nr_auto_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 bEnable);

    /**
    \brief get  SR demo type. CNcomment:获取超分SR演示类型CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] penType.CNcomment:SR演示类型CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_sr_demo_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SR_DEMO_E *penType);

    /**
    \brief set  SR demo type. CNcomment:设置超分SR演示类型CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] enType.CNcomment:演示类型CCNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_sr_demo_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SR_DEMO_E enType);


    /**
    \brief get sharpness level. CNcomment:获取清晰度强度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pu32Sharpness.CNcomment:清晰度强度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_sharpness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Sharpness);

    /**
    \brief set sharpness level. CNcomment:设置清晰度强度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] u32Sharpness.CNcomment:清晰度强度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_sharpness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Sharpness);

    /**
    \brief get de-blocking level. CNcomment:获取块降噪De-blocking强度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pu32DbLevel.CNcomment:De-blocking强度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_deblock)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32DbLevel);

    /**
    \brief set de-blocking level. CNcomment:设置块降噪De-blocking强度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] u32DbLevel.CNcomment:De-blocking强度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_deblock)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32DbLevel);

    /**
     \brief get de-ringing level. CNcomment:获取de-ringing强度CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[out] pu32DMlevel.CNcomment:De-ringing强度值,有效范围为0~255 CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */

    S32 (* pq_get_deringing)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32DMlevel);

    /**
    \brief set de-ringing level. CNcomment:设置de-ringing强度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] u32DMlevel.CNcomment:De-ringing强度值,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_deringing)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32DMlevel);
    /**
    \brief set color temperature. CNcomment:设置色温值CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] pstColorTemp.CNcomment:色温值 ,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_color_temp)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_COLOR_TEMP_S *pstColorTemp);

    /**
    \brief get color temperature. CNcomment:获取色温值CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pstColorTemp.CNcomment:色温值 ,有效范围为0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_color_temp)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_COLOR_TEMP_S *pstColorTemp);

    /**
    \brief get color curve total number . CNcomment:获取颜色曲线总数CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pu32ColorType.CNcomment: 参考Color 个数  CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_color_curve_num)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32ColorCurveNum);

    /**
    \brief set color curve index. CNcomment:设置color曲线Index
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] u32Index curve index.CNcomment: Color曲线Index CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_color_curve_index)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Index);

    /**
    \brief get flesh tone level. CNcomment:获取肤色增强强度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] penFleshToneLevel Flesh Tone Level.CNcomment:Flesh Tone强度CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_flesh_tone)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_FLESHTONE_E *penFleshToneLevel);

    /**
    \brief set flesh tone level. CNcomment:设置肤色增强强度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] enFleshToneLevel.CNcomment:强度 ,参考 PQ_FLESHTONE_E CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_flesh_tone)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_FLESHTONE_E enFleshToneLevel);

    /**
    \brief get gamma total number. CNcomment:Gamma Table中存在多组Gamma曲线,用户可获取Gamma曲线数量CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] ps32Num.CNcomment:gamma 个数 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */


    S32 (* pq_get_gamma_curve_num)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, S32 *ps32Num);


    /**
    \brief set gamma by index. CNcomment:设置gamma CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] s32GammaIndex.CNcomment:gamma index CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_gamma_curve_index)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, S32 s32GammaIndex);

    /**
    \brief get Dci total number. CNcomment:Dci Table中可能存在多组Dci曲线,用户可获取Dci曲线数量CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] ps32Num.CNcomment:Dci 个数 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_dci_curve_num)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, S32 *ps32Num);

    /**
    \brief set Dci by index. CNcomment:设置Dci CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] s32DciIndex.CNcomment:Dci index CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_dci_curve_index)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, S32 s32DciIndex);

    /**
    \brief set all PQ module on/off status. CNcomment:设置各PQ 模块开关 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] enFlags.CNcomment:模块号，参考PQ_MODULE_E CNend
    \param[in] bEnable.CNcomment:开关 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_module_enable)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq,  PQ_MODULE_E enFlags, BOOL bEnable);

    /**
    \brief get all PQ module on/off status. CNcomment:获取各PQ 模块开关 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] enFlags.CNcomment:模块号，参考PQ_MODULE_E CNend
    \param[out] bEnable.CNcomment:开关状态 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_module_enable)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_MODULE_E enFlags, BOOL *pbEnable);

    /**
    \brief set all PQ module demo status. CNcomment:设置各PQ 模块卖场模式 CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] enFlags.CNcomment:模块号，参考PQ_DEMO_E CNend
    \param[in] bEnable.CNcomment:卖场模式开关 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_module_demo_enable)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DEMO_E enFlags, BOOL bEnable);


    /**
    \brief get brightness histgram information. CNcomment:获取亮度直方图信息CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pstDCIHistgram histgram info.CNcomment:直方图信息CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_histgram)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DCI_HISTGRAM_S *pstDciHistgram);

    /**
    \brief get average brightness by histgram information. CNcomment:获取平均亮度CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pu32AvrBrigheness().CNcomment:平均亮度CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_average_brightness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32AvrBrigheness);

    /**
    \brief get White balance information. CNcomment:获取自动白平衡结果信息CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pstWhiteBalanceParam.CNcomment:自动白平衡结果信息CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_white_balance_param)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_WHITE_BALANCE_PARAM_S *pstWhiteBalanceParam);

    /**
    \brief get color gain information. CNcomment:获取颜色 的增益CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pstColorGain.CNcomment:COLOR   增益CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_color_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_COLOR_GAIN_S *pstColorGain);

    /**
    \brief set color gain information. CNcomment:设置颜色 的增益CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] pstColorGain.CNcomment:COLOR   增益CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_color_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_COLOR_GAIN_S *pstColorGain);


    /**
    \brief Set dolby mode. CNcomment: 设置dolby模式CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] enDolbyMode.CNcomment:dolby 模式CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */

    S32 (* pq_set_dolby_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DOLBY_MODE_E enDolbyMode);

    /**
    \brief get dolby mode. CNcomment: 获取dolby模式CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[in] penDolbyMode.CNcomment:dolby 模式CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_dolby_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DOLBY_MODE_E *penDolbyMode);

    /**
    \brief get hdr type。 CNcomment: 获取HDR类型  CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] enHdrType.CNcomment:HDR的类型0~5CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_hdr_type)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_HDR_TYPE_E *penHdrType);

    /**
    \brief set sharpen gain information. CNcomment:获取Sharpen 的增益CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
    \param[out] pstSharpenGain Sharpen gain info.CNcomment:Sharpen   增益CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:无效参数，如无效句柄。CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:操作失败。CNend
    \retval ::FAILURE  other error.CNcomment:其它错误 CNend
    \see \n

    \par example
    \code


    \endcode
    */
     S32 (* pq_get_sharpen_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SHARP_GAIN_S *pstSharpenGain);

     /**
     \brief get average brightness by histgram information. CNcomment:设置Sharpen高频的增益CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[in] pstSharpenGain.CNcomment:Sharpen   增益CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_set_sharpen_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SHARP_GAIN_S *pstSharpenGain);

     /**
     \brief get average brightness by histgram information. CNcomment:获取对比度 的增益CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[out] pstDciGain.CNcomment:dci  增益CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_get_dci_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DCI_GAIN_S *pstDciGain);

    /**
     \brief get average brightness by histgram information. CNcomment:设置对比度 的增益CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[in] pstDciGain.CNcomment:DCI   增益CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */

    S32 (* pq_set_dci_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DCI_GAIN_S *pstDciGain);

    /**
     \brief Set Saturation gain for section color. CNcomment: 设置分段颜色饱和度增益 信息CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[in] pstSatGain.CNcomment:颜色饱和度增益信息CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_set_satuation_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SAT_GAIN_S *pstSatGain);

    /**
     \brief Get Saturation gain for section color. CNcomment: 获取分段颜色饱和度 信息CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[out] pstSatGain.CNcomment:颜色饱和度增益信息CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_get_satuation_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SAT_GAIN_S *pstSatGain);


    /**
     \brief Set HUE gain for section color. CNcomment: 设置分段颜色色调信息CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[in] pstHueGain.CNcomment:COLOR  源信息CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_set_hue_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_HUE_GAIN_S *pstHueGain);

    /**
     \brief Get HUE gain for section color. CNcomment: 获取分段颜色色调信息CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[out] pstHueGain.CNcomment:COLOR 源信息CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */

    S32 (* pq_get_hue_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_HUE_GAIN_S *pstHueGain);

    /**
     \brief Get Bright gain for section color. CNcomment: 获取分段颜色亮度信息CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[in] pstHueGain.CNcomment:COLOR  源信息CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_get_brightness_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_BRI_GAIN_S *pstBriGain);

    /**
     \brief Set Bright gain for section color. CNcomment: 设置分段颜色亮度信息CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[in] pstHueGain.CNcomment:COLOR  源信息CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_set_brightness_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_BRI_GAIN_S *pstBriGain);

    /**
     \brief Set gamma table data. CNcomment: 获取GAMMA 表数据CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[in] pstGammaTable gamma table.CNcomment:gamma table 数据CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_set_gamma_table)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_GAMMA_TABLE_S *pstGammaTable);

    /**
     \brief Get gamma table data. CNcomment: 获取GAMMA 表数据CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[out] pstGammaTable gamma table.CNcomment:gamma table 数据CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_get_gamma_table)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_GAMMA_TABLE_S *pstGammaTable);

    /**
     \brief set cti gain. CNcomment:设置 cti 的增益CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[in] pstCtiGain .CNcomment:Cti   增益CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment: 0~128
     */
    S32 (* pq_set_cti_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32CtiGain);

    /**
     \brief get cti gain. CNcomment:获取 cti 的增益CNend
     \attention \n
     \param[in] hPqend pq handle param.CNcomment:句柄 CNend
     \param[out] pstCtiGain.CNcomment:Cti   增益CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_get_cti_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32CtiGain);


    /**
     \brief Set NRStr . CNcomment: 设置降噪增益CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[in] pstNRStr .CNcomment:NR增益 CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment: 0~64
     */
    S32 (* pq_set_nr_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_NRSTR_GAIN_S *pstNRStr);

    /**
     \brief get NRStr.    CNcomment: 获取降噪增益CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ句柄 CNend
     \param[out] pstNRStr.CNcomment:NR  增益CNend
     \retval HI_SUCCESS     success.  CNcomment:成功 CNend
     \retval please refer to the err code definitino of mpi.CNcomment:请参考MPI错误码 CNend
     \see \n
     CNcomment:无 CNend
     */
    S32 (* pq_get_nr_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_NRSTR_GAIN_S *pstNRStr);

} PQ_DEVICE_S;

/**
\brief direct get PQ device api, for linux and android.CNcomment:获取PQ设备的接口, Linux和Android平台都可以使用 CNend
\attention \n
get PQ device api，for linux and andorid.
CNcomment:获取屏设备接口，linux和android平台都可以使用. CNend
\retval  PQ device pointer when success.CNcomment:成功返回PQ设备指针。CNend
\retval ::NULL when failure.CNcomment:失败返回空指针 CNend
\see \n
::PQ_DEVICE_S

\par example
*/
PQ_DEVICE_S* getPqEndDevice();

/**
\brief Open HAL PQ module device.CNcomment:打开HAL PQ模块设备 CNend
\attention \n
Open HAL PQ module device(for compatible Android HAL).
CNcomment:打开HAL PQ模块设备(为兼容Android HAL结构). CNend
\param[in] pstModule moudule structure.CNcomment:模块数据结构CNend
\param[out] ppstDevice PQ device structure.CNcomment:PQ设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:其它错误 CNend
\see \n
::PQ_DEVICE_S

\par example
*/
static inline int pq_open(const struct hw_module_t* pstModule, PQ_DEVICE_S** ppstDevice)
{
#ifdef ANDROID_HAL_MODULE_USED
    return pstModule->methods->open(pstModule, PQ_HARDWARE_PQ0,  (struct hw_device_t**) ppstDevice);
#else
    *ppstDevice = getPqEndDevice();
    return SUCCESS;
#endif
    return SUCCESS;
}

/**
\brief Close HAL PQ module device.CNcomment:Close HAL PQ模块设备 CNend
\attention \n
Close HAL PQ module device.(for compatible Android HAL).
CNcomment:Close HAL PQ模块设备(为兼容Android HAL结构). CNend
\param[in] pstDevice pq device structure.CNcomment:PQ设备数据结构 CNend
\retval ::SUCCESS Success.CNcomment:成功。CNend
\retval ::FAILURE  other error.CNcomment:错误 CNend
\see \n
::PQ_DEVICE_S

\par example
*/
static inline int pq_close(PQ_DEVICE_S* pstDevice)
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

#endif /* __TVOS_HAL_PQ */


