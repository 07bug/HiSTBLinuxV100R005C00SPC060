/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : special_image.h
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

#ifndef __SPECIAL_IMGAE_H__
#define __SPECIAL_IMGAE_H__

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
/** \addtogroup     SPECIAL_IMAGE */
/** @{ */  /** <!-- [SPECIAL_IMAGE] */

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     SPECIAL_IMAGE */
/** @{ */  /** <!-- [SPECIAL_IMAGE] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     SPECIAL_IMAGE */
/** @{ */  /** <!-- [SPECIAL_IMAGE] */

HI_S32 SSA_SpecialSignedImgRead
(
    LOADER_FLASH_OPENPARAM_S*   pstOpenParam,
    HI_U8*                      pu8DataBuffer,
    HI_U32                      u32DataBufferSize,
    HI_U32*                     pu32DataOffset,
    HI_U32*                     pu32DataSize
);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__SPECIAL_IMAGE_H__*/

