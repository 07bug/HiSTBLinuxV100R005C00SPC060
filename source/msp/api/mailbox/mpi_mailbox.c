/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mpi_mailbox.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_mpi_mailbox.h"
#include "drv_mailbox_ioctl.h"
#include "hi_error_mpi.h"
#include "hi_drv_struct.h"
#include "hi_error_mpi.h"
#include "hi_module.h"

#include "hi_debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

static HI_S32               s_mailbox_dev_fd = -1;
static pthread_mutex_t      s_mailbox_mutex = PTHREAD_MUTEX_INITIALIZER;

#define HI_MAILBOX_LOCK()        (HI_VOID)pthread_mutex_lock(&s_mailbox_mutex);
#define HI_MAILBOX_UNLOCK()      (HI_VOID)pthread_mutex_unlock(&s_mailbox_mutex);

#define HI_ERR_MAILBOX(fmt...)                HI_ERR_PRINT(HI_ID_MAILBOX,   fmt)
#define MAILBOX_ERR_PrintHex(val)             HI_ERR_MAILBOX("%s = 0x%08X\n",#val, val)
#define MAILBOX_PrintErrorCode(errCode)       HI_ERR_MAILBOX("return [0x%08x]\n", errCode)
#define MAILBOX_PrintErrorFunc(func,errCode)  HI_ERR_MAILBOX("Call [%s] return [0x%08x]\n", #func, errCode)


#define MAILBOX_CHECK_FLAG(flag) \
    do {\
        if (((flag) != 0) && ((flag) != 1)) \
        {\
            MAILBOX_ERR_PrintHex(flag); \
            return HI_ERR_MAILBOX_INVALID_FLAG;\
        }\
    } while(0)


#define MAILBOX_CHECK_POINTER(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_INVALID_PTR); \
            return HI_ERR_MAILBOX_INVALID_PTR; \
        } \
    } while (0)


#define MAILBOX_CHECK_HANDLE(handle) \
    do{ \
        if ((handle >> 16) != HI_ID_MAILBOX)\
        {\
            MAILBOX_ERR_PrintHex(handle); \
            return HI_ERR_MAILBOX_INVALID_HANDLE;\
        }\
    }while(0)


#define MAILBOX_CHECK_RECEIVER(receiver) \
    do{ \
        if ((receiver != MID_SCPU_COMMON))\
        {\
            MAILBOX_ERR_PrintHex(receiver); \
            return HI_ERR_MAILBOX_INVALID_RECEIVER;\
        }\
    }while(0)

#define MAILBOX_CHECK_SENDER(sender) \
    do{ \
        if ((sender != MID_ACPU_COMMON))\
        {\
            MAILBOX_ERR_PrintHex(sender); \
            return HI_ERR_MAILBOX_INVALID_RECEIVER;\
        }\
    }while(0)


#define MAILBOX_CHECK_PARAM(value) \
    do{ \
        if ((value) != HI_TRUE) \
        {\
            return HI_ERR_MAILBOX_INVALID_PARA;\
        }\
    }while(0)




HI_S32 HI_MPI_MAILBOX_Init(HI_VOID)
{
    HI_MAILBOX_LOCK();

    if (s_mailbox_dev_fd > 0)
    {
        HI_MAILBOX_UNLOCK();
        return HI_SUCCESS;
    }

    s_mailbox_dev_fd = open("/dev/"UMAP_DEVNAME_MAILBOX, O_RDWR | O_NONBLOCK, 0);
    if(s_mailbox_dev_fd < 0)
    {
        HI_MAILBOX_UNLOCK();
        HI_ERR_MAILBOX("open mailbox error\n");
        return HI_FAILURE;
    }

    HI_MAILBOX_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_MAILBOX_DeInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    HI_MAILBOX_LOCK();

    if (s_mailbox_dev_fd < 0)
    {
        HI_MAILBOX_UNLOCK();
        return HI_FAILURE;
    }

    ret = close(s_mailbox_dev_fd);
    if(HI_SUCCESS != ret)
    {
        HI_MAILBOX_UNLOCK();
        return ret;
    }

    s_mailbox_dev_fd = -1;

    HI_MAILBOX_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_MAILBOX_Open(HI_HANDLE *pHandle, HI_U32 u32MID)
{
    HI_S32        ret;
    DRV_MAILBOX_CMD_OPEN_S open;

    MAILBOX_CHECK_POINTER(pHandle);
    MAILBOX_CHECK_SENDER(u32MID);

    memset(&open, 0x0, sizeof (open));
    open.handle = HI_INVALID_HANDLE;
    open.id     = u32MID;

    ret = ioctl(s_mailbox_dev_fd, CMD_MAILBOX_OPEN, &open);
    if(HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    *pHandle = open.handle;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_MAILBOX_Close(HI_HANDLE hHandle)
{
    HI_S32          ret;
    DRV_MAILBOX_CMD_CLOSE_S close;

    MAILBOX_CHECK_HANDLE(hHandle);

    memset(&close, 0x0, sizeof (close));
    close.handle = hHandle;

    ret = ioctl(s_mailbox_dev_fd, CMD_MAILBOX_CLOSE, &close);
    if(HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_MAILBOX_Send
(
    HI_HANDLE handle,
    HI_U32 receiver,
    HI_UNF_MAILBOX_BUFFER_S *pstBuffer,
    HI_U32 flags,
    HI_U32 param
)
{
    HI_S32                  ret;
    DRV_MAILBOX_CMD_SEND_S  send;

    MAILBOX_CHECK_HANDLE(handle);
    MAILBOX_CHECK_POINTER(pstBuffer);
    MAILBOX_CHECK_POINTER(pstBuffer->pMessage);
    MAILBOX_CHECK_POINTER(pstBuffer->pOutBuffer);
    MAILBOX_CHECK_POINTER(pstBuffer->pu32OutBufferLen);
    MAILBOX_CHECK_PARAM(pstBuffer->u32MessageLen > 0);
    MAILBOX_CHECK_PARAM(*(pstBuffer->pu32OutBufferLen) > 0);

    memset(&send, 0x0, sizeof (send));
    send.handle      = handle;
    send.receiver    = receiver;
    send.message     = pstBuffer->pMessage;
    send.message_len = pstBuffer->u32MessageLen;
    send.output      = pstBuffer->pOutBuffer;
    send.output_len  = pstBuffer->pu32OutBufferLen;
    send.flag        = flags;
    send.param       = param;

    ret = ioctl(s_mailbox_dev_fd, CMD_MAILBOX_SEND, &send);
    if(HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(ioctl, ret);
        return ret;
    }

    return HI_SUCCESS;
}

