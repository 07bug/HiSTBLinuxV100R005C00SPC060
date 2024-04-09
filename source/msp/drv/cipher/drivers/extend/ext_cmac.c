/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ext_cmac.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_symc.h"

/*********************************************************
 * The function below is added for AES CBC-MAC
 *
 *********************************************************/

/* the max extend data length for encryption / decryption is  8k one time */
#define MAX_EXT_DATA_LEN        (0x2000)

#define BYTE_MSB            0x80

/* For CMAC Calculation */

static u8 const_Rb[AES_BLOCK_SIZE] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
};

/* only output last block */
static s32 ext_aes_cmac_block(u32 id, u8 *input, u32 inlen, u8 *output)
{
    s32 ret = HI_FAILURE;
    u32 enc_len = 0;
    u32 left_len = 0;
    u32 i = 0;
    u32 blocknum = 0;
    crypto_mem mem;
    compat_addr phy;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == input);
    HI_LOG_CHECK_PARAM(HI_NULL == output);
    HI_LOG_CHECK_PARAM(0x00 != (inlen % AES_BLOCK_SIZE));

    /* malloc dma buffer */
    ret = crypto_mem_create(&mem, SEC_MMZ, "AES_EXT_BUF", MAX_EXT_DATA_LEN);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(crypto_mem_create, ret);
        return ret;
    }
    crypto_mem_phys(&mem, &phy);

    /* split data to decryption or enctryption */
    left_len = inlen;
    blocknum = (inlen + MAX_EXT_DATA_LEN - 1) / MAX_EXT_DATA_LEN;
    for (i = 0; i < blocknum; i++)
    {
        /* new data length */
        enc_len = left_len >= MAX_EXT_DATA_LEN ? MAX_EXT_DATA_LEN : left_len;
        left_len -= enc_len;

        /* attach input buffer with dma buffer */
        crypto_mem_attach(&mem, input + i * MAX_EXT_DATA_LEN);

        /* copy data to dma buffer */
        crypto_mem_flush(&mem, HI_FALSE, 0, enc_len);
        //HI_PRINT_HEX("AES-IN", crypto_mem_virt(&mem), enc_len);

        CHECK_EXIT(kapi_symc_crypto(id, phy, phy, enc_len, HI_FALSE, HI_FALSE, HI_FALSE));

        /* only output last block */
        crypto_memcpy(output, AES_BLOCK_SIZE,
            crypto_mem_virt(&mem) + enc_len - AES_BLOCK_SIZE,  AES_BLOCK_SIZE);
        //HI_PRINT_HEX("AES-OUT", output, AES_BLOCK_SIZE);
    }

exit__:
    crypto_mem_destory(&mem);
    HI_LOG_FuncExit();

    return ret;
}

/* Basic Functions */
static void xor_128(u8 *a, u8 *b, u8 *out)
{
    u32 i;

    for (i = 0; i < AES_BLOCK_SIZE; i++)
    {
        out[i] = a[i] ^ b[i];
    }
}

/* AES-CMAC Generation Function */
static void leftshift_onebit(u8 *input, u8 *output)
{
    s32 i;
    u8 overflow = 0;

    for (i = AES_BLOCK_SIZE - 1; i >= 0; i--)
    {
        output[i] = input[i] << 1;
        output[i] |= overflow;
        overflow = (input[i] & BYTE_MSB) ? 1 : 0;
    }
    return;
}

static s32 generate_subkey(u32 id, u8 *K1, u8 *K2)
{
    u8 L[AES_BLOCK_SIZE] = {0};
    u8 Z[AES_BLOCK_SIZE] = {0};
    u8 tmp[AES_BLOCK_SIZE] = {0};
    u32 u32DataLen = AES_BLOCK_SIZE;
    s32 ret = HI_FAILURE;

    ret = ext_aes_cmac_block(id, Z, u32DataLen, L);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(ext_aes_cmac_block, ret);
        return ret;
    }

    if ((L[0] & BYTE_MSB) == 0) /* If MSB(L) = 0, then K1 = L << 1 */
    {
        leftshift_onebit(L, K1);
    }
    else  /* Else K1 = (L << 1) (+) Rb */
    {
        leftshift_onebit(L, tmp);
        xor_128(tmp, const_Rb, K1);
    }

    if ((K1[0] & BYTE_MSB) == 0)
    {
        leftshift_onebit(K1,K2);
    }
    else
    {
        leftshift_onebit(K1, tmp);
        xor_128(tmp, const_Rb, K2);
    }

    return HI_SUCCESS;
}

static void padding (u8 *lastb, u8 *pad, u32 length)
{
    u32 j;

    /* original last block */
    for (j = 0; j < AES_BLOCK_SIZE; j++)
    {
        if (j < length)
        {
            pad[j] = lastb[j];
        }
        else if (j == length)
        {
            pad[j] = BYTE_MSB;
        }
        else
        {
            pad[j] = 0x00;
        }
    }
}

/**********************************************************
*                        AES_CBCMAC                       *

http://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38b.pdf

Subkey Generation:
Steps:
1. Let L = CIPHK(0b).
2. If MSB1(L) = 0, then K1 = L << 1;
   Else K1 = (L << 1) ¨’ Rb; see Sec. 5.3 for the definition of Rb.
3. If MSB1(K1) = 0, then K2 = K1 << 1; Else K2 = (K1 << 1) ¨’ Rb.
4. Return K1, K2.

MAC Generation:
Steps:
1. Apply the subkey generation process in Sec. 6.1 to K to produce K1 and K2.
2. If Mlen = 0, let n = 1; else, let n = [Mlen/b]
3. Let M1, M2, ... , Mn-1, Mn* denote the unique sequence of bit strings such that
   M = M1 || M2 || ... || Mn-1 || Mn*, where M1, M2,..., Mn-1 are complete blocks.2
4. If Mn* is a complete block, let Mn = K1 ^ Mn*;
   else, let Mn = K2 ^ (Mn*||10j), where j = nb-Mlen-1.
5. Let C0 = 0b .
6. For i = 1 to n, let Ci = CIPHK(Ci-1 . Mi).
7. Let T = MSBTlen(Cn).
8. Return T.
***********************************************************/
s32 ext_aes_cmac_update(u32 id, u8 *input, u32 inlen)
{
    s32 ret = HI_FAILURE;
    u8 iv[AES_BLOCK_SIZE] = {0};

    HI_LOG_FuncEnter();

    HI_LOG_DEBUG("id %d, inlen %d\n", id, inlen);

    HI_LOG_CHECK_PARAM(HI_NULL == input);
    HI_LOG_CHECK_PARAM(0 == inlen);
    HI_LOG_CHECK_PARAM(0 != (inlen % AES_BLOCK_SIZE));

    /* X := AES-128(KEY, Y); */
    ret = ext_aes_cmac_block(id, input, inlen, iv);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(ext_aes_cmac_block, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 ext_aes_cmac_finish(u32 id, u8 *input, u32 inlen, u8 *mac)
{
    u8 M_last[AES_BLOCK_SIZE] = {0};
    u8 padded[AES_BLOCK_SIZE] = {0};
    u8 K1[AES_BLOCK_SIZE] = {0};
    u8 K2[AES_BLOCK_SIZE] = {0};
    u8 IV[AES_BLOCK_SIZE] = {0};
    u32 tail = 0, ivlen = 0;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_DEBUG("id %d, inlen %d\n", id, inlen);

    HI_LOG_CHECK_PARAM(HI_NULL == mac);
    HI_LOG_CHECK_PARAM(HI_NULL == input);

    /* tail length */
    tail = inlen % AES_BLOCK_SIZE;
    if ((0 < inlen) && (0 == tail))
    {
        tail = AES_BLOCK_SIZE;
    }
    inlen -= tail;

    /* Copy tail data then padding with zero */
    crypto_memcpy(M_last, AES_BLOCK_SIZE, input + inlen, tail);
    //HI_PRINT_HEX("M_last", M_last, AES_BLOCK_SIZE);

    /* compute part of complete block */
    if (0 < inlen)
    {
        ret = ext_aes_cmac_block(id, input, inlen, IV);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(ext_aes_cmac_block, ret);
            return ret;
        }
    }

    /* save last IV */
    ret = kapi_symc_getiv(id, IV, &ivlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_getiv, ret);
        return ret;
    }
    //HI_PRINT_HEX("IV", IV, ivlen);

    /* reset IV to zero */
    crypto_memset(padded, sizeof(padded), 0, sizeof(padded));
    ret = kapi_symc_setiv(id, padded, AES_BLOCK_SIZE);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_setiv, ret);
        return ret;
    }

    /* generate K1 and K2 */
    ret = generate_subkey(id, K1, K2);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(generate_subkey, ret);
        return ret;
    }
    //HI_PRINT_HEX("K1", K1, AES_BLOCK_SIZE);
    //HI_PRINT_HEX("K2", K2, AES_BLOCK_SIZE);

    /* last block is complete block ? */
    if (AES_BLOCK_SIZE == tail)
    {
        xor_128(M_last, K1, M_last);
//      HI_PRINT_HEX("XOR", M_last, AES_BLOCK_SIZE);
    }
    else
    {
        padding(M_last, M_last, tail);
        xor_128(M_last, K2, M_last);
//      HI_PRINT_HEX("padding", M_last, AES_BLOCK_SIZE);
//      HI_PRINT_HEX("XOR", M_last, AES_BLOCK_SIZE);
    }

    /* recovery the last IV */
    ret = kapi_symc_setiv(id, IV, AES_BLOCK_SIZE);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_setiv, ret);
        return ret;
    }

    /* continue to compute last block */
    ret = ext_aes_cmac_block(id, M_last, AES_BLOCK_SIZE, mac);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_setiv, ret);
        return ret;
    }
    //HI_PRINT_HEX("MAC", mac, AES_BLOCK_SIZE);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
