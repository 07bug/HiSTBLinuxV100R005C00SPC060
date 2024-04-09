/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_unf_pq.h
  Version       : Initial Draft
  Author        : sdk
  Created       : 2014/4/23
  Description   :

******************************************************************************/

#ifndef __HI_UNF_PQ_H__
#define __HI_UNF_PQ_H__

#include "hi_type.h"
#include "hi_unf_disp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */
/******************************************************************************/


/********************************Struct Definition********************************/
/** \addtogroup      PQ */
/** @{ */  /** <!-- [PQ] */

/**<Image Mode Set Different Parameters Under Different Mode*/
/**<CNcomment:ͼ��ģʽѡ���ڲ�ͬ��ģʽ�����ò�ͬ�Ĳ��� CNend*/
typedef enum hiUNF_PQ_IMAGE_MODE_E
{
    HI_UNF_OPTION_MODE_NATURAL    = 0,  /**<Natural mode*/ /**<CNcomment:��Ȼģʽ CNend*/
    HI_UNF_OPTION_MODE_PERSON     = 1,  /**<Person mode*/ /**<CNcomment:����ģʽ CNend*/
    HI_UNF_OPTION_MODE_FILM       = 2,  /**<Film mode*/ /**<CNcomment:��Ӱģʽ CNend*/
    HI_UNF_OPTION_MODE_UD         = 3,  /**<User Defined mode*/ /**<CNcomment:�û��Զ���ģʽ CNend*/
    HI_UNF_OPTION_MODE_NORMAL     = 4,  /**<Normal mode*/ /**<CNcomment:����ģʽ CNend*/
    HI_UNF_OPTION_MODE_VIDEOPHONE = 5,  /**<Video Phone mode*/ /**<CNcomment:���ӵ绰ģʽ CNend*/
    HI_UNF_OPTION_MODE_GALLERY    = 6,  /**<Gallery mode*/ /**<CNcomment:ͼ��ģʽ CNend*/

    HI_UNF_OPTION_MODE_BUTT,
} HI_UNF_PQ_IMAGE_MODE_E;

typedef enum hiUNF_PQ_HDR_MODE_E
{
    HI_UNF_PQ_HDR_PROCESS_SCENE_HDR10_TO_SDR   = 0,
    HI_UNF_PQ_HDR_PROCESS_SCENE_HDR10_TO_HDR10 = 1,
    HI_UNF_PQ_HDR_PROCESS_SCENE_HDR10_TO_HLG   = 2,
    HI_UNF_PQ_HDR_PROCESS_SCENE_HLG_TO_SDR     = 3,
    HI_UNF_PQ_HDR_PROCESS_SCENE_HLG_TO_HDR10   = 4,
    HI_UNF_PQ_HDR_PROCESS_SCENE_HLG_TO_HLG     = 5,
    HI_UNF_PQ_HDR_PROCESS_SCENE_SLF_TO_SDR     = 6,
    HI_UNF_PQ_HDR_PROCESS_SCENE_SLF_TO_HDR10   = 7,
    HI_UNF_PQ_HDR_PROCESS_SCENE_SLF_TO_HLG     = 8,
    HI_UNF_PQ_HDR_PROCESS_SCENE_SDR_TO_SDR     = 9,
    HI_UNF_PQ_HDR_PROCESS_SCENE_SDR_TO_HDR10   = 10,
    HI_UNF_PQ_HDR_PROCESS_SCENE_SDR_TO_HLG     = 11,

    HI_UNF_PQ_HDR_PROCESS_SCENE_BUTT,
} HI_UNF_PQ_HDR_PROCESS_SCENE_E;

/******************************************************************************/
typedef struct hiUNF_PQ_SETHDROFFSET_S
{
    HI_UNF_PQ_HDR_PROCESS_SCENE_E enHdrProcessScene;
    HI_U32       u32HdrMode;
    HI_U32       u32Bright;
    HI_U32       u32Contrast;
    HI_U32       u32Satu;
    HI_U32       u32Hue;
    HI_U32       u32R;
    HI_U32       u32G;
    HI_U32       u32B;
    HI_U32       u32darkCv;
    HI_U32       u32brightCv;
    HI_U32       u32ACCdark;
    HI_U32       u32ACCbrigt;
} HI_UNF_PQ_SETHDROFFSET_S;
/******************************************************************************/

/**<Demo Mode*/
/**<CNcomment:����ģʽ CNend*/
typedef enum hiUNF_PQ_DEMO_E
{
    HI_UNF_PQ_DEMO_SHARPNESS = 0,   /**<Sharpen */ /**<CNcomment:�� CNend*/
    HI_UNF_PQ_DEMO_DCI,             /**<Dynamic Contrast Improvement */ /**<CNcomment:�Զ��Աȶȵ��� CNend*/
    HI_UNF_PQ_DEMO_COLOR,           /**<Automatic Color Management */ /**<CNcomment:������ɫ���� CNend*/
    HI_UNF_PQ_DEMO_SR,              /**<Super Resolution */ /**<CNcomment:�����ֱ��� CNend*/
    HI_UNF_PQ_DEMO_TNR,             /**<Time Noise Reduction */ /**<CNcomment:ʱ���������� CNend*/
    HI_UNF_PQ_DEMO_DEI,             /**<De interlace */ /**<CNcomment:ȥ���� CNend*/
    HI_UNF_PQ_DEMO_DBM,             /**<Digital Noise Reduction; include DB DM DR DS*/ /**<CNcomment:������������ CNend*/
    HI_UNF_PQ_DEMO_SNR,             /**<Space Noise Reduction */ /**<CNcomment:������������ CNend*/
    HI_UNF_PQ_DEMO_ALL,             /**<All Algorithm */ /**<CNcomment:ȫ���㷨 CNend*/

    HI_UNF_PQ_DEMO_BUTT
} HI_UNF_PQ_DEMO_E;

/**<Demo Display Mode*/
/**<CNcomment:������ʾģʽ CNend*/
typedef enum hiUNF_PQ_DEMO_MODE_E
{
    HI_UNF_PQ_DEMO_MODE_FIXED_R,    /**<Fixed Enable Right */ /**<CNcomment:�̶��Ҳ�ʹ�� CNend*/
    HI_UNF_PQ_DEMO_MODE_FIXED_L,    /**<Fixed Enable Left */ /**<CNcomment:�̶����ʹ�� CNend*/
    HI_UNF_PQ_DEMO_MODE_SCROLL_R,   /**<Enable Right; and Roll from Left to right */ /**<CNcomment:�Ҳ�ʹ�ܣ����������ƶ� CNend*/
    HI_UNF_PQ_DEMO_MODE_SCROLL_L,   /**<Enable Left; and Roll from Left to right */ /**<CNcomment:���ʹ�ܣ����������ƶ� CNend*/

    HI_UNF_PQ_DEMO_MODE_BUTT
} HI_UNF_PQ_DEMO_MODE_E;

/**<Algorithm Moudle*/
/**<CNcomment:�㷨ģ�� CNend*/
typedef enum hiUNF_PQ_MODULE_E
{
    HI_UNF_PQ_MODULE_SHARPNESS = 0, /**<Sharpen */ /**<CNcomment:�� CNend*/
    HI_UNF_PQ_MODULE_DCI,           /**<Dynamic Contrast Improvement */ /**<CNcomment:�Զ��Աȶȵ��� CNend*/
    HI_UNF_PQ_MODULE_COLOR,         /**<Automatic Color Management */ /**<CNcomment:������ɫ���� CNend*/
    HI_UNF_PQ_MODULE_SR,            /**<Super Resolution */ /**<CNcomment:�����ֱ��� CNend*/
    HI_UNF_PQ_MODULE_TNR,           /**<Time Noise Reduction */ /**<CNcomment:ʱ���������� CNend*/
    HI_UNF_PQ_MODULE_DBM,           /**<Digital Noise Reduction; include DB DM DR DS*/ /**<CNcomment:������������ CNend*/
    HI_UNF_PQ_MODULE_SNR,           /**<Space Noise Reduction */ /**<CNcomment:������������ CNend*/
    HI_UNF_PQ_MODULE_MCDI,          /**<Motion Compensation DeInterlace */ /**<CNcomment:�����˶�������ȥ�����㷨 CNend*/

    HI_UNF_PQ_MODULE_ALL,           /**<All Algorithm */ /**<CNcomment:ȫ���㷨 CNend*/

    HI_UNF_PQ_MODULE_BUTT
} HI_UNF_PQ_MODULE_E;

/**<Spuer Resolution Demo Mode*/
/**<CNcomment:SR��ʾģʽ CNend*/
typedef enum hiUNF_PQ_SR_DEMO_E
{
    HI_UNF_PQ_SR_DISABLE  = 0, /**<Close SR */ /**<CNcomment:��SR,ֻ������ CNend*/
    HI_UNF_PQ_SR_ENABLE_R,     /**<SR open at right hand side */ /**<CNcomment:�ұ�SR CNend*/
    HI_UNF_PQ_SR_ENABLE_L,     /**<SR open at left hand side */ /**<CNcomment:���SR CNend*/
    HI_UNF_PQ_SR_ENABLE_A,     /**<SR open all screen */ /**<CNcomment:ȫ��SR CNend*/

    HI_UNF_PQ_SR_DEMO_BUTT
} HI_UNF_PQ_SR_DEMO_E;

/**<Custom Colors Parameter*/
/**<CNcomment:�Զ�����ɫ���� CNend*/
typedef struct  hiUNF_PQ_SIX_BASE_S
{
    HI_U32  u32Red;       /**<Red; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
    HI_U32  u32Green;     /**<Green; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
    HI_U32  u32Blue;      /**<Blue; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/

    HI_U32  u32Cyan;      /**<Cyan; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
    HI_U32  u32Magenta;   /**<Magenta; Range:0~100 */ /**<CNcomment:Ʒ�죻��Χ:0~100 CNend*/
    HI_U32  u32Yellow;    /**<Yellow; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
} HI_UNF_PQ_SIX_BASE_S;

/**<Custom Color Temperature Parameter*/
/**<CNcomment:�Զ���ɫ�²��� CNend*/
typedef struct  hiUNF_PQ_COLORTEMPERATURE_S
{
    HI_U32  u32Red;       /**<Red; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
    HI_U32  u32Green;     /**<Green; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
    HI_U32  u32Blue;      /**<Blue; Range:0~100 */ /**<CNcomment:��ɫ����Χ:0~100 CNend*/
} HI_UNF_PQ_COLORTEMPERATURE_S;

/**<Portrait Colors Parameter*/
/**<CNcomment:����ģʽ���� CNend*/
typedef enum hiUNF_PQ_FLESHTONE_E
{
    HI_UNF_PQ_FLESHTONE_GAIN_OFF  = 0,   /**<Portrait Model Strength Off */ /**<CNcomment:����ģʽ�ر� CNend*/
    HI_UNF_PQ_FLESHTONE_GAIN_LOW  = 1,   /**<Portrait Model Strength Low */ /**<CNcomment:����ģʽǿ�ȵ� CNend*/
    HI_UNF_PQ_FLESHTONE_GAIN_MID  = 2,   /**<Portrait Model Strength Middle */ /**<CNcomment:����ģʽǿ���� CNend*/
    HI_UNF_PQ_FLESHTONE_GAIN_HIGH = 3,   /**<Portrait Model Strength High */ /**<CNcomment:����ģʽǿ�ȸ� CNend*/

    HI_UNF_PQ_FLESHTONE_GAIN_BUTT
}  HI_UNF_PQ_FLESHTONE_E;

/**<Color Optimization Model*/
/**<CNcomment:��ɫ��ǿ���� CNend*/
typedef enum hiUNF_PQ_COLOR_SPEC_MODE_E
{
    HI_UNF_PQ_COLOR_MODE_RECOMMEND  = 0, /**<Optimization Model */ /**<CNcomment:����ģʽ CNend*/
    HI_UNF_PQ_COLOR_MODE_BLUE       = 1, /**<Blue Model */ /**<CNcomment:��ɫ��ǿģʽ CNend*/
    HI_UNF_PQ_COLOR_MODE_GREEN      = 2, /**<Green Model */ /**<CNcomment:��ɫ��ǿģʽ CNend*/
    HI_UNF_PQ_COLOR_MODE_BG         = 3, /**<Cyan Model */ /**<CNcomment:������ǿģʽ CNend*/
    HI_UNF_PQ_COLOR_MODE_ORIGINAL   = 4, /**<Original Model */ /**<CNcomment:ԭʼ��ɫģʽ CNend*/

    HI_UNF_PQ_COLOR_MODE_BUTT
} HI_UNF_PQ_COLOR_SPEC_MODE_E;

/**<Intelligent Colors Form*/
/**<CNcomment:������ɫ���� CNend*/
typedef enum hiUNF_PQ_COLOR_ENHANCE_E
{
    HI_UNF_PQ_COLOR_ENHANCE_FLESHTONE       = 0,  /**<Portrait Model */ /**<CNcomment:����ģʽ CNend*/
    HI_UNF_PQ_COLOR_ENHANCE_SIX_BASE        = 1,  /**<Custom Model */ /**<CNcomment:�Զ�����ɫ CNend*/
    HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE = 2,  /**<Special Color Model */ /**<CNcomment:��ɫ��ǿģʽ CNend*/

    HI_UNF_PQ_COLOR_ENHANCE_BUTT
} HI_UNF_PQ_COLOR_ENHANCE_E;

/**<Intelligent Colors Parameter*/
/**<CNcomment:������ɫ���� CNend*/
typedef struct  hiUNF_PQ_COLOR_ENHANCE_S
{
    HI_UNF_PQ_COLOR_ENHANCE_E  enColorEnhanceType;  /**<Color Model */ /**<CNcomment��ǿ���� CNend*/
    union
    {
        HI_UNF_PQ_FLESHTONE_E        enFleshtone;   /**<Portrait Model Parameter */ /**<CNcomment����ģʽ���� CNend*/
        HI_UNF_PQ_SIX_BASE_S         stSixBase;     /**<Custom Model Parameter */ /**<CNcomment�Զ�����ɫ���� CNend*/
        HI_UNF_PQ_COLOR_SPEC_MODE_E  enColorMode;   /**<Special Color Model Parameter */ /**<CNcomment��ɫ��ǿ���� CNend*/
    } unColorGain;
} HI_UNF_PQ_COLOR_ENHANCE_S;

typedef enum hiUNF_PQ_IMAGE_TYPE_E
{
    HI_UNF_PQ_IMAGE_GRAPH = 0,          /**<graph image */ /**<CNcomment: ͼ��ͼ�� CNend*/
    HI_UNF_PQ_IMAGE_VIDEO,              /**<video image */ /**<CNcomment: ��Ƶͼ�� CNend*/

    HI_UNF_PQ_IMAGE_BUTT
} HI_UNF_PQ_IMAGE_TYPE_E;

typedef struct hiUNF_PQ_IMAGE_PARAM_S
{
    HI_U32       u32Brightness;         /**<Brightness; Range:0~100; recommended: 50 */ /**<CNcomment:���ȣ���Χ: 0~100���Ƽ�ֵ: 50 CNend*/
    HI_U32       u32Contrast;           /**<Contrast; Range:0~100; recommended: 50 */ /**<CNcomment:�Աȶȣ���Χ: 0~100���Ƽ�ֵ: 50 CNend*/
    HI_U32       u32Hue;                /**<HuePlus; Range:0~100; recommended: 50 */ /**<CNcomment:ɫ������Χ: 0~100���Ƽ�ֵ: 50 CNend*/
    HI_U32       u32Saturation;         /**<Saturation; Range:0~100; recommended: 50 */ /**<CNcomment:���Ͷȣ���Χ: 0~100���Ƽ�ֵ: 50 CNend*/
} HI_UNF_PQ_IMAGE_PARAM_S;

/******************************* API Declaration *****************************/
/** \addtogroup      PQ */
/** @{ */  /** <!-- [PQ] */

/******************************************************************************/
/**
 \brief Set PQ mode . CNcomment: ����ͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] enImageMode Destination DISP channel PQ mode CNcomment: Ŀ��ͨ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_SetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E enImageMode);


/**
 \brief Get PQ mode . CNcomment: ��ȡͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] penImageMode  pointer of image mode CNcomment: ָ�����ͣ�ָ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_GetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E *penImageMode);

/**
 \brief Set the default PQ configuration for video parameter test.  CNcomment: Ϊ����ָ���������PQ ��Ĭ��ֵCNend
 \attention \n
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
 N/A CNcomment: �� CNend
*/
HI_S32 HI_UNF_PQ_SetDefaultParam(HI_VOID);


/**
 \brief Initializes the picture quality unit (PQU). CNcomment: ��ʼ��PQ CNend
 \attention \n
Before calling the PQU, you must call this application programming interface (API).
CNcomment: ����PQģ��Ҫ�����ȵ��øýӿ� CNend
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \retval ::HI_ERR_PQ_DEV_NOT_EXIST No PQ device exists. CNcomment: �豸������ CNend
 \retval ::HI_ERR_PQ_NOT_DEV_FILE The file is not a PQ file. CNcomment: �ļ����豸 CNend
 \retval ::HI_ERR_PQ_DEV_OPENED The PQ device fails to be started. CNcomment: ���豸ʧ�� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_Init(HI_VOID);


/**
 \brief Deinitializes the PQU. CNcomment: ȥ��ʼ��PQ CNend
 \attention \n
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_DeInit(HI_VOID);


/**
 \brief Get Brightness. CNcomment:��ȡ���� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32Brightness   CNcomment: ����ֵ����Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetBrightness(HI_UNF_DISP_E enChan, HI_U32 *pu32Brightness);


/**
 \brief Set Brightness. CNcomment:�������� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Brightness; Range:0~100 CNcomment: ����ֵ����Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetBrightness(HI_UNF_DISP_E enChan, HI_U32 u32Brightness);


/**
 \brief Get Contrast. CNcomment:��ȡ�Աȶ� CNend
 \attention \n
 \param[in] enChan Destination DISP channel  CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32Contrast; Range:0~100  CNcomment: �Աȶȣ���Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetContrast(HI_UNF_DISP_E enChan, HI_U32 *pu32Contrast);


/**
 \brief Set Contrast. CNcomment:���öԱȶ� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Contrast; Range:0~100  CNcomment: �Աȶȣ���Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetContrast(HI_UNF_DISP_E enChan, HI_U32 u32Contrast);


/**
 \brief Get Saturation. CNcomment:��ȡ���Ͷ� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32Saturation; Range:0~100  CNcomment: ���Ͷȣ���Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetSaturation(HI_UNF_DISP_E enChan, HI_U32 *pu32Saturation);


/**
 \brief Set Saturation. CNcomment:���ñ��Ͷ� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Saturation; Range:0~100  CNcomment: ���Ͷȣ���Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetSaturation(HI_UNF_DISP_E enChan, HI_U32 u32Saturation);


/**
 \brief Get Hue. CNcomment:��ȡɫ�� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32Hue; Range:0~100  CNcomment: ɫ������Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetHue(HI_UNF_DISP_E enChan, HI_U32 *pu32Hue);


/**
 \brief Set Hue. CNcomment:����ɫ�� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Hue; Range:0~100  CNcomment: ɫ������Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success  CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetHue(HI_UNF_DISP_E enChan, HI_U32 u32Hue);

/**
\brief  set color temperature. CNcomment:����ɫ�� CNend
\attention \n
none.CNcomment:�� CNend
\param[in] enDisp              DISP channel ID.CNcomment:DISPͨ���� CNend
\param[in] colortemp           temperature value. the range is 0~100, 0 means the min value. \n
CNcomment:��ʾ���ɫ������ֵ����ΧΪ0��100��0����ʾ��Сɫ�����棻100����ʾ���ɫ������ CNend
none.CNcomment:�� CNend
*/
HI_S32 HI_UNF_PQ_SetColorTemperature(HI_UNF_DISP_E enChan, HI_UNF_PQ_COLORTEMPERATURE_S stColorTemperature);


/**
\brief  set color temperature. CNcomment:����ɫ�� CNend
\attention \n
none.CNcomment:�� CNend
\param[in] enDisp              DISP channel ID.CNcomment:DISPͨ���� CNend
\param[in] colortemp           temperature value. the range is 0~100, 0 means the min value. \n
CNcomment:��ʾ���ɫ������ֵ����ΧΪ0��100��0����ʾ��Сɫ�����棻100����ʾ���ɫ������ CNend
\see \n
none.CNcomment:�� CNend
*/
HI_S32 HI_UNF_PQ_GetColorTemperature(HI_UNF_DISP_E enChan, HI_UNF_PQ_COLORTEMPERATURE_S *pstColorTemperature);

/**
 \brief Set Basic image para. CNcomment:����ͼ���������. CNend
 \attention \n
 \param[in] enType: Graph or Video  CNcomment: ���õ���ͼ�λ�����Ƶ CNend
 \param[in] enChan: Destination DISP channel  CNcomment: Ŀ��ͨ���� CNend
 \param[in] stParam:Basic Image Param CNcomment:ͼ���������CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetBasicImageParam(HI_UNF_PQ_IMAGE_TYPE_E enType, HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_PARAM_S stParam);


/**
 \brief Get Basic image para. CNcomment:��ȡͼ��������� CNend
 \attention \n
 \param[in] enType: Graph or Video  CNcomment: ѡ�����ͼ�λ�����Ƶ CNend
 \param[in] enChan: Destination DISP channel  CNcomment: Ŀ��ͨ���� CNend
 \param[in] pstParam:Basic Image Param CNcomment:ͼ��������� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetBasicImageParam(HI_UNF_PQ_IMAGE_TYPE_E enType, HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_PARAM_S *pstParam);


/**
 \brief Get SR Demo Mode. CNcomment:��ȡSR��ʾ���� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] *penType, SR Demo Mode  CNcomment:ָ�룬SR ��ʾģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetSRMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_SR_DEMO_E *penType);


/**
 \brief  Set SR Demo Mode. CNcomment:����SR��ʾ���� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] enType, SR Demo Mode  CNcomment:SR ��ʾģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetSRMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_SR_DEMO_E enType);


/**
 \brief Get Sharpness. CNcomment:��ȡ������ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] pu32Sharpness; Range:0~100  CNcomment: �����ȣ���Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetSharpness(HI_UNF_DISP_E enChan, HI_U32 *pu32Sharpness);


/**
 \brief Set Sharpness. CNcomment:���������� CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] u32Sharpness; Range:0~100  CNcomment: �����ȣ���Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS  Success CNcomment: �ɹ� CNend
 */
HI_S32 HI_UNF_PQ_SetSharpness(HI_UNF_DISP_E enChan, HI_U32 u32Sharpness);

/**
 \brief Get Color Enhance Type and Para. CNcomment:��ȡ��ɫ��ǿ�����ͺͲ��� CNend
 \attention \n
 \param[out] pstColorEnhanceParam  CNcomment:��ɫ��ǿ�����ͺͲ��� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetColorEnhanceParam(HI_UNF_PQ_COLOR_ENHANCE_S *pstColorEnhanceParam);


/**
 \brief Set Color Enhance Type and Para. CNcomment:������ɫ��ǿ�����ͺͲ��� CNend
 \attention \n
 \param[out] stColorEnhanceParam  CNcomment:��ɫ��ǿ�����ͺͲ��� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetColorEnhanceParam(HI_UNF_PQ_COLOR_ENHANCE_S stColorEnhanceParam);


/** Dynamic Contrast Improvement(DCI)
 \brief Get Dynamic Contrast Improvement(DCI) Range  CNcomment:��ȡDCI����̬�Աȶ���ǿ����ǿ�ȷ�Χ CNend
 \attention \n
 \param[out] pu32DCIlevel; Range:0~100 CNcomment:��̬�Աȶȵȼ�����Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetDynamicContrast(HI_U32 *pu32DCIlevel);


/**
 \brief Get DCI Range  CNcomment:��ȡDCIǿ�ȷ�Χ CNend
 \attention \n
 \param[in] u32DCIlevel; Range:0~100 CNcomment:��̬�Աȶȵȼ�����Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetDynamicContrast(HI_U32 u32DCIlevel);


/**
 \brief Get noise reduction strength CNcomment:��ȡ����ǿ�� CNend
 \attention \n
 \param[out] pu32NRLevel: noise reduction level; Range:0~100 CNcomment:����ȼ�����Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetNR(HI_UNF_DISP_E enChan, HI_U32 *pu32NRLevel);


/**
 \brief  Set noise reduction strength CNcomment:���ý���ǿ�� CNend
 \attention \n
 \param[in] u32NRLevel: noise reduction level; Range:0~100 CNcomment:����ȼ�����Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetNR(HI_UNF_DISP_E enChan, HI_U32 u32NRLevel);

/**
 \brief Get digital noise reduction strength CNcomment:��ȡ���ֽ���ǿ�� CNend
 \attention \n
 \param[out] pu32NRLevel: noise reduction level; Range:0~100 CNcomment:���ֽ���ȼ�����Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetDNR(HI_UNF_DISP_E enChan, HI_U32 *pu32DNRLevel);


/**
 \brief  Set digital noise reduction strength CNcomment:�������ֽ���ǿ�� CNend
 \attention \n
 \param[in] u32NRLevel: noise reduction level; Range:0~100 CNcomment:���ֽ���ȼ�����Ч��Χ: 0~100 CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetDNR(HI_UNF_DISP_E enChan, HI_U32 u32DNRLevel);



/**
 \brief  Set Algorithm Moudle on-off  CNcomment:�����㷨ģ�鿪�� CNend
 \attention \n
 \param[in] enFlags   CNcomment:�㷨ģ�� CNend
 \param[in] u32OnOff  CNcomment:�㷨���� CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
 */
HI_S32 HI_UNF_PQ_SetPQModule(HI_UNF_PQ_MODULE_E enFlags, HI_U32 u32OnOff);


/**
 \brief Get Algorithm Moudle on-off  CNcomment:��ȡ�㷨ģ�鿪�� CNend
 \attention \n
 \param[in]  enFlags   CNcomment:�㷨ģ�� CNend
 \param[out] pu32OnOff CNcomment:�㷨���� CNend
 \retval ::HI_SUCCESS  Success CNcomment:�ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetPQModule(HI_UNF_PQ_MODULE_E enFlags, HI_U32 *pu32OnOff);


/**
 \brief Set Demo Mode on-off  CNcomment:��������ģʽ���� CNend
 \attention \n
 \param[in] enFlags   CNcomment:�㷨ģ�� CNend
 \param[in] u32OnOff  CNcomment:����ģʽ���� CNend
 \retval ::HI_SUCCESS CNcomment:�ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetDemo(HI_UNF_PQ_DEMO_E enFlags, HI_U32 u32OnOff);


/**
 \brief Set Demo Display Mode  CNcomment:����������ʾģʽ CNend
 \attention \n
 \param[in] enChan    CNcomment:��ʾͨ�� CNend
 \param[in] enMode    CNcomment:������ʾģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetDemoMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_DEMO_MODE_E enMode);


/**
 \brief Get Demo Display Mode  CNcomment:��ȡ������ʾģʽ CNend
 \attention \n
 \param[in] enChan    CNcomment:��ʾͨ�� CNend
 \param[out] enMode   CNcomment:������ʾģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetDemoMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_DEMO_MODE_E *penMode);

/**
 \brief Set Demo Display Mode Coordinate CNcomment:����������ʾ���� CNend
 \attention \n
 \param[in] u32X Range:0~100 Default:50 CNcomment:������ʾ�ֽ��ߺ����� ��Ч��Χ:0~100 Ĭ��ֵ:50 CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend

 */
HI_S32 HI_UNF_PQ_SetDemoCoordinate(HI_U32 u32X);


/**
 \brief Get Demo Display Mode Coordinate CNcomment:��ȡ������ʾģʽ���� CNend
 \attention \n
 \param[out] pu32X  Range:0~100 Default:50 CNcomment:������ʾ�ֽ��ߺ����� ��Ч��Χ:0~100 Ĭ��ֵ:50 CNend
 \retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend

 */
HI_S32 HI_UNF_PQ_GetDemoCoordinate(HI_U32 *pu32X);


/** @} */  /** <!-- ==== API Declaration End ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* End of #ifndef __HI_UNF_PQ_H__ */


