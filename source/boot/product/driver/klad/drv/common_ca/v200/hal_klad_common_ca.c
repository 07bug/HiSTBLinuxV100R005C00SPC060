/******************************************************************************

Copyright (C), 2016, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hal_klad_common_ca.c
Version       : Initial draft
Author        : Hisilicon hisecurity team
Created       : 2016-12-08
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#include "hal_klad_common_ca.h"
#include "hal_klad_common_ca_reg.h"
#include "hal_klad.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

HI_VOID HAL_KLAD_COMMON_CA_R2RStart(HI_U8 level, HI_U8 alg, HI_U8 addr, HI_U8 odd, HI_U8 engine, HI_U8 target)
{
    KL_COM_CA_R2R_KLAD_CTRL_U ctrl;

    ctrl.u32 = 0;
    ctrl.bits.calc_start    = 0x1;
    ctrl.bits.level_sel     = level & 0xf;
    ctrl.bits.tdes_aes_sel  = alg & 0x1;
    ctrl.bits.key_addr      = ((addr & 0x7F) << 1) + (odd & 0x1);
    ctrl.bits.port_sel      = target & 0x3;
    HAL_KLAD_WriteReg(KL_COM_CA_R2R_KLAD_CTRL, ctrl.u32);
    return;
}

HI_U8 HAL_KLAD_COMMON_CA_GetR2RLevel(HI_VOID)
{
    HI_U32 value = 0;
    HI_U32 level[] = {2, 3};
    KL_COMMON_CA_OTP_LV_SEL_U lv_sel;

    value = HAL_KLAD_ReadOtpShadowReg(KL_COM_CA_OTP_LV_SEL);
    lv_sel.u8 = value & 0xff;
    return level[lv_sel.bits.cm0_r2r_lv_sel];
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
