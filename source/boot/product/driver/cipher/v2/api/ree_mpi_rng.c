/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : ree_mpi_rng.c
  Version       : Initial Draft
  Author        :
  Created       : 2017/2/23
  Last Modified :
  Description   :
  Function List :
******************************************************************************/
#include "cipher_osal.h"

HI_S32 HI_MPI_CIPHER_GetRandomNumber(HI_U8 *pu8RandomByte, HI_U32 u32Bytes, HI_U32 u32TimeOutUs)
{
    CIPHER_RNG_S stRNG;

    INLET_PARAM_CHECK_POINT_NULL(pu8RandomByte);

    stRNG.pu8RandomByte = pu8RandomByte;
    stRNG.u32Bytes      = u32Bytes;
    stRNG.u32TimeOutUs  = u32TimeOutUs;

    return cipher_ioctl(g_CipherDevFd, CMD_CIPHER_GETRANDOMNUMBER, &stRNG);
}

