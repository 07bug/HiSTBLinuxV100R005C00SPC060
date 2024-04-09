/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : common_image.c
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
#include "loader_flash.h"
#include "general_harden.h"
#include "common_verify.h"
#include "common_image.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

static HI_S32 ssaGetSignData
(
    HI_HANDLE           hFlashHandle,
    HI_U8*              pu8Buffer,
    HI_U32              u32BufferSize
)
{
    HI_U32 u32Index = 0;
    HI_U32 u32LeftSize = 0;
    HI_U32 u32ReadSize = 0;
    HI_U32 u32PartSize = 0;
    HI_U64 u32ReadAddr = 0;
    HI_U32 u32TotalSize = 0;
    HI_U8* pu8CurrTail = HI_NULL_PTR;
    HI_U8* pu8PrevTail = HI_NULL_PTR;
    BLSH_SECTIONTAIL_S* pstTailHead = HI_NULL_PTR;
    LOADER_FLASH_INFO_S stFlashInfo;
    HI_U8* pu8TailHead = pu8Buffer;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_MemSet(&stFlashInfo, 0x00, sizeof(stFlashInfo));
    s32Ret = LOADER_FLASH_GetInfo(hFlashHandle, &stFlashInfo);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_GetInfo, s32Ret);
        return s32Ret;
    }

    if (BLSH_COMMON_FIX_PAGESIZE > stFlashInfo.u64PartSize)
    {
        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    while (u32ReadAddr <= u32PartSize - BLSH_COMMON_FIX_PAGESIZE)
    {
        u32ReadSize = LOADER_FLASH_Read(hFlashHandle, u32ReadAddr, pu8Buffer, u32BufferSize, BLSH_COMMON_FIX_PAGESIZE);
        if (BLSH_COMMON_FIX_PAGESIZE > u32ReadSize)
        {
            LOADER_PrintFuncErr(LOADER_FLASH_Read, LOADER_ERR_FLASH);
            return LOADER_ERR_FLASH;
        }

        pu8TailHead = pu8Buffer;
        u32LeftSize = u32ReadSize;

        while (u32LeftSize >= BLSH_COMMON_FIX_PAGESIZE)
        {
            if (BLSH_CHECK_TAILSECTION(pu8TailHead))
            {
                pstTailHead = (BLSH_SECTIONTAIL_S*)pu8TailHead;
                break;
            }

            pu8TailHead += BLSH_COMMON_FIX_PAGESIZE;
            u32ReadAddr += BLSH_COMMON_FIX_PAGESIZE;
            u32LeftSize -= BLSH_COMMON_FIX_PAGESIZE;

            if (HI_NULL_PTR != pstTailHead)
            {
                break;
            }
        }

        if (HI_NULL_PTR != pstTailHead)
        {
            break;
        }
    }

    if ((HI_NULL_PTR == pstTailHead)
        || (0 == pstTailHead->u32Totalsection))
    {
        LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
        return LOADER_ERR_ILLEGAL_IMAGE;
    }

    u32TotalSize = pstTailHead->u32Totalsection * BLSH_COMMON_FIX_PAGESIZE;
    if (u32TotalSize > u32LeftSize)
    {
        LOADER_PrintInfo("No need to read again!");

        u32ReadSize  = LOADER_FLASH_Read(hFlashHandle, u32ReadAddr, pu8Buffer, u32BufferSize, u32TotalSize);
        if (u32TotalSize > u32ReadSize)
        {
            LOADER_PrintFuncErr(LOADER_FLASH_Read, LOADER_ERR_FLASH);
            return LOADER_ERR_FLASH;
        }

        pu8TailHead = pu8Buffer;
        pstTailHead = (BLSH_SECTIONTAIL_S*)pu8TailHead;

        if (0 == pstTailHead->u32Totalsection)
        {
            LOADER_PrintErrCode(LOADER_ERR_ILLEGAL_IMAGE);
            return LOADER_ERR_ILLEGAL_IMAGE;
        }
    }

    pu8CurrTail = pu8TailHead;

    for (u32Index = 0; u32Index < pstTailHead->u32Totalsection; u32Index ++)
    {
        s32Ret = BLSH_VerifySectionTail(pu8PrevTail, pu8CurrTail);
        if (HI_SUCCESS != s32Ret)
        {
            LOADER_PrintFuncErr(BLSH_VerifySectionTail, s32Ret);
            return s32Ret;
        }
        pu8CurrTail = pu8CurrTail + BLSH_COMMON_FIX_PAGESIZE;
        pu8PrevTail = pu8CurrTail;
    }

    LOADER_FuncExit();
    return HI_SUCCESS;
}


static HI_S32 ssaImageRead
(
    HI_HANDLE           hDataFlashHandle,
    HI_HANDLE           hSignFlashHandle,
    HI_U8*              pu8DataBuffer,
    HI_U32              u32DataBufferSize,
    HI_U8*              pu8SignBuffer,
    HI_U32              u32SignBufferSize
)
{
    HI_U32 u32Index = 0;
    HI_U32 u32DataSize = 0;
    HI_U32 u32ReadSize = 0;
    HI_U8* pu8SectionTail = HI_NULL_PTR;
    HI_U8* pu8SectionData = pu8DataBuffer;
    BLSH_SECTIONTAIL_S* pstSectionTail = (BLSH_SECTIONTAIL_S*)pu8SignBuffer;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    s32Ret = BLSH_CipherInit();
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(BLSH_CipherInit, s32Ret);
        return s32Ret;
    }

    s32Ret = ssaGetSignData(hSignFlashHandle, pu8SignBuffer, u32SignBufferSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(ssaGetSignData, s32Ret);

        LOADER_CHECK(BLSH_CipherDeInit());
        return s32Ret;
    }

    u32ReadSize = (1 == pstSectionTail->u32Totalsection) ? pstSectionTail->u32SignedDataLength : pstSectionTail->u32Totalsection * pstSectionTail->u32SectionSize;
    u32DataSize = LOADER_FLASH_Read(hDataFlashHandle, 0ULL, pu8DataBuffer, u32DataBufferSize, u32ReadSize);
    if (u32ReadSize > u32DataSize)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_Read, LOADER_ERR_FLASH);

        LOADER_CHECK(BLSH_CipherDeInit());
        return LOADER_ERR_FLASH;
    }

    for (u32Index = 0; u32Index < pstSectionTail->u32Totalsection; u32Index ++)
    {
        pu8SectionData = pu8DataBuffer + u32Index * pstSectionTail->u32SectionSize;
        pu8SectionTail = pu8SignBuffer + u32Index * BLSH_COMMON_FIX_PAGESIZE;
        s32Ret = BLSH_VerifySectionData(pu8SectionData, pu8SectionTail);
        if (HI_SUCCESS != s32Ret)
        {
            LOADER_PrintFuncErr(BLSH_VerifySectionData, s32Ret);

            LOADER_CHECK(BLSH_CipherDeInit());
            return s32Ret;
        }
    }

    LOADER_CHECK(BLSH_CipherDeInit());

    LOADER_FuncExit();
    return HI_SUCCESS;
}

HI_S32 SSA_ComSingedImgRead
(
    LOADER_FLASH_OPENPARAM_S*  pstDataParam,
    LOADER_FLASH_OPENPARAM_S*  pstSignParam,
    HI_U8*                     pu8DataBuffer,
    HI_U32                     u32DataBufferSize,
    HI_U8*                     pu8SignBuffer,
    HI_U32                     u32SignBufferSize
)
{
    HI_HANDLE hDataFlashHandle = HI_INVALID_HANDLE;
    HI_HANDLE hSignFlashHandle = HI_INVALID_HANDLE;

    HI_S32 s32Ret = HI_FAILURE;

    LOADER_FuncEnter();

    LOADER_CHECK_PARAM(HI_NULL_PTR == pstDataParam);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8DataBuffer);
    LOADER_CHECK_PARAM(HI_NULL_PTR == pu8SignBuffer);

    LOADER_CHECK_PARAM(0 == u32DataBufferSize);
    LOADER_CHECK_PARAM(0 == u32SignBufferSize);

    hDataFlashHandle = LOADER_FLASH_Open(pstDataParam);
    if (HI_INVALID_HANDLE == hDataFlashHandle)
    {
        LOADER_PrintFuncErr(LOADER_FLASH_Open, LOADER_ERR_FLASH);
        return LOADER_ERR_FLASH;
    }

    if (HI_NULL_PTR != pstSignParam)
    {
        hSignFlashHandle = LOADER_FLASH_Open(pstSignParam);
        if (HI_INVALID_HANDLE == hSignFlashHandle)
        {
            LOADER_PrintFuncErr(LOADER_FLASH_Open, LOADER_ERR_FLASH);

            LOADER_FLASH_Close(hDataFlashHandle);
            hDataFlashHandle = HI_INVALID_HANDLE;

            return LOADER_ERR_FLASH;
        }
    }
    else
    {
        hSignFlashHandle = hDataFlashHandle;
    }

    s32Ret = ssaImageRead(hDataFlashHandle,
                          hSignFlashHandle,
                          pu8DataBuffer,
                          u32DataBufferSize,
                          pu8SignBuffer,
                          u32SignBufferSize);
    if (HI_SUCCESS != s32Ret)
    {
        LOADER_PrintFuncErr(ssaImageRead, s32Ret);

        if (HI_NULL_PTR != pstSignParam)
        {
            LOADER_FLASH_Close(hSignFlashHandle);
            hSignFlashHandle = HI_INVALID_HANDLE;
        }

        LOADER_FLASH_Close(hDataFlashHandle);
        hDataFlashHandle = HI_INVALID_HANDLE;

        return s32Ret;
    }

    if (HI_NULL_PTR != pstSignParam)
    {
        LOADER_FLASH_Close(hSignFlashHandle);
        hSignFlashHandle = HI_INVALID_HANDLE;
    }

    LOADER_FLASH_Close(hDataFlashHandle);
    hDataFlashHandle = HI_INVALID_HANDLE;

    LOADER_FuncExit();
    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

