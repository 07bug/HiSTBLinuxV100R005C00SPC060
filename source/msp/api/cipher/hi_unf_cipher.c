/******************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : hi_unf_cipher.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "user_osal_lib.h"

crypto_mutex  cipher_mutex = PTHREAD_MUTEX_INITIALIZER;

#define HI_CIPHER_LOCK()        (void)crypto_mutex_lock(&cipher_mutex)
#define HI_CIPHER_UNLOCK()      (void)crypto_mutex_unlock(&cipher_mutex)

#define BYTE_BITS               (8)
#define CIPHER_MAX_MULTIPAD_NUM (5000)
#define CENC_SUBSAMPLE_MAX_NUM  (100)
#define ECDH_MAX_KEY_LEN        (72)
#define CIPHER_INIT_MAX_NUM     (0x7FFFFFFF)
#define TRNG_TIMEOUT            (10000)

/* handle of cipher device */
HI_S32 g_CipherDevFd = -1;

/* flag of cipher device
 * indicate the status of device that open or close
 * <0: close, 0: open>0: multiple initialization
 */
static HI_S32 g_CipherInitCounter = -1;

/* check the device of cipher whether already opend or not */
#define CHECK_CIPHER_OPEN()\
do{\
    if (0 > g_CipherInitCounter)\
    {\
        HI_LOG_ERROR("cipher init counter %d\n", g_CipherInitCounter);\
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_NOT_INIT);\
        return HI_ERR_CIPHER_NOT_INIT;\
    }\
}while(0)

/* check the device of cipher for hdcp whether already opend or not */
HI_U32 CHECK_CIPHER_HDCP_OPEN()
{
    HI_UNF_FuncEnter();

    CHECK_CIPHER_OPEN();

    HI_UNF_FuncExit();

    return HI_SUCCESS;
}

/**
 * Read E in public key from arry to U32,
 * so only use last byte0~byte3, others are zero
 */
#define CIPHER_GET_PUB_EXPONENT(e, rsades) \
if (WORD_WIDTH <= rsades->stPubKey.u16ELen) \
{\
    crypto_memcpy(e, WORD_WIDTH, (HI_U8*)&rsades->stPubKey.pu8E[rsades->stPubKey.u16ELen - WORD_WIDTH], WORD_WIDTH); \
}\
else \
{ \
    crypto_memcpy(e, WORD_WIDTH, (HI_U8*)&rsades->stPubKey.pu8E, rsades->stPubKey.u16ELen); \
}

/**
 * \brief  Init the cipher device.
 */
HI_S32 CRYP_CIPHER_Init(HI_VOID)
{
    HI_UNF_FuncEnter();

    HI_CIPHER_LOCK();

    if (CIPHER_INIT_MAX_NUM <= g_CipherInitCounter)
    {
        HI_CIPHER_UNLOCK();

        HI_LOG_PrintErrCode(HI_ERR_CIPHER_OVERFLOW);
        return HI_ERR_CIPHER_OVERFLOW;
    }

    if (0 <= g_CipherInitCounter)
    {
        g_CipherInitCounter++;
        HI_CIPHER_UNLOCK();

        HI_UNF_FuncExit();
        return HI_SUCCESS;
    }

    g_CipherDevFd = crypto_open("/dev/"UMAP_DEVNAME_CIPHER, O_RDWR, 0);
    if (0 > g_CipherDevFd)
    {
        HI_CIPHER_UNLOCK();

        HI_LOG_PrintFuncErr(crypto_open, HI_ERR_CIPHER_FAILED_INIT);
        return HI_ERR_CIPHER_FAILED_INIT;
    }

    g_CipherInitCounter = 0;

    HI_CIPHER_UNLOCK();

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

/**
 * \brief  Deinit the cipher device.
 */
HI_S32 CRYP_CIPHER_DeInit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_CIPHER_LOCK();

    if (0 > g_CipherInitCounter)
    {
        HI_CIPHER_UNLOCK();

        HI_UNF_FuncExit();
        return HI_SUCCESS;
    }

    if (0 < g_CipherInitCounter)
    {
        g_CipherInitCounter--;

        HI_CIPHER_UNLOCK();

        HI_UNF_FuncExit();
        return HI_SUCCESS;
    }

    ret = crypto_close(g_CipherDevFd);
    if (HI_SUCCESS != ret)
    {
        HI_CIPHER_UNLOCK();

        HI_LOG_PrintFuncErr(crypto_close, ret);
        return ret;
    }

    g_CipherInitCounter = -1;

    HI_CIPHER_UNLOCK();

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

/**
 * \brief Obtain a cipher handle for encryption and decryption.
 */
HI_S32 CRYP_CIPHER_CreateHandle(HI_HANDLE* phCipher, const CRYP_CIPHER_ATTS_S *pstCipherAttr)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 id = 0;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == phCipher);
    HI_LOG_CHECK_PARAM(HI_NULL == pstCipherAttr);
    HI_LOG_CHECK_PARAM(CRYP_CIPHER_TYPE_BUTT <= pstCipherAttr->enCipherType);

    HI_DBG_PrintU32(pstCipherAttr->enCipherType);

    CHECK_CIPHER_OPEN();

    ret = mpi_symc_create(&id, pstCipherAttr->enCipherType);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_create, ret);
        return ret;
    }

    *phCipher = id;

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 CRYP_CIPHER_GetRsaAttr(HI_U32 u32SchEme, HI_U32 *pu32Hlen,
                    CRYP_CIPHER_HASH_TYPE_E *penShaType)
{
    HI_UNF_FuncEnter();

    switch(u32SchEme)
    {
        case CRYP_CIPHER_RSA_ENC_SCHEME_NO_PADDING:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_0:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_1:
        case CRYP_CIPHER_RSA_ENC_SCHEME_BLOCK_TYPE_2:
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_PKCS1_V1_5:
        {
            *pu32Hlen = 0;
            *penShaType = CRYP_CIPHER_HASH_TYPE_BUTT;

            break;
        }
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA1:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA1:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA1:
        {
            *pu32Hlen = SHA1_RESULT_SIZE;
            *penShaType = CRYP_CIPHER_HASH_TYPE_SHA1;

            break;
        }
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA224:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA224:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA224:
            *pu32Hlen = SHA224_RESULT_SIZE;
            *penShaType = CRYP_CIPHER_HASH_TYPE_SHA224;

            break;
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA256:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA256:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA256:
        {
            *pu32Hlen = SHA256_RESULT_SIZE;
            *penShaType = CRYP_CIPHER_HASH_TYPE_SHA256;
            break;
        }
#ifdef HI_PRODUCT_SHA512_SUPPORT
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA384:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA384:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA384:
        {
            *pu32Hlen = SHA384_RESULT_SIZE;
            *penShaType = CRYP_CIPHER_HASH_TYPE_SHA384;

            break;
        }
        case CRYP_CIPHER_RSA_ENC_SCHEME_RSAES_OAEP_SHA512:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_V15_SHA512:
        case CRYP_CIPHER_RSA_SIGN_SCHEME_RSASSA_PKCS1_PSS_SHA512:
        {
            *pu32Hlen = SHA512_RESULT_SIZE;
            *penShaType = CRYP_CIPHER_HASH_TYPE_SHA512;
            break;
        }
#endif
        default:
        {
            HI_LOG_PrintU32(u32SchEme);
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_UNAVAILABLE);
            return HI_ERR_CIPHER_UNAVAILABLE;
        }
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

/**
 * \brief Destroy the existing cipher handle.
 */
HI_S32 CRYP_CIPHER_DestroyHandle(HI_HANDLE hCipher)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    CHECK_CIPHER_OPEN();

    ret = mpi_symc_destroy(hCipher);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_destroy, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

/**
 * \brief Configures the cipher control information.
 */
HI_S32 CRYP_CIPHER_ConfigHandle(HI_HANDLE hCipher, CRYP_CIPHER_CTRL_S * pstCtrl)
{
    HI_U32 ivlen = AES_IV_SIZE;
    HI_U32 u32Hardkey = 0;
    HI_U32 u32KeyLen = SYMC_KEY_SIZE;
    compat_addr aad;
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstCtrl);
    HI_LOG_CHECK_PARAM(HI_INVALID_HANDLE == hCipher);

    if (HI_TRUE == pstCtrl->bKeyByCA)
     {
        if (CRYP_CIPHER_CA_TYPE_BUTT <= pstCtrl->enCaType)
        {
            HI_LOG_ERROR("Invalid enCaType with bKeyByCA is HI_TRUE.\n");
            HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
        u32Hardkey  = (pstCtrl->enCaType & 0xFF) << BITS_IN_BYTE;
        u32Hardkey |= 0x01;
    }

    CHECK_CIPHER_OPEN();

    ADDR_U64(aad) = 0x00;

    if ((CRYP_CIPHER_ALG_3DES == pstCtrl->enAlg) || (CRYP_CIPHER_ALG_DES == pstCtrl->enAlg))
    {
        ivlen = DES_IV_SIZE;
    }

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU32(pstCtrl->bKeyByCA);
    HI_LOG_PrintU32(pstCtrl->enAlg);
    HI_LOG_PrintU32(pstCtrl->enWorkMode);
    HI_LOG_PrintU32(pstCtrl->enBitWidth);
    HI_LOG_PrintU32(pstCtrl->enKeyLen);
    HI_LOG_PrintU32(ivlen);
    HI_LOG_PrintU32(pstCtrl->stChangeFlags.bit1IV);
    HI_LOG_PrintU64(ADDR_U64(aad));

    ret = mpi_symc_config(hCipher, u32Hardkey,
        pstCtrl->enAlg, pstCtrl->enWorkMode,
        pstCtrl->enBitWidth, pstCtrl->enKeyLen, 0, (HI_U8*)pstCtrl->u32Key, HI_NULL, u32KeyLen,
        (HI_U8*)pstCtrl->u32IV, ivlen, pstCtrl->stChangeFlags.bit1IV,
        aad, 0, 0);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_config, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

/**
 * \brief Configures the cipher expand control information.
 */
#ifdef HI_PRODUCT_SYMC_CONFIG_EX_SUPPORT
HI_S32 CRYP_CIPHER_ConfigHandleEx(HI_HANDLE hCipher, CRYP_CIPHER_CTRL_EX_S * pstExCtrl)
{
    CRYP_CIPHER_KEY_LENGTH_E enKeyLen = CRYP_CIPHER_KEY_DEFAULT;
    HI_U8 *pu8FirstKey = HI_NULL;
    HI_U8 *pu8SndKey = HI_NULL;
    HI_U32 u32KeyLen = 0;
    HI_U8 *pu8IV = HI_NULL;
    HI_U32 u32Usage = 0;
    compat_addr aad;
    HI_U32 u32ALen = 0;
    HI_U32 u32Taglen = 0;
    HI_U32 u32IVLen = 0;
    CRYP_CIPHER_SM1_ROUND_E enSm1Round = 0;
    CRYP_CIPHER_BIT_WIDTH_E enBitWidth = CRYP_CIPHER_BIT_WIDTH_128BIT;
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstExCtrl);
    HI_LOG_CHECK_PARAM((HI_NULL == pstExCtrl->pParam) && (CRYP_CIPHER_ALG_DMA != pstExCtrl->enAlg));

    CHECK_CIPHER_OPEN();

    ADDR_U64(aad) = 0x00;

    /*****************************************************************************
     * for AES, the pointer should point to CRYP_CIPHER_CTRL_AES_S;
     * for AES_CCM or AES_GCM, the pointer should point to CRYP_CIPHER_CTRL_AES_CCM_GCM_S;
     * for DES, the pointer should point to CRYP_CIPHER_CTRL_DES_S;
     * for 3DES, the pointer should point to CRYP_CIPHER_CTRL_3DES_S;
     * for SM1, the pointer should point to CRYP_CIPHER_CTRL_SM1_S;
     * for SM4, the pointer should point to CRYP_CIPHER_CTRL_SM4_S;
    */
    switch(pstExCtrl->enAlg)
    {
    case CRYP_CIPHER_ALG_DES:
    {
        CRYP_CIPHER_CTRL_DES_S *pstDesCtrl = (CRYP_CIPHER_CTRL_DES_S *)pstExCtrl->pParam;

        pu8FirstKey = (HI_U8*)pstDesCtrl->u32Key;
        u32KeyLen = sizeof(pstDesCtrl->u32Key);
        pu8IV = (HI_U8*)pstDesCtrl->u32IV;
        u32Usage = pstDesCtrl->stChangeFlags.bit1IV;
        u32IVLen = DES_IV_SIZE;
        enBitWidth = pstDesCtrl->enBitWidth;

        break;
    }
    case CRYP_CIPHER_ALG_3DES:
    {
        CRYP_CIPHER_CTRL_3DES_S *pst3DesCtrl = (CRYP_CIPHER_CTRL_3DES_S *)pstExCtrl->pParam;

        pu8FirstKey = (HI_U8*)pst3DesCtrl->u32Key;
        u32KeyLen = sizeof(pst3DesCtrl->u32Key);
        pu8IV = (HI_U8*)pst3DesCtrl->u32IV;
        u32Usage = pst3DesCtrl->stChangeFlags.bit1IV;
        enKeyLen = pst3DesCtrl->enKeyLen;
        u32IVLen = DES_IV_SIZE;
        enBitWidth = pst3DesCtrl->enBitWidth;
        break;
    }
    case CRYP_CIPHER_ALG_AES:
    {
        if ((pstExCtrl->enWorkMode == CRYP_CIPHER_WORK_MODE_CCM)
            || (pstExCtrl->enWorkMode == CRYP_CIPHER_WORK_MODE_GCM))
        {
            CRYP_CIPHER_CTRL_AES_CCM_GCM_S *pstAesCcmGcmCtrl
                = (CRYP_CIPHER_CTRL_AES_CCM_GCM_S *)pstExCtrl->pParam;

            pu8FirstKey = (HI_U8*)pstAesCcmGcmCtrl->u32Key;
            u32KeyLen = sizeof(pstAesCcmGcmCtrl->u32Key);
            pu8IV = (HI_U8*)pstAesCcmGcmCtrl->u32IV;
            u32IVLen = pstAesCcmGcmCtrl->u32IVLen;

            if (AES_IV_SIZE < u32IVLen)
            {
                HI_LOG_ERROR("para set CIPHER ccm/gcm iv is invalid, u32IVLen:0x%x.\n",u32IVLen);
                HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
                return HI_ERR_CIPHER_INVALID_PARA;
            }

            u32Taglen = pstAesCcmGcmCtrl->u32TagLen;
            enKeyLen = pstAesCcmGcmCtrl->enKeyLen;
            ADDR_U64(aad) = pstAesCcmGcmCtrl->u32APhyAddr;
            u32ALen = pstAesCcmGcmCtrl->u32ALen;
            u32Usage = CIPHER_IV_CHANGE_ONE_PKG;
        }
        else
        {
            CRYP_CIPHER_CTRL_AES_S *pstAesCtrl = (CRYP_CIPHER_CTRL_AES_S *)pstExCtrl->pParam;

            pu8FirstKey = (HI_U8*)pstAesCtrl->u32EvenKey;
            pu8SndKey = (HI_U8*)pstAesCtrl->u32OddKey;
            u32KeyLen = sizeof(pstAesCtrl->u32EvenKey);
            pu8IV = (HI_U8*)pstAesCtrl->u32IV;
            u32Usage = pstAesCtrl->stChangeFlags.bit1IV;
            enKeyLen = pstAesCtrl->enKeyLen;
            enBitWidth = pstAesCtrl->enBitWidth;
            u32IVLen = AES_IV_SIZE;
        }
        break;
    }
    case CRYP_CIPHER_ALG_SM1:
    {
        CRYP_CIPHER_CTRL_SM1_S *pstSm1Ctrl = (CRYP_CIPHER_CTRL_SM1_S *)pstExCtrl->pParam;

        pu8FirstKey = (HI_U8*)pstSm1Ctrl->u32EK;
        pu8SndKey = (HI_U8*)pstSm1Ctrl->u32SK;
        u32KeyLen = sizeof(pstSm1Ctrl->u32EK);
        pu8IV = (HI_U8*)pstSm1Ctrl->u32IV;
        u32Usage = pstSm1Ctrl->stChangeFlags.bit1IV;
        enKeyLen = CRYP_CIPHER_KEY_DEFAULT;
        enSm1Round = pstSm1Ctrl->enSm1Round;
        enBitWidth = pstSm1Ctrl->enBitWidth;
        u32IVLen = AES_IV_SIZE;
        break;
    }
    case CRYP_CIPHER_ALG_SM4:
    {
        CRYP_CIPHER_CTRL_SM4_S *pstSm4Ctrl = (CRYP_CIPHER_CTRL_SM4_S *)pstExCtrl->pParam;

        pu8FirstKey = (HI_U8*)pstSm4Ctrl->u32Key;
        u32KeyLen = sizeof(pstSm4Ctrl->u32Key);
        pu8IV = (HI_U8*)pstSm4Ctrl->u32IV;
        u32Usage = pstSm4Ctrl->stChangeFlags.bit1IV;
        enKeyLen = CRYP_CIPHER_KEY_DEFAULT;
        u32IVLen = AES_IV_SIZE;
        break;
    }
    case CRYP_CIPHER_ALG_DMA:
    {
        break;
    }
    default:
        HI_LOG_ERROR("para set CIPHER alg is invalid.\n");
        HI_LOG_PrintErrCode(HI_ERR_CIPHER_INVALID_PARA);
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU32(pstExCtrl->bKeyByCA);
    HI_LOG_PrintU32(pstExCtrl->enAlg);
    HI_LOG_PrintU32(pstExCtrl->enWorkMode);
    HI_LOG_PrintU32(enBitWidth);
    HI_LOG_PrintU32(enKeyLen);
    HI_LOG_PrintU32(enSm1Round);
    HI_LOG_PrintU32(u32KeyLen);
    HI_LOG_PrintU32(u32IVLen);
    HI_LOG_PrintU32(u32Usage);
    HI_LOG_PrintU64(ADDR_U64(aad));
    HI_LOG_PrintU32(u32ALen);
    HI_LOG_PrintU32(u32Taglen);

    ret = mpi_symc_config(hCipher, pstExCtrl->bKeyByCA, pstExCtrl->enAlg,
        pstExCtrl->enWorkMode, enBitWidth, enKeyLen, enSm1Round,
        pu8FirstKey, pu8SndKey, u32KeyLen, pu8IV, u32IVLen,
        u32Usage, aad, u32ALen, u32Taglen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_config, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}
#endif

/**
 * \brief Performs encryption.
 */
HI_S32 CRYP_CIPHER_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    compat_addr input;
    compat_addr output;
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    CHECK_CIPHER_OPEN();

    ADDR_U64(input) = u32SrcPhyAddr;
    ADDR_U64(output) = u32DestPhyAddr;

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU64(u32SrcPhyAddr);
    HI_LOG_PrintU64(u32DestPhyAddr);
    HI_LOG_PrintU32(u32ByteLength);

    ret = mpi_symc_crypto(hCipher, input, output, u32ByteLength, SYMC_OPERATION_ENCRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_crypto, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

/**
 * \brief Performs descryption.
 */
HI_S32 CRYP_CIPHER_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr,
                             HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    compat_addr input;
    compat_addr output;
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU64(u32SrcPhyAddr);
    HI_LOG_PrintU64(u32DestPhyAddr);
    HI_LOG_PrintU32(u32ByteLength);

    CHECK_CIPHER_OPEN();

    ADDR_U64(input) = u32SrcPhyAddr;
    ADDR_U64(output) = u32DestPhyAddr;

    ret = mpi_symc_crypto(hCipher, input, output, u32ByteLength, SYMC_OPERATION_DECRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_crypto, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

/**
 * \brief Encrypt multiple packaged data.
 */
HI_S32 CRYP_CIPHER_EncryptMulti(HI_HANDLE hCipher,
                                CRYP_CIPHER_DATA_S *pstDataPkg,
                                HI_U32 u32DataPkgNum)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    CHECK_CIPHER_OPEN();

    HI_LOG_CHECK_PARAM(HI_NULL == pstDataPkg);
    HI_LOG_CHECK_PARAM(0x00 == u32DataPkgNum);
    HI_LOG_CHECK_PARAM(CIPHER_MAX_MULTIPAD_NUM <= u32DataPkgNum);

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU32(u32DataPkgNum);

    ret = mpi_symc_crypto_multi(hCipher, pstDataPkg, u32DataPkgNum, SYMC_OPERATION_ENCRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_crypto_multi, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

/**
 * \brief Encrypt multiple packaged data.
 */
HI_S32 CRYP_CIPHER_DecryptMulti(HI_HANDLE hCipher, CRYP_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();


    HI_LOG_CHECK_PARAM(HI_NULL == pstDataPkg);
    HI_LOG_CHECK_PARAM(0x00 == u32DataPkgNum);
    HI_LOG_CHECK_PARAM(CIPHER_MAX_MULTIPAD_NUM <= u32DataPkgNum);

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU32(u32DataPkgNum);

    CHECK_CIPHER_OPEN();

    ret = mpi_symc_crypto_multi(hCipher, pstDataPkg, u32DataPkgNum, SYMC_OPERATION_DECRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_crypto_multi, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

#ifdef HI_PRODUCT_AEAD_SUPPORT
HI_S32 CRYP_CIPHER_GetTag(HI_HANDLE hCipher, HI_U8 *pu8Tag, HI_U32 *pu32TagLen)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu8Tag);
    HI_LOG_CHECK_PARAM(HI_NULL == pu32TagLen);
    HI_LOG_CHECK_PARAM(AEAD_TAG_SIZE != *pu32TagLen);

    HI_LOG_PrintU32(hCipher);

    CHECK_CIPHER_OPEN();

    ret = mpi_aead_get_tag(hCipher, pu8Tag, pu32TagLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_aead_get_tag, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}
#endif

HI_S32 CRYP_CIPHER_GetHandleConfig(HI_HANDLE hCipherHandle, CRYP_CIPHER_CTRL_S * pstCtrl)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstCtrl);

    CHECK_CIPHER_OPEN();

    ret = mpi_symc_get_config(hCipherHandle, pstCtrl);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_get_config, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_GetMultiRandomBytes(HI_U8 *pu8RandomByte, HI_U32 u32Bytes)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu8RandomByte);

    ret = mpi_trng_get_random(pu8RandomByte, u32Bytes, TRNG_TIMEOUT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_trng_get_random, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu32RandomNumber);

    ret = mpi_trng_get_random((HI_U8*)pu32RandomNumber, WORD_WIDTH, 0);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_HashInit(CRYP_CIPHER_HASH_ATTS_S *pstHashAttr, HI_HANDLE *pHashHandle)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstHashAttr);
    HI_LOG_CHECK_PARAM(HI_NULL == pHashHandle);

    HI_DBG_PrintU32(pstHashAttr->eShaType);
    HI_DBG_PrintU32(pstHashAttr->u32HMACKeyLen);

    CHECK_CIPHER_OPEN();

    ret = mpi_hash_start(pHashHandle,
                         pstHashAttr->eShaType,
                         pstHashAttr->pu8HMACKey,
                         pstHashAttr->u32HMACKeyLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_start, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu8InputData);

    HI_DBG_PrintU32(hHashHandle);
    HI_DBG_PrintU32(u32InputDataLen);

    CHECK_CIPHER_OPEN();

    ret = mpi_hash_update(hHashHandle, pu8InputData, u32InputDataLen, HASH_CHUNCK_SRC_USER);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_update, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32HashLen = 0x00;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu8OutputHash);
    HI_LOG_CHECK_PARAM(HI_INVALID_HANDLE == hHashHandle);

    HI_DBG_PrintU32(hHashHandle);

    CHECK_CIPHER_OPEN();

    ret = mpi_hash_finish(hHashHandle, pu8OutputHash, &u32HashLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_finish, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 CHECK_RSA_PRI_key(CRYP_CIPHER_RSA_PRI_KEY_S *pstPriKey)
{
    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstPriKey);
    HI_LOG_CHECK_PARAM(HI_NULL == pstPriKey->pu8N);
    HI_LOG_CHECK_PARAM(RSA_MIN_KEY_LEN > pstPriKey->u16NLen);
    HI_LOG_CHECK_PARAM(RSA_MAX_KEY_LEN < pstPriKey->u16NLen);

    if (HI_NULL == pstPriKey->pu8D)
    {
        HI_LOG_CHECK_PARAM(HI_NULL == pstPriKey->pu8P);
        HI_LOG_CHECK_PARAM(HI_NULL == pstPriKey->pu8Q);
        HI_LOG_CHECK_PARAM(HI_NULL == pstPriKey->pu8DP);
        HI_LOG_CHECK_PARAM(HI_NULL == pstPriKey->pu8DQ);
        HI_LOG_CHECK_PARAM(HI_NULL == pstPriKey->pu8QP);
        HI_LOG_CHECK_PARAM(pstPriKey->u16NLen/2 != pstPriKey->u16PLen);
        HI_LOG_CHECK_PARAM(pstPriKey->u16NLen/2 != pstPriKey->u16QLen);
        HI_LOG_CHECK_PARAM(pstPriKey->u16NLen/2 != pstPriKey->u16DPLen);
        HI_LOG_CHECK_PARAM(pstPriKey->u16NLen/2 != pstPriKey->u16DQLen);
        HI_LOG_CHECK_PARAM(pstPriKey->u16NLen/2 != pstPriKey->u16QPLen);
    }
    else
    {
        HI_LOG_CHECK_PARAM(pstPriKey->u16NLen != pstPriKey->u16DLen);
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_RsaPublicEncrypt(CRYP_CIPHER_RSA_PUB_ENC_S *pstRsaEnc,
                                  HI_U8 *pu8Input, HI_U32 u32InLen,
                                  HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaEnc);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Input);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Output);
    HI_LOG_CHECK_PARAM(HI_NULL == pu32OutLen);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaEnc->stPubKey.pu8N);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaEnc->stPubKey.pu8E);
    HI_LOG_CHECK_PARAM(RSA_MIN_KEY_LEN > pstRsaEnc->stPubKey.u16NLen);
    HI_LOG_CHECK_PARAM(RSA_MAX_KEY_LEN < pstRsaEnc->stPubKey.u16NLen);
    HI_LOG_CHECK_PARAM(pstRsaEnc->stPubKey.u16NLen < pstRsaEnc->stPubKey.u16ELen);

    HI_LOG_PrintU32(pstRsaEnc->stPubKey.u16NLen);
    HI_LOG_PrintU32(pstRsaEnc->enScheme);
    HI_LOG_PrintU32(u32InLen);

    CHECK_CIPHER_OPEN();

    crypto_memset(&key, sizeof(key), 0, sizeof(key));
    key.public = HI_TRUE;
    key.klen = pstRsaEnc->stPubKey.u16NLen;
    key.N = pstRsaEnc->stPubKey.pu8N;
    CIPHER_GET_PUB_EXPONENT(&key.e, pstRsaEnc);

    ret = mpi_rsa_encrypt(&key, pstRsaEnc->enScheme,
                          pu8Input, u32InLen,
                          pu8Output, pu32OutLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_encrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;

}

HI_S32 CRYP_CIPHER_RsaPrivateDecrypt(CRYP_CIPHER_RSA_PRI_ENC_S *pstRsaDec,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaDec);

    ret = CHECK_RSA_PRI_key(&pstRsaDec->stPriKey);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CHECK_RSA_PRI_key, ret);
        return ret;
    }

    HI_LOG_CHECK_PARAM(HI_NULL == pu8Input);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Output);
    HI_LOG_CHECK_PARAM(HI_NULL == pu32OutLen);

    HI_LOG_PrintU32(pstRsaDec->stPriKey.u16NLen);
    HI_LOG_PrintU32(pstRsaDec->enScheme);
    HI_LOG_PrintU32(u32InLen);

    CHECK_CIPHER_OPEN();

    crypto_memset(&key, sizeof(key), 0, sizeof(key));
    key.public  = HI_FALSE;
    key.klen    = pstRsaDec->stPriKey.u16NLen;
    key.N       = pstRsaDec->stPriKey.pu8N;
    key.d       = pstRsaDec->stPriKey.pu8D;
    key.p       = pstRsaDec->stPriKey.pu8P;
    key.q       = pstRsaDec->stPriKey.pu8Q;
    key.dP       = pstRsaDec->stPriKey.pu8DP;
    key.dQ       = pstRsaDec->stPriKey.pu8DQ;
    key.qP       = pstRsaDec->stPriKey.pu8QP;

    ret = mpi_rsa_decrypt(&key,
                          pstRsaDec->enScheme,
                          pu8Input, u32InLen,
                          pu8Output, pu32OutLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_decrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_RsaPrivateEncrypt(CRYP_CIPHER_RSA_PRI_ENC_S *pstRsaEnc,
                                   HI_U8 *pu8Input, HI_U32 u32InLen,
                                   HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaEnc);

    ret = CHECK_RSA_PRI_key(&pstRsaEnc->stPriKey);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CHECK_RSA_PRI_key, ret);
        return ret;
    }

    HI_LOG_CHECK_PARAM(HI_NULL == pu8Input);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Output);
    HI_LOG_CHECK_PARAM(HI_NULL == pu32OutLen);

    HI_LOG_PrintU32(pstRsaEnc->stPriKey.u16NLen);
    HI_LOG_PrintU32(pstRsaEnc->enScheme);
    HI_LOG_PrintU32(u32InLen);

    CHECK_CIPHER_OPEN();

    crypto_memset(&key, sizeof(key), 0, sizeof(key));
    key.public  = HI_FALSE;
    key.klen    = pstRsaEnc->stPriKey.u16NLen;
    key.N       = pstRsaEnc->stPriKey.pu8N;
    key.d       = pstRsaEnc->stPriKey.pu8D;
    key.p       = pstRsaEnc->stPriKey.pu8P;
    key.q       = pstRsaEnc->stPriKey.pu8Q;
    key.dP       = pstRsaEnc->stPriKey.pu8DP;
    key.dQ       = pstRsaEnc->stPriKey.pu8DQ;
    key.qP       = pstRsaEnc->stPriKey.pu8QP;

    ret = mpi_rsa_encrypt(&key,
                          pstRsaEnc->enScheme,
                          pu8Input, u32InLen,
                          pu8Output, pu32OutLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_encrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}


HI_S32 CRYP_CIPHER_RsaPublicDecrypt(CRYP_CIPHER_RSA_PUB_ENC_S *pstRsaDec,
                               HI_U8 *pu8Input, HI_U32 u32InLen,
                               HI_U8 *pu8Output, HI_U32 *pu32OutLen)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaDec);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Input);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Output);
    HI_LOG_CHECK_PARAM(HI_NULL == pu32OutLen);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaDec->stPubKey.pu8N);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaDec->stPubKey.pu8E);
    HI_LOG_CHECK_PARAM(RSA_MIN_KEY_LEN > pstRsaDec->stPubKey.u16NLen);
    HI_LOG_CHECK_PARAM(RSA_MAX_KEY_LEN < pstRsaDec->stPubKey.u16NLen);
    HI_LOG_CHECK_PARAM(pstRsaDec->stPubKey.u16NLen < pstRsaDec->stPubKey.u16ELen);

    HI_DBG_PrintU32(pstRsaDec->enScheme);
    HI_DBG_PrintU32(u32InLen);
    HI_DBG_PrintU32(pstRsaDec->stPubKey.u16NLen);

    CHECK_CIPHER_OPEN();

    crypto_memset(&key, sizeof(key), 0, sizeof(key));
    key.public  = HI_TRUE;
    key.klen    = pstRsaDec->stPubKey.u16NLen;
    key.N       = pstRsaDec->stPubKey.pu8N;
    CIPHER_GET_PUB_EXPONENT(&key.e, pstRsaDec);

    ret = mpi_rsa_decrypt(&key, pstRsaDec->enScheme, pu8Input, u32InLen, pu8Output, pu32OutLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_decrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

static HI_S32 CRYP_CIPHER_Hash(CRYP_CIPHER_HASH_TYPE_E enShaType,
                               HI_U8 *pu8InData, HI_U32 u32InDataLen,
                               HI_U8 *pu8HashData, HI_U32 *pu32Hlen)
{
    HI_S32 ret = HI_FAILURE;
    HI_HANDLE hash_id;

    ret = mpi_hash_start(&hash_id, enShaType, HI_NULL, 0);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_start, ret);
        return ret;
    }

    ret = mpi_hash_update(hash_id, pu8InData, u32InDataLen, HASH_CHUNCK_SRC_USER);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_update, ret);
        return ret;
    }

    ret = mpi_hash_finish(hash_id, pu8HashData, pu32Hlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_finish, ret);
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_RsaSign(CRYP_CIPHER_RSA_SIGN_S *pstRsaSign,
                             HI_U8 *pu8InData, HI_U32 u32InDataLen,
                             HI_U8 *pu8HashData,
                             HI_U8 *pu8OutSign, HI_U32 *pu32OutSignLen)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;
    HI_U8 hash[HASH_RESULT_MAX_SIZE];
    HI_U8 *ptr = HI_NULL;
    HI_U32 u32Hlen = 0;
    CRYP_CIPHER_HASH_TYPE_E enShaType = 0;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaSign);

    ret = CHECK_RSA_PRI_key(&pstRsaSign->stPriKey);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CHECK_RSA_PRI_key, ret);
        return ret;
    }

    HI_LOG_CHECK_PARAM(HI_NULL == pu8OutSign);
    HI_LOG_CHECK_PARAM(HI_NULL == pu32OutSignLen);

    HI_LOG_CHECK_PARAM((HI_NULL == pu8InData) && (HI_NULL == pu8HashData));

    HI_LOG_PrintU32(pstRsaSign->enScheme);
    HI_LOG_PrintU32(pstRsaSign->stPriKey.u16NLen);

    CHECK_CIPHER_OPEN();

    ret = CRYP_CIPHER_GetRsaAttr(pstRsaSign->enScheme, &u32Hlen, &enShaType);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYP_CIPHER_GetRsaAttr, ret);
        return ret;
    }

    HI_LOG_PrintU32(u32Hlen);
    HI_LOG_PrintU32(enShaType);

    /* hash value of context,if NULL, compute hash = Hash(pu8InData */
    if (HI_NULL == pu8HashData)
    {
        ret = CRYP_CIPHER_Hash(enShaType, pu8InData, u32InDataLen, hash, &u32Hlen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(CRYP_CIPHER_Hash, ret);
            return ret;
        }
        ptr = hash;
    }
    else
    {
        ptr = pu8HashData;
    }

    crypto_memset(&key, sizeof(key), 0, sizeof(key));
    key.public  = HI_FALSE;
    key.klen    = pstRsaSign->stPriKey.u16NLen;
    key.N       = pstRsaSign->stPriKey.pu8N;
    key.d       = pstRsaSign->stPriKey.pu8D;
    key.p       = pstRsaSign->stPriKey.pu8P;
    key.q       = pstRsaSign->stPriKey.pu8Q;
    key.dP       = pstRsaSign->stPriKey.pu8DP;
    key.dQ       = pstRsaSign->stPriKey.pu8DQ;
    key.qP       = pstRsaSign->stPriKey.pu8QP;

    ret = mpi_rsa_sign_hash(&key, pstRsaSign->enScheme, ptr, u32Hlen, pu8OutSign, pu32OutSignLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_sign_hash, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_RsaVerify(CRYP_CIPHER_RSA_VERIFY_S *pstRsaVerify,
                               HI_U8 *pu8InData, HI_U32 u32InDataLen,
                               HI_U8 *pu8HashData,
                               HI_U8 *pu8InSign, HI_U32 u32InSignLen)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;
    HI_U8 hash[HASH_RESULT_MAX_SIZE];
    HI_U32 u32Hlen = 0;
    HI_U8 *ptr = HI_NULL;
    CRYP_CIPHER_HASH_TYPE_E enShaType = 0;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaVerify);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8InSign);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaVerify->stPubKey.pu8N);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaVerify->stPubKey.pu8E);
    HI_LOG_CHECK_PARAM(RSA_MIN_KEY_LEN > pstRsaVerify->stPubKey.u16NLen);
    HI_LOG_CHECK_PARAM(RSA_MAX_KEY_LEN < pstRsaVerify->stPubKey.u16NLen);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8InData && HI_NULL == pu8HashData);
    HI_LOG_CHECK_PARAM(pstRsaVerify->stPubKey.u16NLen < pstRsaVerify->stPubKey.u16ELen);

    HI_LOG_PrintU32(pstRsaVerify->enScheme);
    HI_LOG_PrintU32(pstRsaVerify->stPubKey.u16NLen);
    HI_LOG_PrintU32(pstRsaVerify->enScheme);

    CHECK_CIPHER_OPEN();

    ret = CRYP_CIPHER_GetRsaAttr(pstRsaVerify->enScheme, &u32Hlen, &enShaType);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYP_CIPHER_GetRsaAttr, ret);
        return ret;
    }

    HI_LOG_PrintU32(enShaType);

    /* hash value of context,if NULL, compute hash = Hash(pu8InData */
    if (HI_NULL == pu8HashData)
    {
        ret = CRYP_CIPHER_Hash(enShaType, pu8InData, u32InDataLen, hash, &u32Hlen);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(CRYP_CIPHER_Hash, ret);
            return ret;
        }
        ptr = hash;
    }
    else
    {
        ptr = pu8HashData;
    }

    HI_LOG_PrintU32(u32Hlen);

    crypto_memset(&key, sizeof(key), 0, sizeof(key));
    key.public  = HI_TRUE;
    key.klen    = pstRsaVerify->stPubKey.u16NLen;
    key.N       = pstRsaVerify->stPubKey.pu8N;
    CIPHER_GET_PUB_EXPONENT(&key.e, pstRsaVerify);

    ret = mpi_rsa_verify_hash(&key, pstRsaVerify->enScheme, ptr, u32Hlen, pu8InSign, u32InSignLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_verify_hash, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

#ifdef HI_PRODUCT_DH_SUPPORT
HI_S32 CRYP_CIPHER_DhComputeKey(HI_U8 * pu8P, HI_U8 *pu8PrivKey, HI_U8 *pu8OtherPubKey,
                                  HI_U8 *pu8SharedSecret, HI_U32 u32KeySize)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;

    HI_LOG_CHECK_PARAM(HI_NULL == pu8P);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8PrivKey);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8OtherPubKey);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8SharedSecret);
    HI_LOG_CHECK_PARAM(0 == u32KeySize);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(u32KeySize);

    crypto_memset(&key, sizeof(key), 0, sizeof(key));
    key.public  = HI_FALSE;
    key.klen    = u32KeySize;
    key.N       = pu8P;
    key.d       = pu8PrivKey;

    ret = mpi_rsa_encrypt(&key,
                          CRYP_CIPHER_RSA_ENC_SCHEME_NO_PADDING,
                          pu8OtherPubKey, u32KeySize,
                          pu8SharedSecret, &u32KeySize);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_encrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_DhGenKey(HI_U8 *pu8G, HI_U8 *pu8P, HI_U8 *pu8InputPrivKey,
                            HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKey,
                            HI_U32 u32KeySize)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;
    u32 i;

    HI_LOG_CHECK_PARAM(HI_NULL == pu8P);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8G);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8PubKey);
    HI_LOG_CHECK_PARAM((HI_NULL == pu8InputPrivKey) && (HI_NULL == pu8OutputPrivKey));
    HI_LOG_CHECK_PARAM(0 == u32KeySize);

    if (0x00 == pu8P[0])
    {
        HI_LOG_ERROR("Invalid P[0], must large than 0!");
        return HI_ERR_CIPHER_INVALID_PARA;
    }

    CHECK_CIPHER_OPEN();

    crypto_memset(&key, sizeof(key), 0, sizeof(key));

    if (HI_NULL == pu8InputPrivKey)
    {
        ret = CRYP_CIPHER_GetMultiRandomBytes(pu8OutputPrivKey, u32KeySize);
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(CRYP_CIPHER_GetRandomBytes, ret);
            return ret;
        }

        //make sure PrivKey < P
        for (i=0; i<u32KeySize; i++)
        {
            if (0x00 == pu8P[i])
            {
                pu8OutputPrivKey[i] = 0x00;
            }
            else if (pu8OutputPrivKey[i] < pu8P[i])
            {
                break;
            }
            else
            {
                pu8OutputPrivKey[i] = pu8P[0] - 1;
                break;
            }
        }

        key.d = pu8OutputPrivKey;
    }
    else
    {
        key.d = pu8InputPrivKey;
    }

    key.public = HI_FALSE;
    key.klen = u32KeySize;
    key.N = pu8P;

    HI_LOG_PrintU32(u32KeySize);

    ret = mpi_rsa_encrypt(&key, CRYP_CIPHER_RSA_ENC_SCHEME_NO_PADDING,
                           pu8G, u32KeySize,
                           pu8PubKey, &u32KeySize);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_encrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}
#endif

#ifdef HI_PRODUCT_SM2_SUPPORT
HI_S32 CRYP_CIPHER_Sm2Sign(CRYP_CIPHER_SM2_SIGN_S *pstSm2Sign, HI_U8 *pu8Msg,
                           HI_U32 u32MsgLen, HI_U8 u8R[SM2_LEN_IN_BYTE],
                           HI_U8 u8S[SM2_LEN_IN_BYTE])
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstSm2Sign);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Msg);
    HI_LOG_CHECK_PARAM(HI_NULL == u8R);
    HI_LOG_CHECK_PARAM(HI_NULL == u8S);
    HI_LOG_CHECK_PARAM(SM2_ID_MAX_LEN < pstSm2Sign->u16IdLen);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(pstSm2Sign->u16IdLen);
    HI_LOG_PrintU32(u32MsgLen);

    ret = mpi_sm2_sign(pstSm2Sign->u32d, pstSm2Sign->u32Px, pstSm2Sign->u32Py,
                       pstSm2Sign->pu8Id, pstSm2Sign->u16IdLen,
                       pu8Msg, u32MsgLen,
                       HASH_CHUNCK_SRC_USER, u8R, u8S);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_sm2_sign, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return ret;
}

HI_S32 CRYP_CIPHER_Sm2Verify(CRYP_CIPHER_SM2_VERIFY_S *pstSm2Verify,
                             HI_U8 *pu8Msg, HI_U32 u32MsgLen,
                             HI_U8 u8R[SM2_LEN_IN_BYTE],
                             HI_U8 u8S[SM2_LEN_IN_BYTE])
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstSm2Verify);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Msg);
    HI_LOG_CHECK_PARAM(HI_NULL == u8R);
    HI_LOG_CHECK_PARAM(HI_NULL == u8S);

    CHECK_CIPHER_OPEN();
    HI_LOG_PrintU32(pstSm2Verify->u16IdLen);
    HI_LOG_PrintU32(u32MsgLen);

    ret = mpi_sm2_verify(pstSm2Verify->u32Px,
                         pstSm2Verify->u32Py,
                         pstSm2Verify->pu8Id, pstSm2Verify->u16IdLen,
                         pu8Msg, u32MsgLen,
                         HASH_CHUNCK_SRC_USER, u8R, u8S);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_sm2_verify, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_Sm2Encrypt(CRYP_CIPHER_SM2_ENC_S *pstSm2Enc,  HI_U8 *pu8Msg,
                              HI_U32 u32MsgLen, HI_U8 *pu8C, HI_U32 *pu32Clen)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstSm2Enc);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Msg);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8C);
    HI_LOG_CHECK_PARAM(HI_NULL == pu32Clen);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(u32MsgLen);

    ret = mpi_sm2_encrypt(pstSm2Enc->u32Px,
                          pstSm2Enc->u32Py,
                          pu8Msg, u32MsgLen,
                          pu8C, pu32Clen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintU32(*pu32Clen);
        HI_LOG_PrintFuncErr(mpi_sm2_encrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_Sm2Decrypt(CRYP_CIPHER_SM2_DEC_S *pstSm2Dec, HI_U8 *pu8C,
                              HI_U32 u32Clen, HI_U8 *pu8Msg, HI_U32 *pu32MsgLen)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstSm2Dec);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Msg);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8C);
    HI_LOG_CHECK_PARAM(HI_NULL == pu32MsgLen);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(u32Clen);

    ret = mpi_sm2_decrypt(pstSm2Dec->u32d,
                          pu8C, u32Clen,
                          pu8Msg, pu32MsgLen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_sm2_decrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_Sm2GenKey(CRYP_CIPHER_SM2_KEY_S *pstSm2Key)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstSm2Key);

    CHECK_CIPHER_OPEN();

    ret = mpi_sm2_gen_key(pstSm2Key->u32d, pstSm2Key->u32Px, pstSm2Key->u32Py);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_sm2_gen_key, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}
#endif

#ifdef HI_PRODUCT_CENC_SUPPORT
HI_S32 CRYP_CIPHER_CENCDecrypt(HI_HANDLE hCipher, HI_U8 *pu8Key, HI_U8 *pu8IV,
                            HI_U32 u32NonSecInPhyAddr, HI_U32 u32SecOutPhyAddr,
                            HI_U32 u32ByteLength, HI_U32 u32FirstEncryptOffset,
                            CRYP_CIPHER_SUBSAMPLE_S *pstSubSample, HI_U32 u32SubsampleNum)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstSubSample);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Key);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8IV);
    HI_LOG_CHECK_PARAM(0 == u32NonSecInPhyAddr);
    HI_LOG_CHECK_PARAM(0 == u32SecOutPhyAddr);
    HI_LOG_CHECK_PARAM(CENC_SUBSAMPLE_MAX_NUM < u32SubsampleNum);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU32(u32NonSecInPhyAddr);
    HI_LOG_PrintU32(u32SecOutPhyAddr);
    HI_LOG_PrintU32(u32ByteLength);
    HI_LOG_PrintU32(u32FirstEncryptOffset);
    HI_LOG_PrintU32(u32SubsampleNum);

    ret = mpi_cenc_decrypt(hCipher, pu8Key, pu8IV, u32NonSecInPhyAddr, u32SecOutPhyAddr,
            u32ByteLength, u32FirstEncryptOffset, pstSubSample, u32SubsampleNum);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintU32(pstSubSample->u32ClearHeaderLen);
        HI_LOG_PrintU32(pstSubSample->u32PayLoadLen);
        HI_LOG_PrintU32(pstSubSample->u32PayloadPatternEncryptLen);
        HI_LOG_PrintU32(pstSubSample->u32PayloadPatternClearLen);
        HI_LOG_PrintU32(pstSubSample->u32PayloadPatternOffsetLen);
        HI_LOG_PrintFuncErr(mpi_cenc_decrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_CENCDecryptEx(HI_HANDLE hCipher, HI_U8 *pu8Key, HI_BOOL bOddKey,
                               HI_U32 u32NonSecInPhyAddr, HI_U32 u32SecOutPhyAddr, HI_U32 u32ByteLength,
                               HI_U32 u32FirstEncryptOffset,
                               CRYP_CIPHER_SUBSAMPLE_EX_S *pstSubSample, HI_U32 u32SubsampleNum)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstSubSample);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Key);
    HI_LOG_CHECK_PARAM(0 == u32NonSecInPhyAddr);
    HI_LOG_CHECK_PARAM(0 == u32SecOutPhyAddr);
    HI_LOG_CHECK_PARAM(CENC_SUBSAMPLE_MAX_NUM < u32SubsampleNum);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU32(u32NonSecInPhyAddr);
    HI_LOG_PrintU32(u32SecOutPhyAddr);
    HI_LOG_PrintU32(u32ByteLength);
    HI_LOG_PrintU32(u32FirstEncryptOffset);
    HI_LOG_PrintU32(u32SubsampleNum);

    ret = mpi_cenc_decrypt_ex(hCipher, pu8Key, bOddKey, u32NonSecInPhyAddr, u32SecOutPhyAddr,
            u32ByteLength, u32FirstEncryptOffset, pstSubSample, u32SubsampleNum);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintU32(pstSubSample->u32ClearHeaderLen);
        HI_LOG_PrintU32(pstSubSample->u32PayLoadLen);
        HI_LOG_PrintU32(pstSubSample->u32PayloadPatternEncryptLen);
        HI_LOG_PrintU32(pstSubSample->u32PayloadPatternClearLen);
        HI_LOG_PrintU32(pstSubSample->u32PayloadPatternOffsetLen);
        HI_LOG_PrintFuncErr(mpi_cenc_decrypt, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}
#endif

#ifdef HI_PRODUCT_ECC_SUPPORT
HI_S32 CRYP_CIPHER_RsaComputeCrtParams(HI_U32 u32NumBits, HI_U32 u32Exponent, HI_U8 *pu8P,
                               HI_U8 *pu8Q, HI_U8 *pu8DP, HI_U8 *pu8DQ, HI_U8 *pu8QP)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;

    HI_LOG_CHECK_PARAM(HI_NULL == pu8P);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Q);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8DP);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8DQ);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8QP);
    HI_LOG_CHECK_PARAM(0 == pu8P[0]);
    HI_LOG_CHECK_PARAM((RSA_KEY_BITWIDTH_1024 != u32NumBits / BYTE_BITS)
        && (RSA_KEY_BITWIDTH_2048 != u32NumBits / BYTE_BITS)
        && (RSA_KEY_BITWIDTH_3072 != u32NumBits / BYTE_BITS)
        && (RSA_KEY_BITWIDTH_4096 != u32NumBits / BYTE_BITS));
    HI_LOG_CHECK_PARAM((RSA_KEY_EXPONENT_VALUE1 != u32Exponent)
        && (RSA_KEY_EXPONENT_VALUE2 != u32Exponent));

    CHECK_CIPHER_OPEN();

    crypto_memset(&key, sizeof(key), 0, sizeof(key));

    key.public = HI_FALSE;
    key.klen = u32NumBits / BITS_IN_BYTE;
    key.e = u32Exponent;
    key.p = pu8P;
    key.q = pu8Q;
    key.dP = pu8DP;
    key.dQ = pu8DQ;
    key.qP = pu8QP;

    HI_LOG_PrintU32(u32NumBits);
    HI_LOG_PrintU32(u32Exponent);

    ret = mpi_rsa_compute_ctr(&key);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_compute_ctr, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_RsaGenKey(HI_U32 u32NumBits, HI_U32 u32Exponent, CRYP_CIPHER_RSA_PRI_KEY_S *pstRsaPriKey)
{
    HI_S32 ret = HI_FAILURE;
    cryp_rsa_key key;

    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaPriKey);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaPriKey->pu8N);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaPriKey->pu8E);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaPriKey->pu8D);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaPriKey->pu8P);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaPriKey->pu8Q);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaPriKey->pu8DP);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaPriKey->pu8DQ);
    HI_LOG_CHECK_PARAM(HI_NULL == pstRsaPriKey->pu8QP);
    HI_LOG_CHECK_PARAM((RSA_KEY_BITWIDTH_1024 != u32NumBits / BYTE_BITS)
        && (RSA_KEY_BITWIDTH_2048 != u32NumBits / BYTE_BITS)
        && (RSA_KEY_BITWIDTH_3072 != u32NumBits / BYTE_BITS)
        && (RSA_KEY_BITWIDTH_4096 != u32NumBits / BYTE_BITS));
    HI_LOG_CHECK_PARAM((RSA_KEY_EXPONENT_VALUE1 != u32Exponent)
        && (RSA_KEY_EXPONENT_VALUE2 != u32Exponent));

    CHECK_CIPHER_OPEN();

    crypto_memset(&key, sizeof(key), 0, sizeof(key));

    key.public = HI_FALSE;
    key.klen = u32NumBits / BITS_IN_BYTE;
    key.e = u32Exponent;
    key.N = pstRsaPriKey->pu8N;
    key.d = pstRsaPriKey->pu8D;
    key.p = pstRsaPriKey->pu8P;
    key.q = pstRsaPriKey->pu8Q;
    key.dP = pstRsaPriKey->pu8DP;
    key.dQ = pstRsaPriKey->pu8DQ;
    key.qP = pstRsaPriKey->pu8QP;

    HI_LOG_PrintU32(u32NumBits);
    HI_LOG_PrintU32(u32Exponent);

    ret = mpi_rsa_gen_key(&key);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_rsa_gen_key, ret);
        return ret;
    }

    pstRsaPriKey->u16NLen  = u32NumBits / BITS_IN_BYTE;
    pstRsaPriKey->u16DLen  = pstRsaPriKey->u16NLen;
    pstRsaPriKey->u16PLen  = pstRsaPriKey->u16NLen / 2;
    pstRsaPriKey->u16QLen  = pstRsaPriKey->u16NLen / 2;
    pstRsaPriKey->u16DPLen = pstRsaPriKey->u16NLen / 2;
    pstRsaPriKey->u16DQLen = pstRsaPriKey->u16NLen / 2;
    pstRsaPriKey->u16QPLen = pstRsaPriKey->u16NLen / 2;

    pstRsaPriKey->u16ELen = 0;

    if (RSA_KEY_EXPONENT_VALUE1 == u32Exponent)
    {
        pstRsaPriKey->u16ELen = 1;
        pstRsaPriKey->pu8E[0]  = (HI_U8)(u32Exponent) & 0xFF;
    }
    else
    {
        pstRsaPriKey->u16ELen = 3;
        pstRsaPriKey->pu8E[0]  = (HI_U8)(u32Exponent >> 16) & 0xFF;
        pstRsaPriKey->pu8E[1]  = (HI_U8)(u32Exponent >> 8) & 0xFF;
        pstRsaPriKey->pu8E[2]  = (HI_U8)(u32Exponent) & 0xFF;
    }

    HI_LOG_PrintU32(pstRsaPriKey->u16NLen);

    HI_UNF_FuncExit();
    return ret;
}

static HI_S32 CRYP_CIPHER_EccGetInfo(CRYP_CIPHER_ECC_PARAM_S *pstParams, ecc_param_t *pstEcc)
{
    HI_LOG_CHECK_PARAM(HI_NULL == pstEcc);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams->pu8p);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams->pu8b);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams->pu8a);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams->pu8GX);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams->pu8GY);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams->pu8n);
    HI_LOG_CHECK_PARAM(0 == pstParams->u32keySize);
    HI_LOG_CHECK_PARAM(ECDH_MAX_KEY_LEN < pstParams->u32keySize);

    crypto_memset(pstEcc, sizeof(ecc_param_t), 0, sizeof(ecc_param_t));

    pstEcc->p = pstParams->pu8p;
    pstEcc->b = pstParams->pu8b;
    pstEcc->a = pstParams->pu8a;
    pstEcc->Gx = pstParams->pu8GX;
    pstEcc->Gy = pstParams->pu8GY;
    pstEcc->n = pstParams->pu8n;
    pstEcc->ksize = pstParams->u32keySize;

    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_EcdhComputeKey(CRYP_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8PrivKey,
                                  HI_U8 *pu8OtherPubKeyX, HI_U8 *pu8OtherPubKeyY,
                                  HI_U8 *pu8SharedSecret)
{
    HI_S32 ret = HI_FAILURE;
    ecc_param_t ecc;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu8PrivKey);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8OtherPubKeyX);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8OtherPubKeyY);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8SharedSecret);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams);

    CHECK_CIPHER_OPEN();

    crypto_memset(&ecc, sizeof(ecc), 0, sizeof(ecc));

    ret = CRYP_CIPHER_EccGetInfo(pstParams, &ecc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYP_CIPHER_EccGetInfo, ret);
        return ret;
    }

    HI_LOG_PrintU32(ecc.ksize);
    HI_LOG_PrintU32(ecc.h);

    ret = mpi_ecdh_compute_key(&ecc, pu8PrivKey, pu8OtherPubKeyX, pu8OtherPubKeyY, pu8SharedSecret);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_ecdh_compute_key, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_EccGenKey(CRYP_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8InputPrivKey,
                             HI_U8 *pu8OutputPrivKey, HI_U8 *pu8PubKeyX, HI_U8 *pu8PubKeyY)
{
    HI_S32 ret = HI_FAILURE;
    ecc_param_t ecc;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu8OutputPrivKey);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8PubKeyX);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8PubKeyY);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(pstParams->u32keySize);
    HI_LOG_PrintU32(pstParams->u32h);

    ret = CRYP_CIPHER_EccGetInfo(pstParams, &ecc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYP_CIPHER_EccGetInfo, ret);
        return ret;
    }

    ret = mpi_ecc_gen_key(&ecc, pu8InputPrivKey, pu8OutputPrivKey, pu8PubKeyX, pu8PubKeyY);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_ecc_gen_key, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_EcdsaSign(CRYP_CIPHER_ECC_PARAM_S *pstParams, HI_U8 *pu8PrivKey,
                               CRYP_CIPHER_HASH_TYPE_E enShaType,
                               HI_U8 *pu8Message, HI_U32 u32MessageSize,
                               HI_U8 *pu8SigR, HI_U8 *pu8SigS)
{
    HI_S32 ret = HI_FAILURE;
    ecc_param_t ecc;
    HI_U32 hashid = 0;
    HI_U8 u8Hash[HASH_RESULT_MAX_SIZE];
    HI_U32 u32Hlen = 0;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu8PrivKey);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Message);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8SigR);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8SigS);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams);

    CHECK_CIPHER_OPEN();


    HI_LOG_PrintU32(enShaType);
    HI_LOG_PrintU32(u32MessageSize);
    HI_LOG_PrintU32(pstParams->u32keySize);
    HI_LOG_PrintU32(pstParams->u32h);

    ret = mpi_hash_start(&hashid, enShaType, HI_NULL, 0);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_start, ret);
        return ret;
    }

    ret = mpi_hash_update(hashid, pu8Message, u32MessageSize, HASH_CHUNCK_SRC_USER);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_update, ret);
        return ret;
    }

    ret = mpi_hash_finish(hashid, u8Hash, &u32Hlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_finish, ret);
        return ret;
    }

    crypto_memset (&ecc, sizeof(ecc), 0, sizeof(ecc));
    ret = CRYP_CIPHER_EccGetInfo(pstParams, &ecc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYP_CIPHER_EccGetInfo, ret);
        return ret;
    }

    HI_LOG_PrintU32(u32Hlen);

    ret = mpi_ecdsa_sign_hash(&ecc, pu8PrivKey, u8Hash, u32Hlen, pu8SigR, pu8SigS);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_ecdsa_sign_hash, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_EcdsaVerify(CRYP_CIPHER_ECC_PARAM_S *pstParams,
                                 HI_U8 *pu8PubKeyX, HI_U8 *pu8PubKeyY,
                                 CRYP_CIPHER_HASH_TYPE_E enShaType,
                                 HI_U8 *pu8Message, HI_U32 u32MessageSize,
                                 HI_U8 *pu8SigR, HI_U8 *pu8SigS)
{
    HI_S32 ret = HI_FAILURE;
    ecc_param_t ecc;
    HI_U32 hashid = 0;
    HI_U8 u8Hash[HASH_RESULT_MAX_SIZE];
    HI_U32 u32Hlen = 0;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu8PubKeyX);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8PubKeyY);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Message);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8SigR);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8SigS);
    HI_LOG_CHECK_PARAM(HI_NULL == pstParams);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(enShaType);
    HI_LOG_PrintU32(u32MessageSize);
    HI_LOG_PrintU32(pstParams->u32keySize);
    HI_LOG_PrintU32(pstParams->u32h);

    ret = mpi_hash_start(&hashid, enShaType, HI_NULL, 0);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_start, ret);
        return ret;
    }

    ret = mpi_hash_update(hashid, pu8Message, u32MessageSize, HASH_CHUNCK_SRC_USER);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_update, ret);
        return ret;
    }

    ret = mpi_hash_finish(hashid, u8Hash, &u32Hlen);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_hash_finish, ret);
        return ret;
    }

    HI_LOG_PrintU32(u32Hlen);

    crypto_memset (&ecc, sizeof(ecc), 0, sizeof(ecc));
    ret = CRYP_CIPHER_EccGetInfo(pstParams, &ecc);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(CRYP_CIPHER_EccGetInfo, ret);
        return ret;
    }

    ret = mpi_ecdsa_verify_hash(&ecc, pu8PubKeyX, pu8PubKeyY, u8Hash, u32Hlen, pu8SigR, pu8SigS);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_ecdsa_verify_hash, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}
#endif

#if defined(HI_PLATFORM_TYPE_LINUX)
/******************************* Compat Code *******************************/
/** \addtogroup      cipher, these api are compatible with old interface */
/** @{*/  /** <!-- [mpi]*/
/*
*/
HI_S32 HI_MPI_CIPHER_RsaVerify(CRYP_CIPHER_RSA_VERIFY_S *pstRsaVerify,
                               HI_U8 *pu8InData, HI_U32 u32InDataLen,
                               HI_U8 *pu8HashData,
                               HI_U8 *pu8InSign, HI_U32 u32InSignLen)
{
    return CRYP_CIPHER_RsaVerify(pstRsaVerify, pu8InData, u32InDataLen,
                               pu8HashData, pu8InSign, u32InSignLen);
}

HI_S32 HI_MPI_CIPHER_GetRandomNumber(HI_U32 *pu32RandomNumber, HI_U32 u32TimeOutUs)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pu32RandomNumber);

    ret = mpi_trng_get_random((u8*)pu32RandomNumber, WORD_WIDTH, u32TimeOutUs);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 HI_MPI_CIPHER_Init(HI_VOID)
{
    return CRYP_CIPHER_Init();
}

HI_S32 HI_MPI_CIPHER_DeInit(HI_VOID)
{
    return CRYP_CIPHER_DeInit();
}

HI_S32 HI_MPI_CIPHER_CbcMac_Auth(HI_U8 *pu8RefCbcMac, HI_U32 u32AppLen)
{
    HI_LOG_ERROR("HI_MPI_CIPHER_CbcMac_Auth is unsupported!\n");
    return HI_FAILURE;
}

HI_S32 CRYP_CIPHER_CalcMAC(HI_HANDLE hCipherHandle, HI_U8 *pInputData, HI_U32 u32InputDataLen,
                           HI_U8 *pOutputMAC, HI_BOOL bIsLastBlock)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pInputData);
    HI_LOG_CHECK_PARAM(HI_NULL == pOutputMAC);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(hCipherHandle);
    HI_LOG_PrintU32(u32InputDataLen);
    HI_LOG_PrintU32(bIsLastBlock);

    ret = mpi_symc_aes_cmac(hCipherHandle, pInputData, u32InputDataLen, pOutputMAC, bIsLastBlock);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_aes_cmac, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return ret;
}

#elif defined(HI_PLATFORM_TYPE_TEE)

HI_S32 CRYP_CIPHER_EncryptMultiAsyn(HI_HANDLE hCipher, CRYP_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    s32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    CHECK_CIPHER_OPEN();

    HI_LOG_CHECK_PARAM(HI_NULL == pstDataPkg);
    HI_LOG_CHECK_PARAM(0x00 == u32DataPkgNum);
    HI_LOG_CHECK_PARAM(CIPHER_MAX_MULTIPAD_NUM < u32DataPkgNum);

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU32(pstDataPkg->u32SrcPhyAddr);
    HI_LOG_PrintU32(pstDataPkg->u32DestPhyAddr);
    HI_LOG_PrintU32(pstDataPkg->u32ByteLength);
    HI_LOG_PrintU32(pstDataPkg->bOddKey);
    HI_LOG_PrintU32(u32DataPkgNum);

    ret = mpi_symc_crypto_multi_asyn(hCipher, pstDataPkg, u32DataPkgNum, SYMC_OPERATION_ENCRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_crypto_multi_asyn, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_DecryptMultiAsyn(HI_HANDLE hCipher, CRYP_CIPHER_DATA_S *pstDataPkg, HI_U32 u32DataPkgNum)
{
    s32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    CHECK_CIPHER_OPEN();

    HI_LOG_CHECK_PARAM(HI_NULL == pstDataPkg);
    HI_LOG_CHECK_PARAM(0x00 == u32DataPkgNum);
    HI_LOG_CHECK_PARAM(CIPHER_MAX_MULTIPAD_NUM < u32DataPkgNum);

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU32(pstDataPkg->u32SrcPhyAddr);
    HI_LOG_PrintU32(pstDataPkg->u32DestPhyAddr);
    HI_LOG_PrintU32(pstDataPkg->u32ByteLength);
    HI_LOG_PrintU32(pstDataPkg->bOddKey);
    HI_LOG_PrintU32(u32DataPkgNum);

    ret = mpi_symc_crypto_multi_asyn(hCipher, pstDataPkg, u32DataPkgNum, SYMC_OPERATION_DECRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_crypto_multi_asyn, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_WaitDone(HI_HANDLE hCipher, HI_U32 u32TimeOut)
{
    s32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(hCipher);
    HI_LOG_PrintU32(u32TimeOut);

    ret = mpi_symc_crypto_waitdone(hCipher, u32TimeOut);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_symc_crypto_waitdone, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_PBKDF2(CRYP_CIPHER_PBKDF2_S *pstInfo, HI_U8 *pu8Output)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstInfo);
    HI_LOG_CHECK_PARAM(HI_NULL == pu8Output);

    CHECK_CIPHER_OPEN();

    ret = mpi_pbkdf_hmac256(pstInfo->password, pstInfo->plen, pstInfo->salt,
        pstInfo->slen, pstInfo->iteration_count, pstInfo->key_length, pu8Output);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_pbkdf_hmac256, ret);
        return ret;
    }

    HI_UNF_FuncExit();

    return ret;
}

HI_S32 CRYP_CIPHER_SetUsageRule(HI_HANDLE hCipher, CRYP_CIPHER_UR_S *pstCipherUR)
{
    HI_S32 ret = HI_FAILURE;

    HI_UNF_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == pstCipherUR);

    CHECK_CIPHER_OPEN();

    HI_LOG_PrintU32(hCipher);

    ret = mpi_set_usage_rule(hCipher, pstCipherUR);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(mpi_set_usage_rule, ret);
        return ret;
    }

    HI_UNF_FuncExit();
    return HI_SUCCESS;
}

HI_S32 CRYP_CIPHER_Test(HI_U32 u32Cmd, HI_VOID *pu8Param, HI_U32 u32ParamSize)
{
    return mpi_crypto_self_test(u32Cmd, pu8Param, u32ParamSize);
}

#ifdef EXPORT_SYMBOL_SUPPORT
EXPORT_SYMBOL(CRYP_CIPHER_Init);
EXPORT_SYMBOL(CRYP_CIPHER_DeInit);
EXPORT_SYMBOL(CRYP_CIPHER_Encrypt);
EXPORT_SYMBOL(CRYP_CIPHER_Decrypt);
EXPORT_SYMBOL(CRYP_CIPHER_EncryptMulti);
EXPORT_SYMBOL(CRYP_CIPHER_DecryptMulti);
EXPORT_SYMBOL(CRYP_CIPHER_ConfigHandle);
EXPORT_SYMBOL(CRYP_CIPHER_CreateHandle);
EXPORT_SYMBOL(CRYP_CIPHER_DestroyHandle);
EXPORT_SYMBOL(CRYP_CIPHER_GetHandleConfig);
EXPORT_SYMBOL(CRYP_CIPHER_GetRandomNumber);
EXPORT_SYMBOL(CRYP_CIPHER_GetMultiRandomBytes);
EXPORT_SYMBOL(CRYP_CIPHER_HashInit);
EXPORT_SYMBOL(CRYP_CIPHER_HashUpdate);
EXPORT_SYMBOL(CRYP_CIPHER_HashFinal);
EXPORT_SYMBOL(CRYP_CIPHER_RsaPublicEncrypt);
EXPORT_SYMBOL(CRYP_CIPHER_RsaPrivateDecrypt);
EXPORT_SYMBOL(CRYP_CIPHER_RsaPrivateEncrypt);
EXPORT_SYMBOL(CRYP_CIPHER_RsaPublicDecrypt);
EXPORT_SYMBOL(CRYP_CIPHER_RsaSign);
EXPORT_SYMBOL(CRYP_CIPHER_RsaVerify);
EXPORT_SYMBOL(CRYP_CIPHER_ConfigHandleEx);
EXPORT_SYMBOL(CRYP_CIPHER_EncryptMultiAsyn);
EXPORT_SYMBOL(CRYP_CIPHER_DecryptMultiAsyn);
EXPORT_SYMBOL(CRYP_CIPHER_WaitDone);
EXPORT_SYMBOL(CRYP_CIPHER_GetTag);
EXPORT_SYMBOL(CRYP_CIPHER_Sm2Sign);
EXPORT_SYMBOL(CRYP_CIPHER_Sm2Verify);
EXPORT_SYMBOL(CRYP_CIPHER_Sm2Encrypt);
EXPORT_SYMBOL(CRYP_CIPHER_Sm2Decrypt);
EXPORT_SYMBOL(CRYP_CIPHER_Sm2GenKey);
EXPORT_SYMBOL(CRYP_CIPHER_PBKDF2);
EXPORT_SYMBOL(CRYP_CIPHER_Test);
EXPORT_SYMBOL(CRYP_CIPHER_CENCDecrypt);
EXPORT_SYMBOL(CRYP_CIPHER_CENCDecryptEx);
EXPORT_SYMBOL(CRYP_CIPHER_DhComputeKey);
EXPORT_SYMBOL(CRYP_CIPHER_DhGenKey);
EXPORT_SYMBOL(CRYP_CIPHER_SetUsageRule);
#endif

#endif

/** @}*/  /** <!-- ==== Compat Code end ====*/
