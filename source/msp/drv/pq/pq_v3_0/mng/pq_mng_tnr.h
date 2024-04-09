/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : pq_mng_tnr.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2015/1/9
  Description   :

******************************************************************************/

#ifndef __PQ_MNG_TNR_H__
#define __PQ_MNG_TNR_H__

#include "pq_hal_tnr.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


/**
 \brief ��ʼ��TNRģ��
 \attention \n
��

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitTnr(HI_VOID);


/**
 \brief ȥ��ʼ��TNRģ��
 \attention \n
��

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DeInitTnr(HI_VOID);


/**
 \brief ����TNRģ��
 \attention \n
��

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_EnableTnr(HI_BOOL bOnOff);


/**
 \brief ��ȡTNRʹ��״̬
 \attention \n
��

 \param[out] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_GetTnrEnableFlag(HI_BOOL *pbOnOff);


/**
 \brief ����NRģ��DEMOģʽ
 \attention \n
��

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_EnableTnrDemo(HI_BOOL bOnOff);


/**
 \brief :  set tnr demo mode ;

 \param[in] enMode

 \retval ::HI_SUCCESS
 */

HI_S32 PQ_MNG_SetTnrDemoMode(TNR_DEMO_MODE_E enMode);

/**
 \brief :  get tnr demo mode ;

 \param[in] enMode

 \retval ::HI_SUCCESS
 */

HI_S32 PQ_MNG_GetTnrDemoMode(TNR_DEMO_MODE_E *penMode);


/**
\brief Set Tnr Strengh
\attention \n
��

\param[in] s32TnrStr  Tnr Strengh[0,100]

\retval ::HI_SUCCESS

*/

HI_S32 PQ_MNG_SetTnrStrength(HI_S32 s32TnrStr);


/**
 \brief ��ȡNRǿ��
 \attention \n
��

 \param[in] s32NrStr  NRǿ��ֵ��ȡֵ��Χ[0,255]

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetTnrStrength(HI_S32 *ps32TnrStr);


/**
  \brief ����TNR��PixMean-Ratio For YMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_YMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrYMotionPixMeanRatio(TNR_MAPPING_S *pstTNR_YMotionPixmeanRatio);


/**
  \brief ��ȡTNR��PixMean-Ratio For YMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_YMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrYMotionPixMeanRatio(TNR_MAPPING_S *pstTNR_YMotionPixmeanRatio);


/**
  \brief ����TNR��PixMean-Ratio For CMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_CMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrCMotionPixMeanRatio(TNR_MAPPING_S *pstTNR_CMotionPixmeanRatio);


/**
  \brief ��ȡTNR��PixMean-Ratio For CMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_CMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrCMotionPixMeanRatio(TNR_MAPPING_S *pstTNR_CMotionPixmeanRatio);


/**
  \brief ����TNR��YMotionMapping����
  \attention \n
 ��

  \param[in] pstTNR_YMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrYMotionMapping(TNR_MAPPING_S *pstTNR_YMotionMapping);


/**
  \brief ��ȡTNR��YMotionMapping����
  \attention \n
 ��

  \param[in] pstTNR_YMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrYMotionMapping(TNR_MAPPING_S *pstTNR_YMotionMapping);


/**
  \brief ����TNR��CMotonMapping ����
  \attention \n
 ��

  \param[in] pstTNR_CMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrCMotionMapping(TNR_MAPPING_S *pstTNR_CMotionMapping);


/**
  \brief ��ȡTNR��CMotonMapping����
  \attention \n
 ��

  \param[in] pstTNR_CMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrCMotionMapping(TNR_MAPPING_S *pstTNR_CMotionMapping);


/**
  \brief ����TNR��Final Y Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionYMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrFnlMotionYMapping(TNR_MAPPING_S *pstTNR_FnlMotionYMapping);


/**
  \brief ��ȡTNR��Final Y Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionYMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrFnlMotionYMapping(TNR_MAPPING_S *pstTNR_FnlMotionYMapping);


/**
  \brief ����TNR��Final C Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionCMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrFnlMotionCMapping(TNR_MAPPING_S *pstTNR_FnlMotionCMapping);



/**
  \brief ��ȡTNR��Final C Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionCMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrFnlMotionCMapping(TNR_MAPPING_S *pstTNR_FnlMotionCMapping);

/**
  \brief ���� TNR��Y Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_YfmotionMapping

  \retval ::HI_SUCCESS

  */
HI_S32 PQ_MNG_SetTnrFmotionMapping(TNR_FMOTION_MAPPING_S *pstTNR_YfmotionMapping);

/**
  \brief ��ȡTNR��Y Motion Mapping  ����
  \attention \n
 ��

  \param[in] pstTNR_YfmotionMapping

  \retval ::HI_SUCCESS

  */
HI_S32 PQ_MNG_GetTnrFmotionMapping(TNR_FMOTION_MAPPING_S *pstTNR_YfmotionMapping);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*End of #ifndef __MNG_PQ_NR_H__ */



