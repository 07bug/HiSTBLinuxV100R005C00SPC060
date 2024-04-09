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

/* secure cpu*/
#define CRYPTO_SEC_CPU

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
    .version_reg  = 0x0820, \
    .version_val  = 0x00000002, \
    .reg_addr_phy = 0xF9A00000, \
    .reg_addr_size = 0x4000,\
    .crg_addr_phy = 0xF8A220C0, \
}

/* support interrupt*/
#define CRYPTO_OS_INT_SUPPORT

/* support hash cmac */
#define HASH_CMAC_SUPPORT

/* reserve nonsec channel for nonsec klad */
#define RESERVED_NONSEC_CHANNEL_SUPPORT

/* the hardware version */
#define CHIP_SYMC_VER_V100
#define CHIP_TRNG_VER_V200
#define CHIP_HDCP_VER_V100
#define CHIP_HASH_VER_V100

#define CHIP_IFEP_RSA_VER_V100

/* the hardware capacity */
//#define CHIP_AES_CCM_GCM_SUPPORT

/* the software capacity */
//#define SOFT_AES_CCM_GCM_SUPPORT
//#define SOFT_AES_CTS_SUPPORT
//#define SOFT_SHA1_SUPPORT
#define SOFT_SHA256_SUPPORT
#define SOFT_SHA512_SUPPORT
//#define SOFT_SM2_SUPPORT
//#define SOFT_SM3_SUPPORT
//#define SOFT_SM4_SUPPORT
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

/* define initial value of struct sys_arch_hardware_info for HASH*/
#define HARD_INFO_TRNG {\
    .name = "trng",  \
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 1, \
    .crg_valid = 0, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .reg_addr_phy = 0xF8ABC200,  \
    .reg_addr_size = 0x1000,\
}

/* define initial value of struct sys_arch_boot_dts for IFEP RSA*/
#define HARD_INFO_IFEP_RSA {\
    .name = "rsa",  \
    .reset_valid = 0,  \
    .clk_valid = 0, \
    .phy_valid = 1, \
    .crg_valid = 0, \
    .ver_valid = 0, \
    .int_valid = 0, \
    .reg_addr_phy = 0xF8ABB000,  \
    .reg_addr_size = 0x1000,\
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

#define HARD_INFO_SIC_RSA          BASE_TABLE_NULL
#define HARD_INFO_CIPHER_KEY       BASE_TABLE_NULL
#define HARD_INFO_SM2              BASE_TABLE_NULL
#define HARD_INFO_SM4              BASE_TABLE_NULL
#define HARD_INFO_SMMU             BASE_TABLE_NULL
