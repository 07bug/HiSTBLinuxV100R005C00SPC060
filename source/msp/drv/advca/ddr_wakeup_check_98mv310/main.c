#include "base.h"
#include "hash/cipher_define.h"
#include "hash/cipher_reg.h"
#include "hash/hi_cipher.h"

#define dsb() __asm__ __volatile__ ("dsb" : : : "memory")
#define isb() __asm__ __volatile__ ("isb" : : : "memory")
#define wfi() __asm__ __volatile__ ("wfi" : : : "memory")

/******************DDRPHYRegSave Struct per section*******
****************   RegCount
****************   DDRPHY_ADDR_BASE
****************   the first DDRPHYReg value
                   ***
****************   the RegCount DDRPHYReg value
**********************************************************/
static void DDRPHYRegSave(void)
{
    unsigned int * pLPDSData;
    unsigned int * pTmpAddr;

    unsigned int RegCount;
    unsigned int i, j;
    unsigned int RegVal;

    pLPDSData = (unsigned int *)DATA_PHY_BASE_ADDR;
    RegCount = 13;

    for (i = 0; i < DDRPHY_ARRAY_COUNT; i++)
    {
        reg_set(pLPDSData + i * (RegCount + 2), RegCount);
        reg_set(pLPDSData + i * (RegCount + 2) + 1, DDRPHY_BASE_ADDR + 0x210 + i * 0x80);

        for (j = 0; j < RegCount; j++)
        {
            RegVal = reg_get((unsigned int)DDRPHY_BASE_ADDR + 0x210 + i * 0x80 + j * 4);
            reg_set(pLPDSData + i * (RegCount + 2) + 0x2 + j, RegVal);
        }
    }

    pTmpAddr = pLPDSData + DDRPHY_ARRAY_COUNT * (RegCount + 2);

    for (i = 0; i < DDRPHY_ARRAY_COUNT; i++)
    {
        /* save (0x21c + 0x400), (0x220 + 0x400), (0x224 + 0x400) */
        RegCount = 3;
        reg_set(pTmpAddr, RegCount);
        reg_set(pTmpAddr + 1, DDRPHY_BASE_ADDR + 0x21c + i * 0x80 + 0x400);

        for (j = 0; j < RegCount; j++)
        {
            RegVal = reg_get((unsigned int)DDRPHY_BASE_ADDR + 0x21c + i * 0x80 + 0x400 + j * 4);
            reg_set(pTmpAddr + 0x2 + j, RegVal);
        }

        pTmpAddr += (RegCount + 2);

        /* save (0x240 + 0x400) */
        reg_set(pTmpAddr, 1);
        reg_set(pTmpAddr + 1, DDRPHY_BASE_ADDR + 0x240 + i * 0x80 + 0x400);

        RegVal = reg_get((unsigned int)DDRPHY_BASE_ADDR + 0x240 + i * 0x80 + 0x400);
        reg_set(pTmpAddr + 2, RegVal);

        pTmpAddr += 3;

        /* save 0x270 0x274 for ddr4*/
        RegCount = 2;
        reg_set(pTmpAddr, RegCount);
        reg_set(pTmpAddr + 1, DDRPHY_BASE_ADDR + 0x270 + i * 0x80);

        for (j = 0; j < RegCount; j++)
        {
            RegVal = reg_get((unsigned int)DDRPHY_BASE_ADDR + 0x270 + i * 0x80 + j * 4);
            reg_set(pTmpAddr + 0x2 + j, RegVal);
        }

        pTmpAddr += 4;
    }

    /* set (u32DDRBaseAddr + 0x70) bit 19 to 1 */
    reg_set(pTmpAddr, 1);
    reg_set(pTmpAddr + 1, DDRPHY_BASE_ADDR + 0x70);
    RegVal = reg_get((unsigned int)DDRPHY_BASE_ADDR + 0x70);
    RegVal |= 0x00080000;
    reg_set(pTmpAddr + 2, RegVal);

    /* set (u32DDRBaseAddr + 0x70) bit 19 to 0 */
    reg_set(pTmpAddr + 3, 1);
    reg_set(pTmpAddr + 4, DDRPHY_BASE_ADDR + 0x70);
    RegVal = reg_get((unsigned int)DDRPHY_BASE_ADDR + 0x70);
    RegVal &= 0xfff7ffff;
    reg_set(pTmpAddr + 5, RegVal);

    /* set (u32DDRBaseAddr + 0x04) bit 15 to 1 */
    reg_set(pTmpAddr + 6, 1);
    reg_set(pTmpAddr + 7, DDRPHY_BASE_ADDR + 0x04);
    RegVal = reg_get((unsigned int)DDRPHY_BASE_ADDR + 0x04);
    RegVal |= 0x8000;
    reg_set(pTmpAddr + 8, RegVal);

    /* set (u32DDRBaseAddr + 0x04) bit 15 to 0 */
    reg_set(pTmpAddr + 9, 1);
    reg_set(pTmpAddr + 10, DDRPHY_BASE_ADDR + 0x04);
    RegVal = reg_get((unsigned int)DDRPHY_BASE_ADDR + 0x04);
    RegVal &= 0xffff7fff;
    reg_set(pTmpAddr + 11, RegVal);

    /*  set the last value to 0, so bootrom will recognize the end */
    reg_set(pTmpAddr + 12, 0);

    return;
}

/******************LPDS Operational Data******************
****************HashValueLPDS   32Bytes
****************CEP              4Bytes
****************Reserved        16Bytes
****************CEP64            4Bytes
****************Reserved         8Bytes
****************HashValueDDR    32Bytes
****************CheckAreaNum     4Bytes
****************CheckAreaAddr0   4Bytes
****************CheckAreaSize0   4Bytes
                       ***
****************CheckAreaAddr15  4Bytes
****************CheckAreaSize1 5 4Bytes
**********************************************************/
static void Verify_DDR(void)
{
    OTP_PV_0_U up_otp_pv_0;

    unsigned int block_num = 1;
    unsigned int chk_addr[DDR_CHECK_MAX_NUM] = {0}; /* check start addr */
    unsigned int chk_size[DDR_CHECK_MAX_NUM] = {0}; /* check size */
    unsigned int cep = reg_get(ADDR_MCU_LPDS_START + CEP_Offset);//CEP
    unsigned int cep64 = reg_get(ADDR_MCU_LPDS_START + CEP64_Offset);//CEP64

    unsigned int pad_size = 0;
    unsigned int length = 0;
    unsigned char padding[128] = {0};
    unsigned char u8_hash[32] = {0};
    unsigned int u32_hash[8] = {0};
    unsigned int i;
    volatile int ret = 0;

    if (cep <= cep64)
    {
        chk_addr[0] = cep;
        chk_size[0] = (cep64 - cep) > 0x220000 ? (cep64 - cep + HASH_BLOCK_SIZE) : (0x220000);
    }
    else
    {
        chk_addr[0] = cep64;
        chk_size[0] = (cep - cep64) > 0x220000 ? (cep - cep64 + HASH_BLOCK_SIZE) : (0x220000);
    }

    //printf_hex(chk_addr[0]);
    //printf_hex(chk_size[0]);

    up_otp_pv_0.u32 = reg_get(OTPCTRL_PVINFO0);
    if(up_otp_pv_0.bits.auth_alg_sel)
    {
        HI_HASH_Init(HI_HASH_ALG_SM3);
    }
    else
    {
        HI_HASH_Init(HI_HASH_ALG_SHA256);
    }

    memset(padding, 0, 128);

    for (i = 0; i < block_num; i++)
    {
        ret = HI_HASH_Update(chk_addr[i], chk_size[i]);
        if (AUTH_SUCCESS != ret)
        {
            printf_str("DDR HI_HASH_Update error \n");
            return;
        }

        length += chk_size[i];
    }

    pad_size += HI_HASH_Padding(padding, pad_size, length);

    ret = HI_HASH_Final((unsigned int)padding, pad_size, u8_hash);
    if (AUTH_SUCCESS != ret)
    {
        printf_str("DDR HI_HASH_Final error \n");
        return;
    }

    reg_set(ADDR_MCU_LPDS_START + CheckAreaNum_Offset, block_num);

    for (i = 0; i < block_num; i++)
    {
        reg_set(ADDR_MCU_LPDS_START + CheckAreaAddr0_Offset + i * 8, chk_addr[i]);
        reg_set(ADDR_MCU_LPDS_START + CheckAreaSize0_Offset + i * 8, chk_size[i]);
    }

    u82u32(u32_hash, u8_hash, SHA256_LEN);

    for (i = 0; i < SHA256_LEN / 4; i++)
    {
        reg_set(ADDR_MCU_LPDS_START + HashValueDDR_Offset + i * 4, u32_hash[i]);
        //printf_hex(u32_hash[i]);
    }

    return;
}

static void Verify_LPDS(void)
{
    OTP_PV_0_U up_otp_pv_0;
    volatile int ret = 0;
    unsigned int pad_size = 0;
    unsigned int length = LPDS_VERIFY_LEN;
    unsigned char padding[128] = {0};
    unsigned char u8_hash[SHA256_LEN] = {0};
    unsigned int u32_hash[SHA256_LEN / 4] = {0};
    int i = 0;

    up_otp_pv_0.u32 = reg_get(OTPCTRL_PVINFO0);
    if(up_otp_pv_0.bits.auth_alg_sel)
    {
        HI_HASH_Init(HI_HASH_ALG_SM3);
    }
    else
    {
        HI_HASH_Init(HI_HASH_ALG_SHA256);
    }

    memset(padding, 0, 128);

    pad_size = length % HASH_BLOCK_SIZE;

    if((length - pad_size) != 0)
    {
        ret = HI_HASH_Update((unsigned int)(ADDR_MCU_LPDS_START + 0x20), length - pad_size);
        if (AUTH_SUCCESS != ret)
        {
            printf_str("LPDS HI_HASH_Update error \n");
            return;
        }
    }

    memcpy(padding, (void *)((unsigned int)(ADDR_MCU_LPDS_START + 0x20) + length - pad_size), pad_size);

    pad_size += HI_HASH_Padding(padding, pad_size, length);

    ret = HI_HASH_Final((unsigned int)padding, pad_size, u8_hash);
    if (AUTH_SUCCESS != ret)
    {
        printf_str("LPDS HI_HASH_Final error \n");
        return;
    }

    u82u32(u32_hash, u8_hash, SHA256_LEN);

    for (i = 0; i < SHA256_LEN / 4; i++)
    {
        reg_set(ADDR_MCU_LPDS_START + i * 4, u32_hash[i]);
        //printf_hex(u32_hash[i]);
    }

    return;
}


void DDREnterSelf(void)
{
    unsigned int regval = 0;

    /* Config DDR to self-refresh state */
    reg_set(DDRC0_BASE_ADDR + DDR_SREF, 0x01);

    /* Whether DDR change to self-refresh state */
    while (1)
    {
        regval = reg_get(DDRC0_BASE_ADDR + DDR_STATUS);
        if ((regval & 0x1) == 0x1) //bit0
        {
            break;
        }
    }

    wait_minute_2(10, 10);

    /* cs/ck/oe disable to reduce power */
    regval = reg_get(DDRPHY0_BASE_ADDR + 0x78);
    regval &= 0xffffff7f;
    reg_set(DDRPHY0_BASE_ADDR + 0x78, regval);

    reg_set(DDR_PHYCTRL0_28NM_ADDR, 0x2800);

    /* enable DDRPHY retention */
    regval = reg_get(REG_SC_BASE + DDR_PHY_ISO);
    regval &= 0xfffffffc;
    regval |= 0x02;
    reg_set(REG_SC_BASE + DDR_PHY_ISO, regval);
}

void ClockPowerDown(void)
{
    unsigned int RegValue = 0;

    //choose ddr timer to 24M
    reg_set(CRG_BASE_ADDR + 0x128, 0x304);
    reg_set(CRG_BASE_ADDR + 0x128, 0x704);

    //switch bus to 24M
    reg_set(CRG_BASE_ADDR + 0x58, 0x0);

    //APLL  power down
    reg_set(CRG_BASE_ADDR + 0x48, 0x204);
    reg_set(CRG_BASE_ADDR + 0x48, 0x604);

    RegValue= reg_get(CRG_BASE_ADDR + 0x04);
    reg_set(CRG_BASE_ADDR + 0x04, RegValue | 0x100000);

    //HPLL  power down
    RegValue= reg_get(CRG_BASE_ADDR + 0x2c);
    reg_set(CRG_BASE_ADDR + 0x2c, RegValue | 0x100000);

    //QPLL  power down.
    RegValue= reg_get(CRG_BASE_ADDR + 0x44);
    reg_set(CRG_BASE_ADDR + 0x44, RegValue | 0x100000);

    return;
}

int main(void)
{
    unsigned int ddr_wakeup_check_en;
    unsigned int ddr_wakeup_disable;
    unsigned int value;
    unsigned int cep = reg_get(ADDR_MCU_LPDS_START + CEP_Offset);//save CEP
    unsigned int cep64 = reg_get(ADDR_MCU_LPDS_START + CEP64_Offset);//save CEP64

    printf_str("ACPU suspend firmware ");

    value = reg_get(OTPCTRL_PVINFO0);
    ddr_wakeup_disable = (value >> 4) & 0x1;

    value = reg_get(OTPCTRL_PVINFO1);
    ddr_wakeup_check_en = (value >> 24) & 0x1;

    memset((void *)ADDR_MCU_LPDS_START, 0, LPDS_LEN);

    reg_set(ADDR_MCU_LPDS_START + CEP_Offset, cep);
    reg_set(ADDR_MCU_LPDS_START + CEP64_Offset, cep64);

    DDRPHYRegSave();

    if (NONSEC_ID_WORD != reg_get(REG_KLD_SEC_FLAG))
    {
        HI_CIPHER_Init();

        if((ddr_wakeup_disable == 0) && (ddr_wakeup_check_en == 1))
        {
            Verify_DDR();
        }

        Verify_LPDS();

        HI_CIPHER_DeInit();
    }

    DDREnterSelf();

    ClockPowerDown();

    //Notify C51 to standby
    reg_set(SC_GEN15, MCU_SUSPEND_FLAG);

    //enable MCU
    value = reg_get(MCU_START_CTRL);
    value |= 0x1;
    reg_set(MCU_START_CTRL, value);

    printf_str("exit\r\n");

    while(1)
    {
        dsb();
        isb();
        wfi();
    };
}

