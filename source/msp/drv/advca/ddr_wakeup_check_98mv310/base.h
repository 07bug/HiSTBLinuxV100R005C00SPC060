#ifndef __BASE_H__
#define __BASE_H__

#include "types.h"

#define ADDR_MCU_LPDS_START      (0xf840ec00)
#define LPDS_LEN                 (0x400)
#define LPDS_VERIFY_LEN          (LPDS_LEN - 0x20)
#define DDR_CHECK_MAX_NUM        (16)
#define HashValueLPDS_Offset     (0x0)
#define CEP_Offset               (0x20)
#define CEP64_Offset             (0x34)
#define HashValueDDR_Offset      (0x40)
#define CheckAreaNum_Offset      (0x60)
#define CheckAreaAddr0_Offset    (0x64)
#define CheckAreaSize0_Offset    (0x68)

#define OTP_BASE_ADDR_P          (0xf8ab0000)
#define OTPCTRL_PVINFO0          (OTP_BASE_ADDR_P + 0x80) //ddr_wakeup_disable: [4]
#define OTPCTRL_PVINFO1          (OTP_BASE_ADDR_P + 0x84) //wakeup_ddr_check_en: [24]

#define REG_KLD_BASE             (0xF8A90000)
#define REG_KLD_SEC_FLAG         (REG_KLD_BASE + 0x174)
#define NONSEC_ID_WORD           (0x2A13C812)

#define DDRPHY_BASE_ADDR         (0xF8A3C000)
#define DATA_PHY_BASE_ADDR       (0xF840EC00 + 0x100)
#define DDRPHY_ARRAY_COUNT       (0x4)
#define DDRC0_BASE_ADDR          (0xF8A38000)
#define DDRPHY0_BASE_ADDR        (0xF8A3C000)
#define DDR_SREF                 (0x00)
#define DDR_STATUS               (0x0294)
#define DDR_PHYCTRL0_28NM_ADDR   (0xf8a3d014)
#define DDR_PHY_ISO              (0x58)

#define REG_SC_BASE              (0xf8000000)
#define SC_GEN15                 (REG_SC_BASE + 0x00BC) //This register is set to standby.

#define MCU_SUSPEND_FLAG         (0x80510001)
#define MCU_START_CTRL           (0xf840f000)

#define CRG_BASE_ADDR            (0xF8A22000)

#define SHA256_LEN               (0x20)

#define wait_minute_2(x,y) do{ \
    unsigned char  i, j; \
    for(i = 0; i < x; i++) {\
        for(j = 0; j < y; j++); \
    }\
}while(0);

typedef union
{
    struct
    {
        u32 soc_tee_enable              : 1; //[0]
        u32 reserved                    : 16;//[31:1]
    } bits;
    u32 u32;
} FUSE_ISOLATE_U;

typedef union
{
    struct
    {
        u32 reserved                    : 26; //[25:0]
        u32 auth_alg_sel                : 1;//0x03[2], Secure boot mode authentication control.
        u32 scs_emmc_normal_en          : 1;//0x03[3], eMMC  mode control when bootROM run.
        u32 tskl_tdes_disable           : 1;//0x03[4], DEMUX TDES engine control.
        u32 scs_emmc_uefi_en            : 1;//0x03[5], Whether support eMMC UEFI mode or not
        u32 ddr_scramble_en             : 1;//0x03[6]
        u32 otp_global_lock_en          : 1;//0x03[7]
    } bits;
    u32 u32;
} OTP_PV_0_U;                   //Offset:0x0


#ifndef reg_get
#define reg_get(addr) (*(volatile unsigned int *)(addr))
#endif

#ifndef reg_set
#define reg_set(addr, val) (*(volatile unsigned int *)(addr) = (val))
#endif

void printf_char(unsigned char ch);
void printf_str(char *string);
void printf_hex(unsigned int u32Hex);
void memset(void *s, int c, unsigned int count);
void memset(void *s, int c, unsigned int count);
void u82u32(unsigned int * u32_data, unsigned char * u8_data, unsigned int byte_size);
void u322u8(unsigned char * u8_data, unsigned int * u32_data, unsigned int byte_size);

#endif /*__BASE_H__*/
