#if defined(HI_TEE_SUPPORT)  || defined(HI_LOADER_APPLOADER) || defined(HI_DRV_WORK_IN_NON_SECURE_MODE)

/* the total cipher hard channel which we can used*/
#define CIPHER_HARD_CHANNEL_CNT         (0x03)

/* mask which cipher channel we can used, bit0 means channel 0*/
#define CIPHER_HARD_CHANNEL_MASK        (0x0E)

/* the total hash hard channel which we can used*/
#define HASH_HARD_CHANNEL_CNT           (0x01)

/* mask which cipher channel we can used, bit0 means channel 0*/
#define HASH_HARD_CHANNEL_MASK          (0x01)
#define HASH_HARD_CHANNEL               (0x00)

/* the total cipher hard key channel which we can used*/
#define CIPHER_HARD_KEY_CHANNEL_CNT     (0x03)

/* mask which cipher hard key channel we can used, bit0 means channel 0*/
#define CIPHER_HARD_KEY_CHANNEL_MASK    (0x0E)

/* when CFG_HI_CHIP_TYPE=hi3798mv200 and CFG_HI_ADVCA_TYPE=VERIMATRIX_ULTRA,
 * the tee image is replaced by ultra branch,
 * tee image of ultra nonsupport cipher ta
 */
#ifdef HI_ADVCA_TYPE_VERIMATRIX_ULTRA
#define TEE_CIPHER_TA_NONSUPPORT
#endif

#else

/* the total cipher hard channel which we can used*/
#define CIPHER_HARD_CHANNEL_CNT         (0x07)

/* mask which cipher channel we can used, bit0 means channel 0*/
#define CIPHER_HARD_CHANNEL_MASK        (0xFE)

/* the total hash hard channel which we can used*/
#define HASH_HARD_CHANNEL_CNT           (0x01)

/* mask which cipher channel we can used, bit0 means channel 0*/
#define HASH_HARD_CHANNEL_MASK          (0x01)
#define HASH_HARD_CHANNEL               (0x00)

/* the total cipher hard key channel which we can used*/
#define CIPHER_HARD_KEY_CHANNEL_CNT     (0x07)

/* mask which cipher hard key channel we can used, bit0 means channel 0*/
#define CIPHER_HARD_KEY_CHANNEL_MASK    (0xFE)

#define CHIP_TRNG_VER_V200

#endif

/* info for secure CPU */
#define HARD_INFO_CIPHER {\
    .name = "cipher",  \
    .reset_valid = 1,  \
    .clk_valid = 0, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 1, \
    .int_valid = 1, \
    .clk_bit = 12, \
    .reset_bit = 9, \
    .int_num = 126, \
    .version_reg = 0x1440, \
    .version_val = 0x71641002, \
    .reg_addr_phy = 0xF9A00000, \
    .reg_addr_size = 0x4000,\
    .crg_addr_phy = 0xF8A220C0, \
}

/* define initial value of struct sys_arch_hardware_info for SMMU*/
#define HARD_INFO_SMMU {\
    .name = "smmu",  \
    .reset_valid = 1,  \
    .clk_valid = 1, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 1, \
    .int_valid = 1, \
    .clk_bit = 0, \
    .reset_bit = 4, \
    .int_num = 126, \
    .version_reg  = 0x0000, \
    .version_val  = 0x00000001, \
    .reg_addr_phy = 0xF99F0000,  \
    .reg_addr_size = 0x1000,\
    .crg_addr_phy = 0xF8A22378, \
}

/* define initial value of struct sys_arch_boot_dts for cipher*/
#define HARD_INFO_HASH {\
    .name = "hash",  \
    .reset_valid = 1,  \
    .clk_valid = 1, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 1, \
    .int_valid = 0, \
    .clk_bit = 0, \
    .reset_bit = 4, \
    .version_reg  = 0x0008, \
    .version_val  = 0x0000000F, \
    .reg_addr_phy = 0xF9A10000, \
    .reg_addr_size = 0x1000,\
    .crg_addr_phy = 0xF8A220C4, \
}

/* define initial value of struct sys_arch_hardware_info for HASH*/
#define HARD_INFO_TRNG {\
    .name = "trng",  \
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 1, \
    .crg_valid = 0, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .reg_addr_phy = 0xF8005200,  \
    .reg_addr_size = 0x1000,\
}

/* support smmu*/
#define CRYPTO_SMMU_SUPPORT

/* support hash cmac */
#define HASH_CMAC_SUPPORT

/* support advca function */
#define ADVCA_FUNC_SUPPORT

/* support interrupt*/
#define CRYPTO_OS_INT_SUPPORT

/* the hardware version */
#define CHIP_SYMC_VER_V100
#define CHIP_HASH_VER_V100
#define CHIP_HDCP_VER_V100
//#define CHIP_IFEP_RSA_VER_V100

/* the hardware capacity */
//#define CHIP_AES_CCM_GCM_SUPPORT

/* the software capacity */
//#define SOFT_AES_CCM_GCM_SUPPORT
//#define SOFT_AES_CTS_SUPPORT
//#define SOFT_SHA1_SUPPORT
//#define SOFT_SHA256_SUPPORT
#define SOFT_SHA512_SUPPORT
#define SOFT_SM2_SUPPORT
#define SOFT_SM3_SUPPORT
#define SOFT_SM4_SUPPORT
#define SOFT_ECC_SUPPORT

/* moudle unsupport, we need set the table*/
#define BASE_TABLE_NULL    {\
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 0, \
    .crg_valid = 0, \
    .ver_valid = 0, \
    .int_valid = 0, \
}


#define HARD_INFO_IFEP_RSA         BASE_TABLE_NULL
#define HARD_INFO_SIC_RSA          BASE_TABLE_NULL
#define HARD_INFO_CIPHER_KEY       BASE_TABLE_NULL
#define HARD_INFO_SM2              BASE_TABLE_NULL
#define HARD_INFO_SM4              BASE_TABLE_NULL

/* the loader cpu may be running under non-secure CPU or secure CPU,
 * need to switch the hard info when ree running in non-secure CPU
 */
#define CRYPTO_SWITCH_CPU

#define NSEC_HARD_INFO_CIPHER {\
    .name = "multicipher",  \
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 1, \
    .int_valid = 1, \
    .clk_bit = 12, \
    .reset_bit = 9, \
    .int_num = 75, \
    .version_reg = 0x1440, \
    .version_val = 0x71641002, \
    .reg_addr_phy = 0xF9A00000, \
    .reg_addr_size = 0x4000,\
    .crg_addr_phy = 0xF8A220C0, \
}

#define NSEC_HARD_INFO_SMMU {\
    .name = "smmu",  \
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 1, \
    .int_valid = 1, \
    .clk_bit = 0, \
    .reset_bit = 4, \
    .int_num = 126, \
    .version_reg  = 0x0000, \
    .version_val  = 0x00000001, \
    .reg_addr_phy = 0xF99F0000,  \
    .reg_addr_size = 0x1000,\
    .crg_addr_phy = 0xF8A22378, \
}

#define NSEC_HARD_INFO_HASH {\
    .name = "hash",  \
    .reset_valid = 1,  \
    .clk_valid = 1, \
    .phy_valid = 1, \
    .crg_valid = 1, \
    .ver_valid = 1, \
    .int_valid = 0, \
    .clk_bit = 5, \
    .reset_bit = 6, \
    .version_reg  = 0x0008, \
    .version_val  = 0x0000000F, \
    .reg_addr_phy = 0xF9A20000, \
    .reg_addr_size = 0x1000,\
    .crg_addr_phy = 0xF8A220C4, \
}

#define NSEC_HARD_INFO_CIPHER_KEY       BASE_TABLE_NULL
#define NSEC_HARD_INFO_IFEP_RSA         BASE_TABLE_NULL
#define NSEC_HARD_INFO_SIC_RSA          BASE_TABLE_NULL
#define NSEC_HARD_INFO_TRNG             BASE_TABLE_NULL
#define NSEC_HARD_INFO_SM2              BASE_TABLE_NULL
#define NSEC_HARD_INFO_SM4              BASE_TABLE_NULL
