/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_otp.h
  Version       : Initial Draft
  Author        : Hisilicon otp software group
  Created       : 2016/10/9
  Description   :
*******************************************************************************/
/**
 * \file
 * \brief Describes the information about the otp module.
          CNcomment:�ṩ OTP ģ��������Ϣ CNend
 */
#ifndef __HI_UNF_OTP_H__
#define __HI_UNF_OTP_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      OTP */
/** @{ */  /** <!-- [OTP] */

/** CA VendorID */
typedef enum
{
    HI_UNF_OTP_VENDORID_COMMON     = 0x00,        /**<No-Advcance CA chipset, Marked with 0*/
    HI_UNF_OTP_VENDORID_NAGRA      = 0x01,        /**<NAGRA  Chipse, Marked with R*/
    HI_UNF_OTP_VENDORID_IRDETO     = 0x02,        /**<IRDETO Chipset, Marked with I*/
    HI_UNF_OTP_VENDORID_CONAX      = 0x03,        /**<CONAX Chipset, Marked with C*/
    HI_UNF_OTP_VENDORID_NDS        = 0x04,        /**<NDS Chipset*/
    HI_UNF_OTP_VENDORID_SUMA       = 0x05,        /**<SUMA Chipset, Marked with S*/
    HI_UNF_OTP_VENDORID_NOVEL      = 0x06,        /**<NOVEL Chipset, Marked with Y*/
    HI_UNF_OTP_VENDORID_VERIMATRIX = 0x07,        /**<VERIMATRIX Chipset, Marked with M*/
    HI_UNF_OTP_VENDORID_CTI        = 0x08,        /**<CTI Chipset, Marked with T*/
    HI_UNF_OTP_VENDORID_SAFEVIEW   = 0x09,        /**<SAFEVIEW CA Chipset*/
    HI_UNF_OTP_VENDORID_LATENSE    = 0x0a,        /**<LATENSE CA Chipset*/
    HI_UNF_OTP_VENDORID_SH_TELECOM = 0x0b,        /**<SH_TELECOM CA Chipset*/
    HI_UNF_OTP_VENDORID_DCAS       = 0x0c,        /**<DCAS CA Chipset*/
    HI_UNF_OTP_VENDORID_VIACCESS   = 0x0d,        /**<VIACCESS CA Chipset*/
    HI_UNF_OTP_VENDORID_BUTT
} HI_UNF_OTP_VENDORID_E;

/** FLASH device types*/
typedef enum
{
    HI_UNF_OTP_FLASH_TYPE_SPI     = 0,    /**<SPI flash*/
    HI_UNF_OTP_FLASH_TYPE_NAND,           /**<nand flash*/
    HI_UNF_OTP_FLASH_TYPE_NOR,            /**<nor flash*/
    HI_UNF_OTP_FLASH_TYPE_EMMC,           /**<eMMC*/
    HI_UNF_OTP_FLASH_TYPE_SPI_NAND,       /**<spi_nand flash*/
    HI_UNF_OTP_FLASH_TYPE_SD,             /**<FSD/TSD flash*/
    HI_UNF_OTP_FLASH_TYPE_BUTT
} HI_UNF_OTP_FLASH_TYPE_E;

/** JTAG protect mode*/
typedef enum
{
    HI_UNF_OTP_JTAG_MODE_OPEN     = 0,
    HI_UNF_OTP_JTAG_MODE_PROTECT,
    HI_UNF_OTP_JTAG_MODE_CLOSED,
    HI_UNF_OTP_JTAG_MODE_BUTT
} HI_UNF_OTP_JTAG_MODE_E;

/** Rootkey type*/
typedef enum
{
    HI_UNF_OTP_OEM_ROOTKEY        = 0,
    HI_UNF_OTP_HDCP_ROOTKEY,
    HI_UNF_OTP_STB_ROOTKEY,
    HI_UNF_OTP_SW_ROOTKEY,
    HI_UNF_OTP_STBTA_ROOTKEY,
    HI_UNF_OTP_ROOTKEY_BUTT
} HI_UNF_OTP_ROOTKEY_E;

/** TA MSID(Trusted Application Market Segment ID) */
typedef enum
{
    HI_UNF_OTP_TA_INDEX_1 = 0,
    HI_UNF_OTP_TA_INDEX_2,
    HI_UNF_OTP_TA_INDEX_3,
    HI_UNF_OTP_TA_INDEX_4,
    HI_UNF_OTP_TA_INDEX_5,
    HI_UNF_OTP_TA_INDEX_6,
    HI_UNF_OTP_TA_INDEX_BUTT
} HI_UNF_OTP_TA_INDEX_E;

#define OTP_FIELD_VALUE_MAX_LEN 1024
#define OTP_FIELD_NAME_MAX_LEN 32
typedef struct
{
    HI_BOOL bBurn;
    HI_CHAR aszFieldName[OTP_FIELD_NAME_MAX_LEN]; //32
    HI_U32 u32ValueLen;
    HI_U8 au8Value[OTP_FIELD_VALUE_MAX_LEN]; //4
    HI_BOOL bLock;
}HI_UNF_OTP_BURN_PV_ITEM_S;

/** UART type
ChipSet: HI3796MV200/HI3716MV450
UART0:For REE CPU, TEE CPU and LPMCU.
UART1:Reserved.
UART2:Reserved.
UART3:Only for SMCU
*/
typedef enum
{
    HI_UNF_OTP_UART0 = 0,
    HI_UNF_OTP_UART1,
    HI_UNF_OTP_UART2,
    HI_UNF_OTP_UART3,
    HI_UNF_OTP_BUTT,
} HI_UNF_OTP_UART_TYPE_E;
/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */


/******************************* API declaration *****************************/
/** \addtogroup      OTP */
/** @{ */  /** <!-- [OTP] */

#define HI_UNF_OTP_Open(HI_VOID) HI_UNF_OTP_Init(HI_VOID)
#define HI_UNF_OTP_Close(HI_VOID) HI_UNF_OTP_DeInit(HI_VOID)

/**
\brief Initializes the otp module. CNcomment:��ʼ��OTPģ�� CNend
\attention \n
Before calling other functions in this file, you must call this application programming interface (API).
CNcomment �ڵ���OTPģ�������ӿ�ǰ��Ҫ�����ȵ��ñ��ӿ� CNend
\param N/A
\retval ::HI_SUCCESS  Success.   CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Failure.       CNcomment:APIϵͳ����ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_Init(HI_VOID);

/**
\brief Deinitializes the otp module. CNcomment:ȥ��ʼ��OTP�豸 CNend
\attention \n
N/A
\param N/A                                        CNcomment:�ޡ� CNend
\retval ::HI_SUCCESS  Success.   CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Failure.       CNcomment:APIϵͳ����ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_DeInit(HI_VOID);


/**
\brief Set customer key, the customer key is used by the customer to encrypt some private data.
\brief CNcomment:����customer key��customer key�ɿͻ��Լ����壬���Զ�����;�� CNend
\attention \n
N/A
\param[in] pKey:  Customer key to be written to otp.                    CNcomment:Customer key��ֵ����д��OTP�� CNend
\param[in] u32KeyLen:  The length of customer key, must be 16bytes.     CNcomment:Customer key�ĳ��ȣ�����Ϊ16�ֽڡ�           CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_SetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen);

/**
\brief Get customer key, the customer key is used by the customer to encrypt some private data.
\brief CNcomment:��ȡcustomer key�� CNend
\attention \n
N/A
\param[in] pKey:Buffer to store the customer key read from otp.     CNcomment:�洢customer key��buffer�� CNend
\param[in] u32KeyLen:The length of buffer, must be 16bytes.             CNcomment:customer key �ĳ��ȣ�����Ϊ16�ֽڡ� CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetCustomerKey(HI_U8 *pKey, HI_U32 u32KeyLen);


/**
\brief Set stb private data, the stb private data is used by the customer to set some private data.
\brief CNcomment:���ÿͻ�˽�����ݡ� CNend
\attention \n
N/A
\param[in] u32Offset:  The offset to set the private data, should be between 0 and 15.  CNcomment:����stbprivData��ƫ�ƣ�����Ϊ0~15֮�䡣 CNend
\param[in] u8Data:  The private data to be set.                         CNcomment:��Ҫ���õ�ֵ�� CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_SetStbPrivData(HI_U32 u32Offset, HI_U8 u8Data);

/**
\brief Get stb private data, the stb private data is used by the customer to set some private data.
\brief CNcomment:��ȡ�ͻ�˽�����ݡ� CNend
\attention \n
N/A
\param[in] u32Offset:  The offset to get the private data, should be between 0 and 15.  CNcomment:��ȡstbprivData��ƫ�ƣ�����Ϊ0~15֮�䡣 CNend
\param[out] pu8Data:  The data read from otp.                           CNcomment:��ȡ��ֵ�� CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetStbPrivData(HI_U32 u32Offset, HI_U8 *pu8Data);

/**
\brief burn chipset to normal chipset CNcomment:��оƬ��д����ͨоƬ CNend
\attention \n
N/A
\retval ::HI_SUCCESS  Success.         CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Failure.         CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTPδ��ʼ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_BurnToNormalChipset(HI_VOID);

/**
\brief Burn nomal chipset to secure chipset
\brief CNcomment:����ͨоƬ��д�ɰ�ȫоƬ�� CNend
\attention \n
N/A
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_BurnToSecureChipset(HI_VOID);

/**
\brief Get idword lock status CNcomment:��ȡоƬ�ڲ�IDWord������־λ״̬ CNend
\attention \n
N/A
\param[out] pbLockFlag:  Point to IDWord lock status. CNcomment:ָ�����ͣ���״̬��Ϣ CNend
\retval ::HI_SUCCESS  Success.         CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Failure.         CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTPδ��ʼ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetIDWordLockFlag(HI_BOOL *pbLockFlag);
/**
\brief  Set hdcp root key to otp, 16bytes length.
\brief CNcomment:��оƬ�ڲ�д��hdcp root key������Ϊ16�ֽڳ��� CNend
\attention \n
N/A
\param[in] pu8RootKey:  Set hdcp root key to otp.                   CNcomment����hdcp root key��OTP�� CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_WriteHdcpRootKey(HI_U8 *pu8HdcpRootKey, HI_U32 u32Keylen);

/**
\brief  Get hdcp root key from otp, 16bytes length.
\brief CNcomment:��ȡоƬ�ڲ����õ�hdcp root key������Ϊ16�ֽڳ��� CNend
\attention \n
N/A
\param[out] pu8RootKey:  Point to hdcp root key from otp.               CNcomment:��OTP�л�ȡhdcp root key�� CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_ReadHdcpRootKey(HI_U8 *pu8HdcpRootKey, HI_U32 u32Keylen);

/**
\brief  Lock hdcp root key in otp.
\brief CNcomment:����оƬ�ڲ����õ�hdcp root key��������hdcp root key�����ɱ���ȡ�� CNend
\attention \n
N/A
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_LockHdcpRootKey(HI_VOID);

/**
\brief  Get hdcp root Key lock flag.
\brief CNcomment:��ȡоƬ�ڲ����õ�hdcp root key��������־λ�� CNend
\attention \n
N/A
\param[out] pbLockFlag:  Point to hdcp root key lock flag from otp.     CNcomment:ָ���ȡ���ı�־λ�� CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetHdcpRootKeyLockFlag(HI_BOOL *pbLock);

/**
\brief Set stb root key to otp.
\brief CNcomment:��оƬ�ڲ�����stb root key�� CNend
\attention \n
N/A
\param[in] u8StbRootKey:  Point to stb root key value.                  CNcomment:Stb root key��ֵ�� CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_WriteStbRootKey(HI_U8 *pu8StbRootKey, HI_U32 u32Keylen);

/**
\brief Get stb root key from otp.
\brief CNcomment:��ȡоƬ�ڲ����õ�stb root key�� CNend
\attention \n
N/A
\param[out] pu8RootKey:  Point to stb root key from otp.                CNcomment:ֻ���ȡ����Stb root key�� CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_ReadStbRootKey(HI_U8 *pu8StbRootKey, HI_U32 u32Keylen);

/**
\brief Lock stb root key in otp.
\brief CNcomment:��סоƬ�ڲ����õ�stb root key��������stb root key�����ɱ���ȡ�� CNend
\attention \n
N/A
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_LockStbRootKey(HI_VOID);

/**
\brief Get stb root Key lock flag
\brief CNcomment:��ȡоƬ�ڲ�stb root key��������־λ�� CNend
\attention \n
N/A
\param[out] pbLockFlag:  Point to stb root key lock flag from otp.      CNcomment:ָ���ȡ���ı�־λ�� CNend
\retval ::HI_SUCCESS  Call this API successful.                     CNcomment:APIϵͳ���óɹ��� CNend
\retval ::HI_FAILURE  Call this API fails.                          CNcomment:APIϵͳ����ʧ�ܡ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetStbRootKeyLockFlag(HI_BOOL *pbLockFlag);


/**
\brief Get CA Vendor ID. CNcomment:��ȡ�߰����̱�ʶ CNend
\attention \n
N/A
\param[out] penVendorID:  CA VendorID. CNcomment:�߰����̱�ʶ CNend
\retval ::HI_SUCCESS  Success.         CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Failure.         CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTPδ��ʼ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetVendorID(HI_UNF_OTP_VENDORID_E *penVendorID);

/**
\brief Get the serial number of the STB. CNcomment:��ȡ���������к� CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu8StbSn serial number of the STB. CNcomment:ָ�����ͣ����������к� CNend
\param[in/out] pu32Len point to the length of serial number of the STB, current is 4. CNcomment:ָ�����ͣ����������кų��ȣ���ǰ��4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetStbSn
*/
HI_S32 HI_UNF_OTP_GetStbSN(HI_U8 *pu8StbSN, HI_U32 *pu32Len);

/**
\brief Set the serial number of the STB. CNcomment:���û��������к� CNend
\attention \n
The serial number of the STB is set before delivery. The serial number can be set once only and takes effects after the STB restarts.
CNcomment:�ڻ����г���ʱ���ã���֧������һ�Σ����ú�������Ч CNend
\param[in] pu8StbSn point to serial number of the STB. CNcomment:ָ�����ͣ����������к� CNend
\param[in] u32Len The length of serial number of the STB, current is 4. CNcomment:ָ�����ͣ����������кų��ȣ���ǰ��4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_OTP_SETPARAM_AGAIN The parameter has been set already. CNcomment:�ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetStbSN(HI_U8 *pu8StbSN, HI_U32 u32Len);

/**
\brief set the type of flash memory for security startup. CNcomment:ָ����ȫ������Flash���� CNend
\attention N/A
\param[in]  enFlashType Type of the flash memory for security startup. CNcomment: ������Flash���� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_OTP_SETPARAM_AGAIN The parameter has been set already. CNcomment:�ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetBootMode(HI_UNF_OTP_FLASH_TYPE_E enFlashType);


/**
\brief Disables the self-boot. CNcomment:�ر��Ծٹ���, boot�²���ʹ�ô���/�������� CNend
\attention \n
The setting is performed before delivery and can be performed once only.
The self-boot function is enabled by default.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ�Σ�Ĭ��ʹ��SelfBoot���� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_DisableSelfBoot(HI_VOID);

/**
\brief Get the self-boot status. CNcomment:��ȡ�Ծ�״̬ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbDisable Pointer to the self-boot status, true means DISABLE. CNcomment:ָ�����ͣ��Ծ�״̬��true��ʾ�����Ծٹ��� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetSelfBootStat(HI_BOOL *pbDisable);


/**
\brief Force decrypt the BootLoader. CNcomment:���ñ����BootLoader���н��� CNend
\attention \n
The setting is performed before delivery and can be performed once only.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϸ���Flash�е����ݱ�ʶ������BootLoader�Ƿ���Ҫ���� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_EnableBootDecrypt(HI_VOID);


/**
\brief Get the BootLoader Decryption status. CNcomment:��ȡBootLoader����״̬ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbEnable Point to bootLoader Decryption status. CNcomment:ָ�����ͣ�Bootloader���ܱ�־λ CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetBootDecryptStat(HI_BOOL *pbEnable);


/**
\brief Enable the security startup. This API should be used after the API HI_UNF_OTP_SetBootMode.
CNcomment:���ð�ȫ����ʹ�ܣ��ýӿڱ����HI_UNF_OTP_COMMON_SetBootMode����ʹ�� CNend
\attention \n
None CNcomment:�� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_EnableSCS(HI_VOID);


/**
\brief Get the security startup status function. CNcomment:��ȡ��ȫ����ʹ�ܱ�� CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbEnable Point to bootLoader SCS status. CNcomment:ָ�����ͣ���ȫ����ʹ�ܱ�־λ CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetSCSStat(HI_BOOL *pbEnable);


/**
\brief Enable the Trust Zone. CNcomment:����Trust Zoneʹ��CNend
\attention \n
None CNcomment:�� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_EnableTrustZone(HI_VOID);


/**
\brief Get the Trust Zone status.
CNcomment:��ȡTrustZoneʹ�ܱ�� CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbEnable Point to trust zone status. CNcomment:ָ�����ͣ���ȫ����ʹ�ܱ�־λ CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetTrustZoneStat(HI_BOOL *pbEnable);


/**
\brief Get the market segment identifier. CNcomment:��ȡ�г�������  CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu8MSID Point to MSID. CNcomment:ָ�����ͣ��г������� CNend
\param[in/out] pu32Len Point to MSID length, current is 4. CNcomment:ָ�����ͣ��г������볤�ȣ���ǰ������4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetMSId
*/
HI_S32 HI_UNF_OTP_GetMSID(HI_U8 *pu8MSID, HI_U32 *pu32Len);


/**
\brief Set the market segment identifier CNcomment:�����г�������  CNend
\attention \n
None CNcomment:�� CNend
\param[in] pu8MSID Point to MSID. CNcomment:ָ�����ͣ��г������� CNend
\param[in/out] u32MSIdLen MSID length, current is 4. CNcomment:�г������볤�ȣ���ǰ������4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetMSID(HI_U8 *pu8MSID, HI_U32 u32Len);


/**
\brief Get the secure os market segment identifier CNcomment:��ȡ��ȫOS�г�������  CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu8SOSMSID Point to SOS MSID. CNcomment:ָ�����ͣ���ȫOS�г������� CNend
\param[in/out] pu32Len Point to SOS MSID length, current is 4. CNcomment:ָ�����ͣ���ȫOS�г������볤�ȣ���ǰ������4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetMSId
*/
HI_S32 HI_UNF_OTP_GetSOSMSID(HI_U8 *pu8SOSMSID, HI_U32 *pu32Len);


/**
\brief Sets the sos market segment identifier CNcomment:���ð�ȫOS�г�������  CNend
\attention \n
None CNcomment:�� CNend
\param[in] pu8SOSMSID Point to SOSMSID. CNcomment:ָ�����ͣ���ȫOS�г������� CNend
\param[in] u32Len MSID length, current is 4. CNcomment:ָ�����ͣ���ȫOS�г������볤�ȣ���ǰ������4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetSOSMSID(HI_U8 *pu8SOSMSID, HI_U32 u32Len);

/**
\brief Sets the LongData segment identifier CNcomment:����LongData  CNend
\attention \n
None CNcomment:�� CNend
\param[in] u32Offset CNcomment: ��ַƫ��16�ֽڶ��� CNend
\param[in] pu8Value CNcomment: otp��������  CNend
\param[in] u32Length CNcomment: otp�������鳤��,����16�ֽڶ���  CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length);

/**
\brief Sets the LongData segment identifier CNcomment:����LongData  CNend
\attention \n
None CNcomment:�� CNend
\param[in] u32Offset CNcomment: ��ַƫ��16�ֽڶ��� CNend
\param[out] pu8Value CNcomment: ����otp��������  CNend
\param[in] u32Length CNcomment: otp�������鳤��,����16�ֽڶ���  CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetLongData(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U8 * pu8Value, HI_U32 u32Length);

/**
\brief Sets the LongData segment identifier CNcomment:����LongData����  CNend
\attention \n
None CNcomment:�� CNend
\param[in] u32Offset CNcomment: ��ַƫ��,16�ֽڶ��� CNend
\param[in] u32Length CNcomment: otp�������鳤��,16�ֽڶ���  CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length);

/**
\brief Sets the LongData segment identifier CNcomment:���LongData���� CNend
\attention \n
None CNcomment:�� CNend
\param[in] u32Offset CNcomment: ��ַƫ��,16�ֽڶ��� CNend
\param[in] u32Length CNcomment: otp�������鳤��,16�ֽڶ���  CNend
\param[out] pu32Lock CNcomment: ����0ȫû��,����1ȫ��,����2���ֱ���  CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetLongDataLock(HI_CHAR * pFuseName, HI_U32 u32Offset, HI_U32 u32Length,  HI_U32 * pu32Lock);

/**
\brief disable wake up from ddr. CNcomment:�ر�ԭ�ػ���ģʽ CNend
\attention \n
None CNcomment:�� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_DisableDDRWakeup(HI_VOID);


/**
\brief Get wake up from ddr status. CNcomment:��ȡԭ�ػ���״̬ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbDisable Point to DDR WakeUp status. CNcomment:ָ�����ͣ�ԭ�ػ���ʹ��״̬ CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetDDRWakeupStat(HI_BOOL *pbDisable);

/**
\brief Lock the whole OTP area. CNcomment:��������OTP���� CNend
\attention \n
None CNcomment:�� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_LockGlobalOTP(HI_VOID);



/**
\brief Get global otp lock status function. CNcomment:��ȡOTP��״̬ CNend
\attention \n
None CNcomment:�� CNend
\param[out]  pbEnable Point to global OTP lock status. CNcomment:ָ�����ͣ�OTP����״̬ CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetGlobalOTPLockStat(HI_BOOL *pbEnable);


/**
\brief Enable runtime-check. CNcomment:��������ʱУ�鹦��ʹ�� CNend
\attention \n
None CNcomment:�� CNend
\param[in]  None
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_EnableRuntimeCheck(HI_VOID);


/**
\brief Get runtime-check status CNcomment:��ȡ����ʱУ��״̬ʹ�ܱ��  CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbEnable Point to runtime Check status. CNcomment:ָ�����ͣ�����ʱУ��ʹ��״̬ CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetRuntimeCheckStat(HI_BOOL *pbEnable);

/**
\brief Disable DDR wakeup check. CNcomment:�رմ�������У�顣CNend
\attention \n
None CNcomment:�� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_DisableDDRWakeupCheck(HI_VOID);


/**
\brief Get ddr wakeup check status. CNcomment:��ȡ��������У��ʹ�ܱ��  CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbEnable Point to DDR Wakeup Check status. CNcomment:ָ�����ͣ���������У��ʹ��״̬ CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetDDRWakeupCheckStat(HI_BOOL *pbEnable);


/**
\brief Enable ddr scramble. CNcomment:�����ڴ���Ź��� CNend
\attention \n
None CNcomment:�� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_EnableDDRScramble(HI_VOID);


/**
\brief Get ddr scramble status CNcomment:��ȡ�ڴ����ʹ�ܱ��  CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbEnable Pointer to DDR Scramble Stat. CNcomment:ָ���ڴ����ʹ�ܱ��ֵ��ָ�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetDDRScrambleStat(HI_BOOL *pbEnable);


/**
\brief Get the mode of the JTAG. CNcomment:��ȡJTAG���Խӿ�ģʽ CNend
\attention \n
None CNcomment:�� CNend
\param[out] penJtagMode Point to the mode of the JTAG. CNcomment:ָ�����ͣ�JTAG���Խӿ�ģʽ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_OTP_GetJtagMode(HI_UNF_OTP_JTAG_MODE_E *penJtagMode);


/**
\brief Set the mode of the JTAG. CNcomment:����JTAG���Խӿ�ģʽ CNend
\attention \n
If the mode of the JTAG interface is set to closed or password-protected, it cannot be opened.
If the JTAG interface is open, it can be closed or password-protected.
If the JATG interface is password-protected, it can be closed.
After being closed, the JATG interface cannot be set to open or password-protected mode.
CNcomment:��֧������Ϊ��״̬��\n
�򿪵�ʱ����Թرջ�����Ϊ��Կ����״̬��\n
������Կ����״̬ʱ���Թرա�\n
�ر�֮���ܴ򿪺�����Ϊ��Կ����״̬ CNend
\param[in] enJtagMode Mode of the JTAG. CNcomment:JTAG���Խӿ�ģʽ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_OTP_SetJtagMode(HI_UNF_OTP_JTAG_MODE_E enJtagMode);


/**
\brief Get the mode of the TEE JTAG. CNcomment:��ȡ TEE JTAG���Խӿ�ģʽ CNend
\attention \n
None CNcomment:�� CNend
\param[out] penJtagMode Point to the mode of the JTAG. CNcomment:ָ�����ͣ�JTAG���Խӿ�ģʽ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_OTP_GetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E *penJtagMode);


/**
\brief Set the mode of the TEE JTAG. CNcomment:���� TEE JTAG���Խӿ�ģʽ CNend
\attention \n
If the mode of the JTAG interface is set to closed or password-protected, it cannot be opened.
If the JTAG interface is open, it can be closed or password-protected.
If the JATG interface is password-protected, it can be closed.
After being closed, the JATG interface cannot be set to open or password-protected mode.
CNcomment:��֧������Ϊ��״̬��\n
�򿪵�ʱ����Թرջ�����Ϊ��Կ����״̬��\n
������Կ����״̬ʱ���Թرա�\n
�ر�֮���ܴ򿪺�����Ϊ��Կ����״̬ CNend
\param[in] enJtagMode Mode of the JTAG. CNcomment:JTAG���Խӿ�ģʽ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_OTP_SetTEEJtagMode(HI_UNF_OTP_JTAG_MODE_E enJtagMode);


/**
\brief Get the boot version identifier CNcomment:��ȡboot�汾��  CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu8VersionID Point to version ID. CNcomment:ָ�����ͣ�boot�汾�� CNend
\param[in/out] pu32VersionIdLen Point to the length of version ID, current is 4. CNcomment:ָ�����ͣ�boot�汾�ų��ȣ���ǰΪ4 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetMSId
*/
HI_S32 HI_UNF_OTP_GetBootVersionID(HI_U8 *pu8VersionID, HI_U32 *pu32Len);


/**
\brief Sets the boot version identifier CNcomment:����boot�汾��  CNend
\attention \n
None CNcomment:�� CNend
\param[in] pu8VersionID Point to version ID. CNcomment:ָ�����ͣ�boot�汾�� CNend
\param[in] u32Len The length of version ID, current is 4. CNcomment:ָ�����ͣ�boot�汾�ų��ȣ���ǰΪ4 CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetBootVersionID(HI_U8 *pu8VersionID, HI_U32 u32Len);


/**
\brief Set root key to otp. CNcomment:��оƬ�ڲ����ø���Կ CNend
\attention \n
N/A
\param[in] enRootkeyType:   Type of rootkey.        CNcomment:����Կ���� CNend
\param[in] pu8Rootkey: Point to root key value.     CNcomment:ָ�����ͣ�����Կ CNend
\param[in] u32Len: The length of root key.          CNcomment:����Կ���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_SetRootKey(HI_UNF_OTP_ROOTKEY_E enRootkeyType, HI_U8 *pu8Rootkey, HI_U32 u32Len);


/**
\brief Get root key lock status.                    CNcomment:��ȡOTP��״̬��Ϣ CNend
\attention \n
N/A
\param[in] enRootkeyType: Type of rootkey.          CNcomment:����Կ���� CNend
\param[out] pbLock: Point to root key lock status.  CNcomment:ָ�����ͣ�����Կ�Ƿ��� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetRootKeyLockStat(HI_UNF_OTP_ROOTKEY_E enRootkeyType, HI_BOOL *pbLock);

/**
\brief Set RSA key to otp. CNcomment:��оƬ�ڲ�����RSA��Կ CNend
\attention \n
N/A
\param[in] pu8Key: Point to RSA key value.         CNcomment:ָ�����ͣ�RSA��Կ CNend
\param[in] u32KeyLen: The length of RSA key.       CNcomment:RSA��Կ���� CNend
\retval ::HI_SUCCESS Success                                            CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called                        CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized  CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid   CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_SetRSAKey(HI_U8 *pu8Key, HI_U32 u32KeyLen);

/**
\brief Get rsa lock status. CNcomment:��ȡRSA lock״̬ CNend
\attention \n
N/A
\param[out] pbLock: Rsa lock status.   CNcomment:ָ�����ͣ�RSA lock״̬ CNend
\retval ::HI_SUCCESS  Success.         CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE  Failure.         CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized. CNcomment:OTPδ��ʼ�� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_GetRSALockStat(HI_BOOL *pbLock);


/**
\brief Burn product PV to otp. CNcomment:��оƬ�ڲ�OTP�̶����� CNend
\attention \n
N/A
\param[in] pstPV: Point to the name of the config table.   CNcomment:ָ�����ͣ��������ݱ��ַ CNend
\param[in] u32Num: The nember of config table.         CNcomment:����������Ŀ�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_BurnProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pstPV, HI_U32 u32Num);

/**
\brief Verify product PV. CNcomment:����У��PV���ݵ���ȷ�� CNend
\attention \n
N/A
\param[in] pstPV: Point to the name of the config table.   CNcomment:ָ�����ͣ��������ݱ��ַ CNend
\param[in] u32Num: The nember of config table.         CNcomment:����������Ŀ�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
N/A
*/
HI_S32 HI_UNF_OTP_VerifyProductPV(HI_UNF_OTP_BURN_PV_ITEM_S *pstPV, HI_U32 u32Num);

/**
\brief Set TEE enable lock flag. CNcomment:����TEEʹ���������λ CNend
\attention \n
None CNcomment:�� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetTEECtrlLock(HI_VOID);

/**
\brief Get TEE enable lock flag. CNcomment: ��ȡTEEʹ���������λ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbTEEEnL: Point to TEE lock status. CNcomment:ָ�����ͣ�TEE����״̬ CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetTEECtrlLock(HI_BOOL *pbTEEEnL);

/**
\brief Set the ASC(ACPU Start Code) market segment ID. CNcomment: ����ASC(ACPU Start Code)�г������� CNend
\attention \n
None CNcomment:�� CNend
\param[in] pu8ASCMSID: Point to ASC market segment ID. CNcomment:ָ�����ͣ�ASC�г������� CNend
\param[in] u32Len: ASC market segment ID length, current is 4. CNcomment:ASC �г������볤�ȣ���ǰ������4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetASCMSID (HI_U8 *pu8ASCMSID, HI_U32 u32Len);

/**
\brief Get the ASC(ACPU Start Code) market segment ID. CNcomment:��ȡASC(ACPU Start Code)�г������� CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu8ASCMSID: Point to ASC market segment identifier. CNcomment:ָ�����ͣ�ASC�г������� CNend
\param[in] pu32Len: ASC market segment ID length, current is 4. CNcomment:ָ�����ͣ�ASC�г������볤�ȣ���ǰ������4 CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetASCMSID(HI_U8 *pu8ASCMSID, HI_U32 *pu32Len);

/**
\brief Sets TA ID and TA market segment ID. CNcomment:����TA ID��TA�г�������  CNend
\attention \n
None CNcomment:�� CNend
\param[in] enIndex: TA ID and TA market segment ID index. CNcomment:TA ID��TA�г������������  CNend
\param[in] u32TAID: TA ID. CNcomment:TA ID CNend
\param[in] u32MSID: TA market Segment ID. CNcomment:TA�г������� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_SetTAIDAndMSID(const HI_UNF_OTP_TA_INDEX_E enIndex, HI_U32 u32TAID, HI_U32 u32MSID);

/**
\brief Get TA ID and TA market segment ID. CNcomment:��ȡTA ID��TA�г�������  CNend
\attention \n
None CNcomment:�� CNend
\param[in] enIndex: TA ID and TA market segment ID index. CNcomment:TA ID��TA�г������������  CNend
\param[out] pu32TAID: TA ID. CNcomment:ָ�����ͣ�TA ID CNend
\param[out] pu32MSID: TA market segment ID. CNcomment:ָ�����ͣ�TA�г������� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetTAIDAndMSID(const HI_UNF_OTP_TA_INDEX_E enIndex, HI_U32 *pu32TAID, HI_U32 *pu32MSID);

/**
\brief Disable UART(Universal Asynchronous Receiver/Transmitter) output. CNcomment:�ر�UART���  CNend
\attention \n
None CNcomment:�� CNend
\param[in] enUartType: UART type. CNcomment:UART����  CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_OTP_NOT_SUPPORT Not support for this chipset. CNcomment:��оƬ��֧�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_DisableUART(HI_UNF_OTP_UART_TYPE_E enUartType);
/**
\brief Get UART(Universal Asynchronous Receiver/Transmitter) status. CNcomment:��ȡUART״̬  CNend
\attention \n
None CNcomment:�� CNend
\param[in] enUartType: UART type. CNcomment:UART����  CNend
\param[out] pbDisable Pointer to UART Stat. CNcomment:ָ��UARTȥʹ�ܱ��ֵ��ָ�� CNend
\retval ::HI_SUCCESS Success.  CNcomment:APIϵͳ���óɹ� CNend
\retval ::HI_FAILURE Failure.  CNcomment:APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_OTP_NOT_INIT The otp module is not initialized.  CNcomment:OTPδ��ʼ�� CNend
\retval ::HI_ERR_OTP_INVALID_PARA The input parameter is invalid. CNcomment:��������Ƿ� CNend
\retval ::HI_ERR_OTP_NOT_SUPPORT Not support for this chipset. CNcomment:��оƬ��֧�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_OTP_GetUARTStat(HI_UNF_OTP_UART_TYPE_E enUartType, HI_BOOL *pbDisable);

/** @} */  /** <!-- ==== API declaration end ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_OTP_H__ */
