/******************************************************************************
 *  Copyright (C) 2016 Hisilicon Technologies CO.,LTD.
 *
 * Create By Hisilicon 2017.4.15
 *
******************************************************************************/

#ifndef MAILBOX_H
#define MAILBOX_H

#define MBX_REG_BASE                    (0xF8ABD000)

#define CMD_ACPU_TO_SCPU(x)             (MBX_REG_BASE + 0x40 + (x) * 4)
#define CMD_SCPU_TO_ACPU(x)             (MBX_REG_BASE + 0x110 + (x) * 4)
#define SCPU_INTR_FROM_ACPU_STATUS      (MBX_REG_BASE + 0x408)
#define CMD_SEND_ACPU_TO_SCPU           (MBX_REG_BASE + 0x400)
#define ACPU_INTR_STATUS                (MBX_REG_BASE + 0x418)

#define MAX_MBX_ARGC                    0x4

typedef union
{
    struct {
        unsigned int scpu_intr_from_acpu             : 1; //[0]
        unsigned int reserved                        : 31; //[31:1]
    } bits;
    unsigned int u32;
} SCPU_INTR_FROM_ACPU_STATUS_U;                   //0x40C

typedef union
{
    struct {
        unsigned int cmd_send_acpu2scpu              : 1; //[0]
        unsigned int reserved                        : 31; //[31:1]
    } bits;
    unsigned int u32;
} CMD_SEND_ACPU_TO_SCPU_U;                   //0x414

typedef union
{
    struct {
        unsigned int acpu_intr                       : 1; //[0]
        unsigned int reserved                        : 31; //[31:1]
    } bits;
    unsigned int u32;
} ACPU_INTR_STATUS_U;                   //0x41C

typedef enum
{
    MBX_TYPE_SW_RESET            = 0x4B3C2D1E,
    MBX_TYPE_SOS_PROCESS         = 0x4B3C2D2D,
    MBX_TYPE_CAS_LOADER_PROCESS  = 0x4B3C2D3C,
    MBX_TYPE_TRNG_GET            = 0x4B3C2D4B,
    MBX_TYPE_CMD_PROCESS_OK      = 0x4B3CD2C3,
    MBX_TYPE_CMD_PROCESS_FAILURE = 0xB4C32D3C,
    MBX_TYPE_MBX_TYPE_BUTT
} MBX_TYPE_E;

int mailbox_get(unsigned int *command, unsigned int *argv, unsigned int wait_ms);
int mailbox_set(unsigned int *command, unsigned int *argv, unsigned int argc, unsigned int wait_ms);

#endif /* MAILBOX_H*/
