/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : kapi_hash.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_hash.h"
#include "ext_alg.h"

#ifdef MHASH_NONSUPPORT
#define HASH_SOFT_CHANNEL_MAX            (0x01)
#define HASH_SOFT_CHANNEL_MASK           (0x01)
#else
#define HASH_SOFT_CHANNEL_MAX            (0x08)
#define HASH_SOFT_CHANNEL_MASK           (0xFF)
#endif

/*! /hmac ipad byte */
#define HMAC_IPAD_BYTE                   (0x36)

/*! /hmac opad byte */
#define HMAC_OPAD_BYTE                   (0x5C)

#define HMAC_HASH                        (0x01)
#define HMAC_AESCBC                      (0x02)

typedef struct
{
    hash_func *func;                   /*!<  HASH function */
    void *cryp_ctx;                    /*!<  Context of cryp instance */
    u32 hmac;                          /*!<  HMAC or not */
    u32 mac_id;                        /*!<  CMAC handle */
    u8 hmac_ipad[HASH_BLOCK_SIZE_128]; /*!<  hmac ipad */
    u8 hmac_opad[HASH_BLOCK_SIZE_128]; /*!<  hmac opad */
    crypto_owner owner;                /*!<  user ID */
}kapi_hash_ctx;

/*! Context of cipher */
static channel_context hash_ctx[HASH_SOFT_CHANNEL_MAX];

/*! hash mutex */
static crypto_mutex hash_mutex;

#define kapi_check_hash_handle(handle)   \
do \
{ \
    if((HI_ID_CIPHER != HI_HANDLE_GET_MODID(handle)) \
        || (0 != HI_HANDLE_GET_PriDATA(handle))) \
    { \
        HI_LOG_ERROR("invalid handle 0x%x!\n", handle); \
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA); \
        return HI_ERR_CIPHER_INVALID_HANDLE; \
    } \
    if (HI_HANDLE_GET_CHNID(handle) >= HASH_SOFT_CHANNEL_MAX) \
    { \
        HI_LOG_ERROR("chan %d is too large, max: %d\n", HI_HANDLE_GET_CHNID(handle), HASH_SOFT_CHANNEL_MAX); \
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA); \
        return HI_ERR_CIPHER_INVALID_HANDLE; \
    } \
    if (HI_FALSE == hash_ctx[HI_HANDLE_GET_CHNID(handle)].open) \
    { \
        HI_LOG_ERROR("chan %d is not open\n", HI_HANDLE_GET_CHNID(handle)); \
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA); \
        return HI_ERR_CIPHER_INVALID_HANDLE; \
    } \
} while (0)

#define KAPI_HASH_LOCK()   \
    ret = crypto_mutex_lock(&hash_mutex);  \
    if (HI_SUCCESS != ret)        \
    {\
        HI_LOG_ERROR("error, hash lock failed\n");\
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_BUSY); \
        return HI_ERR_CIPHER_BUSY;\
    }

#define KAPI_HASH_UNLOCK()   crypto_mutex_unlock(&hash_mutex)

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      hash */
/** @{*/  /** <!-- [kapi]*/

s32 kapi_hash_init(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_INFO("HASH init\n");

    crypto_mutex_init(&hash_mutex);

    ret = cryp_hash_init();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, cryp_hash_init failed\n");
        HI_LOG_PrintFuncErr(cryp_hash_init, ret);
        return ret;
    }

    /* Initialize soft channel list */
    ret = crypto_channel_init(hash_ctx, HASH_SOFT_CHANNEL_MAX, sizeof(kapi_hash_ctx));
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, hash channel list init failed\n");
        HI_LOG_PrintFuncErr(crypto_channel_init, ret);
        cryp_hash_deinit();
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_hash_deinit(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = crypto_channel_deinit(hash_ctx, HASH_SOFT_CHANNEL_MAX);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, hash channel list deinit failed\n");
        HI_LOG_PrintFuncErr(crypto_channel_deinit, ret);
        return ret;
    }

    cryp_hash_deinit();

    crypto_mutex_destroy(&hash_mutex);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static kapi_hash_ctx *kapi_hash_get_ctx(u32 id)
{
    return crypto_channel_get_context(hash_ctx, HASH_SOFT_CHANNEL_MAX, id);
}

static s32 kapi_hash_create(u32 *id)
{
    s32 ret = HI_FAILURE;
    u32 chn = 0;

    HI_LOG_FuncEnter();

    /* allocate a hash channel */
    ret = crypto_channel_alloc(hash_ctx, HASH_SOFT_CHANNEL_MAX, HASH_SOFT_CHANNEL_MASK, &chn);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, allocate hash channel failed\n");
        HI_LOG_PrintFuncErr(crypto_channel_alloc, ret);
        return ret;
    }

    *id = chn;

    HI_LOG_DEBUG("kapi create soft chn %d\n", chn);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 kapi_hash_destroy(u32 id)
{
    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HASH_SOFT_CHANNEL_MAX <= id);

    /* Free soft channel */
    crypto_channel_free(hash_ctx, HASH_SOFT_CHANNEL_MAX, id);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 kapi_hash_mode_transform(CRYP_CIPHER_HASH_TYPE_E type,
                                    hash_mode *mode, u32 *hmac)
{
    *hmac = HI_FALSE;

    /* transform hash mode */
    switch(type)
    {
        case CRYP_CIPHER_HASH_TYPE_HMAC_SHA1:
        {
            *hmac = HMAC_HASH;
            *mode = HASH_MODE_SHA1;
            break;
        }
        case CRYP_CIPHER_HASH_TYPE_SHA1:
        {
            *mode = HASH_MODE_SHA1;
            break;
        }
        case CRYP_CIPHER_HASH_TYPE_HMAC_SHA224:
        {
            *hmac = HMAC_HASH;
            *mode = HASH_MODE_SHA224;
            break;
        }
        case CRYP_CIPHER_HASH_TYPE_SHA224:
        {
            *mode = HASH_MODE_SHA224;
            break;
        }
        case CRYP_CIPHER_HASH_TYPE_HMAC_SHA256:
        {
            *hmac = HMAC_HASH;
            *mode = HASH_MODE_SHA256;
            break;
        }
        case CRYP_CIPHER_HASH_TYPE_SHA256:
        {
            *mode = HASH_MODE_SHA256;
            break;
        }
#ifdef HI_PRODUCT_SHA512_SUPPORT
        case CRYP_CIPHER_HASH_TYPE_HMAC_SHA384:
        {
            *hmac = HMAC_HASH;
            *mode = HASH_MODE_SHA384;
            break;
        }
        case CRYP_CIPHER_HASH_TYPE_SHA384:
        {
            *mode = HASH_MODE_SHA384;
            break;
        }
        case CRYP_CIPHER_HASH_TYPE_HMAC_SHA512:
        {
            *hmac = HMAC_HASH;
            *mode = HASH_MODE_SHA512;
            break;
        }
        case CRYP_CIPHER_HASH_TYPE_SHA512:
        {
            *mode = HASH_MODE_SHA512;
            break;
        }
        case CRYP_CIPHER_HASH_TYPE_SM3:
        {
            *mode = HASH_MODE_SM3;
            break;
        }
#endif
#if defined(HASH_CMAC_SUPPORT)
        case CRYP_CIPHER_HASH_TYPE_CBCMAC:
        {
            *hmac = HMAC_AESCBC;
            *mode = HASH_MODE_COUNT;
            break;
        }
#endif
        default:
        {
            HI_LOG_ERROR("error, invalid hash type %d\n", type);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    return HI_SUCCESS;
}

static s32 kapi_hmac_start(kapi_hash_ctx *ctx, u8 *key, u32 keylen)
{
    s32 ret = HI_FAILURE;
    u8 sum[HASH_RESULT_MAX_SIZE] = {0};
    u32 len = 0;
    u32 i;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == key);

    /* clean ipad and opad */
    crypto_memset(ctx->hmac_ipad, HASH_BLOCK_SIZE_128, 0x00, ctx->func->block_size);
    crypto_memset(ctx->hmac_opad, HASH_BLOCK_SIZE_128, 0x00, ctx->func->block_size);

    /* compute K0 */

    if (keylen <= ctx->func->block_size)
    {
        /* If the length of K = B: set K0 = K.
         *
         * If the length of K > B: hash K to obtain an L byte string,
         * then append (B-L) zeros to create a B-byte
         * string K0 (i.e., K0 = H(K) || 00...00).
         */
         crypto_memcpy(ctx->hmac_ipad, HASH_BLOCK_SIZE_128, key, keylen);
         crypto_memcpy(ctx->hmac_opad, HASH_BLOCK_SIZE_128, key, keylen);
    }
    else
    {
        /* If the length of K > B: hash K to obtain an L byte string,
         * then append (B-L) zeros to create a B-byte
         * string K0 (i.e., K0 = H(K) || 00...00).
         */

        /* H(K) */
        ctx->cryp_ctx = ctx->func->create(ctx->func->mode);
        if (HI_NULL == ctx->cryp_ctx)
        {
            HI_LOG_PrintFuncErr(ctx->func->create, 0);
            return HI_ERR_CIPHER_BUSY;
        }

        /* update key */
        CHECK_EXIT(ctx->func->update(ctx->cryp_ctx, key,
            keylen, HASH_CHUNCK_SRC_LOCAL));

        /* sum */
        CHECK_EXIT(ctx->func->finish(ctx->cryp_ctx, sum, &len));
        ctx->func->destroy(ctx->cryp_ctx);
        ctx->cryp_ctx = HI_NULL;

        /* K0 = H(K) || 00...00 */
        crypto_memcpy(ctx->hmac_ipad, HASH_BLOCK_SIZE_128, sum, len);
        crypto_memcpy(ctx->hmac_opad, HASH_BLOCK_SIZE_128, sum, len);
    }

    /* Exclusive-Or K0 with ipad/opad byte to produce K0 ^ ipad and K0 ^ opad */
    for (i = 0; i < ctx->func->block_size; i++)
    {
        ctx->hmac_ipad[i] ^=  HMAC_IPAD_BYTE;
        ctx->hmac_opad[i] ^=  HMAC_OPAD_BYTE;
    }

    /* H(K0 ^ ipad) */
    ctx->cryp_ctx = ctx->func->create(ctx->func->mode);
    if (HI_NULL == ctx->cryp_ctx)
    {
        HI_LOG_PrintFuncErr(ctx->func->create, 0);
        return HI_ERR_CIPHER_BUSY;
    }
    CHECK_EXIT(ctx->func->update(ctx->cryp_ctx, ctx->hmac_ipad,
        ctx->func->block_size, HASH_CHUNCK_SRC_LOCAL));

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:
    ctx->func->destroy(ctx->cryp_ctx);
    ctx->cryp_ctx = HI_NULL;

    return ret;

}

static s32 kapi_hmac_finish(kapi_hash_ctx *ctx, u8 *hash, u32 *hashlen)
{
    s32 ret = HI_FAILURE;
    u8 sum[HASH_RESULT_MAX_SIZE] = {0};

    HI_LOG_FuncEnter();

    /* sum = H((K0 ^ ipad) || text). */
    ctx->func->finish(ctx->cryp_ctx, sum, hashlen);
    ctx->func->destroy(ctx->cryp_ctx);
    ctx->cryp_ctx = HI_NULL;

    /* H((K0 ^ opad)|| sum). */
    ctx->cryp_ctx = ctx->func->create(ctx->func->mode);
    if (HI_NULL == ctx->cryp_ctx)
    {
        HI_LOG_PrintFuncErr(ctx->func->create, 0);
        return HI_ERR_CIPHER_BUSY;
    }

    /* update(K0 ^ opad) */
    ret = ctx->func->update(ctx->cryp_ctx, ctx->hmac_opad,
        ctx->func->block_size, HASH_CHUNCK_SRC_LOCAL);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(ctx->func->update, ret);
        return ret;
    }

    /* update(sum) */
    ret = ctx->func->update(ctx->cryp_ctx, sum,
        ctx->func->size, HASH_CHUNCK_SRC_LOCAL);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(ctx->func->update, ret);
        return ret;
    }

    /* H */
    ret = ctx->func->finish(ctx->cryp_ctx, hash, hashlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(ctx->func->finish, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

#if defined(HASH_CMAC_SUPPORT)
static s32 kapi_hash_cbcmac_start(u32 *id)
{
    s32 ret = HI_FAILURE;
    u8 key[SYMC_KEY_SIZE] = {0};
    u8 iv[AES_IV_SIZE] = {0};

    HI_LOG_FuncEnter();

    /* allocate a aes channel */
    ret = kapi_symc_create(id, CRYP_CIPHER_TYPE_NORMAL);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_create, ret);
        return ret;
    }

    ret = kapi_symc_config(*id, CRYP_CIPHER_CA_TYPE_HCA << BITS_IN_BYTE | HI_TRUE,
                           CRYP_CIPHER_ALG_AES,
                           CRYP_CIPHER_WORK_MODE_CBC,
                           CRYP_CIPHER_BIT_WIDTH_128BIT,
                           CRYP_CIPHER_KEY_AES_128BIT,
                           0, key, HI_NULL,
                           iv, AES_IV_SIZE,
                           CIPHER_IV_CHANGE_ONE_PKG,
                           ADDR_NULL, 0, 0);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_config, ret);
        kapi_symc_destroy(*id);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 kapi_hash_cbcmac_update(u32 id, u8* in, u32 inlen)
{
    s32 ret = HI_FAILURE;
    u8 *msg = HI_NULL;

    HI_LOG_FuncEnter();

    msg = crypto_calloc(1, inlen);
    if (HI_NULL == msg)
    {
        HI_LOG_ERROR("error, malloc for cmac failed\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    CHECK_EXIT(crypto_copy_from_user(msg, in, inlen));
    CHECK_EXIT(ext_aes_cmac_update(id, msg, inlen));

exit__:
    if (HI_NULL != msg)
    {
        crypto_free(msg);
        msg = HI_NULL;
    }
    if (HI_SUCCESS != ret)
    {
        kapi_symc_destroy(id);;
    }

    HI_LOG_FuncExit();
    return ret;
}

static s32 kapi_hash_cbcmac_finish(u32 id, u8* mac, u32 *maclen)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = kapi_symc_getiv(id, mac, maclen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_symc_getiv, ret);
        kapi_symc_destroy(id);
        return ret;
    }

    kapi_symc_destroy(id);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
#endif

s32 kapi_hash_start(u32 *id, CRYP_CIPHER_HASH_TYPE_E type,
                    u8 *key, u32 keylen)
{
    s32 ret = HI_FAILURE;
    kapi_hash_ctx *ctx = HI_NULL;
    hash_mode mode = 0x00;
    u32 hmac = 0;
    u32 softHashId = 0;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == id);

    /* transform hash mode */
    ret = kapi_hash_mode_transform(type, &mode, &hmac);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(kapi_hash_mode_transform, ret);
        return ret;
    }

    KAPI_HASH_LOCK();

    /* Create hash channel */
    ret = kapi_hash_create(&softHashId);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, kapi_hash_create failed\n");
        HI_LOG_PrintFuncErr(kapi_hash_create, ret);
        KAPI_HASH_UNLOCK();
        return ret;
    }

    ctx = kapi_hash_get_ctx(softHashId);
    if (HI_NULL == ctx)
    {
        HI_LOG_ERROR("error, kapi_hash_get_ctx failed\n");
        HI_LOG_PrintFuncErr(kapi_hash_get_ctx, 0);
        ret = HI_ERR_CIPHER_BUSY;
        goto error1;
    }

    crypto_memset(ctx, sizeof(kapi_hash_ctx), 0, sizeof(kapi_hash_ctx));
    /* record owner */
    crypto_get_owner(&ctx->owner);
    ctx->hmac = hmac;

#if defined(HASH_CMAC_SUPPORT)
    if (HMAC_AESCBC == ctx->hmac)
    {
        KAPI_HASH_UNLOCK();

        ret = kapi_hash_cbcmac_start(&ctx->mac_id);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(kapi_hash_cbcmac_start, ret);
            kapi_hash_destroy(softHashId);
            return ret;
        }
        *id = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, softHashId);
        return HI_SUCCESS;
    }
#endif

    /* Clone the function from template of hash engine*/
    ctx->cryp_ctx = HI_NULL;
    ctx->func = cryp_get_hash(mode);
    if (HI_NULL == ctx->func)
    {
        HI_LOG_ERROR("error, cryp_get_hash failed\n");
        HI_LOG_PrintFuncErr(cryp_get_hash, 0);
        ret = HI_ERR_CIPHER_INVALID_PARA;
        goto error1;
    }

    if ((HI_NULL == ctx->func->create)
        || (HI_NULL == ctx->func->update)
        || (HI_NULL == ctx->func->finish)
        || (HI_NULL == ctx->func->destroy))
    {
        HI_LOG_ERROR("error, cryp hash func is HI_NULL\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_UNSUPPORTED);
        ret = HI_ERR_CIPHER_UNSUPPORTED;
        goto error1;
    }

    if (HMAC_HASH == ctx->hmac)
    {
        ret = kapi_hmac_start(ctx, key, keylen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("error, kapi_hmac_start failed\n");
            HI_LOG_PrintFuncErr(kapi_hmac_start, ret);
            goto error1;
        }
    }
    else
    {
        ctx->cryp_ctx = ctx->func->create(mode);
        if (HI_NULL == ctx->cryp_ctx)
        {
            HI_LOG_ERROR("error, hash context for hash engine failed\n");
            HI_LOG_PrintFuncErr(ctx->func->create, 0);
            ret = HI_ERR_CIPHER_BUSY;
            goto error1;
        }
    }

    *id = HI_HANDLE_MAKEHANDLE(HI_ID_CIPHER, 0, softHashId);

    KAPI_HASH_UNLOCK();

    HI_LOG_FuncExit();
    return HI_SUCCESS;

error1:
    kapi_hash_destroy(softHashId);

    KAPI_HASH_UNLOCK();

    HI_LOG_FuncExit();

    return ret;

}

s32 kapi_hash_update(u32 id, u8 *input, u32 length,
                     hash_chunk_src src)
{
    s32 ret = HI_FAILURE;
    kapi_hash_ctx *ctx = HI_NULL;
    u32 softHashId = 0;

    HI_LOG_FuncEnter();

    kapi_check_hash_handle(id);
    softHashId = HI_HANDLE_GET_CHNID(id);

    ctx = kapi_hash_get_ctx(softHashId);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx);
    HI_LOG_CHECK_PARAM(input > input + length); /* check overflow */

    CHECK_OWNER(&ctx->owner);

#if defined(HASH_CMAC_SUPPORT)
    if (HMAC_AESCBC == ctx->hmac)
    {
        ret = kapi_hash_cbcmac_update(ctx->mac_id, input, length);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(kapi_hash_cbcmac_update, ret);
            kapi_hash_destroy(softHashId);
            return ret;
        }
        return HI_SUCCESS;
    }
#endif

    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func->update);

    KAPI_HASH_LOCK();

    ret = ctx->func->update(ctx->cryp_ctx, input, length, src);

    /* release resource */
    if (HI_SUCCESS != ret)
    {
        ctx->func->destroy(ctx->cryp_ctx);
        ctx->cryp_ctx = HI_NULL;
        kapi_hash_destroy(softHashId);
        HI_LOG_PrintFuncErr(ctx->func->update, ret);
    }

    KAPI_HASH_UNLOCK();

    HI_LOG_FuncExit();

    return ret;
}

s32 kapi_hash_finish(u32 id, u8 *hash, u32 *hashlen)
{
    s32 ret = HI_FAILURE;
    kapi_hash_ctx *ctx = HI_NULL;
    u32 softHashId = 0;

    HI_LOG_FuncEnter();

    kapi_check_hash_handle(id);
    softHashId = HI_HANDLE_GET_CHNID(id);

    HI_LOG_CHECK_PARAM(HI_NULL == hash);
    HI_LOG_CHECK_PARAM(HI_NULL == hashlen);

    ctx = kapi_hash_get_ctx(softHashId);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx);

    CHECK_OWNER(&ctx->owner);

#if defined(HASH_CMAC_SUPPORT)
    if (HMAC_AESCBC == ctx->hmac)
    {
        ret = kapi_hash_cbcmac_finish(ctx->mac_id, hash, hashlen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(kapi_hash_cbcmac_finish, ret);
            kapi_hash_destroy(softHashId);
            return ret;
        }
        kapi_hash_destroy(softHashId);
        return HI_SUCCESS;
    }
#endif

    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func);
    HI_LOG_CHECK_PARAM(HI_NULL == ctx->func->destroy);

    KAPI_HASH_LOCK();

    if (HMAC_HASH == ctx->hmac)
    {
        ret = kapi_hmac_finish(ctx, hash, hashlen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(kapi_hmac_finish, ret);
        }
    }
    else
    {
        ret = ctx->func->finish(ctx->cryp_ctx, hash, hashlen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(ctx->func->finish, ret);
        }
    }

    /* release resource */
    ctx->func->destroy(ctx->cryp_ctx);
    ctx->cryp_ctx = HI_NULL;
    kapi_hash_destroy(softHashId);

    KAPI_HASH_UNLOCK();

    HI_LOG_FuncExit();

    return ret;
}

s32 kapi_hash_release(void)
{
    u32 i = 0;
    s32 ret = HI_FAILURE;
    kapi_hash_ctx *ctx = HI_NULL;
    crypto_owner owner;

    HI_LOG_FuncEnter();

    crypto_get_owner(&owner);

    HI_LOG_INFO("hash release owner 0x%x\n", owner);

    /* destroy the channel which are created by current user */
    for (i=0; i<HASH_SOFT_CHANNEL_MAX; i++)
    {
        if (HI_TRUE == hash_ctx[i].open)
        {
            ctx = kapi_hash_get_ctx(i);
            if (HI_NULL == ctx)
            {
                HI_LOG_PrintFuncErr(kapi_hash_get_ctx, HI_ERR_CIPHER_INVALID_POINT);
                return HI_ERR_CIPHER_INVALID_POINT;
            }
            if (0 == memcmp(&owner, &ctx->owner, sizeof(owner)))
            {
                HI_LOG_INFO("hash release chn %d\n", i);
                if ((HI_NULL != ctx->func)
                    && (HI_NULL != ctx->func->destroy)
                    && (HI_NULL != ctx->cryp_ctx))
                {
                    ctx->func->destroy(ctx->cryp_ctx);
                }
                ctx->cryp_ctx = HI_NULL;
                ret = kapi_hash_destroy(i);
                if (HI_SUCCESS != ret)
                {
                    HI_LOG_PrintFuncErr(kapi_hash_destroy, ret);
                    return ret;
                }
            }
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/** @}*/  /** <!-- ==== Structure Definition end ====*/
