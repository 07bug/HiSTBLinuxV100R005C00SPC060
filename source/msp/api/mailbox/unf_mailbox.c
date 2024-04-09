/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : unf_mailbox.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/15
  Description   :
  History       :
  1.Date        : 2009/12/15
    Author      : sdk
    Modification: Created file

*******************************************************************************/
#include "hi_unf_mailbox.h"
#include "hi_mpi_mailbox.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_S32 HI_UNF_MAILBOX_Init(HI_VOID)
{
    return HI_MPI_MAILBOX_Init();
}

HI_S32 HI_UNF_MAILBOX_DeInit(HI_VOID)
{
    return HI_MPI_MAILBOX_DeInit();
}

HI_S32 HI_UNF_MAILBOX_Open(HI_HANDLE* pHandle, HI_U32 u32Id)
{
    return HI_MPI_MAILBOX_Open(pHandle, u32Id);
}

HI_S32 HI_UNF_MAILBOX_Close(HI_HANDLE handle)
{
    return HI_MPI_MAILBOX_Close(handle);
}


HI_S32 HI_UNF_MAILBOX_Send(HI_HANDLE handle, HI_U32 receiver, HI_UNF_MAILBOX_BUFFER_S *pstBuffer, HI_U32 flags, HI_U32 param)
{
    return HI_MPI_MAILBOX_Send(handle, receiver, pstBuffer, flags, param);
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

