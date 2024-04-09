/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : special_verify.h
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

#ifndef __SPECIAL_VERIFY_H__
#define __SPECIAL_VERIFY_H__

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
/** \addtogroup     SPECIAL_VERIFY */
/** @{ */  /** <!-- [SPECIAL_VERIFY] */

#define BLSH_IMG_HEADER_BLOCK_NUM            (5)
#define BLSH_IMG_HEADER_MAGINNUMBER_SIZE     (32)
#define BLSH_IMG_HEADER_HEADERVERSION_SIZE   (8)
#define BLSH_IMG_HEADER_RESERVE_SIZE         (31)

#define BLSH_IMG_HEADER_LEN                  (0x2000)
#define BLSH_IMG_HEADER_SIGNATURE_LEN        (0x100)
#define BLSH_IMG_HEADER_SIGNATURE_POS        (0x1F00)

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     SPECIAL_VERIFY */
/** @{ */  /** <!-- [SPECIAL_VERIFY] */

/****** Enumeration definition ************/

typedef struct tagBLSH_IMAGE_HEAD_S
{
    HI_U8  u8MagicNumber[BLSH_IMG_HEADER_MAGINNUMBER_SIZE];     /**< Magic Number: "Hisilicon_ADVCA_ImgHead_MagicNum" */
    HI_U8  u8HeaderVersion[BLSH_IMG_HEADER_HEADERVERSION_SIZE]; /**< Version: "V000 0003" */
    HI_U32 u32TotalLen;                                         /**< Total length */
    HI_U32 u32CodeOffset;                                       /**< Image offset */
    HI_U32 u32SignedImageLen;                                   /**< Signed Image file size */
    HI_U32 u32SignatureOffset;                                  /**< Signed Image offset */
    HI_U32 u32SignatureLen;                                     /**< Signature length */
    HI_U32 u32BlockNum;                                         /**< Image block number */
    HI_U32 u32BlockOffset[BLSH_IMG_HEADER_BLOCK_NUM];           /**< Each Block offset */
    HI_U32 u32BlockLength[BLSH_IMG_HEADER_BLOCK_NUM];           /**< Each Block length */
    HI_U32 u32SoftwareVerion;                                   /**< Software version */
    HI_U32 u32Reserverd[BLSH_IMG_HEADER_RESERVE_SIZE];
    HI_U32 u32CRC32;                                            /**< CRC32 value */

} BLSH_IMAGE_HEAD_S;

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/*nand and SPI max flash block size*/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     SPECIAL_VERIFY */
/** @{ */  /** <!-- [SPECIAL_VERIFY] */

HI_S32 BLSH_VerifyImageHeader(HI_U8* pu8DataBuffer, HI_U32 u32DataBufferSize);

HI_S32 BLSH_VerifyImageData(BLSH_IMAGE_HEAD_S* pstImageHeader, HI_U8* pu8DataBuffer, HI_U32 u32DataBufferSize);

HI_S32 BLSH_VerifyWholeImage(HI_U8* pu8Data, HI_U32 u32Size);


/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__SPECIAL_VERIFY_H__*/

