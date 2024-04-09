/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : cmd_advca.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2017-02-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef HI_ADVCA_FUNCTION_RELEASE

#ifdef KLAD_CMD_TEST

#include "hi_common.h"
#include "command.h"
#include "exports.h"
#include "hi_unf_cipher.h"
#include "hi_unf_klad.h"
#include "hi_unf_klad_common_ca.h"

#define ST_KLAD_ASSERT(func) \
    do { \
        HI_S32 ret = HI_FAILURE; \
        ret = func;  \
        if (HI_SUCCESS != ret) { \
            printf("call %s failed. [%#x]\n", # func, ret); \
            return ret; \
        } \
    } while (0)

#define ST_KLAD_MCIPHER_DECLARE_VAR \
    HI_U32 level = 0; \
    HI_HANDLE klad = HI_INVALID_HANDLE; \
    HI_HANDLE mcipher = HI_INVALID_HANDLE; \
    HI_U32 klad_type = HI_INVALID_HANDLE; \
    HI_UNF_KLAD_ALG_TYPE_E alg; \
    HI_UNF_CIPHER_ALG_E cipher_alg = HI_UNF_CIPHER_ALG_AES; \
    HI_UNF_KLAD_ATTR_S attr;

#define ST_KLAD_BASIC_MCIPHER_DECLARE_FUNC \
    attr.enAlg = alg; \
    attr.enEngine = HI_UNF_KLAD_TARGET_ENGINE_FIXED; \
    ST_KLAD_ASSERT(KLAD_CreateWithMCipher(klad_type, &klad, &attr, &mcipher, &level)); \
    ST_KLAD_ASSERT(KLAD_SetKey(klad, level)); \
    ST_KLAD_ASSERT(KLAD_VerifyWithMCipher(klad_type, mcipher, alg, cipher_alg)); \
    ST_KLAD_ASSERT(KLAD_DestroyWithMCipher(klad, mcipher)); \

//***********************************************************************************************************************
static HI_U8 plainttext[16]                  = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x00};

static HI_U8  RESULT_Common_CA_R2R_TDES[16]   = {0xb1,0x71,0xf5,0x0a,0xbb,0x12,0x94,0x4f,0x72,0x32,0x6b,0xbd,0xc2,0x47,0x7e,0x74};

//***********************************************************************************************************************
static HI_S32 KLAD_SetKey(HI_HANDLE klad, HI_U32 level)
{
    HI_U32 i = 0;
    HI_UNF_KLAD_CONTENT_KEY_S conent_key =
            {
                HI_FALSE,
                {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff}
            };
    HI_UNF_KLAD_SESSION_KEY_S session_key[] =
        {
            {
                HI_UNF_KLAD_LEVEL1,
                {0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0}
            },
            {
                HI_UNF_KLAD_LEVEL2,
                {0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0, 0x01}
            },
            {
                HI_UNF_KLAD_LEVEL3,
                {0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0, 0x01, 0x12}
            },
            {
                HI_UNF_KLAD_LEVEL4,
                {0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0, 0x01, 0x12, 0x23}
            },
        };

    if(level > 1)
    {
        for (i=0; i<level-1; i++)
        {
            ST_KLAD_ASSERT(HI_UNF_KLAD_SetSessionKey(klad, &(session_key[i])));
        }

   }
    ST_KLAD_ASSERT(HI_UNF_KLAD_SetContentKey(klad, &conent_key));

    return HI_SUCCESS;
}

static HI_S32 KLAD_CreateWithMCipher(HI_U32 klad_type, HI_HANDLE *klad, HI_UNF_KLAD_ATTR_S *attr, HI_HANDLE *mcipher, HI_U32 *level)
{
    HI_UNF_CIPHER_ATTS_S attr_mcipher;

    ST_KLAD_ASSERT(HI_UNF_KLAD_Init());
    ST_KLAD_ASSERT(HI_UNF_KLAD_Create(klad));

    attr->u32KladType = klad_type;
    ST_KLAD_ASSERT(HI_UNF_KLAD_SetAttr(*klad, attr));

    ST_KLAD_ASSERT(HI_UNF_CIPHER_Init());
    attr_mcipher.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    ST_KLAD_ASSERT(HI_UNF_CIPHER_CreateHandle(mcipher, &attr_mcipher));

    ST_KLAD_ASSERT(HI_UNF_KLAD_Attach(*klad, *mcipher));

    // only support max level
    switch (klad_type)
    {
        case HI_UNF_KLAD_COMMON_CA_TYPE_R2R:    *level = 3;break;
        default:
            break;
    }

    return HI_SUCCESS;
}

static HI_S32 KLAD_MCipherConfig
(
    HI_BOOL bCA,
    HI_HANDLE cipher,
    HI_UNF_CIPHER_ALG_E alg,
    HI_UNF_CIPHER_WORK_MODE_E mode,
    HI_U8 *IV,
    HI_U8 *key
)
{
    HI_UNF_CIPHER_CTRL_S CipherCtrl;

    memset(&CipherCtrl, 0x0, sizeof (HI_UNF_CIPHER_CTRL_S));
    CipherCtrl.bKeyByCA = bCA;
    CipherCtrl.enAlg    = alg;
    CipherCtrl.enWorkMode = mode;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    if (alg == HI_UNF_CIPHER_ALG_AES)
    {
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    }
    else
    {
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
    }

    if (HI_UNF_CIPHER_WORK_MODE_ECB != mode)
    {
        CipherCtrl.stChangeFlags.bit1IV = 1;
        memcpy(CipherCtrl.u32IV, IV, 16);
    }

    if (HI_FALSE == bCA && key != NULL)
    {
        memcpy(CipherCtrl.u32Key, key, 16);
    }

    ST_KLAD_ASSERT(HI_UNF_CIPHER_ConfigHandle(cipher, &CipherCtrl));

    return HI_SUCCESS;
}

static HI_S32 KLAD_MCipherEncrypt(HI_HANDLE cipher, HI_U8 *input, HI_U8 *output, HI_U32 length)
{
    ST_KLAD_ASSERT(HI_UNF_CIPHER_Encrypt(cipher, (HI_U32)input, (HI_U32)output, length));

    return HI_SUCCESS;
}

static HI_S32 KLAD_MCipherVerify(HI_U32 klad_type, HI_U8 *verifydata, HI_U32 length, HI_UNF_KLAD_ALG_TYPE_E alg)
{
    HI_U32 i = 0;
    HI_U8 *result = HI_NULL;

    switch (klad_type)
    {
        case HI_UNF_KLAD_COMMON_CA_TYPE_R2R:
            result = RESULT_Common_CA_R2R_TDES;
            break;

        default:
        {
            printf("Not support klad type: [%#x]\n", klad_type);
            return HI_FAILURE;
        }
    }

    if (0 == memcmp(verifydata, result, 16))
    {
        printf("verfiy success.\n");
        return HI_SUCCESS;
    }
    else
    {
        printf("verfiy failed.\n");
        printf("expected result: ");
        for (i=0; i<16; i++)
        {
            printf("0x%02x,", result[i]);
        }
        printf("\nactual result  : ");
        for (i=0; i<16; i++)
        {
            printf("0x%02x,", verifydata[i]);
        }
        printf("\n");
        return HI_FAILURE;
    }
}

static HI_S32 KLAD_VerifyWithMCipher(HI_U32 klad_type, HI_HANDLE mcipher, HI_UNF_KLAD_ALG_TYPE_E alg, HI_UNF_CIPHER_ALG_E cipher_alg)
{
    HI_U8 output[16] = {0};

    ST_KLAD_ASSERT(KLAD_MCipherConfig(HI_TRUE, mcipher, cipher_alg, HI_UNF_CIPHER_WORK_MODE_ECB, NULL, NULL));

    ST_KLAD_ASSERT(KLAD_MCipherEncrypt(mcipher, plainttext, output, 16));

    ST_KLAD_ASSERT(KLAD_MCipherVerify(klad_type, output, 16, alg));

    return HI_SUCCESS;
}

static HI_S32 KLAD_DestroyWithMCipher(HI_HANDLE klad, HI_HANDLE mcipher)
{
    ST_KLAD_ASSERT(HI_UNF_KLAD_Detach(klad, mcipher));

    ST_KLAD_ASSERT(HI_UNF_CIPHER_DestroyHandle(mcipher));
    ST_KLAD_ASSERT(HI_UNF_CIPHER_DeInit());

    ST_KLAD_ASSERT(HI_UNF_KLAD_Destroy(klad));
    ST_KLAD_ASSERT(HI_UNF_KLAD_DeInit());

    return HI_SUCCESS;
}

//***********************************************************************************************************************

HI_S32 ST_KLAD_MCipher_Common_CA_R2R_TDES(HI_VOID)
{
    ST_KLAD_MCIPHER_DECLARE_VAR;

    klad_type = HI_UNF_KLAD_COMMON_CA_TYPE_R2R;
    alg = HI_UNF_KLAD_ALG_TYPE_TDES;

    attr.enAlg = alg;
    attr.enEngine = HI_UNF_KLAD_TARGET_ENGINE_FIXED;
    ST_KLAD_ASSERT(KLAD_CreateWithMCipher(klad_type, &klad, &attr, &mcipher, &level));
    ST_KLAD_ASSERT(KLAD_SetKey(klad, level));
    ST_KLAD_ASSERT(KLAD_VerifyWithMCipher(klad_type, mcipher, alg, cipher_alg));
    ST_KLAD_ASSERT(KLAD_DestroyWithMCipher(klad, mcipher));

    return HI_SUCCESS;
}

HI_S32 KLAD_TEST_MCipher_Common_CA_R2R_TDES(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    printf("---[%s.%d]---\n", __FUNCTION__, __LINE__);
    ST_KLAD_MCipher_Common_CA_R2R_TDES();
    return HI_SUCCESS;
}
U_BOOT_CMD(klad_commonca_r2r,2,1,KLAD_TEST_MCipher_Common_CA_R2R_TDES,"Test common ca r2r key ladder","");

#endif /* #ifdef KLAD_CMD_TEST */
#endif /* #ifndef HI_ADVCA_FUNCTION_RELEASE */

