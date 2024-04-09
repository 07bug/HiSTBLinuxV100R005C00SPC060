/******************************************************************************
Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_rng.c
Version       : Initial Draft
Author        : Hisilicon
Created       : 2012/07/10
Last Modified :
Description   : sample for rng
Function List :
History       :
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "hi_type.h"
#include "hi_common.h"
#include "hi_unf_cipher.h"
#include "hi_error_mpi.h"

#ifdef  CONFIG_SUPPORT_CA_RELEASE
#define HI_ERR_RNG(format, arg...)
#define HI_DEBUG_RNG(format...)   printf(format)
#else
#define HI_ERR_RNG(format, arg...)    printf( "%s,%d: " format , __FUNCTION__, __LINE__, ## arg)
#define HI_DEBUG_RNG(format...)   printf(format)
#endif

#define RAND_BYTE_CNT     127

static HI_S32 printBuffer(HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{
    HI_U32 i = 0;

    if ( NULL != string )
    {
        printf("%s\n", string);
    }

    for ( i = 0 ; i < u32Length; i++ )
    {
        if( (i % 16 == 0) && (i != 0)) printf("\n");
        printf("0x%02x ", pu8Input[i]);
    }
    printf("\n");

    return HI_SUCCESS;
}

int main(void)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_S32 index = 0;
    HI_U8  randByte[RAND_BYTE_CNT] = {0};
    HI_U32 randomNumber = 0;

    Ret = HI_SYS_Init();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_RNG("HI_SYS_Init ERROR!%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, Ret);
        return Ret;
    }

    Ret = HI_UNF_CIPHER_Init();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_RNG("HI_UNF_CIPHER_Init ERROR!\n");
        return Ret;
    }

    for (index = 0; index < 10; index++)
    {
        Ret = HI_UNF_CIPHER_GetRandomNumber(&randomNumber);
        if (HI_ERR_CIPHER_NO_AVAILABLE_RNG == Ret)
        {
            /* "There is No ramdom number available now. Try again! */
            index--;
            continue;
        }

        if (HI_SUCCESS != Ret)
        {
            HI_ERR_RNG("HI_UNF_CIPHER_GetRandomNumber failed!\n");
            return Ret;
        }

        HI_DEBUG_RNG("Random number: %08x\n", randomNumber);
    }

    Ret = HI_UNF_CIPHER_GetMultiRandomBytes(randByte, RAND_BYTE_CNT);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_RNG("HI_UNF_CIPHER_GetRandomByte failed!\n");
        return Ret;
    }
    printBuffer("randByte", randByte, RAND_BYTE_CNT);

    Ret = HI_UNF_CIPHER_DeInit();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_RNG("CIPHER DeInit ERROR! Return Value = %d.\n", Ret);
        return Ret;
    }

    Ret = HI_SYS_DeInit();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_RNG("System DeInit ERROR! Return Value = %d.\n", Ret);
        return Ret;
    }

    return Ret;
}

