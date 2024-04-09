/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : unf_otp_dcas.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-16
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include <errno.h>
#include <sys/ioctl.h>
#include <string.h>
#include "hi_debug.h"
#include "hi_type.h"
#include "hi_error_mpi.h"
#include "otp_enum.h"
#include "hi_unf_otp.h"
#include "hi_unf_otp_dcas.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

extern HI_S32 OTP_DRV_PVItem(HI_OTP_DATA_E field_id, HI_BOOL is_write,
                             HI_U8 *value, HI_U32 *value_len, HI_BOOL is_lock);

#define CHECK_NULL_PTR(ptr)\
    do{\
        if(NULL == ptr )\
        {\
            HI_FATAL_PRINT(HI_ID_OTP, "Null point.\n"); \
            return HI_ERR_OTP_PTR_NULL;\
        }\
    }while(0)

HI_S32 HI_UNF_OTP_DCAS_GetChipID(HI_U8 *pu8ChipID, HI_U32 *pu32Len)
{
    CHECK_NULL_PTR(pu8ChipID);
    CHECK_NULL_PTR(pu32Len);

    if (*pu32Len != 8)
    {
        HI_FATAL_PRINT(HI_ID_OTP, "Get ChipID, parameters check failed.len=%d.\n", *pu32Len);
        return HI_FAILURE;
    }

    return OTP_DRV_PVItem(HI_OTP_DCASCHIPID, HI_FALSE, pu8ChipID, pu32Len, HI_TRUE);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
