/******************************************************************************
 *
 * Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : hi_drv_mailbox.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-08-18
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __HI_DRV_MAILBOX_H__
#define __HI_DRV_MAILBOX_H__

#include "hi_type.h"
#include "hi_module.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HI_DRV_MID_SCPU          (0x01)
#define HI_DRV_MID_CAS           (0x02)
#define HI_DRV_MID_TCPU          (0x40)
#define HI_DRV_MID_ACPU          (0x60)

typedef struct
{
    HI_VOID *pMessage;
    HI_U32 u32MessageLen;
    HI_VOID *pOutBuffer;
    HI_U32 *pu32OutBufferLen;
} HI_DRV_MAILBOX_BUFFER_S;


/*************************** Structure Definition ****************************/
/** \addtogroup      Mailbox */
/** @{ */  /** <!-- [Mailbox] */

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/

HI_S32 HI_DRV_MAILBOX_Open(HI_HANDLE* pHandle, HI_U32 u32Id);

HI_S32 HI_DRV_MAILBOX_Close(HI_HANDLE handle);

HI_S32 HI_DRV_MAILBOX_SendMessage(HI_HANDLE handle, HI_U32 receiver, HI_DRV_MAILBOX_BUFFER_S *buffer_info, HI_U32 flag, HI_U32 param);


/** @} */  /** <!-- ==== API declaration end ==== */


#ifdef __cplusplus
}
#endif

#endif
