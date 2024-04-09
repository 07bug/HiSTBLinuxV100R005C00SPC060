#include "vpss_hal_comm.h"
#include "vpss_hal_ip_wchn.h"
#include "vpss_mac_define.h"
#include "vpss_cbb_reg.h"

// Base Image Reg Use: VPSS_OUT0_CTRL
// Base Solo  Reg Use: VPSS_NR_WMAD_CTRL

//-------------------------------------------------
// vpss mac wchn hal image
//-------------------------------------------------

HI_VOID VPSS_WCHN_SetEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.en = en;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetTunlEn( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 tunl_en)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.tunl_en = tunl_en;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetDBypass( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 d_bypass)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.d_bypass = d_bypass;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetHBypass( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 h_bypass)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.h_bypass = h_bypass;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetLmRmode(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 lm_rmode)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.lm_rmode = lm_rmode;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetDitherMode(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 dither_mode)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.dither_mode = dither_mode;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetDitherEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 dither_en)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.dither_en = dither_en;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetFlip(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 flip)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.flip = flip;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetMirror(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mirror)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.mirror = mirror;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetUvInvert(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 uv_invert)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.uv_invert = uv_invert;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetCmpMode(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 cmp_mode)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.cmp_mode = cmp_mode;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetBitw(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 bitw)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.bitw = bitw;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetType(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 type)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.type = type;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetVerOffset(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 ver_offset)
{
    U_VPSS_BASE_WR_IMG_OFFSET VPSS_BASE_WR_IMG_OFFSET;

    VPSS_BASE_WR_IMG_OFFSET.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x1 + offset));
    VPSS_BASE_WR_IMG_OFFSET.bits.ver_offset = ver_offset;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x1 + offset), VPSS_BASE_WR_IMG_OFFSET.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetHorOffset(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 hor_offset)
{
    U_VPSS_BASE_WR_IMG_OFFSET VPSS_BASE_WR_IMG_OFFSET;

    VPSS_BASE_WR_IMG_OFFSET.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x1 + offset));
    VPSS_BASE_WR_IMG_OFFSET.bits.hor_offset = hor_offset;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x1 + offset), VPSS_BASE_WR_IMG_OFFSET.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetYAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_addr_l)
{
    U_VPSS_BASE_WR_IMGY_ADDR_LOW VPSS_BASE_WR_IMGY_ADDR_LOW;

    VPSS_BASE_WR_IMGY_ADDR_LOW.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x3 + offset));
    VPSS_BASE_WR_IMGY_ADDR_LOW.bits.y_addr_l = y_addr_l;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x3 + offset), VPSS_BASE_WR_IMGY_ADDR_LOW.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetYAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_addr_h)
{
    U_VPSS_BASE_WR_IMGY_ADDR_HIGH VPSS_BASE_WR_IMGY_ADDR_HIGH;

    VPSS_BASE_WR_IMGY_ADDR_HIGH.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x2 + offset));
    VPSS_BASE_WR_IMGY_ADDR_HIGH.bits.y_addr_h = y_addr_h;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x2 + offset), VPSS_BASE_WR_IMGY_ADDR_HIGH.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetCAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_addr_l)
{
    U_VPSS_BASE_WR_IMGC_ADDR_LOW VPSS_BASE_WR_IMGC_ADDR_LOW;

    VPSS_BASE_WR_IMGC_ADDR_LOW.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x5 + offset));
    VPSS_BASE_WR_IMGC_ADDR_LOW.bits.c_addr_l = c_addr_l;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x5 + offset), VPSS_BASE_WR_IMGC_ADDR_LOW.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetCAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_addr_h)
{
    U_VPSS_BASE_WR_IMGC_ADDR_HIGH VPSS_BASE_WR_IMGC_ADDR_HIGH;

    VPSS_BASE_WR_IMGC_ADDR_HIGH.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x4 + offset));
    VPSS_BASE_WR_IMGC_ADDR_HIGH.bits.c_addr_h = c_addr_h;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x4 + offset), VPSS_BASE_WR_IMGC_ADDR_HIGH.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetCStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 c_stride)
{
    U_VPSS_BASE_WR_IMG_STRIDE VPSS_BASE_WR_IMG_STRIDE;

    VPSS_BASE_WR_IMG_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x6 + offset));
    VPSS_BASE_WR_IMG_STRIDE.bits.c_stride = c_stride;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x6 + offset), VPSS_BASE_WR_IMG_STRIDE.u32);

    return ;
}


HI_VOID VPSS_WCHN_SetYStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 y_stride)
{
    U_VPSS_BASE_WR_IMG_STRIDE VPSS_BASE_WR_IMG_STRIDE;

    VPSS_BASE_WR_IMG_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x6 + offset));
    VPSS_BASE_WR_IMG_STRIDE.bits.y_stride = y_stride;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0x6 + offset), VPSS_BASE_WR_IMG_STRIDE.u32);

    return ;
}


HI_VOID VPSS_WCHN_ENV_SetFormat(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 format)
{
    U_VPSS_BASE_WR_IMG_CTRL VPSS_BASE_WR_IMG_CTRL;

    VPSS_BASE_WR_IMG_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + offset));
    VPSS_BASE_WR_IMG_CTRL.bits.format = format;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + offset), VPSS_BASE_WR_IMG_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_ENV_SetHeight(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 height)
{
    U_VPSS_BASE_WR_IMG_SIZE VPSS_BASE_WR_IMG_SIZE;

    VPSS_BASE_WR_IMG_SIZE.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0xc + offset));
    VPSS_BASE_WR_IMG_SIZE.bits.height = height;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0xc + offset), VPSS_BASE_WR_IMG_SIZE.u32);

    return ;
}


HI_VOID VPSS_WCHN_ENV_SetWidth(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 width)
{
    U_VPSS_BASE_WR_IMG_SIZE VPSS_BASE_WR_IMG_SIZE;

    VPSS_BASE_WR_IMG_SIZE.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0xc + offset));
    VPSS_BASE_WR_IMG_SIZE.bits.width = width;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0xc + offset), VPSS_BASE_WR_IMG_SIZE.u32);

    return ;
}


HI_VOID VPSS_WCHN_ENV_SetFinfoH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 finfo_h)
{
    U_VPSS_BASE_WR_IMG_FINFO_HIGN VPSS_BASE_WR_IMG_FINFO_HIGN;

    VPSS_BASE_WR_IMG_FINFO_HIGN.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0xd + offset));
    VPSS_BASE_WR_IMG_FINFO_HIGN.bits.finfo_h = finfo_h;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0xd + offset), VPSS_BASE_WR_IMG_FINFO_HIGN.u32);

    return ;
}


HI_VOID VPSS_WCHN_ENV_SetFinfoL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 finfo_l)
{
    U_VPSS_BASE_WR_IMG_FINFO_LOW VPSS_BASE_WR_IMG_FINFO_LOW;

    VPSS_BASE_WR_IMG_FINFO_LOW.u32 = VPSS_RegRead((&(pstReg->VPSS_OUT0_CTRL.u32) + 0xe + offset));
    VPSS_BASE_WR_IMG_FINFO_LOW.bits.finfo_l = finfo_l;
    VPSS_RegWrite((&(pstReg->VPSS_OUT0_CTRL.u32) + 0xe + offset), VPSS_BASE_WR_IMG_FINFO_LOW.u32);

    return ;
}


//-------------------------------------------------
// vpss mac wchn hal solo
//-------------------------------------------------

HI_VOID VPSS_WCHN_SOLO_SetEn(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 en)
{
    U_VPSS_BASE_WR_SOLO_CTRL VPSS_BASE_WR_SOLO_CTRL;

    VPSS_BASE_WR_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset));
    VPSS_BASE_WR_SOLO_CTRL.bits.en = en;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset), VPSS_BASE_WR_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SOLO_SetTunlEn( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 tunl_en)
{
    U_VPSS_BASE_WR_SOLO_CTRL VPSS_BASE_WR_SOLO_CTRL;

    VPSS_BASE_WR_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset));
    VPSS_BASE_WR_SOLO_CTRL.bits.tunl_en = tunl_en;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset), VPSS_BASE_WR_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SOLO_SetDBypass( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 d_bypass)
{
    U_VPSS_BASE_WR_SOLO_CTRL VPSS_BASE_WR_SOLO_CTRL;

    VPSS_BASE_WR_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset));
    VPSS_BASE_WR_SOLO_CTRL.bits.d_bypass = d_bypass;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset), VPSS_BASE_WR_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SOLO_SetFlip( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 flip)
{
    U_VPSS_BASE_WR_SOLO_CTRL VPSS_BASE_WR_SOLO_CTRL;

    VPSS_BASE_WR_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset));
    VPSS_BASE_WR_SOLO_CTRL.bits.flip = flip;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset), VPSS_BASE_WR_SOLO_CTRL.u32);

    return ;
}


HI_VOID VPSS_WCHN_SOLO_SetMirror( S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 mirror)
{
    U_VPSS_BASE_WR_SOLO_CTRL VPSS_BASE_WR_SOLO_CTRL;

    VPSS_BASE_WR_SOLO_CTRL.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset));
    VPSS_BASE_WR_SOLO_CTRL.bits.mirror = mirror;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + offset), VPSS_BASE_WR_SOLO_CTRL.u32);

    return ;
}



HI_VOID VPSS_WCHN_SOLO_SetAddrH(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 addr_h)
{
    U_VPSS_BASE_WR_SOLO_ADDR_HIGH VPSS_BASE_WR_SOLO_ADDR_HIGH;

    VPSS_BASE_WR_SOLO_ADDR_HIGH.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x1 + offset));
    VPSS_BASE_WR_SOLO_ADDR_HIGH.bits.addr_h = addr_h;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x1 + offset), VPSS_BASE_WR_SOLO_ADDR_HIGH.u32);

    return ;
}


HI_VOID VPSS_WCHN_SOLO_SetAddrL(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 addr_l)
{
    U_VPSS_BASE_WR_SOLO_ADDR_LOW VPSS_BASE_WR_SOLO_ADDR_LOW;

    VPSS_BASE_WR_SOLO_ADDR_LOW.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x2 + offset));
    VPSS_BASE_WR_SOLO_ADDR_LOW.bits.addr_l = addr_l;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x2 + offset), VPSS_BASE_WR_SOLO_ADDR_LOW.u32);

    return ;
}


HI_VOID VPSS_WCHN_SOLO_SetStride(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 stride)
{
    U_VPSS_BASE_WR_SOLO_STRIDE VPSS_BASE_WR_SOLO_STRIDE;

    VPSS_BASE_WR_SOLO_STRIDE.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x3 + offset));
    VPSS_BASE_WR_SOLO_STRIDE.bits.stride = stride;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x3 + offset), VPSS_BASE_WR_SOLO_STRIDE.u32);

    return ;
}


HI_VOID VPSS_WCHN_SOLO_ENV_SetHeight(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 height)
{
    U_VPSS_BASE_WR_SOLO_SIZE VPSS_BASE_WR_SOLO_SIZE;

    VPSS_BASE_WR_SOLO_SIZE.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x4 + offset));
    VPSS_BASE_WR_SOLO_SIZE.bits.height = height;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x4 + offset), VPSS_BASE_WR_SOLO_SIZE.u32);

    return ;
}


HI_VOID VPSS_WCHN_SOLO_ENV_SetWidth(S_VPSS_REGS_TYPE *pstReg, HI_U32 offset, HI_U32 width)
{
    U_VPSS_BASE_WR_SOLO_SIZE VPSS_BASE_WR_SOLO_SIZE;

    VPSS_BASE_WR_SOLO_SIZE.u32 = VPSS_RegRead((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x4 + offset));
    VPSS_BASE_WR_SOLO_SIZE.bits.width = width;
    VPSS_RegWrite((&(pstReg->VPSS_NR_WMAD_CTRL.u32) + 0x4 + offset), VPSS_BASE_WR_SOLO_SIZE.u32);

    return ;
}


