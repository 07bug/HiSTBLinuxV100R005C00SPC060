/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : hi_unf_pq.c
  Version       : Initial Draft
  Author        : sdk
  Created       : 2014/04/01
  Description   : UNF���װ����

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hi_type.h"
#include "hi_unf_pq.h"
#include "hi_mpi_pq.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 \brief ��ʼ��PQ
 \attention \n
��

 \param[in] pszPath:PQ�����ļ�·��

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_Init(HI_VOID)
{
    HI_CHAR *pszPath = HI_NULL;
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_PQ_Init(pszPath);

    return s32Ret;
}


/**
 \brief ȥ��ʼ��PQ
 \attention \n
��

 \param[in] none

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_PQ_DeInit();

    return s32Ret;
}


/**
 \brief Set PQ mode . CNcomment: ����ͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] enImageMode Destination DISP channel PQ mode CNcomment: Ŀ��ͨ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_SetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E enImageMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(enImageMode, HI_UNF_OPTION_MODE_BUTT);

    s32Ret = HI_MPI_PQ_SetImageMode(enImageMode);

    return s32Ret;
}


/**
 \brief Get PQ mode . CNcomment: ��ȡͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] penImageMode  pointer of image mode CNcomment: ָ�����ͣ�ָ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_GetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E *penImageMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(penImageMode);

    s32Ret = HI_MPI_PQ_GetImageMode(penImageMode);

    return s32Ret;
}


/**
 \brief Set the default PQ configuration for video parameter test.  CNcomment: Ϊ����ָ���������PQ ��Ĭ��ֵCNend
 \attention \n
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
 N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_SetDefaultParam(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_MPI_PQ_SetDefaultParam(HI_TRUE);

    return s32Ret;
}

HI_S32 HI_UNF_PQ_SetHDROffset(HI_UNF_DISP_E enChan, HI_UNF_PQ_SETHDROFFSET_S stSetHdrOffset)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_SETHDROFFSET_S stSetHdrOffsetParam = {0};

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(stSetHdrOffset.enHdrProcessScene, HI_UNF_PQ_HDR_PROCESS_SCENE_BUTT);

    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32HdrMode, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32Bright, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32Contrast, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32Satu, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32Hue, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32R, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32G, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32B, PQ_API_MAX_LEVEL);

    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32darkCv, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32brightCv, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32ACCdark, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stSetHdrOffset.u32ACCbrigt, PQ_API_MAX_LEVEL);

    stSetHdrOffsetParam.enHdrProcessScene  = (HI_PQ_HDR_MODE_E)stSetHdrOffset.enHdrProcessScene;
    stSetHdrOffsetParam.u32HdrMode  = stSetHdrOffset.u32HdrMode;
    stSetHdrOffsetParam.u32Bright   = stSetHdrOffset.u32Bright;
    stSetHdrOffsetParam.u32Contrast = stSetHdrOffset.u32Contrast;
    stSetHdrOffsetParam.u32Satu     = stSetHdrOffset.u32Satu;
    stSetHdrOffsetParam.u32Hue      = stSetHdrOffset.u32Hue;
    stSetHdrOffsetParam.u32R        = stSetHdrOffset.u32R;
    stSetHdrOffsetParam.u32G        = stSetHdrOffset.u32G;
    stSetHdrOffsetParam.u32B        = stSetHdrOffset.u32B;
    stSetHdrOffsetParam.u32darkCv   = stSetHdrOffset.u32darkCv;
    stSetHdrOffsetParam.u32brightCv = stSetHdrOffset.u32brightCv;
    stSetHdrOffsetParam.u32ACCdark  = stSetHdrOffset.u32ACCdark;
    stSetHdrOffsetParam.u32ACCbrigt = stSetHdrOffset.u32ACCbrigt;

    s32Ret = HI_MPI_PQ_SetHdrOffsetParam((HI_DRV_DISPLAY_E)enChan, stSetHdrOffsetParam);

    return  s32Ret;
}



/**
 \brief ����ͼ���������
 \attention \n
��
 \param[in] enType: Graph or Video  CNcomment: ���õ���ͼ�λ�����Ƶ CNend
 \param[in] enChan: Destination DISP channel  CNcomment: Ŀ��ͨ���� CNend
 \param[in] stParam:Basic Image Param CNcomment:ͼ���������CNend


 \retval ::HI_SUCCESS CNcomment: �ɹ� CNend

 */


HI_S32 HI_UNF_PQ_SetBasicImageParam(HI_UNF_PQ_IMAGE_TYPE_E enType, HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_PARAM_S stParam)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_IMAGE_PARAM_S stImageParam;
    PQ_API_CHECK_ENID_OVER_RANGE(enType, HI_UNF_PQ_IMAGE_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(stParam.u32Brightness, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stParam.u32Contrast, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stParam.u32Hue, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stParam.u32Saturation, PQ_API_MAX_LEVEL);

    stImageParam.u16Brightness = stParam.u32Brightness;
    stImageParam.u16Contrast   = stParam.u32Contrast;
    stImageParam.u16Hue        = stParam.u32Hue;
    stImageParam.u16Saturation = stParam.u32Saturation;

    s32Ret = HI_MPI_PQ_SetBasicImageParam((HI_MPI_PQ_IMAGE_TYPE_E)enType, (HI_DRV_DISPLAY_E)enChan, stImageParam);

    return s32Ret;
}

/**
 \brief ��ȡͼ���������
 \attention \n
��
 \param[in] enType: Graph or Video  CNcomment: ѡ�����ͼ�λ�����Ƶ CNend
 \param[in] enChan: Destination DISP channel  CNcomment: Ŀ��ͨ���� CNend
 \param[in] pstParam:Basic Image Param CNcomment:ͼ��������� CNend


 \retval ::HI_SUCCESS CNcomment: �ɹ� CNend

 */


HI_S32 HI_UNF_PQ_GetBasicImageParam(HI_UNF_PQ_IMAGE_TYPE_E enType, HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_PARAM_S *pstParam)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_PQ_IMAGE_PARAM_S stImageParam = {0};

    PQ_API_CHECK_NULL_PTR(pstParam);
    PQ_API_CHECK_ENID_OVER_RANGE(enType, HI_UNF_PQ_IMAGE_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);

    s32Ret = HI_MPI_PQ_GetBasicImageParam((HI_MPI_PQ_IMAGE_TYPE_E)enType, (HI_DRV_DISPLAY_E)enChan, &stImageParam);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    pstParam->u32Brightness = stImageParam.u16Brightness;
    pstParam->u32Contrast   = stImageParam.u16Contrast;
    pstParam->u32Hue        = stImageParam.u16Hue;
    pstParam->u32Saturation = stImageParam.u16Saturation;

    return s32Ret;
}


/**
 \brief ��ȡ����
 \attention \n
��

 \param[in] pu32Brightness ����ֵ,��Ч��Χ: 0~100;
 \param[out]

 \retval ::HI_SUCCESS

 */
HI_S32 HI_UNF_PQ_GetBrightness(HI_UNF_DISP_E enChan, HI_U32 *pu32Brightness)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Brightness = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Brightness);

    s32Ret = HI_MPI_PQ_GetBrightness((HI_DRV_DISPLAY_E)enChan, &u32Brightness);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    *pu32Brightness = u32Brightness;

    return s32Ret;
}

/**
 \brief ��������
 \attention \n
��

 \param[in] u32Brightness, ����ֵ,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetBrightness(HI_UNF_DISP_E enChan, HI_U32 u32Brightness)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Brightness, PQ_API_MAX_LEVEL);

    s32Ret = HI_MPI_PQ_SetBrightness((HI_DRV_DISPLAY_E)enChan, u32Brightness);

    return s32Ret;
}


/**
 \brief ��ȡ�Աȶ�
 \attention \n
��

 \param[in]
 \param[out] pu32Contrast �Աȶ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetContrast(HI_UNF_DISP_E enChan, HI_U32 *pu32Contrast)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Contrast = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Contrast);

    s32Ret = HI_MPI_PQ_GetContrast((HI_DRV_DISPLAY_E)enChan, &u32Contrast);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    *pu32Contrast = u32Contrast;
    return s32Ret;
}

/**
 \brief ���öԱȶ�
 \attention \n
��

 \param[in] u32Contrast, �Աȶ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetContrast(HI_UNF_DISP_E enChan, HI_U32 u32Contrast)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Contrast, PQ_API_MAX_LEVEL);

    s32Ret = HI_MPI_PQ_SetContrast((HI_DRV_DISPLAY_E)enChan, u32Contrast);

    return s32Ret;
}

/**
 \brief ��ȡɫ��
 \attention \n
��

 \param[in]
 \param[out] pu32Hue��ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetHue(HI_UNF_DISP_E enChan, HI_U32 *pu32Hue)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Hue = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Hue);

    s32Ret = HI_MPI_PQ_GetHue((HI_DRV_DISPLAY_E)enChan, &u32Hue);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    *pu32Hue = u32Hue;

    return s32Ret;
}

/**
 \brief ����ɫ��
 \attention \n
��

 \param[in] u32Hue��ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetHue(HI_UNF_DISP_E enChan, HI_U32 u32Hue)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Hue, PQ_API_MAX_LEVEL);

    s32Ret = HI_MPI_PQ_SetHue((HI_DRV_DISPLAY_E)enChan, u32Hue);

    return s32Ret;
}

/**
 \brief ����ɫ��
 \attention \n
��

 \param[in] u32Hue��ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetColorTemperature(HI_UNF_DISP_E enChan, HI_UNF_PQ_COLORTEMPERATURE_S stColorTemperature)
{
    HI_PQ_COLORTEMPERATURE_S stPqColorTemperature = {0};

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(stColorTemperature.u32Red, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stColorTemperature.u32Green, PQ_API_MAX_LEVEL);
    PQ_API_CHECK_NUM_OVER_RANGE(stColorTemperature.u32Blue, PQ_API_MAX_LEVEL);

    stPqColorTemperature.u32Red   = stColorTemperature.u32Red;
    stPqColorTemperature.u32Green = stColorTemperature.u32Green;
    stPqColorTemperature.u32Blue  = stColorTemperature.u32Blue;

    return HI_MPI_PQ_SetColorTemperature((HI_DRV_DISPLAY_E)enChan, stPqColorTemperature);
}



/**
 \brief ��ȡɫ��
 \attention \n
��

 \param[in]
 \param[out] pstColorTemperature��ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetColorTemperature(HI_UNF_DISP_E enChan, HI_UNF_PQ_COLORTEMPERATURE_S *pstColorTemperature)
{
    HI_S32 s32Ret;
    HI_PQ_COLORTEMPERATURE_S stColorTemperature = {0};

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pstColorTemperature);

    s32Ret = HI_MPI_PQ_GetColorTemperature((HI_DRV_DISPLAY_E)enChan, &stColorTemperature);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    pstColorTemperature->u32Red   = stColorTemperature.u32Red;
    pstColorTemperature->u32Green = stColorTemperature.u32Green;
    pstColorTemperature->u32Blue  = stColorTemperature.u32Blue;

    return s32Ret;
}


/**
 \brief ��ȡ���Ͷ�
 \attention \n
��

 \param[out] pu32Saturation�����Ͷ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetSaturation(HI_UNF_DISP_E enChan, HI_U32 *pu32Saturation)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Saturation = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Saturation);

    s32Ret = HI_MPI_PQ_GetSaturation((HI_DRV_DISPLAY_E)enChan, &u32Saturation);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    *pu32Saturation = u32Saturation;

    return s32Ret;
}

/**
 \brief ���ñ��Ͷ�
 \attention \n
��

 \param[in] u32Saturation�����Ͷ�,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetSaturation(HI_UNF_DISP_E enChan, HI_U32 u32Saturation)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Saturation, PQ_API_MAX_LEVEL);

    s32Ret = HI_MPI_PQ_SetSaturation((HI_DRV_DISPLAY_E)enChan, u32Saturation);

    return s32Ret;
}

/**
 \brief ��ȡ����ǿ��
 \attention \n
��

 \param[out] pu32NRLevel: ����ȼ�, ��Ч��Χ: 0~100


 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetNR(HI_UNF_DISP_E enChan, HI_U32 *pu32NRLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32NRLevel);

    s32Ret = HI_MPI_PQ_GetTNR(pu32NRLevel);

    return s32Ret;
}

/**
 \brief ���ý���ǿ��
 \attention \n
��

 \param[in] u32NRLevel: ����ȼ�, ��Ч��Χ: 0~100

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetNR(HI_UNF_DISP_E enChan, HI_U32 u32NRLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32NRLevel, PQ_API_MAX_LEVEL);

    s32Ret = HI_MPI_PQ_SetSNR(u32NRLevel);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = HI_MPI_PQ_SetTNR(u32NRLevel);

    return s32Ret;
}

HI_S32 HI_UNF_PQ_GetDNR(HI_UNF_DISP_E enChan, HI_U32 *pu32DNRLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32DNRLevel);

    s32Ret = HI_MPI_PQ_GetDeBlocking(pu32DNRLevel);

    return s32Ret;
}

HI_S32 HI_UNF_PQ_SetDNR(HI_UNF_DISP_E enChan, HI_U32 u32DNRLevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32DNRLevel, PQ_API_MAX_LEVEL);

    s32Ret  = HI_MPI_PQ_SetDeBlocking(u32DNRLevel);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = HI_MPI_PQ_SetDeMosquito(u32DNRLevel);

    return s32Ret;
}


/**
 \brief ��ȡSR��ʾ����
 \attention \n
��

 \param[out] *penType


 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetSRMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_SR_DEMO_E *penType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(penType);

    s32Ret = HI_MPI_PQ_GetSRMode((HI_PQ_SR_DEMO_E *)penType);

    return s32Ret;
}

/**
 \brief ����SR��ʾ����
 \attention \n
��

 \param[in] enType

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetSRMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_SR_DEMO_E enType)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(enType, HI_UNF_PQ_SR_DEMO_BUTT);

    s32Ret = HI_MPI_PQ_SetSRMode((HI_PQ_SR_DEMO_E)enType);

    return s32Ret;
}

/**
 \brief ��ȡ������
 \attention \n
��

 \param[out] pu32Sharpness��������, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetSharpness(HI_UNF_DISP_E enChan, HI_U32 *pu32Sharpness)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Sharpness = 0;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32Sharpness);

    s32Ret = HI_MPI_PQ_GetSharpness(&u32Sharpness);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    *pu32Sharpness = u32Sharpness;

    return s32Ret;
}

/**
 \brief ����������
 \attention \n
��

 \param[in] u32Sharpness��������, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetSharpness(HI_UNF_DISP_E enChan, HI_U32 u32Sharpness)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32Sharpness, PQ_API_MAX_LEVEL);

    s32Ret = HI_MPI_PQ_SetSharpness(u32Sharpness);

    return s32Ret;
}

/**
 \brief ��ȡPQģ�鿪��
 \attention \n
  ��

 \param[in] enFlags
 \param[in] pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetPQModule( HI_UNF_PQ_MODULE_E enFlags, HI_U32 *pu32OnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enFlags, HI_UNF_PQ_MODULE_BUTT);
    PQ_API_CHECK_NULL_PTR(pu32OnOff);

    s32Ret = HI_MPI_PQ_GetPQModule(enFlags, pu32OnOff);

    return s32Ret;
}

/**
 \brief ����PQģ�鿪��
 \attention \n
  ��

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetPQModule( HI_UNF_PQ_MODULE_E enFlags, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enFlags, HI_UNF_PQ_MODULE_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32OnOff,1);

    s32Ret  = HI_MPI_PQ_SetPQModule(enFlags, u32OnOff);

    return s32Ret;
}

/**
 \brief ��������ģʽ����
 \attention \n
��

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetDemo( HI_UNF_PQ_DEMO_E enFlags, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i;

    PQ_API_CHECK_ENID_OVER_RANGE(enFlags, HI_UNF_PQ_DEMO_BUTT);
    PQ_API_CHECK_NUM_OVER_RANGE(u32OnOff, 1);

    if (HI_UNF_PQ_DEMO_ALL == enFlags)
    {
        for (i = HI_UNF_PQ_DEMO_SHARPNESS; i < HI_UNF_PQ_DEMO_ALL; i++)
        {
            s32Ret  = HI_MPI_PQ_SetDemo((HI_UNF_PQ_DEMO_E)i, u32OnOff);
        }
    }
    else
    {
        s32Ret  = HI_MPI_PQ_SetDemo(enFlags, u32OnOff);
    }

    return s32Ret;
}

/**
 \brief ��������ģʽ��ʾ��ʽ
 \attention \n
��

 \param[in] enChan
 \param[in] enMode

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetDemoMode( HI_UNF_DISP_E enChan, HI_UNF_PQ_DEMO_MODE_E enMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_ENID_OVER_RANGE(enMode, HI_UNF_PQ_DEMO_MODE_BUTT);

    s32Ret = HI_MPI_PQ_SetDemoMode((HI_DRV_DISPLAY_E)enChan, (HI_PQ_DEMO_MODE_E)enMode);

    return s32Ret;
}


/**
 \brief ��ȡ����ģʽ��ʾ��ʽ
 \attention \n
��

 \param[in] enChan
 \param[in] enMode

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetDemoMode( HI_UNF_DISP_E enChan, HI_UNF_PQ_DEMO_MODE_E *penMode)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_ENID_OVER_RANGE(enChan, HI_UNF_DISPLAY_BUTT);
    PQ_API_CHECK_NULL_PTR(penMode);

    s32Ret = HI_MPI_PQ_GetDemoMode((HI_DRV_DISPLAY_E)enChan, (HI_PQ_DEMO_MODE_E *)penMode);

    return s32Ret;
}

/**
 \brief ��ȡ��ɫ��ǿ�����ͺ�ǿ��
 \attention \n
��

 \param[out] pstColorEnhanceParam:��ɫ��ǿ�����ͺ�ǿ��;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetColorEnhanceParam(HI_UNF_PQ_COLOR_ENHANCE_S *pstColorEnhanceParam)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_PQ_COLOR_ENHANCE_E    enType;
    HI_UNF_PQ_FLESHTONE_E enFleshToneLevel = HI_UNF_PQ_FLESHTONE_GAIN_OFF;
    HI_UNF_PQ_SIX_BASE_S stSixBase = {0};
    HI_UNF_PQ_COLOR_SPEC_MODE_E enColorMode = HI_UNF_PQ_COLOR_MODE_RECOMMEND;

    PQ_API_CHECK_NULL_PTR(pstColorEnhanceParam);
    PQ_API_CHECK_ENID_OVER_RANGE(pstColorEnhanceParam->enColorEnhanceType, HI_UNF_PQ_COLOR_ENHANCE_BUTT);

    enType = pstColorEnhanceParam->enColorEnhanceType;

    if (HI_UNF_PQ_COLOR_ENHANCE_FLESHTONE == enType)
    {
        s32Ret = HI_MPI_PQ_GetFleshTone(&enFleshToneLevel);
        if (HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }
        pstColorEnhanceParam->unColorGain.enFleshtone = enFleshToneLevel;
    }
    else if (HI_UNF_PQ_COLOR_ENHANCE_SIX_BASE == enType)
    {
        s32Ret = HI_MPI_PQ_GetSixBaseColor(&stSixBase);
        if (HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }

        pstColorEnhanceParam->unColorGain.stSixBase = stSixBase;
    }
    else if (HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE == enType)
    {
        s32Ret = HI_MPI_PQ_GetColorEnhanceMode(&enColorMode);
        if (HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }

        pstColorEnhanceParam->unColorGain.enColorMode = enColorMode;
    }

    return s32Ret;
}


/**
 \brief ������ɫ��ǿ�����ͺ�ǿ��
 \attention \n
��

 \param[out] enColorEnhanceType:��ɫ��ǿ�����ͺ�ǿ��;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetColorEnhanceParam(HI_UNF_PQ_COLOR_ENHANCE_S stColorEnhanceParam)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_PQ_COLOR_ENHANCE_E    enType;
    enType = stColorEnhanceParam.enColorEnhanceType;
    HI_UNF_PQ_SIX_BASE_S stSixBaseColor;
    HI_UNF_PQ_COLOR_SPEC_MODE_E enColorSpecMode;

    PQ_API_CHECK_ENID_OVER_RANGE(stColorEnhanceParam.enColorEnhanceType, HI_UNF_PQ_COLOR_ENHANCE_BUTT);

    if (HI_UNF_PQ_COLOR_ENHANCE_FLESHTONE == enType)
    {
        s32Ret = HI_MPI_PQ_SetFleshTone(stColorEnhanceParam.unColorGain.enFleshtone);

        return s32Ret;
    }
    else if (HI_UNF_PQ_COLOR_ENHANCE_SIX_BASE == enType)
    {
        stSixBaseColor = stColorEnhanceParam.unColorGain.stSixBase;
        s32Ret = HI_MPI_PQ_SetSixBaseColor((HI_PQ_SIX_BASE_COLOR_S *)&stSixBaseColor);

        return s32Ret;
    }
    else if (HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE == enType)
    {
        enColorSpecMode = stColorEnhanceParam.unColorGain.enColorMode;
        s32Ret = HI_MPI_PQ_SetColorEnhanceMode((HI_PQ_COLOR_SPEC_MODE_E)enColorSpecMode);

        return s32Ret;
    }

    return s32Ret;
}


/**
 \brief ��ȡDCI����̬�Աȶ���ǿ����ǿ�ȷ�Χ
 \attention \n
��

 \param[out] pu32DCIlevel:��̬�Աȶȵȼ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetDynamicContrast(HI_U32 *pu32DCIlevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pu32DCIlevel);

    s32Ret = HI_MPI_PQ_GetDciLevel(pu32DCIlevel);

    return s32Ret;
}


/**
 \brief ����DCI����̬�Աȶ���ǿ����ǿ�ȷ�Χ
 \attention \n
��

 \param[in] u32DCIlevel:��̬�Աȶȵȼ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 HI_UNF_PQ_SetDynamicContrast(HI_U32 u32DCIlevel)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NUM_OVER_RANGE(u32DCIlevel, PQ_API_MAX_LEVEL);

    s32Ret = HI_MPI_PQ_SetDciLevel(u32DCIlevel);

    return s32Ret;
}

HI_S32 HI_UNF_PQ_SetDemoCoordinate(HI_U32 u32X)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NUM_OVER_RANGE(u32X, PQ_API_MAX_LEVEL);

    s32Ret = HI_MPI_PQ_SetDemoCoordinate(u32X);

    return s32Ret;
}

HI_S32 HI_UNF_PQ_GetDemoCoordinate(HI_U32 *pu32X)
{
    HI_S32 s32Ret = HI_SUCCESS;

    PQ_API_CHECK_NULL_PTR(pu32X);

    s32Ret = HI_MPI_PQ_GetDemoCoordinate(pu32X);

    return s32Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

