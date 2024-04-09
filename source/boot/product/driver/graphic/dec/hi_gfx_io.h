/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name          : hi_gfx_io.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : ����������
Function List      :
History            :
Date                            Author                     Modification
2018/01/01                      sdk                        Created file
*************************************************************************************************/
#ifndef __HI_GFX_IO_H__
#define __HI_GFX_IO_H__


/*********************************add include here***********************************************/
#include "hi_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition *************************************************/

/*************************** Structure Definition ***********************************************/
typedef struct hiGFXIOINSTANCE_S
{
    HI_CHAR *pAddr;
    HI_U32  u32Length;
    HI_U32  u32Position;
}HIGFX_IO_INSTANCE_S;

/********************** Global Variable declaration *********************************************/



/******************************* API declaration ************************************************/

/***************************************************************************************
* func        : HI_GFX_IOCreate
* description : CNcomment: �������������� CNend\n
* param[in]   : HI_VOID
* retval      : NA
* others:     : NA
***************************************************************************************/
HI_S32 HI_GFX_IOCreate(HIGFX_IO_INSTANCE_S* const pstStream, HI_CHAR* pStremBuf, HI_U32 u32StreamLen);

/***************************************************************************************
* func         : HI_GFX_IORead
* description  : CNcomment: ������ CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 HI_GFX_IORead(HIGFX_IO_INSTANCE_S* const pstStream, HI_VOID *pBuf, HI_U32 BufLen, HI_U32 *pCopyLen, HI_BOOL *pEndFlag);

/***************************************************************************************
* func         : HI_GFX_IOSeek
* description  : CNcomment: �������˵�λ�� CNend\n
* param[in]    : HI_VOID
* retval       : NA
* others:      : NA
***************************************************************************************/
HI_S32 HI_GFX_IOSeek(HIGFX_IO_INSTANCE_S* const pstStream,HI_U32 Offset);

/***************************************************************************************
* func          : HI_GFX_IODestroy
* description   : CNcomment: �������������� CNend\n
* param[in]     : HI_VOID
* retval        : NA
* others:       : NA
***************************************************************************************/
HI_S32 HI_GFX_IODestroy(HIGFX_IO_INSTANCE_S* const pstStream);


#ifdef __cplusplus
}
#endif
#endif /* __HI_GFX_IO_H__ */
