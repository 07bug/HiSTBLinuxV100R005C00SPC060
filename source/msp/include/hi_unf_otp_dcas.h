/******************************************************************************

  Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_otp_dcas.h
  Version       : Initial Draft
  Author        : Hisilicon otp software group
  Created       : 2017/1/14
  Description   :
*******************************************************************************/
#ifndef __HI_UNF_OTP_DCAS_H__
#define __HI_UNF_OTP_DCAS_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      OTP_DCAS */
/** @{ */  /** <!-- [OTP_DCAS] */


/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      OTP_DCAS */
/** @{ */  /** <!-- [OTP_DCAS] */


/**
\brief Get the chipID. CNcomment:��ȡоƬID CNend
\attention \n
\param[out] pu8ChipID point to chip id. CNcomment:ָ�����ͣ�оƬID CNend
\param[in/out] pu32Len Point to the length of ChipID, current output length is 8. CNcomment:ָ�����ͣ�оƬID���ȣ���ǰ���8 CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_OTP_SETPARAM_AGAIN The parameter has been set already. CNcomment:�ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_DCAS_GetChipID(HI_U8 *pu8ChipID, HI_U32 *pu32Len);


/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_OTP_DCAS_H__ */
