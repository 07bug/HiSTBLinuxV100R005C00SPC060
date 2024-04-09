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
#include "drv_symc.h"
#include "hi_drv_cipher.h"

#define HDCP_KEY_FLAG_MASK  0xC0
#define HDCP_KEY_FLAG_HISI  0x80

static HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S s_stFlashHdcpKey;
static HI_BOOL s_bIsLoadHdcpKey = HI_FALSE;

HI_S32 HI_DRV_CIPHER_CreateHandle(CIPHER_HANDLE_S *pstCIHandle, HI_VOID *file)
{
    HI_LOG_CHECK_PARAM(HI_NULL == pstCIHandle);
    return kapi_symc_create(&pstCIHandle->hCIHandle, pstCIHandle->stCipherAtts.enCipherType);
}

HI_S32 HI_DRV_CIPHER_ConfigChn(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S *pstCtrl)
{
    HI_LOG_CHECK_PARAM(HI_NULL == pstCtrl);
    return kapi_symc_config(hCipher,
        pstCtrl->bKeyByCA, pstCtrl->enAlg,
        pstCtrl->enWorkMode, pstCtrl->enBitWidth, pstCtrl->enKeyLen, 0,
        (HI_U8*)pstCtrl->u32Key, HI_NULL, (HI_U8*)pstCtrl->u32IV,
        AES_IV_SIZE, pstCtrl->stChangeFlags.bit1IV, ADDR_NULL, 0, 0);
}

HI_S32 HI_DRV_CIPHER_DestroyHandle(HI_HANDLE hCipherchn)
{
    return kapi_symc_destroy(hCipherchn);
}

HI_S32 HI_DRV_CIPHER_Encrypt(CIPHER_DATA_S *pstCIData)
{
    compat_addr input;
    compat_addr output;
    HI_LOG_CHECK_PARAM(HI_NULL == pstCIData);

    ADDR_U64(input) = pstCIData->ScrPhyAddr;
    ADDR_U64(output) = pstCIData->DestPhyAddr;

    return kapi_symc_crypto(pstCIData->CIHandle, input, output,
        pstCIData->u32DataLength, SYMC_OPERATION_ENCRYPT, HI_FALSE, HI_FALSE);
}

HI_S32 HI_DRV_CIPHER_Decrypt(CIPHER_DATA_S *pstCIData)
{
    compat_addr input;
    compat_addr output;

    HI_LOG_CHECK_PARAM(HI_NULL == pstCIData);

    ADDR_U64(input) = pstCIData->ScrPhyAddr;
    ADDR_U64(output) = pstCIData->DestPhyAddr;

    return kapi_symc_crypto(pstCIData->CIHandle, input, output,
        pstCIData->u32DataLength, SYMC_OPERATION_DECRYPT, HI_FALSE, HI_FALSE);
}

HI_S32 HI_DRV_CIPHER_GetRandomNumber(CIPHER_RNG_S *pstRNG)
{
    HI_LOG_CHECK_PARAM(HI_NULL == pstRNG);
    return kapi_trng_get_random(&pstRNG->u32RNG, pstRNG->u32TimeOutUs);
}

s32 HI_DRV_CIPHER_SetIV(HI_HANDLE hCIHandle,  HI_U8 *pu8IV, HI_U32 u32IVLen)
{
    return kapi_symc_setiv(hCIHandle, pu8IV, u32IVLen);
}

HI_S32 HI_DRV_CIPHER_SoftReset(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    drv_symc_suspend();
    ret = drv_symc_resume();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CIPHER("drv symc resume failed!\n");
        return ret;
    }

    return HI_SUCCESS;
}

#ifdef HI_PRODUCT_HDCP22_SUPPORT
static unsigned int TwoByteCRC(unsigned char *in, int in_len)
{
    unsigned int check_sum = 0xA3C5;
    unsigned int index;
    unsigned int srcChar, nCksumTemp, nCksumTemp7, nCksumTemp16, crc_bit0;

    for(index = 0; index < in_len; index++)
    {
        srcChar = in[index];
        nCksumTemp = check_sum ^ srcChar;

        nCksumTemp7 = (0x0080 & nCksumTemp) >> 7;
        nCksumTemp16 = (0x10000 & nCksumTemp) >> 16;
        crc_bit0 = nCksumTemp7 ^ nCksumTemp16 ^ 1;

        check_sum = 0x1FFFF & ((nCksumTemp << 1) | crc_bit0);
    }


    for(index = 0; index < 8; index++)
    {
        nCksumTemp7 = (0x0080 & check_sum) >> 7;
        nCksumTemp16 = (0x10000 & check_sum) >> 16;
        crc_bit0 = nCksumTemp7 ^ nCksumTemp16 ^ 1;

        check_sum = 0x1FFFF & ((check_sum << 1) | crc_bit0);
    }

    return check_sum & 0xFFFF;
}
#endif

HI_S32 HI_DRV_CIPHER_LoadHdcpKey(HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *pstFlashHdcpKey)
{
    hdcp_rootkey_sel keysel = HDCP_KEY_SEL_OTP;
    HI_U8 tmp = 0;
    HI_U32 keylen = 0;
    hdmi_ram_sel ramsel = HDMI_RAM_SEL_TX_14;

    if( HI_NULL == pstFlashHdcpKey)
    {
        HI_ERR_CIPHER("NULL Pointer, Invalid param input!\n");
        return HI_FAILURE;
    }

    tmp = pstFlashHdcpKey->u8Key[0] & HDCP_KEY_FLAG_MASK;
    if( HDCP_KEY_FLAG_HISI == tmp)
    {
        keysel = HDCP_KEY_SEL_HISI;
    }

    if (HDCP_KEY_CHIP_FILE_SIZE == pstFlashHdcpKey->u32KeyLen)    /* hdcp 1.4 */
    {
        if(HI_DRV_HDCP_VERIOSN_1x != pstFlashHdcpKey->enHDCPVersion)
        {
            HI_ERR_CIPHER("Invalid HDCP ver %d!\n", pstFlashHdcpKey->enHDCPVersion);
            return HI_FAILURE;
        }

        if(HI_DRV_HDCPKEY_RX0 == pstFlashHdcpKey->enHDCPKeyType)
        {
            ramsel = HDMI_RAM_SEL_RX_14;
        }

        /* check B1: 0x00 B2~B3: HI */
        if((pstFlashHdcpKey->u8Key[1] != 0x00)
            || (pstFlashHdcpKey->u8Key[2] != 'H')
            || (pstFlashHdcpKey->u8Key[3] != 'I'))
        {
            HI_ERR_CIPHER("Invalid head of B1~B3!\n");
            return HI_FAILURE;
        }
        keylen = HDCP_KEY_RAM_SIZE;
    }
#ifdef HI_PRODUCT_HDCP22_SUPPORT
    else if (HDMIRX20_HDCP22_KEY_PACKAGE_LEN == pstFlashHdcpKey->u32KeyLen) /* hdcp 2.2 */
    {
        if(HI_DRV_HDCP_VERIOSN_2x != pstFlashHdcpKey->enHDCPVersion)
        {
            HI_ERR_CIPHER("Invalid HDCP ver %d!\n", pstFlashHdcpKey->enHDCPVersion);
            return HI_FAILURE;
        }

        /* verify checksum */
        tmp = TwoByteCRC(&pstFlashHdcpKey->u8Key[4], HDMIRX20_HDCP22_KEY_PACKAGE_VALID_LEN);
        if (memcmp(&tmp, &pstFlashHdcpKey->u8Key[2], 2) != 0)
        {
            HI_ERR_CIPHER("HDCP KEY head CRC compare failed!");
            return HI_FAILURE;
        }
        keylen = HDMIRX20_HDCP22_KEY_PACKAGE_VALID_LEN;
        ramsel = HDMI_RAM_SEL_RX_22;
    }
#endif
    else
    {
        HI_ERR_CIPHER("Invalid key len: 0x%x!\n", pstFlashHdcpKey->u32KeyLen);
        return HI_FAILURE;
    }

    /* save the hdcp key, then recover it while system resume */
    crypto_memcpy(&s_stFlashHdcpKey, sizeof(s_stFlashHdcpKey), pstFlashHdcpKey, sizeof(s_stFlashHdcpKey));
    s_bIsLoadHdcpKey = HI_TRUE;

    return kapi_hdcp_encrypt(keysel, ramsel, HI_NULL,
        (HI_U32*)&pstFlashHdcpKey->u8Key[4], HI_NULL, keylen,
        SYMC_OPERATION_DECRYPT);
}

s32 crypto_recover_hdcp_key(void)
{
    if (HI_TRUE == s_bIsLoadHdcpKey)
    {
        return HI_DRV_CIPHER_LoadHdcpKey(&s_stFlashHdcpKey);
    }

    return HI_SUCCESS;
}

HI_VOID HI_DRV_CIPHER_SetHdmiReadClk(HI_DRV_HDCPKEY_TYPE_E enHDCPKeyType)
{
    CRYPTO_UNUSED(enHDCPKeyType);

    return;
}

HI_S32 Cipher_ConfigHandle(HI_HANDLE hCipher, CRYP_CIPHER_CTRL_S* pstCtrl)
{
    HI_LOG_CHECK_PARAM(HI_NULL == pstCtrl);
    return kapi_symc_config(hCipher, pstCtrl->bKeyByCA,
                           pstCtrl->enAlg, pstCtrl->enWorkMode, pstCtrl->enBitWidth,
                           pstCtrl->enKeyLen, 0, (u8*)pstCtrl->u32Key,
                           (u8*)pstCtrl->u32Key, (u8*)pstCtrl->u32IV, AES_IV_SIZE,
                           pstCtrl->stChangeFlags.bit1IV,
                           ADDR_NULL, 0, 0);
}

HI_S32 Cipher_GetHandleConfig(HI_HANDLE hCipher, CRYP_CIPHER_CTRL_S* pstCtrl)
{
    HI_LOG_CHECK_PARAM(HI_NULL == pstCtrl);
    return kapi_symc_get_config(hCipher, pstCtrl);
}

HI_S32 Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    compat_addr in, out;

    ADDR_L32(in) = u32SrcPhyAddr;
    ADDR_L32(out) = u32DestPhyAddr;

    return kapi_symc_crypto(hCipher, in, out,
        u32ByteLength, SYMC_OPERATION_DECRYPT, HI_FALSE, true);
}

HI_S32 Cenc_Cipher_Decrypt(HI_HANDLE hCipher, HI_BOOL bOddKey, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength)
{
    compat_addr in, out;

    ADDR_L32(in) = u32SrcPhyAddr;
    ADDR_L32(out) = u32DestPhyAddr;

    return kapi_symc_crypto(hCipher, in, out,
        u32ByteLength, SYMC_OPERATION_DECRYPT, bOddKey, true);
}

/* adapt for opentv */
HI_S32 HI_DRV_CIPHER_ConfigChnEx(CIPHER_CONFIG_CTRL_EX *pConfig)
{
    compat_addr APhyAddr;

    HI_LOG_CHECK_PARAM(HI_NULL == pConfig);

    ADDR_U64(APhyAddr) = pConfig->u32APhyAddr;

    return kapi_symc_config(pConfig->CIHandle,/* handle or softid*/
                                pConfig->bKeyByCA,
                                pConfig->enAlg,
                                pConfig->enWorkMode,
                                pConfig->enBitWidth,
                                pConfig->enKeyLen,
                                pConfig->enSm1Round,
                                (HI_U8 *)pConfig->u32Key, (HI_U8 *)pConfig->u32OddKey,
                                (HI_U8 *)pConfig->u32IV, pConfig->u32IVLen, pConfig->stChangeFlags.bit1IV,
                                APhyAddr, pConfig->u32ALen, pConfig->u32TagLen);
}

/* adapt for pm */
HI_S32 HI_DRV_CIPHER_HashStart(HI_HANDLE *hCipher, CRYP_CIPHER_HASH_TYPE_E type,
                    u8 *key, u32 keylen)
{
    return kapi_hash_start(hCipher, type, key, keylen);
}

HI_S32 HI_DRV_CIPHER_HashUpdate(HI_HANDLE hCipher, u8 *input, u32 length)
{
    return kapi_hash_update(hCipher, input, length, HASH_CHUNCK_SRC_LOCAL);
}

HI_S32 HI_DRV_CIPHER_HashFinish(HI_HANDLE hCipher, u8 *hash, u32 *hashlen)
{
    return kapi_hash_finish(hCipher, hash, hashlen);
}

EXPORT_SYMBOL(HI_DRV_CIPHER_ConfigChnEx);
EXPORT_SYMBOL(HI_DRV_CIPHER_DestroyHandle);
EXPORT_SYMBOL(HI_DRV_CIPHER_Encrypt);
EXPORT_SYMBOL(HI_DRV_CIPHER_CreateHandle);
EXPORT_SYMBOL(HI_DRV_CIPHER_Decrypt);
EXPORT_SYMBOL(HI_DRV_CIPHER_HashStart);
EXPORT_SYMBOL(HI_DRV_CIPHER_HashUpdate);
EXPORT_SYMBOL(HI_DRV_CIPHER_HashFinish);
