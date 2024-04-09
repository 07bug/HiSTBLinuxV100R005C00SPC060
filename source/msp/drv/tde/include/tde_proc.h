/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : tde_proc.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/
#ifndef  __TDE_PROC_H__
#define  __TDE_PROC_H__

/*********************************add include here**********************************************/
#include "tde_hal.h"

/***********************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


#ifndef CONFIG_TDE_PROC_DISABLE


/***************************** Macro Definition ********************************************/

#define TDE_MAX_PROC_NUM 8

/*************************** Enum Definition ***********************************************/

/*************************** Structure Definition ******************************************/

/******************************* API declaration *******************************************/

/******************************* API release ***********************************************/

/*****************************************************************************
* Function:      TDEProcRecordNode
* Description:   Record TDE Node configure information
* Input:         null
* Output:        none
* Return:        none
* Others:        none
*****************************************************************************/
HI_VOID TDEProcRecordNode(TDE_HWNode_S *pHWNode);

HI_S32 tde_read_proc(struct seq_file *p, HI_VOID *v);

HI_S32 tde_write_proc(struct file *file,const char __user *buf, size_t count, loff_t *ppos);

HI_S32 tde_proc_init(HI_VOID);

HI_VOID tde_proc_dinit(HI_VOID);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__TDE_PROC_H__ */
