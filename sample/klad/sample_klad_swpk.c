/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_ca_crypto.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hi_type.h"
#include "hi_common.h"
#include "hi_unf_cipher.h"
#include "parse_config_file.h"
#include "hi_unf_klad.h"
#include "hi_unf_klad_common_ca.h"

/***************************** Macro Definition ******************************/

#define TEXT_LEN    (1024)
#define KEY_LEN     (16)

#define PLAINTEXT_TAG     "PLAINTTEXT"
#define SESSIONKEY1_TAG   "SESSIONKEY1"
#define SESSIONKEY2_TAG   "SESSIONKEY2"
#define SESSIONKEY3_TAG   "SESSIONKEY3"
#define SESSIONKEY4_TAG   "SESSIONKEY4"
#define CONTENTKEY_TAG    "CONTENTKEY"
/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/
HI_S32             g_CwType = 0;

HI_U8 g_PlainText[TEXT_LEN]           = {0};
HI_U8 g_sessionkey1[KEY_LEN]          = {0};
HI_U8 g_sessionkey2[KEY_LEN]          = {0};
HI_U8 g_sessionkey3[KEY_LEN]          = {0};
HI_U8 g_sessionkey4[KEY_LEN]          = {0};
HI_U8 g_contentkey[KEY_LEN]           = {0};
HI_U8 g_IV[KEY_LEN]                   = {0};
HI_U8 g_clearContentkey[KEY_LEN]      = {0};

HI_U32 g_PlainTextLen                    = 0;
HI_U32 g_KladType;

HI_UNF_KLAD_LEVEL_E           g_kladLevel = HI_UNF_KLAD_LEVEL_BUTT;
HI_UNF_KLAD_ALG_TYPE_E        g_kladAlg  = HI_UNF_KLAD_ALG_TYPE_BUTT;
HI_UNF_CIPHER_ALG_E           g_cipherAlg = HI_UNF_CIPHER_ALG_BUTT;
HI_UNF_CIPHER_WORK_MODE_E     g_cipherMode = HI_UNF_CIPHER_WORK_MODE_BUTT;

#define ST_KLAD_ASSERT(func) \
    do { \
        HI_S32 ret = HI_FAILURE; \
        ret = func;  \
        if (HI_SUCCESS != ret) { \
            printf("call %s failed. [%#x]\n", # func, ret); \
            return ret; \
        } \
    } while (0)

/******************************* API declaration *****************************/

static HI_S32 KLAD_MCipherEncrypt(HI_HANDLE cipher, HI_U8 *input, HI_U8 *output, HI_U32 length)
{
    HI_S32 Ret;
    HI_MMZ_BUF_S PlainBuf,EncrytedBuf;

    strcpy(PlainBuf.bufname,"plain_text");
    PlainBuf.bufsize = 0x1000;
    PlainBuf.overflow_threshold = 100;
    PlainBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&PlainBuf);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_MMZ_Malloc failed:%x\n",Ret);
        return HI_FAILURE;
    }

    strcpy(EncrytedBuf.bufname,"encrypted_text");
    EncrytedBuf.bufsize = 0x1000;
    EncrytedBuf.overflow_threshold = 100;
    EncrytedBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&EncrytedBuf);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_MMZ_Malloc failed:%x\n",Ret);
        (HI_VOID)HI_MMZ_Free(&PlainBuf);
        return HI_FAILURE;
    }

    memcpy(PlainBuf.user_viraddr, input, length);
    memset(EncrytedBuf.user_viraddr, 0, EncrytedBuf.bufsize);

    Ret = HI_UNF_CIPHER_Encrypt(cipher, PlainBuf.phyaddr, EncrytedBuf.phyaddr, length);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_CIPHER_Encrypt failed:%x\n",Ret);
        HI_MMZ_Free(&PlainBuf);
        HI_MMZ_Free(&EncrytedBuf);
        return HI_FAILURE;
    }

    memcpy(output, EncrytedBuf.user_viraddr, length);

    HI_MMZ_Free(&PlainBuf);
    HI_MMZ_Free(&EncrytedBuf);

    return HI_SUCCESS;
}


HI_S32  sample_klad_genrate_encrypt_sw_key(HI_VOID)
{
    HI_S32 Ret;
    HI_HANDLE klad = HI_INVALID_HANDLE;
    HI_UNF_KLAD_ATTR_S attr = {0};
    HI_U8   clear_key[16]= {0x12,0x34,0x56,0x78,0x23,0x45,0x67,0x89,0x34,0x56,0x78,0x90,0x45,0x67,0x89,0x01};
    HI_U8   encrypt_key[16]={0x38,0x14,0x96,0x4a,0x8b,0x07,0xf2,0xea,0x74,0x90,0x0f,0xe5,0xbd,0xeb,0x46,0x13};
    HI_UNF_KLAD_ENC_KEY_S stKey;
    HI_U32  i = 0;

    Ret = HI_UNF_KLAD_Init();
    if (HI_SUCCESS != Ret)
    {
        printf("call KLAD Init failed\n");
        return HI_FAILURE;
    }

    Ret = HI_UNF_KLAD_Create(&klad);
    if (HI_SUCCESS != Ret)
    {
        printf("call KLAD Create failed\n");
        return HI_FAILURE;
    }

    attr.u32KladType = HI_UNF_KLAD_TYPE_SWPK;
    attr.enAlg = HI_UNF_KLAD_ALG_TYPE_TDES;
    attr.enEngine = HI_UNF_KLAD_TARGET_ENGINE_FIXED;
    Ret = HI_UNF_KLAD_SetAttr(klad, &attr);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_SetAttr failed\n");
        goto ERR_KLAD;
    }

    memset(&stKey, 0x00, sizeof(stKey));
    memcpy(stKey.au8ClearKey, clear_key, sizeof(clear_key));
    Ret = HI_UNF_KLAD_GenerateEncKey(klad, &stKey);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_GenerateEncKey failed\n");
        goto ERR_KLAD;
    }

    Ret = memcmp(stKey.au8EncKey, encrypt_key, sizeof(encrypt_key));
    if (HI_SUCCESS != Ret)
    {
        printf("The Result of sample_klad_genrate_encrypt_sw_key is not correspond with expected.\n");
        printf("expected result: ");
        for (i=0; i<16; i++)
        {
            printf("%02x", encrypt_key[i]);
        }
        printf("\nactual result  : ");
        for (i=0; i<16; i++)
        {
            printf("%02x", stKey.au8EncKey[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Success : The Result of sample_klad_genrate_encrypt_sw_key is correspond with expected.\n");
    }

ERR_KLAD:
    HI_UNF_KLAD_Destroy(klad);
    HI_UNF_KLAD_DeInit();

    return Ret;
}

HI_S32 sample_klad_sw_mcipher_encrypt(HI_VOID)
{
    HI_S32 Ret;
    HI_HANDLE klad = HI_INVALID_HANDLE;
    HI_HANDLE mcipher = HI_INVALID_HANDLE;
    HI_UNF_KLAD_ATTR_S attr = {0};
    HI_UNF_CIPHER_ATTS_S attr_mcipher;
    HI_UNF_KLAD_CONTENT_KEY_S content_key = {0};
    HI_U8   encrypt_key[16]={0x38,0x14,0x96,0x4a,0x8b,0x07,0xf2,0xea,0x74,0x90,0x0f,0xe5,0xbd,0xeb,0x46,0x13};
    //HI_U8   clear_key[16]= {0x12,0x34,0x56,0x78,0x23,0x45,0x67,0x89,0x34,0x56,0x78,0x90,0x45,0x67,0x89,0x01};
    HI_U8   plaint_text[32] = {0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0,
                               0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0, 0x01};
    HI_U8   excrypt_text[32] ={0xd9, 0xba, 0xe9, 0x28, 0x14, 0x20, 0xbe, 0x87, 0x06, 0xa9, 0x2c, 0x7a, 0x07, 0x07, 0x7f, 0xa7,
                               0x32, 0x8d, 0xe4, 0x72, 0x78, 0x84, 0xde, 0x56, 0x33, 0x74, 0x0a, 0x0a, 0x2b, 0x04, 0x83, 0x15};
    HI_U8   result_text[32] = {0x00};
    HI_UNF_CIPHER_CTRL_S CipherCtrl;
    HI_U32 i = 0;

    Ret = HI_UNF_KLAD_Init();
    if(HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_Init failed\n");
        return HI_FAILURE;
    }
    Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_CIPHER_Init failed\n");
        return HI_FAILURE;
    }

    Ret = HI_UNF_KLAD_Create(&klad);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_Create failed\n");
        return HI_FAILURE;
    }

    attr_mcipher.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&mcipher, &attr_mcipher);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_CIPHER_CreateHandle failed\n");
        return HI_FAILURE;
    }

    Ret = HI_UNF_KLAD_Attach(klad, mcipher);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_Attach failed\n");
        goto ERR_KLAD;
    }

    attr.u32KladType = HI_UNF_KLAD_TYPE_SWPK;
    attr.enAlg = HI_UNF_KLAD_ALG_TYPE_TDES;
    attr.enEngine = HI_UNF_KLAD_TARGET_ENGINE_FIXED;
    Ret = HI_UNF_KLAD_SetAttr(klad, &attr);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_SetAttr failed\n");
        goto ERR_KLAD;
    }

    content_key.bOdd = 0;
    memcpy(content_key.au8Key, encrypt_key, 16);
    Ret = HI_UNF_KLAD_SetContentKey(klad, &content_key);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_KLAD_SetContentKey failed\n");
        goto ERR_KLAD;
    }

    memset(&CipherCtrl, 0x00, sizeof(HI_UNF_CIPHER_CTRL_S));
    CipherCtrl.bKeyByCA = HI_TRUE;
    CipherCtrl.enAlg    = HI_UNF_CIPHER_ALG_AES;
    CipherCtrl.enWorkMode = HI_UNF_CIPHER_WORK_MODE_ECB;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    Ret = HI_UNF_CIPHER_ConfigHandle(mcipher, &CipherCtrl);
    if (HI_SUCCESS != Ret)
    {
        printf("call HI_UNF_CIPHER_ConfigHandle failed\n");
        goto ERR_KLAD;
    }

    Ret = KLAD_MCipherEncrypt(mcipher, plaint_text, result_text, 32);
    if (HI_SUCCESS != Ret)
    {
        printf("The Result is not correspond with expected.\n");
    }

    Ret = memcmp(result_text, excrypt_text, sizeof(excrypt_text));
    if (HI_SUCCESS != Ret)
    {
        printf("Error : The Result of sample_klad_sw_mcipher_encrypt is not correspond with expected.\n");
        printf("expected result: ");
        for (i=0; i<16; i++)
        {
            printf("%02x", excrypt_text[i]);
        }
        printf("\nactual result  : ");
        for (i=0; i<16; i++)
        {
            printf("%02x", result_text[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Success : The Result of sample_klad_sw_mcipher_encrypt is correspond with expected.\n");
    }

ERR_KLAD:

    HI_UNF_KLAD_Destroy(klad);
    HI_UNF_KLAD_DeInit();
    HI_UNF_CIPHER_DestroyHandle(mcipher);
    HI_UNF_CIPHER_DeInit();

    return Ret;
}

HI_S32 main(HI_S32 argc,HI_CHAR **argv)
{
    sample_klad_genrate_encrypt_sw_key();
    sample_klad_sw_mcipher_encrypt();

    return HI_SUCCESS;
}

