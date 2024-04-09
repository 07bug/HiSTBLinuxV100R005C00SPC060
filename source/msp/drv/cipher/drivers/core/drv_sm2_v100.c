/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_sm2_v100.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_sm2_v100.h"
#include "drv_sm2.h"
#include "drv_trng.h"

#ifdef CHIP_SM2_VER_V100

/*************************** Structure Definition ****************************/
/** \addtogroup     sm2 */
/** @{ */  /** <!-- [sm2] */


/*! Define the time out */
#define SM2_TIME_OUT                 5000

/*! Define the start code */
#define SM2_START_CODE               0x05

/*! Define the error code */
#define SM2_ERROR_CODE_SUCCESS       0x05

/*! Define the key type */
#define SM2_KEY_CFG_PRIVATE          0x05
#define SM2_KEY_CFG_PUBLIC           0x0a

/*! Define the length of zero padding for mul-dot */
#define SM2_MUL_DOT_ZERO_LEN         56

/*! Define the int code */
#define SM2_ALARM_INT_NONE           0x0a
#define SM2_ALARM_INT_DONE           0x05
#define SM2_FINISK_INT_NONE          0x03
#define SM2_FINISK_INT_DONE          0x0c

/* crc 16 */
#define CRC16_TABLE_SIZE          256
#define U16_MSB                   0x8000
#define CRC16_POLYNOMIAL          0x1021
#define BYTE_BITS                 0x08
#define BYTE_MASK                 0xFF


/*! Define the constant value */
const u32 sm2wp[SM2_LEN_IN_WROD] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01000000};
const u32 sm2N[SM2_LEN_IN_WROD] =  {0x12E4B51E, 0x3B3D2BA2, 0x4CC80F62, 0xD4E0FF3A, 0x4A506434, 0xFAA26FDE, 0xAF921190, 0x204F117C};
const u32 sm2wn[SM2_LEN_IN_WROD] = {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x889E7F32, 0x75093572};
const u32 sm21[SM2_LEN_IN_WROD] =  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x01000000};
const u32 sm20[SM2_LEN_IN_WROD] =  {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000};
const u32 sm2ma[SM2_LEN_IN_WROD] = {0xFBFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFCFFFFFF, 0x03000000, 0xFFFFFFFF, 0xFCFFFFFF};
const u32 sm2mb[SM2_LEN_IN_WROD] = {0x88E10F24, 0xC8E220BA, 0x50817952, 0x3C1CA55E, 0x9A37CF71, 0xAB37B5E9, 0x6330D290, 0x42DDC02B};
const u32 sm2m1[SM2_LEN_IN_WROD] = {0x01000000, 0x00000000, 0x00000000, 0x00000000, 0x9420fc8d, 0xd4fa39de, 0xf60b44ac, 0xddbe2ac6};

const char * err_string[] =
{
    "SM2 is still running",
    "The operation of mod inverse is failed",
    "Get randnum failed",
    "Attacked by DFA",
    "The result of mod add/multiply is infinity"
};

/*! Define the context of sm2 */
typedef struct
{
    u32 done;                   /*!<  calculation finish flag*/
    crypto_queue_head  queue;   /*!<  quene list */
    u32 attacked;               /*!<  if be attacked, don't compute any more */
}sm2_hard_context;

static sm2_hard_context sm2info;

/*! sm2 already initialize or not */
static u32 sm2_initialize = HI_FALSE;
static u16 crc_table[CRC16_TABLE_SIZE];

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      sm2 */
/** @{ */  /** <!--[sm2]*/

static void drv_sm2_crc16_init(void)
{
    u16 nRemainder;
    u16 n, m;
    u16  *pulTable = crc_table;

    for (n = 0; n < CRC16_TABLE_SIZE; n ++)
    {
        nRemainder = (HI_U16)n << BYTE_BITS;
        for (m = BYTE_BITS; m > 0; m --)
        {
            if (nRemainder & U16_MSB)
            {
                nRemainder = (nRemainder << 1) ^ CRC16_POLYNOMIAL;
            }
            else
            {
                nRemainder = (nRemainder << 1);
            }
        }
        *(pulTable + n) = nRemainder;
    }
}

u16 static drv_sm2_crc16_key(u16 initial, u32 key[SM2_LEN_IN_WROD])
{
    u32 i, j;
    u16 crc16 = 0x0000;
    u8 *p = HI_NULL;

    crc16 = initial;

    for (i = 0; i < SM2_LEN_IN_WROD; i+=2)
    {
        p = (u8*)&key[SM2_LEN_IN_WROD - i - 2];
        for (j=0; j<4; j++)
        {
            crc16 = (crc16 << BYTE_BITS) ^ crc_table[((crc16 >> BYTE_BITS) ^ p[j]) & BYTE_MASK];
        }

        p = (u8*)&key[SM2_LEN_IN_WROD - i - 1];
        for (j=0; j<4; j++)
        {
            crc16 = (crc16 << BYTE_BITS) ^ crc_table[((crc16 >> BYTE_BITS) ^ p[j]) & BYTE_MASK];
        }
    }

    return crc16;
}

/*crc = CRC16(crc, randnum)*/
static u16 drv_sm2_crc16_random(u16 initial, u32 random[2])
{
    u32 i;
    u16 crc16 = 0x0000;
    u8 *p = HI_NULL;

    crc16 = initial;
    p = (u8*)&random[1];
    for (i=0; i<WORD_WIDTH; i++)
    {
        crc16 = (crc16 << BYTE_BITS) ^ crc_table[((crc16 >> BYTE_BITS) ^ p[i]) & BYTE_MASK];
    }

    p = (u8*)&random[0];
    for (i=0; i<WORD_WIDTH; i++)
    {
        crc16 = (crc16 << BYTE_BITS) ^ crc_table[((crc16 >> BYTE_BITS) ^ p[i]) & BYTE_MASK];
    }

    return crc16;
}

/*crc = CRC16(crc, 0)*/
static u16 drv_sm2_crc16_zero(u16 initial, u32 len)
{
    u32 i;
    u16 crc16 = 0x0000;

    crc16 = initial;

    for (i = 0; i < len; i++)
    {
        crc16 = (crc16 << BYTE_BITS) ^ crc_table[((crc16 >> BYTE_BITS) ^ 0x00) & BYTE_MASK];
    }

    return crc16;
}


static u32 sm2_done_try(void)
{
    U_SM2_INT_NOMASK_STATUS int_raw;
    u32 mask = 0;

    int_raw.u32 = SM2_READ(SM2_REG_NOMASK_STATUS);

    mask = (SM2_ALARM_INT_DONE == int_raw.bits.alarm_int_nomsk_status)
        || (SM2_FINISK_INT_DONE == int_raw.bits.finish_int_nomsk_status);

    if (mask)
    {
        int_raw.bits.finish_int_nomsk_status = 1;
        int_raw.bits.alarm_int_nomsk_status = 1;

        /*Clean raw int*/
        SM2_WRITE(SM2_REG_NOMASK_STATUS, int_raw.u32);
    }

    return mask;
}

#ifdef CRYPTO_OS_INT_SUPPORT
static u32 sm2_done_notify(void)
{
    U_SM2_INT_STATUS int_st;
    U_SM2_INT_NOMASK_STATUS int_raw;

    int_st.u32 = SM2_READ(SM2_REG_INT_STATUS);
    int_raw.u32 = 0x00;

    int_raw.bits.finish_int_nomsk_status = 1;
    int_raw.bits.alarm_int_nomsk_status = 1;

    /*Clean raw int*/
    SM2_WRITE(SM2_REG_NOMASK_STATUS, int_raw.u32);

    return (SM2_ALARM_INT_DONE == int_st.bits.alarm_int_status)
        || (SM2_FINISK_INT_DONE == int_st.bits.finish_int_status);
}

/*! sm2 interrupt process function */
static irqreturn_t sm2_interrupt_isr(s32 irq, void *devId)
{
    CRYPTO_UNUSED(irq);

    sm2_done_notify();

    sm2info.done = HI_TRUE;
    HI_LOG_DEBUG("sm2 wake up\n");
    crypto_queue_wait_up(&sm2info.queue);

    return IRQ_HANDLED;
}

/*! set interrupt */
static void sm2_set_interrupt(void)
{
    u32 int_valid = 0, int_num = 0;
    U_SM2_INT_ENABLE sm2_int_en;

    (void)module_get_attr(CRYPTO_MODULE_ID_SM2, &int_valid, &int_num, HI_NULL);
    if (HI_FALSE == int_valid)
    {
        return;
    }

    sm2_int_en.u32 = SM2_READ(SM2_REG_INT_ENABLE);

    /*The top interrupt switch only can be enable/disable by secure CPU*/
    sm2_int_en.bits.sm2_all_int_enable = 1;
    sm2_int_en.bits.sm2_err_int_enable = 1;
    sm2_int_en.bits.sm2_finish_int_enable = 1;
    SM2_WRITE(SM2_REG_INT_ENABLE, sm2_int_en.u32);
    HI_LOG_INFO("SM2_INT_EN: 0x%x\n", sm2_int_en.u32);

    return;
}

/*! sm2 register interrupt process function */
static s32 drv_sm2_register_interrupt(void)
{
    s32 ret = HI_FAILURE;
    u32 int_valid = 0, int_num = 0;
    const char *name;

    HI_LOG_FuncEnter();

    module_get_attr(CRYPTO_MODULE_ID_SM2, &int_valid, &int_num, &name);
    if (HI_FALSE == int_valid)
    {
        return HI_SUCCESS;
    }

    /* request irq */
    ret = crypto_request_irq(int_num, sm2_interrupt_isr, name);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("Irq request failure, irq = %d", int_num);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_REGISTER_IRQ);
        return ret;
    }

    /* initialize queue list*/
    crypto_queue_init(&sm2info.queue);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*! sm2 unregister interrupt process function */
static void drv_sm2_unregister_interrupt(void)
{
    u32 int_valid = 0, int_num = 0;
    const char *name = HI_NULL;

    HI_LOG_FuncEnter();

    module_get_attr(CRYPTO_MODULE_ID_SM2, &int_valid, &int_num, &name);
    if (HI_FALSE == int_valid)
    {
        return;
    }

    /* free irq */
    HI_LOG_DEBUG("sm2 free irq, num %d, name %s\n", int_num, name);
    crypto_free_irq(int_num, name);

    HI_LOG_FuncExit();

    return;
}
#endif

s32 drv_sm2_init(void)
{
    HI_LOG_FuncEnter();

    HI_LOG_INFO("enable sm2\n");

    if (sm2_initialize)
    {
        return HI_SUCCESS;
    }

    module_disable(CRYPTO_MODULE_ID_SM2);

    drv_sm2_crc16_init();

#ifdef CRYPTO_OS_INT_SUPPORT
    {
        s32 ret = HI_SUCCESS;

        HI_LOG_INFO("sm2 register interrupt function\n");
        ret = drv_sm2_register_interrupt();
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("error, register interrupt failed\n");
            HI_LOG_PrintFuncErr(drv_sm2_register_interrupt, ret);
            module_disable(CRYPTO_MODULE_ID_SM2);
            return ret;
        }
    }
#endif

    sm2_initialize = HI_TRUE;
    sm2info.done = HI_TRUE;
    sm2info.attacked = HI_FALSE;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_sm2_deinit(void)
{
    HI_LOG_INFO("disable sm2\n");

    if (HI_FALSE == sm2_initialize)
    {
        return HI_SUCCESS;
    }

#ifdef CRYPTO_OS_INT_SUPPORT
    drv_sm2_unregister_interrupt();
#endif

    sm2_initialize = HI_FALSE;

    return HI_SUCCESS;
}

s32 drv_sm2_resume(void)
{
    HI_LOG_FuncEnter();

    module_enable(CRYPTO_MODULE_ID_SM2);

#ifdef CRYPTO_OS_INT_SUPPORT
    HI_LOG_INFO("sm2 interrupt configure\n");
    sm2_set_interrupt();
#endif

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_sm2_suspend(void)
{
    HI_LOG_FuncEnter();

    module_disable(CRYPTO_MODULE_ID_SM2);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static void drv_sm2_set_ram(SM2_RAM_TYPE_S type, u32 section, const u32 ram[SM2_LEN_IN_WROD], u32 zero)
{
    u32 start = 0;
    u32 end = 0;
    u32 val = 0;
    u32 i;

    start = SM2_REG_MRAM + SM2_RAM_RANG_SIZE * type
        + section * SM2_RAM_SECTION_SIZE_IN_WORD * WORD_WIDTH;
    end = start + SM2_RAM_SECTION_SIZE_IN_WORD * WORD_WIDTH;

    for (i=0; i<SM2_LEN_IN_WROD; i++)
    {
        val = CPU_TO_BE32(ram[SM2_LEN_IN_WROD - i - 1]);
        SM2_WRITE(start, val);
        start += WORD_WIDTH;
    }

    /* padding with zero at high byte */
    if (zero)
    {
        while(start < end)
        {
            SM2_WRITE(start, 0x00);
            start += WORD_WIDTH;
        }
    }
    return;
}

static void drv_sm2_get_ram(SM2_RAM_TYPE_S type, u32 section, u32 ram[SM2_LEN_IN_WROD * 2])
{
    u32 addr = 0;
    u32 val = 0;
    u32 len = SM2_LEN_IN_WROD;
    u32 i;

    /* when compute mul, the result is store in 0x00~0x40 */
    if (SM2_RAM_TYPE_MRAM == type)
    {
        len = SM2_LEN_IN_WROD * 2;
    }

    addr = SM2_REG_MRAM + SM2_RAM_RANG_SIZE * type
        + section * SM2_RAM_SECTION_SIZE_IN_WORD * WORD_WIDTH;

    for (i=0; i<len; i++)
    {
        val = SM2_READ(addr + i * WORD_WIDTH);
        ram[len - i - 1]  = CPU_TO_BE32(val);
    }
    return;
}

static void drv_sm2_set_mode(SM2_MODEA_S mode, SM2_OPCODE_S opcode)
{
    U_SM2_WORK_MODE work;

    work.u32 = 0x00;

    if (SM2_OPCODE_CLR_RAM != opcode)
    {
        work.bits.mode = 0x04; /* fix */
    }
    else
    {
        work.bits.mode = mode;
    }
    work.bits.opcode = opcode;

    SM2_WRITE(SM2_REG_WORK_MODE, work.u32);
    HI_LOG_DEBUG("SM2_REG_WORK_MODE 0x%x\n", work.u32);
    return;
}

static void drv_sm2_start(void)
{
    U_SM2_START start;

    HI_LOG_FuncEnter();

    start.u32 = 0x00;
    start.bits.sm2_start = SM2_START_CODE;

    SM2_WRITE(SM2_REG_STRAT, start.u32);
    HI_LOG_DEBUG("SM2_REG_STRAT 0x%x\n", start.u32);

    HI_LOG_FuncExit();

    return;
}

static s32 drv_sm2_wait_free(void)
{
    u32 i = 0;
    U_SM2_BUSY busy;

    HI_LOG_FuncEnter();

    /* wait ready */
    for (i=0; i<SM2_TIME_OUT; i++)
    {
        busy.u32 = SM2_READ(SM2_REG_BUSY);
        if (!busy.bits.sm2_busy)
        {
            break;
        }
        crypto_msleep(1);
    }

    if (SM2_TIME_OUT <= i)
    {
        HI_LOG_ERROR("error, sm2 wait free timeout\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_TIMEOUT);
        return HI_ERR_CIPHER_TIMEOUT;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 drv_sm2_error_code(void)
{
    u32 code = 0, result = 0;

    HI_LOG_FuncEnter();

    result = SM2_READ(SM2_REG_RESULT_FLAG);
    if (SM2_ERROR_CODE_SUCCESS != result)
    {
        code = SM2_READ(SM2_REG_FAILURE_FLAGS);
        HI_LOG_ERROR("SM2 operation failed: %s\n", err_string[code]);
        CRYPTO_UNUSED(code);
        sm2info.attacked = HI_TRUE;
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_HARD_STATUS);
        return HI_ERR_CIPHER_HARD_STATUS;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/* wait sm2 done */
static s32 drv_sm2_wait_done(void)
{
    u32 int_valid = 0, int_num = 0;
    u32 i;
    s32 ret = HI_FAILURE;
    const char *name = HI_NULL;

    HI_LOG_FuncEnter();

    module_get_attr(CRYPTO_MODULE_ID_SM2, &int_valid, &int_num, &name);

#ifdef CRYPTO_OS_INT_SUPPORT
    /* interrupt support, wait irq*/
    if (int_valid)
    {
        /* wait interrupt */
        ret = crypto_queue_wait_timeout(sm2info.queue, sm2info.done != HI_FALSE, SM2_TIME_OUT);
        if (0x00 == ret)
        {
            HI_LOG_ERROR("wait done timeout\n");
            HI_LOG_PrintFuncErr(crypto_queue_wait_timeout, HI_ERR_CIPHER_TIMEOUT);
            return HI_ERR_CIPHER_TIMEOUT;
        }
        HI_LOG_FuncExit();
        return HI_SUCCESS;
    }
    else /* interrupt unsupport, query the raw interrupt flag*/
#endif
    {
        for (i=0; i<SM2_TIME_OUT; i++)
        {
            if (sm2_done_try())
            {
                HI_LOG_FuncExit();
                return HI_SUCCESS;
            }
            if (MS_TO_US >= i)
            {
                crypto_udelay(1);  /* short waitting for 1000 us */
            }
            else
            {
                crypto_msleep(1);  /* long waitting for 5000 ms*/
            }
        }

        HI_LOG_ERROR("sm2 wait done timeout\n");
        HI_LOG_PrintFuncErr(crypto_queue_wait_timeout, HI_ERR_CIPHER_TIMEOUT);
        ret = drv_sm2_error_code();
        return ret;
    }
}

static void drv_sm2_set_key(const u32 inkey[SM2_LEN_IN_WROD],
                            u32 outkey[SM2_LEN_IN_WROD],
                            u32 private, u32 zlen)
{
    u32 i;
    u32 random[2] = {0};
    u16 crc16 = 0;

    if (private)
    {
        random[0] = get_rand();
        random[1] = get_rand();

        for (i=0; i<SM2_LEN_IN_WROD; i+=2)
        {
           outkey[i] =  inkey[i] ^ random[1];
        }
        for (i=1; i<SM2_LEN_IN_WROD; i+=2)
        {
           outkey[i] =  inkey[i] ^ random[0];
        }
        crc16 = drv_sm2_crc16_key(0x0000, outkey);
        crc16 = drv_sm2_crc16_random(crc16, random);
        crc16 = drv_sm2_crc16_zero(crc16, zlen);

        /* set Random */
        SM2_WRITE(SM2_REG_KEY_RANDOM, CPU_TO_BE32(random[0]));
        SM2_WRITE(SM2_REG_KEY_RANDOM_A, CPU_TO_BE32(random[1]));

        /* set src16 */
        SM2_WRITE(SM2_REG_KEY_CRC, crc16);

        /* private key */
        SM2_WRITE(SM2_REG_KEY_CFG, SM2_KEY_CFG_PRIVATE);
    }
    else
    {
        /* not private key */
        SM2_WRITE(SM2_REG_KEY_CFG, SM2_KEY_CFG_PUBLIC);
        memcpy(outkey, inkey, SM2_LEN_IN_BYTE);
    }
    return;
}

/*c = a + b mod p*/
s32 drv_sm2_add_mod(const u32 a[SM2_LEN_IN_WROD],
                    const u32 b[SM2_LEN_IN_WROD],
                    const u32 p[SM2_LEN_IN_WROD],
                    u32 c[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);
    CRYPTO_ASSERT(HI_NULL != a);
    CRYPTO_ASSERT(HI_NULL != b);
    CRYPTO_ASSERT(HI_NULL != p);
    CRYPTO_ASSERT(HI_NULL != c);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_SIZE, SM2_OPCODE_ADD_MOD);

    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 0, a, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_NRAM, 0, p, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 0, b, HI_FALSE);

    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 mod add failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }

    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 0, c);
/*
    HI_PRINT_HEX ("Addmod-a", a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Addmod-b", b, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Addmod-p", p, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Addmod-c", c, SM2_LEN_IN_WROD*4);
*/
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*c = a - b mod p*/
s32 drv_sm2_sub_mod(const u32 a[SM2_LEN_IN_WROD],
                    const u32 b[SM2_LEN_IN_WROD],
                    const u32 p[SM2_LEN_IN_WROD],
                    u32 c[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);
    CRYPTO_ASSERT(a);
    CRYPTO_ASSERT(HI_NULL != b);
    CRYPTO_ASSERT(HI_NULL != p);
    CRYPTO_ASSERT(HI_NULL != c);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_SIZE, SM2_OPCODE_SUB_MOD);

    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 0, a, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 0, b, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_NRAM, 0, p, HI_FALSE);

    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 mod sub failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }

    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 0, c);
/*
    HI_PRINT_HEX ("Submod-a", a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Submod-b", b, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Submod-p", p, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Submod-c", c, SM2_LEN_IN_WROD*4);
*/

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*c = a * b mod p*/
s32 drv_sm2_mul_modp(const u32 a[SM2_LEN_IN_WROD],
                     const u32 b[SM2_LEN_IN_WROD],
                     u32 c[SM2_LEN_IN_WROD],
                     u32 private)
{
    s32 ret = HI_FAILURE;
    u32 key[SM2_LEN_IN_WROD] = {0};

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);
    CRYPTO_ASSERT(a);
    CRYPTO_ASSERT(HI_NULL != b);
    CRYPTO_ASSERT(HI_NULL != c);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_SIZE, SM2_OPCODE_MUL_MOD);
    drv_sm2_set_key(b, key, private, 0x00);

    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 0, a, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 0, key, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_NRAM, 0, sm2p, HI_FALSE);

    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 mod mul failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }
    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 0, c);
/*
    HI_PRINT_HEX ("Mulmodp-a", a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Mulmodp-b", b, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Mulmodp-p", sm2p, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Mulmodp-c", c, SM2_LEN_IN_WROD*4);
*/
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*c = a * b mod n*/
s32 drv_sm2_mul_modn(const u32 a[SM2_LEN_IN_WROD],
                     const u32 b[SM2_LEN_IN_WROD],
                     u32 c[SM2_LEN_IN_WROD],
                     u32 private)
{
    s32 ret = HI_FAILURE;
    u32 key[SM2_LEN_IN_WROD] = {0};

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);
    CRYPTO_ASSERT(a);
    CRYPTO_ASSERT(HI_NULL != b);
    CRYPTO_ASSERT(HI_NULL != c);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_SIZE, SM2_OPCODE_MUL_MOD);
    drv_sm2_set_key(b, key, private, 0x00);

    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 0, a, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 0, key, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_NRAM, 0, sm2n, HI_FALSE);
//  HAL_SM2_SetWP(s_u32wn[SM2_LEN_IN_WROD - 2], s_u32wn[SM2_LEN_IN_WROD - 1]);

    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 mod mul failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }

    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 0, c);
/*
    HI_PRINT_HEX ("Mulmodp-a", a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Mulmodp-b", b, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Mulmodp-p", sm2n, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Mulmodp-c", c, SM2_LEN_IN_WROD*4);
*/
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*c = a^-1 mod p*/
s32 drv_sm2_inv_mod(const u32 a[SM2_LEN_IN_WROD],
                    const u32 p[SM2_LEN_IN_WROD],
                    u32 c[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_SIZE, SM2_OPCODE_INV_MOD);

    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 0, a, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_NRAM, 0, p, HI_FALSE);

    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 mod inv failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }

    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 0, c);
/*
    HI_PRINT_HEX ("Invmod-a", a, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Invmod-p", p, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("Invmod-c", c, SM2_LEN_IN_WROD*4);
*/
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*c = a mod p*/
s32 drv_sm2_mod(const u32 a[SM2_LEN_IN_WROD],
                const u32 p[SM2_LEN_IN_WROD],
                u32 c[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);
    CRYPTO_ASSERT(a);
    CRYPTO_ASSERT(HI_NULL != p);
    CRYPTO_ASSERT(HI_NULL != c);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_SIZE, SM2_OPCODE_MOD);

    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 0, a, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_NRAM, 0, p, HI_FALSE);

    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 mod failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }

    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 0, c);
/*
    HI_PRINT_HEX ("mod-a", a, SM2_LEN_IN_BYTE);
    HI_PRINT_HEX ("mod-p", p, SM2_LEN_IN_BYTE);
    HI_PRINT_HEX ("mod-c", c, SM2_LEN_IN_BYTE);
*/
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*c = a * b*/
s32 drv_sm2_mul(const u32 a[SM2_LEN_IN_WROD],
                    const u32 b[SM2_LEN_IN_WROD],
                    u32 c[SM2_LEN_IN_WROD*2])
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);
    CRYPTO_ASSERT(a);
    CRYPTO_ASSERT(HI_NULL != b);
    CRYPTO_ASSERT(HI_NULL != c);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_SIZE, SM2_OPCODE_MUL);

    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 0, a, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_RRAM, 0, b, HI_FALSE);
    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 mul failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }

    drv_sm2_get_ram(SM2_RAM_TYPE_MRAM, 0, c);
/*
    HI_PRINT_HEX ("mul-a", a, SM2_LEN_IN_BYTE);
    HI_PRINT_HEX ("mul-b", b, SM2_LEN_IN_BYTE);
    HI_PRINT_HEX ("mul-c", c, SM2_LEN_IN_BYTE*2);
*/
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/* R = k . P(x,y) */
s32 drv_sm2_mul_dot(const u32 k[SM2_LEN_IN_WROD],
                    const u32 px[SM2_LEN_IN_WROD],
                    const u32 py[SM2_LEN_IN_WROD],
                    u32 rx[SM2_LEN_IN_WROD],
                    u32 ry[SM2_LEN_IN_WROD],
                    u32 private)
{
    s32 ret = HI_FAILURE;
    u32 key[SM2_LEN_IN_WROD] = {0};

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);
    CRYPTO_ASSERT(k);
    CRYPTO_ASSERT(px);
    CRYPTO_ASSERT(py);
    CRYPTO_ASSERT(rx);
    CRYPTO_ASSERT(ry);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_SIZE, SM2_OPCODE_MUL_DOT);
    drv_sm2_set_key(k, key, private, SM2_MUL_DOT_ZERO_LEN);

    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 0, px, HI_TRUE);
    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 1, py, HI_TRUE);
    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 2, sm2n, HI_TRUE);
    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 3, sm2b, HI_TRUE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 0, key, HI_TRUE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 1, sm2p, HI_TRUE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 2, sm2a, HI_TRUE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 3, sm2Gx, HI_TRUE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 4, sm2Gy, HI_TRUE);

    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 mul dot failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }

    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 0, rx);
    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 1, ry);
/*
    HI_PRINT_HEX ("MulDot-k", k, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulDot-Px", px, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulDot-Py", py, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulDot-Rx", rx, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("MulDot-Ry", ry, SM2_LEN_IN_WROD*4);
    HI_PRINT("CRC: 0x%02X\n", HAL_SM2_GetCrc16());
*/
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*C = S(x,y) + R(x,y)*/
s32 drv_sm2_add_dot(const u32 sx[SM2_LEN_IN_WROD],
                    const u32 sy[SM2_LEN_IN_WROD],
                    const u32 rx[SM2_LEN_IN_WROD],
                    const u32 ry[SM2_LEN_IN_WROD],
                    u32 cx[SM2_LEN_IN_WROD],
                    u32 cy[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);
    CRYPTO_ASSERT(sx);
    CRYPTO_ASSERT(sy);
    CRYPTO_ASSERT(rx);
    CRYPTO_ASSERT(ry);
    CRYPTO_ASSERT(cx);
    CRYPTO_ASSERT(cy);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_SIZE, SM2_OPCODE_ADD_DOT);

    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 0, sx, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_MRAM, 1, sy, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 1, sm2p, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 2, sm2a, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 3, rx, HI_FALSE);
    drv_sm2_set_ram(SM2_RAM_TYPE_KRAM, 4, ry, HI_FALSE);

    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 dot add failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }

    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 0, cx);
    drv_sm2_get_ram(SM2_RAM_TYPE_RRAM, 1, cy);
/*
    HI_PRINT_HEX ("AddDot-Sx", sx, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Sy", sy, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Rx", rx, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Ry", ry, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Cx", cx, SM2_LEN_IN_WROD*4);
    HI_PRINT_HEX ("AddDot-Cy", ry, SM2_LEN_IN_WROD*4);
*/
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 drv_sm2_clean_ram(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_INITED(sm2_initialize);
    HI_LOG_CHECK_PARAM(sm2info.attacked);

    sm2info.done = HI_FALSE;

    ret = drv_sm2_wait_free();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 wait ready failed!\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_free, ret);
        return ret;
    }

    drv_sm2_set_mode(SM2_MODEA_CLR_ALLRAM, SM2_OPCODE_CLR_RAM);
    drv_sm2_start();

    ret = drv_sm2_wait_done();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("SM2 clean ram failed\n");
        HI_LOG_PrintFuncErr(drv_sm2_wait_done, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void drv_sm2_get_capacity(sm2_capacity *capacity)
{
    crypto_memset(capacity, sizeof(sm2_capacity), 0,  sizeof(sm2_capacity));

    capacity->sm2 = CRYPTO_CAPACITY_SUPPORT;

    return;
}

/** @} */  /** <!-- ==== API declaration end ==== */

#endif //End of CHIP_SM2_VER_V100
