/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_mailbox.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/interrupt.h>

#include "hi_kernel_adapt.h"
#include "hi_drv_mailbox.h"
#include "hi_module.h"
#include "hi_drv_sys.h"
#include "hi_drv_mem.h"

#include "drv_mailbox.h"
#include "drv_mailbox_debug.h"
#include "drv_mailbox_crc.h"

#include "hal_mailbox.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAKEHANDLE(id)                (HI_ID_MAILBOX << 16) | (id & 0xff)
#define DRV_MAILBOX_MAX_SESSION_NUM   (4)
#define DRV_MAILBOX_INTERRUPT_IRQ     (160)
#define DRV_MAILBOX_IRQ_NAME          "scpu_mailbox"

typedef struct
{
    HI_HANDLE handle[DRV_MAILBOX_MAX_SESSION_NUM];
} DRV_MAILBOX_SESSION_S;

typedef HI_S32 (*f_write_head)(HI_U32, HI_U32, HI_BOOL, HI_BOOL);
typedef HI_S32 (*f_write_body)(HI_U8 *, HI_U32);
typedef HI_U32 (*f_read_head)(HI_VOID);
typedef HI_S32 (*f_read_body)(HI_U8 *, HI_U32);
typedef HI_VOID (*f_setSendCmd)(HI_VOID);
typedef HI_BOOL (*f_checkReceive)(HI_VOID);
typedef HI_BOOL (*f_checkSend)(HI_VOID);
typedef HI_VOID (*f_cleanIntr)(HI_VOID);
typedef HI_U32  (*f_getBodySize)(HI_VOID);

typedef struct
{
    f_write_head write_head;
    f_write_body write_body;
    f_setSendCmd send_cmd;
    f_checkReceive check_receive;
    f_getBodySize  get_body_size;
} DRV_MAILBOX_SEND_S;

typedef struct
{
    f_read_head  read_head;
    f_read_body  read_body;
    f_checkSend  check_send;
    f_cleanIntr  clean_intr;
    f_getBodySize  get_body_size;
} DRV_MAILBOX_RECEIVE_S;

#define DRV_MAILBOX_MAX_RECEIVE_BUFF_LEN  (DRV_MAILBOX_MAX_MESSAGE_LEN + 0x4)  // add 4B crc

#define DRV_MAILBOX_FLAG_BLOCK          (0x0)
#define DRV_MAILBOX_FLAG_TIMEOUT        (0x1)

typedef enum
{
    MAILBOX_BUFFER_STATUS_NOMAL = 0,
    MAILBOX_BUFFER_STATUS_FINISH,
    MAILBOX_BUFFER_STATUS_INVALID_LEN,
    MAILBOX_BUFFER_STATUS_INVALID_PARAM,
    MAILBOX_BUFFER_STATUS_BUTT
} DRV_MAILBOX_BUFFER_STATUS_E;

typedef struct
{
    HI_U8 buffer[DRV_MAILBOX_MAX_RECEIVE_BUFF_LEN];
    HI_U32 pos;
    DRV_MAILBOX_BUFFER_STATUS_E status;
    wait_queue_head_t receive_queue;
} DRV_MAILBOX_RECEIVE_BUFFER_S;

#define DRV_MAILBOX_WAIT(timeout, func) \
    do { \
        while ((timeout)) \
        { \
            if (HI_TRUE == (func)()) \
            { \
                break;\
            }\
            msleep(1); \
            (timeout)--; \
            if ((timeout) == 0) \
            { \
                MAILBOX_ERR_PrintHex(HI_ERR_MAILBOX_TIMEOUT); \
                return HI_ERR_MAILBOX_TIMEOUT; \
            } \
        } \
    } while(0)


static DRV_MAILBOX_SESSION_S s_mailbox_session;
static DRV_MAILBOX_RECEIVE_BUFFER_S *pReceiveBuffer = HI_NULL;

static HI_S32 send_msg(HI_U32 receiver, HI_U8 *message, HI_U32 message_len, HI_U32 *timeout, DRV_MAILBOX_SEND_S *func)
{
    HI_S32 i;
    HI_U32 block_size     = 0;
    HI_S32 mid_block_num  = 0;
    HI_U32 last_block_len = 0;

    MAILBOX_FUNC_ENTER();

    DRV_MAILBOX_WAIT(*timeout, func->check_receive);

    block_size = func->get_body_size();
    //小于等于1块的情况
    if (message_len <= block_size)
    {
        func->write_head(receiver, message_len, HI_TRUE, HI_TRUE);
        func->write_body(message, message_len);
        func->send_cmd();

        DRV_MAILBOX_WAIT(*timeout, func->check_receive);
        MAILBOX_FUNC_EXIT();
        return HI_SUCCESS;
    }

    //处理第一块
    func->write_head(receiver, block_size, HI_TRUE, HI_FALSE);
    func->write_body(message, block_size);
    func->send_cmd();

    DRV_MAILBOX_WAIT(*timeout, func->check_receive);

    //处理中间块
    mid_block_num = (message_len - block_size - 1) / block_size;
    for (i = 0; i < mid_block_num; i++)
    {
        func->write_head(receiver, block_size, HI_FALSE, HI_FALSE);
        func->write_body((message + (i + 1) * block_size), block_size);
        func->send_cmd();

        DRV_MAILBOX_WAIT(*timeout, func->check_receive);
    }

    //处理最后一块
    last_block_len = message_len - (mid_block_num + 1) * block_size;
    func->write_head(receiver, last_block_len, HI_FALSE, HI_TRUE);
    func->write_body((message + (mid_block_num + 1) * block_size), last_block_len);
    func->send_cmd();

    DRV_MAILBOX_WAIT(*timeout, func->check_receive);

    MAILBOX_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 send_msg_to_scpu(HI_U8 *message, HI_U32 message_len, HI_U32 *timeout)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 *send_buffer = HI_NULL;
    HI_U32 send_buffer_len = 0;
    HI_U32 crc = 0;
    DRV_MAILBOX_SEND_S param;

    MAILBOX_FUNC_ENTER();

    send_buffer_len = message_len + 4;

    send_buffer = (HI_U8 *) HI_VMALLOC (HI_ID_MAILBOX, send_buffer_len);
    if (HI_NULL == send_buffer)
    {
        MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_NO_MEMORY);
        return HI_ERR_MAILBOX_NO_MEMORY;
    }

    memset(send_buffer, 0x0, send_buffer_len);
    memcpy(send_buffer, message, message_len);

    crc = crc32(0, message, message_len);
    memcpy(send_buffer + message_len, (HI_U8 *)&crc, sizeof (HI_U32));

    memset(&param, 0x0, sizeof (param));
    param.check_receive = HAL_MAILBOX_CheckScpuReceive;
    param.get_body_size = HAL_MAILBOX_GetBodySizeToScpu;
    param.send_cmd      = HAL_MAILBOX_SetSendCmdToScpu;
    param.write_body    = HAL_MAILBOX_WriteBodyToScpu;
    param.write_head    = HAL_MAILBOX_WriteHeadToScpu;

    ret = send_msg(MID_SCPU_COMMON, send_buffer, send_buffer_len, timeout, &param);
    if (HI_SUCCESS != ret)
    {
        HI_VFREE (HI_ID_MAILBOX, send_buffer);
        MAILBOX_PrintErrorFunc(send_msg, ret);
        return ret;
    }

    HI_VFREE (HI_ID_MAILBOX, send_buffer);
    MAILBOX_FUNC_EXIT();
    return HI_SUCCESS;
}

#ifndef MAILBOX_CRC_ENABLE
static HI_S32 send_msg_to_scpu_withoutCRC(HI_U8 *message, HI_U32 message_len, HI_U32 *timeout)
{
    HI_S32 ret = HI_FAILURE;
    DRV_MAILBOX_SEND_S param;

    MAILBOX_FUNC_ENTER();

    memset(&param, 0x0, sizeof (param));
    param.check_receive = HAL_MAILBOX_CheckScpuReceive;
    param.get_body_size = HAL_MAILBOX_GetBodySizeToScpu;
    param.send_cmd      = HAL_MAILBOX_SetSendCmdToScpu;
    param.write_body    = HAL_MAILBOX_WriteBodyToScpu;
    param.write_head    = HAL_MAILBOX_WriteHeadToScpu;

    ret = send_msg(MID_SCPU_COMMON, message, message_len, timeout, &param);
    if (HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(send_msg, ret);
        return ret;
    }

    MAILBOX_FUNC_EXIT();
    return HI_SUCCESS;
}
#endif

static HI_S32 send_msg_to_smcu(HI_U32 receiver, HI_VOID *message, HI_U32 message_len, HI_U32 *timeout)
{
    HI_S32 ret = HI_FAILURE;
    DRV_MAILBOX_SEND_S param;

    MAILBOX_FUNC_ENTER();

    memset(&param, 0x0, sizeof (param));
    param.check_receive = HAL_MAILBOX_CheckSmcuReceive;
    param.get_body_size = HAL_MAILBOX_GetBodySizeToSmcu;
    param.send_cmd      = HAL_MAILBOX_SetSendCmdToSmcu;
    param.write_body    = HAL_MAILBOX_WriteBodyToSmcu;
    param.write_head    = HAL_MAILBOX_WriteHeadToSmcu;

    ret = send_msg(receiver, message, message_len, timeout, &param);
    if (HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(send_msg, ret);
        return ret;
    }

    MAILBOX_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 send_msg_to_receiver(HI_U32 receiver, HI_U8 *message, HI_U32 message_len, HI_U32 *timeout)
{
    HI_S32 ret = HI_FAILURE;

    MAILBOX_FUNC_ENTER();

    if (MID_SCPU_COMMON == receiver)
    {
#ifdef MAILBOX_CRC_ENABLE
        ret = send_msg_to_scpu(message, message_len, timeout);
#else
        ret = send_msg_to_scpu_withoutCRC(message, message_len, timeout);
#endif
        if (HI_SUCCESS != ret)
        {
            MAILBOX_PrintErrorFunc(send_msg_to_scpu, ret);
            return ret;
        }
    }
    else if (MID_SCPU_CAS == receiver)
    {
        ret = send_msg_to_scpu(message, message_len, timeout);
        if (HI_SUCCESS != ret)
        {
            MAILBOX_PrintErrorFunc(send_msg_to_scpu, ret);
            return ret;
        }
    }
    else if ((MID_SMCU_SCS == receiver) || (MID_SMCU_KEY_PROVISION == receiver)
          || (MID_SMCU_RUNTIME_CHECK == receiver) || (MID_SMCU_SEC_STANDBY == receiver)
          || (MID_SMCU_RUNTIME_CHECK_FS == receiver) )
    {
        ret = send_msg_to_smcu(receiver, message, message_len, timeout);
        if (HI_SUCCESS != ret)
        {
            MAILBOX_PrintErrorFunc(send_msg_to_smcu, ret);
            return ret;
        }
    }

    MAILBOX_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 receive_msg_by_poll(HI_U32 sender, HI_VOID *output, HI_U32 *output_len, HI_U32 *timeout, DRV_MAILBOX_RECEIVE_S *func)
{
    MBOX_MSG_HEAD_U head;
    HI_U32 length = 0;
    HI_U8 *pos = HI_NULL;
    HI_U32 block_size = 0;
    HI_U32 max_length = *output_len;

    MAILBOX_FUNC_ENTER();

    block_size = func->get_body_size();

    while (1)
    {
        DRV_MAILBOX_WAIT(*timeout, func->check_send);

        head.u32 = func->read_head();

        MAILBOX_DBG_PrintHex(head.u32);
        if (head.bits.sender != sender)
        {
            MAILBOX_ERR_PrintHex(head.bits.sender);
            MAILBOX_ERR_PrintHex(sender);
            MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_ERR_RECEIVE);
            func->clean_intr();
            return HI_ERR_MAILBOX_ERR_RECEIVE;
        }

        if (head.bits.start == 1)
        {
            pos = (HI_U8 *)output;
            length = 0;
        }

        if ((head.bits.length > block_size) || (length + head.bits.length > max_length))
        {
            MAILBOX_ERR_PrintHex(head.bits.length);
            MAILBOX_ERR_PrintHex(length + head.bits.length);
            MAILBOX_ERR_PrintHex(block_size);
            MAILBOX_ERR_PrintHex(max_length);
            MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_UNEXPECTED_RECEIVE_LEN);
            func->clean_intr();
            return HI_ERR_MAILBOX_UNEXPECTED_RECEIVE_LEN;
        }

        func->read_body(pos, head.bits.length);

        length += head.bits.length;
        pos    += head.bits.length;

        if (head.bits.end == 1)
        {
            *output_len = length;
            func->clean_intr();

            MAILBOX_FUNC_EXIT();
            return HI_SUCCESS;
        }

        func->clean_intr();
    }

    return HI_FAILURE;
}

static HI_S32 receive_msg_by_interrupt(HI_U32 *timeout)
{
    HI_S32 ret = 0;
    MAILBOX_FUNC_ENTER();

    ret = wait_event_timeout(pReceiveBuffer->receive_queue, (pReceiveBuffer->status == MAILBOX_BUFFER_STATUS_FINISH), msecs_to_jiffies(*timeout));
    if (ret <= 0)
    {   *timeout = 0;
        return HI_ERR_MAILBOX_TIMEOUT;
    }
    else
    {
        *timeout = jiffies_to_msecs(ret);
        MAILBOX_FUNC_EXIT();
        return HI_SUCCESS;
    }
}

#ifdef MAILBOX_CRC_ENABLE
static HI_S32 recieve_msg_from_scpu_withCRC(HI_U8 *output, HI_U32 *output_len, HI_U32 *timeout)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 crc = 0;

    MAILBOX_FUNC_ENTER();

    ret = receive_msg_by_interrupt(timeout);
    if (HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(receive_msg_by_interrupt, ret);
        return ret;
    }

    crc = crc32(0, pReceiveBuffer->buffer, pReceiveBuffer->pos - 4);
    if (crc != *(HI_U32 *)((HI_U8 *)pReceiveBuffer->buffer + pReceiveBuffer->pos - 4))
    {
        MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_CRC_CHECK_ERROR);
        return HI_ERR_MAILBOX_CRC_CHECK_ERROR;
    }

    *output_len = pReceiveBuffer->pos - 4;
    memcpy(output, pReceiveBuffer->buffer, *output_len);

    MAILBOX_FUNC_EXIT();

    return HI_SUCCESS;
}
#else
static HI_S32 recieve_msg_from_scpu_withoutCRC(HI_U8 *output, HI_U32 *output_len, HI_U32 *timeout)
{
    HI_S32 ret = HI_FAILURE;

    MAILBOX_FUNC_ENTER();

    ret = receive_msg_by_interrupt(timeout);
    if (HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(receive_msg_by_interrupt, ret);
        return ret;
    }

    *output_len = pReceiveBuffer->pos;
    memcpy(output, pReceiveBuffer->buffer, *output_len);

    MAILBOX_FUNC_EXIT();
    return HI_SUCCESS;
}
#endif

static HI_S32 receive_msg_from_smcu(HI_U32 receiver, HI_U8 *output, HI_U32 *output_len, HI_U32 *timeout)
{
    HI_S32 ret = HI_FAILURE;
    DRV_MAILBOX_RECEIVE_S func;

    MAILBOX_FUNC_ENTER();

    memset(&func, 0x0, sizeof (func));
    func.check_send  = HAL_MAILBOX_CheckSmcuSend;
    func.clean_intr  = HAL_MAILBOX_CleanIntrFromSmcu;
    func.read_body   = HAL_MAILBOX_ReadBodyFromSmcu;
    func.read_head   = HAL_MAILBOX_ReadHeadFromSmcu;
    func.get_body_size = HAL_MAILBOX_GetBodySizeFromSmcu;

    ret = receive_msg_by_poll(receiver, output, output_len, timeout, &func);
    if (HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(receive_msg_by_poll, ret);
        return ret;
    }

    MAILBOX_FUNC_EXIT();
    return HI_SUCCESS;
}

static HI_S32 get_response_from_receiver(HI_U32 receiver, HI_VOID *output, HI_U32 *output_len, HI_U32 *timeout)
{
    HI_S32 ret = HI_FAILURE;

    MAILBOX_FUNC_ENTER();

    if (MID_SCPU_COMMON == receiver)
    {
#ifdef MAILBOX_CRC_ENABLE
        ret = recieve_msg_from_scpu_withCRC(output, output_len, timeout);
        if (HI_SUCCESS != ret)
        {
            MAILBOX_PrintErrorFunc(recieve_msg_from_scpu_withCRC, ret);
            return ret;
        }
#else
        ret = recieve_msg_from_scpu_withoutCRC(output, output_len, timeout);
        if (HI_SUCCESS != ret)
        {
            MAILBOX_PrintErrorFunc(recieve_msg_from_scpu_withoutCRC, ret);
            return ret;
        }
#endif
    }
    else if (MID_SCPU_CAS == receiver)
    {
        ret = recieve_msg_from_scpu_withoutCRC(output, output_len, timeout);
        if (HI_SUCCESS != ret)
        {
            MAILBOX_PrintErrorFunc(recieve_msg_from_scpu_withCRC, ret);
            return ret;
        }
    }
    else
    {
        ret = receive_msg_from_smcu(receiver, output, output_len, timeout);
        if (HI_SUCCESS != ret)
        {
            MAILBOX_PrintErrorFunc(receive_msg_from_smcu, ret);
            return ret;
        }
    }

    MAILBOX_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 DRV_MAILBOX_SendMessage
(
    HI_HANDLE handle,
    HI_U32 receiver,
    DRV_MAILBOX_BUFFER_S *buffer_info,
    HI_U32 flag,
    HI_U32 param
)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 block_time;
//    HI_U32 start, end;

    MAILBOX_FUNC_ENTER();

    MAILBOX_CHECK_HANDLE(handle);
    MAILBOX_CHECK_RECEIVER(receiver);
    MAILBOX_CHECK_POINTER(buffer_info);
    MAILBOX_CHECK_POINTER(buffer_info->pMessage);
    MAILBOX_CHECK_POINTER(buffer_info->pOutBuffer);
    MAILBOX_CHECK_POINTER(buffer_info->pu32OutBufferLen);
    MAILBOX_CHECK_PARAM(*(buffer_info->pu32OutBufferLen) > 0);
    MAILBOX_CHECK_PARAM(buffer_info->u32MessageLen > 0);
    MAILBOX_CHECK_FLAG(flag);

    MAILBOX_DBG_PrintHex(handle);
    MAILBOX_DBG_PrintHex(receiver);
    MAILBOX_DBG_PrintHex(flag);
    MAILBOX_DBG_PrintHex(param);

    memset(pReceiveBuffer->buffer, 0x0, sizeof (pReceiveBuffer->buffer));
    pReceiveBuffer->pos = 0;
    pReceiveBuffer->status = MAILBOX_BUFFER_STATUS_NOMAL;

    block_time = (flag == DRV_MAILBOX_FLAG_BLOCK) ? DRV_MAILBOX_INFINITE_TIME : param;
  //  HI_DRV_SYS_GetTimeStampMs(&start);
    ret = send_msg_to_receiver(receiver, buffer_info->pMessage, buffer_info->u32MessageLen, &block_time);
    if (HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(send_msg_to_receiver, ret);
        return ret;
    }

    ret = get_response_from_receiver(receiver, buffer_info->pOutBuffer, buffer_info->pu32OutBufferLen, &block_time);
    if (HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(get_response_from_receiver, ret);
        return ret;
    }

//    HI_DRV_SYS_GetTimeStampMs(&end);
//    MAILBOX_ERR_PrintHex(end - start);
    MAILBOX_FUNC_EXIT();
    return ret;
}

HI_S32 DRV_MAILBOX_Open(HI_HANDLE* pHandle, HI_U32 u32Id)
{
    HI_S32 i = 0;
    HI_U32 handle = HI_INVALID_HANDLE;

    MAILBOX_FUNC_ENTER();

    MAILBOX_CHECK_POINTER(pHandle);
    MAILBOX_CHECK_PARAM(MID_ACPU_COMMON == u32Id);

    handle = MAKEHANDLE(u32Id);
    for (i = 0; i < DRV_MAILBOX_MAX_SESSION_NUM; i++)
    {
        if (handle == s_mailbox_session.handle[i])
        {
            *pHandle = handle;
            MAILBOX_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }

    for (i = 0; i < DRV_MAILBOX_MAX_SESSION_NUM; i++)
    {
        if (HI_INVALID_HANDLE == s_mailbox_session.handle[i])
        {
            s_mailbox_session.handle[i] = handle;
            *pHandle = handle;
            MAILBOX_FUNC_EXIT();
            return HI_SUCCESS;
        }

    }

    MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_NO_SESSION);
    return HI_ERR_MAILBOX_NO_SESSION;
}

HI_S32 DRV_MAILBOX_Close(HI_HANDLE handle)
{
    HI_S32 i = 0;

    MAILBOX_FUNC_ENTER();

    MAILBOX_CHECK_HANDLE(handle);

    for (i = 0; i < DRV_MAILBOX_MAX_SESSION_NUM; i++)
    {
        if (handle == s_mailbox_session.handle[i])
        {
            s_mailbox_session.handle[i] = HI_INVALID_HANDLE;
            MAILBOX_FUNC_EXIT();
            return HI_SUCCESS;
        }
    }

    MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_INVALID_HANDLE);
    return HI_ERR_MAILBOX_INVALID_HANDLE;
}

irqreturn_t mailbox_spcu_irq(int irq,void *dev_id)
{
    MBOX_MSG_HEAD_U head;
    DRV_MAILBOX_RECEIVE_BUFFER_S *p = (DRV_MAILBOX_RECEIVE_BUFFER_S *) dev_id;

    if (p->status != MAILBOX_BUFFER_STATUS_NOMAL)
    {
        MAILBOX_PrintErrorCode(p->status);
        goto RET;
    }

    if (p == HI_NULL)
    {
        p->status = MAILBOX_BUFFER_STATUS_INVALID_PARAM;
        MAILBOX_PrintErrorCode(p->status);
        goto RET;
    }

    head.u32 = HAL_MAILBOX_ReadHeadFromScpu();
    if (head.bits.start == 1)
    {
        p->pos = 0;
    }

    if ((head.bits.length > HAL_MAILBOX_GetBodySizeFromScpu()) || (p->pos + head.bits.length > sizeof (p->buffer)))
    {
        p->status = MAILBOX_BUFFER_STATUS_INVALID_LEN;
        MAILBOX_ERR_PrintHex(head.bits.length);
        MAILBOX_ERR_PrintHex(p->pos);
        goto RET;
    }

    HAL_MAILBOX_ReadBodyFromScpu(p->buffer + p->pos, head.bits.length);

    p->pos    += head.bits.length;

    if (head.bits.end == 1)
    {
        p->status = MAILBOX_BUFFER_STATUS_FINISH;
        wake_up(&(p->receive_queue));
        goto RET;
    }

RET:
    HAL_MAILBOX_CleanIntrFromScpu();
    return IRQ_HANDLED;
}

HI_S32 DRV_MAILBOX_Init(HI_VOID)
{
    HI_S32 i;
    HI_S32 ret = HI_FAILURE;

    for (i = 0; i < DRV_MAILBOX_MAX_SESSION_NUM; i++)
    {
        s_mailbox_session.handle[i] = HI_INVALID_HANDLE;
    }

    ret = HAL_MAILBOX_Init();
    if (HI_SUCCESS != ret)
    {
        MAILBOX_PrintErrorFunc(HAL_MAILBOX_Init, ret);
        return ret;
    }

    pReceiveBuffer = (DRV_MAILBOX_RECEIVE_BUFFER_S *) HI_VMALLOC (HI_ID_MAILBOX, sizeof (DRV_MAILBOX_RECEIVE_BUFFER_S));
    if (HI_NULL == pReceiveBuffer)
    {
        HAL_MAILBOX_DeInit();
        MAILBOX_PrintErrorCode(HI_ERR_MAILBOX_NO_MEMORY);
        return HI_ERR_MAILBOX_NO_MEMORY;
    }

    pReceiveBuffer->pos = 0;
    pReceiveBuffer->status = MAILBOX_BUFFER_STATUS_BUTT;
    init_waitqueue_head(&pReceiveBuffer->receive_queue);

    ret = osal_request_irq(DRV_MAILBOX_INTERRUPT_IRQ, (irq_handler_t)mailbox_spcu_irq, IRQF_SHARED, DRV_MAILBOX_IRQ_NAME, pReceiveBuffer);
    if (HI_SUCCESS != ret)
    {
        HAL_MAILBOX_DeInit();
        HI_VFREE (HI_ID_MAILBOX, pReceiveBuffer);
        MAILBOX_PrintErrorFunc(osal_request_irq, ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_MAILBOX_DeInit(HI_VOID)
{
    HI_S32 i;

    for (i = 0; i < DRV_MAILBOX_MAX_SESSION_NUM; i++)
    {
        s_mailbox_session.handle[i] = HI_INVALID_HANDLE;
    }

    HAL_MAILBOX_DeInit();
    osal_free_irq(DRV_MAILBOX_INTERRUPT_IRQ, DRV_MAILBOX_IRQ_NAME, pReceiveBuffer);

    HI_VFREE (HI_ID_MAILBOX, pReceiveBuffer);

    return HI_SUCCESS;
}

HI_S32 HI_DRV_MAILBOX_Open(HI_HANDLE* pHandle, HI_U32 u32Id)
{
    return DRV_MAILBOX_Open(pHandle, u32Id);
}

HI_S32 HI_DRV_MAILBOX_Close(HI_HANDLE handle)
{
    return DRV_MAILBOX_Close(handle);
}

HI_S32 HI_DRV_MAILBOX_SendMessage(HI_HANDLE handle, HI_U32 receiver, HI_DRV_MAILBOX_BUFFER_S *buffer_info, HI_U32 flag, HI_U32 param)
{
    DRV_MAILBOX_BUFFER_S buffer;

    buffer.pMessage = buffer_info->pMessage;
    buffer.pOutBuffer = buffer_info->pOutBuffer;
    buffer.pu32OutBufferLen = buffer_info->pu32OutBufferLen;
    buffer.u32MessageLen = buffer_info->u32MessageLen;

    return DRV_MAILBOX_SendMessage(handle, receiver, &buffer, flag, param);
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

