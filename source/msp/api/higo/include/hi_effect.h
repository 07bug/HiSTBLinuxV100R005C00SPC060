/******************************************************************************
*
* Copyright (C) 2016 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
******************************************************************************
File Name        : hi_effect.h
Version          : Initial Draft
Author           :
Created          : 2016/06/28
Description      :
Function List    :


History          :
Date                Author                Modification
2014/06/28          sdk              Created file
******************************************************************************/
#ifndef __HI_EFFECT_H__
#define __HI_EFFECT_H__

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

#include <hi_type.h>
#include <hi_go.h>



/***************************** Macro Definition ******************************/
/** \addtogroup      Effect */
/** @{ */  /** <!-- [Effect] */

/**Definition of the HiEffect error ID*/
/** CNcomment:HiEffect ��Ŀ����ID */
#define HIEFFECT_ERR_APPID (0x80000000L + 0x40000000L)

/**Definition of the HiEffect module ID*/
/** CNcomment:HiEffect ģ��ID */
#define HIEFFECT_ERR_MODUID 0x00000000

/** @} */  /*! <!-- Macro Definition end */

/*************************** Structure Definition ****************************/
/** \addtogroup      Effect */
/** @{ */  /** <!-- [Effect] */


typedef enum hiEFFECTLOG_ERRLEVEL_E
{
    HIEFFECT_LOG_LEVEL_DEBUG = 0,  /**<debug-level                                  */
    HIEFFECT_LOG_LEVEL_INFO,       /**<informational                                */
    HIEFFECT_LOG_LEVEL_NOTICE,     /**<normal but significant condition      */
    HIEFFECT_LOG_LEVEL_WARNING,    /**<warning conditions                         */
    HIEFFECT_LOG_LEVEL_ERROR,      /**<error conditions                             */
    HIEFFECT_LOG_LEVEL_CRIT,       /**<critical conditions                           */
    HIEFFECT_LOG_LEVEL_ALERT,      /**<action must be taken immediately   */
    HIEFFECT_LOG_LEVEL_FATAL,      /**<just for compatibility with previous version */
    HIEFFECT_LOG_LEVEL_BUTT
} HIEFFECT_LOG_ERRLEVEL_E;

/**Definition of the HiEffect error code*/
/** CNcomment:HiEffect �����붨��� */
#define HIEFFECT_DEF_ERR(module, errid) \
    ((HI_S32)((HIEFFECT_ERR_APPID) | ((module) << 16) | ((HIEFFECT_LOG_LEVEL_ERROR) << 13) | (errid)))


enum HIEFFECT_ErrorCode_E
{
    ERR_HIEFFECT_CODE_UNDEF,
    ERR_HIEFFECT_PTR_NULL,                 /**<pointer is NULL*/
    ERR_HIEFFECT_NO_OPEN,                  /**<effect not open*/
    ERR_HIEFFECT_OPENED,                   /**<effect opened*/
    ERR_HIEFFECT_CLOSED,                   /**<effect closed*/

    /* New */
    ERR_HIEFFECT_INVALID_DEVICE,           /**<invalid device */
    ERR_HIEFFECT_INVALID_HANDLE,           /**<invalid handle*/
    ERR_HIEFFECT_INVALID_PARAMETER,        /**<invalid parameter */
    ERR_HIEFFECT_INVALID_OPERATION,        /**<invalid operation*/
    ERR_HIEFFECT_ADDR_FAULT,               /**<address fault */
    ERR_HIEFFECT_NO_MEM                    /**<mem alloc fail */
};

#define HI_ERR_HIEFFECT_CODE_UNDEF\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_CODE_UNDEF)

#define HI_ERR_HIEFFECT_PTR_NULL\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_PTR_NULL)

#define HI_ERR_HIEFFECT_OPENED\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_OPENED)

#define HI_ERR_HIEFFECT_CLOSED\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_CLOSED)

#define HI_ERR_HIEFFECT_NO_OPEN\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_NO_OPEN)


#define HI_ERR_HIEFFECT_INVALID_DEVICE\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_INVALID_DEVICE)

#define HI_ERR_HIEFFECT_INVALID_HANDLE\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_INVALID_HANDLE)

#define HI_ERR_HIEFFECT_INVALID_PARAMETER\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_INVALID_PARAMETER)

#define HI_ERR_HIEFFECT_INVALID_OPERATION\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_INVALID_OPERATION)

#define HI_ERR_HIEFFECT_ADDR_FAULT\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_ADDR_FAULT)

#define HI_ERR_HIEFFECT_NO_MEM\
    HIEFFECT_DEF_ERR(HIEFFECT_ERR_MODUID, ERR_HIEFFECT_NO_MEM)

/**Screen refresh callback*/
/** CNcomment:��Ļˢ�»ص�����*/
typedef HI_S32 (*pRefresh_Callback)(HI_VOID);
typedef enum hiEFFECT_MODE_E
{
    HI_EFFECT_NONE = 0, 			/**<Copy *//**<CNcomment:������ʾ*/
    HI_EFFECT_TURNPAGE, 			/**<Turnpage *//**<CNcomment:��ҳ*/
    HI_EFFECT_ROLLPAGE, 			/**<Rollpage *//**<CNcomment:����*/
    HI_EFFECT_VERTICALSHUTTER,		/**<Vertical shutter *//**<CNcomment:��ֱ��Ҷ��*/
    HI_EFFECT_HORIZONTALSHUTTER,    /**<Horizontal shutter *//**<CNcomment:ˮƽ��Ҷ��*/
    HI_EFFECT_LEFTIN,				/**<Leftin*//**<CNcomment:������*/
    HI_EFFECT_TOPIN, 				/**<Topin*//**<CNcomment:���ϳ��*/
    HI_EFFECT_TRANSIN, 				/**<Transin*//**<CNcomment:��������*/
    HI_EFFECT_ROTATE,  				/**<Rotate*//**<CNcomment:����*/
    HI_EFFECT_CENTEROUT,  			/**<Centerout*//**<CNcomment:���뽥��*/
    HI_EFFECT_CENTERIN, 			/**<Centerin*//**<CNcomment:���뽥��*/
} EFFECT_MODE_E;

typedef enum hiEFFECT_SPEED
{
    HI_EFFECT_SPEED_FAST   = 1,
    HI_EFFECT_SPEED_NORMAL = 2,
    HI_EFFECT_SPEED_SLOW = 4,
} EFFECT_SPEED;


/** @} */  /*! <!-- Structure Definition end */

/******************************* API declaration *****************************/
/** \addtogroup      Effect */
/** @{ */  /** <!-- [Effect] */

/**
\brief Effect init function. CNcomment:��Ч��ʼ������ CNend

\attention \n
CNcomment: ע����Ļˢ�»ص�������������ʾģʽ
bLetfbox ΪHI_TRUE, ��ʾͼ���������Ļ������һ��ʱ��Ӻڱ�
bLetfbox ΪHI_FALSE, ��ʾͼ�����ų�ȫ��,���ͼ�α�������Ļ������һ�»ᵼ�±���.
�������ַ�ʽ,ͼ��ȫ����ʾ CNend
\param[in] pfCallBack Screen refresh callback function.CNcomment:��Ļˢ�»ص����� CNend
\param[in] bLetfbox Picture dispaly mode.CNcomment:ͼ����ʾ��ʽ CNend
\retval ::HI_ERR_HIEFFECT_OPENED
\retval ::HI_ERR_HIEFFECT_PTR_NULL
\retval ::HI_SUCCESS

\see \n
::HI_Effect_Init \n
::HI_Effect_Deinit
*/
extern HI_S32  HI_Effect_Init(pRefresh_Callback pfCallBack, HI_BOOL bLetfbox);

/**
\brief Effect deinit function. CNcomment:��Чȥ��ʼ������ CNend
\attention \n
N/A
\param N/A. CNcomment:�� CNend
\retval ::HI_ERR_HIEFFECT_NO_OPEN
\retval ::HI_SUCCESS
\see \n
::HI_GO_Init \n
::HI_Effect_Deinit
*/
extern HI_S32  HI_Effect_Deinit(HI_VOID);

/**
\brief Effect play function. CNcomment:��Ч���ź��� CNend

\attention \n
CNcomment: ��Ч���ź���, �ú���Ϊ��������,��Ч��ɲ��˳�
����surface�����ظ�ʽ���뱣��һ��
Ŀǰ֧�ֵĸ�ʽ:
    HIGO_PF_4444,
    HIGO_PF_0444,
    HIGO_PF_1555,
    HIGO_PF_0555,
    HIGO_PF_565, CNend
\param[in] hNewSurface new surface
\param[in] hScreenSurface Screen suface
\param[in] mode Effect mode.
\retval ::HI_ERR_HIEFFECT_NO_OPEN
\retval ::HI_ERR_HIEFFECT_INVALID_PARAMETER
\retval ::HI_ERR_HIEFFECT_INVALID_OPERATION
\retval ::HI_ERR_HIEFFECT_NO_MEM
\retval ::HI_SUCCESS
\see \n
N/A. CNcomment:�� CNend
*/
extern HI_S32  HI_Effect_Play(HI_HANDLE hNewSurface, HI_HANDLE hScreenSurface, EFFECT_MODE_E mode);


/**
\brief Effect Set Layer handle function. CNcomment:������Ч��� CNend
\attention \n
N/A
\param[in] Layer Layer handle
\retval ::HI_SUCCESS
\see \n
N/A. CNcomment:�� CNend
*/
extern HI_S32 HI_Effect_SetLayer(HI_HANDLE Layer);

/**
\brief Effect Stop function. CNcomment:��Ч������ֹ,������߰�����Ӧ�ٶ� CNend
\attention \n
N/A
\param N/A. CNcomment:�� CNend
\retval ::HI_ERR_HIEFFECT_NO_OPEN
\retval ::HI_SUCCESS
\see \n
N/A. CNcomment:��
*/
extern HI_S32  HI_Effect_Stop(HI_VOID);

/**
\brief Set Effect Speed function. CNcomment:������Ч�����ٶ� CNend
\attention \n
N/A
\param[in] eSpeed Effect Speed
\retval ::HI_ERR_HIEFFECT_NO_OPEN
\retval ::HI_ERR_HIEFFECT_INVALID_PARAMETER
\retval ::HI_SUCCESS
\see \n
N/A. CNcomment:�� CNend
*/
extern HI_S32  HI_Effect_SetSpeed(EFFECT_SPEED eSpeed);

/** @} */  /*! <!-- API declaration end */
#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __HI_PEFFECT_H__ */
