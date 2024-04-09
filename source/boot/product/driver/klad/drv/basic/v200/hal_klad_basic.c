/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_basic.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hal_klad.h"
#include "hal_klad_basic_reg.h"
#include "hal_klad_basic.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

HI_VOID HAL_KLAD_BOOTStart(HI_U8 alg, HI_U8 decrypt, HI_U8 addr, HI_U8 target)
{
    KL_BOOT_KLAD_CTRL_U ctrl;

    ctrl.u32 = 0;
    ctrl.bits.boot_calc_start   = 0x1;
    ctrl.bits.boot_tdes_aes_sel = alg & 0x1;
    ctrl.bits.boot_decrypt      = decrypt & 0x1;
    ctrl.bits.boot_key_addr     = (addr & 0x7F) << 1;
    ctrl.bits.boot_port_sel     = target & 0x3;
    HAL_KLAD_WriteReg(KL_BOOT_KLAD_CTRL, ctrl.u32);

    return;
}

HI_VOID HAL_KLAD_BOOTGetEncRslt(HI_U8 *data)
{
    HI_U32 i = 0;
    HI_U32 din = 0;

    for(i = 0; i < 4; i++)
    {
        din = HAL_KLAD_ReadReg(KL_BOOT_ENC_RSLT0 + 4*i);
        data[4*i] = din & 0xff;
        data[4*i + 1] = (din >> 8) & 0xff;
        data[4*i + 2] = (din >> 16) & 0xff;
        data[4*i + 3] = (din >> 24) & 0xff;
    }

    return;
}

HI_U32 HAL_KLAD_BOOTGetState(HI_VOID)
{
    KL_BOOT_KLAD_STATE_U state;

    state.u32 = HAL_KLAD_ReadReg(KL_BOOT_KLAD_STATE);

    return state.u32;
}

HI_VOID HAL_KLAD_SWStart(HI_U8 decrypt, HI_U8 addr)
{
    KL_SW_KLAD_CTRL_U ctrl;

    ctrl.u32 = 0;
    ctrl.bits.sw_calc_start   = 0x1;
    ctrl.bits.sw_decrypt      = decrypt & 0x1;
    ctrl.bits.sw_key_addr     = (addr & 0x7F) << 1;
    HAL_KLAD_WriteReg(KL_SW_KLAD_CTRL, ctrl.u32);

    return;
}

HI_VOID HAL_KLAD_SWGetEncRslt(HI_U8 *data)
{
    HI_U32 i = 0;
    HI_U32 din = 0;

    for(i = 0; i < 4; i++)
    {
        din = HAL_KLAD_ReadReg(KL_SW_ENC_RSLT0 + 4*i);
        data[4*i] = din & 0xff;
        data[4*i + 1] = (din >> 8) & 0xff;
        data[4*i + 2] = (din >> 16) & 0xff;
        data[4*i + 3] = (din >> 24) & 0xff;
    }

    return;
}

HI_U32 HAL_KLAD_SWGetState(HI_VOID)
{
    KL_SW_KLAD_STATE_U state;

    state.u32 = HAL_KLAD_ReadReg(KL_SW_KLAD_STATE);

    return state.u32;
}

HI_VOID HAL_KLAD_SetClearCwDataIn(HI_U8 *data)
{
    HI_U32 i = 0;
    HI_U32 din = 0;

    for (i = 0; i < 16; i += 4)
    {
        din = (data[i + 3] << 24) | (data[i + 2] << 16) | (data[i + 1] << 8) | data[i];
        HAL_KLAD_WriteReg(KL_CLEAR_CW_DIN0 + i, din);
    }

    return;
}

HI_VOID HAL_KLAD_CLEAR_CWStart(HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target)
{
    KL_CLEAR_CW_KLAD_CTRL_U ctrl;

    ctrl.u32 = 0;
    ctrl.bits.clear_cw_calc_start   = 0x1;
    ctrl.bits.clear_cw_key_addr     = ((addr & 0x7F) << 1) + (odd & 0x1);
    ctrl.bits.clear_cw_dsc_mode     = engine;
    ctrl.bits.clear_cw_port_sel     = target & 0x3;
    HAL_KLAD_WriteReg(KL_CLEAR_CW_KLAD_CTRL, ctrl.u32);

    return;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif
