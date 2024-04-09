/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : advca_reg.h
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __ADVCA_REG_H__
#define __ADVCA_REG_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*the follows definens from ca_reg_v300.h*/
#if defined (CHIP_TYPE_hi3716mv310)
#define CA_V300_BASE_ADDR 0x10000000
#else
#define CA_V300_BASE_ADDR 0xF8A90000
#endif


#define REG_SYS_BRM_DEBUG              (0xF8A90180)
#define CA_V300_DCAS_CHIP_ID_MSB       (0xF8AB00E8)
#define CA_V300_DCAS_CHIP_ID_LSB       (0xF8AB00EC)

#define CA_V300_CONFIG_STATE           (CA_V300_BASE_ADDR + 0x00)//����״̬�Ĵ���
#define CA_V300_CSA2_CTRL              (CA_V300_BASE_ADDR + 0x04)//CSA���ƼĴ���
#define CA_V300_R2R_CTRL               (CA_V300_BASE_ADDR + 0x08)//R2R���ƼĴ���
#define CA_V300_SP_CTRL                (CA_V300_BASE_ADDR + 0x0C)//SP���ƼĴ���
#define CA_V300_CSA3_CTRL              (CA_V300_BASE_ADDR + 0x10)//CSA���ƼĴ���
#define CA_V300_LP_CTRL                (CA_V300_BASE_ADDR + 0x14)//LP���ƼĴ�����
#define CA_V300_BL_CTRL_DEC            (CA_V300_BASE_ADDR + 0x18)//BootLoader���ܿ��ƼĴ���
#define CA_V300_BL_CTRL_ENC            (CA_V300_BASE_ADDR + 0x1C)//BootLoader���ܿ��ƼĴ���
#define CA_V300_CA_DIN0                (CA_V300_BASE_ADDR + 0x20)//Key Ladder�������������0�Ĵ���
#define CA_V300_CA_DIN1                (CA_V300_BASE_ADDR + 0x24)//Key Ladder�������������1�Ĵ���
#define CA_V300_CA_DIN2                (CA_V300_BASE_ADDR + 0x28)//Key Ladder�������������2�Ĵ���
#define CA_V300_CA_DIN3                (CA_V300_BASE_ADDR + 0x2C)//Key Ladder�������������3�Ĵ���
#define CA_V300_TEST_CRTL              (CA_V300_BASE_ADDR + 0x30)//���Կ��ƼĴ���
//#define CA_V300_STB_KEY_CTRL           (CA_V300_BASE_ADDR + 0x34)//STB KEY���ƼĴ���
#define CA_V300_CA_STATE               (CA_V300_BASE_ADDR + 0x38)//CAģ��״̬�Ĵ���
#define CA_V300_LEVEL_REG              (CA_V300_BASE_ADDR + 0x3C)//keyladder �����Ĵ���
#define CA_V300_CHECKSUM_FLAG          (CA_V300_BASE_ADDR + 0x40)//secret key��checksum��־λ
#define CA_V300_CA_VERSION             (CA_V300_BASE_ADDR + 0x44)//Key Ladderģ���ж�ʹ�ܼĴ���
#define CA_V300_CA_INT_RAW             (CA_V300_BASE_ADDR + 0x48)//Key Ladderģ��ԭʼ�ж�״̬�Ĵ���
#define CA_V300_SECURE_BOOT_STATE      (CA_V300_BASE_ADDR + 0x4C)//��ȫ����״̬�Ĵ���
#define CA_V300_LP_PARAMETER_BASE      (CA_V300_BASE_ADDR + 0x50)//parameter�Ĵ���
#define CA_V300_BLK_ENC_RSLT           (CA_V300_BASE_ADDR + 0x60)//BLK���ܽ���Ĵ���
#define CA_V300_GDRM_CTRL              (CA_V300_BASE_ADDR + 0x70)//GOOGLE DRM���ƼĴ���
#define CA_V300_DCAS_CTRL              (CA_V300_BASE_ADDR + 0x74)//������CA���ƼĴ���
#define CA_V300_DEBUG_INFO             (CA_V300_BASE_ADDR + 0x78)//debug��Ϣ�Ĵ���
#define CA_V300_VERSION                (CA_V300_BASE_ADDR + 0x7C)//�汾�Ĵ���
#define CA_V300_DA_NOUCE               (CA_V300_BASE_ADDR + 0x80)//���ܵ���֤��Կ�Ĵ���
#define CA_V300_TEST_KEY               (CA_V300_BASE_ADDR + 0x90)//������Կ�Ĵ���
#define CA_V300_TEST_RESULT            (CA_V300_BASE_ADDR + 0xA0)//���Խ���Ĵ���
#define CA_V300_KEY_DOUT               (CA_V300_BASE_ADDR + 0xB0)//�м��������Ĵ���
#define CA_V300_MISC_CTRL              (CA_V300_BASE_ADDR + 0xC0)//misc���ƼĴ���
#define CA_V300_CAUK_CTRL               (CA_V300_BASE_ADDR + 0x110)//CAUK���ƼĴ���

#define DVB_SYMMETRIC_KEY_ERROR         (6)
#define R2R_SP_SYMMETRIC_KEY_ERROR      (4)
#define MISC_KL_LEVEL_ERROR             (2)
#define DCAS_KL_DISABLE_ERROR           (1)

typedef union
{
    struct
    {
        HI_U32 st_vld       : 1;  //[0]
        HI_U32 reserved     : 31; //[31:1]
    }bits;
    HI_U32 u32;
}CA_V300_CONFIG_STATE_U;


typedef union
{
    struct
    {
        HI_U32 level_sel      : 2; //[1:0]
        HI_U32 tdes_aes_sel   : 1; //[2]
        HI_U32 reserved0      : 5; //[7:3]
        HI_U32 EvenOrOdd      : 1; //[8]
        HI_U32 key_addr       : 7; //[15:9]
        HI_U32 dsc_mode       : 8; //[23:16]
        HI_U32 reserved       : 8; //[24:31]
    }bits;
    HI_U32 u32;
}CA_V300_CSA2_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 level_sel      : 2; //[1:0]
        HI_U32 tdes_aes_sel   : 1; //[2]
        HI_U32 reserved0      : 4; //[6:3]
        HI_U32 sm4_sel        : 1; //[7]   (for 98mv310)
        HI_U32 key_addr       : 8; //[15:8]
        HI_U32 mc_alg_sel     : 8; //[23:16]
        HI_U32 reserved       : 8; //[31:24]
    }bits;
    HI_U32 u32;
}CA_V300_R2R_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 level_sel      : 2; //[1:0]
        HI_U32 tdes_aes_sel   : 1; //[2]
        HI_U32 raw_mode       : 1; //[3]
        HI_U32 level_sel_5    : 1; //[4]
        HI_U32 ta_kl_flag     : 1; //[5]
        HI_U32 reserved1      : 2; //[7:6]
        HI_U32 key_addr       : 8; //[15:8]
        HI_U32 dsc_mode       : 8; //[23:16]
        HI_U32 reserved       : 8; //[31:24]
    }bits;
    HI_U32 u32;
}CA_V300_SP_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 level_sel      : 2; //[1:0]
        HI_U32 tdes_aes_sel   : 1; //[2]
        HI_U32 reserved0      : 5; //[7:3]
        HI_U32 EvenOrOdd      : 1; //[8]
        HI_U32 key_addr       : 7; //[15:9]
        HI_U32 dsc_mode       : 8; //[23:16]
        HI_U32 reserved       : 8; //[31:24]
    }bits;
    HI_U32 u32;
}CA_V300_CSA3_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 level_sel      : 2; //[1:0]
        HI_U32 reserved0      : 6; //[7:2]
        HI_U32 reserved       : 24; //[31:8]
    }bits;
    HI_U32 u32;
}CA_V300_LP_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 reserved0      : 7; //[6:0]
        HI_U32 sm4_sel        : 1; //[7]          //used for 98mv310
        HI_U32 key_addr       : 8; //[15:8]
        HI_U32 reserved       : 16; //[31:16]
    }bits;
    HI_U32 u32;
}CA_V300_BL_CTRL_DEC_U;

typedef union
{
    struct
    {
        HI_U32 reserved0      : 7; //[6:0]
        HI_U32 sm4_sel        : 1; //[7]          //used for 98mv310
        HI_U32 reserved       : 24; //[31:8]
    }bits;
    HI_U32 u32;
}CA_V300_BL_CTRL_ENC_U;

typedef union
{
    struct
    {
        HI_U32 alg_sel        : 1; //[0]
        HI_U32 decrypt        : 1; //[1]
        HI_U32 reserved       : 30; //[31:2]
    }bits;
    HI_U32 u32;
}CA_V300_TEST_CRTL_U;


typedef union
{
    struct
    {
        HI_U32 err_state           : 4; //[3:0]
        HI_U32 last_key_not_rdy    : 1; //[4]
        HI_U32 csa2_klad0_rdy      : 1; //[5]
        HI_U32 csa2_klad1_rdy      : 1; //[6]
        HI_U32 csa2_klad2_rdy      : 1; //[7]
        HI_U32 r2r_klad0_rdy       : 1; //[8]
        HI_U32 r2r_klad1_rdy       : 1; //[9]
        HI_U32 r2r_klad2_rdy       : 1; //[10]
        HI_U32 sp_klad0_rdy        : 1; //[11]
        HI_U32 sp_klad1_rdy        : 1; //[12]
        HI_U32 sp_klad2_rdy        : 1; //[13]
        HI_U32 csa3_klad0_rdy      : 1; //[14]
        HI_U32 csa3_klad1_rdy      : 1; //[15]
        HI_U32 csa3_klad2_rdy      : 1; //[16]
        HI_U32 misc_klad0_rdy      : 1; //[17]
        HI_U32 misc_klad1_rdy      : 1; //[18]
        HI_U32 misc_klad2_rdy      : 1; //[19]
        HI_U32 lp_klad0_rdy        : 1; //[20]
        HI_U32 lp_klad1_rdy        : 1; //[21]
        HI_U32 k3_rdy              : 1; //[22]
        HI_U32 k2_rdy              : 1; //[23]
        HI_U32 k1_rdy              : 1; //[24]
        HI_U32 reserved            : 6; //[25:30]
        HI_U32 klad_busy           : 1; //[31]
    }bits;
    HI_U32 u32;
}CA_V300_CA_STATE_U;

typedef union
{
    struct
    {
        HI_U32 csa2_lv      : 1; //[0]
        HI_U32 r2r_lv       : 1; //[1]
        HI_U32 sp_lv        : 1; //[2]
        HI_U32 csa3_lv      : 1; //[3]
        HI_U32 reserved     : 28; //[31:4]
    }bits;
    HI_U32 u32;
}CA_V300_LEVEL_REG_U;

typedef union
{
    struct
    {
        HI_U32 ca_finish_int  : 1; //[0]
        HI_U32 reserved_0     : 1; //[1]
        HI_U32 wdg_over_int   : 1; //[2]
        HI_U32 reserved       : 29; //[31:3]
    }bits;
    HI_U32 u32;
}CA_V300_CA_INT_STATE_U;

typedef union
{
    struct
    {
        HI_U32 ca_finish_en   : 1; //[0]
        HI_U32 reserved_0     : 1; //[1]
        HI_U32 wdg_over_en    : 1; //[2]
        HI_U32 reserved_1     : 4; //[6:3]
        HI_U32 ca_int_en      : 1; //[7]
        HI_U32 reserved       : 24; //[31:8]
    }bits;
    HI_U32 u32;
}CA_V300_CA_INT_EN_U;

typedef union
{
    struct
    {
        HI_U32 ca_finish_raw  : 1; //[0]
        HI_U32 reserved_0     : 1; //[1]
        HI_U32 wdg_over_raw   : 1; //[2]
        HI_U32 reserved       : 29; //[31:3]
    }bits;
    HI_U32 u32;
}CA_V300_CA_INT_RAW_U;

typedef union
{
    struct
    {
        HI_U32 bootrom_start  : 1; //[0]
        HI_U32 goin_normal    : 1; //[1]
        HI_U32 wrf_end        : 1; //[2]
        HI_U32 wrf_result     : 1; //[3]
        HI_U32 reserved       : 28; //[31:4]
    }bits;
    HI_U32 u32;
}CA_V300_SECURE_BOOT_STATE_U;

typedef union
{
    struct
    {
        HI_U32 level_sel               : 4; //[3:0]
        HI_U32 tdes_aes_sel            : 1; //[4]
        HI_U32 reserved_0              : 11; //[15:5]
        HI_U32 dsc_code_mc_alg_sel     : 8; //[23:16]
        HI_U32 even_or_odd             : 1; //[24]
        HI_U32 key_addr                : 7; //[31:25]
    }bits;
    HI_U32 u32;
}CA_V300_DCAS_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 work_flag      : 2; //[1:0]
        HI_U32 jtag_cur_st    : 4; //[5:2]
        HI_U32 jtag_if_state  : 2; //[7:6]
        HI_U32 key_addr       : 24; //[31:8]
    }bits;
    HI_U32 u32;
}CA_V300_DEBUG_INFO_U;

typedef union
{
    struct
    {
        HI_U32 level_sel    : 2; //[1:0]
        HI_U32 target_sel   : 1; //[2]
        HI_U32 decryption   : 1; //[3]
        HI_U32 reserved0    : 4; //[7:4]
        HI_U32 even_or_odd  : 1; //[8]
        HI_U32 key_addr     : 7; //[15:9]
        HI_U32 reserved1    : 16;//[31:16]
    }bits;
    HI_U32 u32;
}CA_V300_GDRM_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 level_sel      : 2; //[1:0]
        HI_U32 tdes_aes_sel   : 1; //[2]
        HI_U32 target_sel     : 1; //[3]
        HI_U32 level_sel_5    : 1; //[4]
        HI_U32 reserved_0     : 3; //[7:5]
        HI_U32 key_addr       : 8; //[15:8]
        HI_U32 dsc_mode       : 8; //[23:16]
        HI_U32 reserved       : 8; //[31:24]
    }bits;
    HI_U32 u32;
}CA_V300_MISC_CTRL_U;

typedef union
{
    struct
    {
        HI_U32 key_addr       : 8; //[7:0]
        HI_U32 reserved       : 24; //[31:8]
    }bits;
    HI_U32 u32;
}CA_V300_CAUK_CTRL_U; // high level code authentication

typedef union
{
    struct
    {
        HI_U32 CSA2_RootKey     :1; //[0]
        HI_U32 R2R_RootKey      :1; //[1]
        HI_U32 SP_RootKey       :1; //[2]
        HI_U32 CSA3_RootKey     :1; //[3]
        HI_U32 ChipID_JTAGKey   :1; //[4]
        HI_U32 ESCK             :1; //[5]
        HI_U32 BOOT_RootKey     :1; //[6]
        HI_U32 MISC_RootKey     :1; //[7]
        HI_U32 HDCP_RootKey     :1; //[8]
        HI_U32 OEM_RootKey      :1; //[9]
        HI_U32 STB_RootKey      :1; //[10]
        HI_U32 CA_TA_RootKey    :1; //[11]
        HI_U32 STB_TA_RootKey   :1; //[12]
        HI_U32 TZ_JTAG_RootKey  :1; //[13]
        HI_U32 SEC_STORE_RootKey :1; //[14]
        HI_U32 reserve          :17; //[15~31]
    }bits;
    HI_U32 u32;
}HI_UNF_ADVCA_CHECKSUM_FLAG_U;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif