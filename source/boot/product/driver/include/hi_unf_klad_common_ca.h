/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_klad_common_ca.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   : Key ladder API declaration for common ca
Function List :
History       :
******************************************************************************/
#ifndef __HI_UNF_KLAD_COMMON_CA_H__
#define __HI_UNF_KLAD_COMMON_CA_H__

#include "hi_type.h"
#include "hi_unf_klad.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      COMMON_CA */
/** @{ */  /** <!-- [COMMON_CA] */

/*
Level: 2/3 depends on OTP
Algorithm: TDES/AES
Target Engine: Demux - AES/NOVEL/SM4/TDES; Payload cipher - AES; Multicipher - fixed
*/
#define HI_UNF_KLAD_COMMON_CA_TYPE_R2R    0x3f03


/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      COM_CA */
/** @{ */  /** <!-- [COM_CA] */


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_KLAD_COMMON_CA_H__ */

