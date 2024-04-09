/*******************************************************************
 * File Name:       ttv_enc_if.h
 * Authors:         benqiang
 * Data:            2014.03.07
 * Copyright:       tongtuic technology
 * Description:     video encoder interface
 *
 *******************************************************************/
#ifndef _TTV_CODEC_LCV2_CONFIG_H_
#define _TTV_CODEC_LCV2_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef struct
{
    int is_raw_cmp;                 //1: is raw frame compress mode             0: is not ...
    int is_lossless;                //1: is lossless compress                   0:is lossy compress

    int frm_width;                  //input frame width
    int frm_height;                 //input frame height
    int bit_dep;                    //pixel bit depth

    int is_stride_mem;              //pCmpData format in memory 1: stride          0: frame
    int stride;                     //pCmpData stride(unit is 128bit)

    /* register parameter of ratio control*/
    int budget_bit_mb_y;
    int pix_diff_thr;
    int smth_thr;
    int still_thr;
    int big_grad_thr;
    int smth_pix_num_thr;
    int still_pix_num_thr;
    int noise_pix_num_thr;
    int adj_sad_bit_thr;
    int qp_inc1_bits_thr;
    int qp_inc2_bits_thr;
    int qp_dec1_bits_thr;
    int qp_dec2_bits_thr;
    int max_qp;
    int sadbits_gain;                                               //3bits
    int rc_smth_ngain;      //3bits
    int max_trow_bits;
    int min_sad_thr;
    int max_sad_thr;
    int noise_sad;
    int min_mb_bits;
    int est_err_gain;
    int max_est_err_level;
    int vbv_buf_loss1_thr_y;
    int vbv_buf_loss2_thr_y;

    /* add for eda test */
    int cmp_ratio;
    int rc_type_mode;

} CMP_LCV2_PARM_T;

typedef struct
{
    int is_raw_cmp;                 //1: is raw frame compress mode             0: is not ...
    int is_lossless;                //1: is lossless compress                   0: is lossy compress

    int frm_width;                  //input frame width
    int frm_height;                 //input frame height
    int bit_dep;                    //pixel bit depth

    int is_stride_mem;              //pCmpData format in memory 1: stride          0: frame
    int stride;                     //pCmpData stride(unit is 128bit)

} DCMP_LCV2_PARM_T;

#ifdef __cplusplus
}
#endif

#endif
