/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_hdcp_v200.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_hdcp_v200.h"
#include "drv_symc_v200.h"
#include "drv_symc.h"
#include "drv_hdcp.h"

#ifdef CHIP_HDCP_VER_V200

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
    cfg.bits.cipher_sec_chn_cfg |= 0x01;
    SYMC_WRITE(SEC_CHN_CFG, cfg.u32);

    /* enable hdcp */
    ctrl.u32 = SYMC_READ(HDCP_MODE_CTRL);
    ctrl.bits.hdmi_tx_hdcp14_wr_en = 0x01;  /* hdcp 1.4 rx ram read enable */
    ctrl.bits.hdmi_rx_hdcp14_wr_en = 0x01;  /* hdcp 1.4 rx ram read enable */
    ctrl.bits.hdmi_rx_hdcp22_wr_en = 0x01;  /* hdcp 2.2 rx ram read enable */

    /* hdmi write ram sel */
    switch(ramsel)
    {
        case HDMI_RAM_SEL_NONE:
        {
            ctrl.bits.hdcp_mode_en = 0x00;          /* disable hdcp mode */
            ctrl.bits.hdmi_tx_hdcp14_wr_en = 0x01;  /* hdcp 1.4 rx ram read enable */
            ctrl.bits.hdmi_rx_hdcp14_wr_en = 0x01;  /* hdcp 1.4 rx ram read enable */
            ctrl.bits.hdmi_rx_hdcp22_wr_en = 0x01;  /* hdcp 2.2 rx ram read enable */
            break;
        }
        case HDMI_RAM_SEL_RX_14:
        {
            ctrl.bits.hdcp_mode_en = 0x01;                 /* enable hdcp mode */
            ctrl.bits.hdcp_wr_sel = HDMI_WRITE_RX_HDCP_14; /* write to hdcp 1.4 rx ram */
            ctrl.bits.hdmi_rx_hdcp14_wr_en = 0x00;         /* hdcp 1.4 rx ram write enable */
            break;
        }
        case HDMI_RAM_SEL_TX_14:
        {
            ctrl.bits.hdcp_mode_en = 0x01;                 /* enable hdcp mode */
            ctrl.bits.hdcp_wr_sel = HDMI_WRITE_TX_HDCP_14; /* write to hdcp 1.4 tx ram */
            ctrl.bits.hdmi_tx_hdcp14_wr_en = 0x00;         /* hdcp 1.4 tx ram write enable */
            break;
        }
        case HDMI_RAM_SEL_RX_22:
        {
            ctrl.bits.hdcp_mode_en = 0x01;                 /* enable hdcp mode */
            ctrl.bits.hdcp_wr_sel = HDMI_WRITE_RX_HDCP_22; /* write to hdcp 2.2 rx ram */
            ctrl.bits.hdmi_rx_hdcp22_wr_en = 0x00;         /* hdcp 2.2 rx ram write enable */
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

    /* write host cpu even key */
    SYMC_WRITE(ODD_EVEN_KEY_SEL, 0x00); /* even key */
    for (i=0; i< HDCP_ROOT_KEY_SIZE; i+=4)
    {
        if ((HDCP_KEY_SEL_HOST == keysel) && (HI_NULL != hostkey))
        {
            SYMC_WRITE(CIPHER_KEY(0) + i, hostkey[i/4]);
        }
        SYMC_WRITE(CHAN0_CIPHER_IV + i, 0x00);
    }

    return HI_SUCCESS;
}

static void drv_hdmi_read_enable(void)
{
    U_HDCP_MODE_CTRL ctrl;

    ctrl.u32 = SYMC_READ(HDCP_MODE_CTRL);
    ctrl.bits.hdcp_mode_en = 0x00;          /* disable hdcp mode */
    ctrl.bits.hdmi_tx_hdcp14_wr_en = 0x01;  /* hdcp 1.4 rx ram read enable */
    ctrl.bits.hdmi_rx_hdcp14_wr_en = 0x01;  /* hdcp 1.4 rx ram read enable */
    ctrl.bits.hdmi_rx_hdcp22_wr_en = 0x01;  /* hdcp 2.2 rx ram read enable */
    SYMC_WRITE(HDCP_MODE_CTRL, ctrl.u32);
    HI_LOG_INFO("HDCP_MODE_CTRL 0x%x\n", ctrl.u32);
}

static void drv_hdcp_aes_cbc_config(u32 decrypt)
{
    U_CHAN0_CIPHER_CTRL chn0_ctrl;

    /* AES-128 CBC */
    chn0_ctrl.u32 = SYMC_READ(CHAN0_CIPHER_CTRL);
    chn0_ctrl.bits.sym_ch0_alg_mode = SYMC_MODE_CBC;
    chn0_ctrl.bits.sym_ch0_alg_sel = SYMC_ALG_AES;
    chn0_ctrl.bits.sym_ch0_decrypt = decrypt;
    chn0_ctrl.bits.sym_ch0_dat_width = 0x00;
    chn0_ctrl.bits.sym_ch0_key_length = SYMC_KEY_DEFAULT;
    chn0_ctrl.bits.sym_ch0_key_sel = 0x00;
    chn0_ctrl.bits.sym_ch0_ivin_sel = 0x01;
    chn0_ctrl.bits.sym_ch0_sm1_round_num = 0;
    chn0_ctrl.bits.sym_ch0_start = 0;

    SYMC_WRITE(CHAN0_CIPHER_CTRL, chn0_ctrl.u32);
    HI_LOG_INFO("CHAN0_CIPHER_CTRL 0x%x\n", chn0_ctrl.u32);
}

static s32 drv_hdcp_aes_cbc_done(void)
{
    U_CHAN0_CIPHER_CTRL chn0_ctrl;
    u32 timeout = 0x00;

    /* start */
    chn0_ctrl.u32 = SYMC_READ(CHAN0_CIPHER_CTRL);
    chn0_ctrl.bits.sym_ch0_start = 0x01;
    SYMC_WRITE(CHAN0_CIPHER_CTRL, chn0_ctrl.u32);

    /* wait done */
    chn0_ctrl.u32 = SYMC_READ(CHAN0_CIPHER_CTRL);
    while(chn0_ctrl.bits.sym_ch0_start)
    {
        if (HDCP_TIME_OUT <= timeout++)
        {
            HI_LOG_ERROR("error, hdcp wait done time out\n");
            return HI_ERR_CIPHER_TIMEOUT;
        }
        crypto_udelay(1);
        chn0_ctrl.u32 = SYMC_READ(CHAN0_CIPHER_CTRL);
    }

    /* don't update iv any more */
    chn0_ctrl.u32 = SYMC_READ(CHAN0_CIPHER_CTRL);
    chn0_ctrl.bits.sym_ch0_ivin_sel = 0x00;
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

    /* shouble be 0x0C for gole data */
    count = SYMC_READ(CALC_ST0);
    HI_LOG_INFO("Load HDCP Key, KSV CRC: 0x%02x\n", (count >> 12) & 0x0F);

    /* enable hdmi ram read */
    drv_hdmi_read_enable();

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/** @} */  /** <!-- ==== API declaration end ==== */

#endif //End of CHIP_HDCP_VER_V200
