/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_mailbox.h
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 2016-11-4
  Description   :
  History       :
  1.Date        :
  Author        : sdk
  Modification  :

*******************************************************************************/
#ifndef __HI_UNF_MAILBOX_H__
#define __HI_UNF_MAILBOX_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/** Mailbox ID */
#define MID_SCPU_COMMON          (0x01)
#define MID_TCPU_COMMON          (0x40)
#define MID_ACPU_COMMON          (0x60)

typedef struct
{
    HI_VOID *pMessage;
    HI_U32 u32MessageLen;
    HI_VOID *pOutBuffer;
    HI_U32 *pu32OutBufferLen;
} HI_UNF_MAILBOX_BUFFER_S;

/******************************* API declaration *****************************/

/**
\brief Initializes the mailbox module. CNcomment:初始化Mailbox模块 CNend
\attention \n
Before calling other functions in this file, you must call this application programming interface (API).
\param N/A
\retval ::HI_SUCCESS  Success.       CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.       CNcomment:API系统调用失败 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_MAILBOX_Init(HI_VOID);

/**
\brief Deinitializes the mailbox module. CNcomment:去初始化Mailbox设备 CNend
\attention \n
N/A
\param N/A                           CNcomment:无。 CNend
\retval ::HI_SUCCESS  Success.       CNcomment:API系统调用成功 CNend
\retval ::HI_FAILURE  Failure.       CNcomment:API系统调用失败 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_MAILBOX_DeInit(HI_VOID);

/**
\brief Open mailbox device.                      CNcomment:打开 mailbox 设备，返回 maibox 句柄。 CNend
\attention \n
N/A
\param[out] pHandle: Create handle/A             CNcomment:无。 CNend
\param[in]  u32Id:  mailbox ID, now it is fixed to MID_ACPU_COMMON/A  CNcomment:无。 CNend

\retval ::HI_SUCCESS  Call this API successful.  CNcomment:系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API failure.     CNcomment:分配句柄失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_MAILBOX_Open(HI_HANDLE* pHandle, HI_U32 u32Id);

/**
\brief Destory mailbox instance.                 CNcomment:关闭 mailbox 设备实例。 CNend
\attention \n
N/A
\param [in] handle: mailbox instance handle/A    CNcomment:无。 CNend
\retval ::HI_SUCCESS  Call this API successful.  CNcomment:系统调用成功。 CNend
\retval ::HI_FAILURE  Call this API failure.     CNcomment:释放句柄失败。 CNend
\see \n
N/A
*/
HI_S32 HI_UNF_MAILBOX_Close(HI_HANDLE handle);

/**
\brief  send data by mailbox.                    CNcomment:通过 mailbox 发送数据。 CNend
\attention \n
N/A
\param [in] handle: mailbox instance handle/A
\param [in] u32ReceiverId: mailbox ID of data receiver/A
\param [in/out] pstBuffer: intput and output buffer/A
\param [in] u32Flags: mailbox mode. 0 means block mode, 1 means timeout mode/A
\param [in] u32Param: mailbox max wait time, it is valid when mailbox mode is set to 1/A
\retval ::HI_SUCCESS  Call this API successful.
\retval ::HI_FAILURE  Call this API failure.
\see \n
N/A
*/
HI_S32 HI_UNF_MAILBOX_Send
(
    HI_HANDLE handle,
    HI_U32 u32ReceiverId,
    HI_UNF_MAILBOX_BUFFER_S *pstBuffer,
    HI_U32 u32Flags,
    HI_U32 u32Param
);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif /** __HI_UNF_MAILBOX_H__*/

