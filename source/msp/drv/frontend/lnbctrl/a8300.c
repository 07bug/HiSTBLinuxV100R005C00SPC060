#include <linux/delay.h>
#include "drv_lnbctrl.h"
#include "drv_demod.h"
#include "hi_drv_gpio.h"

#include "drv_tuner_ext.h"
#include "hi_drv_i2c.h"
#include "a8300.h"

#define A8300_ADDR (0x10)
#define A8300_CTRL_REG0_ADDR (0)
#define A8300_CTRL_REG1_ADDR (1)

#define A8300_STATUS_REG0_ADDR (0)

#define A8300_I2C_WRITE_TIMES (1)


static HI_BOOL s_bA8300Inited = HI_FALSE;
static HI_U8 s_u8Reg1Data = 0;
static HI_U8 s_u8Reg2Data = 0;
static HI_U32 s_u32A8300Port = 0;



HI_S32 a8300_read_byte(LNBCTRL_DEV_PARAM_S* pstParam, HI_U8 u8RegAddr, HI_U8 *pu8RegVal)
{
    HI_S32 s32Ret = HI_SUCCESS;


    if (HI_NULL == pu8RegVal)
    {
        HI_ERR_TUNER("pointer is null\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    s32Ret = HI_DRV_I2C_Read_2Stop(pstParam->u32I2CNum, pstParam->u8DevAddr, u8RegAddr, 1, pu8RegVal, 1);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("A8300 read i2c 0x%02x failed.\n", *pu8RegVal);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 a8300_write_byte(LNBCTRL_DEV_PARAM_S* pstParam, HI_U8 u8RegAddr, HI_U8 u8RegVal)
{
    HI_S32 s32Ret = HI_SUCCESS;


    s32Ret = HI_DRV_I2C_Write(pstParam->u32I2CNum, pstParam->u8DevAddr, u8RegAddr, 1, &u8RegVal, 1);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("A8300 write i2c failed, %x\n", s32Ret);
        return HI_FAILURE;
    }

    HI_INFO_TUNER("A8300 write i2c 0x%02x ok.\n", u8RegVal);
    return HI_SUCCESS;
}

HI_VOID a8300_rw_test(LNBCTRL_DEV_PARAM_S* pstParam)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 u8RegVal = 0;

    s32Ret = a8300_write_byte(pstParam, A8300_CTRL_REG0_ADDR, 0x12);
    s32Ret |= a8300_read_byte(pstParam, A8300_STATUS_REG0_ADDR, &u8RegVal);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("a8300_read/write_byte 0x%x failed.\n", u8RegVal);
        return;
    }
}

HI_S32 a8300_init(HI_U32 u32TunerPort, HI_U32 u32I2CNum, HI_U8 u8DevAddr, HI_UNF_DEMOD_DEV_TYPE_E enDemodDevType)
{
    LNBCTRL_DEV_PARAM_S* pstParam;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U8 u8RegVal = 0x80;

    if (s_bA8300Inited)
    {
        return HI_SUCCESS;
    }

    s_u8Reg1Data = 0;
    s_u8Reg2Data = 0;

    /* 添加一个node,所有port共用一个 pstParam*/
    s_u32A8300Port = u32TunerPort;
    pstParam = lnbctrl_queue_get(s_u32A8300Port);
    if (HI_NULL == pstParam)
    {
        pstParam = lnbctrl_queue_insert(s_u32A8300Port, u32I2CNum, u8DevAddr, enDemodDevType);
        if (HI_NULL == pstParam)
        {
            HI_ERR_TUNER("lnbctrl_queue_insert failed.\n");
            return HI_FAILURE;
        }
    }

    if (!pstParam->bInited)
    {
        //初始化,寄存器写0。如果不先读一下寄存器的话，首次写入会失效，原因待查。
        s32Ret = a8300_read_byte(pstParam, A8300_STATUS_REG0_ADDR, &u8RegVal);
        s32Ret |= a8300_write_byte(pstParam, A8300_STATUS_REG0_ADDR, 0);

        u8RegVal = s_u8Reg1Data;
        u8RegVal |= 0x20;      //22k波形由外部产生
        s32Ret = a8300_write_byte(pstParam, A8300_CTRL_REG0_ADDR, u8RegVal);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("a8300_write_byte 0x%x failed.\n", u8RegVal);
            return HI_FAILURE;
        }
        s_u8Reg1Data = u8RegVal;

        pstParam->bInited = HI_TRUE;
    }

    s_bA8300Inited = HI_TRUE;

    return HI_SUCCESS;
}


HI_S32 a8300_deInit(HI_U32 u32TunerPort)
{
    LNBCTRL_DEV_PARAM_S* pstParam;
    HI_S32 s32Ret = HI_SUCCESS;


    /* Find node */
    pstParam = lnbctrl_queue_get(s_u32A8300Port);
    if (HI_NULL == pstParam)
    {
        HI_ERR_TUNER("lnbctrl_queue_get failed.\n");
        return HI_FAILURE;
    }

    /* A8300 power off */
    s32Ret = a8300_lnbctrl_power(s_u32A8300Port, 0);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("a8300_lnbctrl_power0 failed.\n");
        return HI_FAILURE;
    }

    lnbctrl_queue_remove(s_u32A8300Port);
    s_bA8300Inited = HI_FALSE;
    s_u8Reg1Data = 0;
    s_u8Reg2Data = 0;
    s_u32A8300Port = 0;

    return HI_SUCCESS;
}

HI_S32 a8300_standby(HI_U32 u32TunerPort, HI_U32 u32Standby)
{
    return HI_SUCCESS;
}

HI_S32 a8300_lnbctrl_power(HI_U32 u32TunerPort, HI_U8 u8Power)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 u8RegVal = 0;
    LNBCTRL_DEV_PARAM_S* pstParam;


    /* Find node */
    pstParam = lnbctrl_queue_get(s_u32A8300Port);
    if (HI_NULL == pstParam)
    {
        HI_ERR_TUNER("lnbctrl_queue_get failed.\n");
        return HI_FAILURE;
    }

    u8RegVal = s_u8Reg1Data;
    if (u8Power == 0)
    {
        u8RegVal &= 0xe0;
    }
    else
    {
        u8RegVal |= 0x10;
    }

    s32Ret = a8300_write_byte(pstParam, A8300_CTRL_REG0_ADDR, u8RegVal);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_TUNER("a8300_write_byte failed.\n");
        return HI_FAILURE;
    }

    s_u8Reg1Data = u8RegVal;

    return HI_SUCCESS;
}

HI_S32 a8300_set_lnb_out(HI_U32 u32TunerPort, TUNER_LNB_OUT_E enOut)
{
    HI_S32 s32Ret = HI_FAILURE;
    LNBCTRL_DEV_PARAM_S* pstParam;
    HI_U8 u8Reg = 0;

    pstParam = lnbctrl_queue_get(s_u32A8300Port);
    if (HI_NULL == pstParam)
    {
        HI_ERR_TUNER("lnbctrl_queue_get failed.\n");
        return HI_FAILURE;
    }

    if (!pstParam->bInited)
    {
        HI_ERR_TUNER("pstParam uninited.\n");
        return HI_FAILURE;
    }

    u8Reg = s_u8Reg1Data;
    switch(enOut)
    {
        case TUNER_LNB_OUT_0V:
        case TUNER_LNB_OUT_BUTT:
        {
            u8Reg &= 0xe0;
            break;
        }
        case TUNER_LNB_OUT_13V:
        {
            u8Reg &= 0xe0;
            u8Reg |= 0x12;
            break;
        }
        case TUNER_LNB_OUT_14V:
        {
            u8Reg &= 0xe0;
            u8Reg |= 0x13;
            break;
        }
        case TUNER_LNB_OUT_18V:
        {
            u8Reg &= 0xe0;
            u8Reg |= 0x1b;
            break;
        }
        case TUNER_LNB_OUT_19V:
        {
            u8Reg &= 0xe0;
            u8Reg |= 0x1c;
            break;
        }
        default:
        {
            HI_ERR_TUNER("Unkown enout: %d.\n", enOut);
            return HI_FAILURE;
        }
    }

    s32Ret = a8300_write_byte(pstParam, A8300_CTRL_REG0_ADDR, u8Reg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("a8300_write_byte 0x%x failed.\n", u8Reg);
        return HI_FAILURE;
    }

    s_u8Reg1Data = u8Reg;

    return HI_SUCCESS;
}

HI_S32 a8300_send_continuous_22K(HI_U32 u32TunerPort, HI_U32 u32Continuous22K)
{
    return HI_SUCCESS;
}

HI_S32 a8300_send_tone(HI_U32 u32TunerPort, HI_U32 u32Tone)
{
    return HI_SUCCESS;
}

HI_S32 a8300_DiSEqC_send_msg(HI_U32 u32TunerPort, HI_UNF_TUNER_DISEQC_SENDMSG_S *pstSendMsg)
{
    return HI_SUCCESS;
}

HI_S32 a8300_DiSEqC_recv_msg(HI_U32 u32TunerPort, HI_UNF_TUNER_DISEQC_RECVMSG_S *pstRecvMsg)
{
    return HI_SUCCESS;
}


