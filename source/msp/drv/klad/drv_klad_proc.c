/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : drv_klad_proc.h
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/

#include "hi_drv_klad.h"
#include "hal_klad.h"
#include "drv_klad_ioctl.h"
#include "drv_klad.h"
#include "drv_klad_proc.h"
#include "hal_klad_reg.h"

#ifdef HI_ADVCA_C1_SUPPORT
#include "hal_klad_nagra.h"
#include "hi_unf_klad_nagra.h"
#endif
#ifdef HI_ADVCA_C2_SUPPORT
#include "hal_klad_irdeto.h"
#include "hi_unf_klad_irdeto.h"
#endif
#ifdef HI_ADVCA_C3_SUPPORT
#include "hal_klad_conax.h"
#include "hi_unf_klad_conax.h"
#endif
#ifdef HI_ADVCA_COMMON_CA_SUPPORT
#include "hal_klad_common_ca.h"
#include "hi_unf_klad_common_ca.h"
#endif
#ifdef HI_ADVCA_DCAS_SUPPORT
#include "hal_klad_dcas.h"
#include "hi_unf_klad_dcas.h"
#endif
#ifdef HI_ADVCA_C6_SUPPORT
#include "hal_klad_verimatrix.h"
#include "hi_unf_klad_verimatrix.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef HI_PROC_SUPPORT
#define CA_KLAD_BASE_ADDR 0xF8ABA000
#define DRV_KLAD_PROC_SEPARATE         "===============================================\n"
#define DRV_KLAD_PROC_PRINT(fmt...)    PROC_PRINT(p, fmt)

#define INVALID_BIT    0xff
#define INVALID_ADDR   0xffffffff

#define HI_KLAD_BASE_RKP            (0xf8ab0000)
#define HI_SECURE_BOOT_RSA_VERIFY   (HI_KLAD_BASE_RKP + (0X6064))
#define HI_SECURE_BOOT_DETAIL_INFO  (HI_KLAD_BASE_RKP + (0X6050))
#define HI_SECURE_BOOT_BRIEF_INFO   (HI_KLAD_BASE_RKP + (0X6100))

#define HI_OTP_BOOT_MODE_SEL       (KL_OTP_SHADOW_BASE_ADDR + (0X0))
#define HI_OTP_BOOTSEL_CTRL        (KL_OTP_SHADOW_BASE_ADDR + (0X1))
#define HI_OTP_RSA_RD_DISABLE      (KL_OTP_SHADOW_BASE_ADDR + (0x0e))
#define SECURE_BOOT_DISABLE         (0X81)
#define HI_OTP_SCS_ACTIVATION      (KL_OTP_SHADOW_BASE_ADDR + (0X50))
#define HI_OTP_MS_ID               (KL_OTP_SHADOW_BASE_ADDR + (0xe0))
#define HI_OTP_SOS_MS_ID           (KL_OTP_SHADOW_BASE_ADDR + (0xe8))
#define HI_OTP_CA_VENDER_ID        (KL_OTP_SHADOW_BASE_ADDR + (0XF0))

typedef HI_U8 (*KLAD_GetLevel) (HI_VOID);
typedef struct
{
    HI_U32 index;
    HI_U32 klad_type;
    HI_CHAR klad_str[32];
    KLAD_GetLevel klad_get_level;
} DRV_KLAD_PROCINFO;

typedef struct
{
    HI_U32 index;
    HI_CHAR klad_str[32];
    HI_U32 check_crc_rslt_regs;
    HI_U8 reg_offset;
} DRV_KLAD_ROOTKEY_CRC;

static HI_S32 DRV_KLAD_ProcGetSCSStatus(struct seq_file* p)
{
    HI_U8 u8SCSStatus = 0;

    if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(HI_OTP_SCS_ACTIVATION, &u8SCSStatus))
    {
        return HI_FAILURE;
    }

    if(SECURE_BOOT_DISABLE == u8SCSStatus)
    {
        PROC_PRINT(p, "SCS(Secure Boot Activation): not enabled\n");
    }
    else
    {
        PROC_PRINT(p, "SCS(Secure Boot Activation): enabled\n");
    }
    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_ProcGetCAVendorType(struct seq_file* p)
{
    HI_U8 u8VendorID = 0;

    if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(HI_OTP_CA_VENDER_ID, &u8VendorID))
    {
        return HI_FAILURE;
    }

    switch(u8VendorID)
    {
        case HI_UNF_ADVCA_NULL:
            PROC_PRINT(p, "CA vendor type: 0x%08x(NULL)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_NAGRA:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Nagra)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_IRDETO:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Irdeto)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_CONAX:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Conax)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_SUMA:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Suma)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_NOVEL:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Novel)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_VERIMATRIX:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Vermatrix)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_CTI:
            PROC_PRINT(p, "CA vendor type: 0x%08x(CTI)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_COMMONCA:
            PROC_PRINT(p, "CA vendor type: 0x%08x(CommonCA)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_DCAS:
            PROC_PRINT(p, "CA vendor type: 0x%08x(DCAS)\n", u8VendorID);
            break;
        case HI_UNF_ADVCA_PANACCESS:
            PROC_PRINT(p, "CA vendor type: 0x%08x(Panaccess)\n", u8VendorID);
            break;
        default:
            PROC_PRINT(p, "CA vendor type: 0x%08x(UnkownCA)\n", u8VendorID);
            break;
    }
    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_ProcGetMSID(struct seq_file* p)
{
    HI_U8 u8MSID[4] = {0};
    HI_U32 i = 0;

    PROC_PRINT(p, "Market ID:");
    for(i = 0; i < 4; i++)
    {
        if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(HI_OTP_MS_ID + i, &u8MSID[i]))
        {
            return HI_FAILURE;
        }
        PROC_PRINT(p, " 0x%02x", u8MSID[i]);
    }
    PROC_PRINT(p, "\n");

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_ProcGetSOSMSID(struct seq_file* p)
{
    HI_U8 u8MSID[4] = {0};
    HI_U32 i = 0;

    PROC_PRINT(p, "SecureOS Market ID:");
    for(i = 0; i < 4; i++)
    {
        if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(HI_OTP_SOS_MS_ID + i, &u8MSID[i]))
        {
            return HI_FAILURE;
        }
        PROC_PRINT(p, " 0x%02x", u8MSID[i]);
    }
    PROC_PRINT(p, "\n");

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_GetRSAKeyReadable(struct seq_file* p)
{
    HI_U8 u8RsaKeyRd = 0;

    if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(HI_OTP_RSA_RD_DISABLE,&u8RsaKeyRd))
    {
        return HI_FAILURE;
    }

    if(0 == (u8RsaKeyRd & 0x1))
    {
        PROC_PRINT(p, "RSA Root Public Key is readable.\n");
    }
    else
    {
        PROC_PRINT(p, "RSA Root Public Key is unreadable.\n");
    }

    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_ProcGetBootMode(struct seq_file* p)
{
    HI_U8 u8BootMode = 0;
    HI_U8 u8BootSel = 0;

    if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(HI_OTP_BOOT_MODE_SEL,&u8BootMode)
        || HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(HI_OTP_BOOTSEL_CTRL,&u8BootSel))
    {
        return HI_FAILURE;
    }

    if(0 == (u8BootSel & 0x1))
    {
        PROC_PRINT(p, "Boot mode is controlled by chipset pin\n");
        return HI_SUCCESS;
    }

    PROC_PRINT(p, "Boot Mode: %s\n",
        u8BootMode == HI_UNF_ADVCA_FLASH_TYPE_SPI ? "SPI" :
        (u8BootMode == HI_UNF_ADVCA_FLASH_TYPE_NAND ? "NAND" :
        (u8BootMode == HI_UNF_ADVCA_FLASH_TYPE_EMMC ? "EMMC" :
        (u8BootMode == HI_UNF_ADVCA_FLASH_TYPE_SPI_NAND ? "SPI_NAND" :
        (u8BootMode == HI_UNF_ADVCA_FLASH_TYPE_SD ? "SD" : "Unknow")))));

    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_PrintSessionKey(struct seq_file* p, DRV_KLAD_SESSION * session, HI_U32 key_level, HI_CHAR* klad_str)
{
    HI_U32 level, index2;

    KLAD_CHECK_POINTER(session);
    KLAD_CHECK_POINTER(p);
    KLAD_CHECK_PARAM(key_level >= HI_UNF_KLAD_LEVEL_BUTT);
    KLAD_CHECK_PARAM(key_level < 1);
    for(level = 0; level < key_level - 1; level++)
    {
        PROC_PRINT(p, "%s klad%d:(session key)", klad_str, level);
        for(index2 = 0; index2 < HI_UNF_KLAD_MAX_KEY_LEN; index2++)
            PROC_PRINT(p, " 0x%02x", session->instance.session_key[level].key[index2]);
        PROC_PRINT(p, "\n");
    }
    PROC_PRINT(p, "%s klad%d:(content key)", klad_str, level);
    for(index2 = 0; index2 < HI_UNF_KLAD_MAX_KEY_LEN; index2++)
        PROC_PRINT(p, " 0x%02x", session->instance.content_key.key[index2]);
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_PrintKeyladderSession(struct seq_file* p, HI_U32 key_level, HI_U32 klad_type, HI_CHAR* klad_str)
{
    DRV_KLAD_SESSION *session = HI_NULL;
    DRV_KLAD_SESSION *tmp = HI_NULL;
    HI_U32 num = 0;

    KLAD_CHECK_POINTER(p);
    KLAD_CHECK_POINTER(klad_str);
    KLAD_CHECK_PARAM(key_level >= HI_UNF_KLAD_LEVEL_BUTT);

    PROC_PRINT(p, "====================================\n");
    PROC_PRINT(p, "%s key ladder stage: %d Level\n", klad_str, key_level);

    mutex_lock(&klad_session_list.lock);
    list_for_each_entry_safe(session, tmp, &klad_session_list.list, list)
    {
        if (session && session->instance.attr.klad_type == klad_type)
        {
            PROC_PRINT(p, "------------------------------------\nsession index %d\n", num);
            num ++;
            if(session->instance.attr.alg == HI_UNF_KLAD_ALG_TYPE_TDES)
            {
                PROC_PRINT(p, "%s key ladder algorithm is TDES\n", klad_str);
            }
            else if(session->instance.attr.alg == HI_UNF_KLAD_ALG_TYPE_AES)
            {
                PROC_PRINT(p, "%s key ladder algorithm is AES\n", klad_str);
            }
            else
            {
                PROC_PRINT(p, "%s key ladder algorithm is unknown\n", klad_str);
            }
            (HI_VOID)DRV_KLAD_PrintSessionKey(p, session, key_level, klad_str);
            PROC_PRINT(p, "------------------------------------\n");
        }
    }
    mutex_unlock(&klad_session_list.lock);
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_ProcGetChipId(struct seq_file* p, HI_U32 chip_id_off, HI_U8 * ca_str)
{
    HI_U32 i;
    HI_U8 chip_id[8] = {0};

    KLAD_CHECK_POINTER(p);
    KLAD_CHECK_POINTER(ca_str);
    PROC_PRINT(p, "\n==================%s========================\n",ca_str);
    PROC_PRINT(p, "ChipID:");
    for(i = 0; i < 8; i++)
    {
        if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(chip_id_off + i, &chip_id[i]))
        {
            return HI_FAILURE;
        }
        PROC_PRINT(p, " 0x%02x", chip_id[i]);
    }
    PROC_PRINT(p, "\n");
    return HI_SUCCESS;
}

#define DRV_KLAD_ProcDumpKey(p, Cx_klad_info) \
{   \
    HI_U32 num = 0; \
    HI_U32 i = 0; \
    HI_U32 klad_level = 0; \
    \
    KLAD_CHECK_POINTER(p); \
    KLAD_CHECK_POINTER(Cx_klad_info); \
    num = sizeof(Cx_klad_info)/sizeof(Cx_klad_info[0]); \
    for (i=0; i < num; i++) \
    { \
        if(Cx_klad_info[i].klad_get_level) \
            klad_level = Cx_klad_info[i].klad_get_level(); \
        else \
            klad_level = 1; \
        DRV_KLAD_PrintKeyladderSession(p, klad_level, Cx_klad_info[i].klad_type, Cx_klad_info[i].klad_str); \
    } \
}

#define DRV_KLAD_ProcRootKeyVerify(p, Cx_rootkey_crc) \
{   \
    HI_U32 num = 0; \
    HI_U32 i = 0; \
    HI_U32 check_crc_reg = 0; \
    \
    KLAD_CHECK_POINTER(p); \
    KLAD_CHECK_POINTER(Cx_rootkey_crc); \
    num = sizeof(Cx_rootkey_crc)/sizeof(Cx_rootkey_crc[0]); \
    for (i=0; i < num; i++) \
    { \
        if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowReg(HI_KLAD_BASE_RKP + Cx_rootkey_crc[i].check_crc_rslt_regs, &check_crc_reg)) \
        { \
            return HI_FAILURE; \
        } \
        if(Cx_rootkey_crc[i].reg_offset >= 32) continue; \
        if(check_crc_reg & (1 << Cx_rootkey_crc[i].reg_offset)) \
        { \
            PROC_PRINT(p, "--%-32s verify:   success.(0x%08x)\n", Cx_rootkey_crc[i].klad_str, check_crc_reg); \
        } \
        else \
        { \
            PROC_PRINT(p, "--%-32s verify:   failed.\n", Cx_rootkey_crc[i].klad_str); \
        } \
    } \
}

#define DRV_KLAD_ProcRootKeyVerify_0(p, Cx_rootkey_crc) \
{   \
    HI_U32 num = 0; \
    HI_U32 i = 0; \
    HI_U32 check_crc_reg = 0; \
    \
    KLAD_CHECK_POINTER(p); \
    KLAD_CHECK_POINTER(Cx_rootkey_crc); \
    num = sizeof(Cx_rootkey_crc)/sizeof(Cx_rootkey_crc[0]); \
    for (i=0; i < num; i++) \
    { \
        if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowReg(HI_KLAD_BASE_RKP + Cx_rootkey_crc[i].check_crc_rslt_regs, &check_crc_reg)) \
        { \
            return HI_FAILURE; \
        } \
        if(Cx_rootkey_crc[i].reg_offset >= 32) continue; \
        if(0 == (check_crc_reg & (1 << Cx_rootkey_crc[i].reg_offset)) ) \
        { \
            PROC_PRINT(p, "--%-32s verify:   success.(0x%08x)\n", Cx_rootkey_crc[i].klad_str, check_crc_reg); \
        } \
        else \
        { \
            PROC_PRINT(p, "--%-32s verify:   failed.\n", Cx_rootkey_crc[i].klad_str); \
        } \
    } \
}


#ifdef HI_ADVCA_C1_SUPPORT

#define HI_OTP_NAGRA_CHIP_ID  (KL_OTP_SHADOW_BASE_ADDR + (0x90))

static DRV_KLAD_PROCINFO C1_klad_info[] = {
    {0, HI_UNF_KLAD_NAGRA_TYPE_CSA2, "CSA2", HAL_KLAD_NAGRA_CSA2GetLevel},
    {1, HI_UNF_KLAD_NAGRA_TYPE_CSA3, "CSA3", HAL_KLAD_NAGRA_CSA3GetLevel},
    {2, HI_UNF_KLAD_NAGRA_TYPE_AES , "AES ", HAL_KLAD_NAGRA_AESGetLevel },
    {3, HI_UNF_KLAD_NAGRA_TYPE_TDES, "TDES", HAL_KLAD_NAGRA_TDESGetLevel},
    {4, HI_UNF_KLAD_NAGRA_TYPE_FPK,  "FPK ", HAL_KLAD_NAGRA_BOOTGetLevel},
};

static DRV_KLAD_ROOTKEY_CRC C1_rootkey_crc[] = {
    {0, "MasterRootkeyStorage_0", 0x5008, 4},
};
static DRV_KLAD_ROOTKEY_CRC C1_rootkey_crc_0[] = {
    {0, "AKL Slot 0",             0x4050, 0},
    {0, "AKL Slot 1",             0x4050, 1},
    {0, "AKL Slot 2",             0x4050, 2},
    {0, "AKL Slot 3",             0x4050, 3},
};

static HI_S32 DRV_KLAD_ProcGetC1Info(struct seq_file* p)
{
    DRV_KLAD_ProcGetChipId(p, HI_OTP_NAGRA_CHIP_ID, "NAGRA(C1)");
    DRV_KLAD_ProcRootKeyVerify(p, C1_rootkey_crc);
    DRV_KLAD_ProcRootKeyVerify_0(p, C1_rootkey_crc_0);
    DRV_KLAD_ProcDumpKey(p, C1_klad_info);
    return HI_SUCCESS;
}

#endif
#ifdef HI_ADVCA_C2_SUPPORT

#define HI_OTP_IRDETO_CHIP_ID  (KL_OTP_SHADOW_BASE_ADDR + (0x98))

static DRV_KLAD_PROCINFO C2_klad_info[] = {
    {0, HI_UNF_KLAD_IRDETO_TYPE_CSA2, "CSA2", HAL_KLAD_IRDETO_CSA2GetLevel},
    {1, HI_UNF_KLAD_IRDETO_TYPE_CSA3, "CSA3", HAL_KLAD_IRDETO_CSA3GetLevel},
    {2, HI_UNF_KLAD_IRDETO_TYPE_SP,   "SP  ", HAL_KLAD_IRDETO_SPGetLevel  },
    {3, HI_UNF_KLAD_IRDETO_TYPE_R2R,  "R2R ", HAL_KLAD_IRDETO_R2RGetLevel },
    {4, HI_UNF_KLAD_IRDETO_TYPE_TA,   "TA  ", HAL_KLAD_IRDETO_TAGetLevel  },
    {5, HI_UNF_KLAD_IRDETO_TYPE_SSUK, "SSUK", NULL                        },

};

static DRV_KLAD_ROOTKEY_CRC C2_V2_2_rootkey_crc[] = {
    {0, "ECSUK1", 0x5014, 4},
};

static DRV_KLAD_ROOTKEY_CRC C2_V3_2_rootkey_crc[] = {
    {0, "ECSGK1",  0x502c, 11},
    {1, "EECSUK2", 0x5030, 4},
    {2, "EDOK1",   0x5030, 5},
    {3, "ECSGK2",  0x5030, 6},
};

static HI_S32 DRV_KLAD_ProcGetC2Info(struct seq_file* p)
{
    DRV_KLAD_ProcGetChipId(p, HI_OTP_IRDETO_CHIP_ID, "IRDETO(C2)");
    DRV_KLAD_ProcRootKeyVerify(p, C2_V2_2_rootkey_crc);
    DRV_KLAD_ProcRootKeyVerify(p, C2_V3_2_rootkey_crc);
    DRV_KLAD_ProcDumpKey(p, C2_klad_info);
    return HI_SUCCESS;
}
#endif
#ifdef HI_ADVCA_C3_SUPPORT

#define HI_OTP_CONAX_CHIP_ID  (KL_OTP_SHADOW_BASE_ADDR + (0xB0))

static DRV_KLAD_PROCINFO C3_klad_info[] = {
    {0, HI_UNF_KLAD_CONAX_TYPE_CSA2,    "C3_CSA2 ", HAL_KLAD_CONAX_CSA2GetLevel},
    {1, HI_UNF_KLAD_CONAX_TYPE_CSA3,    "C3_CSA3 ", HAL_KLAD_CONAX_CSA3GetLevel},
    {2, HI_UNF_KLAD_CONAX_TYPE_SP,      "C3_SP   ", HAL_KLAD_CONAX_SPGetLevel  },
    {3, HI_UNF_KLAD_CONAX_TYPE_R2R,     "C3_R2R  ", HAL_KLAD_CONAX_R2RGetLevel },
    {4, HI_UNF_KLAD_CONAX_TYPE_LP,      "C3_LP   ", HAL_KLAD_CONAX_LPGetLevel  },
    {5, 0,"CM1_CSA2", HAL_KLAD_CONAX_CM1_CSA2GetLevel},
    {6, 0,"CM1_CSA3", HAL_KLAD_CONAX_CM1_CSA3GetLevel},
    {7, 0,"CM1_SP  ", HAL_KLAD_CONAX_CM1_SPGetLevel  },
    {8, 0,"CM1_R2R ", HAL_KLAD_CONAX_CM1_R2RGetLevel },
    {9, 0,"CM1_MISC", HAL_KLAD_CONAX_CM1_MISCGetLevel  },
};

static DRV_KLAD_ROOTKEY_CRC C3_rootkey_crc[] = {
    {0, "C3_CSA2_RootKey",    0x501C, 2},
    {1, "C3_CSA3_RootKey",    0x501C, 3},
    {2, "C3_SP_RootKey",      0x501C, 4},
    {3, "C3_R2R_Rootkey",     0x501C, 5},
    {5, "CM1_CSA2_RootKey",   0x5028, 2},
    {6, "CM1_CSA3_RootKey",   0x5028, 3},
    {7, "CM1_SP_RootKey",     0x5028, 4},
    {8, "CM1_R2R_RootKey",    0x5028, 5},
    {9, "CM1_MISC_RootKey",   0x5028, 6},
};
static HI_S32 DRV_KLAD_ProcGetC3Info(struct seq_file* p)
{
    DRV_KLAD_ProcGetChipId(p, HI_OTP_CONAX_CHIP_ID, "CONAX(C3)");
    DRV_KLAD_ProcRootKeyVerify(p, C3_rootkey_crc);
    DRV_KLAD_ProcDumpKey(p, C3_klad_info);
    return HI_SUCCESS;
}
#endif

#ifdef HI_ADVCA_COMMON_CA_SUPPORT

#define HI_OTP_COM0_CA_CHIP_ID  (KL_OTP_SHADOW_BASE_ADDR + (0xB0))

static DRV_KLAD_PROCINFO Com0_klad_info[] = {
    {0, HI_UNF_KLAD_COMMON_CA_TYPE_CSA2, "CM0_CSA2", HAL_KLAD_COMMON_CA_CSA2GetLevel},
    {1, HI_UNF_KLAD_COMMON_CA_TYPE_CSA3, "CM0_CSA3", HAL_KLAD_COMMON_CA_CSA3GetLevel},
    {2, HI_UNF_KLAD_COMMON_CA_TYPE_SP,   "CM0_SP  ", HAL_KLAD_COMMON_CA_SPGetLevel  },
    {3, HI_UNF_KLAD_COMMON_CA_TYPE_R2R,  "CM0_R2R ", HAL_KLAD_COMMON_CA_R2RGetLevel },
    {4, HI_UNF_KLAD_COMMON_CA_TYPE_MISC, "CM0_MISC", HAL_KLAD_COMMON_CA_MISCGetLevel},
};

static DRV_KLAD_ROOTKEY_CRC Com0_rootkey_crc[] = {
    {0, "CM0_CSA2_RootKey",   0x5024, 2},
    {1, "CM0_CSA3_RootKey",   0x5024, 3},
    {2, "CM0_SP_RootKey",     0x5024, 4},
    {3, "CM0_R2R_RootKey",    0x5024, 5},
    {4, "CM0_MISC_RootKey",   0x5024, 6},
    {5, "CM0_JTAG_RootKey",   0x5024, 7},
};

static HI_S32 DRV_KLAD_ProcGetCommonCAInfo(struct seq_file* p)
{
    DRV_KLAD_ProcGetChipId(p, HI_OTP_COM0_CA_CHIP_ID, "COM0(C5)");
    DRV_KLAD_ProcRootKeyVerify(p, Com0_rootkey_crc);
    DRV_KLAD_ProcDumpKey(p, Com0_klad_info);
    return HI_SUCCESS;
}

#endif
#ifdef HI_ADVCA_DCAS_SUPPORT

#define HI_OTP_COM0_CA_CHIP_ID  (KL_OTP_SHADOW_BASE_ADDR + (0xB0))

static DRV_KLAD_PROCINFO dcas_klad_info[] = {
    {0, HI_UNF_KLAD_DCAS_TYPE_K30, "K30 ", HAL_KLAD_DCAS_K30GetLevel},
    {0, HI_UNF_KLAD_DCAS_TYPE_RKD, "RKD ", NULL},
};
static DRV_KLAD_ROOTKEY_CRC dcas_rootkey_crc[] = {
    {0, "ESCK",   0x5020, 3},
};
static HI_S32 DRV_KLAD_ProcGetDCASInfo(struct seq_file* p)
{
    DRV_KLAD_ProcGetChipId(p, HI_OTP_COM0_CA_CHIP_ID, "DCAS");
    DRV_KLAD_ProcRootKeyVerify(p, dcas_rootkey_crc);
    DRV_KLAD_ProcDumpKey(p, dcas_klad_info);
    return HI_SUCCESS;
}

#endif
#ifdef HI_ADVCA_C6_SUPPORT

#define HI_OTP_VERIMATRIX_CA_CHIP_ID  (KL_OTP_SHADOW_BASE_ADDR + (0xc0))

static DRV_KLAD_PROCINFO C6_klad_info[] = {
    {0, HI_UNF_KLAD_VERIMATRIX_TYPE_CSA2, "CSA2", HAL_KLAD_VERIMATRIX_CSA2GetLevel},
    {1, HI_UNF_KLAD_VERIMATRIX_TYPE_CSA3, "CSA3", HAL_KLAD_VERIMATRIX_CSA3GetLevel},
    {2, HI_UNF_KLAD_VERIMATRIX_TYPE_SP,   "SP  ", HAL_KLAD_VERIMATRIX_SPGetLevel  },
    {3, HI_UNF_KLAD_VERIMATRIX_TYPE_R2R,  "R2R ", HAL_KLAD_VERIMATRIX_R2RGetLevel },
    {4, HI_UNF_KLAD_VERIMATRIX_TYPE_MISC, "MISC", HAL_KLAD_VERIMATRIX_MISCGetLevel},
};
static DRV_KLAD_ROOTKEY_CRC C6_rootkey_crc[] = {
    {0, "CM1_CSA2_RootKey",   0x5028, 2},
    {1, "CM1_CSA3_RootKey",   0x5028, 3},
    {2, "CM1_SP_RootKey",     0x5028, 4},
    {3, "CM1_R2R_RootKey",    0x5028, 5},
    {4, "CM1_MISC_RootKey",   0x5028, 6},
    {5, "CM1_JTAG_RootKey",   0x5028, 7},
};
static HI_S32 DRV_KLAD_ProcGetC6Info(struct seq_file* p)
{
    DRV_KLAD_ProcGetChipId(p, HI_OTP_VERIMATRIX_CA_CHIP_ID, "VERIMATRIX(C6)");
    DRV_KLAD_ProcRootKeyVerify(p, C6_rootkey_crc);
    DRV_KLAD_ProcDumpKey(p, C6_klad_info);
    return HI_SUCCESS;
}

#endif

static DRV_KLAD_ROOTKEY_CRC Basic_rootkey_crc[] = {
    {0, "BOOT_Rootkey",     0x502c, 11},
    {1, "OEM_RootKey",      0x502c, 2},
    {2, "HDCP_Rootkey",     0x502c, 3},
    {3, "STB_Rootkey",      0x502c, 4},
    {4, "SW_Rootkey",       0x502c, 5},
    {5, "STB_TA_Rootkey",   0x502c, 7},
    {6, "TZ_JTAG_KEY",      0x502c, 8},
    {7, "OBFU_EXT_KEY",     0x502c, 10},
    {8, "EPFDK_Rootkey",    0x502c, 12},
    {9, "dcas_rk_ext_key",  0x502c, 13},
    {10,"smk_ext_key",      0x502c, 14},
    {11,"Hisi_Rootkey",     0x502c, 15},
};

static HI_S32 DRV_KLAD_ProcBasicRootKeyVerify(struct seq_file* p)
{
    HI_U8 u8VendorID = 0;

    if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(HI_OTP_CA_VENDER_ID, &u8VendorID))
    {
        return HI_FAILURE;
    }

    DRV_KLAD_ProcRootKeyVerify(p, Basic_rootkey_crc);
    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_ProcRSAKeyVerify(struct seq_file* p)
{
    HI_U8 rsa_verify = 0;

    if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowByte(HI_SECURE_BOOT_RSA_VERIFY, &rsa_verify))
    {
        return HI_FAILURE;
    }

    if((rsa_verify & 0x01))
    {
        PROC_PRINT(p, "RSA Root Public Key verify successfull.(0x%08x)\n", rsa_verify);
    }
    else
    {
        PROC_PRINT(p, "RSA Root Public Key verify failed.\n");
    }
    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_ProcSecBootDetailInfo(struct seq_file* p)
{
    HI_U32 rsa_verify = 0;
    HI_U32 i = 0;

    PROC_PRINT(p, "Secure boot detailed information:\n");
    for(i = 0; i < 4; i ++)
    {
        if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowReg(HI_SECURE_BOOT_DETAIL_INFO + i * 4, &rsa_verify))
        {
            return HI_FAILURE;
        }
        PROC_PRINT(p, "0x%08x ", rsa_verify);
    }
    PROC_PRINT(p, "\n");
    return HI_SUCCESS;
}

static HI_S32 DRV_KLAD_ProcSecBootBriefInfo(struct seq_file* p)
{
    HI_U32 rsa_verify = 0;
    HI_U32 i = 0;

    PROC_PRINT(p, "Secure boot brief information:\n");
    for(i = 0; i < 4; i ++)
    {
        if(HI_SUCCESS != HAL_KLAD_ProcReadOtpShadowReg(HI_SECURE_BOOT_BRIEF_INFO + i * 4, &rsa_verify))
        {
            return HI_FAILURE;
        }
        PROC_PRINT(p, "0x%08x ", rsa_verify);
    }
    PROC_PRINT(p, "\n");
    return HI_SUCCESS;
}

HI_S32 DRV_KLAD_ProcWrite(struct file* file, const char __user* buf, size_t count, loff_t* ppos)
{
    return HI_SUCCESS;
}

HI_VOID DRV_KLAD_GetCommonInfo(struct seq_file* p)
{
    PROC_PRINT(p, "\n==================common======================\n");
    (HI_VOID)DRV_KLAD_ProcGetSCSStatus(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_KLAD_ProcGetCAVendorType(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_KLAD_ProcGetMSID(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_KLAD_ProcGetSOSMSID(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_KLAD_GetRSAKeyReadable(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_KLAD_ProcGetBootMode(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_KLAD_ProcRSAKeyVerify(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_KLAD_ProcSecBootDetailInfo(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_KLAD_ProcSecBootBriefInfo(p);
    PROC_PRINT(p, "====================================\n");
    (HI_VOID)DRV_KLAD_ProcBasicRootKeyVerify(p);
}

HI_S32 DRV_KLAD_ProcRead(struct seq_file* p, HI_VOID* v)
{
    (HI_VOID)DRV_KLAD_GetCommonInfo(p);
#ifdef HI_ADVCA_C1_SUPPORT
    (HI_VOID)DRV_KLAD_ProcGetC1Info(p);
#endif
#ifdef HI_ADVCA_C2_SUPPORT
    (HI_VOID)DRV_KLAD_ProcGetC2Info(p);
#endif
#ifdef HI_ADVCA_C3_SUPPORT
    (HI_VOID)DRV_KLAD_ProcGetC3Info(p);
#endif
#ifdef HI_ADVCA_COMMON_CA_SUPPORT
    (HI_VOID)DRV_KLAD_ProcGetCommonCAInfo(p);
#endif
#ifdef HI_ADVCA_DCAS_SUPPORT
    (HI_VOID)DRV_KLAD_ProcGetDCASInfo(p);
#endif
#ifdef HI_ADVCA_C6_SUPPORT
    (HI_VOID)DRV_KLAD_ProcGetC6Info(p);
#endif

    return HI_SUCCESS;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
