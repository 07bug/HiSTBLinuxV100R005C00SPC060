/*****************************************************************************

    Copyright (C), 2017, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : kapi_hdcp.c
  Version       : Initial Draft
  Created       : 2017
  Last Modified :
  Description   :
  Function List :
  History       :
******************************************************************************/
#include "drv_osal_lib.h"
#include "cryp_hdcp.h"

/** @}*/  /** <!-- ==== Structure Definition end ====*/

/******************************* API Code *****************************/
/** \addtogroup      hdcp */
/** @{*/  /** <!-- [kapi]*/

s32 kapi_hdcp_encrypt(hdcp_rootkey_sel keysel, hdmi_ram_sel ramsel, u32 *hostkey,
                 u32 *in, u32 *out, u32 len, u32 operation)
{
    s32 ret = HI_FAILURE;

    HI_LOG_FuncEnter();

    HI_LOG_CHECK_PARAM(HI_NULL == in);

    ret =  cryp_hdcp_crypto(keysel, ramsel, hostkey, in, out, len, operation);
    if (HI_SUCCESS != ret)
    {
        HI_LOG_PrintFuncErr(cryp_hdcp_crypto, ret);
        return ret;
    }

    HI_LOG_FuncExit();
    return HI_SUCCESS;
}

/** @}*/  /** <!-- ==== Structure Definition end ====*/
