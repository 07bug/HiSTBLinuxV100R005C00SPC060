/******************************************************************************

          Copyright (C), 2001-2015, HiSilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : loader_osal.h
 Version         : Initial draft
 Author          : Device Chipset STB Development Dept
 Created Date    : 2015-07-29
 Last Modified by: sdk
 Description     :
 Function List   :
 Change History  :
 Version  Date        Author     DefectNum         Description
 main\1   2015-07-29  sdk  N/A               Create this file.
 ******************************************************************************/

#ifndef __LOADER_OSAL_H__
#define __LOADER_OSAL_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup      LOADER_OSAL */
/** @{ */  /** <!-- [LOADER_OSAL] */

#define LOADER_MemFreeSetNull(pBuf)    \
{                                    \
    LOADER_MemFree(pBuf);              \
    pBuf = HI_NULL_PTR;              \
}

#define LOADER_StrIsEmpty(str)     (HI_NULL == str[0])

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup      LOADER_OSAL */
/** @{ */  /** <!-- [LOADER_OSAL] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @} */  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup      LOADER_OSAL */
/** @{ */  /** <!-- [LOADER_OSAL] */

HI_U32 LOADER_StrLen(const HI_CHAR* pcStr);

HI_U64 LOADER_Strtoul(const HI_CHAR* nptr, HI_CHAR** endptr, int base);

HI_CHAR* LOADER_StrStr(const HI_CHAR* pcStr1, const HI_CHAR* pcStr2);

HI_CHAR* LOADER_StrNCpy(HI_CHAR* pcDestination, const HI_CHAR* pcSource , HI_U32 u32Count);

HI_S32 LOADER_StrNCmp(const HI_CHAR* pcStr1, const HI_CHAR* pcStr2, HI_U32 u32Count);

HI_VOID* LOADER_MemCpy(HI_VOID* pDest, const HI_VOID* pSrc, HI_U32 u32Count);

HI_VOID* LOADER_MemSet(HI_VOID* pToSet, HI_S32 s32SetChar, HI_U32 u32Count);

HI_S32 LOADER_MemCmp(HI_VOID* pBuf1, HI_VOID* pBuf2, HI_U32 u32Count);

HI_VOID* LOADER_MemMalloc(HI_U32 u32Size);

HI_VOID LOADER_MemFree(HI_VOID* pBuf);

HI_S32 LOADER_MmzMalloc(HI_U32 u32Size, HI_U32* pu32PhyAddr, HI_U8** ppu8VirAddr);

HI_S32 LOADER_MmzFree(HI_U32 u32PhyAddr);

/** @} */  /** <!-- ==== API Declaration End ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */


#endif /*__LOADER_OSAL_H__*/
