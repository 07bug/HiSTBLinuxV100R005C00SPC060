/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : cryp_hdcp.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "drv_hdcp.h"
#include "cryp_hdcp.h"

/*********************** Internal Structure Definition ***********************/
/** \addtogroup      hdcp */
/** @{*/  /** <!-- [hdcp]*/



/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      hdcp drivers*/
/** @{*/  /** <!-- [hdcp]*/

s32 cryp_hdcp_crypto(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, u32 *hostkey,
                 u32 *in, u32 *out, u32 len, u32 decrypt)
{
#ifdef CHIP_HDCP_SUPPORT
    return drv_hdcp_encrypt(keysel, ramsel, hostkey, in, out, len, decrypt);
#else
    return HI_ERR_CIPHER_UNSUPPORTED;
#endif
}

/** @}*/  /** <!-- ==== API Code end ====*/
