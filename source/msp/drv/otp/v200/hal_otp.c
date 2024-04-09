/******************************************************************************

  Copyright (C), 2016, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_otp.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       :
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include <linux/delay.h>
#include <linux/kernel.h>
#include <asm/io.h>
#include "hi_drv_reg.h"
#include "hi_type.h"
#include "hal_otp.h"
#include "hi_drv_otp.h"

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
extern HI_BOOL DRV_OTP_IsFakeOTPAccessErr_Flag(HI_VOID);
extern HI_BOOL DRV_OTP_IsFakeOTPBuffer_Flag(HI_VOID);
extern HI_S32 DRV_OTP_FakeOTP_ReadByte(HI_U32 addr);
extern HI_S32 DRV_OTP_FakeOTP_WriteByte(HI_U32 addr, HI_U8 value);

#define DRV_FAKE_OTP_ACCESSERR_CHECK() do{                          \
        if(DRV_OTP_IsFakeOTPAccessErr_Flag() == HI_TRUE)            \
        {                                                           \
            HI_FATAL_OTP("OTP Access Error Mode\n");                \
            return HI_FAILURE;                                      \
        }                                                           \
    }while(0)

#endif
/******* proc function end   ********/

static HI_VOID otp_write_reg(HI_U32 addr, HI_U32 val)
{
    HI_U8 *pu8VirAddr = HI_NULL;
    pu8VirAddr = (HI_U8 *)ioremap_nocache(addr, 0x10);
    if (HI_NULL == pu8VirAddr)
    {
        OTP_PrintErrorCode(HI_ERR_OTP_MEM_MAP);
        return ;
    }
    HI_REG_WRITE32(pu8VirAddr, val);
    iounmap(pu8VirAddr);
    return;
}

static HI_U32 otp_read_reg(HI_U32 addr)
{
    HI_U32 val = 0;
    HI_U8 *pu8VirAddr = HI_NULL;

    pu8VirAddr = (HI_U8 *)ioremap_nocache(addr, 0x10);
    if (HI_NULL == pu8VirAddr)
    {
        OTP_PrintErrorCode(HI_ERR_OTP_MEM_MAP);
        return HI_ERR_OTP_MEM_MAP;
    }
    HI_REG_READ32(pu8VirAddr, val);
    iounmap(pu8VirAddr);
    return val;
}

static HI_S32 s_check_error_status(HI_VOID)
{
    OTP_CTR_ST0_U st0;

    st0.u32 = 0;
    st0.u32 = otp_read_reg(OTP_CTR_ST0);

    if (0 == st0.bits.otp_init_rdy)
    {
        OTP_PrintErrorCode(HI_ERR_OTP_NOT_INITRDY);
        return HI_ERR_OTP_NOT_INITRDY;
    }
    else if (1 == st0.bits.err)
    {
        OTP_PrintWarnCode(HI_ERR_OTP_PROG_PERM);
        return HI_ERR_OTP_PROG_PERM;
    }
    else if (1 == st0.bits.prm_rd_fail)
    {
        OTP_PrintErrorCode(HI_ERR_OTP_FAIL_PRMRD);
        return HI_ERR_OTP_FAIL_PRMRD;
    }
    else if (1 == st0.bits.rd_fail)
    {
        OTP_PrintErrorCode(HI_ERR_OTP_FAIL_RD);
        return HI_ERR_OTP_FAIL_RD;
    }
    else if (1 == st0.bits.prog_disable)
    {
        OTP_PrintErrorCode(HI_ERR_OTP_DISABLE_PROG);
        return HI_ERR_OTP_DISABLE_PROG;
    }
    else
    {
        return HI_SUCCESS;
    }
}

static void s_wait_ctrl_idle(HI_VOID)
{
    HI_U32 reg_data[1] = {0};

    reg_data[0] = otp_read_reg(OTP_RW_CTRL);
    while ((*reg_data & 0x1) == 0x1)
    {
        reg_data[0] = otp_read_reg(OTP_RW_CTRL);
    }

    return;
}

HI_S32 HAL_OTP_Reset(HI_VOID)
{
    HI_U32 reg_data[1] = {0};
    HI_U32 cnt = 0;

    OTP_FUNC_ENTER();
    otp_write_reg(OTP_SH_UPDATE, 0x1);

    reg_data[0] = otp_read_reg(OTP_CTR_ST0);
    while ((*reg_data & 0x2) == 0x0)        //2b'10
    {
        reg_data[0] = otp_read_reg(OTP_CTR_ST0);
        cnt ++;
        udelay(10*100);
        if(cnt >= 100)
        {
            OTP_PrintErrorCode(HI_ERR_OTP_TIMEOUT);
            return HI_ERR_OTP_TIMEOUT;
        }
    }
    OTP_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HAL_OTP_Init(HI_VOID)
{
    HI_U32 reg_data[1] = {0};
    HI_U32 cnt = 0;

    OTP_FUNC_ENTER();
    reg_data[0] = otp_read_reg(OTP_CTR_ST0);
    while ((*reg_data & 0x1) == 0x0)
    {
        reg_data[0] = otp_read_reg(OTP_CTR_ST0);
        cnt ++;
        udelay(10*100);
        if(cnt >= 100)
        {
            OTP_PrintErrorCode(HI_ERR_OTP_TIMEOUT);
            return HI_ERR_OTP_TIMEOUT;
        }
    }
    OTP_FUNC_EXIT();
    return HI_SUCCESS;
}

/******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
HI_S32 HAL_OTP_ProcRead(HI_U32 addr, HI_U32 *value)
{
    HI_U32 read1, read2, ramdom;

    OTP_FUNC_ENTER();
    CHECK_NULL_PTR(value);
    otp_write_reg(OTP_RADDR, addr);
    otp_write_reg(OTP_RW_CTRL, 0x3);
    s_wait_ctrl_idle();

    ramdom = otp_read_reg(RNG_BASE + RNG_FIFO_DATA);
    usleep_range(((ramdom & 0xFF) / 2), (ramdom & 0xFF));
    read1 = otp_read_reg(OTP_RDATA);

    ramdom = otp_read_reg(RNG_BASE + RNG_FIFO_DATA);
    usleep_range(((ramdom & 0xFF) / 2), (ramdom & 0xFF));
    read2 = otp_read_reg(OTP_RDATA);

    if (read1 != read2)
    {
        *value = 0;
        OTP_PrintErrorCode(HI_ERR_OTP_FAIL_RD);
        return HI_ERR_OTP_FAIL_RD;
    }

    *value = read1;
    OTP_FUNC_EXIT();
    return s_check_error_status();
}

HI_S32 HAL_OTP_ProcReadByte(HI_U32 addr, HI_U8 *value)
{
    HI_S32 ret = 0;
    HI_U32 v = 0;
    HI_U32 addr_e = 0;

    OTP_FUNC_ENTER();
    CHECK_NULL_PTR(value);
    addr_e = addr & (~0x3);
    ret = HAL_OTP_ProcRead(addr_e, &v);
    if (HI_SUCCESS != ret)
    {
        return HI_ERR_OTP_FAIL_RD;
    }
    *value = (v >> ((addr & 0x3) * 8)) & 0xff ;
    OTP_FUNC_EXIT();
    return HI_SUCCESS;
}
#endif
/******* proc function end   ********/

HI_S32 HAL_OTP_Read(HI_U32 addr, HI_U32 *value)
{
    HI_U32 read1, read2, ramdom;

    OTP_FUNC_ENTER();
    /******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    DRV_FAKE_OTP_ACCESSERR_CHECK();
    if (DRV_OTP_IsFakeOTPBuffer_Flag() == HI_TRUE)
    {
        HI_U32 val = 0;

        val = DRV_OTP_FakeOTP_ReadByte(addr + 0x00)
              + DRV_OTP_FakeOTP_ReadByte(addr + 0x01) * 0x100
              + DRV_OTP_FakeOTP_ReadByte(addr + 0x02) * 0x10000
              + DRV_OTP_FakeOTP_ReadByte(addr + 0x03) * 0x1000000;
        * value = val;
        return HI_SUCCESS;
    }
#endif
    /******* proc function end   ********/
    CHECK_NULL_PTR(value);
    otp_write_reg(OTP_RADDR, addr);
    otp_write_reg(OTP_RW_CTRL, 0x3);
    s_wait_ctrl_idle();

    ramdom = otp_read_reg(RNG_BASE + RNG_FIFO_DATA);
    usleep_range(((ramdom & 0xFF) / 2), (ramdom & 0xFF));
    read1 = otp_read_reg(OTP_RDATA);

    ramdom = otp_read_reg(RNG_BASE + RNG_FIFO_DATA);
    usleep_range(((ramdom & 0xFF) / 2), (ramdom & 0xFF));
    read2 = otp_read_reg(OTP_RDATA);
    if (read1 != read2)
    {
        *value = 0;
        OTP_PrintErrorCode(HI_ERR_OTP_FAIL_RD);
        return HI_ERR_OTP_FAIL_RD;
    }

    *value = read1;
    OTP_FUNC_EXIT();
    return s_check_error_status();
}

HI_S32 HAL_OTP_Write(HI_U32 addr, HI_U32 value)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 i = 0;

    OTP_FUNC_ENTER();
    OTP_CHECK_PARAM((addr & 0x03) != 0);
    for(i = 0; i < 4; i ++)
    {
        ret = HAL_OTP_WriteByte(addr + i, (value >> 8*i) & 0xFF);
        if (HI_SUCCESS != ret)
        {
            OTP_PrintErrorFunc(HAL_OTP_WriteByte, ret);
            return ret;
        }
    }
    OTP_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HAL_OTP_ReadByte(HI_U32 addr, HI_U8 *value)
{
    HI_S32 ret = 0;
    HI_U32 v = 0;
    HI_U32 addr_e = 0;

    OTP_FUNC_ENTER();
    CHECK_NULL_PTR(value);
    addr_e = addr & (~0x3);
    ret = HAL_OTP_Read(addr_e, &v);
    if (HI_SUCCESS != ret)
    {
        OTP_PrintErrorFunc(HAL_OTP_Read, ret);
        return ret;
    }
    *value = (v >> ((addr & 0x3) * 8)) & 0xff;
    OTP_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HAL_OTP_WriteByte(HI_U32 addr, HI_U8 value)
{
    HI_S32 ret = HI_FAILURE;

    OTP_FUNC_ENTER();
    /******* proc function begin ********/
#ifdef HI_PROC_SUPPORT
    DRV_FAKE_OTP_ACCESSERR_CHECK();
    if (DRV_OTP_IsFakeOTPBuffer_Flag() == HI_TRUE)
    {
        HI_U8 val = 0;
        val = value & 0xFF;
        return DRV_OTP_FakeOTP_WriteByte(addr, val);
    }
#endif
    /******* proc function end   ********/
    otp_write_reg(OTP_WDATA, value);
    otp_write_reg(OTP_WADDR, addr);
    otp_write_reg(OTP_RW_CTRL, 0x5);
    s_wait_ctrl_idle();

    ret = s_check_error_status();
    if(ret == HI_SUCCESS)
    {
        OTP_READABLE(addr, value);
    }
    OTP_FUNC_EXIT();
    return ret;
}

HI_S32 HAL_OTP_WriteBit(HI_U32 addr, HI_U32 bit_pos, HI_U32 bit_value)
{
    HI_U8 data = 0;
    HI_U8 rd_data = 0;
    HI_S32 ret = HI_FAILURE;

    OTP_FUNC_ENTER();
    if (bit_value == 1)
    {
        data = (1 << bit_pos);
        ret = HAL_OTP_WriteByte(addr, data);
        if(HI_SUCCESS != ret)
        {
            return ret;
        }
        if(addr < 0x40)
        {
            ret = HAL_OTP_ReadByte(addr, &rd_data);
            if(HI_SUCCESS != ret)
            {
                return ret;
            }
            if((data & rd_data) != data)
            {
                return HI_ERR_OTP_FAILED_AUTH;
            }
        }
    }
    else
    {
        //Do nothing when bit_value is 0.
    }
    OTP_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HAL_OTP_ReadBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 *value)
{
    HI_S32 ret = 0;
    HI_U8 data = 0;

    OTP_FUNC_ENTER();
    OTP_CHECK_PARAM(start_bit + bit_width > 8);

    ret = HAL_OTP_ReadByte(addr, &data);
    if (HI_SUCCESS != ret)
    {
        OTP_PrintErrorFunc(HAL_OTP_ReadByte, ret);
        return ret;
    }
    data &= GENMASK_U(start_bit + bit_width - 1, start_bit);
    *value = data >> start_bit;
    OTP_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_S32 HAL_OTP_WriteBitsOnebyte(HI_U32 addr, HI_U32 start_bit, HI_U32 bit_width, HI_U8 value)
{
    HI_U8 data = 0;
    HI_U8 rd_data = 0;
    HI_S32 ret = HI_FAILURE;

    OTP_FUNC_ENTER();
    OTP_CHECK_PARAM(start_bit + bit_width > 8);

    data = (value << start_bit) & GENMASK_U(start_bit + bit_width - 1, start_bit);

    ret = HAL_OTP_WriteByte(addr, data);
    if (HI_SUCCESS != ret)
    {
        OTP_PrintErrorFunc(HAL_OTP_WriteByte, ret);
        return ret;
    }
    if(addr < 0x40)
    {
        ret = HAL_OTP_ReadByte(addr, &rd_data);
        if(HI_SUCCESS != ret)
        {
            return ret;
        }
        if((data & rd_data) != data)
        {
            return HI_ERR_OTP_FAILED_AUTH;
        }
    }
    OTP_FUNC_EXIT();
    return HI_SUCCESS;
}

HI_U32 HAL_OTP_Export_Read(HI_U32 addr)
{
    HI_U32 value = 0;
    HI_S32 ret = 0;

    OTP_FUNC_ENTER();
    ret = HAL_OTP_Read(addr, &value);
    if (HI_SUCCESS != ret)
    {
        OTP_PrintErrorFunc(HAL_OTP_Read, ret);
    }
    OTP_FUNC_EXIT();
    return value;
}

HI_U8 HAL_OTP_Export_ReadByte(HI_U32 addr)
{
    HI_U8 value = 0;
    HI_S32 ret = 0;

    OTP_FUNC_ENTER();
    ret = HAL_OTP_ReadByte(addr, &value);
    if (HI_SUCCESS != ret)
    {
        OTP_PrintErrorFunc(HAL_OTP_Read, ret);
    }
    OTP_FUNC_EXIT();
    return value;
}

EXPORT_SYMBOL(HAL_OTP_Read);
EXPORT_SYMBOL(HAL_OTP_ReadByte);
EXPORT_SYMBOL(HAL_OTP_Write);
EXPORT_SYMBOL(HAL_OTP_WriteByte);
EXPORT_SYMBOL(HAL_OTP_WriteBit);
