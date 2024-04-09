/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : special_image.c
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

#ifdef HI_MINIBOOT_SUPPORT
#include <stdio.h>
#include <string.h>
#else
#include "common.h"
#endif

#include "loader_debug.h"
#include "loader_osal.h"
#include "loader_flash.h"
#include "general_harden.h"
#include "special_verify.h"
#include "special_image.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

static HI_S32 ssaGetImageData
(
    HI_HANDLE   hFlashHandle,
    HI_U8*      pu8DataBuffer,
    HI_U32      u32DataBufferSize,
    HI_U32*     pu32DataOffset,
    HI_U32*     pu32DataSize
)
{
    HI_U32 u32DataSize = 0;
    BLSH_IMAGE_HEAD_S stImageHeader;

    HI_S32 s32Ret = HI_FAILURE;

    u32DataSize = LOADER_FLASH_Read(hFlashHandle, 0ULL, pu8DataBuffer, u32DataBufferSize, BLSH_IMG_HEADER_LEN);
    if (BLSH_IMG_HEADER_LEN > u32DataSize)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_Read, s32Ret);
        return s32Ret;
    }

    s32Ret = BLSH_VerifyImageHeader(pu8DataBuffer, BLSH_IMG_HEADER_LEN);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_VerifyImageHeader, s32Ret);
        return s32Ret;
    }

    LOADER_MemSet(&stImageHeader, 0x00, sizeof(stImageHeader));
    LOADER_MemCpy(&stImageHeader, pu8DataBuffer, sizeof(stImageHeader));

    u32DataSize = LOADER_FLASH_Read(hFlashHandle,
                                    BLSH_IMG_HEADER_LEN,
                                    pu8DataBuffer + BLSH_IMG_HEADER_LEN,
                                    u32DataBufferSize - BLSH_IMG_HEADER_LEN,
                                    stImageHeader.u32TotalLen - BLSH_IMG_HEADER_LEN);
    if (stImageHeader.u32TotalLen - BLSH_IMG_HEADER_LEN > u32DataSize)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_Read, LOADER_ERR_FLASH);
        return LOADER_ERR_FLASH;
    }

    s32Ret = BLSH_VerifyImageData(&stImageHeader, pu8DataBuffer, stImageHeader.u32TotalLen);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_VerifyImageData, s32Ret);
        return s32Ret;
    }

    *pu32DataOffset = stImageHeader.u32CodeOffset;
    *pu32DataSize = stImageHeader.u32SignedImageLen - stImageHeader.u32CodeOffset;

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 SSA_SpecialSignedImgRead
(
    LOADER_FLASH_OPENPARAM_S*   pstOpenParam,
    HI_U8*                      pu8DataBuffer,
    HI_U32                      u32DataBufferSize,
    HI_U32*                     pu32DataOffset,
    HI_U32*                     pu32DataSize
)
{
    HI_HANDLE hFlashHandle = HI_INVALID_HANDLE;
    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstOpenParam);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8DataBuffer);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu32DataOffset);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu32DataSize);
    LOADER_CHECK_PARAM(0 == u32DataBufferSize);

    hFlashHandle = LOADER_FLASH_Open(pstOpenParam);
    if (HI_INVALID_HANDLE == hFlashHandle)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_Open, LOADER_ERR_FLASH);
        return LOADER_ERR_FLASH;
    }

    s32Ret = BLSH_CipherInit();
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_CipherInit, s32Ret);

        LOADER_CHECK(LOADER_FLASH_Close(hFlashHandle));
        hFlashHandle = HI_INVALID_HANDLE;

        return s32Ret;
    }

    s32Ret = ssaGetImageData(hFlashHandle, pu8DataBuffer, u32DataBufferSize, pu32DataOffset, pu32DataSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(ssaGetImageData, s32Ret);

        LOADER_CHECK(BLSH_CipherDeInit());
        LOADER_CHECK(LOADER_FLASH_Close(hFlashHandle));
        hFlashHandle = HI_INVALID_HANDLE;

        return s32Ret;
    }

    LOADER_CHECK(BLSH_CipherDeInit());
    LOADER_CHECK(LOADER_FLASH_Close(hFlashHandle));
    hFlashHandle = HI_INVALID_HANDLE;

    LOADER_FuncExit();
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

