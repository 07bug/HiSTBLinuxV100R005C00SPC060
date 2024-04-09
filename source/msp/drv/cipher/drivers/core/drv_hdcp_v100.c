/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_hdcp_v100.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_hdcp_v100.h"
#include "drv_symc_v100.h"
#include "drv_symc.h"
#include "drv_hdcp.h"

#ifdef CHIP_HDCP_VER_V100

/*************************** Internal Structure Definition ****************************/
/** \addtogroup      hdcp drivers*/
/** @{*/  /** <!-- [hdcp]*/

/*! Define the time out */
#define HDCP_TIME_OUT                   5000

/*! \HDCP ROOT KEY size 128bit*/
#define HDCP_ROOT_KEY_SIZE              (16)

typedef enum
{
    HDMI_WRITE_TX_HDCP_14 = 0x00,
    HDMI_WRITE_RX_HDCP_14 = 0x01,
    HDMI_WRITE_RX_HDCP_22 = 0x02,
}hdmi_ram_write_sel;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API Declaration *****************************/
/** \addtogroup      hdcp */
/** @{ */  /** <!--[hdcp]*/

static s32 drv_hdmi_write_enable(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel,
                                 u32 *hostkey)
{
    U_SEC_CHN_CFG cfg;
    U_HDCP_MODE_CTRL ctrl;
    u32 i = 0;

    /***
     * secure cpu use secure chn 0
     * non-secure cpu use non-secure chn 0
     * but non-secure can't write the non-secure chn configuration register
     * non-secure write the SEC_CHN_CFG will inoperative
     * */
    cfg.u32 = SYMC_READ(SEC_CHN_CFG);
    cfg.bits.sec_chn_cfg |= 0x01;
    SYMC_WRITE(SEC_CHN_CFG, cfg.u32);

    /* enable hdcp */
    ctrl.u32 = SYMC_READ(HDCP_MODE_CTRL);
    ctrl.bits.tx_read = 0x01;         /* hdcp 1.4 rx ram read enable */
    ctrl.bits.rx_read = 0x01;         /* hdcp 1.4 rx ram read enable */
    ctrl.bits.hdcp22_rx_read = 0x01;  /* hdcp 2.2 rx ram read enable */

    /* hdmi write ram sel */
    switch(ramsel)
    {
        case HDMI_RAM_SEL_NONE:
        {
            ctrl.bits.hdcp_mode_en = 0x00;    /* disable hdcp mode */
            ctrl.bits.tx_read = 0x01;         /* hdcp 1.4 rx ram read enable */
            ctrl.bits.rx_read = 0x01;         /* hdcp 1.4 rx ram read enable */
            ctrl.bits.hdcp22_rx_read = 0x01;  /* hdcp 2.2 rx ram read enable */
            break;
        }
        case HDMI_RAM_SEL_RX_14:
        {
            ctrl.bits.hdcp_mode_en = 0x01;               /* enable hdcp mode */
            ctrl.bits.rx_sel = HDMI_WRITE_RX_HDCP_14;    /* write to hdcp 1.4 rx ram */
            ctrl.bits.rx_read = 0x00;                    /* hdcp 1.4 rx ram write enable */
            break;
        }
        case HDMI_RAM_SEL_TX_14:
        {
            ctrl.bits.hdcp_mode_en = 0x01;               /* enable hdcp mode */
            ctrl.bits.rx_sel = HDMI_WRITE_TX_HDCP_14;    /* write to hdcp 1.4 tx ram */
            ctrl.bits.tx_read = 0x00;                    /* hdcp 1.4 tx ram write enable */
            break;
        }
        case HDMI_RAM_SEL_RX_22:
        {
            ctrl.bits.hdcp_mode_en = 0x01;            /* enable hdcp mode */
            ctrl.bits.rx_sel = HDMI_WRITE_RX_HDCP_22; /* write to hdcp 2.2 rx ram */
            ctrl.bits.hdcp22_rx_read = 0x00;          /* hdcp 2.2 rx ram write enable */
            break;
        }
        default:
        {
            HI_LOG_ERROR("error, invalid hdcp ram sel %d\n", ramsel);
            return HI_ERR_CIPHER_INVALID_PARA;
        }
    }
    /* hdcp root key sel */
    ctrl.bits.hdcp_rootkey_sel = keysel;
    SYMC_WRITE(HDCP_MODE_CTRL, ctrl.u32);
    HI_LOG_INFO("HDCP_MODE_CTRL 0x%x\n", ctrl.u32);

    /* write host cpu key */
    for (i=0; i< HDCP_ROOT_KEY_SIZE; i+=4)
    {
        if ((HDCP_KEY_SEL_HOST == keysel) && (HI_NULL != hostkey))
        {
            SYMC_WRITE(REG_CIPHER_KEY(0) + i, hostkey[i/4]);
        }
        SYMC_WRITE(CHAN0_CIPHER_IV + i, 0x00);
    }

    return HI_SUCCESS;
}

static void drv_hdmi_read_enable(void)
{
    U_HDCP_MODE_CTRL ctrl;

    ctrl.u32 = SYMC_READ(HDCP_MODE_CTRL);
    ctrl.bits.hdcp_mode_en = 0x00;    /* disable hdcp mode */
    ctrl.bits.tx_read = 0x01;         /* hdcp 1.4 rx ram read enable */
    ctrl.bits.rx_read = 0x01;         /* hdcp 1.4 rx ram read enable */
    ctrl.bits.hdcp22_rx_read = 0x01;  /* hdcp 2.2 rx ram read enable */
    SYMC_WRITE(HDCP_MODE_CTRL, ctrl.u32);
    HI_LOG_INFO("HDCP_MODE_CTRL 0x%x\n", ctrl.u32);
}

static void drv_hdcp_aes_cbc_config(u32 decrypt)
{
    U_CHAN0_CIPHER_CTRL chn0_ctrl;

    /* AES-128 CBC */
    chn0_ctrl.u32 = SYMC_READ(CHAN0_CIPHER_CTRL);
    chn0_ctrl.bits.mode = SYMC_MODE_CBC;
    chn0_ctrl.bits.alg_sel = SYMC_ALG_AES;
    chn0_ctrl.bits.decrypt = decrypt;
    chn0_ctrl.bits.width = 0x00;
    chn0_ctrl.bits.key_length = SYMC_KEY_DEFAULT;
    chn0_ctrl.bits.key_sel = 0x00;
    chn0_ctrl.bits.ivin_sel = 0x01;
    chn0_ctrl.bits.key_adder = 0x00;

    SYMC_WRITE(CHAN0_CIPHER_CTRL, chn0_ctrl.u32);
    HI_LOG_INFO("CHAN0_CIPHER_CTRL 0x%x\n", chn0_ctrl.u32);
}

static s32 drv_hdcp_aes_cbc_done(void)
{
    U_CIPHER_REG_CHAN0_CFG chn0_cfg;
    U_CHAN0_CIPHER_CTRL chn0_ctrl;
    u32 timeout = 0x00;

    /* start */
    chn0_cfg.u32 = SYMC_READ(CIPHER_REG_CHAN0_CFG);
    chn0_cfg.bits.ch0_start = 0x01;
    SYMC_WRITE(CIPHER_REG_CHAN0_CFG, chn0_cfg.u32);

    /* wait done */
    chn0_cfg.u32 = SYMC_READ(CIPHER_REG_CHAN0_CFG);
    while(chn0_cfg.bits.ch0_busy)
    {
        if (HDCP_TIME_OUT <= timeout++)
        {
            HI_LOG_ERROR("error, hdcp wait done time out\n");
            return HI_ERR_CIPHER_TIMEOUT;
        }
        crypto_udelay(1);
        chn0_cfg.u32 = SYMC_READ(CIPHER_REG_CHAN0_CFG);
    }

    /* don't update iv any more */
    chn0_ctrl.u32 = SYMC_READ(CHAN0_CIPHER_CTRL);
    chn0_ctrl.bits.ivin_sel = 0x00;
    SYMC_WRITE(CHAN0_CIPHER_CTRL, chn0_ctrl.u32);

    return HI_SUCCESS;
}

s32 drv_hdcp_encrypt(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, u32 *hostkey,
                 u32 *in, u32 *out, u32 len, u32 decrypt)
{
    u32 i = 0, j = 0, din = 0, dout = 0;
    u32 count = 0;
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(0x00 != len % AES_BLOCK_SIZE);

    HI_LOG_INFO("keysel 0x%x, ramsel 0x%x, decrypt 0x%x\n", keysel, ramsel, decrypt);

    /* hdcp mode configuration */
    ret = drv_hdmi_write_enable(keysel, ramsel, hostkey);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(drv_hdmi_write_enable, ret);
        return ret;
    }

    /* aes cbc configuration */
    drv_hdcp_aes_cbc_config(decrypt);

    count = len / AES_BLOCK_SIZE;
    for (i = 0; i < count; i++)
    {
        /* write input data */
        for (j=0; j<AES_BLOCK_SIZE; j+=4)
        {
            SYMC_WRITE(CHAN0_CIPHER_DIN + j, in[din++]);
        }

        /* start and wait done */
        ret = drv_hdcp_aes_cbc_done();
        if (HI_SUCCESS != ret)
        {
            HI_LOG_PrintFuncErr(drv_hdcp_aes_cbc_done, ret);
            return ret;
        }

        /* read ouptut data, hdcp decrypt operation can't read ouptut */
        if (HI_NULL != out)
        {
            for (j=0; j<AES_BLOCK_SIZE; j+=4)
            {
                out[dout++] = SYMC_READ(CHAN0_CIPHER_DOUT + j);
            }
        }
    }

    /* enable hdmi ram read */
    drv_hdmi_read_enable();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

void drv_hdcp_get_capacity(hdcp_capacity *capacity)
{
    crypto_memset(capacity, sizeof(hdcp_capacity), 0,  sizeof(hdcp_capacity));

    capacity->hdcp = CRYPTO_CAPACITY_SUPPORT;

    return;
}

/** @} */  /** <!-- ==== API declaration end ==== */

#endif //End of CHIP_HDCP_VER_V100
