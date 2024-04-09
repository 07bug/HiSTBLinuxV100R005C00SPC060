/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_tee_klad.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :

******************************************************************************/
#ifndef __DRV_TEE_KLAD_H__
#define __DRV_TEE_KLAD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#ifdef HI_TEE_SUPPORT
#include "teek_client_api.h"
#include "hi_type.h"
#include "hi_unf_klad.h"


#define TEEC_CMD_KLAD_CREAT                 1
#define TEEC_CMD_KLAD_DESTORY               2
#define TEEC_CMD_KLAD_SET_CONTENT_KEY       3
#define TEEC_CMD_KLAD_DISABLESECEN          4
#define TEEC_CMD_KLAD_ENABLESECEN           5

HI_S32 DEV_KLAD_SendCmdToTA(HI_U32 cmd_id, TEEC_Operation *operation, HI_U32 *ret_origin);
HI_S32 DEV_KLAD_InitTeec(HI_VOID);
HI_S32 DEV_KLAD_DeInitTeec(HI_VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_TEE_KLAD_H__ */

