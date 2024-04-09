// ******************************************************************************
// Copyright     :  Copyright (C) 2017, Hisilicon Technologies Co. Ltd.
// File name     :  hi_reg_vdp.h
// Project line  :  Platform And Key Technologies Development
// Department    :  CAD Development Department
// Author        :  xxx
// Version       :  1
// Date          :  2013/3/10
// Description   :  The description of xxx project
// Others        :  Generated automatically by nManager V4.1
// History       :  xxx 2017/11/29 09:06:22 Create file
// ******************************************************************************

#ifndef __HI_REG_VDP_H__
#define __HI_REG_VDP_H__

/* Define the union U_VOCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_ck_gt_en           : 1   ; /* [0]  */
        unsigned int    v1_ck_gt_en           : 1   ; /* [1]  */
        unsigned int    m1_arb_mode           : 1   ; /* [2]  */
        unsigned int    m2_arb_mode           : 1   ; /* [3]  */
        unsigned int    vp0_ck_gt_en          : 1   ; /* [4]  */
        unsigned int    m3_arb_mode           : 1   ; /* [5]  */
        unsigned int    g0_ck_gt_en           : 1   ; /* [6]  */
        unsigned int    g1_ck_gt_en           : 1   ; /* [7]  */
        unsigned int    grc_arb_mode          : 1   ; /* [8]  */
        unsigned int    twochn_en             : 1   ; /* [9]  */
        unsigned int    gp0_ck_gt_en          : 1   ; /* [10]  */
        unsigned int    twochn_mode           : 1   ; /* [11]  */
        unsigned int    wbc0_ck_gt_en         : 1   ; /* [12]  */
        unsigned int    g3_sel                : 1   ; /* [13]  */
        unsigned int    reserved_0            : 17  ; /* [30..14]  */
        unsigned int    vo_ck_gt_en           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOCTRL;

/* Define the union U_VOINTSTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0vtthd1_int        : 1   ; /* [0]  */
        unsigned int    dhd0vtthd2_int        : 1   ; /* [1]  */
        unsigned int    dhd0vtthd3_int        : 1   ; /* [2]  */
        unsigned int    dhd0uf_int            : 1   ; /* [3]  */
        unsigned int    dhd1vtthd1_int        : 1   ; /* [4]  */
        unsigned int    dhd1vtthd2_int        : 1   ; /* [5]  */
        unsigned int    dhd1vtthd3_int        : 1   ; /* [6]  */
        unsigned int    dhd1uf_int            : 1   ; /* [7]  */
        unsigned int    gwbc0_vte_int         : 1   ; /* [8]  */
        unsigned int    dwbc0_vte_int         : 1   ; /* [9]  */
        unsigned int    g0wbc_vte_int         : 1   ; /* [10]  */
        unsigned int    g4wbc_vte_int         : 1   ; /* [11]  */
        unsigned int    hdmi_buf_int          : 1   ; /* [12]  */
        unsigned int    wbc_ref_vte_int       : 1   ; /* [13]  */
        unsigned int    wbc_mad_int           : 1   ; /* [14]  */
        unsigned int    v0_back_int           : 1   ; /* [15]  */
        unsigned int    v1_back_int           : 1   ; /* [16]  */
        unsigned int    gfx_back_int          : 1   ; /* [17]  */
        unsigned int    v4rr_int              : 1   ; /* [18]  */
        unsigned int    wbc_stt_vte_int       : 1   ; /* [19]  */
        unsigned int    vdac0_load_int        : 1   ; /* [20]  */
        unsigned int    vdac1_load_int        : 1   ; /* [21]  */
        unsigned int    vdac2_load_int        : 1   ; /* [22]  */
        unsigned int    vdac3_load_int        : 1   ; /* [23]  */
        unsigned int    v0_fc_int             : 1   ; /* [24]  */
        unsigned int    v1_fc_int             : 1   ; /* [25]  */
        unsigned int    gfx_fc_int            : 1   ; /* [26]  */
        unsigned int    vdp_usingip_int       : 1   ; /* [27]  */
        unsigned int    comip_conflict_int    : 1   ; /* [28]  */
        unsigned int    wbcdhd_partfns_int    : 1   ; /* [29]  */
        unsigned int    m0_be_int             : 1   ; /* [30]  */
        unsigned int    m1_be_int             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOINTSTA;

/* Define the union U_VOMSKINTSTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0vtthd1_clr        : 1   ; /* [0]  */
        unsigned int    dhd0vtthd2_clr        : 1   ; /* [1]  */
        unsigned int    dhd0vtthd3_clr        : 1   ; /* [2]  */
        unsigned int    dhd0uf_clr            : 1   ; /* [3]  */
        unsigned int    dhd1vtthd1_clr        : 1   ; /* [4]  */
        unsigned int    dhd1vtthd2_clr        : 1   ; /* [5]  */
        unsigned int    dhd1vtthd3_clr        : 1   ; /* [6]  */
        unsigned int    dhd1uf_clr            : 1   ; /* [7]  */
        unsigned int    gwbc0_vte_clr         : 1   ; /* [8]  */
        unsigned int    dwbc0_vte_clr         : 1   ; /* [9]  */
        unsigned int    g0wbc_vte_clr         : 1   ; /* [10]  */
        unsigned int    g4wbc_vte_clr         : 1   ; /* [11]  */
        unsigned int    hdmi_buf_clr          : 1   ; /* [12]  */
        unsigned int    wbc_ref_vte_clr       : 1   ; /* [13]  */
        unsigned int    wbc_mad_clr           : 1   ; /* [14]  */
        unsigned int    v0rr_clr              : 1   ; /* [15]  */
        unsigned int    v1rr_clr              : 1   ; /* [16]  */
        unsigned int    v3rr_clr              : 1   ; /* [17]  */
        unsigned int    v4rr_clr              : 1   ; /* [18]  */
        unsigned int    wbc_stt_vte_clr       : 1   ; /* [19]  */
        unsigned int    vdac0_load_clr        : 1   ; /* [20]  */
        unsigned int    vdac1_load_clr        : 1   ; /* [21]  */
        unsigned int    vdac2_load_clr        : 1   ; /* [22]  */
        unsigned int    vdac3_load_clr        : 1   ; /* [23]  */
        unsigned int    g0rr_clr              : 1   ; /* [24]  */
        unsigned int    g1rr_clr              : 1   ; /* [25]  */
        unsigned int    g2rr_clr              : 1   ; /* [26]  */
        unsigned int    vdp_usingip_clr       : 1   ; /* [27]  */
        unsigned int    comip_conflict_clr    : 1   ; /* [28]  */
        unsigned int    wbcdhd_partfns_clr    : 1   ; /* [29]  */
        unsigned int    m0_be_clr             : 1   ; /* [30]  */
        unsigned int    m1_be_clr             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOMSKINTSTA;

/* Define the union U_VOINTMSK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0vtthd1_intmsk     : 1   ; /* [0]  */
        unsigned int    dhd0vtthd2_intmsk     : 1   ; /* [1]  */
        unsigned int    dhd0vtthd3_intmsk     : 1   ; /* [2]  */
        unsigned int    dhd0uf_intmsk         : 1   ; /* [3]  */
        unsigned int    dhd1vtthd1_intmsk     : 1   ; /* [4]  */
        unsigned int    dhd1vtthd2_intmsk     : 1   ; /* [5]  */
        unsigned int    dhd1vtthd3_intmsk     : 1   ; /* [6]  */
        unsigned int    dhd1uf_intmsk         : 1   ; /* [7]  */
        unsigned int    gwbc0_vte_intmsk      : 1   ; /* [8]  */
        unsigned int    dwbc0_vte_intmsk      : 1   ; /* [9]  */
        unsigned int    g0wbc_vte_intmsk      : 1   ; /* [10]  */
        unsigned int    g4wbc_vte_intmsk      : 1   ; /* [11]  */
        unsigned int    hdmi_buf_intmsk       : 1   ; /* [12]  */
        unsigned int    wbc_ref_mskint        : 1   ; /* [13]  */
        unsigned int    wbc_mad_intmsk        : 1   ; /* [14]  */
        unsigned int    v0_back_intmsk        : 1   ; /* [15]  */
        unsigned int    v1_back_intmsk        : 1   ; /* [16]  */
        unsigned int    gfx_back_intmsk       : 1   ; /* [17]  */
        unsigned int    v4rr_intmsk           : 1   ; /* [18]  */
        unsigned int    wbc_stt_intmsk        : 1   ; /* [19]  */
        unsigned int    vdac0_load_intmsk     : 1   ; /* [20]  */
        unsigned int    vdac1_load_intmsk     : 1   ; /* [21]  */
        unsigned int    vdac2_load_intmsk     : 1   ; /* [22]  */
        unsigned int    vdac3_load_intmsk     : 1   ; /* [23]  */
        unsigned int    v0_fc_intmsk          : 1   ; /* [24]  */
        unsigned int    v1_fc_intmsk          : 1   ; /* [25]  */
        unsigned int    gfx_fc_intmsk         : 1   ; /* [26]  */
        unsigned int    vdp_usingip_intmsk    : 1   ; /* [27]  */
        unsigned int    comip_conflict_intmsk : 1   ; /* [28]  */
        unsigned int    wbcdhd_partfns_intmsk : 1   ; /* [29]  */
        unsigned int    m0_be_intmsk          : 1   ; /* [30]  */
        unsigned int    m1_be_intmsk          : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOINTMSK;

/* Define the union U_VODEBUG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rm_en_chn             : 4   ; /* [3..0]  */
        unsigned int    dhd0_ff_info          : 2   ; /* [5..4]  */
        unsigned int    dhd1_ff_info          : 2   ; /* [7..6]  */
        unsigned int    dsd0_ff_info          : 2   ; /* [9..8]  */
        unsigned int    bfm_vga_en            : 1   ; /* [10]  */
        unsigned int    bfm_cvbs_en           : 1   ; /* [11]  */
        unsigned int    bfm_lcd_en            : 1   ; /* [12]  */
        unsigned int    bfm_bt1120_en         : 1   ; /* [13]  */
        unsigned int    wbc2_ff_info          : 2   ; /* [15..14]  */
        unsigned int    wbc_mode              : 4   ; /* [19..16]  */
        unsigned int    node_num              : 4   ; /* [23..20]  */
        unsigned int    wbc_cmp_mode          : 2   ; /* [25..24]  */
        unsigned int    bfm_mode              : 3   ; /* [28..26]  */
        unsigned int    bfm_clk_sel           : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VODEBUG;

/* Define the union U_VDPVERSION1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vdpversion1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VDPVERSION1;
/* Define the union U_VDPVERSION2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vdpversion2            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VDPVERSION2;
/* Define the union U_VOLOWPOWER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rfs_ema               : 3   ; /* [2..0]  */
        unsigned int    rfs_emaw              : 2   ; /* [4..3]  */
        unsigned int    rfs_ret1n             : 1   ; /* [5]  */
        unsigned int    rft_emaa              : 3   ; /* [8..6]  */
        unsigned int    rft_emab              : 3   ; /* [11..9]  */
        unsigned int    rft_colldisn          : 1   ; /* [12]  */
        unsigned int    rft_emasa             : 1   ; /* [13]  */
        unsigned int    rftuhd_ema            : 3   ; /* [16..14]  */
        unsigned int    rftuhd_emawb          : 2   ; /* [18..17]  */
        unsigned int    rftuhd_emasa          : 1   ; /* [19]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOLOWPOWER_CTRL;

/* Define the union U_VOUFSTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_uf_sta             : 1   ; /* [0]  */
        unsigned int    v1_uf_sta             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    v3_uf_sta             : 1   ; /* [3]  */
        unsigned int    reserved_1            : 4   ; /* [7..4]  */
        unsigned int    g0_uf_sta             : 1   ; /* [8]  */
        unsigned int    g1_uf_sta             : 1   ; /* [9]  */
        unsigned int    g2_uf_sta             : 1   ; /* [10]  */
        unsigned int    g3_uf_sta             : 1   ; /* [11]  */
        unsigned int    g4_uf_sta             : 1   ; /* [12]  */
        unsigned int    reserved_2            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOUFSTA;

/* Define the union U_VOUFCLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_uf_clr             : 1   ; /* [0]  */
        unsigned int    v1_uf_clr             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 1   ; /* [2]  */
        unsigned int    v3_uf_clr             : 1   ; /* [3]  */
        unsigned int    reserved_1            : 4   ; /* [7..4]  */
        unsigned int    g0_uf_clr             : 1   ; /* [8]  */
        unsigned int    g1_uf_clr             : 1   ; /* [9]  */
        unsigned int    g2_uf_clr             : 1   ; /* [10]  */
        unsigned int    g3_uf_clr             : 1   ; /* [11]  */
        unsigned int    g4_uf_clr             : 1   ; /* [12]  */
        unsigned int    reserved_2            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOUFCLR;

/* Define the union U_VOINTPROC_TIM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vointproc_time        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOINTPROC_TIM;

/* Define the union U_VOMSKINTSTA2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0vtthd5_clr        : 1   ; /* [0]  */
        unsigned int    dhd0vtthd6_clr        : 1   ; /* [1]  */
        unsigned int    dhd1vtthd5_clr        : 1   ; /* [2]  */
        unsigned int    dhd1vtthd6_clr        : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOMSKINTSTA2;

/* Define the union U_VOINTSTA2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dhd0vtthd5_int        : 1   ; /* [0]  */
        unsigned int    dhd0vtthd6_int        : 1   ; /* [1]  */
        unsigned int    dhd1vtthd5_int        : 1   ; /* [2]  */
        unsigned int    dhd1vtthd6_int        : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VOINTSTA2;

/* Define the union U_VOFPGATEST */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VOFPGATEST;
/* Define the union U_VO_MUX_DAC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac0_sel              : 4   ; /* [3..0]  */
        unsigned int    dac1_sel              : 4   ; /* [7..4]  */
        unsigned int    dac2_sel              : 4   ; /* [11..8]  */
        unsigned int    dac3_sel              : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_MUX_DAC;

/* Define the union U_VO_DAC_CTRL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac_reg_rev           : 16  ; /* [15..0]  */
        unsigned int    enctr                 : 4   ; /* [19..16]  */
        unsigned int    enextref              : 1   ; /* [20]  */
        unsigned int    pdchopper             : 1   ; /* [21]  */
        unsigned int    envbg                 : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_CTRL0;

/* Define the union U_VO_DAC_C_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cablectr              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    dacgc                 : 6   ; /* [9..4]  */
        unsigned int    reserved_1            : 21  ; /* [30..10]  */
        unsigned int    dac_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_C_CTRL;

/* Define the union U_VO_DAC_R_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cablectr              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    dacgc                 : 6   ; /* [9..4]  */
        unsigned int    reserved_1            : 21  ; /* [30..10]  */
        unsigned int    dac_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_R_CTRL;

/* Define the union U_VO_DAC_G_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cablectr              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    dacgc                 : 6   ; /* [9..4]  */
        unsigned int    reserved_1            : 21  ; /* [30..10]  */
        unsigned int    dac_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_G_CTRL;

/* Define the union U_VO_DAC_B_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cablectr              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    dacgc                 : 6   ; /* [9..4]  */
        unsigned int    reserved_1            : 21  ; /* [30..10]  */
        unsigned int    dac_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_B_CTRL;

/* Define the union U_VO_DAC_CTRL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac_otp_reg           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_DAC_CTRL1;

/* Define the union U_CBM_BKG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cbm_bkgcr1            : 10  ; /* [9..0]  */
        unsigned int    cbm_bkgcb1            : 10  ; /* [19..10]  */
        unsigned int    cbm_bkgy1             : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_BKG1;

/* Define the union U_CBM_MIX1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_CBM_MIX1;

/* Define the union U_LINK_CTRL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v0_link_ctrl          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LINK_CTRL0;

/* Define the union U_PARA_ADDR_VHD_CHN00 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn00    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN00;
/* Define the union U_PARA_ADDR_VHD_CHN01 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn01    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN01;
/* Define the union U_PARA_ADDR_VHD_CHN02 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn02    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN02;
/* Define the union U_PARA_ADDR_VHD_CHN03 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn03    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN03;
/* Define the union U_PARA_ADDR_VHD_CHN04 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn04    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN04;
/* Define the union U_PARA_ADDR_VHD_CHN05 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn05    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN05;
/* Define the union U_PARA_ADDR_VHD_CHN06 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn06    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN06;
/* Define the union U_PARA_ADDR_VHD_CHN07 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn07    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN07;
/* Define the union U_PARA_ADDR_VHD_CHN08 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn08    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN08;
/* Define the union U_PARA_ADDR_VHD_CHN09 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn09    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN09;
/* Define the union U_PARA_ADDR_VHD_CHN10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn10    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN10;
/* Define the union U_PARA_ADDR_VHD_CHN11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn11    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN11;
/* Define the union U_PARA_ADDR_VHD_CHN12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn12    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN12;
/* Define the union U_PARA_ADDR_VHD_CHN13 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn13    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN13;
/* Define the union U_PARA_ADDR_VHD_CHN14 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn14    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN14;
/* Define the union U_PARA_ADDR_VHD_CHN15 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn15    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN15;
/* Define the union U_PARA_ADDR_VHD_CHN16 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn16    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN16;
/* Define the union U_PARA_ADDR_VHD_CHN17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn17    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN17;
/* Define the union U_PARA_ADDR_VHD_CHN18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn18    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN18;
/* Define the union U_PARA_ADDR_VHD_CHN19 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn19    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN19;
/* Define the union U_PARA_ADDR_VHD_CHN20 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn20    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN20;
/* Define the union U_PARA_ADDR_VHD_CHN21 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn21    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN21;
/* Define the union U_PARA_ADDR_VHD_CHN22 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn22    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN22;
/* Define the union U_PARA_ADDR_VHD_CHN23 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn23    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN23;
/* Define the union U_PARA_ADDR_VHD_CHN24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn24    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN24;
/* Define the union U_PARA_ADDR_VHD_CHN25 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn25    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN25;
/* Define the union U_PARA_ADDR_VHD_CHN26 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn26    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN26;
/* Define the union U_PARA_ADDR_VHD_CHN27 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn27    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN27;
/* Define the union U_PARA_ADDR_VHD_CHN28 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn28    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN28;
/* Define the union U_PARA_ADDR_VHD_CHN29 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn29    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN29;
/* Define the union U_PARA_ADDR_VHD_CHN30 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn30    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN30;
/* Define the union U_PARA_ADDR_VHD_CHN31 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int para_addr_vhd_chn31    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_PARA_ADDR_VHD_CHN31;
/* Define the union U_PARA_UP_VHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    para_up_vhd_chn00     : 1   ; /* [0]  */
        unsigned int    para_up_vhd_chn01     : 1   ; /* [1]  */
        unsigned int    para_up_vhd_chn02     : 1   ; /* [2]  */
        unsigned int    para_up_vhd_chn03     : 1   ; /* [3]  */
        unsigned int    para_up_vhd_chn04     : 1   ; /* [4]  */
        unsigned int    para_up_vhd_chn05     : 1   ; /* [5]  */
        unsigned int    para_up_vhd_chn06     : 1   ; /* [6]  */
        unsigned int    para_up_vhd_chn07     : 1   ; /* [7]  */
        unsigned int    para_up_vhd_chn08     : 1   ; /* [8]  */
        unsigned int    para_up_vhd_chn09     : 1   ; /* [9]  */
        unsigned int    para_up_vhd_chn10     : 1   ; /* [10]  */
        unsigned int    para_up_vhd_chn11     : 1   ; /* [11]  */
        unsigned int    para_up_vhd_chn12     : 1   ; /* [12]  */
        unsigned int    para_up_vhd_chn13     : 1   ; /* [13]  */
        unsigned int    para_up_vhd_chn14     : 1   ; /* [14]  */
        unsigned int    para_up_vhd_chn15     : 1   ; /* [15]  */
        unsigned int    para_up_vhd_chn16     : 1   ; /* [16]  */
        unsigned int    para_up_vhd_chn17     : 1   ; /* [17]  */
        unsigned int    para_up_vhd_chn18     : 1   ; /* [18]  */
        unsigned int    para_up_vhd_chn19     : 1   ; /* [19]  */
        unsigned int    para_up_vhd_chn20     : 1   ; /* [20]  */
        unsigned int    para_up_vhd_chn21     : 1   ; /* [21]  */
        unsigned int    para_up_vhd_chn22     : 1   ; /* [22]  */
        unsigned int    para_up_vhd_chn23     : 1   ; /* [23]  */
        unsigned int    para_up_vhd_chn24     : 1   ; /* [24]  */
        unsigned int    para_up_vhd_chn25     : 1   ; /* [25]  */
        unsigned int    para_up_vhd_chn26     : 1   ; /* [26]  */
        unsigned int    para_up_vhd_chn27     : 1   ; /* [27]  */
        unsigned int    para_up_vhd_chn28     : 1   ; /* [28]  */
        unsigned int    para_up_vhd_chn29     : 1   ; /* [29]  */
        unsigned int    para_up_vhd_chn30     : 1   ; /* [30]  */
        unsigned int    para_up_vhd_chn31     : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PARA_UP_VHD;

/* Define the union U_PARA_CONFLICT_CLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    para_conflict_clr_hd  : 1   ; /* [0]  */
        unsigned int    para_conflict_clr_sd  : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PARA_CONFLICT_CLR;

/* Define the union U_PARA_CONFLICT_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    para_conflict_hd      : 1   ; /* [0]  */
        unsigned int    para_conflict_sd      : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PARA_CONFLICT_STA;

/* Define the union U_V0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    zme1_out_pro_sel      : 1   ; /* [8]  */
        unsigned int    add_buf_sw_en         : 1   ; /* [9]  */
        unsigned int    add_buf_sw_sel        : 1   ; /* [10]  */
        unsigned int    zme1_reduce_tap       : 1   ; /* [11]  */
        unsigned int    zme2_reduce_tap       : 1   ; /* [12]  */
        unsigned int    zme_in_fmt            : 2   ; /* [14..13]  */
        unsigned int    reserved_0            : 7   ; /* [21..15]  */
        unsigned int    vicap_abnm_en         : 1   ; /* [22]  */
        unsigned int    ofl_master            : 1   ; /* [23]  */
        unsigned int    es_en                 : 1   ; /* [24]  */
        unsigned int    fi_vscale             : 1   ; /* [25]  */
        unsigned int    twodt3d_en            : 1   ; /* [26]  */
        unsigned int    surface_c_en          : 1   ; /* [27]  */
        unsigned int    rupd_field            : 1   ; /* [28]  */
        unsigned int    vup_mode              : 1   ; /* [29]  */
        unsigned int    nosec_flag            : 1   ; /* [30]  */
        unsigned int    surface_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_CTRL;

/* Define the union U_V0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_UPD;

/* Define the union U_V0_ORESO_READ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 16  ; /* [15..0]  */
        unsigned int    oh                    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ORESO_READ;

/* Define the union U_V0_CTRL_WORK */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int v0_ctrl_work           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V0_CTRL_WORK;
/* Define the union U_V0_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 16  ; /* [15..0]  */
        unsigned int    disp_yfpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DFPOS;

/* Define the union U_V0_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 16  ; /* [15..0]  */
        unsigned int    disp_ylpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_DLPOS;

/* Define the union U_V0_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 16  ; /* [15..0]  */
        unsigned int    video_yfpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VFPOS;

/* Define the union U_V0_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 16  ; /* [15..0]  */
        unsigned int    video_ylpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VLPOS;

/* Define the union U_V0_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_BK;

/* Define the union U_V0_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ALPHA;

/* Define the union U_V0_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 1   ; /* [30]  */
        unsigned int    mute_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_MUTE_BK;

/* Define the union U_V0_HPZME */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ck_gt_en              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 28  ; /* [28..1]  */
        unsigned int    hpzme_mode            : 1   ; /* [29]  */
        unsigned int    reserved_1            : 1   ; /* [30]  */
        unsigned int    hpzme_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HPZME;

/* Define the union U_V0_HPZME_COEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef0                 : 10  ; /* [9..0]  */
        unsigned int    coef1                 : 10  ; /* [19..10]  */
        unsigned int    coef2                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HPZME_COEF;

/* Define the union U_V0_HSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hratio                : 24  ; /* [23..0]  */
        unsigned int    hfir_order            : 1   ; /* [24]  */
        unsigned int    hchfir_en             : 1   ; /* [25]  */
        unsigned int    hlfir_en              : 1   ; /* [26]  */
        unsigned int    non_lnr_en            : 1   ; /* [27]  */
        unsigned int    hchmid_en             : 1   ; /* [28]  */
        unsigned int    hlmid_en              : 1   ; /* [29]  */
        unsigned int    hchmsc_en             : 1   ; /* [30]  */
        unsigned int    hlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HSP;

/* Define the union U_V0_HLOFFSET */
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

} U_V0_HLOFFSET;

/* Define the union U_V0_HCOFFSET */
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

} U_V0_HCOFFSET;

/* Define the union U_V0_HZONE0DELTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zone0_delta           : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HZONE0DELTA;

/* Define the union U_V0_HZONE2DELTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zone2_delta           : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HZONE2DELTA;

/* Define the union U_V0_HZONEEND */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zone0_end             : 12  ; /* [11..0]  */
        unsigned int    zone1_end             : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HZONEEND;

/* Define the union U_V0_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ck_gt_en              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 18  ; /* [18..1]  */
        unsigned int    zme_in_fmt            : 2   ; /* [20..19]  */
        unsigned int    zme_out_fmt           : 2   ; /* [22..21]  */
        unsigned int    vchfir_en             : 1   ; /* [23]  */
        unsigned int    vlfir_en              : 1   ; /* [24]  */
        unsigned int    vfir_1tap_en          : 1   ; /* [25]  */
        unsigned int    el_zme_en             : 1   ; /* [26]  */
        unsigned int    vtap_reduce           : 1   ; /* [27]  */
        unsigned int    vchmid_en             : 1   ; /* [28]  */
        unsigned int    vlmid_en              : 1   ; /* [29]  */
        unsigned int    vchmsc_en             : 1   ; /* [30]  */
        unsigned int    vlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VSP;

/* Define the union U_V0_VSR */
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

} U_V0_VSR;

/* Define the union U_V0_VOFFSET */
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

} U_V0_VOFFSET;

/* Define the union U_V0_VBOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbchroma_offset       : 16  ; /* [15..0]  */
        unsigned int    vbluma_offset         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_VBOFFSET;

/* Define the union U_V0_ZME_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    oh                    : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME_ORESO;

/* Define the union U_V0_ZMECOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_vf_cren       : 1   ; /* [0]  */
        unsigned int    apb_vhd_vf_lren       : 1   ; /* [1]  */
        unsigned int    apb_vhd_hf_cren_b     : 1   ; /* [2]  */
        unsigned int    apb_vhd_hf_cren_a     : 1   ; /* [3]  */
        unsigned int    apb_vhd_hf_lren_b     : 1   ; /* [4]  */
        unsigned int    apb_vhd_hf_lren_a     : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZMECOEF;

/* Define the union U_V0_ZMECOEFAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_coef_raddr    : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZMECOEFAD;

/* Define the union U_V0_ZME_SHOOTCTRL_HL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hl_coring             : 8   ; /* [7..0]  */
        unsigned int    hl_gain               : 6   ; /* [13..8]  */
        unsigned int    hl_coringadj_en       : 1   ; /* [14]  */
        unsigned int    hl_flatdect_mode      : 1   ; /* [15]  */
        unsigned int    hl_shootctrl_mode     : 1   ; /* [16]  */
        unsigned int    hl_shootctrl_en       : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME_SHOOTCTRL_HL;

/* Define the union U_V0_ZME_SHOOTCTRL_HC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hc_coring             : 8   ; /* [7..0]  */
        unsigned int    hc_gain               : 6   ; /* [13..8]  */
        unsigned int    hc_coringadj_en       : 1   ; /* [14]  */
        unsigned int    hc_flatdect_mode      : 1   ; /* [15]  */
        unsigned int    hc_shootctrl_mode     : 1   ; /* [16]  */
        unsigned int    hc_shootctrl_en       : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME_SHOOTCTRL_HC;

/* Define the union U_V0_ZME_SHOOTCTRL_VL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vl_coring             : 8   ; /* [7..0]  */
        unsigned int    vl_gain               : 6   ; /* [13..8]  */
        unsigned int    vl_coringadj_en       : 1   ; /* [14]  */
        unsigned int    vl_flatdect_mode      : 1   ; /* [15]  */
        unsigned int    vl_shootctrl_mode     : 1   ; /* [16]  */
        unsigned int    vl_shootctrl_en       : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME_SHOOTCTRL_VL;

/* Define the union U_V0_ZME_SHOOTCTRL_VC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vc_coring             : 8   ; /* [7..0]  */
        unsigned int    vc_gain               : 6   ; /* [13..8]  */
        unsigned int    vc_coringadj_en       : 1   ; /* [14]  */
        unsigned int    vc_flatdect_mode      : 1   ; /* [15]  */
        unsigned int    vc_shootctrl_mode     : 1   ; /* [16]  */
        unsigned int    vc_shootctrl_en       : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME_SHOOTCTRL_VC;

/* Define the union U_V0_ZME2_HSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hratio                : 24  ; /* [23..0]  */
        unsigned int    hfir_order            : 1   ; /* [24]  */
        unsigned int    hchfir_en             : 1   ; /* [25]  */
        unsigned int    hlfir_en              : 1   ; /* [26]  */
        unsigned int    non_lnr_en            : 1   ; /* [27]  */
        unsigned int    hchmid_en             : 1   ; /* [28]  */
        unsigned int    hlmid_en              : 1   ; /* [29]  */
        unsigned int    hchmsc_en             : 1   ; /* [30]  */
        unsigned int    hlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_HSP;

/* Define the union U_V0_ZME2_HLOFFSET */
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

} U_V0_ZME2_HLOFFSET;

/* Define the union U_V0_ZME2_HCOFFSET */
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

} U_V0_ZME2_HCOFFSET;

/* Define the union U_V0_ZME2_HZONE0DELTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zone0_delta           : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_HZONE0DELTA;

/* Define the union U_V0_ZME2_HZONE2DELTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zone2_delta           : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_HZONE2DELTA;

/* Define the union U_V0_ZME2_HZONEEND */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    zone0_end             : 12  ; /* [11..0]  */
        unsigned int    zone1_end             : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_HZONEEND;

/* Define the union U_V0_ZME2_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ck_gt_en              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 18  ; /* [18..1]  */
        unsigned int    zme_in_fmt            : 2   ; /* [20..19]  */
        unsigned int    zme_out_fmt           : 2   ; /* [22..21]  */
        unsigned int    vchfir_en             : 1   ; /* [23]  */
        unsigned int    vlfir_en              : 1   ; /* [24]  */
        unsigned int    vfir_1tap_en          : 1   ; /* [25]  */
        unsigned int    el_zme_en             : 1   ; /* [26]  */
        unsigned int    vtap_reduce           : 1   ; /* [27]  */
        unsigned int    vchmid_en             : 1   ; /* [28]  */
        unsigned int    vlmid_en              : 1   ; /* [29]  */
        unsigned int    vchmsc_en             : 1   ; /* [30]  */
        unsigned int    vlmsc_en              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_VSP;

/* Define the union U_V0_ZME2_VSR */
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

} U_V0_ZME2_VSR;

/* Define the union U_V0_ZME2_VOFFSET */
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

} U_V0_ZME2_VOFFSET;

/* Define the union U_V0_ZME2_VBOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbchroma_offset       : 16  ; /* [15..0]  */
        unsigned int    vbluma_offset         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_VBOFFSET;

/* Define the union U_V0_ZME2_ORESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    oh                    : 12  ; /* [27..16]  */
        unsigned int    reserved_1            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_ORESO;

/* Define the union U_V0_ZME2_ZMECOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_vf_cren       : 1   ; /* [0]  */
        unsigned int    apb_vhd_vf_lren       : 1   ; /* [1]  */
        unsigned int    apb_vhd_hf_cren_b     : 1   ; /* [2]  */
        unsigned int    apb_vhd_hf_cren_a     : 1   ; /* [3]  */
        unsigned int    apb_vhd_hf_lren_b     : 1   ; /* [4]  */
        unsigned int    apb_vhd_hf_lren_a     : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_ZMECOEF;

/* Define the union U_V0_ZME2_ZMECOEFAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_coef_raddr    : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_ZMECOEFAD;

/* Define the union U_V0_ZME2_SHOOTCTRL_HL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hl_coring             : 8   ; /* [7..0]  */
        unsigned int    hl_gain               : 6   ; /* [13..8]  */
        unsigned int    hl_coringadj_en       : 1   ; /* [14]  */
        unsigned int    hl_flatdect_mode      : 1   ; /* [15]  */
        unsigned int    hl_shootctrl_mode     : 1   ; /* [16]  */
        unsigned int    hl_shootctrl_en       : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_SHOOTCTRL_HL;

/* Define the union U_V0_ZME2_SHOOTCTRL_HC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hc_coring             : 8   ; /* [7..0]  */
        unsigned int    hc_gain               : 6   ; /* [13..8]  */
        unsigned int    hc_coringadj_en       : 1   ; /* [14]  */
        unsigned int    hc_flatdect_mode      : 1   ; /* [15]  */
        unsigned int    hc_shootctrl_mode     : 1   ; /* [16]  */
        unsigned int    hc_shootctrl_en       : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_SHOOTCTRL_HC;

/* Define the union U_V0_ZME2_SHOOTCTRL_VL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vl_coring             : 8   ; /* [7..0]  */
        unsigned int    vl_gain               : 6   ; /* [13..8]  */
        unsigned int    vl_coringadj_en       : 1   ; /* [14]  */
        unsigned int    vl_flatdect_mode      : 1   ; /* [15]  */
        unsigned int    vl_shootctrl_mode     : 1   ; /* [16]  */
        unsigned int    vl_shootctrl_en       : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_SHOOTCTRL_VL;

/* Define the union U_V0_ZME2_SHOOTCTRL_VC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vc_coring             : 8   ; /* [7..0]  */
        unsigned int    vc_gain               : 6   ; /* [13..8]  */
        unsigned int    vc_coringadj_en       : 1   ; /* [14]  */
        unsigned int    vc_flatdect_mode      : 1   ; /* [15]  */
        unsigned int    vc_shootctrl_mode     : 1   ; /* [16]  */
        unsigned int    vc_shootctrl_en       : 1   ; /* [17]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_ZME2_SHOOTCTRL_VC;

/* Define the union U_V0_HFIR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    hfir_mode             : 2   ; /* [2..1]  */
        unsigned int    mid_en                : 1   ; /* [3]  */
        unsigned int    ck_gt_en              : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_HFIR_CTRL;

/* Define the union U_V0_IFIRCOEF01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef0                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef1                 : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_IFIRCOEF01;

/* Define the union U_V0_IFIRCOEF23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef2                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef3                 : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_IFIRCOEF23;

/* Define the union U_V0_IFIRCOEF45 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef4                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef5                 : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_IFIRCOEF45;

/* Define the union U_V0_IFIRCOEF67 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef6                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef7                 : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V0_IFIRCOEF67;

/* Define the union U_V1_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 17  ; /* [24..8]  */
        unsigned int    yc_sel                : 2   ; /* [26..25]  */
        unsigned int    buf_mode              : 1   ; /* [27]  */
        unsigned int    rupd_field            : 1   ; /* [28]  */
        unsigned int    vup_mode              : 1   ; /* [29]  */
        unsigned int    nosec_flag            : 1   ; /* [30]  */
        unsigned int    surface_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_CTRL;

/* Define the union U_V1_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_UPD;

/* Define the union U_V1_ORESO_READ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 16  ; /* [15..0]  */
        unsigned int    oh                    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_ORESO_READ;

/* Define the union U_V1_CTRL_WORK */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int v1_ctrl_work           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_CTRL_WORK;
/* Define the union U_V1_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 16  ; /* [15..0]  */
        unsigned int    disp_yfpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DFPOS;

/* Define the union U_V1_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 16  ; /* [15..0]  */
        unsigned int    disp_ylpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DLPOS;

/* Define the union U_V1_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 16  ; /* [15..0]  */
        unsigned int    video_yfpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VFPOS;

/* Define the union U_V1_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 16  ; /* [15..0]  */
        unsigned int    video_ylpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VLPOS;

/* Define the union U_V1_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_BK;

/* Define the union U_V1_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_ALPHA;

/* Define the union U_V1_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 1   ; /* [30]  */
        unsigned int    mute_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MUTE_BK;

/* Define the union U_V1_HFIR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 1   ; /* [0]  */
        unsigned int    hfir_mode             : 2   ; /* [2..1]  */
        unsigned int    mid_en                : 1   ; /* [3]  */
        unsigned int    ck_gt_en              : 1   ; /* [4]  */
        unsigned int    hfir_en               : 1   ; /* [5]  */
        unsigned int    reserved_1            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_HFIR_CTRL;

/* Define the union U_V1_IFIRCOEF01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef0                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    coef1                 : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_IFIRCOEF01;

/* Define the union U_VP0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 14  ; /* [21..8]  */
        unsigned int    vp_sel                : 1   ; /* [22]  */
        unsigned int    odd_data_mute         : 1   ; /* [23]  */
        unsigned int    even_data_mute        : 1   ; /* [24]  */
        unsigned int    dwm_sel               : 1   ; /* [25]  */
        unsigned int    vp_hdr_sel            : 1   ; /* [26]  */
        unsigned int    ipt2yuv_mux           : 1   ; /* [27]  */
        unsigned int    rupd_field            : 1   ; /* [28]  */
        unsigned int    rgup_mode             : 1   ; /* [29]  */
        unsigned int    reserved_1            : 1   ; /* [30]  */
        unsigned int    surface_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_CTRL;

/* Define the union U_VP0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_UPD;

/* Define the union U_VP0_ORESO_READ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 16  ; /* [15..0]  */
        unsigned int    oh                    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_ORESO_READ;

/* Define the union U_VP0_IRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    iw                    : 16  ; /* [15..0]  */
        unsigned int    ih                    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_IRESO;

/* Define the union U_VP0_CTRL_WORK */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vp0_ctrl_work          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VP0_CTRL_WORK;
/* Define the union U_VP0_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 16  ; /* [15..0]  */
        unsigned int    disp_yfpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DFPOS;

/* Define the union U_VP0_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 16  ; /* [15..0]  */
        unsigned int    disp_ylpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DLPOS;

/* Define the union U_VP0_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 16  ; /* [15..0]  */
        unsigned int    video_yfpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_VFPOS;

/* Define the union U_VP0_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 16  ; /* [15..0]  */
        unsigned int    video_ylpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_VLPOS;

/* Define the union U_VP0_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_BK;

/* Define the union U_VP0_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_ALPHA;

/* Define the union U_VP0_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 1   ; /* [30]  */
        unsigned int    mute_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_MUTE_BK;

/* Define the union U_MIXV0_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_bkgcr           : 10  ; /* [9..0]  */
        unsigned int    mixer_bkgcb           : 10  ; /* [19..10]  */
        unsigned int    mixer_bkgy            : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXV0_BKG;

/* Define the union U_MIXV0_MIX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXV0_MIX;

/* Define the union U_VP0_DOF_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 31  ; /* [30..0]  */
        unsigned int    dof_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DOF_CTRL;

/* Define the union U_VP0_DOF_STEP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    left_step             : 8   ; /* [7..0]  */
        unsigned int    right_step            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DOF_STEP;

/* Define the union U_VP0_DOF_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dof_bk_cr             : 10  ; /* [9..0]  */
        unsigned int    dof_bk_cb             : 10  ; /* [19..10]  */
        unsigned int    dof_bk_y              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VP0_DOF_BKG;

/* Define the union U_G0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    alpha_thrd            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 3   ; /* [18..16]  */
        unsigned int    odd_data_mute         : 1   ; /* [19]  */
        unsigned int    even_data_mute        : 1   ; /* [20]  */
        unsigned int    fifo_latency_clc      : 1   ; /* [21]  */
        unsigned int    req_mac_ctrl          : 2   ; /* [23..22]  */
        unsigned int    lossless_a            : 1   ; /* [24]  */
        unsigned int    lossless              : 1   ; /* [25]  */
        unsigned int    ofl_master            : 1   ; /* [26]  */
        unsigned int    depremult             : 1   ; /* [27]  */
        unsigned int    rupd_field            : 1   ; /* [28]  */
        unsigned int    upd_mode              : 1   ; /* [29]  */
        unsigned int    nosec_flag            : 1   ; /* [30]  */
        unsigned int    surface_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_CTRL;

/* Define the union U_G0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_UPD;

/* Define the union U_G0_GALPHA_SUM */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fk_alpha_sum           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G0_GALPHA_SUM;
/* Define the union U_G0_ORESO_READ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 16  ; /* [15..0]  */
        unsigned int    oh                    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_ORESO_READ;

/* Define the union U_G0_CTRL_WORK */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int g0_ctrl_work           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G0_CTRL_WORK;
/* Define the union U_G0_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 16  ; /* [15..0]  */
        unsigned int    disp_yfpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DFPOS;

/* Define the union U_G0_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 16  ; /* [15..0]  */
        unsigned int    disp_ylpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DLPOS;

/* Define the union U_G0_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 16  ; /* [15..0]  */
        unsigned int    video_yfpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_VFPOS;

/* Define the union U_G0_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 16  ; /* [15..0]  */
        unsigned int    video_ylpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_VLPOS;

/* Define the union U_G0_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_BK;

/* Define the union U_G0_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_ALPHA;

/* Define the union U_G0_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 1   ; /* [30]  */
        unsigned int    mute_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_MUTE_BK;

/* Define the union U_G0_DOF_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 31  ; /* [30..0]  */
        unsigned int    dof_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DOF_CTRL;

/* Define the union U_G0_DOF_STEP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    left_step             : 8   ; /* [7..0]  */
        unsigned int    right_step            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DOF_STEP;

/* Define the union U_G0_DOF_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dof_bk_cr             : 10  ; /* [9..0]  */
        unsigned int    dof_bk_cb             : 10  ; /* [19..10]  */
        unsigned int    dof_bk_y              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DOF_BKG;

/* Define the union U_G0_DOF_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dof_bk_alpha          : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G0_DOF_ALPHA;

/* Define the union U_G1_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    alpha_thrd            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 11  ; /* [26..16]  */
        unsigned int    depremult             : 1   ; /* [27]  */
        unsigned int    rupd_field            : 1   ; /* [28]  */
        unsigned int    upd_mode              : 1   ; /* [29]  */
        unsigned int    nosec_flag            : 1   ; /* [30]  */
        unsigned int    surface_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_CTRL;

/* Define the union U_G1_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_UPD;

/* Define the union U_G1_GALPHA_SUM */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fk_alpha_sum           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GALPHA_SUM;
/* Define the union U_G1_ORESO_READ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 16  ; /* [15..0]  */
        unsigned int    oh                    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_ORESO_READ;

/* Define the union U_G1_CTRL_WORK */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int g1_ctrl_work           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_CTRL_WORK;
/* Define the union U_G1_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 16  ; /* [15..0]  */
        unsigned int    disp_yfpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_DFPOS;

/* Define the union U_G1_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 16  ; /* [15..0]  */
        unsigned int    disp_ylpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_DLPOS;

/* Define the union U_G1_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 16  ; /* [15..0]  */
        unsigned int    video_yfpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_VFPOS;

/* Define the union U_G1_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 16  ; /* [15..0]  */
        unsigned int    video_ylpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_VLPOS;

/* Define the union U_G1_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_BK;

/* Define the union U_G1_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_ALPHA;

/* Define the union U_G1_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 1   ; /* [30]  */
        unsigned int    mute_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_MUTE_BK;

/* Define the union U_G1_DOF_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 31  ; /* [30..0]  */
        unsigned int    dof_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_DOF_CTRL;

/* Define the union U_G1_DOF_STEP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    left_step             : 8   ; /* [7..0]  */
        unsigned int    right_step            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_DOF_STEP;

/* Define the union U_G1_DOF_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dof_bk_cr             : 10  ; /* [9..0]  */
        unsigned int    dof_bk_cb             : 10  ; /* [19..10]  */
        unsigned int    dof_bk_y              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_DOF_BKG;

/* Define the union U_G1_DOF_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dof_bk_alpha          : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_DOF_ALPHA;

/* Define the union U_WBC_DHD0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_p2i_en            : 1   ; /* [0]  */
        unsigned int    root_path             : 2   ; /* [2..1]  */
        unsigned int    reserved_0            : 15  ; /* [17..3]  */
        unsigned int    histogam_en           : 1   ; /* [18]  */
        unsigned int    wbc_point_sel         : 2   ; /* [20..19]  */
        unsigned int    ofl_master            : 1   ; /* [21]  */
        unsigned int    mode_out              : 2   ; /* [23..22]  */
        unsigned int    three_d_mode          : 2   ; /* [25..24]  */
        unsigned int    auto_stop_en          : 1   ; /* [26]  */
        unsigned int    wbc_vtthd_mode        : 1   ; /* [27]  */
        unsigned int    rupd_field            : 1   ; /* [28]  */
        unsigned int    rgup_mode             : 1   ; /* [29]  */
        unsigned int    nosec_flag            : 1   ; /* [30]  */
        unsigned int    wbc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CTRL;

/* Define the union U_WBC_DHD0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_UPD;

/* Define the union U_WBC_DHD0_CTRL_WORK */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_dhd_ctrl_work      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_CTRL_WORK;
/* Define the union U_WBC_DHD0_ZME_HINFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_width             : 16  ; /* [15..0]  */
        unsigned int    ck_gt_en              : 1   ; /* [16]  */
        unsigned int    out_fmt               : 3   ; /* [19..17]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_HINFO;

/* Define the union U_WBC_DHD0_ZME_HSP */
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

} U_WBC_DHD0_ZME_HSP;

/* Define the union U_WBC_DHD0_ZME_HLOFFSET */
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

} U_WBC_DHD0_ZME_HLOFFSET;

/* Define the union U_WBC_DHD0_ZME_HCOFFSET */
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

} U_WBC_DHD0_ZME_HCOFFSET;

/* Define the union U_WBC_DHD0_ZME_HRCOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_hf_cren       : 1   ; /* [0]  */
        unsigned int    apb_vhd_hf_lren       : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_HRCOEF;

/* Define the union U_WBC_DHD0_ZME_HYCOEFAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_hycoef_raddr  : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_HYCOEFAD;

/* Define the union U_WBC_DHD0_ZME_HCCOEFAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_hccoef_raddr  : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_HCCOEFAD;

/* Define the union U_WBC_DHD0_CSCIDC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscidc0               : 9   ; /* [8..0]  */
        unsigned int    cscidc1               : 9   ; /* [17..9]  */
        unsigned int    cscidc2               : 9   ; /* [26..18]  */
        unsigned int    csc_en                : 1   ; /* [27]  */
        unsigned int    csc_mode              : 3   ; /* [30..28]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCIDC;

/* Define the union U_WBC_DHD0_CSCODC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscodc0               : 9   ; /* [8..0]  */
        unsigned int    cscodc1               : 9   ; /* [17..9]  */
        unsigned int    cscodc2               : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCODC;

/* Define the union U_WBC_DHD0_CSCP0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp00                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp01                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP0;

/* Define the union U_WBC_DHD0_CSCP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp02                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp10                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP1;

/* Define the union U_WBC_DHD0_CSCP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp11                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp12                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP2;

/* Define the union U_WBC_DHD0_CSCP3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp20                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 1   ; /* [15]  */
        unsigned int    cscp21                : 15  ; /* [30..16]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP3;

/* Define the union U_WBC_DHD0_CSCP4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cscp22                : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_CSCP4;

/* Define the union U_WBC_DHD0_HCDS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    hchfir_en             : 1   ; /* [29]  */
        unsigned int    hchmid_en             : 1   ; /* [30]  */
        unsigned int    hcds_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HCDS;

/* Define the union U_WBC_DHD0_HCDS_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef0                 : 10  ; /* [9..0]  */
        unsigned int    coef1                 : 10  ; /* [19..10]  */
        unsigned int    coef2                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HCDS_COEF0;

/* Define the union U_WBC_DHD0_HCDS_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef3                 : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_HCDS_COEF1;

/* Define the union U_WBC_DHD0_DITHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 29  ; /* [28..0]  */
        unsigned int    dither_round          : 1   ; /* [29]  */
        unsigned int    dither_mode           : 1   ; /* [30]  */
        unsigned int    dither_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_DITHER_CTRL;

/* Define the union U_WBC_DHD0_DITHER_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef0          : 8   ; /* [7..0]  */
        unsigned int    dither_coef1          : 8   ; /* [15..8]  */
        unsigned int    dither_coef2          : 8   ; /* [23..16]  */
        unsigned int    dither_coef3          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_DITHER_COEF0;

/* Define the union U_WBC_DHD0_DITHER_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dither_coef4          : 8   ; /* [7..0]  */
        unsigned int    dither_coef5          : 8   ; /* [15..8]  */
        unsigned int    dither_coef6          : 8   ; /* [23..16]  */
        unsigned int    dither_coef7          : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_DITHER_COEF1;

/* Define the union U_WBC_DHD0_ZME_VINFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_height            : 12  ; /* [11..0]  */
        unsigned int    out_pro               : 1   ; /* [12]  */
        unsigned int    out_fld               : 1   ; /* [13]  */
        unsigned int    ck_gt_en              : 1   ; /* [14]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_VINFO;

/* Define the union U_WBC_DHD0_ZME_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 19  ; /* [18..0]  */
        unsigned int    zme_in_fmt            : 2   ; /* [20..19]  */
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

} U_WBC_DHD0_ZME_VSP;

/* Define the union U_WBC_DHD0_ZME_VSR */
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

} U_WBC_DHD0_ZME_VSR;

/* Define the union U_WBC_DHD0_ZME_VOFFSET */
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

} U_WBC_DHD0_ZME_VOFFSET;

/* Define the union U_WBC_DHD0_ZME_VBOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbchroma_offset       : 16  ; /* [15..0]  */
        unsigned int    vbluma_offset         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_VBOFFSET;

/* Define the union U_WBC_DHD0_ZME_VCOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_vhd_vf_cren       : 1   ; /* [0]  */
        unsigned int    apb_vhd_vf_lren       : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_ZME_VCOEF;

/* Define the union U_WBC_DHD0_ZME_VCOEFAD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int apb_vhd_vcoef_raddr    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_DHD0_ZME_VCOEFAD;
/* Define the union U_WBC_DHD0_FCROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wfcrop                : 12  ; /* [11..0]  */
        unsigned int    hfcrop                : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_FCROP;

/* Define the union U_WBC_DHD0_LCROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wlcrop                : 12  ; /* [11..0]  */
        unsigned int    hlcrop                : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_DHD0_LCROP;

/* Define the union U_GP0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    galpha                : 8   ; /* [7..0]  */
        unsigned int    alpha_thrd            : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 1   ; /* [16]  */
        unsigned int    bout_sel              : 2   ; /* [18..17]  */
        unsigned int    mux1_sel              : 2   ; /* [20..19]  */
        unsigned int    mux2_sel              : 2   ; /* [22..21]  */
        unsigned int    aout_sel              : 2   ; /* [24..23]  */
        unsigned int    ffc_sel               : 1   ; /* [25]  */
        unsigned int    gp_hdr_sel            : 1   ; /* [26]  */
        unsigned int    depremult_en          : 1   ; /* [27]  */
        unsigned int    rupd_field            : 1   ; /* [28]  */
        unsigned int    rgup_mode             : 1   ; /* [29]  */
        unsigned int    read_mode             : 1   ; /* [30]  */
        unsigned int    surface_en            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_CTRL;

/* Define the union U_GP0_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_UPD;

/* Define the union U_GP0_GALPHA_SUM */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int galpha_sum             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GP0_GALPHA_SUM;
/* Define the union U_GP0_ORESO_READ */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ow                    : 16  ; /* [15..0]  */
        unsigned int    oh                    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ORESO_READ;

/* Define the union U_GP0_IRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    iw                    : 16  ; /* [15..0]  */
        unsigned int    ih                    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_IRESO;

/* Define the union U_GP0_CTRL_WORK */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gp0_ctrl_work          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GP0_CTRL_WORK;
/* Define the union U_GP0_DFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xfpos            : 16  ; /* [15..0]  */
        unsigned int    disp_yfpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_DFPOS;

/* Define the union U_GP0_DLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_xlpos            : 16  ; /* [15..0]  */
        unsigned int    disp_ylpos            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_DLPOS;

/* Define the union U_GP0_VFPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xfpos           : 16  ; /* [15..0]  */
        unsigned int    video_yfpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_VFPOS;

/* Define the union U_GP0_VLPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_xlpos           : 16  ; /* [15..0]  */
        unsigned int    video_ylpos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_VLPOS;

/* Define the union U_GP0_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_cr                : 10  ; /* [9..0]  */
        unsigned int    vbk_cb                : 10  ; /* [19..10]  */
        unsigned int    vbk_y                 : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_BK;

/* Define the union U_GP0_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbk_alpha             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ALPHA;

/* Define the union U_GP0_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 1   ; /* [30]  */
        unsigned int    mute_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_MUTE_BK;

/* Define the union U_MIXG0_BKG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_bkgcr           : 10  ; /* [9..0]  */
        unsigned int    mixer_bkgcb           : 10  ; /* [19..10]  */
        unsigned int    mixer_bkgy            : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_BKG;

/* Define the union U_MIXG0_BKALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_alpha           : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_BKALPHA;

/* Define the union U_MIXG0_MIX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mixer_prio0           : 4   ; /* [3..0]  */
        unsigned int    mixer_prio1           : 4   ; /* [7..4]  */
        unsigned int    mixer_prio2           : 4   ; /* [11..8]  */
        unsigned int    mixer_prio3           : 4   ; /* [15..12]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MIXG0_MIX;

/* Define the union U_GP0_ZME_HINFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_width             : 16  ; /* [15..0]  */
        unsigned int    ck_gt_en              : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_HINFO;

/* Define the union U_GP0_ZME_HSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hratio                : 24  ; /* [23..0]  */
        unsigned int    hfir_order            : 1   ; /* [24]  */
        unsigned int    hafir_en              : 1   ; /* [25]  */
        unsigned int    hfir_en               : 1   ; /* [26]  */
        unsigned int    reserved_0            : 1   ; /* [27]  */
        unsigned int    hchmid_en             : 1   ; /* [28]  */
        unsigned int    hlmid_en              : 1   ; /* [29]  */
        unsigned int    hamid_en              : 1   ; /* [30]  */
        unsigned int    hsc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_HSP;

/* Define the union U_GP0_ZME_HLOFFSET */
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

} U_GP0_ZME_HLOFFSET;

/* Define the union U_GP0_ZME_HCOFFSET */
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

} U_GP0_ZME_HCOFFSET;

/* Define the union U_GP0_ZME_VINFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_height            : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 2   ; /* [17..16]  */
        unsigned int    out_pro               : 1   ; /* [18]  */
        unsigned int    reserved_1            : 13  ; /* [31..19]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_VINFO;

/* Define the union U_GP0_ZME_VSP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 23  ; /* [22..0]  */
        unsigned int    vafir_en              : 1   ; /* [23]  */
        unsigned int    vfir_en               : 1   ; /* [24]  */
        unsigned int    vfir_1tap_en          : 1   ; /* [25]  */
        unsigned int    vfir_2tap_en          : 1   ; /* [26]  */
        unsigned int    reserved_1            : 1   ; /* [27]  */
        unsigned int    vchmid_en             : 1   ; /* [28]  */
        unsigned int    vlmid_en              : 1   ; /* [29]  */
        unsigned int    vamid_en              : 1   ; /* [30]  */
        unsigned int    vsc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_VSP;

/* Define the union U_GP0_ZME_VSR */
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

} U_GP0_ZME_VSR;

/* Define the union U_GP0_ZME_VOFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbtm_offset           : 16  ; /* [15..0]  */
        unsigned int    vtp_offset            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZME_VOFFSET;

/* Define the union U_GP0_ZMECOEF */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_g0_lcti_vc_ren    : 1   ; /* [0]  */
        unsigned int    apb_g0_lcti_vl_ren    : 1   ; /* [1]  */
        unsigned int    apb_g0_lcti_hc_ren    : 1   ; /* [2]  */
        unsigned int    apb_g0_lcti_hl_ren    : 1   ; /* [3]  */
        unsigned int    apb_g0_vf_ren         : 1   ; /* [4]  */
        unsigned int    apb_g0_hf_ren_b       : 1   ; /* [5]  */
        unsigned int    apb_g0_hf_ren_a       : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZMECOEF;

/* Define the union U_GP0_ZMECOEFAD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apb_g0_coef_raddr     : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GP0_ZMECOEFAD;

/* Define the union U_SPCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    demo_en               : 1   ; /* [0]  */
        unsigned int    sharpen_en            : 1   ; /* [1]  */
        unsigned int    demo_mode             : 1   ; /* [2]  */
        unsigned int    demo_pos              : 16  ; /* [18..3]  */
        unsigned int    ensctrl               : 1   ; /* [19]  */
        unsigned int    peak_en               : 1   ; /* [20]  */
        unsigned int    detec_en              : 1   ; /* [21]  */
        unsigned int    hfreq_en_h            : 1   ; /* [22]  */
        unsigned int    hfreq_en_v            : 1   ; /* [23]  */
        unsigned int    hfreq_en_d            : 1   ; /* [24]  */
        unsigned int    shp_ck_gt_en          : 1   ; /* [25]  */
        unsigned int    winsize_h             : 3   ; /* [28..26]  */
        unsigned int    winsize_v             : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCTRL;

/* Define the union U_SPGAIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    peak_gain             : 10  ; /* [9..0]  */
        unsigned int    edge_gain             : 10  ; /* [19..10]  */
        unsigned int    dir_gain              : 8   ; /* [27..20]  */
        unsigned int    winsize_d             : 3   ; /* [30..28]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAIN;

/* Define the union U_SPPEAKSHOOTCTL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    peak_over_thr         : 8   ; /* [7..0]  */
        unsigned int    peak_under_thr        : 8   ; /* [15..8]  */
        unsigned int    peak_mixratio         : 8   ; /* [23..16]  */
        unsigned int    peak_coring           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPPEAKSHOOTCTL;

/* Define the union U_SPGAINPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_pos_h            : 9   ; /* [8..0]  */
        unsigned int    gain_pos_v            : 9   ; /* [17..9]  */
        unsigned int    gain_pos_d            : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINPOS;

/* Define the union U_SPGAINNEG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gain_neg_h            : 9   ; /* [8..0]  */
        unsigned int    gain_neg_v            : 9   ; /* [17..9]  */
        unsigned int    gain_neg_d            : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGAINNEG;

/* Define the union U_SPOVERTHR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    over_thr_h            : 8   ; /* [7..0]  */
        unsigned int    over_thr_v            : 8   ; /* [15..8]  */
        unsigned int    over_thr_d            : 8   ; /* [23..16]  */
        unsigned int    under_thr_h           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPOVERTHR;

/* Define the union U_SPUNDERTHR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    under_thr_v           : 8   ; /* [7..0]  */
        unsigned int    under_thr_d           : 8   ; /* [15..8]  */
        unsigned int    mixratio_h            : 8   ; /* [23..16]  */
        unsigned int    mixratio_v            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPUNDERTHR;

/* Define the union U_SPCORINGZERO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coringzero_h          : 8   ; /* [7..0]  */
        unsigned int    coringzero_v          : 8   ; /* [15..8]  */
        unsigned int    coringzero_d          : 8   ; /* [23..16]  */
        unsigned int    mixratio_d            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCORINGZERO;

/* Define the union U_SPCORINGRATIO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coringratio_h         : 5   ; /* [4..0]  */
        unsigned int    coringratio_v         : 5   ; /* [9..5]  */
        unsigned int    coringratio_d         : 5   ; /* [14..10]  */
        unsigned int    coringthr_h           : 8   ; /* [22..15]  */
        unsigned int    coringthr_v           : 8   ; /* [30..23]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPCORINGRATIO;

/* Define the union U_SPLMTRATIO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    limit_ratio_h         : 3   ; /* [2..0]  */
        unsigned int    limit_ratio_v         : 3   ; /* [5..3]  */
        unsigned int    limit_ratio_d         : 3   ; /* [8..6]  */
        unsigned int    coringthr_d           : 8   ; /* [16..9]  */
        unsigned int    gradcontrastthr       : 8   ; /* [24..17]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPLMTRATIO;

/* Define the union U_SPLMTPOS0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    limitpos0_h           : 8   ; /* [7..0]  */
        unsigned int    limitpos0_v           : 8   ; /* [15..8]  */
        unsigned int    limitpos0_d           : 8   ; /* [23..16]  */
        unsigned int    limitpos1_h           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPLMTPOS0;

/* Define the union U_SPBOUNDPOS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    boundpos_h            : 8   ; /* [7..0]  */
        unsigned int    boundpos_v            : 8   ; /* [15..8]  */
        unsigned int    boundpos_d            : 8   ; /* [23..16]  */
        unsigned int    limitpos1_v           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPBOUNDPOS;

/* Define the union U_SPLMTNEG0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    limitneg0_h           : 9   ; /* [8..0]  */
        unsigned int    limitneg0_v           : 9   ; /* [17..9]  */
        unsigned int    limitneg0_d           : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPLMTNEG0;

/* Define the union U_SPLMTNEG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    limitneg1_h           : 9   ; /* [8..0]  */
        unsigned int    limitneg1_v           : 9   ; /* [17..9]  */
        unsigned int    limitneg1_d           : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPLMTNEG1;

/* Define the union U_SPBOUNDNEG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    boundneg_h            : 9   ; /* [8..0]  */
        unsigned int    boundneg_v            : 9   ; /* [17..9]  */
        unsigned int    boundneg_d            : 9   ; /* [26..18]  */
        unsigned int    reserved_0            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPBOUNDNEG;

/* Define the union U_SPEDGESHOOTCTL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_over_thr         : 8   ; /* [7..0]  */
        unsigned int    edge_under_thr        : 8   ; /* [15..8]  */
        unsigned int    edge_mixratio         : 8   ; /* [23..16]  */
        unsigned int    limitpos1_d           : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPEDGESHOOTCTL;

/* Define the union U_SPEDGEEI */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    edge_ei0              : 8   ; /* [7..0]  */
        unsigned int    edge_ei1              : 8   ; /* [15..8]  */
        unsigned int    edge_eiratio          : 8   ; /* [23..16]  */
        unsigned int    ushootratioe          : 7   ; /* [30..24]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPEDGEEI;

/* Define the union U_SPGRADMIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gradminthrl           : 10  ; /* [9..0]  */
        unsigned int    gradminthrh           : 10  ; /* [19..10]  */
        unsigned int    gradminslop           : 8   ; /* [27..20]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRADMIN;

/* Define the union U_SPGRADCTR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gradminthr            : 10  ; /* [9..0]  */
        unsigned int    chessboardthr         : 16  ; /* [25..10]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPGRADCTR;

/* Define the union U_SPSHOOTRATIO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gradcontrastslop      : 9   ; /* [8..0]  */
        unsigned int    ushootratiot          : 7   ; /* [15..9]  */
        unsigned int    oshootratioe          : 7   ; /* [22..16]  */
        unsigned int    oshootratiot          : 7   ; /* [29..23]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SPSHOOTRATIO;

/* Define the union U_VHDACCTHD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    thd_low               : 10  ; /* [9..0]  */
        unsigned int    thd_high              : 10  ; /* [19..10]  */
        unsigned int    thd_med_low           : 10  ; /* [29..20]  */
        unsigned int    acc_mode              : 1   ; /* [30]  */
        unsigned int    acc_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCTHD1;

/* Define the union U_VHDACCTHD2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    thd_med_high          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    acc_rst               : 1   ; /* [12]  */
        unsigned int    ck_gt_en              : 1   ; /* [13]  */
        unsigned int    reserved_1            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCTHD2;

/* Define the union U_VHDACCDEMO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    demo_en               : 1   ; /* [0]  */
        unsigned int    demo_mode             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    demo_split_point      : 12  ; /* [15..4]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCDEMO;

/* Define the union U_VHDACCLOW1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    low_table_data0       : 10  ; /* [9..0]  */
        unsigned int    low_table_data1       : 10  ; /* [19..10]  */
        unsigned int    low_table_data2       : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCLOW1;

/* Define the union U_VHDACCLOW2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    low_table_data3       : 10  ; /* [9..0]  */
        unsigned int    low_table_data4       : 10  ; /* [19..10]  */
        unsigned int    low_table_data5       : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCLOW2;

/* Define the union U_VHDACCLOW3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    low_table_data6       : 10  ; /* [9..0]  */
        unsigned int    low_table_data7       : 10  ; /* [19..10]  */
        unsigned int    low_table_data8       : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCLOW3;

/* Define the union U_VHDACCMED1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mid_table_data0       : 10  ; /* [9..0]  */
        unsigned int    mid_table_data1       : 10  ; /* [19..10]  */
        unsigned int    mid_table_data2       : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCMED1;

/* Define the union U_VHDACCMED2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mid_table_data3       : 10  ; /* [9..0]  */
        unsigned int    mid_table_data4       : 10  ; /* [19..10]  */
        unsigned int    mid_table_data5       : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCMED2;

/* Define the union U_VHDACCMED3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mid_table_data6       : 10  ; /* [9..0]  */
        unsigned int    mid_table_data7       : 10  ; /* [19..10]  */
        unsigned int    mid_table_data8       : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCMED3;

/* Define the union U_VHDACCHIGH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    high_table_data0      : 10  ; /* [9..0]  */
        unsigned int    high_table_data1      : 10  ; /* [19..10]  */
        unsigned int    high_table_data2      : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCHIGH1;

/* Define the union U_VHDACCHIGH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    high_table_data3      : 10  ; /* [9..0]  */
        unsigned int    high_table_data4      : 10  ; /* [19..10]  */
        unsigned int    high_table_data5      : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCHIGH2;

/* Define the union U_VHDACCHIGH3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    high_table_data6      : 10  ; /* [9..0]  */
        unsigned int    high_table_data7      : 10  ; /* [19..10]  */
        unsigned int    high_table_data8      : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCHIGH3;

/* Define the union U_VHDACC3LOW */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt3_low              : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC3LOW;

/* Define the union U_VHDACC3MED */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt3_med              : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC3MED;

/* Define the union U_VHDACC3HIGH */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt3_high             : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC3HIGH;

/* Define the union U_VHDACCTOTAL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acc_pix_total         : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACCTOTAL;

/* Define the union U_VHDACC64HIST_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist0           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_0;

/* Define the union U_VHDACC64HIST_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist1           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_1;

/* Define the union U_VHDACC64HIST_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist2           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_2;

/* Define the union U_VHDACC64HIST_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist3           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_3;

/* Define the union U_VHDACC64HIST_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist4           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_4;

/* Define the union U_VHDACC64HIST_5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist5           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_5;

/* Define the union U_VHDACC64HIST_6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist6           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_6;

/* Define the union U_VHDACC64HIST_7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist7           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_7;

/* Define the union U_VHDACC64HIST_8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist8           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_8;

/* Define the union U_VHDACC64HIST_9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist9           : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_9;

/* Define the union U_VHDACC64HIST_10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist10          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_10;

/* Define the union U_VHDACC64HIST_11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist11          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_11;

/* Define the union U_VHDACC64HIST_12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist12          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_12;

/* Define the union U_VHDACC64HIST_13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist13          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_13;

/* Define the union U_VHDACC64HIST_14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist14          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_14;

/* Define the union U_VHDACC64HIST_15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist15          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_15;

/* Define the union U_VHDACC64HIST_16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist16          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_16;

/* Define the union U_VHDACC64HIST_17 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist17          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_17;

/* Define the union U_VHDACC64HIST_18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist18          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_18;

/* Define the union U_VHDACC64HIST_19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist19          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_19;

/* Define the union U_VHDACC64HIST_20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist20          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_20;

/* Define the union U_VHDACC64HIST_21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist21          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_21;

/* Define the union U_VHDACC64HIST_22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist22          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_22;

/* Define the union U_VHDACC64HIST_23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist23          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_23;

/* Define the union U_VHDACC64HIST_24 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist24          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_24;

/* Define the union U_VHDACC64HIST_25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist25          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_25;

/* Define the union U_VHDACC64HIST_26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist26          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_26;

/* Define the union U_VHDACC64HIST_27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist27          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_27;

/* Define the union U_VHDACC64HIST_28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist28          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_28;

/* Define the union U_VHDACC64HIST_29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist29          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_29;

/* Define the union U_VHDACC64HIST_30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist30          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_30;

/* Define the union U_VHDACC64HIST_31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist31          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_31;

/* Define the union U_VHDACC64HIST_32 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist32          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_32;

/* Define the union U_VHDACC64HIST_33 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist33          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_33;

/* Define the union U_VHDACC64HIST_34 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist34          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_34;

/* Define the union U_VHDACC64HIST_35 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist35          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_35;

/* Define the union U_VHDACC64HIST_36 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist36          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_36;

/* Define the union U_VHDACC64HIST_37 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist37          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_37;

/* Define the union U_VHDACC64HIST_38 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist38          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_38;

/* Define the union U_VHDACC64HIST_39 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist39          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_39;

/* Define the union U_VHDACC64HIST_40 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist40          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_40;

/* Define the union U_VHDACC64HIST_41 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist41          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_41;

/* Define the union U_VHDACC64HIST_42 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist42          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_42;

/* Define the union U_VHDACC64HIST_43 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist43          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_43;

/* Define the union U_VHDACC64HIST_44 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist44          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_44;

/* Define the union U_VHDACC64HIST_45 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist45          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_45;

/* Define the union U_VHDACC64HIST_46 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist46          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_46;

/* Define the union U_VHDACC64HIST_47 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist47          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_47;

/* Define the union U_VHDACC64HIST_48 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist48          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_48;

/* Define the union U_VHDACC64HIST_49 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist49          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_49;

/* Define the union U_VHDACC64HIST_50 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist50          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_50;

/* Define the union U_VHDACC64HIST_51 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist51          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_51;

/* Define the union U_VHDACC64HIST_52 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist52          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_52;

/* Define the union U_VHDACC64HIST_53 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist53          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_53;

/* Define the union U_VHDACC64HIST_54 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist54          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_54;

/* Define the union U_VHDACC64HIST_55 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist55          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_55;

/* Define the union U_VHDACC64HIST_56 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist56          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_56;

/* Define the union U_VHDACC64HIST_57 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist57          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_57;

/* Define the union U_VHDACC64HIST_58 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist58          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_58;

/* Define the union U_VHDACC64HIST_59 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist59          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_59;

/* Define the union U_VHDACC64HIST_60 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist60          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_60;

/* Define the union U_VHDACC64HIST_61 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist61          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_61;

/* Define the union U_VHDACC64HIST_62 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist62          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_62;

/* Define the union U_VHDACC64HIST_63 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cnt64_hist63          : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACC64HIST_63;

/* Define the union U_VDP_MST_OUTSTANDING */
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

} U_VDP_MST_OUTSTANDING;

/* Define the union U_VDP_MST_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    split_mode            : 4   ; /* [3..0]  */
        unsigned int    arb_mode              : 4   ; /* [7..4]  */
        unsigned int    mid_enable            : 1   ; /* [8]  */
        unsigned int    reserved_0            : 3   ; /* [11..9]  */
        unsigned int    wport_sel             : 4   ; /* [15..12]  */
        unsigned int    reserved_1            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VDP_MST_CTRL;

/* Define the union U_VDP_MST_RCHN_PRIO0 */
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

} U_VDP_MST_RCHN_PRIO0;

/* Define the union U_VDP_MST_WCHN_PRIO0 */
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

} U_VDP_MST_WCHN_PRIO0;

/* Define the union U_VDP_MST_BUS_ERR_CLR */
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

} U_VDP_MST_BUS_ERR_CLR;

/* Define the union U_VDP_MST_BUS_ERR */
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

} U_VDP_MST_BUS_ERR;

/* Define the union U_VDP_MST_SRC0_STATUS0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int src0_status0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VDP_MST_SRC0_STATUS0;
/* Define the union U_VDP_MST_SRC0_STATUS1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int src0_status1           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VDP_MST_SRC0_STATUS1;
/* Define the union U_VDP_MST_DEBUG_CTRL */
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

} U_VDP_MST_DEBUG_CTRL;

/* Define the union U_VDP_MST_DEBUG_CLR */
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

} U_VDP_MST_DEBUG_CLR;

/* Define the union U_VDP_MST0_DET_LATENCY */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int axi_mst0_latency       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VDP_MST0_DET_LATENCY;
/* Define the union U_VDP_MST0_RD_INFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mst0_rd_info           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VDP_MST0_RD_INFO;
/* Define the union U_VDP_MST0_WR_INFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mst0_wr_info           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VDP_MST0_WR_INFO;
/* Define the union U_VID_READ_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chm_rmode             : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    lm_rmode              : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 5   ; /* [11..7]  */
        unsigned int    flip_en               : 1   ; /* [12]  */
        unsigned int    chm_copy_en           : 1   ; /* [13]  */
        unsigned int    rmode_3d              : 1   ; /* [14]  */
        unsigned int    reserved_2            : 1   ; /* [15]  */
        unsigned int    mute_en               : 1   ; /* [16]  */
        unsigned int    mute_req_en           : 1   ; /* [17]  */
        unsigned int    vicap_mute_en         : 1   ; /* [18]  */
        unsigned int    mrg_enable            : 1   ; /* [19]  */
        unsigned int    fdr_ck_gt_en          : 1   ; /* [20]  */
        unsigned int    mrg_mute_mode         : 1   ; /* [21]  */
        unsigned int    reserved_3            : 2   ; /* [23..22]  */
        unsigned int    chm_draw_mode         : 3   ; /* [26..24]  */
        unsigned int    lm_draw_mode          : 3   ; /* [29..27]  */
        unsigned int    reserved_4            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_READ_CTRL;

/* Define the union U_VID_MAC_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_ctrl              : 2   ; /* [1..0]  */
        unsigned int    req_len               : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    ofl_master            : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    req_interval          : 12  ; /* [23..12]  */
        unsigned int    req_ld_mode           : 4   ; /* [27..24]  */
        unsigned int    reserved_2            : 3   ; /* [30..28]  */
        unsigned int    pre_rd_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_MAC_CTRL;

/* Define the union U_VID_OUT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    draw_pixel_mode       : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    uv_order_en           : 1   ; /* [4]  */
        unsigned int    single_port_mode      : 1   ; /* [5]  */
        unsigned int    testpattern_en        : 1   ; /* [6]  */
        unsigned int    dcmp_frm_max_en       : 1   ; /* [7]  */
        unsigned int    reserved_1            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_OUT_CTRL;

/* Define the union U_VID_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_MUTE_BK;

/* Define the union U_VID_SMMU_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lm_bypass_2d          : 1   ; /* [0]  */
        unsigned int    chm_bypass_2d         : 1   ; /* [1]  */
        unsigned int    lm_bypass_3d          : 1   ; /* [2]  */
        unsigned int    chm_bypass_3d         : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_SMMU_BYPASS;

/* Define the union U_VID_SRC_LFSIZE */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int y_frm_size             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_SRC_LFSIZE;
/* Define the union U_VID_SRC_CFSIZE */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_frm_size             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_SRC_CFSIZE;
/* Define the union U_VID_SRC_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    data_type             : 3   ; /* [2..0]  */
        unsigned int    data_fmt              : 2   ; /* [4..3]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    data_width            : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    field_type            : 1   ; /* [12]  */
        unsigned int    reserved_2            : 3   ; /* [15..13]  */
        unsigned int    disp_mode             : 4   ; /* [19..16]  */
        unsigned int    dcmp_type             : 2   ; /* [21..20]  */
        unsigned int    reserved_3            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_SRC_INFO;

/* Define the union U_VID_SRC_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_w                 : 16  ; /* [15..0]  */
        unsigned int    src_h                 : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_SRC_RESO;

/* Define the union U_VID_SRC_CROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_crop_x            : 16  ; /* [15..0]  */
        unsigned int    src_crop_y            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_SRC_CROP;

/* Define the union U_VID_IN_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ireso_w               : 16  ; /* [15..0]  */
        unsigned int    ireso_h               : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_IN_RESO;

/* Define the union U_VID_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdaddr_h              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_ADDR_H;
/* Define the union U_VID_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdaddr_l              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_ADDR_L;
/* Define the union U_VID_CADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdcaddr_h             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_CADDR_H;
/* Define the union U_VID_CADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdcaddr_l             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_CADDR_L;
/* Define the union U_VID_NADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdnaddr_h             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_NADDR_H;
/* Define the union U_VID_NADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdnaddr_l             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_NADDR_L;
/* Define the union U_VID_NCADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdncaddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_NCADDR_H;
/* Define the union U_VID_NCADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdncaddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_NCADDR_L;
/* Define the union U_VID_HEAD_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_vhdaddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_HEAD_ADDR_H;
/* Define the union U_VID_HEAD_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_vhdaddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_HEAD_ADDR_L;
/* Define the union U_VID_HEAD_CADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_vhdcaddr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_HEAD_CADDR_H;
/* Define the union U_VID_HEAD_CADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_vhdcaddr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_HEAD_CADDR_L;
/* Define the union U_VID_2BIT_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int b_vhdaddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_2BIT_ADDR_H;
/* Define the union U_VID_2BIT_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int b_vhdaddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_2BIT_ADDR_L;
/* Define the union U_VID_2BIT_CADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int b_vhdcaddr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_2BIT_CADDR_H;
/* Define the union U_VID_2BIT_CADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int b_vhdcaddr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_2BIT_CADDR_L;
/* Define the union U_VID_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lm_stride             : 16  ; /* [15..0]  */
        unsigned int    chm_stride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_STRIDE;

/* Define the union U_VID_2BIT_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lm_tile_stride        : 16  ; /* [15..0]  */
        unsigned int    chm_tile_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_2BIT_STRIDE;

/* Define the union U_VID_HEAD_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lm_head_stride        : 16  ; /* [15..0]  */
        unsigned int    chm_head_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_HEAD_STRIDE;

/* Define the union U_VID_TESTPAT_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tp_speed              : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    tp_line_w             : 1   ; /* [12]  */
        unsigned int    tp_color_mode         : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    tp_mode               : 2   ; /* [17..16]  */
        unsigned int    reserved_2            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_TESTPAT_CFG;

/* Define the union U_VID_TESTPAT_SEED */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tp_seed               : 30  ; /* [29..0]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_TESTPAT_SEED;

/* Define the union U_VID_DEBUG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    checksum_en           : 1   ; /* [0]  */
        unsigned int    fdr_press_en          : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DEBUG_CTRL;

/* Define the union U_VID_PRESS_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    min_nodrdy_num        : 8   ; /* [7..0]  */
        unsigned int    scope_nodrdy_num      : 8   ; /* [15..8]  */
        unsigned int    min_drdy_num          : 8   ; /* [23..16]  */
        unsigned int    scope_drdy_num        : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_PRESS_CTRL;

/* Define the union U_VID_TUNL_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tunl_interval         : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    tunl_thd              : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_TUNL_CTRL;

/* Define the union U_VID_TUNL_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tunl_addr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_TUNL_ADDR_H;
/* Define the union U_VID_TUNL_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tunl_addr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_TUNL_ADDR_L;
/* Define the union U_VID_IN_L_CHECKSUM0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_checksum0            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_IN_L_CHECKSUM0;
/* Define the union U_VID_IN_L_CHECKSUM1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_checksum1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_IN_L_CHECKSUM1;
/* Define the union U_VID_IN_C_CHECKSUM0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_checksum0            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_IN_C_CHECKSUM0;
/* Define the union U_VID_IN_C_CHECKSUM1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_checksum1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_IN_C_CHECKSUM1;
/* Define the union U_VID_L_FIFOSTA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_fifosta0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_L_FIFOSTA0;
/* Define the union U_VID_L_FIFOSTA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_fifo_total           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_L_FIFOSTA1;
/* Define the union U_VID_C_FIFOSTA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_fifosta0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_C_FIFOSTA0;
/* Define the union U_VID_C_FIFOSTA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_fifo_total           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_C_FIFOSTA1;
/* Define the union U_VID_L_CUR_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_cur_flow             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_L_CUR_FLOW;
/* Define the union U_VID_L_CUR_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_cur_sreq_time        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_L_CUR_SREQ_TIME;
/* Define the union U_VID_C_CUR_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_cur_flow             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_C_CUR_FLOW;
/* Define the union U_VID_C_CUR_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_cur_sreq_time        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_C_CUR_SREQ_TIME;
/* Define the union U_VID_L_LAST_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_last_flow            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_L_LAST_FLOW;
/* Define the union U_VID_L_LAST_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_last_sreq_time       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_L_LAST_SREQ_TIME;
/* Define the union U_VID_C_LAST_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_last_flow            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_C_LAST_FLOW;
/* Define the union U_VID_C_LAST_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_last_sreq_time       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_C_LAST_SREQ_TIME;
/* Define the union U_VID_WORK_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_width             : 16  ; /* [15..0]  */
        unsigned int    out_height            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_WORK_RESO;

/* Define the union U_VID_WORK_FINFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out_finfo              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_WORK_FINFO;
/* Define the union U_VID_LAST_YADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int y_last_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_LAST_YADDR;
/* Define the union U_VID_LAST_CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_last_caddr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_LAST_CADDR;
/* Define the union U_VID_WORK_READ_CTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_read_ctrl         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_WORK_READ_CTRL;
/* Define the union U_VID_WORK_SMMU_CTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_smmu_bypass       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_WORK_SMMU_CTRL;
/* Define the union U_VID_WORK_Y_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_y_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_WORK_Y_ADDR;
/* Define the union U_VID_WORK_C_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_c_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_WORK_C_ADDR;
/* Define the union U_VID_WORK_Y_NADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_y_naddr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_WORK_Y_NADDR;
/* Define the union U_VID_WORK_C_NADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_c_naddr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_WORK_C_NADDR;
/* Define the union U_VID_L_BUSY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_busy_time            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_L_BUSY_TIME;
/* Define the union U_VID_L_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_neednordy_time       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_L_NEEDNORDY_TIME;
/* Define the union U_VID_L2_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l2_neednordy_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_L2_NEEDNORDY_TIME;
/* Define the union U_VID_C_BUSY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_busy_time            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_C_BUSY_TIME;
/* Define the union U_VID_C_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_neednordy_time       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_C_NEEDNORDY_TIME;
/* Define the union U_VID_C2_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c2_neednordy_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_C2_NEEDNORDY_TIME;
/* Define the union U_VID_Y_DCMP_WRONG_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y_dcmp_err            : 1   ; /* [0]  */
        unsigned int    y_forgive             : 1   ; /* [1]  */
        unsigned int    y_consume             : 1   ; /* [2]  */
        unsigned int    y_bs_err              : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_Y_DCMP_WRONG_STA;

/* Define the union U_VID_C_DCMP_WRONG_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    c_dcmp_err            : 1   ; /* [0]  */
        unsigned int    c_forgive             : 1   ; /* [1]  */
        unsigned int    c_consume             : 1   ; /* [2]  */
        unsigned int    c_bs_err              : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_C_DCMP_WRONG_STA;

/* Define the union U_V1_VID_READ_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chm_rmode             : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    lm_rmode              : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 5   ; /* [11..7]  */
        unsigned int    flip_en               : 1   ; /* [12]  */
        unsigned int    chm_copy_en           : 1   ; /* [13]  */
        unsigned int    rmode_3d              : 1   ; /* [14]  */
        unsigned int    reserved_2            : 1   ; /* [15]  */
        unsigned int    mute_en               : 1   ; /* [16]  */
        unsigned int    mute_req_en           : 1   ; /* [17]  */
        unsigned int    vicap_mute_en         : 1   ; /* [18]  */
        unsigned int    mrg_enable            : 1   ; /* [19]  */
        unsigned int    fdr_ck_gt_en          : 1   ; /* [20]  */
        unsigned int    mrg_mute_mode         : 1   ; /* [21]  */
        unsigned int    reserved_3            : 2   ; /* [23..22]  */
        unsigned int    chm_draw_mode         : 3   ; /* [26..24]  */
        unsigned int    lm_draw_mode          : 3   ; /* [29..27]  */
        unsigned int    reserved_4            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_READ_CTRL;

/* Define the union U_V1_VID_MAC_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_ctrl              : 2   ; /* [1..0]  */
        unsigned int    req_len               : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    ofl_master            : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    req_interval          : 12  ; /* [23..12]  */
        unsigned int    req_ld_mode           : 4   ; /* [27..24]  */
        unsigned int    reserved_2            : 3   ; /* [30..28]  */
        unsigned int    pre_rd_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_MAC_CTRL;

/* Define the union U_V1_VID_OUT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    draw_pixel_mode       : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    uv_order_en           : 1   ; /* [4]  */
        unsigned int    single_port_mode      : 1   ; /* [5]  */
        unsigned int    testpattern_en        : 1   ; /* [6]  */
        unsigned int    dcmp_frm_max_en       : 1   ; /* [7]  */
        unsigned int    reserved_1            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_OUT_CTRL;

/* Define the union U_V1_VID_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_MUTE_BK;

/* Define the union U_V1_VID_SMMU_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lm_bypass_2d          : 1   ; /* [0]  */
        unsigned int    chm_bypass_2d         : 1   ; /* [1]  */
        unsigned int    lm_bypass_3d          : 1   ; /* [2]  */
        unsigned int    chm_bypass_3d         : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_SMMU_BYPASS;

/* Define the union U_V1_VID_SRC_LFSIZE */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int y_frm_size             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_SRC_LFSIZE;
/* Define the union U_V1_VID_SRC_CFSIZE */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_frm_size             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_SRC_CFSIZE;
/* Define the union U_V1_VID_SRC_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    data_type             : 3   ; /* [2..0]  */
        unsigned int    data_fmt              : 2   ; /* [4..3]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    data_width            : 2   ; /* [9..8]  */
        unsigned int    reserved_1            : 2   ; /* [11..10]  */
        unsigned int    field_type            : 1   ; /* [12]  */
        unsigned int    reserved_2            : 3   ; /* [15..13]  */
        unsigned int    disp_mode             : 4   ; /* [19..16]  */
        unsigned int    dcmp_type             : 2   ; /* [21..20]  */
        unsigned int    reserved_3            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_SRC_INFO;

/* Define the union U_V1_VID_SRC_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_w                 : 16  ; /* [15..0]  */
        unsigned int    src_h                 : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_SRC_RESO;

/* Define the union U_V1_VID_SRC_CROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_crop_x            : 16  ; /* [15..0]  */
        unsigned int    src_crop_y            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_SRC_CROP;

/* Define the union U_V1_VID_IN_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ireso_w               : 16  ; /* [15..0]  */
        unsigned int    ireso_h               : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_IN_RESO;

/* Define the union U_V1_VID_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdaddr_h              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_ADDR_H;
/* Define the union U_V1_VID_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdaddr_l              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_ADDR_L;
/* Define the union U_V1_VID_CADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdcaddr_h             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_CADDR_H;
/* Define the union U_V1_VID_CADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdcaddr_l             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_CADDR_L;
/* Define the union U_V1_VID_NADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdnaddr_h             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_NADDR_H;
/* Define the union U_V1_VID_NADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdnaddr_l             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_NADDR_L;
/* Define the union U_V1_VID_NCADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdncaddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_NCADDR_H;
/* Define the union U_V1_VID_NCADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdncaddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_NCADDR_L;
/* Define the union U_V1_VID_HEAD_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_vhdaddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_HEAD_ADDR_H;
/* Define the union U_V1_VID_HEAD_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_vhdaddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_HEAD_ADDR_L;
/* Define the union U_V1_VID_HEAD_CADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_vhdcaddr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_HEAD_CADDR_H;
/* Define the union U_V1_VID_HEAD_CADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_vhdcaddr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_HEAD_CADDR_L;
/* Define the union U_V1_VID_2BIT_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int b_vhdaddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_2BIT_ADDR_H;
/* Define the union U_V1_VID_2BIT_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int b_vhdaddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_2BIT_ADDR_L;
/* Define the union U_V1_VID_2BIT_CADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int b_vhdcaddr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_2BIT_CADDR_H;
/* Define the union U_V1_VID_2BIT_CADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int b_vhdcaddr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_2BIT_CADDR_L;
/* Define the union U_V1_VID_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lm_stride             : 16  ; /* [15..0]  */
        unsigned int    chm_stride            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_STRIDE;

/* Define the union U_V1_VID_2BIT_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lm_tile_stride        : 16  ; /* [15..0]  */
        unsigned int    chm_tile_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_2BIT_STRIDE;

/* Define the union U_V1_VID_HEAD_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lm_head_stride        : 16  ; /* [15..0]  */
        unsigned int    chm_head_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_HEAD_STRIDE;

/* Define the union U_V1_VID_TESTPAT_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tp_speed              : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    tp_line_w             : 1   ; /* [12]  */
        unsigned int    tp_color_mode         : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    tp_mode               : 2   ; /* [17..16]  */
        unsigned int    reserved_2            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_TESTPAT_CFG;

/* Define the union U_V1_VID_TESTPAT_SEED */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tp_seed               : 30  ; /* [29..0]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_TESTPAT_SEED;

/* Define the union U_V1_VID_DEBUG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    checksum_en           : 1   ; /* [0]  */
        unsigned int    fdr_press_en          : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_DEBUG_CTRL;

/* Define the union U_V1_VID_PRESS_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    min_nodrdy_num        : 8   ; /* [7..0]  */
        unsigned int    scope_nodrdy_num      : 8   ; /* [15..8]  */
        unsigned int    min_drdy_num          : 8   ; /* [23..16]  */
        unsigned int    scope_drdy_num        : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_PRESS_CTRL;

/* Define the union U_V1_VID_TUNL_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tunl_interval         : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 8   ; /* [15..8]  */
        unsigned int    tunl_thd              : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_TUNL_CTRL;

/* Define the union U_V1_VID_TUNL_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tunl_addr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_TUNL_ADDR_H;
/* Define the union U_V1_VID_TUNL_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tunl_addr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_TUNL_ADDR_L;
/* Define the union U_V1_VID_IN_L_CHECKSUM0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_checksum0            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_IN_L_CHECKSUM0;
/* Define the union U_V1_VID_IN_L_CHECKSUM1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_checksum1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_IN_L_CHECKSUM1;
/* Define the union U_V1_VID_IN_C_CHECKSUM0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_checksum0            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_IN_C_CHECKSUM0;
/* Define the union U_V1_VID_IN_C_CHECKSUM1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_checksum1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_IN_C_CHECKSUM1;
/* Define the union U_V1_VID_L_FIFOSTA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_fifosta0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_L_FIFOSTA0;
/* Define the union U_V1_VID_L_FIFOSTA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_fifo_total           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_L_FIFOSTA1;
/* Define the union U_V1_VID_C_FIFOSTA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_fifosta0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_C_FIFOSTA0;
/* Define the union U_V1_VID_C_FIFOSTA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_fifo_total           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_C_FIFOSTA1;
/* Define the union U_V1_VID_L_CUR_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_cur_flow             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_L_CUR_FLOW;
/* Define the union U_V1_VID_L_CUR_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_cur_sreq_time        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_L_CUR_SREQ_TIME;
/* Define the union U_V1_VID_C_CUR_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_cur_flow             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_C_CUR_FLOW;
/* Define the union U_V1_VID_C_CUR_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_cur_sreq_time        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_C_CUR_SREQ_TIME;
/* Define the union U_V1_VID_L_LAST_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_last_flow            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_L_LAST_FLOW;
/* Define the union U_V1_VID_L_LAST_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_last_sreq_time       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_L_LAST_SREQ_TIME;
/* Define the union U_V1_VID_C_LAST_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_last_flow            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_C_LAST_FLOW;
/* Define the union U_V1_VID_C_LAST_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_last_sreq_time       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_C_LAST_SREQ_TIME;
/* Define the union U_V1_VID_WORK_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_width             : 16  ; /* [15..0]  */
        unsigned int    out_height            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_VID_WORK_RESO;

/* Define the union U_V1_VID_WORK_FINFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out_finfo              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_WORK_FINFO;
/* Define the union U_V1_VID_LAST_YADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int y_last_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_LAST_YADDR;
/* Define the union U_V1_VID_LAST_CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_last_caddr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_LAST_CADDR;
/* Define the union U_V1_VID_WORK_READ_CTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_read_ctrl         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_WORK_READ_CTRL;
/* Define the union U_V1_VID_WORK_SMMU_CTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_smmu_bypass       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_WORK_SMMU_CTRL;
/* Define the union U_V1_VID_WORK_Y_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_y_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_WORK_Y_ADDR;
/* Define the union U_V1_VID_WORK_C_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_c_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_WORK_C_ADDR;
/* Define the union U_V1_VID_WORK_Y_NADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_y_naddr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_WORK_Y_NADDR;
/* Define the union U_V1_VID_WORK_C_NADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_c_naddr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_WORK_C_NADDR;
/* Define the union U_V1_VID_L_BUSY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_busy_time            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_L_BUSY_TIME;
/* Define the union U_V1_VID_L_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l_neednordy_time       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_L_NEEDNORDY_TIME;
/* Define the union U_V1_VID_L2_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int l2_neednordy_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_L2_NEEDNORDY_TIME;
/* Define the union U_V1_VID_C_BUSY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_busy_time            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_C_BUSY_TIME;
/* Define the union U_V1_VID_C_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c_neednordy_time       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_C_NEEDNORDY_TIME;
/* Define the union U_V1_VID_C2_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int c2_neednordy_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_VID_C2_NEEDNORDY_TIME;
/* Define the union U_HWLD_TOP_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 10  ; /* [9..0]  */
        unsigned int    gfx_succ_en           : 1   ; /* [10]  */
        unsigned int    gfx_bind_en           : 1   ; /* [11]  */
        unsigned int    reserved_1            : 2   ; /* [13..12]  */
        unsigned int    vid1_3_succ_en        : 1   ; /* [14]  */
        unsigned int    vid1_3_bind_en        : 1   ; /* [15]  */
        unsigned int    reserved_2            : 2   ; /* [17..16]  */
        unsigned int    vid1_2_succ_en        : 1   ; /* [18]  */
        unsigned int    vid1_2_bind_en        : 1   ; /* [19]  */
        unsigned int    reserved_3            : 2   ; /* [21..20]  */
        unsigned int    vid1_1_succ_en        : 1   ; /* [22]  */
        unsigned int    vid1_1_bind_en        : 1   ; /* [23]  */
        unsigned int    reserved_4            : 2   ; /* [25..24]  */
        unsigned int    vid1_succ_en          : 1   ; /* [26]  */
        unsigned int    vid1_bind_en          : 1   ; /* [27]  */
        unsigned int    reserved_5            : 2   ; /* [29..28]  */
        unsigned int    vid0_succ_en          : 1   ; /* [30]  */
        unsigned int    vid0_bind_en          : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HWLD_TOP_CTRL;

/* Define the union U_HWLD_TOP_REGUP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HWLD_TOP_REGUP;

/* Define the union U_HWLD_TOP_SMMU_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smmu_bypass           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HWLD_TOP_SMMU_BYPASS;

/* Define the union U_HWLD_TOP_DEBUG_STA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug_sta0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HWLD_TOP_DEBUG_STA0;
/* Define the union U_HWLD_TOP_DEBUG_STA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug_sta1             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HWLD_TOP_DEBUG_STA1;
/* Define the union U_HWLD_TOP_DEBUG_STA2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug_sta2             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HWLD_TOP_DEBUG_STA2;
/* Define the union U_HWLD_TOP_DEBUG_STA3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug_sta3             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_HWLD_TOP_DEBUG_STA3;
/* Define the union U_VID_DTV_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dtv_mode              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    frm_change_mode       : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_MODE;

/* Define the union U_VID_DTV_MODE_IMG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reset_en              : 1   ; /* [0]  */
        unsigned int    reset_mode            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_MODE_IMG;

/* Define the union U_VID_DTV_GLB_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lburst_num            : 16  ; /* [15..0]  */
        unsigned int    hburst_num            : 8   ; /* [23..16]  */
        unsigned int    burst_mask            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_GLB_FRM_INFO;

/* Define the union U_VID_DTV_LOC_FRM_INFO_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    write_ready           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_LOC_FRM_INFO_READY;

/* Define the union U_VID_DTV_LOC_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    top_disp_num          : 8   ; /* [7..0]  */
        unsigned int    btm_disp_num          : 8   ; /* [15..8]  */
        unsigned int    first_field_sel       : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_LOC_FRM_INFO;

/* Define the union U_VID_DTV_LOC_FRM_INFO1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_DTV_LOC_FRM_INFO1;
/* Define the union U_VID_DTV_BACK_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_DTV_BACK_ADDR;
/* Define the union U_VID_DTV_BACK_PSW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_password      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_DTV_BACK_PSW;
/* Define the union U_VID_DTV_CFG_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfg_ready             : 1   ; /* [0]  */
        unsigned int    mute_clr              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_CFG_READY;

/* Define the union U_VID_DTV_CHANGE_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_change_addr        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_DTV_CHANGE_ADDR;
/* Define the union U_VID_DTV_DISP_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_disp_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_DTV_DISP_ADDR;
/* Define the union U_VID_DTV_BACK_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    back_num              : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_BACK_NUM;

/* Define the union U_VID_DTV_ERR_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    send_err              : 1   ; /* [0]  */
        unsigned int    back_err              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_ERR_STA;

/* Define the union U_VID_DTV_DEBUG_CLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    debug_clr             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_DEBUG_CLR;

/* Define the union U_VID_DTV_DEBUG1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int disp_cnt               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_DTV_DEBUG1;
/* Define the union U_VID_DTV_DEBUG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_fifo_sta         : 8   ; /* [7..0]  */
        unsigned int    back_fifo_sta         : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VID_DTV_DEBUG2;

/* Define the union U_VID_DTV_DEBUG3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_sta          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_DTV_DEBUG3;
/* Define the union U_VID_DTV_DEBUG4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_cnt          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VID_DTV_DEBUG4;
/* Define the union U_V1_DTV_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dtv_mode              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    frm_change_mode       : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_MODE;

/* Define the union U_V1_DTV_MODE_IMG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reset_en              : 1   ; /* [0]  */
        unsigned int    reset_mode            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_MODE_IMG;

/* Define the union U_V1_DTV_GLB_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lburst_num            : 16  ; /* [15..0]  */
        unsigned int    hburst_num            : 8   ; /* [23..16]  */
        unsigned int    burst_mask            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_GLB_FRM_INFO;

/* Define the union U_V1_DTV_LOC_FRM_INFO_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    write_ready           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_LOC_FRM_INFO_READY;

/* Define the union U_V1_DTV_LOC_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    top_disp_num          : 8   ; /* [7..0]  */
        unsigned int    btm_disp_num          : 8   ; /* [15..8]  */
        unsigned int    first_field_sel       : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_LOC_FRM_INFO;

/* Define the union U_V1_DTV_LOC_FRM_INFO1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_DTV_LOC_FRM_INFO1;
/* Define the union U_V1_DTV_BACK_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_DTV_BACK_ADDR;
/* Define the union U_V1_DTV_BACK_PSW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_password      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_DTV_BACK_PSW;
/* Define the union U_V1_DTV_CFG_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfg_ready             : 1   ; /* [0]  */
        unsigned int    mute_clr              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_CFG_READY;

/* Define the union U_V1_DTV_CHANGE_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_change_addr        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_DTV_CHANGE_ADDR;
/* Define the union U_V1_DTV_DISP_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_disp_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_DTV_DISP_ADDR;
/* Define the union U_V1_DTV_BACK_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    back_num              : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_BACK_NUM;

/* Define the union U_V1_DTV_ERR_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    send_err              : 1   ; /* [0]  */
        unsigned int    back_err              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_ERR_STA;

/* Define the union U_V1_DTV_DEBUG_CLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    debug_clr             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_DEBUG_CLR;

/* Define the union U_V1_DTV_DEBUG1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int disp_cnt               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_DTV_DEBUG1;
/* Define the union U_V1_DTV_DEBUG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_fifo_sta         : 8   ; /* [7..0]  */
        unsigned int    back_fifo_sta         : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_DTV_DEBUG2;

/* Define the union U_V1_DTV_DEBUG3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_sta          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_DTV_DEBUG3;
/* Define the union U_V1_DTV_DEBUG4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_cnt          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_DTV_DEBUG4;
/* Define the union U_V1_1_DTV_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dtv_mode              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    frm_change_mode       : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_MODE;

/* Define the union U_V1_1_DTV_MODE_IMG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reset_en              : 1   ; /* [0]  */
        unsigned int    reset_mode            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_MODE_IMG;

/* Define the union U_V1_1_DTV_GLB_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lburst_num            : 16  ; /* [15..0]  */
        unsigned int    hburst_num            : 8   ; /* [23..16]  */
        unsigned int    burst_mask            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_GLB_FRM_INFO;

/* Define the union U_V1_1_DTV_LOC_FRM_INFO_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    write_ready           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_LOC_FRM_INFO_READY;

/* Define the union U_V1_1_DTV_LOC_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    top_disp_num          : 8   ; /* [7..0]  */
        unsigned int    btm_disp_num          : 8   ; /* [15..8]  */
        unsigned int    first_field_sel       : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_LOC_FRM_INFO;

/* Define the union U_V1_1_DTV_LOC_FRM_INFO1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_1_DTV_LOC_FRM_INFO1;
/* Define the union U_V1_1_DTV_BACK_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_1_DTV_BACK_ADDR;
/* Define the union U_V1_1_DTV_BACK_PSW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_password      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_1_DTV_BACK_PSW;
/* Define the union U_V1_1_DTV_CFG_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfg_ready             : 1   ; /* [0]  */
        unsigned int    mute_clr              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_CFG_READY;

/* Define the union U_V1_1_DTV_CHANGE_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_change_addr        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_1_DTV_CHANGE_ADDR;
/* Define the union U_V1_1_DTV_DISP_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_disp_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_1_DTV_DISP_ADDR;
/* Define the union U_V1_1_DTV_BACK_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    back_num              : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_BACK_NUM;

/* Define the union U_V1_1_DTV_ERR_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    send_err              : 1   ; /* [0]  */
        unsigned int    back_err              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_ERR_STA;

/* Define the union U_V1_1_DTV_DEBUG_CLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    debug_clr             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_DEBUG_CLR;

/* Define the union U_V1_1_DTV_DEBUG1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int disp_cnt               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_1_DTV_DEBUG1;
/* Define the union U_V1_1_DTV_DEBUG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_fifo_sta         : 8   ; /* [7..0]  */
        unsigned int    back_fifo_sta         : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_1_DTV_DEBUG2;

/* Define the union U_V1_1_DTV_DEBUG3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_sta          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_1_DTV_DEBUG3;
/* Define the union U_V1_1_DTV_DEBUG4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_cnt          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_1_DTV_DEBUG4;
/* Define the union U_V1_2_DTV_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dtv_mode              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    frm_change_mode       : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_MODE;

/* Define the union U_V1_2_DTV_MODE_IMG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reset_en              : 1   ; /* [0]  */
        unsigned int    reset_mode            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_MODE_IMG;

/* Define the union U_V1_2_DTV_GLB_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lburst_num            : 16  ; /* [15..0]  */
        unsigned int    hburst_num            : 8   ; /* [23..16]  */
        unsigned int    burst_mask            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_GLB_FRM_INFO;

/* Define the union U_V1_2_DTV_LOC_FRM_INFO_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    write_ready           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_LOC_FRM_INFO_READY;

/* Define the union U_V1_2_DTV_LOC_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    top_disp_num          : 8   ; /* [7..0]  */
        unsigned int    btm_disp_num          : 8   ; /* [15..8]  */
        unsigned int    first_field_sel       : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_LOC_FRM_INFO;

/* Define the union U_V1_2_DTV_LOC_FRM_INFO1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_2_DTV_LOC_FRM_INFO1;
/* Define the union U_V1_2_DTV_BACK_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_2_DTV_BACK_ADDR;
/* Define the union U_V1_2_DTV_BACK_PSW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_password      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_2_DTV_BACK_PSW;
/* Define the union U_V1_2_DTV_CFG_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfg_ready             : 1   ; /* [0]  */
        unsigned int    mute_clr              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_CFG_READY;

/* Define the union U_V1_2_DTV_CHANGE_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_change_addr        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_2_DTV_CHANGE_ADDR;
/* Define the union U_V1_2_DTV_DISP_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_disp_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_2_DTV_DISP_ADDR;
/* Define the union U_V1_2_DTV_BACK_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    back_num              : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_BACK_NUM;

/* Define the union U_V1_2_DTV_ERR_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    send_err              : 1   ; /* [0]  */
        unsigned int    back_err              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_ERR_STA;

/* Define the union U_V1_2_DTV_DEBUG_CLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    debug_clr             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_DEBUG_CLR;

/* Define the union U_V1_2_DTV_DEBUG1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int disp_cnt               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_2_DTV_DEBUG1;
/* Define the union U_V1_2_DTV_DEBUG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_fifo_sta         : 8   ; /* [7..0]  */
        unsigned int    back_fifo_sta         : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_2_DTV_DEBUG2;

/* Define the union U_V1_2_DTV_DEBUG3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_sta          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_2_DTV_DEBUG3;
/* Define the union U_V1_2_DTV_DEBUG4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_cnt          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_2_DTV_DEBUG4;
/* Define the union U_V1_3_DTV_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dtv_mode              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    frm_change_mode       : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_MODE;

/* Define the union U_V1_3_DTV_MODE_IMG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reset_en              : 1   ; /* [0]  */
        unsigned int    reset_mode            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_MODE_IMG;

/* Define the union U_V1_3_DTV_GLB_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lburst_num            : 16  ; /* [15..0]  */
        unsigned int    hburst_num            : 8   ; /* [23..16]  */
        unsigned int    burst_mask            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_GLB_FRM_INFO;

/* Define the union U_V1_3_DTV_LOC_FRM_INFO_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    write_ready           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_LOC_FRM_INFO_READY;

/* Define the union U_V1_3_DTV_LOC_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    top_disp_num          : 8   ; /* [7..0]  */
        unsigned int    btm_disp_num          : 8   ; /* [15..8]  */
        unsigned int    first_field_sel       : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_LOC_FRM_INFO;

/* Define the union U_V1_3_DTV_LOC_FRM_INFO1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_3_DTV_LOC_FRM_INFO1;
/* Define the union U_V1_3_DTV_BACK_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_3_DTV_BACK_ADDR;
/* Define the union U_V1_3_DTV_BACK_PSW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_password      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_3_DTV_BACK_PSW;
/* Define the union U_V1_3_DTV_CFG_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfg_ready             : 1   ; /* [0]  */
        unsigned int    mute_clr              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_CFG_READY;

/* Define the union U_V1_3_DTV_CHANGE_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_change_addr        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_3_DTV_CHANGE_ADDR;
/* Define the union U_V1_3_DTV_DISP_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_disp_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_3_DTV_DISP_ADDR;
/* Define the union U_V1_3_DTV_BACK_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    back_num              : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_BACK_NUM;

/* Define the union U_V1_3_DTV_ERR_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    send_err              : 1   ; /* [0]  */
        unsigned int    back_err              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_ERR_STA;

/* Define the union U_V1_3_DTV_DEBUG_CLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    debug_clr             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_DEBUG_CLR;

/* Define the union U_V1_3_DTV_DEBUG1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int disp_cnt               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_3_DTV_DEBUG1;
/* Define the union U_V1_3_DTV_DEBUG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_fifo_sta         : 8   ; /* [7..0]  */
        unsigned int    back_fifo_sta         : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_3_DTV_DEBUG2;

/* Define the union U_V1_3_DTV_DEBUG3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_sta          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_3_DTV_DEBUG3;
/* Define the union U_V1_3_DTV_DEBUG4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_cnt          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_3_DTV_DEBUG4;
/* Define the union U_GFX_DTV_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dtv_mode              : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    frm_change_mode       : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_MODE;

/* Define the union U_GFX_DTV_MODE_IMG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reset_en              : 1   ; /* [0]  */
        unsigned int    reset_mode            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_MODE_IMG;

/* Define the union U_GFX_DTV_GLB_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    lburst_num            : 16  ; /* [15..0]  */
        unsigned int    hburst_num            : 8   ; /* [23..16]  */
        unsigned int    burst_mask            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_GLB_FRM_INFO;

/* Define the union U_GFX_DTV_LOC_FRM_INFO_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    write_ready           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_LOC_FRM_INFO_READY;

/* Define the union U_GFX_DTV_LOC_FRM_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    top_disp_num          : 8   ; /* [7..0]  */
        unsigned int    btm_disp_num          : 8   ; /* [15..8]  */
        unsigned int    first_field_sel       : 1   ; /* [16]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_LOC_FRM_INFO;

/* Define the union U_GFX_DTV_LOC_FRM_INFO1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_cfg_addr           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DTV_LOC_FRM_INFO1;
/* Define the union U_GFX_DTV_BACK_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DTV_BACK_ADDR;
/* Define the union U_GFX_DTV_BACK_PSW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_back_password      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DTV_BACK_PSW;
/* Define the union U_GFX_DTV_CFG_READY */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cfg_ready             : 1   ; /* [0]  */
        unsigned int    mute_clr              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_CFG_READY;

/* Define the union U_GFX_DTV_CHANGE_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_change_addr        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DTV_CHANGE_ADDR;
/* Define the union U_GFX_DTV_DISP_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dtv_disp_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DTV_DISP_ADDR;
/* Define the union U_GFX_DTV_BACK_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    back_num              : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_BACK_NUM;

/* Define the union U_GFX_DTV_ERR_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    send_err              : 1   ; /* [0]  */
        unsigned int    back_err              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_ERR_STA;

/* Define the union U_GFX_DTV_DEBUG_CLR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    debug_clr             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_DEBUG_CLR;

/* Define the union U_GFX_DTV_DEBUG1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int disp_cnt               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DTV_DEBUG1;
/* Define the union U_GFX_DTV_DEBUG2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    disp_fifo_sta         : 8   ; /* [7..0]  */
        unsigned int    back_fifo_sta         : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DTV_DEBUG2;

/* Define the union U_GFX_DTV_DEBUG3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_sta          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DTV_DEBUG3;
/* Define the union U_GFX_DTV_DEBUG4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int underload_cnt          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DTV_DEBUG4;
/* Define the union U_GFX_READ_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    read_mode             : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    draw_mode             : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    flip_en               : 1   ; /* [8]  */
        unsigned int    rmode_3d              : 1   ; /* [9]  */
        unsigned int    mute_en               : 1   ; /* [10]  */
        unsigned int    mute_req_en           : 1   ; /* [11]  */
        unsigned int    fdr_ck_gt_en          : 1   ; /* [12]  */
        unsigned int    addr_map_en           : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_READ_CTRL;

/* Define the union U_GFX_MAC_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_ctrl              : 2   ; /* [1..0]  */
        unsigned int    req_len               : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    ofl_master            : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    req_interval          : 12  ; /* [23..12]  */
        unsigned int    req_ld_mode           : 2   ; /* [25..24]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_MAC_CTRL;

/* Define the union U_GFX_OUT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    palpha_range          : 1   ; /* [0]  */
        unsigned int    palpha_en             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    key_mode              : 1   ; /* [4]  */
        unsigned int    key_en                : 1   ; /* [5]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    bitext                : 2   ; /* [9..8]  */
        unsigned int    premulti_en           : 1   ; /* [10]  */
        unsigned int    testpattern_en        : 1   ; /* [11]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_OUT_CTRL;

/* Define the union U_GFX_MUTE_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_alpha            : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_MUTE_ALPHA;

/* Define the union U_GFX_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_MUTE_BK;

/* Define the union U_GFX_SMMU_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smmu_bypass_2d        : 1   ; /* [0]  */
        unsigned int    smmu_bypass_3d        : 1   ; /* [1]  */
        unsigned int    smmu_bypass_h2d       : 1   ; /* [2]  */
        unsigned int    smmu_bypass_h3d       : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_SMMU_BYPASS;

/* Define the union U_GFX_1555_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    alpha_0               : 8   ; /* [7..0]  */
        unsigned int    alpha_1               : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_1555_ALPHA;

/* Define the union U_GFX_DCMP_FRAMESIZE0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int frame_size0            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DCMP_FRAMESIZE0;
/* Define the union U_GFX_DCMP_FRAMESIZE1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int frame_size1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DCMP_FRAMESIZE1;
/* Define the union U_GFX_SRC_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ifmt                  : 8   ; /* [7..0]  */
        unsigned int    typ                   : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    disp_mode             : 4   ; /* [19..16]  */
        unsigned int    dcmp_type             : 2   ; /* [21..20]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_SRC_INFO;

/* Define the union U_GFX_SRC_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_w                 : 16  ; /* [15..0]  */
        unsigned int    src_h                 : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_SRC_RESO;

/* Define the union U_GFX_SRC_CROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_crop_x            : 16  ; /* [15..0]  */
        unsigned int    src_crop_y            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_SRC_CROP;

/* Define the union U_GFX_IRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ireso_w               : 16  ; /* [15..0]  */
        unsigned int    ireso_h               : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_IRESO;

/* Define the union U_GFX_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_addr_h             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_ADDR_H;
/* Define the union U_GFX_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_addr_l             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_ADDR_L;
/* Define the union U_GFX_NADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_naddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_NADDR_H;
/* Define the union U_GFX_NADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_naddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_NADDR_L;
/* Define the union U_GFX_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    dcmp_stride           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_STRIDE;

/* Define the union U_GFX_DCMP_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_addr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DCMP_ADDR_H;
/* Define the union U_GFX_DCMP_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_addr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DCMP_ADDR_L;
/* Define the union U_GFX_DCMP_NADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_naddr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DCMP_NADDR_H;
/* Define the union U_GFX_DCMP_NADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_naddr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_DCMP_NADDR_L;
/* Define the union U_GFX_HEAD_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_addr_h               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_HEAD_ADDR_H;
/* Define the union U_GFX_HEAD_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_addr_l               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_HEAD_ADDR_L;
/* Define the union U_GFX_HEAD_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    head_stride           : 16  ; /* [15..0]  */
        unsigned int    head2_stride          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_HEAD_STRIDE;

/* Define the union U_GFX_HEAD2_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h2_addr_h              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_HEAD2_ADDR_H;
/* Define the union U_GFX_HEAD2_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h2_addr_l              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_HEAD2_ADDR_L;
/* Define the union U_GFX_CKEY_MAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    key_b_max             : 8   ; /* [7..0]  */
        unsigned int    key_g_max             : 8   ; /* [15..8]  */
        unsigned int    key_r_max             : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_CKEY_MAX;

/* Define the union U_GFX_CKEY_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    key_b_min             : 8   ; /* [7..0]  */
        unsigned int    key_g_min             : 8   ; /* [15..8]  */
        unsigned int    key_r_min             : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_CKEY_MIN;

/* Define the union U_GFX_CKEY_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    key_b_msk             : 8   ; /* [7..0]  */
        unsigned int    key_g_msk             : 8   ; /* [15..8]  */
        unsigned int    key_r_msk             : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_CKEY_MASK;

/* Define the union U_GFX_TESTPAT_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tp_speed              : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    tp_line_w             : 1   ; /* [12]  */
        unsigned int    tp_color_mode         : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    tp_mode               : 2   ; /* [17..16]  */
        unsigned int    reserved_2            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_TESTPAT_CFG;

/* Define the union U_GFX_TESTPAT_SEED */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tp_seed               : 30  ; /* [29..0]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_TESTPAT_SEED;

/* Define the union U_GFX_DEBUG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    checksum_en           : 1   ; /* [0]  */
        unsigned int    fdr_press_en          : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_DEBUG_CTRL;

/* Define the union U_GFX_PRESS_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    min_nodrdy_num        : 8   ; /* [7..0]  */
        unsigned int    scope_nodrdy_num      : 8   ; /* [15..8]  */
        unsigned int    min_drdy_num          : 8   ; /* [23..16]  */
        unsigned int    scope_drdy_num        : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_PRESS_CTRL;

/* Define the union U_GFX_IN_AR_CHECKSUM0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ar_checksum0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_IN_AR_CHECKSUM0;
/* Define the union U_GFX_IN_AR_CHECKSUM1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ar_checksum1           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_IN_AR_CHECKSUM1;
/* Define the union U_GFX_IN_GB_CHECKSUM0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gb_checksum0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_IN_GB_CHECKSUM0;
/* Define the union U_GFX_IN_GB_CHECKSUM1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gb_checksum1           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_IN_GB_CHECKSUM1;
/* Define the union U_GFX_CHN0_FIFOSTA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chn0_fifosta0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_CHN0_FIFOSTA0;
/* Define the union U_GFX_CHN0_FIFOSTA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chn0_fifo_total        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_CHN0_FIFOSTA1;
/* Define the union U_GFX_CHN1_FIFOSTA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chn1_fifosta0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_CHN1_FIFOSTA0;
/* Define the union U_GFX_CHN1_FIFOSTA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chn1_fifo_total        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_CHN1_FIFOSTA1;
/* Define the union U_GFX_CUR_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_cur_flow           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_CUR_FLOW;
/* Define the union U_GFX_CUR_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_cur_sreq_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_CUR_SREQ_TIME;
/* Define the union U_GFX_LAST_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_last_flow          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_LAST_FLOW;
/* Define the union U_GFX_LAST_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_last_sreq_time     : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_LAST_SREQ_TIME;
/* Define the union U_GFX_BUSY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_busy_time          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_BUSY_TIME;
/* Define the union U_GFX_AR_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ar_neednordy_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_AR_NEEDNORDY_TIME;
/* Define the union U_GFX_GB_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gb_neednordy_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_GB_NEEDNORDY_TIME;
/* Define the union U_GFX_WORK_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_width             : 16  ; /* [15..0]  */
        unsigned int    out_height            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GFX_WORK_RESO;

/* Define the union U_GFX_WORK_FINFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out_finfo              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_WORK_FINFO;
/* Define the union U_GFX_LAST_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_last_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_LAST_ADDR;
/* Define the union U_GFX_WORK_READ_CTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_read_ctrl         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_WORK_READ_CTRL;
/* Define the union U_GFX_WORK_SMMU_CTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_smmu_bypass       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_WORK_SMMU_CTRL;
/* Define the union U_GFX_WORK_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_WORK_ADDR;
/* Define the union U_GFX_WORK_NADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_naddr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GFX_WORK_NADDR;
/* Define the union U_DCMP_WRONG_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    forgive_ar            : 1   ; /* [0]  */
        unsigned int    consume_ar            : 1   ; /* [1]  */
        unsigned int    wrong_ar              : 1   ; /* [2]  */
        unsigned int    forgive_gb            : 1   ; /* [3]  */
        unsigned int    consume_gb            : 1   ; /* [4]  */
        unsigned int    wrong_gb              : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DCMP_WRONG_STA;

/* Define the union U_DCMP_DEBUG_STA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ar_debug0              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DCMP_DEBUG_STA0;
/* Define the union U_DCMP_DEBUG_STA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ar_debug1              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DCMP_DEBUG_STA1;
/* Define the union U_DCMP_DEBUG_STA2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gb_debug0              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DCMP_DEBUG_STA2;
/* Define the union U_DCMP_DEBUG_STA3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gb_debug1              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DCMP_DEBUG_STA3;
/* Define the union U_G1_GFX_READ_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    read_mode             : 2   ; /* [1..0]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    draw_mode             : 2   ; /* [5..4]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    flip_en               : 1   ; /* [8]  */
        unsigned int    rmode_3d              : 1   ; /* [9]  */
        unsigned int    mute_en               : 1   ; /* [10]  */
        unsigned int    mute_req_en           : 1   ; /* [11]  */
        unsigned int    fdr_ck_gt_en          : 1   ; /* [12]  */
        unsigned int    addr_map_en           : 1   ; /* [13]  */
        unsigned int    reserved_2            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_READ_CTRL;

/* Define the union U_G1_GFX_MAC_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_ctrl              : 2   ; /* [1..0]  */
        unsigned int    req_len               : 2   ; /* [3..2]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    ofl_master            : 1   ; /* [8]  */
        unsigned int    reserved_1            : 3   ; /* [11..9]  */
        unsigned int    req_interval          : 12  ; /* [23..12]  */
        unsigned int    req_ld_mode           : 2   ; /* [25..24]  */
        unsigned int    reserved_2            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_MAC_CTRL;

/* Define the union U_G1_GFX_OUT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    palpha_range          : 1   ; /* [0]  */
        unsigned int    palpha_en             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    key_mode              : 1   ; /* [4]  */
        unsigned int    key_en                : 1   ; /* [5]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    bitext                : 2   ; /* [9..8]  */
        unsigned int    premulti_en           : 1   ; /* [10]  */
        unsigned int    testpattern_en        : 1   ; /* [11]  */
        unsigned int    reserved_2            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_OUT_CTRL;

/* Define the union U_G1_GFX_MUTE_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_alpha            : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_MUTE_ALPHA;

/* Define the union U_G1_GFX_MUTE_BK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mute_cr               : 10  ; /* [9..0]  */
        unsigned int    mute_cb               : 10  ; /* [19..10]  */
        unsigned int    mute_y                : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_MUTE_BK;

/* Define the union U_G1_GFX_SMMU_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    smmu_bypass_2d        : 1   ; /* [0]  */
        unsigned int    smmu_bypass_3d        : 1   ; /* [1]  */
        unsigned int    smmu_bypass_h2d       : 1   ; /* [2]  */
        unsigned int    smmu_bypass_h3d       : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_SMMU_BYPASS;

/* Define the union U_G1_GFX_1555_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    alpha_0               : 8   ; /* [7..0]  */
        unsigned int    alpha_1               : 8   ; /* [15..8]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_1555_ALPHA;

/* Define the union U_G1_GFX_DCMP_FRAMESIZE0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int frame_size0            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_DCMP_FRAMESIZE0;
/* Define the union U_G1_GFX_DCMP_FRAMESIZE1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int frame_size1            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_DCMP_FRAMESIZE1;
/* Define the union U_G1_GFX_SRC_INFO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ifmt                  : 8   ; /* [7..0]  */
        unsigned int    typ                   : 4   ; /* [11..8]  */
        unsigned int    reserved_0            : 4   ; /* [15..12]  */
        unsigned int    disp_mode             : 4   ; /* [19..16]  */
        unsigned int    dcmp_type             : 2   ; /* [21..20]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_SRC_INFO;

/* Define the union U_G1_GFX_SRC_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_w                 : 16  ; /* [15..0]  */
        unsigned int    src_h                 : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_SRC_RESO;

/* Define the union U_G1_GFX_SRC_CROP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    src_crop_x            : 16  ; /* [15..0]  */
        unsigned int    src_crop_y            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_SRC_CROP;

/* Define the union U_G1_GFX_IRESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ireso_w               : 16  ; /* [15..0]  */
        unsigned int    ireso_h               : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_IRESO;

/* Define the union U_G1_GFX_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_addr_h             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_ADDR_H;
/* Define the union U_G1_GFX_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_addr_l             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_ADDR_L;
/* Define the union U_G1_GFX_NADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_naddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_NADDR_H;
/* Define the union U_G1_GFX_NADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_naddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_NADDR_L;
/* Define the union U_G1_GFX_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    surface_stride        : 16  ; /* [15..0]  */
        unsigned int    dcmp_stride           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_STRIDE;

/* Define the union U_G1_GFX_DCMP_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_addr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_DCMP_ADDR_H;
/* Define the union U_G1_GFX_DCMP_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_addr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_DCMP_ADDR_L;
/* Define the union U_G1_GFX_DCMP_NADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_naddr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_DCMP_NADDR_H;
/* Define the union U_G1_GFX_DCMP_NADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int dcmp_naddr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_DCMP_NADDR_L;
/* Define the union U_G1_GFX_HEAD_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_addr_h               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_HEAD_ADDR_H;
/* Define the union U_G1_GFX_HEAD_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h_addr_l               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_HEAD_ADDR_L;
/* Define the union U_G1_GFX_HEAD_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    head_stride           : 16  ; /* [15..0]  */
        unsigned int    head2_stride          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_HEAD_STRIDE;

/* Define the union U_G1_GFX_HEAD2_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h2_addr_h              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_HEAD2_ADDR_H;
/* Define the union U_G1_GFX_HEAD2_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int h2_addr_l              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_HEAD2_ADDR_L;
/* Define the union U_G1_GFX_CKEY_MAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    key_b_max             : 8   ; /* [7..0]  */
        unsigned int    key_g_max             : 8   ; /* [15..8]  */
        unsigned int    key_r_max             : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_CKEY_MAX;

/* Define the union U_G1_GFX_CKEY_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    key_b_min             : 8   ; /* [7..0]  */
        unsigned int    key_g_min             : 8   ; /* [15..8]  */
        unsigned int    key_r_min             : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_CKEY_MIN;

/* Define the union U_G1_GFX_CKEY_MASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    key_b_msk             : 8   ; /* [7..0]  */
        unsigned int    key_g_msk             : 8   ; /* [15..8]  */
        unsigned int    key_r_msk             : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_CKEY_MASK;

/* Define the union U_G1_GFX_TESTPAT_CFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tp_speed              : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    tp_line_w             : 1   ; /* [12]  */
        unsigned int    tp_color_mode         : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    tp_mode               : 2   ; /* [17..16]  */
        unsigned int    reserved_2            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_TESTPAT_CFG;

/* Define the union U_G1_GFX_TESTPAT_SEED */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tp_seed               : 30  ; /* [29..0]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_TESTPAT_SEED;

/* Define the union U_G1_GFX_DEBUG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    checksum_en           : 1   ; /* [0]  */
        unsigned int    fdr_press_en          : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_DEBUG_CTRL;

/* Define the union U_G1_GFX_PRESS_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    min_nodrdy_num        : 8   ; /* [7..0]  */
        unsigned int    scope_nodrdy_num      : 8   ; /* [15..8]  */
        unsigned int    min_drdy_num          : 8   ; /* [23..16]  */
        unsigned int    scope_drdy_num        : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_PRESS_CTRL;

/* Define the union U_G1_GFX_IN_AR_CHECKSUM0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ar_checksum0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_IN_AR_CHECKSUM0;
/* Define the union U_G1_GFX_IN_AR_CHECKSUM1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ar_checksum1           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_IN_AR_CHECKSUM1;
/* Define the union U_G1_GFX_IN_GB_CHECKSUM0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gb_checksum0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_IN_GB_CHECKSUM0;
/* Define the union U_G1_GFX_IN_GB_CHECKSUM1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gb_checksum1           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_IN_GB_CHECKSUM1;
/* Define the union U_G1_GFX_CHN0_FIFOSTA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chn0_fifosta0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_CHN0_FIFOSTA0;
/* Define the union U_G1_GFX_CHN0_FIFOSTA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chn0_fifo_total        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_CHN0_FIFOSTA1;
/* Define the union U_G1_GFX_CHN1_FIFOSTA0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chn1_fifosta0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_CHN1_FIFOSTA0;
/* Define the union U_G1_GFX_CHN1_FIFOSTA1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chn1_fifo_total        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_CHN1_FIFOSTA1;
/* Define the union U_G1_GFX_CUR_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_cur_flow           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_CUR_FLOW;
/* Define the union U_G1_GFX_CUR_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_cur_sreq_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_CUR_SREQ_TIME;
/* Define the union U_G1_GFX_LAST_FLOW */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_last_flow          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_LAST_FLOW;
/* Define the union U_G1_GFX_LAST_SREQ_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_last_sreq_time     : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_LAST_SREQ_TIME;
/* Define the union U_G1_GFX_BUSY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_busy_time          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_BUSY_TIME;
/* Define the union U_G1_GFX_AR_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ar_neednordy_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_AR_NEEDNORDY_TIME;
/* Define the union U_G1_GFX_GB_NEEDNORDY_TIME */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gb_neednordy_time      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_GB_NEEDNORDY_TIME;
/* Define the union U_G1_GFX_WORK_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    out_width             : 16  ; /* [15..0]  */
        unsigned int    out_height            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_G1_GFX_WORK_RESO;

/* Define the union U_G1_GFX_WORK_FINFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int out_finfo              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_WORK_FINFO;
/* Define the union U_G1_GFX_LAST_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gfx_last_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_LAST_ADDR;
/* Define the union U_G1_GFX_WORK_READ_CTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_read_ctrl         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_WORK_READ_CTRL;
/* Define the union U_G1_GFX_WORK_SMMU_CTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_smmu_bypass       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_WORK_SMMU_CTRL;
/* Define the union U_G1_GFX_WORK_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_WORK_ADDR;
/* Define the union U_G1_GFX_WORK_NADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_naddr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_G1_GFX_WORK_NADDR;
/* Define the union U_WBC_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_fmt               : 4   ; /* [3..0]  */
        unsigned int    data_width            : 1   ; /* [4]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    uv_order              : 1   ; /* [8]  */
        unsigned int    flip_en               : 1   ; /* [9]  */
        unsigned int    reserved_1            : 1   ; /* [10]  */
        unsigned int    chksum_en             : 1   ; /* [11]  */
        unsigned int    wbc_3d_mode           : 2   ; /* [13..12]  */
        unsigned int    cap_ck_gt_en          : 1   ; /* [14]  */
        unsigned int    reserved_2            : 14  ; /* [28..15]  */
        unsigned int    wbc_cmp_en            : 1   ; /* [29]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_CTRL;

/* Define the union U_WBC_MAC_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_interval          : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 2   ; /* [11..10]  */
        unsigned int    wbc_len               : 2   ; /* [13..12]  */
        unsigned int    reserved_1            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_MAC_CTRL;

/* Define the union U_WBC_SMMU_BYPASS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mmu_2d_bypass         : 1   ; /* [0]  */
        unsigned int    mmu_3d_bypass         : 1   ; /* [1]  */
        unsigned int    stt_bypass            : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_SMMU_BYPASS;

/* Define the union U_WBC_LOWDLYCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wb_per_line_num       : 12  ; /* [11..0]  */
        unsigned int    partfns_line_num      : 12  ; /* [23..12]  */
        unsigned int    reserved_0            : 6   ; /* [29..24]  */
        unsigned int    lowdly_test           : 1   ; /* [30]  */
        unsigned int    lowdly_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_LOWDLYCTRL;

/* Define the union U_WBC_TUNLADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_tunladdr_h         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_TUNLADDR_H;
/* Define the union U_WBC_TUNLADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_tunladdr_l         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_TUNLADDR_L;
/* Define the union U_WBC_LOWDLYSTA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 31  ; /* [30..0]  */
        unsigned int    part_finish           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_LOWDLYSTA;

/* Define the union U_WBC_YADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_yaddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_YADDR_H;
/* Define the union U_WBC_YADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_yaddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_YADDR_L;
/* Define the union U_WBC_CADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_caddr_h            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_CADDR_H;
/* Define the union U_WBC_CADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_caddr_l            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_CADDR_L;
/* Define the union U_WBC_YSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_ystride           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_YSTRIDE;

/* Define the union U_WBC_CSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_cstride           : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_CSTRIDE;

/* Define the union U_WBC_YNADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_ynaddr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_YNADDR_H;
/* Define the union U_WBC_YNADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_ynaddr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_YNADDR_L;
/* Define the union U_WBC_CNADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_cnaddr_h           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_CNADDR_H;
/* Define the union U_WBC_CNADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_cnaddr_l           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_CNADDR_L;
/* Define the union U_WBC_YNSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_ynstride          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_YNSTRIDE;

/* Define the union U_WBC_CNSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_cnstride          : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_CNSTRIDE;

/* Define the union U_WBC_STT_ADDR_H */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_stt_addr_h         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_STT_ADDR_H;
/* Define the union U_WBC_STT_ADDR_L */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int wbc_stt_addr_l         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_STT_ADDR_L;
/* Define the union U_WBC_STA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_l_busy            : 1   ; /* [0]  */
        unsigned int    wbc_c_busy            : 1   ; /* [1]  */
        unsigned int    wbc_lh_busy           : 1   ; /* [2]  */
        unsigned int    wbc_ch_busy           : 1   ; /* [3]  */
        unsigned int    stt_busy              : 1   ; /* [4]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_STA;

/* Define the union U_WBC_LINE_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wbc_l_linenum         : 16  ; /* [15..0]  */
        unsigned int    wbc_c_linenum         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_LINE_NUM;

/* Define the union U_WBC_CAP_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cap_width             : 16  ; /* [15..0]  */
        unsigned int    cap_height            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_WBC_CAP_RESO;

/* Define the union U_WBC_CAP_INFO */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cap_info_h             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_CAP_INFO;
/* Define the union U_WBC_CAP_INFO1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cap_info_l             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_CAP_INFO1;
/* Define the union U_WBC_CAP_CHKSUM */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cap_y_chksum           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_CAP_CHKSUM;
/* Define the union U_WBC_CAP_CHKSUM1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cap_c_chksum           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_CAP_CHKSUM1;
/* Define the union U_WBC_WORK_CTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_wbc_ctrl          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_WORK_CTRL;
/* Define the union U_WBC_WORK_YADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_wbc_yaddr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_WORK_YADDR;
/* Define the union U_WBC_WORK_CADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_wbc_caddr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_WORK_CADDR;
/* Define the union U_WBC_WORK_SMMU */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_wbc_smmu          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_WORK_SMMU;
/* Define the union U_WBC_WORK_LOWDLYCTRL */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_wbc_lowdlyctrl    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_WBC_WORK_LOWDLYCTRL;
/* Define the union U_V1_MRG_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 20  ; /* [19..0]  */
        unsigned int    mrg_edge_en           : 1   ; /* [20]  */
        unsigned int    reserved_1            : 4   ; /* [24..21]  */
        unsigned int    mrg_edge_typ          : 1   ; /* [25]  */
        unsigned int    mrg_chm_mmu_bypass    : 1   ; /* [26]  */
        unsigned int    mrg_lm_mmu_bypass     : 1   ; /* [27]  */
        unsigned int    mrg_crop_en           : 1   ; /* [28]  */
        unsigned int    reserved_2            : 1   ; /* [29]  */
        unsigned int    mrg_mute_en           : 1   ; /* [30]  */
        unsigned int    mrg_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_CTRL;

/* Define the union U_V1_MRG_DISP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_xpos              : 16  ; /* [15..0]  */
        unsigned int    mrg_ypos              : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_DISP_POS;

/* Define the union U_V1_MRG_DISP_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_width             : 16  ; /* [15..0]  */
        unsigned int    mrg_height            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_DISP_RESO;

/* Define the union U_V1_MRG_SRC_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_src_width         : 16  ; /* [15..0]  */
        unsigned int    mrg_src_height        : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_SRC_RESO;

/* Define the union U_V1_MRG_SRC_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_src_hoffset       : 16  ; /* [15..0]  */
        unsigned int    mrg_src_voffset       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_SRC_OFFSET;

/* Define the union U_V1_MRG_Y_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_y_addr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_Y_ADDR;
/* Define the union U_V1_MRG_C_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_c_addr             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_C_ADDR;
/* Define the union U_V1_MRG_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_c_stride          : 16  ; /* [15..0]  */
        unsigned int    mrg_y_stride          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_STRIDE;

/* Define the union U_V1_MRG_YH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_yh_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_YH_ADDR;
/* Define the union U_V1_MRG_CH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_ch_addr            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_CH_ADDR;
/* Define the union U_V1_MRG_HSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_ch_stride         : 16  ; /* [15..0]  */
        unsigned int    mrg_yh_stride         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_HSTRIDE;

/* Define the union U_V1_MRG_READ_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd_region             : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 23  ; /* [30..8]  */
        unsigned int    load_mode             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_READ_CTRL;

/* Define the union U_V1_MRG_READ_EN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rd_en                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_READ_EN;

/* Define the union U_V1_MRG_DEBUG_INFO0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug_info0            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_DEBUG_INFO0;
/* Define the union U_V1_MRG_WORK_EN */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_en                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_EN;
/* Define the union U_V1_MRG_WORK_MUTE */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_mute              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_MUTE;
/* Define the union U_V1_MRG_WORK_R0_DPOS0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_r0_dpos0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_R0_DPOS0;
/* Define the union U_V1_MRG_WORK_R0_DPOS1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_r0_dpos1          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_R0_DPOS1;
/* Define the union U_V1_MRG_WORK_R1_DPOS0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_r1_dpos0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_R1_DPOS0;
/* Define the union U_V1_MRG_WORK_R1_DPOS1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_r1_dpos1          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_R1_DPOS1;
/* Define the union U_V1_MRG_WORK_R2_DPOS0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_r2_dpos0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_R2_DPOS0;
/* Define the union U_V1_MRG_WORK_R2_DPOS1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_r2_dpos1          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_R2_DPOS1;
/* Define the union U_V1_MRG_WORK_R3_DPOS0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_r3_dpos0          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_R3_DPOS0;
/* Define the union U_V1_MRG_WORK_R3_DPOS1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_r3_dpos1          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_WORK_R3_DPOS1;
/* Define the union U_V1_MRG_R0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 20  ; /* [19..0]  */
        unsigned int    mrg_r0_edge_en        : 1   ; /* [20]  */
        unsigned int    reserved_1            : 4   ; /* [24..21]  */
        unsigned int    mrg_r0_edge_typ       : 1   ; /* [25]  */
        unsigned int    mrg_r0_chm_mmu_bypass : 1   ; /* [26]  */
        unsigned int    mrg_r0_lm_mmu_bypass  : 1   ; /* [27]  */
        unsigned int    mrg_r0_crop_en        : 1   ; /* [28]  */
        unsigned int    reserved_2            : 1   ; /* [29]  */
        unsigned int    mrg_r0_mute_en        : 1   ; /* [30]  */
        unsigned int    mrg_r0_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R0_CTRL;

/* Define the union U_V1_MRG_R0_DISP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r0_xpos           : 16  ; /* [15..0]  */
        unsigned int    mrg_r0_ypos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R0_DISP_POS;

/* Define the union U_V1_MRG_R0_DISP_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r0_width          : 16  ; /* [15..0]  */
        unsigned int    mrg_r0_height         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R0_DISP_RESO;

/* Define the union U_V1_MRG_R0_SRC_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r0_src_width      : 16  ; /* [15..0]  */
        unsigned int    mrg_r0_src_height     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R0_SRC_RESO;

/* Define the union U_V1_MRG_R0_SRC_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r0_src_hoffset    : 16  ; /* [15..0]  */
        unsigned int    mrg_r0_src_voffset    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R0_SRC_OFFSET;

/* Define the union U_V1_MRG_R0_Y_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r0_y_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R0_Y_ADDR;
/* Define the union U_V1_MRG_R0_C_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r0_c_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R0_C_ADDR;
/* Define the union U_V1_MRG_R0_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r0_c_stride       : 16  ; /* [15..0]  */
        unsigned int    mrg_r0_y_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R0_STRIDE;

/* Define the union U_V1_MRG_R0_YH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r0_yh_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R0_YH_ADDR;
/* Define the union U_V1_MRG_R0_CH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r0_ch_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R0_CH_ADDR;
/* Define the union U_V1_MRG_R0_HSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r0_ch_stride      : 16  ; /* [15..0]  */
        unsigned int    mrg_r0_yh_stride      : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R0_HSTRIDE;

/* Define the union U_V1_MRG_R1_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 20  ; /* [19..0]  */
        unsigned int    mrg_r1_edge_en        : 1   ; /* [20]  */
        unsigned int    reserved_1            : 4   ; /* [24..21]  */
        unsigned int    mrg_r1_edge_typ       : 1   ; /* [25]  */
        unsigned int    mrg_r1_chm_mmu_bypass : 1   ; /* [26]  */
        unsigned int    mrg_r1_lm_mmu_bypass  : 1   ; /* [27]  */
        unsigned int    mrg_r1_crop_en        : 1   ; /* [28]  */
        unsigned int    reserved_2            : 1   ; /* [29]  */
        unsigned int    mrg_r1_mute_en        : 1   ; /* [30]  */
        unsigned int    mrg_r1_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R1_CTRL;

/* Define the union U_V1_MRG_R1_DISP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r1_xpos           : 16  ; /* [15..0]  */
        unsigned int    mrg_r1_ypos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R1_DISP_POS;

/* Define the union U_V1_MRG_R1_DISP_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r1_width          : 16  ; /* [15..0]  */
        unsigned int    mrg_r1_height         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R1_DISP_RESO;

/* Define the union U_V1_MRG_R1_SRC_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r1_src_width      : 16  ; /* [15..0]  */
        unsigned int    mrg_r1_src_height     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R1_SRC_RESO;

/* Define the union U_V1_MRG_R1_SRC_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r1_src_hoffset    : 16  ; /* [15..0]  */
        unsigned int    mrg_r1_src_voffset    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R1_SRC_OFFSET;

/* Define the union U_V1_MRG_R1_Y_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r1_y_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R1_Y_ADDR;
/* Define the union U_V1_MRG_R1_C_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r1_c_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R1_C_ADDR;
/* Define the union U_V1_MRG_R1_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r1_c_stride       : 16  ; /* [15..0]  */
        unsigned int    mrg_r1_y_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R1_STRIDE;

/* Define the union U_V1_MRG_R1_YH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r1_yh_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R1_YH_ADDR;
/* Define the union U_V1_MRG_R1_CH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r1_ch_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R1_CH_ADDR;
/* Define the union U_V1_MRG_R1_HSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r1_ch_stride      : 16  ; /* [15..0]  */
        unsigned int    mrg_r1_yh_stride      : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R1_HSTRIDE;

/* Define the union U_V1_MRG_R2_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 20  ; /* [19..0]  */
        unsigned int    mrg_r2_edge_en        : 1   ; /* [20]  */
        unsigned int    reserved_1            : 4   ; /* [24..21]  */
        unsigned int    mrg_r2_edge_typ       : 1   ; /* [25]  */
        unsigned int    mrg_r2_chm_mmu_bypass : 1   ; /* [26]  */
        unsigned int    mrg_r2_lm_mmu_bypass  : 1   ; /* [27]  */
        unsigned int    mrg_r2_crop_en        : 1   ; /* [28]  */
        unsigned int    reserved_2            : 1   ; /* [29]  */
        unsigned int    mrg_r2_mute_en        : 1   ; /* [30]  */
        unsigned int    mrg_r2_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R2_CTRL;

/* Define the union U_V1_MRG_R2_DISP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r2_xpos           : 16  ; /* [15..0]  */
        unsigned int    mrg_r2_ypos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R2_DISP_POS;

/* Define the union U_V1_MRG_R2_DISP_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r2_width          : 16  ; /* [15..0]  */
        unsigned int    mrg_r2_height         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R2_DISP_RESO;

/* Define the union U_V1_MRG_R2_SRC_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r2_src_width      : 16  ; /* [15..0]  */
        unsigned int    mrg_r2_src_height     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R2_SRC_RESO;

/* Define the union U_V1_MRG_R2_SRC_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r2_src_hoffset    : 16  ; /* [15..0]  */
        unsigned int    mrg_r2_src_voffset    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R2_SRC_OFFSET;

/* Define the union U_V1_MRG_R2_Y_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r2_y_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R2_Y_ADDR;
/* Define the union U_V1_MRG_R2_C_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r2_c_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R2_C_ADDR;
/* Define the union U_V1_MRG_R2_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r2_c_stride       : 16  ; /* [15..0]  */
        unsigned int    mrg_r2_y_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R2_STRIDE;

/* Define the union U_V1_MRG_R2_YH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r2_yh_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R2_YH_ADDR;
/* Define the union U_V1_MRG_R2_CH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r2_ch_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R2_CH_ADDR;
/* Define the union U_V1_MRG_R2_HSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r2_ch_stride      : 16  ; /* [15..0]  */
        unsigned int    mrg_r2_yh_stride      : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R2_HSTRIDE;

/* Define the union U_V1_MRG_R3_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 20  ; /* [19..0]  */
        unsigned int    mrg_r3_edge_en        : 1   ; /* [20]  */
        unsigned int    reserved_1            : 4   ; /* [24..21]  */
        unsigned int    mrg_r3_edge_typ       : 1   ; /* [25]  */
        unsigned int    mrg_r3_chm_mmu_bypass : 1   ; /* [26]  */
        unsigned int    mrg_r3_lm_mmu_bypass  : 1   ; /* [27]  */
        unsigned int    mrg_r3_crop_en        : 1   ; /* [28]  */
        unsigned int    reserved_2            : 1   ; /* [29]  */
        unsigned int    mrg_r3_mute_en        : 1   ; /* [30]  */
        unsigned int    mrg_r3_en             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R3_CTRL;

/* Define the union U_V1_MRG_R3_DISP_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r3_xpos           : 16  ; /* [15..0]  */
        unsigned int    mrg_r3_ypos           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R3_DISP_POS;

/* Define the union U_V1_MRG_R3_DISP_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r3_width          : 16  ; /* [15..0]  */
        unsigned int    mrg_r3_height         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R3_DISP_RESO;

/* Define the union U_V1_MRG_R3_SRC_RESO */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r3_src_width      : 16  ; /* [15..0]  */
        unsigned int    mrg_r3_src_height     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R3_SRC_RESO;

/* Define the union U_V1_MRG_R3_SRC_OFFSET */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r3_src_hoffset    : 16  ; /* [15..0]  */
        unsigned int    mrg_r3_src_voffset    : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R3_SRC_OFFSET;

/* Define the union U_V1_MRG_R3_Y_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r3_y_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R3_Y_ADDR;
/* Define the union U_V1_MRG_R3_C_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r3_c_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R3_C_ADDR;
/* Define the union U_V1_MRG_R3_STRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r3_c_stride       : 16  ; /* [15..0]  */
        unsigned int    mrg_r3_y_stride       : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R3_STRIDE;

/* Define the union U_V1_MRG_R3_YH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r3_yh_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R3_YH_ADDR;
/* Define the union U_V1_MRG_R3_CH_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int mrg_r3_ch_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_V1_MRG_R3_CH_ADDR;
/* Define the union U_V1_MRG_R3_HSTRIDE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mrg_r3_ch_stride      : 16  ; /* [15..0]  */
        unsigned int    mrg_r3_yh_stride      : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_V1_MRG_R3_HSTRIDE;

/* Define the union U_MSREQ_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sreq_delay            : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 18  ; /* [25..8]  */
        unsigned int    smd_valid             : 1   ; /* [26]  */
        unsigned int    avi_valid             : 1   ; /* [27]  */
        unsigned int    reserved_1            : 1   ; /* [28]  */
        unsigned int    mmu_bypass            : 1   ; /* [29]  */
        unsigned int    nosec_flag            : 1   ; /* [30]  */
        unsigned int    chn_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MSREQ_CTRL;

/* Define the union U_MSREQ_RUPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MSREQ_RUPD;

/* Define the union U_MSREQ_ADDR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int maddr                  : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_MSREQ_ADDR;
/* Define the union U_MSREQ_BURST */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mburst                : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MSREQ_BURST;

/* Define the union U_MSREQ_DEBUG0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int work_addr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_MSREQ_DEBUG0;
/* Define the union U_MSREQ_DEBUG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    send_num              : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_MSREQ_DEBUG1;

/* Define the union U_MSREQ_DEBUG2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int debug_sta              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_MSREQ_DEBUG2;
/* Define the union U_HIHDR_V_YUV2RGB_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_en          : 1   ; /* [0]  */
        unsigned int    hihdr_y2r_ck_gt_en    : 1   ; /* [1]  */
        unsigned int    hihdr_v0_cl_en        : 1   ; /* [2]  */
        unsigned int    hihdr_v1_cl_en        : 1   ; /* [3]  */
        unsigned int    hihdr_v0_y2r_en       : 1   ; /* [4]  */
        unsigned int    hihdr_v1_y2r_en       : 1   ; /* [5]  */
        unsigned int    hihdr_v0_vhdr_en      : 1   ; /* [6]  */
        unsigned int    hihdr_v1_vhdr_en      : 1   ; /* [7]  */
        unsigned int    reserved_0            : 4   ; /* [11..8]  */
        unsigned int    hihdr_v_demo_en       : 1   ; /* [12]  */
        unsigned int    hihdr_v_demo_mode     : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    hihdr_v_demo_pos      : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_CTRL;

/* Define the union U_HIHDR_V_YUV2RGB_COEF00 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef00      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF00;

/* Define the union U_HIHDR_V_YUV2RGB_COEF01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef01      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF01;

/* Define the union U_HIHDR_V_YUV2RGB_COEF02 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef02      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF02;

/* Define the union U_HIHDR_V_YUV2RGB_COEF03 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef03      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF03;

/* Define the union U_HIHDR_V_YUV2RGB_COEF04 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef04      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF04;

/* Define the union U_HIHDR_V_YUV2RGB_COEF05 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef05      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF05;

/* Define the union U_HIHDR_V_YUV2RGB_COEF06 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef06      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF06;

/* Define the union U_HIHDR_V_YUV2RGB_COEF07 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef07      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF07;

/* Define the union U_HIHDR_V_YUV2RGB_COEF08 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef08      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF08;

/* Define the union U_HIHDR_V_YUV2RGB_COEF10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef10      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF10;

/* Define the union U_HIHDR_V_YUV2RGB_COEF11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef11      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF11;

/* Define the union U_HIHDR_V_YUV2RGB_COEF12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef12      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF12;

/* Define the union U_HIHDR_V_YUV2RGB_COEF13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef13      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF13;

/* Define the union U_HIHDR_V_YUV2RGB_COEF14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef14      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF14;

/* Define the union U_HIHDR_V_YUV2RGB_COEF15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef15      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF15;

/* Define the union U_HIHDR_V_YUV2RGB_COEF16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef16      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF16;

/* Define the union U_HIHDR_V_YUV2RGB_COEF17 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef17      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF17;

/* Define the union U_HIHDR_V_YUV2RGB_COEF18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_coef18      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_COEF18;

/* Define the union U_HIHDR_V_YUV2RGB_SCALE2P */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_v0_scale2p  : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    hihdr_y2r_v1_scale2p  : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    reserved_2            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_SCALE2P;

/* Define the union U_HIHDR_V_YUV2RGB_IN_DC00 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_idc00       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_IN_DC00;

/* Define the union U_HIHDR_V_YUV2RGB_IN_DC01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_idc01       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_IN_DC01;

/* Define the union U_HIHDR_V_YUV2RGB_IN_DC02 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_idc02       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_IN_DC02;

/* Define the union U_HIHDR_V_YUV2RGB_OUT_DC00 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_odc00       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_OUT_DC00;

/* Define the union U_HIHDR_V_YUV2RGB_OUT_DC01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_odc01       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_OUT_DC01;

/* Define the union U_HIHDR_V_YUV2RGB_OUT_DC02 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_odc02       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_OUT_DC02;

/* Define the union U_HIHDR_V_YUV2RGB_IN_DC10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_idc10       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_IN_DC10;

/* Define the union U_HIHDR_V_YUV2RGB_IN_DC11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_idc11       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_IN_DC11;

/* Define the union U_HIHDR_V_YUV2RGB_IN_DC12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_idc12       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_IN_DC12;

/* Define the union U_HIHDR_V_YUV2RGB_OUT_DC10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_odc10       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_OUT_DC10;

/* Define the union U_HIHDR_V_YUV2RGB_OUT_DC11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_odc11       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_OUT_DC11;

/* Define the union U_HIHDR_V_YUV2RGB_OUT_DC12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_odc12       : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_OUT_DC12;

/* Define the union U_HIHDR_V_YUV2RGB_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_v0_clip_min : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    hihdr_y2r_v1_clip_min : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_MIN;

/* Define the union U_HIHDR_V_YUV2RGB_MAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_y2r_v0_clip_max : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    hihdr_y2r_v1_clip_max : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_V_YUV2RGB_MAX;

/* Define the union U_VHDR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_en               : 1   ; /* [0]  */
        unsigned int    vhdr_gamut_bind       : 1   ; /* [1]  */
        unsigned int    vhdr_ck_gt_en         : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_CTRL;

/* Define the union U_VHDR_DEGAMMA_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_degmm_en         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_CTRL;

/* Define the union U_VHDR_DEGAMMA_REN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_degamma_rd_en    : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_REN;

/* Define the union U_VHDR_DEGAMMA_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdr_degamma_para_data : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VHDR_DEGAMMA_DATA;
/* Define the union U_VHDR_DEGAMMA_STEP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_degmm_x1_step       : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 5   ; /* [7..3]  */
        unsigned int    v_degmm_x2_step       : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 5   ; /* [15..11]  */
        unsigned int    v_degmm_x3_step       : 3   ; /* [18..16]  */
        unsigned int    reserved_2            : 5   ; /* [23..19]  */
        unsigned int    v_degmm_x4_step       : 3   ; /* [26..24]  */
        unsigned int    reserved_3            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_STEP1;

/* Define the union U_VHDR_DEGAMMA_STEP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_degmm_x5_step       : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 5   ; /* [7..3]  */
        unsigned int    v_degmm_x6_step       : 3   ; /* [10..8]  */
        unsigned int    reserved_1            : 5   ; /* [15..11]  */
        unsigned int    v_degmm_x7_step       : 3   ; /* [18..16]  */
        unsigned int    reserved_2            : 5   ; /* [23..19]  */
        unsigned int    v_degmm_x8_step       : 3   ; /* [26..24]  */
        unsigned int    reserved_3            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_STEP2;

/* Define the union U_VHDR_DEGAMMA_POS1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_degmm_x1_pos        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    v_degmm_x2_pos        : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_POS1;

/* Define the union U_VHDR_DEGAMMA_POS2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_degmm_x3_pos        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    v_degmm_x4_pos        : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_POS2;

/* Define the union U_VHDR_DEGAMMA_POS3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_degmm_x5_pos        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    v_degmm_x6_pos        : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_POS3;

/* Define the union U_VHDR_DEGAMMA_POS4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_degmm_x7_pos        : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    v_degmm_x8_pos        : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_POS4;

/* Define the union U_VHDR_DEGAMMA_NUM1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_degmm_x1_num        : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    v_degmm_x2_num        : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    v_degmm_x3_num        : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    v_degmm_x4_num        : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_NUM1;

/* Define the union U_VHDR_DEGAMMA_NUM2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_degmm_x5_num        : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    v_degmm_x6_num        : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    v_degmm_x7_num        : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    v_degmm_x8_num        : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DEGAMMA_NUM2;

/* Define the union U_VHDR_GAMUT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_en         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_CTRL;

/* Define the union U_VHDR_GAMUT_COEF00 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_coef00     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_COEF00;

/* Define the union U_VHDR_GAMUT_COEF01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_coef01     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_COEF01;

/* Define the union U_VHDR_GAMUT_COEF02 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_coef02     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_COEF02;

/* Define the union U_VHDR_GAMUT_COEF10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_coef10     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_COEF10;

/* Define the union U_VHDR_GAMUT_COEF11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_coef11     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_COEF11;

/* Define the union U_VHDR_GAMUT_COEF12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_coef12     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_COEF12;

/* Define the union U_VHDR_GAMUT_COEF20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_coef20     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_COEF20;

/* Define the union U_VHDR_GAMUT_COEF21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_coef21     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_COEF21;

/* Define the union U_VHDR_GAMUT_COEF22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_coef22     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_COEF22;

/* Define the union U_VHDR_GAMUT_SCALE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_scale      : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_SCALE;

/* Define the union U_VHDR_GAMUT_IDC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_idc0       : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_IDC0;

/* Define the union U_VHDR_GAMUT_IDC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_idc1       : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_IDC1;

/* Define the union U_VHDR_GAMUT_IDC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_idc2       : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_IDC2;

/* Define the union U_VHDR_GAMUT_ODC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_odc0       : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_ODC0;

/* Define the union U_VHDR_GAMUT_ODC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_odc1       : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_ODC1;

/* Define the union U_VHDR_GAMUT_ODC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_odc2       : 22  ; /* [21..0]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_ODC2;

/* Define the union U_VHDR_GAMUT_CLIP_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_clip_min   : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_CLIP_MIN;

/* Define the union U_VHDR_GAMUT_CLIP_MAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamut_clip_max   : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMUT_CLIP_MAX;

/* Define the union U_VHDR_TONEMAP_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_en          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_CTRL;

/* Define the union U_VHDR_TONEMAP_REN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_rd_en       : 1   ; /* [0]  */
        unsigned int    vhdr_sm_rd_en         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_REN;

/* Define the union U_VHDR_TONEMAP_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdr_tmap_para_data    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VHDR_TONEMAP_DATA;
/* Define the union U_VHDR_TONEMAP_SM_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdr_sm_para_data      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VHDR_TONEMAP_SM_DATA;
/* Define the union U_VHDR_TONEMAP_STEP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x1_step        : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    v_tmap_x2_step        : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    v_tmap_x3_step        : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    v_tmap_x4_step        : 5   ; /* [28..24]  */
        unsigned int    reserved_3            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_STEP1;

/* Define the union U_VHDR_TONEMAP_STEP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x5_step        : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    v_tmap_x6_step        : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    v_tmap_x7_step        : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    v_tmap_x8_step        : 5   ; /* [28..24]  */
        unsigned int    reserved_3            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_STEP2;

/* Define the union U_VHDR_TONEMAP_POS1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x1_pos         : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_POS1;

/* Define the union U_VHDR_TONEMAP_POS2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x2_pos         : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_POS2;

/* Define the union U_VHDR_TONEMAP_POS3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x3_pos         : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_POS3;

/* Define the union U_VHDR_TONEMAP_POS4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x4_pos         : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_POS4;

/* Define the union U_VHDR_TONEMAP_POS5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x5_pos         : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_POS5;

/* Define the union U_VHDR_TONEMAP_POS6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x6_pos         : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_POS6;

/* Define the union U_VHDR_TONEMAP_POS7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x7_pos         : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_POS7;

/* Define the union U_VHDR_TONEMAP_POS8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x8_pos         : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_POS8;

/* Define the union U_VHDR_TONEMAP_NUM1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x1_num         : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    v_tmap_x2_num         : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    v_tmap_x3_num         : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    v_tmap_x4_num         : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_NUM1;

/* Define the union U_VHDR_TONEMAP_NUM2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_tmap_x5_num         : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    v_tmap_x6_num         : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    v_tmap_x7_num         : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    v_tmap_x8_num         : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_NUM2;

/* Define the union U_VHDR_TONEMAP_SM_STEP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x1_step        : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    v_smap_x2_step        : 4   ; /* [11..8]  */
        unsigned int    reserved_1            : 4   ; /* [15..12]  */
        unsigned int    v_smap_x3_step        : 4   ; /* [19..16]  */
        unsigned int    reserved_2            : 4   ; /* [23..20]  */
        unsigned int    v_smap_x4_step        : 4   ; /* [27..24]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_STEP1;

/* Define the union U_VHDR_TONEMAP_SM_STEP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x5_step        : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    v_smap_x6_step        : 4   ; /* [11..8]  */
        unsigned int    reserved_1            : 4   ; /* [15..12]  */
        unsigned int    v_smap_x7_step        : 4   ; /* [19..16]  */
        unsigned int    reserved_2            : 4   ; /* [23..20]  */
        unsigned int    v_smap_x8_step        : 4   ; /* [27..24]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_STEP2;

/* Define the union U_VHDR_TONEMAP_SM_POS1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x1_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_POS1;

/* Define the union U_VHDR_TONEMAP_SM_POS2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x2_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_POS2;

/* Define the union U_VHDR_TONEMAP_SM_POS3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x3_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_POS3;

/* Define the union U_VHDR_TONEMAP_SM_POS4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x4_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_POS4;

/* Define the union U_VHDR_TONEMAP_SM_POS5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x5_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_POS5;

/* Define the union U_VHDR_TONEMAP_SM_POS6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x6_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_POS6;

/* Define the union U_VHDR_TONEMAP_SM_POS7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x7_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_POS7;

/* Define the union U_VHDR_TONEMAP_SM_POS8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x8_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_POS8;

/* Define the union U_VHDR_TONEMAP_SM_NUM1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x1_num         : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    v_smap_x2_num         : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    v_smap_x3_num         : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    v_smap_x4_num         : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_NUM1;

/* Define the union U_VHDR_TONEMAP_SM_NUM2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_smap_x5_num         : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    v_smap_x6_num         : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    v_smap_x7_num         : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    v_smap_x8_num         : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_SM_NUM2;

/* Define the union U_VHDR_TONEMAP_LUMA_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_luma_coef0  : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_LUMA_COEF0;

/* Define the union U_VHDR_TONEMAP_LUMA_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_luma_coef1  : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_LUMA_COEF1;

/* Define the union U_VHDR_TONEMAP_LUMA_COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_luma_coef2  : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_LUMA_COEF2;

/* Define the union U_VHDR_TONEMAP_LUMA_SCALE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_luma_scale  : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_LUMA_SCALE;

/* Define the union U_VHDR_TONEMAP_COEF_SCALE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_coef_scale  : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_COEF_SCALE;

/* Define the union U_VHDR_TONEMAP_OUT_CLIP_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_out_clip_min : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_OUT_CLIP_MIN;

/* Define the union U_VHDR_TONEMAP_OUT_CLIP_MAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_out_clip_max : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_OUT_CLIP_MAX;

/* Define the union U_VHDR_TONEMAP_OUT_DC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_out_dc0     : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_OUT_DC0;

/* Define the union U_VHDR_TONEMAP_OUT_DC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_out_dc1     : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_OUT_DC1;

/* Define the union U_VHDR_TONEMAP_OUT_DC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_out_dc2     : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_OUT_DC2;

/* Define the union U_VHDR_TONEMAP_ALPHA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_tmap_mix_alpha   : 8   ; /* [7..0]  */
        unsigned int    vhdr_tmap_scale_mix_alpha : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_TONEMAP_ALPHA;

/* Define the union U_VHDR_GAMMA_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gmm_en           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_CTRL;

/* Define the union U_VHDR_GAMMA_REN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_gamma_rd_en      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_REN;

/* Define the union U_VHDR_GAMMMA_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vhdr_gamma_para_data   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_VHDR_GAMMMA_DATA;
/* Define the union U_VHDR_GAMMA_STEP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x1_step         : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    v_gmm_x2_step         : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    v_gmm_x3_step         : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    v_gmm_x4_step         : 5   ; /* [28..24]  */
        unsigned int    reserved_3            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_STEP1;

/* Define the union U_VHDR_GAMMA_STEP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x5_step         : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    v_gmm_x6_step         : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    v_gmm_x7_step         : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    v_gmm_x8_step         : 5   ; /* [28..24]  */
        unsigned int    reserved_3            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_STEP2;

/* Define the union U_VHDR_GAMMA_POS1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x1_pos          : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_POS1;

/* Define the union U_VHDR_GAMMA_POS2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x2_pos          : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_POS2;

/* Define the union U_VHDR_GAMMA_POS3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x3_pos          : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_POS3;

/* Define the union U_VHDR_GAMMA_POS4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x4_pos          : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_POS4;

/* Define the union U_VHDR_GAMMA_POS5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x5_pos          : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_POS5;

/* Define the union U_VHDR_GAMMA_POS6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x6_pos          : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_POS6;

/* Define the union U_VHDR_GAMMA_POS7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x7_pos          : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_POS7;

/* Define the union U_VHDR_GAMMA_POS8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x8_pos          : 21  ; /* [20..0]  */
        unsigned int    reserved_0            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_POS8;

/* Define the union U_VHDR_GAMMA_NUM1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x1_num          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    v_gmm_x2_num          : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    v_gmm_x3_num          : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    v_gmm_x4_num          : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_NUM1;

/* Define the union U_VHDR_GAMMA_NUM2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    v_gmm_x5_num          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    v_gmm_x6_num          : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    v_gmm_x7_num          : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    v_gmm_x8_num          : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_GAMMA_NUM2;

/* Define the union U_VHDR_DITHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_tap_mode  : 2   ; /* [1..0]  */
        unsigned int    vhdr_dither_domain_mode : 1   ; /* [2]  */
        unsigned int    vhdr_dither_round     : 1   ; /* [3]  */
        unsigned int    vhdr_dither_mode      : 1   ; /* [4]  */
        unsigned int    vhdr_dither_en        : 1   ; /* [5]  */
        unsigned int    vhdr_dither_round_unlim : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_CTRL;

/* Define the union U_VHDR_DITHER_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_thr_min   : 16  ; /* [15..0]  */
        unsigned int    vhdr_dither_thr_max   : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_THR;

/* Define the union U_VHDR_DITHER_SED_Y0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_sed_y0    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_SED_Y0;

/* Define the union U_VHDR_DITHER_SED_U0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_sed_u0    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_SED_U0;

/* Define the union U_VHDR_DITHER_SED_V0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_sed_v0    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_SED_V0;

/* Define the union U_VHDR_DITHER_SED_W0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_sed_w0    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_SED_W0;

/* Define the union U_VHDR_DITHER_SED_Y1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_sed_y1    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_SED_Y1;

/* Define the union U_VHDR_DITHER_SED_U1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_sed_u1    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_SED_U1;

/* Define the union U_VHDR_DITHER_SED_V1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_sed_v1    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_SED_V1;

/* Define the union U_VHDR_DITHER_SED_W1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_dither_sed_w1    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_DITHER_SED_W1;

/* Define the union U_VHDR_RGB2YUV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_en           : 1   ; /* [0]  */
        unsigned int    vhdr_cadj_en          : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_CTRL;

/* Define the union U_VHDR_RGB2YUV_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_coef00       : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_COEF0;

/* Define the union U_VHDR_RGB2YUV_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_coef01       : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_COEF1;

/* Define the union U_VHDR_RGB2YUV_COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_coef02       : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_COEF2;

/* Define the union U_VHDR_RGB2YUV_COEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_coef10       : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_COEF3;

/* Define the union U_VHDR_RGB2YUV_COEF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_coef11       : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_COEF4;

/* Define the union U_VHDR_RGB2YUV_COEF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_coef12       : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_COEF5;

/* Define the union U_VHDR_RGB2YUV_COEF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_coef20       : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_COEF6;

/* Define the union U_VHDR_RGB2YUV_COEF7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_coef21       : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_COEF7;

/* Define the union U_VHDR_RGB2YUV_COEF8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_coef22       : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_COEF8;

/* Define the union U_VHDR_RGB2YUV_SCALE2P */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_scale2p      : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    vhdr_cadj_scale2p     : 4   ; /* [7..4]  */
        unsigned int    reserved_1            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_SCALE2P;

/* Define the union U_VHDR_RGB2YUV_IDC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_idc0         : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_IDC0;

/* Define the union U_VHDR_RGB2YUV_IDC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_idc1         : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_IDC1;

/* Define the union U_VHDR_RGB2YUV_IDC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_idc2         : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_IDC2;

/* Define the union U_VHDR_RGB2YUV_ODC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_odc0         : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_ODC0;

/* Define the union U_VHDR_RGB2YUV_ODC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_odc1         : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_ODC1;

/* Define the union U_VHDR_RGB2YUV_ODC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_odc2         : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_ODC2;

/* Define the union U_VHDR_RGB2YUV_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_clip_y_min   : 10  ; /* [9..0]  */
        unsigned int    vhdr_r2y_clip_c_min   : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_MIN;

/* Define the union U_VHDR_RGB2YUV_MAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vhdr_r2y_clip_y_max   : 10  ; /* [9..0]  */
        unsigned int    vhdr_r2y_clip_c_max   : 10  ; /* [19..10]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDR_RGB2YUV_MAX;

/* Define the union U_VHDACM0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_a_u_off           : 5   ; /* [4..0]  */
        unsigned int    acm_b_u_off           : 5   ; /* [9..5]  */
        unsigned int    acm_c_u_off           : 5   ; /* [14..10]  */
        unsigned int    acm_d_u_off           : 5   ; /* [19..15]  */
        unsigned int    acm_fir_blk           : 4   ; /* [23..20]  */
        unsigned int    acm_sec_blk           : 4   ; /* [27..24]  */
        unsigned int    acm0_en               : 1   ; /* [28]  */
        unsigned int    acm1_en               : 1   ; /* [29]  */
        unsigned int    acm2_en               : 1   ; /* [30]  */
        unsigned int    acm3_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACM0;

/* Define the union U_VHDACM1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_a_v_off           : 5   ; /* [4..0]  */
        unsigned int    acm_b_v_off           : 5   ; /* [9..5]  */
        unsigned int    acm_c_v_off           : 5   ; /* [14..10]  */
        unsigned int    acm_d_v_off           : 5   ; /* [19..15]  */
        unsigned int    acm_test_en           : 1   ; /* [20]  */
        unsigned int    acm_dbg_mode          : 1   ; /* [21]  */
        unsigned int    bw_pro_mode           : 1   ; /* [22]  */
        unsigned int    reserved_0            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACM1;

/* Define the union U_VHDACM2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_a_u_off           : 5   ; /* [4..0]  */
        unsigned int    acm_b_u_off           : 5   ; /* [9..5]  */
        unsigned int    acm_c_u_off           : 5   ; /* [14..10]  */
        unsigned int    acm_d_u_off           : 5   ; /* [19..15]  */
        unsigned int    acm_fir_blk           : 4   ; /* [23..20]  */
        unsigned int    acm_sec_blk           : 4   ; /* [27..24]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACM2;

/* Define the union U_VHDACM3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_a_v_off           : 5   ; /* [4..0]  */
        unsigned int    acm_b_v_off           : 5   ; /* [9..5]  */
        unsigned int    acm_c_v_off           : 5   ; /* [14..10]  */
        unsigned int    acm_d_v_off           : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACM3;

/* Define the union U_VHDACM4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_a_u_off           : 5   ; /* [4..0]  */
        unsigned int    acm_b_u_off           : 5   ; /* [9..5]  */
        unsigned int    acm_c_u_off           : 5   ; /* [14..10]  */
        unsigned int    acm_d_u_off           : 5   ; /* [19..15]  */
        unsigned int    acm_fir_blk           : 4   ; /* [23..20]  */
        unsigned int    acm_sec_blk           : 4   ; /* [27..24]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACM4;

/* Define the union U_VHDACM5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_a_v_off           : 5   ; /* [4..0]  */
        unsigned int    acm_b_v_off           : 5   ; /* [9..5]  */
        unsigned int    acm_c_v_off           : 5   ; /* [14..10]  */
        unsigned int    acm_d_v_off           : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACM5;

/* Define the union U_VHDACM6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_a_u_off           : 5   ; /* [4..0]  */
        unsigned int    acm_b_u_off           : 5   ; /* [9..5]  */
        unsigned int    acm_c_u_off           : 5   ; /* [14..10]  */
        unsigned int    acm_d_u_off           : 5   ; /* [19..15]  */
        unsigned int    acm_fir_blk           : 4   ; /* [23..20]  */
        unsigned int    acm_sec_blk           : 4   ; /* [27..24]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACM6;

/* Define the union U_VHDACM7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    acm_a_v_off           : 5   ; /* [4..0]  */
        unsigned int    acm_b_v_off           : 5   ; /* [9..5]  */
        unsigned int    acm_c_v_off           : 5   ; /* [14..10]  */
        unsigned int    acm_d_v_off           : 5   ; /* [19..15]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VHDACM7;

/* Define the union U_DHD_TOP_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chk_sum_en            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD_TOP_CTRL;

/* Define the union U_VO_MUX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mipi_sel              : 4   ; /* [3..0]  */
        unsigned int    lcd_sel               : 4   ; /* [7..4]  */
        unsigned int    vga_sel               : 4   ; /* [11..8]  */
        unsigned int    hdmi_sel              : 1   ; /* [12]  */
        unsigned int    sddate_sel            : 1   ; /* [13]  */
        unsigned int    hddate_sel            : 1   ; /* [14]  */
        unsigned int    reserved_0            : 13  ; /* [27..15]  */
        unsigned int    digital_sel           : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VO_MUX;

/* Define the union U_DHD_VO_MUX_SYNC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sync_dv               : 1   ; /* [0]  */
        unsigned int    sync_hsync            : 1   ; /* [1]  */
        unsigned int    sync_vsync            : 1   ; /* [2]  */
        unsigned int    sync_field            : 1   ; /* [3]  */
        unsigned int    reserved_0            : 27  ; /* [30..4]  */
        unsigned int    sync_test_mode        : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD_VO_MUX_SYNC;

/* Define the union U_DHD_VO_MUX_DATA */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vomux_data            : 30  ; /* [29..0]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD_VO_MUX_DATA;

/* Define the union U_DHD0_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    disp_mode             : 3   ; /* [3..1]  */
        unsigned int    iop                   : 1   ; /* [4]  */
        unsigned int    intf_ivs              : 1   ; /* [5]  */
        unsigned int    intf_ihs              : 1   ; /* [6]  */
        unsigned int    intf_idv              : 1   ; /* [7]  */
        unsigned int    emb_mode              : 1   ; /* [8]  */
        unsigned int    fp_inter_sync         : 1   ; /* [9]  */
        unsigned int    trigger_en            : 1   ; /* [10]  */
        unsigned int    uf_offline_en         : 1   ; /* [11]  */
        unsigned int    fpga_lmt_width        : 7   ; /* [18..12]  */
        unsigned int    fpga_lmt_en           : 1   ; /* [19]  */
        unsigned int    reserved_0            : 1   ; /* [20]  */
        unsigned int    gmm_mode              : 1   ; /* [21]  */
        unsigned int    gmm_en                : 1   ; /* [22]  */
        unsigned int    hdmi_mode             : 1   ; /* [23]  */
        unsigned int    twochn_debug          : 1   ; /* [24]  */
        unsigned int    mirror_en             : 1   ; /* [25]  */
        unsigned int    sin_en                : 1   ; /* [26]  */
        unsigned int    p2i_en                : 1   ; /* [27]  */
        unsigned int    cbar_mode             : 1   ; /* [28]  */
        unsigned int    cbar_sel              : 1   ; /* [29]  */
        unsigned int    cbar_en               : 1   ; /* [30]  */
        unsigned int    intf_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CTRL;

/* Define the union U_DHD0_CTRL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup_mode            : 1   ; /* [0]  */
        unsigned int    p2i_en                : 1   ; /* [1]  */
        unsigned int    mir_en                : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    multichn_split_mode   : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    multichn_en           : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CTRL1;

/* Define the union U_DHD0_VSYNC */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vact                  : 16  ; /* [15..0]  */
        unsigned int    vbb                   : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VSYNC;

/* Define the union U_DHD0_VSYNC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vfb                   : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VSYNC2;

/* Define the union U_DHD0_HSYNC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hact                  : 16  ; /* [15..0]  */
        unsigned int    hbb                   : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_HSYNC1;

/* Define the union U_DHD0_HSYNC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hfb                   : 16  ; /* [15..0]  */
        unsigned int    hmid                  : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_HSYNC2;

/* Define the union U_DHD0_VPLUS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bvact                 : 16  ; /* [15..0]  */
        unsigned int    bvbb                  : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VPLUS;

/* Define the union U_DHD0_VPLUS2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bvfb                  : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VPLUS2;

/* Define the union U_DHD0_PWR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpw                   : 16  ; /* [15..0]  */
        unsigned int    vpw                   : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PWR;

/* Define the union U_DHD0_VTTHD3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vtmgthd3              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 2   ; /* [14..13]  */
        unsigned int    thd3_mode             : 1   ; /* [15]  */
        unsigned int    vtmgthd4              : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 2   ; /* [30..29]  */
        unsigned int    thd4_mode             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VTTHD3;

/* Define the union U_DHD0_VTTHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vtmgthd1              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 2   ; /* [14..13]  */
        unsigned int    thd1_mode             : 1   ; /* [15]  */
        unsigned int    vtmgthd2              : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 2   ; /* [30..29]  */
        unsigned int    thd2_mode             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VTTHD;

/* Define the union U_DHD0_PARATHD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    para_thd              : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 23  ; /* [30..8]  */
        unsigned int    dfs_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PARATHD;

/* Define the union U_DHD0_PRECHARGE_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tcon_precharge_thd    : 17  ; /* [16..0]  */
        unsigned int    reserved_0            : 15  ; /* [31..17]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PRECHARGE_THD;

/* Define the union U_DHD0_START_POS */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    start_pos             : 8   ; /* [7..0]  */
        unsigned int    timing_start_pos      : 8   ; /* [15..8]  */
        unsigned int    fi_start_pos          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_START_POS;

/* Define the union U_DHD0_START_POS1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    req_start_line_pos    : 16  ; /* [15..0]  */
        unsigned int    req_start_pos         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_START_POS1;

/* Define the union U_DHD0_START_POS2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pre_start_line_pos    : 16  ; /* [15..0]  */
        unsigned int    pre_start_pos         : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_START_POS2;

/* Define the union U_DHD0_BUSY_MODE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rm_busy               : 1   ; /* [0]  */
        unsigned int    para_busy_mode        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_BUSY_MODE;

/* Define the union U_DHD0_BUSY_MODE_RD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    rm_busy_rd_sta        : 1   ; /* [0]  */
        unsigned int    para_busy_rd_sta      : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_BUSY_MODE_RD;

/* Define the union U_DHD0_CLK_DV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intf_clk_mux          : 1   ; /* [0]  */
        unsigned int    intf_dv_mux           : 1   ; /* [1]  */
        unsigned int    no_active_area_pos    : 16  ; /* [17..2]  */
        unsigned int    reserved_0            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_CLK_DV_CTRL;

/* Define the union U_DHD0_RGB_FIX_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fix_b                 : 10  ; /* [9..0]  */
        unsigned int    fix_g                 : 10  ; /* [19..10]  */
        unsigned int    fix_r                 : 10  ; /* [29..20]  */
        unsigned int    rgb_fix_mux           : 1   ; /* [30]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_RGB_FIX_CTRL;

/* Define the union U_DHD0_LOCKCFG */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_measure_en         : 1   ; /* [0]  */
        unsigned int    lock_cnt_en           : 1   ; /* [1]  */
        unsigned int    vdp_measure_en        : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_LOCKCFG;

/* Define the union U_DHD0_CAP_FRM_CNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cap_frm_cnt            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_CAP_FRM_CNT;
/* Define the union U_DHD0_VDP_FRM_CNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vdp_frm_cnt            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_VDP_FRM_CNT;
/* Define the union U_DHD0_VSYNC_CAP_VDP_CNT */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vsync_cap_vdp_cnt      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_VSYNC_CAP_VDP_CNT;
/* Define the union U_DHD0_INTF_CHKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_r0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF_CHKSUM_Y;
/* Define the union U_DHD0_INTF_CHKSUM_U */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_g0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF_CHKSUM_U;
/* Define the union U_DHD0_INTF_CHKSUM_V */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_b0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF_CHKSUM_V;
/* Define the union U_DHD0_INTF1_CHKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_r1           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF1_CHKSUM_Y;
/* Define the union U_DHD0_INTF1_CHKSUM_U */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_g1           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF1_CHKSUM_U;
/* Define the union U_DHD0_INTF1_CHKSUM_V */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_b1           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF1_CHKSUM_V;
/* Define the union U_DHD0_INTF_CHKSUM_HIGH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    b0_sum_high           : 8   ; /* [7..0]  */
        unsigned int    g0_sum_high           : 8   ; /* [15..8]  */
        unsigned int    r0_sum_high           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_INTF_CHKSUM_HIGH1;

/* Define the union U_DHD0_INTF_CHKSUM_HIGH2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    b1_sum_high           : 8   ; /* [7..0]  */
        unsigned int    g1_sum_high           : 8   ; /* [15..8]  */
        unsigned int    r1_sum_high           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_INTF_CHKSUM_HIGH2;

/* Define the union U_DHD0_INTF2_CHKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_r2           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF2_CHKSUM_Y;
/* Define the union U_DHD0_INTF2_CHKSUM_U */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_g2           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF2_CHKSUM_U;
/* Define the union U_DHD0_INTF2_CHKSUM_V */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_b2           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF2_CHKSUM_V;
/* Define the union U_DHD0_INTF3_CHKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_r3           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF3_CHKSUM_Y;
/* Define the union U_DHD0_INTF3_CHKSUM_U */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_g3           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF3_CHKSUM_U;
/* Define the union U_DHD0_INTF3_CHKSUM_V */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_b3           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DHD0_INTF3_CHKSUM_V;
/* Define the union U_DHD0_INTF_CHKSUM_HIGH3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    b2_sum_high           : 8   ; /* [7..0]  */
        unsigned int    g2_sum_high           : 8   ; /* [15..8]  */
        unsigned int    r2_sum_high           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_INTF_CHKSUM_HIGH3;

/* Define the union U_DHD0_INTF_CHKSUM_HIGH4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    b3_sum_high           : 8   ; /* [7..0]  */
        unsigned int    g3_sum_high           : 8   ; /* [15..8]  */
        unsigned int    r3_sum_high           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_INTF_CHKSUM_HIGH4;

/* Define the union U_DHD0_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vback_blank           : 1   ; /* [0]  */
        unsigned int    vblank                : 1   ; /* [1]  */
        unsigned int    bottom_field          : 1   ; /* [2]  */
        unsigned int    count_vcnt            : 13  ; /* [15..3]  */
        unsigned int    count_int             : 8   ; /* [23..16]  */
        unsigned int    dhd_even              : 1   ; /* [24]  */
        unsigned int    reserved_0            : 6   ; /* [30..25]  */
        unsigned int    intf_under_flow       : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_STATE;

/* Define the union U_DHD0_UF_STATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ud_first_cnt          : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_UF_STATE;

/* Define the union U_DHD0_VBI */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vbi_data              : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 8   ; /* [23..16]  */
        unsigned int    vbi_addr              : 4   ; /* [27..24]  */
        unsigned int    reserved_1            : 3   ; /* [30..28]  */
        unsigned int    vbi_en                : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VBI;

/* Define the union U_DHD0_ONLINE_CFG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    chip_online           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_ONLINE_CFG1;

/* Define the union U_DHD0_PRECHARGE_THD1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tcon_precharge_thd_otr : 17  ; /* [16..0]  */
        unsigned int    reserved_0            : 3   ; /* [19..17]  */
        unsigned int    tcon_pre_mode         : 1   ; /* [20]  */
        unsigned int    dneed_en_mode         : 1   ; /* [21]  */
        unsigned int    reserved_1            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PRECHARGE_THD1;

/* Define the union U_DHD0_LLRR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    llrr_start_pos_line   : 16  ; /* [15..0]  */
        unsigned int    llrr_start_pos_cycle  : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_LLRR_CTRL;

/* Define the union U_DHD0_SCAN_BL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    intf_vsync_bl_sel     : 1   ; /* [0]  */
        unsigned int    intf_vsync_bl_inv     : 1   ; /* [1]  */
        unsigned int    llrr_mode             : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_SCAN_BL;

/* Define the union U_DHD0_MULTICHIP_CFG1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vstate_change_mode    : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_MULTICHIP_CFG1;

/* Define the union U_DHD0_PAUSE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pause_mode            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PAUSE;

/* Define the union U_DHD0_PRE_UF_THD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    afifo_pre_uf_thd      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_PRE_UF_THD;

/* Define the union U_DHD0_VDAC_DET0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdac_det_high         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    det_line              : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VDAC_DET0;

/* Define the union U_DHD0_VDAC_DET1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    det_pixel_stat        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    det_pixel_wid         : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 4   ; /* [30..27]  */
        unsigned int    vdac_det_en           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VDAC_DET1;

/* Define the union U_DHD0_VTTHD5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vtmgthd5              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 2   ; /* [14..13]  */
        unsigned int    thd5_mode             : 1   ; /* [15]  */
        unsigned int    vtmgthd6              : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 2   ; /* [30..29]  */
        unsigned int    thd6_mode             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DHD0_VTTHD5;

/* Define the union U_INTF_HDMI_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmi_422_en           : 1   ; /* [0]  */
        unsigned int    hdmi_420_en           : 1   ; /* [1]  */
        unsigned int    hdmi_420_mode         : 2   ; /* [3..2]  */
        unsigned int    hdmi_mode             : 2   ; /* [5..4]  */
        unsigned int    rgb_mode              : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTF_HDMI_CTRL;

/* Define the union U_INTF_HDMI_SYNC_INV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dv_inv                : 1   ; /* [0]  */
        unsigned int    hs_inv                : 1   ; /* [1]  */
        unsigned int    vs_inv                : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTF_HDMI_SYNC_INV;

/* Define the union U_INTF_HDMI_CLIP_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmi_cl0              : 10  ; /* [9..0]  */
        unsigned int    hdmi_cl1              : 10  ; /* [19..10]  */
        unsigned int    hdmi_cl2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 1   ; /* [30]  */
        unsigned int    hdmi_clip_en          : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTF_HDMI_CLIP_L;

/* Define the union U_INTF_HDMI_CLIP_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmi_ch0              : 10  ; /* [9..0]  */
        unsigned int    hdmi_ch1              : 10  ; /* [19..10]  */
        unsigned int    hdmi_ch2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTF_HDMI_CLIP_H;

/* Define the union U_INTF_HDMI_CHKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_r0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_INTF_HDMI_CHKSUM_Y;
/* Define the union U_INTF_HDMI_CHKSUM_U */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_g0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_INTF_HDMI_CHKSUM_U;
/* Define the union U_INTF_HDMI_CHKSUM_V */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_b0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_INTF_HDMI_CHKSUM_V;
/* Define the union U_INTF_HDMI_CHKSUM_HIGH1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    b0_sum_high           : 8   ; /* [7..0]  */
        unsigned int    g0_sum_high           : 8   ; /* [15..8]  */
        unsigned int    r0_sum_high           : 8   ; /* [23..16]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTF_HDMI_CHKSUM_HIGH1;

/* Define the union U_INTF_DATE_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 24  ; /* [23..0]  */
        unsigned int    yc_mode               : 1   ; /* [24]  */
        unsigned int    lcd_parallel_mode     : 1   ; /* [25]  */
        unsigned int    lcd_data_inv          : 1   ; /* [26]  */
        unsigned int    lcd_parallel_order    : 1   ; /* [27]  */
        unsigned int    lcd_serial_perd       : 1   ; /* [28]  */
        unsigned int    lcd_serial_mode       : 1   ; /* [29]  */
        unsigned int    dfir_en               : 1   ; /* [30]  */
        unsigned int    hdmi_mode             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTF_DATE_CTRL;

/* Define the union U_INTF_DATE_UPD */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    regup                 : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTF_DATE_UPD;

/* Define the union U_INTF_DATE_SYNC_INV */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dv_inv                : 1   ; /* [0]  */
        unsigned int    hs_inv                : 1   ; /* [1]  */
        unsigned int    vs_inv                : 1   ; /* [2]  */
        unsigned int    f_inv                 : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_INTF_DATE_SYNC_INV;

/* Define the union U_DATE_CLIP0_L */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_cl0              : 10  ; /* [9..0]  */
        unsigned int    clip_cl1              : 10  ; /* [19..10]  */
        unsigned int    clip_cl2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 1   ; /* [30]  */
        unsigned int    clip_en               : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_CLIP0_L;

/* Define the union U_DATE_CLIP0_H */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clip_ch0              : 10  ; /* [9..0]  */
        unsigned int    clip_ch1              : 10  ; /* [19..10]  */
        unsigned int    clip_ch2              : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_CLIP0_H;

/* Define the union U_DATE_INTF_CHKSUM_Y */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_r0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_INTF_CHKSUM_Y;
/* Define the union U_DATE_INTF_CHKSUM_U */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_g0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_INTF_CHKSUM_U;
/* Define the union U_DATE_INTF_CHKSUM_V */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int check_sum_b0           : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_INTF_CHKSUM_V;
/* Define the union U_DATE_COEFF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_seq                : 1   ; /* [0]  */
        unsigned int    chgain_en             : 1   ; /* [1]  */
        unsigned int    sylp_en               : 1   ; /* [2]  */
        unsigned int    chlp_en               : 1   ; /* [3]  */
        unsigned int    oversam2_en           : 1   ; /* [4]  */
        unsigned int    lunt_en               : 1   ; /* [5]  */
        unsigned int    oversam_en            : 2   ; /* [7..6]  */
        unsigned int    reserved_0            : 1   ; /* [8]  */
        unsigned int    luma_dl               : 4   ; /* [12..9]  */
        unsigned int    agc_amp_sel           : 1   ; /* [13]  */
        unsigned int    length_sel            : 1   ; /* [14]  */
        unsigned int    sync_mode_scart       : 1   ; /* [15]  */
        unsigned int    sync_mode_sel         : 2   ; /* [17..16]  */
        unsigned int    style_sel             : 4   ; /* [21..18]  */
        unsigned int    fm_sel                : 1   ; /* [22]  */
        unsigned int    vbi_lpf_en            : 1   ; /* [23]  */
        unsigned int    rgb_en                : 1   ; /* [24]  */
        unsigned int    scanline              : 1   ; /* [25]  */
        unsigned int    pbpr_lpf_en           : 1   ; /* [26]  */
        unsigned int    pal_half_en           : 1   ; /* [27]  */
        unsigned int    reserved_1            : 1   ; /* [28]  */
        unsigned int    dis_ire               : 1   ; /* [29]  */
        unsigned int    clpf_sel              : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF0;

/* Define the union U_DATE_COEFF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac_test              : 10  ; /* [9..0]  */
        unsigned int    date_test_mode        : 2   ; /* [11..10]  */
        unsigned int    date_test_en          : 1   ; /* [12]  */
        unsigned int    amp_outside           : 10  ; /* [22..13]  */
        unsigned int    c_limit_en            : 1   ; /* [23]  */
        unsigned int    cc_seq                : 1   ; /* [24]  */
        unsigned int    cgms_seq              : 1   ; /* [25]  */
        unsigned int    vps_seq               : 1   ; /* [26]  */
        unsigned int    wss_seq               : 1   ; /* [27]  */
        unsigned int    cvbs_limit_en         : 1   ; /* [28]  */
        unsigned int    c_gain                : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF1;

/* Define the union U_DATE_COEFF2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int coef02                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF2;
/* Define the union U_DATE_COEFF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef03                : 26  ; /* [25..0]  */
        unsigned int    reserved_0            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF3;

/* Define the union U_DATE_COEFF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef04                : 30  ; /* [29..0]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF4;

/* Define the union U_DATE_COEFF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef05                : 29  ; /* [28..0]  */
        unsigned int    reserved_0            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF5;

/* Define the union U_DATE_COEFF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    coef06_1              : 23  ; /* [22..0]  */
        unsigned int    reserved_0            : 8   ; /* [30..23]  */
        unsigned int    coef06_0              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF6;

/* Define the union U_DATE_COEFF7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt07_enf2             : 1   ; /* [0]  */
        unsigned int    tt08_enf2             : 1   ; /* [1]  */
        unsigned int    tt09_enf2             : 1   ; /* [2]  */
        unsigned int    tt10_enf2             : 1   ; /* [3]  */
        unsigned int    tt11_enf2             : 1   ; /* [4]  */
        unsigned int    tt12_enf2             : 1   ; /* [5]  */
        unsigned int    tt13_enf2             : 1   ; /* [6]  */
        unsigned int    tt14_enf2             : 1   ; /* [7]  */
        unsigned int    tt15_enf2             : 1   ; /* [8]  */
        unsigned int    tt16_enf2             : 1   ; /* [9]  */
        unsigned int    tt17_enf2             : 1   ; /* [10]  */
        unsigned int    tt18_enf2             : 1   ; /* [11]  */
        unsigned int    tt19_enf2             : 1   ; /* [12]  */
        unsigned int    tt20_enf2             : 1   ; /* [13]  */
        unsigned int    tt21_enf2             : 1   ; /* [14]  */
        unsigned int    tt22_enf2             : 1   ; /* [15]  */
        unsigned int    tt07_enf1             : 1   ; /* [16]  */
        unsigned int    tt08_enf1             : 1   ; /* [17]  */
        unsigned int    tt09_enf1             : 1   ; /* [18]  */
        unsigned int    tt10_enf1             : 1   ; /* [19]  */
        unsigned int    tt11_enf1             : 1   ; /* [20]  */
        unsigned int    tt12_enf1             : 1   ; /* [21]  */
        unsigned int    tt13_enf1             : 1   ; /* [22]  */
        unsigned int    tt14_enf1             : 1   ; /* [23]  */
        unsigned int    tt15_enf1             : 1   ; /* [24]  */
        unsigned int    tt16_enf1             : 1   ; /* [25]  */
        unsigned int    tt17_enf1             : 1   ; /* [26]  */
        unsigned int    tt18_enf1             : 1   ; /* [27]  */
        unsigned int    tt19_enf1             : 1   ; /* [28]  */
        unsigned int    tt20_enf1             : 1   ; /* [29]  */
        unsigned int    tt21_enf1             : 1   ; /* [30]  */
        unsigned int    tt22_enf1             : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF7;

/* Define the union U_DATE_COEFF8 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tt_staddr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF8;
/* Define the union U_DATE_COEFF9 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int tt_edaddr              : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF9;
/* Define the union U_DATE_COEFF10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_pktoff             : 8   ; /* [7..0]  */
        unsigned int    tt_mode               : 2   ; /* [9..8]  */
        unsigned int    tt_highest            : 1   ; /* [10]  */
        unsigned int    full_page             : 1   ; /* [11]  */
        unsigned int    nabts_100ire          : 1   ; /* [12]  */
        unsigned int    reserved_0            : 18  ; /* [30..13]  */
        unsigned int    tt_ready              : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF10;

/* Define the union U_DATE_COEFF11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    date_clf2             : 10  ; /* [9..0]  */
        unsigned int    date_clf1             : 10  ; /* [19..10]  */
        unsigned int    cc_enf2               : 1   ; /* [20]  */
        unsigned int    cc_enf1               : 1   ; /* [21]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF11;

/* Define the union U_DATE_COEFF12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cc_f2data             : 16  ; /* [15..0]  */
        unsigned int    cc_f1data             : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF12;

/* Define the union U_DATE_COEFF13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cg_f1data             : 20  ; /* [19..0]  */
        unsigned int    cg_enf2               : 1   ; /* [20]  */
        unsigned int    cg_enf1               : 1   ; /* [21]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF13;

/* Define the union U_DATE_COEFF14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cg_f2data             : 20  ; /* [19..0]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF14;

/* Define the union U_DATE_COEFF15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wss_data              : 14  ; /* [13..0]  */
        unsigned int    wss_en                : 1   ; /* [14]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF15;

/* Define the union U_DATE_COEFF16 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vps_data              : 24  ; /* [23..0]  */
        unsigned int    vps_en                : 1   ; /* [24]  */
        unsigned int    reserved_0            : 7   ; /* [31..25]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF16;

/* Define the union U_DATE_COEFF17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vps_data               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF17;
/* Define the union U_DATE_COEFF18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int vps_data               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF18;
/* Define the union U_DATE_COEFF19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vps_data              : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF19;

/* Define the union U_DATE_COEFF20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt05_enf2             : 1   ; /* [0]  */
        unsigned int    tt06_enf2             : 1   ; /* [1]  */
        unsigned int    tt06_enf1             : 1   ; /* [2]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF20;

/* Define the union U_DATE_COEFF21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac0_in_sel           : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    dac1_in_sel           : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    dac2_in_sel           : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    dac3_in_sel           : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    dac4_in_sel           : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    dac5_in_sel           : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF21;

/* Define the union U_DATE_COEFF22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    video_phase_delta     : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF22;

/* Define the union U_DATE_COEFF23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dac0_out_dly          : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    dac1_out_dly          : 3   ; /* [6..4]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    dac2_out_dly          : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    dac3_out_dly          : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    dac4_out_dly          : 3   ; /* [18..16]  */
        unsigned int    reserved_4            : 1   ; /* [19]  */
        unsigned int    dac5_out_dly          : 3   ; /* [22..20]  */
        unsigned int    reserved_5            : 9   ; /* [31..23]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF23;

/* Define the union U_DATE_COEFF24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int burst_start            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_COEFF24;
/* Define the union U_DATE_COEFF25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x_n_coef              : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 3   ; /* [15..13]  */
        unsigned int    x_n_1_coef            : 13  ; /* [28..16]  */
        unsigned int    reserved_1            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF25;

/* Define the union U_DATE_COEFF26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    x_n_1_coef            : 13  ; /* [12..0]  */
        unsigned int    reserved_0            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF26;

/* Define the union U_DATE_COEFF27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    y_n_coef              : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    y_n_1_coef            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF27;

/* Define the union U_DATE_COEFF28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pixel_begin1          : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    pixel_begin2          : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF28;

/* Define the union U_DATE_COEFF29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pixel_end             : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF29;

/* Define the union U_DATE_COEFF30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_secam               : 7   ; /* [6..0]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF30;

/* Define the union U_DATE_ISRMASK */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_mask               : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_ISRMASK;

/* Define the union U_DATE_ISRSTATE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_status             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_ISRSTATE;

/* Define the union U_DATE_ISR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tt_int                : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_ISR;

/* Define the union U_DATE_VERSION */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_DATE_VERSION;
/* Define the union U_DATE_COEFF37 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_y1_coeff0         : 8   ; /* [7..0]  */
        unsigned int    fir_y1_coeff1         : 8   ; /* [15..8]  */
        unsigned int    fir_y1_coeff2         : 8   ; /* [23..16]  */
        unsigned int    fir_y1_coeff3         : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF37;

/* Define the union U_DATE_COEFF38 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_y2_coeff0         : 16  ; /* [15..0]  */
        unsigned int    fir_y2_coeff1         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF38;

/* Define the union U_DATE_COEFF39 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_y2_coeff2         : 16  ; /* [15..0]  */
        unsigned int    fir_y2_coeff3         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF39;

/* Define the union U_DATE_COEFF40 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_c1_coeff0         : 8   ; /* [7..0]  */
        unsigned int    fir_c1_coeff1         : 8   ; /* [15..8]  */
        unsigned int    fir_c1_coeff2         : 8   ; /* [23..16]  */
        unsigned int    fir_c1_coeff3         : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF40;

/* Define the union U_DATE_COEFF41 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_c2_coeff0         : 16  ; /* [15..0]  */
        unsigned int    fir_c2_coeff1         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF41;

/* Define the union U_DATE_COEFF42 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fir_c2_coeff2         : 16  ; /* [15..0]  */
        unsigned int    fir_c2_coeff3         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF42;

/* Define the union U_DATE_DACDET1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdac_det_high         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 6   ; /* [15..10]  */
        unsigned int    det_line              : 10  ; /* [25..16]  */
        unsigned int    reserved_1            : 6   ; /* [31..26]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_DACDET1;

/* Define the union U_DATE_DACDET2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    det_pixel_sta         : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    det_pixel_wid         : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 4   ; /* [30..27]  */
        unsigned int    vdac_det_en           : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_DACDET2;

/* Define the union U_DATE_COEFF50 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF50;

/* Define the union U_DATE_COEFF51 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF51;

/* Define the union U_DATE_COEFF52 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF52;

/* Define the union U_DATE_COEFF53 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF53;

/* Define the union U_DATE_COEFF54 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF54;

/* Define the union U_DATE_COEFF55 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ovs_coeff0            : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 5   ; /* [15..11]  */
        unsigned int    ovs_coeff1            : 11  ; /* [26..16]  */
        unsigned int    reserved_1            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_DATE_COEFF55;

/* Define the union U_GHDR_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_en               : 1   ; /* [0]  */
        unsigned int    ghdr_degmm_en         : 1   ; /* [1]  */
        unsigned int    ghdr_ck_gt_en         : 1   ; /* [2]  */
        unsigned int    reserved_0            : 9   ; /* [11..3]  */
        unsigned int    ghdr_demo_en          : 1   ; /* [12]  */
        unsigned int    ghdr_demo_mode        : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    ghdr_demo_pos         : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_CTRL;

/* Define the union U_GHDR_GAMUT_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_en         : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_CTRL;

/* Define the union U_GHDR_GAMUT_COEF00 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_coef00     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_COEF00;

/* Define the union U_GHDR_GAMUT_COEF01 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_coef01     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_COEF01;

/* Define the union U_GHDR_GAMUT_COEF02 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_coef02     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_COEF02;

/* Define the union U_GHDR_GAMUT_COEF10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_coef10     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_COEF10;

/* Define the union U_GHDR_GAMUT_COEF11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_coef11     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_COEF11;

/* Define the union U_GHDR_GAMUT_COEF12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_coef12     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_COEF12;

/* Define the union U_GHDR_GAMUT_COEF20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_coef20     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_COEF20;

/* Define the union U_GHDR_GAMUT_COEF21 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_coef21     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_COEF21;

/* Define the union U_GHDR_GAMUT_COEF22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_coef22     : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_COEF22;

/* Define the union U_GHDR_GAMUT_SCALE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_scale      : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_SCALE;

/* Define the union U_GHDR_GAMUT_CLIP_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_clip_min   : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_CLIP_MIN;

/* Define the union U_GHDR_GAMUT_CLIP_MAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamut_clip_max   : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMUT_CLIP_MAX;

/* Define the union U_GHDR_TONEMAP_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_tmap_en          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_CTRL;

/* Define the union U_GHDR_TONEMAP_REN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_tmap_rd_en       : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_REN;

/* Define the union U_GHDR_TONEMAP_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ghdr_tmap_para_data    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GHDR_TONEMAP_DATA;
/* Define the union U_GHDR_TONEMAP_STEP */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_tmap_x1_step        : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    g_tmap_x2_step        : 4   ; /* [11..8]  */
        unsigned int    reserved_1            : 4   ; /* [15..12]  */
        unsigned int    g_tmap_x3_step        : 4   ; /* [19..16]  */
        unsigned int    reserved_2            : 4   ; /* [23..20]  */
        unsigned int    g_tmap_x4_step        : 4   ; /* [27..24]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_STEP;

/* Define the union U_GHDR_TONEMAP_POS1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_tmap_x1_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_POS1;

/* Define the union U_GHDR_TONEMAP_POS2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_tmap_x2_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_POS2;

/* Define the union U_GHDR_TONEMAP_POS3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_tmap_x3_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_POS3;

/* Define the union U_GHDR_TONEMAP_POS4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_tmap_x4_pos         : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_POS4;

/* Define the union U_GHDR_TONEMAP_NUM */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_tmap_x1_num         : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 3   ; /* [7..5]  */
        unsigned int    g_tmap_x2_num         : 5   ; /* [12..8]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    g_tmap_x3_num         : 5   ; /* [20..16]  */
        unsigned int    reserved_2            : 3   ; /* [23..21]  */
        unsigned int    g_tmap_x4_num         : 5   ; /* [28..24]  */
        unsigned int    reserved_3            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_NUM;

/* Define the union U_GHDR_TONEMAP_LUMA_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_tmap_luma_coef0  : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_LUMA_COEF0;

/* Define the union U_GHDR_TONEMAP_LUMA_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_tmap_luma_coef1  : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_LUMA_COEF1;

/* Define the union U_GHDR_TONEMAP_LUMA_COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_tmap_luma_coef2  : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_LUMA_COEF2;

/* Define the union U_GHDR_TONEMAP_LUMA_SCALE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_tmap_luma_scale  : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_LUMA_SCALE;

/* Define the union U_GHDR_TONEMAP_COEF_SCALE */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_tmap_coef_scale  : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_COEF_SCALE;

/* Define the union U_GHDR_TONEMAP_OUT_CLIP_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_tmap_out_clip_min : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_OUT_CLIP_MIN;

/* Define the union U_GHDR_TONEMAP_OUT_CLIP_MAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_tmap_out_clip_max : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_TONEMAP_OUT_CLIP_MAX;

/* Define the union U_GHDR_GAMMA_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gmm_en           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_CTRL;

/* Define the union U_GHDR_GAMMA_REN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_gamma_rd_en      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_REN;

/* Define the union U_GHDR_GAMMMA_DATA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int ghdr_gamma_para_data   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_GHDR_GAMMMA_DATA;
/* Define the union U_GHDR_GAMMA_STEP1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_gmm_x1_step         : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    g_gmm_x2_step         : 4   ; /* [11..8]  */
        unsigned int    reserved_1            : 4   ; /* [15..12]  */
        unsigned int    g_gmm_x3_step         : 4   ; /* [19..16]  */
        unsigned int    reserved_2            : 4   ; /* [23..20]  */
        unsigned int    g_gmm_x4_step         : 4   ; /* [27..24]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_STEP1;

/* Define the union U_GHDR_GAMMA_STEP2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_gmm_x5_step         : 4   ; /* [3..0]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    g_gmm_x6_step         : 4   ; /* [11..8]  */
        unsigned int    reserved_1            : 4   ; /* [15..12]  */
        unsigned int    g_gmm_x7_step         : 4   ; /* [19..16]  */
        unsigned int    reserved_2            : 4   ; /* [23..20]  */
        unsigned int    g_gmm_x8_step         : 4   ; /* [27..24]  */
        unsigned int    reserved_3            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_STEP2;

/* Define the union U_GHDR_GAMMA_POS1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_gmm_x1_pos          : 16  ; /* [15..0]  */
        unsigned int    g_gmm_x2_pos          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_POS1;

/* Define the union U_GHDR_GAMMA_POS2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_gmm_x3_pos          : 16  ; /* [15..0]  */
        unsigned int    g_gmm_x4_pos          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_POS2;

/* Define the union U_GHDR_GAMMA_POS3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_gmm_x5_pos          : 16  ; /* [15..0]  */
        unsigned int    g_gmm_x6_pos          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_POS3;

/* Define the union U_GHDR_GAMMA_POS4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_gmm_x7_pos          : 16  ; /* [15..0]  */
        unsigned int    g_gmm_x8_pos          : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_POS4;

/* Define the union U_GHDR_GAMMA_NUM1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_gmm_x1_num          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    g_gmm_x2_num          : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    g_gmm_x3_num          : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    g_gmm_x4_num          : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_NUM1;

/* Define the union U_GHDR_GAMMA_NUM2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    g_gmm_x5_num          : 6   ; /* [5..0]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    g_gmm_x6_num          : 6   ; /* [13..8]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    g_gmm_x7_num          : 6   ; /* [21..16]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    g_gmm_x8_num          : 6   ; /* [29..24]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_GAMMA_NUM2;

/* Define the union U_GHDR_DITHER_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_tap_mode  : 2   ; /* [1..0]  */
        unsigned int    ghdr_dither_domain_mode : 1   ; /* [2]  */
        unsigned int    ghdr_dither_round     : 1   ; /* [3]  */
        unsigned int    ghdr_dither_mode      : 1   ; /* [4]  */
        unsigned int    ghdr_dither_en        : 1   ; /* [5]  */
        unsigned int    ghdr_dither_round_unlim : 1   ; /* [6]  */
        unsigned int    reserved_0            : 25  ; /* [31..7]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_CTRL;

/* Define the union U_GHDR_DITHER_THR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_thr_min   : 16  ; /* [15..0]  */
        unsigned int    ghdr_dither_thr_max   : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_THR;

/* Define the union U_GHDR_DITHER_SED_Y0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_sed_y0    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_SED_Y0;

/* Define the union U_GHDR_DITHER_SED_U0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_sed_u0    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_SED_U0;

/* Define the union U_GHDR_DITHER_SED_V0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_sed_v0    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_SED_V0;

/* Define the union U_GHDR_DITHER_SED_W0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_sed_w0    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_SED_W0;

/* Define the union U_GHDR_DITHER_SED_Y1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_sed_y1    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_SED_Y1;

/* Define the union U_GHDR_DITHER_SED_U1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_sed_u1    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_SED_U1;

/* Define the union U_GHDR_DITHER_SED_V1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_sed_v1    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_SED_V1;

/* Define the union U_GHDR_DITHER_SED_W1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ghdr_dither_sed_w1    : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_GHDR_DITHER_SED_W1;

/* Define the union U_HIHDR_G_RGB2YUV_CTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_en          : 1   ; /* [0]  */
        unsigned int    reserved_0            : 31  ; /* [31..1]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_CTRL;

/* Define the union U_HIHDR_G_RGB2YUV_COEF0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_coef00      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_COEF0;

/* Define the union U_HIHDR_G_RGB2YUV_COEF1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_coef01      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_COEF1;

/* Define the union U_HIHDR_G_RGB2YUV_COEF2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_coef02      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_COEF2;

/* Define the union U_HIHDR_G_RGB2YUV_COEF3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_coef10      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_COEF3;

/* Define the union U_HIHDR_G_RGB2YUV_COEF4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_coef11      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_COEF4;

/* Define the union U_HIHDR_G_RGB2YUV_COEF5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_coef12      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_COEF5;

/* Define the union U_HIHDR_G_RGB2YUV_COEF6 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_coef20      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_COEF6;

/* Define the union U_HIHDR_G_RGB2YUV_COEF7 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_coef21      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_COEF7;

/* Define the union U_HIHDR_G_RGB2YUV_COEF8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_coef22      : 15  ; /* [14..0]  */
        unsigned int    reserved_0            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_COEF8;

/* Define the union U_HIHDR_G_RGB2YUV_SCALE2P */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_scale2p     : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 29  ; /* [31..3]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_SCALE2P;

/* Define the union U_HIHDR_G_RGB2YUV_IDC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_idc0        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_IDC0;

/* Define the union U_HIHDR_G_RGB2YUV_IDC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_idc1        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_IDC1;

/* Define the union U_HIHDR_G_RGB2YUV_IDC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_idc2        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_IDC2;

/* Define the union U_HIHDR_G_RGB2YUV_ODC0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_odc0        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_ODC0;

/* Define the union U_HIHDR_G_RGB2YUV_ODC1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_odc1        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_ODC1;

/* Define the union U_HIHDR_G_RGB2YUV_ODC2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_odc2        : 11  ; /* [10..0]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_ODC2;

/* Define the union U_HIHDR_G_RGB2YUV_MIN */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_clip_min    : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_MIN;

/* Define the union U_HIHDR_G_RGB2YUV_MAX */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hihdr_r2y_clip_max    : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_HIHDR_G_RGB2YUV_MAX;

/* Define the union U_SMMU_SCR */
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

} U_SMMU_SCR;

/* Define the union U_SMMU_LP_CTRL */
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

} U_SMMU_LP_CTRL;

/* Define the union U_SMMU_MEM_SPEEDCTRL */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    RFS_EMAW              : 2   ; /* [1..0]  */
        unsigned int    RFS_EMA               : 3   ; /* [4..2]  */
        unsigned int    RFS_RET1N             : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SMMU_MEM_SPEEDCTRL;

/* Define the union U_SMMU_INTMASK_S */
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

} U_SMMU_INTMASK_S;

/* Define the union U_SMMU_INTRAW_S */
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

} U_SMMU_INTRAW_S;

/* Define the union U_SMMU_INTSTAT_S */
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

} U_SMMU_INTSTAT_S;

/* Define the union U_SMMU_INTCLR_S */
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

} U_SMMU_INTCLR_S;

/* Define the union U_SMMU_INTMASK_NS */
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

} U_SMMU_INTMASK_NS;

/* Define the union U_SMMU_INTRAW_NS */
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

} U_SMMU_INTRAW_NS;

/* Define the union U_SMMU_INTSTAT_NS */
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

} U_SMMU_INTSTAT_NS;

/* Define the union U_SMMU_INTCLR_NS */
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

} U_SMMU_INTCLR_NS;

/* Define the union U_SMMU_SCB_TTBR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scb_ttbr               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_SCB_TTBR;
/* Define the union U_SMMU_CB_TTBR */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cb_ttbr                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_CB_TTBR;
/* Define the union U_SMMU_ERR_RDADDR_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int err_s_rd_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_ERR_RDADDR_S;
/* Define the union U_SMMU_ERR_WRADDR_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int err_s_wr_addr          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_ERR_WRADDR_S;
/* Define the union U_SMMU_ERR_RDADDR_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int err_ns_rd_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_ERR_RDADDR_NS;
/* Define the union U_SMMU_ERR_WRADDR_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int err_ns_wr_addr         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_ERR_WRADDR_NS;
/* Define the union U_SMMU_FAULT_ADDR_PTW_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_ptw_s       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_ADDR_PTW_S;
/* Define the union U_SMMU_FAULT_ID_PTW_S */
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

} U_SMMU_FAULT_ID_PTW_S;

/* Define the union U_SMMU_FAULT_ADDR_PTW_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_ptw_ns      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_ADDR_PTW_NS;
/* Define the union U_SMMU_FAULT_ID_PTW_NS */
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

} U_SMMU_FAULT_ID_PTW_NS;

/* Define the union U_SMMU_FAULT_PTW_NUM */
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

} U_SMMU_FAULT_PTW_NUM;

/* Define the union U_SMMU_FAULT_ADDR_WR_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_wr_s        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_ADDR_WR_S;
/* Define the union U_SMMU_FAULT_TLB_WR_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_tlb_wr_s         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_TLB_WR_S;
/* Define the union U_SMMU_FAULT_ID_WR_S */
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

} U_SMMU_FAULT_ID_WR_S;

/* Define the union U_SMMU_FAULT_ADDR_WR_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_wr_ns       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_ADDR_WR_NS;
/* Define the union U_SMMU_FAULT_TLB_WR_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_tlb_wr_ns        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_TLB_WR_NS;
/* Define the union U_SMMU_FAULT_ID_WR_NS */
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

} U_SMMU_FAULT_ID_WR_NS;

/* Define the union U_SMMU_FAULT_ADDR_RD_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_rd_s        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_ADDR_RD_S;
/* Define the union U_SMMU_FAULT_TLB_RD_S */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_tlb_rd_s         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_TLB_RD_S;
/* Define the union U_SMMU_FAULT_ID_RD_S */
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

} U_SMMU_FAULT_ID_RD_S;

/* Define the union U_SMMU_FAULT_ADDR_RD_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_addr_rd_ns       : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_ADDR_RD_NS;
/* Define the union U_SMMU_FAULT_TLB_RD_NS */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int fault_tlb_rd_ns        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
        unsigned int    u32;

} U_SMMU_FAULT_TLB_RD_NS;
/* Define the union U_SMMU_FAULT_ID_RD_NS */
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

} U_SMMU_FAULT_ID_RD_NS;

/* Define the union U_SMMU_FAULT_TBU_INFO */
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

} U_SMMU_FAULT_TBU_INFO;

/* Define the union U_SMMU_FAULT_TBU_DBG */
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

} U_SMMU_FAULT_TBU_DBG;

/* Define the union U_SMMU_PREF_BUFFER_EMPTY */
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

} U_SMMU_PREF_BUFFER_EMPTY;

/* Define the union U_SMMU_PTWQ_IDLE */
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

} U_SMMU_PTWQ_IDLE;

/* Define the union U_SMMU_RESET_STATE */
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

} U_SMMU_RESET_STATE;

/* Define the union U_SMMU_MASTER_DBG0 */
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

} U_SMMU_MASTER_DBG0;

/* Define the union U_SMMU_MASTER_DBG1 */
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

} U_SMMU_MASTER_DBG1;

/* Define the union U_SMMU_MASTER_DBG2 */
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

} U_SMMU_MASTER_DBG2;

/* Define the union U_SMMU_MASTER_DBG3 */
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

} U_SMMU_MASTER_DBG3;

/* Define the union U_SMMU_MASTER_DBG4 */
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

} U_SMMU_MASTER_DBG4;

/* Define the union U_SMMU_MASTER_DBG5 */
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

} U_SMMU_MASTER_DBG5;

/* Define the union U_SMMU_MASTER_DBG6 */
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

} U_SMMU_MASTER_DBG6;

/* Define the union U_SMMU_MASTER_DBG7 */
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

} U_SMMU_MASTER_DBG7;

/* Define the union U_SMMU_MASTER_DBG8 */
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

} U_SMMU_MASTER_DBG8;

//==============================================================================
/* Define the global struct */
typedef struct
{
    U_VOCTRL               VOCTRL                            ; /* 0x0 */
    U_VOINTSTA             VOINTSTA                          ; /* 0x4 */
    U_VOMSKINTSTA          VOMSKINTSTA                       ; /* 0x8 */
    U_VOINTMSK             VOINTMSK                          ; /* 0xc */
    U_VODEBUG              VODEBUG                           ; /* 0x10 */
    unsigned int           reserved_0[3]                     ; /* 0x14~0x1c */
    U_VDPVERSION1          VDPVERSION1                       ; /* 0x20 */
    U_VDPVERSION2          VDPVERSION2                       ; /* 0x24 */
    unsigned int           reserved_1                     ; /* 0x28 */
    U_VOLOWPOWER_CTRL      VOLOWPOWER_CTRL                   ; /* 0x2c */
    unsigned int           reserved_2[8]                     ; /* 0x30~0x4c */
    U_VOUFSTA              VOUFSTA                           ; /* 0x50 */
    U_VOUFCLR              VOUFCLR                           ; /* 0x54 */
    unsigned int           reserved_3[2]                     ; /* 0x58~0x5c */
    U_VOINTPROC_TIM        VOINTPROC_TIM                     ; /* 0x60 */
    U_VOMSKINTSTA2         VOMSKINTSTA2                      ; /* 0x64 */
    U_VOINTSTA2            VOINTSTA2                         ; /* 0x68 */
    U_VOFPGATEST           VOFPGATEST                        ; /* 0x6c */
    unsigned int           reserved_4[37]                     ; /* 0x70~0x100 */
    U_VO_MUX_DAC           VO_MUX_DAC                        ; /* 0x104 */
    unsigned int           reserved_5[6]                     ; /* 0x108~0x11c */
    U_VO_DAC_CTRL0         VO_DAC_CTRL0                      ; /* 0x120 */
    unsigned int           reserved_6[3]                     ; /* 0x124~0x12c */
    U_VO_DAC_C_CTRL        VO_DAC_C_CTRL                     ; /* 0x130 */
    U_VO_DAC_R_CTRL        VO_DAC_R_CTRL                     ; /* 0x134 */
    U_VO_DAC_G_CTRL        VO_DAC_G_CTRL                     ; /* 0x138 */
    U_VO_DAC_B_CTRL        VO_DAC_B_CTRL                     ; /* 0x13c */
    unsigned int           reserved_7[4]                     ; /* 0x140~0x14c */
    U_VO_DAC_CTRL1         VO_DAC_CTRL1                      ; /* 0x150 */
    unsigned int           reserved_8[43]                     ; /* 0x154~0x1fc */
    U_CBM_BKG1             CBM_BKG1                          ; /* 0x200 */
    unsigned int           reserved_9                     ; /* 0x204 */
    U_CBM_MIX1             CBM_MIX1                          ; /* 0x208 */
    unsigned int           reserved_10[637]                     ; /* 0x20c~0xbfc */
    U_LINK_CTRL0           LINK_CTRL0                        ; /* 0xc00 */
    unsigned int           reserved_11[128]                     ; /* 0xc04~0xe00 */
    U_PARA_ADDR_VHD_CHN00   PARA_ADDR_VHD_CHN00              ; /* 0xe04 */
    unsigned int           reserved_12                     ; /* 0xe08 */
    U_PARA_ADDR_VHD_CHN01   PARA_ADDR_VHD_CHN01              ; /* 0xe0c */
    unsigned int           reserved_13                     ; /* 0xe10 */
    U_PARA_ADDR_VHD_CHN02   PARA_ADDR_VHD_CHN02              ; /* 0xe14 */
    unsigned int           reserved_14                     ; /* 0xe18 */
    U_PARA_ADDR_VHD_CHN03   PARA_ADDR_VHD_CHN03              ; /* 0xe1c */
    unsigned int           reserved_15                     ; /* 0xe20 */
    U_PARA_ADDR_VHD_CHN04   PARA_ADDR_VHD_CHN04              ; /* 0xe24 */
    unsigned int           reserved_16                     ; /* 0xe28 */
    U_PARA_ADDR_VHD_CHN05   PARA_ADDR_VHD_CHN05              ; /* 0xe2c */
    unsigned int           reserved_17                     ; /* 0xe30 */
    U_PARA_ADDR_VHD_CHN06   PARA_ADDR_VHD_CHN06              ; /* 0xe34 */
    unsigned int           reserved_18                     ; /* 0xe38 */
    U_PARA_ADDR_VHD_CHN07   PARA_ADDR_VHD_CHN07              ; /* 0xe3c */
    unsigned int           reserved_19                     ; /* 0xe40 */
    U_PARA_ADDR_VHD_CHN08   PARA_ADDR_VHD_CHN08              ; /* 0xe44 */
    unsigned int           reserved_20                     ; /* 0xe48 */
    U_PARA_ADDR_VHD_CHN09   PARA_ADDR_VHD_CHN09              ; /* 0xe4c */
    unsigned int           reserved_21                     ; /* 0xe50 */
    U_PARA_ADDR_VHD_CHN10   PARA_ADDR_VHD_CHN10              ; /* 0xe54 */
    unsigned int           reserved_22                     ; /* 0xe58 */
    U_PARA_ADDR_VHD_CHN11   PARA_ADDR_VHD_CHN11              ; /* 0xe5c */
    unsigned int           reserved_23                     ; /* 0xe60 */
    U_PARA_ADDR_VHD_CHN12   PARA_ADDR_VHD_CHN12              ; /* 0xe64 */
    unsigned int           reserved_24                     ; /* 0xe68 */
    U_PARA_ADDR_VHD_CHN13   PARA_ADDR_VHD_CHN13              ; /* 0xe6c */
    unsigned int           reserved_25                     ; /* 0xe70 */
    U_PARA_ADDR_VHD_CHN14   PARA_ADDR_VHD_CHN14              ; /* 0xe74 */
    unsigned int           reserved_26                     ; /* 0xe78 */
    U_PARA_ADDR_VHD_CHN15   PARA_ADDR_VHD_CHN15              ; /* 0xe7c */
    unsigned int           reserved_27                     ; /* 0xe80 */
    U_PARA_ADDR_VHD_CHN16   PARA_ADDR_VHD_CHN16              ; /* 0xe84 */
    unsigned int           reserved_28                     ; /* 0xe88 */
    U_PARA_ADDR_VHD_CHN17   PARA_ADDR_VHD_CHN17              ; /* 0xe8c */
    unsigned int           reserved_29                     ; /* 0xe90 */
    U_PARA_ADDR_VHD_CHN18   PARA_ADDR_VHD_CHN18              ; /* 0xe94 */
    unsigned int           reserved_30                     ; /* 0xe98 */
    U_PARA_ADDR_VHD_CHN19   PARA_ADDR_VHD_CHN19              ; /* 0xe9c */
    unsigned int           reserved_31                     ; /* 0xea0 */
    U_PARA_ADDR_VHD_CHN20   PARA_ADDR_VHD_CHN20              ; /* 0xea4 */
    unsigned int           reserved_32                     ; /* 0xea8 */
    U_PARA_ADDR_VHD_CHN21   PARA_ADDR_VHD_CHN21              ; /* 0xeac */
    unsigned int           reserved_33                     ; /* 0xeb0 */
    U_PARA_ADDR_VHD_CHN22   PARA_ADDR_VHD_CHN22              ; /* 0xeb4 */
    unsigned int           reserved_34                     ; /* 0xeb8 */
    U_PARA_ADDR_VHD_CHN23   PARA_ADDR_VHD_CHN23              ; /* 0xebc */
    unsigned int           reserved_35                     ; /* 0xec0 */
    U_PARA_ADDR_VHD_CHN24   PARA_ADDR_VHD_CHN24              ; /* 0xec4 */
    unsigned int           reserved_36                     ; /* 0xec8 */
    U_PARA_ADDR_VHD_CHN25   PARA_ADDR_VHD_CHN25              ; /* 0xecc */
    unsigned int           reserved_37                     ; /* 0xed0 */
    U_PARA_ADDR_VHD_CHN26   PARA_ADDR_VHD_CHN26              ; /* 0xed4 */
    unsigned int           reserved_38                     ; /* 0xed8 */
    U_PARA_ADDR_VHD_CHN27   PARA_ADDR_VHD_CHN27              ; /* 0xedc */
    unsigned int           reserved_39                     ; /* 0xee0 */
    U_PARA_ADDR_VHD_CHN28   PARA_ADDR_VHD_CHN28              ; /* 0xee4 */
    unsigned int           reserved_40                     ; /* 0xee8 */
    U_PARA_ADDR_VHD_CHN29   PARA_ADDR_VHD_CHN29              ; /* 0xeec */
    unsigned int           reserved_41                     ; /* 0xef0 */
    U_PARA_ADDR_VHD_CHN30   PARA_ADDR_VHD_CHN30              ; /* 0xef4 */
    unsigned int           reserved_42                     ; /* 0xef8 */
    U_PARA_ADDR_VHD_CHN31   PARA_ADDR_VHD_CHN31              ; /* 0xefc */
    U_PARA_UP_VHD          PARA_UP_VHD                       ; /* 0xf00 */
    unsigned int           reserved_43[17]                     ; /* 0xf04~0xf44 */
    U_PARA_CONFLICT_CLR    PARA_CONFLICT_CLR                 ; /* 0xf48 */
    U_PARA_CONFLICT_STA    PARA_CONFLICT_STA                 ; /* 0xf4c */
    unsigned int           reserved_44[1068]                     ; /* 0xf50~0x1ffc */
    U_V0_CTRL              V0_CTRL                           ; /* 0x2000 */
    U_V0_UPD               V0_UPD                            ; /* 0x2004 */
    U_V0_ORESO_READ        V0_ORESO_READ                     ; /* 0x2008 */
    unsigned int           reserved_45[3]                     ; /* 0x200c~0x2014 */
    U_V0_CTRL_WORK         V0_CTRL_WORK                      ; /* 0x2018 */
    unsigned int           reserved_46[25]                     ; /* 0x201c~0x207c */
    U_V0_DFPOS             V0_DFPOS                          ; /* 0x2080 */
    U_V0_DLPOS             V0_DLPOS                          ; /* 0x2084 */
    U_V0_VFPOS             V0_VFPOS                          ; /* 0x2088 */
    U_V0_VLPOS             V0_VLPOS                          ; /* 0x208c */
    U_V0_BK                V0_BK                             ; /* 0x2090 */
    U_V0_ALPHA             V0_ALPHA                          ; /* 0x2094 */
    U_V0_MUTE_BK           V0_MUTE_BK                        ; /* 0x2098 */
    unsigned int           reserved_47[25]                     ; /* 0x209c~0x20fc */
    U_V0_HPZME             V0_HPZME                          ; /* 0x2100 */
    U_V0_HPZME_COEF        V0_HPZME_COEF                     ; /* 0x2104 */
    unsigned int           reserved_48[110]                     ; /* 0x2108~0x22bc */
    U_V0_HSP               V0_HSP                            ; /* 0x22c0 */
    U_V0_HLOFFSET          V0_HLOFFSET                       ; /* 0x22c4 */
    U_V0_HCOFFSET          V0_HCOFFSET                       ; /* 0x22c8 */
    U_V0_HZONE0DELTA       V0_HZONE0DELTA                    ; /* 0x22cc */
    U_V0_HZONE2DELTA       V0_HZONE2DELTA                    ; /* 0x22d0 */
    U_V0_HZONEEND          V0_HZONEEND                       ; /* 0x22d4 */
    U_V0_VSP               V0_VSP                            ; /* 0x22d8 */
    U_V0_VSR               V0_VSR                            ; /* 0x22dc */
    U_V0_VOFFSET           V0_VOFFSET                        ; /* 0x22e0 */
    U_V0_VBOFFSET          V0_VBOFFSET                       ; /* 0x22e4 */
    U_V0_ZME_ORESO         V0_ZME_ORESO                      ; /* 0x22e8 */
    unsigned int           reserved_49                     ; /* 0x22ec */
    U_V0_ZMECOEF           V0_ZMECOEF                        ; /* 0x22f0 */
    U_V0_ZMECOEFAD         V0_ZMECOEFAD                      ; /* 0x22f4 */
    U_V0_ZME_SHOOTCTRL_HL   V0_ZME_SHOOTCTRL_HL              ; /* 0x22f8 */
    U_V0_ZME_SHOOTCTRL_HC   V0_ZME_SHOOTCTRL_HC              ; /* 0x22fc */
    U_V0_ZME_SHOOTCTRL_VL   V0_ZME_SHOOTCTRL_VL              ; /* 0x2300 */
    U_V0_ZME_SHOOTCTRL_VC   V0_ZME_SHOOTCTRL_VC              ; /* 0x2304 */
    unsigned int           reserved_50[110]                     ; /* 0x2308~0x24bc */
    U_V0_ZME2_HSP          V0_ZME2_HSP                       ; /* 0x24c0 */
    U_V0_ZME2_HLOFFSET     V0_ZME2_HLOFFSET                  ; /* 0x24c4 */
    U_V0_ZME2_HCOFFSET     V0_ZME2_HCOFFSET                  ; /* 0x24c8 */
    U_V0_ZME2_HZONE0DELTA   V0_ZME2_HZONE0DELTA              ; /* 0x24cc */
    U_V0_ZME2_HZONE2DELTA   V0_ZME2_HZONE2DELTA              ; /* 0x24d0 */
    U_V0_ZME2_HZONEEND     V0_ZME2_HZONEEND                  ; /* 0x24d4 */
    U_V0_ZME2_VSP          V0_ZME2_VSP                       ; /* 0x24d8 */
    U_V0_ZME2_VSR          V0_ZME2_VSR                       ; /* 0x24dc */
    U_V0_ZME2_VOFFSET      V0_ZME2_VOFFSET                   ; /* 0x24e0 */
    U_V0_ZME2_VBOFFSET     V0_ZME2_VBOFFSET                  ; /* 0x24e4 */
    U_V0_ZME2_ORESO        V0_ZME2_ORESO                     ; /* 0x24e8 */
    unsigned int           reserved_51                     ; /* 0x24ec */
    U_V0_ZME2_ZMECOEF      V0_ZME2_ZMECOEF                   ; /* 0x24f0 */
    U_V0_ZME2_ZMECOEFAD    V0_ZME2_ZMECOEFAD                 ; /* 0x24f4 */
    U_V0_ZME2_SHOOTCTRL_HL   V0_ZME2_SHOOTCTRL_HL            ; /* 0x24f8 */
    U_V0_ZME2_SHOOTCTRL_HC   V0_ZME2_SHOOTCTRL_HC            ; /* 0x24fc */
    U_V0_ZME2_SHOOTCTRL_VL   V0_ZME2_SHOOTCTRL_VL            ; /* 0x2500 */
    U_V0_ZME2_SHOOTCTRL_VC   V0_ZME2_SHOOTCTRL_VC            ; /* 0x2504 */
    unsigned int           reserved_52[62]                     ; /* 0x2508~0x25fc */
    U_V0_HFIR_CTRL         V0_HFIR_CTRL                      ; /* 0x2600 */
    U_V0_IFIRCOEF01        V0_IFIRCOEF01                     ; /* 0x2604 */
    U_V0_IFIRCOEF23        V0_IFIRCOEF23                     ; /* 0x2608 */
    U_V0_IFIRCOEF45        V0_IFIRCOEF45                     ; /* 0x260c */
    U_V0_IFIRCOEF67        V0_IFIRCOEF67                     ; /* 0x2610 */
    unsigned int           reserved_53[635]                     ; /* 0x2614~0x2ffc */
    U_V1_CTRL              V1_CTRL                           ; /* 0x3000 */
    U_V1_UPD               V1_UPD                            ; /* 0x3004 */
    U_V1_ORESO_READ        V1_ORESO_READ                     ; /* 0x3008 */
    unsigned int           reserved_54[3]                     ; /* 0x300c~0x3014 */
    U_V1_CTRL_WORK         V1_CTRL_WORK                      ; /* 0x3018 */
    unsigned int           reserved_55[25]                     ; /* 0x301c~0x307c */
    U_V1_DFPOS             V1_DFPOS                          ; /* 0x3080 */
    U_V1_DLPOS             V1_DLPOS                          ; /* 0x3084 */
    U_V1_VFPOS             V1_VFPOS                          ; /* 0x3088 */
    U_V1_VLPOS             V1_VLPOS                          ; /* 0x308c */
    U_V1_BK                V1_BK                             ; /* 0x3090 */
    U_V1_ALPHA             V1_ALPHA                          ; /* 0x3094 */
    U_V1_MUTE_BK           V1_MUTE_BK                        ; /* 0x3098 */
    unsigned int           reserved_56[153]                     ; /* 0x309c~0x32fc */
    U_V1_HFIR_CTRL         V1_HFIR_CTRL                      ; /* 0x3300 */
    U_V1_IFIRCOEF01        V1_IFIRCOEF01                     ; /* 0x3304 */
    unsigned int           reserved_57[830]                     ; /* 0x3308~0x3ffc */
    U_VP0_CTRL             VP0_CTRL                          ; /* 0x4000 */
    U_VP0_UPD              VP0_UPD                           ; /* 0x4004 */
    U_VP0_ORESO_READ       VP0_ORESO_READ                    ; /* 0x4008 */
    unsigned int           reserved_58                     ; /* 0x400c */
    U_VP0_IRESO            VP0_IRESO                         ; /* 0x4010 */
    unsigned int           reserved_59                     ; /* 0x4014 */
    U_VP0_CTRL_WORK        VP0_CTRL_WORK                     ; /* 0x4018 */
    unsigned int           reserved_60[25]                     ; /* 0x401c~0x407c */
    U_VP0_DFPOS            VP0_DFPOS                         ; /* 0x4080 */
    U_VP0_DLPOS            VP0_DLPOS                         ; /* 0x4084 */
    U_VP0_VFPOS            VP0_VFPOS                         ; /* 0x4088 */
    U_VP0_VLPOS            VP0_VLPOS                         ; /* 0x408c */
    U_VP0_BK               VP0_BK                            ; /* 0x4090 */
    U_VP0_ALPHA            VP0_ALPHA                         ; /* 0x4094 */
    U_VP0_MUTE_BK          VP0_MUTE_BK                       ; /* 0x4098 */
    unsigned int           reserved_61[25]                     ; /* 0x409c~0x40fc */
    U_MIXV0_BKG            MIXV0_BKG                         ; /* 0x4100 */
    unsigned int           reserved_62                     ; /* 0x4104 */
    U_MIXV0_MIX            MIXV0_MIX                         ; /* 0x4108 */
    unsigned int           reserved_63[29]                     ; /* 0x410c~0x417c */
    U_VP0_DOF_CTRL         VP0_DOF_CTRL                      ; /* 0x4180 */
    U_VP0_DOF_STEP         VP0_DOF_STEP                      ; /* 0x4184 */
    U_VP0_DOF_BKG          VP0_DOF_BKG                       ; /* 0x4188 */
    unsigned int           reserved_64[925]                     ; /* 0x418c~0x4ffc */
    U_G0_CTRL              G0_CTRL                           ; /* 0x5000 */
    U_G0_UPD               G0_UPD                            ; /* 0x5004 */
    U_G0_GALPHA_SUM        G0_GALPHA_SUM                     ; /* 0x5008 */
    U_G0_ORESO_READ        G0_ORESO_READ                     ; /* 0x500c */
    unsigned int           reserved_65[2]                     ; /* 0x5010~0x5014 */
    U_G0_CTRL_WORK         G0_CTRL_WORK                      ; /* 0x5018 */
    unsigned int           reserved_66[25]                     ; /* 0x501c~0x507c */
    U_G0_DFPOS             G0_DFPOS                          ; /* 0x5080 */
    U_G0_DLPOS             G0_DLPOS                          ; /* 0x5084 */
    U_G0_VFPOS             G0_VFPOS                          ; /* 0x5088 */
    U_G0_VLPOS             G0_VLPOS                          ; /* 0x508c */
    U_G0_BK                G0_BK                             ; /* 0x5090 */
    U_G0_ALPHA             G0_ALPHA                          ; /* 0x5094 */
    U_G0_MUTE_BK           G0_MUTE_BK                        ; /* 0x5098 */
    unsigned int           reserved_67[89]                     ; /* 0x509c~0x51fc */
    U_G0_DOF_CTRL          G0_DOF_CTRL                       ; /* 0x5200 */
    U_G0_DOF_STEP          G0_DOF_STEP                       ; /* 0x5204 */
    U_G0_DOF_BKG           G0_DOF_BKG                        ; /* 0x5208 */
    U_G0_DOF_ALPHA         G0_DOF_ALPHA                      ; /* 0x520c */
    unsigned int           reserved_68[380]                     ; /* 0x5210~0x57fc */
    U_G1_CTRL              G1_CTRL                           ; /* 0x5800 */
    U_G1_UPD               G1_UPD                            ; /* 0x5804 */
    U_G1_GALPHA_SUM        G1_GALPHA_SUM                     ; /* 0x5808 */
    U_G1_ORESO_READ        G1_ORESO_READ                     ; /* 0x580c */
    unsigned int           reserved_69[2]                     ; /* 0x5810~0x5814 */
    U_G1_CTRL_WORK         G1_CTRL_WORK                      ; /* 0x5818 */
    unsigned int           reserved_70[25]                     ; /* 0x581c~0x587c */
    U_G1_DFPOS             G1_DFPOS                          ; /* 0x5880 */
    U_G1_DLPOS             G1_DLPOS                          ; /* 0x5884 */
    U_G1_VFPOS             G1_VFPOS                          ; /* 0x5888 */
    U_G1_VLPOS             G1_VLPOS                          ; /* 0x588c */
    U_G1_BK                G1_BK                             ; /* 0x5890 */
    U_G1_ALPHA             G1_ALPHA                          ; /* 0x5894 */
    U_G1_MUTE_BK           G1_MUTE_BK                        ; /* 0x5898 */
    unsigned int           reserved_71[89]                     ; /* 0x589c~0x59fc */
    U_G1_DOF_CTRL          G1_DOF_CTRL                       ; /* 0x5a00 */
    U_G1_DOF_STEP          G1_DOF_STEP                       ; /* 0x5a04 */
    U_G1_DOF_BKG           G1_DOF_BKG                        ; /* 0x5a08 */
    U_G1_DOF_ALPHA         G1_DOF_ALPHA                      ; /* 0x5a0c */
    unsigned int           reserved_72[380]                     ; /* 0x5a10~0x5ffc */
    U_WBC_DHD0_CTRL        WBC_DHD0_CTRL                     ; /* 0x6000 */
    U_WBC_DHD0_UPD         WBC_DHD0_UPD                      ; /* 0x6004 */
    unsigned int           reserved_73[4]                     ; /* 0x6008~0x6014 */
    U_WBC_DHD0_CTRL_WORK   WBC_DHD0_CTRL_WORK                ; /* 0x6018 */
    unsigned int           reserved_74[25]                     ; /* 0x601c~0x607c */
    U_WBC_DHD0_ZME_HINFO   WBC_DHD0_ZME_HINFO                ; /* 0x6080 */
    U_WBC_DHD0_ZME_HSP     WBC_DHD0_ZME_HSP                  ; /* 0x6084 */
    U_WBC_DHD0_ZME_HLOFFSET   WBC_DHD0_ZME_HLOFFSET          ; /* 0x6088 */
    U_WBC_DHD0_ZME_HCOFFSET   WBC_DHD0_ZME_HCOFFSET          ; /* 0x608c */
    unsigned int           reserved_75[5]                     ; /* 0x6090~0x60a0 */
    U_WBC_DHD0_ZME_HRCOEF   WBC_DHD0_ZME_HRCOEF              ; /* 0x60a4 */
    U_WBC_DHD0_ZME_HYCOEFAD   WBC_DHD0_ZME_HYCOEFAD          ; /* 0x60a8 */
    U_WBC_DHD0_ZME_HCCOEFAD   WBC_DHD0_ZME_HCCOEFAD          ; /* 0x60ac */
    unsigned int           reserved_76[20]                     ; /* 0x60b0~0x60fc */
    U_WBC_DHD0_CSCIDC      WBC_DHD0_CSCIDC                   ; /* 0x6100 */
    U_WBC_DHD0_CSCODC      WBC_DHD0_CSCODC                   ; /* 0x6104 */
    U_WBC_DHD0_CSCP0       WBC_DHD0_CSCP0                    ; /* 0x6108 */
    U_WBC_DHD0_CSCP1       WBC_DHD0_CSCP1                    ; /* 0x610c */
    U_WBC_DHD0_CSCP2       WBC_DHD0_CSCP2                    ; /* 0x6110 */
    U_WBC_DHD0_CSCP3       WBC_DHD0_CSCP3                    ; /* 0x6114 */
    U_WBC_DHD0_CSCP4       WBC_DHD0_CSCP4                    ; /* 0x6118 */
    unsigned int           reserved_77[61]                     ; /* 0x611c~0x620c */
    U_WBC_DHD0_HCDS        WBC_DHD0_HCDS                     ; /* 0x6210 */
    U_WBC_DHD0_HCDS_COEF0   WBC_DHD0_HCDS_COEF0              ; /* 0x6214 */
    U_WBC_DHD0_HCDS_COEF1   WBC_DHD0_HCDS_COEF1              ; /* 0x6218 */
    unsigned int           reserved_78[25]                     ; /* 0x621c~0x627c */
    U_WBC_DHD0_DITHER_CTRL   WBC_DHD0_DITHER_CTRL            ; /* 0x6280 */
    U_WBC_DHD0_DITHER_COEF0   WBC_DHD0_DITHER_COEF0          ; /* 0x6284 */
    U_WBC_DHD0_DITHER_COEF1   WBC_DHD0_DITHER_COEF1          ; /* 0x6288 */
    unsigned int           reserved_79[29]                     ; /* 0x628c~0x62fc */
    U_WBC_DHD0_ZME_VINFO   WBC_DHD0_ZME_VINFO                ; /* 0x6300 */
    U_WBC_DHD0_ZME_VSP     WBC_DHD0_ZME_VSP                  ; /* 0x6304 */
    U_WBC_DHD0_ZME_VSR     WBC_DHD0_ZME_VSR                  ; /* 0x6308 */
    U_WBC_DHD0_ZME_VOFFSET   WBC_DHD0_ZME_VOFFSET            ; /* 0x630c */
    U_WBC_DHD0_ZME_VBOFFSET   WBC_DHD0_ZME_VBOFFSET          ; /* 0x6310 */
    U_WBC_DHD0_ZME_VCOEF   WBC_DHD0_ZME_VCOEF                ; /* 0x6314 */
    U_WBC_DHD0_ZME_VCOEFAD   WBC_DHD0_ZME_VCOEFAD            ; /* 0x6318 */
    unsigned int           reserved_80[130]                     ; /* 0x631c~0x6520 */
    U_WBC_DHD0_FCROP       WBC_DHD0_FCROP                    ; /* 0x6524 */
    U_WBC_DHD0_LCROP       WBC_DHD0_LCROP                    ; /* 0x6528 */
    unsigned int           reserved_81[181]                     ; /* 0x652c~0x67fc */
    U_GP0_CTRL             GP0_CTRL                          ; /* 0x6800 */
    U_GP0_UPD              GP0_UPD                           ; /* 0x6804 */
    U_GP0_GALPHA_SUM       GP0_GALPHA_SUM                    ; /* 0x6808 */
    U_GP0_ORESO_READ       GP0_ORESO_READ                    ; /* 0x680c */
    U_GP0_IRESO            GP0_IRESO                         ; /* 0x6810 */
    unsigned int           reserved_82                     ; /* 0x6814 */
    U_GP0_CTRL_WORK        GP0_CTRL_WORK                     ; /* 0x6818 */
    unsigned int           reserved_83[25]                     ; /* 0x681c~0x687c */
    U_GP0_DFPOS            GP0_DFPOS                         ; /* 0x6880 */
    U_GP0_DLPOS            GP0_DLPOS                         ; /* 0x6884 */
    U_GP0_VFPOS            GP0_VFPOS                         ; /* 0x6888 */
    U_GP0_VLPOS            GP0_VLPOS                         ; /* 0x688c */
    U_GP0_BK               GP0_BK                            ; /* 0x6890 */
    U_GP0_ALPHA            GP0_ALPHA                         ; /* 0x6894 */
    U_GP0_MUTE_BK          GP0_MUTE_BK                       ; /* 0x6898 */
    unsigned int           reserved_84[25]                     ; /* 0x689c~0x68fc */
    U_MIXG0_BKG            MIXG0_BKG                         ; /* 0x6900 */
    U_MIXG0_BKALPHA        MIXG0_BKALPHA                     ; /* 0x6904 */
    U_MIXG0_MIX            MIXG0_MIX                         ; /* 0x6908 */
    unsigned int           reserved_85[61]                     ; /* 0x690c~0x69fc */
    U_GP0_ZME_HINFO        GP0_ZME_HINFO                     ; /* 0x6a00 */
    U_GP0_ZME_HSP          GP0_ZME_HSP                       ; /* 0x6a04 */
    U_GP0_ZME_HLOFFSET     GP0_ZME_HLOFFSET                  ; /* 0x6a08 */
    U_GP0_ZME_HCOFFSET     GP0_ZME_HCOFFSET                  ; /* 0x6a0c */
    U_GP0_ZME_VINFO        GP0_ZME_VINFO                     ; /* 0x6a10 */
    U_GP0_ZME_VSP          GP0_ZME_VSP                       ; /* 0x6a14 */
    U_GP0_ZME_VSR          GP0_ZME_VSR                       ; /* 0x6a18 */
    U_GP0_ZME_VOFFSET      GP0_ZME_VOFFSET                   ; /* 0x6a1c */
    U_GP0_ZMECOEF          GP0_ZMECOEF                       ; /* 0x6a20 */
    U_GP0_ZMECOEFAD        GP0_ZMECOEFAD                     ; /* 0x6a24 */
    unsigned int           reserved_86[374]                     ; /* 0x6a28~0x6ffc */
    U_SPCTRL               SPCTRL                            ; /* 0x7000 */
    U_SPGAIN               SPGAIN                            ; /* 0x7004 */
    U_SPPEAKSHOOTCTL       SPPEAKSHOOTCTL                    ; /* 0x7008 */
    U_SPGAINPOS            SPGAINPOS                         ; /* 0x700c */
    U_SPGAINNEG            SPGAINNEG                         ; /* 0x7010 */
    U_SPOVERTHR            SPOVERTHR                         ; /* 0x7014 */
    U_SPUNDERTHR           SPUNDERTHR                        ; /* 0x7018 */
    U_SPCORINGZERO         SPCORINGZERO                      ; /* 0x701c */
    U_SPCORINGRATIO        SPCORINGRATIO                     ; /* 0x7020 */
    U_SPLMTRATIO           SPLMTRATIO                        ; /* 0x7024 */
    U_SPLMTPOS0            SPLMTPOS0                         ; /* 0x7028 */
    U_SPBOUNDPOS           SPBOUNDPOS                        ; /* 0x702c */
    U_SPLMTNEG0            SPLMTNEG0                         ; /* 0x7030 */
    U_SPLMTNEG1            SPLMTNEG1                         ; /* 0x7034 */
    U_SPBOUNDNEG           SPBOUNDNEG                        ; /* 0x7038 */
    U_SPEDGESHOOTCTL       SPEDGESHOOTCTL                    ; /* 0x703c */
    U_SPEDGEEI             SPEDGEEI                          ; /* 0x7040 */
    U_SPGRADMIN            SPGRADMIN                         ; /* 0x7044 */
    U_SPGRADCTR            SPGRADCTR                         ; /* 0x7048 */
    U_SPSHOOTRATIO         SPSHOOTRATIO                      ; /* 0x704c */
    unsigned int           reserved_87[108]                     ; /* 0x7050~0x71fc */
    U_VHDACCTHD1           VHDACCTHD1                        ; /* 0x7200 */
    U_VHDACCTHD2           VHDACCTHD2                        ; /* 0x7204 */
    U_VHDACCDEMO           VHDACCDEMO                        ; /* 0x7208 */
    U_VHDACCLOW1           VHDACCLOW1                        ; /* 0x720c */
    U_VHDACCLOW2           VHDACCLOW2                        ; /* 0x7210 */
    U_VHDACCLOW3           VHDACCLOW3                        ; /* 0x7214 */
    U_VHDACCMED1           VHDACCMED1                        ; /* 0x7218 */
    U_VHDACCMED2           VHDACCMED2                        ; /* 0x721c */
    U_VHDACCMED3           VHDACCMED3                        ; /* 0x7220 */
    U_VHDACCHIGH1          VHDACCHIGH1                       ; /* 0x7224 */
    U_VHDACCHIGH2          VHDACCHIGH2                       ; /* 0x7228 */
    U_VHDACCHIGH3          VHDACCHIGH3                       ; /* 0x722c */
    U_VHDACC3LOW           VHDACC3LOW                        ; /* 0x7230 */
    U_VHDACC3MED           VHDACC3MED                        ; /* 0x7234 */
    U_VHDACC3HIGH          VHDACC3HIGH                       ; /* 0x7238 */
    U_VHDACCTOTAL          VHDACCTOTAL                       ; /* 0x723c */
    U_VHDACC64HIST_0       VHDACC64HIST_0                    ; /* 0x7240 */
    U_VHDACC64HIST_1       VHDACC64HIST_1                    ; /* 0x7244 */
    U_VHDACC64HIST_2       VHDACC64HIST_2                    ; /* 0x7248 */
    U_VHDACC64HIST_3       VHDACC64HIST_3                    ; /* 0x724c */
    U_VHDACC64HIST_4       VHDACC64HIST_4                    ; /* 0x7250 */
    U_VHDACC64HIST_5       VHDACC64HIST_5                    ; /* 0x7254 */
    U_VHDACC64HIST_6       VHDACC64HIST_6                    ; /* 0x7258 */
    U_VHDACC64HIST_7       VHDACC64HIST_7                    ; /* 0x725c */
    U_VHDACC64HIST_8       VHDACC64HIST_8                    ; /* 0x7260 */
    U_VHDACC64HIST_9       VHDACC64HIST_9                    ; /* 0x7264 */
    U_VHDACC64HIST_10      VHDACC64HIST_10                   ; /* 0x7268 */
    U_VHDACC64HIST_11      VHDACC64HIST_11                   ; /* 0x726c */
    U_VHDACC64HIST_12      VHDACC64HIST_12                   ; /* 0x7270 */
    U_VHDACC64HIST_13      VHDACC64HIST_13                   ; /* 0x7274 */
    U_VHDACC64HIST_14      VHDACC64HIST_14                   ; /* 0x7278 */
    U_VHDACC64HIST_15      VHDACC64HIST_15                   ; /* 0x727c */
    U_VHDACC64HIST_16      VHDACC64HIST_16                   ; /* 0x7280 */
    U_VHDACC64HIST_17      VHDACC64HIST_17                   ; /* 0x7284 */
    U_VHDACC64HIST_18      VHDACC64HIST_18                   ; /* 0x7288 */
    U_VHDACC64HIST_19      VHDACC64HIST_19                   ; /* 0x728c */
    U_VHDACC64HIST_20      VHDACC64HIST_20                   ; /* 0x7290 */
    U_VHDACC64HIST_21      VHDACC64HIST_21                   ; /* 0x7294 */
    U_VHDACC64HIST_22      VHDACC64HIST_22                   ; /* 0x7298 */
    U_VHDACC64HIST_23      VHDACC64HIST_23                   ; /* 0x729c */
    U_VHDACC64HIST_24      VHDACC64HIST_24                   ; /* 0x72a0 */
    U_VHDACC64HIST_25      VHDACC64HIST_25                   ; /* 0x72a4 */
    U_VHDACC64HIST_26      VHDACC64HIST_26                   ; /* 0x72a8 */
    U_VHDACC64HIST_27      VHDACC64HIST_27                   ; /* 0x72ac */
    U_VHDACC64HIST_28      VHDACC64HIST_28                   ; /* 0x72b0 */
    U_VHDACC64HIST_29      VHDACC64HIST_29                   ; /* 0x72b4 */
    U_VHDACC64HIST_30      VHDACC64HIST_30                   ; /* 0x72b8 */
    U_VHDACC64HIST_31      VHDACC64HIST_31                   ; /* 0x72bc */
    U_VHDACC64HIST_32      VHDACC64HIST_32                   ; /* 0x72c0 */
    U_VHDACC64HIST_33      VHDACC64HIST_33                   ; /* 0x72c4 */
    U_VHDACC64HIST_34      VHDACC64HIST_34                   ; /* 0x72c8 */
    U_VHDACC64HIST_35      VHDACC64HIST_35                   ; /* 0x72cc */
    U_VHDACC64HIST_36      VHDACC64HIST_36                   ; /* 0x72d0 */
    U_VHDACC64HIST_37      VHDACC64HIST_37                   ; /* 0x72d4 */
    U_VHDACC64HIST_38      VHDACC64HIST_38                   ; /* 0x72d8 */
    U_VHDACC64HIST_39      VHDACC64HIST_39                   ; /* 0x72dc */
    U_VHDACC64HIST_40      VHDACC64HIST_40                   ; /* 0x72e0 */
    U_VHDACC64HIST_41      VHDACC64HIST_41                   ; /* 0x72e4 */
    U_VHDACC64HIST_42      VHDACC64HIST_42                   ; /* 0x72e8 */
    U_VHDACC64HIST_43      VHDACC64HIST_43                   ; /* 0x72ec */
    U_VHDACC64HIST_44      VHDACC64HIST_44                   ; /* 0x72f0 */
    U_VHDACC64HIST_45      VHDACC64HIST_45                   ; /* 0x72f4 */
    U_VHDACC64HIST_46      VHDACC64HIST_46                   ; /* 0x72f8 */
    U_VHDACC64HIST_47      VHDACC64HIST_47                   ; /* 0x72fc */
    U_VHDACC64HIST_48      VHDACC64HIST_48                   ; /* 0x7300 */
    U_VHDACC64HIST_49      VHDACC64HIST_49                   ; /* 0x7304 */
    U_VHDACC64HIST_50      VHDACC64HIST_50                   ; /* 0x7308 */
    U_VHDACC64HIST_51      VHDACC64HIST_51                   ; /* 0x730c */
    U_VHDACC64HIST_52      VHDACC64HIST_52                   ; /* 0x7310 */
    U_VHDACC64HIST_53      VHDACC64HIST_53                   ; /* 0x7314 */
    U_VHDACC64HIST_54      VHDACC64HIST_54                   ; /* 0x7318 */
    U_VHDACC64HIST_55      VHDACC64HIST_55                   ; /* 0x731c */
    U_VHDACC64HIST_56      VHDACC64HIST_56                   ; /* 0x7320 */
    U_VHDACC64HIST_57      VHDACC64HIST_57                   ; /* 0x7324 */
    U_VHDACC64HIST_58      VHDACC64HIST_58                   ; /* 0x7328 */
    U_VHDACC64HIST_59      VHDACC64HIST_59                   ; /* 0x732c */
    U_VHDACC64HIST_60      VHDACC64HIST_60                   ; /* 0x7330 */
    U_VHDACC64HIST_61      VHDACC64HIST_61                   ; /* 0x7334 */
    U_VHDACC64HIST_62      VHDACC64HIST_62                   ; /* 0x7338 */
    U_VHDACC64HIST_63      VHDACC64HIST_63                   ; /* 0x733c */
    unsigned int           reserved_88[816]                     ; /* 0x7340~0x7ffc */
    U_VDP_MST_OUTSTANDING   VDP_MST_OUTSTANDING              ; /* 0x8000 */
    U_VDP_MST_CTRL         VDP_MST_CTRL                      ; /* 0x8004 */
    unsigned int           reserved_89[2]                     ; /* 0x8008~0x800c */
    U_VDP_MST_RCHN_PRIO0   VDP_MST_RCHN_PRIO0                ; /* 0x8010 */
    unsigned int           reserved_90                     ; /* 0x8014 */
    U_VDP_MST_WCHN_PRIO0   VDP_MST_WCHN_PRIO0                ; /* 0x8018 */
    unsigned int           reserved_91[9]                     ; /* 0x801c~0x803c */
    U_VDP_MST_BUS_ERR_CLR   VDP_MST_BUS_ERR_CLR              ; /* 0x8040 */
    U_VDP_MST_BUS_ERR      VDP_MST_BUS_ERR                   ; /* 0x8044 */
    unsigned int           reserved_92[2]                     ; /* 0x8048~0x804c */
    U_VDP_MST_SRC0_STATUS0   VDP_MST_SRC0_STATUS0            ; /* 0x8050 */
    U_VDP_MST_SRC0_STATUS1   VDP_MST_SRC0_STATUS1            ; /* 0x8054 */
    unsigned int           reserved_93[6]                     ; /* 0x8058~0x806c */
    U_VDP_MST_DEBUG_CTRL   VDP_MST_DEBUG_CTRL                ; /* 0x8070 */
    U_VDP_MST_DEBUG_CLR    VDP_MST_DEBUG_CLR                 ; /* 0x8074 */
    unsigned int           reserved_94[2]                     ; /* 0x8078~0x807c */
    U_VDP_MST0_DET_LATENCY   VDP_MST0_DET_LATENCY            ; /* 0x8080 */
    unsigned int           reserved_95[3]                     ; /* 0x8084~0x808c */
    U_VDP_MST0_RD_INFO     VDP_MST0_RD_INFO                  ; /* 0x8090 */
    U_VDP_MST0_WR_INFO     VDP_MST0_WR_INFO                  ; /* 0x8094 */
    unsigned int           reserved_96[90]                     ; /* 0x8098~0x81fc */
    U_VID_READ_CTRL        VID_READ_CTRL                     ; /* 0x8200 */
    U_VID_MAC_CTRL         VID_MAC_CTRL                      ; /* 0x8204 */
    unsigned int           reserved_97[2]                     ; /* 0x8208~0x820c */
    U_VID_OUT_CTRL         VID_OUT_CTRL                      ; /* 0x8210 */
    U_VID_MUTE_BK          VID_MUTE_BK                       ; /* 0x8214 */
    unsigned int           reserved_98[2]                     ; /* 0x8218~0x821c */
    U_VID_SMMU_BYPASS      VID_SMMU_BYPASS                   ; /* 0x8220 */
    unsigned int           reserved_99[3]                     ; /* 0x8224~0x822c */
    U_VID_SRC_LFSIZE       VID_SRC_LFSIZE                    ; /* 0x8230 */
    U_VID_SRC_CFSIZE       VID_SRC_CFSIZE                    ; /* 0x8234 */
    unsigned int           reserved_100[2]                     ; /* 0x8238~0x823c */
    U_VID_SRC_INFO         VID_SRC_INFO                      ; /* 0x8240 */
    U_VID_SRC_RESO         VID_SRC_RESO                      ; /* 0x8244 */
    U_VID_SRC_CROP         VID_SRC_CROP                      ; /* 0x8248 */
    U_VID_IN_RESO          VID_IN_RESO                       ; /* 0x824c */
    U_VID_ADDR_H           VID_ADDR_H                        ; /* 0x8250 */
    U_VID_ADDR_L           VID_ADDR_L                        ; /* 0x8254 */
    U_VID_CADDR_H          VID_CADDR_H                       ; /* 0x8258 */
    U_VID_CADDR_L          VID_CADDR_L                       ; /* 0x825c */
    U_VID_NADDR_H          VID_NADDR_H                       ; /* 0x8260 */
    U_VID_NADDR_L          VID_NADDR_L                       ; /* 0x8264 */
    U_VID_NCADDR_H         VID_NCADDR_H                      ; /* 0x8268 */
    U_VID_NCADDR_L         VID_NCADDR_L                      ; /* 0x826c */
    U_VID_HEAD_ADDR_H      VID_HEAD_ADDR_H                   ; /* 0x8270 */
    U_VID_HEAD_ADDR_L      VID_HEAD_ADDR_L                   ; /* 0x8274 */
    U_VID_HEAD_CADDR_H     VID_HEAD_CADDR_H                  ; /* 0x8278 */
    U_VID_HEAD_CADDR_L     VID_HEAD_CADDR_L                  ; /* 0x827c */
    U_VID_2BIT_ADDR_H      VID_2BIT_ADDR_H                   ; /* 0x8280 */
    U_VID_2BIT_ADDR_L      VID_2BIT_ADDR_L                   ; /* 0x8284 */
    U_VID_2BIT_CADDR_H     VID_2BIT_CADDR_H                  ; /* 0x8288 */
    U_VID_2BIT_CADDR_L     VID_2BIT_CADDR_L                  ; /* 0x828c */
    U_VID_STRIDE           VID_STRIDE                        ; /* 0x8290 */
    U_VID_2BIT_STRIDE      VID_2BIT_STRIDE                   ; /* 0x8294 */
    U_VID_HEAD_STRIDE      VID_HEAD_STRIDE                   ; /* 0x8298 */
    unsigned int           reserved_101[5]                     ; /* 0x829c~0x82ac */
    U_VID_TESTPAT_CFG      VID_TESTPAT_CFG                   ; /* 0x82b0 */
    U_VID_TESTPAT_SEED     VID_TESTPAT_SEED                  ; /* 0x82b4 */
    unsigned int           reserved_102[2]                     ; /* 0x82b8~0x82bc */
    U_VID_DEBUG_CTRL       VID_DEBUG_CTRL                    ; /* 0x82c0 */
    U_VID_PRESS_CTRL       VID_PRESS_CTRL                    ; /* 0x82c4 */
    unsigned int           reserved_103[2]                     ; /* 0x82c8~0x82cc */
    U_VID_TUNL_CTRL        VID_TUNL_CTRL                     ; /* 0x82d0 */
    unsigned int           reserved_104                     ; /* 0x82d4 */
    U_VID_TUNL_ADDR_H      VID_TUNL_ADDR_H                   ; /* 0x82d8 */
    U_VID_TUNL_ADDR_L      VID_TUNL_ADDR_L                   ; /* 0x82dc */
    U_VID_IN_L_CHECKSUM0   VID_IN_L_CHECKSUM0                ; /* 0x82e0 */
    U_VID_IN_L_CHECKSUM1   VID_IN_L_CHECKSUM1                ; /* 0x82e4 */
    U_VID_IN_C_CHECKSUM0   VID_IN_C_CHECKSUM0                ; /* 0x82e8 */
    U_VID_IN_C_CHECKSUM1   VID_IN_C_CHECKSUM1                ; /* 0x82ec */
    U_VID_L_FIFOSTA0       VID_L_FIFOSTA0                    ; /* 0x82f0 */
    U_VID_L_FIFOSTA1       VID_L_FIFOSTA1                    ; /* 0x82f4 */
    U_VID_C_FIFOSTA0       VID_C_FIFOSTA0                    ; /* 0x82f8 */
    U_VID_C_FIFOSTA1       VID_C_FIFOSTA1                    ; /* 0x82fc */
    U_VID_L_CUR_FLOW       VID_L_CUR_FLOW                    ; /* 0x8300 */
    U_VID_L_CUR_SREQ_TIME   VID_L_CUR_SREQ_TIME              ; /* 0x8304 */
    U_VID_C_CUR_FLOW       VID_C_CUR_FLOW                    ; /* 0x8308 */
    U_VID_C_CUR_SREQ_TIME   VID_C_CUR_SREQ_TIME              ; /* 0x830c */
    U_VID_L_LAST_FLOW      VID_L_LAST_FLOW                   ; /* 0x8310 */
    U_VID_L_LAST_SREQ_TIME   VID_L_LAST_SREQ_TIME            ; /* 0x8314 */
    U_VID_C_LAST_FLOW      VID_C_LAST_FLOW                   ; /* 0x8318 */
    U_VID_C_LAST_SREQ_TIME   VID_C_LAST_SREQ_TIME            ; /* 0x831c */
    U_VID_WORK_RESO        VID_WORK_RESO                     ; /* 0x8320 */
    U_VID_WORK_FINFO       VID_WORK_FINFO                    ; /* 0x8324 */
    U_VID_LAST_YADDR       VID_LAST_YADDR                    ; /* 0x8328 */
    U_VID_LAST_CADDR       VID_LAST_CADDR                    ; /* 0x832c */
    U_VID_WORK_READ_CTRL   VID_WORK_READ_CTRL                ; /* 0x8330 */
    U_VID_WORK_SMMU_CTRL   VID_WORK_SMMU_CTRL                ; /* 0x8334 */
    U_VID_WORK_Y_ADDR      VID_WORK_Y_ADDR                   ; /* 0x8338 */
    U_VID_WORK_C_ADDR      VID_WORK_C_ADDR                   ; /* 0x833c */
    U_VID_WORK_Y_NADDR     VID_WORK_Y_NADDR                  ; /* 0x8340 */
    U_VID_WORK_C_NADDR     VID_WORK_C_NADDR                  ; /* 0x8344 */
    unsigned int           reserved_105[2]                     ; /* 0x8348~0x834c */
    U_VID_L_BUSY_TIME      VID_L_BUSY_TIME                   ; /* 0x8350 */
    U_VID_L_NEEDNORDY_TIME   VID_L_NEEDNORDY_TIME            ; /* 0x8354 */
    U_VID_L2_NEEDNORDY_TIME   VID_L2_NEEDNORDY_TIME          ; /* 0x8358 */
    unsigned int           reserved_106                     ; /* 0x835c */
    U_VID_C_BUSY_TIME      VID_C_BUSY_TIME                   ; /* 0x8360 */
    U_VID_C_NEEDNORDY_TIME   VID_C_NEEDNORDY_TIME            ; /* 0x8364 */
    U_VID_C2_NEEDNORDY_TIME   VID_C2_NEEDNORDY_TIME          ; /* 0x8368 */
    unsigned int           reserved_107[5]                     ; /* 0x836c~0x837c */
    U_VID_Y_DCMP_WRONG_STA   VID_Y_DCMP_WRONG_STA            ; /* 0x8380 */
    unsigned int           reserved_108[15]                     ; /* 0x8384~0x83bc */
    U_VID_C_DCMP_WRONG_STA   VID_C_DCMP_WRONG_STA            ; /* 0x83c0 */
    unsigned int           reserved_109[15]                     ; /* 0x83c4~0x83fc */
    U_V1_VID_READ_CTRL     V1_VID_READ_CTRL                  ; /* 0x8400 */
    U_V1_VID_MAC_CTRL      V1_VID_MAC_CTRL                   ; /* 0x8404 */
    unsigned int           reserved_110[2]                     ; /* 0x8408~0x840c */
    U_V1_VID_OUT_CTRL      V1_VID_OUT_CTRL                   ; /* 0x8410 */
    U_V1_VID_MUTE_BK       V1_VID_MUTE_BK                    ; /* 0x8414 */
    unsigned int           reserved_111[2]                     ; /* 0x8418~0x841c */
    U_V1_VID_SMMU_BYPASS   V1_VID_SMMU_BYPASS                ; /* 0x8420 */
    unsigned int           reserved_112[3]                     ; /* 0x8424~0x842c */
    U_V1_VID_SRC_LFSIZE    V1_VID_SRC_LFSIZE                 ; /* 0x8430 */
    U_V1_VID_SRC_CFSIZE    V1_VID_SRC_CFSIZE                 ; /* 0x8434 */
    unsigned int           reserved_113[2]                     ; /* 0x8438~0x843c */
    U_V1_VID_SRC_INFO      V1_VID_SRC_INFO                   ; /* 0x8440 */
    U_V1_VID_SRC_RESO      V1_VID_SRC_RESO                   ; /* 0x8444 */
    U_V1_VID_SRC_CROP      V1_VID_SRC_CROP                   ; /* 0x8448 */
    U_V1_VID_IN_RESO       V1_VID_IN_RESO                    ; /* 0x844c */
    U_V1_VID_ADDR_H        V1_VID_ADDR_H                     ; /* 0x8450 */
    U_V1_VID_ADDR_L        V1_VID_ADDR_L                     ; /* 0x8454 */
    U_V1_VID_CADDR_H       V1_VID_CADDR_H                    ; /* 0x8458 */
    U_V1_VID_CADDR_L       V1_VID_CADDR_L                    ; /* 0x845c */
    U_V1_VID_NADDR_H       V1_VID_NADDR_H                    ; /* 0x8460 */
    U_V1_VID_NADDR_L       V1_VID_NADDR_L                    ; /* 0x8464 */
    U_V1_VID_NCADDR_H      V1_VID_NCADDR_H                   ; /* 0x8468 */
    U_V1_VID_NCADDR_L      V1_VID_NCADDR_L                   ; /* 0x846c */
    U_V1_VID_HEAD_ADDR_H   V1_VID_HEAD_ADDR_H                ; /* 0x8470 */
    U_V1_VID_HEAD_ADDR_L   V1_VID_HEAD_ADDR_L                ; /* 0x8474 */
    U_V1_VID_HEAD_CADDR_H   V1_VID_HEAD_CADDR_H              ; /* 0x8478 */
    U_V1_VID_HEAD_CADDR_L   V1_VID_HEAD_CADDR_L              ; /* 0x847c */
    U_V1_VID_2BIT_ADDR_H   V1_VID_2BIT_ADDR_H                ; /* 0x8480 */
    U_V1_VID_2BIT_ADDR_L   V1_VID_2BIT_ADDR_L                ; /* 0x8484 */
    U_V1_VID_2BIT_CADDR_H   V1_VID_2BIT_CADDR_H              ; /* 0x8488 */
    U_V1_VID_2BIT_CADDR_L   V1_VID_2BIT_CADDR_L              ; /* 0x848c */
    U_V1_VID_STRIDE        V1_VID_STRIDE                     ; /* 0x8490 */
    U_V1_VID_2BIT_STRIDE   V1_VID_2BIT_STRIDE                ; /* 0x8494 */
    U_V1_VID_HEAD_STRIDE   V1_VID_HEAD_STRIDE                ; /* 0x8498 */
    unsigned int           reserved_114[5]                     ; /* 0x849c~0x84ac */
    U_V1_VID_TESTPAT_CFG   V1_VID_TESTPAT_CFG                ; /* 0x84b0 */
    U_V1_VID_TESTPAT_SEED   V1_VID_TESTPAT_SEED              ; /* 0x84b4 */
    unsigned int           reserved_115[2]                     ; /* 0x84b8~0x84bc */
    U_V1_VID_DEBUG_CTRL    V1_VID_DEBUG_CTRL                 ; /* 0x84c0 */
    U_V1_VID_PRESS_CTRL    V1_VID_PRESS_CTRL                 ; /* 0x84c4 */
    unsigned int           reserved_116[2]                     ; /* 0x84c8~0x84cc */
    U_V1_VID_TUNL_CTRL     V1_VID_TUNL_CTRL                  ; /* 0x84d0 */
    unsigned int           reserved_117                     ; /* 0x84d4 */
    U_V1_VID_TUNL_ADDR_H   V1_VID_TUNL_ADDR_H                ; /* 0x84d8 */
    U_V1_VID_TUNL_ADDR_L   V1_VID_TUNL_ADDR_L                ; /* 0x84dc */
    U_V1_VID_IN_L_CHECKSUM0   V1_VID_IN_L_CHECKSUM0          ; /* 0x84e0 */
    U_V1_VID_IN_L_CHECKSUM1   V1_VID_IN_L_CHECKSUM1          ; /* 0x84e4 */
    U_V1_VID_IN_C_CHECKSUM0   V1_VID_IN_C_CHECKSUM0          ; /* 0x84e8 */
    U_V1_VID_IN_C_CHECKSUM1   V1_VID_IN_C_CHECKSUM1          ; /* 0x84ec */
    U_V1_VID_L_FIFOSTA0    V1_VID_L_FIFOSTA0                 ; /* 0x84f0 */
    U_V1_VID_L_FIFOSTA1    V1_VID_L_FIFOSTA1                 ; /* 0x84f4 */
    U_V1_VID_C_FIFOSTA0    V1_VID_C_FIFOSTA0                 ; /* 0x84f8 */
    U_V1_VID_C_FIFOSTA1    V1_VID_C_FIFOSTA1                 ; /* 0x84fc */
    U_V1_VID_L_CUR_FLOW    V1_VID_L_CUR_FLOW                 ; /* 0x8500 */
    U_V1_VID_L_CUR_SREQ_TIME   V1_VID_L_CUR_SREQ_TIME        ; /* 0x8504 */
    U_V1_VID_C_CUR_FLOW    V1_VID_C_CUR_FLOW                 ; /* 0x8508 */
    U_V1_VID_C_CUR_SREQ_TIME   V1_VID_C_CUR_SREQ_TIME        ; /* 0x850c */
    U_V1_VID_L_LAST_FLOW   V1_VID_L_LAST_FLOW                ; /* 0x8510 */
    U_V1_VID_L_LAST_SREQ_TIME   V1_VID_L_LAST_SREQ_TIME      ; /* 0x8514 */
    U_V1_VID_C_LAST_FLOW   V1_VID_C_LAST_FLOW                ; /* 0x8518 */
    U_V1_VID_C_LAST_SREQ_TIME   V1_VID_C_LAST_SREQ_TIME      ; /* 0x851c */
    U_V1_VID_WORK_RESO     V1_VID_WORK_RESO                  ; /* 0x8520 */
    U_V1_VID_WORK_FINFO    V1_VID_WORK_FINFO                 ; /* 0x8524 */
    U_V1_VID_LAST_YADDR    V1_VID_LAST_YADDR                 ; /* 0x8528 */
    U_V1_VID_LAST_CADDR    V1_VID_LAST_CADDR                 ; /* 0x852c */
    U_V1_VID_WORK_READ_CTRL   V1_VID_WORK_READ_CTRL          ; /* 0x8530 */
    U_V1_VID_WORK_SMMU_CTRL   V1_VID_WORK_SMMU_CTRL          ; /* 0x8534 */
    U_V1_VID_WORK_Y_ADDR   V1_VID_WORK_Y_ADDR                ; /* 0x8538 */
    U_V1_VID_WORK_C_ADDR   V1_VID_WORK_C_ADDR                ; /* 0x853c */
    U_V1_VID_WORK_Y_NADDR   V1_VID_WORK_Y_NADDR              ; /* 0x8540 */
    U_V1_VID_WORK_C_NADDR   V1_VID_WORK_C_NADDR              ; /* 0x8544 */
    unsigned int           reserved_118[2]                     ; /* 0x8548~0x854c */
    U_V1_VID_L_BUSY_TIME   V1_VID_L_BUSY_TIME                ; /* 0x8550 */
    U_V1_VID_L_NEEDNORDY_TIME   V1_VID_L_NEEDNORDY_TIME      ; /* 0x8554 */
    U_V1_VID_L2_NEEDNORDY_TIME   V1_VID_L2_NEEDNORDY_TIME    ; /* 0x8558 */
    unsigned int           reserved_119                     ; /* 0x855c */
    U_V1_VID_C_BUSY_TIME   V1_VID_C_BUSY_TIME                ; /* 0x8560 */
    U_V1_VID_C_NEEDNORDY_TIME   V1_VID_C_NEEDNORDY_TIME      ; /* 0x8564 */
    U_V1_VID_C2_NEEDNORDY_TIME   V1_VID_C2_NEEDNORDY_TIME    ; /* 0x8568 */
    unsigned int           reserved_120[37]                     ; /* 0x856c~0x85fc */
    U_HWLD_TOP_CTRL        HWLD_TOP_CTRL                     ; /* 0x8600 */
    U_HWLD_TOP_REGUP       HWLD_TOP_REGUP                    ; /* 0x8604 */
    U_HWLD_TOP_SMMU_BYPASS   HWLD_TOP_SMMU_BYPASS            ; /* 0x8608 */
    unsigned int           reserved_121                     ; /* 0x860c */
    U_HWLD_TOP_DEBUG_STA0   HWLD_TOP_DEBUG_STA0              ; /* 0x8610 */
    U_HWLD_TOP_DEBUG_STA1   HWLD_TOP_DEBUG_STA1              ; /* 0x8614 */
    U_HWLD_TOP_DEBUG_STA2   HWLD_TOP_DEBUG_STA2              ; /* 0x8618 */
    U_HWLD_TOP_DEBUG_STA3   HWLD_TOP_DEBUG_STA3              ; /* 0x861c */
    unsigned int           reserved_122[56]                     ; /* 0x8620~0x86fc */
    U_VID_DTV_MODE         VID_DTV_MODE                      ; /* 0x8700 */
    U_VID_DTV_MODE_IMG     VID_DTV_MODE_IMG                  ; /* 0x8704 */
    unsigned int           reserved_123[2]                     ; /* 0x8708~0x870c */
    U_VID_DTV_GLB_FRM_INFO   VID_DTV_GLB_FRM_INFO            ; /* 0x8710 */
    U_VID_DTV_LOC_FRM_INFO_READY   VID_DTV_LOC_FRM_INFO_READY ; /* 0x8714 */
    U_VID_DTV_LOC_FRM_INFO   VID_DTV_LOC_FRM_INFO            ; /* 0x8718 */
    U_VID_DTV_LOC_FRM_INFO1   VID_DTV_LOC_FRM_INFO1          ; /* 0x871c */
    U_VID_DTV_BACK_ADDR    VID_DTV_BACK_ADDR                 ; /* 0x8720 */
    unsigned int           reserved_124                     ; /* 0x8724 */
    U_VID_DTV_BACK_PSW     VID_DTV_BACK_PSW                  ; /* 0x8728 */
    U_VID_DTV_CFG_READY    VID_DTV_CFG_READY                 ; /* 0x872c */
    U_VID_DTV_CHANGE_ADDR   VID_DTV_CHANGE_ADDR              ; /* 0x8730 */
    unsigned int           reserved_125                     ; /* 0x8734 */
    U_VID_DTV_DISP_ADDR    VID_DTV_DISP_ADDR                 ; /* 0x8738 */
    unsigned int           reserved_126                     ; /* 0x873c */
    U_VID_DTV_BACK_NUM     VID_DTV_BACK_NUM                  ; /* 0x8740 */
    U_VID_DTV_ERR_STA      VID_DTV_ERR_STA                   ; /* 0x8744 */
    U_VID_DTV_DEBUG_CLR    VID_DTV_DEBUG_CLR                 ; /* 0x8748 */
    U_VID_DTV_DEBUG1       VID_DTV_DEBUG1                    ; /* 0x874c */
    U_VID_DTV_DEBUG2       VID_DTV_DEBUG2                    ; /* 0x8750 */
    U_VID_DTV_DEBUG3       VID_DTV_DEBUG3                    ; /* 0x8754 */
    U_VID_DTV_DEBUG4       VID_DTV_DEBUG4                    ; /* 0x8758 */
    unsigned int           reserved_127[9]                     ; /* 0x875c~0x877c */
    U_V1_DTV_MODE          V1_DTV_MODE                       ; /* 0x8780 */
    U_V1_DTV_MODE_IMG      V1_DTV_MODE_IMG                   ; /* 0x8784 */
    unsigned int           reserved_128[2]                     ; /* 0x8788~0x878c */
    U_V1_DTV_GLB_FRM_INFO   V1_DTV_GLB_FRM_INFO              ; /* 0x8790 */
    U_V1_DTV_LOC_FRM_INFO_READY   V1_DTV_LOC_FRM_INFO_READY  ; /* 0x8794 */
    U_V1_DTV_LOC_FRM_INFO   V1_DTV_LOC_FRM_INFO              ; /* 0x8798 */
    U_V1_DTV_LOC_FRM_INFO1   V1_DTV_LOC_FRM_INFO1            ; /* 0x879c */
    U_V1_DTV_BACK_ADDR     V1_DTV_BACK_ADDR                  ; /* 0x87a0 */
    unsigned int           reserved_129                     ; /* 0x87a4 */
    U_V1_DTV_BACK_PSW      V1_DTV_BACK_PSW                   ; /* 0x87a8 */
    U_V1_DTV_CFG_READY     V1_DTV_CFG_READY                  ; /* 0x87ac */
    U_V1_DTV_CHANGE_ADDR   V1_DTV_CHANGE_ADDR                ; /* 0x87b0 */
    unsigned int           reserved_130                     ; /* 0x87b4 */
    U_V1_DTV_DISP_ADDR     V1_DTV_DISP_ADDR                  ; /* 0x87b8 */
    unsigned int           reserved_131                     ; /* 0x87bc */
    U_V1_DTV_BACK_NUM      V1_DTV_BACK_NUM                   ; /* 0x87c0 */
    U_V1_DTV_ERR_STA       V1_DTV_ERR_STA                    ; /* 0x87c4 */
    U_V1_DTV_DEBUG_CLR     V1_DTV_DEBUG_CLR                  ; /* 0x87c8 */
    U_V1_DTV_DEBUG1        V1_DTV_DEBUG1                     ; /* 0x87cc */
    U_V1_DTV_DEBUG2        V1_DTV_DEBUG2                     ; /* 0x87d0 */
    U_V1_DTV_DEBUG3        V1_DTV_DEBUG3                     ; /* 0x87d4 */
    U_V1_DTV_DEBUG4        V1_DTV_DEBUG4                     ; /* 0x87d8 */
    unsigned int           reserved_132[9]                     ; /* 0x87dc~0x87fc */
    U_V1_1_DTV_MODE        V1_1_DTV_MODE                     ; /* 0x8800 */
    U_V1_1_DTV_MODE_IMG    V1_1_DTV_MODE_IMG                 ; /* 0x8804 */
    unsigned int           reserved_133[2]                     ; /* 0x8808~0x880c */
    U_V1_1_DTV_GLB_FRM_INFO   V1_1_DTV_GLB_FRM_INFO          ; /* 0x8810 */
    U_V1_1_DTV_LOC_FRM_INFO_READY   V1_1_DTV_LOC_FRM_INFO_READY ; /* 0x8814 */
    U_V1_1_DTV_LOC_FRM_INFO   V1_1_DTV_LOC_FRM_INFO          ; /* 0x8818 */
    U_V1_1_DTV_LOC_FRM_INFO1   V1_1_DTV_LOC_FRM_INFO1        ; /* 0x881c */
    U_V1_1_DTV_BACK_ADDR   V1_1_DTV_BACK_ADDR                ; /* 0x8820 */
    unsigned int           reserved_134                     ; /* 0x8824 */
    U_V1_1_DTV_BACK_PSW    V1_1_DTV_BACK_PSW                 ; /* 0x8828 */
    U_V1_1_DTV_CFG_READY   V1_1_DTV_CFG_READY                ; /* 0x882c */
    U_V1_1_DTV_CHANGE_ADDR   V1_1_DTV_CHANGE_ADDR            ; /* 0x8830 */
    unsigned int           reserved_135                     ; /* 0x8834 */
    U_V1_1_DTV_DISP_ADDR   V1_1_DTV_DISP_ADDR                ; /* 0x8838 */
    unsigned int           reserved_136                     ; /* 0x883c */
    U_V1_1_DTV_BACK_NUM    V1_1_DTV_BACK_NUM                 ; /* 0x8840 */
    U_V1_1_DTV_ERR_STA     V1_1_DTV_ERR_STA                  ; /* 0x8844 */
    U_V1_1_DTV_DEBUG_CLR   V1_1_DTV_DEBUG_CLR                ; /* 0x8848 */
    U_V1_1_DTV_DEBUG1      V1_1_DTV_DEBUG1                   ; /* 0x884c */
    U_V1_1_DTV_DEBUG2      V1_1_DTV_DEBUG2                   ; /* 0x8850 */
    U_V1_1_DTV_DEBUG3      V1_1_DTV_DEBUG3                   ; /* 0x8854 */
    U_V1_1_DTV_DEBUG4      V1_1_DTV_DEBUG4                   ; /* 0x8858 */
    unsigned int           reserved_137[9]                     ; /* 0x885c~0x887c */
    U_V1_2_DTV_MODE        V1_2_DTV_MODE                     ; /* 0x8880 */
    U_V1_2_DTV_MODE_IMG    V1_2_DTV_MODE_IMG                 ; /* 0x8884 */
    unsigned int           reserved_138[2]                     ; /* 0x8888~0x888c */
    U_V1_2_DTV_GLB_FRM_INFO   V1_2_DTV_GLB_FRM_INFO          ; /* 0x8890 */
    U_V1_2_DTV_LOC_FRM_INFO_READY   V1_2_DTV_LOC_FRM_INFO_READY ; /* 0x8894 */
    U_V1_2_DTV_LOC_FRM_INFO   V1_2_DTV_LOC_FRM_INFO          ; /* 0x8898 */
    U_V1_2_DTV_LOC_FRM_INFO1   V1_2_DTV_LOC_FRM_INFO1        ; /* 0x889c */
    U_V1_2_DTV_BACK_ADDR   V1_2_DTV_BACK_ADDR                ; /* 0x88a0 */
    unsigned int           reserved_139                     ; /* 0x88a4 */
    U_V1_2_DTV_BACK_PSW    V1_2_DTV_BACK_PSW                 ; /* 0x88a8 */
    U_V1_2_DTV_CFG_READY   V1_2_DTV_CFG_READY                ; /* 0x88ac */
    U_V1_2_DTV_CHANGE_ADDR   V1_2_DTV_CHANGE_ADDR            ; /* 0x88b0 */
    unsigned int           reserved_140                     ; /* 0x88b4 */
    U_V1_2_DTV_DISP_ADDR   V1_2_DTV_DISP_ADDR                ; /* 0x88b8 */
    unsigned int           reserved_141                     ; /* 0x88bc */
    U_V1_2_DTV_BACK_NUM    V1_2_DTV_BACK_NUM                 ; /* 0x88c0 */
    U_V1_2_DTV_ERR_STA     V1_2_DTV_ERR_STA                  ; /* 0x88c4 */
    U_V1_2_DTV_DEBUG_CLR   V1_2_DTV_DEBUG_CLR                ; /* 0x88c8 */
    U_V1_2_DTV_DEBUG1      V1_2_DTV_DEBUG1                   ; /* 0x88cc */
    U_V1_2_DTV_DEBUG2      V1_2_DTV_DEBUG2                   ; /* 0x88d0 */
    U_V1_2_DTV_DEBUG3      V1_2_DTV_DEBUG3                   ; /* 0x88d4 */
    U_V1_2_DTV_DEBUG4      V1_2_DTV_DEBUG4                   ; /* 0x88d8 */
    unsigned int           reserved_142[9]                     ; /* 0x88dc~0x88fc */
    U_V1_3_DTV_MODE        V1_3_DTV_MODE                     ; /* 0x8900 */
    U_V1_3_DTV_MODE_IMG    V1_3_DTV_MODE_IMG                 ; /* 0x8904 */
    unsigned int           reserved_143[2]                     ; /* 0x8908~0x890c */
    U_V1_3_DTV_GLB_FRM_INFO   V1_3_DTV_GLB_FRM_INFO          ; /* 0x8910 */
    U_V1_3_DTV_LOC_FRM_INFO_READY   V1_3_DTV_LOC_FRM_INFO_READY ; /* 0x8914 */
    U_V1_3_DTV_LOC_FRM_INFO   V1_3_DTV_LOC_FRM_INFO          ; /* 0x8918 */
    U_V1_3_DTV_LOC_FRM_INFO1   V1_3_DTV_LOC_FRM_INFO1        ; /* 0x891c */
    U_V1_3_DTV_BACK_ADDR   V1_3_DTV_BACK_ADDR                ; /* 0x8920 */
    unsigned int           reserved_144                     ; /* 0x8924 */
    U_V1_3_DTV_BACK_PSW    V1_3_DTV_BACK_PSW                 ; /* 0x8928 */
    U_V1_3_DTV_CFG_READY   V1_3_DTV_CFG_READY                ; /* 0x892c */
    U_V1_3_DTV_CHANGE_ADDR   V1_3_DTV_CHANGE_ADDR            ; /* 0x8930 */
    unsigned int           reserved_145                     ; /* 0x8934 */
    U_V1_3_DTV_DISP_ADDR   V1_3_DTV_DISP_ADDR                ; /* 0x8938 */
    unsigned int           reserved_146                     ; /* 0x893c */
    U_V1_3_DTV_BACK_NUM    V1_3_DTV_BACK_NUM                 ; /* 0x8940 */
    U_V1_3_DTV_ERR_STA     V1_3_DTV_ERR_STA                  ; /* 0x8944 */
    U_V1_3_DTV_DEBUG_CLR   V1_3_DTV_DEBUG_CLR                ; /* 0x8948 */
    U_V1_3_DTV_DEBUG1      V1_3_DTV_DEBUG1                   ; /* 0x894c */
    U_V1_3_DTV_DEBUG2      V1_3_DTV_DEBUG2                   ; /* 0x8950 */
    U_V1_3_DTV_DEBUG3      V1_3_DTV_DEBUG3                   ; /* 0x8954 */
    U_V1_3_DTV_DEBUG4      V1_3_DTV_DEBUG4                   ; /* 0x8958 */
    unsigned int           reserved_147[9]                     ; /* 0x895c~0x897c */
    U_GFX_DTV_MODE         GFX_DTV_MODE                      ; /* 0x8980 */
    U_GFX_DTV_MODE_IMG     GFX_DTV_MODE_IMG                  ; /* 0x8984 */
    unsigned int           reserved_148[2]                     ; /* 0x8988~0x898c */
    U_GFX_DTV_GLB_FRM_INFO   GFX_DTV_GLB_FRM_INFO            ; /* 0x8990 */
    U_GFX_DTV_LOC_FRM_INFO_READY   GFX_DTV_LOC_FRM_INFO_READY ; /* 0x8994 */
    U_GFX_DTV_LOC_FRM_INFO   GFX_DTV_LOC_FRM_INFO            ; /* 0x8998 */
    U_GFX_DTV_LOC_FRM_INFO1   GFX_DTV_LOC_FRM_INFO1          ; /* 0x899c */
    U_GFX_DTV_BACK_ADDR    GFX_DTV_BACK_ADDR                 ; /* 0x89a0 */
    unsigned int           reserved_149                     ; /* 0x89a4 */
    U_GFX_DTV_BACK_PSW     GFX_DTV_BACK_PSW                  ; /* 0x89a8 */
    U_GFX_DTV_CFG_READY    GFX_DTV_CFG_READY                 ; /* 0x89ac */
    U_GFX_DTV_CHANGE_ADDR   GFX_DTV_CHANGE_ADDR              ; /* 0x89b0 */
    unsigned int           reserved_150                     ; /* 0x89b4 */
    U_GFX_DTV_DISP_ADDR    GFX_DTV_DISP_ADDR                 ; /* 0x89b8 */
    unsigned int           reserved_151                     ; /* 0x89bc */
    U_GFX_DTV_BACK_NUM     GFX_DTV_BACK_NUM                  ; /* 0x89c0 */
    U_GFX_DTV_ERR_STA      GFX_DTV_ERR_STA                   ; /* 0x89c4 */
    U_GFX_DTV_DEBUG_CLR    GFX_DTV_DEBUG_CLR                 ; /* 0x89c8 */
    U_GFX_DTV_DEBUG1       GFX_DTV_DEBUG1                    ; /* 0x89cc */
    U_GFX_DTV_DEBUG2       GFX_DTV_DEBUG2                    ; /* 0x89d0 */
    U_GFX_DTV_DEBUG3       GFX_DTV_DEBUG3                    ; /* 0x89d4 */
    U_GFX_DTV_DEBUG4       GFX_DTV_DEBUG4                    ; /* 0x89d8 */
    unsigned int           reserved_152[9]                     ; /* 0x89dc~0x89fc */
    U_GFX_READ_CTRL        GFX_READ_CTRL                     ; /* 0x8a00 */
    U_GFX_MAC_CTRL         GFX_MAC_CTRL                      ; /* 0x8a04 */
    U_GFX_OUT_CTRL         GFX_OUT_CTRL                      ; /* 0x8a08 */
    unsigned int           reserved_153                     ; /* 0x8a0c */
    U_GFX_MUTE_ALPHA       GFX_MUTE_ALPHA                    ; /* 0x8a10 */
    U_GFX_MUTE_BK          GFX_MUTE_BK                       ; /* 0x8a14 */
    unsigned int           reserved_154[2]                     ; /* 0x8a18~0x8a1c */
    U_GFX_SMMU_BYPASS      GFX_SMMU_BYPASS                   ; /* 0x8a20 */
    unsigned int           reserved_155                     ; /* 0x8a24 */
    U_GFX_1555_ALPHA       GFX_1555_ALPHA                    ; /* 0x8a28 */
    unsigned int           reserved_156                     ; /* 0x8a2c */
    U_GFX_DCMP_FRAMESIZE0   GFX_DCMP_FRAMESIZE0              ; /* 0x8a30 */
    U_GFX_DCMP_FRAMESIZE1   GFX_DCMP_FRAMESIZE1              ; /* 0x8a34 */
    unsigned int           reserved_157[2]                     ; /* 0x8a38~0x8a3c */
    U_GFX_SRC_INFO         GFX_SRC_INFO                      ; /* 0x8a40 */
    U_GFX_SRC_RESO         GFX_SRC_RESO                      ; /* 0x8a44 */
    U_GFX_SRC_CROP         GFX_SRC_CROP                      ; /* 0x8a48 */
    U_GFX_IRESO            GFX_IRESO                         ; /* 0x8a4c */
    U_GFX_ADDR_H           GFX_ADDR_H                        ; /* 0x8a50 */
    U_GFX_ADDR_L           GFX_ADDR_L                        ; /* 0x8a54 */
    U_GFX_NADDR_H          GFX_NADDR_H                       ; /* 0x8a58 */
    U_GFX_NADDR_L          GFX_NADDR_L                       ; /* 0x8a5c */
    U_GFX_STRIDE           GFX_STRIDE                        ; /* 0x8a60 */
    unsigned int           reserved_158[3]                     ; /* 0x8a64~0x8a6c */
    U_GFX_DCMP_ADDR_H      GFX_DCMP_ADDR_H                   ; /* 0x8a70 */
    U_GFX_DCMP_ADDR_L      GFX_DCMP_ADDR_L                   ; /* 0x8a74 */
    U_GFX_DCMP_NADDR_H     GFX_DCMP_NADDR_H                  ; /* 0x8a78 */
    U_GFX_DCMP_NADDR_L     GFX_DCMP_NADDR_L                  ; /* 0x8a7c */
    U_GFX_HEAD_ADDR_H      GFX_HEAD_ADDR_H                   ; /* 0x8a80 */
    U_GFX_HEAD_ADDR_L      GFX_HEAD_ADDR_L                   ; /* 0x8a84 */
    U_GFX_HEAD_STRIDE      GFX_HEAD_STRIDE                   ; /* 0x8a88 */
    unsigned int           reserved_159                     ; /* 0x8a8c */
    U_GFX_HEAD2_ADDR_H     GFX_HEAD2_ADDR_H                  ; /* 0x8a90 */
    U_GFX_HEAD2_ADDR_L     GFX_HEAD2_ADDR_L                  ; /* 0x8a94 */
    unsigned int           reserved_160[2]                     ; /* 0x8a98~0x8a9c */
    U_GFX_CKEY_MAX         GFX_CKEY_MAX                      ; /* 0x8aa0 */
    U_GFX_CKEY_MIN         GFX_CKEY_MIN                      ; /* 0x8aa4 */
    U_GFX_CKEY_MASK        GFX_CKEY_MASK                     ; /* 0x8aa8 */
    unsigned int           reserved_161                     ; /* 0x8aac */
    U_GFX_TESTPAT_CFG      GFX_TESTPAT_CFG                   ; /* 0x8ab0 */
    U_GFX_TESTPAT_SEED     GFX_TESTPAT_SEED                  ; /* 0x8ab4 */
    unsigned int           reserved_162[2]                     ; /* 0x8ab8~0x8abc */
    U_GFX_DEBUG_CTRL       GFX_DEBUG_CTRL                    ; /* 0x8ac0 */
    U_GFX_PRESS_CTRL       GFX_PRESS_CTRL                    ; /* 0x8ac4 */
    unsigned int           reserved_163[6]                     ; /* 0x8ac8~0x8adc */
    U_GFX_IN_AR_CHECKSUM0   GFX_IN_AR_CHECKSUM0              ; /* 0x8ae0 */
    U_GFX_IN_AR_CHECKSUM1   GFX_IN_AR_CHECKSUM1              ; /* 0x8ae4 */
    U_GFX_IN_GB_CHECKSUM0   GFX_IN_GB_CHECKSUM0              ; /* 0x8ae8 */
    U_GFX_IN_GB_CHECKSUM1   GFX_IN_GB_CHECKSUM1              ; /* 0x8aec */
    U_GFX_CHN0_FIFOSTA0    GFX_CHN0_FIFOSTA0                 ; /* 0x8af0 */
    U_GFX_CHN0_FIFOSTA1    GFX_CHN0_FIFOSTA1                 ; /* 0x8af4 */
    U_GFX_CHN1_FIFOSTA0    GFX_CHN1_FIFOSTA0                 ; /* 0x8af8 */
    U_GFX_CHN1_FIFOSTA1    GFX_CHN1_FIFOSTA1                 ; /* 0x8afc */
    U_GFX_CUR_FLOW         GFX_CUR_FLOW                      ; /* 0x8b00 */
    U_GFX_CUR_SREQ_TIME    GFX_CUR_SREQ_TIME                 ; /* 0x8b04 */
    U_GFX_LAST_FLOW        GFX_LAST_FLOW                     ; /* 0x8b08 */
    U_GFX_LAST_SREQ_TIME   GFX_LAST_SREQ_TIME                ; /* 0x8b0c */
    U_GFX_BUSY_TIME        GFX_BUSY_TIME                     ; /* 0x8b10 */
    U_GFX_AR_NEEDNORDY_TIME   GFX_AR_NEEDNORDY_TIME          ; /* 0x8b14 */
    U_GFX_GB_NEEDNORDY_TIME   GFX_GB_NEEDNORDY_TIME          ; /* 0x8b18 */
    unsigned int           reserved_164                     ; /* 0x8b1c */
    U_GFX_WORK_RESO        GFX_WORK_RESO                     ; /* 0x8b20 */
    U_GFX_WORK_FINFO       GFX_WORK_FINFO                    ; /* 0x8b24 */
    U_GFX_LAST_ADDR        GFX_LAST_ADDR                     ; /* 0x8b28 */
    unsigned int           reserved_165                     ; /* 0x8b2c */
    U_GFX_WORK_READ_CTRL   GFX_WORK_READ_CTRL                ; /* 0x8b30 */
    U_GFX_WORK_SMMU_CTRL   GFX_WORK_SMMU_CTRL                ; /* 0x8b34 */
    U_GFX_WORK_ADDR        GFX_WORK_ADDR                     ; /* 0x8b38 */
    U_GFX_WORK_NADDR       GFX_WORK_NADDR                    ; /* 0x8b3c */
    unsigned int           reserved_166[16]                     ; /* 0x8b40~0x8b7c */
    U_DCMP_WRONG_STA       DCMP_WRONG_STA                    ; /* 0x8b80 */
    unsigned int           reserved_167[3]                     ; /* 0x8b84~0x8b8c */
    U_DCMP_DEBUG_STA0      DCMP_DEBUG_STA0                   ; /* 0x8b90 */
    U_DCMP_DEBUG_STA1      DCMP_DEBUG_STA1                   ; /* 0x8b94 */
    U_DCMP_DEBUG_STA2      DCMP_DEBUG_STA2                   ; /* 0x8b98 */
    U_DCMP_DEBUG_STA3      DCMP_DEBUG_STA3                   ; /* 0x8b9c */
    unsigned int           reserved_168[24]                     ; /* 0x8ba0~0x8bfc */
    U_G1_GFX_READ_CTRL     G1_GFX_READ_CTRL                  ; /* 0x8c00 */
    U_G1_GFX_MAC_CTRL      G1_GFX_MAC_CTRL                   ; /* 0x8c04 */
    U_G1_GFX_OUT_CTRL      G1_GFX_OUT_CTRL                   ; /* 0x8c08 */
    unsigned int           reserved_169                     ; /* 0x8c0c */
    U_G1_GFX_MUTE_ALPHA    G1_GFX_MUTE_ALPHA                 ; /* 0x8c10 */
    U_G1_GFX_MUTE_BK       G1_GFX_MUTE_BK                    ; /* 0x8c14 */
    unsigned int           reserved_170[2]                     ; /* 0x8c18~0x8c1c */
    U_G1_GFX_SMMU_BYPASS   G1_GFX_SMMU_BYPASS                ; /* 0x8c20 */
    unsigned int           reserved_171                     ; /* 0x8c24 */
    U_G1_GFX_1555_ALPHA    G1_GFX_1555_ALPHA                 ; /* 0x8c28 */
    unsigned int           reserved_172                     ; /* 0x8c2c */
    U_G1_GFX_DCMP_FRAMESIZE0   G1_GFX_DCMP_FRAMESIZE0        ; /* 0x8c30 */
    U_G1_GFX_DCMP_FRAMESIZE1   G1_GFX_DCMP_FRAMESIZE1        ; /* 0x8c34 */
    unsigned int           reserved_173[2]                     ; /* 0x8c38~0x8c3c */
    U_G1_GFX_SRC_INFO      G1_GFX_SRC_INFO                   ; /* 0x8c40 */
    U_G1_GFX_SRC_RESO      G1_GFX_SRC_RESO                   ; /* 0x8c44 */
    U_G1_GFX_SRC_CROP      G1_GFX_SRC_CROP                   ; /* 0x8c48 */
    U_G1_GFX_IRESO         G1_GFX_IRESO                      ; /* 0x8c4c */
    U_G1_GFX_ADDR_H        G1_GFX_ADDR_H                     ; /* 0x8c50 */
    U_G1_GFX_ADDR_L        G1_GFX_ADDR_L                     ; /* 0x8c54 */
    U_G1_GFX_NADDR_H       G1_GFX_NADDR_H                    ; /* 0x8c58 */
    U_G1_GFX_NADDR_L       G1_GFX_NADDR_L                    ; /* 0x8c5c */
    U_G1_GFX_STRIDE        G1_GFX_STRIDE                     ; /* 0x8c60 */
    unsigned int           reserved_174[3]                     ; /* 0x8c64~0x8c6c */
    U_G1_GFX_DCMP_ADDR_H   G1_GFX_DCMP_ADDR_H                ; /* 0x8c70 */
    U_G1_GFX_DCMP_ADDR_L   G1_GFX_DCMP_ADDR_L                ; /* 0x8c74 */
    U_G1_GFX_DCMP_NADDR_H   G1_GFX_DCMP_NADDR_H              ; /* 0x8c78 */
    U_G1_GFX_DCMP_NADDR_L   G1_GFX_DCMP_NADDR_L              ; /* 0x8c7c */
    U_G1_GFX_HEAD_ADDR_H   G1_GFX_HEAD_ADDR_H                ; /* 0x8c80 */
    U_G1_GFX_HEAD_ADDR_L   G1_GFX_HEAD_ADDR_L                ; /* 0x8c84 */
    U_G1_GFX_HEAD_STRIDE   G1_GFX_HEAD_STRIDE                ; /* 0x8c88 */
    unsigned int           reserved_175                     ; /* 0x8c8c */
    U_G1_GFX_HEAD2_ADDR_H   G1_GFX_HEAD2_ADDR_H              ; /* 0x8c90 */
    U_G1_GFX_HEAD2_ADDR_L   G1_GFX_HEAD2_ADDR_L              ; /* 0x8c94 */
    unsigned int           reserved_176[2]                     ; /* 0x8c98~0x8c9c */
    U_G1_GFX_CKEY_MAX      G1_GFX_CKEY_MAX                   ; /* 0x8ca0 */
    U_G1_GFX_CKEY_MIN      G1_GFX_CKEY_MIN                   ; /* 0x8ca4 */
    U_G1_GFX_CKEY_MASK     G1_GFX_CKEY_MASK                  ; /* 0x8ca8 */
    unsigned int           reserved_177                     ; /* 0x8cac */
    U_G1_GFX_TESTPAT_CFG   G1_GFX_TESTPAT_CFG                ; /* 0x8cb0 */
    U_G1_GFX_TESTPAT_SEED   G1_GFX_TESTPAT_SEED              ; /* 0x8cb4 */
    unsigned int           reserved_178[2]                     ; /* 0x8cb8~0x8cbc */
    U_G1_GFX_DEBUG_CTRL    G1_GFX_DEBUG_CTRL                 ; /* 0x8cc0 */
    U_G1_GFX_PRESS_CTRL    G1_GFX_PRESS_CTRL                 ; /* 0x8cc4 */
    unsigned int           reserved_179[6]                     ; /* 0x8cc8~0x8cdc */
    U_G1_GFX_IN_AR_CHECKSUM0   G1_GFX_IN_AR_CHECKSUM0        ; /* 0x8ce0 */
    U_G1_GFX_IN_AR_CHECKSUM1   G1_GFX_IN_AR_CHECKSUM1        ; /* 0x8ce4 */
    U_G1_GFX_IN_GB_CHECKSUM0   G1_GFX_IN_GB_CHECKSUM0        ; /* 0x8ce8 */
    U_G1_GFX_IN_GB_CHECKSUM1   G1_GFX_IN_GB_CHECKSUM1        ; /* 0x8cec */
    U_G1_GFX_CHN0_FIFOSTA0   G1_GFX_CHN0_FIFOSTA0            ; /* 0x8cf0 */
    U_G1_GFX_CHN0_FIFOSTA1   G1_GFX_CHN0_FIFOSTA1            ; /* 0x8cf4 */
    U_G1_GFX_CHN1_FIFOSTA0   G1_GFX_CHN1_FIFOSTA0            ; /* 0x8cf8 */
    U_G1_GFX_CHN1_FIFOSTA1   G1_GFX_CHN1_FIFOSTA1            ; /* 0x8cfc */
    U_G1_GFX_CUR_FLOW      G1_GFX_CUR_FLOW                   ; /* 0x8d00 */
    U_G1_GFX_CUR_SREQ_TIME   G1_GFX_CUR_SREQ_TIME            ; /* 0x8d04 */
    U_G1_GFX_LAST_FLOW     G1_GFX_LAST_FLOW                  ; /* 0x8d08 */
    U_G1_GFX_LAST_SREQ_TIME   G1_GFX_LAST_SREQ_TIME          ; /* 0x8d0c */
    U_G1_GFX_BUSY_TIME     G1_GFX_BUSY_TIME                  ; /* 0x8d10 */
    U_G1_GFX_AR_NEEDNORDY_TIME   G1_GFX_AR_NEEDNORDY_TIME    ; /* 0x8d14 */
    U_G1_GFX_GB_NEEDNORDY_TIME   G1_GFX_GB_NEEDNORDY_TIME    ; /* 0x8d18 */
    unsigned int           reserved_180                     ; /* 0x8d1c */
    U_G1_GFX_WORK_RESO     G1_GFX_WORK_RESO                  ; /* 0x8d20 */
    U_G1_GFX_WORK_FINFO    G1_GFX_WORK_FINFO                 ; /* 0x8d24 */
    U_G1_GFX_LAST_ADDR     G1_GFX_LAST_ADDR                  ; /* 0x8d28 */
    unsigned int           reserved_181                     ; /* 0x8d2c */
    U_G1_GFX_WORK_READ_CTRL   G1_GFX_WORK_READ_CTRL          ; /* 0x8d30 */
    U_G1_GFX_WORK_SMMU_CTRL   G1_GFX_WORK_SMMU_CTRL          ; /* 0x8d34 */
    U_G1_GFX_WORK_ADDR     G1_GFX_WORK_ADDR                  ; /* 0x8d38 */
    U_G1_GFX_WORK_NADDR    G1_GFX_WORK_NADDR                 ; /* 0x8d3c */
    unsigned int           reserved_182[304]                     ; /* 0x8d40~0x91fc */
    U_WBC_CTRL             WBC_CTRL                          ; /* 0x9200 */
    U_WBC_MAC_CTRL         WBC_MAC_CTRL                      ; /* 0x9204 */
    unsigned int           reserved_183[3]                     ; /* 0x9208~0x9210 */
    U_WBC_SMMU_BYPASS      WBC_SMMU_BYPASS                   ; /* 0x9214 */
    unsigned int           reserved_184[2]                     ; /* 0x9218~0x921c */
    U_WBC_LOWDLYCTRL       WBC_LOWDLYCTRL                    ; /* 0x9220 */
    U_WBC_TUNLADDR_H       WBC_TUNLADDR_H                    ; /* 0x9224 */
    U_WBC_TUNLADDR_L       WBC_TUNLADDR_L                    ; /* 0x9228 */
    U_WBC_LOWDLYSTA        WBC_LOWDLYSTA                     ; /* 0x922c */
    unsigned int           reserved_185[8]                     ; /* 0x9230~0x924c */
    U_WBC_YADDR_H          WBC_YADDR_H                       ; /* 0x9250 */
    U_WBC_YADDR_L          WBC_YADDR_L                       ; /* 0x9254 */
    U_WBC_CADDR_H          WBC_CADDR_H                       ; /* 0x9258 */
    U_WBC_CADDR_L          WBC_CADDR_L                       ; /* 0x925c */
    U_WBC_YSTRIDE          WBC_YSTRIDE                       ; /* 0x9260 */
    U_WBC_CSTRIDE          WBC_CSTRIDE                       ; /* 0x9264 */
    unsigned int           reserved_186[2]                     ; /* 0x9268~0x926c */
    U_WBC_YNADDR_H         WBC_YNADDR_H                      ; /* 0x9270 */
    U_WBC_YNADDR_L         WBC_YNADDR_L                      ; /* 0x9274 */
    U_WBC_CNADDR_H         WBC_CNADDR_H                      ; /* 0x9278 */
    U_WBC_CNADDR_L         WBC_CNADDR_L                      ; /* 0x927c */
    U_WBC_YNSTRIDE         WBC_YNSTRIDE                      ; /* 0x9280 */
    U_WBC_CNSTRIDE         WBC_CNSTRIDE                      ; /* 0x9284 */
    U_WBC_STT_ADDR_H       WBC_STT_ADDR_H                    ; /* 0x9288 */
    U_WBC_STT_ADDR_L       WBC_STT_ADDR_L                    ; /* 0x928c */
    unsigned int           reserved_187[8]                     ; /* 0x9290~0x92ac */
    U_WBC_STA              WBC_STA                           ; /* 0x92b0 */
    U_WBC_LINE_NUM         WBC_LINE_NUM                      ; /* 0x92b4 */
    U_WBC_CAP_RESO         WBC_CAP_RESO                      ; /* 0x92b8 */
    unsigned int           reserved_188                     ; /* 0x92bc */
    U_WBC_CAP_INFO         WBC_CAP_INFO                      ; /* 0x92c0 */
    U_WBC_CAP_INFO1        WBC_CAP_INFO1                     ; /* 0x92c4 */
    U_WBC_CAP_CHKSUM       WBC_CAP_CHKSUM                    ; /* 0x92c8 */
    U_WBC_CAP_CHKSUM1      WBC_CAP_CHKSUM1                   ; /* 0x92cc */
    U_WBC_WORK_CTRL        WBC_WORK_CTRL                     ; /* 0x92d0 */
    U_WBC_WORK_YADDR       WBC_WORK_YADDR                    ; /* 0x92d4 */
    U_WBC_WORK_CADDR       WBC_WORK_CADDR                    ; /* 0x92d8 */
    U_WBC_WORK_SMMU        WBC_WORK_SMMU                     ; /* 0x92dc */
    U_WBC_WORK_LOWDLYCTRL   WBC_WORK_LOWDLYCTRL              ; /* 0x92e0 */
    unsigned int           reserved_189[839]                     ; /* 0x92e4~0x9ffc */
    U_V1_MRG_CTRL          V1_MRG_CTRL                       ; /* 0xa000 */
    U_V1_MRG_DISP_POS      V1_MRG_DISP_POS                   ; /* 0xa004 */
    U_V1_MRG_DISP_RESO     V1_MRG_DISP_RESO                  ; /* 0xa008 */
    U_V1_MRG_SRC_RESO      V1_MRG_SRC_RESO                   ; /* 0xa00c */
    U_V1_MRG_SRC_OFFSET    V1_MRG_SRC_OFFSET                 ; /* 0xa010 */
    U_V1_MRG_Y_ADDR        V1_MRG_Y_ADDR                     ; /* 0xa014 */
    U_V1_MRG_C_ADDR        V1_MRG_C_ADDR                     ; /* 0xa018 */
    U_V1_MRG_STRIDE        V1_MRG_STRIDE                     ; /* 0xa01c */
    U_V1_MRG_YH_ADDR       V1_MRG_YH_ADDR                    ; /* 0xa020 */
    U_V1_MRG_CH_ADDR       V1_MRG_CH_ADDR                    ; /* 0xa024 */
    U_V1_MRG_HSTRIDE       V1_MRG_HSTRIDE                    ; /* 0xa028 */
    unsigned int           reserved_190[5]                     ; /* 0xa02c~0xa03c */
    U_V1_MRG_READ_CTRL     V1_MRG_READ_CTRL                  ; /* 0xa040 */
    U_V1_MRG_READ_EN       V1_MRG_READ_EN                    ; /* 0xa044 */
    U_V1_MRG_DEBUG_INFO0   V1_MRG_DEBUG_INFO0                ; /* 0xa048 */
    unsigned int           reserved_191                     ; /* 0xa04c */
    U_V1_MRG_WORK_EN       V1_MRG_WORK_EN                    ; /* 0xa050 */
    U_V1_MRG_WORK_MUTE     V1_MRG_WORK_MUTE                  ; /* 0xa054 */
    U_V1_MRG_WORK_R0_DPOS0   V1_MRG_WORK_R0_DPOS0            ; /* 0xa058 */
    U_V1_MRG_WORK_R0_DPOS1   V1_MRG_WORK_R0_DPOS1            ; /* 0xa05c */
    U_V1_MRG_WORK_R1_DPOS0   V1_MRG_WORK_R1_DPOS0            ; /* 0xa060 */
    U_V1_MRG_WORK_R1_DPOS1   V1_MRG_WORK_R1_DPOS1            ; /* 0xa064 */
    U_V1_MRG_WORK_R2_DPOS0   V1_MRG_WORK_R2_DPOS0            ; /* 0xa068 */
    U_V1_MRG_WORK_R2_DPOS1   V1_MRG_WORK_R2_DPOS1            ; /* 0xa06c */
    U_V1_MRG_WORK_R3_DPOS0   V1_MRG_WORK_R3_DPOS0            ; /* 0xa070 */
    U_V1_MRG_WORK_R3_DPOS1   V1_MRG_WORK_R3_DPOS1            ; /* 0xa074 */
    unsigned int           reserved_192[34]                     ; /* 0xa078~0xa0fc */
    U_V1_MRG_R0_CTRL       V1_MRG_R0_CTRL                    ; /* 0xa100 */
    U_V1_MRG_R0_DISP_POS   V1_MRG_R0_DISP_POS                ; /* 0xa104 */
    U_V1_MRG_R0_DISP_RESO   V1_MRG_R0_DISP_RESO              ; /* 0xa108 */
    U_V1_MRG_R0_SRC_RESO   V1_MRG_R0_SRC_RESO                ; /* 0xa10c */
    U_V1_MRG_R0_SRC_OFFSET   V1_MRG_R0_SRC_OFFSET            ; /* 0xa110 */
    U_V1_MRG_R0_Y_ADDR     V1_MRG_R0_Y_ADDR                  ; /* 0xa114 */
    U_V1_MRG_R0_C_ADDR     V1_MRG_R0_C_ADDR                  ; /* 0xa118 */
    U_V1_MRG_R0_STRIDE     V1_MRG_R0_STRIDE                  ; /* 0xa11c */
    U_V1_MRG_R0_YH_ADDR    V1_MRG_R0_YH_ADDR                 ; /* 0xa120 */
    U_V1_MRG_R0_CH_ADDR    V1_MRG_R0_CH_ADDR                 ; /* 0xa124 */
    U_V1_MRG_R0_HSTRIDE    V1_MRG_R0_HSTRIDE                 ; /* 0xa128 */
    unsigned int           reserved_193                     ; /* 0xa12c */
    U_V1_MRG_R1_CTRL       V1_MRG_R1_CTRL                    ; /* 0xa130 */
    U_V1_MRG_R1_DISP_POS   V1_MRG_R1_DISP_POS                ; /* 0xa134 */
    U_V1_MRG_R1_DISP_RESO   V1_MRG_R1_DISP_RESO              ; /* 0xa138 */
    U_V1_MRG_R1_SRC_RESO   V1_MRG_R1_SRC_RESO                ; /* 0xa13c */
    U_V1_MRG_R1_SRC_OFFSET   V1_MRG_R1_SRC_OFFSET            ; /* 0xa140 */
    U_V1_MRG_R1_Y_ADDR     V1_MRG_R1_Y_ADDR                  ; /* 0xa144 */
    U_V1_MRG_R1_C_ADDR     V1_MRG_R1_C_ADDR                  ; /* 0xa148 */
    U_V1_MRG_R1_STRIDE     V1_MRG_R1_STRIDE                  ; /* 0xa14c */
    U_V1_MRG_R1_YH_ADDR    V1_MRG_R1_YH_ADDR                 ; /* 0xa150 */
    U_V1_MRG_R1_CH_ADDR    V1_MRG_R1_CH_ADDR                 ; /* 0xa154 */
    U_V1_MRG_R1_HSTRIDE    V1_MRG_R1_HSTRIDE                 ; /* 0xa158 */
    unsigned int           reserved_194                     ; /* 0xa15c */
    U_V1_MRG_R2_CTRL       V1_MRG_R2_CTRL                    ; /* 0xa160 */
    U_V1_MRG_R2_DISP_POS   V1_MRG_R2_DISP_POS                ; /* 0xa164 */
    U_V1_MRG_R2_DISP_RESO   V1_MRG_R2_DISP_RESO              ; /* 0xa168 */
    U_V1_MRG_R2_SRC_RESO   V1_MRG_R2_SRC_RESO                ; /* 0xa16c */
    U_V1_MRG_R2_SRC_OFFSET   V1_MRG_R2_SRC_OFFSET            ; /* 0xa170 */
    U_V1_MRG_R2_Y_ADDR     V1_MRG_R2_Y_ADDR                  ; /* 0xa174 */
    U_V1_MRG_R2_C_ADDR     V1_MRG_R2_C_ADDR                  ; /* 0xa178 */
    U_V1_MRG_R2_STRIDE     V1_MRG_R2_STRIDE                  ; /* 0xa17c */
    U_V1_MRG_R2_YH_ADDR    V1_MRG_R2_YH_ADDR                 ; /* 0xa180 */
    U_V1_MRG_R2_CH_ADDR    V1_MRG_R2_CH_ADDR                 ; /* 0xa184 */
    U_V1_MRG_R2_HSTRIDE    V1_MRG_R2_HSTRIDE                 ; /* 0xa188 */
    unsigned int           reserved_195                     ; /* 0xa18c */
    U_V1_MRG_R3_CTRL       V1_MRG_R3_CTRL                    ; /* 0xa190 */
    U_V1_MRG_R3_DISP_POS   V1_MRG_R3_DISP_POS                ; /* 0xa194 */
    U_V1_MRG_R3_DISP_RESO   V1_MRG_R3_DISP_RESO              ; /* 0xa198 */
    U_V1_MRG_R3_SRC_RESO   V1_MRG_R3_SRC_RESO                ; /* 0xa19c */
    U_V1_MRG_R3_SRC_OFFSET   V1_MRG_R3_SRC_OFFSET            ; /* 0xa1a0 */
    U_V1_MRG_R3_Y_ADDR     V1_MRG_R3_Y_ADDR                  ; /* 0xa1a4 */
    U_V1_MRG_R3_C_ADDR     V1_MRG_R3_C_ADDR                  ; /* 0xa1a8 */
    U_V1_MRG_R3_STRIDE     V1_MRG_R3_STRIDE                  ; /* 0xa1ac */
    U_V1_MRG_R3_YH_ADDR    V1_MRG_R3_YH_ADDR                 ; /* 0xa1b0 */
    U_V1_MRG_R3_CH_ADDR    V1_MRG_R3_CH_ADDR                 ; /* 0xa1b4 */
    U_V1_MRG_R3_HSTRIDE    V1_MRG_R3_HSTRIDE                 ; /* 0xa1b8 */
    unsigned int           reserved_196[81]                     ; /* 0xa1bc~0xa2fc */
    U_MSREQ_CTRL           MSREQ_CTRL                        ; /* 0xa300 */
    U_MSREQ_RUPD           MSREQ_RUPD                        ; /* 0xa304 */
    unsigned int           reserved_197[3]                     ; /* 0xa308~0xa310 */
    U_MSREQ_ADDR           MSREQ_ADDR                        ; /* 0xa314 */
    U_MSREQ_BURST          MSREQ_BURST                       ; /* 0xa318 */
    unsigned int           reserved_198                     ; /* 0xa31c */
    U_MSREQ_DEBUG0         MSREQ_DEBUG0                      ; /* 0xa320 */
    U_MSREQ_DEBUG1         MSREQ_DEBUG1                      ; /* 0xa324 */
    U_MSREQ_DEBUG2         MSREQ_DEBUG2                      ; /* 0xa328 */
    unsigned int           reserved_199[821]                     ; /* 0xa32c~0xaffc */
    U_HIHDR_V_YUV2RGB_CTRL   HIHDR_V_YUV2RGB_CTRL            ; /* 0xb000 */
    U_HIHDR_V_YUV2RGB_COEF00   HIHDR_V_YUV2RGB_COEF00        ; /* 0xb004 */
    U_HIHDR_V_YUV2RGB_COEF01   HIHDR_V_YUV2RGB_COEF01        ; /* 0xb008 */
    U_HIHDR_V_YUV2RGB_COEF02   HIHDR_V_YUV2RGB_COEF02        ; /* 0xb00c */
    U_HIHDR_V_YUV2RGB_COEF03   HIHDR_V_YUV2RGB_COEF03        ; /* 0xb010 */
    U_HIHDR_V_YUV2RGB_COEF04   HIHDR_V_YUV2RGB_COEF04        ; /* 0xb014 */
    U_HIHDR_V_YUV2RGB_COEF05   HIHDR_V_YUV2RGB_COEF05        ; /* 0xb018 */
    U_HIHDR_V_YUV2RGB_COEF06   HIHDR_V_YUV2RGB_COEF06        ; /* 0xb01c */
    U_HIHDR_V_YUV2RGB_COEF07   HIHDR_V_YUV2RGB_COEF07        ; /* 0xb020 */
    U_HIHDR_V_YUV2RGB_COEF08   HIHDR_V_YUV2RGB_COEF08        ; /* 0xb024 */
    U_HIHDR_V_YUV2RGB_COEF10   HIHDR_V_YUV2RGB_COEF10        ; /* 0xb028 */
    U_HIHDR_V_YUV2RGB_COEF11   HIHDR_V_YUV2RGB_COEF11        ; /* 0xb02c */
    U_HIHDR_V_YUV2RGB_COEF12   HIHDR_V_YUV2RGB_COEF12        ; /* 0xb030 */
    U_HIHDR_V_YUV2RGB_COEF13   HIHDR_V_YUV2RGB_COEF13        ; /* 0xb034 */
    U_HIHDR_V_YUV2RGB_COEF14   HIHDR_V_YUV2RGB_COEF14        ; /* 0xb038 */
    U_HIHDR_V_YUV2RGB_COEF15   HIHDR_V_YUV2RGB_COEF15        ; /* 0xb03c */
    U_HIHDR_V_YUV2RGB_COEF16   HIHDR_V_YUV2RGB_COEF16        ; /* 0xb040 */
    U_HIHDR_V_YUV2RGB_COEF17   HIHDR_V_YUV2RGB_COEF17        ; /* 0xb044 */
    U_HIHDR_V_YUV2RGB_COEF18   HIHDR_V_YUV2RGB_COEF18        ; /* 0xb048 */
    U_HIHDR_V_YUV2RGB_SCALE2P   HIHDR_V_YUV2RGB_SCALE2P      ; /* 0xb04c */
    U_HIHDR_V_YUV2RGB_IN_DC00   HIHDR_V_YUV2RGB_IN_DC00      ; /* 0xb050 */
    U_HIHDR_V_YUV2RGB_IN_DC01   HIHDR_V_YUV2RGB_IN_DC01      ; /* 0xb054 */
    U_HIHDR_V_YUV2RGB_IN_DC02   HIHDR_V_YUV2RGB_IN_DC02      ; /* 0xb058 */
    U_HIHDR_V_YUV2RGB_OUT_DC00   HIHDR_V_YUV2RGB_OUT_DC00    ; /* 0xb05c */
    U_HIHDR_V_YUV2RGB_OUT_DC01   HIHDR_V_YUV2RGB_OUT_DC01    ; /* 0xb060 */
    U_HIHDR_V_YUV2RGB_OUT_DC02   HIHDR_V_YUV2RGB_OUT_DC02    ; /* 0xb064 */
    U_HIHDR_V_YUV2RGB_IN_DC10   HIHDR_V_YUV2RGB_IN_DC10      ; /* 0xb068 */
    U_HIHDR_V_YUV2RGB_IN_DC11   HIHDR_V_YUV2RGB_IN_DC11      ; /* 0xb06c */
    U_HIHDR_V_YUV2RGB_IN_DC12   HIHDR_V_YUV2RGB_IN_DC12      ; /* 0xb070 */
    U_HIHDR_V_YUV2RGB_OUT_DC10   HIHDR_V_YUV2RGB_OUT_DC10    ; /* 0xb074 */
    U_HIHDR_V_YUV2RGB_OUT_DC11   HIHDR_V_YUV2RGB_OUT_DC11    ; /* 0xb078 */
    U_HIHDR_V_YUV2RGB_OUT_DC12   HIHDR_V_YUV2RGB_OUT_DC12    ; /* 0xb07c */
    U_HIHDR_V_YUV2RGB_MIN   HIHDR_V_YUV2RGB_MIN              ; /* 0xb080 */
    U_HIHDR_V_YUV2RGB_MAX   HIHDR_V_YUV2RGB_MAX              ; /* 0xb084 */
    unsigned int           reserved_200[30]                     ; /* 0xb088~0xb0fc */
    U_VHDR_CTRL            VHDR_CTRL                         ; /* 0xb100 */
    unsigned int           reserved_201[63]                     ; /* 0xb104~0xb1fc */
    U_VHDR_DEGAMMA_CTRL    VHDR_DEGAMMA_CTRL                 ; /* 0xb200 */
    U_VHDR_DEGAMMA_REN     VHDR_DEGAMMA_REN                  ; /* 0xb204 */
    U_VHDR_DEGAMMA_DATA    VHDR_DEGAMMA_DATA                 ; /* 0xb208 */
    U_VHDR_DEGAMMA_STEP1   VHDR_DEGAMMA_STEP1                ; /* 0xb20c */
    U_VHDR_DEGAMMA_STEP2   VHDR_DEGAMMA_STEP2                ; /* 0xb210 */
    U_VHDR_DEGAMMA_POS1    VHDR_DEGAMMA_POS1                 ; /* 0xb214 */
    U_VHDR_DEGAMMA_POS2    VHDR_DEGAMMA_POS2                 ; /* 0xb218 */
    U_VHDR_DEGAMMA_POS3    VHDR_DEGAMMA_POS3                 ; /* 0xb21c */
    U_VHDR_DEGAMMA_POS4    VHDR_DEGAMMA_POS4                 ; /* 0xb220 */
    U_VHDR_DEGAMMA_NUM1    VHDR_DEGAMMA_NUM1                 ; /* 0xb224 */
    U_VHDR_DEGAMMA_NUM2    VHDR_DEGAMMA_NUM2                 ; /* 0xb228 */
    unsigned int           reserved_202[53]                     ; /* 0xb22c~0xb2fc */
    U_VHDR_GAMUT_CTRL      VHDR_GAMUT_CTRL                   ; /* 0xb300 */
    U_VHDR_GAMUT_COEF00    VHDR_GAMUT_COEF00                 ; /* 0xb304 */
    U_VHDR_GAMUT_COEF01    VHDR_GAMUT_COEF01                 ; /* 0xb308 */
    U_VHDR_GAMUT_COEF02    VHDR_GAMUT_COEF02                 ; /* 0xb30c */
    U_VHDR_GAMUT_COEF10    VHDR_GAMUT_COEF10                 ; /* 0xb310 */
    U_VHDR_GAMUT_COEF11    VHDR_GAMUT_COEF11                 ; /* 0xb314 */
    U_VHDR_GAMUT_COEF12    VHDR_GAMUT_COEF12                 ; /* 0xb318 */
    U_VHDR_GAMUT_COEF20    VHDR_GAMUT_COEF20                 ; /* 0xb31c */
    U_VHDR_GAMUT_COEF21    VHDR_GAMUT_COEF21                 ; /* 0xb320 */
    U_VHDR_GAMUT_COEF22    VHDR_GAMUT_COEF22                 ; /* 0xb324 */
    U_VHDR_GAMUT_SCALE     VHDR_GAMUT_SCALE                  ; /* 0xb328 */
    U_VHDR_GAMUT_IDC0      VHDR_GAMUT_IDC0                   ; /* 0xb32c */
    U_VHDR_GAMUT_IDC1      VHDR_GAMUT_IDC1                   ; /* 0xb330 */
    U_VHDR_GAMUT_IDC2      VHDR_GAMUT_IDC2                   ; /* 0xb334 */
    U_VHDR_GAMUT_ODC0      VHDR_GAMUT_ODC0                   ; /* 0xb338 */
    U_VHDR_GAMUT_ODC1      VHDR_GAMUT_ODC1                   ; /* 0xb33c */
    U_VHDR_GAMUT_ODC2      VHDR_GAMUT_ODC2                   ; /* 0xb340 */
    U_VHDR_GAMUT_CLIP_MIN   VHDR_GAMUT_CLIP_MIN              ; /* 0xb344 */
    U_VHDR_GAMUT_CLIP_MAX   VHDR_GAMUT_CLIP_MAX              ; /* 0xb348 */
    unsigned int           reserved_203[45]                     ; /* 0xb34c~0xb3fc */
    U_VHDR_TONEMAP_CTRL    VHDR_TONEMAP_CTRL                 ; /* 0xb400 */
    U_VHDR_TONEMAP_REN     VHDR_TONEMAP_REN                  ; /* 0xb404 */
    U_VHDR_TONEMAP_DATA    VHDR_TONEMAP_DATA                 ; /* 0xb408 */
    U_VHDR_TONEMAP_SM_DATA   VHDR_TONEMAP_SM_DATA            ; /* 0xb40c */
    U_VHDR_TONEMAP_STEP1   VHDR_TONEMAP_STEP1                ; /* 0xb410 */
    U_VHDR_TONEMAP_STEP2   VHDR_TONEMAP_STEP2                ; /* 0xb414 */
    U_VHDR_TONEMAP_POS1    VHDR_TONEMAP_POS1                 ; /* 0xb418 */
    U_VHDR_TONEMAP_POS2    VHDR_TONEMAP_POS2                 ; /* 0xb41c */
    U_VHDR_TONEMAP_POS3    VHDR_TONEMAP_POS3                 ; /* 0xb420 */
    U_VHDR_TONEMAP_POS4    VHDR_TONEMAP_POS4                 ; /* 0xb424 */
    U_VHDR_TONEMAP_POS5    VHDR_TONEMAP_POS5                 ; /* 0xb428 */
    U_VHDR_TONEMAP_POS6    VHDR_TONEMAP_POS6                 ; /* 0xb42c */
    U_VHDR_TONEMAP_POS7    VHDR_TONEMAP_POS7                 ; /* 0xb430 */
    U_VHDR_TONEMAP_POS8    VHDR_TONEMAP_POS8                 ; /* 0xb434 */
    U_VHDR_TONEMAP_NUM1    VHDR_TONEMAP_NUM1                 ; /* 0xb438 */
    U_VHDR_TONEMAP_NUM2    VHDR_TONEMAP_NUM2                 ; /* 0xb43c */
    U_VHDR_TONEMAP_SM_STEP1   VHDR_TONEMAP_SM_STEP1          ; /* 0xb440 */
    U_VHDR_TONEMAP_SM_STEP2   VHDR_TONEMAP_SM_STEP2          ; /* 0xb444 */
    U_VHDR_TONEMAP_SM_POS1   VHDR_TONEMAP_SM_POS1            ; /* 0xb448 */
    U_VHDR_TONEMAP_SM_POS2   VHDR_TONEMAP_SM_POS2            ; /* 0xb44c */
    U_VHDR_TONEMAP_SM_POS3   VHDR_TONEMAP_SM_POS3            ; /* 0xb450 */
    U_VHDR_TONEMAP_SM_POS4   VHDR_TONEMAP_SM_POS4            ; /* 0xb454 */
    U_VHDR_TONEMAP_SM_POS5   VHDR_TONEMAP_SM_POS5            ; /* 0xb458 */
    U_VHDR_TONEMAP_SM_POS6   VHDR_TONEMAP_SM_POS6            ; /* 0xb45c */
    U_VHDR_TONEMAP_SM_POS7   VHDR_TONEMAP_SM_POS7            ; /* 0xb460 */
    U_VHDR_TONEMAP_SM_POS8   VHDR_TONEMAP_SM_POS8            ; /* 0xb464 */
    U_VHDR_TONEMAP_SM_NUM1   VHDR_TONEMAP_SM_NUM1            ; /* 0xb468 */
    U_VHDR_TONEMAP_SM_NUM2   VHDR_TONEMAP_SM_NUM2            ; /* 0xb46c */
    U_VHDR_TONEMAP_LUMA_COEF0   VHDR_TONEMAP_LUMA_COEF0      ; /* 0xb470 */
    U_VHDR_TONEMAP_LUMA_COEF1   VHDR_TONEMAP_LUMA_COEF1      ; /* 0xb474 */
    U_VHDR_TONEMAP_LUMA_COEF2   VHDR_TONEMAP_LUMA_COEF2      ; /* 0xb478 */
    U_VHDR_TONEMAP_LUMA_SCALE   VHDR_TONEMAP_LUMA_SCALE      ; /* 0xb47c */
    U_VHDR_TONEMAP_COEF_SCALE   VHDR_TONEMAP_COEF_SCALE      ; /* 0xb480 */
    U_VHDR_TONEMAP_OUT_CLIP_MIN   VHDR_TONEMAP_OUT_CLIP_MIN  ; /* 0xb484 */
    U_VHDR_TONEMAP_OUT_CLIP_MAX   VHDR_TONEMAP_OUT_CLIP_MAX  ; /* 0xb488 */
    U_VHDR_TONEMAP_OUT_DC0   VHDR_TONEMAP_OUT_DC0            ; /* 0xb48c */
    U_VHDR_TONEMAP_OUT_DC1   VHDR_TONEMAP_OUT_DC1            ; /* 0xb490 */
    U_VHDR_TONEMAP_OUT_DC2   VHDR_TONEMAP_OUT_DC2            ; /* 0xb494 */
    U_VHDR_TONEMAP_ALPHA   VHDR_TONEMAP_ALPHA                ; /* 0xb498 */
    unsigned int           reserved_204[25]                     ; /* 0xb49c~0xb4fc */
    U_VHDR_GAMMA_CTRL      VHDR_GAMMA_CTRL                   ; /* 0xb500 */
    U_VHDR_GAMMA_REN       VHDR_GAMMA_REN                    ; /* 0xb504 */
    U_VHDR_GAMMMA_DATA     VHDR_GAMMMA_DATA                  ; /* 0xb508 */
    U_VHDR_GAMMA_STEP1     VHDR_GAMMA_STEP1                  ; /* 0xb50c */
    U_VHDR_GAMMA_STEP2     VHDR_GAMMA_STEP2                  ; /* 0xb510 */
    U_VHDR_GAMMA_POS1      VHDR_GAMMA_POS1                   ; /* 0xb514 */
    U_VHDR_GAMMA_POS2      VHDR_GAMMA_POS2                   ; /* 0xb518 */
    U_VHDR_GAMMA_POS3      VHDR_GAMMA_POS3                   ; /* 0xb51c */
    U_VHDR_GAMMA_POS4      VHDR_GAMMA_POS4                   ; /* 0xb520 */
    U_VHDR_GAMMA_POS5      VHDR_GAMMA_POS5                   ; /* 0xb524 */
    U_VHDR_GAMMA_POS6      VHDR_GAMMA_POS6                   ; /* 0xb528 */
    U_VHDR_GAMMA_POS7      VHDR_GAMMA_POS7                   ; /* 0xb52c */
    U_VHDR_GAMMA_POS8      VHDR_GAMMA_POS8                   ; /* 0xb530 */
    U_VHDR_GAMMA_NUM1      VHDR_GAMMA_NUM1                   ; /* 0xb534 */
    U_VHDR_GAMMA_NUM2      VHDR_GAMMA_NUM2                   ; /* 0xb538 */
    unsigned int           reserved_205[49]                     ; /* 0xb53c~0xb5fc */
    U_VHDR_DITHER_CTRL     VHDR_DITHER_CTRL                  ; /* 0xb600 */
    U_VHDR_DITHER_THR      VHDR_DITHER_THR                   ; /* 0xb604 */
    U_VHDR_DITHER_SED_Y0   VHDR_DITHER_SED_Y0                ; /* 0xb608 */
    U_VHDR_DITHER_SED_U0   VHDR_DITHER_SED_U0                ; /* 0xb60c */
    U_VHDR_DITHER_SED_V0   VHDR_DITHER_SED_V0                ; /* 0xb610 */
    U_VHDR_DITHER_SED_W0   VHDR_DITHER_SED_W0                ; /* 0xb614 */
    U_VHDR_DITHER_SED_Y1   VHDR_DITHER_SED_Y1                ; /* 0xb618 */
    U_VHDR_DITHER_SED_U1   VHDR_DITHER_SED_U1                ; /* 0xb61c */
    U_VHDR_DITHER_SED_V1   VHDR_DITHER_SED_V1                ; /* 0xb620 */
    U_VHDR_DITHER_SED_W1   VHDR_DITHER_SED_W1                ; /* 0xb624 */
    unsigned int           reserved_206[54]                     ; /* 0xb628~0xb6fc */
    U_VHDR_RGB2YUV_CTRL    VHDR_RGB2YUV_CTRL                 ; /* 0xb700 */
    U_VHDR_RGB2YUV_COEF0   VHDR_RGB2YUV_COEF0                ; /* 0xb704 */
    U_VHDR_RGB2YUV_COEF1   VHDR_RGB2YUV_COEF1                ; /* 0xb708 */
    U_VHDR_RGB2YUV_COEF2   VHDR_RGB2YUV_COEF2                ; /* 0xb70c */
    U_VHDR_RGB2YUV_COEF3   VHDR_RGB2YUV_COEF3                ; /* 0xb710 */
    U_VHDR_RGB2YUV_COEF4   VHDR_RGB2YUV_COEF4                ; /* 0xb714 */
    U_VHDR_RGB2YUV_COEF5   VHDR_RGB2YUV_COEF5                ; /* 0xb718 */
    U_VHDR_RGB2YUV_COEF6   VHDR_RGB2YUV_COEF6                ; /* 0xb71c */
    U_VHDR_RGB2YUV_COEF7   VHDR_RGB2YUV_COEF7                ; /* 0xb720 */
    U_VHDR_RGB2YUV_COEF8   VHDR_RGB2YUV_COEF8                ; /* 0xb724 */
    U_VHDR_RGB2YUV_SCALE2P   VHDR_RGB2YUV_SCALE2P            ; /* 0xb728 */
    U_VHDR_RGB2YUV_IDC0    VHDR_RGB2YUV_IDC0                 ; /* 0xb72c */
    U_VHDR_RGB2YUV_IDC1    VHDR_RGB2YUV_IDC1                 ; /* 0xb730 */
    U_VHDR_RGB2YUV_IDC2    VHDR_RGB2YUV_IDC2                 ; /* 0xb734 */
    U_VHDR_RGB2YUV_ODC0    VHDR_RGB2YUV_ODC0                 ; /* 0xb738 */
    U_VHDR_RGB2YUV_ODC1    VHDR_RGB2YUV_ODC1                 ; /* 0xb73c */
    U_VHDR_RGB2YUV_ODC2    VHDR_RGB2YUV_ODC2                 ; /* 0xb740 */
    U_VHDR_RGB2YUV_MIN     VHDR_RGB2YUV_MIN                  ; /* 0xb744 */
    U_VHDR_RGB2YUV_MAX     VHDR_RGB2YUV_MAX                  ; /* 0xb748 */
    unsigned int           reserved_207[45]                     ; /* 0xb74c~0xb7fc */
    U_VHDACM0              VHDACM0                           ; /* 0xb800 */
    U_VHDACM1              VHDACM1                           ; /* 0xb804 */
    U_VHDACM2              VHDACM2                           ; /* 0xb808 */
    U_VHDACM3              VHDACM3                           ; /* 0xb80c */
    U_VHDACM4              VHDACM4                           ; /* 0xb810 */
    U_VHDACM5              VHDACM5                           ; /* 0xb814 */
    U_VHDACM6              VHDACM6                           ; /* 0xb818 */
    U_VHDACM7              VHDACM7                           ; /* 0xb81c */
    unsigned int           reserved_208[504]                     ; /* 0xb820~0xbffc */
    U_DHD_TOP_CTRL         DHD_TOP_CTRL                      ; /* 0xc000 */
    U_VO_MUX               VO_MUX                            ; /* 0xc004 */
    U_DHD_VO_MUX_SYNC      DHD_VO_MUX_SYNC                   ; /* 0xc008 */
    U_DHD_VO_MUX_DATA      DHD_VO_MUX_DATA                   ; /* 0xc00c */
    unsigned int           reserved_209[124]                     ; /* 0xc010~0xc1fc */
    U_DHD0_CTRL            DHD0_CTRL                         ; /* 0xc200 */
    U_DHD0_CTRL1           DHD0_CTRL1                        ; /* 0xc204 */
    U_DHD0_VSYNC           DHD0_VSYNC                        ; /* 0xc208 */
    U_DHD0_VSYNC2          DHD0_VSYNC2                       ; /* 0xc20c */
    U_DHD0_HSYNC1          DHD0_HSYNC1                       ; /* 0xc210 */
    U_DHD0_HSYNC2          DHD0_HSYNC2                       ; /* 0xc214 */
    U_DHD0_VPLUS           DHD0_VPLUS                        ; /* 0xc218 */
    U_DHD0_VPLUS2          DHD0_VPLUS2                       ; /* 0xc21c */
    U_DHD0_PWR             DHD0_PWR                          ; /* 0xc220 */
    U_DHD0_VTTHD3          DHD0_VTTHD3                       ; /* 0xc224 */
    U_DHD0_VTTHD           DHD0_VTTHD                        ; /* 0xc228 */
    U_DHD0_PARATHD         DHD0_PARATHD                      ; /* 0xc22c */
    U_DHD0_PRECHARGE_THD   DHD0_PRECHARGE_THD                ; /* 0xc230 */
    U_DHD0_START_POS       DHD0_START_POS                    ; /* 0xc234 */
    U_DHD0_START_POS1      DHD0_START_POS1                   ; /* 0xc238 */
    U_DHD0_START_POS2      DHD0_START_POS2                   ; /* 0xc23c */
    U_DHD0_BUSY_MODE       DHD0_BUSY_MODE                    ; /* 0xc240 */
    U_DHD0_BUSY_MODE_RD    DHD0_BUSY_MODE_RD                 ; /* 0xc244 */
    U_DHD0_CLK_DV_CTRL     DHD0_CLK_DV_CTRL                  ; /* 0xc248 */
    U_DHD0_RGB_FIX_CTRL    DHD0_RGB_FIX_CTRL                 ; /* 0xc24c */
    U_DHD0_LOCKCFG         DHD0_LOCKCFG                      ; /* 0xc250 */
    U_DHD0_CAP_FRM_CNT     DHD0_CAP_FRM_CNT                  ; /* 0xc254 */
    U_DHD0_VDP_FRM_CNT     DHD0_VDP_FRM_CNT                  ; /* 0xc258 */
    U_DHD0_VSYNC_CAP_VDP_CNT   DHD0_VSYNC_CAP_VDP_CNT        ; /* 0xc25c */
    U_DHD0_INTF_CHKSUM_Y   DHD0_INTF_CHKSUM_Y                ; /* 0xc260 */
    U_DHD0_INTF_CHKSUM_U   DHD0_INTF_CHKSUM_U                ; /* 0xc264 */
    U_DHD0_INTF_CHKSUM_V   DHD0_INTF_CHKSUM_V                ; /* 0xc268 */
    U_DHD0_INTF1_CHKSUM_Y   DHD0_INTF1_CHKSUM_Y              ; /* 0xc26c */
    U_DHD0_INTF1_CHKSUM_U   DHD0_INTF1_CHKSUM_U              ; /* 0xc270 */
    U_DHD0_INTF1_CHKSUM_V   DHD0_INTF1_CHKSUM_V              ; /* 0xc274 */
    U_DHD0_INTF_CHKSUM_HIGH1   DHD0_INTF_CHKSUM_HIGH1        ; /* 0xc278 */
    U_DHD0_INTF_CHKSUM_HIGH2   DHD0_INTF_CHKSUM_HIGH2        ; /* 0xc27c */
    U_DHD0_INTF2_CHKSUM_Y   DHD0_INTF2_CHKSUM_Y              ; /* 0xc280 */
    U_DHD0_INTF2_CHKSUM_U   DHD0_INTF2_CHKSUM_U              ; /* 0xc284 */
    U_DHD0_INTF2_CHKSUM_V   DHD0_INTF2_CHKSUM_V              ; /* 0xc288 */
    U_DHD0_INTF3_CHKSUM_Y   DHD0_INTF3_CHKSUM_Y              ; /* 0xc28c */
    U_DHD0_INTF3_CHKSUM_U   DHD0_INTF3_CHKSUM_U              ; /* 0xc290 */
    U_DHD0_INTF3_CHKSUM_V   DHD0_INTF3_CHKSUM_V              ; /* 0xc294 */
    U_DHD0_INTF_CHKSUM_HIGH3   DHD0_INTF_CHKSUM_HIGH3        ; /* 0xc298 */
    U_DHD0_INTF_CHKSUM_HIGH4   DHD0_INTF_CHKSUM_HIGH4        ; /* 0xc29c */
    U_DHD0_STATE           DHD0_STATE                        ; /* 0xc2a0 */
    U_DHD0_UF_STATE        DHD0_UF_STATE                     ; /* 0xc2a4 */
    unsigned int           reserved_210[3]                     ; /* 0xc2a8~0xc2b0 */
    U_DHD0_VBI             DHD0_VBI                          ; /* 0xc2b4 */
    U_DHD0_ONLINE_CFG1     DHD0_ONLINE_CFG1                  ; /* 0xc2b8 */
    U_DHD0_PRECHARGE_THD1   DHD0_PRECHARGE_THD1              ; /* 0xc2bc */
    U_DHD0_LLRR_CTRL       DHD0_LLRR_CTRL                    ; /* 0xc2c0 */
    U_DHD0_SCAN_BL         DHD0_SCAN_BL                      ; /* 0xc2c4 */
    U_DHD0_MULTICHIP_CFG1   DHD0_MULTICHIP_CFG1              ; /* 0xc2c8 */
    unsigned int           reserved_211[2]                     ; /* 0xc2cc~0xc2d0 */
    U_DHD0_PAUSE           DHD0_PAUSE                        ; /* 0xc2d4 */
    U_DHD0_PRE_UF_THD      DHD0_PRE_UF_THD                   ; /* 0xc2d8 */
    unsigned int           reserved_212                     ; /* 0xc2dc */
    U_DHD0_VDAC_DET0       DHD0_VDAC_DET0                    ; /* 0xc2e0 */
    U_DHD0_VDAC_DET1       DHD0_VDAC_DET1                    ; /* 0xc2e4 */
    U_DHD0_VTTHD5          DHD0_VTTHD5                       ; /* 0xc2e8 */
    unsigned int           reserved_213[197]                     ; /* 0xc2ec~0xc5fc */
    U_INTF_HDMI_CTRL       INTF_HDMI_CTRL                    ; /* 0xc600 */
    U_INTF_HDMI_SYNC_INV   INTF_HDMI_SYNC_INV                ; /* 0xc604 */
    U_INTF_HDMI_CLIP_L     INTF_HDMI_CLIP_L                  ; /* 0xc608 */
    U_INTF_HDMI_CLIP_H     INTF_HDMI_CLIP_H                  ; /* 0xc60c */
    U_INTF_HDMI_CHKSUM_Y   INTF_HDMI_CHKSUM_Y                ; /* 0xc610 */
    U_INTF_HDMI_CHKSUM_U   INTF_HDMI_CHKSUM_U                ; /* 0xc614 */
    U_INTF_HDMI_CHKSUM_V   INTF_HDMI_CHKSUM_V                ; /* 0xc618 */
    U_INTF_HDMI_CHKSUM_HIGH1   INTF_HDMI_CHKSUM_HIGH1        ; /* 0xc61c */
    unsigned int           reserved_214[248]                     ; /* 0xc620~0xc9fc */
    U_INTF_DATE_CTRL       INTF_DATE_CTRL                    ; /* 0xca00 */
    U_INTF_DATE_UPD        INTF_DATE_UPD                     ; /* 0xca04 */
    U_INTF_DATE_SYNC_INV   INTF_DATE_SYNC_INV                ; /* 0xca08 */
    unsigned int           reserved_215                     ; /* 0xca0c */
    U_DATE_CLIP0_L         DATE_CLIP0_L                      ; /* 0xca10 */
    U_DATE_CLIP0_H         DATE_CLIP0_H                      ; /* 0xca14 */
    unsigned int           reserved_216[54]                     ; /* 0xca18~0xcaec */
    U_DATE_INTF_CHKSUM_Y   DATE_INTF_CHKSUM_Y                ; /* 0xcaf0 */
    U_DATE_INTF_CHKSUM_U   DATE_INTF_CHKSUM_U                ; /* 0xcaf4 */
    U_DATE_INTF_CHKSUM_V   DATE_INTF_CHKSUM_V                ; /* 0xcaf8 */
    unsigned int           reserved_217[193]                     ; /* 0xcafc~0xcdfc */
    U_DATE_COEFF0          DATE_COEFF0                       ; /* 0xce00 */
    U_DATE_COEFF1          DATE_COEFF1                       ; /* 0xce04 */
    U_DATE_COEFF2          DATE_COEFF2                       ; /* 0xce08 */
    U_DATE_COEFF3          DATE_COEFF3                       ; /* 0xce0c */
    U_DATE_COEFF4          DATE_COEFF4                       ; /* 0xce10 */
    U_DATE_COEFF5          DATE_COEFF5                       ; /* 0xce14 */
    U_DATE_COEFF6          DATE_COEFF6                       ; /* 0xce18 */
    U_DATE_COEFF7          DATE_COEFF7                       ; /* 0xce1c */
    U_DATE_COEFF8          DATE_COEFF8                       ; /* 0xce20 */
    U_DATE_COEFF9          DATE_COEFF9                       ; /* 0xce24 */
    U_DATE_COEFF10         DATE_COEFF10                      ; /* 0xce28 */
    U_DATE_COEFF11         DATE_COEFF11                      ; /* 0xce2c */
    U_DATE_COEFF12         DATE_COEFF12                      ; /* 0xce30 */
    U_DATE_COEFF13         DATE_COEFF13                      ; /* 0xce34 */
    U_DATE_COEFF14         DATE_COEFF14                      ; /* 0xce38 */
    U_DATE_COEFF15         DATE_COEFF15                      ; /* 0xce3c */
    U_DATE_COEFF16         DATE_COEFF16                      ; /* 0xce40 */
    U_DATE_COEFF17         DATE_COEFF17                      ; /* 0xce44 */
    U_DATE_COEFF18         DATE_COEFF18                      ; /* 0xce48 */
    U_DATE_COEFF19         DATE_COEFF19                      ; /* 0xce4c */
    U_DATE_COEFF20         DATE_COEFF20                      ; /* 0xce50 */
    U_DATE_COEFF21         DATE_COEFF21                      ; /* 0xce54 */
    U_DATE_COEFF22         DATE_COEFF22                      ; /* 0xce58 */
    U_DATE_COEFF23         DATE_COEFF23                      ; /* 0xce5c */
    U_DATE_COEFF24         DATE_COEFF24                      ; /* 0xce60 */
    U_DATE_COEFF25         DATE_COEFF25                      ; /* 0xce64 */
    U_DATE_COEFF26         DATE_COEFF26                      ; /* 0xce68 */
    U_DATE_COEFF27         DATE_COEFF27                      ; /* 0xce6c */
    U_DATE_COEFF28         DATE_COEFF28                      ; /* 0xce70 */
    U_DATE_COEFF29         DATE_COEFF29                      ; /* 0xce74 */
    U_DATE_COEFF30         DATE_COEFF30                      ; /* 0xce78 */
    unsigned int           reserved_218                     ; /* 0xce7c */
    U_DATE_ISRMASK         DATE_ISRMASK                      ; /* 0xce80 */
    U_DATE_ISRSTATE        DATE_ISRSTATE                     ; /* 0xce84 */
    U_DATE_ISR             DATE_ISR                          ; /* 0xce88 */
    unsigned int           reserved_219                     ; /* 0xce8c */
    U_DATE_VERSION         DATE_VERSION                      ; /* 0xce90 */
    U_DATE_COEFF37         DATE_COEFF37                      ; /* 0xce94 */
    U_DATE_COEFF38         DATE_COEFF38                      ; /* 0xce98 */
    U_DATE_COEFF39         DATE_COEFF39                      ; /* 0xce9c */
    U_DATE_COEFF40         DATE_COEFF40                      ; /* 0xcea0 */
    U_DATE_COEFF41         DATE_COEFF41                      ; /* 0xcea4 */
    U_DATE_COEFF42         DATE_COEFF42                      ; /* 0xcea8 */
    unsigned int           reserved_220[5]                     ; /* 0xceac~0xcebc */
    U_DATE_DACDET1         DATE_DACDET1                      ; /* 0xcec0 */
    U_DATE_DACDET2         DATE_DACDET2                      ; /* 0xcec4 */
    U_DATE_COEFF50         DATE_COEFF50                      ; /* 0xcec8 */
    U_DATE_COEFF51         DATE_COEFF51                      ; /* 0xcecc */
    U_DATE_COEFF52         DATE_COEFF52                      ; /* 0xced0 */
    U_DATE_COEFF53         DATE_COEFF53                      ; /* 0xced4 */
    U_DATE_COEFF54         DATE_COEFF54                      ; /* 0xced8 */
    U_DATE_COEFF55         DATE_COEFF55                      ; /* 0xcedc */
    unsigned int           reserved_221[72]                     ; /* 0xcee0~0xcffc */
    U_GHDR_CTRL            GHDR_CTRL                         ; /* 0xd000 */
    unsigned int           reserved_222[63]                     ; /* 0xd004~0xd0fc */
    U_GHDR_GAMUT_CTRL      GHDR_GAMUT_CTRL                   ; /* 0xd100 */
    U_GHDR_GAMUT_COEF00    GHDR_GAMUT_COEF00                 ; /* 0xd104 */
    U_GHDR_GAMUT_COEF01    GHDR_GAMUT_COEF01                 ; /* 0xd108 */
    U_GHDR_GAMUT_COEF02    GHDR_GAMUT_COEF02                 ; /* 0xd10c */
    U_GHDR_GAMUT_COEF10    GHDR_GAMUT_COEF10                 ; /* 0xd110 */
    U_GHDR_GAMUT_COEF11    GHDR_GAMUT_COEF11                 ; /* 0xd114 */
    U_GHDR_GAMUT_COEF12    GHDR_GAMUT_COEF12                 ; /* 0xd118 */
    U_GHDR_GAMUT_COEF20    GHDR_GAMUT_COEF20                 ; /* 0xd11c */
    U_GHDR_GAMUT_COEF21    GHDR_GAMUT_COEF21                 ; /* 0xd120 */
    U_GHDR_GAMUT_COEF22    GHDR_GAMUT_COEF22                 ; /* 0xd124 */
    U_GHDR_GAMUT_SCALE     GHDR_GAMUT_SCALE                  ; /* 0xd128 */
    U_GHDR_GAMUT_CLIP_MIN   GHDR_GAMUT_CLIP_MIN              ; /* 0xd12c */
    U_GHDR_GAMUT_CLIP_MAX   GHDR_GAMUT_CLIP_MAX              ; /* 0xd130 */
    unsigned int           reserved_223[51]                     ; /* 0xd134~0xd1fc */
    U_GHDR_TONEMAP_CTRL    GHDR_TONEMAP_CTRL                 ; /* 0xd200 */
    U_GHDR_TONEMAP_REN     GHDR_TONEMAP_REN                  ; /* 0xd204 */
    U_GHDR_TONEMAP_DATA    GHDR_TONEMAP_DATA                 ; /* 0xd208 */
    U_GHDR_TONEMAP_STEP    GHDR_TONEMAP_STEP                 ; /* 0xd20c */
    U_GHDR_TONEMAP_POS1    GHDR_TONEMAP_POS1                 ; /* 0xd210 */
    U_GHDR_TONEMAP_POS2    GHDR_TONEMAP_POS2                 ; /* 0xd214 */
    U_GHDR_TONEMAP_POS3    GHDR_TONEMAP_POS3                 ; /* 0xd218 */
    U_GHDR_TONEMAP_POS4    GHDR_TONEMAP_POS4                 ; /* 0xd21c */
    U_GHDR_TONEMAP_NUM     GHDR_TONEMAP_NUM                  ; /* 0xd220 */
    U_GHDR_TONEMAP_LUMA_COEF0   GHDR_TONEMAP_LUMA_COEF0      ; /* 0xd224 */
    U_GHDR_TONEMAP_LUMA_COEF1   GHDR_TONEMAP_LUMA_COEF1      ; /* 0xd228 */
    U_GHDR_TONEMAP_LUMA_COEF2   GHDR_TONEMAP_LUMA_COEF2      ; /* 0xd22c */
    U_GHDR_TONEMAP_LUMA_SCALE   GHDR_TONEMAP_LUMA_SCALE      ; /* 0xd230 */
    U_GHDR_TONEMAP_COEF_SCALE   GHDR_TONEMAP_COEF_SCALE      ; /* 0xd234 */
    U_GHDR_TONEMAP_OUT_CLIP_MIN   GHDR_TONEMAP_OUT_CLIP_MIN  ; /* 0xd238 */
    U_GHDR_TONEMAP_OUT_CLIP_MAX   GHDR_TONEMAP_OUT_CLIP_MAX  ; /* 0xd23c */
    unsigned int           reserved_224[48]                     ; /* 0xd240~0xd2fc */
    U_GHDR_GAMMA_CTRL      GHDR_GAMMA_CTRL                   ; /* 0xd300 */
    U_GHDR_GAMMA_REN       GHDR_GAMMA_REN                    ; /* 0xd304 */
    U_GHDR_GAMMMA_DATA     GHDR_GAMMMA_DATA                  ; /* 0xd308 */
    U_GHDR_GAMMA_STEP1     GHDR_GAMMA_STEP1                  ; /* 0xd30c */
    U_GHDR_GAMMA_STEP2     GHDR_GAMMA_STEP2                  ; /* 0xd310 */
    U_GHDR_GAMMA_POS1      GHDR_GAMMA_POS1                   ; /* 0xd314 */
    U_GHDR_GAMMA_POS2      GHDR_GAMMA_POS2                   ; /* 0xd318 */
    U_GHDR_GAMMA_POS3      GHDR_GAMMA_POS3                   ; /* 0xd31c */
    U_GHDR_GAMMA_POS4      GHDR_GAMMA_POS4                   ; /* 0xd320 */
    U_GHDR_GAMMA_NUM1      GHDR_GAMMA_NUM1                   ; /* 0xd324 */
    U_GHDR_GAMMA_NUM2      GHDR_GAMMA_NUM2                   ; /* 0xd328 */
    unsigned int           reserved_225[53]                     ; /* 0xd32c~0xd3fc */
    U_GHDR_DITHER_CTRL     GHDR_DITHER_CTRL                  ; /* 0xd400 */
    U_GHDR_DITHER_THR      GHDR_DITHER_THR                   ; /* 0xd404 */
    U_GHDR_DITHER_SED_Y0   GHDR_DITHER_SED_Y0                ; /* 0xd408 */
    U_GHDR_DITHER_SED_U0   GHDR_DITHER_SED_U0                ; /* 0xd40c */
    U_GHDR_DITHER_SED_V0   GHDR_DITHER_SED_V0                ; /* 0xd410 */
    U_GHDR_DITHER_SED_W0   GHDR_DITHER_SED_W0                ; /* 0xd414 */
    U_GHDR_DITHER_SED_Y1   GHDR_DITHER_SED_Y1                ; /* 0xd418 */
    U_GHDR_DITHER_SED_U1   GHDR_DITHER_SED_U1                ; /* 0xd41c */
    U_GHDR_DITHER_SED_V1   GHDR_DITHER_SED_V1                ; /* 0xd420 */
    U_GHDR_DITHER_SED_W1   GHDR_DITHER_SED_W1                ; /* 0xd424 */
    unsigned int           reserved_226[54]                     ; /* 0xd428~0xd4fc */
    U_HIHDR_G_RGB2YUV_CTRL   HIHDR_G_RGB2YUV_CTRL            ; /* 0xd500 */
    U_HIHDR_G_RGB2YUV_COEF0   HIHDR_G_RGB2YUV_COEF0          ; /* 0xd504 */
    U_HIHDR_G_RGB2YUV_COEF1   HIHDR_G_RGB2YUV_COEF1          ; /* 0xd508 */
    U_HIHDR_G_RGB2YUV_COEF2   HIHDR_G_RGB2YUV_COEF2          ; /* 0xd50c */
    U_HIHDR_G_RGB2YUV_COEF3   HIHDR_G_RGB2YUV_COEF3          ; /* 0xd510 */
    U_HIHDR_G_RGB2YUV_COEF4   HIHDR_G_RGB2YUV_COEF4          ; /* 0xd514 */
    U_HIHDR_G_RGB2YUV_COEF5   HIHDR_G_RGB2YUV_COEF5          ; /* 0xd518 */
    U_HIHDR_G_RGB2YUV_COEF6   HIHDR_G_RGB2YUV_COEF6          ; /* 0xd51c */
    U_HIHDR_G_RGB2YUV_COEF7   HIHDR_G_RGB2YUV_COEF7          ; /* 0xd520 */
    U_HIHDR_G_RGB2YUV_COEF8   HIHDR_G_RGB2YUV_COEF8          ; /* 0xd524 */
    U_HIHDR_G_RGB2YUV_SCALE2P   HIHDR_G_RGB2YUV_SCALE2P      ; /* 0xd528 */
    U_HIHDR_G_RGB2YUV_IDC0   HIHDR_G_RGB2YUV_IDC0            ; /* 0xd52c */
    U_HIHDR_G_RGB2YUV_IDC1   HIHDR_G_RGB2YUV_IDC1            ; /* 0xd530 */
    U_HIHDR_G_RGB2YUV_IDC2   HIHDR_G_RGB2YUV_IDC2            ; /* 0xd534 */
    U_HIHDR_G_RGB2YUV_ODC0   HIHDR_G_RGB2YUV_ODC0            ; /* 0xd538 */
    U_HIHDR_G_RGB2YUV_ODC1   HIHDR_G_RGB2YUV_ODC1            ; /* 0xd53c */
    U_HIHDR_G_RGB2YUV_ODC2   HIHDR_G_RGB2YUV_ODC2            ; /* 0xd540 */
    U_HIHDR_G_RGB2YUV_MIN   HIHDR_G_RGB2YUV_MIN              ; /* 0xd544 */
    U_HIHDR_G_RGB2YUV_MAX   HIHDR_G_RGB2YUV_MAX              ; /* 0xd548 */
    unsigned int           reserved_227[685]                     ; /* 0xd54c~0xdffc */
    U_SMMU_SCR             SMMU_SCR                          ; /* 0xe000 */
    unsigned int           reserved_228                     ; /* 0xe004 */
    U_SMMU_LP_CTRL         SMMU_LP_CTRL                      ; /* 0xe008 */
    U_SMMU_MEM_SPEEDCTRL   SMMU_MEM_SPEEDCTRL                ; /* 0xe00c */
    U_SMMU_INTMASK_S       SMMU_INTMASK_S                    ; /* 0xe010 */
    U_SMMU_INTRAW_S        SMMU_INTRAW_S                     ; /* 0xe014 */
    U_SMMU_INTSTAT_S       SMMU_INTSTAT_S                    ; /* 0xe018 */
    U_SMMU_INTCLR_S        SMMU_INTCLR_S                     ; /* 0xe01c */
    U_SMMU_INTMASK_NS      SMMU_INTMASK_NS                   ; /* 0xe020 */
    U_SMMU_INTRAW_NS       SMMU_INTRAW_NS                    ; /* 0xe024 */
    U_SMMU_INTSTAT_NS      SMMU_INTSTAT_NS                   ; /* 0xe028 */
    U_SMMU_INTCLR_NS       SMMU_INTCLR_NS                    ; /* 0xe02c */
    unsigned int           reserved_229[118]                     ; /* 0xe030~0xe204 */
    U_SMMU_SCB_TTBR        SMMU_SCB_TTBR                     ; /* 0xe208 */
    U_SMMU_CB_TTBR         SMMU_CB_TTBR                      ; /* 0xe20c */
    unsigned int           reserved_230[56]                     ; /* 0xe210~0xe2ec */
    U_SMMU_ERR_RDADDR_S    SMMU_ERR_RDADDR_S                 ; /* 0xe2f0 */
    U_SMMU_ERR_WRADDR_S    SMMU_ERR_WRADDR_S                 ; /* 0xe2f4 */
    unsigned int           reserved_231[3]                     ; /* 0xe2f8~0xe300 */
    U_SMMU_ERR_RDADDR_NS   SMMU_ERR_RDADDR_NS                ; /* 0xe304 */
    U_SMMU_ERR_WRADDR_NS   SMMU_ERR_WRADDR_NS                ; /* 0xe308 */
    unsigned int           reserved_232                     ; /* 0xe30c */
    U_SMMU_FAULT_ADDR_PTW_S   SMMU_FAULT_ADDR_PTW_S          ; /* 0xe310 */
    U_SMMU_FAULT_ID_PTW_S   SMMU_FAULT_ID_PTW_S              ; /* 0xe314 */
    unsigned int           reserved_233[2]                     ; /* 0xe318~0xe31c */
    U_SMMU_FAULT_ADDR_PTW_NS   SMMU_FAULT_ADDR_PTW_NS        ; /* 0xe320 */
    U_SMMU_FAULT_ID_PTW_NS   SMMU_FAULT_ID_PTW_NS            ; /* 0xe324 */
    U_SMMU_FAULT_PTW_NUM   SMMU_FAULT_PTW_NUM                ; /* 0xe328 */
    unsigned int           reserved_234                     ; /* 0xe32c */
    U_SMMU_FAULT_ADDR_WR_S   SMMU_FAULT_ADDR_WR_S            ; /* 0xe330 */
    U_SMMU_FAULT_TLB_WR_S   SMMU_FAULT_TLB_WR_S              ; /* 0xe334 */
    U_SMMU_FAULT_ID_WR_S   SMMU_FAULT_ID_WR_S                ; /* 0xe338 */
    unsigned int           reserved_235                     ; /* 0xe33c */
    U_SMMU_FAULT_ADDR_WR_NS   SMMU_FAULT_ADDR_WR_NS          ; /* 0xe340 */
    U_SMMU_FAULT_TLB_WR_NS   SMMU_FAULT_TLB_WR_NS            ; /* 0xe344 */
    U_SMMU_FAULT_ID_WR_NS   SMMU_FAULT_ID_WR_NS              ; /* 0xe348 */
    unsigned int           reserved_236                     ; /* 0xe34c */
    U_SMMU_FAULT_ADDR_RD_S   SMMU_FAULT_ADDR_RD_S            ; /* 0xe350 */
    U_SMMU_FAULT_TLB_RD_S   SMMU_FAULT_TLB_RD_S              ; /* 0xe354 */
    U_SMMU_FAULT_ID_RD_S   SMMU_FAULT_ID_RD_S                ; /* 0xe358 */
    unsigned int           reserved_237                     ; /* 0xe35c */
    U_SMMU_FAULT_ADDR_RD_NS   SMMU_FAULT_ADDR_RD_NS          ; /* 0xe360 */
    U_SMMU_FAULT_TLB_RD_NS   SMMU_FAULT_TLB_RD_NS            ; /* 0xe364 */
    U_SMMU_FAULT_ID_RD_NS   SMMU_FAULT_ID_RD_NS              ; /* 0xe368 */
    U_SMMU_FAULT_TBU_INFO   SMMU_FAULT_TBU_INFO              ; /* 0xe36c */
    U_SMMU_FAULT_TBU_DBG   SMMU_FAULT_TBU_DBG                ; /* 0xe370 */
    U_SMMU_PREF_BUFFER_EMPTY   SMMU_PREF_BUFFER_EMPTY        ; /* 0xe374 */
    U_SMMU_PTWQ_IDLE       SMMU_PTWQ_IDLE                    ; /* 0xe378 */
    U_SMMU_RESET_STATE     SMMU_RESET_STATE                  ; /* 0xe37c */
    U_SMMU_MASTER_DBG0     SMMU_MASTER_DBG0                  ; /* 0xe380 */
    U_SMMU_MASTER_DBG1     SMMU_MASTER_DBG1                  ; /* 0xe384 */
    U_SMMU_MASTER_DBG2     SMMU_MASTER_DBG2                  ; /* 0xe388 */
    U_SMMU_MASTER_DBG3     SMMU_MASTER_DBG3                  ; /* 0xe38c */
    unsigned int           reserved_238[100]                     ; /* 0xe390~0xe51c */
    U_SMMU_MASTER_DBG4     SMMU_MASTER_DBG4                  ; /* 0xe520 */
    U_SMMU_MASTER_DBG5     SMMU_MASTER_DBG5                  ; /* 0xe524 */
    U_SMMU_MASTER_DBG6     SMMU_MASTER_DBG6                  ; /* 0xe528 */
    U_SMMU_MASTER_DBG7     SMMU_MASTER_DBG7                  ; /* 0xe52c */
    U_SMMU_MASTER_DBG8     SMMU_MASTER_DBG8                  ; /* 0xe530 */

} S_VDP_REGS_TYPE;


#endif /* __HI_REG_VDP_H__ */
