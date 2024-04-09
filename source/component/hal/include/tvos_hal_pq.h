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
/** CNcomment:ģ��ID ���� */
#define PQ_HARDWARE_MODULE_ID "pq"

/**Device name define .*/
/** CNcomment:�豸���ƶ��� */
#define PQ_HARDWARE_PQ0      "pq0"

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HAL_PQ */
/** @{ */  /** <!-- [HAL_PQ] */

/**pq init param *//** CNcomment:PQģ���ʼ������ */
typedef struct _PQ_INIT_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:����*/
} PQ_INIT_PARAMS_S;

/**pq deinit param *//** CNcomment:ģ��ȥ��ʼ������  */
typedef struct _PQ_TERM_PARAMS_S
{
    U32 u32Dummy; /**<Reserve *//**<CNcomment:����*/
} PQ_TERM_PARAMS_S;

/**pq create param *//** CNcomment:PQ�������� */
typedef struct _PQ_CREATE_PARAMS_S
{
    PQ_ID_E enPqId; /**<Pq ID *//**<CNcomment:PQID*/
} PQ_CREATE_PARAMS_S;

/**pq destroy param *//** CNcomment:PQ���ٲ��� */
typedef struct _PQ_DESTORY_PARAMS_S
{
    U32 u32Dummy;  /**<Reserve *//**<CNcomment:����*/
} PQ_DESTORY_PARAMS_S;


/**PQ matket mode */
/**CNcomment: PQ����ģʽ */
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
/**CNcomment: PQ����ģ��*/
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
/**CNcomment: ɫ����Ϣ*/
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
/**CNcomment: ��ɫ��������*/
typedef enum _PQ_FLESHTONE_E
{
     PQ_FLESHTONE_GAIN_OFF = 0,
     PQ_FLESHTONE_GAIN_LOW,
     PQ_FLESHTONE_GAIN_MID,
     PQ_FLESHTONE_GAIN_HIGH,

     PQ_FLESHTONE_GAIN_BUTT
}  PQ_FLESHTONE_E;

/**Six base color type*/
/**CNcomment: ����ɫ����*/
typedef enum _PQ_SIX_BASE_COLOR_E
{
    PQ_SIX_BASE_COLOR_ALL_ON = 0,
    PQ_SIX_BASE_COLOR_R_OFF,//��
    PQ_SIX_BASE_COLOR_G_OFF,//��
    PQ_SIX_BASE_COLOR_B_OFF,//��
    PQ_SIX_BASE_COLOR_CYAN_OFF,//��
    PQ_SIX_BASE_COLOR_MAGENTA_OFF,//��
    PQ_SIX_BASE_COLOR_YELLOW_OFF,//��
    PQ_SIX_BASE_COLOR_RGB_OFF,//������
    PQ_SIX_BASE_COLOR_CMY_OFF,//���ϻ�
    PQ_SIX_BASE_COLOR_ALL_OFF,//������ɫ�ر�

    PQ_SIX_BASE_COLOR_BUTT
} PQ_SIX_BASE_COLOR_E;

/**SR demo mode*//**CNcomment: SR��ʾģʽ*/
typedef enum _PQ_SR_DEMO_E
{
     PQ_SR_DISABLE  = 0,//�ص�SR,ֻZME
     PQ_SR_ENABLE_R,  //  �ұ�SR
     PQ_SR_ENABLE_L,  //���SR
     PQ_SR_ENABLE_A,  //ȫ��

     PQ_SR_DEMO_BUTT
}PQ_SR_DEMO_E;

/**Brightness histgram information*//**CNcomment: ֱ��ͼλ����Ϣ*/
typedef enum _PQ_HISTGRAM_SITE_E
{
    PQ_HISTGRAM_VIDEO,
    PQ_HISTGRAM_VIDEO_OSD,

    PQ_HISTGRAM_BUTT
}PQ_HISTGRAM_SITE_E;

/**Brightness histgram information*//**CNcomment: ����ֱ��ͼ��Ϣ*/
typedef struct _PQ_DCI_HISTGRAM_S
{
    S32 s32HistGram[32];
}PQ_DCI_HISTGRAM_S;

/****  �Զ���ƽ��������  ****/
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


/**Sharpen GAIN*//**CNcomment: �߼�����������*/
typedef struct _PQ_SHARP_GAIN_S
{
    U32 u32LtiGain; //��Χ[ 0 , 511]
    U32 u32HPeakRatio; //��Χ[ 0 , 511]
    U32 u32VPeakRatio; //��Χ[ 0 , 511]
    U32 u32DPeakRatio; //��Χ[ 0 , 511]
}PQ_SHARP_GAIN_S;

/**Color GAIN*//**CNcomment:Color   ����*/
typedef struct _PQ_COLOR_GAIN_S
{
    U32 u32LumGain; //��Χ[ 0 , 1023]
    U32 u32HueGain; //��Χ[ 0 , 1023]
    U32 u32SatGain; //��Χ[ 0 , 1023]
    U32 u32Reserved;
}PQ_COLOR_GAIN_S;

/**DCI GAIN*//**CNcomment:Color   ����*/
typedef struct _PQ_DCI_GAIN_S
{
    U32 u32LowGain; //��Χ[ 0 , 63]
    U32 u32MiddleGain; //��Χ[ 0 , 63]
    U32 u32HighGain; //��Χ[ 0 , 63]
    U32 u32Reserved;
}PQ_DCI_GAIN_S;

/**Color Section*//**CNcomment:FIXMODE :��ɫ�ֶ����� */
typedef enum _PQ_COLOR_E
{
    PQ_COLOR_R,//��
    PQ_COLOR_G,//��
    PQ_COLOR_B,//��
    PQ_COLOR_CYAN,//��
    PQ_COLOR_PURPLE,//��
    PQ_COLOR_YELLOW,//��
    PQ_COLOR_FLESH,//��ɫ

    PQ_COLOR_BUTT
} PQ_COLOR_E;

/**Color SATGAIN*//**CNcomment:FIXMODE :��ɫ���Ͷ�����  */
typedef struct _PQ_SAT_GAIN_S
{
    PQ_COLOR_E enColorType;
    S32 s32Gain;
}PQ_SAT_GAIN_S;


/**Color HUEGAIN*//**CNcomment:��ɫɫ������ */
typedef struct _PQ_HUE_GAIN_S
{
    PQ_COLOR_E enColorType;
    S32 s32Gain;
}PQ_HUE_GAIN_S;

/**Color YGAIN*//**CNcomment:��ɫ��������  */
typedef struct _PQ_BRI_GAIN_S
{
    PQ_COLOR_E enColorType;
    S32 s32Gain;
}PQ_BRI_GAIN_S;

/**struct of gamma*//**CNcomment:gamma�ṹ  */
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


/**dolby mode*//**CNcomment:�ű�ģʽ��Ϣ  */
typedef enum PQ_DOLBY_MODE_E
{
    PQ_DOLBY_MODE_ENHANCE = 0,
    PQ_DOLBY_MODE_STANDARD,
    PQ_DOLBY_MODE_BUTT
}PQ_DOLBY_MODE_E;

/**HDR TYPE info *//**CNcomment: HDR ������Ϣ  */
typedef enum PQ_HDR_TYPE_E
{
    PQ_HDR_TYPE_SDR = 0,//SDR
    PQ_HDR_HDR10_NONCONSTLUM,//HDR10�Ǻ㶨����
    PQ_HDR_HDR10_CONSTLUM,//HDR10�㶨����
    PQ_HDR_SDR_BT2020_NONCONSTLUM,// 2020�Ǻ㶨����
    PQ_HDR_SDR_BT2020_CONSTLUM,// 2020�㶨����
    PQ_HDR_SDR_XVYCC,// XVYCC
    PQ_HDR_DOLBY_VISION,//�ű�
    PQ_HDR_TYPE_BUTT
}PQ_HDR_TYPE_E;

#ifdef ANDROID_HAL_MODULE_USED
/**PQ module structure(Android require)*/
/**CNcomment:PQģ��ṹ(Android�Խ�Ҫ��) */
typedef struct _PQ_MODULE_S
{
    struct hw_module_t stCommon;
} PQ_MODULE_S;
#endif

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      HAL_PQ */
/** @{ */  /** <!-- [HAL_PQ] */

/**PQ device structure*//** CNcomment:PQ�豸�ṹ*/
typedef struct _PQ_DEVICE_S
{
#ifdef ANDROID_HAL_MODULE_USED
    struct hw_device_t stCommon;
#endif

    /**
    \brief PQ  init.CNcomment:PQģ���ʼ�� CNend
    \attention \n
    Lower layer pq module init and alloc necessary repq,  repeat call return success.
    CNcomment:�ײ�PQģ���ʼ���������Ҫ����Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstInitParams system module init param.CNcomment:��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_PQ_INIT_FAILED  Lower layer pq module init error.CNcomment:�ײ�PQģ���ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
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
    \brief PQ  term.CNcomment:PQģ����ֹ CNend
    \attention \n
    Lower layer pq module init and alloc necessary repq,  repeat call return success.
    CNcomment:�ײ�PQģ���ʼ���������Ҫ����Դ, �������ظ����÷��سɹ�. CNend
    \param[in] pstInitParams system module init param.CNcomment:��ʼ������ CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_PQ_INIT_FAILED  Lower layer pq module init error.CNcomment:�ײ�PQģ���ʼ������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
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
    \brief PQ  init.CNcomment:PQģ���ʼ�� CNend
    \attention \n
    \param[out] pPqHandle Pointor to the PQ handle.CNcomment:ָ��PQ�����ָ�� CNend
    \param[in] pstInitParams system module create param.CNcomment:���������� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_PQ_INIT_FAILED  Lower layer pq module init error.CNcomment:�ײ�PQģ�鴴������CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    \par example
    \code

    \endcode
    */
    S32 (* pq_create)(struct _PQ_DEVICE_S* pstDev, HANDLE * const pPqHandle, PQ_CREATE_PARAMS_S * const pstCreateParams);

    /**
    \brief PQ  destory.CNcomment:PQģ������ CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] pstDestoryParams system module destory param.CNcomment:���ٲ��� CNend
    \retval ::SUCCESS Success.CNcomment:�ɹ���CNend
    \retval ::ERROR_PQ_INIT_FAILED  Lower layer pq module init error.CNcomment:�ײ�PQģ�����ٴ���CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n
    \par example
    \code

    \endcode
    */
    S32 (* pq_destory)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DESTORY_PARAMS_S * const pstDestoryParams);

    /**
    \brief get brightness. CNcomment:��ȡ���� CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pu32Brightness.CNcomment:����ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_brightness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Brightness);

    /**
    \brief set brightness. CNcomment:�������� CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] u32Brightness.CNcomment:����ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_brightness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Brightness);

    /**
    \brief get contrast. CNcomment:��ȡ�Աȶ� CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pu32Contrast.CNcomment:�Ա�ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_contrast)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Contrast);

    /**
    \brief set Contrast. CNcomment:���öԱȶ� CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] u32Contrast.CNcomment:�Աȶ�ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_contrast)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Contrast);

    /**
    \brief get saturation. CNcomment:��ȡ���Ͷ� CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pu32Saturation.CNcomment:���Ͷ� ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_satuation)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Saturation);

    /**
    \brief set saturation. CNcomment:���ñ��Ͷ� CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] u32Saturation.CNcomment:���Ͷ�ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_saturation)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Saturation);

    /**
    \brief get hue. CNcomment:��ȡɫ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pu32Hue.CNcomment:ɫ��ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_hue)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Hue);

    /**
    \brief set hue. CNcomment:����ɫ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] u32Hue.CNcomment:ɫ��ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_hue)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Hue);

    /**
    \brief get noise reduction level. CNcomment:��ȡ����ǿ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pu32NrLevel.CNcomment:����ǿ��ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_nr)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32NrLevel);


    /**
    \brief set noise reduction level. CNcomment:��ȡ����ǿ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] u32NrLevel.CNcomment:����ǿ��ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_nr)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32NrLevel);

    /**
    \brief get  auto noise reduction status. CNcomment:��ȡ�Զ����뿪��״̬CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pbEnable.CNcomment:����״̬ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_nr_auto_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pbEnable);

    /**
    \brief set  auto noise reduction status. CNcomment:�����Զ����뿪��״̬CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] bEnable.CNcomment: Auto NR���� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_nr_auto_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 bEnable);

    /**
    \brief get  SR demo type. CNcomment:��ȡ����SR��ʾ����CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] penType.CNcomment:SR��ʾ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_sr_demo_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SR_DEMO_E *penType);

    /**
    \brief set  SR demo type. CNcomment:���ó���SR��ʾ����CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] enType.CNcomment:��ʾ����CCNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_sr_demo_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SR_DEMO_E enType);


    /**
    \brief get sharpness level. CNcomment:��ȡ������ǿ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pu32Sharpness.CNcomment:������ǿ��ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_sharpness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32Sharpness);

    /**
    \brief set sharpness level. CNcomment:����������ǿ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] u32Sharpness.CNcomment:������ǿ��ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_sharpness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Sharpness);

    /**
    \brief get de-blocking level. CNcomment:��ȡ�齵��De-blockingǿ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pu32DbLevel.CNcomment:De-blockingǿ��ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_deblock)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32DbLevel);

    /**
    \brief set de-blocking level. CNcomment:���ÿ齵��De-blockingǿ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] u32DbLevel.CNcomment:De-blockingǿ��ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_deblock)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32DbLevel);

    /**
     \brief get de-ringing level. CNcomment:��ȡde-ringingǿ��CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[out] pu32DMlevel.CNcomment:De-ringingǿ��ֵ,��Ч��ΧΪ0~255 CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */

    S32 (* pq_get_deringing)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32DMlevel);

    /**
    \brief set de-ringing level. CNcomment:����de-ringingǿ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] u32DMlevel.CNcomment:De-ringingǿ��ֵ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_deringing)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32DMlevel);
    /**
    \brief set color temperature. CNcomment:����ɫ��ֵCNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] pstColorTemp.CNcomment:ɫ��ֵ ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_color_temp)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_COLOR_TEMP_S *pstColorTemp);

    /**
    \brief get color temperature. CNcomment:��ȡɫ��ֵCNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pstColorTemp.CNcomment:ɫ��ֵ ,��Ч��ΧΪ0~255 CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_color_temp)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_COLOR_TEMP_S *pstColorTemp);

    /**
    \brief get color curve total number . CNcomment:��ȡ��ɫ��������CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pu32ColorType.CNcomment: �ο�Color ����  CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_color_curve_num)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32ColorCurveNum);

    /**
    \brief set color curve index. CNcomment:����color����Index
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] u32Index curve index.CNcomment: Color����Index CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_color_curve_index)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32Index);

    /**
    \brief get flesh tone level. CNcomment:��ȡ��ɫ��ǿǿ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] penFleshToneLevel Flesh Tone Level.CNcomment:Flesh Toneǿ��CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_flesh_tone)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_FLESHTONE_E *penFleshToneLevel);

    /**
    \brief set flesh tone level. CNcomment:���÷�ɫ��ǿǿ��CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] enFleshToneLevel.CNcomment:ǿ�� ,�ο� PQ_FLESHTONE_E CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_flesh_tone)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_FLESHTONE_E enFleshToneLevel);

    /**
    \brief get gamma total number. CNcomment:Gamma Table�д��ڶ���Gamma����,�û��ɻ�ȡGamma��������CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] ps32Num.CNcomment:gamma ���� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */


    S32 (* pq_get_gamma_curve_num)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, S32 *ps32Num);


    /**
    \brief set gamma by index. CNcomment:����gamma CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] s32GammaIndex.CNcomment:gamma index CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_gamma_curve_index)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, S32 s32GammaIndex);

    /**
    \brief get Dci total number. CNcomment:Dci Table�п��ܴ��ڶ���Dci����,�û��ɻ�ȡDci��������CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] ps32Num.CNcomment:Dci ���� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_dci_curve_num)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, S32 *ps32Num);

    /**
    \brief set Dci by index. CNcomment:����Dci CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] s32DciIndex.CNcomment:Dci index CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_dci_curve_index)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, S32 s32DciIndex);

    /**
    \brief set all PQ module on/off status. CNcomment:���ø�PQ ģ�鿪�� CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] enFlags.CNcomment:ģ��ţ��ο�PQ_MODULE_E CNend
    \param[in] bEnable.CNcomment:���� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_module_enable)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq,  PQ_MODULE_E enFlags, BOOL bEnable);

    /**
    \brief get all PQ module on/off status. CNcomment:��ȡ��PQ ģ�鿪�� CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] enFlags.CNcomment:ģ��ţ��ο�PQ_MODULE_E CNend
    \param[out] bEnable.CNcomment:����״̬ CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_module_enable)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_MODULE_E enFlags, BOOL *pbEnable);

    /**
    \brief set all PQ module demo status. CNcomment:���ø�PQ ģ������ģʽ CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] enFlags.CNcomment:ģ��ţ��ο�PQ_DEMO_E CNend
    \param[in] bEnable.CNcomment:����ģʽ���� CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_module_demo_enable)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DEMO_E enFlags, BOOL bEnable);


    /**
    \brief get brightness histgram information. CNcomment:��ȡ����ֱ��ͼ��ϢCNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pstDCIHistgram histgram info.CNcomment:ֱ��ͼ��ϢCNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_histgram)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DCI_HISTGRAM_S *pstDciHistgram);

    /**
    \brief get average brightness by histgram information. CNcomment:��ȡƽ������CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pu32AvrBrigheness().CNcomment:ƽ������CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_average_brightness)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32AvrBrigheness);

    /**
    \brief get White balance information. CNcomment:��ȡ�Զ���ƽ������ϢCNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pstWhiteBalanceParam.CNcomment:�Զ���ƽ������ϢCNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_white_balance_param)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_WHITE_BALANCE_PARAM_S *pstWhiteBalanceParam);

    /**
    \brief get color gain information. CNcomment:��ȡ��ɫ ������CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pstColorGain.CNcomment:COLOR   ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_color_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_COLOR_GAIN_S *pstColorGain);

    /**
    \brief set color gain information. CNcomment:������ɫ ������CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] pstColorGain.CNcomment:COLOR   ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_set_color_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_COLOR_GAIN_S *pstColorGain);


    /**
    \brief Set dolby mode. CNcomment: ����dolbyģʽCNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] enDolbyMode.CNcomment:dolby ģʽCNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */

    S32 (* pq_set_dolby_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DOLBY_MODE_E enDolbyMode);

    /**
    \brief get dolby mode. CNcomment: ��ȡdolbyģʽCNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[in] penDolbyMode.CNcomment:dolby ģʽCNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_dolby_mode)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DOLBY_MODE_E *penDolbyMode);

    /**
    \brief get hdr type�� CNcomment: ��ȡHDR����  CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] enHdrType.CNcomment:HDR������0~5CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
    S32 (* pq_get_hdr_type)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_HDR_TYPE_E *penHdrType);

    /**
    \brief set sharpen gain information. CNcomment:��ȡSharpen ������CNend
    \attention \n
    \param[in] hPq PQ handle.CNcomment:PQ��� CNend
    \param[out] pstSharpenGain Sharpen gain info.CNcomment:Sharpen   ����CNend
    \retval ::ERROR_INVALID_PARAM invalid param, such as invalid hanlde.CNcomment:��Ч����������Ч�����CNend
    \retval ::ERROR_PQ_OP_FAILED do this funtion error.CNcomment:����ʧ�ܡ�CNend
    \retval ::FAILURE  other error.CNcomment:�������� CNend
    \see \n

    \par example
    \code


    \endcode
    */
     S32 (* pq_get_sharpen_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SHARP_GAIN_S *pstSharpenGain);

     /**
     \brief get average brightness by histgram information. CNcomment:����Sharpen��Ƶ������CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[in] pstSharpenGain.CNcomment:Sharpen   ����CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_set_sharpen_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SHARP_GAIN_S *pstSharpenGain);

     /**
     \brief get average brightness by histgram information. CNcomment:��ȡ�Աȶ� ������CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[out] pstDciGain.CNcomment:dci  ����CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_get_dci_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DCI_GAIN_S *pstDciGain);

    /**
     \brief get average brightness by histgram information. CNcomment:���öԱȶ� ������CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[in] pstDciGain.CNcomment:DCI   ����CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */

    S32 (* pq_set_dci_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_DCI_GAIN_S *pstDciGain);

    /**
     \brief Set Saturation gain for section color. CNcomment: ���÷ֶ���ɫ���Ͷ����� ��ϢCNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[in] pstSatGain.CNcomment:��ɫ���Ͷ�������ϢCNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_set_satuation_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SAT_GAIN_S *pstSatGain);

    /**
     \brief Get Saturation gain for section color. CNcomment: ��ȡ�ֶ���ɫ���Ͷ� ��ϢCNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[out] pstSatGain.CNcomment:��ɫ���Ͷ�������ϢCNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_get_satuation_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_SAT_GAIN_S *pstSatGain);


    /**
     \brief Set HUE gain for section color. CNcomment: ���÷ֶ���ɫɫ����ϢCNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[in] pstHueGain.CNcomment:COLOR  Դ��ϢCNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_set_hue_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_HUE_GAIN_S *pstHueGain);

    /**
     \brief Get HUE gain for section color. CNcomment: ��ȡ�ֶ���ɫɫ����ϢCNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[out] pstHueGain.CNcomment:COLOR Դ��ϢCNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */

    S32 (* pq_get_hue_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_HUE_GAIN_S *pstHueGain);

    /**
     \brief Get Bright gain for section color. CNcomment: ��ȡ�ֶ���ɫ������ϢCNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[in] pstHueGain.CNcomment:COLOR  Դ��ϢCNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_get_brightness_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_BRI_GAIN_S *pstBriGain);

    /**
     \brief Set Bright gain for section color. CNcomment: ���÷ֶ���ɫ������ϢCNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[in] pstHueGain.CNcomment:COLOR  Դ��ϢCNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_set_brightness_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_BRI_GAIN_S *pstBriGain);

    /**
     \brief Set gamma table data. CNcomment: ��ȡGAMMA ������CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[in] pstGammaTable gamma table.CNcomment:gamma table ����CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_set_gamma_table)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_GAMMA_TABLE_S *pstGammaTable);

    /**
     \brief Get gamma table data. CNcomment: ��ȡGAMMA ������CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[out] pstGammaTable gamma table.CNcomment:gamma table ����CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_get_gamma_table)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_GAMMA_TABLE_S *pstGammaTable);

    /**
     \brief set cti gain. CNcomment:���� cti ������CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[in] pstCtiGain .CNcomment:Cti   ����CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment: 0~128
     */
    S32 (* pq_set_cti_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 u32CtiGain);

    /**
     \brief get cti gain. CNcomment:��ȡ cti ������CNend
     \attention \n
     \param[in] hPqend pq handle param.CNcomment:��� CNend
     \param[out] pstCtiGain.CNcomment:Cti   ����CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_get_cti_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, U32 *pu32CtiGain);


    /**
     \brief Set NRStr . CNcomment: ���ý�������CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[in] pstNRStr .CNcomment:NR���� CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment: 0~64
     */
    S32 (* pq_set_nr_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_NRSTR_GAIN_S *pstNRStr);

    /**
     \brief get NRStr.    CNcomment: ��ȡ��������CNend
     \attention \n
     \param[in] hPq PQ handle.CNcomment:PQ��� CNend
     \param[out] pstNRStr.CNcomment:NR  ����CNend
     \retval HI_SUCCESS     success.  CNcomment:�ɹ� CNend
     \retval please refer to the err code definitino of mpi.CNcomment:��ο�MPI������ CNend
     \see \n
     CNcomment:�� CNend
     */
    S32 (* pq_get_nr_gain)(struct _PQ_DEVICE_S* pstDev, const HANDLE hPq, PQ_NRSTR_GAIN_S *pstNRStr);

} PQ_DEVICE_S;

/**
\brief direct get PQ device api, for linux and android.CNcomment:��ȡPQ�豸�Ľӿ�, Linux��Androidƽ̨������ʹ�� CNend
\attention \n
get PQ device api��for linux and andorid.
CNcomment:��ȡ���豸�ӿڣ�linux��androidƽ̨������ʹ��. CNend
\retval  PQ device pointer when success.CNcomment:�ɹ�����PQ�豸ָ�롣CNend
\retval ::NULL when failure.CNcomment:ʧ�ܷ��ؿ�ָ�� CNend
\see \n
::PQ_DEVICE_S

\par example
*/
PQ_DEVICE_S* getPqEndDevice();

/**
\brief Open HAL PQ module device.CNcomment:��HAL PQģ���豸 CNend
\attention \n
Open HAL PQ module device(for compatible Android HAL).
CNcomment:��HAL PQģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstModule moudule structure.CNcomment:ģ�����ݽṹCNend
\param[out] ppstDevice PQ device structure.CNcomment:PQ�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:�������� CNend
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
\brief Close HAL PQ module device.CNcomment:Close HAL PQģ���豸 CNend
\attention \n
Close HAL PQ module device.(for compatible Android HAL).
CNcomment:Close HAL PQģ���豸(Ϊ����Android HAL�ṹ). CNend
\param[in] pstDevice pq device structure.CNcomment:PQ�豸���ݽṹ CNend
\retval ::SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::FAILURE  other error.CNcomment:���� CNend
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


