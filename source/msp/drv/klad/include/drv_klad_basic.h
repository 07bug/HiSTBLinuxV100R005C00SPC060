/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_basic.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_KLAD_BASIC_H__
#define __DRV_KLAD_BASIC_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */

HI_S32 EXT_DRV_KLAD_BASIC_SetClearCWKey(EXT_CLEAR_CW_KLAD_PARA_S *stClearKey);

HI_S32 DRV_KLAD_BASIC_Init(HI_VOID);
HI_S32 DRV_KLAD_BASIC_Exit(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_KLAD_BASIC_H__ */

