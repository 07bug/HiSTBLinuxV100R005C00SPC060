/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : general_harden.h
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

#ifndef __COMMON_HARDEN_H__
#define __COMMON_HARDEN_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"
#include "loader_flash.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup     GENERAL_HARDEN */
/** @{ */  /** <!-- [GENERAL_HARDEN] */

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     GENERAL_HARDEN */
/** @{ */  /** <!-- [GENERAL_HARDEN] */

/****** Enumeration definition ************/

typedef enum tagBLSH_HASH_TYPE_E
{
    BLSH_HASH_TYPE_1 = 0,
    BLSH_HASH_TYPE_2,
    BLSH_HASH_TYPE_BUTT

}BLSH_HASH_TYPE_E;

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/*nand and SPI max flash block size*/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     GENERAL_HARDEN */
/** @{ */  /** <!-- [GENERAL_HARDEN] */

HI_S32 BLSH_CipherInit(HI_VOID);

HI_S32 BLSH_CipherDeInit(HI_VOID);

HI_S32 BLSH_HashVerify(BLSH_HASH_TYPE_E enHashType, HI_U8* pu8Data, HI_U32 u32Size, HI_U8* pu8Value);

HI_S32 BLSH_RSAVerify(HI_U8* pu8Data, HI_U32 u32Size, HI_U8* pu8Signature, HI_U32 u32SignatureSize);

HI_S32 BLSH_SetRSAPublicKey(HI_U8* pu8RsaData, HI_U32 u32Length);

HI_S32 BLSH_ConfigExternKey(LOADER_FLASH_OPENPARAM_S* pstOpenParam, HI_U8* pu8Buffer, HI_U32 u32Size, HI_U64 u64ReadAddress);

HI_S32 BLSH_GetRandomNum(HI_U32* pu32Random);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__GENERAL_HARDEN_H__*/

