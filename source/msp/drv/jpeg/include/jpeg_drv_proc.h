/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name        : jpeg_drv_proc.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      : the proc information define in this file
                   CNcomment: proc 相关的信息都在这里 CNend\n
Function List    :


History          :
Date                  Author           Modification
2018/01/01            sdk              Created file
*************************************************************************************************/

#ifndef __JPEG_DRV_PROC_H__
#define __JPEG_DRV_PROC_H__

/*********************************add include here***********************************************/
#include "hi_jpeg_config.h"


#ifdef CONFIG_JPEG_PROC_ENABLE

#include "hi_type.h"
#include "hi_drv_jpeg.h"

/************************************************************************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */


   /***************************** Macro Definition **********************************************/

   /*************************** Structure Definition ********************************************/


   /********************** Global Variable declaration ******************************************/


   /******************************* API declaration *********************************************/

   /*****************************************************************************
    * Function     : JPEG_PROC_Init
    * Description  : initial jpeg proc
    * param[in]    : NA
    * retval       : NA
     *****************************************************************************/
    HI_S32 JPEG_PROC_Init(HI_VOID);

   /*****************************************************************************
    * Function     : JPEG_PROC_DInit
    * Description  : dinitial jpeg proc
    * param[in]    : NA
    * retval       : NA
    *****************************************************************************/
    HI_VOID JPEG_PROC_DInit(HI_VOID);

   /*****************************************************************************
    * Function     : JPEG_PROC_SetPthreadNum
    * Description  : set jpeg decode pthread numbers
    * param[in]    : PthreadNums
    * retval       : NA
    *****************************************************************************/
    HI_VOID JPEG_PROC_SetPthreadNum(HI_U32 PthreadNums);

   /*****************************************************************************
    * Function     : JPEG_PROC_SetDecLockTimes
    * Description  : set jpeg decode has been lock times
    * param[in]    : PthreadNums
    * retval       : NA
     *****************************************************************************/
    HI_VOID JPEG_PROC_SetDecLockTimes(HI_U32 LockTimes);

   /*****************************************************************************
    * Function     : JPEG_PROC_SetOpenDevCnt
    * Description  : set jpeg decode has been open times
    * param[in]    : PthreadNums
    * retval       : NA
    *****************************************************************************/
    HI_VOID JPEG_PROC_SetOpenDevCnt(HI_S32 OpenTimes);

   /****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

#endif
