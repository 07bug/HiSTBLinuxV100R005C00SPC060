/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_rng.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "cipher_adapt.h"
#include "mailbox.h"

#define  REG_RNG_BASE_ADDR                   g_u32RngRegBase
#define  HISEC_COM_TRNG_CTRL                 (REG_RNG_BASE_ADDR + 0x200)
#define  HISEC_COM_TRNG_FIFO_DATA            (REG_RNG_BASE_ADDR + 0x204)
#define  HISEC_COM_TRNG_DATA_ST              (REG_RNG_BASE_ADDR + 0x208)

static HI_VOID *g_u32RngRegBase;
static HI_BOOL s_bSecure = HI_TRUE;

HI_S32 DRV_RNG_Init(HI_VOID)
{
    g_u32RngRegBase = cipher_ioremap_nocache(CIPHER_RNG_REG_BASE_ADDR_PHY, 0x1000);
    if (g_u32RngRegBase == HI_NULL)
    {
        HI_ERR_CIPHER("ioremap_nocache sha2 Reg failed\n");
        return HI_FAILURE;
    }
    HI_DRV_SYS_GetCPUSecureMode(&s_bSecure);

    return HI_SUCCESS;
}

HI_VOID DRV_RNG_DeInit(HI_VOID)
{
    cipher_iounmap(g_u32RngRegBase);
}

HI_S32 DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG)
{
    HI_U32 u32RngStat = 0;
    HI_U32 u32TimeOut = 0;
    HI_U32 u32Randnum = 0;
    HI_U32 u32Cnt = 0;
    HI_U32 i = 0;

    if(NULL == pstRNG)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    pstRNG->u32TimeOutUs = 1000;

    while((i < pstRNG->u32Bytes) && (u32TimeOut < pstRNG->u32TimeOutUs))
    {
        /* low 3bit(RNG_data_count[2:0]), indicate how many RNGs in the fifo is available now */
        HAL_CIPHER_ReadReg(HISEC_COM_TRNG_DATA_ST, &u32RngStat);
        if(((u32RngStat >> 8) & 0x3F) == 0)
        {
            u32TimeOut++;
            continue;
        }
        HAL_CIPHER_ReadReg(HISEC_COM_TRNG_FIFO_DATA, &u32Randnum);
        u32Cnt = MIN(pstRNG->u32Bytes - i, sizeof(HI_U32));
        memcpy(pstRNG->pu8RandomByte + i, &u32Randnum, u32Cnt);
        i += u32Cnt;
        u32TimeOut = 0;
    }

    if (u32TimeOut >= pstRNG->u32TimeOutUs)
    {
        return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_CIPHER_GetRngFromHSL(unsigned int addr, unsigned int size)
{
    unsigned int command = MBX_TYPE_TRNG_GET;
    unsigned int args[2] = {0};

    args[0] = addr;
    args[1] = size;
    mailbox_set(&command, args, 2, 0);

    mailbox_get(&command, args, 5000);
    if (command == MBX_TYPE_CMD_PROCESS_OK)
    {
        return HI_SUCCESS;
    }
    else
    {
        return HI_ERR_CIPHER_NO_AVAILABLE_RNG;
    }
}

HI_U32 DRV_CIPHER_Rand(HI_VOID)
{
    CIPHER_RNG_S stRNG;
    HI_U32 u32Randunm = 0;

    stRNG.pu8RandomByte = (HI_U8*)&u32Randunm;

    if (s_bSecure)
    {
        stRNG.u32TimeOutUs = - 1;
        DRV_CIPHER_GetRandomNumber(&stRNG);
    }
    else
    {
        /* non-secure CPU can't read trng, but read trng by HSL use mailbox */
        DRV_CIPHER_GetRngFromHSL((HI_U32)&u32Randunm, sizeof(HI_U32));
    }

    return u32Randunm;
}

HI_S32 HI_DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG)
{
    HI_S32 ret = HI_SUCCESS;

    if(NULL == pstRNG)
    {
        HI_ERR_CIPHER("Invalid params!\n");
        return HI_FAILURE;
    }

    if (s_bSecure)
    {
        ret = DRV_CIPHER_GetRandomNumber(pstRNG);
    }
    else
    {
        /* non-secure CPU can't read trng, but read trng by HSL use mailbox */
        DRV_CIPHER_GetRngFromHSL((HI_U32)pstRNG->pu8RandomByte, pstRNG->u32Bytes);
    }

    return ret;
}

