/******************************************************************************

Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_unf_advca.h
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : Hisilicon CA API declaration
Function List :
History       :
******************************************************************************/
#ifndef __HI_UNF_ADVCA_H__
#define __HI_UNF_ADVCA_H__

#include "hi_type.h"
#include "hi_unf_cipher.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      ADVCA */
/** @{ */  /** <!-- [ADVCA] */

/** advanced CA session serect key class*/
typedef enum hiUNF_ADVCA_KEYLADDER_LEV_E
{
    HI_UNF_ADVCA_KEYLADDER_LEV1     = 0,    /**<session serect key level 1*/
    HI_UNF_ADVCA_KEYLADDER_LEV2 ,           /**<session serect key level 2*/
    HI_UNF_ADVCA_KEYLADDER_LEV3 ,           /**<session serect key level 3*/
    HI_UNF_ADVCA_KEYLADDER_LEV4,            /**<session serect key level 4*/
    HI_UNF_ADVCA_KEYLADDER_LEV5,            /**<session serect key level 5*/
    HI_UNF_ADVCA_KEYLADDER_LEV6,            /**<session serect key level 6*/
    HI_UNF_ADVCA_KEYLADDER_BUTT
}HI_UNF_ADVCA_KEYLADDER_LEV_E;

/** advanced CA session keyladder target */
typedef enum hiUNF_ADVCA_CA_TARGET_E
{
    HI_UNF_ADVCA_CA_TARGET_DEMUX         = 0, /**<demux*/
    HI_UNF_ADVCA_CA_TARGET_MULTICIPHER,       /**<multicipher*/
    HI_UNF_ADVCA_CA_TARGET_BUTT
}HI_UNF_ADVCA_CA_TARGET_E;

/** advanced CA Encrypt arith*/
typedef enum hiUNF_ADVCA_ALG_TYPE_E
{
    HI_UNF_ADVCA_ALG_TYPE_TDES      = 0,    /**<Encrypt arith :3 DES*/
    HI_UNF_ADVCA_ALG_TYPE_AES,              /**<Encrypt arith : AES*/
    HI_UNF_ADVCA_ALG_TYPE_SM4,              /**<Encrypt arith : SM4*/
    HI_UNF_ADVCA_ALG_TYPE_BUTT
}HI_UNF_ADVCA_ALG_TYPE_E;

/** FLASH device types*/
typedef enum hiUNF_ADVCA_FLASH_TYPE_E
{
    HI_UNF_ADVCA_FLASH_TYPE_SPI     = 0,    /**<SPI flash*/
    HI_UNF_ADVCA_FLASH_TYPE_NAND ,          /**<nand flash*/
    HI_UNF_ADVCA_FLASH_TYPE_NOR ,           /**<nor flash*/
    HI_UNF_ADVCA_FLASH_TYPE_EMMC ,          /**<eMMC*/
    HI_UNF_ADVCA_FLASH_TYPE_SPI_NAND ,      /**<spi_nand flash*/
    HI_UNF_ADVCA_FLASH_TYPE_SD,             /**<FSD/TSD flash*/
    HI_UNF_ADVCA_FLASH_TYPE_BUTT
}HI_UNF_ADVCA_FLASH_TYPE_E;

/** JTAG protect mode*/
typedef enum hiUNF_ADVCA_JTAG_MODE_E
{
    HI_UNF_ADVCA_JTAG_MODE_OPEN     = 0,
    HI_UNF_ADVCA_JTAG_MODE_PROTECT,
    HI_UNF_ADVCA_JTAG_MODE_CLOSED,
    HI_UNF_ADVCA_JTAG_MODE_BUTT
}HI_UNF_ADVCA_JTAG_MODE_E;


typedef struct HiUNF_ADVCA_LOCK_TZ_OTP_PARAM
{
    HI_U32 u32Addr;
    HI_U32 u32Len;
}HI_UNF_ADVCA_LOCK_TZ_OTP_PARAM_S;

typedef enum hiUNF_ADVCA_SP_DSC_MODE_E
{
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_CSA2              = 0x0000,   /**<Demux PAYLOAD CSA2 */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_CSA3              = 0x0010,   /**<Demux PAYLOAD CSA3 */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_IDSA      = 0x0020,   /**<Demux PAYLOAD AES  IPTV Mode */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_ECB           = 0x0021,   /**<Demux PAYLOAD AES  ECB Mode */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_CI        = 0x0022,   /**<Demux PAYLOAD AES  CIPLUS */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_DES_IPTV          = 0x0030,   /**<Demux PAYLOAD DES  CIPLUS */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_DES_CIPLUS        = 0x0032,   /**<Demux PAYLOAD DES  CIPLUS */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_DES_CBC           = 0x0033,   /**<Demux PAYLOAD DES  CBC */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_NOVEL         = 0x0040,   /**<Demux PAYLOAD AES  NOVEL */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_SMS4_NOVEL        = 0x0041,   /**<Demux PAYLOAD SMS4 NOVEL */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_SMS4_IPTV         = 0x0050,   /**<Demux PAYLOAD SMS4 IPTV */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_SMS4_ECB          = 0x0051,   /**<Demux PAYLOAD SMS4 ECB */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_SMS4_CBC          = 0x0053,   /**<Demux PAYLOAD SMS4 CBC */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC           = 0x0063,   /**<Demux PAYLOAD AES  CBC */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_TDES_IPTV         = 0x0070,   /**<Demux PAYLOAD TDES IPTV */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_TDES_ECB          = 0x0071,   /**<Demux PAYLOAD TDES ECB */
     HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_TDES_CBC          = 0x0073,   /**<Demux PAYLOAD TDES CBC */
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_CBC               = 0x4020,   /**<MultiCipher AES CBC */
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_ECB               = 0x4021,   /**<MultiCipher AES ECB */
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_CBC_PIFF          = 0x4022,   /**<MultiCipher AES CBC PIFF */
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_CBC_APPLE         = 0x4023,   /**<MultiCipher AES CBC APPLE */
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_AES_CTR               = 0x4024,   /**<MultiCipher AES CTR */
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_TDES_CBC              = 0x4040,   /**<MultiCipher AES CBC */
     HI_UNF_ADVCA_SP_DSC_MODE_RAW_TDES_ECB              = 0x4041,   /**<MultiCipher AES ECB */
     HI_UNF_ADVCA_SP_DSC_MODE_BUTT
}HI_UNF_ADVCA_SP_DSC_MODE_E;

/** Advca CA VendorID */
typedef enum hiUNF_ADVCA_VENDORID_E
{
    HI_UNF_ADVCA_NULL       = 0x00,        /**<No-Advcance CA chipset, Marked with 0*/
    HI_UNF_ADVCA_NAGRA      = 0x01,        /**<NAGRA  Chipse, Marked with R*/
    HI_UNF_ADVCA_IRDETO     = 0x02,        /**<IRDETO Chipset, Marked with I*/
    HI_UNF_ADVCA_CONAX      = 0x03,        /**<CONAX Chipset, Marked with C*/
    HI_UNF_ADVCA_SUMA       = 0x05,        /**<SUMA Chipset, Marked with S*/
    HI_UNF_ADVCA_NOVEL      = 0x06,        /**<NOVEL Chipset, Marked with Y*/
    HI_UNF_ADVCA_VERIMATRIX = 0x07,        /**<VERIMATRIX Chipset, Marked with M*/
    HI_UNF_ADVCA_CTI        = 0x08,        /**<CTI Chipset, Marked with T*/
    HI_UNF_ADVCA_COMMONCA   = 0x0b,        /**<COMMONCA Chipset, Marked with H*/
    HI_UNF_ADVCA_DCAS       = 0x0c,        /**<DCAS CA Chipset*/
    HI_UNF_ADVCA_PANACCESS  = 0x0e,        /**<PANACCESS CA Chipset*/
    HI_UNF_ADVCA_VENDORIDE_BUTT
}HI_UNF_ADVCA_VENDORID_E;

/** Advca CA lock type */
typedef enum hiUNF_ADVCA_LOCK_TYPE
{
    HI_UNF_ADVCA_LOCK_RSA_KEY = 0,
    HI_UNF_ADVCA_LOCK_TZ_OTP,
    HI_UNF_ADVCA_LOCK_MISC_KL_DISABLE,
    HI_UNF_ADVCA_LOCK_GG_KL_DISABLE,
    HI_UNF_ADVCA_LOCK_TSKL_CSA3_DISABLE,
    HI_UNF_ADVCA_LOCK_BUTT,
}HI_UNF_ADVCA_LOCK_TYPE_E;


/** DCAS KeyLadder use mode */
typedef enum hiUNF_ADVCA_DCAS_KEYLADDER_LEV_E
{
    HI_UNF_ADVCA_DCAS_KEYLADDER_EK2         = 0,    /**<session EK2*/
    HI_UNF_ADVCA_DCAS_KEYLADDER_EK1         = 1,    /**<session EK1*/
    HI_UNF_ADVCA_DCAS_KEYLADDER_VENDORSYSID = 8,    /**<session Vendor_SysID*/
    HI_UNF_ADVCA_DCAS_KEYLADDER_NONCE       = 9,    /**<session nonce*/
    HI_UNF_ADVCA_DCAS_KEYLADDER_BUTT
}HI_UNF_ADVCA_DCAS_KEYLADDER_LEV_E;

/**Defines the attribute ID of the OTP fuse. Please be kindly noted that the OTP fuse is set permanently.
After setting the OTP fuse, please power off and then power on the STB to make the OTP fuse function effective */
/**CNcomment: ����OTPλIDö������. ��ע��OTPλ���ú󲻿ɸı�.
���ú���ϵ�����ʹOTPλ������Ч.*/
typedef enum hiUNF_ADVCA_OTP_FUSE_E
{
    HI_UNF_ADVCA_OTP_NULL = 0,
    HI_UNF_ADVCA_OTP_SECURE_BOOT_ACTIVATION, /**<Whether to enable the secure boot authentication, set the boot flash type together, HI_UNF_ADVCA_OTP_SECURE_BOOT_ATTR_S*//**<CNcomment: ��ȫ�����Ƿ�����ͬʱ���ð�ȫ����flash����, HI_UNF_ADVCA_OTP_SECURE_BOOT_ATTR_S*/
    HI_UNF_ADVCA_OTP_BOOT_DECRYPTION_ACTIVATION, /**<Whether to enable the secure boot decryption, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: boot���ܹ����Ƿ���, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_SELF_BOOT_DEACTIVATION, /**<Whether to disable the self boot, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: �Ծ��Ƿ�ر�, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_DDR_WAKEUP_DEACTIVATION, /**<Whether to disable the DDR wakeup, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: ����ԭ�ػ����Ƿ�ر� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_CSA2_KL_LEVEL_SEL, /**<CSA2 keyladder stage, HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*//**<CNcomment: CSA2 keyladder���� , HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*/
    HI_UNF_ADVCA_OTP_R2R_KL_LEVEL_SEL, /**<R2R keyladder stage, HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*//**<CNcomment: R2R keyladder���� , HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*/
    HI_UNF_ADVCA_OTP_SP_KL_LEVEL_SEL, /**<SP keyladder stage, HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*//**<CNcomment: SP keyladder���� , HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*/
    HI_UNF_ADVCA_OTP_CSA3_KL_LEVEL_SEL, /**<CSA3 keyladder stage, HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*//**<CNcomment: CSA3 keyladder���� , HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*/
    HI_UNF_ADVCA_OTP_LP_DEACTIVATION, /**<Whether to disable the LP keyladder, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: LP keyladder�Ƿ�ر� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_CSA2_CW_HARDONLY_ACTIVATION, /**<Whether to enable the CSA2 hard CW only, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: CSA2ӲCW�Ƿ�ʹ�� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_SP_CW_HARDONLY_ACTIVATION, /**<Whether to enable the SP hard CW only, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: SPӲCW�Ƿ�ʹ�� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_CSA3_CW_HARDONLY_ACTIVATION, /**<Whether to enable the CSA3 hard CW only, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: CSA3ӲCW�Ƿ�ʹ�� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_CSA2_KL_DEACTIVATION, /**<Whether to disable the CSA2 keyladder crypto engine, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: CSA2 keyladder���������Ƿ�ر� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_SP_KL_DEACTIVATION, /**<Whether to disable the SP keyladder crypto engine, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: SP keyladder���������Ƿ�ر� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_CSA3_KL_DEACTIVATION, /**<Whether to disable the CSA3 keyladder crypto engine, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: CSA3 keyladder���������Ƿ�ر�, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_MISC_KL_DEACTIVATION, /**<Whether to disable the MISC keyladder crypto engine, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: MISC keyladder���������Ƿ�ر� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_GOOGLE_KL_DEACTIVATION, /**<Whether to disable the google keyladder crypto engine, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: Google keyladder���������Ƿ�ر�, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_DCAS_KL_DEACTIVATION, /**<Whether to disable the DCAS keyladder crypto engine, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: DCAS keyladder���������Ƿ�ر� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_DDR_SCRAMBLE_ACTIVATION, /**<Whether to enable the DDR scrambling, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: DDR�����Ƿ��� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_GLOBAL_LOCK_ACTIVATION, /**<Whether to lock the whole OTP area, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: OTPд�����Ƿ��� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_RUNTIME_CHECK_ACTIVATION, /**<Whether to enable the runtime check, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: Runtime check�Ƿ��� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_DDR_WAKEUP_CHECK_ACTIVATION, /**<Whether to enable the DDR check when wakeup from standby, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: ����ԭ�ػ���ʱDDRУ���Ƿ��� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_VERSION_ID_CHECK_ACTIVATION, /**<Whether to enable the version id check, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: Version IDУ���Ƿ��� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_BOOT_MSID_CHECK_ACTIVATION, /**<Whether to enable the boot MSID check, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: Boot MSIDУ���Ƿ��� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_JTAG_MODE, /**<JTAG protected mode, HI_UNF_ADVCA_JTAG_PRT_MODE_ATTR_S*//**<CNcomment: JTAG����ģʽ , HI_UNF_ADVCA_JTAG_PRT_MODE_ATTR_S*/
    HI_UNF_ADVCA_OTP_JTAG_READ_DEACTIVATION, /**<Whether to disable to read OTP via JTAG, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: ͨ��JTAG��ȡOTP�Ƿ�ر� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_CSA2_ROOTKEY, /**<CSA2 keyladder root key, HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*//**<CNcomment: CSA2 keyladder����Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_R2R_ROOTKEY, /**<R2R keyladder root key, HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*//**<CNcomment: R2R keyladder����Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_SP_ROOTKEY, /**<SP keyladder root key, HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*//**<CNcomment: SP keyladder����Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_CSA3_ROOTKEY, /**<CSA3 keyladder root key, HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*//**<CNcomment: CSA3 keyladder����Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_MISC_ROOTKEY, /**<MISC keyladder root key, HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*//**<CNcomment: MISC keyladder����Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_OEM_ROOTKEY, /**<OEM keyladder root key, HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*//**<CNcomment: OEM keyladder����Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_ESCK_ROOTKEY, /**<ESCK keyladder root key, HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*//**<CNcomment: ESCK keyladder����Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_JTAG_KEY, /**<JTAG key, HI_UNF_ADVCA_JTAG_KEY_ATTR_S*//**<CNcomment: JTAG��Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_CHIP_ID, /**<Chip ID, HI_UNF_ADVCA_CHIPID_ATTR_S*//**<CNcomment: Chip ID, HI_UNF_ADVCA_JTAG_KEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_MARKET_SEGMENT_ID, /**<Market segment ID, HI_UNF_ADVCA_MARKET_ID_ATTR_S*//**<CNcomment: Market segment ID , HI_UNF_ADVCA_MARKET_ID_ATTR_S*/
    HI_UNF_ADVCA_OTP_VERSION_ID, /**<Version ID, HI_UNF_ADVCA_VERSION_ID_ATTR_S*//**<CNcomment: Version ID, HI_UNF_ADVCA_VERSION_ID_ATTR_S*/
    HI_UNF_ADVCA_OTP_MISC_KL_LEVEL_SEL, /**<MISC keyladder stage, HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*//**<CNcomment: MISC keyladder���� , HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S*/
    HI_UNF_ADVCA_OTP_VMX_BL_FUSE, /**<Burn verimatrix bootloader fuse*//**<CNcomment: ��дverimatrix�ض���bootloader fuseλ*/
    HI_UNF_ADVCA_OTP_IRDETO_ITCSA3_ACTIVATION, /**<Whether to enbale the tweaked CSA3, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: ˽��CSA3�㷨�Ƿ�����HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_BOOTINFO_DEACTIVATION, /**<Whether to disable the bootinfo, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: Bootinfo�Ƿ�ر�, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_ITCSA3_IMLB, /**<tweaked CSA3 IMLB, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: ˽��CSA3�㷨IMLB,HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_USB_DEACTIVATION, /**<Whether to disable the usb host, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: ��ֹUSB�豸, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_SERIAL_DEACTIVATION, /**<Whether to disable serial port, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: ��ֹ���ڹ���, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_ETHERNET_DEACTIVATION, /**<Whether to disable the ethernet, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: ��ֹ����, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_SM4_CRYPTO_ENGINE_DEACTIVATION, /**<Whether to disable the SM4 crypto engine, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: SM4���������Ƿ�ر� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_TDES_CRYPTO_ENGINE_DEACTIVATION, /**<Whether to disable the TDES crypto engine, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: TDES���������Ƿ�ر� , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/

    HI_UNF_ADVCA_OTP_SECURE_BOOT_ACTIVATION_ONLY,   /**<Enable secure boot authentication only, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*//**<CNcomment: ��ȫ����ʹ�ܣ� HI_UNF_ADVCA_OTP_SECURE_BOOT_ATTR_S*/
    HI_UNF_ADVCA_OTP_BOOT_FLASH_TYPE,   /**<Boot flash type, HI_UNF_ADVCA_OTP_BOOT_FLASH_TYPE_ATTR_S*//**<CNcomment: ��ȫ����flash���ͣ� HI_UNF_ADVCA_OTP_BOOT_FLASH_TYPE_ATTR_S*/

    HI_UNF_ADVCA_OTP_RSA_KEY_LOCK_FLAG,   /**< Get the lock flag of RSA_Root_key, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡRSA_Root_Key lock��ǣ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_STBSN_LOCK_FLAG,   /**< Get the lock flag of STBSN, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡSTBSN lock��ǣ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_MSID_LOCK_FLAG,   /**< Get the lock flag of MSID, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡMSID lock��ǣ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_VERSIONID_LOCK_FLAG,   /**< Get the lock flag of VersionID, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡVersionID lock��ǣ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_OEM_ROOTKEY_LOCK_FLAG,   /**< Get the lock flag of OEM_Root_key, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡOEM_Root_key lock��ǣ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_R2R_ROOTKEY_LOCK_FLAG,   /**< Get the lock flag of R2R_Root_key, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡR2R_Root_key lock��ǣ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_JTAG_KEY_LOCK_FLAG,   /**< Get the lock flag of JTAG key, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡJTAG key lock��ǣ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_TZ_AREA_LOCK_FLAG,   /**< Get the lock flag of OTP trust area, when otp_tz_area_enable is set, these lock flags can only be accessed by secure cpu , HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡOTP trust area lock��ǣ���otp_tz_area_enable������ʱ����Щ���ֻ�ܱ���ȫCPU��ȡ��HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_BOOT_ENCRYPTION_DEACTIVATION, /**< whether to diable boot loader key generation, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ����bootloader key�����Ƿ�رգ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_BOOT_ROOTKEY,        /**<Boot keyladder root key, HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*//**<CNcomment: boot keyladder����Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_SEC_STORE_ROOTKEY,   /**<Sec store keyladder root key, HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*//**<CNcomment: Sec store keyladder����Կ , HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S*/
    HI_UNF_ADVCA_OTP_BOOT_ROOTKEY_LOCK_FLAG, /**< Get the lock flag of BOOT_Root_key, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡBOOT_Root_Key lock��ǣ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_SEC_STORE_ROOTKEY_LOCK_FLAG, /**< Get the lock flag of SEC_STORE_Root_key, HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/ /**<CNcomment: ��ȡSEC_STORE_Root_Key lock��ǣ�HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S*/
    HI_UNF_ADVCA_OTP_SOS_MSID, /**< Get the security OS MSID (market segment id)*/ /**<CNcomment: ��ȡ��ȫϵͳ��MSID */
    HI_UNF_ADVCA_OTP_REE_MSID, /**< Get MSID(market segment id) of REE images, Currently, this fuse is used for SBL(second boot loader) of VMX ultra*/ /**<CNcomment: ��ȡREE�����MSID Ŀǰ��VMX ultra��ȫ������Ҫʹ�ô�OTPУ�����boot*/
    HI_UNF_ADVCA_OTP_FUSE_BUTT
}HI_UNF_ADVCA_OTP_FUSE_E;

/**Defines the attribute of secure boot check.*/
/**CNcomment: ���尲ȫ����У�����Խṹ��*/
typedef struct hiUNF_ADVCA_OTP_SECURE_BOOT_ATTR_S
{
    HI_BOOL bEnable;    /**<Is secure boot check enable or not*/
    HI_UNF_ADVCA_FLASH_TYPE_E enFlashType; /**<Boot flash type*/
}HI_UNF_ADVCA_OTP_SECURE_BOOT_ATTR_S;

/**Defines the boot flash type.*/
/**CNcomment: ���尲ȫ����flash���ͽṹ��*/
typedef struct hiUNF_ADVCA_OTP_BOOT_FLASH_TYPE_ATTR_S
{
    HI_BOOL bBootSelCtrl;    /**<0--the boot flash type is defined by chipset pin, 1--the boot flash type is defined by OTP value*/
    HI_UNF_ADVCA_FLASH_TYPE_E enFlashType; /**<Boot flash type, only valid when bBootSelCtrl is 1*/
}HI_UNF_ADVCA_OTP_BOOT_FLASH_TYPE_ATTR_S;

/**Defines the default attribute of OTP fuse. If one OTP fuse can ONLY be "Enable" or "Disable",
then we will use this attribute.*/
/**CNcomment: ����OTPλĬ�����Խṹ��. ������һ��OTPλ�Ĺ���
ֻ�ǿ�����رյ����*/
typedef struct hiUNF_ADVCA_OTP_DEFAULT_ATTR_S
{
    HI_BOOL bEnable;    /**<Is the feature enable or not*/
}HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S;

/**Defines the attribute of the keyladder level.*/
/**CNcomment: ����keyladder�������Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKeyladderLevel;   /**<Keyladder level*/
}HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S;

/**Defines the attribute of the JTAG protected mode.*/
/**CNcomment: ����JTAG�ӿڱ������Խṹ��.*/
typedef struct hiUNF_ADVCA_JTAG_PRT_MODE_ATTR_S
{
    HI_UNF_ADVCA_JTAG_MODE_E enJtagMode;    /**<JTAG protection mode*/
}HI_UNF_ADVCA_JTAG_PRT_MODE_ATTR_S;

/**Defines the attribute of the keyladder root key.*/
/**CNcomment: ����keyladder ����Կ���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S
{
    HI_U8 u8RootKey[16];    /**<Root key of the keyladder*/
}HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S;

/**Defines the attribute of the JTAG key.*/
/**CNcomment: ����JTAG�ӿڱ�����Կ���Խṹ��.*/
typedef struct hiUNF_ADVCA_JTAG_KEY_ATTR_S
{
    HI_U8 u8JtagKey[8];     /**<JTAG protected key*/
}HI_UNF_ADVCA_JTAG_KEY_ATTR_S;

/**Defines the attribute of the chip id.*/
/**CNcomment: ����chip id���Խṹ��.*/
typedef struct hiUNF_ADVCA_CHIPID_ATTR_S
{
    HI_U8 au8ChipId[8];       /**<ChipID of the chipset, it is unique every chipset*/
}HI_UNF_ADVCA_CHIPID_ATTR_S;

/**Defines the attribute of the market segment id.*/
/**CNcomment: ����market segment id���Խṹ��.*/
typedef struct hiUNF_ADVCA_MARKET_ID_ATTR_S
{
    HI_U8 u8MSID[4];    /**<Market Segment ID*/
}HI_UNF_ADVCA_MARKET_ID_ATTR_S;

/**Defines the attribute of the version id.*/
/**CNcomment: ����version id���Խṹ��.*/
typedef struct hiUNF_ADVCA_VERSION_ID_ATTR_S
{
    HI_U8 u8VersionId[4];   /**<Bootloader Version ID*/
}HI_UNF_ADVCA_VERSION_ID_ATTR_S;

typedef struct hiUNF_ADVCA_VMX_BL_FUSE_ATTR_S
{
    HI_U32 u32VMXBLFuse;
}HI_UNF_ADVCA_VMX_BL_FUSE_S;

/**Defines the attribute of the tweaked CSA3 IMLB.*/
/**CNcomment: ����tweaked CSA3 IMLB���Խṹ��.*/
typedef struct hiUNF_ADVCA_ITCSA3_IMLB_ATTR_S
{
    HI_U8 au8ItCsa3IMLB[2];   /**<tweaked CSA3 IMLB*/
}HI_UNF_ADVCA_ITCSA3_IMLB_ATTR_S;

/**Defines the attribute of the OTP fuse.*/
/**CNcomment: ����OTP fuse���Խṹ��.*/
typedef struct hiUNF_ADVCA_OTP_ATTR_S
{
    union
    {
        HI_UNF_ADVCA_OTP_DEFAULT_ATTR_S          stDefaultAttr; /**<Default attribute, if one fuse can ONLY be "Enable" or "Disable", then we can use this attribute*/
        HI_UNF_ADVCA_OTP_SECURE_BOOT_ATTR_S      stEnableSecureBoot; /**<Secure boot attribute*/
        HI_UNF_ADVCA_KEYLADDER_LEVEL_SEL_ATTR_S  stKeyladderLevSel;  /**<Keyladder level attribute*/
        HI_UNF_ADVCA_JTAG_PRT_MODE_ATTR_S        stJtagPrtMode; /**<JTAG protected mode attribute*/
        HI_UNF_ADVCA_KEYLADDER_ROOTKEY_ATTR_S    stKeyladderRootKey; /**<Keyladder rootkey attribute*/
        HI_UNF_ADVCA_JTAG_KEY_ATTR_S             stJtagKey;   /**<JTAG key attribute*/
        HI_UNF_ADVCA_CHIPID_ATTR_S               stChipId;     /**<Chip ID attribute*/
        HI_UNF_ADVCA_MARKET_ID_ATTR_S            stMarketId;    /**<Market segment ID attribute*/
        HI_UNF_ADVCA_VERSION_ID_ATTR_S           stVersionId;  /**<Bootloadder version ID attribute*/
        HI_UNF_ADVCA_VMX_BL_FUSE_S               stVMXBLFuse;  /**<Vmx Bootloadder specific fuse attribute*/
        HI_UNF_ADVCA_ITCSA3_IMLB_ATTR_S          stItCsa3IMLB; /**<tweaked CSA3 IMLB attribute*/
        HI_UNF_ADVCA_OTP_BOOT_FLASH_TYPE_ATTR_S  stBootFlashType;   /**<Boot flash type attribute*/
    }unOtpFuseAttr;
}HI_UNF_ADVCA_OTP_ATTR_S;

/**Defines the attribute of the keyladder type ID.*/
/**CNcomment: ����keyladder����ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_TYPE_E
{
    HI_UNF_ADVCA_KEYLADDER_CSA2 = 0,        /**<CSA2 keyladder*/
    HI_UNF_ADVCA_KEYLADDER_CSA3,            /**<CSA3 keyladder*/
    HI_UNF_ADVCA_KEYLADDER_R2R,             /**<R2R keyladder*/
    HI_UNF_ADVCA_KEYLADDER_SP,              /**<SP keyladder*/
    HI_UNF_ADVCA_KEYLADDER_MISC,            /**<MISC keyladder*/
    HI_UNF_ADVCA_KEYLADDER_LP,              /**<LP keyladder*/
    HI_UNF_ADVCA_KEYLADDER_TA,              /**<TA keyladder*/
    HI_UNF_ADVCA_KEYLADDER_GDRM,            /**<Google DRM key ladder*/
    HI_UNF_ADVCA_KEYLADDER_SECSTORE,        /**<Secure Store key ladder*/
    HI_UNF_ADVCA_KEYLADDER_SWPKDEC,         /**<SWPK DEC key ladder*/
    HI_UNF_ADVCA_KEYLADDER_SWPKENC,         /**<SWPK ENC key ladder*/
    HI_UNF_ADVCA_KEYLADDER_TYPE_BUTT
}HI_UNF_ADVCA_KEYLADDER_TYPE_E;

/**Defines the attribute of the CSA2 keyladder type ID.*/
/**CNcomment: ����CSA2 keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_CSA2_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_ALG = 0,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_E;

/**Defines the attribute of the CSA3 keyladder type ID.*/
/**CNcomment: ����CSA3 keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_CSA3_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_ALG = 0,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_E;

/**Defines the attribute of the R2R keyladder type ID.*/
/**CNcomment: ����R2R keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_R2R_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_ALG = 0,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_E;



/**Defines the attribute of the SP keyladder type ID.*/
/**CNcomment: ����SP keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_SP_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ENABLE = 0,       /**<Use SPE keyladder or not for specal CA system */
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ALG ,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_DSC_MODE,   /**<Descrambling mode*/
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_SP_ATTR_E;

/**Defines the attribute of the MISC keyladder type ID.*/
/**CNcomment: ����MISC keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_MISC_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ENABLE = 0, /**<Use MISC keyladder or not. Before using the MISC keyladder, should set this attribute to HI_TRUE,
                                                                     and after using, should set it to HI_FALSE.*/
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ALG,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_DSC_MODE,   /**<Descrambling mode*/
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_E;

/**Defines the attribute of the TA keyladder type ID.*/
/**CNcomment: ����TA keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_TA_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ENABLE = 0, /**<Use TA keyladder or not. Before using the TA keyladder, should set this attribute to HI_TRUE,
                                                                     and after using, should set it to HI_FALSE.*/
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ALG,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_LOAD_TRANDATA,   /**<Transformation data protection and loading*/
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_TA_ATTR_E;

/**Defines the attribute of the SECSTORE keyladder type ID.*/
/**CNcomment: ����SECSTORE keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_SECSTORE_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_ENABLE = 0, /**<Use SECSTORE keyladder or not. Before using the TA keyladder, should set this attribute to HI_TRUE,
                                                                     and after using, should set it to HI_FALSE.*/
    HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_ALG,            /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_E;

/**Defines the attribute of the SWPK DEC keyladder type ID.*/
/**CNcomment: ����SWPK DEC keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_ALG = 0,            /**<Keyladder algorithm, TDES/SM4*/
    HI_UNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_E;

/**Defines the attribute of the SWPK ENC keyladder type ID.*/
/**CNcomment: ����SWPK ENC keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_SWPKENC_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_SWPKENC_ATTR_ALG = 0,            /**<Keyladder algorithm, TDES/SM4*/
    HI_UNF_ADVCA_KEYLADDER_SWPKENC_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_SWPKENC_ATTR_E;

/**Defines the attribute of the CSA2 keyladder.*/
/**CNcomment: ����CSA2 keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_CSA2_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_E  enCsa2KlAttr; /**<CSA2 keyladder attribute ID*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;          /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                   /**<Session key*/
}HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_S;

/**Defines the attribute of the CSA3 keyladder.*/
/**CNcomment: ����CSA3 keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_CSA3_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_E  enCsa3KlAttr; /**<CSA3 keyladder attribute ID*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;          /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                    /**<Session key*/
}HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_S;

/**Defines the attribute of the R2R keyladder.*/
/**CNcomment: ����R2R keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_R2R_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_E  enR2RKlAttr; /**<R2R keyladder attribute  ID*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;          /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                   /**<Session key*/
}HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_S;

/**Defines the attribute of the SP keyladder.*/
/**CNcomment: ����SP keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_SP_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_E  enSPKlAttr; /**<SP keyladder attribute ID*/
    HI_BOOL bEnable;    /**<Use SP keyladder or not. Before using the SP keyladder*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;               /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_SP_DSC_MODE_E enDscMode;    /**<Descramblig mode*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;         /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                         /**<Session key*/
}HI_UNF_ADVCA_KEYLADDER_SP_ATTR_S;



/**Defines the attribute of the MISC keyladder.*/
/**CNcomment: ����MISC keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_MISC_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_E  enMiscKlAttr; /**<MISC keyladder attribute ID*/
    HI_BOOL bEnable;    /**<Use MISC keyladder or not. Before using the MISC keyladder, should be set to HI_TRUE,
                            and after using, should be set to HI_FALSE.*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;               /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_SP_DSC_MODE_E enDscMode;    /**<Descramblig mode*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;         /**<Keyladder stage of the session key to be set*/
    HI_U8 u8SessionKey[16];                                         /**<Session key*/
}HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_S;

/**Defines the attribute of the TA keyladder.*/
/**CNcomment: ����TA keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_TA_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_E  enTAKlAttr; /**<TA keyladder attribute ID*/
    HI_BOOL bEnable;    /**<Use TA keyladder or not. Before using the TA keyladder, should be set to HI_TRUE,
                            and after using, should be set to HI_FALSE.*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;          /**<Keyladder algorithm, TDES/AES*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;   /**<Keyladder stage of the session key to be set*/
    HI_U8 au8SessionKey[16];                                   /**<Session key*/
    HI_U8 *pu8TranData;                                         /**<Transformation data*/
    HI_U32 u32TranDataLen;                                  /**<Transformation data length*/
}HI_UNF_ADVCA_KEYLADDER_TA_ATTR_S;

/**Defines the attribute of the Google DRM keyladder type ID.*/
/**CNcomment: ����Google DRM keyladder��������ID.*/
typedef enum hiUNF_ADVCA_KEYLADDER_GDRM_ATTR_E
{
    HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENABLE = 0,    /**<Use GDRM keyladder or not. Before using the GDRM keyladder, should set this attribute to HI_TRUE, and after using, should set it to HI_FALSE.*/
    HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENCRYPT,       /**<Encrypt clear device key*/
    HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_SESSION_KEY,   /**<Keyladder session key*/
    HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_GETFLAG,       /**<Get flag*/
    HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_BUTT
}HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_E;

/**Defines the attribute of Google DRM keyladder.*/
/**CNcomment: ����Google DRM keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_GDRM_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_E  enGDRMKlAttr;
    HI_BOOL bEnable;                                  /**<Use GDRM keyladder or not. Before using the GDRM keyladder, should be set to HI_TRUE, and after using, should set it to HI_FALSE.*/
    HI_UNF_ADVCA_KEYLADDER_LEV_E enStage;       /**<Keyladder stage of the session key to be set*/
    HI_HANDLE hCipherHandle;                    /**<cipher handle, if enStage is HI_UNF_ADVCA_KEYLADDER_LEV3, hCipherHandle should be set*/
    HI_U8 au8SessionKey[32];                     /**<if select HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENCRYPT it is clear device key, if select HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_SESSION_KEY, it is session key*/
    HI_U8 au8Output[16];                          /**<if HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENCRYPT is set, it is encrypted device key, if HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_GETFLAG is set, it is flag*/
}HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_S;

/**Defines the attribute of the TA keyladder.*/
/**CNcomment: ����TA keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_SECSTORE_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_E  enSECSTREKlAttr; /**<Secure STORE keyladder attribute ID*/
    HI_BOOL bEnable;    /**<Use Secure STORE keyladder or not. Before using the Secure STORE keyladder, should be set to HI_TRUE,
                            and after using, should be set to HI_FALSE.*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;          /**<Keyladder algorithm, TDES/AES*/
}HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_S;

/**Defines the attribute of the SWPK DEC keyladder.*/
/**CNcomment: ����SWPK DEC keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_E  enSWPKDECKlAttr;     /**<SWPK DEC keyladder attribute ID*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;                          /**<Keyladder algorithm, TDES/SM4*/
}HI_UNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_S;

/**Defines the attribute of the SWPK ENC keyladder.*/
/**CNcomment: ����SWPK ENC keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_SWPKENC_ATTR_S
{
    HI_UNF_ADVCA_KEYLADDER_SWPKENC_ATTR_E  enSWPKENCKlAttr;     /**<SWPK ENC keyladder attribute ID*/
    HI_UNF_ADVCA_ALG_TYPE_E enAlgType;                          /**<Keyladder algorithm, TDES/SM4*/
}HI_UNF_ADVCA_KEYLADDER_SWPKENC_ATTR_S;

/**Defines the attribute of all of the keyladder.*/
/**CNcomment: �������� keyladder���Խṹ��.*/
typedef struct hiUNF_ADVCA_KEYLADDER_ATTR_S
{
    union
    {
        HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_S      stCSA2KlAttr;       /**<CSA2 keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_S      stCSA3KlAttr;       /**<CSA3 keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_S       stR2RKlAttr;        /**<R2R keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_SP_ATTR_S        stSPKlAttr;         /**<SP keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_S      stMiscKlAttr;       /**<MISC keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_TA_ATTR_S        stTAKlAttr;         /**<TA keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_S      stGDRMAttr;         /**<Google DRM keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_SECSTORE_ATTR_S  stSECSTOREAttr;     /**<Secure STORE keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_SWPKDEC_ATTR_S   stSWPKDECKlAttr;    /**<SWPKDEC keyladder attribute*/
        HI_UNF_ADVCA_KEYLADDER_SWPKENC_ATTR_S   stSWPKENCKlAttr;    /**<SWPKENE keyladder attribute*/
    }unKlAttr;
}HI_UNF_ADVCA_KEYLADDER_ATTR_S;


/**Defines the attribute of the CA vendor type ID.*/
/**CNcomment: ����CA vendor��������ID.*/
typedef enum hiUNF_ADVCA_CA_VENDOR_OPT_E
{
    HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_CHIP_CONF_CMAC = 0, /**<To generate a secure message authentication code (MAC) tag for the OTP configuration data*/
    HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_CBCMAC_CALC,  /**<To calculate the high level code CBC-MAC.*/
    HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_CBCMAC_AUTH,  /**<To authenticate the high level code CBC-MAC.*/
    HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_ACTIVATION_CODE, /**<To set the activation code for tweaked CSA3.*/
    HI_UNF_ADVCA_CA_VENDOR_OPT_VMX_GET_RNG, /**<To get the RNG number, ONLY used for verimatrix currently.*/
    HI_UNF_ADVCA_CA_VENDOR_OPT_BUTT
}HI_UNF_ADVCA_CA_VENDOR_OPT_E;

/**Defines the attribute of chip configuration CMAC.*/
/**CNcomment: �������OTP����CMAC���Խṹ��.*/
typedef struct hiUNF_ADVCA_IRDETO_CHIP_CONF_CMAC_ATTR_S
{
    HI_U8 au8ChipConfBitm[16]; /**<128bit Chip configuration bit map*/
    HI_U8 au8ChipConfCmac[16];   /**<128bit Chip configuration CMAC*/
}HI_UNF_ADVCA_IRDETO_CHIP_CONF_CMAC_ATTR_S;

/**Defines the attribute of the tweak CSA3, Activation Code.*/
/**CNcomment: ����CSA3�㷨��Ҫ���õ�ACTIVATION CODE.*/
typedef struct hiUNF_ADVCA_IRDETO_ACTIVATION_CODE_ATTR_S
{
    HI_U8 au8CSA3ActCode[16];   /**<128bit tweak CSA3 Activation Code*/
}HI_UNF_ADVCA_IRDETO_ACTIVATION_CODE_ATTR_S;

/**Defines the attribute of the high level code CBC-MAC authentication.*/
/**CNcomment: �����ϲ�Ӧ��CBC-MACУ�����Խṹ��.*/
typedef struct hiUNF_ADVCA_IRDETO_CBCMAC_ATTR_S
{
    HI_U8 *pu8InputData;
    HI_U32 u32InputDataLen;
    HI_U8 au8OutputCBCMAC[16];
    HI_U8 au8RefCBCMAC[16];  /**<Reference CBC-MAC*/
    HI_U32 u32AppLen; /**<High level code length*/
}HI_UNF_ADVCA_IRDETO_CBCMAC_ATTR_S;

typedef struct hiUNF_ADVCA_VMX_GetRNG_S
{
    HI_U32 u32RNG;
}HI_UNF_ADVCA_VMX_GetRNG_S;

/**Defines the attribute of the CA vendor private function.*/
/**CNcomment: ����CA����˽�й������Խṹ��.*/
typedef struct hiADVCA_CA_VENDOR_OPT_S
{
    HI_UNF_ADVCA_CA_VENDOR_OPT_E enCaVendorOpt;
    union
    {
        HI_UNF_ADVCA_IRDETO_CHIP_CONF_CMAC_ATTR_S     stIrdetoChipConfCmac;
        HI_UNF_ADVCA_IRDETO_ACTIVATION_CODE_ATTR_S    stIrdetoCsa3ActCode;
        HI_UNF_ADVCA_IRDETO_CBCMAC_ATTR_S             stIrdetoCbcMac;
        HI_UNF_ADVCA_VMX_GetRNG_S                     stVMXRng;
    }unCaVendorOpt;
}HI_UNF_ADVCA_CA_VENDOR_OPT_S;

/************************************************/

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup      ADVCA */
/** @{ */  /** <!-- [ADVCA] */

/**
\brief Initializes the advanced CA module CNcomment:��ʼ��advance CAģ�� CNend
\attention \n
Call this application programming interface (API) before using the advanced CA module.
The code HI_SUCCESS is returned if this API is called repeatedly.
CNcomment:�ڽ���advance CA��ز���ǰӦ�����ȵ��ñ��ӿ�\n
�ظ����ñ��ӿڣ��᷵�سɹ� CNend
\param N/A CNcomment:�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_OPEN_ERR The CA device fails to start CNcomment:HI_ERR_CA_OPEN_ERR ��CA�豸ʧ�� CNend
\see \n
::HI_UNF_ADVCA_DeInit
*/
HI_S32 HI_UNF_ADVCA_Init(HI_VOID);

/**
\brief Deinitializes the advanced CA module CNcomment:ȥ��ʼ��advance CAģ�� CNend
\attention \n
None CNcomment:�� CNend
\param N/A CNcomment:�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DeInit(HI_VOID);

/**
\brief Set the ChipId CNcomment:����ChipId  CNend
\attention \n
This application programming interface (API) is allowed to invoked only once.
It's not allowed to call this API repeatedly.
CHIP_ID should have been setting before chipset is delivered to STB Manufacture.
Please contact Hisilicon before Customer try to use this interface.
CNcomment:\n  CNend
CNcomment:�ýӿ�ֻ�������һ�Σ������ظ����ã������ʹ��\n
CHIP_ID�����Ѱ���CA��˾Ҫ�����ã��ýӿ�����ͻ���Ҫʹ�øýӿ���Ҫ��֪ͨ��˼\n  CNend
\param[in] Id chip id CNcomment:Id chip id\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\see \n
::HI_UNF_ADVCA_SetChipId
*/
HI_S32 HI_UNF_ADVCA_SetChipId(HI_U32 Id);

/**
\brief Obtains the chip ID CNcomment:��ȡоƬID  CNend
\attention \n
The chip ID is read-only.
CNcomment:оƬIDֻ�ܶ�����д CNend
\param[out] pu32ChipId Chip ID CNcomment:pu32ChipId   оƬID  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetChipId(HI_U32 *pu32ChipId);


/**
\brief Obtains the market ID CNcomment:��ȡMarket ID  CNend
\attention \n
None CNcomment:�� CNend
\param[out] u8MarketId market ID CNcomment:u8MarketId   ����г��ı�ʶ��� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetMarketId
*/
HI_S32 HI_UNF_ADVCA_GetMarketId(HI_U8 u8MarketId[4]);

/**
\brief Sets the Market ID CNcomment:����Market ID  CNend
\attention \n
The market ID of the set-top box (STB) is set before delivery. The market ID can be set once only and takes effects after the STB restarts.
CNcomment:�ڻ����г���ʱ���ã���֧������һ�� ���ú�������Ч CNend
\param[in] u8MarketId market ID CNcomment:u8MarketId   ����г��ı�ʶ��� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetMarketId(HI_U8 u8MarketId[4]);


/**
\brief Obtains the serial number of the STB CNcomment:��ȡ���������к� CNend
\attention \n
None CNcomment:�� CNend
\param[out] u8StbSn serial number of the STB CNcomment:u8StbSn   ���������к� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetStbSn
*/
HI_S32 HI_UNF_ADVCA_GetStbSn(HI_U8 u8StbSn[4]);

/**
\brief Sets the serial number of the STB CNcomment:���û��������к� CNend
\attention \n
The serial number of the STB is set before delivery. The market ID can be set once only and takes effects after the STB restarts.
CNcomment:�ڻ����г���ʱ���ã���֧������һ�� ���ú�������Ч CNend
\param[in] u8StbSn serial number of the STB CNcomment:u8StbSn   ���������к� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetStbSn(HI_U8 u8StbSn[4]);

/**
\brief Set the R2R RootKey and lock it. CNcomment:����R2R RootKey������ס��  CNend
\attention \n
This application programming interface (API) is allowed to invoked only once.
It's not allowed to call this API repeatedly.
R2R RootKey should have been setting before chipset is delivered to STB Manufacture.
Please contact Hisilicon before Customer try to use this interface.
CNcomment:�ýӿ�ֻ�������һ�Σ������ظ�����,�����ʹ�øýӿ�\n
R2RRootKey�����Ѱ���CA��˾Ҫ�����ã��ýӿ�����ͻ���Ҫʹ�øýӿ���Ҫ��֪ͨ��˼\n  CNend
\param[in] pkey R2R Root Key CNcomment:pkey  R2R����Կ\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
*/
HI_S32 HI_UNF_ADVCA_SetR2RRootKey(HI_U8 *pkey);

/**
\brief Obtains the security startup enable status CNcomment:��ȡ��ȫ����ʹ��״̬ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbEnable: Security startup enable. CNcomment:pbEnable   ��ȫ�����Ƿ�ʹ�ܣ� CNend
HI_TRUE enabled CNcomment:HI_TRUE ʹ�ܣ�  CNend
HI_FALSE disabled CNcomment:HI_FALSE ��ʹ�� CNend
\param[out] penFlashType the startup flash type, only valid when SCS is enable
CNcomment:penFlashType ���ڰ�ȫ����ʹ��ʱ��Ч����ʾ��ȫ������Flash���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetSecBootStat(HI_BOOL *pbEnable,HI_UNF_ADVCA_FLASH_TYPE_E *penFlashType);

/**
\brief Obtains the mode of the JTAG interface CNcomment:��ȡJTAG���Կ�ģʽ CNend
\attention \n
None CNcomment:�� CNend
\param[out] penJtagMode Mode of the JTAG interface CNcomment:penJtagMode   JTAG���Կ�ģʽ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_ADVCA_GetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E *penJtagMode);

/**
\brief Sets the mode of the JTAG interface CNcomment:����JTAG���Կ�ģʽ   CNend
\attention \n
If the mode of the JTAG interface is set to closed or password-protected, it cannot be opened.
If the JTAG interface is open, it can be closed or password-protected.
If the JATG interface is password-protected, it can be closed.
After being closed, the JATG interface cannot be set to open or password-protected mode.
CNcomment:��֧������Ϊ��״̬��\n
�򿪵�ʱ����Թرջ�����Ϊ��Կ����״̬��\n
������Կ����״̬ʱ���Թرա�\n
�ر�֮���ܴ򿪺�����Ϊ��Կ����״̬ CNend
\param[in] enJtagMode Mode of the JTAG interface CNcomment:enJtagMode   JTAG���Կ�ģʽ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN �ظ����� CNend
\see \n
::HI_UNF_ADVCA_JTAG_MODE_E
*/
HI_S32 HI_UNF_ADVCA_SetJtagMode(HI_UNF_ADVCA_JTAG_MODE_E enJtagMode);


/**
\brief Obtains the R2R key ladder stage CNcomment:��ȡR2R key ladder���� CNend
\attention \n
None CNcomment:�� CNend
\param[out] penStage Key ladder stage CNcomment:penStage   key ladder���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);

/**
\brief Sets the R2R key ladder stage CNcomment:����R2R key ladder�ļ���    CNend
\attention \n
The key ladder stage can be set only once before delivery and cannot be changed. Please use default value.
CNcomment:�����г���ʱ���� ��������һ�� ���ɸ���,������ʹ�øýӿڸı�stage  CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3
CNcomment:enStage   key ladder����\n ȡֵֻ��ΪHI_UNF_ADVCA_KEYLADDER_LEV2 ���� HI_UNF_ADVCA_KEYLADDER_LEV3  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief Obtains the digital video broadcasting (DVB) key ladder stage CNcomment:��ȡDVB key ladder�ļ��� CNend
\attention \n
None CNcomment:�� CNend
\param[out] penStage Key ladder stage CNcomment:penStage   key ladder���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);

/**
\brief Sets the DVB key ladder stage CNcomment:����DVB key ladder�ļ���    CNend
\attention \n
The key ladder stage can be set only once before delivery and cannot be changed. Please use default value.
CNcomment:�����г���ʱ���� ��������һ�� ���ɸ���,������ʹ�øýӿڸı�stage  CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage  key ladder����\n ȡֵֻ��ΪHI_UNF_ADVCA_KEYLADDER_lev2 ���� HI_UNF_ADVCA_KEYLADDER_lev3  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetDVBKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief Obtains the CSA3 key ladder stage CNcomment:��ȡCSA3 key ladder�ļ��� CNend
\attention \n
None CNcomment:�� CNend
\param[out] penStage Key ladder stage CNcomment:penStage   key ladder���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetCSA3KeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);

/**
\brief Sets the CSA3 key ladder stage CNcomment:����CSA3 key ladder�ļ���    CNend
\attention \n
The key ladder stage can be set only once before delivery and cannot be changed. Please use default value.
CNcomment:�����г���ʱ���� ��������һ�� ���ɸ���,������ʹ�øýӿڸı�stage  CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage  key ladder����\n ȡֵֻ��ΪHI_UNF_ADVCA_KEYLADDER_lev2 ���� HI_UNF_ADVCA_KEYLADDER_lev3  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetCSA3KeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief Sets session keys for an R2R key ladder CNcomment:ΪR2R key ladder���ûỰ��Կ    CNend
\attention \n

The stage of the session key cannot be greater than the configured stage of the key ladder. The last stage of the session key is configured by calling the API of the CIPHER module rather than this API.
That is, only session key 1 and session key 2 need to be configured for a 3-stage key ladder.
Only session key 1 needs to be configured for a 2-stage key ladder.
You need to set the key ladder stage by calling HI_UNF_ADVCA_SetR2RKeyLadderStage first.
Session keys can be set during initialization or changed at any time.
CNcomment:ע�����õļ������ܳ������õļ���ֵ�����һ����CIPHERģ���ڲ����ã�����ͨ���˽ӿ����á�\n
Ҳ����˵������3��key ladder��ֻ�����ûỰ��Կ1�ͻỰ��Կ2��\n
����2����key ladder��ֻ�����ûỰ��Կ1��\n
���ȵ���HI_UNF_ADVCA_SetR2RKeyLadderStage����key ladder������\n
�Ự��Կ���Գ�ʼʱ����һ�Σ�Ҳ������ʱ�޸ġ� CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage    ��Կ������[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]  CNend
\param[in] pu8Key Protection key pointer, 128 bits (16 bytes) in total CNcomment:pu8Key     ������Կָ�룬��128bit(16byte)  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_R2R_DECRYPT The R2R decryption fails CNcomment:HI_ERR_CA_R2R_DECRYPT  R2R����ʧ�� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

/**
\brief Sets session keys for a DVB key ladder CNcomment:ΪDVB key ladder���ûỰ��Կ    CNend
\attention \n
The stage of the session key cannot be greater than the configured stage of the key ladder. The last stage of the session key is configured by calling the API of the CIPHER module rather than this API.
That is, only session key 1 and session key 2 need to be configured for a 3-stage key ladder.
Only session key 1 needs to be configured for a 2-stage key ladder.
You need to set the key ladder stage by calling HI_UNF_ADVCA_SetDVBKeyLadderStage first.
 Session keys can be set during initialization or changed at any time.
CNcomment:ע�����õļ������ܳ������õļ���ֵ�����һ����Descramblerģ���ڲ����ã�����ͨ���˽ӿ����á�\n
Ҳ����˵������3��key ladder��ֻ�����ûỰ��Կ1�ͻỰ��Կ2��\n
����2����key ladder��ֻ�����ûỰ��Կ1��\n
���ȵ���HI_UNF_ADVCA_SetDVBKeyLadderStage����key ladder������\n
�Ự��Կ���Գ�ʼʱ����һ�Σ�Ҳ������ʱ�޸ġ� CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage    ��Կ������[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]  CNend
\param[in] pu8Key Protection key pointer, 128 bits (16 bytes) in total CNcomment:pu8Key     ������Կָ�룬��128bit(16byte)  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_R2R_DECRYPT The CW decryption fails CNcomment:HI_ERR_CA_CW_DECRYPT   CW����ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetDVBSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

/**
\brief Sets session keys for a CSA3 key ladder CNcomment:ΪCSA3 key ladder���ûỰ��Կ    CNend
\attention \n
The stage of the session key cannot be greater than the configured stage of the key ladder. The last stage of the session key is configured by calling the API of the CIPHER module rather than this API.
That is, only session key 1 and session key 2 need to be configured for a 3-stage key ladder.
Only session key 1 needs to be configured for a 2-stage key ladder.
You need to set the key ladder stage by calling HI_UNF_ADVCA_SetDVBKeyLadderStage first.
 Session keys can be set during initialization or changed at any time.
CNcomment:ע�����õļ������ܳ������õļ���ֵ�����һ����Descramblerģ���ڲ����ã�����ͨ���˽ӿ����á�\n
Ҳ����˵������3��key ladder��ֻ�����ûỰ��Կ1�ͻỰ��Կ2��\n
����2����key ladder��ֻ�����ûỰ��Կ1��\n
���ȵ���HI_UNF_ADVCA_SetDVBKeyLadderStage����key ladder������\n
�Ự��Կ���Գ�ʼʱ����һ�Σ�Ҳ������ʱ�޸ġ� CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage    ��Կ������[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]  CNend
\param[in] pu8Key Protection key pointer, 128 bits (16 bytes) in total CNcomment:pu8Key     ������Կָ�룬��128bit(16byte)  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_R2R_DECRYPT The CW decryption fails CNcomment:HI_ERR_CA_CW_DECRYPT   CW����ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetCSA3SessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

/**
\brief Set widevine keyladder session key CNcomment:����widevine keyladder�ĸ���������Կ CNend
\param[in]  enLevel keyladder level for input CNcomment:enLevel ������Կ�ļ��� CNend
\param[in]  hCipherHandle cipher handle input when level 3 CNcomment:hCipherHandle ���������������ʱ����Ҫ����Ԥ�ȴ����õ�Cipher�ľ�� CNend
\param[in]  pu8Input input data for keyladder CNcomment:pu8Input  keyladder���������� CNend
\param[in]  u32InputLen input data length CNcomment:u32InputLen ���ݵĳ��� CNend
\param[out] pu32GdrmFlag the flag value when level 3 CNcomment:pu32GdrmFlag  ���������������Կʱ�������GDRM��־  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS               �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT       CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA   ��������Ƿ� CNend
\retval ::HI_ERR_CA_NOT_SUPPORT The function is not supported CNcomment:HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧�� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ CNend
\return ::HI_ERR_CA_SWPK_ENCRYPT SWPK encryption fails CNcomment:HI_ERR_CA_SWPK_ENCRYPT   SWPK����ʧ�� CNend
\see
\li ::
*/
HI_S32 HI_UNF_ADVCA_SetGDRMSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,
                                    HI_HANDLE hCipherHandle,
                                    HI_U8 *pu8Input,
                                    HI_U32 u32InputLen,
                                    HI_U32 *pu32GdrmFlag);


/**
\brief Encrypts software protect keys (SWPKs) CNcomment:�������������Կ CNend
\attention
Before the delivery of the STB, you need to read the SWPKs in plain text format from the flash memory, encrypt SWPKs by calling this API, and store the encrypted SWPKs in the flash memory for security startup.
CNcomment:�����г���ʱ ��Flash�϶�ȡ���ĵ�SWPK(Software Protect Key),���øýӿڼ���,�����ܵ�SWPK�洢��Flash�У����ڰ�ȫ���� CNend
The fist 8 bytes of the SWPK can't be equal to the last 8 bytes.
CNcomment:SWPK��ǰ8���ֽ����8���ֽڲ������ CNend
This API is only for special CA, please contact Hislicon before usage.
CNcomment:ע��:�˽ӿ�Ϊ�ض�CAר�ã�����ʹ�ã�����ϵ��˼ CNend
\param[in]  pPlainSwpk SWPKs in plain text format CNcomment:pPlainSwpk    ����SWPK  CNend
\param[out] pEncryptedSwpk Encrypted SWPKs CNcomment:pEncryptedSwpk  ���ܺ��SWPK  CNend

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS               �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT       CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA   ��������Ƿ� CNend
\retval ::HI_ERR_CA_NOT_SUPPORT The function is not supported CNcomment:HI_ERR_CA_NOT_SUPPORT    ���ܲ�֧�� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT   CA�ȴ��ӽ��ܳ�ʱ CNend
\return ::HI_ERR_CA_SWPK_ENCRYPT SWPK encryption fails CNcomment:HI_ERR_CA_SWPK_ENCRYPT   SWPK����ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EncryptSWPK(HI_U8 *pPlainSwpk,HI_U8 *pEncryptedSwpk);

/**
\brief Sets the algorithm of the DVB key ladder CNcomment:����DVB key ladder���㷨    CNend
\attention \n
You must set an algorithm before using a key ladder in a session. The default algorithm is TDES.
It is recommended that you retain the algorithm in a session.
CNcomment:ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_ALG_TYPE_TDES��\n
���λỰ�����У����鱣���㷨���ȶ����䡣 CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief Sets the algorithm of the CSA2 key ladder CNcomment:����CSA3 key ladder���㷨    CNend
\attention \n
You must set an algorithm before using a key ladder in a session. The default algorithm is TDES.
It is recommended that you retain the algorithm in a session.
CNcomment:ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_ALG_TYPE_TDES��\n
���λỰ�����У����鱣���㷨���ȶ����䡣 CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetCSA3Alg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief Sets the algorithm of the R2R key ladder CNcomment:����R2R key ladder���㷨    CNend
\attention \n
You must set an algorithm before using a key ladder in a session. The default algorithm is TDES.
It is recommended that you retain the algorithm in a session.
CNcomment:ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_ALG_TYPE_TDES��\n
���λỰ�����У����鱣���㷨���ȶ����䡣 CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief Obtains the algorithm of the DVB key ladder CNcomment: ��ȡ DVB key ladder���㷨    CNend
\attention \n
None CNcomment:�� CNend
\param[in] pEnType Key ladder algorithm CNcomment:pEnType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetDVBAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
\brief Obtains the algorithm of the R2R key ladder CNcomment:��ȡ R2R key ladder���㷨    CNend
\attention \n
None CNcomment:�� CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
  \brief set RSA key CNcomment:����ǩ��У���RSA��Կ CNeng
  \attention \n
  If the mass-produced chipset have been set RSA Key by CA, there's no need to use this API to set RSA Key again.
  This API can been called only once, please be careful, after setting RSA key, you should lock it by call API
  HI_UNF_ADVCA_ConfigLockFlag.The length of RSA key must be 512 Bytes.
  CNcomment:�������оƬ�Ѿ�����CA��˾����RSAKey,�������ٴ�ʹ�øýӿ�����RSAKey\n
     �ýӿ�ֻ�������һ�Σ������ظ�����,�����ʹ�øýӿ�,�������ú�RSAKey����Ҫʹ�ýӿ�\n
     HI_UNF_ADVCA_ConfigLockFlag���������� RSA key�ĳ��ȱ���Ϊ512 Bytes  CNend
  \param[in] pkey RSA key CNcomment:pkey  RSA��Կ\n  CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetRSAKey(HI_U8 *pkey);

/**
  \brief set RSA key CNcomment:��ȡǩ��У���RSA��Կ CNend
  \attention \n
     RSA key can be read out when only the RSAKey is not locked,The length of RSA key is 512 Bytes.
     RSA key should have been setting and lock before chipset is delivered to STB Manufacture.
     Please contact Hisilicon before Customer try to use this interface.
  CNcomment:�ýӿڽ���RSAkeyû�б�����������£���ȡ����, RSA key�ĳ���Ϊ512 Bytes\n
     RSA key�����Ѱ���CA��˾Ҫ�����ò��������ýӿ�����ͻ���Ҫʹ�øýӿ���Ҫ��֪ͨ��˼\n  CNend
  \param[in] pkey RSA key CNcomment:pkey  RSA�ܹ�Կ\n  CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetRSAKey(HI_U8 *pkey);

/**
  \brief set RSA key CNcomment:��ȡǩ��У���RSA���� CNend
  \attention \n
    This API is used to lock RSA KEY/Trustzone OTP\misc keyladder etc.Please contact Hisilicon before Customer try to use this interface.
  CNcomment:�ýӿ���������RSAkey\Trustzone OTP\misc keyladder�ȣ��ýӿ�����ͻ���Ҫʹ�øýӿ���Ҫ��֪ͨ��˼\n  CNend
  \param[enType] enType the type you want to lock.  CNcomment:enType  ��Ҫ����������\n  CNend
  \param[pu8ParamIn] pu8ParamIn reserved, default is null. CNcomment:pu8ParamIn  Ԥ����Ĭ��Ϊnull\n  CNend
  \param[u32ParamLen] u32ParamLen reserved, default is 0. CNcomment:u32ParamLen  Ԥ����Ĭ��Ϊ0\n  CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_ConfigLockFlag(HI_UNF_ADVCA_LOCK_TYPE_E enType, HI_U8 *pu8ParamIn, HI_U32 u32ParamLen);


/**
  \brief This function is used to check if the MarketID is already set
  \attention \n
  None
  \param[in] pbIsMarketIdSet: the pointer point to the buffer to store the return value
  \param[out] pbIsMarketIdSet: save the return value
  \retval ::HI_SUCCESS Success
  \retval ::HI_FAILURE This API fails to be called
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_IsMarketIdSet(HI_BOOL *pbIsMarketIdSet);

/**
  \brief This function is used to get the vendor type of the chipset
  \attention \n
  None
  \param[out] pu32VendorID: The number indicates the vendor id
  \retval ::HI_SUCCESS Success
  \retval ::HI_FAILURE This API fails to be called
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetVendorID(HI_U32 *pu32VendorID);

/**
\brief Enables the security startup function and sets the type of flash memory for security startup
CNcomment:���ð�ȫ����ʹ��,ͬʱָ����ȫ������Flash���� CNend
\attention \n
This function can be enabled only and cannot be disabled after being enabled.
CNcomment:ֻ��ʹ�ܣ�ʹ��֮�󲻿��޸ġ� CNend
\param[in]  enFlashType Type of the flash memory for security startup CNcomment:enFlashType  ������Flash���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EnableSecBoot(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType);

/**
\brief Enables the security startup function. This API should be used with the API HI_UNF_ADVCA_SetFlashTypeEx.
CNcomment:���ð�ȫ����ʹ�ܣ��ýӿڱ����HI_UNF_ADVCA_SetFlashTypeEx����ʹ�á� CNend
\attention \n
\param[in]  None
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EnableSecBootEx(HI_VOID);

/**
\brief Sets the type of flash memory for security startup and disable the self boot, which mean that you cannot use the serial port to update the boot. This API should be used with the API HI_UNF_ADVCA_EnableSecBootEx
CNcomment:ָ����ȫ������Flash���ͣ�ͬʱ�ر��Ծٹ��ܣ�������ͨ����������fastboot���ýӿڸ�HI_UNF_ADVCA_EnableSecBootEx����ʹ�� CNend
\attention \n
The setting is performed before delivery and can be performed once only.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ�� CNend
\param[in]  enFlashType Type of the flash memory for security startup CNcomment:enFlashType  ������Flash���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetFlashTypeEx(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType);

/**
\brief  Sets whether to use hardware CWs only CNcomment:���ù̶�ʹ��Ӳ��CW�� CNend
\attention
The setting is performed before delivery and can be performed once only.
By default, the CW type (hardware CWs or software CWs) depends on the configuration of the DEMUX.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϸ���Demux������ѡ��ʹ��Ӳ��CW�ֻ������CW�� CNend
\param  none
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_LockHardCwSel(HI_VOID);

/**
\brief Disables the self-boot function CNcomment:�ر�SelfBoot����,Ҳ����boot�²���ʹ�ô���/�������� CNend
\attention
The setting is performed before delivery and can be performed once only.
The self-boot function is enabled by default.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ��ʹ��SelfBoot���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized.  CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DisableSelfBoot(HI_VOID);

/**
\brief Obtains the self-boot status CNcomment:��ȡSelfBoot״̬ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pbDisable: self-boot status. CNcomment:pbEnable   SelfBoot�Ƿ���� CNend
HI_TRUE enabled CNcomment:HI_TRUE ���ã�  CNend
HI_FALSE disabled CNcomment:HI_FALSE δ���� CNend

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetSelfBootStat(HI_BOOL *pbDisable);

/**
\brief  Get whether to use hardware CWs only CNcomment:��ȡ�̶�ʹ��Ӳ��CW�ֱ�־ CNend
\attention
None CNcomment:�� CNend
\param[out] pbLock indicates the state of hardware CWs  CNcomment:pbLock Ӳ��CW�ֵı�־λ CNend

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetHardCwSelStat(HI_BOOL *pbLock);

/**
\brief  Open the SWPK key ladder CNcomment:��boot key ladder  CNend
\attention
\param  none

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SWPKKeyLadderOpen(HI_VOID);

/**
\brief  Close the SWPK key ladder CNcomment:�ر�boot key ladder  CNend
\attention
\param  none

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SWPKKeyLadderClose(HI_VOID);

/**
\brief Obtains the Version ID CNcomment:��ȡVersion ID  CNend
\attention \n
None CNcomment:�� CNend
\param[out] u8VersionId version ID CNcomment:u8VersionId   �汾�ű�־ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_SetVersionId
*/
HI_S32 HI_UNF_ADVCA_GetVersionId(HI_U8 u8VersionId[4]);

/**
\brief Sets the Version ID CNcomment:����Version ID  CNend
\attention \n
The version ID of the set-top box (STB) is set before delivery. The version ID can be set once only and takes effects after the STB restarts.
CNcomment:�ڻ����г���ʱ���ã���֧������һ�� ���ú�������Ч CNend
\param[in] u8VersionId version ID CNcomment:u8VersionId   �汾�ű�־ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN  �ظ����� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetVersionId(HI_U8 u8VersionId[4]);

/**
\brief  Sets whether to check the boot version CNcomment:�����Ƿ���Version  CNend
\attention
The setting is performed before delivery and can be performed once only.
By default, the version check function is disabled
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϲ�ʹ��version check  CNend
\param  none
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EnableVersionCheck(HI_VOID);

/**
\brief  Get the boot version check flag CNcomment:��ȡ�Ƿ���version�ı�־λ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu32Stat boot version check flag CNcomment:pu32Stat    version���ı�־λ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetVersionCheckStat(HI_U32 *pu32Stat);

/**
\brief  Sets whether to check the MSID in boot area CNcomment:�����Ƿ���boot area��MSID  CNend
\attention
The setting is performed before delivery and can be performed once only.
By default, the boot MSID check function is disabled
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϲ�ʹ��boot MSID check  CNend
\param none
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_EnableBootMSIDCheck(HI_VOID);

/**
\brief  Get the boot MSID check flag CNcomment:��ȡ�Ƿ���MSID�ı�־λ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu32Stat boot MSID check flag CNcomment:pu32Stat    MSID���ı�־λ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetBootMSIDCheckStat(HI_U32 *pu32Stat);

/**
\brief  Get the software revision
CNcomment:��ȡ�����revision�汾�� CNend
\attention \n
None CNcomment:�� CNend
\param[out] revision string of Revision CNcomment:revision    Revision�汾�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetRevision(HI_U8 revision[25]);

/**
\brief  Set the DDR Scramble flag. Normally, this flag has been set as required by CA vendor
CNcomment:����DDR���ű�־λ��һ��߰�оƬ����ʱ�Ѱ���CA��˾Ҫ������ CNend
\attention \n
None CNcomment:�� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetDDRScramble(HI_VOID);

/**
\brief  Get the DDR Scramble flag
CNcomment:��ȡDDR���ű�־λ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu32Stat DDR Scramble flag CNcomment:pu32Stat    DDR���ű�־ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetDDRScrambleStat(HI_U32 *pu32Stat);

/**
\brief Sets whether to decrypt the BootLoader CNcomment:���ñ����BootLoader���н��� CNend
\attention
The setting is performed before delivery and can be performed once only.
CNcomment:�ڻ����г���ʱѡ���Ƿ����ã���֧������һ��
Ĭ�ϸ���Flash�е����ݱ�ʶ������BootLoader�Ƿ���Ҫ���� CNend

\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS                  �ɹ� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT          CAδ��ʼ�� CNend
\return ::HI_ERR_CA_SETPARAM_AGAIN The parameter has been set CNcomment:HI_ERR_CA_SETPARAM_AGAIN    �ظ����ò��� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_LockBootDecEn(HI_VOID);

/**
\brief Get the BootLoader Decryption flag CNcomment:��ȡBootLoader���ܵı�־λ CNend
\attention \n
None CNcomment:�� CNend
\param[out] pu32Stat BootLoader Decryption flag CNcomment:pu32Stat    Bootloader���ܱ�־λ CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized CNcomment:HI_ERR_CA_NOT_INIT  CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA  ��������Ƿ� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetBootDecEnStat(HI_U32 *pu32Stat);





/**
\brief  Calculte the AES_CMAC value of data
CNcomment: �������ݵ�AES_CMAC ֵ CNend
\attention \n
None CNcomment:�� CNend

\param[in]  buffer  pointer of data buffer .        CNcomment:����buffer ָ�� CNend
\param[in]  Length  The length  of data .   CNcomment:���ݳ��� CNend
\param[in]  Key   The key used in Calculte the AES_CMAC of data           CNcomment: AES_CMAC ������ʹ�õ�key  CNend
\param[out]  MAC   The AES_CMAC value          CNcomment:AES_CMAC ֵ CNend

\retval ::HI_SUCCESS  Success                 CNcomment:�ɹ� CNend
\retval ::HI_FAILURE    Failure                     CNcomment:ʧ�� CNend
\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_CalculteAES_CMAC(HI_U8 *buffer, HI_U32 Length, HI_U8 Key[16], HI_U8 MAC[16]);



/**
\brief Sets the algorithm of the SP key ladder CNcomment:����SP key ladder���㷨    CNend
\attention \n
You must set an algorithm before using a key ladder in a session. The default algorithm is TDES.
It is recommended that you retain the algorithm in a session.
CNcomment:ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_ALG_TYPE_TDES��\n
���λỰ�����У����鱣���㷨���ȶ����䡣 CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetSPAlg(HI_UNF_ADVCA_ALG_TYPE_E enType);

/**
\brief Obtains the algorithm of the SP key ladder CNcomment: ��ȡ SP key ladder���㷨    CNend
\attention \n
None CNcomment:�� CNend
\param[in] pEnType Key ladder algorithm CNcomment:pEnType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetSPAlg(HI_UNF_ADVCA_ALG_TYPE_E *pEnType);

/**
\brief Sets the SP key ladder stage CNcomment:����SP key ladder�ļ���    CNend
\attention \n
The key ladder stage can be set only once before delivery and cannot be changed. Please use default value.
CNcomment:�����г���ʱ���� ��������һ�� ���ɸ���,������ʹ�øýӿڸı�stage  CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage  key ladder����\n ȡֵֻ��ΪHI_UNF_ADVCA_KEYLADDER_lev2 ���� HI_UNF_ADVCA_KEYLADDER_lev3  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_SetSPKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage);

/**
\brief Obtains the SP key ladder stage CNcomment:��ȡSP key ladder�ļ��� CNend
\attention \n
None CNcomment:�� CNend
\param[out] penStage Key ladder stage CNcomment:penStage   key ladder���� CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_KEYLADDER_LEV_E
*/
HI_S32 HI_UNF_ADVCA_GetSPKeyLadderStage(HI_UNF_ADVCA_KEYLADDER_LEV_E *penStage);


/**
\brief Sets session keys for a SP key ladder CNcomment:ΪSP key ladder���ûỰ��Կ    CNend
\attention \n
The stage of the session key cannot be greater than the configured stage of the key ladder. The last stage of the session key is configured by calling the API of the CIPHER module rather than this API.
That is, only session key 1 and session key 2 need to be configured for a 3-stage key ladder.
Only session key 1 needs to be configured for a 2-stage key ladder.
You need to set the key ladder stage by calling HI_UNF_ADVCA_SetSPKeyLadderStage first.
 Session keys can be set during initialization or changed at any time.
CNcomment:ע�����õļ������ܳ������õļ���ֵ�����һ����Descramblerģ���ڲ����ã�����ͨ���˽ӿ����á�\n
Ҳ����˵������3��key ladder��ֻ�����ûỰ��Կ1�ͻỰ��Կ2��\n
����2����key ladder��ֻ�����ûỰ��Կ1��\n
���ȵ���HI_UNF_ADVCA_SetSPKeyLadderStage����key ladder������\n
�Ự��Կ���Գ�ʼʱ����һ�Σ�Ҳ������ʱ�޸ġ� CNend
\param[in] enStage Key ladder stage Its value is HI_UNF_ADVCA_KEYLADDER_LEV2 or HI_UNF_ADVCA_KEYLADDER_LEV3.
CNcomment:enStage    ��Կ������[HI_UNF_ADVCA_KEYLADDER_LEV1 ~ HI_UNF_ADVCA_KEYLADDER_LEV2]  CNend
\param[in] pu8Key Protection key pointer, 128 bits (16 bytes) in total CNcomment:pu8Key     ������Կָ�룬��128bit(16byte)  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_WAIT_TIMEOUT Timeout occurs when the CA module waits for encryption or decryption
CNcomment:HI_ERR_CA_WAIT_TIMEOUT CA�ȴ��ӽ��ܳ�ʱ CNend
\retval ::HI_ERR_CA_R2R_DECRYPT The CW decryption fails CNcomment:HI_ERR_CA_CW_DECRYPT   CW����ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetSPSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key);

/**
\brief Sets the descramble mode of the SP key ladder CNcomment:����SP key ladder�Ľ����㷨    CNend
\attention \n
You must set a descramble mode before using a key ladder in a session. The default algorithm is HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_CI.
It is recommended that you retain the descramble mode in a session.
CNcomment:ÿ�λỰ������ʹ��key ladder֮ǰ�������þ����㷨, ϵͳ��ʼĬ��ֵ HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_CI��\n
���λỰ�����У����鱣���㷨���ȶ����䡣 CNend
\param[in] enType Key ladder algorithm CNcomment:enType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_SetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E enType);

/**
\brief Obtains the descramble mode of the SP key ladder CNcomment: ��ȡ SP key ladder���㷨    CNend
\attention \n
None CNcomment:�� CNend
\param[in] pEnType Key ladder algorithm CNcomment:pEnType  key ladder�㷨\n  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\see \n
::HI_UNF_ADVCA_ALG_TYPE_E
*/
HI_S32 HI_UNF_ADVCA_GetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E *pEnType);

/**
  \brief this function is used by the Novel CA for the encryption and decryption setting
   CNcomment:Novel�ڴ�ӽ����㷨��key���� CNend
  \attention \n
  This function is used for the Novel encryption and decrption
  CNcomment:  ���������ṩ�� Novel �ڴ�ӽ��ܷ���ʹ�ã��������üӽ��ܹ���keyladder�㷨��key CNend
  \retval ::HI_SUCCESS Success  CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called  CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_NovelCryptologyConfig(HI_VOID);

/**
  \brief Used for Novel CA to encrypt the data  CNcomment:Novel�ڴ����ݼ��� CNend
  \attention \n
  None  CNcomment: �� CNend
  \param[in]  pPlainText: the buffer to store the data to be encrypted CNcomment:pPlainText ����������ָ�� CNend
  \param[in]  TextLen: the length of the data to be encrypted CNcomment:TextLen    ���������ݳ��� CNend
  \param[in]  pCipherText: the buffer to store the encrypted data CNcomment:pCipherText ���ܺ�����ָ�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_NovelDataEncrypt(HI_U8 *pPlainText, HI_U32 TextLen, HI_U8 *pCipherText);

/**
  \brief This function is used for Novel to decrypt the data CNcomment:TextNovel�ڴ����ݽ��� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  pPlainText: point to the data to be decrypted CNcomment:pPlainText ������������ָ�� CNend
  \param[in]  TextLen: the length of the data to be decrypted CNcomment:TextLen    ���������ݳ��� CNend
  \param[in]  pCipherText: the buffer store the decrypted data CNcomment:pCipherText ���ܺ�����ָ�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_NovelDataDecrypt(HI_U8 *pCipherText, HI_U32 TextLen, HI_U8 *pPlainText);

/**
\brief Sets oem root key�� it's mainly used for widevine keyladder CNcomment:OEM_root_key ��Ҫ����Widevine keyladder    CNend
\attention \n
This root key could only be written only once be careful, thanks    CNcomment: �����Կֻ����дһ��,��������� CNend
\param[in] pu8OEMRootKey buffer of the input key    CNcomment:pu8OEMRootKey    ������Կ��buffer  CNend
\param[in] u32KeyLen key length of the input CNcomment:u32KeyLen     ������Կ�ĳ��ȣ��޶�Ϊ16�ֽ�  CNend
\retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
\retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
\retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
\retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
\retval ::HI_ERR_CA_R2R_DECRYPT The CW decryption fails CNcomment:HI_ERR_CA_CW_DECRYPT   CW����ʧ�� CNend

\see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetOEMRootKey(HI_U8 *pu8OEMRootKey, HI_U32 u32KeyLen);

/**
  \brief This function is used to open the DCAS CNcomment:���ڴ�DCAS CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enAlg: DCAS keyladder algorithm CNcomment:enAlg DCAS keyladder�㷨 CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DCASOpen(HI_UNF_CIPHER_ALG_E enAlg);

/**
  \brief This function is used to get the DCAS CHIPID CNcomment:���ڻ�ȡDCAS CHIPID
  \attention \n
  None  CNcomment:�� CNend
  \param[out]  pu32MSBID: First 4 bytes of DCAS CHIPID CNcomment:DCAS CHIPIDǰ4���ֽ� CNend
  \param[out]  pu32LSBID: last 4 bytes of DCAS CHIPID CNcomment:DCAS CHIPID��4���ֽ� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetDCASChipId(HI_U32 *pu32MSBID, HI_U32 *pu32LSBID);

/**
  \brief This function is used to set the session key CNcomment:��������DCAS session��Կ CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enDCASLevel: the DCAS keyladder level CNcomment:enAlg DCAS keyladder���� CNend
  \param[in]  pu8Key: the DCAS keyladder session key CNcomment:enAlg DCAS keyladder��Կ CNend
  \param[in]  pu8Output: the output of the DCAS keyladder CNcomment:pu8Output DCAS keyladder��� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetDCASSessionKey(HI_UNF_ADVCA_DCAS_KEYLADDER_LEV_E enDCASLevel, HI_U8 au8Key[16], HI_U8 au8Output[16]);

/**
  \brief This function is used to close the DCAS keyladder CNcomment:���ڹر�DCAS CNend
  \attention \n
  None  CNcomment:�� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \see  \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_DCASClose(HI_VOID);

/**
  \brief This function is used to set the OTP fuse. CNcomment:��������OTPλ CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enOtpFuse: the OTP fuse ID CNcomment:enOtpFuse �����õ�OTPλID CNend
  \param[in]  pstOtpFuseAttr: the OTP fuse attribute CNcomment:pstOtpFuseAttr �����õ�OTPλ���� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetOtpFuse(HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse, HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr);

/**
  \brief This function is used to get the OTP fuse. CNcomment:���ڻ�ȡOTPλ CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enOtpFuse: the OTP fuse ID CNcomment:enOtpFuse ����ȡ��OTPλID CNend
  \param[in]  pstOtpFuseAttr: the OTP fuse attribute CNcomment:pstOtpFuseAttr ��ȡ��OTPλ���� CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_GetOtpFuse(HI_UNF_ADVCA_OTP_FUSE_E enOtpFuse, HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr);

/**
  \brief This function is used to set the keyladder attribute. CNcomment:��������keyladder���� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enKeyLadderType: The keyladder type ID CNcomment:enKeyLadderType Keyladder����ID CNend
  \param[in]  pstKeyladderAttr: The keyladder attribute CNcomment:pstKeyladderAttr �����õ�keyladder����CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_SetKeyLadderAttr(HI_UNF_ADVCA_KEYLADDER_TYPE_E enKeyLadderType, HI_UNF_ADVCA_KEYLADDER_ATTR_S *pstKeyladderAttr);

/**
  \brief This function is used to achieve the CA vendor privated function. CNcomment:�������CA�������еĲ��� CNend
  \attention \n
  None  CNcomment:�� CNend
  \param[in]  enCaVendor: The CA vendor type ID CNcomment:enCaVendor CA vendor����ID CNend
  \param[in]  pstCavendorOpt: The parameter to achieve the CA vendor private function CNcomment:pstCavendorOpt ���CA�������й�����Ҫ�Ĳ���CNend
  \retval ::HI_SUCCESS Success CNcomment:HI_SUCCESS  �ɹ� CNend
  \retval ::HI_FAILURE This API fails to be called CNcomment:HI_FAILURE  APIϵͳ����ʧ�� CNend
  \retval ::HI_ERR_CA_NOT_INIT The advanced CA module is not initialized. CNcomment:HI_ERR_CA_NOT_INIT CAδ��ʼ�� CNend
  \retval ::HI_ERR_CA_INVALID_PARA The input parameter value is invalid CNcomment:HI_ERR_CA_INVALID_PARA ��������Ƿ� CNend
  \see \n
None CNcomment:�� CNend
*/
HI_S32 HI_UNF_ADVCA_CaVendorOperation(HI_UNF_ADVCA_VENDORID_E enCaVendor, HI_UNF_ADVCA_CA_VENDOR_OPT_S *pstCaVendorOpt);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_ADVCA_H__ */


