/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_otp.h
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2014-09-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __HI_UNF_OTP_H__
#define __HI_UNF_OTP_H__

#define  HI_ERR_OTP_NOT_SUPPORT_INTERFACE         (HI_S32)(0x808F0002)

/** FLASH device types*/
typedef enum
{
    HI_UNF_OTP_FLASH_TYPE_SPI     = 0,    /**<SPI flash*/
    HI_UNF_OTP_FLASH_TYPE_NAND,           /**<nand flash*/
    HI_UNF_OTP_FLASH_TYPE_NOR,            /**<nor flash*/
    HI_UNF_OTP_FLASH_TYPE_EMMC,           /**<eMMC*/
    HI_UNF_OTP_FLASH_TYPE_SPI_NAND,       /**<spi_nand flash*/
    HI_UNF_OTP_FLASH_TYPE_SD,             /**<FSD/TSD flash*/
    HI_UNF_OTP_FLASH_TYPE_BUTT
} HI_UNF_OTP_FLASH_TYPE_E;


HI_S32 HI_UNF_OTP_Init(HI_VOID);

HI_S32 HI_UNF_OTP_DeInit(HI_VOID);

HI_S32 HI_UNF_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data);

HI_S32 HI_UNF_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data);

HI_S32 HI_UNF_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen);

HI_S32 HI_UNF_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag);

HI_S32 HI_UNF_OTP_LockIDWord(HI_VOID);

HI_S32 HI_UNF_OTP_BurnToNormalChipset(HI_VOID);

HI_S32 HI_UNF_OTP_BurnToSecureChipset(HI_VOID);

HI_U32 HI_UNF_OTP_Read(HI_U32 addr);

HI_U8  HI_UNF_OTP_ReadByte(HI_U32 addr);

HI_S32 HI_UNF_OTP_WriteByte(HI_U32 addr, HI_U8 u8data);

HI_S32 HI_UNF_OTP_GetTrustZoneStat(HI_BOOL *pbEnable);

HI_S32 HI_UNF_OTP_GetRSALockStat(HI_BOOL *pbLock);

HI_S32 HI_UNF_OTP_SetRSAKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);

HI_S32 HI_UNF_OTP_GetSCSStat(HI_BOOL *pbEnable);

HI_S32 HI_UNF_OTP_GetBootMode(HI_UNF_OTP_FLASH_TYPE_E *enFlashType);

HI_S32 HI_UNF_OTP_EnableSCS(HI_VOID);

HI_S32 HI_UNF_OTP_SetBootMode(HI_UNF_OTP_FLASH_TYPE_E enFlashType);

HI_S32 HI_UNF_OTP_EnableSocTee(HI_VOID);

HI_S32 HI_UNF_OTP_GetSocTeeStat(HI_BOOL *pbEnable);

#endif

