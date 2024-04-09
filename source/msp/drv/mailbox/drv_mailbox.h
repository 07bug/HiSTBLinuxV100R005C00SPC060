/******************************************************************************
 *
 * Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : drv_mailbox.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-08-18
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __DRV_MAILBOX_H__
#define __DRV_MAILBOX_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cpluscplus */


/*************************** Macro Definition *********************************/
/** \addtogroup     DRV_MAILBOX */
/** @{ */  /** <!-- [DRV_MAILBOX] */
#define MID_SCPU_COMMON             (0x01)
#define MID_SCPU_CAS                (0x02)
#define MID_TCPU_COMMON             (0x40)
#define MID_ACPU_COMMON             (0x60)

#define MID_SMCU_SCS                (0x20)
#define MID_SMCU_SEC_STANDBY        (0x21)
#define MID_SMCU_KEY_PROVISION      (0x22)
#define MID_SMCU_RUNTIME_CHECK      (0x23)
#define MID_SMCU_RUNTIME_CHECK_FS   (0x24)
#define DRV_MAILBOX_MAX_MESSAGE_LEN       (0x1000)
#define DRV_MAILBOX_INFINITE_TIME         (0xFFFFFFFF)


/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     DRV_MAILBOX */
/** @{ */  /** <!-- [DRV_MAILBOX] */


/****** Structure definition **************/

typedef struct
{
    HI_VOID *pMessage;
    HI_U32 u32MessageLen;
    HI_VOID *pOutBuffer;
    HI_U32 *pu32OutBufferLen;
} DRV_MAILBOX_BUFFER_S;


/** @}*/  /** <!-- ==== Structure Definition End ====*/

HI_S32 DRV_MAILBOX_Init(HI_VOID);

HI_S32 DRV_MAILBOX_DeInit(HI_VOID);

HI_S32 DRV_MAILBOX_Open(HI_HANDLE *pHandle, HI_U32 u32Id);

HI_S32 DRV_MAILBOX_Close(HI_HANDLE handle);

HI_S32 DRV_MAILBOX_SendMessage
(
    HI_HANDLE handle,
    HI_U32 receiver,
    DRV_MAILBOX_BUFFER_S *buffer_info,
    HI_U32 flags,
    HI_U32 param
);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cpluscplus */

#endif /* __DRV_MAILBOX_H__ */

