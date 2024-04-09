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

static HI_VOID show_usage(HI_VOID)
{
    printf("./sample_ca_crypot configfilename\n");
    printf("config file include: ");
    printf("PLAINTTEXT, SESSIONKEY1, SESSIONKEY2, SESSIONKEY3, SESSIONKEY4, CONTENTKEY\n");
}

static HI_VOID printBuffer(HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{
    HI_U32 i = 0;

    if (NULL != string)
    {
        printf("%s\n", string);
    }

    for (i = 0 ; i < u32Length; i++)
    {
        if((i % 16 == 0) && (i != 0))
            printf("\n");

        printf("0x%02x ", pu8Input[i]);
    }

    printf("\n");

    return;
}

static HI_VOID show_keyladderinfo(HI_VOID)
{
    if (HI_UNF_KLAD_COMMON_CA_TYPE_R2R == g_KladType)
    {
        printf("Keyladder type is R2R\n");
    }
    else if (HI_UNF_KLAD_COMMON_CA_TYPE_MISC == g_KladType)
    {
        printf("Keyladder type is Misc\n");
    }
    else if (HI_UNF_KLAD_COMMON_CA_TYPE_SP == g_KladType)
    {
        printf("Keyladder type is SP\n");
    }
    else
    {
        printf("Keyladder type is unknow\n");
    }

    printf("klad Level is %d\n", g_kladLevel + 1);

    if (HI_UNF_KLAD_ALG_TYPE_TDES == g_kladAlg)
    {
        printf("Keyladder Alg  is TDES\n");
    }
    else if (HI_UNF_KLAD_ALG_TYPE_AES == g_kladAlg)
    {
        printf("Keyladder Alg  is AES\n");
    }
    return;
}


static HI_VOID show_cipherinfo(HI_VOID)
{
    if (HI_UNF_CIPHER_ALG_AES == g_cipherAlg)
    {
        printf("Cipher Alg is AES\n");
    }
    else if (HI_UNF_CIPHER_ALG_3DES == g_cipherAlg)
    {
        printf("Cipher Alg is TDES\n");
    }
    else
    {
        printf("Cipher Alg is unknow\n");
    }

    if (HI_UNF_CIPHER_WORK_MODE_ECB == g_cipherMode)
    {
        printf("Cipher Alg mode is ECB\n");
    }
    else if (HI_UNF_CIPHER_WORK_MODE_CBC == g_cipherMode)
    {
        printf("Cipher Alg mode is CBC\n");
    }
    else
    {
        printf("Cipher Alg mode is %x\n", g_cipherMode);
    }
    return;
}

static HI_VOID show_info(HI_VOID)
{
    show_keyladderinfo();
    show_cipherinfo();
}

static HI_S32 cfgCipher(HI_HANDLE hKlad,HI_HANDLE hCipher, HI_BOOL ca)
{
    HI_UNF_CIPHER_CTRL_S CipherCtrl;

    memset(&CipherCtrl, 0x0, sizeof(HI_UNF_CIPHER_CTRL_S));
    CipherCtrl.bKeyByCA = ca;
    CipherCtrl.enAlg    = g_cipherAlg;
    CipherCtrl.enWorkMode = g_cipherMode;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    if (g_cipherAlg == HI_UNF_CIPHER_ALG_AES)
    {
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_AES_128BIT;
    }
    else
    {
        CipherCtrl.enKeyLen = HI_UNF_CIPHER_KEY_DES_2KEY;
    }

    if (HI_UNF_CIPHER_WORK_MODE_ECB != g_cipherMode)
    {
        printBuffer("IV:", g_IV, 16);
        CipherCtrl.stChangeFlags.bit1IV = 1;
        memcpy(CipherCtrl.u32IV, g_IV, 16);
    }

    if(HI_FALSE == ca)
    {
        printBuffer("clear cw content key:", g_clearContentkey, 16);
        memcpy(CipherCtrl.u32Key, g_clearContentkey, 16);
    }
    ST_KLAD_ASSERT(HI_UNF_CIPHER_ConfigHandle(hCipher, &CipherCtrl));

    return HI_SUCCESS;
}

static HI_S32 setCw(HI_HANDLE hKlad,HI_HANDLE hCipher)
{
    HI_UNF_KLAD_ATTR_S  attr = {0};
    HI_UNF_KLAD_SESSION_KEY_S sessionkey;
    HI_UNF_KLAD_CONTENT_KEY_S Contentkey = {0};

    attr.enAlg = g_kladAlg;
    attr.enEngine = HI_UNF_KLAD_TARGET_ENGINE_FIXED;
    attr.u32KladType = g_KladType;
    ST_KLAD_ASSERT(HI_UNF_KLAD_SetAttr(hKlad,&attr));

    printf("keyladder level is :%d\n", g_kladLevel + 1);
    if (g_kladLevel >= HI_UNF_KLAD_LEVEL2)
    {
        printBuffer("Sessionkey1:", g_sessionkey1, 16);
        memset(&sessionkey,0x00,sizeof(HI_UNF_KLAD_SESSION_KEY_S));
        sessionkey.enLevel = HI_UNF_KLAD_LEVEL1;
        memcpy(sessionkey.au8Key,g_sessionkey1,16);

        ST_KLAD_ASSERT(HI_UNF_KLAD_SetSessionKey(hKlad,&sessionkey));
    }

    if (g_kladLevel >= HI_UNF_KLAD_LEVEL3)
    {
        printBuffer("Sessionkey2:", g_sessionkey2, 16);
        memset(&sessionkey,0x00,sizeof(HI_UNF_KLAD_SESSION_KEY_S));
        sessionkey.enLevel = HI_UNF_KLAD_LEVEL2;
        memcpy(sessionkey.au8Key,g_sessionkey2,16);

        ST_KLAD_ASSERT(HI_UNF_KLAD_SetSessionKey(hKlad,&sessionkey));
    }

    if (g_kladLevel >= HI_UNF_KLAD_LEVEL4)
    {
        printBuffer("Sessionkey3:", g_sessionkey3, 16);
        memset(&sessionkey,0x00,sizeof(HI_UNF_KLAD_SESSION_KEY_S));
        sessionkey.enLevel = HI_UNF_KLAD_LEVEL3;
        memcpy(sessionkey.au8Key,g_sessionkey3,16);

        ST_KLAD_ASSERT(HI_UNF_KLAD_SetSessionKey(hKlad,&sessionkey));
    }

    if (g_kladLevel >= HI_UNF_KLAD_LEVEL5)
    {
        printBuffer("Sessionkey4:", g_sessionkey4, 16);
        memset(&sessionkey,0x00,sizeof(HI_UNF_KLAD_SESSION_KEY_S));
        sessionkey.enLevel = HI_UNF_KLAD_LEVEL4;
        memcpy(sessionkey.au8Key,g_sessionkey4,16);

        ST_KLAD_ASSERT(HI_UNF_KLAD_SetSessionKey(hKlad,&sessionkey));
    }

    get_key_value("ENCRYPTEDCONTENTKEY", g_contentkey, 16);

    printBuffer("Encrypted content key :", g_contentkey, 16);

    Contentkey.bOdd = 0;
    memcpy(Contentkey.au8Key,g_contentkey,16);
    ST_KLAD_ASSERT(HI_UNF_KLAD_SetContentKey(hKlad,&Contentkey));

    ST_KLAD_ASSERT(cfgCipher(hKlad,hCipher,HI_TRUE));

    return HI_SUCCESS;
}

#if !(defined(CHIP_TYPE_hi3716mv420) || defined(CHIP_TYPE_hi3716mv410))
static HI_S32 setClearCw(HI_HANDLE hKlad,HI_HANDLE hCipher)
{
    HI_UNF_KLAD_ATTR_S stKladAttr = {0};
    HI_UNF_KLAD_CONTENT_KEY_S Contentkey = {0};

    stKladAttr.u32KladType= HI_UNF_KLAD_TYPE_CLEARCW;
    stKladAttr.enAlg = HI_UNF_KLAD_ALG_TYPE_BUTT;
    stKladAttr.enEngine = HI_UNF_KLAD_TARGET_ENGINE_FIXED;
    ST_KLAD_ASSERT(HI_UNF_KLAD_SetAttr(hKlad,&stKladAttr));

    printBuffer("clear cw content key:", g_clearContentkey, 16);
    Contentkey.bOdd = 0;
    memcpy(Contentkey.au8Key,g_clearContentkey,16);

    ST_KLAD_ASSERT(HI_UNF_KLAD_SetContentKey(hKlad,&Contentkey));

    ST_KLAD_ASSERT(cfgCipher(hKlad,hCipher,HI_TRUE));

    return HI_SUCCESS;
}
#endif

static HI_S32 setConfigure(HI_HANDLE hKlad,HI_HANDLE hCipher)
{
    HI_S32 Ret = HI_SUCCESS;

    if (1 == g_CwType)
    {
        Ret = setCw(hKlad,hCipher);
    }
    else
    {
    #if defined(CHIP_TYPE_hi3716mv420) ||defined(CHIP_TYPE_hi3716mv410)
        Ret = cfgCipher(hKlad,hCipher,HI_FALSE);
    #else
        Ret = setClearCw(hKlad,hCipher);
    #endif
    }

    return Ret;
}



static HI_S32 get_plainttext(HI_CHAR *pName, HI_U8 *pData, HI_U32 *pDataLen)
{
    HI_CHAR *value = NULL;
    HI_S32 i;

    value = get_config_var(pName);
    if (NULL == value)
    {
        return -1;
    }

    for (i = 0; i < strlen (value) / 2; i++)
    {
        sscanf(value + 2 * i, "%2x", (HI_U32 *)&pData[i]);
    }

    *pDataLen = i;

    return 0;
}

static HI_S32 get_cw_type()
{
    HI_CHAR *value = HI_NULL;

    value = get_config_var("ENCRYPTCW");
    if (HI_NULL == value)
    {
        return -1;
    }

    if (0 == strncmp(value, "NO", sizeof ("NO")))
    {
        g_CwType = 0;
        printf("clear cw selected\n");
        return 0;
    }

    if (0 == strncmp(value, "YES", sizeof ("YES")))
    {
        g_CwType = 1;
        printf("encrypt cw selected\n");
        return 0;
    }

    g_CwType = 0;
    printf("not set cw type, clear cw selected\n");

    return 0;
}

static HI_S32 readConfigFile(HI_CHAR *pFileName)
{
    HI_S32 s32ValueNum = 0;
    HI_S32 s32Ret = 0;

    s32ValueNum = parse_config_file(pFileName);
    if (0 == s32ValueNum || MAX_VAR_NUM < s32ValueNum)
    {
        return HI_FAILURE;
    }

    get_cw_type();

    s32Ret  = get_key_value(SESSIONKEY1_TAG, g_sessionkey1, KEY_LEN);
    s32Ret |= get_key_value(SESSIONKEY2_TAG, g_sessionkey2, KEY_LEN);
    s32Ret |= get_key_value(SESSIONKEY3_TAG, g_sessionkey3, KEY_LEN);
    s32Ret |= get_key_value(SESSIONKEY4_TAG, g_sessionkey4, KEY_LEN);
    s32Ret |= get_key_value(CONTENTKEY_TAG, g_contentkey, KEY_LEN);
    s32Ret |= get_key_value("IV", g_IV, KEY_LEN);
    s32Ret |= get_plainttext(PLAINTEXT_TAG, g_PlainText, &g_PlainTextLen);
    s32Ret |= get_key_value("CLEARCW", g_clearContentkey, KEY_LEN);

    s32Ret |= get_keyladder_type(&g_KladType);
    s32Ret |= get_keyladder_level(&g_kladLevel);
    s32Ret |= get_keyladder_alg(&g_kladAlg);
    s32Ret |= get_cipher_alg(&g_cipherAlg);
    s32Ret |= get_cipher_mode(&g_cipherMode);
    if (s32Ret != 0)
    {
        printf("read config key failed\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


HI_S32 main(HI_S32 argc,HI_CHAR **argv)
{
    HI_S32 Ret;
    HI_HANDLE hCipher;
    HI_HANDLE hKlad;
    HI_MMZ_BUF_S PlainBuf,EncrytedBuf;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;

    if (argc != 2)
    {
        show_usage();
        return 0;
    }

    Ret = readConfigFile(argv[1]);
    if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

    strncpy(PlainBuf.bufname,"plain_text",MAX_BUFFER_NAME_SIZE);
    PlainBuf.bufsize = 0x1000;
    PlainBuf.overflow_threshold = 100;
    PlainBuf.underflow_threshold = 0;
    Ret = HI_MMZ_Malloc(&PlainBuf);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_MMZ_Malloc failed:%x\n",Ret);
        return HI_FAILURE;
    }

    strncpy(EncrytedBuf.bufname,"encrypted_text",MAX_BUFFER_NAME_SIZE);
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

    if (HI_SUCCESS != HI_UNF_KLAD_Init())
    {
        printf("HI_UNF_KLAD_Init failed:%x\n",Ret);
        goto FREE;
    }

    if (HI_SUCCESS != HI_UNF_CIPHER_Init())
    {
        printf("HI_UNF_CIPHER_Init failed:%x\n",Ret);
        goto CA_DEINIT;
    }

    if (HI_SUCCESS != HI_UNF_KLAD_Create(&hKlad))
    {
        printf("HI_UNF_KLAD_Create failed:%x\n",Ret);
        goto CA_DESTORY;
    }

    memset(&stCipherAttr, 0, sizeof(stCipherAttr));
    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    Ret = HI_UNF_CIPHER_CreateHandle(&hCipher, &stCipherAttr);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_CIPHER_CreateHandle failed:%x\n",Ret);
        goto CLOSE;
    }

    if (HI_SUCCESS != HI_UNF_KLAD_Attach(hKlad,hCipher))
    {
        printf("HI_UNF_KLAD_Attach failed:%x\n",Ret);
        goto CA_DETACH;
    }

    show_info();

    Ret  = setConfigure(hKlad,hCipher);

    if (HI_SUCCESS != Ret)
    {
        printf("config error\n");
        goto DESTROY;

    }

    /* encryption demo */
    memcpy(PlainBuf.user_viraddr, g_PlainText, TEXT_LEN);
    memset(EncrytedBuf.user_viraddr, 0, EncrytedBuf.bufsize);
    Ret = HI_UNF_CIPHER_Encrypt(hCipher,PlainBuf.phyaddr, EncrytedBuf.phyaddr, TEXT_LEN);
    if (HI_SUCCESS != Ret)
    {
        printf("HI_UNF_CIPHER_Encrypt failed:%x\n",Ret);
        goto DESTROY;
    }

    printBuffer("plaint data", PlainBuf.user_viraddr, g_PlainTextLen);
    printBuffer("encrypt result:", EncrytedBuf.user_viraddr, g_PlainTextLen);

    Ret = HI_SUCCESS;
DESTROY:
    (HI_VOID)HI_UNF_CIPHER_DestroyHandle(hCipher);
CA_DETACH:
    (HI_VOID)HI_UNF_KLAD_Detach(hKlad,hCipher);
CA_DESTORY:
    (HI_VOID)HI_UNF_KLAD_Destroy(hKlad);
CLOSE:
    (HI_VOID)HI_UNF_CIPHER_DeInit();
CA_DEINIT:
    (HI_VOID)HI_UNF_KLAD_DeInit();
FREE:
    (HI_VOID)HI_MMZ_Free(&PlainBuf);
    (HI_VOID)HI_MMZ_Free(&EncrytedBuf);

    return Ret;
}


