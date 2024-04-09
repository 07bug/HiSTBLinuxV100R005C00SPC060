/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : kapi_rsa.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_rsa.h"

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      rsa */
/** @{*/  /** <!-- [kapi]*/

/**
\brief   Kapi Init.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_rsa_init(void)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = cryp_rsa_init();
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_rsa_init, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/**
\brief   Kapi Deinitialize.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_rsa_deinit(void)
{
    HI_LOG_FuncEnter();

    cryp_rsa_deinit();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_rsa_encrypt(cryp_rsa_key *key,
                     CRYP_CIPHER_RSA_ENC_SCHEME_E enScheme,
                     u8 *in, u32 inlen,
                     u8 *out, u32 *outlen)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = cryp_rsa_encrypt(key, enScheme, in, inlen, out, outlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_rsa_encrypt, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_rsa_decrypt(cryp_rsa_key *key,
                    CRYP_CIPHER_RSA_ENC_SCHEME_E enScheme,
                    u8 *in, u32 inlen,
                    u8 *out, u32 *outlen)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = cryp_rsa_decrypt(key, enScheme, in, inlen, out, outlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_rsa_decrypt, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_rsa_sign_hash(cryp_rsa_key *key,
                          CRYP_CIPHER_RSA_SIGN_SCHEME_E enScheme,
                          u8* hash, u32 hlen,
                          u8 *sign, u32 *signlen)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = cryp_rsa_sign_hash(key, enScheme, hash, hlen, sign, signlen, hlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_rsa_sign_hash, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_rsa_verify_hash(cryp_rsa_key *key,
                          CRYP_CIPHER_RSA_SIGN_SCHEME_E enScheme,
                          u8* hash, u32 hlen,
                          u8 *sign, u32 signlen)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    ret = cryp_rsa_verify_hash(key, enScheme, hash, hlen, sign, signlen, hlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_rsa_verify_hash, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 kapi_rsa_gen_key(u32 numbits, u32 exponent, cryp_rsa_key *key)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == key);
    HI_LOG_CHECK_PARAM(HI_NULL == key->p);
    HI_LOG_CHECK_PARAM(HI_NULL == key->q);
    HI_LOG_CHECK_PARAM(HI_NULL == key->dP);
    HI_LOG_CHECK_PARAM(HI_NULL == key->dQ);
    HI_LOG_CHECK_PARAM(HI_NULL == key->qP);
    HI_LOG_CHECK_PARAM(RSA_KEY_BITWIDTH_4096 * BITS_IN_BYTE < numbits);

    if((RSA_KEY_EXPONENT_VALUE1 != exponent) && (RSA_KEY_EXPONENT_VALUE2 != exponent))
    {
        HI_LOG_ERROR("RSA compute crt params, e error\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    ret = cryp_rsa_gen_key(numbits, exponent, key);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_rsa_gen_key, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/** @}*/  /** <!-- ==== Structure Definition end ====*/
