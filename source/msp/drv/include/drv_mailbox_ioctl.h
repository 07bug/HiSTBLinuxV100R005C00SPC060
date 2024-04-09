/******************************************************************************

Copyright (C), 2017, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_mailbox_ioctl.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2017-10-23
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_MAILBOX_IOCTL_H__
#define __DRV_MAILBOX_IOCTL_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */

typedef struct
{
    HI_U32 handle;
    HI_U32 id;
} DRV_MAILBOX_CMD_OPEN_S;

typedef struct
{
    HI_HANDLE handle;
} DRV_MAILBOX_CMD_CLOSE_S;


typedef struct
{
    HI_HANDLE handle;
    HI_U32 receiver;
    HI_U8 *message;
    HI_U32 message_len;
    HI_U8 *output;
    HI_U32 *output_len;
    HI_U32 flag;
    HI_U32 param;
} DRV_MAILBOX_CMD_SEND_S;

typedef struct
{
    HI_HANDLE handle;
    HI_U32 receiver;
    HI_U32 message;
    HI_U32 message_len;
    HI_U32 output;
    HI_U32 output_len;
    HI_U32 flag;
    HI_U32 param;
} DRV_MAILBOX_CMD_SEND_COMPAT_S;


#define CMD_MAILBOX_OPEN                    _IOWR(HI_ID_MAILBOX, 0x1, DRV_MAILBOX_CMD_OPEN_S)
#define CMD_MAILBOX_CLOSE                   _IOW (HI_ID_MAILBOX, 0x2, DRV_MAILBOX_CMD_CLOSE_S)
#define CMD_MAILBOX_SEND                    _IOWR(HI_ID_MAILBOX, 0x3, DRV_MAILBOX_CMD_SEND_S)
#define CMD_MAILBOX_COMPAT_SEND             _IOWR(HI_ID_MAILBOX, 0x3, DRV_MAILBOX_CMD_SEND_COMPAT_S)

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */

#endif /* End of #ifndef __DRV_MAILBOX_IOCTL_H__ */
