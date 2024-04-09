/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : kapi_dispatch.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#include "drv_osal_lib.h"
#include "cryp_symc.h"
#include "ext_alg.h"
#ifdef HI_PLATFORM_TYPE_TEE
#include "tee_drv_cenc.h"
#else
#include "drv_cenc.h"
#endif

/*************************** Internal Structure Definition *******************/

/* ! \max pakage numher of symc mutli encrypt */
#define SYMC_MULTI_MAX_PKG      (0x1000)

#define RSA_PUBLIC_BUFFER_NUM   (0x03)
#define RSA_PRIVATE_BUFFER_NUM  (0x07)
#define ECC_PARAM_CNT           (0x06)

#define SM2_ENCRYPT_PAD_LEN     (SM2_LEN_IN_BYTE * 3)
#define MAX_MALLOC_BUF_SIZE     (0x10000)
#define MAX_CENC_SUB_SAMPLE     (100)

typedef s32 (*hi_drv_func)(void *param);

typedef struct
{
    const char *name;
    hi_drv_func func;
    u32 cmd;
}crypto_dispatch_func;

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      link*/
/** @{*/  /** <!-- [link]*/

static s32 dispatch_symc_create_handle(void *argp)
{
    s32 ret = HI_FAILURE;
    symc_create_t *symc_create = argp;

    HI_LOG_FuncEnter();

    /* allocate a aes channel */
    ret = kapi_symc_create(&symc_create->id, symc_create->type);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_create, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_symc_destroy_handle(void *argp)
{
    s32 ret = HI_FAILURE;
    symc_destroy_t *destroy = argp;

    HI_LOG_FuncEnter();

    ret = kapi_symc_destroy(destroy->id);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_destroy, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_symc_config(void *argp)
{
    s32 ret = HI_FAILURE;
    symc_config_t *config = argp;

    HI_LOG_FuncEnter();

    ret = kapi_symc_config(config->id,
                           config->hard_key,
                           config->alg,
                           config->mode,
                           config->width,
                           config->klen,
                           config->sm1_round_num,
                           (HI_U8*)config->fkey,
                           (u8*)config->skey,
                           (u8*)config->iv,
                           config->ivlen,
                           config->iv_usage,
                           config->aad,
                           config->alen,
                           config->tlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_config, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_symc_encrypt(void *argp)
{
    s32 ret = HI_FAILURE;
    symc_encrypt_t *encrypt = argp;

    HI_LOG_FuncEnter();

    ret = kapi_symc_crypto(encrypt->id,
                           encrypt->input,
                           encrypt->output,
                           encrypt->length,
                           encrypt->operation,
                           HI_FALSE,
                           encrypt->last);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_crypto, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_symc_encrypt_multi(void *argp)
{
    s32 ret = HI_FAILURE;
    symc_encrypt_multi_t *encrypt_mutli = argp;

    HI_LOG_FuncEnter();

    HI_LOG_DEBUG("operation %d\n", encrypt_mutli->operation);
    ret = kapi_symc_crypto_multi(encrypt_mutli->id,
                                 ADDR_VIA(encrypt_mutli->pkg),
                                 encrypt_mutli->pkg_num,
                                 encrypt_mutli->operation,
                                 HI_TRUE);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_crypto_multi, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_symc_get_tag(void *argp)
{
    s32 ret = HI_FAILURE;
    aead_tag_t *aead_tag = argp;

    HI_LOG_FuncEnter();

    ret = kapi_aead_get_tag(aead_tag->id,
                            aead_tag->tag,
                            &aead_tag->taglen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_aead_get_tag, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_symc_get_config(void *argp)
{
    s32 ret = HI_FAILURE;
    symc_get_config_t *get_config = argp;

    HI_LOG_FuncEnter();

    ret = kapi_symc_get_config(get_config->id, &get_config->ctrl);

    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_get_config, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_symc_camc(void *argp)
{
    s32 ret = HI_FAILURE;
    symc_cmac_t *cmac = argp;
    u8 *msg = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(MAX_MALLOC_BUF_SIZE < cmac->inlen);
    HI_LOG_CHECK_PARAM(MAX_MALLOC_BUF_SIZE < (cmac->inlen + AES_BLOCK_SIZE));

    msg = crypto_calloc(1, cmac->inlen + AES_BLOCK_SIZE);
    if (HI_NULL == msg)
    {
        HI_LOG_ERROR("error, malloc for cmac failed\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    CHECK_EXIT(crypto_copy_from_user(msg, ADDR_VIA(cmac->in), cmac->inlen));

    if (HI_TRUE == cmac->last)
    {
        CHECK_EXIT(ext_aes_cmac_finish(cmac->id, msg, cmac->inlen, cmac->mac));
    }
    else
    {
        CHECK_EXIT(ext_aes_cmac_update(cmac->id, msg, cmac->inlen));
    }

exit__:
    if (HI_NULL != msg)
    {
        crypto_free(msg);
        msg = HI_NULL;
    }

    if(HI_SUCCESS != ret)
    {
       HI_LOG_PrintErrCode(ret);
       return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_hash_start(void *argp)
{
    s32 ret = HI_FAILURE;
    hash_start_t *start = argp;
    u8 *key = HI_NULL;

    HI_LOG_FuncEnter();

    if (CRYP_CIPHER_HASH_TYPE_HMAC_SHA1 == start->type
        || CRYP_CIPHER_HASH_TYPE_HMAC_SHA224 == start->type
        || CRYP_CIPHER_HASH_TYPE_HMAC_SHA256 == start->type
#ifdef HI_PRODUCT_SHA512_SUPPORT
        || CRYP_CIPHER_HASH_TYPE_HMAC_SHA384 == start->type
        || CRYP_CIPHER_HASH_TYPE_HMAC_SHA512 == start->type
#endif
        )
    {

        HI_LOG_CHECK_PARAM(MAX_MALLOC_BUF_SIZE < start->keylen);
        HI_LOG_CHECK_PARAM(HI_NULL == ADDR_VIA(start->key));

        key = (u8*)crypto_calloc(1, start->keylen);
        if (HI_NULL == key)
        {
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
            HI_LOG_PrintFuncErr(crypto_calloc, ret);
            return HI_ERR_CIPHER_FAILED_MEM;
        }

        CHECK_EXIT(crypto_copy_from_user(key, ADDR_VIA(start->key), start->keylen));
    }

    CHECK_EXIT(kapi_hash_start(&start->id, start->type, key, start->keylen));

    if (HI_NULL != key)
    {
        crypto_free(key);
        key = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    if (HI_NULL != key)
    {
        crypto_free(key);
        key = HI_NULL;
    }

    return ret;
}

static s32 dispatch_hash_update(void *argp)
{
    s32 ret = HI_FAILURE;
    hash_update_t *update = argp;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ADDR_VIA(update->input));

    update->src = HASH_CHUNCK_SRC_USER;
    ret = kapi_hash_update(update->id,
                           ADDR_VIA(update->input),
                           update->length,
                           update->src);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_hash_update, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_hash_finish(void *argp)
{
    s32 ret = HI_FAILURE;
    hash_finish_t *finish = argp;

    HI_LOG_FuncEnter();

    ret = kapi_hash_finish(finish->id, (u8*)finish->hash, &finish->hashlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_hash_finish, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 rsa_alloc_buffer(cryp_rsa_key *key, rsa_info_t *rsa_info,
                            u8 **in, u8 **out)
{
    u32 size = 0, klen = 0;
    s32 ret = HI_FAILURE;
    u8 *buf = HI_NULL;

    HI_LOG_FuncEnter();

    if (HI_FALSE == rsa_info->public)
    {
        HI_LOG_CHECK_PARAM((HI_NULL == ADDR_VIA(rsa_info->d))
            && ((HI_NULL == ADDR_VIA(rsa_info->p))
            || (HI_NULL == ADDR_VIA(rsa_info->q))
            || (HI_NULL == ADDR_VIA(rsa_info->dP))
            || (HI_NULL == ADDR_VIA(rsa_info->dQ))
            || (HI_NULL == ADDR_VIA(rsa_info->qP))));
    }

    HI_LOG_CHECK_PARAM(rsa_info->inlen > rsa_info->klen);
    HI_LOG_CHECK_PARAM(rsa_info->outlen > rsa_info->klen);
    HI_LOG_CHECK_PARAM(RSA_MIN_KEY_LEN > rsa_info->klen);
    HI_LOG_CHECK_PARAM(RSA_MAX_KEY_LEN < rsa_info->klen);

    crypto_memset(key, sizeof(cryp_rsa_key), 0, sizeof(cryp_rsa_key));

    key->klen = klen = rsa_info->klen;
    key->public = rsa_info->public;

    if (rsa_info->public)
    {
        /* buffer size of key, input and output */
        size = rsa_info->klen * RSA_PUBLIC_BUFFER_NUM;

        buf = crypto_calloc(1, size);
        if (HI_NULL == buf)
        {
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
            HI_LOG_PrintFuncErr(crypto_calloc, ret);
            return HI_ERR_CIPHER_FAILED_MEM;
        }

        key->N = buf; buf += klen;
        *in = buf;    buf += klen;
        *out = buf;   buf += klen;

        CHECK_EXIT(crypto_copy_from_user(key->N, ADDR_VIA(rsa_info->N), klen));
        CHECK_EXIT(crypto_copy_from_user(*in, ADDR_VIA(rsa_info->in), klen));
        key->e = rsa_info->e;
    }
    else
    {
        /* n + d or n + p + q + dP + dQ + qp
         * the length of n/d is klen,
         * the length of p/q/dP/dQ/qp is klen/2,
         * the length of input is klen
         * the length of output is klen
         */
        size = klen * RSA_PRIVATE_BUFFER_NUM;

        buf = crypto_calloc(1, size);
        HI_LOG_CHECK_PARAM(HI_NULL == buf);

        key->N  = buf;       buf += klen;
        key->d  = buf;       buf += klen;
        key->p  = buf;       buf += klen / 2;
        key->q  = buf;       buf += klen / 2;
        key->dP = buf;       buf += klen / 2;
        key->dQ = buf;       buf += klen / 2;
        key->qP = buf;       buf += klen / 2;
        key->e  = rsa_info->e;

        if (HI_NULL != ADDR_VIA(rsa_info->N))
        {
            CHECK_EXIT(crypto_copy_from_user(key->N, ADDR_VIA(rsa_info->N), klen));
        }

        if (HI_NULL != ADDR_VIA(rsa_info->d))
        {
            CHECK_EXIT(crypto_copy_from_user(key->d, ADDR_VIA(rsa_info->d), klen));
        }
        else
        {
            CHECK_EXIT(crypto_copy_from_user(key->p, ADDR_VIA(rsa_info->p), klen/2));
            CHECK_EXIT(crypto_copy_from_user(key->q, ADDR_VIA(rsa_info->q), klen/2));
            CHECK_EXIT(crypto_copy_from_user(key->dP, ADDR_VIA(rsa_info->dP), klen/2));
            CHECK_EXIT(crypto_copy_from_user(key->dQ, ADDR_VIA(rsa_info->dQ), klen/2));
            CHECK_EXIT(crypto_copy_from_user(key->qP, ADDR_VIA(rsa_info->qP), klen/2));
            key->d = HI_NULL;
        }

        *in  = buf;       buf += klen;
        *out = buf;       buf += klen;

        if (HI_NULL != ADDR_VIA(rsa_info->in))
        {
            CHECK_EXIT(crypto_copy_from_user(*in, ADDR_VIA(rsa_info->in), rsa_info->inlen));
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    if (HI_NULL != key->N)
    {
        crypto_free(key->N);
        key->N = HI_NULL;
    }

    HI_LOG_ERROR("error, copy rsa key from user failed\n");
    HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);

    return HI_ERR_CIPHER_FAILED_MEM;
}

static void rsa_free_buffer(cryp_rsa_key *key)
{
    HI_LOG_FuncEnter();

    if (HI_NULL != key->N)
    {
        crypto_free(key->N);
        key->N = HI_NULL;
    }

    HI_LOG_FuncExit();
    return;
}

static s32 dispatch_rsa_encrypt(void *argp)
{
    s32 ret = HI_FAILURE;
    rsa_info_t *rsa_info = argp;
    u8 *in = HI_NULL;
    u8 *out = HI_NULL;
    cryp_rsa_key key;

    HI_LOG_FuncEnter();

    ret = rsa_alloc_buffer(&key, rsa_info, &in, &out);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, rsa_alloc_key failed\n");
        HI_LOG_PrintFuncErr(rsa_alloc_buffer, ret);
        return ret;
    }

    ret = kapi_rsa_encrypt(&key, rsa_info->enScheme, in, rsa_info->inlen,
            out, &rsa_info->outlen);
    if (HI_SUCCESS != ret)
    {
        rsa_free_buffer(&key);
        HI_LOG_PrintFuncErr(kapi_rsa_encrypt, ret);
        return ret;
    }

    ret = crypto_copy_to_user(ADDR_VIA(rsa_info->out), out, rsa_info->outlen);
    if (HI_SUCCESS != ret)
    {
        rsa_free_buffer(&key);
        HI_LOG_PrintFuncErr(crypto_copy_to_user, ret);
        return ret;
    }

    rsa_free_buffer(&key);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_rsa_decrypt(void *argp)
{
    s32 ret = HI_FAILURE;
    rsa_info_t *rsa_info = argp;
    u8 *in = HI_NULL;
    u8 *out = HI_NULL;
    cryp_rsa_key key;

    HI_LOG_FuncEnter();

    ret = rsa_alloc_buffer(&key, rsa_info, &in, &out);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, rsa_alloc_key failed\n");
        HI_LOG_PrintFuncErr(rsa_alloc_buffer, ret);
        return ret;
    }

    ret = kapi_rsa_decrypt(&key, rsa_info->enScheme,
                    in, rsa_info->inlen, out, &rsa_info->outlen);
    if (HI_SUCCESS != ret)
    {
        rsa_free_buffer(&key);
        HI_LOG_PrintFuncErr(kapi_rsa_decrypt, ret);
        return ret;
    }

    ret = crypto_copy_to_user(ADDR_VIA(rsa_info->out), out, rsa_info->outlen);
    if (HI_SUCCESS != ret)
    {
        rsa_free_buffer(&key);
        HI_LOG_PrintFuncErr(crypto_copy_to_user, ret);
        return ret;
    }

    rsa_free_buffer(&key);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_rsa_sign_hash(void *argp)
{
    s32 ret = HI_FAILURE;
    rsa_info_t *rsa_info = argp;
    u8 *in= HI_NULL;
    u8 *out = HI_NULL;
    cryp_rsa_key key;

    HI_LOG_FuncEnter();

    ret = rsa_alloc_buffer(&key, rsa_info, &in, &out);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, rsa alloc key buffer failed\n");
        HI_LOG_PrintFuncErr(rsa_alloc_buffer, ret);
        return ret;
    }

    ret = kapi_rsa_sign_hash(&key, rsa_info->enScheme, in,
            rsa_info->inlen, out, &rsa_info->outlen);
    if (HI_SUCCESS != ret)
    {
        rsa_free_buffer(&key);
        HI_LOG_PrintFuncErr(kapi_rsa_sign_hash, ret);
        return ret;
    }

    ret = crypto_copy_to_user(ADDR_VIA(rsa_info->out), out, rsa_info->outlen);
    if (HI_SUCCESS != ret)
    {
        rsa_free_buffer(&key);
        HI_LOG_PrintFuncErr(crypto_copy_to_user, ret);
        return ret;
    }

    rsa_free_buffer(&key);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 dispatch_rsa_verify_hash(void *argp)
{
    s32 ret = HI_FAILURE;
    rsa_info_t *rsa_info = argp;
    u8 *in= HI_NULL;
    u8 *out = HI_NULL;
    cryp_rsa_key key;

    HI_LOG_FuncEnter();

    ret = rsa_alloc_buffer(&key, rsa_info, &in, &out);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, rsa_alloc_key failed\n");
        HI_LOG_PrintFuncErr(rsa_alloc_buffer, ret);
        return ret;
    }

    /* copy hash value from user */
    CHECK_EXIT(crypto_copy_from_user(out, ADDR_VIA(rsa_info->out), rsa_info->outlen));
    CHECK_EXIT(kapi_rsa_verify_hash(&key,
                                    rsa_info->enScheme,
                                    out,
                                    rsa_info->outlen,
                                    in,
                                    rsa_info->inlen));
    rsa_free_buffer(&key);
    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    rsa_free_buffer(&key);

    return ret;
}

static s32 dispatch_rsa_compute_crt(void *argp)
{
    s32 ret = HI_FAILURE;

#ifdef SOFT_ECC_SUPPORT
    rsa_info_t *rsa_info = argp;
    u8 *in= HI_NULL;
    u8 *out = HI_NULL;
    cryp_rsa_key key;

    HI_LOG_FuncEnter();

    crypto_memset(&key, sizeof(key), 0, sizeof(key));

    rsa_info->public = HI_FALSE;
    ret = rsa_alloc_buffer(&key, rsa_info, &in, &out);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, rsa_alloc_key failed\n");
        HI_LOG_PrintFuncErr(rsa_alloc_buffer, ret);
        return ret;
    }

    CHECK_EXIT(ext_rsa_compute_crt(&key));

    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->dP), key.dP, key.klen / 2));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->dQ), key.dQ, key.klen / 2));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->qP), key.qP, key.klen / 2));

    rsa_free_buffer(&key);
    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    rsa_free_buffer(&key);
#endif

    return ret;
}

static s32 dispatch_rsa_gen_key(void *argp)
{
    s32 ret = HI_FAILURE;

#ifdef SOFT_ECC_SUPPORT
    rsa_info_t *rsa_info = argp;
    u8 *in= HI_NULL;
    u8 *out = HI_NULL;
    cryp_rsa_key key;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(RSA_KEY_BITWIDTH_4096 < rsa_info->klen);

    rsa_info->public = HI_FALSE;
    crypto_memset(&key, sizeof(key), 0, sizeof(key));

    ret = rsa_alloc_buffer(&key, rsa_info, &in, &out);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, rsa_alloc_key failed\n");
        HI_LOG_PrintFuncErr(rsa_alloc_buffer, ret);
        return ret;
    }

    CHECK_EXIT(kapi_rsa_gen_key(key.klen * BITS_IN_BYTE, key.e, &key));

    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->N), key.N, key.klen));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->d), key.d, key.klen));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->p), key.p, key.klen / 2));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->q), key.q, key.klen / 2));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->dP), key.dP, key.klen / 2));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->dQ), key.dQ, key.klen / 2));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(rsa_info->qP), key.qP, key.klen / 2));

    rsa_free_buffer(&key);
    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    rsa_free_buffer(&key);
#endif

    return ret;
}

static s32 dispatch_hdcp_encrypt(void *argp)
{
#ifdef CHIP_HDCP_SUPPORT
    s32 ret =HI_FAILURE;
    hdcp_key_t *hdcp_key = (hdcp_key_t *)argp;
    u32 *in = HI_NULL;
    u32 *out = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(MAX_MALLOC_BUF_SIZE < hdcp_key->len);

    in = crypto_calloc(1, hdcp_key->len);
    if (HI_NULL == in)
    {
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        HI_LOG_PrintFuncErr(crypto_calloc, ret);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    CHECK_EXIT(crypto_copy_from_user(in, ADDR_VIA(hdcp_key->in), hdcp_key->len));

    if (HI_NULL != ADDR_VIA(hdcp_key->out))
    {
        out = crypto_calloc(1, hdcp_key->len);
        if (HI_NULL == out)
        {
            HI_LOG_ERROR("error, malloc buffer for hdcp key output failed\n");
            ret = HI_ERR_CIPHER_FAILED_MEM;
            goto exit__;
        }
    }

    CHECK_EXIT(kapi_hdcp_encrypt(hdcp_key->keysel,
                                 hdcp_key->ramsel,
                                 hdcp_key->hostkey,
                                 in,
                                 out,
                                 hdcp_key->len,
                                 hdcp_key->decrypt));

    if (HI_NULL != out)
    {
        CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(hdcp_key->out), out, hdcp_key->len));
    }

    if (HI_NULL != in)
    {
        crypto_free(in);
        in = HI_NULL;
    }
    if (HI_NULL != out)
    {
        crypto_free(out);
        out = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    if (HI_NULL != in)
    {
        crypto_free(in);
        in = HI_NULL;
    }
    if (HI_NULL != out)
    {
        crypto_free(out);
        out = HI_NULL;
    }

    return ret;
#else
    HI_LOG_ERROR("Unsupport HDCP\n");
    return HI_FAILURE;
#endif
}

static s32 dispatch_trng_get_random(void *argp)
{
    trng_t *trng = argp;
    s32 ret = HI_FAILURE;
    u8 *randbyte = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(MAX_MALLOC_BUF_SIZE < trng->size);

    randbyte = crypto_malloc(trng->size);
    if (HI_NULL == randbyte)
    {
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        HI_LOG_PrintFuncErr(crypto_malloc, ret);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    ret = kapi_trng_get_rand_byte(randbyte, trng->size, trng->timeout);
    if (HI_SUCCESS != ret)
    {
        goto exit__;
    }

    ret = crypto_copy_to_user(ADDR_VIA(trng->randnum), randbyte, trng->size);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(crypto_copy_to_user, ret);
        goto exit__;
    }

exit__:
    if (HI_NULL != randbyte)
    {
        crypto_free(randbyte);
        randbyte = HI_NULL;
    }

    HI_LOG_FuncExit();
    return ret;
}

static s32 dispatch_sm2_sign(void *argp)
{
#ifdef HI_PRODUCT_SM2_SUPPORT

    s32 ret = HI_FAILURE;
    sm2_sign_t *sign = (sm2_sign_t *)argp;
    u8 *user_id = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(CRYPTO_MAGIC_NUM != sign->magic_num);
    HI_LOG_CHECK_PARAM(SM2_ID_MAX_LEN < (sign->idlen + 1));

    user_id = crypto_calloc(1, sign->idlen + 1);
    if (HI_NULL == user_id)
    {
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        HI_LOG_PrintFuncErr(crypto_calloc, ret);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    CHECK_EXIT(crypto_copy_from_user(user_id, ADDR_VIA(sign->id), sign->idlen));
    sign->src = HASH_CHUNCK_SRC_USER;
    CHECK_EXIT(kapi_sm2_sign(sign->d,
                             sign->px,
                             sign->py,
                             user_id,
                             sign->idlen,
                             ADDR_VIA(sign->msg),
                             sign->msglen,
                             sign->src,
                             sign->r,
                             sign->s));
    if (HI_NULL != user_id)
    {
        crypto_free(user_id);
        user_id = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;


exit__:
    if (HI_NULL != user_id)
    {
        crypto_free(user_id);
        user_id = HI_NULL;
    }

    return ret;
#else
    HI_LOG_ERROR("Unsupport SM2\n");
    return HI_FAILURE;
#endif
}

static s32 dispatch_sm2_verify(void *argp)
{
#ifdef HI_PRODUCT_SM2_SUPPORT
    s32 ret = HI_FAILURE;
    sm2_verify_t *verify = (sm2_verify_t *)argp;
    u8 *user_id = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(CRYPTO_MAGIC_NUM != verify->magic_num);
    HI_LOG_CHECK_PARAM(SM2_ID_MAX_LEN < (verify->idlen + 1));

    user_id = crypto_calloc(1, (verify->idlen + 1));
    if (HI_NULL == user_id)
    {
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        HI_LOG_PrintFuncErr(crypto_calloc, ret);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    CHECK_EXIT(crypto_copy_from_user(user_id, ADDR_VIA(verify->id), verify->idlen));
    verify->src = HASH_CHUNCK_SRC_USER;
    CHECK_EXIT(kapi_sm2_verify(verify->px,
                               verify->py,
                               user_id,
                               verify->idlen,
                               ADDR_VIA(verify->msg),
                               verify->msglen,
                               verify->src,
                               verify->r,
                               verify->s));
    if (HI_NULL != user_id)
    {
        crypto_free(user_id);
        user_id = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    if (HI_NULL != user_id)
    {
        crypto_free(user_id);
        user_id = HI_NULL;
    }

    return ret;
#else
    HI_LOG_ERROR("Unsupport SM2\n");
    return HI_FAILURE;
#endif
}

static s32 dispatch_sm2_encrypt(void *argp)
{
#ifdef HI_PRODUCT_SM2_SUPPORT
    s32 ret = HI_FAILURE;
    sm2_encrypt_t *encrypt = (sm2_encrypt_t *)argp;
    u8 *msg = HI_NULL;
    u8 *enc = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(CRYPTO_MAGIC_NUM != encrypt->magic_num);
    HI_LOG_CHECK_PARAM(SM2_LEN_IN_WROD != encrypt->keylen);
    HI_LOG_CHECK_PARAM(MAX_MALLOC_BUF_SIZE < encrypt->msglen);

    msg = crypto_calloc(1, encrypt->msglen);
    if (HI_NULL == msg)
    {
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        HI_LOG_PrintFuncErr(crypto_calloc, ret);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    enc = crypto_calloc(1, encrypt->msglen + SM2_ENCRYPT_PAD_LEN);
    if (HI_NULL == enc)
    {
        crypto_free(msg);
        msg = HI_NULL;
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    CHECK_EXIT(crypto_copy_from_user(msg, ADDR_VIA(encrypt->msg), encrypt->msglen));
    CHECK_EXIT(kapi_sm2_encrypt(encrypt->px, encrypt->py, msg, encrypt->msglen, enc,
        &encrypt->enclen));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(encrypt->enc), enc, encrypt->enclen));

    if (HI_NULL != msg)
    {
        crypto_free(msg);
        msg = HI_NULL;
    }
    if (HI_NULL != enc)
    {
        crypto_free(enc);
        enc = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    if (HI_NULL != msg)
    {
        crypto_free(msg);
        msg = HI_NULL;
    }
    if (HI_NULL != enc)
    {
        crypto_free(enc);
        enc = HI_NULL;
    }

    return ret;
#else
    HI_LOG_ERROR("Unsupport SM2\n");
    return HI_FAILURE;
#endif
}

static s32 dispatch_sm2_decrypt(void *argp)
{
#ifdef HI_PRODUCT_SM2_SUPPORT
    s32 ret = HI_FAILURE;
    sm2_decrypt_t *decrypt = (sm2_decrypt_t *)argp;
    u8 *msg = HI_NULL;
    u8 *enc = HI_NULL;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(CRYPTO_MAGIC_NUM != decrypt->magic_num);
    HI_LOG_CHECK_PARAM(SM2_LEN_IN_WROD != decrypt->keylen);
    HI_LOG_CHECK_PARAM(HI_NULL == ADDR_VIA(decrypt->msg));
    HI_LOG_CHECK_PARAM(HI_NULL == ADDR_VIA(decrypt->enc));
    HI_LOG_CHECK_PARAM(SM2_ENCRYPT_PAD_LEN > decrypt->enclen);
    HI_LOG_CHECK_PARAM(MAX_MALLOC_BUF_SIZE < decrypt->enclen);

    msg = crypto_calloc(1, decrypt->enclen - SM2_ENCRYPT_PAD_LEN);
    if (HI_NULL == msg)
    {
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        HI_LOG_PrintFuncErr(crypto_calloc, ret);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    enc = crypto_calloc(1, decrypt->enclen);
    if (HI_NULL == enc)
    {
        crypto_free(msg);
        msg = HI_NULL;
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    CHECK_EXIT(crypto_copy_from_user(enc, ADDR_VIA(decrypt->enc), decrypt->enclen));
    CHECK_EXIT(kapi_sm2_decrypt(decrypt->d, enc, decrypt->enclen, msg, &decrypt->msglen));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(decrypt->msg), msg, decrypt->msglen));

    if (HI_NULL != msg)
    {
        crypto_free(msg);
        msg = HI_NULL;
    }
    if (HI_NULL != enc)
    {
        crypto_free(enc);
        enc = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    if (HI_NULL != msg)
    {
        crypto_free(msg);
        msg = HI_NULL;
    }
    if (HI_NULL != enc)
    {
        crypto_free(enc);
        enc = HI_NULL;
    }

    return ret;
#else
    HI_LOG_ERROR("Unsupport SM2\n");
    return HI_FAILURE;
#endif
}

static s32 dispatch_sm2_gen_key(void *argp)
{
#ifdef HI_PRODUCT_SM2_SUPPORT
    s32 ret = HI_FAILURE;
    sm2_key_t *key = (sm2_key_t *)argp;

    HI_LOG_FuncEnter();
    HI_LOG_CHECK_PARAM(SM2_LEN_IN_WROD != key->keylen);
    HI_LOG_CHECK_PARAM(CRYPTO_MAGIC_NUM != key->magic_num);

    ret = kapi_sm2_gen_key(key->d, key->px, key->py);

    HI_LOG_FuncExit();

    return ret;
#else
    HI_LOG_ERROR("Unsupport SM2\n");
    return HI_FAILURE;
#endif
}

static s32 dispatch_cenc_decrypt(void *argp)
{
#if defined(HI_PRODUCT_CENC_SUPPORT)
    s32 ret = HI_FAILURE;
    cenc_info_t *cenc = argp;

    HI_LOG_FuncEnter();

#ifdef HI_PLATFORM_TYPE_TEE
    HI_TEE_RIGHTCHECK_R(ADDR_VIA(cenc->subsample), cenc->subsample_num * sizeof(HI_TEE_CIPHER_SUBSAMPLE_S));
#endif

    ret = kapi_symc_cenc_decrypt(cenc->id,
                       cenc->key,
                       cenc->iv,
                       HI_FALSE,
                       cenc->inphy,
                       cenc->outphy,
                       cenc->length,
                       cenc->firstoffset,
                       ADDR_VIA(cenc->subsample),
                       cenc->subsample_num);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_cenc_decrypt, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
#else
    HI_LOG_ERROR("Unsupport CENC\n");
    return HI_FAILURE;
#endif
}

static s32 dispatch_cenc_decrypt_ex(void *argp)
{
#if defined(HI_PRODUCT_CENC_SUPPORT)
    s32 ret = HI_FAILURE;
    cenc_info_t *cenc = argp;

    HI_LOG_FuncEnter();

#ifdef HI_PLATFORM_TYPE_TEE
    HI_TEE_RIGHTCHECK_R(ADDR_VIA(cenc->subsample), cenc->subsample_num * sizeof(HI_TEE_CIPHER_SUBSAMPLE_EX_S));
#endif

    ret = kapi_symc_cenc_decrypt(cenc->id,
                       cenc->key,
                       cenc->iv,
                       cenc->oddkey | CENC_ODDKEY_SUPPORT,
                       cenc->inphy,
                       cenc->outphy,
                       cenc->length,
                       cenc->firstoffset,
                       ADDR_VIA(cenc->subsample),
                       cenc->subsample_num);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_cenc_decrypt, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
#else
    HI_LOG_ERROR("Unsupport CENC\n");
    return HI_FAILURE;
#endif
}

#ifdef SOFT_ECC_SUPPORT
static s32 dispatch_ecc_alloc_param(ecc_info_t *info, ecc_param_t *ecc)
{
    s32 ret = HI_FAILURE;

    HI_LOG_CHECK_PARAM(MAX_MALLOC_BUF_SIZE < info->ksize);

    HI_LOG_DEBUG("ecc->ksize 0x%x\n", info->ksize);

    ecc->p = crypto_calloc(1, info->ksize * ECC_PARAM_CNT);
    if (HI_NULL == ecc->p)
    {
        HI_LOG_ERROR("error, malloc for ecc->p failed\n");
        HI_LOG_PrintFuncErr(crypto_calloc, HI_ERR_CIPHER_FAILED_MEM);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    ecc->b = ecc->p + info->ksize;
    ecc->a = ecc->b + info->ksize;
    ecc->Gx= ecc->a + info->ksize;
    ecc->Gy= ecc->Gx + info->ksize;
    ecc->n = ecc->Gy + info->ksize;

    ecc->h = info->h;
    ecc->ksize = info->ksize;

    CHECK_EXIT(crypto_copy_from_user(ecc->p, ADDR_VIA(info->p), ecc->ksize));
    CHECK_EXIT(crypto_copy_from_user(ecc->b, ADDR_VIA(info->b), ecc->ksize));
    CHECK_EXIT(crypto_copy_from_user(ecc->a, ADDR_VIA(info->a), ecc->ksize));
    CHECK_EXIT(crypto_copy_from_user(ecc->Gx, ADDR_VIA(info->Gx), ecc->ksize));
    CHECK_EXIT(crypto_copy_from_user(ecc->Gy, ADDR_VIA(info->Gy), ecc->ksize));
    CHECK_EXIT(crypto_copy_from_user(ecc->n, ADDR_VIA(info->n), ecc->ksize));

    return HI_SUCCESS;

exit__:
    if (HI_NULL != ecc->p)
    {
        crypto_free(ecc->p);
        ecc->p = HI_NULL;
    }

    return ret;
}

static void dispatch_ecc_free_param(ecc_param_t *ecc)
{
    if (HI_NULL != ecc->p)
    {
        crypto_free(ecc->p);
    }

    ecc->p = HI_NULL;
    ecc->a = HI_NULL;
    ecc->b = HI_NULL;
    ecc->Gx= HI_NULL;
    ecc->Gy= HI_NULL;
    ecc->n = HI_NULL;
    return;
}
#endif

static s32 dispatch_ecdh_compute_key(void *argp)
{
    s32 ret = HI_FAILURE;

#ifdef SOFT_ECC_SUPPORT
    ecc_info_t *info = argp;
    ecc_param_t ecc;
    u8 *buf = HI_NULL;
    u8 *d = HI_NULL;
    u8 *px = HI_NULL;
    u8 *py = HI_NULL;
    u8 *sharekey = HI_NULL;

    HI_LOG_FuncEnter();
    HI_LOG_CHECK_PARAM(CRYPTO_MAGIC_NUM != info->magic_num);

    ret = dispatch_ecc_alloc_param(info, &ecc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, dispatch_ecc_alloc_param failed\n");
        HI_LOG_PrintFuncErr(dispatch_ecc_alloc_param, ret);
        return ret;
    }

    /*alloc buffer for p, px, py, sharekey */
    buf = crypto_calloc(1, ecc.ksize * 4);
    if (HI_NULL == buf)
    {
        HI_LOG_ERROR("error, malloc for key failed\n");
        HI_LOG_PrintFuncErr(crypto_calloc, HI_ERR_CIPHER_FAILED_MEM);
        goto exit__;
    }
    d = buf;
    px = d + ecc.ksize;
    py = px + ecc.ksize;
    sharekey = py + ecc.ksize;

    CHECK_EXIT(crypto_copy_from_user(d, ADDR_VIA(info->d), ecc.ksize));
    CHECK_EXIT(crypto_copy_from_user(px, ADDR_VIA(info->Px), ecc.ksize));
    CHECK_EXIT(crypto_copy_from_user(py, ADDR_VIA(info->Py), ecc.ksize));
    CHECK_EXIT(ext_ecdh_compute_key(&ecc, d, px, py, sharekey));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(info->msg), sharekey, ecc.ksize));

    dispatch_ecc_free_param(&ecc);
    if (HI_NULL != buf)
    {
        crypto_free(buf);
        buf = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    dispatch_ecc_free_param(&ecc);
    if (HI_NULL != buf)
    {
        crypto_free(buf);
        buf = HI_NULL;
    }
#else
    HI_LOG_ERROR("error, ECC Alg nonsupport\n");
#endif

    return ret;
}

static s32 dispatch_ecc_gen_key(void *argp)
{
    s32 ret = HI_FAILURE;

#ifdef SOFT_ECC_SUPPORT
    ecc_info_t *info = argp;
    ecc_param_t ecc;
    u8 *buf = HI_NULL;
    u8 *inkey = HI_NULL;
    u8 *outkey = HI_NULL;
    u8 *px = HI_NULL;
    u8 *py = HI_NULL;

    HI_LOG_FuncEnter();
    HI_LOG_CHECK_PARAM(CRYPTO_MAGIC_NUM != info->magic_num);

    ret = dispatch_ecc_alloc_param(info, &ecc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, dispatch_ecc_alloc_param failed\n");
        HI_LOG_PrintFuncErr(dispatch_ecc_alloc_param, ret);
        return ret;
    }

    /*alloc buffer for px, py, inkey,  outkey*/
    buf = crypto_calloc(1, ecc.ksize * 4);
    if (HI_NULL == buf)
    {
        HI_LOG_ERROR("error, malloc for key failed\n");
        HI_LOG_PrintFuncErr(crypto_calloc, HI_ERR_CIPHER_FAILED_MEM);
        goto exit__;
    }
    px = buf;
    py = px + ecc.ksize;
    inkey = py + ecc.ksize;
    outkey = inkey + ecc.ksize;

    if (HI_NULL != ADDR_VIA(info->msg))
    {
        CHECK_EXIT(crypto_copy_from_user(inkey, ADDR_VIA(info->msg), ecc.ksize));
    }
    else
    {
        inkey = HI_NULL;
    }

    CHECK_EXIT(ext_ecc_gen_key(&ecc, inkey, outkey, px, py));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(info->d), outkey, ecc.ksize));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(info->Px), px, ecc.ksize));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(info->Py), py, ecc.ksize));

    dispatch_ecc_free_param(&ecc);
    if (HI_NULL != buf)
    {
        crypto_free(buf);
        buf = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    dispatch_ecc_free_param(&ecc);
    if (HI_NULL != buf)
    {
        crypto_free(buf);
        buf = HI_NULL;
    }

#else
    HI_LOG_ERROR("error, ECC Alg nonsupport\n");
#endif

    return ret;
}

static s32 dispatch_ecdsa_sign_hash(void *argp)
{
    s32 ret = HI_FAILURE;

#ifdef SOFT_ECC_SUPPORT
    ecc_info_t *info = argp;
    ecc_param_t ecc;
    u8 *buf = HI_NULL;
    u8 *d = HI_NULL;
    u8 *hash = HI_NULL;
    u8 *r = HI_NULL;
    u8 *s = HI_NULL;

    HI_LOG_FuncEnter();
    HI_LOG_CHECK_PARAM(CRYPTO_MAGIC_NUM != info->magic_num);
    HI_LOG_CHECK_PARAM(HASH_RESULT_MAX_SIZE < info->mlen);

    ret = dispatch_ecc_alloc_param(info, &ecc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, dispatch_ecc_alloc_param failed\n");
        HI_LOG_PrintFuncErr(dispatch_ecc_alloc_param, ret);
        return ret;
    }

    /*alloc buffer for d, hash, r, s*/
    buf = crypto_calloc(1, ecc.ksize * 3 + info->mlen);
    if (HI_NULL == buf)
    {
        HI_LOG_ERROR("error, malloc for buf failed\n");
        HI_LOG_PrintFuncErr(crypto_calloc, HI_ERR_CIPHER_FAILED_MEM);
        goto exit__;
    }
    d = buf;
    r = d + ecc.ksize;
    s = r + ecc.ksize;
    hash = s + ecc.ksize;

    CHECK_EXIT(crypto_copy_from_user(d, ADDR_VIA(info->d), ecc.ksize));
    CHECK_EXIT(crypto_copy_from_user(hash, ADDR_VIA(info->msg), info->mlen));

    CHECK_EXIT(ext_ecdsa_sign_hash(&ecc, d, hash, info->mlen, r, s));

    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(info->r), r, ecc.ksize));
    CHECK_EXIT(crypto_copy_to_user(ADDR_VIA(info->s), s, ecc.ksize));

    dispatch_ecc_free_param(&ecc);
    if (HI_NULL != buf)
    {
        crypto_free(buf);
        buf = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    dispatch_ecc_free_param(&ecc);
    if (HI_NULL != buf)
    {
        crypto_free(buf);
        buf = HI_NULL;
    }

    HI_LOG_FuncExit();
#else
    HI_LOG_ERROR("error, ECC Alg nonsupport\n");
#endif

    return ret;
}

static s32 dispatch_ecdsa_verify_hash(void *argp)
{
    s32 ret = HI_FAILURE;

#ifdef SOFT_ECC_SUPPORT
    ecc_info_t *info = argp;
    ecc_param_t ecc;
    u8 *buf = HI_NULL;
    u8 *px = HI_NULL;
    u8 *py = HI_NULL;
    u8 *hash = HI_NULL;
    u8 *r = HI_NULL;
    u8 *s = HI_NULL;

    HI_LOG_FuncEnter();
    HI_LOG_CHECK_PARAM(CRYPTO_MAGIC_NUM != info->magic_num);
    HI_LOG_CHECK_PARAM(HASH_RESULT_MAX_SIZE < info->mlen);

    ret = dispatch_ecc_alloc_param(info, &ecc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, dispatch_ecc_alloc_param failed\n");
        HI_LOG_PrintFuncErr(dispatch_ecc_alloc_param, ret);
        return ret;
    }

    /*alloc buffer for px, py, hash, r, s*/
    buf = crypto_calloc(1, ecc.ksize * 4 + info->mlen);
    if (HI_NULL == buf)
    {
        HI_LOG_ERROR("error, malloc for key failed\n");
        HI_LOG_PrintFuncErr(crypto_calloc, HI_ERR_CIPHER_FAILED_MEM);
        goto exit__;
    }
    px = buf;
    py = px + ecc.ksize;
    r = py + ecc.ksize;
    s = r + ecc.ksize;
    hash = s + ecc.ksize;

    CHECK_EXIT(crypto_copy_from_user(px, ADDR_VIA(info->Px), ecc.ksize));
    CHECK_EXIT(crypto_copy_from_user(py, ADDR_VIA(info->Py), ecc.ksize));
    CHECK_EXIT(crypto_copy_from_user(hash, ADDR_VIA(info->msg), info->mlen));
    CHECK_EXIT(crypto_copy_from_user(r, ADDR_VIA(info->r), ecc.ksize));
    CHECK_EXIT(crypto_copy_from_user(s, ADDR_VIA(info->s), ecc.ksize));

    CHECK_EXIT(ext_ecdsa_verify_hash(&ecc, px, py, hash, info->mlen, r, s));
    dispatch_ecc_free_param(&ecc);
    if (HI_NULL != buf)
    {
        crypto_free(buf);
        buf = HI_NULL;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    dispatch_ecc_free_param(&ecc);
    if (HI_NULL != buf)
    {
        crypto_free(buf);
        buf = HI_NULL;
    }
#else
    HI_LOG_ERROR("error, ECC Alg nonsupport\n");
#endif

    return ret;
}

static crypto_dispatch_func dispatch_func[CRYPTO_CMD_COUNT] =
{
    {"CreateHandle",  dispatch_symc_create_handle,  CRYPTO_CMD_SYMC_CREATEHANDLE},
    {"DestroyHandle", dispatch_symc_destroy_handle, CRYPTO_CMD_SYMC_DESTROYHANDLE},
    {"ConfigChn",     dispatch_symc_config,         CRYPTO_CMD_SYMC_CONFIGHANDLE},
    {"Encrypt",       dispatch_symc_encrypt,        CRYPTO_CMD_SYMC_ENCRYPT},
    {"EncryptMulti",  dispatch_symc_encrypt_multi,  CRYPTO_CMD_SYMC_ENCRYPTMULTI},
    {"CMAC",          dispatch_symc_camc,           CRYPTO_CMD_SYMC_CMAC},
    {"GetTag",        dispatch_symc_get_tag,        CRYPTO_CMD_SYMC_GETTAG},
    {"CencDerypt",    dispatch_cenc_decrypt,        CRYPTO_CMD_CENC},
    {"HashStart",     dispatch_hash_start,          CRYPTO_CMD_HASH_START},
    {"HashUpdate",    dispatch_hash_update,         CRYPTO_CMD_HASH_UPDATE},
    {"HashFinish",    dispatch_hash_finish,         CRYPTO_CMD_HASH_FINISH},
    {"RsaEncrypt",    dispatch_rsa_encrypt,         CRYPTO_CMD_RSA_ENC},
    {"RsaDecrypt",    dispatch_rsa_decrypt,         CRYPTO_CMD_RSA_DEC},
    {"RsaSign",       dispatch_rsa_sign_hash,       CRYPTO_CMD_RSA_SIGN},
    {"RsaVerify",     dispatch_rsa_verify_hash,     CRYPTO_CMD_RSA_VERIFY},
    {"RsaComputeCrt", dispatch_rsa_compute_crt,     CRYPTO_CMD_RSA_COMPUTE_CRT},
    {"RsaGenKey",     dispatch_rsa_gen_key,         CRYPTO_CMD_RSA_GEN_KEY},
    {"HdcpEncrypt",   dispatch_hdcp_encrypt,        CRYPTO_CMD_HDCP_ENCRYPT},
    {"TRNG",          dispatch_trng_get_random,     CRYPTO_CMD_TRNG},
    {"Sm2Sign",       dispatch_sm2_sign,            CRYPTO_CMD_SM2_SIGN},
    {"Sm2Verify",     dispatch_sm2_verify,          CRYPTO_CMD_SM2_VERIFY},
    {"Sm2Encrypt",    dispatch_sm2_encrypt,         CRYPTO_CMD_SM2_ENCRYPT},
    {"Sm2Decrypt",    dispatch_sm2_decrypt,         CRYPTO_CMD_SM2_DECRYPT},
    {"Sm2GenKey",     dispatch_sm2_gen_key,         CRYPTO_CMD_SM2_GEN_KEY},
    {"EcdhComputeKey",dispatch_ecdh_compute_key,    CRYPTO_CMD_ECDH_COMPUTE_KEY},
    {"EcdhGenKey",    dispatch_ecc_gen_key,         CRYPTO_CMD_ECC_GEN_KEY},
    {"EcdsaSign",     dispatch_ecdsa_sign_hash,     CRYPTO_CMD_ECDSA_SIGN},
    {"EcdsaVerify",   dispatch_ecdsa_verify_hash,   CRYPTO_CMD_ECDSA_VERIFY},
    {"GetSymcConfig", dispatch_symc_get_config,     CRYPTO_CMD_SYMC_GET_CONFIG},
    {"CencDerypt",    dispatch_cenc_decrypt_ex,     CRYPTO_CMD_CENC_EX},
};

s32 crypto_ioctl(u32 cmd, HI_VOID *argp)
{
    u32 nr = 0;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    nr = CRYPTO_IOC_NR (cmd);

    HI_LOG_DEBUG("cmd 0x%x, nr %d, size %d, local cmd 0x%x\n",
        cmd, nr, CRYPTO_IOC_SIZE(cmd), dispatch_func[nr].cmd);

    HI_LOG_CHECK_PARAM(HI_NULL == argp);
    HI_LOG_CHECK_PARAM(CRYPTO_CMD_COUNT <= nr);
    HI_LOG_CHECK_PARAM(cmd != dispatch_func[nr].cmd);

    HI_LOG_INFO("Link Func NR %d, Name:  %s\n", nr, dispatch_func[nr].name);
    ret = dispatch_func[nr].func(argp);
    if (HI_SUCCESS != ret)
    {
        /*TRNG may be empty in FIFO, don't report error, try to read it again */
        if (CRYPTO_CMD_TRNG != cmd)
        {
            HI_LOG_ERROR("error, call dispatch_fun fun failed!\n");
            HI_LOG_PrintFuncErr(crypto_dispatch_func, ret);
        }
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 crypto_entry(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    crypto_mem_init();

    ret = module_addr_map();
    if (HI_SUCCESS != ret)
    {
       HI_LOG_ERROR("module addr map failed\n");
       HI_LOG_PrintFuncErr(module_addr_map, ret);
       return ret;
    }

    ret = kapi_symc_init();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("kapi symc init failed\n");
        HI_LOG_PrintFuncErr(kapi_symc_init, ret);
        goto error;
    }

    ret = kapi_hash_init();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("kapi hash init failed\n");
        HI_LOG_PrintFuncErr(kapi_hash_init, ret);
        goto error1;
    }

    ret = kapi_rsa_init();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("kapi rsa init failed\n");
        HI_LOG_PrintFuncErr(kapi_hash_init, ret);
        goto error2;
    }

#ifdef HI_PRODUCT_SM2_SUPPORT
    ret = kapi_sm2_init();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("kapi sm2 init failed\n");
        HI_LOG_PrintFuncErr(kapi_sm2_init, ret);
        kapi_rsa_deinit();
        goto error2;
    }
#endif

    HI_LOG_FuncExit();
    return HI_SUCCESS;

error2:
    kapi_hash_deinit();
error1:
    kapi_symc_deinit();
error:
    module_addr_unmap();

    return ret;

}

s32 crypto_exit(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = kapi_symc_deinit();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_deinit, ret);
        return ret;
    }

    ret = kapi_hash_deinit();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_hash_deinit, ret);
        return ret;
    }

    ret = kapi_rsa_deinit();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_rsa_deinit, ret);
        return ret;
    }

#ifdef HI_PRODUCT_SM2_SUPPORT
    ret = kapi_sm2_deinit();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_sm2_deinit, ret);
        return ret;
    }
#endif

    ret = module_addr_unmap();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(module_addr_unmap, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}


s32 crypto_release(void)
{
    s32 ret = HI_FAILURE;

    ret = kapi_symc_release();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_release, ret);
        return ret;
    }

    ret = kapi_hash_release();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_hash_release, ret);
        return ret;
    }

    return HI_SUCCESS;
}

/** @}*/  /** <!-- ==== Structure Definition end ====*/

