/******************************************************************************
Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : sample_rng.c
Version       : Initial Draft
Author        : Hisilicon
Created       : 2012/07/10
Last Modified :
Description   : sample for cipher
Function List :
History       :
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "hi_type.h"
#include "hi_unf_cipher.h"
#include "hi_common.h"
#include "hi_adp.h"
#include "sample_cenc.h"

#define HI_ERR_CIPHER(format, arg...)     HI_PRINT( "\033[0;1;31m" format "\033[0m", ## arg)
#define HI_INFO_CIPHER(format, arg...)    HI_PRINT( "\033[0;1;32m" format "\033[0m", ## arg)
#define TEST_END_PASS()                        HI_INFO_CIPHER("****************** %s test PASS !!! ******************\n", __FUNCTION__)
#define TEST_END_FAIL()                        HI_ERR_CIPHER("****************** %s test FAIL !!! ******************\n", __FUNCTION__)
#define TEST_RESULT_PRINT()                  { if (ret) TEST_END_FAIL(); else TEST_END_PASS();}
#define U32_TO_POINT(addr)  ((HI_VOID*)((HI_SIZE_T)(addr)))
#define POINT_TO_U32(addr)  ((HI_U32)((HI_SIZE_T)(addr)))

static HI_S32 printBuffer(HI_CHAR *string, HI_U8 *pu8Input, HI_U32 u32Length)
{
    HI_U32 i = 0;

    if ( NULL != string )
    {
        printf("%s\n", string);
    }

    for ( i = 0 ; i < u32Length; i++ )
    {
        if( (i % 16 == 0) && (i != 0)) printf("\n");
        printf("0x%02x ", pu8Input[i]);
    }
    printf("\n");

    return HI_SUCCESS;
}


HI_S32 Setconfiginfo(HI_HANDLE chnHandle, HI_BOOL bKeyByCA, HI_UNF_CIPHER_ALG_E alg, HI_UNF_CIPHER_WORK_MODE_E mode, HI_UNF_CIPHER_KEY_LENGTH_E keyLen,
                                                const HI_U8 u8KeyBuf[16], const HI_U8 u8IVBuf[16])
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_CIPHER_CTRL_S CipherCtrl;

    memset(&CipherCtrl, 0, sizeof(HI_UNF_CIPHER_CTRL_S));
    CipherCtrl.enAlg = alg;
    CipherCtrl.enWorkMode = mode;
    CipherCtrl.enBitWidth = HI_UNF_CIPHER_BIT_WIDTH_128BIT;
    CipherCtrl.enKeyLen = keyLen;
    CipherCtrl.bKeyByCA = bKeyByCA;
    if(CipherCtrl.enWorkMode != HI_UNF_CIPHER_WORK_MODE_ECB)
    {
        CipherCtrl.stChangeFlags.bit1IV = 1;  //must set for CBC , CFB mode
        memcpy(CipherCtrl.u32IV, u8IVBuf, 16);
    }

    memcpy(CipherCtrl.u32Key, u8KeyBuf, 16);

    s32Ret = HI_UNF_CIPHER_ConfigHandle(chnHandle, &CipherCtrl);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/* encrypt data using special chn*/
HI_S32 sample_cenc(HI_U8 *key, HI_U8 *iv, HI_U8 *enc, HI_U8 *dec, HI_UNF_CIPHER_WORK_MODE_E mode,
                    HI_U32 u32TestDataLen, HI_U32 u32FirstEncryptOffset,
                    HI_UNF_CIPHER_SUBSAMPLE_EX_S *pstSubSample, HI_U32 u32SubsampleNum)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32InputAddrPhy = 0;
    HI_U32 u32OutPutAddrPhy = 0;
    HI_U32 u32Testcached = 0;
    HI_U8 *pInputAddrVir = HI_NULL;
    HI_U8 *pOutputAddrVir = HI_NULL;
    HI_HANDLE hTestchnid = 0;
    HI_UNF_CIPHER_ATTS_S stCipherAttr;

    s32Ret = HI_UNF_CIPHER_Init();
    if(HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    stCipherAttr.enCipherType = HI_UNF_CIPHER_TYPE_NORMAL;
    s32Ret = HI_UNF_CIPHER_CreateHandle(&hTestchnid, &stCipherAttr);
    if(HI_SUCCESS != s32Ret)
    {
        HI_UNF_CIPHER_DeInit();
        return s32Ret;
    }

    u32InputAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufIn"));
    if (0 == u32InputAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for input failed!\n");
        goto __CIPHER_EXIT__;
    }
    pInputAddrVir = HI_MMZ_Map(u32InputAddrPhy, u32Testcached);
    u32OutPutAddrPhy = POINT_TO_U32(HI_MMZ_New(u32TestDataLen, 0, NULL, "CIPHER_BufOut"));
    if (0 == u32OutPutAddrPhy)
    {
        HI_ERR_CIPHER("Error: Get phyaddr for outPut failed!\n");
        goto __CIPHER_EXIT__;
    }
    pOutputAddrVir = HI_MMZ_Map(u32OutPutAddrPhy, u32Testcached);

    s32Ret = Setconfiginfo(hTestchnid,
                            HI_FALSE,
                            HI_UNF_CIPHER_ALG_AES,
                            mode,
                            HI_UNF_CIPHER_KEY_AES_128BIT,
                            key,
                            iv);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Set config info failed.\n");
        goto __CIPHER_EXIT__;
    }

    memset(pInputAddrVir, 0x0, u32TestDataLen);
    memcpy(pInputAddrVir, enc, u32TestDataLen);
//    printBuffer("CENC-ORI:", enc, u32TestDataLen > 128 ? 128 : u32TestDataLen);

    memset(pOutputAddrVir, 0x0, u32TestDataLen);

    s32Ret = HI_UNF_CIPHER_CENCDecryptEx(hTestchnid, key, HI_TRUE, u32InputAddrPhy,
        u32OutPutAddrPhy, u32TestDataLen, u32FirstEncryptOffset, pstSubSample, u32SubsampleNum);
    if(HI_SUCCESS != s32Ret)
    {
        HI_ERR_CIPHER("Cipher encrypt failed.\n");
        s32Ret = HI_FAILURE;
        goto __CIPHER_EXIT__;
    }

    /* compare */
    if ( 0 != memcmp(pOutputAddrVir, dec, u32TestDataLen) )
    {
        printBuffer("CENC-DEC:", pOutputAddrVir, u32TestDataLen > 1024 ? 1024 : u32TestDataLen);
        HI_ERR_CIPHER("cipher cenc decrypt, memcmp failed!\n");
        s32Ret = HI_FAILURE;

        goto __CIPHER_EXIT__;
    }

    TEST_END_PASS();

__CIPHER_EXIT__:

    if (u32InputAddrPhy> 0)
    {
        HI_MMZ_Unmap(u32InputAddrPhy);
        HI_MMZ_Delete(u32InputAddrPhy);
    }
    if (u32OutPutAddrPhy > 0)
    {
        HI_MMZ_Unmap(u32OutPutAddrPhy);
        HI_MMZ_Delete(u32OutPutAddrPhy);
    }

    HI_UNF_CIPHER_DestroyHandle(hTestchnid);
    HI_UNF_CIPHER_DeInit();

    return s32Ret;
}

HI_S32 main(int argc, char* argv[])
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Conut = 0;

    HI_SYS_Init();
    HI_U32 id = 0;

    for (id=0; id < sizeof(cenc_sample_data)/sizeof(cenc_sample_data[0]); id++)
    {
        s32Ret = sample_cenc(cenc_sample_data[id].key, cenc_sample_data[id].iv,
            cenc_sample_data[id].enc, cenc_sample_data[id].dec,
            cenc_sample_data[id].mode, cenc_sample_data[id].length,
            cenc_sample_data[id].u32FirstEncryptOffset,
            cenc_sample_data[id].subsample, cenc_sample_data[id].subsampleNum);
        HI_PRINT("*************** sample %d test end ****************\n", id);

        if (HI_SUCCESS == s32Ret)
        {
            u32Conut++;
        }
    }

    HI_PRINT("\n**********************************************************\n");
    HI_PRINT("             CENC Test End, Success %d, Faile %d\n", u32Conut, id - u32Conut);
    HI_PRINT("\n**********************************************************\n");

    HI_SYS_DeInit();

    return HI_SUCCESS;
}

