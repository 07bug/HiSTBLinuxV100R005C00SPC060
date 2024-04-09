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
#ifndef __HI_MPI_OTP_V100_H__
#define __HI_MPI_OTP_V100_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#if defined(CHIP_TYPE_hi3798cv200)

#define OTP_ADDR_TA1_SEGMENTATIONID         0x520
#define OTP_TA_SEGMENTATIONID_LEN           0x08
#define OTP_TA_SM_LEN                       0x4
#else

#define OTP_ADDR_TA1_SEGMENTATIONID         0x580
#define OTP_TA_SEGMENTATIONID_LEN           0x10
#define OTP_TA_SM_LEN                       0x4

#endif

#define CHECK_NULL_PTR(ptr)\
do{\
    if(NULL == ptr )\
    {\
        HI_ERR_OTP("point is null\n");\
        return HI_ERR_OTP_PTR_NULL;\
    }\
}while(0)

#define CHECK_OTP_PARAM(val) \
do{\
    if(val) \
    {\
        HI_ERR_OTP("otp param is invalid\n");\
        return HI_ERR_OTP_INVALID_PARA;\
    }\
}while(0)

HI_S32 HI_MPI_OTP_Init(HI_VOID);
HI_S32 HI_MPI_OTP_DeInit(HI_VOID);
HI_S32 HI_MPI_OTP_SetCustomerKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_MPI_OTP_GetCustomerKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_MPI_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data);
HI_S32 HI_MPI_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data);
HI_S32 HI_MPI_OTP_WriteHdcpRootKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_MPI_OTP_ReadHdcpRootKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_MPI_OTP_LockHdcpRootKey(HI_VOID);
HI_S32 HI_MPI_OTP_GetHdcpRootKeyLockFlag(HI_BOOL *pbKeyLockFlag);
HI_S32 HI_MPI_OTP_WriteStbRootKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_MPI_OTP_ReadStbRootKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);
HI_S32 HI_MPI_OTP_LockStbRootKey(HI_VOID);
HI_S32 HI_MPI_OTP_GetStbRootKeyLockFlag(HI_BOOL *pbKeyLockFlag);
HI_S32 HI_MPI_OTP_SetTAIDAndMSID(const HI_UNF_OTP_TA_INDEX_E enIndex, HI_U32 u32TAID, HI_U32 u32MSID);
HI_S32 HI_MPI_OTP_GetTAIDAndMSID(const HI_UNF_OTP_TA_INDEX_E enIndex, HI_U32* pu32TAID, HI_U32* pu32MSID);
HI_S32 HI_MPI_OTP_BurnToNormalChipset(HI_VOID);
HI_S32 HI_MPI_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag);
HI_S32 HI_MPI_OTP_LockIDWord(HI_VOID);
HI_S32 HI_MPI_OTP_BurnToSecureChipset(HI_VOID);
HI_S32 HI_MPI_OTP_SetRootKey(HI_UNF_OTP_ROOTKEY_E type, HI_U8 *key, HI_U32 len);
HI_S32 HI_MPI_OTP_GetRootKeyLockStat(HI_UNF_OTP_ROOTKEY_E type, HI_BOOL *pbLock);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_MPI_OTP_V100_H__ */

