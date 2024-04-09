/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_mailbox.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hal_mailbox.h"
#include "hal_mailbox_reg.h"

#include "drv_mailbox_debug.h"

#include <asm/io.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define read_register(addr)              *(volatile unsigned int *)(addr)
#define write_register(addr,value)       (*(volatile unsigned int *)(addr)) = (value)

static HI_U8 *s_scpu_base_addr = HI_NULL;
static HI_U8 *s_smcu_base_addr = HI_NULL;

static HI_VOID write_body(HI_U8 *addr, HI_U8 *message, HI_U32 message_len)
{
    HI_S32 i;
    HI_U32 last = 0;

    for (i = 0; i < (message_len / 4); i++)
    {
        write_register(addr + i * 4, (*(HI_U32 *)&message[i * 4]));
    }

    if (message_len % 4 != 0)
    {
        memcpy((HI_U8 *)&last, (HI_U8 *)(message + i * 4), message_len % 4);
        write_register(addr + i * 4, last);
    }
}

static HI_VOID write_head(HI_U8 *addr, HI_U32 head)
{
    write_register(addr, head);
    return;
}

static HI_VOID write_send(HI_U8 *addr)
{
    MBOX_CDM_SEND_U send;

    send.u32 = 0;
    send.bits.cmd_send = 1;

    write_register(addr, send.u32);
    return;
}

static HI_VOID read_body(HI_U8 *addr, HI_U8 *output, HI_U32 output_length)
{
    HI_U32 buffer[4] = {0};
    HI_S32 i;

    for (i = 0; i < 4; i++)
    {
        buffer[i] = read_register(addr + 4 * i);
    }

    memcpy(output, (HI_U8 *)buffer, output_length);

    return;
}

static HI_U32 read_head(HI_U8 *addr)
{
    return read_register(addr);
}

HI_S32 HAL_MAILBOX_WriteHeadToScpu(HI_U32 receive, HI_U32 length, HI_BOOL start, HI_BOOL end)
{
    MBOX_MSG_HEAD_U head;

    head.u32 = 0;

    head.bits.length   = length;
    head.bits.receiver = receive;
    head.bits.sender   = 0x60;
    head.bits.start    = start;
    head.bits.end      = end;

    write_head(s_scpu_base_addr + ACPU_TO_SCPU_HEAD_ADDRESS, head.u32);

    MAILBOX_DBG_PrintHex(s_scpu_base_addr + ACPU_TO_SCPU_HEAD_ADDRESS);
    MAILBOX_DBG_PrintHex(head.u32);

    return HI_SUCCESS;
}

HI_S32 HAL_MAILBOX_WriteBodyToScpu(HI_U8 *message, HI_U32 length)
{
    if ((HI_NULL == message) || (length == 0) || (length > ACPU_TO_SCPU_ARGS_NUM * 4))
    {
        return HI_FAILURE;
    }

    write_body(s_scpu_base_addr + ACPU_TO_SCPU_ARGS_ADDRESS, message, length);

    MAILBOX_DBG_PrintHex(s_scpu_base_addr + ACPU_TO_SCPU_ARGS_ADDRESS);
    MAILBOX_DBG_DUMP("body", message, length);

    return HI_SUCCESS;
}

HI_U32 HAL_MAILBOX_ReadHeadFromScpu()
{
    return read_head(s_scpu_base_addr + SCPU_TO_ACPU_HEAD_ADDRESS);
}


HI_S32 HAL_MAILBOX_ReadBodyFromScpu(HI_U8 *message, HI_U32 length)
{
    HI_U32 read_length = 0;

    if ((HI_NULL == message) || (length == 0))
    {
        return HI_FAILURE;
    }

    read_length = (length < SCPU_TO_ACPU_ARGS_NUM * 4) ? length : SCPU_TO_ACPU_ARGS_NUM * 4;

    read_body(s_scpu_base_addr + SCPU_TO_ACPU_ARGS_ADDRESS, message, read_length);

    return HI_SUCCESS;
}


HI_VOID HAL_MAILBOX_SetSendCmdToScpu()
{
    MAILBOX_DBG_PrintHex(s_scpu_base_addr + ACPU_TO_SCPU_SEND_ADDRESS);
    write_send(s_scpu_base_addr + ACPU_TO_SCPU_SEND_ADDRESS);
}

HI_BOOL HAL_MAILBOX_CheckScpuReceive()
{
    MBOX_INTR_STATUS_U state;

    state.u32 = read_register(s_scpu_base_addr + SCPU_INTR_FROM_ACPU_ADDRESS);

    MAILBOX_DBG_PrintHex(s_scpu_base_addr + SCPU_INTR_FROM_ACPU_ADDRESS);
    MAILBOX_DBG_PrintHex(state.u32);

    return state.bits.intr == 0 ? HI_TRUE : HI_FALSE;
}

HI_BOOL HAL_MAILBOX_CheckScpuSend()
{
    MBOX_INTR_STATUS_U state;

    state.u32 = read_register(s_scpu_base_addr + ACPU_INTR_FROM_SCPU_ADDRESS);

    return state.bits.intr == 1 ? HI_TRUE : HI_FALSE;
}

HI_VOID HAL_MAILBOX_CleanIntrFromScpu()
{
    MBOX_INTR_STATUS_U state;

    state.u32 = 0;
    state.bits.intr = 1;

    write_register(s_scpu_base_addr + ACPU_INTR_FROM_SCPU_ADDRESS, state.u32);
}


HI_S32 HAL_MAILBOX_WriteHeadToSmcu(HI_U32 receive, HI_U32 length, HI_BOOL start, HI_BOOL end)
{
    MBOX_MSG_HEAD_U head;

    head.u32 = 0;

    head.bits.length   = length;
    head.bits.receiver = receive;
    head.bits.sender   = 0x60;
    head.bits.start    = start;
    head.bits.end      = end;

    write_head(s_smcu_base_addr + ACPU_TO_SMCU_HEAD_ADDRESS, head.u32);
    return HI_SUCCESS;
}

HI_U32  HAL_MAILBOX_GetBodySizeToScpu()
{
    return ACPU_TO_SCPU_ARGS_NUM * 4;
}


HI_S32 HAL_MAILBOX_WriteBodyToSmcu(HI_U8 *message, HI_U32 length)
{
    if ((HI_NULL == message) || (length == 0) || (length > ACPU_TO_SMCU_ARGS_NUM * 4))
    {
        return HI_FAILURE;
    }

    write_body(s_smcu_base_addr + ACPU_TO_SMCU_ARGS_ADDRESS, message, length);

    return HI_SUCCESS;
}

HI_U32 HAL_MAILBOX_ReadHeadFromSmcu()
{
    return read_head(s_smcu_base_addr + SMCU_TO_ACPU_HEAD_ADDRESS);
}


HI_S32 HAL_MAILBOX_ReadBodyFromSmcu(HI_U8 *message, HI_U32 length)
{
    HI_U32 read_length = 0;

    if ((HI_NULL == message) || (length == 0))
    {
        return HI_FAILURE;
    }

    read_length = (length < SMCU_TO_ACPU_ARGS_NUM * 4) ? length : SMCU_TO_ACPU_ARGS_NUM * 4;

    read_body(s_smcu_base_addr + SMCU_TO_ACPU_ARGS_ADDRESS, message, read_length);

    return HI_SUCCESS;
}


HI_VOID HAL_MAILBOX_SetSendCmdToSmcu()
{
    write_send(s_smcu_base_addr + ACPU_TO_SMCU_SEND_ADDRESS);
}

HI_BOOL HAL_MAILBOX_CheckSmcuReceive()
{
    MBOX_INTR_STATUS_U state;

    state.u32 = read_register(s_smcu_base_addr + SMCU_INTR_FROM_ACPU_ADDRESS);

    return state.bits.intr == 0 ? HI_TRUE : HI_FALSE;

}

HI_BOOL HAL_MAILBOX_CheckSmcuSend()
{
    MBOX_INTR_STATUS_U state;

    state.u32 = read_register(s_smcu_base_addr + ACPU_INTR_FROM_SMCU_ADDRESS);

    return state.bits.intr == 1 ? HI_TRUE : HI_FALSE;
}

HI_VOID HAL_MAILBOX_CleanIntrFromSmcu()
{
    MBOX_INTR_STATUS_U state;

    state.u32 = 0;
    state.bits.intr = 1;

    write_register(s_smcu_base_addr + ACPU_INTR_FROM_SMCU_ADDRESS, state.u32);
}

HI_U32  HAL_MAILBOX_GetBodySizeToSmcu()
{
    return ACPU_TO_SMCU_ARGS_NUM * 4;
}

HI_U32  HAL_MAILBOX_GetBodySizeFromSmcu()
{
    return SMCU_TO_ACPU_ARGS_NUM * 4;
}

HI_U32  HAL_MAILBOX_GetBodySizeFromScpu()
{
    return SCPU_TO_ACPU_ARGS_NUM * 4;
}


HI_S32 HAL_MAILBOX_Init(HI_VOID)
{
    s_scpu_base_addr = ioremap_nocache(ACPU_TO_SCPU_BASE_ADDRESS, 0x420);
    if (HI_NULL == s_scpu_base_addr)
    {
        return HI_FAILURE;
    }

    s_smcu_base_addr = ioremap_nocache(ACPU_TO_SMCU_BASE_ADDRESS, 0x420);
    if (HI_NULL == s_smcu_base_addr)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_MAILBOX_DeInit(HI_VOID)
{
    if (HI_NULL == s_scpu_base_addr)
    {
        iounmap(s_scpu_base_addr);
    }

    if (HI_NULL == s_smcu_base_addr)
    {
        iounmap(s_smcu_base_addr);
    }

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

