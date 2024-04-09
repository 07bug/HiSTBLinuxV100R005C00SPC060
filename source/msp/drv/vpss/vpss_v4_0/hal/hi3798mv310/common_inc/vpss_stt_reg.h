//******************************************************************************
// Copyright     :  Copyright (C) 2015, Hisilicon Technologies Co., Ltd.
// File name     :  c_union_define.h
// Author        :  xxx
// Version       :  1.0
// Date          :  2015-11-07
// Description   :  Define all registers/tables for xxx
// Others        :  Generated automatically by nManager V4.0
// History       :  xxx 2015-11-07 Create file
//******************************************************************************

#ifndef __VPSS_STT_REG_H__
#define __VPSS_STT_REG_H__

/* Define the union U_LBD_TB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    top                   : 16  ; /* [15..0]  */
        unsigned int    bot                   : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LBD_TB;

/* Define the union U_LBD_LR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    left                  : 16  ; /* [15..0]  */
        unsigned int    right                 : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LBD_LR;

/* Define the union U_LBD_SHIFT_TB */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    shift_top             : 16  ; /* [15..0]  */
        unsigned int    shift_bot             : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LBD_SHIFT_TB;

/* Define the union U_LBD_SHIFT_LR */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    shift_left            : 16  ; /* [15..0]  */
        unsigned int    shift_right           : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_LBD_SHIFT_LR;

/* Define the union U_SCD_HIST_BIN_1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_1         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_1;
/* Define the union U_SCD_HIST_BIN_2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_2         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_2;
/* Define the union U_SCD_HIST_BIN_3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_3         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_3;
/* Define the union U_SCD_HIST_BIN_4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_4         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_4;
/* Define the union U_SCD_HIST_BIN_5 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_5         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_5;
/* Define the union U_SCD_HIST_BIN_6 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_6         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_6;
/* Define the union U_SCD_HIST_BIN_7 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_7         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_7;
/* Define the union U_SCD_HIST_BIN_8 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_8         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_8;
/* Define the union U_SCD_HIST_BIN_9 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_9         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_9;
/* Define the union U_SCD_HIST_BIN_10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_10        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_10;
/* Define the union U_SCD_HIST_BIN_11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_11        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_11;
/* Define the union U_SCD_HIST_BIN_12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_12        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_12;
/* Define the union U_SCD_HIST_BIN_13 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_13        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_13;
/* Define the union U_SCD_HIST_BIN_14 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_14        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_14;
/* Define the union U_SCD_HIST_BIN_15 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_15        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_15;
/* Define the union U_SCD_HIST_BIN_16 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_16        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_16;
/* Define the union U_SCD_HIST_BIN_17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_17        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_17;
/* Define the union U_SCD_HIST_BIN_18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_18        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_18;
/* Define the union U_SCD_HIST_BIN_19 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_19        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_19;
/* Define the union U_SCD_HIST_BIN_20 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_20        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_20;
/* Define the union U_SCD_HIST_BIN_21 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_21        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_21;
/* Define the union U_SCD_HIST_BIN_22 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_22        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_22;
/* Define the union U_SCD_HIST_BIN_23 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_23        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_23;
/* Define the union U_SCD_HIST_BIN_24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_24        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_24;
/* Define the union U_SCD_HIST_BIN_25 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_25        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_25;
/* Define the union U_SCD_HIST_BIN_26 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_26        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_26;
/* Define the union U_SCD_HIST_BIN_27 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_27        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_27;
/* Define the union U_SCD_HIST_BIN_28 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_28        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_28;
/* Define the union U_SCD_HIST_BIN_29 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_29        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_29;
/* Define the union U_SCD_HIST_BIN_30 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_30        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_30;
/* Define the union U_SCD_HIST_BIN_31 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_31        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_31;
/* Define the union U_SCD_HIST_BIN_32 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_hist_bin_32        : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_SCD_HIST_BIN_32;
/* Define the union U_PFMD_COMBHIST00 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist00             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST00;
/* Define the union U_PFMD_COMBHIST01 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist01             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST01;
/* Define the union U_PFMD_COMBHIST02 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist02             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST02;
/* Define the union U_PFMD_COMBHIST03 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist03             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST03;
/* Define the union U_PFMD_COMBHIST04 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist04             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST04;
/* Define the union U_PFMD_COMBHIST05 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist05             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST05;
/* Define the union U_PFMD_COMBHIST06 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist06             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST06;
/* Define the union U_PFMD_COMBHIST07 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist07             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST07;
/* Define the union U_PFMD_COMBHIST08 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist08             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST08;
/* Define the union U_PFMD_COMBHIST09 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist09             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST09;
/* Define the union U_PFMD_COMBHIST10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist10             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST10;
/* Define the union U_PFMD_COMBHIST11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist11             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST11;
/* Define the union U_PFMD_COMBHIST12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist12             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST12;
/* Define the union U_PFMD_COMBHIST13 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist13             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST13;
/* Define the union U_PFMD_COMBHIST14 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist14             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST14;
/* Define the union U_PFMD_COMBHIST15 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist15             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST15;
/* Define the union U_PFMD_COMBHIST16 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist16             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST16;
/* Define the union U_PFMD_COMBHIST17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist17             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST17;
/* Define the union U_PFMD_COMBHIST18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist18             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST18;
/* Define the union U_PFMD_COMBHIST19 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist19             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST19;
/* Define the union U_PFMD_COMBHIST20 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist20             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST20;
/* Define the union U_PFMD_COMBHIST21 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist21             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST21;
/* Define the union U_PFMD_COMBHIST22 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist22             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST22;
/* Define the union U_PFMD_COMBHIST23 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist23             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST23;
/* Define the union U_PFMD_COMBHIST24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist24             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST24;
/* Define the union U_PFMD_COMBHIST25 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist25             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST25;
/* Define the union U_PFMD_COMBHIST26 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist26             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST26;
/* Define the union U_PFMD_COMBHIST27 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist27             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST27;
/* Define the union U_PFMD_COMBHIST28 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist28             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST28;
/* Define the union U_PFMD_COMBHIST29 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist29             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST29;
/* Define the union U_PFMD_COMBHIST30 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist30             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST30;
/* Define the union U_PFMD_COMBHIST31 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist31             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST31;
/* Define the union U_PFMD_COMBHIST32 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist32             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST32;
/* Define the union U_PFMD_COMBHIST33 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist33             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST33;
/* Define the union U_PFMD_COMBHIST34 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist34             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST34;
/* Define the union U_PFMD_COMBHIST35 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist35             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST35;
/* Define the union U_PFMD_COMBHIST36 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist36             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST36;
/* Define the union U_PFMD_COMBHIST37 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist37             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST37;
/* Define the union U_PFMD_COMBHIST38 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist38             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST38;
/* Define the union U_PFMD_COMBHIST39 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist39             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST39;
/* Define the union U_PFMD_COMBHIST40 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist40             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST40;
/* Define the union U_PFMD_COMBHIST41 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist41             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST41;
/* Define the union U_PFMD_COMBHIST42 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist42             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST42;
/* Define the union U_PFMD_COMBHIST43 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist43             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST43;
/* Define the union U_PFMD_COMBHIST44 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist44             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST44;
/* Define the union U_PFMD_COMBHIST45 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist45             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST45;
/* Define the union U_PFMD_COMBHIST46 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist46             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST46;
/* Define the union U_PFMD_COMBHIST47 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist47             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST47;
/* Define the union U_PFMD_COMBHIST48 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist48             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST48;
/* Define the union U_PFMD_COMBHIST49 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist49             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST49;
/* Define the union U_PFMD_COMBHIST50 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist50             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST50;
/* Define the union U_PFMD_COMBHIST51 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist51             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST51;
/* Define the union U_PFMD_COMBHIST52 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist52             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST52;
/* Define the union U_PFMD_COMBHIST53 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist53             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST53;
/* Define the union U_PFMD_COMBHIST54 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist54             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST54;
/* Define the union U_PFMD_COMBHIST55 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist55             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST55;
/* Define the union U_PFMD_COMBHIST56 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist56             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST56;
/* Define the union U_PFMD_COMBHIST57 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist57             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST57;
/* Define the union U_PFMD_COMBHIST58 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist58             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST58;
/* Define the union U_PFMD_COMBHIST59 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist59             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST59;
/* Define the union U_PFMD_COMBHIST60 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist60             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST60;
/* Define the union U_PFMD_COMBHIST61 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist61             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST61;
/* Define the union U_PFMD_COMBHIST62 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist62             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST62;
/* Define the union U_PFMD_COMBHIST63 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combhist63             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBHIST63;
/* Define the union U_PFMD_GRADHIST00 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist00             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST00;
/* Define the union U_PFMD_GRADHIST01 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist01             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST01;
/* Define the union U_PFMD_GRADHIST02 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist02             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST02;
/* Define the union U_PFMD_GRADHIST03 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist03             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST03;
/* Define the union U_PFMD_GRADHIST04 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist04             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST04;
/* Define the union U_PFMD_GRADHIST05 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist05             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST05;
/* Define the union U_PFMD_GRADHIST06 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist06             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST06;
/* Define the union U_PFMD_GRADHIST07 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist07             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST07;
/* Define the union U_PFMD_GRADHIST08 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist08             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST08;
/* Define the union U_PFMD_GRADHIST09 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist09             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST09;
/* Define the union U_PFMD_GRADHIST10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist10             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST10;
/* Define the union U_PFMD_GRADHIST11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist11             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST11;
/* Define the union U_PFMD_GRADHIST12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist12             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST12;
/* Define the union U_PFMD_GRADHIST13 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist13             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST13;
/* Define the union U_PFMD_GRADHIST14 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist14             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST14;
/* Define the union U_PFMD_GRADHIST15 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist15             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST15;
/* Define the union U_PFMD_GRADHIST16 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist16             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST16;
/* Define the union U_PFMD_GRADHIST17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist17             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST17;
/* Define the union U_PFMD_GRADHIST18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist18             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST18;
/* Define the union U_PFMD_GRADHIST19 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist19             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST19;
/* Define the union U_PFMD_GRADHIST20 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist20             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST20;
/* Define the union U_PFMD_GRADHIST21 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist21             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST21;
/* Define the union U_PFMD_GRADHIST22 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist22             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST22;
/* Define the union U_PFMD_GRADHIST23 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist23             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST23;
/* Define the union U_PFMD_GRADHIST24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist24             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST24;
/* Define the union U_PFMD_GRADHIST25 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist25             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST25;
/* Define the union U_PFMD_GRADHIST26 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist26             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST26;
/* Define the union U_PFMD_GRADHIST27 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist27             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST27;
/* Define the union U_PFMD_GRADHIST28 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist28             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST28;
/* Define the union U_PFMD_GRADHIST29 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist29             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST29;
/* Define the union U_PFMD_GRADHIST30 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist30             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST30;
/* Define the union U_PFMD_GRADHIST31 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist31             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST31;
/* Define the union U_PFMD_GRADHIST32 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist32             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST32;
/* Define the union U_PFMD_GRADHIST33 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist33             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST33;
/* Define the union U_PFMD_GRADHIST34 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist34             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST34;
/* Define the union U_PFMD_GRADHIST35 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist35             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST35;
/* Define the union U_PFMD_GRADHIST36 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist36             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST36;
/* Define the union U_PFMD_GRADHIST37 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist37             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST37;
/* Define the union U_PFMD_GRADHIST38 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist38             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST38;
/* Define the union U_PFMD_GRADHIST39 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist39             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST39;
/* Define the union U_PFMD_GRADHIST40 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist40             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST40;
/* Define the union U_PFMD_GRADHIST41 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist41             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST41;
/* Define the union U_PFMD_GRADHIST42 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist42             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST42;
/* Define the union U_PFMD_GRADHIST43 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist43             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST43;
/* Define the union U_PFMD_GRADHIST44 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist44             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST44;
/* Define the union U_PFMD_GRADHIST45 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist45             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST45;
/* Define the union U_PFMD_GRADHIST46 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist46             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST46;
/* Define the union U_PFMD_GRADHIST47 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist47             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST47;
/* Define the union U_PFMD_GRADHIST48 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist48             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST48;
/* Define the union U_PFMD_GRADHIST49 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist49             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST49;
/* Define the union U_PFMD_GRADHIST50 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist50             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST50;
/* Define the union U_PFMD_GRADHIST51 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist51             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST51;
/* Define the union U_PFMD_GRADHIST52 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist52             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST52;
/* Define the union U_PFMD_GRADHIST53 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist53             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST53;
/* Define the union U_PFMD_GRADHIST54 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist54             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST54;
/* Define the union U_PFMD_GRADHIST55 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist55             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST55;
/* Define the union U_PFMD_GRADHIST56 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist56             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST56;
/* Define the union U_PFMD_GRADHIST57 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist57             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST57;
/* Define the union U_PFMD_GRADHIST58 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist58             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST58;
/* Define the union U_PFMD_GRADHIST59 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist59             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST59;
/* Define the union U_PFMD_GRADHIST60 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist60             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST60;
/* Define the union U_PFMD_GRADHIST61 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist61             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST61;
/* Define the union U_PFMD_GRADHIST62 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist62             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST62;
/* Define the union U_PFMD_GRADHIST63 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int gradhist63             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_GRADHIST63;
/* Define the union U_PFMD_CUR_HIST000 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist000            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST000;
/* Define the union U_PFMD_CUR_HIST001 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist001            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST001;
/* Define the union U_PFMD_CUR_HIST002 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist002            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST002;
/* Define the union U_PFMD_CUR_HIST003 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist003            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST003;
/* Define the union U_PFMD_CUR_HIST004 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist004            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST004;
/* Define the union U_PFMD_CUR_HIST005 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist005            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST005;
/* Define the union U_PFMD_CUR_HIST006 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist006            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST006;
/* Define the union U_PFMD_CUR_HIST007 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist007            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST007;
/* Define the union U_PFMD_CUR_HIST008 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist008            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST008;
/* Define the union U_PFMD_CUR_HIST009 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist009            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST009;
/* Define the union U_PFMD_CUR_HIST010 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist010            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST010;
/* Define the union U_PFMD_CUR_HIST011 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist011            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST011;
/* Define the union U_PFMD_CUR_HIST012 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist012            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST012;
/* Define the union U_PFMD_CUR_HIST013 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist013            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST013;
/* Define the union U_PFMD_CUR_HIST014 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist014            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST014;
/* Define the union U_PFMD_CUR_HIST015 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist015            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST015;
/* Define the union U_PFMD_CUR_HIST016 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist016            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST016;
/* Define the union U_PFMD_CUR_HIST017 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist017            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST017;
/* Define the union U_PFMD_CUR_HIST018 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist018            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST018;
/* Define the union U_PFMD_CUR_HIST019 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist019            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST019;
/* Define the union U_PFMD_CUR_HIST020 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist020            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST020;
/* Define the union U_PFMD_CUR_HIST021 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist021            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST021;
/* Define the union U_PFMD_CUR_HIST022 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist022            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST022;
/* Define the union U_PFMD_CUR_HIST023 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist023            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST023;
/* Define the union U_PFMD_CUR_HIST024 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist024            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST024;
/* Define the union U_PFMD_CUR_HIST025 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist025            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST025;
/* Define the union U_PFMD_CUR_HIST026 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist026            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST026;
/* Define the union U_PFMD_CUR_HIST027 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist027            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST027;
/* Define the union U_PFMD_CUR_HIST028 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist028            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST028;
/* Define the union U_PFMD_CUR_HIST029 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist029            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST029;
/* Define the union U_PFMD_CUR_HIST030 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist030            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST030;
/* Define the union U_PFMD_CUR_HIST031 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist031            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST031;
/* Define the union U_PFMD_CUR_HIST032 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist032            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST032;
/* Define the union U_PFMD_CUR_HIST033 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist033            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST033;
/* Define the union U_PFMD_CUR_HIST034 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist034            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST034;
/* Define the union U_PFMD_CUR_HIST035 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist035            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST035;
/* Define the union U_PFMD_CUR_HIST036 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist036            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST036;
/* Define the union U_PFMD_CUR_HIST037 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist037            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST037;
/* Define the union U_PFMD_CUR_HIST038 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist038            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST038;
/* Define the union U_PFMD_CUR_HIST039 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist039            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST039;
/* Define the union U_PFMD_CUR_HIST040 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist040            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST040;
/* Define the union U_PFMD_CUR_HIST041 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist041            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST041;
/* Define the union U_PFMD_CUR_HIST042 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist042            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST042;
/* Define the union U_PFMD_CUR_HIST043 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist043            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST043;
/* Define the union U_PFMD_CUR_HIST044 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist044            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST044;
/* Define the union U_PFMD_CUR_HIST045 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist045            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST045;
/* Define the union U_PFMD_CUR_HIST046 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist046            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST046;
/* Define the union U_PFMD_CUR_HIST047 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist047            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST047;
/* Define the union U_PFMD_CUR_HIST048 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist048            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST048;
/* Define the union U_PFMD_CUR_HIST049 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist049            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST049;
/* Define the union U_PFMD_CUR_HIST050 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist050            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST050;
/* Define the union U_PFMD_CUR_HIST051 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist051            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST051;
/* Define the union U_PFMD_CUR_HIST052 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist052            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST052;
/* Define the union U_PFMD_CUR_HIST053 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist053            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST053;
/* Define the union U_PFMD_CUR_HIST054 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist054            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST054;
/* Define the union U_PFMD_CUR_HIST055 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist055            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST055;
/* Define the union U_PFMD_CUR_HIST056 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist056            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST056;
/* Define the union U_PFMD_CUR_HIST057 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist057            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST057;
/* Define the union U_PFMD_CUR_HIST058 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist058            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST058;
/* Define the union U_PFMD_CUR_HIST059 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist059            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST059;
/* Define the union U_PFMD_CUR_HIST060 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist060            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST060;
/* Define the union U_PFMD_CUR_HIST061 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist061            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST061;
/* Define the union U_PFMD_CUR_HIST062 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist062            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST062;
/* Define the union U_PFMD_CUR_HIST063 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist063            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST063;
/* Define the union U_PFMD_CUR_HIST064 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist064            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST064;
/* Define the union U_PFMD_CUR_HIST065 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist065            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST065;
/* Define the union U_PFMD_CUR_HIST066 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist066            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST066;
/* Define the union U_PFMD_CUR_HIST067 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist067            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST067;
/* Define the union U_PFMD_CUR_HIST068 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist068            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST068;
/* Define the union U_PFMD_CUR_HIST069 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist069            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST069;
/* Define the union U_PFMD_CUR_HIST070 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist070            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST070;
/* Define the union U_PFMD_CUR_HIST071 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist071            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST071;
/* Define the union U_PFMD_CUR_HIST072 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist072            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST072;
/* Define the union U_PFMD_CUR_HIST073 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist073            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST073;
/* Define the union U_PFMD_CUR_HIST074 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist074            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST074;
/* Define the union U_PFMD_CUR_HIST075 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist075            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST075;
/* Define the union U_PFMD_CUR_HIST076 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist076            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST076;
/* Define the union U_PFMD_CUR_HIST077 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist077            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST077;
/* Define the union U_PFMD_CUR_HIST078 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist078            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST078;
/* Define the union U_PFMD_CUR_HIST079 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist079            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST079;
/* Define the union U_PFMD_CUR_HIST080 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist080            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST080;
/* Define the union U_PFMD_CUR_HIST081 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist081            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST081;
/* Define the union U_PFMD_CUR_HIST082 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist082            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST082;
/* Define the union U_PFMD_CUR_HIST083 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist083            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST083;
/* Define the union U_PFMD_CUR_HIST084 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist084            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST084;
/* Define the union U_PFMD_CUR_HIST085 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist085            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST085;
/* Define the union U_PFMD_CUR_HIST086 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist086            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST086;
/* Define the union U_PFMD_CUR_HIST087 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist087            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST087;
/* Define the union U_PFMD_CUR_HIST088 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist088            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST088;
/* Define the union U_PFMD_CUR_HIST089 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist089            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST089;
/* Define the union U_PFMD_CUR_HIST090 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist090            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST090;
/* Define the union U_PFMD_CUR_HIST091 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist091            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST091;
/* Define the union U_PFMD_CUR_HIST092 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist092            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST092;
/* Define the union U_PFMD_CUR_HIST093 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist093            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST093;
/* Define the union U_PFMD_CUR_HIST094 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist094            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST094;
/* Define the union U_PFMD_CUR_HIST095 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist095            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST095;
/* Define the union U_PFMD_CUR_HIST096 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist096            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST096;
/* Define the union U_PFMD_CUR_HIST097 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist097            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST097;
/* Define the union U_PFMD_CUR_HIST098 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist098            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST098;
/* Define the union U_PFMD_CUR_HIST099 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist099            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST099;
/* Define the union U_PFMD_CUR_HIST100 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist100            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST100;
/* Define the union U_PFMD_CUR_HIST101 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist101            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST101;
/* Define the union U_PFMD_CUR_HIST102 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist102            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST102;
/* Define the union U_PFMD_CUR_HIST103 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist103            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST103;
/* Define the union U_PFMD_CUR_HIST104 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist104            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST104;
/* Define the union U_PFMD_CUR_HIST105 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist105            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST105;
/* Define the union U_PFMD_CUR_HIST106 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist106            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST106;
/* Define the union U_PFMD_CUR_HIST107 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist107            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST107;
/* Define the union U_PFMD_CUR_HIST108 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist108            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST108;
/* Define the union U_PFMD_CUR_HIST109 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist109            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST109;
/* Define the union U_PFMD_CUR_HIST110 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist110            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST110;
/* Define the union U_PFMD_CUR_HIST111 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist111            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST111;
/* Define the union U_PFMD_CUR_HIST112 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist112            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST112;
/* Define the union U_PFMD_CUR_HIST113 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist113            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST113;
/* Define the union U_PFMD_CUR_HIST114 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist114            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST114;
/* Define the union U_PFMD_CUR_HIST115 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist115            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST115;
/* Define the union U_PFMD_CUR_HIST116 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist116            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST116;
/* Define the union U_PFMD_CUR_HIST117 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist117            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST117;
/* Define the union U_PFMD_CUR_HIST118 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist118            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST118;
/* Define the union U_PFMD_CUR_HIST119 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist119            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST119;
/* Define the union U_PFMD_CUR_HIST120 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist120            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST120;
/* Define the union U_PFMD_CUR_HIST121 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist121            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST121;
/* Define the union U_PFMD_CUR_HIST122 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist122            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST122;
/* Define the union U_PFMD_CUR_HIST123 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist123            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST123;
/* Define the union U_PFMD_CUR_HIST124 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist124            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST124;
/* Define the union U_PFMD_CUR_HIST125 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist125            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST125;
/* Define the union U_PFMD_CUR_HIST126 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist126            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST126;
/* Define the union U_PFMD_CUR_HIST127 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cur_hist127            : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CUR_HIST127;
/* Define the union U_PFMD_COMB00 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb00                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB00;
/* Define the union U_PFMD_COMB01 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb01                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB01;
/* Define the union U_PFMD_COMB02 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb02                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB02;
/* Define the union U_PFMD_COMB03 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb03                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB03;
/* Define the union U_PFMD_COMB04 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb04                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB04;
/* Define the union U_PFMD_COMB05 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb05                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB05;
/* Define the union U_PFMD_COMB06 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb06                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB06;
/* Define the union U_PFMD_COMB07 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb07                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB07;
/* Define the union U_PFMD_COMB08 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb08                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB08;
/* Define the union U_PFMD_COMB09 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb09                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB09;
/* Define the union U_PFMD_COMB10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb10                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB10;
/* Define the union U_PFMD_COMB11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb11                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB11;
/* Define the union U_PFMD_COMB12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb12                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB12;
/* Define the union U_PFMD_COMB13 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb13                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB13;
/* Define the union U_PFMD_COMB14 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb14                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB14;
/* Define the union U_PFMD_COMB15 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb15                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB15;
/* Define the union U_PFMD_COMB16 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb16                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB16;
/* Define the union U_PFMD_COMB17 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb17                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB17;
/* Define the union U_PFMD_COMB18 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb18                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB18;
/* Define the union U_PFMD_COMB19 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb19                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB19;
/* Define the union U_PFMD_COMB20 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb20                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB20;
/* Define the union U_PFMD_COMB21 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb21                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB21;
/* Define the union U_PFMD_COMB22 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb22                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB22;
/* Define the union U_PFMD_COMB23 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb23                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB23;
/* Define the union U_PFMD_COMB24 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb24                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB24;
/* Define the union U_PFMD_COMB25 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb25                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB25;
/* Define the union U_PFMD_COMB26 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb26                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB26;
/* Define the union U_PFMD_COMB27 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb27                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB27;
/* Define the union U_PFMD_COMB28 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb28                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB28;
/* Define the union U_PFMD_COMB29 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb29                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB29;
/* Define the union U_PFMD_COMB30 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb30                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB30;
/* Define the union U_PFMD_COMB31 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb31                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB31;
/* Define the union U_PFMD_CHD000 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd000                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD000;
/* Define the union U_PFMD_CHD001 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd001                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD001;
/* Define the union U_PFMD_CHD002 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd002                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD002;
/* Define the union U_PFMD_CHD003 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd003                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD003;
/* Define the union U_PFMD_CHD004 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd004                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD004;
/* Define the union U_PFMD_CHD005 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd005                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD005;
/* Define the union U_PFMD_CHD006 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd006                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD006;
/* Define the union U_PFMD_CHD007 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd007                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD007;
/* Define the union U_PFMD_CHD008 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd008                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD008;
/* Define the union U_PFMD_CHD009 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd009                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD009;
/* Define the union U_PFMD_CHD010 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd010                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD010;
/* Define the union U_PFMD_CHD011 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd011                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD011;
/* Define the union U_PFMD_CHD012 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd012                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD012;
/* Define the union U_PFMD_CHD013 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd013                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD013;
/* Define the union U_PFMD_CHD014 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd014                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD014;
/* Define the union U_PFMD_CHD015 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd015                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD015;
/* Define the union U_PFMD_CHD016 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd016                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD016;
/* Define the union U_PFMD_CHD017 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd017                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD017;
/* Define the union U_PFMD_CHD018 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd018                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD018;
/* Define the union U_PFMD_CHD019 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd019                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD019;
/* Define the union U_PFMD_CHD020 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd020                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD020;
/* Define the union U_PFMD_CHD021 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd021                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD021;
/* Define the union U_PFMD_CHD022 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd022                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD022;
/* Define the union U_PFMD_CHD023 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd023                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD023;
/* Define the union U_PFMD_CHD024 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd024                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD024;
/* Define the union U_PFMD_CHD025 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd025                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD025;
/* Define the union U_PFMD_CHD026 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd026                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD026;
/* Define the union U_PFMD_CHD027 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd027                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD027;
/* Define the union U_PFMD_CHD028 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd028                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD028;
/* Define the union U_PFMD_CHD029 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd029                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD029;
/* Define the union U_PFMD_CHD030 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd030                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD030;
/* Define the union U_PFMD_CHD031 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd031                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD031;
/* Define the union U_PFMD_CHD032 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd032                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD032;
/* Define the union U_PFMD_CHD033 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd033                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD033;
/* Define the union U_PFMD_CHD034 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd034                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD034;
/* Define the union U_PFMD_CHD035 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd035                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD035;
/* Define the union U_PFMD_CHD036 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd036                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD036;
/* Define the union U_PFMD_CHD037 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd037                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD037;
/* Define the union U_PFMD_CHD038 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd038                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD038;
/* Define the union U_PFMD_CHD039 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd039                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD039;
/* Define the union U_PFMD_CHD040 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd040                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD040;
/* Define the union U_PFMD_CHD041 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd041                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD041;
/* Define the union U_PFMD_CHD042 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd042                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD042;
/* Define the union U_PFMD_CHD043 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd043                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD043;
/* Define the union U_PFMD_CHD044 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd044                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD044;
/* Define the union U_PFMD_CHD045 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd045                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD045;
/* Define the union U_PFMD_CHD046 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd046                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD046;
/* Define the union U_PFMD_CHD047 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd047                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD047;
/* Define the union U_PFMD_CHD048 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd048                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD048;
/* Define the union U_PFMD_CHD049 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd049                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD049;
/* Define the union U_PFMD_CHD050 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd050                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD050;
/* Define the union U_PFMD_CHD051 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd051                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD051;
/* Define the union U_PFMD_CHD052 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd052                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD052;
/* Define the union U_PFMD_CHD053 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd053                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD053;
/* Define the union U_PFMD_CHD054 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd054                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD054;
/* Define the union U_PFMD_CHD055 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd055                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD055;
/* Define the union U_PFMD_CHD056 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd056                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD056;
/* Define the union U_PFMD_CHD057 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd057                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD057;
/* Define the union U_PFMD_CHD058 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd058                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD058;
/* Define the union U_PFMD_CHD059 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd059                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD059;
/* Define the union U_PFMD_CHD060 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd060                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD060;
/* Define the union U_PFMD_CHD061 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd061                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD061;
/* Define the union U_PFMD_CHD062 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd062                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD062;
/* Define the union U_PFMD_CHD063 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd063                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD063;
/* Define the union U_PFMD_CHD064 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd064                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD064;
/* Define the union U_PFMD_CHD065 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd065                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD065;
/* Define the union U_PFMD_CHD066 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd066                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD066;
/* Define the union U_PFMD_CHD067 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd067                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD067;
/* Define the union U_PFMD_CHD068 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd068                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD068;
/* Define the union U_PFMD_CHD069 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd069                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD069;
/* Define the union U_PFMD_CHD070 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd070                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD070;
/* Define the union U_PFMD_CHD071 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd071                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD071;
/* Define the union U_PFMD_CHD072 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd072                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD072;
/* Define the union U_PFMD_CHD073 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd073                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD073;
/* Define the union U_PFMD_CHD074 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd074                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD074;
/* Define the union U_PFMD_CHD075 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd075                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD075;
/* Define the union U_PFMD_CHD076 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd076                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD076;
/* Define the union U_PFMD_CHD077 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd077                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD077;
/* Define the union U_PFMD_CHD078 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd078                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD078;
/* Define the union U_PFMD_CHD079 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd079                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD079;
/* Define the union U_PFMD_CHD080 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd080                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD080;
/* Define the union U_PFMD_CHD081 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd081                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD081;
/* Define the union U_PFMD_CHD082 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd082                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD082;
/* Define the union U_PFMD_CHD083 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd083                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD083;
/* Define the union U_PFMD_CHD084 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd084                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD084;
/* Define the union U_PFMD_CHD085 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd085                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD085;
/* Define the union U_PFMD_CHD086 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd086                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD086;
/* Define the union U_PFMD_CHD087 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd087                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD087;
/* Define the union U_PFMD_CHD088 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd088                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD088;
/* Define the union U_PFMD_CHD089 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd089                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD089;
/* Define the union U_PFMD_CHD090 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd090                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD090;
/* Define the union U_PFMD_CHD091 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd091                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD091;
/* Define the union U_PFMD_CHD092 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd092                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD092;
/* Define the union U_PFMD_CHD093 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd093                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD093;
/* Define the union U_PFMD_CHD094 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd094                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD094;
/* Define the union U_PFMD_CHD095 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd095                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD095;
/* Define the union U_PFMD_CHD096 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd096                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD096;
/* Define the union U_PFMD_CHD097 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd097                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD097;
/* Define the union U_PFMD_CHD098 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd098                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD098;
/* Define the union U_PFMD_CHD099 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd099                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD099;
/* Define the union U_PFMD_CHD100 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd100                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD100;
/* Define the union U_PFMD_CHD101 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd101                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD101;
/* Define the union U_PFMD_CHD102 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd102                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD102;
/* Define the union U_PFMD_CHD103 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd103                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD103;
/* Define the union U_PFMD_CHD104 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd104                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD104;
/* Define the union U_PFMD_CHD105 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd105                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD105;
/* Define the union U_PFMD_CHD106 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd106                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD106;
/* Define the union U_PFMD_CHD107 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd107                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD107;
/* Define the union U_PFMD_CHD108 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd108                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD108;
/* Define the union U_PFMD_CHD109 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd109                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD109;
/* Define the union U_PFMD_CHD110 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd110                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD110;
/* Define the union U_PFMD_CHD111 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd111                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD111;
/* Define the union U_PFMD_CHD112 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd112                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD112;
/* Define the union U_PFMD_CHD113 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd113                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD113;
/* Define the union U_PFMD_CHD114 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd114                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD114;
/* Define the union U_PFMD_CHD115 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd115                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD115;
/* Define the union U_PFMD_CHD116 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd116                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD116;
/* Define the union U_PFMD_CHD117 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd117                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD117;
/* Define the union U_PFMD_CHD118 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd118                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD118;
/* Define the union U_PFMD_CHD119 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd119                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD119;
/* Define the union U_PFMD_CHD120 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd120                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD120;
/* Define the union U_PFMD_CHD121 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd121                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD121;
/* Define the union U_PFMD_CHD122 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd122                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD122;
/* Define the union U_PFMD_CHD123 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd123                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD123;
/* Define the union U_PFMD_CHD124 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd124                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD124;
/* Define the union U_PFMD_CHD125 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd125                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD125;
/* Define the union U_PFMD_CHD126 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd126                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD126;
/* Define the union U_PFMD_CHD127 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int chd127                 : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CHD127;
/* Define the union U_PFMD_MODE00_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode00_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode00_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode00_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode00_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode00_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode00_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode00_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode00_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode00_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode00_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode00_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode00_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode00_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode00_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode00_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode00_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE00_COMBVARY_0;

/* Define the union U_PFMD_MODE00_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode00_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode00_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode00_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode00_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode00_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode00_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode00_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode00_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode00_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode00_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode00_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode00_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode00_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode00_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode00_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode00_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE00_COMBVARY_1;

/* Define the union U_PFMD_MODE01_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode01_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode01_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode01_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode01_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode01_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode01_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode01_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode01_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode01_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode01_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode01_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode01_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode01_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode01_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode01_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode01_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE01_COMBVARY_0;

/* Define the union U_PFMD_MODE01_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode01_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode01_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode01_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode01_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode01_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode01_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode01_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode01_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode01_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode01_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode01_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode01_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode01_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode01_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode01_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode01_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE01_COMBVARY_1;

/* Define the union U_PFMD_MODE02_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode02_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode02_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode02_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode02_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode02_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode02_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode02_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode02_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode02_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode02_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode02_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode02_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode02_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode02_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode02_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode02_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE02_COMBVARY_0;

/* Define the union U_PFMD_MODE02_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode02_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode02_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode02_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode02_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode02_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode02_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode02_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode02_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode02_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode02_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode02_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode02_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode02_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode02_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode02_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode02_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE02_COMBVARY_1;

/* Define the union U_PFMD_MODE03_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode03_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode03_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode03_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode03_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode03_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode03_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode03_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode03_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode03_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode03_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode03_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode03_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode03_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode03_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode03_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode03_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE03_COMBVARY_0;

/* Define the union U_PFMD_MODE03_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode03_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode03_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode03_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode03_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode03_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode03_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode03_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode03_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode03_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode03_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode03_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode03_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode03_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode03_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode03_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode03_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE03_COMBVARY_1;

/* Define the union U_PFMD_MODE04_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode04_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode04_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode04_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode04_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode04_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode04_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode04_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode04_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode04_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode04_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode04_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode04_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode04_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode04_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode04_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode04_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE04_COMBVARY_0;

/* Define the union U_PFMD_MODE04_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode04_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode04_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode04_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode04_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode04_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode04_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode04_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode04_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode04_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode04_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode04_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode04_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode04_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode04_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode04_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode04_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE04_COMBVARY_1;

/* Define the union U_PFMD_MODE05_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode05_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode05_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode05_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode05_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode05_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode05_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode05_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode05_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode05_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode05_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode05_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode05_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode05_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode05_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode05_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode05_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE05_COMBVARY_0;

/* Define the union U_PFMD_MODE05_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode05_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode05_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode05_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode05_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode05_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode05_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode05_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode05_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode05_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode05_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode05_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode05_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode05_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode05_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode05_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode05_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE05_COMBVARY_1;

/* Define the union U_PFMD_MODE06_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode06_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode06_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode06_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode06_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode06_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode06_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode06_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode06_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode06_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode06_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode06_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode06_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode06_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode06_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode06_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode06_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE06_COMBVARY_0;

/* Define the union U_PFMD_MODE06_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode06_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode06_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode06_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode06_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode06_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode06_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode06_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode06_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode06_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode06_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode06_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode06_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode06_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode06_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode06_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode06_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE06_COMBVARY_1;

/* Define the union U_PFMD_MODE07_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode07_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode07_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode07_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode07_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode07_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode07_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode07_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode07_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode07_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode07_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode07_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode07_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode07_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode07_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode07_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode07_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE07_COMBVARY_0;

/* Define the union U_PFMD_MODE07_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode07_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode07_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode07_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode07_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode07_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode07_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode07_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode07_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode07_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode07_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode07_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode07_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode07_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode07_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode07_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode07_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE07_COMBVARY_1;

/* Define the union U_PFMD_MODE08_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode08_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode08_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode08_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode08_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode08_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode08_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode08_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode08_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode08_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode08_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode08_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode08_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode08_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode08_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode08_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode08_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE08_COMBVARY_0;

/* Define the union U_PFMD_MODE08_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode08_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode08_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode08_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode08_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode08_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode08_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode08_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode08_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode08_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode08_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode08_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode08_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode08_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode08_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode08_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode08_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE08_COMBVARY_1;

/* Define the union U_PFMD_MODE09_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode09_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode09_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode09_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode09_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode09_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode09_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode09_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode09_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode09_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode09_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode09_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode09_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode09_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode09_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode09_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode09_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE09_COMBVARY_0;

/* Define the union U_PFMD_MODE09_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode09_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode09_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode09_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode09_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode09_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode09_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode09_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode09_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode09_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode09_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode09_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode09_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode09_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode09_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode09_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode09_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE09_COMBVARY_1;

/* Define the union U_PFMD_MODE10_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode10_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode10_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode10_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode10_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode10_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode10_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode10_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode10_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode10_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode10_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode10_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode10_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode10_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode10_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode10_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode10_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE10_COMBVARY_0;

/* Define the union U_PFMD_MODE10_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode10_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode10_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode10_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode10_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode10_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode10_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode10_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode10_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode10_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode10_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode10_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode10_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode10_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode10_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode10_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode10_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE10_COMBVARY_1;

/* Define the union U_PFMD_MODE11_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode11_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode11_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode11_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode11_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode11_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode11_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode11_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode11_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode11_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode11_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode11_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode11_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode11_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode11_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode11_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode11_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE11_COMBVARY_0;

/* Define the union U_PFMD_MODE11_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode11_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode11_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode11_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode11_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode11_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode11_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode11_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode11_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode11_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode11_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode11_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode11_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode11_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode11_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode11_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode11_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE11_COMBVARY_1;

/* Define the union U_PFMD_MODE12_COMBVARY_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode12_combvary0      : 2   ; /* [1..0]  */
        unsigned int    mode12_combvary1      : 2   ; /* [3..2]  */
        unsigned int    mode12_combvary2      : 2   ; /* [5..4]  */
        unsigned int    mode12_combvary3      : 2   ; /* [7..6]  */
        unsigned int    mode12_combvary4      : 2   ; /* [9..8]  */
        unsigned int    mode12_combvary5      : 2   ; /* [11..10]  */
        unsigned int    mode12_combvary6      : 2   ; /* [13..12]  */
        unsigned int    mode12_combvary7      : 2   ; /* [15..14]  */
        unsigned int    mode12_combvary8      : 2   ; /* [17..16]  */
        unsigned int    mode12_combvary9      : 2   ; /* [19..18]  */
        unsigned int    mode12_combvary10     : 2   ; /* [21..20]  */
        unsigned int    mode12_combvary11     : 2   ; /* [23..22]  */
        unsigned int    mode12_combvary12     : 2   ; /* [25..24]  */
        unsigned int    mode12_combvary13     : 2   ; /* [27..26]  */
        unsigned int    mode12_combvary14     : 2   ; /* [29..28]  */
        unsigned int    mode12_combvary15     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE12_COMBVARY_0;

/* Define the union U_PFMD_MODE12_COMBVARY_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mode12_combvary16     : 2   ; /* [1..0]  */
        unsigned int    mode12_combvary17     : 2   ; /* [3..2]  */
        unsigned int    mode12_combvary18     : 2   ; /* [5..4]  */
        unsigned int    mode12_combvary19     : 2   ; /* [7..6]  */
        unsigned int    mode12_combvary20     : 2   ; /* [9..8]  */
        unsigned int    mode12_combvary21     : 2   ; /* [11..10]  */
        unsigned int    mode12_combvary22     : 2   ; /* [13..12]  */
        unsigned int    mode12_combvary23     : 2   ; /* [15..14]  */
        unsigned int    mode12_combvary24     : 2   ; /* [17..16]  */
        unsigned int    mode12_combvary25     : 2   ; /* [19..18]  */
        unsigned int    mode12_combvary26     : 2   ; /* [21..20]  */
        unsigned int    mode12_combvary27     : 2   ; /* [23..22]  */
        unsigned int    mode12_combvary28     : 2   ; /* [25..24]  */
        unsigned int    mode12_combvary29     : 2   ; /* [27..26]  */
        unsigned int    mode12_combvary30     : 2   ; /* [29..28]  */
        unsigned int    mode12_combvary31     : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MODE12_COMBVARY_1;

/* Define the union U_PFMD_RESERVE0 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE0;
/* Define the union U_PFMD_RESERVE1 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE1;
/* Define the union U_PFMD_PRECOMBHISTORYTHD00 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd00    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD00;
/* Define the union U_PFMD_PRECOMBHISTORYTHD01 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd01    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD01;
/* Define the union U_PFMD_PRECOMBHISTORYTHD02 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd02    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD02;
/* Define the union U_PFMD_PRECOMBHISTORYTHD03 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd03    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD03;
/* Define the union U_PFMD_PRECOMBHISTORYTHD04 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd04    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD04;
/* Define the union U_PFMD_PRECOMBHISTORYTHD05 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd05    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD05;
/* Define the union U_PFMD_PRECOMBHISTORYTHD06 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd06    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD06;
/* Define the union U_PFMD_PRECOMBHISTORYTHD07 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd07    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD07;
/* Define the union U_PFMD_PRECOMBHISTORYTHD08 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd08    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD08;
/* Define the union U_PFMD_PRECOMBHISTORYTHD09 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd09    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD09;
/* Define the union U_PFMD_PRECOMBHISTORYTHD10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd10    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD10;
/* Define the union U_PFMD_PRECOMBHISTORYTHD11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd11    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD11;
/* Define the union U_PFMD_PRECOMBHISTORYTHD12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int precombhistorythd12    : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_PRECOMBHISTORYTHD12;
/* Define the union U_PFMD_RESERVE2 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE2;
/* Define the union U_PFMD_RESERVE3 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE3;
/* Define the union U_PFMD_RESERVE4 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE4;
/* Define the union U_PFMD_CVSCDCOUNTER00 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter00         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER00;
/* Define the union U_PFMD_CVSCDCOUNTER01 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter01         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER01;
/* Define the union U_PFMD_CVSCDCOUNTER02 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter02         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER02;
/* Define the union U_PFMD_CVSCDCOUNTER03 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter03         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER03;
/* Define the union U_PFMD_CVSCDCOUNTER04 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter04         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER04;
/* Define the union U_PFMD_CVSCDCOUNTER05 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter05         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER05;
/* Define the union U_PFMD_CVSCDCOUNTER06 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter06         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER06;
/* Define the union U_PFMD_CVSCDCOUNTER07 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter07         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER07;
/* Define the union U_PFMD_CVSCDCOUNTER08 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter08         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER08;
/* Define the union U_PFMD_CVSCDCOUNTER09 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter09         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER09;
/* Define the union U_PFMD_CVSCDCOUNTER10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter10         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER10;
/* Define the union U_PFMD_CVSCDCOUNTER11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter11         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER11;
/* Define the union U_PFMD_CVSCDCOUNTER12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int cvscdcounter12         : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_CVSCDCOUNTER12;
/* Define the union U_PFMD_RESERVE5 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE5;
/* Define the union U_PFMD_RESERVE6 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE6;
/* Define the union U_PFMD_RESERVE7 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE7;
/* Define the union U_PFMD_SCDCOUNTER */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scdcounter             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SCDCOUNTER;
/* Define the union U_PFMD_RESERVE8 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE8;
/* Define the union U_PFMD_RESERVE9 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE9;
/* Define the union U_PFMD_RESERVE10 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE10;
/* Define the union U_PFMD_COMBWSIGMAOSD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combwsigmaosd          : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBWSIGMAOSD;
/* Define the union U_PFMD_COMBWSIGMA */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combwsigma             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBWSIGMA;
/* Define the union U_PFMD_COMBOSD */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int combosd                : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMBOSD;
/* Define the union U_PFMD_COMB */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int comb                   : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_COMB;
/* Define the union U_PFMD_TOTAL_OSD_PIX_NUM */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int total_osd_pix_num      : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_TOTAL_OSD_PIX_NUM;
/* Define the union U_PFMD_SCD_FLAG */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int scd_flag               : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SCD_FLAG;
/* Define the union U_PFMD_MAX_CV_OUTPUT_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cv_0          : 10  ; /* [9..0]  */
        unsigned int    max_pcc_cv_1          : 10  ; /* [19..10]  */
        unsigned int    max_pcc_cv_2          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CV_OUTPUT_0;

/* Define the union U_PFMD_MAX_CV_OUTPUT_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cv_3          : 10  ; /* [9..0]  */
        unsigned int    max_pcc_cv_4          : 10  ; /* [19..10]  */
        unsigned int    max_pcc_cv_5          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CV_OUTPUT_1;

/* Define the union U_PFMD_MAX_CV_OUTPUT_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cv_6          : 10  ; /* [9..0]  */
        unsigned int    max_pcc_cv_7          : 10  ; /* [19..10]  */
        unsigned int    max_pcc_cv_8          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CV_OUTPUT_2;

/* Define the union U_PFMD_MAX_CV_OUTPUT_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cv_9          : 10  ; /* [9..0]  */
        unsigned int    max_pcc_cv_10         : 10  ; /* [19..10]  */
        unsigned int    max_pcc_cv_11         : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CV_OUTPUT_3;

/* Define the union U_PFMD_MAX_CV_OUTPUT_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cv_12         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CV_OUTPUT_4;

/* Define the union U_PFMD_MAX_CV_PHASE_OUTPUT_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cv_phase_0    : 5   ; /* [4..0]  */
        unsigned int    max_pcc_cv_phase_1    : 5   ; /* [9..5]  */
        unsigned int    max_pcc_cv_phase_2    : 5   ; /* [14..10]  */
        unsigned int    max_pcc_cv_phase_3    : 5   ; /* [19..15]  */
        unsigned int    max_pcc_cv_phase_4    : 5   ; /* [24..20]  */
        unsigned int    max_pcc_cv_phase_5    : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CV_PHASE_OUTPUT_0;

/* Define the union U_PFMD_MAX_CV_PHASE_OUTPUT_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cv_phase_6    : 5   ; /* [4..0]  */
        unsigned int    max_pcc_cv_phase_7    : 5   ; /* [9..5]  */
        unsigned int    max_pcc_cv_phase_8    : 5   ; /* [14..10]  */
        unsigned int    max_pcc_cv_phase_9    : 5   ; /* [19..15]  */
        unsigned int    max_pcc_cv_phase_10   : 5   ; /* [24..20]  */
        unsigned int    max_pcc_cv_phase_11   : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CV_PHASE_OUTPUT_1;

/* Define the union U_PFMD_MAX_CV_PHASE_OUTPUT_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cv_phase_12   : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CV_PHASE_OUTPUT_2;

/* Define the union U_PFMD_SEC_CV_OUTPUT_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sec_pcc_cv_0          : 10  ; /* [9..0]  */
        unsigned int    sec_pcc_cv_1          : 10  ; /* [19..10]  */
        unsigned int    sec_pcc_cv_2          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SEC_CV_OUTPUT_0;

/* Define the union U_PFMD_SEC_CV_OUTPUT_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sec_pcc_cv_3          : 10  ; /* [9..0]  */
        unsigned int    sec_pcc_cv_4          : 10  ; /* [19..10]  */
        unsigned int    sec_pcc_cv_5          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SEC_CV_OUTPUT_1;

/* Define the union U_PFMD_SEC_CV_OUTPUT_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sec_pcc_cv_6          : 10  ; /* [9..0]  */
        unsigned int    sec_pcc_cv_7          : 10  ; /* [19..10]  */
        unsigned int    sec_pcc_cv_8          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SEC_CV_OUTPUT_2;

/* Define the union U_PFMD_SEC_CV_OUTPUT_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sec_pcc_cv_9          : 10  ; /* [9..0]  */
        unsigned int    sec_pcc_cv_10         : 10  ; /* [19..10]  */
        unsigned int    sec_pcc_cv_11         : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SEC_CV_OUTPUT_3;

/* Define the union U_PFMD_SEC_CV_OUTPUT_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sec_pcc_cv_12         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SEC_CV_OUTPUT_4;

/* Define the union U_PFMD_SEC_CV_PHASE_OUTPUT_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sec_pcc_cv_phase_0    : 5   ; /* [4..0]  */
        unsigned int    sec_pcc_cv_phase_1    : 5   ; /* [9..5]  */
        unsigned int    sec_pcc_cv_phase_2    : 5   ; /* [14..10]  */
        unsigned int    sec_pcc_cv_phase_3    : 5   ; /* [19..15]  */
        unsigned int    sec_pcc_cv_phase_4    : 5   ; /* [24..20]  */
        unsigned int    sec_pcc_cv_phase_5    : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SEC_CV_PHASE_OUTPUT_0;

/* Define the union U_PFMD_SEC_CV_PHASE_OUTPUT_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sec_pcc_cv_phase_6    : 5   ; /* [4..0]  */
        unsigned int    sec_pcc_cv_phase_7    : 5   ; /* [9..5]  */
        unsigned int    sec_pcc_cv_phase_8    : 5   ; /* [14..10]  */
        unsigned int    sec_pcc_cv_phase_9    : 5   ; /* [19..15]  */
        unsigned int    sec_pcc_cv_phase_10   : 5   ; /* [24..20]  */
        unsigned int    sec_pcc_cv_phase_11   : 5   ; /* [29..25]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SEC_CV_PHASE_OUTPUT_1;

/* Define the union U_PFMD_SEC_CV_PHASE_OUTPUT_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sec_pcc_cv_phase_12   : 5   ; /* [4..0]  */
        unsigned int    reserved_0            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_SEC_CV_PHASE_OUTPUT_2;

/* Define the union U_PFMD_MAX_CB_OUTPUT_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cb_0          : 10  ; /* [9..0]  */
        unsigned int    max_pcc_cb_1          : 10  ; /* [19..10]  */
        unsigned int    max_pcc_cb_2          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CB_OUTPUT_0;

/* Define the union U_PFMD_MAX_CB_OUTPUT_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cb_3          : 10  ; /* [9..0]  */
        unsigned int    max_pcc_cb_4          : 10  ; /* [19..10]  */
        unsigned int    max_pcc_cb_5          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CB_OUTPUT_1;

/* Define the union U_PFMD_MAX_CB_OUTPUT_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cb_6          : 10  ; /* [9..0]  */
        unsigned int    max_pcc_cb_7          : 10  ; /* [19..10]  */
        unsigned int    max_pcc_cb_8          : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CB_OUTPUT_2;

/* Define the union U_PFMD_MAX_CB_OUTPUT_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cb_9          : 10  ; /* [9..0]  */
        unsigned int    max_pcc_cb_10         : 10  ; /* [19..10]  */
        unsigned int    max_pcc_cb_11         : 10  ; /* [29..20]  */
        unsigned int    reserved_0            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CB_OUTPUT_3;

/* Define the union U_PFMD_MAX_CB_OUTPUT_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cb_12         : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CB_OUTPUT_4;

/* Define the union U_PFMD_MAX_CB_PHASE_OUTPUT_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cb_phase_0    : 4   ; /* [3..0]  */
        unsigned int    max_pcc_cb_phase_1    : 4   ; /* [7..4]  */
        unsigned int    max_pcc_cb_phase_2    : 4   ; /* [11..8]  */
        unsigned int    max_pcc_cb_phase_3    : 4   ; /* [15..12]  */
        unsigned int    max_pcc_cb_phase_4    : 4   ; /* [19..16]  */
        unsigned int    max_pcc_cb_phase_5    : 4   ; /* [23..20]  */
        unsigned int    max_pcc_cb_phase_6    : 4   ; /* [27..24]  */
        unsigned int    max_pcc_cb_phase_7    : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CB_PHASE_OUTPUT_0;

/* Define the union U_PFMD_MAX_CB_PHASE_OUTPUT_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    max_pcc_cb_phase_8    : 4   ; /* [3..0]  */
        unsigned int    max_pcc_cb_phase_9    : 4   ; /* [7..4]  */
        unsigned int    max_pcc_cb_phase_10   : 4   ; /* [11..8]  */
        unsigned int    max_pcc_cb_phase_11   : 4   ; /* [15..12]  */
        unsigned int    max_pcc_cb_phase_12   : 4   ; /* [19..16]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_MAX_CB_PHASE_OUTPUT_1;

/* Define the union U_PFMD_RESERVE11 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE11;
/* Define the union U_PFMD_RESERVE12 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE12;
/* Define the union U_PFMD_RESERVE13 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PFMD_RESERVE13;
//==============================================================================
/* Define the global struct */
#if 0
typedef struct
{
    U_LBD_TB               LBD_TB                            ; /* 0x0 */
    U_LBD_LR               LBD_LR                            ; /* 0x4 */
    U_LBD_SHIFT_TB         LBD_SHIFT_TB                      ; /* 0x8 */
    U_LBD_SHIFT_LR         LBD_SHIFT_LR                      ; /* 0xc */
    unsigned int           reserved_0[36]                     ; /* 0x10~0x9c */
    U_SCD_HIST_BIN_1       SCD_HIST_BIN_1                    ; /* 0xa0 */
    U_SCD_HIST_BIN_2       SCD_HIST_BIN_2                    ; /* 0xa4 */
    U_SCD_HIST_BIN_3       SCD_HIST_BIN_3                    ; /* 0xa8 */
    U_SCD_HIST_BIN_4       SCD_HIST_BIN_4                    ; /* 0xac */
    U_SCD_HIST_BIN_5       SCD_HIST_BIN_5                    ; /* 0xb0 */
    U_SCD_HIST_BIN_6       SCD_HIST_BIN_6                    ; /* 0xb4 */
    U_SCD_HIST_BIN_7       SCD_HIST_BIN_7                    ; /* 0xb8 */
    U_SCD_HIST_BIN_8       SCD_HIST_BIN_8                    ; /* 0xbc */
    U_SCD_HIST_BIN_9       SCD_HIST_BIN_9                    ; /* 0xc0 */
    U_SCD_HIST_BIN_10      SCD_HIST_BIN_10                   ; /* 0xc4 */
    U_SCD_HIST_BIN_11      SCD_HIST_BIN_11                   ; /* 0xc8 */
    U_SCD_HIST_BIN_12      SCD_HIST_BIN_12                   ; /* 0xcc */
    U_SCD_HIST_BIN_13      SCD_HIST_BIN_13                   ; /* 0xd0 */
    U_SCD_HIST_BIN_14      SCD_HIST_BIN_14                   ; /* 0xd4 */
    U_SCD_HIST_BIN_15      SCD_HIST_BIN_15                   ; /* 0xd8 */
    U_SCD_HIST_BIN_16      SCD_HIST_BIN_16                   ; /* 0xdc */
    U_SCD_HIST_BIN_17      SCD_HIST_BIN_17                   ; /* 0xe0 */
    U_SCD_HIST_BIN_18      SCD_HIST_BIN_18                   ; /* 0xe4 */
    U_SCD_HIST_BIN_19      SCD_HIST_BIN_19                   ; /* 0xe8 */
    U_SCD_HIST_BIN_20      SCD_HIST_BIN_20                   ; /* 0xec */
    U_SCD_HIST_BIN_21      SCD_HIST_BIN_21                   ; /* 0xf0 */
    U_SCD_HIST_BIN_22      SCD_HIST_BIN_22                   ; /* 0xf4 */
    U_SCD_HIST_BIN_23      SCD_HIST_BIN_23                   ; /* 0xf8 */
    U_SCD_HIST_BIN_24      SCD_HIST_BIN_24                   ; /* 0xfc */
    U_SCD_HIST_BIN_25      SCD_HIST_BIN_25                   ; /* 0x100 */
    U_SCD_HIST_BIN_26      SCD_HIST_BIN_26                   ; /* 0x104 */
    U_SCD_HIST_BIN_27      SCD_HIST_BIN_27                   ; /* 0x108 */
    U_SCD_HIST_BIN_28      SCD_HIST_BIN_28                   ; /* 0x10c */
    U_SCD_HIST_BIN_29      SCD_HIST_BIN_29                   ; /* 0x110 */
    U_SCD_HIST_BIN_30      SCD_HIST_BIN_30                   ; /* 0x114 */
    U_SCD_HIST_BIN_31      SCD_HIST_BIN_31                   ; /* 0x118 */
    U_SCD_HIST_BIN_32      SCD_HIST_BIN_32                   ; /* 0x11c */
    U_PFMD_COMBHIST00      PFMD_COMBHIST00                   ; /* 0x120 */
    U_PFMD_COMBHIST01      PFMD_COMBHIST01                   ; /* 0x124 */
    U_PFMD_COMBHIST02      PFMD_COMBHIST02                   ; /* 0x128 */
    U_PFMD_COMBHIST03      PFMD_COMBHIST03                   ; /* 0x12c */
    U_PFMD_COMBHIST04      PFMD_COMBHIST04                   ; /* 0x130 */
    U_PFMD_COMBHIST05      PFMD_COMBHIST05                   ; /* 0x134 */
    U_PFMD_COMBHIST06      PFMD_COMBHIST06                   ; /* 0x138 */
    U_PFMD_COMBHIST07      PFMD_COMBHIST07                   ; /* 0x13c */
    U_PFMD_COMBHIST08      PFMD_COMBHIST08                   ; /* 0x140 */
    U_PFMD_COMBHIST09      PFMD_COMBHIST09                   ; /* 0x144 */
    U_PFMD_COMBHIST10      PFMD_COMBHIST10                   ; /* 0x148 */
    U_PFMD_COMBHIST11      PFMD_COMBHIST11                   ; /* 0x14c */
    U_PFMD_COMBHIST12      PFMD_COMBHIST12                   ; /* 0x150 */
    U_PFMD_COMBHIST13      PFMD_COMBHIST13                   ; /* 0x154 */
    U_PFMD_COMBHIST14      PFMD_COMBHIST14                   ; /* 0x158 */
    U_PFMD_COMBHIST15      PFMD_COMBHIST15                   ; /* 0x15c */
    U_PFMD_COMBHIST16      PFMD_COMBHIST16                   ; /* 0x160 */
    U_PFMD_COMBHIST17      PFMD_COMBHIST17                   ; /* 0x164 */
    U_PFMD_COMBHIST18      PFMD_COMBHIST18                   ; /* 0x168 */
    U_PFMD_COMBHIST19      PFMD_COMBHIST19                   ; /* 0x16c */
    U_PFMD_COMBHIST20      PFMD_COMBHIST20                   ; /* 0x170 */
    U_PFMD_COMBHIST21      PFMD_COMBHIST21                   ; /* 0x174 */
    U_PFMD_COMBHIST22      PFMD_COMBHIST22                   ; /* 0x178 */
    U_PFMD_COMBHIST23      PFMD_COMBHIST23                   ; /* 0x17c */
    U_PFMD_COMBHIST24      PFMD_COMBHIST24                   ; /* 0x180 */
    U_PFMD_COMBHIST25      PFMD_COMBHIST25                   ; /* 0x184 */
    U_PFMD_COMBHIST26      PFMD_COMBHIST26                   ; /* 0x188 */
    U_PFMD_COMBHIST27      PFMD_COMBHIST27                   ; /* 0x18c */
    U_PFMD_COMBHIST28      PFMD_COMBHIST28                   ; /* 0x190 */
    U_PFMD_COMBHIST29      PFMD_COMBHIST29                   ; /* 0x194 */
    U_PFMD_COMBHIST30      PFMD_COMBHIST30                   ; /* 0x198 */
    U_PFMD_COMBHIST31      PFMD_COMBHIST31                   ; /* 0x19c */
    U_PFMD_COMBHIST32      PFMD_COMBHIST32                   ; /* 0x1a0 */
    U_PFMD_COMBHIST33      PFMD_COMBHIST33                   ; /* 0x1a4 */
    U_PFMD_COMBHIST34      PFMD_COMBHIST34                   ; /* 0x1a8 */
    U_PFMD_COMBHIST35      PFMD_COMBHIST35                   ; /* 0x1ac */
    U_PFMD_COMBHIST36      PFMD_COMBHIST36                   ; /* 0x1b0 */
    U_PFMD_COMBHIST37      PFMD_COMBHIST37                   ; /* 0x1b4 */
    U_PFMD_COMBHIST38      PFMD_COMBHIST38                   ; /* 0x1b8 */
    U_PFMD_COMBHIST39      PFMD_COMBHIST39                   ; /* 0x1bc */
    U_PFMD_COMBHIST40      PFMD_COMBHIST40                   ; /* 0x1c0 */
    U_PFMD_COMBHIST41      PFMD_COMBHIST41                   ; /* 0x1c4 */
    U_PFMD_COMBHIST42      PFMD_COMBHIST42                   ; /* 0x1c8 */
    U_PFMD_COMBHIST43      PFMD_COMBHIST43                   ; /* 0x1cc */
    U_PFMD_COMBHIST44      PFMD_COMBHIST44                   ; /* 0x1d0 */
    U_PFMD_COMBHIST45      PFMD_COMBHIST45                   ; /* 0x1d4 */
    U_PFMD_COMBHIST46      PFMD_COMBHIST46                   ; /* 0x1d8 */
    U_PFMD_COMBHIST47      PFMD_COMBHIST47                   ; /* 0x1dc */
    U_PFMD_COMBHIST48      PFMD_COMBHIST48                   ; /* 0x1e0 */
    U_PFMD_COMBHIST49      PFMD_COMBHIST49                   ; /* 0x1e4 */
    U_PFMD_COMBHIST50      PFMD_COMBHIST50                   ; /* 0x1e8 */
    U_PFMD_COMBHIST51      PFMD_COMBHIST51                   ; /* 0x1ec */
    U_PFMD_COMBHIST52      PFMD_COMBHIST52                   ; /* 0x1f0 */
    U_PFMD_COMBHIST53      PFMD_COMBHIST53                   ; /* 0x1f4 */
    U_PFMD_COMBHIST54      PFMD_COMBHIST54                   ; /* 0x1f8 */
    U_PFMD_COMBHIST55      PFMD_COMBHIST55                   ; /* 0x1fc */
    U_PFMD_COMBHIST56      PFMD_COMBHIST56                   ; /* 0x200 */
    U_PFMD_COMBHIST57      PFMD_COMBHIST57                   ; /* 0x204 */
    U_PFMD_COMBHIST58      PFMD_COMBHIST58                   ; /* 0x208 */
    U_PFMD_COMBHIST59      PFMD_COMBHIST59                   ; /* 0x20c */
    U_PFMD_COMBHIST60      PFMD_COMBHIST60                   ; /* 0x210 */
    U_PFMD_COMBHIST61      PFMD_COMBHIST61                   ; /* 0x214 */
    U_PFMD_COMBHIST62      PFMD_COMBHIST62                   ; /* 0x218 */
    U_PFMD_COMBHIST63      PFMD_COMBHIST63                   ; /* 0x21c */
    U_PFMD_GRADHIST00      PFMD_GRADHIST00                   ; /* 0x220 */
    U_PFMD_GRADHIST01      PFMD_GRADHIST01                   ; /* 0x224 */
    U_PFMD_GRADHIST02      PFMD_GRADHIST02                   ; /* 0x228 */
    U_PFMD_GRADHIST03      PFMD_GRADHIST03                   ; /* 0x22c */
    U_PFMD_GRADHIST04      PFMD_GRADHIST04                   ; /* 0x230 */
    U_PFMD_GRADHIST05      PFMD_GRADHIST05                   ; /* 0x234 */
    U_PFMD_GRADHIST06      PFMD_GRADHIST06                   ; /* 0x238 */
    U_PFMD_GRADHIST07      PFMD_GRADHIST07                   ; /* 0x23c */
    U_PFMD_GRADHIST08      PFMD_GRADHIST08                   ; /* 0x240 */
    U_PFMD_GRADHIST09      PFMD_GRADHIST09                   ; /* 0x244 */
    U_PFMD_GRADHIST10      PFMD_GRADHIST10                   ; /* 0x248 */
    U_PFMD_GRADHIST11      PFMD_GRADHIST11                   ; /* 0x24c */
    U_PFMD_GRADHIST12      PFMD_GRADHIST12                   ; /* 0x250 */
    U_PFMD_GRADHIST13      PFMD_GRADHIST13                   ; /* 0x254 */
    U_PFMD_GRADHIST14      PFMD_GRADHIST14                   ; /* 0x258 */
    U_PFMD_GRADHIST15      PFMD_GRADHIST15                   ; /* 0x25c */
    U_PFMD_GRADHIST16      PFMD_GRADHIST16                   ; /* 0x260 */
    U_PFMD_GRADHIST17      PFMD_GRADHIST17                   ; /* 0x264 */
    U_PFMD_GRADHIST18      PFMD_GRADHIST18                   ; /* 0x268 */
    U_PFMD_GRADHIST19      PFMD_GRADHIST19                   ; /* 0x26c */
    U_PFMD_GRADHIST20      PFMD_GRADHIST20                   ; /* 0x270 */
    U_PFMD_GRADHIST21      PFMD_GRADHIST21                   ; /* 0x274 */
    U_PFMD_GRADHIST22      PFMD_GRADHIST22                   ; /* 0x278 */
    U_PFMD_GRADHIST23      PFMD_GRADHIST23                   ; /* 0x27c */
    U_PFMD_GRADHIST24      PFMD_GRADHIST24                   ; /* 0x280 */
    U_PFMD_GRADHIST25      PFMD_GRADHIST25                   ; /* 0x284 */
    U_PFMD_GRADHIST26      PFMD_GRADHIST26                   ; /* 0x288 */
    U_PFMD_GRADHIST27      PFMD_GRADHIST27                   ; /* 0x28c */
    U_PFMD_GRADHIST28      PFMD_GRADHIST28                   ; /* 0x290 */
    U_PFMD_GRADHIST29      PFMD_GRADHIST29                   ; /* 0x294 */
    U_PFMD_GRADHIST30      PFMD_GRADHIST30                   ; /* 0x298 */
    U_PFMD_GRADHIST31      PFMD_GRADHIST31                   ; /* 0x29c */
    U_PFMD_GRADHIST32      PFMD_GRADHIST32                   ; /* 0x2a0 */
    U_PFMD_GRADHIST33      PFMD_GRADHIST33                   ; /* 0x2a4 */
    U_PFMD_GRADHIST34      PFMD_GRADHIST34                   ; /* 0x2a8 */
    U_PFMD_GRADHIST35      PFMD_GRADHIST35                   ; /* 0x2ac */
    U_PFMD_GRADHIST36      PFMD_GRADHIST36                   ; /* 0x2b0 */
    U_PFMD_GRADHIST37      PFMD_GRADHIST37                   ; /* 0x2b4 */
    U_PFMD_GRADHIST38      PFMD_GRADHIST38                   ; /* 0x2b8 */
    U_PFMD_GRADHIST39      PFMD_GRADHIST39                   ; /* 0x2bc */
    U_PFMD_GRADHIST40      PFMD_GRADHIST40                   ; /* 0x2c0 */
    U_PFMD_GRADHIST41      PFMD_GRADHIST41                   ; /* 0x2c4 */
    U_PFMD_GRADHIST42      PFMD_GRADHIST42                   ; /* 0x2c8 */
    U_PFMD_GRADHIST43      PFMD_GRADHIST43                   ; /* 0x2cc */
    U_PFMD_GRADHIST44      PFMD_GRADHIST44                   ; /* 0x2d0 */
    U_PFMD_GRADHIST45      PFMD_GRADHIST45                   ; /* 0x2d4 */
    U_PFMD_GRADHIST46      PFMD_GRADHIST46                   ; /* 0x2d8 */
    U_PFMD_GRADHIST47      PFMD_GRADHIST47                   ; /* 0x2dc */
    U_PFMD_GRADHIST48      PFMD_GRADHIST48                   ; /* 0x2e0 */
    U_PFMD_GRADHIST49      PFMD_GRADHIST49                   ; /* 0x2e4 */
    U_PFMD_GRADHIST50      PFMD_GRADHIST50                   ; /* 0x2e8 */
    U_PFMD_GRADHIST51      PFMD_GRADHIST51                   ; /* 0x2ec */
    U_PFMD_GRADHIST52      PFMD_GRADHIST52                   ; /* 0x2f0 */
    U_PFMD_GRADHIST53      PFMD_GRADHIST53                   ; /* 0x2f4 */
    U_PFMD_GRADHIST54      PFMD_GRADHIST54                   ; /* 0x2f8 */
    U_PFMD_GRADHIST55      PFMD_GRADHIST55                   ; /* 0x2fc */
    U_PFMD_GRADHIST56      PFMD_GRADHIST56                   ; /* 0x300 */
    U_PFMD_GRADHIST57      PFMD_GRADHIST57                   ; /* 0x304 */
    U_PFMD_GRADHIST58      PFMD_GRADHIST58                   ; /* 0x308 */
    U_PFMD_GRADHIST59      PFMD_GRADHIST59                   ; /* 0x30c */
    U_PFMD_GRADHIST60      PFMD_GRADHIST60                   ; /* 0x310 */
    U_PFMD_GRADHIST61      PFMD_GRADHIST61                   ; /* 0x314 */
    U_PFMD_GRADHIST62      PFMD_GRADHIST62                   ; /* 0x318 */
    U_PFMD_GRADHIST63      PFMD_GRADHIST63                   ; /* 0x31c */
    U_PFMD_CUR_HIST000     PFMD_CUR_HIST000                  ; /* 0x320 */
    U_PFMD_CUR_HIST001     PFMD_CUR_HIST001                  ; /* 0x324 */
    U_PFMD_CUR_HIST002     PFMD_CUR_HIST002                  ; /* 0x328 */
    U_PFMD_CUR_HIST003     PFMD_CUR_HIST003                  ; /* 0x32c */
    U_PFMD_CUR_HIST004     PFMD_CUR_HIST004                  ; /* 0x330 */
    U_PFMD_CUR_HIST005     PFMD_CUR_HIST005                  ; /* 0x334 */
    U_PFMD_CUR_HIST006     PFMD_CUR_HIST006                  ; /* 0x338 */
    U_PFMD_CUR_HIST007     PFMD_CUR_HIST007                  ; /* 0x33c */
    U_PFMD_CUR_HIST008     PFMD_CUR_HIST008                  ; /* 0x340 */
    U_PFMD_CUR_HIST009     PFMD_CUR_HIST009                  ; /* 0x344 */
    U_PFMD_CUR_HIST010     PFMD_CUR_HIST010                  ; /* 0x348 */
    U_PFMD_CUR_HIST011     PFMD_CUR_HIST011                  ; /* 0x34c */
    U_PFMD_CUR_HIST012     PFMD_CUR_HIST012                  ; /* 0x350 */
    U_PFMD_CUR_HIST013     PFMD_CUR_HIST013                  ; /* 0x354 */
    U_PFMD_CUR_HIST014     PFMD_CUR_HIST014                  ; /* 0x358 */
    U_PFMD_CUR_HIST015     PFMD_CUR_HIST015                  ; /* 0x35c */
    U_PFMD_CUR_HIST016     PFMD_CUR_HIST016                  ; /* 0x360 */
    U_PFMD_CUR_HIST017     PFMD_CUR_HIST017                  ; /* 0x364 */
    U_PFMD_CUR_HIST018     PFMD_CUR_HIST018                  ; /* 0x368 */
    U_PFMD_CUR_HIST019     PFMD_CUR_HIST019                  ; /* 0x36c */
    U_PFMD_CUR_HIST020     PFMD_CUR_HIST020                  ; /* 0x370 */
    U_PFMD_CUR_HIST021     PFMD_CUR_HIST021                  ; /* 0x374 */
    U_PFMD_CUR_HIST022     PFMD_CUR_HIST022                  ; /* 0x378 */
    U_PFMD_CUR_HIST023     PFMD_CUR_HIST023                  ; /* 0x37c */
    U_PFMD_CUR_HIST024     PFMD_CUR_HIST024                  ; /* 0x380 */
    U_PFMD_CUR_HIST025     PFMD_CUR_HIST025                  ; /* 0x384 */
    U_PFMD_CUR_HIST026     PFMD_CUR_HIST026                  ; /* 0x388 */
    U_PFMD_CUR_HIST027     PFMD_CUR_HIST027                  ; /* 0x38c */
    U_PFMD_CUR_HIST028     PFMD_CUR_HIST028                  ; /* 0x390 */
    U_PFMD_CUR_HIST029     PFMD_CUR_HIST029                  ; /* 0x394 */
    U_PFMD_CUR_HIST030     PFMD_CUR_HIST030                  ; /* 0x398 */
    U_PFMD_CUR_HIST031     PFMD_CUR_HIST031                  ; /* 0x39c */
    U_PFMD_CUR_HIST032     PFMD_CUR_HIST032                  ; /* 0x3a0 */
    U_PFMD_CUR_HIST033     PFMD_CUR_HIST033                  ; /* 0x3a4 */
    U_PFMD_CUR_HIST034     PFMD_CUR_HIST034                  ; /* 0x3a8 */
    U_PFMD_CUR_HIST035     PFMD_CUR_HIST035                  ; /* 0x3ac */
    U_PFMD_CUR_HIST036     PFMD_CUR_HIST036                  ; /* 0x3b0 */
    U_PFMD_CUR_HIST037     PFMD_CUR_HIST037                  ; /* 0x3b4 */
    U_PFMD_CUR_HIST038     PFMD_CUR_HIST038                  ; /* 0x3b8 */
    U_PFMD_CUR_HIST039     PFMD_CUR_HIST039                  ; /* 0x3bc */
    U_PFMD_CUR_HIST040     PFMD_CUR_HIST040                  ; /* 0x3c0 */
    U_PFMD_CUR_HIST041     PFMD_CUR_HIST041                  ; /* 0x3c4 */
    U_PFMD_CUR_HIST042     PFMD_CUR_HIST042                  ; /* 0x3c8 */
    U_PFMD_CUR_HIST043     PFMD_CUR_HIST043                  ; /* 0x3cc */
    U_PFMD_CUR_HIST044     PFMD_CUR_HIST044                  ; /* 0x3d0 */
    U_PFMD_CUR_HIST045     PFMD_CUR_HIST045                  ; /* 0x3d4 */
    U_PFMD_CUR_HIST046     PFMD_CUR_HIST046                  ; /* 0x3d8 */
    U_PFMD_CUR_HIST047     PFMD_CUR_HIST047                  ; /* 0x3dc */
    U_PFMD_CUR_HIST048     PFMD_CUR_HIST048                  ; /* 0x3e0 */
    U_PFMD_CUR_HIST049     PFMD_CUR_HIST049                  ; /* 0x3e4 */
    U_PFMD_CUR_HIST050     PFMD_CUR_HIST050                  ; /* 0x3e8 */
    U_PFMD_CUR_HIST051     PFMD_CUR_HIST051                  ; /* 0x3ec */
    U_PFMD_CUR_HIST052     PFMD_CUR_HIST052                  ; /* 0x3f0 */
    U_PFMD_CUR_HIST053     PFMD_CUR_HIST053                  ; /* 0x3f4 */
    U_PFMD_CUR_HIST054     PFMD_CUR_HIST054                  ; /* 0x3f8 */
    U_PFMD_CUR_HIST055     PFMD_CUR_HIST055                  ; /* 0x3fc */
    U_PFMD_CUR_HIST056     PFMD_CUR_HIST056                  ; /* 0x400 */
    U_PFMD_CUR_HIST057     PFMD_CUR_HIST057                  ; /* 0x404 */
    U_PFMD_CUR_HIST058     PFMD_CUR_HIST058                  ; /* 0x408 */
    U_PFMD_CUR_HIST059     PFMD_CUR_HIST059                  ; /* 0x40c */
    U_PFMD_CUR_HIST060     PFMD_CUR_HIST060                  ; /* 0x410 */
    U_PFMD_CUR_HIST061     PFMD_CUR_HIST061                  ; /* 0x414 */
    U_PFMD_CUR_HIST062     PFMD_CUR_HIST062                  ; /* 0x418 */
    U_PFMD_CUR_HIST063     PFMD_CUR_HIST063                  ; /* 0x41c */
    U_PFMD_CUR_HIST064     PFMD_CUR_HIST064                  ; /* 0x420 */
    U_PFMD_CUR_HIST065     PFMD_CUR_HIST065                  ; /* 0x424 */
    U_PFMD_CUR_HIST066     PFMD_CUR_HIST066                  ; /* 0x428 */
    U_PFMD_CUR_HIST067     PFMD_CUR_HIST067                  ; /* 0x42c */
    U_PFMD_CUR_HIST068     PFMD_CUR_HIST068                  ; /* 0x430 */
    U_PFMD_CUR_HIST069     PFMD_CUR_HIST069                  ; /* 0x434 */
    U_PFMD_CUR_HIST070     PFMD_CUR_HIST070                  ; /* 0x438 */
    U_PFMD_CUR_HIST071     PFMD_CUR_HIST071                  ; /* 0x43c */
    U_PFMD_CUR_HIST072     PFMD_CUR_HIST072                  ; /* 0x440 */
    U_PFMD_CUR_HIST073     PFMD_CUR_HIST073                  ; /* 0x444 */
    U_PFMD_CUR_HIST074     PFMD_CUR_HIST074                  ; /* 0x448 */
    U_PFMD_CUR_HIST075     PFMD_CUR_HIST075                  ; /* 0x44c */
    U_PFMD_CUR_HIST076     PFMD_CUR_HIST076                  ; /* 0x450 */
    U_PFMD_CUR_HIST077     PFMD_CUR_HIST077                  ; /* 0x454 */
    U_PFMD_CUR_HIST078     PFMD_CUR_HIST078                  ; /* 0x458 */
    U_PFMD_CUR_HIST079     PFMD_CUR_HIST079                  ; /* 0x45c */
    U_PFMD_CUR_HIST080     PFMD_CUR_HIST080                  ; /* 0x460 */
    U_PFMD_CUR_HIST081     PFMD_CUR_HIST081                  ; /* 0x464 */
    U_PFMD_CUR_HIST082     PFMD_CUR_HIST082                  ; /* 0x468 */
    U_PFMD_CUR_HIST083     PFMD_CUR_HIST083                  ; /* 0x46c */
    U_PFMD_CUR_HIST084     PFMD_CUR_HIST084                  ; /* 0x470 */
    U_PFMD_CUR_HIST085     PFMD_CUR_HIST085                  ; /* 0x474 */
    U_PFMD_CUR_HIST086     PFMD_CUR_HIST086                  ; /* 0x478 */
    U_PFMD_CUR_HIST087     PFMD_CUR_HIST087                  ; /* 0x47c */
    U_PFMD_CUR_HIST088     PFMD_CUR_HIST088                  ; /* 0x480 */
    U_PFMD_CUR_HIST089     PFMD_CUR_HIST089                  ; /* 0x484 */
    U_PFMD_CUR_HIST090     PFMD_CUR_HIST090                  ; /* 0x488 */
    U_PFMD_CUR_HIST091     PFMD_CUR_HIST091                  ; /* 0x48c */
    U_PFMD_CUR_HIST092     PFMD_CUR_HIST092                  ; /* 0x490 */
    U_PFMD_CUR_HIST093     PFMD_CUR_HIST093                  ; /* 0x494 */
    U_PFMD_CUR_HIST094     PFMD_CUR_HIST094                  ; /* 0x498 */
    U_PFMD_CUR_HIST095     PFMD_CUR_HIST095                  ; /* 0x49c */
    U_PFMD_CUR_HIST096     PFMD_CUR_HIST096                  ; /* 0x4a0 */
    U_PFMD_CUR_HIST097     PFMD_CUR_HIST097                  ; /* 0x4a4 */
    U_PFMD_CUR_HIST098     PFMD_CUR_HIST098                  ; /* 0x4a8 */
    U_PFMD_CUR_HIST099     PFMD_CUR_HIST099                  ; /* 0x4ac */
    U_PFMD_CUR_HIST100     PFMD_CUR_HIST100                  ; /* 0x4b0 */
    U_PFMD_CUR_HIST101     PFMD_CUR_HIST101                  ; /* 0x4b4 */
    U_PFMD_CUR_HIST102     PFMD_CUR_HIST102                  ; /* 0x4b8 */
    U_PFMD_CUR_HIST103     PFMD_CUR_HIST103                  ; /* 0x4bc */
    U_PFMD_CUR_HIST104     PFMD_CUR_HIST104                  ; /* 0x4c0 */
    U_PFMD_CUR_HIST105     PFMD_CUR_HIST105                  ; /* 0x4c4 */
    U_PFMD_CUR_HIST106     PFMD_CUR_HIST106                  ; /* 0x4c8 */
    U_PFMD_CUR_HIST107     PFMD_CUR_HIST107                  ; /* 0x4cc */
    U_PFMD_CUR_HIST108     PFMD_CUR_HIST108                  ; /* 0x4d0 */
    U_PFMD_CUR_HIST109     PFMD_CUR_HIST109                  ; /* 0x4d4 */
    U_PFMD_CUR_HIST110     PFMD_CUR_HIST110                  ; /* 0x4d8 */
    U_PFMD_CUR_HIST111     PFMD_CUR_HIST111                  ; /* 0x4dc */
    U_PFMD_CUR_HIST112     PFMD_CUR_HIST112                  ; /* 0x4e0 */
    U_PFMD_CUR_HIST113     PFMD_CUR_HIST113                  ; /* 0x4e4 */
    U_PFMD_CUR_HIST114     PFMD_CUR_HIST114                  ; /* 0x4e8 */
    U_PFMD_CUR_HIST115     PFMD_CUR_HIST115                  ; /* 0x4ec */
    U_PFMD_CUR_HIST116     PFMD_CUR_HIST116                  ; /* 0x4f0 */
    U_PFMD_CUR_HIST117     PFMD_CUR_HIST117                  ; /* 0x4f4 */
    U_PFMD_CUR_HIST118     PFMD_CUR_HIST118                  ; /* 0x4f8 */
    U_PFMD_CUR_HIST119     PFMD_CUR_HIST119                  ; /* 0x4fc */
    U_PFMD_CUR_HIST120     PFMD_CUR_HIST120                  ; /* 0x500 */
    U_PFMD_CUR_HIST121     PFMD_CUR_HIST121                  ; /* 0x504 */
    U_PFMD_CUR_HIST122     PFMD_CUR_HIST122                  ; /* 0x508 */
    U_PFMD_CUR_HIST123     PFMD_CUR_HIST123                  ; /* 0x50c */
    U_PFMD_CUR_HIST124     PFMD_CUR_HIST124                  ; /* 0x510 */
    U_PFMD_CUR_HIST125     PFMD_CUR_HIST125                  ; /* 0x514 */
    U_PFMD_CUR_HIST126     PFMD_CUR_HIST126                  ; /* 0x518 */
    U_PFMD_CUR_HIST127     PFMD_CUR_HIST127                  ; /* 0x51c */
    U_PFMD_COMB00          PFMD_COMB00                       ; /* 0x520 */
    U_PFMD_COMB01          PFMD_COMB01                       ; /* 0x524 */
    U_PFMD_COMB02          PFMD_COMB02                       ; /* 0x528 */
    U_PFMD_COMB03          PFMD_COMB03                       ; /* 0x52c */
    U_PFMD_COMB04          PFMD_COMB04                       ; /* 0x530 */
    U_PFMD_COMB05          PFMD_COMB05                       ; /* 0x534 */
    U_PFMD_COMB06          PFMD_COMB06                       ; /* 0x538 */
    U_PFMD_COMB07          PFMD_COMB07                       ; /* 0x53c */
    U_PFMD_COMB08          PFMD_COMB08                       ; /* 0x540 */
    U_PFMD_COMB09          PFMD_COMB09                       ; /* 0x544 */
    U_PFMD_COMB10          PFMD_COMB10                       ; /* 0x548 */
    U_PFMD_COMB11          PFMD_COMB11                       ; /* 0x54c */
    U_PFMD_COMB12          PFMD_COMB12                       ; /* 0x550 */
    U_PFMD_COMB13          PFMD_COMB13                       ; /* 0x554 */
    U_PFMD_COMB14          PFMD_COMB14                       ; /* 0x558 */
    U_PFMD_COMB15          PFMD_COMB15                       ; /* 0x55c */
    U_PFMD_COMB16          PFMD_COMB16                       ; /* 0x560 */
    U_PFMD_COMB17          PFMD_COMB17                       ; /* 0x564 */
    U_PFMD_COMB18          PFMD_COMB18                       ; /* 0x568 */
    U_PFMD_COMB19          PFMD_COMB19                       ; /* 0x56c */
    U_PFMD_COMB20          PFMD_COMB20                       ; /* 0x570 */
    U_PFMD_COMB21          PFMD_COMB21                       ; /* 0x574 */
    U_PFMD_COMB22          PFMD_COMB22                       ; /* 0x578 */
    U_PFMD_COMB23          PFMD_COMB23                       ; /* 0x57c */
    U_PFMD_COMB24          PFMD_COMB24                       ; /* 0x580 */
    U_PFMD_COMB25          PFMD_COMB25                       ; /* 0x584 */
    U_PFMD_COMB26          PFMD_COMB26                       ; /* 0x588 */
    U_PFMD_COMB27          PFMD_COMB27                       ; /* 0x58c */
    U_PFMD_COMB28          PFMD_COMB28                       ; /* 0x590 */
    U_PFMD_COMB29          PFMD_COMB29                       ; /* 0x594 */
    U_PFMD_COMB30          PFMD_COMB30                       ; /* 0x598 */
    U_PFMD_COMB31          PFMD_COMB31                       ; /* 0x59c */
    U_PFMD_CHD000          PFMD_CHD000                       ; /* 0x5a0 */
    U_PFMD_CHD001          PFMD_CHD001                       ; /* 0x5a4 */
    U_PFMD_CHD002          PFMD_CHD002                       ; /* 0x5a8 */
    U_PFMD_CHD003          PFMD_CHD003                       ; /* 0x5ac */
    U_PFMD_CHD004          PFMD_CHD004                       ; /* 0x5b0 */
    U_PFMD_CHD005          PFMD_CHD005                       ; /* 0x5b4 */
    U_PFMD_CHD006          PFMD_CHD006                       ; /* 0x5b8 */
    U_PFMD_CHD007          PFMD_CHD007                       ; /* 0x5bc */
    U_PFMD_CHD008          PFMD_CHD008                       ; /* 0x5c0 */
    U_PFMD_CHD009          PFMD_CHD009                       ; /* 0x5c4 */
    U_PFMD_CHD010          PFMD_CHD010                       ; /* 0x5c8 */
    U_PFMD_CHD011          PFMD_CHD011                       ; /* 0x5cc */
    U_PFMD_CHD012          PFMD_CHD012                       ; /* 0x5d0 */
    U_PFMD_CHD013          PFMD_CHD013                       ; /* 0x5d4 */
    U_PFMD_CHD014          PFMD_CHD014                       ; /* 0x5d8 */
    U_PFMD_CHD015          PFMD_CHD015                       ; /* 0x5dc */
    U_PFMD_CHD016          PFMD_CHD016                       ; /* 0x5e0 */
    U_PFMD_CHD017          PFMD_CHD017                       ; /* 0x5e4 */
    U_PFMD_CHD018          PFMD_CHD018                       ; /* 0x5e8 */
    U_PFMD_CHD019          PFMD_CHD019                       ; /* 0x5ec */
    U_PFMD_CHD020          PFMD_CHD020                       ; /* 0x5f0 */
    U_PFMD_CHD021          PFMD_CHD021                       ; /* 0x5f4 */
    U_PFMD_CHD022          PFMD_CHD022                       ; /* 0x5f8 */
    U_PFMD_CHD023          PFMD_CHD023                       ; /* 0x5fc */
    U_PFMD_CHD024          PFMD_CHD024                       ; /* 0x600 */
    U_PFMD_CHD025          PFMD_CHD025                       ; /* 0x604 */
    U_PFMD_CHD026          PFMD_CHD026                       ; /* 0x608 */
    U_PFMD_CHD027          PFMD_CHD027                       ; /* 0x60c */
    U_PFMD_CHD028          PFMD_CHD028                       ; /* 0x610 */
    U_PFMD_CHD029          PFMD_CHD029                       ; /* 0x614 */
    U_PFMD_CHD030          PFMD_CHD030                       ; /* 0x618 */
    U_PFMD_CHD031          PFMD_CHD031                       ; /* 0x61c */
    U_PFMD_CHD032          PFMD_CHD032                       ; /* 0x620 */
    U_PFMD_CHD033          PFMD_CHD033                       ; /* 0x624 */
    U_PFMD_CHD034          PFMD_CHD034                       ; /* 0x628 */
    U_PFMD_CHD035          PFMD_CHD035                       ; /* 0x62c */
    U_PFMD_CHD036          PFMD_CHD036                       ; /* 0x630 */
    U_PFMD_CHD037          PFMD_CHD037                       ; /* 0x634 */
    U_PFMD_CHD038          PFMD_CHD038                       ; /* 0x638 */
    U_PFMD_CHD039          PFMD_CHD039                       ; /* 0x63c */
    U_PFMD_CHD040          PFMD_CHD040                       ; /* 0x640 */
    U_PFMD_CHD041          PFMD_CHD041                       ; /* 0x644 */
    U_PFMD_CHD042          PFMD_CHD042                       ; /* 0x648 */
    U_PFMD_CHD043          PFMD_CHD043                       ; /* 0x64c */
    U_PFMD_CHD044          PFMD_CHD044                       ; /* 0x650 */
    U_PFMD_CHD045          PFMD_CHD045                       ; /* 0x654 */
    U_PFMD_CHD046          PFMD_CHD046                       ; /* 0x658 */
    U_PFMD_CHD047          PFMD_CHD047                       ; /* 0x65c */
    U_PFMD_CHD048          PFMD_CHD048                       ; /* 0x660 */
    U_PFMD_CHD049          PFMD_CHD049                       ; /* 0x664 */
    U_PFMD_CHD050          PFMD_CHD050                       ; /* 0x668 */
    U_PFMD_CHD051          PFMD_CHD051                       ; /* 0x66c */
    U_PFMD_CHD052          PFMD_CHD052                       ; /* 0x670 */
    U_PFMD_CHD053          PFMD_CHD053                       ; /* 0x674 */
    U_PFMD_CHD054          PFMD_CHD054                       ; /* 0x678 */
    U_PFMD_CHD055          PFMD_CHD055                       ; /* 0x67c */
    U_PFMD_CHD056          PFMD_CHD056                       ; /* 0x680 */
    U_PFMD_CHD057          PFMD_CHD057                       ; /* 0x684 */
    U_PFMD_CHD058          PFMD_CHD058                       ; /* 0x688 */
    U_PFMD_CHD059          PFMD_CHD059                       ; /* 0x68c */
    U_PFMD_CHD060          PFMD_CHD060                       ; /* 0x690 */
    U_PFMD_CHD061          PFMD_CHD061                       ; /* 0x694 */
    U_PFMD_CHD062          PFMD_CHD062                       ; /* 0x698 */
    U_PFMD_CHD063          PFMD_CHD063                       ; /* 0x69c */
    U_PFMD_CHD064          PFMD_CHD064                       ; /* 0x6a0 */
    U_PFMD_CHD065          PFMD_CHD065                       ; /* 0x6a4 */
    U_PFMD_CHD066          PFMD_CHD066                       ; /* 0x6a8 */
    U_PFMD_CHD067          PFMD_CHD067                       ; /* 0x6ac */
    U_PFMD_CHD068          PFMD_CHD068                       ; /* 0x6b0 */
    U_PFMD_CHD069          PFMD_CHD069                       ; /* 0x6b4 */
    U_PFMD_CHD070          PFMD_CHD070                       ; /* 0x6b8 */
    U_PFMD_CHD071          PFMD_CHD071                       ; /* 0x6bc */
    U_PFMD_CHD072          PFMD_CHD072                       ; /* 0x6c0 */
    U_PFMD_CHD073          PFMD_CHD073                       ; /* 0x6c4 */
    U_PFMD_CHD074          PFMD_CHD074                       ; /* 0x6c8 */
    U_PFMD_CHD075          PFMD_CHD075                       ; /* 0x6cc */
    U_PFMD_CHD076          PFMD_CHD076                       ; /* 0x6d0 */
    U_PFMD_CHD077          PFMD_CHD077                       ; /* 0x6d4 */
    U_PFMD_CHD078          PFMD_CHD078                       ; /* 0x6d8 */
    U_PFMD_CHD079          PFMD_CHD079                       ; /* 0x6dc */
    U_PFMD_CHD080          PFMD_CHD080                       ; /* 0x6e0 */
    U_PFMD_CHD081          PFMD_CHD081                       ; /* 0x6e4 */
    U_PFMD_CHD082          PFMD_CHD082                       ; /* 0x6e8 */
    U_PFMD_CHD083          PFMD_CHD083                       ; /* 0x6ec */
    U_PFMD_CHD084          PFMD_CHD084                       ; /* 0x6f0 */
    U_PFMD_CHD085          PFMD_CHD085                       ; /* 0x6f4 */
    U_PFMD_CHD086          PFMD_CHD086                       ; /* 0x6f8 */
    U_PFMD_CHD087          PFMD_CHD087                       ; /* 0x6fc */
    U_PFMD_CHD088          PFMD_CHD088                       ; /* 0x700 */
    U_PFMD_CHD089          PFMD_CHD089                       ; /* 0x704 */
    U_PFMD_CHD090          PFMD_CHD090                       ; /* 0x708 */
    U_PFMD_CHD091          PFMD_CHD091                       ; /* 0x70c */
    U_PFMD_CHD092          PFMD_CHD092                       ; /* 0x710 */
    U_PFMD_CHD093          PFMD_CHD093                       ; /* 0x714 */
    U_PFMD_CHD094          PFMD_CHD094                       ; /* 0x718 */
    U_PFMD_CHD095          PFMD_CHD095                       ; /* 0x71c */
    U_PFMD_CHD096          PFMD_CHD096                       ; /* 0x720 */
    U_PFMD_CHD097          PFMD_CHD097                       ; /* 0x724 */
    U_PFMD_CHD098          PFMD_CHD098                       ; /* 0x728 */
    U_PFMD_CHD099          PFMD_CHD099                       ; /* 0x72c */
    U_PFMD_CHD100          PFMD_CHD100                       ; /* 0x730 */
    U_PFMD_CHD101          PFMD_CHD101                       ; /* 0x734 */
    U_PFMD_CHD102          PFMD_CHD102                       ; /* 0x738 */
    U_PFMD_CHD103          PFMD_CHD103                       ; /* 0x73c */
    U_PFMD_CHD104          PFMD_CHD104                       ; /* 0x740 */
    U_PFMD_CHD105          PFMD_CHD105                       ; /* 0x744 */
    U_PFMD_CHD106          PFMD_CHD106                       ; /* 0x748 */
    U_PFMD_CHD107          PFMD_CHD107                       ; /* 0x74c */
    U_PFMD_CHD108          PFMD_CHD108                       ; /* 0x750 */
    U_PFMD_CHD109          PFMD_CHD109                       ; /* 0x754 */
    U_PFMD_CHD110          PFMD_CHD110                       ; /* 0x758 */
    U_PFMD_CHD111          PFMD_CHD111                       ; /* 0x75c */
    U_PFMD_CHD112          PFMD_CHD112                       ; /* 0x760 */
    U_PFMD_CHD113          PFMD_CHD113                       ; /* 0x764 */
    U_PFMD_CHD114          PFMD_CHD114                       ; /* 0x768 */
    U_PFMD_CHD115          PFMD_CHD115                       ; /* 0x76c */
    U_PFMD_CHD116          PFMD_CHD116                       ; /* 0x770 */
    U_PFMD_CHD117          PFMD_CHD117                       ; /* 0x774 */
    U_PFMD_CHD118          PFMD_CHD118                       ; /* 0x778 */
    U_PFMD_CHD119          PFMD_CHD119                       ; /* 0x77c */
    U_PFMD_CHD120          PFMD_CHD120                       ; /* 0x780 */
    U_PFMD_CHD121          PFMD_CHD121                       ; /* 0x784 */
    U_PFMD_CHD122          PFMD_CHD122                       ; /* 0x788 */
    U_PFMD_CHD123          PFMD_CHD123                       ; /* 0x78c */
    U_PFMD_CHD124          PFMD_CHD124                       ; /* 0x790 */
    U_PFMD_CHD125          PFMD_CHD125                       ; /* 0x794 */
    U_PFMD_CHD126          PFMD_CHD126                       ; /* 0x798 */
    U_PFMD_CHD127          PFMD_CHD127                       ; /* 0x79c */
    U_PFMD_MODE00_COMBVARY_0   PFMD_MODE00_COMBVARY_0        ; /* 0x7a0 */
    U_PFMD_MODE00_COMBVARY_1   PFMD_MODE00_COMBVARY_1        ; /* 0x7a4 */
    U_PFMD_MODE01_COMBVARY_0   PFMD_MODE01_COMBVARY_0        ; /* 0x7a8 */
    U_PFMD_MODE01_COMBVARY_1   PFMD_MODE01_COMBVARY_1        ; /* 0x7ac */
    U_PFMD_MODE02_COMBVARY_0   PFMD_MODE02_COMBVARY_0        ; /* 0x7b0 */
    U_PFMD_MODE02_COMBVARY_1   PFMD_MODE02_COMBVARY_1        ; /* 0x7b4 */
    U_PFMD_MODE03_COMBVARY_0   PFMD_MODE03_COMBVARY_0        ; /* 0x7b8 */
    U_PFMD_MODE03_COMBVARY_1   PFMD_MODE03_COMBVARY_1        ; /* 0x7bc */
    U_PFMD_MODE04_COMBVARY_0   PFMD_MODE04_COMBVARY_0        ; /* 0x7c0 */
    U_PFMD_MODE04_COMBVARY_1   PFMD_MODE04_COMBVARY_1        ; /* 0x7c4 */
    U_PFMD_MODE05_COMBVARY_0   PFMD_MODE05_COMBVARY_0        ; /* 0x7c8 */
    U_PFMD_MODE05_COMBVARY_1   PFMD_MODE05_COMBVARY_1        ; /* 0x7cc */
    U_PFMD_MODE06_COMBVARY_0   PFMD_MODE06_COMBVARY_0        ; /* 0x7d0 */
    U_PFMD_MODE06_COMBVARY_1   PFMD_MODE06_COMBVARY_1        ; /* 0x7d4 */
    U_PFMD_MODE07_COMBVARY_0   PFMD_MODE07_COMBVARY_0        ; /* 0x7d8 */
    U_PFMD_MODE07_COMBVARY_1   PFMD_MODE07_COMBVARY_1        ; /* 0x7dc */
    U_PFMD_MODE08_COMBVARY_0   PFMD_MODE08_COMBVARY_0        ; /* 0x7e0 */
    U_PFMD_MODE08_COMBVARY_1   PFMD_MODE08_COMBVARY_1        ; /* 0x7e4 */
    U_PFMD_MODE09_COMBVARY_0   PFMD_MODE09_COMBVARY_0        ; /* 0x7e8 */
    U_PFMD_MODE09_COMBVARY_1   PFMD_MODE09_COMBVARY_1        ; /* 0x7ec */
    U_PFMD_MODE10_COMBVARY_0   PFMD_MODE10_COMBVARY_0        ; /* 0x7f0 */
    U_PFMD_MODE10_COMBVARY_1   PFMD_MODE10_COMBVARY_1        ; /* 0x7f4 */
    U_PFMD_MODE11_COMBVARY_0   PFMD_MODE11_COMBVARY_0        ; /* 0x7f8 */
    U_PFMD_MODE11_COMBVARY_1   PFMD_MODE11_COMBVARY_1        ; /* 0x7fc */
    U_PFMD_MODE12_COMBVARY_0   PFMD_MODE12_COMBVARY_0        ; /* 0x800 */
    U_PFMD_MODE12_COMBVARY_1   PFMD_MODE12_COMBVARY_1        ; /* 0x804 */
    U_PFMD_RESERVE0        PFMD_RESERVE0                     ; /* 0x808 */
    U_PFMD_RESERVE1        PFMD_RESERVE1                     ; /* 0x80c */
    U_PFMD_PRECOMBHISTORYTHD00   PFMD_PRECOMBHISTORYTHD00    ; /* 0x810 */
    U_PFMD_PRECOMBHISTORYTHD01   PFMD_PRECOMBHISTORYTHD01    ; /* 0x814 */
    U_PFMD_PRECOMBHISTORYTHD02   PFMD_PRECOMBHISTORYTHD02    ; /* 0x818 */
    U_PFMD_PRECOMBHISTORYTHD03   PFMD_PRECOMBHISTORYTHD03    ; /* 0x81c */
    U_PFMD_PRECOMBHISTORYTHD04   PFMD_PRECOMBHISTORYTHD04    ; /* 0x820 */
    U_PFMD_PRECOMBHISTORYTHD05   PFMD_PRECOMBHISTORYTHD05    ; /* 0x824 */
    U_PFMD_PRECOMBHISTORYTHD06   PFMD_PRECOMBHISTORYTHD06    ; /* 0x828 */
    U_PFMD_PRECOMBHISTORYTHD07   PFMD_PRECOMBHISTORYTHD07    ; /* 0x82c */
    U_PFMD_PRECOMBHISTORYTHD08   PFMD_PRECOMBHISTORYTHD08    ; /* 0x830 */
    U_PFMD_PRECOMBHISTORYTHD09   PFMD_PRECOMBHISTORYTHD09    ; /* 0x834 */
    U_PFMD_PRECOMBHISTORYTHD10   PFMD_PRECOMBHISTORYTHD10    ; /* 0x838 */
    U_PFMD_PRECOMBHISTORYTHD11   PFMD_PRECOMBHISTORYTHD11    ; /* 0x83c */
    U_PFMD_PRECOMBHISTORYTHD12   PFMD_PRECOMBHISTORYTHD12    ; /* 0x840 */
    U_PFMD_RESERVE2        PFMD_RESERVE2                     ; /* 0x844 */
    U_PFMD_RESERVE3        PFMD_RESERVE3                     ; /* 0x848 */
    U_PFMD_RESERVE4        PFMD_RESERVE4                     ; /* 0x84c */
    U_PFMD_CVSCDCOUNTER00   PFMD_CVSCDCOUNTER00              ; /* 0x850 */
    U_PFMD_CVSCDCOUNTER01   PFMD_CVSCDCOUNTER01              ; /* 0x854 */
    U_PFMD_CVSCDCOUNTER02   PFMD_CVSCDCOUNTER02              ; /* 0x858 */
    U_PFMD_CVSCDCOUNTER03   PFMD_CVSCDCOUNTER03              ; /* 0x85c */
    U_PFMD_CVSCDCOUNTER04   PFMD_CVSCDCOUNTER04              ; /* 0x860 */
    U_PFMD_CVSCDCOUNTER05   PFMD_CVSCDCOUNTER05              ; /* 0x864 */
    U_PFMD_CVSCDCOUNTER06   PFMD_CVSCDCOUNTER06              ; /* 0x868 */
    U_PFMD_CVSCDCOUNTER07   PFMD_CVSCDCOUNTER07              ; /* 0x86c */
    U_PFMD_CVSCDCOUNTER08   PFMD_CVSCDCOUNTER08              ; /* 0x870 */
    U_PFMD_CVSCDCOUNTER09   PFMD_CVSCDCOUNTER09              ; /* 0x874 */
    U_PFMD_CVSCDCOUNTER10   PFMD_CVSCDCOUNTER10              ; /* 0x878 */
    U_PFMD_CVSCDCOUNTER11   PFMD_CVSCDCOUNTER11              ; /* 0x87c */
    U_PFMD_CVSCDCOUNTER12   PFMD_CVSCDCOUNTER12              ; /* 0x880 */
    U_PFMD_RESERVE5        PFMD_RESERVE5                     ; /* 0x884 */
    U_PFMD_RESERVE6        PFMD_RESERVE6                     ; /* 0x888 */
    U_PFMD_RESERVE7        PFMD_RESERVE7                     ; /* 0x88c */
    U_PFMD_SCDCOUNTER      PFMD_SCDCOUNTER                   ; /* 0x890 */
    U_PFMD_RESERVE8        PFMD_RESERVE8                     ; /* 0x894 */
    U_PFMD_RESERVE9        PFMD_RESERVE9                     ; /* 0x898 */
    U_PFMD_RESERVE10       PFMD_RESERVE10                    ; /* 0x89c */
    U_PFMD_COMBWSIGMAOSD   PFMD_COMBWSIGMAOSD                ; /* 0x8a0 */
    U_PFMD_COMBWSIGMA      PFMD_COMBWSIGMA                   ; /* 0x8a4 */
    U_PFMD_COMBOSD         PFMD_COMBOSD                      ; /* 0x8a8 */
    U_PFMD_COMB            PFMD_COMB                         ; /* 0x8ac */
    U_PFMD_TOTAL_OSD_PIX_NUM   PFMD_TOTAL_OSD_PIX_NUM        ; /* 0x8b0 */
    U_PFMD_SCD_FLAG        PFMD_SCD_FLAG                     ; /* 0x8b4 */
    U_PFMD_MAX_CV_OUTPUT_0   PFMD_MAX_CV_OUTPUT_0            ; /* 0x8b8 */
    U_PFMD_MAX_CV_OUTPUT_1   PFMD_MAX_CV_OUTPUT_1            ; /* 0x8bc */
    U_PFMD_MAX_CV_OUTPUT_2   PFMD_MAX_CV_OUTPUT_2            ; /* 0x8c0 */
    U_PFMD_MAX_CV_OUTPUT_3   PFMD_MAX_CV_OUTPUT_3            ; /* 0x8c4 */
    U_PFMD_MAX_CV_OUTPUT_4   PFMD_MAX_CV_OUTPUT_4            ; /* 0x8c8 */
    U_PFMD_MAX_CV_PHASE_OUTPUT_0   PFMD_MAX_CV_PHASE_OUTPUT_0 ; /* 0x8cc */
    U_PFMD_MAX_CV_PHASE_OUTPUT_1   PFMD_MAX_CV_PHASE_OUTPUT_1 ; /* 0x8d0 */
    U_PFMD_MAX_CV_PHASE_OUTPUT_2   PFMD_MAX_CV_PHASE_OUTPUT_2 ; /* 0x8d4 */
    U_PFMD_SEC_CV_OUTPUT_0   PFMD_SEC_CV_OUTPUT_0            ; /* 0x8d8 */
    U_PFMD_SEC_CV_OUTPUT_1   PFMD_SEC_CV_OUTPUT_1            ; /* 0x8dc */
    U_PFMD_SEC_CV_OUTPUT_2   PFMD_SEC_CV_OUTPUT_2            ; /* 0x8e0 */
    U_PFMD_SEC_CV_OUTPUT_3   PFMD_SEC_CV_OUTPUT_3            ; /* 0x8e4 */
    U_PFMD_SEC_CV_OUTPUT_4   PFMD_SEC_CV_OUTPUT_4            ; /* 0x8e8 */
    U_PFMD_SEC_CV_PHASE_OUTPUT_0   PFMD_SEC_CV_PHASE_OUTPUT_0 ; /* 0x8ec */
    U_PFMD_SEC_CV_PHASE_OUTPUT_1   PFMD_SEC_CV_PHASE_OUTPUT_1 ; /* 0x8f0 */
    U_PFMD_SEC_CV_PHASE_OUTPUT_2   PFMD_SEC_CV_PHASE_OUTPUT_2 ; /* 0x8f4 */
    U_PFMD_MAX_CB_OUTPUT_0   PFMD_MAX_CB_OUTPUT_0            ; /* 0x8f8 */
    U_PFMD_MAX_CB_OUTPUT_1   PFMD_MAX_CB_OUTPUT_1            ; /* 0x8fc */
    U_PFMD_MAX_CB_OUTPUT_2   PFMD_MAX_CB_OUTPUT_2            ; /* 0x900 */
    U_PFMD_MAX_CB_OUTPUT_3   PFMD_MAX_CB_OUTPUT_3            ; /* 0x904 */
    U_PFMD_MAX_CB_OUTPUT_4   PFMD_MAX_CB_OUTPUT_4            ; /* 0x908 */
    U_PFMD_MAX_CB_PHASE_OUTPUT_0   PFMD_MAX_CB_PHASE_OUTPUT_0 ; /* 0x90c */
    U_PFMD_MAX_CB_PHASE_OUTPUT_1   PFMD_MAX_CB_PHASE_OUTPUT_1 ; /* 0x910 */
    U_PFMD_RESERVE11       PFMD_RESERVE11                    ; /* 0x914 */
    U_PFMD_RESERVE12       PFMD_RESERVE12                    ; /* 0x918 */
    U_PFMD_RESERVE13       PFMD_RESERVE13                    ; /* 0x91c */
    HI_U32                 u32FilmType                       ;

} S_STT_REGS_TYPE;
#endif
/* Declare the struct pointor of the module MODULE_NAME */



#endif /* __C_UNION_DEFINE_H__ */
