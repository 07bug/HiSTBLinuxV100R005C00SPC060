/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : jpeg_decode.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : decode images
                     CNcomment: JPEGͼƬ����CNend\n
Function List      :
History            :
Date                          Author                     Modification
2018/01/01                    sdk                         Created file
************************************************************************************************/
#ifndef  __JPEG_DECODE_H__
#define  __JPEG_DECODE_H__


/*********************************add include here**********************************************/

#include "hi_type.h"

/***************************** Macro Definition ************************************************/


/***************************** Structure Definition ********************************************/

/***************************** Global Variable declaration *************************************/

/***************************** API forward declarations ****************************************/

/***************************** API realization *************************************************/


/***************************************************************************************
* func          : JPEG_ADP_CreateDecoder
* description   : CNcomment:���������� CNend\n
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 JPEG_ADP_CreateDecode(HI_U32 *pDecHandle,HI_CHAR* pSrcBuf,HI_U32 u32SrcLen);

/***************************************************************************************
* func          : JPEG_ADP_DestroyDecoder
* description   : CNcomment:���ٽ����� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 JPEG_ADP_DestroyDecode(HI_U32 DecHandle);

/***************************************************************************************
* func         : JPEG_ADP_GetImgInfo
* description  : CNcomment:��ȡͼƬ��ϢCNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 JPEG_ADP_GetImgInfo(HI_U32 DecHandle, HI_HANDLE hSurface);

/***************************************************************************************
* func        : JPEG_ADP_StartDecode
* description : CNcomment:��ʼ����CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 JPEG_ADP_StartDecode(HI_U32 DecHandle, HI_HANDLE hSurface);

#endif /*__JPEG_DECODE_H__ */
