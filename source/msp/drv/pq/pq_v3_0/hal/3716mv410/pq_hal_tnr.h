/******************************************************************************
*
* Copyright (C) 2015 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

 File Name    : pq_hal_tnr.h
 Version        : Initial Draft
 Author         : sdk
 Created       : 2015/01/09
 Description   :
******************************************************************************/
#ifndef __PQ_HAL_TNR_H__
#define __PQ_HAL_TNR_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


/* tnr demo mode */
typedef enum
{
    TNR_DEMO_ENABLE_L = 0,
    TNR_DEMO_ENABLE_R
} TNR_DEMO_MODE_E;


/*TNR ��ӳ������*/
typedef struct  hiTNR_MAPPING_S
{
    HI_S32 s32MappingMax;    /*���y motionʱMean Ratioӳ������ֵ*/
    HI_S32 s32MappingMin;    /*���y motionʱMean Ratioӳ�����Сֵ*/
    HI_S32 s32MappingR[5];   /*Result*/
    HI_S32 s32MappingT[6];   /*Threshhold*/
    HI_S32 s32MappingK[4];   /*Slope*/

} TNR_MAPPING_S;


//MotionResult
typedef struct
{
    HI_U32 u32GlobalMotion;
    HI_U32 u32AdjustGain;
} TNR_MOTION_RESULT_S;

/* YFmotion ��ӳ������  */
typedef struct hiTNR_FMOTION_MAPPING_S
{
    HI_S16 s16YFmotion[32];
    HI_S16 s16CFmotion[32];
} TNR_FMOTION_MAPPING_S;


HI_S32 PQ_HAL_SetTNRRegist(HI_U32 u32HandleNo, HI_U16 TLUT_CbCr[][32]);


/**
 \brief :  Set Nr Strength;

 \param[in] s32NRStr

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_SetTnrStr(HI_U32 u32HandleNo, HI_S32 s32TnrStr);


/**
 \brief :  Enable or Disable TNr Module;

 \param[in] bNROnOff

 \retval ::HI_SUCCESS
 */
HI_S32 PQ_HAL_EnableTNR(HI_U32 u32HandleNo, HI_BOOL bNROnOff);


/**
 \brief :  Enable or Disable Tnr Demo ;

 \param[in] bNROnOff

 \retval ::HI_SUCCESS
 */
HI_S32 PQ_HAL_EnableTNRDemo(HI_U32 u32HandleNo, HI_BOOL bTNRDemoEn);


/**
 \brief :  Set Tnr Demo Mode;

 \param[in]

 \retval ::HI_SUCCESS
 */

HI_S32 PQ_HAL_SetTNRDemoMode(HI_U32 u32HandleNo, TNR_DEMO_MODE_E enMode);

/**
 \brief Set Tnr Strengh
 \attention \n
��

 \param[in] s32TnrStr  Tnr Strengh[0,100]

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_SetTnrStr(HI_U32 u32HandleNo, HI_S32 s32TnrStr);

HI_S32 PQ_HAL_SetTnrMidStr(HI_U32 u32HandleNo);




/**
  \brief ����TNR��PixMean-Ratio For YMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_YMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_SetTnrYMotionPixMeanRatio(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_YMotionPixmeanRatio);




/**
  \brief ��ȡTNR��PixMean-Ratio For YMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_YMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_GetTnrYMotionPixMeanRatio(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_YMotionPixmeanRatio);






/**
  \brief ����TNR��PixMean-Ratio For CMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_CMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_SetTnrCMotionPixMeanRatio(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_CMotionPixmeanRatio);





/**
  \brief ��ȡTNR��PixMean-Ratio For CMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_CMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_GetTnrCMotionPixMeanRatio(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_CMotionPixmeanRatio);


/**
  \brief ����TNR��YMotionMapping����
  \attention \n
 ��

  \param[in] pstTNR_YMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_SetTnrYMotionMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_YMotionMapping);



/**
  \brief ��ȡTNR��YMotionMapping����
  \attention \n
 ��

  \param[in] pstTNR_YMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_GetTnrYMotionMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_YMotionMapping);


/**
  \brief ����TNR��CMotonMapping ����
  \attention \n
 ��

  \param[in] pstTNR_CMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_SetTnrCMotionMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_CMotionMapping);


/**
  \brief ��ȡTNR��CMotonMapping����
  \attention \n
 ��

  \param[in] pstTNR_CMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_GetTnrCMotionMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_CMotionMapping);



/**
  \brief ����TNR��Final Y Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionYMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_SetTnrFnlMotionYMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_FnlMotionYMapping);


/**
  \brief ��ȡTNR��Final Y Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionYMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_GetTnrFnlMotionYMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_FnlMotionYMapping);


/**
  \brief ����TNR��Final C Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionCMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_SetTnrFnlMotionCMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_FnlMotionCMapping);



/**
  \brief ��ȡTNR��Final C Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionCMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_HAL_GetTnrFnlMotionCMapping(HI_U32 u32HandleNo, TNR_MAPPING_S *pstTNR_FnlMotionCMapping);

/**
  \brief ���áTNR��YFmotionMapping����
  \attention \n
 ��

  \param[in] pstYfmotionMapping

  \retval ::HI_SUCCESS

  */
HI_S32 PQ_HAL_SetTnrFmotionMapping(HI_U32 u32HandleNo, TNR_FMOTION_MAPPING_S *pstFmotionMapping);

/**
  \brief ��ȡTNR��YFmotionMapping����
  \attention \n
 ��

  \param[in] pstYfmotionMapping

  \retval ::HI_SUCCESS

  */
HI_S32 PQ_HAL_GetTnrFmotionMapping(HI_U32 u32HandleNo, TNR_FMOTION_MAPPING_S *pstFmotionMapping);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

