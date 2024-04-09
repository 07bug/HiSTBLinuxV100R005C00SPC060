/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : unf_cipher.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "hi_unf_hdcp.h"
#include "hi_common.h"
#include "mpi_cipher.h"

/*************************** Internal Structure Definition ******************/
/** \addtogroup      hdcp */
/** @{*/  /** <!-- [mpi]*/


/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      hdcp */
/** @{*/  /** <!-- [mpi]*/

#define HDCP_KEY_RAM_LONG_SIZE    (512)

#define CRC32_P32           0xEDB88320L
#define CRC32_TABLE_LEN     256
#define BYTE_BITS           8
#define BYTE_MASK           0xFF
#define HDCP_KEY_FLAG_MASK  0xC0
#define HDCP_KEY_FLAG_OTP   0x00
#define HDCP_KEY_FLAG_HISI  0x80
#define HDCP_ROOT_KEY_SIZE  16

#define  HDCP_KEY_RAM_SIZE                      320
#define  HDCP_KEY_TOOL_FILE_SIZE                384
#define  HDCP_KEY_CHIP_FILE_SIZE               (HDCP_KEY_RAM_SIZE + 12)
#define  HDCP22_KEY_HEAD_SIZE                   40
#define  HDCP22_KEY_PRIM_SIZE                   864
#define  HDCP22_KEY_TOOL_FILE_SIZE              904
#define  HDCP22_KEY_RAM_SIZE                    1024
#define  HDCP22_KEY_CHIP_FILE_SIZE              1028

#define HI_ERR_HDCP(fmt...)                HI_ERR_PRINT(HI_ID_HDCP, fmt)
#define HI_INFO_HDCP(fmt...)               HI_INFO_PRINT(HI_ID_HDCP, fmt)
extern HI_U32 CHECK_CIPHER_HDCP_OPEN();
static HI_S32 crc32_tab_init = 0;
static HI_U32 crc_tab32[CRC32_TABLE_LEN];

static HI_VOID mpi_crc32_tab_init( HI_VOID )
{
    HI_U32 i,j;
    HI_U32 crc32;

    for (i=0; i<CRC32_TABLE_LEN; i++)
    {
        crc32 = i;
        for (j=0; j<BYTE_BITS; j++)
        {
            if (crc32 & 0x00000001L)
            {
                crc32 = (crc32 >> 1) ^ CRC32_P32;
            }
            else
            {
                crc32 = crc32 >> 1;
            }
        }
        crc_tab32[i] = crc32;
    }

    crc32_tab_init = HI_TRUE;

}

static HI_U32 mpi_update_crc32(HI_U32 crc32, HI_U8 s8C)
{
    HI_U32 tmp;

    tmp = crc32 ^ (HI_U32)s8C;
    crc32 = (crc32 >> BYTE_BITS) ^ crc_tab32[tmp & BYTE_MASK];
    return crc32;
}

static HI_S32 mpi_hdcp_crc32( HI_U8 *buffer, HI_U32 length, HI_U32 *crc32)
{
    HI_U32 i;

    if (!crc32_tab_init)
    {
        mpi_crc32_tab_init();
    }

    *crc32 = 0xffffffffL;

    for(i=0 ; i < length ; i++)
    {
        *crc32 = mpi_update_crc32(*crc32, (char)buffer[i]);
    }

    *crc32 ^= 0xffffffffL;

    return HI_SUCCESS;
}

/* The final encrypt data structure is as below:
    head              HDMIIP_HDCPKey                 CRC32_0 CRC32_1
  |-------|-----------------------------------------|------|------|
  |4bytes-|-----------------Encrypt(320bytes)-------|-4byte|-4byte|

  total: 332

  Head: 4 byte
  B0[7..6] key type, 00: otp root key
  B1: 0x00
  B2~B3: HI
  B4~B324:   HDCPKey, 320 byte
  B325~B328: CRC32_0, CRC32 of HDCP key before encrypted
  B329~B331: CRC32_1, CRC32 of Head+HDCPKey+CRC32_0
*/
static HI_S32 mpi_hdcp_load_key(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, u8 *in)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 crc32 = 0;
    HI_U8  *hdcpkey = HI_NULL;

    /* verify crc32_1 */
    ret = mpi_hdcp_crc32(in, (HDCP_KEY_CHIP_FILE_SIZE - 4), &crc32);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("HDCP KEY CRC32_1 calc failed!\n");
        return HI_FAILURE;
    }
    if ( memcmp(&crc32, &in[HDCP_KEY_CHIP_FILE_SIZE - 4], 4) != 0 )
    {
        HI_ERR_HDCP("HDCP KEY CRC32_1 compare failed!");
        return HI_FAILURE;
    }
    hdcpkey = in + 4;

    ret = mpi_hdcp_operation(keysel, ramsel, HI_NULL, hdcpkey,
        HI_NULL, HDCP_KEY_RAM_SIZE, SYMC_OPERATION_DECRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("HDCP key decrypt final failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/* The 320 Byte of HDCP key structure is as below:
  B0: 0x00
  B1~B5: KSV
  B6~B7: CRC16 of HDCPKey, not include B6~B8.
  B8: 0xa8
  B9~B288: Device Private Key
  B289~B319: filled to 0x14, 0xf7, 0x61, 0x03, 0xb7, 0x59, 0x45, 0xe3, 0x0c,
    0x7d, 0xb4, 0x45, 0x19, 0xea, 0x8f, 0xd2,0x89, 0xee, 0xbd, 0x90, 0x21, 0x8b,
    0x05, 0xe0,0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
*/
static HI_VOID mpi_hdcp_format_key(HI_U8 *ksv, HI_U8 *private_key, HI_U8 *out) //HDCP_KEY_RAM_SIZE
{
    HI_S32 i;
    HI_U8 TailBytes[31] = {0x14, 0xf7, 0x61, 0x03, 0xb7, 0x59, 0x45, 0xe3,
                           0x0c, 0x7d, 0xb4, 0x45, 0x19, 0xea, 0x8f, 0xd2,
                           0x89, 0xee, 0xbd, 0x90, 0x21, 0x8b, 0x05, 0xe0,
                           0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    HI_U32 checkout = 0xa3c5;
    HI_U32 xorvalue = 0x0, tmp = 0x0;

    memset(out, 0, HDCP_KEY_RAM_SIZE);

    /* Byte 0*/
    out[0] = 0x00;

    /* Byte 1 ~ 5 KSV */
    for (i = 0; i < 5; i ++)
    {
        out[1 + i] = ksv[i];
    }

    /* Byte 8 */
    out[8] = 0xa8;
    /* Byte 9 ~ 288 Device Private Key */
    for (i = 0; i < 280; i ++)
    {
        out[9 + i] = private_key[i];
    }

    /* Byte 289 ~ 319 */
    for (i = 0; i < 31; i ++)
    {
        out[289 + i] = TailBytes[i];
    }

    /* Count CRC value */
    for(i=0; i<320; i++)
    {
        if((i>=6) && (i<=8))
        {
            continue;
        }
        xorvalue = checkout ^ out[i];
        tmp = ~((xorvalue >> 7) ^ (xorvalue >> 16));
        xorvalue = xorvalue << 1;
        xorvalue = (xorvalue & 0x1fffe) | (tmp & 1);
        checkout = xorvalue;
    }

    for(i=0; i<8; i++)
    {
        xorvalue = checkout;
        tmp = ~((xorvalue >> 7) ^ (xorvalue >> 16));
        xorvalue = xorvalue << 1;
        xorvalue = (xorvalue & 0x1fffe) | (tmp & 1);
        checkout = xorvalue;
    }

    /* Byte 6 && 7  CRC Value */
    out[6] = checkout & 0xff;
    out[7] = (checkout >> 8) & 0xff;

    return;
}

/**********************************************************************
The Encrypted data structure is as below:
	0~7bytes: HISI_xxx      (8byte, Hisilicon magic number)
	8~15: V0000001          (8byte, tool version number)
	16~47: xxxxxxxx         (32bytes, Customer ID, don't need to care)
	48~367:                 320 bytes, encrypted HDCP key using AES-CBC with key
	368~384: 16bytes, reserved

The 320 bytes HDCP key data structure is as below:
    0~4:     KSV
    5~7:     resvred, 00 00 00
    8~287:   Device Private Key
    287~319: resvred
*/
static HI_S32 mpi_hdcp_decrypt_from_tool(HI_U8 *in,  HI_U8 *out, u8 *tool_key)
{
    HI_S32 ret = HI_FAILURE;
    HI_U8 *encrypt_key = NULL;
    HI_U8 *clean_key = NULL;
    HI_U8 hostkey[HDCP_ROOT_KEY_SIZE];

    encrypt_key = in;
    encrypt_key+=8; //Skip HISI_xxx
    if( memcmp("V0000001", encrypt_key, 8) != 0 )
    {
        HI_ERR_HDCP("EncryptKey check version failed\n");
        return HI_FAILURE;
    }
    encrypt_key+=8;  //Skip version number
    encrypt_key+=32; //Ship Customer ID

    clean_key = malloc(HDCP_KEY_RAM_SIZE);
    if (NULL == clean_key)
    {
        HI_ERR_HDCP("mallc buffer for clean hdcp key failed\n");
        return HI_FAILURE;
    }

    memset(hostkey, 0, HDCP_ROOT_KEY_SIZE);
    memcpy(hostkey, tool_key, HDCP_ROOT_KEY_SIZE);

    ret = mpi_hdcp_operation(HDCP_KEY_SEL_HOST, HDMI_RAM_SEL_NONE, hostkey,
        encrypt_key, clean_key, HDCP_KEY_RAM_SIZE, SYMC_OPERATION_DECRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("HDCP key decrypt final failed!\n");
        free(clean_key);
        clean_key = HI_NULL;
        memset(hostkey, 0, HDCP_ROOT_KEY_SIZE);
        return ret;
    }

    mpi_hdcp_format_key(&clean_key[0], &clean_key[8], out);
    memset(hostkey, 0, HDCP_ROOT_KEY_SIZE);

    free(clean_key);
    clean_key = HI_NULL;

    return HI_SUCCESS;
}

HI_S32 mpi_hdcp_encrypt_key(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, HI_U8 *in, HI_U8 *out, u8 *tool_key)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 index = 0;
    HI_U32 crc0 = 0, crc1 = 1;

    if ( NULL == in || NULL == out)
    {
        HI_ERR_HDCP("Invalid param, null pointer!\n");
        return HI_FAILURE;
    }
    memset(out, 0, HDCP_KEY_CHIP_FILE_SIZE);

    /* header config */
    out[index++] = (HDCP_KEY_SEL_OTP == keysel ? HDCP_KEY_FLAG_OTP : HDCP_KEY_FLAG_HISI);
    out[index++] = 0x00;
    /* 'H' 'I' display that the Encrypted Hdpcp Key Exists */
    out[index++] = 'H';
    out[index++] = 'I';

    /* format 320 byte hdcp key */
    ret = mpi_hdcp_decrypt_from_tool(in, &out[index], tool_key);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("mpi_hdcp_decrypt_from_tool failed!\n");
        return HI_FAILURE;
    }

    /* crc32_0 calculate */
    ret = mpi_hdcp_crc32(&out[index], HDCP_KEY_RAM_SIZE, &crc0);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("CRC32_0 calc failed!\n");
        return HI_FAILURE;
    }

    /* encrypt hdcp key by root key*/
    ret = mpi_hdcp_operation(keysel, ramsel, HI_NULL,
            &out[index], &out[index], HDCP_KEY_RAM_SIZE, SYMC_OPERATION_ENCRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("HDCP key decrypt final failed!\n");
        return HI_FAILURE;
    }

    /* write CRC32_0  */
    index += HDCP_KEY_RAM_SIZE;
    memcpy(&out[index], &crc0, 4);
    index += 4;

    /* CRC32_1  calculate */
    ret = mpi_hdcp_crc32(out, index, &crc1);
    if ( HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("CRC32_1 calc failed!\n");
        return HI_FAILURE;
    }
    memcpy(&out[index], &crc1, 4);

    return HI_SUCCESS;
}

#ifdef HI_PRODUCT_HDCP22_RX_SUPPORT
static unsigned int TwoByteCRC(unsigned char *in, int in_len)
{
    unsigned int check_sum = 0xA3C5;
    unsigned int index;
    unsigned int srcChar, nCksumTemp, nCksumTemp7, nCksumTemp16, crc_bit0;

    for(index = 0; index < in_len; index++)
    {
        srcChar = in[index];
        nCksumTemp = check_sum ^ srcChar;

        nCksumTemp7 = (0x0080 & nCksumTemp) >> 7;
        nCksumTemp16 = (0x10000 & nCksumTemp) >> 16;
        crc_bit0 = nCksumTemp7 ^ nCksumTemp16 ^ 1;

        check_sum = 0x1FFFF & ((nCksumTemp << 1) | crc_bit0);
    }


    for(index = 0; index < 8; index++)
    {
        nCksumTemp7 = (0x0080 & check_sum) >> 7;
        nCksumTemp16 = (0x10000 & check_sum) >> 16;
        crc_bit0 = nCksumTemp7 ^ nCksumTemp16 ^ 1;

        check_sum = 0x1FFFF & ((check_sum << 1) | crc_bit0);
    }

    return check_sum & 0xFFFF;
}

static void mpi_hdcp22_format_key(unsigned char *in, unsigned char *out)
{
    HI_U32 CheckSum;

    memset(out, 0, HDCP22_KEY_RAM_SIZE);

    /* Byte 0 - 319 RX priv key 562 - 881*/
    memcpy(&out[0], &in[522], 320);

    /* Byte 320 ~ 324 KSV 40 -44 */
    memcpy(&out[320], &in[0], 5);

    /* Byte 325 - 455  Rx pub key 45 - 175*/
    memcpy(&out[325], &in[5], 131);

    /* Byte 456 ~ 457 Reserved 176-177 */
    memcpy(&out[456], &in[136], 2);

    /* Byte 458 ~ 508 Write 0 */

    /* Byte 511 protect */
    out[511] = 0xFF;

    /* Byte 509 && 510  CRC Value */
    CheckSum = TwoByteCRC(out, 458);
    out[509] = CheckSum & 0xff;
    out[510] = (CheckSum >> 8) & 0xff;

    /* Byte 512 ~ 895 Reserved 178-561 */
    memcpy(&out[512], &in[138], 384);

    /* Byte 895 ~ 1020 Write 0 */

    /* Byte 1023 protect */
    out[1023] = 0xFF;

    /* Byte 1021 && 1022  CRC Value */
    CheckSum = TwoByteCRC(&out[512], 384);
    out[1021] = CheckSum & 0xff;
    out[1022] = (CheckSum >> 8) & 0xff;
}

static int mpi_hdcp_22_trans(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, HI_U8 *in, HI_U8 *out, u8 *tool_key)
{
    HI_U16 checksum = 0;
    HI_S32 ret = HI_FAILURE;
    HI_U8 *encrypt_key = NULL;
    HI_U8 *clean_key = NULL;
    HI_U8 hostkey[HDCP_ROOT_KEY_SIZE];
    HI_U32 index = 0;

    encrypt_key  = in;
    encrypt_key += HDCP22_KEY_HEAD_SIZE;

    clean_key = malloc(HDCP22_KEY_RAM_SIZE);
    if (NULL == clean_key)
    {
        HI_ERR_HDCP("mallc buffer for clean hdcp key failed\n");
        return HI_FAILURE;
    }

    memset(hostkey, 0, HDCP_ROOT_KEY_SIZE);
    memcpy(hostkey, tool_key, HDCP_ROOT_KEY_SIZE);

    ret = mpi_hdcp_operation(HDCP_KEY_SEL_HOST, HDMI_RAM_SEL_NONE, hostkey,
        encrypt_key, clean_key, HDCP22_KEY_PRIM_SIZE, SYMC_OPERATION_DECRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("HDCP key decrypt final failed!\n");
        free(clean_key);
        return HI_FAILURE;
    }

    out[index++] = (HDCP_KEY_SEL_OTP == keysel ? HDCP_KEY_FLAG_OTP : HDCP_KEY_FLAG_HISI);
    out[index++] = 0x00;
    index += 2; /* skip 2 byte of crc */

    mpi_hdcp22_format_key(&clean_key[0], &out[index]);
    memset(hostkey, 0, HDCP_ROOT_KEY_SIZE);

    free(clean_key);

    /* encrypt hdcp key by root key*/
    ret = mpi_hdcp_operation(keysel, ramsel, HI_NULL,
            &out[index], &out[index], HDCP22_KEY_RAM_SIZE, SYMC_OPERATION_ENCRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("HDCP key decrypt final failed!\n");
        return HI_FAILURE;
    }

    checksum = TwoByteCRC(&out[index], HDCP22_KEY_RAM_SIZE);
    out[2] = checksum & 0xff;
    out[3] = (checksum >> 8) & 0xff;

    return ret;
}

static HI_S32 mpi_hdcp22_load_key(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, u8 *in)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 checksum = 0;
    HI_U8  *hdcpkey = HI_NULL;

    /* verify checksum */
    checksum = TwoByteCRC(in+4, HDCP22_KEY_RAM_SIZE);
    if (memcmp(&checksum, &in[2], 2) != 0)
    {
        HI_ERR_HDCP("HDCP KEY head CRC compare failed!");
        return HI_FAILURE;
    }
    hdcpkey = in + 4;

    ret = mpi_hdcp_operation(keysel, ramsel, HI_NULL, hdcpkey,
        HI_NULL, HDCP22_KEY_RAM_SIZE, SYMC_OPERATION_DECRYPT);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("HDCP key decrypt final failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}
#endif

HI_S32 HI_UNF_HDCP_EncryptHDCPKey(HI_UNF_HDCP_HDCPKEY_S stHdcpKey,
                                  HI_BOOL bIsUseOTPRootKey,
                                  HI_U8 *pu8OutEncryptKey,
                                  HI_U8 *pu8ToolAesKey,
                                  HI_U32 u32ToolAesKeyLen)
{
    HI_S32 ret = HI_FAILURE;
    hdcp_rootkey_sel keysel = HDCP_KEY_SEL_OTP;
    HI_U8 *pu8HdcpKey = stHdcpKey.key.EncryptData.u8EncryptKey;

    if ((HI_NULL == pu8OutEncryptKey) || (HI_NULL == pu8ToolAesKey))
    {
        HI_ERR_HDCP("Error:point is null!\n");
        return HI_FAILURE;
    }

    if (HDCP_ROOT_KEY_SIZE != u32ToolAesKeyLen)
    {
        HI_ERR_HDCP("Invalid tool key len 0x%x!\n", u32ToolAesKeyLen);
        return HI_FAILURE;
    }

    ret = CHECK_CIPHER_HDCP_OPEN();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("Error:encrypt hdcp key,cipher is not open!\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == stHdcpKey.EncryptionFlag)
    {
        HI_ERR_HDCP("only support encryption key from tool!\n");
        return HI_FAILURE;
    }

    if (HI_FALSE == bIsUseOTPRootKey)
    {
        keysel = HDCP_KEY_SEL_HISI;
    }

    if(memcmp(pu8HdcpKey, "\x48\x49\x53\x49\x5f\x00\x00\x00", 8) == 0)/* HPCP 1.X */
    {
         ret = mpi_hdcp_encrypt_key(keysel, HDMI_RAM_SEL_TX_14, pu8HdcpKey, pu8OutEncryptKey, pu8ToolAesKey);
    }
#ifdef HI_PRODUCT_HDCP22_RX_SUPPORT
    else /* HDCP 2.2 */
    {
         ret = mpi_hdcp_22_trans(keysel, HDMI_RAM_SEL_RX_22, pu8HdcpKey, pu8OutEncryptKey, pu8ToolAesKey);
    }
#endif

    return ret;
}

HI_S32 HI_MPI_CIPHER_LoadHDCPKey(HI_U8 *pu8EncryptedHDCPKey, HI_U32 u32Len)
{
    HI_S32 ret = HI_FAILURE;
    HI_U32 tmp = 0;
    hdcp_rootkey_sel keysel = HDCP_KEY_SEL_OTP;

    if(HI_NULL == pu8EncryptedHDCPKey)
    {
        HI_ERR_HDCP("NULL Pointer, Invalid param input!\n");
        return HI_FAILURE;
    }

    ret = CHECK_CIPHER_HDCP_OPEN();
    if (HI_SUCCESS != ret)
    {
        HI_ERR_HDCP("Error:load hdcp key,cipher is not open!\n");
        return HI_FAILURE;
    }

    tmp = pu8EncryptedHDCPKey[0] & HDCP_KEY_FLAG_MASK;
    if ( HDCP_KEY_FLAG_OTP == tmp)
    {
        keysel = HDCP_KEY_SEL_OTP;
    }
    else if( HDCP_KEY_FLAG_HISI== tmp)
    {
        keysel = HDCP_KEY_SEL_HISI;
    }
    else
    {
        HI_ERR_HDCP("Invalid keySelect mode input!\n");
        return  HI_FAILURE;
    }

    if (HDCP_KEY_CHIP_FILE_SIZE == u32Len)
    {
#ifdef HI_PRODUCT_HDCP14_RX_SUPPORT
        hdmi_ram_sel ramsel = HDMI_RAM_SEL_RX_14;
#else
        hdmi_ram_sel ramsel = HDMI_RAM_SEL_TX_14;
#endif
        return mpi_hdcp_load_key(keysel, ramsel, pu8EncryptedHDCPKey);
    }
#ifdef HI_PRODUCT_HDCP22_RX_SUPPORT
    else if (HDCP22_KEY_CHIP_FILE_SIZE == u32Len)
    {
        return mpi_hdcp22_load_key(keysel, HDMI_RAM_SEL_RX_22, pu8EncryptedHDCPKey);
    }
#endif
    else
    {
        HI_ERR_HDCP("Invalid key len: 0x%x!\n", u32Len);
        return HI_FAILURE;
    }
}

/** @}*/  /** <!-- ==== API Code end ====*/


