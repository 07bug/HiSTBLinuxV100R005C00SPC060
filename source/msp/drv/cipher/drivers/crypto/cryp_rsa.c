/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : cryp_rsa.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "drv_srsa.h"
#include "cryp_rsa.h"
#include "cryp_trng.h"
#include "mbedtls/rsa.h"

/********************** Internal Structure Definition ************************/
/** \addtogroup      rsa */
/** @{*/  /** <!-- [rsa]*/

#define RSA_PKCS1_TYPE_MIN_PAD_LEN               (11)
#define RSA_BITS_1024                            1024
#define RSA_BITS_2048                            2048
#define RSA_BITS_3072                            3072
#define RSA_BITS_4096                            4096

/*! rsa mutex */
static crypto_mutex rsa_mutex;

#define KAPI_RSA_LOCK()   \
    ret = crypto_mutex_lock(&rsa_mutex);  \
    if (HI_SUCCESS != ret)        \
    {\
        HI_LOG_ERROR("error, rsa lock failed\n");\
        HI_LOG_FuncExit();\
        return ret;\
    }

#define KAPI_RSA_UNLOCK()   crypto_mutex_unlock(&rsa_mutex)

/*! \rsa rsa soft function */
extern int mbedtls_mpi_exp_mod_sw(mbedtls_mpi *X, const mbedtls_mpi *A,
                            const mbedtls_mpi *E, const mbedtls_mpi *N,
                            mbedtls_mpi *_RR);

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      rsa drivers*/
/** @{*/  /** <!-- [rsa]*/

void mbedtls_mpi_print(const mbedtls_mpi *X, const char *name)
{
#if 0
    int ret;
    size_t n;
    u8 buf[512] = {0};

    n = mbedtls_mpi_size(X);
    MBEDTLS_MPI_CHK(mbedtls_mpi_write_binary(X, buf, n));
    HI_PRINT_HEX(name, (u8*)buf, n);

cleanup:
    return;
#endif
}

#ifdef CHIP_RSA_SUPPORT
static s32 rsa_get_klen(unsigned long module_len, u32 *keylen, rsa_key_width *width)
{
    if (module_len <= RSA_KEY_LEN_1024)
    {
        *keylen = 128;
        *width = RSA_KEY_WIDTH_1024;
    }
    else if (module_len <= RSA_KEY_LEN_2048)
    {
        *keylen = 256;
        *width = RSA_KEY_WIDTH_2048;
    }
    else if (module_len <= RSA_KEY_LEN_4096)
    {
        *keylen = 512;
        *width = RSA_KEY_WIDTH_4096;
    }
    else
    {
        HI_LOG_ERROR("error, invalid key len %ld\n", module_len);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static s32 cryp_check_data(u8 *N, u8 *E, u8 *MC, u32 len)
{
    u32 i;

    /*MC > 0*/
    for (i = 0; i < len; i++)
    {
        if (0 < MC[i])
        {
            break;
        }
    }
    if (i >= len)
    {
        HI_LOG_ERROR("RSA M/C is zero, error!\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*MC < N*/
    for (i = 0; i < len; i++)
    {
        if (MC[i] < N[i])
        {
            break;
        }
    }
    if (i >= len)
    {
        HI_LOG_ERROR("RSA M/C is larger than N, error!\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /*E >= 1*/
    for (i = 0; i < len; i++)
    {
        if (E[i] > 0)
        {
            break;
        }
    }
    if (i >= len)
    {
        HI_LOG_ERROR("RSA D/E is zero, error!\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

static int cryp_ifep_rsa_exp_mod(mbedtls_mpi *X, const mbedtls_mpi *A,
                            const mbedtls_mpi *E, const mbedtls_mpi *N,
                            mbedtls_mpi *_RR)
{
    u32 module_len = 0;
    u8 *buf = HI_NULL;
    u8 *n = HI_NULL, *k = HI_NULL;
    u8 *in = HI_NULL, *out = HI_NULL;
    u32 keylen = 0;
    rsa_key_width width = 0;
    mbedtls_mpi _A;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    /* computes valid bits of N */
    module_len = mbedtls_mpi_size(N);

    ret = rsa_get_klen(module_len, &keylen, &width);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(rsa_get_klen, ret);
        return ret;
    }

    /* mallc buf to store n || k(e or d) || in || out */
    buf = crypto_malloc(keylen * 4);
    if (HI_NULL == buf)
    {
        HI_LOG_PrintFuncErr(crypto_malloc, HI_ERR_CIPHER_FAILED_MEM);
        return HI_ERR_CIPHER_FAILED_MEM;
    }

    /* zero */
    crypto_memset(buf, keylen * 4, 0, keylen * 4);

    n = buf;
    k = n + keylen;
    in = k + keylen;
    out = in + keylen;

    mbedtls_mpi_init(&_A);
    CHECK_EXIT(mbedtls_mpi_mod_mpi(&_A, A, N));

    /* read A, E, N */
    CHECK_EXIT(mbedtls_mpi_write_binary(&_A, in, keylen));
    CHECK_EXIT(mbedtls_mpi_write_binary(E, k, keylen));
    CHECK_EXIT(mbedtls_mpi_write_binary(N, n, keylen));

    /* key and data valid ?*/
    CHECK_EXIT(cryp_check_data(n, k, in, keylen));

    /* out = in ^ k mod n */
    ret = drv_ifep_rsa_exp_mod(n, k, in, out, width);
    if (HI_SUCCESS == ret)
    {
        /* write d */
        mbedtls_mpi_read_binary(X, out, keylen);
    }
exit__:

    mbedtls_mpi_free(&_A);
    crypto_free(buf);
    buf = HI_NULL;

    HI_LOG_FuncExit();

    return ret;
}
#endif

int mbedtls_mpi_exp_mod(mbedtls_mpi *X, const mbedtls_mpi *A,
                         const mbedtls_mpi *E,
                         const mbedtls_mpi *N,
                         mbedtls_mpi *_RR)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    KAPI_RSA_LOCK();

    HI_LOG_CHECK_PARAM(HI_NULL == X);
    HI_LOG_CHECK_PARAM(HI_NULL == A);
    HI_LOG_CHECK_PARAM(HI_NULL == E);
    HI_LOG_CHECK_PARAM(HI_NULL == N);

    mbedtls_mpi_print(A, "M");
    mbedtls_mpi_print(E, "E");
    mbedtls_mpi_print(N, "N");

#if defined(CHIP_IFEP_RSA_VER_V100)
    ret = cryp_ifep_rsa_exp_mod(X, A, E, N, _RR);
#else
    ret = mbedtls_mpi_exp_mod_sw(X, A, E, N, _RR);
#endif
    mbedtls_mpi_print(X, "X");

    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("rsa mpi_exp_mod failed, ret = 0x%x\n", ret);
    }

    KAPI_RSA_UNLOCK();

    HI_LOG_FuncExit();

    return ret;
}

int cryp_rsa_init(void)
{
    HI_LOG_FuncEnter();

    crypto_mutex_init(&rsa_mutex);

#if defined(CHIP_IFEP_RSA_VER_V100)
    {
        s32 ret = HI_FAILURE;

        ret = drv_rsa_init();
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_rsa_init, ret);
            return ret;
        }
    }
#endif

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void cryp_rsa_deinit(void)
{
#if defined(CHIP_IFEP_RSA_VER_V100)
    rsa_capacity capacity;

    drv_ifep_rsa_get_capacity(&capacity);

    /* recovery the rsa function of mbedtls */
    if (capacity.rsa)
    {
        drv_rsa_deinit();
    }
#endif

    crypto_mutex_destroy(&rsa_mutex);
}

int mbedtls_get_random(void *param, u8 *rand, size_t size)
{
    u32 i;
    u32 randnum = 0;

    for (i=0; i<size; i+=4)
    {
        cryp_trng_get_random(&randnum, -1);
        rand[i+3]   = (HI_U8)(randnum >> 24)& 0xFF;
        rand[i+2] = (HI_U8)(randnum >> 16)& 0xFF;
        rand[i+1] = (HI_U8)(randnum >> 8)& 0xFF;
        rand[i+0] = (HI_U8)(randnum) & 0xFF;
    }

    return HI_SUCCESS;
}

static s32 cryp_rsa_init_key(cryp_rsa_key *key, u32 *mode, mbedtls_rsa_context *rsa)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    mbedtls_mpi_init(&rsa->N);
    mbedtls_mpi_init(&rsa->E);
    mbedtls_mpi_init(&rsa->D);
    mbedtls_mpi_init(&rsa->P);
    mbedtls_mpi_init(&rsa->Q);
    mbedtls_mpi_init(&rsa->DP);
    mbedtls_mpi_init(&rsa->DQ);
    mbedtls_mpi_init(&rsa->Q);

    CHECK_EXIT(mbedtls_mpi_read_binary(&rsa->N, key->N, key->klen));
    rsa->len = key->klen;
    if (RSA_MIN_KEY_LEN > rsa->len || RSA_MAX_KEY_LEN < rsa->len)
    {
        HI_LOG_ERROR("RSA invalid keylen: 0x%x!\n", rsa->len);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        ret = HI_ERR_CIPHER_INVALID_PARA;
        goto exit__;
    }

    if (key->public)
    {
        CHECK_EXIT(mbedtls_mpi_read_binary(&rsa->E, (u8*)&key->e, WORD_WIDTH));
        *mode = MBEDTLS_RSA_PUBLIC;
    }
    else
    {
        if (HI_NULL != key->d) /* Non CRT */
        {
            CHECK_EXIT(mbedtls_mpi_read_binary(&rsa->D, key->d, key->klen));
            *mode = MBEDTLS_RSA_PRIVATE;
        }
        else /* CRT */
        {
            CHECK_EXIT(mbedtls_mpi_read_binary(&rsa->P, key->p, key->klen/2));
            CHECK_EXIT(mbedtls_mpi_read_binary(&rsa->Q, key->q, key->klen/2));
            CHECK_EXIT(mbedtls_mpi_read_binary(&rsa->DP, key->dP, key->klen/2));
            CHECK_EXIT(mbedtls_mpi_read_binary(&rsa->DQ, key->dQ, key->klen/2));
            CHECK_EXIT(mbedtls_mpi_read_binary(&rsa->QP, key->qP, key->klen/2));
            *mode = MBEDTLS_RSA_PRIVATE;
        }
    }

    HI_LOG_DEBUG("mode %d, e 0x%x\n", *mode, key->e);

    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:

    mbedtls_mpi_free(&rsa->N);
    mbedtls_mpi_free(&rsa->E);
    mbedtls_mpi_free(&rsa->D);
    mbedtls_mpi_free(&rsa->P);
    mbedtls_mpi_free(&rsa->Q);
    mbedtls_mpi_free(&rsa->DP);
    mbedtls_mpi_free(&rsa->DQ);
    mbedtls_mpi_free(&rsa->Q);

    HI_LOG_FuncExit();

    return ret;
}

static void cryp_rsa_deinit_key(mbedtls_rsa_context *rsa)
{
    HI_LOG_FuncEnter();

    mbedtls_mpi_free(&rsa->N);
    mbedtls_mpi_free(&rsa->E);
    mbedtls_mpi_free(&rsa->D);
    mbedtls_mpi_free(&rsa->P);
    mbedtls_mpi_free(&rsa->Q);
    mbedtls_mpi_free(&rsa->DP);
    mbedtls_mpi_free(&rsa->DQ);
    mbedtls_mpi_free(&rsa->Q);

    HI_LOG_FuncExit();
}

static s32 cryp_rsa_get_alg(u32 scheme, int *padding, int *hash_id, int *hashlen)
{
    switch(scheme)
    {
        case CRYP_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2:
        {
            *padding = 0x00;
            *hash_id = 0;
            *hashlen = 0;
            break;
        }
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5:
        {
            *padding = MBEDTLS_RSA_PKCS_V15;
            *hash_id = 0;
            *hashlen = 0;
            break;
        }
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1:
        {
            *padding = MBEDTLS_RSA_PKCS_V15;
            *hash_id = MBEDTLS_MD_SHA1;
            *hashlen = SHA1_RESULT_SIZE;
            break;
        }
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224:
        {
            *padding = MBEDTLS_RSA_PKCS_V15;
            *hash_id = MBEDTLS_MD_SHA224;
            *hashlen = SHA224_RESULT_SIZE;
            break;
        }
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256:
        {
            *padding = MBEDTLS_RSA_PKCS_V15;
            *hash_id = MBEDTLS_MD_SHA256;
            *hashlen = SHA256_RESULT_SIZE;
            break;
        }
#ifdef HI_PRODUCT_SHA512_SUPPORT
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384:
        {
            *padding = MBEDTLS_RSA_PKCS_V15;
            *hash_id = MBEDTLS_MD_SHA384;
            *hashlen = SHA384_RESULT_SIZE;
            break;
        }
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512:
        {
            *padding = MBEDTLS_RSA_PKCS_V15;
            *hash_id = MBEDTLS_MD_SHA512;
            *hashlen = SHA512_RESULT_SIZE;
            break;
        }
#endif
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
        {
            *padding = MBEDTLS_RSA_PKCS_V21;
            *hash_id = MBEDTLS_MD_SHA1;
            *hashlen = SHA1_RESULT_SIZE;
            break;
        }
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
        {
            *padding = MBEDTLS_RSA_PKCS_V21;
            *hash_id = MBEDTLS_MD_SHA224;
            *hashlen = SHA224_RESULT_SIZE;
            break;
        }
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
        {
            *padding = MBEDTLS_RSA_PKCS_V21;
            *hash_id = MBEDTLS_MD_SHA256;
            *hashlen = SHA256_RESULT_SIZE;
            break;
        }
#ifdef HI_PRODUCT_SHA512_SUPPORT
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
        {
            *padding = MBEDTLS_RSA_PKCS_V21;
            *hash_id = MBEDTLS_MD_SHA384;
            *hashlen = SHA384_RESULT_SIZE;
            break;
        }
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
        {
            *padding = MBEDTLS_RSA_PKCS_V21;
            *hash_id = MBEDTLS_MD_SHA512;
            *hashlen = SHA512_RESULT_SIZE;
            break;
        }
#endif
        default:
        {
            HI_LOG_ERROR("RSA padding mode error, mode = 0x%x.\n", scheme);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    HI_LOG_DEBUG("padding %d, hash_id %d, hashlen %d\n",*padding, *hash_id, *hashlen);

    return HI_SUCCESS;
}

/*PKCS #1: block type 0,1,2 message padding*/
/*************************************************
EB = 00 || BT || PS || 00 || D

PS_LEN >= 8, mlen < u32KeyLen - 11
*************************************************/
static s32 rsa_padding_add_pkcs1_type(mbedtls_rsa_context *rsa, u32 mode, u32 klen,
                                      u8  bt, u8 *in, u32 inlen, u8 *out)
{
    s32 ret = HI_FAILURE;
    u32 plen = 0;
    u8 *peb = HI_NULL;
    u32 i = 0;

    HI_LOG_FuncEnter();

    if (inlen > klen - RSA_PKCS1_TYPE_MIN_PAD_LEN)
    {
        HI_LOG_ERROR("klen is invalid.\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    peb = out;

    /* first byte is 0x00 */
    *(peb++) = 0;

    /* Private Key BT (Block Type) */
    *(peb++) = bt;

    /* The padding string PS shall consist of k-3-||D|| octets */
    plen = klen - 3 - inlen;
    switch(bt)
    {
        case 0x00:
        {
            /* For block type 00, the octets shall have value 00 */
            crypto_memset(peb, plen, 0x00, plen);
            break;
        }
        case 0x01:
        {
            /* for block type 01, they shall have value FF */
            crypto_memset(peb, plen, 0xFF, plen);
            break;
        }
        case 0x02:
        {
            /* for block type 02, they shall be pseudorandomly generated and nonzero. */
            (HI_VOID)mbedtls_get_random(HI_NULL, peb, plen);

            /* make sure nonzero */
            for (i= 0; i < plen; i++)
            {
                if (0x00 == peb[i])
                {
                    peb[i] = 0x01;
                }
            }
            break;
        }
        default:
        {
            HI_LOG_ERROR("BT(0x%x) is invalid.\n", plen);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    /* skip the padding string */
    peb += plen;

    /* set 0x00 follow PS */
    *(peb++) = 0x00;

    /* input data */
    crypto_memcpy(peb, inlen, in, inlen);

    if (MBEDTLS_RSA_PUBLIC == mode)
    {
        ret = mbedtls_rsa_public(rsa, out, out);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("rsa public failed.\n");
            HI_LOG_PrintFuncErr(mbedtls_rsa_public, ret);
            return ret;
        }
    }
    else
    {
        ret = mbedtls_rsa_private(rsa, HI_NULL, 0, out, out);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("rsa private failed.\n");
            HI_LOG_PrintFuncErr(mbedtls_rsa_private, ret);
            return ret;
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/*PKCS #1: block type 0,1,2 message padding*/
/*************************************************
EB = 00 || BT || PS || 00 || D

PS_LEN >= 8, mlen < u32KeyLen - 11
*************************************************/
static s32 rsa_padding_check_pkcs1_type(mbedtls_rsa_context *rsa, u32 klen, u32 mode,
                                        u8  bt, u8 *in, u32 inlen,
                                        u8 *out, u32 *outlen)
{
    s32 ret = HI_FAILURE;
    u8 *peb = HI_NULL;

    HI_LOG_FuncEnter();

    if (MBEDTLS_RSA_PUBLIC == mode)
    {
        ret = mbedtls_rsa_public(rsa, in, in);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("rsa public failed.\n");
            HI_LOG_PrintFuncErr(mbedtls_rsa_public, ret);
            return ret;
        }
    }
    else
    {
        ret = mbedtls_rsa_private(rsa, HI_NULL, 0, in, in);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("rsa private failed.\n");
            HI_LOG_PrintFuncErr(mbedtls_rsa_private, ret);
            return ret;
        }
    }

    *outlen = 0x00;
    peb = in;

    /* first byte must be 0x00 */
    if (0x00 != *peb)
    {
        HI_LOG_ERROR("EB[0] != 0x00.\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    peb++;

    /* Private Key BT (Block Type) */
    if(*peb != bt)
    {
        HI_LOG_ERROR("EB[1] != BT(0x%x).\n", bt);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    peb++;

    switch(bt)
    {
    case 0x00:
        /* For block type 00, the octets shall have value 00 */
        for (; peb < in + inlen - 1; peb++)
        {
            if ((*peb == 0x00) && (*(peb+1) != 0))
            {
                break;
            }
        }
        break;
    case 0x01:
        /* For block type 01, the octets shall have value FF */
        for (; peb < in + inlen - 1; peb++)
        {
            if(*peb == 0xFF)
            {
                continue;
            }
            else if (*peb == 0x00)
            {
                break;
            }
            else
            {
                peb = in + inlen - 1;
                break;
            }
        }
        break;
    case 0x02:
        /* for block type 02, they shall be pseudorandomly generated and nonzero. */
        for (; peb < in + inlen - 1; peb++)
        {
            if (0x00 == *peb)
            {
                break;
            }
        }
        break;
    default:
        HI_LOG_ERROR("BT(0x%x) is invalid.\n", bt);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    if (peb >= (in + inlen - 1))
    {
        HI_LOG_ERROR("PS Error.\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    /* skip 0x00 after PS */
    peb++;

    /* get payload data */
    *outlen = in + klen - peb;
    crypto_memcpy(out, klen, peb, *outlen);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

static s32 rsa_no_padding(mbedtls_rsa_context *rsa, u32 klen, u32 mode,
                                       u8 *in, u32 inlen, u8 *out)
{
    s32 ret = HI_FAILURE;
    u8 data[RSA_MAX_KEY_LEN] = {0};

    HI_LOG_FuncEnter();

    if (inlen != klen)
    {
        HI_LOG_ERROR("input length %d invalid.\n", inlen);
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }
    crypto_memcpy(data + klen - inlen, RSA_MAX_KEY_LEN, in, inlen);

    if (MBEDTLS_RSA_PUBLIC == mode)
    {
        ret = mbedtls_rsa_public(rsa, data, out);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("rsa public failed.\n");
            HI_LOG_PrintFuncErr(mbedtls_rsa_public, ret);
            return ret;
        }
    }
    else
    {
        ret = mbedtls_rsa_private(rsa, HI_NULL, 0, data, out);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_ERROR("rsa private failed, ret = %d.\n", ret);
            HI_LOG_PrintFuncErr(mbedtls_rsa_private, ret);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 cryp_rsa_encrypt(cryp_rsa_key *key, CRYP_CIPHER_RSA_ENC_SCHEME_E scheme,
                     u8 *in, u32 inlen, u8 *out, u32 *outlen)
{
    s32 ret = HI_FAILURE;
    u32 mode = 0;
    int padding = 0;
    int hash_id = 0;
    int hashlen = 0;
    u32 bt = 0;
    mbedtls_rsa_context rsa;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == key);
    HI_LOG_CHECK_PARAM(HI_NULL == in);
    HI_LOG_CHECK_PARAM(HI_NULL == out);
    HI_LOG_CHECK_PARAM(HI_NULL == outlen);
    HI_LOG_CHECK_PARAM(RSA_KEY_LEN_4096 < key->klen);
    HI_LOG_CHECK_PARAM(inlen > key->klen);

    ret = cryp_rsa_get_alg(scheme, &padding, &hash_id, &hashlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, cryp_rsa_get_alg failed.\n");
        HI_LOG_PrintErrCode(ret);
        return ret;
    }

    mbedtls_rsa_init(&rsa, padding, hash_id);

    ret = cryp_rsa_init_key(key, &mode, &rsa);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, cryp_rsa_init_key failed.\n");
        HI_LOG_PrintErrCode(ret);
        return ret;
    }

    switch(scheme)
    {
        case CRYP_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        {
            ret = rsa_no_padding(&rsa, key->klen, mode, in, inlen, out);
            break;
        }
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2:
        {
            bt = scheme - CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0;
            ret = rsa_padding_add_pkcs1_type(&rsa, mode, key->klen, bt, in, inlen, out);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_ERROR("error, rsa add pkcs1_type failed, ret = %d.\n", ret);
                HI_LOG_PrintFuncErr(rsa_padding_add_pkcs1_type, ret);
                ret = HI_ERR_CIPHER_FAILED_ENCRYPT;
            }
            break;
        }
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
#ifdef HI_PRODUCT_SHA512_SUPPORT
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
#endif
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5:
        {
            ret = mbedtls_rsa_pkcs1_encrypt(&rsa, mbedtls_get_random,
                HI_NULL, mode, inlen, in, out);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_ERROR("error, rsa pkcs1 encrypt failed, ret = %d", ret);
                HI_LOG_PrintFuncErr(rsa_padding_add_pkcs1_type, ret);
                ret = HI_ERR_CIPHER_FAILED_ENCRYPT;
            }
            break;
        }
        default:
        {
            HI_LOG_ERROR("RSA padding mode error, mode = 0x%x.\n", scheme);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            ret = HI_ERR_CIPHER_INVALID_PARA;
            break;
        }
    }

    if (HI_SUCCESS == ret)
    {
        *outlen = key->klen;
    }

    cryp_rsa_deinit_key(&rsa);

    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("rsa encrypt failed, scheme %d, ret = 0x%x\n", scheme, ret);
    }

    HI_LOG_FuncExit();

    return ret;
}

s32 cryp_rsa_decrypt(cryp_rsa_key *key, CRYP_CIPHER_RSA_ENC_SCHEME_E scheme,
                     u8 *in, u32 inlen, u8 *out, u32 *outlen)
{
    s32 ret = HI_FAILURE;
    u32 mode = 0;
    int padding = 0;
    int hash_id = 0;
    int hashlen = 0;
    u32 bt = 0;
    size_t outsize = 0;
    mbedtls_rsa_context rsa;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == key);
    HI_LOG_CHECK_PARAM(HI_NULL == in);
    HI_LOG_CHECK_PARAM(HI_NULL == out);
    HI_LOG_CHECK_PARAM(HI_NULL == outlen);
    HI_LOG_CHECK_PARAM(RSA_KEY_LEN_4096 < key->klen);
    HI_LOG_CHECK_PARAM(inlen != key->klen);

    ret = cryp_rsa_get_alg(scheme, &padding, &hash_id, &hashlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, cryp_rsa_sign_get_alg failed");
        HI_LOG_PrintFuncErr(cryp_rsa_get_alg, ret);
        return ret;
    }

    mbedtls_rsa_init(&rsa, padding, hash_id);

    ret = cryp_rsa_init_key(key, &mode, &rsa);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, cryp_rsa_init_key failed");
        HI_LOG_PrintFuncErr(cryp_rsa_init_key, ret);
        return ret;
    }

    switch(scheme)
    {
        case CRYP_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        {
            ret = rsa_no_padding(&rsa, key->klen, mode, in, inlen, out);
            *outlen = key->klen;
            if (HI_SUCCESS != ret)
            {
                HI_LOG_PrintFuncErr(rsa_no_padding, ret);
            }
            break;
        }
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2:
        {
            bt = scheme - CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0;
            ret = rsa_padding_check_pkcs1_type(&rsa, key->klen, mode, bt, in, inlen, out, outlen);
            if (HI_SUCCESS != ret)
            {
                HI_LOG_ERROR("error, rsa check pkcs1 type failed, ret = %d", ret);
                HI_LOG_PrintFuncErr(rsa_padding_check_pkcs1_type, ret);
                ret = HI_ERR_CIPHER_FAILED_DECRYPT;
            }
            break;
        }
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
#ifdef HI_PRODUCT_SHA512_SUPPORT
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
#endif
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5:
        {
            ret = mbedtls_rsa_pkcs1_decrypt(&rsa, mbedtls_get_random,
                HI_NULL, mode, &outsize, in, out, key->klen);
            *outlen = (u32)outsize;
            if (HI_SUCCESS != ret)
            {
                HI_LOG_ERROR("error, rsa pkcs1 decrypt failed, ret = %d", ret);
                HI_LOG_PrintFuncErr(mbedtls_rsa_pkcs1_decrypt, ret);
                ret = HI_ERR_CIPHER_FAILED_DECRYPT;
            }
            break;
        }
        default:
        {
            HI_LOG_ERROR("RSA padding mode error, mode = 0x%x.\n", scheme);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            ret = HI_ERR_CIPHER_INVALID_PARA;
            break;
        }
    }

    cryp_rsa_deinit_key(&rsa);

    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("rsa decrypt failed, scheme %d, ret = 0x%x\n", scheme, ret);
    }

    HI_LOG_FuncExit();

    return ret;
}

s32 cryp_rsa_sign_hash(cryp_rsa_key *key, CRYP_CIPHER_RSA_SIGN_SCHEME_E scheme,
                        u8 *in, u32 inlen, u8 *out, u32 *outlen, u32 saltlen)
{
    s32 ret = HI_FAILURE;
    u32 mode = 0;
    int padding = 0;
    int hash_id = 0;
    int hashlen = 0;
    mbedtls_rsa_context rsa;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == key);
    HI_LOG_CHECK_PARAM(HI_NULL == in);
    HI_LOG_CHECK_PARAM(HI_NULL == out);
    HI_LOG_CHECK_PARAM(HI_NULL == outlen);
    HI_LOG_CHECK_PARAM(RSA_KEY_LEN_4096 < key->klen);
    HI_LOG_CHECK_PARAM(inlen > key->klen);

    //HI_PRINT_HEX("HASH", in, inlen);

    ret = cryp_rsa_get_alg(scheme, &padding, &hash_id, &hashlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, cryp_rsa_sign_get_alg failed");
        HI_LOG_PrintFuncErr(cryp_rsa_get_alg, ret);
        return ret;
    }

    mbedtls_rsa_init(&rsa, padding, hash_id);

    ret = cryp_rsa_init_key(key, &mode, &rsa);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, cryp_rsa_init_key failed");
        HI_LOG_PrintFuncErr(cryp_rsa_init_key, ret);
        return ret;
    }

//    HI_PRINT_HEX("in", in, hashlen);

    ret = mbedtls_rsa_pkcs1_sign(&rsa, mbedtls_get_random, HI_NULL,
        mode, hash_id, hashlen, in, out);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, rsa_pkcs1 sign failed, ret = %d\n", ret);
        HI_LOG_PrintFuncErr(mbedtls_rsa_pkcs1_sign, ret);
        cryp_rsa_deinit_key(&rsa);
        ret = HI_ERR_CIPHER_RSA_SIGN;
        HI_LOG_ERROR("rsa sign hash failed, scheme %d, ret = 0x%x\n", scheme, ret);
        return ret;
    }

    *outlen = key->klen;
    cryp_rsa_deinit_key(&rsa);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 cryp_rsa_verify_hash(cryp_rsa_key *key, CRYP_CIPHER_RSA_SIGN_SCHEME_E scheme,
                        u8 *hash, u32 hlen, u8 *sign, u32 signlen, u32 saltlen)
{
    s32 ret = HI_FAILURE;
    int padding = 0;
    int hash_id = 0;
    int hashlen = 0;
    u32 mode = 0;
    mbedtls_rsa_context rsa;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == key);
    HI_LOG_CHECK_PARAM(HI_NULL == hash);
    HI_LOG_CHECK_PARAM(HI_NULL == sign);
    HI_LOG_CHECK_PARAM(RSA_KEY_LEN_4096 < key->klen);
    HI_LOG_CHECK_PARAM(signlen > key->klen);

    //HI_PRINT_HEX("HASH", hash, hlen);

    ret = cryp_rsa_get_alg(scheme, &padding, &hash_id, &hashlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, cryp_rsa_sign_get_alg failed");
        HI_LOG_PrintFuncErr(cryp_rsa_get_alg, ret);
        return ret;
    }

    mbedtls_rsa_init(&rsa, padding, hash_id);

    ret = cryp_rsa_init_key(key, &mode, &rsa);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error, cryp_rsa_init_key failed, ret = %d\n", ret);
        HI_LOG_PrintFuncErr(cryp_rsa_init_key, ret);
        return ret;
    }

    ret = mbedtls_rsa_pkcs1_verify(&rsa, mbedtls_get_random, HI_NULL,
        mode, hash_id, hashlen, hash, sign);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_ERROR("error,  rsa pkcs1 verify failed, ret = %d\n", ret);
        HI_LOG_PrintFuncErr(mbedtls_rsa_pkcs1_verify, ret);
        cryp_rsa_deinit_key(&rsa);
        ret = HI_ERR_CIPHER_RSA_VERIFY;
        HI_LOG_ERROR("rsa verify hash failed, scheme %d, ret = 0x%x\n", scheme, ret);
        return ret;
    }

    cryp_rsa_deinit_key(&rsa);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 cryp_rsa_gen_key(u32 numbits, u32 exponent, cryp_rsa_key *key)
{
    s32 ret = HI_FAILURE;
    mbedtls_rsa_context rsa;

    HI_LOG_FuncEnter();

    mbedtls_rsa_init(&rsa, 0, 0);
    ret = mbedtls_rsa_gen_key(&rsa, mbedtls_get_random, 0, numbits, exponent);
    if (HI_SUCCESS == ret)
    {
        key->klen = mbedtls_mpi_size(&rsa.N);
        key->e = exponent;
        CHECK_EXIT(mbedtls_mpi_write_binary(&rsa.N, key->N, key->klen));
        CHECK_EXIT(mbedtls_mpi_write_binary(&rsa.D, key->d, key->klen));
        CHECK_EXIT(mbedtls_mpi_write_binary(&rsa.P, key->p, key->klen / 2));
        CHECK_EXIT(mbedtls_mpi_write_binary(&rsa.Q, key->q, key->klen / 2));
        CHECK_EXIT(mbedtls_mpi_write_binary(&rsa.DP, key->dP, key->klen / 2));
        CHECK_EXIT(mbedtls_mpi_write_binary(&rsa.DQ, key->dQ, key->klen / 2));
        CHECK_EXIT(mbedtls_mpi_write_binary(&rsa.QP, key->qP, key->klen / 2));
    }
    else
    {
        HI_LOG_PrintFuncErr(mbedtls_rsa_gen_key, ret);
        ret = HI_ERR_CIPHER_ILLEGAL_KEY;
        HI_LOG_ERROR("rsa gen key error, ret = 0x%x!\n", ret);
        mbedtls_rsa_free(&rsa);
        return ret;
    }
    mbedtls_rsa_free(&rsa);
    HI_LOG_FuncExit();
    return HI_SUCCESS;

exit__:

    HI_LOG_ERROR("rsa gen key failed, ret = 0x%x\n", ret);
    mbedtls_rsa_free(&rsa);
    return ret;
}

/** @}*/  /** <!-- ==== API Code end ====*/
