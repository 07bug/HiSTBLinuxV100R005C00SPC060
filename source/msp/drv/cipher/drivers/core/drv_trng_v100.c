/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_trng_v100.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_trng_v100.h"
#include "drv_trng.h"

#ifdef CHIP_TRNG_VER_V100

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      cipher drivers*/
/** @{*/  /** <!-- [cipher]*/

/*! Define the post process depth */
#define TRNG_POST_PROCESS_DEPTH     0x10

/*! Define the osc sel */
#define TRNG_OSC_SEL                0x02

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      trng */
/** @{ */  /** <!--[trng]*/

s32 drv_trng_randnum(u32 *randnum, u32 timeout)
{
    U_RNG_STAT stat;
    U_RNG_CTRL ctrl;
    u32 times = 0;
    static u32 last = 0x1082;

    HI_LOG_FuncEnter();

    CRYPTO_ASSERT(HI_NULL != randnum);

    if (ctrl.u32 != last)
    {
        module_enable(CRYPTO_MODULE_ID_TRNG);

        ctrl.u32 = TRNG_READ(RNG_CTRL);
        ctrl.bits.filter_enable = 0x00;
        ctrl.bits.mix_en = 0x00;
        ctrl.bits.drop_enable = 0x00;
        ctrl.bits.post_process_enable = 0x01;
        ctrl.bits.post_process_depth = TRNG_POST_PROCESS_DEPTH;
        ctrl.bits.osc_sel = TRNG_OSC_SEL;
        TRNG_WRITE(RNG_CTRL, ctrl.u32);
    }

#if defined(HI_PLATFORM_TYPE_LINUX)
    if (0 == timeout) /* unblock */
    {
        /* trng number is valid ? */
        stat.u32 = TRNG_READ(RNG_STAT);
        if (0x00 == stat.bits.rng_data_count)
        {
            return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
        }
    }
    else /* block */
#endif
    {
        while(times++ < TRNG_TIMEOUT)
        {
            /* trng number is valid ? */
            stat.u32 = TRNG_READ(RNG_STAT);
            if (0x00 < stat.bits.rng_data_count)
            {
                break;
            }
        }

        /* time out */
        if (times >= TRNG_TIMEOUT)
        {
            return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
        }
    }

    /* read valid randnum */
    *randnum = TRNG_READ(RNG_FIFO_DATA);

    HI_LOG_INFO("randnum: 0x%x\n", *randnum);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void drv_trng_get_capacity(trng_capacity *capacity)
{
    crypto_memset(capacity, sizeof(trng_capacity), 0,  sizeof(trng_capacity));

    capacity->trng = CRYPTO_CAPACITY_SUPPORT;

    return;
}

/** @} */  /** <!-- ==== API declaration end ==== */

#endif //End of CHIP_TRNG_VER_V100
