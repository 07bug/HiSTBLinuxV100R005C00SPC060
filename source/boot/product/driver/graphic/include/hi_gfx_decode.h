/**************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
***************************************************************************************************
File Name          : hi_gfx_decode.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : decode images
                     CNcomment: ����ͼƬ CNend\n
Function List      :
History            :
Date                          Author                     Modification
2018/01/01                     sdk                        Created file
***************************************************************************************************/

#ifndef  __HI_GFX_DECODE_H__
#define  __HI_GFX_DECODE_H__

/*********************************add include here*************************************************/

#include "hi_type.h"

/***************************** Macro Definition ***************************************************/

/*************************** Structure Definition *************************************************/

/********************** Global Variable declaration ***********************************************/


/******************************* API declaration **************************************************/
/***************************************************************************************
* func          : HI_GFX_DecImg
* description   : decode imag to surface
                  CNcomment: ����ͼƬ��surface
                             ֻ��֧��24/32λ��bmpͼƬ��baseline��ʽ��jpeg���ָ�ʽ��ͼƬ���룬CNend\n
* param[in]     : DataBuf    CNcomment: ����ͼƬ����buffer CNend\n
* param[in]     : DataLen    CNcomment: ͼƬ���ݴ�С CNend\n
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_DecImg(HI_U32 DataBuf, HI_U32 DataLen, HI_HANDLE *pSurface);

#endif /*__HI_GFX_DECODE_H__ */
