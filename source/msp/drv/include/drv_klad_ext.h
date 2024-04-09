/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     :drv_klad_ext.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#ifndef __DRV_KLAD_EXT_H_
#define __DRV_KLAD_EXT_H_

#include "hi_type.h"
#include "hi_unf_klad.h"
#include "hi_unf_cipher.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum
{
    KLAD_SEC_ENABLE = 0,
    KLAD_SEC_DISABLE,
    KLAD_SEC_BUTT
} DRV_KLAD_SEC_E;

typedef struct
{
    HI_HANDLE handle;
    HI_UNF_KLAD_TARGET_ENGINE_E enEngine;
    HI_BOOL bOdd;
    HI_U8  u8Key[HI_UNF_KLAD_MAX_KEY_LEN];
    DRV_KLAD_SEC_E  enSecEn;
}EXT_CLEAR_CW_KLAD_PARA_S;

typedef HI_S32 (*SET_CLEAR_CW_KLAD_FUNC)(EXT_CLEAR_CW_KLAD_PARA_S *stClearKey);

typedef struct
{
    SET_CLEAR_CW_KLAD_FUNC pSetClearkey;
}KLAD_EXPORT_FUNC_S;

HI_S32  KLAD_ModInit(HI_VOID);
HI_VOID KLAD_ModExit(HI_VOID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif   /* __DRV_KLAD_EXT_H_ */

