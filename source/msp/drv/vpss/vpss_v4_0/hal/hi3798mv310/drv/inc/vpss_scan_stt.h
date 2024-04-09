// ******************************************************************************
// Copyright     :  Copyright (C) 2017, Hisilicon Technologies Co. Ltd.
// File name     :  vpss_scan_stt.h
// Project line  :  Platform And Key Technologies Development
// Department    :  CAD Development Department
// Author        :  xxx
// Version       :  1.0
// Date          :  2013/3/10
// Description   :  The description of xxx project
// Others        :  Generated automatically by nManager V4.1
// History       :  xxx 2017/04/18 15:18:34 Create file
// ******************************************************************************

#ifndef __VPSS_SCAN_STT_H__
#define __VPSS_SCAN_STT_H__

/* Define the union U_VPSS_ME_GLBMV_HIST_0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    me_glbmv0_mvx         : 8   ; /* [7..0]  */
        unsigned int    me_glbmv0_mvy         : 7   ; /* [14..8]  */
        unsigned int    me_glbmv0_num         : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_ME_GLBMV_HIST_0;

/* Define the union U_VPSS_ME_GLBMV_HIST_1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    me_glbmv1_mvx         : 8   ; /* [7..0]  */
        unsigned int    me_glbmv1_mvy         : 7   ; /* [14..8]  */
        unsigned int    me_glbmv1_num         : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_ME_GLBMV_HIST_1;

/* Define the union U_VPSS_ME_GLBMV_HIST_2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    me_glbmv_goodmv_cnt   : 16  ; /* [15..0]  */
        unsigned int    blk_mv_hist_num_0     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_ME_GLBMV_HIST_2;

/* Define the union U_VPSS_ME_GLBMV_HIST_3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blk_mv_hist_num_1     : 16  ; /* [15..0]  */
        unsigned int    blk_mv_hist_num_2     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_ME_GLBMV_HIST_3;

/* Define the union U_VPSS_ME_GLBMV_HIST_4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    blk_mv_hist_num_3     : 16  ; /* [15..0]  */
        unsigned int    blk_mv_hist_num_4     : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_ME_GLBMV_HIST_4;

/* Define the union U_VPSS_ME_GLBMV_HIST_5 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_ME_GLBMV_HIST_5;
/* Define the union U_VPSS_ME_GLBMV_HIST_6 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_ME_GLBMV_HIST_6;
/* Define the union U_VPSS_ME_GLBMV_HIST_7 */
typedef union
{
    /* Define the struct bits  */
    struct
    {
        unsigned int reserved_0             : 32  ; /* [31..0]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_VPSS_ME_GLBMV_HIST_7;
//==============================================================================
/* Define the global struct */
typedef struct
{
    U_VPSS_ME_GLBMV_HIST_0   VPSS_ME_GLBMV_HIST_0            ; /* 0x0 */
    U_VPSS_ME_GLBMV_HIST_1   VPSS_ME_GLBMV_HIST_1            ; /* 0x4 */
    U_VPSS_ME_GLBMV_HIST_2   VPSS_ME_GLBMV_HIST_2            ; /* 0x8 */
    U_VPSS_ME_GLBMV_HIST_3   VPSS_ME_GLBMV_HIST_3            ; /* 0xc */
    U_VPSS_ME_GLBMV_HIST_4   VPSS_ME_GLBMV_HIST_4            ; /* 0x10 */
    U_VPSS_ME_GLBMV_HIST_5   VPSS_ME_GLBMV_HIST_5            ; /* 0x14 */
    U_VPSS_ME_GLBMV_HIST_6   VPSS_ME_GLBMV_HIST_6            ; /* 0x18 */
    U_VPSS_ME_GLBMV_HIST_7   VPSS_ME_GLBMV_HIST_7            ; /* 0x1c */

} S_VPSS_SCAN_STT_REGS_TYPE;

/* Declare the struct pointor of the module VPSS_SCAN_STT */
extern S_VPSS_SCAN_STT_REGS_TYPE *gopVPSS_SCAN_STTAllReg;


#endif /* __VPSS_SCAN_STT_H__ */
