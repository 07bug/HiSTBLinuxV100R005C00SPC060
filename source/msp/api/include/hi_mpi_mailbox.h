/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name    : hi_mpi_mailbox.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created      : 2016-09-19
  Description : Define the data struct and APIs of Mailbox

*******************************************************************************/
#ifndef __HI_MPI_MAILBOX_H__
#define __HI_MPI_MAILBOX_H__

#include "hi_type.h"
#include "hi_unf_mailbox.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


/*************************** Structure Definition ****************************/
/** \addtogroup      Mailbox */
/** @{ */  /** <!-- [Mailbox] */


/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      Mailbox */
/** @{ */  /** <!--[Mailbox]*/

HI_S32 HI_MPI_MAILBOX_Init(HI_VOID);

HI_S32 HI_MPI_MAILBOX_DeInit(HI_VOID);

HI_S32  HI_MPI_MAILBOX_Open(HI_HANDLE *pHandle, HI_U32 id);

HI_S32 HI_MPI_MAILBOX_Close(HI_HANDLE handle);

HI_S32 HI_MPI_MAILBOX_Send(HI_U32 handle, HI_U32 receiver, HI_UNF_MAILBOX_BUFFER_S *pstBuffer, HI_U32 flags, HI_U32 param);


/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_SCPU_MAILBOX_H__ */

