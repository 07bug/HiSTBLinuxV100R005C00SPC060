/******************************************************************************
Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name   :  hi_unf_payloadcipher.h
Author        :  Hisilicon multimedia software group
Created      :  2016/10/21
Description :
******************************************************************************/
#ifndef __HI_UNF_PAYLOADCIPHER_H__
#define __HI_UNF_PAYLOADCIPHER_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      PayloadCipher */
/** @{ */  /** <!-- [PayloadCipher] */

/** Max pidFilter Num */
/**CNcomment:���PID������*/
#define HI_UNF_PLCIPHER_PIDFILTER_NUM 16

/** PLCipher algorithm */
/** CNcomment:PLCipher�����㷨*/
typedef enum
{
    HI_UNF_PLCIPHER_ALG_AES_IPTV            = 0x20,  /**<AES IPTV*/
    HI_UNF_PLCIPHER_ALG_AES_ECB             = 0x21,  /**<AES ECB*/
    HI_UNF_PLCIPHER_ALG_AES_CBC             = 0x22,  /**<AES CBC*/
    HI_UNF_PLCIPHER_ALG_AES_CISSA           = 0x23,  /**<AES CISSA*/
    HI_UNF_PLCIPHER_ALG_BUTT                = 0x84
}HI_UNF_PLCIPHER_ALG_E;

/** PLCipher Key Type */
/** CNcomment:PLCipher Key ����*/
typedef enum
{
    HI_UNF_PLCIPHER_KEY_EVEN       = 0,   /**< Even key type */ /**< CNcomment:żKEY����*/
    HI_UNF_PLCIPHER_KEY_ODD        = 1,   /**< Odd key type */ /**< CNcomment:��KEY����*/
    HI_UNF_PLCIPHER_KEY_BUTT,
}HI_UNF_PLCIPHER_KEY_EVENODD_E;

/** Structure of the plcipher control information */
/** CNcomment:���ܿ�����Ϣ�ṹ */
typedef struct
{
    HI_UNF_PLCIPHER_ALG_E enAlg;                   /**< Algorithm  type*/ /**< CNcomment:�㷨����*/
    HI_BOOL bPIDFilterEn;                          /**< Pid filter switch, default disable, plcipher will encrypt all pids in the ts when the switch is setted with HI_FALSE, and plcipher will just encrypt the assigned pids when the switch is setted with HI_TRUE*/
                                                   /**< CNcomment:Pid ����ʹ�ÿ��أ�Ĭ�Ϲرգ��ر�ʱplcipher����TS��������PID���м��ܣ���������ʱplcipher����ָ����PID���ݽ��м���*/
    HI_U32  u32PidNum;                             /**< valid when bPIDFilterEn is HI_TRUE, the pid number need to be filted.*/ /**< CNcomment:����bPIDFilterEnΪHI_TRUEʱ��Ч��Ҫ���˵�PID����*/
    HI_U16  u16PID[HI_UNF_PLCIPHER_PIDFILTER_NUM]; /**< valid when bPIDFilterEn is HI_TRUE, the pid arrays need to be filted.*/ /**< CNcomment:����bPIDFilterEnΪHI_TRUEʱ��Ч��Ҫ���˵�PID����*/
    HI_UNF_PLCIPHER_KEY_EVENODD_E enEvenOdd;       /**< Even Odd type, for keyladder encrypt even or odd key set */ /**< CNcomment:��ż���ͣ������keyladder ���ܳ���ʱ������ż����*/
} HI_UNF_PLCIPHER_ATTR_S;

/** @} */  /** <!-- ==== Structure Definition End ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      PayloadCipher */
/** @{ */  /** <!--[PayloadCipher]*/

/**
\brief Initializes the PLCIPHER module.CNcomment:��ʼ��PLCIPHERģ�顣CNend
\attention \n
Before using PLCIPHERs, you must call this application programming interface (API).\n
Before using the ts level encryption function, you need to initialize the PLCIPHER module.\n
The error code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:�ڽ���PLCIPHER��ز���ǰӦ�����ȵ��ñ��ӿ�\n
��ʹ��TS�����ܹ���ǰ����ǰ����PLCIPHERģ��ĳ�ʼ��\n
�ظ����ñ��ӿڷ��سɹ���CNend
\param  N/A.CNcomment:�ޡ�CNend
\retval ::HI_SUCCESS Success. CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
\see \n
N/A.CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_PLCIPHER_Init(HI_VOID);

/**
\brief Deinitializes the PLCIPHER module. CNcomment:ȥ��ʼ��PLCIPHERģ�顣CNend
\attention \n
After this API is called, the PLCIPHER module is stopped, and the PLCIPHER resources used by the process are released.\n
This API is valid when it is called for the first time. If this API is called repeatedly, the error code HI_SUCCESS is returned.
CNcomment:���ñ��ӿ�ֹͣʹ��PLCIPHERģ�飬���ͷű�������ռ�õ�PLCIPHER��Դ\n
���ӿڵ�һ�ε��������ã��ظ����÷��سɹ���CNend
\param  N/A.CNcomment:�ޡ�CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ���CNend
\retval ::HI_FAILURE Calling this API fails. CNcomment:APIϵͳ����ʧ�ܡ�CNend
\see \n
 N/A.CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_PLCIPHER_DeInit(HI_VOID);

/**
\brief Creates a PLCIPHER channel for encryption.CNcomment:����һ·PLCIPHERͨ����CNend
\param[out] phPLCipher     Pointer to the handle of a PLCIPHER.CNcomment:ָ�����ͣ�������뵽��PLCIPHER Handle��CNend
\retval ::HI_SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:ģ��û�г�ʼ����CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:ָ�����Ϊ�ա�CNend
\retval ::HI_ERR_PLCIPHER_FAILED_GETHANDLE There is no more PLCIPHER channel left. CNcomment:û�п��е�PLCIPHERͨ����CNend
\see \n
 N/A.CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_PLCIPHER_Create(HI_HANDLE *phPLCipher);

/**
\brief Destroys an existing PLCIPHER channel.CNcomment:����һ·PLCIPHERͨ����CNend
\param[in] hPLCipher  Handle of PLCIPHER channel to be destroyed.CNcomment:�����ٵ�PLCIPHER ͨ�������CNend
\retval ::HI_SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:ģ��û�г�ʼ����CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:����PLCIPHER����Ƿ���CNend
\see \n
 N/A.CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_PLCIPHER_Destroy(HI_HANDLE hPLCipher);

/**
\brief Gets the attributes of a PLCIPHER channel.CNcomment:��ȡһ·PLCIPHERͨ�������ԡ�CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER ͨ�������CNend
\param[out] pstAttr  Pointer to the attributes of a PLCIPHER channel.CNcomment:PLCIPHERͨ������ָ�롣CNend
\retval ::HI_SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:ģ��û�г�ʼ����CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:����PLCIPHER����Ƿ���CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:ָ�����Ϊ�ա�CNend
\see \n
 N/A.CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_PLCIPHER_GetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S *pstAttr);

/**
\brief Sets the attributes of a PLCIPHER channel.CNcomment:����һ·PLCIPHERͨ�������ԡ�CNend
\attention \n
plcipher will encrypt all pids in the ts when bPIDFilterEn is setted with HI_FALSE,\n
and plcipher will just encrypt the assigned pids when bPIDFilterEn is setted with HI_TRUE.
CNcomment:bPIDFilterEn ΪHI_FALSEʱplcipher����TS��������PID���м��ܣ�����bPIDFilterEn ΪHI_TRUEʱplcipher����ָ����PID���ݽ��м��ܡ�CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER ͨ�������CNend
\param[in] pstAttr  Pointer to the attributes of a PLCIPHER channel.CNcomment:PLCIPHERͨ������ָ�롣CNend
\retval ::HI_SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:ģ��û�г�ʼ����CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:����PLCIPHER����Ƿ���CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:ָ�����Ϊ�ա�CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PARA  The input attribute is invalid.CNcomment:�������Խṹ��Ա�Ƿ���CNend
\see \n
 N/A.CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_PLCIPHER_SetAttr(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_ATTR_S *pstAttr);

/**
\brief Sets the CW keys of a PLCIPHER channel. This API is used to configure the PLCIPHER channel.CNcomment:����PLCIPHERͨ������Կ�����ӿ���������PLCIPHERͨ������Կ��CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER ͨ�������CNend
\param[in] enKeyEvenOdd  Type of CW key odd or even.CNcomment:��������Կ����ż���͡�CNend
\param[in] pu8Key  Pointer to odd or even CW key buffer to be set, always a 8 or 16 bytes array.CNcomment:ָ�����ͣ�ָ��Ҫ���õ����ż��Կ���ݣ�һ��8��16���ֽڵ����顣CNend
\param[in] u32KeyLen  The length of CW key data to be set, always 8 or 16.CNcomment:Ҫ���õ���Կ���ݵĳ��ȣ�һ��8��16��CNend
\retval ::HI_SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:ģ��û�г�ʼ����CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:����PLCIPHER����Ƿ���CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:ָ�����Ϊ�ա�CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PARA  The input attribute is invalid.CNcomment:�������Խṹ��Ա�Ƿ���CNend
\see \n
 N/A.CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_PLCIPHER_SetKey(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enKeyEvenOdd, const HI_U8 *pu8Key, HI_U32 u32KeyLen);

/**
\brief Sets the IV vector of a PLCIPHER channel. This API is used to configure the PLCIPHER channel.CNcomment:����PLCIPHERͨ����IV���������ӿ���������PLCIPHERͨ����IV������CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER ͨ�������CNend
\param[in] enIVEvenOdd  Type of IV vector odd or even.CNcomment:������IV��������ż���͡�CNend
\param[in] pu8IV  Pointer to odd or even IV vector buffer to be set, always a 8 or 16 bytes array.CNcomment:ָ�����ͣ�ָ��Ҫ���õ����żIV������һ��8��16���ֽڵ����顣CNend
\param[in] u32IVLen  The length of IV vector to be set, always 8 or 16.CNcomment:Ҫ���õ�IV�������ݵĳ��ȣ�һ��8��16��CNend
\retval ::HI_SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:ģ��û�г�ʼ����CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:����PLCIPHER����Ƿ���CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:ָ�����Ϊ�ա�CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PARA  The input attribute is invalid.CNcomment:�������Խṹ��Ա�Ƿ���CNend
\see \n
 N/A.CNcomment:�ޡ�CNend
*/

HI_S32 HI_UNF_PLCIPHER_SetIV(HI_HANDLE hPLCipher, HI_UNF_PLCIPHER_KEY_EVENODD_E enIVEvenOdd, const HI_U8 *pu8IV, HI_U32 u32IVLen);

/**
\brief Encrypt TS package data in a PLCIPHER channel.CNcomment:ʹ��PLCIPHERͨ����TS�����ݽ���TS�����ܡ�CNend
\attention \n
PLCIPHER support pSrcBuf and pDestBuf are the same address, in other word, PLCIPHER support encryption at the same adress.
CNcomment:PLCIPHER֧��pSrcBuf��pDestBuf��ֵ��ͬ�����仰˵PLCIPHER֧�־͵ؼ��ܡ�CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER ͨ�������CNend
\param[in] pSrcBuf  The physical address(must be 16 bytes align) of TS package data to be encrypted.CNcomment:VOIDָ�����ͣ�������TS�����ݵ���ʼ�����ַ������16�ֽڶ��롣CNend
\param[in] pDestBuf  The physical address(must be 16 bytes align) of the encryted TS package data.CNcomment:VOIDָ�����ͣ�������ɺ�TS���������ݵ������ַ������16�ֽڶ��롣CNend
\param[in] u32Length  The length of TS package data to be encrypted.CNcomment:������TS�����ݵĳ��ȡ�CNend
\retval ::HI_SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:ģ��û�г�ʼ����CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:����PLCIPHER����Ƿ���CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:ָ�����Ϊ�ա�CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PARA  The input attribute is invalid.CNcomment:�������Խṹ��Ա�Ƿ���CNend
\see \n
 N/A.CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_PLCIPHER_Encrypt(HI_HANDLE hPLCipher, HI_VOID* pSrcBuf, HI_VOID* pDestBuf, HI_U32 u32Length);

/**
\brief Decrypt TS package data in a PLCIPHER channel.CNcomment:ʹ��PLCIPHERͨ����TS�����ݽ���TS�����ܡ�CNend
\attention \n
PLCIPHER support pSrcBuf and pDestBuf are the same address, in other word, PLCIPHER support decryption at the same adress.
CNcomment:PLCIPHER֧��pSrcBuf��pDestBuf��ֵ��ͬ�����仰˵PLCIPHER֧�־͵ؽ��ܡ�CNend
\param[in] hPLCipher  Handle of PLCIPHER channel.CNcomment:PLCIPHER ͨ�������CNend
\param[in] pSrcBuf  The physical address(must be 16 bytes align) of TS package data to be decrypted.CNcomment:VOIDָ�����ͣ�������TS�����ݵ���ʼ�����ַ������16�ֽڶ��롣CNend
\param[in] pDestBuf  The physical address(must be 16 bytes align) of the decryted TS package data.CNcomment:VOIDָ�����ͣ�������ɺ�TS���������ݵ������ַ������16�ֽڶ��롣CNend
\param[in] u32Length  The length of TS package data to be decrypted.CNcomment:������TS�����ݵĳ��ȡ�CNend
\retval ::HI_SUCCESS Success.CNcomment:�ɹ���CNend
\retval ::HI_FAILURE  Calling this API fails.CNcomment:APIϵͳ����ʧ�ܡ�CNend
\retval ::HI_ERR_PLCIPHER_NOT_INIT  The PLCIPHER module is not initialized.CNcomment:ģ��û�г�ʼ����CNend
\retval ::HI_ERR_PLCIPHER_INVALID_HANDLE The input PLCIPHER handle is invalid. CNcomment:����PLCIPHER����Ƿ���CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PTR  The pointer is null. CNcomment:ָ�����Ϊ�ա�CNend
\retval ::HI_ERR_PLCIPHER_INVALID_PARA  The input attribute is invalid.CNcomment:�������Խṹ��Ա�Ƿ���CNend
\see \n
 N/A.CNcomment:�ޡ�CNend
*/
HI_S32 HI_UNF_PLCIPHER_Decrypt(HI_HANDLE hPLCipher, HI_VOID* pSrcBuf, HI_VOID* pDestBuf, HI_U32 u32Length);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_PAYLOADCIPHER_H__ */
