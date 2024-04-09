/******************************************************************************

          Copyright (C), 2001-2015, Hisilicon Technologies Co., Ltd.
 ******************************************************************************
 File Name       : l2_config.h
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

#ifndef __L2_CONFIG_H__
#define __L2_CONFIG_H__

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
/** \addtogroup     L2_CONFIG */
/** @{ */  /** <!-- [L2_CONFIG] */

#define SSA_LEN_COMMAND                 (1024)
#define SSA_LEN_IMG_HEADER_SIGN         (256)
#define SSA_LEN_IMG_HEADER_SIGN_POS     (16)
#define SSA_LEN_IMG_HEADER              (SSA_LEN_IMG_HEADER_SIGN + SSA_LEN_IMG_HEADER_SIGN_POS)
#define SSA_IMG_HEADER_LEN              (0x2000)
#define SSA_KEY_AREA_OFFSET             (0x00010000)


#if defined(HI_ANDROID_BOOT_SUPPORT)
#define SSA_VERIFY_ADDR_KERNEL          (HI_U8*)(0x01FFFFC0 - SSA_LEN_IMG_HEADER)
#define SSA_VERIFY_ADDR_LOADER          (HI_U8*)(0x01FFFFC0 - SSA_LEN_IMG_HEADER)
#define SSA_VERIFY_ADDR_BOOTARGS        (HI_U8*)(0x08000000)
#define SSA_VERIFY_ADDR_RESERVE         (HI_U8*)(0x0C000000)
#define SSA_VERIFY_ADDR_TEEOS           (HI_U8*)(0x0801E000)

#define SSA_VERIFY_SIZE_KERNEL          (0x02000000)
#define SSA_VERIFY_SIZE_LOADER          (0x02000000)
#define SSA_VERIFY_SIZE_BOOTARGS        (0x00100000)
#define SSA_VERIFY_SIZE_VERIFY          (0x19000000)
#define SSA_VERIFY_SIZE_TEEOS           (0x04000000)

#else
#define SSA_VERIFY_ADDR_KERNEL          (HI_U8*)(0x01FFFFC0 - SSA_LEN_IMG_HEADER)
#define SSA_VERIFY_ADDR_LOADER          (HI_U8*)(0x01FFFFC0 - SSA_LEN_IMG_HEADER)
#define SSA_VERIFY_ADDR_BOOTARGS        (HI_U8*)(0x08000000)
#define SSA_VERIFY_ADDR_RESERVE         (HI_U8*)(0x0C000000)
#define SSA_VERIFY_ADDR_TEEOS           (HI_U8*)(0x0801E000)

#define SSA_VERIFY_SIZE_KERNEL          (0x02000000)
#define SSA_VERIFY_SIZE_LOADER          (0x02000000)
#define SSA_VERIFY_SIZE_BOOTARGS        (0x00100000)
#define SSA_VERIFY_SIZE_VERIFY          (0x19000000)
#define SSA_VERIFY_SIZE_TEEOS           (0x04000000)
#endif

#define SSA_PARTSIZE_BOOT                   (0x00100000)

/** Partition define */
#define SSA_PARTNAME_BOOTARGS               "bootargs"
#define SSA_PARTNAME_LOGO                   "logo"
#define SSA_PARTNAME_KERNEL                 "kernel"
#define SSA_PARTNAME_SWINFO                 "softwareinfo"
#define SSA_PARTNAME_TEEOS                  "trustedcore"

#if defined(HI_ANDROID_BOOT_SUPPORT)
#define SSA_PARTNAME_ROOTFS                 "shatable"
#if defined(HI_APPLOADER_SUPPORT)
#define SSA_PARTNAME_LOADER                 "loader"
#else
#define SSA_PARTNAME_LOADER                 "recovery"
#endif
#else
#define SSA_PARTNAME_ROOTFS                 "rootfs"
#define SSA_PARTNAME_LOADER                 "loader"
#endif

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     L2_CONFIG */
/** @{ */  /** <!-- [L2_CONFIG] */

/****** Enumeration definition ************/

/****** Structure definition **************/

/****** Union definition ******************/

/****** Global variable declaration *******/

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration ******************************/
/** \addtogroup     L2_CONFIG */
/** @{ */  /** <!-- [L2_CONFIG] */

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif/*__L2_CONFIG_H__*/
