/***********************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
************************************************************************************************
File Name        : tde_config.h
Version          : Initial Draft
Author           :
Created          : 2018/01/01
Description      :
Function List    :

History          :
Date                     Author           Modification
2018/01/01               sdk              Created file
************************************************************************************************/
#ifndef  __TDE_CONFIG_H__
#define  __TDE_CONFIG_H__

/*********************************add include here**********************************************/

#ifdef __cplusplus
#if __cplusplus
   extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Macro Definition ********************************************/

#ifdef CONFIG_GFX_PROC_UNSUPPORT
#define CONFIG_TDE_VERSION_DISABLE
#define CONFIG_TDE_DEBUG_DISABLE
#endif

#ifdef CONFIG_GFX_PROC_UNSUPPORT
#define CONFIG_TDE_PROC_DISABLE
#endif

/*************************** Enum Definition ***********************************************/

/*************************** Structure Definition ******************************************/

/******************************* API declaration *******************************************/

/******************************* API release ***********************************************/

#endif /*__TDE_CONFIG_H__ */
