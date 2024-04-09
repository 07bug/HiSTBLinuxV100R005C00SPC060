/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name          : hi_gfx_mem.h
Version            : Initial Draft
Author             :
Created            : 2018/01/01
Description        : memory manage
                     CNcomment: �ڴ���� CNend\n
Function List      :
History            :
Date                         Author                     Modification
2018/01/01                   sdk                        Created file
************************************************************************************************/

#ifndef  __HI_GFX_MEM_H__
#define  __HI_GFX_MEM_H__

/*********************************add include here**********************************************/
#include "hi_type.h"

/***************************** Macro Definition ************************************************/
#define HI_GFX_RESERVE_Malloc(size,module)    BOOT_GFX_RESERVE_Alloc(size,module)
#define HI_GFX_MMZ_Malloc(size,module)        BOOT_GFX_MMZ_Alloc(size)
#define HI_GFX_MMZ_Free(phy)                  BOOT_GFX_MMZ_Free(phy)
#define HI_GFX_Malloc(size,module)            BOOT_GFX_Malloc(size)
#define HI_GFX_Free(phy)                      BOOT_GFX_Free(phy)
#define HI_GFX_Memcmp(phy,size)               BOOT_GFX_Memcmp(phy,size)
/*************************** Structure Definition **********************************************/


/********************** Global Variable declaration ********************************************/

/******************************* API declaration ***********************************************/

/*****************************************************************************
* func          : BOOT_GFX_RESERVE_Alloc
* description   : ���䱣���ڴ�
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_RESERVE_Alloc(HI_U32 u32Size,HI_CHAR* pModuleName);


/*****************************************************************************
* func          : BOOT_GFX_MMZ_Alloc
* description   : ���������������ַ��boot��������ַҲ�����������ַ����ֱ�Ӷ�д,
                  ����ʹ�ñ����ڴ�
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_MMZ_Alloc(HI_U32 u32Size);

/*****************************************************************************
* func         : BOOT_GFX_MMZ_Free
* description  : �ͷŵ�ַ
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_MMZ_Free(HI_CHAR* pPhyAddr);

/*****************************************************************************
* func          : BOOT_GFX_Malloc
* description   : ʹ��malloc�����ڴ棬ʹ�����ͷŸ���������ʹ��,С�ڴ�
                  ʹ�øýӿڱ���handle�ȣ������ڴ���Ƭ
* retval        : HI_SUCCESS
* retval        : HI_FAILURE
*****************************************************************************/
HI_CHAR* BOOT_GFX_Malloc(HI_U32 u32Size);

/*****************************************************************************
* func         : BOOT_GFX_Free
* description  : �ͷŵ�ַ
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_Free(HI_CHAR* pVirAddr);

/*****************************************************************************
* func         : BOOT_GFX_Memcmp
* description  : ��ַ����У�飬����ĵ�ַ�����Ǳ�ģ�����ģ�Լ���׳ɵģ�������
                 10���ֽ���Ϊ�Ƿ��ڴ�Խ��У��
* retval       : HI_SUCCESS
* retval       : HI_FAILURE
*****************************************************************************/
HI_VOID BOOT_GFX_Memcmp(HI_CHAR* pPhyAddr, HI_U32 Size);

#endif /*__HI_GFX_MEM_H__ */
