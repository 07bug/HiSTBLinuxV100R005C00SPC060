/******************************************************************************
 *
 * Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : hal_mailbox_reg.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-08-18
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __HAL_MAILBOX_REG_H__
#define __HAL_MAILBOX_REG_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cpluscplus */


/*************************** Macro Definition *********************************/
/** \addtogroup     DRV_MAILBOX */
/** @{ */  /** <!-- [DRV_MAILBOX] */

//acpu to scpu
#define ACPU_TO_SCPU_BASE_ADDRESS     (0xF8ABD000)
#define ACPU_TO_SCPU_HEAD_ADDRESS     (0x0020)
#define ACPU_TO_SCPU_ARGS_ADDRESS     (0x0040)
#define ACPU_TO_SCPU_ARGS_NUM         (16)

#define ACPU_TO_SCPU_SEND_ADDRESS     (0x0400)
#define SCPU_INTR_FROM_ACPU_ADDRESS   (0x0408)

//acpu to smcu
#define ACPU_TO_SMCU_BASE_ADDRESS     (0xF9A39000)
#define ACPU_TO_SMCU_HEAD_ADDRESS     (0x0020)
#define ACPU_TO_SMCU_ARGS_ADDRESS     (0x0040)
#define ACPU_TO_SMCU_ARGS_NUM         (8)

#define ACPU_TO_SMCU_SEND_ADDRESS     (0x0400)
#define SMCU_INTR_FROM_ACPU_ADDRESS   (0x0408)

//scpu to acpu
#define SCPU_TO_ACPU_HEAD_ADDRESS     (0x0100)
#define SCPU_TO_ACPU_ARGS_ADDRESS     (0x0110)
#define SCPU_TO_ACPU_ARGS_NUM         (4)
#define ACPU_INTR_FROM_SCPU_ADDRESS   (0x0418)


//smcu to acpu
#define SMCU_TO_ACPU_HEAD_ADDRESS     (0x0100)
#define SMCU_TO_ACPU_ARGS_ADDRESS     (0x0110)
#define SMCU_TO_ACPU_ARGS_NUM         (4)
#define ACPU_INTR_FROM_SMCU_ADDRESS   (0x0418)


/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     DRV_MAILBOX */
/** @{ */  /** <!-- [DRV_MAILBOX] */


/****** Structure definition **************/


/** @}*/  /** <!-- ==== Structure Definition End ====*/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cpluscplus */

#endif /* __HAL_MAILBOX_REG_H__ */


