/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_sm_tee_func.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_SM_TEE_FUNC_H__
#define __DRV_SM_TEE_FUNC_H__

#include "hi_common.h"
#include "hi_type.h"
#include "hi_error_mpi.h"
#include "hi_unf_session_manager.h"
#include "hi_mpi_session_manager.h"

HI_S32 SM_TEEC_Init(HI_VOID);

HI_S32 SM_TEEC_DeInit(HI_VOID);

HI_S32 SM_TEEC_Create(HI_HANDLE *pHandle, HI_UNF_SM_ATTR_S *pstAttr);

HI_S32 SM_TEEC_Destroy(HI_HANDLE handle);

HI_S32 SM_TEEC_Add(HI_HANDLE sm_handle, HI_UNF_SM_MODULE_E modlue, HI_UNF_SM_MODULE_S *pstModule);

HI_S32 SM_TEEC_Del(HI_HANDLE sm_handle, HI_UNF_SM_MODULE_E modlue, HI_UNF_SM_MODULE_S *pstModule);

HI_S32 SM_TEEC_SetIntent(HI_HANDLE sm_handle, HI_UNF_SM_INTENT_E intent);

HI_S32 SM_TEEC_GetResource(HI_UNF_SM_MODULE_E src_mod, HI_HANDLE src_handle, HI_UNF_SM_MODULE_E des_mod, HI_UNF_SM_MODULE_S *pstModule, HI_U32 *pu32ModNum);

HI_S32 SM_TEEC_PrintProc(HI_VOID);

HI_S32 SM_TEEC_GetSMHandle(HI_U32 u32SessionID, HI_HANDLE *phSM);

HI_S32 SM_TEEC_GetIntent(HI_HANDLE sm_handle, HI_UNF_SM_INTENT_E *pIntent);

HI_S32 SM_TEEC_GetResourceBySM(HI_HANDLE hSM, HI_UNF_SM_MODULE_E des_mod, HI_UNF_SM_MODULE_S *pstModule, HI_U32 *pu32ModNum);
#endif /* __DRV_SM_TEE_FUNC_H__ */

