/************************************************************************************************
*
* Copyright (C) 2018 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
* and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
**************************************************************************************************
File Name           : drv_png_ext.h
Version             : Initial Draft
Author              :
Created             : 2018/01/01
Description         :
Function List       :


History             :
Date                         Author                     Modification
2018/01/01                   sdk                        Created file
**************************************************************************************************/
#ifndef __DRV_PNG_EXT_H__
#define __DRV_PNG_EXT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_drv_dev.h"

typedef HI_S32  (*FN_PNG_ModInit)(HI_VOID);
typedef HI_VOID (*FN_PNG_ModeExit)(HI_VOID);
typedef HI_S32  (*FN_PNG_Suspend)(PM_BASEDEV_S *, pm_message_t);
typedef HI_S32  (*FN_PNG_Resume)(PM_BASEDEV_S *);

typedef struct
{
    FN_PNG_ModInit   pfnPngModInit;
    FN_PNG_ModeExit  pfnPngModExit;
    FN_PNG_Suspend   pfnPngSuspend;
    FN_PNG_Resume    pfnPngResume;
} PNG_EXPORT_FUNC_S;

void PNG_DRV_ModExit(void);
int PNG_DRV_ModInit(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__DRV_PNG_EXT_H__*/
