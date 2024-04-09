/***************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
****************************************************************************************************
File Name          : hi_gfx_show.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : show input data from base through vo or gfx layer
                     CNcomment: ͨ��ͼ�β������Ƶ�㽫�����������ʾ���� CNend\n
Function List      :
History            :
Date                          Author                     Modification
2018/01/01                    sdk                        Created file
****************************************************************************************************/

#ifndef  __HI_GFX_SHOW_H__
#define  __HI_GFX_SHOW_H__


/*********************************add include here**************************************************/

#include "hi_type.h"

/***************************** Macro Definition ****************************************************/

#define CONFIG_GFX_DISP_LOGO_SD        0
#define CONFIG_GFX_DISP_LOGO_HD        1
#define CONFIG_GFX_DISP_LOGO_CHANNEL   2
#define CONFIG_GFX_LAYER_BUF_NUM       2

/*************************** Structure Definition **************************************************/
typedef enum hiGfxPixelFormatE
{
    HI_GFX_PF_4444       = 3,
    HI_GFX_PF_0444       = 4,
    HI_GFX_PF_1555       = 5,
    HI_GFX_PF_0555       = 6,
    HI_GFX_PF_565        = 7,
    HI_GFX_PF_8565       = 8,
    HI_GFX_PF_8888       = 9,
    HI_GFX_PF_0888       = 10,
    HI_GFX_PF_YUV400     = 11,
    HI_GFX_PF_YUV420     = 12,
    HI_GFX_PF_YUV444     = 13,
    HI_GFX_PF_YUV422_12  = 14,
    HI_GFX_PF_YUV422_21  = 15,
    HI_GFX_PF_AYCbCr8888 = 16,
    HI_GFX_PF_BUTT
}HI_GFX_PF_E;

typedef struct hiBaseGfxLogoInfoS
{
    HI_BOOL DispToSD;
    HI_U32 LogoDataLen;
    HI_U32 LogoDataBuf;
    HI_U32 DispVirtScreenWidth[CONFIG_GFX_DISP_LOGO_CHANNEL];
    HI_U32 DispVirtScreenHeight[CONFIG_GFX_DISP_LOGO_CHANNEL];
    HI_GFX_PF_E DispColorFmt[CONFIG_GFX_DISP_LOGO_CHANNEL];
}HI_BASE_GFX_LOGO_INFO;

/********************** Global Variable declaration ************************************************/


/******************************* API declaration ***************************************************/

/***************************************************************************************
* func          :  HI_GFX_ShowLogo
* description   :  display the input logo by graphic or vo
                   CNcomment: ͨ��ͼ�β���������㽫�����logo��������ʾ����CNend\n
* param[in]     : pInputBaseLogoInfo
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_ShowLogo(HI_BASE_GFX_LOGO_INFO *pInputBaseLogoInfo);

/***************************************************************************************
* func          : HI_GFX_ShowAnimation
* description   : show animation
                  CNcomment: ��ʾ�������� CNend\n
* param[in]     : DataBuf    CNcomment: ����ͼƬ����buffer CNend\n
* param[in]     : DataLen    CNcomment: ͼƬ���ݴ�С       CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_ShowAnimation(HI_U32 DataBuf, HI_U32 DataLen);

#endif /*__HI_GFX_SHOW_H__ */
