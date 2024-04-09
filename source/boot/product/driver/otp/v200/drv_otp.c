/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
    File Name   : mpi_otp_v200.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "string.h"
#include "hal_otp.h"
#include "drv_otp.h"
#include "otp_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define OTP_CUSTOMER_KEY_LEN                (16)
#define OTP_SOC_TEE_ENABLE                  (0x05)
#define OTP_SEC_WORD                        (0x60)
#define OTP_NORMAL_CHIP_VALUE               (0x2A13C812)
#define OTP_SECURE_CHIP_VALUE               (0x6EDBE953)

#define OTP_BOOT_MODE_SEL_ADDR              (0x00)
#define OTP_SCS_ACTIVATION_ADDR             (0x50)
#define OTP_BOOT_MODE_SEL_LOCK_ADDR         (0x100)
#define OTP_RSA_PUB_KEY_EXPO_LOCK_ADDR      (0x14E)
#define OTP_RSA_PUB_KEY_MODU_LOCK_ADDR      (0x14E)
#define OTP_STB_PRIV_DATA_ADDR              (0x220)
#define OTP_CUSTOMER_KEY_ADDR               (0x230)
#define OTP_RSA_ROOT_PUB_KEY_EXPO_ADDR      (0x6F0)
#define OTP_RSA_ROOT_PUB_KEY_MODU_ADDR      (0x700)


HI_S32 DRV_OTP_Init(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 DRV_OTP_DeInit(HI_VOID)
{
    return HI_SUCCESS;
}

HI_S32 DRV_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data)
{
    OTP_CHECK_PARAM(u32Offset >= 16);

    return HAL_OTP_WriteByte(OTP_STB_PRIV_DATA_ADDR + u32Offset, u8Data);
}

HI_S32 DRV_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data)
{
    HI_U8 value = 0;
    HI_S32 ret  = HI_FAILURE;

    OTP_CHECK_PARAM(u32Offset >= 16);
    OTP_CHECK_PARAM(HI_NULL == pu8Data);

    ret = HAL_OTP_ReadByte(OTP_STB_PRIV_DATA_ADDR + u32Offset, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get stb priv data, return:%x\n", ret);
        return HI_FAILURE;
    }

    *pu8Data = value;

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen)
{
    HI_U8 customerkey[OTP_CUSTOMER_KEY_LEN] = {0};
    HI_S32 ret            = HI_FAILURE;
    HI_S32 i              = 0;

    OTP_CHECK_PARAM(HI_NULL == pKey);
    OTP_CHECK_PARAM(u32KeyLen != 16);

    for (i = 0; i < 16; i++)
    {
        ret = HAL_OTP_ReadByte(OTP_CUSTOMER_KEY_ADDR + i, &customerkey[i]);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_OTP("failed to get customer key, return:%x\n", ret);
            return HI_FAILURE;
        }
    }

    memcpy(pKey, customerkey, OTP_CUSTOMER_KEY_LEN);

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag)
{
    return HI_FAILURE;
}

HI_S32 DRV_OTP_LockIDWord(HI_VOID)
{
    return HI_FAILURE;
}

HI_S32 DRV_OTP_BurnToNormalChipset(HI_VOID)
{
    HI_U32 value = OTP_NORMAL_CHIP_VALUE;
    HI_S32 ret  = HI_FAILURE;
    ret = HAL_OTP_Write(OTP_SEC_WORD, value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Write Normal Chip otp failed, return:%x\n", ret);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_S32 DRV_OTP_BurnToSecureChipset(HI_VOID)
{
    HI_U32 value = OTP_SECURE_CHIP_VALUE;
    HI_S32 ret  = HI_FAILURE;
    ret = HAL_OTP_Write(OTP_SEC_WORD, value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Write Secure Chip otp failed, return:%x\n", ret);
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_U32 DRV_OTP_Read(HI_U32 addr)
{
    HI_U32 value = 0;
    HI_S32 ret   = HI_FAILURE;

    ret = HAL_OTP_Read(addr, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to read otp, return:%x\n", ret);
        return 0;
    }

    return value;
}

HI_U8 DRV_OTP_ReadByte(HI_U32 addr)
{
    HI_U8  value = 0;
    HI_S32 ret   = HI_FAILURE;

    ret = HAL_OTP_ReadByte(addr, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to read otp, return:%x\n", ret);
        return 0;
    }

    return value;
}

HI_S32 DRV_OTP_WriteByte(HI_U32 addr, HI_U8 u8data)
{
    HI_S32 ret = HI_FAILURE;

    ret = HAL_OTP_WriteByte(addr, u8data);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to write otp, return:%x\n", ret);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetTrustZoneStat(HI_BOOL *pbEnable)
{
    HI_U8 value = 0;
    HI_S32 ret  = HI_FAILURE;

    OTP_CHECK_PARAM(HI_NULL == pbEnable);

    ret = HAL_OTP_ReadByte(OTP_SOC_TEE_ENABLE, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get tee status, return:%x\n", ret);
        return HI_FAILURE;
    }

    *pbEnable = (value == 0x42) ? HI_FALSE : HI_TRUE;

    return HI_SUCCESS;
}


HI_S32 DRV_OTP_GetRSALockStat(HI_BOOL *pbLock)
{
    HI_U8 value = 0;
    HI_S32 ret  = HI_FAILURE;

    OTP_CHECK_PARAM(HI_NULL == pbLock);

    ret = HAL_OTP_ReadByte(OTP_RSA_PUB_KEY_MODU_LOCK_ADDR, &value);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get RSA lock status, return:%x\n", ret);
        return HI_FAILURE;
    }

    if( 0x00 == (value&0x10))
    {
        *pbLock = HI_FALSE;
    }
    else
    {
        *pbLock = HI_TRUE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_SetRSAKey(HI_U8 *pu8Key, HI_U32 u32KeyLen)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 rsakey[0x200] = {0};
    HI_BOOL islocked;
    HI_U32 index = 0;
    HI_U8 u8Tmp = 0;
    HI_U8 *ptr = NULL;

    OTP_CHECK_PARAM(u32KeyLen != 0x200);
    OTP_CHECK_PARAM(HI_NULL == pu8Key);

    memcpy( rsakey, pu8Key, 0x200 );

    /* check if rsa key is locked or not */
    ret = DRV_OTP_GetRSALockStat( &islocked );
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Failed to Get rsa key lock status, return:%x\n", ret);
        return ret;
    }
    if(HI_TRUE == islocked)
    {
        HI_ERR_OTP("RSA Key has already been locked, can not be set any more.\n");
        return HI_FAILURE;
    }

    /* check if rsa key has been set or not */
    for(index = 0; index < 0x10; index++)
    {
        ret = HAL_OTP_ReadByte(OTP_RSA_ROOT_PUB_KEY_EXPO_ADDR + index, &u8Tmp);
        if(0x00 != u8Tmp)
        {
            HI_ERR_OTP("RSA Root Public KEY Exponent have been already set.\n");
            return HI_FAILURE;
        }
    }
    for(index = 0; index < 0x100; index++)
    {
        ret = HAL_OTP_ReadByte(OTP_RSA_ROOT_PUB_KEY_MODU_ADDR + index, &u8Tmp);
        if(0x00 != u8Tmp)
        {
            HI_ERR_OTP("RSA Root Public KEY Modulus have been already set.\n");
            return HI_FAILURE;
        }
    }

    /* Set rsa key */
    ptr = rsakey;
    for(index = 0; index < 0x100; index++)
    {
        ret = HAL_OTP_WriteByte(OTP_RSA_ROOT_PUB_KEY_MODU_ADDR + index, ptr[index]);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_OTP("Set RSA Root Public KEY Modulus failed ,ret:0x%x, index:0x%x.\n", ret, index);
            return HI_FAILURE;
        }
    }

    ptr = &rsakey[0x1F0];
    for(index = 0; index < 0x10; index++)
    {
        ret = HAL_OTP_WriteByte(OTP_RSA_ROOT_PUB_KEY_EXPO_ADDR + index, ptr[index]);
        if(HI_SUCCESS != ret)
        {
            HI_ERR_OTP("Set RSA Root Public KEY Exponent failed ,ret:0x%x, index:0x%x.\n", ret, index);
            return HI_FAILURE;
        }
    }

    /*Set RSA Key Lock*/
    u8Tmp = 0x18;
    ret = HAL_OTP_WriteByte(OTP_RSA_PUB_KEY_EXPO_LOCK_ADDR, u8Tmp);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Fail to write RSA lock!\n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetSCSStat(HI_BOOL *pbEnable)
{
    HI_S32 ret  = HI_FAILURE;
    HI_U8 ScsAct = 0;

    OTP_CHECK_PARAM(HI_NULL == pbEnable);

    ret = HAL_OTP_ReadByte(OTP_SCS_ACTIVATION_ADDR, &ScsAct);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("failed to get SCS Status, return:%x\n", ret);
        return HI_FAILURE;
    }

    *pbEnable = (ScsAct == 0x81) ? 0: 1;

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_GetBootMode(HI_UNF_OTP_FLASH_TYPE_E *enFlashType)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U8 bootMode = 0;

    OTP_CHECK_PARAM(NULL == enFlashType)

    bootMode = DRV_OTP_ReadByte(OTP_BOOT_MODE_SEL_ADDR);
    switch (bootMode)
    {
        case 0x00:
        {
            *enFlashType = HI_UNF_OTP_FLASH_TYPE_SPI;
            break;
        }
        case 0x01:
        {
            *enFlashType = HI_UNF_OTP_FLASH_TYPE_NAND;
            break;
        }
        case 0x02:
        {
            *enFlashType = HI_UNF_OTP_FLASH_TYPE_SD;
            break;
        }
        case 0x03:
        {
            *enFlashType = HI_UNF_OTP_FLASH_TYPE_EMMC;
            break;
        }
        default:
        {
            *enFlashType = HI_UNF_OTP_FLASH_TYPE_BUTT;
            break;
        }
    }

    return ret;
}

HI_S32 DRV_OTP_EnableSCS(HI_VOID)
{
    HI_U8 data = 0xFF;

    return HAL_OTP_WriteByte(OTP_SCS_ACTIVATION_ADDR, data);
}

HI_S32 DRV_OTP_SetBootMode(HI_UNF_OTP_FLASH_TYPE_E enFlashType)
{
    HI_S32 ret  = HI_FAILURE;
    HI_U8 data = 0;
    HI_U8 BootLock = 0;

    OTP_CHECK_PARAM(enFlashType >= HI_UNF_OTP_FLASH_TYPE_BUTT);

    BootLock = DRV_OTP_ReadByte(OTP_BOOT_MODE_SEL_LOCK_ADDR);
    if( 0x00 != BootLock )
    {
        HI_ERR_OTP("Boot Mode has already been locked, can not be set any more.\n");
        return HI_FAILURE;
    }

    data = enFlashType;
    ret = HAL_OTP_WriteByte(OTP_BOOT_MODE_SEL_ADDR, data);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Fail to write boot sel!\n");
        return ret;
    }

    data = 0xFF;
    ret = HAL_OTP_WriteByte(OTP_BOOT_MODE_SEL_LOCK_ADDR, data);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_OTP("Fail to write boot sel lock!\n");
        return ret;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_OTP_EnableSocTee(HI_VOID)
{
    HI_U8 data = 0xFF;

    return HAL_OTP_WriteByte(OTP_SOC_TEE_ENABLE, data);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
