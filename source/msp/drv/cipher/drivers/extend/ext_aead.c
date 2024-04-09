/******************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ext_aead.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_symc.h"
#include "mbedtls/ccm.h"
#include "mbedtls/gcm.h"

#ifdef SOFT_AES_CCM_GCM_SUPPORT

/**
 * \brief          aes ccm context structure
 */
typedef struct
{
    u32 key[SYMC_KEY_SIZE/4];      /*!<  SYMC even round keys, default */
    u32 iv[AES_IV_SIZE/4];         /*!<  symc IV */
    u32 tag[AEAD_TAG_SIZE/4];      /*!<  aead tag */
    u32 ivlen;               /*!<  symc IV length */
    u32 klen;                /*!<  symc key length */
    compat_addr aad;         /*!<  Associated Data */
    u32 alen;                /*!<  Associated Data length */
    u32 tlen;                /*!<  Tag length */
}
ext_aead_context;

void * ext_mbedtls_aead_create(u32 hard_chn)
{
    ext_aead_context *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    ctx = crypto_calloc(1, sizeof(ext_aead_context));
    if (HI_NULL == ctx)
    {
        HI_LOG_ERROR("malloc failed \n");
        HI_LOG_PrintFuncErr(crypto_calloc, 0);
        return HI_NULL;
    }

    HI_LOG_FuncExit();

    return ctx;
}

s32 ext_mbedtls_aead_destory(void *ctx)
{
    HI_LOG_FuncEnter();

    if (HI_NULL != ctx)
    {
        crypto_free(ctx);
        ctx = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 ext_mbedtls_aead_setiv(void *ctx, const u8 *iv, u32 ivlen, u32 usage)
{
    ext_aead_context *aead = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == aead);
    HI_LOG_CHECK_PARAM(AES_IV_SIZE < ivlen);

    if (HI_NULL != iv)
    {
        crypto_memcpy(aead->iv, AES_IV_SIZE, iv, ivlen);
        aead->ivlen = ivlen;
        HI_LOG_DEBUG("ivlen %d\n", ivlen);
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 ext_mbedtls_aead_setkey(void *ctx, const u8 *fkey, const u8 *skey, u32 *hisi_klen)
{
    u32 klen = 0;
    ext_aead_context *aead = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == aead);
    HI_LOG_CHECK_PARAM(HI_NULL == fkey);
    HI_LOG_CHECK_PARAM(HI_NULL == hisi_klen);

    switch(*hisi_klen)
    {
        case CRYP_CIPHER_KEY_AES_128BIT:
        {
            klen = AES_KEY_128BIT;
            break;
        }
        case CRYP_CIPHER_KEY_AES_192BIT:
        {
            klen = AES_KEY_192BIT;
            break;
        }
        case CRYP_CIPHER_KEY_AES_256BIT:
        {
            klen = AES_KEY_256BIT;
            break;
        }
        default:
        {
            HI_LOG_ERROR("Invalid aes key len: 0x%x\n", klen);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }
    HI_LOG_INFO("key len %d, type %d\n", klen, hisi_klen);

    crypto_memcpy(aead->key, SYMC_KEY_SIZE, fkey, klen);
    aead->klen = klen;
    *hisi_klen = klen;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 ext_mbedtls_aead_set_aad(void *ctx, compat_addr aad, u32 alen, u32 tlen)
{
    ext_aead_context *aead = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == aead);

    aead->aad = aad;
    aead->alen = alen;
    aead->tlen = tlen;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 ext_mbedtls_aead_get_tag(void *ctx, u32 tag[AEAD_TAG_SIZE_IN_WORD], u32 *taglen)
{
    ext_aead_context *aead = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == aead);
    HI_LOG_CHECK_PARAM(*taglen < aead->tlen);

    HI_LOG_DEBUG("tag buffer len %d, tag len %d\n", *taglen,  aead->tlen);

    *taglen = aead->tlen;

    crypto_memcpy(tag, AEAD_TAG_SIZE, aead->tag, aead->tlen);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 ext_mbedtls_aead_ccm_crypto(void *ctx,
                    u32 operation,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    symc_node_usage usage_list[],
                    u32 pkg_num, u32 last)
{
    ext_aead_context *aead = ctx;
    mbedtls_ccm_context ccm;
    crypto_mem mem_in, mem_out, aad;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == aead);
    HI_LOG_CHECK_PARAM(HI_NULL == length);
    HI_LOG_CHECK_PARAM(0x01 != pkg_num);

    ret = crypto_mem_open(&mem_in, input[0], length[0]);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of input failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    ret = crypto_mem_open(&mem_out, output[0], length[0]);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of output failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        goto error1;
    }

    ret = crypto_mem_open(&aad, aead->aad, aead->alen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of aad failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_FuncExit();
        goto error2;
    }

    mbedtls_ccm_init(&ccm);

    HI_LOG_DEBUG("aead 0x%p, klen len: %d\n", aead, aead->klen);

    ret = mbedtls_ccm_setkey(&ccm, MBEDTLS_CIPHER_ID_AES, (u8*)aead->key,
                aead->klen * BITS_IN_BYTE);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mbedtls_ccm_setkey, ret);
        goto error3;
    }

    //HI_PRINT_HEX("key", (u8*)aead->key, aead->klen);
    //HI_PRINT_HEX("iv", (u8*)aead->iv , aead->ivlen);
    //HI_PRINT_HEX("a", crypto_mem_virt(&aad), aead->alen);
    //HI_PRINT_HEX("in", crypto_mem_virt(&mem_in), length[0]);

    if (operation)
    {
        ret = mbedtls_ccm_auth_decrypt(&ccm, length[0],
                (u8*)aead->iv , aead->ivlen,
                crypto_mem_virt(&aad), aead->alen,
                crypto_mem_virt(&mem_in), crypto_mem_virt(&mem_out),
                (u8*)aead->tag, aead->tlen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(mbedtls_ccm_auth_decrypt, ret);
        }
    }
    else
    {
        ret = mbedtls_ccm_encrypt_and_tag(&ccm, length[0],
                (u8*)aead->iv , aead->ivlen,
                crypto_mem_virt(&aad), aead->alen,
                crypto_mem_virt(&mem_in), crypto_mem_virt(&mem_out),
                (u8*)aead->tag, aead->tlen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(mbedtls_ccm_encrypt_and_tag, ret);
        }
    }

    //HI_PRINT_HEX("out", crypto_mem_virt(&mem_out), length[0]);
    //HI_PRINT_HEX("tag", (u8*)aead->tag, aead->tlen);

    HI_LOG_FuncExit();

error3:
    mbedtls_ccm_free(&ccm);
    crypto_mem_close(&aad);
error2:
    crypto_mem_close(&mem_out);
error1:
    crypto_mem_close(&mem_in);

    return ret;
}

s32 ext_mbedtls_aead_gcm_crypto(void *ctx,
                    u32 operation,
                    compat_addr input[],
                    compat_addr output[],
                    u32 length[],
                    symc_node_usage usage_list[],
                    u32 pkg_num, u32 last)
{
    ext_aead_context *aead = ctx;
    mbedtls_gcm_context gcm;
    crypto_mem mem_in, mem_out, aad;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == aead);
    HI_LOG_CHECK_PARAM(HI_NULL == length);
    HI_LOG_CHECK_PARAM(0x01 != pkg_num);

    ret = crypto_mem_open(&mem_in, input[0], length[0]);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of input failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_PrintFuncErr(crypto_mem_open, ret);
        return ret;
    }

    ret = crypto_mem_open(&mem_out, output[0], length[0]);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of output failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_PrintFuncErr(crypto_mem_open, ret);
        goto error1;
    }

    ret = crypto_mem_open(&aad, aead->aad, aead->alen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("open mem of aad failed\n");
        ret = HI_ERR_CIPHER_FAILED_MEM;
        HI_LOG_PrintFuncErr(crypto_mem_open, ret);
        goto error2;
    }

    mbedtls_gcm_init(&gcm);

    ret = mbedtls_gcm_setkey(&gcm, MBEDTLS_CIPHER_ID_AES, (u8*)aead->key,
                aead->klen * BITS_IN_BYTE);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mbedtls_gcm_setkey, ret);
        goto error3;
    }

    ret = mbedtls_gcm_starts(&gcm, operation ? MBEDTLS_DECRYPT : MBEDTLS_ENCRYPT,
        (u8*)aead->iv , aead->ivlen,
        crypto_mem_virt(&aad), aead->alen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mbedtls_gcm_starts, ret);
        goto error3;
    }

    ret = mbedtls_gcm_update(&gcm, length[0], crypto_mem_virt(&mem_in),
        crypto_mem_virt(&mem_out));
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mbedtls_gcm_update, ret);
        goto error3;
    }

    ret = mbedtls_gcm_finish(&gcm,(u8*)aead->tag, aead->tlen);

error3:
    mbedtls_gcm_free(&gcm);
    crypto_mem_close(&aad);
error2:
    crypto_mem_close(&mem_out);
error1:
    crypto_mem_close(&mem_in);

    return ret;
}

#endif // End of SOFT_AES_CCM_GCM_SUPPORT
