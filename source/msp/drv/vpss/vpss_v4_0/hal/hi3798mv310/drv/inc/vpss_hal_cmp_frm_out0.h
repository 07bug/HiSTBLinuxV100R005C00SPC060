#ifndef __VPSS_HAL_CMP_FRM_OUT0_H__
#define __VPSS_HAL_CMP_FRM_OUT0_H__

#include "hi_reg_common.h"
#include "vpss_define.h"

HI_VOID VPSS_MAC_SetOut0SliceCmpEn           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_slice_cmp_en);
HI_VOID VPSS_MAC_SetOut0QpForceEn            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_qp_force_en);
HI_VOID VPSS_MAC_SetOut0GrphEn               ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_grph_en);
HI_VOID VPSS_MAC_SetOut0PartCmpEn            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_part_cmp_en);
HI_VOID VPSS_MAC_SetOut0PixelFormat          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_pixel_format);
HI_VOID VPSS_MAC_SetOut0FrameBitdepth        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_frame_bitdepth);
HI_VOID VPSS_MAC_SetOut0CmpMode              ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_cmp_mode);
HI_VOID VPSS_MAC_SetOut0IsLossless           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_is_lossless);
HI_VOID VPSS_MAC_SetOut0CmpEn                ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_cmp_en);
HI_VOID VPSS_MAC_SetOut0FrameHeight          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_frame_height);
HI_VOID VPSS_MAC_SetOut0FrameWidth           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_frame_width);
HI_VOID VPSS_MAC_SetOut0PcmpEndHpos          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_pcmp_end_hpos);
HI_VOID VPSS_MAC_SetOut0PcmpStartHpos        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_pcmp_start_hpos);
HI_VOID VPSS_MAC_SetOut0MinMbBits            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_min_mb_bits);
HI_VOID VPSS_MAC_SetOut0MbBits               ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_mb_bits);
HI_VOID VPSS_MAC_SetOut0FirstColAdjBits      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_first_col_adj_bits);
HI_VOID VPSS_MAC_SetOut0FirstRowAdjBits      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_first_row_adj_bits);
HI_VOID VPSS_MAC_SetOut0SmoothStatusThr      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_smooth_status_thr);
HI_VOID VPSS_MAC_SetOut0FirstMbAdjBits       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_first_mb_adj_bits);
HI_VOID VPSS_MAC_SetOut0DiffThr              ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_diff_thr);
HI_VOID VPSS_MAC_SetOut0BigGradThr           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_big_grad_thr);
HI_VOID VPSS_MAC_SetOut0StillThr             ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_still_thr);
HI_VOID VPSS_MAC_SetOut0SmthThr              ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_smth_thr);
HI_VOID VPSS_MAC_SetOut0NoisePixNumThr       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_noise_pix_num_thr);
HI_VOID VPSS_MAC_SetOut0StillPixNumThr       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_still_pix_num_thr);
HI_VOID VPSS_MAC_SetOut0SmthPixNumThr        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_smth_pix_num_thr);
HI_VOID VPSS_MAC_SetOut0QpDec2BitsThr        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_qp_dec2_bits_thr);
HI_VOID VPSS_MAC_SetOut0QpDec1BitsThr        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_qp_dec1_bits_thr);
HI_VOID VPSS_MAC_SetOut0QpInc2BitsThr        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_qp_inc2_bits_thr);
HI_VOID VPSS_MAC_SetOut0QpInc1BitsThr        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_qp_inc1_bits_thr);
HI_VOID VPSS_MAC_SetOut0GrphBitsPenalty      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_grph_bits_penalty);
HI_VOID VPSS_MAC_SetOut0BufFullnessThrReg0   ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_buf_fullness_thr_reg0);
HI_VOID VPSS_MAC_SetOut0BufFullnessThrReg1   ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_buf_fullness_thr_reg1);
HI_VOID VPSS_MAC_SetOut0BufFullnessThrReg2   ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_buf_fullness_thr_reg2);
HI_VOID VPSS_MAC_SetOut0QpRgeReg0            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_qp_rge_reg0);
HI_VOID VPSS_MAC_SetOut0QpRgeReg1            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_qp_rge_reg1);
HI_VOID VPSS_MAC_SetOut0QpRgeReg2            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_qp_rge_reg2);
HI_VOID VPSS_MAC_SetOut0BitsOffsetReg0       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_bits_offset_reg0);
HI_VOID VPSS_MAC_SetOut0BitsOffsetReg1       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_bits_offset_reg1);
HI_VOID VPSS_MAC_SetOut0BitsOffsetReg2       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_bits_offset_reg2);
HI_VOID VPSS_MAC_SetOut0GrphIdealBitsC       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_grph_ideal_bits_c);
HI_VOID VPSS_MAC_SetOut0GrphIdealBitsY       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_grph_ideal_bits_y);
HI_VOID VPSS_MAC_SetOut0EstErrGainMap        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_est_err_gain_map);
HI_VOID VPSS_MAC_SetOut0BufferInitBits       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_buffer_init_bits);
HI_VOID VPSS_MAC_SetOut0SpecialStatusThr     ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_special_status_thr);
HI_VOID VPSS_MAC_SetOut0NoiseStatusThr       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_noise_status_thr);
HI_VOID VPSS_MAC_SetOut0LowStatusThr         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_low_status_thr);
HI_VOID VPSS_MAC_SetOut0PreNoiseMbThr1       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_pre_noise_mb_thr1);
HI_VOID VPSS_MAC_SetOut0PreNoiseMbThr0       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_pre_noise_mb_thr0);
HI_VOID VPSS_MAC_SetOut0NoiseQpIncBitsThr    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_noise_qp_inc_bits_thr);
HI_VOID VPSS_MAC_SetOut0SpecialQpDecBitsThr  ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_special_qp_dec_bits_thr);
HI_VOID VPSS_MAC_SetOut0GrphPenaltyBitC      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_grph_penalty_bit_c);
HI_VOID VPSS_MAC_SetOut0SamllDiffThr         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_samll_diff_thr);
HI_VOID VPSS_MAC_SetOut0FrameSize            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_frame_size);
HI_VOID VPSS_MAC_SetOut0MaxLeftBitsBufferReg ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_max_left_bits_buffer_reg);
HI_VOID VPSS_MAC_SetOut0GlbSt                ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_glb_st);
HI_VOID VPSS_MAC_SetOut0Slice0Size           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_slice0_size);
HI_VOID VPSS_MAC_SetOut0Slice1Size           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_slice1_size);
HI_VOID VPSS_MAC_SetOut0Slice2Size           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 out0_slice2_size);

#endif


