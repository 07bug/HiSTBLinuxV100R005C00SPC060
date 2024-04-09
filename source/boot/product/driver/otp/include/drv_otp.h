/******************************************************************************
 Copyright (C), 2001-2012, Hisilicon Tech. Co., Ltd.
******************************************************************************
 File Name     : mpi_otp.h
 Version       : Initial Draft
 Author        : Hisilicon multimedia software group
 Created       :
 Last Modified :
 Description   :
 Function List :
 History       :
******************************************************************************/
#ifndef __DRV_OTP_H__
#define __DRV_OTP_H__

#include "hi_type.h"
#include "hi_unf_otp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32 DRV_OTP_Init(HI_VOID);

HI_S32 DRV_OTP_DeInit(HI_VOID);

HI_S32 DRV_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data);

HI_S32 DRV_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data);

HI_S32 DRV_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen);

HI_S32 DRV_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag);

HI_S32 DRV_OTP_LockIDWord(HI_VOID);

HI_S32 DRV_OTP_BurnToNormalChipset(HI_VOID);

HI_S32 DRV_OTP_BurnToSecureChipset(HI_VOID);

HI_U32 DRV_OTP_Read(HI_U32 addr);

HI_U8  DRV_OTP_ReadByte(HI_U32 addr);

HI_S32 DRV_OTP_WriteByte(HI_U32 addr, HI_U8 u8data);

HI_S32 DRV_OTP_GetTrustZoneStat(HI_BOOL *pbEnable);


HI_S32 DRV_OTP_GetRSALockStat(HI_BOOL *pbLock);

HI_S32 DRV_OTP_SetRSAKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);

HI_S32 DRV_OTP_GetSCSStat(HI_BOOL *enable);

HI_S32 DRV_OTP_GetBootMode(HI_UNF_OTP_FLASH_TYPE_E *enFlashType);

HI_S32 DRV_OTP_EnableSCS(HI_VOID);

HI_S32 DRV_OTP_SetBootMode(HI_UNF_OTP_FLASH_TYPE_E flash_type);

HI_S32 DRV_OTP_EnableSocTee(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __DRV_OTP_H__ */

