/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : user_osal_lib.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "user_osal_lib.h"


/************************ Internal Structure Definition **********************/
/** \addtogroup      lib */
/** @{*/  /** <!-- [osal]*/


/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      osal lib */
/** @{*/  /** <!-- [osal]*/

void crypto_memset(void *s, int sn, int val, int n)
{
    if (sn >= n)
    {
        memset(s, val, n);
    }
    else
    {
        HI_LOG_ERROR("error, memset overflow\n");
    }
}

void crypto_memcpy(void* s, int sn, const void* c, int n)
{
    if (sn >= n)
    {
        memcpy(s, c, n);
    }
    else
    {
        HI_LOG_ERROR("error, memcpy overflow\n");
    }
}

void HEX2STR(char buf[2], HI_U8 val)
{
    HI_U8 high, low;

    high = (val >> 4) & 0x0F;
    low =  val & 0x0F;

    if(high <= 9)
    {
        buf[0] = high + '0';
    }
    else
    {
        buf[0] = (high - 0x0A) + 'A';
    }

    if(low <= 9)
    {
        buf[1] = low + '0';
    }
    else
    {
        buf[1] = (low - 0x0A) + 'A';
    }

}

void print_string(const char*name, u8 *string, u32 size)
{
    HI_U32 i;
    char buf[4];

    if (name != HI_NULL)
    {
        HI_PRINT("[%s-%p]:\n", name, string);
    }
    for (i=0; i<size; i++)
    {
        HEX2STR(buf, string[i]);
        HI_PRINT("%c%c ", buf[0], buf[1]);
        if(((i+1) % 16) == 0)
            HI_PRINT("\n");
    }
    if (( i % 16) != 0)
    {
        HI_PRINT("\n");
    }
}

/** @}*/  /** <!-- ==== API Code end ====*/
