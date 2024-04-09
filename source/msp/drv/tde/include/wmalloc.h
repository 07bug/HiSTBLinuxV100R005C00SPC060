/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : wmalloc.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/
#ifndef  __WMALLOC_H__
#define  __WMALLOC_H__



/*********************************add include here**********************************************/
#include "hi_type.h"


/***********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ********************************************/

/*************************** Enum Definition ***********************************************/

/*************************** Structure Definition ******************************************/

/******************************* API declaration *******************************************/

/******************************* API release ***********************************************/

/******************************************************************************
*Function: wmeminit
*Description: init memery pool. CNcomment:TDE�ڴ�س�ʼ��
*Input: none
*Output: none
*Return: success/error code. CNcomment:�ɹ�/������
others: none
*******************************************************************************/
HI_S32 wmeminit(void);

/******************************************************************************
*Function: wmemterm
*Description: Deinit memery pool. CNcomment:TDE�ڴ��ȥ��ʼ��
*Input: none
*Output: none
*Return: none
others: none
*******************************************************************************/
HI_VOID wmemterm(void);

/******************************************************************************
*Function: wgetphy
*Description: get the physics address of memery. CNcomment:��ȡ�ڴ�������ַ
*Input: ptr  the pointer of memery. CNcomment:ָ���ڴ��ָ��
*Output:  physics address. CNcomment:�����ַ
*Return: none
others: none
*******************************************************************************/
HI_U32 wgetphy(HI_VOID *ptr);

/******************************************************************************
*Function: wgetphy
*Description: get the virtual address of memery. CNcomment:��ȡ�ڴ�������ַ
*Input: phyaddr  physics address. CNcomment:�����ַ
*Output: virtual address. CNcomment:�����ַ
*Return: none
others: none
*******************************************************************************/
HI_VOID *wgetvrt(HI_U32 phyaddr);

/******************************************************************************
*Function: wgetfreenum
*Description:get the number of the free unit. CNcomment:��ȡ�ڴ��ʣ���Unit��Ԫ��
*Input: none
*Output: none
*Return: the number of the free unit. CNcomment:ʣ��ĵ�Ԫ��
others: none
*******************************************************************************/
HI_U32 wgetfreenum(HI_VOID);
#ifndef TDE_BOOT
struct seq_file *wprintinfo(struct seq_file *page);
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__WMALLOC_H__ */
