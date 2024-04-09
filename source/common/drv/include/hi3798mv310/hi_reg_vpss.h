//******************************************************************************
// Copyright     :  Copyright (C) 2017, Hisilicon Technologies Co., Ltd.
// File name     :  hi_reg_vpss.h
// Author        :
// Version       :  1.0
// Date          :  2017-11-21
// Description   :  Define all registers/tables for SYS
// Others        :  Generated automatically by nManager V4.0
// History       :  2017-11-21 Create file
//******************************************************************************

#ifndef __HI_REG_VPSS_H__
#define __HI_REG_VPSS_H__

/* Define the union U_VPSS_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tnr_mad_mode          : 2   ; /* [1..0]  */
        unsigned int    mcnr_en               : 1   ; /* [2]  */
        unsigned int    vhd0_en               : 1   ; /* [3]  */
        unsigned int    mad_vfir_en           : 1   ; /* [4]  */
        unsigned int    out_pro_en            : 1   ; /* [5]  */
        unsigned int    reserved_0            : 1   ; /* [6]  */
        unsigned int    dei_en                : 1   ; /* [7]  */
        unsigned int    mcdi_en               : 1   ; /* [8]  */
        unsigned int    reserved_1            : 1   ; /* [9]  */
        unsigned int    vc1_en                : 1   ; /* [10]  */
        unsigned int    rgme_en               : 1   ; /* [11]  */
        unsigned int    bit10_bypass_en       : 1   ; /* [12]  */
        unsigned int    blk_det_en            : 1   ; /* [13]  */
        unsigned int    reserved_2            : 3   ; /* [16..14]  */
        unsigned int    snr_en                : 1   ; /* [17]  */
        unsigned int    tnr_en                : 1   ; /* [18]  */
        unsigned int    reserved_3            : 1   ; /* [19]  */
        unsigned int    four_pix_en           : 1   ; /* [20]  */
        unsigned int    hdr_in                : 1   ; /* [21]  */
        unsigned int    reserved_4            : 3   ; /* [24..22]  */
        unsigned int    ifmd_en               : 1   ; /* [25]  */
        unsigned int    igbm_en               : 1   ; /* [26]  */
        unsigned int    reserved_5            : 2   ; /* [28..27]  */
        unsigned int    bfield_first          : 1   ; /* [29]  */
        unsigned int    reserved_6            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CTRL;

/* Define the union U_VPSS_CTRL2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    reserved_1            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CTRL2;

/* Define the union U_VPSS_CTRL3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 3   ; /* [2..0]  */
        unsigned int    zme_vhd0_en           : 1   ; /* [3]  */
        unsigned int    reserved_1            : 1   ; /* [4]  */
        unsigned int    reserved_2            : 1   ; /* [5]  */
        unsigned int    vhd0_pre_vfir_en      : 1   ; /* [6]  */
        unsigned int    reserved_3            : 9   ; /* [15..7]  */
        unsigned int    reserved_4            : 1   ; /* [16]  */
        unsigned int    vhd0_crop_en          : 1   ; /* [17]  */
        unsigned int    reserved_5            : 2   ; /* [19..18]  */
        unsigned int    vhd0_lba_en           : 1   ; /* [20]  */
        unsigned int    reserved_6            : 1   ; /* [21]  */
        unsigned int    reserved_7            : 1   ; /* [22]  */
        unsigned int    reserved_8            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CTRL3;

/* Define the union U_VPSS_CMD_CNT_CHN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cmdlen_cnt_wr_chn     : 8   ; /* [7..0]  */
        unsigned int    cmd_cnt_wr_chn        : 8   ; /* [15..8]  */
        unsigned int    cmdlen_cnt_rd_chn     : 8   ; /* [23..16]  */
        unsigned int    cmd_cnt_rd_chn        : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CMD_CNT_CHN;

/* Define the union U_VPSS_RCH_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    rch_cury_bypass       : 1   ; /* [1]  */
        unsigned int    rch_curc_bypass       : 1   ; /* [2]  */
        unsigned int    rch_refy_bypass       : 1   ; /* [3]  */
        unsigned int    rch_refc_bypass       : 1   ; /* [4]  */
        unsigned int    rch_nx1y_bypass       : 1   ; /* [5]  */
        unsigned int    rch_nx1c_bypass       : 1   ; /* [6]  */
        unsigned int    rch_nx2y_bypass       : 1   ; /* [7]  */
        unsigned int    rch_nx2c_bypass       : 1   ; /* [8]  */
        unsigned int    reserved_1            : 1   ; /* [9]  */
        unsigned int    rch_trmd_bypass       : 1   ; /* [10]  */
        unsigned int    rch_srmd_bypass       : 1   ; /* [11]  */
        unsigned int    rch_rst_bypass        : 1   ; /* [12]  */
        unsigned int    rch_prjh_cur_bypass   : 1   ; /* [13]  */
        unsigned int    rch_blkmv_nx1_bypass  : 1   ; /* [14]  */
        unsigned int    rch_blkmv_cur_bypass  : 1   ; /* [15]  */
        unsigned int    rch_blkmv_ref_bypass  : 1   ; /* [16]  */
        unsigned int    rch_prjv_cur_bypass   : 1   ; /* [17]  */
        unsigned int    rch_rgmv_nx1_bypass   : 1   ; /* [18]  */
        unsigned int    rch_rgmv_cur_bypass   : 1   ; /* [19]  */
        unsigned int    rch_reey_bypass       : 1   ; /* [20]  */
        unsigned int    rch_reec_bypass       : 1   ; /* [21]  */
        unsigned int    rch_tunl_bypass       : 1   ; /* [22]  */
        unsigned int    rch_nx2y_head_bypass  : 1   ; /* [23]  */
        unsigned int    rch_nx2c_head_bypass  : 1   ; /* [24]  */
        unsigned int    rch_nx2y_tile_2bit_bypass : 1   ; /* [25]  */
        unsigned int    rch_nx2c_tile_2bit_bypass : 1   ; /* [26]  */
        unsigned int    reserved_2            : 1   ; /* [27]  */
        unsigned int    rch_transr_bypass     : 1   ; /* [28]  */
        unsigned int    reserved_3            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_RCH_BYPASS;

/* Define the union U_VPSS_WCH_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wch_vhd0y_bypass      : 1   ; /* [0]  */
        unsigned int    wch_vhd0c_bypass      : 1   ; /* [1]  */
        unsigned int    wch_rfry_bypass       : 1   ; /* [2]  */
        unsigned int    wch_rfrc_bypass       : 1   ; /* [3]  */
        unsigned int    reserved_0            : 1   ; /* [4]  */
        unsigned int    wch_wst_bypass        : 1   ; /* [5]  */
        unsigned int    wch_twmd_bypass       : 1   ; /* [6]  */
        unsigned int    wch_stt_bypass        : 1   ; /* [7]  */
        unsigned int    reserved_1            : 1   ; /* [8]  */
        unsigned int    wch_prjhnx2_bypass    : 1   ; /* [9]  */
        unsigned int    wch_blkmvnx2_bypass   : 1   ; /* [10]  */
        unsigned int    wch_prjvnx2_bypass    : 1   ; /* [11]  */
        unsigned int    wch_rgmvnx2_bypass    : 1   ; /* [12]  */
        unsigned int    wch_cuey_bypass       : 1   ; /* [13]  */
        unsigned int    wch_cuec_bypass       : 1   ; /* [14]  */
        unsigned int    wch_transw_bypass     : 1   ; /* [15]  */
        unsigned int    wch_tunl_bypass       : 1   ; /* [16]  */
        unsigned int    reserved_2            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_WCH_BYPASS;

/* Define the union U_VPSS_VHD0_ZMEORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_zme_ow           : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_zme_oh           : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_ZMEORESO;

/* Define the union U_VPSS_VHD0_ZME_LHADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhd0_scl_lh            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_VHD0_ZME_LHADDR;
/* Define the union U_VPSS_VHD0_ZME_LVADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhd0_scl_lv            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_VHD0_ZME_LVADDR;
/* Define the union U_VPSS_VHD0_ZME_CHADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhd0_scl_ch            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_VHD0_ZME_CHADDR;
/* Define the union U_VPSS_VHD0_ZME_CVADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhd0_scl_cv            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_VHD0_ZME_CVADDR;
/* Define the union U_VPSS_TNR_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tnr_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_TNR_ADDR;
/* Define the union U_VPSS_SNR_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int snr_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_SNR_ADDR;
/* Define the union U_VPSS_ZME_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int zme_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_ZME_ADDR;
/* Define the union U_VPSS_DEI_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dei_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEI_ADDR;
/* Define the union U_VPSS_HDR_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int hdr_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_HDR_ADDR;
/* Define the union U_VPSS_NODEID */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nodeid                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_NODEID;
/* Define the union U_VPSS_PNEXT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p_next                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_PNEXT;
/* Define the union U_VPSS_START */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_START;

/* Define the union U_VPSS_INTSTATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    eof_state             : 1   ; /* [0]  */
        unsigned int    timeout_state         : 1   ; /* [1]  */
        unsigned int    bus_w_err_state       : 1   ; /* [2]  */
        unsigned int    eof_end_state         : 1   ; /* [3]  */
        unsigned int    vhd0_tunl_state       : 1   ; /* [4]  */
        unsigned int    dcmp_err_state        : 1   ; /* [5]  */
        unsigned int    bus_r_err_state       : 1   ; /* [6]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    reserved_1            : 1   ; /* [8]  */
        unsigned int    reserved_2            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_INTSTATE;

/* Define the union U_VPSS_INTCLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    eof_clr               : 1   ; /* [0]  */
        unsigned int    timeout_clr           : 1   ; /* [1]  */
        unsigned int    bus_w_err_clr         : 1   ; /* [2]  */
        unsigned int    eof_end_clr           : 1   ; /* [3]  */
        unsigned int    vhd0_tunl_clr         : 1   ; /* [4]  */
        unsigned int    dcmp_err_clr          : 1   ; /* [5]  */
        unsigned int    bus_r_err_clr         : 1   ; /* [6]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    reserved_1            : 1   ; /* [8]  */
        unsigned int    reserved_2            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_INTCLR;

/* Define the union U_VPSS_RAWINT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    raw_eof               : 1   ; /* [0]  */
        unsigned int    raw_timeout           : 1   ; /* [1]  */
        unsigned int    raw_bus_w_err         : 1   ; /* [2]  */
        unsigned int    raw_eof_end           : 1   ; /* [3]  */
        unsigned int    raw_vhd0_tunl         : 1   ; /* [4]  */
        unsigned int    raw_dcmp_err          : 1   ; /* [5]  */
        unsigned int    raw_bus_r_err         : 1   ; /* [6]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    reserved_1            : 1   ; /* [8]  */
        unsigned int    reserved_2            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_RAWINT;

/* Define the union U_VPSS_PFCNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int pfcnt                  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_PFCNT;
/* Define the union U_VPSS_TIMEOUT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int timeout                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_TIMEOUT;
/* Define the union U_VPSS_FTCONFIG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    node_rst_en           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_FTCONFIG;

/* Define the union U_VPSS_INTMASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    eof_mask              : 1   ; /* [0]  */
        unsigned int    timeout_mask          : 1   ; /* [1]  */
        unsigned int    bus_w_err_mask        : 1   ; /* [2]  */
        unsigned int    eof_end_mask          : 1   ; /* [3]  */
        unsigned int    vhd0_tunl_mask        : 1   ; /* [4]  */
        unsigned int    dcmp_err_mask         : 1   ; /* [5]  */
        unsigned int    bus_r_err_mask        : 1   ; /* [6]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    reserved_1            : 1   ; /* [8]  */
        unsigned int    reserved_2            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_INTMASK;

/* Define the union U_VPSS_EOFCNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int eof_cnt                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_EOFCNT;
/* Define the union U_VPSS_VERSION */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int version                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_VERSION;
/* Define the union U_VPSS_LOWPOWER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rfs_ema               : 3   ; /* [2..0]  */
        unsigned int    rfs_emaw              : 2   ; /* [4..3]  */
        unsigned int    ret1n                 : 1   ; /* [5]  */
        unsigned int    rft_emaa              : 3   ; /* [8..6]  */
        unsigned int    rft_emab              : 3   ; /* [11..9]  */
        unsigned int    rfs_colldisn          : 1   ; /* [12]  */
        unsigned int    rft_emasa             : 1   ; /* [13]  */
        unsigned int    rftuhd_ema            : 3   ; /* [16..14]  */
        unsigned int    rftuhd_emawb          : 2   ; /* [18..17]  */
        unsigned int    rftuhd_emasa          : 1   ; /* [19]  */
        unsigned int    rfs_rtsel             : 2   ; /* [21..20]  */
        unsigned int    rfts_wct              : 2   ; /* [23..22]  */
        unsigned int    rfts_rct              : 2   ; /* [25..24]  */
        unsigned int    rfts_kp               : 3   ; /* [28..26]  */
        unsigned int    rftf_wct              : 2   ; /* [30..29]  */
        unsigned int    ck_gt_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LOWPOWER_CTRL;

/* Define the union U_VPSS_LOWPOWER_CTRL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rftf_rct              : 2   ; /* [1..0]  */
        unsigned int    rftf_kp               : 3   ; /* [4..2]  */
        unsigned int    rft_wtsel             : 2   ; /* [6..5]  */
        unsigned int    rft_rtsel             : 2   ; /* [8..7]  */
        unsigned int    rft_mtsel             : 2   ; /* [10..9]  */
        unsigned int    rasshds_wtsel         : 2   ; /* [12..11]  */
        unsigned int    rasshds_rtsel         : 2   ; /* [14..13]  */
        unsigned int    rasshdm_wtsel         : 2   ; /* [16..15]  */
        unsigned int    rasshdm_rtsel         : 2   ; /* [18..17]  */
        unsigned int    rashds_wtsel          : 2   ; /* [20..19]  */
        unsigned int    rashds_rtsel          : 2   ; /* [22..21]  */
        unsigned int    rashdm_wtsel          : 2   ; /* [24..23]  */
        unsigned int    rashdm_rtsel          : 2   ; /* [26..25]  */
        unsigned int    ras_wtsel             : 2   ; /* [28..27]  */
        unsigned int    ras_rtsel             : 2   ; /* [30..29]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LOWPOWER_CTRL1;

/* Define the union U_VPSS_HOLD_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    node_hold_num         : 16  ; /* [15..0]  */
        unsigned int    node_hold_en          : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HOLD_CTRL;

/* Define the union U_VPSS_HARDGATE_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hard_gate_clk_axi_en  : 1   ; /* [0]  */
        unsigned int    hard_gate_clk_ppc_en  : 1   ; /* [1]  */
        unsigned int    hard_gate_clk_cfg_en  : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_HARDGATE_CTRL;

/* Define the union U_VPSS_LINKLIST_CNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int linklist_cnt           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_LINKLIST_CNT;
/* Define the union U_VPSS_MST_OUTSTANDING */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mstr0_routstanding    : 4   ; /* [3..0]  */
        unsigned int    mstr0_woutstanding    : 4   ; /* [7..4]  */
        unsigned int    mstr1_routstanding    : 4   ; /* [11..8]  */
        unsigned int    mstr1_woutstanding    : 4   ; /* [15..12]  */
        unsigned int    mstr2_routstanding    : 4   ; /* [19..16]  */
        unsigned int    mstr2_woutstanding    : 4   ; /* [23..20]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MST_OUTSTANDING;

/* Define the union U_VPSS_MST_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    split_mode            : 4   ; /* [3..0]  */
        unsigned int    arb_mode              : 4   ; /* [7..4]  */
        unsigned int    mid_enable            : 1   ; /* [8]  */
        unsigned int    split_typ             : 1   ; /* [9]  */
        unsigned int    cas_mmu_bypass        : 1   ; /* [10]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    wport_sel             : 4   ; /* [15..12]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MST_CTRL;

/* Define the union U_VPSS_MST_RCHN_PRIO0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rchn0_prio            : 1   ; /* [0]  */
        unsigned int    rchn1_prio            : 1   ; /* [1]  */
        unsigned int    rchn2_prio            : 1   ; /* [2]  */
        unsigned int    rchn3_prio            : 1   ; /* [3]  */
        unsigned int    rchn4_prio            : 1   ; /* [4]  */
        unsigned int    rchn5_prio            : 1   ; /* [5]  */
        unsigned int    rchn6_prio            : 1   ; /* [6]  */
        unsigned int    rchn7_prio            : 1   ; /* [7]  */
        unsigned int    rchn8_prio            : 1   ; /* [8]  */
        unsigned int    rchn9_prio            : 1   ; /* [9]  */
        unsigned int    rchn10_prio           : 1   ; /* [10]  */
        unsigned int    rchn11_prio           : 1   ; /* [11]  */
        unsigned int    rchn12_prio           : 1   ; /* [12]  */
        unsigned int    rchn13_prio           : 1   ; /* [13]  */
        unsigned int    rchn14_prio           : 1   ; /* [14]  */
        unsigned int    rchn15_prio           : 1   ; /* [15]  */
        unsigned int    rchn16_prio           : 1   ; /* [16]  */
        unsigned int    rchn17_prio           : 1   ; /* [17]  */
        unsigned int    rchn18_prio           : 1   ; /* [18]  */
        unsigned int    rchn19_prio           : 1   ; /* [19]  */
        unsigned int    rchn20_prio           : 1   ; /* [20]  */
        unsigned int    rchn21_prio           : 1   ; /* [21]  */
        unsigned int    rchn22_prio           : 1   ; /* [22]  */
        unsigned int    rchn23_prio           : 1   ; /* [23]  */
        unsigned int    rchn24_prio           : 1   ; /* [24]  */
        unsigned int    rchn25_prio           : 1   ; /* [25]  */
        unsigned int    rchn26_prio           : 1   ; /* [26]  */
        unsigned int    rchn27_prio           : 1   ; /* [27]  */
        unsigned int    rchn28_prio           : 1   ; /* [28]  */
        unsigned int    rchn29_prio           : 1   ; /* [29]  */
        unsigned int    rchn30_prio           : 1   ; /* [30]  */
        unsigned int    rchn31_prio           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MST_RCHN_PRIO0;

/* Define the union U_VPSS_MST_WCHN_PRIO0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wchn0_prio            : 1   ; /* [0]  */
        unsigned int    wchn1_prio            : 1   ; /* [1]  */
        unsigned int    wchn2_prio            : 1   ; /* [2]  */
        unsigned int    wchn3_prio            : 1   ; /* [3]  */
        unsigned int    wchn4_prio            : 1   ; /* [4]  */
        unsigned int    wchn5_prio            : 1   ; /* [5]  */
        unsigned int    wchn6_prio            : 1   ; /* [6]  */
        unsigned int    wchn7_prio            : 1   ; /* [7]  */
        unsigned int    wchn8_prio            : 1   ; /* [8]  */
        unsigned int    wchn9_prio            : 1   ; /* [9]  */
        unsigned int    wchn10_prio           : 1   ; /* [10]  */
        unsigned int    wchn11_prio           : 1   ; /* [11]  */
        unsigned int    wchn12_prio           : 1   ; /* [12]  */
        unsigned int    wchn13_prio           : 1   ; /* [13]  */
        unsigned int    wchn14_prio           : 1   ; /* [14]  */
        unsigned int    wchn15_prio           : 1   ; /* [15]  */
        unsigned int    wchn16_prio           : 1   ; /* [16]  */
        unsigned int    wchn17_prio           : 1   ; /* [17]  */
        unsigned int    wchn18_prio           : 1   ; /* [18]  */
        unsigned int    wchn19_prio           : 1   ; /* [19]  */
        unsigned int    wchn20_prio           : 1   ; /* [20]  */
        unsigned int    wchn21_prio           : 1   ; /* [21]  */
        unsigned int    wchn22_prio           : 1   ; /* [22]  */
        unsigned int    wchn23_prio           : 1   ; /* [23]  */
        unsigned int    wchn24_prio           : 1   ; /* [24]  */
        unsigned int    wchn25_prio           : 1   ; /* [25]  */
        unsigned int    wchn26_prio           : 1   ; /* [26]  */
        unsigned int    wchn27_prio           : 1   ; /* [27]  */
        unsigned int    wchn28_prio           : 1   ; /* [28]  */
        unsigned int    wchn29_prio           : 1   ; /* [29]  */
        unsigned int    wchn30_prio           : 1   ; /* [30]  */
        unsigned int    wchn31_prio           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MST_WCHN_PRIO0;

/* Define the union U_VPSS_MST_BUS_ERR_CLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bus_error_clr         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MST_BUS_ERR_CLR;

/* Define the union U_VPSS_MST_BUS_ERR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mst0_r_error          : 1   ; /* [0]  */
        unsigned int    mst0_w_error          : 1   ; /* [1]  */
        unsigned int    mst1_r_error          : 1   ; /* [2]  */
        unsigned int    mst1_w_error          : 1   ; /* [3]  */
        unsigned int    mst2_r_error          : 1   ; /* [4]  */
        unsigned int    mst2_w_error          : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MST_BUS_ERR;

/* Define the union U_VPSS_MST_SRC0_STATUS0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int src0_status0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_MST_SRC0_STATUS0;
/* Define the union U_VPSS_MST_SRC0_STATUS1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int src0_status1           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_MST_SRC0_STATUS1;
/* Define the union U_VPSS_MST_DEBUG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    axi_det_enable        : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MST_DEBUG_CTRL;

/* Define the union U_VPSS_MST_DEBUG_CLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    axi_det_clr           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MST_DEBUG_CLR;

/* Define the union U_VPSS_MST0_DET_LATENCY */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int axi_mst0_latency       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_MST0_DET_LATENCY;
/* Define the union U_VPSS_MST0_RD_INFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mst0_rd_info           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_MST0_RD_INFO;
/* Define the union U_VPSS_MST0_WR_INFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mst0_wr_info           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_MST0_WR_INFO;
/* Define the union U_VPSS_VHD0CROP_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_crop_width       : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_crop_height      : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0CROP_SIZE;

/* Define the union U_VPSS_VHD0CROP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_crop_x           : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_crop_y           : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0CROP_POS;

/* Define the union U_VPSS_VHD0LBA_DSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_lba_width        : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_lba_height       : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0LBA_DSIZE;

/* Define the union U_VPSS_VHD0LBA_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_lba_xfpos        : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    vhd0_lba_yfpos        : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0LBA_VFPOS;

/* Define the union U_VPSS_VHD0LBA_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhd0_vbk_y            : 10  ; /* [9..0]  */
        unsigned int    vhd0_vbk_cb           : 10  ; /* [19..10]  */
        unsigned int    vhd0_vbk_cr           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0LBA_BK;

/* Define the union U_VPSS_VC1_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vc1_mapc              : 3   ; /* [2..0]  */
        unsigned int    vc1_mapy              : 3   ; /* [5..3]  */
        unsigned int    vc1_mapcflg           : 1   ; /* [6]  */
        unsigned int    vc1_mapyflg           : 1   ; /* [7]  */
        unsigned int    vc1_profile           : 2   ; /* [9..8]  */
        unsigned int    vc1_rangedfrm         : 1   ; /* [10]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VC1_CTRL;

/* Define the union U_VPSS_DIECTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    edge_smooth_ratio     : 8   ; /* [15..8]  */
        unsigned int    stinfo_stop           : 1   ; /* [16]  */
        unsigned int    die_rst               : 1   ; /* [17]  */
        unsigned int    mchdir_c              : 1   ; /* [18]  */
        unsigned int    mchdir_l              : 1   ; /* [19]  */
        unsigned int    edge_smooth_en        : 1   ; /* [20]  */
        unsigned int    ma_only               : 1   ; /* [21]  */
        unsigned int    mc_only               : 1   ; /* [22]  */
        unsigned int    two_four_pxl_share    : 1   ; /* [23]  */
        unsigned int    die_c_mode            : 2   ; /* [25..24]  */
        unsigned int    die_l_mode            : 2   ; /* [27..26]  */
        unsigned int    die_out_sel_c         : 1   ; /* [28]  */
        unsigned int    die_out_sel_l         : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECTRL;

/* Define the union U_VPSS_DIELMA2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    recmode_frmfld_blend_mode : 1   ; /* [0]  */
        unsigned int    frame_motion_smooth_en : 1   ; /* [1]  */
        unsigned int    luma_scesdf_max       : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    motion_iir_en         : 1   ; /* [4]  */
        unsigned int    luma_mf_max           : 1   ; /* [5]  */
        unsigned int    chroma_mf_max         : 1   ; /* [6]  */
        unsigned int    rec_mode_en           : 1   ; /* [7]  */
        unsigned int    dei_st_rst_value      : 16  ; /* [23..8]  */
        unsigned int    chroma_mf_offset      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIELMA2;

/* Define the union U_VPSS_DIEINTEN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rec_mode_set_pre_info_mode : 2   ; /* [1..0]  */
        unsigned int    rec_mode_output_mode  : 1   ; /* [2]  */
        unsigned int    reserved_0            : 5   ; /* [7..3]  */
        unsigned int    dir_ratio_north       : 4   ; /* [11..8]  */
        unsigned int    reserved_1            : 4   ; /* [15..12]  */
        unsigned int    min_north_strength    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEINTEN;

/* Define the union U_VPSS_DIESCALE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    range_scale           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIESCALE;

/* Define the union U_VPSS_DIECHECK1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bc1_max_dz            : 8   ; /* [7..0]  */
        unsigned int    bc1_autodz_gain       : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    bc1_gain              : 4   ; /* [19..16]  */
        unsigned int    reserved_1            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECHECK1;

/* Define the union U_VPSS_DIECHECK2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bc2_max_dz            : 8   ; /* [7..0]  */
        unsigned int    bc2_autodz_gain       : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    bc2_gain              : 4   ; /* [19..16]  */
        unsigned int    reserved_1            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECHECK2;

/* Define the union U_VPSS_DIEDIR0_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir0_scale            : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    dir1_scale            : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    dir2_scale            : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    dir3_scale            : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIR0_3;

/* Define the union U_VPSS_DIEDIR4_7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir4_scale            : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    dir5_scale            : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    dir6_scale            : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    dir7_scale            : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIR4_7;

/* Define the union U_VPSS_DIEDIR8_11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir8_scale            : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    dir9_scale            : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    dir10_scale           : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    dir11_scale           : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIR8_11;

/* Define the union U_VPSS_DIEDIR12_14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir12_scale           : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    dir13_scale           : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    dir14_scale           : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIR12_14;

/* Define the union U_VPSS_DIESTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cur_state             : 4   ; /* [3..0]  */
        unsigned int    cur_cstate            : 4   ; /* [7..4]  */
        unsigned int    l_height_cnt          : 12  ; /* [19..8]  */
        unsigned int    c_height_cnt          : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIESTA;

/* Define the union U_VPSS_DIEINTPSCL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intp_scale_ratio_1    : 4   ; /* [3..0]  */
        unsigned int    intp_scale_ratio_2    : 4   ; /* [7..4]  */
        unsigned int    intp_scale_ratio_3    : 4   ; /* [11..8]  */
        unsigned int    intp_scale_ratio_4    : 4   ; /* [15..12]  */
        unsigned int    intp_scale_ratio_5    : 4   ; /* [19..16]  */
        unsigned int    intp_scale_ratio_6    : 4   ; /* [23..20]  */
        unsigned int    intp_scale_ratio_7    : 4   ; /* [27..24]  */
        unsigned int    intp_scale_ratio_8    : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEINTPSCL0;

/* Define the union U_VPSS_DIEINTPSCL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intp_scale_ratio_9    : 4   ; /* [3..0]  */
        unsigned int    intp_scale_ratio_10   : 4   ; /* [7..4]  */
        unsigned int    intp_scale_ratio_11   : 4   ; /* [11..8]  */
        unsigned int    intp_scale_ratio_12   : 4   ; /* [15..12]  */
        unsigned int    intp_scale_ratio_13   : 4   ; /* [19..16]  */
        unsigned int    intp_scale_ratio_14   : 4   ; /* [23..20]  */
        unsigned int    intp_scale_ratio_15   : 4   ; /* [27..24]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEINTPSCL1;

/* Define the union U_VPSS_DIEDIRTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bc_gain               : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    dir_thd               : 4   ; /* [11..8]  */
        unsigned int    edge_mode             : 1   ; /* [12]  */
        unsigned int    hor_edge_en           : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    strength_thd          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEDIRTHD;

/* Define the union U_VPSS_DIEJITMTN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    jitter_gain           : 4   ; /* [3..0]  */
        unsigned int    jitter_coring         : 8   ; /* [11..4]  */
        unsigned int    fld_motion_coring     : 8   ; /* [19..12]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEJITMTN;

/* Define the union U_VPSS_DIEFLDMTN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fld_motion_thd_low    : 8   ; /* [7..0]  */
        unsigned int    fld_motion_thd_high   : 8   ; /* [15..8]  */
        unsigned int    fld_motion_curve_slope : 6   ; /* [21..16]  */
        unsigned int    reserved_0            : 2   ; /* [23..22]  */
        unsigned int    fld_motion_gain       : 4   ; /* [27..24]  */
        unsigned int    fld_motion_wnd_mode   : 1   ; /* [28]  */
        unsigned int    long_motion_shf       : 1   ; /* [29]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFLDMTN;

/* Define the union U_VPSS_DIEMTNDIFFTHD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_diff_thd_0     : 8   ; /* [7..0]  */
        unsigned int    motion_diff_thd_1     : 8   ; /* [15..8]  */
        unsigned int    motion_diff_thd_2     : 8   ; /* [23..16]  */
        unsigned int    motion_diff_thd_3     : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNDIFFTHD0;

/* Define the union U_VPSS_DIEMTNDIFFTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_diff_thd_4     : 8   ; /* [7..0]  */
        unsigned int    motion_diff_thd_5     : 8   ; /* [15..8]  */
        unsigned int    min_motion_iir_ratio  : 7   ; /* [22..16]  */
        unsigned int    reserved_0            : 1   ; /* [23]  */
        unsigned int    max_motion_iir_ratio  : 7   ; /* [30..24]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNDIFFTHD1;

/* Define the union U_VPSS_DIEMTNIIRSLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_iir_curve_slope_0 : 6   ; /* [5..0]  */
        unsigned int    motion_iir_curve_slope_1 : 6   ; /* [11..6]  */
        unsigned int    motion_iir_curve_slope_2 : 6   ; /* [17..12]  */
        unsigned int    motion_iir_curve_slope_3 : 6   ; /* [23..18]  */
        unsigned int    motion_iir_curve_ratio_0 : 7   ; /* [30..24]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNIIRSLP;

/* Define the union U_VPSS_DIEMTNIIRRAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_iir_curve_ratio_1 : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    motion_iir_curve_ratio_2 : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    motion_iir_curve_ratio_3 : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    motion_iir_curve_ratio_4 : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNIIRRAT;

/* Define the union U_VPSS_DIEHISMODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rec_mode_fld_motion_step_0 : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    rec_mode_fld_motion_step_1 : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    rec_mode_frm_motion_step_0 : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 2   ; /* [11..10]  */
        unsigned int    rec_mode_frm_motion_step_1 : 2   ; /* [13..12]  */
        unsigned int    reserved_3            : 2   ; /* [15..14]  */
        unsigned int    ppre_info_en          : 1   ; /* [16]  */
        unsigned int    pre_info_en           : 1   ; /* [17]  */
        unsigned int    his_motion_en         : 1   ; /* [18]  */
        unsigned int    his_motion_using_mode : 1   ; /* [19]  */
        unsigned int    his_motion_write_mode : 1   ; /* [20]  */
        unsigned int    his_motion_info_write_mode : 1   ; /* [21]  */
        unsigned int    reserved_4            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEHISMODE;

/* Define the union U_VPSS_DIEMORFLT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mor_flt_thd           : 8   ; /* [7..0]  */
        unsigned int    mor_flt_size          : 2   ; /* [9..8]  */
        unsigned int    reserved_0            : 14  ; /* [23..10]  */
        unsigned int    mor_flt_en            : 1   ; /* [24]  */
        unsigned int    reserved_1            : 1   ; /* [25]  */
        unsigned int    med_blend_en          : 1   ; /* [26]  */
        unsigned int    reserved_2            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMORFLT;

/* Define the union U_VPSS_DIECOMBCHK0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    comb_chk_min_hthd     : 8   ; /* [7..0]  */
        unsigned int    comb_chk_min_vthd     : 8   ; /* [15..8]  */
        unsigned int    comb_chk_lower_limit  : 8   ; /* [23..16]  */
        unsigned int    comb_chk_upper_limit  : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECOMBCHK0;

/* Define the union U_VPSS_DIECOMBCHK1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    comb_chk_edge_thd     : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    comb_chk_md_thd       : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    comb_chk_en           : 1   ; /* [16]  */
        unsigned int    reserved_2            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIECOMBCHK1;

/* Define the union U_VPSS_DIEFRMMTNSMTHTHD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_motion_smooth_thd0 : 8   ; /* [7..0]  */
        unsigned int    frame_motion_smooth_thd1 : 8   ; /* [15..8]  */
        unsigned int    frame_motion_smooth_thd2 : 8   ; /* [23..16]  */
        unsigned int    frame_motion_smooth_thd3 : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMMTNSMTHTHD0;

/* Define the union U_VPSS_DIEFRMMTNSMTHTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_motion_smooth_thd4 : 8   ; /* [7..0]  */
        unsigned int    frame_motion_smooth_thd5 : 8   ; /* [15..8]  */
        unsigned int    frame_motion_smooth_ratio_min : 7   ; /* [22..16]  */
        unsigned int    reserved_0            : 1   ; /* [23]  */
        unsigned int    frame_motion_smooth_ratio_max : 7   ; /* [30..24]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMMTNSMTHTHD1;

/* Define the union U_VPSS_DIEFRMMTNSMTHSLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_motion_smooth_slope0 : 6   ; /* [5..0]  */
        unsigned int    frame_motion_smooth_slope1 : 6   ; /* [11..6]  */
        unsigned int    frame_motion_smooth_slope2 : 6   ; /* [17..12]  */
        unsigned int    frame_motion_smooth_slope3 : 6   ; /* [23..18]  */
        unsigned int    frame_motion_smooth_ratio0 : 7   ; /* [30..24]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMMTNSMTHSLP;

/* Define the union U_VPSS_DIEFRMMTNSMTHRAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_motion_smooth_ratio1 : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    frame_motion_smooth_ratio2 : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    frame_motion_smooth_ratio3 : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    frame_motion_smooth_ratio4 : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMMTNSMTHRAT;

/* Define the union U_VPSS_DIEFRMFLDBLENDTHD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_field_blend_thd0 : 8   ; /* [7..0]  */
        unsigned int    frame_field_blend_thd1 : 8   ; /* [15..8]  */
        unsigned int    frame_field_blend_thd2 : 8   ; /* [23..16]  */
        unsigned int    frame_field_blend_thd3 : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMFLDBLENDTHD0;

/* Define the union U_VPSS_DIEFRMFLDBLENDTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_field_blend_thd4 : 8   ; /* [7..0]  */
        unsigned int    frame_field_blend_thd5 : 8   ; /* [15..8]  */
        unsigned int    frame_field_blend_ratio_min : 7   ; /* [22..16]  */
        unsigned int    reserved_0            : 1   ; /* [23]  */
        unsigned int    frame_field_blend_ratio_max : 7   ; /* [30..24]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMFLDBLENDTHD1;

/* Define the union U_VPSS_DIEFRMFLDBLENDSLP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_field_blend_slope0 : 6   ; /* [5..0]  */
        unsigned int    frame_field_blend_slope1 : 6   ; /* [11..6]  */
        unsigned int    frame_field_blend_slope2 : 6   ; /* [17..12]  */
        unsigned int    frame_field_blend_slope3 : 6   ; /* [23..18]  */
        unsigned int    frame_field_blend_ratio0 : 7   ; /* [30..24]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMFLDBLENDSLP;

/* Define the union U_VPSS_DIEFRMFLDBLENDRAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    frame_field_blend_ratio1 : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    frame_field_blend_ratio2 : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    frame_field_blend_ratio3 : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    frame_field_blend_ratio4 : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFRMFLDBLENDRAT;

/* Define the union U_VPSS_DIEMTNADJ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_adjust_gain    : 8   ; /* [7..0]  */
        unsigned int    motion_adjust_coring  : 6   ; /* [13..8]  */
        unsigned int    reserved_0            : 2   ; /* [15..14]  */
        unsigned int    motion_adjust_gain_chr : 8   ; /* [23..16]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMTNADJ;

/* Define the union U_VPSS_DIEEDGENORM0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_norm_0           : 12  ; /* [11..0]  */
        unsigned int    edge_norm_1           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEEDGENORM0;

/* Define the union U_VPSS_DIEEDGENORM1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_norm_2           : 12  ; /* [11..0]  */
        unsigned int    edge_norm_3           : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEEDGENORM1;

/* Define the union U_VPSS_DIEEDGENORM2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_norm_4           : 12  ; /* [11..0]  */
        unsigned int    edge_norm_5           : 12  ; /* [23..12]  */
        unsigned int    mc_strength_k3        : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEEDGENORM2;

/* Define the union U_VPSS_DIEEDGENORM3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_norm_6           : 12  ; /* [11..0]  */
        unsigned int    edge_norm_7           : 12  ; /* [23..12]  */
        unsigned int    mc_strength_g3        : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEEDGENORM3;

/* Define the union U_VPSS_DIEEDGENORM4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_norm_8           : 12  ; /* [11..0]  */
        unsigned int    edge_norm_9           : 12  ; /* [23..12]  */
        unsigned int    inter_diff_thd0       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEEDGENORM4;

/* Define the union U_VPSS_DIEEDGENORM5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_norm_10          : 12  ; /* [11..0]  */
        unsigned int    edge_norm_11          : 12  ; /* [23..12]  */
        unsigned int    inter_diff_thd1       : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEEDGENORM5;

/* Define the union U_VPSS_DIEEDGEFORMC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_coring           : 10  ; /* [9..0]  */
        unsigned int    edge_scale            : 10  ; /* [19..10]  */
        unsigned int    inter_diff_thd2       : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEEDGEFORMC;

/* Define the union U_VPSS_DIEMCSTRENGTH0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mc_strength_k0        : 8   ; /* [7..0]  */
        unsigned int    mc_strength_k1        : 8   ; /* [15..8]  */
        unsigned int    mc_strength_k2        : 8   ; /* [23..16]  */
        unsigned int    mc_strength_g0        : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMCSTRENGTH0;

/* Define the union U_VPSS_DIEMCSTRENGTH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mc_strength_g1        : 8   ; /* [7..0]  */
        unsigned int    mc_strength_g2        : 8   ; /* [15..8]  */
        unsigned int    mc_strength_ming      : 8   ; /* [23..16]  */
        unsigned int    mc_strength_maxg      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMCSTRENGTH1;

/* Define the union U_VPSS_DIEFUSION0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_y_mcw               : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    k_y_mcbld             : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    k_c_mcw               : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    k_c_mcbld             : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFUSION0;

/* Define the union U_VPSS_DIEFUSION1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x0_mcw_adj            : 8   ; /* [7..0]  */
        unsigned int    k0_mcw_adj            : 8   ; /* [15..8]  */
        unsigned int    g0_mcw_adj            : 12  ; /* [27..16]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFUSION1;

/* Define the union U_VPSS_DIEFUSION2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_mcw_adj            : 8   ; /* [7..0]  */
        unsigned int    x0_mcbld              : 8   ; /* [15..8]  */
        unsigned int    k0_mcbld              : 8   ; /* [23..16]  */
        unsigned int    k1_mcbld              : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFUSION2;

/* Define the union U_VPSS_DIEFUSION3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g0_mcbld              : 12  ; /* [11..0]  */
        unsigned int    k_curw_mcbld          : 5   ; /* [16..12]  */
        unsigned int    reserved_0            : 3   ; /* [19..17]  */
        unsigned int    mc_lai_bldmode        : 1   ; /* [20]  */
        unsigned int    reserved_1            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEFUSION3;

/* Define the union U_VPSS_DIEMAGBMTHD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ma_gbm_thd1           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    ma_gbm_thd0           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMAGBMTHD0;

/* Define the union U_VPSS_DIEMAGBMTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ma_gbm_thd3           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    ma_gbm_thd2           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMAGBMTHD1;

/* Define the union U_VPSS_DIEMCGBMCOEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mtth0_gmd             : 4   ; /* [3..0]  */
        unsigned int    mtth1_gmd             : 5   ; /* [8..4]  */
        unsigned int    reserved_0            : 3   ; /* [11..9]  */
        unsigned int    mtth2_gmd             : 6   ; /* [17..12]  */
        unsigned int    reserved_1            : 2   ; /* [19..18]  */
        unsigned int    mtth3_gmd             : 6   ; /* [25..20]  */
        unsigned int    reserved_2            : 2   ; /* [27..26]  */
        unsigned int    mtfilten_gmd          : 1   ; /* [28]  */
        unsigned int    reserved_3            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMCGBMCOEF0;

/* Define the union U_VPSS_DIEMCGBMCOEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_maxmag_gmd          : 4   ; /* [3..0]  */
        unsigned int    k_difh_gmd            : 7   ; /* [10..4]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    k_mag_gmd             : 8   ; /* [19..12]  */
        unsigned int    reserved_1            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEMCGBMCOEF1;

/* Define the union U_VPSS_DIEKMAG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    kmagh_1               : 7   ; /* [6..0]  */
        unsigned int    kmagh_2               : 7   ; /* [13..7]  */
        unsigned int    kmagv_1               : 5   ; /* [18..14]  */
        unsigned int    kmagv_2               : 5   ; /* [23..19]  */
        unsigned int    khoredge              : 5   ; /* [28..24]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEKMAG1;

/* Define the union U_VPSS_DIEKMAG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scaler_horedge        : 3   ; /* [2..0]  */
        unsigned int    frame_mag_en          : 1   ; /* [3]  */
        unsigned int    motion_limt_1         : 8   ; /* [11..4]  */
        unsigned int    motion_limt_2         : 8   ; /* [19..12]  */
        unsigned int    scaler_framemotion    : 3   ; /* [22..20]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIEKMAG2;

/* Define the union U_VPSS_DIE_S3ADD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dir_ratio_c           : 4   ; /* [3..0]  */
        unsigned int    edge_str_coring_c     : 5   ; /* [8..4]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DIE_S3ADD;

/* Define the union U_VPSS_PDPHISTTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hist_thd0             : 8   ; /* [7..0]  */
        unsigned int    hist_thd1             : 8   ; /* [15..8]  */
        unsigned int    hist_thd2             : 8   ; /* [23..16]  */
        unsigned int    hist_thd3             : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPHISTTHD1;

/* Define the union U_VPSS_PDPCCMOV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mov_coring_blk        : 8   ; /* [7..0]  */
        unsigned int    mov_coring_tkr        : 8   ; /* [15..8]  */
        unsigned int    mov_coring_norm       : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPCCMOV;

/* Define the union U_VPSS_PDCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bitsmov2r             : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 16  ; /* [18..3]  */
        unsigned int    lasi_mode             : 1   ; /* [19]  */
        unsigned int    reserved_1            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDCTRL;

/* Define the union U_VPSS_PDBLKTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 20  ; /* [19..0]  */
        unsigned int    diff_movblk_thd       : 8   ; /* [27..20]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDBLKTHD;

/* Define the union U_VPSS_PDUMTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    um_thd0               : 8   ; /* [7..0]  */
        unsigned int    um_thd1               : 8   ; /* [15..8]  */
        unsigned int    um_thd2               : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDUMTHD;

/* Define the union U_VPSS_PDPCCCORING */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coring_tkr            : 8   ; /* [7..0]  */
        unsigned int    coring_norm           : 8   ; /* [15..8]  */
        unsigned int    coring_blk            : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPCCCORING;

/* Define the union U_VPSS_PDPCCHTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pcc_hthd              : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPCCHTHD;

/* Define the union U_VPSS_PDPCCVTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pcc_vthd0             : 8   ; /* [7..0]  */
        unsigned int    pcc_vthd1             : 8   ; /* [15..8]  */
        unsigned int    pcc_vthd2             : 8   ; /* [23..16]  */
        unsigned int    pcc_vthd3             : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDPCCVTHD;

/* Define the union U_VPSS_PDITDIFFVTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    itdiff_vthd0          : 8   ; /* [7..0]  */
        unsigned int    itdiff_vthd1          : 8   ; /* [15..8]  */
        unsigned int    itdiff_vthd2          : 8   ; /* [23..16]  */
        unsigned int    itdiff_vthd3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDITDIFFVTHD;

/* Define the union U_VPSS_PDLASITHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lasi_coring_thd       : 8   ; /* [7..0]  */
        unsigned int    lasi_edge_thd         : 8   ; /* [15..8]  */
        unsigned int    lasi_mov_thd          : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDLASITHD;

/* Define the union U_VPSS_PDLASIMODE0COEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lasi_txt_alpha        : 8   ; /* [7..0]  */
        unsigned int    lasi_txt_coring       : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDLASIMODE0COEF;

/* Define the union U_VPSS_PDLASIMODE1COEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lasi_txt_thd0         : 8   ; /* [7..0]  */
        unsigned int    lasi_txt_thd1         : 8   ; /* [15..8]  */
        unsigned int    lasi_txt_thd2         : 8   ; /* [23..16]  */
        unsigned int    lasi_txt_thd3         : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDLASIMODE1COEF;

/* Define the union U_VPSS_PDREGION */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    region1_y_end         : 12  ; /* [11..0]  */
        unsigned int    region1_y_stt         : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_PDREGION;

/* Define the union U_VPSS_MCDI_RGDIFY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lmt_rgdify            : 10  ; /* [9..0]  */
        unsigned int    core_rgdify           : 4   ; /* [13..10]  */
        unsigned int    g_rgdifycore          : 10  ; /* [23..14]  */
        unsigned int    k_rgdifycore          : 4   ; /* [27..24]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGDIFY;

/* Define the union U_VPSS_MCDI_RGSAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_tpdif_rgsad         : 9   ; /* [8..0]  */
        unsigned int    k_tpdif_rgsad         : 6   ; /* [14..9]  */
        unsigned int    kmv_rgsad             : 7   ; /* [21..15]  */
        unsigned int    reserved_0            : 1   ; /* [22]  */
        unsigned int    coef_sadlpf           : 3   ; /* [25..23]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGSAD;

/* Define the union U_VPSS_MCDI_RGMV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    th_0mvsad_rgmv        : 10  ; /* [9..0]  */
        unsigned int    th_saddif_rgmv        : 9   ; /* [18..10]  */
        unsigned int    thmag_rgmv            : 8   ; /* [26..19]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMV;

/* Define the union U_VPSS_MCDI_RGMAG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lmt_mag_rg            : 10  ; /* [9..0]  */
        unsigned int    core_mag_rg           : 4   ; /* [13..10]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMAG0;

/* Define the union U_VPSS_MCDI_RGMAG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    en_mvadj_rgmvls       : 1   ; /* [0]  */
        unsigned int    th_mvadj_rgmvls       : 4   ; /* [4..1]  */
        unsigned int    k_mag_rgmvls          : 4   ; /* [8..5]  */
        unsigned int    core_mag_rgmvls       : 7   ; /* [15..9]  */
        unsigned int    k_mv_rgmvls           : 5   ; /* [20..16]  */
        unsigned int    core_mv_rgmvls        : 5   ; /* [25..21]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMAG1;

/* Define the union U_VPSS_MCDI_RGLS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_sadcore_rgmv        : 4   ; /* [3..0]  */
        unsigned int    th_sad_rgls           : 5   ; /* [8..4]  */
        unsigned int    th_mag_rgls           : 6   ; /* [14..9]  */
        unsigned int    k_sad_rgls            : 4   ; /* [18..15]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGLS;

/* Define the union U_VPSS_MCDI_SEL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    force_mvx             : 8   ; /* [7..0]  */
        unsigned int    force_mven            : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_SEL;

/* Define the union U_VPSS_MCDI_DLT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    th_hblkdist_mvdlt     : 4   ; /* [3..0]  */
        unsigned int    th_vblkdist_mvdlt     : 4   ; /* [7..4]  */
        unsigned int    th_ls_mvdlt           : 4   ; /* [11..8]  */
        unsigned int    th_rgmvx_mvdlt        : 4   ; /* [15..12]  */
        unsigned int    th_blkmvx_mvdlt       : 3   ; /* [18..16]  */
        unsigned int    reserved_0            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_DLT0;

/* Define the union U_VPSS_MCDI_DLT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    thh_sad_mvdlt         : 5   ; /* [4..0]  */
        unsigned int    thl_sad_mvdlt         : 7   ; /* [11..5]  */
        unsigned int    g_mag_mvdlt           : 6   ; /* [17..12]  */
        unsigned int    th_mag_mvdlt          : 5   ; /* [22..18]  */
        unsigned int    k_sadcore_mvdlt       : 3   ; /* [25..23]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_DLT1;

/* Define the union U_VPSS_MCDI_RGMCW0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_core_simimv         : 5   ; /* [4..0]  */
        unsigned int    gl_core_simimv        : 3   ; /* [7..5]  */
        unsigned int    gh_core_simimv        : 6   ; /* [13..8]  */
        unsigned int    k_simimvw             : 6   ; /* [19..14]  */
        unsigned int    k_rglsw               : 5   ; /* [24..20]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMCW0;

/* Define the union U_VPSS_MCDI_RGMCW1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rgtb_en_mcw           : 1   ; /* [0]  */
        unsigned int    core_mvy_mcw          : 3   ; /* [3..1]  */
        unsigned int    k_mvy_mcw             : 6   ; /* [9..4]  */
        unsigned int    core_rgsadadj_mcw     : 9   ; /* [18..10]  */
        unsigned int    k_rgsadadj_mcw        : 4   ; /* [22..19]  */
        unsigned int    k_core_vsaddif        : 5   ; /* [27..23]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMCW1;

/* Define the union U_VPSS_MCDI_RGMCW2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gl_core_vsaddif       : 5   ; /* [4..0]  */
        unsigned int    gh_core_vsad_dif      : 7   ; /* [11..5]  */
        unsigned int    k_vsaddifw            : 6   ; /* [17..12]  */
        unsigned int    mode_rgysad_mcw       : 1   ; /* [18]  */
        unsigned int    core_rgmag_mcw        : 8   ; /* [26..19]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMCW2;

/* Define the union U_VPSS_MCDI_RGMCW3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x0_rgmag_mcw          : 9   ; /* [8..0]  */
        unsigned int    k0_rgmag_mcw          : 9   ; /* [17..9]  */
        unsigned int    g0_rgmag_mcw          : 8   ; /* [25..18]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMCW3;

/* Define the union U_VPSS_MCDI_RGMCW4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_rgmag_mcw          : 9   ; /* [8..0]  */
        unsigned int    core_rgsad_mcw        : 8   ; /* [16..9]  */
        unsigned int    x0_rgsad_mcw          : 10  ; /* [26..17]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMCW4;

/* Define the union U_VPSS_MCDI_RGMCW5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k0_rgsad_mcw          : 9   ; /* [8..0]  */
        unsigned int    g0_rgsad_mcw          : 8   ; /* [16..9]  */
        unsigned int    k1_rgsad_mcw          : 9   ; /* [25..17]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMCW5;

/* Define the union U_VPSS_MCDI_RGMCW6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x0_smrg_mcw           : 8   ; /* [7..0]  */
        unsigned int    k0_smrg_mcw           : 8   ; /* [15..8]  */
        unsigned int    x_rgsad_mcw           : 8   ; /* [23..16]  */
        unsigned int    k_rgsad_mcw           : 6   ; /* [29..24]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_RGMCW6;

/* Define the union U_VPSS_MCDI_TPMCW0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x0_tpmvdist_mcw       : 8   ; /* [7..0]  */
        unsigned int    k0_tpmvdist_mcw       : 7   ; /* [14..8]  */
        unsigned int    g0_tpmvdist_mcw       : 8   ; /* [22..15]  */
        unsigned int    k1_tpmvdist_mcw       : 7   ; /* [29..23]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_TPMCW0;

/* Define the union U_VPSS_MCDI_TPMCW1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_minmvdist_mcw       : 4   ; /* [3..0]  */
        unsigned int    k_avgmvdist_mcw       : 4   ; /* [7..4]  */
        unsigned int    b_core_tpmvdist_mcw   : 3   ; /* [10..8]  */
        unsigned int    k_core_tpmvdist_mcw   : 3   ; /* [13..11]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_TPMCW1;

/* Define the union U_VPSS_MCDI_WNDMCW0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_difhcore_mcw        : 5   ; /* [4..0]  */
        unsigned int    k_difvcore_mcw        : 6   ; /* [10..5]  */
        unsigned int    k_max_core_mcw        : 4   ; /* [14..11]  */
        unsigned int    k_max_dif_mcw         : 4   ; /* [18..15]  */
        unsigned int    k1_max_mag_mcw        : 4   ; /* [22..19]  */
        unsigned int    k0_max_mag_mcw        : 4   ; /* [26..23]  */
        unsigned int    k_tbdif_mcw           : 4   ; /* [30..27]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_WNDMCW0;

/* Define the union U_VPSS_MCDI_WNDMCW1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_tbmag_mcw           : 4   ; /* [3..0]  */
        unsigned int    x0_mag_wnd_mcw        : 7   ; /* [10..4]  */
        unsigned int    k0_mag_wnd_mcw        : 4   ; /* [14..11]  */
        unsigned int    g0_mag_wnd_mcw        : 6   ; /* [20..15]  */
        unsigned int    k1_mag_wnd_mcw        : 4   ; /* [24..21]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_WNDMCW1;

/* Define the union U_VPSS_MCDI_WNDMCW2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g1_mag_wnd_mcw        : 9   ; /* [8..0]  */
        unsigned int    x0_sad_wnd_mcw        : 7   ; /* [15..9]  */
        unsigned int    k0_sad_wnd_mcw        : 5   ; /* [20..16]  */
        unsigned int    g0_sad_wnd_mcw        : 8   ; /* [28..21]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_WNDMCW2;

/* Define the union U_VPSS_MCDI_WNDMCW3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_sad_wnd_mcw        : 5   ; /* [4..0]  */
        unsigned int    g1_sad_wnd_mcw        : 9   ; /* [13..5]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_WNDMCW3;

/* Define the union U_VPSS_MCDI_VERTWEIGHT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_max_hvdif_dw        : 4   ; /* [3..0]  */
        unsigned int    gain_lpf_dw           : 4   ; /* [7..4]  */
        unsigned int    core_bhvdif_dw        : 4   ; /* [11..8]  */
        unsigned int    k_bhvdif_dw           : 7   ; /* [18..12]  */
        unsigned int    reserved_0            : 1   ; /* [19]  */
        unsigned int    b_bhvdif_dw           : 3   ; /* [22..20]  */
        unsigned int    reserved_1            : 1   ; /* [23]  */
        unsigned int    b_hvdif_dw            : 3   ; /* [26..24]  */
        unsigned int    reserved_2            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_VERTWEIGHT0;

/* Define the union U_VPSS_MCDI_VERTWEIGHT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_hvdif_dw         : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    k_difv_dw             : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    core_mv_dw            : 4   ; /* [19..16]  */
        unsigned int    b_mv_dw               : 6   ; /* [25..20]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_VERTWEIGHT1;

/* Define the union U_VPSS_MCDI_VERTWEIGHT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x0_hvdif_dw           : 9   ; /* [8..0]  */
        unsigned int    k0_hvdif_dw           : 4   ; /* [12..9]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    g0_hvdif_dw           : 9   ; /* [24..16]  */
        unsigned int    k1_hvdif_dw           : 6   ; /* [30..25]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_VERTWEIGHT2;

/* Define the union U_VPSS_MCDI_VERTWEIGHT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x0_mv_dw              : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    k0_mv_dw              : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    g0_mv_dw              : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    k1_mv_dw              : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_VERTWEIGHT3;

/* Define the union U_VPSS_MCDI_VERTWEIGHT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x0_mt_dw              : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    k0_mt_dw              : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    g0_mt_dw              : 8   ; /* [23..16]  */
        unsigned int    k1_mt_dw              : 6   ; /* [29..24]  */
        unsigned int    reserved_2            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_VERTWEIGHT4;

/* Define the union U_VPSS_MCDI_VERTWEIGHT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g0_mv_mt              : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    x0_mv_mt              : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    k1_mv_mt              : 5   ; /* [16..12]  */
        unsigned int    reserved_2            : 7   ; /* [23..17]  */
        unsigned int    b_mt_dw               : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_VERTWEIGHT5;

/* Define the union U_VPSS_MCDI_MC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_up_mclpfv        : 5   ; /* [4..0]  */
        unsigned int    gain_dn_mclpfv        : 5   ; /* [9..5]  */
        unsigned int    gain_mclpfh           : 5   ; /* [14..10]  */
        unsigned int    rs_pxlmag_mcw         : 1   ; /* [15]  */
        unsigned int    x_pxlmag_mcw          : 3   ; /* [18..16]  */
        unsigned int    reserved_0            : 1   ; /* [19]  */
        unsigned int    k_pxlmag_mcw          : 7   ; /* [26..20]  */
        unsigned int    reserved_1            : 1   ; /* [27]  */
        unsigned int    mclpf_mode            : 1   ; /* [28]  */
        unsigned int    reserved_2            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_MC0;

/* Define the union U_VPSS_MCDI_MC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_pxlmag_mcw          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_MC1;

/* Define the union U_VPSS_MCDI_MC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_y_vertw             : 5   ; /* [4..0]  */
        unsigned int    k_c_vertw             : 7   ; /* [11..5]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_MC2;

/* Define the union U_VPSS_MCDI_MC3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k_delta               : 5   ; /* [4..0]  */
        unsigned int    bdh_mcpos             : 3   ; /* [7..5]  */
        unsigned int    bdv_mcpos             : 3   ; /* [10..8]  */
        unsigned int    x0_mv_mc              : 3   ; /* [13..11]  */
        unsigned int    k1_mv_mc              : 6   ; /* [19..14]  */
        unsigned int    x_fstmt_mc            : 5   ; /* [24..20]  */
        unsigned int    k_fstmt_mc            : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_MC3;

/* Define the union U_VPSS_MCDI_MC4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_fstmt_mc            : 5   ; /* [4..0]  */
        unsigned int    x_slmt_mc             : 5   ; /* [9..5]  */
        unsigned int    k_slmt_mc             : 5   ; /* [14..10]  */
        unsigned int    g_slmt_mc             : 6   ; /* [20..15]  */
        unsigned int    x_hfcore_mc           : 5   ; /* [25..21]  */
        unsigned int    k_hfcore_mc           : 5   ; /* [30..26]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_MC4;

/* Define the union U_VPSS_MCDI_MC5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_hfcore_mc           : 6   ; /* [5..0]  */
        unsigned int    c0_mc                 : 12  ; /* [17..6]  */
        unsigned int    r0_mc                 : 12  ; /* [29..18]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_MC5;

/* Define the union U_VPSS_MCDI_MC6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    c1_mc                 : 12  ; /* [11..0]  */
        unsigned int    r1_mc                 : 12  ; /* [23..12]  */
        unsigned int    mcmvrange             : 6   ; /* [29..24]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_MC6;

/* Define the union U_VPSS_MCDI_MC7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scenechange_mc        : 1   ; /* [0]  */
        unsigned int    x_frcount_mc          : 5   ; /* [5..1]  */
        unsigned int    k_frcount_mc          : 7   ; /* [12..6]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_MC7;

/* Define the union U_VPSS_MCDI_LCDINEW0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mcstartr              : 8   ; /* [7..0]  */
        unsigned int    mcstartc              : 8   ; /* [15..8]  */
        unsigned int    mcendr                : 8   ; /* [23..16]  */
        unsigned int    mcendc                : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_LCDINEW0;

/* Define the union U_VPSS_MCDI_LCDINEW1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    movethdh              : 6   ; /* [5..0]  */
        unsigned int    movethdl              : 6   ; /* [11..6]  */
        unsigned int    movecorig             : 6   ; /* [17..12]  */
        unsigned int    movegain              : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_LCDINEW1;

/* Define the union U_VPSS_MCDI_NUMT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    numt_lpf_en           : 1   ; /* [0]  */
        unsigned int    numt_coring           : 6   ; /* [6..1]  */
        unsigned int    numt_gain             : 8   ; /* [14..7]  */
        unsigned int    mc_numt_blden         : 1   ; /* [15]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_NUMT;

/* Define the union U_VPSS_MCDI_S3ADD0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_rglsw            : 3   ; /* [2..0]  */
        unsigned int    k0_hfvline            : 3   ; /* [5..3]  */
        unsigned int    k1_hfvline            : 3   ; /* [8..6]  */
        unsigned int    core_hfvline          : 6   ; /* [14..9]  */
        unsigned int    k0_hw                 : 6   ; /* [20..15]  */
        unsigned int    k1_hw                 : 6   ; /* [26..21]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_S3ADD0;

/* Define the union U_VPSS_MCDI_S3ADD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_hw                  : 7   ; /* [6..0]  */
        unsigned int    b_core0_hw            : 4   ; /* [10..7]  */
        unsigned int    k_core0_hw            : 4   ; /* [14..11]  */
        unsigned int    core1_hw              : 4   ; /* [18..15]  */
        unsigned int    subpix_mc_en          : 1   ; /* [19]  */
        unsigned int    g_difcore_mcw         : 9   ; /* [28..20]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_S3ADD1;

/* Define the union U_VPSS_MCDI_S3ADD2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rp_k1_mag_wnd_mcw     : 4   ; /* [3..0]  */
        unsigned int    rp_k1_sad_wnd_mcw     : 5   ; /* [8..4]  */
        unsigned int    x0_sadr_wnd_mcw       : 7   ; /* [15..9]  */
        unsigned int    k0_sadr_wnd_mcw       : 4   ; /* [19..16]  */
        unsigned int    g0_sadr_wnd_mcw       : 8   ; /* [27..20]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_S3ADD2;

/* Define the union U_VPSS_MCDI_S3ADD3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    k1_sadr_wnd_mcw       : 4   ; /* [3..0]  */
        unsigned int    g1_sadr_wnd_mcw       : 9   ; /* [12..4]  */
        unsigned int    k_p1cfdifh_mcw        : 4   ; /* [16..13]  */
        unsigned int    k_mcdifv_mcw          : 4   ; /* [20..17]  */
        unsigned int    th_cur_blksad         : 9   ; /* [29..21]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_S3ADD3;

/* Define the union U_VPSS_MCDI_S3ADD4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    thh_neigh_blksad      : 9   ; /* [8..0]  */
        unsigned int    thl_neigh_blksad      : 9   ; /* [17..9]  */
        unsigned int    th_cur_blkmotion      : 5   ; /* [22..18]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_S3ADD4;

/* Define the union U_VPSS_MCDI_S3ADD5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    th_rgmv_mag           : 10  ; /* [9..0]  */
        unsigned int    blkmv_update_en       : 1   ; /* [10]  */
        unsigned int    k_rpcounter           : 3   ; /* [13..11]  */
        unsigned int    rpcounterth           : 3   ; /* [16..14]  */
        unsigned int    rp_mvxth_rgmv         : 3   ; /* [19..17]  */
        unsigned int    rp_difmvxth_rgmv      : 4   ; /* [23..20]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_S3ADD5;

/* Define the union U_VPSS_MCDI_S3ADD6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rp_difsadth_rgmv      : 8   ; /* [7..0]  */
        unsigned int    rp_sadth_rgmv         : 9   ; /* [16..8]  */
        unsigned int    rp_magth_rgmv         : 10  ; /* [26..17]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_S3ADD6;

/* Define the union U_VPSS_MCDI_S3ADD7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rp_difmvxth_sp        : 3   ; /* [2..0]  */
        unsigned int    rp_difsadth_tb        : 9   ; /* [11..3]  */
        unsigned int    k1_tpdif_rgsad        : 6   ; /* [17..12]  */
        unsigned int    submv_sadchk_en       : 1   ; /* [18]  */
        unsigned int    rp_en                 : 1   ; /* [19]  */
        unsigned int    difvt_mode            : 1   ; /* [20]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_S3ADD7;

/* Define the union U_VPSS_MCDI_STILLCNT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cntlut_0              : 5   ; /* [4..0]  */
        unsigned int    cntlut_1              : 5   ; /* [9..5]  */
        unsigned int    cntlut_2              : 5   ; /* [14..10]  */
        unsigned int    cntlut_3              : 5   ; /* [19..15]  */
        unsigned int    cntlut_4              : 5   ; /* [24..20]  */
        unsigned int    cntlut_5              : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_STILLCNT0;

/* Define the union U_VPSS_MCDI_STILLCNT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cntlut_6              : 5   ; /* [4..0]  */
        unsigned int    cntlut_7              : 5   ; /* [9..5]  */
        unsigned int    cntlut_8              : 5   ; /* [14..10]  */
        unsigned int    mc_mtshift            : 1   ; /* [15]  */
        unsigned int    mcw_scnt_en           : 1   ; /* [16]  */
        unsigned int    mcw_scnt_gain         : 9   ; /* [25..17]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_STILLCNT1;

/* Define the union U_VPSS_MCDI_DEMO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    demo_en               : 1   ; /* [0]  */
        unsigned int    demo_mode_l           : 2   ; /* [2..1]  */
        unsigned int    demo_mode_r           : 2   ; /* [4..3]  */
        unsigned int    demo_border           : 12  ; /* [16..5]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_MCDI_DEMO;

/* Define the union U_VPSS_VHD0_HSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hratio                : 24  ; /* [23..0]  */
        unsigned int    hfir_order            : 1   ; /* [24]  */
        unsigned int    hchfir_en             : 1   ; /* [25]  */
        unsigned int    hlfir_en              : 1   ; /* [26]  */
        unsigned int    reserved_0            : 1   ; /* [27]  */
        unsigned int    hchmid_en             : 1   ; /* [28]  */
        unsigned int    hlmid_en              : 1   ; /* [29]  */
        unsigned int    hchmsc_en             : 1   ; /* [30]  */
        unsigned int    hlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_HSP;

/* Define the union U_VPSS_VHD0_HLOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_loffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_HLOFFSET;

/* Define the union U_VPSS_VHD0_HCOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hor_coffset           : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_HCOFFSET;

/* Define the union U_VPSS_VHD0_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 21  ; /* [20..0]  */
        unsigned int    zme_out_fmt           : 2   ; /* [22..21]  */
        unsigned int    vchfir_en             : 1   ; /* [23]  */
        unsigned int    vlfir_en              : 1   ; /* [24]  */
        unsigned int    reserved_1            : 3   ; /* [27..25]  */
        unsigned int    vchmid_en             : 1   ; /* [28]  */
        unsigned int    vlmid_en              : 1   ; /* [29]  */
        unsigned int    vchmsc_en             : 1   ; /* [30]  */
        unsigned int    vlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_VSP;

/* Define the union U_VPSS_VHD0_VSR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vratio                : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_VSR;

/* Define the union U_VPSS_VHD0_VOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vchroma_offset        : 16  ; /* [15..0]  */
        unsigned int    vluma_offset          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_VHD0_VOFFSET;

/* Define the union U_VPSS_DB_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_en                 : 1   ; /* [0]  */
        unsigned int    dm_en                 : 1   ; /* [1]  */
        unsigned int    nr_en                 : 1   ; /* [2]  */
        unsigned int    db_lum_hor_en         : 1   ; /* [3]  */
        unsigned int    reserved_0            : 5   ; /* [8..4]  */
        unsigned int    dbm_demo_en           : 1   ; /* [9]  */
        unsigned int    dbm_demo_mode         : 1   ; /* [10]  */
        unsigned int    reserved_1            : 2   ; /* [12..11]  */
        unsigned int    det_hy_en             : 1   ; /* [13]  */
        unsigned int    reserved_2            : 2   ; /* [15..14]  */
        unsigned int    dbm_out_mode          : 3   ; /* [18..16]  */
        unsigned int    reserved_3            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_CTRL;

/* Define the union U_VPSS_DBM_DEMO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbm_demo_pos_x        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBM_DEMO;

/* Define the union U_VPSS_DB_DIR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_grad_sub_ratio     : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    db_ctrst_thresh       : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_DIR;

/* Define the union U_VPSS_DB_BLK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_lum_h_blk_size     : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_BLK;

/* Define the union U_VPSS_DB_RATIO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_lum_hor_scale_ratio : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 6   ; /* [7..2]  */
        unsigned int    db_lum_hor_filter_sel : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    db_global_db_strenth_lum : 4   ; /* [15..12]  */
        unsigned int    reserved_2            : 4   ; /* [19..16]  */
        unsigned int    db_lum_hor_txt_win_size : 2   ; /* [21..20]  */
        unsigned int    reserved_3            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_RATIO;

/* Define the union U_VPSS_DB_LHHF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_lum_hor_hf_diff_core : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    db_lum_hor_hf_diff_gain1 : 4   ; /* [11..8]  */
        unsigned int    db_lum_hor_hf_diff_gain2 : 4   ; /* [15..12]  */
        unsigned int    db_lum_hor_hf_var_core : 7   ; /* [22..16]  */
        unsigned int    reserved_1            : 1   ; /* [23]  */
        unsigned int    db_lum_hor_hf_var_gain1 : 4   ; /* [27..24]  */
        unsigned int    db_lum_hor_hf_var_gain2 : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LHHF;

/* Define the union U_VPSS_DB_LVHF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 16  ; /* [15..0]  */
        unsigned int    db_lum_hor_adj_gain   : 5   ; /* [20..16]  */
        unsigned int    db_lum_hor_bord_adj_gain : 3   ; /* [23..21]  */
        unsigned int    reserved_1            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LVHF;

/* Define the union U_VPSS_DB_CTRS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_ctrst_adj_core     : 5   ; /* [4..0]  */
        unsigned int    db_dir_smooth_mode    : 2   ; /* [6..5]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    db_ctrst_adj_gain1    : 4   ; /* [11..8]  */
        unsigned int    db_ctrst_adj_gain2    : 4   ; /* [15..12]  */
        unsigned int    db_max_lum_hor_db_dist : 4   ; /* [19..16]  */
        unsigned int    reserved_1            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_CTRS;

/* Define the union U_VPSS_DB_LUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_lum_hor_delta_lut_p0 : 4   ; /* [3..0]  */
        unsigned int    db_lum_hor_delta_lut_p1 : 4   ; /* [7..4]  */
        unsigned int    db_lum_hor_delta_lut_p2 : 4   ; /* [11..8]  */
        unsigned int    db_lum_hor_delta_lut_p3 : 4   ; /* [15..12]  */
        unsigned int    db_lum_hor_delta_lut_p4 : 4   ; /* [19..16]  */
        unsigned int    db_lum_hor_delta_lut_p5 : 4   ; /* [23..20]  */
        unsigned int    db_lum_hor_delta_lut_p6 : 4   ; /* [27..24]  */
        unsigned int    db_lum_hor_delta_lut_p7 : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT0;

/* Define the union U_VPSS_DB_LUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_lum_hor_delta_lut_p8 : 4   ; /* [3..0]  */
        unsigned int    db_lum_hor_delta_lut_p9 : 4   ; /* [7..4]  */
        unsigned int    db_lum_hor_delta_lut_p10 : 4   ; /* [11..8]  */
        unsigned int    db_lum_hor_delta_lut_p11 : 4   ; /* [15..12]  */
        unsigned int    db_lum_hor_delta_lut_p12 : 4   ; /* [19..16]  */
        unsigned int    db_lum_hor_delta_lut_p13 : 4   ; /* [23..20]  */
        unsigned int    db_lum_hor_delta_lut_p14 : 4   ; /* [27..24]  */
        unsigned int    db_lum_hor_delta_lut_p15 : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT1;

/* Define the union U_VPSS_DB_LUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_lum_h_str_fade_lut_p0 : 3   ; /* [2..0]  */
        unsigned int    db_lum_h_str_fade_lut_p1 : 3   ; /* [5..3]  */
        unsigned int    db_lum_h_str_fade_lut_p2 : 3   ; /* [8..6]  */
        unsigned int    db_lum_h_str_fade_lut_p3 : 3   ; /* [11..9]  */
        unsigned int    db_lum_h_str_fade_lut_p4 : 3   ; /* [14..12]  */
        unsigned int    db_lum_h_str_fade_lut_p5 : 3   ; /* [17..15]  */
        unsigned int    db_lum_h_str_fade_lut_p6 : 3   ; /* [20..18]  */
        unsigned int    db_lum_h_str_fade_lut_p7 : 3   ; /* [23..21]  */
        unsigned int    db_lum_h_str_fade_lut_p8 : 3   ; /* [26..24]  */
        unsigned int    db_lum_h_str_fade_lut_p9 : 3   ; /* [29..27]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT2;

/* Define the union U_VPSS_DB_LUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_lum_h_str_fade_lut_p10 : 3   ; /* [2..0]  */
        unsigned int    db_lum_h_str_fade_lut_p11 : 3   ; /* [5..3]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT3;

/* Define the union U_VPSS_DB_LUT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_dir_str_gain_lut_p0 : 4   ; /* [3..0]  */
        unsigned int    db_dir_str_gain_lut_p1 : 4   ; /* [7..4]  */
        unsigned int    db_dir_str_gain_lut_p2 : 4   ; /* [11..8]  */
        unsigned int    db_dir_str_gain_lut_p3 : 4   ; /* [15..12]  */
        unsigned int    db_dir_str_gain_lut_p4 : 4   ; /* [19..16]  */
        unsigned int    db_dir_str_gain_lut_p5 : 4   ; /* [23..20]  */
        unsigned int    db_dir_str_gain_lut_p6 : 4   ; /* [27..24]  */
        unsigned int    db_dir_str_gain_lut_p7 : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT4;

/* Define the union U_VPSS_DB_LUT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_dir_str_lut_p0     : 4   ; /* [3..0]  */
        unsigned int    db_dir_str_lut_p1     : 4   ; /* [7..4]  */
        unsigned int    db_dir_str_lut_p2     : 4   ; /* [11..8]  */
        unsigned int    db_dir_str_lut_p3     : 4   ; /* [15..12]  */
        unsigned int    db_dir_str_lut_p4     : 4   ; /* [19..16]  */
        unsigned int    db_dir_str_lut_p5     : 4   ; /* [23..20]  */
        unsigned int    db_dir_str_lut_p6     : 4   ; /* [27..24]  */
        unsigned int    db_dir_str_lut_p7     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT5;

/* Define the union U_VPSS_DB_LUT6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    db_dir_str_lut_p8     : 4   ; /* [3..0]  */
        unsigned int    db_dir_str_lut_p9     : 4   ; /* [7..4]  */
        unsigned int    db_dir_str_lut_p10    : 4   ; /* [11..8]  */
        unsigned int    db_dir_str_lut_p11    : 4   ; /* [15..12]  */
        unsigned int    db_dir_str_lut_p12    : 4   ; /* [19..16]  */
        unsigned int    db_dir_str_lut_p13    : 4   ; /* [23..20]  */
        unsigned int    db_dir_str_lut_p14    : 4   ; /* [27..24]  */
        unsigned int    db_dir_str_lut_p15    : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DB_LUT6;

/* Define the union U_VPSS_DBD_THDEDGE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_hy_thd_edge       : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_THDEDGE;

/* Define the union U_VPSS_DBD_THDTXT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_hy_thd_txt        : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_THDTXT;

/* Define the union U_VPSS_DBD_LUTWGT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_det_lut_wgt0      : 4   ; /* [3..0]  */
        unsigned int    dbd_det_lut_wgt1      : 4   ; /* [7..4]  */
        unsigned int    dbd_det_lut_wgt2      : 4   ; /* [11..8]  */
        unsigned int    dbd_det_lut_wgt3      : 4   ; /* [15..12]  */
        unsigned int    dbd_det_lut_wgt4      : 4   ; /* [19..16]  */
        unsigned int    dbd_det_lut_wgt5      : 4   ; /* [23..20]  */
        unsigned int    dbd_det_lut_wgt6      : 4   ; /* [27..24]  */
        unsigned int    dbd_det_lut_wgt7      : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_LUTWGT0;

/* Define the union U_VPSS_DBD_LUTWGT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_det_lut_wgt8      : 4   ; /* [3..0]  */
        unsigned int    dbd_det_lut_wgt9      : 4   ; /* [7..4]  */
        unsigned int    dbd_det_lut_wgt10     : 4   ; /* [11..8]  */
        unsigned int    dbd_det_lut_wgt11     : 4   ; /* [15..12]  */
        unsigned int    dbd_det_lut_wgt12     : 4   ; /* [19..16]  */
        unsigned int    dbd_det_lut_wgt13     : 4   ; /* [23..20]  */
        unsigned int    dbd_det_lut_wgt14     : 4   ; /* [27..24]  */
        unsigned int    dbd_det_lut_wgt15     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_LUTWGT1;

/* Define the union U_VPSS_DBD_RTNBDTXT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_hy_rtn_bd_txt     : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_RTNBDTXT;

/* Define the union U_VPSS_DBD_TSTBLKNUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_hy_tst_blk_num    : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_TSTBLKNUM;

/* Define the union U_VPSS_DBD_HYRDX8BINLUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_hy_rdx8bin_lut0   : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    dbd_hy_rdx8bin_lut1   : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HYRDX8BINLUT0;

/* Define the union U_VPSS_DBD_HYRDX8BINLUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_hy_rdx8bin_lut2   : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    dbd_hy_rdx8bin_lut3   : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HYRDX8BINLUT1;

/* Define the union U_VPSS_DBD_HYRDX8BINLUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_hy_rdx8bin_lut4   : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    dbd_hy_rdx8bin_lut5   : 11  ; /* [22..12]  */
        unsigned int    reserved_1            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HYRDX8BINLUT2;

/* Define the union U_VPSS_DBD_HYRDX8BINLUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_hy_rdx8bin_lut6   : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_HYRDX8BINLUT3;

/* Define the union U_VPSS_DBD_BLKSIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_min_blk_size      : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    dbd_hy_max_blk_size   : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_BLKSIZE;

/* Define the union U_VPSS_DBD_FLAT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dbd_thr_flat          : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DBD_FLAT;

/* Define the union U_VPSS_DM_DIR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_grad_sub_ratio     : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 1   ; /* [5]  */
        unsigned int    dm_ctrst_thresh       : 2   ; /* [7..6]  */
        unsigned int    dm_opp_ang_ctrst_t    : 8   ; /* [15..8]  */
        unsigned int    dm_opp_ang_ctrst_div  : 2   ; /* [17..16]  */
        unsigned int    reserved_1            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_DIR;

/* Define the union U_VPSS_DM_EDGE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_mmf_set            : 1   ; /* [0]  */
        unsigned int    dm_init_val_step      : 2   ; /* [2..1]  */
        unsigned int    reserved_0            : 19  ; /* [21..3]  */
        unsigned int    dm_global_str         : 4   ; /* [25..22]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_EDGE;

/* Define the union U_VPSS_DM_LUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_sw_wht_lut_p0      : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    dm_sw_wht_lut_p1      : 7   ; /* [14..8]  */
        unsigned int    reserved_1            : 1   ; /* [15]  */
        unsigned int    dm_sw_wht_lut_p2      : 7   ; /* [22..16]  */
        unsigned int    reserved_2            : 1   ; /* [23]  */
        unsigned int    dm_sw_wht_lut_p3      : 7   ; /* [30..24]  */
        unsigned int    reserved_3            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT0;

/* Define the union U_VPSS_DM_LUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_sw_wht_lut_p4      : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    dm_limit_t            : 8   ; /* [15..8]  */
        unsigned int    dm_limit_t_10         : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT1;

/* Define the union U_VPSS_DM_LUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_dir_str_gain_lut_p0 : 4   ; /* [3..0]  */
        unsigned int    dm_dir_str_gain_lut_p1 : 4   ; /* [7..4]  */
        unsigned int    dm_dir_str_gain_lut_p2 : 4   ; /* [11..8]  */
        unsigned int    dm_dir_str_gain_lut_p3 : 4   ; /* [15..12]  */
        unsigned int    dm_dir_str_gain_lut_p4 : 4   ; /* [19..16]  */
        unsigned int    dm_dir_str_gain_lut_p5 : 4   ; /* [23..20]  */
        unsigned int    dm_dir_str_gain_lut_p6 : 4   ; /* [27..24]  */
        unsigned int    dm_dir_str_gain_lut_p7 : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT2;

/* Define the union U_VPSS_DM_LUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_dir_str_lut_p0     : 4   ; /* [3..0]  */
        unsigned int    dm_dir_str_lut_p1     : 4   ; /* [7..4]  */
        unsigned int    dm_dir_str_lut_p2     : 4   ; /* [11..8]  */
        unsigned int    dm_dir_str_lut_p3     : 4   ; /* [15..12]  */
        unsigned int    dm_dir_str_lut_p4     : 4   ; /* [19..16]  */
        unsigned int    dm_dir_str_lut_p5     : 4   ; /* [23..20]  */
        unsigned int    dm_dir_str_lut_p6     : 4   ; /* [27..24]  */
        unsigned int    dm_dir_str_lut_p7     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT3;

/* Define the union U_VPSS_DM_LUT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_dir_str_lut_p8     : 4   ; /* [3..0]  */
        unsigned int    dm_dir_str_lut_p9     : 4   ; /* [7..4]  */
        unsigned int    dm_dir_str_lut_p10    : 4   ; /* [11..8]  */
        unsigned int    dm_dir_str_lut_p11    : 4   ; /* [15..12]  */
        unsigned int    dm_dir_str_lut_p12    : 4   ; /* [19..16]  */
        unsigned int    dm_dir_str_lut_p13    : 4   ; /* [23..20]  */
        unsigned int    dm_dir_str_lut_p14    : 4   ; /* [27..24]  */
        unsigned int    dm_dir_str_lut_p15    : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT4;

/* Define the union U_VPSS_DM_DIRC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 18  ; /* [17..0]  */
        unsigned int    dm_mndir_opp_ctrst_t  : 8   ; /* [25..18]  */
        unsigned int    reserved_1            : 5   ; /* [30..26]  */
        unsigned int    dm_mmf_limit_en       : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_DIRC;

/* Define the union U_VPSS_DM_DIRO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 22  ; /* [21..0]  */
        unsigned int    dm_csw_trsnt_st_10    : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_DIRO;

/* Define the union U_VPSS_DM_LSW */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_lw_ctrst_t         : 8   ; /* [7..0]  */
        unsigned int    dm_lw_ctrst_t_10      : 10  ; /* [17..8]  */
        unsigned int    dm_csw_trsnt_st       : 8   ; /* [25..18]  */
        unsigned int    reserved_0            : 1   ; /* [26]  */
        unsigned int    dm_lsw_ratio          : 3   ; /* [29..27]  */
        unsigned int    reserved_1            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LSW;

/* Define the union U_VPSS_DM_MMFLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_mmf_lr             : 9   ; /* [8..0]  */
        unsigned int    dm_mmf_lr_10          : 11  ; /* [19..9]  */
        unsigned int    dm_csw_trsnt_lt       : 8   ; /* [27..20]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_MMFLR;

/* Define the union U_VPSS_DM_MMFSR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_mmf_sr             : 9   ; /* [8..0]  */
        unsigned int    dm_mmf_sr_10          : 11  ; /* [19..9]  */
        unsigned int    dm_csw_trsnt_lt_10    : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_MMFSR;

/* Define the union U_VPSS_DM_THR0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_limit_lsw_ratio    : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    dm_lim_res_blend_str1 : 4   ; /* [7..4]  */
        unsigned int    dm_lim_res_blend_str2 : 4   ; /* [11..8]  */
        unsigned int    dm_dir_blend_str      : 4   ; /* [15..12]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_THR0;

/* Define the union U_VPSS_DM_LUT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_trans_band_lut_p0  : 6   ; /* [5..0]  */
        unsigned int    dm_trans_band_lut_p1  : 6   ; /* [11..6]  */
        unsigned int    dm_trans_band_lut_p2  : 6   ; /* [17..12]  */
        unsigned int    dm_trans_band_lut_p3  : 6   ; /* [23..18]  */
        unsigned int    dm_trans_band_lut_p4  : 6   ; /* [29..24]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT5;

/* Define the union U_VPSS_DM_LUT6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_trans_band_lut_p5  : 6   ; /* [5..0]  */
        unsigned int    dm_trans_band_lut_p6  : 6   ; /* [11..6]  */
        unsigned int    dm_trans_band_lut_p7  : 6   ; /* [17..12]  */
        unsigned int    dm_trans_band_lut_p8  : 6   ; /* [23..18]  */
        unsigned int    dm_trans_band_lut_p9  : 6   ; /* [29..24]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT6;

/* Define the union U_VPSS_DM_LUT7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_trans_band_lut_p10 : 6   ; /* [5..0]  */
        unsigned int    dm_trans_band_lut_p11 : 6   ; /* [11..6]  */
        unsigned int    dm_trans_band_lut_p12 : 6   ; /* [17..12]  */
        unsigned int    dm_trans_band_lut_p13 : 6   ; /* [23..18]  */
        unsigned int    dm_trans_band_lut_p14 : 6   ; /* [29..24]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT7;

/* Define the union U_VPSS_DM_LUT8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_trans_band_lut_p15 : 6   ; /* [5..0]  */
        unsigned int    dm_trans_band_lut_p16 : 6   ; /* [11..6]  */
        unsigned int    dm_trans_band_lut_p17 : 6   ; /* [17..12]  */
        unsigned int    dm_trans_band_lut_p18 : 6   ; /* [23..18]  */
        unsigned int    dm_trans_band_lut_p19 : 6   ; /* [29..24]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT8;

/* Define the union U_VPSS_DM_LUT9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_trans_band_lut_p20 : 6   ; /* [5..0]  */
        unsigned int    dm_trans_band_lut_p21 : 6   ; /* [11..6]  */
        unsigned int    dm_trans_band_lut_p22 : 6   ; /* [17..12]  */
        unsigned int    dm_trans_band_lut_p23 : 6   ; /* [23..18]  */
        unsigned int    dm_trans_band_lut_p24 : 6   ; /* [29..24]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT9;

/* Define the union U_VPSS_DM_LUT10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_trans_band_lut_p25 : 6   ; /* [5..0]  */
        unsigned int    dm_trans_band_lut_p26 : 6   ; /* [11..6]  */
        unsigned int    dm_trans_band_lut_p27 : 6   ; /* [17..12]  */
        unsigned int    dm_trans_band_lut_p28 : 6   ; /* [23..18]  */
        unsigned int    dm_trans_band_lut_p29 : 6   ; /* [29..24]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT10;

/* Define the union U_VPSS_DM_LUT11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dm_trans_band_lut_p30 : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DM_LUT11;

/* Define the union U_VPSS_DB_BORD_FLAG0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_0    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG0;
/* Define the union U_VPSS_DB_BORD_FLAG1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_1    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG1;
/* Define the union U_VPSS_DB_BORD_FLAG2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_2    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG2;
/* Define the union U_VPSS_DB_BORD_FLAG3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_3    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG3;
/* Define the union U_VPSS_DB_BORD_FLAG4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_4    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG4;
/* Define the union U_VPSS_DB_BORD_FLAG5 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_5    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG5;
/* Define the union U_VPSS_DB_BORD_FLAG6 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_6    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG6;
/* Define the union U_VPSS_DB_BORD_FLAG7 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_7    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG7;
/* Define the union U_VPSS_DB_BORD_FLAG8 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_8    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG8;
/* Define the union U_VPSS_DB_BORD_FLAG9 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_9    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG9;
/* Define the union U_VPSS_DB_BORD_FLAG10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_10   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG10;
/* Define the union U_VPSS_DB_BORD_FLAG11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_11   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG11;
/* Define the union U_VPSS_DB_BORD_FLAG12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_12   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG12;
/* Define the union U_VPSS_DB_BORD_FLAG13 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_13   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG13;
/* Define the union U_VPSS_DB_BORD_FLAG14 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_14   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG14;
/* Define the union U_VPSS_DB_BORD_FLAG15 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_15   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG15;
/* Define the union U_VPSS_DB_BORD_FLAG16 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_16   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG16;
/* Define the union U_VPSS_DB_BORD_FLAG17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_17   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG17;
/* Define the union U_VPSS_DB_BORD_FLAG18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_18   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG18;
/* Define the union U_VPSS_DB_BORD_FLAG19 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_19   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG19;
/* Define the union U_VPSS_DB_BORD_FLAG20 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_20   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG20;
/* Define the union U_VPSS_DB_BORD_FLAG21 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_21   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG21;
/* Define the union U_VPSS_DB_BORD_FLAG22 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_22   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG22;
/* Define the union U_VPSS_DB_BORD_FLAG23 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_23   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG23;
/* Define the union U_VPSS_DB_BORD_FLAG24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_24   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG24;
/* Define the union U_VPSS_DB_BORD_FLAG25 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_25   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG25;
/* Define the union U_VPSS_DB_BORD_FLAG26 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_26   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG26;
/* Define the union U_VPSS_DB_BORD_FLAG27 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_27   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG27;
/* Define the union U_VPSS_DB_BORD_FLAG28 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_28   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG28;
/* Define the union U_VPSS_DB_BORD_FLAG29 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_29   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG29;
/* Define the union U_VPSS_DB_BORD_FLAG30 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_30   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG30;
/* Define the union U_VPSS_DB_BORD_FLAG31 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vpss_db_bord_flag_31   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DB_BORD_FLAG31;
/* Define the union U_VPSS_SNR_ENABLE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    ynr2den               : 1   ; /* [1]  */
        unsigned int    cnr2den               : 1   ; /* [2]  */
        unsigned int    motionedgeweighten    : 1   ; /* [3]  */
        unsigned int    colorweighten         : 1   ; /* [4]  */
        unsigned int    edgeprefilteren       : 1   ; /* [5]  */
        unsigned int    reserved_1            : 1   ; /* [6]  */
        unsigned int    test_en               : 1   ; /* [7]  */
        unsigned int    reserved_2            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_ENABLE;

/* Define the union U_VPSS_SNR_EDGE_RATIORANGE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edgemaxratio          : 4   ; /* [3..0]  */
        unsigned int    edgeminratio          : 4   ; /* [7..4]  */
        unsigned int    edgeoriratio          : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_RATIORANGE;

/* Define the union U_VPSS_SNR_EDGE_STRRANGE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edgemaxstrength       : 4   ; /* [3..0]  */
        unsigned int    edgeminstrength       : 4   ; /* [7..4]  */
        unsigned int    edgeoristrength       : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_STRRANGE;

/* Define the union U_VPSS_SNR_EDGE_STRTH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edgestrth1            : 10  ; /* [9..0]  */
        unsigned int    edgestrth2            : 10  ; /* [19..10]  */
        unsigned int    edgestrth3            : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_STRTH;

/* Define the union U_VPSS_SNR_EDGE_STRK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edgestrk1             : 6   ; /* [5..0]  */
        unsigned int    edgestrk2             : 6   ; /* [11..6]  */
        unsigned int    edgestrk3             : 6   ; /* [17..12]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_STRK;

/* Define the union U_VPSS_SNR_EDGE_MEANTH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edgemeanth1           : 10  ; /* [9..0]  */
        unsigned int    edgemeanth2           : 10  ; /* [19..10]  */
        unsigned int    edgemeanth3           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_MEANTH1;

/* Define the union U_VPSS_SNR_EDGE_MEANTH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edgemeanth4           : 10  ; /* [9..0]  */
        unsigned int    edgemeanth5           : 10  ; /* [19..10]  */
        unsigned int    edgemeanth6           : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_MEANTH2;

/* Define the union U_VPSS_SNR_EDGE_MEANTH3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edgemeanth7           : 10  ; /* [9..0]  */
        unsigned int    edgemeanth8           : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_MEANTH3;

/* Define the union U_VPSS_SNR_EDGE_MEANK1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edgemeank1            : 6   ; /* [5..0]  */
        unsigned int    edgemeank2            : 6   ; /* [11..6]  */
        unsigned int    edgemeank3            : 6   ; /* [17..12]  */
        unsigned int    edgemeank4            : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_MEANK1;

/* Define the union U_VPSS_SNR_EDGE_MEANK2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edgemeank5            : 6   ; /* [5..0]  */
        unsigned int    edgemeank6            : 6   ; /* [11..6]  */
        unsigned int    edgemeank7            : 6   ; /* [17..12]  */
        unsigned int    edgemeank8            : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_MEANK2;

/* Define the union U_VPSS_SNR_WIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y2dwinwidth           : 5   ; /* [4..0]  */
        unsigned int    y2dwinheight          : 4   ; /* [8..5]  */
        unsigned int    c2dwinwidth           : 4   ; /* [12..9]  */
        unsigned int    c2dwinheight          : 2   ; /* [14..13]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_WIN;

/* Define the union U_VPSS_SNR_STR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ysnrstr               : 8   ; /* [7..0]  */
        unsigned int    csnrstr               : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_STR;

/* Define the union U_VPSS_SNR_STR_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    stroffset0            : 2   ; /* [1..0]  */
        unsigned int    stroffset1            : 2   ; /* [3..2]  */
        unsigned int    stroffset2            : 2   ; /* [5..4]  */
        unsigned int    stroffset3            : 2   ; /* [7..6]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_STR_OFFSET;

/* Define the union U_VPSS_SNR_STR_ADJUST */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ystradjust            : 6   ; /* [5..0]  */
        unsigned int    cstradjust            : 6   ; /* [11..6]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_STR_ADJUST;

/* Define the union U_VPSS_SNR_SCHANGE_TH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scenechangeth         : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_SCHANGE_TH;

/* Define the union U_VPSS_SNR_EDGE_RATIO_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ratio1                : 9   ; /* [8..0]  */
        unsigned int    ratio2                : 9   ; /* [17..9]  */
        unsigned int    ratio3                : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_RATIO_1;

/* Define the union U_VPSS_SNR_EDGE_RATIO_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ratio4                : 9   ; /* [8..0]  */
        unsigned int    ratio5                : 9   ; /* [17..9]  */
        unsigned int    ratio6                : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_RATIO_2;

/* Define the union U_VPSS_SNR_EDGE_RATIO_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ratio7                : 9   ; /* [8..0]  */
        unsigned int    ratio8                : 9   ; /* [17..9]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_RATIO_3;

/* Define the union U_VPSS_SNR_EDGE_STR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge1                 : 4   ; /* [3..0]  */
        unsigned int    edge2                 : 4   ; /* [7..4]  */
        unsigned int    edge3                 : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_EDGE_STR;

/* Define the union U_VPSS_SNR_TEST_COLOR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    test_color_cb         : 10  ; /* [9..0]  */
        unsigned int    test_color_cr         : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_TEST_COLOR;

/* Define the union U_VPSS_SNR_SCHANGE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scenechange_info      : 8   ; /* [7..0]  */
        unsigned int    scenechange_en        : 1   ; /* [8]  */
        unsigned int    scenechange_mode1_en  : 1   ; /* [9]  */
        unsigned int    scenechange_bldk      : 10  ; /* [19..10]  */
        unsigned int    scenechange_bldcore   : 10  ; /* [29..20]  */
        unsigned int    scenechange_mode2_en  : 1   ; /* [30]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_SCHANGE;

/* Define the union U_VPSS_SNR_MT */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motionalpha           : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_MT;

/* Define the union U_VPSS_SNR_CBCR_W1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cb_begin1             : 6   ; /* [5..0]  */
        unsigned int    cr_begin1             : 6   ; /* [11..6]  */
        unsigned int    cb_end1               : 6   ; /* [17..12]  */
        unsigned int    cr_end1               : 6   ; /* [23..18]  */
        unsigned int    cbcr_weight1          : 4   ; /* [27..24]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_CBCR_W1;

/* Define the union U_VPSS_SNR_CBCR_W2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cb_begin2             : 6   ; /* [5..0]  */
        unsigned int    cr_begin2             : 6   ; /* [11..6]  */
        unsigned int    cb_end2               : 6   ; /* [17..12]  */
        unsigned int    cr_end2               : 6   ; /* [23..18]  */
        unsigned int    cbcr_weight2          : 4   ; /* [27..24]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_SNR_CBCR_W2;

/* Define the union U_MOTION_EDGE_LUT_01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut00     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut01     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut02     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut03     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut04     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut05     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut06     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut07     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_01;

/* Define the union U_MOTION_EDGE_LUT_02 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut08     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut09     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut0a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut0b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut0c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut0d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut0e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut0f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_02;

/* Define the union U_MOTION_EDGE_LUT_03 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut10     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut11     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut12     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut13     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut14     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut15     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut16     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut17     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_03;

/* Define the union U_MOTION_EDGE_LUT_04 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut18     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut19     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut1a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut1b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut1c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut1d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut1e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut1f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_04;

/* Define the union U_MOTION_EDGE_LUT_05 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut20     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut21     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut22     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut23     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut24     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut25     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut26     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut27     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_05;

/* Define the union U_MOTION_EDGE_LUT_06 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut28     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut29     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut2a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut2b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut2c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut2d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut2e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut2f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_06;

/* Define the union U_MOTION_EDGE_LUT_07 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut30     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut31     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut32     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut33     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut34     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut35     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut36     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut37     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_07;

/* Define the union U_MOTION_EDGE_LUT_08 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut38     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut39     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut3a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut3b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut3c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut3d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut3e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut3f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_08;

/* Define the union U_MOTION_EDGE_LUT_09 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut40     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut41     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut42     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut43     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut44     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut45     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut46     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut47     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_09;

/* Define the union U_MOTION_EDGE_LUT_10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut48     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut49     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut4a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut4b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut4c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut4d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut4e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut4f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_10;

/* Define the union U_MOTION_EDGE_LUT_11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut50     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut51     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut52     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut53     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut54     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut55     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut56     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut57     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_11;

/* Define the union U_MOTION_EDGE_LUT_12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut58     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut59     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut5a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut5b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut5c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut5d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut5e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut5f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_12;

/* Define the union U_MOTION_EDGE_LUT_13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut60     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut61     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut62     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut63     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut64     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut65     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut66     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut67     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_13;

/* Define the union U_MOTION_EDGE_LUT_14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut68     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut69     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut6a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut6b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut6c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut6d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut6e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut6f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_14;

/* Define the union U_MOTION_EDGE_LUT_15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut70     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut71     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut72     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut73     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut74     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut75     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut76     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut77     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_15;

/* Define the union U_MOTION_EDGE_LUT_16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut78     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut79     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut7a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut7b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut7c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut7d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut7e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut7f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_16;

/* Define the union U_MOTION_EDGE_LUT_17 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut80     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut81     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut82     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut83     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut84     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut85     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut86     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut87     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_17;

/* Define the union U_MOTION_EDGE_LUT_18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut88     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut89     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut8a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut8b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut8c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut8d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut8e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut8f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_18;

/* Define the union U_MOTION_EDGE_LUT_19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut90     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut91     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut92     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut93     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut94     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut95     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut96     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut97     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_19;

/* Define the union U_MOTION_EDGE_LUT_20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lut98     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lut99     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lut9a     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lut9b     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lut9c     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lut9d     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lut9e     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lut9f     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_20;

/* Define the union U_MOTION_EDGE_LUT_21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_luta0     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_luta1     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_luta2     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_luta3     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_luta4     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_luta5     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_luta6     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_luta7     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_21;

/* Define the union U_MOTION_EDGE_LUT_22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_luta8     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_luta9     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutaa     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lutab     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutac     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lutad     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutae     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutaf     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_22;

/* Define the union U_MOTION_EDGE_LUT_23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lutb0     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lutb1     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutb2     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lutb3     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutb4     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lutb5     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutb6     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutb7     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_23;

/* Define the union U_MOTION_EDGE_LUT_24 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lutb8     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lutb9     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutba     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lutbb     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutbc     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lutbd     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutbe     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutbf     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_24;

/* Define the union U_MOTION_EDGE_LUT_25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lutc0     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lutc1     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutc2     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lutc3     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutc4     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lutc5     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutc6     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutc7     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_25;

/* Define the union U_MOTION_EDGE_LUT_26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lutc8     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lutc9     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutca     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lutcb     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutcc     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lutcd     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutce     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutcf     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_26;

/* Define the union U_MOTION_EDGE_LUT_27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lutd0     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lutd1     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutd2     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lutd3     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutd4     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lutd5     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutd6     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutd7     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_27;

/* Define the union U_MOTION_EDGE_LUT_28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lutd8     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lutd9     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutda     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lutdb     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutdc     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lutdd     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutde     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutdf     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_28;

/* Define the union U_MOTION_EDGE_LUT_29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lute0     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lute1     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lute2     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lute3     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lute4     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lute5     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lute6     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lute7     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_29;

/* Define the union U_MOTION_EDGE_LUT_30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lute8     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lute9     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutea     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_luteb     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutec     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_luted     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutee     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutef     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_30;

/* Define the union U_MOTION_EDGE_LUT_31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lutf0     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lutf1     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutf2     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lutf3     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutf4     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lutf5     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutf6     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutf7     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_31;

/* Define the union U_MOTION_EDGE_LUT_32 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motion_edge_lutf8     : 4   ; /* [3..0]  */
        unsigned int    motion_edge_lutf9     : 4   ; /* [7..4]  */
        unsigned int    motion_edge_lutfa     : 4   ; /* [11..8]  */
        unsigned int    motion_edge_lutfb     : 4   ; /* [15..12]  */
        unsigned int    motion_edge_lutfc     : 4   ; /* [19..16]  */
        unsigned int    motion_edge_lutfd     : 4   ; /* [23..20]  */
        unsigned int    motion_edge_lutfe     : 4   ; /* [27..24]  */
        unsigned int    motion_edge_lutff     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MOTION_EDGE_LUT_32;

/* Define the union U_VPSS_LCHDR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_en              : 1   ; /* [0]  */
        unsigned int    lchdr_tmen            : 1   ; /* [1]  */
        unsigned int    lchdr_dithen          : 1   ; /* [2]  */
        unsigned int    lchdr_satmapyen       : 1   ; /* [3]  */
        unsigned int    lchdr_cscen           : 1   ; /* [4]  */
        unsigned int    lchdr_fullorlimt      : 1   ; /* [5]  */
        unsigned int    lchdr_ck_gt_en        : 1   ; /* [6]  */
        unsigned int    reserved_0            : 5   ; /* [11..7]  */
        unsigned int    lchdr_demo_en         : 1   ; /* [12]  */
        unsigned int    lchdr_demo_mode       : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    lchdr_demo_pos        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_CTRL;

/* Define the union U_VPSS_LCHDR_CSC_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_csc_coef12      : 16  ; /* [15..0]  */
        unsigned int    lchdr_csc_coef11      : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_CSC_COEF0;

/* Define the union U_VPSS_LCHDR_CSC_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_csc_coef22      : 16  ; /* [15..0]  */
        unsigned int    lchdr_csc_coef21      : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_CSC_COEF1;

/* Define the union U_VPSS_LCHDR_SCALE2P */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_satsclcoef      : 4   ; /* [3..0]  */
        unsigned int    lchdr_csc_scale       : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SCALE2P;

/* Define the union U_VPSS_LCHDR_TMAP_STEP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gmm_x4_step           : 4   ; /* [3..0]  */
        unsigned int    gmm_x3_step           : 4   ; /* [7..4]  */
        unsigned int    gmm_x2_step           : 4   ; /* [11..8]  */
        unsigned int    gmm_x1_step           : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_STEP;

/* Define the union U_VPSS_LCHDR_TMAP_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gmm_x4_num            : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    gmm_x3_num            : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    gmm_x2_num            : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    gmm_x1_num            : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_NUM;

/* Define the union U_VPSS_LCHDR_TMAP_POS0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gmm_x2_pos            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    gmm_x1_pos            : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_POS0;

/* Define the union U_VPSS_LCHDR_TMAP_POS1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gmm_x4_pos            : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    gmm_x3_pos            : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_POS1;

/* Define the union U_VPSS_LCHDR_DITHER_FUNC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_dither_round    : 1   ; /* [0]  */
        unsigned int    lchdr_dither_domain_mode : 1   ; /* [1]  */
        unsigned int    lchdr_dither_tap_mode : 2   ; /* [3..2]  */
        unsigned int    lchdr_dither_round_unlim : 1   ; /* [4]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_DITHER_FUNC;

/* Define the union U_VPSS_LCHDR_DITHER_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_dither_thr_max  : 16  ; /* [15..0]  */
        unsigned int    lchdr_dither_thr_min  : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_DITHER_THR;

/* Define the union U_VPSS_LCHDR_DITHER_SEED */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_dither_sed_y0   : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_DITHER_SEED;

/* Define the union U_VPSS_LCHDR_TMAP_LUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut1           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut0           : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT0;

/* Define the union U_VPSS_LCHDR_TMAP_LUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut3           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut2           : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT1;

/* Define the union U_VPSS_LCHDR_TMAP_LUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut5           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut4           : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT2;

/* Define the union U_VPSS_LCHDR_TMAP_LUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut7           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut6           : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT3;

/* Define the union U_VPSS_LCHDR_TMAP_LUT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut9           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut8           : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT4;

/* Define the union U_VPSS_LCHDR_TMAP_LUT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut11          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut10          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT5;

/* Define the union U_VPSS_LCHDR_TMAP_LUT6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut13          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut12          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT6;

/* Define the union U_VPSS_LCHDR_TMAP_LUT7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut15          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut14          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT7;

/* Define the union U_VPSS_LCHDR_TMAP_LUT8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut17          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut16          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT8;

/* Define the union U_VPSS_LCHDR_TMAP_LUT9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut19          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut18          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT9;

/* Define the union U_VPSS_LCHDR_TMAP_LUT10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut21          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut20          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT10;

/* Define the union U_VPSS_LCHDR_TMAP_LUT11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut23          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut22          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT11;

/* Define the union U_VPSS_LCHDR_TMAP_LUT12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut25          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut24          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT12;

/* Define the union U_VPSS_LCHDR_TMAP_LUT13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut27          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut26          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT13;

/* Define the union U_VPSS_LCHDR_TMAP_LUT14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut29          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut28          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT14;

/* Define the union U_VPSS_LCHDR_TMAP_LUT15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut31          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut30          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT15;

/* Define the union U_VPSS_LCHDR_TMAP_LUT16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut33          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut32          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT16;

/* Define the union U_VPSS_LCHDR_TMAP_LUT17 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut35          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut34          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT17;

/* Define the union U_VPSS_LCHDR_TMAP_LUT18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut37          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut36          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT18;

/* Define the union U_VPSS_LCHDR_TMAP_LUT19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut39          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut38          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT19;

/* Define the union U_VPSS_LCHDR_TMAP_LUT20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut41          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut40          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT20;

/* Define the union U_VPSS_LCHDR_TMAP_LUT21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut43          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut42          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT21;

/* Define the union U_VPSS_LCHDR_TMAP_LUT22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut45          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut44          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT22;

/* Define the union U_VPSS_LCHDR_TMAP_LUT23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut47          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut46          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT23;

/* Define the union U_VPSS_LCHDR_TMAP_LUT24 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut49          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut48          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT24;

/* Define the union U_VPSS_LCHDR_TMAP_LUT25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut51          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut50          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT25;

/* Define the union U_VPSS_LCHDR_TMAP_LUT26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut53          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut52          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT26;

/* Define the union U_VPSS_LCHDR_TMAP_LUT27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut55          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut54          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT27;

/* Define the union U_VPSS_LCHDR_TMAP_LUT28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut57          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut56          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT28;

/* Define the union U_VPSS_LCHDR_TMAP_LUT29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut59          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut58          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT29;

/* Define the union U_VPSS_LCHDR_TMAP_LUT30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut61          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut60          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT30;

/* Define the union U_VPSS_LCHDR_TMAP_LUT31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_ylut63          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    lchdr_ylut62          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_TMAP_LUT31;

/* Define the union U_VPSS_LCHDR_SMAP_LUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut1           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut0           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT0;

/* Define the union U_VPSS_LCHDR_SMAP_LUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut3           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut2           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT1;

/* Define the union U_VPSS_LCHDR_SMAP_LUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut5           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut4           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT2;

/* Define the union U_VPSS_LCHDR_SMAP_LUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut7           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut6           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT3;

/* Define the union U_VPSS_LCHDR_SMAP_LUT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut9           : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut8           : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT4;

/* Define the union U_VPSS_LCHDR_SMAP_LUT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut11          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut10          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT5;

/* Define the union U_VPSS_LCHDR_SMAP_LUT6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut13          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut12          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT6;

/* Define the union U_VPSS_LCHDR_SMAP_LUT7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut15          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut14          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT7;

/* Define the union U_VPSS_LCHDR_SMAP_LUT8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut17          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut16          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT8;

/* Define the union U_VPSS_LCHDR_SMAP_LUT9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut19          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut18          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT9;

/* Define the union U_VPSS_LCHDR_SMAP_LUT10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut21          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut20          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT10;

/* Define the union U_VPSS_LCHDR_SMAP_LUT11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut23          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut22          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT11;

/* Define the union U_VPSS_LCHDR_SMAP_LUT12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut25          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut24          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT12;

/* Define the union U_VPSS_LCHDR_SMAP_LUT13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut27          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut26          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT13;

/* Define the union U_VPSS_LCHDR_SMAP_LUT14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut29          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut28          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT14;

/* Define the union U_VPSS_LCHDR_SMAP_LUT15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut31          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut30          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT15;

/* Define the union U_VPSS_LCHDR_SMAP_LUT16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut33          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut32          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT16;

/* Define the union U_VPSS_LCHDR_SMAP_LUT17 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut35          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut34          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT17;

/* Define the union U_VPSS_LCHDR_SMAP_LUT18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut37          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut36          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT18;

/* Define the union U_VPSS_LCHDR_SMAP_LUT19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut39          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut38          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT19;

/* Define the union U_VPSS_LCHDR_SMAP_LUT20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut41          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut40          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT20;

/* Define the union U_VPSS_LCHDR_SMAP_LUT21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut43          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut42          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT21;

/* Define the union U_VPSS_LCHDR_SMAP_LUT22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut45          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut44          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT22;

/* Define the union U_VPSS_LCHDR_SMAP_LUT23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut47          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut46          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT23;

/* Define the union U_VPSS_LCHDR_SMAP_LUT24 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut49          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut48          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT24;

/* Define the union U_VPSS_LCHDR_SMAP_LUT25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut51          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut50          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT25;

/* Define the union U_VPSS_LCHDR_SMAP_LUT26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut53          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut52          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT26;

/* Define the union U_VPSS_LCHDR_SMAP_LUT27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut55          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut54          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT27;

/* Define the union U_VPSS_LCHDR_SMAP_LUT28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut57          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut56          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT28;

/* Define the union U_VPSS_LCHDR_SMAP_LUT29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut59          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut58          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT29;

/* Define the union U_VPSS_LCHDR_SMAP_LUT30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut61          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut60          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT30;

/* Define the union U_VPSS_LCHDR_SMAP_LUT31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut63          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    lchdr_slut62          : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT31;

/* Define the union U_VPSS_LCHDR_SMAP_LUT32 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lchdr_slut64          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_LCHDR_SMAP_LUT32;

/* Define the union U_VPSS_TNR_CONTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nren                  : 1   ; /* [0]  */
        unsigned int    ynren                 : 1   ; /* [1]  */
        unsigned int    cnren                 : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    reserved_1            : 1   ; /* [4]  */
        unsigned int    marketmodeen          : 1   ; /* [5]  */
        unsigned int    marketmode            : 1   ; /* [6]  */
        unsigned int    marketcoor            : 13  ; /* [19..7]  */
        unsigned int    reserved_2            : 2   ; /* [21..20]  */
        unsigned int    reserved_3            : 2   ; /* [23..22]  */
        unsigned int    reserved_4            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CONTRL;

/* Define the union U_VPSS_TNR_MAMD_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mdprelpfen            : 1   ; /* [0]  */
        unsigned int    mean_ymotion_adj_en   : 1   ; /* [1]  */
        unsigned int    mean_cmotion_adj_en   : 1   ; /* [2]  */
        unsigned int    meanyadjshift         : 3   ; /* [5..3]  */
        unsigned int    meancadjshift         : 3   ; /* [8..6]  */
        unsigned int    ymotioncalcmode       : 2   ; /* [10..9]  */
        unsigned int    cmotioncalcmode       : 2   ; /* [12..11]  */
        unsigned int    ymotionlpfmode        : 2   ; /* [14..13]  */
        unsigned int    cmotionlpfmode        : 2   ; /* [16..15]  */
        unsigned int    alpha1                : 3   ; /* [19..17]  */
        unsigned int    alpha2                : 3   ; /* [22..20]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAMD_CTRL;

/* Define the union U_VPSS_TNR_MAMD_GAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ymdgain               : 6   ; /* [5..0]  */
        unsigned int    ymdcore               : 6   ; /* [11..6]  */
        unsigned int    cmdgain               : 6   ; /* [17..12]  */
        unsigned int    cmdcore               : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAMD_GAIN;

/* Define the union U_VPSS_TNR_MAND_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    noisedetecten         : 1   ; /* [0]  */
        unsigned int    blkdiffthd            : 8   ; /* [8..1]  */
        unsigned int    randomctrlmode        : 2   ; /* [10..9]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAND_CTRL;

/* Define the union U_VPSS_TNR_MAND_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    flatthdmin            : 8   ; /* [7..0]  */
        unsigned int    flatthdmed            : 8   ; /* [15..8]  */
        unsigned int    flatthdmax            : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAND_THD;

/* Define the union U_VPSS_TNR_MAME_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motionestimateen      : 1   ; /* [0]  */
        unsigned int    mvrefmode             : 2   ; /* [2..1]  */
        unsigned int    mvlpfmode             : 2   ; /* [4..3]  */
        unsigned int    gm_adj                : 3   ; /* [7..5]  */
        unsigned int    discardsmvxen         : 1   ; /* [8]  */
        unsigned int    discardsmvyen         : 1   ; /* [9]  */
        unsigned int    smvxthd               : 3   ; /* [12..10]  */
        unsigned int    smvythd               : 3   ; /* [15..13]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAME_CTRL;

/* Define the union U_VPSS_TNR_MAME_GAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mag_pnl_gain_0mv      : 8   ; /* [7..0]  */
        unsigned int    mag_pnl_core_0mv      : 8   ; /* [15..8]  */
        unsigned int    mag_pnl_gain_xmv      : 8   ; /* [23..16]  */
        unsigned int    mag_pnl_core_xmv      : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAME_GAIN;

/* Define the union U_VPSS_TNR_MAME_STD_CORE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    std_core_0mv          : 5   ; /* [4..0]  */
        unsigned int    std_core_xmv          : 5   ; /* [9..5]  */
        unsigned int    std_pnl_gain_0mv      : 5   ; /* [14..10]  */
        unsigned int    std_pnl_core_0mv      : 5   ; /* [19..15]  */
        unsigned int    std_pnl_gain_xmv      : 5   ; /* [24..20]  */
        unsigned int    std_pnl_core_xmv      : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAME_STD_CORE;

/* Define the union U_VPSS_TNR_MAME_STD_GAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    std_pnl_gain          : 5   ; /* [4..0]  */
        unsigned int    std_pnl_core          : 5   ; /* [9..5]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAME_STD_GAIN;

/* Define the union U_VPSS_TNR_MAME_MV_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    adj_mv_max            : 5   ; /* [4..0]  */
        unsigned int    adj_mv_min            : 5   ; /* [9..5]  */
        unsigned int    adj_0mv_min           : 5   ; /* [14..10]  */
        unsigned int    adj_xmv_min           : 5   ; /* [19..15]  */
        unsigned int    adj_0mv_max           : 5   ; /* [24..20]  */
        unsigned int    adj_xmv_max           : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAME_MV_THD;

/* Define the union U_VPSS_TNR_MAMC_CBCR_UPEN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbcrupdateen          : 1   ; /* [0]  */
        unsigned int    cbcrweight1           : 4   ; /* [4..1]  */
        unsigned int    cbcrweight2           : 4   ; /* [8..5]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAMC_CBCR_UPEN;

/* Define the union U_VPSS_TNR_MAMC_CBCR_UPTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbbegin1              : 6   ; /* [5..0]  */
        unsigned int    crbegin1              : 6   ; /* [11..6]  */
        unsigned int    cbend1                : 6   ; /* [17..12]  */
        unsigned int    crend1                : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAMC_CBCR_UPTHD1;

/* Define the union U_VPSS_TNR_MAMC_CBCR_UPTHD2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbbegin2              : 6   ; /* [5..0]  */
        unsigned int    crbegin2              : 6   ; /* [11..6]  */
        unsigned int    cbend2                : 6   ; /* [17..12]  */
        unsigned int    crend2                : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAMC_CBCR_UPTHD2;

/* Define the union U_VPSS_TNR_MAMC_PRE_MAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    premotionmergemode    : 1   ; /* [0]  */
        unsigned int    premotionalpha        : 5   ; /* [5..1]  */
        unsigned int    motionmergeratio      : 5   ; /* [10..6]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAMC_PRE_MAD;

/* Define the union U_VPSS_TNR_MAMC_MAP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    motionmappingen       : 1   ; /* [0]  */
        unsigned int    ymotiongain           : 5   ; /* [5..1]  */
        unsigned int    ymotioncore           : 6   ; /* [11..6]  */
        unsigned int    cmotiongain           : 5   ; /* [16..12]  */
        unsigned int    cmotioncore           : 6   ; /* [22..17]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAMC_MAP;

/* Define the union U_VPSS_TNR_MAMC_SALTUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    saltusdecten          : 1   ; /* [0]  */
        unsigned int    saltuslevel           : 5   ; /* [5..1]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAMC_SALTUS;

/* Define the union U_VPSS_TNR_MAMC_MCADJ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ymcadjen              : 1   ; /* [0]  */
        unsigned int    cmcadjen              : 1   ; /* [1]  */
        unsigned int    ymclpfmode            : 2   ; /* [3..2]  */
        unsigned int    cmclpfmode            : 2   ; /* [5..4]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MAMC_MCADJ;

/* Define the union U_VPSS_TNR_FILR_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ymotionmode           : 1   ; /* [0]  */
        unsigned int    cmotionmode           : 1   ; /* [1]  */
        unsigned int    ynonrrange            : 5   ; /* [6..2]  */
        unsigned int    cnonrrange            : 5   ; /* [11..7]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_FILR_MODE;

/* Define the union U_VPSS_TNR_SCENE_CHANGE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    scenechangeen         : 1   ; /* [0]  */
        unsigned int    scenechangeinfo       : 8   ; /* [8..1]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_SCENE_CHANGE;

/* Define the union U_VPSS_TNR_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfg_ymdgain           : 6   ; /* [5..0]  */
        unsigned int    cfg_ymdcore           : 5   ; /* [10..6]  */
        unsigned int    cfg_cmdgain           : 6   ; /* [16..11]  */
        unsigned int    cfg_cmdcore           : 5   ; /* [21..17]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CFG;

/* Define the union U_VPSS_TNR_FLAT_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    flatinfoxmin          : 8   ; /* [7..0]  */
        unsigned int    flatinfoymin          : 8   ; /* [15..8]  */
        unsigned int    flatinfoxmax          : 8   ; /* [23..16]  */
        unsigned int    flatinfoymax          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_FLAT_INFO;

/* Define the union U_VPSS_TNR_YBLEND */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yblendingxmin         : 5   ; /* [4..0]  */
        unsigned int    yblendingymin         : 5   ; /* [9..5]  */
        unsigned int    yblendingxmax         : 5   ; /* [14..10]  */
        unsigned int    yblendingymax         : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_YBLEND;

/* Define the union U_VPSS_TNR_CBLEND */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cblendingxmin         : 5   ; /* [4..0]  */
        unsigned int    cblendingymin         : 5   ; /* [9..5]  */
        unsigned int    cblendingxmax         : 5   ; /* [14..10]  */
        unsigned int    cblendingymax         : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CBLEND;

/* Define the union U_VPSS_TNR_DTBLEND */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dtblendingxmin        : 5   ; /* [4..0]  */
        unsigned int    dtblendingymin        : 5   ; /* [9..5]  */
        unsigned int    dtblendingxmax        : 5   ; /* [14..10]  */
        unsigned int    dtblendingymax        : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_DTBLEND;

/* Define the union U_VPSS_TNR_MEAN_MOTION_LUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mean_motion_ratio0    : 6   ; /* [5..0]  */
        unsigned int    mean_motion_ratio1    : 6   ; /* [11..6]  */
        unsigned int    mean_motion_ratio2    : 6   ; /* [17..12]  */
        unsigned int    mean_motion_ratio3    : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MEAN_MOTION_LUT0;

/* Define the union U_VPSS_TNR_MEAN_MOTION_LUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mean_motion_ratio4    : 6   ; /* [5..0]  */
        unsigned int    mean_motion_ratio5    : 6   ; /* [11..6]  */
        unsigned int    mean_motion_ratio6    : 6   ; /* [17..12]  */
        unsigned int    mean_motion_ratio7    : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MEAN_MOTION_LUT1;

/* Define the union U_VPSS_TNR_MEAN_MOTION_LUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mean_motion_ratio8    : 6   ; /* [5..0]  */
        unsigned int    mean_motion_ratio9    : 6   ; /* [11..6]  */
        unsigned int    mean_motion_ratio10   : 6   ; /* [17..12]  */
        unsigned int    mean_motion_ratio11   : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MEAN_MOTION_LUT2;

/* Define the union U_VPSS_TNR_MEAN_MOTION_LUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mean_motion_ratio12   : 6   ; /* [5..0]  */
        unsigned int    mean_motion_ratio13   : 6   ; /* [11..6]  */
        unsigned int    mean_motion_ratio14   : 6   ; /* [17..12]  */
        unsigned int    mean_motion_ratio15   : 6   ; /* [23..18]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_MEAN_MOTION_LUT3;

/* Define the union U_VPSS_TNR_YBLENDING_LUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yblendingalphalut0    : 5   ; /* [4..0]  */
        unsigned int    yblendingalphalut1    : 5   ; /* [9..5]  */
        unsigned int    yblendingalphalut2    : 5   ; /* [14..10]  */
        unsigned int    yblendingalphalut3    : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_YBLENDING_LUT0;

/* Define the union U_VPSS_TNR_YBLENDING_LUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yblendingalphalut4    : 5   ; /* [4..0]  */
        unsigned int    yblendingalphalut5    : 5   ; /* [9..5]  */
        unsigned int    yblendingalphalut6    : 5   ; /* [14..10]  */
        unsigned int    yblendingalphalut7    : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_YBLENDING_LUT1;

/* Define the union U_VPSS_TNR_YBLENDING_LUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yblendingalphalut8    : 5   ; /* [4..0]  */
        unsigned int    yblendingalphalut9    : 5   ; /* [9..5]  */
        unsigned int    yblendingalphalut10   : 5   ; /* [14..10]  */
        unsigned int    yblendingalphalut11   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_YBLENDING_LUT2;

/* Define the union U_VPSS_TNR_YBLENDING_LUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yblendingalphalut12   : 5   ; /* [4..0]  */
        unsigned int    yblendingalphalut13   : 5   ; /* [9..5]  */
        unsigned int    yblendingalphalut14   : 5   ; /* [14..10]  */
        unsigned int    yblendingalphalut15   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_YBLENDING_LUT3;

/* Define the union U_VPSS_TNR_YBLENDING_LUT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yblendingalphalut16   : 5   ; /* [4..0]  */
        unsigned int    yblendingalphalut17   : 5   ; /* [9..5]  */
        unsigned int    yblendingalphalut18   : 5   ; /* [14..10]  */
        unsigned int    yblendingalphalut19   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_YBLENDING_LUT4;

/* Define the union U_VPSS_TNR_YBLENDING_LUT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yblendingalphalut20   : 5   ; /* [4..0]  */
        unsigned int    yblendingalphalut21   : 5   ; /* [9..5]  */
        unsigned int    yblendingalphalut22   : 5   ; /* [14..10]  */
        unsigned int    yblendingalphalut23   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_YBLENDING_LUT5;

/* Define the union U_VPSS_TNR_YBLENDING_LUT6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yblendingalphalut24   : 5   ; /* [4..0]  */
        unsigned int    yblendingalphalut25   : 5   ; /* [9..5]  */
        unsigned int    yblendingalphalut26   : 5   ; /* [14..10]  */
        unsigned int    yblendingalphalut27   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_YBLENDING_LUT6;

/* Define the union U_VPSS_TNR_YBLENDING_LUT7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    yblendingalphalut28   : 5   ; /* [4..0]  */
        unsigned int    yblendingalphalut29   : 5   ; /* [9..5]  */
        unsigned int    yblendingalphalut30   : 5   ; /* [14..10]  */
        unsigned int    yblendingalphalut31   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_YBLENDING_LUT7;

/* Define the union U_VPSS_TNR_CBLENDING_LUT0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cblendingalphalut0    : 5   ; /* [4..0]  */
        unsigned int    cblendingalphalut1    : 5   ; /* [9..5]  */
        unsigned int    cblendingalphalut2    : 5   ; /* [14..10]  */
        unsigned int    cblendingalphalut3    : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CBLENDING_LUT0;

/* Define the union U_VPSS_TNR_CBLENDING_LUT1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cblendingalphalut4    : 5   ; /* [4..0]  */
        unsigned int    cblendingalphalut5    : 5   ; /* [9..5]  */
        unsigned int    cblendingalphalut6    : 5   ; /* [14..10]  */
        unsigned int    cblendingalphalut7    : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CBLENDING_LUT1;

/* Define the union U_VPSS_TNR_CBLENDING_LUT2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cblendingalphalut8    : 5   ; /* [4..0]  */
        unsigned int    cblendingalphalut9    : 5   ; /* [9..5]  */
        unsigned int    cblendingalphalut10   : 5   ; /* [14..10]  */
        unsigned int    cblendingalphalut11   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CBLENDING_LUT2;

/* Define the union U_VPSS_TNR_CBLENDING_LUT3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cblendingalphalut12   : 5   ; /* [4..0]  */
        unsigned int    cblendingalphalut13   : 5   ; /* [9..5]  */
        unsigned int    cblendingalphalut14   : 5   ; /* [14..10]  */
        unsigned int    cblendingalphalut15   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CBLENDING_LUT3;

/* Define the union U_VPSS_TNR_CBLENDING_LUT4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cblendingalphalut16   : 5   ; /* [4..0]  */
        unsigned int    cblendingalphalut17   : 5   ; /* [9..5]  */
        unsigned int    cblendingalphalut18   : 5   ; /* [14..10]  */
        unsigned int    cblendingalphalut19   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CBLENDING_LUT4;

/* Define the union U_VPSS_TNR_CBLENDING_LUT5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cblendingalphalut20   : 5   ; /* [4..0]  */
        unsigned int    cblendingalphalut21   : 5   ; /* [9..5]  */
        unsigned int    cblendingalphalut22   : 5   ; /* [14..10]  */
        unsigned int    cblendingalphalut23   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CBLENDING_LUT5;

/* Define the union U_VPSS_TNR_CBLENDING_LUT6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cblendingalphalut24   : 5   ; /* [4..0]  */
        unsigned int    cblendingalphalut25   : 5   ; /* [9..5]  */
        unsigned int    cblendingalphalut26   : 5   ; /* [14..10]  */
        unsigned int    cblendingalphalut27   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CBLENDING_LUT6;

/* Define the union U_VPSS_TNR_CBLENDING_LUT7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cblendingalphalut28   : 5   ; /* [4..0]  */
        unsigned int    cblendingalphalut29   : 5   ; /* [9..5]  */
        unsigned int    cblendingalphalut30   : 5   ; /* [14..10]  */
        unsigned int    cblendingalphalut31   : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TNR_CBLENDING_LUT7;

/* Define the union U_VPSS_DEBUG0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug0                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG0;
/* Define the union U_VPSS_DEBUG1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug1                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG1;
/* Define the union U_VPSS_DEBUG2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug2                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG2;
/* Define the union U_VPSS_DEBUG3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug3                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG3;
/* Define the union U_VPSS_DEBUG4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug4                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG4;
/* Define the union U_VPSS_DEBUG5 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug5                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG5;
/* Define the union U_VPSS_DEBUG6 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug6                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG6;
/* Define the union U_VPSS_DEBUG7 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug7                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG7;
/* Define the union U_VPSS_DEBUG8 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug8                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG8;
/* Define the union U_VPSS_DEBUG9 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug9                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG9;
/* Define the union U_VPSS_DEBUG10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug10                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG10;
/* Define the union U_VPSS_DEBUG11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug11                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG11;
/* Define the union U_VPSS_DEBUG12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug12                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG12;
/* Define the union U_VPSS_DEBUG13 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug13                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG13;
/* Define the union U_VPSS_DEBUG14 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug14                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG14;
/* Define the union U_VPSS_DEBUG15 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug15                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG15;
/* Define the union U_VPSS_DEBUG16 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug16                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG16;
/* Define the union U_VPSS_DEBUG17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug17                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG17;
/* Define the union U_VPSS_DEBUG18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug18                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG18;
/* Define the union U_VPSS_DEBUG19 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug19                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG19;
/* Define the union U_VPSS_DEBUG20 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug20                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG20;
/* Define the union U_VPSS_DEBUG21 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug21                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG21;
/* Define the union U_VPSS_DEBUG22 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug22                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG22;
/* Define the union U_VPSS_DEBUG23 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug23                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG23;
/* Define the union U_VPSS_DEBUG24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug24                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG24;
/* Define the union U_VPSS_DEBUG25 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug25                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG25;
/* Define the union U_VPSS_DEBUG26 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug26                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG26;
/* Define the union U_VPSS_DEBUG27 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug27                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG27;
/* Define the union U_VPSS_DEBUG28 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug28                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG28;
/* Define the union U_VPSS_DEBUG29 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug29                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG29;
/* Define the union U_VPSS_DEBUG30 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug30                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG30;
/* Define the union U_VPSS_DEBUG31 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug31                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG31;
/* Define the union U_VPSS_DEBUG32 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug32                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG32;
/* Define the union U_VPSS_DEBUG33 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug33                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG33;
/* Define the union U_VPSS_DEBUG34 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug34                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG34;
/* Define the union U_VPSS_DEBUG35 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug35                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG35;
/* Define the union U_VPSS_DEBUG36 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug36                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG36;
/* Define the union U_VPSS_DEBUG37 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug37                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG37;
/* Define the union U_VPSS_DEBUG38 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug38                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG38;
/* Define the union U_VPSS_DEBUG39 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug39                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG39;
/* Define the union U_VPSS_DEBUG40 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug40                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG40;
/* Define the union U_VPSS_DEBUG41 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug41                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG41;
/* Define the union U_VPSS_DEBUG42 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug42                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG42;
/* Define the union U_VPSS_DEBUG43 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug43                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DEBUG43;
/* Define the union U_VPSS_CHN_CFG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    prot                  : 2   ; /* [1..0]  */
        unsigned int    img_pro_mode          : 2   ; /* [3..2]  */
        unsigned int    rotate_en             : 1   ; /* [4]  */
        unsigned int    rotate_angle          : 1   ; /* [5]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    max_req_num           : 2   ; /* [9..8]  */
        unsigned int    max_req_len           : 2   ; /* [11..10]  */
        unsigned int    reserved_1            : 6   ; /* [17..12]  */
        unsigned int    dma_en                : 1   ; /* [18]  */
        unsigned int    reserved_2            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CHN_CFG_CTRL;

/* Define the union U_VPSS_STT_W_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int stt_w_addr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_STT_W_ADDR_LOW;
/* Define the union U_VPSS_CF_RTUNL_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cf_rtunl_en           : 1   ; /* [0]  */
        unsigned int    cf_rtunl_bypass       : 1   ; /* [1]  */
        unsigned int    reserved_0            : 6   ; /* [7..2]  */
        unsigned int    cf_rtunl_interval     : 8   ; /* [15..8]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CF_RTUNL_CTRL;

/* Define the union U_VPSS_CF_RTUNL_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cf_rtunl_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CF_RTUNL_ADDR_LOW;
/* Define the union U_VPSS_OUT0_WTUNL_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out0_wtunl_en         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 7   ; /* [7..1]  */
        unsigned int    out0_wtunl_mode       : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_OUT0_WTUNL_CTRL;

/* Define the union U_VPSS_OUT0_WTUNL_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out0_wtunl_finish_line : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_OUT0_WTUNL_THD;

/* Define the union U_VPSS_OUT0_WTUNL_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out0_wtunl_addr        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_OUT0_WTUNL_ADDR_LOW;
/* Define the union U_VPSS_TRANS_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    trans_size            : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 13  ; /* [28..16]  */
        unsigned int    trans_bypass          : 1   ; /* [29]  */
        unsigned int    trans_prot            : 1   ; /* [30]  */
        unsigned int    trans_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TRANS_INFO;

/* Define the union U_VPSS_TRANS_SRC_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int trans_src_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_TRANS_SRC_ADDR;
/* Define the union U_VPSS_TRANS_DES_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int trans_des_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_TRANS_DES_ADDR;
/* Define the union U_VPSS_TESTPATTERN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    test_pat_en           : 1   ; /* [0]  */
        unsigned int    pat_angle             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 6   ; /* [7..2]  */
        unsigned int    pat_dis_width         : 8   ; /* [15..8]  */
        unsigned int    pat_bkgrnd_u          : 8   ; /* [23..16]  */
        unsigned int    pat_bkgrnd_v          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_TESTPATTERN;

/* Define the union U_VPSS_DCMP_STATUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfy_dcmp_err          : 1   ; /* [0]  */
        unsigned int    cfy_dcmp_forgive      : 1   ; /* [1]  */
        unsigned int    cfy_dcmp_consume      : 1   ; /* [2]  */
        unsigned int    cfy_dcmp_bs_err       : 1   ; /* [3]  */
        unsigned int    cfc_dcmp_err          : 1   ; /* [4]  */
        unsigned int    cfc_dcmp_forgive      : 1   ; /* [5]  */
        unsigned int    cfc_dcmp_consume      : 1   ; /* [6]  */
        unsigned int    cfc_dcmp_bs_err       : 1   ; /* [7]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DCMP_STATUS;

/* Define the union U_VPSS_OUT0Y_CHKSUM */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out0y_chksum           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_OUT0Y_CHKSUM;
/* Define the union U_VPSS_OUT0C_CHKSUM */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out0c_chksum           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_OUT0C_CHKSUM;
/* Define the union U_VPSS_CF_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cf_format             : 4   ; /* [3..0]  */
        unsigned int    cf_type               : 4   ; /* [7..4]  */
        unsigned int    cf_order              : 4   ; /* [11..8]  */
        unsigned int    cf_bitw               : 4   ; /* [15..12]  */
        unsigned int    cf_dcmp_mode          : 3   ; /* [18..16]  */
        unsigned int    cf_mute_mode          : 1   ; /* [19]  */
        unsigned int    cf_uv_invert          : 1   ; /* [20]  */
        unsigned int    reserved_0            : 2   ; /* [22..21]  */
        unsigned int    cf_lm_rmode           : 3   ; /* [25..23]  */
        unsigned int    cf_2b_bypass          : 1   ; /* [26]  */
        unsigned int    cf_h_bypass           : 1   ; /* [27]  */
        unsigned int    cf_d_bypass           : 1   ; /* [28]  */
        unsigned int    cf_mute_en            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 1   ; /* [30]  */
        unsigned int    cf_en                 : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CF_CTRL;

/* Define the union U_VPSS_CF_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cf_width              : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    cf_height             : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CF_SIZE;

/* Define the union U_VPSS_CF_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cf_hor_offset         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    cf_ver_offset         : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CF_OFFSET;

/* Define the union U_VPSS_CFY_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfy_addr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFY_ADDR_LOW;
/* Define the union U_VPSS_CFC_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfc_addr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFC_ADDR_LOW;
/* Define the union U_VPSS_CFY_HEAD_TOP_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfy_top_head_addr      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFY_HEAD_TOP_ADDR_LOW;
/* Define the union U_VPSS_CFC_HEAD_TOP_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfc_top_head_addr      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFC_HEAD_TOP_ADDR_LOW;
/* Define the union U_VPSS_CF_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfy_stride            : 16  ; /* [15..0]  */
        unsigned int    cfc_stride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CF_STRIDE;

/* Define the union U_VPSS_CF_HEAD_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfy_head_stride       : 16  ; /* [15..0]  */
        unsigned int    cfc_head_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CF_HEAD_STRIDE;

/* Define the union U_VPSS_CFY_2B_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfy_2b_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFY_2B_ADDR_LOW;
/* Define the union U_VPSS_CFC_2B_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfc_2b_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFC_2B_ADDR_LOW;
/* Define the union U_VPSS_CF_2B_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfy_2b_stride         : 16  ; /* [15..0]  */
        unsigned int    cfc_2b_stride         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CF_2B_STRIDE;

/* Define the union U_VPSS_CF_MUTE_VAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfy_mute_val          : 10  ; /* [9..0]  */
        unsigned int    cfc_mute_val          : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CF_MUTE_VAL;

/* Define the union U_VPSS_P1_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p1_format             : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 8   ; /* [11..4]  */
        unsigned int    p1_bitw               : 4   ; /* [15..12]  */
        unsigned int    reserved_1            : 3   ; /* [18..16]  */
        unsigned int    p1_mute_mode          : 1   ; /* [19]  */
        unsigned int    reserved_2            : 8   ; /* [27..20]  */
        unsigned int    p1_d_bypass           : 1   ; /* [28]  */
        unsigned int    p1_mute_en            : 1   ; /* [29]  */
        unsigned int    reserved_3            : 1   ; /* [30]  */
        unsigned int    p1_en                 : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P1_CTRL;

/* Define the union U_VPSS_P1Y_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p1y_addr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P1Y_ADDR_LOW;
/* Define the union U_VPSS_P1C_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p1c_addr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P1C_ADDR_LOW;
/* Define the union U_VPSS_P1_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p1y_stride            : 16  ; /* [15..0]  */
        unsigned int    p1c_stride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P1_STRIDE;

/* Define the union U_VPSS_P1_MUTE_VAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p1y_mute_val          : 10  ; /* [9..0]  */
        unsigned int    p1c_mute_val          : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P1_MUTE_VAL;

/* Define the union U_VPSS_P2_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p2_format             : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 8   ; /* [11..4]  */
        unsigned int    p2_bitw               : 4   ; /* [15..12]  */
        unsigned int    reserved_1            : 3   ; /* [18..16]  */
        unsigned int    p2_mute_mode          : 1   ; /* [19]  */
        unsigned int    reserved_2            : 8   ; /* [27..20]  */
        unsigned int    p2_d_bypass           : 1   ; /* [28]  */
        unsigned int    p2_mute_en            : 1   ; /* [29]  */
        unsigned int    reserved_3            : 1   ; /* [30]  */
        unsigned int    p2_en                 : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2_CTRL;

/* Define the union U_VPSS_P2Y_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p2y_addr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P2Y_ADDR_LOW;
/* Define the union U_VPSS_P2C_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p2c_addr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P2C_ADDR_LOW;
/* Define the union U_VPSS_P2_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p2y_stride            : 16  ; /* [15..0]  */
        unsigned int    p2c_stride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2_STRIDE;

/* Define the union U_VPSS_P2_MUTE_VAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p2y_mute_val          : 10  ; /* [9..0]  */
        unsigned int    p2c_mute_val          : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2_MUTE_VAL;

/* Define the union U_VPSS_P3_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p3_format             : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 8   ; /* [11..4]  */
        unsigned int    p3_bitw               : 4   ; /* [15..12]  */
        unsigned int    reserved_1            : 3   ; /* [18..16]  */
        unsigned int    p3_mute_mode          : 1   ; /* [19]  */
        unsigned int    reserved_2            : 8   ; /* [27..20]  */
        unsigned int    p3_d_bypass           : 1   ; /* [28]  */
        unsigned int    p3_mute_en            : 1   ; /* [29]  */
        unsigned int    reserved_3            : 1   ; /* [30]  */
        unsigned int    p3_en                 : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3_CTRL;

/* Define the union U_VPSS_P3Y_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p3y_addr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P3Y_ADDR_LOW;
/* Define the union U_VPSS_P3C_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p3c_addr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P3C_ADDR_LOW;
/* Define the union U_VPSS_P3_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p3y_stride            : 16  ; /* [15..0]  */
        unsigned int    p3c_stride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3_STRIDE;

/* Define the union U_VPSS_P3_MUTE_VAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p3y_mute_val          : 10  ; /* [9..0]  */
        unsigned int    p3c_mute_val          : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3_MUTE_VAL;

/* Define the union U_VPSS_P3I_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p3i_format            : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 15  ; /* [18..4]  */
        unsigned int    p3i_mute_mode         : 1   ; /* [19]  */
        unsigned int    reserved_1            : 8   ; /* [27..20]  */
        unsigned int    p3i_d_bypass          : 1   ; /* [28]  */
        unsigned int    p3i_mute_en           : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    p3i_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3I_CTRL;

/* Define the union U_VPSS_P3IY_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p3iy_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P3IY_ADDR_LOW;
/* Define the union U_VPSS_P3IC_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p3ic_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P3IC_ADDR_LOW;
/* Define the union U_VPSS_P3I_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p3iy_stride           : 16  ; /* [15..0]  */
        unsigned int    p3ic_stride           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3I_STRIDE;

/* Define the union U_VPSS_P3I_MUTE_VAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p3iy_mute_val         : 10  ; /* [9..0]  */
        unsigned int    p3ic_mute_val         : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3I_MUTE_VAL;

/* Define the union U_VPSS_NR_RMAD_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    nr_rmad_mute_mode     : 1   ; /* [19]  */
        unsigned int    reserved_1            : 8   ; /* [27..20]  */
        unsigned int    nr_rmad_d_bypass      : 1   ; /* [28]  */
        unsigned int    nr_rmad_mute_en       : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    nr_rmad_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_RMAD_CTRL;

/* Define the union U_VPSS_NR_RMAD_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nr_rmad_width         : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    nr_rmad_height        : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_RMAD_SIZE;

/* Define the union U_VPSS_NR_RMAD_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nr_rmad_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_NR_RMAD_ADDR_LOW;
/* Define the union U_VPSS_NR_RMAD_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nr_rmad_stride        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_RMAD_STRIDE;

/* Define the union U_VPSS_NR_RMAD_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nr_rmad_mute_val0      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_NR_RMAD_MUTE_VAL0;
/* Define the union U_VPSS_DI_RST_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    di_rst_mute_mode      : 1   ; /* [19]  */
        unsigned int    reserved_1            : 8   ; /* [27..20]  */
        unsigned int    di_rst_d_bypass       : 1   ; /* [28]  */
        unsigned int    di_rst_mute_en        : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    di_rst_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RST_CTRL;

/* Define the union U_VPSS_DI_RST_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_rst_width          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    di_rst_height         : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RST_SIZE;

/* Define the union U_VPSS_DI_RST_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int di_rst_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DI_RST_ADDR_LOW;
/* Define the union U_VPSS_DI_RST_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_rst_stride         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RST_STRIDE;

/* Define the union U_VPSS_DI_RST_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int di_rst_mute_val0       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DI_RST_MUTE_VAL0;
/* Define the union U_VPSS_DI_RST_CNT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    di_rst_cnt_mute_mode  : 1   ; /* [19]  */
        unsigned int    reserved_1            : 8   ; /* [27..20]  */
        unsigned int    di_rst_cnt_d_bypass   : 1   ; /* [28]  */
        unsigned int    di_rst_cnt_mute_en    : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    di_rst_cnt_en         : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RST_CNT_CTRL;

/* Define the union U_VPSS_DI_RST_CNT_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_rst_cnt_width      : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    di_rst_cnt_height     : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RST_CNT_SIZE;

/* Define the union U_VPSS_DI_RST_CNT_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int di_rst_cnt_addr        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DI_RST_CNT_ADDR_LOW;
/* Define the union U_VPSS_DI_RST_CNT_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_rst_cnt_stride     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RST_CNT_STRIDE;

/* Define the union U_VPSS_DI_RST_CNT_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int di_rst_cnt_mute_val0   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DI_RST_CNT_MUTE_VAL0;
/* Define the union U_VPSS_P3MT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    p3mt_mute_mode        : 1   ; /* [19]  */
        unsigned int    reserved_1            : 8   ; /* [27..20]  */
        unsigned int    p3mt_d_bypass         : 1   ; /* [28]  */
        unsigned int    p3mt_mute_en          : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    p3mt_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3MT_CTRL;

/* Define the union U_VPSS_P3MT_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p3mt_width            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    p3mt_height           : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3MT_SIZE;

/* Define the union U_VPSS_P3MT_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p3mt_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P3MT_ADDR_LOW;
/* Define the union U_VPSS_P3MT_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p3mt_stride           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3MT_STRIDE;

/* Define the union U_VPSS_P3MT_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p3mt_mute_val0         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P3MT_MUTE_VAL0;
/* Define the union U_VPSS_P2MV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    p2mv_mute_mode        : 1   ; /* [19]  */
        unsigned int    reserved_1            : 8   ; /* [27..20]  */
        unsigned int    p2mv_d_bypass         : 1   ; /* [28]  */
        unsigned int    p2mv_mute_en          : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    p2mv_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2MV_CTRL;

/* Define the union U_VPSS_P2MV_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p2mv_width            : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    p2mv_height           : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2MV_SIZE;

/* Define the union U_VPSS_P2MV_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p2mv_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P2MV_ADDR_LOW;
/* Define the union U_VPSS_P2MV_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p2mv_stride           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2MV_STRIDE;

/* Define the union U_VPSS_P2MV_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p2mv_mute_val0         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P2MV_MUTE_VAL0;
/* Define the union U_VPSS_P3MV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    p3mv_mute_mode        : 1   ; /* [19]  */
        unsigned int    reserved_1            : 8   ; /* [27..20]  */
        unsigned int    p3mv_d_bypass         : 1   ; /* [28]  */
        unsigned int    p3mv_mute_en          : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    p3mv_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3MV_CTRL;

/* Define the union U_VPSS_P3MV_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p3mv_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P3MV_ADDR_LOW;
/* Define the union U_VPSS_P3MV_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p3mv_stride           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P3MV_STRIDE;

/* Define the union U_VPSS_P3MV_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p3mv_mute_val0         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P3MV_MUTE_VAL0;
/* Define the union U_VPSS_P1RGMV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    p1rgmv_mute_mode      : 1   ; /* [19]  */
        unsigned int    reserved_1            : 7   ; /* [26..20]  */
        unsigned int    p1rgmv_en1            : 1   ; /* [27]  */
        unsigned int    p1rgmv_d_bypass       : 1   ; /* [28]  */
        unsigned int    p1rgmv_mute_en        : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    p1rgmv_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P1RGMV_CTRL;

/* Define the union U_VPSS_P1RGMV_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p1rgmv_width          : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    p1rgmv_height         : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P1RGMV_SIZE;

/* Define the union U_VPSS_P1RGMV_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p1rgmv_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P1RGMV_ADDR_LOW;
/* Define the union U_VPSS_P1RGMV_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p1rgmv_stride         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P1RGMV_STRIDE;

/* Define the union U_VPSS_P1RGMV_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p1rgmv_mute_val0       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P1RGMV_MUTE_VAL0;
/* Define the union U_VPSS_P1RGMV_MUTE_VAL1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p1rgmv_mute_val1       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P1RGMV_MUTE_VAL1;
/* Define the union U_VPSS_P2RGMV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    p2rgmv_mute_mode      : 1   ; /* [19]  */
        unsigned int    reserved_1            : 7   ; /* [26..20]  */
        unsigned int    p2rgmv_en1            : 1   ; /* [27]  */
        unsigned int    p2rgmv_d_bypass       : 1   ; /* [28]  */
        unsigned int    p2rgmv_mute_en        : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    p2rgmv_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2RGMV_CTRL;

/* Define the union U_VPSS_P2RGMV_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p2rgmv_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P2RGMV_ADDR_LOW;
/* Define the union U_VPSS_P2RGMV_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p2rgmv_stride         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2RGMV_STRIDE;

/* Define the union U_VPSS_P2RGMV_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p2rgmv_mute_val0       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P2RGMV_MUTE_VAL0;
/* Define the union U_VPSS_P2RGMV_MUTE_VAL1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p2rgmv_mute_val1       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P2RGMV_MUTE_VAL1;
/* Define the union U_VPSS_RPRJH_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    rprjh_mute_mode       : 1   ; /* [19]  */
        unsigned int    reserved_1            : 8   ; /* [27..20]  */
        unsigned int    rprjh_d_bypass        : 1   ; /* [28]  */
        unsigned int    rprjh_mute_en         : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    rprjh_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_RPRJH_CTRL;

/* Define the union U_VPSS_RPRJH_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rprjh_width           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    rprjh_height          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_RPRJH_SIZE;

/* Define the union U_VPSS_RPRJH_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int rprjh_addr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_RPRJH_ADDR_LOW;
/* Define the union U_VPSS_RPRJH_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rprjh_stride          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_RPRJH_STRIDE;

/* Define the union U_VPSS_RPRJH_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int rprjh_mute_val0        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_RPRJH_MUTE_VAL0;
/* Define the union U_VPSS_RPRJV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    rprjv_mute_mode       : 1   ; /* [19]  */
        unsigned int    reserved_1            : 8   ; /* [27..20]  */
        unsigned int    rprjv_d_bypass        : 1   ; /* [28]  */
        unsigned int    rprjv_mute_en         : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    rprjv_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_RPRJV_CTRL;

/* Define the union U_VPSS_RPRJV_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rprjv_width           : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    rprjv_height          : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_RPRJV_SIZE;

/* Define the union U_VPSS_RPRJV_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int rprjv_addr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_RPRJV_ADDR_LOW;
/* Define the union U_VPSS_RPRJV_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rprjv_stride          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_RPRJV_STRIDE;

/* Define the union U_VPSS_RPRJV_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int rprjv_mute_val0        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_RPRJV_MUTE_VAL0;
/* Define the union U_VPSS_OUT0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    out0_bitw             : 4   ; /* [11..8]  */
        unsigned int    reserved_1            : 4   ; /* [15..12]  */
        unsigned int    out0_uv_invert        : 1   ; /* [16]  */
        unsigned int    out0_mirror           : 1   ; /* [17]  */
        unsigned int    out0_flip             : 1   ; /* [18]  */
        unsigned int    out0_dither_en        : 1   ; /* [19]  */
        unsigned int    out0_dither_mode      : 1   ; /* [20]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    out0_mute_mode        : 1   ; /* [24]  */
        unsigned int    out0_mute_en          : 1   ; /* [25]  */
        unsigned int    out0_cts_en           : 1   ; /* [26]  */
        unsigned int    out0_cts_bit_sel      : 1   ; /* [27]  */
        unsigned int    reserved_3            : 1   ; /* [28]  */
        unsigned int    out0_d_bypass         : 1   ; /* [29]  */
        unsigned int    reserved_4            : 1   ; /* [30]  */
        unsigned int    out0_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_OUT0_CTRL;

/* Define the union U_VPSS_OUT0_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out0_hor_offset       : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    out0_ver_offset       : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_OUT0_OFFSET;

/* Define the union U_VPSS_OUT0Y_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out0y_addr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_OUT0Y_ADDR_LOW;
/* Define the union U_VPSS_OUT0C_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out0c_addr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_OUT0C_ADDR_LOW;
/* Define the union U_VPSS_OUT0_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out0y_stride          : 16  ; /* [15..0]  */
        unsigned int    out0c_stride          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_OUT0_STRIDE;

/* Define the union U_VPSS_OUT0_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out0_width            : 16  ; /* [15..0]  */
        unsigned int    out0_height           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_OUT0_SIZE;

/* Define the union U_VPSS_OUT0_FINFO_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out0_finfo             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_OUT0_FINFO_LOW;
/* Define the union U_VPSS_OUT0_MUTE_VAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out0y_mute_val        : 10  ; /* [9..0]  */
        unsigned int    out0c_mute_val        : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_OUT0_MUTE_VAL;

/* Define the union U_VPSS_NR_RFR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 8   ; /* [7..0]  */
        unsigned int    nr_rfr_bitw           : 4   ; /* [11..8]  */
        unsigned int    reserved_1            : 7   ; /* [18..12]  */
        unsigned int    nr_rfr_dither_en      : 1   ; /* [19]  */
        unsigned int    nr_rfr_dither_mode    : 1   ; /* [20]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    nr_rfr_mute_mode      : 1   ; /* [24]  */
        unsigned int    nr_rfr_mute_en        : 1   ; /* [25]  */
        unsigned int    reserved_3            : 3   ; /* [28..26]  */
        unsigned int    nr_rfr_d_bypass       : 1   ; /* [29]  */
        unsigned int    reserved_4            : 1   ; /* [30]  */
        unsigned int    nr_rfr_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_RFR_CTRL;

/* Define the union U_VPSS_NR_RFRY_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nr_rfry_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_NR_RFRY_ADDR_LOW;
/* Define the union U_VPSS_NR_RFRC_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nr_rfrc_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_NR_RFRC_ADDR_LOW;
/* Define the union U_VPSS_NR_RFR_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nr_rfry_stride        : 16  ; /* [15..0]  */
        unsigned int    nr_rfrc_stride        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_RFR_STRIDE;

/* Define the union U_VPSS_NR_RFR_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nr_rfr_width          : 16  ; /* [15..0]  */
        unsigned int    nr_rfr_height         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_RFR_SIZE;

/* Define the union U_VPSS_NR_RFR_FINFO_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nr_rfr_finfo           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_NR_RFR_FINFO_LOW;
/* Define the union U_VPSS_NR_RFR_MUTE_VAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nr_rfry_mute_val      : 10  ; /* [9..0]  */
        unsigned int    nr_rfrc_mute_val      : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_RFR_MUTE_VAL;

/* Define the union U_VPSS_DI_RFR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    di_rfr_mute_mode      : 1   ; /* [24]  */
        unsigned int    di_rfr_mute_en        : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    di_rfr_d_bypass       : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    di_rfr_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RFR_CTRL;

/* Define the union U_VPSS_DI_RFRY_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int di_rfry_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DI_RFRY_ADDR_LOW;
/* Define the union U_VPSS_DI_RFRC_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int di_rfrc_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DI_RFRC_ADDR_LOW;
/* Define the union U_VPSS_DI_RFR_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_rfry_stride        : 16  ; /* [15..0]  */
        unsigned int    di_rfrc_stride        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RFR_STRIDE;

/* Define the union U_VPSS_DI_RFR_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_rfr_width          : 16  ; /* [15..0]  */
        unsigned int    di_rfr_height         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RFR_SIZE;

/* Define the union U_VPSS_DI_RFR_FINFO_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int di_rfr_finfo           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DI_RFR_FINFO_LOW;
/* Define the union U_VPSS_DI_RFR_MUTE_VAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_rfry_mute_val      : 10  ; /* [9..0]  */
        unsigned int    di_rfrc_mute_val      : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_RFR_MUTE_VAL;

/* Define the union U_VPSS_NR_WMAD_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    nr_wmad_mute_mode     : 1   ; /* [24]  */
        unsigned int    nr_wmad_mute_en       : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    nr_wmad_d_bypass      : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    nr_wmad_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_WMAD_CTRL;

/* Define the union U_VPSS_NR_WMAD_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int nr_wmad_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_NR_WMAD_ADDR_LOW;
/* Define the union U_VPSS_NR_WMAD_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nr_wmad_stride        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_WMAD_STRIDE;

/* Define the union U_VPSS_NR_WMAD_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nr_wmad_width         : 16  ; /* [15..0]  */
        unsigned int    nr_wmad_height        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_WMAD_SIZE;

/* Define the union U_VPSS_NR_WMAD_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nr_wmad_mute_val0     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_NR_WMAD_MUTE_VAL0;

/* Define the union U_VPSS_DI_WST_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    di_wst_mute_mode      : 1   ; /* [24]  */
        unsigned int    di_wst_mute_en        : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    di_wst_d_bypass       : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    di_wst_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_WST_CTRL;

/* Define the union U_VPSS_DI_WST_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int di_wst_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DI_WST_ADDR_LOW;
/* Define the union U_VPSS_DI_WST_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_wst_stride         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_WST_STRIDE;

/* Define the union U_VPSS_DI_WST_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_wst_width          : 16  ; /* [15..0]  */
        unsigned int    di_wst_height         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_WST_SIZE;

/* Define the union U_VPSS_DI_WST_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_wst_mute_val0      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_WST_MUTE_VAL0;

/* Define the union U_VPSS_DI_WST_CNT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    di_wst_cnt_mute_mode  : 1   ; /* [24]  */
        unsigned int    di_wst_cnt_mute_en    : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    di_wst_cnt_d_bypass   : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    di_wst_cnt_en         : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_WST_CNT_CTRL;

/* Define the union U_VPSS_DI_WST_CNT_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int di_wst_cnt_addr        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_DI_WST_CNT_ADDR_LOW;
/* Define the union U_VPSS_DI_WST_CNT_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_wst_cnt_stride     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_WST_CNT_STRIDE;

/* Define the union U_VPSS_DI_WST_CNT_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_wst_cnt_width      : 16  ; /* [15..0]  */
        unsigned int    di_wst_cnt_height     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_WST_CNT_SIZE;

/* Define the union U_VPSS_DI_WST_CNT_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    di_wst_cnt_mute_val0  : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_DI_WST_CNT_MUTE_VAL0;

/* Define the union U_VPSS_P2MT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    p2mt_mute_mode        : 1   ; /* [24]  */
        unsigned int    p2mt_mute_en          : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    p2mt_d_bypass         : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    p2mt_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2MT_CTRL;

/* Define the union U_VPSS_P2MT_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int p2mt_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_P2MT_ADDR_LOW;
/* Define the union U_VPSS_P2MT_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p2mt_stride           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2MT_STRIDE;

/* Define the union U_VPSS_P2MT_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p2mt_width            : 16  ; /* [15..0]  */
        unsigned int    p2mt_height           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2MT_SIZE;

/* Define the union U_VPSS_P2MT_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    p2mt_mute_val0        : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_P2MT_MUTE_VAL0;

/* Define the union U_VPSS_CFMV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    cfmv_mute_mode        : 1   ; /* [24]  */
        unsigned int    cfmv_mute_en          : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    cfmv_d_bypass         : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    cfmv_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CFMV_CTRL;

/* Define the union U_VPSS_CFMV_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfmv_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFMV_ADDR_LOW;
/* Define the union U_VPSS_CFMV_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfmv_stride           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CFMV_STRIDE;

/* Define the union U_VPSS_CFMV_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfmv_width            : 16  ; /* [15..0]  */
        unsigned int    cfmv_height           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CFMV_SIZE;

/* Define the union U_VPSS_CFMV_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfmv_mute_val0         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFMV_MUTE_VAL0;
/* Define the union U_VPSS_CFRGMV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    cfrgmv_mute_mode      : 1   ; /* [24]  */
        unsigned int    cfrgmv_mute_en        : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    cfrgmv_d_bypass       : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    cfrgmv_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CFRGMV_CTRL;

/* Define the union U_VPSS_CFRGMV_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfrgmv_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFRGMV_ADDR_LOW;
/* Define the union U_VPSS_CFRGMV_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfrgmv_stride         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CFRGMV_STRIDE;

/* Define the union U_VPSS_CFRGMV_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfrgmv_width          : 16  ; /* [15..0]  */
        unsigned int    cfrgmv_height         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_CFRGMV_SIZE;

/* Define the union U_VPSS_CFRGMV_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfrgmv_mute_val0       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFRGMV_MUTE_VAL0;
/* Define the union U_VPSS_CFRGMV_MUTE_VAL1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cfrgmv_mute_val1       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_CFRGMV_MUTE_VAL1;
/* Define the union U_VPSS_WPRJH_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    wprjh_mute_mode       : 1   ; /* [24]  */
        unsigned int    wprjh_mute_en         : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    wprjh_d_bypass        : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    wprjh_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_WPRJH_CTRL;

/* Define the union U_VPSS_WPRJH_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wprjh_addr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_WPRJH_ADDR_LOW;
/* Define the union U_VPSS_WPRJH_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wprjh_stride          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_WPRJH_STRIDE;

/* Define the union U_VPSS_WPRJH_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wprjh_width           : 16  ; /* [15..0]  */
        unsigned int    wprjh_height          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_WPRJH_SIZE;

/* Define the union U_VPSS_WPRJH_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wprjh_mute_val0       : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_WPRJH_MUTE_VAL0;

/* Define the union U_VPSS_WPRJV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    wprjv_mute_mode       : 1   ; /* [24]  */
        unsigned int    wprjv_mute_en         : 1   ; /* [25]  */
        unsigned int    reserved_1            : 3   ; /* [28..26]  */
        unsigned int    wprjv_d_bypass        : 1   ; /* [29]  */
        unsigned int    reserved_2            : 1   ; /* [30]  */
        unsigned int    wprjv_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_WPRJV_CTRL;

/* Define the union U_VPSS_WPRJV_ADDR_LOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wprjv_addr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS_WPRJV_ADDR_LOW;
/* Define the union U_VPSS_WPRJV_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wprjv_stride          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_WPRJV_STRIDE;

/* Define the union U_VPSS_WPRJV_SIZE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wprjv_width           : 16  ; /* [15..0]  */
        unsigned int    wprjv_height          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_WPRJV_SIZE;

/* Define the union U_VPSS_WPRJV_MUTE_VAL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wprjv_mute_val0       : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_WPRJV_MUTE_VAL0;

/* Define the union U_VPSS0_SMMU_SCR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    glb_bypass            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 2   ; /* [2..1]  */
        unsigned int    int_en                : 1   ; /* [3]  */
        unsigned int    reserved_1            : 12  ; /* [15..4]  */
        unsigned int    ptw_pf                : 4   ; /* [19..16]  */
        unsigned int    reserved_2            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_SCR;

/* Define the union U_VPSS0_SMMU_LP_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    auto_clk_gt_en        : 1   ; /* [0]  */
        unsigned int    reserved_0            : 1   ; /* [1]  */
        unsigned int    reserved_1            : 1   ; /* [2]  */
        unsigned int    reserved_2            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_LP_CTRL;

/* Define the union U_VPSS0_SMMU_MEM_SPEEDCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rfs_emaw              : 2   ; /* [1..0]  */
        unsigned int    rfs_ema               : 3   ; /* [4..2]  */
        unsigned int    rfs_ret1n             : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MEM_SPEEDCTRL;

/* Define the union U_VPSS0_SMMU_INTMASK_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ints_tlbmiss_msk      : 1   ; /* [0]  */
        unsigned int    ints_ptw_trans_msk    : 1   ; /* [1]  */
        unsigned int    ints_tlbinvalid_rd_msk : 1   ; /* [2]  */
        unsigned int    ints_tlbinvalid_wr_msk : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_INTMASK_S;

/* Define the union U_VPSS0_SMMU_INTRAW_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ints_tlbmiss_raw      : 1   ; /* [0]  */
        unsigned int    ints_ptw_trans_raw    : 1   ; /* [1]  */
        unsigned int    ints_tlbinvalid_rd_raw : 1   ; /* [2]  */
        unsigned int    ints_tlbinvalid_wr_raw : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_INTRAW_S;

/* Define the union U_VPSS0_SMMU_INTSTAT_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ints_tlbmiss_stat     : 1   ; /* [0]  */
        unsigned int    ints_ptw_trans_stat   : 1   ; /* [1]  */
        unsigned int    ints_tlbinvalid_rd_stat : 1   ; /* [2]  */
        unsigned int    ints_tlbinvalid_wr_stat : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_INTSTAT_S;

/* Define the union U_VPSS0_SMMU_INTCLR_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ints_tlbmiss_clr      : 1   ; /* [0]  */
        unsigned int    ints_ptw_trans_clr    : 1   ; /* [1]  */
        unsigned int    ints_tlbinvalid_rd_clr : 1   ; /* [2]  */
        unsigned int    ints_tlbinvalid_wr_clr : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_INTCLR_S;

/* Define the union U_VPSS0_SMMU_INTMASK_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intns_tlbmiss_msk     : 1   ; /* [0]  */
        unsigned int    intns_ptw_trans_msk   : 1   ; /* [1]  */
        unsigned int    intns_tlbinvalid_rd_msk : 1   ; /* [2]  */
        unsigned int    intns_tlbinvalid_wr_msk : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_INTMASK_NS;

/* Define the union U_VPSS0_SMMU_INTRAW_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intns_tlbmiss_raw     : 1   ; /* [0]  */
        unsigned int    intns_ptw_trans_raw   : 1   ; /* [1]  */
        unsigned int    intns_tlbinvalid_rd_raw : 1   ; /* [2]  */
        unsigned int    intns_tlbinvalid_wr_raw : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_INTRAW_NS;

/* Define the union U_VPSS0_SMMU_INTSTAT_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intns_tlbmiss_stat    : 1   ; /* [0]  */
        unsigned int    intns_ptw_trans_stat  : 1   ; /* [1]  */
        unsigned int    intns_tlbinvalid_rd_stat : 1   ; /* [2]  */
        unsigned int    intns_tlbinvalid_wr_stat : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_INTSTAT_NS;

/* Define the union U_VPSS0_SMMU_INTCLR_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intns_tlbmiss_clr     : 1   ; /* [0]  */
        unsigned int    intns_ptw_trans_clr   : 1   ; /* [1]  */
        unsigned int    intns_tlbinvalid_rd_clr : 1   ; /* [2]  */
        unsigned int    intns_tlbinvalid_wr_clr : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_INTCLR_NS;

/* Define the union U_VPSS0_SMMU_SCB_TTBR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scb_ttbr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_SCB_TTBR;
/* Define the union U_VPSS0_SMMU_CB_TTBR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cb_ttbr                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_CB_TTBR;
/* Define the union U_VPSS0_SMMU_ERR_RDADDR_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int err_s_rd_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_ERR_RDADDR_S;
/* Define the union U_VPSS0_SMMU_ERR_WRADDR_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int err_s_wr_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_ERR_WRADDR_S;
/* Define the union U_VPSS0_SMMU_ERR_RDADDR_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int err_ns_rd_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_ERR_RDADDR_NS;
/* Define the union U_VPSS0_SMMU_ERR_WRADDR_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int err_ns_wr_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_ERR_WRADDR_NS;
/* Define the union U_VPSS0_SMMU_FAULT_ADDR_PTW_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_ptw_s       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ADDR_PTW_S;
/* Define the union U_VPSS0_SMMU_FAULT_ID_PTW_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_s      : 16  ; /* [15..0]  */
        unsigned int    fault_strm_id_s       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ID_PTW_S;

/* Define the union U_VPSS0_SMMU_FAULT_ADDR_PTW_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_ptw_ns      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ADDR_PTW_NS;
/* Define the union U_VPSS0_SMMU_FAULT_ID_PTW_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_ns     : 16  ; /* [15..0]  */
        unsigned int    fault_strm_id_ns      : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ID_PTW_NS;

/* Define the union U_VPSS0_SMMU_FAULT_PTW_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_s_ptw_num       : 4   ; /* [3..0]  */
        unsigned int    fault_ns_ptw_num      : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_FAULT_PTW_NUM;

/* Define the union U_VPSS0_SMMU_FAULT_ADDR_WR_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_wr_s        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ADDR_WR_S;
/* Define the union U_VPSS0_SMMU_FAULT_TLB_WR_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_tlb_wr_s         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_TLB_WR_S;
/* Define the union U_VPSS0_SMMU_FAULT_ID_WR_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_wr_s   : 16  ; /* [15..0]  */
        unsigned int    fault_str_id_wr_s     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ID_WR_S;

/* Define the union U_VPSS0_SMMU_FAULT_ADDR_WR_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_wr_ns       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ADDR_WR_NS;
/* Define the union U_VPSS0_SMMU_FAULT_TLB_WR_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_tlb_wr_ns        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_TLB_WR_NS;
/* Define the union U_VPSS0_SMMU_FAULT_ID_WR_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_wr_ns  : 16  ; /* [15..0]  */
        unsigned int    fault_str_id_wr_ns    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ID_WR_NS;

/* Define the union U_VPSS0_SMMU_FAULT_ADDR_RD_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_rd_s        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ADDR_RD_S;
/* Define the union U_VPSS0_SMMU_FAULT_TLB_RD_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_tlb_rd_s         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_TLB_RD_S;
/* Define the union U_VPSS0_SMMU_FAULT_ID_RD_S */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_rd_s   : 16  ; /* [15..0]  */
        unsigned int    fault_str_id_rd_s     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ID_RD_S;

/* Define the union U_VPSS0_SMMU_FAULT_ADDR_RD_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_rd_ns       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ADDR_RD_NS;
/* Define the union U_VPSS0_SMMU_FAULT_TLB_RD_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_tlb_rd_ns        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VPSS0_SMMU_FAULT_TLB_RD_NS;
/* Define the union U_VPSS0_SMMU_FAULT_ID_RD_NS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_index_id_rd_ns  : 16  ; /* [15..0]  */
        unsigned int    fault_str_id_rd_ns    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_FAULT_ID_RD_NS;

/* Define the union U_VPSS0_SMMU_FAULT_TBU_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fault_tlbmiss_err_s   : 2   ; /* [1..0]  */
        unsigned int    fault_tlbinvalid_err_s : 2   ; /* [3..2]  */
        unsigned int    fault_tlbmiss_err_ns  : 2   ; /* [5..4]  */
        unsigned int    fault_tlbinvalid_err_ns : 2   ; /* [7..6]  */
        unsigned int    fault_tbu_num         : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_FAULT_TBU_INFO;

/* Define the union U_VPSS0_SMMU_FAULT_TBU_DBG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aw_valids             : 1   ; /* [0]  */
        unsigned int    aw_readys             : 1   ; /* [1]  */
        unsigned int    tbu_awreadym          : 1   ; /* [2]  */
        unsigned int    awch_stall_n          : 1   ; /* [3]  */
        unsigned int    write_command_counter : 2   ; /* [5..4]  */
        unsigned int    ar_valids             : 1   ; /* [6]  */
        unsigned int    ar_readys             : 1   ; /* [7]  */
        unsigned int    tbu_arreadym          : 1   ; /* [8]  */
        unsigned int    arch_stall_n          : 1   ; /* [9]  */
        unsigned int    read_command_counter  : 2   ; /* [11..10]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_FAULT_TBU_DBG;

/* Define the union U_VPSS0_SMMU_PREF_BUFFER_EMPTY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pref_buffer_empty     : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_PREF_BUFFER_EMPTY;

/* Define the union U_VPSS0_SMMU_PTWQ_IDLE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ptwq0_idle_state      : 1   ; /* [0]  */
        unsigned int    ptwq1_idle_state      : 1   ; /* [1]  */
        unsigned int    ptwq2_idle_state      : 1   ; /* [2]  */
        unsigned int    ptwq3_idle_state      : 1   ; /* [3]  */
        unsigned int    ptwq4_idle_state      : 1   ; /* [4]  */
        unsigned int    ptwq5_idle_state      : 1   ; /* [5]  */
        unsigned int    ptwq6_idle_state      : 1   ; /* [6]  */
        unsigned int    ptwq7_idle_state      : 1   ; /* [7]  */
        unsigned int    ptwq8_idle_state      : 1   ; /* [8]  */
        unsigned int    ptwq9_idle_state      : 1   ; /* [9]  */
        unsigned int    ptwq10_idle_state     : 1   ; /* [10]  */
        unsigned int    ptwq11_idle_state     : 1   ; /* [11]  */
        unsigned int    ptwq12_idle_state     : 1   ; /* [12]  */
        unsigned int    ptwq13_idle_state     : 1   ; /* [13]  */
        unsigned int    ptwq14_idle_state     : 1   ; /* [14]  */
        unsigned int    ptwq15_idle_state     : 1   ; /* [15]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_PTWQ_IDLE;

/* Define the union U_VPSS0_SMMU_RESET_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smmu_rst_state        : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_RESET_STATE;

/* Define the union U_VPSS0_SMMU_MASTER_DBG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    last_miss_cnt_rd      : 10  ; /* [9..0]  */
        unsigned int    cur_miss_cnt_rd       : 10  ; /* [19..10]  */
        unsigned int    vld_debug_rd          : 4   ; /* [23..20]  */
        unsigned int    rdy_debug_rd          : 4   ; /* [27..24]  */
        unsigned int    in_out_cmd_cnt_rd     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MASTER_DBG0;

/* Define the union U_VPSS0_SMMU_MASTER_DBG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    last_miss_cnt_wr      : 10  ; /* [9..0]  */
        unsigned int    cur_miss_cnt_wr       : 10  ; /* [19..10]  */
        unsigned int    vld_debug_wr          : 4   ; /* [23..20]  */
        unsigned int    rdy_debug_wr          : 4   ; /* [27..24]  */
        unsigned int    in_out_cmd_cnt_wr     : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MASTER_DBG1;

/* Define the union U_VPSS0_SMMU_MASTER_DBG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    last_double_miss_cnt_rd : 8   ; /* [7..0]  */
        unsigned int    cur_double_miss_cnt_rd : 8   ; /* [15..8]  */
        unsigned int    last_double_upd_cnt_rd : 8   ; /* [23..16]  */
        unsigned int    cur_double_upd_cnt_rd : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MASTER_DBG2;

/* Define the union U_VPSS0_SMMU_MASTER_DBG3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    last_double_miss_cnt_wr : 8   ; /* [7..0]  */
        unsigned int    cur_double_miss_cnt_wr : 8   ; /* [15..8]  */
        unsigned int    last_double_upd_cnt_wr : 7   ; /* [22..16]  */
        unsigned int    cur_double_upd_cnt_wr : 7   ; /* [29..23]  */
        unsigned int    mst_fsm_cur           : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MASTER_DBG3;

/* Define the union U_VPSS0_SMMU_MASTER_DBG4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    last_sel1_chn_miss_cnt_rd : 16  ; /* [15..0]  */
        unsigned int    cur_sel1_chn_miss_cnt_rd : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MASTER_DBG4;

/* Define the union U_VPSS0_SMMU_MASTER_DBG5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    last_sel2_chn_miss_cnt_rd : 16  ; /* [15..0]  */
        unsigned int    cur_sel2_chn_miss_cnt_rd : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MASTER_DBG5;

/* Define the union U_VPSS0_SMMU_MASTER_DBG6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    last_sel1_chn_miss_cnt_wr : 16  ; /* [15..0]  */
        unsigned int    cur_sel1_chn_miss_cnt_wr : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MASTER_DBG6;

/* Define the union U_VPSS0_SMMU_MASTER_DBG7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    last_sel2_chn_miss_cnt_wr : 16  ; /* [15..0]  */
        unsigned int    cur_sel2_chn_miss_cnt_wr : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MASTER_DBG7;

/* Define the union U_VPSS0_SMMU_MASTER_DBG8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sel2_chn_wr           : 8   ; /* [7..0]  */
        unsigned int    sel1_chn_wr           : 8   ; /* [15..8]  */
        unsigned int    sel2_chn_rd           : 8   ; /* [23..16]  */
        unsigned int    sel1_chn_rd           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS0_SMMU_MASTER_DBG8;

//==============================================================================
/* Define the global struct */
typedef struct
{
    U_VPSS_CTRL            VPSS_CTRL                         ; /* 0x0 */
    U_VPSS_CTRL2           VPSS_CTRL2                        ; /* 0x4 */
    U_VPSS_CTRL3           VPSS_CTRL3                        ; /* 0x8 */
    U_VPSS_CMD_CNT_CHN     VPSS_CMD_CNT_CHN                  ; /* 0xc */
    U_VPSS_RCH_BYPASS      VPSS_RCH_BYPASS                   ; /* 0x10 */
    U_VPSS_WCH_BYPASS      VPSS_WCH_BYPASS                   ; /* 0x14 */
    U_VPSS_VHD0_ZMEORESO   VPSS_VHD0_ZMEORESO                ; /* 0x18 */
    U_VPSS_VHD0_ZME_LHADDR   VPSS_VHD0_ZME_LHADDR            ; /* 0x1c */
    U_VPSS_VHD0_ZME_LVADDR   VPSS_VHD0_ZME_LVADDR            ; /* 0x20 */
    U_VPSS_VHD0_ZME_CHADDR   VPSS_VHD0_ZME_CHADDR            ; /* 0x24 */
    U_VPSS_VHD0_ZME_CVADDR   VPSS_VHD0_ZME_CVADDR            ; /* 0x28 */
    U_VPSS_TNR_ADDR        VPSS_TNR_ADDR                     ; /* 0x2c */
    unsigned int           reserved_0                     ; /* 0x30 */
    U_VPSS_SNR_ADDR        VPSS_SNR_ADDR                     ; /* 0x34 */
    unsigned int           reserved_1                     ; /* 0x38 */
    U_VPSS_ZME_ADDR        VPSS_ZME_ADDR                     ; /* 0x3c */
    U_VPSS_DEI_ADDR        VPSS_DEI_ADDR                     ; /* 0x40 */
    U_VPSS_HDR_ADDR        VPSS_HDR_ADDR                     ; /* 0x44 */
    unsigned int           reserved_2[172]                     ; /* 0x48~0x2f4 */
    U_VPSS_NODEID          VPSS_NODEID                       ; /* 0x2f8 */
    U_VPSS_PNEXT           VPSS_PNEXT                        ; /* 0x2fc */
    U_VPSS_START           VPSS_START                        ; /* 0x300 */
    U_VPSS_INTSTATE        VPSS_INTSTATE                     ; /* 0x304 */
    U_VPSS_INTCLR          VPSS_INTCLR                       ; /* 0x308 */
    U_VPSS_RAWINT          VPSS_RAWINT                       ; /* 0x30c */
    U_VPSS_PFCNT           VPSS_PFCNT                        ; /* 0x310 */
    unsigned int           reserved_3[2]                     ; /* 0x314~0x318 */
    U_VPSS_TIMEOUT         VPSS_TIMEOUT                      ; /* 0x31c */
    U_VPSS_FTCONFIG        VPSS_FTCONFIG                     ; /* 0x320 */
    U_VPSS_INTMASK         VPSS_INTMASK                      ; /* 0x324 */
    unsigned int           reserved_4[2]                     ; /* 0x328~0x32c */
    U_VPSS_EOFCNT          VPSS_EOFCNT                       ; /* 0x330 */
    unsigned int           reserved_5[3]                     ; /* 0x334~0x33c */
    U_VPSS_VERSION         VPSS_VERSION                      ; /* 0x340 */
    unsigned int           reserved_6                     ; /* 0x344 */
    U_VPSS_LOWPOWER_CTRL   VPSS_LOWPOWER_CTRL                ; /* 0x348 */
    U_VPSS_LOWPOWER_CTRL1   VPSS_LOWPOWER_CTRL1              ; /* 0x34c */
    U_VPSS_HOLD_CTRL       VPSS_HOLD_CTRL                    ; /* 0x350 */
    U_VPSS_HARDGATE_CTRL   VPSS_HARDGATE_CTRL                ; /* 0x354 */
    unsigned int           reserved_7[3]                     ; /* 0x358~0x360 */
    U_VPSS_LINKLIST_CNT    VPSS_LINKLIST_CNT                 ; /* 0x364 */
    unsigned int           reserved_8[38]                     ; /* 0x368~0x3fc */
    U_VPSS_MST_OUTSTANDING   VPSS_MST_OUTSTANDING            ; /* 0x400 */
    U_VPSS_MST_CTRL        VPSS_MST_CTRL                     ; /* 0x404 */
    unsigned int           reserved_9[2]                     ; /* 0x408~0x40c */
    U_VPSS_MST_RCHN_PRIO0   VPSS_MST_RCHN_PRIO0              ; /* 0x410 */
    unsigned int           reserved_10                     ; /* 0x414 */
    U_VPSS_MST_WCHN_PRIO0   VPSS_MST_WCHN_PRIO0              ; /* 0x418 */
    unsigned int           reserved_11[9]                     ; /* 0x41c~0x43c */
    U_VPSS_MST_BUS_ERR_CLR   VPSS_MST_BUS_ERR_CLR            ; /* 0x440 */
    U_VPSS_MST_BUS_ERR     VPSS_MST_BUS_ERR                  ; /* 0x444 */
    unsigned int           reserved_12[2]                     ; /* 0x448~0x44c */
    U_VPSS_MST_SRC0_STATUS0   VPSS_MST_SRC0_STATUS0          ; /* 0x450 */
    U_VPSS_MST_SRC0_STATUS1   VPSS_MST_SRC0_STATUS1          ; /* 0x454 */
    unsigned int           reserved_13[6]                     ; /* 0x458~0x46c */
    U_VPSS_MST_DEBUG_CTRL   VPSS_MST_DEBUG_CTRL              ; /* 0x470 */
    U_VPSS_MST_DEBUG_CLR   VPSS_MST_DEBUG_CLR                ; /* 0x474 */
    unsigned int           reserved_14[2]                     ; /* 0x478~0x47c */
    U_VPSS_MST0_DET_LATENCY   VPSS_MST0_DET_LATENCY          ; /* 0x480 */
    unsigned int           reserved_15[3]                     ; /* 0x484~0x48c */
    U_VPSS_MST0_RD_INFO    VPSS_MST0_RD_INFO                 ; /* 0x490 */
    U_VPSS_MST0_WR_INFO    VPSS_MST0_WR_INFO                 ; /* 0x494 */
    unsigned int           reserved_16[124]                     ; /* 0x498~0x684 */
    U_VPSS_VHD0CROP_SIZE   VPSS_VHD0CROP_SIZE                ; /* 0x688 */
    U_VPSS_VHD0CROP_POS    VPSS_VHD0CROP_POS                 ; /* 0x68c */
    U_VPSS_VHD0LBA_DSIZE   VPSS_VHD0LBA_DSIZE                ; /* 0x690 */
    U_VPSS_VHD0LBA_VFPOS   VPSS_VHD0LBA_VFPOS                ; /* 0x694 */
    U_VPSS_VHD0LBA_BK      VPSS_VHD0LBA_BK                   ; /* 0x698 */
    U_VPSS_VC1_CTRL        VPSS_VC1_CTRL                     ; /* 0x69c */
    unsigned int           reserved_17[600]                     ; /* 0x6a0~0xffc */
    U_VPSS_DIECTRL         VPSS_DIECTRL                      ; /* 0x1000 */
    U_VPSS_DIELMA2         VPSS_DIELMA2                      ; /* 0x1004 */
    U_VPSS_DIEINTEN        VPSS_DIEINTEN                     ; /* 0x1008 */
    U_VPSS_DIESCALE        VPSS_DIESCALE                     ; /* 0x100c */
    U_VPSS_DIECHECK1       VPSS_DIECHECK1                    ; /* 0x1010 */
    U_VPSS_DIECHECK2       VPSS_DIECHECK2                    ; /* 0x1014 */
    U_VPSS_DIEDIR0_3       VPSS_DIEDIR0_3                    ; /* 0x1018 */
    U_VPSS_DIEDIR4_7       VPSS_DIEDIR4_7                    ; /* 0x101c */
    U_VPSS_DIEDIR8_11      VPSS_DIEDIR8_11                   ; /* 0x1020 */
    U_VPSS_DIEDIR12_14     VPSS_DIEDIR12_14                  ; /* 0x1024 */
    U_VPSS_DIESTA          VPSS_DIESTA                       ; /* 0x1028 */
    U_VPSS_DIEINTPSCL0     VPSS_DIEINTPSCL0                  ; /* 0x102c */
    U_VPSS_DIEINTPSCL1     VPSS_DIEINTPSCL1                  ; /* 0x1030 */
    U_VPSS_DIEDIRTHD       VPSS_DIEDIRTHD                    ; /* 0x1034 */
    U_VPSS_DIEJITMTN       VPSS_DIEJITMTN                    ; /* 0x1038 */
    U_VPSS_DIEFLDMTN       VPSS_DIEFLDMTN                    ; /* 0x103c */
    U_VPSS_DIEMTNDIFFTHD0   VPSS_DIEMTNDIFFTHD0              ; /* 0x1040 */
    U_VPSS_DIEMTNDIFFTHD1   VPSS_DIEMTNDIFFTHD1              ; /* 0x1044 */
    U_VPSS_DIEMTNIIRSLP    VPSS_DIEMTNIIRSLP                 ; /* 0x1048 */
    U_VPSS_DIEMTNIIRRAT    VPSS_DIEMTNIIRRAT                 ; /* 0x104c */
    U_VPSS_DIEHISMODE      VPSS_DIEHISMODE                   ; /* 0x1050 */
    U_VPSS_DIEMORFLT       VPSS_DIEMORFLT                    ; /* 0x1054 */
    U_VPSS_DIECOMBCHK0     VPSS_DIECOMBCHK0                  ; /* 0x1058 */
    U_VPSS_DIECOMBCHK1     VPSS_DIECOMBCHK1                  ; /* 0x105c */
    U_VPSS_DIEFRMMTNSMTHTHD0   VPSS_DIEFRMMTNSMTHTHD0        ; /* 0x1060 */
    U_VPSS_DIEFRMMTNSMTHTHD1   VPSS_DIEFRMMTNSMTHTHD1        ; /* 0x1064 */
    U_VPSS_DIEFRMMTNSMTHSLP   VPSS_DIEFRMMTNSMTHSLP          ; /* 0x1068 */
    U_VPSS_DIEFRMMTNSMTHRAT   VPSS_DIEFRMMTNSMTHRAT          ; /* 0x106c */
    U_VPSS_DIEFRMFLDBLENDTHD0   VPSS_DIEFRMFLDBLENDTHD0      ; /* 0x1070 */
    U_VPSS_DIEFRMFLDBLENDTHD1   VPSS_DIEFRMFLDBLENDTHD1      ; /* 0x1074 */
    U_VPSS_DIEFRMFLDBLENDSLP   VPSS_DIEFRMFLDBLENDSLP        ; /* 0x1078 */
    U_VPSS_DIEFRMFLDBLENDRAT   VPSS_DIEFRMFLDBLENDRAT        ; /* 0x107c */
    U_VPSS_DIEMTNADJ       VPSS_DIEMTNADJ                    ; /* 0x1080 */
    U_VPSS_DIEEDGENORM0    VPSS_DIEEDGENORM0                 ; /* 0x1084 */
    U_VPSS_DIEEDGENORM1    VPSS_DIEEDGENORM1                 ; /* 0x1088 */
    U_VPSS_DIEEDGENORM2    VPSS_DIEEDGENORM2                 ; /* 0x108c */
    U_VPSS_DIEEDGENORM3    VPSS_DIEEDGENORM3                 ; /* 0x1090 */
    U_VPSS_DIEEDGENORM4    VPSS_DIEEDGENORM4                 ; /* 0x1094 */
    U_VPSS_DIEEDGENORM5    VPSS_DIEEDGENORM5                 ; /* 0x1098 */
    U_VPSS_DIEEDGEFORMC    VPSS_DIEEDGEFORMC                 ; /* 0x109c */
    U_VPSS_DIEMCSTRENGTH0   VPSS_DIEMCSTRENGTH0              ; /* 0x10a0 */
    U_VPSS_DIEMCSTRENGTH1   VPSS_DIEMCSTRENGTH1              ; /* 0x10a4 */
    U_VPSS_DIEFUSION0      VPSS_DIEFUSION0                   ; /* 0x10a8 */
    U_VPSS_DIEFUSION1      VPSS_DIEFUSION1                   ; /* 0x10ac */
    U_VPSS_DIEFUSION2      VPSS_DIEFUSION2                   ; /* 0x10b0 */
    U_VPSS_DIEFUSION3      VPSS_DIEFUSION3                   ; /* 0x10b4 */
    U_VPSS_DIEMAGBMTHD0    VPSS_DIEMAGBMTHD0                 ; /* 0x10b8 */
    U_VPSS_DIEMAGBMTHD1    VPSS_DIEMAGBMTHD1                 ; /* 0x10bc */
    U_VPSS_DIEMCGBMCOEF0   VPSS_DIEMCGBMCOEF0                ; /* 0x10c0 */
    U_VPSS_DIEMCGBMCOEF1   VPSS_DIEMCGBMCOEF1                ; /* 0x10c4 */
    U_VPSS_DIEKMAG1        VPSS_DIEKMAG1                     ; /* 0x10c8 */
    U_VPSS_DIEKMAG2        VPSS_DIEKMAG2                     ; /* 0x10cc */
    U_VPSS_DIE_S3ADD       VPSS_DIE_S3ADD                    ; /* 0x10d0 */
    U_VPSS_PDPHISTTHD1     VPSS_PDPHISTTHD1                  ; /* 0x10d4 */
    U_VPSS_PDPCCMOV        VPSS_PDPCCMOV                     ; /* 0x10d8 */
    U_VPSS_PDCTRL          VPSS_PDCTRL                       ; /* 0x10dc */
    U_VPSS_PDBLKTHD        VPSS_PDBLKTHD                     ; /* 0x10e0 */
    U_VPSS_PDUMTHD         VPSS_PDUMTHD                      ; /* 0x10e4 */
    U_VPSS_PDPCCCORING     VPSS_PDPCCCORING                  ; /* 0x10e8 */
    U_VPSS_PDPCCHTHD       VPSS_PDPCCHTHD                    ; /* 0x10ec */
    U_VPSS_PDPCCVTHD       VPSS_PDPCCVTHD                    ; /* 0x10f0 */
    U_VPSS_PDITDIFFVTHD    VPSS_PDITDIFFVTHD                 ; /* 0x10f4 */
    U_VPSS_PDLASITHD       VPSS_PDLASITHD                    ; /* 0x10f8 */
    U_VPSS_PDLASIMODE0COEF   VPSS_PDLASIMODE0COEF            ; /* 0x10fc */
    U_VPSS_PDLASIMODE1COEF   VPSS_PDLASIMODE1COEF            ; /* 0x1100 */
    U_VPSS_PDREGION        VPSS_PDREGION                     ; /* 0x1104 */
    U_VPSS_MCDI_RGDIFY     VPSS_MCDI_RGDIFY                  ; /* 0x1108 */
    U_VPSS_MCDI_RGSAD      VPSS_MCDI_RGSAD                   ; /* 0x110c */
    U_VPSS_MCDI_RGMV       VPSS_MCDI_RGMV                    ; /* 0x1110 */
    U_VPSS_MCDI_RGMAG0     VPSS_MCDI_RGMAG0                  ; /* 0x1114 */
    U_VPSS_MCDI_RGMAG1     VPSS_MCDI_RGMAG1                  ; /* 0x1118 */
    U_VPSS_MCDI_RGLS       VPSS_MCDI_RGLS                    ; /* 0x111c */
    U_VPSS_MCDI_SEL        VPSS_MCDI_SEL                     ; /* 0x1120 */
    U_VPSS_MCDI_DLT0       VPSS_MCDI_DLT0                    ; /* 0x1124 */
    U_VPSS_MCDI_DLT1       VPSS_MCDI_DLT1                    ; /* 0x1128 */
    U_VPSS_MCDI_RGMCW0     VPSS_MCDI_RGMCW0                  ; /* 0x112c */
    U_VPSS_MCDI_RGMCW1     VPSS_MCDI_RGMCW1                  ; /* 0x1130 */
    U_VPSS_MCDI_RGMCW2     VPSS_MCDI_RGMCW2                  ; /* 0x1134 */
    U_VPSS_MCDI_RGMCW3     VPSS_MCDI_RGMCW3                  ; /* 0x1138 */
    U_VPSS_MCDI_RGMCW4     VPSS_MCDI_RGMCW4                  ; /* 0x113c */
    U_VPSS_MCDI_RGMCW5     VPSS_MCDI_RGMCW5                  ; /* 0x1140 */
    U_VPSS_MCDI_RGMCW6     VPSS_MCDI_RGMCW6                  ; /* 0x1144 */
    U_VPSS_MCDI_TPMCW0     VPSS_MCDI_TPMCW0                  ; /* 0x1148 */
    U_VPSS_MCDI_TPMCW1     VPSS_MCDI_TPMCW1                  ; /* 0x114c */
    U_VPSS_MCDI_WNDMCW0    VPSS_MCDI_WNDMCW0                 ; /* 0x1150 */
    U_VPSS_MCDI_WNDMCW1    VPSS_MCDI_WNDMCW1                 ; /* 0x1154 */
    U_VPSS_MCDI_WNDMCW2    VPSS_MCDI_WNDMCW2                 ; /* 0x1158 */
    U_VPSS_MCDI_WNDMCW3    VPSS_MCDI_WNDMCW3                 ; /* 0x115c */
    U_VPSS_MCDI_VERTWEIGHT0   VPSS_MCDI_VERTWEIGHT0          ; /* 0x1160 */
    U_VPSS_MCDI_VERTWEIGHT1   VPSS_MCDI_VERTWEIGHT1          ; /* 0x1164 */
    U_VPSS_MCDI_VERTWEIGHT2   VPSS_MCDI_VERTWEIGHT2          ; /* 0x1168 */
    U_VPSS_MCDI_VERTWEIGHT3   VPSS_MCDI_VERTWEIGHT3          ; /* 0x116c */
    U_VPSS_MCDI_VERTWEIGHT4   VPSS_MCDI_VERTWEIGHT4          ; /* 0x1170 */
    U_VPSS_MCDI_VERTWEIGHT5   VPSS_MCDI_VERTWEIGHT5          ; /* 0x1174 */
    U_VPSS_MCDI_MC0        VPSS_MCDI_MC0                     ; /* 0x1178 */
    U_VPSS_MCDI_MC1        VPSS_MCDI_MC1                     ; /* 0x117c */
    U_VPSS_MCDI_MC2        VPSS_MCDI_MC2                     ; /* 0x1180 */
    U_VPSS_MCDI_MC3        VPSS_MCDI_MC3                     ; /* 0x1184 */
    U_VPSS_MCDI_MC4        VPSS_MCDI_MC4                     ; /* 0x1188 */
    U_VPSS_MCDI_MC5        VPSS_MCDI_MC5                     ; /* 0x118c */
    U_VPSS_MCDI_MC6        VPSS_MCDI_MC6                     ; /* 0x1190 */
    U_VPSS_MCDI_MC7        VPSS_MCDI_MC7                     ; /* 0x1194 */
    U_VPSS_MCDI_LCDINEW0   VPSS_MCDI_LCDINEW0                ; /* 0x1198 */
    U_VPSS_MCDI_LCDINEW1   VPSS_MCDI_LCDINEW1                ; /* 0x119c */
    U_VPSS_MCDI_NUMT       VPSS_MCDI_NUMT                    ; /* 0x11a0 */
    U_VPSS_MCDI_S3ADD0     VPSS_MCDI_S3ADD0                  ; /* 0x11a4 */
    U_VPSS_MCDI_S3ADD1     VPSS_MCDI_S3ADD1                  ; /* 0x11a8 */
    U_VPSS_MCDI_S3ADD2     VPSS_MCDI_S3ADD2                  ; /* 0x11ac */
    U_VPSS_MCDI_S3ADD3     VPSS_MCDI_S3ADD3                  ; /* 0x11b0 */
    U_VPSS_MCDI_S3ADD4     VPSS_MCDI_S3ADD4                  ; /* 0x11b4 */
    U_VPSS_MCDI_S3ADD5     VPSS_MCDI_S3ADD5                  ; /* 0x11b8 */
    U_VPSS_MCDI_S3ADD6     VPSS_MCDI_S3ADD6                  ; /* 0x11bc */
    U_VPSS_MCDI_S3ADD7     VPSS_MCDI_S3ADD7                  ; /* 0x11c0 */
    U_VPSS_MCDI_STILLCNT0   VPSS_MCDI_STILLCNT0              ; /* 0x11c4 */
    U_VPSS_MCDI_STILLCNT1   VPSS_MCDI_STILLCNT1              ; /* 0x11c8 */
    U_VPSS_MCDI_DEMO       VPSS_MCDI_DEMO                    ; /* 0x11cc */
    unsigned int           reserved_18[908]                     ; /* 0x11d0~0x1ffc */
    U_VPSS_VHD0_HSP        VPSS_VHD0_HSP                     ; /* 0x2000 */
    U_VPSS_VHD0_HLOFFSET   VPSS_VHD0_HLOFFSET                ; /* 0x2004 */
    U_VPSS_VHD0_HCOFFSET   VPSS_VHD0_HCOFFSET                ; /* 0x2008 */
    U_VPSS_VHD0_VSP        VPSS_VHD0_VSP                     ; /* 0x200c */
    U_VPSS_VHD0_VSR        VPSS_VHD0_VSR                     ; /* 0x2010 */
    U_VPSS_VHD0_VOFFSET    VPSS_VHD0_VOFFSET                 ; /* 0x2014 */
    unsigned int           reserved_19[58]                     ; /* 0x2018~0x20fc */
    U_VPSS_DB_CTRL         VPSS_DB_CTRL                      ; /* 0x2100 */
    U_VPSS_DBM_DEMO        VPSS_DBM_DEMO                     ; /* 0x2104 */
    U_VPSS_DB_DIR          VPSS_DB_DIR                       ; /* 0x2108 */
    U_VPSS_DB_BLK          VPSS_DB_BLK                       ; /* 0x210c */
    U_VPSS_DB_RATIO        VPSS_DB_RATIO                     ; /* 0x2110 */
    U_VPSS_DB_LHHF         VPSS_DB_LHHF                      ; /* 0x2114 */
    U_VPSS_DB_LVHF         VPSS_DB_LVHF                      ; /* 0x2118 */
    U_VPSS_DB_CTRS         VPSS_DB_CTRS                      ; /* 0x211c */
    U_VPSS_DB_LUT0         VPSS_DB_LUT0                      ; /* 0x2120 */
    U_VPSS_DB_LUT1         VPSS_DB_LUT1                      ; /* 0x2124 */
    U_VPSS_DB_LUT2         VPSS_DB_LUT2                      ; /* 0x2128 */
    U_VPSS_DB_LUT3         VPSS_DB_LUT3                      ; /* 0x212c */
    U_VPSS_DB_LUT4         VPSS_DB_LUT4                      ; /* 0x2130 */
    U_VPSS_DB_LUT5         VPSS_DB_LUT5                      ; /* 0x2134 */
    U_VPSS_DB_LUT6         VPSS_DB_LUT6                      ; /* 0x2138 */
    unsigned int           reserved_20[5]                     ; /* 0x213c~0x214c */
    U_VPSS_DBD_THDEDGE     VPSS_DBD_THDEDGE                  ; /* 0x2150 */
    U_VPSS_DBD_THDTXT      VPSS_DBD_THDTXT                   ; /* 0x2154 */
    U_VPSS_DBD_LUTWGT0     VPSS_DBD_LUTWGT0                  ; /* 0x2158 */
    U_VPSS_DBD_LUTWGT1     VPSS_DBD_LUTWGT1                  ; /* 0x215c */
    U_VPSS_DBD_RTNBDTXT    VPSS_DBD_RTNBDTXT                 ; /* 0x2160 */
    U_VPSS_DBD_TSTBLKNUM   VPSS_DBD_TSTBLKNUM                ; /* 0x2164 */
    U_VPSS_DBD_HYRDX8BINLUT0   VPSS_DBD_HYRDX8BINLUT0        ; /* 0x2168 */
    U_VPSS_DBD_HYRDX8BINLUT1   VPSS_DBD_HYRDX8BINLUT1        ; /* 0x216c */
    U_VPSS_DBD_HYRDX8BINLUT2   VPSS_DBD_HYRDX8BINLUT2        ; /* 0x2170 */
    U_VPSS_DBD_HYRDX8BINLUT3   VPSS_DBD_HYRDX8BINLUT3        ; /* 0x2174 */
    U_VPSS_DBD_BLKSIZE     VPSS_DBD_BLKSIZE                  ; /* 0x2178 */
    U_VPSS_DBD_FLAT        VPSS_DBD_FLAT                     ; /* 0x217c */
    unsigned int           reserved_21[4]                     ; /* 0x2180~0x218c */
    U_VPSS_DM_DIR          VPSS_DM_DIR                       ; /* 0x2190 */
    U_VPSS_DM_EDGE         VPSS_DM_EDGE                      ; /* 0x2194 */
    U_VPSS_DM_LUT0         VPSS_DM_LUT0                      ; /* 0x2198 */
    U_VPSS_DM_LUT1         VPSS_DM_LUT1                      ; /* 0x219c */
    U_VPSS_DM_LUT2         VPSS_DM_LUT2                      ; /* 0x21a0 */
    U_VPSS_DM_LUT3         VPSS_DM_LUT3                      ; /* 0x21a4 */
    U_VPSS_DM_LUT4         VPSS_DM_LUT4                      ; /* 0x21a8 */
    U_VPSS_DM_DIRC         VPSS_DM_DIRC                      ; /* 0x21ac */
    U_VPSS_DM_DIRO         VPSS_DM_DIRO                      ; /* 0x21b0 */
    U_VPSS_DM_LSW          VPSS_DM_LSW                       ; /* 0x21b4 */
    U_VPSS_DM_MMFLR        VPSS_DM_MMFLR                     ; /* 0x21b8 */
    U_VPSS_DM_MMFSR        VPSS_DM_MMFSR                     ; /* 0x21bc */
    U_VPSS_DM_THR0         VPSS_DM_THR0                      ; /* 0x21c0 */
    U_VPSS_DM_LUT5         VPSS_DM_LUT5                      ; /* 0x21c4 */
    U_VPSS_DM_LUT6         VPSS_DM_LUT6                      ; /* 0x21c8 */
    U_VPSS_DM_LUT7         VPSS_DM_LUT7                      ; /* 0x21cc */
    U_VPSS_DM_LUT8         VPSS_DM_LUT8                      ; /* 0x21d0 */
    U_VPSS_DM_LUT9         VPSS_DM_LUT9                      ; /* 0x21d4 */
    U_VPSS_DM_LUT10        VPSS_DM_LUT10                     ; /* 0x21d8 */
    U_VPSS_DM_LUT11        VPSS_DM_LUT11                     ; /* 0x21dc */
    unsigned int           reserved_22[8]                     ; /* 0x21e0~0x21fc */
    U_VPSS_DB_BORD_FLAG0   VPSS_DB_BORD_FLAG0                ; /* 0x2200 */
    U_VPSS_DB_BORD_FLAG1   VPSS_DB_BORD_FLAG1                ; /* 0x2204 */
    U_VPSS_DB_BORD_FLAG2   VPSS_DB_BORD_FLAG2                ; /* 0x2208 */
    U_VPSS_DB_BORD_FLAG3   VPSS_DB_BORD_FLAG3                ; /* 0x220c */
    U_VPSS_DB_BORD_FLAG4   VPSS_DB_BORD_FLAG4                ; /* 0x2210 */
    U_VPSS_DB_BORD_FLAG5   VPSS_DB_BORD_FLAG5                ; /* 0x2214 */
    U_VPSS_DB_BORD_FLAG6   VPSS_DB_BORD_FLAG6                ; /* 0x2218 */
    U_VPSS_DB_BORD_FLAG7   VPSS_DB_BORD_FLAG7                ; /* 0x221c */
    U_VPSS_DB_BORD_FLAG8   VPSS_DB_BORD_FLAG8                ; /* 0x2220 */
    U_VPSS_DB_BORD_FLAG9   VPSS_DB_BORD_FLAG9                ; /* 0x2224 */
    U_VPSS_DB_BORD_FLAG10   VPSS_DB_BORD_FLAG10              ; /* 0x2228 */
    U_VPSS_DB_BORD_FLAG11   VPSS_DB_BORD_FLAG11              ; /* 0x222c */
    U_VPSS_DB_BORD_FLAG12   VPSS_DB_BORD_FLAG12              ; /* 0x2230 */
    U_VPSS_DB_BORD_FLAG13   VPSS_DB_BORD_FLAG13              ; /* 0x2234 */
    U_VPSS_DB_BORD_FLAG14   VPSS_DB_BORD_FLAG14              ; /* 0x2238 */
    U_VPSS_DB_BORD_FLAG15   VPSS_DB_BORD_FLAG15              ; /* 0x223c */
    U_VPSS_DB_BORD_FLAG16   VPSS_DB_BORD_FLAG16              ; /* 0x2240 */
    U_VPSS_DB_BORD_FLAG17   VPSS_DB_BORD_FLAG17              ; /* 0x2244 */
    U_VPSS_DB_BORD_FLAG18   VPSS_DB_BORD_FLAG18              ; /* 0x2248 */
    U_VPSS_DB_BORD_FLAG19   VPSS_DB_BORD_FLAG19              ; /* 0x224c */
    U_VPSS_DB_BORD_FLAG20   VPSS_DB_BORD_FLAG20              ; /* 0x2250 */
    U_VPSS_DB_BORD_FLAG21   VPSS_DB_BORD_FLAG21              ; /* 0x2254 */
    U_VPSS_DB_BORD_FLAG22   VPSS_DB_BORD_FLAG22              ; /* 0x2258 */
    U_VPSS_DB_BORD_FLAG23   VPSS_DB_BORD_FLAG23              ; /* 0x225c */
    U_VPSS_DB_BORD_FLAG24   VPSS_DB_BORD_FLAG24              ; /* 0x2260 */
    U_VPSS_DB_BORD_FLAG25   VPSS_DB_BORD_FLAG25              ; /* 0x2264 */
    U_VPSS_DB_BORD_FLAG26   VPSS_DB_BORD_FLAG26              ; /* 0x2268 */
    U_VPSS_DB_BORD_FLAG27   VPSS_DB_BORD_FLAG27              ; /* 0x226c */
    U_VPSS_DB_BORD_FLAG28   VPSS_DB_BORD_FLAG28              ; /* 0x2270 */
    U_VPSS_DB_BORD_FLAG29   VPSS_DB_BORD_FLAG29              ; /* 0x2274 */
    U_VPSS_DB_BORD_FLAG30   VPSS_DB_BORD_FLAG30              ; /* 0x2278 */
    U_VPSS_DB_BORD_FLAG31   VPSS_DB_BORD_FLAG31              ; /* 0x227c */
    unsigned int           reserved_23[32]                     ; /* 0x2280~0x22fc */
    U_VPSS_SNR_ENABLE      VPSS_SNR_ENABLE                   ; /* 0x2300 */
    U_VPSS_SNR_EDGE_RATIORANGE   VPSS_SNR_EDGE_RATIORANGE    ; /* 0x2304 */
    U_VPSS_SNR_EDGE_STRRANGE   VPSS_SNR_EDGE_STRRANGE        ; /* 0x2308 */
    U_VPSS_SNR_EDGE_STRTH   VPSS_SNR_EDGE_STRTH              ; /* 0x230c */
    U_VPSS_SNR_EDGE_STRK   VPSS_SNR_EDGE_STRK                ; /* 0x2310 */
    U_VPSS_SNR_EDGE_MEANTH1   VPSS_SNR_EDGE_MEANTH1          ; /* 0x2314 */
    U_VPSS_SNR_EDGE_MEANTH2   VPSS_SNR_EDGE_MEANTH2          ; /* 0x2318 */
    U_VPSS_SNR_EDGE_MEANTH3   VPSS_SNR_EDGE_MEANTH3          ; /* 0x231c */
    U_VPSS_SNR_EDGE_MEANK1   VPSS_SNR_EDGE_MEANK1            ; /* 0x2320 */
    U_VPSS_SNR_EDGE_MEANK2   VPSS_SNR_EDGE_MEANK2            ; /* 0x2324 */
    U_VPSS_SNR_WIN         VPSS_SNR_WIN                      ; /* 0x2328 */
    U_VPSS_SNR_STR         VPSS_SNR_STR                      ; /* 0x232c */
    U_VPSS_SNR_STR_OFFSET   VPSS_SNR_STR_OFFSET              ; /* 0x2330 */
    U_VPSS_SNR_STR_ADJUST   VPSS_SNR_STR_ADJUST              ; /* 0x2334 */
    U_VPSS_SNR_SCHANGE_TH   VPSS_SNR_SCHANGE_TH              ; /* 0x2338 */
    U_VPSS_SNR_EDGE_RATIO_1   VPSS_SNR_EDGE_RATIO_1          ; /* 0x233c */
    U_VPSS_SNR_EDGE_RATIO_2   VPSS_SNR_EDGE_RATIO_2          ; /* 0x2340 */
    U_VPSS_SNR_EDGE_RATIO_3   VPSS_SNR_EDGE_RATIO_3          ; /* 0x2344 */
    U_VPSS_SNR_EDGE_STR    VPSS_SNR_EDGE_STR                 ; /* 0x2348 */
    U_VPSS_SNR_TEST_COLOR   VPSS_SNR_TEST_COLOR              ; /* 0x234c */
    U_VPSS_SNR_SCHANGE     VPSS_SNR_SCHANGE                  ; /* 0x2350 */
    U_VPSS_SNR_MT          VPSS_SNR_MT                       ; /* 0x2354 */
    U_VPSS_SNR_CBCR_W1     VPSS_SNR_CBCR_W1                  ; /* 0x2358 */
    U_VPSS_SNR_CBCR_W2     VPSS_SNR_CBCR_W2                  ; /* 0x235c */
    U_MOTION_EDGE_LUT_01   MOTION_EDGE_LUT_01                ; /* 0x2360 */
    U_MOTION_EDGE_LUT_02   MOTION_EDGE_LUT_02                ; /* 0x2364 */
    U_MOTION_EDGE_LUT_03   MOTION_EDGE_LUT_03                ; /* 0x2368 */
    U_MOTION_EDGE_LUT_04   MOTION_EDGE_LUT_04                ; /* 0x236c */
    U_MOTION_EDGE_LUT_05   MOTION_EDGE_LUT_05                ; /* 0x2370 */
    U_MOTION_EDGE_LUT_06   MOTION_EDGE_LUT_06                ; /* 0x2374 */
    U_MOTION_EDGE_LUT_07   MOTION_EDGE_LUT_07                ; /* 0x2378 */
    U_MOTION_EDGE_LUT_08   MOTION_EDGE_LUT_08                ; /* 0x237c */
    U_MOTION_EDGE_LUT_09   MOTION_EDGE_LUT_09                ; /* 0x2380 */
    U_MOTION_EDGE_LUT_10   MOTION_EDGE_LUT_10                ; /* 0x2384 */
    U_MOTION_EDGE_LUT_11   MOTION_EDGE_LUT_11                ; /* 0x2388 */
    U_MOTION_EDGE_LUT_12   MOTION_EDGE_LUT_12                ; /* 0x238c */
    U_MOTION_EDGE_LUT_13   MOTION_EDGE_LUT_13                ; /* 0x2390 */
    U_MOTION_EDGE_LUT_14   MOTION_EDGE_LUT_14                ; /* 0x2394 */
    U_MOTION_EDGE_LUT_15   MOTION_EDGE_LUT_15                ; /* 0x2398 */
    U_MOTION_EDGE_LUT_16   MOTION_EDGE_LUT_16                ; /* 0x239c */
    U_MOTION_EDGE_LUT_17   MOTION_EDGE_LUT_17                ; /* 0x23a0 */
    U_MOTION_EDGE_LUT_18   MOTION_EDGE_LUT_18                ; /* 0x23a4 */
    U_MOTION_EDGE_LUT_19   MOTION_EDGE_LUT_19                ; /* 0x23a8 */
    U_MOTION_EDGE_LUT_20   MOTION_EDGE_LUT_20                ; /* 0x23ac */
    U_MOTION_EDGE_LUT_21   MOTION_EDGE_LUT_21                ; /* 0x23b0 */
    U_MOTION_EDGE_LUT_22   MOTION_EDGE_LUT_22                ; /* 0x23b4 */
    U_MOTION_EDGE_LUT_23   MOTION_EDGE_LUT_23                ; /* 0x23b8 */
    U_MOTION_EDGE_LUT_24   MOTION_EDGE_LUT_24                ; /* 0x23bc */
    U_MOTION_EDGE_LUT_25   MOTION_EDGE_LUT_25                ; /* 0x23c0 */
    U_MOTION_EDGE_LUT_26   MOTION_EDGE_LUT_26                ; /* 0x23c4 */
    U_MOTION_EDGE_LUT_27   MOTION_EDGE_LUT_27                ; /* 0x23c8 */
    U_MOTION_EDGE_LUT_28   MOTION_EDGE_LUT_28                ; /* 0x23cc */
    U_MOTION_EDGE_LUT_29   MOTION_EDGE_LUT_29                ; /* 0x23d0 */
    U_MOTION_EDGE_LUT_30   MOTION_EDGE_LUT_30                ; /* 0x23d4 */
    U_MOTION_EDGE_LUT_31   MOTION_EDGE_LUT_31                ; /* 0x23d8 */
    U_MOTION_EDGE_LUT_32   MOTION_EDGE_LUT_32                ; /* 0x23dc */
    unsigned int           reserved_24[8]                     ; /* 0x23e0~0x23fc */
    U_VPSS_LCHDR_CTRL      VPSS_LCHDR_CTRL                   ; /* 0x2400 */
    U_VPSS_LCHDR_CSC_COEF0   VPSS_LCHDR_CSC_COEF0            ; /* 0x2404 */
    U_VPSS_LCHDR_CSC_COEF1   VPSS_LCHDR_CSC_COEF1            ; /* 0x2408 */
    U_VPSS_LCHDR_SCALE2P   VPSS_LCHDR_SCALE2P                ; /* 0x240c */
    U_VPSS_LCHDR_TMAP_STEP   VPSS_LCHDR_TMAP_STEP            ; /* 0x2410 */
    U_VPSS_LCHDR_TMAP_NUM   VPSS_LCHDR_TMAP_NUM              ; /* 0x2414 */
    U_VPSS_LCHDR_TMAP_POS0   VPSS_LCHDR_TMAP_POS0            ; /* 0x2418 */
    U_VPSS_LCHDR_TMAP_POS1   VPSS_LCHDR_TMAP_POS1            ; /* 0x241c */
    U_VPSS_LCHDR_DITHER_FUNC   VPSS_LCHDR_DITHER_FUNC        ; /* 0x2420 */
    U_VPSS_LCHDR_DITHER_THR   VPSS_LCHDR_DITHER_THR          ; /* 0x2424 */
    U_VPSS_LCHDR_DITHER_SEED   VPSS_LCHDR_DITHER_SEED        ; /* 0x2428 */
    unsigned int           reserved_25[53]                     ; /* 0x242c~0x24fc */
    U_VPSS_LCHDR_TMAP_LUT0   VPSS_LCHDR_TMAP_LUT0            ; /* 0x2500 */
    U_VPSS_LCHDR_TMAP_LUT1   VPSS_LCHDR_TMAP_LUT1            ; /* 0x2504 */
    U_VPSS_LCHDR_TMAP_LUT2   VPSS_LCHDR_TMAP_LUT2            ; /* 0x2508 */
    U_VPSS_LCHDR_TMAP_LUT3   VPSS_LCHDR_TMAP_LUT3            ; /* 0x250c */
    U_VPSS_LCHDR_TMAP_LUT4   VPSS_LCHDR_TMAP_LUT4            ; /* 0x2510 */
    U_VPSS_LCHDR_TMAP_LUT5   VPSS_LCHDR_TMAP_LUT5            ; /* 0x2514 */
    U_VPSS_LCHDR_TMAP_LUT6   VPSS_LCHDR_TMAP_LUT6            ; /* 0x2518 */
    U_VPSS_LCHDR_TMAP_LUT7   VPSS_LCHDR_TMAP_LUT7            ; /* 0x251c */
    U_VPSS_LCHDR_TMAP_LUT8   VPSS_LCHDR_TMAP_LUT8            ; /* 0x2520 */
    U_VPSS_LCHDR_TMAP_LUT9   VPSS_LCHDR_TMAP_LUT9            ; /* 0x2524 */
    U_VPSS_LCHDR_TMAP_LUT10   VPSS_LCHDR_TMAP_LUT10          ; /* 0x2528 */
    U_VPSS_LCHDR_TMAP_LUT11   VPSS_LCHDR_TMAP_LUT11          ; /* 0x252c */
    U_VPSS_LCHDR_TMAP_LUT12   VPSS_LCHDR_TMAP_LUT12          ; /* 0x2530 */
    U_VPSS_LCHDR_TMAP_LUT13   VPSS_LCHDR_TMAP_LUT13          ; /* 0x2534 */
    U_VPSS_LCHDR_TMAP_LUT14   VPSS_LCHDR_TMAP_LUT14          ; /* 0x2538 */
    U_VPSS_LCHDR_TMAP_LUT15   VPSS_LCHDR_TMAP_LUT15          ; /* 0x253c */
    U_VPSS_LCHDR_TMAP_LUT16   VPSS_LCHDR_TMAP_LUT16          ; /* 0x2540 */
    U_VPSS_LCHDR_TMAP_LUT17   VPSS_LCHDR_TMAP_LUT17          ; /* 0x2544 */
    U_VPSS_LCHDR_TMAP_LUT18   VPSS_LCHDR_TMAP_LUT18          ; /* 0x2548 */
    U_VPSS_LCHDR_TMAP_LUT19   VPSS_LCHDR_TMAP_LUT19          ; /* 0x254c */
    U_VPSS_LCHDR_TMAP_LUT20   VPSS_LCHDR_TMAP_LUT20          ; /* 0x2550 */
    U_VPSS_LCHDR_TMAP_LUT21   VPSS_LCHDR_TMAP_LUT21          ; /* 0x2554 */
    U_VPSS_LCHDR_TMAP_LUT22   VPSS_LCHDR_TMAP_LUT22          ; /* 0x2558 */
    U_VPSS_LCHDR_TMAP_LUT23   VPSS_LCHDR_TMAP_LUT23          ; /* 0x255c */
    U_VPSS_LCHDR_TMAP_LUT24   VPSS_LCHDR_TMAP_LUT24          ; /* 0x2560 */
    U_VPSS_LCHDR_TMAP_LUT25   VPSS_LCHDR_TMAP_LUT25          ; /* 0x2564 */
    U_VPSS_LCHDR_TMAP_LUT26   VPSS_LCHDR_TMAP_LUT26          ; /* 0x2568 */
    U_VPSS_LCHDR_TMAP_LUT27   VPSS_LCHDR_TMAP_LUT27          ; /* 0x256c */
    U_VPSS_LCHDR_TMAP_LUT28   VPSS_LCHDR_TMAP_LUT28          ; /* 0x2570 */
    U_VPSS_LCHDR_TMAP_LUT29   VPSS_LCHDR_TMAP_LUT29          ; /* 0x2574 */
    U_VPSS_LCHDR_TMAP_LUT30   VPSS_LCHDR_TMAP_LUT30          ; /* 0x2578 */
    U_VPSS_LCHDR_TMAP_LUT31   VPSS_LCHDR_TMAP_LUT31          ; /* 0x257c */
    U_VPSS_LCHDR_SMAP_LUT0   VPSS_LCHDR_SMAP_LUT0            ; /* 0x2580 */
    U_VPSS_LCHDR_SMAP_LUT1   VPSS_LCHDR_SMAP_LUT1            ; /* 0x2584 */
    U_VPSS_LCHDR_SMAP_LUT2   VPSS_LCHDR_SMAP_LUT2            ; /* 0x2588 */
    U_VPSS_LCHDR_SMAP_LUT3   VPSS_LCHDR_SMAP_LUT3            ; /* 0x258c */
    U_VPSS_LCHDR_SMAP_LUT4   VPSS_LCHDR_SMAP_LUT4            ; /* 0x2590 */
    U_VPSS_LCHDR_SMAP_LUT5   VPSS_LCHDR_SMAP_LUT5            ; /* 0x2594 */
    U_VPSS_LCHDR_SMAP_LUT6   VPSS_LCHDR_SMAP_LUT6            ; /* 0x2598 */
    U_VPSS_LCHDR_SMAP_LUT7   VPSS_LCHDR_SMAP_LUT7            ; /* 0x259c */
    U_VPSS_LCHDR_SMAP_LUT8   VPSS_LCHDR_SMAP_LUT8            ; /* 0x25a0 */
    U_VPSS_LCHDR_SMAP_LUT9   VPSS_LCHDR_SMAP_LUT9            ; /* 0x25a4 */
    U_VPSS_LCHDR_SMAP_LUT10   VPSS_LCHDR_SMAP_LUT10          ; /* 0x25a8 */
    U_VPSS_LCHDR_SMAP_LUT11   VPSS_LCHDR_SMAP_LUT11          ; /* 0x25ac */
    U_VPSS_LCHDR_SMAP_LUT12   VPSS_LCHDR_SMAP_LUT12          ; /* 0x25b0 */
    U_VPSS_LCHDR_SMAP_LUT13   VPSS_LCHDR_SMAP_LUT13          ; /* 0x25b4 */
    U_VPSS_LCHDR_SMAP_LUT14   VPSS_LCHDR_SMAP_LUT14          ; /* 0x25b8 */
    U_VPSS_LCHDR_SMAP_LUT15   VPSS_LCHDR_SMAP_LUT15          ; /* 0x25bc */
    U_VPSS_LCHDR_SMAP_LUT16   VPSS_LCHDR_SMAP_LUT16          ; /* 0x25c0 */
    U_VPSS_LCHDR_SMAP_LUT17   VPSS_LCHDR_SMAP_LUT17          ; /* 0x25c4 */
    U_VPSS_LCHDR_SMAP_LUT18   VPSS_LCHDR_SMAP_LUT18          ; /* 0x25c8 */
    U_VPSS_LCHDR_SMAP_LUT19   VPSS_LCHDR_SMAP_LUT19          ; /* 0x25cc */
    U_VPSS_LCHDR_SMAP_LUT20   VPSS_LCHDR_SMAP_LUT20          ; /* 0x25d0 */
    U_VPSS_LCHDR_SMAP_LUT21   VPSS_LCHDR_SMAP_LUT21          ; /* 0x25d4 */
    U_VPSS_LCHDR_SMAP_LUT22   VPSS_LCHDR_SMAP_LUT22          ; /* 0x25d8 */
    U_VPSS_LCHDR_SMAP_LUT23   VPSS_LCHDR_SMAP_LUT23          ; /* 0x25dc */
    U_VPSS_LCHDR_SMAP_LUT24   VPSS_LCHDR_SMAP_LUT24          ; /* 0x25e0 */
    U_VPSS_LCHDR_SMAP_LUT25   VPSS_LCHDR_SMAP_LUT25          ; /* 0x25e4 */
    U_VPSS_LCHDR_SMAP_LUT26   VPSS_LCHDR_SMAP_LUT26          ; /* 0x25e8 */
    U_VPSS_LCHDR_SMAP_LUT27   VPSS_LCHDR_SMAP_LUT27          ; /* 0x25ec */
    U_VPSS_LCHDR_SMAP_LUT28   VPSS_LCHDR_SMAP_LUT28          ; /* 0x25f0 */
    U_VPSS_LCHDR_SMAP_LUT29   VPSS_LCHDR_SMAP_LUT29          ; /* 0x25f4 */
    U_VPSS_LCHDR_SMAP_LUT30   VPSS_LCHDR_SMAP_LUT30          ; /* 0x25f8 */
    U_VPSS_LCHDR_SMAP_LUT31   VPSS_LCHDR_SMAP_LUT31          ; /* 0x25fc */
    U_VPSS_LCHDR_SMAP_LUT32   VPSS_LCHDR_SMAP_LUT32          ; /* 0x2600 */
    unsigned int           reserved_26[1151]                     ; /* 0x2604~0x37fc */
    U_VPSS_TNR_CONTRL      VPSS_TNR_CONTRL                   ; /* 0x3800 */
    U_VPSS_TNR_MAMD_CTRL   VPSS_TNR_MAMD_CTRL                ; /* 0x3804 */
    U_VPSS_TNR_MAMD_GAIN   VPSS_TNR_MAMD_GAIN                ; /* 0x3808 */
    U_VPSS_TNR_MAND_CTRL   VPSS_TNR_MAND_CTRL                ; /* 0x380c */
    U_VPSS_TNR_MAND_THD    VPSS_TNR_MAND_THD                 ; /* 0x3810 */
    U_VPSS_TNR_MAME_CTRL   VPSS_TNR_MAME_CTRL                ; /* 0x3814 */
    U_VPSS_TNR_MAME_GAIN   VPSS_TNR_MAME_GAIN                ; /* 0x3818 */
    U_VPSS_TNR_MAME_STD_CORE   VPSS_TNR_MAME_STD_CORE        ; /* 0x381c */
    U_VPSS_TNR_MAME_STD_GAIN   VPSS_TNR_MAME_STD_GAIN        ; /* 0x3820 */
    U_VPSS_TNR_MAME_MV_THD   VPSS_TNR_MAME_MV_THD            ; /* 0x3824 */
    U_VPSS_TNR_MAMC_CBCR_UPEN   VPSS_TNR_MAMC_CBCR_UPEN      ; /* 0x3828 */
    U_VPSS_TNR_MAMC_CBCR_UPTHD1   VPSS_TNR_MAMC_CBCR_UPTHD1  ; /* 0x382c */
    U_VPSS_TNR_MAMC_CBCR_UPTHD2   VPSS_TNR_MAMC_CBCR_UPTHD2  ; /* 0x3830 */
    U_VPSS_TNR_MAMC_PRE_MAD   VPSS_TNR_MAMC_PRE_MAD          ; /* 0x3834 */
    U_VPSS_TNR_MAMC_MAP    VPSS_TNR_MAMC_MAP                 ; /* 0x3838 */
    U_VPSS_TNR_MAMC_SALTUS   VPSS_TNR_MAMC_SALTUS            ; /* 0x383c */
    U_VPSS_TNR_MAMC_MCADJ   VPSS_TNR_MAMC_MCADJ              ; /* 0x3840 */
    U_VPSS_TNR_FILR_MODE   VPSS_TNR_FILR_MODE                ; /* 0x3844 */
    U_VPSS_TNR_SCENE_CHANGE   VPSS_TNR_SCENE_CHANGE          ; /* 0x3848 */
    U_VPSS_TNR_CFG         VPSS_TNR_CFG                      ; /* 0x384c */
    U_VPSS_TNR_FLAT_INFO   VPSS_TNR_FLAT_INFO                ; /* 0x3850 */
    U_VPSS_TNR_YBLEND      VPSS_TNR_YBLEND                   ; /* 0x3854 */
    U_VPSS_TNR_CBLEND      VPSS_TNR_CBLEND                   ; /* 0x3858 */
    U_VPSS_TNR_DTBLEND     VPSS_TNR_DTBLEND                  ; /* 0x385c */
    unsigned int           reserved_27[40]                     ; /* 0x3860~0x38fc */
    U_VPSS_TNR_MEAN_MOTION_LUT0   VPSS_TNR_MEAN_MOTION_LUT0  ; /* 0x3900 */
    U_VPSS_TNR_MEAN_MOTION_LUT1   VPSS_TNR_MEAN_MOTION_LUT1  ; /* 0x3904 */
    U_VPSS_TNR_MEAN_MOTION_LUT2   VPSS_TNR_MEAN_MOTION_LUT2  ; /* 0x3908 */
    U_VPSS_TNR_MEAN_MOTION_LUT3   VPSS_TNR_MEAN_MOTION_LUT3  ; /* 0x390c */
    unsigned int           reserved_28[12]                     ; /* 0x3910~0x393c */
    U_VPSS_TNR_YBLENDING_LUT0   VPSS_TNR_YBLENDING_LUT0      ; /* 0x3940 */
    U_VPSS_TNR_YBLENDING_LUT1   VPSS_TNR_YBLENDING_LUT1      ; /* 0x3944 */
    U_VPSS_TNR_YBLENDING_LUT2   VPSS_TNR_YBLENDING_LUT2      ; /* 0x3948 */
    U_VPSS_TNR_YBLENDING_LUT3   VPSS_TNR_YBLENDING_LUT3      ; /* 0x394c */
    U_VPSS_TNR_YBLENDING_LUT4   VPSS_TNR_YBLENDING_LUT4      ; /* 0x3950 */
    U_VPSS_TNR_YBLENDING_LUT5   VPSS_TNR_YBLENDING_LUT5      ; /* 0x3954 */
    U_VPSS_TNR_YBLENDING_LUT6   VPSS_TNR_YBLENDING_LUT6      ; /* 0x3958 */
    U_VPSS_TNR_YBLENDING_LUT7   VPSS_TNR_YBLENDING_LUT7      ; /* 0x395c */
    U_VPSS_TNR_CBLENDING_LUT0   VPSS_TNR_CBLENDING_LUT0      ; /* 0x3960 */
    U_VPSS_TNR_CBLENDING_LUT1   VPSS_TNR_CBLENDING_LUT1      ; /* 0x3964 */
    U_VPSS_TNR_CBLENDING_LUT2   VPSS_TNR_CBLENDING_LUT2      ; /* 0x3968 */
    U_VPSS_TNR_CBLENDING_LUT3   VPSS_TNR_CBLENDING_LUT3      ; /* 0x396c */
    U_VPSS_TNR_CBLENDING_LUT4   VPSS_TNR_CBLENDING_LUT4      ; /* 0x3970 */
    U_VPSS_TNR_CBLENDING_LUT5   VPSS_TNR_CBLENDING_LUT5      ; /* 0x3974 */
    U_VPSS_TNR_CBLENDING_LUT6   VPSS_TNR_CBLENDING_LUT6      ; /* 0x3978 */
    U_VPSS_TNR_CBLENDING_LUT7   VPSS_TNR_CBLENDING_LUT7      ; /* 0x397c */
    unsigned int           reserved_29[416]                     ; /* 0x3980~0x3ffc */
    U_VPSS_DEBUG0          VPSS_DEBUG0                       ; /* 0x4000 */
    U_VPSS_DEBUG1          VPSS_DEBUG1                       ; /* 0x4004 */
    U_VPSS_DEBUG2          VPSS_DEBUG2                       ; /* 0x4008 */
    U_VPSS_DEBUG3          VPSS_DEBUG3                       ; /* 0x400c */
    U_VPSS_DEBUG4          VPSS_DEBUG4                       ; /* 0x4010 */
    U_VPSS_DEBUG5          VPSS_DEBUG5                       ; /* 0x4014 */
    U_VPSS_DEBUG6          VPSS_DEBUG6                       ; /* 0x4018 */
    U_VPSS_DEBUG7          VPSS_DEBUG7                       ; /* 0x401c */
    U_VPSS_DEBUG8          VPSS_DEBUG8                       ; /* 0x4020 */
    U_VPSS_DEBUG9          VPSS_DEBUG9                       ; /* 0x4024 */
    U_VPSS_DEBUG10         VPSS_DEBUG10                      ; /* 0x4028 */
    U_VPSS_DEBUG11         VPSS_DEBUG11                      ; /* 0x402c */
    U_VPSS_DEBUG12         VPSS_DEBUG12                      ; /* 0x4030 */
    U_VPSS_DEBUG13         VPSS_DEBUG13                      ; /* 0x4034 */
    U_VPSS_DEBUG14         VPSS_DEBUG14                      ; /* 0x4038 */
    U_VPSS_DEBUG15         VPSS_DEBUG15                      ; /* 0x403c */
    U_VPSS_DEBUG16         VPSS_DEBUG16                      ; /* 0x4040 */
    U_VPSS_DEBUG17         VPSS_DEBUG17                      ; /* 0x4044 */
    U_VPSS_DEBUG18         VPSS_DEBUG18                      ; /* 0x4048 */
    U_VPSS_DEBUG19         VPSS_DEBUG19                      ; /* 0x404c */
    U_VPSS_DEBUG20         VPSS_DEBUG20                      ; /* 0x4050 */
    U_VPSS_DEBUG21         VPSS_DEBUG21                      ; /* 0x4054 */
    U_VPSS_DEBUG22         VPSS_DEBUG22                      ; /* 0x4058 */
    U_VPSS_DEBUG23         VPSS_DEBUG23                      ; /* 0x405c */
    U_VPSS_DEBUG24         VPSS_DEBUG24                      ; /* 0x4060 */
    U_VPSS_DEBUG25         VPSS_DEBUG25                      ; /* 0x4064 */
    U_VPSS_DEBUG26         VPSS_DEBUG26                      ; /* 0x4068 */
    U_VPSS_DEBUG27         VPSS_DEBUG27                      ; /* 0x406c */
    U_VPSS_DEBUG28         VPSS_DEBUG28                      ; /* 0x4070 */
    U_VPSS_DEBUG29         VPSS_DEBUG29                      ; /* 0x4074 */
    U_VPSS_DEBUG30         VPSS_DEBUG30                      ; /* 0x4078 */
    U_VPSS_DEBUG31         VPSS_DEBUG31                      ; /* 0x407c */
    U_VPSS_DEBUG32         VPSS_DEBUG32                      ; /* 0x4080 */
    U_VPSS_DEBUG33         VPSS_DEBUG33                      ; /* 0x4084 */
    U_VPSS_DEBUG34         VPSS_DEBUG34                      ; /* 0x4088 */
    U_VPSS_DEBUG35         VPSS_DEBUG35                      ; /* 0x408c */
    U_VPSS_DEBUG36         VPSS_DEBUG36                      ; /* 0x4090 */
    U_VPSS_DEBUG37         VPSS_DEBUG37                      ; /* 0x4094 */
    U_VPSS_DEBUG38         VPSS_DEBUG38                      ; /* 0x4098 */
    U_VPSS_DEBUG39         VPSS_DEBUG39                      ; /* 0x409c */
    U_VPSS_DEBUG40         VPSS_DEBUG40                      ; /* 0x40a0 */
    U_VPSS_DEBUG41         VPSS_DEBUG41                      ; /* 0x40a4 */
    U_VPSS_DEBUG42         VPSS_DEBUG42                      ; /* 0x40a8 */
    U_VPSS_DEBUG43         VPSS_DEBUG43                      ; /* 0x40ac */
    unsigned int           reserved_30[980]                     ; /* 0x40b0~0x4ffc */
    U_VPSS_CHN_CFG_CTRL    VPSS_CHN_CFG_CTRL                 ; /* 0x5000 */
    unsigned int           reserved_31[3]                     ; /* 0x5004~0x500c */
    U_VPSS_STT_W_ADDR_LOW   VPSS_STT_W_ADDR_LOW              ; /* 0x5010 */
    unsigned int           reserved_32[4]                     ; /* 0x5014~0x5020 */
    U_VPSS_CF_RTUNL_CTRL   VPSS_CF_RTUNL_CTRL                ; /* 0x5024 */
    unsigned int           reserved_33                     ; /* 0x5028 */
    U_VPSS_CF_RTUNL_ADDR_LOW   VPSS_CF_RTUNL_ADDR_LOW        ; /* 0x502c */
    U_VPSS_OUT0_WTUNL_CTRL   VPSS_OUT0_WTUNL_CTRL            ; /* 0x5030 */
    U_VPSS_OUT0_WTUNL_THD   VPSS_OUT0_WTUNL_THD              ; /* 0x5034 */
    unsigned int           reserved_34                     ; /* 0x5038 */
    U_VPSS_OUT0_WTUNL_ADDR_LOW   VPSS_OUT0_WTUNL_ADDR_LOW    ; /* 0x503c */
    U_VPSS_TRANS_INFO      VPSS_TRANS_INFO                   ; /* 0x5040 */
    U_VPSS_TRANS_SRC_ADDR   VPSS_TRANS_SRC_ADDR              ; /* 0x5044 */
    U_VPSS_TRANS_DES_ADDR   VPSS_TRANS_DES_ADDR              ; /* 0x5048 */
    unsigned int           reserved_35                     ; /* 0x504c */
    U_VPSS_TESTPATTERN     VPSS_TESTPATTERN                  ; /* 0x5050 */
    unsigned int           reserved_36[3]                     ; /* 0x5054~0x505c */
    U_VPSS_DCMP_STATUS     VPSS_DCMP_STATUS                  ; /* 0x5060 */
    U_VPSS_OUT0Y_CHKSUM    VPSS_OUT0Y_CHKSUM                 ; /* 0x5064 */
    U_VPSS_OUT0C_CHKSUM    VPSS_OUT0C_CHKSUM                 ; /* 0x5068 */
    unsigned int           reserved_37[5]                     ; /* 0x506c~0x507c */
    U_VPSS_CF_CTRL         VPSS_CF_CTRL                      ; /* 0x5080 */
    unsigned int           reserved_38                     ; /* 0x5084 */
    U_VPSS_CF_SIZE         VPSS_CF_SIZE                      ; /* 0x5088 */
    U_VPSS_CF_OFFSET       VPSS_CF_OFFSET                    ; /* 0x508c */
    unsigned int           reserved_39                     ; /* 0x5090 */
    U_VPSS_CFY_ADDR_LOW    VPSS_CFY_ADDR_LOW                 ; /* 0x5094 */
    unsigned int           reserved_40                     ; /* 0x5098 */
    U_VPSS_CFC_ADDR_LOW    VPSS_CFC_ADDR_LOW                 ; /* 0x509c */
    unsigned int           reserved_41[3]                     ; /* 0x50a0~0x50a8 */
    U_VPSS_CFY_HEAD_TOP_ADDR_LOW   VPSS_CFY_HEAD_TOP_ADDR_LOW ; /* 0x50ac */
    unsigned int           reserved_42                     ; /* 0x50b0 */
    U_VPSS_CFC_HEAD_TOP_ADDR_LOW   VPSS_CFC_HEAD_TOP_ADDR_LOW ; /* 0x50b4 */
    unsigned int           reserved_43[4]                     ; /* 0x50b8~0x50c4 */
    U_VPSS_CF_STRIDE       VPSS_CF_STRIDE                    ; /* 0x50c8 */
    U_VPSS_CF_HEAD_STRIDE   VPSS_CF_HEAD_STRIDE              ; /* 0x50cc */
    unsigned int           reserved_44                     ; /* 0x50d0 */
    U_VPSS_CFY_2B_ADDR_LOW   VPSS_CFY_2B_ADDR_LOW            ; /* 0x50d4 */
    unsigned int           reserved_45                     ; /* 0x50d8 */
    U_VPSS_CFC_2B_ADDR_LOW   VPSS_CFC_2B_ADDR_LOW            ; /* 0x50dc */
    U_VPSS_CF_2B_STRIDE    VPSS_CF_2B_STRIDE                 ; /* 0x50e0 */
    U_VPSS_CF_MUTE_VAL     VPSS_CF_MUTE_VAL                  ; /* 0x50e4 */
    unsigned int           reserved_46[6]                     ; /* 0x50e8~0x50fc */
    U_VPSS_P1_CTRL         VPSS_P1_CTRL                      ; /* 0x5100 */
    unsigned int           reserved_47[4]                     ; /* 0x5104~0x5110 */
    U_VPSS_P1Y_ADDR_LOW    VPSS_P1Y_ADDR_LOW                 ; /* 0x5114 */
    unsigned int           reserved_48                     ; /* 0x5118 */
    U_VPSS_P1C_ADDR_LOW    VPSS_P1C_ADDR_LOW                 ; /* 0x511c */
    unsigned int           reserved_49[10]                     ; /* 0x5120~0x5144 */
    U_VPSS_P1_STRIDE       VPSS_P1_STRIDE                    ; /* 0x5148 */
    unsigned int           reserved_50[6]                     ; /* 0x514c~0x5160 */
    U_VPSS_P1_MUTE_VAL     VPSS_P1_MUTE_VAL                  ; /* 0x5164 */
    unsigned int           reserved_51[6]                     ; /* 0x5168~0x517c */
    U_VPSS_P2_CTRL         VPSS_P2_CTRL                      ; /* 0x5180 */
    unsigned int           reserved_52[4]                     ; /* 0x5184~0x5190 */
    U_VPSS_P2Y_ADDR_LOW    VPSS_P2Y_ADDR_LOW                 ; /* 0x5194 */
    unsigned int           reserved_53                     ; /* 0x5198 */
    U_VPSS_P2C_ADDR_LOW    VPSS_P2C_ADDR_LOW                 ; /* 0x519c */
    unsigned int           reserved_54[10]                     ; /* 0x51a0~0x51c4 */
    U_VPSS_P2_STRIDE       VPSS_P2_STRIDE                    ; /* 0x51c8 */
    unsigned int           reserved_55[6]                     ; /* 0x51cc~0x51e0 */
    U_VPSS_P2_MUTE_VAL     VPSS_P2_MUTE_VAL                  ; /* 0x51e4 */
    unsigned int           reserved_56[6]                     ; /* 0x51e8~0x51fc */
    U_VPSS_P3_CTRL         VPSS_P3_CTRL                      ; /* 0x5200 */
    unsigned int           reserved_57[4]                     ; /* 0x5204~0x5210 */
    U_VPSS_P3Y_ADDR_LOW    VPSS_P3Y_ADDR_LOW                 ; /* 0x5214 */
    unsigned int           reserved_58                     ; /* 0x5218 */
    U_VPSS_P3C_ADDR_LOW    VPSS_P3C_ADDR_LOW                 ; /* 0x521c */
    unsigned int           reserved_59[10]                     ; /* 0x5220~0x5244 */
    U_VPSS_P3_STRIDE       VPSS_P3_STRIDE                    ; /* 0x5248 */
    unsigned int           reserved_60[6]                     ; /* 0x524c~0x5260 */
    U_VPSS_P3_MUTE_VAL     VPSS_P3_MUTE_VAL                  ; /* 0x5264 */
    unsigned int           reserved_61[6]                     ; /* 0x5268~0x527c */
    U_VPSS_P3I_CTRL        VPSS_P3I_CTRL                     ; /* 0x5280 */
    unsigned int           reserved_62[4]                     ; /* 0x5284~0x5290 */
    U_VPSS_P3IY_ADDR_LOW   VPSS_P3IY_ADDR_LOW                ; /* 0x5294 */
    unsigned int           reserved_63                     ; /* 0x5298 */
    U_VPSS_P3IC_ADDR_LOW   VPSS_P3IC_ADDR_LOW                ; /* 0x529c */
    unsigned int           reserved_64[10]                     ; /* 0x52a0~0x52c4 */
    U_VPSS_P3I_STRIDE      VPSS_P3I_STRIDE                   ; /* 0x52c8 */
    unsigned int           reserved_65[6]                     ; /* 0x52cc~0x52e0 */
    U_VPSS_P3I_MUTE_VAL    VPSS_P3I_MUTE_VAL                 ; /* 0x52e4 */
    unsigned int           reserved_66[6]                     ; /* 0x52e8~0x52fc */
    U_VPSS_NR_RMAD_CTRL    VPSS_NR_RMAD_CTRL                 ; /* 0x5300 */
    U_VPSS_NR_RMAD_SIZE    VPSS_NR_RMAD_SIZE                 ; /* 0x5304 */
    unsigned int           reserved_67                     ; /* 0x5308 */
    U_VPSS_NR_RMAD_ADDR_LOW   VPSS_NR_RMAD_ADDR_LOW          ; /* 0x530c */
    U_VPSS_NR_RMAD_STRIDE   VPSS_NR_RMAD_STRIDE              ; /* 0x5310 */
    U_VPSS_NR_RMAD_MUTE_VAL0   VPSS_NR_RMAD_MUTE_VAL0        ; /* 0x5314 */
    unsigned int           reserved_68[2]                     ; /* 0x5318~0x531c */
    U_VPSS_DI_RST_CTRL     VPSS_DI_RST_CTRL                  ; /* 0x5320 */
    U_VPSS_DI_RST_SIZE     VPSS_DI_RST_SIZE                  ; /* 0x5324 */
    unsigned int           reserved_69                     ; /* 0x5328 */
    U_VPSS_DI_RST_ADDR_LOW   VPSS_DI_RST_ADDR_LOW            ; /* 0x532c */
    U_VPSS_DI_RST_STRIDE   VPSS_DI_RST_STRIDE                ; /* 0x5330 */
    U_VPSS_DI_RST_MUTE_VAL0   VPSS_DI_RST_MUTE_VAL0          ; /* 0x5334 */
    unsigned int           reserved_70[2]                     ; /* 0x5338~0x533c */
    U_VPSS_DI_RST_CNT_CTRL   VPSS_DI_RST_CNT_CTRL            ; /* 0x5340 */
    U_VPSS_DI_RST_CNT_SIZE   VPSS_DI_RST_CNT_SIZE            ; /* 0x5344 */
    unsigned int           reserved_71                     ; /* 0x5348 */
    U_VPSS_DI_RST_CNT_ADDR_LOW   VPSS_DI_RST_CNT_ADDR_LOW    ; /* 0x534c */
    U_VPSS_DI_RST_CNT_STRIDE   VPSS_DI_RST_CNT_STRIDE        ; /* 0x5350 */
    U_VPSS_DI_RST_CNT_MUTE_VAL0   VPSS_DI_RST_CNT_MUTE_VAL0  ; /* 0x5354 */
    unsigned int           reserved_72[2]                     ; /* 0x5358~0x535c */
    U_VPSS_P3MT_CTRL       VPSS_P3MT_CTRL                    ; /* 0x5360 */
    U_VPSS_P3MT_SIZE       VPSS_P3MT_SIZE                    ; /* 0x5364 */
    unsigned int           reserved_73                     ; /* 0x5368 */
    U_VPSS_P3MT_ADDR_LOW   VPSS_P3MT_ADDR_LOW                ; /* 0x536c */
    U_VPSS_P3MT_STRIDE     VPSS_P3MT_STRIDE                  ; /* 0x5370 */
    U_VPSS_P3MT_MUTE_VAL0   VPSS_P3MT_MUTE_VAL0              ; /* 0x5374 */
    unsigned int           reserved_74[2]                     ; /* 0x5378~0x537c */
    U_VPSS_P2MV_CTRL       VPSS_P2MV_CTRL                    ; /* 0x5380 */
    U_VPSS_P2MV_SIZE       VPSS_P2MV_SIZE                    ; /* 0x5384 */
    unsigned int           reserved_75                     ; /* 0x5388 */
    U_VPSS_P2MV_ADDR_LOW   VPSS_P2MV_ADDR_LOW                ; /* 0x538c */
    U_VPSS_P2MV_STRIDE     VPSS_P2MV_STRIDE                  ; /* 0x5390 */
    U_VPSS_P2MV_MUTE_VAL0   VPSS_P2MV_MUTE_VAL0              ; /* 0x5394 */
    unsigned int           reserved_76[2]                     ; /* 0x5398~0x539c */
    U_VPSS_P3MV_CTRL       VPSS_P3MV_CTRL                    ; /* 0x53a0 */
    unsigned int           reserved_77[2]                     ; /* 0x53a4~0x53a8 */
    U_VPSS_P3MV_ADDR_LOW   VPSS_P3MV_ADDR_LOW                ; /* 0x53ac */
    U_VPSS_P3MV_STRIDE     VPSS_P3MV_STRIDE                  ; /* 0x53b0 */
    U_VPSS_P3MV_MUTE_VAL0   VPSS_P3MV_MUTE_VAL0              ; /* 0x53b4 */
    unsigned int           reserved_78[2]                     ; /* 0x53b8~0x53bc */
    U_VPSS_P1RGMV_CTRL     VPSS_P1RGMV_CTRL                  ; /* 0x53c0 */
    U_VPSS_P1RGMV_SIZE     VPSS_P1RGMV_SIZE                  ; /* 0x53c4 */
    unsigned int           reserved_79                     ; /* 0x53c8 */
    U_VPSS_P1RGMV_ADDR_LOW   VPSS_P1RGMV_ADDR_LOW            ; /* 0x53cc */
    U_VPSS_P1RGMV_STRIDE   VPSS_P1RGMV_STRIDE                ; /* 0x53d0 */
    U_VPSS_P1RGMV_MUTE_VAL0   VPSS_P1RGMV_MUTE_VAL0          ; /* 0x53d4 */
    U_VPSS_P1RGMV_MUTE_VAL1   VPSS_P1RGMV_MUTE_VAL1          ; /* 0x53d8 */
    unsigned int           reserved_80                     ; /* 0x53dc */
    U_VPSS_P2RGMV_CTRL     VPSS_P2RGMV_CTRL                  ; /* 0x53e0 */
    unsigned int           reserved_81[2]                     ; /* 0x53e4~0x53e8 */
    U_VPSS_P2RGMV_ADDR_LOW   VPSS_P2RGMV_ADDR_LOW            ; /* 0x53ec */
    U_VPSS_P2RGMV_STRIDE   VPSS_P2RGMV_STRIDE                ; /* 0x53f0 */
    U_VPSS_P2RGMV_MUTE_VAL0   VPSS_P2RGMV_MUTE_VAL0          ; /* 0x53f4 */
    U_VPSS_P2RGMV_MUTE_VAL1   VPSS_P2RGMV_MUTE_VAL1          ; /* 0x53f8 */
    unsigned int           reserved_82                     ; /* 0x53fc */
    U_VPSS_RPRJH_CTRL      VPSS_RPRJH_CTRL                   ; /* 0x5400 */
    U_VPSS_RPRJH_SIZE      VPSS_RPRJH_SIZE                   ; /* 0x5404 */
    unsigned int           reserved_83                     ; /* 0x5408 */
    U_VPSS_RPRJH_ADDR_LOW   VPSS_RPRJH_ADDR_LOW              ; /* 0x540c */
    U_VPSS_RPRJH_STRIDE    VPSS_RPRJH_STRIDE                 ; /* 0x5410 */
    U_VPSS_RPRJH_MUTE_VAL0   VPSS_RPRJH_MUTE_VAL0            ; /* 0x5414 */
    unsigned int           reserved_84[2]                     ; /* 0x5418~0x541c */
    U_VPSS_RPRJV_CTRL      VPSS_RPRJV_CTRL                   ; /* 0x5420 */
    U_VPSS_RPRJV_SIZE      VPSS_RPRJV_SIZE                   ; /* 0x5424 */
    unsigned int           reserved_85                     ; /* 0x5428 */
    U_VPSS_RPRJV_ADDR_LOW   VPSS_RPRJV_ADDR_LOW              ; /* 0x542c */
    U_VPSS_RPRJV_STRIDE    VPSS_RPRJV_STRIDE                 ; /* 0x5430 */
    U_VPSS_RPRJV_MUTE_VAL0   VPSS_RPRJV_MUTE_VAL0            ; /* 0x5434 */
    unsigned int           reserved_86[242]                     ; /* 0x5438~0x57fc */
    U_VPSS_OUT0_CTRL       VPSS_OUT0_CTRL                    ; /* 0x5800 */
    U_VPSS_OUT0_OFFSET     VPSS_OUT0_OFFSET                  ; /* 0x5804 */
    unsigned int           reserved_87                     ; /* 0x5808 */
    U_VPSS_OUT0Y_ADDR_LOW   VPSS_OUT0Y_ADDR_LOW              ; /* 0x580c */
    unsigned int           reserved_88                     ; /* 0x5810 */
    U_VPSS_OUT0C_ADDR_LOW   VPSS_OUT0C_ADDR_LOW              ; /* 0x5814 */
    U_VPSS_OUT0_STRIDE     VPSS_OUT0_STRIDE                  ; /* 0x5818 */
    unsigned int           reserved_89[5]                     ; /* 0x581c~0x582c */
    U_VPSS_OUT0_SIZE       VPSS_OUT0_SIZE                    ; /* 0x5830 */
    unsigned int           reserved_90                     ; /* 0x5834 */
    U_VPSS_OUT0_FINFO_LOW   VPSS_OUT0_FINFO_LOW              ; /* 0x5838 */
    U_VPSS_OUT0_MUTE_VAL   VPSS_OUT0_MUTE_VAL                ; /* 0x583c */
    U_VPSS_NR_RFR_CTRL     VPSS_NR_RFR_CTRL                  ; /* 0x5840 */
    unsigned int           reserved_91[2]                     ; /* 0x5844~0x5848 */
    U_VPSS_NR_RFRY_ADDR_LOW   VPSS_NR_RFRY_ADDR_LOW          ; /* 0x584c */
    unsigned int           reserved_92                     ; /* 0x5850 */
    U_VPSS_NR_RFRC_ADDR_LOW   VPSS_NR_RFRC_ADDR_LOW          ; /* 0x5854 */
    U_VPSS_NR_RFR_STRIDE   VPSS_NR_RFR_STRIDE                ; /* 0x5858 */
    unsigned int           reserved_93[5]                     ; /* 0x585c~0x586c */
    U_VPSS_NR_RFR_SIZE     VPSS_NR_RFR_SIZE                  ; /* 0x5870 */
    unsigned int           reserved_94                     ; /* 0x5874 */
    U_VPSS_NR_RFR_FINFO_LOW   VPSS_NR_RFR_FINFO_LOW          ; /* 0x5878 */
    U_VPSS_NR_RFR_MUTE_VAL   VPSS_NR_RFR_MUTE_VAL            ; /* 0x587c */
    U_VPSS_DI_RFR_CTRL     VPSS_DI_RFR_CTRL                  ; /* 0x5880 */
    unsigned int           reserved_95[2]                     ; /* 0x5884~0x5888 */
    U_VPSS_DI_RFRY_ADDR_LOW   VPSS_DI_RFRY_ADDR_LOW          ; /* 0x588c */
    unsigned int           reserved_96                     ; /* 0x5890 */
    U_VPSS_DI_RFRC_ADDR_LOW   VPSS_DI_RFRC_ADDR_LOW          ; /* 0x5894 */
    U_VPSS_DI_RFR_STRIDE   VPSS_DI_RFR_STRIDE                ; /* 0x5898 */
    unsigned int           reserved_97[5]                     ; /* 0x589c~0x58ac */
    U_VPSS_DI_RFR_SIZE     VPSS_DI_RFR_SIZE                  ; /* 0x58b0 */
    unsigned int           reserved_98                     ; /* 0x58b4 */
    U_VPSS_DI_RFR_FINFO_LOW   VPSS_DI_RFR_FINFO_LOW          ; /* 0x58b8 */
    U_VPSS_DI_RFR_MUTE_VAL   VPSS_DI_RFR_MUTE_VAL            ; /* 0x58bc */
    U_VPSS_NR_WMAD_CTRL    VPSS_NR_WMAD_CTRL                 ; /* 0x58c0 */
    unsigned int           reserved_99                     ; /* 0x58c4 */
    U_VPSS_NR_WMAD_ADDR_LOW   VPSS_NR_WMAD_ADDR_LOW          ; /* 0x58c8 */
    U_VPSS_NR_WMAD_STRIDE   VPSS_NR_WMAD_STRIDE              ; /* 0x58cc */
    U_VPSS_NR_WMAD_SIZE    VPSS_NR_WMAD_SIZE                 ; /* 0x58d0 */
    U_VPSS_NR_WMAD_MUTE_VAL0   VPSS_NR_WMAD_MUTE_VAL0        ; /* 0x58d4 */
    unsigned int           reserved_100[2]                     ; /* 0x58d8~0x58dc */
    U_VPSS_DI_WST_CTRL     VPSS_DI_WST_CTRL                  ; /* 0x58e0 */
    unsigned int           reserved_101                     ; /* 0x58e4 */
    U_VPSS_DI_WST_ADDR_LOW   VPSS_DI_WST_ADDR_LOW            ; /* 0x58e8 */
    U_VPSS_DI_WST_STRIDE   VPSS_DI_WST_STRIDE                ; /* 0x58ec */
    U_VPSS_DI_WST_SIZE     VPSS_DI_WST_SIZE                  ; /* 0x58f0 */
    U_VPSS_DI_WST_MUTE_VAL0   VPSS_DI_WST_MUTE_VAL0          ; /* 0x58f4 */
    unsigned int           reserved_102[2]                     ; /* 0x58f8~0x58fc */
    U_VPSS_DI_WST_CNT_CTRL   VPSS_DI_WST_CNT_CTRL            ; /* 0x5900 */
    unsigned int           reserved_103                     ; /* 0x5904 */
    U_VPSS_DI_WST_CNT_ADDR_LOW   VPSS_DI_WST_CNT_ADDR_LOW    ; /* 0x5908 */
    U_VPSS_DI_WST_CNT_STRIDE   VPSS_DI_WST_CNT_STRIDE        ; /* 0x590c */
    U_VPSS_DI_WST_CNT_SIZE   VPSS_DI_WST_CNT_SIZE            ; /* 0x5910 */
    U_VPSS_DI_WST_CNT_MUTE_VAL0   VPSS_DI_WST_CNT_MUTE_VAL0  ; /* 0x5914 */
    unsigned int           reserved_104[2]                     ; /* 0x5918~0x591c */
    U_VPSS_P2MT_CTRL       VPSS_P2MT_CTRL                    ; /* 0x5920 */
    unsigned int           reserved_105                     ; /* 0x5924 */
    U_VPSS_P2MT_ADDR_LOW   VPSS_P2MT_ADDR_LOW                ; /* 0x5928 */
    U_VPSS_P2MT_STRIDE     VPSS_P2MT_STRIDE                  ; /* 0x592c */
    U_VPSS_P2MT_SIZE       VPSS_P2MT_SIZE                    ; /* 0x5930 */
    U_VPSS_P2MT_MUTE_VAL0   VPSS_P2MT_MUTE_VAL0              ; /* 0x5934 */
    unsigned int           reserved_106[2]                     ; /* 0x5938~0x593c */
    U_VPSS_CFMV_CTRL       VPSS_CFMV_CTRL                    ; /* 0x5940 */
    unsigned int           reserved_107                     ; /* 0x5944 */
    U_VPSS_CFMV_ADDR_LOW   VPSS_CFMV_ADDR_LOW                ; /* 0x5948 */
    U_VPSS_CFMV_STRIDE     VPSS_CFMV_STRIDE                  ; /* 0x594c */
    U_VPSS_CFMV_SIZE       VPSS_CFMV_SIZE                    ; /* 0x5950 */
    U_VPSS_CFMV_MUTE_VAL0   VPSS_CFMV_MUTE_VAL0              ; /* 0x5954 */
    unsigned int           reserved_108[2]                     ; /* 0x5958~0x595c */
    U_VPSS_CFRGMV_CTRL     VPSS_CFRGMV_CTRL                  ; /* 0x5960 */
    unsigned int           reserved_109                     ; /* 0x5964 */
    U_VPSS_CFRGMV_ADDR_LOW   VPSS_CFRGMV_ADDR_LOW            ; /* 0x5968 */
    U_VPSS_CFRGMV_STRIDE   VPSS_CFRGMV_STRIDE                ; /* 0x596c */
    U_VPSS_CFRGMV_SIZE     VPSS_CFRGMV_SIZE                  ; /* 0x5970 */
    U_VPSS_CFRGMV_MUTE_VAL0   VPSS_CFRGMV_MUTE_VAL0          ; /* 0x5974 */
    U_VPSS_CFRGMV_MUTE_VAL1   VPSS_CFRGMV_MUTE_VAL1          ; /* 0x5978 */
    unsigned int           reserved_110                     ; /* 0x597c */
    U_VPSS_WPRJH_CTRL      VPSS_WPRJH_CTRL                   ; /* 0x5980 */
    unsigned int           reserved_111                     ; /* 0x5984 */
    U_VPSS_WPRJH_ADDR_LOW   VPSS_WPRJH_ADDR_LOW              ; /* 0x5988 */
    U_VPSS_WPRJH_STRIDE    VPSS_WPRJH_STRIDE                 ; /* 0x598c */
    U_VPSS_WPRJH_SIZE      VPSS_WPRJH_SIZE                   ; /* 0x5990 */
    U_VPSS_WPRJH_MUTE_VAL0   VPSS_WPRJH_MUTE_VAL0            ; /* 0x5994 */
    unsigned int           reserved_112[2]                     ; /* 0x5998~0x599c */
    U_VPSS_WPRJV_CTRL      VPSS_WPRJV_CTRL                   ; /* 0x59a0 */
    unsigned int           reserved_113                     ; /* 0x59a4 */
    U_VPSS_WPRJV_ADDR_LOW   VPSS_WPRJV_ADDR_LOW              ; /* 0x59a8 */
    U_VPSS_WPRJV_STRIDE    VPSS_WPRJV_STRIDE                 ; /* 0x59ac */
    U_VPSS_WPRJV_SIZE      VPSS_WPRJV_SIZE                   ; /* 0x59b0 */
    U_VPSS_WPRJV_MUTE_VAL0   VPSS_WPRJV_MUTE_VAL0            ; /* 0x59b4 */
    unsigned int           reserved_114[9618]                     ; /* 0x59b8~0xeffc */
    U_VPSS0_SMMU_SCR       VPSS0_SMMU_SCR                    ; /* 0xf000 */
    unsigned int           reserved_115                     ; /* 0xf004 */
    U_VPSS0_SMMU_LP_CTRL   VPSS0_SMMU_LP_CTRL                ; /* 0xf008 */
    U_VPSS0_SMMU_MEM_SPEEDCTRL   VPSS0_SMMU_MEM_SPEEDCTRL    ; /* 0xf00c */
    U_VPSS0_SMMU_INTMASK_S   VPSS0_SMMU_INTMASK_S            ; /* 0xf010 */
    U_VPSS0_SMMU_INTRAW_S   VPSS0_SMMU_INTRAW_S              ; /* 0xf014 */
    U_VPSS0_SMMU_INTSTAT_S   VPSS0_SMMU_INTSTAT_S            ; /* 0xf018 */
    U_VPSS0_SMMU_INTCLR_S   VPSS0_SMMU_INTCLR_S              ; /* 0xf01c */
    U_VPSS0_SMMU_INTMASK_NS   VPSS0_SMMU_INTMASK_NS          ; /* 0xf020 */
    U_VPSS0_SMMU_INTRAW_NS   VPSS0_SMMU_INTRAW_NS            ; /* 0xf024 */
    U_VPSS0_SMMU_INTSTAT_NS   VPSS0_SMMU_INTSTAT_NS          ; /* 0xf028 */
    U_VPSS0_SMMU_INTCLR_NS   VPSS0_SMMU_INTCLR_NS            ; /* 0xf02c */
    unsigned int           reserved_116[118]                     ; /* 0xf030~0xf204 */
    U_VPSS0_SMMU_SCB_TTBR   VPSS0_SMMU_SCB_TTBR              ; /* 0xf208 */
    U_VPSS0_SMMU_CB_TTBR   VPSS0_SMMU_CB_TTBR                ; /* 0xf20c */
    unsigned int           reserved_117[56]                     ; /* 0xf210~0xf2ec */
    U_VPSS0_SMMU_ERR_RDADDR_S   VPSS0_SMMU_ERR_RDADDR_S      ; /* 0xf2f0 */
    U_VPSS0_SMMU_ERR_WRADDR_S   VPSS0_SMMU_ERR_WRADDR_S      ; /* 0xf2f4 */
    unsigned int           reserved_118[3]                     ; /* 0xf2f8~0xf300 */
    U_VPSS0_SMMU_ERR_RDADDR_NS   VPSS0_SMMU_ERR_RDADDR_NS    ; /* 0xf304 */
    U_VPSS0_SMMU_ERR_WRADDR_NS   VPSS0_SMMU_ERR_WRADDR_NS    ; /* 0xf308 */
    unsigned int           reserved_119                     ; /* 0xf30c */
    U_VPSS0_SMMU_FAULT_ADDR_PTW_S   VPSS0_SMMU_FAULT_ADDR_PTW_S ; /* 0xf310 */
    U_VPSS0_SMMU_FAULT_ID_PTW_S   VPSS0_SMMU_FAULT_ID_PTW_S  ; /* 0xf314 */
    unsigned int           reserved_120[2]                     ; /* 0xf318~0xf31c */
    U_VPSS0_SMMU_FAULT_ADDR_PTW_NS   VPSS0_SMMU_FAULT_ADDR_PTW_NS ; /* 0xf320 */
    U_VPSS0_SMMU_FAULT_ID_PTW_NS   VPSS0_SMMU_FAULT_ID_PTW_NS ; /* 0xf324 */
    U_VPSS0_SMMU_FAULT_PTW_NUM   VPSS0_SMMU_FAULT_PTW_NUM    ; /* 0xf328 */
    unsigned int           reserved_121                     ; /* 0xf32c */
    U_VPSS0_SMMU_FAULT_ADDR_WR_S   VPSS0_SMMU_FAULT_ADDR_WR_S ; /* 0xf330 */
    U_VPSS0_SMMU_FAULT_TLB_WR_S   VPSS0_SMMU_FAULT_TLB_WR_S  ; /* 0xf334 */
    U_VPSS0_SMMU_FAULT_ID_WR_S   VPSS0_SMMU_FAULT_ID_WR_S    ; /* 0xf338 */
    unsigned int           reserved_122                     ; /* 0xf33c */
    U_VPSS0_SMMU_FAULT_ADDR_WR_NS   VPSS0_SMMU_FAULT_ADDR_WR_NS ; /* 0xf340 */
    U_VPSS0_SMMU_FAULT_TLB_WR_NS   VPSS0_SMMU_FAULT_TLB_WR_NS ; /* 0xf344 */
    U_VPSS0_SMMU_FAULT_ID_WR_NS   VPSS0_SMMU_FAULT_ID_WR_NS  ; /* 0xf348 */
    unsigned int           reserved_123                     ; /* 0xf34c */
    U_VPSS0_SMMU_FAULT_ADDR_RD_S   VPSS0_SMMU_FAULT_ADDR_RD_S ; /* 0xf350 */
    U_VPSS0_SMMU_FAULT_TLB_RD_S   VPSS0_SMMU_FAULT_TLB_RD_S  ; /* 0xf354 */
    U_VPSS0_SMMU_FAULT_ID_RD_S   VPSS0_SMMU_FAULT_ID_RD_S    ; /* 0xf358 */
    unsigned int           reserved_124                     ; /* 0xf35c */
    U_VPSS0_SMMU_FAULT_ADDR_RD_NS   VPSS0_SMMU_FAULT_ADDR_RD_NS ; /* 0xf360 */
    U_VPSS0_SMMU_FAULT_TLB_RD_NS   VPSS0_SMMU_FAULT_TLB_RD_NS ; /* 0xf364 */
    U_VPSS0_SMMU_FAULT_ID_RD_NS   VPSS0_SMMU_FAULT_ID_RD_NS  ; /* 0xf368 */
    U_VPSS0_SMMU_FAULT_TBU_INFO   VPSS0_SMMU_FAULT_TBU_INFO  ; /* 0xf36c */
    U_VPSS0_SMMU_FAULT_TBU_DBG   VPSS0_SMMU_FAULT_TBU_DBG    ; /* 0xf370 */
    U_VPSS0_SMMU_PREF_BUFFER_EMPTY   VPSS0_SMMU_PREF_BUFFER_EMPTY ; /* 0xf374 */
    U_VPSS0_SMMU_PTWQ_IDLE   VPSS0_SMMU_PTWQ_IDLE            ; /* 0xf378 */
    U_VPSS0_SMMU_RESET_STATE   VPSS0_SMMU_RESET_STATE        ; /* 0xf37c */
    U_VPSS0_SMMU_MASTER_DBG0   VPSS0_SMMU_MASTER_DBG0        ; /* 0xf380 */
    U_VPSS0_SMMU_MASTER_DBG1   VPSS0_SMMU_MASTER_DBG1        ; /* 0xf384 */
    U_VPSS0_SMMU_MASTER_DBG2   VPSS0_SMMU_MASTER_DBG2        ; /* 0xf388 */
    U_VPSS0_SMMU_MASTER_DBG3   VPSS0_SMMU_MASTER_DBG3        ; /* 0xf38c */
    unsigned int           reserved_125[100]                     ; /* 0xf390~0xf51c */
    U_VPSS0_SMMU_MASTER_DBG4   VPSS0_SMMU_MASTER_DBG4        ; /* 0xf520 */
    U_VPSS0_SMMU_MASTER_DBG5   VPSS0_SMMU_MASTER_DBG5        ; /* 0xf524 */
    U_VPSS0_SMMU_MASTER_DBG6   VPSS0_SMMU_MASTER_DBG6        ; /* 0xf528 */
    U_VPSS0_SMMU_MASTER_DBG7   VPSS0_SMMU_MASTER_DBG7        ; /* 0xf52c */
    U_VPSS0_SMMU_MASTER_DBG8   VPSS0_SMMU_MASTER_DBG8        ; /* 0xf530 */

} VPSS_REG_S,S_VPSS_REGS_TYPE,S_CAS_REGS_TYPE;


#endif /* __HI_REG_VPSS_H__ */
