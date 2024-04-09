//**********************************************************************
// File Name   : vdp_drv_gfx.cpp
// Data        : 2012/10/17
// Version     : v1.0
// Abstract    : header of vdp define
//
// Modification history
//----------------------------------------------------------------------
// Version       Data(yyyy/mm/dd)      name
// Description
//
//
//
//
//
//**********************************************************************


#include "vdp_hal_comm.h"
#include "vdp_hal_gfx.h"
#include "vdp_hal_ip_fdr.h"

extern volatile S_VDP_REGS_TYPE* pVdpReg;
HI_VOID  VDP_GP_SetLayerEnable(HI_U32 u32Data, HI_U32 u32bEnable )
{
    U_GP0_CTRL GP0_CTRL;

    GP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32) + u32Data * GFX_OFFSET));
    GP0_CTRL.bits.surface_en = u32bEnable ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32) + u32Data * GFX_OFFSET), GP0_CTRL.u32);

    return ;
}

HI_VOID  VDP_GP_SetUpdMode(HI_U32 u32Data, HI_U32  u32Rgup)
{
    U_GP0_CTRL GP0_CTRL;


    GP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32) + u32Data * GFX_OFFSET));
    GP0_CTRL.bits.rgup_mode = u32Rgup ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32) + u32Data * GFX_OFFSET), GP0_CTRL.u32);

    return ;
}

HI_VOID VDP_GFX_SetGfxArbMode  (HI_U32 u32GfxLayer, HI_U32 u32Mode)
{
    U_VOCTRL VOCTRL;

    VOCTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VOCTRL.u32)));
    VOCTRL.bits.grc_arb_mode = u32Mode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VOCTRL.u32)),VOCTRL.u32);
}
HI_VOID  VDP_GFX_SetLayerReso     (HI_U32 u32Data, VDP_DISP_RECT_S  stRect)
{
#if 0
    U_G0_SFPOS G0_SFPOS;
    U_G0_VFPOS G0_VFPOS;
    U_G0_VLPOS G0_VLPOS;
    U_G0_DFPOS G0_DFPOS;
    U_G0_DLPOS G0_DLPOS;
    U_G0_IRESO G0_IRESO;
    //U_G0_ORESO G0_ORESO;


    // Read source position
    G0_SFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_SFPOS.u32)+ u32Data * GFX_OFFSET));
    G0_SFPOS.bits.src_xfpos = stRect.u32SX;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_SFPOS.u32)+ u32Data * GFX_OFFSET), G0_SFPOS.u32);

    G0_VFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_VFPOS.u32) + u32Data * GFX_OFFSET));
    G0_VFPOS.bits.video_xfpos = stRect.u32VX;
    G0_VFPOS.bits.video_yfpos = stRect.u32VY;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_VFPOS.u32) + u32Data * GFX_OFFSET), G0_VFPOS.u32);

    G0_VLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_VLPOS.u32) + u32Data * GFX_OFFSET));
    G0_VLPOS.bits.video_xlpos = stRect.u32VX + stRect.u32OWth - 1;
    G0_VLPOS.bits.video_ylpos = stRect.u32VY + stRect.u32OHgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_VLPOS.u32) + u32Data * GFX_OFFSET), G0_VLPOS.u32);

    // display position
    G0_DFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_DFPOS.u32)+ u32Data * GFX_OFFSET));
    G0_DFPOS.bits.disp_xfpos = stRect.u32DXS;
    G0_DFPOS.bits.disp_yfpos = stRect.u32DYS;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DFPOS.u32)+ u32Data * GFX_OFFSET), G0_DFPOS.u32);

    G0_DLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_DLPOS.u32)+ u32Data * GFX_OFFSET));
    G0_DLPOS.bits.disp_xlpos = stRect.u32DXL - 1;
    G0_DLPOS.bits.disp_ylpos = stRect.u32DYL - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DLPOS.u32)+ u32Data * GFX_OFFSET), G0_DLPOS.u32);

    // input width and height
    G0_IRESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_IRESO.u32)+ u32Data * GFX_OFFSET));
    G0_IRESO.bits.iw = stRect.u32IWth - 1;
    G0_IRESO.bits.ih = stRect.u32IHgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_IRESO.u32)+ u32Data * GFX_OFFSET), G0_IRESO.u32);

    // output width and height
    //G0_ORESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_ORESO.u32)+ u32Data * GFX_OFFSET));
    //G0_ORESO.bits.ow = stRect.u32OWth - 1;
    //G0_ORESO.bits.oh = stRect.u32OHgt - 1;
    //VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_ORESO.u32)+ u32Data * GFX_OFFSET), G0_ORESO.u32);
#endif
    return ;
}
HI_VOID  VDP_GFX_SetVideoPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_G0_VFPOS G0_VFPOS;
    U_G0_VLPOS G0_VLPOS;


    /*video position */
    G0_VFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_VFPOS.u32) + u32Data * GFX_OFFSET));
    G0_VFPOS.bits.video_xfpos = stRect.u32X;
    G0_VFPOS.bits.video_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_VFPOS.u32) + u32Data * GFX_OFFSET), G0_VFPOS.u32);

    G0_VLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_VLPOS.u32) + u32Data * GFX_OFFSET));
    G0_VLPOS.bits.video_xlpos = stRect.u32X + stRect.u32Wth - 1;
    G0_VLPOS.bits.video_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_VLPOS.u32) + u32Data * GFX_OFFSET), G0_VLPOS.u32);
    return ;
}

HI_VOID  VDP_GFX_SetDispPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_G0_DFPOS G0_DFPOS;
    U_G0_DLPOS G0_DLPOS;


    /*video position */
    G0_DFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_DFPOS.u32) + u32Data * GFX_OFFSET));
    G0_DFPOS.bits.disp_xfpos = stRect.u32X;
    G0_DFPOS.bits.disp_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DFPOS.u32) + u32Data * GFX_OFFSET), G0_DFPOS.u32);

    G0_DLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_DLPOS.u32) + u32Data * GFX_OFFSET));
    G0_DLPOS.bits.disp_xlpos = stRect.u32X + stRect.u32Wth - 1;
    G0_DLPOS.bits.disp_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DLPOS.u32) + u32Data * GFX_OFFSET), G0_DLPOS.u32);
    return ;
}

HI_VOID  VDP_GFX_SetInReso(HI_U32 u32Data, VDP_RECT_S  stRect)
{
    VDP_FDR_GFX_SetSrcH          (  u32Data * GFX_FDR_OFFSET, stRect.u32Hgt - 1);
    VDP_FDR_GFX_SetSrcW          (  u32Data * GFX_FDR_OFFSET, stRect.u32Wth - 1);
    VDP_FDR_GFX_SetSrcCropY      (  u32Data * GFX_FDR_OFFSET, 0);
    VDP_FDR_GFX_SetSrcCropX      (  u32Data * GFX_FDR_OFFSET, 0);
    VDP_FDR_GFX_SetIresoH        (  u32Data * GFX_FDR_OFFSET, stRect.u32Hgt - 1);
    VDP_FDR_GFX_SetIresoW        (  u32Data * GFX_FDR_OFFSET, stRect.u32Wth - 1);

#if 0
    U_G0_IRESO G0_IRESO;


    //grap position
    G0_IRESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_IRESO.u32) + u32Data * GFX_OFFSET));
    G0_IRESO.bits.iw = stRect.u32Wth - 1;
    G0_IRESO.bits.ih = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_IRESO.u32) + u32Data * GFX_OFFSET), G0_IRESO.u32);
#endif
    return ;
}

HI_VOID  VDP_GFX_SetSrcPos (HI_U32 u32Data, VDP_RECT_S  stRect)
{
#if 0
    U_G0_SFPOS G0_SFPOS;


    // Read source position
    G0_SFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_SFPOS.u32)+ u32Data * GFX_OFFSET));
    G0_SFPOS.bits.src_xfpos = stRect.u32SX;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_SFPOS.u32)+ u32Data * GFX_OFFSET), G0_SFPOS.u32);
#endif
    return ;
}

HI_VOID  VDP_GFX_SetLayerEnable(HI_U32 u32Data, HI_U32 u32bEnable )
{
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    if((u32Data == VDP_LAYER_GFX3) || (u32Data == VDP_LAYER_GFX4))
        G0_CTRL.bits.surface_en = 0;
    else
        G0_CTRL.bits.surface_en = u32bEnable ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);

    return ;
}

HI_VOID VDP_GFX_SetReqCtrl(HI_U32 u32Data, HI_U32 u32ReqCtrl)
{
    VDP_FDR_GFX_SetReqCtrl       ( u32Data * GFX_FDR_OFFSET, u32ReqCtrl);
#if 0
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.req_ctrl = u32ReqCtrl;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);
#endif
    return ;
}

HI_VOID VDP_GFX_SetReqLength(HI_U32 u32Data, HI_U32 u32RegLen)
{
    VDP_FDR_GFX_SetReqLen ( u32Data * GFX_FDR_OFFSET, u32RegLen);

#if 0
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
#ifdef VDP_HI3798MV200
    G0_CTRL.bits.rlen_sel = 0;
#else
    G0_CTRL.bits.rlen_sel = u32RegLen;
#endif
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);
#endif
    return ;
}

HI_VOID VDP_GFX_SetReqMacCtrl(HI_U32 u32Data, HI_U32 u32ReqMacCtrl)
{
#ifdef VDP_HI3798MV200
#else
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.req_mac_ctrl = u32ReqMacCtrl;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);
#endif

    return ;
}

HI_VOID  VDP_GFX_SetNoSecFlag    (HI_U32 u32Data, HI_U32 u32Enable )
{
    U_G0_CTRL  G0_CTRL;

    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.nosec_flag= u32Enable ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);

    return ;
}

HI_VOID VDP_GFX_SetLayerAddr(HI_U32 u32Data, HI_U32 u32LAddr, HI_U32 u32Stride)
{
    VDP_FDR_GFX_SetGfxAddrL       (  u32Data * GFX_FDR_OFFSET, u32LAddr);
    VDP_FDR_GFX_SetSurfaceStride  (  u32Data * GFX_FDR_OFFSET, u32Stride);
    VDP_FDR_GFX_SetDcmpStride     (  u32Data * GFX_FDR_OFFSET, u32Stride);
    VDP_FDR_GFX_SetHead2Stride    (  u32Data * GFX_FDR_OFFSET, 0x1);
    VDP_FDR_GFX_SetHeadStride     (  u32Data * GFX_FDR_OFFSET, 0x1);
#if 0
    U_G0_ADDR G0_ADDR;
    U_G0_STRIDE G0_STRIDE;
    G0_ADDR.u32 = u32LAddr;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_ADDR.u32)+ u32Data * GFX_OFFSET), G0_ADDR.u32);

    G0_STRIDE.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_STRIDE.u32)+ u32Data * GFX_OFFSET));
    G0_STRIDE.bits.surface_stride = u32Stride;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_STRIDE.u32)+ u32Data * GFX_OFFSET), G0_STRIDE.u32);
#endif
    return;
}

HI_VOID  VDP_GFX_SetInDataFmt(HI_U32 u32Data, VDP_GFX_IFMT_E  enDataFmt)
{

    VDP_FDR_GFX_SetIfmt          (  u32Data * GFX_FDR_OFFSET, enDataFmt);
#if 0
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.ifmt = enDataFmt;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);
#endif
    return ;
}

HI_VOID VDP_GFX_SetReadMode(HI_U32 u32Data, HI_U32 u32Mode)
{
    VDP_FDR_GFX_SetReadMode      ( u32Data * GFX_FDR_OFFSET, u32Mode);
#if 0
    U_G0_CTRL G0_CTRL;

    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32)+ u32Data * GFX_OFFSET));
    G0_CTRL.bits.read_mode = u32Mode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32)+ u32Data * GFX_OFFSET), G0_CTRL.u32);
#endif
    return ;
}

HI_VOID VDP_GFX_SetBitExtend(HI_U32 u32Data, VDP_GFX_BITEXTEND_E u32mode)
{
    VDP_FDR_GFX_SetBitext        ( u32Data * GFX_FDR_OFFSET, u32mode);
#if 0
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32)+ u32Data * GFX_OFFSET));
    G0_CTRL.bits.bitext = u32mode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32)+ u32Data * GFX_OFFSET), G0_CTRL.u32);
#endif
    return ;
}

HI_VOID VDP_GFX_SetColorKey(HI_U32 u32Data, HI_U32 u32keyEn,VDP_GFX_CKEY_S stKey )
{
    VDP_FDR_GFX_SetKeyEn         (  u32Data * GFX_FDR_OFFSET, u32keyEn);
    VDP_FDR_GFX_SetKeyMode       (  u32Data * GFX_FDR_OFFSET, stKey.bKeyMode);
    VDP_FDR_GFX_SetKeyRMax       (  u32Data * GFX_FDR_OFFSET, stKey.u32Key_r_max);
    VDP_FDR_GFX_SetKeyGMax       (  u32Data * GFX_FDR_OFFSET, stKey.u32Key_g_max);
    VDP_FDR_GFX_SetKeyBMax       (  u32Data * GFX_FDR_OFFSET, stKey.u32Key_b_max);
    VDP_FDR_GFX_SetKeyRMin       (  u32Data * GFX_FDR_OFFSET, stKey.u32Key_r_min);
    VDP_FDR_GFX_SetKeyGMin       (  u32Data * GFX_FDR_OFFSET, stKey.u32Key_g_min);
    VDP_FDR_GFX_SetKeyBMin       (  u32Data * GFX_FDR_OFFSET, stKey.u32Key_b_min);
#if 0
    U_G0_CKEYMAX G0_CKEYMAX;
    U_G0_CKEYMIN G0_CKEYMIN;
    U_G0_CBMPARA G0_CBMPARA;

    G0_CKEYMAX.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CKEYMAX.u32)+ u32Data * GFX_OFFSET));
    G0_CKEYMAX.bits.keyr_max = stKey.u32Key_r_max;
    G0_CKEYMAX.bits.keyg_max = stKey.u32Key_g_max;
    G0_CKEYMAX.bits.keyb_max = stKey.u32Key_b_max;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CKEYMAX.u32)+ u32Data * GFX_OFFSET), G0_CKEYMAX.u32);

    G0_CKEYMIN.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CKEYMIN.u32)+ u32Data * GFX_OFFSET));
    G0_CKEYMIN.bits.keyr_min = stKey.u32Key_r_min;
    G0_CKEYMIN.bits.keyg_min = stKey.u32Key_g_min;
    G0_CKEYMIN.bits.keyb_min = stKey.u32Key_b_min;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CKEYMIN.u32)+ u32Data * GFX_OFFSET), G0_CKEYMIN.u32);

    G0_CBMPARA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CBMPARA.u32)+ u32Data * GFX_OFFSET));
    G0_CBMPARA.bits.key_en = u32keyEn;
    G0_CBMPARA.bits.key_mode = stKey.bKeyMode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CBMPARA.u32)+ u32Data * GFX_OFFSET), G0_CBMPARA.u32);
#endif
    return ;
}

HI_VOID VDP_GFX_SetKeyMask(HI_U32 u32Data, VDP_GFX_MASK_S stMsk)
{
    VDP_FDR_GFX_SetKeyRMsk       (  u32Data * GFX_FDR_OFFSET, stMsk.u32Mask_r);
    VDP_FDR_GFX_SetKeyGMsk       (  u32Data * GFX_FDR_OFFSET, stMsk.u32Mask_g);
    VDP_FDR_GFX_SetKeyBMsk       (  u32Data * GFX_FDR_OFFSET, stMsk.u32Mask_b);
#if 0
    U_G0_CMASK G0_CMASK;
    G0_CMASK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CMASK.u32)+ u32Data * GFX_OFFSET));
    G0_CMASK.bits.kmsk_r = stMsk.u32Mask_r;
    G0_CMASK.bits.kmsk_g = stMsk.u32Mask_g;
    G0_CMASK.bits.kmsk_b = stMsk.u32Mask_b;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CMASK.u32)+ u32Data * GFX_OFFSET), G0_CMASK.u32);
#endif
    return ;
}

HI_VOID  VDP_GFX_SetParaUpd  (HI_U32 u32Data, VDP_GFX_PARA_E enMode )
{
    U_PARA_UP_VHD PARA_UP_VHD;

    PARA_UP_VHD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32));
    if(u32Data == VDP_LAYER_GFX0)
    {
        PARA_UP_VHD.bits.para_up_vhd_chn17 = 0x1;
    }
    else if(u32Data == VDP_LAYER_GFX1)
    {
        PARA_UP_VHD.bits.para_up_vhd_chn18 = 0x1;
    }
    else
    {

    }
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);

#if 0
    U_G0_PARAUP G0_PARAUP;

    if (enMode == VDP_GFX_PARA_LUT)
    {
        G0_PARAUP.bits.gdc_paraup = 0x1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_PARAUP.u32)+ u32Data * GFX_OFFSET), G0_PARAUP.u32);
    }
#endif


}

HI_VOID VDP_GFX_SetLutAddr(HI_U32 u32Data, HI_U32 u32LutAddr)
{

    if(u32Data == VDP_LAYER_GFX0)
    {
        U_PARA_ADDR_VHD_CHN17 PARA_ADDR_VHD_CHN17;

        PARA_ADDR_VHD_CHN17.bits.para_addr_vhd_chn17 = u32LutAddr;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN17.u32),PARA_ADDR_VHD_CHN17.u32);
    }
    else if(u32Data == VDP_LAYER_GFX1)
    {
        U_PARA_ADDR_VHD_CHN18 PARA_ADDR_VHD_CHN18;

        PARA_ADDR_VHD_CHN18.bits.para_addr_vhd_chn18 = u32LutAddr;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN18.u32),PARA_ADDR_VHD_CHN18.u32);
    }
    else
    {

    }

#if 0
    U_G0_PARAADDR G0_PARAADDR;
    G0_PARAADDR.u32 = u32LutAddr;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_PARAADDR.u32)+ u32Data * GFX_OFFSET), G0_PARAADDR.u32);
#endif
}

HI_VOID  VDP_GFX_SetDcmpEnable(HI_U32 u32Data, HI_U32 u32bEnable )
{
    HI_U32 u32DcmpType = u32bEnable;
    VDP_FDR_GFX_SetDcmpType      (  u32Data * GFX_FDR_OFFSET, u32DcmpType);
#if 0
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.dcmp_en = u32bEnable ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);
#endif
    return ;
}

HI_VOID VDP_GFX_SetDcmpAddr(HI_U32 u32Data, HI_U32 u32LAddr)
{
    VDP_FDR_GFX_SetHAddrL         ( u32Data * GFX_FDR_OFFSET, u32LAddr );
#if 0
    U_G0_DCMP_ADDR G0_DCMP_ADDR;
    G0_DCMP_ADDR.u32 = u32LAddr;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DCMP_ADDR.u32)+ u32Data * GFX_OFFSET), G0_DCMP_ADDR.u32);
#endif
    return ;
}

HI_VOID VDP_GFX_SetDcmpNAddr(HI_U32 u32Data, HI_U32 u32NAddr)
{
    VDP_FDR_GFX_SetH2AddrL        ( u32Data * GFX_FDR_OFFSET, u32NAddr);
#if 0
    U_G0_DCMP_NADDR G0_DCMP_NADDR;
    G0_DCMP_NADDR.u32 = u32NAddr;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DCMP_NADDR.u32)+ u32Data * GFX_OFFSET), G0_DCMP_NADDR.u32);
#endif
    return ;
}

HI_VOID VDP_GFX_SetDcmpOffset(HI_U32 u32Data, HI_U32 u32Offset)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID  VDP_GFX_SetThreeDimDofStep(HI_U32 u32Data, HI_S32 s32LStep, HI_S32 s32RStep)
{
    U_G0_DOF_STEP  G0_DOF_STEP;

    G0_DOF_STEP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_DOF_STEP.u32))+ u32Data * GFX_OFFSET);
    G0_DOF_STEP.bits.right_step= s32RStep;
    G0_DOF_STEP.bits.left_step = s32LStep;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DOF_STEP.u32)+ u32Data * GFX_OFFSET), G0_DOF_STEP.u32);
}


HI_VOID  VDP_GFX_SetThreeDimDofEnable    (HI_U32 u32Data, HI_U32 bEnable)
{
    U_G0_DOF_CTRL  G0_DOF_CTRL;

    G0_DOF_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_DOF_CTRL.u32))+ u32Data * GFX_OFFSET);
    G0_DOF_CTRL.bits.dof_en= bEnable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DOF_CTRL.u32)+ u32Data * GFX_OFFSET), G0_DOF_CTRL.u32);
}

HI_VOID  VDP_GFX_SetThreeDimDofBkg   (HI_U32 u32Data, VDP_BKG_S stBkg)
{
    U_G0_DOF_BKG  G0_DOF_BKG;
    U_G0_DOF_ALPHA  G0_DOF_ALPHA;

    G0_DOF_BKG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_DOF_BKG.u32))+ u32Data * GFX_OFFSET);
    G0_DOF_BKG.bits.dof_bk_y  = stBkg.u32BkgY>>2;
    G0_DOF_BKG.bits.dof_bk_cb = stBkg.u32BkgU>>2;
    G0_DOF_BKG.bits.dof_bk_cr = stBkg.u32BkgV>>2;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DOF_BKG.u32)+ u32Data * GFX_OFFSET), G0_DOF_BKG.u32);

    G0_DOF_ALPHA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_DOF_ALPHA.u32))+ u32Data * GFX_OFFSET);
    G0_DOF_ALPHA.bits.dof_bk_alpha  = stBkg.u32BkgA;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_DOF_ALPHA.u32)+ u32Data * GFX_OFFSET), G0_DOF_ALPHA.u32);

}

HI_VOID  VDP_GFX_SetFlipEnable(HI_U32 u32Data, HI_U32 bEnable)
{
    VDP_FDR_GFX_SetFlipEn        ( u32Data * GFX_FDR_OFFSET, bEnable );
    return;
}

HI_VOID VDP_GFX_SetPreMultEnable(HI_U32 u32Data, HI_U32 bEnable)
{
    VDP_FDR_GFX_SetPremultiEn    ( u32Data * GFX_FDR_OFFSET, bEnable);
    return ;
}

HI_VOID  VDP_GFX_SetLayerBkg(HI_U32 u32Data, VDP_BKG_S stBkg)
{
    U_G0_BK    G0_BK;
    U_G0_ALPHA G0_ALPHA;


    G0_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_BK.u32) + u32Data * GFX_OFFSET));
    G0_BK.bits.vbk_y  = stBkg.u32BkgY*4;//0x0;  //
    G0_BK.bits.vbk_cb = stBkg.u32BkgU*4;//0x200;//
    G0_BK.bits.vbk_cr = stBkg.u32BkgV*4;//0x200;//
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_BK.u32) + u32Data * GFX_OFFSET), G0_BK.u32);

    G0_ALPHA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_ALPHA.u32) + u32Data * GFX_OFFSET));
    G0_ALPHA.bits.vbk_alpha = stBkg.u32BkgA;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_ALPHA.u32) + u32Data * GFX_OFFSET), G0_ALPHA.u32);

    return ;
}

HI_VOID  VDP_GFX_SetLayerGalpha (HI_U32 u32Data, HI_U32 u32Alpha0)
{
    U_G0_CTRL G0_CTRL;



    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.galpha = u32Alpha0;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);
    return ;
}

HI_VOID VDP_GFX_SetPalpha(HI_U32 u32Data, HI_U32 bAlphaEn,HI_U32 bArange,HI_U32 u32Alpha0,HI_U32 u32Alpha1)
{

    VDP_FDR_GFX_SetPalphaEn      (  u32Data * GFX_FDR_OFFSET, bAlphaEn);
    VDP_FDR_GFX_SetPalphaRange   (  u32Data * GFX_FDR_OFFSET, bArange);
    VDP_FDR_GFX_SetAlpha1        (  u32Data * GFX_FDR_OFFSET, u32Alpha1);
    VDP_FDR_GFX_SetAlpha0        (  u32Data * GFX_FDR_OFFSET, u32Alpha0);
    return;
}

HI_VOID VDP_GFX_SetLayerNAddr(HI_U32 u32Data, HI_U32 u32NAddr)
{
    VDP_FDR_GFX_SetGfxNaddrL      (  u32Data * GFX_FDR_OFFSET, u32NAddr);
    VDP_FDR_GFX_SetDcmpAddrL      (  u32Data * GFX_FDR_OFFSET, u32NAddr );
    return;
}

HI_VOID  VDP_GFX_SetMuteEnable(HI_U32 u32Data, HI_U32 bEnable)
{
    VDP_FDR_GFX_SetMuteEn( u32Data * GFX_FDR_OFFSET, bEnable);
    return ;
}

HI_VOID  VDP_GFX_SetUpdMode(HI_U32 u32Data, HI_U32 u32Mode)
{
    U_G0_CTRL G0_CTRL;

    /* G0 layer register update mode */
    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32)+ u32Data * GFX_OFFSET));
    G0_CTRL.bits.upd_mode = u32Mode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32)+ u32Data * GFX_OFFSET), G0_CTRL.u32);
}


HI_VOID  VDP_GFX_SetRegUp (HI_U32 u32Data)
{
    U_G0_UPD G0_UPD;

    /* GO layer register update */

    G0_UPD.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_UPD.u32) + u32Data * GFX_OFFSET), G0_UPD.u32);

    return ;
}
//---------------------------------------------------------------------------
//driver for GP layer
//---------------------------------------------------------------------------

#if GP0_EN
HI_VOID  VDP_GP_SetLayerReso (HI_U32 u32Data, VDP_DISP_RECT_S  stRect)
{
    U_GP0_VFPOS GP0_VFPOS;
    U_GP0_VLPOS GP0_VLPOS;
    U_GP0_DFPOS GP0_DFPOS;
    U_GP0_DLPOS GP0_DLPOS;
    U_GP0_IRESO GP0_IRESO;
    U_GP0_ZME_HINFO      GP0_ZME_HINFO;
    U_GP0_ZME_VINFO      GP0_ZME_VINFO;

    /*video position */
    GP0_VFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_VFPOS.u32) + u32Data * GP_OFFSET));
    GP0_VFPOS.bits.video_xfpos = stRect.u32VX;
    GP0_VFPOS.bits.video_yfpos = stRect.u32VY;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_VFPOS.u32) + u32Data * GP_OFFSET), GP0_VFPOS.u32);

    GP0_VLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_VLPOS.u32) + u32Data * GP_OFFSET));
    GP0_VLPOS.bits.video_xlpos = stRect.u32VX + stRect.u32OWth - 1;
    GP0_VLPOS.bits.video_ylpos = stRect.u32VY + stRect.u32OHgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_VLPOS.u32) + u32Data * GP_OFFSET), GP0_VLPOS.u32);

    GP0_DFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_DFPOS.u32) + u32Data * GP_OFFSET));
    GP0_DFPOS.bits.disp_xfpos = stRect.u32DXS;
    GP0_DFPOS.bits.disp_yfpos = stRect.u32DYS;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_DFPOS.u32) + u32Data * GP_OFFSET), GP0_DFPOS.u32);

    GP0_DLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_DLPOS.u32) + u32Data * GP_OFFSET));
    GP0_DLPOS.bits.disp_xlpos = stRect.u32DXL-1;
    GP0_DLPOS.bits.disp_ylpos = stRect.u32DYL-1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_DLPOS.u32) + u32Data * GP_OFFSET), GP0_DLPOS.u32);

    GP0_IRESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_IRESO.u32) + u32Data * GP_OFFSET));
    GP0_IRESO.bits.iw = stRect.u32IWth - 1;
    GP0_IRESO.bits.ih = stRect.u32IHgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_IRESO.u32) + u32Data * GP_OFFSET), GP0_IRESO.u32);

    GP0_ZME_HINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32) + u32Data * GP_OFFSET));
    GP0_ZME_HINFO.bits.out_width = stRect.u32OWth - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32) + u32Data * GP_OFFSET), GP0_ZME_HINFO.u32);

    GP0_ZME_VINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VINFO.u32) + u32Data * GP_OFFSET));
    GP0_ZME_VINFO.bits.out_height = stRect.u32OHgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VINFO.u32) + u32Data * GP_OFFSET), GP0_ZME_VINFO.u32);

    return ;
}
HI_VOID  VDP_GP_SetVideoPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_GP0_VFPOS GP0_VFPOS;
    U_GP0_VLPOS GP0_VLPOS;


    /*video position */
    GP0_VFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_VFPOS.u32) + u32Data * GP_OFFSET));
    GP0_VFPOS.bits.video_xfpos = stRect.u32X;
    GP0_VFPOS.bits.video_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_VFPOS.u32) + u32Data * GP_OFFSET), GP0_VFPOS.u32);

    GP0_VLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_VLPOS.u32) + u32Data * GP_OFFSET));
    GP0_VLPOS.bits.video_xlpos = stRect.u32X + stRect.u32Wth - 1;
    GP0_VLPOS.bits.video_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_VLPOS.u32) + u32Data * GP_OFFSET), GP0_VLPOS.u32);
    return ;
}

HI_VOID  VDP_GP_SetDispPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_GP0_DFPOS GP0_DFPOS;
    U_GP0_DLPOS GP0_DLPOS;


    /*video position */
    GP0_DFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_DFPOS.u32) + u32Data * GP_OFFSET));
    GP0_DFPOS.bits.disp_xfpos = stRect.u32X;
    GP0_DFPOS.bits.disp_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_DFPOS.u32) + u32Data * GP_OFFSET), GP0_DFPOS.u32);

    GP0_DLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_DLPOS.u32) + u32Data * GP_OFFSET));
    GP0_DLPOS.bits.disp_xlpos = stRect.u32X + stRect.u32Wth - 1;
    GP0_DLPOS.bits.disp_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_DLPOS.u32) + u32Data * GP_OFFSET), GP0_DLPOS.u32);
    return ;
}

HI_VOID  VDP_GP_SetInReso (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_GP0_IRESO GP0_IRESO;

    GP0_IRESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_IRESO.u32) + u32Data * GP_OFFSET));
    GP0_IRESO.bits.iw = stRect.u32Wth - 1;
    GP0_IRESO.bits.ih = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_IRESO.u32) + u32Data * GP_OFFSET), GP0_IRESO.u32);

    return ;
}

HI_VOID  VDP_GP_SetOutReso (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_GP0_ZME_HINFO      GP0_ZME_HINFO;
    U_GP0_ZME_VINFO      GP0_ZME_VINFO;

    GP0_ZME_HINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32) + u32Data * GP_OFFSET));
    GP0_ZME_HINFO.bits.out_width = stRect.u32Wth - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32) + u32Data * GP_OFFSET), GP0_ZME_HINFO.u32);

    GP0_ZME_VINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VINFO.u32) + u32Data * GP_OFFSET));
    GP0_ZME_VINFO.bits.out_height = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VINFO.u32) + u32Data * GP_OFFSET), GP0_ZME_VINFO.u32);
    return ;
}

HI_VOID VDP_GP_SetIpOrder (HI_U32 u32Data, HI_U32 u32Chn, VDP_GP_ORDER_E enIpOrder)
{

    U_GP0_CTRL GP0_CTRL ;

    if((u32Data == VDP_LAYER_GP0) && (u32Chn == 1))
    {
        VDP_PRINT("Error,VDP_LAYER_GP0 have no channel 1\n");
        return;
    }

    GP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32)+ u32Data * GP_OFFSET));

    if(u32Chn == 0)//channel A
    {
        if(u32Data == VDP_LAYER_GP1)
        {
            //for GP1
            GP0_CTRL.bits.ffc_sel = 0;
        }
        switch(enIpOrder)
        {
            case VDP_GP_ORDER_NULL:
                {
                    GP0_CTRL.bits.mux1_sel = 3;
                    GP0_CTRL.bits.mux2_sel = 2;
                    GP0_CTRL.bits.aout_sel = 0;
                    GP0_CTRL.bits.bout_sel = 1;

                    break;
                }
            case VDP_GP_ORDER_CSC:
                {
                    GP0_CTRL.bits.mux1_sel = 0;
                    GP0_CTRL.bits.mux2_sel = 3;
                    GP0_CTRL.bits.aout_sel = 2;
                    GP0_CTRL.bits.bout_sel = 1;

                    break;
                }
            case VDP_GP_ORDER_ZME:
                {
                    GP0_CTRL.bits.mux1_sel = 2;
                    GP0_CTRL.bits.mux2_sel = 0;
                    GP0_CTRL.bits.aout_sel = 3;
                    GP0_CTRL.bits.bout_sel = 1;

                    break;
                }
            case VDP_GP_ORDER_CSC_ZME:
                {
                    GP0_CTRL.bits.mux1_sel = 0;
                    GP0_CTRL.bits.mux2_sel = 2;
                    GP0_CTRL.bits.aout_sel = 3;
                    GP0_CTRL.bits.bout_sel = 1;

                    break;
                }
            case VDP_GP_ORDER_ZME_CSC:
                {
                    GP0_CTRL.bits.mux1_sel = 0;
                    GP0_CTRL.bits.mux2_sel = 1;
                    GP0_CTRL.bits.aout_sel = 2;
                    GP0_CTRL.bits.bout_sel = 3;
                    break;
                }
            default://null
                {
                    GP0_CTRL.bits.mux1_sel = 3;
                    GP0_CTRL.bits.mux2_sel = 2;
                    GP0_CTRL.bits.aout_sel = 0;
                    GP0_CTRL.bits.bout_sel = 1;

                    break;
                }
        }
    }
    else if(u32Chn == 1)//channel B
    {
        if(u32Data == VDP_LAYER_GP1)
        {
            //for WBC_GP0
            GP0_CTRL.bits.ffc_sel = 1;
        }
        switch(enIpOrder)
        {
            case VDP_GP_ORDER_NULL:
                {
                    GP0_CTRL.bits.mux1_sel = 3;
                    GP0_CTRL.bits.mux2_sel = 2;
                    GP0_CTRL.bits.aout_sel = 0;
                    GP0_CTRL.bits.bout_sel = 1;

                    break;
                }
            case VDP_GP_ORDER_CSC:
                {
                    GP0_CTRL.bits.mux1_sel = 1;
                    GP0_CTRL.bits.mux2_sel = 3;
                    GP0_CTRL.bits.aout_sel = 0;
                    GP0_CTRL.bits.bout_sel = 2;

                    break;
                }
            case VDP_GP_ORDER_ZME:
                {
                    GP0_CTRL.bits.mux1_sel = 2;
                    GP0_CTRL.bits.mux2_sel = 1;
                    GP0_CTRL.bits.aout_sel = 0;
                    GP0_CTRL.bits.bout_sel = 3;

                    break;
                }
            case VDP_GP_ORDER_CSC_ZME:
                {
                    GP0_CTRL.bits.mux1_sel = 0;
                    GP0_CTRL.bits.mux2_sel = 1;
                    GP0_CTRL.bits.aout_sel = 2;
                    GP0_CTRL.bits.bout_sel = 3;

                    break;
                }
            case VDP_GP_ORDER_ZME_CSC:
                {
                    GP0_CTRL.bits.mux1_sel = 0;
                    GP0_CTRL.bits.mux2_sel = 1;
                    GP0_CTRL.bits.aout_sel = 2;
                    GP0_CTRL.bits.bout_sel = 3;
                    break;
                }
            default://null
                {
                    GP0_CTRL.bits.mux1_sel = 3;
                    GP0_CTRL.bits.mux2_sel = 2;
                    GP0_CTRL.bits.aout_sel = 0;
                    GP0_CTRL.bits.bout_sel = 1;

                    break;
                }
        }
    }
    else
    {
        VDP_PRINT("Error,VDP_GP_SetIpOrder() Select Wrong GP Channel\n");
    }

    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32)+ u32Data * GP_OFFSET), GP0_CTRL.u32);
}

HI_VOID VDP_GP_SetReadMode(HI_U32 u32Data, HI_U32 u32Mode)
{
    U_GP0_CTRL GP0_CTRL;

    GP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32)+ u32Data * GP_OFFSET));
    GP0_CTRL.bits.read_mode = u32Mode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32)+ u32Data * GP_OFFSET), GP0_CTRL.u32);
}

HI_VOID  VDP_GP_SetParaUpd       (HI_U32 u32Data, VDP_GP_PARA_E enMode)
{

    U_PARA_UP_VHD PARA_UP_VHD;

    PARA_UP_VHD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32));
    PARA_UP_VHD.bits.para_up_vhd_chn16 = 0x1;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);
    return ;
}


HI_VOID  VDP_GP_SetRegUp  (HI_U32 u32Data)
{
    U_GP0_UPD GP0_UPD;

    /* GP layer register update */

    GP0_UPD.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_UPD.u32) + u32Data * GP_OFFSET), GP0_UPD.u32);

    return ;
}

HI_VOID  VDP_GP_SetLayerGalpha (HI_U32 u32Data, HI_U32 u32Alpha)
{
    U_GP0_CTRL GP0_CTRL;



    GP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32) + u32Data * GP_OFFSET));
    GP0_CTRL.bits.galpha = u32Alpha;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32) + u32Data * GP_OFFSET), GP0_CTRL.u32);
    return ;
}

HI_VOID  VDP_GP_SetLayerBkg(HI_U32 u32Data, VDP_BKG_S stBkg)
{
    U_GP0_BK GP0_BK;
    U_GP0_ALPHA     GP0_ALPHA;


    GP0_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_BK.u32) + u32Data * GP_OFFSET));
    GP0_BK.bits.vbk_y  = stBkg.u32BkgY;//0x0;  //
    GP0_BK.bits.vbk_cb = stBkg.u32BkgU;//0x200;//
    GP0_BK.bits.vbk_cr = stBkg.u32BkgV;//0x200;//
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_BK.u32) + u32Data * GP_OFFSET), GP0_BK.u32);

    GP0_ALPHA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ALPHA.u32) + u32Data * GP_OFFSET));
    GP0_ALPHA.bits.vbk_alpha = stBkg.u32BkgA;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ALPHA.u32) + u32Data * GP_OFFSET), GP0_ALPHA.u32);

    return ;
}

HI_VOID VDP_GP_SetDePreMultEnable(HI_U32 u32Data, HI_U32 bEnable)
{
    U_GP0_CTRL GP0_CTRL;

    GP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32)+ u32Data * GP_OFFSET));
    GP0_CTRL.bits.depremult_en = bEnable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_CTRL.u32)+ u32Data * GP_OFFSET), GP0_CTRL.u32);
}

HI_VOID  VDP_GP_SetCscDcCoef   (HI_U32 u32Data, VDP_CSC_DC_COEF_S pstCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");

    return ;
}

HI_VOID   VDP_GP_SetCscCoef(HI_U32 u32Data, VDP_CSC_COEF_S stCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID  VDP_GP_SetCscEnable   (HI_U32 u32Data, HI_U32 u32bCscEn)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_GP_SetCscMode(HI_U32 u32Data, VDP_CSC_MODE_E enCscMode)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_GP_SetZmeEnable  (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_GP0_ZME_HSP GP0_ZME_HSP;
    U_GP0_ZME_VSP GP0_ZME_VSP;


    /*GP zoom enable */
    if((enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_HSP.bits.hsc_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET), GP0_ZME_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_VSP.bits.vsc_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET), GP0_ZME_VSP.u32);
    }

    return ;
}

HI_VOID VDP_GP_SetZmePhase   (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_S32 s32Phase)
{
    U_GP0_ZME_HLOFFSET  GP0_ZME_HLOFFSET;
    U_GP0_ZME_HCOFFSET  GP0_ZME_HCOFFSET;
    U_GP0_ZME_VOFFSET  GP0_ZME_VOFFSET;


    /* GP zoom enable */
    if((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HLOFFSET.u32) + u32Data * GP_OFFSET));
        GP0_ZME_HLOFFSET.bits.hor_loffset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HLOFFSET.u32) + u32Data * GP_OFFSET), GP0_ZME_HLOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HCOFFSET.u32) + u32Data * GP_OFFSET));
        GP0_ZME_HCOFFSET.bits.hor_coffset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HCOFFSET.u32) + u32Data * GP_OFFSET), GP0_ZME_HCOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERB) || (enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32) + u32Data * GP_OFFSET));
        GP0_ZME_VOFFSET.bits.vbtm_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32) + u32Data * GP_OFFSET), GP0_ZME_VOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERT) || (enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32) + u32Data * GP_OFFSET));
        GP0_ZME_VOFFSET.bits.vtp_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VOFFSET.u32) + u32Data * GP_OFFSET), GP0_ZME_VOFFSET.u32);
    }

    return ;
}

HI_VOID VDP_GP_SetZmeFirEnable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_GP0_ZME_HSP        GP0_ZME_HSP;
    U_GP0_ZME_VSP        GP0_ZME_VSP;


    if((enMode == VDP_ZME_MODE_ALPHA)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_HSP.bits.hafir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET), GP0_ZME_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_HSP.bits.hfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET), GP0_ZME_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_ALPHAV)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_VSP.bits.vafir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET), GP0_ZME_VSP.u32);
    }

    if((enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_VSP.bits.vfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET), GP0_ZME_VSP.u32);
    }

    return ;
}

HI_VOID VDP_GP_SetZmeMidEnable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_GP0_ZME_HSP        GP0_ZME_HSP;
    U_GP0_ZME_VSP        GP0_ZME_VSP;


    /* VHD layer zoom enable */
    if((enMode == VDP_ZME_MODE_ALPHA)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_HSP.bits.hamid_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET), GP0_ZME_HSP.u32);
    }
    if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_HSP.bits.hlmid_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET), GP0_ZME_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_HSP.bits.hchmid_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET), GP0_ZME_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_ALPHAV)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_VSP.bits.vamid_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET), GP0_ZME_VSP.u32);
    }
    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_VSP.bits.vlmid_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET), GP0_ZME_VSP.u32);
    }

    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET));
        GP0_ZME_VSP.bits.vchmid_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET), GP0_ZME_VSP.u32);
    }

    return ;
}

HI_VOID VDP_GP_SetZmeHorRatio  (HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_GP0_ZME_HSP        GP0_ZME_HSP;


    GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET));
    GP0_ZME_HSP.bits.hratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET), GP0_ZME_HSP.u32);

    return ;
}

HI_VOID VDP_GP_SetZmeVerRatio  (HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_GP0_ZME_VSR        GP0_ZME_VSR;


    GP0_ZME_VSR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSR.u32) + u32Data * GP_OFFSET));
    GP0_ZME_VSR.bits.vratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSR.u32) + u32Data * GP_OFFSET), GP0_ZME_VSR.u32);

    return ;
}
//modify add
HI_VOID  VDP_GP_SetVfirOneTapEnable(HI_U32 u32Data, HI_U32 u32VfirOneTapEn)
{
    U_GP0_ZME_VSP GP0_ZME_VSP;


    GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET));
    GP0_ZME_VSP.bits.vfir_1tap_en = u32VfirOneTapEn;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET), GP0_ZME_VSP.u32);

    return ;
}


HI_VOID  VDP_GP_SetVfirTwoTapEnable(HI_U32 u32Data, HI_U32 u32VfirTwoTapEn)
{
    U_GP0_ZME_VSP GP0_ZME_VSP;


    GP0_ZME_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET));
    GP0_ZME_VSP.bits.vfir_2tap_en = u32VfirTwoTapEn;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_VSP.u32) + u32Data * GP_OFFSET), GP0_ZME_VSP.u32);

    return ;
}

HI_VOID VDP_GP_SetZmeCkGtEn(HI_U32 u32Data, HI_U32 ck_gt_en)
{
	U_GP0_ZME_HINFO GP0_ZME_HINFO;

    GP0_ZME_HINFO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32) + u32Data * GP_OFFSET));
    GP0_ZME_HINFO.bits.ck_gt_en = ck_gt_en;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HINFO.u32) + u32Data * GP_OFFSET), GP0_ZME_HINFO.u32);

	return ;
}

HI_VOID VDP_GP_SetZmeHfirOrder        (HI_U32 u32Data, HI_U32 u32HfirOrder)
{
    U_GP0_ZME_HSP        GP0_ZME_HSP;


    GP0_ZME_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET));
    GP0_ZME_HSP.bits.hfir_order = 1;//u32HfirOrder;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_ZME_HSP.u32) + u32Data * GP_OFFSET), GP0_ZME_HSP.u32);

    return ;
}

HI_VOID VDP_GP0_SetZmeCoefAddr  (HI_U32 u32Addr)
{
	U_PARA_ADDR_VHD_CHN16 PARA_ADDR_VHD_CHN16;

    PARA_ADDR_VHD_CHN16.bits.para_addr_vhd_chn16 = u32Addr;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN16.u32),PARA_ADDR_VHD_CHN16.u32);

    return ;
}

HI_VOID VDP_GP_SetZmeCoefAddr  (HI_U32 u32Data, HI_U32 u32Mode, HI_U32 u32Addr)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_GP_SetParaRd   (HI_U32 u32Data, VDP_GP_PARA_E enMode)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_GP_SetTiEnable(HI_U32 u32Data, HI_U32 u32Md,HI_U32 u32Data1)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID  VDP_GP_SetTiGainRatio(HI_U32 u32Data, HI_U32 u32Md, HI_S32 s32Data)
{
    DISP_INFO("98mv310 Nousing!\n");

}

HI_VOID  VDP_GP_SetTiMixRatio(HI_U32 u32Data, HI_U32 u32Md, HI_U32 u32mixing_ratio)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID  VDP_GP_SetTiHfThd(HI_U32 u32Data, HI_U32 u32Md, HI_U32 * u32TiHfThd)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID  VDP_GP_SetTiHpCoef(HI_U32 u32Data, HI_U32 u32Md, HI_S32 * s32Data)
{
    DISP_INFO("98mv310 Nousing!\n");

}

HI_VOID  VDP_GP_SetTiCoringThd(HI_U32 u32Data, HI_U32 u32Md, HI_U32 u32thd)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID  VDP_GP_SetTiSwingThd(HI_U32 u32Data, HI_U32 u32Md, HI_U32 u32thd, HI_U32 u32thd1)//have problem
{
    DISP_INFO("98mv310 Nousing!\n");

}

HI_VOID  VDP_GP_SetTiGainCoef(HI_U32 u32Data, HI_U32 u32Md, HI_U32 * u32coef)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID  VDP_GP_SetTiDefThd(HI_U32 u32Data, HI_U32 u32Md)
{
    DISP_INFO("98mv310 Nousing!\n");
}

#if 1
HI_VOID VDP_GFX_SetConnection(HI_U32 u32LayerId, HI_U32 u32Data )
{
    U_VOCTRL  VOCTRL;

	if(u32LayerId != VDP_LAYER_GFX3)
    {
        VDP_PRINT("Error, VDP_GFX_SetConnection() select wrong layer id\n");
        return ;

    }
    VOCTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VOCTRL.u32)));
    VOCTRL.bits.g3_sel = u32Data;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VOCTRL.u32)), VOCTRL.u32);

}
#endif

#if GFX_CSC_EN
HI_VOID  VDP_GFX_SetCscDcCoef   (HI_U32 u32Data, VDP_CSC_DC_COEF_S pstCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID   VDP_GFX_SetCscCoef(HI_U32 u32Data, VDP_CSC_COEF_S stCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_GFX_SetCscEnable   (HI_U32 u32Data, HI_U32 u32bCscEn)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_GFX_SetCscMode(HI_U32 u32Data, VDP_CSC_MODE_E enCscMode)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}
#endif

HI_VOID VDP_GP_SetCoefReadEnable(HI_U32 u32Id, HI_U32 u32Para)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_GP_SetCoefReadDisable(HI_U32 u32Id, HI_U32 u32Para)
{
    DISP_INFO("98mv310 Nousing!\n");
}

#endif //end of GP0_EN

HI_VOID VDP_GFX_SetMasterSel  (HI_U32 u32Data, HI_U32 u32MasterNum)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_GFX_SetDataMask    (HI_U32 u32Data, HI_U32 u32Odd, HI_U32 u32Even)
{
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.odd_data_mute  = u32Odd ;
    G0_CTRL.bits.even_data_mute = u32Even ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);

    return ;
}

HI_VOID VDP_GP_SetTwoChnEnable    (HI_U32 u32Enable)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_GP_SetOutputMode    (HI_U32 u32Mode)
{
    U_GP0_MUTE_BK GP0_MUTE_BK;

    GP0_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->GP0_MUTE_BK.u32)));
    GP0_MUTE_BK.bits.mute_en = u32Mode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->GP0_MUTE_BK.u32)), GP0_MUTE_BK.u32);
    return ;
}
//add by dcmp

HI_VOID VDP_GFX_SetDcmpLossLess(HI_U32 u32Data, HI_U32 u32bEnable)
{
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.lossless = u32bEnable ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);
}

HI_VOID VDP_GFX_SetDcmpAlphaLossLess(HI_U32 u32Data, HI_U32 u32bEnable)
{
    U_G0_CTRL G0_CTRL;


    G0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET));
    G0_CTRL.bits.lossless_a = u32bEnable ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->G0_CTRL.u32) + u32Data * GFX_OFFSET), G0_CTRL.u32);
}

HI_VOID VDP_GFX_SetDcmpCmpMode (HI_U32 u32Data, HI_U32 u32Mode)
{
    DISP_INFO("98mv310 Nousing!\n");
}
HI_VOID VDP_GFX_SetDcmpAddrMapEn (HI_U32 u32Data, HI_U32 u32Mode)
{
    VDP_FDR_GFX_SetAddrMapEn      ( u32Data * GFX_FDR_OFFSET, u32Mode);
    DISP_INFO("98mv310 Nousing!\n");
    return;
}

HI_VOID VDP_GFX_MixvBypassEn (HI_U32 u32En)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_GFX_MixvPremultEn (HI_U32 u32En)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_GFX_MixvBypassMode (HI_U32 u32Mode)
{
    DISP_INFO("98mv310 Nousing!\n");
}

HI_VOID VDP_DRV_GetGfxState(HI_BOOL *pbNeedProcessGfx)
{
    DISP_INFO("98mv310 Nousing!\n");
}

