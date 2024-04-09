#include "vpss_hal_comm.h"
#include "vpss_hal_ip_rchn.h"
#include "vpss_mac_define.h"
#include "vpss_cbb_reg.h"

// Base Image Reg Use: VPSS_CF_CTRL
// Base Solo  Reg Use: VPSS_NR_RMAD_CTRL

//-------------------------------------------------
// vpss mac rchn hal image
//-------------------------------------------------

HI_VOID VPSS_RCHN_SetEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.en = en;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetTunlEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 tunl_en)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.tunl_en = tunl_en;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetMuteEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mute_en)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.mute_en = mute_en;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetDBypass(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 d_bypass)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.d_bypass = d_bypass;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetHBypass(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 h_bypass)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.h_bypass = h_bypass;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_Set2bBypass(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 b_bypass)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.b_bypass = b_bypass;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetLmRmode(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 lm_rmode)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.lm_rmode = lm_rmode;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetFlip(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 flip)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.flip = flip;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetMirror(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mirror)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.mirror = mirror;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetUvInvert(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 uv_invert)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.uv_invert = uv_invert;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetDcmpMode(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 dcmp_mode)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.dcmp_mode = dcmp_mode;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetBitw(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 bitw)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.bitw = bitw;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetOrder(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 order)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.order = order;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetType(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 type)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.type = type;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetFormat(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 format)
{
    U_VPSS_BASE_RD_IMG_CTRL VPSS_BASE_RD_IMG_CTRL;

    VPSS_BASE_RD_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + offset));
    VPSS_BASE_RD_IMG_CTRL.bits.format = format;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + offset), VPSS_BASE_RD_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetHeight(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 height)
{
    U_VPSS_BASE_RD_IMG_SIZE VPSS_BASE_RD_IMG_SIZE;

    VPSS_BASE_RD_IMG_SIZE.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x2 + offset));
    VPSS_BASE_RD_IMG_SIZE.bits.height = height;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x2 + offset), VPSS_BASE_RD_IMG_SIZE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetWidth(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 width)
{
    U_VPSS_BASE_RD_IMG_SIZE VPSS_BASE_RD_IMG_SIZE;

    VPSS_BASE_RD_IMG_SIZE.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x2 + offset));
    VPSS_BASE_RD_IMG_SIZE.bits.width = width;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x2 + offset), VPSS_BASE_RD_IMG_SIZE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetVerOffset(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 ver_offset)
{
    U_VPSS_BASE_RD_IMG_OFFSET VPSS_BASE_RD_IMG_OFFSET;

    VPSS_BASE_RD_IMG_OFFSET.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x3 + offset));
    VPSS_BASE_RD_IMG_OFFSET.bits.ver_offset = ver_offset;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x3 + offset), VPSS_BASE_RD_IMG_OFFSET.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetHorOffset(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 hor_offset)
{
    U_VPSS_BASE_RD_IMG_OFFSET VPSS_BASE_RD_IMG_OFFSET;

    VPSS_BASE_RD_IMG_OFFSET.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x3 + offset));
    VPSS_BASE_RD_IMG_OFFSET.bits.hor_offset = hor_offset;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x3 + offset), VPSS_BASE_RD_IMG_OFFSET.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetYAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_addr_h)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x4 + offset), y_addr_h);

    return ;
}


HI_VOID VPSS_RCHN_SetYAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_addr_l)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x5 + offset), y_addr_l);

    return ;
}


HI_VOID VPSS_RCHN_SetCAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_addr_h)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x6 + offset), c_addr_h);

    return ;
}


HI_VOID VPSS_RCHN_SetCAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_addr_l)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x7 + offset), c_addr_l);

    return ;
}


HI_VOID VPSS_RCHN_SetCrAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 cr_addr_h)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x8 + offset), cr_addr_h);

    return ;
}


HI_VOID VPSS_RCHN_SetCrAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 cr_addr_l)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x9 + offset), cr_addr_l);

    return ;
}


HI_VOID VPSS_RCHN_SetYTopHeadAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_top_head_addr_h)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0xa + offset), y_top_head_addr_h);
    return ;
}


HI_VOID VPSS_RCHN_SetYTopHeadAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_top_head_addr_l)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0xb + offset), y_top_head_addr_l);
    return ;
}


HI_VOID VPSS_RCHN_SetCTopHeadAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_top_head_addr_h)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0xc + offset), c_top_head_addr_h);
    return ;
}


HI_VOID VPSS_RCHN_SetCTopHeadAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_top_head_addr_l)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0xd + offset), c_top_head_addr_l);
    return ;
}


HI_VOID VPSS_RCHN_SetYBotHeadAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_bot_head_addr_h)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0xe + offset), y_bot_head_addr_h);
    return ;
}


HI_VOID VPSS_RCHN_SetYBotHeadAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_bot_head_addr_l)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0xf + offset), y_bot_head_addr_l);
    return ;
}


HI_VOID VPSS_RCHN_SetCBotHeadAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_bot_head_addr_h)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x10 + offset), c_bot_head_addr_h);
    return ;
}


HI_VOID VPSS_RCHN_SetCBotHeadAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_bot_head_addr_l)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x11 + offset), c_bot_head_addr_l);
    return ;
}


HI_VOID VPSS_RCHN_SetY2bAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_2b_addr_h)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x14 + offset), y_2b_addr_h);
    return ;
}


HI_VOID VPSS_RCHN_SetY2bAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_2b_addr_l)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x15 + offset), y_2b_addr_l);
    return ;
}


HI_VOID VPSS_RCHN_SetC2bAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_2b_addr_h)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x16 + offset), c_2b_addr_h);
    return ;
}


HI_VOID VPSS_RCHN_SetC2bAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_2b_addr_l)
{
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x17 + offset), c_2b_addr_l);
    return ;
}


HI_VOID VPSS_RCHN_SetCStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_stride)
{
    U_VPSS_BASE_RD_IMG_STRIDE VPSS_BASE_RD_IMG_STRIDE;

    VPSS_BASE_RD_IMG_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x12 + offset));
    VPSS_BASE_RD_IMG_STRIDE.bits.c_stride = c_stride;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x12 + offset), VPSS_BASE_RD_IMG_STRIDE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetYStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_stride)
{
    U_VPSS_BASE_RD_IMG_STRIDE VPSS_BASE_RD_IMG_STRIDE;

    VPSS_BASE_RD_IMG_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x12 + offset));
    VPSS_BASE_RD_IMG_STRIDE.bits.y_stride = y_stride;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x12 + offset), VPSS_BASE_RD_IMG_STRIDE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetCHeadStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_head_stride)
{
    U_VPSS_BASE_RD_IMG_STRIDE VPSS_BASE_RD_IMG_STRIDE;

    VPSS_BASE_RD_IMG_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x13 + offset));
    VPSS_BASE_RD_IMG_STRIDE.bits.c_stride = c_head_stride;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x13 + offset), VPSS_BASE_RD_IMG_STRIDE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetYHeadStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_head_stride)
{
    U_VPSS_BASE_RD_IMG_STRIDE VPSS_BASE_RD_IMG_STRIDE;

    VPSS_BASE_RD_IMG_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x13 + offset));
    VPSS_BASE_RD_IMG_STRIDE.bits.y_stride = y_head_stride;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x13 + offset), VPSS_BASE_RD_IMG_STRIDE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetC2bStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_2b_stride)
{
    U_VPSS_BASE_RD_IMG_STRIDE VPSS_BASE_RD_IMG_STRIDE;

    VPSS_BASE_RD_IMG_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x18 + offset));
    VPSS_BASE_RD_IMG_STRIDE.bits.c_stride = c_2b_stride;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x18 + offset), VPSS_BASE_RD_IMG_STRIDE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetY2bStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_2b_stride)
{
    U_VPSS_BASE_RD_IMG_STRIDE VPSS_BASE_RD_IMG_STRIDE;

    VPSS_BASE_RD_IMG_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x18 + offset));
    VPSS_BASE_RD_IMG_STRIDE.bits.y_stride = y_2b_stride;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x18 + offset), VPSS_BASE_RD_IMG_STRIDE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetCMuteVal(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_mute_val)
{
    U_VPSS_BASE_RD_IMG_MUTE_VAL VPSS_BASE_RD_IMG_MUTE_VAL;

    VPSS_BASE_RD_IMG_MUTE_VAL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x19 + offset));
    VPSS_BASE_RD_IMG_MUTE_VAL.bits.c_mute_val = c_mute_val;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x19 + offset), VPSS_BASE_RD_IMG_MUTE_VAL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SetYMuteVal(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_mute_val)
{
    U_VPSS_BASE_RD_IMG_MUTE_VAL VPSS_BASE_RD_IMG_MUTE_VAL;

    VPSS_BASE_RD_IMG_MUTE_VAL.u32 = VPSS_RegRead((&(pstReg->VPSS_CF_CTRL.u32) + 0x19 + offset));
    VPSS_BASE_RD_IMG_MUTE_VAL.bits.y_mute_val = y_mute_val;
    VPSS_RegWrite((&(pstReg->VPSS_CF_CTRL.u32) + 0x19 + offset), VPSS_BASE_RD_IMG_MUTE_VAL.u32);

    return ;
}


//-------------------------------------------------
// vpss mac rchn hal solo
//-------------------------------------------------

HI_VOID VPSS_RCHN_SOLO_SetEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en)
{
    U_VPSS_BASE_RD_SOLO_CTRL VPSS_BASE_RD_SOLO_CTRL;

    VPSS_BASE_RD_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset));
    VPSS_BASE_RD_SOLO_CTRL.bits.en = en;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset), VPSS_BASE_RD_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetEn1(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en1)
{
    U_VPSS_BASE_RD_SOLO_CTRL VPSS_BASE_RD_SOLO_CTRL;

    VPSS_BASE_RD_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset));
    VPSS_BASE_RD_SOLO_CTRL.bits.en1 = en1;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset), VPSS_BASE_RD_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetTunleEn( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 tunl_en)
{
    U_VPSS_BASE_RD_SOLO_CTRL VPSS_BASE_RD_SOLO_CTRL;

    VPSS_BASE_RD_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset));
    VPSS_BASE_RD_SOLO_CTRL.bits.tunl_en = tunl_en;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset), VPSS_BASE_RD_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetMuteEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mute_en)
{
    U_VPSS_BASE_RD_SOLO_CTRL VPSS_BASE_RD_SOLO_CTRL;

    VPSS_BASE_RD_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset));
    VPSS_BASE_RD_SOLO_CTRL.bits.mute_en = mute_en;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset), VPSS_BASE_RD_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetDBypass( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 d_bypass)
{
    U_VPSS_BASE_RD_SOLO_CTRL VPSS_BASE_RD_SOLO_CTRL;

    VPSS_BASE_RD_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset));
    VPSS_BASE_RD_SOLO_CTRL.bits.d_bypass = d_bypass;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset), VPSS_BASE_RD_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetFlip( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 flip)
{
    U_VPSS_BASE_RD_SOLO_CTRL VPSS_BASE_RD_SOLO_CTRL;

    VPSS_BASE_RD_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset));
    VPSS_BASE_RD_SOLO_CTRL.bits.flip = flip;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset), VPSS_BASE_RD_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetMirror( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mirror)
{
    U_VPSS_BASE_RD_SOLO_CTRL VPSS_BASE_RD_SOLO_CTRL;

    VPSS_BASE_RD_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset));
    VPSS_BASE_RD_SOLO_CTRL.bits.mirror = mirror;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + offset), VPSS_BASE_RD_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetHeight(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 height)
{
    U_VPSS_BASE_RD_SOLO_SIZE VPSS_BASE_RD_SOLO_SIZE;

    VPSS_BASE_RD_SOLO_SIZE.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x1 + offset));
    VPSS_BASE_RD_SOLO_SIZE.bits.height = height;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x1 + offset), VPSS_BASE_RD_SOLO_SIZE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetWidth(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 width)
{
    U_VPSS_BASE_RD_SOLO_SIZE VPSS_BASE_RD_SOLO_SIZE;

    VPSS_BASE_RD_SOLO_SIZE.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x1 + offset));
    VPSS_BASE_RD_SOLO_SIZE.bits.width = width;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x1 + offset), VPSS_BASE_RD_SOLO_SIZE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 addr_h)
{
    U_VPSS_BASE_RD_SOLO_ADDR_HIGH VPSS_BASE_RD_SOLO_ADDR_HIGH;

    VPSS_BASE_RD_SOLO_ADDR_HIGH.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x2 + offset));
    VPSS_BASE_RD_SOLO_ADDR_HIGH.bits.addr_h = addr_h;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x2 + offset), VPSS_BASE_RD_SOLO_ADDR_HIGH.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 addr_l)
{
    U_VPSS_BASE_RD_SOLO_ADDR_LOW VPSS_BASE_RD_SOLO_ADDR_LOW;

    VPSS_BASE_RD_SOLO_ADDR_LOW.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x3 + offset));
    VPSS_BASE_RD_SOLO_ADDR_LOW.bits.addr_l = addr_l;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x3 + offset), VPSS_BASE_RD_SOLO_ADDR_LOW.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 stride)
{
    U_VPSS_BASE_RD_SOLO_STRIDE VPSS_BASE_RD_SOLO_STRIDE;

    VPSS_BASE_RD_SOLO_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x4 + offset));
    VPSS_BASE_RD_SOLO_STRIDE.bits.stride = stride;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x4 + offset), VPSS_BASE_RD_SOLO_STRIDE.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetMuteVal0(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mute_val0)
{
    U_VPSS_BASE_RD_SOLO_MUTE_VAL0 VPSS_BASE_RD_SOLO_MUTE_VAL0;

    VPSS_BASE_RD_SOLO_MUTE_VAL0.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x5 + offset));
    VPSS_BASE_RD_SOLO_MUTE_VAL0.bits.mute_val0 = mute_val0;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x5 + offset), VPSS_BASE_RD_SOLO_MUTE_VAL0.u32);

    return ;
}


HI_VOID VPSS_RCHN_SOLO_SetMuteVal1(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mute_val1)
{
    U_VPSS_BASE_RD_SOLO_MUTE_VAL1 VPSS_BASE_RD_SOLO_MUTE_VAL1;

    VPSS_BASE_RD_SOLO_MUTE_VAL1.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x6 + offset));
    VPSS_BASE_RD_SOLO_MUTE_VAL1.bits.mute_val1 = mute_val1;
    VPSS_RegWrite((&(pstReg->VPSS_NR_RMAD_CTRL.u32) + 0x6 + offset), VPSS_BASE_RD_SOLO_MUTE_VAL1.u32);

    return ;
}


