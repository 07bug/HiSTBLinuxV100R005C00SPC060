#ifndef __DRV_MAILBOX_EXT_H__
#define __DRV_MAILBOX_EXT_H__

#include "hi_type.h"
#include "hi_drv_mailbox.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef HI_S32 (*FN_DRV_MAILBOX_Open)(HI_HANDLE* pHandle, HI_U32 u32Id);
typedef HI_S32 (*FN_DRV_MAILBOX_Close)(HI_HANDLE handle);
typedef HI_S32 (*FN_DRV_MAILBOX_SendMessage)(HI_HANDLE handle, HI_U32 receiver, HI_DRV_MAILBOX_BUFFER_S *buffer_info, HI_U32 flag, HI_U32 param);

typedef struct
{
    FN_DRV_MAILBOX_Open             pfnMailbox_Open;
    FN_DRV_MAILBOX_Close            pfnMailbox_Close;
    FN_DRV_MAILBOX_SendMessage      pfnMailbox_SendMessage;
} MAILBOX_EXPORT_FUNC_S;

HI_S32 MAILBOX_ModInit(HI_VOID);
HI_VOID MAILBOX_ModExit(HI_VOID);


#ifdef __cplusplus
}
#endif

#endif

