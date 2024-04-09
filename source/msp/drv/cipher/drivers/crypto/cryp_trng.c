/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : cryp_trng.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "drv_trng.h"
#include "cryp_trng.h"

/********************** Internal Structure Definition ************************/
/** \addtogroup      trng */
/** @{*/  /** <!-- [trng]*/

/* the max continuous bits of randnum is allowed */
#define CONTINUOUS_BITS_ALLOWD              0x08

/* times try to read rang  */
#define RANG_READ_TRY_TIME                  0x40

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      trng drivers*/
/** @{*/  /** <!-- [trng]*/

#ifdef CHIP_TRNG_SUPPORT
static s32 cryp_trng_check(u32 randnum)
{
#if 0
    static u32 lastrand = 0;
    u8 *byte = HI_NULL;
    u32 i;

    /* compare with last rand number */
    if (randnum == lastrand)
    {
        return HI_FAILURE;
    }

    /* update last randnum */
    lastrand = randnum;
    byte = (u8*)&randnum;

    /* continuous 8 bits0 or bit1 is prohibited */
    for (i=0; i<4; i++)
    {
        /* compare with 0x00 and 0xff */
        if (byte[i] == 0x00 || byte[i] == 0xff)
        {
            return HI_FAILURE;
        }
    }
#else
    /* continuous 32 bits0 or bit1 is prohibited */
    if (0x00000000 == randnum || 0xffffffff == randnum)
    {
        return HI_FAILURE;
    }
#endif
    return HI_SUCCESS;
}

s32 cryp_trng_get_random(u32 *randnum, u32 timeout)
{
    u32 i = 0;
    s32 ret = HI_FAILURE;
    trng_capacity capacity;

    HI_LOG_FuncEnter();

    drv_trng_get_capacity(&capacity);
    if (!capacity.trng)
    {
        HI_LOG_ERROR("error, trng nonsupport\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_UNSUPPORTED);
        return HI_ERR_CIPHER_UNSUPPORTED;
    }

    for (i=0; i<RANG_READ_TRY_TIME; i++)
    {
        ret = drv_trng_randnum(randnum, timeout);
        if (HI_SUCCESS != ret)
        {
            return ret;
        }

        ret = cryp_trng_check(*randnum);
        if (HI_SUCCESS == ret)
        {
           break;
        }
    }

    if (RANG_READ_TRY_TIME <= i)
    {
        HI_LOG_ERROR("error, trng randnum check failed\n");
        return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 cryp_trng_get_random_bytes(u8 *randbyte, u32 size, u32 timeout)
{
    s32 ret = HI_FAILURE;
    u32 i;
    u32 cnt = 0;
    u32 randnum = 0;

    HI_LOG_FuncEnter();

    cnt = size / WORD_WIDTH;
    for(i=0; i < cnt; i++)
    {
        ret = cryp_trng_get_random(&randnum, timeout);
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
        crypto_memcpy(randbyte, WORD_WIDTH, &randnum, WORD_WIDTH);
        randbyte += WORD_WIDTH;
    }

    /* less then 4 byte */
    for(i=cnt * WORD_WIDTH; i < size; i++)
    {
        ret = cryp_trng_get_random(&randnum, timeout);
        if (HI_SUCCESS != ret)
        {
            return ret;
        }
        *randbyte++ = randnum & 0xFF;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

#else

#include "drv_osal_tee.h"
#include <linux/random.h>

s32 cryp_trng_get_random_bytes(u8 *randbyte, u32 size, u32 timeout)
{
    HI_LOG_FuncEnter();

#if defined(HI_TEE_SUPPORT) && !defined(TEE_CIPHER_TA_NONSUPPORT)
    {
        s32 ret = HI_FAILURE;

        /* read trng from tee, require tee support cipher ta
         * used by ree with non-secure CPU
         * weakness vs get_random_bytes:
         * reduce the performance
         * unsupport multithread
         *
         */
        ret = drv_osal_tee_command(TEEC_CMD_GET_TRNG, randbyte, size);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_osal_tee_command, ret);
            drv_osal_tee_close_session();
            return ret;
        }
    }
#else
    /* used by loader with non-secure CPU */
    get_random_bytes((u8*)randbyte, size);
#endif

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 cryp_trng_get_random(u32 *randnum, u32 timeout)
{
    return cryp_trng_get_random_bytes((u8*)randnum, WORD_WIDTH, timeout);
}

#endif

/** @}*/  /** <!-- ==== API Code end ====*/
