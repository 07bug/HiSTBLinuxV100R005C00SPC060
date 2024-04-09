#ifndef __HAL_IP_VPSS_RCHN_H__
#define __HAL_IP_VPSS_RCHN_H__

#include "vpss_define.h"
#include "hi_reg_common.h"

//-------------------------------------------------
// vpss mac rchn hal image
//-------------------------------------------------
HI_VOID VPSS_RCHN_SetEn               ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en                );
HI_VOID VPSS_RCHN_SetTunlEn           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 tunl_en           );
HI_VOID VPSS_RCHN_SetMuteEn           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 test_en           );
HI_VOID VPSS_RCHN_SetDBypass          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 d_bypass          );
HI_VOID VPSS_RCHN_SetHBypass          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 h_bypass          );
HI_VOID VPSS_RCHN_Set2bBypass         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 b_bypass          );
HI_VOID VPSS_RCHN_SetLmRmode          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 lm_rmode          );
HI_VOID VPSS_RCHN_SetFlip             ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 flip              );
HI_VOID VPSS_RCHN_SetMirror           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mirror            );
HI_VOID VPSS_RCHN_SetUvInvert         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 uv_invert         );
HI_VOID VPSS_RCHN_SetDcmpMode         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 dcmp_mode         );
HI_VOID VPSS_RCHN_SetBitw             ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 bitw              );
HI_VOID VPSS_RCHN_SetOrder            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 order             );
HI_VOID VPSS_RCHN_SetType             ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 type              );
HI_VOID VPSS_RCHN_SetFormat           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 format            );
HI_VOID VPSS_RCHN_SetHeight           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 height            );
HI_VOID VPSS_RCHN_SetWidth            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 width             );
HI_VOID VPSS_RCHN_SetVerOffset        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 ver_offset        );
HI_VOID VPSS_RCHN_SetHorOffset        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 hor_offset        );
HI_VOID VPSS_RCHN_SetYAddrL           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_addr_l          );
HI_VOID VPSS_RCHN_SetYAddrH           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_addr_h          );
HI_VOID VPSS_RCHN_SetCAddrL           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_addr_l          );
HI_VOID VPSS_RCHN_SetCAddrH           ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_addr_h          );
HI_VOID VPSS_RCHN_SetCrAddrH          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 cr_addr_h         );
HI_VOID VPSS_RCHN_SetCrAddrL          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 cr_addr_l         );
HI_VOID VPSS_RCHN_SetYTopHeadAddrL    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_top_head_addr_l );
HI_VOID VPSS_RCHN_SetYTopHeadAddrH    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_top_head_addr_h );
HI_VOID VPSS_RCHN_SetCTopHeadAddrL    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_top_head_addr_l );
HI_VOID VPSS_RCHN_SetCTopHeadAddrH    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_top_head_addr_h );
HI_VOID VPSS_RCHN_SetYBotHeadAddrL    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_bot_head_addr_l );
HI_VOID VPSS_RCHN_SetYBotHeadAddrH    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_bot_head_addr_h );
HI_VOID VPSS_RCHN_SetCBotHeadAddrL    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_bot_head_addr_l );
HI_VOID VPSS_RCHN_SetCBotHeadAddrH    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_bot_head_addr_h );
HI_VOID VPSS_RCHN_SetCStride          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_stride          );
HI_VOID VPSS_RCHN_SetYStride          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_stride          );
HI_VOID VPSS_RCHN_SetCHeadStride      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_head_stride     );
HI_VOID VPSS_RCHN_SetYHeadStride      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_head_stride     );
HI_VOID VPSS_RCHN_SetY2bAddrL         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_2b_addr_l       );
HI_VOID VPSS_RCHN_SetY2bAddrH         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_2b_addr_h       );
HI_VOID VPSS_RCHN_SetC2bAddrL         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_2b_addr_l       );
HI_VOID VPSS_RCHN_SetC2bAddrH         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_2b_addr_h       );
HI_VOID VPSS_RCHN_SetC2bStride        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_2b_stride       );
HI_VOID VPSS_RCHN_SetY2bStride        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_2b_stride       );
HI_VOID VPSS_RCHN_SetCMuteVal         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_mute_val        );
HI_VOID VPSS_RCHN_SetYMuteVal         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_mute_val        );

//-------------------------------------------------
// vpss mac rchn hal solo
//-------------------------------------------------
HI_VOID VPSS_RCHN_SOLO_SetEn          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en                );
HI_VOID VPSS_RCHN_SOLO_SetEn1         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en1               );
HI_VOID VPSS_RCHN_SOLO_SetTunleEn     ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 tunl_en           );
HI_VOID VPSS_RCHN_SOLO_SetMuteEn      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 test_en           );
HI_VOID VPSS_RCHN_SOLO_SetDBypass     ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 d_bypass          );
HI_VOID VPSS_RCHN_SOLO_SetFlip        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 flip              );
HI_VOID VPSS_RCHN_SOLO_SetMirror      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mirror            );
HI_VOID VPSS_RCHN_SOLO_SetHeight      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 height            );
HI_VOID VPSS_RCHN_SOLO_SetWidth       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 width             );
HI_VOID VPSS_RCHN_SOLO_SetAddrH       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 addr_h            );
HI_VOID VPSS_RCHN_SOLO_SetAddrL       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 addr_l            );
HI_VOID VPSS_RCHN_SOLO_SetStride      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 stride            );
HI_VOID VPSS_RCHN_SOLO_SetMuteVal0    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mute_val0         );
HI_VOID VPSS_RCHN_SOLO_SetMuteVal1    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mute_val1         );

#endif

