/*******************************************************************
 * File Name:       codec_muv2_if.h
 * Authors:         benqiang
 * Data:            2016.07.06
 * Copyright:       tongtuic technology
 * Description:     video encoder interface
 *
 *******************************************************************/
#ifndef _TTV_CODEC_MUV2_PARM_H_
#define _TTV_CODEC_MUV2_PARM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hi_type.h"

typedef struct
{
    HI_S32 rm_dbg_en;                  //1: rm debug enable     0: rm debug unable

    //
    HI_S32 is_lossless;                //1: is lossless compress                   0:is lossy compress
    HI_S32 cmp_mode;                   //1: is raw frame compress mode             0: is not ...
    HI_S32 part_cmp_en;                //0: compress total frame                   1: compress partial frame
    HI_S32 source_mode;                //4: rgb888, 6: rgbw£»

    HI_S32 frame_width;                //input frame width
    HI_S32 frame_height;               //input frame height
    HI_S32 pcmp_start_hpos;            //start horizontal position of partial cmp
    HI_S32 pcmp_end_hpos;              //end horizontal position of partial cmp

    //
    HI_S32 budget_mb_bits;
    HI_S32 min_mb_bits;

    HI_S32 smth_thr;
    HI_S32 still_thr;
    HI_S32 big_grad_thr;
    HI_S32 diff_thr;
    HI_S32 smth_pix_num_thr;
    HI_S32 still_pix_num_thr;
    HI_S32 noise_pix_num_thr;
    HI_S32 grph_group_num_thr;

    HI_S32 qp_inc1_bits_thr;
    HI_S32 qp_inc2_bits_thr;
    HI_S32 qp_dec1_bits_thr;
    HI_S32 qp_dec2_bits_thr;

    HI_S32 raw_bits_penalty;
    HI_S32 grph_bits_penalty;

    HI_S32 buf_fullness_thr_reg0;
    HI_S32 buf_fullness_thr_reg1;
    HI_S32 buf_fullness_thr_reg2;
    HI_S32 qp_rge_reg0;
    HI_S32 qp_rge_reg1;
    HI_S32 qp_rge_reg2;
    HI_S32 bits_offset_reg0;
    HI_S32 bits_offset_reg1;
    HI_S32 bits_offset_reg2;

    HI_S32 grph_loss_thr;
    HI_S32 est_err_gain_map;
    HI_S32 buffer_init_bits;
    HI_S32 qp_force_en;
    HI_S32 coeff_skip_en;
    HI_S32 graphic_en;
    HI_S32 first_mb_adj_bits;
    HI_S32 first_row_adj_bits;
    HI_S32 smooth_status_thr;

} ODCMP_PARM_T;

typedef struct
{
    HI_S32    cmp_mode;                   //1: is raw frame compress mode             0: is not ...
    HI_S32    is_lossless;                //1: is lossless compress                   0:is lossy compress
    HI_S32    source_mode;                //4: rgb888, 6: rgbw£»
    HI_S32    frame_width;                //input frame width
    HI_S32    frame_height;               //input frame height

    //
    HI_S32    coeff_skip_en;
    HI_S32    bd_det_en;
    HI_S32    buffer_init_bits;
    HI_S32    buffer_fullness_thr;
    HI_S32    budget_mb_bits;

} ODDCMP_PARM_T;

#ifdef __cplusplus
}
#endif

#endif
