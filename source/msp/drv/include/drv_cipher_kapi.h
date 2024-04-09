/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     :drv_cipher_kapi.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/

#ifndef __TEE_DRV_CIPHER_KAPI_H__
#define __TEE_DRV_CIPHER_KAPI_H__

#include "drv_cipher_osal.h"

#ifdef __cplusplus
extern "C" {
#endif    /* __cplusplus */

/******************************* API Declaration *****************************/
/** \addtogroup      crypto */
/** @{ */  /** <!--[link]*/

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      crypto*/
/** @{*/  /** <!-- [link]*/

/**
\brief   Kapi Init.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_symc_init(void);

/**
\brief   Kapi Deinit.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_symc_deinit(void);

/**
\brief   Kapi release.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_symc_release(void);

/**
\brief   Create symc handle.
\param[in]  id The channel number.
\param[in]  uuid The user identification.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_symc_create(u32 *id, CRYP_CIPHER_TYPE_E type);

/**
\brief   Destroy symc handle.
\param[in]  id The channel number.
\param[in]  uuid The user identification.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_symc_destroy(u32 id);

/**
\brief  set work params.
* \param[in]  id The channel number.
* \param[in]  hard_key whether use the hard key or not.
* \param[in]  alg The symmetric cipher algorithm.
* \param[in]  mode The symmetric cipher mode.
* \param[in]  sm1_round_num The round number of sm1.
* \param[in]  fkey first  key buffer, defualt
* \param[in]  skey second key buffer, expand
* \param[in]  klen The key length.
* \param[in]  aad      Associated Data
* \param[in]  alen     Associated Data Length
* \param[in]  tlen     Tag length
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_symc_config(u32 id,
                    u32 hard_key,
                    CRYP_CIPHER_ALG_E enAlg,
                    CRYP_CIPHER_WORK_MODE_E enWorkMode,
                    CRYP_CIPHER_BIT_WIDTH_E enBitWidth,
                    CRYP_CIPHER_KEY_LENGTH_E enKeyLen,
                    CRYP_CIPHER_SM1_ROUND_E sm1_round_num,
                    u8 *fkey, u8 *skey,
                    u8 *iv, u32 ivlen, u32 iv_usage,
                    compat_addr aad, u32 alen, u32 tlen);

/**
\brief  get work params.
* \param[in]  id The channel number.
* \param[out] ctrl infomation.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_symc_get_config(u32 id, CRYP_CIPHER_CTRL_S *ctrl);

/**
\brief  get work params without lock.
* \param[in]  id The channel number.
* \param[out] ctrl infomation.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_symc_unlock_get_config(u32 id, CRYP_CIPHER_CTRL_S *ctrl);

/**
 * \brief          SYMC  buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param[in]  id The channel number.
 * \param input    buffer holding the input data
 * \param output   buffer holding the output data
 * \param length   length of the input data
 * \param operation  decrypt or encrypt
 * \param oddkey     odd key or not
 *
 * \return         0 if successful
 */
s32 kapi_symc_crypto(u32 id, compat_addr input,
                      compat_addr output, u32 length,
                      u32 operation, u32 oddkey, u32 last);

/**
 * \brief          SYMC multiple buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param[in]  id The channel number.
 * \param pkg       Buffer of package infomation
 * \param pkg_num   Number of package infomation
 * \param operation  decrypt or encrypt
 * \param last       last or not
 *
 * \return         0 if successful
 */
s32 kapi_symc_crypto_multi(u32 id, void *pkg,
                            u32 pkg_num, u32 operation, u32 last);

/**
 * \brief          SYMC multiple buffer encryption/decryption.
 *
 * Note: Due to the nature of aes you should use the same key schedule for
 * both encryption and decryption.
 *
 * \param[in]  id The channel number.
 * \param pkg       Buffer of package infomation
 * \param pkg_num   Number of package infomation
 * \param operation  decrypt or encrypt
 * \param last       last or not
 *
 * \return         0 if successful
 */
s32 kapi_symc_crypto_multi_asyn(u32 id, void *pkg,
                            u32 pkg_num, u32 operation, u32 last);

/**
 * \brief          SYMC wait done.
 *
 * \param[in]  id The channel number.
 *
 * \return         0 if successful
 */
s32 kapi_symc_crypto_waitdone(u32 id, u32 timeout);

/**
 * \brief          SYMC multiple buffer encryption/decryption.
 * \param[in]  id The channel number.
 * \param[in]  tag tag data of CCM/GCM
 *
 * \return         0 if successful
 */
s32 kapi_aead_get_tag(u32 id, u32 tag[AEAD_TAG_SIZE_IN_WORD], u32 *taglen);

/**
\brief   Kapi Init.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_hash_init(void);

/**
\brief   Kapi Deinit.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_hash_deinit(void);

/**
 * \brief          HASH context setup.
 *
 *
 * \param[out] id The channel number.
 * \param[in] type    Hash type
 * \param[in] key     hmac key
 * \param[in] keylen  hmac key length
 *
 * \return         0 if successful
 */
s32 kapi_hash_start(u32 *id, CRYP_CIPHER_HASH_TYPE_E type,
                    u8 *key, u32 keylen);

/**
 * \brief          HASH process buffer.
 *
 * \param[in]  id The channel number.
 * \param[in] input    buffer holding the input data
 * \param[in] length   length of the input data
 * \param[in] src      source of hash message
 *
 * \return         0 if successful
 */
s32 kapi_hash_update(u32 id, u8 *input, u32 length,
                     hash_chunk_src src);

/**
 * \brief          HASH final digest.
 *
 * \param[in]  id The channel number.
 * \param[out] hash    buffer holding the hash data
 * \param[out] hashlen length of the hash data
 *
 * \return         0 if successful
 */
s32 kapi_hash_finish(u32 id, u8 *hash, u32 *hashlen);

/**
\brief   hash release.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_hash_release(void);

/**
\brief   Kapi Init.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_rsa_init(void);

/**
\brief   Kapi Deinitialize.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_rsa_deinit(void);

/**
* \brief RSA encryption a plaintext with a RSA private key.
*
* \param[in] key:       rsa key struct.
* \param[in] enScheme:  rsa encrypt/decrypt scheme.
* \param[in] in£º   input data to be encryption
* \param[out] inlen:  length of input data to be encryption
* \param[out] out£º   output data of encryption
* \param[out] outlen: length of output data to be encryption
* \retval ::HI_SUCCESS  Call this API successful
* \retval ::HI_FAILURE  Call this API fails.
*/
s32 kapi_rsa_encrypt(cryp_rsa_key *key,
                     CRYP_CIPHER_RSA_ENC_SCHEME_E enScheme,
                     u8 *in, u32 inlen,
                     u8 *out, u32 *outlen);

/**
* \brief RSA decryption a ciphertext with a RSA public key.
*
* \param[in] key:       rsa key struct.
* \param[in] enScheme:  rsa encrypt/decrypt scheme.
* \param[in] in£º   input data to be encryption
* \param[in] inlen:  length of input data to be encryption
* \param[out] out£º   output data to be encryption
* \param[out] outlen: length of output data to be encryption
* \retval ::HI_SUCCESS  Call this API successful
* \retval ::HI_FAILURE  Call this API fails.
*/
s32 kapi_rsa_decrypt(cryp_rsa_key *key,
                    CRYP_CIPHER_RSA_ENC_SCHEME_E enScheme,
                    u8 *in, u32 inlen,
                    u8 *out, u32 *outlen);

/**
* \brief RSA signature a context with appendix, where a signer¡¯s RSA private key is used.
*
* \param[in] key:       rsa key struct.
* \param[in] enScheme:  rsa signature/verify scheme.
* \param[in] in£º    input data to be encryption
* \param[in] inlen:  length of input data to be encryption
* \param[in] hash:   hash value of context,if NULL, let hash = Hash(context) automatically
* \param[out] out£º   output data to be encryption
* \param[out] outlen: length of output data to be encryption
* \param[in]  src      source of hash message
* \param[in]  uuid uuid The user identification.
* \retval ::HI_SUCCESS  Call this API successful
* \retval ::HI_FAILURE  Call this API fails.
*/
s32 kapi_rsa_sign_hash(cryp_rsa_key *key,
                       CRYP_CIPHER_RSA_SIGN_SCHEME_E enScheme,
                       u8* hash, u32 hlen,
                       u8 *sign, u32 *signlen);

/**
* \brief RSA verify a ciphertext with a RSA public key.
*
* \param[in]  key_info:   encryption struct.
* \param[in]  in£º   input data to be encryption
* \param[out] inlen:  length of input data to be encryption
* \param[in]  hash:   hash value of context,if NULL, let hash = Hash(context) automatically
* \param[out] out£º   output data to be encryption
* \param[out] outlen: length of output data to be encryption
* \param[in]  src      source of hash message
* \retval ::HI_SUCCESS  Call this API successful
* \retval ::HI_FAILURE  Call this API fails.
*/
s32 kapi_rsa_verify_hash(cryp_rsa_key *key,
                         CRYP_CIPHER_RSA_SIGN_SCHEME_E enScheme,
                        u8 *hash, u32 hlen,
                        u8 *sign, u32 signlen);

/**
* \brief RSA gen key.
*
* \param[in]  numbits£º   bits num of N
* \param[in]  exponent£º  e
* \param[in]  key_info:   encryption struct.
* \retval ::HI_SUCCESS  Call this API successful
* \retval ::HI_FAILURE  Call this API fails.
*/
s32 kapi_rsa_gen_key(u32 numbits, u32 exponent, cryp_rsa_key *key);

/**
* \brief set iv.
*
* \param[in]  hCIHandle:   handle.
* \param[in]  iv£º   iv data
* \param[in]  inlen:  length of input data to be encryption
* \retval ::HI_SUCCESS  Call this API successful
* \retval ::HI_FAILURE  Call this API fails.
*/
s32 kapi_symc_setiv(u32 hCIHandle, u8 *iv, u32 ivlen);

/**
* \brief get iv.
*
* \param[in]  handle:   handle.
* \param[in]  iv£º   iv data
* \param[in]  inlen:  length of input data to be encryption
* \retval ::HI_SUCCESS  Call this API successful
* \retval ::HI_FAILURE  Call this API fails.
*/
s32 kapi_symc_getiv(u32 handle, u8 *iv, u32 *ivlen);

/**
* \brief get mode.
*
* \param[in]  handle:   handle.
* \retval ::HI_SUCCESS  Call this API successful
* \retval ::HI_FAILURE  Call this API fails.
*/
CRYP_CIPHER_WORK_MODE_E kapi_symc_getmode(u32 handle);

/**
\brief  HDCP encrypt/decrypt use AES-CBC, IV is all zero.
\param[in]  keysel Hdcp root key sel.
\param[in]  ramsel hdmi ram sel.
\param[in]  in The input data.
\param[out] out The input data.
\param[out] len The input data length, must align with 16.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_hdcp_encrypt(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, u32 *hostkey,
                 u32 *in, u32 *out, u32 len, u32 decrypt);

/**
\brief get rand number.
\param[out]  randnum rand number.
\param[in]   timeout time out.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_trng_get_random( u32 *randnum, u32 timeout);

/**
\brief get rand bytes.
\param[out]  randnum rand bytes.
\param[in]   size size of rand byte.
\param[in]   timeout time out.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_trng_get_rand_byte( u8 *randbyte, u32 size, u32 timeout);

/**
\brief   Kapi Init.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_sm2_init(void);

/**
\brief   Kapi Deinitialize.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_sm2_deinit(void);

/**
\brief SM2 signature a context with appendix, where a signer¡¯s SM2 private key is used.
\param d[in]     sm2 private key
\param px[in]    sm2 x public key
\param py[in]    sm2 y public key
\param id[in]    sm2 user id
\param idlen[in] length of sm2 user id
\param msg[in]   mesaage to be sign
\param msglen[in] length of mesaage to be sign
\param src[in]    source of hash message
\param r[out]      sm2 sign result of r
\param s[out]      sm2 sign result of s
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_sm2_sign(u32 d[SM2_LEN_IN_WROD],
                  u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                  u8 *id, u16 idlen,
                  u8 *msg, u32 msglen, hash_chunk_src src,
                  u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD]);
/**
\brief SM2 signature verification a context with appendix, where a signer¡¯s SM2 public key is used.
\param px[in]    sm2 x public key
\param py[in]    sm2 y public key
\param id[in]    sm2 user id
\param idlen[in] length of sm2 user id
\param msg[in]   mesaage to be sign
\param msglen[in] length of mesaage to be sign
\param src[in]    source of hash message
\param r[in]      sm2 sign result of r
\param s[in]      sm2 sign result of s
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_sm2_verify(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                    u8 *id, u16 idlen, u8 *msg, u32 msglen, hash_chunk_src src,
                    u32 r[SM2_LEN_IN_WROD], u32 s[SM2_LEN_IN_WROD]);

/**
\brief SM2 encryption a plaintext with a RSA public key.
\param px[in]    sm2 x public key
\param py[in]    sm2 y public key
\param msg[in]   mesaage to be encryption
\param msglen[in] length of mesaage to be encryption
\param enc[out]    encryption mesaage
\param enclen[out] length of encryption mesaage
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_sm2_encrypt(u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD],
                     u8 *msg, u32 msglen, u8 *enc, u32 *enclen);
/**
\brief SM2 decryption a plaintext with a RSA public key.
\param d[in]     sm2 private key
\param enc[out]    mesaage to be decryption
\param enclen[out] length of mesaage to be decryption
\param msg[in]     decryption mesaage
\param msglen[in]  length of decryption mesaage
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_sm2_decrypt(u32 d[SM2_LEN_IN_WROD], u8 *enc,
                     u32 enclen, u8 *msg, u32 *msglen);

/**
\brief Generate a SM2 key pair..
\param d[in]     sm2 private key
\param px[in]    sm2 x public key
\param py[in]    sm2 y public key
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_sm2_gen_key(u32 d[SM2_LEN_IN_WROD],
    u32 px[SM2_LEN_IN_WROD], u32 py[SM2_LEN_IN_WROD]);


/**
\brief CENC decryption a ciphertext.
\param id[in] Cipher handle
\param key[in] for cipher decryption
\param iv[in] for cipher decryption
\param inphy[in] non-secure Physical address of the source data
\param outphy[in] secure Physical address of the target data
\param length[in] Length of the decrypted data
\param firstoffset[in] offset of the first encrypt block data
\retval HI_SUCCESS  Call this API succussful.
\retval HI_FAILURE  Call this API fails.
\see \n
N/A
*/
s32 kapi_symc_cenc_decrypt(u32 id,
                    u8 *key,
                    u8 *iv,
                    u32 oddkey,
                    u32 inputphy,
                    u32 outputphy,
                    u32 bytelength,
                    u32 firstoffset,
                    void *subsample,
                    u32 number);

#if defined(HI_PLATFORM_TYPE_TEE)
/**
\brief Set usage rule.
\param[in]  id The channel number.
\param[in] pstCipherUR usage rule information.
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API fails.
*/
s32 kapi_set_usage_rule(u32 id, CRYP_CIPHER_UR_S *pstCipherUR);

/**
\brief   Get user uuid.
\param[in]  id The channel number.
\param[out] the point to user uuid.
\retval     On success, HI_SUCCESS is returned.  On error, HI_FAILURE is returned.
*/
s32 kapi_symc_get_user_uuid(u32 id, TEE_UUID *pstUUID);
#endif

/** @}*/  /** <!-- ==== API Code end ====*/

#ifdef __cplusplus
}
#endif    /* __cplusplus */

#endif    /* End of #ifndef __HI_DRV_CIPHER_H__*/
