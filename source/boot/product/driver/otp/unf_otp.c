/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_otp.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2014-09-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hi_type.h"
#include "exports.h"
#include "hi_unf_otp.h"
#include "drv_otp.h"
#include "otp_debug.h"

HI_S32 HI_UNF_OTP_Init(HI_VOID)
{
    return DRV_OTP_Init();
}

HI_S32 HI_UNF_OTP_DeInit(HI_VOID)
{
    return DRV_OTP_DeInit();
}

HI_S32 HI_UNF_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen)
{
    return DRV_OTP_GetCustomerKey(pKey, u32KeyLen);
}


HI_S32 HI_UNF_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data)
{
    return DRV_OTP_SetStbPrivData(u32Offset, u8Data);
}

HI_S32 HI_UNF_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data)
{
    return DRV_OTP_GetStbPrivData(u32Offset, pu8Data);
}

HI_S32 HI_UNF_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag)
{
    return DRV_OTP_GetIDWordLockFlag(pbLockFlag);
}

HI_S32 HI_UNF_OTP_LockIDWord(HI_VOID)
{
    return DRV_OTP_LockIDWord();
}

HI_S32 HI_UNF_OTP_BurnToSecureChipset(HI_VOID)
{
    return DRV_OTP_BurnToSecureChipset();
}

HI_S32 HI_UNF_OTP_BurnToNormalChipset(HI_VOID)
{
    return DRV_OTP_BurnToNormalChipset();
}

HI_S32 HI_UNF_OTP_GetTrustZoneStat(HI_BOOL *pbEnable)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    return DRV_OTP_GetTrustZoneStat(pbEnable);
#else
    HI_ERR_OTP("Not support now!!!\n");
    return HI_FAILURE;
#endif
}

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100) || defined(CHIP_TYPE_hi3798mv200) || defined(CHIP_TYPE_hi3798mv300)
HI_S32 HI_OTP_LockIdWord(HI_VOID)
{
    HI_S32 ret = 0;
    HI_BOOL bLockFlag = HI_FALSE;

    ret = HI_UNF_OTP_GetIDWordLockFlag(&bLockFlag);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Get ID_WORD lock flag failed! Ret = %x\n");
        return HI_FAILURE;
    }

    if (bLockFlag == HI_TRUE)
    {
        HI_PRINT("ID_WORD have already been locked\n");
        return HI_SUCCESS;
    }

#ifdef HI_ADVCA_SUPPORT
    /* Check and burn to secure chipset */
    ret = HI_UNF_OTP_BurnToSecureChipset();
    if (HI_SUCCESS != ret)
    {
        HI_PRINT("Burn to secure chipset failed! Ret = %x\n", ret);
        return HI_FAILURE;
    }
    HI_PRINT("Burn to secure chipset success!\n");

#else
    ret = HI_UNF_OTP_BurnToNormalChipset();
    if (HI_SUCCESS != ret)
    {
        HI_PRINT("Burn to nomal chipset failed! Ret = %x\n", ret);
        return HI_FAILURE;
    }
    HI_PRINT("Burn to nomal chipset success!\n");
#endif

    return HI_SUCCESS;
}
#endif

HI_U32 HI_UNF_OTP_Read(HI_U32 addr)
{
    return DRV_OTP_Read(addr);
}

HI_U8 HI_UNF_OTP_ReadByte(HI_U32 addr)
{
    return DRV_OTP_ReadByte(addr);
}

HI_S32 HI_UNF_OTP_Write(HI_U32 addr, HI_U32 u32Data)
{
    return HI_UNF_OTP_Write(addr, u32Data);
}

HI_S32 HI_UNF_OTP_WriteByte(HI_U32 addr, HI_U8 u8data)
{
    return DRV_OTP_WriteByte(addr, u8data);
}

HI_S32 HI_UNF_OTP_GetRSALockStat(HI_BOOL *pbLock)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    return DRV_OTP_GetRSALockStat(pbLock);
#else
    HI_ERR_OTP("Not support now!!!\n");
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_SetRSAKey(HI_U8 *pu8Key, HI_U32 u32KeyLen)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    return DRV_OTP_SetRSAKey(pu8Key, u32KeyLen);
#else
    HI_ERR_OTP("Not support now!!!\n");
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_GetSCSStat(HI_BOOL *pbEnable)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    return DRV_OTP_GetSCSStat(pbEnable);
#else
    HI_ERR_OTP("Not support now!!!\n");
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_GetBootMode(HI_UNF_OTP_FLASH_TYPE_E *enFlashType)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    return DRV_OTP_GetBootMode(enFlashType);
#else
    HI_ERR_OTP("Not support now!!!\n");
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_EnableSCS(HI_VOID)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    return DRV_OTP_EnableSCS();
#else
    HI_ERR_OTP("Not support now!!!\n");
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_SetBootMode(HI_UNF_OTP_FLASH_TYPE_E enFlashType)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    return DRV_OTP_SetBootMode(enFlashType);
#else
    HI_ERR_OTP("Not support now!!!\n");
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_EnableSocTee(HI_VOID)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    return DRV_OTP_EnableSocTee();
#else
    HI_ERR_OTP("Not support now!!!\n");
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

HI_S32 HI_UNF_OTP_GetSocTeeStat(HI_BOOL *pbEnable)
{
#if (defined(CHIP_TYPE_hi3796mv200) || defined(CHIP_TYPE_hi3716mv450))
    return DRV_OTP_GetTrustZoneStat(pbEnable);
#else
    HI_ERR_OTP("Not support now!!!\n");
    return HI_ERR_OTP_NOT_SUPPORT_INTERFACE;
#endif
}

