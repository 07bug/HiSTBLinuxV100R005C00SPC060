/******************************************************************************
 *
 * Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : hal_mailbox.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2017-08-18
 * Last Modified :
 * Description   :
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __HAL_MAILBOX_H__
#define __HAL_MAILBOX_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cpluscplus */


/*************************** Macro Definition *********************************/
/** \addtogroup     HAL_MAILBOX */
/** @{ */  /** <!-- [HAL_MAILBOX] */

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition *****************************/
/** \addtogroup     HAL_MAILBOX */
/** @{ */  /** <!-- [HAL_MAILBOX] */


/****** Structure definition **************/

typedef union
{
    struct
    {
        unsigned int reserved0           : 8;  /** [7:0]   */
        unsigned int length              : 7;  /** [13:8]  */
        unsigned int reserved1           : 1;  /** [15:14] */
        unsigned int receiver            : 7;  /** [22:16] */
        unsigned int end                 : 1;  /** [23]    */
        unsigned int sender              : 7;  /** [30:24] */
        unsigned int start               : 1;  /** [31]    */
    } bits;

    unsigned int u32;
} MBOX_MSG_HEAD_U;

typedef union
{
    struct
    {
        unsigned int cmd_send             : 1;  /** [0]     */
        unsigned int reserved             : 31; /** [31:1] */
    } bits;

    unsigned int u32;
} MBOX_CDM_SEND_U;

typedef union
{
    struct {
        unsigned int intr                 : 1;  /** [0] */
        unsigned int reserved             : 31; /** [31:1] */
    } bits;

    unsigned int u32;
} MBOX_INTR_STATUS_U;


/** @}*/  /** <!-- ==== Structure Definition End ====*/


HI_S32 HAL_MAILBOX_WriteHeadToScpu(HI_U32 receive, HI_U32 length, HI_BOOL start, HI_BOOL end);

HI_S32 HAL_MAILBOX_WriteBodyToScpu(HI_U8 *message, HI_U32 length);

HI_U32 HAL_MAILBOX_ReadHeadFromScpu(HI_VOID);

HI_S32 HAL_MAILBOX_ReadBodyFromScpu(HI_U8 *message, HI_U32 length);

HI_VOID HAL_MAILBOX_SetSendCmdToScpu(HI_VOID);

HI_BOOL HAL_MAILBOX_CheckScpuReceive(HI_VOID);

HI_BOOL HAL_MAILBOX_CheckScpuSend(HI_VOID);

HI_VOID HAL_MAILBOX_CleanIntrFromScpu(HI_VOID);

HI_U32  HAL_MAILBOX_GetBodySizeToScpu(HI_VOID);

HI_S32 HAL_MAILBOX_WriteHeadToSmcu(HI_U32 receive, HI_U32 length, HI_BOOL start, HI_BOOL end);

HI_S32 HAL_MAILBOX_WriteBodyToSmcu(HI_U8 *message, HI_U32 length);

HI_U32 HAL_MAILBOX_ReadHeadFromSmcu(HI_VOID);

HI_S32 HAL_MAILBOX_ReadBodyFromSmcu(HI_U8 *message, HI_U32 length);

HI_VOID HAL_MAILBOX_SetSendCmdToSmcu(HI_VOID);

HI_BOOL HAL_MAILBOX_CheckSmcuReceive(HI_VOID);

HI_BOOL HAL_MAILBOX_CheckSmcuSend(HI_VOID);

HI_VOID HAL_MAILBOX_CleanIntrFromSmcu(HI_VOID);

HI_U32  HAL_MAILBOX_GetBodySizeToSmcu(HI_VOID);

HI_U32  HAL_MAILBOX_GetBodySizeFromSmcu(HI_VOID);

HI_U32  HAL_MAILBOX_GetBodySizeFromScpu(HI_VOID);

HI_S32 HAL_MAILBOX_Init(HI_VOID);

HI_S32 HAL_MAILBOX_DeInit(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cpluscplus */

#endif /* __HAL_MAILBOX_H__ */


