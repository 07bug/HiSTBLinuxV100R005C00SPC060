/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : special_verify.c
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
#include "special_verify.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

HI_S32 BLSH_VerifyImageHeader(HI_U8* pu8DataBuffer, HI_U32 u32DataBufferSize)
{
    HI_U8* pu8Signature = HI_NULL_PTR;
    BLSH_IMAGE_HEAD_S* pstImageHeader = HI_NULL_PTR;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8DataBuffer);
    LOADER_CHECK_PARAM(sizeof(BLSH_IMAGE_HEAD_S) > u32DataBufferSize);

    LOADER_PrintBuffer("Header:", pu8DataBuffer, 256);
    LOADER_PrintBuffer("Header Signature:", pu8DataBuffer + BLSH_IMG_HEADER_SIGNATURE_POS, BLSH_IMG_HEADER_SIGNATURE_LEN);

    pstImageHeader = (BLSH_IMAGE_HEAD_S*)pu8DataBuffer;

    pu8Signature = pu8DataBuffer + BLSH_IMG_HEADER_SIGNATURE_POS;
    s32Ret = BLSH_RSAVerify(pu8DataBuffer, BLSH_IMG_HEADER_SIGNATURE_POS,  pu8Signature, BLSH_IMG_HEADER_SIGNATURE_LEN);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_RSAVerify, s32Ret);
        return s32Ret;
    }

    if ((BLSH_IMG_HEADER_LEN >= pstImageHeader->u32TotalLen)
        || (BLSH_IMG_HEADER_LEN >= pstImageHeader->u32SignedImageLen)
        || (BLSH_IMG_HEADER_LEN != pstImageHeader->u32CodeOffset)
        || (BLSH_IMG_HEADER_SIGNATURE_LEN != pstImageHeader->u32SignatureLen)
        || (pstImageHeader->u32SignatureOffset != pstImageHeader->u32SignedImageLen)
        || (pstImageHeader->u32SignedImageLen + pstImageHeader->u32SignatureLen != pstImageHeader->u32TotalLen))
    {
        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 BLSH_VerifyImageData(BLSH_IMAGE_HEAD_S* pstImageHeader, HI_U8* pu8DataBuffer, HI_U32 u32DataBufferSize)
{
    HI_U8* pu8ImageSignature = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstImageHeader);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8DataBuffer);

    LOADER_PrintBuffer("Data:", pu8DataBuffer, 256);
    LOADER_PrintBuffer("Data Signature:", pu8DataBuffer + pstImageHeader->u32SignatureOffset, BLSH_IMG_HEADER_SIGNATURE_LEN);

    pu8ImageSignature = pu8DataBuffer + pstImageHeader->u32SignatureOffset;
    s32Ret = BLSH_RSAVerify(pu8DataBuffer, pstImageHeader->u32SignedImageLen, pu8ImageSignature, pstImageHeader->u32SignatureLen);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_RSAVerify, s32Ret);
        return s32Ret;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 BLSH_VerifyWholeImage(HI_U8* pu8Data, HI_U32 u32Size)
{
    BLSH_IMAGE_HEAD_S* pstImageHeader = HI_NULL_PTR;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8Data);
    LOADER_CHECK_PARAM(sizeof(BLSH_IMAGE_HEAD_S) >= u32Size);

    s32Ret = BLSH_VerifyImageHeader(pu8Data, u32Size);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_VerifyImageHeader, s32Ret);
        return s32Ret;
    }

    pstImageHeader = (BLSH_IMAGE_HEAD_S*)pu8Data;
    s32Ret = BLSH_VerifyImageData(pstImageHeader, pu8Data, pstImageHeader->u32TotalLen);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_VerifyImageData, s32Ret);
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

