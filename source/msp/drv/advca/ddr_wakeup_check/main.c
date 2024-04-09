#include "hash.h"

/*-----------------------------------------------------------------
 * otp reg
------------------------------------------------------------------ */
#define PV_0_ADDR_P         (OTP_BASE_ADDR_P + 0x80) //ddr_wakeup_disable: [4]
#define PV_1_ADDR_P         (OTP_BASE_ADDR_P + 0x84) //wakeup_ddr_check_en: [24]
#define OTPCTRL_VENDOR_P    (OTP_BASE_ADDR_P + 0x12c)


#define SC_GEN15      (SC_SYS_BASE + 0x00BC) //This register is set to standby.

#define MCU_SUSPEND_FLAG  0x80510001


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

#ifndef reg_get
#define reg_get(addr) (*(volatile unsigned int *)(addr))
#endif

#ifndef reg_set
#define reg_set(addr, val) (*(volatile unsigned int *)(addr) = (val))
#endif

//UART1 UART_DR:UART_DR 为UART 数据寄存器，存放接收数据和发送数据
//[7:0] RW data 接收数据和发送数据。
#if   defined (CHIP_TYPE_hi3716mv410) \
   || defined (CHIP_TYPE_hi3716mv420) \
   || defined (CHIP_TYPE_hi3716cv200) \
   || defined (CHIP_TYPE_hi3719cv100) \
   || defined (CHIP_TYPE_hi3719mv100) \
   || defined (CHIP_TYPE_hi3798mv100) \
   || defined (CHIP_TYPE_hi3796mv100) \
   || defined (CHIP_TYPE_hi3798cv200) \
   || defined(CHIP_TYPE_hi3798mv200) \
   || defined(CHIP_TYPE_hi3798mv300) \
   || defined(CHIP_TYPE_hi3798mv310)
#define OTP_BASE_ADDR_P     0xf8ab0000
#define DDR_CHECK_ADDR_SECTOR       0xf8407818
#define DDR_CHECK_LEN_SECTOR        0xf840781C

#define SC_SYS_BASE   0xf8000000

#define SC_GEN53        (SC_SYS_BASE + 0x0F54)
#define SC_GEN55        (SC_SYS_BASE + 0x0F5C)
#define SC_GEN57        (SC_SYS_BASE + 0x0F64)
#define SC_GEN59        (SC_SYS_BASE + 0x0F6C)  //The GEN register 32 ~ 64 are used for storing wakeup check parameters

#define UART_PRINT_OUT  0xf8b00000
#endif
#if  defined (CHIP_TYPE_hi3716mv310) \
  || defined (CHIP_TYPE_hi3110ev500) \
  || defined (CHIP_TYPE_hi3716mv330)
#define OTP_BASE_ADDR_P     0x10180000
#define DDR_CHECK_ADDR_SECTOR       0x600b7818
#define DDR_CHECK_LEN_SECTOR        0x600b781C
#define SC_SYS_BASE   0x101e0000

#define UART_PRINT_OUT  0x101e5000
#endif

int main(void)
{
    unsigned int i;
    unsigned int u32BlockNum = 1;
    unsigned int u32Length = 0;
    unsigned int pad_size;
    #ifdef HI_DDR_WAKEUP_CHECK_HASH256
    unsigned char u8Digest[32];
    #else
    unsigned char u8Digest[20];
    #endif
    unsigned int u32Value;
    unsigned int wakeup_ddr_check_en;
    unsigned int ddr_wakeup_disable;
    HI_UNF_ADVCA_VENDORID_E eVendorId = HI_UNF_ADVCA_NULL;
    unsigned int addr;
    u32 total_dma_len = 0;

    u32Value = reg_get(PV_0_ADDR_P);
    ddr_wakeup_disable = (u32Value >> 4) & 0x1;

    u32Value = reg_get(PV_1_ADDR_P);
    wakeup_ddr_check_en = (u32Value >> 24) & 0x1;

    u32Value = reg_get(OTPCTRL_VENDOR_P);
    eVendorId = u32Value & 0xFF;
    if((ddr_wakeup_disable == 0) && (wakeup_ddr_check_en == 1))
    {
        //Calculat sha1
        addr = reg_get(DDR_CHECK_ADDR_SECTOR);
        u32Length = reg_get(DDR_CHECK_LEN_SECTOR);

        #ifdef HI_DDR_WAKEUP_CHECK_HASH256
        hash_cfg_len(MOD_HASH256, &u32Length, &pad_size);
        #else
        hash_cfg_len(MOD_HASH1, &u32Length, &pad_size);
        #endif
        for(i = 0; i < u32BlockNum; i++)
        {
            hash_cfg_dma((unsigned char *)addr, u32Length, &total_dma_len);
        }
        hash_cfg_pad(u32Length, pad_size);
        #ifdef HI_DDR_WAKEUP_CHECK_HASH256
        hash_get_result(MOD_HASH256, u8Digest);
        #else
        hash_get_result(MOD_HASH1, u8Digest);
        #endif
        //write hash result to GEN register
#if   defined (CHIP_TYPE_hi3716mv410) \
   || defined (CHIP_TYPE_hi3716mv420) \
   || defined (CHIP_TYPE_hi3716cv200) \
   || defined (CHIP_TYPE_hi3719cv100) \
   || defined (CHIP_TYPE_hi3719mv100) \
   || defined (CHIP_TYPE_hi3798mv100) \
   || defined (CHIP_TYPE_hi3796mv100) \
   || defined (CHIP_TYPE_hi3798cv200) \
   || defined(CHIP_TYPE_hi3798mv200) \
   || defined(CHIP_TYPE_hi3798mv300) \
   || defined(CHIP_TYPE_hi3798mv310)
        reg_set(SC_GEN59,*(unsigned int*)(u8Digest + 0x0));//HASH[0]
        reg_set(SC_GEN59 + 0x4,*(unsigned int*)(u8Digest + 0x4));//HASH[1]
        reg_set(SC_GEN59 + 0x8,*(unsigned int*)(u8Digest + 0x8));//HASH[2]
        reg_set(SC_GEN59 + 0xc,*(unsigned int*)(u8Digest + 0xc));//HASH[3]
        reg_set(SC_GEN59 + 0x10,*(unsigned int*)(u8Digest + 0x10));//HASH[4]

        #ifdef HI_DDR_WAKEUP_CHECK_HASH256
        reg_set(SC_GEN53,*(unsigned int*)(u8Digest + 0x14));//HASH[5] sc_gen35
        reg_set(SC_GEN55,*(unsigned int*)(u8Digest + 0x18));//HASH[6] sc_gen37
        reg_set(SC_GEN57,*(unsigned int*)(u8Digest + 0x1c));//HASH[7] sc_gen38
        #endif
#endif
#if  defined (CHIP_TYPE_hi3716mv310) \
  || defined (CHIP_TYPE_hi3110ev500) \
  || defined (CHIP_TYPE_hi3716mv330)
        reg_set(0x4700,*(unsigned int*)(u8Digest + 0x0));//HASH[0]
        reg_set(0x4700 + 0x4,*(unsigned int*)(u8Digest + 0x4));//HASH[1]
        reg_set(0x4700 + 0x8,*(unsigned int*)(u8Digest + 0x8));//HASH[2]
        reg_set(0x4700 + 0xc,*(unsigned int*)(u8Digest + 0xc));//HASH[3]
        reg_set(0x4700 + 0x10,*(unsigned int*)(u8Digest + 0x10));//HASH[4]
#endif

    }

    //Notify C51 to standby
    reg_set(SC_GEN15, MCU_SUSPEND_FLAG);

    while(1);
}

