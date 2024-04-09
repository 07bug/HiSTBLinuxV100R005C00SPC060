/******************************************************************************
  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
  File Name     : hal_reg_cfg_manager.h
  Version       : Initial Draft
  Author        :
  Created       : 2017/11/22
  Last Modified :
  Description   : Reg config
  Function List :
  History       :
******************************************************************************/

#ifndef _HAL_REG_CFG_MANAGER_H_
#define _HAL_REG_CFG_MANAGER_H_

#include "hi_reg_common.h"


#ifdef __cplusplus
#if __cplusplus
 extern "C"
{
#endif
#endif


#define RESTORE_OFFSET_ELE_NUM  2
#define OUT_STD_ELE_NUM         3

#define REG_ADDR_OFFSET(REG) ((HI_ULONG) &(((S_VDP_REGS_TYPE*)0)->REG))

/* List1 : Chipset config, value only */
#define VDP_CHIP_CFG_DHD0_CTRL_DEFAULT      0x00008011  /*Default DHD0_CTRL value for DHD*/
#define VDP_CHIP_CFG_DHD0_SYNC_INV_DEFAULT  0x2000      /*Default DHD0_SYNC_INV value for DHD*/
#define VDP_CHIP_CFG_DSD_CTRL_DEFAULT       0x00008011  /*Default DHD0_CTRL value for DSD*/
#define VDP_CHIP_CFG_DSD_SYNC_INV_DEFAULT   0x2000      /*Default DHD0_SYNC_INV value for DSD*/

/* List2 : Chipset config, choice only */
#define VDP_CHIP_CFG_CBM_MIX_2

/* List3 : Chipset config, choice and value */
//#define VDP_CHIP_CFG_MASTER0_RD_BUS1 0x2


/*CRG211 init config */
#define PERI_CRG211_INIT(CRG211, Rst)\
    {\
        (CRG211).bits.vdp_ini_cksel0    = (Rst) ? 0: 1;\
        /*(CRG211).bits.vdp_ini_cksel1    = (Rst) ? 0: 1;*/\
        (CRG211).bits.vdp_hd_clk_div0   = (Rst) ? 0: 1;\
        /*(CRG211).bits.vdp_hd_clk_div1   = (Rst) ? 0: 1;*/\
        (CRG211).bits.vdp_hd_cken       = (Rst) ? 0: 1;\
        /*(CRG211).bits.vdp_v0_cken       = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_v1_cken       = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_g0_cken       = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_g1_cken       = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_g3_cken       = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_wbc_hd_cken   = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_wbc_gp_cken   = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_wbc_vp_cken   = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_sd_cken       = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_v3_cken       = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vdp_g4_cken       = (Rst) ? 0: 1;*/\
        /*(CRG211).bits.vo_bp_cken        = (Rst) ? 0: 1;*/\
    }

/*CRG54 init config */
#define PERI_CRG54_INIT(CRG54, Rst)\
    {\
        (CRG54).bits.vo_bus_cken        = (Rst) ? 0: 1;\
        (CRG54).bits.vo_hd0_cken        = (Rst) ? 0: 1;\
        /*(CRG54).bits.vo_sd_cken         = (Rst) ? 0: 1*/;\
        (CRG54).bits.vo_sdate_cken      = (Rst) ? 0: 1;\
        (CRG54).bits.vdac_ch0_cken      = (Rst) ? 0: 0;\
        /*(CRG54).bits.vo_sd_clk_sel      = (Rst) ? (CRG54).bits.vo_sd_clk_sel: 0;*/\
        /*(CRG54).bits.vo_sd_clk_div      = (Rst) ? (CRG54).bits.vo_sd_clk_div: 2;*/\
        (CRG54).bits.vo_hd_clk_sel      = (Rst) ? (CRG54).bits.vo_hd_clk_sel: 1;\
        (CRG54).bits.vo_hd_clk_div      = (Rst) ? (CRG54).bits.vo_hd_clk_div: 0;\
        /*(CRG54).bits.hdmi_clk_sel       = (Rst) ? (CRG54).bits.hdmi_clk_sel:  1;*/\
        /*(CRG54).bits.vo_sd_hdmi_clk_sel = (Rst) ? (CRG54).bits.vo_sd_hdmi_clk_sel: 0;*/\
        (CRG54).bits.vdp_clk_sel        = (Rst) ? (CRG54).bits.vdp_clk_sel:        0;\
        (CRG54).bits.vo_hd_hdmi_clk_sel = (Rst) ? (CRG54).bits.vo_hd_hdmi_clk_sel: 0;\
        (CRG54).bits.vdp_cfg_cken       = (Rst) ? 0: 1;\
    }


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

