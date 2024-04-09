/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_mpi_sessoin_manager.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __HI_MPI_SESSION_MANAGER_H__
#define __HI_MPI_SESSION_MANAGER_H__

#include "hi_type.h"
#include "hi_unf_session_manager.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/** the type of intent*/
typedef enum
{
    HI_UNF_SM_INTENT_DEFAULT = 0,
    HI_UNF_SM_INTENT_WATCH,
    HI_UNF_SM_INTENT_RECORD,
    HI_UNF_SM_INTENT_EXPORT,
    HI_UNF_SM_INTENT_BUTT
} HI_UNF_SM_INTENT_E;

HI_S32 HI_MPI_SM_Init(HI_VOID);

HI_S32 HI_MPI_SM_DeInit(HI_VOID);

HI_S32 HI_MPI_SM_Create(HI_HANDLE *phSM, HI_UNF_SM_ATTR_S *pstSMAttr);

HI_S32 HI_MPI_SM_AddResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstModule);

HI_S32 HI_MPI_SM_DelResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstModule);

HI_S32 HI_MPI_SM_Destroy(HI_HANDLE hSM);

HI_S32 HI_MPI_SM_SetIntent(HI_HANDLE hSM, HI_UNF_SM_INTENT_E enIntent);

HI_S32 HI_MPI_SM_GetResource(HI_UNF_SM_MODULE_E enSrcModID, HI_HANDLE hSrcModHandle, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstModule, HI_U32 *pu32ModNum);

HI_S32 HI_MPI_SM_GetSMHandleBySID(HI_U32 u32SessionID, HI_HANDLE *phSM);

HI_S32 HI_MPI_SM_GetIntent(HI_HANDLE hSM, HI_UNF_SM_INTENT_E *penIntent);

HI_S32 HI_MPI_SM_GetResourceBySMHandle(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstModule, HI_U32 *pu32ModNum);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif  // __HI_MPI_SESSION_MANAGER_H__
