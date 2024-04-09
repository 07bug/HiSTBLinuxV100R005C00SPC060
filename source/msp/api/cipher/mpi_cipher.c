
/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : mpi_cipher.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#include "mpi_cipher.h"

#define SM2_DECRYPT_ENC_ZERO    (0x04)

/*************************** Internal Structure Definition *******************/
/** \addtogroup      symc */
/** @{*/  /** <!-- [mpi]*/


/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      symc */
/** @{*/  /** <!-- [mpi]*/

s32 mpi_symc_create(u32 *hd, CRYP_CIPHER_TYPE_E type)
{
    s32 ret = HI_FAILURE;
    symc_create_t create = {0};

    HI_LOG_FuncEnter();

    crypto_memset(&create, sizeof(create), 0, sizeof(create));

    create.type = type;
    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_CREATEHANDLE, &create);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    *hd = create.id;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_symc_destroy(u32 id)
{
    symc_destroy_t destroy = {0};
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    crypto_memset(&destroy, sizeof(destroy), 0, sizeof(destroy));

    destroy.id = id;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_DESTROYHANDLE, &destroy);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_symc_config(u32 id,
                    u32 hard_key,
                    CRYP_CIPHER_ALG_E enAlg,
                    CRYP_CIPHER_WORK_MODE_E enWorkMode,
                    CRYP_CIPHER_BIT_WIDTH_E enBitWidth,
                    CRYP_CIPHER_KEY_LENGTH_E enKeyLen,
                    CRYP_CIPHER_SM1_ROUND_E sm1_round_num,
                    u8 *fkey, u8 *skey, u32 keylen,
                    u8 *iv, u32 ivlen, u32 iv_usage,
                    compat_addr aad, u32 alen, u32 tlen)
{
    symc_config_t config;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    crypto_memset(&config, sizeof(config), 0, sizeof(config));

    config.id = id;
    config.hard_key = hard_key;
    config.alg = enAlg;
    config.mode = enWorkMode;
    config.klen = enKeyLen;
    config.iv_usage = iv_usage;
    config.sm1_round_num = sm1_round_num;
    config.aad = aad;
    config.alen = alen;
    config.tlen = tlen;
    config.ivlen = ivlen;
    config.width = enBitWidth;

    HI_LOG_DEBUG("iv len %d, enKeyLen 0x%x\n", ivlen, enKeyLen);

    if (HI_NULL != fkey)
    {
        crypto_memcpy(config.fkey, sizeof(config.fkey), fkey, keylen);

        if (CRYP_CIPHER_ALG_SM1 == enAlg)
        {
            /* fkey contains EK and AK for SM1, here Copy the AK */
            crypto_memcpy(config.fkey + SYMC_SM1_SK_SIZE, SYMC_SM1_SK_SIZE,
                fkey + SYMC_SM1_SK_SIZE, SYMC_SM1_SK_SIZE);
        }
    }
    if (HI_NULL != iv)
    {
        crypto_memcpy(config.iv, sizeof(config.iv), iv, ivlen);
    }
    if (HI_NULL != skey)
    {
        crypto_memcpy(config.skey, sizeof(config.skey), skey, keylen);
    }

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_CONFIGHANDLE, &config);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_symc_get_config(u32 id, CRYP_CIPHER_CTRL_S *ctrl)
{
    symc_get_config_t get_config;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    crypto_memset(&get_config, sizeof(get_config), 0, sizeof(get_config));

    get_config.id = id;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_GET_CONFIG, &get_config);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    crypto_memcpy(ctrl, sizeof(CRYP_CIPHER_CTRL_S), &get_config.ctrl, sizeof(CRYP_CIPHER_CTRL_S));

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_symc_crypto(u32 id, compat_addr input,
                      compat_addr output, u32 length,
                      u32 operation)
{
    symc_encrypt_t encrypt;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    crypto_memset(&encrypt, sizeof(encrypt), 0, sizeof(encrypt));

    encrypt.id = id;
    encrypt.input = input;
    encrypt.output = output;
    encrypt.length = length;
    encrypt.operation = operation;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_ENCRYPT, &encrypt);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_symc_crypto_multi(u32 id, void *pkg, u32 pkg_num, u32 operation)
{
    symc_encrypt_multi_t encrypt_multi;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    crypto_memset(&encrypt_multi, sizeof(encrypt_multi), 0, sizeof(encrypt_multi));

    encrypt_multi.id = id;
    ADDR_VIA(encrypt_multi.pkg) = pkg;
    encrypt_multi.pkg_num = pkg_num;
    encrypt_multi.operation = operation;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_ENCRYPTMULTI, &encrypt_multi);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_symc_aes_cmac(u32 id, u8 *in, u32 inlen, u8 *mac, u32 last)
{
    symc_cmac_t cmac;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    crypto_memset(&cmac, sizeof(cmac), 0, sizeof(cmac));

    cmac.id = id;
    ADDR_VIA(cmac.in) = in;
    cmac.inlen = inlen;
    cmac.last = last;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_CMAC, &cmac);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    if (HI_TRUE == last)
    {
        crypto_memcpy(mac, AES_BLOCK_SIZE, cmac.mac, AES_BLOCK_SIZE);
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

#ifdef HI_PRODUCT_AEAD_SUPPORT
s32 mpi_aead_get_tag(u32 id, u8 *tag, u32 *taglen)
{
    s32 ret = HI_FAILURE;
    aead_tag_t aead_tag;

    HI_LOG_FuncEnter();

    crypto_memset(&aead_tag, sizeof(aead_tag), 0, sizeof(aead_tag));

    aead_tag.id = id;
    aead_tag.taglen = *taglen;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_GETTAG, &aead_tag);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    crypto_memcpy(tag, *taglen, aead_tag.tag, aead_tag.taglen);
    *taglen = aead_tag.taglen;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
#endif

s32 mpi_hash_start(u32 *id, CRYP_CIPHER_HASH_TYPE_E type,
                    u8 *key, u32 keylen)
{
    s32 ret = HI_FAILURE;
    hash_start_t start;

    HI_LOG_FuncEnter();

    crypto_memset(&start, sizeof(start), 0, sizeof(start));

    start.id = 0;
    start.type = type;
    start.keylen = keylen;
    ADDR_VIA(start.key) = key;

    ret =  CRYPTO_IOCTL(CRYPTO_CMD_HASH_START, &start);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    *id = start.id;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_hash_update(u32 id, u8 *input, u32 length, hash_chunk_src src)
{
    s32 ret = HI_FAILURE;
    hash_update_t update;

    HI_LOG_FuncEnter();

    crypto_memset(&update, sizeof(update), 0, sizeof(update));

    update.id = id;
    ADDR_VIA(update.input) = input;
    update.length = length;
    update.src = src;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_HASH_UPDATE, &update);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_hash_finish(u32 id, u8 *hash, u32 *hashlen)
{
    s32 ret = HI_FAILURE;
    hash_finish_t finish;

    HI_LOG_FuncEnter();

    crypto_memset(&finish, sizeof(finish), 0, sizeof(finish));

    finish.id = id;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_HASH_FINISH, &finish);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    crypto_memcpy(hash, HASH_RESULT_MAX_SIZE, finish.hash, finish.hashlen);
    *hashlen = finish.hashlen;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_rsa_encrypt(cryp_rsa_key *key,
                    CRYP_CIPHER_RSA_ENC_SCHEME_E enScheme,
                    u8 *in, u32 inlen,
                    u8 *out, u32 *outlen)
{
    s32 ret = HI_FAILURE;
    rsa_info_t rsa_info;

    HI_LOG_FuncEnter();

    crypto_memset(&rsa_info, sizeof(rsa_info_t), 0, sizeof(rsa_info_t));

    ADDR_VIA(rsa_info.N) = key->N;
    ADDR_VIA(rsa_info.d) = key->d;
    ADDR_VIA(rsa_info.p) = key->p;
    ADDR_VIA(rsa_info.q) = key->q;
    ADDR_VIA(rsa_info.dP) = key->dP;
    ADDR_VIA(rsa_info.dQ) = key->dQ;
    ADDR_VIA(rsa_info.qP) = key->qP;

    rsa_info.e = key->e;
    rsa_info.public = key->public;
    rsa_info.klen = key->klen;
    rsa_info.enScheme = enScheme;
    ADDR_VIA(rsa_info.in) = in;
    rsa_info.inlen = inlen;
    ADDR_VIA(rsa_info.out) = out;
    rsa_info.outlen = key->klen;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_RSA_ENC, &rsa_info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    *outlen = rsa_info.outlen;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_rsa_decrypt(cryp_rsa_key *key,
                    CRYP_CIPHER_RSA_ENC_SCHEME_E enScheme,
                    u8 *in, u32 inlen,
                    u8 *out, u32 *outlen)
{
    s32 ret = HI_FAILURE;
    rsa_info_t rsa_info;

    HI_LOG_FuncEnter();

    crypto_memset(&rsa_info, sizeof(rsa_info), 0, sizeof(rsa_info));

    ADDR_VIA(rsa_info.N) = key->N;
    ADDR_VIA(rsa_info.d) = key->d;
    ADDR_VIA(rsa_info.p) = key->p;
    ADDR_VIA(rsa_info.q) = key->q;
    ADDR_VIA(rsa_info.dP) = key->dP;
    ADDR_VIA(rsa_info.dQ) = key->dQ;
    ADDR_VIA(rsa_info.qP) = key->qP;

    rsa_info.e = key->e;
    rsa_info.public = key->public;
    rsa_info.klen = key->klen;
    rsa_info.enScheme = enScheme;
    ADDR_VIA(rsa_info.in) = in;
    rsa_info.inlen = inlen;
    ADDR_VIA(rsa_info.out) = out;
    rsa_info.outlen = key->klen;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_RSA_DEC, &rsa_info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    *outlen = rsa_info.outlen;
    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_rsa_sign_hash(cryp_rsa_key *key,
                      CRYP_CIPHER_RSA_SIGN_SCHEME_E enScheme,
                      u8* hash, u32 hlen,
                      u8 *sign, u32 *signlen)
{
    s32 ret = HI_FAILURE;
    rsa_info_t rsa_info;

    HI_LOG_FuncEnter();

    crypto_memset(&rsa_info, sizeof(rsa_info), 0, sizeof(rsa_info));

    ADDR_VIA(rsa_info.N) = key->N;
    ADDR_VIA(rsa_info.d) = key->d;
    ADDR_VIA(rsa_info.p) = key->p;
    ADDR_VIA(rsa_info.q) = key->q;
    ADDR_VIA(rsa_info.dP) = key->dP;
    ADDR_VIA(rsa_info.dQ) = key->dQ;
    ADDR_VIA(rsa_info.qP) = key->qP;

    rsa_info.e = key->e;
    rsa_info.public = key->public;
    rsa_info.klen = key->klen;
    rsa_info.enScheme = enScheme;
    ADDR_VIA(rsa_info.in) = hash;
    rsa_info.inlen = hlen;
    ADDR_VIA(rsa_info.out) = sign;
    rsa_info.outlen = key->klen;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_RSA_SIGN, &rsa_info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    *signlen = rsa_info.outlen;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_rsa_verify_hash(cryp_rsa_key *key,
                       CRYP_CIPHER_RSA_SIGN_SCHEME_E enScheme,
                       u8 *hash, u32 hlen,
                       u8 *sign, u32 signlen)
{
    s32 ret = HI_FAILURE;
    rsa_info_t rsa_info;

    HI_LOG_FuncEnter();

    crypto_memset(&rsa_info, sizeof(rsa_info_t), 0, sizeof(rsa_info_t));

    ADDR_VIA(rsa_info.N) = key->N;

    rsa_info.e = key->e;
    rsa_info.public = key->public;
    rsa_info.klen = key->klen;
    rsa_info.enScheme = enScheme;
    ADDR_VIA(rsa_info.in) = sign;
    rsa_info.inlen = signlen;
    ADDR_VIA(rsa_info.out) = hash;
    rsa_info.outlen = hlen;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_RSA_VERIFY, &rsa_info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_rsa_compute_ctr(cryp_rsa_key *key)
{
    s32 ret = HI_FAILURE;
    rsa_info_t rsa_info;

    HI_LOG_FuncEnter();

    crypto_memset(&rsa_info, sizeof(rsa_info), 0, sizeof(rsa_info));

    ADDR_VIA(rsa_info.N) = key->N;
    ADDR_VIA(rsa_info.p) = key->p;
    ADDR_VIA(rsa_info.q) = key->q;
    ADDR_VIA(rsa_info.dP) = key->dP;
    ADDR_VIA(rsa_info.dQ) = key->dQ;
    ADDR_VIA(rsa_info.qP) = key->qP;
    rsa_info.e = key->e;
    rsa_info.public = key->public;
    rsa_info.klen = key->klen;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_RSA_COMPUTE_CRT, &rsa_info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_rsa_gen_key(cryp_rsa_key *key)
{
    s32 ret = HI_FAILURE;
    rsa_info_t rsa_info;

    HI_LOG_FuncEnter();

    crypto_memset(&rsa_info, sizeof(rsa_info), 0, sizeof(rsa_info));

    ADDR_VIA(rsa_info.N) = key->N;
    ADDR_VIA(rsa_info.d) = key->d;
    ADDR_VIA(rsa_info.p) = key->p;
    ADDR_VIA(rsa_info.q) = key->q;
    ADDR_VIA(rsa_info.dP) = key->dP;
    ADDR_VIA(rsa_info.dQ) = key->dQ;
    ADDR_VIA(rsa_info.qP) = key->qP;
    rsa_info.e = key->e;
    rsa_info.public = key->public;
    rsa_info.klen = key->klen;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_RSA_GEN_KEY, &rsa_info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_hdcp_operation(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, u8 *hostkey,
                       u8 *in, u8 *out, u32 len, u32 operation)
{
#ifdef HI_PLATFORM_TYPE_LINUX
    s32 ret = HI_FAILURE;
    hdcp_key_t hdcp_key;

    HI_LOG_FuncEnter();

    crypto_memset(&hdcp_key, sizeof(hdcp_key), 0, sizeof(hdcp_key));

    hdcp_key.keysel = keysel;
    hdcp_key.ramsel = ramsel;
    hdcp_key.len = len;
    hdcp_key.decrypt = operation;

    if (HI_NULL != hostkey)
    {
        crypto_memcpy(hdcp_key.hostkey, sizeof(hdcp_key.hostkey), hostkey,
            HDCP_ROOT_KEY_SIZE_IN_WORD * 4);
    }

    ADDR_VIA(hdcp_key.in) = in;
    ADDR_VIA(hdcp_key.out) = out;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_HDCP_ENCRYPT, &hdcp_key);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
#else
    HI_LOG_ERROR("Unsupport HDCP\n");
    return HI_FAILURE;
#endif
}

s32 mpi_trng_get_random(u8 *randnum, u32 size, u32 timeout)
{
    s32 ret = HI_FAILURE;
    trng_t trng;

    HI_LOG_FuncEnter();

    crypto_memset(&trng, sizeof(trng), 0, sizeof(trng));

    ADDR_VIA(trng.randnum) = randnum;
    trng.size    = size;
    trng.timeout = timeout;
    ret = CRYPTO_IOCTL(CRYPTO_CMD_TRNG, &trng);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

#ifdef HI_PRODUCT_SM2_SUPPORT
s32 mpi_sm2_sign(u32 d[SM2_LEN_IN_WROD],
                  u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                  u8 *id, u16 idlen,
                  u8 *msg, u32 msglen, hash_chunk_src src,
                  u8 r[SM2_LEN_IN_BYTE], u8 s[SM2_LEN_IN_BYTE])
{
    s32 ret = HI_FAILURE;
    sm2_sign_t sign;

    HI_LOG_FuncEnter();

    crypto_memset(&sign, sizeof(sign), 0, sizeof(sign));

    crypto_memcpy(sign.d,  SM2_LEN_IN_BYTE, d,  SM2_LEN_IN_BYTE);
    crypto_memcpy(sign.px, SM2_LEN_IN_BYTE, px, SM2_LEN_IN_BYTE);
    crypto_memcpy(sign.py, SM2_LEN_IN_BYTE, py, SM2_LEN_IN_BYTE);
    ADDR_VIA(sign.id) = id;
    sign.idlen = idlen;
    ADDR_VIA(sign.msg) = msg;
    sign.msglen = msglen;
    sign.src = src;
    sign.magic_num = CRYPTO_MAGIC_NUM;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SM2_SIGN, &sign);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    crypto_memcpy(r, SM2_LEN_IN_BYTE, sign.r, SM2_LEN_IN_BYTE);
    crypto_memcpy(s, SM2_LEN_IN_BYTE, sign.s, SM2_LEN_IN_BYTE);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_sm2_verify(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                    u8 *id, u16 idlen, u8 *msg, u32 msglen, hash_chunk_src src,
                    u8 r[SM2_LEN_IN_BYTE], u8 s[SM2_LEN_IN_BYTE])
{
    s32 ret = HI_FAILURE;
    sm2_verify_t verify;

    HI_LOG_FuncEnter();

    crypto_memset(&verify, sizeof(verify), 0, sizeof(verify));

    crypto_memcpy(verify.px, SM2_LEN_IN_BYTE, px, SM2_LEN_IN_BYTE);
    crypto_memcpy(verify.py, SM2_LEN_IN_BYTE, py, SM2_LEN_IN_BYTE);
    ADDR_VIA(verify.id) = id;
    verify.idlen = idlen;
    ADDR_VIA(verify.msg) = msg;
    verify.msglen = msglen;
    crypto_memcpy(verify.r, SM2_LEN_IN_BYTE, r, SM2_LEN_IN_BYTE);
    crypto_memcpy(verify.s, SM2_LEN_IN_BYTE, s, SM2_LEN_IN_BYTE);
    verify.src =src;
    verify.magic_num = CRYPTO_MAGIC_NUM;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SM2_VERIFY, &verify);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_sm2_encrypt(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                     u8 *msg, u32 msglen, u8 *enc, u32 *enclen)
{
    s32 ret = HI_FAILURE;
    sm2_encrypt_t encrypt;

    HI_LOG_FuncEnter();

    crypto_memset(&encrypt, sizeof(encrypt), 0, sizeof(encrypt));

    crypto_memcpy(encrypt.px, SM2_LEN_IN_BYTE, px, SM2_LEN_IN_BYTE);
    crypto_memcpy(encrypt.py, SM2_LEN_IN_BYTE, py, SM2_LEN_IN_BYTE);
    ADDR_VIA(encrypt.msg) = msg;
    ADDR_VIA(encrypt.enc) = enc;
    encrypt.msglen = msglen;
    encrypt.keylen = SM2_LEN_IN_WROD;
    encrypt.magic_num = CRYPTO_MAGIC_NUM;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SM2_ENCRYPT, &encrypt);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    *enclen = encrypt.enclen;


    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_sm2_decrypt(u32 d[SM2_LEN_IN_WROD], u8 *enc,
                    u32 enclen, u8 *msg, u32 *msglen)
{
    s32 ret = HI_FAILURE;
    sm2_decrypt_t decrypt;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == enc);

    crypto_memset(&decrypt, sizeof(decrypt), 0, sizeof(decrypt));

    crypto_memcpy(decrypt.d, SM2_LEN_IN_BYTE, d, SM2_LEN_IN_BYTE);
    ADDR_VIA(decrypt.enc) = enc;
    ADDR_VIA(decrypt.msg) = msg;
    decrypt.enclen = enclen;
    decrypt.keylen = SM2_LEN_IN_WROD;
    decrypt.magic_num = CRYPTO_MAGIC_NUM;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SM2_DECRYPT, &decrypt);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    *msglen = decrypt.msglen;

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_sm2_gen_key(u32 d[SM2_LEN_IN_WROD], u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD])
{
    s32 ret = HI_FAILURE;
    sm2_key_t key;

    HI_LOG_FuncEnter();

    crypto_memset(&key, sizeof(key), 0, sizeof(key));
    key.keylen = SM2_LEN_IN_WROD;
    key.magic_num = CRYPTO_MAGIC_NUM;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SM2_GEN_KEY, &key);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    crypto_memcpy(d, SM2_LEN_IN_BYTE, key.d, SM2_LEN_IN_BYTE);
    crypto_memcpy(px, SM2_LEN_IN_BYTE, key.px, SM2_LEN_IN_BYTE);
    crypto_memcpy(py, SM2_LEN_IN_BYTE, key.py, SM2_LEN_IN_BYTE);

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
#endif

#ifdef HI_PRODUCT_CENC_SUPPORT
s32 mpi_cenc_decrypt(u32 id, u8 *key, u8 *iv, u32 inphy, u32 outphy,
                     u32 length, u32 firstoffset,
                     CRYP_CIPHER_SUBSAMPLE_S *subsample, u32 subsample_num)
{
    s32 ret = HI_FAILURE;
    cenc_info_t cenc;

    HI_LOG_FuncEnter();

    crypto_memset(&cenc, sizeof(cenc), 0, sizeof(cenc));

    cenc.id = id;
    crypto_memcpy(&cenc.key, AES_IV_SIZE, key, AES_IV_SIZE);
    crypto_memcpy(&cenc.iv, AES_IV_SIZE, iv, AES_IV_SIZE);
    cenc.inphy = inphy;
    cenc.outphy = outphy;
    cenc.length = length;
    cenc.firstoffset = firstoffset;
    ADDR_VIA(cenc.subsample) = subsample;
    cenc.subsample_num = subsample_num;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_CENC, &cenc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_cenc_decrypt_ex(u32 id, u8 *key, u32 oddkey, u32 inphy, u32 outphy,
                     u32 length, u32 firstoffset,
                     CRYP_CIPHER_SUBSAMPLE_EX_S *subsample, u32 subsample_num)
{
    s32 ret = HI_FAILURE;
    cenc_info_t cenc;

    HI_LOG_FuncEnter();

    crypto_memset(&cenc, sizeof(cenc), 0, sizeof(cenc));

    cenc.id = id;
    crypto_memcpy(&cenc.key, AES_IV_SIZE, key, AES_IV_SIZE);
    cenc.inphy = inphy;
    cenc.outphy = outphy;
    cenc.length = length;
    cenc.oddkey = oddkey;
    cenc.firstoffset = firstoffset;
    ADDR_VIA(cenc.subsample) = subsample;
    cenc.subsample_num = subsample_num;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_CENC_EX, &cenc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
#endif

#ifdef HI_PRODUCT_ECC_SUPPORT
static void mpi_ecc_get_info(ecc_param_t *ecc, ecc_info_t *info)
{
    ADDR_VIA(info->p) = ecc->p;
    ADDR_VIA(info->b) = ecc->b;
    ADDR_VIA(info->a) = ecc->a;
    ADDR_VIA(info->Gx) = ecc->Gx;
    ADDR_VIA(info->Gy) = ecc->Gy;
    ADDR_VIA(info->n) = ecc->n;
    info->ksize = ecc->ksize;
}

s32 mpi_ecdh_compute_key(ecc_param_t *ecc, u8 *prikey, u8 *px, u8 *py, u8 *sharekey)
{
    s32 ret = HI_FAILURE;
    ecc_info_t info;

    HI_LOG_FuncEnter();

    crypto_memset(&info, sizeof(info), 0, sizeof(info));

    mpi_ecc_get_info(ecc, &info);
    ADDR_VIA(info.d) = prikey;
    ADDR_VIA(info.Px) = px;
    ADDR_VIA(info.Py) = py;
    ADDR_VIA(info.msg) = sharekey;
    info.magic_num = CRYPTO_MAGIC_NUM;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_ECDH_COMPUTE_KEY, &info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_ecc_gen_key(ecc_param_t *ecc, u8 *inkey, u8 *outkey, u8 *px, u8 *py)
{
    s32 ret = HI_FAILURE;
    ecc_info_t info;

    HI_LOG_FuncEnter();

    crypto_memset(&info, sizeof(info), 0, sizeof(info));

    mpi_ecc_get_info(ecc, &info);
    ADDR_VIA(info.msg) = inkey;
    ADDR_VIA(info.d) = outkey;
    ADDR_VIA(info.Px) = px;
    ADDR_VIA(info.Py) = py;
    info.magic_num = CRYPTO_MAGIC_NUM;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_ECC_GEN_KEY, &info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_ecdsa_sign_hash(ecc_param_t *ecc, u8 *prikey, u8 *hash, u32 hlen, u8 *r, u8 *s)
{
    s32 ret = HI_FAILURE;
    ecc_info_t info;

    HI_LOG_FuncEnter();

    crypto_memset(&info, sizeof(info), 0, sizeof(info));

    mpi_ecc_get_info(ecc, &info);
    ADDR_VIA(info.d) = prikey;
    ADDR_VIA(info.msg) = hash;
    info.mlen = hlen;
    ADDR_VIA(info.r) = r;
    ADDR_VIA(info.s) = s;
    info.magic_num = CRYPTO_MAGIC_NUM;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_ECDSA_SIGN, &info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_ecdsa_verify_hash(ecc_param_t *ecc, u8 *px, u8 *py, u8 *hash, u32 hlen, u8 *r, u8 *s)
{
    s32 ret = HI_FAILURE;
    ecc_info_t info;

    HI_LOG_FuncEnter();

    crypto_memset(&info, sizeof(info), 0, sizeof(info));

    mpi_ecc_get_info(ecc, &info);
    ADDR_VIA(info.Px) = px;
    ADDR_VIA(info.Py) = py;
    ADDR_VIA(info.msg) = hash;
    info.mlen = hlen;
    ADDR_VIA(info.r) = r;
    ADDR_VIA(info.s) = s;
    info.magic_num = CRYPTO_MAGIC_NUM;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_ECDSA_VERIFY, &info);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
#endif

#ifdef HI_PLATFORM_TYPE_TEE
s32 mpi_symc_crypto_multi_asyn(u32 id, void *pkg, u32 pkg_num, u32 operation)
{
    symc_encrypt_multi_t encrypt_multi;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    crypto_memset(&encrypt_multi, sizeof(encrypt_multi), 0, sizeof(encrypt_multi));

    encrypt_multi.id = id;
    ADDR_VIA(encrypt_multi.pkg) = pkg;
    encrypt_multi.pkg_num = pkg_num;
    encrypt_multi.operation = operation;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_ENCRYPTMULTI_ASYN, &encrypt_multi);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_symc_crypto_waitdone(u32 id, u32 timeout)
{
    s32 ret = HI_FAILURE;
    symc_waitdone_t waitdone;

    HI_LOG_FuncEnter();

    crypto_memset(&waitdone, sizeof(waitdone), 0, sizeof(waitdone));

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SYMC_WAIT_DONE, &waitdone);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return ret;
}

s32 mpi_pbkdf_hmac256(u8 *password, u32 plen, u8 *salt, u32 slen,
                      u32 iteration_count, u32 outlen, u8 *out)
{
    s32 ret = HI_FAILURE;
    pbkdf_hmac256_t pfkdf;

    HI_LOG_FuncEnter();

    crypto_memset(&pfkdf, sizeof(pfkdf), 0, sizeof(pfkdf));

    ADDR_VIA(pfkdf.password) = password;
    ADDR_VIA(pfkdf.salt) = salt;
    ADDR_VIA(pfkdf.output) = out;
    pfkdf.plen = plen;
    pfkdf.slen = slen;
    pfkdf.iteration_count = iteration_count;
    pfkdf.outlen = outlen;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_PBKDF2, &pfkdf);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_set_usage_rule(u32 id, CRYP_CIPHER_UR_S *pstCipherUR)
{
    usage_rule_t usagerule;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    crypto_memset(&usagerule, sizeof(usagerule), 0, sizeof(usagerule));

    usagerule.id = id;
    crypto_memcpy(&usagerule.stCipherUR,sizeof(usagerule.stCipherUR),pstCipherUR,sizeof(CRYP_CIPHER_UR_S));

    ret = CRYPTO_IOCTL(CRYPTO_CMD_SETUSAGERULE, &usagerule);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

s32 mpi_crypto_self_test(u32 cmd, void *param, u32 size)
{
    s32 ret = HI_FAILURE;
    test_t test;

    HI_LOG_FuncEnter();

    crypto_memset(&test, sizeof(test), 0, sizeof(test));

    test.cmd = cmd;
    ADDR_VIA(test.param) = param;
    test.size = size;

    ret = CRYPTO_IOCTL(CRYPTO_CMD_TEST, &test);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYPTO_IOCTL, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}
#endif

/** @}*/  /** <!-- ==== API Code end ====*/
