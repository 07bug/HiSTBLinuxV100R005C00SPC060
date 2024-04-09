/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_cipher_intf.h
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __DRV_CIPHER_INTF_H__
#define __DRV_CIPHER_INTF_H__

#if defined (CHIP_TYPE_hi3716mv310)
#include "hi_boot_common.h"
#else
#include "hi_common.h"
#endif
#include "drv_cipher_define.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define MAX_DATA_LEN (1024*1024 - 16) //the max data length for encryption / decryption is  8k one time

#ifdef  HI_ADVCA_FUNCTION_RELEASE
#define HI_ERR_CIPHER(format, arg...)
#define HI_INFO_CIPHER(format, arg...)
#else
#undef HI_ERR_CIPHER
#define HI_ERR_CIPHER(fmt...) HI_ERR_PRINT(HI_ID_CIPHER, fmt)
#define HI_INFO_CIPHER(fmt...) HI_INFO_PRINT(HI_ID_CIPHER, fmt)
#endif

/******************************* API Declaration *****************************/
/** \addtogroup      CIPHER */
/** @{ */  /** <!-- [CIPHER] */
/* ---CIPHER---*/
/**
\brief  Init the cipher device.  CNcomment:��ʼ��CIPHER�豸�� CNend
\attention \n
This API is used to start the cipher device.
CNcomment:���ô˽ӿڳ�ʼ��CIPHER�豸�� CNend
\param N/A                                                                       CNcomment:�� CNend
\retval ::HI_SUCCESS  Call this API succussful.                                 CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Call this API fails.                                       CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CIPHER_FAILED_INIT  The cipher device fails to be initialized. CNcomment:CIPHER�豸��ʼ��ʧ�� CNend
\see \n
N/A
*/
HI_S32 Cipher_Init(HI_VOID);

/**
\brief  Deinit the cipher device.
CNcomment:\brief  ȥ��ʼ��CIPHER�豸�� CNend
\attention \n
This API is used to stop the cipher device. If this API is called repeatedly, HI_SUCCESS is returned, but only the first operation takes effect.
CNcomment:���ô˽ӿڹر�CIPHER�豸���ظ��رշ��سɹ�����һ�������á� CNend

\param N/A                                                                       CNcomment:�� CNend
\retval ::HI_SUCCESS  Call this API succussful.                                  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Call this API fails.                                        CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.          CNcomment:CIPHER�豸δ��ʼ�� CNend
\see \n
N/A
*/
HI_VOID Cipher_Exit(HI_VOID);

/**
\brief Obtain a cipher handle for encryption and decryption.
CNcomment������һ·Cipher����� CNend

\param[in] cipher attributes                                                     CNcomment:cipher ���ԡ� CNend
\param[out] phCipher Cipher handle                                               CNcomment:CIPHER����� CNend
\retval ::HI_SUCCESS Call this API succussful.                                      CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Call this API fails.                                        CNcomment: APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.          CNcomment:CIPHER�豸δ��ʼ�� CNend
\retval ::HI_ERR_CIPHER_INVALID_POINT  The pointer is null.                      CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_CIPHER_FAILED_GETHANDLE  The cipher handle fails to be obtained, because there are no available cipher handles. CNcomment: ��ȡCIPHER���ʧ�ܣ�û�п��е�CIPHER��� CNend
\see \n
N/A
*/
HI_S32 Cipher_CreateHandle(HI_HANDLE* phCipher, const HI_UNF_CIPHER_ATTS_S *pstCipherAttr);

/**
\brief Destroy the existing cipher handle. CNcomment:�����Ѵ��ڵ�CIPHER����� CNend
\attention \n
This API is used to destroy existing cipher handles.
CNcomment:���ô˽ӿ������Ѿ�������CIPHER����� CNend

\param[in] hCipher Cipher handle                                                 CNcomment:CIPHER����� CNend
\retval ::HI_SUCCESS  Call this API succussful.                                  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Call this API fails.                                        CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.         CNcomment:CIPHER�豸δ��ʼ�� CNend
\see \n
N/A
*/
HI_S32 Cipher_DestroyHandle(HI_HANDLE hCipher);

/**
\brief Configures the cipher control information.
CNcomment:\brief ����CIPHER������Ϣ�� CNend
\attention \n
Before encryption or decryption, you must call this API to configure the cipher control information.
The first 64-bit data and the last 64-bit data should not be the same when using TDES algorithm.
CNcomment:���м��ܽ���ǰ������ʹ�ô˽ӿ�����CIPHER�Ŀ�����Ϣ��ʹ��TDES�㷨ʱ��������Կ��ǰ��64 bit���ݲ�����ͬ�� CNend

\param[in] hCipher Cipher handle.                                                CNcomment:CIPHER��� CNend
\param[in] pstCtrl Cipher control information.                                   CNcomment:CIPHER������Ϣ CNend
\retval ::HI_SUCCESS Call this API succussful.                                      CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Call this API fails.                                       CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.         CNcomment:CIPHER�豸δ��ʼ�� CNend
\retval ::HI_ERR_CIPHER_INVALID_POINT  The pointer is null.                     CNcomment:ָ�����Ϊ�� CNend
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.                 CNcomment:�������� CNend
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  The handle is invalid.                  CNcomment:����Ƿ� CNend
\see \n
N/A
*/
HI_S32 Cipher_ConfigHandle(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_S* pstCtrl);

/**
\brief Performs encryption.
CNcomment:\brief ���м��ܡ� CNend

\attention \n
This API is used to perform encryption by using the cipher module.
The length of the encrypted data should be a multiple of 8 in TDES mode and 16 in AES mode. Besides, the length can not be bigger than 0xFFFFF.After this operation, the result will affect next operation.If you want to remove vector, you need to config IV(config pstCtrl->stChangeFlags.bit1IV with 1) by transfering HI_UNF_CIPHER_ConfigHandle.
CNcomment:ʹ��CIPHER���м��ܲ�����TDESģʽ�¼��ܵ����ݳ���Ӧ����8�ı�����AES��Ӧ����16�ı��������⣬�������ݳ��Ȳ��ܳ���0xFFFFF�����β�����ɺ󣬴˴β�������������������������һ�β��������Ҫ�����������Ҫ���´μ��ܲ���֮ǰ����HI_UNF_CIPHER_ConfigHandle��������IV(��Ҫ����pstCtrl->stChangeFlags.bit1IVΪ1)�� CNend
\param[in] hCipher Cipher handle                                                  CNcomment:CIPHER��� CNend
\param[in] u32SrcPhyAddr Physical address of the source data                    CNcomment:Դ���������ַ CNend
\param[in] u32DestPhyAddr Physical address of the target data                   CNcomment:Ŀ�����������ַ CNend
\param[in] u32ByteLength   Length of the encrypted data                         CNcomment:�������ݳ��� CNend
\retval ::HI_SUCCESS  Call this API succussful.                                  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Call this API fails.                                       CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.         CNcomment:CIPHER�豸δ��ʼ�� CNend
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.                 CNcomment:�������� CNend
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  The handle is invalid.                  CNcomment:����Ƿ� CNend
\see \n
N/A
*/
HI_S32 Cipher_Encrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);

/**
\brief ���м���
\attention \n
This API is used to perform decryption by using the cipher module.
The length of the decrypted data should be a multiple of 8 in TDES mode and 16 in AES mode. Besides, the length can not be bigger than 0xFFFFF.After this operation, the result will affect next operation.If you want to remove vector, you need to config IV(config pstCtrl->stChangeFlags.bit1IV with 1) by transfering HI_UNF_CIPHER_ConfigHandle.
CNcomment:ʹ��CIPHER���н��ܲ�����TDESģʽ�½��ܵ����ݳ���Ӧ����8�ı�����AES��Ӧ����16�ı��������⣬�������ݳ��Ȳ��ܳ���0xFFFFF�����β�����ɺ󣬴˴β�������������������������һ�β��������Ҫ�����������Ҫ���´ν��ܲ���֮ǰ����HI_UNF_CIPHER_ConfigHandle��������IV(��Ҫ����pstCtrl->stChangeFlags.bit1IVΪ1)�� CNend
\param[in] hCipher Cipher handle.                                                CNcomment:CIPHER��� CNend
\param[in] u32SrcPhyAddr Physical address of the source data.                    CNcomment:Դ���������ַ CNend
\param[in] u32DestPhyAddr Physical address of the target data.                   CNcomment:Ŀ�����������ַ CNend
\param[in] u32ByteLength Length of the decrypted data                           CNcomment:�������ݳ��� CNend
\retval ::HI_SUCCESS Call this API succussful.                                      CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Call this API fails.                                       CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CIPHER_NOT_INIT  The cipher device is not initialized.         CNcomment:CIPHER�豸δ��ʼ�� CNend
\retval ::HI_ERR_CIPHER_INVALID_PARA  The parameter is invalid.                 CNcomment:�������� CNend
\retval ::HI_ERR_CIPHER_INVALID_HANDLE  The handle is invalid.                  CNcomment:����Ƿ� CNend
\see \n
N/A
*/
HI_S32 Cipher_Decrypt(HI_HANDLE hCipher, HI_U32 u32SrcPhyAddr, HI_U32 u32DestPhyAddr, HI_U32 u32ByteLength);

/**
\brief Get the random number.
CNcomment:\brief ��ȡ������� CNend

\attention \n
This API is used to obtain the random number from the hardware.
CNcomment:���ô˽ӿ����ڻ�ȡ������� CNend

\param[out] pu32RandomNumber Point to the random number.                                        CNcomment:�������ֵ�� CNend
\retval ::HI_SUCCESS  Call this API succussful.                                                 CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                                                      CNcomment: APIϵͳ����ʧ�ܡ� CNend

\see \n
N/A
*/
HI_S32 Cipher_GetRandomNumber(HI_U8 *pu8RandomByte, HI_U32 u32Bytes, HI_U32 u32TimeOutUs);


/**
\brief Init the hash module, if other program is using the hash module, the API will return failure.
CNcomment:\brief ��ʼ��HASHģ�飬�����������������ʹ��HASHģ�飬����ʧ��״̬�� CNend

\attention \n
N/A

\param[in] pstHashAttr: The hash calculating structure input.                                      CNcomment:���ڼ���hash�Ľṹ����� CNend
\param[out] pHashHandle: The output hash handle.                                                   CNcomment:�����hash��� CNend
\retval ::HI_SUCCESS  Call this API succussful.                                                  CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                                                       CNcomment: APIϵͳ����ʧ�� CNend

\see \n
N/A
*/
HI_S32 Cipher_HashInit(HI_UNF_CIPHER_HASH_ATTS_EX_S *pstHashAttr, HI_HANDLE *pHashHandle);

/**
\brief Calculate the hash, if the size of the data to be calculated is very big and the DDR ram is not enough, this API can calculate the data one block by one block.
CNcomment:\brief ����hashֵ�������Ҫ������������Ƚϴ󣬸ýӿڿ���ʵ��һ��blockһ��block�ļ��㣬�����������Ƚϴ������£��ڴ治������⡣ CNend

\attention \n
N/A

\param[in] hHashHandl:  Hash handle.                                          CNcomment:Hash����� CNend
\param[in] pu8InputData:  The input data buffer.                              CNcomment:�������ݻ��� CNend
\param[in] u32InputDataLen:  The input data length, attention: the block length input must be 4bytes aligned except the last block!            CNcomment:�������ݵĳ��ȡ���Ҫ�� �������ݿ�ĳ��ȱ�����4�ֽڶ��룬���һ��block�޴����ơ� CNend
\retval ::HI_SUCCESS  Call this API succussful.                              CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                               CNcomment:APIϵͳ����ʧ�ܡ� CNend

\see \n
N/A
*/
HI_S32 Cipher_HashUpdate(HI_HANDLE hHashHandle, HI_U8 *pu8InputData, HI_U32 u32InputDataLen);



/**
\brief Get the final hash value, after calculate all of the data, call this API to get the final hash value and close the handle.If there is some reason need to interupt the calculation, this API should also be call to close the handle.
CNcomment:��ȡhashֵ���ڼ��������е����ݺ󣬵�������ӿڻ�ȡ���յ�hashֵ���ýӿ�ͬʱ��ر�hash���������ڼ�������У���Ҫ�жϼ��㣬Ҳ������øýӿڹر�hash����� CNend

\attention \n
N/A

\param[in] hHashHandle:  Hash handle.                                          CNcomment:Hash����� CNend
\param[out] pu8OutputHash:  The final output hash value.                       CNcomment:�����hashֵ�� CNend

\retval ::HI_SUCCESS  Call this API succussful.                              CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                               CNcomment:APIϵͳ����ʧ�ܡ� CNend

\see \n
N/A
*/
HI_S32 Cipher_HashFinal(HI_HANDLE hHashHandle, HI_U8 *pu8OutputHash);

HI_S32 Cipher_CalcRsa(CIPHER_RSA_DATA_S *pCipherRsaData);

HI_S32 Cipher_GetHandleConfig(HI_HANDLE hCipherHandle, HI_UNF_CIPHER_CTRL_S* pstCtr);
/** @} */  /** <!-- ==== API declaration end ==== */

HI_S32 Cipher_ConfigHandleEx(HI_HANDLE hCipher, HI_UNF_CIPHER_CTRL_EX_S* pstExCtrl);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __DRV_CIPHER_INTF_H__ */
