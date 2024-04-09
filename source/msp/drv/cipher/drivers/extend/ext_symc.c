/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ext_symc.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_symc.h"
#include "mbedtls/cipher.h"

#if defined(SOFT_AES_SUPPORT) || defined(SOFT_TDES_SUPPORT)

/**
 * \brief          aes ccm context structure
 */
typedef struct
{
    u32 key[SYMC_KEY_SIZE/4];      /*!<  SYMC even round keys, default */
    u32 klen;                /*!<  symc key length */
    mbedtls_cipher_id_t cipher_id;
    mbedtls_cipher_mode_t mode;
    mbedtls_cipher_context_t cipher;
}
ext_symc_context;

void * ext_mbedtls_symc_create(u32 hard_chn)
{
    ext_symc_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    ctx = crypto_malloc(sizeof(ext_symc_context));
    if (HI_NULL == ctx)
    {
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        HI_LOG_ERROR("malloc failed \n");
    }
    mbedtls_cipher_init(&ctx->cipher);

    HI_LOG_FuncExit();

    return ctx;
}

s32 ext_mbedtls_symc_destory(void *ctx)
{
    ext_symc_context *symc = ctx;

    HI_DBG_FuncEnter();

    if (HI_NULL != ctx)
    {
        mbedtls_cipher_free(symc);
        crypto_free(ctx);
        ctx = HI_NULL;
    }

    HI_DBG_FuncExit();
    return HI_SUCCESS;
}

s32 ext_mbedtls_symc_setmode(void *ctx, symc_alg alg, symc_mode mode, symc_width width)
{
    ext_symc_context *symc = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == symc);
    HI_LOG_CHECK_PARAM(SYMC_DAT_WIDTH_128 != width);

    switch(alg)
    {
    case SYMC_ALG_AES:
        symc->cipher_id = MBEDTLS_CIPHER_ID_AES;
        break;
    case SYMC_ALG_TDES:
        symc->cipher_id = MBEDTLS_CIPHER_ID_3DES;
        break;
    case SYMC_ALG_DES:
        symc->cipher_id = MBEDTLS_CIPHER_ID_DES;
        break;
    default:
        HI_LOG_ERROR("unsupport alg %d\n", alg);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    switch(mode)
    {
    case SYMC_MODE_ECB:
        symc->mode = MBEDTLS_MODE_ECB;
        break;
    case SYMC_MODE_CBC:
        symc->mode = MBEDTLS_MODE_CBC;
        break;
    case SYMC_MODE_CFB:
        symc->mode = MBEDTLS_MODE_CFB;
        break;
    case SYMC_MODE_OFB:
        symc->mode = MBEDTLS_MODE_OFB;
        break;
    case SYMC_MODE_CTR:
        symc->mode = MBEDTLS_MODE_CTR;
        break;
    default:
        HI_LOG_ERROR("unsupport mode %d\n", mode);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    HI_LOG_DEBUG("cipher_id %d, mode %d\n", symc->cipher_id, symc->mode);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 ext_mbedtls_symc_setiv(void *ctx, const u8 *iv, u32 ivlen, u32 usage)
{
    s32 ret = HI_FAILURE;
    ext_symc_context *symc = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == symc);
    HI_LOG_CHECK_PARAM(HI_NULL == iv);
    HI_LOG_CHECK_PARAM(AES_IV_SIZE < ivlen);

    ret = mbedtls_cipher_set_iv(&symc->cipher, iv, ivlen);

    HI_LOG_FuncExit();

    return ret;
}

void ext_mbedtls_symc_getiv(void *ctx, u8 *iv, u32 *ivlen)
{
    s32 ret = HI_FAILURE;
    ext_symc_context *symc = ctx;

    HI_LOG_FuncEnter();

    if ((HI_NULL == symc) || (HI_NULL == iv) || (HI_NULL == ivlen))
    {
        return;
    }

    crypto_memcpy(iv, AES_IV_SIZE, symc->cipher.iv, symc->cipher.iv_size);
    *ivlen = symc->cipher.iv_size;

    HI_LOG_FuncExit();

    return;
}

s32 ext_mbedtls_symc_setkey(void *ctx, const u8 *fkey, const u8 *skey, u32 *hisi_klen)
{
    s32 ret = HI_FAILURE;
    u32 klen = 0;
    ext_symc_context *symc = ctx;
    const mbedtls_cipher_info_t *info= HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == symc);
    HI_LOG_CHECK_PARAM(HI_NULL == fkey);
    HI_LOG_CHECK_PARAM(HI_NULL == hisi_klen);

    if (MBEDTLS_CIPHER_ID_AES == symc->cipher_id)
    {
        switch(*hisi_klen)
        {
            case CRYP_CIPHER_KEY_AES_128BIT:
                klen = AES_KEY_128BIT;
                break;
            case CRYP_CIPHER_KEY_AES_192BIT:
                klen = AES_KEY_192BIT;
                break;
            case CRYP_CIPHER_KEY_AES_256BIT:
                klen = AES_KEY_256BIT;
                break;
            default:
                HI_LOG_ERROR("Invalid aes key len: 0x%x\n", klen);
                HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
                return HI_ERR_CIPHER_INVALID_PARA;
        }
        crypto_memcpy(symc->key, SYMC_KEY_SIZE, fkey, klen);
    }
    else if (MBEDTLS_CIPHER_ID_3DES == symc->cipher_id)
    {
        klen = TDES_KEY_192BIT;
        crypto_memcpy(symc->key, SYMC_KEY_SIZE, fkey, klen);
        if (CRYP_CIPHER_KEY_DES_2KEY == *hisi_klen)
        {
            /* k3 = k1*/
            symc->key[4] = symc->key[0];
            symc->key[5] = symc->key[1];
        }
    }
    else if (MBEDTLS_CIPHER_ID_DES == symc->cipher_id)
    {
        klen = DES_KEY_SIZE;
        crypto_memcpy(symc->key, SYMC_KEY_SIZE, fkey, klen);
    }
    HI_LOG_INFO("key len %d, type %d\n", klen, *hisi_klen);

    symc->klen = klen;

    HI_LOG_DEBUG("cipher_id %d, klen %d, mode %d\n", symc->cipher_id, klen, symc->mode);
    info = mbedtls_cipher_info_from_values(symc->cipher_id, klen * 8, symc->mode);
    HI_LOG_CHECK_PARAM(HI_NULL == info);

    ret = mbedtls_cipher_setup(&symc->cipher, info);

    *hisi_klen = klen;

    HI_LOG_FuncExit();

    return ret;
}

s32 ext_mbedtls_symc_crypto(void *ctx,
                    u32 operation,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    symc_node_usage usage_list[],
                    u32 pkg_num, u32 last)
{
    ext_symc_context *symc = ctx;
    crypto_mem mem_in, mem_out;
    u32 offset = 0;
    size_t olen = 0;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == symc);
    HI_LOG_CHECK_PARAM(HI_NULL == input);
    HI_LOG_CHECK_PARAM(HI_NULL == output);
    HI_LOG_CHECK_PARAM(HI_NULL == length);
    HI_LOG_CHECK_PARAM(0x01 != pkg_num);

    ret = mbedtls_cipher_setkey(&symc->cipher, (HI_U8*)symc->key, symc->klen * 8,
        operation ? MBEDTLS_DECRYPT : MBEDTLS_ENCRYPT);
    if (HI_SUCCESS != ret)
        return ret;

    ret = crypto_mem_open(&mem_in, input[0], length[0]);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of input failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        goto error0;
    }

    ret = crypto_mem_open(&mem_out, output[0], length[0]);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of output failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        goto error1;
    }

    HI_LOG_DEBUG("symc 0x%p, klen len: %d\n", symc, symc->klen);

    if (MBEDTLS_MODE_ECB == symc->mode)
    {
        offset = 0;
        while(offset < length[0])
        {
            ret = mbedtls_cipher_update(&symc->cipher, crypto_mem_virt(&mem_in) + offset,
                    mbedtls_cipher_get_block_size(&symc->cipher),
                    crypto_mem_virt(&mem_out) + offset, &olen);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_ERROR("mbedtls_cipher_update failed\n");
                break;
            }
            offset += mbedtls_cipher_get_block_size(&symc->cipher);
        }
    }
    else
    {
        ret = mbedtls_cipher_update(&symc->cipher, crypto_mem_virt(&mem_in),
            length[0], crypto_mem_virt(&mem_out), &olen);
    }

    HI_LOG_FuncExit();

    crypto_mem_close(&mem_out);
error1:
    crypto_mem_close(&mem_in);
error0:

    return ret;
}
#endif
