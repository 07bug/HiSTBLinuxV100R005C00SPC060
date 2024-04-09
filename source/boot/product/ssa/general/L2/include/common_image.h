/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : common_image.h
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

#ifndef __COMMON_IMAGE_H__
#define __COMMON_IMAGE_H__

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
/** \addtogroup     COMMON_IMAGE */
/** @{ */  /** <!-- [COMMON_IMAGE] */

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     COMMON_IMAGE */
/** @{ */  /** <!-- [COMMON_IMAGE] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     COMMON_IMAGE */
/** @{ */  /** <!-- [COMMON_IMAGE] */

HI_S32 SSA_ComSingedImgRead
(
    LOADER_FLASH_OPENPARAM_S*  pstDataParam,
    LOADER_FLASH_OPENPARAM_S*  pstSignParam,
    HI_U8*                     pu8DataBuffer,
    HI_U32                     u32DataBufferSize,
    HI_U8*                     pu8SignBuffer,
    HI_U32                     u32SignBufferSize
);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif /*__COMMON_IMAGE_H__*/

