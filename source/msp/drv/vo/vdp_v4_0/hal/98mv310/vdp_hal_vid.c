//**********************************************************************
// File Name   : vdp_driver.cpp
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
#include "vdp_hal_vid.h"
#include "vdp_hal_ip_fdr.h"
#include "vdp_hal_ip_region.h"

extern volatile S_VDP_REGS_TYPE* pVdpReg;

HI_VOID  VDP_VID_SetZmeOutReso(HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_V0_ZME_ORESO  V0_ZME_ORESO;

	V0_ZME_ORESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_ORESO.u32)));
	V0_ZME_ORESO.bits.ow = stRect.u32Wth - 1;
	V0_ZME_ORESO.bits.oh = stRect.u32Hgt - 1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_ORESO.u32)), V0_ZME_ORESO.u32);

    return ;
}
HI_VOID  VDP_VID_SetZme2OutReso(HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_V0_ZME2_ORESO  V0_ZME2_ORESO;


	V0_ZME2_ORESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME2_ORESO.u32)));
	V0_ZME2_ORESO.bits.ow = stRect.u32Wth - 1;
	V0_ZME2_ORESO.bits.oh = stRect.u32Hgt - 1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME2_ORESO.u32)), V0_ZME2_ORESO.u32);

    return ;
}

HI_VOID  VDP_VP_SetLayerEnable (HI_U32 u32Data, HI_U32 u32bEnable )
{
    U_VP0_CTRL VP0_CTRL;



    VP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_CTRL.u32) + u32Data * VID_OFFSET));
    VP0_CTRL.bits.surface_en =  u32bEnable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_CTRL.u32) + u32Data * VID_OFFSET), VP0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VP_SetUpdMode (HI_U32 u32Data, HI_U32 u32UpdMode )
{
    U_VP0_CTRL VP0_CTRL;



    VP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_CTRL.u32) + u32Data * VID_OFFSET));
    VP0_CTRL.bits.rgup_mode =  u32UpdMode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_CTRL.u32) + u32Data * VID_OFFSET), VP0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VP_SetUpdField (HI_U32 u32Data, HI_U32 u32UpdMode )
{
    U_VP0_CTRL VP0_CTRL;



    VP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_CTRL.u32) + u32Data * VID_OFFSET));
    VP0_CTRL.bits.rupd_field =  u32UpdMode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_CTRL.u32) + u32Data * VID_OFFSET), VP0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetPreReadEnable    (HI_U32 u32Data, HI_U32 u32Enable )
{
    VDP_FDR_VID_SetPreRdEn         (  u32Data * VID_FDR_OFFSET, 1); //fix cfg
     return ;
}

HI_VOID  VDP_VID_SetReqLength    (HI_U32 u32Data, HI_U32 ReqLenght )
{
    if(ReqLenght == 2)
    {
       ReqLenght = 0;
    }
 VDP_FDR_VID_SetReqLen          (  u32Data * VID_FDR_OFFSET, ReqLenght);
     return ;
}

HI_VOID  VDP_VID_SetReqMacCtrl    (HI_U32 u32Data, HI_U32 u32ReqMacCtrl )
{
#ifdef VDP_HI3798MV200
#else
    U_V0_PRERD     V0_PRERD;

    V0_PRERD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_PRERD.u32) + u32Data * VID_OFFSET));
    V0_PRERD.bits.req_mac_ctrl = u32ReqMacCtrl ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_PRERD.u32) + u32Data * VID_OFFSET), V0_PRERD.u32);
#endif

    return ;
}

HI_VOID  VDP_VID_SetUvorder(HI_U32 u32Data, HI_U32 u32bUvorder)
{
    VDP_FDR_VID_SetUvOrderEn       (  u32Data * VID_FDR_OFFSET, u32bUvorder);

    return ;
}

HI_VOID  VDP_VID_SetNoSecFlag    (HI_U32 u32Data, HI_U32 u32Enable )
{
    U_V0_CTRL  V0_CTRL;



    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.nosec_flag= u32Enable ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetZme1OutProSel(HI_U32 u32Data, HI_U32 u32OutProSel)
{
    U_V0_CTRL V0_CTRL;


    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.zme1_out_pro_sel =  u32OutProSel;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetAddBufSwEn(HI_U32 u32Data, HI_U32 add_buf_sw_en)
{
    U_V0_CTRL V0_CTRL;


    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.add_buf_sw_en =  add_buf_sw_en;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetAddBufSwSel(HI_U32 u32Data, HI_U32 add_buf_sw_sel)
{
    U_V0_CTRL V0_CTRL;


    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.add_buf_sw_sel =  add_buf_sw_sel;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetZme1ReduceTap(HI_U32 u32Data, HI_U32 zme1_reduce_tap)
{
    U_V0_CTRL V0_CTRL;


    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.zme1_reduce_tap =  zme1_reduce_tap;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetZme2ReduceTap(HI_U32 u32Data, HI_U32 zme2_reduce_tap)
{
    U_V0_CTRL V0_CTRL;


    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.zme2_reduce_tap = zme2_reduce_tap ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetV0LinkCtrl (HI_U32 u32Data, HI_U32 u32LinkCtrl)
{
    U_LINK_CTRL0 LINK_CTRL0;


    LINK_CTRL0.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->LINK_CTRL0.u32)));
    LINK_CTRL0.bits.v0_link_ctrl =  u32LinkCtrl;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->LINK_CTRL0.u32)), LINK_CTRL0.u32);

    return ;
}

HI_VOID  VDP_VID_SetLayerEnable    (HI_U32 u32Data, HI_U32 u32bEnable )
{
    U_V0_CTRL V0_CTRL;
    //U_V0_16REGIONENL V0_16REGIONENL;


    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    if(u32Data == VDP_LAYER_VID3)
        V0_CTRL.bits.surface_en = 0;
    else
        V0_CTRL.bits.surface_en = u32bEnable ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetFiLayerEnable    (HI_U32 u32Data, HI_U32 u32bEnable )
{
    U_V0_CTRL V0_CTRL;


    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.surface_c_en = u32bEnable ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetFiVscale    (HI_U32 u32Data, HI_U32 u32bFiVscale )
{
    U_V0_CTRL V0_CTRL;


    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.fi_vscale = u32bFiVscale ;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID VDP_VID_SetTileStride (HI_U32 u32Data, HI_U32 u32LStr, HI_U32 u32CStr)
{
    VDP_FDR_VID_SetChmTileStride   ( u32Data * VID_FDR_OFFSET,  u32CStr );
    VDP_FDR_VID_SetLmTileStride    ( u32Data * VID_FDR_OFFSET,  u32LStr );
     return ;
}

HI_VOID  VDP_VID_SetLayerAddr   (HI_U32 u32Data, HI_U32 u32Chan, HI_U32 u32LAddr,HI_U32 u32CAddr,HI_U32 u32LStr, HI_U32 u32CStr)
{
    if(u32Chan == 0)
    {
        VDP_FDR_VID_SetVhdaddrL        (  u32Data * VID_FDR_OFFSET,  u32LAddr);
        VDP_FDR_VID_SetVhdcaddrL       (  u32Data * VID_FDR_OFFSET,  u32CAddr);
    }
    else if(u32Chan == 1)
    {
        VDP_FDR_VID_SetVhdnaddrL       (  u32Data * VID_FDR_OFFSET,  u32LAddr);
        VDP_FDR_VID_SetVhdncaddrL      (  u32Data * VID_FDR_OFFSET,  u32CAddr);
        VDP_FDR_VID_SetBVhdaddrL       (  u32Data * VID_FDR_OFFSET,  u32LAddr );
        VDP_FDR_VID_SetBVhdcaddrL      (  u32Data * VID_FDR_OFFSET,  u32CAddr );
    }
    else
    {
        VDP_PRINT("Error,VDP_VID_SetLayerAddr() Select Wrong Addr ID\n");
    }
    VDP_FDR_VID_SetChmStride       (  u32Data * VID_FDR_OFFSET, u32CStr );
    VDP_FDR_VID_SetLmStride        (  u32Data * VID_FDR_OFFSET, u32LStr );

     return ;
}

HI_VOID  VDP_VID_SetHeadAddr   (HI_U32 u32Data, HI_U32 u32LHeadAddr,HI_U32 u32CHeadAddr)
{
    VDP_FDR_VID_SetHVhdaddrL       ( u32Data * VID_FDR_OFFSET,  u32LHeadAddr );
    VDP_FDR_VID_SetHVhdcaddrL      ( u32Data * VID_FDR_OFFSET,  u32CHeadAddr );
     return ;
}

HI_VOID  VDP_VID_SetHeadSize   (HI_U32 u32Data, HI_U32 u32HeadSize)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_VID_SetHeadStride  (HI_U32 u32Data, HI_U32 u32HeadStride)
{
    VDP_FDR_VID_SetChmHeadStride   ( u32Data * VID_FDR_OFFSET, u32HeadStride );
    VDP_FDR_VID_SetLmHeadStride    ( u32Data * VID_FDR_OFFSET, u32HeadStride );
     return ;
}

HI_VOID  VDP_VID_SetLayerReso     (HI_U32 u32Data, VDP_DISP_RECT_S  stRect)
{
    U_V0_VFPOS V0_VFPOS;
    U_V0_VLPOS V0_VLPOS;
    U_V0_DFPOS V0_DFPOS;
    U_V0_DLPOS V0_DLPOS;
    U_V0_ZME_ORESO  V0_ZME_ORESO;


    VDP_FDR_VID_SetMrgYpos       (  0 * REGION_FDR_OFFSET, stRect.u32VY);
    VDP_FDR_VID_SetMrgXpos       (  0 * REGION_FDR_OFFSET, stRect.u32VX);
    VDP_FDR_VID_SetMrgHeight     (  0 * REGION_FDR_OFFSET, stRect.u32IHgt - 1);
    VDP_FDR_VID_SetMrgWidth      (  0 * REGION_FDR_OFFSET, stRect.u32IWth - 1);
    VDP_FDR_VID_SetMrgSrcHeight  (  0 * REGION_FDR_OFFSET, stRect.u32IHgt - 1);
    VDP_FDR_VID_SetMrgSrcWidth   (  0 * REGION_FDR_OFFSET, stRect.u32IWth - 1);
    VDP_FDR_VID_SetMrgSrcVoffset (  0 * REGION_FDR_OFFSET, 0);
    VDP_FDR_VID_SetMrgSrcHoffset (  0 * REGION_FDR_OFFSET, 0);
    VDP_FDR_VID_SetMrgCropEn     (  0 * REGION_FDR_OFFSET, 0);

    VDP_FDR_VID_SetIresoH          (  u32Data * VID_FDR_OFFSET, stRect.u32IHgt - 1);
    VDP_FDR_VID_SetIresoW          (  u32Data * VID_FDR_OFFSET, stRect.u32IWth - 1);
    VDP_FDR_VID_SetSrcCropY        (  u32Data * VID_FDR_OFFSET, 0);
    VDP_FDR_VID_SetSrcCropX        (  u32Data * VID_FDR_OFFSET, 0);
    VDP_FDR_VID_SetSrcH            (  u32Data * VID_FDR_OFFSET, stRect.u32IHgt - 1);
    VDP_FDR_VID_SetSrcW            (  u32Data * VID_FDR_OFFSET, stRect.u32IWth - 1);



    /*video position */
    V0_VFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VFPOS.u32) + u32Data * VID_OFFSET));
    V0_VFPOS.bits.video_xfpos = stRect.u32VX;
    V0_VFPOS.bits.video_yfpos = stRect.u32VY;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VFPOS.u32) + u32Data * VID_OFFSET), V0_VFPOS.u32);

    V0_VLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VLPOS.u32) + u32Data * VID_OFFSET));
    V0_VLPOS.bits.video_xlpos = stRect.u32VX + stRect.u32OWth - 1;
    V0_VLPOS.bits.video_ylpos = stRect.u32VY + stRect.u32OHgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VLPOS.u32) + u32Data * VID_OFFSET), V0_VLPOS.u32);

    V0_DFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_DFPOS.u32) + u32Data * VID_OFFSET));
    V0_DFPOS.bits.disp_xfpos = stRect.u32DXS;
    V0_DFPOS.bits.disp_yfpos = stRect.u32DYS;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_DFPOS.u32) + u32Data * VID_OFFSET), V0_DFPOS.u32);

    V0_DLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_DLPOS.u32) + u32Data * VID_OFFSET));
    V0_DLPOS.bits.disp_xlpos = stRect.u32DXL-1;
    V0_DLPOS.bits.disp_ylpos = stRect.u32DYL-1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_DLPOS.u32) + u32Data * VID_OFFSET), V0_DLPOS.u32);

	V0_ZME_ORESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_ORESO.u32) + u32Data * VID_OFFSET));
	V0_ZME_ORESO.bits.ow = stRect.u32OWth-1;
	V0_ZME_ORESO.bits.oh = stRect.u32OHgt-1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_ORESO.u32) + u32Data * VID_OFFSET), V0_ZME_ORESO.u32);

     return ;
}

HI_VOID  VDP_VID_SetInDataFmt       (HI_U32 u32Data, VDP_VID_IFMT_E  enDataFmt)
{

    if(u32Data == VDP_LAYER_VID1)
    {
        VDP_FDR_VID_SetDataFmt         (  u32Data * VID_FDR_OFFSET, 0);
        VDP_FDR_VID_SetDataType        (  u32Data * VID_FDR_OFFSET, 3);
    }
    else
    {
        if((enDataFmt == VDP_VID_IFMT_SP_TILE_64) || (enDataFmt == VDP_VID_IFMT_SP_TILE))
        {
            VDP_FDR_VID_SetDataFmt         (  u32Data * VID_FDR_OFFSET, 1);
            VDP_FDR_VID_SetDataType        (  u32Data * VID_FDR_OFFSET, 2);
        }
        else if(enDataFmt == VDP_VID_IFMT_SP_420)
        {
            VDP_FDR_VID_SetDataFmt         (  u32Data * VID_FDR_OFFSET, 0);
            VDP_FDR_VID_SetDataType        (  u32Data * VID_FDR_OFFSET, 2);
        }
        else if(enDataFmt == VDP_VID_IFMT_SP_422)
        {
            VDP_FDR_VID_SetDataFmt         (  u32Data * VID_FDR_OFFSET, 0);
            VDP_FDR_VID_SetDataType        (  u32Data * VID_FDR_OFFSET, 3);
        }
        else if(enDataFmt == VDP_VID_IFMT_SP_444)
        {
            VDP_FDR_VID_SetDataFmt         (  u32Data * VID_FDR_OFFSET, 0);
            VDP_FDR_VID_SetDataType        (  u32Data * VID_FDR_OFFSET, 4);
        }
        else if(enDataFmt == VDP_VID_IFMT_SP_400)
        {
            VDP_FDR_VID_SetDataFmt         (  u32Data * VID_FDR_OFFSET, 0);
            VDP_FDR_VID_SetDataType        (  u32Data * VID_FDR_OFFSET, 1);
        }
        else if(enDataFmt == VDP_VID_IFMT_PKG_444)
        {
            VDP_FDR_VID_SetDataFmt         (  u32Data * VID_FDR_OFFSET, 2);
            VDP_FDR_VID_SetDataType        (  u32Data * VID_FDR_OFFSET, 4);
        }
        else if(enDataFmt == VDP_VID_IFMT_PKG_888)
        {
            VDP_FDR_VID_SetDataFmt         (  u32Data * VID_FDR_OFFSET, 2);
            VDP_FDR_VID_SetDataType        (  u32Data * VID_FDR_OFFSET, 5);
        }
        else if(enDataFmt == VDP_VID_IFMT_PKG_8888)
        {
            VDP_FDR_VID_SetDataFmt         (  u32Data * VID_FDR_OFFSET, 2);
            VDP_FDR_VID_SetDataType        (  u32Data * VID_FDR_OFFSET, 6);
        }
        else
        {

        }
    }
     return ;
}

HI_VOID  VDP_VID_SetDataWidth    (HI_U32 u32Data, HI_U32 DataWidth)
{
    if(DataWidth == VDP_DATA_WTH_10_CTS)
    {
        DataWidth = 3;
    }
    VDP_FDR_VID_SetDataWidth       (  u32Data * VID_FDR_OFFSET, DataWidth );
     return ;
}

HI_VOID  VDP_VID_SetReadMode    (HI_U32 u32Data, VDP_DATA_RMODE_E enLRMode,VDP_DATA_RMODE_E enCRMode)
{
    VDP_FDR_VID_SetLmRmode         (  u32Data * VID_FDR_OFFSET,  enLRMode);
    VDP_FDR_VID_SetChmRmode        (  u32Data * VID_FDR_OFFSET,  enCRMode);
     return ;
}

HI_VOID  VDP_VID_SetFlipEnable(HI_U32 u32Data, HI_U32 u32bEnable)
{
    VDP_FDR_VID_SetFlipEn          (  u32Data * VID_FDR_OFFSET, 0);
     return;
}

HI_VOID  VDP_VID_SetInReso      (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    VDP_FDR_VID_SetIresoH          (  u32Data * VID_FDR_OFFSET, stRect.u32Hgt-1);
    VDP_FDR_VID_SetIresoW          (  u32Data * VID_FDR_OFFSET, stRect.u32Wth-1);
    VDP_FDR_VID_SetSrcCropY        (  u32Data * VID_FDR_OFFSET, 0);
    VDP_FDR_VID_SetSrcCropX        (  u32Data * VID_FDR_OFFSET, 0);
    VDP_FDR_VID_SetSrcH            (  u32Data * VID_FDR_OFFSET, stRect.u32Hgt-1);
    VDP_FDR_VID_SetSrcW            (  u32Data * VID_FDR_OFFSET, stRect.u32Wth-1);
     return ;
}

HI_VOID  VDP_VID_SetOutReso     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_V0_ZME_ORESO  V0_ZME_ORESO;

	V0_ZME_ORESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_ORESO.u32) + u32Data * VID_OFFSET));
	V0_ZME_ORESO.bits.ow = stRect.u32Wth - 1;
	V0_ZME_ORESO.bits.oh = stRect.u32Hgt - 1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_ORESO.u32) + u32Data * VID_OFFSET), V0_ZME_ORESO.u32);
     return ;
}

HI_VOID  VDP_VID_SetVideoPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_V0_VFPOS V0_VFPOS;
    U_V0_VLPOS V0_VLPOS;

    /*video position */
    V0_VFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VFPOS.u32) + u32Data * VID_OFFSET));
    V0_VFPOS.bits.video_xfpos = stRect.u32X;
    V0_VFPOS.bits.video_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VFPOS.u32) + u32Data * VID_OFFSET), V0_VFPOS.u32);

    V0_VLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VLPOS.u32) + u32Data * VID_OFFSET));
    V0_VLPOS.bits.video_xlpos = stRect.u32X + stRect.u32Wth - 1;
    V0_VLPOS.bits.video_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VLPOS.u32) + u32Data * VID_OFFSET), V0_VLPOS.u32);
    return ;
}

HI_VOID  VDP_VID_SetDispPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_V0_DFPOS V0_DFPOS;
    U_V0_DLPOS V0_DLPOS;

    /*video position */
    V0_DFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_DFPOS.u32) + u32Data * VID_OFFSET));
    V0_DFPOS.bits.disp_xfpos = stRect.u32X;
    V0_DFPOS.bits.disp_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_DFPOS.u32) + u32Data * VID_OFFSET), V0_DFPOS.u32);

    V0_DLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_DLPOS.u32) + u32Data * VID_OFFSET));
    V0_DLPOS.bits.disp_xlpos = stRect.u32X + stRect.u32Wth - 1;
    V0_DLPOS.bits.disp_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_DLPOS.u32) + u32Data * VID_OFFSET), V0_DLPOS.u32);
    return ;
}

HI_VOID VDP_VID_SetSrOutReso (HI_U32 u32Data, VDP_RECT_S stRect)
{
    U_V0_ZME2_ORESO  V0_ZME2_ORESO;

	V0_ZME2_ORESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME2_ORESO.u32) + u32Data * VID_OFFSET));
	V0_ZME2_ORESO.bits.ow = stRect.u32Wth - 1;
	V0_ZME2_ORESO.bits.oh = stRect.u32Hgt - 1;
	VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME2_ORESO.u32) + u32Data * VID_OFFSET), V0_ZME2_ORESO.u32);

 }

//#if DCMP_EN
HI_VOID  VDP_VID_SetDcmpEnable    (HI_U32 u32Data, HI_U32 u32bEnable )
{
    return ;
}

HI_VOID  VDP_VID_SetTileDcmpEnable    (HI_U32 u32Data, HI_U32 u32bEnable )
{

    HI_U32 u32DcmpType = u32bEnable;
    VDP_FDR_VID_SetDcmpType        (  u32Data * VID_FDR_OFFSET, u32DcmpType);

    return ;
}

HI_VOID  VDP_VID_SetDcmpErrorClr    (HI_U32 u32Data,HI_U32 u32dcmp_lerror_clr,HI_U32  u32dcmp_cerror_clr)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_VID_SetDcmpHeadErrClr    (HI_U32 u32Data,HI_U32 u32dcmp_lerror_clr,HI_U32  u32dcmp_cerror_clr)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_VID_SetDcmpConsumeErrClr    (HI_U32 u32Data,HI_U32 u32dcmp_lerror_clr,HI_U32  u32dcmp_cerror_clr)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_VID_SetDcmpForgiveErrClr    (HI_U32 u32Data,HI_U32 u32dcmp_lerror_clr,HI_U32  u32dcmp_cerror_clr)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}
//#endif

HI_VOID VDP_VID_SetIfirMode(HI_U32 u32Data, VDP_IFIRMODE_E enMode)
{
    U_V0_HFIR_CTRL V0_HFIR_CTRL;


    V0_HFIR_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HFIR_CTRL.u32) + u32Data * VID_HFIR_OFFSET));
    V0_HFIR_CTRL.bits.hfir_mode = enMode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HFIR_CTRL.u32) + u32Data * VID_HFIR_OFFSET), V0_HFIR_CTRL.u32);
     return ;
}

HI_VOID VDP_VID_SetIfirEn(HI_U32 u32Data, HI_U32 u32En)
{
    U_V1_HFIR_CTRL V1_HFIR_CTRL;


    V1_HFIR_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V1_HFIR_CTRL.u32) + 0 * VID_HFIR_OFFSET));
    V1_HFIR_CTRL.bits.hfir_en    = u32En;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V1_HFIR_CTRL.u32) + 0 * VID_HFIR_OFFSET), V1_HFIR_CTRL.u32);
    return ;
}

HI_VOID VDP_VID_SetIfirMidEn(HI_U32 u32Data, HI_U32 u32En)
{
    U_V0_HFIR_CTRL V0_HFIR_CTRL;

    V0_HFIR_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HFIR_CTRL.u32) + u32Data * VID_HFIR_OFFSET));
    V0_HFIR_CTRL.bits.mid_en    = u32En;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HFIR_CTRL.u32) + u32Data * VID_HFIR_OFFSET), V0_HFIR_CTRL.u32);
    return ;
}

HI_VOID VDP_VID_SetIfirCkGtEn(HI_U32 u32Data, HI_U32 u32En)
{
    U_V0_HFIR_CTRL V0_HFIR_CTRL;

    V0_HFIR_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HFIR_CTRL.u32) + u32Data * VID_HFIR_OFFSET));
    V0_HFIR_CTRL.bits.ck_gt_en  = u32En;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HFIR_CTRL.u32) + u32Data * VID_HFIR_OFFSET), V0_HFIR_CTRL.u32);
    return ;
}

HI_VOID  VDP_VID_SetIfirCoef    (HI_U32 u32Data, HI_S32 * s32Coef)
{
    U_V0_IFIRCOEF01 V0_IFIRCOEF01;
    U_V0_IFIRCOEF23 V0_IFIRCOEF23;
    U_V0_IFIRCOEF45 V0_IFIRCOEF45;
    U_V0_IFIRCOEF67 V0_IFIRCOEF67;

    V0_IFIRCOEF01.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_IFIRCOEF01.u32) + u32Data * VID_HFIR_OFFSET));
    V0_IFIRCOEF23.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_IFIRCOEF23.u32) + u32Data * VID_HFIR_OFFSET));
    V0_IFIRCOEF45.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_IFIRCOEF45.u32) + u32Data * VID_HFIR_OFFSET));
    V0_IFIRCOEF67.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_IFIRCOEF67.u32) + u32Data * VID_HFIR_OFFSET));

    if(u32Data == VDP_LAYER_VID0)
    {
        V0_IFIRCOEF01.bits.coef0 = s32Coef[0];
        V0_IFIRCOEF01.bits.coef1 = s32Coef[1];
        V0_IFIRCOEF23.bits.coef2 = s32Coef[2];
        V0_IFIRCOEF23.bits.coef3 = s32Coef[3];
        V0_IFIRCOEF45.bits.coef4 = s32Coef[4];
        V0_IFIRCOEF45.bits.coef5 = s32Coef[5];
        V0_IFIRCOEF67.bits.coef6 = s32Coef[6];
        V0_IFIRCOEF67.bits.coef7 = s32Coef[7];
    }
    else
    {
        V0_IFIRCOEF01.bits.coef0 = s32Coef[7];
        V0_IFIRCOEF01.bits.coef1 = s32Coef[6];
        V0_IFIRCOEF23.bits.coef2 = s32Coef[2];
        V0_IFIRCOEF23.bits.coef3 = s32Coef[3];
        V0_IFIRCOEF45.bits.coef4 = s32Coef[4];
        V0_IFIRCOEF45.bits.coef5 = s32Coef[5];
        V0_IFIRCOEF67.bits.coef6 = s32Coef[0];
        V0_IFIRCOEF67.bits.coef7 = s32Coef[1];
    }

    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_IFIRCOEF01.u32) + u32Data * VID_HFIR_OFFSET), V0_IFIRCOEF01.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_IFIRCOEF23.u32) + u32Data * VID_HFIR_OFFSET), V0_IFIRCOEF23.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_IFIRCOEF45.u32) + u32Data * VID_HFIR_OFFSET), V0_IFIRCOEF45.u32);
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_IFIRCOEF67.u32) + u32Data * VID_HFIR_OFFSET), V0_IFIRCOEF67.u32);

    return ;
}

HI_VOID  VDP_VID_SetLayerGalpha (HI_U32 u32Data, HI_U32 u32Alpha0)
{
    U_V0_CTRL V0_CTRL;

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.galpha = u32Alpha0;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);
    return ;
}

HI_VOID  VDP_VID_SetCropReso    (HI_U32 u32Data, VDP_RECT_S stRect)
{
    HI_U32 u32SrcWth = ((VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_IN_RESO.u32) + u32Data * VID_FDR_OFFSET))) & 0xffff) + 1 + stRect.u32X;
    HI_U32 u32SrcHgt = (((VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_IN_RESO.u32) + u32Data * VID_FDR_OFFSET))) >> 16) & 0xffff) + 1 + 0;
    VDP_FDR_VID_SetSrcCropY        (  u32Data * VID_FDR_OFFSET, 0);
    VDP_FDR_VID_SetSrcCropX        (  u32Data * VID_FDR_OFFSET, stRect.u32X);
    VDP_FDR_VID_SetSrcH            (  u32Data * VID_FDR_OFFSET, u32SrcHgt - 1);
    VDP_FDR_VID_SetSrcW            (  u32Data * VID_FDR_OFFSET, u32SrcWth - 1);
    return ;
}

HI_VOID  VDP_VID_SetLayerBkg    (HI_U32 u32Data, VDP_BKG_S stBkg)
{
    U_V0_BK    V0_BK;
    U_V0_ALPHA V0_ALPHA;

    V0_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_BK.u32) + u32Data * VID_OFFSET));
    V0_BK.bits.vbk_y  = stBkg.u32BkgY;
    V0_BK.bits.vbk_cb = stBkg.u32BkgU;
    V0_BK.bits.vbk_cr = stBkg.u32BkgV;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_BK.u32) + u32Data * VID_OFFSET), V0_BK.u32);

    V0_ALPHA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ALPHA.u32) + u32Data * VID_OFFSET));
    V0_ALPHA.bits.vbk_alpha = stBkg.u32BkgA;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ALPHA.u32) + u32Data * VID_OFFSET), V0_ALPHA.u32);

    return;
}

HI_VOID  VDP_VID_SetMuteEnable   (HI_U32 u32Data, HI_U32 bEnable)
{
    U_V0_MUTE_BK   V0_MUTE_BK;

    V0_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MUTE_BK.u32) + u32Data * VID_OFFSET));
    V0_MUTE_BK.bits.mute_en = bEnable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MUTE_BK.u32) + u32Data * VID_OFFSET), V0_MUTE_BK.u32);
    return ;
}

HI_VOID  VDP_VID_SetMuteBkg    (HI_U32 u32Data, VDP_BKG_S stMuteBkg)
{
    U_V0_MUTE_BK   V0_MUTE_BK;

    V0_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_MUTE_BK.u32) + u32Data * VID_OFFSET));
    V0_MUTE_BK.bits.mute_y  = stMuteBkg.u32BkgY;
    V0_MUTE_BK.bits.mute_cb = stMuteBkg.u32BkgU;
    V0_MUTE_BK.bits.mute_cr = stMuteBkg.u32BkgV;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_MUTE_BK.u32) + u32Data * VID_OFFSET), V0_MUTE_BK.u32);

    return ;
}


HI_VOID  VDP_SetParaUpMode(HI_U32 u32Data,HI_U32 u32Mode)
{
    U_V0_CTRL V0_CTRL;

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.vup_mode = u32Mode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_SetParaUpField (HI_U32 u32Data,HI_U32 u32Mode)
{
    U_V0_CTRL V0_CTRL;

    V0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET));
    V0_CTRL.bits.rupd_field = u32Mode;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_CTRL.u32) + u32Data * VID_OFFSET), V0_CTRL.u32);

    return ;
}

HI_VOID  VDP_VID_SetCscDcCoef   (HI_U32 u32Data, VDP_CSC_DC_COEF_S pstCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID   VDP_VID_SetCscCoef(HI_U32 u32Data, VDP_CSC_COEF_S stCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_VID_SetCscEnable   (HI_U32 u32Data, HI_U32 u32bCscEn)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_VID_SetCscMode(HI_U32 u32Data, VDP_CSC_MODE_E enCscMode)

{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_VID_SetDispMode(HI_U32 u32Data, VDP_DISP_MODE_E enDispMode)
{
    return ;
}

HI_VOID VDP_VID_SetDrawMode (HI_U32 u32Data, HI_U32 u32ModeLuma, HI_U32 u32ModeChroma)
{
    VDP_FDR_VID_SetLmDrawMode      (  u32Data * VID_FDR_OFFSET, u32ModeLuma);
    VDP_FDR_VID_SetChmDrawMode     (  u32Data * VID_FDR_OFFSET, u32ModeChroma);
     return;
}

HI_VOID VDP_VID_SetDrawPixelMode (HI_U32 u32Data, HI_U32 u32DrawPixelMode)
{
    VDP_FDR_VID_SetDrawPixelMode   (  u32Data * VID_FDR_OFFSET, u32DrawPixelMode);
     return ;
}

HI_VOID VDP_VID_SetReqCtrl(HI_U32 u32Data, HI_U32 u32ReqCtrl)
{
    VDP_FDR_VID_SetReqCtrl         (  u32Data * VID_FDR_OFFSET, u32ReqCtrl);
     return ;
}

HI_VOID VDP_VID_SetMultiModeEnable(HI_U32 u32Data, HI_U32 u32Enable )
{
    VDP_FDR_VID_SetMrgEnable       (  u32Data * VID_FDR_OFFSET, u32Enable);
     return ;
}

HI_VOID VDP_VID_SetRegionCoefAddr(HI_U32 u32Addr)
{
    U_PARA_ADDR_VHD_CHN19 PARA_ADDR_VHD_CHN19;
    PARA_ADDR_VHD_CHN19.bits.para_addr_vhd_chn19 = u32Addr;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN19.u32),PARA_ADDR_VHD_CHN19.u32);
    return;
}

HI_VOID VDP_VID_SetShpCoefAddr(HI_U32 u32Addr)
{
    U_PARA_ADDR_VHD_CHN04 PARA_ADDR_VHD_CHN04;
    PARA_ADDR_VHD_CHN04.bits.para_addr_vhd_chn04 = u32Addr;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN04.u32),PARA_ADDR_VHD_CHN04.u32);
    return;
}
HI_VOID VDP_VID_SetRegionParaUp(HI_U32 u32ParaUp)
{
    U_PARA_UP_VHD PARA_UP_VHD;

    PARA_UP_VHD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32));
    PARA_UP_VHD.bits.para_up_vhd_chn19 = u32ParaUp;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);
    return;
}

HI_VOID VDP_VID_SetShpParaUp(HI_U32 u32ParaUp)
{
    U_PARA_UP_VHD PARA_UP_VHD;

    PARA_UP_VHD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32));
    PARA_UP_VHD.bits.para_up_vhd_chn04 = u32ParaUp;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);
    return;
}

HI_VOID VDP_VID_SetRegionEnable(HI_U32 u32Data, HI_U32 u32Num, HI_U32 u32bEnable )
{
    VDP_FDR_VID_SetMrgEn         (  u32Num * REGION_FDR_OFFSET, u32bEnable );
    return ;
}

HI_VOID VDP_VID_SetAllRegionDisable(HI_U32 u32Data )
{
    HI_U32           u32Num;
    for(u32Num=0; u32Num<VID_REGION_NUM; u32Num++)
    {
        VDP_FDR_VID_SetMrgEn         (  u32Num * REGION_FDR_OFFSET, 0 );
    }
    return ;
}

HI_BOOL VDP_VID_CheckRegionState(HI_U32 u32Data)
{
    HI_U32  u32RegValue = 0;
    U_V1_MRG_WORK_EN      V1_MRG_WORK_EN;

    V1_MRG_WORK_EN.u32   =   VDP_RegRead((HI_ULONG)&(pVdpReg->V1_MRG_WORK_EN.u32));
	u32RegValue     |= V1_MRG_WORK_EN.bits.work_en;

	if (u32RegValue)
	{
		return HI_TRUE;
	}
	else
	{
		return HI_FALSE;
	}
}

HI_BOOL VDP_VID_CheckLastRegionState(HI_U32 u32Data)
{
    HI_U32  u32RegValue = 0;

    u32RegValue   =   *(HI_U32*)&(pVdpReg->V1_MRG_WORK_EN.u32);

    if (u32RegValue == (1<<u32Data))
    {
        return HI_TRUE;
    }
    return HI_FALSE;
}

HI_VOID VDP_VID_SetRegionAddr(HI_U32 u32Data, HI_U32 u32Num, HI_U32 u32LAddr,HI_U32 u32CAddr,HI_U32 u32LStr, HI_U32 u32CStr)
{
    VDP_FDR_VID_SetMrgYAddr      (  u32Num * REGION_FDR_OFFSET, u32LAddr );
    VDP_FDR_VID_SetMrgCAddr      (  u32Num * REGION_FDR_OFFSET, u32CAddr );
    VDP_FDR_VID_SetMrgYStride    (  u32Num * REGION_FDR_OFFSET, u32LStr );
    VDP_FDR_VID_SetMrgCStride    (  u32Num * REGION_FDR_OFFSET, u32CStr );
    return ;
}

HI_VOID VDP_VID_SetRegionReso(HI_U32 u32Data, HI_U32 u32Num, VDP_RECT_S  stRect)
{
    VDP_FDR_VID_SetMrgYpos       (  u32Num * REGION_FDR_OFFSET, stRect.u32Y);
    VDP_FDR_VID_SetMrgXpos       (  u32Num * REGION_FDR_OFFSET, stRect.u32X);
    VDP_FDR_VID_SetMrgHeight     (  u32Num * REGION_FDR_OFFSET, stRect.u32Hgt - 1);
    VDP_FDR_VID_SetMrgWidth      (  u32Num * REGION_FDR_OFFSET, stRect.u32Wth - 1);
    VDP_FDR_VID_SetMrgSrcHeight  (  u32Num * REGION_FDR_OFFSET, stRect.u32Hgt - 1);
    VDP_FDR_VID_SetMrgSrcWidth   (  u32Num * REGION_FDR_OFFSET, stRect.u32Wth - 1);
    VDP_FDR_VID_SetMrgSrcVoffset (  u32Num * REGION_FDR_OFFSET, 0);
    VDP_FDR_VID_SetMrgSrcHoffset (  u32Num * REGION_FDR_OFFSET, 0);
    VDP_FDR_VID_SetMrgCropEn     (  u32Num * REGION_FDR_OFFSET, 0);
    return ;
}

HI_VOID VDP_VID_SetRegionMuteEnable(HI_U32 u32Data, HI_U32 u32Num, HI_U32 bEnable)
{
    VDP_FDR_VID_SetMrgMuteEn     ( u32Num * REGION_FDR_OFFSET, bEnable);
    return ;
}

HI_VOID  VDP_VID_SetRegUp       (HI_U32 u32Data)
{
    U_V0_UPD V0_UPD;

    /* VHD layer register update */

    V0_UPD.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_UPD.u32) + u32Data * VID_OFFSET), V0_UPD.u32);

    return ;
}

///////////////////////////////////
//ZME BEGIN
///////////////////////////////////
HI_VOID  VDP_VID_SetZmeEnable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;


    /* VHD layer zoom enable */
    if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hlmsc_en = u32bEnable;
        V0_HSP.bits.hlfir_en = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hchmsc_en = u32bEnable;
        V0_HSP.bits.hchfir_en = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
    }
#if 1
    if((enMode == VDP_ZME_MODE_NONL)||(enMode == VDP_ZME_MODE_ALL))
    {
		V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32)));
        V0_HSP.bits.non_lnr_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32)), V0_HSP.u32);
    }
#endif

    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vlmsc_en = u32bEnable;
        V0_VSP.bits.vlfir_en = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }

    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vchmsc_en = u32bEnable;
        V0_VSP.bits.vchfir_en = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }

    if(u32Data == VDP_LAYER_VID1)
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hlmsc_en = 0;
        V0_HSP.bits.hlfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hchmsc_en = 0;
        V0_HSP.bits.hchfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vlmsc_en = 0;
        V0_VSP.bits.vlfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vchmsc_en = 0;
        V0_VSP.bits.vchfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }

#ifdef VDP_HI3798MV200T
#else
    if(u32Data == VDP_LAYER_VID1)
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hlmsc_en = 0;
        V0_HSP.bits.hlfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hchmsc_en = 0;
        V0_HSP.bits.hchfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vlmsc_en = 0;
        V0_VSP.bits.vlfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }
#endif

#ifdef VDP_HI3798CV200
    if(u32Data == VDP_LAYER_VID3)
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hlmsc_en = 0;
        V0_HSP.bits.hlfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hchmsc_en = 0;
        V0_HSP.bits.hchfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vlmsc_en = 0;
        V0_VSP.bits.vlfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vchmsc_en = 0;
        V0_VSP.bits.vchfir_en = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }
#endif

    return;
}

HI_VOID  VDP_VID_SetVtapReduce   (HI_U32 u32Data, HI_U32 u32bEnable)
{
    U_V0_VSP V0_VSP;


        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
#ifdef VDP_HI3798MV200
        V0_VSP.bits.vtap_reduce = 0;
#else
        V0_VSP.bits.vtap_reduce = u32bEnable;
#endif
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZmeShootCtrlEnable  (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_U32 u32bEnable,HI_U32 u32bMode)
{
    U_V0_ZME_SHOOTCTRL_HL V0_ZME_SHOOTCTRL_HL;
    U_V0_ZME_SHOOTCTRL_HC V0_ZME_SHOOTCTRL_HC;
    U_V0_ZME_SHOOTCTRL_VL V0_ZME_SHOOTCTRL_VL;
    U_V0_ZME_SHOOTCTRL_VC V0_ZME_SHOOTCTRL_VC;



    if(u32Data != VDP_LAYER_VID0)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeShootCtrlEnable() Select Wrong Video Layer ID\n");
        return;
    }

    /* VHD layer zoom enable */
    if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_HL.bits.hl_shootctrl_en   = u32bEnable;
        V0_ZME_SHOOTCTRL_HL.bits.hl_shootctrl_mode = 0;
        //V0_ZME_SHOOTCTRL_HL.bits.hl_shootctrl_mode = u32bMode;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_HL.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_HC.bits.hc_shootctrl_en   = u32bEnable;
//         V0_ZME_SHOOTCTRL_HC.bits.hc_shootctrl_mode = u32bMode;
        V0_ZME_SHOOTCTRL_HC.bits.hc_shootctrl_mode = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_HC.u32);
    }

    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_VL.bits.vl_shootctrl_en   = u32bEnable;
        V0_ZME_SHOOTCTRL_VL.bits.vl_shootctrl_mode = 0;
        //V0_ZME_SHOOTCTRL_VL.bits.vl_shootctrl_mode = u32bMode;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_VL.u32);
    }

    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_VC.bits.vc_shootctrl_en   = u32bEnable;
//         V0_ZME_SHOOTCTRL_VC.bits.vc_shootctrl_mode = u32bMode;
        V0_ZME_SHOOTCTRL_VC.bits.vc_shootctrl_mode = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_VC.u32);
    }

    return ;
}


HI_VOID  VDP_VID_SetZmeShootCtrlPara  (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_U32 u32Flatdect_mode,HI_U32 u32Coringadj_en,HI_U32 u32Gain,HI_U32 u32Coring)
{
    U_V0_ZME_SHOOTCTRL_HL V0_ZME_SHOOTCTRL_HL;
    U_V0_ZME_SHOOTCTRL_HC V0_ZME_SHOOTCTRL_HC;
    U_V0_ZME_SHOOTCTRL_VL V0_ZME_SHOOTCTRL_VL;
    U_V0_ZME_SHOOTCTRL_VC V0_ZME_SHOOTCTRL_VC;


    if(u32Data != VDP_LAYER_VID0)
    {
        VDP_PRINT("Error,VDP_VID_SetZmeShootCtrlPara() Select Wrong Video Layer ID\n");
        return;
    }

    /* VHD layer zoom enable */
    if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_HL.bits.hl_flatdect_mode  = u32Flatdect_mode;
        V0_ZME_SHOOTCTRL_HL.bits.hl_coringadj_en   = u32Coringadj_en;
        V0_ZME_SHOOTCTRL_HL.bits.hl_gain           = u32Gain;
        V0_ZME_SHOOTCTRL_HL.bits.hl_coring         = u32Coring;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_HL.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_HC.bits.hc_flatdect_mode  = u32Flatdect_mode;
        V0_ZME_SHOOTCTRL_HC.bits.hc_coringadj_en   = u32Coringadj_en;
        V0_ZME_SHOOTCTRL_HC.bits.hc_gain           = u32Gain;
        V0_ZME_SHOOTCTRL_HC.bits.hc_coring         = u32Coring;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_HC.u32);
    }

    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_VL.bits.vl_flatdect_mode  = u32Flatdect_mode;
        V0_ZME_SHOOTCTRL_VL.bits.vl_coringadj_en   = u32Coringadj_en;
        V0_ZME_SHOOTCTRL_VL.bits.vl_gain           = u32Gain;
        V0_ZME_SHOOTCTRL_VL.bits.vl_coring         = u32Coring;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_VL.u32);
    }
    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + u32Data * VID_OFFSET));
        V0_ZME_SHOOTCTRL_VC.bits.vc_flatdect_mode  = u32Flatdect_mode;
        V0_ZME_SHOOTCTRL_VC.bits.vc_coringadj_en   = u32Coringadj_en;
        V0_ZME_SHOOTCTRL_VC.bits.vc_gain           = u32Gain;
        V0_ZME_SHOOTCTRL_VC.bits.vc_coring         = u32Coring;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + u32Data * VID_OFFSET), V0_ZME_SHOOTCTRL_VC.u32);
    }
    return ;
}
HI_VOID  VDP_VID_SetZmePhase    (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_S32 s32Phase)
{
    U_V0_HLOFFSET  V0_HLOFFSET;
    U_V0_HCOFFSET  V0_HCOFFSET;
    U_V0_VOFFSET   V0_VOFFSET;
    U_V0_VBOFFSET  V0_VBOFFSET;


    /* VHD layer zoom enable */
    if((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HLOFFSET.u32) + u32Data * VID_OFFSET));
        V0_HLOFFSET.bits.hor_loffset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HLOFFSET.u32) + u32Data * VID_OFFSET), V0_HLOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HCOFFSET.u32) + u32Data * VID_OFFSET));
        V0_HCOFFSET.bits.hor_coffset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HCOFFSET.u32) + u32Data * VID_OFFSET), V0_HCOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VOFFSET.u32) + u32Data * VID_OFFSET));
        V0_VOFFSET.bits.vluma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VOFFSET.u32) + u32Data * VID_OFFSET), V0_VOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VOFFSET.u32) + u32Data * VID_OFFSET));
        V0_VOFFSET.bits.vchroma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VOFFSET.u32) + u32Data * VID_OFFSET), V0_VOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERB)||(enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VBOFFSET.u32) + u32Data * VID_OFFSET));
        V0_VBOFFSET.bits.vbluma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VBOFFSET.u32) + u32Data * VID_OFFSET), V0_VBOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERB)||(enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VBOFFSET.u32) + u32Data * VID_OFFSET));
        V0_VBOFFSET.bits.vbchroma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VBOFFSET.u32) + u32Data * VID_OFFSET), V0_VBOFFSET.u32);
    }

    return ;
}

HI_VOID  VDP_VID_SetHdrElZme(HI_U32 u32Data, HI_U32 u32bEnable)
{
#if 0
    U_V0_VSP V0_VSP;

    if(u32Data != VDP_LAYER_VID1)
    {
        VDP_PRINT("Error,VDP_VID_SetHdrElZme() Select Wrong Video Layer ID\n");
        return ;
    }

    V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
    V0_VSP.bits.hdr_el_zme = u32bEnable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
#endif
    return ;
}




HI_VOID  VDP_VID_SetZmeFirEnable(HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;


    if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hlfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
        V0_HSP.bits.hchfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vlfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }

    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
        V0_VSP.bits.vchfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
    }

    return ;
}

HI_VOID  VDP_VID_SetZmeMidEnable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;


    if(u32Data == VDP_LAYER_VID0)
    {
        /* VHD layer zoom enable */
        if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
            V0_HSP.bits.hlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
            V0_HSP.bits.hchmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
            V0_VSP.bits.vlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
            V0_VSP.bits.vchmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
        }
    }
    else
    {
        /* VHD layer zoom enable */
        if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
            V0_HSP.bits.hlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
            V0_HSP.bits.hchmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
            V0_VSP.bits.vlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
            V0_VSP.bits.vchmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);
        }
    }

    return ;
}

HI_VOID VDP_VID_SetZmeHorRatio(HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_V0_HSP V0_HSP;


    V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
    V0_HSP.bits.hratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZmeVerRatio(HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_V0_VSR V0_VSR;


    V0_VSR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSR.u32) + u32Data * VID_OFFSET));
    V0_VSR.bits.vratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSR.u32) + u32Data * VID_OFFSET), V0_VSR.u32);

    return ;
}

HI_VOID  VDP_VID_SetVfirOneTapEnable(HI_U32 u32Data, HI_U32 u32VfirOneTapEn)
{
    U_V0_VSP V0_VSP;


    V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
    V0_VSP.bits.vfir_1tap_en = u32VfirOneTapEn;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

    return ;
}

HI_VOID VDP_VID_SetZmeHfirOrder(HI_U32 u32Data, HI_U32 u32HfirOrder)
{
    U_V0_HSP V0_HSP;


    V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET));
#ifdef VDP_HI3798CV200
    V0_HSP.bits.hfir_order = 1;     //u32HfirOrder;
#else
    V0_HSP.bits.hfir_order = u32HfirOrder;
#endif
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + u32Data * VID_OFFSET), V0_HSP.u32);

    return ;
}

HI_VOID VDP_VID_SetZmeCoefAddr(HI_U32 u32Data, HI_U32 u32Mode, HI_U32 u32Addr)
{
    HI_U32 ADDR_OFFSET= 0x100 ;
	U_PARA_ADDR_VHD_CHN00 PARA_ADDR_VHD_CHN00;
	U_PARA_ADDR_VHD_CHN02 PARA_ADDR_VHD_CHN02;
	U_PARA_ADDR_VHD_CHN01 PARA_ADDR_VHD_CHN01;
	U_PARA_ADDR_VHD_CHN03 PARA_ADDR_VHD_CHN03;

    if(u32Mode == VDP_VID_PARA_ZME_HOR)
    {

        PARA_ADDR_VHD_CHN00.bits.para_addr_vhd_chn00 = u32Addr;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN00.u32),PARA_ADDR_VHD_CHN00.u32);


        PARA_ADDR_VHD_CHN02.bits.para_addr_vhd_chn02 = (u32Addr +ADDR_OFFSET) & 0xfffffff0;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN02.u32),PARA_ADDR_VHD_CHN02.u32);
    }
    else if(u32Mode == VDP_VID_PARA_ZME_VER)
    {

        PARA_ADDR_VHD_CHN01.bits.para_addr_vhd_chn01 = u32Addr;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN01.u32),PARA_ADDR_VHD_CHN01.u32);

        PARA_ADDR_VHD_CHN03.bits.para_addr_vhd_chn03 = (u32Addr +ADDR_OFFSET) & 0xfffffff0;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN03.u32),PARA_ADDR_VHD_CHN03.u32);
    }
    else
    {

    }

#if 0
    U_V0_HLCOEFAD V0_HLCOEFAD;
    U_V0_HCCOEFAD V0_HCCOEFAD;
    U_V0_VLCOEFAD V0_VLCOEFAD;
    U_V0_VCCOEFAD V0_VCCOEFAD;

    HI_U32 ADDR_OFFSET= 0x100 ;

    if(u32Mode == VDP_VID_PARA_ZME_HOR)
    {
        V0_HLCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HLCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_HLCOEFAD.bits.coef_addr = u32Addr;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HLCOEFAD.u32) + u32Data * VID_OFFSET), V0_HLCOEFAD.u32);

        V0_HCCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HCCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_HCCOEFAD.bits.coef_addr = (u32Addr +ADDR_OFFSET) & 0xfffffff0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HCCOEFAD.u32) + u32Data * VID_OFFSET), V0_HCCOEFAD.u32);

    }
    else if(u32Mode == VDP_VID_PARA_ZME_VER)
    {
        V0_VLCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VLCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_VLCOEFAD.bits.coef_addr = u32Addr;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VLCOEFAD.u32) + u32Data * VID_OFFSET), V0_VLCOEFAD.u32);

        V0_VCCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VCCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_VCCOEFAD.bits.coef_addr = (u32Addr + ADDR_OFFSET)  & 0xfffffff0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VCCOEFAD.u32) + u32Data * VID_OFFSET), V0_VCCOEFAD.u32);


    }
    else
    {
        VDP_PRINT("Error,VDP_VID_SetZmeCoefAddr() Select a Wrong Mode!\n");
    }
#endif
    return ;
}

HI_VOID VDP_VID_SetZme2CoefAddr(HI_U32 u32Data, HI_U32 u32Mode, HI_U32 u32Addr)
{
    HI_U32 ADDR_OFFSET= 0x100 ;
    U_PARA_ADDR_VHD_CHN05 PARA_ADDR_VHD_CHN05;
    U_PARA_ADDR_VHD_CHN06 PARA_ADDR_VHD_CHN06;
    U_PARA_ADDR_VHD_CHN07 PARA_ADDR_VHD_CHN07;
    U_PARA_ADDR_VHD_CHN08 PARA_ADDR_VHD_CHN08;
    if(u32Mode == VDP_VID_PARA_ZME2_HOR)
    {
        PARA_ADDR_VHD_CHN05.bits.para_addr_vhd_chn05 = u32Addr;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN05.u32),PARA_ADDR_VHD_CHN05.u32);

        PARA_ADDR_VHD_CHN07.bits.para_addr_vhd_chn07 = (u32Addr +ADDR_OFFSET) & 0xfffffff0;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN07.u32),PARA_ADDR_VHD_CHN07.u32);
    }
    else if(u32Mode == VDP_VID_PARA_ZME2_VER)
    {
        PARA_ADDR_VHD_CHN06.bits.para_addr_vhd_chn06 = u32Addr;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN06.u32),PARA_ADDR_VHD_CHN06.u32);

        PARA_ADDR_VHD_CHN08.bits.para_addr_vhd_chn08 = (u32Addr +ADDR_OFFSET) & 0xfffffff0;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_ADDR_VHD_CHN08.u32),PARA_ADDR_VHD_CHN08.u32);
    }
    else
    {

    }


#if 0
    U_V0_ZME2_HLCOEFAD V0_ZME2_HLCOEFAD;
    U_V0_ZME2_HCCOEFAD V0_ZME2_HCCOEFAD;
    U_V0_ZME2_VLCOEFAD V0_ZME2_VLCOEFAD;
    U_V0_ZME2_VCCOEFAD V0_ZME2_VCCOEFAD;

    HI_U32 ADDR_OFFSET= 0x100 ;

    if(u32Mode == VDP_VID_PARA_ZME2_HOR)
    {
        V0_ZME2_HLCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME2_HLCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_ZME2_HLCOEFAD.bits.coef_addr = u32Addr;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME2_HLCOEFAD.u32) + u32Data * VID_OFFSET), V0_ZME2_HLCOEFAD.u32);

        V0_ZME2_HCCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME2_HCCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_ZME2_HCCOEFAD.bits.coef_addr = (u32Addr +ADDR_OFFSET) & 0xfffffff0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME2_HCCOEFAD.u32) + u32Data * VID_OFFSET), V0_ZME2_HCCOEFAD.u32);

    }
    else if(u32Mode == VDP_VID_PARA_ZME2_VER)
    {
        V0_ZME2_VLCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME2_VLCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_ZME2_VLCOEFAD.bits.coef_addr = u32Addr;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME2_VLCOEFAD.u32) + u32Data * VID_OFFSET), V0_ZME2_VLCOEFAD.u32);

        V0_ZME2_VCCOEFAD.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME2_VCCOEFAD.u32) + u32Data * VID_OFFSET));
        V0_ZME2_VCCOEFAD.bits.coef_addr = (u32Addr + ADDR_OFFSET)  & 0xfffffff0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME2_VCCOEFAD.u32) + u32Data * VID_OFFSET), V0_ZME2_VCCOEFAD.u32);


    }
    else
    {
        VDP_PRINT("Error,VDP_VID_SetZmeCoefAddr() Select a Wrong Mode!\n");
    }
#endif
    return ;
}

HI_VOID  VDP_VID_SetZmeInFmt(HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt)
{
    U_V0_VSP V0_VSP;


    V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
    V0_VSP.bits.zme_in_fmt = u32Fmt;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZmeOutFmt(HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt)
{
    U_V0_VSP V0_VSP;


    V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
    V0_VSP.bits.zme_out_fmt = u32Fmt;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET), V0_VSP.u32);

    return ;
}

#if 1
// VID.ZME.NONLINE begin
HI_VOID  VDP_VID_SetZmeNonLnrDelta(HI_U32 u32Data, HI_S32 s32Zone0Delta, HI_S32 s32Zone2Delta)
{
    U_V0_HZONE0DELTA     V0_HZONE0DELTA;
    U_V0_HZONE2DELTA     V0_HZONE2DELTA;


    V0_HZONE0DELTA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HZONE0DELTA.u32) + u32Data * VID_OFFSET));
    V0_HZONE0DELTA.bits.zone0_delta = s32Zone0Delta;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HZONE0DELTA.u32) + u32Data * VID_OFFSET), V0_HZONE0DELTA.u32);

    V0_HZONE2DELTA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HZONE2DELTA.u32) + u32Data * VID_OFFSET));
    V0_HZONE2DELTA.bits.zone2_delta = s32Zone2Delta;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HZONE2DELTA.u32) + u32Data * VID_OFFSET), V0_HZONE2DELTA.u32);

    return ;
}

HI_VOID  VDP_VID_SetZmeNonLnrZoneEnd(HI_U32 u32Data, HI_U32 u32Zone0End, HI_U32 u32Zone1End)
{
    U_V0_HZONEEND        V0_HZONEEND;


    V0_HZONEEND.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HZONEEND.u32) + u32Data * VID_OFFSET));
    V0_HZONEEND.bits.zone0_end = u32Zone0End-1;
    V0_HZONEEND.bits.zone1_end = u32Zone1End-1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HZONEEND.u32) + u32Data * VID_OFFSET), V0_HZONEEND.u32);

    return ;
}
#endif

HI_VOID  VDP_VID_SetCvfirVCoef(HI_U32 u32Data,  VDP_VID_CVFIR_VCOEF_S stCvfirVCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

////////////////////////////////////
//ZME END
////////////////////////////////////

#if VID_ZME2_EN
///////////////////////////////////
//ZME2 BEGIN
///////////////////////////////////
HI_VOID  VDP_VID_SetZme2Enable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;


    /* VHD layer zoom enable */
    if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
        V0_HSP.bits.hlmsc_en = u32bEnable;
        V0_HSP.bits.hlfir_en = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
        V0_HSP.bits.hchmsc_en = u32bEnable;
        V0_HSP.bits.hchfir_en = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
    }
#if 1
    if((enMode == VDP_ZME_MODE_NONL)||(enMode == VDP_ZME_MODE_ALL))
    {
		V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32)));
        V0_HSP.bits.non_lnr_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32)), V0_HSP.u32);
    }
#endif

    if(u32Data == VDP_LAYER_VID1 || u32Data == VDP_LAYER_VID4)
    {
        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vlmsc_en = 0;//u32bEnable;
            V0_VSP.bits.vlfir_en = 1;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vchmsc_en = u32bEnable;
            V0_VSP.bits.vchfir_en = 1;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }
    }
    else
    {
        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vlmsc_en = u32bEnable;
            V0_VSP.bits.vlfir_en = 1;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vchmsc_en = u32bEnable;
            V0_VSP.bits.vchfir_en = 1;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }
    }
    return;
}

HI_VOID  VDP_VID_SetZme2ShootCtrlEnable  (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_U32 u32bEnable,HI_U32 u32bMode)
{
    U_V0_ZME_SHOOTCTRL_HL V0_ZME_SHOOTCTRL_HL;
    U_V0_ZME_SHOOTCTRL_HC V0_ZME_SHOOTCTRL_HC;
    U_V0_ZME_SHOOTCTRL_VL V0_ZME_SHOOTCTRL_VL;
    U_V0_ZME_SHOOTCTRL_VC V0_ZME_SHOOTCTRL_VC;

    /* VHD layer zoom enable */
    if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + VID_ZME_OFFSET));
        V0_ZME_SHOOTCTRL_HL.bits.hl_shootctrl_en   = u32bEnable;
        V0_ZME_SHOOTCTRL_HL.bits.hl_shootctrl_mode = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + VID_ZME_OFFSET), V0_ZME_SHOOTCTRL_HL.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + VID_ZME_OFFSET));
        V0_ZME_SHOOTCTRL_HC.bits.hc_shootctrl_en   = u32bEnable;
        V0_ZME_SHOOTCTRL_HC.bits.hc_shootctrl_mode = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + VID_ZME_OFFSET), V0_ZME_SHOOTCTRL_HC.u32);
    }

    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + VID_ZME_OFFSET));
        V0_ZME_SHOOTCTRL_VL.bits.vl_shootctrl_en   = u32bEnable;
        V0_ZME_SHOOTCTRL_VL.bits.vl_shootctrl_mode = 0;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + VID_ZME_OFFSET), V0_ZME_SHOOTCTRL_VL.u32);
    }

    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + VID_ZME_OFFSET));
        V0_ZME_SHOOTCTRL_VC.bits.vc_shootctrl_en   = u32bEnable;
        V0_ZME_SHOOTCTRL_VC.bits.vc_shootctrl_mode = 1;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + VID_ZME_OFFSET), V0_ZME_SHOOTCTRL_VC.u32);
    }

    return ;
}


HI_VOID  VDP_VID_SetZme2ShootCtrlPara  (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_U32 u32Flatdect_mode,HI_U32 u32Coringadj_en,HI_U32 u32Gain,HI_U32 u32Coring)
{
    U_V0_ZME_SHOOTCTRL_HL V0_ZME_SHOOTCTRL_HL;
    U_V0_ZME_SHOOTCTRL_HC V0_ZME_SHOOTCTRL_HC;
    U_V0_ZME_SHOOTCTRL_VL V0_ZME_SHOOTCTRL_VL;
    U_V0_ZME_SHOOTCTRL_VC V0_ZME_SHOOTCTRL_VC;


    /* VHD layer zoom enable */
    if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + VID_ZME_OFFSET));
        V0_ZME_SHOOTCTRL_HL.bits.hl_flatdect_mode  = u32Flatdect_mode;
        V0_ZME_SHOOTCTRL_HL.bits.hl_coringadj_en   = u32Coringadj_en;
        V0_ZME_SHOOTCTRL_HL.bits.hl_gain           = u32Gain;
        V0_ZME_SHOOTCTRL_HL.bits.hl_coring         = u32Coring;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HL.u32) + VID_ZME_OFFSET), V0_ZME_SHOOTCTRL_HL.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_HC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + VID_ZME_OFFSET));
        V0_ZME_SHOOTCTRL_HC.bits.hc_flatdect_mode  = u32Flatdect_mode;
        V0_ZME_SHOOTCTRL_HC.bits.hc_coringadj_en   = u32Coringadj_en;
        V0_ZME_SHOOTCTRL_HC.bits.hc_gain           = u32Gain;
        V0_ZME_SHOOTCTRL_HC.bits.hc_coring         = u32Coring;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_HC.u32) + VID_ZME_OFFSET), V0_ZME_SHOOTCTRL_HC.u32);
    }

    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + VID_ZME_OFFSET));
        V0_ZME_SHOOTCTRL_VL.bits.vl_flatdect_mode  = u32Flatdect_mode;
        V0_ZME_SHOOTCTRL_VL.bits.vl_coringadj_en   = u32Coringadj_en;
        V0_ZME_SHOOTCTRL_VL.bits.vl_gain           = u32Gain;
        V0_ZME_SHOOTCTRL_VL.bits.vl_coring         = u32Coring;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VL.u32) + VID_ZME_OFFSET), V0_ZME_SHOOTCTRL_VL.u32);
    }
    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_ZME_SHOOTCTRL_VC.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + VID_ZME_OFFSET));
        V0_ZME_SHOOTCTRL_VC.bits.vc_flatdect_mode  = u32Flatdect_mode;
        V0_ZME_SHOOTCTRL_VC.bits.vc_coringadj_en   = u32Coringadj_en;
        V0_ZME_SHOOTCTRL_VC.bits.vc_gain           = u32Gain;
        V0_ZME_SHOOTCTRL_VC.bits.vc_coring         = u32Coring;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_ZME_SHOOTCTRL_VC.u32) + VID_ZME_OFFSET), V0_ZME_SHOOTCTRL_VC.u32);
    }
    return ;
}
HI_VOID  VDP_VID_SetZme2Phase    (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_S32 s32Phase)
{
    U_V0_HLOFFSET  V0_HLOFFSET;
    U_V0_HCOFFSET  V0_HCOFFSET;
    U_V0_VOFFSET   V0_VOFFSET;
    U_V0_VBOFFSET  V0_VBOFFSET;


    /* VHD layer zoom enable */
    if((enMode == VDP_ZME_MODE_HORL) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HLOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HLOFFSET.u32) + VID_ZME_OFFSET));
        V0_HLOFFSET.bits.hor_loffset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HLOFFSET.u32) + VID_ZME_OFFSET), V0_HLOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC) || (enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HCOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HCOFFSET.u32) + VID_ZME_OFFSET));
        V0_HCOFFSET.bits.hor_coffset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HCOFFSET.u32) + VID_ZME_OFFSET), V0_HCOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VOFFSET.u32) + VID_ZME_OFFSET));
        V0_VOFFSET.bits.vluma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VOFFSET.u32) + VID_ZME_OFFSET), V0_VOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VOFFSET.u32) + VID_ZME_OFFSET));
        V0_VOFFSET.bits.vchroma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VOFFSET.u32) + VID_ZME_OFFSET), V0_VOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERB)||(enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VBOFFSET.u32) + VID_ZME_OFFSET));
        V0_VBOFFSET.bits.vbluma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VBOFFSET.u32) + VID_ZME_OFFSET), V0_VBOFFSET.u32);
    }

    if((enMode == VDP_ZME_MODE_VERB)||(enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VBOFFSET.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VBOFFSET.u32) + VID_ZME_OFFSET));
        V0_VBOFFSET.bits.vbchroma_offset = s32Phase;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VBOFFSET.u32) + VID_ZME_OFFSET), V0_VBOFFSET.u32);
    }

    return ;
}

HI_VOID  VDP_VID_SetZme2FirEnable(HI_U32 u32Data, VDP_ZME_MODE_E enMode, HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;


    if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
        V0_HSP.bits.hlfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
        V0_HSP.bits.hchfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
    }

    if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
        V0_VSP.bits.vlfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
    }

    if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
    {
        V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
        V0_VSP.bits.vchfir_en = u32bEnable;
        VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
    }

    return ;
}

HI_VOID  VDP_VID_SetZme2MidEnable   (HI_U32 u32Data, VDP_ZME_MODE_E enMode,HI_U32 u32bEnable)
{
    U_V0_HSP V0_HSP;
    U_V0_VSP V0_VSP;

        /* VHD layer zoom enable */
        if((enMode == VDP_ZME_MODE_HORL)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
            V0_HSP.bits.hlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_HORC)||(enMode == VDP_ZME_MODE_HOR)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
            V0_HSP.bits.hchmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERL)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vlmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }

        if((enMode == VDP_ZME_MODE_VERC)||(enMode == VDP_ZME_MODE_VER)||(enMode == VDP_ZME_MODE_ALL))
        {
            V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
            V0_VSP.bits.vchmid_en = u32bEnable;
            VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);
        }
    return ;
}

HI_VOID VDP_VID_SetZme2HorRatio(HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_V0_HSP V0_HSP;


    V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
    V0_HSP.bits.hratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZme2VerRatio(HI_U32 u32Data, HI_U32 u32Ratio)
{
    U_V0_VSR V0_VSR;


    V0_VSR.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSR.u32) + VID_ZME_OFFSET));
    V0_VSR.bits.vratio = u32Ratio;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSR.u32) + VID_ZME_OFFSET), V0_VSR.u32);

    return ;
}

HI_VOID  VDP_VID_SetZme2VfirOneTapEnable(HI_U32 u32Data, HI_U32 u32VfirOneTapEn)
{
    U_V0_VSP V0_VSP;


    V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
    V0_VSP.bits.vfir_1tap_en = u32VfirOneTapEn;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);

    return ;
}

HI_VOID VDP_VID_SetZme2HfirOrder(HI_U32 u32Data, HI_U32 u32HfirOrder)
{
    U_V0_HSP V0_HSP;


    V0_HSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET));
#ifdef VDP_HI3798CV200
    V0_HSP.bits.hfir_order = 1;     //u32HfirOrder;
#else
    V0_HSP.bits.hfir_order = u32HfirOrder;
#endif
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HSP.u32) + VID_ZME_OFFSET), V0_HSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZme2InFmt(HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt)
{
    U_V0_VSP V0_VSP;


    V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
    V0_VSP.bits.zme_in_fmt = u32Fmt;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);

    return ;
}

HI_VOID  VDP_VID_SetZme2OutFmt(HI_U32 u32Data, VDP_PROC_FMT_E u32Fmt)
{
    U_V0_VSP V0_VSP;


    V0_VSP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET));
    V0_VSP.bits.zme_out_fmt = u32Fmt;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_VSP.u32) + VID_ZME_OFFSET), V0_VSP.u32);

    return ;
}

#if 1

HI_VOID  VDP_VID_SetZme2NonLnrDelta(HI_U32 u32Data, HI_S32 s32Zone0Delta, HI_S32 s32Zone2Delta)
{
    U_V0_HZONE0DELTA     V0_HZONE0DELTA;
    U_V0_HZONE2DELTA     V0_HZONE2DELTA;


    V0_HZONE0DELTA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HZONE0DELTA.u32) + VID_ZME_OFFSET));
    V0_HZONE0DELTA.bits.zone0_delta = s32Zone0Delta;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HZONE0DELTA.u32) + VID_ZME_OFFSET), V0_HZONE0DELTA.u32);

    V0_HZONE2DELTA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HZONE2DELTA.u32) + VID_ZME_OFFSET));
    V0_HZONE2DELTA.bits.zone2_delta = s32Zone2Delta;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HZONE2DELTA.u32) + VID_ZME_OFFSET), V0_HZONE2DELTA.u32);

    return ;
}

HI_VOID  VDP_VID_SetZme2NonLnrZoneEnd(HI_U32 u32Data, HI_U32 u32Zone0End, HI_U32 u32Zone1End)
{
    U_V0_HZONEEND        V0_HZONEEND;


    V0_HZONEEND.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->V0_HZONEEND.u32) + VID_ZME_OFFSET));
    V0_HZONEEND.bits.zone0_end = u32Zone0End-1;
    V0_HZONEEND.bits.zone1_end = u32Zone1End-1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->V0_HZONEEND.u32) + VID_ZME_OFFSET), V0_HZONEEND.u32);

    return ;
}
#endif


//ZME2 coef sent drv
HI_VOID  VDP_VID_SetZme2HCoef(HI_U32 u32Data,  VDP_VID_ZME2_HCOEF_S stZme2HCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_VID_SetZme2VCoef(HI_U32 u32Data,  VDP_VID_ZME2_VCOEF_S stZme2VCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}
////////////////////////////////////
//ZME2 END
////////////////////////////////////
#endif

HI_VOID  VDP_VID_SetParaUpd       (HI_U32 u32Data, VDP_VID_PARA_E enMode)
{
    U_PARA_UP_VHD PARA_UP_VHD;
    PARA_UP_VHD.u32 = VDP_RegRead((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32));

    if(enMode == VDP_VID_PARA_ZME_HOR)
    {
        PARA_UP_VHD.bits.para_up_vhd_chn00 = 0x1;
        PARA_UP_VHD.bits.para_up_vhd_chn02 = 0x1;
    }
    else if(enMode == VDP_VID_PARA_ZME_VER)
    {
        PARA_UP_VHD.bits.para_up_vhd_chn01 = 0x1;
        PARA_UP_VHD.bits.para_up_vhd_chn03 = 0x1;
    }
    else if(enMode == VDP_VID_PARA_ZME2_HOR)
    {
        PARA_UP_VHD.bits.para_up_vhd_chn05 = 0x1;
        PARA_UP_VHD.bits.para_up_vhd_chn07 = 0x1;

    }
    else if(enMode == VDP_VID_PARA_ZME2_VER)
    {
        PARA_UP_VHD.bits.para_up_vhd_chn06 = 0x1;
        PARA_UP_VHD.bits.para_up_vhd_chn08 = 0x1;
    }
    VDP_RegWrite((HI_ULONG)&(pVdpReg->PARA_UP_VHD.u32),PARA_UP_VHD.u32);

    return ;
}
//------------------------------------------------------------------
//driver for VP layer
//------------------------------------------------------------------

#if VP0_EN
HI_VOID  VDP_VP_SetThreeDimDofEnable    (HI_U32 u32Data, HI_U32 bEnable)
{
    U_VP0_DOF_CTRL  VP0_DOF_CTRL;


    VP0_DOF_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_DOF_CTRL.u32)));
    VP0_DOF_CTRL.bits.dof_en = bEnable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_DOF_CTRL.u32)), VP0_DOF_CTRL.u32);
}

HI_VOID  VDP_VP_SetThreeDimDofStep(HI_U32 u32Data, HI_S32 s32LStep, HI_S32 s32RStep)
{
    U_VP0_DOF_STEP  VP0_DOF_STEP;

    VP0_DOF_STEP.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_DOF_STEP.u32)));
    VP0_DOF_STEP.bits.right_step= s32RStep;
    VP0_DOF_STEP.bits.left_step = s32LStep;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_DOF_STEP.u32)), VP0_DOF_STEP.u32);
}

HI_VOID  VDP_VP_SetThreeDimDofBkg   (HI_U32 u32Data, VDP_BKG_S stBkg)
{
    U_VP0_DOF_BKG  VP0_DOF_BKG;
    //U_G0_DOF_ALPHA G0_DOF_ALPHA;


    VP0_DOF_BKG.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_DOF_BKG.u32)));
    VP0_DOF_BKG.bits.dof_bk_y  = stBkg.u32BkgY ;
    VP0_DOF_BKG.bits.dof_bk_cb = stBkg.u32BkgU;
    VP0_DOF_BKG.bits.dof_bk_cr = stBkg.u32BkgV;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_DOF_BKG.u32)), VP0_DOF_BKG.u32);

    return ;
}
HI_VOID  VDP_VP_SetLayerReso     (HI_U32 u32Data, VDP_DISP_RECT_S  stRect)
{
    U_VP0_VFPOS VP0_VFPOS;
    U_VP0_VLPOS VP0_VLPOS;
    U_VP0_DFPOS VP0_DFPOS;
    U_VP0_DLPOS VP0_DLPOS;
    U_VP0_IRESO VP0_IRESO;


    /*video position */
    VP0_VFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_VFPOS.u32) + u32Data * VID_OFFSET));
    VP0_VFPOS.bits.video_xfpos = stRect.u32VX;
    VP0_VFPOS.bits.video_yfpos = stRect.u32VY;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_VFPOS.u32) + u32Data * VID_OFFSET), VP0_VFPOS.u32);

    VP0_VLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_VLPOS.u32) + u32Data * VID_OFFSET));
    VP0_VLPOS.bits.video_xlpos = stRect.u32VX + stRect.u32OWth - 1;
    VP0_VLPOS.bits.video_ylpos = stRect.u32VY + stRect.u32OHgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_VLPOS.u32) + u32Data * VID_OFFSET), VP0_VLPOS.u32);

    VP0_DFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_DFPOS.u32) + u32Data * VID_OFFSET));
    VP0_DFPOS.bits.disp_xfpos = stRect.u32DXS;
    VP0_DFPOS.bits.disp_yfpos = stRect.u32DYS;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_DFPOS.u32) + u32Data * VID_OFFSET), VP0_DFPOS.u32);

    VP0_DLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_DLPOS.u32) + u32Data * VID_OFFSET));
    VP0_DLPOS.bits.disp_xlpos = stRect.u32DXL-1;
    VP0_DLPOS.bits.disp_ylpos = stRect.u32DYL-1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_DLPOS.u32) + u32Data * VID_OFFSET), VP0_DLPOS.u32);

    VP0_IRESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_IRESO.u32) + u32Data * VID_OFFSET));
    VP0_IRESO.bits.iw = stRect.u32IWth - 1;
    VP0_IRESO.bits.ih = stRect.u32IHgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_IRESO.u32) + u32Data * VID_OFFSET), VP0_IRESO.u32);

    return ;
}
HI_VOID  VDP_VP_SetVideoPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_VP0_VFPOS VP0_VFPOS;
    U_VP0_VLPOS VP0_VLPOS;


    /*video position */
    VP0_VFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_VFPOS.u32) + u32Data * VP_OFFSET));
    VP0_VFPOS.bits.video_xfpos = stRect.u32X;
    VP0_VFPOS.bits.video_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_VFPOS.u32) + u32Data * VP_OFFSET), VP0_VFPOS.u32);

    VP0_VLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_VLPOS.u32) + u32Data * VP_OFFSET));
    VP0_VLPOS.bits.video_xlpos = stRect.u32X + stRect.u32Wth - 1;
    VP0_VLPOS.bits.video_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_VLPOS.u32) + u32Data * VP_OFFSET), VP0_VLPOS.u32);

    return ;
}

HI_VOID  VDP_VP_SetDispPos     (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_VP0_DFPOS VP0_DFPOS;
    U_VP0_DLPOS VP0_DLPOS;


    /*video position */
    VP0_DFPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_DFPOS.u32) + u32Data * VP_OFFSET));
    VP0_DFPOS.bits.disp_xfpos = stRect.u32X;
    VP0_DFPOS.bits.disp_yfpos = stRect.u32Y;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_DFPOS.u32) + u32Data * VP_OFFSET), VP0_DFPOS.u32);

    VP0_DLPOS.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_DLPOS.u32) + u32Data * VP_OFFSET));
    VP0_DLPOS.bits.disp_xlpos = stRect.u32X + stRect.u32Wth - 1;
    VP0_DLPOS.bits.disp_ylpos = stRect.u32Y + stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_DLPOS.u32) + u32Data * VP_OFFSET), VP0_DLPOS.u32);
    return ;
}

HI_VOID  VDP_VP_SetInReso      (HI_U32 u32Data, VDP_RECT_S  stRect)
{
    U_VP0_IRESO VP0_IRESO;


    VP0_IRESO.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_IRESO.u32) + u32Data * VP_OFFSET));
    VP0_IRESO.bits.iw = stRect.u32Wth - 1;
    VP0_IRESO.bits.ih = stRect.u32Hgt - 1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_IRESO.u32) + u32Data * VP_OFFSET), VP0_IRESO.u32);

    return ;
}

HI_VOID  VDP_VP_SetRegUp  (HI_U32 u32Data)
{
    U_VP0_UPD VP0_UPD;

    /* VP layer register update */

    VP0_UPD.bits.regup = 0x1;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_UPD.u32) + u32Data * VP_OFFSET), VP0_UPD.u32);

    return ;
}

HI_VOID  VDP_VP_SetLayerGalpha (HI_U32 u32Data, HI_U32 u32Alpha)
{

    U_VP0_CTRL  VP0_CTRL;
    U_VP0_ALPHA VP0_ALPHA;



    VP0_CTRL.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_CTRL.u32) + u32Data * VP_OFFSET));
    VP0_CTRL.bits.galpha = u32Alpha;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_CTRL.u32) + u32Data * VP_OFFSET), VP0_CTRL.u32);


    VP0_ALPHA.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_ALPHA.u32)));
    VP0_ALPHA.bits.vbk_alpha = u32Alpha;
    VDP_RegWrite((HI_ULONG)&(pVdpReg->VP0_ALPHA.u32), VP0_ALPHA.u32);

    return ;
}

HI_VOID  VDP_VP_SetLayerBkg(HI_U32 u32Data, VDP_BKG_S stBkg)
{
    U_VP0_BK VP0_BK;

    if(u32Data == VDP_LAYER_VP0)
    {
        VP0_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_BK.u32)));
        VP0_BK.bits.vbk_y  = stBkg.u32BkgY;
        VP0_BK.bits.vbk_cb = stBkg.u32BkgU;
        VP0_BK.bits.vbk_cr = stBkg.u32BkgV;
        VDP_RegWrite((HI_ULONG)&(pVdpReg->VP0_BK.u32), VP0_BK.u32);

     }
    else
    {
        VDP_PRINT("Error,VDP_VP_SetLayerBkg() Select Wrong VP Layer ID\n");
    }

    return ;
}

HI_VOID VDP_VP_SetMuteEnable     (HI_U32 u32Data, HI_U32 bEnable)
{
    U_VP0_MUTE_BK VP0_MUTE_BK;


    VP0_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_MUTE_BK.u32) + u32Data * VP_OFFSET));
    VP0_MUTE_BK.bits.mute_en = bEnable;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_MUTE_BK.u32) + u32Data * VP_OFFSET), VP0_MUTE_BK.u32);
     return ;
}

HI_VOID  VDP_VP_SetMuteBkg(HI_U32 u32Data, VDP_VP_MUTE_BK_S stVpMuteBkg)
{
    U_VP0_MUTE_BK VP0_MUTE_BK;


    VP0_MUTE_BK.u32 = VDP_RegRead(((HI_ULONG)&(pVdpReg->VP0_MUTE_BK.u32) + u32Data * VP_OFFSET));
    VP0_MUTE_BK.bits.mute_y  = stVpMuteBkg.u32VpMuteBkgY;
    VP0_MUTE_BK.bits.mute_cb = stVpMuteBkg.u32VpMuteBkgU;
    VP0_MUTE_BK.bits.mute_cr = stVpMuteBkg.u32VpMuteBkgV;
    VDP_RegWrite(((HI_ULONG)&(pVdpReg->VP0_MUTE_BK.u32) + u32Data * VP_OFFSET), VP0_MUTE_BK.u32);

    return ;
}

HI_VOID VDP_VP_SetDispMode(HI_U32 u32Data, VDP_DISP_MODE_E enDispMode)
{
}

HI_VOID  VDP_VP_SetCscDcCoef   (HI_U32 u32Data, VDP_CSC_DC_COEF_S pstCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID   VDP_VP_SetCscCoef(HI_U32 u32Data, VDP_CSC_COEF_S stCscCoef)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_VP_SetCscEnable   (HI_U32 u32Data, HI_U32 u32bCscEn)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_VP_SetCscMode(HI_U32 u32Data, VDP_CSC_MODE_E enCscMode)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

#endif //end VP0_EN


HI_VOID VDP_VID_SetMasterSel  (HI_U32 u32Data, HI_U32 u32MasterNum)
{
    DISP_INFO("98mv310 Nousing!\n");

    return ;

}

HI_VOID  VDP_VID_SetFrReqSize    (HI_U32 u32Data)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID  VDP_VID_SetDsReqSize    (HI_U32 u32Data)
{
    DISP_INFO("98mv310 Nousing!\n");
    return ;
}

HI_VOID VDP_VID_SetDcmpCtrl   (HI_U32 u32Data, HI_U32 u32LumLosslessEn, HI_U32 u32ChmLosslessEn )
{
    DISP_INFO("98mv310 Nousing!\n");

    return ;
}

HI_VOID VDP_VID_SetSrcCropReso    (HI_U32 u32Data, VDP_RECT_S stRect)
{
    HI_U32 u32SrcWth = ((VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_IN_RESO.u32) + u32Data * VID_FDR_OFFSET))) & 0xffff) + 1 + stRect.u32X;
    HI_U32 u32SrcHgt = (((VDP_RegRead(((HI_ULONG)&(pVdpReg->VID_IN_RESO.u32) + u32Data * VID_FDR_OFFSET))) >> 16) & 0xffff) + 1 + stRect.u32Y;
    VDP_FDR_VID_SetSrcCropY        (  u32Data * VID_FDR_OFFSET, stRect.u32Y);
    VDP_FDR_VID_SetSrcCropX        (  u32Data * VID_FDR_OFFSET, stRect.u32X);
    VDP_FDR_VID_SetSrcH            (  u32Data * VID_FDR_OFFSET, u32SrcHgt - 1);
    VDP_FDR_VID_SetSrcW            (  u32Data * VID_FDR_OFFSET, u32SrcWth - 1);
    return ;
}


HI_VOID  VDP_VID_SetTestPatternEnable    (HI_U32 u32Data, HI_U32 u32Enable )
{
    VDP_FDR_VID_SetTestpatternEn   (  u32Data * VID_FDR_OFFSET, u32Enable);
    return ;
}

HI_VOID  VDP_VID_SetTestPatternMode    (HI_U32 u32Data, HI_U32 u32Mode )
{
    HI_U32 u32TpCMode = 0;
    VDP_FDR_VID_SetTpMode          (   u32Data * VID_FDR_OFFSET, u32Mode );
    VDP_FDR_VID_SetTpColorMode     (   u32Data * VID_FDR_OFFSET,  u32TpCMode);
    return ;
}

HI_VOID  VDP_VID_SetTestPatternLWidth    (HI_U32 u32Data, HI_U32 u32Width )
{
    VDP_FDR_VID_SetTpLineW         (  u32Data * VID_FDR_OFFSET, u32Width );
    return ;
}

HI_VOID  VDP_VID_SetTestPatternSpeed    (HI_U32 u32Data, HI_U32 u32Speed )
{
    VDP_FDR_VID_SetTpSpeed         (  u32Data * VID_FDR_OFFSET, u32Speed );
    return ;
}

HI_VOID  VDP_VID_SetTestPatternSeed    (HI_U32 u32Data, HI_U32 u32Seed )
{
    VDP_FDR_VID_SetTpSeed         (  u32Data * VID_FDR_OFFSET,  u32Seed);

    return ;
}

//HZME
HI_VOID VDP_VID_SetHpzmeEn(HI_U32 u32Data, HI_U32 hpzme_en)
{
	U_V0_HPZME V0_HPZME;
	V0_HPZME.u32 = VDP_RegRead( ((HI_ULONG)&(pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET));
	V0_HPZME.bits.hpzme_en = hpzme_en;
	VDP_RegWrite( ((HI_ULONG)&(pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET),V0_HPZME.u32);

	return ;
}

HI_VOID VDP_VID_SetHpzmeCkGtEn(HI_U32 u32Data, HI_U32 u32CkGtEn)
{
	U_V0_HPZME V0_HPZME;
	V0_HPZME.u32 = VDP_RegRead( ((HI_ULONG)&(pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET));
	V0_HPZME.bits.ck_gt_en = u32CkGtEn;
	VDP_RegWrite( ((HI_ULONG)&(pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET),V0_HPZME.u32);

	return ;
}
HI_VOID VDP_VID_SetZme1CkGtEn(HI_U32 u32Data, HI_U32 u32CkGtEn)
{
	U_V0_VSP V0_VSP;
	V0_VSP.u32 = VDP_RegRead( ((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET));
	V0_VSP.bits.ck_gt_en = u32CkGtEn;
	VDP_RegWrite( ((HI_ULONG)&(pVdpReg->V0_VSP.u32) + u32Data * VID_OFFSET),V0_VSP.u32);

	return ;
}
HI_VOID VDP_VID_SetZme2CkGtEn(HI_U32 u32Data, HI_U32 u32CkGtEn)
{
	U_V0_ZME2_VSP V0_ZME2_VSP;
	V0_ZME2_VSP.u32 = VDP_RegRead( ((HI_ULONG)&(pVdpReg->V0_ZME2_VSP.u32) + u32Data * VID_OFFSET));
	V0_ZME2_VSP.bits.ck_gt_en = u32CkGtEn;
	VDP_RegWrite( ((HI_ULONG)&(pVdpReg->V0_ZME2_VSP.u32) + u32Data * VID_OFFSET),V0_ZME2_VSP.u32);

	return ;
}


HI_VOID VDP_VID_SetHpzmeMode(HI_U32 u32Data, HI_U32 hpzme_mode)
{
	U_V0_HPZME V0_HPZME;

	V0_HPZME.u32 = VDP_RegRead( ((HI_ULONG)&(pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET));
	V0_HPZME.bits.hpzme_mode = hpzme_mode;
	VDP_RegWrite( ((HI_ULONG)&(pVdpReg->V0_HPZME.u32) + u32Data * VID_OFFSET),V0_HPZME.u32);

	return ;
}


HI_VOID VDP_VID_SetHpzmeCoef2(HI_U32 u32Data, HI_U32 coef2)
{
	U_V0_HPZME_COEF V0_HPZME_COEF;

	V0_HPZME_COEF.u32 = VDP_RegRead( ((HI_ULONG)&(pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET));
	V0_HPZME_COEF.bits.coef2 = coef2;
	VDP_RegWrite( ((HI_ULONG)&(pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET),V0_HPZME_COEF.u32);

	return ;
}


HI_VOID VDP_VID_SetHpzmeCoef1(HI_U32 u32Data, HI_U32 coef1)
{
	U_V0_HPZME_COEF V0_HPZME_COEF;

	V0_HPZME_COEF.u32 = VDP_RegRead( ((HI_ULONG)&(pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET));
	V0_HPZME_COEF.bits.coef1 = coef1;
	VDP_RegWrite( ((HI_ULONG)&(pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET),V0_HPZME_COEF.u32);

	return ;
}


HI_VOID VDP_VID_SetHpzmeCoef0(HI_U32 u32Data, HI_U32 coef0)
{
	U_V0_HPZME_COEF V0_HPZME_COEF;

	V0_HPZME_COEF.u32 = VDP_RegRead( ((HI_ULONG)&(pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET));
	V0_HPZME_COEF.bits.coef0 = coef0;
	VDP_RegWrite( ((HI_ULONG)&(pVdpReg->V0_HPZME_COEF.u32) + u32Data * VID_OFFSET),V0_HPZME_COEF.u32);

	return ;
}

