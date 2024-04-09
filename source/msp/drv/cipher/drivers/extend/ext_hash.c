/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : ext_hash.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_hash.h"
#include "mbedtls/md.h"

#define HASH_MAX_BUFFER_SIZE    0x10000 /* 64K */

#if defined(SOFT_SHA1_SUPPORT) \
    || defined(SOFT_SHA256_SUPPORT) \
    || defined(SOFT_SHA512_SUPPORT)

void * mbedtls_hash_create(hash_mode mode)
{
    mbedtls_md_type_t md_type;
    const mbedtls_md_info_t *info;
    mbedtls_md_context_t *ctx = HI_NULL;

    HI_LOG_FuncEnter();

    /* convert to mebdtls type */
    md_type = MBEDTLS_MD_SHA1 + (mode - HASH_MODE_SHA1);

    info = mbedtls_md_info_from_type(md_type);
    if (HI_NULL == info)
    {
        HI_LOG_ERROR("error, invalid hash mode %d\n", mode);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_NULL;
    }

    ctx = crypto_malloc(sizeof(mbedtls_md_context_t));
    if (HI_NULL == ctx)
    {
        HI_LOG_ERROR("malloc hash context buffer failed!");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
        return HI_NULL;
    }
    crypto_memset(ctx, sizeof(mbedtls_md_context_t), 0, sizeof(mbedtls_md_context_t));

    mbedtls_md_init(ctx);
    mbedtls_md_setup(ctx, info, HI_FALSE);
    mbedtls_md_starts(ctx);

    HI_LOG_FuncExit();

    return ctx;
}

s32 mbedtls_hash_update(void *ctx, u8 *chunk, u32 chunkLen, hash_chunk_src src)
{
    u8 *ptr = HI_NULL;
    s32 ret = HI_FAILURE;
    mbedtls_md_context_t *md = ctx;
    u32 offset = 0, length = 0;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ctx);

    if (0x00 == chunkLen)
    {
        return HI_SUCCESS;
    }

    if (HASH_CHUNCK_SRC_USER == src)
    {
        ptr = crypto_malloc(HASH_MAX_BUFFER_SIZE);
        if (HI_NULL == ptr)
        {
            HI_LOG_ERROR("malloc hash chunk buffer failed, chunkLen 0x%x\n!", chunkLen);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
            return HI_ERR_CIPHER_FAILED_MEM;
        }

        while (offset < chunkLen)
        {
            length = chunkLen - offset;
            if (HASH_MAX_BUFFER_SIZE < length)
            {
                length = HASH_MAX_BUFFER_SIZE;
            }
            if (crypto_copy_from_user(ptr, chunk + offset, length))
            {
                HI_LOG_ERROR("copy hash chunk from user failed!");
                HI_LOG_PrintErrCode(HI_ERR_CIPHER_FAILED_MEM);
                ret = HI_ERR_CIPHER_FAILED_MEM;
                goto exit;
            }
            ret = mbedtls_md_update(md, ptr, length);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_PrintFuncErr(mbedtls_md_update, ret);
                break;
            }
            crypto_msleep(1);
            offset   += length;
        }
    }
    else
    {
        ret = mbedtls_md_update(md, chunk, chunkLen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(mbedtls_md_update, ret);
        }
    }

exit:
    if (HI_NULL != ptr)
    {
        crypto_free(ptr);
        ptr = HI_NULL;
    }

    HI_LOG_FuncExit();

    return ret;
}

s32 mbedtls_hash_finish(void *ctx,  void *hash, u32 *hashlen)
{
    mbedtls_md_context_t *md = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ctx);

    mbedtls_md_finish(md, hash);

    *hashlen = mbedtls_md_get_size(md->md_info);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mbedtls_hash_destory(void *ctx)
{
    mbedtls_md_context_t *md = ctx;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == ctx);

    mbedtls_md_free(md);
    crypto_free(ctx);
    ctx = HI_NULL;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

#endif // End of SOFT_AES_CCM_GCM_SUPPORT
