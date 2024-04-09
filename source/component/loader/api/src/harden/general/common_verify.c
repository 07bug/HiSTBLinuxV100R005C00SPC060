/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : common_verify.c
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2017-07-09
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2017-07-09  sdk  N/A               Create this file.
 ******************************************************************************/

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#if defined(HI_LOADER_RUNNING_ENVIRONMENT_MINIBOOT)
#include <stdio.h>
#include <string.h>
#elif defined(HI_LOADER_RUNNING_ENVIRONMENT_UBOOT)
#include "common.h"
#else
#include <stdio.h>
#include <string.h>
#endif

#include "loader_debug.h"
#include "loader_osal.h"
#include "general_harden.h"
#include "common_verify.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define BLSH_CRC_POLYNOMIAL          (0x04c11db7L)
#define BLSH_CRC_TABLELEN            (256)

static HI_ULONG s_aulCrcTable[BLSH_CRC_TABLELEN] = {0};

static HI_U32 ssaCRC32(HI_U8* pu8Buffer, HI_U32 u32Length)
{
    HI_ULONG ulCRC = 0xffffffff;
    HI_ULONG ulCrcAccum = 0;
    HI_U32 j = 0;

    static HI_U32 i = 0;

    for (i = 0; i < BLSH_CRC_TABLELEN; i++)
    {
        ulCrcAccum = (i << 24);

        for (j = 0; j < 8;  j++)
        {
            if (ulCrcAccum & 0x80000000L)
            {
                ulCrcAccum = ( ulCrcAccum << 1 ) ^ BLSH_CRC_POLYNOMIAL;
            }
            else
            {
                ulCrcAccum = (ulCrcAccum << 1);
            }
        }

        s_aulCrcTable[i] = ulCrcAccum;
    }

    while (u32Length--)
    {
        ulCRC = (ulCRC << 8) ^ s_aulCrcTable[((ulCRC >> 24) ^ *pu8Buffer ++) & 0xff];
    }

    return ulCRC;
}

HI_S32 BLSH_VerifySectionTail(HI_U8* pu8PrevTail, HI_U8* pu8CurrTail)
{
    HI_U32 u32CRCValue = 0;
    BLSH_SECTIONTAIL_S* pstPrevHead = (BLSH_SECTIONTAIL_S*)pu8PrevTail;
    BLSH_SECTIONTAIL_S* pstCurrTail = (BLSH_SECTIONTAIL_S*)pu8CurrTail;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8CurrTail);

    if (!BLSH_CHECK_TAILSECTION(pu8CurrTail))
    {
        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    u32CRCValue = ssaCRC32(pu8CurrTail, sizeof(BLSH_SECTIONTAIL_S) - sizeof(pstCurrTail->u32CRC32));
    if (u32CRCValue != pstCurrTail->u32CRC32)
    {
        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    LOADER_Print32Hex(pstCurrTail->u32CRC32);
    LOADER_Print32Hex(u32CRCValue);

    if ((0 == pstCurrTail->u32Totalsection)
        || (0 == pstCurrTail->u32SignatureLen)
        || (pstCurrTail->u32CurrentsectionID >= pstCurrTail->u32Totalsection))
    {
        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    if ((1 < pstCurrTail->u32Totalsection)
        && (0 == pstCurrTail->u32SectionSize))
    {
        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    if (HI_NULL_PTR != pstPrevHead)
    {
        if ((pstPrevHead->u32SectionSize != pstCurrTail->u32SectionSize)
            || (pstPrevHead->u32Totalsection != pstCurrTail->u32Totalsection))
        {
            LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
            return LOADER_ERR_ILLEGAL_IMAGE;
        }
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 BLSH_VerifySectionData(HI_U8* pu8Data, HI_U8* pu8Tail)
{
    BLSH_SECTIONTAIL_S* pstTail = (BLSH_SECTIONTAIL_S*)pu8Tail;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8Data);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8Tail);

    s32Ret = BLSH_HashVerify(pstTail->u32HashType, pu8Data, pstTail->u32SignedDataLength, pstTail->au8Sha);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_HashVerify, s32Ret);
        return s32Ret;
    }

    LOADER_PrintBuffer("RSA Signature:", pstTail->au8Signature, pstTail->u32SignatureLen);
    s32Ret = BLSH_RSAVerify(pu8Data, pstTail->u32SignedDataLength, pstTail->au8Signature, pstTail->u32SignatureLen);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_RSAVerify, s32Ret);
        return s32Ret;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

