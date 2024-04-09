#ifndef __CRYP_COMPAT_H__
#define __CRYP_COMPAT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* enum defined */
#define CRYP_CIPHER_WORK_MODE_E                                       HI_UNF_CIPHER_WORK_MODE_E
#define CRYP_CIPHER_WORK_MODE_ECB                                     HI_UNF_CIPHER_WORK_MODE_ECB
#define CRYP_CIPHER_WORK_MODE_CBC                                     HI_UNF_CIPHER_WORK_MODE_CBC
#define CRYP_CIPHER_WORK_MODE_CFB                                     HI_UNF_CIPHER_WORK_MODE_CFB
#define CRYP_CIPHER_WORK_MODE_OFB                                     HI_UNF_CIPHER_WORK_MODE_OFB
#define CRYP_CIPHER_WORK_MODE_CTR                                     HI_UNF_CIPHER_WORK_MODE_CTR
#define CRYP_CIPHER_WORK_MODE_CCM                                     HI_UNF_CIPHER_WORK_MODE_CCM
#define CRYP_CIPHER_WORK_MODE_GCM                                     HI_UNF_CIPHER_WORK_MODE_GCM
#define CRYP_CIPHER_WORK_MODE_BUTT                                    HI_UNF_CIPHER_WORK_MODE_BUTT

#define CRYP_CIPHER_ALG_E                                             HI_UNF_CIPHER_ALG_E
#define CRYP_CIPHER_ALG_DES                                           HI_UNF_CIPHER_ALG_DES
#define CRYP_CIPHER_ALG_3DES                                          HI_UNF_CIPHER_ALG_3DES
#define CRYP_CIPHER_ALG_AES                                           HI_UNF_CIPHER_ALG_AES
#define CRYP_CIPHER_ALG_SM1                                           HI_UNF_CIPHER_ALG_SM1
#define CRYP_CIPHER_ALG_SM4                                           HI_UNF_CIPHER_ALG_SM4
#define CRYP_CIPHER_ALG_DMA                                           HI_UNF_CIPHER_ALG_DMA
#define CRYP_CIPHER_ALG_BUTT                                          HI_UNF_CIPHER_ALG_BUTT

#define CRYP_CIPHER_KEY_LENGTH_E                                      HI_UNF_CIPHER_KEY_LENGTH_E
#define CRYP_CIPHER_KEY_AES_128BIT                                    HI_UNF_CIPHER_KEY_AES_128BIT
#define CRYP_CIPHER_KEY_AES_192BIT                                    HI_UNF_CIPHER_KEY_AES_192BIT
#define CRYP_CIPHER_KEY_AES_256BIT                                    HI_UNF_CIPHER_KEY_AES_256BIT
#define CRYP_CIPHER_KEY_DES_3KEY                                      HI_UNF_CIPHER_KEY_DES_3KEY
#define CRYP_CIPHER_KEY_DES_2KEY                                      HI_UNF_CIPHER_KEY_DES_2KEY
#define CRYP_CIPHER_KEY_DEFAULT                                       HI_UNF_CIPHER_KEY_DEFAULT

#define CRYP_CIPHER_BIT_WIDTH_E                                       HI_UNF_CIPHER_BIT_WIDTH_E
#define CRYP_CIPHER_BIT_WIDTH_64BIT                                   HI_UNF_CIPHER_BIT_WIDTH_64BIT
#define CRYP_CIPHER_BIT_WIDTH_8BIT                                    HI_UNF_CIPHER_BIT_WIDTH_8BIT
#define CRYP_CIPHER_BIT_WIDTH_1BIT                                    HI_UNF_CIPHER_BIT_WIDTH_1BIT
#define CRYP_CIPHER_BIT_WIDTH_128BIT                                  HI_UNF_CIPHER_BIT_WIDTH_128BIT

#define CRYP_CIPHER_SM1_ROUND_E                                       HI_UNF_CIPHER_SM1_ROUND_E
#define CRYP_CIPHER_SM1_ROUND_08                                      HI_UNF_CIPHER_SM1_ROUND_08
#define CRYP_CIPHER_SM1_ROUND_10                                      HI_UNF_CIPHER_SM1_ROUND_10
#define CRYP_CIPHER_SM1_ROUND_12                                      HI_UNF_CIPHER_SM1_ROUND_12
#define CRYP_CIPHER_SM1_ROUND_14                                      HI_UNF_CIPHER_SM1_ROUND_14
#define CRYP_CIPHER_SM1_ROUND_BUTT                                    HI_UNF_CIPHER_SM1_ROUND_BUTT

#define CRYP_CIPHER_CTRL_CHANGE_FLAG_S                                HI_UNF_CIPHER_CTRL_CHANGE_FLAG_S

#define CRYP_CIPHER_CA_TYPE_E                                         HI_UNF_CIPHER_CA_TYPE_E
#define CRYP_CIPHER_CA_TYPE_R2R                                       HI_UNF_CIPHER_CA_TYPE_R2R
#define CRYP_CIPHER_CA_TYPE_SP                                        HI_UNF_CIPHER_CA_TYPE_SP
#define CRYP_CIPHER_CA_TYPE_CSA2                                      HI_UNF_CIPHER_CA_TYPE_CSA2
#define CRYP_CIPHER_CA_TYPE_CSA3                                      HI_UNF_CIPHER_CA_TYPE_CSA3
#define CRYP_CIPHER_CA_TYPE_MISC                                      HI_UNF_CIPHER_CA_TYPE_MISC
#define CRYP_CIPHER_CA_TYPE_GDRM                                      HI_UNF_CIPHER_CA_TYPE_GDRM
#define CRYP_CIPHER_CA_TYPE_BLPK                                      HI_UNF_CIPHER_CA_TYPE_BLPK
#define CRYP_CIPHER_CA_TYPE_LPK                                       HI_UNF_CIPHER_CA_TYPE_LPK
#define CRYP_CIPHER_CA_TYPE_HCA                                       HI_UNF_CIPHER_CA_TYPE_HCA
#define CRYP_CIPHER_CA_TYPE_STBROOTKEY                                HI_UNF_CIPHER_CA_TYPE_STBROOTKEY
#define CRYP_CIPHER_CA_TYPE_BUTT                                      HI_UNF_CIPHER_CA_TYPE_BUTT

#define CRYP_CIPHER_TYPE_E                                            HI_UNF_CIPHER_TYPE_E
#define CRYP_CIPHER_TYPE_NORMAL                                       HI_UNF_CIPHER_TYPE_NORMAL
#define CRYP_CIPHER_TYPE_COPY_AVOID                                   HI_UNF_CIPHER_TYPE_COPY_AVOID
#define CRYP_CIPHER_TYPE_BUTT                                         HI_UNF_CIPHER_TYPE_BUTT

#define CRYP_CIPHER_HASH_TYPE_SHA1                                    HI_UNF_CIPHER_HASH_TYPE_SHA1
#define CRYP_CIPHER_HASH_TYPE_SHA224                                  HI_UNF_CIPHER_HASH_TYPE_SHA224
#define CRYP_CIPHER_HASH_TYPE_SHA256                                  HI_UNF_CIPHER_HASH_TYPE_SHA256
#define CRYP_CIPHER_HASH_TYPE_SHA384                                  HI_UNF_CIPHER_HASH_TYPE_SHA384
#define CRYP_CIPHER_HASH_TYPE_SHA512                                  HI_UNF_CIPHER_HASH_TYPE_SHA512
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA1                               HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA1
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA224                             HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA224
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA256                             HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA256
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA384                             HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA384
#define CRYP_CIPHER_HASH_TYPE_HMAC_SHA512                             HI_UNF_CIPHER_HASH_TYPE_HMAC_SHA512
#define CRYP_CIPHER_HASH_TYPE_SM3                                     HI_UNF_CIPHER_HASH_TYPE_SM3
#define CRYP_CIPHER_HASH_TYPE_CBCMAC                                  HI_UNF_CIPHER_HASH_TYPE_CBCMAC
#define CRYP_CIPHER_HASH_TYPE_BUTT                                    HI_UNF_CIPHER_HASH_TYPE_BUTT

#define CRYP_CIPHER_RSA_ENC_SCHEME_E                                  HI_UNF_CIPHER_RSA_ENC_SCHEME_E
#define CRYP_CIPHER_RSA_ENC_SCHEME_NO_PADDING                         HI_UNF_CIPHER_RSA_ENC_SCHEME_NO_PADDING
#define CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0                       HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0
#define CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1                       HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1
#define CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2                       HI_UNF_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1                    HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224                  HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256                  HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384                  HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512                  HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512
#define CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5                   HI_UNF_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5
#define CRYP_CIPHER_RSA_ENC_SCHEME_BUTT                               HI_UNF_CIPHER_RSA_ENC_SCHEME_BUTT

#define CRYP_CIPHER_RSA_SIGN_SCHEME_E                                 HI_UNF_CIPHER_RSA_SIGN_SCHEME_E
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1             HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224           HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256           HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384           HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512           HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1             HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224           HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256           HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384           HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384
#define CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512           HI_UNF_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512
#define CRYP_CIPHER_RSA_SIGN_SCHEME_BUTT                              HI_UNF_CIPHER_RSA_SIGN_SCHEME_BUTT

/* struct defined */
#define CRYP_CIPHER_ATTS_S                                            HI_UNF_CIPHER_ATTS_S
#define CRYP_CIPHER_CTRL_S                                            HI_UNF_CIPHER_CTRL_S
#define CRYP_CIPHER_CTRL_AES_S                                        HI_UNF_CIPHER_CTRL_AES_S
#define CRYP_CIPHER_CTRL_AES_CCM_GCM_S                                HI_UNF_CIPHER_CTRL_AES_CCM_GCM_S
#define CRYP_CIPHER_CTRL_DES_S                                        HI_UNF_CIPHER_CTRL_DES_S
#define CRYP_CIPHER_CTRL_3DES_S                                       HI_UNF_CIPHER_CTRL_3DES_S
#define CRYP_CIPHER_CTRL_SM1_S                                        HI_UNF_CIPHER_CTRL_SM1_S
#define CRYP_CIPHER_CTRL_SM4_S                                        HI_UNF_CIPHER_CTRL_SM4_S
#define CRYP_CIPHER_CTRL_EX_S                                         HI_UNF_CIPHER_CTRL_EX_S
#define CRYP_CIPHER_DATA_S                                            HI_UNF_CIPHER_DATA_S

#define CRYP_CIPHER_HASH_TYPE_E                                       HI_UNF_CIPHER_HASH_TYPE_E
#define CRYP_CIPHER_HASH_ATTS_S                                       HI_UNF_CIPHER_HASH_ATTS_S

#define CRYP_CIPHER_RSA_PUB_KEY_S                                     HI_UNF_CIPHER_RSA_PUB_KEY_S
#define CRYP_CIPHER_RSA_PRI_KEY_S                                     HI_UNF_CIPHER_RSA_PRI_KEY_S
#define CRYP_CIPHER_RSA_PUB_ENC_S                                     HI_UNF_CIPHER_RSA_PUB_ENC_S
#define CRYP_CIPHER_RSA_PRI_ENC_S                                     HI_UNF_CIPHER_RSA_PRI_ENC_S
#define CRYP_CIPHER_RSA_SIGN_S                                        HI_UNF_CIPHER_RSA_SIGN_S

#define CRYP_CIPHER_RSA_VERIFY_S                                      HI_UNF_CIPHER_RSA_VERIFY_S
#define CRYP_CIPHER_SM2_SIGN_S                                        HI_UNF_CIPHER_SM2_SIGN_S
#define CRYP_CIPHER_SM2_VERIFY_S                                      HI_UNF_CIPHER_SM2_VERIFY_S
#define CRYP_CIPHER_SM2_ENC_S                                         HI_UNF_CIPHER_SM2_ENC_S
#define CRYP_CIPHER_SM2_DEC_S                                         HI_UNF_CIPHER_SM2_DEC_S
#define CRYP_CIPHER_SM2_KEY_S                                         HI_UNF_CIPHER_SM2_KEY_S
#define CRYP_CIPHER_ECC_PARAM_S                                       HI_UNF_CIPHER_ECC_PARAM_S

#define CRYP_CIPHER_SUBSAMPLE_S                                       HI_UNF_CIPHER_SUBSAMPLE_S
#define CRYP_CIPHER_SUBSAMPLE_EX_S                                    HI_UNF_CIPHER_SUBSAMPLE_EX_S

/* function defined */
#define CRYP_CIPHER_Init                                              HI_UNF_CIPHER_Init
#define CRYP_CIPHER_DeInit                                            HI_UNF_CIPHER_DeInit
#define CRYP_CIPHER_CreateHandle                                      HI_UNF_CIPHER_CreateHandle
#define CRYP_CIPHER_DestroyHandle                                     HI_UNF_CIPHER_DestroyHandle
#define CRYP_CIPHER_ConfigHandle                                      HI_UNF_CIPHER_ConfigHandle
#define CRYP_CIPHER_ConfigHandleEx                                    HI_UNF_CIPHER_ConfigHandleEx
#define CRYP_CIPHER_Encrypt                                           HI_UNF_CIPHER_Encrypt
#define CRYP_CIPHER_Decrypt                                           HI_UNF_CIPHER_Decrypt
#define CRYP_CIPHER_EncryptMulti                                      HI_UNF_CIPHER_EncryptMulti
#define CRYP_CIPHER_DecryptMulti                                      HI_UNF_CIPHER_DecryptMulti
#define CRYP_CIPHER_GetTag                                            HI_UNF_CIPHER_GetTag

#define CRYP_CIPHER_GetRandomNumber                                   HI_UNF_CIPHER_GetRandomNumber
#define CRYP_CIPHER_GetMultiRandomBytes                               HI_UNF_CIPHER_GetMultiRandomBytes

#define CRYP_CIPHER_CalcMAC                                           HI_UNF_CIPHER_CalcMAC
#define CRYP_CIPHER_HashInit                                          HI_UNF_CIPHER_HashInit
#define CRYP_CIPHER_HashUpdate                                        HI_UNF_CIPHER_HashUpdate
#define CRYP_CIPHER_HashFinal                                         HI_UNF_CIPHER_HashFinal

#define CRYP_CIPHER_RsaPublicEncrypt                                  HI_UNF_CIPHER_RsaPublicEncrypt
#define CRYP_CIPHER_RsaPrivateDecrypt                                 HI_UNF_CIPHER_RsaPrivateDecrypt
#define CRYP_CIPHER_RsaPrivateEncrypt                                 HI_UNF_CIPHER_RsaPrivateEncrypt
#define CRYP_CIPHER_RsaPublicDecrypt                                  HI_UNF_CIPHER_RsaPublicDecrypt
#define CRYP_CIPHER_RsaSign                                           HI_UNF_CIPHER_RsaSign
#define CRYP_CIPHER_RsaVerify                                         HI_UNF_CIPHER_RsaVerify
#define CRYP_CIPHER_RsaGenKey                                         HI_UNF_CIPHER_RsaGenKey
#define CRYP_CIPHER_RsaComputeCrtParams                               HI_UNF_CIPHER_RsaComputeCrtParams

#define CRYP_CIPHER_Sm2Sign                                           HI_UNF_CIPHER_Sm2Sign
#define CRYP_CIPHER_Sm2Verify                                         HI_UNF_CIPHER_Sm2Verify
#define CRYP_CIPHER_Sm2Encrypt                                        HI_UNF_CIPHER_Sm2Encrypt
#define CRYP_CIPHER_Sm2Decrypt                                        HI_UNF_CIPHER_Sm2Decrypt
#define CRYP_CIPHER_Sm2GenKey                                         HI_UNF_CIPHER_Sm2GenKey

#define CRYP_CIPHER_CENCDecrypt                                       HI_UNF_CIPHER_CENCDecrypt
#define CRYP_CIPHER_CENCDecryptEx                                     HI_UNF_CIPHER_CENCDecryptEx

#define CRYP_CIPHER_DhComputeKey                                      HI_UNF_CIPHER_DhComputeKey
#define CRYP_CIPHER_DhGenKey                                          HI_UNF_CIPHER_DhGenKey
#define CRYP_CIPHER_EcdhComputeKey                                    HI_UNF_CIPHER_EcdhComputeKey
#define CRYP_CIPHER_EccGenKey                                         HI_UNF_CIPHER_EccGenKey
#define CRYP_CIPHER_EcdsaSign                                         HI_UNF_CIPHER_EcdsaSign
#define CRYP_CIPHER_EcdsaVerify                                       HI_UNF_CIPHER_EcdsaVerify

#define CRYP_CIPHER_Test                                              HI_UNF_CIPHER_Test
#define CRYP_CIPHER_PBKDF2                                            HI_UNF_CIPHER_PBKDF2
#define CRYP_CIPHER_EncryptMultiAsyn                                  HI_UNF_CIPHER_EncryptMultiAsyn
#define CRYP_CIPHER_DecryptMultiAsyn                                  HI_UNF_CIPHER_DecryptMultiAsyn
#define CRYP_CIPHER_WaitDone                                          HI_UNF_CIPHER_WaitDone
#define CRYP_CIPHER_GetHandleConfig                                   HI_UNF_CIPHER_GetHandleConfig

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __CRYP_CIPHER_H__ */
