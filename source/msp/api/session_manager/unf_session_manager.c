/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_session_manager.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-08-11
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include "hi_mpi_session_manager.h"
#include "hi_unf_session_manager.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32 HI_UNF_SM_Init(HI_VOID)
{
    return HI_MPI_SM_Init();
}


HI_S32 HI_UNF_SM_DeInit(HI_VOID)
{
    return HI_MPI_SM_DeInit();
}

HI_S32 HI_UNF_SM_Create(HI_HANDLE *phSM, HI_UNF_SM_ATTR_S *pstSMAttr)
{
    return HI_MPI_SM_Create(phSM, pstSMAttr);
}

HI_S32 HI_UNF_SM_AddResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstModule)
{
    return HI_MPI_SM_AddResource(hSM, enModID, pstModule);
}


HI_S32 HI_UNF_SM_DelResource(HI_HANDLE hSM, HI_UNF_SM_MODULE_E enModID, HI_UNF_SM_MODULE_S *pstModule)
{
    return HI_MPI_SM_DelResource(hSM, enModID, pstModule);
}


HI_S32 HI_UNF_SM_Destroy(HI_HANDLE hSM)
{
    return HI_MPI_SM_Destroy(hSM);
}

HI_S32 HI_UNF_SM_GetSMHandleBySID(HI_U32 u32SessionID, HI_HANDLE *pSM)
{
    return HI_MPI_SM_GetSMHandleBySID(u32SessionID, pSM);
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
