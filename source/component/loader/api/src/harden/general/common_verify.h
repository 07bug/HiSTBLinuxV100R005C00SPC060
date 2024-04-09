/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : common_verify.h
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

#ifndef __COMMON_VERIFY_H__
#define __COMMON_VERIFY_H__

/******************************************************************************/
/*  Header file references                                                    */
/*  Quote order                                                               */
/*  1. Global header file                                                     */
/*  2. Public header files of other modules                                   */
/*  3. Header files within this module                                        */
/*  4. Private files within this module (.inc)                                */
/******************************************************************************/

#include "hi_type.h"
#include "loader_osal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

/*************************** Macro Definition *********************************/
/** \addtogroup     COMMON_VERIFY */
/** @{ */  /** <!-- [COMMON_VERIFY] */

#define BLSH_CHECK_TAILSECTION(pu8Section)     (0 == LOADER_MemCmp(pu8Section, BLSH_COMMON_STR_MAGICNUMBER, BLSH_COMMON_LEN_MAGICNUMBER))

#define BLSH_COMMON_FIX_PAGESIZE               (0x2000)
#define BLSH_COMMON_LEN_VERSION                (8)
#define BLSH_COMMON_LEN_SHA_VALUE              (32)
#define BLSH_COMMON_LEN_SIGNATURE              (256)
#define BLSH_COMMON_LEN_ORIGNAL_IMAGE_PATH     (256)
#define BLSH_COMMON_LEN_RSA_PRIVATE_KEY_PATH   (256)
#define BLSH_COMMON_LEN_MAGICNUMBER            (32)
#define BLSH_COMMON_STR_MAGICNUMBER            ("Hisilicon_ADVCA_ImgHead_MagicNum")


/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     COMMON_VERIFY */
/** @{ */  /** <!-- [COMMON_VERIFY] */

/****** Enumeration definition ************/

/****** Structure definition **************/

typedef struct tagBLSH_SECTIONTAIL_S
{
    HI_U8   au8MagicNumber[BLSH_COMMON_LEN_MAGICNUMBER];                /**< Magic Number: "Hisilicon_ADVCA_ImgHead_MagicNum" */
    HI_U8   au8Version[BLSH_COMMON_LEN_VERSION];                        /**< version: "V000 0003" */
    HI_U32  u32CreateDay;                                               /**< yyyymmdd */
    HI_U32  u32CreateTime;                                              /**< hhmmss */
    HI_U32  u32HeadLength;                                              /**< The following data size */
    HI_U32  u32SignedDataLength;                                        /**< signed data length */
    HI_U32  u32IsYaffsImage;                                            /**< Yaffsr image need to specail read-out, No use */
    HI_U32  u32IsConfigNandBlock;                                       /**< Yaffsr image need to specail read-out, No use */
    HI_U32  u32NandBlockType;                                           /**< Yaffsr image need to specail read-out, No use */
    HI_U32  u32IsNeedEncrypt;                                           /**< if "1", code need to be encrypted. */
    HI_U32  u32IsEncrypted;                                             /**< if "1", code has encrypted. */
    HI_U32  u32HashType;                                                /**< if "0", au8Sha save sha1 of code, if "1",  au8Sha save sha256 of code */
    HI_U8   au8Sha[BLSH_COMMON_LEN_SHA_VALUE];                          /**< SHA value */
    HI_U32  u32SignatureLen;                                            /**< Actural Signature length */
    HI_U8   au8Signature[BLSH_COMMON_LEN_SIGNATURE];                    /**< Max length:0x100 */
    HI_U8   au8OrignalImagePath[BLSH_COMMON_LEN_ORIGNAL_IMAGE_PATH];    /**< Max length: */
    HI_U8   au8RSAPrivateKeyPath[BLSH_COMMON_LEN_RSA_PRIVATE_KEY_PATH]; /**< Max length:0x100 */
    HI_U32  u32CurrentsectionID;                                        /**< Begin with 0 */
    HI_U32  u32SectionSize;                                             /**< Section size */
    HI_U32  u32Totalsection;                                            /**< Total Section Count >= 1 */
    HI_U32  u32CRC32;                                                   /**< CRC32 value */
} BLSH_SECTIONTAIL_S;

/****** Union definition ******************/

/****** Global variable declaration *******/

/*nand and SPI max flash block size*/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     COMMON_VERIFY */
/** @{ */  /** <!-- [COMMON_VERIFY] */

HI_S32 BLSH_VerifySectionTail(HI_U8* pu8PrevTail, HI_U8* pu8CurrTail);

HI_S32 BLSH_VerifySectionData(HI_U8* pu8Data, HI_U8* pu8Tail);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__COMMON_VERIFY_H__*/

