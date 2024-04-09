/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*************************************************************************************************
File Name	    : hi_png_config.h
Version		    : Initial Draft
Author		    :
Created		    : 2018/01/01
Description	    :
Function List 	:


History       	:
Date                Author                   Modification
2018/01/01   		sdk            		    Created file
*************************************************************************************************/
#ifndef __PNG_CONFIG_H__
#define __PNG_CONFIG_H__

#define CONFIG_PNG_PREMULTIALPHA_ENABLE

#ifdef CONFIG_GFX_PROC_UNSUPPORT
#define CONFIG_PNG_DEBUG_DISABLE
//#define CONFIG_PNG_PROC_DISABLE
#define CONFIG_PNG_VERSION_DISABLE
#define CONFIG_PNG_STR_DISABLE
#endif

#define CONFIG_PNG_USE_SDK_CRG_ENABLE

#endif
