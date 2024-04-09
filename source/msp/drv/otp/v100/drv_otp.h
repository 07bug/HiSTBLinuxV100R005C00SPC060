/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : drv_otp.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#ifndef __DRV_OTP_H__
#define __DRV_OTP_H__

#include "hi_common.h"
#include "hi_type.h"
#ifdef SDK_OTP_ARCH_VERSION_V3
#include "drv_otp_ioctl.h"
#else
#include "priv_otp.h"
#endif
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
typedef enum
{
    DRV_OTP_NO_FAKE_FLAG               = 0X00,
    DRV_OTP_GET_FAKE_BUFFER_FLAG       = 0X01,
    DRV_OTP_FAKE_BUFFER_FLAG           = 0X10,
    DRV_OTP_FAKE_BUFFER_RESET_FLAG     = 0X11,
    DRV_OTP_FAKE_ACCESS_ERR_FLAG       = 0X20,
    DRV_OTP_CLEAR_OTP_FAKE_BUFFER      = 0X30,
    DRV_OTP_FAKE_BUTT
}DRV_OTP_FAKE_FLAG_E;
#endif
/******* proc function end   ********/

HI_S32 DRV_OTP_Init(void);
HI_S32 DRV_OTP_DeInit(void);
HI_U32 DRV_OTP_Read(HI_U32 Addr);
HI_U8 DRV_OTP_ReadByte(HI_U32 Addr);
HI_S32 DRV_OTP_Write(HI_U32 Addr, HI_U32 value);
HI_S32 DRV_OTP_Write_Byte(HI_U32 Addr, HI_U8 value);
HI_S32 DRV_OTP_Write_Bit(HI_U32 Addr, HI_U32 BitPos, HI_U32 BitValue);
HI_S32 DRV_OTP_Reset(HI_VOID);
HI_S32 DRV_OTP_Set_CustomerKey(OTP_CUSTOMER_KEY_S *pCustomerKey);
HI_S32 DRV_OTP_Get_CustomerKey(OTP_CUSTOMER_KEY_S *pCustomerKey);
HI_S32 DRV_OTP_Get_DDPLUS_Flag(HI_BOOL *pDDPLUSFlag);
HI_S32 DRV_OTP_Get_DTS_Flag(HI_BOOL *pDTSFlag);
HI_S32 DRV_OTP_Set_StbPrivData(OTP_STB_PRIV_DATA_S *pStbPrivData);
HI_S32 DRV_OTP_Get_StbPrivData(OTP_STB_PRIV_DATA_S *pStbPrivData);

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
HI_S32 DRV_OTP_Is_FakeOTPBuffer_Flag(HI_VOID);
HI_S32 DRV_OTP_Is_FakeOTPAccessErr_Flag(HI_VOID);
HI_S32 DRV_OTP_GetFakeOTPFlag(HI_VOID);
HI_S32 DRV_OTP_SetFakeOTPFlag(HI_U32 u32Value);
HI_S32 DRV_OTP_FakeOTP_ReadByte(HI_U32 Addr);
HI_S32 DRV_OTP_FakeOTP_WriteByte(HI_U32 Addr, HI_U8 value);
HI_VOID DRV_OTP_ClearFakeOTPBuffer(HI_VOID);
#endif
/******* proc function end   ********/

HI_S32 DRV_OTP_DieID_Check(HI_VOID);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* __DRV_OTP_H__ */
