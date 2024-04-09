#ifndef __HAL_IP_VPSS_WCHN_H__
#define __HAL_IP_VPSS_WCHN_H__

#include "vpss_define.h"
#include "hi_reg_common.h"

//-------------------------------------------------
// vpss mac wchn hal image
//-------------------------------------------------
HI_VOID VPSS_WCHN_SetEn              ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en            );
HI_VOID VPSS_WCHN_SetTunlEn          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 tunl_en       );
HI_VOID VPSS_WCHN_SetDBypass         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 d_bypass      );
HI_VOID VPSS_WCHN_SetHBypass         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 h_bypass      );
HI_VOID VPSS_WCHN_SetLmRmode         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 lm_rmode      );
HI_VOID VPSS_WCHN_SetDitherMode      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 dither_mode   );
HI_VOID VPSS_WCHN_SetDitherEn        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 dither_en     );
HI_VOID VPSS_WCHN_SetFlip            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 flip          );
HI_VOID VPSS_WCHN_SetMirror          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mirror        );
HI_VOID VPSS_WCHN_SetUvInvert        ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 uv_invert     );
HI_VOID VPSS_WCHN_SetCmpMode         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 cmp_mode      );
HI_VOID VPSS_WCHN_SetBitw            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 bitw          );
HI_VOID VPSS_WCHN_SetType            ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 type          );
HI_VOID VPSS_WCHN_SetVerOffset       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 ver_offset    );
HI_VOID VPSS_WCHN_SetHorOffset       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 hor_offset    );
HI_VOID VPSS_WCHN_SetYAddrL          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_addr_l      );
HI_VOID VPSS_WCHN_SetYAddrH          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_addr_h      );
HI_VOID VPSS_WCHN_SetCAddrL          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_addr_l      );
HI_VOID VPSS_WCHN_SetCAddrH          ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_addr_h      );
HI_VOID VPSS_WCHN_SetCStride         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_stride      );
HI_VOID VPSS_WCHN_SetYStride         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_stride      );
// HI_VOID VPSS_WCHN_SetYHeadAddrL      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_head_addr_l );
// HI_VOID VPSS_WCHN_SetYHeadAddrH      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_head_addr_h );
// HI_VOID VPSS_WCHN_SetCHeadAddrL      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_head_addr_l );
// HI_VOID VPSS_WCHN_SetCHeadAddrH      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_head_addr_h );
// HI_VOID VPSS_WCHN_SetCHeadStride     ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_head_stride );
// HI_VOID VPSS_WCHN_SetYHeadStride     ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_head_stride );
HI_VOID VPSS_WCHN_ENV_SetFormat      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 format        );
HI_VOID VPSS_WCHN_ENV_SetHeight      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 height        );
HI_VOID VPSS_WCHN_ENV_SetWidth       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 width         );
HI_VOID VPSS_WCHN_ENV_SetFinfoH      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 finfo_h       );
HI_VOID VPSS_WCHN_ENV_SetFinfoL      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 finfo_l       );

//-------------------------------------------------
// vpss mac wchn hal solo
//-------------------------------------------------
HI_VOID VPSS_WCHN_SOLO_SetEn         ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en            );
HI_VOID VPSS_WCHN_SOLO_SetTunlEn     ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 tunl_en       );
HI_VOID VPSS_WCHN_SOLO_SetDBypass    ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 d_bypass      );
HI_VOID VPSS_WCHN_SOLO_SetFlip       ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 flip          );
HI_VOID VPSS_WCHN_SOLO_SetMirror     ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mirror        );
HI_VOID VPSS_WCHN_SOLO_SetAddrH      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 addr_h        );
HI_VOID VPSS_WCHN_SOLO_SetAddrL      ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 addr_l        );
HI_VOID VPSS_WCHN_SOLO_SetStride     ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 stride        );
HI_VOID VPSS_WCHN_SOLO_ENV_SetHeight ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 height        );
HI_VOID VPSS_WCHN_SOLO_ENV_SetWidth  ( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 width         );

#endif

